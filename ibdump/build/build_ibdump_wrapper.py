#!/usr/bin/python


#
# Copyright (C) Jan 2021 Mellanox Technologies Ltd. All rights reserved.
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
#        copyright notice, this list of conditions and the following disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# End of legal section ......................................................


##########################################
# By: Itay Avraham, itayavr@mellanox.com #
##########################################

##########
# Imports
##########
import os
import copy
import sys
import optparse
import rpyc
import subprocess
import re
import time 
from optparse import OptionParser

#######################
# Globals and Constants
#######################

options = None
settings = None
IBDUMP_EXT_LIB_PATH = "/mswg/projects/mft/ibdump_build"
release_dir = "/mswg/projects/mft/ibdump_build/BUILDS"
WININF_GIT_PATH = "/mswg/git/wininf.git"
time_stamp = "ibdump_%s" % time.strftime("%Y%m%d_%H%M")
SCRIPT_VERSION = "0.0.9"
WINBUILD = ""
LINUXBUILD = ""

latest_symlink = "/mswg/release/sniffer/latest"
Version = "3.0.0"
RC = "1"

CURR_SCRIPT_LOC = os.path.abspath(os.path.dirname(__file__))

build_machines = {
                  #"windows" : {
                   #            "build_script" : "M:\\projects\\mft\\bin\\build_ibdump.py --version %s --rc %s",
                    #           "hostname_ip"  : "10.143.111.104"
                     #          },
                  "linux"   : {
                               "build_script" : "/mswg/projects/mft/bin/build_ibdump.py --version %s --rc %s",
                               "hostname_ip"  : "mtlbuild-002-007"
                               }
                  }

######################
# Run command helpers
######################
usage="""%prog [options]
\tBuild ibdump for all platforms ."""

def Run_Build():
    ret_val = 0
    for oper_sys , data in build_machines.iteritems():
        print "\n========================== %s build ===========================" % oper_sys
        if "linux" not in oper_sys:
            try:
                conn = rpyc.classic.connect(data["hostname_ip"])
                print "-I- Connected to %s build Successfully" % oper_sys
            except:
                print >> sys.stderr, "-E- The connection could not be established. Check if the rpyc server is running on the destination machine"
                sys.exit(1)        
        try:
            cmd = data["build_script"] % (Version, RC)
            if "linux" not in oper_sys:
                print "-I- Running %s on %s" % (cmd, data["hostname_ip"])
                rc = conn.modules.os.system(cmd)
            else:
                print "-I- Build Linux package"
                rc = os.system(cmd)
            if rc:
                print "-E- Build for %s Failed, review RPyC Logger" % oper_sys
                ret_val = 1
            else:
                print "-I- Build for %s has finished successfully" % oper_sys
        except Exception,e:
            print >> sys.stderr, "-E- An error occurred while running command \"%s\" on machine %s" % (cmd, data["hostname_ip"])
            #print >> sys.stderr, "    Please be sure to run RPyC on the %s build machine"
            raise
    return ret_val
        
def collect_and_export():
    print "-I- Collecting all packages .."
    build_dir = "/tgwork/tools/ibdump_build/tmp/ibdump-%s-%s" % (Version, RC)
    release_path = release_dir+ '/' + time_stamp
    os.mkdir(release_path)
    os.chdir(release_path)
    for ar in build_machines.keys():
        os.mkdir(ar)
        print "-I- Copying the %s package to %s/%s ..." % (ar, release_path, ar)
        fd = os.popen("cp -rf %s_%s*/* %s/%s" % (build_dir, ar, release_path, ar))
        out = fd.read()
        rc = fd.close()
        if rc:
           print "-E- Failed to copy %s package" % ar
           sys.exit(1)
    print "-I- Copying the installer to the release path ..."
    os.system("cp %s/install.py %s" % (CURR_SCRIPT_LOC, release_path))
    print "-I- ibdump build is ready in: %s" % release_path

def getLatestVerRc():
    #Getting the latest link and increase the RC with 1, in case it exists
    global latest_symlink
    full_path = os.path.realpath(latest_symlink)
    if os.path.exists(full_path):
        ibdump_str = full_path.split("/")[-1]
        ptrn = "sniffer-(?P<Ver>\w+\.\w+\.\w+)-(?P<Rc>\w+)"
        m = re.match(ptrn, ibdump_str)
        if m:
            global Version
            global RC
            Version = m.groupdict()["Ver"]
            RC = str(int(m.groupdict()["Rc"]) + 1)
    else:
        print "-W- latest link for ibdump release is not valid"

def main():
    parser=OptionParser(usage=usage)
    parser.add_option("--version", dest="ver", help="The version of the ibdump", metavar="VERSION")
    parser.add_option("--rc", dest="rc", help="The rc of the ibdump", metavar="RC")
    
    #Get the default values of Version and RC
    getLatestVerRc()
    (options, args) = parser.parse_args()
    if options.ver:
        global Version
        Version = options.ver
    if options.rc:
        global RC
        RC = options.rc
            
    if Run_Build():
        print "-E- Building ibdump was failed !"
        sys.exit(1)
    print "-I- Build passed successfully ..."
    collect_and_export()

    
if __name__ == "__main__":
    
    main()
