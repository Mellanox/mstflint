# Copyright (c) Sep 2019 Mellanox Technologies LTD. All rights reserved.
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
#--

class CmdRegMfrl():

    LIVE_PATCH, PCI_RESET, WARM_REBOOT, COLD_REBOOT= 0,3,4,5
    reset_levels_db = [
        {'level': LIVE_PATCH, 'description': 'Driver, PCI link, network link will remain up ("live-Patch")', 'bit_offset' : 0x1, 'support_reset_type': False},
        {'level': PCI_RESET, 'description': 'Driver restart and PCI reset', 'bit_offset' : 0x8, 'support_reset_type': True},
        {'level': WARM_REBOOT, 'description': 'Warm Reboot', 'bit_offset' : 0x40, 'support_reset_type': True},
        {'level': COLD_REBOOT, 'description': 'Cold Reboot', 'bit_offset' : 0x80, 'support_reset_type': False}
    ]

    FULL_CHIP, PHY_LESS = 0,1
    reset_types_db = [
        {'type': FULL_CHIP, 'description': 'Full chip reset', 'bit_offset' : 0x1, 'default': True, 'supported': True},
        {'type': PHY_LESS, 'description': 'Phy-less reset ("port-alive" - network link will remain up)', 'bit_offset' : 0x2,'default': False}
    ]

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
        return [reset_level_ii['level'] for reset_level_ii in cls.reset_levels_db]

    @classmethod
    def reset_types(cls):
        'Return a list with all the optional reset-types'
        return [reset_type_ii['type'] for reset_type_ii in cls.reset_types_db]

    @classmethod
    def default_reset_type(cls):
        'Return the default reset-type'
        for reset_type_ii in cls.reset_types_db:
            if reset_type_ii['default'] is True:
                return reset_type_ii['type']

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

    def __init__(self, reg_access):

        self._reg_access = reg_access

        self._reset_levels = CmdRegMfrl.reset_levels_db[:] # copy
        self._reset_types = CmdRegMfrl.reset_types_db[:]   # copy

        # Read register ('get' command) from device
        reg = self._read_reg()
        # Update 'supported' field in reset_levels
        reset_level = reg['reset_level']
        for reset_level_ii in self._reset_levels:
            reset_level_ii['supported'] = (reset_level & reset_level_ii['bit_offset'])  != 0
        # Update 'supported' field in reset_types
        reset_type  = reg['reset_type']
        for reset_type_ii in self._reset_types:
            if 'supported' not in reset_type_ii:
                reset_type_ii['supported'] = (reset_type & reset_type_ii['bit_offset']) != 0 

    def _read_reg(self):
        reset_level, reset_type = self._reg_access.sendMFRL(self._reg_access.GET)
        return {
            'reset_level' : reset_level,
            'reset_type'  : reset_type
        }

    def _write_reg(self, reset_level, reset_type, reset_sync):
        self._reg_access.sendMFRL(self._reg_access.SET, reset_level, reset_type, reset_sync)

    def query_text(self):
        'return the text for the query operation in mlxfwreset'
        # Reset levels
        default_reset_level = self.default_reset_level()
        result = "Reset-levels:\n"
        for reset_level_ii in self._reset_levels:
            level = reset_level_ii['level']
            description = reset_level_ii['description']
            supported = "Supported" if reset_level_ii['supported'] else "Not Supported"
            default = "(default)" if reset_level_ii["level"]==default_reset_level else ""
            result += "{0}: {1:<62}-{2:<14}{3}\n".format(level, description, supported, default)

        # Reset types
        relevant_levels = []
        for reset_level_ii in self._reset_levels:
            if reset_level_ii['support_reset_type']:
                relevant_levels.append(str(reset_level_ii['level']))

        result += "\nReset-types "
        result += "(relevant only for reset-levels {0}):\n".format(','.join(relevant_levels))
        for reset_type_ii in self._reset_types:
            type_ = reset_type_ii['type']
            description = reset_type_ii['description']
            supported = "Supported" if reset_type_ii['supported'] else "Not Supported"
            default = "(default)" if reset_type_ii["default"] else ""
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


    def default_reset_level(self):
        'Return the default reset-level (minimal supported reset-level)'
        for reset_level_ii in CmdRegMfrl.reset_levels():
            if self.is_reset_level_supported(reset_level_ii) is True:
                return reset_level_ii
        raise Exception("There is no supported reset-level")

    
    def is_default_reset_type(self, reset_type):
        return reset_type == self.default_reset_type()

    def is_default_reset_level(self, reset_level):
        return reset_level == self.default_reset_level()

    def send(self, reset_level, reset_type, reset_sync):
        """
        send MFRL Set command
        Verify that reset-level and reset-type are supported (reset-sync is not verified)
        """

        # Reset-level to send         
        for reset_level_ii in self._reset_levels:
            if reset_level_ii['level'] == reset_level and reset_level_ii['supported']:
                reset_level_2_send = reset_level_ii['bit_offset']
                break
        else:
            raise RuntimeError('Failed to send MFRL! reset-level {0} is not supported!'.format(reset_level))
        
        # Reset-type to send
        for reset_type_ii in self._reset_types:
            if reset_type_ii['type'] == reset_type and reset_type_ii['supported']:
                reset_type_2_send = reset_type
                break
        else:
            raise RuntimeError('Failed to send MFRL! reset-type {0} is not supported!'.format(reset_type))

        self._write_reg(reset_level_2_send, reset_type_2_send, reset_sync)
