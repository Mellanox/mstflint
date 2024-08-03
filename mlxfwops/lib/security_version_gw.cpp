/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "security_version_gw.h"
#include "tools_time.h"

bool SecurityVersionGW::isAccessibleInLiveFish()
{
    setGWAddress(ROLLBACK_PROTECTION); // only to set _ctrl_address (can pick ROLLBACK_PROTECTION or MINIMAL_VERSION)
    return _ctrl_address == GW_NOT_SUPPORTED ? false : true;
}

bool SecurityVersionGW::getSecurityVersion(u_int32_t* result)
{
    u_int32_t rollbackProtection;
    u_int32_t minimalSecurityVersion;

    try
    {
        getRollbackProtection(&rollbackProtection);
        getMinimalSecurityVersion(&minimalSecurityVersion);
    }
    catch (const char* msg)
    {
        // Ignore the message and return false instead
        return false;
    }

    *result = rollbackProtection + minimalSecurityVersion;
    return true;
}

// ---------------
// Private methods
// ---------------

void SecurityVersionGW::setGWAddress(gw_type_t gw_type)
{
    switch (_chip_type)
    {
        case CT_CONNECTX7:
            _ctrl_address = (gw_type == ROLLBACK_PROTECTION ? 0xf4540 : 0xf4520);
            break;
        case CT_BLUEFIELD3:
            _ctrl_address = (gw_type == ROLLBACK_PROTECTION ? 0xf4340 : 0xf4320);
            break;
        default:
            _ctrl_address = GW_NOT_SUPPORTED;
    }

    _result1_address = _ctrl_address + 8;
    _result2_address = _result1_address + 4;
}

void SecurityVersionGW::getRollbackProtection(u_int32_t* result)
{
    u_int32_t result1, result2;

    setGWAddress(ROLLBACK_PROTECTION);

    // Read from GW
    try
    {
        lock();
        executeReadCommand();
        waitForResult();
        readResult1(&result1);
        readResult2(&result2);
        unlock();
    }
    catch (const char* msg)
    {
        unlock();
        throw msg;
    }

    *result = countSetBits(result1) + countSetBits(result2);
}

void SecurityVersionGW::getMinimalSecurityVersion(u_int32_t* result)
{
    u_int32_t result2;

    setGWAddress(MINIMAL_VERSION);

    // Read from GW
    try
    {
        lock();
        executeReadCommand();
        waitForResult();
        readResult2(&result2);
        unlock();
    }
    catch (const char* msg)
    {
        unlock();
        throw msg;
    }

    // Extract minimal_security_version
    u_int32_t const MINIMAL_SECURITY_VERSION_MASK = 0x00000ff0;
    u_int32_t const MINIMAL_SECURITY_VERSION_OFFSET = 4;
    *result = (result2 & MINIMAL_SECURITY_VERSION_MASK) >> MINIMAL_SECURITY_VERSION_OFFSET;
}

void SecurityVersionGW::lock()
{
    int iter_num = 0, MAX_ITER_NUM = 100;
    int const SLEEP_TIME = 10; // [msec]

    bool lock;
    do
    {
        int rc = 0;
        u_int32_t ctrl_reg = 0;
        if (iter_num != 0)
            msleep(SLEEP_TIME);
        rc = mread4(_mf, _ctrl_address, &ctrl_reg);
        if (rc != 4)
            throw "failed to lock (read error)";
        lock = (ctrl_reg & CTRL_LOCK) != 0;
        iter_num++;
        if (iter_num > MAX_ITER_NUM)
            throw "failed to lock (timeout error)";
    } while (lock);
}

void SecurityVersionGW::executeReadCommand()
{
    int rc = mwrite4(_mf, _ctrl_address, CTRL_READ | CTRL_BUSY);
    if (rc != 4)
        throw "failed to executeReadCommand (write error)";
}

void SecurityVersionGW::waitForResult()
{
    int iter_num = 0, MAX_ITER_NUM = 100;
    int const SLEEP_TIME = 10; // [msec]

    bool busy;
    do
    {
        int rc = 0;
        u_int32_t ctrl_reg = 0;
        if (iter_num != 0)
            msleep(SLEEP_TIME);
        rc = mread4(_mf, _ctrl_address, &ctrl_reg);
        if (rc != 4)
            throw "failed to waitForResult (read error)";
        busy = (ctrl_reg & CTRL_BUSY) != 0;
        iter_num++;
        if (iter_num > MAX_ITER_NUM)
            throw "failed to waitForResult (timeout error)";
    } while (busy);
}

void SecurityVersionGW::readResult1(u_int32_t* result)
{
    int rc = mread4(_mf, _result1_address, result);
    if (rc != 4)
        throw "failed to readResult1 (read error)";
}

void SecurityVersionGW::readResult2(u_int32_t* result)
{
    int rc = mread4(_mf, _result2_address, result);
    if (rc != 4)
        throw "failed to readResult2 (read error)";
}

void SecurityVersionGW::unlock()
{
    int rc = mwrite4(_mf, _ctrl_address, 0);
    if (rc != 4)
        throw "failed to unlock (write error)";
}

u_int32_t SecurityVersionGW::countSetBits(u_int32_t num)
{
    u_int32_t count = 0;
    while (num)
    {
        count += num & 1;
        num >>= 1;
    }
    return count;
}
