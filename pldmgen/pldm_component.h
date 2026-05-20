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

 #ifndef PLDM_COMPONENT_H_
 #define PLDM_COMPONENT_H_
 
 #include <string>
 #include <vector>
 
 #include "common/compatibility.h"
 #include "pldm_utils/pldm_utils.h"
 
 #define SOURCE_STR "Source"
 #define IDENTIFIER_STR "Identifier"
 #define VERSION_STR "Version"
 #define COMPONENT_COMPARISON_STAMP_STR "Comparison Stamp"
 #define COMPONENT_OPTIONS_STR "Options"
 #define COMPONENT_ACTIVATION_METHOD_STR "Requested Activation Method"
 
 class PLDMComponent
 {
 public:
     std::string _name;
     std::string _src;
     std::string _version;
     ComponentIdentifier _identifier;
     u_int32_t _offsetOfComponentDataOffset;
     u_int16_t _options;
     u_int16_t _activationMethod;
     u_int32_t _comparisonStamp;
     PLDMComponent(const std::string& name,
                   const std::string& src,
                   const std::string& version,
                   ComponentIdentifier componentIdentifier,
                   const std::string& options,
                   const std::string& activationMethod,
                   u_int32_t comparisonStamp);
     ~PLDMComponent(){};
     void ComponentInfoPack(std::vector<u_int8_t>& buff);
     void ComponentDataPack(std::vector<u_int8_t>& buff);
     u_int32_t ComponentDataSize();
     void SetComponentLocationOffset(std::vector<u_int8_t>& buff, u_int32_t value);
     static std::string extractFwData(std::string& imageSource);
 
 private:
     void ParseHexField(const std::string& value,
                        ComponentField fieldId,
                        u_int8_t maxBytes,
                        const char* fieldName,
                        u_int16_t& out) const;
 };
 
 #endif
 