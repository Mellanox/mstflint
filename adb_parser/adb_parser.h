/* 
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef ADB_PARSER_H
#define ADB_PARSER_H

#include <string>
#include <map>
#include <vector>
#include <exception>
#include <list>
#include <common/compatibility.h>
#include "adb_expr.h"

using namespace std;

//#define printf win32_printf
#if defined(__MINGW32__) || defined(__MINGW64__)
#define PRINTF_FORMAT __MINGW_PRINTF_FORMAT
#else
#define PRINTF_FORMAT printf
#endif

/*************************** AdbException ***************************/
class AdbException: public std::exception {
public:
    // Methods
    AdbException();
    AdbException(const char *msg, ...) __attribute__((format(__printf__, 2, 3)));
    AdbException(string msg);
    virtual ~AdbException() throw ();
    virtual const char* what() const throw ();
    virtual string what_s() const;

private:
    string _msg;
};

/*************************** LogFile ***************************/
class LogFile {
public:
    LogFile();
    void init(string logFileName, bool allowMultipleExceptions);
    ~LogFile();
    void appendLogFile(string adbFileName);
private:
    FILE *_logFile;
};

/*************************** AdbProgress ***************************/
class AdbProgress {
public:
    virtual ~AdbProgress() {
    }
    ;
    virtual void progress(int prog = 0, int total = 0) {
        (void) prog;
        (void) total;
    }
    ;
};

/*************************** AdbNode ***************************/
class AdbField;
typedef map<string, string> AttrsMap;
typedef vector<AdbField*> FieldsList;
class AdbNode {
public:
    // Methods
    AdbNode();
    ~AdbNode();
    string toXml(const string& addPrefix);

    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    string name;
    u_int32_t size; // in bits
    bool isUnion;
    string desc;
    FieldsList fields;
    FieldsList condFields; // Field that weren't instantiated due to not satisfied condition
    AttrsMap attrs;

    // defined in
    string fileName;
    int lineNumber;

    // FOR USER USAGE
    void *userData;
};

/*************************** AdbField ***************************/
class AdbField {
public:
    // Methods
    AdbField();
    ~AdbField();
    bool isLeaf();
    bool isStruct();
    bool isArray();
    u_int32_t arrayLen();
    bool isUnlimitedArr();
    u_int32_t eSize();
    string toXml(const string& addPrefix);

    // Operator overloading - useful for sorting
    bool operator<(AdbField& other);

    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    string name;
    u_int32_t size; // in bits
    u_int32_t offset; // in bits (relative to the node start addr)
    string desc;
    bool definedAsArr;
    u_int32_t lowBound;
    u_int32_t highBound;
    bool unlimitedArr;
    string subNode;
    AttrsMap attrs;
    bool isReserved;
    string condition; // field's visibility dynamic condition

    // FOR USER USAGE
    void *userData;
};

/*************************** AdbConfig ***************************/
class AdbConfig {
public:
    // FOR DEBUG
    void print(int indent = 0);

    string toXml();

public:
    // Members
    AttrsMap attrs;
    AttrsMap enums;
};

/*************************** AdbInstance ***************************/
class AdbInstance {
public:
    // Methods
    AdbInstance();
    ~AdbInstance();
    bool isLeaf();
    bool isUnion();
    bool isStruct();
    bool isNode();
    bool isPartOfArray();
    string fullName(int skipLevel = 0);
    bool isReserved();
    u_int32_t dwordAddr();
    u_int32_t startBit();
    bool isEnumExists();
    bool enumToInt(const string &name, u_int64_t &val); // false means no enum value found
    bool intToEnum(u_int64_t val, string &valName); // false means no enum name found
    map<string, u_int64_t> getEnumMap();
    vector<u_int64_t> getEnumValues();
    AdbInstance* getUnionSelectedNodeName(const u_int64_t& selectorVal);
    AdbInstance* getUnionSelectedNodeName(const string& selectorEnum);
    bool operator<(const AdbInstance& other);
    bool isConditionalNode();
    bool isConditionValid(map<string, string> *valuesMap);
    // DB like access methods
    AdbInstance
    * getChildByPath(const string& path, bool isCaseSensitive = true);
    vector<AdbInstance*> findChild(const string& name,
            bool isCaseSensitive = true, bool by_inst_name = false);
    string getInstanceAttr(const string &attrName) const;
    AttrsMap::iterator getInstanceAttrIterator(const string &attrName, bool &isEnd);
    void setInstanceAttr(const string &attrName, const string &attrValue);
    void copyAllInstanceAttr(AttrsMap &attsToCopy); 
    AttrsMap getFullInstanceAttrsMapCopy();
    void setVarsMap(const string &attrName, const string &attrValue);
    void setVarsMap(const AttrsMap &AttrsMap);
    AttrsMap getVarsMap();
    vector<AdbInstance*> getLeafFields(); // Get all leaf fields
    void pushBuf(u_int8_t *buf, u_int64_t value);
    u_int64_t popBuf(u_int8_t *buf);
    int instAttrsMapLen() {return instAttrsMap.size();}
    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    AdbField *fieldDesc;
    AdbNode *nodeDesc;
    AdbInstance *parent;
    string name; // instance name
    vector<AdbInstance*> subItems;
    u_int32_t offset; // Global offset in bits (Relative to 0)
    u_int32_t size; // in bits
    u_int32_t arrIdx;
    AdbInstance *unionSelector; // For union instances only
    bool isDiff;
    // FOR USER USAGE
    void *userData;
private:
    AttrsMap instAttrsMap; // Attributes after evaluations and array expanding
    AttrsMap varsMap; // all variables relevant to this item after evaluation
};

/*************************** Adb ***************************/
typedef vector<string> StringVector;
typedef struct {
    string fullPath;
    string includedFromFile;
    int includedFromLine;
} IncludeFileInfo;
typedef map<string, IncludeFileInfo> IncludeFileMap;
typedef map<string, AdbNode*> NodesMap;
typedef vector<AdbConfig*> ConfigList;
typedef map<string, AttrsMap> InstanceAttrs;
typedef map<string, StringVector> ExceptionsMap;
class Adb {
public:
    // Methods
    Adb();
    ~Adb();
    void raiseException(bool allowMultipleExceptions, string exceptionTxt, const string expType);
    // strict union means:
    //   1- dwrod aligned unions
    //   2- contains nodes only
    //   3- check node size vs instance size
    bool loadFromString(const char *adbContents, bool addReserved = false,
            AdbProgress *progressObj = NULL, bool strict = true,
            bool enforceExtraChecks = false);
    bool load(string fname, bool addReserved = false,
            AdbProgress *progressObj = NULL, bool strict = true,
            string includePath = "", string includeDir = "",
            bool enforceExtraChecks = false, bool getAllExceptions = false,
            string logFile = "");
    string toXml(vector<string> nodeNames = vector<string> (),
            bool addRootNode = false, string rootName = "MainNode",
            string addPrefix = "");

    AdbInstance* addMissingNodes(int depth, bool allowMultipleExceptions);
    AdbInstance* createLayout(string rootNodeName, bool isExprEval = false,
            AdbProgress *progressObj = NULL, int depth = -1, /* -1 means instantiate full tree */
            bool ignoreMissingNodes = false, bool getAllExceptions = false);
    vector<string> getNodeDeps(string nodeName);
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
    LogFile _logFile;

    /* For internal use */
public:
    StringVector includePaths;
    string mainFileName;
    IncludeFileMap includedFiles;
    StringVector warnings;
    ExceptionsMap adbExceptionMap;
private:
    vector<AdbInstance*> createInstance(AdbField *fieldDesc,
            AdbInstance *parent, map<string, string> vars, bool isExprEval,
            AdbProgress *progressObj, int depth,
            bool ignoreMissingNodes = false, bool getAllExceptions = false);
    u_int32_t calcArrOffset(AdbField *fieldDesc, AdbInstance *parent,
            u_int32_t arrIdx);
    string evalExpr(string expr, AttrsMap *vars);
    bool checkInstSizeConsistency(bool getAllExceptions = false);
    void cleanInstAttrs();

private:
    string _lastError;
    AdbExpr _adbExpr;
    std::list<AdbInstance*> _unionSelectorEvalDeffered;
    void checkInstanceOffsetValidity(AdbInstance *inst, AdbInstance *parent, bool allowMultipleExceptions);
    void throwExeption(bool allowMultipleExceptions, string exceptionTxt, string addedMsgMultiExp);
};
#endif // ADB_PARSER_H
