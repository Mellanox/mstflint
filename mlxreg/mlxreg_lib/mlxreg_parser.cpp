/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include "mlxreg_parser.h"

#include <sstream>
#include <iostream>
#include <common/bit_slice.h>
#include <common/tools_utils.h>
#include <errno.h>
#include <adb_parser/adb_instance.h>
#include <mtcr.h>

using namespace mlxreg;

/************************************
 * Function: RegParser
 ************************************/
template<bool dynamic>
_RegAccessParser_impl<dynamic>::_RegAccessParser_impl(string data,
                                                      string indexes,
                                                      string ops,
                                                      Adb* adb,
                                                      AdbInstance* regNode,
                                                      std::vector<u_int32_t> buffer,
                                                      bool ignore_ro,
                                                      bool full_path)
{
    _data = data;
    _indexes = indexes;
    _ops = ops;
    _adb = adb;
    _regNode = regNode;
    _ignore_ro = ignore_ro;
    _full_path = full_path;
    output_file = "";
    if (!regNode)
    {
        _parseMode = Pm_Unknown;
    }
    else
    {
        _parseMode = Pm_Known;
    }
    _len = buffer.size();
    _buffer = buffer;
    /*
     * Initiate byte-swapping
     * At this point we know the the buffer <buffer> argument already been trough byte-
     * swapping process, we need to re-commit this process so the data will be correct.
     */
    for (typename std::vector<u_int32_t>::size_type j = 0; j < _buffer.size(); j++)
    {
        _buffer[j] = CPU_TO_BE32((_buffer[j]));
    }
}
/************************************
 * Function: RegParser
 ************************************/
template<bool dynamic>
_RegAccessParser_impl<dynamic>::_RegAccessParser_impl(string data,
                                                      string indexes,
                                                      string ops,
                                                      Adb* adb,
                                                      AdbInstance* regNode,
                                                      u_int32_t len,
                                                      bool ignore_ro,
                                                      bool full_path)
{
    _data = data;
    _indexes = indexes;
    _ops = ops;
    _adb = adb;
    _regNode = regNode;
    _ignore_ro = ignore_ro;
    _full_path = full_path;
    output_file = "";
    _len = len;
    // Set parsing method
    if (!regNode)
    {
        if (_len > MAX_REG_SIZE)
        {
            throw MlxRegException("Register length: 0x%08x is too large", _len);
        }
        _parseMode = Pm_Unknown;
        _len = (_len + 3) / 4;
    }
    else
    {
        _parseMode = Pm_Known;

        _len = _regNode->containsDynamicArray() ? len >> 2 : (_regNode->get_size()) >> 5;
    }
    // Resize buffer
    _buffer.resize(_len);
}

/************************************
 * Function: parse
 ************************************/
template<bool dynamic>
std::vector<u_int32_t> _RegAccessParser_impl<dynamic>::genBuff()
{
    if (_parseMode == Pm_Known)
    {
        return genBuffKnown();
    }
    else
    {
        return genBuffUnknown();
    }
}

/************************************
 * Function: genBuffKnown
 ************************************/
template<bool dynamic>
std::vector<u_int32_t> _RegAccessParser_impl<dynamic>::genBuffKnown()
{
    parseIndexes();
    parseOps();

    // Update buffer with data values
    if (_data != "")
    {
        parseData();
    }
    // Convert to BE32
    for (typename std::vector<u_int32_t>::size_type j = 0; j < _buffer.size(); j++)
    {
        _buffer[j] = CPU_TO_BE32((_buffer[j]));
    }
    return _buffer;
}

/************************************
 * Function: genBuffUnknown
 ************************************/
template<bool dynamic>
std::vector<u_int32_t> _RegAccessParser_impl<dynamic>::genBuffUnknown()
{
    parseUnknown();
    // Convert to BE32
    for (typename std::vector<u_int32_t>::size_type j = 0; j < _buffer.size(); j++)
    {
        _buffer[j] = CPU_TO_BE32((_buffer[j]));
    }
    return _buffer;
}

/************************************
 * Function: parseIndexes
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::parseIndexes()
{
    std::vector<string> tokens = strSplit(_indexes, ',', false);
    std::vector<string> valid_tokens = getAllIndexes(_regNode);
    parseAccessType(tokens, valid_tokens, INDEX);
}

/************************************
 * Function: parseOps
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::parseOps()
{
    std::vector<string> tokens = strSplit(_ops, ',', false);
    std::vector<string> valid_tokens = getAllOps(_regNode);
    parseAccessType(tokens, valid_tokens, OP);
}

/************************************
 * Function: accessTypeToString
 ************************************/
template<bool dynamic>
const string _RegAccessParser_impl<dynamic>::accessTypeToString(access_type_t accessType)
{
    static map<access_type_t, string> access_type_map;
    if (access_type_map.size() == 0)
    {
        access_type_map.insert(pair<access_type_t, string>(INDEX, "INDEX"));
        access_type_map.insert(pair<access_type_t, string>(OP, "OP"));
    }
    typename map<access_type_t, string>::iterator itr = access_type_map.find(accessType);
    if (itr != access_type_map.end())
    {
        return itr->second;
    }
    return string("Unknown"); // should not get here
}

/************************************
 * Function: parseAccessType
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::parseAccessType(std::vector<string> tokens,
                                                     std::vector<string> validTokens,
                                                     access_type_t accessType)
{
    std::vector<string> foundTokens;

    // Update buffer with values (indexes/ops)
    for (typename std::vector<std::string>::size_type i = 0; i != tokens.size(); i++)
    {
        std::vector<std::string> tokenPair = strSplit(tokens[i], '=', true);
        string name = tokenPair[0];
        string val = tokenPair[1];
        u_int32_t uintVal;
        strToUint32((char*)val.c_str(), uintVal);
        AdbInstance* field = getField(name);
        // Make sure that the given field name is valid
        if (std::find(validTokens.begin(), validTokens.end(), name) != validTokens.end())
        {
            if (std::find(foundTokens.begin(), foundTokens.end(), name) != foundTokens.end())
            {
                throw MlxRegException("Field: %s appears twice.", name.c_str());
            }
            foundTokens.push_back(name);
        }
        else
        {
            throw MlxRegException("Field: %s is not a %s.", name.c_str(), this->accessTypeToString(accessType).c_str());
        }
        updateBuffer(field->offset, field->get_size(), uintVal);
    }

    // Per #4207832, skip checking that all indexes are set
    // if (accessType == INDEX)
    // {
    //     // Make sure that all the indexes are set
    //     for (std::vector<std::string>::size_type i = 0; i != validTokens.size(); i++)
    //     {
    //         bool idxFound = false;
    //         for (std::vector<std::string>::size_type j = 0; j != foundTokens.size(); j++)
    //         {
    //             if (validTokens[i] == foundTokens[j])
    //             {
    //                 idxFound = true;
    //             }
    //         }
    //         if (!idxFound)
    //         {
    //             throw MlxRegException("Index: %s was not provided", validTokens[i].c_str());
    //         }
    //     }
    // }
}

template<bool dynamic>
void _RegAccessParser_impl<dynamic>::_on_traverse_update_buffer(const string& calculated_path,
                                                                uint64_t calculated_offset,
                                                                uint64_t calculated_value,
                                                                AdbInstance* instance,
                                                                void* context)
{
    (void)context;
    (void)calculated_value;

    _RegAccessParser_impl<dynamic>* parser = (_RegAccessParser_impl<dynamic>*)context;
    string path_to_compare = parser->_full_path ? calculated_path : get_legacy_path(*instance);

    for (const auto& entry : parser->_data_map)
    {
        const string& key = entry.first;
        const uint32_t value = entry.second;
        if (path_to_compare.length() >= key.length() &&
            path_to_compare.substr(path_to_compare.length() - key.length()) == key &&
            (path_to_compare.length() == key.length() ||
             path_to_compare[path_to_compare.length() - key.length() - 1] == '.'))
        {
            if (!parser->_ignore_ro && instance->is_ro())
            {
                throw MlxRegException("Field: %s is ReadOnly", calculated_path.c_str());
            }
            parser->updateBuffer((uint32_t)calculated_offset, (uint32_t)instance->get_size(), value);
            parser->_data_map.erase(key);
            break;
        }
    }
}
/************************************
 * Function: parseData
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::parseData()
{
    std::vector<string> datTokens = strSplit(_data, ',', false);
    // Update buffer with data values
    for (typename std::vector<std::string>::size_type i = 0; i != datTokens.size(); i++)
    {
        std::vector<std::string> dat = strSplit(datTokens[i], '=', true);
        string datName = dat[0];
        string datVal = dat[1];
        u_int32_t uintVal;
        strToUint32((char*)datVal.c_str(), uintVal);
        _data_map[datName] = uintVal;
    }

    _adb->traverse_layout(_regNode,
                          "",
                          0,
                          (uint8_t*)&(_buffer[0]),
                          _buffer.size() * sizeof(uint32_t),
                          _RegAccessParser_impl<dynamic>::_on_traverse_update_buffer,
                          (void*)this,
                          false,
                          false,
                          _full_path);
    if (_data_map.size() > 0)
        {
        auto unfound_name = _data_map.begin()->first; // for backward compatibility, only prints one unfound name
        throw MlxRegException("Can't find field name: \"%s\"", unfound_name.c_str());
    }
}

/************************************
 * Function: parseUnknown
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::parseUnknown()
{
    // Split input strings
    std::vector<string> idxTokens = strSplit(_indexes, ',', false);
    updateBufferUnknwon(idxTokens);
    if (_data != "")
    {
        std::vector<string> datTokens = strSplit(_data, ',', false);
        updateBufferUnknwon(datTokens);
    }
}

/************************************
 * Function: updateBuffer
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::updateBuffer(u_int32_t offset, u_int32_t size, u_int32_t val)
{
    _buffer[offset >> 5] = MERGE(_buffer[offset >> 5], val, (offset % 32), size);
}

/************************************
 * Function: updateBufferUnknown
 *
 * Raw Data/Indexes Pattern is:
 * Address.Offset:Size=Data
 * Where:
 * Address: In bytes (DWORD aligned).
 * Offset:  In bits within the address.
 * Size:    In bits.
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::updateBufferUnknwon(std::vector<string> fieldTokens)
{
    // Parse fields
    for (typename std::vector<std::string>::size_type i = 0; i != fieldTokens.size(); i++)
    {
        std::vector<std::string> fieldToken = strSplit(fieldTokens[i], '=', true);
        // extract <data>
        u_int32_t fieldDataUint;
        string fieldDataStr = fieldToken[1];
        strToUint32((char*)fieldDataStr.c_str(), fieldDataUint);
        // <Address>.<Offset>:<size>
        string fieldPropStr = fieldToken[0];
        std::vector<std::string> fieldPropVec = strSplit(fieldPropStr, ':', true);
        // extract <size>
        u_int32_t fieldSizeUint;
        string fieldSizeStr = fieldPropVec[1];
        strToUint32((char*)fieldSizeStr.c_str(), fieldSizeUint);
        // validate <size>
        if (fieldSizeUint > 32)
        {
            throw MlxRegException("Invalid size: %d. max size = 32 (bits)", fieldSizeUint);
        }
        // extract <address> <offset>
        string fieldLocStr = fieldPropVec[0];
        std::vector<std::string> fieldLocVec = strSplit(fieldLocStr, '.', true);
        // extract <address>
        u_int32_t fieldAddrUint;
        string fieldAddrStr = fieldLocVec[0];
        strToUint32((char*)fieldAddrStr.c_str(), fieldAddrUint);
        // extract <offset>
        u_int32_t fieldOffsetUint;
        string fieldOffsetStr = fieldLocVec[1];
        strToUint32((char*)fieldOffsetStr.c_str(), fieldOffsetUint);
        // validation
        // Address out of range
        if (fieldAddrUint > (_buffer.size() << 2))
        {
            throw MlxRegException("Address: 0x%08x is out of range", fieldOffsetUint);
        }
        // Address not 4 bytes aligned
        if (fieldAddrUint % 0x4 != 0)
        {
            throw MlxRegException("Address: 0x%08x is not 4-bytes aligned", fieldOffsetUint);
        }
        // offset + size out of address range
        if ((fieldOffsetUint + fieldSizeUint) > 32)
        {
            throw MlxRegException("Offset: %d and Size: %d is out of address range", fieldOffsetUint, fieldSizeUint);
        }
        // Update buffer
        u_int32_t val = _buffer[fieldAddrUint >> 2];
        val = MERGE(val, fieldDataUint, fieldOffsetUint, fieldSizeUint);
        _buffer[fieldAddrUint >> 2] = val;
    }
}

/************************************
 * Function: strSplit
 ************************************/
template<bool dynamic>
std::vector<string> _RegAccessParser_impl<dynamic>::strSplit(string str, char delimiter, bool forcePairs)
{
    std::vector<string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;
    while (getline(ss, tok, delimiter))
    {
        internal.push_back((const string)tok);
    }
    // Vector must contain <key-values> otherwise it's invalid.
    if (forcePairs)
    {
        if (internal.size() != 2)
        {
            throw MlxRegException("Argument: %s is invalid", str.c_str());
        }
    }
    // Can't have an empty key/value
    for (typename std::vector<string>::size_type i = 0; i != internal.size(); i++)
    {
        if (internal[i].length() == 0)
        {
            throw MlxRegException("Argument: %s is invalid", str.c_str());
        }
    }
    return internal;
}

/************************************
 * Function: strToUint32
 ************************************/
template<bool dynamic>
void _RegAccessParser_impl<dynamic>::strToUint32(char* str, u_int32_t& uint)
{
    char* endp;
    errno = 0;
    uint = strtoul(str, &endp, 0);
    if (*endp || errno == ERANGE)
    {
        throw MlxRegException("Argument: %s is invalid.", str);
    }
    if (str[0] == '-')
    {
        throw MlxRegException("Argument: %s is invalid. It must be non-negative.", str);
    }
    return;
}

/************************************
 * Function: getFieldWithParents
 ************************************/
template<bool dynamic>
bool _RegAccessParser_impl<dynamic>::checkFieldWithPath(AdbInstance* field,
                                                        u_int32_t idx,
                                                        std::vector<string>& fieldsChain,
                                                        u_int32_t size,
                                                        u_int32_t offset,
                                                        bool offsetSpecified)
{
    if (idx == 0 && (field->get_field_name() == fieldsChain[0]))
    {
        if (size == 0 || (!offsetSpecified && size && field->get_size() == size) ||
            (offsetSpecified && offset % 32 == field->offset % 32 && size && field->get_size() == size))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (field->get_field_name() == fieldsChain[idx])
    {
        return checkFieldWithPath(field->parent, --idx, fieldsChain);
    }
    else
    {
        return false;
    }
}
/************************************
 * Function: getField
 ************************************/
template<bool dynamic>
typename _RegAccessParser_impl<dynamic>::AdbInstance* _RegAccessParser_impl<dynamic>::getField(string name,
                                                                                               u_int32_t size,
                                                                                               u_int32_t offset,
                                                                                               bool offsetSpecified,
                                                                                               bool is_buffer_full)
{
    // this will allow to access the leaf field by specifying it's parent.
    std::vector<string> fieldsChain = strSplit(name, '.', false);
    std::vector<AdbInstance*> subItems;

    if (!is_buffer_full)
    {
        subItems = _regNode->getLeafFields(true);
    }
    else
    {
        subItems = _RegAccessParser_impl<dynamic>::getRelevantFields(
          _regNode, _buffer); // todo: refactor this function to  use traverse instead of getRelevantFields
    }

    for (typename std::vector<AdbInstance*>::size_type i = 0; i != subItems.size(); i++)
    {
        if (checkFieldWithPath(subItems[i], fieldsChain.size() - 1, fieldsChain, size, offset, offsetSpecified))
        {
            return subItems[i];
        }
    }
    throw MlxRegException("Can't find field name: \"%s\"", name.c_str());
}

template<bool dynamic>
string _RegAccessParser_impl<dynamic>::getAccess(const AdbInstance* field)
{
    string access = field->getInstanceAttr("access");
    if (access.empty())
    {
        access = "N/A";
        if (field->parent)
        {
            access = getAccess(field->parent);
        }
    }
    return access;
}

template<bool dynamic>
bool _RegAccessParser_impl<dynamic>::checkAccess(const AdbInstance* field, const string accessStr)
{
    return getAccess(field) == accessStr;
}

template<bool dynamic>
bool _RegAccessParser_impl<dynamic>::isRO(AdbInstance* field)
{
    if (_ignore_ro)
    {
        return false;
    }
    return checkAccess(field, "RO");
}

template<bool dynamic>
bool _RegAccessParser_impl<dynamic>::isIndex(AdbInstance* field)
{
    return checkAccess(field, "INDEX");
}

template<bool dynamic>
bool _RegAccessParser_impl<dynamic>::isOP(AdbInstance* field)
{
    return checkAccess(field, "OP");
}

/************************************
 * Function: getAllIndexes
 ************************************/
template<bool dynamic>
std::vector<string> _RegAccessParser_impl<dynamic>::getAllIndexes(AdbInstance* node)
{
    std::vector<string> indexes;
    std::vector<AdbInstance*> subItems = node->getLeafFields(true);
    for (typename std::vector<AdbInstance*>::size_type i = 0; i != subItems.size(); i++)
    {
        if (isIndex(subItems[i]))
        {
            indexes.push_back(subItems[i]->get_field_name());
        }
    }
    return indexes;
}

template<bool dynamic>
std::vector<string> _RegAccessParser_impl<dynamic>::getAllOps(AdbInstance* node)
{
    std::vector<string> ops;
    std::vector<AdbInstance*> subItems = node->getLeafFields(true);
    for (typename std::vector<AdbInstance*>::size_type i = 0; i != subItems.size(); i++)
    {
        if (isOP(subItems[i]))
        {
            ops.push_back(subItems[i]->get_field_name());
        }
    }
    return ops;
}

template<bool dynamic>
void _RegAccessParser_impl<dynamic>::updateField(string field_name, u_int32_t value)
{
    AdbInstance* field = getField(field_name);
    updateBuffer(field->offset, field->get_size(), value);
}

template<bool dynamic>
u_int32_t _RegAccessParser_impl<dynamic>::getFieldValue(string field_name,
                                                        std::vector<u_int32_t>& buff,
                                                        u_int32_t size,
                                                        u_int32_t offset,
                                                        bool offsetSpecified,
                                                        bool is_buffer_full)
{
    AdbInstance* field = getField(field_name, size, offset, offsetSpecified, is_buffer_full);
    return (u_int32_t)field->popBuf((u_int8_t*)&buff[0]);
}

/************************************
 * Function: getRelevantFields
 * Description: Traverses ADB instance tree and returns relevant leaf fields.
 * For union selectors and conditional nodes, only returns the selected union field or the node based on buffer value.
 ************************************/
template<bool dynamic>
std::vector<typename _RegAccessParser_impl<dynamic>::AdbInstance*>
  _RegAccessParser_impl<dynamic>::getRelevantFields(typename _RegAccessParser_impl<dynamic>::AdbInstance* node,
                                                    const std::vector<u_int32_t>& buff)
{
    std::vector<AdbInstance*> result;

    if (!node)
    {
        return result;
    }

    // If this is a leaf node (no children), add it to result
    if (node->subItems.empty())
    {
        result.push_back(node);
        return result;
    }

    // Check if this is a union selector
    if (node->isUnion() && node->unionSelector)
    { // TODO: add isUnionSelector() function to AdbInstance
        // Get the selector value from buffer
        u_int32_t selectorValue = node->unionSelector->popBuf((u_int8_t*)&buff[0]);

        // Get the selected union field using getUnionSelectedNodeName
        AdbInstance* selectedNode = nullptr;
        try
        {
            selectedNode = node->getUnionSelectedNodeName(selectorValue);
        }
        catch (const AdbException& e)
        {
            // If getUnionSelectedNodeName throws an exception, treat as a regular non-union node
            // and process all children
            std::cerr << "-W- Field - " << node->get_field_name()
                      << " with union selector failed treating as regular node and processing all children\n"
                      << e.what() << std::endl;
            for (typename std::vector<AdbInstance*>::const_iterator it = node->subItems.begin();
                 it != node->subItems.end();
                 ++it)
            {
                std::vector<AdbInstance*> subResult = getRelevantFields(*it, buff);
                result.insert(result.end(), subResult.begin(), subResult.end());
            }
            return result;
        }

        if (selectedNode)
        {
            // Recursively get relevant fields from the selected union field
            std::vector<AdbInstance*> subResult = getRelevantFields(selectedNode, buff);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }
    else if (node->parent && node->parent->isConditionalNode())
    {
        AdbCondition* condition = node->getCondition();
        if (condition)
        {
            uint64_t cond_val = 0;
            try
            {
                cond_val = condition->evaluate((u_int8_t*)&buff[0]);
            }
            catch (const AdbException& e)
            {
                // If condition evaluation throws an exception, treat as a regular non-union node
                // and process all children
                std::cerr << "-W- Field - " << node->get_field_name()
                          << " with condition, evaluation failed, treating as regular node and processing all children\n"
                          << e.what() << std::endl;
                for (typename std::vector<AdbInstance*>::const_iterator it = node->subItems.begin();
                     it != node->subItems.end();
                     ++it)
                {
                    std::vector<AdbInstance*> subResult = getRelevantFields(*it, buff);
                    result.insert(result.end(), subResult.begin(), subResult.end());
                }
                return result;
            }

            if (!cond_val)
            {
                return result;
            }
        }
        // Recursively get relevant fields from the selected union field
        for (typename std::vector<AdbInstance*>::const_iterator it = node->subItems.begin(); it != node->subItems.end();
             ++it)
        {
            std::vector<AdbInstance*> subResult = getRelevantFields(*it, buff);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }
    else
    {
        // For non-union nodes, recursively process all children
        for (typename std::vector<AdbInstance*>::const_iterator it = node->subItems.begin(); it != node->subItems.end();
             ++it)
        {
            std::vector<AdbInstance*> subResult = getRelevantFields(*it, buff);
            result.insert(result.end(), subResult.begin(), subResult.end());
        }
    }

    return result;
}

/************************************
 * Function: get_legacy_path
 ************************************/
template<bool dynamic>
string _RegAccessParser_impl<dynamic>::get_legacy_path(AdbInstance& instance)
{
    string path = instance.fullName(1);
    size_t last_dot = path.rfind('.');
    string parent_path = (last_dot != string::npos) ? path.substr(0, last_dot) : "";

    if (instance.parent->fieldDesc && instance.parent->fieldDesc->subNode == "uint64")
    {
        path = parent_path + "_" + instance.fieldDesc->name;
    }
    else
    {
        if (path[path.length() - 1] != ']')
        {
            path = parent_path + "." + instance.fieldDesc->name +
                   _AdbInstance_impl<true, uint32_t>::addPathSuffixForArraySupport(path);
        }
    }
    return path;
}

// Explicit template instantiations
namespace mlxreg
{
template class _RegAccessParser_impl<false>;
template class _RegAccessParser_impl<true>;
} // namespace mlxreg
