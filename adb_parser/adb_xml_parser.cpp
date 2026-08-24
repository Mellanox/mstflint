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
#include "common/tools_filesystem.h"
#include "common/tools_regex.h"
#include "common/tools_algorithm.h"

#include <string.h>
#include <iostream>
#include <sstream>

namespace Filesystem = mstflint::common::filesystem;
namespace Regex = mstflint::common::regex;
namespace Algorithm = mstflint::common::algorithm;

/**
 * Function: AdbParser::compareFieldsPtr
 **/

/*************************** AdbParser Implementation ***************************/
/**
 * Function: AdbParser::AdbParser
 **/
template<bool e, typename O>
AdbParser<e, O>::AdbParser(string fileName,
                           Adb* adbCtxt,
                           string root_node_name,
                           bool addReserved,
                           bool strict,
                           string includePath,
                           bool enforceExtraChecks,
                           bool checkDsAlign,
                           bool enforceGuiChecks,
                           bool force_dword_align,
                           bool cd_mode,
                           bool variable_alignment) :
    _adbCtxt(adbCtxt),
    _fileName(fileName),
    _root_node_name(root_node_name),
    _addReserved(addReserved),
    _strict(strict),
    _checkDsAlign(checkDsAlign),
    skipNode(false),
    _support_variable_alignment(variable_alignment || cd_mode),
    _includePath(includePath),
    _currentNode(0),
    _current_node_alignment(32),
    _currentField(0),
    _currentConfig(0),
    _instanceOps(false),
    _nodeOps(false),
    _enforceGuiChecks(enforceGuiChecks),
    _force_dword_align(force_dword_align),
    _cd_mode(cd_mode),
    _nname_pattern(".*"),
    _fname_pattern(".*")
{
    _enforceExtraChecks = enforceExtraChecks;

    // add default patterns
    _nname_pattern = ".*";
    _fname_pattern = ".*";
    _enum_pattern = "\\s*\\w+\\s*=\\s*(0[xX])?[0-9a-fA-F]+\\s*";

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
        Algorithm::split(path, fileName, Algorithm::is_any_of(OS_PATH_SEP));
        // IncludeFileInfo info = {fileName, "ROOT", 0};
        // _adbCtxt->includedFiles[path[path.size() - 1]] = info;

        _adbCtxt->add_include(path[path.size() - 1], fileName, "ROOT", 0);
    }
}

template<bool e, typename O>
void AdbParser<e, O>::addIncludePaths(Adb* adbCtxt, string includePaths)
{
    vector<string> paths;
    Algorithm::split(paths, includePaths, Algorithm::is_any_of(";"));
    adbCtxt->includePaths.insert(adbCtxt->includePaths.end(), paths.begin(), paths.end());

    vector<string> relatives;
    string projPath = Filesystem::path(adbCtxt->mainFileName).parent_path().string();

    for (vector<string>::iterator it = adbCtxt->includePaths.begin(); it != adbCtxt->includePaths.end(); it++)
    {
        if (projPath != "" && projPath != *it && Filesystem::path(*it).is_relative())
        {
            relatives.push_back(projPath + OS_PATH_SEP + *it);
        }
    }

    adbCtxt->includePaths.insert(adbCtxt->includePaths.end(), relatives.begin(), relatives.end());
}

/**
 * Function: AdbParser::~AdbParser
 **/
template<bool e, typename O>
AdbParser<e, O>::~AdbParser()
{
    XML_ParserFree(_xmlParser);
}

/**
 * Function: AdbParser::setAllowMultipleExceptionsTrue
 * This function is a static function to change the value of set all exceptions to true
 **/
template<bool e, typename O>
void AdbParser<e, O>::setAllowMultipleExceptionsTrue()
{
    AdbParser::allowMultipleExceptions = true;
}

/**
 * Function: AdbParser::load
 **/
template<bool e, typename O>
bool AdbParser<e, O>::load(bool is_main)
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
            auto root_node_it = _adbCtxt->nodesMap.find(_root_node_name);
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
        _lastError = exp.what_s();
        if (exp.what_s().find("in file:") == string::npos)
        {
            int line = XML_GetCurrentLineNumber(_xmlParser);
            ExceptionHolder::appendLocationSuffix(_lastError, _fileName, line);
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
    catch (AdbStopException& er)
    {
        free(data);
        return false;
    }
    catch (std::runtime_error& er)
    {
        _lastError = CHECK_RUNTIME_ERROR(er);
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
        _lastError = "An exception raised during the loading of the file";
        ExceptionHolder::appendLocationSuffix(_lastError, _fileName, line);
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
template<bool e, typename O>
bool AdbParser<e, O>::loadFromString(const char* adbString)
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
        _lastError = exp.what_s();
        if (exp.what_s().find("in file:") == string::npos)
        {
            int line = XML_GetCurrentLineNumber(_xmlParser);
            ExceptionHolder::appendLocationSuffix(_lastError, _fileName, line);
        }

        _lastError += string("\nNOTE: this project is configured to work with: \"") +
                      (_adbCtxt->bigEndianArr ? "Big" : "Little") + " Endian Arrays\"";
        return false;
    }
    catch (std::runtime_error& er)
    {
        _lastError = CHECK_RUNTIME_ERROR(er);
        return false;
    }
    catch (...)
    {
        int line = XML_GetCurrentLineNumber(_xmlParser);
        _lastError = "An exception raised during the loading of the file";
        ExceptionHolder::appendLocationSuffix(_lastError, _fileName, line);
        return false;
    }

    return true;
}

/**
 * Function: AdbParser::getError
 **/
template<bool e, typename O>
string AdbParser<e, O>::getError()
{
    return _lastError;
}

/**
 * Function: AdbParser::attrsCount
 **/
template<bool e, typename O>
int AdbParser<e, O>::attrCount(const XML_Char** atts)
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
template<bool e, typename O>
string AdbParser<e, O>::attrValue(const XML_Char** atts, const XML_Char* attrName, AttrsMap* override_attrs)
{
    if (override_attrs)
    {
        auto found_it = override_attrs->find(attrName);
        if (found_it != override_attrs->end())
        {
            return found_it->second;
        }
    }

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
template<bool e, typename O>
bool AdbParser<e, O>::checkAttrExist(const XML_Char** atts, const XML_Char* attrName)
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
template<bool e, typename O>
string AdbParser<e, O>::attrName(const XML_Char** atts, int i)
{
    return string(atts[i * 2]);
}

/**
 * Function: AdbParser::attrName
 **/
template<bool e, typename O>
string AdbParser<e, O>::attrValue(const XML_Char** atts, int i, AttrsMap* override_attrs)
{
    string name = string(atts[i * 2]);
    if (override_attrs)
    {
        auto found_it = override_attrs->find(name);
        if (found_it != override_attrs->end())
        {
            return found_it->second;
        }
    }
    return string(atts[i * 2 + 1]);
}

/**
 * Function: AdbParser::findFile
 **/
template<bool e, typename O>
string AdbParser<e, O>::findFile(string fileName)
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
 * Function: AdbParser::parse_size
 **/
template<bool e, typename T_OFFSET>
bool AdbParser<e, T_OFFSET>::parse_size(const string& s,
                                        T_OFFSET& res,
                                        AdbParser<e, T_OFFSET>* adbParser,
                                        bool size_or_offset,
                                        bool node_or_field)
{
    string attribute_name{size_or_offset ? "size" : "offset"};
    string tag_name{node_or_field ? "node" : "field"};
    int lineNumber = XML_GetCurrentLineNumber(adbParser->_xmlParser);

    bool exception_raised = false;
    string error_message;

    Regex::smatch match;
    // Matches "[0x]H[.D]" — hex bytes (group 1) with optional dot + decimal bits (group 4).
    // Permissive on purpose; edge cases (.D, 0x.D, H.) are caught below.
    static Regex::regex correctHEXExpr("^\\s*((0[xX])?[0-9A-Fa-f]*)(\\.([0-9]*))?\\s*$");
    if (!regex_match(s, match, correctHEXExpr))
    {
        error_message = "Failed parsing " + tag_name + " " + attribute_name + ", " + s + "\", " +
                        "invalid format, valid formats are: \"0xH.D\", \"D.D\", \"0xH\", \".D\".";
        exception_raised = ExceptionHolder::handle_exception(
          allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        res = static_cast<T_OFFSET>(-1);
        return false;
    }

    auto num_bytes_str = match[1].str();
    Algorithm::to_lower(num_bytes_str);

    auto num_bits_str = match[4].str();

    unsigned long long num_bytes = 0;
    unsigned long long num_bits = 0;

    // Catch "0x.5" — bare 0x prefix with no hex digits
    if (num_bytes_str == "0x")
    {
        if (adbParser->_enforceExtraChecks)
        {
            error_message =
              "Invalid format of " + tag_name + "'s " + attribute_name + ", \"" + s + "\". 0x.D is an invalid format";
            exception_raised =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::WARN_EXCEPTION,
                                                adbParser->_fileName, lineNumber);
        }
        num_bytes_str = "0";
    }

    size_t end;
    try
    {
        if (!num_bytes_str.empty())
        {
            num_bytes = stoull(num_bytes_str, &end, 0);
            if (end != num_bytes_str.size())
            {
                throw std::invalid_argument("");
            }
        }
        else
        {
            num_bytes = 0;
        }

        if (!num_bits_str.empty())
        {
            num_bits = stoull(num_bits_str, &end, 10);
            if (end != num_bits_str.size())
            {
                throw std::invalid_argument("");
            }
        }
        else
        {
            num_bits = 0;
        }
    }
    catch (std::invalid_argument&)
    {
        error_message = "Failed parsing " + tag_name + " " + attribute_name + ", " + s + "\", " +
                        "invalid format, valid formats are: \"0xH.D\", \"D.D\", \"0xH\", \".D\".";
        exception_raised = ExceptionHolder::handle_exception(
          allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        res = static_cast<T_OFFSET>(-1);
        return false;
    }
    catch (std::out_of_range&)
    {
        error_message = "Failed parsing " + tag_name + " " + attribute_name + ", " + s + "\", " + "out of range.";
        exception_raised = ExceptionHolder::handle_exception(
          allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        res = static_cast<T_OFFSET>(-1);
        return false;
    }

    if (adbParser->_enforceExtraChecks && !size_or_offset)
    {
        if (num_bytes % 4 != 0)
        {
            error_message = "Failed parsing " + tag_name + " " + attribute_name + ", " + s + ", " +
                            "invalid format, address part must be dword aligned, while given, " + num_bytes_str;
            exception_raised =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::WARN_EXCEPTION,
                                                adbParser->_fileName, lineNumber);
        }

        if (num_bits > 31)
        {
            error_message = "Failed parsing " + tag_name + " " + attribute_name + ", " + s + ", " +
                            "invalid format, offset part must in range [0,31], while given, " + num_bits_str;
            exception_raised =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::WARN_EXCEPTION,
                                                adbParser->_fileName, lineNumber);
        }
    }

    res = num_bytes * 8 + num_bits;
    return !exception_raised;
}

/**
 * Function: AdbParser::dword
 **/
template<bool e, typename T_OFFSET>
T_OFFSET AdbParser<e, T_OFFSET>::aligned_word(T_OFFSET offset, uint8_t alignment)
{
    return offset / alignment;
}

/**
 * Function: AdbParser::startBit
 **/
template<bool e, typename T_OFFSET>
uint32_t AdbParser<e, T_OFFSET>::startBit(T_OFFSET offset, uint8_t alignment)
{
    return offset % alignment;
}

/**
 * Function: AdbParser::descXmlToNative
 **/
template<bool e, typename O>
string AdbParser<e, O>::descXmlToNative(const string& desc)
{
    return Algorithm::replace_all_copy(desc, "\\;", "\n");
}

template<bool e, typename O>
bool AdbParser<e, O>::is_inst_ifdef_exist_and_correct_project(const XML_Char** atts, AdbParser* adbParser)
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
                Algorithm::split(defVal, it_def->second, Algorithm::is_any_of("="));

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
 * Function: AdbParser::includeFile
 **/
template<bool e, typename O>
void AdbParser<e, O>::includeFile(AdbParser* adbParser, string fileName, int lineNumber)
{
    // add this file to the included files map
    string filePath;
    FILE* probeFile = NULL;

    if (!Filesystem::path(fileName).is_relative())
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
    Filesystem::path boostPath(filePath);
    fileName = boostPath.filename().string();

    if (!adbParser->_adbCtxt->includedFiles.count(fileName))
    {
        // IncludeFileInfo info = {filePath, adbParser->_fileName, lineNumber};
        // adbParser->_adbCtxt->includedFiles[fileName] = info;

        adbParser->_adbCtxt->add_include(fileName, filePath, adbParser->_fileName, lineNumber);

        // parse the included file
        AdbParser p(filePath, adbParser->_adbCtxt, adbParser->_root_node_name, adbParser->_addReserved,
                    adbParser->_strict, "", adbParser->_enforceExtraChecks, adbParser->_checkDsAlign,
                    adbParser->_enforceGuiChecks, adbParser->_force_dword_align, adbParser->_cd_mode,
                    adbParser->_support_variable_alignment);
        if (!p.load(false))
        {
            throw AdbException(p.getError());
        }
    }
}

/**
 * Function: AdbParser::includeAllFilesInDir
 **/
template<bool e, typename O>
void AdbParser<e, O>::includeAllFilesInDir(AdbParser* adbParser, string dirPath, int lineNumber)
{
    vector<string> paths;
    Filesystem::path mainFile(adbParser->_fileName);
    Algorithm::split(paths, dirPath, Algorithm::is_any_of(";"));
    for (vector<string>::iterator pathIt = paths.begin(); pathIt != paths.end(); pathIt++)
    {
        // first look in the main file's path
        Filesystem::path fsPath(mainFile.parent_path().string() + "/" + *pathIt);
        if (!Filesystem::exists(fsPath))
        {
            fsPath = Filesystem::path(*pathIt);
        }

        if (Filesystem::exists(fsPath) && Filesystem::is_directory(fsPath))
        {
            addIncludePaths(adbParser->_adbCtxt, *pathIt);
            Filesystem::directory_iterator filesIter(fsPath), dirEnd;
            for (; filesIter != dirEnd; ++filesIter)
            {
                if (Filesystem::is_regular_file(filesIter->status()) && filesIter->path().extension() == ".adb")
                {
                    try
                    {
                        includeFile(adbParser, filesIter->path().string(), lineNumber);
                    }
                    catch (AdbException& er)
                    {
                        throw(er);
                    }
                }
            }
        }
    }
}

/**
 *  Function AdbParser::checkSpecialChars
 *
 *  Validates that a node/field/enum name is a valid C identifier, optionally
 *  followed by an array subscript (e.g. "my_field[3]").
 *  Allowed pattern: [_A-Za-z][_A-Za-z0-9]*  with optional  [<digits>]  suffix.
 */
template<bool e, typename O>
bool AdbParser<e, O>::checkSpecialChars(string tagName)
{
    // Uses explicit character classes instead of \w / \d for POSIX ERE compatibility (USE_STDLIB_REGEX).
    static Regex::regex validNameExpr("[_A-Za-z][_A-Za-z0-9]*(\\[[0-9]+\\])?$");
    Regex::smatch match;
    return !tagName.empty() && Regex::regex_match(tagName, match, validNameExpr);
}

template<bool e, typename O>
void AdbParser<e, O>::startNodesDefElement(const XML_Char** atts, AdbParser<e, O>* adbParser)
{
    if (adbParser->_adbCtxt->version == "")
    {
        if ((attrCount(atts) == 1) && (attrName(atts, 0) == "version"))
        {
            string adbVersion = attrValue(atts, 0);
            if (adbVersion != "1" && adbVersion != "1.0" && adbVersion != "2")
            {
                throw AdbException("Requested _Adb_impl Version (%s) is not supported. Supporting only version 1 or 2",
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

template<bool e, typename O>
void AdbParser<e, O>::startEnumElement(const XML_Char** atts, AdbParser<e, O>* adbParser, const int lineNumber)
{
    bool expFound = false;
    string error_message;
    if (!adbParser->_currentConfig || !adbParser->_currentConfig->attrs.count("type") ||
        TAG_ATTR_ENUM.compare(adbParser->_currentConfig->attrs["type"]))
    {
        error_message = "\"enum\" tag must be inside relevant \"config\" tag";
        expFound = ExceptionHolder::handle_exception(
          allowMultipleExceptions, error_message, ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
    }

    string tagName = attrValue(atts, "name");
    string value = attrValue(atts, "value");
    if (adbParser->_enforceExtraChecks)
    {
        if (!AdbParser::checkSpecialChars(tagName))
        {
            error_message = "Invalid character in enum name, in enum: \"" + tagName + "\"";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::WARN_EXCEPTION,
                                                adbParser->_fileName, lineNumber);
        }
    }
    if (tagName.empty() || value.empty())
    {
        error_message = "Both \"name\" and \"value\" attributes must be specified";
        expFound = ExceptionHolder::handle_exception(
          allowMultipleExceptions, error_message, ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
    }
    if (!expFound)
    {
        adbParser->_currentConfig->enums.insert(pair<string, string>(tagName, value));
    }
}

template<bool e, typename O>
void AdbParser<e, O>::startConfigElement(const XML_Char** atts, AdbParser<e, O>* adbParser, const int lineNumber)
{
    bool expFound = false;
    bool is_field_attribute = false;

    string error_message;

    if (adbParser->_currentConfig)
    {
        error_message = "config tag can't appear within other config";
        expFound = ExceptionHolder::handle_exception(
          allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
    }

    adbParser->_currentConfig = new AdbConfig;
    for (int i = 0; i < attrCount(atts); i++)
    {
        bool is_valid_att = true;
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
                aValue = Regex::regex_replace(aValue, Regex::regex("\\s+"), string(""));
                Algorithm::split(adbParser->field_mand_attr, aValue, Algorithm::is_any_of(","));
            }

            // check the define statement is according to format
            else if (!aName.compare("define"))
            {
                Regex::smatch result;
                static Regex::regex pattern(TAG_ATTR_DEFINE_PATTERN);
                if (!Regex::regex_match(aValue, result, pattern))
                {
                    error_message = "Bad define format: \"" + aName + "\" attribute value: \"" + aValue + "\"";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                                 lineNumber);
                }
                else
                {
                    // check for define duplication
                    string define_key = result[1], define_value = result[2];

                    if (adbParser->_adbCtxt->defines_map.find(define_key) != adbParser->_adbCtxt->defines_map.end())
                    {
                        error_message = "Multiple definition of preprocessor variable: \"" + define_key +
                                        "\" attribute name: \"" + aName + "\"";
                        expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                     ExceptionHolder::ERROR_EXCEPTION,
                                                                     adbParser->_fileName, lineNumber);
                    }
                    else
                    {
                        adbParser->_adbCtxt->defines_map.insert(pair<string, string>(define_key, define_value));
                    }
                }
            }

            else if (!expFound && !aName.compare("field_attr"))
            {
                is_field_attribute = true;
                // check that the field_attr is unique
                if (adbParser->field_attr_names_set.find(aValue) != adbParser->field_attr_names_set.end())
                {
                    error_message = "Redefinition of field_attr: \"" + aName + "\" attribute name: \"" + aValue + "\"";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                                 lineNumber);
                }
                else
                {
                    adbParser->field_attr_names_set.insert(aValue);
                }

                string attr_type = attrValue(atts, "type");
                string field_attr = attrValue(atts, "field_attr");

                // check attr 'type' is configured only when attr 'field_attr' is configured as well
                if (field_attr.empty())
                {
                    error_message = "Attribute \"type\" is supported only for attributes definition \"config\" tag";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::WARN_EXCEPTION, "", lineNumber);
                }

                // check that attr 'type' was provided and not empty
                if (attr_type.empty())
                {
                    error_message = "field_attr type must be specified (not empty): \"" + aName +
                                    "\" attribute value: \"" + aValue + "\"";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                                 lineNumber);
                }
                else
                {
                    // check that type 'multival' has a 'fw_label' value
                    if (!attr_type.compare("multival") && aValue.compare("fw_label"))
                    {
                        error_message = "Type \"multival\" is supported only for \"fw_label\" not for: \"" + aName +
                                        "\" attribute value: \"" + aValue + "\"";
                        expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                     ExceptionHolder::ERROR_EXCEPTION,
                                                                     adbParser->_fileName, lineNumber);
                    }
                }

                string attr_used_for = attrValue(atts, "used_for");

                // check that attr 'used_for' was not provided empty
                if (checkAttrExist(atts, "used_for") && attr_used_for.empty())
                {
                    error_message = "used_for is invalid: \"" + aName + "\" attribute value: \"" + aValue + "\"";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                                 lineNumber);
                }

                // check if 'pattern' was provided
                if (checkAttrExist(atts, "pattern"))
                {
                    // check if the given pattern is a valid reg expression.
                    try
                    {
                        string pattern_value = attrValue(atts, "pattern");
                        static Regex::regex r(pattern_value);
                        adbParser->attr_pattern.insert(pair<string, string>(aValue, pattern_value));
                    }
                    catch (...)
                    {
                        error_message = "Bad attribute pattern: \"" + aValue + "\" name Pattern: \"" +
                                        attrValue(atts, "pattern") + "\"";
                        expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                     ExceptionHolder::ERROR_EXCEPTION,
                                                                     adbParser->_fileName, lineNumber);
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
                    static Regex::regex r(nname_pattern);
                    adbParser->_nname_pattern = nname_pattern;
                }
                catch (...)
                {
                    error_message =
                      "Bad node name pattern: \"" + aValue + "\" pattern: \"" + attrValue(atts, "nname_pattern") + "\"";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                                 lineNumber);
                }
            }

            // check if fname_pattern was provided and the name of the field is compatible with that pattern
            else if (!expFound && checkAttrExist(atts, "fname_pattern"))
            {
                // check if the given pattern is a valid reg expression.
                try
                {
                    string fname_pattern = attrValue(atts, "fname_pattern");
                    static Regex::regex r(fname_pattern);
                    adbParser->_fname_pattern = fname_pattern;
                }
                catch (...)
                {
                    error_message = "Bad field name pattern: \"" + aValue + "\" pattern: \"" +
                                    attrValue(atts, "fname_pattern") + "\"";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                                 lineNumber);
                }
            }
            else if (!aName.compare("type") or !aName.compare("used_for") or !aName.compare("pattern"))
            {
                if (!is_field_attribute)
                {
                    error_message =
                      "Attribute \"" + aName + "\" is supported only for field_attr definition in \"config\" tag";
                    ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                      ExceptionHolder::WARN_EXCEPTION, adbParser->_fileName,
                                                      lineNumber);
                }
            }
            else if (aName.compare("sw_export") and aName.compare("disable_exports"))
            {
                is_valid_att = false;
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
                error_message = "Filed to parse the \"" + aName + "\" attribute value: \"" + aValue + "\"";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }

        else if (!TAG_ATTR_SINGLE_ENTRY_ARR.compare(aName))
        {
            try
            {
                int val = stoi(aValue);
                adbParser->_adbCtxt->singleEntryArrSupp = val != 0;
            }
            catch (std::exception&)
            {
                error_message = "Filed to parse the \"" + aName + "\" attribute value: \"" + aValue + "\"";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }

        else if (!expFound && !TAG_ATTR_INCLUDE_PATH.compare(aName))
        {
            vector<string> paths;
            Algorithm::split(paths, aValue, Algorithm::is_any_of(";"));
            adbParser->_adbCtxt->includePaths.insert(adbParser->_adbCtxt->includePaths.end(), paths.begin(),
                                                     paths.end());

            vector<string> relatives;
            string projPath = Filesystem::path(adbParser->_adbCtxt->mainFileName).parent_path().string();

            for (vector<string>::iterator it = adbParser->_adbCtxt->includePaths.begin();
                 it != adbParser->_adbCtxt->includePaths.end();
                 it++)
            {
                if (Filesystem::path(*it).is_relative())
                {
                    relatives.push_back(projPath + OS_PATH_SEP + *it);
                }
            }

            adbParser->_adbCtxt->includePaths.insert(adbParser->_adbCtxt->includePaths.end(), relatives.begin(),
                                                     relatives.end());
        }
        else if (!is_valid_att)
        {
            error_message = "Attribute \"" + aName + "\" for config tag is not supported.";
            ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::WARN_EXCEPTION,
                                              adbParser->_fileName, lineNumber);
        }
    }
}

template<bool e, typename O>
void AdbParser<e, O>::startInfoElement(const XML_Char** atts, AdbParser<e, O>* adbParser)
{
    string docName = attrValue(atts, "source_doc_name");
    string docVer = attrValue(atts, "source_doc_version");
    adbParser->_adbCtxt->srcDocName = docName;
    adbParser->_adbCtxt->srcDocVer = docVer;
}

template<bool e, typename O>
void AdbParser<e, O>::startIncludeElement(const XML_Char** atts, AdbParser<e, O>* adbParser, const int lineNumber)
{
    bool cond = is_inst_ifdef_exist_and_correct_project(atts, adbParser);
    if (cond)
    {
        string includeAttr = attrName(atts, 0);
        Algorithm::trim(includeAttr);

        bool expFound = false;
        string error_message;
        if (includeAttr == "file")
        {
            string fname = attrValue(atts, "file");
            Algorithm::trim(fname);
            if (fname.empty())
            {
                error_message = "File attribute isn't given within " + TAG_INCLUDE + " tag";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
            }
            if (!expFound)
                includeFile(adbParser, fname, lineNumber);
        }
        else if (includeAttr == "dir")
        {
            string includeAllDirPath = attrValue(atts, "dir");
            Algorithm::trim(includeAllDirPath);
            if (includeAllDirPath.empty())
            {
                error_message = "Directory to include isn't given within " + TAG_INCLUDE + " tag";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
            }

            if (!expFound)
                includeAllFilesInDir(adbParser, includeAllDirPath, lineNumber);
        }
        else
        {
            error_message = "Include is called without file or dir attribute.";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
        }
    }
}

template<bool e, typename O>
void AdbParser<e, O>::startAttrReplaceElement(const XML_Char** atts,
                                              AdbParser<e, O>* adbParser,
                                              const int lineNumber,
                                              bool instance)
{
    string path = attrValue(atts, "path");
    if (path.empty())
    {
        string message = "path attribute is missing in attr_replace operation";
        ExceptionHolder::handle_exception(allowMultipleExceptions, message, ExceptionHolder::ERROR_EXCEPTION,
                                          adbParser->_fileName, lineNumber);
        return;
    }

    auto& path_attrs_map = instance ? adbParser->_adbCtxt->instAttrs : adbParser->_adbCtxt->nodeAttrs;
    path_attrs_map[path] = AttrsMap();
    for (int i = 0; i < attrCount(atts); i++)
    {
        string attrN = attrName(atts, i);
        if (attrN == "path")
        {
            continue;
        }

        string attrV = attrValue(atts, i);
        path_attrs_map[path][attrN] = attrV;
    }
}

template<bool e, typename T_OFFSET>
void AdbParser<e, T_OFFSET>::startNodeElement(const XML_Char** atts,
                                              AdbParser<e, T_OFFSET>* adbParser,
                                              const int lineNumber)
{
    string error_message;
    if (adbParser->_currentNode || adbParser->skipNode)
    {
        error_message = "Nested nodes are not allowed";
        ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION,
                                          adbParser->_fileName, lineNumber);
    }
    bool cond = is_inst_ifdef_exist_and_correct_project(atts, adbParser);

    if (cond)
    {
        string nodeName = attrValue(atts, "name");

        AttrsMap* override_attrs{nullptr};

        auto replace_attrs_it = adbParser->_adbCtxt->nodeAttrs.find(nodeName);
        if (replace_attrs_it != adbParser->_adbCtxt->nodeAttrs.end())
        {
            override_attrs = &(replace_attrs_it->second);
        }

        Algorithm::trim(nodeName);

        if (adbParser->_enforceGuiChecks)
        {
            // check the node name is compatible with the nname_pattern
            if (!Regex::regex_match(nodeName, Regex::regex(adbParser->_nname_pattern)))
            {
                error_message = "Illegal node name: \"" + nodeName +
                                "\" doesn't match the given node name pattern: \"" + adbParser->_nname_pattern + "\"";
                ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                  ExceptionHolder::WARN_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }

        string size = attrValue(atts, "size", override_attrs);
        T_OFFSET node_size = 0;
        parse_size(size, node_size, adbParser, true, true);
        if (node_size == 0)
        {
            error_message = "Node size is not allowed to be 0, in Node: \"" + nodeName + "\"";
            ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION,
                                              adbParser->_fileName, lineNumber);
        }

        if (adbParser->_enforceExtraChecks)
        {
            if (!AdbParser::checkSpecialChars(nodeName))
            {
                error_message = "Invalid character in node name, in Node: \"" + nodeName + "\"";
                ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                  ExceptionHolder::WARN_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }
        string desc = descXmlToNative(attrValue(atts, "descr", override_attrs));

        // Check for mandatory attrs
        if (nodeName.empty())
        {
            error_message = "Missing node name";
            ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION,
                                              adbParser->_fileName, lineNumber);
        }
        // Check for duplications
        if (adbParser->_adbCtxt->nodesMap.count(nodeName))
        {
            error_message = "node \"" + nodeName + "\" is already defined";
            ExceptionHolder::appendLocationSuffix(error_message, adbParser->_adbCtxt->nodesMap[nodeName]->fileName,
                                                  adbParser->_adbCtxt->nodesMap[nodeName]->lineNumber);
            ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION,
                                              adbParser->_fileName, lineNumber);
        }

        string unionAttrVal = attrValue(atts, "attr_is_union", override_attrs);
        auto is_union = !unionAttrVal.empty() && stoi(unionAttrVal) != 0;

        adbParser->_currentNode =
          AdbNode::create_AdbNode(nodeName, node_size, is_union, desc, adbParser->_fileName, lineNumber);

        if (adbParser->_strict && adbParser->_currentNode->isUnion && adbParser->_currentNode->get_size() % 32)
        {
            // throw AdbException("union must be dword aligned");
        }

        if (adbParser->_support_variable_alignment && attrValue(atts, "cr_data_wdt", override_attrs) == "64")
        {
            adbParser->_current_node_alignment = 64;
        }
        else
        {
            adbParser->_current_node_alignment = 32;
        }

        // Add all node attributes
        for (int i = 0; i < attrCount(atts); i++)
        {
            auto val = attrValue(atts, i, override_attrs);
            if (val == "")
            {
                continue;
            }
            adbParser->_currentNode->attrs[attrName(atts, i)] = val;
        }
    }
    else
    {
        adbParser->skipNode = true;
    }
}

template<bool e, typename T_OFFSET>
void AdbParser<e, T_OFFSET>::startFieldElement(const XML_Char** atts,
                                               AdbParser<e, T_OFFSET>* adbParser,
                                               const int lineNumber)
{
    bool expFound = false;
    bool invalid_size = false;
    bool invalid_offset = false;
    bool default_offset = false;

    string error_message;

    if (!adbParser->_currentNode && !adbParser->skipNode)
    {
        error_message = "Field definition outside of node";
        expFound = ExceptionHolder::handle_exception(
          allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
    }

    if (!adbParser->skipNode)
    {
        if (adbParser->_currentField)
        {
            error_message = "Nested fields are not allowed";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        }

        string fieldName = attrValue(atts, "name");
        Algorithm::trim(fieldName);

        string nodeName = adbParser->_currentNode->name;

        AttrsMap* override_attrs{nullptr};

        auto replace_attrs_it = adbParser->_adbCtxt->nodeAttrs.find(nodeName + "." + fieldName);
        if (replace_attrs_it != adbParser->_adbCtxt->nodeAttrs.end())
        {
            override_attrs = &(replace_attrs_it->second);
        }

        string offset = attrValue(atts, "offset", override_attrs);
        string size = attrValue(atts, "size", override_attrs);

        T_OFFSET field_size = 0;

        expFound = !parse_size(size, field_size, adbParser, true, false);
        invalid_size = field_size == static_cast<T_OFFSET>(-1);

        if (field_size == 0)
        {
            error_message = "Missing or zero field size, in field: \"" + fieldName + "\"";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
            invalid_size = true;
        }

        Algorithm::trim(offset);
        if (offset.empty())
        {
            default_offset = true;
        }

        T_OFFSET field_offset = 0;
        if (!default_offset)
        {
            expFound = expFound || !parse_size(offset, field_offset, adbParser, false, false);
        }
        invalid_offset = field_offset == static_cast<T_OFFSET>(-1);

        if (adbParser->_enforceExtraChecks)
        {
            if (!AdbParser::checkSpecialChars(fieldName))
            {
                error_message = "Invalid character in field name, in Field: \"" + fieldName + "\"";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::WARN_EXCEPTION, adbParser->_fileName, lineNumber);
            }
            if (!expFound && adbParser->_currentNode->isUnion && !default_offset && field_offset != 0)
            {
                error_message = "Offset must be 0x0.0 in Union fields";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }

        string desc = descXmlToNative(attrValue(atts, "descr", override_attrs));
        string lowBound = attrValue(atts, "low_bound", override_attrs);
        string highBound = attrValue(atts, "high_bound", override_attrs);

        if (!invalid_size && lowBound != "" && highBound != "")
        {
            int low = atoi(lowBound.c_str());
            int high = 0;
            if (highBound != "VARIABLE")
            {
                high = atoi(highBound.c_str());
            }
            T_OFFSET entrySize = field_size / (high - low + 1);
            if (entrySize % 8 != 0 && entrySize > 8)
            {
                error_message = "Invalid size of array entries";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
            }
            if (entrySize < 8 && entrySize != 4 && entrySize != 2 && entrySize != 1 &&
                ((field_size > 32 && highBound != "VARIABLE") || highBound == "VARIABLE"))
            {
                error_message = "Array with entry size 3, 5, 6 or 7 bits and array size is larger than 32bit";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }
        else if (adbParser->_enforceGuiChecks && (lowBound != "" || highBound != ""))
        {
            error_message =
              "Field: \"" + adbParser->_currentField->name + "\": both low_bound or high_bound must be specified";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::WARN_EXCEPTION,
                                                adbParser->_fileName, lineNumber);
        }

        string subNode = attrValue(atts, "subnode", override_attrs);

        // Check for mandatory attrs
        if (fieldName.empty())
        {
            error_message = "Missing field name";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        }

        // Create new fields
        adbParser->_currentField =
          AdbField::create_AdbField(fieldName, static_cast<T_OFFSET>(-1), field_size, false, subNode, desc);

        adbParser->_currentField->lowBound = lowBound.empty() ? 0 : stoi(lowBound);
        if (highBound == "VARIABLE")
        {
            adbParser->_currentField->highBound = 0;
            string size_condition_str = attrValue(atts, "size_condition", override_attrs);
            if (!size_condition_str.empty())
            {
                adbParser->_currentField->array_type = AdbField::ArrayType::dynamic;
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

        if ((invalid_size || invalid_offset) && adbParser->allowMultipleExceptions)
        {
            throw AdbStopException();
        }

        // Check array element size
        if (adbParser->_currentField->array_type >= AdbField::ArrayType::definite &&
            adbParser->_currentField->array_type < AdbField::ArrayType::unlimited &&
            adbParser->_currentField->get_size() % (adbParser->_currentField->arrayLen()))
        {
            std::stringstream ss;
            ss << "In field \"" << fieldName << "\" invalid array element size \""
               << adbParser->_currentField->get_size() << "/" << adbParser->_currentField->arrayLen() << "\"";

            error_message = ss.str();
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        }
        if (default_offset)
        {
            if (adbParser->_currentNode->fields.empty())
            {
                adbParser->_currentField->offset = 0;
            }
            else
            {
                AdbField* lastField = adbParser->_currentNode->fields.back();
                adbParser->_currentField->offset = lastField->offset + lastField->get_size();
            }
        }
        else
        {
            adbParser->_currentField->offset = field_offset;
        }

        // Very tricky but works well for big endian arrays support - on endElement we will fix the address again
        if (!expFound && adbParser->_adbCtxt->bigEndianArr && adbParser->_current_node_alignment != 64)
        {
            T_OFFSET offset = adbParser->_currentField->offset;
            T_OFFSET size = adbParser->_currentField->eSize();

            adbParser->_currentField->offset =
              ((offset >> 5) << 5) + ((MIN(32, adbParser->_currentNode->get_size()) - ((offset + size) % 32)) % 32);
        }

        // workaround for 64bit registers (flip every two adjacent 32b dwords)
        if (adbParser->_current_node_alignment == 64 && adbParser->_currentField->get_size() <= 32)
        {
            T_OFFSET offset = adbParser->_currentField->offset;

            uint8_t in_dword_offset = offset % 32;
            offset = ((offset >> 5) << 5) xor 32;
            adbParser->_currentField->offset = offset + in_dword_offset;
        }

        // Check that field doesn't extend beyond parent node's end
        if (adbParser->_enforceGuiChecks && !expFound &&
            adbParser->_currentField->offset + adbParser->_currentField->get_size() >
              adbParser->_currentNode->get_size())
        {
            error_message = "Node: " + adbParser->_currentNode->name + " size(" +
                            to_string(adbParser->_currentNode->get_size()) + ") - field (" +
                            adbParser->_currentField->name + ") continue over the node's end";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
        }

        // For DS alignment check
        adbParser->_currentNode->update_max_leaf(adbParser->_currentField);

        if (!expFound && adbParser->_strict && adbParser->_currentNode->isUnion && adbParser->_currentField->isLeaf())
        {
            error_message = "Fields are not allowed in unions (only subnodes)";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        }

        if (!expFound && adbParser->_strict && adbParser->_currentNode->isUnion &&
            adbParser->_currentField->get_size() % 32)
        {
            error_message = "Union is allowed to contains only dword aligned subnodes";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        }

        if (!expFound && adbParser->_currentNode->isUnion &&
            adbParser->_currentField->get_size() > adbParser->_currentNode->get_size())
        {
            error_message = "Field size is greater than the parent node size";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        }

        if (!expFound && adbParser->_strict && !adbParser->_currentField->isArray() &&
            adbParser->_currentField->isLeaf() && adbParser->_currentField->get_size() > 32)
        {
            error_message = "Leaf fields can't be > 32 bits";
            expFound =
              ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
        }

        if (!expFound && adbParser->_checkDsAlign)
        {
            T_OFFSET esize = adbParser->_currentField->eSize();
            if ((adbParser->_currentField->isLeaf() || adbParser->_currentField->subNode == "uint64") &&
                (esize == 16 || esize == 32 || esize == 64) && adbParser->_currentField->offset % esize != 0)
            {
                error_message = "Field: " + adbParser->_currentField->name +
                                " in Node: " + adbParser->_currentNode->name + " offset(" +
                                to_string(adbParser->_currentField->offset) + ") is not aligned to size(" +
                                to_string(esize) + ")";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }

        if (adbParser->_enforceGuiChecks)
        {
            // check if all mandatory attributes were supplied
            for (unsigned int i = 0; i < adbParser->field_mand_attr.size(); i++)
            {
                if (!checkAttrExist(atts, adbParser->field_mand_attr[i].c_str()))
                {
                    error_message = "Atrribute: \"" + adbParser->field_mand_attr[i] + "\" for field must be specified.";
                    expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                 ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                                 lineNumber);
                }
            }

            // check if the field name is compatible with the fname pattern
            if (!Regex::regex_match(adbParser->_currentField->name, Regex::regex(adbParser->_fname_pattern)))
            {
                error_message = "Illegal field name: \"" + adbParser->_currentField->name +
                                "\" doesn't match the given field name pattern";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::WARN_EXCEPTION, adbParser->_fileName, lineNumber);
            }

            // check if the field inside a union is an array
            if (!expFound && adbParser->_currentNode->isUnion && adbParser->_currentField->isArray())
            {
                error_message = "Arrays are not allowed in unions (only subnodes)";
                expFound =
                  ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                    ExceptionHolder::FATAL_EXCEPTION, adbParser->_fileName, lineNumber);
            }
        }

        // Add all field attributes
        if (!expFound)
        {
            for (int i = 0; i < attrCount(atts); i++)
            {
                string aName = attrName(atts, i);
                string aValue = attrValue(atts, i, override_attrs);
                if (adbParser->_enforceGuiChecks)
                {
                    // check if the field contains illegal attribute
                    if (!aName.compare("inst_if") && !aName.compare("inst_ifdef") && !aName.compare("subnode") &&
                        adbParser->field_attr_names_set.find(aName) != adbParser->field_attr_names_set.end() &&
                        adbParser->field_spec_attr.find(aName) != adbParser->field_spec_attr.end())
                    {
                        error_message = "Unknown attribute: " + aName + " at field: " + adbParser->_currentField->name;
                        expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                     ExceptionHolder::ERROR_EXCEPTION,
                                                                     adbParser->_fileName, lineNumber);
                    }

                    if (!aName.compare("enum"))
                    {
                        // check the enum attribute is compatible with the enum pattern
                        vector<string> enum_entries;
                        if (aValue[aValue.length() - 1] == ',')
                        {
                            aValue = aValue.substr(0, aValue.length() - 1);
                        }
                        Algorithm::split(enum_entries, aValue, Algorithm::is_any_of(","));
                        for (const auto& entry : enum_entries)
                        {
                            if (!Regex::regex_match(entry, Regex::regex(adbParser->_enum_pattern)))
                            {
                                error_message = "Illegal value: \"" + aValue + "\" for attribute: \"" + aName +
                                                "\" doesn't match the given attribute pattern";
                                expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                             ExceptionHolder::ERROR_EXCEPTION,
                                                                             adbParser->_fileName, lineNumber);
                            }
                        }
                    }
                    else
                    {
                        // check the attribute name is compatible with the attribute pattern
                        if (adbParser->attr_pattern.find(aName) != adbParser->attr_pattern.end() &&
                            !Regex::regex_match(aValue, Regex::regex(adbParser->attr_pattern[aName])))
                        {
                            error_message = "Illegal value: \"" + aValue + "\" for attribute: \"" + aName +
                                            "\" doesn't match the given attribute pattern";
                            expFound = ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                                         ExceptionHolder::WARN_EXCEPTION,
                                                                         adbParser->_fileName, lineNumber);
                        }
                    }
                }
                adbParser->_currentField->attrs[aName] = aValue;
            }
        }
    }
}

/**
 * Function: AdbParser::startElement
 **/
template<bool e, typename O>
void AdbParser<e, O>::startElement(void* _adbParser, const XML_Char* name, const XML_Char** atts)
{
    AdbParser<e, O>* adbParser = static_cast<AdbParser<e, O>*>(_adbParser);

    int lineNumber = XML_GetCurrentLineNumber(adbParser->_xmlParser);
    adbParser->_currentTagValue = "";

    string error_message;

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
    else if (TAG_NODE_OPS == name)
    {
        adbParser->_nodeOps = true;
    }
    else if (TAG_ATTR_REPLACE == name)
    {
        if (adbParser->_instanceOps)
        {
            startAttrReplaceElement(atts, adbParser, lineNumber);
        }
        else if (adbParser->_nodeOps)
        {
            startAttrReplaceElement(atts, adbParser, lineNumber, false);
        }
        else
        {
            error_message = "Operation attr_replace must be defined within <instance_ops> element only.";
            ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION,
                                              adbParser->_fileName, lineNumber);
        }
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
        error_message = "Unsupported tag: " + string(name);
        ExceptionHolder::handle_exception(allowMultipleExceptions, error_message, ExceptionHolder::FATAL_EXCEPTION,
                                          adbParser->_fileName, lineNumber);
        return;
    }
}

/**
 * Function: AdbParser::addReserved
 **/
template<bool e, typename T_OFFSET>
void AdbParser<e, T_OFFSET>::addReserved(vector<AdbField*>& reserveds, T_OFFSET offset, T_OFFSET size, uint8_t alignment)
{
    T_OFFSET word_span = (aligned_word(offset + size - 1, alignment) - aligned_word(offset, alignment)) + 1;

    // printf("==> %s\n", formatAddr(offset, size).c_str());
    // printf("word_span = %d\n", word_span);
    bool start_aligned = (offset % alignment) == 0;
    bool end_aligned = ((offset + size) % alignment) == 0;
    bool full_words = start_aligned && end_aligned;

    if (word_span == 1 || full_words)
    {
        AdbField* f1 = AdbField::create_AdbField("reserved", offset, size, true);
        if (alignment == 64)
        {
            f1->attrs["cr_data_wdt"] = "64";
        }

        reserveds.push_back(f1);
        // printf("case1: reserved0: %s\n", formatAddr(f1->offset, f1->size).c_str());
    }
    else if (word_span == 2) // Partial words
    {
        AdbField* f1 = AdbField::create_AdbField("reserved", offset, alignment - startBit(offset, alignment), true);
        AdbField* f2 = AdbField::create_AdbField("reserved", aligned_word(offset + alignment, alignment) * alignment,
                                                 size - f1->get_size(), true);

        reserveds.push_back(f1);
        reserveds.push_back(f2);
        /*printf("case2: reserved0: %s, reserved1: %s\n",
         formatAddr(f1->offset, f1->size).c_str(),
         formatAddr(f2->offset, f2->size).c_str());*/
        if (alignment == 64)
        {
            f1->attrs["cr_data_wdt"] = "64";
            f2->attrs["cr_data_wdt"] = "64";
        }
    }
    else // more than two partial words
    {
        T_OFFSET offset_first = offset;
        T_OFFSET size_first = 0;

        T_OFFSET offset_middle = 0;
        T_OFFSET size_middle = 0;

        T_OFFSET offset_end = 0;
        T_OFFSET size_end = 0;

        if (start_aligned && !end_aligned)
        {
            size_first = (word_span - 1) * alignment;
            size_end = size - size_first;
        }
        else if (!start_aligned && end_aligned)
        {
            size_end = (word_span - 1) * alignment;
            size_first = size - size_end;
        }
        else // start and end not aligned
        {
            size_first = alignment - startBit(offset, alignment);
            size_middle = (word_span - 2) * alignment;
            size_end = size - (size_first + size_middle);
        }

        if (!size_middle)
        {
            offset_end = offset + size_first;
        }
        else
        {
            offset_middle = offset + size_first;
            offset_end = offset + (size_first + size_middle);
        }

        AdbField* reserved_first = AdbField::create_AdbField("reserved", offset_first, size_first, true);
        reserveds.push_back(reserved_first);
        if (alignment == 64)
        {
            reserved_first->attrs["cr_data_wdt"] = "64";
        }

        if (size_middle)
        {
            AdbField* reserved_middle = AdbField::create_AdbField("reserved", offset_middle, size_middle, true);
            reserveds.push_back(reserved_middle);
            if (alignment == 64)
            {
                reserved_middle->attrs["cr_data_wdt"] = "64";
            }
        }

        AdbField* reserved_last = AdbField::create_AdbField("reserved", offset_end, size_end, true);
        reserveds.push_back(reserved_last);
        if (alignment == 64)
        {
            reserved_last->attrs["cr_data_wdt"] = "64";
        }
    }
}

/**
 * Function: AdbParser::endElement
 **/
template<bool e, typename T_OFFSET>
void AdbParser<e, T_OFFSET>::endElement(void* _adbParser, const XML_Char* name)
{
    AdbParser<e, T_OFFSET>* adbParser = static_cast<AdbParser<e, T_OFFSET>*>(_adbParser);
    int lineNumber = XML_GetCurrentLineNumber(adbParser->_xmlParser);
    string error_message;
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
     * Node Operations
     * ----
     */
    else if (TAG_NODE_OPS == name)
    {
        adbParser->_nodeOps = false;
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
            AdbField dummy_field;
            dummy_field.offset = 0; // used as a trivial field to prevent iteration overflow
            dummy_field.set_size(0);
            AdbField* prevField = &dummy_field;
            AdbField* prevprevField = &dummy_field;
            if (!adbParser->_currentNode->isUnion)
            {
                if (adbParser->_cd_mode)
                {
                    vector<AdbField*> processed_fields;
                    for (auto field : adbParser->_currentNode->fields)
                    {
                        auto found_broken = field->attrs.find("broken32");
                        auto found_broken_prev = prevField->attrs.find("broken32");

                        auto broken = found_broken != field->attrs.end() && found_broken->second == "1";
                        auto broken_prev =
                          found_broken_prev != prevField->attrs.end() && found_broken_prev->second == "1";
                        auto same_qword = adbParser->_current_node_alignment > 32 &&
                                          field->offset / adbParser->_current_node_alignment ==
                                            prevField->offset / adbParser->_current_node_alignment;

                        if (!same_qword && broken_prev)
                        {
                            prevField->reformat_name_bitspan(*prevprevField, *field);
                        }
                        if (!broken || !broken_prev || !same_qword)
                        {
                            processed_fields.push_back(field);
                            prevprevField = prevField;
                            prevField = field;
                        }
                        else
                        {
                            auto current_broken_series = processed_fields.back();
                            current_broken_series->merge_broken(*field);

                            if (adbParser->_currentNode->_max_leaf == field)
                            {
                                adbParser->_currentNode->_max_leaf = current_broken_series;
                            }
                            delete field;
                        }
                    }
                    if (processed_fields.size() > 0)
                    {
                        AdbField& prev_for_reformat =
                          processed_fields.size() > 1 ? *(processed_fields[processed_fields.size() - 2]) : dummy_field;
                        AdbField& next_for_reformat = dummy_field;
                        processed_fields.back()->reformat_name_bitspan(prev_for_reformat, next_for_reformat);
                    }

                    adbParser->_currentNode->fields = processed_fields;
                    prevField = &dummy_field;
                }

                for (auto field : adbParser->_currentNode->fields)
                {
                    if (prevField->offset + prevField->get_size() > field->offset)
                    { // Overlapping
                        error_message = "Field: " + field->name + " " + formatAddr(field->offset, field->get_size()) +
                                        " overlaps with Field: " + prevField->name + " " +
                                        formatAddr(prevField->offset, prevField->get_size());
                        ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                          ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                          lineNumber);
                    }
                    T_OFFSET delta = field->offset - (prevField->offset + prevField->get_size());
                    if (delta > 0 && adbParser->_addReserved)
                    { // Need reserved
                        addReserved(reserveds, prevField->offset + prevField->get_size(), delta,
                                    adbParser->_current_node_alignment);
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
                    addReserved(reserveds, 0, adbParser->_currentNode->get_size(), adbParser->_current_node_alignment);
                }
                else
                {
                    T_OFFSET effective_node_size = adbParser->_currentNode->get_size();

                    // In Chip-Design mode force pad to 32 bit
                    if (adbParser->_force_dword_align && effective_node_size < 32 && effective_node_size != 16 &&
                        effective_node_size != 8)
                    {
                        effective_node_size = 32;
                    }

                    long delta = (long)effective_node_size - (long)(prevField->offset + prevField->get_size());
                    /*if (adbParser->_currentNode->name == "miss_machine_slice_info")
                    {
                    printf("Adding filler\n");
                    printf("node offs: %s, prevField: %s\n", formatAddr(0, adbParser->_currentNode->size).c_str(),
                    formatAddr(prevField->offset, prevField->size).c_str());
                    printf("delta: %ld\n", delta);
                    }*/

                    if (delta > 0)
                    {
                        addReserved(reserveds, prevField->offset + prevField->get_size(), delta,
                                    adbParser->_current_node_alignment);
                    }
                }

                adbParser->_currentNode->fields.insert(adbParser->_currentNode->fields.end(), reserveds.begin(),
                                                       reserveds.end());
            }

            auto max_leaf_size = adbParser->_currentNode->get_max_leaf_size();
            if (adbParser->_checkDsAlign && max_leaf_size != 0 &&
                adbParser->_currentNode->get_size() % max_leaf_size != 0)
            {
                error_message = "Node: " + adbParser->_currentNode->name + " size(" +
                                to_string(adbParser->_currentNode->get_size()) + ") is not aligned with largest leaf(" +
                                to_string(max_leaf_size) + ")";
                ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                  ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName, lineNumber);
            }

            // Re-fix fields offset
            if (adbParser->_adbCtxt->bigEndianArr && adbParser->_current_node_alignment != 64)
            {
                for (size_t i = 0; i < adbParser->_currentNode->fields.size(); i++)
                {
                    T_OFFSET offset = adbParser->_currentNode->fields[i]->offset;
                    T_OFFSET size = adbParser->_currentNode->fields[i]->eSize();

                    adbParser->_currentNode->fields[i]->offset =
                      ((offset >> 5) << 5) +
                      ((MIN(32, adbParser->_currentNode->get_size()) - ((offset + size) % 32)) % 32);
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
            if (adbParser->_currentNode->name == adbParser->_root_node_name)
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
                        Algorithm::split(defVal, it_def->second, Algorithm::is_any_of("="));

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
                        Algorithm::split(defVal, it_def->second, Algorithm::is_any_of("="));

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

                uint64_t res;
                adbExpr.setVars(&vars);
                int status = adbExpr.expr(&exp, &res);
                delete[] expOrg;
                string statusStr;

                if (status < 0)
                {
                    error_message =
                      "Error evaluating expression \"" + it->second + "\" : " + AdbExpr::statusStr(status);
                    ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                      ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                      lineNumber);
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
                            error_message = "The field \"" + adbParser->_currentField->name + "\" isn't unique in node";
                            ExceptionHolder::handle_exception(allowMultipleExceptions, error_message,
                                                              ExceptionHolder::ERROR_EXCEPTION, adbParser->_fileName,
                                                              lineNumber);
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

template class AdbParser<false, uint32_t>;
template class AdbParser<false, uint64_t>;

template class AdbParser<true, uint32_t>;
template class AdbParser<true, uint64_t>;
