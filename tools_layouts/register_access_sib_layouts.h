/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 */
 

/***
         *** This file was generated at "2019-03-23 21:38:49"
         *** by:
         ***    > /mswg/release/tools/a-me/last_stable/adabe_plugins/adb2c/adb2pack.py --input adb/register_access/register_access_sib.adb --file-prefix register_access_sib --prefix register_access_sib_
         ***/
#ifndef REGISTER_ACCESS_SIB_LAYOUTS_H
#define REGISTER_ACCESS_SIB_LAYOUTS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "adb_to_c_utils.h"
/* Description -   */
/* Size in bytes - 16 */
struct register_access_sib_IB_PSID_ {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - PS - ID */
	/* 0x0.0 - 0xc.31 */
	u_int32_t PS_ID[4];
};

/* Description -  Development Info */
/* Size in bytes - 28 */
struct register_access_sib_IB_DEVInfo_ {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - FW version as string characters */
	/* 0x0.0 - 0x18.31 */
	u_int32_t dev_branch_tag[7];
};

/* Description -  FW Info */
/* Size in bytes - 64 */
struct register_access_sib_IB_FWInfo_ {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t SubMinor;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	u_int8_t Minor;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t Major;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description -  */
	/* 0x4.0 - 0x4.31 */
	u_int32_t BuildID;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description -  */
	/* 0x8.0 - 0x8.15 */
	u_int16_t Year;
	/* Description -  */
	/* 0x8.16 - 0x8.23 */
	u_int8_t Day;
	/* Description -  */
	/* 0x8.24 - 0x8.31 */
	u_int8_t Month;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description -  */
	/* 0xc.0 - 0xc.15 */
	u_int16_t Hour;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x1c.31 */
	struct register_access_sib_IB_PSID_ PSID;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x20.31 */
	u_int32_t INIFileNum;
/*---------------- DWORD[9] (Offset 0x24) ----------------*/
	/* Description -  */
	/* 0x24.0 - 0x24.31 */
	u_int32_t extended_major;
/*---------------- DWORD[10] (Offset 0x28) ----------------*/
	/* Description -  */
	/* 0x28.0 - 0x28.31 */
	u_int32_t extended_minor;
/*---------------- DWORD[11] (Offset 0x2c) ----------------*/
	/* Description -  */
	/* 0x2c.0 - 0x2c.31 */
	u_int32_t extended_subminor;
};

/* Description -  HW Info */
/* Size in bytes - 32 */
struct register_access_sib_IB_HWInfo_ {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.15 */
	u_int16_t DEVID;
	/* Description -  */
	/* 0x0.16 - 0x0.31 */
	u_int16_t REVID;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Maximum supported V_CORE voltage for the device. (in 50mV increments). */
	/* 0x4.0 - 0x4.4 */
	u_int8_t pvs;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - the device_id in HW, used by tools */
	/* 0x8.0 - 0x8.15 */
	u_int16_t hw_dev_id;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description - Time (in sec) since last reset */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t UpTime;
};

/* Description -  SW Info */
/* Size in bytes - 32 */
struct register_access_sib_IB_SWInfo_ {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x0.7 */
	u_int8_t VerSubMinor;
	/* Description -  */
	/* 0x0.8 - 0x0.15 */
	u_int8_t VerMinor;
	/* Description -  */
	/* 0x0.16 - 0x0.23 */
	u_int8_t VerMajor;
};

/* Description -   */
/* Size in bytes - 160 */
struct register_access_sib_mgir {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct register_access_sib_IB_HWInfo_ HWInfo;
/*---------------- DWORD[8] (Offset 0x20) ----------------*/
	/* Description -  */
	/* 0x20.0 - 0x5c.31 */
	struct register_access_sib_IB_FWInfo_ FWInfo;
/*---------------- DWORD[24] (Offset 0x60) ----------------*/
	/* Description -  */
	/* 0x60.0 - 0x7c.31 */
	struct register_access_sib_IB_SWInfo_ SWInfo;
/*---------------- DWORD[32] (Offset 0x80) ----------------*/
	/* Description -  */
	/* 0x80.0 - 0x98.31 */
	struct register_access_sib_IB_DEVInfo_ DEVInfo;
};

/* Description -   */
/* Size in bytes - 32 */
struct register_access_sib_mtmp {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Sensors index to access */
	/* 0x0.0 - 0x0.11 */
	u_int16_t sensor_index;
	/* Description - query the internal diodes */
	/* 0x0.31 - 0x0.31 */
	u_int8_t internal_diodes_query;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Temperature reading from the sensor. Reading in 0.125 Celsius degrees. */
	/* 0x4.0 - 0x4.15 */
	u_int16_t temperature;
	/* Description - Module Sensor Supported:; 0: The module is not connected, or the module sensor is not supported; 1: The module sensor is supported */
	/* 0x4.31 - 0x4.31 */
	u_int8_t mss;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
	/* Description - The highest measured temperature from the sensor. */
	/* 0x8.0 - 0x8.15 */
	u_int16_t max_temperture;
	/* Description - Max Temperature Reset - clears the value of the max temperature register */
	/* 0x8.30 - 0x8.30 */
	u_int8_t mtr;
	/* Description - Max Temperature Enable - enables measuring the max temperature on a sensor */
	/* 0x8.31 - 0x8.31 */
	u_int8_t mte;
/*---------------- DWORD[3] (Offset 0xc) ----------------*/
	/* Description - If the sensor temperature measurement is above the threshold (and events are enabled), an event
will be generated */
	/* 0xc.0 - 0xc.15 */
	u_int16_t temperature_threshold_hi;
	/* Description - Temperature Event Enable
00 - Do not generate event
01 - Generate Event
10 - Generate single event */
	/* 0xc.30 - 0xc.31 */
	u_int8_t tee;
/*---------------- DWORD[4] (Offset 0x10) ----------------*/
	/* Description -  */
	/* 0x10.0 - 0x10.15 */
	u_int16_t temperature_threshold_lo;
/*---------------- DWORD[6] (Offset 0x18) ----------------*/
	/* Description -  */
	/* 0x18.0 - 0x18.31 */
	u_int32_t name_hi;
/*---------------- DWORD[7] (Offset 0x1c) ----------------*/
	/* Description -  */
	/* 0x1c.0 - 0x1c.31 */
	u_int32_t name_lo;
};

/* Description -   */
/* Size in bytes - 12 */
struct register_access_sib_pmaos {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description - Port operational state
0001 - up
0010 - down */
	/* 0x0.0 - 0x0.3 */
	u_int8_t oper_status;
	/* Description - Port administrative state (the desired state of the interface)
0001 - up
0010 - down by configuration (default) */
	/* 0x0.8 - 0x0.11 */
	u_int8_t admin_status;
	/* Description - Local port number */
	/* 0x0.16 - 0x0.23 */
	u_int8_t module;
	/* Description - Module Reset toggle */
	/* 0x0.31 - 0x0.31 */
	u_int8_t rst;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
	/* Description - Event Generation on operational state change
00 - Do not generate event
01 - Generate Unacknowledged Event 
10 - Generate Acknowledged Event */
	/* 0x4.0 - 0x4.1 */
	u_int8_t e;
	/* Description - module error type. valid only when oper_status=0011 */
	/* 0x4.8 - 0x4.11 */
	u_int8_t error_type;
	/* Description - Event Update Enable. If this bit is set, Event Generation will be 
updated based on the e field. Only relevant on Set operations */
	/* 0x4.30 - 0x4.30 */
	u_int8_t ee;
	/* Description - Admin State Update Enable. If this bit is set, Admin State will be 
updated based on admin_state field. Only relevant on Set operations */
	/* 0x4.31 - 0x4.31 */
	u_int8_t ase;
};

/* Description -   */
/* Size in bytes - 160 */
union register_access_sib_register_access_sib_Nodes {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
	/* Description -  */
	/* 0x0.0 - 0x1c.31 */
	struct register_access_sib_mtmp mtmp;
	/* Description -  */
	/* 0x0.0 - 0x8.31 */
	struct register_access_sib_pmaos pmaos;
	/* Description -  */
	/* 0x0.0 - 0x9c.31 */
	struct register_access_sib_mgir mgir;
};


/*================= PACK/UNPACK/PRINT FUNCTIONS ======================*/
/* IB_PSID_ */
void register_access_sib_IB_PSID__pack(const struct register_access_sib_IB_PSID_ *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_IB_PSID__unpack(struct register_access_sib_IB_PSID_ *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_IB_PSID__print(const struct register_access_sib_IB_PSID_ *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_IB_PSID__size(void);
#define REGISTER_ACCESS_SIB_IB_PSID__SIZE    (0x10)
void register_access_sib_IB_PSID__dump(const struct register_access_sib_IB_PSID_ *ptr_struct, FILE *fd);
/* IB_DEVInfo_ */
void register_access_sib_IB_DEVInfo__pack(const struct register_access_sib_IB_DEVInfo_ *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_IB_DEVInfo__unpack(struct register_access_sib_IB_DEVInfo_ *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_IB_DEVInfo__print(const struct register_access_sib_IB_DEVInfo_ *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_IB_DEVInfo__size(void);
#define REGISTER_ACCESS_SIB_IB_DEVINFO__SIZE    (0x1c)
void register_access_sib_IB_DEVInfo__dump(const struct register_access_sib_IB_DEVInfo_ *ptr_struct, FILE *fd);
/* IB_FWInfo_ */
void register_access_sib_IB_FWInfo__pack(const struct register_access_sib_IB_FWInfo_ *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_IB_FWInfo__unpack(struct register_access_sib_IB_FWInfo_ *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_IB_FWInfo__print(const struct register_access_sib_IB_FWInfo_ *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_IB_FWInfo__size(void);
#define REGISTER_ACCESS_SIB_IB_FWINFO__SIZE    (0x40)
void register_access_sib_IB_FWInfo__dump(const struct register_access_sib_IB_FWInfo_ *ptr_struct, FILE *fd);
/* IB_HWInfo_ */
void register_access_sib_IB_HWInfo__pack(const struct register_access_sib_IB_HWInfo_ *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_IB_HWInfo__unpack(struct register_access_sib_IB_HWInfo_ *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_IB_HWInfo__print(const struct register_access_sib_IB_HWInfo_ *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_IB_HWInfo__size(void);
#define REGISTER_ACCESS_SIB_IB_HWINFO__SIZE    (0x20)
void register_access_sib_IB_HWInfo__dump(const struct register_access_sib_IB_HWInfo_ *ptr_struct, FILE *fd);
/* IB_SWInfo_ */
void register_access_sib_IB_SWInfo__pack(const struct register_access_sib_IB_SWInfo_ *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_IB_SWInfo__unpack(struct register_access_sib_IB_SWInfo_ *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_IB_SWInfo__print(const struct register_access_sib_IB_SWInfo_ *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_IB_SWInfo__size(void);
#define REGISTER_ACCESS_SIB_IB_SWINFO__SIZE    (0x20)
void register_access_sib_IB_SWInfo__dump(const struct register_access_sib_IB_SWInfo_ *ptr_struct, FILE *fd);
/* mgir */
void register_access_sib_mgir_pack(const struct register_access_sib_mgir *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_mgir_unpack(struct register_access_sib_mgir *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_mgir_print(const struct register_access_sib_mgir *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_mgir_size(void);
#define REGISTER_ACCESS_SIB_MGIR_SIZE    (0xa0)
void register_access_sib_mgir_dump(const struct register_access_sib_mgir *ptr_struct, FILE *fd);
/* mtmp */
void register_access_sib_mtmp_pack(const struct register_access_sib_mtmp *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_mtmp_unpack(struct register_access_sib_mtmp *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_mtmp_print(const struct register_access_sib_mtmp *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_mtmp_size(void);
#define REGISTER_ACCESS_SIB_MTMP_SIZE    (0x20)
void register_access_sib_mtmp_dump(const struct register_access_sib_mtmp *ptr_struct, FILE *fd);
/* pmaos */
void register_access_sib_pmaos_pack(const struct register_access_sib_pmaos *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_pmaos_unpack(struct register_access_sib_pmaos *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_pmaos_print(const struct register_access_sib_pmaos *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_pmaos_size(void);
#define REGISTER_ACCESS_SIB_PMAOS_SIZE    (0xc)
void register_access_sib_pmaos_dump(const struct register_access_sib_pmaos *ptr_struct, FILE *fd);
/* register_access_sib_Nodes */
void register_access_sib_register_access_sib_Nodes_pack(const union register_access_sib_register_access_sib_Nodes *ptr_struct, u_int8_t *ptr_buff);
void register_access_sib_register_access_sib_Nodes_unpack(union register_access_sib_register_access_sib_Nodes *ptr_struct, const u_int8_t *ptr_buff);
void register_access_sib_register_access_sib_Nodes_print(const union register_access_sib_register_access_sib_Nodes *ptr_struct, FILE *fd, int indent_level);
unsigned int register_access_sib_register_access_sib_Nodes_size(void);
#define REGISTER_ACCESS_SIB_REGISTER_ACCESS_SIB_NODES_SIZE    (0xa0)
void register_access_sib_register_access_sib_Nodes_dump(const union register_access_sib_register_access_sib_Nodes *ptr_struct, FILE *fd);


#ifdef __cplusplus
}
#endif

#endif // REGISTER_ACCESS_SIB_LAYOUTS_H
