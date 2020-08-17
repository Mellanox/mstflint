# Copyright (c) Sep 2019 Mellanox Technologies LTD. All rights reserved.
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
import sys
import os
import string
import subprocess
import re
import platform
import regaccess
import time


class FwTraceUtilities(object):    

    @classmethod    
    def _cmd_exec(self, cmd):
        """
        Execute a command line and return the state and the output
        of the command
        """
        p = subprocess.Popen(cmd,
                             stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE,
                             universal_newlines=False,
                             shell=True)
        output = p.communicate()
        stat = p.wait()
        return (stat, output[0].decode('utf-8'), output[1].decode('utf-8'))  # RC, Stdout, Stderr

    @classmethod
    def _is_dev_dbdf_format(self, dev):
        """
        Check if the input has a bdf format with domain
        If bdf format with domain format return True, otherwise return False
        """
        pat = r"[0-9,A-F,a-f]{4}:[0-9,A-F,a-f]{2}:[0-9,A-F,a-f]{2}\.[0-9,A-F,a-f]{1,2}"
        if re.match(pat, dev):
            return True
        return False
    
    @classmethod
    def _is_dev_bdf_format(self, dev):
        """
        Check if the input has a bdf format
        If bdf format return True, otherwise return False
        """
        pat = r"[0-9,A-F,a-f]{2}:[0-9,A-F,a-f]{2}\.[0-9,A-F,a-f]{1,2}"
        if re.match(pat, dev):
            return True
        return False
    
    @classmethod
    def _add_domain_to_address(self, dev_addr):
        """
        Add the domain "0000:" to the given address
        """  
        if len(dev_addr.split(":")) == 2 :
            return "0000:" + dev_addr
        return dev_addr

    @staticmethod 
    def get_dev_dbdf(device_name):
        """
        retrieve the BDF according to the device name
        """ 
        if FwTraceUtilities._is_dev_dbdf_format(device_name):
            return device_name
        if FwTraceUtilities._is_dev_bdf_format(device_name):
            return FwTraceUtilities._add_domain_to_address(device_name)

        operatingSys = platform.system()

        if operatingSys == "FreeBSD":
            if not(device_name.startswith("pci")):
                raise RuntimeError("Unexpected device name format")
            return device_name[3:]
        elif operatingSys == "Linux":
            cmd = "mdevices_info -vv"
            (rc, out, _) = FwTraceUtilities._cmd_exec(cmd)
            if rc != 0 :
                raise RuntimeError("Failed to get device PCI address")
            # extract bdf
            bdf = None
            for line in out.split('\n'):
                if device_name in line:
                    if len(line.split()) > 2:
                        bdf = line.split()[2]
            if not bdf:
                raise RuntimeError("Failed to get device PCI Address")
            return FwTraceUtilities._add_domain_to_address(bdf)
        elif operatingSys == "Windows":
            cmd = "mdevices status -vv"
            (rc, out, _) = FwTraceUtilities._cmd_exec(cmd)
            if rc != 0 :
                raise RuntimeError("Failed to get device PCI address")
            # extract bdf
            bdf = None
            for line in out.split('\n'):
                l = line.split()
                if (len(l) > 1) and (device_name in l[0]) and ("seg:bus:dev.fn" in l[1]):
                    bdf = line.split('=')[1]
            if not bdf:
                raise RuntimeError("Failed to get device PCI Address")
            return bdf
        else:
            raise RuntimeError("Unsupported OS")       
    
    @staticmethod 
    def is_driver_mem_mode_supported(): 
        """
        Check if driver mem mode is suported
        If supported return True, otherwise return False
        """   
        is_supported = False
    
        if os.name == "nt":
            # future capability - windows
            pass
        else:
            if os.path.exists("/sys/kernel/debug/tracing/events/mlx5/fw_tracer/") or \
               os.path.exists("/sys/kernel/debug/tracing/events/mlx5/mlx5_fw/"):
                is_supported = True

        return is_supported
    
    @staticmethod
    def is_secure_fw(mst_device):
        """
        Check if the firmware is secure or not
        If secure return True, otherwise return False
        """
        is_secure = False
        if mst_device is None:
            return  is_secure

        # in case that reg access fail, we cant determain a secure fw and return false
        try:
            reg_access_obj = regaccess.RegAccess(mst_device)
            is_secure = reg_access_obj.getSecureFWStatus()
        except:
            is_secure = False

        return is_secure
    
    @staticmethod
    def ts_to_real_ts(ts, freq):
        """
        The method calculate a real time stamp
        and return is as [hh:mm:ss:nsec] format
        """ 
        if freq <= 0:
            raise RuntimeError("device frequency is not above Zero - can't calc real time stamp")
        
        nano_seconds = int(1000 / freq) * ts
        # calc hours
        time_in_seconds = int(nano_seconds / 1000000000)
        hours = int(time_in_seconds / 3600)
        # calc minutes
        time_in_seconds = time_in_seconds - (hours * 3600)
        minutes = int(time_in_seconds / 60)
        # calc seconds
        time_in_seconds = time_in_seconds - (minutes * 60)
        seconds = time_in_seconds        
        # calc the reminder in nano seconds
        nsecs = nano_seconds - int(nano_seconds / 1000000000) * 1000000000
        
        return "{:02d}:{:02d}:{:02d}:{:09d}".format(hours, minutes, seconds, nsecs)

    @staticmethod
    def get_device_frequency(device):
        """
        The method call mlxuptime, parse 
        the device frequency and return it as integer
        (mlxuptime can take 1 sec)
        """ 
        cmd = "mlxuptime -d" + device
        (rc, out, _) = FwTraceUtilities._cmd_exec(cmd)
        freq_num = 0
        if rc != 0 :
            raise RuntimeError("Failed to get device frequency (necessary for real ts calculation)")
        else:
            for line in out.split('\n'):
                if "Measured core frequency" in line:
                    freq_str = line.split(": ")[1].split(" ")[0]
                    freq_num = int(round(float(freq_str))) 
                    break
               
        return freq_num
        
##########################################


if __name__ == "__main__":
    sys.exit(ExtractStrings())
