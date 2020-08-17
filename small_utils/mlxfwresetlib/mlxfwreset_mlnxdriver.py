# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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
from .mlxfwreset_utils import cmdExec
from functools import reduce


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


class MlnxDriverLinux(MlnxDriver):

    # blacklist_file_path = '/etc/modprobe.d/mlxfwreset.conf'
    PCI_DRIVERS_PATH = '/sys/bus/pci/drivers'
    mlnx_drivers = ['mlx5_core','rshim_pcie']

    def __init__(self,devices,logger,skip): # devices : 1 physical function per card

        self.drivers_dbdf = [] # A List of tuples (<dbdf>,<driver-name>)

        # Check if opensm is running in the background
        (rc, _, _) = cmdExec("pgrep opensm")
        if rc == 0:
            raise RuntimeError('Please stop "opensm" manually and resume operation!')

        if not skip:
            if not os.path.exists(MlnxDriverLinux.PCI_DRIVERS_PATH):
                raise RuntimeError("path {0} doesn't exist!".format(MlnxDriverLinux.PCI_DRIVERS_PATH))

            for device in devices:

                dbdf = mlxfwreset_utils.getDevDBDF(device,logger)
                dbd = dbdf.split('.')[0]

                # Reset virtual functions (reset pf1 is speculative - only if exists)
                for pf_num in range(2):
                    num_vfs_file_path = '/sys/bus/pci/devices/{0}.{1}/sriov_numvfs'.format(dbd,pf_num)
                    if os.path.exists(num_vfs_file_path):
                        cmd = "echo 0 > {0} ".format(num_vfs_file_path)
                        logger.info('{0}'.format(cmd))
                        (rc, out, _) = cmdExec(cmd)
                        if rc!=0:
                            logger.info('Reset virtual functions failed : {0}'.format(out))

                        # Verify the reset of the VFs
                        with open(num_vfs_file_path) as file:
                            if int(file.read())!=0:
                                raise RuntimeError('Reset virtual functions failed! Please reset virtual functions manually and resume operation')

                # insert all the instances of the driver that need unbind/bind
                cmd = "find {0} | grep {1}".format(MlnxDriverLinux.PCI_DRIVERS_PATH,dbd)
                logger.info('{0}'.format(cmd))
                (_, out, _) = cmdExec(cmd)
                for line in out.split('\n')[:-1]:
                    line = line.split('/')
                    driver_name,dbdf = line[-2],line[-1]
                    if driver_name not in MlnxDriverLinux.mlnx_drivers:
                        raise RuntimeError("mlxfwreset doesn't support 3rd party driver ({0})!\nPlease, stop the driver manually and resume operation with --skip_driver".format(driver_name))
                    self.drivers_dbdf.append((dbdf,driver_name))

            self.drivers_dbdf.sort()

        logger.info('{0}'.format(self.drivers_dbdf))

        driverStatus = MlnxDriver.DRIVER_IGNORE if skip or not self.drivers_dbdf else MlnxDriver.DRIVER_LOADED
        super(MlnxDriverLinux, self).__init__(logger, driverStatus)

    # def disableAutoLoad(self):
    #     with open(MlnxDriverLinux.blacklist_file_path,'w') as blacklist_file:
    #         blacklist_file.write('blacklist mlx5_core\n')
    #         blacklist_file.write('blacklist mlx5_ib\n')
    #         blacklist_file.write('blacklist mlx5_fpga_tools\n')
    #
    # def enableAutoLoad(self):
    #     if os.path.exists(MlnxDriverLinux.blacklist_file_path):
    #         os.remove(MlnxDriverLinux.blacklist_file_path)

    def driverStart(self):
        self.logger.info('MlnxDriverLinux driverStart()')
        for dbdf,driver_name in self.drivers_dbdf:
            driver_path = '{0}/{1}'.format(MlnxDriverLinux.PCI_DRIVERS_PATH,driver_name)
            assert os.path.exists(driver_path)
            # Bind if not binded (in HotPlug, 'rescan' will bind automatically)
            if not os.path.exists('/sys/bus/pci/devices/{0}/driver'.format(dbdf)):
                cmd = 'echo "{0}" > {1}/bind'.format(dbdf, driver_path)
                self.logger.info('{0}'.format(cmd))
                (rc, _, _) = cmdExec(cmd)
                if rc!=0:
                    raise RuntimeError("Failed to start driver! please start driver manually to load FW")


    def driverStop(self):
        self.logger.info('MlnxDriverLinux driverStop()')
        for dbdf,driver_name in self.drivers_dbdf:
            driver_path = '{0}/{1}'.format(MlnxDriverLinux.PCI_DRIVERS_PATH,driver_name)
            assert os.path.exists(driver_path)
            cmd = 'echo "{0}" > {1}/unbind'.format(dbdf, driver_path)
            self.logger.info('{0}'.format(cmd))
            (rc, _, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to stop driver! please stop driver manually and resume Operation")


class MlnxDriverFreeBSD(MlnxDriver):
    def __init__(self, logger, skip):
        logger.info('MlnxDriverFreeBSD object created')
        if skip == True:
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
                    raise RuntimeError("Failed to Start Driver, please start driver manually to load FW")

    def driverStop(self):
        self.logger.info('MlnxDriverFreeBSD driverStop()')
        for moduleName, isPresent in self._knownModules:
            if isPresent:
                cmd = "kldunload %s" % moduleName
                (rc, stdout, stderr) = cmdExec(cmd)
                if rc and not ("can't find file" in stderr):
                    raise RuntimeError("Failed to Stop Driver, please stop driver manually and resume Operation")

    def getDriverStatusAux(self):
        cmd = "ls -l /boot/kernel/ | grep mlx -c"
        (rc, stdout, _) = cmdExec(cmd)
        if rc != 0:
            raise DriverUnknownMode("Can not run the command: %s" % cmd)
        # the voodoo below checks if we had at least one kernel object loaded
        return (MlnxDriver.DRIVER_IGNORE, MlnxDriver.DRIVER_LOADED)[reduce(lambda x, y: x or y, map(lambda x: x[1], self._knownModules))]


class WindowsRshimDriver:
    """
    Rshim-driver is the SOC managment driver (the driver that communicates with the ARMs) in a SmartNIC device
    """

    def _powershell(self, cmd):
        powershell_cmd = 'powershell.exe -c "{0}"'.format(cmd)
        self.logger.info("{0}".format(powershell_cmd))
        result = cmdExec(powershell_cmd)
        self.logger.info("rc={0}\nstdout={1}\nstderr={2}".format(*result))
        return result

    def __init__(self, logger):

        self.logger = logger

        #SOC_MANAGEMENT_PCI_DEVICE_IDS = {"A2D2": "C2D2", "A2D6": "C2D3", "A2D9": "C2D4", "A2DC": "C2D5"}
        # TODO Need to disable only relevant drivers (might be different device-id and multiple from the same type)

        cmd = "(Get-PnpDevice -InstanceId '*VEN_15B3&DEV_C2D2*').InstanceId"
        rc, output, _ = self._powershell(cmd)
        if rc == 0 and output:
            # TODO if number of lines >1 then we need to filter the right driver
            self.driver_name = output.strip()
            self.logger.info("rshim-driver name : {0}".format(self.driver_name))
        else:
            raise DriverNotExist("rshim-driver doesn't exist")

        cmd = "(Get-PnpDevice -InstanceId '*VEN_15B3&DEV_C2D2*').Status"
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

        def read_4_lines(txt):
            'Generator to read 4 non-empty lines'

            lines = [line.strip() for line in txt.split('\n') if line.strip()]  # remove empty lines and convert to list
            assert len(lines) % 4 == 0

            lines = iter(lines)
            try:
                while True:
                    yield (next(lines), next(lines), next(lines), next(lines))
            except StopIteration:
                return

        cmd = 'powershell.exe -c "Get-NetAdapterHardwareInfo | Format-List -Property Segment,Bus,Device,Name'
        logger.debug(cmd)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to get Adapters Hardware Information")
        logger.debug(out)

        drivers_names = []
        for seg_line, bus_line, device_line, name_line in read_4_lines(out):
            seg_num_ii = int(seg_line.split(':')[1])
            bus_num_ii = int(bus_line.split(':')[1])
            device_num_ii = int(device_line.split(':')[1])
            seg_bus_device_list_ii = (seg_num_ii, bus_num_ii, device_num_ii)
            name_ii = name_line.split(':')[1].strip()

            if seg_bus_device_list_ii in seg_bus_device_list:
                drivers_names.append(name_ii)

        return drivers_names

    def _is_powershell_exists(self):
        rc, _, _ = cmdExec('where powershell.exe')
        return rc == 0

    def __init__(self, logger, skip, devices):

        logger.info('MlnxDriverWindows object created')
        if skip == True:
            super(MlnxDriverWindows, self).__init__(logger, MlnxDriver.DRIVER_IGNORE)
            return
        
        # Check if Powershell installed
        if self._is_powershell_exists() is False:
            raise RuntimeError("PowerShell.exe is not installed. Please stop the driver manually and re-run the tool with --skip_driver ")

        try:
            self.rshim_driver = WindowsRshimDriver(logger)
        except (DriverNotExist, DriverDisabled):
            self.rshim_driver = None            


        seg_bus_device_list = []
        # Extract bus and device from the device_name
        for device in devices:
            seg_bus_device = mlxfwreset_utils.getDevDBDF(device,logger).split('.')[0]
            seg_num = int(seg_bus_device.split(':')[0],16)
            bus_num = int(seg_bus_device.split(':')[1],16)
            device_num = int(seg_bus_device.split(':')[2],16)
            seg_bus_device_list.append((seg_num, bus_num, device_num))
        
        # Find the network adapters for the dus:device
        targetedAdaptersTemp = self.get_device_drivers(logger, seg_bus_device_list)
        logger.debug(targetedAdaptersTemp)
     
        # Filter the network adapter thar are disabled
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
        if self.rshim_driver:
            self.rshim_driver.start() # must be enabled before network adapaters 
        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe -c Enable-NetAdapter '%s' " % targetedAdapter
            self.logger.info(cmd)
            (rc, stdout, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to Start Driver, please start driver manually to load FW")
        
    def driverStop(self):
        self.logger.info('MlnxDriverWindows driverStop()')
        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe -c Disable-NetAdapter '%s' -confirm:$false" % targetedAdapter
            self.logger.info(cmd)
            (rc, stdout, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to Stop Driver, please stop driver manually and resume Operation")
        
        if self.rshim_driver:        # must be disabled after network adapaters
            self.rshim_driver.stop() # reason: The manangement network adapter is a dependency of the SoC management i/f


class MlnxDriverFactory(object):
    def getDriverObj(self,logger, skip, devices):
        operatingSystem = platform.system()
        if operatingSystem == "Linux":
            return MlnxDriverLinux(devices,logger,skip)
        elif operatingSystem == "FreeBSD":
            return MlnxDriverFreeBSD(logger, skip)
        elif operatingSystem == "Windows":
            return MlnxDriverWindows(logger, skip, devices)
        else:
            raise RuntimeError("Unsupported OS: %s" % operatingSystem)
