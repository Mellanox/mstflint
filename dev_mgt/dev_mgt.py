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

from __future__ import print_function
import os
import sys
import platform
import ctypes
import mtcr


class DevMgtException(Exception):
    pass


##########################
DEV_MGT = None
try:
    from ctypes import *
    if platform.system() == "Windows" or os.name == "nt":
        try:
            DEV_MGT = CDLL("c_dev_mgt.dll")
        except BaseException:
            DEV_MGT = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "c_dev_mgt.dll"))
    else:
        try:
            # c_dev_mgt.so must be specified explicitly for pyinstaller collection
            DEV_MGT = CDLL("c_dev_mgt.so")
        except BaseException:
            DEV_MGT = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "c_dev_mgt.so"))
except Exception as exp:
    raise DevMgtException("Failed to load shared library c_dev_mgt: %s" % exp)

if DEV_MGT:
    class DevMgt:
        ##########################
        def __init__(self, dev, i2c_secondary=-1):
            self.mf = 0
            self._isLivefishModeFunc = DEV_MGT.dm_is_livefish_mode  # dm_is_livefish_mode(mfile* mf)
            self._getDeviceIdFunc = DEV_MGT.dm_get_device_id
            self._isIBAccess = DEV_MGT.dm_is_ib_access
            if isinstance(dev, (mtcr.MstDevice)):
                self._mstdev = dev
            else:
                self._mstdev = mtcr.MstDevice(dev, i2c_secondary)
                if not self._mstdev:
                    raise DevMgtException("Failed to open device (%s): %s" % (dev, os.strerror(ctypes.get_errno())))

        ##########################
        def isLivefishMode(self):
            rc = self._isLivefishModeFunc(self._mstdev.mf)
            return not (rc == 0)

        ##########################
        def getHwId(self):
            dm_dev_id = ctypes.c_uint16()
            hw_dev_id = ctypes.c_uint32()
            hw_rev = ctypes.c_uint32()

            rc = DEV_MGT.dm_get_device_id(self._mstdev.mf, ctypes.byref(dm_dev_id), ctypes.byref(hw_dev_id), ctypes.byref(hw_rev))
            return {"return_code": rc, "dm_device_id": dm_dev_id, "hw_device_id": hw_dev_id, "hw_revision": hw_rev}

        @classmethod
        def getDevIdOffline(cls, hw_dev_id):
            dm_dev_id = ctypes.c_uint16()
            rc = DEV_MGT.dm_get_device_id_offline(hw_dev_id, -1, ctypes.byref(dm_dev_id))
            return {"return_code": rc, "dm_device_id": dm_dev_id, "hw_device_id": hw_dev_id, "hw_revision": -1}

        @classmethod
        def str2hwId(cls, name):
            name_char_p = ctypes.c_char_p(name.lower().encode('utf-8'))
            dm_dev_id = ctypes.c_uint16()
            hw_dev_id = ctypes.c_uint32()
            hw_rev = ctypes.c_uint32()

            dm_dev_id = DEV_MGT.dm_dev_aproxstr2type(name_char_p)

            rc = 0
            hw_dev_id = DEV_MGT.dm_get_hw_dev_id(dm_dev_id)
            hw_rev = DEV_MGT.dm_get_hw_rev_id(dm_dev_id)

            if (hw_dev_id == 0 or hw_rev == 0):
                rc = 1

            return {"return_code": rc, "dm_device_id": dm_dev_id, "hw_device_id": hw_dev_id, "hw_revision": hw_rev}

        @classmethod
        def type2str(cls, dm_dev_id):
            DEV_MGT.dm_dev_type2str.restype = ctypes.c_char_p
            return DEV_MGT.dm_dev_type2str(dm_dev_id).decode("utf-8")

        @classmethod
        def is_ib_switch(cls, dm_dev_id):
            return DEV_MGT.dm_dev_is_ib_switch(dm_dev_id)

        @classmethod
        def is_connectib(cls, dm_dev_id):
            return DEV_MGT.dm_is_connectib(dm_dev_id)

        @classmethod
        def is_gpu(cls, dm_dev_id):
            return DEV_MGT.dm_is_gpu(dm_dev_id)

        @classmethod
        def is_cx7(cls, dm_dev_id):
            return DEV_MGT.dm_is_cx7(dm_dev_id)

        @classmethod
        def is_fs3(cls, dm_dev_id):
            return DEV_MGT.dm_dev_is_fs3(dm_dev_id)

        @classmethod
        def is_fs4(cls, dm_dev_id):
            return DEV_MGT.dm_dev_is_fs4(dm_dev_id)

        @classmethod
        def is_fs5(cls, dm_dev_id):
            return DEV_MGT.dm_dev_is_fs5(dm_dev_id)

        @classmethod
        def is_4th_gen(cls, dm_dev_id):
            return DEV_MGT.dm_is_4th_gen(dm_dev_id)

        @classmethod
        def sw_id2hw_id(cls, sw_dev_id):
            dm_dev_id = DEV_MGT.dm_dev_sw_id2type(sw_dev_id)
            rc = 0
            hw_dev_id = DEV_MGT.dm_get_hw_dev_id(dm_dev_id)
            hw_rev = DEV_MGT.dm_get_hw_rev_id(dm_dev_id)

            if (hw_dev_id == 0 or hw_rev == 0):
                rc = 1

            return {"return_code": rc, "dm_device_id": dm_dev_id, "hw_device_id": hw_dev_id, "hw_revision": hw_rev}

        def is_ib_access(self):
            return (self._isIBAccess(self._mstdev.mf) != 0)
else:
    raise DevMgtException("Failed to load c_dev_mgt.so/libdev_mgt.dll")
