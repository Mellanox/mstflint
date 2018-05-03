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
    from mlxfwresetlib import mlxfwreset_utils
    from mlxfwresetlib.mlxfwreset_utils import cmdExec
    from mlxfwresetlib.mlxfwreset_mlnxdriver import MlnxDriver
    from mlxfwresetlib.mlxfwreset_mlnxdriver import DriverUnknownMode
    from mlxfwresetlib.mlxfwreset_mlnxdriver import MlnxDriverFactory,MlnxDriverLinux
    from mlxfwresetlib.mlxfwreset_status_checker import FirmwareResetStatusChecker
    from mlxfwresetlib.logger import LoggerFactory

    from mlxfwresetlib.mlnx_peripheral_components import MlnxPeripheralComponents
    import Queue
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

EPILOG = textwrap.dedent('''\
Reset levels:
    0: Full ISFU.
    1: Driver restart (link/managment will remain up).
    2: Driver restart (link/managment will be down).
    3: Driver restart and PCI reset.
    4: Warm reboot.
    5: Cold reboot (performed by the user).

Supported Devices:''') + "\n    " + ", ".join(SUPP_DEVICES) + ".\n"

IS_MSTFLINT = True 
# TODO latter remove mcra to the new class
MCRA = 'mcra'
if IS_MSTFLINT:
    MCRA = "mstmcra"

PROG = 'mlxfwreset'
if IS_MSTFLINT:
    PROG = 'mstfwreset'
    
TOOL_VERSION = "1.0.0"

DESCRIPTION = textwrap.dedent('''\
%s : Tool which provides the following functionality:
    1. Query device for reset level required in order to load new firmware
    2. Perform reset operation in order to load new firmware
''' % PROG)
# Adresses    [Base    offset  length]
DEVID_ADDR = [0xf0014, 0     , 16   ]
REVID_ADDR = [0xf0014, 16    , 8    ]

COMMAND_ADDR = 0x4


# Reset Level Constants
RL_ISFU = 0
RL_DR_LNK_UP = 1
RL_DR_LNK_DN = 2
RL_PCI_RESET = 3
RL_WARM_REBOOT = 4
RL_COLD_REBOOT = 5

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
MstDevObjsSD = []
MstFlags = ""
# Pci device Obj
PciOpsObj = None

DevDBDF = None
# icmd object
CmdifObj = None
CmdifObjsSD = []
# FirmwareResetStatusChecker object
FWResetStatusChecker = None

# Global options
SkipMstRestart = False
ResetMultihostReg = False
SkipMultihostSync = False

logger = None
device_global = None

pciModuleName      = "mst_ppc_pci_reset.ko"
pathToPciModuleDir = "/etc/mft/mlxfwreset"

RESET_MULTIHOST_REGISTER_FLAG = "--reset_fsm_register"

SUPPORTED_DEVICES_WITH_SWITCHES = ["15b3", "10ee"]

######################################################################
# Description:  NoError Exception
# OS Support :  Linux/FreeBSD/Windows.
######################################################################
class NoError(Exception):
    pass

######################################################################
# Description:  reset_fsm_register
# OS Support :  Linux/FreeBSD/Windows.
######################################################################
def reset_fsm_register():
    if device_global:
        MstDev = mtcr.MstDevice(device_global)
        Cmdif = cmdif.CmdIf(MstDev)
        if Cmdif.isMultiHostSyncSupported():
            status = Cmdif.multiHostSyncStatus()
            Cmdif.multiHostSync(SYNC_STATE_IDLE, status.fsm_sync_type)
        MstDev.close()

######################################################################
# Description:  Signal handler
# OS Support :  Linux/FreeBSDWindows.
######################################################################

def sigHndl(signal, frame):

    # Remove blacklist file - required to prevent driver auto-load in case of hotswap PCI (flow with old kernel)
    if platform.system() == "Linux" and os.path.exists(MlnxDriverLinux.blacklist_file_path):
        os.remove(MlnxDriverLinux.blacklist_file_path)

    reset_fsm_register()

    print("\nSignal %d Recieved, Exiting..." % signal)
    sys.exit(1)

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
# Description:  Get Linux kernel version
# OS Support :  Linux
######################################################################
def getLinuxKernelVersion():
    cmd = 'uname -r'
    (rc, stdout, stderr) = cmdExec(cmd)
    if rc:
        raise RuntimeError (str(stderr))
    pattern = r'(\d+\.\d+)\..*'
    result = re.match(pattern, stdout)
    if result:
        kernel_version = float(result.group(1))
    else:
        raise RuntimeError('Failed when trying to get the version of Linux kernel')

    return kernel_version


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
    def isMellanoxDevice(self, devAddr):
        raise NotImplementedError("isMellanoxDevice() is not implemented")
    def getPciBridgeAddr(self, devAddr):
        raise NotImplementedError("getPciBridgeAddr() is not implemented")
    def getPcieCapAddr(self, bridgeDev):
        raise NotImplementedError("getPcieCapAddr() is not implemented")
    def getMFDeviceList(self, mstDev, devAddr):
        raise NotImplementedError("getMFDeviceList() is not implemented")
    def savePCIConfigurationSpace(self, devAddr):
        raise NotImplementedError("savePCIConfigurationSpace() is not implemented")
    def loadPCIConfigurationSpace(self, devAddr):
        raise NotImplementedError("loadPCIConfigurationSpace() is not implemented")
    def setPciBridgeAddr(self, bridgeAddr):
        self.bridgeAddr = bridgeAddr

class MlnxPciOpLinux(MlnxPciOp):
    
    def __init__(self):
        super(MlnxPciOpLinux, self).__init__()
        self.pciConfSpaceMap = {}

    def read(self, devAddr, addr, width = "L"):
        cmd = "setpci -s %s 0x%x.%s" % (devAddr, addr, width)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 or not out:
            raise RuntimeError("Failed to read address 0x%x from device %s " % (addr, devAddr))
        return int(out, 16)

    def write(self, devAddr, addr, val, width = "L"):
        cmd = "setpci -s %s 0x%x.%s=0x%x" % (devAddr, addr, width, val)
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to write 0x%x to address 0x%x to device %s " % (val, addr, devAddr))
        return

    def getVendorId(self, devAddr):
        cmd = "setpci -s %s 0x0.w" % (devAddr)
        (rc, output, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("failed to run '%s'" % (cmd))
        return output.strip()

    def isMellanoxDevice(self, devAddr):
        if "15b3" in self.getVendorId(devAddr):
            return True
        return False

    def getPciBridgeAddr(self, devAddr):
        if self.bridgeAddr : # user specified the bridge address
            return self.bridgeAddr
        devAddr = mlxfwreset_utils.addDomainToAddress(devAddr)
        cmd = r'readlink /sys/bus/pci/devices/%s | sed -e "s/.*\/\([0-9a-f:.]*\)\/%s/\1/g"' % (devAddr, devAddr)
        (rc, out, _) = cmdExec(cmd)
        bridgeDev = out.strip()
        result = re.match(r'^[0-9A-Fa-f]{4}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}\.[0-9A-Fa-f]$',bridgeDev)
        if rc != 0 or result is None:
            raise RuntimeError("failed to get Bridge Device for the given PCI device")

        return bridgeDev

    def getPciECapAddr(self, bridgeDev):
        cmd = "lspci -s %s -v | grep 'Capabilities: \[.*\] Express' | sed -e 's/.*\[\([0-9,a-f].*\)\].*/\\1/g'" % bridgeDev
        (rc, capAddr, _) = cmdExec(cmd)
        if rc != 0 or len(capAddr.strip()) == 0:
            raise RuntimeError("Failed to find PCI bridge Pci Express Capability")
        return int(capAddr, 16)

    def getAllPciDevices(self, devAddr):
        devices = []
        pciPath = "/sys/bus/pci/devices/%s" % devAddr
        q = Queue.Queue()
        q.put(pciPath)
        devices.append(devAddr)
        while not q.empty():
            i = q.get()
            files = os.listdir(i)
            for file in files:
                if file.startswith("0000"):
                    if self.getVendorId(file) in SUPPORTED_DEVICES_WITH_SWITCHES:
                        q.put(i + "/" + file)
                        devices.append(file)
        return devices

    def getMFDeviceList(self, mstDev, devAddr):
        MFDevices = []
        #Check if the device has a switch
        if not "ppc64" in platform.machine():
            bridgeDev = self.getPciBridgeAddr(devAddr)
            if isMellanoxSwitchDevice(self, bridgeDev):
                bridgeOfBridge = self.getPciBridgeAddr(bridgeDev)
                return self.getAllPciDevices(bridgeOfBridge)
        domainBus = ":".join(devAddr.split(":")[:2])
        cmd = "lspci -d 15b3: -D | grep %s | cut -d' ' -f1" %domainBus
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("failed to execute: %s" %cmd)
        out = out.strip().split('\n')
        for dev in out:
            MFDevices.append(dev)
        return MFDevices

    def savePCIConfigurationSpace(self, devAddr):
        if self.isMellanoxDevice(devAddr):
            if devAddr.startswith("0000:"):
                devAddr = mlxfwreset_utils.removeDomainFromAddress(devAddr)
            cmd = "mst save %s" %devAddr
            (rc, out, _) = cmdExec(cmd)
            if rc != 0 :
                raise RuntimeError("failed to execute: %s" %cmd)
            return
        confSpaceList = []
        for addr in range(0, 0xfff, 4):
            val = self.read(devAddr, addr)
            confSpaceList.append(val)
        self.pciConfSpaceMap[devAddr] = confSpaceList
        return

    def loadPCIConfigurationSpace(self, devAddr):
        logger.info('loadPCIConfigurationSpace() called. Input is {0}'.format(devAddr))
        if self.isMellanoxDevice(devAddr):
            if devAddr.startswith("0000:"):
                devAddr = mlxfwreset_utils.removeDomainFromAddress(devAddr)
            cmd = "mst load %s" %devAddr
            (rc, out, _) = cmdExec(cmd)
            if rc != 0 :
                raise RuntimeError("failed to execute: %s" %cmd)
            return
        pciConfSpaceList = []
        try:
            pciConfSpaceList = self.pciConfSpaceMap[devAddr]
        except KeyError as ke:
            raise RuntimeError("PCI configuration space for device %s was not saved please reboot server" % devAddr)
        if len(pciConfSpaceList) != 0x400:
            raise RuntimeError("PCI configuration space for device %s was not saved properly please reboot server" % devAddr)
        for i in range(0, 0x400):
            addr = i * 4
            self.write(devAddr, addr, pciConfSpaceList[i])
        return

    def waitForDevice(self,devAddr):
        logger.info('waitForDevice() called. Input is {0}'.format(devAddr))
        path = '/sys/bus/pci/devices/{0}'.format(devAddr)
        TIMEOUT = 10
        for _ in range(TIMEOUT):
            if os.path.exists(path):
                return
            else:
                time.sleep(1)

        raise RuntimeError('Failed to find device in {0}'.format(path))

    def removeDevice(self,devAddr):
        cmd = 'echo 1 > /sys/bus/pci/devices/{0}/remove'.format(devAddr)
        (rc, _, _) = cmdExec(cmd)
        if rc != 0:
           raise RuntimeError("failed to execute: %s" % cmd)


    def rescan(self):
        # TODO check how to exit if rescan is not back
        logger.info('rescan() is called')
        cmd = 'echo 1 > /sys/bus/pci/rescan'
        (rc, _, _) = cmdExec(cmd)
        if rc != 0:
           raise RuntimeError("failed to execute: %s" % cmd)


    def isHotPlugSlot(self,devAddr):
        # TODO check if you can do it with setpci instead of grep
        logger.info('isHotPlugSlot() is called')
        pciBridgeAddr = self.getPciBridgeAddr(devAddr)
        cmd = 'lspci -s {0} -vvv | grep "HotPlug+"'.format(pciBridgeAddr)
        (rc, _, _) = cmdExec(cmd)
        return True if rc == 0 else False


class MlnxPciOpLinuxUl(MlnxPciOpLinux): # Copied from old commit - TODO need to use the same logic of mst load/save
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

    def isMellanoxDevice(self, devAddr):
        cmd = "pciconf -r %s 0x0.w" % devAddr
        (rc, output, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("failed to run '%s'" % (cmd))
        if "15b3" in output:
            return True
        return False

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
    
    def getMFDeviceList(self, mstDev,devAddr):
        MFDevices = []
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
        operatingSystem = platform.system()
        if operatingSystem == "Linux":
            return MlnxPciOpLinuxUl() if IS_MSTFLINT else MlnxPciOpLinux()
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
    logger.debug('Execute {0}'.format(cmd))
    for _ in range(0, 30):
        (rc, stdout, _) = cmdExec(cmd)
        if rc != 0:
            raise NoError("Failed to get the status of the mst module (RC=%d), please restart MST manually" % rc)
        matchedLines = [line for line in stdout.split('\n') if "mst_pciconf" in line]
        logger.debug('matchedLines = {0}'.format(matchedLines))
        if len(matchedLines) == 0:
            return 1
        if matchedLines[0].split()[-1] == '0':
            break
        else :
            time.sleep(2)

    cmd = "lspci -s %s" % busId
    logger.debug('Execute {0}'.format(cmd))
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

    signal.signal(signal.SIGINT,signal.SIG_IGN) # Disable the option to cancel operation with ctrl+c (mst restart might be destructive)
    cmd = "/etc/init.d/mst restart %s" % MstFlags
    logger.debug('Execute {0}'.format(cmd))
    (rc, stdout, stderr) = cmdExec(cmd)
    if rc != 0:
        logger.debug('stdout:\n{0}\nstderr:\n{1}'.format(stdout,stderr))
        raise NoError("Failed to restart MST (RC=%d), please restart MST manually" % rc)
    signal.signal(signal.SIGINT,sigHndl) # Enable the option to cancel operation with ctrl+C
    return 0

######################################################################
# Description:  Get Device ID / Device Rev-ID
# OS Support :  Linux/Windows.
######################################################################

getDevidFromDevice = lambda device: mcraRead(device, DEVID_ADDR[0], DEVID_ADDR[1], DEVID_ADDR[2])


######################################################################
# Description:  Check if device is supported
# OS Support :  Linux/Windows.
######################################################################

def isDevSupp(device):
    logger.info('isDevSupp() called. Inputs : device = {0}'.format(device))
    try:
        devid = getDevidFromDevice(device)
        logger.debug('devid = {0:x}'.format(devid))
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

    # Wait for the pci-device to back if it was removed from the pci tree
    PciOpsObj.waitForDevice(busId)

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

def disablePci(busId):
    logger.debug('disablePci() called')
    global PciOpsObj
    bridgeDev = PciOpsObj.getPciBridgeAddr(busId)
    if isMellanoxSwitchDevice(PciOpsObj, bridgeDev):
        bridgeDev = PciOpsObj.getPciBridgeAddr(bridgeDev)
        bridgeDev = PciOpsObj.getPciBridgeAddr(bridgeDev) # Bridge of bridge
    # Link Control Register : PCI_EXPRESS_CAP_OFFS + 0x10
    capAddr = PciOpsObj.getPciECapAddr(bridgeDev)
    disableAddr = capAddr + 0x10
    width = "L"
    oldCapDw = PciOpsObj.read(bridgeDev, disableAddr, width)
    # turn on Link Disable bit
    logger.debug('Disable PCI address {0}'.format(busId))
    newCapDw = oldCapDw | 0x10
    PciOpsObj.write(bridgeDev, disableAddr, newCapDw, width)
    time.sleep(1.25)

    return (bridgeDev, disableAddr, oldCapDw, width)


def enablePci(bridgeDev, disableAddr, oldCapDw, width):
    logger.debug('enablePci() called')
    PciOpsObj.write(bridgeDev, disableAddr, oldCapDw, width)
    time.sleep(0.25)




######################################################################
# Description:  reset PCI of a certain device
# OS Support : Linux, FreeBSD, Windows
######################################################################

def resetPciAddr(device,devicesSD,driverObj):

    isPPC = "ppc64" in platform.machine()
    isWindows = platform.system() == "Windows"

    # save pci conf space
    global DevDBDF
    busId = DevDBDF

    if isWindows is False: # relevant for ppc(p7)
        devList = savePciConfSpace(device,busId)

        # Socket Direct - save all buses and PCI configuration for all "other" devices in SD
        busIdsSD = []
        devListsSD = []
        for deviceSD in devicesSD:
            busIdSD = mlxfwreset_utils.getDevDBDF(deviceSD, logger)
            busIdsSD.append(busIdSD)
            devListsSD.append(savePciConfSpace(deviceSD,busIdSD))


    #update FWResetStatusChecker
    FWResetStatusChecker.UpdateUptimeBeforeReset()

    isLinuxOldKernel = None
    if platform.system() == "Linux"  and isPPC is False and PciOpsObj.isHotPlugSlot(devList[0]) is True:
        isLinuxAndHotPlugSlot = True
        isLinuxOldKernel = getLinuxKernelVersion() < 4.2 # A bug exist in old linux kerenel - OS rescan doesn't restore all the PCI configuration
    else:
        isLinuxAndHotPlugSlot = False

    if isLinuxAndHotPlugSlot is True:
        driverObj.disableAutoLoad()

    # Close the mst device because the file handler is about to be removed
    # In windows we use the mstdevice to execute the reset pci
    if isWindows is False:
        MstDevObj.close()
        for MstDevObjSD in MstDevObjsSD:
            MstDevObjSD.close()

    signal.signal(signal.SIGINT,signal.SIG_IGN) # Disable the option to cancel operation with ctrl+c (reset pci stage is destructive)
    try:
        if isWindows:
            resetPciAddrWindows(busId)
        elif isPPC:
            resetPciAddrPPC(busId)
        else:
            info = []
            info.append(disablePci(busId))

            for busIdSD in busIdsSD:
                info.append(disablePci(busIdSD))

            for info_ii in info:
                enablePci(*info_ii)
    except Exception as e:
        if isLinuxAndHotPlugSlot:
            driverObj.enableAutoLoad()
        raise RuntimeError("Failed To reset PCI(Driver starting will be skipped). %s" % str(e))


    # wait for FW to re-boot
    time.sleep(1)

    if isWindows is False:
        # restore pci conf space
        loadPciConfSpace(devList,isLinuxAndHotPlugSlot,isLinuxOldKernel)
        # Socket Direct - Load PCI configuration for all other devices in case of SD
        for devListSD in devListsSD:
            time.sleep(1) # TODO check why it's required
            loadPciConfSpace(devListSD,isLinuxAndHotPlugSlot,isLinuxOldKernel)

    if isLinuxAndHotPlugSlot:
        logger.debug('Cleanup for hotplug flow')
        driverObj.enableAutoLoad()

    # Need to re-open the file handler because PCI tree is updated (OS remove/rescan)
    if isWindows is False:
        MstDevObj.open()
        for MstDevObjSD in MstDevObjsSD:
            MstDevObjSD.open()

    logger.debug('UpdateUptimeAfterReset')
    FWResetStatusChecker.UpdateUptimeAfterReset()
    signal.signal(signal.SIGINT,sigHndl) # Enable the option to cancel operation with ctrl+C

    return

######################################################################
# Description: is Given PCI device address a switch device
######################################################################

def isMellanoxSwitchDevice(PciOpsObj, devAddr):
    if (platform.system() == "Windows") or ("ppc64" in platform.machine()):
        return False
    return PciOpsObj.isMellanoxDevice(devAddr)

########################################################################
# Description: is Given PCI device address connected to a switch device
########################################################################

def isConnectedToMellanoxSwitchDevice():
    if (platform.system() == "Windows") or ("ppc64" in platform.machine()):
        return False
    global PciOpsObj
    global DevDBDF
    busId = DevDBDF
    bridgeAddr = PciOpsObj.getPciBridgeAddr(busId)
    return isMellanoxSwitchDevice(PciOpsObj, bridgeAddr)

######################################################################
# Description: Save PCI configuration space for an MST device
# OS Support : Linux, FreeBSD
######################################################################

def savePciConfSpace(mstDev,devAddr):
    logger.info('SavePciConfSpace() called')
    if platform.system() == "Windows": # being Done in mHcaReset
        return None
    global PciOpsObj
    devList = PciOpsObj.getMFDeviceList(mstDev,devAddr)
    # perform mcra read of 0xf0014 to avoid locking semaphores in vsec
    mcraRead(mstDev, 0xf0014, 0, 32)
    # for each PF/VF save its configuration space
    for pciDev in devList:
        PciOpsObj.savePCIConfigurationSpace(pciDev)
    return devList

######################################################################
# Description: Load PCI configuration space for an MST device
# OS Support : Linux, FreeBSD
######################################################################

def loadPciConfSpace(devList,isLinuxAndHotPlugSlot,isLinuxOldKernel):
    logger.info('loadPciConfSpace() called. Inputs are devList={0} , isLinuxAndHotPlugSlot={1}'.format(devList,isLinuxAndHotPlugSlot))
    if platform.system() == "Windows": # being Done in mHcaReset
        return
    global PciOpsObj

    if isLinuxAndHotPlugSlot:

        logger.debug('loadPciConfSpace: wait for PCI devices after OS remove/rescan')
        for pciDev in devList:
            PciOpsObj.waitForDevice(pciDev)  # OS remove the pci device and then rescan

        if isLinuxOldKernel is True: # Old Linux kernel has a bug - OS doesn't restore all the PCI configuration

            time.sleep(0.5) # Avoid stuck of 'mst load' (happen in rare situations)
            logger.debug('loadPciConfSpace: mst-load')
            for pciDev in devList:
                PciOpsObj.loadPCIConfigurationSpace(pciDev)

            logger.debug('loadPciConfSpace: remove bridge device')
            pciBridgeAddr = PciOpsObj.getPciBridgeAddr(devList[0])
            PciOpsObj.removeDevice(pciBridgeAddr)

            logger.debug('loadPciConfSpace: rescan')
            PciOpsObj.rescan()

    else: # Not 'Linux and hotplug' (regular/old flow) - the MSE bit check still here becasue we are not sure what its origin (hotplug or not)
        for pciDev in devList:
            command_reg = PciOpsObj.read(pciDev, COMMAND_ADDR, "W")
            logger.debug('command_reg is {0:x}.'.format(command_reg))
            # Added becasue OS rescan on IBM with PPC - Yoni Galezer can't recall if it's related to hotplug
            # Why it was added also for Linux? Check if it was implemented in the PPC module
            if (command_reg & 0x2) == 0:
                PciOpsObj.loadPCIConfigurationSpace(pciDev)

######################################################################
# Description: get minimum reset level required for device
# OS Support : Linux
######################################################################

def getResetLevel(device):
    logger.info('getResetLevel() called')
    # send mfrl register get
    level = 0
    actualLevel = 0
    try:
        actualLevel = RegAccessObj.sendMFRL(0, regaccess.REG_ACCESS_METHOD_GET)
        if actualLevel == 0:
            raise RuntimeError("Bad reset level Value recieved from FW. please reboot machine to load new FW.")
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
        raise RuntimeError("The fsm register is busy, run \"%s -d <device> reset_fsm_register\" to reset the register." % PROG)
    elif status.fsm_state == SYNC_STATE_IDLE:
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET, 0x1)
        #WA: send again because in single host case the firmware will wait for a second call (fw bug ??)
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
        logger.info('send SYNC_STATE_GET_READY command')

        try:
            sendResetToFW(device, level, force)
        except Exception as e:
            CmdifObj.multiHostSync(SYNC_STATE_IDLE, SYNC_TYPE_FW_RESET)
            raise e

        # Socket Direct - send SYNC_STATE_GET_READY for all other devices in SD
        for CmdifObjSD in CmdifObjsSD:
            CmdifObjSD.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
            logger.info('send SYNC_STATE_GET_READY command')

    elif status.fsm_state == SYNC_STATE_GET_READY: # TODO (update after GA) and status.fsm_sync_type == SYNC_TYPE_FW_RESET
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
        logger.info('send SYNC_STATE_GET_READY command')
    # TODO (update after GA) else: reset_fsm_register



######################################################################
# Description: Stop Driver
######################################################################
def stopDriver(driverObj):
    if driverObj.getDriverStatus() == MlnxDriver.DRIVER_LOADED:
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

    # Roei
    def reloadDriver(driverObj):
        if driverObj.getDriverStatus() == MlnxDriver.DRIVER_LOADED:
            try:
                driverObj.driverStart()
                msg = " (driver was reloaded)"
            except Exception as e:
                msg = " (driver failed to reload: %s)" % str(e)
            return msg

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
            print("Waiting for %s to run on all other hosts, press 'ctrl+c' to abort" % PROG)
            print_waiting_msg = False
        time.sleep(0.5)

    if status.fsm_state != SYNC_STATE_GO or status.fsm_sync_type != SYNC_TYPE_FW_RESET:
        raise RuntimeError("Operation failed, the fsm register state or type is not as expected")

    stopDriver(driverObj)

    CmdifObj.multiHostSync(SYNC_STATE_GO, SYNC_TYPE_FW_RESET)
    # Socket Direct - send SYNC_STATE_GO for all other devices in SD
    for CmdifObjSD in CmdifObjsSD:
        CmdifObjSD.multiHostSync(SYNC_STATE_GO, SYNC_TYPE_FW_RESET)


    status = CmdifObj.multiHostSyncStatus()
    timestamp = time.time()
    print_waiting_msg = True
    while status.fsm_host_ready != 0x0:
        status = CmdifObj.multiHostSyncStatus()
        if status.fsm_sync_type != SYNC_TYPE_FW_RESET or status.fsm_state != SYNC_STATE_GO:
            # Roei
            errmsg = "Operation failed, the fsm register state or type is not as expected"
            msg = reloadDriver(driverObj)
            raise RuntimeError(errmsg+msg)

        diffTime = time.time() - timestamp
        if diffTime > 180:
            errmsg = "fsm sync timed out"
            msg = reloadDriver(driverObj)
            raise RuntimeError(errmsg+msg)
        if print_waiting_msg and diffTime > 2:
            print("Synchronizing with other hosts...")
            print_waiting_msg = False
        time.sleep(0.5)

    if status.fsm_sync_type != SYNC_TYPE_FW_RESET or status.fsm_state != SYNC_STATE_GO:
        # Roei
        errmsg = "Operation failed, the fsm register state or type is not as expected"
        msg = reloadDriver(driverObj)
        raise RuntimeError(errmsg + msg)
        #raise RuntimeError("Operation failed, the fsm register state or type is not as expected")

######################################################################
# Description: Driver restart (link/managment up/down flow) w/wo PCI RESET
# OS Support : Linux
######################################################################
def resetFlow(device,devicesSD, level, force=False):
    logger.info('resetFlow() called')

    try:

        if isConnectedToMellanoxSwitchDevice() and \
               ((platform.system() != "Linux") or
                ("ppc64" in platform.machine())):
            raise RuntimeError("-E- Resetting Device that contains a switch is supported only in Linux/x86")

        if SkipMultihostSync or not CmdifObj.isMultiHostSyncSupported():
            sendResetToFW(device, level, force)
        else:
            sendResetToFWSync(device, level, force) # Roei added support for Socket Direct to send GET_READY for all "other" devices

        # stop driver
        try:
            driverObj = MlnxDriverFactory().getDriverObj(logger, skipDriver, device)
            driverStat = driverObj.getDriverStatus()
        except DriverUnknownMode as e:
            print("-E- Failed to get the driver status: %s" % str(e))
            print("-E- Please make sure the driver is down, and re-run the tool with --skip_driver")
            raise e

        if SkipMultihostSync or not CmdifObj.isMultiHostSyncSupported():
            stopDriver(driverObj)
        else:
            stopDriverSync(driverObj) # Roei added support for Socket Direct to send GO for all "other" devices

        if level == RL_PCI_RESET:
            # reset PCI
            printAndFlush("-I- %-40s-" % ("Resetting PCI"), endChar="")
            resetPciAddr(device,devicesSD,driverObj) # Roei added support to save PCI conf , reset and load PCI conf for all "other"devices
            printAndFlush("Done")

        if driverStat == MlnxDriver.DRIVER_LOADED:
            printAndFlush("-I- %-40s-" % ("Starting Driver"), endChar="")
            driverObj.driverStart()
            printAndFlush("Done")

        # we close MstDevObj to allow a clean operation of mst restart
        MstDevObj.close()
        for MstDevObjSD in MstDevObjsSD:    #Roei close mst devices for all "other" devices
            MstDevObjSD.close()


        global SkipMstRestart
        global DevDBDF
        if SkipMstRestart == False and platform.system() == "Linux":
            printAndFlush("-I- %-40s-" % ("Restarting MST"), endChar="")
            if mstRestart(DevDBDF) == 0:
                printAndFlush("Done")
            else:
                printAndFlush("Skipped")
    except Exception as e:
        reset_fsm_register()
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
# Description:  execute reset level for device
# OS Support : Linux
######################################################################

def execResLvl(device,devicesSD, level, force=False):

    if level == RL_ISFU:
        fullISFU(device,level,force)
    elif level in [RL_DR_LNK_UP,RL_DR_LNK_DN,RL_PCI_RESET]:
        resetFlow(device,devicesSD,level,force)
    elif level == RL_WARM_REBOOT:
        rebootMachine(device,level,force)
    elif level == RL_COLD_REBOOT:
        coldRebootMachine(device,level,force)
    else:
        raise RuntimeError("Unknown reset level")



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
    # try:
    #     level = getResetLevel(device)
    #     if (reqLevel < level):
    #         print("-W- minimal reset level required to load Fw: %d. given reset level: %d" % (level, reqLevel))
    # except Exception as e:
    #     pass
    # return

    try:
        level = getResetLevel(device)
    except:
        level = None

    if level and reqLevel < level:
        raise RuntimeError("Minimal reset level required to load Fw: %d. given reset level: %d" % (level, reqLevel))



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
        device = mlxfwreset_utils.removeDomainFromAddress(device)
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
    global logger
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
        tools_version.PrintVersionString(PROG, TOOL_VERSION)
        sys.exit(0)

    parser = argparse.ArgumentParser(description=DESCRIPTION,
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     prog=PROG,
                                     epilog=EPILOG,
                                     usage="%s -d|--device DEVICE [-l|--level {0,1,2,3,4,5}] [--yes] q|query|r|reset\n[--help]\n[--version]" % PROG,
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
                        version=tools_version.GetVersionString(PROG, TOOL_VERSION))
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

    # Skip on the self discover devices logic for socket direct(option to disable the feature in case of bug)
    options_group.add_argument('--skip_socket_direct',
                               action="store_true",
                               help=argparse.SUPPRESS)
    # log level
    options_group.add_argument('--log',
                               choices=['info','debug','error','fatal'],
                               help=argparse.SUPPRESS)

    # command arguments
    command_group = parser.add_argument_group('Commands')
    command_group.add_argument('command',
                        nargs=1,
                        choices=["q", "query", "r", "reset", "reset_fsm_register"],
                        help='query: Query reset Level.\n reset: Execute reset.\n reset_fsm_register: Reset the fsm register.')
    args = parser.parse_args()
    device = args.device
    global device_global
    device_global = args.device # required for reset_fsm_register when exiting with ctrl+c/exception (latter think how to move the global)
    level = args.level
    yes = args.yes

    command = args.command[0]
    if command in ["r", "reset"]:
        command = "reset"
    elif command in ["q", "query"]:
        command = "query"
    elif command in ["reset_fsm_register"]:
        command = "reset_fsm_register"

    # logger
    logger = LoggerFactory().get('mlxfwreset',args.log)

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

    if platform.system() == "Linux": # Convert ib-device , net-device to mst-device(mst started) or pci-device
        if IS_MSTFLINT:
            if device.startswith('mlx'):
                driver_path = '/sys/class/infiniband/{0}/device'.format(device)
                try:
                    device = os.path.basename(os.readlink(driver_path))
                except:
                    raise RuntimeError('Failed to Identify Device: {0}'.format(device))
        else:
            device = map2DevPath(device)

    # Insert Flow here
    isDevSupp(device)

    DevDBDF = mlxfwreset_utils.getDevDBDF(device,logger)
    logger.info('device domain:bus:dev.fn (DBDF) is {0}'.format(DevDBDF))
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

    logger.info('Check if device is livefish')
    DevMgtObj = dev_mgt.DevMgt(MstDevObj) # check if device is in livefish
    if DevMgtObj.isLivefishMode() == 1:
        raise RuntimeError("%s is not supported for device in Flash Recovery mode" % PROG)


    # Socket Direct - Create a list of command i/f for all "other" devices
    global CmdifObjsSD
    global MstDevObjsSD

    # Roei
    devicesSD = []
    if command == "reset" and not args.skip_socket_direct:

        try:
            peripherals = MlnxPeripheralComponents()
            usr_pci_device = peripherals.get_pci_device(device)
            socket_direct_pci_devices = peripherals.get_socket_direct_pci_devices(usr_pci_device)
            for socket_direct_pci_device in socket_direct_pci_devices:
                devicesSD.append(socket_direct_pci_device.get_alias())

            for deviceSD in devicesSD:
                MstDevObjsSD.append(mtcr.MstDevice(deviceSD))
                CmdifObjsSD.append(cmdif.CmdIf(MstDevObjsSD[-1]))
        except:
            #print("-I- Failed to check if device is Socket Direct. Continue...") TODO remove if from the GA
            devicesSD = []
            for MstDevObjSD in MstDevObjsSD:
                MstDevObjSD.close()
            MstDevObjsSD = []
            CmdifObjsSD = []


        if len(devicesSD)>0:
            if platform.system() == "Windows":
                raise RuntimeError("mlxfwreset doesn't support socket direct on windows!")
            if "ppc64" in platform.machine():
                raise RuntimeError("mlxfwreset doesn't support socket direct on ppc!")


    MstFlags = "" if (args.mst_flags == None) else args.mst_flags   



    logger.info('Create FWResetStatusChecker')
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
        logger.debug('Command is query')
        print("Supported reset levels for loading FW on device, %s:\n" % device)
        queryResetLvl(device)
    elif command == "reset":
        logger.debug('Command is reset')
        if level != None:
            print("Requested reset level for device, %s:\n" % device)
        else:
            level = getResetLevel(device)
            print("Minimal reset level for device, %s:\n" % device)
        print("%d: %s" % (level, RESET_LINES[level]))
        logger.debug('level is {0}'.format(level))
        # check if user gave us specific reset level and print warning if its < from minimum reset level required.
        if level != None:
            checkResetLevel(device, level)
        AskUser("Continue with reset", yes)
        execResLvl(device,devicesSD, level, args.force)
        if level != RL_COLD_REBOOT and level != RL_WARM_REBOOT:
            if FWResetStatusChecker.GetStatus() == FirmwareResetStatusChecker.FirmwareResetStatusFailed:
                reset_fsm_register()
                print("-E- Firmware reset failed, retry operation or reboot machine.")
                return 1
            else:
                print("-I- FW was loaded successfully.")
    elif command == "reset_fsm_register":
        reset_fsm_register()
        print("-I- FSM register was reset successfully.")
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
