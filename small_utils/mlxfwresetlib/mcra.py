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
* $Id           : mcra.py 2017-11-28
* $Authors      : Roei Yitzhak (roei@mellanox.com)
"""

from __future__ import print_function
import platform
from .mlxfwreset_utils import cmdExec

class Mcra(object):

    def __init__(self):

        self.mcra_cmd = self.pick_mcra_cmd() # mcra or mstmcra (in mstflint)

    def pick_mcra_cmd(self):

        SUCCESS = 0

        os = platform.system()
        if os in ['Linux','FreeBSD']:
            identify_location_cmd = 'which'
        elif os ==   'Windows':
            identify_location_cmd = 'where'
        else:
            raise RuntimeError("Unsupported OS")

        (rc, _, _) = cmdExec(identify_location_cmd + ' mcra')
        if rc == SUCCESS:
            return 'mcra'
        else:
            (rc, _, _) = cmdExec(identify_location_cmd + ' mstmcra')
            if rc == SUCCESS:
                return 'mstmcra'
            else:
                raise RuntimeError("Can't identify the location of mcra/mstmcra command")

    def read(self, device, addr, offset, length):

        cmd = "%s %s %s.%s:%s" % (self.mcra_cmd, device, addr, offset, length)
        (rc, stdout, stderr) = cmdExec(cmd)
        if rc:
            raise RuntimeError (str(stderr))
        return int(stdout, 16)

    def write(self, device, addr, offset, length, value):

        cmd = "%s %s %s.%s:%s %s" % (self.mcra_cmd, device, addr, offset, length, value)
        (rc, _, stderr) = cmdExec(cmd)
        if rc:
            raise RuntimeError (str(stderr))
