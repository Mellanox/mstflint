
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
 */

#ifndef __MLNX_DEV_H__
#define __MLNX_DEV_H__

#include <compatibility.h>
#include <sstream>
#include <tools_dev_types.h>
#include <img_version.h>
#include "mlxfwmanager_common.h"
#include "mlxconfig/mlxcfg_commander.h"
#ifdef __WIN__
#include "ToolsSyncDefs.h"
#include "ToolsSync.h"
#endif
#define MTCR_EXPORT
#include <mtcr.h>

using namespace std;
#define MLNX_ERR_BUFF_SIZE 1024

class MlnxDev
{
public:
    MlnxDev(dev_info* devinfo, int compare_ffv);
    MlnxDev(const char* devname, int compare_ffv);
    ~MlnxDev();

    int query();
    int preBurn(string mfa_file,
                f_prog_func prog_cb,
                bool burnFailsafe,
                bool& isTimeConsumingFixesNeeded,
                vector<string>& questions,
                f_prog_func_adv stage_prog = (f_prog_func_adv)NULL);
    int burn(bool&);
    bool burnPLDMComponent(FwComponent::comps_ids_t compId, u_int8_t* buff, u_int32_t buffSize);
    bool clearSemaphore();
    int isBurnSuccess();
    int isQuerySuccess();
    int compareFWVer(const ImgVersion& ver);
    string getLastErrMsg();
    string getLog();
    string getDevDisplayName(bool pci_if_possible = false);
    string getDevName();
    string getPsid();
    string getFWVersion(bool show_type = true, bool use_default_ffv = true);
    string getDescription();
    string getPartNumber();
    string getDeviceTypeStr();
    dm_dev_id_t getDeviceType();
    string getBoardTypeId();
    dev_info* getDevInfo();
    void patchPsidInfo(string psid);
    void setDevToNeedUpdate();
    bool doesDevNeedUpdate();
    void setNoFwCtrl();
    void setMccSupport(bool val = true) { _mccSupport = val; };
    vector<ImgVersion> _imageVers;
    inline bool isAlignmentNeeded();
    inline void setShifting8MBInBurnParams(bool v) { _burnParams.shift8MBIfNeeded = v; }

    bool checkExistence(vector<MlnxDev*>& devs);
    string getUniqueId() { return _uniqueId; };
    bool isBFBSupported() { return _bfbSupported; };

public:
    string guidPortOne;
    string guidPortTwo;
    string macPortOne;
    string macPortTwo;
    string systemGuid;
    string nodeGuid;
    typedef enum
    {
        PORT_NA,
        PORT_IB,
        PORT_ETH
    } port_type_t;
    port_type_t portOneType;
    port_type_t portTwoType;
    bool isOnlyBase;

private:
    bool InitDevFWParams(FwOperations::fw_ops_params_t& devFwParams);
    void setDeviceType(void);
    void setGuidMac(fw_info_t& fw_query);
    void _MlnxDevInit(int compare_ffv);
    int getImageIndex(string type);
    int queryFwops();
    bool OpenDev();
    bool openImg(u_int32_t* fileBuffer, u_int32_t bufferSize, u_int16_t swDevId = 0);
    bool openImg(u_int32_t* fileBuffer, u_int32_t bufferSize);
    port_type_t findPortType(int port);
    void initUniqueId();
    bool equals(MlnxDev* dev);
    int LockDevice(FwOperations* fwOps);
    int UnlockDevice(FwOperations* fwOps);

private:
    typedef enum
    {
        INIT_DEVINFO,
        INIT_DEVNAME
    } init_type_t;

    init_type_t _init_type;
    dev_info* _devinfo;
    string _devname;
    int _querySuccess;
    int _burnSuccess;
    string _psid;
    string _productVer;

    string _log;
    string _errMsg;
    string _boardTypeId;
    string _uniqueId;
    FwOperations* _devFwOps;
    FwOperations* _imgFwOps;
    FwOperations::fw_ops_params_t _devFwParams;
    FwOperations::fw_ops_params_t _imgFwParams;
    FwOperations::ExtBurnParams _burnParams;
    bool _imageEncrypted;
    bool _deviceEncrypted;

    Commander* _commander;
    char _errBuff[MLNX_ERR_BUFF_SIZE];
    int _compareFFV;
    int _ExpRomExists;
    bool _needsUpdate;
    bool _noFwCtrl;
    bool _mccSupport;
    string _description;
    string _partNumber;
    string _deviceTypeStr;
    dm_dev_id_t _deviceType;

    bool _preBurnInit;
    int _unknowProgress;
    bool _bfbSupported;

#ifdef __WIN__
    ToolsSync m_ToolsSync;
#endif
};

#endif
