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

 #pragma once

 #if __cplusplus
 
 #include <string>
 
 #include "common/compatibility.h"
 #include "json/reader.h"
 
 namespace nbu
 {
 namespace mft
 {
 namespace common
 {
 class JSON_API ReaderWrapper
 {
 public:
     ReaderWrapper();
     ~ReaderWrapper();
 
     Json::Reader* getReader();
 
 private:
     Json::Reader* reader;
 };
 
 void AssertMandatory(const Json::Value& value, const std::string& fieldName);
 
 std::string GetStrValue(const Json::Value& value, bool isNumber = false);
 
 std::string GetStrValue(const Json::Value& value, const std::string& fieldName, bool isMandatory, bool isNumber);
 u_int32_t GetUIntFromStrValue(const Json::Value& value, const std::string& fieldName, bool isMandatory);
 u_int32_t GetUIntValue(const Json::Value& value, const std::string& fieldName, bool isMandatory);
 
 } // namespace common
 } // namespace mft
 } // namespace nbu
 
 #else // C {
 
 #include <stdbool.h>
 
 bool GetStrValue(char* file, const char* key, char* out, unsigned len);
 
 #endif // } C
 