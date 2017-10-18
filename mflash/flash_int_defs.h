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


#ifndef USER_MFLASH_FLASH_INT_DEFS_H_
#define USER_MFLASH_FLASH_INT_DEFS_H_

////////////////////////////////////////
//
// ST SPI functions - common for InfiniHostIIILx and ConnectX
//
////////////////////////////////////////
enum StFlashCommand {
    SFC_SE    = 0xD8,
    SFC_SSE   = 0x20,
    SFC_PP    = 0x02,
    SFC_RDSR  = 0x05,
    SFC_WRSR2 = 0x31,
    SFC_RDSR2 = 0x35,
    SFC_WREN  = 0x06,
    SFC_READ  = 0x03,
    SFC_FAST_READ  = 0x3B,
    SFC_QUAD_READ  = 0x3B,
    SFC_RES   = 0xAB,
    SFC_JEDEC = 0x9F,
    SFC_RDNVR = 0xB5,
    SFC_RDCR  = 0x15,
    SFC_WRNVR = 0xB1,
    SFC_WRSR  = 0x01,
    SFC_RDFR  = 0x48,
    SFC_WRFR  = 0x42
};

#define SST_FLASH_NAME   "SST25VFxx"
#define WINBOND_NAME     "W25QxxBV"
#define WINBOND_W25X     "W25Xxx"
#define WINBOND_3V_NAME  "W25QxxxJV"
#define ATMEL_NAME       "AT25DFxxx"
#define S25FLXXXP_NAME   "S25FLXXXP"
#define S25FL116K_NAME   "S25FL11xx"
#define MACRONIX_NAME    "MX25L16xxx"
#define MACRONIX_3V_NAME "MX25Lxxx45G"
#define CYPRESS_3V_NAME  "S25FLxxxL"
#define ISSI_3V_NAME     "IS25LPxxx"

typedef enum flash_vendor {
    FV_ST      = 0x20,
    FV_SST     = 0xbf,
    FV_WINBOND = 0xef,
    FV_ATMEL   = 0x1f,
    FV_S25FLXXXX = 0x01,
    FV_MX25K16XXX = 0xc2,
    FV_IS25LPXXX = 0x9d
} flash_vendor_t;

typedef enum flash_memory_type {
    FMT_ST_M25P  = 0x20,
    FMT_MX25K16XXX = 0x20,
    FMT_ST_M25PX = 0x71,
    FMT_SST_25   = 0x25,
    FMT_WINBOND  = 0x40,
    FMT_WINBOND_W25X = 0x30,
    FMT_WINBOND_3V = 0x70,
    FMT_ATMEL    = 0x2,
    FMT_N25QXXX  = 0xba,
    FMT_S25FLXXXP = 0x02,
    FMT_S25FL116K = 0x40,
    FMT_S25FLXXXL = 0x60,
    FMT_MT25QLXXXABA = 0xba,
    FMT_IS25LPXXX = 0x60
} flash_memory_type_t;


#endif /* USER_MFLASH_FLASH_INT_DEFS_H_ */
