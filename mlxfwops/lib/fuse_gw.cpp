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
 */

#include <math.h>
#include <bit_slice.h>
#include "fuse_gw.h"

FuseGW::FuseGW(mfile* mf): _mf(mf), _gw_address(0), _data_address(0), _data_bit_offset(0), _data_bit_len(0)
{};

void FuseGW::setGWAddress(u_int32_t address)
{
    _gw_address = address;
}

void FuseGW::setDataAddress(u_int32_t address)
{
    _data_address = address;
}

void FuseGW::setFieldBitOffset(size_t offset)
{
    _data_bit_offset = offset;
}

void FuseGW::setFieldBitLen(size_t len)
{
    _data_bit_len = len;
}

void FuseGW::getData(u_int32_t& data)
{
    // Read from GW
    try {
        lock();
        executeReadCommand();
        waitForResult();
        readResult(data);
        unlock();
    } catch (const char* msg) {
        unlock();   
        throw msg;
    }
}

// ---------------
// Private methods
// ---------------

void FuseGW::lock() 
{
    waitForGWLockState(_gw_address, 0);

    //* lock GW copy
    waitForGWLockState(_gw_address + 4, 1);
}

void FuseGW::waitForGWLockState(u_int32_t address, u_int32_t requiredState) 
{
    const u_int32_t MAX_ITER_NUM = 100;
    const u_int32_t SLEEP_TIME = 10; // [msec]
    u_int32_t iter_num = 0;    
    u_int32_t currentState = getCurrentGWState(address);

    while (currentState != requiredState) {
        msleep(SLEEP_TIME);

        currentState = getCurrentGWState(address);

        iter_num++;        
        if (iter_num > MAX_ITER_NUM) {
            throw "failed to lock (timeout error)";
        }
    }
}

bool FuseGW::getCurrentGWState(u_int32_t address)
{
    u_int32_t ctrl_reg = 0;

    if (mread4(_mf, address, &ctrl_reg) != 4) {
        throw "failed to lock (read error)";
    }
        
    return EXTRACT(ctrl_reg, CTRL_LOCK_BIT_OFFSET, 1);
}

void FuseGW::executeReadCommand() 
{
    int rc = mwrite4(_mf, _gw_address, CTRL_READ | CTRL_BUSY);
    if (rc != 4) {
        throw "failed to executeReadCommand (write error)";
    }
}

void FuseGW::waitForResult() 
{
    int iter_num = 0, MAX_ITER_NUM = 100;
    int const SLEEP_TIME = 10; // [msec]

    bool busy;
    do {
        int rc = 0;
        u_int32_t ctrl_reg = 0;

        if (iter_num != 0) {
            msleep(SLEEP_TIME);
        }
        rc = mread4(_mf, _gw_address, &ctrl_reg);
        
        if (rc != 4) {
            throw "failed to waitForResult (read error)";
        }

        busy = (ctrl_reg & CTRL_BUSY) != 0;
        iter_num++;
        
        if (iter_num > MAX_ITER_NUM) {
            throw "failed to waitForResult (timeout error)";
        }
    } while (busy);
}

void FuseGW::readResult(u_int32_t& result)
{
    int rc = mread4(_mf, _data_address, &result);
    if (rc !=  4) 
    {
        throw "failed to readResult (read error)";
    }

    TOCPU(&result);    
    result = EXTRACT(result, _data_bit_offset, _data_bit_len);
}

void FuseGW::unlock(){
    int rc = mwrite4(_mf, _gw_address, 0);
    if (rc != 4) {
        throw "failed to unlock (write error)";
    }
}


/********************************************************************************/
/*                                                                              */
/*                        SecureBootFuse Class                                  */
/*                                                                              */
/********************************************************************************/

SecureBootFuse::SecureBootFuse(mfile* mf, chip_type_t chip_type):
    _gw(mf), _chip_type(chip_type), _is_supported_in_live_fish(false)
{
    switch (chip_type)
    {
        case CT_CONNECTX7:
            _gw.setGWAddress(0xE4C00);      // irisc.ir_fuse_gw
            _gw.setDataAddress(0xE4E7C);    // irisc.ir_fuse_gw.desc0.secure_boot
            _gw.setFieldBitOffset(28);
            _gw.setFieldBitLen(1);
            _is_supported_in_live_fish = true;
            break;
        case CT_QUANTUM2:
            _gw.setGWAddress(0xa2800);      // mng.irisc.ir_fuse_gw
            _gw.setDataAddress(0xa2a7c);    // mng.ir.ir_fuse_gw.desc0.secure_boot
            _gw.setFieldBitOffset(29);
            _gw.setFieldBitLen(1);
            _is_supported_in_live_fish = true;
            break;
        default:
            _is_supported_in_live_fish = false;
            break;
    }
}

bool SecureBootFuse::isAccessibleInLiveFish()
{
    return _is_supported_in_live_fish;
}

// secure boot means that the device is capable of using secure boot mode
int SecureBootFuse::isSecureBoot(bool& is_secure_boot)
{
    u_int32_t data;
    int rc = 0;
    
    try
    {
        _gw.getData(data);
        
        switch (_chip_type)
        {
            case CT_CONNECTX7:
            case CT_QUANTUM2:
                is_secure_boot = (data & 0x1) == 0x1;
                break;
            default:
                printf("-E- Failed to get data from Fuse: Device is not supported.\n");
                rc = -1;
                break;
        }
    }
    catch(const char* msg)
    {
        printf("-E- Failed to get data from Fuse: %s.\n", msg);
        rc = -1;
    }
    catch(exception e)
    {
        printf("-E- Failed to get data from Fuse: %s.\n", e.what());
        rc = -1;
    }
    catch(...)
    {
        rc = -1;
    }

    return rc;
}


/********************************************************************************/
/*                                                                              */
/*                        LifeCycleFuse Class                                   */
/*                                                                              */
/********************************************************************************/

LifeCycleFuse::LifeCycleFuse(mfile* mf, chip_type_t chip_type):
    _gw(mf), _chip_type(chip_type), _is_supported_in_live_fish(false)
{
    switch (chip_type)
    {
        case CT_CONNECTX7:
            _gw.setGWAddress(0xF4550);      // yu.fuse_gw_life_cycle
            _gw.setDataAddress(0xF455C);    // yu.fuse_gw_life_cycle.desc0.life_cycle_replica0
            _gw.setFieldBitOffset(0);
            _gw.setFieldBitLen(32);
            _is_supported_in_live_fish = true;
            break;
        case CT_QUANTUM2:
            _gw.setGWAddress(0xf3250);      // mng.yu.fuse_gw_life_cycle
            _gw.setDataAddress(0xf325c);    // mng.yu.fuse_gw_life_cycle.desc0.life_cycle_replica0
            _gw.setFieldBitOffset(0);
            _gw.setFieldBitLen(32);
            _is_supported_in_live_fish = true;
            break;
        default:
            _is_supported_in_live_fish = false;
            break;
    }
}

bool LifeCycleFuse::isAccessibleInLiveFish()
{
    return _is_supported_in_live_fish;
}

int LifeCycleFuse::getStatus(life_cycle_t& life_cycle)
{
    u_int32_t data;
    int rc = 0;
    
    try
    {
        _gw.getData(data); 
        
        switch (_chip_type)
        {
            case CT_CONNECTX7:
            case CT_QUANTUM2:
                life_cycle = (life_cycle_t)calcMajorityVote4B(data);
                break;
            default:
                printf("-E- Failed to get data from Fuse: Device is not supported.\n");
                rc = -1;
                break;
        }
    }
    catch(const char* msg)
    {
        printf("-E- Failed to get data from Fuse: %s.\n", msg);
        rc = -1;
    }
    catch(exception e)
    {
        printf("-E- Failed to get data from Fuse: %s.\n", e.what());
        rc = -1;
    }
    catch(...)
    {
        rc = -1;
    }

    return rc;
}

// in 4 bytes there are 16 replicas, each replica is 2 bits.
// this method calculates the vote for each bit, and determines bit's value 
// in the life cycle status using majority vote
life_cycle_t LifeCycleFuse::calcMajorityVote4B(u_int32_t data)
{
    int life_cycle = 0;
    u_int32_t even_bits_mask = 0xAA;
    u_int32_t odd_bits_mask = 0x55;
    u_int32_t first_bit_vote = 0;
    u_int32_t second_bit_vote = 0;
    size_t i = 0;

    // Count the number of 'on' bits in 4B
    for (; i < 4; ++i)
    {
        first_bit_vote += calcOnBits1B((data >> (i * 4)) & odd_bits_mask);
        second_bit_vote += calcOnBits1B((data >> (i * 4)) & even_bits_mask);
    }

    // Check if votes are equal (device is in RMA)
    if ((first_bit_vote == 8) || (second_bit_vote == 8))
    {
        return RMA;
    }

    // Set life cycle according to majority vote
    if (first_bit_vote > 8)
    {
        life_cycle |= 1;
    }
    if (second_bit_vote > 8)
    {
        life_cycle |= 2;
    }

    return (life_cycle_t)life_cycle;
}

u_int8_t LifeCycleFuse::calcOnBits1B(u_int8_t byte)
{
    u_int32_t on_bits_count = 0;
    u_int8_t first_bit_mask = 0x1;
    size_t i = 0;

    for (; i < BYTE_SIZE; ++i) 
    {
        on_bits_count += ((byte >> i) & first_bit_mask);
    }

    return on_bits_count;
}


/********************************************************************************/
/*                                                                              */
/*                        SecurityVersionFuse Class                             */
/*                                                                              */
/********************************************************************************/

SecurityVersionFuse::SecurityVersionFuse(mfile* mf, chip_type_t chip_type):
    _rollbackProtectionGW(mf), _minimalSecurityVersionGW(mf), _chip_type(chip_type), _is_supported_in_live_fish(false)
{
    switch (chip_type)
    {
        case CT_CONNECTX7:
            _rollbackProtectionGW.setGWAddress(0xf4540);      
            _rollbackProtectionGW.setDataAddress(0xf4548);    
            _rollbackProtectionGW.setFieldBitOffset(0);
            _rollbackProtectionGW.setFieldBitLen(32);
            _minimalSecurityVersionGW.setGWAddress(0xf4520);      
            _minimalSecurityVersionGW.setDataAddress(0xf452c);  
            _minimalSecurityVersionGW.setFieldBitOffset(0);
            _minimalSecurityVersionGW.setFieldBitLen(32);
            _is_supported_in_live_fish = true;
            break;
        case CT_QUANTUM2:
            _rollbackProtectionGW.setGWAddress(0xf3240);      
            _rollbackProtectionGW.setDataAddress(0xf3248);    
            _rollbackProtectionGW.setFieldBitOffset(0);
            _rollbackProtectionGW.setFieldBitLen(32);
            _minimalSecurityVersionGW.setGWAddress(0xf3220);      
            _minimalSecurityVersionGW.setDataAddress(0xf322c);  
            _minimalSecurityVersionGW.setFieldBitOffset(0);
            _minimalSecurityVersionGW.setFieldBitLen(32);
            _is_supported_in_live_fish = true;
            break;
        default:
            _is_supported_in_live_fish = false;
            break;
    }
}

bool SecurityVersionFuse::isAccessibleInLiveFish()
{
    return _is_supported_in_live_fish;
}

bool SecurityVersionFuse::getSecurityVersion(u_int32_t& securityVersion)
{
    u_int32_t data;
    int rc = 0;
    
    try
    {
        u_int32_t const MINIMAL_SECURITY_VERSION_MASK = 0x00000ff0;
        u_int32_t const MINIMAL_SECURITY_VERSION_OFFSET = 4;

        switch (_chip_type)
        {
            case CT_CONNECTX7:
            case CT_QUANTUM2:
                _rollbackProtectionGW.getData(data);
                securityVersion += countSetBits(data);
                _rollbackProtectionGW.setDataAddress(0xf454c);
                _rollbackProtectionGW.getData(data);
                securityVersion += countSetBits(data);
                
                _minimalSecurityVersionGW.getData(data);
                securityVersion += ((data & MINIMAL_SECURITY_VERSION_MASK) >> MINIMAL_SECURITY_VERSION_OFFSET); 
                break;
            default:
                printf("-E- Failed to get data from Fuse: Device is not supported.\n");
                rc = -1;
                break;
        }
    }
    catch(const char* msg)
    {
        printf("-E- Failed to get data from Fuse: %s.\n", msg);
        rc = -1;
    }
    catch(exception e)
    {
        printf("-E- Failed to get data from Fuse: %s.\n", e.what());
        rc = -1;
    }
    catch(...)
    {
        rc = -1;
    }

    return rc;
}

u_int32_t SecurityVersionFuse::countSetBits(u_int32_t num){
    u_int32_t count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}