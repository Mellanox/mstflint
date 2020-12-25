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
 * mlxcfg_commander.h
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_COMMANDER_H_
#define MLXCFG_COMMANDER_H_

#include <vector>
#include "mlxcfg_view.h"
#include "mlxcfg_utils.h"

class Commander {

public:
    static Commander* create(std::string device, std::string dbName);
    static Commander* create(mfile *mf, std::string device, std::string dbName);
    virtual void printLongDesc(FILE*) = 0;
    virtual bool isDefaultSupported() = 0;
    virtual bool isCurrentSupported() = 0;
    virtual void queryParamViews(std::vector<ParamView>& paramsToQuery,
                                 QueryType qt = QueryNext) = 0;
    virtual void queryAll(std::vector<ParamView>& params, vector<string>& failedTLVs,
                          QueryType qt = QueryNext) = 0;
    virtual void getCfg(ParamView& cfgParam, QueryType qt = QueryNext) = 0;
    virtual void setCfg(std::vector<ParamView>&, bool) = 0;
    virtual void clearSemaphore() = 0;
    virtual void invalidateCfgs() = 0;
    virtual const char* loadConfigurationGetStr() = 0;
    virtual void setRawCfg(std::vector<u_int32_t> rawTlvVec) = 0;
    virtual std::vector<u_int32_t> getRawCfg(std::vector<u_int32_t> rawTlvVec) = 0;
    virtual void dumpRawCfg(std::vector<u_int32_t> rawTlvVec,
                            std::string& tlvDump) = 0;
    virtual void backupCfgs(vector<BackupView>& views) = 0;
    virtual void updateParamViewValue(ParamView&, std::string val) = 0;
    void setExtResourceType(bool extT) { _extResource = extT; }
    static string getDefaultDBName(bool isSwitch);
    mfile* mf() { return _mf;}
    Commander(mfile *mf) : _mf(mf), _extResource(true), _isSwitch(false) {};
    virtual ~Commander();

protected:
    mfile *_mf;
    bool _extResource;
    bool _isSwitch;
};
#endif /* MLXCFG_COMMANDER_H_ */
