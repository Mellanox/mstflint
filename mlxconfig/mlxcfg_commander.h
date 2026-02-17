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
 * mlxcfg_commander.h
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_COMMANDER_H_
#define MLXCFG_COMMANDER_H_

#include <map>
#include <memory>
#include <vector>
#include "tools_dev_types.h"
#include "mlxcfg_configuration.h"
#include "mlxcfg_view.h"
#include "mlxcfg_utils.h"
#include "mlxcfg_status.h"

class Commander
{
public:
    static Commander* create(std::string device,
                             std::string& dbName,
                             bool forceCreate = false,
                             Device_Type deviceType = Device_Type::HCA,
                             bool useMaxPort = false); // clients can force create skipping any
                                                       // support check, and move the responsibility
                                                       // to the client.
    static Commander*
      create(mfile* mf, std::string& dbName, Device_Type deviceType = Device_Type::HCA, bool useMaxPort = false);
    virtual void printLongDesc(FILE*) = 0;
    virtual void
      getGlobalCapabilities(bool& isDefaultSupported, bool& isCurrentSupported, bool& isPrivNvOtherHostSupported) = 0;
    virtual void updateDBWithHostPF(u_int8_t hostId, u_int8_t pfIndex) = 0;
    virtual void
      queryParamViews(std::vector<ParamView>& paramsToQuery, bool isWriteOperation, QueryType qt = QueryNext) = 0;
    virtual void queryAll(vector<ParamView>& params, vector<string>& failedTLVs, QueryType qt) = 0;
    virtual void getCfg(ParamView& cfgParam, QueryType qt = QueryNext) = 0;
    virtual void setCfg(std::vector<ParamView>&, bool) = 0;
    virtual void clearSemaphore() = 0;
    virtual void invalidateCfgs() = 0;
    virtual void invalidateCfg(const std::string& configName) = 0;
    virtual void invalidateCfg(const std::vector<ParamView>& params) = 0;
    virtual const char* loadConfigurationGetStr() = 0;
    virtual void setRawCfg(std::vector<u_int32_t> rawTlvVec) = 0;
    virtual std::vector<u_int32_t> getRawCfg(std::vector<u_int32_t> rawTlvVec) = 0;
    virtual void dumpRawCfg(std::vector<u_int32_t> rawTlvVec, std::string& tlvDump) = 0;
    virtual void backupCfgs(vector<BackupView>& views) = 0;
    virtual void updateParamViewValue(ParamView&, std::string val, QueryType qt) = 0;
    virtual std::shared_ptr<SystemConfiguration>
      getSystemConfiguration(const std::string& name, int32_t asicNumber, const std::string& deviceName) = 0;
    virtual std::vector<std::shared_ptr<SystemConfiguration>>
      getSystemConfigurationsByName(const std::string& name, const std::string& deviceName) = 0;
    virtual std::map<std::string, std::vector<std::shared_ptr<SystemConfiguration>>>
      getAllSystemConfigurations(const std::string& deviceName) = 0;
    void setExtResourceType(bool extT) { _extResource = extT; }
    void setIgnoreWriteSupport(bool ignore) { _ignoreWriteSupport = ignore; }
    virtual void setHostFunctionParams(u_int8_t hostId, u_int8_t pfIndex, bool valid);
    static string getDefaultDBName(bool isSwitch);
    mfile* mf() { return _mf; }
    Commander(mfile* mf) : _mf(mf), _extResource(true), _isSwitch(false), _ignoreWriteSupport(false){};
    virtual ~Commander();

protected:
    mfile* _mf;
    bool _extResource;
    bool _isSwitch;
    bool _ignoreWriteSupport;
    u_int8_t _userHostId = 0;
    u_int8_t _userPfIndex = 0;
    bool _userHostIdPfValid = false;
};
#endif /* MLXCFG_COMMANDER_H_ */
