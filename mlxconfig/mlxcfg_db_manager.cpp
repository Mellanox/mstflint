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

#define SQL_SELECT_TLV_BY_NAME \
    "SELECT * FROM tlvs WHERE name='%s'"

#define SQL_SELECT_TLV_BY_INDEX_AND_CLASS \
    "SELECT * FROM tlvs WHERE id=%d and class=%d"

#define SQL_SELECT_PARAMS_BY_TLV_NAME \
    "SELECT * FROM params WHERE tlv_name='%s'"

#define SQL_SELECT_PARAM_BY_MLXCONFIG_NAME \
    "SELECT * FROM params WHERE mlxconfig_name='%s'"
// clang-format on
MlxcfgDBManager::MlxcfgDBManager(string dbName) :
    _dbName(dbName), _db(NULL), _supportedVersion(0x0), _callBackErr(""), _isAllFetched(false), _paramSqlResult(NULL)
{
    openDB();
}

MlxcfgDBManager::~MlxcfgDBManager()
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it) { delete *it; }

    if (!_db)
    {
        return;
    }
    sqlite3_close(_db);
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
        TLVConf* tlv = new TLVConf(argc, argv, azColName);
        dbManager->fetchedTLVs.push_back(tlv);
    }
    catch (MlxcfgException& e)
    {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }

    return 0;
}

int MlxcfgDBManager::selectAndCreateNewTLVCallBack(void* object, int argc, char** argv, char** azColName)
{
    TLVConf** tlv = reinterpret_cast<TLVConf**>(object);

    try
    {
        *tlv = new TLVConf(argc, argv, azColName);
    }
    catch (MlxcfgException& /*e*/)
    {
        return SQLITE_ABORT;
    }

    return 0;
}

int MlxcfgDBManager::selectAndCreateParamCallBack(void* object, int argc, char** argv, char** azColName)
{
    TLVConf* tlv = reinterpret_cast<TLVConf*>(object);

    try
    {
        std::shared_ptr<Param> param = std::make_shared<Param>(argc, argv, azColName);
        tlv->_params.push_back(param);
    }
    catch (MlxcfgException& e)
    {
        return SQLITE_ABORT;
    }

    return 0;
}

int MlxcfgDBManager::selectParamCallBack(void* object, int argc, char** argv, char** azColName)
{
    MlxcfgDBManager* dbManager = reinterpret_cast<MlxcfgDBManager*>(object); // TODOO check this casting

    try
    {
        std::shared_ptr<Param> param = std::make_shared<Param>(argc, argv, azColName);
        dbManager->fetchedParams.push_back(param);
    }
    catch (MlxcfgException& e)
    {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }
    // printf("-D- Added new Param = %s\n", param->_name.c_str());
    return 0;
}

int MlxcfgDBManager::selectParamByMlxconfigNameCallBack(void* object, int argc, char** argv, char** azColName)
{
    MlxcfgDBManager* dbManager = reinterpret_cast<MlxcfgDBManager*>(object);
    try
    {
        dbManager->_paramSqlResult = std::make_shared<Param>(argc, argv, azColName);
    }
    catch (MlxcfgException& e)
    {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }
    return 0;
}

void MlxcfgDBManager::getAllTLVs()
{
    size_t i = 0, j = 0;

    if (_isAllFetched)
    {
        return;
    }

    // fetch from db all tlvs
    execSQL(selectTLVCallBack, this, SQL_SELECT_ALL_TLVS);

    // fetch from db all params
    execSQL(selectParamCallBack, this, SQL_SELECT_ALL_PARAMS);

    /*
       Fill in TLV.params vector
       we assume that params table is grouped by tlv name
     */
    while (j < fetchedTLVs.size() && i < fetchedParams.size())
    {
        std::shared_ptr<Param> p = fetchedParams[i];
        if (p->_tlvName == fetchedTLVs[j]->_name && p->_port == fetchedTLVs[j]->_port &&
            p->_module == fetchedTLVs[j]->_module)
        {
            fetchedTLVs[j]->_params.push_back(p);
            i++; // move to next parameter
        }
        else
        {
            j++; // move to next tlv
        }
    }
    if (j >= fetchedTLVs.size() && i < fetchedParams.size())
    {
        throw MlxcfgException("A parameter without a TLV configuration: %s", fetchedParams[i]->_name.c_str());
    }
    // TODO check if there is a tlv that does not have params
    _isAllFetched = true;
}

TLVConf* MlxcfgDBManager::getTLVByNameAux(string tlv_name, u_int32_t port, int32_t module)
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it)
    {
        TLVConf* t = *it;
        if (t->_name == tlv_name && t->_port == port && t->_module == module)
        {
            return t;
        }
    }
    return NULL;
}

TLVConf* MlxcfgDBManager::getAndSetTLVByNameAuxNotInitialized(string tlv_name, u_int32_t port, int32_t module)
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it)
    {
        TLVConf* tlv = *it;
        if (tlv->_name == tlv_name && tlv->_port == 0 && tlv->_module == -1)
        {
            if (port != 0)
            {
                tlv->_port = port;
            }
            else if (module != -1)
            {
                tlv->_module = module;
            }
            return tlv;
        }
    }
    return NULL;
}

void MlxcfgDBManager::fillInRelevantParamsOfTlv(TLVConf* tlv, u_int32_t port, int32_t module)
{
    VECTOR_ITERATOR(std::shared_ptr<Param>, fetchedParams, p)
    {
        if ((*p)->_tlvName == tlv->_name && (*p)->_port == port && (*p)->_module == module)
        {
            tlv->_params.push_back(*p);
        }
        else if ((*p)->_tlvName == tlv->_name && (*p)->_port == 0 && (*p)->_module == -1)
        {
            if (port != 0)
            {
                (*p)->_port = port;
            }
            if (module != -1)
            {
                (*p)->_module = module;
            }
            tlv->_params.push_back(*p);
        }
    }
}

TLVConf* MlxcfgDBManager::fetchTLVByName(string tlvName, u_int32_t port, int32_t module)
{
    TLVConf* tlv;
    const char* nc = tlvName.c_str();

    execSQL(selectTLVCallBack, this, SQL_SELECT_TLV_BY_NAME, nc);
    tlv = getTLVByNameAux(tlvName, port, module);
    if (!tlv)
    {
        tlv = getAndSetTLVByNameAuxNotInitialized(tlvName, port, module);
        if (!tlv)
        {
            throw MlxcfgTLVNotFoundException(nc);
        }
    }
    // fetch the parameters
    execSQL(selectParamCallBack, this, SQL_SELECT_PARAMS_BY_TLV_NAME, nc);

    // fill in params vector of the tlv
    this->fillInRelevantParamsOfTlv(tlv, port, module);
    return tlv;
}

TLVConf* MlxcfgDBManager::fetchTLVByIndexAndClass(u_int32_t id, TLVClass c)
{
    TLVConf* t;
    execSQL(selectTLVCallBack, this, SQL_SELECT_TLV_BY_INDEX_AND_CLASS, id, c);
    t = getTLVByIndexAndClassAux(id, c);
    if (!t)
    {
        throw MlxcfgException("The TLV configuration with index 0x%x and class 0x%x was not found", id, c);
    }

    // fetch the parameters
    execSQL(selectParamCallBack, this, SQL_SELECT_PARAMS_BY_TLV_NAME, t->_name.c_str());

    // fill in params vector of the tlv
    VECTOR_ITERATOR(std::shared_ptr<Param>, fetchedParams, p)
    {
        if ((*p)->_tlvName == t->_name && (*p)->_port == t->_port)
        {
            t->_params.push_back(*p);
        }
    }

    return t;
}

TLVConf* MlxcfgDBManager::getAndCreateTLVByName(string tlvName, u_int32_t port, int32_t module)
{
    TLVConf* tlv = NULL;
    const char* nc = tlvName.c_str();

    execSQL(selectAndCreateNewTLVCallBack, &tlv, SQL_SELECT_TLV_BY_NAME, nc);
    if (!tlv)
    {
        throw MlxcfgTLVNotFoundException(nc);
    }
    if (port != 0)
    {
        tlv->_port = port;
    }
    else if (module != -1)
    {
        tlv->_module = module;
    }

    // fetch the parameters
    execSQL(selectAndCreateParamCallBack, tlv, SQL_SELECT_PARAMS_BY_TLV_NAME, nc);
    VECTOR_ITERATOR(std::shared_ptr<Param>, tlv->_params, p)
    {
        (*p)->_port = port;
        if (port != 0)
        {
            (*p)->_port = port;
        }
        else if (module != -1)
        {
            (*p)->_module = module;
        }
    }
    return tlv;
}

TLVConf* MlxcfgDBManager::getTLVByNameOnlyAux(string tlv_name)
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it)
    {
        TLVConf* t = *it;
        if (t->_name == tlv_name)
        {
            return t;
        }
    }
    return NULL;
}

TLVConf* MlxcfgDBManager::getTLVByName(string tlvName, u_int32_t port, int32_t module)
{
    TLVConf* tlv = NULL;

    tlv = getTLVByNameAux(tlvName, port, module);
    if (!tlv)
    {
        tlv = fetchTLVByName(tlvName, port, module);
    }

    return tlv;
}

TLVConf* MlxcfgDBManager::getDependencyTLVByName(string tlvName, u_int32_t cTLVPort, int32_t cTLVModule)
{
    TLVConf* dependendTLV = getTLVByNameOnlyAux(tlvName);
    if (!dependendTLV)
    {
        getAllTLVs();
        dependendTLV = getTLVByNameOnlyAux(tlvName);
        if (!dependendTLV)
        {
            // TLV not in DB
            return NULL;
        }
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

TLVConf* MlxcfgDBManager::getTLVByIndexAndClassAux(u_int32_t id, TLVClass c)
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it)
    {
        TLVConf* t = *it;
        if (t->_id == id && t->_tlvClass == c)
        {
            return t;
        }
    }
    return NULL;
}

bool MlxcfgDBManager::isParamMlxconfigNameExist(std::string mlxconfigName)
{
    execSQL(selectParamByMlxconfigNameCallBack, this, SQL_SELECT_PARAM_BY_MLXCONFIG_NAME, mlxconfigName.c_str());

    return (mlxconfigName == _paramSqlResult->_mlxconfigName);
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

TLVConf* MlxcfgDBManager::findTLVInExisting(std::string mlxconfigName,
                                            std::string noPortModuleMlxcfgName,
                                            u_int32_t port,
                                            u_int32_t index,
                                            int32_t module)
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it)
    {
        if (((port != 0 || module != -1) &&
             (*it)->findParamByMlxconfigNamePortModule(noPortModuleMlxcfgName, port, module)) ||
            (*it)->findParamByMlxconfigNamePortModule(mlxconfigName, port, module) ||
            (*it)->findParamByMlxconfigNamePortModule(mlxconfigName + getArraySuffixByInterval(index), port, module))
        {
            if (port == (*it)->_port && module == (*it)->_module)
            {
                return (*it);
            }
        }
    }
    return NULL;
}

void MlxcfgDBManager::findTLVInDB(string mlxconfigName, u_int32_t index)
{
    // Try to find it in DB:dd
    execSQL(selectParamByMlxconfigNameCallBack, this, SQL_SELECT_PARAM_BY_MLXCONFIG_NAME, mlxconfigName.c_str());

    // if not found try to find it with continuance array suffix
    if (!_paramSqlResult)
    {
        string newName = mlxconfigName + getArraySuffixByInterval(index);
        execSQL(selectParamByMlxconfigNameCallBack, this, SQL_SELECT_PARAM_BY_MLXCONFIG_NAME, newName.c_str());
    }

    if (!_paramSqlResult)
    {
        string suffix = "";
        if (index > 0)
        {
            if (isIndexedStartFromOneSupported(mlxconfigName))
            {
                index++;
            }
            suffix = "[" + numToStr(index) + "]";
        }

        throw MlxcfgException("Unknown Parameter: %s", (mlxconfigName + suffix).c_str());
    }
}

tuple<string, int, int> MlxcfgDBManager::getMlxconfigNamePortModule(string mlxconfigName, mfile* mf)
{
    u_int32_t port = 0;
    int32_t module = -1;
    auto namePortTuple = splitMlxcfgNameAndPortOrModule(mlxconfigName, PORT, mf);
    auto nameModuleTuple = splitMlxcfgNameAndPortOrModule(mlxconfigName, MODULE, mf);
    if (get<1>(namePortTuple) != 0)
    {
        port = get<1>(namePortTuple);
        mlxconfigName = get<0>(namePortTuple);
    }
    else if (get<1>(nameModuleTuple) != -1)
    {
        module = get<1>(nameModuleTuple);
        mlxconfigName = get<0>(nameModuleTuple);
    }

    return make_tuple(mlxconfigName, port, module);
}

TLVConf* MlxcfgDBManager::getTLVByParamMlxconfigName(std::string mlxconfigName, u_int32_t index, mfile* mf)
{
    string tlvName = "";

    auto ret = this->getMlxconfigNamePortModule(mlxconfigName, mf);
    string mlxconfigNameNoPortModuleName = get<0>(ret);
    u_int32_t port = get<1>(ret);
    int32_t module = get<2>(ret);
    TLVConf* existingTlv = findTLVInExisting(mlxconfigName, mlxconfigNameNoPortModuleName, port, index, module);
    if (existingTlv != NULL && existingTlv->_port == port && existingTlv->_module == module)
    {
        return existingTlv;
    }
    mlxconfigName = mlxconfigNameNoPortModuleName;
    findTLVInDB(mlxconfigName, index);

    tlvName = _paramSqlResult->_tlvName;
    _paramSqlResult.reset();
    _paramSqlResult = NULL;
    TLVConf* tlv = fetchTLVByName(tlvName, port, module);
    tlv->CheckModuleAndPortMatchClass(module, port, mlxconfigName);
    return tlv;
}

TLVConf* MlxcfgDBManager::getTLVByIndexAndClass(u_int32_t id, TLVClass c)
{
    TLVConf* t = NULL;

    t = getTLVByIndexAndClassAux(id, c);
    if (!t)
    {
        t = fetchTLVByIndexAndClass(id, c);
    }

    return t;
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

/*
   string MlxcfgDBManagerException::getMessageByCode(ExceptionCode c) const{
    switch(c) {
        case DB_FILE_DOES_NOT_EXIST:
            return "Database file does not exist";
        case SQL_ERROR:
            return "SQL Error: " + _info;
        case PARAM_DOES_NOT_BELONG_TO_TLV:
            return "A parameter does not belong to any TLV Configuration: " + _info;
        case UNKNOWN:
        default:
            return "Unknown";
    }
   }*/
