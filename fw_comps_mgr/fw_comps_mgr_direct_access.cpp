/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
/*
 * fw_comps_mgr_direct_access.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: eddy
 */

#include "fw_comps_mgr_direct_access.h"

#ifndef UEFI_BUILD
#include <mft_sig_handler.h>
#else
// no signal handling.
static void mft_signal_set_handling(int isOn)
{
    return;
}
#endif

typedef struct reg_access_hca_mcda_reg mcdaReg;

bool DirectComponentAccess::accessComponent(u_int32_t updateHandle, u_int32_t offset,
    u_int32_t size,
    u_int32_t* data,
    access_type_t access,
    const char* currComponentStr,
    ProgressCallBackAdvSt *progressFuncAdv)
{

    int leftSize = (int)size;
    u_int32_t i = 0;
    mcdaReg accessData;
    char stage[MAX_MSG_SIZE] = { 0 };
    int progressPercentage = -1;
    if (progressFuncAdv && progressFuncAdv->func) {
        snprintf(stage, MAX_MSG_SIZE, "%s %s component", (access == MCC_READ_COMP) ? "Reading" : "Writing", currComponentStr);
    }
    int maxDataSize = mget_max_reg_size(_mf, (access == MCC_READ_COMP) ? MACCESS_REG_METHOD_GET : MACCESS_REG_METHOD_SET)
        - sizeof(accessData);
    if (maxDataSize > MAX_REG_DATA) {
            maxDataSize = MAX_REG_DATA;
    }
    if (_mf->flags & MDEVS_IB && _mf->tp == MST_IB && maxDataSize > INBAND_MAX_REG_SIZE) {
        maxDataSize = INBAND_MAX_REG_SIZE - MCDA_REG_HEADER;
    }
    std::vector<u_int32_t> dataToRW(maxDataSize, 0);
    while (leftSize > 0) {
        DPRINTF(("0x%x bytes left to %s\n", leftSize, access == MCC_READ_COMP ? "read" : "burn"));
        memset(&accessData, 0, sizeof(mcdaReg));

        memcpy(accessData.data, dataToRW.data(), sizeof(accessData.data));
        accessData.update_handle = updateHandle;
        accessData.offset = offset + (size - leftSize);
        accessData.size = leftSize > maxDataSize ? maxDataSize : leftSize;
        mft_signal_set_handling(1);

        if (access == MCC_READ_COMP) {
            reg_access_status_t rc = reg_access_mcda(_mf, REG_ACCESS_METHOD_GET, &accessData);
            _manager->deal_with_signal();
            if (rc) {
                setLastFwError(_manager->regErrTrans(rc));
                _lastRegisterAccessStatus = rc;
                return false;
            }
            for (i = 0; i < accessData.size / 4; i++) {
                data[(size - leftSize) / 4 + i] = __le32_to_cpu(accessData.data[i]);
            }
            //printf("data[%#02x]: %#08x\n", (i-1)*4, data[(size - leftSize)/4 + i-1]);
        }
        else {
            for (i = 0; i < accessData.size / 4; i++) {
                accessData.data[i] = __cpu_to_le32(data[(size - leftSize) / 4 + i]);
            }
            reg_access_status_t rc = reg_access_mcda(_mf, REG_ACCESS_METHOD_SET, &accessData);
            _manager->deal_with_signal();
            if (rc) {
                setLastFwError(_manager->regErrTrans(rc));
                _lastRegisterAccessStatus = rc;
                return false;
            }
        }
        int newPercentage = (((size - leftSize) * 100) / size);
#ifdef UEFI_BUILD
        if (newPercentage > progressPercentage &&
            progressFuncAdv && progressFuncAdv->uefi_func) {
                progressPercentage = newPercentage;
                if (progressFuncAdv->uefi_func((int)newPercentage)) {
                     setLastFwError(FWCOMPS_ABORTED);
                     return false;
                }
        }
#else
        if (newPercentage > progressPercentage &&
            progressFuncAdv && progressFuncAdv->func) {
            progressPercentage = newPercentage;
            if (progressFuncAdv->func(progressPercentage, stage,
                PROG_WITH_PRECENTAGE, progressFuncAdv->opaque)) {
                setLastFwError(FWCOMPS_ABORTED);
                return false;
            }
        }
#endif
        leftSize -= maxDataSize;
    }
    if (progressFuncAdv && progressFuncAdv->func) {
        if (progressFuncAdv->func(0, stage,
            PROG_OK, progressFuncAdv->opaque)) {
                setLastFwError(FWCOMPS_ABORTED);
                return false;
        }
    }
    return true;
}
