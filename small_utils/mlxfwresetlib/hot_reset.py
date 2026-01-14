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
    def _prepare_dbdf_for_hot_reset(dev_dbdf, logger, RegAccessObjArg=None):
        try:
            if RegAccessObjArg is None:
                MstDevObj = mtcr.MstDevice(mlxfwreset_utils.getDevDBDF(dev_dbdf, logger))
                RegAccessObj = regaccess.RegAccess(MstDevObj)
            else:
                RegAccessObj = RegAccessObjArg
            requester_pcie_index = RegAccessObj.sendMPQD(depth=0, node=0, DPNv=1, pcie_index=0)
            logger.debug('DevDBDF: {0}, requester_pcie_index: {1}'.format(mlxfwreset_utils.getDevDBDF(dev_dbdf, logger), requester_pcie_index))
            domain = mlxfwreset_utils.split_dbdf(mlxfwreset_utils.getDevDBDF(dev_dbdf, logger), logger)[HotResetFlow.DOMAIN]
            bus, device, _ = RegAccessObj.sendMPIR(depth=0, pcie_index=requester_pcie_index, node=0)
            function = 0
        finally:
            if RegAccessObjArg is None:  # we created the MstDevObj, so we need to close it
                MstDevObj.close()

        return {
            HotResetFlow.DOMAIN: domain,
            HotResetFlow.BUS: bus,
            HotResetFlow.DEVICE: device,
            HotResetFlow.FUNCTION: function
        }

    @staticmethod
    def _get_V3_field_from_vpd(dbdf_str, logger):
        cmd = "lspci -s {0} -vvv".format(dbdf_str)
        logger.debug('lspci command: {0}'.format(cmd))
        (rc, output, stderr) = cmdExec(cmd)
        if rc:
            raise RuntimeError(str(stderr))
        # logger.debug('lspci output: {0}'.format(output))

        for line in output.splitlines():
            if '[V3]' in line:
                v3 = line.strip().split()[-1]  # [V3] Vendor specific: 62ee5a540e91
                logger.debug('V3 field string: {0}'.format(v3))
                return v3

        raise HotResetError("No V3 field found")

    @staticmethod
    def _get_hidden_aux_dbdf(v3_prime_str, logger):
        try:
            cmd = "lspci -D -d 15b3:2100"
            (rc, pci_list, stderr) = cmdExec(cmd)
            if rc:
                raise RuntimeError(str(stderr))

            for line in pci_list.splitlines():
                aux_dbdf = line.strip().split()[0]  # for example: 82:00.0 Infiniband controller...
                try:
                    v3_aux_str = HotResetFlow._get_V3_field_from_vpd(aux_dbdf, logger)
                except Exception as error:
                    logger.warning("Failed to read V3 from {0}: {1}".format(aux_dbdf, error))
                    continue
                if v3_prime_str == v3_aux_str:
                    logger.debug('V3 numbers are identical, found aux device, dbdf: {0}, v3 number: {1}'.format(aux_dbdf, v3_aux_str))
                    return aux_dbdf
            else:
                logger.warning("No aux device found")
                return None

        except Exception as e:
            raise HotResetError(str(e))

    @staticmethod
    def get_upstream_port_aux_device(dbdf_aux_str, logger, RegAccessObj):
        dbdf_aux_dict = {}
        dbdf_aux_dict[HotResetFlow.FUNCTION] = 0
        dbdf_aux_dict[HotResetFlow.DOMAIN] = mlxfwreset_utils.split_dbdf(dbdf_aux_str, logger)[HotResetFlow.DOMAIN]
        dbdf_aux_dict[HotResetFlow.BUS], dbdf_aux_dict[HotResetFlow.DEVICE], _ = RegAccessObj.sendMPIR(depth=0, pcie_index=1, node=0)
        return dbdf_aux_dict

    @staticmethod
    def _get_hidden_socket_direct_dbdf_for_reset(dev_dbdf, logger, RegAccessObj):
        res = {}
        try:
            v3_prime_str = HotResetFlow._get_V3_field_from_vpd(dev_dbdf, logger)
            dbdf_aux_str = HotResetFlow._get_hidden_aux_dbdf(v3_prime_str, logger)
            if dbdf_aux_str:
                res = HotResetFlow.get_upstream_port_aux_device(dbdf_aux_str, logger, RegAccessObj)
        except Exception as error:
            raise HotResetError("Failed to retrieve hidden socket DBDF: {0}".format(error))

        if not res:  # we search for hidden aux as last resort - us not finding it means we couldn't track down the aux device and can't continue with the reset flow
            raise HotResetError("failed to find aux device both as hidden and as discovered")
        return res

    @staticmethod
    def _get_dbdf_aux_device(devices_sd, logger):
        if not devices_sd:
            raise HotResetError("No socket direct devices provided")
        if len(devices_sd) > 1:
            raise HotResetError("Only one device is supported for hot reset in SD mode")

        DevDBDF_sd = mlxfwreset_utils.getDevDBDF(devices_sd[0], logger)
        return mlxfwreset_utils.split_dbdf(DevDBDF_sd, logger)

    @staticmethod
    def hot_reset(mfrl, dev_dbdf, devices_sd, reset_flow, mst_dev, RegAccessObj, logger):
        try:
            dtor_result = RegAccessObj.getDTOR()
            timeout = mlxfwreset_utils.get_timeout_in_miliseconds(dtor_result, "EMBEDDED_CPU_OS_SHUTDOWN_TO") / 1000
            logger.debug('EMBEDDED_CPU_OS_SHUTDOWN timeout = {0}'.format(timeout))

            start_time = time.time()
            while not HotResetFlow.is_fw_ready_for_reset_trigger(mfrl):
                mlxfwreset_utils.check_if_elapsed_time(start_time, timeout, "The reset state did not change to 'waiting for reset trigger' state")

            dbdf_target_device_dict = HotResetFlow._prepare_dbdf_for_hot_reset(dev_dbdf, logger, RegAccessObj)
            logger.debug('dbdf_target_device_dict : {0}'.format(dbdf_target_device_dict))
            dbdf_sd_partner_dict = {}

            logger.debug('reset_flow: {0}'.format(reset_flow))
            if reset_flow == HotResetFlow.SINGLE_DEVICE:
                pass
            elif reset_flow == HotResetFlow.SOCKET_DIRECT:
                dbdf_sd_partner_dict = HotResetFlow._prepare_dbdf_for_hot_reset(devices_sd[0], logger)
                logger.debug('dbdf_sd_partner_dict: {0}'.format(dbdf_sd_partner_dict))
            elif reset_flow == HotResetFlow.HIDDEN_SOCKET_DIRECT:
                dbdf_sd_partner_dict = HotResetFlow._get_hidden_socket_direct_dbdf_for_reset(dev_dbdf, logger, RegAccessObj)
            else:
                raise HotResetError("Unknown reset type: {0}".format(reset_flow))

            is_socket_direct = 0 if not dbdf_sd_partner_dict else 1

            logger.debug('send_hot_reset | domain_target: 0x{0:x}, bus_target: 0x{1:x}, device_target: 0x{2:x}, function_target: 0x{3:x}, is_socket_direct: {4}, domain_sd_partner: 0x{5:x}, bus_sd_partner: 0x{6:x}, device_sd_partner: 0x{7:x}, function_sd_partner: 0x{8:x}'.format(
                dbdf_target_device_dict[HotResetFlow.DOMAIN], dbdf_target_device_dict[HotResetFlow.BUS], dbdf_target_device_dict[HotResetFlow.DEVICE], dbdf_target_device_dict[HotResetFlow.FUNCTION], is_socket_direct, dbdf_sd_partner_dict.get(HotResetFlow.DOMAIN, 0), dbdf_sd_partner_dict.get(HotResetFlow.BUS, 0), dbdf_sd_partner_dict.get(HotResetFlow.DEVICE, 0), dbdf_sd_partner_dict.get(HotResetFlow.FUNCTION, 0)))

            res = mst_dev.send_hot_reset(is_socket_direct, dbdf_target_device_dict[HotResetFlow.DOMAIN], dbdf_target_device_dict[HotResetFlow.BUS], dbdf_target_device_dict[HotResetFlow.DEVICE], dbdf_target_device_dict[HotResetFlow.FUNCTION], dbdf_sd_partner_dict.get(HotResetFlow.DOMAIN, 0), dbdf_sd_partner_dict.get(HotResetFlow.BUS, 0), dbdf_sd_partner_dict.get(HotResetFlow.DEVICE, 0), dbdf_sd_partner_dict.get(HotResetFlow.FUNCTION, 0))  # Using get() with default 0 for dbdf_sd_partner_dict values when device is not socket direct (then dbdf_sd_partner_dict is empty)

            if res != 0:
                raise HotResetError('Failed to reset the device (pci_reset_bus failed)')
            time.sleep(2)  # Per MosheS request, need 2 sec sleep to let driver load

        except Exception as e:
            raise HotResetError(str(e))
