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
 * mlxcfg_param.cpp
 *
 *  Created on: May 24, 2016
 *      Author: ahmads
 */


#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../tools_layouts/adb_to_c_utils.h"
#include "../common/compatibility.h"

#include "mlxcfg_param.h"
#include "mlxcfg_utils.h"

using namespace std;

#define ENABLED "True"
#define DISABLED "False"

#define PARAM_NAME_HEADER "name"
#define PARAM_TLVNAME_HEADER "tlv_name"
#define PARAM_OFFSET_HEADER "offset"
#define PARAM_SIZE_HEADER "size"
#define PARAM_TYPE_HEADER "type"
#define PARAM_DESCRIPTION_HEADER "description"
#define PARAM_TEXTUAL_VALUES_HEADER "textual_values"
#define PARAM_MLXCONFIG_NAME_HEADER "mlxconfig_name"
#define PARAM_DEPENDENCY_HEADER "dependency"
#define PARAM_VALID_BIT_HEADER "valid_bit"
#define PARAM_TEMP_VARS_HEADER "temp_vars"
#define PARAM_MIN_VAL_HEADER "min_val"
#define PARAM_MAX_VAL_HEADER "max_val"
#define PARAM_RULE_HEADER "rule"
#define PARAM_REGEX_HEADER "regex"
#define PARAM_PORT_HEADER "port"
#define PARAM_SUPPORTED_FROM_VERSION_HEADER "supported_from_version"
#define PARAM_ARRAY_LENGTH "array_length"

#define OPERATION_NOT_SUPPORTED "Operation is not supported"

#define CHECK_IF_FIELD_FOUND(b, s) \
    if (!b) { \
        throw MlxcfgException("The Parameter field %s was not initialized", s); \
    }


#define CHECKFIELD(d, n) \
    if (!d || (strcmp(d, "") == 0)) { \
        throw MlxcfgException("The field: %s, cannot be empty", n); \
    }

u_int32_t getSizeInBits(string size)
{
    u_int32_t bits = 0;
    size_t pos = size.find('.');

    if (pos != string::npos) {
        bits += atoi(size.substr(pos + 1).c_str());
    }
    bits += (8 * strtol(size.substr(0, pos).c_str(), NULL, 0));
    return bits;
}

Param::Param(int columnsCount, char **dataRow, char **headerRow) :
    _isNameFound(false), _isTLVNameFound(false), _isOffsetFound(false),
    _isSizeFound(false), _isTypeFound(false), _isDescriptionFound(false),
    _isTextualValuesFound(false), _isMlxconfigNameFound(false),
    _isDependencyFound(false), _isValidBitFound(false), _isTempVarsFound(false),
    _isMinValFound(false), _isMaxValFound(false), _isRuleFound(false),
    _isRegexFound(false), _isPortFound(false), _supportedFromVersion(0),
    _arrayLength(0)
{
    _offset = (Offset*)NULL;
    for (int i = 0; i < columnsCount; i++) {
        if (strcmp(headerRow[i], PARAM_NAME_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            _name = dataRow[i];
            _isNameFound = true;
        } else if (strcmp(headerRow[i], PARAM_TLVNAME_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            if (!dataRow[i]) {
                throw MlxcfgException("Empty tlv_name field");
            }
            _tlvName = dataRow[i];
            _isTLVNameFound = true;
        } else if (strcmp(headerRow[i], PARAM_OFFSET_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            if (_offset) {
                delete _offset;
            }
            _offset = new Offset(dataRow[i]);
            _isOffsetFound = true;
        } else if (strcmp(headerRow[i], PARAM_SIZE_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            _size = dataRow[i];
            _isSizeFound = true;
        } else if (strcmp(headerRow[i], PARAM_TYPE_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            _type = Param::str2ParamType(dataRow[i]);
            _isTypeFound = true;
        } else if (strcmp(headerRow[i], PARAM_DESCRIPTION_HEADER) == 0) {
            //CHECKFIELD(dataRow[i], headerRow[i])
            _description = dataRow[i] ? dataRow[i] : "";
            _isDescriptionFound = true;
        } else if (strcmp(headerRow[i], "version") == 0) {
            //TODO there is something in params regarding version.. check it
        } else if (strcmp(headerRow[i], PARAM_TEXTUAL_VALUES_HEADER) == 0) {
            if (dataRow[i] != NULL) {
                Param::str2TextualValuesMap(dataRow[i], _textualValues);
            }
            _isTextualValuesFound = true;
        } else if (strcmp(headerRow[i], PARAM_MLXCONFIG_NAME_HEADER) == 0) {
            _mlxconfigName = dataRow[i] ? dataRow[i] : "";
            _isMlxconfigNameFound = true;
        } else if (strcmp(headerRow[i], PARAM_DEPENDENCY_HEADER) == 0) {
            _dependency = dataRow[i] ? dataRow[i] : "";
            _isDependencyFound = true;
        } else if (strcmp(headerRow[i], PARAM_VALID_BIT_HEADER) == 0) {
            _validBit = dataRow[i] ? dataRow[i] : "";
            _isValidBitFound = true;
        } else if (strcmp(headerRow[i], PARAM_TEMP_VARS_HEADER) == 0) {
            _tempVars = dataRow[i] ? dataRow[i] : "";
            _isTempVarsFound = true;
        } else if (strcmp(headerRow[i], PARAM_MIN_VAL_HEADER) == 0) {
            _minVal = dataRow[i] ? dataRow[i] : "";
            _isMinValFound = true;
        } else if (strcmp(headerRow[i], PARAM_MAX_VAL_HEADER) == 0) {
            _maxVal = dataRow[i] ? dataRow[i] : "";
            _isMaxValFound = true;
        } else if (strcmp(headerRow[i], PARAM_RULE_HEADER) == 0) {
            _rule = dataRow[i] ? dataRow[i] : "";
            _isRuleFound = true;
        } else if (strcmp(headerRow[i], PARAM_REGEX_HEADER) == 0) {
            _regex = dataRow[i] ? dataRow[i] : "";
            _isRegexFound = true;
        } else if (strcmp(headerRow[i], PARAM_PORT_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            _port = atoi(dataRow[i]);
            _isPortFound = true;
        } else if (strcmp(headerRow[i], PARAM_SUPPORTED_FROM_VERSION_HEADER) == 0) {
            _supportedFromVersion = atoi(dataRow[i]);
        } else if (strcmp(headerRow[i], PARAM_ARRAY_LENGTH) == 0) {
            _arrayLength = atoi(dataRow[i]);
        } else {
            throw MlxcfgException("Unknown parameter field: %s", headerRow[i]);
        }
    }

    CHECK_IF_FIELD_FOUND(_isNameFound, PARAM_NAME_HEADER)
    CHECK_IF_FIELD_FOUND(_isTLVNameFound, PARAM_TLVNAME_HEADER)
    CHECK_IF_FIELD_FOUND(_isOffsetFound, PARAM_OFFSET_HEADER)
    CHECK_IF_FIELD_FOUND(_isSizeFound, PARAM_SIZE_HEADER)
    CHECK_IF_FIELD_FOUND(_isTypeFound, PARAM_TYPE_HEADER)
    CHECK_IF_FIELD_FOUND(_isDescriptionFound, PARAM_DESCRIPTION_HEADER)
    CHECK_IF_FIELD_FOUND(_isTextualValuesFound, PARAM_TEXTUAL_VALUES_HEADER)
    CHECK_IF_FIELD_FOUND(_isMlxconfigNameFound, PARAM_MLXCONFIG_NAME_HEADER)
    CHECK_IF_FIELD_FOUND(_isDependencyFound, PARAM_DEPENDENCY_HEADER)
    CHECK_IF_FIELD_FOUND(_isValidBitFound, PARAM_VALID_BIT_HEADER)
    CHECK_IF_FIELD_FOUND(_isTempVarsFound, PARAM_TEMP_VARS_HEADER)
    CHECK_IF_FIELD_FOUND(_isMinValFound, PARAM_MIN_VAL_HEADER)
    CHECK_IF_FIELD_FOUND(_isMaxValFound, PARAM_MAX_VAL_HEADER)
    CHECK_IF_FIELD_FOUND(_isRuleFound, PARAM_RULE_HEADER)
    CHECK_IF_FIELD_FOUND(_isRegexFound, PARAM_REGEX_HEADER)
    CHECK_IF_FIELD_FOUND(_isPortFound, PARAM_PORT_HEADER)

    if (_type == ENUM && _textualValues.empty()) {
        throw MlxcfgException(
                  "The parameter: %s, "
                  "is type of ENUM but there is no any enum provided",
                  _name.c_str());
    }

    switch (_type) {
    case BOOLEAN_TYPE:
        _value = new BoolParamValue(_size);
        break;

    case ENUM:
        if (_arrayLength == 0) {
            _value = new EnumParamValue(_size, _textualValues);
        } else {
            _value = new EnumArrayParamValue(_size, _arrayLength, ENUM, _textualValues);
        }
        break;

    case INTEGER:
    case UNSIGNED:
        if (_arrayLength == 0) {
            _value = new UnsignedParamValue(_size);
        } else {
            _value = new ArrayParamValue(_size, _arrayLength, UNSIGNED);
        }
        break;

    case BINARY:
        if (_arrayLength == 0) {
            _value = new BinaryParamValue(_size);
        } else {
            _value = new ArrayParamValue(_size, _arrayLength, BINARY);
        }
        break;

    case STRING:
        _value = new StringParamValue(_arrayLength);
        break;

    case BYTES:
        _value = new BytesParamValue(_arrayLength);
        break;

    default:
        throw MlxcfgException("Unknown parameter type %d", _type);
    }

}

Param::~Param()
{
    delete _value;
    delete _offset;
}

void Param::pack(u_int8_t *buff)
{
    _value->pack(buff, _offset->toBigEndian(getSizeInBits(_size), _arrayLength == 0));
}

void Param::unpack(u_int8_t *buff)
{
    _value->unpack(buff, _offset->toBigEndian(getSizeInBits(_size), _arrayLength == 0));
}

void Param::setVal(string val)
{
    try {
        _value->setVal(val);
    } catch (MlxcfgException& e) {
        throw MlxcfgException("Cannot set the value %s for the parameter %s: %s",
                              val.c_str(), getDisplayName().c_str(), e._err.c_str());
    }
}

void Param::setVal(string val, u_int32_t index)
{
    if (_arrayLength == 0 || _type == STRING || _type == BYTES) {
        throw MlxcfgException("Operation not supported for this type of parameters");
    }
    ((ArrayParamValue*)_value)->setVal(val, index);
}

void Param::setVal(vector<string> vals)
{
    _value->setVal(vals);
}

string Param::getVal()
{
    return _value->getVal();
}

string Param::getVal(u_int32_t index)
{
    if (_arrayLength == 0 || _type == STRING || _type == BYTES) {
        throw MlxcfgException("Operation not supported for this type of parameters");
    }
    return ((ArrayParamValue*)_value)->getVal(index);
}

void Param::getView(ParamView& paramView)
{
    if ((_type != BOOLEAN_TYPE && _type != ENUM && _type != INTEGER && _type != UNSIGNED && _type != BINARY) ||
        (_arrayLength != 0 && (_type == STRING || _type == BYTES))) {
        throw MlxcfgException("Operation not supported");
    }
    paramView.mlxconfigName = _mlxconfigName;
    paramView.description = _description;
    paramView.type = _type;
    paramView.port = _port;
    paramView.textualVals = _textualValues;
    if (_arrayLength != 0 && _type != STRING && _type != BYTES) {
        string strVal = "Array[0..";
        strVal += numToStr(_arrayLength - 1) + "]";
        paramView.strVal = strVal;
        paramView.val = 0x0;
        paramView.arrayVal = ((ArrayParamValue*)_value)->getIntVals();
        paramView.strArrayVal = ((ArrayParamValue*)_value)->getStrVals();
    } else {
        paramView.val = ((UnsignedParamValue*)_value)->_value;
        paramView.strVal = _value->getVal();
    }
}

string Param::getDisplayName()
{
    string displayName = _name;
    displayName += (_mlxconfigName.empty()) ? "" : ("(" + _mlxconfigName + ")");
    return displayName;
}

ParamType Param::str2ParamType(const char *s)
{
    if (strcmp(s, "BOOL") == 0) {
        return BOOLEAN_TYPE;
    } else if (strcmp(s, "ENUM") == 0) {
        return ENUM;
    } else if (strcmp(s, "INTEGER") == 0) {
        return INTEGER;
    } else if (strcmp(s, "UNSIGNED") == 0) {
        return UNSIGNED;
    } else if (strcmp(s, "STRING") == 0) {
        return STRING;
    } else if (strcmp(s, "BINARY") == 0) {
        return BINARY;
    } else if (strcmp(s, "BYTES") == 0) {
        return BYTES;
    }
    throw MlxcfgException("Unknown parameter type '%s'", s);
}

string Param::paramType2Str(enum ParamType paramType)
{
    if (paramType == BOOLEAN_TYPE) {
        return "BOOL";;
    } else if (paramType == ENUM) {
        return "ENUM";
    } else if (paramType == INTEGER) {
        return "INTEGER";
    } else if (paramType == UNSIGNED) {
        return "UNSIGNED";
    } else if (paramType == STRING) {
        return "STRING";
    } else if (paramType == BINARY) {
        return "BINARY";
    } else if (paramType == BYTES) {
        return "BYTES";
    } else {
        throw MlxcfgException("Unknown parameter type %d", paramType);
    }
}

//split a string by comma, updates result vector with all sub-strings
void splitByComma(const char *s, vector<string>& result)
{
    int len = strlen(s);
    string e2v = "";

    for (int i = 0; i < len; i++) {
        if (s[i] == ',') {
            result.push_back(e2v);
            e2v = "";
        } else {
            e2v += s[i];
        }
    }
    result.push_back(e2v);
}

void extractEnumAndValue(string e2v, string& e, u_int32_t& v)
{
    size_t eqPos = e2v.find('=');
    if (eqPos == string::npos) {
        throw MlxcfgException("Enum syntax error: %s", e2v.c_str());
    }
    e = e2v.substr(0, eqPos);
    v = strtol(e2v.substr(eqPos + 1).c_str(), NULL, 16);
    return;
}

void Param::extractVars(vector<string>& result, string rule)
{
    string tlv;
    for (unsigned int i = 0; i < rule.size(); i++) {
        if (rule[i] == '$') {
            tlv = "";
            i++;
            while (i < rule.size() &&
                   (rule[i] == '_' ||
                    rule[i] == '.' ||
                    ('a' <= rule[i] && rule[i] <= 'z') ||
                    ('A' <= rule[i] && rule[i] <= 'Z') ||
                    ('0' <= rule[i] && rule[i] <= '9'))) {
                tlv += rule[i];
                i++;
            }
            result.push_back(tlv);
        }
    }
    if (!tlv.empty()) {
        result.push_back(tlv);
    }
}

void Param::getRulesTLV(vector<string>& result)
{
    vector<string> vars;
    extractVars(vars, _rule);
    extractVars(vars, _minVal);
    extractVars(vars, _maxVal);
    extractVars(vars, _tempVars);
    for (unsigned int i = 0; i < vars.size(); i++) {
        size_t pos = vars[i].find('.');
        if (pos == string::npos) {
            continue;
        }
        //printf("-D- tlv=%s", vars[i].substr(0, pos).c_str());
        result.push_back(vars[i].substr(0, pos));
    }
}

void Param::str2TextualValuesMap(const char *s, map<string, u_int32_t>& m)
{
    u_int32_t v;
    string e, e2v;
    vector<string> e2vVector;

    //printf("-D- textual_values=%s\n", s);

    //first split the string by comma
    splitByComma(s, e2vVector);

    //extract the enum and update the map with this enum and its value
    for (size_t i = 0; i < e2vVector.size(); i++) {
        e2v = e2vVector[i];
        e = "";
        extractEnumAndValue(e2v, e, v);
        m[e] = v;
    }
}

void Param::genXMLTemplateAux(std::string& xmlTemplate, bool withVal, bool isPartOfArray, u_int32_t index)
{
    if (_type == ENUM) {
        xmlTemplate += "<!-- Legal Values:";
        std::map<string, u_int32_t>::iterator tv = _textualValues.begin();
        xmlTemplate += tv->first;
        tv++;
        for (; tv != _textualValues.end(); tv++) {
            xmlTemplate += "|" + tv->first;
        }
        xmlTemplate += " -->\n";
    } else if (_type == BOOLEAN_TYPE) {
        xmlTemplate += "<!-- Legal Values: " DISABLED "/" ENABLED " -->\n";
    }
    xmlTemplate += "<" + _name + (isPartOfArray ? (" index='" + numToStr(index) + "' ")  : "") + ">" +
                   (withVal ? (isPartOfArray ? getVal(index) : getVal()) : "") +
                   "</" + _name + ">";
    xmlTemplate += isPartOfArray ? "\n" : "";
}

void Param::genXMLTemplate(std::string& xmlTemplate, bool withVal)
{
    if (_arrayLength != 0 && _type != STRING && _type != BYTES) {
        for (u_int32_t i = 0; i < _arrayLength; i++) {
            genXMLTemplateAux(xmlTemplate, withVal, true, i);
        }
    } else {
        genXMLTemplateAux(xmlTemplate, withVal, false, 0);
    }
}

/* ParamValue Class */
ParamValue::ParamValue(string size)
{
    _size = getSizeInBits(size);
}

u_int32_t ParamValue::getIntVal()
{
    throw MlxcfgException(OPERATION_NOT_SUPPORTED);
}

void ParamValue::setVal(u_int32_t)
{
    throw MlxcfgException(OPERATION_NOT_SUPPORTED);
}

void ParamValue::setVal(vector<string> /*vals*/)
{
    throw MlxcfgException(OPERATION_NOT_SUPPORTED);
}

void ParamValue::parseValue(string, u_int32_t&, string&)
{
    throw MlxcfgException(OPERATION_NOT_SUPPORTED);
}


/* UnsignedParamValue Class */
string UnsignedParamValue::getVal()
{
    string strVal;
    stringstream ss;

    //convert int to string
    ss << _value;
    strVal = ss.str();

    return strVal;
}

void UnsignedParamValue::setVal(string s)
{
    string strVal;
    parseValue(s, _value, strVal);
}

void UnsignedParamValue::setVal(const u_int32_t value)
{
    _value = value;
}

void UnsignedParamValue::pack(u_int8_t *buff, u_int32_t bitOffset)
{
    adb2c_push_bits_to_buff(buff, bitOffset, _size, _value);
}

void UnsignedParamValue::unpack(u_int8_t *buff, u_int32_t bitOffset)
{
    _value = adb2c_pop_bits_from_buff(buff, bitOffset, _size);
}

u_int32_t UnsignedParamValue::getIntVal()
{
    return _value;
}

void UnsignedParamValue::parseValueAux(string strToParse, u_int32_t& value, string& strValue, int base)
{
    if (strToNum(strToParse, value, base)) {
        if ((_size == 32 && value == MLXCFG_UNKNOWN) ||
            ((_size != 32) && value > (unsigned)((1 << _size) - 1))) {
            throw MlxcfgException("The value %s is not valid,  as its size is %d bits",
                                  strToParse.c_str(), _size);
        }
    } else {
        throw MlxcfgException("Cannot parse the value");
    }
    strValue = strToParse;
}

void UnsignedParamValue::parseValue(string strToParse, u_int32_t& value, string& strValue)
{
    parseValueAux(strToParse, value, strValue);
}

/* EnumParamValue Class */
EnumParamValue::EnumParamValue(string size, map<string, u_int32_t> textualValues) :
    UnsignedParamValue(size), _textualValues(textualValues)
{

}

EnumParamValue::EnumParamValue(u_int32_t size, map<string, u_int32_t> textualValues) :
    UnsignedParamValue(size), _textualValues(textualValues)
{

}

string EnumParamValue::getVal()
{
    map<string, u_int32_t>::const_iterator it;

    //printf("-D- textual values size = %u\n", (unsigned int)_textualValues.size());
    for (it = _textualValues.begin(); it != _textualValues.end(); ++it) {
        //printf("-D- textual value - %s=%d\n", it->first.c_str(), it->second);
        if (it->second == _value) {
            return it->first;
        }
    }
    //its enum and we did not find the mapping of the value, so what to do?
    //do not throw exception, print the value as it
    return UnsignedParamValue::getVal();
};

void EnumParamValue::setVal(string strVal)
{
    string s;
    parseValue(strVal, _value, s);
}

void EnumParamValue::setVal(u_int32_t value)
{
    map<string, u_int32_t>::const_iterator it;

    for (it = _textualValues.begin(); it != _textualValues.end(); ++it) {
        if (it->second == value) {
            _value = value;
            return;
        }
    }

    throw MlxcfgException("Unknown value %d", value);
}

void EnumParamValue::parseValue(string strToParse, u_int32_t& value, string& strValue)
{
    map<string, u_int32_t>::const_iterator it;

    //try to convert to int
    if (strToNum(strToParse, value)) {
        //try to find the enum
        for (it = _textualValues.begin(); it != _textualValues.end(); ++it) {
            //printf("-D- textual value - %s=%d\n", it->first.c_str(), it->second);
            if (it->second == value) {
                strValue = it->first;
                return;
            }
        }
    } else {
        for (it = _textualValues.begin(); it != _textualValues.end(); ++it) {
            if (strcasecmp(it->first.c_str(), strToParse.c_str()) == 0) {
                value = it->second;
                strValue = it->first;
                return;
            }
        }
    }

    throw MlxcfgException("Unknown value %s", strToParse.c_str());
}


/* BoolParamValue Class */
BoolParamValue::BoolParamValue(string size) :
    EnumParamValue(size, initBoolTextualValues())
{

}

map<string, u_int32_t> BoolParamValue::initBoolTextualValues()
{
    map<string, u_int32_t> m;
    m[DISABLED] = 0;
    m[ENABLED] = 1;
    return m;
}


/* BinaryParamValue Class */
string BinaryParamValue::getVal()
{
    return numToStr(_value, true);
}

void BinaryParamValue::setVal(string val)
{
    string tmpStr = val;

    trimHexString(val);

    if (val.size() > 8) {
        throw MlxcfgException("Value %s exceeds max allowed value(4 bytes)",
                              tmpStr.c_str());
    }
    parseValue(val, _value, tmpStr);
}

void BinaryParamValue::parseValue(string strToParse, u_int32_t& value, string& strValue)
{
    parseValueAux(strToParse, value, strValue, 16);
}

void BinaryParamValue::trimHexString(string& s)
{
    size_t pos = 0;
    char delimiters[] = {':', '-', ' ', '\n', '\t'};

    for (unsigned int i = 0; i < sizeof(delimiters); i++) {
        while ((pos = s.find(delimiters[i])) != string::npos) {
            s.replace(pos, 1, "");
        }
    }
}

/* StringParamValue Class */
string StringParamValue::getVal()
{
    //convert the integer to a hex string
    return _value;
}

void StringParamValue::setVal(string val)
{
    if (val.length() > _size) {
        throw MlxcfgException("Max allowed size is %d", _size);
    }
    _value = val;
}

void StringParamValue::pack(u_int8_t *buff, u_int32_t bitOffset)
{
    unsigned int i = 0;
    u_int32_t byteOffset = bitOffset / 8;

    for (; i < _value.length(); i++) {
        buff[byteOffset + i] = _value[i];
    }
    if (_value.length() < _size) {
        buff[byteOffset + i] = '\0';
    }
}

void StringParamValue::unpack(u_int8_t *buff, u_int32_t bitOffset)
{
    u_int32_t byteOffset = bitOffset / 8;

    for (unsigned int i = 0; i < _size; i++) {
        if (buff[byteOffset + i] == '\0') {
            break;
        }
        _value += buff[byteOffset + i];
    }
}


/* BytesParamValue Class */
string BytesParamValue::getVal()
{
    string strVal = "";

    VECTOR_ITERATOR(BinaryParamValue, _bytes, binary) {
        strVal += binary->getVal();
    }

    return strVal;
}

void BytesParamValue::setVal(string val)
{
    BinaryParamValue::trimHexString(val);

    //check if DW aligned:
    if (val.length() % 8) {
        throw MlxcfgException("Value is not Dword aligned");
    }

    if (val.length() / 2 > _size) {
        throw MlxcfgException("Value size %d bytes is larger than max size: %d bytes",
                              val.length() / 2,
                              _size);
    }

    u_int32_t i = 0;
    while (i < val.length()) {
        BinaryParamValue b("0x4.0");
        string s = val.substr(i, 8);
        b.setVal(s);
        _bytes.push_back(b);
        i += 8;
    }

}

void BytesParamValue::parseValue(string, u_int32_t&, string&)
{
    throw MlxcfgException("Not supported for BYTES types\n");
}

void BytesParamValue::pack(u_int8_t *buff, u_int32_t bitOffset)
{

    VECTOR_ITERATOR(BinaryParamValue, _bytes, binary) {
        binary->pack(buff, bitOffset);
        bitOffset += 32;
    }
}

void BytesParamValue::unpack(u_int8_t *buff, u_int32_t bitOffset)
{
    VECTOR_ITERATOR(BinaryParamValue, _bytes, binary) {
        binary->unpack(buff, bitOffset);
        bitOffset += 32;
    }
}

void BytesParamValue::setVal(const vector<u_int32_t>& buffVal)
{
    CONST_VECTOR_ITERATOR(u_int32_t, buffVal, it) {
        BinaryParamValue b("0x4.0");
        b.UnsignedParamValue::setVal(*it);
        _bytes.push_back(b);
    }
}



ArrayParamValue::ArrayParamValue(string size, u_int32_t count, enum ParamType paramType) :
    ParamValue(size), _elementSizeInBits(_size / count)
{
    if (_elementSizeInBits != 32 &&
        _elementSizeInBits != 16 &&
        _elementSizeInBits != 8) {
        throw MlxcfgException("The size of the elements of array values must be 1, 2 or 4 bytes.");
    }
    if (paramType == ENUM) {
        return;
    }
    for (u_int32_t i = 0; i < count; i++) {
        ParamValue *t;
        switch (paramType) {
        case UNSIGNED:
            t = new UnsignedParamValue(_elementSizeInBits);
            break;

        case BINARY:
            t = new BinaryParamValue(_elementSizeInBits);
            break;

        default:
            throw MlxcfgException("% is not supported in Array parameters!", Param::paramType2Str(paramType).c_str());
            break;
        }
        _values.push_back(t);
    }
};

ArrayParamValue::~ArrayParamValue()
{
    for (u_int32_t i = 0; i < _values.size(); i++) {
        if (_values[i] != NULL) {
            delete _values[i];
        }
    }
}

u_int32_t ArrayParamValue::getIntVal()
{
    throw MlxcfgException(OPERATION_NOT_SUPPORTED);
}

string ArrayParamValue::getVal()
{
    throw MlxcfgException(OPERATION_NOT_SUPPORTED);
}

void ArrayParamValue::setVal(string /*val*/)
{
    throw MlxcfgException(OPERATION_NOT_SUPPORTED);
}

string ArrayParamValue::getVal(u_int32_t index)
{
    if (index >= _values.size()) {
        //TODO give another message
        throw MlxcfgException("Index %d is out of range", index);
    }
    return _values.at(index)->getVal();
}

void ArrayParamValue::setVal(vector<string> vals)
{
    if (_values.size() != vals.size()) {
        throw MlxcfgException(
                  "The size of the given input %d is not the same as the size of the parameter array %d",
                  vals.size(), _values.size());
    }
    for (u_int32_t i = 0; i < vals.size(); i++) {
        _values[i]->setVal(vals[i]);
    }
}

void ArrayParamValue::setVal(string val, u_int32_t index)
{
    if (index >= _values.size()) {
        throw MlxcfgException("Index %d is out of range", index);
    }
    _values[index]->setVal(val);
}

u_int32_t ArrayParamValue::offsetToBigEndian(u_int32_t offset)
{
    switch (_elementSizeInBits) {
        case  8: return (offset & 0xFFFFFFE7) + 0x18 - (offset & 0x18);
        case 16: return (offset & 0xFFFFFFEF) + 0x10 - (offset & 0x10);
        case 32: return offset;
        default:
            throw MlxcfgException("Element size %d bits is not supported", _elementSizeInBits);
    }
}

void ArrayParamValue::pack(u_int8_t *buff, u_int32_t offset)
{
    /* The FW expect a big endian buffer for both the order of the elements in the array
     * and the values of each element. So if elementsInDW = 2, _values[0] will point to buff[16..31]
     * To understand this piece of code, try to think about these cases:
     * elementsInDW = 1, 2, 4
     */
    vector<ParamValue*>::iterator j;
    for (vector<ParamValue*>::iterator it = _values.begin(); it != _values.end();) {
        int elementsInDW = 32 / _elementSizeInBits;
        j = it + elementsInDW - 1;
        unsigned int iterations = elementsInDW;
        while (iterations) {
            (*j)->pack(buff, offsetToBigEndian(offset));
            offset += _elementSizeInBits;
            iterations--;
            j--;
        }
        it += elementsInDW;
    }
}

void ArrayParamValue::unpack(u_int8_t *buff, u_int32_t offset)
{
    vector<ParamValue*>::iterator j;
    for (vector<ParamValue*>::iterator it = _values.begin(); it != _values.end();) {
        int elementsInDW = 32 / _elementSizeInBits;
        j = it + elementsInDW - 1;
        unsigned int iterations = elementsInDW;
        while (iterations) {
            (*j)->unpack(buff, offsetToBigEndian(offset));
            offset += _elementSizeInBits;
            iterations--;
            j--;
        }
        it += elementsInDW;
    }
}

void ArrayParamValue::parseValue(string strToParse, u_int32_t& val, string& strVal)
{
    _values[0]->parseValue(strToParse, val, strVal);
}

vector<u_int32_t> ArrayParamValue::getIntVals()
{
    vector<u_int32_t> v;
    for (vector<ParamValue*>::iterator it = _values.begin(); it != _values.end(); it++) {
        v.push_back((*it)->getIntVal());
    }
    return v;
}

vector<string> ArrayParamValue::getStrVals()
{
    vector<string> v;
    for (vector<ParamValue*>::iterator it = _values.begin(); it != _values.end(); it++) {
        v.push_back((*it)->getVal());
    }
    return v;
}

EnumArrayParamValue::EnumArrayParamValue(string size, u_int32_t count, enum ParamType paramType,
                                         map<string, u_int32_t> textualValues) : ArrayParamValue(size, count, paramType)
{
    for (u_int32_t i = 0; i < count; i++) {
        ParamValue *t = new EnumParamValue(_elementSizeInBits, textualValues);
        _values.push_back(t);
    }
}
