/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 * mlxcfg_param.h
 *
 *  Created on: May 24, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_PARAM_H_
#define MLXCFG_PARAM_H_

#include <string>
#include <vector>
#include <map>
#include "mlxcfg_view.h"
#include "mlxcfg_db_items.h"
#include <memory>

using namespace std;
using namespace DB;

class ParamValue
{
public:
    ParamValue(string size);
    ParamValue(u_int32_t size) : _size(size) {}

    virtual string getVal() = 0;
    virtual string getValFormatted();
    virtual void setVal(string s) = 0;
    virtual void setVal(u_int32_t);
    virtual void setVal(vector<string>);
    virtual void pack(u_int8_t* buff, u_int32_t offset) = 0;
    virtual void unpack(u_int8_t* buff, u_int32_t offset) = 0;
    virtual u_int32_t getIntVal();
    virtual void parseValue(string, u_int32_t&, string&);

    virtual ~ParamValue(){};

    // Create a deep copy of the concrete ParamValue instance
    virtual std::shared_ptr<ParamValue> clone() const = 0;

protected:
    u_int32_t _size;
};

class UnsignedParamValue : public ParamValue
{
public:
    UnsignedParamValue(string size) : ParamValue(size), _value(0x0) {}
    UnsignedParamValue(u_int32_t size) : ParamValue(size), _value(0x0) {}

    virtual string getVal() override;
    virtual void setVal(string s) override;
    virtual void setVal(const u_int32_t) override;
    void pack(u_int8_t* buff, u_int32_t offset) override;
    void unpack(u_int8_t* buff, u_int32_t offset) override;
    u_int32_t getIntVal() override;
    virtual void parseValue(string, u_int32_t&, string&) override;
    virtual std::shared_ptr<ParamValue> clone() const override;

    u_int32_t _value;

protected:
    void parseValueAux(string, u_int32_t&, string&, int base = 0);
};

class EnumParamValue : public UnsignedParamValue
{
public:
    EnumParamValue(string size, map<string, u_int32_t> textualValues);
    EnumParamValue(u_int32_t size, map<string, u_int32_t> textualValues);

    string getVal() override;
    void setVal(string strVal) override;
    void setVal(u_int32_t val) override;
    void parseValue(string, u_int32_t&, string&) override;
    virtual std::shared_ptr<ParamValue> clone() const override;

    map<string, u_int32_t> _textualValues;
};

class BoolParamValue : public EnumParamValue
{
public:
    BoolParamValue(string size);
    virtual std::shared_ptr<ParamValue> clone() const override;

private:
    static map<string, u_int32_t> initBoolTextualValues();
};

class BinaryParamValue : public UnsignedParamValue
{
public:
    BinaryParamValue(string size) : UnsignedParamValue(size){};
    BinaryParamValue(u_int32_t size) : UnsignedParamValue(size){};

    string getVal() override;
    string getValFormatted() override;
    void setVal(string val) override;
    void parseValue(string, u_int32_t&, string&) override;
    virtual std::shared_ptr<ParamValue> clone() const override;

    static void trimHexString(string& s);
};

class StringParamValue : public ParamValue
{
public:
    StringParamValue(u_int32_t size) : ParamValue(size) { _value = ""; }

    string getVal() override;
    void setVal(string s) override;
    void pack(u_int8_t* buff, u_int32_t bitOffset) override;
    void unpack(u_int8_t* buff, u_int32_t bitOffset) override;
    virtual std::shared_ptr<ParamValue> clone() const override;

    string _value;
};

class BytesParamValue : public ParamValue
{
public:
    BytesParamValue(u_int32_t size) : ParamValue(size) { _bytes = vector<BinaryParamValue>(); }
    using ParamValue::setVal;
    string getVal() override;
    string getValFormatted() override;
    void setVal(string val) override;
    void setVal(const vector<u_int32_t>& buffVal);
    void parseValue(string, u_int32_t&, string&) override;
    void pack(u_int8_t* buff, u_int32_t offset) override;
    void unpack(u_int8_t* buff, u_int32_t offset) override;
    virtual std::shared_ptr<ParamValue> clone() const override;

private:
    vector<BinaryParamValue> _bytes;
};

class ArrayParamValue : public ParamValue
{
private:
    u_int32_t offsetToBigEndian(u_int32_t offset);

public:
    ArrayParamValue(string size, u_int32_t count, enum ParamType paramType);
    ~ArrayParamValue();
    using ParamValue::setVal;
    using ParamValue::getValFormatted;
    string getVal() override;
    void setVal(string val) override;
    void setVal(vector<string> vals) override;
    void setVal(string val, u_int32_t index);
    string getVal(u_int32_t index);
    string getValFormatted(u_int32_t index);
    u_int32_t getIntVal() override;
    vector<u_int32_t> getIntVals();
    vector<string> getStrVals();
    void parseValue(string, u_int32_t&, string&) override;
    void pack(u_int8_t* buff, u_int32_t offset) override;
    void unpack(u_int8_t* buff, u_int32_t offset) override;
    virtual std::shared_ptr<ParamValue> clone() const override;

protected:
    u_int32_t _elementSizeInBits;
    vector<std::shared_ptr<ParamValue>> _values;
};

class EnumArrayParamValue : public ArrayParamValue
{
public:
    EnumArrayParamValue(string size, u_int32_t count, enum ParamType paramType, map<string, u_int32_t> textualValues);
    virtual std::shared_ptr<ParamValue> clone() const override;
};

class BytesArrayParamVal : public ParamValue
{
public:
    BytesArrayParamVal(u_int32_t numOfBytes);
    virtual ~BytesArrayParamVal();

    void setVal(string val) override;
    void setVal(vector<string> vals) override;
    void setVal(u_int32_t val) override;
    void setVal(u_int32_t val, u_int32_t offset);
    void setVal(const vector<u_int32_t>& buffVal);
    string getVal() override;
    vector<u_int32_t> getIntVals();
    vector<string> getStrVals();
    void pack(u_int8_t* buff, u_int32_t offset) override;
    void unpack(u_int8_t* buff, u_int32_t offset) override;
    virtual std::shared_ptr<ParamValue> clone() const override;

    bool isEmpty;
    vector<uint8_t> _bytes;
};

class Param
{
private:
    bool _isNameFound, _isTLVNameFound, _isOffsetFound, _isSizeFound, _isTypeFound, _isDescriptionFound,
      _isTextualValuesFound, _isMlxconfigNameFound, _isDependencyFound, _isValidBitFound, _isTempVarsFound,
      _isMinValFound, _isMaxValFound, _isRuleFound, _isRegexFound;

public:
    string _name;
    string _tlvName;
    shared_ptr<Offset> _offset;
    string _size;
    enum ParamType _type;
    string _description;
    map<string, u_int32_t> _textualValues;
    string _mlxconfigName;
    string _dependency;
    string _validBit;
    string _tempVars;
    string _minVal;
    string _maxVal;
    string _rule;
    string _regex;
    u_int32_t _port;
    int32_t _module;
    shared_ptr<ParamValue> _value;
    u_int32_t _supportedFromVersion;
    u_int32_t _arrayLength;

    Param(int columnsCount, char** dataRow, char** headerRow);
    ~Param();

    string getDisplayName();
    void getView(ParamView& paramView);
    void helpAux();
    void pack(u_int8_t* buff);
    void unpack(u_int8_t* buff);
    void setVal(string val);
    void setVal(string val, u_int32_t index);
    void setVal(vector<string> vals);
    string getVal(bool confFormat = false);
    string getVal(u_int32_t index);
    void extractVars(vector<string>& rulesVars, string rule);
    void getRulesTLV(vector<string>& rulesTlvs);
    void genXMLTemplate(string& xmlTemplate, bool withVal, bool confFormat);
    void genXMLTemplateAux(string& xmlTemplate, bool withVal, bool isPartOfArray, u_int32_t index, bool confFormat);

    // Create a deep copy of Param, including a deep copy of _value
    std::shared_ptr<Param> cloneDeep() const;

    static enum ParamType str2ParamType(const char* s);
    static string paramType2Str(enum ParamType);
    static void str2TextualValuesMap(const char* s, map<string, u_int32_t>& m);
};

bool isParamViewInList(const ParamView& param, const vector<ParamView>& list);
#endif
