# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --

from __future__ import print_function

import os
import sys

if not getattr(sys, 'frozen', False):
    _base = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
    _candidates = [
        _base,
        os.path.join(os.path.dirname(_base), "mlxpci"),
    ]
    for _candidate in _candidates:
        if os.path.exists(os.path.join(_candidate, "mlxpci_lib.py")):
            if _candidate not in sys.path:
                sys.path.insert(0, _candidate)
            break

from mlxpci_lib import CAP_DPC, CAP_PCI_EXPRESS, PCIDeviceFactory

# Offsets within the DPC extended capability structure (PCIe Base Spec)
PCI_EXP_DPC_RP_PIO_MASK = 0x10
PCI_EXP_DPC_RP_PIO_SEVERITY = 0x14

# Standard (legacy) PCI capability list pointer (PCI Base Spec)
PCI_CAPABILITY_LIST_PTR = 0x34
# PCI Express Capabilities Register offset within the PCIe capability
PCI_EXP_FLAGS = 0x02
# Device/Port Type field (bits [7:4] of the PCI Express Capabilities Register)
PCI_EXP_TYPE_ROOT_PORT = 0x4

# Events that block driver sync (sync 1)
RP_PIO_BLOCK_EVENT_BITS = (0, 1, 2, 16, 17, 18)

RP_PIO_EVENT_NAMES = {
    0: "Cfg UR Cpl",
    1: "Cfg CA Cpl",
    2: "Cfg CTO",
    16: "Mem UR Cpl",
    17: "Mem CA Cpl",
    18: "Mem CTO",
}


def _block_event(mask, severity, bit, logger):
    # Block[event] = (~Mask[event]) and Severity[event]
    bit_mask = 1 << bit
    blocked = (not bool(mask & bit_mask)) and bool(severity & bit_mask)
    logger.debug(
        "rp_pio_dpc: event bit %d (%s): mask=%d severity=%d block=%s"
        % (bit, RP_PIO_EVENT_NAMES.get(bit, "?"), bool(mask & bit_mask),
           bool(severity & bit_mask), blocked)
    )
    return blocked


def compute_rp_pio_block(mask, severity, logger):
    """
    # Return (block_driver_sync, blocked_event_bits) per arch:
    Block driver sync = OR of Block[event] for Cfg/Mem UR, CA, CTO events.
    """
    blocked_bits = []
    for bit in RP_PIO_BLOCK_EVENT_BITS:
        blocked = _block_event(mask, severity, bit, logger)
        if blocked:
            blocked_bits.append(bit)
    return (len(blocked_bits) > 0, blocked_bits)


def find_pci_capability_offset(pci_read, dbdf, capability_id, logger):
    # Walk the standard (legacy) PCI capability list starting at the cap pointer.
    # pci_read(dbdf, offset, width) -> int
    try:
        offset = pci_read(dbdf, PCI_CAPABILITY_LIST_PTR, "B") & 0xfc
    except Exception as e:
        logger.debug(
            "rp_pio_dpc: failed to read capability list pointer on %s: %s" % (dbdf, e)
        )
        return None
    visited = set()
    while offset >= 0x40 and offset not in visited:
        visited.add(offset)
        try:
            header = pci_read(dbdf, offset, "W")
        except Exception as e:
            logger.debug(
                "rp_pio_dpc: failed to read capability header at 0x%x on %s: %s"
                % (offset, dbdf, e)
            )
            return None
        cap_id = header & 0xff
        if cap_id == capability_id:
            return offset
        offset = (header >> 8) & 0xfc
    return None


def _is_root_port(pci_read, dbdf, logger):
    """Return True if dbdf is a PCIe Root Port (Device/Port Type == Root Port)."""
    exp_offset = find_pci_capability_offset(pci_read, dbdf, CAP_PCI_EXPRESS, logger)
    if exp_offset is None:
        logger.debug("rp_pio_dpc: no PCI Express capability on %s" % dbdf)
        return False
    try:
        flags = pci_read(dbdf, exp_offset + PCI_EXP_FLAGS, "W")
    except Exception as e:
        logger.debug(
            "rp_pio_dpc: failed to read PCI Express flags on %s: %s" % (dbdf, e)
        )
        return False
    port_type = (flags >> 4) & 0xf
    logger.debug("rp_pio_dpc: %s PCIe device/port type = 0x%x" % (dbdf, port_type))
    return port_type == PCI_EXP_TYPE_ROOT_PORT


def _get_root_port_dbdf(endpoint_dbdf, get_parent, logger):
    logger.debug("rp_pio_dpc: resolving root port for endpoint %s" % endpoint_dbdf)
    root_port = None
    cur = get_parent(endpoint_dbdf)
    visited = set()
    while cur is not None and cur not in visited:
        visited.add(cur)
        logger.debug("rp_pio_dpc: ancestor of %s is %s" % (endpoint_dbdf, cur))
        root_port = cur
        cur = get_parent(cur)
    if root_port is None:
        logger.debug("rp_pio_dpc: no parent for endpoint %s" % endpoint_dbdf)
        return None
    logger.debug("rp_pio_dpc: root port of %s is %s" % (endpoint_dbdf, root_port))
    return root_port


class RpPioDpcBlockChecker(object):
    def __init__(self, endpoint_dbdf, logger, pci_op=None):
        self.logger = logger
        self._endpoint_dbdf = endpoint_dbdf
        self._pci_op = pci_op

        self.block_driver_sync = False
        self._dpc_port_dbdf = None
        self._mask = None
        self._severity = None
        self._blocked_event_bits = []
        self._applicable = False
        self._driver_sync_disabled = False

        self.logger.debug(
            "rp_pio_dpc: init checker for endpoint %s" % self._endpoint_dbdf
        )
        if pci_op is None:
            self.logger.debug("rp_pio_dpc: skip check (no PCI operations object)")
            return

        self._evaluate()

    def _pci_read(self, dbdf, offset, width="L"):
        return self._pci_op.read(dbdf, offset, width)

    def _get_parent(self, dbdf):
        return self._pci_op.getPciParentAddr(dbdf)

    def _evaluate(self):
        root_port_dbdf = _get_root_port_dbdf(self._endpoint_dbdf, self._get_parent, self.logger)
        if root_port_dbdf is None:
            return

        # RP PIO mask/severity registers are Root-Port-specific. On switch
        # topologies, downstream ports may also expose DPC, so confirm the
        # selected device is actually a Root Port before reading those fields.
        if not _is_root_port(self._pci_read, root_port_dbdf, self.logger):
            self.logger.debug(
                "rp_pio_dpc: %s is not a Root Port; skipping RP PIO check" % root_port_dbdf
            )
            return

        self.logger.debug("rp_pio_dpc: checking root port %s for DPC capability" % root_port_dbdf)
        try:
            pci_device = PCIDeviceFactory().get(root_port_dbdf, "debug")
            dpc_cap_offset = pci_device.get_extended_capability_offset(CAP_DPC)
        except Exception as e:
            self.logger.debug("rp_pio_dpc: failed to query DPC capability on %s: %s" % (root_port_dbdf, e))
            return
        if dpc_cap_offset is None:
            self.logger.debug("rp_pio_dpc: no DPC capability on root port %s" % root_port_dbdf)
            return

        mask_offset = dpc_cap_offset + PCI_EXP_DPC_RP_PIO_MASK
        severity_offset = dpc_cap_offset + PCI_EXP_DPC_RP_PIO_SEVERITY
        try:
            self.logger.debug("rp_pio_dpc: reading RP PIO mask at 0x%x and severity at 0x%x on %s"
                              % (mask_offset, severity_offset, root_port_dbdf))
            mask = self._pci_read(root_port_dbdf, mask_offset, "L")
            severity = self._pci_read(root_port_dbdf, severity_offset, "L")
        except Exception as e:
            self.logger.debug("rp_pio_dpc: failed to read RP PIO registers on %s: %s" % (root_port_dbdf, e))
            return

        self._applicable = True
        self._dpc_port_dbdf = root_port_dbdf
        self._mask = mask
        self._severity = severity
        self.logger.debug("rp_pio_dpc: evaluating block conditions (mask=0x%x severity=0x%x)"
                          % (mask, severity))
        blocked, blocked_bits = compute_rp_pio_block(mask, severity, self.logger)
        self._blocked_event_bits = blocked_bits
        self.block_driver_sync = blocked

        self.logger.debug(
            "rp_pio_dpc: result port=%s applicable=%s block_driver_sync=%s events=%s"
            % (root_port_dbdf, self._applicable, blocked,
               [RP_PIO_EVENT_NAMES[b] for b in blocked_bits])
        )

    def apply_restrictions(self, mroq):
        if not self.block_driver_sync:
            self.logger.debug("rp_pio_dpc: no restrictions to apply")
            return

        if mroq.mroq_is_supported():
            self.logger.debug("rp_pio_dpc: applying restrictions (disable driver sync)")
            mroq.disable_driver_sync(self.logger)
            self._driver_sync_disabled = True
        else:
            self.logger.debug("rp_pio_dpc: driver sync will be blocked at request validation")

    def blocked_event_names(self):
        return [RP_PIO_EVENT_NAMES[b] for b in self._blocked_event_bits]

    def print_warning(self):
        if not self.block_driver_sync:
            return
        events = ", ".join(self.blocked_event_names())
        state = "disabled" if self._driver_sync_disabled else "blocked"
        self.logger.debug("Reset sync 1 (driver) is {0}: the PCIe Root Port DPC PIO mechanism is "
                          "enabled for: {1}. Driver status polling during reset can trigger downstream "
                          "port containment on the parent port ({2}).".format(state, events, self._dpc_port_dbdf))


def apply_rp_pio_dpc_restrictions(endpoint_dbdf, mroq, logger, pci_op=None):
    """
    Evaluate RP PIO mask/severity on the upstream path and update the MROQ sync flags.
    Returns RpPioDpcBlockChecker instance (skipped when pci_op is None).
    """
    logger.debug("rp_pio_dpc: apply restrictions for endpoint %s" % endpoint_dbdf)
    checker = RpPioDpcBlockChecker(endpoint_dbdf, logger, pci_op=pci_op)
    checker.apply_restrictions(mroq)
    logger.debug(
        "rp_pio_dpc: done block_driver_sync=%s"
        % (checker.block_driver_sync,)
    )
    return checker
