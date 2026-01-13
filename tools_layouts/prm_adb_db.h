/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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
 *
 * prm_adb_db.h
 *
 *  Created on: Feb 27, 2019
 *      Author: diaedinrim
 */
#ifndef PRMADBDB
#define PRMADBDB

#include <string>
#include <exception>
#include "dev_mgt/tools_dev_types.h"


typedef enum PrmAdbType
{
    PRM_ADB_TYPE_HCA,
    PRM_ADB_TYPE_SWITCH,
    PRM_ADB_TYPE_RETIMER,
    PRM_ADB_TYPE_GPU,
    PRM_ADB_TYPE_UNKNOWN
} PrmAdbType_t;


class PrmAdbDB
{
public:
    static std::string prm_adb_db_trim(const std::string& s);
    static std::string prm_adb_db_rtrim(const std::string& s);
    static std::string prm_adb_db_ltrim(const std::string& s);
    static std::string getDefaultDBName(PrmAdbType_t adbType);
    static std::string getDefaultDBName(dm_dev_id_t devID);
};

class PrmDBException: public std::exception
{
public:
    /* Methods */
    PrmDBException();
    PrmDBException(const char* msg, ...) __attribute__((format(__printf__, 2, 3)));
    PrmDBException(std::string msg);
    virtual ~PrmDBException() throw();
    virtual const char* what() const throw();
    virtual std::string what_s() const;

private:
    std::string _msg;
};

#endif
