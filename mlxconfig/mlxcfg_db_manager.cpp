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

#include <stdarg.h>
#include <stdio.h>

// #define NDEBUG //uncomment in order to disable asserts
#include <assert.h>

#include <ext_libs/sqlite/sqlite3.h>
#include "mlxcfg_db_manager.h"
#include "mlxcfg_utils.h"
#include <memory>
// clang-format off
#define SQL_SELECT_ALL_TLVS \
    "SELECT * FROM tlvs"

#define SQL_SELECT_ALL_PARAMS \
    "SELECT * FROM params"

MlxcfgDBManager::MlxcfgDBManager(string dbName, mfile* mf) :
    _dbName(dbName), _db(NULL), _supportedVersion(0x0), _callBackErr(""), _isAllFetched(false), _paramSqlResult(NULL), _mf(mf)
{
    openDB();
    getAllTLVs();
}

MlxcfgDBManager::~MlxcfgDBManager()
{
    for (std::vector<std::shared_ptr<TLVConf>>::iterator it = _fetchedTLVs.begin(); it != _fetchedTLVs.end(); ++it)
    {
        it->reset();
    }
    for (std::vector<std::shared_ptr<Param>>::iterator it = _fetchedParams.begin(); it != _fetchedParams.end(); ++it)
    {
        it->reset();
    }
    for (auto it = _tlvMap.begin(); it != _tlvMap.end(); ++it)
    {
        if (it->second)
        {
            it->second.reset();
        }
    }
    _tlvMap.clear();

    if (!_db)
    {
        return;
    }
    sqlite3_close(_db);
}

void MlxcfgDBManager::updateMapWithHostPF(u_int8_t hostId, u_int8_t pfIndex)
{
    for (auto it = _tlvMap.begin(); it != _tlvMap.end(); ++it)
    {
        if (it->second->isHostTargetClass())
        {
            it->second->_hostId = hostId;
            it->second->_pfIndex = pfIndex;
            it->second->_isHostIdValid = true;
        }
    }
}

void MlxcfgDBManager::checkDBVersion()
{
    int rc;
    sqlite3_stmt* stmt = NULL;
    unsigned int dbVersion = 0x0;

    sqlite3_prepare_v2(_db, "PRAGMA user_version", -1, &stmt, NULL);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        if (strcmp(sqlite3_column_name(stmt, 0), "user_version") == 0)
        {
            dbVersion = (unsigned int)sqlite3_column_int(stmt, 0);
            break;
        }
    }
    sqlite3_finalize(stmt); // releasing allocated stmt
    if (dbVersion != _supportedVersion)
    {
        throw MlxcfgException("Unsupported database version");
    }
}

void MlxcfgDBManager::openDB()
{
    if (!isDBFileExists(_dbName))
    {
        throw MlxcfgException("Database file %s does not exist", _dbName.c_str());
    }

    if (sqlite3_open_v2(_dbName.c_str(), &_db, SQLITE_OPEN_READONLY, 0))
    {
        string e = sqlite3_errmsg(_db);
        sqlite3_close(_db);
        _db = NULL;
        throw MlxcfgException("SQL Error when opening DB: %s", e.c_str());
    }

    checkDBVersion();

    return;
}

void MlxcfgDBManager::execSQL(sqlite3_callback f, void* obj, const char* stat, ...)
{
    va_list vl;
    char sql[1024];
    char* zErrMsg = 0;

    va_start(vl, stat);
    vsnprintf(sql, sizeof(sql), stat, vl);
    va_end(vl);

    if (sqlite3_exec(_db, sql, f, obj, &zErrMsg) != SQLITE_OK)
    {
        string e = zErrMsg;
        sqlite3_free(zErrMsg);
        if (_callBackErr.empty())
        {
            throw MlxcfgException("Cannot execute %s, %s", sql, e.c_str());
        }
        else
        {
            throw MlxcfgException(_callBackErr.c_str());
        }
    }
}

int MlxcfgDBManager::selectTLVCallBack(void* object, int argc, char** argv, char** azColName)
{
    MlxcfgDBManager* dbManager = reinterpret_cast<MlxcfgDBManager*>(object); // TODOO check this casting

    try
    {
        std::shared_ptr<TLVConf> tlv = make_shared<TLVConf>(argc, argv, azColName);
        dbManager->_fetchedTLVs.push_back(tlv);
    }
    catch (MlxcfgException& e)
    {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }

    return 0;
}


int MlxcfgDBManager::selectParamCallBack(void* object, int argc, char** argv, char** azColName)
{
    MlxcfgDBManager* dbManager = reinterpret_cast<MlxcfgDBManager*>(object);

    try
    {
        std::shared_ptr<Param> param = std::make_shared<Param>(argc, argv, azColName);
        dbManager->_fetchedParams.push_back(param);
    }
    catch (MlxcfgException& e)
    {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }
    // printf("-D- Added new Param = %s\n", param->_name.c_str());
    return 0;
}

void MlxcfgDBManager::fillMapWithFetchedTLVs(mfile* mf)
{
    for(size_t j = 0; j < _fetchedTLVs.size(); j++)
    {
        if(_fetchedTLVs[j]->isPortTargetClass())
        {
            for(int k = 1; k <= TLVConf::getMaxPort(mf); k++)
            {
                std::shared_ptr<TLVConf> tlv = make_shared<TLVConf>(*_fetchedTLVs[j]);
                tlv->_port = k;
                _tlvMap[make_tuple(tlv->_name, tlv->_port, tlv->_module)] = tlv;
            }
        }
        else if(_fetchedTLVs[j]->isModuleTargetClass())
        {
            for(int k = 0; k <= TLVConf::getMaxModule(); k++)
            {
                std::shared_ptr<TLVConf> tlv = make_shared<TLVConf>(*_fetchedTLVs[j]);
                tlv->_module = k;
                _tlvMap[make_tuple(tlv->_name, tlv->_port, tlv->_module)] = tlv;
            }
        }
        else
        {
            std::shared_ptr<TLVConf> tlv = make_shared<TLVConf>(*_fetchedTLVs[j]);
            _tlvMap[make_tuple(tlv->_name, tlv->_port, tlv->_module)] = tlv;
        }
    }
}

/*
    Fill in TLV.params vector
    we assume that params table is grouped by tlv name
*/
void MlxcfgDBManager::fillMapWithFetchedParams(mfile* mf)
{
    size_t i = 0, j = 0;
    while (j < _fetchedTLVs.size() && i < _fetchedParams.size())
    {
        if (_fetchedParams[i]->_tlvName == _fetchedTLVs[j]->_name)
        {
            if(_fetchedParams[i]->_mlxconfigName != "")
            {
                _mlxconfigNameToTlv[_fetchedParams[i]->_mlxconfigName] = _fetchedParams[i]->_tlvName;
            }

            if(_fetchedTLVs[j]->isPortTargetClass())
            {
                for(int k = 1; k <= TLVConf::getMaxPort(mf); k++)
                {
                    std::shared_ptr<Param> pTemplate = make_shared<Param>(*_fetchedParams[i]);
                    pTemplate->_port = k;
                    if(pTemplate->_mlxconfigName != "")
                    {
                        pTemplate->_mlxconfigName += "_P" + to_string(k);
                    }
                    auto tlvKey = make_tuple(pTemplate->_tlvName, pTemplate->_port, pTemplate->_module);
                    if (_tlvMap.count(tlvKey) == 0) {
                        throw MlxcfgException("Parameter with TLV name '%s', port %d, module %d does not have a corresponding TLV in _tlvMap", 
                                              pTemplate->_tlvName.c_str(), pTemplate->_port, pTemplate->_module);
                    }
                    // Push distinct deep clones for default/current/next
                    _tlvMap[tlvKey]->_paramsDefault.push_back(pTemplate->cloneDeep());
                    _tlvMap[tlvKey]->_paramsCurrent.push_back(pTemplate->cloneDeep());
                    _tlvMap[tlvKey]->_paramsNext.push_back(pTemplate->cloneDeep());
                }
            }
            else if(_fetchedTLVs[j]->isModuleTargetClass())
            {
                for(int k = 0; k <= TLVConf::getMaxModule(); k++)
                {
                    std::shared_ptr<Param> pTemplate = make_shared<Param>(*_fetchedParams[i]);
                    pTemplate->_module = k;
                    if(pTemplate->_mlxconfigName != "")
                    {
                        pTemplate->_mlxconfigName += "_M" + to_string(k);
                    }
                    auto tlvKey = make_tuple(pTemplate->_tlvName, pTemplate->_port, pTemplate->_module);
                    if (_tlvMap.count(tlvKey) == 0) {
                        throw MlxcfgException("Parameter with TLV name '%s', port %d, module %d does not have a corresponding TLV in _tlvMap", 
                                              pTemplate->_tlvName.c_str(), pTemplate->_port, pTemplate->_module);
                    }
                    _tlvMap[tlvKey]->_paramsDefault.push_back(pTemplate->cloneDeep());
                    _tlvMap[tlvKey]->_paramsCurrent.push_back(pTemplate->cloneDeep());
                    _tlvMap[tlvKey]->_paramsNext.push_back(pTemplate->cloneDeep());
                }
            }
            else
            {
                std::shared_ptr<Param> pTemplate = make_shared<Param>(*_fetchedParams[i]);
                auto tlvKey = make_tuple(pTemplate->_tlvName, pTemplate->_port, pTemplate->_module);
                if (_tlvMap.count(tlvKey) == 0) {
                    throw MlxcfgException("Parameter with TLV name '%s', port %d, module %d does not have a corresponding TLV in _tlvMap", 
                                          pTemplate->_tlvName.c_str(), pTemplate->_port, pTemplate->_module);
                }
                _tlvMap[tlvKey]->_paramsDefault.push_back(pTemplate->cloneDeep());
                _tlvMap[tlvKey]->_paramsCurrent.push_back(pTemplate->cloneDeep());
                _tlvMap[tlvKey]->_paramsNext.push_back(pTemplate->cloneDeep());
            }
            i++;
        }
        else
        {
            j++; // move to next tlv
        }
    }
    if (j >= _fetchedTLVs.size() && i < _fetchedParams.size())
    {
        throw MlxcfgException("A parameter without a TLV configuration: %s", _fetchedParams[i]->_name.c_str());
    }
}

void MlxcfgDBManager::getAllTLVs()
{
    if (_isAllFetched)
    {
        return;
    }

    // fetch from db all tlvs
    execSQL(selectTLVCallBack, this, SQL_SELECT_ALL_TLVS);

    // fetch from db all params
    execSQL(selectParamCallBack, this, SQL_SELECT_ALL_PARAMS);

    fillMapWithFetchedTLVs(_mf);

    //the _tlvMap is now filled with all the tlvs including port and module duplicates,
    fillMapWithFetchedParams(_mf);

    _isAllFetched = true;
}

std::shared_ptr<TLVConf> MlxcfgDBManager::getTLVByName(string tlv_name, u_int32_t port, int32_t tlvModule)
{
    auto tlvKey = make_tuple(tlv_name, port, tlvModule);
    if (_tlvMap.count(tlvKey) == 0) {
        throw MlxcfgException("TLV with name '%s', port %d, module %d does not exist", 
                              tlv_name.c_str(), port, tlvModule);
    }
    return _tlvMap[tlvKey];
}

std::shared_ptr<TLVConf> MlxcfgDBManager::getCloneTLVByName(string tlv_name, u_int32_t port, int32_t tlvModule)
{
    auto tlvKey = make_tuple(tlv_name, port, tlvModule);
    if (_tlvMap.count(tlvKey) == 0) {
        throw MlxcfgException("TLV with name '%s', port %d, module %d does not exist", 
                              tlv_name.c_str(), port, tlvModule);
    }
    return _tlvMap[tlvKey]->cloneDeep();
}

std::shared_ptr<TLVConf> MlxcfgDBManager::getFetchedTLVByName(string tlv_name)
{
    for (std::vector<std::shared_ptr<TLVConf>>::iterator it = _fetchedTLVs.begin(); it != _fetchedTLVs.end(); ++it)
    {
        if ((*it)->_name == tlv_name)
        {
            return (*it);
        }
    }
    return NULL;
}

std::shared_ptr<TLVConf> MlxcfgDBManager::getDependencyTLVByName(string tlvName, u_int32_t cTLVPort, int32_t cTLVModule)
{
    std::shared_ptr<TLVConf> dependendTLV = getFetchedTLVByName(tlvName);
    if (!dependendTLV)
    {
        throw MlxcfgException("TLV '%s' does not exist", tlvName.c_str());
    }
    if ((dependendTLV->_tlvClass == TLVClass::Physical_Port) || (dependendTLV->_tlvClass == TLVClass::Module))
    {
        return getTLVByName(tlvName, cTLVPort, cTLVModule); // get TLV with same port and module as the requester TLV
    }
    else // this is not port / module related tlv, ignore the requeter port/module (for cross class dependency)
    {
        return getTLVByName(tlvName, 0, -1);
    }
}

std::shared_ptr<TLVConf> MlxcfgDBManager::getTLVByIdAndClass(u_int32_t id, TLVClass c)
{
    for (std::vector<std::shared_ptr<TLVConf>>::iterator it = _fetchedTLVs.begin(); it != _fetchedTLVs.end(); ++it)
    {
        if ((*it)->_id == id && (*it)->_tlvClass == c)
        {
            if((*it)->_tlvClass == Physical_Port)
            {
                return getTLVByName((*it)->_name, 1, -1);
            }
            else if((*it)->_tlvClass == Module){
                return getTLVByName((*it)->_name, 0, 0);
            }
            else
            {
                return getTLVByName((*it)->_name, (*it)->_port, (*it)->_module);
            }
        }
    }
    return NULL;
}

bool MlxcfgDBManager::isParamMlxconfigNameExist(std::string mlxconfigName)
{
    return _mlxconfigNameToTlv.count(mlxconfigName) > 0;

}

tuple<string, int> MlxcfgDBManager::splitMlxcfgNameAndPortOrModule(std::string mlxconfigName, SPLITBY splitBy, mfile* mf)
{
    char* ending = (char*)" ";
    int maxNum = 0;
    int minNum = 0;
    char* ending_position = nullptr;
    char* last_ending_position = nullptr;
    if (splitBy == PORT)
    {
        ending = (char*)"_P";
        maxNum = TLVConf::getMaxPort(mf);
        minNum = 0;
    }
    else
    {
        ending = (char*)"_M";
        maxNum = TLVConf::getMaxModule();
        minNum = -1;
    }
    int port_num = minNum;
    char* mlxconfigName_char = (char*)mlxconfigName.c_str();
    ending_position = strstr(mlxconfigName_char, ending);
    while (ending_position != nullptr)
    {
        last_ending_position = ending_position;
        ending_position = strstr(last_ending_position + strlen(ending), ending);
    }
    if (last_ending_position != nullptr)
    {
        int index = last_ending_position - mlxconfigName_char;
        string endingStr = mlxconfigName.substr(index + strlen(ending), mlxconfigName.length() - index);
        string newMlxconfigName = mlxconfigName;
        newMlxconfigName.resize(index);
        try
        {
            port_num = std::stoi(endingStr);
        }
        catch (const std::exception& e)
        {
            return make_tuple(mlxconfigName, minNum);
        }
        if (minNum < port_num && port_num <= maxNum)
        {
            return make_tuple(newMlxconfigName, port_num);
        }
        return make_tuple(mlxconfigName, minNum);
    }
    return make_tuple(mlxconfigName, minNum);
}

tuple<string, int, int> MlxcfgDBManager::getMlxconfigNamePortModule(string mlxconfigName, mfile* mf)
{
    u_int32_t port = 0;
    int32_t tlvModule = -1;
    auto namePortTuple = splitMlxcfgNameAndPortOrModule(mlxconfigName, PORT, mf);
    auto nameModuleTuple = splitMlxcfgNameAndPortOrModule(mlxconfigName, MODULE, mf);
    if (get<1>(namePortTuple) != 0)
    {
        port = get<1>(namePortTuple);
        mlxconfigName = get<0>(namePortTuple);
    }
    else if (get<1>(nameModuleTuple) != -1)
    {
        tlvModule = get<1>(nameModuleTuple);
        mlxconfigName = get<0>(nameModuleTuple);
    }

    return make_tuple(mlxconfigName, port, tlvModule);
}


std::shared_ptr<TLVConf>
  MlxcfgDBManager::getTLVByParamMlxconfigNameAndIndex(std::string mlxconfigName, u_int32_t index, mfile* mf)
  {
    string newName = getConfigNameWithSuffixByInterval(mlxconfigName, index);
    try
    {
        return getTLVByParamMlxconfigName(newName, mf);
    }
    catch (MlxcfgException& e)
    {
        throw MlxcfgException("Failed to find Param / index out of range: %s[%d]", mlxconfigName.c_str(), index);
    }
  }

std::shared_ptr<TLVConf>
  MlxcfgDBManager::getTLVByParamMlxconfigName(std::string mlxconfigName, mfile* mf)
{
    string tlvName = "";
    auto ret = this->getMlxconfigNamePortModule(mlxconfigName, mf);
    string mlxconfigNameNoPortModuleName = get<0>(ret);
    u_int32_t port = get<1>(ret);
    int32_t tlvModule = get<2>(ret);

    if(_mlxconfigNameToTlv.find(mlxconfigNameNoPortModuleName) != _mlxconfigNameToTlv.end())
    {
        return getTLVByName(_mlxconfigNameToTlv[mlxconfigNameNoPortModuleName], port, tlvModule);
    }
    throw MlxcfgException("Failed to find Param / TLV with name '%s' port %d module %d", mlxconfigName.c_str(), port, tlvModule);
}


inline bool MlxcfgDBManager::isDBFileExists(const std::string& name)
{
    if (FILE* file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}
