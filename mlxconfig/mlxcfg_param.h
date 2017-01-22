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

class Param {

    private:
        bool _isNameFound, _isTLVNameFound, _isOffsetFound, _isSizeFound,
             _isTypeFound, _isDescriptionFound, _isTextualValuesFound,
             _isMlxconfigNameFound, _isDependencyFound, _isValidBitFound,
             _isTempVarsFound, _isMinValFound, _isMaxValFound, _isRuleFound,
             _isRegexFound, _isPortFound;
    public:
        std::string _name;
        std::string _tlvName;
        std::string _offset;
        std::string _size;
        enum ParamType _type;
        std::string _description;
        std::map<std::string, u_int32_t> _textualValues;
        std::string _mlxconfigName;
        std::string _dependency;
        std::string _validBit;
        std::string _tempVars;
        std::string _minVal;
        std::string _maxVal;
        std::string _rule;
        std::string _regex;
        u_int32_t _port;
        u_int32_t _value;
        u_int32_t _supportedFromVersion;

        Param(int columnsCount, char **dataRow, char **headerRow);

        std::string getDisplayName();
        void getView(ParamView& paramView);
        void helpAux();
        void pack(u_int8_t* buff);
        void unpack(u_int8_t* buff);
        void setVal(std::string val);
        std::string getVal(u_int32_t);
        std::string getVal();
        void parseBoolValue(std::string valToParse, u_int32_t& val,
                std::string& strVal);
        void parseEnumValue(std::string valToParse, u_int32_t& val,
                std::string& strVal);
        void parseValue(std::string, u_int32_t&, std::string&);

        void extractVars(std::vector<std::string>& rulesVars, std::string rule);
        void getRulesTLV(std::vector<std::string>& rulesTlvs);

        u_int32_t getSizeInBits();

        static enum ParamType str2ParamType(const char* s);
        static void str2TextualValuesMap(const char* s, std::map<std::string, u_int32_t>& m);

        void genXMLTemplate(std::string& xmlTemplate, bool withVal);

};


#endif
