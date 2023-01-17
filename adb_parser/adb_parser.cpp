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
/**
 * Function: Adb::Adb
 **/

#include "adb_parser.h"
#include "adb_instance.h"
#include "adb_condition.h"
#include "adb_condVar.h"
#include "buf_ops.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <expat.h>

#if __cplusplus >= 201402L
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif

using namespace xmlCreator;

class AdbParser
{
public:
    // METHODS
    AdbParser(string fileName,
              Adb* adbCtxt,
              bool addReserved = false,
              AdbProgress* progressObj = NULL,
              bool strict = true,
              string includePath = "",
              bool enforceExtraChecks = false,
              bool checkDsAlign = false,
              bool enforceGuiChecks = false);
    ~AdbParser();
    bool load();
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
    int _progressCnt;
    AdbProgress* _progressObj;
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
const string AdbParser::TAG_ATTR_DEFINE_PATTERN = "([A-Za-z_]\\w*)=(\\w+)";

/**
 * Function: AdbParser::compareFieldsPtr
 **/

/*************************** AdbParser Implementation ***************************/
/**
 * Function: AdbParser::AdbParser
 **/
AdbParser::AdbParser(string fileName,
                     Adb* adbCtxt,
                     bool addReserved,
                     AdbProgress* progressObj,
                     bool strict,
                     string includePath,
                     bool enforceExtraChecks,
                     bool _checkDsAlign,
                     bool _enforceGuiChecks) :
    _adbCtxt(adbCtxt),
    _fileName(fileName),
    _addReserved(addReserved),
    _progressCnt(0),
    _progressObj(progressObj),
    _strict(strict),
    _checkDsAlign(_checkDsAlign),
    skipNode(false),
    _includePath(includePath),
    _currentNode(0),
    _currentField(0),
    _currentConfig(0),
    _enforceGuiChecks(_enforceGuiChecks),
    _nname_pattern(".*"),
    _fname_pattern(".*")
{
    _enforceExtraChecks = enforceExtraChecks;

    // add default patterns
    _nname_pattern = ".*";
    _fname_pattern = ".*";
    _enum_pattern = "(\\s*\\w+\\s*=\\s*(0x)?[0-9a-fA-f]+\\s*(,)?)+";

    // add special attr names
    field_spec_attr.insert("name");
    field_spec_attr.insert("offset");
    field_spec_attr.insert("size");
    field_spec_attr.insert("descr");
    field_spec_attr.insert("low_bound");
    field_spec_attr.insert("high_bound");

    if (includePath != "")
    {
        addIncludePaths(adbCtxt, includePath);
    }
    _xmlParser = XML_ParserCreate(0);
    XML_SetUserData(_xmlParser, this);
    XML_SetElementHandler(_xmlParser, startElement, endElement);
    if (adbCtxt->includePaths.size() == 0)
    {
        // first add the opened project path
        adbCtxt->includePaths.push_back(
          _fileName.find(OS_PATH_SEP) == string::npos ? "." : _fileName.substr(0, _fileName.rfind(OS_PATH_SEP)));
        vector<string> path;
        boost::algorithm::split(path, fileName, boost::is_any_of(string(OS_PATH_SEP)));
        IncludeFileInfo info = {fileName, "ROOT", 0};
        _adbCtxt->includedFiles[path[path.size() - 1]] = info;
    }
    _instanceOps = false;
}

void AdbParser::addIncludePaths(Adb* adbCtxt, string includePaths)
{
    vector<string> paths;
    boost::algorithm::split(paths, includePaths, boost::is_any_of(string(";")));
    adbCtxt->includePaths.insert(adbCtxt->includePaths.end(), paths.begin(), paths.end());

    StringVector relatives;
    string projPath = boost::filesystem::path(adbCtxt->mainFileName).parent_path().string();

    for (StringVector::iterator it = adbCtxt->includePaths.begin(); it != adbCtxt->includePaths.end(); it++)
    {
        if (projPath != "" && projPath != *it && boost::filesystem::path(*it).is_relative())
        {
            relatives.push_back(projPath + OS_PATH_SEP + *it);
        }
    }

    adbCtxt->includePaths.insert(adbCtxt->includePaths.end(), relatives.begin(), relatives.end());
}

/**
 * Function: AdbParser::~AdbParser
 **/
AdbParser::~AdbParser()
{
    XML_ParserFree(_xmlParser);
}

/**
 * Function: AdbParser::setAllowMultipleExceptionsTrue
 * This function is a static function to change the value of set all exceptions to true
 **/
void AdbParser::setAllowMultipleExceptionsTrue()
{
    AdbParser::allowMultipleExceptions = true;
}

/**
 * Function: AdbParser::load
 **/
bool AdbParser::load()
{
    FILE* file;
    char* data = NULL;
    // Important: we open the file to read it as binary not as text.
    // Difference in line endings style in Linux and Windows causes unexpected behavior on Windows
    // platform when file has Windows style line endings.
    // In case if file is opened to read it as text, "fread"-call in function below skips line
    // ending symbols effectively reducing number of bytes read from file by amount of lines in file.
    // Since we expect it to read the entire file at once it will fail to do that (number of bytes
    // read is less than the size of file in bytes).
    file = fopen(_fileName.c_str(), "rb");
    _adbCtxt->_logFile->appendLogFile("Opening " + _fileName + "\n");

    if (!file)
    {
        _lastError = "Can't open file (" + _fileName + ") for reading: " + strerror(errno);
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    if (fseek(file, 0L, SEEK_END) < 0)
    { // go to the end of the file
        _lastError = "fseek() failed for file (" + _fileName + "): " + strerror(errno);
        fclose(file);
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    long fSize = ftell(file);
    if (fSize < 0)
    {
        _lastError = "ftell() failed for file (" + _fileName + "): " + strerror(errno);
        fclose(file);
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    data = (char*)malloc(fSize + 1);
    if (!data)
    {
        fclose(file);
        throw AdbException("Out of memory.");
    }

    if (fseek(file, 0L, SEEK_SET) < 0)
    { // go back to the start of the file
        _lastError = "Failed to read file (" + _fileName + "): " + strerror(errno);
        fclose(file);
        free(data);
        data = NULL;
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    size_t result = fread(data, fSize, 1, file);
    if (result != 1)
    {
        _lastError = "Failed to read file (" + _fileName + "): " + strerror(errno);
        fclose(file);
        free(data);
        data = NULL;
        if (allowMultipleExceptions)
        {
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }

    data[fSize] = 0;
    fclose(file);

    bool xmlStatus = true;
    try
    {
        if (!XML_Parse(_xmlParser, data, strlen(data), 0))
        {
            enum XML_Error errNo = XML_GetErrorCode(_xmlParser);
            throw AdbException(string("XML parsing issues: ") + XML_ErrorString(errNo));
        }
    }
    catch (AdbException& exp)
    {
        if (exp.what_s().find("in file:") == string::npos)
        {
            int line = XML_GetCurrentLineNumber(_xmlParser);
            int column = XML_GetCurrentColumnNumber(_xmlParser);
            _lastError = exp.what_s() + " in file: " + _fileName + " at line: " + boost::lexical_cast<string>(line) +
                         " column: " + boost::lexical_cast<string>(column);
        }
        else
        {
            _lastError = exp.what_s();
        }
        if (allowMultipleExceptions)
        {
            xmlStatus = false;
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        else
        {
            free(data);
            return false;
        }
    }
    catch (std::runtime_error& e)
    {
        _lastError = CHECK_RUNTIME_ERROR(e);
        if (allowMultipleExceptions)
        {
            xmlStatus = false;
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        else
        {
            free(data);
            return false;
        }
    }
    catch (...)
    {
        int line = XML_GetCurrentLineNumber(_xmlParser);
        int column = XML_GetCurrentColumnNumber(_xmlParser);
        _lastError = string("An exception raised during the loading of the file: ") + _fileName +
                     " at line: " + boost::lexical_cast<string>(line) +
                     " column: " + boost::lexical_cast<string>(column);
        if (allowMultipleExceptions)
        {
            xmlStatus = false;
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        else
        {
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
bool AdbParser::loadFromString(const char* adbString)
{
    _fileName = "\"STRING\"";
    try
    {
        if (!XML_Parse(_xmlParser, adbString, strlen(adbString), 0))
        {
            enum XML_Error errNo = XML_GetErrorCode(_xmlParser);
            throw AdbException(string("XML parsing issues: ") + XML_ErrorString(errNo));
        }
    }
    catch (AdbException& exp)
    {
        if (exp.what_s().find("in file:") == string::npos)
        {
            int line = XML_GetCurrentLineNumber(_xmlParser);
            int column = XML_GetCurrentColumnNumber(_xmlParser);
            _lastError = exp.what_s() + " in file: " + _fileName + " at line: " + boost::lexical_cast<string>(line) +
                         " column: " + boost::lexical_cast<string>(column);
        }
        else
        {
            _lastError = exp.what_s();
        }

        _lastError += string("\nNOTE: this project is configured to work with: \"") +
                      (_adbCtxt->bigEndianArr ? "Big" : "Little") + " Endian Arrays\"";
        return false;
    }
    catch (std::runtime_error& e)
    {
        _lastError = CHECK_RUNTIME_ERROR(e);
        return false;
    }
    catch (...)
    {
        int line = XML_GetCurrentLineNumber(_xmlParser);
        int column = XML_GetCurrentColumnNumber(_xmlParser);
        _lastError = string("An exception raised during the loading of the file: ") + _fileName +
                     " at line: " + boost::lexical_cast<string>(line) +
                     " column: " + boost::lexical_cast<string>(column);
        return false;
    }

    return true;
}

/**
 * Function: AdbParser::getError
 **/
string AdbParser::getError()
{
    return _lastError;
}

/**
 * Function: AdbParser::attrsCount
 **/
int AdbParser::attrCount(const XML_Char** atts)
{
    int i = 0;
    while (atts[i])
    {
        i++;
    }
    return i / 2;
}

/**
 * Function: AdbParser::attrValue
 **/
string AdbParser::attrValue(const XML_Char** atts, const XML_Char* attrName)
{
    int i = 0;
    while (atts[i])
    {
        if (!strcmp(atts[i], attrName))
        {
            return string(atts[i + 1]);
        }
        i += 2;
    }

    return string();
}

/**
 * Function: AdbParser::checkAttrExist
 */
bool AdbParser::checkAttrExist(const XML_Char** atts, const XML_Char* attrName)
{
    int i = 0;
    while (atts[i])
    {
        if (!strcmp(atts[i], attrName))
        {
            return true;
        }
        i += 2;
    }
    return false;
}

/**
 * Function: AdbParser::attrName
 **/
string AdbParser::attrName(const XML_Char** atts, int i)
{
    return string(atts[i * 2]);
}

/**
 * Function: AdbParser::attrName
 **/
string AdbParser::attrValue(const XML_Char** atts, int i)
{
    return string(atts[i * 2 + 1]);
}

/**
 * Function: AdbParser::findFile
 **/
string AdbParser::findFile(string fileName)
{
    FILE* f;

    for (size_t i = 0; i < _adbCtxt->includePaths.size(); i++)
    {
        string filePath = _adbCtxt->includePaths[i] + OS_PATH_SEP + fileName;
        f = fopen(filePath.c_str(), "r");
        if (f)
        {
            fclose(f);
            return filePath;
        }
        else if (fileName.find(_adbCtxt->includePaths[i]) != string::npos)
        { // includePath is part of fileName
            f = fopen(fileName.c_str(), "r");
            if (f)
            {
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
u_int32_t AdbParser::addr2int(string& s)
{
    try
    {
        u_int32_t res;
        boost::algorithm::to_lower(s);
        char* end;
        vector<string> words;
        boost::algorithm::split(words, s, boost::is_any_of(string(".")));

        // fix for cases like: 0x.16
        if (words.size() && !words[0].compare("0x"))
        {
            words[0] = "0";
        }

        switch (words.size())
        {
            case 1:
                res = strtoul(words[0].c_str(), &end, 0);
                if (*end != '\0')
                {
                    throw AdbException();
                }

                res *= 8;
                break;

            case 2:
                if (words[0].empty())
                {
                    // .DDD form
                    res = strtoul(words[1].c_str(), &end, 0);
                    if (*end != '\0')
                    {
                        throw AdbException();
                    }
                }
                else
                {
                    // 0xHHHHH.DDD or DDDDD.DDD form
                    res = strtoul(words[0].c_str(), &end, 0);
                    if (*end != '\0')
                    {
                        throw AdbException();
                    }
                    res *= 8;
                    res += strtoul(words[1].c_str(), &end, 0);
                    if (*end != '\0')
                    {
                        throw AdbException();
                    }
                }
                break;

            default:
                throw AdbException("Invalid size: " + s);
        }

        return res;
    }
    catch (AdbException& exp)
    {
        throw AdbException("Failed to retrieve integer from string: " + exp.what_s());
    }
}

/**
 * Function: AdbParser::dword
 **/
u_int32_t AdbParser::dword(u_int32_t offset)
{
    return (offset >> 5) << 2;
}

/**
 * Function: AdbParser::startBit
 **/
u_int32_t AdbParser::startBit(u_int32_t offset)
{
    return offset % 32;
}

/**
 * Function: AdbParser::descXmlToNative
 **/
string AdbParser::descXmlToNative(const string& desc)
{
    return boost::replace_all_copy(desc, "\\;", "\n");
}

bool AdbParser::is_inst_ifdef_exist_and_correct_project(const XML_Char** atts, AdbParser* adbParser)
{
    bool cond = true;
    string definedProject = attrValue(atts, "inst_ifdef");
    if (!definedProject.empty())
    {
        bool found = false;
        for (size_t i = 0; i < adbParser->_adbCtxt->configs.size(); i++)
        {
            AttrsMap::iterator it_def = adbParser->_adbCtxt->configs[i]->attrs.find("define");
            if (it_def != adbParser->_adbCtxt->configs[i]->attrs.end())
            {
                vector<string> defVal;
                boost::algorithm::split(defVal, it_def->second, boost::is_any_of(string("=")));

                if (defVal[0] == definedProject)
                {
                    found = true;
                    break;
                }
            }
        }
        cond = found;
    }
    return cond;
}

/**
 * Function: AdbParser::descNativeToXml
 **/

/**
 * Function: AdbParser::includeFile
 **/
void AdbParser::includeFile(AdbParser* adbParser, string fileName, int lineNumber)
{
    // add this file to the included files map
    string filePath;
    FILE* probeFile = NULL;

    if (!boost::filesystem::path(fileName).is_relative())
    {
        probeFile = fopen(fileName.c_str(), "r");
    }

    if (probeFile)
    {
        fclose(probeFile);
        filePath = fileName;
    }
    else
    {
        filePath = adbParser->findFile(fileName);
    }
    if (filePath.empty())
    {
        throw AdbException(string() + "Can't find the file: " + fileName);
    }

    // Update filename to be only base name with extension to prevent duplications
    boost::filesystem::path boostPath(filePath);
    fileName = boostPath.filename().string();

    if (!adbParser->_adbCtxt->includedFiles.count(fileName))
    {
        IncludeFileInfo info = {filePath, adbParser->_fileName, lineNumber};
        adbParser->_adbCtxt->includedFiles[fileName] = info;

        // parse the included file
        AdbParser p(filePath, adbParser->_adbCtxt, adbParser->_addReserved, adbParser->_progressObj, adbParser->_strict,
                    "", adbParser->_enforceExtraChecks);
        if (!p.load())
        {
            throw AdbException(p.getError());
        }
    }
}

/**
 * Function: AdbParser::includeAllFilesInDir
 **/
void AdbParser::includeAllFilesInDir(AdbParser* adbParser, string dirPath, int lineNumber)
{
    vector<string> paths;
    boost::filesystem::path mainFile(adbParser->_fileName);
    boost::algorithm::split(paths, dirPath, boost::is_any_of(string(";")));
    for (StringVector::iterator pathIt = paths.begin(); pathIt != paths.end(); pathIt++)
    {
        // first look in the main file's path
        boost::filesystem::path fsPath(mainFile.parent_path().string() + "/" + *pathIt);
        if (!boost::filesystem::exists(fsPath))
        {
            fsPath = boost::filesystem::path(*pathIt);
        }

        if (boost::filesystem::exists(fsPath) && boost::filesystem::is_directory(fsPath))
        {
            addIncludePaths(adbParser->_adbCtxt, *pathIt);
            boost::filesystem::directory_iterator filesIter(fsPath), dirEnd;
            for (; filesIter != dirEnd; ++filesIter)
            {
                if (boost::filesystem::is_regular_file(filesIter->status()) && filesIter->path().extension() == ".adb")
                {
                    try
                    {
                        includeFile(adbParser, filesIter->path().string(), lineNumber);
                    }
                    catch (AdbException& e)
                    {
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
bool AdbParser::checkSpecialChars(string tagName)
{
    smatch match;
    regex allowedCharsExpr("[^\\w\\[\\]]"); // only alphanumeric and square brackets are allowed
    if (regex_search(tagName, match, allowedCharsExpr))
    {
        return false;
    }
    regex checkArrayExpr("[\\[\\]]"); // this check if containing the array brackets
    if (regex_search(tagName, match, checkArrayExpr))
    {
        regex correctNameForArrayExpr("[_A-Za-z][\\w]*\\[[\\d]+\\]$");
        if (!regex_search(tagName, match, correctNameForArrayExpr))
        { // check the name if correct the square brackets (array)
            return false;
        }
    }
    else
    {
        regex correctNameNoneArrayExpr("[_A-Za-z][\\w]*$");
        if (!regex_search(tagName, match, correctNameNoneArrayExpr))
        { // check the name if correct without the square brackets (not array)
            return false;
        }
    }
    return true;
}

bool AdbParser::checkHEXFormat(string addr)
{
    smatch match;
    regex correctHEXExpr("^(0x[0-9A-fa-f])?[0-9A-Fa-f]*(\\.[0-9]*)?$");
    if (!regex_search(addr, match, correctHEXExpr))
    {
        return false;
    }
    return true;
}

bool AdbParser::checkBigger32(string num)
{
    std::istringstream iss(num);
    std::string token;
    std::getline(iss, token, '.');
    if (std::getline(iss, token, '.'))
    { // the second part of the size after the . max to be 32 0x0.0
        if (addr2int(token) / 8 >= 32)
        {
            return true;
        }
    }
    return false;
}

void AdbParser::startNodesDefElement(const XML_Char** atts, AdbParser* adbParser)
{
    if (adbParser->_adbCtxt->version == "")
    {
        if ((attrCount(atts) == 1) && (attrName(atts, 0) == "version"))
        {
            string adbVersion = attrValue(atts, 0);
            if (adbVersion != "1" && adbVersion != "1.0" && adbVersion != "2")
            {
                throw AdbException("Requested Adb Version (%s) is not supported. Supporting only version 1 or 2",
                                   adbVersion.c_str());
            }
            if (adbVersion == "1.0")
            {
                adbParser->_adbCtxt->version = "1";
            }
            else
            {
                adbParser->_adbCtxt->version = adbVersion;
            }
        }
        else if (attrCount(atts) == 0)
        {
            adbParser->_adbCtxt->version = "1";
        }
        else
        {
            throw AdbException("\"NodesDefinition\" tag can only have \"version\" attribute and only once");
        }
    }
}

void AdbParser::startEnumElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber)
{
    bool expFound = false;
    if (!adbParser->_currentConfig || !adbParser->_currentConfig->attrs.count("type") ||
        TAG_ATTR_ENUM.compare(adbParser->_currentConfig->attrs["type"]))
    {
        expFound =
          raiseException(allowMultipleExceptions,
                         "\"enum\" tag must be inside relevant \"config\" tag",
                         ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                         ExceptionHolder::ERROR_EXCEPTION);
    }

    string tagName = attrValue(atts, "name");
    string value = attrValue(atts, "value");
    if (adbParser->_enforceExtraChecks)
    {
        if (!AdbParser::checkSpecialChars(tagName))
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Invalid character in enum name, in enum: \"" + tagName + "\"",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::WARN_EXCEPTION);
        }
    }
    if (tagName.empty() || value.empty())
    {
        expFound =
          raiseException(allowMultipleExceptions,
                         "Both \"name\" and \"value\" attributes must be specified",
                         ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                         ExceptionHolder::ERROR_EXCEPTION);
    }
    if (!expFound)
    {
        adbParser->_currentConfig->enums.insert(pair<string, string>(tagName, value));
    }
}

void AdbParser::startConfigElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber)
{
    bool expFound = false;
    if (adbParser->_currentConfig)
    {
        expFound =
          raiseException(allowMultipleExceptions,
                         "config tag can't appear within other config",
                         ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                         ExceptionHolder::FATAL_EXCEPTION);
    }

    adbParser->_currentConfig = new AdbConfig;
    for (int i = 0; i < attrCount(atts); i++)
    {
        // First add this config to context
        string aName = attrName(atts, i);
        string aValue = attrValue(atts, i);
        adbParser->_currentConfig->attrs.insert(pair<string, string>(aName, aValue));

        // checks that was imported from the gui-parser
        if (adbParser->_enforceGuiChecks)
        {
            // check if the attribute is mandatory
            if (!aName.compare("field_mand"))
            {
                aValue = regex_replace(aValue, regex("\\s+"), "");
                boost::split(adbParser->field_mand_attr, aValue, boost::is_any_of(","));
            }

            // check the define statement is according to format
            else if (!aName.compare("define"))
            {
                smatch result;
                regex pattern(TAG_ATTR_DEFINE_PATTERN);
                if (!regex_match(aValue, result, pattern))
                {
                    expFound = raiseException(
                      allowMultipleExceptions,
                      string("Bad define format: \"") + aName + "\" attribute value: \"" + aValue + "\"",
                      ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }
                else
                {
                    // check for define duplication
                    string define_key = result[1], define_value = result[2];

                    if (adbParser->_adbCtxt->defines_map.find(define_key) != adbParser->_adbCtxt->defines_map.end())
                    {
                        expFound = raiseException(allowMultipleExceptions,
                                                  string("Multiple definition of preprocessor variable: \"") +
                                                    define_key + "\" attribute name: \"" + aName + "\"",
                                                  ", in file: \"" + adbParser->_fileName +
                                                    "\" line: " + boost::lexical_cast<string>(lineNumber),
                                                  ExceptionHolder::ERROR_EXCEPTION);
                    }
                    else
                    {
                        adbParser->_adbCtxt->defines_map.insert(pair<string, string>(define_key, define_value));
                    }
                }
            }

            else if (!expFound && !aName.compare("field_attr"))
            {
                // check that the field_attr is unique
                if (adbParser->field_attr_names_set.find(aValue) != adbParser->field_attr_names_set.end())
                {
                    expFound = raiseException(
                      allowMultipleExceptions,
                      string("Redefinition of field_attr: \"") + aName + "\" attribute name: \"" + aValue + "\"",
                      ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }
                else
                {
                    adbParser->field_attr_names_set.insert(aValue);
                }

                string attr_type = attrValue(atts, "type");

                // check that attr 'type' was provided and not empty
                if (attr_type.empty())
                {
                    expFound = raiseException(
                      allowMultipleExceptions,
                      string("field_attr type must be specified: \"") + aName + "\" attribute value: \"" + aValue + "\"",
                      ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }
                else
                {
                    // check that type 'multival' has a 'fw_label' value
                    if (!attr_type.compare("multival") && aValue.compare("fw_label"))
                    {
                        expFound =
                          raiseException(allowMultipleExceptions,
                                         string("Type \"multival\" is supported only for \"fw_label\" not for: \"") +
                                           aName + "\" attribute value: \"" + aValue + "\"",
                                         ", in file: \"" + adbParser->_fileName +
                                           "\" line: " + boost::lexical_cast<string>(lineNumber),
                                         ExceptionHolder::ERROR_EXCEPTION);
                    }
                }

                string attr_used_for = attrValue(atts, "used_for");

                // check that attr 'used_for' was not provided empty
                if (checkAttrExist(atts, "used_for") && attr_used_for.empty())
                {
                    expFound = raiseException(
                      allowMultipleExceptions,
                      string("used_for is invalid: \"") + aName + "\" attribute value: \"" + aValue + "\"",
                      ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }

                // check if 'pattern' was provided
                if (checkAttrExist(atts, "pattern"))
                {
                    // check if the given pattern is a valid reg expression.
                    try
                    {
                        string pattern_value = attrValue(atts, "pattern");
                        regex r(pattern_value);
                        adbParser->attr_pattern.insert(pair<string, string>(aValue, pattern_value));
                    }
                    catch (...)
                    {
                        expFound = raiseException(allowMultipleExceptions,
                                                  string("Bad attribute pattern: \"") + aValue + "\" name Pattern: \"" +
                                                    attrValue(atts, "pattern") + "\"",
                                                  ", in file: \"" + adbParser->_fileName +
                                                    "\" line: " + boost::lexical_cast<string>(lineNumber),
                                                  ExceptionHolder::ERROR_EXCEPTION);
                    }
                }
            }

            // check if nname_pattern was provided
            else if (!expFound && checkAttrExist(atts, "nname_pattern"))
            {
                // check if the given pattern is a valid reg expression.
                try
                {
                    string nname_pattern = attrValue(atts, "nname_pattern");
                    regex r(nname_pattern);
                    adbParser->_nname_pattern = nname_pattern;
                }
                catch (...)
                {
                    expFound = raiseException(
                      allowMultipleExceptions,
                      string("Bad node name pattern: \"") + aValue + "\" pattern: \"" +
                        attrValue(atts, "nname_pattern") + "\"",
                      ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }
            }

            // check if fname_pattern was provided and the name of the field is compatible with that pattern
            else if (!expFound && checkAttrExist(atts, "fname_pattern"))
            {
                // check if the given pattern is a valid reg expression.
                try
                {
                    string fname_pattern = attrValue(atts, "fname_pattern");
                    regex r(fname_pattern);
                    adbParser->_fname_pattern = fname_pattern;
                }
                catch (...)
                {
                    expFound = raiseException(
                      allowMultipleExceptions,
                      string("Bad field name pattern: \"") + aValue + "\" pattern: \"" +
                        attrValue(atts, "fname_pattern") + "\"",
                      ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }
            }
        }

        // Parse attrs that affect the parser itself
        if (!TAG_ATTR_BIG_ENDIAN.compare(aName))
        {
            try
            {
                int val = boost::lexical_cast<int>(aValue);
                adbParser->_adbCtxt->bigEndianArr = val != 0;
            }
            catch (std::exception&)
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  string("Filed to parse the \"") + aName + "\" attribute value: \"" + aValue + "\"",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::ERROR_EXCEPTION);
            }
        }

        if (!TAG_ATTR_SINGLE_ENTRY_ARR.compare(aName))
        {
            try
            {
                int val = boost::lexical_cast<int>(aValue);
                adbParser->_adbCtxt->singleEntryArrSupp = val != 0;
            }
            catch (std::exception&)
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  string("Filed to parse the \"") + aName + "\" attribute value: \"" + aValue + "\"",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::ERROR_EXCEPTION);
            }
        }

        if (!expFound && !TAG_ATTR_INCLUDE_PATH.compare(aName))
        {
            vector<string> paths;
            boost::algorithm::split(paths, aValue, boost::is_any_of(string(";")));
            adbParser->_adbCtxt->includePaths.insert(adbParser->_adbCtxt->includePaths.end(), paths.begin(),
                                                     paths.end());

            StringVector relatives;
            string projPath = boost::filesystem::path(adbParser->_adbCtxt->mainFileName).parent_path().string();

            for (StringVector::iterator it = adbParser->_adbCtxt->includePaths.begin();
                 it != adbParser->_adbCtxt->includePaths.end();
                 it++)
            {
                if (boost::filesystem::path(*it).is_relative())
                {
                    relatives.push_back(projPath + OS_PATH_SEP + *it);
                }
            }

            adbParser->_adbCtxt->includePaths.insert(adbParser->_adbCtxt->includePaths.end(), relatives.begin(),
                                                     relatives.end());
        }
    }
}

void AdbParser::startInfoElement(const XML_Char** atts, AdbParser* adbParser)
{
    string docName = attrValue(atts, "source_doc_name");
    string docVer = attrValue(atts, "source_doc_version");
    adbParser->_adbCtxt->srcDocName = docName;
    adbParser->_adbCtxt->srcDocVer = docVer;
}

void AdbParser::startIncludeElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber)
{
    bool cond = is_inst_ifdef_exist_and_correct_project(atts, adbParser);

    if (cond)
    {
        string includeAttr = attrName(atts, 0);
        boost::algorithm::trim(includeAttr);

        bool expFound = false;
        if (includeAttr == "file")
        {
            string fname = attrValue(atts, "file");
            boost::algorithm::trim(fname);
            if (fname.empty())
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  string() + "File attribute isn't given within " + TAG_INCLUDE + " tag",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::FATAL_EXCEPTION);
            }
            if (!expFound)
                includeFile(adbParser, fname, lineNumber);
        }
        else if (includeAttr == "dir")
        {
            string includeAllDirPath = attrValue(atts, "dir");
            boost::algorithm::trim(includeAllDirPath);
            if (includeAllDirPath.empty())
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  string() + "Directory to include isn't given within " + TAG_INCLUDE + " tag",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::FATAL_EXCEPTION);
            }

            if (!expFound)
                includeAllFilesInDir(adbParser, includeAllDirPath, lineNumber);
        }
        else
        {
            expFound = raiseException(
              allowMultipleExceptions,
              string() + "Include is called without file or dir attribute.",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::ERROR_EXCEPTION);
        }
    }
}

void AdbParser::startInstOpAttrReplaceElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber)
{
    bool expFound = false;
    if (!adbParser->_instanceOps)
    {
        expFound =
          raiseException(allowMultipleExceptions,
                         "Operation attr_replace must be defined within <instance_ops> element only.",
                         ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                         ExceptionHolder::FATAL_EXCEPTION);
    }

    string path = attrValue(atts, "path");
    if (path.empty())
    {
        expFound =
          raiseException(allowMultipleExceptions,
                         "path attribute is missing in attr_replace operation",
                         ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                         ExceptionHolder::ERROR_EXCEPTION);
    }

    if (!expFound)
    {
        adbParser->_adbCtxt->instAttrs[path] = AttrsMap();
        for (int i = 0; i < attrCount(atts); i++)
        {
            string attrN = attrName(atts, i);
            if (attrN == "path")
            {
                continue;
            }

            string attrV = attrValue(atts, i);
            adbParser->_adbCtxt->instAttrs[path][attrN] = attrV;
        }
    }
}

void AdbParser::startNodeElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber)
{
    if (adbParser->_currentNode || adbParser->skipNode)
    {
        raiseException(allowMultipleExceptions,
                       "Nested nodes are not allowed",
                       ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                       ExceptionHolder::FATAL_EXCEPTION);
    }
    bool cond = is_inst_ifdef_exist_and_correct_project(atts, adbParser);

    if (cond)
    {
        string nodeName = attrValue(atts, "name");
        boost::algorithm::trim(nodeName);
        string size = attrValue(atts, "size");

        if (adbParser->_enforceGuiChecks)
        {
            // check the node name is compatible with the nname_pattern
            if (!regex_match(nodeName, regex(adbParser->_nname_pattern)))
            {
                raiseException(allowMultipleExceptions,
                               "Illegal node name: \"" + nodeName + "\" doesn't match the given node name pattern: \"",
                               adbParser->_nname_pattern + "\", in file: \"" + adbParser->_fileName +
                                 "\" line: " + boost::lexical_cast<string>(lineNumber),
                               ExceptionHolder::WARN_EXCEPTION);
            }
        }

        if (adbParser->_enforceExtraChecks)
        {
            if (!AdbParser::checkSpecialChars(nodeName))
            {
                raiseException(
                  allowMultipleExceptions,
                  "Invalid character in node name, in Node: \"" + nodeName + "\"",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (AdbParser::checkBigger32(size))
            { // the second part of the size after the . max to be 32 0x0.0
                raiseException(
                  allowMultipleExceptions,
                  "Invalid size format, valid format 0x0.0 not allowed to be more than 0x0.31",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (!AdbParser::checkHEXFormat(size))
            {
                raiseException(
                  allowMultipleExceptions,
                  "Invalid size format",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (addr2int(size) == 0)
            {
                raiseException(
                  allowMultipleExceptions,
                  "Node Size is not allowed to be 0, in Node: \"" + nodeName + "\"",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::ERROR_EXCEPTION);
            }
        }
        string desc = descXmlToNative(attrValue(atts, "descr"));

        // Check for mandatory attrs
        if (nodeName.empty())
        {
            raiseException(
              allowMultipleExceptions,
              "Missing node name",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }
        if (size.empty())
        {
            raiseException(
              allowMultipleExceptions,
              "Missing node size",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }
        // Check for duplications
        if (adbParser->_adbCtxt->nodesMap.count(nodeName))
        {
            raiseException(
              allowMultipleExceptions,
              "node \"" + nodeName + "\" is already defined in file: \"" +
                adbParser->_adbCtxt->nodesMap[nodeName]->fileName +
                "\" line: " + boost::lexical_cast<string>(adbParser->_adbCtxt->nodesMap[nodeName]->lineNumber),
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }

        adbParser->_currentNode = new AdbNode;
        adbParser->_currentNode->name = nodeName;
        adbParser->_currentNode->size = addr2int(size);
        adbParser->_currentNode->desc = desc;
        string unionAttrVal = attrValue(atts, "attr_is_union");
        adbParser->_currentNode->isUnion = !unionAttrVal.empty() && boost::lexical_cast<int>(unionAttrVal) != 0;
        adbParser->_currentNode->fileName = adbParser->_fileName;
        adbParser->_currentNode->lineNumber = lineNumber;

        if (adbParser->_strict && adbParser->_currentNode->isUnion && adbParser->_currentNode->size % 32)
        {
            // throw AdbException("union must be dword aligned");
        }

        // Add all node attributes
        for (int i = 0; i < attrCount(atts); i++)
        {
            if (attrValue(atts, i) == "")
            {
                continue;
            }
            adbParser->_currentNode->attrs[attrName(atts, i)] = attrValue(atts, i);
        }
    }
    else
    {
        adbParser->skipNode = true;
    }
}

void AdbParser::startFieldElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber)
{
    bool expFound = false;
    if (!adbParser->_currentNode && !adbParser->skipNode)
    {
        expFound =
          raiseException(allowMultipleExceptions,
                         "Field definition outside of node",
                         ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                         ExceptionHolder::FATAL_EXCEPTION);
    }

    if (!adbParser->skipNode)
    {
        if (adbParser->_currentField)
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Nested fields are not allowed",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }

        string fieldName = attrValue(atts, "name");
        boost::algorithm::trim(fieldName);
        string offset = attrValue(atts, "offset");
        string size = attrValue(atts, "size");

        if (adbParser->_enforceExtraChecks)
        {
            if (addr2int(size) % 32 == 0 && !AdbParser::checkHEXFormat(size))
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Invalid size format",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (!AdbParser::checkHEXFormat(offset))
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Invalid offset format",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (!AdbParser::checkSpecialChars(fieldName))
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Invalid character in field name, in Field: \"" + fieldName + "\"",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (!expFound && adbParser->_currentNode->isUnion && addr2int(offset) != 0)
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Offset must be 0x0.0 in Union fields",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (AdbParser::checkBigger32(size))
            { // the second part of the size after the . max to be 32 0x0.0
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Invalid size format, valid format 0x0.0 not allowed to be more than 0x0.31",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (AdbParser::checkBigger32(offset))
            { // the second part of the size after the . max to be 32 0x0.0
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Invalid offset format, valid format 0x0.0 not allowed to be more than 0x0.31",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
            if (addr2int(size) == 0)
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Field Size is not allowed to be 0, in Field: \"" + fieldName + "\"",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
        }

        string desc = descXmlToNative(attrValue(atts, "descr"));
        string lowBound = attrValue(atts, "low_bound");
        string highBound = attrValue(atts, "high_bound");

        if (lowBound != "" && highBound != "")
        {
            int low = atoi(lowBound.c_str());
            int high = 0;
            if (highBound != "VARIABLE")
            {
                high = atoi(highBound.c_str());
            }
            int isize = addr2int(size);
            int entrySize = isize / (high - low + 1);
            if (entrySize % 8 != 0 && entrySize > 8)
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Invalid size of array entries",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::ERROR_EXCEPTION);
            }
            if (entrySize < 8 && entrySize != 4 && entrySize != 2 && entrySize != 1 &&
                ((isize > 32 && highBound != "VARIABLE") || highBound == "VARIABLE"))
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Array with entry size 3, 5, 6 or 7 bits and array size is larger than 32bit",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::ERROR_EXCEPTION);
            }
        }
        else if (adbParser->_enforceGuiChecks && !(lowBound == "" && highBound == ""))
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Field: \"" + adbParser->_currentField->name + "\": both low_bound or high_bound must be specified",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::WARN_EXCEPTION);
        }

        string subNode = attrValue(atts, "subnode");

        // Check for mandatory attrs
        if (fieldName.empty())
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Missing field name",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }

        if (size.empty())
        {
            expFound = raiseException(
              allowMultipleExceptions,
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
        if (adbParser->_adbCtxt->singleEntryArrSupp)
        {
            int low = -1;
            int high = -1;
            if (!lowBound.empty())
            {
                low = atoi(lowBound.c_str());
            }
            if (!highBound.empty())
            {
                high = atoi(highBound.c_str());
            }
            adbParser->_currentField->definedAsArr = (low == high) && (low >= 0);
        }
        else
        {
            adbParser->_currentField->definedAsArr = false;
        }

        adbParser->_currentField->lowBound = lowBound.empty() ? 0 : boost::lexical_cast<u_int32_t>(lowBound);
        if (highBound == "VARIABLE")
        {
            adbParser->_currentField->highBound = 0;
            adbParser->_currentField->unlimitedArr = true;
        }
        else
        {
            adbParser->_currentField->highBound = highBound.empty() ? 0 : boost::lexical_cast<u_int32_t>(highBound);
        }
        adbParser->_currentField->subNode = subNode;

        // Check array element size
        if (adbParser->_currentField->isArray() && !adbParser->_currentField->isUnlimitedArr() &&
            adbParser->_currentField->size % (adbParser->_currentField->arrayLen()))
        {
            char exceptionTxt[1000];
            sprintf(exceptionTxt, "In field \"%s\" invalid array element size\"%0.2f\" in file: \"%s\" line: %d",
                    fieldName.c_str(),
                    ((double)adbParser->_currentField->size / (adbParser->_currentField->arrayLen())),
                    adbParser->_fileName.c_str(), lineNumber);

            expFound = raiseException(allowMultipleExceptions, exceptionTxt, "", ExceptionHolder::FATAL_EXCEPTION);
        }
        if (offset.empty())
        {
            if (adbParser->_currentNode->fields.empty())
            {
                adbParser->_currentField->offset = 0;
            }
            else
            {
                AdbField* lastField = adbParser->_currentNode->fields.back();
                adbParser->_currentField->offset = lastField->offset + lastField->size;
            }
        }
        else
        {
            adbParser->_currentField->offset = addr2int(offset);
        }

        // Very tricky but works well for big endian arrays support - on endElement we will fix the address again
        if (!expFound && adbParser->_adbCtxt->bigEndianArr)
        {
            u_int32_t offset = adbParser->_currentField->offset;
            u_int32_t size = adbParser->_currentField->eSize();

            adbParser->_currentField->offset =
              ((offset >> 5) << 5) + ((MIN(32, adbParser->_currentNode->size) - ((offset + size) % 32)) % 32);
        }

        // For DS alignment check
        u_int32_t esize = adbParser->_currentField->eSize();
        if ((adbParser->_currentField->isLeaf() || adbParser->_currentField->subNode == "uint64") &&
            (esize == 16 || esize == 32 || esize == 64) && esize > adbParser->_currentNode->_maxLeafSize)
        {
            adbParser->_currentNode->_maxLeafSize = esize;
        }

        if (!expFound && adbParser->_strict && adbParser->_currentNode->isUnion && adbParser->_currentField->isLeaf())
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Fields are not allowed in unions (only subnodes)",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_strict && adbParser->_currentNode->isUnion && adbParser->_currentField->size % 32)
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Union is allowed to contains only dword aligned subnodes",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_currentNode->isUnion &&
            adbParser->_currentField->size > adbParser->_currentNode->size)
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Field size is greater than the parent node size",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_strict && !adbParser->_currentField->isArray() &&
            adbParser->_currentField->isLeaf() && adbParser->_currentField->size > 32)
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Leaf fields can't be > 32 bits",
              ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
              ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_checkDsAlign)
        {
            u_int32_t esize = adbParser->_currentField->eSize();
            if ((adbParser->_currentField->isLeaf() || adbParser->_currentField->subNode == "uint64") &&
                (esize == 16 || esize == 32 || esize == 64) && adbParser->_currentField->offset % esize != 0)
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Field: " + adbParser->_currentField->name + " in Node: " + adbParser->_currentNode->name +
                    " offset(" + boost::lexical_cast<string>(adbParser->_currentField->offset) +
                    ") is not aligned to size(" + boost::lexical_cast<string>(esize) + ")",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::ERROR_EXCEPTION);
            }
        }

        if (adbParser->_enforceGuiChecks)
        {
            // check if all mandatory attributes were supplied
            for (unsigned int i = 0; i < adbParser->field_mand_attr.size(); i++)
            {
                if (!checkAttrExist(atts, adbParser->field_mand_attr[i].c_str()))
                {
                    expFound = raiseException(
                      allowMultipleExceptions,
                      "Atrribute: \"" + adbParser->field_mand_attr[i] + "\" for field must be specified.",
                      " in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }
            }

            // check if the field name is compatible with the fname pattern
            if (!regex_match(adbParser->_currentField->name, regex(adbParser->_fname_pattern)))
            {
                expFound = raiseException(
                  allowMultipleExceptions,
                  "Illegal field name: \"" + adbParser->_currentField->name +
                    "\" doesn't match the given field name pattern",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::WARN_EXCEPTION);
            }
        }

        // Add all field attributes
        if (!expFound)
        {
            for (int i = 0; i < attrCount(atts); i++)
            {
                if (adbParser->_enforceGuiChecks)
                {
                    string aName = attrName(atts, i);
                    string aValue = attrValue(atts, i);

                    // check if the field contains illegal attribute
                    if (!aName.compare("inst_if") && !aName.compare("inst_ifdef") && !aName.compare("subnode") &&
                        adbParser->field_attr_names_set.find(aName) != adbParser->field_attr_names_set.end() &&
                        adbParser->field_spec_attr.find(aName) != adbParser->field_spec_attr.end())
                    {
                        expFound =
                          raiseException(allowMultipleExceptions,
                                         "Unknown attribute: " + aName + " at field: " + adbParser->_currentField->name,
                                         ", in file: \"" + adbParser->_fileName +
                                           "\" line: " + boost::lexical_cast<string>(lineNumber),
                                         ExceptionHolder::ERROR_EXCEPTION);
                    }

                    if (!aName.compare("enum"))
                    {
                        // check the enum attribute is compatible with the enum pattern
                        if (!regex_match(aValue, regex(adbParser->_enum_pattern)))
                        {
                            expFound = raiseException(
                              allowMultipleExceptions,
                              "Illegal value: \"" + aValue + "\" for attribute: \"" + aName + "\" ",
                              "doesn't match the given attribute pattern, in file: \"" + adbParser->_fileName +
                                "\" line: " + boost::lexical_cast<string>(lineNumber),
                              ExceptionHolder::WARN_EXCEPTION);
                        }
                    }
                    else
                    {
                        // check the attribute name is compatible with the attribute pattern
                        if (adbParser->attr_pattern.find(aName) != adbParser->attr_pattern.end() &&
                            !regex_match(aValue, regex(adbParser->attr_pattern[aName])))
                        {
                            expFound = raiseException(
                              allowMultipleExceptions,
                              "Illegal value: \"" + aValue + "\" for attribute: \"" + aName + "\" ",
                              "doesn't match the given attribute pattern, in file: \"" + adbParser->_fileName +
                                "\" line: " + boost::lexical_cast<string>(lineNumber),
                              ExceptionHolder::WARN_EXCEPTION);
                        }
                    }
                }
                adbParser->_currentField->attrs[attrName(atts, i)] = attrValue(atts, i);
            }
        }
    }
}

/**
 * Function: AdbParser::startElement
 **/
void AdbParser::startElement(void* _adbParser, const XML_Char* name, const XML_Char** atts)
{
    AdbParser* adbParser = static_cast<AdbParser*>(_adbParser);

    int lineNumber = XML_GetCurrentLineNumber(adbParser->_xmlParser);
    adbParser->_currentTagValue = "";

    if (TAG_NODES_DEFINITION == name)
    {
        startNodesDefElement(atts, adbParser);
    }
    else if (TAG_ENUM == name)
    {
        startEnumElement(atts, adbParser, lineNumber);
    }
    else if (TAG_CONFIG == name)
    {
        startConfigElement(atts, adbParser, lineNumber);
    }
    else if (TAG_INFO == name)
    {
        startInfoElement(atts, adbParser);
    }
    else if (TAG_INCLUDE == name)
    {
        startIncludeElement(atts, adbParser, lineNumber);
    }
    else if (TAG_INSTANCE_OPS == name)
    {
        adbParser->_instanceOps = true;
    }
    else if (TAG_INSTANCE_OP_ATTR_REPLACE == name)
    {
        startInstOpAttrReplaceElement(atts, adbParser, lineNumber);
    }
    else if (TAG_NODE == name)
    {
        startNodeElement(atts, adbParser, lineNumber);
    }
    else if (TAG_FIELD == name)
    {
        startFieldElement(atts, adbParser, lineNumber);
    }
    else if (TAG_RCS_HEADERS == name)
    {
        // DO NOTHING
    }
    else
    {
        string exceptionTxt = "Unsupported tag: " + string(name);
        if (allowMultipleExceptions)
        {
            exceptionTxt = exceptionTxt + ", in file: \"" + adbParser->_fileName +
                           "\" line: " + boost::lexical_cast<string>(lineNumber);
            ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, exceptionTxt);
            return;
        }
        else
        {
            throw AdbException(exceptionTxt);
        }
    }
}

/**
 * Function: AdbParser::addReserved
 **/
void AdbParser::addReserved(vector<AdbField*>& reserveds, u_int32_t offset, u_int32_t size)
{
    u_int32_t numOfDwords = (dword(offset + size - 1) - dword(offset)) / 4 + 1;

    // printf("==> %s\n", formatAddr(offset, size).c_str());
    // printf("numOfDwords = %d\n", numOfDwords);

    if (numOfDwords == 1 || ((offset % 32) == 0 && ((offset + size) % 32) == 0))
    {
        AdbField* f1 = new AdbField;
        f1->name = "reserved";
        f1->offset = offset;
        f1->isReserved = true;
        f1->size = size;

        reserveds.push_back(f1);
        // printf("case1: reserved0: %s\n", formatAddr(f1->offset, f1->size).c_str());
    }
    else if (numOfDwords == 2)
    {
        AdbField* f1 = new AdbField;
        f1->name = "reserved";
        f1->offset = offset;
        f1->isReserved = true;
        f1->size = 32 - startBit(offset);

        AdbField* f2 = new AdbField;
        f2->name = "reserved";
        f2->offset = dword(offset + 32) * 8;
        f2->isReserved = true;
        f2->size = size - f1->size;
        reserveds.push_back(f1);
        reserveds.push_back(f2);
        /*printf("case2: reserved0: %s, reserved1: %s\n",
         formatAddr(f1->offset, f1->size).c_str(),
         formatAddr(f2->offset, f2->size).c_str());*/
    }
    else
    {
        AdbField* f1 = new AdbField;
        f1->name = "reserved";
        f1->offset = offset;
        f1->isReserved = true;
        f1->size = 32 - startBit(offset);

        AdbField* f2 = new AdbField;
        f2->name = "reserved";
        f2->offset = dword(offset + 32) * 8;
        f2->isReserved = true;
        f2->size = (numOfDwords - 2) * 32;

        if (!((offset + size) % 32))
        {
            f2->size = (numOfDwords - 1) * 32;
            reserveds.push_back(f1);
            reserveds.push_back(f2);
            /*printf("case3.1: reserved0: %s, reserved1: %s\n",
             formatAddr(f1->offset, f1->size).c_str(),
             formatAddr(f2->offset, f2->size).c_str());*/
            return;
        }
        else
        {
            if (!(f1->size % 32))
            {
                f1->size = (numOfDwords - 1) * 32;
                f2->size = size - f1->size;
                f2->offset = f1->offset + f1->size;
                reserveds.push_back(f1);
                reserveds.push_back(f2);
                /*printf("case3.2: reserved0: %s, reserved1: %s\n",
                 formatAddr(f1->offset, f1->size).c_str(),
                 formatAddr(f2->offset, f2->size).c_str());*/
                return;
            }
            else
            {
                f2->size = (numOfDwords - 2) * 32;
                AdbField* f3 = new AdbField;
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
void AdbParser::endElement(void* _adbParser, const XML_Char* name)
{
    AdbParser* adbParser = static_cast<AdbParser*>(_adbParser);
    int lineNumber = XML_GetCurrentLineNumber(adbParser->_xmlParser);
    /*
     * Config
     * ----
     */
    if (TAG_CONFIG == name)
    {
        adbParser->_adbCtxt->configs.push_back(adbParser->_currentConfig);
        adbParser->_currentConfig = NULL;
    }
    /*
     * Instance Operations
     * ----
     */
    else if (TAG_INSTANCE_OPS == name)
    {
        adbParser->_instanceOps = false;
    }
    /*
     * Node
     * ----
     */
    else if (TAG_NODE == name)
    {
        // Sort the fields by offset
        if (adbParser->skipNode)
        {
            adbParser->skipNode = false;
        }
        else
        {
            if (!adbParser->_currentNode->isUnion)
            {
                stable_sort(adbParser->_currentNode->fields.begin(),
                            adbParser->_currentNode->fields.end(),
                            compareFieldsPtr<AdbField>);
            }

            // Check overlapping
            vector<AdbField*> reserveds;
            AdbField prevFieldDummy;
            prevFieldDummy.offset = 0;
            prevFieldDummy.size = 0;
            AdbField* prevField = &prevFieldDummy;
            if (!adbParser->_currentNode->isUnion)
            {
                for (size_t i = 0; i < adbParser->_currentNode->fields.size(); i++)
                {
                    AdbField* field = adbParser->_currentNode->fields[i];
                    long int delta = (long)field->offset - (long)(prevField->offset + prevField->size);

                    if (delta < 0)
                    { // Overlapping
                        string exceptionTxt = "Field: " + field->name + " " + formatAddr(field->offset, field->size) +
                                              " overlaps with Field: " + prevField->name + " " +
                                              formatAddr(prevField->offset, prevField->size);
                        if (allowMultipleExceptions)
                        {
                            exceptionTxt = exceptionTxt + ", in file: \"" + adbParser->_fileName +
                                           "\" line: " + boost::lexical_cast<string>(lineNumber);
                            ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                        }
                        else
                        {
                            throw AdbException(exceptionTxt);
                        }
                    }
                    if (delta > 0 && adbParser->_addReserved)
                    { // Need reserved
                        addReserved(reserveds, prevField->offset + prevField->size, delta);
                    }

                    prevField = field;
                }
            }

            // Add reserved filler at end of union/node
            // special case if node is empty, we need to add reserved anyway
            if (adbParser->_addReserved /*|| adbParser->_currentNode->fields.empty()*/)
            {
                if (adbParser->_currentNode->isUnion)
                {
                    addReserved(reserveds, 0, adbParser->_currentNode->size);
                }
                else
                {
                    long delta = (long)adbParser->_currentNode->size - (long)(prevField->offset + prevField->size);
                    /*if (adbParser->_currentNode->name == "miss_machine_slice_info")
                    {
                    printf("Adding filler\n");
                    printf("node offs: %s, prevField: %s\n", formatAddr(0, adbParser->_currentNode->size).c_str(),
                    formatAddr(prevField->offset, prevField->size).c_str());
                    printf("delta: %ld\n", delta);
                    }*/

                    if (delta > 0)
                    {
                        addReserved(reserveds, prevField->offset + prevField->size, delta);
                    }
                }

                adbParser->_currentNode->fields.insert(adbParser->_currentNode->fields.end(), reserveds.begin(),
                                                       reserveds.end());
            }

            if (adbParser->_checkDsAlign && adbParser->_currentNode->_maxLeafSize != 0 &&
                adbParser->_currentNode->_maxLeafSize != 0 &&
                adbParser->_currentNode->size % adbParser->_currentNode->_maxLeafSize != 0)
            {
                raiseException(
                  allowMultipleExceptions,
                  "Node: " + adbParser->_currentNode->name + " size(" +
                    boost::lexical_cast<string>(adbParser->_currentNode->size) + ") is not aligned with largest leaf(" +
                    boost::lexical_cast<string>(adbParser->_currentNode->_maxLeafSize) + ")",
                  ", in file: \"" + adbParser->_fileName + "\" line: " + boost::lexical_cast<string>(lineNumber),
                  ExceptionHolder::ERROR_EXCEPTION);
            }

            // Re-fix fields offset
            if (adbParser->_adbCtxt->bigEndianArr)
            {
                for (size_t i = 0; i < adbParser->_currentNode->fields.size(); i++)
                {
                    u_int32_t offset = adbParser->_currentNode->fields[i]->offset;
                    u_int32_t size = adbParser->_currentNode->fields[i]->eSize();

                    adbParser->_currentNode->fields[i]->offset =
                      ((offset >> 5) << 5) + ((MIN(32, adbParser->_currentNode->size) - ((offset + size) % 32)) % 32);
                }
            }

            // Resort the fields by offset (since we changed offset to workaround big endian issues and added reserved)
            if (!adbParser->_currentNode->isUnion)
            {
                stable_sort(adbParser->_currentNode->fields.begin(),
                            adbParser->_currentNode->fields.end(),
                            compareFieldsPtr<AdbField>);
            }

            // Add this node to AdbCtxt
            adbParser->_adbCtxt->nodesMap.insert(
              pair<string, AdbNode*>(adbParser->_currentNode->name, adbParser->_currentNode));
            adbParser->_currentNode = 0;

            // Call progress_func callback
            if (adbParser->_progressObj && !(adbParser->_progressCnt++ % PROGRESS_NODE_CNT))
            {
                adbParser->_progressObj->progress(); // TODO - call with real parameters
            }
        }
    }
    /*
     * Field
     * ----
     */
    else if (TAG_FIELD == name)
    {
        // Add this field to current node
        if (!adbParser->skipNode)
        {
            if (adbParser->_currentNode->name == "root")
            {
                adbParser->_adbCtxt->rootNode = adbParser->_currentField->subNode;
            }

            // Check conditions
            bool cond = true;
            AttrsMap::iterator it;
            it = adbParser->_currentField->attrs.find("inst_ifdef");
            if (it != adbParser->_currentField->attrs.end())
            {
                bool found = false;
                for (size_t i = 0; i < adbParser->_adbCtxt->configs.size(); i++)
                {
                    AttrsMap::iterator it_def = adbParser->_adbCtxt->configs[i]->attrs.find("define");
                    if (it_def != adbParser->_adbCtxt->configs[i]->attrs.end())
                    {
                        vector<string> defVal;
                        boost::algorithm::split(defVal, it_def->second, boost::is_any_of(string("=")));

                        if (defVal[0] == it->second)
                        {
                            found = true;
                            break;
                        }
                    }
                }
                cond = found;
            }

            //
            it = adbParser->_currentField->attrs.find("inst_if");
            if (cond && it != adbParser->_currentField->attrs.end())
            {
                // Prepare vars
                map<string, string> vars;
                for (size_t i = 0; i < adbParser->_adbCtxt->configs.size(); i++)
                {
                    AttrsMap::iterator it_def = adbParser->_adbCtxt->configs[i]->attrs.find("define");
                    if (it_def != adbParser->_adbCtxt->configs[i]->attrs.end())
                    {
                        vector<string> defVal;
                        boost::algorithm::split(defVal, it_def->second, boost::is_any_of(string("=")));

                        if (defVal.size() == 1)
                        {
                            vars[defVal[0]] = "0";
                        }
                        else
                        {
                            vars[defVal[0]] = defVal[1];
                        }
                    }
                }

                AdbExpr adbExpr;
                char* expOrg = new char[it->second.size() + 1];
                char* exp = expOrg;
                if (!exp)
                {
                    throw AdbException("Memory allocation error");
                }
                strcpy(exp, it->second.c_str());

                u_int64_t res;
                adbExpr.setVars(&vars);
                int status = adbExpr.expr(&exp, &res);
                delete[] expOrg;
                string statusStr;

                if (status < 0)
                {
                    string exceptionTxt = string("Error evaluating expression \"") + it->second.c_str() +
                                          "\" : " + AdbExpr::statusStr(status);
                    if (allowMultipleExceptions)
                    {
                        exceptionTxt = exceptionTxt + ", in file: \"" + adbParser->_fileName +
                                       "\" line: " + boost::lexical_cast<string>(lineNumber);
                        ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                    }
                    else
                    {
                        throw AdbException(exceptionTxt);
                    }
                }
                cond = !!res;
            }

            if (cond)
            {
                // Name should be unique
                if (adbParser->_strict)
                {
                    for (size_t i = 0; i < adbParser->_currentNode->fields.size(); i++)
                    {
                        if (!adbParser->_currentNode->fields[i]->name.compare(adbParser->_currentField->name))
                        {
                            string exceptionTxt =
                              "The field \"" + adbParser->_currentField->name + "\" isn't unique in node";
                            if (allowMultipleExceptions)
                            {
                                exceptionTxt = exceptionTxt + ", in file: \"" + adbParser->_fileName +
                                               "\" line: " + boost::lexical_cast<string>(lineNumber);
                                ExceptionHolder::insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                            }
                            else
                            {
                                throw AdbException(exceptionTxt);
                            }
                        }
                    }
                }
                it = adbParser->_currentField->attrs.find("condition");
                if (it != adbParser->_currentField->attrs.end())
                {
                    adbParser->_currentField->condition = string(it->second);
                }

                adbParser->_currentNode->fields.push_back(adbParser->_currentField);
            }
            else
            {
                adbParser->_currentNode->condFields.push_back(adbParser->_currentField);
            }
            adbParser->_currentField = 0;
        }
    }
}

/**
 * Function: AdbParser::raiseException
 **/
bool AdbParser::raiseException(bool allowMultipleExceptions, string exceptionTxt, string addedMsg, const string expType)
{
    if (allowMultipleExceptions)
    {
        ExceptionHolder::insertNewException(expType, exceptionTxt + addedMsg);
        return false;
    }
    else
    {
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

Adb::Adb() : bigEndianArr(false), singleEntryArrSupp(false), _checkDsAlign(false), _enforceGuiChecks(false)
{
    _logFile = new LogFile;
}

/**
 * Function: Adb::~Adb
 **/
Adb::~Adb()
{
    // Free configs
    for (size_t i = 0; i < configs.size(); i++)
        delete configs[i];

    // Free nodes
    NodesMap::iterator iter;
    for (iter = nodesMap.begin(); iter != nodesMap.end(); iter++)
        delete iter->second;

    delete _logFile;
}

/**
 * Function: Adb::raiseException
 **/
void Adb::raiseException(bool allowMultipleExceptions, string exceptionTxt, const string expType)
{
    if (allowMultipleExceptions)
    {
        ExceptionHolder::insertNewException(expType, exceptionTxt);
    }
    else
    {
        throw AdbException(exceptionTxt);
    }
    return;
}

/**
 * Function: Adb::getAdbExceptionsMap
 * This function return the adb exception map
 **/
void Adb::fetchAdbExceptionsMap(ExceptionsMap otherMap)
{
    vector<string> fatals = otherMap[ExceptionHolder::FATAL_EXCEPTION];
    for (vector<string>::iterator it = fatals.begin(); it != fatals.end(); ++it)
    {
        insertNewException(ExceptionHolder::FATAL_EXCEPTION, *it);
    }
    vector<string> errors = otherMap[ExceptionHolder::ERROR_EXCEPTION];
    for (vector<string>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        insertNewException(ExceptionHolder::ERROR_EXCEPTION, *it);
    }
    vector<string> warnings = otherMap[ExceptionHolder::WARN_EXCEPTION];
    for (vector<string>::iterator it = warnings.begin(); it != warnings.end(); ++it)
    {
        insertNewException(ExceptionHolder::WARN_EXCEPTION, *it);
    }
}

/**
 * Function: Adb::insertNewException
 * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 * Then it insert it to the adb exception map
 **/
void Adb::insertNewException(const string exceptionType, string exceptionTxt)
{
    adbExceptionMap[exceptionType].push_back(exceptionTxt);
}

/**
 * Function: Adb::printAdbExceptionMap
 * This function will pring the content of the Adb Exception Map
 **/
string Adb::printAdbExceptionMap()
{
    string errorStr = "";
    vector<string> fatals = adbExceptionMap[ExceptionHolder::FATAL_EXCEPTION];
    for (vector<string>::iterator it = fatals.begin(); it != fatals.end(); ++it)
    {
        errorStr += "-" + ExceptionHolder::FATAL_EXCEPTION + "- " + *it + ";";
    }
    vector<string> errors = adbExceptionMap[ExceptionHolder::ERROR_EXCEPTION];
    for (vector<string>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        errorStr += "-" + ExceptionHolder::ERROR_EXCEPTION + "- " + *it + ";";
    }
    vector<string> warnings = adbExceptionMap[ExceptionHolder::WARN_EXCEPTION];
    for (vector<string>::iterator it = warnings.begin(); it != warnings.end(); ++it)
    {
        errorStr += "-" + ExceptionHolder::WARN_EXCEPTION + "- " + "- " + *it + ";";
    }
    return errorStr;
}

/**
 * Function: Adb::load
 **/
bool Adb::load(string fname,
               bool addReserved,
               AdbProgress* progressObj,
               bool strict,
               string includePath,
               string includeDir,
               bool enforceExtraChecks,
               bool allowMultipleExceptions,
               string logFileStr,
               bool checkDsAlign,
               bool enforceGuiChecks)
{
    try
    {
        bool status = true;
        mainFileName = fname;
        if (allowMultipleExceptions)
        {
            AdbParser::setAllowMultipleExceptionsTrue();
        }
        _logFile->init(logFileStr, allowMultipleExceptions);
        AdbParser p(fname, this, addReserved, progressObj, strict, includePath, enforceExtraChecks, checkDsAlign,
                    enforceGuiChecks);
        _checkDsAlign = checkDsAlign;
        _enforceGuiChecks = enforceGuiChecks;
        if (!p.load())
        {
            _lastError = p.getError();
            status = false;
        }
        if (status && includeDir != "")
        {
            AdbParser::includeAllFilesInDir(&p, includeDir);
        }
        if (status && !nodesMap.size())
        {
            _lastError = "Empty project, no nodes were found";
            if (allowMultipleExceptions)
            {
                insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
            }
            status = false;
        }
        if (status)
        {
            bool checkSizeConsistency = strict ? checkInstSizeConsistency(allowMultipleExceptions) : true;
            status = status && checkSizeConsistency;
        }
        if (allowMultipleExceptions && ExceptionHolder::getNumberOfExceptions() > 0)
        {
            fetchAdbExceptionsMap(ExceptionHolder::getAdbExceptionsMap());
            status = false;
        }
        return status;
    }
    catch (AdbException& e)
    {
        _lastError = e.what_s();
        if (allowMultipleExceptions)
        {
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return false;
    }
}

/**
 * Function: Adb::loadFromString
 **/
bool Adb::loadFromString(const char* adbContents,
                         bool addReserved,
                         AdbProgress* progressObj,
                         bool strict,
                         bool enforceExtraChecks)
{
    try
    {
        AdbParser p(string(), this, addReserved, progressObj, strict, "", enforceExtraChecks);
        mainFileName = OS_PATH_SEP;
        if (!p.loadFromString(adbContents))
        {
            _lastError = p.getError();
            return false;
        }

        if (!nodesMap.size())
        {
            _lastError = "Empty project, no nodes were found";
            return false;
        }

        return strict ? checkInstSizeConsistency() : true;
    }
    catch (AdbException& e)
    {
        _lastError = e.what_s();
        return false;
    }
}

/**
 * Function: Adb::toXml
 **/
string Adb::toXml(vector<string> nodeNames, bool addRootNode, string rootName, string addPrefix)
{
    try
    {
        vector<string> nodeDeps;
        for (vector<string>::iterator it = nodeNames.begin(); it != nodeNames.end(); it++)
        {
            vector<string> tmp = getNodeDeps(*it);
            nodeDeps.insert(nodeDeps.end(), tmp.begin(), tmp.end());
        }
        stable_sort(nodeDeps.begin(), nodeDeps.end());
        nodeDeps.erase(unique(nodeDeps.begin(), nodeDeps.end()), nodeDeps.end());

        string xml;
        if (this->version == "2")
        {
            xml = "<NodesDefinition version=\"2\">\n";
        }
        else
        {
            xml = "<NodesDefinition>\n";
        }
        for (ConfigList::iterator it = configs.begin(); it != configs.end(); it++)
        {
            xml += (*it)->toXml() + "\n";
        }

        // Add source info
        xml += "<info source_doc_name=\"" + encodeXml(descNativeToXml(srcDocName)) + "\" source_doc_version=\"" +
               encodeXml(descNativeToXml(srcDocVer)) + "\" />\n";

        if (nodeNames.empty())
        {
            for (NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++)
            {
                AdbNode* node = it->second;
                xml += node->toXml(addPrefix);
            }
        }
        else
        {
            u_int32_t maxSize = 0;
            for (size_t i = 0; i < nodeDeps.size(); i++)
            {
                NodesMap::iterator it = nodesMap.find(nodeDeps[i]);
                if (it == nodesMap.end())
                {
                    _lastError = "Can't find node definition for: " + nodeDeps[i];
                    return "";
                }

                AdbNode* node = it->second;
                xml += node->toXml(addPrefix) + "\n\n";

                maxSize = TOOLS_MAX(node->size, maxSize);
            }

            if (addRootNode)
            {
                stringstream buf;
                buf << "<node name=\"root\" size=\"0x" << hex << ((maxSize >> 5) << 2) << "." << dec << (maxSize % 32)
                    << "\" descr=\"\" >\n";
                buf << "\t<field name=\"" << rootName << "\" offset=\"0x0.0\""
                    << " size=\"0x" << hex << ((maxSize >> 5) << 2) << "." << dec << (maxSize % 32) << "\" subnode=\""
                    << addPrefix + rootName << "\" descr=\"\" />\n";
                buf << "</node>\n\n";

                buf << "<node name=\"" + addPrefix + rootName + "\" size=\"0x" << hex << ((maxSize >> 5) << 2) << "."
                    << dec << (maxSize % 32) << "\" attr_is_union=\"1\" descr=\"\" >\n";
                for (size_t i = 0; i < nodeNames.size(); i++)
                {
                    AdbNode* node = nodesMap[nodeNames[i]];
                    buf << "\t<field name=\"" << node->name << "\" offset=\"0x0.0\" size=\"0x" << hex
                        << ((node->size >> 5) << 2) << "." << dec << (node->size % 32)
                        << "\" subnode=\"" + addPrefix + node->name + "\" descr=\"\" />\n";
                }
                buf << "</node>\n";
                xml += buf.str();
            }
        }

        xml += "</NodesDefinition>\n";
        return xml;
    }
    catch (AdbException& exp)
    {
        _lastError = exp.what_s();
        return "";
    }
}

/**
 * Function: Adb::addMissingNodes
 **/

AdbInstance* Adb::addMissingNodes(int depth, bool allowMultipleExceptions)
{
    try
    {
        NodesMap::iterator it;
        for (it = nodesMap.begin(); it != nodesMap.end(); it++)
        {
            AdbNode* nodeDesc = it->second;
            for (size_t i = 0; (depth == -1 || depth > 0) && i < nodeDesc->fields.size(); i++)
            {
                AdbField* fieldDesc = nodeDesc->fields[i];
                for (u_int32_t i = 0; i < fieldDesc->arrayLen(); i++)
                {
                    if (fieldDesc->isStruct())
                    {
                        NodesMap::iterator it2 = nodesMap.find(fieldDesc->subNode);
                        if (it2 == nodesMap.end())
                        {
                            // If in ignore missing nodes mode, it should create temporary node with placeholder
                            AdbNode* tmpNode = new AdbNode;
                            tmpNode->name = fieldDesc->subNode;
                            tmpNode->size = fieldDesc->eSize();
                            tmpNode->desc = fieldDesc->desc + " ***MISSING NODE***";
                            tmpNode->isUnion = false;
                            tmpNode->fileName = "tempForMissingNodes.adb";
                            tmpNode->lineNumber = 0;
                            AdbField* tmpField = new AdbField;
                            tmpField->name = "placeholder";
                            tmpField->desc = "This field is part of auto generated node for missing node.";
                            tmpField->size = tmpNode->size;
                            tmpField->offset = 0;
                            tmpNode->fields.push_back(tmpField);
                            nodesMap.insert(pair<string, AdbNode*>(tmpNode->name, tmpNode));
                        }
                    }
                }
            }
        }
    }
    catch (AdbException& exp)
    {
        _lastError = exp.what_s();
        if (allowMultipleExceptions)
        {
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return NULL;
    }
    catch (...)
    {
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
    for (InstanceAttrs::iterator it = instAttrs.begin(); it != instAttrs.end(); it++)
    {
        it->second.clear();
    }
    instAttrs.clear();
}

/**
 * Function: Adb::createLayout
 **/
AdbInstance* Adb::createLayout(string rootNodeName,
                               bool isExprEval,
                               AdbProgress* progressObj,
                               int depth,
                               bool ignoreMissingNodes,
                               bool allowMultipleExceptions)
{
    try
    {
        // find root in nodes map
        NodesMap::iterator it;
        it = nodesMap.find(rootNodeName);
        if (it == nodesMap.end())
        {
            raiseException(allowMultipleExceptions,
                           "Can't find definition for node \"" + rootNodeName + "\"",
                           ExceptionHolder::FATAL_EXCEPTION);
        }

        AdbNode* nodeDesc = it->second;
        nodeDesc->inLayout = true;
        AdbInstance* rootItem = new AdbInstance();
        rootItem->fieldDesc = NULL;
        rootItem->nodeDesc = nodeDesc;
        rootItem->parent = NULL;
        rootItem->name = nodeDesc->name;
        rootItem->offset = 0;
        rootItem->size = nodeDesc->size;
        rootItem->copyAllInstanceAttr(nodeDesc->attrs);

        map<string, string> emptyVars;
        _unionSelectorEvalDeffered.clear();
        _conditionInstances.clear();
        if (ignoreMissingNodes)
        {
            addMissingNodes(depth, allowMultipleExceptions);
        }

        for (size_t i = 0; (depth == -1 || depth > 0) && i < nodeDesc->fields.size(); i++)
        {
            vector<AdbInstance*> subItems =
              createInstance(nodeDesc->fields[i], rootItem, emptyVars, isExprEval, progressObj,
                             depth == -1 ? -1 : depth - 1, ignoreMissingNodes, allowMultipleExceptions);
            rootItem->subItems.insert(rootItem->subItems.end(), subItems.begin(), subItems.end());
        }

        // Now set the instance attributes (override field attrs), only if this is root node instantiation
        if (rootNodeName == rootNode && depth == -1)
        {
            for (InstanceAttrs::iterator it = instAttrs.begin(); it != instAttrs.end(); it++)
            {
                size_t idx = it->first.find(".");
                string path = idx == string::npos ? string() : it->first.substr(idx + 1);

                AdbInstance* inst = rootItem->getChildByPath(path);
                if (!inst)
                {
                    raiseException(allowMultipleExceptions,
                                   "Can't find instance path (" + it->first + ") defined in <instance_ops> section",
                                   ExceptionHolder::ERROR_EXCEPTION);
                }

                for (AttrsMap::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
                {
                    if (allowMultipleExceptions && !inst)
                    {
                        break;
                    }
                    inst->setInstanceAttr(it2->first, it2->second);
                }
            }
        }

        /* Evaluate unions selector fields*/
        for (list<AdbInstance*>::iterator it = _unionSelectorEvalDeffered.begin();
             it != _unionSelectorEvalDeffered.end();
             it++)
        {
            bool foundSelector = true;
            vector<string> path;
            AdbInstance* inst = *it;
            AdbInstance* curInst = inst;
            const string splitVal = inst->getInstanceAttr("union_selector");
            boost::algorithm::split(path, splitVal, boost::is_any_of(string(".")));
            for (size_t i = 0; i < path.size(); i++)
            {
                if (path[i] == "#(parent)" || path[i] == "$(parent)")
                {
                    curInst = curInst->parent;
                    if (curInst == NULL || i == path.size() - 1)
                    {
                        foundSelector = false;
                        if (rootNodeName == rootNode)
                        { // give this warning only if this root instantiation
                            if (allowMultipleExceptions)
                                cout << "allow multiple";
                            raiseException(allowMultipleExceptions,
                                           "Invalid union selector (" + inst->fullName() +
                                             "), must be a leaf field, cannot be a parent of root",
                                           ExceptionHolder::ERROR_EXCEPTION);
                        }
                        break;
                    }
                }
                else
                {
                    size_t j;
                    bool inPath = false;
                    for (j = 0; j < curInst->subItems.size(); j++)
                    {
                        if (curInst->subItems[j]->name == path[i])
                        {
                            curInst = curInst->subItems[j];
                            inPath = true;
                            break;
                        }
                    }

                    if (j == curInst->subItems.size() && !inPath)
                    {
                        foundSelector = false;
                        if (rootNodeName == rootNode)
                        { // give this warning only if this root instantiation
                            raiseException(allowMultipleExceptions,
                                           "Failed to find union selector for union (" + inst->fullName() +
                                             ") Can't find field (" + path[i] + ") under (" + curInst->fullName() + ")",
                                           ExceptionHolder::ERROR_EXCEPTION);
                        }
                        break;
                    }
                }
            }

            if (foundSelector)
            {
                inst->unionSelector = curInst;
                for (size_t i = 0; i < inst->subItems.size(); i++)
                {
                    // printf("Field %s, isResered=%d\n", inst->subItems[i]->fullName().c_str(),
                    // inst->subItems[i]->isReserved());
                    if (inst->subItems[i]->isReserved())
                    {
                        continue;
                    }

                    // make sure all union subnodes define "selected_by" attribute
                    bool found = false;
                    AttrsMap::iterator selectorValIt = inst->subItems[i]->getInstanceAttrIterator("selected_by", found);
                    if (!found)
                    {
                        raiseException(allowMultipleExceptions,
                                       "In union (" + inst->fullName() + ") the union subnode (" +
                                         inst->subItems[i]->name + ") doesn't define selection value",
                                       ExceptionHolder::ERROR_EXCEPTION);
                    }

                    // make sure that all union subnodes selector values are defined in the selector field enum
                    if (selectorValIt->second == "")
                    {
                        continue;
                    }

                    if (!inst->unionSelector->isEnumExists())
                    {
                        string exceptionTxt = "In union (" + inst->fullName() + ") the union selector (" +
                                              inst->unionSelector->fullName() + ") is not an enum";
                        raiseException(allowMultipleExceptions, exceptionTxt, ExceptionHolder::ERROR_EXCEPTION);
                        break;
                    }

                    map<string, u_int64_t>::iterator it;
                    map<string, u_int64_t> selectorValMap = inst->unionSelector->getEnumMap();
                    for (it = selectorValMap.begin(); it != selectorValMap.end(); it++)
                    {
                        if (it->first == selectorValIt->second)
                        {
                            break;
                        }
                    }

                    // if not found in map throw exeption
                    if (it == selectorValMap.end())
                    {
                        string exceptionTxt = "In union (" + inst->fullName() + ") the union subnode (" +
                                              inst->subItems[i]->name + ") uses a selector value (" +
                                              selectorValIt->second + ") which isn't defined in the selector field (" +
                                              inst->unionSelector->fullName() + ")";
                        raiseException(allowMultipleExceptions, exceptionTxt, ExceptionHolder::ERROR_EXCEPTION);
                    }
                }
            }
        }

        // initialize condition variables objects
        for (list<AdbInstance*>::iterator it = _conditionInstances.begin(); it != _conditionInstances.end(); it++)
        {
            map<string, CondVar> variables = (*it)->condition.getVarsMap();
            for (map<string, CondVar>::iterator it2 = variables.begin(); it2 != variables.end(); it2++)
            {
                string currentName = it2->first;
                CondVar* currentVar = &(it2->second);
                map<string, string>::iterator currentDefine = defines_map.find(currentName);
                if (currentDefine != defines_map.end())
                {
                    currentVar->setScalar(std::stoi(currentDefine->second));
                }
                // else // if it's a conditional variable
                // {
                //     //TODO: to be evaluated later!
                // }
            }
        }

        if (allowMultipleExceptions && ExceptionHolder::getNumberOfExceptions() > 0)
        {
            fetchAdbExceptionsMap(ExceptionHolder::getAdbExceptionsMap());
            rootItem = NULL;
        }
        return rootItem;
    }
    catch (AdbException& exp)
    {
        _lastError = exp.what_s();
        if (allowMultipleExceptions)
        {
            insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
        }
        return NULL;
    }
    catch (...)
    {
        _lastError = "Unknown error occurred";
        return NULL;
    }
}

/**
 * Function: Adb::getNodeDeps
 **/
vector<string> Adb::getNodeDeps(string nodeName)
{
    NodesMap::iterator it = nodesMap.find(nodeName);
    if (it == nodesMap.end())
    {
        throw AdbException("Can't find node definition for: " + nodeName);
    }

    AdbNode* node = it->second;
    vector<string> deps(1, node->name);

    for (size_t i = 0; i < node->fields.size(); i++)
    {
        if (node->fields[i]->isStruct())
        {
            deps.push_back(node->fields[i]->subNode);
            vector<string> subDeps = getNodeDeps(node->fields[i]->subNode);
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
vector<AdbInstance*> Adb::createInstance(AdbField* field,
                                         AdbInstance* parent,
                                         map<string, string> vars,
                                         bool isExprEval,
                                         AdbProgress* progressObj,
                                         int depth,
                                         bool ignoreMissingNodes,
                                         bool allowMultipleExceptions)
{
    static const regex EXP_PATTERN("\\s*([a-zA-Z0-9_]+)=((\\$\\(.*?\\)|\\S+|$)*)\\s*");
    if (progressObj)
    {
        progressObj->progress();
    }

    // if array create instance for each item. else - create 1
    vector<AdbInstance*> instList;
    for (u_int32_t i = 0; i < field->arrayLen(); i++)
    {
        AdbInstance* inst = new AdbInstance;
        inst->fieldDesc = field;

        // if field is struct - find field->subNode in nodes map and addto instance not desc

        if (field->isStruct())
        {
            NodesMap::iterator it = nodesMap.find(field->subNode);
            if (it == nodesMap.end())
            {
                delete inst;
                raiseException(allowMultipleExceptions,
                               "Can't find the definition for subnode: " + field->subNode + " of field: " + field->name,
                               ExceptionHolder::ERROR_EXCEPTION);
                return instList;
            }
            else
            {
                inst->nodeDesc = it->second;
            }
        }

        if (inst)
        {
            inst->name = field->name;
            inst->arrIdx = 0;
            inst->size = field->eSize();
            inst->parent = parent;
        }

        if (field->offset == 0xffffffff)
        {
            if (parent->subItems.size() > 0)
            {
                field->offset = parent->subItems.back()->offset;
            }
            else
            {
                field->offset = parent->offset;
            }
        }
        inst->offset = calcArrOffset(field, parent, i);
        if (field->isArray())
        {
            inst->name += "[" + boost::lexical_cast<string>(i + field->lowBound) + "]";
            inst->arrIdx = i;
        }
        // printf("field: %s, offset: %s (%d)\n", inst->name.c_str(),formatAddr(inst->offset, inst->size).c_str(),
        // inst->offset);

        if (isExprEval)
        {
            try
            {
                // First add the special variables
                char tmpStr[32];
                vars["NAME"] = inst->name;
                vars["ARR_IDX"] = boost::lexical_cast<string>(inst->arrIdx);
                sprintf(tmpStr, "[%d:%d]", inst->offset % 32 + inst->size - 1, inst->offset % 32);
                vars["BN"] = tmpStr;
                vars["parent"] = "#(parent)"; // special internal name

                // Get variables attribute value
                AttrsMap::iterator it = field->attrs.find("variables");
                string varStr = (it == field->attrs.end() ? string() : it->second);
                boost::algorithm::trim(varStr);

                // build var_name->value map from varAttrStr
                AttrsMap curVars;
                if (!varStr.empty())
                {
                    match_results<string::const_iterator> what;
                    string::const_iterator start = varStr.begin();
                    string::const_iterator end = varStr.end();

                    while (regex_search(start, end, what, EXP_PATTERN))
                    {
                        string var(what[1].first, what[1].second);
                        string exp(what[2].first, what[2].second);
#if 0
                        printf("%s) %s <=> %s\n", inst->fullName().c_str(), var.c_str(), exp.c_str());
                        printf("Variable Attr: %s\n", inst->field->attrs["variables"].c_str());
#endif
                        start = what[0].second;
                        curVars[var] = exp;
                    }

                    for (AttrsMap::iterator it = curVars.begin(); it != curVars.end(); it++)
                    {
                        vars[it->first] = it->second;
                    }

                    // evaluate the variables themselves
                    for (AttrsMap::iterator it = curVars.begin(); it != curVars.end(); it++)
                    {
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
                for (AttrsMap::iterator it = field->attrs.begin(); it != field->attrs.end(); it++)
                {
                    if (it->first == "variables")
                    {
                        continue;
                    }

                    inst->setInstanceAttr(it->first, evalExpr(it->second, &vars));
                }
                inst->setVarsMap(vars);
            }
            catch (AdbException& exp)
            {
                string exceptionTxt =
                  "Failed to evaluate expression for field (" + inst->fullName() + "): " + exp.what_s();
                if (allowMultipleExceptions)
                {
                    insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
                }
                else
                {
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
        if (inst->isUnion() && found)
        {
            _unionSelectorEvalDeffered.push_back(inst);
        }

        // if the field has a condition attribute
        found = false;
        inst->getInstanceAttrIterator("condition", found);
        AdbInstance* parent = inst->parent;
        if (found && parent->getInstanceAttr("is_conditional") == "1")
        {
            const string condition = inst->getInstanceAttr("condition");
            inst->condition.setCondition(condition);
            _conditionInstances.push_back(inst);
        }

        checkInstanceOffsetValidity(inst, parent, allowMultipleExceptions);

        if (field->isStruct() && !inst->nodeDesc->fields.empty() && (depth == -1 || depth > 0))
        {
            if (inst->nodeDesc->inLayout)
            {
                delete inst;
                raiseException(false,
                               "Cyclic definition of nodes, node: " + field->name + " was already added to the layout",
                               ExceptionHolder::ERROR_EXCEPTION);
            }
            inst->nodeDesc->inLayout = true;

            // validation 2
            if (inst->size != inst->nodeDesc->size)
            {
                inst->nodeDesc->size = inst->size;
                /*throw AdbException("Node +(" + inst->name + ") size (" + boost::lexical_cast<string>(inst->size)) +
                 " isn't the same as its instance (" + inst->nodeDesc->name +
                 ") (" +  boost::lexical_cast<string>(inst->nodeDesc->size) + ")";*/
            }

            vector<AdbField*>::iterator it;
            for (it = inst->nodeDesc->fields.begin(); it != inst->nodeDesc->fields.end(); it++)
            {
                map<string, string> varsCopy = vars;
                vector<AdbInstance*> subItems =
                  createInstance(*it, inst, vars, isExprEval, progressObj, depth == -1 ? -1 : depth - 1,
                                 ignoreMissingNodes, allowMultipleExceptions);
                if (subItems.size() > 0)
                {
                    inst->subItems.insert(inst->subItems.end(), subItems.begin(), subItems.end());
                    if (subItems[0]->maxLeafSize > inst->maxLeafSize)
                    {
                        inst->maxLeafSize = subItems[0]->maxLeafSize;
                    }
                }
            }
            inst->nodeDesc->inLayout = false;

            if (_checkDsAlign && inst->maxLeafSize != 0 && inst->size % inst->maxLeafSize != 0)
            {
                raiseException(allowMultipleExceptions,
                               "Node: " + inst->nodeDesc->name + " size(" + boost::lexical_cast<string>(inst->size) +
                                 ") is not aligned with largest leaf(" +
                                 boost::lexical_cast<string>(inst->maxLeafSize) + ")",
                               ExceptionHolder::ERROR_EXCEPTION);
            }

            if (!inst->isUnion() && inst->subItems.size() > 0)
            {
                stable_sort(inst->subItems.begin(), inst->subItems.end(), compareFieldsPtr<AdbInstance>);

                for (size_t j = 0; j < inst->subItems.size() - 1; j++)
                {
                    // printf("field: %s, offset: %s\n",
                    // inst->subItems[j+1]->name.c_str(),formatAddr(inst->subItems[j+1]->offset,
                    // inst->subItems[j+1]->size).c_str()); printf("field: %s, offset: %s\n",
                    // inst->subItems[j]->name.c_str(),formatAddr(inst->subItems[j]->offset,
                    // inst->subItems[j]->size).c_str());
                    if (inst->subItems[j + 1]->offset < inst->subItems[j]->offset + inst->subItems[j]->size)
                    {
                        string exceptionTxt =
                          "Field (" + inst->subItems[j + 1]->name + ") (" +
                          formatAddr(inst->subItems[j + 1]->offset, inst->subItems[j + 1]->size).c_str() +
                          ") overlaps with (" + inst->subItems[j]->name + ") (" +
                          formatAddr(inst->subItems[j]->offset, inst->subItems[j]->size).c_str() + ")";
                        raiseException(allowMultipleExceptions, exceptionTxt, ExceptionHolder::ERROR_EXCEPTION);
                    }
                }
            }
        }

        u_int32_t esize = inst->fieldDesc->size;
        if ((field->isLeaf() || field->subNode == "uint64") && (esize == 16 || esize == 32 || esize == 64)) // A leaf
        {
            inst->maxLeafSize = esize;
        }
        instList.push_back(inst);
    }

    stable_sort(instList.begin(), instList.end(), compareFieldsPtr<AdbInstance>);
    return instList;
}

/**
 * Function: Adb::checkInstanceOffsetValidity
 **/
void Adb::checkInstanceOffsetValidity(AdbInstance* inst, AdbInstance* parent, bool allowMultipleExceptions)
{
    if (inst->offset + inst->size > parent->offset + parent->size)
    {
        string exceptionTxt = "Field (" + inst->name + ") " + formatAddr(inst->offset, inst->size) +
                              " crosses its parent node (" + parent->name + ") " +
                              formatAddr(parent->offset, parent->size) + " boundaries";
        if (allowMultipleExceptions)
        {
            insertNewException(ExceptionHolder::ERROR_EXCEPTION, exceptionTxt);
        }
        else
        {
            throw AdbException(exceptionTxt);
        }
    }
}

/**
 * Function: Adb::calcArrOffset
 **/
u_int32_t Adb::calcArrOffset(AdbField* fieldDesc, AdbInstance* parent, u_int32_t arrIdx)
{
    int offs;

    if (fieldDesc->eSize() >= 32)
    {
        // Make sure this is dword aligned
        if (fieldDesc->eSize() % 32 || parent->offset % 32 || fieldDesc->offset % 32)
        {
            throw AdbException("Field " + fieldDesc->name + " isn't dword aligned");
        }
        offs = parent->offset + fieldDesc->offset + fieldDesc->eSize() * arrIdx;
    }
    else
    {
        if (bigEndianArr)
        {
            offs = (int)parent->offset + (int)fieldDesc->offset - (int)fieldDesc->eSize() * arrIdx;

            int dwordDelta = abs((dword(parent->offset + fieldDesc->offset) - dword(offs))) / 4;

            if (dwordDelta)
            {
                offs += 32 * 2 * dwordDelta;
            }
        }
        else
        {
            offs = parent->offset + fieldDesc->offset + fieldDesc->eSize() * arrIdx;
        }
    }

    return offs;
}

/**
 * Function: Adb::evalExpr
 **/
string Adb::evalExpr(string expr, AttrsMap* vars)
{
    if (expr.find('$') == string::npos)
    {
        return expr;
    }

    smatch what, what2;
    regex singleExpr("^([^\\$]*)(\\$\\(([^)]+)\\))(.*)$");
    while (regex_search(expr, what, singleExpr))
    {
        string vname = what[3].str();
        string vvalue;
        regex singleVar("^[a-zA-Z_][a-zA-Z0-9_]*$");

        // Need to change to array-like initialization when we'll move to c++11
        vector<string> specialVars;
        specialVars.push_back("NAME");
        specialVars.push_back("ARR_IDX");
        specialVars.push_back("BN");
        specialVars.push_back("parent");

        if (regex_search(vname, what2, singleVar))
        {
            if (find(specialVars.begin(), specialVars.end(), vname) == specialVars.end())
            {
                return expr;
            }
            else
            {
                AttrsMap::iterator it = vars->find(vname);
                if (it == vars->end())
                {
                    throw AdbException("Can't find the variable: " + vname);
                }
                vvalue = it->second;
            }
        }
        else
        {
            string vnameCopy = vname;
            regex singleVarInExpr("[a-zA-Z_][a-zA-Z0-9_]*");
            smatch matches;
            while (regex_search(vnameCopy, matches, singleVarInExpr))
            {
                if (find(specialVars.begin(), specialVars.end(), matches[0]) == specialVars.end())
                {
                    return expr;
                }
                vnameCopy = matches.suffix();
            }

            char exp[vname.size() + 1];
            char* expPtr = exp;
            strcpy(exp, vname.c_str());
            u_int64_t res;
            _adbExpr.setVars(vars);
            int status = _adbExpr.expr(&expPtr, &res);
            string statusStr;

            // printf("-D- Eval expr \"%s\" = %ul.\n", vname.ascii(), (u_int32_t)res);

            if (status < 0)
            {
                switch (status)
                {
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

                throw AdbException("Error evaluating expression " + expr + " : " + statusStr);
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
bool Adb::checkInstSizeConsistency(bool allowMultipleExceptions)
{
    bool status = true;
    for (NodesMap::iterator it = nodesMap.begin(); it != nodesMap.end(); it++)
    {
        for (size_t i = 0; i < it->second->fields.size(); i++)
        {
            if (it->second->fields[i]->isStruct())
            {
                NodesMap::iterator iter = nodesMap.find(it->second->fields[i]->subNode);
                if (iter == nodesMap.end())
                {
                    continue;
                    /*
                     _lastError = "Can't find definition of subnode \"" + it->second->fields[i]->subNode +
                     "\" instantiated from node \"" + it->first + "\"";
                     return false;
                     */
                }
                AdbNode* node = nodesMap[it->second->fields[i]->subNode];
                if (node->size != it->second->fields[i]->size / it->second->fields[i]->arrayLen())
                {
                    char tmp[256];
                    sprintf(tmp, "Node (%s) size 0x%x.%d is not consistent with the instance (%s->%s) size 0x%x.%d",
                            node->name.c_str(), (node->size >> 5) << 2, node->size % 32, it->second->name.c_str(),
                            it->second->fields[i]->name.c_str(), (it->second->fields[i]->size >> 5) << 2,
                            it->second->fields[i]->size % 32);
                    _lastError = tmp;
                    if (allowMultipleExceptions)
                    {
                        status = false;
                        insertNewException(ExceptionHolder::ERROR_EXCEPTION, tmp);
                    }
                    else
                    {
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
string Adb::getLastError()
{
    return _lastError;
}

/**
 * Function: Adb::print
 **/
void Adb::print(int indent)
{
    cout << indentString(indent) << "Include paths: " << endl;
    for (size_t i = 0; i < includePaths.size(); i++)
        cout << indentString(indent + 1) << includePaths[i] << endl;

    cout << indentString(indent) << "Is Big Endian Arrays: " << bigEndianArr << endl;
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
