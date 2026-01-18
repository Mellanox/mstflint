# Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

try:
    import sys
    import os
    import time
    from enum import Enum
    sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
    from mlxfwresetlib.mlxfwreset_utils import cmdExec
    from mlxfwresetlib.logger import LoggerFactory
    from mlxfwresetlib import mlxfwreset_utils
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)


class HotResetError(Exception):
    pass


class HotResetFlow():
    SINGLE_DEVICE = "SINGLE_DEVICE"
    SOCKET_DIRECT = "SOCKET_DIRECT"
    HIDDEN_SOCKET_DIRECT = "HIDDEN_SOCKET_DIRECT"
    DOMAIN = "domain"
    BUS = "bus"
    DEVICE = "device"
    FUNCTION = "function"

    @staticmethod
    def is_fw_ready_for_reset_trigger(mfrl):
        try:
            mfrl.read()
        except Exception:
            return False
        return mfrl.check_reset_state_and_fail_on_error()

    @staticmethod
    def hot_reset(mfrl, dev_dbdf, devices_sd, drivers_safety_check_manager, mst_dev, RegAccessObj, logger):
        try:
            dtor_result = RegAccessObj.getDTOR()
            timeout = mlxfwreset_utils.get_timeout_in_miliseconds(dtor_result, "EMBEDDED_CPU_OS_SHUTDOWN_TO") / 1000
            logger.debug('EMBEDDED_CPU_OS_SHUTDOWN timeout = {0}'.format(timeout))

            start_time = time.time()
            while not HotResetFlow.is_fw_ready_for_reset_trigger(mfrl):
                mlxfwreset_utils.check_if_elapsed_time(start_time, timeout, "The reset state did not change to 'waiting for reset trigger' state")

            reset_flow = drivers_safety_check_manager._hot_reset_flow
            logger.debug('reset_flow: {0}'.format(reset_flow))

            in_parallel = 0 if not drivers_safety_check_manager._dbdf_sd_partner_dict else 1

            logger.debug('send_hot_reset | dbdf_target_domain: 0x{0:x}, dbdf_target_bus: 0x{1:x}, dbdf_target_device: 0x{2:x}, dbdf_target_function: 0x{3:x}, in_parallel: {4}, dbdf_sd_partner_domain: 0x{5:x}, dbdf_sd_partner_bus: 0x{6:x}, dbdf_sd_partner_device: 0x{7:x}, dbdf_sd_partner_function: 0x{8:x}'.format(
                drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.DOMAIN], drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.BUS], drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.DEVICE], drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.FUNCTION], in_parallel, drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.DOMAIN, 0), drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.BUS, 0), drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.DEVICE, 0), drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.FUNCTION, 0)))

            res = mst_dev.send_hot_reset(in_parallel, drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.DOMAIN], drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.BUS], drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.DEVICE], drivers_safety_check_manager._dbdf_target_device_dict[HotResetFlow.FUNCTION], drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.DOMAIN, 0), drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.BUS, 0), drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.DEVICE, 0), drivers_safety_check_manager._dbdf_sd_partner_dict.get(HotResetFlow.FUNCTION, 0))  # Using get() with default 0 for aux values when device is not socket direct (then dbdf_sd_partner_dict is empty)

            if res != 0:
                raise HotResetError('Failed to reset the device (pci_reset_bus failed)')
            time.sleep(2)  # Per MosheS request, need 2 sec sleep to let driver load

        except Exception as e:
            raise HotResetError(str(e))
