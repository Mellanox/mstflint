
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
         *** This file was generated at "2025-12-21 15:54:24"
         *** by:
         ***    > [REDACTED]/adb2pack.py --input adb/prm/switch/ext/reg_access_switch.adb --file-prefix reg_access_switch --prefix reg_access_switch_ --no-adb-utils
         ***/
#ifndef REG_ACCESS_SWITCH_LAYOUTS_H
#define REG_ACCESS_SWITCH_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_command_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Command data. It may be a request or a response data. */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	u_int32_t data[65];
};

/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_crspace_access_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Starting address */
	/* 0x0.0 - 0x0.31 */
	/* access: WO */
	u_int32_t address;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - CrSpace data */
	/* 0x4.0 - 0x100.31 */
	/* access: RW */
	u_int32_t data[64];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mddq_device_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device index
The first device should number 0 */
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t device_index;
	/* Description - The flash ID that the device is using. */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t flash_id;
	/* Description - If set to '1', the fields related to the device are valid since the line-card is powered on and plugged and matching the INI version. 
Note: this bit is not an indication to validity of the fields related to the specific FW capabilities and version. */
	/* 0x0.28 - 0x0.28 */
	/* access: RO */
	u_int8_t lc_pwr_on;
	/* Description - Thermal Shutdown. If set, the device was shut down due to thermal event. */
	/* 0x0.29 - 0x0.29 */
	/* access: RO */
	u_int8_t thermal_sd;
	/* Description - If set to '1', the device is the flash owner. Otherwise, a shared flash is used by this device (another device is the flash owner). */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t flash_owner;
	/* Description - If set, the device uses a flash */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t uses_flash;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: Amos Gearbox
1: Abir Gearbox */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t device_type;
	/* Description - Major FW version number. Valid only after the FW is burnt. Otherwise, the value should be '0'. */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t fw_major;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Sub-minor FW version number. Valid only after the FW is burnt. Otherwise, the value should be '0'. */
	/* 0x8.0 - 0x8.15 */
	/* access: RO */
	u_int16_t fw_sub_minor;
	/* Description - Minor FW version number. Valid only after the FW is burnt. Otherwise, the value should be '0'. */
	/* 0x8.16 - 0x8.31 */
	/* access: RO */
	u_int16_t fw_minor;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Maximum write size (in D-Words) that the device supports for its PRM commands. */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t max_cmd_write_size_supp;
	/* Description - Maximum read size (in D-Words) that the device supports for its PRM commands. */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t max_cmd_read_size_supp;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Device type ASCII name. Up to 8 chars
	*/
	/* 0x10.24 - 0x18.23 */
	/* access: RO */
	u_int8_t device_type_name[8];
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mddq_slot_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - If set, the FW has completed the MDDC.device_enable command */
	/* 0x0.27 - 0x0.27 */
	/* access: RO */
	u_int8_t active;
	/* Description - If set, the LC is powered on, matching the INI version and a new FW version can be burnt (if necessary)
0: Not ready
1: Ready
2: Error
3: Reserved */
	/* 0x0.28 - 0x0.29 */
	/* access: RO */
	u_int8_t lc_ready;
	/* Description - If set, Shift Register is valid (after being provisioned) and data can be sent from the switch ASIC to the line-card CPLD over Shift-Register. */
	/* 0x0.30 - 0x0.30 */
	/* access: RO */
	u_int8_t sr_valid;
	/* Description - If set, the INI file is ready and the card is provisioned */
	/* 0x0.31 - 0x0.31 */
	/* access: RO */
	u_int8_t provisioned;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - User-configured version number of the current INI file.
Valid only when active or lc_ready are '1'. */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t ini_file_version;
	/* Description - HW revision of the line-card as it appears in the current INI file.
Valid only when active or lc_ready are '1'. */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t hw_revision;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Card type
0x00: Buffalo 4x400G
0x01: Buffalo 8x200G
0x02: Buffalo 16x100G
	*/
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t card_type;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mddq_slot_name_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot's ASCII name. Up to 20 chars
	*/
	/* 0x0.24 - 0x14.23 */
	/* access: RO */
	u_int8_t slot_ascii_name[20];
};

/* Description -   */
/* Size in bytes - 260 */
struct reg_access_switch_prm_register_payload_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Register ID */
	/* 0x0.0 - 0x0.15 */
	/* access: INDEX */
	u_int16_t register_id;
	/* Description - 0: Query
1: Write */
	/* 0x0.22 - 0x0.23 */
	/* access: OP */
	u_int8_t method;
	/* Description - Return code of the Downstream Device to the register that was sent.
0x0: OK - Operation was successfully executed
0x1: BUSY 
0x4: NOT_SUPP_REG - The Switch register requested is not supported on that device
0x7: BAD_PARAM - Incomplete or erroneous parameter set
0x70: INTERNAL_ERR - Internal error */
	/* 0x0.24 - 0x0.31 */
	/* access: RO */
	u_int8_t status;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Register data */
	/* 0x4.0 - 0x100.31 */
	/* access: RW */
	u_int32_t register_data[64];
};

/* Description -   */
/* Size in bytes - 4 */
struct reg_access_switch_lane_2_module_mapping_ext {
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
	/* Description - Indicates start offset of rx_lane, tx_lane inside the modules lanes in 8x granularity. relevant for modules with more than 8 lanes. such as OE.
0: lanes_0-7
1: lanes_8_15
2: lanes_16_23
3: lanes_24_31 */
	/* 0x0.12 - 0x0.13 */
	/* access: RW */
	u_int8_t sub_module;
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
/* Size in bytes - 32 */
union reg_access_switch_mddq_data_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_device_info_ext mddq_device_info_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_slot_info_ext mddq_slot_info_ext;
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_slot_name_ext mddq_slot_name_ext;
};

/* Description -   */
/* Size in bytes - 260 */
union reg_access_switch_mddt_reg_payload_auto_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	struct reg_access_switch_command_payload_ext command_payload_ext;
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	struct reg_access_switch_crspace_access_payload_ext crspace_access_payload_ext;
	/* Description -  */
	/* 0x0.0 - 0x100.31 */
	/* access: RW */
	struct reg_access_switch_prm_register_payload_ext prm_register_payload_ext;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mgpir_hw_info_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Number of devices of device_type. 
	*/
	/* 0x0.0 - 0x0.7 */
	/* access: RO */
	u_int8_t num_of_devices;
	/* Description - Total number of modules within the specific ASIC.

Note: 
For multi ASIC platforms, this field will provide the total number of modules for all ASICs combined together.
For single ASIC platforms, the value will be the same as numfer_of_modules
For QM-3 CPO (Taipan), return the total num of ELS and OE_MCU together. First indexes represent the OE and the higher indexes are assigned to ELS modules. */
	/* 0x0.8 - 0x0.15 */
	/* access: RO */
	u_int8_t num_of_modules_per_system;
	/* Description - Number of devices of device_type per flash. 
	*/
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t devices_per_flash;
	/* Description - Device type.
0: No devices on system of that type.
1: Gearbox 
2: Tiles
3: No Info Available
4: XM */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t device_type;
	/* Description - Slot index
0: Main board */
	/* 0x0.28 - 0x0.31 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Number of modules within the specific ASIC.
	*/
	/* 0x4.0 - 0x4.7 */
	/* access: RO */
	u_int8_t num_of_modules;
	/* Description - Number of slots in the system. To eliminate receiving 'bad param' status, the user should query that field with slot_index set to 0. */
	/* 0x4.8 - 0x4.15 */
	/* access: RO */
	u_int8_t num_of_slots;
	/* Description - Maximum number of modules that can be connected per slot. Includes internal and external modules. */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t max_modules_per_slot;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Num of Resource Modules. 
Value of 0xff..ff means not valid.
	*/
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t num_of_resource_modules;
	/* Description - Maximum lane count per submodule */
	/* 0x8.16 - 0x8.19 */
	/* access: RO */
	u_int8_t num_lanes_per_sub_module;
	/* Description - The maximum submodule index.
0: Only one submodule 3: Four submodules

Other values are reserved */
	/* 0x8.24 - 0x8.27 */
	/* access: RO */
	u_int8_t max_sub_modules_index;
};

/* Description -   */
/* Size in bytes - 32 */
struct reg_access_switch_mmta_tec_power_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - The required cooling level based on TEC power and Set Point.
Cooling Level units are % i.e percentage.
0% (no need to cool down) to 100% (max cooling resource, e.g fan, to cool down the module).
	*/
	/* 0x0.0 - 0x0.15 */
	/* access: RO */
	u_int16_t cooling_level;
	/* Description - Temperature measurement units
0: units of 0.125 Celsius degrees
1: units of 1/256 Celsius degrees

For negative values 2's complement is used
	*/
	/* 0x0.29 - 0x0.29 */
	/* access: INDEX */
	u_int8_t temp_unit;
	/* Description - Max TEC Power Reset:
0: do not modify the value of the max temperature register
1: clear the value of the max TEC Power and max Setpoint register */
	/* 0x0.30 - 0x0.30 */
	/* access: OP */
	u_int8_t mtpr;
	/* Description - Max TEC Power Enable:
0: disable measuring the max TEC Power and set point on a module
1: enables measuring the max TEC Power and set point on a module */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t mtpe;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - TEC power reading from the module. Units of 1mW. */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t tec_power;
	/* Description - The highest measured TEC power from the module.
Reserved when mtece = 0
Cleared by mtecr = 1 */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t max_tec_power;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Refers to module TEC Power low warning threshold. Units of 1mW. */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t tec_power_warning_low;
	/* Description - Refers to module TEC Power high warning threshold. Units of 1mW. */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t tec_power_warning_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Refers to module TEC Power low alarm threshold. Units of 1mW. */
	/* 0xc.0 - 0xc.15 */
	/* access: RW */
	u_int16_t tec_power_alarm_low;
	/* Description - Refers to module TEC Power high alarm threshold. Units of 1mW. */
	/* 0xc.16 - 0xc.31 */
	/* access: RW */
	u_int16_t tec_power_alarm_high;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Laser set point measured from the laser
Units defined at temp_unit field
	*/
	/* 0x10.0 - 0x10.15 */
	/* access: RO */
	u_int16_t set_point_temperature;
	/* Description - The highest measured set point from the module.
Reserved when mtece = 0
Cleared by mtecr = 1 */
	/* 0x10.16 - 0x10.31 */
	/* access: RO */
	u_int16_t max_set_point_temperature;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Refers to module set point low warning threshold Units defined at temp_unit field */
	/* 0x14.0 - 0x14.15 */
	/* access: RW */
	u_int16_t set_point_temperature_warning_low;
	/* Description - Refers to module TEC Power high warning threshold Units defined at temp_unit field */
	/* 0x14.16 - 0x14.31 */
	/* access: RW */
	u_int16_t set_point_temperature_warning_high;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - Refers to module set point low alarm threshold
Units defined at temp_unit field */
	/* 0x18.0 - 0x18.15 */
	/* access: RW */
	u_int16_t set_point_temperature_alarm_low;
	/* Description - Refers to module set point high alarm threshold
Units defined at temp_unit field */
	/* 0x18.16 - 0x18.31 */
	/* access: RW */
	u_int16_t set_point_temperature_alarm_high;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - The minimum allowed cooling level
	*/
	/* 0x1c.0 - 0x1c.15 */
	/* access: RO */
	u_int16_t min_cooling_level;
	/* Description - The maximum allowed cooling level
	*/
	/* 0x1c.16 - 0x1c.31 */
	/* access: RO */
	u_int16_t max_cooling_level;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_mmta_temprature_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Temperature measurement units
0: units of 0.125 Celsius degrees
1: units of 1/256 Celsius degrees

For negative values 2's complement is used
	*/
	/* 0x0.26 - 0x0.26 */
	/* access: INDEX */
	u_int8_t temp_unit;
	/* Description - Temperature Warning Event Enable (MMTA Trap)
0: do_not_generate_event
1: generate_events
2: generate_single_event */
	/* 0x0.27 - 0x0.28 */
	/* access: RW */
	u_int8_t twee;
	/* Description - Temperature Warning Enable:
0: all fields are set
1: only twee field is set, all other fields reserved */
	/* 0x0.29 - 0x0.29 */
	/* access: OP */
	u_int8_t twe;
	/* Description - Max Temperature Reset:
0: do not modify the value of the max temperature register
1: clear the value of the max temperature register */
	/* 0x0.30 - 0x0.30 */
	/* access: OP */
	u_int8_t mtr;
	/* Description - Max Temperature Enable:
0: disable measuring the max temperature on a sensor
1: enables measuring the max temperature on a sensor */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t mte;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Temperature reading from the module
Units defined at temp_unit field */
	/* 0x4.0 - 0x4.15 */
	/* access: RO */
	u_int16_t temperature;
	/* Description - The highest measured temperature from the module.
Reserved when mte = 0
Cleared by mtr = 1 */
	/* 0x4.16 - 0x4.31 */
	/* access: RO */
	u_int16_t max_temperature;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Refers to module temperature low warning threshold
Units defined at temp_unit field */
	/* 0x8.0 - 0x8.15 */
	/* access: RW */
	u_int16_t temperature_warning_low;
	/* Description - Refers to module temperature high warning threshold
Units defined at temp_unit field */
	/* 0x8.16 - 0x8.31 */
	/* access: RW */
	u_int16_t temperature_warning_high;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Refers to module temperature low alarm threshold
Units defined at temp_unit field */
	/* 0xc.0 - 0xc.15 */
	/* access: RW */
	u_int16_t temperature_alarm_low;
	/* Description - Refers to module temperature high alarm threshold
Units defined at temp_unit field */
	/* 0xc.16 - 0xc.31 */
	/* access: RW */
	u_int16_t temperature_alarm_high;
};

/* Description -   */
/* Size in bytes - 8 */
struct reg_access_switch_uint64 {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	u_int64_t uint64;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_MMAM_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - (Global) Module number
Switch: Range 0 .. MGPIR.max_modules_per_slot -1
	*/
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t module;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Geographical Address of the ASIC which controls the module

Reserved when module type is chip2chip or backplane. */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t ga;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Local module number */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t local_module;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - module_type:
0: Backplane_with_4_lanes
1: QSFP
2: SFP
3: No_Cage
4: Backplane_with_single_lane
8: Backplane_with_two_lanes
10: Chip2Chip4x
11: Chip2Chip2x
12: Chip2Chip1x
14: QSFP_DD
15: OSFP
16: SFP_DD
17: DSFP
18: Chip2Chip8x
19: Twisted_Pair
20: Backplane_with_8_lanes
21: Loopback 
22: OE_16x
23: OSFP_ELS
24: QSFP_2x
25: CPO_32x */
	/* 0xc.0 - 0xc.7 */
	/* access: RO */
	u_int8_t module_type;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_PPCR_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port[9:8]
Reserved for HCA */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number.
	*/
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - [DWIP]
Indicate whether asymmetry is enabled or not.

For HCA, reserved if PPCR.asymmetry_enable_supported=0 */
	/* 0x4.30 - 0x4.30 */
	/* access: RO */
	u_int8_t asymmetry_enable;
	/* Description - [DWIP]
Indicate whether asymmetry_enable supported or not.
Reserved for switch.
	*/
	/* 0x4.31 - 0x4.31 */
	/* access: RO */
	u_int8_t asymmetry_enable_supported;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Aggregated Port number to be reflected in MAD.
0 means N/A

Reserved for HCA */
	/* 0x8.0 - 0x8.7 */
	/* access: RW */
	u_int8_t aggregated_port;
	/* Description - Plane number to be reflected in MAD.
0 means N/A

Reserved for HCA */
	/* 0x8.16 - 0x8.18 */
	/* access: RW */
	u_int8_t plane;
	/* Description - When planarized  the FW shall respond to Hierarchy Info.Split with the following split value.
In this use case it represents the split of the APort.

When split = 0, the FW shall send Hierarchy Info without the split field. (meaning it is NA)

When Non planarized (num_of_planes = 0), Hierarchy Info.Split will reflect the actual split value, when 2X- it'll hold the location within the 4x.

0: NA
1: Split 1.
2: Split 2.
3-7: Reserved
Reserved for HCA */
	/* 0x8.24 - 0x8.26 */
	/* access: RW */
	u_int8_t split;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - The number of planes comprising this Aggregated port
	*/
	/* 0xc.0 - 0xc.7 */
	/* access: RW */
	u_int8_t num_of_planes;
	/* Description - [DWIP]
Planarization Type
0: non planarized
1: planirized_gen1
2-7: Reserved */
	/* 0xc.16 - 0xc.18 */
	/* access: RW */
	u_int8_t p_type;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_icam_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Access Register ID groups 
0: REG_IDs 0x3800 to 0x387F
1: REG_IDs 0x3880 to 0x38FF */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t access_reg_group;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Supported infrastructure's access register bitmask. Based on access_reg_group index. 
When bit is set to '1', The register is supported in the device. 
For example, when access_reg_group == 1:
Bit 112: ICSR
Bit0 is at 08h.bit0
Bit 127 is at 14h.bit31 */
	/* 0x8.0 - 0x14.31 */
	/* access: RO */
	u_int32_t infr_access_reg_cap_mask[4];
};

/* Description -   */
/* Size in bytes - 1040 */
struct reg_access_switch_icsr_ext {
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Base cr-space address for reading */
	/* 0x4.0 - 0x4.31 */
	/* access: INDEX */
	u_int32_t base_address;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Number of cr-space consecutive reads.
Each read is 4B (DWord)
Range 1..256 */
	/* 0x8.0 - 0x8.8 */
	/* access: OP */
	u_int16_t num_reads;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - The cr-space read data */
	/* 0x10.0 - 0x40c.31 */
	/* access: RO */
	u_int32_t data[256];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mddq_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Slot index
0: Reserved */
	/* 0x0.0 - 0x0.3 */
	/* access: INDEX */
	u_int8_t slot_index;
	/* Description - 0: Reserved
1: slot_info
2: device_info - for a device on the slot. If there are no devices on the slot, data_valid will be '0'.
3: slot_name - Name of the slot (string) */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t query_type;
	/* Description - Slot info event enable
When set to '1', each change in the MDDQ.slot_info.provisioned / sr_valid / active / ready will generate an DSDSC event. */
	/* 0x0.31 - 0x0.31 */
	/* access: RW */
	u_int8_t sie;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Request message sequential number. 
The first message number should be 0 */
	/* 0x4.0 - 0x4.7 */
	/* access: INDEX */
	u_int8_t request_message_sequence;
	/* Description - Response message sequential number. 
For a specific request, the response message sequential number is the following one. 
In addition, the last message should be 0. */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t response_message_sequence;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Index related to the specific query_type. 
For query_type = 1,2,3 this field is neglected. */
	/* 0x8.0 - 0x8.7 */
	/* access: INDEX */
	u_int8_t query_index;
	/* Description - If set, the data in the data field is valid and contain the information for the queried index. 
Note: This field is not reflecting any validity of the data while accessing a non-existing query entity. Querying with an out of range index will lead to BAD_PARAM status of the register. */
	/* 0x8.31 - 0x8.31 */
	/* access: RO */
	u_int8_t data_valid;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Properties of that field are based on query_type.
For slot information query_type data - see Table 573, "MDDQ slot_info Layout," on page 1121
For devices on slot query_type data - see Table 575, "MDDQ device_info Register Layout," on page 1122
For slot name query_type data - see Table 577, "MDDQ slot_name Layout," on page 1124 */
	/* 0x10.0 - 0x2c.31 */
	/* access: RO */
	union reg_access_switch_mddq_data_auto_ext data;
};

/* Description -   */
/* Size in bytes - 272 */
struct reg_access_switch_mddt_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device index */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t device_index;
	/* Description - Slot index */
	/* 0x0.8 - 0x0.11 */
	/* access: INDEX */
	u_int8_t slot_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 0: PRM_Register
1: Command
2: CrSpace_access */
	/* 0x4.0 - 0x4.1 */
	/* access: OP */
	u_int8_t type;
	/* Description - Write size in D-Words. */
	/* 0x4.16 - 0x4.23 */
	/* access: OP */
	u_int8_t write_size;
	/* Description - Read size in D-Words. */
	/* 0x4.24 - 0x4.31 */
	/* access: OP */
	u_int8_t read_size;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Payload
For PRM Register type payload - See Table 565, "PRM Register Payload Layout," on page 1117
For Command type payload - See Table 567, "Command Payload Layout," on page 1117
For CrSpace type payload - See Table 569, "CrSpace access Payload Layout," on page 1118 */
	/* 0xc.0 - 0x10c.31 */
	/* access: RW */
	union reg_access_switch_mddt_reg_payload_auto_ext payload;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mdsr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - 0: The debug session ended successfully
1: Failed to execute the operation. See additional_info for more details.
2: Debug session active. See type_of_token for more details.
3: No token applied
4: Challenge provided, no token installed yet, see type_of_token for details.
5: Timeout before token installed, see type_of_token for details
6: Timeout of active token.
7-15: Reserved

Note: Status might be '0' even when debug query is not allowed and additional_info field will expose the reason. */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t status;
	/* Description - 0: No additional information available 
1: There is no debug session in progress
2: FW is not secured, debug session cannot be ended
3: Fail - Debug end request cannot be accepted. 
4: Fail - Host is not allowed to query debug session
5: Debug session active */
	/* 0x0.8 - 0x0.13 */
	/* access: RO */
	u_int8_t additional_info;
	/* Description - 0: CS token 
1: Debug FW token 
2: FRC token 
3: RMCS token
4: RMDT token 
5: CRCS token 
6: CRDT token

8: MTFA token
0xFF: All tokens. Relevant only when end=1 */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t type_of_token;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Set to '1' to end debug session.
Setting to '0' will not trigger any operation. */
	/* 0x4.30 - 0x4.30 */
	/* access: WO */
	u_int8_t revoke_version;
	/* Description - Used to revoke token version from device. Relevant only when end=1. */
	/* 0x4.31 - 0x4.31 */
	/* access: WO */
	u_int8_t end;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Time left in seconds.
In case that status is 2 (debug session active) - time left for token operation
In case that status is 4 (challenge provided, no token installed yet) - time left for token installation
For any other status, field should be zero */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t time_left;
};

/* Description -   */
/* Size in bytes - 28 */
struct reg_access_switch_mfmc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Flash select - selects the flash device.
Only zero is supported for NICs with a single flash device. 
Range between 0 .. MFPA.flash_num -1 */
	/* 0x0.4 - 0x0.5 */
	/* access: INDEX */
	u_int8_t fs;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Power of 2 of the write protect block count
0: 1 block
1: 2 blocks
2: 4 blocks
3: 8 blocks etc.
Range 0..5
Note that per flash device there may be invalid configurations
Reserved when wrp_en = 0 */
	/* 0x4.0 - 0x4.7 */
	/* access: RW */
	u_int8_t wrp_block_count;
	/* Description - Block size
0: write protect sub-sector blocks
1: write protect sector blocks
Reserved when wrp_en = 0
Note that not all block sizes are supported on all flash device, need to check MFPA capabilities */
	/* 0x4.16 - 0x4.17 */
	/* access: RW */
	u_int8_t block_size;
	/* Description - Write protect enable
Set write protect of flash device */
	/* 0x4.31 - 0x4.31 */
	/* access: RW */
	u_int8_t wrp_en;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Power of 2 for sub_sector size in 4Kbytes.
0: 4Kbyte.
1: 8 Kbyte
2: 16Kbyte.
Etc. */
	/* 0x8.0 - 0x8.5 */
	/* access: RO */
	u_int8_t sub_sector_protect_size;
	/* Description - Power of 2 for sector size in 4Kbytes.
0: 4Kbyte.
1: 8 Kbyte
2: 16Kbyte.
Etc. */
	/* 0x8.8 - 0x8.13 */
	/* access: RO */
	u_int8_t sector_protect_size;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Quad enable IO bit in the device status register */
	/* 0x10.24 - 0x10.24 */
	/* access: RW */
	u_int8_t quad_en;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - The number of dummy clock cycles subsequent to all FAST READ commands. 
Reserved if not supported by the device */
	/* 0x18.0 - 0x18.3 */
	/* access: RW */
	u_int8_t dummy_clock_cycles;
};

/* Description -   */
/* Size in bytes - 160 */
struct reg_access_switch_mgpir_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Hardware Information, see Table 583, "Hardware Info Layout," on page 1126 */
	/* 0x0.0 - 0x1c.31 */
	/* access: RW */
	struct reg_access_switch_mgpir_hw_info_ext hw_info;
};

/* Description -   */
/* Size in bytes - 44 */
struct reg_access_switch_mkdc_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Indicates the successful completion of the instruction or the reason it failed:
0: OK
1: BAD_SESSION_ID
2: BAD_KEEP_ALIVE_COUNTER
3: BAD_SOURCE_ADDRESS
4: SESSION_TIMEOUT
Other values are Reserved. */
	/* 0x0.0 - 0x0.3 */
	/* access: RO */
	u_int8_t error_code;
	/* Description - Unique debug session identifier. */
	/* 0x0.16 - 0x0.31 */
	/* access: INDEX */
	u_int16_t session_id;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Running counter that states the current sequence number of each keep-alive session. */
	/* 0x4.0 - 0x4.31 */
	/* access: INDEX */
	u_int32_t current_keep_alive_counter;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Running counter that states the expected next sequence number of each keep-alive session. */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t next_keep_alive_counter;
};

/* Description -   */
/* Size in bytes - 144 */
struct reg_access_switch_mmta_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - module number */
	/* 0x0.0 - 0x0.7 */
	/* access: INDEX */
	u_int8_t module;
	/* Description - Supported measurements bit mask
0: Temperature - ELS
1: TEC Power
2: Second Temperature - Optical Engines. Other are reserved */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t supported_measurements;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - 8 characters long module name */
	/* 0x4.0 - 0x4.31 */
	/* access: RO */
	u_int32_t module_name_hi;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - 8 characters long module name */
	/* 0x8.0 - 0x8.31 */
	/* access: RO */
	u_int32_t module_name_lo;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Temperature, see Table 547, "Module Temperature Layout," on page 1103 */
	/* 0xc.0 - 0x20.31 */
	/* access: RW */
	struct reg_access_switch_mmta_temprature_ext module_temperature;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - TEC Power, see Table 549, "Module TEC Power Layout," on page 1105 */
	/* 0x24.0 - 0x40.31 */
	/* access: RW */
	struct reg_access_switch_mmta_tec_power_ext module_tec_power;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Second Temperature, see Table 547, "Module Temperature Layout," on page 1103.
Note: When there is more than one Optical Engine:
1) The "temperature" field shall be populated by the highest of the current OE temperatures.
2) The "max_temperature" field shall be populated by the highest of any temperatures that had been measured, over all OEs.
	*/
	/* 0x44.0 - 0x58.31 */
	/* access: RW */
	struct reg_access_switch_mmta_temprature_ext module_second_temperature;
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mpein_reg_ext {
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
	/* Description - common clock mode:
0 - separate clock mode
1 - common clock mode */
	/* 0x18.1 - 0x18.1 */
	/* access: RO */
	u_int8_t cmn_clk_mode;
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
struct reg_access_switch_mpir_ext {
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
segment_cap = 1 : segment base that was captured in Flit mode
segment_cap = 0 : segment base that was set by software
reserved when pcie_segment is not set in MPCAM */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t segment_base;
	/* Description - when set segment base is valid, else it is invalid
must be set if segment_cap is set.
reserved when pcie_segment is not set in MPCAM */
	/* 0x4.24 - 0x4.24 */
	/* access: RO */
	u_int8_t segment_valid;
	/* Description - segment number (base) was captured in Flit mode. 
reserved when pcie_segment is not set in MPCAM */
	/* 0x4.25 - 0x4.25 */
	/* access: RO */
	u_int8_t segment_cap;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
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
/* Size in bytes - 8 */
struct reg_access_switch_mrsr_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Reset/shutdown command
0: clear state of reset_at_pci_disable
1: software reset immediate (switch soft reset).
6: reset_at_pci_disable - reset will be done at PCI_DISABLE. See MCAM bit48. Note: when no PCI (e.g. unmanaged switches or for Retimers) will do reset without waiting for PCI_DISABLE
7: fw_link_reset_at_pci_disable - PCIe FW Link Reset, core is up [DWIP] */
	/* 0x0.0 - 0x0.3 */
	/* access: RW */
	u_int8_t command;
};

/* Description -   */
/* Size in bytes - 128 */
struct reg_access_switch_msgi_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - ASIC serial number (ASCII string) */
	/* 0x0.0 - 0x14.31 */
	/* access: RO */
	u_int32_t serial_number[6];
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - ASIC part number (ASCII string) */
	/* 0x20.0 - 0x30.31 */
	/* access: RO */
	u_int32_t part_number[5];
/*---------------- DWORD[14] (Offset 0x38) ----------------*/
	/* Description - Revision (ASCII string) */
	/* 0x38.0 - 0x38.31 */
	/* access: RO */
	u_int32_t revision;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - Product Name (ASCII string) */
	/* 0x40.0 - 0x7c.31 */
	/* access: RO */
	u_int32_t product_name[16];
};

/* Description -   */
/* Size in bytes - 48 */
struct reg_access_switch_mspmer_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device Index
0: Main_board_or_NIC
	*/
	/* 0x0.0 - 0x0.3 */
	/* access: INDEX */
	u_int8_t device_index;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Status
0: Success
1: Physical monitor is not supported
2: Device index is not valid */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t status;
	/* Description - Clear Counters
0: don't clear counters
1: clear counters */
	/* 0x4.16 - 0x4.16 */
	/* access: OP */
	u_int8_t clr;
	/* Description - Prevention Enable
0: Notification only. Prevention is disabled 
1: Prevention is enabled

In Spectrum-4 only, controlled by NV_SWITCH_PHY_SEC_CONF.pvpm. See Table 392, "NV_SWITCH_PHY_SEC_CONF Layout," on page 945 */
	/* 0x4.24 - 0x4.24 */
	/* access: RO */
	u_int8_t prev_en;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - 31: FMON - Frequency MONitor
30: VMON - Voltage MONitor
29: SCPM - Secure Canary Path Monitor
0: General 

	*/
	/* 0xc.0 - 0xc.31 */
	/* access: RO */
	u_int32_t supported_physical_monitor;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Frequency Monitor Counter

Stuck at 0xF, cleared only at hard reset (RST_) or power down or clr bit. */
	/* 0x14.0 - 0x14.3 */
	/* access: RO */
	u_int8_t fmon_ctr;
	/* Description - Voltage Monitor Counter

Stuck at 0xF, cleared only at hard reset (RST_) or power down or clr bit. */
	/* 0x14.4 - 0x14.7 */
	/* access: RO */
	u_int8_t vmon_ctr;
	/* Description - Security Canary Path Monitor Counter
A circuit macro used to flag timing slack violations as part of mitigations for physical security attacks.

Stuck at 0xF, cleared only at hard reset (RST_) or power down or clr bit. */
	/* 0x14.8 - 0x14.11 */
	/* access: RO */
	u_int8_t scpm_ctr;
	/* Description - General Error indication
Cleared only at hard reset (RST_) or power down or clr bit. */
	/* 0x14.12 - 0x14.12 */
	/* access: RO */
	u_int8_t general_err;
};

/* Description -   */
/* Size in bytes - 112 */
struct reg_access_switch_mtcq_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Device number.
For gearboxes, the index represents the gearbox die.
For cables, the index represents the module index starting at index 1 while index 0 indicates the host device. */
	/* 0x0.0 - 0x0.11 */
	/* access: INDEX */
	u_int16_t device_index;
	/* Description - Indicates the status of the desired token we are generating the challenge for.
0x0 - OK
0x1 - TOKEN_ALREADY_APPLIED
0x2 - TOKEN_NOT_SUPPORTED
0x3 - NO_KEY_CONFIGURED (there is no public_key that can be used for this token) 
0x4 - INTERFACE_NOT_ALLOWED (asking for local token from remote interface, or remote token from local interface) */
	/* 0x0.16 - 0x0.23 */
	/* access: RO */
	u_int8_t status;
	/* Description - The token which a challenge is generated for.
0: RMCS - (ReMote Customer Support)
1: RMDT - (ReMote Debug Token)
2: CRCS - (Challenge-Response Customer Support) - supported from Spectrum-4 and above
3: CRDT - (Challenge-Response Debug Token) - supported from Spectrum-4 and above

5: MTDT
6: FRC - (Factory ReCustomization)
7: MTFA
Other: Reserved */
	/* 0x0.24 - 0x0.31 */
	/* access: INDEX */
	u_int8_t token_opcode;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - The UUID of the key used to generate the challenge. */
	/* 0x4.0 - 0x10.31 */
	/* access: RO */
	u_int32_t keypair_uuid[4];
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - Device base MAC address / unique identifier. */
	/* 0x14.0 - 0x18.31 */
	/* access: RO */
	u_int64_t base_mac;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Device PSID */
	/* 0x1c.0 - 0x28.31 */
	/* access: RO */
	u_int32_t psid[4];
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description - Device FW version */
	/* 0x2c.0 - 0x2c.7 */
	/* access: RO */
	u_int8_t fw_version_39_32;
/*---------------- DWORD[12] (Offset 0x30) ----------------*/
	/* Description - Device FW version */
	/* 0x30.0 - 0x30.31 */
	/* access: RO */
	u_int32_t fw_version_31_0;
/*---------------- DWORD[13] (Offset 0x34) ----------------*/
	/* Description - Source address of debug requester. DLID for Infiniband
Valid only for RMCS/RMDT. */
	/* 0x34.0 - 0x40.31 */
	/* access: RO */
	u_int32_t source_address[4];
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - Unique debug session identifier. 
See details in REMOTE_DEBUG_KEEP_ALIVE.
Valid only for RMCS. */
	/* 0x44.0 - 0x44.15 */
	/* access: RO */
	u_int16_t session_id;
	/* Description - Version of the challenge format.
	*/
	/* 0x44.24 - 0x44.31 */
	/* access: RO */
	u_int8_t challenge_version;
/*---------------- DWORD[18] (Offset 0x48) ----------------*/
	/* Description - Random generated field. Used for randomness and replay-protection. */
	/* 0x48.0 - 0x64.31 */
	/* access: RO */
	u_int32_t challenge[8];
/*---------------- DWORD[26] (Offset 0x68) ----------------*/
	/* Description - Current device"s token rachet value. */
	/* 0x68.0 - 0x6c.31 */
	/* access: RO */
	u_int64_t token_ratchet;
};

/* Description -   */
/* Size in bytes - 96 */
struct reg_access_switch_pguid_reg_ext {
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
struct reg_access_switch_plib_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - In IB port: InfiniBand port remapping for local_port
In Ethernet port: Label port remapping for local_port
Note: ib_port number can only be updated when a port admin state is DISABLED. */
	/* 0x0.0 - 0x0.9 */
	/* access: RW */
	u_int16_t ib_port;
	/* Description - Local port number [9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Valid only for Ethernet Switches. 
Label split mapping for local_port */
	/* 0x4.0 - 0x4.3 */
	/* access: RW */
	u_int8_t split_num;
};

/* Description -   */
/* Size in bytes - 24 */
struct reg_access_switch_pllp_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Front panel label of the port
Note:
PLIB.ib_port provides IB port in IB and label_port in Eth
MOLP provides the 16bit mirror header value */
	/* 0x0.0 - 0x0.9 */
	/* access: RO */
	u_int16_t label_port;
	/* Description - Local port[9:8] */
	/* 0x0.12 - 0x0.13 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Port split mapping for local_port.
The position of this local port within each splitted port.
When no split: split_num should be 0
When split to 2: split_num should be 0,1
When split to 4: split_num should be 0   3
When split to 8: split_num should be 0   7
Split to 8 exists only for ETH */
	/* 0x4.0 - 0x4.3 */
	/* access: RO */
	u_int8_t split_num;
	/* Description - Inter port in Label number.
gives mapping of the basic port unit  inside the label (cage), From the lowest lanes of the module to the highest.
e.g Label of 8x lanes, with 2 ipil
ipil 1 - will be port mapped to lanes 1-4
ipil 2 - will be port mapped to lanes 5-8

When ipil_stat is 0 (no ipil): ipil_num should be 0.
When ipil_stat is 1: ipil_num should be 1,2
When ipil_stat is 2: ipil_num should be 1   4
When ipil_stat is 3: ipil_num should be 1   8

Spectrum: Only relevant value is 0. */
	/* 0x4.8 - 0x4.11 */
	/* access: RO */
	u_int8_t ipil_num;
	/* Description - Defines the IPIL split. The value is by how much to split each IPIL
The local_port status is:
0: no split
1: split to 2
2: split to 4
3: split to 8


Spectrum: Only relevant value is 0. */
	/* 0x4.16 - 0x4.19 */
	/* access: RO */
	u_int8_t split_stat;
	/* Description - Inter port in Label status.
Number of basic port units inside the label (cage).
0: 1 inter port in label
1: 2 inter port in label
2: 4 inter port in label
3: 8 inter port in label.

Spectrum: Only relevant value is 0. */
	/* 0x4.24 - 0x4.27 */
	/* access: RO */
	u_int8_t ipil_stat;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - Valid only for Ethernet Switches. 
Slot_number mapping for local_port */
	/* 0x8.0 - 0x8.3 */
	/* access: RO */
	u_int8_t slot_num;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - Connectivity Type
0: N/A
1: not-wired 
2: wire to front panel
3: wired to Switch
4: wired to GPU
5: wired to NIC

Describes the internal wiring on the port.
Quantum: Supported from Quantum-3 and above.
Spectrum: Only relevant value is 0. */
	/* 0xc.0 - 0xc.2 */
	/* access: RO */
	u_int8_t conn_type;
	/* Description - Remote ASIC Id
Reserved when conn_type = 0/1/2
Quantum: Supported from Quantum-3 and above.
Spectrum: Reserved as 0.
Obsolete and not updated by FW. */
	/* 0xc.8 - 0xc.15 */
	/* access: RO */
	u_int8_t rmt_id;
	/* Description - 0: Mission port
1: FNM port
Supported from Quantum-3 and above */
	/* 0xc.16 - 0xc.16 */
	/* access: RO */
	u_int8_t is_fnm;
	/* Description - Mission Port as FNM 
0: Mission port
1: Mission port treated as FNM port.

When set, the port shall be configured as a FNM port. 
Reserved when is_fnm is set. 
Note: This configuration does not change port type as stated in is_fnm field. 
Quantum: Supported from Quantum-3 and above.
Spectrum: Only relevant value is 0. */
	/* 0xc.17 - 0xc.17 */
	/* access: RO */
	u_int8_t maf;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - 0: N/A (when FW has no info)
1: ETH (for Eth devices)
2: IB
3: NVLink
4: IBg2Eth
Supported from Quantum-3 and above
	*/
	/* 0x10.0 - 0x10.2 */
	/* access: RO */
	u_int8_t protocol;
	/* Description - [DWIP]
Sub Module ID.
Indicates start offset of module lanes in 8x granularity */
	/* 0x10.20 - 0x10.23 */
	/* access: RO */
	u_int8_t sub_module;
	/* Description - [DWIP]
Module ID.
Range: 0 .. MGPIR.max_modules_per_slot -1 */
	/* 0x10.24 - 0x10.31 */
	/* access: RO */
	u_int8_t module;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - [DWIP]
Resource label port 
The label port for the resource module.
Value of 0xFFFF means field is not valid.
	*/
	/* 0x14.0 - 0x14.15 */
	/* access: RO */
	u_int16_t resource_label_port;
	/* Description - [DWIP]
Optical engine identifier, which represents the OE index which the port is connected to.
Value of 0xFFFF means field is not valid. */
	/* 0x14.16 - 0x14.31 */
	/* access: RO */
	u_int16_t oe_identifier;
};

/* Description -   */
/* Size in bytes - 16 */
struct reg_access_switch_pmaos_reg_ext {
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
Note 2 - disconnect cable will shut down the optical module in ungraceful manner. Not supported for OE/ELS.
Note 3 - Disabling OE in QM-3 CPO will not cause to the OE to power disable. User will need to set all the modules to disable, which will cause the power enable to go down.
Note 4 - Disabling OE in QM3-CPO will cause the ELS to go down as well as part of the HW flow. Before setting the ELS back up, OE should be set to up beforehand.
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
/* Size in bytes - 72 */
struct reg_access_switch_pmdr_reg_ext {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Local port number [9:8] */
	/* 0x0.0 - 0x0.1 */
	/* access: INDEX */
	u_int8_t lp_msb;
	/* Description - Reserved for non-planarized port.
Plane port index of the aggregated port. A value of 0 refers to the aggregated port only. */
	/* 0x0.4 - 0x0.7 */
	/* access: INDEX */
	u_int8_t plane_ind;
	/* Description - When set, port_width field value is valid. otherwise ignored */
	/* 0x0.10 - 0x0.10 */
	/* access: RO */
	u_int8_t width_valid;
	/* Description - 0 if there is no MCM tile arch */
	/* 0x0.12 - 0x0.12 */
	/* access: RO */
	u_int8_t mcm_tile_valid;
	/* Description - 0 if there is no Gearbox/Retimer arch */
	/* 0x0.13 - 0x0.13 */
	/* access: RO */
	u_int8_t gb_valid;
	/* Description - Port number access type. determines the way local_port is interpreted:
0 - Local port number
1 - IB port number
3 - Out of band / PCI */
	/* 0x0.14 - 0x0.15 */
	/* access: INDEX */
	u_int8_t pnat;
	/* Description - [7:0] bits for Local port number. */
	/* 0x0.16 - 0x0.23 */
	/* access: INDEX */
	u_int8_t local_port;
	/* Description - 0 - 40nm products
1 - 28nm products
3 - 16nm products
4 - 7nm products
5 - 5nm products SerDes Gen7.0/ 7.5
6 - 5nm products SerDes Gen8.0 */
	/* 0x0.24 - 0x0.27 */
	/* access: RO */
	u_int8_t version;
	/* Description - 0 - Invalid
1 - Valid
2 - Bad Param (Values are not ready yet - during polling)
3 - Invalid index of local_port or label_port */
	/* 0x0.28 - 0x0.31 */
	/* access: RO */
	u_int8_t status;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - [9:8] pport bits */
	/* 0x4.6 - 0x4.7 */
	/* access: RO */
	u_int8_t pport_msb;
	/* Description - Logical cluster number */
	/* 0x4.8 - 0x4.14 */
	/* access: RO */
	u_int8_t cluster;
	/* Description -  */
	/* 0x4.16 - 0x4.23 */
	/* access: RO */
	u_int8_t module;
	/* Description -  */
	/* 0x4.24 - 0x4.31 */
	/* access: RO */
	u_int8_t pport;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.7 */
	/* access: RO */
	u_int8_t ib_port;
	/* Description - lane mask of active lanes on module */
	/* 0x8.8 - 0x8.15 */
	/* access: RO */
	u_int8_t module_lane_mask;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	/* access: RO */
	u_int8_t swid;
	/* Description - Number of ports the label port is split to.
0 - split to 1
1 - split to 2
2 - split to 4
3 - split to 8 */
	/* 0x8.24 - 0x8.26 */
	/* access: RO */
	u_int8_t split;
	/* Description - DataPath number in GB/Retimer of the port */
	/* 0x8.27 - 0x8.31 */
	/* access: RO */
	u_int8_t gb_dp_num;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - MSB Local port bits [9:8] index for the label port chosen (in case pnat field is '1'). */
	/* 0xc.0 - 0xc.1 */
	/* access: RO */
	u_int8_t lp_query_msb;
	/* Description - MSB Label port bits [9:8] index. */
	/* 0xc.2 - 0xc.3 */
	/* access: RO */
	u_int8_t lbp_query_msb;
	/* Description - MSB tile_pport bits [7:6] index. */
	/* 0xc.4 - 0xc.5 */
	/* access: RO */
	u_int8_t tile_pport_msb;
	/* Description - Port width of logical lanes.
According to number of port width, indicates how many lanes shall be considered in lane<i>_physical_tx/rx
0 - port is unmapped */
	/* 0xc.6 - 0xc.9 */
	/* access: RO */
	u_int8_t port_width;
	/* Description - LSB Local port bits [7:0] index for the label port chosen (in case pnat field is '1'). */
	/* 0xc.16 - 0xc.23 */
	/* access: RO */
	u_int8_t local_port_query;
	/* Description - Label port index for the local port chosen (in case pnat field is '0'). */
	/* 0xc.24 - 0xc.31 */
	/* access: RO */
	u_int8_t label_port_query;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description - Number of the Gearbox/Retimer the local_port is related to.
valid only when gb_valid is 1 */
	/* 0x10.0 - 0x10.6 */
	/* access: RO */
	u_int8_t gearbox_die_num;
	/* Description -  */
	/* 0x10.8 - 0x10.12 */
	/* access: RO */
	u_int8_t tile_pport;
	/* Description - Number of common PLLs mapped to port rx lanes. */
	/* 0x10.13 - 0x10.15 */
	/* access: RO */
	u_int8_t pll_cnt_rx;
	/* Description - Number of the MCM Tile the local_port is related to.
valid only when mcm_tile_valid is 1
	*/
	/* 0x10.16 - 0x10.23 */
	/* access: RO */
	u_int8_t mcm_tile_num;
	/* Description -  */
	/* 0x10.24 - 0x10.27 */
	/* access: RO */
	u_int8_t tile_cluster;
	/* Description - Reserved for HCA 
Slot_index 
Slot_index = 0 represent the onboard (motherboard). 
In case of non modular system only slot_index = 0 is available. */
	/* 0x10.28 - 0x10.31 */
	/* access: RO */
	u_int8_t slot_index;
/*---------------- DWORD[5] (Offset 0x14) ----------------*/
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.0 - 0x14.2 */
	/* access: RO */
	u_int8_t lane0_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.3 - 0x14.5 */
	/* access: RO */
	u_int8_t lane1_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.6 - 0x14.8 */
	/* access: RO */
	u_int8_t lane2_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.9 - 0x14.11 */
	/* access: RO */
	u_int8_t lane3_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.12 - 0x14.14 */
	/* access: RO */
	u_int8_t lane4_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.15 - 0x14.17 */
	/* access: RO */
	u_int8_t lane5_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.18 - 0x14.20 */
	/* access: RO */
	u_int8_t lane6_physical_rx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical rx lane mapping */
	/* 0x14.21 - 0x14.23 */
	/* access: RO */
	u_int8_t lane7_physical_rx;
	/* Description - Number of common PLLs mapped to port for tx lanes. */
	/* 0x14.24 - 0x14.26 */
	/* access: RO */
	u_int8_t pll_cnt_tx;
	/* Description - largest VL number of the port.
for e.g if vl_num = 3
VL<0-3>_lane_map are only valid */
	/* 0x14.27 - 0x14.31 */
	/* access: RO */
	u_int8_t vl_num;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.0 - 0x18.2 */
	/* access: RO */
	u_int8_t lane0_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.3 - 0x18.5 */
	/* access: RO */
	u_int8_t lane1_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.6 - 0x18.8 */
	/* access: RO */
	u_int8_t lane2_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.9 - 0x18.11 */
	/* access: RO */
	u_int8_t lane3_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.12 - 0x18.14 */
	/* access: RO */
	u_int8_t lane4_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.15 - 0x18.17 */
	/* access: RO */
	u_int8_t lane5_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.18 - 0x18.20 */
	/* access: RO */
	u_int8_t lane6_physical_tx;
	/* Description - LSB [2:0] bits for logical lane<i> to physical tx lane mapping */
	/* 0x18.21 - 0x18.23 */
	/* access: RO */
	u_int8_t lane7_physical_tx;
	/* Description - minimal index of pll group of pll that port uses for tx lanes.
For all common pll's that are mapped to the port: [pll_index, pll_index+ 1, ... pll_index + pll_cnt] */
	/* 0x18.24 - 0x18.31 */
	/* access: RO */
	u_int8_t pll_index;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.0 - 0x1c.3 */
	/* access: RO */
	u_int8_t VL0_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.4 - 0x1c.7 */
	/* access: RO */
	u_int8_t VL1_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.8 - 0x1c.11 */
	/* access: RO */
	u_int8_t VL2_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.12 - 0x1c.15 */
	/* access: RO */
	u_int8_t VL3_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.16 - 0x1c.19 */
	/* access: RO */
	u_int8_t VL4_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.20 - 0x1c.23 */
	/* access: RO */
	u_int8_t VL5_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.24 - 0x1c.27 */
	/* access: RO */
	u_int8_t VL6_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x1c.28 - 0x1c.31 */
	/* access: RO */
	u_int8_t VL7_lane_map;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.0 - 0x20.3 */
	/* access: RO */
	u_int8_t VL8_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.4 - 0x20.7 */
	/* access: RO */
	u_int8_t VL9_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.8 - 0x20.11 */
	/* access: RO */
	u_int8_t VL10_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.12 - 0x20.15 */
	/* access: RO */
	u_int8_t VL11_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.16 - 0x20.19 */
	/* access: RO */
	u_int8_t VL12_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.20 - 0x20.23 */
	/* access: RO */
	u_int8_t VL13_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.24 - 0x20.27 */
	/* access: RO */
	u_int8_t VL14_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x20.28 - 0x20.31 */
	/* access: RO */
	u_int8_t VL15_lane_map;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.0 - 0x24.3 */
	/* access: RO */
	u_int8_t VL16_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.4 - 0x24.7 */
	/* access: RO */
	u_int8_t VL17_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.8 - 0x24.11 */
	/* access: RO */
	u_int8_t VL18_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.12 - 0x24.15 */
	/* access: RO */
	u_int8_t VL19_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.16 - 0x24.19 */
	/* access: RO */
	u_int8_t VL20_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.20 - 0x24.23 */
	/* access: RO */
	u_int8_t VL21_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.24 - 0x24.27 */
	/* access: RO */
	u_int8_t VL22_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x24.28 - 0x24.31 */
	/* access: RO */
	u_int8_t VL23_lane_map;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.0 - 0x28.3 */
	/* access: RO */
	u_int8_t VL24_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.4 - 0x28.7 */
	/* access: RO */
	u_int8_t VL25_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.8 - 0x28.11 */
	/* access: RO */
	u_int8_t VL26_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.12 - 0x28.15 */
	/* access: RO */
	u_int8_t VL27_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.16 - 0x28.19 */
	/* access: RO */
	u_int8_t VL28_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.20 - 0x28.23 */
	/* access: RO */
	u_int8_t VL29_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.24 - 0x28.27 */
	/* access: RO */
	u_int8_t VL30_lane_map;
	/* Description - logical lane number that maps to VL_x lane */
	/* 0x28.28 - 0x28.31 */
	/* access: RO */
	u_int8_t VL31_lane_map;
/*---------------- DWORD[15] (Offset 0x3c) ----------------*/
	/* Description - Indicates start offset of rx_lane, tx_lane inside the modules lanes in 8x granularity. relevant for modules with more than 8 lanes. such as OE.
0: lanes_0-7
1: lanes_8_15
2: lanes_16_23
3: lanes_24_31 */
	/* 0x3c.28 - 0x3c.31 */
	/* access: RO */
	u_int8_t sub_module;
/*---------------- DWORD[16] (Offset 0x40) ----------------*/
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.0 - 0x40.3 */
	/* access: RO */
	u_int8_t oe_lane7_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.4 - 0x40.7 */
	/* access: RO */
	u_int8_t oe_lane6_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.8 - 0x40.11 */
	/* access: RO */
	u_int8_t oe_lane5_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.12 - 0x40.15 */
	/* access: RO */
	u_int8_t oe_lane4_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.16 - 0x40.19 */
	/* access: RO */
	u_int8_t oe_lane3_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.20 - 0x40.23 */
	/* access: RO */
	u_int8_t oe_lane2_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.24 - 0x40.27 */
	/* access: RO */
	u_int8_t oe_lane1_to_els_logical_laser;
	/* Description - OE optical lane to ELS logical laser mapping */
	/* 0x40.28 - 0x40.31 */
	/* access: RO */
	u_int8_t oe_lane0_to_els_logical_laser;
/*---------------- DWORD[17] (Offset 0x44) ----------------*/
	/* Description - ELS module index */
	/* 0x44.0 - 0x44.7 */
	/* access: RO */
	u_int8_t els_module_index;
	/* Description - ELS label index */
	/* 0x44.10 - 0x44.15 */
	/* access: RO */
	u_int8_t els_index;
	/* Description - Optical engine MCU index */
	/* 0x44.24 - 0x44.30 */
	/* access: RO */
	u_int8_t oe_mcu_index;
	/* Description - CPO indication:
0 - not CPO
1 - CPO
	*/
	/* 0x44.31 - 0x44.31 */
	/* access: RO */
	u_int8_t cpo_indication;
};

/* Description -   */
/* Size in bytes - 64 */
struct reg_access_switch_pmlp_reg_ext {
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
	struct reg_access_switch_lane_2_module_mapping_ext lane_module_mapping[8];
};

/* Description -   */
/* Size in bytes - 1040 */
union reg_access_switch_reg_access_switch_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mspmer_ext mspmer_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mddq_ext mddq_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_pmaos_reg_ext pmaos_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x40c.31 */
	/* access: RW */
	struct reg_access_switch_icsr_ext icsr_ext;
	/* Description -  */
	/* 0x0.0 - 0x8c.31 */
	/* access: RW */
	struct reg_access_switch_mmta_reg_ext mmta_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x44.31 */
	/* access: RW */
	struct reg_access_switch_pmdr_reg_ext pmdr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_switch_icam_reg_ext icam_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mdsr_reg_ext mdsr_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x14.31 */
	/* access: RW */
	struct reg_access_switch_pllp_reg_ext pllp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x18.31 */
	/* access: RW */
	struct reg_access_switch_mfmc_reg_ext mfmc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x10c.31 */
	/* access: RW */
	struct reg_access_switch_mddt_reg_ext mddt_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x9c.31 */
	/* access: RW */
	struct reg_access_switch_mgpir_ext mgpir_ext;
	/* Description -  */
	/* 0x0.0 - 0x7c.31 */
	/* access: RW */
	struct reg_access_switch_msgi_ext msgi_ext;
	/* Description -  */
	/* 0x0.0 - 0x2c.31 */
	/* access: RW */
	struct reg_access_switch_mpein_reg_ext mpein_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x3c.31 */
	/* access: RW */
	struct reg_access_switch_pmlp_reg_ext pmlp_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_mpir_ext mpir_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_plib_reg_ext plib_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x5c.31 */
	/* access: RW */
	struct reg_access_switch_pguid_reg_ext pguid_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x28.31 */
	/* access: RW */
	struct reg_access_switch_mkdc_reg_ext mkdc_reg_ext;
	/* Description -  */
	/* 0x0.0 - 0x4.31 */
	/* access: RW */
	struct reg_access_switch_mrsr_ext mrsr_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_MMAM_ext MMAM_ext;
	/* Description -  */
	/* 0x0.0 - 0xc.31 */
	/* access: RW */
	struct reg_access_switch_PPCR_ext PPCR_ext;
	/* Description -  */
	/* 0x0.0 - 0x6c.31 */
	/* access: RW */
	struct reg_access_switch_mtcq_reg_ext mtcq_reg_ext;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* command_payload_ext */
void reg_access_switch_command_payload_ext_pack(const struct reg_access_switch_command_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_command_payload_ext_unpack(struct reg_access_switch_command_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_command_payload_ext_print(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_command_payload_ext_size(void);
#define REG_ACCESS_SWITCH_COMMAND_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_command_payload_ext_dump(const struct reg_access_switch_command_payload_ext *ptr_struct, FILE *fd);
/* crspace_access_payload_ext */
void reg_access_switch_crspace_access_payload_ext_pack(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_crspace_access_payload_ext_unpack(struct reg_access_switch_crspace_access_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_crspace_access_payload_ext_print(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_crspace_access_payload_ext_size(void);
#define REG_ACCESS_SWITCH_CRSPACE_ACCESS_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_crspace_access_payload_ext_dump(const struct reg_access_switch_crspace_access_payload_ext *ptr_struct, FILE *fd);
/* mddq_device_info_ext */
void reg_access_switch_mddq_device_info_ext_pack(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_device_info_ext_unpack(struct reg_access_switch_mddq_device_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_device_info_ext_print(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_device_info_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_DEVICE_INFO_EXT_SIZE    (0x20)
void reg_access_switch_mddq_device_info_ext_dump(const struct reg_access_switch_mddq_device_info_ext *ptr_struct, FILE *fd);
/* mddq_slot_info_ext */
void reg_access_switch_mddq_slot_info_ext_pack(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_info_ext_unpack(struct reg_access_switch_mddq_slot_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_info_ext_print(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_slot_info_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_SLOT_INFO_EXT_SIZE    (0x20)
void reg_access_switch_mddq_slot_info_ext_dump(const struct reg_access_switch_mddq_slot_info_ext *ptr_struct, FILE *fd);
/* mddq_slot_name_ext */
void reg_access_switch_mddq_slot_name_ext_pack(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_name_ext_unpack(struct reg_access_switch_mddq_slot_name_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_slot_name_ext_print(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_slot_name_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_SLOT_NAME_EXT_SIZE    (0x20)
void reg_access_switch_mddq_slot_name_ext_dump(const struct reg_access_switch_mddq_slot_name_ext *ptr_struct, FILE *fd);
/* prm_register_payload_ext */
void reg_access_switch_prm_register_payload_ext_pack(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_prm_register_payload_ext_unpack(struct reg_access_switch_prm_register_payload_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_prm_register_payload_ext_print(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_prm_register_payload_ext_size(void);
#define REG_ACCESS_SWITCH_PRM_REGISTER_PAYLOAD_EXT_SIZE    (0x104)
void reg_access_switch_prm_register_payload_ext_dump(const struct reg_access_switch_prm_register_payload_ext *ptr_struct, FILE *fd);
/* lane_2_module_mapping_ext */
void reg_access_switch_lane_2_module_mapping_ext_pack(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_lane_2_module_mapping_ext_unpack(struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_lane_2_module_mapping_ext_print(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_lane_2_module_mapping_ext_size(void);
#define REG_ACCESS_SWITCH_LANE_2_MODULE_MAPPING_EXT_SIZE    (0x4)
void reg_access_switch_lane_2_module_mapping_ext_dump(const struct reg_access_switch_lane_2_module_mapping_ext *ptr_struct, FILE *fd);
/* mddq_data_auto_ext */
void reg_access_switch_mddq_data_auto_ext_pack(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_data_auto_ext_unpack(union reg_access_switch_mddq_data_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_data_auto_ext_print(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_data_auto_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_DATA_AUTO_EXT_SIZE    (0x20)
void reg_access_switch_mddq_data_auto_ext_dump(const union reg_access_switch_mddq_data_auto_ext *ptr_struct, FILE *fd);
/* mddt_reg_payload_auto_ext */
void reg_access_switch_mddt_reg_payload_auto_ext_pack(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_payload_auto_ext_unpack(union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_payload_auto_ext_print(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddt_reg_payload_auto_ext_size(void);
#define REG_ACCESS_SWITCH_MDDT_REG_PAYLOAD_AUTO_EXT_SIZE    (0x104)
void reg_access_switch_mddt_reg_payload_auto_ext_dump(const union reg_access_switch_mddt_reg_payload_auto_ext *ptr_struct, FILE *fd);
/* mgpir_hw_info_ext */
void reg_access_switch_mgpir_hw_info_ext_pack(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mgpir_hw_info_ext_unpack(struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mgpir_hw_info_ext_print(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mgpir_hw_info_ext_size(void);
#define REG_ACCESS_SWITCH_MGPIR_HW_INFO_EXT_SIZE    (0x20)
void reg_access_switch_mgpir_hw_info_ext_dump(const struct reg_access_switch_mgpir_hw_info_ext *ptr_struct, FILE *fd);
/* mmta_tec_power_ext */
void reg_access_switch_mmta_tec_power_ext_pack(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mmta_tec_power_ext_unpack(struct reg_access_switch_mmta_tec_power_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mmta_tec_power_ext_print(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mmta_tec_power_ext_size(void);
#define REG_ACCESS_SWITCH_MMTA_TEC_POWER_EXT_SIZE    (0x20)
void reg_access_switch_mmta_tec_power_ext_dump(const struct reg_access_switch_mmta_tec_power_ext *ptr_struct, FILE *fd);
/* mmta_temprature_ext */
void reg_access_switch_mmta_temprature_ext_pack(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mmta_temprature_ext_unpack(struct reg_access_switch_mmta_temprature_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mmta_temprature_ext_print(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mmta_temprature_ext_size(void);
#define REG_ACCESS_SWITCH_MMTA_TEMPRATURE_EXT_SIZE    (0x18)
void reg_access_switch_mmta_temprature_ext_dump(const struct reg_access_switch_mmta_temprature_ext *ptr_struct, FILE *fd);
/* uint64 */
void reg_access_switch_uint64_pack(const u_int64_t *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_uint64_unpack(u_int64_t *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_uint64_print(const u_int64_t *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_uint64_size(void);
#define REG_ACCESS_SWITCH_UINT64_SIZE    (0x8)
void reg_access_switch_uint64_dump(const u_int64_t *ptr_struct, FILE *fd);
/* MMAM_ext */
void reg_access_switch_MMAM_ext_pack(const struct reg_access_switch_MMAM_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_MMAM_ext_unpack(struct reg_access_switch_MMAM_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_MMAM_ext_print(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_MMAM_ext_size(void);
#define REG_ACCESS_SWITCH_MMAM_EXT_SIZE    (0x10)
void reg_access_switch_MMAM_ext_dump(const struct reg_access_switch_MMAM_ext *ptr_struct, FILE *fd);
/* PPCR_ext */
void reg_access_switch_PPCR_ext_pack(const struct reg_access_switch_PPCR_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_PPCR_ext_unpack(struct reg_access_switch_PPCR_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_PPCR_ext_print(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_PPCR_ext_size(void);
#define REG_ACCESS_SWITCH_PPCR_EXT_SIZE    (0x10)
void reg_access_switch_PPCR_ext_dump(const struct reg_access_switch_PPCR_ext *ptr_struct, FILE *fd);
/* icam_reg_ext */
void reg_access_switch_icam_reg_ext_pack(const struct reg_access_switch_icam_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_icam_reg_ext_unpack(struct reg_access_switch_icam_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_icam_reg_ext_print(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_icam_reg_ext_size(void);
#define REG_ACCESS_SWITCH_ICAM_REG_EXT_SIZE    (0x18)
void reg_access_switch_icam_reg_ext_dump(const struct reg_access_switch_icam_reg_ext *ptr_struct, FILE *fd);
/* icsr_ext */
void reg_access_switch_icsr_ext_pack(const struct reg_access_switch_icsr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_icsr_ext_unpack(struct reg_access_switch_icsr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_icsr_ext_print(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_icsr_ext_size(void);
#define REG_ACCESS_SWITCH_ICSR_EXT_SIZE    (0x410)
void reg_access_switch_icsr_ext_dump(const struct reg_access_switch_icsr_ext *ptr_struct, FILE *fd);
/* mddq_ext */
void reg_access_switch_mddq_ext_pack(const struct reg_access_switch_mddq_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddq_ext_unpack(struct reg_access_switch_mddq_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddq_ext_print(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddq_ext_size(void);
#define REG_ACCESS_SWITCH_MDDQ_EXT_SIZE    (0x30)
void reg_access_switch_mddq_ext_dump(const struct reg_access_switch_mddq_ext *ptr_struct, FILE *fd);
/* mddt_reg_ext */
void reg_access_switch_mddt_reg_ext_pack(const struct reg_access_switch_mddt_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_ext_unpack(struct reg_access_switch_mddt_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mddt_reg_ext_print(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mddt_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MDDT_REG_EXT_SIZE    (0x110)
void reg_access_switch_mddt_reg_ext_dump(const struct reg_access_switch_mddt_reg_ext *ptr_struct, FILE *fd);
/* mdsr_reg_ext */
void reg_access_switch_mdsr_reg_ext_pack(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mdsr_reg_ext_unpack(struct reg_access_switch_mdsr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mdsr_reg_ext_print(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mdsr_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MDSR_REG_EXT_SIZE    (0x30)
void reg_access_switch_mdsr_reg_ext_dump(const struct reg_access_switch_mdsr_reg_ext *ptr_struct, FILE *fd);
/* mfmc_reg_ext */
void reg_access_switch_mfmc_reg_ext_pack(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mfmc_reg_ext_unpack(struct reg_access_switch_mfmc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mfmc_reg_ext_print(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mfmc_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MFMC_REG_EXT_SIZE    (0x1c)
void reg_access_switch_mfmc_reg_ext_dump(const struct reg_access_switch_mfmc_reg_ext *ptr_struct, FILE *fd);
/* mgpir_ext */
void reg_access_switch_mgpir_ext_pack(const struct reg_access_switch_mgpir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mgpir_ext_unpack(struct reg_access_switch_mgpir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mgpir_ext_print(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mgpir_ext_size(void);
#define REG_ACCESS_SWITCH_MGPIR_EXT_SIZE    (0xa0)
void reg_access_switch_mgpir_ext_dump(const struct reg_access_switch_mgpir_ext *ptr_struct, FILE *fd);
/* mkdc_reg_ext */
void reg_access_switch_mkdc_reg_ext_pack(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mkdc_reg_ext_unpack(struct reg_access_switch_mkdc_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mkdc_reg_ext_print(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mkdc_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MKDC_REG_EXT_SIZE    (0x2c)
void reg_access_switch_mkdc_reg_ext_dump(const struct reg_access_switch_mkdc_reg_ext *ptr_struct, FILE *fd);
/* mmta_reg_ext */
void reg_access_switch_mmta_reg_ext_pack(const struct reg_access_switch_mmta_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mmta_reg_ext_unpack(struct reg_access_switch_mmta_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mmta_reg_ext_print(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mmta_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MMTA_REG_EXT_SIZE    (0x90)
void reg_access_switch_mmta_reg_ext_dump(const struct reg_access_switch_mmta_reg_ext *ptr_struct, FILE *fd);
/* mpein_reg_ext */
void reg_access_switch_mpein_reg_ext_pack(const struct reg_access_switch_mpein_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mpein_reg_ext_unpack(struct reg_access_switch_mpein_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mpein_reg_ext_print(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mpein_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MPEIN_REG_EXT_SIZE    (0x30)
void reg_access_switch_mpein_reg_ext_dump(const struct reg_access_switch_mpein_reg_ext *ptr_struct, FILE *fd);
/* mpir_ext */
void reg_access_switch_mpir_ext_pack(const struct reg_access_switch_mpir_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mpir_ext_unpack(struct reg_access_switch_mpir_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mpir_ext_print(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mpir_ext_size(void);
#define REG_ACCESS_SWITCH_MPIR_EXT_SIZE    (0x10)
void reg_access_switch_mpir_ext_dump(const struct reg_access_switch_mpir_ext *ptr_struct, FILE *fd);
/* mrsr_ext */
void reg_access_switch_mrsr_ext_pack(const struct reg_access_switch_mrsr_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mrsr_ext_unpack(struct reg_access_switch_mrsr_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mrsr_ext_print(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mrsr_ext_size(void);
#define REG_ACCESS_SWITCH_MRSR_EXT_SIZE    (0x8)
void reg_access_switch_mrsr_ext_dump(const struct reg_access_switch_mrsr_ext *ptr_struct, FILE *fd);
/* msgi_ext */
void reg_access_switch_msgi_ext_pack(const struct reg_access_switch_msgi_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_msgi_ext_unpack(struct reg_access_switch_msgi_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_msgi_ext_print(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_msgi_ext_size(void);
#define REG_ACCESS_SWITCH_MSGI_EXT_SIZE    (0x80)
void reg_access_switch_msgi_ext_dump(const struct reg_access_switch_msgi_ext *ptr_struct, FILE *fd);
/* mspmer_ext */
void reg_access_switch_mspmer_ext_pack(const struct reg_access_switch_mspmer_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mspmer_ext_unpack(struct reg_access_switch_mspmer_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mspmer_ext_print(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mspmer_ext_size(void);
#define REG_ACCESS_SWITCH_MSPMER_EXT_SIZE    (0x30)
void reg_access_switch_mspmer_ext_dump(const struct reg_access_switch_mspmer_ext *ptr_struct, FILE *fd);
/* mtcq_reg_ext */
void reg_access_switch_mtcq_reg_ext_pack(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_mtcq_reg_ext_unpack(struct reg_access_switch_mtcq_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_mtcq_reg_ext_print(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_mtcq_reg_ext_size(void);
#define REG_ACCESS_SWITCH_MTCQ_REG_EXT_SIZE    (0x70)
void reg_access_switch_mtcq_reg_ext_dump(const struct reg_access_switch_mtcq_reg_ext *ptr_struct, FILE *fd);
/* pguid_reg_ext */
void reg_access_switch_pguid_reg_ext_pack(const struct reg_access_switch_pguid_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pguid_reg_ext_unpack(struct reg_access_switch_pguid_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pguid_reg_ext_print(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pguid_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PGUID_REG_EXT_SIZE    (0x60)
void reg_access_switch_pguid_reg_ext_dump(const struct reg_access_switch_pguid_reg_ext *ptr_struct, FILE *fd);
/* plib_reg_ext */
void reg_access_switch_plib_reg_ext_pack(const struct reg_access_switch_plib_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_plib_reg_ext_unpack(struct reg_access_switch_plib_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_plib_reg_ext_print(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_plib_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PLIB_REG_EXT_SIZE    (0x10)
void reg_access_switch_plib_reg_ext_dump(const struct reg_access_switch_plib_reg_ext *ptr_struct, FILE *fd);
/* pllp_reg_ext */
void reg_access_switch_pllp_reg_ext_pack(const struct reg_access_switch_pllp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pllp_reg_ext_unpack(struct reg_access_switch_pllp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pllp_reg_ext_print(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pllp_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PLLP_REG_EXT_SIZE    (0x18)
void reg_access_switch_pllp_reg_ext_dump(const struct reg_access_switch_pllp_reg_ext *ptr_struct, FILE *fd);
/* pmaos_reg_ext */
void reg_access_switch_pmaos_reg_ext_pack(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pmaos_reg_ext_unpack(struct reg_access_switch_pmaos_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pmaos_reg_ext_print(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pmaos_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PMAOS_REG_EXT_SIZE    (0x10)
void reg_access_switch_pmaos_reg_ext_dump(const struct reg_access_switch_pmaos_reg_ext *ptr_struct, FILE *fd);
/* pmdr_reg_ext */
void reg_access_switch_pmdr_reg_ext_pack(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pmdr_reg_ext_unpack(struct reg_access_switch_pmdr_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pmdr_reg_ext_print(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pmdr_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PMDR_REG_EXT_SIZE    (0x48)
void reg_access_switch_pmdr_reg_ext_dump(const struct reg_access_switch_pmdr_reg_ext *ptr_struct, FILE *fd);
/* pmlp_reg_ext */
void reg_access_switch_pmlp_reg_ext_pack(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_pmlp_reg_ext_unpack(struct reg_access_switch_pmlp_reg_ext *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_pmlp_reg_ext_print(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_pmlp_reg_ext_size(void);
#define REG_ACCESS_SWITCH_PMLP_REG_EXT_SIZE    (0x40)
void reg_access_switch_pmlp_reg_ext_dump(const struct reg_access_switch_pmlp_reg_ext *ptr_struct, FILE *fd);
/* reg_access_switch_Nodes */
void reg_access_switch_reg_access_switch_Nodes_pack(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, u_int8_t *ptr_buff);
void reg_access_switch_reg_access_switch_Nodes_unpack(union reg_access_switch_reg_access_switch_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void reg_access_switch_reg_access_switch_Nodes_print(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int reg_access_switch_reg_access_switch_Nodes_size(void);
#define REG_ACCESS_SWITCH_REG_ACCESS_SWITCH_NODES_SIZE    (0x410)
void reg_access_switch_reg_access_switch_Nodes_dump(const union reg_access_switch_reg_access_switch_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // REG_ACCESS_SWITCH_LAYOUTS_H
