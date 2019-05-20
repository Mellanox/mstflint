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
 * TLV.h
 *
 *  Created on: May 24, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_TLV_H_
#define MLXCFG_TLV_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <mtcr.h>
#include "mlxcfg_param.h"
#include "mlxcfg_view.h"
#include "mlxcfg_utils.h"

#define PORT_ATTR "port"
#define OVR_EN_ATTR "ovr_en"
#define RD_EN_ATTR "rd_en"
#define WRITER_ID_ATTR "writer_id"
#define HOST_ATTR "host"
#define FUNC_ATTR "function"
#define ALL_ATTR_VAL "all"
#define INDEX_ATTR "index"

enum TLVTarget {
    NIC,
    EXP_ROM,
    NIC_INTERNAL,
    SWITCH
};

class TLVConf {

private:
    bool _isNameFound, _isIdFound, _isSizeFound, _isCapFound, _isTargetFound,
         _isClassFound, _isVersion, _isDescriptionFound, _isMlxconfigNameFound,
         _isPortFound;
    Param* getParamByName(std::string n);
    void pack(u_int8_t *buff);
    u_int32_t getGlobalTypeBe();
    u_int32_t getPhysicalPortTypeBe();
    u_int32_t getPerHostFunctionTypeBe();
    u_int32_t getPerHostTypeBe();
    u_int32_t getTlvTypeBe();
    void mnva(mfile *mf, u_int8_t *buff, u_int16_t len, u_int32_t type,
              reg_access_method_t method, QueryType qT = QueryNext);
    static TLVTarget str2TLVTarget(char *s);
    static TLVClass str2TLVClass(char *s);

public:
    std::string _name;
    u_int32_t _id;
    u_int16_t _size;
    bool _cap;
    TLVTarget _target;
    TLVClass _tlvClass;
    u_int32_t _version;
    std::string _description;
    std::vector<Param*> _params;
    std::string _mlxconfigName;
    u_int8_t _port;
    bool _alreadyQueried;
    map<string, string> _attrs;
    vector<u_int8_t> _buff;
    u_int32_t _maxTlvVersionSuppByFw;

    TLVConf(int columnsCount, char **dataRow, char **headerRow);

    bool isMlxconfigSupported();
    void getView(TLVConfView& tlvConfView);
    bool isFWSupported(mfile *mf, bool read_write);
    Param* getValidBitParam(std::string n);
    bool checkParamValidBit(Param *p);
    std::vector<std::pair<ParamView, std::string> > query(mfile *mf, QueryType qT);
    void updateParamByMlxconfigName(std::string param, std::string val);
    void updateParamByMlxconfigName(std::string param, std::string val, u_int32_t index);
    void updateParamByName(string param, string val);
    void updateParamByName(string paramName, vector<string> vals);
    u_int32_t getParamValueByName(std::string n);
    Param* findParamByMlxconfigName(std::string n);
    Param* findParamByName(std::string n);
    void getExprVarsValues(std::vector<std::string>&, std::vector<TLVConf*>,
                           std::map<std::string, u_int32_t>&, std::string);
    void evalTempVars(Param*, std::vector<TLVConf*>,
                      std::map<std::string, u_int32_t>&);
    u_int32_t evalRule(Param*, std::string, std::vector<TLVConf*>&,
                       std::map<std::string, u_int32_t>&);
    void checkRules(std::vector<TLVConf*> ruleTLVs);
    void setOnDevice(mfile *mf);
    void getRuleTLVs(std::set<std::string>& result);
    void parseParamValue(std::string, std::string, u_int32_t&, std::string&, u_int32_t index);
    void unpack(u_int8_t *buff);
    void genXMLTemplate(string& xmlTemplate, bool allAttrs, bool withVal,
                        bool defaultAttrVal);
    void genRaw(string& raw);
    void genBin(vector<u_int32_t>& buff, bool withHeader = true);
    bool isAStringParam(string paramName);
    void setAttr(string attr, string val);
    void invalidate(mfile *mf);
    static void unpackTLVType(TLVClass tlvClass,
                              tools_open_tlv_type& type, u_int32_t& id);
};

#endif /* MLXCFG_TLV_H_ */
