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
 *
 * MlxconfigFactory.h
 *
 *  Created on: May 24, 2016
 *      Author: ahmads
 */

#include <stdarg.h>
#include <stdio.h>

//#define NDEBUG //uncomment in order to enable asserts
#include <assert.h>

#include <sqlite3.h>
#include "mlxcfg_db_manager.h"
#include "mlxcfg_utils.h"

using namespace std;

#define SQL_SELECT_ALL_TLVS \
    "SELECT * FROM tlvs"

#define SQL_SELECT_ALL_PARAMS \
    "SELECT * FROM params"

#define SQL_SELECT_TLV_BY_NAME_AND_PORT \
    "SELECT * FROM tlvs WHERE name='%s' and port='%d'"

#define SQL_SELECT_TLV_BY_INDEX_AND_CLASS \
    "SELECT * FROM tlvs WHERE id=%d and class=%d"

#define SQL_SELECT_PARAMS_BY_TLV_NAME_AND_PORT \
    "SELECT * FROM params WHERE tlv_name='%s' and port='%d'"

#define SQL_SELECT_PARAM_BY_MLXCONFIG_NAME \
    "SELECT * FROM params WHERE mlxconfig_name='%s'"

MlxcfgDBManager::MlxcfgDBManager(string dbName) : _dbName(dbName),
    _db(NULL), _supportedVersion(0x0), _callBackErr(""), _isAllFetched(false),
    _paramSqlResult(NULL)
{
    openDB();
}

MlxcfgDBManager::~MlxcfgDBManager()
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it) {
        delete *it;
    }
    VECTOR_ITERATOR(Param*, fetchedParams, it) {
        delete *it;
    }
    if (!_db) {
        return;
    }
    sqlite3_close(_db);
}

void MlxcfgDBManager::checkDBVersion()
{
    int rc;
    sqlite3_stmt *stmt = NULL;
    unsigned int dbVersion = 0x0;

    sqlite3_prepare_v2(_db, "PRAGMA user_version", -1, &stmt, NULL);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        if (strcmp(sqlite3_column_name(stmt, 0), "user_version") == 0) {
            dbVersion = (unsigned int)sqlite3_column_int(stmt, 0);
            break;
        }
    }

    if (dbVersion != _supportedVersion) {
        throw MlxcfgException("Unsupported database version");
    }
}

void MlxcfgDBManager::openDB()
{

    if (!isDBFileExists(_dbName)) {
        throw MlxcfgException("Database file %s does not exist", _dbName.c_str());
    }

    if (sqlite3_open_v2(_dbName.c_str(), &_db, SQLITE_OPEN_READONLY, 0)) {
        string e = sqlite3_errmsg(_db);
        sqlite3_close(_db);
        _db = NULL;
        throw MlxcfgException("SQL Error when opening DB: %s", e.c_str());
    }

    checkDBVersion();

    return;
}

void MlxcfgDBManager::execSQL(sqlite3_callback f, void *obj,
                              const char *stat, ...)
{
    va_list vl;
    char sql[1024];
    char *zErrMsg = 0;

    va_start(vl, stat);
    vsnprintf(sql, sizeof(sql), stat, vl);
    va_end(vl);

    if (sqlite3_exec(_db, sql, f, obj, &zErrMsg) != SQLITE_OK) {
        string e = zErrMsg;
        sqlite3_free(zErrMsg);
        if (_callBackErr.empty()) {
            throw MlxcfgException("Cannot execute %s, %s", sql, e.c_str());
        } else {
            throw MlxcfgException(_callBackErr.c_str());
        }
    }
}

int MlxcfgDBManager::selectTLVCallBack(void *object, int argc, char **argv, char **azColName)
{

    MlxcfgDBManager *dbManager = reinterpret_cast<MlxcfgDBManager*>(object); //TODOO check this casting

    try {
        TLVConf *tlv = new TLVConf(argc, argv, azColName);
        dbManager->fetchedTLVs.push_back(tlv);
    } catch (MlxcfgException& e) {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }

    return 0;
}

int MlxcfgDBManager::selectAndCreateNewTLVCallBack(void *object, int argc, char **argv, char **azColName)
{

    TLVConf **tlv = reinterpret_cast<TLVConf**>(object);

    try {
        *tlv = new TLVConf(argc, argv, azColName);
    } catch (MlxcfgException& /*e*/) {
        return SQLITE_ABORT;
    }

    return 0;
}

int MlxcfgDBManager::selectAndCreateParamCallBack(void *object, int argc, char **argv,
                                                  char **azColName)
{
    TLVConf *tlv = reinterpret_cast<TLVConf*>(object);

    try {
        Param *param = new Param(argc, argv, azColName);
        tlv->_params.push_back(param);
    } catch (MlxcfgException& e) {
        return SQLITE_ABORT;
    }

    return 0;
}

int MlxcfgDBManager::selectParamCallBack(void *object, int argc, char **argv,
                                         char **azColName)
{

    MlxcfgDBManager *dbManager = reinterpret_cast<MlxcfgDBManager*>(object); //TODOO check this casting

    try {
        Param *param = new Param(argc, argv, azColName);
        dbManager->fetchedParams.push_back(param);
    } catch (MlxcfgException& e) {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }
    //printf("-D- Added new Param = %s\n", param->_name.c_str());
    return 0;
}

int MlxcfgDBManager::selectParamByMlxconfigNameCallBack(void *object, int argc,
                                                        char **argv, char **azColName)
{
    MlxcfgDBManager *dbManager = reinterpret_cast<MlxcfgDBManager*>(object);
    try {
        dbManager->_paramSqlResult = new Param(argc, argv, azColName);
    } catch (MlxcfgException& e) {
        dbManager->_callBackErr = e._err;
        return SQLITE_ABORT;
    }
    return 0;
}

void MlxcfgDBManager::getAllTLVs()
{
    size_t i = 0, j = 0;

    if (_isAllFetched) {
        return;
    }

    //fetch from db all tlvs
    execSQL(selectTLVCallBack, this, SQL_SELECT_ALL_TLVS);

    //fetch from db all params
    execSQL(selectParamCallBack, this, SQL_SELECT_ALL_PARAMS);

    /*
       Fill in TLV.params vector
       we assume that params table is grouped by tlv name
     */
    while (j < fetchedTLVs.size() && i < fetchedParams.size()) {
        Param *p = fetchedParams[i];
        if (p->_tlvName == fetchedTLVs[j]->_name &&
            p->_port == fetchedTLVs[j]->_port) {
            fetchedTLVs[j]->_params.push_back(p);
            i++;//move to next parameter
        } else {
            j++;//move to next tlv
        }
    }
    if (j >= fetchedTLVs.size() && i < fetchedParams.size()) {
        throw MlxcfgException("A parameter without a TLV configuration: %s", fetchedParams[i]->_name.c_str());
    }
    //TODO check if there is a tlv that does not have params

    _isAllFetched = true;
}

TLVConf* MlxcfgDBManager::getTLVByNameAux(string n, u_int8_t port)
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it) {
        TLVConf *t = *it;
        if (t->_name == n && t->_port == port) {
            return t;
        }
    }
    return NULL;
}

TLVConf* MlxcfgDBManager::fetchTLVByName(string n, u_int8_t port)
{
    TLVConf *t;
    const char *nc = n.c_str();

    execSQL(selectTLVCallBack, this, SQL_SELECT_TLV_BY_NAME_AND_PORT,
            nc, port);
    t = getTLVByNameAux(n, port);
    if (!t) {
        throw MlxcfgException("The TLV configuration %s was not found", nc);
    }

    //fetch the parameters
    execSQL(selectParamCallBack, this,
            SQL_SELECT_PARAMS_BY_TLV_NAME_AND_PORT, nc, port);

    //fill in params vector of the tlv
    VECTOR_ITERATOR(Param*, fetchedParams, p) {
        if ((*p)->_tlvName == t->_name && (*p)->_port == port) {
            t->_params.push_back(*p);
        }
    }

    return t;
}

TLVConf* MlxcfgDBManager::fetchTLVByIndexAndClass(u_int32_t id, TLVClass c)
{
    TLVConf *t;

    execSQL(selectTLVCallBack, this, SQL_SELECT_TLV_BY_INDEX_AND_CLASS,
            id, c);
    t = getTLVByIndexAndClassAux(id, c);
    if (!t) {
        throw MlxcfgException("The TLV configuration with index 0x%x and class 0x%x was not found", id, c);
    }

    //fetch the parameters
    execSQL(selectParamCallBack, this,
            SQL_SELECT_PARAMS_BY_TLV_NAME_AND_PORT, t->_name.c_str(), t->_port);

    //fill in params vector of the tlv
    VECTOR_ITERATOR(Param*, fetchedParams, p) {
        if ((*p)->_tlvName == t->_name && (*p)->_port == t->_port) {
            t->_params.push_back(*p);
        }
    }

    return t;
}

TLVConf* MlxcfgDBManager::getAndCreateTLVByName(string n, u_int8_t port)
{
    TLVConf *tlv = NULL;
    const char *nc = n.c_str();

    execSQL(selectAndCreateNewTLVCallBack, &tlv, SQL_SELECT_TLV_BY_NAME_AND_PORT,
            nc, port);
    if (!tlv) {
        throw MlxcfgException("The TLV configuration %s was not found", nc);
    }

    //fetch the parameters
    execSQL(selectAndCreateParamCallBack, tlv,
            SQL_SELECT_PARAMS_BY_TLV_NAME_AND_PORT, nc, port);

    return tlv;
}

TLVConf* MlxcfgDBManager::getTLVByName(string n, u_int8_t port)
{
    TLVConf *t = NULL;

    t = getTLVByNameAux(n, port);
    if (!t) {
        t = fetchTLVByName(n, port);
    }

    return t;
}

TLVConf* MlxcfgDBManager::getTLVByIndexAndClassAux(u_int32_t id, TLVClass c)
{
    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it) {
        TLVConf *t = *it;
        if (t->_id == id && t->_tlvClass == c) {
            return t;
        }
    }
    return NULL;
}

bool MlxcfgDBManager::isParamMlxconfigNameExist(std::string n)
{
    execSQL(selectParamByMlxconfigNameCallBack, this,
        SQL_SELECT_PARAM_BY_MLXCONFIG_NAME, n.c_str());

    return (n == _paramSqlResult->_mlxconfigName);
}

TLVConf* MlxcfgDBManager::getTLVByParamMlxconfigName(std::string n, u_int32_t index)
{
    u_int32_t port;
    string tlvName;

    VECTOR_ITERATOR(TLVConf*, fetchedTLVs, it) {
        if ((*it)->findParamByMlxconfigName(n) || (*it)->findParamByMlxconfigName(n + getArraySuffixByInterval(index))) {
            return (*it);
        }
    }

    //Try to find it in DB:dd
    execSQL(selectParamByMlxconfigNameCallBack, this,
            SQL_SELECT_PARAM_BY_MLXCONFIG_NAME, n.c_str());

    // if not found try to find it with continuance array suffix
    if (!_paramSqlResult) {
        string newName = n + getArraySuffixByInterval(index);

        execSQL(selectParamByMlxconfigNameCallBack, this,
            SQL_SELECT_PARAM_BY_MLXCONFIG_NAME, newName.c_str());
    }

    if (!_paramSqlResult) {
        string suffix = "";
        if (index > 0) {
            if (isIndexedStartFromOneSupported(n)) {
                index++;
            }
            suffix = "[" + numToStr(index) + "]";
        }

        throw MlxcfgException(
                  "Unknown Parameter: %s",
            (n + suffix).c_str());
    }

    port = _paramSqlResult->_port;
    tlvName = _paramSqlResult->_tlvName;
    delete _paramSqlResult;
    _paramSqlResult = NULL;

    return fetchTLVByName(tlvName, port);
}

TLVConf* MlxcfgDBManager::getTLVByIndexAndClass(u_int32_t id, TLVClass c)
{
    TLVConf *t = NULL;

    t = getTLVByIndexAndClassAux(id, c);
    if (!t) {
        t = fetchTLVByIndexAndClass(id, c);
    }

    return t;
}

inline bool MlxcfgDBManager::isDBFileExists(const std::string& name)
{
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
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
