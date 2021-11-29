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

#ifndef FUSE_GW_H
#define FUSE_GW_H

#include <mtcr.h>
#include "flint_base.h"

#define BYTE_SIZE 8

using namespace std;

class FuseGW 
{
public:
    FuseGW(mfile* mf);
    ~FuseGW() {};
        
    void getData(u_int32_t& data);
    void setGWAddress(u_int32_t address);
    void setDataAddress(u_int32_t address);
    void setFieldBitOffset(size_t offset);
    void setFieldBitLen(size_t len);

private:
    mfile* _mf;
    u_int32_t _gw_address;
    u_int32_t _data_address; 
    size_t _data_bit_offset; 
    size_t _data_bit_len;

    u_int32_t static const CTRL_LOCK_BIT_OFFSET = 31;
    u_int32_t static const CTRL_RW   = 0x40000000;
    u_int32_t static const CTRL_READ = CTRL_RW & 0xffffffff;
    u_int32_t static const CTRL_BUSY = 0x20000000;        

    void lock();
    void waitForGWLockState(u_int32_t address, u_int32_t requiredState);
    bool getCurrentGWState(u_int32_t address);
    void executeReadCommand();
    void waitForResult();
    void readResult(u_int32_t& result);
    void unlock();

    void alignBits(u_int8_t* src, size_t byte_len, size_t bit_offset);
};


class LifeCycleFuse
{
public:
    LifeCycleFuse(mfile* mf, chip_type_t chip_type);
    ~LifeCycleFuse() {};

    bool isAccessibleInLiveFish();
    int getStatus(life_cycle_t& life_cycle);

private:
    life_cycle_t calcMajorityVote4B(u_int32_t data);
    u_int8_t calcOnBits1B(u_int8_t byte);

    FuseGW _gw;
    chip_type_t _chip_type;
    
    bool _is_supported_in_live_fish;
};


class SecureBootFuse
{
public:
    SecureBootFuse(mfile* mf, chip_type_t chip_type);
    ~SecureBootFuse() {};

    bool isAccessibleInLiveFish();
    int isSecureBoot(bool& is_secure_boot);

private:
    FuseGW _gw;
    chip_type_t _chip_type;
    bool _is_supported_in_live_fish;
};


class SecurityVersionFuse
{
public:
    SecurityVersionFuse(mfile* mf, chip_type_t chip_type);
    ~SecurityVersionFuse() {};

    bool isAccessibleInLiveFish();
    bool getSecurityVersion(u_int32_t& result);

private:   
    typedef enum {ROLLBACK_PROTECTION, MINIMAL_VERSION} gw_type_t;
    
    void getRollbackProtection(u_int32_t* result);
    void getMinimalSecurityVersion(u_int32_t* result);
    void setGWAddress(gw_type_t gw_type);
    u_int32_t countSetBits(u_int32_t num);

    FuseGW _rollbackProtectionGW;
    FuseGW _minimalSecurityVersionGW;
    chip_type_t _chip_type;
    bool _is_supported_in_live_fish;
};

#endif /*FUSE_GW_H*/
