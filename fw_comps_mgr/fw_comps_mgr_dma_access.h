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
 * fw_comps_mgr_dma_access.h
 *
 *
 *  Created on: Dec 31, 2018
 *      Author: eddy
 */

#ifndef USER_MLXFWOPS_LIB_FW_COMPS_MGR_DMA_ACCESS_H_
#define USER_MLXFWOPS_LIB_FW_COMPS_MGR_DMA_ACCESS_H_

#include "fw_comps_mgr_abstract_access.h"

typedef struct tools_open_mcdd_reg mcddReg;

class DMAComponentAccess : public AbstractComponentAccess
{
public:
    DMAComponentAccess(FwCompsMgr* Manager, mfile* Mf) : AbstractComponentAccess(Manager, Mf) {}
    virtual ~DMAComponentAccess() {}
    virtual bool accessComponent(u_int32_t updateHandle,
                                 u_int32_t offset,
                                 u_int32_t size,
                                 u_int32_t* data,
                                 access_type_t access,
                                 const char* currComponentStr,
                                 ProgressCallBackAdvSt* progressFuncAdv);
    bool allocateMemory();
    static bool isBMESet(mfile* mf);
    virtual fw_comps_error_t getLastFirmwareError() { return _lastFwError; }
    virtual reg_access_status_t getLastRegisterAccessStatus() { return _lastRegisterAccessStatus; }

private:
    bool prepareParameters(u_int32_t _updateHandle,
                           mcddReg* accessData,
                           int offset,
                           u_int32_t* data,
                           int data_size,
                           int access,
                           int leftSize,
                           mtcr_page_addresses page,
                           mtcr_page_addresses mailbox_page,
                           int data_page_number);
    bool readFromDataPage(mcddReg* accessData, mtcr_page_addresses page, u_int32_t* data, int data_size, int leftSize);
    std::vector<mtcr_page_addresses> _allocatedListVect;
    void setLastError(fw_comps_error_t error) { _lastFwError = error; }
};
#endif
