/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

using namespace std;
using namespace DB;

class ParamValue {
public:
    ParamValue(string size);
    ParamValue(u_int32_t size) : _size(size) {}

    virtual string      getVal() = 0;
    virtual void        setVal(string s) = 0;
    virtual void setVal(u_int32_t);
    virtual void        setVal(vector<string>);
    virtual void        pack(u_int8_t *buff, u_int32_t offset) = 0;
    virtual void        unpack(u_int8_t *buff, u_int32_t offset) = 0;
    virtual u_int32_t   getIntVal();
    virtual void parseValue(string, u_int32_t&, string&);

    virtual ~ParamValue() {};

protected:
    u_int32_t _size;
};

class UnsignedParamValue : public ParamValue {
public:
    UnsignedParamValue(string size)     :   ParamValue(size), _value(0x0) {}
    UnsignedParamValue(u_int32_t size)  :   ParamValue(size), _value(0x0){}

    virtual string      getVal();
    virtual void        setVal(string s);
    virtual void        setVal(const u_int32_t);
    void        pack(u_int8_t *buff, u_int32_t offset);
    void        unpack(u_int8_t *buff, u_int32_t offset);
    u_int32_t   getIntVal();
    virtual void parseValue(string, u_int32_t&, string&);

    u_int32_t _value;

protected:
    void parseValueAux(string, u_int32_t&, string&, int base = 0);
};

class EnumParamValue : public UnsignedParamValue {
public:
    EnumParamValue(string size, map<string, u_int32_t> textualValues);
    EnumParamValue(u_int32_t size, map<string, u_int32_t> textualValues);

    string  getVal();
    void    setVal(string strVal);
    void    setVal(u_int32_t val);
    void parseValue(string, u_int32_t&, string&);

    map<string, u_int32_t> _textualValues;
};

class BoolParamValue : public EnumParamValue {
public:
    BoolParamValue(string size);

private:
    static map<string, u_int32_t> initBoolTextualValues();
};

class BinaryParamValue : public UnsignedParamValue {
public:
    BinaryParamValue(string size)       : UnsignedParamValue(size) {};
    BinaryParamValue(u_int32_t size)    : UnsignedParamValue(size) {};

    string  getVal();
    void    setVal(string val);
    void parseValue(string, u_int32_t&, string&);

    static void trimHexString(string& s);
};

class StringParamValue : public ParamValue {
public:
    StringParamValue(u_int32_t size) : ParamValue(size) {}

    string  getVal();
    void    setVal(string s);
    void    pack(u_int8_t *buff, u_int32_t bitOffset);
    void    unpack(u_int8_t *buff, u_int32_t bitOffset);

    string _value;
};

class BytesParamValue : public ParamValue {
public:
    BytesParamValue(u_int32_t size) : ParamValue(size) {}
    using ParamValue::setVal;
    string  getVal();
    void    setVal(string val);
    void    setVal(const vector<u_int32_t>& buffVal);
    void parseValue(string, u_int32_t&, string&);
    void    pack(u_int8_t *buff, u_int32_t offset);
    void    unpack(u_int8_t *buff, u_int32_t offset);

private:
    vector<BinaryParamValue> _bytes;
};


class ArrayParamValue : public ParamValue {

public:
    ArrayParamValue(string size, u_int32_t count, enum ParamType paramType);
    ~ArrayParamValue();
    using ParamValue::setVal;
    string              getVal();
    void                setVal(string val);
    void                setVal(vector<string> vals);
    string              getVal(u_int32_t index);
    void                setVal(string val, u_int32_t index);
    u_int32_t           getIntVal();
    vector<u_int32_t>   getIntVals();
    vector<string>      getStrVals();
    void parseValue(string, u_int32_t&, string&);
    void                pack(u_int8_t *buff, u_int32_t offset);
    void                unpack(u_int8_t *buff, u_int32_t offset);

protected:
    u_int32_t _elementSizeInBits;
    vector<ParamValue*> _values;
};

class EnumArrayParamValue : public ArrayParamValue {
public:
    EnumArrayParamValue(string size, u_int32_t count, enum ParamType paramType,
                        map<string, u_int32_t> textualValues);
};

class Param {

private:
    bool _isNameFound, _isTLVNameFound, _isOffsetFound, _isSizeFound,
         _isTypeFound, _isDescriptionFound, _isTextualValuesFound,
         _isMlxconfigNameFound, _isDependencyFound, _isValidBitFound,
         _isTempVarsFound, _isMinValFound, _isMaxValFound, _isRuleFound,
         _isRegexFound, _isPortFound;
public:
    string _name;
    string _tlvName;
    Offset *_offset;
    string _size;
    enum ParamType _type;
    string _description;
    map<string, u_int32_t>  _textualValues;
    string _mlxconfigName;
    string _dependency;
    string _validBit;
    string _tempVars;
    string _minVal;
    string _maxVal;
    string _rule;
    string _regex;
    u_int32_t _port;
    ParamValue *_value;
    u_int32_t _supportedFromVersion;
    u_int32_t _arrayLength;

    Param(int columnsCount, char **dataRow, char **headerRow);
    ~Param();

    string      getDisplayName();
    void        getView(ParamView& paramView);
    void        helpAux();
    void        pack(u_int8_t *buff);
    void        unpack(u_int8_t *buff);
    void        setVal(string val);
    void        setVal(string val, u_int32_t index);
    void        setVal(vector<string> vals);
    string      getVal();
    string      getVal(u_int32_t index);
    void        extractVars(vector<string>& rulesVars, string rule);
    void        getRulesTLV(vector<string>& rulesTlvs);
    void        genXMLTemplate(string& xmlTemplate, bool withVal);
    void        genXMLTemplateAux(string& xmlTemplate, bool withVal, bool isPartOfArray, u_int32_t index);

    static enum ParamType   str2ParamType(const char *s);
    static string           paramType2Str(enum ParamType);
    static void             str2TextualValuesMap(const char *s, map<string, u_int32_t>& m);

};

#endif
