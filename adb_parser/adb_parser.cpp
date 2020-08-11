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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <list>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <expat.h>
#include <stdexcept>
#include "adb_parser.h"
#include "buf_ops.h"

#if __cplusplus >= 201402L
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif

#ifdef __WIN__
#include <process.h>
#define OS_PATH_SEP "\\"
#else
#define OS_PATH_SEP "/"
#endif

#ifdef __linux__
#define LC_ALL_HINT " using `export LC_ALL=C`"
#else
#define LC_ALL_HINT ""
#endif

#define PROGRESS_NODE_CNT   100 // each 100 parsed node call progress callback

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#define CHECK_RUNTIME_ERROR(e) ((strstr(e.what(), "locale::facet::_S_create_c_locale") != NULL) ? \
                                string("Encoding error, please set locale encoding to C") + LC_ALL_HINT + "." : \
                                string("runtime_error: ") + e.what())

#define WRITE   "w"

string encodeXml(const string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for (size_t pos = 0; pos != data.size(); ++pos) {
        switch (data[pos]) {
        case '&':
            buffer.append("&amp;");
            break;

        case '\"':
            buffer.append("&quot;");
            break;

        case '\'':
            buffer.append("&apos;");
            break;

        case '<':
            buffer.append("&lt;");
            break;

        case '>':
            buffer.append("&gt;");
            break;

        default:
            buffer.append(1, data.at(pos));
            break;
        }
    }

    return buffer;
}

string indentString(int i) {
    string s;
    while (i--) {
        s += "\t";
    }
    return s;
}

int dword(int bits) {
    if (bits < 0) {
        bits -= 31;
    }

    return (bits / 32) * 4;
}

int startBit(int bits) {
    return bits % 32;
}

string formatAddr(u_int32_t offs, u_int32_t size) {
    char str[64];
    sprintf(str, "0x%x.%u:%u", dword(offs), startBit(offs), size);
    return str;
}

/**
 * Function: AdbParser::compareFieldsPtr
 **/
template<class T>
bool compareFieldsPtr(T *f1, T *f2) {
    return (*f1) < (*f2);
}

/*************************** ExceptionHolder ***************************/
class ExceptionHolder {
public:
    // METHODS
    static void insertNewException(const string exceptionType, string exceptionTxt);
    static ExceptionsMap getAdbExceptionsMap();
    static int getNumberOfExceptions();
public:
    // VARIABLES
    static ExceptionsMap adbExceptionMap;
    static const string FATAL_EXCEPTION;
    static const string ERROR_EXCEPTION;
    static const string WARN_EXCEPTION;
    static int exceptionCounter;
};
ExceptionsMap ExceptionHolder::adbExceptionMap;
const string ExceptionHolder::FATAL_EXCEPTION = "FATAL";
const string ExceptionHolder::ERROR_EXCEPTION = "ERROR"; 
const string ExceptionHolder::WARN_EXCEPTION = "WARNING"; 
int ExceptionHolder::exceptionCounter = 0;

/**
 * Function: ExceptionHolder::getNumberOfExceptions
 * This function return the number of exceptions found
 **/

int ExceptionHolder::getNumberOfExceptions() {
    return ExceptionHolder::exceptionCounter;
}

/**
 * Function: ExceptionHolder::getAdbExceptionsMap
 * This function return the adb exception map
 **/

ExceptionsMap ExceptionHolder::getAdbExceptionsMap() {
    return ExceptionHolder::adbExceptionMap;
}

/**
 * Function: ExceptionHolder::insertNewException
 * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 * Then it insert it to the adb exception map
 **/
void ExceptionHolder::insertNewException(const string exceptionType, string exceptionTxt) {
    ExceptionHolder::adbExceptionMap[exceptionType].push_back(exceptionTxt);
    ExceptionHolder::exceptionCounter += 1;
}

LogFile::LogFile() : _logFile(NULL) {
}

void LogFile::init(string logFileName, bool allowMultipleExceptions) {
    if (logFileName.compare("") != 0) {
        _logFile = fopen(logFileName.c_str(), WRITE);
        if (!_logFile) {
            string  _lastError = "Can't open file (" + logFileName + ") for writing: "
                    + strerror(errno);
            if (allowMultipleExceptions) {
                ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
            } else {
                throw AdbException(_lastError);
            }
        }
    } else {
        _logFile = NULL;
    }
}

LogFile::~LogFile() {
    if (_logFile) {
        fclose (_logFile);
    }
}

void LogFile::appendLogFile(string str) {
    if (_logFile) {
        fprintf(_logFile, "%s", str.c_str());
    }
}

/*************************** AdbParser ***************************/
class AdbParser {
public:
    // METHODS
    AdbParser(string fileName, Adb *adbCtxt, bool addReserved = false,
            AdbProgress *progressObj = NULL, bool strict = true,
            string includePath = "", bool enforceExtraChecks = false);
    ~AdbParser();
    bool load();
    bool loadFromString(const char *adbString);
    string getError();

    static string descXmlToNative(const string& desc);
    static string descNativeToXml(const string& desc);
    static void includeAllFilesInDir(AdbParser *adbParser, string dirPath,
            int lineNumber = -1);
    static bool checkSpecialChars(string tagName);
    static bool checkBigger32(string num);
    static bool checkHEXFormat(string addr);
    static void setAllowMultipleExceptionsTrue();

public:
    static bool allowMultipleExceptions;

private:
    // METHODS
    string findFile(string fileName);
    static void addIncludePaths(Adb *adbCtxt, string includePaths);
    static void includeFile(AdbParser *adbParser, string fileName, int lineNumber = -1);
    static void startElement(void *adbParser, const XML_Char *name, const XML_Char **atts);

    static void startNodesDefElement(const XML_Char **atts, AdbParser *adbParser);
    static void startEnumElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber);
    static void startConfigElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber);
    static void startInfoElement(const XML_Char **atts, AdbParser *adbParser);
    static void startIncludeElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber);
    static void startInstOpAttrReplaceElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber);
    static void startNodeElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber);
    static void startFieldElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber);

    static void endElement(void *adbParser, const XML_Char *name);
    static void addReserved(vector<AdbField*> &reserveds, u_int32_t offset, u_int32_t size);
    static int attrCount(const XML_Char **atts);
    static string attrValue(const XML_Char **atts, const XML_Char *attrName);
    static string attrName(const XML_Char **atts, int i);
    static string attrValue(const XML_Char **atts, int i);
    static u_int32_t addr2int(string& s);
    static u_int32_t dword(u_int32_t offset);
    static u_int32_t startBit(u_int32_t offset);
    static bool raiseException(bool allowMultipleExceptions, string exceptionTxt, 
                              string addedMsg, const string expType);

private:
    // MEMBERS
    Adb *_adbCtxt;
    XML_Parser _xmlParser;
    string _fileName;
    string _lastError;
    bool _addReserved;
    int _progressCnt;
    AdbProgress *_progressObj;
    bool _strict;
    string _includePath;
    string _currentTagValue;
    AdbNode *_currentNode;
    AdbField *_currentField;
    AdbConfig *_currentConfig;
    bool _instanceOps;
    bool _enforceExtraChecks;

    static const string TAG_NODES_DEFINITION;
    static const string TAG_RCS_HEADERS;
    static const string TAG_CONFIG;
    static const string TAG_ENUM;
    static const string TAG_INCLUDE;
    static const string TAG_INFO;
    static const string TAG_NODE;
    static const string TAG_FIELD;
    static const string TAG_INSTANCE_OPS;
    static const string TAG_INSTANCE_OP_ATTR_REPLACE;
    static const string TAG_ATTR_ENUM;
    static const string TAG_ATTR_BIG_ENDIAN;
    static const string TAG_ATTR_SINGLE_ENTRY_ARR;
    static const string TAG_ATTR_INCLUDE_PATH;
};
bool AdbParser::allowMultipleExceptions = false;
const string AdbParser::TAG_NODES_DEFINITION = "NodesDefinition";
const string AdbParser::TAG_RCS_HEADERS = "RCSheaders";
const string AdbParser::TAG_CONFIG = "config";
const string AdbParser::TAG_ENUM = "enum";
const string AdbParser::TAG_INCLUDE = "include";
const string AdbParser::TAG_INFO = "info";
const string AdbParser::TAG_NODE = "node";
const string AdbParser::TAG_FIELD = "field";
const string AdbParser::TAG_INSTANCE_OPS = "instance_ops";
const string AdbParser::TAG_INSTANCE_OP_ATTR_REPLACE = "attr_replace";
const string AdbParser::TAG_ATTR_ENUM = "enum";
const string AdbParser::TAG_ATTR_BIG_ENDIAN = "big_endian_arr";
const string AdbParser::TAG_ATTR_SINGLE_ENTRY_ARR = "single_entry_arr";
const string AdbParser::TAG_ATTR_INCLUDE_PATH = "include_path";

/*************************** AdbNode ***************************/

/**
 * Function: AdbNode::AdbNode
 **/
AdbNode::AdbNode() :
    size(0), isUnion(false), lineNumber(-1), userData(0) {

}

/**
 * Function: AdbNode::~AdbNode
 **/
AdbNode::~AdbNode() {
    for (size_t i = 0; i < fields.size(); i++) {
        delete fields[i];
    }
    fields.clear();
    for (size_t i = 0; i < condFields.size(); i++) {
        delete condFields[i];
    }
    condFields.clear();
}

/**
 * Function: AdbNode::toXml
 **/
string AdbNode::toXml(const string& addPrefix) {
    string xml = "<node name=\"" + addPrefix + name + "\" descr=\""
            + encodeXml(AdbParser::descNativeToXml(desc)) + "\"";
    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++) {
        if (it->first == "name" || it->first == "descr") {
            continue;
        }

        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }
    xml += " >\n";

    FieldsList allFields = fields;
    allFields.insert(allFields.end(), condFields.begin(), condFields.end());
    stable_sort(allFields.begin(), allFields.end(), compareFieldsPtr<AdbField> );

    for (size_t i = 0; i < allFields.size(); i++) {
        if (allFields[i]->isReserved) {
            continue;
        }

        xml += "\t" + allFields[i]->toXml(addPrefix) + "\n";
    }

    xml += "</node>";
    return xml;
}

/**
 * Function: AdbNode::print
 **/
void AdbNode::print(int indent) {
    cout << indentString(indent);
    cout << "+ Node Name: " << name << " size: 0x" << hex << size / 32 * 4
            << "." << dec << size % 32 << " isUnion: " << isUnion
            << " Description: " << desc << endl;

    cout << indentString(indent) << "Fields:" << endl;
    for (size_t i = 0; i < fields.size(); i++)
        fields[i]->print(indent + 1);
}

/*************************** AdbField ***************************/
/**
 * Function: AdbField::AdbField
 **/
AdbField::AdbField() :
    size(0), offset(0xffffffff), definedAsArr(false), lowBound(0),
            highBound(0), unlimitedArr(false), isReserved(false), userData(0) {
}

/**
 * Function: AdbField::~AdbField
 **/
AdbField::~AdbField() {
}

/**
 * Function: AdbField::isLeaf
 **/
bool AdbField::isLeaf() {
    return subNode.empty();
}

/**
 * Function: AdbField::isStruct
 **/
bool AdbField::isStruct() {
    return !isLeaf();
}

/**
 * Function: AdbField::operator<
 **/
bool AdbField::operator<(AdbField& other) {
    return offset < other.offset;
}

/**
 * Function: AdbField::isArray
 **/
bool AdbField::isArray() {
    if (unlimitedArr) {
        return true;
    } else {
        return definedAsArr ? true : lowBound != highBound;
    }
}

/**
 * Function: AdbField::arrayLen
 **/
u_int32_t AdbField::arrayLen() {
    if (unlimitedArr) {
        return 1;
    } else {
        return (highBound - lowBound + 1);
    }
}

/**
 * Function: AdbField::isUnlimitedArr
 **/
bool AdbField::isUnlimitedArr() {
    return unlimitedArr;
}

/**
 * Function: AdbField::isArray
 **/
u_int32_t AdbField::eSize() {
    if (unlimitedArr) {
        return size;
    } else {
        return size / arrayLen();
    }
}

/**
 * Function: AdbField::print
 **/
void AdbField::print(int indent) {
    cout << indentString(indent);
    cout << "- FIELD - Name: " << name << " offset: 0x" << hex << offset / 32
            * 4 << "." << dec << offset % 32 << " size: 0x" << hex << size / 32
            * 4 << "." << dec << size % 32 << " low_bound: " << lowBound
            << " high_bound: " << highBound << " sub_node: " << subNode
            << " isReserved: " << isReserved << endl;
}

/**
 * Function: AdbField::toXml
 **/
string AdbField::toXml(const string& addPrefix) {
    string xml = "<field name=\"" + name + "\" descr=\"" + encodeXml(
            AdbParser::descNativeToXml(desc)) + "\"";
    if (isStruct()) {
        xml += " subnode=\"" + addPrefix + subNode + "\"";
    }

    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++) {
        if (it->first == "name" || it->first == "subnode" || it->first
                == "descr") {
            continue;
        }

        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }

    xml += " />";
    return xml;
}

/*************************** AdbConfig ***************************/
/**
 * Function: AdbField::print
 **/
void AdbConfig::print(int indent) {
    cout << indentString(indent) << "Attributes:" << endl;
    AttrsMap::iterator iter;
    for (iter = attrs.begin(); iter != attrs.end(); iter++)
        cout << indentString(indent + 1) << iter->first << " - "
                << iter->second << endl;

    cout << indentString(indent) << "Enums:" << endl;
    for (iter = enums.begin(); iter != enums.end(); iter++)
        cout << indentString(indent + 1) << iter->first << " - "
                << iter->second << endl;
}

/**
 * Function: AdbConfig::toXml
 **/
string AdbConfig::toXml() {
    string xml = "<config ";

    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++) {
        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }

    if (!enums.empty()) {
        xml += " >\n";

        for (AttrsMap::iterator it = enums.begin(); it != enums.end(); it++) {
            xml += "\t<enum  name=\"" + encodeXml(it->first) + "\" value=\""
                    + encodeXml(it->second) + "\" />\n";
        }
        xml += "</config>";
    } else {
        xml += " />";
    }

    return xml;
}

/*************************** AdbInstance ***************************/
/**
 * Function: AdbInstance::AdbInstance
 **/
AdbInstance::AdbInstance() :
    fieldDesc(NULL), nodeDesc(NULL), parent(NULL), offset(0xffffffff), size(0),
            arrIdx(0), unionSelector(NULL), isDiff(false), userData(NULL)

{

}

/**
 * Function: AdbInstance::AdbInstance
 **/
AdbInstance::~AdbInstance() {
    for (size_t i = 0; i < subItems.size(); i++)
        delete subItems[i];
}

/**
 * Function: AdbInstance::isLeaf
 **/
bool AdbInstance::isLeaf() {
    return nodeDesc == NULL;
}

/**
 * Function: isUnionisUnion
 **/
bool AdbInstance::isUnion() {
    return isNode() && nodeDesc->isUnion;
}

/**
 * Function: AdbInstance::isStruct
 **/
bool AdbInstance::isStruct() {
    return isNode() && !isUnion();
}

/**
 * Function: AdbInstance::isNode
 **/
bool AdbInstance::isNode() {
    return !isLeaf();
}

/**
 * Function: AdbInstance::isNode
 **/
bool AdbInstance::isPartOfArray() {
    return fieldDesc->isArray();
}

/**
 * Function: AdbInstance::fullName
 **/
string AdbInstance::fullName(int skipLevel) {
    list < string > fnList;
    AdbInstance *p = parent;

    fnList.push_front(name);
    while (p != NULL) {
        fnList.push_front(p->name);
        p = p->parent;
    }

    if ((int) fnList.size() > skipLevel) {
        while (skipLevel--) {
            fnList.pop_front();
        }

        return boost::algorithm::join(fnList, ".");
    } else {
        return fnList.back();
    }
}

/**
 * Function: AdbInstance::fullName
 **/
bool AdbInstance::isReserved() {
    return fieldDesc->isReserved;
}

/**
 * Function: AdbInstance::fullName
 **/
u_int32_t AdbInstance::dwordAddr() {
    return (offset >> 5) << 2;
}

/**
 * Function: AdbInstance::fullName
 **/
u_int32_t AdbInstance::startBit() {
    return offset % 32;
}

/**
 * Function: AdbInstance::operator<
 **/
bool AdbInstance::operator<(const AdbInstance& other) {
    return offset < other.offset;
}

/**
 * Function: AdbInstance::getChildByPath
 **/
AdbInstance* AdbInstance::getChildByPath(const string &path,
        bool isCaseSensitive) {
    string effPath = isCaseSensitive ? path : boost::algorithm::to_lower_copy(
            path);
    if (effPath[0] == '.') {
        effPath.erase(0, 1);
    }

    size_t idx = effPath.find(".");
    string childName = idx == string::npos ? effPath : effPath.substr(0, idx);
    string grandChildPath = idx == string::npos ? string() : effPath.substr(
            idx + 1);

    if (path.empty()) {
        return this;
    }

    // Search for childName
    AdbInstance *child = NULL;
    for (size_t i = 0; i < subItems.size(); i++) {
        string subName = isCaseSensitive ? subItems[i]->name
                : boost::algorithm::to_lower_copy(subItems[i]->name);
        if (subName == childName) {
            child = subItems[i];
            break;
        }
    }

    if (!child) {
        return NULL;
    }

    // if grandChildPath isn't empty this means we need to continue and find the desired field in grand child node
    return grandChildPath.empty() ? child : child->getChildByPath(
            grandChildPath, isCaseSensitive);
}

/**
 * Function: AdbInstance::findChild
 **/
vector<AdbInstance*> AdbInstance::findChild(const string& childName,
        bool isCaseSensitive, bool by_inst_name) {
    string effName = isCaseSensitive ? childName
            : boost::algorithm::to_lower_copy(childName);
    vector<AdbInstance*> childList;

    if (by_inst_name || isLeaf()) {
        if (name == childName) {
            childList.push_back(this);
        }
    } else {
        if (isNode() && nodeDesc->name == childName) {
            childList.push_back(this);
        }
    }

    // do that recursively for all child items
    for (size_t i = 0; i < subItems.size(); i++) {
        vector<AdbInstance*> l = subItems[i]->findChild(effName, true);
        childList.insert(childList.end(), l.begin(), l.end());
    }

    return childList;
}

/**
 * Function: AdbInstance::getAttr
 **/
string AdbInstance::getInstanceAttr(const string &attrName) const
{
    AttrsMap::const_iterator it = instAttrsMap.find(attrName);
    if (it == instAttrsMap.end()) {
        if (fieldDesc) {
            it = fieldDesc->attrs.find(attrName);
            if (it == fieldDesc->attrs.end()) {
                return string();
            }
        }
        else{
            return string();
        }
    }
    return it->second;
}


/**
 * Function: AdbInstance::getInstanceAttrIterator
 **/
AttrsMap::iterator AdbInstance::getInstanceAttrIterator(const string &attrName, bool &found) 
{
    AttrsMap::iterator it = instAttrsMap.find(attrName);
    found = false;
    if (it != instAttrsMap.end()) {
        found = true;
    } 
    else if (fieldDesc){
        it = fieldDesc->attrs.find(attrName);
        if (it != fieldDesc->attrs.end()) {
            found =true;
        }
    }
    return it;
}


/**
 * Function: AdbInstance::setInstanceAttr
 **/
void AdbInstance::setInstanceAttr(const string &attrName, const string &attrValue)
{
    instAttrsMap[attrName] = attrValue;
}

/*
 * Function: AdbInstance::copyAllInstanceAttr - copies all attrs from attributes structure
 **/
void AdbInstance::copyAllInstanceAttr(AttrsMap &attsToCopy) 
{
    instAttrsMap = attsToCopy;
}

/**
 * Function: AdbInstance::getFullInstanceAttrsMapCopy - returns the instance attr map by val
 **/
AttrsMap AdbInstance::getFullInstanceAttrsMapCopy()
{
    AttrsMap tmpCopy;
    // copy first the fields attr map 
    for (AttrsMap::iterator it = fieldDesc->attrs.begin(); it != fieldDesc->attrs.end(); it++){
        tmpCopy[it->first] = it->second;
    }
    // copy the overriden variables - in instAttrsMap
    for (AttrsMap::iterator it = instAttrsMap.begin(); it != instAttrsMap.end(); it++){
        tmpCopy[it->first] = it->second;
    }
    return tmpCopy;
}

/**
 * Function: AdbInstance::setVarsMap - set an item in vars map 
 **/
void AdbInstance::setVarsMap(const string &attrName, const string &attrValue)
{
    varsMap[attrName] = attrValue;
}

/**
 * Function: AdbInstance::setVarsMap - set an item in vars map 
 **/
void AdbInstance::setVarsMap(const AttrsMap &AttrsMap)
{
    varsMap = AttrsMap;
}

/**
 * Function: AdbInstance::setVarsMap - returns a copy of vars map 
 **/
AttrsMap AdbInstance::getVarsMap()
{
    return varsMap;
}

/**
 * Function: AdbInstance::isEnumExists
 **/
bool AdbInstance::isEnumExists() {
    return !getInstanceAttr("enum").empty();
}

/**
 * Function: AdbInstance::enumToInt
 **/
bool AdbInstance::enumToInt(const string &name, u_int64_t &val) {
    vector < string > enumValues;
    string enums = getInstanceAttr("enum");
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++) {
        vector < string > pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues,
                boost::is_any_of(string("=")));

        if (pair.size() != 2) {
            continue;
        }

        char *end;
        if (pair[0] == name) {
            val = strtoul(pair[1].c_str(), &end, 0);
            if (*end != '\0') {
                return false;
            }
            return true;
        }
    }

    return false;
}

/**
 * Function: AdbInstance::intToEnum
 **/
bool AdbInstance::intToEnum(u_int64_t val, string &valName) {
    vector < string > enumValues;
    string enums = getInstanceAttr("enum");
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++) {
        vector < string > pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues,
                boost::is_any_of(string("=")));

        if (pair.size() != 2) {
            continue;
        }

        char *end;
        u_int64_t tmp = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0') {
            continue;
        }

        if (tmp == val) {
            valName = pair[0];
            return true;
        }
    }

    return false;
}

/**
 * Function: AdbInstance::getEnumMap
 **/
map<string, u_int64_t> AdbInstance::getEnumMap() {
    map < string, u_int64_t > enumMap;
    vector < string > enumValues;
    string enums = getInstanceAttr("enum");
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++) {
        vector < string > pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues,
                boost::is_any_of(string("=")));
        if (pair.size() != 2) {
            throw AdbException("Can't parse enum: " + enumValues[i]);
            //continue;
        }

        char *end;
        u_int64_t intVal = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0') {
            throw AdbException(
                    string("Can't evaluate enum (") + pair[0].c_str() + "): "
                            + pair[1].c_str());
            //continue;
        }

        enumMap[pair[0]] = intVal;
    }

    return enumMap;
}

/**
 * Function: AdbInstance::getEnumValues
 **/
vector<u_int64_t> AdbInstance::getEnumValues() {
    vector < u_int64_t > values;
    vector < string > enumValues;
    string enums = getInstanceAttr("enum");
    boost::algorithm::split(enumValues, enums, boost::is_any_of(string(",")));

    for (size_t i = 0; i < enumValues.size(); i++) {
        vector < string > pair;
        string trimedEnumValues = enumValues[i];
        boost::algorithm::trim(trimedEnumValues);
        boost::algorithm::split(pair, trimedEnumValues,
                boost::is_any_of(string("=")));
        if (pair.size() != 2) {
            continue;
        }

        char *end;
        u_int64_t intVal = strtoul(pair[1].c_str(), &end, 0);
        if (*end != '\0') {
            continue;
        }

        values.push_back(intVal);
    }

    return values;
}

/**
 * Function: AdbInstance::getUnionSelectedNodeName
 **/
AdbInstance* AdbInstance::getUnionSelectedNodeName(const u_int64_t& selectorVal) {
    if (!isUnion()) {
        throw AdbException(
                "This is not union node (%s), can't get selected node name", fullName().c_str());
    }

    if (!unionSelector) {
        throw AdbException("Can't find selector for union: " + name);
    }

    map < string, u_int64_t > selectorValMap = unionSelector->getEnumMap();
    for (map<string, u_int64_t>::iterator it = selectorValMap.begin(); 
         it != selectorValMap.end(); it++) {
        if (it->second == selectorVal) {
            const string& selectorEnum = it->first;
            // search for the sub instance with the "selected_by" attribute == selectorEnum
            for (size_t i = 0; i < subItems.size(); i++) {
                if (subItems[i]->getInstanceAttr("selected_by") == selectorEnum) {
                    return subItems[i];
                }

            }
            throw AdbException("Found selector value (" + selectorEnum
                            + ") is defined for selector field ("
                            + unionSelector->name
                            + ") but no appropriate subfield of this union was found");
        }
    }

    throw AdbException(
            "Union selector field (" + unionSelector->name
                    + ") doesn't define selector value ("
                    + boost::lexical_cast<string>(selectorVal));
}

/**
 * Function: AdbInstance::getUnionSelectedNodeName
 **/
AdbInstance* AdbInstance::getUnionSelectedNodeName(const string& selectorEnum) {
    if (!isUnion()) {
        throw AdbException(
                "This is not union node (%s), can't get selected node name", fullName().c_str());
    }

    if (!unionSelector) {
        throw AdbException("Can't find selector for union: " + name);
    }

    for (size_t i = 0; i < subItems.size(); i++) {
        if (subItems[i]->getInstanceAttr("selected_by") == selectorEnum) {
            return subItems[i];
        }
    }

    throw AdbException("Union selector field (" + unionSelector->name
                    + ") doesn't define a selector value (" + selectorEnum + ")");
}

/**
 * Function: AdbInstance::isConditionalNode
 * Throws exception: AdbException
 **/
bool AdbInstance::isConditionalNode() {
    if (isNode()) {
        return (getInstanceAttr("is_conditional") == "1");
    }
    return false;
}

/**
 * Function: AdbInstance::isConditionValid
 * Throws exception: AdbException
 **/
bool AdbInstance::isConditionValid(map<string, string> *valuesMap) {
    u_int64_t res;
    AdbExpr expressionChecker;
    int status = -1;
    char *condExp;
    char *exp;

    if (fieldDesc->condition.empty()) {
        return true;
    }

    condExp = new char[fieldDesc->condition.size() + 1];
    exp = condExp;
    if (!exp) {
        throw AdbException("Memory allocation error");
    }
    strcpy(exp, fieldDesc->condition.c_str());

    expressionChecker.setVars(valuesMap);
    try {
        status = expressionChecker.expr(&exp, &res);
    } catch (AdbException &e) {
        delete[] condExp;
        throw AdbException(string("AdbException: ") + e.what_s());
    }
    delete[] condExp;

    if (status < 0) {
        throw AdbException(
                string("Error evaluating expression \"")
                        + fieldDesc->condition.c_str() + "\" : "
                        + AdbExpr::statusStr(status));
    }

    return (status >= 0 && res != 0);
}

/**
 * Function: AdbInstance::getLeafFields
 **/
vector<AdbInstance*> AdbInstance::getLeafFields() {
    vector<AdbInstance*> fields;

    for (size_t i = 0; i < subItems.size(); i++) {
        if (subItems[i]->isNode()) {
            vector<AdbInstance*> subFields = subItems[i]->getLeafFields();
            fields.insert(fields.end(), subFields.begin(), subFields.end());
        } else {
            fields.push_back(subItems[i]);
        }
    }

    return fields;
}

/**
 * Function: AdbInstance::pushBuf
 **/
void AdbInstance::pushBuf(u_int8_t *buf, u_int64_t value) {
    push_to_buf(buf, offset, size, value);
}

/**
 * Function: AdbInstance::popBuf
 **/
u_int64_t AdbInstance::popBuf(u_int8_t *buf) {
    return pop_from_buf(buf, offset, size);
}

/**
 * Function: AdbInstance::print
 **/
void AdbInstance::print(int indent) {
    string indentStr = indentString(indent);
    printf(
            "%sfullName: %s, offset: 0x%x.%d, size: 0x%x.%d, isNode:%d, isUnion:%d\n",
            indentStr.c_str(), fullName().c_str(), (offset >> 5) << 2,
            offset % 32, (size >> 5) << 2, size % 32, isNode(), isUnion());

    if (isNode()) {
        for (size_t i = 0; i < subItems.size(); i++)
            subItems[i]->print(indent + 1);
    }
}

/*************************** Adb ***************************/
/**
 * Function: Adb::Adb
 **/
Adb::Adb() :
    bigEndianArr(false), singleEntryArrSupp(false){
}

/**
 * Function: Adb::~Adb
 **/
Adb::~Adb() {
    // Free configs
    for (size_t i = 0; i < configs.size(); i++)
        delete configs[i];

    // Free nodes
    NodesMap::iterator iter;
    for (iter = nodesMap.begin(); iter != nodesMap.end(); iter++)
        delete iter->second;
}

/**
 * Function: Adb::raiseException
 **/
void Adb::raiseException(bool allowMultipleExceptions, string exceptionTxt, const string expType)
{
    if (allowMultipleExceptions) {
        ExceptionHolder::insertNewException(expType, exceptionTxt);
    } else {
        throw AdbException(exceptionTxt);
    }
    return;
}

/**
 * Function: Adb::getAdbExceptionsMap
 * This function return the adb exception map
 **/
void Adb::fetchAdbExceptionsMap(ExceptionsMap otherMap) {
    vector < string > fatals = otherMap[ExceptionHolder::FATAL_EXCEPTION];
    for (vector < string >::iterator it = fatals.begin(); it != fatals.end(); ++it) {
        insertNewException(ExceptionHolder::FATAL_EXCEPTION, *it);
    }
    vector < string > errors = otherMap[ExceptionHolder::ERROR_EXCEPTION];
    for (vector < string >::iterator it = errors.begin(); it != errors.end(); ++it) {
        insertNewException(ExceptionHolder::ERROR_EXCEPTION, *it);
    }
    vector < string > warnings = otherMap[ExceptionHolder::WARN_EXCEPTION];
    for (vector < string >::iterator it = warnings.begin(); it != warnings.end(); ++it) {
        insertNewException(ExceptionHolder::WARN_EXCEPTION, *it);
    }
}


/**
 * Function: Adb::insertNewException
 * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 * Then it insert it to the adb exception map
 **/
void Adb::insertNewException(const string exceptionType, string exceptionTxt) {
    adbExceptionMap[exceptionType].push_back(exceptionTxt);
}

/**
 * Function: Adb::printAdbExceptionMap
 * This function will pring the content of the Adb Exception Map
 **/
string Adb::printAdbExceptionMap() {
    string errorStr = "";
    vector < string > fatals = adbExceptionMap[ExceptionHolder::FATAL_EXCEPTION];
    for (vector < string >::iterator it = fatals.begin(); it != fatals.end(); ++it) {
        errorStr += "-" + ExceptionHolder::FATAL_EXCEPTION + "- " + *it + ";";
    }
    vector < string > errors = adbExceptionMap[ExceptionHolder::ERROR_EXCEPTION];
    for (vector < string >::iterator it = errors.begin(); it != errors.end(); ++it) {
        errorStr += "-" + ExceptionHolder::ERROR_EXCEPTION + "- " + *it + ";";
    }
    vector < string > warnings = adbExceptionMap[ExceptionHolder::WARN_EXCEPTION];
    for (vector < string >::iterator it = warnings.begin(); it != warnings.end(); ++it) {
        errorStr += "-" + ExceptionHolder::WARN_EXCEPTION + "- " + "- " + *it + ";";
    }
    return errorStr;
}

/**
 * Function: Adb::load
 **/
bool Adb::load(string fname, bool addReserved, AdbProgress *progressObj,
        bool strict, string includePath, string includeDir,
        bool enforceExtraChecks, bool allowMultipleExceptions, string logFileStr) {
    try {
        bool status = true;
        mainFileName = fname;
        if (allowMultipleExceptions) {
            AdbParser::setAllowMultipleExceptionsTrue();
        }
        _logFile.init(logFileStr, allowMultipleExceptions);

        AdbParser p(fname, this, addReserved, progressObj, strict, includePath,
                enforceExtraChecks);
        if (!p.load()) {
            _lastError = p.getError();
            status = false;
        }
        if (status && includeDir != "") {
            AdbParser::includeAllFilesInDir(&p, includeDir);
        }
        if (status && !nodesMap.size()) {
            _lastError = "Empty project, no nodes were found";
            if (allowMultipleExceptions) {
                insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
            }
            status = false;
        }
        if (status) {
            bool checkSizeConsistency = strict ? checkInstSizeConsistency(
                    allowMultipleExceptions) : true;
            status = status && checkSizeConsistency;
        }
        if (allowMultipleExceptions && ExceptionHolder::getNumberOfExceptions()
                > 0) {
            fetchAdbExceptionsMap(ExceptionHolder::getAdbExceptionsMap());
            status = false;
        }
        return status;
    } catch (AdbException &e) {
        _lastError = e.what_s();
        if (allowMultipleExceptions) {
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }
}

/**
 * Function: Adb::loadFromString
 **/
bool Adb::loadFromString(const char *adbContents, bool addReserved,
        AdbProgress *progressObj, bool strict, bool enforceExtraChecks) {
    try {
        AdbParser p(string(), this, addReserved, progressObj, strict, "",
                enforceExtraChecks);
        mainFileName = OS_PATH_SEP;
        if (!p.loadFromString(adbContents)) {
            _lastError = p.getError();
            return false;
        }

        if (!nodesMap.size()) {
            _lastError = "Empty project, no nodes were found";
            return false;
        }

        return strict ? checkInstSizeConsistency() : true;
    } catch (AdbException &e) {
        _lastError = e.what_s();
        return false;
    }
}

/**
 * Function: Adb::toXml
 **/
string Adb::toXml(vector<string> nodeNames, bool addRootNode, string rootName,
        string addPrefix) {
    try {
        vector < string > nodeDeps;
        for (vector<string>::iterator it = nodeNames.begin(); it
                != nodeNames.end(); it++) {
            vector < string > tmp = getNodeDeps(*it);
            nodeDeps.insert(nodeDeps.end(), tmp.begin(), tmp.end());
        }
        stable_sort(nodeDeps.begin(), nodeDeps.end());
        nodeDeps.erase(unique(nodeDeps.begin(), nodeDeps.end()), nodeDeps.end());

        string xml;
        if (this->version == "2") {
            xml = "<NodesDefinition version=\"2\">\n";
        } else {
            xml = "<NodesDefinition>\n";
        }
        for (ConfigList::iterator it = configs.begin(); it != configs.end(); it++) {
            xml += (*it)->toXml() + "\n";
        }

        // Add source info
        xml += "<info source_doc_name=\"" + encodeXml(
                AdbParser::descNativeToXml(srcDocName))
                + "\" source_doc_version=\"" + encodeXml(
                AdbParser::descNativeToXml(srcDocVer)) + "\" />\n";

        if (nodeNames.empty()) {
            for (NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
                AdbNode *node = it->second;
                xml += node->toXml(addPrefix);
            }
        } else {
            u_int32_t maxSize = 0;
            for (size_t i = 0; i < nodeDeps.size(); i++) {
                NodesMap::iterator it = nodesMap.find(nodeDeps[i]);
                if (it == nodesMap.end()) {
                    _lastError = "Can't find node definition for: "
                            + nodeDeps[i];
                    return "";
                }

                AdbNode *node = it->second;
                xml += node->toXml(addPrefix) + "\n\n";

                maxSize = TOOLS_MAX(node->size, maxSize);
            }

            if (addRootNode) {
                stringstream buf;
                buf << "<node name=\"root\" size=\"0x" << hex
                        << ((maxSize >> 5) << 2) << "." << dec
                        << (maxSize % 32) << "\" descr=\"\" >\n";
                buf << "\t<field name=\"" << rootName << "\" offset=\"0x0.0\""
                        << " size=\"0x" << hex << ((maxSize >> 5) << 2) << "."
                        << dec << (maxSize % 32) << "\" subnode=\"" << addPrefix
                        + rootName << "\" descr=\"\" />\n";
                buf << "</node>\n\n";

                buf << "<node name=\"" + addPrefix + rootName + "\" size=\"0x"
                        << hex << ((maxSize >> 5) << 2) << "." << dec
                        << (maxSize % 32)
                        << "\" attr_is_union=\"1\" descr=\"\" >\n";
                for (size_t i = 0; i < nodeNames.size(); i++) {
                    AdbNode *node = nodesMap[nodeNames[i]];
                    buf << "\t<field name=\"" << node->name
                            << "\" offset=\"0x0.0\" size=\"0x" << hex
                            << ((node->size >> 5) << 2) << "." << dec
                            << (node->size % 32) << "\" subnode=\"" + addPrefix
                            + node->name + "\" descr=\"\" />\n";
                }
                buf << "</node>\n";
                xml += buf.str();
            }
        }

        xml += "</NodesDefinition>\n";
        return xml;
    } catch (AdbException& exp) {
        _lastError = exp.what_s();
        return "";
    }
}

/**
 * Function: Adb::addMissingNodes
 **/

AdbInstance* Adb::addMissingNodes(int depth, bool allowMultipleExceptions) {
    try {
        NodesMap::iterator it;
        for (it = nodesMap.begin(); it != nodesMap.end(); it++) {
            AdbNode *nodeDesc = it->second;
            for (size_t i = 0; (depth == -1 || depth > 0) && i
                    < nodeDesc->fields.size(); i++) {
                AdbField *fieldDesc = nodeDesc->fields[i];
                for (u_int32_t i = 0; i < fieldDesc->arrayLen(); i++) {
                    if (fieldDesc->isStruct()) {
                        NodesMap::iterator it2 = nodesMap.find(fieldDesc->subNode);
                        if (it2 == nodesMap.end()) {
                            // If in ignore missing nodes mode, it should create temporary node with placeholder
                            AdbNode *tmpNode = new AdbNode;
                            tmpNode->name = fieldDesc->subNode;
                            tmpNode->size = fieldDesc->eSize();
                            tmpNode->desc = fieldDesc->desc + " ***MISSING NODE***";
                            tmpNode->isUnion = false;
                            tmpNode->fileName = "tempForMissingNodes.adb";
                            tmpNode->lineNumber = 0;
                            AdbField *tmpField = new AdbField;
                            tmpField->name = "placeholder";
                            tmpField->desc
                                    = "This field is part of auto generated node for missing node.";
                            tmpField->size = tmpNode->size;
                            tmpField->offset = 0;
                            tmpNode->fields.push_back(tmpField);
                            nodesMap.insert(
                                    pair<string, AdbNode*> (tmpNode->name, tmpNode));
                        }
                    }
                }
            }
        }
    } catch (AdbException &exp) {
        _lastError = exp.what_s();
        if (allowMultipleExceptions) {
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return NULL;
    } catch (...) {
        _lastError = "Unknown error occurred";
        return NULL;
    }
    return NULL;
}

/**
 * Function: Adb::cleaninstAttrs
 **/
void Adb::cleanInstAttrs()
{
    for (InstanceAttrs::iterator it = instAttrs.begin(); it!= instAttrs.end(); it++){
        it->second.clear();
    }
    instAttrs.clear();
}

/**
 * Function: Adb::createLayout
 **/
AdbInstance* Adb::createLayout(string rootNodeName, bool isExprEval,
        AdbProgress *progressObj, int depth, bool ignoreMissingNodes,
        bool allowMultipleExceptions) {
    try {
        //find root in nodes map
        NodesMap::iterator it;
        it = nodesMap.find(rootNodeName);
        if (it == nodesMap.end()) {
            raiseException(allowMultipleExceptions, 
                          "Can't find definition for node \"" + rootNodeName + "\"",
                          ExceptionHolder::FATAL_EXCEPTION);
        }

        AdbNode *nodeDesc = it->second;
        AdbInstance *rootItem = new AdbInstance();
        rootItem->fieldDesc = NULL;
        rootItem->nodeDesc = nodeDesc;
        rootItem->parent = NULL;
        rootItem->name = nodeDesc->name;
        rootItem->offset = 0;
        rootItem->size = nodeDesc->size;
        rootItem->copyAllInstanceAttr(nodeDesc->attrs);

        map < string, string > emptyVars;
        _unionSelectorEvalDeffered.clear();
        if (ignoreMissingNodes) {
            addMissingNodes(depth, allowMultipleExceptions);
        }

        for (size_t i = 0; (depth == -1 || depth > 0) && i
                < nodeDesc->fields.size(); i++) {
            vector<AdbInstance*> subItems = createInstance(nodeDesc->fields[i],
                    rootItem, emptyVars, isExprEval, progressObj,
                    depth == -1 ? -1 : depth - 1, ignoreMissingNodes,
                    allowMultipleExceptions);
            rootItem->subItems.insert(rootItem->subItems.end(),
                    subItems.begin(), subItems.end());
        }

        // Now set the instance attributes (override field attrs), only if this is root node instantiation
        if (rootNodeName == rootNode && depth == -1) {
            for (InstanceAttrs::iterator it = instAttrs.begin(); it!= instAttrs.end(); it++) {
                size_t idx = it->first.find(".");
                string path = idx == string::npos ? string()
                        : it->first.substr(idx + 1);

                AdbInstance *inst = rootItem->getChildByPath(path);
                if (!inst) {
                    raiseException(allowMultipleExceptions, 
                                  "Can't find instance path (" + it->first + ") defined in <instance_ops> section",
                                  ExceptionHolder::ERROR_EXCEPTION);
                }

                for (AttrsMap::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                    if (allowMultipleExceptions && !inst) {
                        break;
                    }
                    inst->setInstanceAttr(it2->first, it2->second);
                }
            }
        }

        /* Evaluate unions selector fields*/
        for (list<AdbInstance*>::iterator it = _unionSelectorEvalDeffered.begin(); 
             it != _unionSelectorEvalDeffered.end(); it++) {
            vector < string > path;
            AdbInstance *inst = *it;
            AdbInstance *curInst = inst;
            const string splitVal = inst->getInstanceAttr("union_selector");
            boost::algorithm::split(path, splitVal, boost::is_any_of(string(".")));
            for (size_t i = 0; i < path.size(); i++) {
                if (path[i] == "#(parent)" || path[i] == "$(parent)") {
                    curInst = curInst->parent;
                } else {
                    size_t j;
                    bool inPath = false;
                    for (j = 0; j < curInst->subItems.size(); j++) {
                        if (curInst->subItems[j]->name == path[i]) {
                            curInst = curInst->subItems[j];
                            inPath = true;
                            break;
                        }
                    }

                    if (j == curInst->subItems.size() && !inPath) {
                        if (rootNodeName == rootNode) { // give this warning only if this root instantiation
                            raiseException(allowMultipleExceptions, 
                                          "Failed to find union selector for union (" + inst->fullName() + ") Can't find field (" + path[i] + ") under (" + curInst->fullName() + ")",
                                          ExceptionHolder::ERROR_EXCEPTION);
                        }
                    }
                }
            }

            inst->unionSelector = curInst;
            for (size_t i = 0; i < inst->subItems.size(); i++) {
                //printf("Field %s, isResered=%d\n", inst->subItems[i]->fullName().c_str(), inst->subItems[i]->isReserved());
                if (inst->subItems[i]->isReserved()) {
                    continue;
                }

                // make sure all union subnodes define "selected_by" attribute
                bool found = false;
                AttrsMap::iterator selectorValIt = inst->subItems[i]->getInstanceAttrIterator("selected_by", found);
                if (!found) {
                    raiseException(allowMultipleExceptions, 
                                  "In union (" + inst->fullName() + ") the union subnode (" + inst->subItems[i]->name + ") doesn't define selection value",
                                  ExceptionHolder::ERROR_EXCEPTION);
                }

                // make sure that all union subnodes selector values are defined in the selector field enum
                if (selectorValIt->second == "") {
                    continue;
                }

                map<string, u_int64_t>::iterator it;
                map < string, u_int64_t > selectorValMap
                        = inst->unionSelector->getEnumMap();
                for (it = selectorValMap.begin(); it != selectorValMap.end(); it++) {
                    if (it->first == selectorValIt->second) {
                        break;
                    }
                }

                //if not found in map throw exeption
                if (it == selectorValMap.end()) {
                    string exceptionTxt = "In union (" + inst->fullName()
                            + ") the union subnode (" + inst->subItems[i]->name
                            + ") uses a selector value ("
                            + selectorValIt->second
                            + ") which isn't defined in the selector field ("
                            + inst->unionSelector->fullName() + ")";
                    raiseException(allowMultipleExceptions, 
                                  exceptionTxt,
                                  ExceptionHolder::ERROR_EXCEPTION);
                }
            }
        }

        return rootItem;
    } catch (AdbException &exp) {
        _lastError = exp.what_s();
        if (allowMultipleExceptions) {
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return NULL;
    } catch (...) {
        _lastError = "Unknown error occurred";
        return NULL;
    }
}

/**
 * Function: Adb::getNodeDeps
 **/
vector<string> Adb::getNodeDeps(string nodeName) {
    NodesMap::iterator it = nodesMap.find(nodeName);
    if (it == nodesMap.end()) {
        throw AdbException("Can't find node definition for: " + nodeName);
    }

    AdbNode *node = it->second;
    vector < string > deps(1, node->name);

    for (size_t i = 0; i < node->fields.size(); i++) {
        if (node->fields[i]->isStruct()) {
            deps.push_back(node->fields[i]->subNode);
            vector < string > subDeps = getNodeDeps(node->fields[i]->subNode);
            deps.insert(deps.end(), subDeps.begin(), subDeps.end());
        }
    }

    stable_sort(deps.begin(), deps.end());
    deps.erase(unique(deps.begin(), deps.end()), deps.end());
    return deps;
}

/**
 * Function: Adb::createInstance
 **/
vector<AdbInstance*> Adb::createInstance(AdbField *field,
        AdbInstance *parent, map<string, string> vars, bool isExprEval,
        AdbProgress *progressObj, int depth, bool ignoreMissingNodes,
        bool allowMultipleExceptions) {
    static const regex EXP_PATTERN(
            "\\s*([a-zA-Z0-9_]+)=((\\$\\(.*?\\)|\\S+|$)*)\\s*");
    if (progressObj) {
        progressObj->progress();
    }

    // if array create instance for each item. else - create 1
    vector<AdbInstance*> instList;
    for (u_int32_t i = 0; i < field->arrayLen(); i++) {
        AdbInstance *inst = new AdbInstance;
        inst->fieldDesc = field;

        // if field is struct - find field->subNode in nodes map and addto instance not desc
        if (field->isStruct()) {
            NodesMap::iterator it = nodesMap.find(field->subNode);
            if (it == nodesMap.end()) {
                delete inst;
                raiseException(allowMultipleExceptions, 
                              "Can't find the definition for subnode: " + field->subNode + " of field: " + field->name,
                              ExceptionHolder::ERROR_EXCEPTION);                
            } else {
                inst->nodeDesc = it->second;
            }
        }
        inst->name = field->name;
        inst->arrIdx = 0;
        inst->size = field->eSize();
        inst->parent = parent;

        if (field->offset == 0xffffffff) {
            if (parent->subItems.size() > 0) {
                field->offset = parent->subItems.back()->offset;
            } else {
                field->offset = parent->offset;
            }
        }
        inst->offset = calcArrOffset(field, parent, i);
        if (field->isArray()) {
            inst->name += "[" + boost::lexical_cast<string>(i + field->lowBound) + "]";
            inst->arrIdx = i;
        }
        //printf("field: %s, offset: %s (%d)\n", inst->name.c_str(),formatAddr(inst->offset, inst->size).c_str(), inst->offset);

        if (isExprEval) {
            try {
                // First add the special variables
                char tmpStr[32];
                vars["NAME"] = inst->name;
                vars["ARR_IDX"] = boost::lexical_cast<string>(inst->arrIdx);
                sprintf(tmpStr, "[%d:%d]", inst->offset % 32 + inst->size - 1,
                        inst->offset % 32);
                vars["BN"] = tmpStr;
                vars["parent"] = "#(parent)"; // special internal name

                // Get variables attribute value
                AttrsMap::iterator it = field->attrs.find("variables");
                string varStr = (it == field->attrs.end() ? string() : it->second);
                boost::algorithm::trim(varStr);

                // build var_name->value map from varAttrStr
                AttrsMap curVars;
                if (!varStr.empty()) {
                    match_results < string::const_iterator > what;
                    string::const_iterator start = varStr.begin();
                    string::const_iterator end = varStr.end();

                    while (regex_search(start, end, what, EXP_PATTERN)) {
                        string var(what[1].first, what[1].second);
                        string exp(what[2].first, what[2].second);
#if 0
                        printf("%s) %s <=> %s\n", inst->fullName().c_str(), var.c_str(), exp.c_str());
                        printf("Variable Attr: %s\n", inst->field->attrs["variables"].c_str());
#endif
                        start = what[0].second;
                        curVars[var] = exp;
                    }

                    for (AttrsMap::iterator it = curVars.begin(); it
                            != curVars.end(); it++) {
                        vars[it->first] = it->second;
                    }

                    // evaluate the variables themselves
                    for (AttrsMap::iterator it = curVars.begin(); it
                            != curVars.end(); it++) {
                        vars[it->first] = evalExpr(it->second, &vars);
                    }
                }

#if 0
                printf("Variables of: %s\n", inst->fullName().c_str());
                for (AttrsMap::iterator it = vars.begin(); it != vars.end(); it++) {
                    printf("\tVars: %s - %s\n", it->first.c_str(), it->second.c_str());
                }
#endif

                // evaluate other attrs
                for (AttrsMap::iterator it = field->attrs.begin(); it != field->attrs.end(); it++) {
                    if (it->first == "variables") {
                        continue;
                    }

                    inst->setInstanceAttr(it->first, evalExpr(it->second, &vars));
                }
                inst->setVarsMap(vars);
            } catch (AdbException &exp) {
                string exceptionTxt =
                        "Failed to evaluate expression for field ("
                                + inst->fullName() + "): " + exp.what_s();
                if (allowMultipleExceptions) {
                    insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                } else {
                    throw AdbException(exceptionTxt);
                }
            }
        } 
        // else {
        //     inst->copyAllInstanceAttr(field->attrs);
        // }

        /* if union and uses selecotr field add it to _unionSelectorEvalDeffered in order to defferred evaluation */
        bool found = false;
        inst->getInstanceAttrIterator("union_selector", found);
        if (inst->isUnion() && found) {
            _unionSelectorEvalDeffered.push_back(inst);
        }

        checkInstanceOffsetValidity(inst, parent, allowMultipleExceptions);

        if (field->isStruct() && !inst->nodeDesc->fields.empty() && (depth
                == -1 || depth > 0)) {
            // validation 2
            if (inst->size != inst->nodeDesc->size) {
                inst->nodeDesc->size = inst->size;
                /*throw AdbException("Node +(" + inst->name + ") size (" + boost::lexical_cast<string>(inst->size)) +
                 " isn't the same as its instance (" + inst->nodeDesc->name +
                 ") (" +  boost::lexical_cast<string>(inst->nodeDesc->size) + ")";*/
            }

            vector<AdbField*>::iterator it;
            for (it = inst->nodeDesc->fields.begin(); it
                    != inst->nodeDesc->fields.end(); it++) {
                map < string, string > varsCopy = vars;
                vector<AdbInstance*> subItems = createInstance(*it, inst, vars,
                        isExprEval, progressObj, depth == -1 ? -1 : depth - 1,
                        ignoreMissingNodes, allowMultipleExceptions);
                inst->subItems.insert(inst->subItems.end(), subItems.begin(),
                        subItems.end());
            }

            if (!inst->isUnion()) {
                stable_sort(inst->subItems.begin(), inst->subItems.end(),
                            compareFieldsPtr<AdbInstance> );

                for (size_t j = 0; j < inst->subItems.size() - 1; j++) {
                    //printf("field: %s, offset: %s\n", inst->subItems[j+1]->name.c_str(),formatAddr(inst->subItems[j+1]->offset, inst->subItems[j+1]->size).c_str());
                    //printf("field: %s, offset: %s\n", inst->subItems[j]->name.c_str(),formatAddr(inst->subItems[j]->offset, inst->subItems[j]->size).c_str());
                    if (inst->subItems[j + 1]->offset
                        < inst->subItems[j]->offset + inst->subItems[j]->size) {
                        string exceptionTxt = "Field ("
                                + inst->subItems[j + 1]->name + ") ("
                                + formatAddr(inst->subItems[j + 1]->offset,
                                        inst->subItems[j + 1]->size).c_str()
                                + ") overlaps with (" + inst->subItems[j]->name
                                + ") (" + formatAddr(inst->subItems[j]->offset,
                                inst->subItems[j]->size).c_str() + ")";
                        raiseException(allowMultipleExceptions, 
                              exceptionTxt,
                              ExceptionHolder::ERROR_EXCEPTION);  
                    }
                }
            }
        }

        instList.push_back(inst);
    }

    stable_sort(instList.begin(), instList.end(), compareFieldsPtr<AdbInstance> );
    return instList;
}

/**
 * Function: Adb::checkInstanceOffsetValidity
 **/
void Adb::checkInstanceOffsetValidity(AdbInstance *inst, AdbInstance *parent, bool allowMultipleExceptions)
{
    if (inst->offset + inst->size > parent->offset + parent->size) {
        string exceptionTxt = "Field (" + inst->name + ") " + formatAddr(
                inst->offset, inst->size) + " crosses its parent node ("
                + parent->name + ") " + formatAddr(parent->offset,
                parent->size) + " boundaries";
        if (allowMultipleExceptions) {
            insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
        } else {
            throw AdbException(exceptionTxt);
        }
    }
}

/**
 * Function: Adb::calcArrOffset
 **/
u_int32_t Adb::calcArrOffset(AdbField *fieldDesc, AdbInstance *parent,
        u_int32_t arrIdx) {
    int offs;

    if (fieldDesc->eSize() >= 32) {
        // Make sure this is dword aligned
        if (fieldDesc->eSize() % 32 || parent->offset % 32 || fieldDesc->offset
                % 32) {
            throw AdbException("Field " + fieldDesc->name + " isn't dword aligned");
        }
        offs = parent->offset + fieldDesc->offset + fieldDesc->eSize() * arrIdx;
    } else {
        if (bigEndianArr) {
            offs = (int) parent->offset + (int) fieldDesc->offset
                    - (int) fieldDesc->eSize() * arrIdx;

            int dwordDelta = abs((dword(parent->offset + fieldDesc->offset) - dword(offs)))/ 4;

            if (dwordDelta) {
                offs += 32 * 2 * dwordDelta;
            }
        } else {
            offs = parent->offset + fieldDesc->offset + fieldDesc->eSize()
                    * arrIdx;
        }
    }

    return offs;
}

/**
 * Function: Adb::evalExpr
 **/
string Adb::evalExpr(string expr, AttrsMap *vars) {
    if (expr.find('$') == string::npos) {
        return expr;
    }

    smatch what, what2;
    regex singleExpr("^([^\\$]*)(\\$\\(([^)]+)\\))(.*)$");
    while (regex_search(expr, what, singleExpr)) {
        string vname = what[3].str();
        string vvalue;
        regex singleVar("^[a-zA-Z_][a-zA-Z0-9_]*$");

        if (regex_search(vname, what2, singleVar)) {
            AttrsMap::iterator it = vars->find(vname);
            if (it == vars->end()) {
                throw AdbException("Can't find the variable: " + vname);
            }
            vvalue = it->second;
        } else {
            char exp[vname.size() + 1];
            char *expPtr = exp;
            strcpy(exp, vname.c_str());
            u_int64_t res;
            _adbExpr.setVars(vars);
            int status = _adbExpr.expr(&expPtr, &res);
            string statusStr;

            //printf("-D- Eval expr \"%s\" = %ul.\n", vname.ascii(), (u_int32_t)res);

            if (status < 0) {
                switch (status) {
                case Expr::ERR_RPAR_EXP:
                    statusStr = "Right parentheses expected";
                    break;

                case Expr::ERR_VALUE_EXP:
                    statusStr = "Value expected";
                    break;

                case Expr::ERR_BIN_EXP:
                    statusStr = "Binary operation expected ";
                    break;

                case Expr::ERR_DIV_ZERO:
                    statusStr = "Divide zero attempt";
                    break;

                case Expr::ERR_BAD_NUMBER:
                    statusStr = "Bad constant syntax";
                    break;

                case Expr::ERR_BAD_NAME:
                    statusStr = "Variable Name not resolved";
                    break;

                default:
                    statusStr = "Unknown error";

                }

                throw AdbException(
                        "Error evaluating expression " + expr + " : "
                                + statusStr);
            }

            vvalue = boost::lexical_cast<string>(res);
        }

        /*printf("what[0] - %s, what[1] - %s, what[2] - %s,  what[3] - %s, what[4] - %s\n",
         what[0].str().c_str(), what[1].str().c_str(),
         what[2].str().c_str(), what[3].str().c_str(),
         what[4].str().c_str());*/

        expr = what[1].str() + vvalue + what[4].str();
    }

    return expr;
}

/**
 * Function: Adb::checkInstSizeConsistency
 **/
bool Adb::checkInstSizeConsistency(bool allowMultipleExceptions) {
    bool status = true;
    for (NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
        for (size_t i = 0; i < it->second->fields.size(); i++) {
            if (it->second->fields[i]->isStruct()) {
                NodesMap::iterator iter = nodesMap.find(
                        it->second->fields[i]->subNode);
                if (iter == nodesMap.end()) {
                    continue;
                    /*
                     _lastError = "Can't find definition of subnode \"" + it->second->fields[i]->subNode +
                     "\" instantiated from node \"" + it->first + "\"";
                     return false;
                     */
                }
                AdbNode *node = nodesMap[it->second->fields[i]->subNode];
                if (node->size != it->second->fields[i]->size
                        / it->second->fields[i]->arrayLen()) {
                    char tmp[256];
                    sprintf(
                            tmp,
                            "Node (%s) size 0x%x.%d is not consistent with the instance (%s->%s) size 0x%x.%d",
                            node->name.c_str(), (node->size >> 5) << 2,
                            node->size % 32, it->second->name.c_str(),
                            it->second->fields[i]->name.c_str(),
                            (it->second->fields[i]->size >> 5) << 2,
                            it->second->fields[i]->size % 32);
                    _lastError = tmp;
                    if (allowMultipleExceptions) {
                        status = false;
                        insertNewException(ExceptionHolder::ERROR_EXCEPTION, tmp);
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    return status;
}

/**
 * Function: Adb::getLastError
 **/
string Adb::getLastError() {
    return _lastError;
}

/**
 * Function: Adb::print
 **/
void Adb::print(int indent) {
    cout << indentString(indent) << "Include paths: " << endl;
    for (size_t i = 0; i < includePaths.size(); i++)
        cout << indentString(indent + 1) << includePaths[i] << endl;

    cout << indentString(indent) << "Is Big Endian Arrays: " << bigEndianArr
            << endl;
    cout << "-------------------------------------" << endl;
    cout << indentString(indent) << "Configs: " << endl;
    for (size_t i = 0; i < configs.size(); i++)
        configs[i]->print(indent + 1);

    cout << "-------------------------------------" << endl;
    cout << indentString(indent) << "Nodes" << endl;
    NodesMap::iterator iter;
    for (iter = nodesMap.begin(); iter != nodesMap.end(); iter++)
        iter->second->print(indent + 1);
}

/*************************** AdbException Implementation ***************************/

AdbException::AdbException() {
}

/**
 * Function: AdbException::AdbException
 **/
AdbException::AdbException(const char *fmt, ...) {
    char tmp[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(tmp, fmt, args);
    va_end(args);
    _msg = tmp;
}

/**
 * Function: AdbException::AdbException
 **/
AdbException::AdbException(string msg) :
    _msg(msg) {
}

/**
 * Function: AdbException::~AdbException
 **/
AdbException::~AdbException() throw () {
}

/**
 * Function: AdbException::what
 **/
const char* AdbException::what() const throw () {
    return _msg.c_str();
}

/**
 * Function: AdbException::what_s
 **/
string AdbException::what_s() const {
    return _msg;
}

/*************************** AdbParser Implementation ***************************/
/**
 * Function: AdbParser::AdbParser
 **/
AdbParser::AdbParser(string fileName, Adb *adbCtxt, bool addReserved,
        AdbProgress *progressObj, bool strict, string includePath,
        bool enforceExtraChecks) :
    _adbCtxt(adbCtxt), _fileName(fileName), _addReserved(addReserved),
            _progressCnt(0), _progressObj(progressObj), _strict(strict),
            _includePath(includePath), _currentNode(0), _currentField(0),
            _currentConfig(0) {
    _enforceExtraChecks = enforceExtraChecks;
    if (includePath != "") {
        addIncludePaths(adbCtxt, includePath);
    }
    _xmlParser = XML_ParserCreate(0);
    XML_SetUserData(_xmlParser, this);
    XML_SetElementHandler(_xmlParser, startElement, endElement);
    if (adbCtxt->includePaths.size() == 0) {
        // first add the opened project path
        adbCtxt->includePaths.push_back(
                _fileName.find(OS_PATH_SEP) == string::npos ? "."
                        : _fileName.substr(0, _fileName.rfind(OS_PATH_SEP)));
        vector < string > path;
        boost::algorithm::split(path, fileName,
                boost::is_any_of(string(OS_PATH_SEP)));
        IncludeFileInfo info = { fileName, "ROOT", 0 };
        _adbCtxt->includedFiles[path[path.size() - 1]] = info;
    }
    _instanceOps = false;
}

void AdbParser::addIncludePaths(Adb *adbCtxt, string includePaths) {
    vector < string > paths;
        boost::algorithm::split(paths, includePaths,
                boost::is_any_of(string(";")));
        adbCtxt->includePaths.insert(adbCtxt->includePaths.end(),
                paths.begin(), paths.end());

        StringVector relatives;
        string
                projPath =
                        boost::filesystem::path(adbCtxt->mainFileName).parent_path().string();

        for (StringVector::iterator it = adbCtxt->includePaths.begin(); it
                != adbCtxt->includePaths.end(); it++) {
            if (projPath != "" && projPath != *it && boost::filesystem::path(*it).is_relative()) {
                relatives.push_back(projPath + OS_PATH_SEP + *it);
            }
        }

        adbCtxt->includePaths.insert(adbCtxt->includePaths.end(),
                relatives.begin(), relatives.end());
}

/**
 * Function: AdbParser::~AdbParser
 **/
AdbParser::~AdbParser() {
    XML_ParserFree(_xmlParser);
}

/**
 * Function: AdbParser::setAllowMultipleExceptionsTrue
 * This function is a static function to change the value of set all exceptions to true
 **/
void AdbParser::setAllowMultipleExceptionsTrue() {
    AdbParser::allowMultipleExceptions = true;
}

/**
 * Function: AdbParser::load
 **/
bool AdbParser::load() {
    FILE *file;
    char *data = NULL;
    file = fopen(_fileName.c_str(), "r");
    _adbCtxt->_logFile.appendLogFile("Opening " + _fileName + "\n");

    if (!file) {
        _lastError = "Can't open file (" + _fileName + ") for reading: "
                + strerror(errno);
        if (allowMultipleExceptions) {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    if (fseek(file, 0L, SEEK_END) < 0) {// go to the end of the file
        _lastError = "fseek() failed for file (" + _fileName + "): "
                + strerror(errno);
        fclose(file);
        if (allowMultipleExceptions) {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    long fSize = ftell(file);
    if (fSize < 0) {
        _lastError = "ftell() failed for file (" + _fileName + "): "
                + strerror(errno);
        fclose(file);
        if (allowMultipleExceptions) {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    data = (char*) malloc(fSize + 1);
    if (!data) {
        fclose(file);
        throw AdbException("Out of memory.");
    }

    if (fseek(file, 0L, SEEK_SET) < 0) { //go back to the start of the file
        _lastError = "Failed to read file (" + _fileName + "): " + strerror(
                errno);
        fclose(file);
        free(data);
        data = NULL;
        if (allowMultipleExceptions) {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    size_t result = fread(data, fSize, 1, file);
    if (result != 1) {
        _lastError = "Failed to read file (" + _fileName + "): " + strerror(
                errno);
        fclose(file);
        free(data);
        data = NULL;
        if (allowMultipleExceptions) {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    data[fSize] = 0;
    fclose(file);

    bool xmlStatus = true;
    try {
        if (!XML_Parse(_xmlParser, data, strlen(data), 0)) {
            enum XML_Error errNo = XML_GetErrorCode(_xmlParser);
            throw AdbException(
                    string("XML parsing issues: ") + XML_ErrorString(errNo));
        }
    } catch (AdbException& exp) {
        if (exp.what_s().find("in file:") == string::npos) {
            int line = XML_GetCurrentLineNumber(_xmlParser);
            int column = XML_GetCurrentColumnNumber(_xmlParser);
            _lastError = exp.what_s() + " in file: " + _fileName + " at line: "
                    + boost::lexical_cast<string>(line) + " column: "
                    + boost::lexical_cast<string>(column);
        } else {
            _lastError = exp.what_s();
        }
        if (allowMultipleExceptions) {
            xmlStatus = false;
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        } else {
            free(data);
            return false;
        }
    } catch (std::runtime_error& e) {
        _lastError = CHECK_RUNTIME_ERROR(e);
        if (allowMultipleExceptions) {
            xmlStatus = false;
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        } else {
            free(data);
            return false;
        }
    } catch (...) {
        int line = XML_GetCurrentLineNumber(_xmlParser);
        int column = XML_GetCurrentColumnNumber(_xmlParser);
        _lastError = string(
                "An exception raised during the loading of the file: ")
                + _fileName + " at line: " + boost::lexical_cast<string>(line)
                + " column: " + boost::lexical_cast<string>(column);
        if (allowMultipleExceptions) {
            xmlStatus = false;
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        } else {
            free(data);
            return false;
        }
    }

    free(data);
    return xmlStatus;
}

/**
 * Function: AdbParser::loadFromString
 **/
bool AdbParser::loadFromString(const char *adbString) {
    _fileName = "\"STRING\"";
    try {
        if (!XML_Parse(_xmlParser, adbString, strlen(adbString), 0)) {
            enum XML_Error errNo = XML_GetErrorCode(_xmlParser);
            throw AdbException(
                    string("XML parsing issues: ") + XML_ErrorString(errNo));
        }
    } catch (AdbException& exp) {
        if (exp.what_s().find("in file:") == string::npos) {
            int line = XML_GetCurrentLineNumber(_xmlParser);
            int column = XML_GetCurrentColumnNumber(_xmlParser);
            _lastError = exp.what_s() + " in file: " + _fileName + " at line: "
                    + boost::lexical_cast<string>(line) + " column: "
                    + boost::lexical_cast<string>(column);
        } else {
            _lastError = exp.what_s();
        }

        _lastError += string(
                "\nNOTE: this project is configured to work with: \"")
                + (_adbCtxt->bigEndianArr ? "Big" : "Little")
                + " Endian Arrays\"";
        return false;
    } catch (std::runtime_error& e) {
        _lastError = CHECK_RUNTIME_ERROR(e);
        return false;
    } catch (...) {
        int line = XML_GetCurrentLineNumber(_xmlParser);
        int column = XML_GetCurrentColumnNumber(_xmlParser);
        _lastError = string(
                "An exception raised during the loading of the file: ")
                + _fileName + " at line: " + boost::lexical_cast<string>(line)
                + " column: " + boost::lexical_cast<string>(column);
        return false;
    }

    return true;
}

/**
 * Function: AdbParser::getError
 **/
string AdbParser::getError() {
    return _lastError;
}

/**
 * Function: AdbParser::attrsCount
 **/
int AdbParser::attrCount(const XML_Char **atts) {
    int i = 0;
    while (atts[i]) {
        i++;
    }
    return i / 2;
}

/**
 * Function: AdbParser::attrValue
 **/
string AdbParser::attrValue(const XML_Char **atts, const XML_Char *attrName) {
    int i = 0;
    while (atts[i]) {
        if (!strcmp(atts[i], attrName)) {
            return string(atts[i + 1]);
        }
        i += 2;
    }

    return string();
}

/**
 * Function: AdbParser::attrName
 **/
string AdbParser::attrName(const XML_Char **atts, int i) {
    return string(atts[i * 2]);
}

/**
 * Function: AdbParser::attrName
 **/
string AdbParser::attrValue(const XML_Char **atts, int i) {
    return string(atts[i * 2 + 1]);
}

/**
 * Function: AdbParser::findFile
 **/
string AdbParser::findFile(string fileName) {
    FILE *f;

    for (size_t i = 0; i < _adbCtxt->includePaths.size(); i++) {
        string filePath = _adbCtxt->includePaths[i] + OS_PATH_SEP + fileName;
        f = fopen(filePath.c_str(), "r");
        if (f) {
            fclose(f);
            return filePath;
        } else if (fileName.find(_adbCtxt->includePaths[i]) != string::npos) { // includePath is part of fileName
            f = fopen(fileName.c_str(), "r");
            if (f) {
                fclose(f);
                return fileName;
            }
        }
    }
    return string();
}

/**
 * Function: AdbParser::addr2int
 **/
u_int32_t AdbParser::addr2int(string& s) {
    try {
        u_int32_t res;
        boost::algorithm::to_lower(s);
        char *end;
        vector < string > words;
        boost::algorithm::split(words, s, boost::is_any_of(string(".")));

        // fix for cases like: 0x.16
        if (words.size() && !words[0].compare("0x")) {
            words[0] = "0";
        }

        switch (words.size()) {
        case 1:
            res = strtoul(words[0].c_str(), &end, 0);
            if (*end != '\0') {
                throw AdbException();
            }

            res *= 8;
            break;

        case 2:
            if (words[0].empty()) {
                // .DDD form
                res = strtoul(words[1].c_str(), &end, 0);
                if (*end != '\0') {
                    throw AdbException();
                }
            } else {
                // 0xHHHHH.DDD or DDDDD.DDD form
                res = strtoul(words[0].c_str(), &end, 0);
                if (*end != '\0') {
                    throw AdbException();
                }
                res *= 8;
                res += strtoul(words[1].c_str(), &end, 0);
                if (*end != '\0') {
                    throw AdbException();
                }
            }
            break;

        default:
            throw AdbException("Invalid size: " + s);
        }

        return res;
    } catch (AdbException& exp) {
        throw AdbException(
                "Failed to retrieve integer from string: " + exp.what_s());
    }
}

/**
 * Function: AdbParser::dword
 **/
u_int32_t AdbParser::dword(u_int32_t offset) {
    return (offset >> 5) << 2;
}

/**
 * Function: AdbParser::startBit
 **/
u_int32_t AdbParser::startBit(u_int32_t offset) {
    return offset % 32;
}

/**
 * Function: AdbParser::descXmlToNative
 **/
string AdbParser::descXmlToNative(const string& desc) {
    return boost::replace_all_copy(desc, "\\;", "\n");
}

/**
 * Function: AdbParser::descNativeToXml
 **/
string AdbParser::descNativeToXml(const string& desc) {
    return boost::replace_all_copy(desc, "\n", "\\;");
}

/**
 * Function: AdbParser::includeFile
 **/
void AdbParser::includeFile(AdbParser *adbParser, string fileName,
        int lineNumber) {
    // add this file to the included files map
    string filePath;
    FILE *probeFile = NULL;

    if (!boost::filesystem::path(fileName).is_relative()) {
        probeFile = fopen(fileName.c_str(), "r");
    }

    if (probeFile) {
        fclose(probeFile);
        filePath = fileName;
    } else {
        filePath = adbParser->findFile(fileName);
    }
    if (filePath.empty()) {
        throw AdbException(string() + "Can't find the file: " + fileName);
    }

    // Update filename to be only base name with extension to prevent duplications
    boost::filesystem::path boostPath(filePath);
    fileName = boostPath.filename().string();

    if (!adbParser->_adbCtxt->includedFiles.count(fileName)) {
        IncludeFileInfo info = { filePath, adbParser->_fileName, lineNumber };
        adbParser->_adbCtxt->includedFiles[fileName] = info;

        // parse the included file
        AdbParser p(filePath, adbParser->_adbCtxt, adbParser->_addReserved,
                adbParser->_progressObj, adbParser->_strict,
                "", adbParser->_enforceExtraChecks);
        if (!p.load()) {
            throw AdbException(p.getError());
        }
    }
}

/**
 * Function: AdbParser::includeAllFilesInDir
 **/
void AdbParser::includeAllFilesInDir(AdbParser *adbParser, string dirPath,
        int lineNumber) {
    vector < string > paths;
    boost::algorithm::split(paths, dirPath, boost::is_any_of(string(";")));

    for (StringVector::iterator pathIt = paths.begin(); pathIt != paths.end(); pathIt++) {
        boost::filesystem::path fsPath(*pathIt);
        if (boost::filesystem::exists(fsPath)
                && boost::filesystem::is_directory(fsPath)) {
                    addIncludePaths(adbParser->_adbCtxt, *pathIt);
            boost::filesystem::directory_iterator filesIter(fsPath), dirEnd;
            for (; filesIter != dirEnd; ++filesIter) {
                if (boost::filesystem::is_regular_file(filesIter->status())
                        && filesIter->path().extension() == ".adb") {
                    try {
                        includeFile(adbParser, filesIter->path().string(),
                                lineNumber);
                    } catch (AdbException &e) {
                        throw(e);
                    }
                }
            }
        }
    }
}

/**
 *  Function AdbParser::checkSpecialChars
 */
bool AdbParser::checkSpecialChars(string tagName) {
    smatch match;
    regex allowedCharsExpr("[^\\w\\[\\]]"); // only alphanumeric and square brackets are allowed
    if (regex_search(tagName, match, allowedCharsExpr)) {
        return false;
    }
    regex checkArrayExpr("[\\[\\]]"); // this check if containing the array brackets
    if (regex_search(tagName, match, checkArrayExpr)) {
        regex correctNameForArrayExpr("[_A-Za-z][\\w]*\\[[\\d]+\\]$");
        if (!regex_search(tagName, match, correctNameForArrayExpr)) { // check the name if correct the square brackets (array)
            return false;
        }
    } else {
        regex correctNameNoneArrayExpr("[_A-Za-z][\\w]*$");
        if (!regex_search(tagName, match, correctNameNoneArrayExpr)) { // check the name if correct without the square brackets (not array)
            return false;
        }
    }
    return true;
}

bool AdbParser::checkHEXFormat(string addr) {
    smatch match;
    regex correctHEXExpr("(0x)?[0-9A-Fa-f]+?(.0)?$");
    if (!regex_search(addr, match, correctHEXExpr)) {
        return false;
    }
    return true;
}

bool AdbParser::checkBigger32(string num) {
    std::istringstream iss(num);
    std::string token;
    std::getline(iss, token, '.');
    if (std::getline(iss, token, '.')) { // the second part of the size after the . max to be 32 0x0.0
        if (addr2int(token) / 8 >= 32) {
            return true;
        }
    }
    return false;
}

void AdbParser::startNodesDefElement(const XML_Char **atts, AdbParser *adbParser) 
{
    if (adbParser->_adbCtxt->version == "") {
        if ((attrCount(atts) == 1) && (attrName(atts, 0) == "version")) {
            string adbVersion = attrValue(atts, 0);
            if (adbVersion != "1" && adbVersion != "1.0" && adbVersion != "2") {
                throw AdbException("Requested Adb Version (%s) is not supported. Supporting only version 1 or 2", adbVersion.c_str());
            }
            if (adbVersion == "1.0") {
                adbParser->_adbCtxt->version = "1";
            } else {
                adbParser->_adbCtxt->version = adbVersion;
            }
        } else if (attrCount(atts) == 0 ) {
            adbParser->_adbCtxt->version = "1";
        } else {
            throw AdbException("\"NodesDefinition\" tag can only have \"version\" attribute and only once");
        }
    }
}


void AdbParser::startEnumElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber) 
{
    bool expFound = false;
    if (!adbParser->_currentConfig || 
        !adbParser->_currentConfig->attrs.count("type") || 
        TAG_ATTR_ENUM.compare(adbParser->_currentConfig->attrs["type"])) {
        expFound = raiseException(allowMultipleExceptions,
                    "\"enum\" tag must be inside relevant \"config\" tag" , 
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber), 
                    ExceptionHolder::ERROR_EXCEPTION);
    }

    string tagName = attrValue(atts, "name");
    string value = attrValue(atts, "value");
    if (adbParser->_enforceExtraChecks) {
        if (!AdbParser::checkSpecialChars(tagName)) {
            expFound = raiseException(allowMultipleExceptions, 
                        "Invalid character in enum name, in enum: \"" + tagName + "\"",
                        ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                        ExceptionHolder::WARN_EXCEPTION);    
        }
    }
    if (tagName.empty() || value.empty()) {
        expFound = raiseException(allowMultipleExceptions, 
                    "Both \"name\" and \"value\" attributes must be specified",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::ERROR_EXCEPTION);  
    }
    if (!expFound) {
        adbParser->_currentConfig->enums.insert( pair<string, string> (tagName, value));
    }
}

void AdbParser::startConfigElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber) 
{
    bool expFound = false;
    if (adbParser->_currentConfig) {
        expFound = raiseException(allowMultipleExceptions, 
                            "config tag can't appear within other config",
                            ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                            ExceptionHolder::FATAL_EXCEPTION);
    }

    adbParser->_currentConfig = new AdbConfig;
    for (int i = 0; i < attrCount(atts); i++) {
        // First add this config to context
        string aName = attrName(atts, i);
        string aValue = attrValue(atts, i);
        adbParser->_currentConfig->attrs.insert(
                pair<string, string> (aName, aValue));

        // Parse attrs that affect the parser itself
        if (!TAG_ATTR_BIG_ENDIAN.compare(aName)) {
            try {
                int val = boost::lexical_cast<int>(aValue);
                adbParser->_adbCtxt->bigEndianArr = val != 0;
            } catch (std::exception&) {
                expFound = raiseException(allowMultipleExceptions, 
                                        string("Filed to parse the \"") + aName + "\" attribute value: \"" + aValue + "\"",
                                        ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                                        ExceptionHolder::ERROR_EXCEPTION);
            }
        }

        if (!TAG_ATTR_SINGLE_ENTRY_ARR.compare(aName)) {
            try {
                int val = boost::lexical_cast<int>(aValue);
                adbParser->_adbCtxt->singleEntryArrSupp = val != 0;
            } catch (std::exception&) {
                expFound = raiseException(allowMultipleExceptions, 
                                         string("Filed to parse the \"") + aName + "\" attribute value: \"" + aValue + "\"",
                                         ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                                         ExceptionHolder::ERROR_EXCEPTION);                                        
            }
        }

        if (!expFound && !TAG_ATTR_INCLUDE_PATH.compare(aName)) {
            vector < string > paths;
            boost::algorithm::split(paths, aValue, boost::is_any_of(string(";")));
            adbParser->_adbCtxt->includePaths.insert(adbParser->_adbCtxt->includePaths.end(), 
                                                     paths.begin(), paths.end());

            StringVector relatives;
            string
                    projPath = boost::filesystem::path(
                                    adbParser->_adbCtxt->mainFileName).parent_path().string();

            for (StringVector::iterator it =
                    adbParser->_adbCtxt->includePaths.begin(); it
                    != adbParser->_adbCtxt->includePaths.end(); it++) {
                if (boost::filesystem::path(*it).is_relative()) {
                    relatives.push_back(projPath + OS_PATH_SEP + *it);
                }
            }

            adbParser->_adbCtxt->includePaths.insert(
                    adbParser->_adbCtxt->includePaths.end(),
                    relatives.begin(), relatives.end());
        }
    }
}

void AdbParser::startInfoElement(const XML_Char **atts, AdbParser *adbParser) 
{
    string docName = attrValue(atts, "source_doc_name");
    string docVer = attrValue(atts, "source_doc_version");
    adbParser->_adbCtxt->srcDocName = docName;
    adbParser->_adbCtxt->srcDocVer = docVer;
}

void AdbParser::startIncludeElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber)
{
    string includeAttr = attrName(atts, 0);
    boost::algorithm::trim(includeAttr);

    bool expFound = false;
    if (includeAttr == "file") {
        string fname = attrValue(atts, "file");
        boost::algorithm::trim(fname);
        if (fname.empty()) {
            expFound = raiseException(allowMultipleExceptions,
                    string() + "File attribute isn't given within " + TAG_INCLUDE + " tag",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
        }
        if (!expFound)
            includeFile(adbParser, fname, lineNumber);
    } 
    else if (includeAttr == "dir") {
        string includeAllDirPath = attrValue(atts, "dir");
        boost::algorithm::trim(includeAllDirPath);
        if (includeAllDirPath.empty()) {
            expFound = raiseException(allowMultipleExceptions,
                        string() + "Directory to include isn't given within " + TAG_INCLUDE + " tag",
                        ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                        ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound)
            includeAllFilesInDir(adbParser, includeAllDirPath, lineNumber);
    } else {
        expFound = raiseException(allowMultipleExceptions,
                        string() + "Include is called without file or dir attribute.",
                        ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                        ExceptionHolder::ERROR_EXCEPTION);
    }
}

void AdbParser::startInstOpAttrReplaceElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber)
{
    bool expFound = false;
    if (!adbParser->_instanceOps) {
        expFound = raiseException(allowMultipleExceptions,
                        "Operation attr_replace must be defined within <instance_ops> element only.",
                        ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                        ExceptionHolder::FATAL_EXCEPTION);
    }

    string path = attrValue(atts, "path");
    if (path.empty()) {
        expFound = raiseException(allowMultipleExceptions,
                        "path attribute is missing in attr_replace operation",
                        ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                        ExceptionHolder::ERROR_EXCEPTION);

    }

    if (!expFound) {
        adbParser->_adbCtxt->instAttrs[path] = AttrsMap();
        for (int i = 0; i < attrCount(atts); i++) {
            string attrN = attrName(atts, i);
            if (attrN == "path") {
                continue;
            }

            string attrV = attrValue(atts, i);
            adbParser->_adbCtxt->instAttrs[path][attrN] = attrV;
        }
    }
}

void AdbParser::startNodeElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber)
{
    if (adbParser->_currentNode) {
        raiseException(allowMultipleExceptions,
                    "Nested nodes are not allowed",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    string nodeName = attrValue(atts, "name");
    boost::algorithm::trim(nodeName);
    string size = attrValue(atts, "size");

    if (adbParser->_enforceExtraChecks) {
        if (!AdbParser::checkSpecialChars(nodeName)) {
            raiseException(allowMultipleExceptions,
                    "Invalid character in node name, in Node: \"" + nodeName + "\"",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (AdbParser::checkBigger32(size)) { // the second part of the size after the . max to be 32 0x0.0
            raiseException(allowMultipleExceptions,
                    "Invalid size format, valid format 0x0.0 not allowed to be more than 0x0.31",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (addr2int(size) == 0) {
            raiseException(allowMultipleExceptions,
                    "Node Size is not allowed to be 0, in Node: \"" + nodeName + "\"",
                    ", in file: \""  + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::ERROR_EXCEPTION);
        }
    }
    string desc = descXmlToNative(attrValue(atts, "descr"));

    // Check for mandatory attrs
    if (nodeName.empty()) {
        raiseException(allowMultipleExceptions,
                   "Missing node name",
                   ", in file: \""  + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                   ExceptionHolder::FATAL_EXCEPTION);
        
    }
    if (size.empty()) {
        raiseException(allowMultipleExceptions,
                   "Missing node size",
                   ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                   ExceptionHolder::FATAL_EXCEPTION);
    }

    // Check for duplications
    if (adbParser->_adbCtxt->nodesMap.count(nodeName)) {
        raiseException(allowMultipleExceptions,
                    "node \"" + nodeName  + "\" is already defined in file: \"" + adbParser->_adbCtxt->nodesMap[nodeName]->fileName + "\" line: " + boost::lexical_cast<string>(adbParser->_adbCtxt->nodesMap[nodeName]->lineNumber),
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    adbParser->_currentNode = new AdbNode;
    adbParser->_currentNode->name = nodeName;
    adbParser->_currentNode->size = addr2int(size);
    adbParser->_currentNode->desc = desc;
    string unionAttrVal = attrValue(atts, "attr_is_union");
    adbParser->_currentNode->isUnion = !unionAttrVal.empty()
            && boost::lexical_cast<int>(unionAttrVal) != 0;
    adbParser->_currentNode->fileName = adbParser->_fileName;
    adbParser->_currentNode->lineNumber = lineNumber;

    if (adbParser->_strict && adbParser->_currentNode->isUnion
            && adbParser->_currentNode->size % 32) {
        //throw AdbException("union must be dword aligned");
    }

    // Add all node attributes
    for (int i = 0; i < attrCount(atts); i++) {
        if (attrValue(atts, i) == "") {
            continue;
        }
        adbParser->_currentNode->attrs[attrName(atts, i)] = attrValue(atts, i);
    }
}

void AdbParser::startFieldElement(const XML_Char **atts, AdbParser *adbParser, const int lineNumber)
{
    bool expFound = false;
    if (!adbParser->_currentNode) {
        expFound = raiseException(allowMultipleExceptions,
                    "Field definition outside of node",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    if (adbParser->_currentField) {
        expFound = raiseException(allowMultipleExceptions,
                    "Nested fields are not allowed",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    string fieldName = attrValue(atts, "name");
    boost::algorithm::trim(fieldName);
    string offset = attrValue(atts, "offset");
    string size = attrValue(atts, "size");

    if (adbParser->_enforceExtraChecks) {
        if (addr2int(size) % 32 == 0 && !AdbParser::checkHEXFormat(size)) 
        {
            expFound = raiseException(allowMultipleExceptions,
                    "Invalid size format",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (!AdbParser::checkHEXFormat(offset)) 
        {
            expFound = raiseException(allowMultipleExceptions,
                    "Invalid offset format",
                    ", in file: \""  + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (!AdbParser::checkSpecialChars(fieldName)) 
        {
            expFound = raiseException(allowMultipleExceptions,
                    "Invalid character in field name, in Field: \"" + fieldName + "\"",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (!expFound && adbParser->_currentNode->isUnion  && addr2int(offset) != 0) 
        {
            expFound = raiseException(allowMultipleExceptions,
                    "Offset must be 0x0.0 in Union fields",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (AdbParser::checkBigger32(size)) 
        { // the second part of the size after the . max to be 32 0x0.0
            expFound = raiseException(allowMultipleExceptions,
                    "Invalid size format, valid format 0x0.0 not allowed to be more than 0x0.31",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (AdbParser::checkBigger32(offset)) 
        { // the second part of the size after the . max to be 32 0x0.0
            expFound = raiseException(allowMultipleExceptions,
                    "Invalid offset format, valid format 0x0.0 not allowed to be more than 0x0.31",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
        if (addr2int(size) == 0) 
        {
            expFound = raiseException(allowMultipleExceptions,
                    "Field Size is not allowed to be 0, in Field: \"" + fieldName + "\"",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::WARN_EXCEPTION);
        }
    }

    string desc = descXmlToNative(attrValue(atts, "descr"));
    string lowBound = attrValue(atts, "low_bound");
    string highBound = attrValue(atts, "high_bound");

    if (lowBound != "" && highBound != "") {
        int low = atoi(lowBound.c_str());
        int high = 0;
        if (highBound != "VARIABLE") {
            high = atoi(highBound.c_str());
        }
        int isize = addr2int(size);
        int entrySize = isize / (high - low + 1);
        if (entrySize % 8 != 0 && entrySize > 8) 
        {
            expFound = raiseException(allowMultipleExceptions,
                   "Invalid size of array entries",
                   ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                   ExceptionHolder::ERROR_EXCEPTION);
        }
        if (entrySize < 8 && entrySize != 4 && entrySize != 2 && entrySize
                != 1 && ((isize > 32 && highBound != "VARIABLE")
                || highBound == "VARIABLE")) 
        {
            expFound = raiseException(allowMultipleExceptions,
                    "Array with entry size 3, 5, 6 or 7 bits and array size is larger than 32bit",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::ERROR_EXCEPTION);
        }
    }

    string subNode = attrValue(atts, "subnode");

    // Check for mandatory attrs
    if (fieldName.empty()){
        expFound = raiseException(allowMultipleExceptions,
                    "Missing field name",
                    ", in file: \""  + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    if (size.empty()) {
        expFound = raiseException(allowMultipleExceptions,
                    "Missing field size",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    // Create new fields
    adbParser->_currentField = new AdbField;

    // Fill the new fields
    adbParser->_currentField->name = fieldName;
    adbParser->_currentField->desc = desc;
    adbParser->_currentField->size = addr2int(size);
    if (adbParser->_adbCtxt->singleEntryArrSupp) {
        int low = -1;
        int high = -1;
        if (!lowBound.empty()) {
            low = atoi(lowBound.c_str());
        }
        if (!highBound.empty()) {
            high = atoi(highBound.c_str());
        }
        adbParser->_currentField->definedAsArr = (low == high)
                && (low >= 0);
    } else {
        adbParser->_currentField->definedAsArr = false;
    }

    adbParser->_currentField->lowBound = lowBound.empty() ? 0
            : boost::lexical_cast<u_int32_t>(lowBound);
    if (highBound == "VARIABLE") {
        adbParser->_currentField->highBound = 0;
        adbParser->_currentField->unlimitedArr = true;
    } else {
        adbParser->_currentField->highBound = highBound.empty() ? 0
                : boost::lexical_cast<u_int32_t>(highBound);
    }
    adbParser->_currentField->subNode = subNode;

    // Check array element size
    if (adbParser->_currentField->isArray()
            && !adbParser->_currentField->isUnlimitedArr()
            && adbParser->_currentField->size
                    % (adbParser->_currentField->arrayLen())) {
        char exceptionTxt[1000];
        sprintf(exceptionTxt,
                "In field \"%s\" invalid array element size\"%0.2f\" in file: \"%s\" line: %d",
                fieldName.c_str(),
                ((double) adbParser->_currentField->size
                        / (adbParser->_currentField->arrayLen())),
                adbParser->_fileName.c_str(), lineNumber);
    
        expFound = raiseException(allowMultipleExceptions,
                    exceptionTxt,
                    "",
                    ExceptionHolder::FATAL_EXCEPTION);
    }
    if (offset.empty()) {
        if (adbParser->_currentNode->fields.empty()) {
            adbParser->_currentField->offset = 0;
        } else {
            AdbField *lastField = adbParser->_currentNode->fields.back();
            adbParser->_currentField->offset = lastField->offset
                    + lastField->size;
        }
    } else {
        adbParser->_currentField->offset = addr2int(offset);
    }

    // Very tricky but works well for big endian arrays support - on endElement we will fix the address again
    if (!expFound && adbParser->_adbCtxt->bigEndianArr) {
        u_int32_t offset = adbParser->_currentField->offset;
        u_int32_t size = adbParser->_currentField->eSize();

        adbParser->_currentField->offset = ((offset >> 5) << 5)
                + ((MIN(32, adbParser->_currentNode->size) - ((offset
                        + size) % 32)) % 32);
    }

    if (!expFound && adbParser->_strict
            && adbParser->_currentNode->isUnion
            && adbParser->_currentField->isLeaf()) 
    {
        expFound = raiseException(allowMultipleExceptions,
                    "Fields are not allowed in unions (only subnodes)",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    if (!expFound && adbParser->_strict
            && adbParser->_currentNode->isUnion
            && adbParser->_currentField->size % 32) 
    {
        expFound = raiseException(allowMultipleExceptions,
                    "Union is allowed to contains only dword aligned subnodes",
                    ", in file: \""  + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    if (!expFound && adbParser->_currentNode->isUnion
            && adbParser->_currentField->size
                    > adbParser->_currentNode->size) 
    {
        expFound = raiseException(allowMultipleExceptions,
                    "Field size is greater than the parent node size",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }

    if (!expFound && adbParser->_strict
            && !adbParser->_currentField->isArray()
            && adbParser->_currentField->isLeaf()
            && adbParser->_currentField->size > 32) 
    {
        expFound = raiseException(allowMultipleExceptions,
                    "Leaf fields can't be > 32 bits",
                    ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                    ExceptionHolder::FATAL_EXCEPTION);
    }
    // Add all field attributes
    if (!expFound) {
        for (int i = 0; i < attrCount(atts); i++) {
            adbParser->_currentField->attrs[attrName(atts, i)] = attrValue(
                    atts, i);
        }
    }
}

/**
 * Function: AdbParser::startElement
 **/
void AdbParser::startElement(void *_adbParser, const XML_Char *name, const XML_Char **atts) 
{
    AdbParser *adbParser = static_cast<AdbParser*> (_adbParser);

    int lineNumber = XML_GetCurrentLineNumber(adbParser->_xmlParser);
    adbParser->_currentTagValue = "";

    if (TAG_NODES_DEFINITION == name) {
        startNodesDefElement(atts, adbParser);
    }
    else if (TAG_ENUM == name) {
        startEnumElement(atts, adbParser, lineNumber);
    }
    else if (TAG_CONFIG == name) {
        startConfigElement(atts, adbParser, lineNumber); 
    }
    else if (TAG_INFO == name) {
        startInfoElement(atts, adbParser); 
    }
    else if (TAG_INCLUDE == name) {
        startIncludeElement(atts, adbParser, lineNumber); 
    }
    else if (TAG_INSTANCE_OPS == name) {
        adbParser->_instanceOps = true;
    }
    else if (TAG_INSTANCE_OP_ATTR_REPLACE == name) {
        startInstOpAttrReplaceElement(atts, adbParser, lineNumber);
    }
    else if (TAG_NODE == name) {
        startNodeElement(atts, adbParser, lineNumber);
    }
    else if (TAG_FIELD == name) {
        startFieldElement(atts, adbParser, lineNumber);
    }
    else if (TAG_RCS_HEADERS == name) {
        // DO NOTHING
    } else {
        string exceptionTxt = "Unsupported tag: " + string(name);
        if (allowMultipleExceptions)
        {
            exceptionTxt = exceptionTxt + ", in file: \"" + adbParser->_fileName + "\" line: " 
                           + boost::lexical_cast<string>(lineNumber);
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, exceptionTxt);
            return;
        } else {
            throw AdbException(exceptionTxt);
        }
    }
}

/**
 * Function: AdbParser::addReserved
 **/
void AdbParser::addReserved(vector<AdbField*> &reserveds, u_int32_t offset,
        u_int32_t size) {
    u_int32_t numOfDwords = (dword(offset + size - 1) - dword(offset)) / 4 + 1;

    //printf("==> %s\n", formatAddr(offset, size).c_str());
    //printf("numOfDwords = %d\n", numOfDwords);

    if (numOfDwords == 1 || ((offset % 32) == 0 && ((offset + size) % 32) == 0)) {
        AdbField *f1 = new AdbField;
        f1->name = "reserved";
        f1->offset = offset;
        f1->isReserved = true;
        f1->size = size;

        reserveds.push_back(f1);
        //printf("case1: reserved0: %s\n", formatAddr(f1->offset, f1->size).c_str());
    } else if (numOfDwords == 2) {
        AdbField *f1 = new AdbField;
        f1->name = "reserved";
        f1->offset = offset;
        f1->isReserved = true;
        f1->size = 32 - startBit(offset);

        AdbField *f2 = new AdbField;
        f2->name = "reserved";
        f2->offset = dword(offset + 32) * 8;
        f2->isReserved = true;
        f2->size = size - f1->size;
        reserveds.push_back(f1);
        reserveds.push_back(f2);
        /*printf("case2: reserved0: %s, reserved1: %s\n",
         formatAddr(f1->offset, f1->size).c_str(),
         formatAddr(f2->offset, f2->size).c_str());*/
    } else {
        AdbField *f1 = new AdbField;
        f1->name = "reserved";
        f1->offset = offset;
        f1->isReserved = true;
        f1->size = 32 - startBit(offset);

        AdbField *f2 = new AdbField;
        f2->name = "reserved";
        f2->offset = dword(offset + 32) * 8;
        f2->isReserved = true;
        f2->size = (numOfDwords - 2) * 32;

        if (!((offset + size) % 32)) {
            f2->size = (numOfDwords - 1) * 32;
            reserveds.push_back(f1);
            reserveds.push_back(f2);
            /*printf("case3.1: reserved0: %s, reserved1: %s\n",
             formatAddr(f1->offset, f1->size).c_str(),
             formatAddr(f2->offset, f2->size).c_str());*/
            return;
        } else {
            if (!(f1->size % 32)) {
                f1->size = (numOfDwords - 1) * 32;
                f2->size = size - f1->size;
                f2->offset = f1->offset + f1->size;
                reserveds.push_back(f1);
                reserveds.push_back(f2);
                /*printf("case3.2: reserved0: %s, reserved1: %s\n",
                 formatAddr(f1->offset, f1->size).c_str(),
                 formatAddr(f2->offset, f2->size).c_str());*/
                return;
            } else {
                f2->size = (numOfDwords - 2) * 32;
                AdbField *f3 = new AdbField;
                f3->name = "reserved";
                f3->offset = f2->offset + f2->size;
                f3->isReserved = true;
                f3->size = size - f1->size - f2->size;
                reserveds.push_back(f1);
                reserveds.push_back(f2);
                reserveds.push_back(f3);
                /*printf("case3.3: reserved0: %s, reserved1: %s, reserved2: %s\n",
                 formatAddr(f1->offset, f1->size).c_str(),
                 formatAddr(f2->offset, f2->size).c_str(),
                 formatAddr(f3->offset, f3->size).c_str());*/
                return;
            }
        }
    }
}

/**
 * Function: AdbParser::endElement
 **/
void AdbParser::endElement(void *_adbParser, const XML_Char *name) {
    AdbParser *adbParser = static_cast<AdbParser*> (_adbParser);
    int lineNumber = XML_GetCurrentLineNumber(adbParser->_xmlParser);
    /*
     * Config
     * ----
     */
    if (TAG_CONFIG == name) {
        adbParser->_adbCtxt->configs.push_back(adbParser->_currentConfig);
        adbParser->_currentConfig = NULL;
    }
    /*
     * Instance Operations
     * ----
     */
    else if (TAG_INSTANCE_OPS == name) {
        adbParser->_instanceOps = false;
    }
    /*
     * Node
     * ----
     */
    else if (TAG_NODE == name) {
        // Sort the fields by offset
        if (!adbParser->_currentNode->isUnion) {
            stable_sort(adbParser->_currentNode->fields.begin(),
                    adbParser->_currentNode->fields.end(),
                    compareFieldsPtr<AdbField> );
        }

        // Check overlapping
        vector<AdbField*> reserveds;
        AdbField prevFieldDummy;
        prevFieldDummy.offset = 0;
        prevFieldDummy.size = 0;
        AdbField *prevField = &prevFieldDummy;
        if (!adbParser->_currentNode->isUnion) {
            for (size_t i = 0; i < adbParser->_currentNode->fields.size(); i++) {
                AdbField *field = adbParser->_currentNode->fields[i];
                long int delta = (long) field->offset
                        - (long) (prevField->offset + prevField->size);

                if (delta < 0) { // Overlapping
                    string exceptionTxt = "Field: " + field->name + " "
                            + formatAddr(field->offset, field->size)
                            + " overlaps with Field: " + prevField->name + " "
                            + formatAddr(prevField->offset, prevField->size);
                    if (allowMultipleExceptions) {
                        exceptionTxt = exceptionTxt + ", in file: \""
                                + adbParser->_fileName + "\" line: "
                                + boost::lexical_cast<string>(lineNumber);
                        ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                    } else {
                        throw AdbException(exceptionTxt);
                    }
                }
                if (delta > 0 && adbParser->_addReserved) { // Need reserved
                    addReserved(reserveds, prevField->offset + prevField->size,
                            delta);
                }

                prevField = field;
            }
        }

        // Add reserved filler at end of union/node
        // special case if node is empty, we need to add reserved anyway
        if (adbParser->_addReserved /*|| adbParser->_currentNode->fields.empty()*/) {
            if (adbParser->_currentNode->isUnion) {
                addReserved(reserveds, 0, adbParser->_currentNode->size);
            } else {
                long delta = (long) adbParser->_currentNode->size
                        - (long) (prevField->offset + prevField->size);
                /*if (adbParser->_currentNode->name == "miss_machine_slice_info")
                 {
                 printf("Adding filler\n");
                 printf("node offs: %s, prevField: %s\n", formatAddr(0, adbParser->_currentNode->size).c_str(),
                 formatAddr(prevField->offset, prevField->size).c_str());
                 printf("delta: %ld\n", delta);
                 }*/

                if (delta > 0) {
                    addReserved(reserveds, prevField->offset + prevField->size,
                            delta);
                }
            }

            adbParser->_currentNode->fields.insert(
                    adbParser->_currentNode->fields.end(), reserveds.begin(),
                    reserveds.end());
        }

        // Re-fix fields offset
        if (adbParser->_adbCtxt->bigEndianArr) {
            for (size_t i = 0; i < adbParser->_currentNode->fields.size(); i++) {
                u_int32_t offset = adbParser->_currentNode->fields[i]->offset;
                u_int32_t size = adbParser->_currentNode->fields[i]->eSize();

                adbParser->_currentNode->fields[i]->offset = ((offset >> 5)
                        << 5) + ((MIN(32, adbParser->_currentNode->size)
                        - ((offset + size) % 32)) % 32);
            }
        }

        // Resort the fields by offset (since we changed offset to workaround big endian issues and added reserved)
        if (!adbParser->_currentNode->isUnion) {
            stable_sort(adbParser->_currentNode->fields.begin(),
                    adbParser->_currentNode->fields.end(),
                    compareFieldsPtr<AdbField> );
        }

        // Add this node to AdbCtxt
        adbParser->_adbCtxt->nodesMap.insert(
                pair<string, AdbNode*> (adbParser->_currentNode->name,
                        adbParser->_currentNode));
        adbParser->_currentNode = 0;

        // Call progress_func callback
        if (adbParser->_progressObj && !(adbParser->_progressCnt++
                % PROGRESS_NODE_CNT)) {
            adbParser->_progressObj->progress(); // TODO - call with real parameters
        }
    }
    /*
     * Field
     * ----
     */
    else if (TAG_FIELD == name) {
        // Add this field to current node
        if (adbParser->_currentNode->name == "root") {
            adbParser->_adbCtxt->rootNode = adbParser->_currentField->subNode;
        }

        // Check conditions
        bool cond = true;
        AttrsMap::iterator it;
        it = adbParser->_currentField->attrs.find("inst_ifdef");
        if (it != adbParser->_currentField->attrs.end()) {
            bool found = false;
            for (size_t i = 0; i < adbParser->_adbCtxt->configs.size(); i++) {
                AttrsMap::iterator it_def =
                        adbParser->_adbCtxt->configs[i]->attrs.find("define");
                if (it_def != adbParser->_adbCtxt->configs[i]->attrs.end()) {
                    vector < string > defVal;
                    boost::algorithm::split(defVal, it_def->second,
                            boost::is_any_of(string("=")));

                    if (defVal[0] == it->second) {
                        found = true;
                        break;
                    }
                }
            }
            cond = found;
        }

        //
        it = adbParser->_currentField->attrs.find("inst_if");
        if (cond && it != adbParser->_currentField->attrs.end()) {
            // Prepare vars
            map < string, string > vars;
            for (size_t i = 0; i < adbParser->_adbCtxt->configs.size(); i++) {
                AttrsMap::iterator it_def =
                        adbParser->_adbCtxt->configs[i]->attrs.find("define");
                if (it_def != adbParser->_adbCtxt->configs[i]->attrs.end()) {
                    vector < string > defVal;
                    boost::algorithm::split(defVal, it_def->second,
                            boost::is_any_of(string("=")));

                    if (defVal.size() == 1) {
                        vars[defVal[0]] = "0";
                    } else {
                        vars[defVal[0]] = defVal[1];
                    }
                }
            }

            AdbExpr adbExpr;
            char *expOrg = new char[it->second.size() + 1];
            char *exp = expOrg;
            if (!exp) {
                throw AdbException("Memory allocation error");
            }
            strcpy(exp, it->second.c_str());

            u_int64_t res;
            adbExpr.setVars(&vars);
            int status = adbExpr.expr(&exp, &res);
            delete[] expOrg;
            string statusStr;

            if (status < 0) {
                string exceptionTxt = string("Error evaluating expression \"")
                        + it->second.c_str() + "\" : " + AdbExpr::statusStr(
                        status);
                if (allowMultipleExceptions) {
                    exceptionTxt = exceptionTxt + ", in file: \""
                            + adbParser->_fileName + "\" line: "
                            + boost::lexical_cast<string>(lineNumber);
                    ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                } else {
                    throw AdbException(exceptionTxt);
                }
            }
            cond = !!res;
        }

        if (cond) {
            // Name should be unique
            if (adbParser->_strict) {
                for (size_t i = 0; i < adbParser->_currentNode->fields.size(); i++) {
                    if (!adbParser->_currentNode->fields[i]->name.compare(
                            adbParser->_currentField->name)) {
                        string exceptionTxt = "The field \""
                                + adbParser->_currentField->name
                                + "\" isn't unique in node";
                        if (allowMultipleExceptions) {
                            exceptionTxt = exceptionTxt + ", in file: \""
                                    + adbParser->_fileName + "\" line: "
                                    + boost::lexical_cast<string>(lineNumber);
                            ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                        } else {
                            throw AdbException(exceptionTxt);
                        }
                    }
                }
            }
            it = adbParser->_currentField->attrs.find("condition");
            if (it != adbParser->_currentField->attrs.end()) {
                adbParser->_currentField->condition = string(it->second);
            }

            adbParser->_currentNode->fields.push_back(adbParser->_currentField);
        } else {
            adbParser->_currentNode->condFields.push_back(
                    adbParser->_currentField);
        }
        adbParser->_currentField = 0;
    }
}

/**
 * Function: AdbParser::raiseException
 **/
bool AdbParser::raiseException(bool allowMultipleExceptions, string exceptionTxt, 
                              string addedMsg, const string expType)
{
    if (allowMultipleExceptions) {
        ExceptionHolder::insertNewException(expType, exceptionTxt + addedMsg);
        return false;
    } else {
        throw AdbException(exceptionTxt);
    }
}


#if 0
void progress(int i, int t)
{
    printf(".");
    fflush(stdout);
}

int main()
{
#define ADB_FILE "path_to.adb"
    Adb adb;
    if (!adb.load(ADB_FILE, true /*, progress*/)) {
        printf("Failed : %s\n", adb.getLastError().c_str());
        return 1;
    }

    try
    {
        //adb.print(0);
        cout << "Root node: " << adb.rootNode << endl;
        AdbInstance *root = adb.createLayout(adb.rootNode, false, NULL);
        AdbInstance *child = root->getChildByPath("packetA.x");
        if (!child) {
            printf("can't find packetA.x\n");
            return 1;
        }

        printf("Child name: %s, addr: %s\n", child->name.c_str(), formatAddr(child->offset, child->size).c_str());

        string n1, n2;
        u_int64_t v1, v2;
        child->intToEnum(0, n1);
        child->intToEnum(1, n2);
        child->enumToInt("SET", v1);
        child->enumToInt("GET", v2);

        printf("enumName(0) = %s, enumName(1) = %s, value(SET) = %d, value(GET) = %d", n1.c_str(), n2.c_str(), v1, v2);
        //root->print();
    }
    catch (AdbException &exp)
    {
        printf("-E- %s\n", exp.what());
        return 1;
    }

    cout << endl;
    //adb.print(0);
    return 0;
}
#endif
