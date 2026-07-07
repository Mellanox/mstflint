/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *
 */
#include <iostream>
#include "mft_sdk/mft_sdk_reg_access.h"
#include "mlxreg_sdk.h"
#include "prm_reg_sdk.h"
#include "adb_parser/buf_ops.h"
#include "mlxreg/mlxreg_lib/mlxreg_parser.h"
#include "common/compatibility.h"

MstPrmAccessType convertRegisterAccessType(const std::string& access)
{
    if (access == "RO")
    {
        return MST_PRM_ACCESS_RO;
    }
    else if (access == "WO")
    {
        return MST_PRM_ACCESS_WO;
    }
    else if (access == "RW")
    {
        return MST_PRM_ACCESS_RW;
    }
    else if (access == "INDEX")
    {
        return MST_PRM_ACCESS_INDEX;
    }
    else if (access == "OP")
    {
        return MST_PRM_ACCESS_OP;
    }
    else
    {
        return MST_PRM_ACCESS_UNKNOWN;
    }
}

bool _getNodeFieldsCallback(const std::string& calculated_path,
                            uint64_t calculated_offset,
                            uint64_t calculated_value,
                            AdbInstanceAdvLegacy* instance,
                            void* context)
{
    (void)calculated_path;
    (void)calculated_offset;
    (void)calculated_value;

    vector<AdbInstanceAdvLegacy*>* fields = (vector<AdbInstanceAdvLegacy*>*)context;
    fields->push_back(instance);

    return false; // continue traversal
}

PrmRegSdk::PrmRegSdk(const char* mstDev, const char* regName, const uint32_t method, const char* params)
{
    _mlxRegLib = nullptr;
    _mf = nullptr;
    _mstDevStr = std::string(mstDev);
    _regName = std::string(regName);
    _regId = (uint16_t)-1;
    _method = method;
    _paramsStr = std::string(params);
    _response_box_used = false;
    _isExternal = true;
}

PrmRegSdk::PrmRegSdk(const char* mstDev, uint16_t regId, const uint32_t method)
{
    _mlxRegLib = nullptr;
    _mf = nullptr;
    _mstDevStr = std::string(mstDev);
    _regName = "";
    _regId = regId;
    _method = method;
    _paramsStr = "";
    _response_box_used = false;
    _isExternal = true;
}

PrmRegSdk::PrmRegSdk(const char* mst_dev)
{
    _mlxRegLib = nullptr;
    _mf = nullptr;
    _mstDevStr = std::string(mst_dev);
    _regName = "";
    _regId = 0;
    _method = 0;
    _paramsStr = "";
    _response_box_used = false;
    _isExternal = true;
}

PrmRegSdk::~PrmRegSdk()
{
    if (_mlxRegLib)
    {
        delete _mlxRegLib;
    }
    if (_mf)
    {
        mclose(_mf);
    }
}

void PrmRegSdk::initPrmCommand(const char* reg_name, const uint32_t method, const char* params)
{
    _regName = std::string(reg_name);
    _method = method;
    _paramsStr = std::string(params);
}

void PrmRegSdk::initPrmCommand(const uint16_t reg_id, const uint32_t method)
{
    _regId = reg_id;
    _method = method;
}

uint32_t PrmRegSdk::strToUint32(const std::string& strInt, int& rc)
{
    char* endp;
    errno = 0;
    rc = 0;
    char* cstrInt = (char*)strInt.c_str();
    uint32_t uint = strtoul(cstrInt, &endp, 0);
    if (*endp || errno == ERANGE || cstrInt[0] == '-')
    {
        rc = ERR_CODE_INVALID_FIELD_ARG;
    }

    return uint;
}

std::vector<std::string> PrmRegSdk::strSplit(const std::string& str, const char delimiter, bool forcePairs, int& rc)
{
    rc = 0;
    string tmpStr = str;
    std::vector<string> internal;
    std::stringstream ss(tmpStr);
    std::string tok;
    while (getline(ss, tok, delimiter))
    {
        internal.push_back((const string)tok);
    }
    if (forcePairs)
    {
        if (internal.size() != 2)
        {
            rc = ERR_CODE_FAILD_TO_PARSE_PARAMS;
            return internal;
        }
    }

    for (std::vector<string>::size_type i = 0; i != internal.size(); i++)
    {
        if (internal[i].length() == 0)
        {
            rc = ERR_CODE_FAILD_TO_PARSE_PARAMS;
            break;
        }
    }
    return internal;
}

std::map<std::string, uint32_t> PrmRegSdk::parseRegParams(const std::string& paramsStr)
{
    std::map<std::string, uint32_t> params;

    if (!paramsStr.empty())
    {
        int rc = 0;

        std::vector<string> datTokens = strSplit(paramsStr, ',', false, rc);
        if (!rc)
        {
            for (auto token : datTokens)
            {
                auto field = strSplit(token, '=', true, rc);
                if (rc)
                {
                    params.clear();
                    break;
                }
                params.insert(std::pair<std::string, uint32_t>(field[0], strToUint32(field[1], rc)));
                if (rc)
                {
                    params.clear();
                    break;
                }
            }
        }
    }
    return params;
}

void PrmRegSdk::updateBuffer(uint32_t offset, uint32_t size, uint32_t val, std::vector<uint32_t>& buffer)
{
    buffer[offset >> 5] = MERGE(buffer[offset >> 5], val, (offset % 32), size);
}

uint32_t
  PrmRegSdk::extractFromBuffer(uint32_t offset, uint32_t size, std::vector<uint32_t>& buffer, bool small_entry_array)
{
    small_entry_array = small_entry_array && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);
    uint32_t offset_in_dword = offset % 32;
    uint32_t extract_offset = small_entry_array ? 32 - (size + offset_in_dword) : offset_in_dword;
    return EXTRACT(buffer[offset >> 5], extract_offset % 32, size);
}

bool PrmRegSdk::checkFieldWithPath(void* adbInstanceField, uint32_t idx, std::vector<std::string>& fieldsChain)
{
    AdbInstanceAdvLegacy* field = static_cast<AdbInstanceAdvLegacy*>(adbInstanceField);

    if (idx == 0 && (field->get_field_name() == fieldsChain[0]))
    {
        return true;
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

void* PrmRegSdk::getField(const std::string& name, void* regNode)
{
    // this will allow to access the leaf field by specifying it's parent.
    int rc = 0;
    std::vector<string> fieldsChain = strSplit(name, '.', false, rc);

    if (!rc)
    {
        std::vector<AdbInstanceAdvLegacy*> subItems = static_cast<AdbInstanceAdvLegacy*>(regNode)->getLeafFields(true);
        for (std::vector<AdbInstanceAdvLegacy*>::size_type i = 0; i != subItems.size(); i++)
        {
            if (checkFieldWithPath(subItems[i], fieldsChain.size() - 1, fieldsChain))
            {
                return subItems[i];
            }
        }
    }

    return nullptr;
}

std::string PrmRegSdk::getAccess(const void* field)
{
    std::string access = static_cast<const AdbInstanceAdvLegacy*>(field)->getInstanceAttr("access");
    if (access.empty())
    {
        access = "N/A";
        if (static_cast<const AdbInstanceAdvLegacy*>(field)->parent)
        {
            access = getAccess(static_cast<const AdbInstanceAdvLegacy*>(field)->parent);
        }
    }
    return access;
}

uint32_t PrmRegSdk::getNodeFields(AdbInstanceAdvLegacy* regNode,
                                  std::vector<AdbInstanceAdvLegacy*>& fields,
                                  const uint8_t* buffer = nullptr,
                                  uint32_t buffer_size = 0)
{
    uint32_t rc = 0;
    if (!_mlxRegLib)
    {
        rc = initRegLib();
    }
    if (rc != 0)
    {
        return rc;
    }
    if (!regNode)
    {
        rc = ERR_CODE_FAILD_TO_FIND_REG_NODE;
    }
    else
    {
        // Pass buffer so that we traverse only the right nodes
        regNode->traverse_layout("", 0, buffer, buffer_size, _getNodeFieldsCallback, &fields, buffer != nullptr, false);
    }
    return rc;
}

int PrmRegSdk::fillBuffWithParams(void* regNode,
                                  std::map<std::string, uint32_t>& params,
                                  std::vector<uint32_t>& buffer,
                                  bool fillIndexesOnly)
{
    int rc = 0;

    // convert to CPU
    for (std::vector<uint32_t>::size_type j = 0; j < buffer.size(); j++)
    {
        buffer[j] = __be32_to_cpu((buffer[j]));
    }

    for (const auto& pair : params)
    {
        AdbInstanceAdvLegacy* field = static_cast<AdbInstanceAdvLegacy*>(getField(pair.first, regNode));
        if (field)
        {
            if (fillIndexesOnly)
            {
                if (getAccess(field) == "INDEX")
                {
                    updateBuffer(field->offset, field->get_size(), pair.second, buffer);
                }
            }
            else
            {
                updateBuffer(field->offset, field->get_size(), pair.second, buffer);
            }
        }
        else
        {
            rc = ERR_CODE_FAILD_TO_PARSE_FIELD;
            break;
        }
    }

    if (!rc)
    {
        // Convert to BE32
        for (std::vector<uint32_t>::size_type j = 0; j < buffer.size(); j++)
        {
            buffer[j] = CPU_TO_BE32((buffer[j]));
        }
    }

    return rc;
}

std::vector<uint32_t> PrmRegSdk::genarateBuffer(void* regNode, uint32_t size)
{
    std::vector<uint32_t> buffer;

    uint32_t len = size != 0 ? size >> 2 : (static_cast<AdbInstanceAdvLegacy*>(regNode)->get_size()) >> 5;
    buffer.resize(len);

    for (std::vector<uint32_t>::size_type j = 0; j < len; j++)
    {
        buffer[j] = 0;
    }

    return buffer;
}

int32_t PrmRegSdk::initRegLib()
{
    char* externalAdbPath = getenv(EXTERNAL_ADB_PATH);
    string externalAdbPathStr = "";

    _mf = mopen(_mstDevStr.c_str());
    if (!_mf)
    {
        return ERR_CODE_FAILD_TO_OPEN_MST_DEV;
    }

    if (externalAdbPath != nullptr)
    {
        externalAdbPathStr = string(externalAdbPath);
    }
    try
    {
        _mlxRegLib = new mlxreg::MlxRegLib(_mf, externalAdbPathStr, _isExternal);
    }
    catch (exception& exc)
    {
        setErrorMessage(exc.what());
        return ERR_CODE_FAILD_TO_INIT_REG_LIB;
    }
    return 0;
}

int32_t PrmRegSdk::ensureRegLibInitialized()
{
    if (!_mlxRegLib)
    {
        return initRegLib();
    }
    return 0;
}

int32_t PrmRegSdk::processRegisterMethod(AdbInstanceAdvLegacy* regNode,
                                         const std::string& regName,
                                         std::map<std::string, uint32_t>& params,
                                         std::vector<uint32_t>& buffer,
                                         std::vector<uint32_t>& bufferOfSet)
{
    int32_t rc = 0;
    mlxreg::MlxRegLibStatus reg_status = mlxreg::MRLS_SUCCESS;

    switch ((access_type)_method)
    {
        case GET:
        case SET:
            rc = fillBuffWithParams((void*)regNode, params, buffer, false);
            bufferOfSet = buffer;
            break;
        case SET_READ_MODIFY_WRITE:
            // Get the current register state with indexes fields only
            rc = fillBuffWithParams((void*)regNode, params, buffer, true);
            if (rc == 0)
            {
                reg_status = _mlxRegLib->sendRegister(regName, GET, buffer);
                if (reg_status == mlxreg::MRLS_SUCCESS)
                {
                    // Use method set normally, and get all modified fields from the user
                    _method = SET;
                    rc = fillBuffWithParams((void*)regNode, params, buffer, false);
                    bufferOfSet = buffer;
                }
                else
                {
                    rc = ERR_CODE_FAILD_TO_SEND_ACCESS_REG;
                }
            }
            break;
        default:
            rc = ERR_CODE_INVALID_METHOD;
            break;
    }
    return rc;
}

template<typename F>
int32_t PrmRegSdk::sendRegisterAndPopulateFields(const std::string& regName,
                                                 AdbInstanceAdvLegacy* regNode,
                                                 std::vector<uint32_t>& buffer,
                                                 std::vector<uint32_t>& bufferOfSet,
                                                 F** fields_ptr,
                                                 uint32_t* number_of_fields)
{
    int32_t rc = 0;
    mlxreg::MlxRegLibStatus reg_status = _mlxRegLib->sendRegister(regName, _method, buffer);
    if (reg_status == mlxreg::MRLS_SUCCESS)
    {
        if (_method == SET)
        {
            buffer = bufferOfSet;
        }

        std::vector<AdbInstanceAdvLegacy*> subItems;
        std::map<std::string, uint32_t> layout;
        rc = getNodeFields(regNode, subItems, (const uint8_t*)buffer.data(), buffer.size() * sizeof(uint32_t));
        if (rc == 0)
        {
            // Realloc according to the number of fields relevant to the response
            *number_of_fields = subItems.size();
            F* fields = nullptr;
            *fields_ptr = fields = static_cast<F*>(realloc(*fields_ptr, sizeof(F) * subItems.size()));
            memset(fields, 0, sizeof(F) * subItems.size());
            for (std::vector<AdbInstanceAdvLegacy*>::size_type i = 0; i != subItems.size(); i++)
            {
                layout[subItems[i]->fullName(1)] = i;
                uint32_t value = (uint32_t)subItems[i]->popBuf((u_int8_t*)&buffer[0]);
                strncpy(fields[i].name, subItems[i]->fullName(1).c_str(), sizeof(fields[i].name) - 1);
                fields[i].name[sizeof(fields[i].name) - 1] = '\0';
                fields[i].value = value;
            }
            _registerMapsCache[regName] = layout;
        }
    }
    else
    {
        rc = ERR_CODE_FAILD_TO_SEND_ACCESS_REG;
    }
    return rc;
}

template int32_t PrmRegSdk::sendRegisterAndPopulateFields<Field>(const std::string& regName,
                                                                 AdbInstanceAdvLegacy* regNode,
                                                                 std::vector<uint32_t>& buffer,
                                                                 std::vector<uint32_t>& bufferOfSet,
                                                                 Field** fields_ptr,
                                                                 uint32_t* number_of_fields);

template int32_t PrmRegSdk::sendRegisterAndPopulateFields<MstPrmRegisterField>(const std::string& regName,
                                                                               AdbInstanceAdvLegacy* regNode,
                                                                               std::vector<uint32_t>& buffer,
                                                                               std::vector<uint32_t>& bufferOfSet,
                                                                               MstPrmRegisterField** fields_ptr,
                                                                               uint32_t* number_of_fields);

int32_t PrmRegSdk::performRegRequest(void* responseOutboxMap)
{
    int32_t rc = ensureRegLibInitialized();
    AdbInstanceAdvLegacy* regNode = nullptr;

    if (rc == 0)
    {
        try
        {
            regNode = _mlxRegLib->findAdbNode(_regName);
        }
        catch (exception& exc)
        {
            setErrorMessage(exc.what());
            rc = ERR_CODE_FAILD_TO_FIND_REG_NODE;
        }
        if (rc == 0 && regNode)
        {
            std::map<std::string, uint32_t> params = parseRegParams(_paramsStr);
            if (!_paramsStr.empty() && params.empty())
            {
                rc = ERR_CODE_INVALID_FIELD_ARG;
            }
            if (rc == 0)
            {
                try
                {
                    std::vector<uint32_t> buffer = genarateBuffer(regNode);
                    std::vector<uint32_t> bufferOfSet;

                    rc = processRegisterMethod(regNode, _regName, params, buffer, bufferOfSet);

                    if (rc == 0)
                    {
                        RegisterMap* reqMap = static_cast<RegisterMap*>(responseOutboxMap);

                        // responseBoxField is allocated in sendRegisterAndPopulateFields
                        if (!_response_box_used)
                        {
                            reqMap->fields = nullptr;
                        }
                        _response_box_used = true;

                        rc = sendRegisterAndPopulateFields<Field>(_regName, regNode, buffer, bufferOfSet,
                                                                  &reqMap->fields, &reqMap->number_of_fields);
                    }
                }
                catch (exception& exc)
                {
                    setErrorMessage(exc.what());
                    rc = ERR_CODE_FAILD_TO_SEND_ACCESS_REG;
                }
            }
        }
    }
    return rc;
}

int32_t PrmRegSdk::showAllRegisters(std::vector<std::string>& registers)
{
    int32_t rc = 0;
    if (!_mlxRegLib)
    {
        rc = initRegLib();
    }
    if (!rc && _mlxRegLib)
    {
        rc = _mlxRegLib->showRegisters(registers);
    }
    return rc;
}

std::string
  PrmRegSdk::fillRegisterMetadataBasicField(AdbInstanceAdvLegacy* adbField, void* metadataFieldVoidPtr, bool fullPath)
{
    MstPrmRegisterFieldMetadata* metadataField = static_cast<MstPrmRegisterFieldMetadata*>(metadataFieldVoidPtr);
    std::string field_name = fullPath ? adbField->fullName(1) : adbField->get_field_name();
    strncpy(metadataField->name, field_name.c_str(), sizeof(metadataField->name) - 1);
    metadataField->name[sizeof(metadataField->name) - 1] = '\0';
    metadataField->address = (adbField->offset >> 3) & ~0x3;
    metadataField->bitOffset = adbField->startBit();
    metadataField->bitSize = (unsigned int)adbField->fieldDesc->eSize();
    metadataField->accessType = convertRegisterAccessType(mlxreg::RegAccessParser::getAccess(adbField));
    return field_name;
}

void PrmRegSdk::fillRegisterMetadataExpandedField(AdbInstanceAdvLegacy* adbField, void* metadataFieldVoidPtr)
{
    MstPrmRegisterFieldExpandedMetadata* expandedField =
      static_cast<MstPrmRegisterFieldExpandedMetadata*>(metadataFieldVoidPtr);
    strncpy(expandedField->description, adbField->fieldDesc->desc.c_str(), sizeof(expandedField->description) - 1);
    strncpy(expandedField->fullPath, adbField->fullName(1).c_str(), sizeof(expandedField->fullPath) - 1);

    auto enum_map = adbField->getEnumMap();
    if (!enum_map.empty())
    {
        expandedField->enums = static_cast<MstPrmRegisterEnum*>(malloc(sizeof(MstPrmRegisterEnum) * enum_map.size()));
        memset(expandedField->enums, 0, sizeof(MstPrmRegisterEnum) * enum_map.size());
        expandedField->number_of_enums = enum_map.size();
        uint32_t enumIdx = 0;
        for (const auto& enum_pair : enum_map)
        {
            strncpy(expandedField->enums[enumIdx].name, enum_pair.first.c_str(),
                    sizeof(expandedField->enums[enumIdx].name) - 1);
            expandedField->enums[enumIdx].name[sizeof(expandedField->enums[enumIdx].name) - 1] = '\0';
            expandedField->enums[enumIdx].value = enum_pair.second;
            enumIdx++;
        }
    }
}

template<typename Metadata, typename Field>
int32_t PrmRegSdk::getRegisterMetadataInt(std::string regName, void* responseOutboxMap, bool expanded, bool fullPath)
{
    int32_t rc = 0;
    std::vector<AdbInstanceAdvLegacy*> fields;
    Metadata* reqMap = static_cast<Metadata*>(responseOutboxMap);
    memset(reqMap, 0, sizeof(Metadata));
    try
    {
        if (!_mlxRegLib)
        {
            rc = initRegLib();
        }
        if (!rc && _mlxRegLib)
        {
            _mlxRegLib->set_current_node(regName);
            auto regNode = _mlxRegLib->get_current_node();
            rc = getNodeFields(regNode, fields);
            if (rc != 0)
            {
                return rc;
            }

            strncpy(reqMap->name, regName.c_str(), sizeof(reqMap->name) - 1);
            reqMap->name[sizeof(reqMap->name) - 1] = '\0';
            reqMap->number_of_fields = fields.size();

            reqMap->fields = static_cast<Field*>(malloc(sizeof(Field) * reqMap->number_of_fields));
            memset(reqMap->fields, 0, sizeof(Field) * reqMap->number_of_fields);
            std::map<std::string, uint32_t> layout;
            for (std::vector<AdbInstanceAdvLegacy*>::size_type i = 0; i != fields.size(); i++)
            {
                std::string fieldName = fillRegisterMetadataBasicField(fields[i], &reqMap->fields[i], fullPath);
                if (expanded)
                {
                    fillRegisterMetadataExpandedField(fields[i], &reqMap->fields[i]);
                }
                layout[fieldName] = i;
            }
            _registerMapsCache[regName] = layout;
        }
        return rc;
    }
    catch (exception& exc)
    {
        setErrorMessage(exc.what());
        rc = ERR_CODE_FAILD_TO_FIND_REG_NODE;
    }
    return rc;
}

template int32_t
  PrmRegSdk::getRegisterMetadataInt<MstPrmRegisterMetadata, MstPrmRegisterFieldMetadata>(std::string regName,
                                                                                         void* responseOutboxMap,
                                                                                         bool expanded,
                                                                                         bool fullPath);
template int32_t PrmRegSdk::getRegisterMetadataInt<MstPrmRegisterExpandedMetadata, MstPrmRegisterFieldExpandedMetadata>(
  std::string regName,
  void* responseOutboxMap,
  bool expanded,
  bool fullPath);

int32_t PrmRegSdk::getRegisterMetadata(const std::string& regName, void* responseOutboxMap, bool fullPath)
{
    return getRegisterMetadataInt<MstPrmRegisterMetadata, MstPrmRegisterFieldMetadata>(regName, responseOutboxMap,
                                                                                       false, fullPath);
}
int32_t PrmRegSdk::getRegisterExpandedMetadata(const std::string& regName, void* responseOutboxMap)
{
    return getRegisterMetadataInt<MstPrmRegisterExpandedMetadata, MstPrmRegisterFieldExpandedMetadata>(
      regName, responseOutboxMap, true, false);
}

int32_t PrmRegSdk::getRegisterFields(const std::string& regName, void* responseOutboxMap)
{
    int32_t rc = 0;
    std::vector<AdbInstanceAdvLegacy*> fields;
    MstPrmRegisterMap* reqMap = static_cast<MstPrmRegisterMap*>(responseOutboxMap);
    memset(reqMap, 0, sizeof(MstPrmRegisterMap));
    try
    {
        if (!_mlxRegLib)
        {
            rc = initRegLib();
        }
        if (!rc && _mlxRegLib)
        {
            _mlxRegLib->set_current_node(regName);
            auto regNode = _mlxRegLib->get_current_node();
            rc = getNodeFields(regNode, fields);
            if (rc != 0)
            {
                return rc;
            }

            strncpy(reqMap->name, regName.c_str(), sizeof(reqMap->name) - 1);
            reqMap->name[sizeof(reqMap->name) - 1] = '\0';
            reqMap->number_of_fields = fields.size();
            reqMap->fields =
              static_cast<MstPrmRegisterField*>(malloc(sizeof(MstPrmRegisterField) * reqMap->number_of_fields));
            std::map<std::string, uint32_t> layout;
            for (std::vector<AdbInstanceAdvLegacy*>::size_type i = 0; i != fields.size(); i++)
            {
                std::string fieldName;
                fieldName = fields[i]->fullName(1);
                snprintf(reqMap->fields[i].name, sizeof(reqMap->fields[i].name), "%s", fieldName.c_str());
                reqMap->fields[i].value = 0;
                reqMap->fields[i].set = false;
                layout[fieldName] = i;
            }
            _registerMapsCache[regName] = layout;
        }
    }
    catch (exception& exc)
    {
        setErrorMessage(exc.what());
        rc = ERR_CODE_FAILD_TO_FIND_REG_NODE;
    }
    return rc;
}

uint32_t PrmRegSdk::getFieldIndexAndMap(const std::string& fieldName, uint32_t& fieldIndex, MstPrmRegisterMap* reqMap)
{
    std::string regName = reqMap->name;
    std::map<std::string, uint32_t> layout = _registerMapsCache[regName];
    if (layout.find(fieldName) == layout.end())
    {
        setErrorMessage("Can't find field name: " + fieldName);
        return ERR_CODE_FAILD_TO_PARSE_FIELD;
    }
    fieldIndex = layout[fieldName];
    return 0;
}

uint32_t PrmRegSdk::setField(const std::string& fieldName, uint32_t value, void* responseOutboxMap)
{
    uint32_t fieldIndex;
    MstPrmRegisterMap* reqMap = static_cast<MstPrmRegisterMap*>(responseOutboxMap);
    uint32_t rc = getFieldIndexAndMap(fieldName, fieldIndex, reqMap);
    if (rc != 0)
    {
        return rc;
    }
    reqMap->fields[fieldIndex].value = value;
    reqMap->fields[fieldIndex].set = true;
    return 0;
}

uint32_t PrmRegSdk::getField(const std::string& fieldName, uint32_t* value, void* responseOutboxMap)
{
    uint32_t fieldIndex;
    MstPrmRegisterMap* reqMap = static_cast<MstPrmRegisterMap*>(responseOutboxMap);
    uint32_t rc = getFieldIndexAndMap(fieldName, fieldIndex, reqMap);
    if (rc != 0)
    {
        return rc;
    }
    *value = reqMap->fields[fieldIndex].value;
    return 0;
}

bool _on_traverse_get_fields(const std::string& calculated_path,
                             uint64_t calculated_offset,
                             uint64_t calculated_value,
                             AdbInstanceAdvLegacy* instance,
                             void* context)
{
    (void)context;
    (void)calculated_value;
    (void)calculated_path;

    vector<tuple<AdbInstanceAdvLegacy*, uint32_t>>* fields_offsets =
      (vector<tuple<AdbInstanceAdvLegacy*, uint32_t>>*)context;
    fields_offsets->push_back(make_tuple(instance, calculated_offset));

    return false; // continue traversal
}

int32_t PrmRegSdk::performRawRegRequest(void* buffer, const uint32_t size)
{
    int32_t rc = 0;
    mlxreg::MlxRegLibStatus reg_status = mlxreg::MRLS_SUCCESS;
    AdbInstanceAdvLegacy* regNode = nullptr;
    vector<uint32_t> outBuffer;
    vector<tuple<AdbInstanceAdvLegacy*, uint32_t>> fields_offsets;

    if ((access_type)_method != GET && (access_type)_method != SET)
    {
        rc = ERR_CODE_INVALID_METHOD;
    }

    if (rc == 0)
    {
        rc = ensureRegLibInitialized();
    }

    if (rc == 0)
    {
        try
        {
            regNode = _mlxRegLib->findAdbNode(_regId);
        }
        catch (AdbException& exc)
        {
            setErrorMessage(exc.what());
            rc = ERR_CODE_FAILD_TO_FIND_REG_NODE;
        }
    }

    if (rc == 0)
    {
        outBuffer = genarateBuffer(regNode, size);

        regNode->traverse_layout("", 0, nullptr, size, _on_traverse_get_fields, &fields_offsets, false, false);

        for (auto field_offset : fields_offsets)
        {
            auto field = get<0>(field_offset);
            auto offset = get<1>(field_offset);
            auto value =
              pop_from_buf_le(static_cast<uint8_t*>(buffer), offset, field->get_size(), field->isPartOfArray());
            updateBuffer(offset, field->get_size(), value, outBuffer);
        }
        // Convert to BE32
        for (std::vector<uint32_t>::size_type j = 0; j < outBuffer.size(); j++)
        {
            outBuffer[j] = CPU_TO_BE32((outBuffer[j]));
        }

        try
        {
            reg_status = _mlxRegLib->sendRegister(_regId, _method, outBuffer);
            if (reg_status != mlxreg::MRLS_SUCCESS)
            {
                rc = ERR_CODE_FAILD_TO_SEND_ACCESS_REG;
            }
        }
        catch (exception& exc)
        {
            setErrorMessage(exc.what());
            rc = ERR_CODE_FAILD_TO_SEND_ACCESS_REG;
        }
        // Convert to BE32
        for (std::vector<uint32_t>::size_type j = 0; j < outBuffer.size(); j++)
        {
            outBuffer[j] = CPU_TO_BE32((outBuffer[j]));
        }

        for (auto field_offset : fields_offsets)
        {
            auto field = get<0>(field_offset);
            auto offset = get<1>(field_offset);
            auto field_size = field->get_size();
            auto value = extractFromBuffer(offset, field_size, outBuffer, field_size != 32 && field->isPartOfArray());
            push_to_buf(static_cast<uint8_t*>(buffer), offset, field_size, value);
        }
    }

    if (rc == 0 || rc == ERR_CODE_FAILD_TO_SEND_ACCESS_REG)
    {
        mlxreg::MlxRegLib::handle_buffer_endianness(buffer, size);
    }

    return rc;
}

std::map<std::string, uint32_t> PrmRegSdk::parseRegParams(void* registerMap)
{
    std::map<std::string, uint32_t> params;

    for (unsigned int i = 0; i < static_cast<MstPrmRegisterMap*>(registerMap)->number_of_fields; i++)
    {
        if (static_cast<MstPrmRegisterMap*>(registerMap)->fields[i].set)
        {
            params[static_cast<MstPrmRegisterMap*>(registerMap)->fields[i].name] =
              static_cast<MstPrmRegisterMap*>(registerMap)->fields[i].value;
        }
    }

    return params;
}

int32_t PrmRegSdk::performRegRequestUsingMap(void* registerMap)
{
    MstPrmRegisterMap* reqMap = static_cast<MstPrmRegisterMap*>(registerMap);
    std::string regName = reqMap->name;
    int32_t rc = ensureRegLibInitialized();
    AdbInstanceAdvLegacy* regNode = nullptr;

    if (rc == 0)
    {
        try
        {
            regNode = _mlxRegLib->findAdbNode(regName);
        }
        catch (exception& exc)
        {
            setErrorMessage(exc.what());
            rc = ERR_CODE_FAILD_TO_FIND_REG_NODE;
        }
        if (rc == 0 && regNode)
        {
            std::map<std::string, uint32_t> params = parseRegParams(registerMap);
            if (rc == 0)
            {
                try
                {
                    std::vector<uint32_t> buffer = genarateBuffer(regNode);
                    std::vector<uint32_t> bufferOfSet;

                    rc = processRegisterMethod(regNode, regName, params, buffer, bufferOfSet);

                    if (rc == 0)
                    {
                        rc = sendRegisterAndPopulateFields<MstPrmRegisterField>(
                          regName, regNode, buffer, bufferOfSet, &reqMap->fields, &reqMap->number_of_fields);
                    }
                }
                catch (exception& exc)
                {
                    setErrorMessage(exc.what());
                    rc = ERR_CODE_FAILD_TO_SEND_ACCESS_REG;
                }
            }
        }
    }

    return rc;
}

std::string PrmRegSdk::getErrorMessage()
{
    return _errorMessage;
}

void PrmRegSdk::setErrorMessage(const std::string& errorMessage)
{
    _errorMessage = errorMessage;
}

void free_register_metadata(MstPrmRegisterMetadata* registerMetadata)
{
    if (registerMetadata)
    {
        if (registerMetadata->fields)
        {
            free(registerMetadata->fields);
        }
        registerMetadata->fields = NULL;
    }
}

void free_register_field_expanded_metadata(MstPrmRegisterExpandedMetadata* registerMetadata)
{
    if (registerMetadata)
    {
        if (registerMetadata->fields)
        {
            for (unsigned int i = 0; i < registerMetadata->number_of_fields; i++)
            {
                if (registerMetadata->fields[i].enums)
                {
                    free(registerMetadata->fields[i].enums);
                }
            }
            free(registerMetadata->fields);
        }
        registerMetadata->fields = NULL;
    }
}

void free_register_map(MstPrmRegisterMap* registerMap)
{
    if (registerMap)
    {
        if (registerMap->fields)
        {
            free(registerMap->fields);
        }
        registerMap->fields = NULL;
    }
}

mfile* PrmRegSdk::getMFile()
{
    ensureRegLibInitialized();
    return _mf;
}

uint32_t PrmRegSdk::getSyndromeCode()
{
    if (!_mf)
    {
        return 0;
    }
    return _mf->icmd.syndrome;
}
