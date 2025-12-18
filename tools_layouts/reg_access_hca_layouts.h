
/*
* Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the main directory of this source tree, or the
* OpenIB.org BSD license below:
*
*     Redistribution and use in source and binary forms, with or
*     without modification, are permitted provided that the following
*     conditions are met:
*
*      - Redistributions of source code must retain the above
*        copyright notice, this list of conditions and the following
*        disclaimer.
*
*      - Redistributions in binary form must reproduce the above
*        copyright notice, this list of conditions and the following
*        disclaimer in the documentation and/or other materials
*        provided with the distribution.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*  Version: $Id$
*
*/
 

/***
         *** This file was generated at "2025-12-18 11:34:54"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/prm/hca/ext/reg_access_hca.adb --file-prefix reg_access_hca --prefix reg_access_hca_ --no-adb-utils
         ***/
#ifndef REG_ACCESS_HCA_LAYOUTS_H
#define REG_ACCESS_HCA_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_file_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	/* access: INDEX */
	u_int32_t parameter_index;
	/* Description - type_class = 0x6 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_global_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	/* access: INDEX */
	u_int32_t parameter_index;
	/* Description - type_class = 0x0 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_host_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.17 */
	/* access: INDEX */
	u_int32_t parameter_index;
	/* Description - type_class = 0x7 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_log_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.23 */
	/* access: INDEX */
	u_int32_t parameter_index;
	/* Description - type_class = 0x5 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_module_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.13 */
	/* access: INDEX */
	u_int16_t parameter_index;
	/* Description - Module Index */
	/* 0x0.14 - 0x0.23 */
	/* access: INDEX */
	u_int16_t module_index;
	/* Description - type_class = 0x9 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_multi_instance_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.11 */
	/* access: INDEX */
	u_int16_t parameter_index;
	/* Description - type_class = 0xA */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_per_host_pf_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.9 */
	/* access: INDEX */
	u_int16_t parameter_index;
	/* Description - If host_id_valid is set, indicates the PF ID, otherwise reserved. 
	*/
	/* 0x0.10 - 0x0.17 */
	/* access: INDEX */
	u_int8_t pf_index;
	/* Description - If host_id_valid is set, indicates the host ID, otherwise reserved. 
	*/
	/* 0x0.18 - 0x0.23 */
	/* access: INDEX */
	u_int8_t host_id;
	/* Description - type_class = 0x3 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_configuration_item_type_class_physical_port_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t parameter_index;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t port;
	/* Description - type_class = 0x1 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_class;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_date_time_layout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - hour (UTC) - 2 packed BCD digits */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t hours;
	/* Description - minutes - 2 packed BCD digits */
	/* 0x0.16 - 0x0.23 */
	/* access: RW */
	u_int8_t minutes;
	/* Description - seconds - 2 packed BCD digits */
	/* 0x0.24 - 0x0.31 */
	/* access: RW */
	u_int8_t seconds;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - day - 2 packed BCD digits */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t day;
	/* Description - month - 2 packed BCD digits */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t month;
	/* Description - year - 4 packed BCD digits */
	/* 0x4.16 - 0x4.31 */
	/* access: RW */
	u_int16_t year;
};

/* Description -   */
/* Size in bytes - 104 */
struct reg_access_hca_mcqi_dpa_metadata_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The subtype of the section */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t subtype;
	/* Description - The type of the section. Should be used to identify "twin" applications, e.g. - CCProg coming from a 3rd party versus "native" application. 
Enumeration details:
0 - APU_APP_EXTERNAL,
1 - 3 - Reserved,
4 - APU_APP_PCC,
5 - APU_APP_DLL,
6 - APU_APP_KERNEL,
7-255 - Reserved */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Version of App Metadata structure */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Structure length */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t length;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - DPA application version */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t dpa_app_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Version of the DPA API to OS */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t dpa_os_api_version;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Version of the DPA API to other DPA FW modules */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t dpa_fw_api_version;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - DPA application UUID, updated with a change in application version */
	/* 0x28.0 - 0x34.31 */
	/* access: RO */
	u_int32_t dpa_app_uuid[4];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Application description ASCII string */
	/* 0x40.0 - 0x5c.31 */
	/* access: RO */
	u_int32_t dpa_app_description_string[8];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_MRSV_CX_7_Value_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - disable_inband_recovery strap */
	/* 0x0.21 - 0x0.21 */
	/* access: RO */
	u_int8_t disable_inband_recovery;
	/* Description - primary_is_pcore1 strap */
	/* 0x0.22 - 0x0.22 */
	/* access: RO */
	u_int8_t primary_is_pcore1;
	/* Description - 2p_core_active strap */
	/* 0x0.23 - 0x0.23 */
	/* access: RO */
	u_int8_t two_p_core_active;
	/* Description - socket_direct strap */
	/* 0x0.24 - 0x0.24 */
	/* access: RO */
	u_int8_t socket_direct;
	/* Description - pci_reversal strap */
	/* 0x0.25 - 0x0.25 */
	/* access: RO */
	u_int8_t pci_reversal;
	/* Description - pci_partition_1 strap */
	/* 0x0.26 - 0x0.26 */
	/* access: RO */
	u_int8_t pci_partition_1;
	/* Description - pci_partition_0 strap */
	/* 0x0.27 - 0x0.27 */
	/* access: RO */
	u_int8_t pci_partition_0;
	/* Description - osc_freq_[1] strap */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t osc_freq_1;
	/* Description - osc_freq_[0] strap */
	/* 0x0.29 - 0x0.29 */
	/* access: RO */
	u_int8_t osc_freq_0;
	/* Description - core bypass n strap */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t core_bypass_n;
	/* Description - fnp strap */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t fnp;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - strapping pins mask
0: ignore strap value
1: strap value is valid */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t straps_mask;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_hca_config_item_type_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_file_ext configuration_item_type_class_file_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_global_ext configuration_item_type_class_global_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_host_ext configuration_item_type_class_host_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_log_ext configuration_item_type_class_log_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_module_ext configuration_item_type_class_module_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_multi_instance_ext configuration_item_type_class_multi_instance_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_per_host_pf_ext configuration_item_type_class_per_host_pf_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_configuration_item_type_class_physical_port_ext configuration_item_type_class_physical_port_ext;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_activation_method_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When set, the operation needed to move the component form ACTIVE_PENDING_RESET to ACTIVE should happen simultaneously on all hosts. */
	/* 0x0.0 - 0x0.0 */
	/* access: RO */
	u_int8_t all_hosts_sync;
	/* Description - This component will be ACTIVE or ACTIVE_PENDING_RESET after the APPLY state. */
	/* 0x0.1 - 0x0.1 */
	/* access: RO */
	u_int8_t auto_activate;
	/* Description - This component goes to ACTIVE_PENDING_RESET after activation.
A FW reset will move it to ACTIVE state. */
	/* 0x0.2 - 0x0.2 */
	/* access: RO */
	u_int8_t pending_fw_reset;
	/* Description - This component goes to ACTIVE_PENDING_RESET state after activation.
A server reset (PCIe PERST#), will move it ACTIVE state. */
	/* 0x0.3 - 0x0.3 */
	/* access: RO */
	u_int8_t pending_server_reboot;
	/* Description - This component goes to ACTIVE_PENDING_RESET state after activation.
DC power cycle (power cycle of PCI power rails), will move it ACTIVE state. */
	/* 0x0.4 - 0x0.4 */
	/* access: RO */
	u_int8_t pending_server_dc_power_cycle;
	/* Description - This component goes to ACTIVE_PENDING_RESET state after activation.
AC power cycle (power cycle for both PCI power rails and AUX power), will move it ACTIVE state. */
	/* 0x0.5 - 0x0.5 */
	/* access: RO */
	u_int8_t pending_server_ac_power_cycle;
	/* Description - When set, the component supports self activation. For cables, please refer to activation_type in LINKX_PROPERTIES data for more details. */
	/* 0x0.6 - 0x0.6 */
	/* access: RO */
	u_int8_t self_activation;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_cap_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bitmask indicating which info_type(s) are supported for this component. Set bit indicates the property set is supported
bit 1: VERSION
bit 5: ACTIVATION_METHOD
Other bits are reserved. CAPABILITIES set is always supported.
bit 6: LinkX
bit 7: Clock Synchronizer

bit 9: DPA_APPS_INFO

Other bits are reserved */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t supported_info_bitmask;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The size of the component given in bytes. Value 0x0 indicates that the size in unknown.
For some components, size may only be available in the READ_COMPONENT state. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t component_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Maximum size for this component, given in bytes. */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t max_component_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Maximal write size for MCDA */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t mcda_max_write_size;
	/* Description - Log 2 of the access word size in bytes.
Read and write access must be aligned to the word size. Write access must be done for an integer number of words. */
	/* 0xc.28 - 0xc.31 */
	/* access: RO */
	u_int8_t log_mcda_word_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The device only accepts updates for this component that explicitly lists its base MAC and/or base GUID */
	/* 0x10.26 - 0x10.26 */
	/* access: RW */
	u_int8_t match_base_guid_mac;
	/* Description - A user defined timestamp (MVTS) is active for this component. */
	/* 0x10.27 - 0x10.27 */
	/* access: RW */
	u_int8_t check_user_timestamp;
	/* Description - PSID is validated for this component update. */
	/* 0x10.28 - 0x10.28 */
	/* access: RW */
	u_int8_t match_psid;
	/* Description - Chip ID (device_hw_revision) is validated for this component update. */
	/* 0x10.29 - 0x10.29 */
	/* access: RW */
	u_int8_t match_chip_id;
	/* Description - Only signed components are accepted. */
	/* 0x10.30 - 0x10.30 */
	/* access: RW */
	u_int8_t signed_updates_only;
	/* Description - When set, this components may be read, see Section 10.3.4, "Read Flow", on page 1102. */
	/* 0x10.31 - 0x10.31 */
	/* access: RO */
	u_int8_t rd_en;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_mcqi_clock_source_properties_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Image Version Minor Number */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t image_version_minor;
	/* Description - Image Version Major Number */
	/* 0x0.4 - 0x0.7 */
	/* access: RO */
	u_int8_t image_version_major;
	/* Description - Clock Source Device Vendor Id
0: Renesas
1: SiTime 148
2: SiTime 348
3: TI
4-255: Reserved */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t vendor_id;
};

/* Description -   */
/* Size in bytes - 112 */
struct reg_access_hca_mcqi_dpa_apps_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Provides the number of DPA apps in the active DPA_APPS partition.
If there are no DPA apps, this field is equal to 0 and all the DPA_APP_METADATA fields will be 0. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t total_number_of_entries;
	/* Description - DPA_APPS_INFO version. */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - DPA metadata, see Table 2945, "MCQI DPA_APP_METADATA Layout," on page 3380 */
	/* 0x8.0 - 0x6c.31 */
	/* access: RO */
	struct reg_access_hca_mcqi_dpa_metadata_ext dpa_app_metadata;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_linkx_properties_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bit 0: Image A is running
Bit 1: Image A is committed, module boots from image A
Bit 2: Image A is erased / empty
Bit 3: Reserved
Bit 4: Image B is running
Bit 5: Image B is committed, module boots from image B
Bit 6: Image B is erased / empty
Bit 7: Reserved */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t fw_image_status_bitmap;
	/* Description - Bit 0: FW image A is present 
Bit 1: FW image B is present
Bit 2: Factory / boot image is present
Bits 3-7: Reserved */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t fw_image_info_bitmap;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Image A FW minor version */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t image_a_minor;
	/* Description - Image A FW major version */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t image_a_major;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Image A FW subminor number */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t image_a_subminor;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Image B FW minor version */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t image_b_minor;
	/* Description - Image B FW major version */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t image_b_major;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Image B FW subminor number */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t image_b_subminor;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Factory / boot image FW minor version */
	/* 0x14.0 - 0x14.7 */
	/* access: RO */
	u_int8_t factory_image_minor;
	/* Description - Factory / boot image FW major version */
	/* 0x14.8 - 0x14.15 */
	/* access: RO */
	u_int8_t factory_image_major;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Factory / boot image FW subminor number */
	/* 0x18.0 - 0x18.15 */
	/* access: RO */
	u_int16_t factory_image_subminor;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - 0: Does not support either one of the FW update procedures defined below
1: SFF-8636 management interface and pseudo-CMIS FW. Update is supported
2: CMIS 4.0 is implemented */
	/* 0x1c.0 - 0x1c.5 */
	/* access: RO */
	u_int8_t management_interface_protocol;
	/* Description - 0: HW reset is required. Host should be prepared to power cycle a cable after sending a RunFWImage command.
1: Self-activation with HW reset contained in the RunFWImage command. No additional actions required from the host.
2:Self-activation with hitless reset contained in the RunFWImage command. No additional actions required from the host.
3-15: Reserved */
	/* 0x1c.10 - 0x1c.13 */
	/* access: RO */
	u_int8_t activation_type;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Vendor Serial Number */
	/* 0x20.0 - 0x20.15 */
	/* access: RO */
	u_int16_t vendor_sn;
};

/* Description -   */
/* Size in bytes - 124 */
struct reg_access_hca_mcqi_version_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t version_string_length;
	/* Description - When set, the component has a valid user-defined version time-stamp in user_defined_time */
	/* 0x0.28 - 0x0.28 */
	/* access: RW */
	u_int8_t user_defined_time_valid;
	/* Description - When set, the component has a valid creation time-stamp in build_time */
	/* 0x0.29 - 0x0.29 */
	/* access: RW */
	u_int8_t build_time_valid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Version number */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t version;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Time of component creation. Valid only if build_time_valid is set. See Table 2935, "Date-Time Layout," on page 3374 */
	/* 0x8.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_date_time_layout_ext build_time;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - User-defined time assigned to the component version. Valid only if user_defined_time_valid is set. See Table 2935, "Date-Time Layout," on page 3374 */
	/* 0x10.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_hca_date_time_layout_ext user_defined_time;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Build tool version number.
Valid only when not equal to 0 */
	/* 0x18.0 - 0x18.31 */
	/* access: RW */
	u_int32_t build_tool_version;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - NULL terminated string representing the version. */
	/* 0x20.24 - 0x7c.23 */
	/* access: RW */
	u_int8_t version_string[92];
};

/* Description -   */
/* Size in bytes - 112 */
struct reg_access_hca_nic_cap_ext_dpa_cap_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Maximal number of DPA EUGs */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t max_num_dpa_eug;
	/* Description - Maximal number of DPA EUs */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t max_num_dpa_eu;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Maximal number of DPA EU partitions */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t max_num_dpa_eu_partition;
	/* Description - Maximal number of DPA EUs in one DPA EUG */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t max_num_dpa_eu_per_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bitmask indicating the supported sampling types of DPA performance counters. Set bit indicates this type is supported:
Bit 0: CUMMULATIVE_EVENT
Bit 1: EVENT_TRACER
Other bits are reserved */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t dpa_perf_sample_type;
	/* Description - Maximal number of VHCAs associated with a single DPA EU partition */
	/* 0x8.16 - 0x8.24 */
	/* access: RO */
	u_int16_t max_num_partition_vhca_id;
	/* Description - When set, DPA process performance counters can be activated using NIC_DPA_PERF_CTRL_REG */
	/* 0x8.30 - 0x8.30 */
	/* access: RO */
	u_int8_t process_perf_cnt;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_ptys_ext_proto_ib_admin_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IB bitmask:
Bit 0: SDR_1x
Bit 1: SDR_2x
Bit 2: SDR_4x
Bit 12: FDR_4x
Bit 14: EDR_2x
Bit 15: EDR_4x
Bit 16: HDR_1x
Bit 17: HDR_2x
Bit 18: HDR_4x
Bit 20: NDR_1x
Bit 21: NDR_2x
Bit 22: NDR_4x
Bit 24: XDR_1x
Bit 25: XDR_2x
Bit 26: XDR_4x */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	u_int32_t ext_proto_ib;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - IB bitmask:
Bit 0: SDR_1x
Bit 1: SDR_2x
Bit 2: SDR_4x
Bit 12: FDR_4x
Bit 14: EDR_2x
Bit 15: EDR_4x
Bit 16: HDR_1x
Bit 17: HDR_2x
Bit 18: HDR_4x
Bit 20: NDR_1x
Bit 21: NDR_2x
Bit 22: NDR_4x
Bit 24: XDR_1x
Bit 25: XDR_2x
Bit 26: XDR_4x */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t ext_proto_ib;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - NVLink bitmask:
Bit 0: 200G_1x_mode_a (200G_1x_Simplex)
Bit 1: 400G_2x_mode_a (400G_2x_Simplex)
Bit 2: 400G_2x_mode_b (375G_2x_Bidi)
Bit 3: 360G_2x_mode_b (337p5G_2x_Bidi)
Bit 4: 328G_2x_mode_b (307p5G_2x_Bidi)
Bit 5: Reserved
Bit 6: 200G_2x_mode_a (200G_2x_Simplex) */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	u_int32_t ext_proto_nvlink;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - NVLink bitmask:
Bit 0: 200G_1x_mode_a (200G_1x_Simplex)
Bit 1: 400G_2x_mode_a (400G_2x_Simplex)
Bit 2: 400G_2x_mode_b (375G_2x_Bidi)
Bit 3: 360G_2x_mode_b (337p5G_2x_Bidi)
Bit 4: 328G_2x_mode_b (307p5G_2x_Bidi)
Bit 5: Reserved
Bit 6: 200G_2x_mode_a (200G_2x_Simplex) */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t ext_proto_nvlink;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_rom_version_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Build version */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t build;
	/* Description - Minor version */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t minor;
	/* Description - Major version */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t major;
};

/* Description -   */
/* Size in bytes - 32 */
union reg_access_hca_MRSV_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_hca_MRSV_CX_7_Value_ext MRSV_CX_7_Value_ext;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_hca_config_item_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Length of configuration item data in bytes (not including header). Must be between 0 and 256. */
	/* 0x0.0 - 0x0.8 */
	/* access: RW */
	u_int16_t length;
	/* Description - Host ID valid:
1: the type_index.host_id field is valid
Valid only when MNVGC.priv_nv_other_host=1 and the type_class is a Host or Host-PF */
	/* 0x0.9 - 0x0.9 */
	/* access: INDEX */
	u_int8_t host_id_valid;
	/* Description - Configuration item version - defines the data structure following the header (together with the type field). */
	/* 0x0.12 - 0x0.15 */
	/* access: RW */
	u_int8_t version;
	/* Description - The entity which configured this parameter
0x0: UNSPECIFIED
0x1: CHASSIS_BMC
0x2: MAD
0x3: BMC
0x4: COMMAND_INTERFACE
0x5: ICMD - with unspecified source
0x6: ICMD_UEFI_HII - configured by the NIC's UEFI expansion ROM"s HII menu.
0x7: ICMD_UEFI_CLP - configured by the NIC's expansion ROM"s CLP.
0x8: ICMD_Flexboot - configured by the NIC"s legacy expansion ROM.
0x9: ICMD_mlxconfig - configured by Mellanox mlxconfig tool
0xA: ICMD_USER1 - value available for customer created tools that uses the ICMD interface for writing TLVs.
0xB: ICMD_USER2 - value available for customer created tools that uses the ICMD interface for writing TLVs.
0xC: ICMD_MLXCONFIG_SET_RAW - configures by
mlxconfig set raw operation.
0xD: ICMD_FLEXBOOT_CLP - configured by Legacy Expansion ROM CLP
0x10: BMC_APP1 - Configuration was done over the BMC by application #1 (application name is OEM specific)
0x11: BMC_APP2 - Configuration was done over the BMC by application #2 (application name is OEM specific)
0x12: BMP_APP3 - Configuration was done over the BMC by application #3 (application name is OEM specific)
0x1F: OTHER - the parameter was written by the NIC due to other reasons. 

Note - This field is writeable only when using the ICMD interface. The only value that are valid for writes are 0x6 through 0xB. Other values will be replaced by 0x5ICMD. */
	/* 0x0.16 - 0x0.20 */
	/* access: RO */
	u_int8_t writer_id;
	/* Description - Defines which value of the Configuration Item will be accessed.
0: NEXT - Next value to be applied
1: CURRENT - Currently set values (only valid for Query operation) Supported only if NVGC.nvda_read_current_settings==1.
2: FACTORY - Default factory values (only valid for Query operation). Supported only if NVGC.nvda_read_factory_settings==1. */
	/* 0x0.22 - 0x0.23 */
	/* access: INDEX */
	u_int8_t access_mode;
	/* Description - Read Enable
Controls the read operation during different life-cycle stages.
0: TLV cannot be read by the subsequent life-cycle priorities.
1: TLV can be read by the subsequent life-cycle priorities. */
	/* 0x0.24 - 0x0.24 */
	/* access: RW */
	u_int8_t rd_en;
	/* Description - Override Enable
0: Can only be overwritten by the current life-cycle priority.
1: Allowed to be over-written by the subsequent life-cycle priorities. */
	/* 0x0.25 - 0x0.25 */
	/* access: RW */
	u_int8_t ovr_en;
	/* Description - The life-cycle priority of this configuration.
0x0: USER,
0x1: OEM,
0x2: Reserved  
0x3: MLNX

The priority is set by either:
1. When using MNVDA, the TLV will have user priority
2. When using NVCONFIG, each TLV has its own priority */
	/* 0x0.28 - 0x0.29 */
	/* access: RO */
	u_int8_t priority;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Configuration item index according to its type_class. 
Table 3070, "Configuration Item Data Type Class Global Layout," on page 3469
Table 3072, "Configuration Item Data Type Class Physical Port Layout," on page 3469
Table 3074, "Configuration Item Data Type Class Per Host-PF Layout," on page 3470
Table 3076, "Configuration Item Data Type Class Log Layout," on page 3470
Table 3078, "Configuration Item Data Type Class File Layout," on page 3471
Table 3080, "Configuration Item Data Type Class Host Layout," on page 3471

Table 3082, "Configuration Item Data Type Class Module Layout," on page 3472
Table 3084, "Configuration Item Data Type Class Multi Instance Layout," on page 3473 */
	/* 0x4.0 - 0x4.31 */
	/* access: INDEX */
	union reg_access_hca_config_item_type_auto_ext type;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_default_timeout_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Timeout value */
	/* 0x0.0 - 0x0.19 */
	/* access: RO */
	u_int32_t to_value;
	/* Description - 0x0: millisecond   
0x1: seconds   
0x2: minutes   
0x3: hours    */
	/* 0x0.29 - 0x0.31 */
	/* access: RO */
	u_int8_t to_multiplier;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_diagnostic_cntr_layout {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Diagnostic counter identifier. */
	/* 0x0.0 - 0x0.15 */
	/* access: RW */
	u_int16_t counter_id;
	/* Description - The counter might be used as Synced Start Diagnostics Counters */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t sync;
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_hca_lane_2_module_mapping_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module number */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t module;
	/* Description - Reserved for HCA.
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t slot_index;
	/* Description - TX lane. 
When m_lane_m field is set, this field is ignored (Reserved). 
When rxtx field is cleared, this field is used for RX as well. */
	/* 0x0.16 - 0x0.19 */
	/* access: RW */
	u_int8_t tx_lane;
	/* Description - RX lane.
When m_lane_m field is set, this field is ignored (Reserved). 
When rxtx field is clreared, for set operation this field is ignored and for get operation may return invalid value, Rx mapping for get should be taken from tx_lane. */
	/* 0x0.24 - 0x0.27 */
	/* access: RW */
	u_int8_t rx_lane;
	/* Description - Supported if PCAM.feature_cap_mask bit 116 is set, otherwise field is not valid.
Relevant for Mode B port only, Mode A port should ignore.
indicates if module lane Tx or Rx is used.
0: module_rx_lane_valid - Mode B lane uses module rx lane. 
tx lane value is not valid should be ignored
1: module_tx_lane_valid - Mode B lane uses module tx lane. 
rx lane value is not valid should be ignored */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t mode_b_map;
};

/* Description -   */
/* Size in bytes - 124 */
union reg_access_hca_mcqi_reg_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_activation_method_ext mcqi_activation_method_ext;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_cap_ext mcqi_cap_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_clock_source_properties_ext mcqi_clock_source_properties_ext;
	/* Description -  */
	/* 0x0.0 - 0x6c.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_dpa_apps_info_ext mcqi_dpa_apps_info_ext;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_linkx_properties_ext mcqi_linkx_properties_ext;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_version_ext mcqi_version_ext;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_hca_mgir_dev_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The format of the string represented by ASCII. */
	/* 0x0.24 - 0x1c.23 */
	/* access: RO */
	u_int8_t dev_branch_tag[28];
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_mgir_fw_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sub-minor firmware version number.
Deprecated and returns '0'. 
Refer to extended_sub_minor. */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t sub_minor;
	/* Description - Minor firmware version number.
Deprecated and returns '0'. 
Refer to extended_minor. */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t minor;
	/* Description - Major firmware version number.
Deprecated and returns '0'. 
Refer to extended_major. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t major;
	/* Description - When set, the device is running firmware with secure-firmware updates capabilities. */
	/* 0x0.24 - 0x0.24 */
	/* access: RO */
	u_int8_t secured;
	/* Description - When set the device is running a signed FW binaries. */
	/* 0x0.25 - 0x0.25 */
	/* access: RO */
	u_int8_t signed_fw;
	/* Description - When set, the device is running a debug firmware. 'debug' binary can only be installed on specific devices (identified by their 'Factory base MAC'), which currently run a specific firmware version. These restrictions are expressed by a signed 'debug' token that must be loaded to the device before installing the debug binary. */
	/* 0x0.26 - 0x0.26 */
	/* access: RO */
	u_int8_t debug;
	/* Description - *NOTE* this field has diff meaning for Switch vs. NIC 

NIC:
The device is running:
0: a regular-secure firmware version
1: a development-secure firmware version

	*/
	/* 0x0.27 - 0x0.27 */
	/* access: RO */
	u_int8_t dev;
	/* Description - When set, string-TLV is supported.
For Retimer - always return 0 (not supported). */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t string_tlv;
	/* Description - *NOTE* for NICs same as dev field
Development-secure:
The device is running:
0: a regular-secure firmware version
1: a development-secure firmware version */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t dev_sc;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Firmware Build ID. Optional. 
Note: Deprecated for switches and returns '0'. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t build_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t year;
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t day;
	/* Description - Firmware installation date. 

For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04 */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t month;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Firmware installation hour.
For example 17:43 will be coded as 0x1743 */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t hour;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - FW PSID */
	/* 0x10.24 - 0x20.23 */
	/* access: RO */
	u_int8_t psid[16];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - User-configured version number of the current INI file. */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t ini_file_version;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - FW version's Major field in extended (32b) format. */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t extended_major;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - FW version's Minor field in extended (32b) format. */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	u_int32_t extended_minor;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - FW version's SubMinor field in extended (32b) format. */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	u_int32_t extended_sub_minor;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - incremented by one when version is not ISSUable */
	/* 0x30.0 - 0x30.15 */
	/* access: RO */
	u_int16_t isfu_major;
	/* Description - Bitmap representing the disabled tiles in the ASIC. Tile '0' is represented by the msb bit. 
0: tile is enabled
1: tile is disabled

The total number of tiles can be derived through MGPIR register. */
	/* 0x30.16 - 0x30.31 */
	/* access: RO */
	u_int16_t disabled_tiles_bitmap;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Note: has also msb bits in life_cycle_msb. Following values are a combination of both fields.
0: Production
1: GA Secured
2: GA Non-Secured
3: RMA
4: Pre Production
	*/
	/* 0x34.0 - 0x34.1 */
	/* access: RO */
	u_int8_t life_cycle;
	/* Description - 0: Disable
1: Enable */
	/* 0x34.2 - 0x34.2 */
	/* access: RO */
	u_int8_t sec_boot;
	/* Description - 0: Disable
1: Enable */
	/* 0x34.3 - 0x34.3 */
	/* access: RO */
	u_int8_t encryption;
	/* Description - [DWIP]
MSB of the life cycle.
Supported in QM3, CX8 and on.
See life_cycle field for full value descriptions. */
	/* 0x34.4 - 0x34.6 */
	/* access: RO */
	u_int8_t life_cycle_msb;
	/* Description - 0: device is in prod mode
1: device is in dev mode */
	/* 0x34.11 - 0x34.11 */
	/* access: RO */
	u_int8_t dev_state;
	/* Description - [DWIP]
ISSU-able:
0: not ISSUable
1: ISSUable
Supported from Quantum-3 and on
Supported for Retimers
Based on FW decisions: fuse, INI, NV and version on flash vs. running version */
	/* 0x34.13 - 0x34.13 */
	/* access: RO */
	u_int8_t issu_able;
	/* Description - [DWIP]
0: PSC is not PDS mode
1: PSC in PDS mode
Supported in QM3,CX8 and on. */
	/* 0x34.14 - 0x34.14 */
	/* access: RO */
	u_int8_t pds;
	/* Description - [NIC_Only]
When set, the embedding CPU engine is disabled
Valid for devices that supports embedded CPU (SOC)

	*/
	/* 0x34.15 - 0x34.15 */
	/* access: RO */
	u_int8_t ec_offload_engine_disabled;
	/* Description - Counter indication of dev fuse value */
	/* 0x34.16 - 0x34.20 */
	/* access: RO */
	u_int8_t dev_counter;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mgir_hardware_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PCI device ID. */
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t device_id;
	/* Description - See Table 2961, "Device HW Revision Descriptions," on page 3395 */
	/* 0x0.16 - 0x0.31 */
	/* access: RO */
	u_int16_t device_hw_revision;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Process Voltage Scaling
Supported nominal V_CORE voltage (in 50mV units) for the device. */
	/* 0x4.0 - 0x4.4 */
	/* access: RO */
	u_int8_t pvs;
	/* Description - Process technology
0: N/A
1: 40nm
2: 28nm
3: 16nm
4: 7nm
5: 5nm
6-31: Reserved */
	/* 0x4.11 - 0x4.15 */
	/* access: RO */
	u_int8_t technology;
	/* Description - Number of ports the device supports. */
	/* 0x4.16 - 0x4.27 */
	/* access: RO */
	u_int16_t num_ports;
	/* Description - [DWIP]
IB MAD Protocol. Based on value from ConfigProfile
0: IBg1
1: IBg2
2-7: Reserved */
	/* 0x4.28 - 0x4.30 */
	/* access: RO */
	u_int8_t ib_mad_gen;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The PCI device-ID of the NIC/HCA in recovery (Livefish) mode. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t hw_dev_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Module Master FW Default
0: FW is in control over modules management by default
1: SW is in control over modules management by default
2: Standalone ASIC (no I2C connectivity).
	Note: Relevant only for Spectrum-3 and above */
	/* 0xc.16 - 0xc.17 */
	/* access: RO */
	u_int8_t module_master_fw_default;
	/* Description - [DWIP][switch_internal] 
When set, this bit indicate this is CPO system */
	/* 0xc.27 - 0xc.27 */
	/* access: RO */
	u_int8_t cpo_indication;
	/* Description - GA Valid bit
0: MGIR.HW Info.ga is reserved
1: MGIR.HW Info.ga is valid

Supported in CX7, QM3 and on. */
	/* 0xc.28 - 0xc.28 */
	/* access: RO */
	u_int8_t ga_valid;
	/* Description - [DWIP]
The device is running:
0: a regular-secure firmware version
1: a development-secure firmware version

Supported in QM3,CX8 and on. */
	/* 0xc.30 - 0xc.30 */
	/* access: RO */
	u_int8_t development;
	/* Description - 0: Embedded HCA PCIe endpoint enabled
1: Embedded HCA PCIe endpoint disabled */
	/* 0xc.31 - 0xc.31 */
	/* access: RO */
	u_int8_t pci_switch_only_mode;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - MSB of the "base" MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.
manufacturing_base_mac of value 0 means field is not supported. */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t manufacturing_base_mac_47_32;
	/* Description - [DWIP]
Geographical Address
0: ASIC 0
1: ASIC 1
2: ASIC 2
3: ASIC 3
Valid for multi ASIC platforms only

. */
	/* 0x10.16 - 0x10.21 */
	/* access: RO */
	u_int8_t ga;
	/* Description - [DWIP]
Chip Type
0: Real chip
1: Emulation
2: ChipSim
3: SimX 
Supported from Quantum-3 and ArcusE */
	/* 0x10.24 - 0x10.27 */
	/* access: RO */
	u_int8_t chip_type;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - LSB of the "base" MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.
manufacturing_base_mac of value 0 means field is not supported. */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	u_int32_t manufacturing_base_mac_31_0;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time (in secs.) since last reset0 */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t uptime;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mgir_sw_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sub-minor Driver version number.
	*/
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t sub_minor;
	/* Description - Minor Driver version number.
	*/
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t minor;
	/* Description - Major Driver version number.
	*/
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - ROM 3 type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t rom3_type;
	/* Description - Arch type of ROM 3:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t rom3_arch;
	/* Description - ROM 2type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.8 - 0x4.11 */
	/* access: RO */
	u_int8_t rom2_type;
	/* Description - Arch type of ROM 2:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.12 - 0x4.15 */
	/* access: RO */
	u_int8_t rom2_arch;
	/* Description - ROM 1type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t rom1_type;
	/* Description - Arch type of ROM 1:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.20 - 0x4.23 */
	/* access: RO */
	u_int8_t rom1_arch;
	/* Description - ROM 0 type:
0x0: none
0x1: Flexboot
0x2: UEFI
0x3: UEFI-CLP
0x4: NVME
0x5: FCODE
0x6: UEFI Virtio net
0x7: UEFI Virtio blk
0x8: PXE Virtio net
0x9-0xF: Reserved */
	/* 0x4.24 - 0x4.27 */
	/* access: RO */
	u_int8_t rom0_type;
	/* Description - Arch type of ROM 0:
0x0: unspecified
0x1: AMD64 - x86 64bit architecture
0x2: AARCH64 - ARM Architecture 64 bits
0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures
0x4: IA32 - Intel Architecture 32 bits */
	/* 0x4.28 - 0x4.31 */
	/* access: RO */
	u_int8_t rom0_arch;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - ROM 0 version. */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	struct reg_access_hca_rom_version_ext rom0_version;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - ROM 1 version. */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	struct reg_access_hca_rom_version_ext rom1_version;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - ROM 2version. */
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	struct reg_access_hca_rom_version_ext rom2_version;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - ROM 3 version. */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	struct reg_access_hca_rom_version_ext rom3_version;
};

/* Description -   */
/* Size in bytes - 112 */
union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x6c.31 */
	/* access: RW */
	struct reg_access_hca_nic_cap_ext_dpa_cap_ext nic_cap_ext_dpa_cap_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_ptys_ext_proto_ib_admin_ext ptys_ext_proto_ib_admin_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext ptys_ext_proto_nvlink_admin_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext ptys_ext_proto_ib_cap_oper_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext ptys_ext_proto_nvlink_cap_oper_ext;
};

/* Description -   */
/* Size in bytes - 4 */
union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext ptys_ext_proto_ib_cap_oper_ext;
	/* Description -  */
	/* 0x0.0 - 0x0.31 */
	/* access: RW */
	struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext ptys_ext_proto_nvlink_cap_oper_ext;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_string_db_parameters_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Offset of the first string of the section, relative to the entire string data base, given in bytes. */
	/* 0x0.0 - 0x0.31 */
	/* access: RO */
	u_int32_t string_db_base_address;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Size of string database section, given in bytes */
	/* 0x4.0 - 0x4.23 */
	/* access: RO */
	u_int32_t string_db_size;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_MRSV_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Straps Structure Id
0: bf3 */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t ssid;
	/* Description - Valid bit
0: Strapping pins value reading is not supported for this system
1: Response is valid */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t v;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Data
See Table 2778, "MRSV entry - BF-3 Straps Layout," on page 3242 */
	/* 0x10.0 - 0x2c.31 */
	/* access: RO */
	union reg_access_hca_MRSV_data_auto_ext data;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_debug_cap {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The maximum number of samples that can be stored on the device's sampling buffer is 2^ log_max_samples in counters unit (i.e. 100 will represent the ability to store 100 samples of single counter, 50 samples of 2 counters, etc). */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t log_max_samples;
	/* Description - Log(base 2) of the the recommended minimal size of eq to handle the resource_dump_event */
	/* 0x0.16 - 0x0.20 */
	/* access: RW */
	u_int8_t log_min_resource_dump_eq;
	/* Description - If set, Resource_dump register is supported.
See Table  1797, "RESOURCE_DUMP Register Layout," on page  2124 */
	/* 0x0.22 - 0x0.22 */
	/* access: RW */
	u_int8_t resource_dump;
	/* Description - Log(base 2) of the size in granularity of 4KB to be allocated by host in order to accommodate cr_dump.
0 means feature is not supported.
See Table  1795, "CORE_DUMP Register Layout," on page  2122 */
	/* 0x0.23 - 0x0.27 */
	/* access: RW */
	u_int8_t log_cr_dump_to_mem_size;
	/* Description - If set, Core dump of type of specific QP is supported.
	*/
	/* 0x0.30 - 0x0.30 */
	/* access: RW */
	u_int8_t core_dump_qp;
	/* Description - If set, Core dump of type "General" is supported. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t core_dump_general;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The minimal sample period is 2^ log_min_smaple_period in device clocks. Clock rate of the device is reported by HCA_CAP.device_frequency_khz. */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t log_min_sample_period;
	/* Description - If set, the device supports dumping the diagnostic counters reports into the tracer buffer. */
	/* 0x4.28 - 0x4.28 */
	/* access: RW */
	u_int8_t diag_counter_tracer_dump;
	/* Description - If set, health monitoring for rx path activity is supported.
See Table  29.5.1, "RX Path Activity," on page  2011 */
	/* 0x4.29 - 0x4.29 */
	/* access: RW */
	u_int8_t health_mon_rx_activity;
	/* Description - Repetitive sampling mode is supported */
	/* 0x4.30 - 0x4.30 */
	/* access: RW */
	u_int8_t repetitive;
	/* Description - Single sampling mode is supported */
	/* 0x4.31 - 0x4.31 */
	/* access: RW */
	u_int8_t single;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - List of counters supported. Number of counters reported by num_of_counters. */
	/* 0x40.0 - 0x40.31 */
	/* access: RW */
	struct reg_access_hca_diagnostic_cntr_layout *diagnostic_counter;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_dtor_reg_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Maximum period for PCIe to be alive after toggle. */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext PCIE_TOGGLE_TO;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Interval for checking if FW health counter incremented. */
	/* 0x14.0 - 0x14.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext HEALTH_POLL_TO;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - On a multi-function device, in case of error, one function dump the CRspace, the other should not do reset till dump is finished. */
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext FULL_CRDUMP_TO;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Maximum period to wait for nic_interface reset. */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext FW_RESET_TO;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Maximum period to flush an errored SQ\RQ. */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext FLUSH_ON_ERR_TO;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Maximum period for pci_sync_for_fw_update_start. */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext PCI_SYNC_UPDATE_TO;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Maximum period for TEARDOWN_HCA. */
	/* 0x28.0 - 0x28.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext TEAR_DOWN_TO;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - The time that takes to do FW FSM reactivate. */
	/* 0x2c.0 - 0x2c.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext FSM_REACTIVATE_TO;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Maximum period for PF to reclaim own function pages. */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext RECLAIM_PAGES_TO;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Maximum period for PF to reclaim VF function pages. */
	/* 0x34.0 - 0x34.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext RECLAIM_VFS_PAGES_TO;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Maximum period for Reset FSM to move from UNLOAD ACCEPTED to LINK_TOGGLE_REQUEST */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	struct reg_access_hca_default_timeout_ext DRIVER_UNLOAD_AND_RESET_TO;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Maximum period for shutting down/booting the embedded CPU OS. Relevant for DPU devices only.
Valid only if the timeout value is not zero.
	*/
	/* 0x3c.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_hca_default_timeout_ext EMBEDDED_CPU_OS_SHUTDOWN_TO;
};

/* Description -   */
/* Size in bytes - 72 */
struct reg_access_hca_mcam_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Access Register ID groups 
0: First_128_REG_ID - Register IDs 0x9001 - 0x907F)
1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9080 while bit 127 represents register ID 0x90FF).
2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9100 while bit 127 represents register ID 0x917F).
3: Register_IDs_0x9180 - 0x91FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9180 while bit 127 represents register ID 0x91FF). */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t access_reg_group;
	/* Description - Feature list mask index: 
0: enhanced_features */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t feature_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Supported management's access register bitmask. Based on access_reg_group index. 
When bit is set, the register is supported in the device. 
For example:
Bit 1: MFCR_0x9001
Bit 2: MFSC_0x9002
Bit 3: MFSM_0x9003
Bit 4: MFSL_0x9004
Bit 58: MGCR_0x903A
Bit 73: MPPF_0x9049
Bit 127: MCAP_0x907F */
	/* 0x8.0 - 0x14.31 */
	/* access: RO */
	u_int32_t mng_access_reg_cap_mask[4];
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - Supported port's enhanced features.Based on feature_group index.
When bit is set, The feature is supported in the device
Bit 0: MPCNT counter group- PCIE performance counters supported
Bit 1: mtpps_fs - If set, field_select field in MTPPS register is supported.
Bit 2: mtpps_enhanced_out_periodic_adjustment - If set, enhanced_out_periodic_adjustment field in MTPPS register is supported.
Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter in MPCNT register is supported.
Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads, outbound_stalled_writes, outbound_stalled_reads_events and outbound_stalled_writes_events counters in MPCNT are supported.
Bit 5: Management pass through is supported
Bit 6: sensor_map - If set, sensor_map is supported in MTCAP register.
Bit 7: if set, module_status bit 8 (Module Low Power) in MCION register is supported. 
Bit 8: beacon_capability_disable - If set, beacon feature, as appears in MLCR register, in not supported by the device. 
Bit 9: dynamic_tx_overflow - If set, tx_overflow_sense field is supported in MPEGC register. 
Bit 10: mark_tx_action_cqe is supported if set to '1'.
Bit 11: mark_tx_action_cnp is supported if set to '1'.
Bit 12: dev_info is supported in  register is set to '1'.
Bit 13: sensor_count field is 12bit size in MTMP and MTBR
Bit 14: cs_tokens_supported is supported 
Bit 15: debug_fw_tokens_supported
Bit 16: long_keys is supported 
Bit 17: pwr_status and pci_power are supported in MPEIN
Bit 18: If set, accessing through device_type and device_index is supported in MCC, MCQI and MCQS
Bit 19: pcie_sync_for_fw_update_supported is set to '1'
Bit 20: ptpCyc2Realtime_modify - If set, the cycle to realtime translation offload is supported
Bit 21: If set to '1', reset_state in MFRL is supported
Bit 22: If set to '1', link_peer_max_speed is supported in MPEIN Register
Bit 23: If set to '1', slot_index field is supported in: MCIA, MCAS, MCION, MQSP, MTCAP, MTECR, MTMP, MTEWE, MTBR, MVCAP, MVCR, MGPIR, MDDT, MDCR.
Bit 24: If set, transceiver burn flow is supported in MCC, MCQI and MCQS.
Bit 26: If set, progress field is supported in MCQS
Bit 28: If set, number_of_slots field is supported in MGPIR.
Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.
Bit 30: If set, my_pf_number is supported in MPPF.
Bit 31: If set, sdee is supported in MTMP
Bit 32: If set, npps_period is supported in MTPPS.
Bit 33: If set, out_pulse_duration_ns is supported in MTPPS.
Bit 34: If set, MCIA supports 32 D-words. Otherwise, 12 D-words.
Bit 35: If set, MGIR.hw_info.technology is supported. 
Bit 37: If set, lp_msb is supported for MLCR, MPIR 
Bit 39: If set, MRCS and RMDT tokens are supported in MCQS
Bit 40: If set, 'encryption' field in MGIR is supported
Bit 43: If set, MFCR supports tacho_active_msb field
Bit 44: If set, FORE supports fan_under_limit_msb and fan_over_limit_msb fields
Bit 45: If set, MFRL.pci_rescan_required is supported
Bit 46: time_adjust_range_extended - if set, the MTUTC.time_adjustment range is extended to -200,000 to +200,000 
Bit 47: If set, MTUTC.freq_adj_units=1 is supported
Bit 48: If set, MRSRFT/MRSR.command=6 is supported
Bit 49: If set, MCQS.identifier support CRCS and CRDT tokens
Bit 51: If set, MTUTC.freq_adj_units=2 is supported
Bit 53: If set, Mlx mlxfwreset with downstream port is supported by FW [Internal]: NIC only, FW rejects reset till user committed that traffic is disabled
Bit 59: If set, MCC.component_specific_error_code is valid for LinkX devices
Bit 60: If set, MGNLE.clr is supported
Bit 61: If set, MGIR supports life_cycle_msb and pds fields in FW info and development field in HW info.
	
Bit 65: If set, MVCR support current_sensor_value_msb
Bit 66: If set. MFRL supports pci_reset_req_method, pci_switch_exist fields. [DWIP]
Bit 67: If set, MRSR.cmd = 6 works with SBR
Bit 68: If set, DPNv supported [NIC_Only]
Bit 70: If set, supports MTCAP support 8 bit internal_sensor_count [DWIP]
Bit 71: If set, supports MVCAP supports sensor_map_type [DWIP]
Bit 72: If set, MVCR supports parent_id field [NIC_only]
Bit 73: If set, MFRL.reset_type=5 Network reset is supported [NIC_only]
Bit 74: If set, MGIR.hw_info.pci_switch_only_mode is supported [NIC_only]
Bit 75: If set, PLLP supports oe_identifier and resource_labe_port [switch_internal][DWIP]
bit 76: If set, MCQS supports the component_not_supported field [DWIP]
Bit 77: If set, host_id field in MPIR is supported
Bit 78: If set, MGIR supports 12 bit num_ports field

bit 80: If set, MCQS,identifier supports the DPA_COMPONENT, DPA _COMPONENT_REMOVAL fields and MCQI supports DPA apps info
Bit 81: If set, MFCDR supports module and query_type fields [DWIP]
Bit 82: If set, MCIA supports async mode [DWIP][switch_internal]
Bit 83: If set, MISOC supports types 0x2,0x3,0xF and query_not_availble, query_pending fields[NIC_Only]
Bit 84: If set, MCANM supports ec_offload_engine_disabled field [NIC_Only]
Bit 85: If set, MTDT token is supported
Bit 86: If set, MPCAPM PRM is supported [NIC_Only]
Bit 87: If set, MTCTR cross timestamp of the DPA timer is supported [NIC_Only] */
	/* 0x28.0 - 0x34.31 */
	/* access: RO */
	u_int32_t mng_feature_cap_mask[4];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mcc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Command to be executed by the FSM
0x1: LOCK_UPDATE_HANDLE
0x2: RELEASE_UPDATE_HANDLE 
0x3: UPDATE_COMPONENT
0x4: VERIFY_COMPONENT
0x6: ACTIVATE
0x7: READ_COMPONENT
0x8: CANCEL
0x9: CHECK_UPDATE_HANDLE
0xA: FORCE_HANDLE_RELEASE
0xB: READ_PENDING_COMPONENT
0xC: DOWNSRTEAM_DEVICE_TRANSFER
Other values are reserved. Applicable for write operation only. */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t instruction;
	/* Description - This is a configuration that delays the activation of the component in seconds. Relevant only for activate command.
This configuration is volatile. */
	/* 0x0.8 - 0x0.15 */
	/* access: RW */
	u_int8_t activation_delay_sec;
	/* Description - The number of seconds elapsed since the update_handle owner last issued a command. The time saturates at 0xFFF. */
	/* 0x0.16 - 0x0.27 */
	/* access: RO */
	u_int16_t time_elapsed_since_last_cmd;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Index of the accessed component. 
Value from MCQS.component_index
Valid for 
UPDATE_COMPONENT, ACTIVATE_COMPONENET, READ_COMPONENT and READ_PENDING_COMPONENT instructions. Otherwise, this field is reserved. */
	/* 0x4.0 - 0x4.15 */
	/* access: INDEX */
	u_int16_t component_index;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Token representing the current flow executed by the FSM.
See Section 10.2.1, "Component Update State", on page 1099. */
	/* 0x8.0 - 0x8.23 */
	/* access: RW */
	u_int32_t update_handle;
	/* Description - Auto-update to all matching downstream devices is requested. */
	/* 0x8.31 - 0x8.31 */
	/* access: WO */
	u_int8_t auto_update;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Current Update FSM state, see Section  10.3.8, "FSM States," on page  1103
0x0: IDLE
0x1: LOCKED
0x2: INITIALIZE
0x3: DOWNLOAD
0x4: VERIFY
0x5: APPLY
0x6: ACTIVATE
0x7: UPLOAD
0x8: UPLOAD_PENDING
0x9: DOWNSRTEAM_DEVICE_TRANSFER
Other values are reserved */
	/* 0xc.0 - 0xc.3 */
	/* access: RO */
	u_int8_t control_state;
	/* Description - Indicates the successful completion of the instruction, or the reason it failed. See Section  10.3.7, "Error Handling," on page  1102
0x0: OK
0x1: ERROR
0x2: REJECTED_DIGEST_ERR
0x3: REJECTED_NOT_APPLICABLE
0x4: REJECTED_UNKNOWN_KEY
0x5: REJECTED_AUTH_FAILED
0x6: REJECTED_UNSIGNED
0x7: REJECTED_KEY_NOT_APPLICABLE
0x8: REJECTED_BAD_FORMAT
0x9: BLOCKED_PENDING_RESET
0xA: REJECTED_NOT_A_SECURED_FW
0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED
0xC: REJECTED_NO_DEBUG_TOKEN
0xD: REJECTED_VERSION_NUM_MISMATCH
0xE: REJECTED_USER_TIMESTAMP_MISMATCH
0xF: REJECTED_FORBIDDEN_VERSION
0x10: FLASH_ERASE_ERROR
0x11: REJECTED_REBURN_RUNNING_AND_RETRY
0x12: REJECTED_LINKX_TYPE_NOT_SUPPORTED
0x13: REJECTED_HOST_STORAGE_IN_USE
0x14: REJECTED_LINKX_TRANSFER (see module index in rejected_device_index)
0x15: REJECTED_LINKX_ACTIVATE (see module index in rejected_device_index)
0x16: REJECTED_INCOMPATIBLE_FLASH
0x17: REJECTED_TOKEN_ALREADY_APPLIED
0x18: REJECTED_FW_BURN_DRAM_NOT_AVAILABLE
0x19: FW_BURN_REJECTED_INVALID_SECURITY_VERSION
0x1A: FW_BURN_REJECTED_CERT_CER509 
0x1B: FW_BURN_REJECTED_CERT_SIGNATURE
0x1C: FW_BURN_REJECTED_CERT_METADATA
0x1D: FW_BURN_REJECTED_INTERNAL_ERROR_0 
0x1E: FW_BURN_REJECTED_NO_PLACE
0x1F: FW_BURN_REJECTED_REMOVAL_NO_MATCH_UIDD
0x20: FW_BURN_REJECTED_INTERNAL_ERROR_1 0x21: FW_BURN_REJECTED_INTERNAL_ERROR_2 0x22: FW_BURN_REJECTED_NUM_OF_SWAP
0x23: FW_BURN_REJECTED_INTERNAL_ERROR_3 
0x24: FW_BURN_REJECTED_INTERNAL_ERROR_4 0x25: FW_BURN_REJECTED_NOT_ALLOWED_SAME_UIDD 
0x26: FW_BURN_REJECTED_INTERNAL_ERROR_5 
0x27: FW_BURN_REJECTED_INTERNAL_ERROR_6 
0x28: FW_BURN_REJECTED_FLASH_WRITE_PROTECTED
0x29: FW_BURN_REJECTED_INTERNAL_ERROR_7 0x2A: FW_BURN_REJECTED_INTERNAL_ERROR_8 0x2B: FW_BURN_REJECTED_INTERNAL_ERROR_90x2C: FW_BURN_REJECTED_DPA_ELF
0x2D: FW_BURN_REJECTED_DPA_CRYPTO_BLOB
0x2E: FW_BURN_REJECTED_DPA_APP_METADATA
0x2F: FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE
0x30: FW_BURN_REJECTED_DPA_CONTAINER_VERIFY
0x31: FW_BURN_REJECTED_INTERNAL_ERROR_10 
0x32: REJECTED_DEV_IMAGE_ON_PROD_DEVICE
0x33: FW_BURN_REJECTED_DPA_APP_MANIFEST

Other values should be treated as an unknown error. */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t error_code;
	/* Description - Indicates the estimated progress status of the current operation executed by the FSM. Valid values are 0..100.
101 indicates that progress reporting is not supported for this update state. */
	/* 0xc.16 - 0xc.22 */
	/* access: RO */
	u_int8_t control_progress;
	/* Description - For handle_owner_type BMC, command-interface and ICMD, indicates the identifier of the host of the handle owner.
Otherwise reserved */
	/* 0xc.24 - 0xc.27 */
	/* access: RO */
	u_int8_t handle_owner_host_id;
	/* Description - Type of entity holding the update handle:
0x0: unspecified
0x1: Chassis BMC
0x2: MAD
0x3: BMC
0x4: command interface
0x5: ICMD 
Other values are reserved. */
	/* 0xc.28 - 0xc.31 */
	/* access: RO */
	u_int8_t handle_owner_type;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Component size in bytes. 
Valid for UPDATE_COMPONENT instruction. Specifying the size may shorten the update time.
Value 0x0 means that size is unspecified. */
	/* 0x10.0 - 0x10.31 */
	/* access: WO */
	u_int32_t component_size;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Peripheral device type:
0: Switch_or_NIC
1: Gearbox */
	/* 0x14.0 - 0x14.7 */
	/* access: INDEX */
	u_int8_t device_type;
	/* Description - Indicates warnings reported during the completion that did not prevent successful completion of the instruction
0x0: OK
0x1: WARNING_DPA_API_OS_INCOMPATIBLE
0x2: WARNING_DPA_API_FW_INCOMPATIBLE */
	/* 0x14.8 - 0x14.15 */
	/* access: RO */
	u_int8_t warning_code;
	/* Description - Device number.
For gearboxes, the index represents the gearbox die. 
For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.
For QM-3 CPO system, device index represents OE or ELS device. */
	/* 0x14.16 - 0x14.27 */
	/* access: INDEX */
	u_int16_t device_index;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - In multiple downstream devices action, the action will be executed starting on device_index and ending on device_index + device_index_size - 1. */
	/* 0x18.0 - 0x18.11 */
	/* access: RW */
	u_int16_t device_index_size;
	/* Description - The device index that the action has been rejected to. */
	/* 0x18.16 - 0x18.27 */
	/* access: RO */
	u_int16_t rejected_device_index;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - [DWIP]:
Component Specific Error Code
Relevant only for Linkx failed updates */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t component_specific_err_code;
};

/* Description -   */
/* Size in bytes - 144 */
struct reg_access_hca_mcda_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Update handle registered when the FSM was activated. */
	/* 0x0.0 - 0x0.23 */
	/* access: RW */
	u_int32_t update_handle;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Offset of accessed address relative to component start. Accesses must be in accordance to log_mcda_word_size in Table 2931, "MCQI CAPABILITIES Info Layout," on page 3371 */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Size of the data accessed, given in bytes */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Data block accessed */
	/* 0x10.0 - 0x8c.31 */
	/* access: RW */
	u_int32_t data[32];
};

/* Description -   */
/* Size in bytes - 148 */
struct reg_access_hca_mcia_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module Status
0: SUCCESS
1: NO_EEPROM_MODULE. No response from module's EEPROM.
2: MODULE_NOT_SUPPORTED. Module type not supported by the device. 3: MODULE_NOT_CONNECTED. No module present indication. 
4: MODULE_TYPE_INVALID - module is not supported by INI. 

9: I2C_ERROR. Error occurred while trying to access the module's EEPROM using I2C.
16: MODULE_DISABLED - module is disabled 
	*/
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t status;
	/* Description - Slot index
0: Main board */
	/* 0x0.12 - 0x0.15 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Module number
NIC: Range 0 .. MGPIR.num_of_modules -1 
	*/
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - [DWIP]:
Page Number Valid
0: write page number
1: don't write page number
Valid only if module is in SW control */
	/* 0x0.29 - 0x0.29 */
	/* access: OP */
	u_int8_t pnv;
	/* Description - Lock Page bit. 
When bit is set, FW can access the last accessed page.
After boot and ISSU, default value is 0.

	*/
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t l;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Device address

	*/
	/* 0x4.0 - 0x4.15 */
	/* access: INDEX */
	u_int16_t device_address;
	/* Description - Page number
Reserved when MCIA.l = 1 or when MCIA.pnv = 1

	*/
	/* 0x4.16 - 0x4.23 */
	/* access: INDEX */
	u_int8_t page_number;
	/* Description - I2C device address
	*/
	/* 0x4.24 - 0x4.31 */
	/* access: INDEX */
	u_int8_t i2c_device_address;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of bytes to read/write (up to 128 bytes) */
	/* 0x8.0 - 0x8.15 */
	/* access: INDEX */
	u_int16_t size;
	/* Description - Bank number
	*/
	/* 0x8.16 - 0x8.23 */
	/* access: INDEX */
	u_int8_t bank_number;
	/* Description - [DWIP][switch_internal]
Background operation
0: Foreground mode (legacy)
1: Background mode

When working on background mode, FW shall return STS_OK immediately and return the transaction data via MCIA trap. */
	/* 0x8.27 - 0x8.27 */
	/* access: OP */
	u_int8_t bg_mode;
	/* Description - 0: password length is 4B (password_msb is reserved)
1: password length is 8B (password_msb is used) */
	/* 0x8.28 - 0x8.28 */
	/* access: OP */
	u_int8_t passwd_length;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The password that is written to the module password field.
This field is reserved when passwd_cap is not set to 1. 
Reserved when module is in SW control. */
	/* 0xc.0 - 0xc.31 */
	/* access: OP */
	u_int32_t password;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Bytes to read/write
Note: some FW versions support only 12*4B
See MCAM bit34 */
	/* 0x10.0 - 0x8c.31 */
	/* access: RW */
	u_int32_t dword[32];
/*---------------- DWORD[36] (Offset 0x90) ----------------*/
	/* Description - password msb
Supported only when MCAM bit34 is set
Supported only when passwd_cap is set
Reserved when passwd_length = 0 */
	/* 0x90.0 - 0x90.31 */
	/* access: RW */
	u_int32_t password_msb;
};

/* Description -   */
/* Size in bytes - 148 */
struct reg_access_hca_mcqi_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Component index gathered by "MCQS - Management Component Query Status" */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t component_index;
	/* Description - Device number.
For gearboxes, the index represents the gearbox die. 
For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.

For Clock Source EEPROM, the index represents the Clock Source Index, starting from 1

For DPA_APPS_INFO, the index represents the index of the DPA app to query, starting from 0 */
	/* 0x0.16 - 0x0.27 */
	/* access: INDEX */
	u_int16_t device_index;
	/* Description - When set, the register will return information about the pending component (if available) */
	/* 0x0.31 - 0x0.31 */
	/* access: INDEX */
	u_int8_t read_pending_component;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Peripheral device type:
0: Switch / NIC
1: Gearbox */
	/* 0x4.0 - 0x4.7 */
	/* access: INDEX */
	u_int8_t device_type;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Component properties set.
0x0: CAPABILITIES
0x1: VERSION
0x5: ACTIVATION_METHOD
0x6: LINKX_PROPERTIES
0x7: CLOCK_SOURCE_PROPERTIES

0x9: DPA_APPS_INFO
Other values are reserved */
	/* 0x8.0 - 0x8.4 */
	/* access: RW */
	u_int8_t info_type;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Properties set structure size, given in bytes. */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t info_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The requested/returned data offset from the section start, given in bytes.
Must be DWORD aligned.
If offset is invalid, FW will return an error. */
	/* 0x10.0 - 0x10.31 */
	/* access: RW */
	u_int32_t offset;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - The requested/returned data size, given in bytes.
If data_size is not DWORD aligned, the last bytes are zero padded.
If size is invalid, FW will return an error. */
	/* 0x14.0 - 0x14.15 */
	/* access: RW */
	u_int16_t data_size;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Properties set structure according to info_type.
CAPABILITIES - See Table 2931, "MCQI CAPABILITIES Info Layout," on page 3371
VERSION - See Table 2933, "MCQI VERSION Info Layout," on page 3373
ACTIVATION_METHOD - See Table 2937, "MCQI ACTIVATION_METHOD Info Layout," on page 3375
LINKX_PROPERTIES - See Table 2939, "MCQI LINKX_PROPERTIES Info Layout," on page 3376
CLOCK_SOURCE_PROPERTIES - See Table 2941, "MCQI CLOCK_SOURCE_PROPERTIES Layout," on page 3378
DPA_APPS_INFO - See Table 2943, "MCQI DPA_APPS_INFO Layout," on page 3379 */
	/* 0x18.0 - 0x90.31 */
	/* access: RO */
	union reg_access_hca_mcqi_reg_data_auto_ext data;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mcqs_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Component Index. Values range from 0 to the last component indicated by last_index_flag. */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t component_index;
	/* Description - Device number.
For gearboxes, the index represents the gearbox die. 
For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.
For Clock synchronizer, index is used to represent the clock sync' device index. Starting from 1. */
	/* 0x0.16 - 0x0.27 */
	/* access: INDEX */
	u_int16_t device_index;
	/* Description - When set, this component not supported. */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t component_not_supported;
	/* Description - When set, this component is the last component (highest component_index). */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t last_index_flag;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - This field uniquely identifies a specific component type. 
0x1: BOOT_IMG
0x4: OEM_NVCONFIG
0x5: MLNX_NVCONFIG
0x6: CS_TOKEN
0x7: DBG_TOKEN
0xA: Gearbox
0xB: CC_ALGO - Congestion Control Algorithm
0xC: LINKX_IMG
0xD: CRYPTO_TO_COMMISSIONING
0xE: RMCS_TOKEN
0xF: RMDT_TOKEN
0x10: CRCS_TOKEN 
0x11: CRDT_TOKEN 
0x12: CLOCK_SYNC_EEPROM  
0x15: DIGITAL_CACERT - Certificate to be trusted by the device0x17: DIGITAL_CACERT_REMOVAL

0x20: PSC_TOKEN

Other values are reserved
[DWIP]: 0x1A: LINKX_FW_ELS

0x1C: DPA_COMPONENT
0x1D: DPA_COMPONENT_REMOVAL
0x1E: MTDT_TOKEN
	*/
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t identifier;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Component state in update flow, see Section  10.2.1, "Component Update State," on page  1099:
0x0: IDLE
0x1: IN_PROGRESS
0x2: APPLIED
0x3: ACTIVE 
0x4: ACTIVE_PENDING_RESET
0x5: FAILED
0x6: CANCELED
0x7: BUSY

Other values are reserved */
	/* 0x8.0 - 0x8.3 */
	/* access: RO */
	u_int8_t component_update_state;
	/* Description - The status of the component:
0x0: NOT_PRESENT - The component is supported by the device but, currently not present
0x1: PRESENT - This component is present. For downstream devices link LinkX component, this is an indication that the binary image is present at the host device memory.
0x2: IN_USE - The component is present and currently in use. */
	/* 0x8.4 - 0x8.8 */
	/* access: RO */
	u_int8_t component_status;
	/* Description - Progress in percentage (from 0 to 100). This field is only relevant for cables. */
	/* 0x8.9 - 0x8.15 */
	/* access: RO */
	u_int8_t progress;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Peripheral device type:
0: Switch_or_NIC
1: Gearbox */
	/* 0xc.0 - 0xc.7 */
	/* access: INDEX */
	u_int8_t device_type;
	/* Description - For last_update_state_changer_type BMC, command-interface and ICMD, indicates the identifier of the host of the handle owner. Otherwise reserved. */
	/* 0xc.24 - 0xc.27 */
	/* access: RO */
	u_int8_t last_update_state_changer_host_id;
	/* Description - Indicates which entity was the last to change the component_update_state of this component.
0x0: unspecified
0x1: Chassis_BMC
0x2: MAD
0x3: BMC
0x4: command_interface
0x5: ICMD

Other values are reserved */
	/* 0xc.28 - 0xc.31 */
	/* access: RO */
	u_int8_t last_update_state_changer_type;
};

/* Description -   */
/* Size in bytes - 268 */
struct reg_access_hca_mfba_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash select - selects the flash device.
Only zero is supported for NICs with a single flash device 
Range between 0 .. MFPA.flash_num -1 */
	/* 0x0.4 - 0x0.5 */
	/* access: INDEX */
	u_int8_t fs;
	/* Description - Capability bit - If set to '1', address field is 32 bit length. */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t add_cap_32b;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The size of the data to be written or read in bytes
Should comply with block_size and block_alignment fields in MFPA. */
	/* 0x4.0 - 0x4.8 */
	/* access: OP */
	u_int16_t size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The start address of this read or write access in bytes. Should comply with block_size and block_alignment fields in MFPA. */
	/* 0x8.0 - 0x8.31 */
	/* access: INDEX */
	u_int32_t address;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The data to be written or read data. */
	/* 0xc.0 - 0x108.31 */
	/* access: RW */
	u_int32_t data[64];
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_hca_mfbe_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash select - selects the flash device.
Only zero is supported for NICs with a single flash device. 
Range between 0 .. MFPA.flash_num -1 */
	/* 0x0.4 - 0x0.5 */
	/* access: INDEX */
	u_int8_t fs;
	/* Description - Erase a 64KB flash area in one bulk operation. */
	/* 0x0.29 - 0x0.29 */
	/* access: WO */
	u_int8_t bulk_64kb_erase;
	/* Description - Erase a 32KB flash area in one bulk operation. */
	/* 0x0.30 - 0x0.30 */
	/* access: WO */
	u_int8_t bulk_32kb_erase;
	/* Description - Capability bit - If set to '1', address field is 32 bit length. */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t add_cap_32b;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The start address (in bytes) of this erase operation. Must be aligned with the selected erase size (sector, 32KB or 64KB). */
	/* 0x8.0 - 0x8.31 */
	/* access: INDEX */
	u_int32_t address;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mfpa_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash select - selects the flash device.
Only zero is supported for NICs with a single flash device.
Range between 0 .. flash_num -1
	*/
	/* 0x0.4 - 0x0.5 */
	/* access: INDEX */
	u_int8_t fs;
	/* Description - Capability bit - If set to '1', boot_address field is 32 bit length. */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t add_cap_32b;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The flash address from which the firmware will boot in the next reset (warm start). */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t boot_address;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The number of flash devices1: there is 1 flash device, etc. */
	/* 0x10.0 - 0x10.3 */
	/* access: RO */
	u_int8_t flash_num;
	/* Description - If set, MFMC register supports setting write protect with sub-sector- blocks
Sub-sector block size is available in MFMC.sub_sector_protect_size */
	/* 0x10.16 - 0x10.16 */
	/* access: RO */
	u_int8_t sub_sector_wrp_en;
	/* Description - If set, MFMC register supports setting write protect with sector blocks.
Sector block size is available in MFMC.sector_protect_size */
	/* 0x10.17 - 0x10.17 */
	/* access: RO */
	u_int8_t sector_wrp_en;
	/* Description - If set, MFBE register supports 64KB bulk erase operation.
	*/
	/* 0x10.29 - 0x10.29 */
	/* access: RO */
	u_int8_t bulk_64kb_erase_en;
	/* Description - If set, MFBE register supports 32KB bulk erase operation. */
	/* 0x10.30 - 0x10.30 */
	/* access: RO */
	u_int8_t bulk_32kb_erase_en;
	/* Description - Work In Progress. Indicates that the flash is currently busy. */
	/* 0x10.31 - 0x10.31 */
	/* access: RO */
	u_int8_t wip;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Return the flash JEDEC ID value returned by the standard Read JEDEC ID command that is available in most flash devices. */
	/* 0x14.0 - 0x14.23 */
	/* access: RO */
	u_int32_t jedec_id;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The minimal unit that can be erased with and MFBE command (in bytes). */
	/* 0x18.0 - 0x18.9 */
	/* access: RO */
	u_int16_t sector_size;
	/* Description - Log 2 of the requested write alignment in bytes. Write access to the flash
must not cross this alignment.
Read and write access must be aligned to this value. */
	/* 0x18.16 - 0x18.23 */
	/* access: RO */
	u_int8_t block_alignment;
	/* Description - The block size in byes of the flash device, max read size for MFBA (typically 128 bytes). */
	/* 0x18.24 - 0x18.31 */
	/* access: RO */
	u_int8_t block_size;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Bitmask indicates which capabilities are supported.
Bit 15..0: reserved 

Bit 16: Set write protect supported (register MFMC supports setting write protection)
Bit 17: quad enable read write is supported (register MFMC supports setting quad enable)
Bit 18: set dummy cycle supported (register MFMC supports setting dummy cycles) */
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t capability_mask;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_mfrl_reg_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The firmware reset trigger.
Bit 0: TRIGGER0 - live patch. When selecting this trigger, all other fields are NA.
Bit 1: TRIGGER1 - Immediate Reset. Note that this reset trigger must be selected explicitly by user and cannot be triggered as part of default logic.
Bit 3: TRIGGER3 - PCIe link toggle or hot reset. For this reset trigger, you need to configure pci_reset_req_method.
Bit 6: TRIGGER6 - PERST
Other bits are reserved. */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t reset_trigger;
	/* Description - Each bit represents a chip reset type.
If set to '1', the reset is supported.
Bit 0: Full_Chip_Reset
Bit 1: Keep_Network_Port_Active_During_Reset
Bit 3: ARM_Only_Reset
Bit 4: ARM_OS_Shutdown
Bit 5: Network_Reset - Keep PCIe active during reset. DWIP */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t reset_type;
	/* Description - Reset state.
0: IDLE
1: Negotiation_In_Progress
2: Reset_In_Progress
3: Error_Negotiation_Timeout
4: Error_Negotiation_Dis_Acknowledgment
5: Error_Driver_Unload_Timeout - DWIP
6: Error- ARM_OS_Is_Up - please shut down. DWIP
7: ARM_OS_Shut_Down_In_Progress - DWIP
8: Waiting_For_Reset_Trigger
All others are reserved */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t reset_state;
	/* Description - FW reset Method selector; Support for the different reset methods exposed through reset_info register. 
0: Link_Disable
1: Hot_Reset - SBR)
All others are reserved */
	/* 0x4.21 - 0x4.23 */
	/* access: RW */
	u_int8_t pci_reset_req_method;
	/* Description - The requested reset type.
When reset_trigger = Immediate (1), reset_type_sel valid values are: bit3 or bit4 (ARM only reset or ARM os shutdown) */
	/* 0x4.24 - 0x4.26 */
	/* access: RW */
	u_int8_t rst_type_sel;
	/* Description - Response of the driver for the reset request.
1: Acknowledgment
2: Dis_acknowledgment
3: Reserved */
	/* 0x4.27 - 0x4.28 */
	/* access: WO */
	u_int8_t pci_sync_for_fw_update_resp;
	/* Description - This field defines the reset flow. 
0: Legacy_Flow
1: Synced_Driver_Flow
2: Synced_Tool_Flow
Synced driver flow will not require to issue MFRL command
from other hosts (x86 / ARM for SoC)
Synced tool flow required to be executed from external host (should not be executed from internal host). */
	/* 0x4.29 - 0x4.30 */
	/* access: RW */
	u_int8_t pci_sync_for_fw_update_start;
	/* Description - Setting this bit to 1 indicates a need of rescan for the corresponding PCI slot */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t pci_rescan_required;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_hca_mfsv_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When this bit is set, it indicates that it is allowed for the boot FW to program the FW security version related EFUSEs if needed. This bit is not relevant in case the FW operates in an automatically EFUSEs programming approach (set in the INI file). Once set to 1, this configuration will be relevant only for the upcoming boot, thus this configuration will be set back to 0 upon next boot.

	*/
	/* 0x0.0 - 0x0.0 */
	/* access: RW */
	u_int8_t efuses_prog_en;
	/* Description - Firmware security version status.0: EFUSEs value is equal to the currently running FW image value. No change is needed.1: EFUSEs value is smaller than the currently running FW image value. An update to the EFUSEs is required.2: There is pending image, MFSV is rejected
3: Reserved

	*/
	/* 0x0.1 - 0x0.2 */
	/* access: RO */
	u_int8_t fw_sec_ver_stat;
	/* Description - EFUSEs programming method.0: manually. Upon boot, if FW indicates that FW_sec_ver_stat is 1 and only if EFUSEs_prog_en is 1, it will program the EFUSEs as needed.1: automatically. Upon boot, if FW indicates that FW_sec_ver_stat is 1, it will program the EFUSEs as needed.

	*/
	/* 0x0.3 - 0x0.3 */
	/* access: RO */
	u_int8_t efuses_prog_method;
	/* Description - 0: EFUSEs value is equal to the currently running FW image value. No change is needed. 
1: EFUSEs value is smaller than the currently running FW image value. An update to the EFUSEs is required. 
	*/
	/* 0x0.4 - 0x0.4 */
	/* access: RW */
	u_int8_t revoke_efuse_prog;
	/* Description - 0: No pending EFUSE programming command 
1: There is pending MFSV command 

	*/
	/* 0x0.5 - 0x0.5 */
	/* access: RO */
	u_int8_t pending_efuse_prog;
	/* Description - [Internal]
Relevant only from CX8/QM3/ArcusE 
When this bit is set, device should increase dummy ratchet value (fuse_psc_reserved2_field_ratchet) 

In case that fuse_psc_reserved2_field_ratchet = 0xFFFF, return Fuse_failure = 2. */
	/* 0x0.6 - 0x0.6 */
	/* access: RO */
	u_int8_t dummy_ratchet_prog_en;
	/* Description -  */
	/* 0x0.8 - 0x0.9 */
	/* access: RO */
	u_int8_t fuse_failure;
	/* Description - Index
0: NCORE FW
1: PSC_BL1
2: PSC_FW
3: BCT
4: reserved2_field_ratchet
5-15: Reserved */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Image security version value */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t img_sec_ver;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - EFUSEs security version value */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t efuses_sec_ver;
};

/* Description -   */
/* Size in bytes - 160 */
struct reg_access_hca_mgir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hardware Information, see Table 2959, "Hardware Info Layout," on page 3393 */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_hca_mgir_hardware_info_ext hw_info;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Firmware Information, see Table 2962, "Firmware Info Layout," on page 3396 */
	/* 0x20.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_hca_mgir_fw_info_ext fw_info;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description - Software Information, see Table 2964, "Software Info Layout," on page 3399
This field indicates the oldest software version compatible with the current firmware */
	/* 0x60.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_hca_mgir_sw_info_ext sw_info;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description - Development Information, see Table 2968, "Development Info Layout," on page 3403 */
	/* 0x80.0 - 0x98.31 */
	/* access: RW */
	struct reg_access_hca_mgir_dev_info_ext dev_info;
};

/* Description -   */
/* Size in bytes - 288 */
struct reg_access_hca_misoc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Type of component query:
0x0: ARM_ATF
0x1: ARM_UEFI
0x2: DPU_BMC
0x3: CEC
0x5: BF_BUNDLE
0x7: BSP
0x8: NIC_GOLDEN
0x9: ARM_GOLDEN
All other values are reserved */
	/* 0x0.0 - 0x0.3 */
	/* access: INDEX */
	u_int8_t type;
	/* Description - If set, the query will be for the pending version instead on the current version */
	/* 0x0.30 - 0x0.30 */
	/* access: INDEX */
	u_int8_t query_pending;
	/* Description - If set, the version information for this component type is not available
In this case the version will be all zeros */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t query_not_available;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The version as a null-terminated ASCII string
Null termination will not be present if version takes up all of the field size */
	/* 0x10.24 - 0x110.23 */
	/* access: RO */
	u_int8_t version[256];
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_hca_mmdio_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0 - NOP
1 - Address (reserved for Clause 22)
2 - Read
3 - Write
4 - Post Read Increment Address (reserved for Clause 22)
6 - Address + Read - Generates Address cycle and then Read cycle in Clause 45 (reserved for Clause 22)
7 - Address + Write - Generates Address cycle and then Write cycle in Clause 45 (reserved for Clause 22) */
	/* 0x0.0 - 0x0.2 */
	/* access: WO */
	u_int8_t operation;
	/* Description - MDIO Definition:
0 - Clause 22
1 - Clause 45 */
	/* 0x0.8 - 0x0.9 */
	/* access: WO */
	u_int8_t clause;
	/* Description - Selection of the MDIO interface */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t mdio_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reg Address (Clause 22) / Dev Type (Clause 45) */
	/* 0x4.0 - 0x4.4 */
	/* access: RW */
	u_int8_t reg_adr;
	/* Description - PHY Address (PHYAD) */
	/* 0x4.8 - 0x4.12 */
	/* access: RW */
	u_int8_t phy_adr;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Data (Clause 22) / Address/Data (Clause 45) */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t data;
	/* Description - Address (Clause 45)
This field is only valid for Address + Read and Address + Write operations, providing the address. For other Clause 45 operations the data field provides the address when appropriate. */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t address;
};

/* Description -   */
/* Size in bytes - 128 */
struct reg_access_hca_mmhi_reg_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Identifier for the host used to access the register */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t host_number;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Bit per Host, when set indicating this host is present in the current Multi-Host configuration.
Value 0x0 indicates this field in not valid. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t host_en;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_hca_mnvdi_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_hca_config_item_ext configuration_item_header;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mnvgc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0:unsupported
1: supported */
	/* 0x0.0 - 0x0.0 */
	/* access: RO */
	u_int8_t nvda_read_factory_settings;
	/* Description - NVDA Read current settings. Indicates if reading the current settings by NVDA is supported.
0: unsupported
1: supported */
	/* 0x0.1 - 0x0.1 */
	/* access: RO */
	u_int8_t nvda_read_current_settings;
	/* Description - When set, TLVs of other hosts may be modified. */
	/* 0x0.2 - 0x0.2 */
	/* access: RO */
	u_int8_t priv_nv_other_host;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_mnvia_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Information targeted for invalidation
0: ALL - all NVRAM parameters.
	All other values are reserved. */
	/* 0x0.0 - 0x0.2 */
	/* access: WO */
	u_int8_t target;
	/* Description - The entity which perform the invalidate.
The encoding same as writer_id in Configuration Item register (See Table 3068, "Configuration Item Header Layout," on page 3465). */
	/* 0x0.4 - 0x0.8 */
	/* access: RW */
	u_int8_t writer_id;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_mnvqc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Configuration item type according to its class. 
Table 3070, "Configuration Item Data Type Class Global Layout," on page 3469
Table 3072, "Configuration Item Data Type Class Physical Port Layout," on page 3469
Table 3074, "Configuration Item Data Type Class Per Host-PF Layout," on page 3470
Table 3076, "Configuration Item Data Type Class Log Layout," on page 3470
Table 3078, "Configuration Item Data Type Class File Layout," on page 3471
Table 3080, "Configuration Item Data Type Class Host Layout," on page 3471

Table 3084, "Configuration Item Data Type Class Multi Instance Layout," on page 3473 */
	/* 0x0.0 - 0x0.31 */
	/* access: INDEX */
	u_int32_t type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The configuration item is supported and can be read */
	/* 0x4.0 - 0x4.0 */
	/* access: RO */
	u_int8_t support_rd;
	/* Description - The configuration item is supported and can be updated */
	/* 0x4.1 - 0x4.1 */
	/* access: RO */
	u_int8_t support_wr;
	/* Description - The maximal version of the configuration item supported by the device */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t version;
};

/* Description -   */
/* Size in bytes - 160 */
struct reg_access_hca_mpcir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Bitmask of which instance to select.
Relevant only to vmod.
0: update vmod 0
1: update vmod 1
... */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t instance;
	/* Description - Bitmask of which FW entity to select.
0: switch_fw
1: virtual_module

note - if all bits are zero fw_entity will be switch_fw (legacy)
If more than one bit is set instance field will be ignored - update all instances. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t fw_entity;
	/* Description - If set to '01', activates the flow of preparation for FW ISSU, on all services. The values in op-codes for "per-service" are ignored.
If set to '10', returns to operational state on all services. The values in op-codes for "per-service" are ignored.
11 - get_status for all services */
	/* 0x0.30 - 0x0.31 */
	/* access: OP */
	u_int8_t all;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - For each of the services, the following operations are available:
0: N/A (no action)
1: start preparation flow for FW ISSU 
2: return to operational service (end of FW ISSU flow)
3: get status

When set to '3', the current status will appear in corresponding _stat fields. */
	/* 0x4.0 - 0x4.1 */
	/* access: OP */
	u_int8_t ports;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Status for each of the services. 
0: not in FW ISSU flow state (FW ISSU flow is not initiated) 
1: done with preparations for FW ISSU flow
2: Preparation for FW ISSU flow started but FW still not done service handling [Internal]: busy with some other critical flow). */
	/* 0xc.0 - 0xc.1 */
	/* access: RO */
	u_int8_t ports_stat;
};

/* Description -   */
/* Size in bytes - 44 */
struct reg_access_hca_mpegc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - the node within each depth. */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t node;
	/* Description - PCIe index number (Internal domain index)
Reserved when access is from the host */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t pcie_index;
	/* Description - depth level of the DUT of some hierarchy */
	/* 0x0.24 - 0x0.29 */
	/* access: INDEX */
	u_int8_t depth;
	/* Description - DPN version
0: multi_topology_unaware_sw
1: multi_topology_aware_sw */
	/* 0x0.30 - 0x0.30 */
	/* access: INDEX */
	u_int8_t DPNv;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Field select indicated which writable fields to modify.
Bit 0: tx_lossy_overflow_oper
Bit 1 : outbound_stalled_reads_th
Bit 2 :outbound_stalled_writes_th
Bit 3 : tx_overflow_sense
Bit 4 : mark_tx_action_cqe
Bit 5 : mark_tx_action_cnp
Bit 6: virtual_hot_plug_unplug (supported only for internal host)
Bit 7: segment_base and seg_valid */
	/* 0x4.0 - 0x4.15 */
	/* access: WO */
	u_int16_t field_select;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - When overflow encountered for lossy packets, it will be dropped or marked and will be counted in "tx_overflow_buffer_dropped_pkt" or "tx_overflow_buffer_marked_pkt" counter.
00 - Disabled
01 - drop - overflow traffic will be dropped.  
10 - mark - overflow traffic will be marked in the CE field in the CqE.  Supported only when MCAM.mark_tx_action_cqe or MCAM.mark_tx_action_cnp are '1'. 
	*/
	/* 0x8.0 - 0x8.1 */
	/* access: RW */
	u_int8_t tx_lossy_overflow_oper;
	/* Description - segment number associated with the link PCI hierarchy
The value here will be reflected in the MPIR segment base
reserved when pcie_segment is not set in MPCAM */
	/* 0x8.16 - 0x8.23 */
	/* access: RW */
	u_int8_t segment_base;
	/* Description - when set the segment base is valid, when clear the segment base is invalid
the value here will be reflected in the MPIR seg_valid
reserved when pcie_segment is not set in MPCAM */
	/* 0x8.24 - 0x8.24 */
	/* access: RW */
	u_int8_t seg_valid;
	/* Description - When this bit is set, the marking action will be generating a CNP for RoCE traffic. Supported only when MCAM.mark_tx_action_cnp is '1'. */
	/* 0x8.29 - 0x8.29 */
	/* access: RW */
	u_int8_t mark_cnp;
	/* Description - When this bit is set, the marking action will be set in the CqE for TCP traffic. Supported only when MCAM.mark_tx_action_cqe is '1'. */
	/* 0x8.30 - 0x8.30 */
	/* access: RW */
	u_int8_t mark_cqe;
	/* Description - Set the sensibility level of the tx overflow mechanism. 
0 - Aggressive 1 - Dynamic adjustment. When tx_lossy_overflow_oper is disabled, tx_overflow_sense must be disabled. Supported only when MCAM.dynamic_tx_oveflow is '1'. */
	/* 0x8.31 - 0x8.31 */
	/* access: RW */
	u_int8_t tx_overflow_sense;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Each time that the counter outbound_stalled_writes will exceed this threshold, will be counted in the counter outbound_stalled_writes_events - range 0   100. */
	/* 0xc.0 - 0xc.6 */
	/* access: RW */
	u_int8_t outbound_stalled_writes_th;
	/* Description - Each time that the counter outbound_stalled_reads will exceed this threshold, will be counted in the counter outbound_stalled_reads_events - range 0   100. */
	/* 0xc.8 - 0xc.14 */
	/* access: RW */
	u_int8_t outbound_stalled_reads_th;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Operation to perform
0: Idle - no operation required (default)
1: Emulate hot removal
2: Emulate hot insertion
3-15: Reserved */
	/* 0x10.16 - 0x10.19 */
	/* access: RW */
	u_int8_t operation;
	/* Description - Operation completion status
0: Operation in process
1: Unplugged
2: Plugged
3: Warning - disconnecting an already disconnected bus cannot be performed
4: Warning - connecting an already connected bus cannot be performed
5: Error - unknown bus number or no device installed on selected bus */
	/* 0x10.24 - 0x10.31 */
	/* access: RO */
	u_int8_t status;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_hca_mpein_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - the node within each depth. */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t node;
	/* Description - PCIe index number (Internal domain index)
Reserved when access is from the host, but can be used when operating in Socket-Direct mode. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t pcie_index;
	/* Description - depth level of the DUT of some hierarchy */
	/* 0x0.24 - 0x0.29 */
	/* access: INDEX */
	u_int8_t depth;
	/* Description - DPN version
0: multi_topology_unaware_sw
1: multi_topology_aware_sw */
	/* 0x0.30 - 0x0.30 */
	/* access: INDEX */
	u_int8_t DPNv;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Max Link Speed:
Bit 0: 2.5G - (Gen1)
Bit 1: 5G - (Gen2)
Bit 2: 8G - (Gen3)
Bit 4: 16G - (Gen4)
Bit 5: 32G (Gen5)
Bit 6: 32G PAM-4 (Gen6) */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t link_speed_enabled;
	/* Description - Maximum Link Width enabled:
1: 1x
2: 2x
4: 4x
8: 8x
16: 16x */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t link_width_enabled;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Current Link Speed:
Bit 0: 2.5G (Gen1)
Bit 1: 5G (Gen2)
Bit 2: 8G (Gen3)
Bit 4: 16G (Gen4)
Bit 5: 32G (Gen5)
Bit 6: 32G PAM-4 (Gen6) */
	/* 0xc.0 - 0xc.15 */
	/* access: RO */
	u_int16_t link_speed_active;
	/* Description - Negotiated Link Width, pcie_link_width active:
1: 1x
2: 2x
4: 4x
8: 8x
16: 16x */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t link_width_active;
	/* Description - The physical lane position of logical lane0 */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t lane0_physical_position;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Number of Total Virtual Functions (for all PFs) */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t num_of_vfs;
	/* Description - Number of Physical Functions (PFs) */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t num_of_pfs;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Bus Device Function - only for function0 */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t bdf0;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Reversal mode of the link:
0 - straight 
1 - reversal

Note: together with lane0_physical_position provide the physical lane. */
	/* 0x18.0 - 0x18.0 */
	/* access: RO */
	u_int8_t lane_reversal;
	/* Description - Indicates the specific type of this PCI Express Function. Note that different Functions in a multi-Function device can generally be of different types.
0 - PCI Express Endpoint port
4 - Root Port of PCI Express Root Complex
5 - PCI Express Upstream port
6 - PCI Express Downstream port */
	/* 0x18.12 - 0x18.15 */
	/* access: RO */
	u_int8_t port_type;
	/* Description - Indicates the status of PCI power consumption limitations.
0: PCI power report could not be read.
1: Sufficient power reported.
2: Insufficient power reported.
3-7: Reserved */
	/* 0x18.16 - 0x18.18 */
	/* access: RO */
	u_int8_t pwr_status;
	/* Description - Max payload size in bytes:
0 - 128B
1 - 256B
2 - 512B
3 - 1024B
4 - 2048B
5 - 4096B */
	/* 0x18.24 - 0x18.27 */
	/* access: RO */
	u_int8_t max_payload_size;
	/* Description - Max read request size in bytes:
0 - 128B
1 - 256B
2 - 512B
3 - 1024B
4 - 2048B
5 - 4096B */
	/* 0x18.28 - 0x18.31 */
	/* access: RO */
	u_int8_t max_read_request_size;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Power reported by the PCI device. The units are in Watts.
0: Power is unknown. */
	/* 0x1c.0 - 0x1c.11 */
	/* access: RO */
	u_int16_t pci_power;
	/* Description - Peer Max Link Speed:
Bit 0: 2.5G - (Gen1)
Bit 1: 5G - (Gen2)
Bit 2: 8G - (Gen3)
Bit 4: 16G - (Gen4)
Bit 5: 32G (Gen5)
Bit 6: 32G PAM-4 (Gen6) */
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t link_peer_max_speed;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - FLIT is supported for the current active speed */
	/* 0x20.0 - 0x20.0 */
	/* access: RO */
	u_int8_t flit_sup;
	/* Description - Precoding is supported for the current active speed */
	/* 0x20.1 - 0x20.1 */
	/* access: RO */
	u_int8_t precode_sup;
	/* Description - FLIT is active for the current speed */
	/* 0x20.8 - 0x20.8 */
	/* access: RO */
	u_int8_t flit_active;
	/* Description - precoding is active for the current speed */
	/* 0x20.9 - 0x20.9 */
	/* access: RO */
	u_int8_t precode_active;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - device_status bit mask:
Bit 0: Correctable_error
Bit 1: Non_Fatal_Error_detection
Bit 2: Fatal_Error_detected
Bit 3: Unsupported_request_detected
Bit 4: AUX_power 
Bit 5: Transaction_Pending */
	/* 0x24.16 - 0x24.31 */
	/* access: RO */
	u_int16_t device_status;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mpir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of PCIe buses available for the host to connect ot the device.
'0' when operating in non-Socket-Direct mode. */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t host_buses;
	/* Description - the node within each depth. */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t node;
	/* Description - Internal domain index */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t pcie_index;
	/* Description - depth level of the DUT of some hierarchy */
	/* 0x0.24 - 0x0.29 */
	/* access: INDEX */
	u_int8_t depth;
	/* Description - DPN version
0: multi_topology_unaware_sw
1: multi_topology_aware_sw */
	/* 0x0.30 - 0x0.30 */
	/* access: INDEX */
	u_int8_t DPNv;
	/* Description - Socket-Direct mode indication.
0: non-Socket-Direct mode (single host or multi-host)
1: Socket-Direct mode, for querying host */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t sdm;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - sunbordinate bus - the highest bus number that subordinates to switch.
Default value of '0' in case it is not a switch port. */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t subordinate_bus;
	/* Description - secondary bus - the internal logic bus in the switch. 
Default value of '0' in case it is not a switch port. */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t secondary_bus;
	/* Description - if segment valid is set this field has the segment number of the PCIe hierarchy of the link. 
seg_cap = 1 : segment base that was captured in Flit mode
seg_cap = 0 : segment base that was set by software
reserved when pcie_segment is not set in MPCAM */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t segment_base;
	/* Description - when set segment base is valid, else it is invalid
must be set if seg_cap is set.
reserved when pcie_segment is not set in MPCAM */
	/* 0x4.24 - 0x4.24 */
	/* access: RO */
	u_int8_t seg_valid;
	/* Description - segment number (base) was captured in Flit mode. 
reserved when pcie_segment is not set in MPCAM */
	/* 0x4.25 - 0x4.25 */
	/* access: RO */
	u_int8_t seg_cap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The Socket Direct group index of the matching PF. 
Value 0x0 indicates no grouping */
	/* 0x8.0 - 0x8.2 */
	/* access: RO */
	u_int8_t sd_group;
	/* Description - PCIe device number. */
	/* 0x8.3 - 0x8.7 */
	/* access: RO */
	u_int8_t device;
	/* Description - 2-bit expansion of the local port. Represents the local_port[9:8] bits */
	/* 0x8.12 - 0x8.13 */
	/* access: RO */
	u_int8_t lp_msb;
	/* Description - PCIe bus number. */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t bus;
	/* Description - Local port number */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t local_port;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Slot number */
	/* 0xc.0 - 0xc.12 */
	/* access: RO */
	u_int16_t slot_number;
	/* Description - number of PCIe connected deices / EP on the current port. */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t num_con_devices;
	/* Description - Host index associated with the pcie_inex */
	/* 0xc.24 - 0xc.30 */
	/* access: RO */
	u_int8_t host_index;
	/* Description - If set to '1', slot_number field is supported. */
	/* 0xc.31 - 0xc.31 */
	/* access: RO */
	u_int8_t slot_cap;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mpqd_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Node for the query */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t node;
	/* Description - pcie_index for the query */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t pcie_index;
	/* Description - Depth level for the query */
	/* 0x0.24 - 0x0.29 */
	/* access: INDEX */
	u_int8_t depth;
	/* Description - DPN version
0: multi_topology_unaware_sw
1: multi_topology_aware_sw
For MPQD SW must set the DPNv bit */
	/* 0x0.30 - 0x0.30 */
	/* access: INDEX */
	u_int8_t DPNv;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The pcie_index associated with the querying host */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t requester_pcie_index;
	/* Description - Max available pcie_index */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t max_valid_pcie_index;
	/* Description - Max depth for the querying pcie_index */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t max_exist_depth;
	/* Description - pcie_index is an internal host PCIe tree
0: pcie_index is an external host PCIe tree
1: pcie_index is an internal host PCIe tree */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t is_internal;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of nodes on querying depth - node numbers are 0 to (number_of_nodes - 1)
when 0 - no valid nodes on that querying depth in querying pcie_index */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t number_of_nodes;
	/* Description - Querying node in querying depth and querying pcie_index a physical node
0: the node is a virtual node
1: the node is a physical node */
	/* 0x8.8 - 0x8.8 */
	/* access: RO */
	u_int8_t node_phy;
	/* Description - Querying pcie_index valid
0 : pcie_index is not a valid index
1: pcie_index is a valid index */
	/* 0x8.31 - 0x8.31 */
	/* access: RO */
	u_int8_t valid_index;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Is querying node valid
0: querying node is not a valid node
1: querying node is valid */
	/* 0xc.0 - 0xc.0 */
	/* access: RW */
	u_int8_t valid_node;
	/* Description - Is querying node a downstream port
0: node is upstream port
1: node is downstream port */
	/* 0xc.1 - 0xc.1 */
	/* access: RO */
	u_int8_t DSP_node;
	/* Description - Parent node number for the querying node, depth and pcie_index in the parent depth (depth - 1). 
When querying depth is 0 the parent node is invalid. */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t parent_node_number;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_hca_mqis_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Type of information string to be queried:
0x0: VPD - Read the PCI Vital Product Data capability content.
0x1: MODEL_NAME
0x2: MODEL_DESCRIPTION
0x3: IMAGE_VSD
0x4: DEVICE_VSD
0x5: ROM_INFO
other values are reserved. */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t info_type;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Total size of the information string, according to info_type. Value given in bytes. */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t info_length;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of bytes requested. The device returns the number of bytes actually read. */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t read_length;
	/* Description - Offset in bytes of the first byte requested to read. */
	/* 0x8.16 - 0x8.31 */
	/* access: INDEX */
	u_int16_t read_offset;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Information string accessed, according to info_type. If the information is not available, a NULL string is returned. */
	/* 0x10.24 - 0x18.23 */
	/* access: RO */
	u_int8_t info_string[8];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mroq_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The firmware reset trigger
Bit 0: TRIGGER0 - live patch
Bit 1: Immediate_Action - used for embedded CPU shut down or reset
Bit 3: TRIGGER3 - PCIe link disable or hot reset
Bit 6: TRIGGER6 - PERST
Other bits are reserved */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t reset_trigger;
	/* Description - Query chip reset type
0x0: Full_Chip_Reset
0x1: Keep_Network_Port_Active_During_Reset - phy less reset
0x2: NIC_Only_Rset - for SoC devices. Keep ARM subsystem operational while NIC subsystem (including PCI) is reset.
0x3: ARM_Only_Reset
0x4: ARM_OS_Shutdown
0x5: Network_Reset - Keep PCIe active during reset. Relevant for ConnectX-8 and onward
0xff: InService_SW_Update - Keep network port and PCIe port active and operation during reset. */
	/* 0x0.8 - 0x0.15 */
	/* access: INDEX */
	u_int8_t reset_type;
	/* Description - Selected type is supported. */
	/* 0x0.16 - 0x0.16 */
	/* access: RO */
	u_int8_t query_is_valid;
	/* Description - This filed defines the reset flow. 
Bit 0: Legacy_Flow
Bit 1: Synced_Driver_Flow
Bit 2: Synced_Tool_Flow - should be 0 for internal host
Bit 3: Reserved */
	/* 0x0.17 - 0x0.20 */
	/* access: RO */
	u_int8_t pci_sync_for_fw_update_start;
	/* Description - FW reset Method
Bit 0: Link_Disable 
Bit 1: Hot_Reset - SBR
Other bits are reserved 
Note that this field provides information when reset trigger equals TRIGGER3 (e.g., PCIe link toggle, PCIe hot reset) */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t pci_reset_req_method;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_mrsi_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - [NIC_Only]
0: Main 
1: Embedded CPU 
Reserved when Switches */
	/* 0x0.0 - 0x0.3 */
	/* access: INDEX */
	u_int8_t device;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Reset/shutdown reason
0: cold reset - A reset triggered following application of power to the component. 1: warm reset - A reset triggered without removal and re-application of power to the device */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t reset_reason;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Timestamp (number of clock cycles) since last cold reset */
	/* 0x8.0 - 0xc.31 */
	/* access: RO */
	u_int64_t crts;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - [NIC only]
Embedded CPU OS state
0: Reset/Boot-ROM
1: BL2
2: BL31
3: UEFI
4: OS starting
5: OS is running
6: Low-Power standby
7: Firmware update in progress
8: OS Crash Dump in progress
9: OS Crash Dump is complete
10: FW Fault Crash Dump in progress
11: FW Fault Crash Dump is complete
Other: Reserved

Reserved when MRSI.device != Embedded CPU */
	/* 0x14.0 - 0x14.7 */
	/* access: RO */
	u_int8_t ecos;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mtcap_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of ASIC+platform sensors supported by the device 
This includes the ASIC and the ambient sensors. Module sensors are not included.
This actually is equal to sum of all '1' in sensor_map
Range 1..64

Known sensors:
0: current asic temp, FW exposes current max(all diode temp sensors)
1..63: ambient, supported only for unmanaged switch, defined by ini
64..127: modules (not exposed by this field) */
	/* 0x0.0 - 0x0.6 */
	/* access: RO */
	u_int8_t sensor_count;
	/* Description - Slot index
0: Main board */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of sensors supported by the device that are on the ASIC.
Exposes how many ASIC diodes exist. 
The FW exposes all of them as sensor[0] */
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t internal_sensor_count;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Mapping of system sensors supported by the device. Only ASIC and ambient sensors are supported. Each bit represents a sensor.
Per bit:
0: Not_connected_or_not_supported
1: Supports_temperature_measurements */
	/* 0x8.0 - 0xc.31 */
	/* access: RO */
	u_int64_t sensor_map;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mtdc_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tracer writing to PCI is limited.When this mode is enable, the hw tracer pointer cannot override the software read index pointer.If software will not update the read index pointer, new events will fall and will not be sent.
0: NA - ignored, does not perform any operation 
1: Enable
2: Disable */
	/* 0x0.0 - 0x0.1 */
	/* access: RW */
	u_int8_t tracer_limit_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The lsb of the address for the cyclic buffer in the host memory. */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t tlb_addr_msb;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The lsb of the for the cyclic buffer address in the host memory. */
	/* 0xc.12 - 0xc.31 */
	/* access: RW */
	u_int32_t tlb_addr_lsb;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Pointer of the current hw index the tracer is writing to.
	*/
	/* 0x10.0 - 0x10.31 */
	/* access: RO */
	u_int32_t hw_pointer;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Pointer to the last tracer event index that the software consumed.
	*/
	/* 0x14.0 - 0x14.31 */
	/* access: RW */
	u_int32_t sw_pointer;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_hca_mteim_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of processors per tile ASIC.
	*/
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t cap_core_tile;
	/* Description - Number of processors in the main ASIC. */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t cap_core_main;
	/* Description - Number of processors in the DPA unit. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t cap_core_dpa;
	/* Description - Number of tiles per device. For devices without tiles (only main ASIC), this field should be '0'.
	*/
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t cap_num_of_tile;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Processor type.
0: N/A
1: IRISC
2: RISC5
Else: Reserved */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t type_core_tile;
	/* Description - Processor type.
0: N/A
1: IRISC
2: RISC5
Else: Reserved */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t type_core_main;
	/* Description - Processor type.
0: N/A
1: IRISC
2: RISC5
Else: Reserved */
	/* 0x4.8 - 0x4.11 */
	/* access: RO */
	u_int8_t type_core_dpa;
	/* Description - Indicates wether Phy_UC tracers mapping are supported by the device FW. 
When set, The event_id of the Phy UC of the instance will be calculated by first_tile/main _core _event_id[i] + cap_core_tile/main.
When clear the Phy UC will be ignored.
	*/
	/* 0x4.30 - 0x4.30 */
	/* access: RO */
	u_int8_t is_phy_uc_supported;
	/* Description - When set to '1', the device supports dwsn_msb bit within the FW trace layout. */
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t is_dwsn_msb_supported;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The mapping for the rest of the DPA ASIC processors are sequential and the mapping is defined as:
processor[x]=first_dpacore_event_id+x */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t first_dpa_core_event_id;
	/* Description - The mapping for the rest of the main ASIC processors are sequential and the mapping is defined as:
processor[x]=first_main_core_event_id+x */
	/* 0x8.24 - 0x8.31 */
	/* access: RO */
	u_int8_t first_main_core_event_id;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The mapping for the rest of the tile[y] ASIC processors are sequential and the mapping is defined as:
processor[x]=first_tile_core_event_id[y]+x
	*/
	/* 0xc.24 - 0x14.23 */
	/* access: RO */
	u_int8_t first_tile_core_event_id[8];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_hca_mtie_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Enable/Disable all FW tracer initiator and ignore mask.
Starts from bit 0.
0: Use bit mask
1: Enable all
2: Disable all */
	/* 0x0.0 - 0x0.1 */
	/* access: OP */
	u_int8_t enable_all;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Adding delay to log events in usecs
	*/
	/* 0x4.0 - 0x4.15 */
	/* access: RW */
	u_int16_t log_delay;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Bit mask of all the possible tracer initiators.
Reserved when enable_all != 0.
The mapping of source id to HW unit is unique per device and can be fetched from FW code.
	*/
	/* 0x10.0 - 0x2c.31 */
	/* access: RW */
	u_int32_t source_id_bitmask[8];
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_mtim_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The verbosity of the log. 
0: LOG_DEBUG
1: LOG_INFO
2: LOG_WARNING
3: LOG_ERROR

The lower value reflects higher verbosity than higher value.
e.g: LOG_INFO contains LOG_WARNING and LOG_ERROR */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t log_level;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bit mask of the different FW units that can be activated for the FW log.
The mapping of source id to FW unit is unique per device and can be fetched from FW code.
	*/
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t log_bit_mask;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_hca_mtmp_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sensors index
0: current asic temp, FW exposes current max(all diode temp sensors)
1..62: ambient, supported only for unmanaged switch, defined by ini
64..255: modules 256..288: Gearbox
[Retimer Only][DWIP][Internal]:
289: Retimer Tsense, valid when i = 1
290..297: Retimer BJT 0..7, valid when i = 1
Others up to 704 are reserved */
	/* 0x0.0 - 0x0.11 */
	/* access: INDEX */
	u_int16_t sensor_index;
	/* Description - Slot index
0: Main board */
	/* 0x0.16 - 0x0.19 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - ASIC index. See ig field for more details. */
	/* 0x0.25 - 0x0.28 */
	/* access: INDEX */
	u_int8_t asic_index;
	/* Description - Internal granularity.
Used to query the internal diodes of the switch main ASIC and tiles. 
0: the 'i' field may be used to query the entire ASIC internal diodes. Main + tile.
1: The 'i' field is ignored and only the main ASIC diodes are available to query and sensor_index is the index of the main ASIC diodes. 
2: The 'i' field is ignored and only the tile ASIC diodes are available to query and sensor_index is the index of the tile ASIC diodes. To query a specific tile, asic_index field should be used.
3: Reserved.
Those sensors are not available externally and should only be used for debug. */
	/* 0x0.29 - 0x0.30 */
	/* access: INDEX */
	u_int8_t ig;
	/* Description - Used to query the internal diodes of the switch ASIC; for i=1, sensor_index is the index of the ASIC diode. */
	/* 0x0.31 - 0x0.31 */
	/* access: INDEX */
	u_int8_t i;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Temperature reading from the sensor. 
Units of 0.125 Celsius degrees.
For negative values 2's complement is used (for example: -3.25 Celsius will read as 0xFFE6) */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t temperature;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The highest measured temperature from the sensor.
Reserved when mte = 0
Cleared by mtr = 1
Valid only when i = 0
	*/
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t max_temperature;
	/* Description - Shut Down Events Modify Set Enable:
0: all fields are set
1: only sdee field is set, all other fields reserved */
	/* 0x8.28 - 0x8.28 */
	/* access: OP */
	u_int8_t sdme;
	/* Description - Warning Events Modify Set Enable:
0: all fields are set
1: only tee field is set, all other fields reserved */
	/* 0x8.29 - 0x8.29 */
	/* access: OP */
	u_int8_t weme;
	/* Description - Max Temperature Reset:
0: do not modify the value of the max temperature register
1: clear the value of the max temperature register */
	/* 0x8.30 - 0x8.30 */
	/* access: OP */
	u_int8_t mtr;
	/* Description - Max Temperature Enable:
0: disable measuring the max temperature on a sensor
1: enables measuring the max temperature on a sensor */
	/* 0x8.31 - 0x8.31 */
	/* access: RW */
	u_int8_t mte;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - temperature_threshold_hi refers to the high threshold of Warning Event. Units of 0.125 Celsius degrees.
If the sensor temperature measurement is above the threshold (and events are enabled), an event will be generated.
threshold_hi and threshold_lo implements hysteresis mechanism of the threshold preventing toggling of the indication.
Note that temperature_threshold_hi must be equal or lower than the system requirement.
System requirement for module is the module warning temperature.
System requirement for board/silicon sensors is according to product information parameters
Note that the temperature threshold can be used to generate an event message or an interrupt using GPIO */
	/* 0xc.0 - 0xc.15 */
	/* access: RW */
	u_int16_t temperature_threshold_hi;
	/* Description - Temperature Shut Down Event Enable (MTSDE Register)
0: do_not_generate_event
1: generate_event
2: generate_single_event

Supported in downstream devices (devices on slots). */
	/* 0xc.28 - 0xc.29 */
	/* access: RW */
	u_int8_t sdee;
	/* Description - Temperature Warning Event Enable (MTEWE Register)
0: do_not_generate_event
1: generate_event
2: generate_single_event

	*/
	/* 0xc.30 - 0xc.31 */
	/* access: RW */
	u_int8_t tee;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - temperature_threshold_lo refers to the low threshold of Warning Event.Units of 0.125 Celsius degrees.
The offset threshold_lo implements the lower threshold for the hysteresis mechanism of over temperature alert. Once alert is set, if the temperature goes below this threshold, the alert is cleared.
Note that temperature_threshold_lo must be at least 5 degrees lower than temperature_threshold_hi */
	/* 0x10.0 - 0x10.15 */
	/* access: RW */
	u_int16_t temperature_threshold_lo;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Sensor Name
8 character long sensor name
	*/
	/* 0x18.0 - 0x18.31 */
	/* access: RO */
	u_int32_t sensor_name_hi;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Sensor Name
8 character long sensor name
	*/
	/* 0x1c.0 - 0x1c.31 */
	/* access: RO */
	u_int32_t sensor_name_lo;
};

/* Description -   */
/* Size in bytes - 132 */
struct reg_access_hca_mtrc_cap_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of different string sections building the database */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t num_string_db;
	/* Description - Indicates the version of the tracing mechanism.
See Section 29.3.4.1, "Timestamp Event Traces", on page 1975
0x0: VER_0
0x1: VER_1
Other values are reserved.
Reserved in Switch */
	/* 0x0.24 - 0x0.25 */
	/* access: RO */
	u_int8_t trc_ver;
	/* Description - When set the device supports logging traces to memory
0: FIFO Mode
1: Host Memory Mode */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t trace_to_memory;
	/* Description - Write 0x1 to register for tracer ownership, write 0x0 to de-register.
Read value 0x1 indicates tracer ownership is granted.
	*/
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t trace_owner;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The number of consecutive event_id that should be interpreted as a string trace */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t num_string_trace;
	/* Description - The lowest event_id that should be interpreted as a string trace */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t first_string_trace;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Log 2 of the maximal size of the trace buffer given in units of 4KB */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t log_max_trace_buffer_size;
	/* Description - Tracer suppported capbailities bitmask:
0: FIFO.
1: MEM mode.
else, reserved. */
	/* 0x8.30 - 0x8.31 */
	/* access: RO */
	u_int8_t tracer_capabilities;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - String DB section parameters. */
	/* 0x10.0 - 0x4c.31 */
	/* access: RO */
	struct reg_access_hca_string_db_parameters_ext string_db_param[8];
};

/* Description -   */
/* Size in bytes - 128 */
struct reg_access_hca_mtrc_conf_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Tracing mode
0x0: FIFO
0x1: TRACE_TO_MEMORY
Other values are reserved. */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t trace_mode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Log 2 of the Size of the trace buffer, given in units of 4KB.
Value should not exceed log_max_trace_buffer_size.
Valid only for trace_mode TRACE_TO_MEMORY.
Modifying this parameter after the tracer was active may cause loss of sync regarding the location of the next trace. */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t log_trace_buffer_size;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - MKey registered for the trace buffer access.
Valid only for trace_mode TRACE_TO_MEMORY.
Modifying this parameter after the tracer was active may cause loss of sync regarding the location of the next trace.
Reserved for Switches. */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t trace_mkey;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_mtrc_ctrl_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Field select indicated which writable fields to modify
bit 0: trace_status
Other bits are reserved. */
	/* 0x0.0 - 0x0.15 */
	/* access: WO */
	u_int16_t modify_field_select;
	/* Description - When set, an event will be generated if new Tracer events were logged since last event.
Reserved in Switches. */
	/* 0x0.27 - 0x0.27 */
	/* access: WO */
	u_int8_t arm_event;
	/* Description - Current status of the tracer
0x0: DISABLED - logging traces is stopped
0x1: ACTIVE - logging traces is active */
	/* 0x0.30 - 0x0.31 */
	/* access: RW */
	u_int8_t trace_status;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - MSB of the current timesatmp counter */
	/* 0x8.0 - 0x8.20 */
	/* access: RO */
	u_int32_t current_timestamp_52_32;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - LSB of the current timesatmp counter */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t current_timestamp_31_0;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_hca_mtrc_stdb_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The number of bytes to read from the String DB. The number of bytes must:
Be a multiple of 64B
Not exceed the String DB section (with start_offset)
Not exceed the limitations defined by the medium carrying the Register. */
	/* 0x0.0 - 0x0.23 */
	/* access: INDEX */
	u_int32_t read_size;
	/* Description - The section of the String DB being accessed */
	/* 0x0.28 - 0x0.31 */
	/* access: INDEX */
	u_int8_t string_db_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The offset in the String DB to read from, given in Bytes. The offset must:
Be a multiple of 64B
Not exceed the String DB section (with read_size) */
	/* 0x4.0 - 0x4.31 */
	/* access: INDEX */
	u_int32_t start_offset;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Strings from the database. The size of this field is defined by read_size */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t *string_db_data;
};

/* Description -   */
/* Size in bytes - 128 */
struct reg_access_hca_nic_cap_ext_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicates which capability group is accessed.
0x1: DPA_CAP
other values are reserved */
	/* 0x0.16 - 0x0.31 */
	/* access: INDEX */
	u_int16_t cap_group;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Capability information according to cap_group.
For DPA_CAP See Table  1831, "DPA_CAP Capability Layout," on page  2149 */
	/* 0x10.0 - 0x7c.31 */
	/* access: RO */
	union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext cap_data;
};

/* Description -   */
/* Size in bytes - 768 */
struct reg_access_hca_nic_dpa_eu_partition_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - DPA EU partition id
For WRITE method with operation CREATE this field is RO and provides the newly created EU partition ID.
For other method/operation, this field is an index to a valid EU partition */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t eu_partition_id;
	/* Description - Operation performed for WRITE method:
0x0: CRETAE - create a new partition
0x1: MODIFY - change the parameters of an existing partition, absed on modify_field_select
0x2: DESTROY - destroy an existing partition
other values are reserved. */
	/* 0x0.28 - 0x0.30 */
	/* access: WO */
	u_int8_t operation;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bitmask indicating which parameter is modified by MODIFY operation. Set bit indicates the field should be updated.
bit 0: member_mask
bit 1: max_num_eug
bit 2: num_vhca_id_and_vhca_id
other bits are reserved.
For Query method, set bit indicates the relevant modification is supported */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t modify_field_select;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The maximal number of groups allowed for EUs in the partition */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t max_num_eug;
	/* Description - The number of valid entries in vhca_id array. Value must not exceed DPA_CAP,max_num_partition_vhca_id */
	/* 0x8.16 - 0x8.23 */
	/* access: RW */
	u_int8_t num_vhca_id;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Bitmask indicating which EUs are members of the partition. Set bit indicates the respective EU is a member. EU partitions may not overlap, and EUs beyond DPA_CAP.max_num_dpa_eu are reserved. */
	/* 0x40.0 - 0xbc.31 */
	/* access: RW */
	u_int32_t member_mask[32];
/*---------------- DWORD[48] (Offset 0xc0) ----------------*/
	/* Description - Array of VHCA IDs indicating which functions are allowed to use this partition. Array size is determined by num_vhca_id, entries with index num_vhca_id or higher are reserved. A vHCA may only belong to a single partition at a time. */
	/* 0xc0.16 - 0x2c0.15 */
	/* access: RW */
	u_int16_t vhca_id[256];
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_hca_nic_dpa_eug_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - DPA EUG id
For WRITE method with operation CREATE this field is RO and provides the newly created EUG.
For other method/operation, this field is an index to a valid EUG */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t eug_id;
	/* Description - If set, partition_id defines the Partition to which the members of the EUG belong. Otherwise, the Partition that holds the calling vHCA is assumed.
Valid if NIC_CAP_EXT.dpa_partition_eug is set. */
	/* 0x0.27 - 0x0.27 */
	/* access: INDEX */
	u_int8_t partition_id_valid;
	/* Description - Operation performed for WRITE method:
0x0: CREATE - create a new DPA EUG
0x1: MODIFY - change the members of an existing DPA EUG
0x2: DESTROY - destroy an existing DPA EUG
other values are reserved. */
	/* 0x0.28 - 0x0.30 */
	/* access: WO */
	u_int8_t operation;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Bitmask indicating which parameter is modified by MODIFY operation. Set bit indicates the field should be updated.
bit 0: member_mask
other bits are reserved.
For Query method, set bit indicates the relevant modification is supported */
	/* 0x4.0 - 0x4.31 */
	/* access: RW */
	u_int32_t modify_field_select;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Defines the Partition to which the members of the EUG belong. Valid if partition_id_valid is set. */
	/* 0xc.0 - 0xc.15 */
	/* access: INDEX */
	u_int16_t partition_id;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - EUG name (ASCII string) */
	/* 0x10.0 - 0x1c.31 */
	/* access: RW */
	u_int32_t eug_name[4];
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Bitmask indicating which EUs are members of the group. Set bit indicates the respective EU is a member. EUGs may not overlap, and EUs beyond NIC_CAP_EXT_REG.max_num_dpa_eu are reserved. */
	/* 0x40.0 - 0xbc.31 */
	/* access: RW */
	u_int32_t member_mask[32];
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - dpa_process object id.
0xffffffff: Applies to all processes (all processes are not valid in read) */
	/* 0x0.0 - 0x0.31 */
	/* access: INDEX */
	u_int32_t dpa_process_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - vhca_id where the process is created */
	/* 0x4.0 - 0x4.15 */
	/* access: WO */
	u_int16_t other_vhca_id;
	/* Description - Selects the sampling type. Supported types are indicated by NIC_CAP_EXT.dpa_perf_sample_type
0x0: CUMMULATIVE_EVENT
0x1: EVENT_TRACER
Other values are reserved */
	/* 0x4.24 - 0x4.26 */
	/* access: RW */
	u_int8_t sample_type;
	/* Description - If set, other_vhca_id field is valid. Otherwise, use the process on my vhca_id */
	/* 0x4.27 - 0x4.27 */
	/* access: WO */
	u_int8_t other_vhca_id_valid;
	/* Description - Process performance counting state.
0x0: UNCHANGED
0x1: ACTIVE
0x2: INACTIVE
0x3: RESET_COUNTERS - reset saved counters. After reset, sampler will switch to inactive state.
Other values are reserved */
	/* 0x4.30 - 0x4.31 */
	/* access: RW */
	u_int8_t count_state;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_paos_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Port operational state:
1: up
2: down
4: down_by_port_failure - (transitioned by the hardware)
	
	*/
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t oper_status;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Port administrative state (the desired state of the interface):
1: up
2: down_by_configuration
3: up_once - if the port goes up and then down, the operational status should go to "down by port failure" and can only go back up upon explicit command
4: disabled_by_system - this mode cannot be set by the software, only by the hardware.
6: sleep - can be configured only if sleep_cap is set. Note that a sleep setting will cause the port to transition immediately into sleep state regardless of previous admin_status.
[Internal] - up_once shall not be used for GPU case. In order to define link down state set PLDS register */
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t admin_status;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - For HCA: must always be 0.
Switch partition ID with which to associate the port.
Switch partitions are numbered from 0 to 7 inclusively.
The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query. */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t swid;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Event generation on operational state change (oper_status):
0: Do_not_generate_event
1: Generate_Event 
2: Generate_Single_Event

Not Supported for HCA. */
	/* 0x4.0 - 0x4.1 */
	/* access: RW */
	u_int8_t e;
	/* Description - IB Port Physical operational (actual) link state:
0: N/A
1: Sleep
2: Polling
3: Disabled
4: PortConfigurationTraining
5: LinkUp
6: LinkErrorRecovery
All others reserved
Note that physical state of 1,2,3,4 will all be reflected as oper_status = down.
Ethernet devices that support this field will use only bits 2,3,5. */
	/* 0x4.4 - 0x4.7 */
	/* access: RO */
	u_int8_t physical_state_status;
	/* Description - Force down.
Supported only when indicated in PCAM
Can be set only with admin_status = 2 ('down_by_configuration'), will force link to be down. 
	*/
	/* 0x4.8 - 0x4.8 */
	/* access: RW */
	u_int8_t fd;
	/* Description - Sleep capability:
0: Sleep state is not supported
1: Sleep state supported */
	/* 0x4.9 - 0x4.9 */
	/* access: RO */
	u_int8_t sleep_cap;
	/* Description - Event generation for physical state.
On set operation, will be ignored if ee_ps is not set.
When bit is set, will generate an event for transition into state.
Bit 0: Sleep
Bit 1: LinkUp 
Note - LinkUp for an Ethernet link refers to PhyUp state where local side is ready, but not necessarily that peer side is also ready.
Bit 2: Disabled
Bit 3: PortConfigurationTraining
Not Supported for HCA. */
	/* 0x4.12 - 0x4.15 */
	/* access: RW */
	u_int8_t ps_e;
	/* Description - IB or NVLink Port Logical link state:
0: N/A
1: Down
2: Init
3: Arm
4: Active */
	/* 0x4.16 - 0x4.18 */
	/* access: RO */
	u_int8_t logical_state_status;
	/* Description - event generation mask for logical state.
On set operation, will be ignored when ee_ls is not set.
When bit is set, will generate event for transition into state.
Bit 0: Down
Bit 1: Init
Bit 2: Arm
Bit 3: Active
Not Supported for HCA. */
	/* 0x4.20 - 0x4.23 */
	/* access: RW */
	u_int8_t ls_e;
	/* Description - Event update enable for NMX AdminState. If this bit is set, event generation will be updated based on the nmxas_e field. Only relevant on Set operations.
Not Supported for HCA.
	*/
	/* 0x4.27 - 0x4.27 */
	/* access: WO */
	u_int8_t ee_nmxas;
	/* Description - Event update enable for physical state. If this bit is set, event generation will be updated based on the ps_e field. Only relevant on Set operations.
Not Supported for HCA. */
	/* 0x4.28 - 0x4.28 */
	/* access: WO */
	u_int8_t ee_ps;
	/* Description - Event update enable for logical state. If this bit is set, event generation will be updated based on the ls_e field. Only relevant on Set operations.
Not Supported for HCA. */
	/* 0x4.29 - 0x4.29 */
	/* access: WO */
	u_int8_t ee_ls;
	/* Description - Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.
Not Supported for HCA. */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t ee;
	/* Description - Admin state update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations. */
	/* 0x4.31 - 0x4.31 */
	/* access: WO */
	u_int8_t ase;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - NVLink Port NMX AdminState current state:
0: N/A
1: Up
2: Down
3: Diag
	*/
	/* 0x8.0 - 0x8.2 */
	/* access: RO */
	u_int8_t nmx_adminstate_status;
	/* Description - Event generation mask for NMX AdminState status.
On set operation, will be ignored when ee_nmxas is not set.
When bit is set, will generate event for transition into state.

Bit 0: Up
Bit 1: Down
Bit 2: Diag

	*/
	/* 0x8.4 - 0x8.7 */
	/* access: RW */
	u_int8_t nmxas_e;
	/* Description - Extension of ps_e field. Event generation for physical state.
On set operation, will be ignored if ee_ps is not set.
When bit is set, will generate an event for transition into state.
Bit 0: Polling
Bit 1: Reserved
	*/
	/* 0x8.12 - 0x8.13 */
	/* access: RW */
	u_int8_t ps_e_ext;
	/* Description - Supported if PCAM.feature_cap_mask bit 118 is set
Last reported oper state in PUDE:
0: no_info
1: up
2: down
4: down_by_port_failure - (transitioned by the hardware) */
	/* 0x8.16 - 0x8.18 */
	/* access: RO */
	u_int8_t last_oper_status;
};

/* Description -   */
/* Size in bytes - 12 */
struct reg_access_hca_pcnr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - When set, port will override tuning process upon following link-up command (PAOS.admin_status = UP).
Cleared by FW once PAOS.admin_status = UP command is set.

The tuning_override is recommended to be set when port operational status is UP (PAOS.oper_status=0x1).
If the field is set while operational status is DOWN (PAOS.oper_status=0x2), port will do best effort of fast linkup on the possible parts of the link (that is, known internal links that cannot change). */
	/* 0x0.0 - 0x0.0 */
	/* access: WO */
	u_int8_t tuning_override;
	/* Description - When set, indicates if flua_en, flua_guar_sec, flua_polling_sec, flua_allowed_ber, flu_always_oper is supported and valid. */
	/* 0x0.2 - 0x0.2 */
	/* access: RO */
	u_int8_t flua_cap;
	/* Description - Bitmask for all flua fiels. When bit is set in mask, the relevant field configuration is valid. Otherwise, field ignores the value.
Bit 0: flua_en
bit 1: flua_allowed_ber
Bit 2: flua_polling_sec
Bit 3: flua_guar_sec */
	/* 0x0.3 - 0x0.6 */
	/* access: WO */
	u_int8_t flua_we_mask;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - When Set, The port will keep the same phy setting upon link down event that occurs only upon link down command of peer port. In the event of Down command/cable disconnect, entire link up flow will be initialized.

NOTE: This mode can be configured only when PTYS.an_disable_admin is set (i.e. AN is disabled). 
NOTE: if physical environment was changed (i.e. replacement of module, temp change, etc) there is a possibility that link won't be established or will be established with high BER */
	/* 0x4.0 - 0x4.0 */
	/* access: WO */
	u_int8_t keep_phy_setting;
	/* Description - Get valid only if flua_cap is set.
Set is valid only if flua_cap and flua_we are set.
valid only if flua_cap is set
0: device_default_behavior
1: enable_fast_linkup_always
2: disable_fast_linkup_always

When enabled, fast linkup attempt will always be performed. On fast linkup failure, regular linkup flow will be performed.
flu configuration is ignored when flu_always enabled */
	/* 0x4.4 - 0x4.5 */
	/* access: RW */
	u_int8_t flua_en;
	/* Description - Valid only if flua_cap is set.
Fast link Up always operational satus
0: fast_linkup_always_was_not_performed
1: fast_linkup_always_was_performed */
	/* 0x4.6 - 0x4.7 */
	/* access: RO */
	u_int8_t flua_oper;
	/* Description - BER exponent threshold for allowed ber during the guard period. */
	/* 0x4.8 - 0x4.15 */
	/* access: RW */
	u_int8_t flua_allowed_ber;
	/* Description - Get valid only if flua_cap is set.
Set is valid only if flua_cap and flua_we are set.
Polling allowed time in 2.5 sec granularity.
When fast linkup always is enabled.
Determines the amount of time to try fast-linkup during polling state. when timer expires in polling state, regular linkup will be performed */
	/* 0x4.16 - 0x4.23 */
	/* access: RW */
	u_int8_t flua_polling_sec;
	/* Description - Get valid only if flua_cap is set.
Set is valid only if flua_cap and flua_we are set.
Guard peiod in sec.
When fast linkup always is enabled, determines the amount of time after link is up that if the link drops or BER threshold is met, next linkup will not perform fast-linkup. */
	/* 0x4.24 - 0x4.28 */
	/* access: RW */
	u_int8_t flua_guar_sec;
};

/* Description -   */
/* Size in bytes - 96 */
struct reg_access_hca_pguid_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Port number access type. determines the way local_port is interpreted:
0 - Local port number
1 - IB port number */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - local_port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - System GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x4.0 - 0x10.31 */
	/* access: RO */
	u_int32_t sys_guid[4];
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Node GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x14.0 - 0x20.31 */
	/* access: RO */
	u_int32_t node_guid[4];
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Port GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x24.0 - 0x30.31 */
	/* access: RO */
	u_int32_t port_guid[4];
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Allocated GUID.
Only 64 LSB are used. 64 MSB are reserved. */
	/* 0x34.0 - 0x40.31 */
	/* access: RO */
	u_int32_t allocated_guid[4];
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_hca_pmaos_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Module state (reserved while admin_status is disabled):
0: initializing
1: plugged_enabled
2: unplugged
3: module_plugged_with_error - (details in error_type).
5: unknown */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t oper_status;
	/* Description - Module administrative state (the desired state of the module):
1: enabled
2: disabled_by_configuration
3: enabled_once - if the module is active and then unplugged, or module experienced an error event, the operational status should go to "disabled" and can only be enabled upon explicit enable command.
0xe: disconnect_cable

Note - To disable a module, all ports associated with the port must be disabled first. 
Note 2 - disconnect cable will shut down the optical module in ungraceful manner. 
	*/
	/* 0x0.8 - 0x0.11 */
	/* access: RW */
	u_int8_t admin_status;
	/* Description - Module number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Reserved for HCA
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x0.24 - 0x0.27 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - Module Reset toggle
NOTE: setting reset while module is plugged-in will result in transition of oper_status to initialization. */
	/* 0x0.31 - 0x0.31 */
	/* access: OP */
	u_int8_t rst;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Event Generation on operational state change:
0: Do_not_generate_event
1: Generate_Event
2: Generate_Single_Event
Not supported by secondary ASICs. */
	/* 0x4.0 - 0x4.1 */
	/* access: RW */
	u_int8_t e;
	/* Description - Module error details:
0x0: Power_Budget_Exceeded
0x1: Long_Range_for_non_MLNX_cable_or_module
0x2: Bus_stuck - (I2C Data or clock shorted)
0x3: bad_or_unsupported_EEPROM
0x4: Enforce_part_number_list
0x5: unsupported_cable
0x6: High_Temperature
0x7: bad_cable - (Module/Cable is shorted)
0x8: PMD_type_is_not_enabled - (see PMTPS)
0xc: pcie_system_power_slot_Exceeded

[DWIP] 0xf: Boot_error
[DWIP] 0x10: Recovery_error
[DWIP] 0x11: Submodule_failure

[DWIP] 0x13: els_critical_indication
Valid only when oper_status = 4'b0011 */
	/* 0x4.8 - 0x4.12 */
	/* access: RO */
	u_int8_t error_type;
	/* Description - This notification can occur only if module passed initialization process
0x0: No notifications.
0x1: Speed degradation - the module is not enabled in its full speed due to incompatible transceiver/cable 
Valid only when oper_status = 4'b0001. */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t operational_notification;
	/* Description - When in multi ASIC module sharing systems,
This flag will be asserted in case primary and secondary FW versions are not compatible. */
	/* 0x4.28 - 0x4.28 */
	/* access: RO */
	u_int8_t rev_incompatible;
	/* Description - Indicates whether the ASIC serves as a the modules secondary (=1) or primary (=0) device. */
	/* 0x4.29 - 0x4.29 */
	/* access: RO */
	u_int8_t secondary;
	/* Description - Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.
Not supported by secondary ASICs. */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t ee;
	/* Description - Admin status update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations. */
	/* 0x4.31 - 0x4.31 */
	/* access: WO */
	u_int8_t ase;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_hca_pmlp_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: unmap_local_port
1: x1 - lane 0 is used
2: x2 - lanes 0,1 are used
4: x4 - lanes 0,1,2 and 3 are used
8: x8 - lanes 0-7 are used

Other - reserved */
	/* 0x0.0 - 0x0.7 */
	/* access: RW */
	u_int8_t width;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Module lane mapping: 
0 - Local to Module mapping include module lanes mapping
1 - Local to Module mapping only, without lane mapping

When this operational is set ('1'), the following fields are ignored in SET command and should return the value "0" in GET commands: 
PMLP.rxtx
PMLP.lane<i>_module_mapping.tx_lane
PMLP.lane<i>_module_mapping.rx_lane */
	/* 0x0.28 - 0x0.28 */
	/* access: OP */
	u_int8_t m_lane_m;
	/* Description - Use different configuration for RX and TX.
If this bit is cleared, the TX value is used for both RX and TX. When set, the RX configuration is taken from the separate field. This is to enable backward compatible implementation. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t rxtx;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Module SerDes for lane <i>
Up to 8 SerDes in a module can be mapped to a local port. */
	/* 0x4.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_hca_lane_2_module_mapping_ext lane_module_mapping[8];
};

/* Description -   */
/* Size in bytes - 68 */
struct reg_access_hca_ptys_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Protocol Mask. Indicates which of the protocol data is valid
Bit 0: InfiniBand
Bit 1: NVLink
Bit 2: Ethernet

	*/
	/* 0x0.0 - 0x0.2 */
	/* access: INDEX */
	u_int8_t proto_mask;
	/* Description - Valid only when port is mapped to SW controlled module, otherwise ignored. module control can be queried via MMCR register.

0: transmit_not_allowed - Transmitter is not allowed to transmit signal on output
1: transmit_allowed - Transmitter is allowed to transmit signal on output. for enabling transmitter, PAOS.admin_status must be up as well. */
	/* 0x0.3 - 0x0.3 */
	/* access: RW */
	u_int8_t transmit_allowed;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - Supported only when indicated by PCAM 
0: Network_Port
1: Near-End_Port - (For Gearbox - Host side)
2: Internal_IC_Port 
3: Far-End_Port - (For Gearbox - Line side)

Other values are reserved. */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t port_type;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - Valid only when ee_tx_ready is set, otherwise field is ignored.
0: do_not_generate_event
Bit 0: generate_tx_ready_event - When set, PTSE register will generate event when Transmitter is generating valid signal on the line
Bit 1: generate_tx_not_ready_event - when set, PTSE will generate event when the transmitter stopped transmitting after Tx_ready was set.
Note: if both tx_not_ready and tx_ready are set, one toggle event may be received instead of 2 consecutive events of not ready --> ready. */
	/* 0x0.26 - 0x0.27 */
	/* access: RW */
	u_int8_t tx_ready_e;
	/* Description - Event Enable for tx_ready_e.
when bit is not set, tx_teady_e write value will be ignored */
	/* 0x0.28 - 0x0.28 */
	/* access: WO */
	u_int8_t ee_tx_ready;
	/* Description - Auto Negotiation disable capability:
0 - Device does not support AN disable
1 - Device Supports  AN disable */
	/* 0x0.29 - 0x0.29 */
	/* access: RO */
	u_int8_t an_disable_cap;
	/* Description - Auto Negotiation disable:
0 - Normal operation 
1 - Disable AN.
Note: In Ethernet port, when Disabling AN, the "eth_proto_admin" bit mask must comply to single speed rate set.
In IB port, when Disabling AN, the "ib_proto_admin" bit mask must comply to single speed rate set.
It's recommended to validate the FEC override bits in PPLM when operating with AN. 

	*/
	/* 0x0.30 - 0x0.30 */
	/* access: RW */
	u_int8_t an_disable_admin;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Port data rate in resolution of 100 Mb/s (data_rate_oper * 100 Mb/s)
Value 0x0 indicates this field is not supported.
	*/
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t data_rate_oper;
	/* Description - Port maxium data rate in resolution of 1 Gb/s (data_rate_oper * 1 Gb/s)
Value 0x0 indicates this field is not supported.

	*/
	/* 0x4.16 - 0x4.27 */
	/* access: RO */
	u_int16_t max_port_rate;
	/* Description - Auto Negotiation status: 
0: Status_is_unavailable
1: AN_completed_successfully 
2: AN_performed_but_failed
3: AN_was_not_performed_link_is_up 
4: AN_was_not_performed_link_is_down */
	/* 0x4.28 - 0x4.31 */
	/* access: RO */
	u_int8_t an_status;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - For HCA: See also PCAM.feature_cap_mask bit 13 for Extended Ethernet protocol support.
Extended Ethernet port speed/protocols supported (bitmask):
Bit 0: SGMII_100M
Bit 1: 1000BASE-X / SGMII
Bit 3: 5GBASE-R
Bit 4: XFI / XAUI-1 // 10G
Bit 5: XLAUI-4/XLPPI-4 // 40G 
Bit 6: 25GAUI-1/ 25GBASE-CR / KR 
Bit 7: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 
Bit 8: 50GAUI-1 /50GBASE-CR / KR
Bit 9: CAUI-4 / 100GBASE-CR4 / KR4
Bit 10: 100GAUI-2 / 100GBASE-CR2 / KR2 
Bit 11: 100GAUI-1 / 100GBASE-CR / KR
Bit 12: 200GAUI-4 / 200GBASE-CR4/KR4
Bit 13: 200GAUI-2 / 200GBASE-CR2/KR2
Bit 14: 200GAUI-1 / 200GBASE-CR1/KR1
Bit 15: 400GAUI-8/ 400GBASE-CR8
Bit 16: 400GAUI-4/ 400GBASE-CR4
Bit 17: 400GAUI-2 / 400GBASE-CR2/KR2
Bit 18: Reserved [internal] Placeholder for 400GAUI-1
Bit 19: 800GAUI-8 / 800GBASE-CR8 / KR8
Bit 20: 800GAUI-4 / 800GBASE-CR4/KR4
Bit 23: 1.6TAUI-8 /1.6TBASE-CR8/KR8
Bit 31: SGMII_10M
Other - Reserved */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t ext_eth_proto_capability;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Ethernet port speed/protocols supported (bitmask)
Bit 31 - 50GBase-KR2
Bit 30 - 50GBase-CR2
Bit 29 - 25GBase-SR
Bit 28 - 25GBase-KR
Bit 27 - 25GBase-CR
Bit 26 - 10GBase-T 
Bit 25 - 1000Base-T
Bit 24 - 100Base-TX
Bit 23 - 100GBase LR4/ER4
Bit 22 - 100GBase KR4
Bit 21 - 100GBase SR4
Bit 20 - 100GBase CR4
Bit 18 - 50GBase-SR2
Bit 16 - 40GBase LR4/ER4
Bit 15 - 40GBase SR4
Bit 14 - 10GBase ER/LR
Bit 13 - 10GBase SR
Bit 12 - 10GBase CR
Bit 10 - 10Base-T
Bit 9 - SGMII_100Base
Bit 7 - 40GBase KR4
Bit 6 - 40GBase CR4
Bit 4 - 10GBase KR
Bit 3 - 10GBase KX4
Bit 2 - 10GBase-CX4
Bit 1 - 1000Base KX
Bit 0 - SGMII */
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t eth_proto_capability;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - InfiniBand port speed supported (bitmask)
Bit 0: SDR
Bit 1: DDR
Bit 2: QDR
Bit 3: FDR10
Bit 4: FDR
Bit 5: EDR
Bit 6: HDR
Bit 7: NDR
Bit 8: XDR */
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t ib_proto_capability;
	/* Description - ib_link_width <= ib_proto_capability
Bit 0 - 1x
Bit 1 - 2x
Bit 2 - 4x
	*/
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t ib_link_width_capability;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Ethernet port extended speed/protocols bitmask
NOTE: This field and "eth_proto_admin" are mutual exclusive, meaning that only one of the field can be set on write command. */
	/* 0x14.0 - 0x14.31 */
	/* access: RW */
	u_int32_t ext_eth_proto_admin;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Ethernet port speed/protocols bitmask */
	/* 0x18.0 - 0x18.31 */
	/* access: RW */
	u_int32_t eth_proto_admin;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - InfiniBand port speed bitmask
	*/
	/* 0x1c.0 - 0x1c.15 */
	/* access: RW */
	u_int16_t ib_proto_admin;
	/* Description - InfiniBand port link width bitmask
	*/
	/* 0x1c.16 - 0x1c.31 */
	/* access: RW */
	u_int16_t ib_link_width_admin;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Ethernet port extended speed/protocols bitmask */
	/* 0x20.0 - 0x20.31 */
	/* access: RO */
	u_int32_t ext_eth_proto_oper;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - Ethernet port speed/protocols bitmask */
	/* 0x24.0 - 0x24.31 */
	/* access: RO */
	u_int32_t eth_proto_oper;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - InfiniBand port speed bitmask */
	/* 0x28.0 - 0x28.15 */
	/* access: RO */
	u_int16_t ib_proto_oper;
	/* Description - InfiniBand port link width bitmask
	*/
	/* 0x28.16 - 0x28.31 */
	/* access: RO */
	u_int16_t ib_link_width_oper;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Connector type indication
0: No_connector_or_unknown 
1: PORT_NONE - None
2: PORT_TP - Twisted Pair
3: PORT_AUI - AUI
4: PORT_BNC - BNC
5: PORT_MII - MII
6: PORT_FIBRE - FIBRE
7: PORT_DA - Direct Attach Copper
8: PORT_OTHER - Other */
	/* 0x2c.0 - 0x2c.3 */
	/* access: RO */
	u_int8_t connector_type;
	/* Description - For active link, Indicates the lane data rate passed per physical lane including the overhead due to FEC.
resolution of 10 Mb/s (lane_rate_oper * 10Mb/s). */
	/* 0x2c.4 - 0x2c.23 */
	/* access: RO */
	u_int32_t lane_rate_oper;
	/* Description - When set and link active, indicates link speed is xdr_2x slow. */
	/* 0x2c.24 - 0x2c.24 */
	/* access: RO */
	u_int8_t xdr_2x_slow_active;
	/* Description - When set, along with ib protocol xdr_2x, XDR_2x slow will be allowed instead of xdr_2x.
Note: in GB100, set by default only with ini and cannot be changed. */
	/* 0x2c.25 - 0x2c.25 */
	/* access: RW */
	u_int8_t xdr_2x_slow_admin;
	/* Description - Ethernet Force mode options when AN disable is set.
0 - auto, keep normal operation
1 - Do Force LT (KR Startup) flow
2 - Do not do LT (KR Startup) flow

Note: Ignored when an_disable_admin is not set
In Ethernet port, when setting force LT flow, the "eth_proto_ext_admin" bit mask must comply to single speed rate set. */
	/* 0x2c.28 - 0x2c.29 */
	/* access: RW */
	u_int8_t force_lt_frames_admin;
	/* Description - 0 - device does not support Force LT (KR Startup) flow
1 - device supports Force LT (KR Startup) flow

Note: Ignored when an_disable_admin is not set */
	/* 0x2c.30 - 0x2c.30 */
	/* access: RO */
	u_int8_t force_lt_frames_cap;
	/* Description - capability for XDR_2x slow is support (200G) */
	/* 0x2c.31 - 0x2c.31 */
	/* access: RO */
	u_int8_t xdr_2x_slow_cap;
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - IB/NVlink port supported protocols and widths bit-mask.
Valid if PCAM.feature_cap_mask bit 90 is set OR mask <>0.

For IB: Table  1864, "PTYS - Extended Protocol IB - cap/oper Layout," on page  2187
For NVLink: Table  1868, "PTYS - Extended Protocol NVLink - cap/oper Layout," on page  2188 */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext ext_ib_proto_cap;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - IB/NVLink port protocols admin values.

For IB: Table  1866, "PTYS - Extended Protocol IB - admin Layout," on page  2187
For NVLink: Table  1870, "PTYS - Extended Protocol NVLink - admin Layout," on page  2189

NOTE: This field and "ib_proto_admin", "ib_link_width_admin" are mutual exclusive, meaning that only one of the field can be set on write command. */
	/* 0x3c.0 - 0x3c.31 */
	/* access: RW */
	union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext ext_ib_proto_admin;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - IB/NVLink port operational protocol.
For IB: Table  1864, "PTYS - Extended Protocol IB - cap/oper Layout," on page  2187
For NVLink: Table  1868, "PTYS - Extended Protocol NVLink - cap/oper Layout," on page  2188 */
	/* 0x40.0 - 0x40.31 */
	/* access: RO */
	union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext ext_ib_proto_oper;
};

/* Description -   */
/* Size in bytes - 256 */
struct reg_access_hca_resource_dump_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - See Section  29.11, "Resource Dump," on page  2020. */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t segment_type;
	/* Description - Sequence number. 0 on first call of dump and incremented on each more dump. */
	/* 0x0.16 - 0x0.19 */
	/* access: RW */
	u_int8_t seq_num;
	/* Description - If set, then vhca_id field is valid. Otherwise dump resources on my vhca_id. */
	/* 0x0.29 - 0x0.29 */
	/* access: WO */
	u_int8_t vhca_id_valid;
	/* Description - If set, data is dumped in the register in inline_data field. otherwise dump to mkey. */
	/* 0x0.30 - 0x0.30 */
	/* access: WO */
	u_int8_t inline_dump;
	/* Description - If set, the device has additional information that has not been dumped yet. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t more_dump;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - vhca_id where the resource is allocated. */
	/* 0x4.0 - 0x4.15 */
	/* access: WO */
	u_int16_t vhca_id;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - First object index to be dumped when supported by the object.
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. */
	/* 0x8.0 - 0x8.31 */
	/* access: RW */
	u_int32_t index1;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Second object index to be dumped when supported by the object.
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. */
	/* 0xc.0 - 0xc.31 */
	/* access: RW */
	u_int32_t index2;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The amount of objects to dump starting for index 2.
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. 
Range is 0..0xfff0. When the segment's num_of_obj2_supports_all is set, the special value of 0xffff represents "all". When the segment's num_of_objx_supports_active is set, the special value of 0xfffe represents "active". The  value of 0x0 and 0x1 are allowed even if the supported_num_of_obj2 is "0". */
	/* 0x10.0 - 0x10.15 */
	/* access: RW */
	u_int16_t num_of_obj2;
	/* Description - The amount of objects to dump starting for index 1
SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. 
Range is 0..0xfff0. When the segment's num_of_obj1_supports_all is set, the special value of 0xffff represents "all". When the segment's num_of_objx_supports_active is set, the special value of 0xfffe represents "active". The  value of 0x0 and 0x1 are allowed even if the supported_num_of_obj1 is "0". */
	/* 0x10.16 - 0x10.31 */
	/* access: RW */
	u_int16_t num_of_obj1;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - An opaque provided by the device. SW shall read the device_opaque upon command done and shall provide it on the next call in case dump_more==1. On first call, device_opaque shall be 0. */
	/* 0x18.0 - 0x1c.31 */
	/* access: RW */
	u_int64_t device_opaque;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - Memory key to dump to. 
Valid when inline_dump==0. */
	/* 0x20.0 - 0x20.31 */
	/* access: WO */
	u_int32_t mkey;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - In write, the size of maximum allocated buffer that the device can use.
In read, the actual written size.
In granularity of Bytes. */
	/* 0x24.0 - 0x24.31 */
	/* access: RW */
	u_int32_t size;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - VA address (absolute address) of memory where to start dumping. 
Valid when inline_dump==0. */
	/* 0x28.0 - 0x2c.31 */
	/* access: WO */
	u_int64_t address;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Data that is dumped in case of inline mode.
Valid when inline_dump==1. */
	/* 0x30.0 - 0xfc.31 */
	/* access: RW */
	u_int32_t inline_data[52];
};

/* Description -   */
/* Size in bytes - 768 */
union reg_access_hca_reg_access_hca_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_hca_mteim_reg_ext mteim_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_hca_mtrc_stdb_reg_ext mtrc_stdb_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	/* access: RW */
	struct reg_access_hca_debug_cap debug_cap;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_cap_ext mcqi_cap_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_pmaos_reg_ext pmaos_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_hca_dtor_reg_ext dtor_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x11c.31 */
	/* access: RW */
	struct reg_access_hca_misoc_reg_ext misoc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_hca_mtrc_ctrl_reg_ext mtrc_ctrl_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_hca_mqis_reg_ext mqis_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_hca_mcc_reg_ext mcc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_hca_mfsv_reg_ext mfsv_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_hca_mfpa_reg_ext mfpa_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_activation_method_ext mcqi_activation_method_ext;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_hca_mcam_reg_ext mcam_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_version_ext mcqi_version_ext;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_hca_pguid_reg_ext pguid_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_mtim_ext mtim_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_hca_mrsi_ext mrsi_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_mnvgc_reg_ext mnvgc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x90.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_reg_ext mcqi_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x9c.31 */
	/* access: RW */
	struct reg_access_hca_mpcir_ext mpcir_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_hca_mnvqc_reg_ext mnvqc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	/* access: RW */
	struct reg_access_hca_nic_dpa_eug_reg_ext nic_dpa_eug_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_hca_mtdc_ext mtdc_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext nic_dpa_perf_ctrl_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_hca_nic_cap_ext_reg_ext nic_cap_ext_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x9c.31 */
	/* access: RW */
	struct reg_access_hca_mgir_ext mgir_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_hca_mmdio_ext mmdio_ext;
	/* Description -  */
	/* 0x0.0 - 0x90.31 */
	/* access: RW */
	struct reg_access_hca_mcia_ext mcia_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_hca_mtie_ext mtie_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_paos_reg_ext paos_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2fc.31 */
	/* access: RW */
	struct reg_access_hca_nic_dpa_eu_partition_reg_ext nic_dpa_eu_partition_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_hca_pcnr_reg_ext pcnr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x28.31 */
	/* access: RW */
	struct reg_access_hca_mpegc_reg_ext mpegc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x108.31 */
	/* access: RW */
	struct reg_access_hca_mfba_reg_ext mfba_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x40.31 */
	/* access: RW */
	struct reg_access_hca_ptys_reg_ext ptys_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_hca_mfrl_reg_ext mfrl_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_hca_MRSV_ext MRSV_ext;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_hca_mmhi_reg_ext mmhi_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_hca_mroq_ext mroq_ext;
	/* Description -  */
	/* 0x0.0 - 0x8c.31 */
	/* access: RW */
	struct reg_access_hca_mcda_reg_ext mcda_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_hca_mtrc_conf_reg_ext mtrc_conf_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_mpqd_reg_ext mpqd_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_hca_mnvdi_reg_ext mnvdi_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_hca_mnvia_reg_ext mnvia_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_hca_mpein_reg_ext mpein_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_hca_pmlp_reg_ext pmlp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_mcqs_reg_ext mcqs_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x80.31 */
	/* access: RW */
	struct reg_access_hca_mtrc_cap_reg_ext mtrc_cap_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xfc.31 */
	/* access: RW */
	struct reg_access_hca_resource_dump_ext resource_dump_ext;
	/* Description -  */
	/* 0x0.0 - 0x78.31 */
	/* access: RW */
	struct reg_access_hca_mcqi_linkx_properties_ext mcqi_linkx_properties_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_mpir_ext mpir_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_hca_mtcap_ext mtcap_ext;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	/* access: RW */
	struct reg_access_hca_mfbe_reg_ext mfbe_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_hca_mtmp_ext mtmp_ext;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* configuration_item_type_class_file_ext */
void reg_access_hca_configuration_item_type_class_file_ext_pack(const struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_file_ext_unpack(struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_file_ext_print(const struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_file_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_FILE_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_file_ext_dump(const struct reg_access_hca_configuration_item_type_class_file_ext *ptr_struct, FILE *fd);
/* configuration_item_type_class_global_ext */
void reg_access_hca_configuration_item_type_class_global_ext_pack(const struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_global_ext_unpack(struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_global_ext_print(const struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_global_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_GLOBAL_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_global_ext_dump(const struct reg_access_hca_configuration_item_type_class_global_ext *ptr_struct, FILE *fd);
/* configuration_item_type_class_host_ext */
void reg_access_hca_configuration_item_type_class_host_ext_pack(const struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_host_ext_unpack(struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_host_ext_print(const struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_host_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_HOST_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_host_ext_dump(const struct reg_access_hca_configuration_item_type_class_host_ext *ptr_struct, FILE *fd);
/* configuration_item_type_class_log_ext */
void reg_access_hca_configuration_item_type_class_log_ext_pack(const struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_log_ext_unpack(struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_log_ext_print(const struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_log_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_LOG_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_log_ext_dump(const struct reg_access_hca_configuration_item_type_class_log_ext *ptr_struct, FILE *fd);
/* configuration_item_type_class_module_ext */
void reg_access_hca_configuration_item_type_class_module_ext_pack(const struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_module_ext_unpack(struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_module_ext_print(const struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_module_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_MODULE_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_module_ext_dump(const struct reg_access_hca_configuration_item_type_class_module_ext *ptr_struct, FILE *fd);
/* configuration_item_type_class_multi_instance_ext */
void reg_access_hca_configuration_item_type_class_multi_instance_ext_pack(const struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_multi_instance_ext_unpack(struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_multi_instance_ext_print(const struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_multi_instance_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_MULTI_INSTANCE_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_multi_instance_ext_dump(const struct reg_access_hca_configuration_item_type_class_multi_instance_ext *ptr_struct, FILE *fd);
/* configuration_item_type_class_per_host_pf_ext */
void reg_access_hca_configuration_item_type_class_per_host_pf_ext_pack(const struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_per_host_pf_ext_unpack(struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_per_host_pf_ext_print(const struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_per_host_pf_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_PER_HOST_PF_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_per_host_pf_ext_dump(const struct reg_access_hca_configuration_item_type_class_per_host_pf_ext *ptr_struct, FILE *fd);
/* configuration_item_type_class_physical_port_ext */
void reg_access_hca_configuration_item_type_class_physical_port_ext_pack(const struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_physical_port_ext_unpack(struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_configuration_item_type_class_physical_port_ext_print(const struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_configuration_item_type_class_physical_port_ext_size(void);
#define REG_ACCESS_HCA_CONFIGURATION_ITEM_TYPE_CLASS_PHYSICAL_PORT_EXT_SIZE    (0x4)
void reg_access_hca_configuration_item_type_class_physical_port_ext_dump(const struct reg_access_hca_configuration_item_type_class_physical_port_ext *ptr_struct, FILE *fd);
/* date_time_layout_ext */
void reg_access_hca_date_time_layout_ext_pack(const struct reg_access_hca_date_time_layout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_date_time_layout_ext_unpack(struct reg_access_hca_date_time_layout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_date_time_layout_ext_print(const struct reg_access_hca_date_time_layout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_date_time_layout_ext_size(void);
#define REG_ACCESS_HCA_DATE_TIME_LAYOUT_EXT_SIZE    (0x8)
void reg_access_hca_date_time_layout_ext_dump(const struct reg_access_hca_date_time_layout_ext *ptr_struct, FILE *fd);
/* mcqi_dpa_metadata_ext */
void reg_access_hca_mcqi_dpa_metadata_ext_pack(const struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_dpa_metadata_ext_unpack(struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_dpa_metadata_ext_print(const struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_dpa_metadata_ext_size(void);
#define REG_ACCESS_HCA_MCQI_DPA_METADATA_EXT_SIZE    (0x68)
void reg_access_hca_mcqi_dpa_metadata_ext_dump(const struct reg_access_hca_mcqi_dpa_metadata_ext *ptr_struct, FILE *fd);
/* MRSV_CX_7_Value_ext */
void reg_access_hca_MRSV_CX_7_Value_ext_pack(const struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_MRSV_CX_7_Value_ext_unpack(struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_MRSV_CX_7_Value_ext_print(const struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_MRSV_CX_7_Value_ext_size(void);
#define REG_ACCESS_HCA_MRSV_CX_7_VALUE_EXT_SIZE    (0x20)
void reg_access_hca_MRSV_CX_7_Value_ext_dump(const struct reg_access_hca_MRSV_CX_7_Value_ext *ptr_struct, FILE *fd);
/* config_item_type_auto_ext */
void reg_access_hca_config_item_type_auto_ext_pack(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_config_item_type_auto_ext_unpack(union reg_access_hca_config_item_type_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_config_item_type_auto_ext_print(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_config_item_type_auto_ext_size(void);
#define REG_ACCESS_HCA_CONFIG_ITEM_TYPE_AUTO_EXT_SIZE    (0x4)
void reg_access_hca_config_item_type_auto_ext_dump(const union reg_access_hca_config_item_type_auto_ext *ptr_struct, FILE *fd);
/* mcqi_activation_method_ext */
void reg_access_hca_mcqi_activation_method_ext_pack(const struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_activation_method_ext_unpack(struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_activation_method_ext_print(const struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_activation_method_ext_size(void);
#define REG_ACCESS_HCA_MCQI_ACTIVATION_METHOD_EXT_SIZE    (0x7c)
void reg_access_hca_mcqi_activation_method_ext_dump(const struct reg_access_hca_mcqi_activation_method_ext *ptr_struct, FILE *fd);
/* mcqi_cap_ext */
void reg_access_hca_mcqi_cap_ext_pack(const struct reg_access_hca_mcqi_cap_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_cap_ext_unpack(struct reg_access_hca_mcqi_cap_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_cap_ext_print(const struct reg_access_hca_mcqi_cap_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_cap_ext_size(void);
#define REG_ACCESS_HCA_MCQI_CAP_EXT_SIZE    (0x7c)
void reg_access_hca_mcqi_cap_ext_dump(const struct reg_access_hca_mcqi_cap_ext *ptr_struct, FILE *fd);
/* mcqi_clock_source_properties_ext */
void reg_access_hca_mcqi_clock_source_properties_ext_pack(const struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_clock_source_properties_ext_unpack(struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_clock_source_properties_ext_print(const struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_clock_source_properties_ext_size(void);
#define REG_ACCESS_HCA_MCQI_CLOCK_SOURCE_PROPERTIES_EXT_SIZE    (0x4)
void reg_access_hca_mcqi_clock_source_properties_ext_dump(const struct reg_access_hca_mcqi_clock_source_properties_ext *ptr_struct, FILE *fd);
/* mcqi_dpa_apps_info_ext */
void reg_access_hca_mcqi_dpa_apps_info_ext_pack(const struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_dpa_apps_info_ext_unpack(struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_dpa_apps_info_ext_print(const struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_dpa_apps_info_ext_size(void);
#define REG_ACCESS_HCA_MCQI_DPA_APPS_INFO_EXT_SIZE    (0x70)
void reg_access_hca_mcqi_dpa_apps_info_ext_dump(const struct reg_access_hca_mcqi_dpa_apps_info_ext *ptr_struct, FILE *fd);
/* mcqi_linkx_properties_ext */
void reg_access_hca_mcqi_linkx_properties_ext_pack(const struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_linkx_properties_ext_unpack(struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_linkx_properties_ext_print(const struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_linkx_properties_ext_size(void);
#define REG_ACCESS_HCA_MCQI_LINKX_PROPERTIES_EXT_SIZE    (0x7c)
void reg_access_hca_mcqi_linkx_properties_ext_dump(const struct reg_access_hca_mcqi_linkx_properties_ext *ptr_struct, FILE *fd);
/* mcqi_version_ext */
void reg_access_hca_mcqi_version_ext_pack(const struct reg_access_hca_mcqi_version_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_version_ext_unpack(struct reg_access_hca_mcqi_version_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_version_ext_print(const struct reg_access_hca_mcqi_version_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_version_ext_size(void);
#define REG_ACCESS_HCA_MCQI_VERSION_EXT_SIZE    (0x7c)
void reg_access_hca_mcqi_version_ext_dump(const struct reg_access_hca_mcqi_version_ext *ptr_struct, FILE *fd);
/* nic_cap_ext_dpa_cap_ext */
void reg_access_hca_nic_cap_ext_dpa_cap_ext_pack(const struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_nic_cap_ext_dpa_cap_ext_unpack(struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_nic_cap_ext_dpa_cap_ext_print(const struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_nic_cap_ext_dpa_cap_ext_size(void);
#define REG_ACCESS_HCA_NIC_CAP_EXT_DPA_CAP_EXT_SIZE    (0x70)
void reg_access_hca_nic_cap_ext_dpa_cap_ext_dump(const struct reg_access_hca_nic_cap_ext_dpa_cap_ext *ptr_struct, FILE *fd);
/* ptys_ext_proto_ib_admin_ext */
void reg_access_hca_ptys_ext_proto_ib_admin_ext_pack(const struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_ib_admin_ext_unpack(struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_ib_admin_ext_print(const struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_ext_proto_ib_admin_ext_size(void);
#define REG_ACCESS_HCA_PTYS_EXT_PROTO_IB_ADMIN_EXT_SIZE    (0x4)
void reg_access_hca_ptys_ext_proto_ib_admin_ext_dump(const struct reg_access_hca_ptys_ext_proto_ib_admin_ext *ptr_struct, FILE *fd);
/* ptys_ext_proto_ib_cap_oper_ext */
void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_pack(const struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_unpack(struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_print(const struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_size(void);
#define REG_ACCESS_HCA_PTYS_EXT_PROTO_IB_CAP_OPER_EXT_SIZE    (0x4)
void reg_access_hca_ptys_ext_proto_ib_cap_oper_ext_dump(const struct reg_access_hca_ptys_ext_proto_ib_cap_oper_ext *ptr_struct, FILE *fd);
/* ptys_ext_proto_nvlink_admin_ext */
void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_pack(const struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_unpack(struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_print(const struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_ext_proto_nvlink_admin_ext_size(void);
#define REG_ACCESS_HCA_PTYS_EXT_PROTO_NVLINK_ADMIN_EXT_SIZE    (0x4)
void reg_access_hca_ptys_ext_proto_nvlink_admin_ext_dump(const struct reg_access_hca_ptys_ext_proto_nvlink_admin_ext *ptr_struct, FILE *fd);
/* ptys_ext_proto_nvlink_cap_oper_ext */
void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_pack(const struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_unpack(struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_print(const struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_size(void);
#define REG_ACCESS_HCA_PTYS_EXT_PROTO_NVLINK_CAP_OPER_EXT_SIZE    (0x4)
void reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext_dump(const struct reg_access_hca_ptys_ext_proto_nvlink_cap_oper_ext *ptr_struct, FILE *fd);
/* rom_version_ext */
void reg_access_hca_rom_version_ext_pack(const struct reg_access_hca_rom_version_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_rom_version_ext_unpack(struct reg_access_hca_rom_version_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_rom_version_ext_print(const struct reg_access_hca_rom_version_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_rom_version_ext_size(void);
#define REG_ACCESS_HCA_ROM_VERSION_EXT_SIZE    (0x4)
void reg_access_hca_rom_version_ext_dump(const struct reg_access_hca_rom_version_ext *ptr_struct, FILE *fd);
/* MRSV_data_auto_ext */
void reg_access_hca_MRSV_data_auto_ext_pack(const union reg_access_hca_MRSV_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_MRSV_data_auto_ext_unpack(union reg_access_hca_MRSV_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_MRSV_data_auto_ext_print(const union reg_access_hca_MRSV_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_MRSV_data_auto_ext_size(void);
#define REG_ACCESS_HCA_MRSV_DATA_AUTO_EXT_SIZE    (0x20)
void reg_access_hca_MRSV_data_auto_ext_dump(const union reg_access_hca_MRSV_data_auto_ext *ptr_struct, FILE *fd);
/* config_item_ext */
void reg_access_hca_config_item_ext_pack(const struct reg_access_hca_config_item_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_config_item_ext_unpack(struct reg_access_hca_config_item_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_config_item_ext_print(const struct reg_access_hca_config_item_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_config_item_ext_size(void);
#define REG_ACCESS_HCA_CONFIG_ITEM_EXT_SIZE    (0xc)
void reg_access_hca_config_item_ext_dump(const struct reg_access_hca_config_item_ext *ptr_struct, FILE *fd);
/* default_timeout_ext */
void reg_access_hca_default_timeout_ext_pack(const struct reg_access_hca_default_timeout_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_default_timeout_ext_unpack(struct reg_access_hca_default_timeout_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_default_timeout_ext_print(const struct reg_access_hca_default_timeout_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_default_timeout_ext_size(void);
#define REG_ACCESS_HCA_DEFAULT_TIMEOUT_EXT_SIZE    (0x4)
void reg_access_hca_default_timeout_ext_dump(const struct reg_access_hca_default_timeout_ext *ptr_struct, FILE *fd);
/* diagnostic_cntr_layout */
void reg_access_hca_diagnostic_cntr_layout_pack(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_diagnostic_cntr_layout_unpack(struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_diagnostic_cntr_layout_print(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_diagnostic_cntr_layout_size(void);
#define REG_ACCESS_HCA_DIAGNOSTIC_CNTR_LAYOUT_SIZE    (0x4)
void reg_access_hca_diagnostic_cntr_layout_dump(const struct reg_access_hca_diagnostic_cntr_layout *ptr_struct, FILE *fd);
/* lane_2_module_mapping_ext */
void reg_access_hca_lane_2_module_mapping_ext_pack(const struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_lane_2_module_mapping_ext_unpack(struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_lane_2_module_mapping_ext_print(const struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_lane_2_module_mapping_ext_size(void);
#define REG_ACCESS_HCA_LANE_2_MODULE_MAPPING_EXT_SIZE    (0x4)
void reg_access_hca_lane_2_module_mapping_ext_dump(const struct reg_access_hca_lane_2_module_mapping_ext *ptr_struct, FILE *fd);
/* mcqi_reg_data_auto_ext */
void reg_access_hca_mcqi_reg_data_auto_ext_pack(const union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_data_auto_ext_unpack(union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_data_auto_ext_print(const union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_reg_data_auto_ext_size(void);
#define REG_ACCESS_HCA_MCQI_REG_DATA_AUTO_EXT_SIZE    (0x7c)
void reg_access_hca_mcqi_reg_data_auto_ext_dump(const union reg_access_hca_mcqi_reg_data_auto_ext *ptr_struct, FILE *fd);
/* mgir_dev_info_ext */
void reg_access_hca_mgir_dev_info_ext_pack(const struct reg_access_hca_mgir_dev_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_dev_info_ext_unpack(struct reg_access_hca_mgir_dev_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_dev_info_ext_print(const struct reg_access_hca_mgir_dev_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_dev_info_ext_size(void);
#define REG_ACCESS_HCA_MGIR_DEV_INFO_EXT_SIZE    (0x1c)
void reg_access_hca_mgir_dev_info_ext_dump(const struct reg_access_hca_mgir_dev_info_ext *ptr_struct, FILE *fd);
/* mgir_fw_info_ext */
void reg_access_hca_mgir_fw_info_ext_pack(const struct reg_access_hca_mgir_fw_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_fw_info_ext_unpack(struct reg_access_hca_mgir_fw_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_fw_info_ext_print(const struct reg_access_hca_mgir_fw_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_fw_info_ext_size(void);
#define REG_ACCESS_HCA_MGIR_FW_INFO_EXT_SIZE    (0x40)
void reg_access_hca_mgir_fw_info_ext_dump(const struct reg_access_hca_mgir_fw_info_ext *ptr_struct, FILE *fd);
/* mgir_hardware_info_ext */
void reg_access_hca_mgir_hardware_info_ext_pack(const struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_hardware_info_ext_unpack(struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_hardware_info_ext_print(const struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_hardware_info_ext_size(void);
#define REG_ACCESS_HCA_MGIR_HARDWARE_INFO_EXT_SIZE    (0x20)
void reg_access_hca_mgir_hardware_info_ext_dump(const struct reg_access_hca_mgir_hardware_info_ext *ptr_struct, FILE *fd);
/* mgir_sw_info_ext */
void reg_access_hca_mgir_sw_info_ext_pack(const struct reg_access_hca_mgir_sw_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_sw_info_ext_unpack(struct reg_access_hca_mgir_sw_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_sw_info_ext_print(const struct reg_access_hca_mgir_sw_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_sw_info_ext_size(void);
#define REG_ACCESS_HCA_MGIR_SW_INFO_EXT_SIZE    (0x20)
void reg_access_hca_mgir_sw_info_ext_dump(const struct reg_access_hca_mgir_sw_info_ext *ptr_struct, FILE *fd);
/* nic_cap_ext_reg_cap_data_auto_ext */
void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_pack(const union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_unpack(union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_print(const union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_size(void);
#define REG_ACCESS_HCA_NIC_CAP_EXT_REG_CAP_DATA_AUTO_EXT_SIZE    (0x70)
void reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext_dump(const union reg_access_hca_nic_cap_ext_reg_cap_data_auto_ext *ptr_struct, FILE *fd);
/* ptys_reg_ext_ib_proto_admin_auto_ext */
void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_pack(const union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_unpack(union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_print(const union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_size(void);
#define REG_ACCESS_HCA_PTYS_REG_EXT_IB_PROTO_ADMIN_AUTO_EXT_SIZE    (0x4)
void reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext_dump(const union reg_access_hca_ptys_reg_ext_ib_proto_admin_auto_ext *ptr_struct, FILE *fd);
/* ptys_reg_ext_ib_proto_cap_auto_ext */
void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_pack(const union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_unpack(union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_print(const union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_size(void);
#define REG_ACCESS_HCA_PTYS_REG_EXT_IB_PROTO_CAP_AUTO_EXT_SIZE    (0x4)
void reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext_dump(const union reg_access_hca_ptys_reg_ext_ib_proto_cap_auto_ext *ptr_struct, FILE *fd);
/* ptys_reg_ext_ib_proto_oper_auto_ext */
void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_pack(const union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_unpack(union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_print(const union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_size(void);
#define REG_ACCESS_HCA_PTYS_REG_EXT_IB_PROTO_OPER_AUTO_EXT_SIZE    (0x4)
void reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext_dump(const union reg_access_hca_ptys_reg_ext_ib_proto_oper_auto_ext *ptr_struct, FILE *fd);
/* string_db_parameters_ext */
void reg_access_hca_string_db_parameters_ext_pack(const struct reg_access_hca_string_db_parameters_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_string_db_parameters_ext_unpack(struct reg_access_hca_string_db_parameters_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_string_db_parameters_ext_print(const struct reg_access_hca_string_db_parameters_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_string_db_parameters_ext_size(void);
#define REG_ACCESS_HCA_STRING_DB_PARAMETERS_EXT_SIZE    (0x8)
void reg_access_hca_string_db_parameters_ext_dump(const struct reg_access_hca_string_db_parameters_ext *ptr_struct, FILE *fd);
/* uint64 */
void reg_access_hca_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_uint64_size(void);
#define REG_ACCESS_HCA_UINT64_SIZE    (0x8)
void reg_access_hca_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* MRSV_ext */
void reg_access_hca_MRSV_ext_pack(const struct reg_access_hca_MRSV_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_MRSV_ext_unpack(struct reg_access_hca_MRSV_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_MRSV_ext_print(const struct reg_access_hca_MRSV_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_MRSV_ext_size(void);
#define REG_ACCESS_HCA_MRSV_EXT_SIZE    (0x40)
void reg_access_hca_MRSV_ext_dump(const struct reg_access_hca_MRSV_ext *ptr_struct, FILE *fd);
/* debug_cap */
void reg_access_hca_debug_cap_pack(const struct reg_access_hca_debug_cap *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_debug_cap_unpack(struct reg_access_hca_debug_cap *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_debug_cap_print(const struct reg_access_hca_debug_cap *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_debug_cap_size(void);
#define REG_ACCESS_HCA_DEBUG_CAP_SIZE    (0x40)
void reg_access_hca_debug_cap_dump(const struct reg_access_hca_debug_cap *ptr_struct, FILE *fd);
/* dtor_reg_ext */
void reg_access_hca_dtor_reg_ext_pack(const struct reg_access_hca_dtor_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_dtor_reg_ext_unpack(struct reg_access_hca_dtor_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_dtor_reg_ext_print(const struct reg_access_hca_dtor_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_dtor_reg_ext_size(void);
#define REG_ACCESS_HCA_DTOR_REG_EXT_SIZE    (0x40)
void reg_access_hca_dtor_reg_ext_dump(const struct reg_access_hca_dtor_reg_ext *ptr_struct, FILE *fd);
/* mcam_reg_ext */
void reg_access_hca_mcam_reg_ext_pack(const struct reg_access_hca_mcam_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcam_reg_ext_unpack(struct reg_access_hca_mcam_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcam_reg_ext_print(const struct reg_access_hca_mcam_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcam_reg_ext_size(void);
#define REG_ACCESS_HCA_MCAM_REG_EXT_SIZE    (0x48)
void reg_access_hca_mcam_reg_ext_dump(const struct reg_access_hca_mcam_reg_ext *ptr_struct, FILE *fd);
/* mcc_reg_ext */
void reg_access_hca_mcc_reg_ext_pack(const struct reg_access_hca_mcc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcc_reg_ext_unpack(struct reg_access_hca_mcc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcc_reg_ext_print(const struct reg_access_hca_mcc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcc_reg_ext_size(void);
#define REG_ACCESS_HCA_MCC_REG_EXT_SIZE    (0x20)
void reg_access_hca_mcc_reg_ext_dump(const struct reg_access_hca_mcc_reg_ext *ptr_struct, FILE *fd);
/* mcda_reg_ext */
void reg_access_hca_mcda_reg_ext_pack(const struct reg_access_hca_mcda_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcda_reg_ext_unpack(struct reg_access_hca_mcda_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcda_reg_ext_print(const struct reg_access_hca_mcda_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcda_reg_ext_size(void);
#define REG_ACCESS_HCA_MCDA_REG_EXT_SIZE    (0x90)
void reg_access_hca_mcda_reg_ext_dump(const struct reg_access_hca_mcda_reg_ext *ptr_struct, FILE *fd);
/* mcia_ext */
void reg_access_hca_mcia_ext_pack(const struct reg_access_hca_mcia_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcia_ext_unpack(struct reg_access_hca_mcia_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcia_ext_print(const struct reg_access_hca_mcia_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcia_ext_size(void);
#define REG_ACCESS_HCA_MCIA_EXT_SIZE    (0x94)
void reg_access_hca_mcia_ext_dump(const struct reg_access_hca_mcia_ext *ptr_struct, FILE *fd);
/* mcqi_reg_ext */
void reg_access_hca_mcqi_reg_ext_pack(const struct reg_access_hca_mcqi_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_ext_unpack(struct reg_access_hca_mcqi_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqi_reg_ext_print(const struct reg_access_hca_mcqi_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqi_reg_ext_size(void);
#define REG_ACCESS_HCA_MCQI_REG_EXT_SIZE    (0x94)
void reg_access_hca_mcqi_reg_ext_dump(const struct reg_access_hca_mcqi_reg_ext *ptr_struct, FILE *fd);
/* mcqs_reg_ext */
void reg_access_hca_mcqs_reg_ext_pack(const struct reg_access_hca_mcqs_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mcqs_reg_ext_unpack(struct reg_access_hca_mcqs_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mcqs_reg_ext_print(const struct reg_access_hca_mcqs_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mcqs_reg_ext_size(void);
#define REG_ACCESS_HCA_MCQS_REG_EXT_SIZE    (0x10)
void reg_access_hca_mcqs_reg_ext_dump(const struct reg_access_hca_mcqs_reg_ext *ptr_struct, FILE *fd);
/* mfba_reg_ext */
void reg_access_hca_mfba_reg_ext_pack(const struct reg_access_hca_mfba_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mfba_reg_ext_unpack(struct reg_access_hca_mfba_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mfba_reg_ext_print(const struct reg_access_hca_mfba_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mfba_reg_ext_size(void);
#define REG_ACCESS_HCA_MFBA_REG_EXT_SIZE    (0x10c)
void reg_access_hca_mfba_reg_ext_dump(const struct reg_access_hca_mfba_reg_ext *ptr_struct, FILE *fd);
/* mfbe_reg_ext */
void reg_access_hca_mfbe_reg_ext_pack(const struct reg_access_hca_mfbe_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mfbe_reg_ext_unpack(struct reg_access_hca_mfbe_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mfbe_reg_ext_print(const struct reg_access_hca_mfbe_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mfbe_reg_ext_size(void);
#define REG_ACCESS_HCA_MFBE_REG_EXT_SIZE    (0xc)
void reg_access_hca_mfbe_reg_ext_dump(const struct reg_access_hca_mfbe_reg_ext *ptr_struct, FILE *fd);
/* mfpa_reg_ext */
void reg_access_hca_mfpa_reg_ext_pack(const struct reg_access_hca_mfpa_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mfpa_reg_ext_unpack(struct reg_access_hca_mfpa_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mfpa_reg_ext_print(const struct reg_access_hca_mfpa_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mfpa_reg_ext_size(void);
#define REG_ACCESS_HCA_MFPA_REG_EXT_SIZE    (0x20)
void reg_access_hca_mfpa_reg_ext_dump(const struct reg_access_hca_mfpa_reg_ext *ptr_struct, FILE *fd);
/* mfrl_reg_ext */
void reg_access_hca_mfrl_reg_ext_pack(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mfrl_reg_ext_unpack(struct reg_access_hca_mfrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mfrl_reg_ext_print(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mfrl_reg_ext_size(void);
#define REG_ACCESS_HCA_MFRL_REG_EXT_SIZE    (0x8)
void reg_access_hca_mfrl_reg_ext_dump(const struct reg_access_hca_mfrl_reg_ext *ptr_struct, FILE *fd);
/* mfsv_reg_ext */
void reg_access_hca_mfsv_reg_ext_pack(const struct reg_access_hca_mfsv_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mfsv_reg_ext_unpack(struct reg_access_hca_mfsv_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mfsv_reg_ext_print(const struct reg_access_hca_mfsv_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mfsv_reg_ext_size(void);
#define REG_ACCESS_HCA_MFSV_REG_EXT_SIZE    (0x30)
void reg_access_hca_mfsv_reg_ext_dump(const struct reg_access_hca_mfsv_reg_ext *ptr_struct, FILE *fd);
/* mgir_ext */
void reg_access_hca_mgir_ext_pack(const struct reg_access_hca_mgir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mgir_ext_unpack(struct reg_access_hca_mgir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mgir_ext_print(const struct reg_access_hca_mgir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mgir_ext_size(void);
#define REG_ACCESS_HCA_MGIR_EXT_SIZE    (0xa0)
void reg_access_hca_mgir_ext_dump(const struct reg_access_hca_mgir_ext *ptr_struct, FILE *fd);
/* misoc_reg_ext */
void reg_access_hca_misoc_reg_ext_pack(const struct reg_access_hca_misoc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_misoc_reg_ext_unpack(struct reg_access_hca_misoc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_misoc_reg_ext_print(const struct reg_access_hca_misoc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_misoc_reg_ext_size(void);
#define REG_ACCESS_HCA_MISOC_REG_EXT_SIZE    (0x120)
void reg_access_hca_misoc_reg_ext_dump(const struct reg_access_hca_misoc_reg_ext *ptr_struct, FILE *fd);
/* mmdio_ext */
void reg_access_hca_mmdio_ext_pack(const struct reg_access_hca_mmdio_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mmdio_ext_unpack(struct reg_access_hca_mmdio_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mmdio_ext_print(const struct reg_access_hca_mmdio_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mmdio_ext_size(void);
#define REG_ACCESS_HCA_MMDIO_EXT_SIZE    (0xc)
void reg_access_hca_mmdio_ext_dump(const struct reg_access_hca_mmdio_ext *ptr_struct, FILE *fd);
/* mmhi_reg_ext */
void reg_access_hca_mmhi_reg_ext_pack(const struct reg_access_hca_mmhi_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mmhi_reg_ext_unpack(struct reg_access_hca_mmhi_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mmhi_reg_ext_print(const struct reg_access_hca_mmhi_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mmhi_reg_ext_size(void);
#define REG_ACCESS_HCA_MMHI_REG_EXT_SIZE    (0x80)
void reg_access_hca_mmhi_reg_ext_dump(const struct reg_access_hca_mmhi_reg_ext *ptr_struct, FILE *fd);
/* mnvdi_reg_ext */
void reg_access_hca_mnvdi_reg_ext_pack(const struct reg_access_hca_mnvdi_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mnvdi_reg_ext_unpack(struct reg_access_hca_mnvdi_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mnvdi_reg_ext_print(const struct reg_access_hca_mnvdi_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mnvdi_reg_ext_size(void);
#define REG_ACCESS_HCA_MNVDI_REG_EXT_SIZE    (0xc)
void reg_access_hca_mnvdi_reg_ext_dump(const struct reg_access_hca_mnvdi_reg_ext *ptr_struct, FILE *fd);
/* mnvgc_reg_ext */
void reg_access_hca_mnvgc_reg_ext_pack(const struct reg_access_hca_mnvgc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mnvgc_reg_ext_unpack(struct reg_access_hca_mnvgc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mnvgc_reg_ext_print(const struct reg_access_hca_mnvgc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mnvgc_reg_ext_size(void);
#define REG_ACCESS_HCA_MNVGC_REG_EXT_SIZE    (0x10)
void reg_access_hca_mnvgc_reg_ext_dump(const struct reg_access_hca_mnvgc_reg_ext *ptr_struct, FILE *fd);
/* mnvia_reg_ext */
void reg_access_hca_mnvia_reg_ext_pack(const struct reg_access_hca_mnvia_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mnvia_reg_ext_unpack(struct reg_access_hca_mnvia_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mnvia_reg_ext_print(const struct reg_access_hca_mnvia_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mnvia_reg_ext_size(void);
#define REG_ACCESS_HCA_MNVIA_REG_EXT_SIZE    (0x8)
void reg_access_hca_mnvia_reg_ext_dump(const struct reg_access_hca_mnvia_reg_ext *ptr_struct, FILE *fd);
/* mnvqc_reg_ext */
void reg_access_hca_mnvqc_reg_ext_pack(const struct reg_access_hca_mnvqc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mnvqc_reg_ext_unpack(struct reg_access_hca_mnvqc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mnvqc_reg_ext_print(const struct reg_access_hca_mnvqc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mnvqc_reg_ext_size(void);
#define REG_ACCESS_HCA_MNVQC_REG_EXT_SIZE    (0x8)
void reg_access_hca_mnvqc_reg_ext_dump(const struct reg_access_hca_mnvqc_reg_ext *ptr_struct, FILE *fd);
/* mpcir_ext */
void reg_access_hca_mpcir_ext_pack(const struct reg_access_hca_mpcir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mpcir_ext_unpack(struct reg_access_hca_mpcir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mpcir_ext_print(const struct reg_access_hca_mpcir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mpcir_ext_size(void);
#define REG_ACCESS_HCA_MPCIR_EXT_SIZE    (0xa0)
void reg_access_hca_mpcir_ext_dump(const struct reg_access_hca_mpcir_ext *ptr_struct, FILE *fd);
/* mpegc_reg_ext */
void reg_access_hca_mpegc_reg_ext_pack(const struct reg_access_hca_mpegc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mpegc_reg_ext_unpack(struct reg_access_hca_mpegc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mpegc_reg_ext_print(const struct reg_access_hca_mpegc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mpegc_reg_ext_size(void);
#define REG_ACCESS_HCA_MPEGC_REG_EXT_SIZE    (0x2c)
void reg_access_hca_mpegc_reg_ext_dump(const struct reg_access_hca_mpegc_reg_ext *ptr_struct, FILE *fd);
/* mpein_reg_ext */
void reg_access_hca_mpein_reg_ext_pack(const struct reg_access_hca_mpein_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mpein_reg_ext_unpack(struct reg_access_hca_mpein_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mpein_reg_ext_print(const struct reg_access_hca_mpein_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mpein_reg_ext_size(void);
#define REG_ACCESS_HCA_MPEIN_REG_EXT_SIZE    (0x30)
void reg_access_hca_mpein_reg_ext_dump(const struct reg_access_hca_mpein_reg_ext *ptr_struct, FILE *fd);
/* mpir_ext */
void reg_access_hca_mpir_ext_pack(const struct reg_access_hca_mpir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mpir_ext_unpack(struct reg_access_hca_mpir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mpir_ext_print(const struct reg_access_hca_mpir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mpir_ext_size(void);
#define REG_ACCESS_HCA_MPIR_EXT_SIZE    (0x10)
void reg_access_hca_mpir_ext_dump(const struct reg_access_hca_mpir_ext *ptr_struct, FILE *fd);
/* mpqd_reg_ext */
void reg_access_hca_mpqd_reg_ext_pack(const struct reg_access_hca_mpqd_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mpqd_reg_ext_unpack(struct reg_access_hca_mpqd_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mpqd_reg_ext_print(const struct reg_access_hca_mpqd_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mpqd_reg_ext_size(void);
#define REG_ACCESS_HCA_MPQD_REG_EXT_SIZE    (0x10)
void reg_access_hca_mpqd_reg_ext_dump(const struct reg_access_hca_mpqd_reg_ext *ptr_struct, FILE *fd);
/* mqis_reg_ext */
void reg_access_hca_mqis_reg_ext_pack(const struct reg_access_hca_mqis_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mqis_reg_ext_unpack(struct reg_access_hca_mqis_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mqis_reg_ext_print(const struct reg_access_hca_mqis_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mqis_reg_ext_size(void);
#define REG_ACCESS_HCA_MQIS_REG_EXT_SIZE    (0x18)
void reg_access_hca_mqis_reg_ext_dump(const struct reg_access_hca_mqis_reg_ext *ptr_struct, FILE *fd);
/* mroq_ext */
void reg_access_hca_mroq_ext_pack(const struct reg_access_hca_mroq_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mroq_ext_unpack(struct reg_access_hca_mroq_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mroq_ext_print(const struct reg_access_hca_mroq_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mroq_ext_size(void);
#define REG_ACCESS_HCA_MROQ_EXT_SIZE    (0x20)
void reg_access_hca_mroq_ext_dump(const struct reg_access_hca_mroq_ext *ptr_struct, FILE *fd);
/* mrsi_ext */
void reg_access_hca_mrsi_ext_pack(const struct reg_access_hca_mrsi_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mrsi_ext_unpack(struct reg_access_hca_mrsi_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mrsi_ext_print(const struct reg_access_hca_mrsi_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mrsi_ext_size(void);
#define REG_ACCESS_HCA_MRSI_EXT_SIZE    (0x40)
void reg_access_hca_mrsi_ext_dump(const struct reg_access_hca_mrsi_ext *ptr_struct, FILE *fd);
/* mtcap_ext */
void reg_access_hca_mtcap_ext_pack(const struct reg_access_hca_mtcap_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtcap_ext_unpack(struct reg_access_hca_mtcap_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtcap_ext_print(const struct reg_access_hca_mtcap_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtcap_ext_size(void);
#define REG_ACCESS_HCA_MTCAP_EXT_SIZE    (0x10)
void reg_access_hca_mtcap_ext_dump(const struct reg_access_hca_mtcap_ext *ptr_struct, FILE *fd);
/* mtdc_ext */
void reg_access_hca_mtdc_ext_pack(const struct reg_access_hca_mtdc_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtdc_ext_unpack(struct reg_access_hca_mtdc_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtdc_ext_print(const struct reg_access_hca_mtdc_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtdc_ext_size(void);
#define REG_ACCESS_HCA_MTDC_EXT_SIZE    (0x20)
void reg_access_hca_mtdc_ext_dump(const struct reg_access_hca_mtdc_ext *ptr_struct, FILE *fd);
/* mteim_reg_ext */
void reg_access_hca_mteim_reg_ext_pack(const struct reg_access_hca_mteim_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mteim_reg_ext_unpack(struct reg_access_hca_mteim_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mteim_reg_ext_print(const struct reg_access_hca_mteim_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mteim_reg_ext_size(void);
#define REG_ACCESS_HCA_MTEIM_REG_EXT_SIZE    (0x30)
void reg_access_hca_mteim_reg_ext_dump(const struct reg_access_hca_mteim_reg_ext *ptr_struct, FILE *fd);
/* mtie_ext */
void reg_access_hca_mtie_ext_pack(const struct reg_access_hca_mtie_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtie_ext_unpack(struct reg_access_hca_mtie_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtie_ext_print(const struct reg_access_hca_mtie_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtie_ext_size(void);
#define REG_ACCESS_HCA_MTIE_EXT_SIZE    (0x30)
void reg_access_hca_mtie_ext_dump(const struct reg_access_hca_mtie_ext *ptr_struct, FILE *fd);
/* mtim_ext */
void reg_access_hca_mtim_ext_pack(const struct reg_access_hca_mtim_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtim_ext_unpack(struct reg_access_hca_mtim_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtim_ext_print(const struct reg_access_hca_mtim_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtim_ext_size(void);
#define REG_ACCESS_HCA_MTIM_EXT_SIZE    (0x10)
void reg_access_hca_mtim_ext_dump(const struct reg_access_hca_mtim_ext *ptr_struct, FILE *fd);
/* mtmp_ext */
void reg_access_hca_mtmp_ext_pack(const struct reg_access_hca_mtmp_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtmp_ext_unpack(struct reg_access_hca_mtmp_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtmp_ext_print(const struct reg_access_hca_mtmp_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtmp_ext_size(void);
#define REG_ACCESS_HCA_MTMP_EXT_SIZE    (0x20)
void reg_access_hca_mtmp_ext_dump(const struct reg_access_hca_mtmp_ext *ptr_struct, FILE *fd);
/* mtrc_cap_reg_ext */
void reg_access_hca_mtrc_cap_reg_ext_pack(const struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtrc_cap_reg_ext_unpack(struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtrc_cap_reg_ext_print(const struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtrc_cap_reg_ext_size(void);
#define REG_ACCESS_HCA_MTRC_CAP_REG_EXT_SIZE    (0x84)
void reg_access_hca_mtrc_cap_reg_ext_dump(const struct reg_access_hca_mtrc_cap_reg_ext *ptr_struct, FILE *fd);
/* mtrc_conf_reg_ext */
void reg_access_hca_mtrc_conf_reg_ext_pack(const struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtrc_conf_reg_ext_unpack(struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtrc_conf_reg_ext_print(const struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtrc_conf_reg_ext_size(void);
#define REG_ACCESS_HCA_MTRC_CONF_REG_EXT_SIZE    (0x80)
void reg_access_hca_mtrc_conf_reg_ext_dump(const struct reg_access_hca_mtrc_conf_reg_ext *ptr_struct, FILE *fd);
/* mtrc_ctrl_reg_ext */
void reg_access_hca_mtrc_ctrl_reg_ext_pack(const struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtrc_ctrl_reg_ext_unpack(struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtrc_ctrl_reg_ext_print(const struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtrc_ctrl_reg_ext_size(void);
#define REG_ACCESS_HCA_MTRC_CTRL_REG_EXT_SIZE    (0x40)
void reg_access_hca_mtrc_ctrl_reg_ext_dump(const struct reg_access_hca_mtrc_ctrl_reg_ext *ptr_struct, FILE *fd);
/* mtrc_stdb_reg_ext */
void reg_access_hca_mtrc_stdb_reg_ext_pack(const struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_mtrc_stdb_reg_ext_unpack(struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_mtrc_stdb_reg_ext_print(const struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_mtrc_stdb_reg_ext_size(void);
#define REG_ACCESS_HCA_MTRC_STDB_REG_EXT_SIZE    (0x8)
void reg_access_hca_mtrc_stdb_reg_ext_dump(const struct reg_access_hca_mtrc_stdb_reg_ext *ptr_struct, FILE *fd);
/* nic_cap_ext_reg_ext */
void reg_access_hca_nic_cap_ext_reg_ext_pack(const struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_nic_cap_ext_reg_ext_unpack(struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_nic_cap_ext_reg_ext_print(const struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_nic_cap_ext_reg_ext_size(void);
#define REG_ACCESS_HCA_NIC_CAP_EXT_REG_EXT_SIZE    (0x80)
void reg_access_hca_nic_cap_ext_reg_ext_dump(const struct reg_access_hca_nic_cap_ext_reg_ext *ptr_struct, FILE *fd);
/* nic_dpa_eu_partition_reg_ext */
void reg_access_hca_nic_dpa_eu_partition_reg_ext_pack(const struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_nic_dpa_eu_partition_reg_ext_unpack(struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_nic_dpa_eu_partition_reg_ext_print(const struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_nic_dpa_eu_partition_reg_ext_size(void);
#define REG_ACCESS_HCA_NIC_DPA_EU_PARTITION_REG_EXT_SIZE    (0x300)
void reg_access_hca_nic_dpa_eu_partition_reg_ext_dump(const struct reg_access_hca_nic_dpa_eu_partition_reg_ext *ptr_struct, FILE *fd);
/* nic_dpa_eug_reg_ext */
void reg_access_hca_nic_dpa_eug_reg_ext_pack(const struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_nic_dpa_eug_reg_ext_unpack(struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_nic_dpa_eug_reg_ext_print(const struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_nic_dpa_eug_reg_ext_size(void);
#define REG_ACCESS_HCA_NIC_DPA_EUG_REG_EXT_SIZE    (0x100)
void reg_access_hca_nic_dpa_eug_reg_ext_dump(const struct reg_access_hca_nic_dpa_eug_reg_ext *ptr_struct, FILE *fd);
/* nic_dpa_perf_ctrl_reg_ext */
void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_pack(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_unpack(struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_print(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_nic_dpa_perf_ctrl_reg_ext_size(void);
#define REG_ACCESS_HCA_NIC_DPA_PERF_CTRL_REG_EXT_SIZE    (0x40)
void reg_access_hca_nic_dpa_perf_ctrl_reg_ext_dump(const struct reg_access_hca_nic_dpa_perf_ctrl_reg_ext *ptr_struct, FILE *fd);
/* paos_reg_ext */
void reg_access_hca_paos_reg_ext_pack(const struct reg_access_hca_paos_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_paos_reg_ext_unpack(struct reg_access_hca_paos_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_paos_reg_ext_print(const struct reg_access_hca_paos_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_paos_reg_ext_size(void);
#define REG_ACCESS_HCA_PAOS_REG_EXT_SIZE    (0x10)
void reg_access_hca_paos_reg_ext_dump(const struct reg_access_hca_paos_reg_ext *ptr_struct, FILE *fd);
/* pcnr_reg_ext */
void reg_access_hca_pcnr_reg_ext_pack(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_pcnr_reg_ext_unpack(struct reg_access_hca_pcnr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_pcnr_reg_ext_print(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_pcnr_reg_ext_size(void);
#define REG_ACCESS_HCA_PCNR_REG_EXT_SIZE    (0xc)
void reg_access_hca_pcnr_reg_ext_dump(const struct reg_access_hca_pcnr_reg_ext *ptr_struct, FILE *fd);
/* pguid_reg_ext */
void reg_access_hca_pguid_reg_ext_pack(const struct reg_access_hca_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_pguid_reg_ext_unpack(struct reg_access_hca_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_pguid_reg_ext_print(const struct reg_access_hca_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_pguid_reg_ext_size(void);
#define REG_ACCESS_HCA_PGUID_REG_EXT_SIZE    (0x60)
void reg_access_hca_pguid_reg_ext_dump(const struct reg_access_hca_pguid_reg_ext *ptr_struct, FILE *fd);
/* pmaos_reg_ext */
void reg_access_hca_pmaos_reg_ext_pack(const struct reg_access_hca_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_pmaos_reg_ext_unpack(struct reg_access_hca_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_pmaos_reg_ext_print(const struct reg_access_hca_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_pmaos_reg_ext_size(void);
#define REG_ACCESS_HCA_PMAOS_REG_EXT_SIZE    (0x10)
void reg_access_hca_pmaos_reg_ext_dump(const struct reg_access_hca_pmaos_reg_ext *ptr_struct, FILE *fd);
/* pmlp_reg_ext */
void reg_access_hca_pmlp_reg_ext_pack(const struct reg_access_hca_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_pmlp_reg_ext_unpack(struct reg_access_hca_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_pmlp_reg_ext_print(const struct reg_access_hca_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_pmlp_reg_ext_size(void);
#define REG_ACCESS_HCA_PMLP_REG_EXT_SIZE    (0x40)
void reg_access_hca_pmlp_reg_ext_dump(const struct reg_access_hca_pmlp_reg_ext *ptr_struct, FILE *fd);
/* ptys_reg_ext */
void reg_access_hca_ptys_reg_ext_pack(const struct reg_access_hca_ptys_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_unpack(struct reg_access_hca_ptys_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_ptys_reg_ext_print(const struct reg_access_hca_ptys_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_ptys_reg_ext_size(void);
#define REG_ACCESS_HCA_PTYS_REG_EXT_SIZE    (0x44)
void reg_access_hca_ptys_reg_ext_dump(const struct reg_access_hca_ptys_reg_ext *ptr_struct, FILE *fd);
/* resource_dump_ext */
void reg_access_hca_resource_dump_ext_pack(const struct reg_access_hca_resource_dump_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_resource_dump_ext_unpack(struct reg_access_hca_resource_dump_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_resource_dump_ext_print(const struct reg_access_hca_resource_dump_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_resource_dump_ext_size(void);
#define REG_ACCESS_HCA_RESOURCE_DUMP_EXT_SIZE    (0x100)
void reg_access_hca_resource_dump_ext_dump(const struct reg_access_hca_resource_dump_ext *ptr_struct, FILE *fd);
/* reg_access_hca_Nodes */
void reg_access_hca_reg_access_hca_Nodes_pack(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, u_int8_t *ptr_buff);
void reg_access_hca_reg_access_hca_Nodes_unpack(union reg_access_hca_reg_access_hca_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_hca_reg_access_hca_Nodes_print(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_hca_reg_access_hca_Nodes_size(void);
#define REG_ACCESS_HCA_REG_ACCESS_HCA_NODES_SIZE    (0x300)
void reg_access_hca_reg_access_hca_Nodes_dump(const union reg_access_hca_reg_access_hca_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_HCA_LAYOUTS_H
