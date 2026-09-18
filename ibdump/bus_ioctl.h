/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#ifndef BUS_IOCTL_IN

#define DEVICE_NAME         L"\\Device\\MLX4BUSControl"
#define DOS_DEVICE_NAME     L"\\DosDevices\\MLX4BUSControl"
#define APP_DEVICE_NAME     L"\\\\.\\MLX4BUSControl"
#define APP_DOS_DEVICE_NAME L"MLX4BUSControl"

#define IOCTL_GETINFO_METHOD_BUFFERED \
            CTL_CODE( FILE_DEVICE_INFINIBAND, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS )

#define IOCTL_GETESWITCH_METHOD_BUFFERED \
            CTL_CODE( FILE_DEVICE_INFINIBAND, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS )

#define IOCTL_GET_RES_TRACK_METHOD_BUFFERED \
            CTL_CODE( FILE_DEVICE_INFINIBAND, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS )

#define IOCTL_GET_HCA_INFO_BUFFERED \
            CTL_CODE( FILE_DEVICE_INFINIBAND, 0x900, METHOD_BUFFERED, FILE_ANY_ACCESS )

#define IOCTL_OPEN_SNIFFER_BUFFERED \
            CTL_CODE( FILE_DEVICE_INFINIBAND, 0x901, METHOD_BUFFERED, FILE_ANY_ACCESS )

#define IOCTL_CLOSE_SNIFFER_BUFFERED \
            CTL_CODE( FILE_DEVICE_INFINIBAND, 0x902, METHOD_BUFFERED, FILE_ANY_ACCESS )

//
// Used in SetPCIDevice for WMI
//
typedef struct
        {
            UCHAR bus;
            UCHAR device;
            UCHAR function;
        } HCA_IDENTIFICATION;

#define PART_NUMBER_SIZE 100

//
// Used in SetPCIDevice for WMI
//
typedef struct
        {
            UINT64 firmwareVersion;
            UINT8  busType;
            UINT8  busSpeed;
            UINT8  busWidth;
            UCHAR  revisionId;
            USHORT deviceId;
            char   partNumber[PART_NUMBER_SIZE];
        } HCA_INFO;

//
// Used for configuring sniffing (IOCTL_OPEN_SNIFFER_BUFFERED, IOCTL_OPEN_SNIFFER_BUFFERED)
//
typedef enum
		{
			SNIFFER_DIR_SX = 1,
			SNIFFER_DIR_RX
			
		} SNIFFER_DIRECTION;

typedef struct
        {
            UINT64 ca_guid;		// HCA guid
            UINT32 port_num;	// 1 or 2
            UINT32 qpn;			// sniffering QP
            SNIFFER_DIRECTION direction;	// SNIFFER_DIR_SX/SNIFFER_DIR_RX
            
        } OPEN_SNIFFER_IN;

typedef struct
        {
            UINT32 reg_id;		// registration id 
            
        } OPEN_SNIFFER_OUT;

typedef struct
        {
            UINT64 ca_guid;		// HCA guid
            UINT32 reg_id;		// registration id 
            
        } CLOSE_SNIFFER_IN;

#endif
