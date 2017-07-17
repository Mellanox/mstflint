#!/usr/bin/env python
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


import mtcr

device = "/dev/mst/l-apps08:23108,@dev@mst@mt26448_pci_cr0"
device = "/dev/mst/mt26448_pciconf0"
device = "mlx4_core0@pci0:0:5:0"
mf = mtcr.MstDevice(device)
print "0x%x" % mf.read4(0xf0014)
for d in mf.read4Block(0xf0014, 8):
    print "[0x%08x]" % d

mf.write4Block(0xf0014, [0, 0, 0, 0, 0, 0, 0, 0])
