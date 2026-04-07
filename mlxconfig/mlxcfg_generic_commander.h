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
 * mlxcfg_generic_commander.h
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_GENERIC_COMMANDER_H_
#define MLXCFG_GENERIC_COMMANDER_H_

#include <errmsg.h>
#include <tools_layouts/tools_open_layouts.h>

#include "fw_comps_mgr/fw_comps_mgr.h"

#include "mlxcfg_commander.h"
#include "mlxcfg_db_manager.h"

#define BIN_FILE_FINGERPRINT "MLNX.CONFIG.BIN!"
#define BIN_FILE_FINGERPRINT_SIZE 16 // bytes

class GenericCommander : public Commander
{
private:
    MlxcfgDBManager* _dbManager;
    Device_Type _deviceType;

    void supportsNVData();
    void printEnums(const ParamView& p, string& s);
    bool checkDependency(std::shared_ptr<TLVConf> cTLV, string dStr);
    void filterByDependency(std::shared_ptr<TLVConf> cTLV,
                            const vector<pair<ParamView, string>>& dependencyTable,
                            vector<ParamView>& result);
    void
      queryTLV(std::shared_ptr<TLVConf> conf, std::vector<ParamView>& paramsConf, bool isWriteOperation, QueryType qt);
    void getAllConfigurations(std::vector<TLVConfView>& confs);
    void excludeDuplicatedTLVs(vector<TLVConfView>& s, vector<TLVConfView>& d);
    void printTLVConfViews(FILE* f, vector<TLVConfView>& v);
    void printParamViews(FILE* f, vector<ParamView>& v);
    void genXMLTemplateAux(vector<string> tlvs, string& xmlTemplate, bool allAttrs, bool withVal, bool defaultAttrVal);
    void removeSignatureTlvs(vector<std::shared_ptr<TLVConf>>& tlvs);

public:
    GenericCommander(mfile* mf, string& dbName, Device_Type deviceType = Device_Type::HCA);
    ~GenericCommander() override;
    void printLongDesc(FILE*) override;
    void setHostFunctionParams(u_int8_t hostId, u_int8_t pfIndex, bool valid) override;
    void updateDBWithHostPF(u_int8_t hostId, u_int8_t pfIndex) override;
    void
      queryParamViews(std::vector<ParamView>& paramsToQuery, bool isWriteOperation, QueryType qt = QueryNext) override;
    void queryAll(vector<ParamView>& params, vector<string>& failedTLVs, QueryType qt) override;
    void getCfg(ParamView& cfgParam, QueryType qt = QueryNext) override;
    void setCfg(std::vector<ParamView>& params, bool force) override;
    void getGlobalCapabilities(bool& isDefaultSupported,
                               bool& isCurrentSupported,
                               bool& isPrivNvOtherHostSupported) override;
    void clearSemaphore() override;
    void invalidateCfgs() override;
    void invalidateCfg(const std::string& configName) override;
    void invalidateCfg(const std::vector<ParamView>& params) override;
    bool isDPUEnabled();
    bool shouldSkipPrepareReset();
    const char* loadConfigurationGetStr() override;
    void setRawCfg(std::vector<u_int32_t> rawTlvVec) override;
    std::vector<u_int32_t> getRawCfg(std::vector<u_int32_t> rawTlvVec) override;
    void dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump) override;
    void backupCfgs(vector<BackupView>& view) override;
    void updateParamViewValue(ParamView& p, std::string v, QueryType qt) override;
    void queryConfigViews(std::vector<TLVConfView>& confs, const std::string& configName = "", QueryType qt = QueryNext);

    void
      getConfigViews(std::vector<TLVConfView>& confs, const std::string& configName = "", QueryType qt = QueryCurrent);

    void genTLVsList(vector<string>& tlvs);
    void genXMLTemplate(vector<string> tlvs, string& xmlTemplate, bool allAttrs);
    void genXMLFromTLVConf(vector<std::shared_ptr<TLVConf>>& tlvsConfs, string& xmlTemplate, bool allAttrs);
    void TLVs2TLVConfs(const vector<string>& tlvs, vector<std::shared_ptr<TLVConf>>& tlvsConfs);
    void XML2TLVConf(const string& xmlContent, vector<std::shared_ptr<TLVConf>>& tlvs);
    void binTLV2XML(const vector<u_int32_t>& binTLV, string& xml);
    void binTLV2TLVConf(const vector<u_int32_t>& binTLV, std::shared_ptr<TLVConf>& tlv);
    void bin2TLVConfs(const vector<u_int32_t>& tlvsBin, vector<std::shared_ptr<TLVConf>>& tlvs);
    void raw2XML(const vector<string>& lines, string& xml);
    void XML2Raw(const string& xml, string& raw);
    void XML2Bin(const string& xml, vector<u_int32_t>& buff, bool withHeader = true);
    void TLVConf2Bin(const vector<std::shared_ptr<TLVConf>>& tlvs, vector<u_int32_t>& buff, bool withHeader = true);
    void checkConfTlvs(const vector<std::shared_ptr<TLVConf>>& tlvs, FwComponent::comps_ids_t& compsId);
    void orderConfTlvs(vector<std::shared_ptr<TLVConf>>& tlvs);
    void createConf(const string& xml, vector<u_int32_t>& buff);
    void sign(vector<u_int32_t>& buff,
              const string& privateKeyFile = "",
              const string& keyPairUUid = "");
    void apply(const vector<u_int8_t>& buff);
};

class RawCfgParams5thGen : public ErrMsg
{
public:
    RawCfgParams5thGen();
    ~RawCfgParams5thGen() {}
    int setRawData(const std::vector<u_int32_t>& tlvBuff);
    std::vector<u_int32_t> getRawData();
    int setOnDev(mfile* mf, RawTlvMode mode);
    std::string dumpTlv();

private:
    int verifyTlv();
    std::vector<u_int32_t> _tlvBuff;
    struct tools_open_mnvda _nvdaTlv;
};

#endif /* MLXCFG_GENERIC_COMMANDER_H_ */
