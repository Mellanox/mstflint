/*
 * Copyright (c) 2013-2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

#ifndef PRM_REG_SDK_H_
#define PRM_REG_SDK_H_

#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "mtcr.h"
#include "common/tools_utils.h"
#include "adb_parser/adb_parser.h"
#include "mlxreg/mlxreg_lib/mlxreg_lib.h"

typedef struct MstPrmRegisterMetadata_t MstPrmRegisterMetadata;
typedef struct MstPrmRegisterExpandedMetadata_t MstPrmRegisterExpandedMetadata;
typedef struct MstPrmRegisterMap_t MstPrmRegisterMap;

void free_register_metadata(MstPrmRegisterMetadata* registerMetadata);
void free_register_field_expanded_metadata(MstPrmRegisterExpandedMetadata* registerMetadata);
void free_register_map(MstPrmRegisterMap* registerMap);

class PrmRegSdk
{
public:
    PrmRegSdk(const char* mst_dev, const char* reg_name, const uint32_t method, const char* params);
    PrmRegSdk(const char* mst_dev, uint16_t reg_id, const uint32_t method);
    PrmRegSdk(const char* mst_dev);
    virtual ~PrmRegSdk();

    virtual void initPrmCommand(const char* reg_name, const uint32_t method, const char* params);
    virtual void initPrmCommand(const uint16_t reg_id, const uint32_t method);
    virtual int32_t performRegRequest(void* responseOutboxMap);
    virtual int32_t performRegRequestUsingMap(void* registerMap);
    virtual int32_t performRawRegRequest(void* buffer, const uint32_t size);
    virtual uint32_t setField(const std::string& fieldName, uint32_t value, void* responseOutboxMap);
    virtual uint32_t getField(const std::string& fieldName, uint32_t* value, void* responseOutboxMap);
    virtual int32_t showAllRegisters(std::vector<std::string>& registers);
    virtual int32_t getRegisterFields(const std::string& regName, void* responseOutboxMap);
    virtual int32_t getRegisterMetadata(const std::string& regName, void* responseOutboxMap, bool fullPath = true);
    virtual int32_t getRegisterExpandedMetadata(const std::string& regName, void* responseOutboxMap);
    virtual int32_t initRegLib();
    virtual std::string getErrorMessage();
    virtual void setErrorMessage(const std::string& errorMessage);
    virtual uint32_t getSyndromeCode();
    mfile* getMFile();

protected:
    bool _isExternal;

private:
    // Helper functions
    static uint32_t strToUint32(const std::string& strInt, int& rc);
    static std::vector<std::string> strSplit(const std::string& str, const char delimiter, bool forcePairs, int& rc);
    // Register parser functions
    static std::map<std::string, uint32_t> parseRegParams(const std::string& paramsStr);
    static std::map<std::string, uint32_t> parseRegParams(void* registerMap);
    static void updateBuffer(uint32_t offset, uint32_t size, uint32_t val, std::vector<uint32_t>& buffer);
    uint32_t extractFromBuffer(uint32_t offset, uint32_t size, std::vector<uint32_t>& buffer, bool small_entry_array);
    static bool checkFieldWithPath(void* adbInstanceField, uint32_t idx, std::vector<std::string>& fieldsChain);
    uint32_t getNodeFields(AdbInstanceAdvLegacy* regNode,
                           std::vector<AdbInstanceAdvLegacy*>& fields,
                           const uint8_t* buffer,
                           uint32_t buffer_size);
    static void* getField(const std::string& name, void* regNode);
    static std::string getAccess(const void* field);
    static int fillBuffWithParams(void* regNode,
                                  std::map<std::string, uint32_t>& params,
                                  std::vector<uint32_t>& buffer,
                                  bool fillIndexesOnly);
    static std::vector<uint32_t> genarateBuffer(void* regNode, uint32_t size = 0);
    uint32_t getFieldIndexAndMap(const std::string& fieldName, uint32_t& fieldIndex, MstPrmRegisterMap* reqMap);
    int32_t ensureRegLibInitialized();
    int32_t processRegisterMethod(AdbInstanceAdvLegacy* regNode,
                                  const std::string& regName,
                                  std::map<std::string, uint32_t>& params,
                                  std::vector<uint32_t>& buffer,
                                  std::vector<uint32_t>& bufferOfSet);
    template<typename F>
    int32_t sendRegisterAndPopulateFields(const std::string& regName,
                                          AdbInstanceAdvLegacy* regNode,
                                          std::vector<uint32_t>& buffer,
                                          std::vector<uint32_t>& bufferOfSet,
                                          F** fields_ptr,
                                          uint32_t* number_of_fields);
    std::string
      fillRegisterMetadataBasicField(AdbInstanceAdvLegacy* adbField, void* metadataFieldVoidPtr, bool fullPath);
    void fillRegisterMetadataExpandedField(AdbInstanceAdvLegacy* adbField, void* metadataFieldVoidPtr);
    template<typename Metadata, typename Field>
    int32_t getRegisterMetadataInt(std::string regName, void* responseOutboxMap, bool expanded, bool fullPath);

    mlxreg::MlxRegLib* _mlxRegLib;
    mfile* _mf;
    std::string _mstDevStr;
    std::string _regName;
    std::string _paramsStr;
    std::string _errorMessage;
    bool _response_box_used;
    uint32_t _method;
    uint16_t _regId;

    std::map<std::string, std::map<std::string, uint32_t>> _registerMapsCache;
};
#endif /* PRM_REG_SDK_H_ */
