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

/*************************** AdbParser ***************************/
#ifndef ADB_XML_PARSER_H
#define ADB_XML_PARSER_H

#include <string>
#include <vector>
#include <set>
#include <map>

#include <expat.h>

#include <common/compatibility.h>

#ifdef __linux__
#define LC_ALL_HINT " using `export LC_ALL=C`"
#else
#define LC_ALL_HINT ""
#endif

#define CHECK_RUNTIME_ERROR(e)                                                         \
    ((strstr(e.what(), "locale::facet::_S_create_c_locale") != NULL) ?                 \
       string("Encoding error, please set locale encoding to C") + LC_ALL_HINT + "." : \
       string("runtime_error: ") + e.what())

using namespace std;

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

class Adb;
class AdbField;
class AdbNode;
class AdbConfig;

class AdbParser
{
public:
    // METHODS
    AdbParser(string fileName,
              Adb* adbCtxt,
              bool addReserved = false,
              bool evalExpr = false,
              bool strict = true,
              string includePath = "",
              bool enforceExtraChecks = false,
              bool checkDsAlign = false,
              bool enforceGuiChecks = false,
              bool force_pad_32 = false);
    ~AdbParser();
    bool load(bool is_main = true);
    bool loadFromString(const char* adbString);
    string getError();

    static string descXmlToNative(const string& desc);
    static string descNativeToXml(const string& desc);
    static void includeAllFilesInDir(AdbParser* adbParser, string dirPath, int lineNumber = -1);
    static bool checkSpecialChars(string tagName);
    static bool checkBigger32(string num);
    static bool checkHEXFormat(string addr);
    static bool checkAttrExist(const XML_Char** atts, const XML_Char* name);
    static void setAllowMultipleExceptionsTrue();

public:
    static bool allowMultipleExceptions;

private:
    // METHODS
    string findFile(string fileName);
    static void addIncludePaths(Adb* adbCtxt, string includePaths);
    static void includeFile(AdbParser* adbParser, string fileName, int lineNumber = -1);
    static void startElement(void* adbParser, const XML_Char* name, const XML_Char** atts);

    static void startNodesDefElement(const XML_Char** atts, AdbParser* adbParser);
    static void startEnumElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber);
    static void startConfigElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber);
    static void startInfoElement(const XML_Char** atts, AdbParser* adbParser);
    static void startIncludeElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber);
    static void startInstOpAttrReplaceElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber);
    static void startNodeElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber);
    static void startFieldElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber);

    static void endElement(void* adbParser, const XML_Char* name);
    static void addReserved(vector<AdbField*>& reserveds, u_int32_t offset, u_int32_t size);
    static int attrCount(const XML_Char** atts);
    static string attrValue(const XML_Char** atts, const XML_Char* attrName);
    static string attrName(const XML_Char** atts, int i);
    static string attrValue(const XML_Char** atts, int i);
    static bool is_inst_ifdef_exist_and_correct_project(const XML_Char** atts, AdbParser* adbParser);
    static u_int32_t addr2int(string& s);
    static u_int32_t dword(u_int32_t offset);
    static u_int32_t startBit(u_int32_t offset);
    static bool raiseException(bool allowMultipleExceptions, string exceptionTxt, string addedMsg, const string expType);

private:
    // MEMBERS
    Adb* _adbCtxt;
    XML_Parser _xmlParser;
    string _fileName;
    string _lastError;
    bool _addReserved;
    bool _isExprEval;
    bool _strict;
    bool _checkDsAlign;
    bool skipNode;
    string _includePath;
    string _currentTagValue;
    AdbNode* _currentNode;
    AdbField* _currentField;
    AdbConfig* _currentConfig;
    bool _instanceOps;
    bool _enforceExtraChecks;
    bool _enforceGuiChecks;
    bool _force_pad_32;
    string _nname_pattern;
    string _fname_pattern;
    string _enum_pattern;
    std::set<string> field_attr_names_set;
    std::set<string> field_spec_attr;
    std::vector<string> field_mand_attr;
    std::map<string, string> attr_pattern;

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
    static const string TAG_ATTR_DEFINE_PATTERN;
};

#endif // ADB_XML_PARSER_H