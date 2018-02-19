#!/usr/bin/python

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
#--

"""
* $Id           : mlnxdriver.py 2017-11-28
* $Authors      : Ahmad Soboh (ahmads@mellanox.com)
"""

import abc
import os
import platform
import mlxfwreset_utils
from mlxfwreset_utils import cmdExec


######################################################################
# Description:  NoDriver Exception
# OS Support :  Linux/Windows.
######################################################################
class NoDriver(Exception):
    pass

######################################################################
# Description:  DriverUnknownMode Exception
# OS Support :  Linux/Windows.
######################################################################
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

    def __init__(self, logger,driverStatus):
        self.logger = logger
        self.driverStatus = driverStatus

    def driverStart(self):
        raise NotImplementedError("driverStart() is not implemented")

    def driverStop(self):
        raise NotImplementedError("driverStop() is not implemented")

    def getDriverStatus(self):
        return self.driverStatus


class MlnxDriverLinux(MlnxDriver):
    __metaclass__ = abc.ABCMeta

    blacklist_file_path = '/etc/modprobe.d/mlxfwreset.conf'

    def __init__(self,logger,driverStatus):
        super(MlnxDriverLinux, self).__init__(logger,driverStatus)

    def disableAutoLoad(self):
        with open(MlnxDriverLinux.blacklist_file_path,'w') as blacklist_file:
            blacklist_file.write('blacklist mlx4_core\n')
            blacklist_file.write('blacklist mlx5_core\n')
            blacklist_file.write('blacklist mlx4_ib\n')
            blacklist_file.write('blacklist mlx5_ib\n')
            blacklist_file.write('blacklist mlx4_en\n')


    def enableAutoLoad(self):
        if os.path.exists(MlnxDriverLinux.blacklist_file_path):
            os.remove(MlnxDriverLinux.blacklist_file_path)

class MlnxOfedDriverLinux(MlnxDriverLinux):

    KNOWN_DRIVER_SCRIPTS = ["/etc/init.d/mlnx-en.d", "/etc/init.d/openibd"]

    def __init__(self, logger, driverStatus):
        logger.info('MlnxOfedDriverLinux object created')
        self._driverScript = None
        for driverScript in MlnxOfedDriverLinux.KNOWN_DRIVER_SCRIPTS:
            if os.path.exists(driverScript):
                self._driverScript = driverScript
        super(MlnxOfedDriverLinux, self).__init__(logger, driverStatus)

    def driverStart(self):
        self.logger.info('MlnxOfedDriverLinux driverStart()')
        if self._driverScript == None:
            raise NoDriver("No Driver found.")
        cmd = self._driverScript + " start"
        self.logger.info('cmd {0}'.format(cmd))
        (rc, _, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to Start Driver, please start driver manually to load FW")
        return

    def driverStop(self):
        self.logger.info('MlnxOfedDriverLinux driverStop()')
        if self._driverScript == None:
            raise NoDriver("No Driver found.")
        cmd = self._driverScript + " stop"
        self.logger.info('cmd {0}'.format(cmd))
        (rc, _, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to Stop Driver, please stop driver manually and resume Operation")
        return




class MlnxInboxDriverLinux(MlnxDriverLinux):
    def isModuleLoaded(self, m):
        cmd = "lsmod"
        (rc, out, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to run lsmod")
        return m in out

    def __init__(self, logger, driverStatus):
        logger.info('MlnxInboxDriverLinux object created')
        self.isCoreLoaded = self.isModuleLoaded("mlx5_core")
        self.isIBLoaded = self.isModuleLoaded("mlx5_ib")
        self.isAccellToolsLoaded = self.isModuleLoaded(
            "mlx_accel_tools")  # Only for temporary backward comp. Should be removed in the future
        self.isAccellCoreLoaded = self.isModuleLoaded(
            "mlx_accel_core")  # Only for temporary backward comp. Should be removed in the future
        self.isFpgaToolsLoaded = self.isModuleLoaded("mlx5_fpga_tools")
        super(MlnxInboxDriverLinux, self).__init__(logger, driverStatus)

    def loadViaModeProbe(self, moduleName):
        cmd = "modprobe " + moduleName
        (rc, _, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to Start Driver(" + cmd + "), please start driver manually to load FW")
        return

    def stopViaModeProbe(self, moduleName):
        cmd = "modprobe -r " + moduleName
        (rc, _, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to Stop Driver(" + cmd + "), please stop driver manually and resume Operation")
        return

    def driverStart(self):
        self.logger.info('MlnxInboxDriverLinux driverStart()')
        if self.isCoreLoaded:
            self.loadViaModeProbe("mlx5_core")
        if self.isIBLoaded:
            self.loadViaModeProbe("mlx5_ib")
        if self.isAccellToolsLoaded or self.isAccellCoreLoaded:
            self.loadViaModeProbe("mlx_accel_tools")  # accel_core is loaded by accel_tools
        if self.isFpgaToolsLoaded:
            self.loadViaModeProbe("mlx5_fpga_tools")
        return

    def driverStop(self):
        self.logger.info('MlnxInboxDriverLinux driverStop()')
        if self.isFpgaToolsLoaded and self.isModuleLoaded("mlx5_fpga_tools"):
            self.stopViaModeProbe("mlx5_fpga_tools")
        if self.isAccellToolsLoaded and self.isModuleLoaded("mlx_accel_tools"):
            self.stopViaModeProbe("mlx_accel_tools")
        if self.isAccellCoreLoaded and self.isModuleLoaded("mlx_accel_core"):
            self.stopViaModeProbe("mlx_accel_core")
        if self.isIBLoaded and self.isModuleLoaded("mlx5_ib"):
            self.stopViaModeProbe("mlx5_ib")
        if self.isCoreLoaded and self.isModuleLoaded("mlx5_core"):
            self.stopViaModeProbe("mlx5_core")
        return


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


class MlnxDriverWindows(MlnxDriver):
    def __init__(self, logger, skip, device):
        logger.info('MlnxDriverWindows object created')
        if skip == True:
            super(MlnxDriverWindows, self).__init__(MlnxDriver.DRIVER_IGNORE)
            return

        deviceBus = int((mlxfwreset_utils.getDevDBDF(device,logger)).split(":")[0], 16)

        self.targetedAdapters = []
        targetedAdaptersTemp = []
        cmd = 'powershell.exe "Get-NetAdapterHardwareInfo | Format-List -Property Bus,Name'
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to get Adapters Hardware Information")
        lines = out.split('\n')
        for idx, line in enumerate(lines):
            if "Bus" in line:
                if (int(line.split(':')[1]) == deviceBus):
                    targetedAdaptersTemp.append(lines[idx + 1].split(':')[1].strip())

        # check status of the adapter
        for targetedAdapter in targetedAdaptersTemp:
            cmd = 'powershell.exe "Get-NetAdapter \'%s\' | Format-List -Property Status' % targetedAdapter
            (rc, out, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to get Adapter '%s' Information" % targetedAdapter)
            if ("Disabled" not in out):
                self.targetedAdapters.append(targetedAdapter)
        driverStatus = MlnxDriver.DRIVER_LOADED if (len(self.targetedAdapters) > 0) else MlnxDriver.DRIVER_IGNORE
        super(MlnxDriverWindows, self).__init__(logger, driverStatus)
        return

    def driverStart(self):
        self.logger.info('MlnxDriverWindows driverStart()')
        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe Enable-NetAdapter '%s' " % targetedAdapter
            (rc, stdout, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to Start Driver, please start driver manually to load FW")
        return

    def driverStop(self):
        self.logger.info('MlnxDriverWindows driverStop()')
        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe Disable-NetAdapter '%s' -confirm:$false" % targetedAdapter
            (rc, stdout, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to Stop Driver, please stop driver manually and resume Operation")
        return

class MlnxDriverFactory(object):
    def getDriverObj(self,logger, skip, device):
        operatingSystem = platform.system()
        if operatingSystem == "Linux":
            if skip:
                return MlnxInboxDriverLinux(logger, MlnxDriver.DRIVER_IGNORE)
            else:
                cmd = "lsmod"
                (rc, out, _) = cmdExec(cmd)
                if rc != 0:
                    raise DriverUnknownMode("Can not run the command: %s" % cmd)
                if "mlx5_core" not in out: # driver is not loaded (driver stopped)
                    return MlnxInboxDriverLinux(logger, MlnxDriver.DRIVER_IGNORE)
                cmd = "modinfo mlx5_core 2>/dev/null | grep \"filename\" | cut -d ':' -f 2` 2>/dev/null`"
                (rc, out, _) = cmdExec(cmd)
                if rc != 0:
                    raise DriverUnknownMode("Can not run the command: %s" % cmd )
                if (("extra" in out) or ("updates" in out)) and (os.path.exists("/etc/init.d/openibd") or os.path.exists("/etc/init.d/mlnx-en.d")):
                    return MlnxOfedDriverLinux(logger, MlnxDriver.DRIVER_LOADED)
                else:
                    return MlnxInboxDriverLinux(logger, MlnxDriver.DRIVER_LOADED)
        elif operatingSystem == "FreeBSD":
            return MlnxDriverFreeBSD(logger, skip)
        elif operatingSystem == "Windows":
            return MlnxDriverWindows(logger, skip, device)
        else:
            raise RuntimeError("Unsupported OS: %s" % operatingSystem)
