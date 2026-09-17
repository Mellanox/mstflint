/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

 #ifndef PLDM_H_
 #define PLDM_H_
 
 #include <string>
 #include <vector>
 
 #include <json/value.h>
 #include "common/tools_json.h"
 #include "common/compatibility.h"
 #include "pldm_devicerecord.h"
 #include "pldm_component.h"
 
 class PLDM
 {
     std::string _packageVersion;
     u_int32_t _packageHeaderFormatRevision;
     std::string _releaseDateTime;
     u_int16_t _componentBitmapLength;
     std::vector<PLDMDeviceRecord> _deviceRecords;
     std::vector<PLDMComponent> _components;
 
 public:
     PLDM(const std::string& cookBook, bool recovery);
     void Pack(std::vector<u_int8_t>& buff);
     static void AddComponentsValues(Json::Value& componentAttr);
     static void GenerateEmptyCookBookFromJson(const std::string& json,
                                               bool reuseComponents,
                                               const std::string& fname,
                                               bool keepDescriptorsOrder = false);
     static void DisableCustomPsid(const std::string& inputFile,
                                  const std::string& outputFile,
                                  const std::string& psid,
                                  const std::string& minorVersion);

 
 private:
     void ParseCommonRecordFields(const Json::Value& deviceRecord,
                                  std::vector<u_int8_t>& appliedComponents,
                                  std::vector<PLDMDescriptor>& descriptors);
     PLDMDeviceRecord ParseDeviceRecord(const Json::Value& deviceRecord);
     static std::string FindComponentNameByIdentifier(const std::string& identifier, const Json::Value& components);
     static std::string
       AddComponent(const std::string& identifier, int& componentCounter, Json::Value& components, bool reuseComponents);
 };
 
 #endif