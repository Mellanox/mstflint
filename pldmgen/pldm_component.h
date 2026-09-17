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
 