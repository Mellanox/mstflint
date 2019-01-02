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
        DEV_MGT = CDLL("c_dev_mgt.dll")
    else:
        try:
            #c_dev_mgt.so must be specified explicitly for pyinstaller collection
            DEV_MGT = CDLL("c_dev_mgt.so")
        except:
            DEV_MGT = CDLL(os.path.join(os.path.dirname(os.path.realpath(__file__)), "c_dev_mgt.so"))
except Exception as exp:
    raise DevMgtException("Failed to load shared library c_dev_mgt: %s" % exp)

if DEV_MGT:
    class DevMgt:
        ##########################
        def __init__(self, dev):
            self.mf = 0
            self._isLivefishModeFunc = DEV_MGT.dm_is_livefish_mode  # dm_is_livefish_mode(mfile* mf)   
            if isinstance(dev,(mtcr.MstDevice)):
              self._mstdev = dev
            else:
                self._mstdev  =  mtcr.MstDevice(dev) 
                if not self._mstdev:
                    raise DevMgtException("Failed to open device (%s): %s" % (dev, os.strerror(ctypes.get_errno())))

        
        ##########################
        def isLivefishMode(self):
            rc = self._isLivefishModeFunc(self._mstdev.mf)
            return not (rc == 0)
else:
    raise DevMgtException("Failed to load c_dev_mgt.so/libdev_mgt.dll") 
