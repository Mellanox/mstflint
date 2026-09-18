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


#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "compatibility.h"
#include "ibd_ibal_access.h"

#include <windows.h>
#include <winioctl.h>
#include <errno.h>

#include "bus_ioctl.h"

#include <iba/ib_types.h>
#include <iba/ib_al.h>
#ifndef WIN32
#include <complib/cl_device.h>
#endif
#include <vc.h>

#define INVALID_REG_ID 0xffffffff

typedef struct _buf {
	PVOID			ptr;
	ib_mr_handle_t 	h_mr;
	ULONG			lkey;
	ULONG			rkey;
} buf_t, *pbuf_t;


typedef struct ibal_sniffer_context {
   HANDLE     h_driver;
   u_int64_t  guid;
   ULONG      tx_reg_id;
   ULONG      rx_reg_id;
} ibal_sniffer_context_t;


static LONG open_driver(HANDLE *pHandle)
{
	DWORD errNum = 0;
    HANDLE hDevice = CreateFileW(APP_DEVICE_NAME,
                         GENERIC_READ | GENERIC_WRITE,
                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                         NULL,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         NULL);

    if(hDevice == INVALID_HANDLE_VALUE)
	{
        errNum = GetLastError();

        wprintf(L"CreateFile %s failed!  ERROR = %d\n", APP_DEVICE_NAME, errNum);
        return ERROR_GEN_FAILURE;
	}

	*pHandle = hDevice;
	return ERROR_SUCCESS;
}


static VOID close_driver(HANDLE hDevice)
{
	CloseHandle(hDevice);
}

static LONG open_sniffer(	HANDLE hDevice, ULONGLONG guid, ULONG port_num, ULONG qpn, SNIFFER_DIRECTION direction, ULONG *pRegId)
{
	BOOL  bRc;
	ULONG bytesReturned = 0;
	OPEN_SNIFFER_IN InputBuffer;
	OPEN_SNIFFER_OUT OutputBuffer;

	// fill input parameters
	InputBuffer.ca_guid = guid;
	InputBuffer.port_num = port_num;
	InputBuffer.qpn = qpn;
	InputBuffer.direction = direction;
	printf("Input: guid %I64x, port_num %d, direction %d, qpn %#x\n",
		InputBuffer.ca_guid, InputBuffer.port_num, InputBuffer.direction, InputBuffer.qpn );

	// send ioctl
	bRc = DeviceIoControl(hDevice,
						  IOCTL_OPEN_SNIFFER_BUFFERED,
						  (char*)&InputBuffer, sizeof(InputBuffer),
						  (char*)&OutputBuffer, sizeof(OutputBuffer),
						  &bytesReturned, NULL);

	// results
	if (!bRc) {
		fprintf(stderr, "open_sniffer: Error in DeviceIoControl: last error %#x\n", GetLastError());
		return ERROR_INVALID_PARAMETER;
	}

	// print results
	printf("Output: reg_id %#x\n", OutputBuffer.reg_id );
	*pRegId = OutputBuffer.reg_id;

	return ERROR_SUCCESS;
}


static void close_sniffer(HANDLE hDevice, ULONGLONG guid, ULONG reg_id)
{
	BOOL  bRc;
	ULONG bytesReturned = 0;
	CLOSE_SNIFFER_IN InputBuffer;

	// fill input parameters
	InputBuffer.ca_guid = guid;
	InputBuffer.reg_id = reg_id;
	printf("-D- Input: guid %I64x, reg_id %#x\n", InputBuffer.ca_guid, InputBuffer.reg_id );

	// send ioctl
	bRc = DeviceIoControl(hDevice,
						  IOCTL_CLOSE_SNIFFER_BUFFERED,
						  (char*)&InputBuffer, sizeof(InputBuffer),
						  NULL, 0,
						  &bytesReturned, NULL);

	// results
	if (!bRc) {
		fprintf(stderr, "-E- close_sniffer: Error in DeviceIoControl: last error %#x\n", GetLastError());
	}
}

int ibd_ibal_open_sniffer(u_int64_t node_guid,
                          int       ib_port,
                          u_int32_t qp_num,
                          int       tx,
                          int       rx,
                          void**    context)
{
    int rc;

    ibal_sniffer_context_t *ctx = malloc(sizeof(ibal_sniffer_context_t));
    if (NULL == ctx) {
        fprintf(stderr, "-E- Memory allocation failed\n");
        return 1;
    }

    memset(ctx, 0, sizeof(*ctx));
    ctx->rx_reg_id = INVALID_REG_ID;
    ctx->tx_reg_id = INVALID_REG_ID;
    ctx->h_driver  = INVALID_HANDLE_VALUE;

    rc = open_driver(&(ctx->h_driver));
    if (rc) {
        goto error_cleanup;
    }

    if (tx) {
        rc = open_sniffer(ctx->h_driver, node_guid, ib_port, qp_num, SNIFFER_DIR_SX, &ctx->tx_reg_id);
        if (rc) {
            goto error_cleanup;
        }
    }

    if (rx) {
        rc = open_sniffer(ctx->h_driver, node_guid, ib_port, qp_num, SNIFFER_DIR_RX, &ctx->rx_reg_id);
        if (rc) {
            goto error_cleanup;
        }
    }

error_cleanup:
    if (rc) {
        ibd_ibal_close_sniffer(ctx);
    } else {
        *context = ctx;
    }
    return rc;
}

int ibd_ibal_close_sniffer(void* context)
{
    ibal_sniffer_context_t* ctx = (ibal_sniffer_context_t*)context;
    if (ctx->rx_reg_id != INVALID_REG_ID) {
        close_sniffer(ctx->h_driver, ctx->guid, ctx->rx_reg_id);
    }

    if (ctx->tx_reg_id != INVALID_REG_ID) {
        close_sniffer(ctx->h_driver, ctx->guid, ctx->tx_reg_id);
    }

    if (ctx->h_driver != INVALID_HANDLE_VALUE) {
        close_driver(ctx->h_driver);
    }

    free(ctx);
    return 0;
}
