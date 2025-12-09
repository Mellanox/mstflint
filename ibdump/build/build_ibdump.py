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
import shutil
import commands
import sys
import platform
import re
import zipfile
import datetime
import getpass
from subprocess import Popen,PIPE

try:
    from subprocess import check_call
    CHECK_CALL = 1
except Exception, e:
    CHECK_CALL = 0
from optparse import OptionParser

USER_NAME = getpass.getuser()

IBDUMP_GIT_PATH = "ssh://%s@l-gerrit.mtl.labs.mlnx:29418/tools/sniffer" % USER_NAME
TMP_PATH = "/tmp/ibdump_build_" + str(os.getpid())
BRANCH = "ibdump-2_0_5_mlnx_ofed"
BIN_DIR = "/mswg/projects/mft/bin"
oper_sys = ("linux", "windows")['Linux' not in platform.system()]
ARCH = platform.machine()
if re.match("i\d86", ARCH) != None :
    ARCH = "x86" 
RELEASE_DIR = "/tgwork/tools/ibdump_build/tmp/ibdump-%s_%s" % ("%s-%s", oper_sys)
PREPARE_ENV_CMD = "C:\\Ewdk\\10.0.17643.0\\LaunchBuildEnv.cmd"
if 'Linux' not in platform.system():
    IBDUMP_GIT_PATH = "http://l-gerrit.mtl.labs.mlnx:8080/tools/sniffer"
    WININF_GIT_PATH = "M:\\git\\wininf.git"
    IBDUMP_EXT_LIB_PATH = "M:\\tmp\\tools\\ibdump_build"
    TMP_PATH = "C:\\tmp\\ibdump_build_" + str(os.getpid())
    BRANCH = "ibdump-2_0_5_mlnx_ofed"
    BIN_DIR = "M:\\projects\\mft\\bin"
    RELEASE_DIR = "M:\\tmp\\tools\\ibdump_build\\tmp\\ibdump-%s_%s" % ("%s-%s", oper_sys)
    #PREPARE_ENV_CMD = "\"c:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\""
    BUILDS_CONF = ["Win8"]
    
VERSION = "2.0.5"
RC = "1212"
##################
# General Helpers
##################

tar_dist_files = ['ibdump.c',
                  'bit_slice.h',
                  'CHANGES',
                  'gitversion.h',
                  'ibd_hw_access.c',
                  'ibd_hw_access.h',
                  'ibdump.spec',
                  'Makefile',
                  'ibd_device.h',
                  'tools_version.h',
                  'vpi_tcpdump',
                  'README.txt']
                  


def exec_command(command, with_exit=True, with_output=True):
    if with_output:
        print '-I- Running command: "%s"' % command
    else:
        print '-I- Running command: "%s"...' % command,
    try:
        if CHECK_CALL:
            rc = check_call(command, shell=True)
        else:
            rc , output = commands.getstatusoutput(command)
            if rc and with_exit:
                print >> sys.stderr, "-E- " + output
                cleanup()
                sys.exit(1)
            if with_output:
                print '-I- Command "%s" output:\n%s' % (command, output)
                
    except Exception, e:
        print "-E- Failed to run command : %s " % str(e)
        cleanup()
        sys.exit(1)

    return 0

def setup():
    print "-I- Creating TMP path : %s" % TMP_PATH
    if os.path.exists(TMP_PATH):
        shutil.rmtree(TMP_PATH)
    os.makedirs(TMP_PATH)

def create_tar():
    setup()
    #shutil.copy(BIN_DIR + "/make_ibdump_build", TMP_PATH)
    os.chdir(TMP_PATH)
    #if exec_command("bash make_ibdump_build --rc %s --ver %s --repo %s" % (RC, VERSION, IBDUMP_GIT_PATH)):
    #    print "Build FAILED !!!"
    #    shutil.rmtree(getpass.getuser()TMP_PATH)
    git_clone_cmd = "git clone %s" % IBDUMP_GIT_PATH
    exec_command(git_clone_cmd)
    os.chdir("sniffer/ibdump")
    exec_command("make gitversion.h")
    replace_version_cmd = 'sed -e "s/^VERSION *=..*$/VERSION    = %s-%s/" Makefile > Makefile.tmp' % (VERSION, RC)
    exec_command(replace_version_cmd)
    exec_command("mv Makefile.tmp Makefile")

    replace_release_cmd = 'sed -e "s/^Release:..*$/Release: %s/" -e "s/^Version:..*$/Version: %s/" ibdump.spec > ibdump.spec.tmp' % (RC, VERSION)
    exec_command(replace_release_cmd)
    exec_command("mv ibdump.spec.tmp ibdump.spec")
    build_name="ibdump-%s" % (VERSION)
    os.chdir(TMP_PATH)
    os.makedirs(build_name)
    for file in tar_dist_files:
        shutil.copy2("sniffer/ibdump/%s" % file, build_name)
    exec_command("cp -rf sniffer/ibdump/debian %s" % build_name)
    tar_cmd = "tar cvfz %s-%s.tgz %s" % (build_name, RC, build_name)
    exec_command(tar_cmd)
    
    
    
def build_wininf():
#     if datetime.datetime.today().weekday() < 6:
#         return
    print "="*15 + "Building WININF ... " + "="*15
    print "-I- Entering " + IBDUMP_EXT_LIB_PATH
    os.chdir(IBDUMP_EXT_LIB_PATH)
    wininf_path = os.path.join(IBDUMP_EXT_LIB_PATH, "wininf")
    if os.path.exists(wininf_path):
        print "-I- Removing %s" % wininf_path
        try:
            shutil.rmtree(wininf_path)
        except Exception, e:
            print "-E- Failed to remove WININF Dir, %s " % str(e)
            sys.exit(1)
    print "-I- Cloning WININF GIT ..."
    rc = os.system("git clone %s" % WININF_GIT_PATH)
    if rc:
        print "-E- Failed to Clone WININF"
        sys.exit(1)
    os.chdir("wininf")
    os.system("git submodule init")
    os.system("git submodule update")
    for config in BUILDS_CONF:
        print "\n\n ******************** [Wininf] %s Build ********************\n" % config
        make_cmd = "msbuild /t:build /p:Configuration=\"%s Release\" /p:platform=x64 /m:24 /p:SignMode=Off dirs.sln" % (config)
        exec_command(make_cmd)    
    
def build_ibdump_win():
    setup()
    os.chdir(TMP_PATH)
    exec_command("git clone %s" % IBDUMP_GIT_PATH)
    os.chdir("sniffer")
    os.chdir("ibdump")
    git_rev_cmd = "git rev-parse --short HEAD"
    pipe = Popen(git_rev_cmd,shell=True,stdout=PIPE,stderr=PIPE)
    git_rev = pipe.stdout.read().split("\n")[0]   
    STR = "#define PACKAGE_GIT_VER \"%s\"\n#define PACKAGE_VERSION_STR \"%s-%s\"" % (git_rev, VERSION, RC) 
    f = open("gitversion.h", "wb")
    f.write(STR)
    f.close()
    curr_dir = os.getcwd()
    for config in BUILDS_CONF:
        print "\n\n ******************** [Ibdump] %s Build ********************\n" % config
        prepare_make_cmd = "msbuild /t:build /p:Configuration=\"%s Release\" /p:platform=x64 /m:24 /p:SignMode=Off ibdump.sln" % config
        if exec_command(prepare_make_cmd):
            print "-E- Build FAILED !!!"
            return 1
    zipf = zipfile.ZipFile(TMP_PATH + os.path.sep + "ibdump-%s-%s.zip" % (VERSION, RC), 'w')
    for config in BUILDS_CONF:
        os.makedirs(config)
        shutil.copy("bin\\user\\obj%sRelease\\x64\\ibdump.exe" % config, config)
        shutil.copy("bin\\user\\obj%sRelease\\x64\\ibdump.pdb" % config, config)
        zipf.write("%s\\ibdump.exe" % config)
        zipf.write("%s\\ibdump.pdb" % config)
        os.chdir(curr_dir)
    #zip.close()
    
def export_ibdump():
    fixed_release_path = RELEASE_DIR % (VERSION, RC)
    if os.path.exists(fixed_release_path):
        shutil.rmtree(fixed_release_path)
    os.makedirs(fixed_release_path)
    try:
        suffix = ("tgz", "zip") ['Linux' not in platform.system()]
        shutil.copy(TMP_PATH + os.path.sep + "ibdump-%s-%s.%s" % (VERSION, RC, suffix),
                    fixed_release_path + os.path.sep + "ibdump-%s-%s.%s" % (VERSION, RC, suffix))
        print "-I- Ibdump exported successfully to %s " % fixed_release_path
        return 0
    except Exception, e:
        print "-E- Failed to copy the tarball, %s" % str(e)
        return 1
    
def cleanup(): 
    print "-I- Cleaning Up .."  
    os.chdir(TMP_PATH+os.path.sep+"..")
    if os.path.exists(TMP_PATH):
        try:
            shutil.rmtree(TMP_PATH)
        except Exception, e:
            print "-E- Failed to delete the temp folder, %s" % str(e)
            sys.exit(0)
      
        
usage="""%prog [options]
\tBuild ibdump for all platforms ."""
    
def main():
    parser=OptionParser(usage=usage)
    parser.add_option("--version", dest="ver", help="The version of the ibdump", metavar="VERSION")
    parser.add_option("--rc", dest="rc", help="The rc of the ibdump", metavar="RC")
    parser.add_option("--nocompilation", help="Do not compile WIN driver", action='store_true', default=False)
    
    (options, args) = parser.parse_args()
    if options.ver:
        global VERSION
        VERSION = options.ver
    if options.rc:
        global RC
        RC = options.rc
    no_export = 0
    print "Creating tar for ibdump"    
    if 'Linux' in platform.system():
        no_export = create_tar()
    else:
        if not(options.nocompilation):
            build_wininf()
        no_export = build_ibdump_win()
        
    if not no_export:
        export_ibdump()
    
    cleanup()
    
if __name__ == "__main__":
    
    main()
