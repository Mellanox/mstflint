/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
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
     static void DisableCustomPsid(const std::string& inputFile, const std::string& outputFile, const std::string& psid);

 
 private:
     static std::string FindComponentNameByIdentifier(const std::string& identifier, const Json::Value& components);
     static std::string
       AddComponent(const std::string& identifier, int& componentCounter, Json::Value& components, bool reuseComponents);
 };
 
 #endif