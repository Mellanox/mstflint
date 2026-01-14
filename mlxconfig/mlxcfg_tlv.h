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
#include <memory>
#include "mlxcfg_param.h"
#include "mlxcfg_view.h"
#include "mlxcfg_utils.h"

#define PORT_ATTR "port"
#define MODULE_ATTR "module"
#define OVR_EN_ATTR "ovr_en"
#define RD_EN_ATTR "rd_en"
#define PRIORITY_ATTR "priority"
#define USER_PRIORITY_ATTR "USER"
#define OEM_PRIORITY_ATTR "OEM"
#define MLNX_PRIORITY_ATTR "MLNX"
#define WRITER_ID_ATTR "writer_id"
#define HOST_ATTR "host"
#define FUNC_ATTR "function"
#define ALL_ATTR_VAL "all"
#define INDEX_ATTR "index"

/* Forward declaration */
union tools_open_tlv_type;
/* End of forward declaration */

enum TLVTarget
{
    NIC,
    EXP_ROM,
    NIC_INTERNAL,
    SWITCH
};

class TLVConf
{
private:
    bool _isNameFound, _isIdFound, _isSizeFound, _isCapFound, _isTargetFound, _isClassFound, _isVersion,
      _isDescriptionFound, _isMlxconfigNameFound;
    std::shared_ptr<Param> getParamByName(std::string n, QueryType qt);
    void pack(u_int8_t* buff, QueryType qt);
    u_int32_t getGlobalTypeBe();
    u_int32_t getPhysicalPortTypeBe();
    u_int32_t getPerHostFunctionTypeBe();
    u_int32_t getPerHostTypeBe();
    u_int32_t getModuleTypeBe();
    u_int32_t getTlvTypeBe();
    bool mnvda(mfile* mf,
               u_int8_t* buff,
               u_int16_t len,
               u_int32_t type,
               reg_access_method_t method,
               QueryType qT = QueryNext);
    static TLVTarget str2TLVTarget(char* s);
    static TLVClass str2TLVClass(char* s);

public:
    std::string _name;
    u_int32_t _id;
    u_int16_t _size;
    bool _cap;
    TLVTarget _target;
    TLVClass _tlvClass;
    u_int32_t _version;
    std::string _description;
    std::vector<std::shared_ptr<Param>> _paramsDefault;
    std::vector<std::shared_ptr<Param>> _paramsCurrent;
    std::vector<std::shared_ptr<Param>> _paramsNext;
    bool _paramsDefaultQueried;
    bool _paramsCurrentQueried;
    bool _paramsNextQueried;
    std::string _mlxconfigName;
    u_int32_t _port;
    int32_t _module;
    u_int8_t _hostId;
    u_int8_t _pfIndex;
    bool _isHostIdValid;
    bool _alreadyQueried;
    map<string, string> _attrs;
    vector<u_int8_t> _buff;
    u_int32_t _maxTlvVersionSuppByFw;
    bool _isReadOnly;

    TLVConf(int columnsCount, char** dataRow, char** headerRow);
    ~TLVConf();
    bool isMlxconfigSupported();
    std::vector<std::shared_ptr<Param>>* getParams(QueryType qt);
    void invalidateParamsQueried();
    bool* getParamsQueried(QueryType qt);
    void getView(TLVConfView& tlvConfView, QueryType qt);
    bool isFWSupported(mfile* mf, bool isWriteOperation);
    std::shared_ptr<Param> getValidBitParam(std::string n, QueryType qt);
    bool checkParamValidBit(std::shared_ptr<Param> p, QueryType qt);
    std::vector<std::pair<ParamView, std::string>> query(mfile* mf, QueryType qT);
    void updateParamByMlxconfigName(std::string param, std::string val, mfile* mf, QueryType qt);
    void updateParamByMlxconfigName(std::string param, std::string val, u_int32_t index, QueryType qt);
    void updateParamByName(string param, string val, QueryType qt);
    void updateParamByName(string paramName, vector<string> vals, QueryType qt);
    u_int32_t getParamValueByName(std::string n, QueryType qt);
    std::shared_ptr<Param> findParamByMlxconfigName(std::string mlxconfigName, QueryType qt);
    std::shared_ptr<Param>
      findParamByMlxconfigNamePortModule(std::string mlxconfigName, u_int32_t port, int32_t tlvModule, QueryType qt);
    std::shared_ptr<Param> findParamByName(std::string n, QueryType qt);
    void CheckModuleAndPortMatchClass(int32_t tlvModule, u_int32_t port, std::string mlxconfigName);
    void getExprVarsValues(std::vector<std::string>&,
                           std::vector<std::shared_ptr<TLVConf>>,
                           std::map<std::string, u_int32_t>&,
                           std::string,
                           QueryType qt);
    void evalTempVars(std::shared_ptr<Param>,
                      std::vector<std::shared_ptr<TLVConf>>,
                      std::map<std::string, u_int32_t>&,
                      QueryType qt);
    u_int32_t evalRule(std::shared_ptr<Param>,
                       std::string,
                       std::vector<std::shared_ptr<TLVConf>>&,
                       std::map<std::string, u_int32_t>&,
                       QueryType qt);
    void checkRules(std::vector<std::shared_ptr<TLVConf>>, QueryType qt);
    void setOnDevice(mfile* mf);
    void getRuleTLVs(std::set<std::string>& result);
    void parseParamValue(std::string, std::string, u_int32_t&, std::string&, u_int32_t index, QueryType qt);
    void unpack(u_int8_t* buff, QueryType qt);
    void genXMLTemplate(string& xmlTemplate, bool allAttrs, bool withVal, bool defaultAttrVal, bool confFormat = false);
    void genRaw(string& raw);
    void genBin(vector<u_int32_t>& buff, bool withHeader = true, QueryType qt = QueryNext);
    bool isAStringParam(string paramName);
    bool isPortTargetClass();
    bool isModuleTargetClass();
    bool isHostTargetClass();
    // Create a deep copy of TLVConf, including deep copies of parameter vectors
    std::shared_ptr<TLVConf> cloneDeep() const;
    static int getMaxPort(mfile* mf);
    static int getMaxModule();
    void setAttr(string attr, string val);
    void invalidate(mfile* mf);
    static void unpackTLVType(TLVClass tlvClass, tools_open_tlv_type& type, u_int32_t& id);
    bool areParamsEqual(TLVConf& rhsTLV, QueryType qt);
};

int PriorityStrToNum(string priority);
string PriorityNumToStr(u_int8_t priority);

#endif /* MLXCFG_TLV_H_ */
