# Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --
from mlxfwresetlib.mlxfwreset_utils import cmdExec
import argparse


class GpuDriverSafetyCheckManager:
    """
    A static utility class for managing GPU driver safety checks.
    This class provides functionality to validate driver names and check their loaded status.
    """

    # Class-level constant defining all known GPU drivers that need safety checks
    GPU_DRIVERS_SAFETY_LIST = (
        "nvidia-persistenced", "dcgm-exporter", "dcgm", "nvidia-dcgm",
        "nvidia-fabricmanager", "xorg-setup", "lightdm", "xcp-rrdd-gpumon",
        "kubelet", "bmc-watchdog", "nvidia_vgpu_vfio", "nvidia-uvm",
        "nvidia-drm", "nvidia-modeset", "nv_peer_mem", "nvidia_peermem",
        "nvidia_fs", "gdrdrv", "nvidia", "i2c_nvidia_gpu"
    )

    @staticmethod
    def validate_ignore_list(value):
        """
        Validates a comma-separated string of driver names to ignore during safety checks.
        This method is designed to work with argparse's type parameter.

        Args:
            value (str): Comma-separated string of driver names to ignore

        Returns:
            list: The validated list of drivers to ignore (will be stored by argparse)

        Raises:
            argparse.ArgumentTypeError: If any specified driver is not in the safety list
        """
        # Handle empty input
        if not value:
            return []

        # Split and clean the input string
        drivers_to_ignore = [d.strip() for d in value.split(',') if d.strip()]

        # Validate each driver
        invalid_drivers = [
            d for d in drivers_to_ignore
            if d not in GpuDriverSafetyCheckManager.GPU_DRIVERS_SAFETY_LIST
        ]

        if invalid_drivers:
            raise argparse.ArgumentTypeError(
                "Invalid driver(s): {0}. Allowed drivers are: {1}".format(
                    ','.join(invalid_drivers),
                    ','.join(GpuDriverSafetyCheckManager.GPU_DRIVERS_SAFETY_LIST)
                )
            )

        return drivers_to_ignore

    @staticmethod
    def check_gpu_drivers_loaded(ignore_list):
        """
        Checks if any GPU drivers that aren't in the ignore list are currently loaded.

        Args:
            ignore_list (list): List of driver names to ignore in the check

        Returns:
            bool: True if relevant drivers are loaded, False otherwise

        Raises:
            RuntimeError: If the lsmod command fails for reasons other than no matches
        """
        # Get list of drivers to check (excluding ignored ones)
        drivers_to_check = [
            driver for driver in GpuDriverSafetyCheckManager.GPU_DRIVERS_SAFETY_LIST
            if driver not in ignore_list
        ]

        # If all drivers are ignored, no need to check
        if not drivers_to_check:
            return False

        # Construct and execute the lsmod command
        cmd = "lsmod | grep -E '{}'".format("|".join(drivers_to_check))
        (rc, output, stderr) = cmdExec(cmd)

        # Process the command results
        if rc == 0:
            if output.strip():
                print("Some drivers attached to the GPU are still loaded, please unload them.")
                print("Here is the lsmod output:")
                print(output.strip())
                return True
            return False
        elif rc == 1:
            return False  # No drivers found
        else:
            raise RuntimeError(str(stderr))
