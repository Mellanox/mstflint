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

"""
* $Id           : mlxfwreset_utils.py 2017-11-28
* $Authors      : Ahmad Soboh (ahmads@mellanox.com)
"""

from __future__ import print_function
import subprocess
import platform
import re
import time


######################################################################
# Description:  Execute command and get (rc, stdout-output, stderr-output)
# OS Support :  Linux/Windows.
######################################################################

def cmdExec(cmd):
    p = subprocess.Popen(cmd,
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE,
                         universal_newlines=False,
                         shell=True)
    output = p.communicate()
    stat = p.wait()
    return (stat, output[0].decode('utf-8'), output[1].decode('utf-8'))  # RC, Stdout, Stderr

######################################################################
# Description:  Run cmd in loops
# OS Support :  N/A
######################################################################


def cmdExecLoop(cmd, sleep_time, max_retries):
    retries_num = 0
    rc = 1
    while rc and retries_num < max_retries:
        (rc, stdout, stderr) = cmdExec(cmd)
        retries_num += 1
        time.sleep(sleep_time)
    return (rc, stdout, stderr)

######################################################################
# Description:  DBDF string manipulation
# OS Support :  N/A
######################################################################


def getDomain(devAddr):
    devAddr = devAddr.split(":")
    if len(devAddr) == 3:
        return devAddr[0]
    return None


def addDomainToAddress(devAddr):
    if len(devAddr.split(":")) == 2:
        return "0000:" + devAddr
    return devAddr


def removeDomainFromAddress(devAddr):
    if len(devAddr.split(":")) == 3:
        return devAddr[5:]
    return devAddr


def isDevDBDFFormat(dev):
    pat = r"[0-9,A-F,a-f]{4}:[0-9,A-F,a-f]{2}:[0-9,A-F,a-f]{2}\.[0-9,A-F,a-f]{1,2}"
    if re.match(pat, dev):
        return True
    return False


def isDevBDFFormat(dev):
    pat = r"[0-9,A-F,a-f]{2}:[0-9,A-F,a-f]{2}\.[0-9,A-F,a-f]{1,2}"
    if re.match(pat, dev):
        return True
    return False

######################################################################
# Description:  get device DBDF format
# OS Support :  Linux/Windows.
######################################################################


def getDevDBDF(device, logger=None):
    if isDevDBDFFormat(device):
        return device
    if isDevBDFFormat(device):
        return addDomainToAddress(device)

    operatingSys = platform.system()
    if (operatingSys == "FreeBSD"):
        if not (device.startswith("pci")):
            raise RuntimeError("Unexpected device name format")
        return device[3:]
    elif (operatingSys == "Linux"):
        # Handle fwctl short names (e.g., fwctl2 -> /dev/fwctl/fwctl2)
        if re.match(r'^fwctl\d+$', device):
            device = "/dev/fwctl/" + device
        if device.startswith("vfio-"):
            device = device[5:]
        cmd = "mdevices_info -vv"
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to get device PCI address")
        # extract bdf
        bdf = None
        for line in out.split('\n'):
            if device in line:
                if len(line.split()) > 2:
                    bdf = line.split()[2]
        if not bdf:
            raise RuntimeError("Failed to get device PCI Address")
        return addDomainToAddress(bdf)
    elif (operatingSys == "Windows"):
        cmd = "mdevices status -vv"
        (rc, out, _) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to get device PCI address")
        # extract bdf
        bdf = None
        for line in out.split('\n'):
            l = line.split()
            if (len(l) > 1) and (device in l[0]) and ("seg:bus:dev.fn" in l[1]):
                bdf = line.split('=')[1]
        if not bdf:
            raise RuntimeError("Failed to get device PCI Address")
        return bdf
    else:
        raise RuntimeError("Unsupported OS")


def is_in_internal_host(logger=None):
    '''
    The function checks if the tool is running on the BlueField's internal host (ARM)
    The function will return true is the OS is Linux and PCIe root-port 00:00.0 is Mellanox
    '''

    # Return value from cache
    if 'result' in dir(is_in_internal_host):          # We need to cache the result to avoid accessing the device
        return is_in_internal_host.result             # when it's still not ready to get PCI packets (after PCI "toggle")

    if platform.system() == "Linux":
        cmd = "setpci -s 00:00.0 0x0.w"
        rc, out, _ = cmdExec(cmd)
        if logger:
            logger.info('is_in_internal_host: RC={0}, setpci output: {1}'.format(rc, out))
        if rc == 0 and out.strip() == "15b3":
            is_in_internal_host.result = True
        else:
            is_in_internal_host.result = False
    else:
        is_in_internal_host.result = False

    return is_in_internal_host.result


def is_uefi_secureboot():

    if platform.system() == "Linux":
        cmd = "mokutil --sb-state"
        rc, out, _ = cmdExec(cmd)
        if rc == 0 and out.strip() == "SecureBoot enabled":
            return True

    return False


def get_timeout_in_miliseconds(dtor_result, timeout):
    timeout_value = dtor_result[timeout].to_value
    timeout_multiplier = dtor_result[timeout].to_multiplier

    if timeout_multiplier == 0x0:  # Time in milliseconds.
        return timeout_value
    elif timeout_multiplier == 0x1:  # Time in seconds.
        return (timeout_value * 1000)
    elif timeout_multiplier == 0x2:  # Time in minutes.
        return (timeout_value * 60 * 1000)
    elif timeout_multiplier == 0x3:  # Time in hours.
        return (timeout_value * 60 * 60 * 1000)
    else:
        raise RuntimeError("Unknown timeout multiplier, exit..")


def check_if_elapsed_time(start_time, timeout, error_msg):
    current_time = time.time()
    elapsed_time = current_time - start_time
    if elapsed_time >= timeout:
        raise RuntimeError(error_msg)


def split_dbdf(dev_dbdf, logger):
    logger.debug('dev_dbdf: {0}'.format(dev_dbdf))
    domain, bus, device_function = dev_dbdf.split(':')
    device, function = device_function.split('.')
    res = {
        "domain": int(domain, 16),
        "bus": int(bus, 16),
        "device": int(device, 16),
        "function": int(function, 16)
    }
    logger.debug('domain: 0x{0:X}, bus: 0x{1:X}, device: 0x{2:X}, function: 0x{3:X}'.format(res["domain"], res["bus"], res["device"], res["function"]))
    return res


def get_device_without_function(dbdf):
    """
    Extract domain:bus:device from a DBDF, excluding the function.

    Args:
        dbdf (str): Full DBDF in format "domain:bus:device.function" (e.g., "0000:01:00.0")

    Returns:
        str: Device without function in format "domain:bus:device" (e.g., "0000:01:00")
    """
    # Split by '.' to remove function, keep domain:bus:device
    return dbdf.rsplit('.', 1)[0]
