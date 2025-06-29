# Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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


import sys
import os

# Clear LD_LIBRARY_PATH to prevent pyinstaller compatibility issues
library_path_var = "LD_LIBRARY_PATH"
is_pyinstaller = getattr(sys, 'frozen', False)
if is_pyinstaller and library_path_var in os.environ:
    os.environ[library_path_var] = ""

import signal
import argparse
from secure_fw_trace import SecureFwTrace
from fw_trace_utilities import FwTraceUtilities
import tools_version

# MFT imports
sys.path.append(os.path.join("..", "..", "common"))
sys.path.append(os.path.join("..", "..", "mtcr_py"))
sys.path.append(os.path.join("..", "..", "cmdif"))
import mtcr  # noqa
import cmdif  # noqa


class UnbufferedStream(object):
    def __init__(self, stream):
        self.stream = stream
    def write(self, data):
        self.stream.write(data)
        self.stream.flush()
    def writelines(self, datas):
        self.stream.writelines(datas)
        self.stream.flush()
    def __getattr__(self, attr):
        return getattr(self.stream, attr)


sys.stdout = UnbufferedStream(sys.stdout)


EXEC_NAME = "mstfwtrace"
proc = None


# Exception class
class TracerException(Exception):
    pass


# Constants

#######################################################
HCA_MASK_CLASSES = [
    ("DEBUG_INIT", 0), ("INIT", 1), ("ICM", 2), ("ICM_FREE_LIST", 3),
    ("HOST_MNG", 4), ("CMD_IF", 5), ("PHY_IB", 6), ("PHY_RX_ADAP", 7),
    ("LIBFHI", 8), ("PHY_COMMON", 9), ("PHY_MANAGER", 10),
    ("PWR", 11), ("FLR", 12), ("ICM_ACCESS", 13),
    ("MAD", 14), ("RXT_CHECKS", 15), ("I2C", 16), ("TRANSPORT", 17),
    ("FW_LL", 18), ("RX_ERRORS", 19), ("CMD_DRIVER", 20), ("PROFILING", 21),
    ("MANAGEMENT", 22), ("FLASH", 23), ("STEERING", 24),
    ("IFARM", 25), ("ICMD", 26), ("PCI", 27), ("DC_CLEANUP", 28),
    ("PHY_ETH", 29), ("VIRT", 30)]  # list of (trace type name, start_bit)

DEV_INFO_DB = [
    # we use list instead of dict to keep order,
    # new devices should be at head of the list
    {
        "name": "ConnectIB",
        "dev_id": [0x1ff],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "SwitchIB",
        "dev_id": [0x247],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "ConnectX4",
        "dev_id": [0x209],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "ConnectX5",
        "dev_id": [0x20d],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "BlueField",
        "dev_id": [0x211],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "BlueField2",
        "dev_id": [0x214],
        "chip_rev":-1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
        "default_tracer_mode": "MEM"
    },
    {
        "name": "BlueField3",
        "dev_id": [0x21c],
        "chip_rev":-1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
        "default_tracer_mode": "MEM"
    },
    {
        "name": "ConnectX6",
        "dev_id": [0x20f],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "ConnectX6DX",
        "dev_id": [0x212],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "Spectrum",
        "dev_id": [0x249],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "ConnectX4LX",
        "dev_id": [0x20b],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "SwitchIB2",
        "dev_id": [0x24B],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "Quantum",
        "dev_id": [0x24D],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "Spectrum2",
        "dev_id": [0x24E],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "Spectrum3",
        "dev_id": [0x250],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "Spectrum4",
        "dev_id": [0x254],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "ConnectX6LX",
        "dev_id": [0x216],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "ConnectX7",
        "dev_id": [0x218],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "Quantum2",
        "dev_id": [0x257],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": [("class1", 0), ("class2", 1)],
    },
    {
        "name": "ConnectX8",
        "dev_id": [0x21e],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
    {
        "name": "ConnectX9",
        "dev_id": [0x224],
        "chip_rev": -1,
        "maskable": True,
        "mask_addr": None,
        # list of (trace type name, start_bit)
        "mask_classes": list(HCA_MASK_CLASSES),
    },
]
MST_DEVICE = None
CMDIFDEV = None
DEV_NAME = None
IRISC_NAME = None
MASK = None
LEVEL = None
STRAMING_MODE = False
TRACER_MODE = None
REAL_TS = False
IGNORE_OLD_EVENTS = False


def add_args():
    """
    Adding tool arguments and options
    """
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter,
                                     prog=EXEC_NAME,
                                     epilog=get_epilog(),
                                     usage="%s -d|--device DEVICE [options]" % EXEC_NAME)
    parser.add_argument("-v", "--version", '-v', help='Print tool version.', action="version", version=tools_version.GetVersionString(EXEC_NAME, None))
    options_group = parser.add_argument_group('Options')
    options_group.add_argument("-d", "--device", dest="device", help="PCI device name", default=None)
    options_group.add_argument("--tracer_mode", dest="tracer_mode", help="Tracer mode [MEM]", default="MEM")
    options_group.add_argument("--real_ts", action="store_true", dest="real_ts", help="Print real timestamps in [hh:mm:ss:nsec]", default=False)
    options_group.add_argument("--ignore_old_events", action="store_true", dest="ignore_old_events", help="Ignore collecting old events", default=False)
    format_group = parser.add_argument_group('Format')
    format_group.add_argument("-i", "--irisc", dest="irisc", help="Irisc name [all]", default="all")
    format_group.add_argument("-s", "--stream", action="store_true", dest="stream", help="Run in streaming mode", default=False)
    format_group.add_argument("-m", "--mask", dest="mask", help="Trace class mask, use \"+\" to enable multiple classes or use integer format, e.g: -m "
                              "class1+class2+... or 0xff00ff00", default=None)
    format_group.add_argument("-l", "--level", dest="level", help="Trace level", default=None)
    return parser


def parse_cmd_line_args():
    args = add_args().parse_args()
    global DEV_NAME
    global IRISC_NAME
    global MASK
    global LEVEL
    global STRAMING_MODE
    global TRACER_MODE
    global REAL_TS
    global IGNORE_OLD_EVENTS

    DEV_NAME = args.device
    IRISC_NAME = args.irisc
    MASK = args.mask
    LEVEL = args.level
    STRAMING_MODE = args.stream
    TRACER_MODE = args.tracer_mode
    REAL_TS = args.real_ts
    IGNORE_OLD_EVENTS = args.ignore_old_events

    if IRISC_NAME != "all":
        raise TracerException("Only 'all' irisc is compatible with this tracer version")
    if TRACER_MODE != "MEM":
        raise TracerException("Only 'MEM' tracer mode is compatible with this tracer version")


def check_secure_fw_args(devInfo):
    maskable = devInfo["maskable"]
    if maskable is None or maskable is False:
        if MASK is not None:
            raise TracerException("This device traces can't be masked")
    if MASK and not is_int_or_hex(MASK):
        classes = MASK.split("+")
        for klass in classes:
            valid_class = False
            for mask_cls in devInfo["mask_classes"]:
                if mask_cls[0] == klass:
                    valid_class = True
            if not valid_class:
                raise TracerException("Unknown trace class: %s" % klass)
    if (MASK and LEVEL is None) or (LEVEL and MASK is None):
        raise TracerException("Both --mask and --level must be provided")


def get_device_info(dev):
    # check if livefish mode before continue to work with the device
    CMDIFDEV.getFwInfo()

    devIdChipRev = dev.read4(0xf0014)
    devId = devIdChipRev & 0xffff
    chipRev = (devIdChipRev >> 16) & 0xf

    for devInfo in DEV_INFO_DB:
        if devId in devInfo["dev_id"] and \
                (devInfo["chip_rev"] == -1 or devInfo["chip_rev"] == chipRev):
            return devInfo

    raise TracerException(
        "Unknown/Unsupported device with DevId: 0x%x and ChipRev: 0x%x" %
        (devId, chipRev))


def get_epilog():
    classes_info = "Device Specific Info:\n====================\n"
    for devInfo in DEV_INFO_DB:
        classes_info = "%s\n    %s:" % (classes_info, devInfo["name"])
        # Print itrace classes
        if devInfo['maskable']:
            trace_levels = []
            for m in devInfo["mask_classes"]:
                trace_levels.append(m[0])

            classes_info = "%s\n    Trace classes:" % classes_info
            for i in range(0, len(trace_levels), 5):
                classes_info = "%s\n         %s" % (classes_info, ", ".join(trace_levels[i: i + 5]))
    return classes_info


def is_int_or_hex(string):
    try:
        int(string)
        return True
    except ValueError:
        try:
            int(string, base=16)
            return True
        except ValueError:
            return False

def is_int_or_hex_test():
    test_cases = ['123', 'quetzalcoatl', '456', 'k1a2l2imba',  '789', '0xFF', '0x1A3B']
    print([is_int_or_hex(x) for x in test_cases])

def apply_mask(devInfo, dev, cmdifdev):
    if not MASK:
        return 0

    maskAddr = devInfo["mask_addr"]

    try:
        level = int(LEVEL)
    except ValueError:
        raise ValueError("Trace level is expected to be a numeric")

    if is_int_or_hex(MASK):
        try:
            mask = int(MASK)
        except ValueError:
            try:
                mask = int(MASK, base=16)
            except ValueError:
                raise ValueError("Internal error")
    else:
        maskClasses = devInfo["mask_classes"]
        reqClasses = MASK.split("+")
        mask = 0
        for reqClass in reqClasses:
            found = False
            for c in maskClasses:
                if c[0] == reqClass:
                    mask += 1 << c[1]
                    found = True
                    break
            if not found:
                raise TracerException("Unknown trace class: %s" % reqClass)

    if maskAddr:
        dev.write4(maskAddr[0], mask)
        dev.write(maskAddr[0] + 4, level)
    elif cmdifdev:
        cmdifdev.setItrace(mask, level)


def open_mst_dev():
    global MST_DEVICE
    global CMDIFDEV
    if MST_DEVICE is None:
        MST_DEVICE = mtcr.MstDevice(DEV_NAME)
        if CMDIFDEV is not None:
            CMDIFDEV = cmdif.CmdIf(MST_DEVICE)


def start_tracer():

    try:
        parse_cmd_line_args()
        if not DEV_NAME:
            raise TracerException("Missing device name, please provide device name. Check help [--help]")
        global MST_DEVICE
        global CMDIFDEV
        MST_DEVICE = mtcr.MstDevice(DEV_NAME)
        CMDIFDEV = cmdif.CmdIf(MST_DEVICE)
        devInfo = get_device_info(MST_DEVICE)

        if FwTraceUtilities.is_driver_mem_mode_supported():
            try:
                check_secure_fw_args(devInfo)
                secure_fw_tracer = SecureFwTrace(MST_DEVICE, DEV_NAME, IGNORE_OLD_EVENTS, REAL_TS)
                open_mst_dev()
                apply_mask(devInfo, MST_DEVICE, CMDIFDEV)
                secure_fw_tracer.parse_driver_mem()
            except Exception as exp:
                print("-E- %s" % exp)
        else:
            raise TracerException("Driver mem mode is not supported")

    except Exception as exp:
        print("-E- %s" % exp)
        return 1

    return 0


def signal_handler(signal, frame):
    print("\nInterrupted, exiting ...")
    global proc
    if proc is not None:
        proc.terminate()
        proc.wait()
        proc = None
    sys.exit(0)


if __name__ == "__main__":
    try:
        signal.signal(signal.SIGINT, signal_handler)
        rc = start_tracer()
    except Exception as exp:
        try:
            print("-E- %s" % str(exp))
        except BaseException:
            pass
        rc = 1
    sys.exit(rc)
