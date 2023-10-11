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

#include "adb_xml_parser.h"
#include "adb_parser.h"
#include "adb_exceptionHolder.h"
#include "adb_config.h"
#include "adb_field.h"
#include "adb_expr.h"

#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "common/algorithm.h"
#include "common/filesystem.h"
#include "common/regex.h"

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

typedef map<string, string> AttrsMap;

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
                     bool evalExpr,
                     bool strict,
                     string includePath,
                     bool enforceExtraChecks,
                     bool checkDsAlign,
                     bool enforceGuiChecks,
                     bool force_pad_32) :
    _adbCtxt(adbCtxt),
    _fileName(fileName),
    _addReserved(addReserved),
    _isExprEval(evalExpr),
    _strict(strict),
    _checkDsAlign(checkDsAlign),
    skipNode(false),
    _includePath(includePath),
    _currentNode(0),
    _currentField(0),
    _currentConfig(0),
    _enforceGuiChecks(enforceGuiChecks),
    _force_pad_32(force_pad_32),
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
        mstflint::common::algorithm::split(path, fileName, mstflint::common::algorithm::is_any_of(string(OS_PATH_SEP)));
        // IncludeFileInfo info = {fileName, "ROOT", 0};
        // _adbCtxt->includedFiles[path[path.size() - 1]] = info;

        _adbCtxt->add_include(path[path.size() - 1], fileName, "ROOT", 0);
    }
    _instanceOps = false;
}

void AdbParser::addIncludePaths(Adb* adbCtxt, string includePaths)
{
    vector<string> paths;
    mstflint::common::algorithm::split(paths, includePaths, mstflint::common::algorithm::is_any_of(string(";")));
    adbCtxt->includePaths.insert(adbCtxt->includePaths.end(), paths.begin(), paths.end());

    vector<string> relatives;
    string projPath = mstflint::common::filesystem::path(adbCtxt->mainFileName).parent_path().string();

    for (vector<string>::iterator it = adbCtxt->includePaths.begin(); it != adbCtxt->includePaths.end(); it++)
    {
        if (projPath != "" && projPath != *it && mstflint::common::filesystem::path(*it).is_relative())
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
bool AdbParser::load(bool is_main)
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

        if (is_main)
        {
            auto root_node_it = _adbCtxt->nodesMap.find("root");
            if (root_node_it == _adbCtxt->nodesMap.end())
            {
                throw AdbException("No root found.");
            }
            else if (root_node_it->second->fields.size() == 0)
            {
                throw AdbException("Root node doesn't contain any field. Root must contain exactly one field.");
            }
            else if (root_node_it->second->fields.size() > 1)
            {
                throw AdbException("Only one field allowed in root node. (Check the root size and fields)");
            }
        }
    }
    catch (AdbException& exp)
    {
        if (exp.what_s().find("in file:") == string::npos)
        {
            int line = XML_GetCurrentLineNumber(_xmlParser);
            int column = XML_GetCurrentColumnNumber(_xmlParser);
            _lastError = exp.what_s() + " in file: " + _fileName + " at line: " + to_string(line) +
                         " column: " + to_string(column);
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
                     " at line: " + to_string(line) + " column: " + to_string(column);
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
            _lastError = exp.what_s() + " in file: " + _fileName + " at line: " + to_string(line) +
                         " column: " + to_string(column);
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
                     " at line: " + to_string(line) + " column: " + to_string(column);
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
        mstflint::common::algorithm::to_lower(s);
        char* end;
        vector<string> words;
        mstflint::common::algorithm::split(words, s, mstflint::common::algorithm::is_any_of(string(".")));

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
    return mstflint::common::algorithm::replace_all_copy(desc, "\\;", "\n");
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
                mstflint::common::algorithm::split(defVal, it_def->second, mstflint::common::algorithm::is_any_of(string("=")));

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

    if (!mstflint::common::filesystem::path(fileName).is_relative())
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
    mstflint::common::filesystem::path boostPath(filePath);
    fileName = boostPath.filename().string();

    if (!adbParser->_adbCtxt->includedFiles.count(fileName))
    {
        // IncludeFileInfo info = {filePath, adbParser->_fileName, lineNumber};
        // adbParser->_adbCtxt->includedFiles[fileName] = info;

        adbParser->_adbCtxt->add_include(fileName, filePath, adbParser->_fileName, lineNumber);

        // parse the included file
        AdbParser p(filePath, adbParser->_adbCtxt, adbParser->_addReserved, adbParser->_isExprEval, adbParser->_strict,
                    "", adbParser->_enforceExtraChecks, adbParser->_checkDsAlign, adbParser->_enforceGuiChecks,
                    adbParser->_force_pad_32);
        if (!p.load(false))
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
    mstflint::common::filesystem::path mainFile(adbParser->_fileName);
    mstflint::common::algorithm::split(paths, dirPath, mstflint::common::algorithm::is_any_of(string(";")));
    for (vector<string>::iterator pathIt = paths.begin(); pathIt != paths.end(); pathIt++)
    {
        // first look in the main file's path
        mstflint::common::filesystem::path fsPath(mainFile.parent_path().string() + "/" + *pathIt);
        if (!mstflint::common::filesystem::exists(fsPath))
        {
            fsPath = mstflint::common::filesystem::path(*pathIt);
        }

        if (mstflint::common::filesystem::exists(fsPath) && mstflint::common::filesystem::is_directory(fsPath))
        {
            addIncludePaths(adbParser->_adbCtxt, *pathIt);
            mstflint::common::filesystem::directory_iterator filesIter(fsPath), dirEnd;
            for (; filesIter!=dirEnd; ++filesIter)
            {
                if (mstflint::common::filesystem::is_regular_file(filesIter->status()) && filesIter->path().extension() == ".adb")
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
    mstflint::common::regex::smatch match;
    mstflint::common::regex::regex allowedCharsExpr("[^\\w\\[\\]]"); // only alphanumeric and square brackets are allowed
    if (mstflint::common::regex::regex_search(tagName, match, allowedCharsExpr))
    {
        return false;
    }
    mstflint::common::regex::regex checkArrayExpr("[\\[\\]]"); // this check if containing the array brackets
    if (mstflint::common::regex::regex_search(tagName, match, checkArrayExpr))
    {
        mstflint::common::regex::regex correctNameForArrayExpr("[_A-Za-z][\\w]*\\[[\\d]+\\]$");
        if (!mstflint::common::regex::regex_search(tagName, match, correctNameForArrayExpr))
        { // check the name if correct the square brackets (array)
            return false;
        }
    }
    else
    {
        mstflint::common::regex::regex correctNameNoneArrayExpr("[_A-Za-z][\\w]*$");
        if (!mstflint::common::regex::regex_search(tagName, match, correctNameNoneArrayExpr))
        { // check the name if correct without the square brackets (not array)
            return false;
        }
    }
    return true;
}

bool AdbParser::checkHEXFormat(string addr)
{
    mstflint::common::regex::smatch match;
    mstflint::common::regex::regex correctHEXExpr("^(0x[0-9A-fa-f])?[0-9A-Fa-f]*(\\.[0-9]*)?$");
    if (!mstflint::common::regex::regex_search(addr, match, correctHEXExpr))
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
        expFound = raiseException(allowMultipleExceptions,
                                  "\"enum\" tag must be inside relevant \"config\" tag",
                                  ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                  ExceptionHolder::ERROR_EXCEPTION);
    }

    string tagName = attrValue(atts, "name");
    string value = attrValue(atts, "value");
    if (adbParser->_enforceExtraChecks)
    {
        if (!AdbParser::checkSpecialChars(tagName))
        {
            expFound = raiseException(allowMultipleExceptions,
                                      "Invalid character in enum name, in enum: \"" + tagName + "\"",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::WARN_EXCEPTION);
        }
    }
    if (tagName.empty() || value.empty())
    {
        expFound = raiseException(allowMultipleExceptions,
                                  "Both \"name\" and \"value\" attributes must be specified",
                                  ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
        expFound = raiseException(allowMultipleExceptions,
                                  "config tag can't appear within other config",
                                  ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                aValue = mstflint::common::regex::regex_replace(aValue, mstflint::common::regex::regex("\\s+"), string(""));
                mstflint::common::algorithm::split(adbParser->field_mand_attr, aValue, mstflint::common::algorithm::is_any_of(","));
            }

            // check the define statement is according to format
            else if (!aName.compare("define"))
            {
                mstflint::common::regex::smatch result;
                mstflint::common::regex::regex pattern(TAG_ATTR_DEFINE_PATTERN);
                if (!mstflint::common::regex::regex_match(aValue, result, pattern))
                {
                    expFound =
                      raiseException(allowMultipleExceptions,
                                     string("Bad define format: \"") + aName + "\" attribute value: \"" + aValue + "\"",
                                     ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                     ExceptionHolder::ERROR_EXCEPTION);
                }
                else
                {
                    // check for define duplication
                    string define_key = result[1], define_value = result[2];

                    if (adbParser->_adbCtxt->defines_map.find(define_key) != adbParser->_adbCtxt->defines_map.end())
                    {
                        expFound =
                          raiseException(allowMultipleExceptions,
                                         string("Multiple definition of preprocessor variable: \"") + define_key +
                                           "\" attribute name: \"" + aName + "\"",
                                         ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                    expFound =
                      raiseException(allowMultipleExceptions,
                                     string("field_attr type must be specified: \"") + aName +
                                       "\" attribute value: \"" + aValue + "\"",
                                     ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                                         ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }

                // check if 'pattern' was provided
                if (checkAttrExist(atts, "pattern"))
                {
                    // check if the given pattern is a valid reg expression.
                    try
                    {
                        string pattern_value = attrValue(atts, "pattern");
                        mstflint::common::regex::regex r(pattern_value);
                        adbParser->attr_pattern.insert(pair<string, string>(aValue, pattern_value));
                    }
                    catch (...)
                    {
                        expFound =
                          raiseException(allowMultipleExceptions,
                                         string("Bad attribute pattern: \"") + aValue + "\" name Pattern: \"" +
                                           attrValue(atts, "pattern") + "\"",
                                         ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                    mstflint::common::regex::regex r(nname_pattern);
                    adbParser->_nname_pattern = nname_pattern;
                }
                catch (...)
                {
                    expFound =
                      raiseException(allowMultipleExceptions,
                                     string("Bad node name pattern: \"") + aValue + "\" pattern: \"" +
                                       attrValue(atts, "nname_pattern") + "\"",
                                     ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                    mstflint::common::regex::regex r(fname_pattern);
                    adbParser->_fname_pattern = fname_pattern;
                }
                catch (...)
                {
                    expFound =
                      raiseException(allowMultipleExceptions,
                                     string("Bad field name pattern: \"") + aValue + "\" pattern: \"" +
                                       attrValue(atts, "fname_pattern") + "\"",
                                     ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                     ExceptionHolder::ERROR_EXCEPTION);
                }
            }
        }

        // Parse attrs that affect the parser itself
        if (!TAG_ATTR_BIG_ENDIAN.compare(aName))
        {
            try
            {
                int val = stoi(aValue);
                adbParser->_adbCtxt->bigEndianArr = val != 0;
            }
            catch (std::exception&)
            {
                expFound =
                  raiseException(allowMultipleExceptions,
                                 string("Filed to parse the \"") + aName + "\" attribute value: \"" + aValue + "\"",
                                 ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                 ExceptionHolder::ERROR_EXCEPTION);
            }
        }

        if (!TAG_ATTR_SINGLE_ENTRY_ARR.compare(aName))
        {
            try
            {
                int val = stoi(aValue);
                adbParser->_adbCtxt->singleEntryArrSupp = val != 0;
            }
            catch (std::exception&)
            {
                expFound =
                  raiseException(allowMultipleExceptions,
                                 string("Filed to parse the \"") + aName + "\" attribute value: \"" + aValue + "\"",
                                 ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                 ExceptionHolder::ERROR_EXCEPTION);
            }
        }

        if (!expFound && !TAG_ATTR_INCLUDE_PATH.compare(aName))
        {
            vector<string> paths;
            mstflint::common::algorithm::split(paths, aValue, mstflint::common::algorithm::is_any_of(string(";")));
            adbParser->_adbCtxt->includePaths.insert(adbParser->_adbCtxt->includePaths.end(), paths.begin(),
                                                     paths.end());

            vector<string> relatives;
            string projPath = mstflint::common::filesystem::path(adbParser->_adbCtxt->mainFileName).parent_path().string();

            for (vector<string>::iterator it = adbParser->_adbCtxt->includePaths.begin();
                 it != adbParser->_adbCtxt->includePaths.end();
                 it++)
            {
                if (mstflint::common::filesystem::path(*it).is_relative())
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
        mstflint::common::algorithm::trim(includeAttr);

        bool expFound = false;
        if (includeAttr == "file")
        {
            string fname = attrValue(atts, "file");
            mstflint::common::algorithm::trim(fname);
            if (fname.empty())
            {
                expFound = raiseException(allowMultipleExceptions,
                                          string() + "File attribute isn't given within " + TAG_INCLUDE + " tag",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::FATAL_EXCEPTION);
            }
            if (!expFound)
                includeFile(adbParser, fname, lineNumber);
        }
        else if (includeAttr == "dir")
        {
            string includeAllDirPath = attrValue(atts, "dir");
            mstflint::common::algorithm::trim(includeAllDirPath);
            if (includeAllDirPath.empty())
            {
                expFound = raiseException(allowMultipleExceptions,
                                          string() + "Directory to include isn't given within " + TAG_INCLUDE + " tag",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::FATAL_EXCEPTION);
            }

            if (!expFound)
                includeAllFilesInDir(adbParser, includeAllDirPath, lineNumber);
        }
        else
        {
            expFound = raiseException(allowMultipleExceptions,
                                      string() + "Include is called without file or dir attribute.",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::ERROR_EXCEPTION);
        }
    }
}

void AdbParser::startInstOpAttrReplaceElement(const XML_Char** atts, AdbParser* adbParser, const int lineNumber)
{
    if (!adbParser->_isExprEval)
    {
        return;
    }

    bool expFound = false;
    if (!adbParser->_instanceOps)
    {
        expFound = raiseException(allowMultipleExceptions,
                                  "Operation attr_replace must be defined within <instance_ops> element only.",
                                  ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                  ExceptionHolder::FATAL_EXCEPTION);
    }

    string path = attrValue(atts, "path");
    if (path.empty())
    {
        expFound = raiseException(allowMultipleExceptions,
                                  "path attribute is missing in attr_replace operation",
                                  ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                       ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                       ExceptionHolder::FATAL_EXCEPTION);
    }
    bool cond = is_inst_ifdef_exist_and_correct_project(atts, adbParser);

    if (cond)
    {
        string nodeName = attrValue(atts, "name");
        mstflint::common::algorithm::trim(nodeName);
        string size = attrValue(atts, "size");

        if (adbParser->_enforceGuiChecks)
        {
            // check the node name is compatible with the nname_pattern
            if (!mstflint::common::regex::regex_match(nodeName, mstflint::common::regex::regex(adbParser->_nname_pattern)))
            {
                raiseException(allowMultipleExceptions,
                               "Illegal node name: \"" + nodeName + "\" doesn't match the given node name pattern: \"",
                               adbParser->_nname_pattern + "\", in file: \"" + adbParser->_fileName +
                                 "\" line: " + to_string(lineNumber),
                               ExceptionHolder::WARN_EXCEPTION);
            }
        }

        if (adbParser->_enforceExtraChecks)
        {
            if (!AdbParser::checkSpecialChars(nodeName))
            {
                raiseException(allowMultipleExceptions,
                               "Invalid character in node name, in Node: \"" + nodeName + "\"",
                               ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                               ExceptionHolder::WARN_EXCEPTION);
            }
            if (AdbParser::checkBigger32(size))
            { // the second part of the size after the . max to be 32 0x0.0
                raiseException(allowMultipleExceptions,
                               "Invalid size format, valid format 0x0.0 not allowed to be more than 0x0.31",
                               ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                               ExceptionHolder::WARN_EXCEPTION);
            }
            if (!AdbParser::checkHEXFormat(size))
            {
                raiseException(allowMultipleExceptions,
                               "Invalid size format",
                               ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                               ExceptionHolder::WARN_EXCEPTION);
            }

            if (addr2int(size) == 0)
            {
                raiseException(allowMultipleExceptions,
                               "Node Size is not allowed to be 0, in Node: \"" + nodeName + "\"",
                               ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                               ExceptionHolder::ERROR_EXCEPTION);
            }
        }
        string desc = descXmlToNative(attrValue(atts, "descr"));

        // Check for mandatory attrs
        if (nodeName.empty())
        {
            raiseException(allowMultipleExceptions,
                           "Missing node name",
                           ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                           ExceptionHolder::FATAL_EXCEPTION);
        }
        if (size.empty())
        {
            raiseException(allowMultipleExceptions,
                           "Missing node size",
                           ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                           ExceptionHolder::FATAL_EXCEPTION);
        }
        // Check for duplications
        if (adbParser->_adbCtxt->nodesMap.count(nodeName))
        {
            raiseException(allowMultipleExceptions,
                           "node \"" + nodeName + "\" is already defined in file: \"" +
                             adbParser->_adbCtxt->nodesMap[nodeName]->fileName +
                             "\" line: " + to_string(adbParser->_adbCtxt->nodesMap[nodeName]->lineNumber),
                           ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                           ExceptionHolder::FATAL_EXCEPTION);
        }

        adbParser->_currentNode = new AdbNode;
        adbParser->_currentNode->name = nodeName;
        adbParser->_currentNode->size = addr2int(size);
        adbParser->_currentNode->desc = desc;
        string unionAttrVal = attrValue(atts, "attr_is_union");
        adbParser->_currentNode->isUnion = !unionAttrVal.empty() && stoi(unionAttrVal) != 0;
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
        expFound = raiseException(allowMultipleExceptions,
                                  "Field definition outside of node",
                                  ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                  ExceptionHolder::FATAL_EXCEPTION);
    }

    if (!adbParser->skipNode)
    {
        if (adbParser->_currentField)
        {
            expFound = raiseException(allowMultipleExceptions,
                                      "Nested fields are not allowed",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::FATAL_EXCEPTION);
        }

        string fieldName = attrValue(atts, "name");
        mstflint::common::algorithm::trim(fieldName);
        string offset = attrValue(atts, "offset");
        string size = attrValue(atts, "size");

        if (adbParser->_enforceExtraChecks)
        {
            if (addr2int(size) % 32 == 0 && !AdbParser::checkHEXFormat(size))
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Invalid size format",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::WARN_EXCEPTION);
            }
            if (!AdbParser::checkHEXFormat(offset))
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Invalid offset format",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::WARN_EXCEPTION);
            }
            if (!AdbParser::checkSpecialChars(fieldName))
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Invalid character in field name, in Field: \"" + fieldName + "\"",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::WARN_EXCEPTION);
            }
            if (!expFound && adbParser->_currentNode->isUnion && addr2int(offset) != 0)
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Offset must be 0x0.0 in Union fields",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::WARN_EXCEPTION);
            }
            if (AdbParser::checkBigger32(size))
            { // the second part of the size after the . max to be 32 0x0.0
                expFound = raiseException(allowMultipleExceptions,
                                          "Invalid size format, valid format 0x0.0 not allowed to be more than 0x0.31",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::WARN_EXCEPTION);
            }
            if (AdbParser::checkBigger32(offset))
            { // the second part of the size after the . max to be 32 0x0.0
                expFound =
                  raiseException(allowMultipleExceptions,
                                 "Invalid offset format, valid format 0x0.0 not allowed to be more than 0x0.31",
                                 ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                 ExceptionHolder::WARN_EXCEPTION);
            }
            if (addr2int(size) == 0)
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Field Size is not allowed to be 0, in Field: \"" + fieldName + "\"",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                expFound = raiseException(allowMultipleExceptions,
                                          "Invalid size of array entries",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::ERROR_EXCEPTION);
            }
            if (entrySize < 8 && entrySize != 4 && entrySize != 2 && entrySize != 1 &&
                ((isize > 32 && highBound != "VARIABLE") || highBound == "VARIABLE"))
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Array with entry size 3, 5, 6 or 7 bits and array size is larger than 32bit",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                          ExceptionHolder::ERROR_EXCEPTION);
            }
        }
        else if (adbParser->_enforceGuiChecks && !(lowBound == "" && highBound == ""))
        {
            expFound = raiseException(
              allowMultipleExceptions,
              "Field: \"" + adbParser->_currentField->name + "\": both low_bound or high_bound must be specified",
              ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
              ExceptionHolder::WARN_EXCEPTION);
        }

        string subNode = attrValue(atts, "subnode");

        // Check for mandatory attrs
        if (fieldName.empty())
        {
            expFound = raiseException(allowMultipleExceptions,
                                      "Missing field name",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::FATAL_EXCEPTION);
        }

        if (size.empty())
        {
            expFound = raiseException(allowMultipleExceptions,
                                      "Missing field size",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::FATAL_EXCEPTION);
        }

        // Create new fields
        adbParser->_currentField = new AdbField;

        // Fill the new fields
        adbParser->_currentField->name = fieldName;
        adbParser->_currentField->desc = desc;
        adbParser->_currentField->size = addr2int(size);

        adbParser->_currentField->lowBound = lowBound.empty() ? 0 : stoi(lowBound);
        if (highBound == "VARIABLE")
        {
            adbParser->_currentField->highBound = 0;
            string isDynamicArray = attrValue(atts, "arr_is_dynamic");
            if (!isDynamicArray.empty() && stoi(isDynamicArray))
            {
                adbParser->_currentField->array_type = AdbField::ArrayType::dynamic;
                string conditionalSize = attrValue(atts, "size_condition");
                if (conditionalSize == "")
                {
                    expFound =
                      raiseException(allowMultipleExceptions,
                                     "Missing size_condition attribute",
                                     ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                     ExceptionHolder::FATAL_EXCEPTION);
                }
            }
            else
            {
                adbParser->_currentField->array_type = AdbField::ArrayType::unlimited;
            }
        }
        else if (highBound.empty())
        {
            adbParser->_currentField->highBound = 0;
            adbParser->_currentField->array_type = AdbField::ArrayType::none;
        }
        else
        {
            adbParser->_currentField->highBound = stoi(highBound);
            if (adbParser->_currentField->lowBound == adbParser->_currentField->highBound)
            {
                if (adbParser->_adbCtxt->singleEntryArrSupp)
                {
                    adbParser->_currentField->array_type = AdbField::ArrayType::single_entry;
                }
                else
                {
                    adbParser->_currentField->array_type = AdbField::ArrayType::none;
                }
            }
            else
            {
                adbParser->_currentField->array_type = AdbField::ArrayType::definite;
            }
        }
        adbParser->_currentField->subNode = subNode;

        // Check array element size
        if (adbParser->_currentField->array_type >= AdbField::ArrayType::definite &&
            adbParser->_currentField->array_type < AdbField::ArrayType::unlimited &&
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
            expFound = raiseException(allowMultipleExceptions,
                                      "Fields are not allowed in unions (only subnodes)",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_strict && adbParser->_currentNode->isUnion && adbParser->_currentField->size % 32)
        {
            expFound = raiseException(allowMultipleExceptions,
                                      "Union is allowed to contains only dword aligned subnodes",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_currentNode->isUnion &&
            adbParser->_currentField->size > adbParser->_currentNode->size)
        {
            expFound = raiseException(allowMultipleExceptions,
                                      "Field size is greater than the parent node size",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_strict && !adbParser->_currentField->isArray() &&
            adbParser->_currentField->isLeaf() && adbParser->_currentField->size > 32)
        {
            expFound = raiseException(allowMultipleExceptions,
                                      "Leaf fields can't be > 32 bits",
                                      ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                      ExceptionHolder::FATAL_EXCEPTION);
        }

        if (!expFound && adbParser->_checkDsAlign)
        {
            u_int32_t esize = adbParser->_currentField->eSize();
            if ((adbParser->_currentField->isLeaf() || adbParser->_currentField->subNode == "uint64") &&
                (esize == 16 || esize == 32 || esize == 64) && adbParser->_currentField->offset % esize != 0)
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Field: " + adbParser->_currentField->name +
                                            " in Node: " + adbParser->_currentNode->name + " offset(" +
                                            to_string(adbParser->_currentField->offset) + ") is not aligned to size(" +
                                            to_string(esize) + ")",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                      " in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                      ExceptionHolder::ERROR_EXCEPTION);
                }
            }

            // check if the field name is compatible with the fname pattern
            if (!mstflint::common::regex::regex_match(adbParser->_currentField->name, mstflint::common::regex::regex(adbParser->_fname_pattern)))
            {
                expFound = raiseException(allowMultipleExceptions,
                                          "Illegal field name: \"" + adbParser->_currentField->name +
                                            "\" doesn't match the given field name pattern",
                                          ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                                         ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                         ExceptionHolder::ERROR_EXCEPTION);
                    }

                    if (!aName.compare("enum"))
                    {
                        // check the enum attribute is compatible with the enum pattern
                        if (!mstflint::common::regex::regex_match(aValue, mstflint::common::regex::regex(adbParser->_enum_pattern)))
                        {
                            expFound =
                              raiseException(allowMultipleExceptions,
                                             "Illegal value: \"" + aValue + "\" for attribute: \"" + aName + "\" ",
                                             "doesn't match the given attribute pattern, in file: \"" +
                                               adbParser->_fileName + "\" line: " + to_string(lineNumber),
                                             ExceptionHolder::WARN_EXCEPTION);
                        }
                    }
                    else
                    {
                        // check the attribute name is compatible with the attribute pattern
                        if (adbParser->attr_pattern.find(aName) != adbParser->attr_pattern.end() &&
                            !mstflint::common::regex::regex_match(aValue, mstflint::common::regex::regex(adbParser->attr_pattern[aName])))
                        {
                            expFound =
                              raiseException(allowMultipleExceptions,
                                             "Illegal value: \"" + aValue + "\" for attribute: \"" + aName + "\" ",
                                             "doesn't match the given attribute pattern, in file: \"" +
                                               adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
            exceptionTxt = exceptionTxt + ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber);
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
                std::stable_sort(adbParser->_currentNode->fields.begin(),
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
                                           "\" line: " + to_string(lineNumber);
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
                    u_int32_t effective_node_size = adbParser->_currentNode->size;
                    if (adbParser->_force_pad_32 && effective_node_size < 32 && effective_node_size != 16 &&
                        effective_node_size != 8)
                    {
                        effective_node_size = 32;
                    }

                    long delta = (long)effective_node_size - (long)(prevField->offset + prevField->size);
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
                raiseException(allowMultipleExceptions,
                               "Node: " + adbParser->_currentNode->name + " size(" +
                                 to_string(adbParser->_currentNode->size) + ") is not aligned with largest leaf(" +
                                 to_string(adbParser->_currentNode->_maxLeafSize) + ")",
                               ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber),
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
                std::stable_sort(adbParser->_currentNode->fields.begin(),
                            adbParser->_currentNode->fields.end(),
                            compareFieldsPtr<AdbField>);
            }

            // Add this node to AdbCtxt
            adbParser->_adbCtxt->nodesMap.insert(
              pair<string, AdbNode*>(adbParser->_currentNode->name, adbParser->_currentNode));
            adbParser->_currentNode = 0;
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
                        mstflint::common::algorithm::split(defVal, it_def->second, mstflint::common::algorithm::is_any_of(string("=")));

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
                        mstflint::common::algorithm::split(defVal, it_def->second, mstflint::common::algorithm::is_any_of(string("=")));

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
                        exceptionTxt =
                          exceptionTxt + ", in file: \"" + adbParser->_fileName + "\" line: " + to_string(lineNumber);
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
                                               "\" line: " + to_string(lineNumber);
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
