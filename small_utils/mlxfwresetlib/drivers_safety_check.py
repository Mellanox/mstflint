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
import sys
try:
    from mlxfwresetlib.mlxfwreset_utils import cmdExec, split_dbdf, getDevDBDF, get_device_without_function
    from mlxfwresetlib.hot_reset import HotResetFlow, HotResetError

    import mtcr
    import argparse
    import regaccess
    import re
    import glob
    import os

    from mlxfwresetlib.mlnx_peripheral_components import MlnxPeripheralComponents  # remove - just for debug

    from regaccess import RegAccException
except Exception as e:
    print("-E- could not import : %s" % str(e))
    sys.exit(1)


######################################################################
# Description:  Operation Terminated
# OS Support :  Linux/FreeBSD/Windows.
######################################################################

class OperationTerminated(Exception):
    pass


class DriversSafetyCheckManager:
    """
    A utility class for managing driver safety checks.
    This class provides functionality to check if any drivers that aren't in the ignore list
    are currently running on PCI devices in the PCIe Switch tree/s.
    It also stores the upstream port DBDFs discovered during the check for reuse in hot reset flow.
    """

    def __init__(self, reg_access_obj, dev_dbdf, devices_sd, ignore_list, is_pcie_switch, logger):
        """
        Initialize the DriversSafetyCheckManager with device information and determine the hot reset flow.

        Args:
            reg_access_obj: Register access object for PCI operations
            dev_dbdf: The device DBDF provided by the user to be reset
            devices_sd: List containing the auxiliary device DBDF of the device if it exists
            logger: Logger object
        """
        self._logger = logger
        self._reg_access_obj = reg_access_obj

        self._logger.debug("DriversSafetyCheckManager: dev_dbdf: {0}, devices_sd: {1}".format(dev_dbdf, devices_sd))
        self._dev_dbdf = dev_dbdf
        self._devices_sd = [getDevDBDF(dev, logger) for dev in devices_sd]

        self._requester_pcie_index = self._reg_access_obj.sendMPQD(depth=0, node=0, DPNv=1)
        self._logger.debug('DriversSafetyCheckManager: Provided device PCIe index is {0}'.format(self._requester_pcie_index))

        # Determine hot reset flow (similar to set_hot_reset_flow function)
        self._hot_reset_flow = self.set_hot_reset_flow()
        self._logger.debug('DriversSafetyCheckManager: Hot reset flow set to {0}'.format(self._hot_reset_flow))

        # Store upstream DBDFs for later reuse in hot reset flow
        self._upstream_dbdfs = []  # List of upstream port DBDFs discovered during check

        self._logger.debug("pcie_switch: {0}, hot_reset_flow: {1}".format(is_pcie_switch, self._hot_reset_flow))
        self._ignore_list = ignore_list
        self._retrieve_data_only = True
        if is_pcie_switch and self._hot_reset_flow is not None:
            self._retrieve_data_only = False  # scanning for forbidden drivers is needed and not just dbdf detection
        self.check_binded_drivers()

        self._dbdf_target_device_dict = {}
        self._dbdf_sd_partner_dict = {}

        self.prepare_hot_reset_targets()

        self._logger.debug("DriversSafetyCheckManager: check_binded_drivers completed successfully")

    def set_hot_reset_flow(self):
        """
        Determine the hot reset flow type based on MPIR.sdm and devices_sd.

        Returns:
            str: The hot reset flow type (SINGLE_DEVICE, SOCKET_DIRECT, or HIDDEN_SOCKET_DIRECT)
        """
        try:
            _, _, _, _, sdm = self._reg_access_obj.sendMPIR(depth=0, pcie_index=self._requester_pcie_index, node=0)
        except Exception as e:
            self._logger.debug('DriversSafetyCheckManager: Failed to send MPIR: {0}, defaulting to regular reset flow'.format(e))
            return None  # regular reset flow will be used

        self._logger.debug('_set_hot_reset_flow: sdm = {0}, devices_sd length = {1}'.format(sdm, len(self._devices_sd)))

        if sdm == 1 and len(self._devices_sd) > 0:
            return HotResetFlow.SOCKET_DIRECT
        elif sdm == 1 and len(self._devices_sd) == 0:
            return HotResetFlow.HIDDEN_SOCKET_DIRECT
        elif sdm == 0:
            return HotResetFlow.SINGLE_DEVICE
        else:
            return None

    def prepare_hot_reset_targets(self):
        """
        Prepare the target device dictionaries for hot reset based on discovered upstream ports.

        Sets self.dbdf_target_device_dict and self.dbdf_sd_partner_dict based on:
        - If no upstream DBDFs found: Raise an error
        - If 1 upstream DBDF found: Use it as the target device
        - If 2 upstream DBDFs found: Use them as target device and SD partner
        - More than 2: Error (invalid configuration)
        """
        if len(self._upstream_dbdfs) == 0:  # must be > 0 since the EP itself will be there at the bare minimum
            raise RuntimeError("DriversSafetyCheckManager: No upstream DBDFs found")
        elif len(self._upstream_dbdfs) == 1:
            self._dbdf_target_device_dict = split_dbdf(self._upstream_dbdfs[0], self._logger)
        elif len(self._upstream_dbdfs) == 2:
            self._dbdf_target_device_dict = split_dbdf(self._upstream_dbdfs[0], self._logger)
            self._dbdf_sd_partner_dict = split_dbdf(self._upstream_dbdfs[1], self._logger)
        else:  # there should be at most 2 USPs/EPs - one for each SD EP
            raise RuntimeError("DriversSafetyCheckManager: Unexpected number of upstream DBDFs found: {}".format(len(self._upstream_dbdfs)))

        self._logger.debug("DriversSafetyCheckManager: dbdf_target_device_dict: {}".format(self._dbdf_target_device_dict))
        self._logger.debug("DriversSafetyCheckManager: dbdf_sd_partner_dict: {}".format(self._dbdf_sd_partner_dict))

    @staticmethod
    def parse_ignore_list(value):
        """
        Validates a comma-separated string of driver names to ignore during safety checks.
        This method is designed to work with argparse's type parameter and as a helper function for validate_ignore_file below.

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

        # Remove duplicates
        return list(set(drivers_to_ignore))

    @staticmethod
    def validate_ignore_file(file_path):
        """
        Validates and parses a file containing driver names to ignore during safety checks.
        This method is designed to work with argparse's type parameter.

        Args:
            file_path (str): Path to file containing driver names (one per line or comma-separated) (comments, i.e lines starting with #, are ignored)

        Returns:
            list: The validated list of drivers to ignore (will be stored by argparse)

        Raises:
            argparse.ArgumentTypeError: If file doesn't exist, can't be read, or contains invalid drivers
        """
        import os

        # Handle empty input
        if not file_path:
            return []

        # Check if file exists
        if not os.path.isfile(file_path):
            raise argparse.ArgumentTypeError("File '{}' does not exist".format(file_path))

        try:
            # Read and process the file to build a comma-separated string
            driver_parts = []
            with open(file_path, 'r') as f:
                for line in f:
                    line = line.strip()

                    # Handle inline comments
                    line = line.split('#')[0].strip()

                    # Skip if line is empty (including empty lines, inline comments, or lines that become empty after removing comments)
                    if not line:
                        continue

                    # Add the line content (whether it's comma-separated or single driver)
                    driver_parts.append(line)

            # Join all parts with commas and let parse_ignore_list handle everything
            combined_string = ','.join(driver_parts)
            return DriversSafetyCheckManager.parse_ignore_list(combined_string)

        except IOError as e:
            raise argparse.ArgumentTypeError("Cannot read file '{}': {}".format(file_path, str(e)))

    @staticmethod
    def _get_all_pci_devices_for_domain_bus(domain, bus):
        """
        Get all PCI device addresses (DBDFs) for a given domain and bus.
        This mimics the command: ls -d /sys/bus/pci/devices/<domain>:<bus>:* | xargs -n1 basename

        Args:
            domain (str): PCI domain (e.g., "0016")
            bus (int): PCI bus number (e.g., 0x05)

        Returns:
            list: List of PCI device addresses in format "domain:bus:device.function"
        """

        # Format the pattern to match PCI devices
        pattern = "/sys/bus/pci/devices/{}:{:02x}:*".format(domain, bus)

        # Get all matching device paths
        device_paths = glob.glob(pattern)

        # Extract just the device dbdf (file name)
        devices_dbdf = []
        for path in device_paths:
            devices_dbdf.append(os.path.basename(path))

        # Sort for consistent ordering
        devices_dbdf.sort()

        return devices_dbdf

    @staticmethod
    def _discover_devices(dev_dbdf, logger):  # not in use eventually but leaving in case we need it later
        """
        Discover devices with matching V3 field from VPD.

        Args:
            dev_dbdf: The device DBDF to get the reference V3 field from
            logger: Logger instance for debugging

        Returns:
            list: List of discovered device DBDFs with matching V3 fields
        """
        cmd = "mdevices_info -vv"
        logger.debug("Running command: {}".format(cmd))
        (rc, out, stderr) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to run: {}. Error: {}".format(cmd, stderr))

        dbdf_pattern = re.compile(r'^[0-9a-f]{4}:[0-9a-f]{2}:[0-9a-f]{2}\.[0-9a-f]$', re.IGNORECASE)
        bdf_no_domain_pattern = re.compile(r'^[0-9a-f]{2}:[0-9a-f]{2}\.[0-9a-f]$', re.IGNORECASE)  # BDF without domain
        discovered_devices = []

        try:
            v3_prime_str = self.get_V3_field_from_vpd(dev_dbdf)
        except HotResetError as e:
            logger.error("Failed to get V3 field from VPD for device {}: {}".format(dev_dbdf, str(e)))
            return [dev_dbdf]

        for line in out.split('\n'):
            parts = line.split()
            if len(parts) > 2:
                potential_bdf = parts[2]
                if dbdf_pattern.match(potential_bdf):
                    dbdf = potential_bdf
                elif bdf_no_domain_pattern.match(potential_bdf):
                    dbdf = "0000:{}".format(potential_bdf)
                    logger.debug("Added domain prefix to BDF: {} -> {}".format(potential_bdf, dbdf))
                else:
                    continue

                try:
                    if HotResetFlow._get_V3_field_from_vpd(dbdf) == v3_prime_str:
                        discovered_devices.append(dbdf)
                except HotResetError as e:
                    logger.warning("Failed to get V3 field from {}: {}".format(potential_bdf, e))

        logger.debug("Discovered devices: {}".format(discovered_devices))
        return discovered_devices

    def is_upstream_port(self, dbdf):
        cmd = "lspci -s {} -n".format(dbdf)
        self._logger.debug("Running command: {}".format(cmd))
        (rc, output, stderr) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to run: {}. Error: {}".format(cmd, stderr))

        # Validate output format
        output = output.strip()
        if not output:
            raise RuntimeError("Empty output from lspci command for device {}".format(dbdf))

        # Use regex to validate and parse the entire lspci output format
        # Expected format: 31:00.0 0604: 15b3:197e (domain may or may not be present)
        pattern = r'^((?:[0-9a-fA-F]{4}:)?[0-9a-fA-F]{2}:[0-9a-fA-F]{2}\.[0-9a-fA-F])\s+([0-9a-fA-F]{4}):\s+([0-9a-fA-F]{4}:[0-9a-fA-F]{4})'

        match = re.match(pattern, output)
        if not match:
            raise RuntimeError("Invalid lspci output format for device {}: {}".format(dbdf, output))

        pci_address, class_code, vendor_device = match.groups()

        is_upstream = class_code == "0604"
        self._logger.debug("Class code: {} {} an upstream port".format(class_code, "is" if is_upstream else "is not"))
        return is_upstream

    def get_forbidden_drivers_from_upstream_port(self, upstream_dbdf, dbd):
        """
        Get forbidden drivers by scanning PCI buses under an upstream port.

        Args:
            upstream_dbdf: Upstream port PCI address (e.g., "0000:00:01.0")
            dbd: DBD (without function) of the EP we want to ignore while scanning for forbidden drivers (its driver will be managed during hot reset flow)

        Returns:
            list: List of forbidden drivers in format "driver_name@pci_address"
        """
        forbidden_drivers = []

        self._logger.debug("Upstream address: {}".format(upstream_dbdf))

        # Get secondary bus
        cmd = "setpci -s {0} SECONDARY_BUS ".format(upstream_dbdf)
        self._logger.debug("Running command: {}".format(cmd))
        (rc, output, stderr) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to run: {}. Error: {}".format(cmd, stderr))
        secondary_bus = int(output.strip(), 16)
        self._logger.debug("Secondary bus: 0x{:02x}".format(secondary_bus))

        # Get subordinate bus
        cmd = "setpci -s {0} SUBORDINATE_BUS ".format(upstream_dbdf)
        self._logger.debug("Running command: {}".format(cmd))
        (rc, output, stderr) = cmdExec(cmd)
        if rc != 0:
            raise RuntimeError("Failed to run: {}. Error: {}".format(cmd, stderr))
        subordinate_bus = int(output.strip(), 16)
        self._logger.debug("Subordinate bus: 0x{:02x}".format(subordinate_bus))

        if secondary_bus == 0 and subordinate_bus == 0:
            self._logger.debug("secondary and subordinate bus are 0, meaning there are no downstream devices. Skipping scan.")
            return forbidden_drivers

        domain = upstream_dbdf.split(':')[0]
        self._logger.debug("For domain: {}, scanning buses in the range from 0x{:02x} to 0x{:02x}".format(domain, secondary_bus, subordinate_bus))

        # Scan all buses in the range
        for bus in range(secondary_bus, subordinate_bus + 1):
            self._logger.debug("Getting all PCI devices for domain: {}, bus: {:02x}".format(domain, bus))

            # Get all PCI device addresses for this domain:bus combination
            downstream_devices_dbdf = DriversSafetyCheckManager._get_all_pci_devices_for_domain_bus(domain, bus)
            if not downstream_devices_dbdf:
                self._logger.debug("No PCI devices found on {}:{:02x}".format(domain, bus))
                continue
            self._logger.debug("Found PCI devices on {}:{:02x} : {}".format(domain, bus, downstream_devices_dbdf))

            # Check each PCI device for binded drivers
            for downstream_device_dbdf in downstream_devices_dbdf:
                self._logger.debug("Checking downstream_device_dbdf: {}".format(downstream_device_dbdf))
                if downstream_device_dbdf.startswith(dbd):  # we need to skip all pfs of the device
                    self._logger.debug("Skipping check of {} since it's our EP and we manage its driver during hot reset flow".format(downstream_device_dbdf))
                    continue
                cmd = "lspci -k -s {}".format(downstream_device_dbdf)
                (rc, output, stderr) = cmdExec(cmd)
                if rc == 0 and output.strip():
                    self._logger.debug("Found PCI device at {}: {}".format(downstream_device_dbdf, output.strip().split('\n')[0]))
                    for line in output.split('\n'):
                        if 'Kernel driver in use:' in line:
                            driver_name = line.split('Kernel driver in use:')[1].strip()
                            self._logger.debug("PCI device {} using driver: {}".format(downstream_device_dbdf, driver_name))
                            if driver_name not in self._ignore_list:
                                forbidden_drivers.append("{}@{}".format(driver_name, downstream_device_dbdf))
                            else:
                                self._logger.debug("Driver {} is in the ignore list, skipping".format(driver_name))
                elif rc != 0:
                    raise RuntimeError("Failed to run {}".format(cmd))

        self._logger.debug("Forbidden drivers: {}".format(forbidden_drivers))
        return forbidden_drivers

    def check_forbidden_drivers_on_discovered_devices(self, discovered_devices):
        """
        Check for forbidden drivers on discovered devices.
        Stores discovered upstream DBDFs in self._upstream_dbdfs and self._pcie_index_to_upstream.

        Args:
            discovered_devices: List of device DBDFs to check

        Returns:
            list: List of forbidden drivers in format "driver_name@pci_address"
        """
        forbidden_drivers = []
        pcie_index_list = []
        upstream_ports_amount = 0

        for dbdf in discovered_devices:
            self._logger.debug("Checking device: {}".format(dbdf))

            domain = dbdf.split(':')[0]
            if self.is_upstream_port(dbdf):
                self._logger.debug("Device {} is an upstream port".format(dbdf))
                upstream_dbdf = dbdf
                upstream_ports_amount += 1
            else:
                MstDevObj = None
                if dbdf == self._dev_dbdf:
                    self._logger.debug("Device {} is the target device, skipping RegAccessObj creation".format(dbdf))
                    RegAccessObj = self._reg_access_obj
                else:
                    MstDevObj = mtcr.MstDevice(dbdf)
                    RegAccessObj = regaccess.RegAccess(MstDevObj)
                requester_pcie_index = RegAccessObj.sendMPQD(depth=0, node=0, DPNv=1)
                self._logger.debug("Requester PCIe index: {}".format(requester_pcie_index))
                if requester_pcie_index not in pcie_index_list:
                    pcie_index_list.append(requester_pcie_index)
                    _, _, upstream_bus, upstream_device, _ = RegAccessObj.sendMPIR(depth=0, pcie_index=requester_pcie_index, node=0)
                    upstream_dbdf = "{0}:{1:02x}:{2:02x}.0".format(domain, upstream_bus, upstream_device)
                else:
                    raise RuntimeError("Both primary and aux devices ({}, {}) have same requester PCIe index {}".format(discovered_devices[0], discovered_devices[1], requester_pcie_index))  # this indicates fw bug

                if MstDevObj is not None:
                    MstDevObj.close()

            self._logger.debug("Upstream DBDF: {}".format(upstream_dbdf))

            # Store upstream DBDF if not already in list for later reuse in hot reset flow
            if upstream_dbdf not in self._upstream_dbdfs:
                self._upstream_dbdfs.append(upstream_dbdf)
                self._logger.debug("Added upstream DBDF: {}".format(upstream_dbdf))

            if self._retrieve_data_only:
                continue
            port_forbidden_drivers = self.get_forbidden_drivers_from_upstream_port(upstream_dbdf, get_device_without_function(dbdf))
            forbidden_drivers.extend(port_forbidden_drivers)

        if len(pcie_index_list) + upstream_ports_amount == 0:  # should have found at least one UPS or the target EP (for the provided device)
            raise RuntimeError("failed to find any upstream port on the discovered devices")

        self._logger.debug("PCIE index list: {}".format(pcie_index_list))
        self._logger.debug("Upstream ports amount: {}".format(upstream_ports_amount))
        return forbidden_drivers

    def check_forbidden_drivers_on_hidden_device(self, aux_dbdf, pcie_index):
        """
        Check for forbidden drivers on hidden devices.
        Stores the upstream DBDF for the auxiliary device.

        Args:
            aux_dbdf: The auxiliary device DBDF
            pcie_index: PCIe index

        Returns:
            list: List of forbidden drivers in format "driver_name@pci_address"
        """
        self._logger.debug("aux_dbdf: {}, pcie_index: {}".format(aux_dbdf, pcie_index))
        domain = aux_dbdf.split(':')[0]
        _, _, upstream_bus, upstream_device, _ = self._reg_access_obj.sendMPIR(depth=0, pcie_index=pcie_index, node=0)
        upstream_dbdf = "{0}:{1:02x}:{2:02x}.0".format(domain, upstream_bus, upstream_device)

        # Store upstream DBDF and PCIe index mapping
        if upstream_dbdf not in self._upstream_dbdfs:
            self._upstream_dbdfs.append(upstream_dbdf)
            self._logger.debug("Added upstream DBDF for hidden device: {}".format(upstream_dbdf))

        forbidden_drivers = []
        if not self._retrieve_data_only:
            forbidden_drivers = self.get_forbidden_drivers_from_upstream_port(upstream_dbdf, get_device_without_function(aux_dbdf))
        return forbidden_drivers

    def get_V3_field_from_vpd(self, dbdf_str):
        cmd = "lspci -s {0} -vvv".format(dbdf_str)
        self._logger.debug('lspci command: {0}'.format(cmd))
        (rc, output, stderr) = cmdExec(cmd)
        if rc:
            raise RuntimeError(str(stderr))
        # logger.debug('lspci output: {0}'.format(output))

        for line in output.splitlines():
            if '[V3]' in line:
                v3 = line.strip().split()[-1]  # [V3] Vendor specific: 62ee5a540e91
                self._logger.debug('V3 field string: {0}'.format(v3))
                return v3

        raise HotResetError("No V3 field found")

    def get_hidden_aux_device(self):
        """
        Get hidden devices.

        Returns:
            str: The hidden aux device DBDF
        """

        aux_dbdf = None
        v3_prime_str = self.get_V3_field_from_vpd(self._dev_dbdf)
        cmd = "lspci -D -d 15b3:2100"
        (rc, pci_list, stderr) = cmdExec(cmd)
        if rc:
            raise RuntimeError(str(stderr))

        for line in pci_list.splitlines():
            aux_dbdf_candidate = line.strip().split()[0]  # for example: 82:00.0 Infiniband controller...
            try:
                v3_aux_str = self.get_V3_field_from_vpd(aux_dbdf_candidate)
            except Exception as error:
                self._logger.warning("Failed to read V3 from {0}: {1}".format(aux_dbdf_candidate, error))
                continue
            if v3_prime_str == v3_aux_str:
                aux_dbdf = aux_dbdf_candidate
                self._logger.debug('V3 numbers are identical, found aux device, dbdf: {0}, v3 number: {1}'.format(aux_dbdf, v3_aux_str))
                break

        if not aux_dbdf:
            raise RuntimeError("failed to find aux device both as hidden and as discovered")

        self._logger.debug("aux_dbdf: {}".format(aux_dbdf))
        return aux_dbdf

    def check_binded_drivers(self):
        """
        Checks if any drivers that aren't in the ignore list are currently running on PCI devices.
        Also stores the upstream DBDFs for later reuse in hot reset flow.

        Args:
            ignore_list (list): List of driver names to ignore in the check

        Returns:
            None: The function does not return anything

        Raises:
            RuntimeError: If commands fail
            OperationTerminated: If forbidden drivers are found
        """
        self._logger.debug("DriversSafetyCheckManager: devices_sd: {}".format(self._devices_sd))
        if len(self._devices_sd) > 1:
            raise RuntimeError("DriversSafetyCheckManager: There can be one aux device for socket direct yet we found {}".format(self._devices_sd))

        discovered_devices = [self._dev_dbdf] + self._devices_sd
        self._logger.debug("DriversSafetyCheckManager: Discovered devices: {}".format(discovered_devices))

        forbidden_drivers = self.check_forbidden_drivers_on_discovered_devices(discovered_devices)

        if self._hot_reset_flow == HotResetFlow.HIDDEN_SOCKET_DIRECT:
            aux_pci_index = 1  # for hidden SD aux pci_index is always 1
            aux_dbdf = self.get_hidden_aux_device()
            self._logger.debug("DriversSafetyCheckManager: Auxiliary device DBDF: {}".format(aux_dbdf))
            forbidden_drivers += self.check_forbidden_drivers_on_hidden_device(aux_dbdf, aux_pci_index)

        self._logger.debug("Stored upstream DBDFs: {}".format(self._upstream_dbdfs))  # this will be used in the hot reset flow, if no forbidden drivers are found

        # If we found any forbidden drivers, report them
        if forbidden_drivers:
            print("===============================================================================")
            print("ERROR: The following drivers are currently bound to PCI devices on the switch:")
            print("===============================================================================")

            pci_column_width = 15  # Enough space for "0000:01:00.0" format

            # Create table header
            print("{:<{}} | {}".format("PCI", pci_column_width, "Driver"))
            print("{} | {}".format("-" * pci_column_width, "-" * 10))

            # Print each driver in table format
            for driver_info in forbidden_drivers:
                driver_name, dbdf = driver_info.split('@', 1)
                print("{:<{}} | {}".format(dbdf, pci_column_width, driver_name))

            print("")
            print("Please unbind the drivers or add them to the ignore file/list.")

            # Extract driver names and format as comma-separated list
            driver_names = list(set([driver_info.split('@')[0] for driver_info in forbidden_drivers]))
            print("* Driver that is resilient to device reset can be added to ignore list, for example:")
            print("    --ignore_list \"{}\"".format(",".join(driver_names)))
            raise OperationTerminated("\nExit on error..")

        self._logger.debug("No forbidden drivers found on PCI devices.")
