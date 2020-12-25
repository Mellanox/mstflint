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
 *
 */
/*
 * fw_comps_mgr_dma_access.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: eddy
 */

#include <math.h>
#include "fw_comps_mgr_dma_access.h"
#include "bit_slice.h"

#ifndef UEFI_BUILD
#include <mft_sig_handler.h>
#include "mad_ifc/mad_ifc.h"
#else
// no signal handling.
static void mft_signal_set_handling(int isOn)
{
    return;
}
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000
#endif
#define FLASH_WRITE_SPEED (640*1024) //640 kB/sec

#define TIMETOSLEEP (1000*PAGE_SIZE/FLASH_WRITE_SPEED) //6 msec
#define MAXIMUM_SLEEP_TIME_MS 20000
#define _MCDD_DEBUG_ 0


#if _MCDD_DEBUG_ 
void printData(u_int32_t* data, int data_size, int format)
{
    for (int i = 0; i < data_size/4; i ++)
    {
        if(format == 0) {
            DPRINTF("\n DWORD[%04x]: 0x%08x\n", (i), (data[i]));
        }
        else {
            u_int32_t x1 = (data[i] & 0xff) << 24;
            u_int32_t x2 = (data[i] & 0xff00) >> 8;
            u_int32_t x3 = (data[i] & 0xff0000) >> 16;
            u_int32_t x4 = (data[i] & 0xff000000) >> 24;
            u_int32_t tmp = x1 + x4 + (x2 << 16) + (x3 << 8);
            DPRINTF("\n DWORD[%04x]: 0x%08x\n", (i), tmp);
        }
    }
}
#endif

bool DMAComponentAccess::prepareParameters(u_int32_t updateHandle, mcddReg* accessData,
    int offset, u_int32_t* data, int data_size, int access, int leftSize,
     mtcr_alloc_page_t page,  mtcr_alloc_page_t mailbox_page)
{
    accessData->update_handle = updateHandle;
    accessData->offset = offset;
    accessData->size = leftSize > PAGE_SIZE ? PAGE_SIZE : leftSize;
    accessData->data_page_phys_addr_lsb = EXTRACT64(page.pa, 0, 32);
    accessData->data_page_phys_addr_msb = EXTRACT64(page.pa, 32, 32);
    accessData->mailbox_page_phys_addr_lsb = EXTRACT64(mailbox_page.pa, 0, 32);
    accessData->mailbox_page_phys_addr_msb = EXTRACT64(mailbox_page.pa, 32, 32);
    int currentOffset = data_size - leftSize;
    if (access == MCDA_WRITE_COMP) {
        u_int32_t* data_ptr = (u_int32_t*)page.va;
        for (int i = 0; i < accessData->size / 4; i++) {
            *data_ptr = ___my_swab32(data[(currentOffset) / 4 + i]);
            data_ptr++;
        }
    }
    return true;
}

bool DMAComponentAccess::allocateMemory()
{
    for (int i = 0; i < FMPT_ALLOCATED_LIST_LENGTH; i++) {
        mtcr_alloc_page alloc_page;
        if (allocate_kernel_memory_page(_mf, (mtcr_alloc_page*)&alloc_page)) {
            return false;
        }
#if _MCDD_DEBUG_
        u_int32_t va_lsb = EXTRACT64(alloc_page.va, 0, 32);
        u_int32_t va_msb = EXTRACT64(alloc_page.va, 32, 32);
        u_int32_t pa_lsb = EXTRACT64(alloc_page.pa, 0, 32);
        u_int32_t pa_msb = EXTRACT64(alloc_page.pa, 32, 32);
        DPRINTF(("Allocated for page %d data PA 0x%08x%08x VA 0x%08x%08x \r\n", i, pa_msb, pa_lsb, va_msb, va_lsb));
#endif
        _allocatedListVect.push_back(alloc_page);
    }
    return true;
}

bool DMAComponentAccess::readFromDataPage(mcddReg* accessData,  mtcr_alloc_page_t page, u_int32_t* data, int data_size, int leftSize)
{
    u_int32_t* data_ptr = (u_int32_t*)page.va;
    int currentOffset = (data_size - leftSize) / 4;
    for (int i = 0; i < accessData->size / 4; i++) {
        data[currentOffset + i] = ___my_swab32(*data_ptr);
        data_ptr++;
#if _MCDD_DEBUG_ 
        if (i % 100 == 0)
            DPRINTF(("\nReading data[%#02x]: %#08x\n", (i) * 4, data[(data_size - leftSize) / 4 + i]));
#endif
    }
    return true;
}

bool DMAComponentAccess::accessComponent(u_int32_t updateHandle, u_int32_t offset,
    u_int32_t data_size,
    u_int32_t* data,
    access_type_t access,
    const char* currComponentStr,
    ProgressCallBackAdvSt *progressFuncAdv)
{
#ifndef UEFI_BUILD
    try
    {
#endif
        int leftSize = (int)data_size;
        int CurrentPage = FMPT_FIRST_PAGE;
        char stage[MAX_MSG_SIZE] = { 0 };
        int progressPercentage = -1;
        int currentOffset = 0;
        int nMaximumSleepTime = 0;
        tools_open_mcdd_descriptor mailboxVirtPtr_1;
        if (progressFuncAdv && progressFuncAdv->func) {
            snprintf(stage, MAX_MSG_SIZE, "%s %s component", (access == MCDA_READ_COMP) ? "Reading" : "Writing", currComponentStr);
        }
        //updateHandle &= ~0xff000000;
        DPRINTF(("DMAComponentAccess::AccessComponent BEGIN size %d access %s\n", data_size, (access == MCDA_READ_COMP) ? "READ" : "WRITE"));
        mcddReg accessData;
         mtcr_alloc_page_t page = _allocatedListVect[CurrentPage];
         mtcr_alloc_page_t mailboxPage = _allocatedListVect[FMPT_MAILBOX_PAGE];
        //tools_open_mcdd_descriptor* mailboxVirtPtr = (tools_open_mcdd_descriptor*)mailboxPage.va;
        int maxDataSize = data_size > PAGE_SIZE ? PAGE_SIZE : data_size;
        memset(&accessData, 0, TOOLS_OPEN_MCDD_REG_SIZE);

        if (access == MCDA_READ_COMP) {
            memset(data , 0, data_size);
        }
        prepareParameters(updateHandle, &accessData, offset + (data_size - leftSize), data, data_size, access, leftSize, page, mailboxPage);
        int nIteration = 0;
        while (leftSize > 0) {
            memset((u_int8_t*)mailboxPage.va, 0, TOOLS_OPEN_MCDD_DESCRIPTOR_SIZE);
            memset(&mailboxVirtPtr_1, 0, TOOLS_OPEN_MCDD_DESCRIPTOR_SIZE);//set zero before each transaction
            maxDataSize = leftSize > PAGE_SIZE ? PAGE_SIZE : leftSize;
            mft_signal_set_handling(1);

            reg_access_status_t rc = reg_access_mcdd(_mf, (access == MCDA_READ_COMP) ? REG_ACCESS_METHOD_GET : REG_ACCESS_METHOD_SET, &accessData);
            _manager->deal_with_signal();
            if (rc) {
                DPRINTF(("CRITICAL : DMAComponentAccess::AccessComponent reg_access_mcdd ERROR: %#x\n", rc));
                setLastError(_manager->regErrTrans(rc));
                _lastRegisterAccessStatus = rc;
                return false;
            }

            //if we write a data, meawhile use a time for prepare next data page
            if (access == MCDA_WRITE_COMP) {
                leftSize -= maxDataSize;
                if (leftSize > 0)
                {
                    if(FMPT_FIRST_PAGE == CurrentPage)
                        CurrentPage = FMPT_SECOND_PAGE;
                    else
                        CurrentPage = FMPT_FIRST_PAGE;

                    page = _allocatedListVect[CurrentPage];
                    currentOffset = offset + (data_size - leftSize);
                    prepareParameters(updateHandle, &accessData, currentOffset, data, data_size, access, leftSize, page, mailboxPage);
                }
            }

            // This is because the FW will change the status from 0 to BUSY, when it starts the reading/writing operation.
            // meanwhile, the SW has to wait until FW is really starting.
            // It's possible, though, that we will not enter to this loop at all or only sometimes.
            tools_open_mcdd_descriptor_unpack(&mailboxVirtPtr_1, (const u_int8_t*)mailboxPage.va);
            DPRINTF(("AccessComponent1 status %d err %d reserved3 %d\n", mailboxVirtPtr_1.status, mailboxVirtPtr_1.error, mailboxVirtPtr_1.reserved3));
            nMaximumSleepTime = 0;
            while (mailboxVirtPtr_1.status == FFS_FW_UNKNOWN) {
                int timeToSleepMs = (int)(floor(TIMETOSLEEP / 8.0));
                msleep(timeToSleepMs);
                tools_open_mcdd_descriptor_unpack(&mailboxVirtPtr_1, (const u_int8_t*)mailboxPage.va);
                nMaximumSleepTime += timeToSleepMs;
                if(nMaximumSleepTime >= MAXIMUM_SLEEP_TIME_MS) {
                    setLastError(FWCOMPS_ABORTED);
                    return false;
                }
            }

            // here the FW started to work
            msleep(TIMETOSLEEP);
            tools_open_mcdd_descriptor_unpack(&mailboxVirtPtr_1, (const u_int8_t*)mailboxPage.va);
            DPRINTF(("AccessComponent2 status %d err %d reserved3 %d\n", mailboxVirtPtr_1.status, mailboxVirtPtr_1.error, mailboxVirtPtr_1.reserved3));

            nMaximumSleepTime = 0;
            while (mailboxVirtPtr_1.status == FFS_FW_BUSY) {
                msleep(TIMETOSLEEP);
                tools_open_mcdd_descriptor_unpack(&mailboxVirtPtr_1, (const u_int8_t*)mailboxPage.va);
                nMaximumSleepTime += TIMETOSLEEP;
                if(nMaximumSleepTime >= MAXIMUM_SLEEP_TIME_MS) {
                    setLastError(FWCOMPS_ABORTED);
                    return false;
                }
            }
            tools_open_mcdd_descriptor_unpack(&mailboxVirtPtr_1, (const u_int8_t*)mailboxPage.va);
            DPRINTF(("AccessComponent3 status %d err %d reserved3 %d\n", mailboxVirtPtr_1.status, mailboxVirtPtr_1.error, mailboxVirtPtr_1.reserved3));

            if (mailboxVirtPtr_1.status == FFS_FW_ERROR) {
                fw_comps_error_t fw_err = (fw_comps_error_t)(mailboxVirtPtr_1.error + FWCOMPS_MCC_ERR_CODES);//return error to high level app. Errors are defined as MCC errors
                setLastError(fw_err);
                DPRINTF(("CRITICAL : DMAComponentAccess::AccessComponent status %d err %d FW ERROR: %#x\n", mailboxVirtPtr_1.status, mailboxVirtPtr_1.error, fw_err));
                return false;
            }

            // read the data from FW (from page.virtual_address -> to 'data' array)
            if (access == MCDA_READ_COMP) {
                DPRINTF(("READ mailboxVirtPtr->status = %d\r\n", mailboxVirtPtr_1.status));
                readFromDataPage(&accessData, page, data, data_size, leftSize);
                leftSize -= maxDataSize;
                if (leftSize > 0) {
                    CurrentPage == FMPT_FIRST_PAGE ? CurrentPage = FMPT_SECOND_PAGE : CurrentPage = FMPT_FIRST_PAGE;
                    page = _allocatedListVect[CurrentPage];//change the page
                    prepareParameters(updateHandle, &accessData, offset + (data_size - leftSize), data, data_size, access, leftSize, page, mailboxPage);
                    //prepare auxilary data for next iteration
                }
            }
            nIteration++;
            int newPercentage = (((data_size - leftSize) * 100) / data_size);
#ifdef UEFI_BUILD
        if (newPercentage > progressPercentage &&
            progressFuncAdv && progressFuncAdv->uefi_func) {
                progressPercentage = newPercentage;
                if (progressFuncAdv->uefi_func((int)newPercentage)) {
                     setLastError(FWCOMPS_ABORTED);
                     return false;
                }
        }
#else
        if (newPercentage > progressPercentage &&
            progressFuncAdv && progressFuncAdv->func) {
            progressPercentage = newPercentage;
            if (progressFuncAdv->func(progressPercentage, stage,
                PROG_WITH_PRECENTAGE, progressFuncAdv->opaque)) {
                setLastError(FWCOMPS_ABORTED);
                return false;
            }
        }
#endif
        }
        if (progressFuncAdv && progressFuncAdv->func) {
            if (progressFuncAdv->func(0, stage,
                PROG_OK, progressFuncAdv->opaque)) {
                setLastError(FWCOMPS_ABORTED);
                return false;
            }
        }
        DPRINTF(("DMAComponentAccess::AccessComponent END \n"));
        return true;
#ifndef UEFI_BUILD
    }
    catch (std::exception &e) {
        DPRINTF(("DMAComponentAccess::Exception occured %s\n", e.what()));
        return false;
    }
#endif
}
