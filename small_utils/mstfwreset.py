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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE OF
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
import sys
try:
    import argparse
    import textwrap
    import os
    import platform
    import struct
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
    from mlxfwresetlib.mlxfwreset_utils import is_in_internal_host, is_uefi_secureboot
    from mlxfwresetlib.mlxfwreset_mlnxdriver import MlnxDriver
    from mlxfwresetlib.mlxfwreset_mlnxdriver import DriverUnknownMode
    from mlxfwresetlib.mlxfwreset_mlnxdriver import MlnxDriverFactory,MlnxDriverLinux
    from mlxfwresetlib.mlxfwreset_status_checker import FirmwareResetStatusChecker
    from mlxfwresetlib.logger import LoggerFactory
    from mlxfwresetlib.cmd_reg_mfrl import CmdRegMfrl, CmdNotSupported
    # from mlxfwresetlib.cmd_reg_mpcir import CmdRegMpcir
    from mlxfwresetlib.cmd_reg_mcam import CmdRegMcam
    if os.name != 'nt':
        if not getattr(sys, 'frozen', False):
            sys.path.append(os.sep.join((os.path.dirname(os.path.dirname(os.path.realpath(__file__))), "mlxpci")))
        from mlxpci_lib import PCIDeviceFactory
    from mlxfwresetlib.mlnx_peripheral_components import MlnxPeripheralComponents
    if (sys.version_info > (3, 0)):
        import queue
        from builtins import input as raw_input
    else:
        import Queue as queue
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)

# Constants ###########################
class SyncOwner():
    TOOL = 0
    DRIVER = 1

MLNX_DEVICES = [
               dict(name="ConnectX2", devid=0x190),
               dict(name="ConnectX3Pro", devid=0x1f7),
               dict(name="ConnectIB", devid=0x1ff, status_config_not_done=(0xb0004, 31)),
               dict(name="ConnectX4", devid=0x209, status_config_not_done=(0xb0004, 31)),
               dict(name="ConnectX4LX", devid=0x20b, status_config_not_done=(0xb0004, 31)),
               dict(name="ConnectX5", devid=0x20d, status_config_not_done=(0xb5e04, 31)),
               dict(name="BlueField", devid=0x211, status_config_not_done=(0xb5e04, 31)),
               dict(name="BlueField2", devid=0x214, status_config_not_done=(0xb5f04, 31)),
               dict(name="BlueField3", devid=0x21c, status_config_not_done=(0xb5f04, 31)),
               dict(name="ConnectX6", devid=0x20f, status_config_not_done=(0xb5f04, 31)),
               dict(name="ConnectX6DX", devid=0x212, status_config_not_done=(0xb5f04, 31)),
               dict(name="ConnectX6LX", devid=0x216, status_config_not_done=(0xb5f04, 31)),
               dict(name="ConnectX7", devid=0x218, status_config_not_done=(0xb5f04, 31)),
               dict(name="ConnectX3", devid=0x1f5),
               dict(name="SwitchX", devid=0x245),
               dict(name="IS4", devid=0x1b3),
               ]

# Supported devices.
SUPP_DEVICES = ["ConnectIB", "ConnectX4", "ConnectX4LX", "ConnectX5", "BlueField",
                "ConnectX6", "ConnectX6DX", "ConnectX6LX", "BlueField2", "ConnectX7", "BlueField3"]
SUPP_OS = ["FreeBSD", "Linux", "Windows"]

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
%s : The tool provides the following functionality in order to load new firmware:
    1. Query the device for the supported reset-level and reset-type
    2. Perform reset operation on the device
''' % PROG)
# Adresses    [Base    offset  length]
DEVID_ADDR = [0xf0014, 0     , 16   ]

COMMAND_ADDR = 0x4

#sync constants:
SYNC_TYPE_FW_RESET   = 0x1
SYNC_STATE_IDLE      = 0x0
SYNC_STATE_GET_READY = 0x1
SYNC_STATE_GO        = 0x2
SYNC_STATE_DONE      = 0x3

# reg access Object
RegAccessObj = None
RegAccessObjsSD = []
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
SkipMultihostSync = False

logger = None
device_global = None

pciModuleName      = "mst_ppc_pci_reset.ko"
pathToPciModuleDir = "/etc/mft/mlxfwreset"

SUPPORTED_DEVICES_WITH_SWITCHES = ["15b3", "10ee","1af4"] #1af4 for Red Hat (virtio)


######################################################################
# Description:  Pcnr Exception
# OS Support :  Linux.
######################################################################
class PcnrError(Exception):
    pass

######################################################################
# Description:  NoError Exception
# OS Support :  Linux/FreeBSD/Windows.
######################################################################
class NoError(Exception):
    pass

######################################################################
# Description:  Warning Exception
# OS Support :  Linux/FreeBSD/Windows.
######################################################################
class WarningException(Exception):
    pass

######################################################################
# Description:  NoPciBridge Exception
# OS Support :  Linux/FreeBSD/Windows.
######################################################################
class NoPciBridgeException(Exception):
    pass

######################################################################
# Description:  is_fw_ready
# OS Support :  Linux/FreeBSD/Windows.
######################################################################
def is_fw_ready(device):
    'Check if FW is ready to get icmd'

    try:
        address, offset = None, None

        devid = getDevidFromDevice(device)

        for mlnx_device in MLNX_DEVICES:
            if mlnx_device['devid'] == devid:
                address, offset = mlnx_device['status_config_not_done']

        status_config_not_done = mcraRead(device, address, offset, 1)
        return False if status_config_not_done == 1 else True

    except:
        raise RuntimeError("Failed to check if fw is ready to get ICMD")

######################################################################
# Description:  wait_for_fw_ready
# OS Support :  Linux/FreeBSD/Windows.
######################################################################
def wait_for_fw_ready(device):
    'Wait for FW to be ready to get icmd'

    MAX_POLL_CNTR = 1000
    POLL_SLEEP_INTERVAL = 0.001

    for ii in range(MAX_POLL_CNTR):
        if is_fw_ready(device) == True:
            break
        else:
            time.sleep(POLL_SLEEP_INTERVAL)
            if ii % 100 == 0: logger.debug("FW isn't ready ii={0}".format(ii))
    else:
        logger.debug("Exit polling before FW is ready!!!!")




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
    reset_fsm_register()

    print("\nSignal %d received, Exiting..." % signal)
    sys.exit(1)

def set_signal_handler():
    "Call sigHndl() when the user exit the process by typing ctrl+c or kill the process"
    signal.signal(signal.SIGINT, sigHndl)
    signal.signal(signal.SIGTERM, sigHndl)

def ignore_signals():
    "Disable the option to cancel operation with ctrl+c or kill"
    signal.signal(signal.SIGINT, signal.SIG_IGN)
    signal.signal(signal.SIGTERM, signal.SIG_IGN)


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
# Description:  ask user Y/N question if N/n/No/no was received raise
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
    def getMFDeviceList(self, devAddr):
        raise NotImplementedError("getMFDeviceList() is not implemented")
    def savePCIConfigurationSpace(self, devAddr, pci_device):
        raise NotImplementedError("savePCIConfigurationSpace() is not implemented")
    def loadPCIConfigurationSpace(self, devAddr, pci_device, full=True):
        raise NotImplementedError("loadPCIConfigurationSpace() is not implemented")
    def waitForDevice(self,devAddr):
        pass # TODO need to implement for FreeBSD
    def getAllBuses(self,devices):
        raise NotImplementedError("getAllBuses() is not implemented")
    def removeDevice(self,devAddr):
        raise NotImplementedError("removeDevice() is not implemented")
    def rescan(self):
        raise NotImplementedError("rescan() is not implemented")
    def setPciBridgeAddr(self, bridgeAddr):
        self.bridgeAddr = bridgeAddr

def printBuf(buf):
    bytes = buf.tolist()
    for i in range(len(bytes)):
        if i % 16 == 0:
            print("")
        print("%02x " % bytes[i], end=''),
    print("")


class MlnxPciOpLinux(MlnxPciOp):
    pciWidthToStructSize = {'Q': 'Q', 'L': 'I', 'W': 'H', 'B': 'B'}
    pciWidthToByteCount = {'Q': 8, 'L': 4, 'W': 2, 'B': 1}

    def __init__(self):
        super(MlnxPciOpLinux, self).__init__()
        self.pciConfSpaceMap = {}
        self.device_control_register_old = {} # key is dbdf, value is configuration of "device_control_register"

    def savePciConfOptimalValues(self,devAddr):
        logger.debug("Saving device control register for device: %s" % devAddr)
        # Save the BIOS values of "device control register" (need to restore in case of OS 'remove'/'rescan')
        assert devAddr not in self.device_control_register_old, 'savePCIConfigurationSpace - {0} is already in dictionary'.format(devAddr)
        self.device_control_register_old[devAddr] = self.read(devAddr, 0x68, 'w') # Reading "Device Control Register" (BIOS values)
        logger.debug("Saving device control register for device: %s - DONE" % devAddr)

    def loadPciConfOptimalValues(self,devAddr):
        logger.debug("Restoring device control register for device: %s" % devAddr)
        # bits 5-7 max_payload_size ; bits 12-14 max_read_request_size in "Device Control Register"
        MASK = 0b0111000011100000
        MASK__ = 0b1000111100011111

        assert devAddr in self.device_control_register_old, 'loadPciConfOptimalValues: {0} is not in dictionay'.format(devAddr)
        device_control_register_new = self.read(devAddr, 0x68,'w')  # Reading "Device Control Register" (after pci 'rescan')
        device_control_register_updated = (device_control_register_new & MASK__) | (self.device_control_register_old[devAddr] & MASK)
        self.write(devAddr, 0x68, device_control_register_updated, 'w')  # Overwriting "Device Control Register"
        logger.debug("Restoring device control register for device: %s - Done" % devAddr)

    def read(self, devAddr, addr, width = "L"):
        cmd = "setpci -s %s 0x%x.%s" % (devAddr, addr, width)
        (rc, out, _) = cmdExec(cmd)
        logger.debug('read : cmd={0} rc={1} out={2}'.format(cmd,rc,out))
        if rc != 0 or not out:
            raise RuntimeError("Failed to read address 0x%x from device %s " % (addr, devAddr))
        return int(out, 16)

    def write(self, devAddr, addr, val, width = "L"):

        cmd = "setpci -s %s 0x%x.%s=0x%x" % (devAddr, addr, width, val)
        (rc, out, _) = cmdExec(cmd)
        logger.debug('write : cmd={0} rc={1} out={2}'.format(cmd,rc,out))
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
            raise NoPciBridgeException("Failed to get Bridge Device for the given PCI device! You might be running on a Virtual Machine!")

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
        q = queue.Queue()
        q.put(pciPath)
        devices.append(devAddr)
        while not q.empty():
            i = q.get()
            files = os.listdir(i)
            for file in files:
                if re.match(r'^[0-9A-Fa-f]{4}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}\.[0-9A-Fa-f]$',file) is not None:
                    if self.getVendorId(file) in SUPPORTED_DEVICES_WITH_SWITCHES:
                        q.put(i + "/" + file)
                        devices.append(file)
        return devices

    def getMFDeviceList(self,devAddr):
        """
        Return the device and the sibling devices (in case of Innova also cousins devices)
        """
        MFDevices = []
        domainBus = ":".join(devAddr.split(":")[:2])

        if "ppc64" in platform.machine():
            cmd = "lspci -d 15b3: -s {0}: -D | grep -v DMA".format(domainBus) # list without NVME emulation (on bluefield)
            (rc, out, _) = cmdExec(cmd)
            if rc != 0:
                raise RuntimeError("failed to execute: {0}".format(cmd))
            for line in out.splitlines():
                MFDevices.append(line.split()[0])
        else: 
            pci_device_bridge1 = self.getPciBridgeAddr(devAddr)
            if is_in_internal_host(): # Bluefield (NIC only reset)
                pci_device_bridge2 = self.getPciBridgeAddr(pci_device_bridge1)
                pci_device_bridge3 = self.getPciBridgeAddr(pci_device_bridge2)    
                return self.getAllPciDevices(pci_device_bridge3)
            elif is_mellanox_device(pci_device_bridge1): # Innova
                pci_device_bridge2 = self.getPciBridgeAddr(pci_device_bridge1)
                return self.getAllPciDevices(pci_device_bridge2)
            else:
                cmd = "lspci -s {0}: -D".format(domainBus)
                (rc, out, _) = cmdExec(cmd)
                if rc != 0:
                    raise RuntimeError("failed to execute: {0}".format(cmd))
                for line in out.splitlines():
                    MFDevices.append(line.split()[0])

        return MFDevices

    def savePCIConfigurationSpace(self, devAddr, pci_device):
        self.savePciConfOptimalValues(devAddr)
        pci_device.save_configuration_space()

    def loadPCIConfigurationSpace(self, devAddr, pci_device, full=True):
        if full == True:
            pci_device.restore_configuration_space()
        else: # OS 'remove'/'rescan' -> need to restore optimal value in "device control register" for old kernel module
            if getLinuxKernelVersion() < 4.2:
                logger.info('old kernel')
                self.loadPciConfOptimalValues(devAddr)


    def waitForDevice(self,devAddr):
        logger.info('waitForDevice() called. Input is {0}'.format(devAddr))
        path = '/sys/bus/pci/devices/{0}/config'.format(devAddr)
        TIMEOUT = 100
        for _ in range(TIMEOUT):
            if os.path.exists(path):
                return
            else:
                time.sleep(0.1)

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

    def getAllBuses(self,devices):         
        buses =[]
        for dev in devices:
            busId =  mlxfwreset_utils.getDevDBDF(dev)            
            buses += self.getMFDeviceList(busId)
        return buses

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
            raise NoPciBridgeException("Failed to get Bridge Device for the given PCI device! You might be running on a Virtual Machine!")
        linesCount = len(out.splitlines())
        if(linesCount == 0):
            raise RuntimeError("There is no secbus with the value: %s" %busNum)
        if(linesCount > 1):
            raise RuntimeError("Found more than one secbus with the value: %s" %busNum)
        hostBridge = "pcib%s" %(out.split("pcib.")[1].split(".")[0])
        
        # get pci address of hostBridge
        cmd = "pciconf -l | grep {0}".format(hostBridge)
        rc, out, _ = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to extract PCI bridge address ({0})".format(cmd))
        try:
            bridgeDevAddr = out.split()[0].split('@')[1][:-1] # Extract the pci device from the output
        except:
            raise RuntimeError("Failed to extract PCI bridge address ({0})".format(out))
        return bridgeDevAddr

    def getPciECapAddr(self, bridgeDev):
        cmd = "pciconf -lc %s | grep \"cap 10\" | sed -e 's/.*\[\([0-9,a-f]*\)\].*/\\1/g'" % bridgeDev
        (rc, capAddr, _) = cmdExec(cmd)
        if rc != 0 or len(capAddr.strip()) == 0:
            raise RuntimeError("Failed to find PCI bridge Pci Express Capability")
        return int(capAddr, 16)
    
    def getMFDeviceList(self, devAddr):
        MFDevices = []
        domainBus = ":".join(devAddr.split(":")[:-2])
        domainBus = "pci" + domainBus
        cmd = "pciconf -l | grep 'chip=0x[0-9,a-f]\{4\}15b3 \|vendor=0x15b3' | grep %s | cut -f1 | cut -d@ -f2" %domainBus
        (rc, out, _) = cmdExec(cmd)
        if rc != 0 :
            raise RuntimeError("failed to get execure: %s" %cmd)
        out = out.strip().split('\n')
        for dev in out:
            MFDevices.append(dev[:-1])
        return MFDevices

    def savePCIConfigurationSpace(self, devAddr, pci_device):
        self.pciConfSpaceMap[devAddr] = {}
        pci_device.save_configuration_space()

    def loadPCIConfigurationSpace(self, devAddr, pci_device, full=True):
        pci_device.restore_configuration_space()

# TODO are we using this class ??? 
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
        raise NotImplementedError("getPciBridgeAddr() not implemented for windows")

    def getPciECapAddr(self, bridgeDev):
        raise NotImplementedError("getPciECapAddr() not implemented for windows")

    def savePCIConfigurationSpace(self, devAddr, pci_device):
        raise NotImplementedError("savePCIConfigurationSpace() not implemented for windows")
    
    def loadPCIConfigurationSpace(self, devAddr, pci_device,full=True):
        raise NotImplementedError("loadPCIConfigurationSpace() not implemented for windows")


class MlnxPciOpFactory(object):
    def getPciOpObj(self,dbdf):
        operatingSystem = platform.system()
        if operatingSystem == "Linux":
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
    logger.debug('Execute {0}'.format(cmd))
    for _ in range(0, 30):
        (rc, stdout, _) = cmdExec(cmd)
        if rc != 0:
            raise WarningException("Failed to get the status of the mst module, please restart MST manually")
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
        raise WarningException("Failed to run lspci command, please restart MST manually")
    if foundBus == False:
        raise RuntimeError("The device is not appearing in lspci output!")

    ignore_signals()
    cmd = "/etc/init.d/mst restart %s" % MstFlags
    logger.debug('Execute {0}'.format(cmd))
    (rc, stdout, stderr) = cmdExec(cmd)
    if rc != 0:
        logger.debug('stdout:\n{0}\nstderr:\n{1}'.format(stdout,stderr))
        raise WarningException("Failed to restart MST, please restart MST manually")
    set_signal_handler()
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

def runPPCPciResetModule(path, busIds):
    busIdStr = ",".join(busIds)
    cmd = "insmod %s pci_dev=%s" % (path, busIdStr)
    logger.debug(cmd)
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

def resetPciAddrPPC(busIds):

    logger.debug('resetPciAddrPPC() called. input is {0}'.format(busIds))

    # check supported system
    if platform.system() != "Linux":
        raise RuntimeError("Unsupported OS(%s) for PPC reset flow" % (platform.system()))

    if isModuleLoaded("mst_ppc_pci_reset") == True:
        logger.debug('Unload the module "mst_ppc_pci_reset"')
        cmd = "rmmod mst_ppc_pci_reset"
        logger.debug(cmd)
        (rc, out, _) = cmdExec(cmd)
    if isModuleLoaded("mst_ppc_pci_reset") == True:
        raise RuntimeError("Failed to unload mst_ppc_pci_reset module. please unload it manually and try again.")

    logger.debug('Load the module "mst_ppc_pci_reset"')
    (foundModule, path) = getPciModulePath()
    if foundModule == True:
        (res, err) = runPPCPciResetModule(path, busIds)
        if res == False:
            raise RuntimeError("Failed to load pci reset module, make sure kernel-mft is installed properly: %s" % err)
    else:
        foundWorkingModule = False
        for p in path:
            (res, err) = runPPCPciResetModule(path, busIds)
            if res == True:
                foundWorkingModule = True
                break
        if foundWorkingModule == False:
            raise RuntimeError("Can not find the module: %s" % pciModuleName)

    logger.debug('Unload the module "mst_ppc_pci_reset"')
    cmd = "rmmod mst_ppc_pci_reset"
    logger.debug(cmd)
    (rc, out, err) = cmdExec(cmd)
    if rc != 0 :
        raise RuntimeError("Failed to unload pci reset module: %s please unload the module manually" % err)


######################################################################
# Description:  reset PCI of a certain device for Windows setup (special flow)
# OS Support : Windows
######################################################################

def resetPciAddrWindows(dbdf_list):
    global MstDevObj
    MstDevObj.mHcaReset(dbdf_list)
    return

######################################################################
# Description:  reset PCI of a certain device for Linux/FBSD setup
# OS Support : Linux, FreeBSD
######################################################################

def disablePci(bridgeDev, capAddr):
    logger.debug('disablePci() called')
    
    disableAddr = capAddr + 0x10
    width = "L"
    oldCapDw = PciOpsObj.read(bridgeDev, disableAddr, width)
    # turn on Link Disable bit
    logger.debug('Disable PCI bridge {0} Link Control Register address {1:x}'.format(bridgeDev, disableAddr))
    newCapDw = oldCapDw | 0x10
    logger.debug('old value: {0:x}; new value: {1:x}'.format(oldCapDw,newCapDw))
    PciOpsObj.write(bridgeDev, disableAddr, newCapDw, width)

    return (bridgeDev, disableAddr, oldCapDw, width)


def enablePci(bridgeDev, disableAddr, oldCapDw, width):
    logger.debug('enablePci() called')
    PciOpsObj.write(bridgeDev, disableAddr, oldCapDw, width)


######################################################################
# Description:  reset PCI of a certain device
# OS Support : Linux, FreeBSD, Windows
######################################################################

def resetPciAddr(device,devicesSD,driverObj, cmdLineArgs):

    isPPC = "ppc64" in platform.machine()
    isWindows = platform.system() == "Windows"
    
    busId = DevDBDF

    # Determine the pci-device to poll (first Mellanox device in the pci tree)
    if isWindows is False:

        if is_in_internal_host(): # Bluefied (NIC only reset)
            pci_device_bridge1 = PciOpsObj.getPciBridgeAddr(DevDBDF)
            pci_device_bridge2 = PciOpsObj.getPciBridgeAddr(pci_device_bridge1)
            pci_device_bridge3 = PciOpsObj.getPciBridgeAddr(pci_device_bridge2)

            pci_device_to_poll_devid = pci_device_bridge3
            root_pci_device = PCIDeviceFactory().get(pci_device_bridge3, "debug")
        elif is_pci_bridge_is_mellanox_device(DevDBDF): # Innova (FPGA)
            pci_device_bridge1 = PciOpsObj.getPciBridgeAddr(DevDBDF)
            pci_device_bridge2 = PciOpsObj.getPciBridgeAddr(pci_device_bridge1)
            pci_device_bridge3 = PciOpsObj.getPciBridgeAddr(pci_device_bridge2)

            pci_device_to_poll_devid = pci_device_bridge2
            root_pci_device = PCIDeviceFactory().get(pci_device_bridge3, "debug")
        elif isPPC: # PPC can run on VM (no PCI bridge device)
            pci_device_to_poll_devid = DevDBDF
        else:
            pci_device_to_poll_devid = DevDBDF
            pci_device_bridge = PciOpsObj.getPciBridgeAddr(DevDBDF)
            root_pci_device = PCIDeviceFactory().get(pci_device_bridge, "debug")

        logger.debug('pci_device_to_poll_devid={0}'.format(pci_device_to_poll_devid))
        if not isPPC:
            logger.debug('root_pci_device={0}'.format(root_pci_device))


    if isWindows is False: # relevant for ppc(p7) TODO check power8/9 shouldn't use mst-save/load
        logger.info('Save PCI Configuration space ...')
       
        devList = PciOpsObj.getMFDeviceList(busId) # Get all devices that you want to save/load pci configuration
        logger.debug('devList is {0}'.format(devList))
        # for each PF/VF save its configuration space
        pci_device_dict = {}
        for pciDev in devList:
            pci_device_object = PCIDeviceFactory().get(pciDev, "debug")
            pci_device_dict[pciDev] = pci_device_object
            PciOpsObj.savePCIConfigurationSpace(pciDev, pci_device_object)
        # Socket Direct - save all buses and PCI configuration for all "other" devices in SD
        busIdsSD = []
        devListsSD = []
        for deviceSD in devicesSD:
            busIdSD = mlxfwreset_utils.getDevDBDF(deviceSD, logger)
            busIdsSD.append(busIdSD)
            busIdSD_list = PciOpsObj.getMFDeviceList(busIdSD)
            logger.debug('Socket Direct List is {0}'.format(devList))
            logger.debug("Saving socket direct list ...")
            for pciDev in busIdSD_list:
                pci_device_object = PCIDeviceFactory().get(pciDev, "debug")
                pci_device_dict[pciDev] = pci_device_object
                PciOpsObj.savePCIConfigurationSpace(pciDev, pci_device_object)
            devListsSD += busIdSD_list

    #update FWResetStatusChecker
    FWResetStatusChecker.UpdateUptimeBeforeReset()
     
    # calculate bridge devices to reset and capaddr - we do it before the critical time
    if not isWindows and not isPPC:
        bridgeDevs = []
        for busId in [busId] + busIdsSD:
            bridgeDev = PciOpsObj.getPciBridgeAddr(busId)
            if is_mellanox_device(bridgeDev) and not is_in_internal_host(): # Innova
                bridgeDev = PciOpsObj.getPciBridgeAddr(bridgeDev)     # bridgeDev = pci_device_bridge2
                bridgeDev = PciOpsObj.getPciBridgeAddr(bridgeDev)     # bridgeDev = pci_device_bridge3
                 
            # Link Control Register : PCI_EXPRESS_CAP_OFFS + 0x10
            capAddr = PciOpsObj.getPciECapAddr(bridgeDev)
                      
            bridgeDevs.append((bridgeDev,capAddr))
     
     
    if SkipMultihostSync or not CmdifObj.isMultiHostSyncSupported():
        stopDriver(driverObj)
    else:
        # Isolated Smart-NIC support
        try:
            cmd = 'echo 0xde31001 > /sys/bus/platform/drivers/mlx-bootctl/fw_reset'
            rc, _, _ = cmdExec(cmd)
            if rc == 0:
                logger.debug('GPIO signal was sent from Smart-NIC integrated ARM')
                # For debug: if signal sent ok, out should be 0x4:
                # cmd = 'mcra <dbdf> 0xf3404'
                # rc, out, _ = cmdExec(cmd)
                # logger.debug("read val of yu.gpio.gpios_bits.gpio_internal.datain = " + str(out))
            else:
                raise Exception
        except:
            logger.debug('Not inside Smart-NIC integrated ARM or command is not supported in FW')
        stopDriverSync(driverObj)

    logger.debug('start critical time (driver is unloaded)')
    
    # Close the mst device because the file handler is about to be removed
    # In windows we use the mstdevice to execute the reset pci
    if isWindows is False:
        MstDevObj.close()
        for MstDevObjSD in MstDevObjsSD:
            MstDevObjSD.close()
        logger.debug('finished to close mst device')

    
    printAndFlush("-I- %-40s-" % ("Resetting PCI"), endChar="")

    ignore_signals()
    try:
        if isWindows:
            dbdf_list= []
            for deviceSD in devicesSD:
                dbdf = mlxfwreset_utils.getDevDBDF(deviceSD, logger)
                dbdf.encode("utf-8")
                dbdf_list.append(dbdf)

            busId.encode("utf-8")
            dbdf_list.append(busId)

            resetPciAddrWindows(dbdf_list)
        elif isPPC:            
            busIdsSD.append(busId)            
            pfs = PciOpsObj.getAllBuses(busIdsSD)
            resetPciAddrPPC(pfs)
        else:
            info = []
 
            # Disable
            logger.debug('[Timing Test] PCI Disable') 
            for bridgeDev,capAddr in bridgeDevs:
                info.append(disablePci(bridgeDev,capAddr))

            # Sleep
            logger.debug('sleeping... ({0} sec)'.format(cmdLineArgs.pci_link_downtime))
            time.sleep(cmdLineArgs.pci_link_downtime)

            # Enable
            if not is_in_internal_host():
                logger.debug('[Timing Test] PCI Enable')
                for info_ii in info:
                    enablePci(*info_ii)

    except Exception as e:
        raise RuntimeError("Failed To reset PCI(Driver starting will be skipped). %s" % str(e))


    if isWindows is False:

        logger.debug('WaitForDevice: in case of OS remove/rescan -> wait for pci-device to be part of pci-tree')
        for pciDevList in [devList]+[devListsSD]:
            for pciDev in pciDevList:
                PciOpsObj.waitForDevice(pciDev)

        # Poll DLL Link Active (required to support AMD - RM #1599465)
        if not isPPC and not is_in_internal_host() and root_pci_device.dll_link_active_reporting_capable:   # in BlueField's internal host (ARM) the root-port will 
            MAX_WAIT_TIME = 2  # sec                                                                        # return a valid response (blocking) or 0xffff0001 when  
            poll_start_time = time.time()                                                                   # it's not ready (depending on its configuration)
            for _ in range(1000*MAX_WAIT_TIME):
                if root_pci_device.dll_link_active == 1:
                    poll_end_time = (time.time() - poll_start_time) * 1000
                    logger.debug('DLL link active is ready after {0} msec'.format(poll_end_time))
                    break
                time.sleep(0.001)
            else:
                print("\n-W- DLL link is not active (PCI device {0})".format(root_pci_device.dbdf))

        # Wait for FW (Iron) - Read devid
        MAX_WAIT_TIME = 2 # sec
        poll_start_time = time.time()
        for _ in range(1000*MAX_WAIT_TIME):
            if PciOpsObj.read(pci_device_to_poll_devid, 0)>>16 != 0xffff: # device-id (0x2.W)
                iron_end_time = (time.time() - poll_start_time) * 1000
                logger.debug('IRON is ready after {0} msec'.format(iron_end_time))
                break
            time.sleep(0.001)
        else:
            print("\n-W- FW is not ready")

        # Restore PCI configuration
        #############################
        logger.debug('Restore PCI configuration')
        if isPPC:
            logger.debug('PPC : indication for re-enumeration by MSE bit on each PCI device')
            for pciDev in devList+devListsSD:
                pci_device_object = pci_device_dict[pciDev]
                command_reg = PciOpsObj.read(pciDev, COMMAND_ADDR, "W")
                logger.debug('command_reg for [{0}]is {1:x}.'.format(pciDev, command_reg))
                if (command_reg & 0x2) == 0: # command_reg[MSE] - Indication for re-enumeration (OS rescan)
                    PciOpsObj.loadPCIConfigurationSpace(pciDev, pci_device_object, full=True)
                else:
                    PciOpsObj.loadPCIConfigurationSpace(pciDev, pci_device_object, full=False)
        else:
            logger.debug('Indication for re-enumeration is by HotPlug on bridge')
            to_restore_pci_conf = not (root_pci_device.hotplug_capable and root_pci_device.hotplug_interrupt_enable)
            logger.debug('hotplug_capable={0}'.format(root_pci_device.hotplug_capable))
            logger.debug('hotplug_interrupt_enable={0}'.format(root_pci_device.hotplug_interrupt_enable))
            logger.debug('to_restore_pci_conf={0}'.format(to_restore_pci_conf))
            for pciDev in devList+devListsSD:
                pci_device_object = pci_device_dict[pciDev]
                if to_restore_pci_conf:
                    PciOpsObj.loadPCIConfigurationSpace(pciDev, pci_device_object, full=True)
                else: # os re-enumeration
                    PciOpsObj.loadPCIConfigurationSpace(pciDev, pci_device_object, full=False)


    # Need to re-open the file handler because PCI tree is updated (OS remove/rescan)
    if isWindows is False:
        MstDevObj.open()
        for MstDevObjSD in MstDevObjsSD:
            MstDevObjSD.open()


    set_signal_handler()

    printAndFlush("Done")


def is_mellanox_device(devAddr):
    try:
        return PciOpsObj.isMellanoxDevice(devAddr)
    except NotImplementedError: # Windows
        return False

def is_pci_bridge_is_mellanox_device(devAddr):
    try:
        pci_bridge_device = PciOpsObj.getPciBridgeAddr(devAddr)
        return is_mellanox_device(pci_bridge_device)
    except NoPciBridgeException:
        return False

def send_reset_cmd_to_fw(mfrl, reset_level, reset_type, reset_sync=SyncOwner.TOOL):
    try:
        printAndFlush("-I- %-40s-" % ("Sending Reset Command To Fw"), endChar="")
        logger.debug('[Timing Test] MFRL')
        mfrl.send(reset_level, reset_type, reset_sync)
        printAndFlush("Done")
    except Exception as e:
        raise e


######################################################################
# Description: Send MFRL to FW in Multihost setup
######################################################################
def sendResetToFWSync(mfrl, reset_level, reset_type):
    status = CmdifObj.multiHostSyncStatus()
    if (status.fsm_state == SYNC_STATE_GET_READY and
                 status.fsm_sync_type != SYNC_TYPE_FW_RESET) or\
            status.fsm_state == SYNC_STATE_GO:
        raise RuntimeError("The fsm register is busy, run \"%s -d <device> reset_fsm_register\" to reset the register." % PROG)
    elif status.fsm_state == SYNC_STATE_IDLE: # First Host arrived 
        logger.debug('[Timing Test] MH SYNC send GET_READY (first host)')
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET, 0x1)
        #WA: send again because in single host case the firmware will wait for a second call (fw bug ??)
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
        logger.info('send SYNC_STATE_GET_READY command')

        try:
            send_reset_cmd_to_fw(mfrl, reset_level, reset_type)
        except CmdNotSupported:
            CmdifObj.multiHostSync(SYNC_STATE_IDLE, SYNC_TYPE_FW_RESET)
            raise RuntimeError("Command is not supported")            
        except Exception as e:
            CmdifObj.multiHostSync(SYNC_STATE_IDLE, SYNC_TYPE_FW_RESET)
            raise e

        # Socket Direct - send SYNC_STATE_GET_READY for all other devices in SD
        for CmdifObjSD in CmdifObjsSD:
            CmdifObjSD.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
            logger.info('send SYNC_STATE_GET_READY command (SD)')

    elif status.fsm_state == SYNC_STATE_GET_READY: # TODO (update after GA) and status.fsm_sync_type == SYNC_TYPE_FW_RESET
        logger.debug('[Timing Test] MH SYNC send GET_READY')
        CmdifObj.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
        logger.info('send SYNC_STATE_GET_READY command')

        # Socket Direct - send SYNC_STATE_GET_READY for all other devices in SD - to support MH device that connected as socket direct (4 'devices' on 2 servers)
        for CmdifObjSD in CmdifObjsSD:
            CmdifObjSD.multiHostSync(SYNC_STATE_GET_READY, SYNC_TYPE_FW_RESET)
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
            logger.debug('[Timing Test] Driver unbind')
        except Exception as e:
            #try again, that will prevent problems in multihost
            time.sleep(1)
            driverObj.driverStop()
        printAndFlush("Done")

######################################################################
# Description: Stop Driver in Multihost setup
######################################################################
def stopDriverSync(driverObj):

    def reloadDriver(driverObj):
        if driverObj.getDriverStatus() == MlnxDriver.DRIVER_LOADED:
            try:
                driverObj.driverStart()
                msg = " (driver was reloaded)"
            except Exception as e:
                msg = " (driver failed to reload: %s)" % str(e)
            return msg
        else:
            return ""

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
        time.sleep(0.01)

    logger.debug('[Timing Test] MH SYNC state is GO')
    if status.fsm_state != SYNC_STATE_GO or status.fsm_sync_type != SYNC_TYPE_FW_RESET:
        raise RuntimeError("Operation failed, the fsm register state or type is not as expected")
    stopDriver(driverObj)

    logger.debug('[Timing Test] MH SYNC send GO')
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
        time.sleep(0.01)

    logger.debug('[Timing Test] MH SYNC done')

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

def sendPcnr(regAccess,port_num):
    try:
        logger.debug("Sending PCNR...")
        regAccess.sendPcnr(1, port_num)
        logger.debug("Sending PCNR - Done")
    except Exception as e:
        logger.debug('Failed to send pcnr. {0}'.format(e))  # port doesn't exist / old FW version, burn FW with allow_pcnr (ini file)
        raise PcnrError

def resetFlow(device, devicesSD, reset_level, reset_type, cmdLineArgs, mfrl):
    global PciOpsObj
    logger.info('resetFlow() called')

    all_devices = [device] + devicesSD


    # A temporary solution to get the pci-device-id (required for SmartNic)
    # This solution is not good when the user insert device in PCI address format (-d xx:xx.x)
    pci_device_id = None
    if platform.system() == "Windows":
        if '_' in device_global:
            pci_device_id = int(device_global.split('_')[0][2:])


    driverObj = MlnxDriverFactory().getDriverObj(logger, skipDriver, all_devices, pci_device_id)

    try:
        # Check if device with PCIe switch (Innova, BL) is supported
        if platform.system() != "Windows" and is_pci_bridge_is_mellanox_device(DevDBDF): # Skip check on Windows OS (is_pci_bridge_is_mellanox_device is not implemented on Windows)
            if platform.system() != "Linux":
                raise RuntimeError("Resetting a device that contains a PCIe switch is supported only in Linux")
            if "ppc64" in platform.machine():
                raise RuntimeError("Resetting a device that contains a PCIe switch is not supported on PPC64")

        if SkipMultihostSync or not CmdifObj.isMultiHostSyncSupported():
            send_reset_cmd_to_fw(mfrl, reset_level, reset_type)
        else:
            sendResetToFWSync(mfrl, reset_level, reset_type)
        
        try:
            #PCNR - Reduce link up time (from ~4 sec to ~1.5 sec)
            sendPcnr(RegAccessObj, 0) # port #0 (will fail if pcnr isn't supported by FW)
            sendPcnr(RegAccessObj, 1) # port #1 (will fail if HW has only one port)
        except PcnrError:
            pass


        # # Socket direct 
        # for RegAccessSD in RegAccessObjsSD:
        #     try:
        #         sendPcnr(RegAccessSD, 0)  # port #0 (will fail if pcnr isn't supported by FW)
        #         sendPcnr(RegAccessSD, 1)  # port #1 (will fail if HW has only one port)
        #     except PcnrError:
        #         pass

        try:
            driverStat = driverObj.getDriverStatus()
        except DriverUnknownMode as e:
            print("-E- Failed to get the driver status: %s" % str(e))
            print("-E- Please make sure the driver is down, and re-run the tool with --skip_driver")
            raise e

        if reset_level == CmdRegMfrl.PCI_RESET:
            # reset PCI
            resetPciAddr(device,devicesSD,driverObj, cmdLineArgs)
        elif reset_level == CmdRegMfrl.WARM_REBOOT:
            if SkipMultihostSync or not CmdifObj.isMultiHostSyncSupported():
                stopDriver(driverObj)
            else:
                stopDriverSync(driverObj)
            rebootMachine()

        # Wait for FW to be ready to get ICMD
        try:
            wait_for_fw_ready(device)
        except: # bug 1980064 ('mst driver' is non-operational after PCI reset)
            logger.warning("wait_for_fw_ready failed. Waiting 1 sec and continue")
            time.sleep(1)
        
        logger.debug('end critical time (start to load driver)')

        if driverStat == MlnxDriver.DRIVER_LOADED:
            printAndFlush("-I- %-40s-" % ("Starting Driver"), endChar="")
            logger.debug('[Timing Test] Driver Bind')
            driverObj.driverStart()
            printAndFlush("Done")

        logger.debug('UpdateUptimeAfterReset')
        FWResetStatusChecker.UpdateUptimeAfterReset()
    
        # we close MstDevObj to allow a clean operation of mst restart
        MstDevObj.close()
        for MstDevObjSD in MstDevObjsSD:    #Roei close mst devices for all "other" devices
            MstDevObjSD.close()


        if SkipMstRestart == False and platform.system() == "Linux" and not IS_MSTFLINT:
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
# Description: Warm reboot reset Flow
######################################################################
def rebootMachine():
    printAndFlush("-I- %-40s-" % ("Sending reboot command to machine"), endChar="")
    if platform.system() == "Windows":
        cmd = "shutdown /r"
    else:
        cmd = "reboot"
    rc, _, _ = cmdExec(cmd)
    if rc == 0:
        printAndFlush("Done")
    else:
        printAndFlush("Failed")
        raise RuntimeError("Failed to reboot machine please reboot machine manually")
    
######################################################################
# Description:  execute reset level for device
######################################################################
def execResLvl(device, devicesSD, reset_level, reset_type, reset_sync, cmdLineArgs, mfrl):
    
    # mpcir usage removed due to RM #2214400
    # # In new FW, the FW doesn't need this command any more
    # if mfrl.is_phy_less_reset(reset_type):
    #     logger.debug('[Timing Test] MPCIR')
    #     mpcir.prepare_for_phyless_fw_upgrade()

    if reset_level == mfrl.LIVE_PATCH:
        send_reset_cmd_to_fw(mfrl, reset_level, reset_type)
    elif reset_level in [mfrl.PCI_RESET, mfrl.WARM_REBOOT]:
        if reset_sync == SyncOwner.DRIVER:
            send_reset_cmd_to_fw(mfrl, reset_level, reset_type, reset_sync)
        else:
            resetFlow(device, devicesSD, reset_level, reset_type, cmdLineArgs, mfrl)
    else:
        raise RuntimeError("Unknown reset level")


######################################################################
# Description:  Search given mst status output for net entity device name
#               and return mst device path.
# OS Support : Linux
######################################################################

def map2DevPathAux(mstOutput, device):
    for l in mstOutput.split('\n'):
        lineList = l.split()
        if device in lineList:
            if len(lineList) > 2:
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

    parser = argparse.ArgumentParser(description=DESCRIPTION,
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     prog=PROG,
                                     epilog=CmdRegMfrl.descriptions(),
                                     add_help=False)

    # options arguments
    options_group = parser.add_argument_group('Options')
    options_group.add_argument('--device',
                        '-d',
                        required=True,
                        help='Device to work with')
    options_group.add_argument('--level',
                        '-l',
                        type=int,
                        choices=CmdRegMfrl.reset_levels(),
                        dest='reset_level',
                        help='Run reset with the specified reset-level')
    options_group.add_argument('--type',
                        '-t',
                        type=int,
                        choices=CmdRegMfrl.reset_types(),
                        dest='reset_type',
                        help='Run reset with the specified reset-type')
    options_group.add_argument('--sync',
                        type=int,
                        choices=[SyncOwner.TOOL, SyncOwner.DRIVER],
                        default=SyncOwner.TOOL,
                        dest='reset_sync',
                        help='Run reset with the specified reset-sync')
    options_group.add_argument('--yes',
                        '-y',
                        help='answer "yes" on prompt',
                        action="store_true")
    options_group.add_argument('--skip_driver',
                        '-s',
                        help="Skip driver start/stop stage (driver must be stopped manually)",
                        action="store_true")
    options_group.add_argument('--mst_flags',
                        '-m',
                        help="Provide mst flags to be used when invoking mst restart step. For example: --mst_flags=\"--with_fpga\""
                        if platform.system() == "Linux" and not IS_MSTFLINT else argparse.SUPPRESS)
    options_group.add_argument('--version',
                        '-v',
                        help='Print tool version',
                        action="version",
                        version=tools_version.GetVersionString(PROG, TOOL_VERSION))
    options_group.add_argument('--help',
                        '-h',
                        help='show this help message and exit',
                        action="help")

    # hidden flag for skipping mst restart when performing pci reset
    options_group.add_argument('--no_mst_restart',
                               action="store_true",
                               help=argparse.SUPPRESS)
    # hidden flag for specifying the host bridge of the device for the PCI reset stage
    options_group.add_argument('--pci_bridge',
                               nargs=1,
                               help=argparse.SUPPRESS)
    options_group.add_argument('--skip_fsm_sync',
                               action="store_true",
                               help=argparse.SUPPRESS)

    # Skip on the self discover devices logic for socket direct(option to disable the feature in case of bug)
    options_group.add_argument('--skip_socket_direct',
                               action="store_true",
                               help=argparse.SUPPRESS)
    # log level
    options_group.add_argument('--log',
                               choices=['critical','error','warning','info','debug'],
                               help=argparse.SUPPRESS)

    def check_positive_float(val):
        try:
            val = float(val)
            assert val>=0
        except:
            raise argparse.ArgumentTypeError("{0} is an invalid positive float value".format(val))

        return val


    # configuration of sleep-time (sec) between 'disable-pci' to 'enable-pci'
    options_group.add_argument('--pci_link_downtime',
                               type=check_positive_float,
                               default=1.25,
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
    global SkipMultihostSync
    global DevDBDF
    global FWResetStatusChecker

    if args.reset_sync == SyncOwner.TOOL and is_uefi_secureboot():        # The tool is using sysfs to access PCI config and it's
        raise RuntimeError("The tool is not supported on UEFI Secure Boot") # restricted on UEFI secure boot

    # Exit in case of virtual-machine (not implemented for FreeBSD and Windows)
    if command == "reset" and platform.system() == "Linux" and "ppc64" not in platform.machine():
        rc, out, _ = cmdExec('lscpu')
        if rc == 0:
            if "Hypervisor vendor" in out:
                raise RuntimeError("The tool is not supported on virtual machines")
        else:
            logger.debug("Failed to execute 'lscpu' command rc = {0}".format(rc))




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
    isDevSupp(device) # function takes ~330msec - TODO remove it if you need performace

    DevDBDF = mlxfwreset_utils.getDevDBDF(device,logger)
    logger.info('device domain:bus:dev.fn (DBDF) is {0}'.format(DevDBDF))
    SkipMstRestart = args.no_mst_restart
    skipDriver = args.skip_driver
    SkipMultihostSync = args.skip_fsm_sync
    MstDevObj = mtcr.MstDevice(device)
    RegAccessObj = regaccess.RegAccess(MstDevObj)    
    CmdifObj = cmdif.CmdIf(MstDevObj)
    PciOpsObj = MlnxPciOpFactory().getPciOpObj(DevDBDF)


    mfrl = CmdRegMfrl(RegAccessObj)
    # mpcir = CmdRegMpcir(RegAccessObj)
    mcam = CmdRegMcam(RegAccessObj)

    logger.info('Check if device is livefish')
    DevMgtObj = dev_mgt.DevMgt(MstDevObj) # check if device is in livefish
    if DevMgtObj.isLivefishMode() == 1:
        raise RuntimeError("%s is not supported for device in Flash Recovery mode" % PROG)

    # Check if other process is accessing the device (burning the device)
    # Supportted on Windows OS only
    if platform.system() == "Windows":
        from tools_sync import ToolsSync
        if ToolsSync(MstDevObj.mf).lock() == False:
            raise RuntimeError("Other tool is accessing the device! Please try again latter")    


    # Socket Direct - Create a list of command i/f for all "other" devices
    global CmdifObjsSD
    global MstDevObjsSD
    global RegAccessObjsSD


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
                RegAccessObjsSD.append(regaccess.RegAccess(MstDevObjsSD[-1]))
                CmdifObjsSD.append(cmdif.CmdIf(MstDevObjsSD[-1]))
        except:
            logger.warning("Failed to check if device is Socket Direct!")
            devicesSD = []
            for MstDevObjSD in MstDevObjsSD:
                MstDevObjSD.close()
            MstDevObjsSD = []
            CmdifObjsSD = []
            RegAccessObjsSD = []

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
        print(mfrl.query_text())
        print(mcam.reset_sync_query_text())

    elif command == "reset":

        #print("Reset device {0}:".format(device))


        reset_level = mfrl.default_reset_level() if args.reset_level is None else args.reset_level
        # print("  * reset-level is '{0}' ({1})".format(reset_level, mfrl.reset_level_description(reset_level)))
        if mfrl.is_reset_level_supported(reset_level) is False:
            raise RuntimeError("Reset-level '{0}' is not supported in the current state of this device".format(reset_level))

        reset_type = mfrl.default_reset_type() if args.reset_type is None else args.reset_type
        # print("  * reset-type  is '{0}' ({1})".format(reset_type, mfrl.reset_type_description(reset_type)))
        if mfrl.is_reset_type_supported(reset_type) is False:
            raise RuntimeError("Reset-type '{0}' is not supported in the current state of this device".format(reset_type))

        if args.reset_type and mfrl.is_reset_level_support_reset_type(reset_level) is False:
            raise RuntimeError("Reset-level '{0}' is not supported with reset-type '{1}'".format(reset_level, reset_type))

        reset_sync = args.reset_sync
        if reset_sync == SyncOwner.DRIVER and mcam.is_reset_by_fw_driver_sync_supported() is False:
            raise RuntimeError("Synchronization by driver is not supported in the current state of this device")
        if reset_sync != SyncOwner.TOOL and reset_level != CmdRegMfrl.PCI_RESET:
            raise RuntimeError("Reset-sync '{0}' is not supported with reset-level '{1}'".format(reset_sync, reset_level))
        
        minimal_or_requested = 'Minimal' if args.reset_level is None else 'Requested'
        print("{0} reset level for device, {1}:\n".format(minimal_or_requested , device))
        print("{0}: {1}".format(reset_level,mfrl.reset_level_description(reset_level)))


        AskUser("Continue with reset", yes)
        execResLvl(device, devicesSD, reset_level, reset_type, reset_sync, args, mfrl)
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
        set_signal_handler()
        rc = main()
    except NoError as e:
        print("-I- %s." % str(e))
    except WarningException as e:
        print("-W- %s." % str(e))
    except Exception as e:
        print("-E- %s." % str(e))
        rc = 1
    sys.exit(rc)
