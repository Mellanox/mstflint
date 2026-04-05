
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

import os
import sys
import platform
import ctypes
import struct


def ones(n):
    return (1 << n) - 1


def extractField(val, start, size):
    return (val & (ones(size) << start)) >> start


def insertField(val1, start1, val2, start2, size):
    return val1 & ~(ones(size) << start1) | (extractField(val2, start2, size) << start1)


class MtcrException(Exception):
    pass


class CmdIfException(Exception):
    pass


##########################
CMTCR = None
try:
    from ctypes import *
    ctypes.CDLL._func_restype_ = ctypes.c_ulonglong
    if platform.system() == "Windows" or os.name == "nt":
        try:
            CMTCR = CDLL("libmtcr-1.dll", use_errno=True)
        except BaseException:
            CMTCR = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "libmtcr-1.dll"), use_errno=True)
    else:
        try:
            CMTCR = CDLL("cmtcr.so", use_errno=True)
        except BaseException:
            CMTCR = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "cmtcr.so"), use_errno=True)
except BaseException as e:
    print("Error loading CMTCR: {0}".format(e))
    CMTCR = None

if CMTCR:
    class MstDevice:
        ##########################
        def __init__(self, dev):
            self.mdev = dev.encode('ascii')
            self.mf = 0
            self.mopenFunc = CMTCR.mopen
            self.mopenFunc.restype = c_void_p
            self.mopenFuncAdv = CMTCR.mopen_adv
            self.mopenFuncAdv.argtypes = [ctypes.c_char_p, ctypes.c_uint]
            self.mcloseFunc = CMTCR.mclose
            self.mread4Func = CMTCR.mread4
            self.mwrite4Func = CMTCR.mwrite4
            self.mread4BlockFunc = CMTCR.mread4_block
            self.mwrite4BlockFunc = CMTCR.mwrite4_block
            self.icmdSendCommandFunc = CMTCR.icmd_send_command
            self.mHcaResetFunc = CMTCR.mhca_reset
            self.open()
            self.is_remote_dev = CMTCR.is_remote_dev
            self.is_gpu_device = CMTCR.is_gpu_device
            self.readDeviceIdFunc = CMTCR.read_device_id
            self.hotResetFunc = CMTCR.hot_reset
        ##########################
        def close(self):
            if self.mf:
                self.mcloseFunc(self.mf)
            self.mf = None

        def is_cable(self):
            return '_cable' in str(self.mdev)

        def is_linkx(self):
            return '_lx' in str(self.mdev)

        def open(self):
            if self.is_cable() or self.is_linkx():
                self.mf = ctypes.c_void_p(self.mopenFuncAdv(self.mdev, 0xffffffff))
            else:
                self.mf = ctypes.c_void_p(self.mopenFunc(self.mdev))

            if not self.mf:
                error = os.strerror(ctypes.get_errno())
                raise MtcrException("Failed to re-open device (%s): %s" % (self.mdev.decode("utf-8"), error))

        ##########################
        def __del__(self):
            self.close()

        ##########################
        def read4(self, addr):
            val = c_uint32()
            if self.mread4Func(self.mf, addr, byref(val)) != 4:
                raise MtcrException("Failed to read from mst device from address: 0x%x" % addr)

            return val.value

        ##########################
        def readField(self, addr, startBit, size):
            return extractField(self.read4(addr), startBit, size)

        ##########################
        def write4(self, addr, val):
            cval = c_uint32(val)
            if self.mwrite4Func(self.mf, addr, cval) != 4:
                raise MtcrException("Failed to write to mst device to address: 0x%x" % addr)

        ##########################
        def writeField(self, val, addr, startBit, size):
            oldVal = self.read4(addr)
            newVal = insertField(oldVal, startBit, val, 0, size)

            self.write4(addr, newVal)

        ##########################
        def read4Block(self, addr, size):  # size in dwords
            dataArr = (c_uint32 * size)()
            if self.mread4BlockFunc(self.mf, addr, cast(dataArr, POINTER(c_uint32)), size * 4) != size * 4:
                raise MtcrException("Failed to read block from mst device from address 0x%x of size %d bytes" % (addr, size))
            return list(dataArr)

        ##########################
        def write4Block(self, addr, dataList):
            size = len(dataList)
            dataArr = (c_uint32 * size)(*dataList)
            if self.mwrite4BlockFunc(self.mf, addr, cast(dataArr, POINTER(c_uint32)), size * 4) != size * 4:
                raise MtcrException("Failed to write block to mst device to address 0x%x of size %d bytes" % (addr, size))

        ##########################
        def icmdSendCmd(self, opcode, data, skipWrite):
            dataArr = (c_uint8 * len(data))(*data)
            rc = self.icmdSendCommandFunc(self.mf, opcode, cast(dataArr, POINTER(c_uint8)), len(data), skipWrite)

            # data can also be used as output so need to convert back from dataArr.
            for i, x in enumerate(dataArr):
                data[i] = dataArr[i]
            if rc:
                raise CmdIfException("Failed to send command")
        ##########################
        def mHcaReset(self, dbdf_list):

            bus_array_size = len(dbdf_list)

            bus_array = (ctypes.c_ulong * bus_array_size)()

            # Extract the bus value from the dbdf list.
            for idx, dbdf in enumerate(dbdf_list):
                bus_array[idx] = int(dbdf[5:7], 16)

            if self.mHcaResetFunc(self.mf, bus_array, bus_array_size) != 0:
                raise MtcrException("Failed to reset device")

        ##########################
        def getPCIDeviceRdma(self):
            dev_rdma = ctypes.create_string_buffer(32)
            CMTCR.get_pci_dev_rdma(self.mf, dev_rdma)
            rdma_str = dev_rdma.value.decode("utf-8")
            return rdma_str

        def is_remote_device(self):
            return self.is_remote_dev(self.mf)
        
        def isGPUDevice(self):
            dev_id = self.read_device_id()
            return self.is_gpu_device(dev_id)

        def read_device_id(self):
            dev_id = c_uint32()
            if self.readDeviceIdFunc(self.mf, byref(dev_id)) != 4:
                raise MtcrException("Failed to read device ID")
            return dev_id.value

        def send_hot_reset(self, in_parallel, domain_1, bus_1, device_1, function_1, domain_2, bus_2, device_2, function_2):
            return self.hotResetFunc(self.mf, in_parallel, domain_1, bus_1, device_1, function_1, domain_2, bus_2, device_2, function_2)
        ##########################

else:
    import subprocess
    import string

    def getstatusoutput(cmd):
        pipe = subprocess.Popen(cmd, shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        cout = pipe.stdout
        output = cout.read()
        cout.close()
        rc = pipe.wait()
        return rc, output

    class MstDevice:
        ##########################
        def __init__(self, dev):
            self.dev = dev
            self.mf = 0

        ##########################
        def is_cable(self):
            return '_cable' in str(self.dev)

        ##########################
        def is_linkx(self):
            return '_lx' in str(self.dev)

        ##########################
        def close(self):
            pass

        ##########################
        def read4(self, addr):
            cmd = ["mcra", self.dev, hex(addr)]
            rc, out = getstatusoutput(cmd)
            if rc:
                raise MtcrException("Failed to read from mst device from address 0x%x: %s" % (addr, out))
            return int(out, 16)

        ##########################
        def readField(self, addr, startBit, size):
            return extractField(self.read4(addr), startBit, size)

        ##########################
        def write4(self, addr, val):
            cmd = ["mcra", self.dev, hex(addr), hex(val)]
            rc, out = getstatusoutput(cmd)
            if rc:
                raise MtcrException("Failed to wrtie to mst device to address 0x%x: %s" % (addr, out))

        ##########################
        def writeField(self, val, addr, startBit, size):
            oldVal = self.read4(addr)
            newVal = insertField(oldVal, startBit, val, 0, size)
            self.write4(addr, newVal)

        ##########################
        def read4Block(self, addr, size):  # size in dwords
            l = []
            for add in range(addr, addr + size * 4, 4):
                l.append(self.read4(add))
            return l

        ##########################
        def write4Block(self, addr, dataList):
            size = len(dataList)
            for i, current_addr in enumerate(range(addr, addr + size * 4, 4)):
                self.write4(current_addr, dataList[i])

        ##########################
        def icmdSendCmd(self, opcode, data, skipWrite):
            raise MtcrException("icmd isn't supported in MCRA mode")

        ##########################
        def mHcaReset(self, dbdf_list):
            raise MtcrException("mswReset isn't supported in MCRA mode")
