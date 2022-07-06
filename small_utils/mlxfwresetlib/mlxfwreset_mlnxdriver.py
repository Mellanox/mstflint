# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --

"""
* $Id           : mlnxdriver.py 2017-11-28
* $Authors      : Ahmad Soboh (ahmads@mellanox.com)
"""

from __future__ import print_function
import abc
import os
import platform
from . import mlxfwreset_utils
from .mlxfwreset_utils import cmdExec, is_in_internal_host
from functools import reduce
from time import sleep


class DriverNotExist(Exception):
    pass


class DriverDisabled(Exception):
    pass


class DriverUnknownMode(Exception):
    pass

######################################################################
# Description:  Driver Class , use factory to get instance
# OS Support :  Linux/Windows.
######################################################################


class MlnxDriver(object):
    __metaclass__ = abc.ABCMeta
    """ Abstract driver Class that provides a simple start stop status methods
    """

    # Driver status constants
    DRIVER_IGNORE = 0
    DRIVER_LOADED = 1

    def __init__(self, logger, driverStatus):
        self.logger = logger
        self.driverStatus = driverStatus

    def driverStart(self):
        raise NotImplementedError("driverStart() is not implemented")

    def driverStop(self):
        raise NotImplementedError("driverStop() is not implemented")

    def getDriverStatus(self):
        return self.driverStatus


class LinuxRshimUserSpaceDriver:

    # The rshim user-space driver exists from BL2 (and up)
    # To start/stop all the rshim user-space drivers manually you can use "systemctl start/stop rshim"
    # In the future this driver might be started/stopped automatically (???)

    def _scan_rshim_drivers(self):

        result = []
        DRIVERS_PATH = "/dev/"
        rshim_drivers_names = [dir_name for dir_name in os.listdir(DRIVERS_PATH) if dir_name.startswith('rshim')]
        for rshim_driver_name in rshim_drivers_names:
            rshim_pci_device_name, rshim_drop_mode = None, None
            rshim_misc_file = DRIVERS_PATH + rshim_driver_name + "/misc"
            with open(rshim_misc_file) as f:
                for line in f:
                    if "DEV_NAME" in line:
                        rshim_pci_device_name = line.split()[1]
                    if "DROP_MODE" in line:  # Exist only in BL2
                        rshim_drop_mode = int(line.split()[1][0])
            if rshim_pci_device_name is not None and rshim_drop_mode is not None:
                result.append((rshim_misc_file, rshim_pci_device_name, rshim_drop_mode))
        return result

    def __init__(self, logger, user_pci_device_name):

        self.logger = logger

        for rshim_misc_file, rshim_pci_device_name, rshim_drop_mode in self._scan_rshim_drivers():
            if user_pci_device_name[5:11] in rshim_pci_device_name and rshim_drop_mode == 0:
                self.rshim_misc_file = rshim_misc_file
                self.pci_device_name = rshim_pci_device_name[5:]
                break
        else:
            raise DriverNotExist("There is no running user-space rshim driver")

    def _update_drop_mode(self, action):

        if self.rshim_misc_file:
            cmd = 'echo "DROP_MODE {0}" > {1}'.format(1 if action == 'stop' else 0, self.rshim_misc_file)
            self.logger.info('{0}'.format(cmd))
            rc, _, _ = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError('Failed to {0} user-space rshim driver ({1})'.format(action, self.rshim_misc_file))

    def stop(self):
        self._update_drop_mode('stop')

    def start(self):
        self._update_drop_mode('start')


class MlnxDriverLinux(MlnxDriver):

    # blocklist_file_path = '/etc/modprobe.d/mlxfwreset.conf'
    PCI_DRIVERS_PATH = '/sys/bus/pci/drivers'
    mlnx_drivers = ['mlx5_core', 'rshim_pcie', 'nvme']

    def __init__(self, devices, logger, skip):  # devices : 1 physical function per card

        self.drivers_dbdf = []  # A List of tuples (<dbdf>,<driver-name>)

        # Check if opensm is running in the background
        (rc, _, _) = cmdExec("pgrep opensm")
        if rc == 0:
            raise RuntimeError('Please stop "opensm" manually and resume operation!')

        if not skip:
            if not os.path.exists(MlnxDriverLinux.PCI_DRIVERS_PATH):
                raise RuntimeError("path {0} doesn't exist!".format(MlnxDriverLinux.PCI_DRIVERS_PATH))

            # Handle rshim user-space driver
            #################################
            self.rshim_driver = None
            if len(devices) == 1:  # BL devices has only one PCI device name (There is no BL socket-direct device)
                pci_device_name = mlxfwreset_utils.getDevDBDF(devices[0], logger)  # domain:bus:device.fn
                try:
                    self.rshim_driver = LinuxRshimUserSpaceDriver(logger, pci_device_name)
                except DriverNotExist:
                    pass

            for device in devices:

                dbdf = mlxfwreset_utils.getDevDBDF(device, logger)
                dbd = dbdf.split('.')[0]

                # Reset virtual functions (reset pf1 is speculative - only if exists)
                for pf_num in range(2):
                    num_vfs_file_path = '/sys/bus/pci/devices/{0}.{1}/sriov_numvfs'.format(dbd, pf_num)
                    if os.path.exists(num_vfs_file_path):
                        cmd = "echo 0 > {0} ".format(num_vfs_file_path)
                        logger.info('{0}'.format(cmd))
                        (rc, out, _) = cmdExec(cmd)
                        if rc != 0:
                            logger.info('Reset virtual functions failed : {0}'.format(out))

                        # Verify the reset of the VFs
                        with open(num_vfs_file_path) as file:
                            if int(file.read()) != 0:
                                raise RuntimeError('Reset virtual functions failed! Please reset virtual functions manually and resume operation')

                # insert all the instances of the driver that need unbind/bind
                cmd = "find {0} | grep {1}".format(MlnxDriverLinux.PCI_DRIVERS_PATH, dbd)
                logger.info('{0}'.format(cmd))
                (_, out, _) = cmdExec(cmd)
                for line in out.split('\n')[:-1]:
                    line = line.split('/')
                    driver_name, dbdf = line[-2], line[-1]
                    if self.rshim_driver is not None and self.rshim_driver.pci_device_name == dbdf and driver_name in ["vfio-pci", "uio_pci_generic"]:
                        logger.info("skip on vfio/uio driver (rshim user-space driver will stop it)")
                        continue
                    if driver_name not in MlnxDriverLinux.mlnx_drivers:
                        raise RuntimeError("mlxfwreset doesn't support 3rd party driver ({0})!\nPlease, stop the driver manually and resume operation with --skip_driver".format(driver_name))
                    self.drivers_dbdf.append((dbdf, driver_name))

            self.drivers_dbdf.sort()

        logger.info('{0}'.format(self.drivers_dbdf))

        driverStatus = MlnxDriver.DRIVER_IGNORE if skip or not self.drivers_dbdf else MlnxDriver.DRIVER_LOADED
        super(MlnxDriverLinux, self).__init__(logger, driverStatus)

    def driverStart(self):
        self.logger.info('MlnxDriverLinux driverStart()')

        driver_err, rshim_err = None, None

        # * Start NIC driver
        for dbdf, driver_name in self.drivers_dbdf:
            driver_path = '{0}/{1}'.format(MlnxDriverLinux.PCI_DRIVERS_PATH, driver_name)
            assert os.path.exists(driver_path)

            # In case of hotplug the OS *might* start the driver automatically as part of the rescan/enumeration stage.
            # On kernel XXXX we saw that the driver file (sysfs) doesn't exist 'on time' and as a result the tool will
            # start the driver even though the OS already triggered the driver start. In this case the tool gets error
            # from the CLI but we don't want the tool to exit with error. For that reason we added the retry mechanism

            MAX_NUM_OF_TRIES = 10
            try_num = 1
            while try_num <= MAX_NUM_OF_TRIES:
                if os.path.exists('/sys/bus/pci/devices/{0}/driver'.format(dbdf)):  # driver is up
                    driver_err = False
                    break
                else:                                                               # driver is down
                    cmd = 'echo "{0}" > {1}/bind'.format(dbdf, driver_path)
                    self.logger.info('{0}'.format(cmd))
                    (rc, _, _) = cmdExec(cmd)
                    if rc == 0:  # bind succeeded
                        driver_err = False
                        break
                    else:       # bind failed
                        try_num += 1
                        driver_err = True
                        sleep(0.1)

        # * Configure the driver in BlueField's internal host (ARM)
        if is_in_internal_host() and driver_err is False:                   # This code is WA. FR will be opened in rel1
            cmd = "mlnx_bf_configure"                                       # 2022 to address this issue (RM #2831210)
            rc, _, _ = cmdExec(cmd)
            if rc != 0:
                print("-W- Failed to configure the driver")

        # * Start RSHIM driver (BlueField)
        try:
            if self.rshim_driver:
                self.rshim_driver.start()
        except Exception as err:
            rshim_err = err

        # * Handle Errors (Best effort to try to start both drivers before indicating on error)
        if driver_err:
            raise RuntimeError("Failed to start driver! please start driver manually")
        if rshim_err:
            raise rshim_err

    def driverStop(self):
        self.logger.info('MlnxDriverLinux driverStop()')

        if self.rshim_driver:
            self.rshim_driver.stop()

        for dbdf, driver_name in self.drivers_dbdf:
            driver_path = '{0}/{1}'.format(MlnxDriverLinux.PCI_DRIVERS_PATH, driver_name)
            assert os.path.exists(driver_path)
            cmd = 'echo "{0}" > {1}/unbind'.format(dbdf, driver_path)
            self.logger.info('{0}'.format(cmd))
            (rc, _, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to stop driver! please stop driver manually and resume Operation")


class MlnxDriverFreeBSD(MlnxDriver):
    def __init__(self, logger, skip):
        logger.info('MlnxDriverFreeBSD object created')
        if skip:
            self.driverStatus = MlnxDriver.DRIVER_IGNORE
            return
        self._knownModules = [("mlx5en", False), ("mlx5ib", False), ("mlx4ib", False), ("mlxen", False),
                              ("mlx5", False)]
        # check whats loaded
        for i in range(0, len(self._knownModules)):
            cmd = "kldstat -n %s" % (self._knownModules[i][0])
            (rc, _, _) = cmdExec(cmd)
            if rc == 0:
                self._knownModules[i] = (self._knownModules[i][0], True)
        super(MlnxDriverFreeBSD, self).__init__(logger, self.getDriverStatusAux())

    def driverStart(self):
        self.logger.info('MlnxDriverFreeBSD driverStart()')
        for moduleName, isPresent in self._knownModules:
            if isPresent:
                cmd = "kldload %s" % moduleName
                (rc, stdout, stderr) = cmdExec(cmd)
                if rc and not ("module already loaded" in stderr):
                    raise RuntimeError("Failed to start driver! Please start driver manually")

    def driverStop(self):
        self.logger.info('MlnxDriverFreeBSD driverStop()')
        for moduleName, isPresent in self._knownModules:
            if isPresent:
                cmd = "kldunload %s" % moduleName
                (rc, stdout, stderr) = cmdExec(cmd)
                if rc and not ("can't find file" in stderr):
                    raise RuntimeError("Failed to stop driver! Please stop driver manually and resume Operation")

    def getDriverStatusAux(self):
        cmd = "ls -l /boot/kernel/ | grep mlx -c"
        (rc, stdout, _) = cmdExec(cmd)
        if rc != 0:
            raise DriverUnknownMode("Can not run the command: %s" % cmd)
        # the voodoo below checks if we had at least one kernel object loaded
        return (MlnxDriver.DRIVER_IGNORE, MlnxDriver.DRIVER_LOADED)[reduce(lambda x, y: x or y, map(lambda x: x[1], self._knownModules))]


class WindowsRshimDriver:
    """
    Rshim-driver is the "SOC management driver" (the driver that communicates with the ARMs) in a SmartNIC device
    This driver is located in the 'System devices' (and not under the 'Network adapters')
    We use the pnp-device utility to find/start/stop the management driver
    """

    def _powershell(self, cmd):
        powershell_cmd = 'powershell.exe -c "{0}"'.format(cmd)
        self.logger.info("{0}".format(powershell_cmd))
        result = cmdExec(powershell_cmd)
        self.logger.info("rc={0}\nstdout={1}\nstderr={2}".format(*result))
        return result

    def _get_pnp_device_name_for_network_adapter(self, network_adapter_name):
        """
        The method will convert network_adapter name e.g "Ethernet 8" to pnp_device name (instance-id)
        e.g "PCI\\VEN_15B3&DEV_A2D6&SUBSYS_004815B3&REV_00\4&2E75E12A&0&0110"
        """

        cmd = "(Get-NetAdapterHardwareInfo -name '{0}').InterfaceDescription".format(network_adapter_name)
        rc, output, _ = self._powershell(cmd)
        if rc != 0:
            raise RuntimeError("Failed to execute {0}".format(cmd))

        interface_description = output.strip()

        cmd = "(Get-PnpDevice -FriendlyName '{0}').InstanceId".format(interface_description)    # We use the InterfaceDescription from the previous command
        rc, output, _ = self._powershell(cmd)                                                   # as FriendlyName in the current command
        if rc != 0:
            raise RuntimeError("Failed to execute {0}".format(cmd))

        pnp_device_name = output.strip()
        self.logger.info("network_adapter_name : {} ; pnp_device_name : {}".format(network_adapter_name, pnp_device_name))
        return pnp_device_name

    def __init__(self, logger, network_adapters, network_adapter_pci_device_id):

        self.logger = logger

        # * Network-adapter to SOC-management PCI-device-id mapping table
        PCI_DEVICE_ID_MAPPING_TABLE = {0xA2D2: 0xC2D2, 0xA2D6: 0xC2D3, 0xA2D9: 0xC2D4, 0xA2DC: 0xC2D5}

        # * Check if it's a Smart NIC. If yes, extract  pci-device-id of the management device
        if network_adapter_pci_device_id in PCI_DEVICE_ID_MAPPING_TABLE:
            soc_management_pci_device_id = PCI_DEVICE_ID_MAPPING_TABLE[network_adapter_pci_device_id]
        else:
            self.logger.info("Not a SmartNIC device")
            raise DriverNotExist("Not a SmartNic device")

        # * Assertion
        if len(network_adapters) == 0:
            raise DriverNotExist("There is no management driver when there are no network adapters")

        # * Check if "Get-PnpDevice" command exists
        #! The "Get-PnpDevice" is not supported in "Windows server 2012"
        #! and "Windows server 2012 R2" so we can't support Bluefield in
        #! these OS versions
        powershell_cmd = 'powershell.exe -c "Get-PnpDevice > $null"'
        result = cmdExec(powershell_cmd)
        if result[0] != 0:
            self.logger.debug("Get-PnpDevice is not supported in this OS version")
            raise RuntimeError("Get-PnpDevice is not supported in this OS version")

        # * Create a network-adapter as pnp device
        network_adapter_as_pnp_device = self._get_pnp_device_name_for_network_adapter(network_adapters[0])
        self.logger.debug("Network adapter as pnp device: {0}".format(network_adapter_as_pnp_device))

        # * Extract the "common part" from the pnp-device
        # The "common part" is common for both the network-adapter and SOC management
        # Example:
        #   pnp-device                    : PCI\VEN_15B3&DEV_A2D6&SUBSYS_004815B3&REV_00\4&2E75E12A&0&0110
        #   common part                   : 2E75E12A
        pnp_device_common_part = network_adapter_as_pnp_device.split("&")[4]
        self.logger.debug("pnp_device_common_part = {0}".format(pnp_device_common_part))

        # * Set the name of the management driver
        cmd = "(Get-PnpDevice -InstanceId '*VEN_15B3*DEV_{0:x}*{1}*').InstanceId".format(soc_management_pci_device_id, pnp_device_common_part)
        rc, output, _ = self._powershell(cmd)
        if rc != 0:
            raise RuntimeError("Faild to execute {0}".format(cmd))
        self.driver_name = output.strip()
        self.logger.info("rshim-driver name : {0}".format(self.driver_name))

        # * Check if the management driver is enabled
        cmd = "(Get-PnpDevice -InstanceId '{0}').Status".format(self.driver_name)
        rc, output, _ = self._powershell(cmd)
        if rc == 0 and output.strip() == 'OK':
            self.logger.debug("rshim-driver name : {0} is enabled".format(self.driver_name))
        else:
            self.logger.debug("rshim-driver name : {0} is disabled".format(self.driver_name))
            raise DriverDisabled("rshim-driver is disabled")

    def start(self):
        cmd = "Enable-PnpDevice -InstanceId '{0}' -confirm:$false".format(self.driver_name)
        rc, _, _ = self._powershell(cmd)
        if rc != 0:
            raise RuntimeError("Failed to start rshim-driver")

    def stop(self):
        cmd = "Disable-PnpDevice -InstanceId '{0}' -confirm:$false".format(self.driver_name)
        rc, _, _ = self._powershell(cmd)
        if rc != 0:
            raise RuntimeError("Failed to stop rshim-driver")


class MlnxDriverWindows(MlnxDriver):

    def get_device_drivers(self, logger, seg_bus_device_list):

        def read_5_lines(txt):
            'Generator to read 5 non-empty lines'

            lines = [line.strip() for line in txt.split('\n') if line.strip()]  # remove empty lines and convert to list
            assert len(lines) % 5 == 0

            lines = iter(lines)
            try:
                while True:
                    yield (next(lines), next(lines), next(lines), next(lines), next(lines))
            except StopIteration:
                return

        cmd = 'powershell.exe -c "Get-NetAdapterHardwareInfo | Format-List -Property Segment,Bus,Device,Name,InterfaceDescription'
        logger.debug(cmd)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to get Adapters Hardware Information")
        logger.debug(out)

        drivers_names = []
        for seg_line, bus_line, device_line, name_line, description_line in read_5_lines(out):
            seg_num_ii = int(seg_line.split(':')[1])
            bus_num_ii = int(bus_line.split(':')[1])
            device_num_ii = int(device_line.split(':')[1])
            seg_bus_device_list_ii = (seg_num_ii, bus_num_ii, device_num_ii)
            name_ii = name_line.split(':')[1].strip()

            # Filter only relevant drivers
            #  1. Ignore drivers that are not relevant to required PCI address
            #  2. Ignore the management driver ('rshim bus' in the 'Network Adapters' section)
            if seg_bus_device_list_ii in seg_bus_device_list and 'Management' not in description_line:
                drivers_names.append(name_ii)

        return drivers_names

    def _is_powershell_exists(self):
        rc, _, _ = cmdExec('where powershell.exe')
        return rc == 0

    def __init__(self, logger, skip, devices, pci_device_id):

        logger.info('MlnxDriverWindows object created')
        if skip:
            super(MlnxDriverWindows, self).__init__(logger, MlnxDriver.DRIVER_IGNORE)
            return

        # Check if Powershell installed
        if self._is_powershell_exists() is False:
            raise RuntimeError("PowerShell.exe is not installed. Please stop the driver manually and re-run the tool with --skip_driver ")

        # Find seg:bus:device of the device(s)
        seg_bus_device_list = []
        for device in devices:
            seg_bus_device = mlxfwreset_utils.getDevDBDF(device, logger).split('.')[0]
            seg_num = int(seg_bus_device.split(':')[0], 16)
            bus_num = int(seg_bus_device.split(':')[1], 16)
            device_num = int(seg_bus_device.split(':')[2], 16)
            seg_bus_device_list.append((seg_num, bus_num, device_num))

        # Find the relevant network adapters for the seg:bus:device
        targetedAdaptersTemp = self.get_device_drivers(logger, seg_bus_device_list)
        logger.debug(targetedAdaptersTemp)

        # Create Rshim-driver (for Bluefield devices)
        logger.info("Create Rshim driver")
        try:
            self.rshim_driver = WindowsRshimDriver(logger, targetedAdaptersTemp, pci_device_id)
        except (DriverNotExist, DriverDisabled):
            self.rshim_driver = None

        # Filter the network adapters that are disabled
        self.targetedAdapters = []
        for targetedAdapter in targetedAdaptersTemp:
            cmd = 'powershell.exe -c "Get-NetAdapter \'%s\' | Format-List -Property Status' % targetedAdapter
            logger.debug(cmd)
            (rc, out, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to get Adapter '%s' Information" % targetedAdapter)
            if ("Disabled" not in out):
                self.targetedAdapters.append(targetedAdapter)
        logger.debug(self.targetedAdapters)

        drivers_exist = len(self.targetedAdapters) > 0 or self.rshim_driver

        driverStatus = MlnxDriver.DRIVER_LOADED if drivers_exist else MlnxDriver.DRIVER_IGNORE
        super(MlnxDriverWindows, self).__init__(logger, driverStatus)

    def driverStart(self):
        self.logger.info('MlnxDriverWindows driverStart()')

        driver_err, rshim_err = None, None

        try:                                # rshim-driver must be enabled before network adapaters
            if self.rshim_driver:
                self.rshim_driver.start()
        except Exception as err:
            rshim_err = err

        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe -c Enable-NetAdapter '%s' " % targetedAdapter
            self.logger.info(cmd)
            (rc, _, _) = cmdExec(cmd)
            if rc != 0:
                driver_err = True

        # Error (Best effort to try to start both drivers before indicating on error)
        if driver_err:
            raise RuntimeError("Failed to start driver! please start driver manually")
        if rshim_err:
            raise rshim_err

    def driverStop(self):
        self.logger.info('MlnxDriverWindows driverStop()')
        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe -c Disable-NetAdapter '%s' -confirm:$false" % targetedAdapter
            self.logger.info(cmd)
            (rc, stdout, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to stop driver! Please stop driver manually and resume Operation")

        if self.rshim_driver:        # must be disabled after network adapaters
            self.rshim_driver.stop()  # reason: The manangement network adapter is a dependency of the SoC management i/f


class MlnxDriverFactory(object):
    def getDriverObj(self, logger, skip, devices, pci_device_id):
        operatingSystem = platform.system()
        if operatingSystem == "Linux":
            return MlnxDriverLinux(devices, logger, skip)
        elif operatingSystem == "FreeBSD":
            return MlnxDriverFreeBSD(logger, skip)
        elif operatingSystem == "Windows":
            return MlnxDriverWindows(logger, skip, devices, pci_device_id)
        else:
            raise RuntimeError("Unsupported OS: %s" % operatingSystem)
