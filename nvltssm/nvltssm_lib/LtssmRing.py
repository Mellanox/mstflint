# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

from nvltssm_lib.LtssmTraceException import LtssmTraceException


class LtssmTables:
    """The name tables of the CX8-generation LTSSM logger."""

    STATES = {
        0x00: "DETECT_RESET",
        0x01: "DETECT_QUIET",
        0x02: "DETECT_ACTIVE",
        0x03: "DETECT_ACTIVE_WAIT",
        0x04: "DETECT_SPEED",
        0x05: "POLLING_ACTIVE",
        0x06: "POLLING_COMPLIANCE_ENTRY",
        0x07: "POLLING_COMPLIANCE_SPEED",
        0x08: "POLLING_COMPLIANCE_ACTIVE",
        0x09: "POLLING_COMPLIANCE_EXIT",
        0x0a: "POLLING_CONFIGURATION",
        0x0b: "CONFIGURATION_LINKWIDTH_START",
        0x0c: "CONFIGURATION_LINKWIDTH_ACCEPT",
        0x0d: "CONFIGURATION_LANENUM_WAIT",
        0x0e: "CONFIGURATION_LANENUM_ACCEPT",
        0x0f: "CONFIGURATION_COMPLETE",
        0x10: "CONFIGURATION_IDLE",
        0x11: "RECOVERY_RCVRLOCK",
        0x12: "RECOVERY_EQ_PHASE0",
        0x13: "RECOVERY_EQ_PHASE1",
        0x14: "RECOVERY_EQ_PHASE2",
        0x15: "RECOVERY_EQ_PHASE3",
        0x16: "RECOVERY_EQ_LEAD_REQ",
        0x17: "RECOVERY_EQ_LEAD_EVAL",
        0x18: "RECOVERY_SPEED",
        0x19: "RECOVERY_RCVRCFG",
        0x1a: "RECOVERY_IDLE",
        0x1b: "L0",
        0x1c: "L0_EXIT",
        0x1d: "L0_TX_RECOVERY_READY",
        0x1e: "L1_ENTRY",
        0x1f: "L1_0_IDLE",
        0x20: "L2_IDLE",
        0x21: "L2_ENTRY",
        0x22: "LOOPBACK_ENTRY_PRE",
        0x23: "LOOPBACK_ENTRY_POST",
        0x24: "LOOPBACK_ENTRY_SPEED",
        0x25: "LOOPBACK_ACTIVE",
        0x26: "LOOPBACK_EXIT",
        0x27: "DISABLE_ENTRY",
        0x28: "DISABLE_TX_EIDLE",
        0x29: "HOT_RESET",
        0x2a: "LINK_RESET_RST",
        0x2b: "L1_IDLE_BLCG_EN",
        0x2c: "L1_IDLE_PLL_PD",
        0x2d: "L1_IDLE_CPM",
        0x2e: "L1_IDLE_EXIT",
        0x2f: "L1_1_IDLE",
        0x30: "L1_1_EXIT",
        0x31: "L1_2_ENTRY",
        0x32: "L1_2_IDLE",
        0x33: "L1_2_EXIT",
        0x34: "FW_EVENT",
        0xfd: "LTSSM_FW_EVENT_PERST_ASSERTED",
        0xfe: "LTSSM_FW_EVENT_PERST_DEASSERTED",
    }

    # Why the state was left.
    REASONS = {
        0: "Framing Error",
        1: "TS",
        2: "EIEOS",
        3: "EIOS/FW INITIATED",
        4: "Replay Rollover",
        5: "Redo Equalizaion",
        6: "Timeout",
        7: "FW",
    }

    FW_EVENTS = {
        0: "INITFC_DONE_DURING_GEN1_2",
        1: "PXD_RESET_IN_UNEXPECTED_PORT_STATE",
        2: "PXD_RESET_WHILE_PACKET_IN_FLIGHT",
        3: "LINKUP_WHILE_NPI_ENGO_FIFO_NOT_EMPTY",
        4: "FW_EVENT_PXP_DSP_PH1_CONFIG",
        6: "FW_EVENT_DISABLE_LTSSM_TRACER",
        7: "FW_EVENT_ENABLE_LTSSM_TRACER",
        8: "FW_EVENT_MAX_VALUE",
    }

    # States that are worth calling out on their own line.
    NOTABLE_STATES = {
        0x29: "Link hot reset",
        0x2a: "Link reset",
        0xfd: "Perst asserted",
        0xfe: "Perst deasserted",
    }


class LtssmRecord:
    """Base of everything the ring walk produces."""

    def __init__(self, slot):
        self.slot = slot


class LtssmTiming:
    """Dwell time of one ring slot, in logger ticks."""

    # The logger's timer_granularity is ignored, as the reference decode does.
    TICK_NS = 1024
    SATURATED_TICKS = 0x7fff
    NS_IN_MS = 1000000.0

    def __init__(self, ticks):
        self.ticks = ticks

    @property
    def milliseconds(self):
        return (self.ticks * self.TICK_NS) / self.NS_IN_MS

    @property
    def is_saturated(self):
        return self.ticks == self.SATURATED_TICKS


class LtssmEntry(LtssmRecord):
    """One LTSSM state transition logged in a ring slot."""

    EMPTY_STATE = 0x00
    FW_EVENT_STATE = 0x03
    WIDTH_X16_ENCODING = 0x7
    WIDTH_X16 = 16

    def __init__(self, slot, state, reason, speed, width, ticks):
        super().__init__(slot)
        self.state = state
        self.reason = reason
        self.speed = speed
        self.width_encoding = width
        self.timing = LtssmTiming(ticks)

    @property
    def is_empty(self):
        return self.speed == 0 and self.state == self.EMPTY_STATE

    @property
    def is_fw_event(self):
        return self.state == self.FW_EVENT_STATE

    @property
    def state_name(self):
        return LtssmTables.STATES.get(self.state, "")

    @property
    def reason_name(self):
        return LtssmTables.REASONS.get(self.reason, "")

    @property
    def link_width(self):
        if self.width_encoding == self.WIDTH_X16_ENCODING:
            return self.WIDTH_X16

        return 1 << self.width_encoding


class LtssmEvent(LtssmRecord):
    """A firmware event logged in a ring slot instead of a state transition."""

    def __init__(self, slot, state, reason, event_num, ticks):
        super().__init__(slot)
        self.state = state
        self.reason = reason
        self.event_num = event_num
        self.timing = LtssmTiming(ticks)

    @property
    def event_name(self):
        return LtssmTables.FW_EVENTS.get(self.event_num, "FW_EVENT")


class LtssmAnnotation(LtssmRecord):
    """A note inserted before the entry that caused it."""

    SPEED_CHANGE = "speed_change"
    WIDTH_CHANGE = "width_change"
    NOTABLE_STATE = "notable_state"

    def __init__(self, slot, kind, old=None, new=None, name=None):
        super().__init__(slot)
        self.kind = kind
        self.old = old
        self.new = new
        self.name = name


class LtssmCurrentState(LtssmRecord):
    """The link state as it is right now, not a ring slot."""

    def __init__(self, state, speed, width):
        super().__init__(None)
        self.state = state
        self.speed = speed
        # Already a lane count, unlike the ring's width encoding.
        self.link_width = width

    @property
    def state_name(self):
        return LtssmTables.STATES.get(self.state, "")


class LtssmRing:
    """Walks the ring logger of one link, oldest slot first."""

    class Fields:
        """Sub-field names of the LTSSM nodes, identical on every device unlike the node names."""

        CURRENT_INDEX = "current_index"
        CURRENT_LOGGED_SIZE = "current_logged_size"
        FULL = "full"
        CURRENT_LINK_SPEED = "current_link_speed"
        NEGOTIATED_LINK_WIDTH = "negotiated_link_width"
        STATE = "state"
        REASON = "reason"
        SPEED = "speed"
        WIDTH = "width"
        TIME = "time"

    SIZE = 128
    # The firmware event number is overlaid on the ring line and no ADB field
    # describes it, so it is cut out of the reconstructed raw dword.
    EVENT_NUM_START_BIT = 8
    EVENT_NUM_MASK = 0x1f

    def __init__(self, fields, device_info):
        self._fields = fields
        self._ring_node = device_info.ring_node
        self._current_index_field = self._qualify(device_info.logger_ctrl_node, self.Fields.CURRENT_INDEX)
        self._logged_size_field = self._qualify(device_info.logger_ctrl_node, self.Fields.CURRENT_LOGGED_SIZE)
        self._current_state_field = self._qualify(device_info.state_node, self.Fields.FULL)
        self._current_speed_field = self._qualify(device_info.link_status_node, self.Fields.CURRENT_LINK_SPEED)
        self._current_width_field = self._qualify(device_info.link_status_node, self.Fields.NEGOTIATED_LINK_WIDTH)
        self._fields_by_address = {}
        for field in fields.values():
            self._fields_by_address.setdefault(field.address, []).append(field)
        self.current_index = self._read(self._current_index_field) % self.SIZE
        self.logged_size = min(self._read(self._logged_size_field), self.SIZE)

    @staticmethod
    def _qualify(node, field):
        return "{}.{}".format(node, field)

    def _read(self, name):
        field = self._fields.get(name)
        if field is None:
            raise LtssmTraceException("The dump holds no {} field".format(name))

        return field.value

    def _slot_field_name(self, slot, field):
        return "{}[{}].{}".format(self._ring_node, slot, field)

    def _slot_dword(self, slot):
        """Rebuild the raw ring dword out of the fields that cover it."""
        address = self._fields[self._slot_field_name(slot, self.Fields.STATE)].address
        dword = 0
        for field in self._fields_by_address[address]:
            dword |= field.value << field.start_bit

        return dword

    def _entry(self, slot):
        return LtssmEntry(slot=slot,
                          state=self._read(self._slot_field_name(slot, self.Fields.STATE)),
                          reason=self._read(self._slot_field_name(slot, self.Fields.REASON)),
                          speed=self._read(self._slot_field_name(slot, self.Fields.SPEED)),
                          width=self._read(self._slot_field_name(slot, self.Fields.WIDTH)),
                          ticks=self._read(self._slot_field_name(slot, self.Fields.TIME)))

    def _event(self, entry):
        event_num = (self._slot_dword(entry.slot) >> self.EVENT_NUM_START_BIT) & self.EVENT_NUM_MASK

        return LtssmEvent(slot=entry.slot, state=entry.state, reason=entry.reason, event_num=event_num,
                          ticks=entry.timing.ticks)

    def current_state(self):
        return LtssmCurrentState(state=self._read(self._current_state_field),
                                 speed=self._read(self._current_speed_field),
                                 width=self._read(self._current_width_field))

    def _logged_slots(self):
        """The slots holding logged data, oldest first.

        The logger fills the ring from slot 0 upwards and only once it has wrapped
        does the write cursor mark the oldest slot. Below that the slots past the
        cursor were never written, and hold whatever the RAM powered up with.
        """
        if self.logged_size < self.SIZE:
            return range(self.logged_size)

        return ((self.current_index + offset) % self.SIZE for offset in range(self.SIZE))

    def walk(self):
        """Yield the ring records oldest first, annotations before their entry."""
        last_speed = None
        last_width = None

        for slot in self._logged_slots():
            entry = self._entry(slot)

            if entry.is_fw_event:
                yield self._event(entry)
                continue

            if entry.is_empty:
                continue

            if entry.speed != 0:
                if last_speed is None:
                    last_speed = entry.speed
                elif entry.speed != last_speed:
                    yield LtssmAnnotation(slot, LtssmAnnotation.SPEED_CHANGE, old=last_speed, new=entry.speed)
                    last_speed = entry.speed

                if last_width is None:
                    last_width = entry.link_width
                elif entry.link_width != last_width:
                    yield LtssmAnnotation(slot, LtssmAnnotation.WIDTH_CHANGE, old=last_width, new=entry.link_width)
                    last_width = entry.link_width

            if entry.state in LtssmTables.NOTABLE_STATES:
                yield LtssmAnnotation(slot, LtssmAnnotation.NOTABLE_STATE,
                                      name=LtssmTables.NOTABLE_STATES[entry.state])

            yield entry

        yield self.current_state()
