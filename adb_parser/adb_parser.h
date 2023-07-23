/*
 * Copyright (c) 2012-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  Version: $Id$
 */
/*************************** Adb ***************************/
#ifndef ADB_ADB_H
#define ADB_ADB_H

class LogFile;

#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include "adb_expr.h"
#include "adb_xmlCreator.h"

#include <string>
#include <map>
#include <vector>
#include <exception>
#include <list>
#include <common/compatibility.h>
#include "adb_expr.h"
#include "adb_node.h"
#include "adb_field.h"
#include "adb_exceptionHolder.h"
#include "adb_logfile.h"
#include "adb_config.h"
#include "adb_instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <list>
#include <stdexcept>
#include "adb_xmlCreator.h"
#include "adb_condition.h"

#ifdef __WIN__
#include <process.h>
#define OS_PATH_SEP "\\"
#else
#define OS_PATH_SEP "/"
#endif

using namespace std;

#if defined(__MINGW32__) || defined(__MINGW64__)
#define PRINTF_FORMAT __MINGW_PRINTF_FORMAT
#else
#define PRINTF_FORMAT printf
#endif

class AdbInstance;
class AdbField;

using namespace xmlCreator;
using namespace std;

struct IncludeFileInfo;
typedef map<string, IncludeFileInfo> IncludeFileMap;
typedef map<string, string> AttrsMap;
typedef map<string, AdbNode*> NodesMap;
typedef vector<AdbConfig*> ConfigList;
typedef map<string, AttrsMap> InstanceAttrs;
typedef map<string, vector<string> > ExceptionsMap;

struct IncludeFileInfo
{
    string fullPath;
    string includedFromFile;
    int includedFromLine;
};

class Adb
{
public:
    // Methods
    Adb();
    ~Adb();
    void raiseException(bool allowMultipleExceptions, string exceptionTxt, const string expType);
    // strict union means:
    //   1- dwrod aligned unions
    //   2- contains nodes only
    //   3- check node size vs instance size
    bool loadFromString(const char* adbContents,
                        bool addReserved = false,
                        bool evalExpr = false,
                        bool strict = true,
                        bool enforceExtraChecks = false);
    bool load(string fname,
              bool addReserved = false,
              bool evalExpr = false,
              bool strict = true,
              string includePath = "",
              string includeDir = "",
              bool enforceExtraChecks = false,
              bool getAllExceptions = false,
              string logFile = "",
              bool checkDsAlign = false,
              bool enforceGuiChecks = false,
              bool force_pad_32 = false);
    string toXml(vector<string> nodeNames = vector<string>(),
                 bool addRootNode = false,
                 string rootName = "MainNode",
                 string addPrefix = "");

    AdbInstance* addMissingNodes(int depth, bool allowMultipleExceptions);
    AdbInstance* createLayout(string rootNodeName,
                              bool isExprEval = false,
                              int depth = -1, /* -1 means instantiate full tree */
                              bool ignoreMissingNodes = false,
                              bool getAllExceptions = false);
    vector<string> getNodeDeps(string nodeName);
    void add_include(string fileName, string filePath, string included_from, int lineNumber);
    string getLastError();

    void fetchAdbExceptionsMap(ExceptionsMap otherMap);
    // excpetionType [FATAL:0, ERROR:1, WARNING:2]
    void insertNewException(const string exceptionType, string exceptionTxt);
    string printAdbExceptionMap();

    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    string version;
    NodesMap nodesMap;
    ConfigList configs;
    string rootNode;
    bool bigEndianArr;
    bool singleEntryArrSupp;
    InstanceAttrs instAttrs; // Key is instance's Adabe full path, value is attribute map
    string srcDocName;
    string srcDocVer;
    LogFile* _logFile;

    /* For internal use */
public:
    vector<string> includePaths;
    std::map<string, string> defines_map;
    string mainFileName;
    IncludeFileMap includedFiles;
    vector<string> warnings;
    ExceptionsMap adbExceptionMap;

private:
    bool createInstance(AdbField* fieldDesc,
                        AdbInstance* parent,
                        map<string, string> vars,
                        bool isExprEval,
                        int depth,
                        bool ignoreMissingNodes = false,
                        bool getAllExceptions = false);
    string evalExpr(string expr, AttrsMap* vars);
    bool checkInstSizeConsistency(bool getAllExceptions = false);

private:
    string _lastError;
    bool _checkDsAlign;
    bool _enforceGuiChecks;
    list<AdbInstance*> _unionSelectorEvalDeffered;
    list<AdbInstance*> _conditionInstances;
    list<AdbInstance*> _conditionalArrays;
    void checkInstanceOffsetValidity(AdbInstance* inst, AdbInstance* parent, bool allowMultipleExceptions);
    void throwExeption(bool allowMultipleExceptions, string exceptionTxt, string addedMsgMultiExp);
};

#endif
