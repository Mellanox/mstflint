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
 *
 * MlxconfigFactory.h
 *
 *  Created on: May 24, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_FACTORY_H_
#define MLXCFG_FACTORY_H_

#include <vector>
#include <exception>

#include "mlxcfg_tlv.h"
#include "mlxcfg_param.h"
#include <ext_libs/sqlite/sqlite3.h>

enum SPLITBY
{
    PORT,
    MODULE,
};

class MlxcfgDBManager
{
private:
    std::string _dbName;
    sqlite3* _db;
    const unsigned int _supportedVersion;

    static int selectAndCreateNewTLVCallBack(void* object, int argc, char** argv, char** azColName);
    static int selectTLVCallBack(void*, int, char**, char**);
    static int selectAndCreateParamCallBack(void* object, int argc, char** argv, char** azColName);
    static int selectParamCallBack(void*, int, char**, char**);
    static int selectParamByMlxconfigNameCallBack(void*, int, char**, char**);
    void openDB();
    void checkDBVersion();
    inline bool isDBFileExists(const std::string& name);
    std::shared_ptr<TLVConf> fetchTLVByName(std::string tlvName, u_int32_t port, int32_t module);
    std::shared_ptr<TLVConf> fetchTLVByIndexAndClass(u_int32_t id, TLVClass c);

public:
    MlxcfgDBManager(std::string dbName);
    ~MlxcfgDBManager();
    std::string _callBackErr;
    bool _isAllFetched;
    bool isParamMlxconfigNameExist(std::string mlxconfigName);
    std::shared_ptr<Param> _paramSqlResult;
    std::vector<std::shared_ptr<TLVConf>> fetchedTLVs;
    std::vector<std::shared_ptr<Param>> fetchedParams;
    void getAllTLVs();
    std::shared_ptr<TLVConf> getTLVByNameAux(std::string tlvName, u_int32_t port, int32_t module);
    std::shared_ptr<TLVConf> getTLVByNameOnlyAux(std::string tlvName);
    std::shared_ptr<TLVConf> getAndSetTLVByNameAuxNotInitialized(string tlv_name, u_int32_t port, int32_t module);
    std::shared_ptr<TLVConf> getTLVByIndexAndClassAux(u_int32_t id, TLVClass c);
    std::shared_ptr<TLVConf> getTLVByName(std::string tlvName, u_int32_t port, int32_t module);
    std::shared_ptr<TLVConf> getDependencyTLVByName(string tlvName, u_int32_t cTLVPort, int32_t cTLVModule);
    std::shared_ptr<TLVConf> getAndCreateTLVByName(std::string tlvName, u_int32_t port, int32_t module);
    std::shared_ptr<TLVConf> getTLVByParamMlxconfigName(std::string mlxconfigName, u_int32_t index, mfile* mf);
    std::shared_ptr<TLVConf> findTLVInExisting(std::string mlxconfigName,
                                               std::string noPortModuleMlxcfgName,
                                               u_int32_t port,
                                               u_int32_t index,
                                               int32_t module);
    void findTLVInDB(std::string mlxconfigName, u_int32_t index);
    std::shared_ptr<TLVConf> getTLVByIndexAndClass(u_int32_t id, TLVClass c);
    void fillInRelevantParamsOfTlv(std::shared_ptr<TLVConf> tlv, u_int32_t port, int32_t module);
    static tuple<string, int, int> getMlxconfigNamePortModule(std::string mlxconfigName, mfile* mf);
    static tuple<string, int> splitMlxcfgNameAndPortOrModule(std::string mlxconfigName, SPLITBY splitBy, mfile* mf);
    void execSQL(sqlite3_callback f, void* obj, const char* stat, ...);
};

#endif
