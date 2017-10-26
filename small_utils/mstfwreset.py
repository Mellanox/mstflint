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

from __future__ import print_function

"""
* $Id           : mlxfwreset.py 2014-06-25
* $Authors      : Adrian Chiris (adrianc@mellanox.com)
* $Tool         : Main file.
"""

__version__ = '1.0'

# Python Imports ######################
try:
    import sys
    import argparse
    import textwrap
    import subprocess
    import os
    import platform
    import re
    import time
    import signal
    import abc
    import mtcr
    import regaccess
    import tools_version
    import dev_mgt
    import cmdif
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)

# Constants ###########################
MLNX_DEVICES = [
               dict(name="ConnectX2", devid=0x190, revid=0xb0),
               dict(name="ConnectX3Pro", devid=0x1f7, revid=None),
               dict(name="ConnectIB", devid=0x1ff, revid=None),
               dict(name="ConnectX4", devid=0x209, revid=None),
               dict(name="ConnectX4LX", devid=0x20b, revid=None),
               dict(name="ConnectX5", devid=0x20d, revid=None),
               dict(name="BlueField", devid=0x211, revid=None),
               dict(name="ConnectX3", devid=0x1f5, revid=None),
               dict(name="SwitchX", devid=0x245, revid=None),
               dict(name="IS4", devid=0x1b3, revid=None),
               ]

# Supported devices.
SUPP_DEVICES = ["ConnectIB", "ConnectX4", "ConnectX4LX", "ConnectX5", "BlueField"]
SUPP_OS = ["FreeBSD", "Linux", "Windows"]

DESCRIPTION = textwrap.dedent('''\
Mlxfwreset : Tool which provides the following functionality:
    1. Query device for reset level required in order to load new firmware
    2. Perform reset operation in order to load new firmware
''')
EPILOG = textwrap.dedent('''\
Reset levels:
    0: Full ISFU.
    1: Driver restart (link/managment will remain up).
    2: Driver restart (link/managment will be down).
    3: Driver restart and PCI reset.
    4: Warm reboot.
    5: Cold reboot (performed by the user).

Supported Devices:''') + "\n    " + ", ".join(SUPP_DEVICES) + ".\n"

PROG = 'mlxfwreset'
TOOL_VERSION = "1.0.0"

# Adresses    [Base    offset  length]
DEVID_ADDR = [0xf0014, 0     , 16   ]
REVID_ADDR = [0xf0014, 16    , 8    ]

COMMAND_ADDR = 0x4
IS_MSTFLINT = "mstfwreset" in __file__
MCRA = 'mcra'
if IS_MSTFLINT:
    MCRA = "mstmcra"
# Reset Level Constants
RL_ISFU = 0
RL_DR_LNK_UP = 1
RL_DR_LNK_DN = 2
RL_PCI_RESET = 3
RL_WARM_REBOOT = 4
RL_COLD_REBOOT = 5
# Driver status constants
DRIVER_IGNORE = 0
DRIVER_LOADED = 1
# Knwon driver scripts locations
KNOWN_DRIVER_SCRIPTS = ["/etc/init.d/mlnx-en.d", "/etc/init.d/openibd"]

# reset lines as displayed in query. index i has i'th reset level str
RESET_LINES = ["Full ISFU",
               "Driver restart (link/management will remain up)",
               "Driver restart (link/management will be down)",
               "Driver restart and PCI reset ",
               "Warm Reboot",
               "Cold Reboot"]

#sync constants:
SYNC_TYPE_FW_RESET   = 0x1
SYNC_STATE_IDLE      = 0x0
SYNC_STATE_GET_READY = 0x1
SYNC_STATE_GO        = 0x2
SYNC_STATE_DONE      = 0x3

# reg access Object
RegAccessObj = None
# mst device object
MstDevObj = None
MstFlags = ""
# Pci device Obj
PciOpsObj = None

DevDBDF = None
# icmd object
CmdifObj = None
# FirmwareResetStatusChecker object
FWResetStatusChecker = None

# Global options
SkipMstRestart = False
ResetMultihostReg = False
SkipMultihostSync = False

pciModuleName      = "mst_ppc_pci_reset.ko"
pathToPciModuleDir = "/etc/mft/mlxfwreset"

RESET_MULTIHOST_REGISTER_FLAG = "--reset_fsm_register"

######################################################################
# Description:  NoError Exception
# OS Support :  Linux/Windows.
######################################################################
class NoError(Exception):
    pass

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
# Description:  Signal handler
# OS Support :  Linux/Windows.
######################################################################

def sigHndl(signal, frame):
    print("\nSignal %d Recieved, Exiting..." % signal)
    sys.exit(1)

######################################################################
# Description:  Execute command and get (rc, stdout-output, stderr-output)
# OS Support :  Linux/Windows.
######################################################################

def cmdExec(cmd):
    p = subprocess.Popen(cmd,
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE,
                         universal_newlines=False,
                         shell=True)
    output = p.communicate()
    stat = p.wait()
    return (stat, output[0], output[1])  # RC, Stdout, Stderr

######################################################################
# Description:  Check if the given module is loaded
# OS Support :  Linux.
######################################################################

def isModuleLoaded(moduleName):
    cmd = "lsmod"
    (rc, out, _) = cmdExec(cmd)
    if rc:
        raise RuntimeError("Failed to run lsmod")
    if moduleName in out:
        return True
    return False

######################################################################
# Description:  print str to stdout and flush stdout.
#               use when txt needs to appear immediately on screen
# OS Support :  Linux/Windows.
######################################################################
def printAndFlush(str, endChar='\n'):
    print(str, end=endChar)
    sys.stdout.flush()

######################################################################
# Description:  ask user Y/N question if N/n/No/no was recieved raise
#                RuntimeError.
# OS Support :  Linux/Windows.
######################################################################

def AskUser(question, autoYes=False):
    qStr = question + "?[y/N] "
    if autoYes :
        print(qStr + "y")
        return
    ans = raw_input(qStr)
    if ans.lower() in ['y', "yes"] :
        return
    raise RuntimeError("Aborted by user")

######################################################################
# Description:  Mcra Read/Write functions
# OS Support :  Linux/Windows.
######################################################################

def mcraRead(device, addr, offset, length):
    cmd = "%s %s %s.%s:%s" % (MCRA, device, addr, offset, length)
    (rc, stdout, stderr) = cmdExec(cmd)
    if rc:
        raise RuntimeError (str(stderr))
    return int(stdout, 16)

def mcraWrite(device, addr, offset, length, value):
    cmd = "%s %s %s.%s:%s %s" % (MCRA, device, addr, offset, length, value)
    (rc, _, stderr) = cmdExec(cmd)
    if rc:
        raise RuntimeError (str(stderr))

######################################################################
# Description:  FirmwareResetStatusChecker
# OS Support :  Linux/Windows.
######################################################################
class FirmwareResetStatusChecker(object):

    FirmwareUptimeStatusInit = 0x0
    FirmwareUptimeStatusBeforeDone = 0x1
    FirmwareUptimeStatusAfterDone = 0x2
    FirmwareUptimeStatusError = 0x3

    FirmwareResetStatusDone = 0x0
    FirmwareResetStatusFailed = 0x1
    FirmwareResetStatusUnknown = 0x2

    def __init__(self, regAccessObj):
        self._RegAccessObj = regAccessObj
        self._UptimeBeforeReset = 0x0
        self._UptimeBeforeStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusInit
        self._UptimeAfterReset = 0x0
        self._UptimeAfterStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusInit

    def UpdateUptimeBeforeReset(self):
        try:
            self._UptimeBeforeReset = self._RegAccessObj.getFWUptime()
            self._UptimeBeforeStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusBeforeDone
        except Exception as e:
            self._UptimeBeforeStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusError

    def UpdateUptimeAfterReset(self):
        try:
            self._UptimeAfterReset = self._RegAccessObj.getFWUptime()
            self._UptimeAfterStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusAfterDone
        except Exception as e:
            self._UptimeAfterStatus = FirmwareResetStatusChecker.FirmwareUptimeStatusError

    def GetStatus(self):
        if self._UptimeBeforeStatus == FirmwareResetStatusChecker.FirmwareUptimeStatusBeforeDone and\
                        self._UptimeAfterStatus == FirmwareResetStatusChecker.FirmwareUptimeStatusAfterDone:
            if self._UptimeAfterReset < self._UptimeBeforeReset:
                return FirmwareResetStatusChecker.FirmwareResetStatusDone
            else:
                if self._UptimeBeforeReset > 5: #5 seconds
                    return FirmwareResetStatusChecker.FirmwareResetStatusFailed
                else:
                    return FirmwareResetStatusChecker.FirmwareResetStatusUnknown
        return FirmwareResetStatusChecker.FirmwareResetStatusUnknown

######################################################################
# Description:  Driver Class , use factory to get instance
# OS Support :  Linux/Windows.
######################################################################

class MlnxDriver(object):
    __metaclass__ = abc.ABCMeta
    """ Abstract driver Class that provides a simple start stop status methods
    """
    
    def __init__(self, driverStatus):
        self.driverStatus = driverStatus

    @abc.abstractmethod
    def driverStart(self):
        raise NotImplementedError("driverStart() is not implemented")

    @abc.abstractmethod
    def driverStop(self):
        raise NotImplementedError("driverStop() is not implemented")

    def getDriverStatus(self):
        return self.driverStatus

class MlnxDriverLinux(MlnxDriver):
    def __init__(self, driverStatus):
        self._driverScript = None
        for driverScript in KNOWN_DRIVER_SCRIPTS:
            if os.path.exists(driverScript):
                self._driverScript = driverScript
        super(MlnxDriverLinux, self).__init__(driverStatus)

    def driverStart(self):
        if self._driverScript == None:
            raise NoDriver("No Driver found.")
        cmd = self._driverScript + " start"
        (rc, _, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to Start Driver, please start driver manually to load FW")
        return

    def driverStop(self):
        if self._driverScript == None:
            raise NoDriver("No Driver found.")
        cmd = self._driverScript + " stop"
        (rc, _, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to Stop Driver, please stop driver manually and resume Operation")
        return

class MlnxInboxDriverLinux(MlnxDriver):
    def isModuleLoaded(self, m):
        cmd = "lsmod"
        (rc, out, _) = cmdExec(cmd)
        if rc:
            raise RuntimeError("Failed to run lsmod")
        return m in out

    def __init__(self, driverStatus):
        self.isCoreLoaded = self.isModuleLoaded("mlx5_core")
        self.isIBLoaded = self.isModuleLoaded("mlx5_ib")
        self.isAccellToolsLoaded = self.isModuleLoaded("mlx_accel_tools") # Only for temporary backward comp. Should be removed in the future
        self.isAccellCoreLoaded = self.isModuleLoaded("mlx_accel_core") # Only for temporary backward comp. Should be removed in the future
        self.isFpgaToolsLoaded = self.isModuleLoaded("mlx5_fpga_tools")
        super(MlnxInboxDriverLinux, self).__init__(driverStatus)

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
        if self.isCoreLoaded:
            self.loadViaModeProbe("mlx5_core")
        if self.isIBLoaded:
            self.loadViaModeProbe("mlx5_ib")
        if self.isAccellToolsLoaded or self.isAccellCoreLoaded:
            self.loadViaModeProbe("mlx_accel_tools") # accel_core is loaded by accel_tools
        if self.isFpgaToolsLoaded:
            self.loadViaModeProbe("mlx5_fpga_tools")
        return

    def driverStop(self):
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
    def __init__(self, skip):
        if skip == True:
            self.driverStatus = DRIVER_IGNORE
            return
        self._knownModules = [("mlx5en", False), ("mlx5ib", False), ("mlx4ib", False), ("mlxen", False), ("mlx5", False)]
        # check whats loaded
        for i in range(0, len(self._knownModules)):
            cmd = "kldstat -n %s" % (self._knownModules[i][0])
            (rc, _, _) = cmdExec(cmd)
            if rc == 0:
                self._knownModules[i] = (self._knownModules[i][0], True)
        super(MlnxDriverFreeBSD, self).__init__(self.getDriverStatusAux())

    def driverStart(self):
        for moduleName, isPresent in self._knownModules:
            if isPresent:
                cmd = "kldload %s" % moduleName
                (rc, stdout, stderr) = cmdExec(cmd)
                if rc and not("module already loaded" in stderr):
                    raise RuntimeError("Failed to Start Driver, please start driver manually to load FW")

    def driverStop(self):
        for moduleName, isPresent in self._knownModules:
            if isPresent:
                cmd = "kldunload %s" % moduleName
                (rc, stdout, stderr) = cmdExec(cmd)
                if rc and not("can't find file" in stderr):
                    raise RuntimeError("Failed to Stop Driver, please stop driver manually and resume Operation")
    
    def getDriverStatusAux(self):
        cmd = "ls -l /boot/kernel/ | grep mlx -c"
        (rc, stdout, _) = cmdExec(cmd)
        if rc != 0:
            raise DriverUnknownMode("Can not run the command: %s" %cmd)
        # the voodoo below checks if we had at least one kernel object loaded 
        return (DRIVER_IGNORE, DRIVER_LOADED)[reduce(lambda x, y: x or y, map(lambda x : x[1], self._knownModules))]
    
class MlnxDriverWindows(MlnxDriver):
    def __init__(self, skip, device):
        if skip == True:
            super(MlnxDriverWindows, self).__init__(DRIVER_IGNORE)
            return

        deviceBus = int((getDevDBDF(device)).split(":")[0], 16)

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

        #check status of the adapter
        for targetedAdapter in targetedAdaptersTemp:
            cmd = 'powershell.exe "Get-NetAdapter \'%s\' | Format-List -Property Status' % targetedAdapter
            (rc, out, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to get Adapter '%s' Information" % targetedAdapter)
            if ("Disabled" not in out):
                self.targetedAdapters.append(targetedAdapter)
        driverStatus = DRIVER_LOADED if (len(self.targetedAdapters) > 0) else DRIVER_IGNORE
        super(MlnxDriverWindows, self).__init__(driverStatus)
        return

    def driverStart(self):
        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe Enable-NetAdapter '%s' " % targetedAdapter
            (rc, stdout, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to Start Driver, please start driver manually to load FW")
        return

    def driverStop(self):
        for targetedAdapter in self.targetedAdapters:
            cmd = "powershell.exe Disable-NetAdapter '%s' -confirm:$false" % targetedAdapter
            (rc, stdout, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("Failed to Stop Driver, please stop driver manually and resume Operation")
        return

class MlnxDriverFactory(object):
    def getDriverObj(self, skip, device):
        operatingSystem = platform.system()
        if operatingSystem == "Linux":
            if skip:
                return MlnxInboxDriverLinux(DRIVER_IGNORE)
            else:
                cmd = "lsmod"
                (rc, out, _) = cmdExec(cmd)
                if rc != 0:
                    raise DriverUnknownMode("Can not run the command: %s" % cmd)
                if "mlx5_core" not in out:
                    return MlnxInboxDriverLinux(DRIVER_IGNORE)
                cmd = "modinfo mlx5_core 2>/dev/null | grep \"filename\" | cut -d ':' -f 2` 2>/dev/null`"
                (rc, out, _) = cmdExec(cmd)
                if rc != 0:
                    raise DriverUnknownMode("Can not run the command: %s" % cmd )
                if (("extra" in out) or ("updates" in out)) and (os.path.exists("/etc/init.d/openibd") or os.path.exists("/etc/init.d/mlnx-en.d")):
                    return MlnxDriverLinux(DRIVER_LOADED)
                else:
                    return MlnxInboxDriverLinux(DRIVER_LOADED)
        elif operatingSystem == "FreeBSD":
            return MlnxDriverFreeBSD(skip)
        elif operatingSystem == "Windows":
            return MlnxDriverWindows(skip, device)
        else:
            raise RuntimeError("Unsupported OS: %s" % operatingSystem)

######################################################################
# Description:  MlnxPciOperation class
# OS Support :  Linux/FreeBSD.
######################################################################
class MlnxPciOp(object):
    """ Abstract Class that provides a unified way to perform pci operations
    """
    def __init__(self):
        self.bridgeAddr=None
    def read(self, devAddr, addr, width = "L"):
        raise NotImplementedError("read() is not implemented")
    def write(self, devAddr, addr, val, width = "L"):
        raise NotImplementedError("write() is not implemented")
    def getPciBridgeAddr(self, devAddr):
        raise NotImplementedError("getPciBridgeAddr() is not implemented")
    def getPcieCapAddr(self, bridgeDev):
        raise NotImplementedError("getPcieCapAddr() is not implemented")
    def getMFDeviceList(self, mstDev):
        raise NotImplementedError("getMFDeviceList() is not implemented")
    def savePCIConfigurationSpace(self, devAddr):
        raise NotImplementedError("savePCIConfigurationSpace() is not implemented")
    def loadPCIConfigurationSpace(self, devAddr):
        raise NotImplementedError("savePCIConfigurationSpace() is not implemented")
    def setPciBridgeAddr(self, bridgeAddr):
        self.bridgeAddr = bridgeAddr

class MlnxPciOpLinux(MlnxPciOp):
    
    def __init__(self):
        super(MlnxPciOpLinux, self).__init__()

    def read(self, devAddr, addr, width = "L"):
        cmd = "setpci -s %s 0x%x.%s" % (devAddr, addr, width)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to read address 0x%x from device %s " % (addr, devAddr))
        return int(out, 16)

    def write(self, devAddr, addr, val, width = "L"):
        cmd = "setpci -s %s 0x%x.%s=0x%x" % (devAddr, addr, width, val)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to write 0x%x to address 0x%x to device %s " % (val, addr, devAddr))
        return

    def getPciBridgeAddr(self, devAddr):
        if self.bridgeAddr : # user specified the bridge address
            return self.bridgeAddr
        devAddr = addDomainToAddress(devAddr)
        cmd = r'readlink /sys/bus/pci/devices/%s | sed -e "s/.*\/\([0-9a-f:.]*\)\/%s/\1/g"' % (devAddr, devAddr)
        (rc, bridgeDev, _) = cmdExec(cmd)
        if rc != 0 or len(bridgeDev.strip()) == 0:
            raise RuntimeError("failed to get Bridge Device for the given PCI device")
        return bridgeDev.strip()

    def getPciECapAddr(self, bridgeDev):
        cmd = "lspci -s %s -v | grep 'Capabilities: \[.*\] Express' | sed -e 's/.*\[\([0-9,a-f].*\)\].*/\\1/g'" % bridgeDev
        (rc, capAddr, _) = cmdExec(cmd)
        if rc != 0 or len(capAddr.strip()) == 0:
            raise RuntimeError("Failed to find PCI bridge Pci Express Capability")
        return int(capAddr, 16)
    
    def getMFDeviceList(self, mstDev):
        global DevDBDF
        devAddr = DevDBDF
        domainBus = ":".join(devAddr.split(":")[:2])
        MFDevices = []
        cmd = "lspci -d 15b3: -D | grep %s | cut -d' ' -f1" %domainBus
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("failed to execute: %s" %cmd)
        out = out.strip().split('\n')
        for dev in out:
            MFDevices.append(dev)
        return MFDevices
    
    def savePCIConfigurationSpace(self, devAddr):
        global IS_MSTFLINT
        if IS_MSTFLINT:
            return 1
        if devAddr.startswith("0000:"):
            devAddr = removeDomainFromAddress(devAddr)
        cmd = "mst save %s" %devAddr
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("failed to execute: %s" %cmd)
        return
    
    def loadPCIConfigurationSpace(self, devAddr):
        global IS_MSTFLINT
        if IS_MSTFLINT:
            return 1
        if devAddr.startswith("0000:"):
            devAddr = removeDomainFromAddress(devAddr)
        cmd = "mst load %s" %devAddr
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("failed to execute: %s" %cmd)
        return


class MlnxPciOpLinuxUl(MlnxPciOpLinux):
    def __init__(self):
        super(MlnxPciOpLinuxUl, self).__init__()
        self.pciConfSpaceMap = {}
        
    def savePCIConfigurationSpace(self, devAddr):
        confSpaceList = []
        for addr in range(0, 0xff, 4):
            if (addr == 0x58 or addr == 0x5c):
                confSpaceList.append(0)
                continue
            val = self.read(devAddr, addr)
            confSpaceList.append(val)
        self.pciConfSpaceMap[devAddr] = confSpaceList
        return

    def loadPCIConfigurationSpace(self, devAddr):
        pciConfSpaceList = []
        try:
            pciConfSpaceList = self.pciConfSpaceMap[devAddr]
        except KeyError as ke:
            raise RuntimeError("PCI configuration space for device %s was not saved please reboot server" % devAddr)
        if len(pciConfSpaceList) != 64:
            raise RuntimeError("PCI configuration space for device %s was not saved properly please reboot server" % devAddr)
        for i in range(0, 64):
            addr = i * 4
            if (addr == 0x58 or addr == 0x5c):
                continue
            self.write(devAddr, addr, pciConfSpaceList[i])
        return
    
class MlnxPciOpFreeBSD(MlnxPciOp):

    def __init__(self):
        super(MlnxPciOpFreeBSD, self).__init__()
        self.pciConfSpaceMap = {}

    def read(self, devAddr, addr, width = "L"):
        if not(devAddr.startswith("pci")):
            devAddr = "pci" + devAddr
        cmd = "pciconf -r %s 0x%x" % (devAddr, addr)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to read address 0x%x from device %s " % (addr, devAddr))
        return int(out, 16)

    def write(self, devAddr, addr, val, width = "L"):
        if not(devAddr.startswith("pci")):
            devAddr = "pci" + devAddr
        cmd = "pciconf -w %s 0x%x 0x%x" % (devAddr, addr, val)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to write 0x%x to address 0x%x to device %s " % (val, addr, devAddr))
        return

    def getPciBridgeAddr(self, devAddr):
        if self.bridgeAddr : # user specified bridge addr
            return self.bridgeAddr
        if re.match("^\d+\:\d+\:\d+\:\d+$", devAddr) == None:
            raise RuntimeError("Illegal format for the device PCI address: %s" % devAddr)
        busNum = devAddr.split(":")[1]
        cmd = "sysctl -a | grep \"secbus: %s\"" % busNum
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to execute the command: %s" %cmd)
        linesCount = len(out.splitlines())
        if(linesCount == 0):
            raise RuntimeError("There is no secbus with the value: %s" %busNum)
        if(linesCount > 1):
            raise RuntimeError("Found more than one secbus with the value: %s" %busNum)
        hostBridge = "pcib%s" %(out.split("pcib.")[1].split(".")[0])
        # get pci address of hostBridge
        cmd = "pciconf -l | grep %s | cut -f 1 | cut -f 2 -d@ | sed -e 's/\(.*\):\s*/\\1/g'" % hostBridge
        (rc, bridgeDevAddr, _) = cmdExec(cmd)
        if rc != 0 or len(bridgeDevAddr.strip()) == 0:
            raise RuntimeError("Failed to extract pci bridge address")
        return bridgeDevAddr.strip()

    def getPciECapAddr(self, bridgeDev):
        cmd = "pciconf -lc %s | grep \"cap 10\" | sed -e 's/.*\[\([0-9,a-f]*\)\].*/\\1/g'" % bridgeDev
        (rc, capAddr, _) = cmdExec(cmd)
        if rc != 0 or len(capAddr.strip()) == 0:
            raise RuntimeError("Failed to find PCI bridge Pci Express Capability")
        return int(capAddr, 16)
    
    def getMFDeviceList(self, mstDev):
        global DevDBDF
        MFDevices = []
        devAddr = DevDBDF
        domainBus = ":".join(devAddr.split(":")[:-2])
        domainBus = "pci" + domainBus
        cmd = "pciconf -l | grep 'chip=0x[0-9,a-f]\{4\}15b3 ' | grep %s | cut -f1 | cut -d@ -f2" %domainBus
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("failed to get execure: %s" %cmd)
        out = out.strip().split('\n')
        for dev in out:
            MFDevices.append(dev[:-1])
        return MFDevices
    
    def savePCIConfigurationSpace(self, devAddr):
        confSpaceList = []
        for addr in range(0, 0xff, 4):
            if (addr == 0x58 or addr == 0x5c):
                confSpaceList.append(0)
                continue
            val = self.read(devAddr, addr)
            confSpaceList.append(val)
        self.pciConfSpaceMap[devAddr] = confSpaceList
        return

    def loadPCIConfigurationSpace(self, devAddr):
        pciConfSpaceList = []
        try:
            pciConfSpaceList = self.pciConfSpaceMap[devAddr]
        except KeyError as ke:
            raise RuntimeError("PCI configuration space for device %s was not saved please reboot server" % devAddr)
        if len(pciConfSpaceList) != 64:
            raise RuntimeError("PCI configuration space for device %s was not saved properly please reboot server" % devAddr)
        for i in range(0, 64):
            addr = i * 4
            if (addr == 0x58 or addr == 0x5c):
                continue
            self.write(devAddr, addr, pciConfSpaceList[i])
        return

class MlnxPciOpWindows(MlnxPciOp):

    def __init__(self):
        super(MlnxPciOpWindows, self).__init__()
        self.lspciPath = os.path.join("c:", "pciutils-3.3.0", "lspci")
        self.setPciPath = os.path.join("c:", "pciutils-3.3.0", "setpci")

    def read(self, devAddr, addr, width = "L"):
        cmd = self.setPciPath + " -s %s 0x%x.%s" % (devAddr, addr, width)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to read address 0x%x from device %s " % (addr, devAddr))
        return int(out, 16)

    def write(self, devAddr, addr, val, width = "L"):
        cmd = self.setPciPath + " -s %s 0x%x.%s=0x%x" % (devAddr, addr, width, val)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to write 0x%x to address 0x%x to device %s " % (val, addr, devAddr))
        return

    def getPciBridgeAddr(self, devAddr):
        # cmd = self.lspciPath + " -tv"
        raise NotImplementedError("getPciBridgeAddr() not implemented for windows")

    def getPciECapAddr(self, bridgeDev):
        raise NotImplementedError("getPciECapAddr() not implemented for windows")

    def savePCIConfigurationSpace(self, devAddr):
        raise NotImplementedError("savePCIConfigurationSpace() not implemented for windows")
    
    def loadPCIConfigurationSpace(self, devAddr):
        raise NotImplementedError("loadPCIConfigurationSpace() not implemented for windows")


class MlnxPciOpFactory(object):
    def getPciOpObj(self):
        global IS_MSTFLINT
        operatingSystem = platform.system()
        if operatingSystem == "Linux":
            if IS_MSTFLINT:
                return MlnxPciOpLinuxUl()
            return MlnxPciOpLinux()
        elif operatingSystem == "FreeBSD":
            return MlnxPciOpFreeBSD()
        elif operatingSystem == "Windows":
            return MlnxPciOpWindows()
        else:
            raise RuntimeError("Unsupported OS: %s" % operatingSystem)

######################################################################
# Description:  Perform mst restart
# OS Support :  Linux.
######################################################################

def mstRestart(busId):
    global MstFlags
    if platform.system() == "FreeBSD" or platform.system() == "Windows":
        return 1
    # poll till module ref count is zero before restarting
    cmd = "lsmod"
    for _ in range(0, 30):
        (rc, stdout, _) = cmdExec(cmd)
        if rc != 0:
            raise NoError("Failed to get the status of the mst module (RC=%d), please restart MST manually" % rc)
        matchedLines = [line for line in stdout.split('\n') if "mst_pciconf" in line]
        if len(matchedLines) == 0:
            return 1
        if matchedLines[0].split()[-1] == '0':
            break
        else :
            time.sleep(2)

    cmd = "lspci -s %s" % busId
    foundBus = False
    rc = 0
    for _ in range(0, 30):
        (rc, stdout, _) = cmdExec(cmd)
        if rc == 0 and stdout != "":
            foundBus = True
            break
        else :
            time.sleep(2)
    if rc != 0:
        raise NoError("Failed to run lspci command (RC=%d), please restart MST manually" % rc)
    if foundBus == False:
        raise RuntimeError("The device is not appearing in lspci output!")

    cmd = "/etc/init.d/mst restart %s" % MstFlags
    (rc, stdout, _) = cmdExec(cmd)
    if rc != 0:
        raise NoError("Failed to restart MST (RC=%d), please restart MST manually" % rc)
    return 0

######################################################################
# Description:  Get Device ID / Device Rev-ID
# OS Support :  Linux/Windows.
######################################################################

getDevidFromDevice = lambda device: mcraRead(device, DEVID_ADDR[0], DEVID_ADDR[1], DEVID_ADDR[2])
getRevidFromDevice = lambda device: mcraRead(device, REVID_ADDR[0], REVID_ADDR[1], REVID_ADDR[2])


######################################################################
# Description:  DBDF string manipulation
# OS Support :  N/A
######################################################################

def getDomain(devAddr):
    devAddr = devAddr.split(":")
    if len(devAddr) == 3 :
        return devAddr[0]
    return None

def addDomainToAddress(devAddr):
    if len(devAddr.split(":")) == 2 :
        return "0000:" + devAddr
    return devAddr

def removeDomainFromAddress(devAddr):
    if len(devAddr.split(":")) == 3 :
        return devAddr[5:]
    return devAddr

def isDevDBDFFormat(dev):
    pat=r"[0-9,A-F,a-f]{4}:[0-9,A-F,a-f]{2}:[0-9,A-F,a-f]{2}\.[0-9,A-F,a-f]{1,2}"
    if re.match(pat, dev):
        return True
    return False

def isDevBDFFormat(dev):
    pat=r"[0-9,A-F,a-f]{2}:[0-9,A-F,a-f]{2}\.[0-9,A-F,a-f]{1,2}"
    if re.match(pat, dev):
        return True
    return False

def isDevDBDFFormatFBSD(dev):
    pat=r"[0-9,A-F,a-f]{1,4}:[0-9,A-F,a-f]{1,2}:[0-9,A-F,a-f]{1,2}:[0-9,A-F,a-f]{1,2}"
    if re.match(pat, dev):
        return True
    return False
######################################################################
# Description:  get device DBDF format
# OS Support :  Linux/Windows.
######################################################################

def getDevDBDF(device):
    if isDevDBDFFormat(device):
        return device
    if isDevBDFFormat(device):
        return addDomainToAddress(device)

    operatingSys = platform.system()
    if (operatingSys == "FreeBSD") :
        if isDevDBDFFormatFBSD(device):
            return device
        if not(device.startswith("pci")):
            raise RuntimeError("Unexpected device name format")
        return device[3:]
    elif (operatingSys == "Linux"):
        cmd = "mdevices_info -vv"
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("Failed to get device PCI address")
        # extract bdf
        bdf = None
        for line in out.split('\n'):
            if device in line:
                if len(line.split()) > 2:
                    bdf = line.split()[2]
        if not bdf:
            raise RuntimeError("Failed to get device PCI Address")
        return addDomainToAddress(bdf)
    elif (operatingSys == "Windows"):
        cmd = "mdevices status -v"
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("Failed to get device PCI address")
        # extract bdf
        bdf = None
        for line in out.split('\n'):
            l = line.split()
            if (len(l) > 1) and (device in l[0]) and ("bus:dev.fn" in l[1]):
                bdf = line.split('=')[1]
        if not bdf:
            raise RuntimeError("Failed to get device PCI Address")
        return bdf
    else:
        raise RuntimeError("Unsupported OS")

######################################################################
# Description:  Check if device is supported
# OS Support :  Linux/Windows.
######################################################################

def isDevSupp(device):
    try:
        devid = getDevidFromDevice(device)
    except Exception as e:
        raise RuntimeError("Failed to Identify Device: %s, %s" % (device, str(e)))
    for devDict in MLNX_DEVICES:
        if devDict["devid"] == devid:
            if devDict["name"] in SUPP_DEVICES :
                return
            else:
                raise RuntimeError("Unsupported Device: %s (%s)" % (device, devDict["name"]))
    raise RuntimeError("Failed to Identify Device: %s" % (device))

######################################################################
# Description: Get All PCI Module Paths
# OS Support : Linux
######################################################################

def getAllPciModulePaths():
    global pciModuleName
    global pathToPciModuleDir
    paths = []
    for f in os.listdir(pathToPciModuleDir):
        if os.path.isdir(os.path.join(pathToPciModuleDir, f)) == True:
            p = os.path.join(pathToPciModuleDir, f, pciModuleName)
            if os.path.isfile(p) == True:
                paths.append(p)
    return paths

######################################################################
# Description: Get PCI Module Path
# OS Support : Linux
######################################################################

def getPciModulePath():
    global pciModuleName
    global pathToPciModuleDir
    cmd = "uname -r"
    (rc, unameOutput, _) = cmdExec(cmd)
    if rc != 0 :
        return (False, getAllPciModulePaths())
    pathToModule = os.path.join(pathToPciModuleDir, unameOutput.strip(), pciModuleName)
    if os.path.isfile(pathToModule) == True:
        return (True, pathToModule)
    else:
        return (False, getAllPciModulePaths())

######################################################################
# Description: Run PPC Pci Reset Module
# OS Support: Linux
#####################################################################

def runPPCPciResetModule(path, busId):
    cmd = "insmod %s pci_dev=%s" % (path, busId)
    (rc, out, err) = cmdExec(cmd)
    if rc != 0 :
        #check if failure is related to SELinux
        if "Permission denied" in err:
            chconCmd = "chcon -t modules_object_t %s" % path
            (rc, out, err) = cmdExec(chconCmd)
            if rc != 0:
                return (False, err)
            (rc, out, err) = cmdExec(cmd)
            if rc != 0:
                return (False, err)
    return (True, "")

######################################################################
# Description:  reset PCI of a certain device for PPC setup (special flow)
# OS Support : Linux
######################################################################

def resetPciAddrPPC(busId):
    global pciModuleName
    global FWResetStatusChecker
    # check supported system
    if platform.system() != "Linux":
        raise RuntimeError("Unsupported OS(%s) for PPC reset flow" % (platform.system()) )
    if isModuleLoaded("mst_ppc_pci_reset") == True:
        cmd = "rmmod mst_ppc_pci_reset"
        (rc, out, _) = cmdExec(cmd)
    if isModuleLoaded("mst_ppc_pci_reset") == True:
        raise RuntimeError("Failed to unload mst_ppc_pci_reset module. please unload it manually and try again.")

    (foundModule, path) = getPciModulePath()
    if foundModule == True:
        (res, err) = runPPCPciResetModule(path, busId)
        if res == False:
            raise RuntimeError("Failed to load pci reset module, make sure kernel-mft is installed properly: %s" % err)
    else:
        foundWorkingModule = False
        for p in path:
            (res, err) = runPPCPciResetModule(path, busId)
            if res == True:
                foundWorkingModule = True
                break
        if foundWorkingModule == False:
            raise RuntimeError("Can not find the module: %s" % pciModuleName)

    cmd = "rmmod mst_ppc_pci_reset"
    (rc, out, err) = cmdExec(cmd)
    if rc != 0 :
        raise RuntimeError("Failed to unload pci reset module: %s please unload the module manually" % err)
    #sleep to be on the safe side
    time.sleep(1)

    return

######################################################################
# Description:  reset PCI of a certain device for Windows setup (special flow)
# OS Support : Windows
######################################################################

def resetPciAddrWindows(busId):
    global MstDevObj
    global FWResetStatusChecker
    MstDevObj.mHcaReset()
    return

######################################################################
# Description:  reset PCI of a certain device for Linux/FBSD setup
# OS Support : Linux, FreeBSD
######################################################################

def resetPciAddrDefault(busId):
    global PciOpsObj
    global FWResetStatusChecker
    bridgeDev = PciOpsObj.getPciBridgeAddr(busId)
    # Link Control Register : PCI_EXPRESS_CAP_OFFS + 0x10
    capAddr = PciOpsObj.getPciECapAddr(bridgeDev)
    disableAddr = capAddr + 0x10
    width = "L"
    oldCapDw = PciOpsObj.read(bridgeDev, disableAddr, width)
    # turn on Link Disable bit
    newCapDw = oldCapDw | 0x10
    PciOpsObj.write(bridgeDev, disableAddr, newCapDw, width)
    time.sleep(1.25)
    # turn off Link Disable bit
    PciOpsObj.write(bridgeDev, disableAddr, oldCapDw, width)
    time.sleep(0.25)
    return

######################################################################
# Description:  reset PCI of a certain device
# OS Support : Linux, FreeBSD, Windows
######################################################################

def resetPciAddr(device):
    global DevDBDF
    # save pci conf space
    savePciConfSpace(device)

    busId = DevDBDF
    isPPC = "ppc64" in platform.machine()
    #update FWResetStatusChecker
    FWResetStatusChecker.UpdateUptimeBeforeReset()
    try:
        if platform.system() == "Windows" :
            resetPciAddrWindows(busId)
        elif isPPC:
            resetPciAddrPPC(busId)
        else:
            resetPciAddrDefault(busId)
    except Exception as e:
        raise RuntimeError("Failed To reset PCI(Driver starting will be skipped). %s" % str(e))
    # wait for FW to re-boot
    time.sleep(1)
    # restore pci conf space
    loadPciConfSpace(device)
    #update FWResetStatusChecker
    FWResetStatusChecker.UpdateUptimeAfterReset()
    return

######################################################################
# Description: Save PCI configuration space for an MST device
# OS Support : Linux, FreeBSD
######################################################################

def savePciConfSpace(mstDev):
    if platform.system() == "Windows" : # being Done in mHcaReset
        return
    global PciOpsObj
    devList = PciOpsObj.getMFDeviceList(mstDev)
    # perform mcra read of 0xf0014 to avoid locking semaphores in vsec
    mcraRead(mstDev, 0xf0014, 0, 32)
    # for each PF/VF save its configuration space
    for pciDev in devList:
        PciOpsObj.savePCIConfigurationSpace(pciDev)
    return

######################################################################
# Description: Load PCI configuration space for an MST device
# OS Support : Linux, FreeBSD
######################################################################

def loadPciConfSpace(mstDev):
    if platform.system() == "Windows" : # being Done in mHcaReset
        return
    global PciOpsObj
    devList = PciOpsObj.getMFDeviceList(mstDev)
    for pciDev in devList:
        command_reg = PciOpsObj.read(pciDev, COMMAND_ADDR, "W")
        if (command_reg & 0x2) == 0: #Second bit in command register is off
            PciOpsObj.loadPCIConfigurationSpace(pciDev)
    return

######################################################################
# Description: get minimum reset level required for device
# OS Support : Linux
######################################################################

def getResetLevel(device):
    # send mfrl register get
    level = 0
    actualLevel = 0
    try:
        actualLevel = RegAccessObj.sendMFRL(0, regaccess.REG_ACCESS_METHOD_GET)
        if actualLevel == 0:
            RuntimeError("Bad reset level Value recieved from FW. please reboot machine to load new FW.")
    except Exception as e:
        if "(265)" in str(e):
            raise NoError("Failed to get Reset level from device. this might indicate that FW was already loaded")
        raise RuntimeError("Failed to get Reset level from device. %s" % str(e))
    # return the first bit that is set (and apply reset level translation according to the reset levels defined above)
    while (actualLevel % 2 == 0):
        actualLevel = actualLevel >> 1
        level += 1
    
    if (level == 6 or level == 7):
        level -= 2
    return level

######################################################################
# Description: set reset level for device
# OS Support : Linux
######################################################################

def setResetLevel(device, level):
    # send mfrl register get
    levelmsk = 1 << level
    if (level == 4 or level == 5):
        levelmsk = levelmsk << 2  # for warm/cold reboot we need bits 6,7 to be set respectiveley
    try:
        RegAccessObj.sendMFRL(levelmsk, regaccess.REG_ACCESS_METHOD_SET)
    except Exception as e:
        raise RuntimeError("Failed to set Reset level(%d) on device. %s" % (level, str(e)))
    return

######################################################################
# Description: Full ISFU Reset Flow
# OS Support : Linux
######################################################################

def fullISFU(device, level=None, force=False):
    try:
        printAndFlush("-I- %-40s-" % ("Sending Reset Command To Fw"), endChar="")
        setResetLevel(device, 0)
        printAndFlush("Done")
    except Exception as e:
        printAndFlush("Failed")
        raise e
    return

######################################################################
# Description: Send MFRL to FW
######################################################################
def sendResetToFW(device, level, force):
    try:
        printAndFlush("-I- %-40s-" % ("Sending Reset Command To Fw"), endChar="")
        setResetLevel(device, level)
        printAndFlush("Done")
    except Exception as e:
        if force :
            printAndFlush("Failed (force flag recieved)")
        else:
            raise e

######################################################################
# Description: Send MFRL to FW in Multihost setup
######################################################################
def sendResetToFWSync(device, level, force):
    status = CmdifObj.multiHostSyncStatus()
    if (status.fsm_state == SYNC_STATE_GET_READY and
                 status.fsm_sync_type != SYNC_TYPE_FW_RESET) or\
            status.fsm_state == SYNC_STATE_GO:
        raise RuntimeError("the fsm register is busy, run reset_fsm_register command")
    elif status.fsm_state == SYNC_STATE_IDLE:
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET, 0x1)
        #WA: send again because in single host case the firmware will wait for a second call (fw bug ??)
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
        try:
            sendResetToFW(device, level, force)
        except Exception as e:
            CmdifObj.multiHostSync(SYNC_STATE_IDLE, SYNC_TYPE_FW_RESET)
            raise e
    elif status.fsm_state == SYNC_STATE_GET_READY:
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)

######################################################################
# Description: Stop Driver
######################################################################
def stopDriver(driverObj):
    if driverObj.getDriverStatus() == DRIVER_LOADED:
        printAndFlush("-I- %-40s-" % ("Stopping Driver"), endChar="")
        try:
            driverObj.driverStop()
        except Exception as e:
            #try again, that will prevent problems in multihost
            time.sleep(1)
            driverObj.driverStop()
        printAndFlush("Done")

######################################################################
# Description: Stop Driver in Multihost setup
######################################################################
def stopDriverSync(driverObj):
    status = CmdifObj.multiHostSyncStatus()
    timestamp = time.time()
    print_waiting_msg = True
    while(status.fsm_state == SYNC_STATE_GET_READY and
          status.fsm_sync_type == SYNC_TYPE_FW_RESET):
        status = CmdifObj.multiHostSyncStatus()
        diffTime = time.time() - timestamp
        if diffTime > 180:
            raise RuntimeError("fsm sync timed out")
        if print_waiting_msg and diffTime > 2:
            print("Waiting for mlxfwreset to run on all other hosts, press 'ctrl+c' to abort")
            print_waiting_msg = False
        time.sleep(0.5)

    if status.fsm_state != SYNC_STATE_GO or status.fsm_sync_type != SYNC_TYPE_FW_RESET:
        raise RuntimeError("Operation failed, the fsm register state or type is not as expected")

    stopDriver(driverObj)

    CmdifObj.multiHostSync(SYNC_STATE_GO, SYNC_TYPE_FW_RESET)
    status = CmdifObj.multiHostSyncStatus()
    timestamp = time.time()
    print_waiting_msg = True
    while status.fsm_host_ready != 0x0:
        status = CmdifObj.multiHostSyncStatus()
        if status.fsm_sync_type != SYNC_TYPE_FW_RESET or status.fsm_state != SYNC_STATE_GO:
            raise RuntimeError("Operation failed, the fsm register state or type is not as expected")
        diffTime = time.time() - timestamp
        if diffTime > 180:
            errmsg = "fsm sync timed out"
            if driverObj.getDriverStatus() == DRIVER_LOADED:
                try:
                    driverObj.driverStart()
                    errmsg = errmsg + " (driver was reloaded)"
                except Exception as e:
                    errmsg = errmsg + " (driver failed to reload: %s)" % str(e)
            raise RuntimeError(errmsg)
        if print_waiting_msg and diffTime > 2:
            print("Waiting for mlxfwreset to run on all other hosts, press 'ctrl+c' to abort")
            print_waiting_msg = False
        time.sleep(0.5)

    if status.fsm_sync_type != SYNC_TYPE_FW_RESET or status.fsm_state != SYNC_STATE_GO:
        raise RuntimeError("Operation failed, the fsm register state or type is not as expected")

######################################################################
# Description: Driver restart (link/managment up/down flow) w/wo PCI RESET
# OS Support : Linux
######################################################################
def resetFlow(device, level, force=False):
    infoStr = ""
    try:

        if SkipMultihostSync or not CmdifObj.isMultiHostSyncSupported():
            sendResetToFW(device, level, force)
        else:
            sendResetToFWSync(device, level, force)

        # stop driver
        try:
            driverObj = MlnxDriverFactory().getDriverObj(skipDriver, device)
            driverStat = driverObj.getDriverStatus()
        except DriverUnknownMode as e:
            print("-E- Failed to get the driver status: %s" % str(e))
            print("-E- Please make sure the driver is down, and re-run the tool with --skipDriver")
            raise e

        if SkipMultihostSync or not CmdifObj.isMultiHostSyncSupported():
            stopDriver(driverObj)
        else:
            stopDriverSync(driverObj)

        if level == RL_PCI_RESET:
            # reset PCI
            printAndFlush("-I- %-40s-" % ("Resetting PCI"), endChar="")
            resetPciAddr(device)
            printAndFlush("Done")

        if driverStat == DRIVER_LOADED:
            printAndFlush("-I- %-40s-" % ("Starting Driver"), endChar="")
            driverObj.driverStart()
            printAndFlush("Done")

        # we close MstDevObj to allow a clean operation of mst restart
        MstDevObj.close()
        global SkipMstRestart
        global DevDBDF
        if SkipMstRestart == False:
            printAndFlush("-I- %-40s-" % ("Restarting MST"), endChar="")
            if mstRestart(DevDBDF) == 0:
                printAndFlush("Done")
            else:
                printAndFlush("Skipped")
    except Exception as e:
        printAndFlush("Failed")
        raise e
    return

######################################################################
# Description: reboot common reset flow
# OS Support : Linux
######################################################################

def rebootComFlow(device, level, force):
    try:
        printAndFlush("-I- %-40s-" % ("Sending Reset Command To Fw"), endChar="")
        setResetLevel(device, level)
        printAndFlush("Done")
    except Exception as e:
        if "(265)" in str(e):  # we ignore bad params here in case of old fw that those reset levels are not supported
            printAndFlush("Done")
        elif force :
            printAndFlush("Failed (force flag recieved)")
        else:
            printAndFlush("Failed")
            raise e
######################################################################
# Description: Warm reboot reset Flow
# OS Support : Linux
######################################################################

def rebootMachine(device=None, level=None, force=False):
    rebootComFlow(device, level, force)
    printAndFlush("-I- %-40s-" % ("Sending reboot command to machine"), endChar="")
    if platform.system() == "Windows" or os.name == "nt":
        cmd = "shutdown /r"
    else:
        cmd = "reboot"
    (rc, _, _) = cmdExec(cmd)
    if rc != 0:
        printAndFlush("Failed")
        raise RuntimeError("Failed to reboot machine please reboot machine manually")
    printAndFlush("Done")
    return

######################################################################
# Description: Cold reboot reset flow
# OS Support : Linux
######################################################################

def coldRebootMachine(device=None, level=None, force=False):
    rebootComFlow(device, level, force)
    print("-I- Cold reboot required. please power cycle machine to load new FW.")
    return

######################################################################
# Description: Dictionary of RESET_LEVEL : RESET_FUNCTION
######################################################################

RESET_FUNCS = {RL_ISFU : fullISFU,
               RL_DR_LNK_UP : resetFlow,
               RL_DR_LNK_DN : resetFlow,
               RL_PCI_RESET : resetFlow,
               RL_WARM_REBOOT : rebootMachine,
               RL_COLD_REBOOT : coldRebootMachine, }

######################################################################
# Description:  execute reset level for device
# OS Support : Linux
######################################################################

def execResLvl(device, level, force=False):
    if not (level in range(0, 6)):
        raise RuntimeError("Unknown reset level")
    RESET_FUNCS[level](device, level, force)
    return

######################################################################
# Description: query reset level
# OS Support : Linux
######################################################################

def queryResetLvl(device):
    def printResLine(line, level, minLevel):
        print("%d: %-50s-%s" % (level, line, ("Not Supported", "Supported") [level >= minLevel]))
        return

    minLvl = getResetLevel(device)
    for i in range(0, 6):
        printResLine(RESET_LINES[i], i, minLvl)
    return

######################################################################
# Description: check if a given level is enough to load FW.
# OS Support : Linux
######################################################################

def checkResetLevel(device, reqLevel):
    try:
        level = getResetLevel(device)
        if (reqLevel < level):
            print("-W- minimal reset level required to load Fw: %d. given reset level: %d" % (level, reqLevel))
    except Exception as e:
        pass
    return

######################################################################
# Description:  Search given mst status output for net entity device name
#               and return mst device path.
# OS Support : Linux
######################################################################

def map2DevPathAux(mstOutput, device):
    for l in mstOutput.split('\n'):
        lineList = l.split()
        if device in lineList:
            d = lineList[1]
            if d == "NA":
                d = lineList[2]
            return d
    return None

######################################################################
# Description: Convert net entity device name to mst device path.
# OS Support : Linux
######################################################################

def map2DevPath(device):
    deviceStartsWith00000 = device.startswith("0000:")
    if deviceStartsWith00000:
        device = removeDomainFromAddress(device)
    cmd = "mst status -v"
    (rc, output, _) = cmdExec(cmd)
    if rc != 0:
        raise RuntimeError("Failed to run: " + cmd)
    d = map2DevPathAux(output, device)
    if d != None:
        return d
    #if not found and the device starts with 0000 try again with 0000
    if deviceStartsWith00000:
        d = map2DevPathAux(output, "0000:" + device)
        if d != None:
            return d
    raise RuntimeError("Can not find path of the provided mst device: " + device)

######################################################################
# Description: Main
######################################################################

def main():
    global IS_MSTFLINT
    if platform.system() not in SUPP_OS:
        print("-E- Unsupported OS.")
        return 1
    if platform.system() != "Windows" and os.geteuid() != 0:
        print("-E- Only root user can run this tool.")
        return 1
    if IS_MSTFLINT and "ppc64" in platform.machine():
        print("-E- Mstfwreset is not supported on PPC64 platforms")
        return 1
    # Workaround python "--version" argparse bug:
    verFlag = ""
    helpFlag = ""
    if ("--version" in sys.argv):
        verFlag = "--version"
    if ("-v" in sys.argv):
        verFlag = "-v"
    if ("--help" in sys.argv):
        helpFlag = "--help"
    if ("-h" in sys.argv):
        helpFlag = "-h"
    if (verFlag != "") and ((helpFlag == "") or (sys.argv.index(helpFlag) > sys.argv.index(verFlag))):
        tools_version.PrintVersionString("mlxfwreset", TOOL_VERSION)
        sys.exit(0)

    parser = argparse.ArgumentParser(description=DESCRIPTION,
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     prog=PROG,
                                     epilog=EPILOG,
                                     usage="mlxfwreset -d|--device DEVICE [-l|--level {0,1,2,3,4,5}] [--yes] q|query|r|reset\n[--help]\n[--version]",
                                     add_help=False)
    # options arguments
    options_group = parser.add_argument_group('Options')
    options_group.add_argument('--device',
                        '-d',
                        required=True,
                        help='Device to work with.')
    options_group.add_argument('--level',
                        '-l',
                        type=int,
                        choices=range(0, 6),
                        help='Run reset with the specified reset level.')
    options_group.add_argument('--yes',
                        '-y',
                        help='answer "yes" on prompt.',
                        action="store_true")
    options_group.add_argument('--skip_driver',
                        '-s',
                        help="Skip driver start/stop stage (driver must be stopped manually).",
                        action="store_true")
    options_group.add_argument('--mst_flags',
                        '-m',
                        help="Provide mst flags to be used when invoking mst restart step. For example: --mst_flags=\"--with_fpga\"")
    options_group.add_argument('--version',
                        '-v',
                        help='Print tool version.',
                        action="version",
                        version=tools_version.GetVersionString("mlxfwreset", TOOL_VERSION))
    options_group.add_argument('--help',
                        '-h',
                        help='show this help message and exit.',
                        action="help")
    # hidden flag for ignoring the success/failure of the sendMFRL method
    options_group.add_argument('--force',
                               action="store_true",
                               help=argparse.SUPPRESS)
    # hidden flag for skipping mst restart when performing pci reset
    options_group.add_argument('--no_mst_restart',
                               action="store_true",
                               help=argparse.SUPPRESS)
    # hidden flag for specifying the host bridge of the device for the PCI reset stage
    options_group.add_argument('--pci_bridge',
                               nargs=1,
                               help=argparse.SUPPRESS)
    # reset the multihost sync register to idle state
    options_group.add_argument(RESET_MULTIHOST_REGISTER_FLAG,
                               action="store_true",
                               help=argparse.SUPPRESS)

    options_group.add_argument('--skip_fsm_sync',
                               action="store_true",
                               help="Skip fsm syncing")
    # command arguments
    command_group = parser.add_argument_group('Commands')
    command_group.add_argument('command',
                        nargs=1,
                        choices=["q", "query", "r", "reset", "reset_fsm_register"],
                        help='query: Query reset Level.\n reset: Execute reset.\n reset_fsm_register: Reset the fsm register.')
    args = parser.parse_args()
    device = args.device
    level = args.level
    yes = args.yes
    command = args.command[0]
    if command in ["r", "reset"]:
        command = "reset"
    elif command in ["q", "query"]:
        command = "query"
    elif command in ["reset_fsm_register"]:
        command = "reset_fsm_register"
    # Insert Flow here
    isDevSupp(device)
    # open reg access obj
    global MstDevObj
    global RegAccessObj
    global SkipMstRestart
    global PciOpsObj
    global skipDriver
    global MstFlags
    global CmdifObj
    global ResetMultihostReg
    global SkipMultihostSync
    global DevDBDF
    global FWResetStatusChecker    
    if not IS_MSTFLINT and platform.system() == "Linux":
        device = map2DevPath(device)
    DevDBDF = getDevDBDF(device)
    SkipMstRestart = args.no_mst_restart
    skipDriver = args.skip_driver
    ResetMultihostReg = args.reset_fsm_register
    #TODO: remove this check for January release
    if ResetMultihostReg:
        print("-E- %s flag was deprecated, use reset_fsm_register command instead" % RESET_MULTIHOST_REGISTER_FLAG)
        return 1
    SkipMultihostSync = args.skip_fsm_sync
    MstDevObj = mtcr.MstDevice(device)
    RegAccessObj = regaccess.RegAccess(MstDevObj)
    CmdifObj = cmdif.CmdIf(MstDevObj)
    PciOpsObj = MlnxPciOpFactory().getPciOpObj()
    MstFlags = "" if (args.mst_flags == None) else args.mst_flags   
        
    DevMgtObj = dev_mgt.DevMgt(MstDevObj) # check if device is in livefish
    if DevMgtObj.isLivefishMode() == 1:
        raise RuntimeError("mlxfwreset is not supported for device in livefish")
        return 1 

    FWResetStatusChecker = FirmwareResetStatusChecker(RegAccessObj)

    try:
        if args.pci_bridge:
            PciOpsObj.setPciBridgeAddr(args.pci_bridge[0])
    except NotImplementedError as re:
        if platform.system() == "Windows": 
            pass
        else: 
            raise re
    print("")
    if command == "query":
        print("Supported reset levels for loading FW on device, %s:\n" % device)
        queryResetLvl(device)
    elif command == "reset":
        if level != None:
            print("Requested reset level for device, %s:\n" % device)
        else:
            level = getResetLevel(device)
            print("Minimal reset level for device, %s:\n" % device)
        print("%d: %s" % (level, RESET_LINES[level]))
        # check if user gave us specific reset level and print warrning if its < from minimum reset level required.
        if level != None:
            checkResetLevel(device, level)
        AskUser("Continue with reset", yes)
        execResLvl(device, level, args.force)
        if level != RL_COLD_REBOOT and level != RL_WARM_REBOOT:
            if FWResetStatusChecker.GetStatus() == FirmwareResetStatusChecker.FirmwareResetStatusFailed:
                print("-E- Firmware reset failed, retry operation or reboot machine.")
                return 1
            else:
                print("-I- FW was loaded successfully.")
    elif command == "reset_fsm_register":
        status = CmdifObj.multiHostSyncStatus()
        CmdifObj.multiHostSync(SYNC_STATE_IDLE, status.fsm_sync_type)
        print("-I- FSM register was reseted successfully.")
    return 0

if __name__ == '__main__':
    rc = 0
    try:
        signal.signal(signal.SIGINT, sigHndl)
        rc = main()
    except NoError as e:
        print("-I- %s." % str(e))
    except Exception as e:
        print("-E- %s." % str(e))
        rc = 1
    sys.exit(rc)
