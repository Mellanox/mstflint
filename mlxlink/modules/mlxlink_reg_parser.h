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

#ifndef MLXLINK_REG_PARSER_H
#define MLXLINK_REG_PARSER_H

#include "mlxlink_utils.h"
#include <mtcr.h>

using namespace mlxreg;

#define PDDR_STATUS_MESSAGE_LENGTH_HCA 236
#define PDDR_STATUS_MESSAGE_LENGTH_SWITCH 59

#define MAX_FIELDS_BUFFER 1024

class MlxlinkRegParser : public RegAccessParser
{
public:
    MlxlinkRegParser();
    virtual ~MlxlinkRegParser();

    virtual void resetParser(const string& regName);
    void readMCIA(u_int32_t page, u_int32_t size, u_int32_t offset, u_int8_t* data, u_int32_t i2cAddress);
    virtual void genBuffSendRegister(const string& regName, maccess_reg_method_t method);
    void writeGvmi(u_int32_t data);
    virtual void updateField(string field_name, u_int32_t value);
    void updateWithDefault(const string& fieldName, const string& fieldsStr, u_int32_t val);
    void setDefaultFields(const string& regName, const string& fieldsStr);
    void sendPrmReg(const string& regName, maccess_reg_method_t method, const char* fields, ...);
    void sendPrmReg(const string& regName, maccess_reg_method_t method);
    void sendPrmRegWithoutReset(const string& regName, maccess_reg_method_t method, const char* fields, ...);
    virtual u_int32_t
      getFieldValue(string field_name,
                    u_int32_t size = 0,
                    u_int32_t offset = 0,
                    bool offsetSpecified = false,
                    bool processDynamicFields = false);
    string getFieldStr(const string& field,
                       const u_int32_t size = 0,
                       const u_int32_t offset = 0,
                       bool offsetSpecified = false,
                       bool processDynamicFields = false);
    string getRawFieldValueStr(const string fieldName);
    u_int32_t getFieldSize(string field_name);
    string getAscii(const string& name, u_int32_t size = 4);

    u_int32_t _gvmiAddress;
    MlxRegLib* _regLib;
    mfile* _mf;
    u_int32_t _localPort;
    u_int32_t _pnat;
    u_int32_t _portType;
    int _planeInd;
    bool _isHCA;
    bool _isSwControled;
    bool _isDPNvSupported;
};

#endif /* MLXLINK_REG_PARSER_H */
