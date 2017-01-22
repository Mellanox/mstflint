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

#define CHECK_IF_FIELD_FOUND(b, s) \
    if(!b) {\
        throw MlxcfgException("The Parameter field %s was not initialized", s);\
    }


#define CHECKFIELD(d, n) \
    if(!d || (strcmp(d, "") == 0)) {\
        throw MlxcfgException("The field: %s, cannot be empty", n);\
    }

Param::Param(int columnsCount, char **dataRow, char **headerRow) :
    _isNameFound(false), _isTLVNameFound(false), _isOffsetFound(false),
    _isSizeFound(false), _isTypeFound(false), _isDescriptionFound(false),
    _isTextualValuesFound(false), _isMlxconfigNameFound(false),
    _isDependencyFound(false), _isValidBitFound(false), _isTempVarsFound(false),
    _isMinValFound(false), _isMaxValFound(false), _isRuleFound(false),
    _isRegexFound(false), _isPortFound(false), _supportedFromVersion(0)
{

    for(int i = 0; i < columnsCount; i++){
        if (strcmp(headerRow[i], PARAM_NAME_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            _name = dataRow[i];
            _isNameFound = true;
        } else if (strcmp(headerRow[i], PARAM_TLVNAME_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            if(!dataRow[i]) {
                throw MlxcfgException("Empty tlv_name field");
            }
            _tlvName = dataRow[i];
            _isTLVNameFound = true;
        } else if (strcmp(headerRow[i], PARAM_OFFSET_HEADER) == 0) {
            CHECKFIELD(dataRow[i], headerRow[i])
            _offset = dataRow[i];
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
            if(dataRow[i] != NULL) {
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

    _value = MLXCFG_UNKNOWN;

    if(_type == ENUM && _textualValues.empty()) {
        throw MlxcfgException(
                "The parameter: %s, "
                "is type of ENUM but there is no any enum provided",
                _name.c_str());
    }

}

u_int32_t Param::getSizeInBits()
{
    u_int32_t bits = 0;
    size_t pos = _size.find('.');

    if (pos != string::npos) {
        bits += atoi(_size.substr(pos + 1).c_str());
    }
    bits += (8 * strtol(_size.substr(0, pos).c_str(), NULL, 0));
    return bits;
}

void Param::pack(u_int8_t* buff)
{
    //printf("-D- param = %s val=%d\n", _name.c_str(), _value);
    u_int32_t bit_offset;
    u_int32_t bits_size;
    u_int32_t pos;

    pos = _size.find('.');
    bits_size = atoi(_size.substr(pos + 1).c_str()) + 8 * strtol(_size.substr(0, pos).c_str(), NULL, 0);

    pos = _offset.find('.');
    bit_offset = 8 * strtol(_offset.substr(0, pos).c_str(), NULL, 0) + atoi(_offset.substr(pos + 1).c_str());
    bit_offset = 32 - bit_offset % 32 - bits_size + ((bit_offset >> 5) << 5);

    adb2c_push_bits_to_buff(buff, bit_offset, bits_size, _value);
}

void Param::unpack(u_int8_t* buff)
{
    u_int32_t bit_offset;
    u_int32_t bits_size;
    u_int32_t pos;

    pos = _size.find('.');
    bits_size = atoi(_size.substr(pos + 1).c_str()) + 8 * strtol(_size.substr(0, pos).c_str(), NULL, 0);

    pos = _offset.find('.');
    bit_offset = 8 * strtol(_offset.substr(0, pos).c_str(), NULL, 0) + atoi(_offset.substr(pos + 1).c_str());
    bit_offset = 32 - bit_offset % 32 - bits_size + ((bit_offset >> 5) << 5);

    _value = adb2c_pop_bits_from_buff(buff, bit_offset, bits_size);

    //printf("param=%s bits_size=%d bit_offset=%d\n", _name.c_str(), bits_size, bit_offset);
    //_value = adb2c_pop_bits_from_buff_le(buff, bit_offset, bits_size);
}

void Param::setVal(string val)
{
    string s;
    parseValue(val, _value, s);
}

string Param::getVal()
{
    return getVal(_value);
}

string Param::getVal(u_int32_t v)
{
    string strVal;
    stringstream ss;
    map<string, u_int32_t>::const_iterator it;

    //convert int to string
    ss << v;
    strVal = ss.str();

    if(_type == BOOLEAN_TYPE) {
        switch(v){
            case 0:
                return DISABLED;
            case 1:
                return ENABLED;
            default:
                return strVal;
        }
    }

    if(_type == ENUM) {
        //printf("-D- textual values size = %u\n", (unsigned int)_textualValues.size());
        for(it = _textualValues.begin(); it != _textualValues.end(); ++it) {
            //printf("-D- textual value - %s=%d\n", it->first.c_str(), it->second);
            if(it->second == v) {
                return it->first;
            }
        }
        //its enum and we did not find the mapping of the value, so what to do?
        //do not throw exception, print the value as it
    }

    return strVal;
}

void Param::getView(ParamView& paramView)
{
    paramView.mlxconfigName = _mlxconfigName;
    paramView.description = _description;
    paramView.type = _type;
    paramView.textualVals = _textualValues;
    paramView.val = _value;
    paramView.strVal = getVal();
}

string Param::getDisplayName()
{
    string displayName = _name;
    displayName += (_mlxconfigName.empty()) ? "" : ("(" + _mlxconfigName + ")");
    return displayName;
}

void Param::parseBoolValue(string valToParse, u_int32_t& val, string& strVal)
{
    if (strToNum(valToParse, val)) {
        switch(val) {
            case 0:
                strVal=DISABLED;
                return;
            case 1:
                strVal = ENABLED;
                return;
        }
    } else {
        if (strcasecmp(valToParse.c_str(), ENABLED) == 0) {
            val = 1;
            strVal = ENABLED;
            return;
        } else if (strcasecmp(valToParse.c_str(), DISABLED) == 0) {
            val = 0;
            strVal = DISABLED;
            return;
        }
    }
    throw MlxcfgException("Value %s is not valid, must be " DISABLED "(0) or "
                                ENABLED "(1)", valToParse.c_str());
}

void Param::parseEnumValue(string valToParse, u_int32_t& val, string& strVal)
{
    map<string, u_int32_t>::const_iterator it;
    //try to convert to int
    if (strToNum(valToParse, val)) {
        //try to find enum for val:
        for(it = _textualValues.begin(); it != _textualValues.end(); ++it) {
            //printf("-D- textual value - %s=%d\n", it->first.c_str(), it->second);
            if(it->second == val) {
                strVal = it->first;
                return;
            }
        }
    } else {
        for(it = _textualValues.begin(); it != _textualValues.end(); ++it) {
            if (strcasecmp(it->first.c_str(), valToParse.c_str()) == 0) {
                val = it->second;
                strVal = valToParse;
                return;
            }
        }
    }
    throw MlxcfgException("The value %s of the parameter %s is not valid",
                              valToParse.c_str(), getDisplayName().c_str());

}

void Param::parseValue(string valToParse, u_int32_t& val, string& strVal)
{
    u_int32_t bitsSize;
    if (_type == BOOLEAN_TYPE) {
        parseBoolValue(valToParse, val, strVal);
        return;
    } else if (_type == ENUM) {
        parseEnumValue(valToParse, val, strVal);
        return;
    } else if (strToNum(valToParse, val)) { //try to convert val to int
        strVal = valToParse;
        bitsSize = getSizeInBits();
        if ((bitsSize == 32 && val == MLXCFG_UNKNOWN) || ((bitsSize != 32) && val > (unsigned)((1 << bitsSize) - 1))) {
            throw MlxcfgException("The value %s of the parameter %s is not valid,"
                                      " as its size is %d bits",
                                      valToParse.c_str(), getDisplayName().c_str(), bitsSize);
        }
        return;
    }
    throw MlxcfgException("Cannot parse the value %s of the parameter %s", valToParse.c_str(), getDisplayName().c_str());
}

ParamType Param::str2ParamType(const char* s)
{
    if(strcmp(s, "BOOL") == 0) {
        return BOOLEAN_TYPE;
    } else if(strcmp(s, "ENUM") == 0) {
        return ENUM;
    } else if(strcmp(s, "INTEGER") == 0) {
        return INTEGER;
    } else if(strcmp(s, "UNSIGNED") == 0) {
        return UNSIGNED;
    } else if(strcmp(s, "STRING") == 0) {
        return STRING;
    }
    throw MlxcfgException("Unknown parameter type '%s'", s);
}

//split a string by comma, updates result vector with all sub-strings
void splitByComma(const char* s, vector<string>& result)
{
    int len = strlen(s);
    string e2v = "";

    for(int i = 0; i < len; i++){
        if (s[i] == ','){
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
    for(unsigned int i = 0; i < rule.size(); i++) {
        if(rule[i] == '$') {
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
    for(unsigned int i = 0; i < vars.size(); i++) {
        size_t pos = vars[i].find('.');
        if (pos == string::npos) {
            continue;
        }
        //printf("-D- tlv=%s", vars[i].substr(0, pos).c_str());
        result.push_back(vars[i].substr(0, pos));
    }
}

void Param::str2TextualValuesMap(const char* s, map<string, u_int32_t>& m)
{
    u_int32_t v;
    string e, e2v;
    vector<string> e2vVector;

    //printf("-D- textual_values=%s\n", s);

    //first split the string by comma
    splitByComma(s, e2vVector);

    //extract the enum and update the map with this enum and its value
    for(size_t i = 0; i < e2vVector.size(); i++){
        e2v = e2vVector[i];
        e = "";
        extractEnumAndValue(e2v, e, v);
        m[e] = v;
    }
}

void Param::genXMLTemplate(std::string& xmlTemplate, bool withVal)
{
    if (_type == ENUM) {
        xmlTemplate += "<!-- Legal Values:";
        std::map<string,u_int32_t>::iterator tv = _textualValues.begin();
        xmlTemplate += tv->first;
        tv++;
        for(; tv != _textualValues.end(); tv++) {
            xmlTemplate += "|" + tv->first;
        }
        xmlTemplate += " -->\n";
    } else if (_type == BOOLEAN_TYPE) {
        xmlTemplate += "<!-- Legal Values: " DISABLED "/" ENABLED " -->\n";
    }
    xmlTemplate += "<" + _name + ">" +
            (withVal ? getVal() : "") +
            "</" + _name + ">";
}
