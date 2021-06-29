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
 
#include "fw_comps_mgr_abstract_access.h"
#include "fw_comps_mgr_direct_access.h"
#include "fw_comps_mgr_dma_access.h"

AbstractComponentAccess* ComponentAccessFactory::createDataAccessObject(FwCompsMgr* Manager, mfile *Mf, bool isMCDDRegisterSupported)
{
#ifndef UEFI_BUILD
    
    if (getenv("DISABLE_DMA_ACCESS") != NULL) {
        return new DirectComponentAccess(Manager, Mf);
    }
#endif

    // DMA is supported only when COMMAND[BME] is set in PCI configuration
    bool isBmeSet = false;
#ifdef __WIN__
    isBmeSet = true; // mst64 (system service that is loaded in mtcr::open()) will set the BME
#else
    isBmeSet = false;

    if (isMCDDRegisterSupported) {

        int COMMAND_REG_OFFSET = 0x4;
        int BME_MASK = 0x00000004;

        mtcr_read_dword_from_config_space result;
        int rc = read_dword_from_conf_space(COMMAND_REG_OFFSET, Mf, &result);

        if ((rc == 0) && (result.data & BME_MASK)) {
            isBmeSet = true;
        }
    }
#endif

    if (isMCDDRegisterSupported && isBmeSet){
        DMAComponentAccess* dmaComponentAccess = new DMAComponentAccess(Manager, Mf);
        if (dmaComponentAccess->allocateMemory()) {
            return dmaComponentAccess;
        }
        else {
            delete dmaComponentAccess;
            return new DirectComponentAccess(Manager, Mf);
        }
    } else {
        return new DirectComponentAccess(Manager, Mf);
    }

}
