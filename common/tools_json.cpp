/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */

 #include "tools_json.h"

 #include <cstring>
 #include <fstream>

 #include "common/tools_string.h"

 namespace nbu
 {
 namespace mft
 {
 namespace common
 {
 
 // Implementation of class ReaderWrapper
 // ////////////////////////////////
 
 ReaderWrapper::ReaderWrapper()
 {
     reader = new Json::Reader{};
 }
 
 ReaderWrapper::~ReaderWrapper()
 {
     delete reader;
 }
 
 Json::Reader* ReaderWrapper::getReader()
 {
     return reader;
 }
 
 // Implementation of class ReaderWrapper
 // ////////////////////////////////
 
 void AssertMandatory(const Json::Value& value, const std::string& fieldName)
 {
     if (value[fieldName].empty())
     {
         throw std::invalid_argument(string_format("field '%s' is missing", fieldName.c_str()));
     }
 }
 
 std::string GetStrValue(const Json::Value& value, bool isNumber)
 {
     if (value.empty())
     {
         return isNumber ? "0" : "";
     }
     else
     {
         return value.asString();
     }
 }
 
 std::string GetStrValue(const Json::Value& value, const std::string& fieldName, bool isMandatory, bool isNumber)
 {
     if (value[fieldName].empty())
     {
         if (isMandatory)
         {
             throw std::invalid_argument(string_format("field '%s' is missing", fieldName.c_str()));
         }
         return isNumber ? "0" : "";
     }
     else
     {
         if (!value[fieldName].isString())
         {
             throw std::invalid_argument(string_format("field '%s' must be a string", fieldName.c_str()));
         }
         return value[fieldName].asString();
     }
 }
 
 u_int32_t GetUIntFromStrValue(const Json::Value& value, const std::string& fieldName, bool isMandatory)
 {
     std::string strValue = GetStrValue(value, fieldName, isMandatory, true);
     if (strValue.size() >= 2 && strValue.substr(0, 2) == "0x")
     {
         strValue = strValue.substr(2);
     }
     if (strValue.size() > 8)
     {
         throw std::invalid_argument(string_format("field '%s' is too large", fieldName.c_str()));
     }
     return std::strtoul(strValue.c_str(), nullptr, 16);
 }
 
 u_int32_t GetUIntValue(const Json::Value& value, const std::string& fieldName, bool isMandatory)
 {
     if (value[fieldName].empty())
     {
         if (isMandatory)
         {
             throw std::invalid_argument(string_format("field '%s' is missing", fieldName.c_str()));
         }
         return 0;
     }
     else
     {
         if (!value[fieldName].isUInt())
         {
             throw std::invalid_argument(string_format("field '%s' must be a number", fieldName.c_str()));
         }
         return value[fieldName].asUInt();
     }
 }
 
 } // namespace common
 } // namespace mft
 } // namespace nbu

 extern "C"
 {
     bool GetStrValue(char* file, const char* key, char* out, unsigned len)
     {
         if (!out || len <= 0)
         {
             return false;
         }
 
         std::ifstream jsonStream(file);
         if (!jsonStream)
         {
             return false;
         }
 
         Json::CharReaderBuilder readerBuilder;
         JSONCPP_STRING errs;
         Json::Value jsonValue;
 
         if (!Json::parseFromStream(readerBuilder, jsonStream, &jsonValue, &errs) || jsonValue[key].empty() ||
             !jsonValue[key].isString())
         {
             return false;
         }
 
         std::string value = jsonValue[key].asString();
         strncpy(out, value.c_str(), len - 1);
         out[len - 1] = '\0';
 
         return true;
     }
 }
 