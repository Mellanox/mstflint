# Copyright (c) Sep 2019 Mellanox Technologies LTD. All rights reserved.
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --
import os
import regaccess


class CmdNotSupported(Exception):
    pass


class ResetReqMethod():
    LINK_DISABLE, HOT_RESET = 0, 1


class CmdRegMfrl():

    LIVE_PATCH, IMMEDIATE_RESET, PCI_RESET, WARM_REBOOT = 0, 1, 3, 4
    reset_levels_db = [
        {'level': LIVE_PATCH, 'description': 'Driver, PCI link, network link will remain up ("live-Patch")', 'mask': 0b1, 'support_reset_type': False, 'valid_default': True},
        {'level': IMMEDIATE_RESET, 'description': 'Only ARM side will not remain up ("Immediate reset").', 'mask': 0b10, 'support_reset_type': True, 'valid_default': False},
        {'level': PCI_RESET, 'description': 'Driver restart and PCI reset', 'mask': 0b1000, 'support_reset_type': True, 'valid_default': True},
        {'level': WARM_REBOOT, 'description': 'Warm Reboot', 'mask': 0b1000000, 'support_reset_type': True, 'valid_default': True},
    ]

    FULL_CHIP, PHY_LESS, NIC_ONLY, ARM_ONLY, ARM_OS_SHUTDOWN = 0, 1, 2, 3, 4
    reset_types_db = [
        {'type': FULL_CHIP, 'description': 'Full chip reset', 'mask': 0b1, 'supported': True},
        {'type': PHY_LESS, 'description': 'Phy-less reset (keep network port active during reset)', 'mask': 0b10},
        {'type': NIC_ONLY, 'description': 'NIC only reset (for SoC devices)', 'mask': 0b100},
        {'type': ARM_ONLY, 'description': 'ARM only reset', 'mask': 0b1000},
        {'type': ARM_OS_SHUTDOWN, 'description': 'ARM OS shut down', 'mask': 0b10000}
    ]

    RESET_STATE_ERROR_NEGOTIATION_TIMEOUT = 3
    RESET_STATE_ERROR_NEGOTIATION_DIS_ACK = 4
    RESET_STATE_ERROR_DRIVER_UNLOAD_TIMEOUT = 5
    RESET_STATE_ARM_OS_IS_UP_PLEASE_SHUT_DOWN = 6
    RESET_STATE_ARM_OS_SHUTDOWN_IN_PROGRESS = 7
    RESET_STATE_WAITING_FOR_RESET_TRIGGER = 8

    RESET_STATE_ERRORS = {
        RESET_STATE_ERROR_NEGOTIATION_TIMEOUT: "The reset flow encountered a failure due to a reset state error of negotiation timeout",
        RESET_STATE_ERROR_NEGOTIATION_DIS_ACK: "The reset flow encountered a failure due to a reset state error of negotiation dis-acknowledgment",
        RESET_STATE_ERROR_DRIVER_UNLOAD_TIMEOUT: "The reset flow encountered a failure due to a reset state error of driver unload timeout",
        RESET_STATE_ARM_OS_IS_UP_PLEASE_SHUT_DOWN: "The reset flow encountered a failure because the ARM OS is up and needs to be shut down"
    }

    @classmethod
    def descriptions(cls):
        result = "Reset levels:\n"
        for reset_level_ii in cls.reset_levels_db:
            result += "\t{0}: {1}\n".format(reset_level_ii['level'], reset_level_ii['description'])
        result += "\nReset types:\n"
        for reset_types_ii in cls.reset_types_db:
            result += "\t{0}: {1}\n".format(reset_types_ii['type'], reset_types_ii['description'])
        result += "\n"
        return result

    @classmethod
    def reset_levels(cls):
        'Return a list with all the optional reset-levels'
        return [(reset_level_ii['level']) for reset_level_ii in cls.reset_levels_db]

    @classmethod
    def reset_levels_default(cls):
        return [(reset_level_ii['level'], reset_level_ii['valid_default']) for reset_level_ii in cls.reset_levels_db]

    @classmethod
    def reset_types(cls):
        'Return a list with all the optional reset-types'
        return [reset_type_ii['type'] for reset_type_ii in cls.reset_types_db]

    @classmethod
    def reset_level_description(cls, reset_level):
        'Return the text description for the input reset-level'
        for reset_level_ii in cls.reset_levels_db:
            if reset_level_ii['level'] == reset_level:
                return reset_level_ii['description']
        else:
            raise RuntimeError("Reset-level {0} doesn't exist in reset-levels !".format(reset_level))

    @classmethod
    def reset_type_description(cls, reset_type):
        'Return the text description for the input reset-type'
        for reset_type_ii in cls.reset_types_db:
            if reset_type_ii['type'] == reset_type:
                return reset_type_ii['description']
        else:
            raise RuntimeError("Reset-type {0} doesn't exist in reset-types !".format(reset_type))

    @classmethod
    def is_phy_less_reset(cls, reset_type):
        return reset_type == cls.PHY_LESS

    @classmethod
    def is_reset_level_trigger_is_pci_link(cls, reset_level):
        for reset_level_ii in cls.reset_levels_db:
            if reset_level_ii['level'] == reset_level:
                return True if (reset_level_ii['mask'] & 0x8) else False
        else:
            raise RuntimeError("Reset-level {0} doesn't exist in reset-levels !".format(reset_level))

    def __init__(self, reg_access, logger):
        self._reg_access = reg_access
        self.logger = logger
        self._warning_printed = False
        self._reset_levels = CmdRegMfrl.reset_levels_db[:]  # copy
        self._reset_types = CmdRegMfrl.reset_types_db[:]   # copy

        # Read register ('get' command) from device
        self.read()

    def _update_variables(self, reg):

        # Update 'pci_rescan_required' field
        self._pci_rescan_required = reg['pci_rescan_required']

        # Update 'supported' field in reset_levels
        reset_level = reg['reset_level']
        for reset_level_ii in self._reset_levels:
            reset_level_ii['supported'] = (reset_level & reset_level_ii['mask']) != 0

        # Update 'supported' field in reset_types
        reset_type = reg['reset_type']
        for reset_type_ii in self._reset_types:
            if 'supported' not in reset_type_ii:
                reset_type_ii['supported'] = (reset_type & reset_type_ii['mask']) != 0

        self._reset_state = reg['reset_state']

    def _send(self, method, reset_level=None, reset_type=None, reset_sync=None, pci_reset_request_method=None):
        try:
            self.logger.debug("sending MFRL with method={}, reset_level={}, reset_type={}, reset_sync={}, pci_reset_request_method={}".format(
                method, reset_level, reset_type, reset_sync, pci_reset_request_method
            ))
            return self._reg_access.sendMFRL(method, reset_level, reset_type, reset_sync, pci_reset_request_method)
        except regaccess.RegAccException as e:
            if reset_sync == 1:
                raise e
            # FW bug first mfrl register might fail
            self.logger.debug("Retry MFRL with method={}, reset_level={}, reset_type={}, reset_sync={}, pci_reset_request_method={}".format(
                method, reset_level, reset_type, reset_sync, pci_reset_request_method
            ))
            return self._reg_access.sendMFRL(method, reset_level, reset_type, reset_sync, pci_reset_request_method)

    def _read_reg(self):
        reset_level, reset_type, pci_rescan_required, reset_state = self._send(self._reg_access.GET)
        return {
            'reset_level': reset_level,
            'reset_type': reset_type,
            'pci_rescan_required': pci_rescan_required,
            'reset_state': reset_state
        }

    def _write_reg(self, reset_level, reset_type, reset_sync, pci_reset_request_method):
        self._send(self._reg_access.SET, reset_level, reset_type, reset_sync, pci_reset_request_method)

    def is_pci_rescan_required(self):
        return True if self._pci_rescan_required == 1 else False

    def query_text(self, is_any_sync_supported=None, sync_2_only_supported=False):
        'return the text for the query operation in mlxfwreset'
        # Reset levels
        skip_pci_reset = False
        if is_any_sync_supported is None:
            skip_pci_reset = True
        default_reset_level = self.default_reset_level(is_any_sync_supported, skip_pci_reset, sync_2_only_supported)
        result = "Reset-levels:\n"
        for reset_level_ii in self._reset_levels:
            level = reset_level_ii['level']
            description = reset_level_ii['description']

            if reset_level_ii['level'] is CmdRegMfrl.PCI_RESET and is_any_sync_supported is False:
                supported = "Not Supported"
            else:
                supported = "Supported" if reset_level_ii['supported'] else "Not Supported"
                default = "(default)" if reset_level_ii["level"] == default_reset_level else ""

            result += "{0}: {1:<62}-{2:<14}{3}\n".format(level, description, supported, default)

        # Reset types
        relevant_levels = []
        for reset_level_ii in self._reset_levels:
            if reset_level_ii['support_reset_type']:
                relevant_levels.append(str(reset_level_ii['level']))

        result += "\nReset-types "
        result += "(relevant only for reset-levels {0}):\n".format(','.join(relevant_levels))
        default_reset_type = self.default_reset_type()
        for reset_type_ii in self._reset_types:
            type_ = reset_type_ii['type']
            description = reset_type_ii['description']
            supported = "Supported" if reset_type_ii['supported'] else "Not Supported"
            default = "(default)" if reset_type_ii["type"] == default_reset_type else ""
            result += "{0}: {1:<62}-{2:<14}{3}\n".format(type_, description, supported, default)

        return result

    def is_reset_level_supported(self, reset_level):
        'check if the input reset-level is supported'
        for reset_level_ii in self._reset_levels:
            if reset_level_ii['level'] == reset_level:
                return reset_level_ii['supported']
        else:
            return False

    def is_reset_type_supported(self, reset_type):
        'Check if the input reset-type is supported'
        for reset_type_ii in self._reset_types:
            if reset_type_ii['type'] == reset_type:
                return reset_type_ii['supported']
        else:
            return False

    def is_reset_level_support_reset_type(self, reset_level):
        'Check if the input reset-level can be executed with reset_type (different than the default)'
        for reset_level_ii in self._reset_levels:
            if reset_level_ii['level'] == reset_level:
                return reset_level_ii['support_reset_type']
        else:
            return False

    def default_reset_level(self, is_any_sync_supported, skip_pci_reset, sync_2_only_supported):
        'Return the default reset-level (minimal supported reset-level)'
        for reset_level_ii, is_default in CmdRegMfrl.reset_levels_default():
            if reset_level_ii == CmdRegMfrl.PCI_RESET and not skip_pci_reset and not is_any_sync_supported:
                continue
            if reset_level_ii == CmdRegMfrl.PCI_RESET and sync_2_only_supported is True:  # Sync 2 is the only supported sync, so PCI reset will not be the default.
                continue
            if self.is_reset_level_supported(reset_level_ii) and is_default:
                return reset_level_ii
        raise CmdNotSupported("There is no supported reset-level")

    def default_reset_type(self):
        'Return the default reset-type'

        # Return NIC_ONLY if supported (Will be supported only in SmartNIC)
        for reset_type_ii in self._reset_types:
            if reset_type_ii['supported'] and reset_type_ii['type'] == CmdRegMfrl.NIC_ONLY:
                return reset_type_ii['type']

        # Return FULL_CHIP
        for reset_type_ii in self._reset_types:
            if reset_type_ii['supported'] and reset_type_ii['type'] == CmdRegMfrl.FULL_CHIP:
                return reset_type_ii['type']

        # Return ARM_ONLY
        for reset_type_ii in self._reset_types:
            if reset_type_ii['supported'] and reset_type_ii['type'] == CmdRegMfrl.ARM_ONLY:
                return reset_type_ii['type']

        # Return ARM_OS_SHUTDOWN
        for reset_type_ii in self._reset_types:
            if reset_type_ii['supported'] and reset_type_ii['type'] == CmdRegMfrl.ARM_OS_SHUTDOWN:
                return reset_type_ii['type']

        raise CmdNotSupported("There is no supported reset-type")

    def is_default_reset_type(self, reset_type):
        return reset_type == self.default_reset_type()

    def check_reset_state_and_fail_on_error(self):
        self.logger.debug("reset_state={}".format(self._reset_state))

        # Ready for reset trigger.
        if self._reset_state == CmdRegMfrl.RESET_STATE_WAITING_FOR_RESET_TRIGGER:
            return True

        # Check for error.
        if self._reset_state in CmdRegMfrl.RESET_STATE_ERRORS:
            if self._reset_state == CmdRegMfrl.RESET_STATE_ARM_OS_IS_UP_PLEASE_SHUT_DOWN and \
                    not os.environ.get("MLXFWRESET_EXIT_ON_ARM_SHUTDOWN_NOT_COMPLETED"):
                if not self._warning_printed:
                    print("Please note that ARM shutdown was not completed")   # According to arch decision, we don't fail on this error and contiue waiting for the FW state to change to 8.
                    self._warning_printed = True  # Don't print the warning again.
            raise Exception(CmdRegMfrl.RESET_STATE_ERRORS[self._reset_state])

        # Need to keep waiting for the FW state to change.
        return False

    def read(self):
        # Read register ('get' command) from device
        reg = self._read_reg()

        # Update privates variables.
        self._update_variables(reg)

    def send(self, reset_level, reset_type, reset_sync, pci_reset_request_method):
        """
        send MFRL Set command
        Verify that reset-level and reset-type are supported (reset-sync is not verified)
        """

        # Reset-level to send
        for reset_level_ii in self._reset_levels:
            if reset_level_ii['level'] == reset_level and reset_level_ii['supported']:
                reset_level_2_send = reset_level_ii['mask']
                break
        else:
            raise CmdNotSupported('Failed to send MFRL! reset-level {0} is not supported!'.format(reset_level))

        # If the reset level it is WARM_REBOOT, we need to set the PCI toggle bit (if supported) because some servers may not perform PERST during the power cycle.
        if reset_level == CmdRegMfrl.WARM_REBOOT:
            for reset_level_ii in self._reset_levels:
                if reset_level_ii['level'] == CmdRegMfrl.PCI_RESET and self.is_reset_level_supported(CmdRegMfrl.PCI_RESET):
                    reset_level_2_send = reset_level_2_send | reset_level_ii['mask']

        # Reset-type to send
        for reset_type_ii in self._reset_types:
            if reset_type_ii['type'] == reset_type and reset_type_ii['supported']:
                reset_type_2_send = reset_type
                break
        else:
            raise CmdNotSupported('Failed to send MFRL! reset-type {0} is not supported!'.format(reset_type))

        self._write_reg(reset_level_2_send, reset_type_2_send, reset_sync, pci_reset_request_method)
