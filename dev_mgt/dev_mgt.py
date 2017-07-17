#--
#                 - Mellanox Confidential and Proprietary -
#
# Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
#
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#--

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
except Exception, exp:
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


if __name__ == "__main__":
    mstdev = "/dev/mst/mt523_pciconf0"
    #mstdev = "/dev/mst/mt4113_pciconf0"
    devMgt = DevMgt(mstdev)
    print devMgt.isLivefishMode()