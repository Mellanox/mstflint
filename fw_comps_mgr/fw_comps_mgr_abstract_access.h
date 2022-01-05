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
 
#ifndef USER_MLXFWOPS_LIB_FW_ABSTRACT_COMP_ACCESS_H_
#define USER_MLXFWOPS_LIB_FW_ABSTRACT_COMP_ACCESS_H_

#include "fw_comps_mgr.h"

class AbstractComponentAccess
{
public:
    virtual bool accessComponent(u_int32_t updateHandle, u_int32_t offset,
        u_int32_t size,
        u_int32_t data[],
        access_type_t access,
        const char* currComponentStr,
        ProgressCallBackAdvSt *progressFuncAdv) = 0;

    virtual fw_comps_error_t  getLastFirmwareError() = 0;
    virtual reg_access_status_t  getLastRegisterAccessStatus() = 0;

    AbstractComponentAccess(FwCompsMgr* manager, mfile *mf)
    {
        _mf = mf;
        _manager = manager;
        _lastFwError = FWCOMPS_SUCCESS;
    }
    virtual ~AbstractComponentAccess() {}

protected:
    mfile *_mf;
    FwCompsMgr* _manager;
    fw_comps_error_t _lastFwError;
    reg_access_status_t _lastRegisterAccessStatus;
};

class ComponentAccessFactory
{
public:
    AbstractComponentAccess* createDataAccessObject(FwCompsMgr* manager, mfile *mf, bool isMCDDRegisterSupported);
    static ComponentAccessFactory* GetInstance() {
        static ComponentAccessFactory myObj;
        return &myObj;
    }
};


#endif
