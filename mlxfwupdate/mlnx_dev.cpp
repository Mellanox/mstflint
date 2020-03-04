
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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

#define MTCR_EXPORT
#include "mlnx_dev.h"
#include <sstream>
#include <iomanip>

#include <dirent.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "image_access.h"
#include "mvpd/mvpd.h"

#if !defined(__WIN__) && !defined(__FreeBSD__)
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/sockios.h>
#include <linux/if.h>


#define ETHTOOL_GDRVINFO        0x00000003 /* Get driver info. */
#define ETHTOOL_FWVERS_LEN      32
#define ETHTOOL_BUSINFO_LEN     32


struct ethtool_drvinfo {
    __u32 cmd;
    char driver[32];            /* driver short name, "tulip", "eepro100" */
    char version[32];           /* driver version string */
    char fw_version[ETHTOOL_FWVERS_LEN];        /* firmware version string */
    char bus_info[ETHTOOL_BUSINFO_LEN];         /* Bus info for this IF. */
    /* For PCI devices, use pci_name(pci_dev). */
    char reserved1[32];
    char reserved2[12];
    __u32 n_priv_flags;         /* number of flags valid in ETHTOOL_GPFLAGS */
    __u32 n_stats;              /* number of u64's from ETHTOOL_GSTATS */
    __u32 testinfo_len;
    __u32 eedump_len;           /* Size of data from ETHTOOL_GEEPROM (bytes) */
    __u32 regdump_len;          /* Size of data from ETHTOOL_GREGS (bytes) */
};
#endif

using namespace std;


void MlnxDev::initUniqueId()
{
    mfile *mf = mopen(getDevName().c_str());
    if (!mf) {
        return;
    }
    vpd_result_t *vpdP = NULL;
    if (mvpd_read(mf, &vpdP, VPD_RO) == 0 && vpdP != NULL) {
        int i = 0;
        string pn;
        string sn;
        while (i < vpdP->ro_fields_size) {
            string id = string(vpdP->ro_fields[i].id);
            if (id == "PN") {
                pn = string(vpdP->ro_fields[i].data);
            } else if (id == "SN") {
                sn = string(vpdP->ro_fields[i].data);
            }
            i++;
        }
        _uniqueId = pn + "_" + sn;
        mvpd_result_free(vpdP);
    }
    mclose(mf);
}

void MlnxDev::_MlnxDevInit(int compare_ffv)
{
    _compareFFV = compare_ffv;
    _querySuccess = 0;
    _burnSuccess  = -1;
    _ExpRomExists = 0;
    _needsUpdate  = false;
    _devFwOps     = NULL;
    _imgFwOps     = NULL;
    _description  = "";
    guidPortOne  = "N/A";
    guidPortTwo  = "N/A";
    macPortOne   = "N/A";
    macPortTwo   = "N/A";
    _deviceTypeStr = "N/A";
    _deviceType   = DeviceUnknown;
    memset(&_devFwParams, 0, sizeof(_devFwParams));
    memset(&_imgFwParams, 0, sizeof(_imgFwParams));
    portOneType = PORT_NA;
    portTwoType = PORT_NA;
    _partNumber  = "";
    isOnlyBase   = false;
    _commander = NULL;
    _noFwCtrl  = false;
    _mccSupport = true;
    _preBurnInit = false;
    _uniqueId = "NA";
    _unknowProgress = 0;
    initUniqueId();
    setDeviceType();
}


MlnxDev::MlnxDev(dev_info *devinfo, int compare_ffv)
{
    _init_type = INIT_DEVINFO;
    _devinfo = devinfo;
    _MlnxDevInit(compare_ffv);
    memset(_errBuff, 0, sizeof(_errBuff));
}


MlnxDev::MlnxDev(const char *devname, int compare_ffv)
{
    _devinfo = NULL;
    _init_type = INIT_DEVNAME;
    _devname = devname;
    _MlnxDevInit(compare_ffv);

}

void MlnxDev::setGuidMac(fw_info_t &fw_query)
{
    bool isFs2  = (fw_query.fw_type == FIT_FS2) ? true : false;
    char buff[512] = {0};
    string mac_format   = "%4.4x%8.8x";
    string guild_format = "%8.8x%8.8x";
    if (_deviceType == DeviceUnknown) {
        return;
    }
    if (isFs2) {
        if (fw_query.fs2_info.guid_num < 3) {
            return;
        }
        if (fw_query.fs2_info.guid_num < 6) {
            if (fw_query.fs2_info.guids[1].h || fw_query.fs2_info.guids[1].l) {
                snprintf(buff, sizeof(buff) - 1, guild_format.c_str(),
                         fw_query.fs2_info.guids[1].h, fw_query.fs2_info.guids[1].l);
                guidPortOne = (string)buff;
            }
            if (fw_query.fs2_info.guids[2].h || fw_query.fs2_info.guids[2].l) {
                snprintf(buff, sizeof(buff) - 1, guild_format.c_str(),
                         fw_query.fs2_info.guids[2].h, fw_query.fs2_info.guids[2].l);
                guidPortTwo = (string)buff;
            }
        } else {
            if (portOneType == PORT_ETH) {
                if (fw_query.fs2_info.guids[4].h || fw_query.fs2_info.guids[4].l) {
                    snprintf(buff, sizeof(buff) - 1, mac_format.c_str(),
                             fw_query.fs2_info.guids[4].h, fw_query.fs2_info.guids[4].l);
                    macPortOne = (string)buff;
                }
            } else if (portOneType == PORT_IB) {
                if (fw_query.fs2_info.guids[1].h || fw_query.fs2_info.guids[1].l) {
                    snprintf(buff, sizeof(buff) - 1, guild_format.c_str(),
                             fw_query.fs2_info.guids[1].h, fw_query.fs2_info.guids[1].l);
                    guidPortOne = (string)buff;
                }
            }

            if (portTwoType == PORT_ETH) {
                if (fw_query.fs2_info.guids[5].h || fw_query.fs2_info.guids[5].l) {
                    snprintf(buff, sizeof(buff) - 1, mac_format.c_str(),
                             fw_query.fs2_info.guids[5].h, fw_query.fs2_info.guids[5].l);
                    macPortTwo = (string)buff;
                }
            } else if (portTwoType == PORT_IB) {
                if (fw_query.fs2_info.guids[2].h || fw_query.fs2_info.guids[2].l) {
                    snprintf(buff, sizeof(buff) - 1, guild_format.c_str(),
                             fw_query.fs2_info.guids[2].h, fw_query.fs2_info.guids[2].l);
                    guidPortTwo = (string)buff;
                }
            }
        }
    } else {
        if (fw_query.fs3_info.fs3_uids_info.valid_field) {
            snprintf(buff, sizeof(buff) - 1, "%016" U64H_FMT_GEN,
                     fw_query.fs3_info.fs3_uids_info.cx4_uids.base_guid.uid);

        } else {
            snprintf(buff, sizeof(buff) - 1, "%016" U64H_FMT_GEN,
                     fw_query.fs3_info.fs3_uids_info.cib_uids.guids[0].uid);
        }
        if (fw_query.fs3_info.fs3_uids_info.cib_uids.guids[0].uid ||
            fw_query.fs3_info.fs3_uids_info.cx4_uids.base_guid.uid) {
            guidPortOne = (string)buff;
        }
        if (fw_query.fs3_info.fs3_uids_info.valid_field) {
            snprintf(buff, sizeof(buff) - 1, "%012" U64H_FMT_GEN,
                     fw_query.fs3_info.fs3_uids_info.cx4_uids.base_mac.uid);
            if (fw_query.fs3_info.fs3_uids_info.cx4_uids.base_mac.uid) {
                macPortOne = (string)buff;
            }
            sprintf(buff, " ");
        } else {
            snprintf(buff, sizeof(buff) - 1, "%016" U64H_FMT_GEN,
                     fw_query.fs3_info.fs3_uids_info.cib_uids.guids[1].uid);
        }
        if (fw_query.fs3_info.fs3_uids_info.cx4_uids.base_mac.uid ||
            fw_query.fs3_info.fs3_uids_info.cib_uids.guids[1].uid) {
            guidPortTwo = (string)buff;
        }
    }
//    printf("Guild 1 : %s\n", guidPortOne.c_str());
//    printf("Guild 2 : %s\n", guidPortTwo.c_str());
//    printf("MAC   1 : %s\n", macPortOne.c_str());
//    printf("MAC   2 : %s\n", macPortTwo.c_str());
}

bool MlnxDev::clearSemaphore()
{
    bool clearSemaphore = true;
    bool overRideCacheReplacement = false;
    int numberOfBanks = -1;
    FBase *io = new Flash;
    if (io == NULL) {
        _errMsg  = "could not allocate io flash";
        _log    += _errMsg;
        return false;
    }
    if (!((Flash*)io)->open(getDevDisplayName().c_str(), clearSemaphore, false, numberOfBanks,
                            NULL, overRideCacheReplacement)) {
        // if we have Hw_Access command we dont fail straght away

        _errMsg = (io)->err();
        _log    += _errMsg;
        delete io;
        return false;
    }
    (io)->close();
    delete io;
    return true;
}

MlnxDev::~MlnxDev()
{

    if (_devFwOps) {
        _devFwOps->FwCleanUp();
        delete _devFwOps;
        _devFwOps = NULL;
    }
    if (_imgFwOps) {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = NULL;
    }
}


bool MlnxDev::doesDevNeedUpdate()
{
    return _needsUpdate;
}


MlnxDev::port_type_t MlnxDev::findPortType(int port)
{
    ParamView pv;
    pv.mlxconfigName = "LINK_TYPE_P1";
    if (port == 2) {
        pv.mlxconfigName = "LINK_TYPE_P2";
    }
    if (!_commander) {
        return PORT_NA;
    }
    try {
        _commander->getCfg(pv);
    } catch (MlxcfgException& e) {
        return PORT_NA;
    }
    if (pv.val == 2) {
        return PORT_ETH;
    } else if (pv.val == 1) {
        return PORT_IB;
    } else {
        return PORT_NA;
    }
}

void MlnxDev::setDeviceType(void)
{
    dm_dev_id_t ptr_dm_dev_id = DeviceUnknown;
    u_int32_t ptr_hw_dev_id = 0;
    u_int32_t ptr_hw_rev    = 0;
    mfile       *mf = NULL;

    mf = mopen(getDevName().c_str());
    if (!mf) {
        return;
    }

    if (dm_get_device_id(mf, &ptr_dm_dev_id, &ptr_hw_dev_id, &ptr_hw_rev)) {
        mclose(mf);
        return;
    }


    switch (ptr_dm_dev_id) {
    case DeviceSpectrum:
    case DeviceSpectrum2:
    case DeviceSpectrum3:
        portOneType = PORT_ETH;
        portTwoType = PORT_ETH;
        isOnlyBase = true;
        break;

    case DeviceConnectIB:
        portOneType = PORT_IB;
        portTwoType = PORT_IB;
        break;

    case DeviceConnectX2:
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
        u_int32_t mac;
        if ((mread4(mf, 0x1f148, &mac)) == 4) {     // port1
            portOneType = EXT(mac, 30, 29) != 1 ? PORT_ETH : PORT_IB;
        }
        if ((mread4(mf, 0x1f164, &mac)) == 4) {     // port2
            portTwoType = EXT(mac, 30, 29) != 1 ? PORT_ETH : PORT_IB;
        }
        break;

    case DeviceSwitchIB:
    case DeviceSwitchIB2:
    case DeviceQuantum:
        portOneType = PORT_IB;
        portTwoType = PORT_IB;
        isOnlyBase = true;
        break;

    case DeviceConnectX4LX:
        portOneType = PORT_ETH;
        portTwoType = PORT_ETH;
        isOnlyBase   = true;
        break;

    case DeviceConnectX4:
    case DeviceConnectX5:
    case DeviceConnectX6:
    case DeviceConnectX6DX:
    case DeviceConnectX6LX:
    case DeviceBlueField:
    case DeviceBlueField2:
        try {
            _commander = Commander::create(mf, getDevName(), "");
        } catch (MlxcfgException& e) {
            _commander = NULL;
        }
        isOnlyBase = true;
        portOneType = findPortType(1);
        portTwoType = findPortType(2);
        if (_commander) {
            delete _commander;
        }
        _commander = NULL;
        break;

    default:
        portOneType = PORT_NA;
        portTwoType = PORT_NA;
    }
    if (mf) {
        mclose(mf);
    }
    _deviceTypeStr = (string)dm_dev_type2str(ptr_dm_dev_id);
    _deviceType    = ptr_dm_dev_id;

}

void MlnxDev::setDevToNeedUpdate()
{
    _needsUpdate = true;
}

void MlnxDev::setNoFwCtrl()
{
    _noFwCtrl = true;
}

void MlnxDev::patchPsidInfo(string psid)
{
    if (psid.size() > 0) {
        _psid = psid;
    }
}


string MlnxDev::getBoardTypeId()
{
    if (_psid.size() > 0) {
        return _psid;
    }
    return _boardTypeId;
}


string MlnxDev::getLastErrMsg()
{
    return _errMsg;
}


string MlnxDev::getLog()
{
    return _log;
}


int MlnxDev::compareFWVer(const ImgVersion& ver) {
    int idx = getImageIndex("FW");
    if (idx == -1) {
        return 0;
    }

    return _imageVers[idx].compareFw(ver);
}


int MlnxDev::isBurnSuccess()
{
    return _burnSuccess;
}


int MlnxDev::isQuerySuccess()
{
    return _querySuccess;
}


bool MlnxDev::openImg(u_int32_t *fileBuffer, u_int32_t bufferSize)
{
    memset(_errBuff, 0, sizeof(_errBuff));
    _imgFwParams.errBuff      = _errBuff;
    _imgFwParams.errBuffSize  = MLNX_ERR_BUFF_SIZE;
    _imgFwParams.hndlType     = FHT_FW_BUFF;
    _imgFwParams.psid         = (char*)_psid.c_str();
    _imgFwParams.buffHndl     = fileBuffer;
    _imgFwParams.buffSize     = bufferSize;
    _imgFwParams.shortErrors  = true;
    _imgFwOps = FwOperations::FwOperationsCreate(_imgFwParams);
    if (_imgFwOps == NULL) {
        _errMsg  = _errBuff;
        _log    += _errMsg;
        return false;
    }
    return true;
}

int MlnxDev::preBurn(string mfa_file, f_prog_func prog_cb, bool burnFailsafe,
                     bool& isTimeConsumingFixesNeeded, vector<string>& questions, f_prog_func_adv stage_prog)
{
    string cmd;
    int rc;
    u_int8_t *filebuf = NULL;
    ImageAccess imgacc(_compareFFV);
    fw_info_t dev_fw_query;
    fw_info_t img_fw_query;
    memset(&dev_fw_query, 0, sizeof(dev_fw_query));
    memset(&img_fw_query, 0, sizeof(img_fw_query));

    _burnSuccess = 0;
    int sza = imgacc.getImage(mfa_file, &filebuf);
    if (sza < 0) {
        _errMsg = imgacc.getLastErrMsg();
        _log    += imgacc.getLog();
        return -1;
    }

    if (!openImg((u_int32_t*)filebuf, (u_int32_t)sza)) {
        goto clean_up_on_error;
    }

    rc = _imgFwOps->FwQuery(&img_fw_query);
    if (!rc) {
        _errMsg  = "Failed to query the image, " +  (string)_imgFwOps->err();
        _log += _errMsg;
        goto clean_up_on_error;
    }

    if (img_fw_query.fs3_info.security_mode == SM_NONE) {
        setNoFwCtrl();
    }
    if (!OpenDev()) {
        goto clean_up_on_error;
    }

    _burnParams.burnFailsafe = burnFailsafe;
    if (_burnParams.burnFailsafe) {
        rc = _devFwOps->FwQuery(&dev_fw_query);
        if (!rc) {
            _errMsg  = "Failed to query the device, " +  (string)_devFwOps->err();
            _log += _errMsg;
            goto clean_up_on_error;
        }
        if (_burnParams.burnFailsafe && (!img_fw_query.fw_info.is_failsafe || !dev_fw_query.fw_info.is_failsafe)) {
            if (!img_fw_query.fw_info.is_failsafe && !dev_fw_query.fw_info.is_failsafe) {
                _burnParams.burnFailsafe = false;
            } else {
                char err[512] = {0};
                snprintf(err, sizeof(err) - 1,
                         "Failsafe burn failed: FW image in the %s is non failsafe.\n"
                         "    you cannot burn a%s failsafe image over a%s failsafe image in a failsafe mode.\n"
                         "    If you want to burn in non failsafe mode, use the \"--nofs\" switch along with \"-d device\".\n",
                         img_fw_query.fw_info.is_failsafe ? "flash" : "given file",  img_fw_query.fw_info.is_failsafe ? "" : " non", \
                         dev_fw_query.fw_info.is_failsafe ? "" : " non");
                _errMsg = err;
                _log += _errMsg;
                goto clean_up_on_error;
            }
        }

        FwOperations::fw_ops_params_t fwParams;
        if (InitDevFWParams(fwParams)) {
            FsChecks fsChecks(dev_fw_query, _devFwOps, _imgFwOps, _burnParams, fwParams);
            if (fsChecks.ExecuteChecks(&_devFwOps, _burnParams, dev_fw_query)) {
                fsChecks.GetUserQuestions(questions);
                isTimeConsumingFixesNeeded = fsChecks._isTimeConsumingFixesNeeded;
                delete[] fwParams.mstHndl;
            } else {
                delete[] fwParams.mstHndl;
                goto clean_up_on_error;
            }
        }

    }
    _burnParams.progressFunc = prog_cb;
    _burnParams.ProgressFuncAdv.func = stage_prog;
    _burnParams.ProgressFuncAdv.opaque = &_unknowProgress;
    _burnParams.ignoreVersionCheck = true;

    _preBurnInit = true;

    free(filebuf);
    return 0;

clean_up_on_error:
    if (_devFwOps) {
        _devFwOps->FwCleanUp();
        delete _devFwOps;
        _devFwOps = NULL;
    }
    if (_imgFwOps) {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = NULL;
    }
    free(filebuf);
    return -1;
}

int MlnxDev::burn(bool& imageWasCached)
{
    int res = 0, rc = 0;

    if (!_preBurnInit) {
        _errMsg  = "Pre-burn was not processed";
        res = -1;
        goto clean_up;
    }

    rc = _devFwOps->FwBurnAdvanced(_imgFwOps, _burnParams);
    if (!rc) {
        if (_devFwOps->err() != NULL) {
            _errMsg  = _devFwOps->err();
        } else {
            _errMsg  = "Failed to burn, unknown reason";
        }
        _log += _errMsg;
        res = -1;
        goto clean_up;
    }

    _burnSuccess = 1;
    imageWasCached = _burnParams.burnStatus.imageCachedSuccessfully;

clean_up:
    if (_devFwOps) {
        _devFwOps->FwCleanUp();
        delete _devFwOps;
        _devFwOps = NULL;
    }
    if (_imgFwOps) {
        _imgFwOps->FwCleanUp();
        delete _imgFwOps;
        _imgFwOps = NULL;
    }
    return res;
}

bool MlnxDev::InitDevFWParams(FwOperations::fw_ops_params_t& devFwParams)
{
    string devName = getDevName();
    memset(_errBuff, 0, sizeof(_errBuff));
    char *tmp = (char*) malloc((devName.length() + 1) * sizeof(char));
    if (tmp == NULL) {
        _errMsg  = "Failed to allocate Memory";
        _log    += _errMsg;
        return false;
    }
    memset(tmp, 0, (devName.length() + 1) * sizeof(char));
    devFwParams.errBuff = _errBuff;
    devFwParams.errBuffSize = MLNX_ERR_BUFF_SIZE;
    devFwParams.hndlType = FHT_MST_DEV;
    devFwParams.mstHndl = strcpy(tmp, devName.c_str());
    devFwParams.forceLock = false;
    devFwParams.readOnly = false;
    devFwParams.numOfBanks = -1;
    devFwParams.flashParams = (flash_params_t*)NULL;
    devFwParams.ignoreCacheRep = 0;
    devFwParams.noFlashVerify = false;
    devFwParams.psid = (char*)_psid.c_str();
    devFwParams.shortErrors = true;
    devFwParams.noFwCtrl = _noFwCtrl;
    devFwParams.mccUnsupported = !(_mccSupport);
    return true;
}

bool MlnxDev::OpenDev()
{
    if (!InitDevFWParams(_devFwParams)) {
        return false;
    }
    _devFwOps = FwOperations::FwOperationsCreate(_devFwParams);
    delete[] _devFwParams.mstHndl;
    if (_devFwOps == NULL) {
        _errMsg  = _errBuff;
        _log    += _errMsg;
        return false;
    }
    return true;
}

int MlnxDev::queryFwops()
{
    int res = -1;
    int i;
    ImgVersion imgv;
    u_int16_t fwVer[4];
    u_int16_t runningfwVer[4] = {0};
    fw_info_t fw_query;

    vector<u_int8_t> sect; // to get fw configuration.
    vector<u_int8_t> dest;

    int versionFields = 3;/*TODO: set variable length*/

    if (!OpenDev()) {
        return -1;
    }

    memset(&fw_query, 0, sizeof(fw_info_t));
    if (!_devFwOps->FwQuery(&fw_query, true)) {
        if (_devFwOps->err() != NULL) {
            _errMsg  = "Failed to query " +  (string)_devFwOps->err();
        } else {
            _errMsg  = "Failed to query : unknown reason";
        }
        _log += _errMsg;
        goto clean_up;
    }
    setGuidMac(fw_query);

    // attempt to take some fields from image info
    if (fw_query.fw_type == FIT_FS3 || fw_query.fw_type == FIT_FS4) {
        if (strlen(fw_query.fs3_info.description)) {
            _description = fw_query.fs3_info.description;
        }
        if (strlen(fw_query.fs3_info.name)) {
            _partNumber = fw_query.fs3_info.name;
        }
    }

    if (!_description.size() || !_partNumber.size()) {  // take missing from ini
        setMccSupport(false);
        _devFwOps->FwCleanUp();
        delete _devFwOps;
        if (!OpenDev()) {
            return -1;
        }
        setMccSupport(true);
        if (_devFwOps->FwGetSection((_devFwOps->FwType() == FIT_FS2) ? (int)H_FW_CONF : (int)FS3_DBG_FW_INI, sect)) {
            // Take from ini
            if (unzipDataFile(sect, dest, "Fw Configuration")) {
                char *ptr;
                int counter;
                if (!_partNumber.size()) {
                    ptr = strstr((char*)&dest[0], "Name =");
                    counter = 7;
                    while (ptr and * ptr != '\n' and * ptr != '\r') {
                        if (counter-- > 0) {
                            ptr++;
                            continue;
                        }
                        _partNumber += *ptr;
                        ptr++;
                    }
                }
                if (!_description.size()) {
                    ptr = strstr((char*)&dest[0], "Description =");
                    counter = 14;
                    while (ptr and * ptr != '\n' and * ptr != '\r') {
                        if (counter-- > 0) {
                            ptr++;
                            continue;
                        }
                        _description += *ptr;
                        ptr++;
                    }
                }
            }
        }
    }
    if (!_compareFFV) {
        for (i = 0; i < versionFields; i++) {
            fwVer[i] = fw_query.fw_info.fw_ver[i];
            runningfwVer[i] = fw_query.fw_info.running_fw_ver[i];
        }
    } else {
        fwVer[0] = fw_query.fw_info.fw_ver[0];
        fwVer[1] = fw_query.fw_info.fw_ver[1];
        fwVer[2] = fw_query.fw_info.fw_ver[2] / 100;
        fwVer[3] = fw_query.fw_info.fw_ver[2] % 100;

        runningfwVer[0] = fw_query.fw_info.running_fw_ver[0];
        runningfwVer[1] = fw_query.fw_info.running_fw_ver[1];
        runningfwVer[2] = fw_query.fw_info.running_fw_ver[2] / 100;
        runningfwVer[3] = fw_query.fw_info.running_fw_ver[2] % 100;
    }
    imgv.setVersion("FW", versionFields + _compareFFV, fwVer,
            fw_query.fw_info.branch_ver);
    _imageVers.push_back(imgv);

    if ((fw_query.fw_info.running_fw_ver[0] || fw_query.fw_info.running_fw_ver[1] || fw_query.fw_info.running_fw_ver[2]) && \
        (fw_query.fw_info.running_fw_ver[0] != fw_query.fw_info.fw_ver[0] || \
         fw_query.fw_info.running_fw_ver[1] != fw_query.fw_info.fw_ver[1] || \
         fw_query.fw_info.running_fw_ver[2] != fw_query.fw_info.fw_ver[2])) {
        ImgVersion imgrv;
        imgrv.setVersion("FW (Running)", versionFields + _compareFFV,
                runningfwVer, fw_query.fw_info.running_branch_ver);
        _imageVers.push_back(imgrv);
    }

    for (i = 0; i < fw_query.fw_info.roms_info.num_of_exp_rom; i++) {
        ImgVersion imgVer;
        const char *tpc = _devFwOps->expRomType2Str(fw_query.fw_info.roms_info.rom_info[i].exp_rom_product_id);
        if (tpc == NULL) {
            //imgVer.setExpansionRomtoUnknown();
            tpc = "UNKNOWN_ROM";
        }
        int sz = fw_query.fw_info.roms_info.rom_info[i].exp_rom_num_ver_fields;
        imgVer.setVersion(tpc, sz, fw_query.fw_info.roms_info.rom_info[i].exp_rom_ver);
        _imageVers.push_back(imgVer);
    }

    _productVer = fw_query.fw_info.product_ver;
    _psid = fw_query.fw_info.psid;

    _querySuccess = 1;
    res = 0;

clean_up:
    _devFwOps->FwCleanUp();
    delete _devFwOps;
    _devFwOps = NULL;
    return res;
}



#if !defined(__WIN__) && !defined(__FreeBSD__)
static int readSysFs(dev_info *devinfo, fw_info_t *fw_query)
{
    int res = -1;
    char path[256] = {0};
    char buf [40] = {0};
    DIR *d;
    struct dirent *dir;
    int v0, v1, v2, v20, v21;

    snprintf(path, sizeof(path) - 1, "/sys/bus/pci/devices/%04x:%02x:%02x.%x/infiniband", devinfo->pci.domain, devinfo->pci.bus, devinfo->pci.dev, devinfo->pci.func);
    d = opendir(path);
    if (d == NULL) {
        return -1;
    }

    while ((dir = readdir(d)) != NULL) {
        string fl = dir->d_name;
        if (fl == "." || fl == "..") {
            continue;
        }
        string fpath = path;
        fpath += "/";
        fpath += fl;
        fpath += "/";
        string file = fpath;
        file += "fw_ver";
        FILE *f = fopen(file.c_str(), "r");
        if (f == NULL) {
            continue;
        }
        if (fgets(buf, 32, f)) {
            if (buf[strlen(buf) - 1] == '\n') {
                buf[strlen(buf) - 1] = 0;
            }
            int tmp = sscanf(buf, "%d.%d.%d", &v0, &v1, &v2);
            fw_query->fw_info.fw_ver[0] = v0;
            fw_query->fw_info.fw_ver[1] = v1;
            fw_query->fw_info.fw_ver[2] = v2;
            v20 = v2 / 100;
            v21 = v2 % 100;
            (void) tmp;
            snprintf(fw_query->fw_info.product_ver, sizeof(fw_query->fw_info.product_ver) - 1, "%02d.%02d.%02d.%02d", v0 % 100, v1 % 100, v20 % 100, v21 % 100);
        }
        fclose(f);


        file = fpath;
        file += "board_id";
        f = fopen(file.c_str(), "r");
        if (f == NULL) {
            continue;
        }
        if (fgets(buf, 32, f)) {
            if (buf[strlen(buf) - 1] == '\n') {
                buf[strlen(buf) - 1] = 0;
            }
            strcpy(fw_query->fw_info.psid, buf);
        }
        fclose(f);
        res = 0;
        break;
    }

    closedir(d);
    return res;
}


static int getEthtoolInfo(dev_info *devinfo, fw_info_t *fw_query)
{
    int sock;
    struct ifreq ifr;
    struct ethtool_drvinfo edata;
    int rc;
    int res = -1;
    char path[256] = {0};
    DIR *d;
    struct dirent *dir;
    int v0, v1, v2, v20, v21;

    snprintf(path, sizeof(path) - 1, "/sys/bus/pci/devices/%04x:%02x:%02x.%x/net", devinfo->pci.domain, devinfo->pci.bus, devinfo->pci.dev, devinfo->pci.func);
    d = opendir(path);
    if (d == NULL) {
        return -1;
    }

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        closedir(d);
        return -1;
    }

    while ((dir = readdir(d)) != NULL) {
        string fl = dir->d_name;
        if (fl == "." || fl == "..") {
            continue;
        }

        strncpy(ifr.ifr_name, fl.c_str(), sizeof(ifr.ifr_name) - 1);//the rest of dest will be filled with zeros
        ifr.ifr_name[sizeof(ifr.ifr_name) - 1] = '\0';

        ifr.ifr_data = &edata;
        edata.cmd = ETHTOOL_GDRVINFO;

        rc = ioctl(sock, SIOCETHTOOL, &ifr);
        if (rc < 0) {
            continue;
        }

        int tmp = sscanf(edata.fw_version, "%d.%d.%d", &v0, &v1, &v2);
        fw_query->fw_info.fw_ver[0] = v0;
        fw_query->fw_info.fw_ver[1] = v1;
        fw_query->fw_info.fw_ver[2] = v2;
        v20 = v2 / 100;
        v21 = v2 % 100;
        (void) tmp;
        snprintf(fw_query->fw_info.product_ver, sizeof(fw_query->fw_info.product_ver) - 1, "%02d.%02d.%02d.%02d", v0 % 100, v1 % 100, v20 % 100, v21 % 100);

        fw_query->fw_info.psid[0] = '\0';
        res = 0;
        break;
    }

    closedir(d);
    close(sock);

    return res;
}
#endif

#if !defined(__WIN__)
int MlnxDev::query()
{
    int res = -1;
    int i;
    int rc;
    char buf[32] = {0};
    (void) buf;
    ImgVersion imgv;
    u_int16_t fwVer[4];
    fw_info_t fw_query;

    int versionFields = 3;/*TODO: set variable length*/
    if (geteuid() == 0) {
        return queryFwops();
    } else {
        _errMsg = "User is Not Root";
        _log += _errMsg;
        rc = -1;
    }

    if (rc && (_init_type == INIT_DEVINFO)) {
        #if !defined(__FreeBSD__)
        rc = readSysFs(_devinfo, &fw_query);
        if (rc) {
            rc = getEthtoolInfo(_devinfo, &fw_query);
            if (rc) {
                goto clean_up;
            }
            snprintf(buf, sizeof(buf) - 1, "%04x:%04x:%04x:%04x", _devinfo->pci.vend_id, _devinfo->pci.dev_id, _devinfo->pci.subsys_vend_id, _devinfo->pci.subsys_id);
            _boardTypeId = buf;
        }
        #else
        goto clean_up;
        #endif
    } else {
        return rc;
    }

    if (!_compareFFV) {
        for (i = 0; i < versionFields; i++) {
            fwVer[i] = fw_query.fw_info.fw_ver[i];
        }
    } else {
        fwVer[0] = fw_query.fw_info.fw_ver[0];
        fwVer[1] = fw_query.fw_info.fw_ver[1];
        fwVer[2] = fw_query.fw_info.fw_ver[2] / 100;
        fwVer[3] = fw_query.fw_info.fw_ver[2] % 100;

    }

    imgv.setVersion("FW", versionFields + _compareFFV, fwVer,
            fw_query.fw_info.branch_ver);
    _imageVers.push_back(imgv);
    _productVer = fw_query.fw_info.product_ver;
    _psid = fw_query.fw_info.psid;

    _querySuccess = 1;
    res = 0;

clean_up:
    return res;
}

#else //__WIN__

int MlnxDev::query()
{
    return queryFwops();
}

#endif //__WIN__


string MlnxDev::getDevDisplayName(bool pci_if_possible)
{
    char tmpb[20] = {0};
    string devname = "";

    if (_init_type == INIT_DEVINFO) {
        if (_devinfo->type == MDEVS_TAVOR_CR) {
            snprintf(tmpb, sizeof(tmpb) - 1, "%04x:%02x:%02x.%x", _devinfo->pci.domain,
                     _devinfo->pci.bus, _devinfo->pci.dev, _devinfo->pci.func);
            devname = tmpb;
            //_devinfo->pci.conf_dev;
        } else {
            devname = _devinfo->dev_name;
        }
        if (pci_if_possible) {
            return devname;
        }
        #ifndef ONLY_PCI_FORMAT
        devname = _devinfo->dev_name;
        #endif
    } else if (_init_type == INIT_DEVNAME) {
        devname = _devname;
    } else {
        fprintf(stderr, "-E- mlnx_dev.cpp: unexpected value for _init_type: %d\n", _init_type);
    }
    return devname;
}

string MlnxDev::getDeviceTypeStr()
{
    return _deviceTypeStr;
}

dm_dev_id_t MlnxDev::getDeviceType()
{
    return _deviceType;
}

string MlnxDev::getDevName()
{
    string devname;

    if (_init_type == INIT_DEVINFO) {
        devname = _devinfo->dev_name;
    } else if (_init_type == INIT_DEVNAME) {
        devname = _devname;
    } else {
        devname = "UNKNOWN";
        fprintf(stderr, "-E- mlnx_dev.cpp: unexpected value for _init_type: %d\n", _init_type);
    }
    return devname;
}


string MlnxDev::getPsid()
{
    return _psid;
}


int MlnxDev::getImageIndex(string type)
{
    int idx = -1;

    for (int i = 0; i < (int)_imageVers.size(); i++) {
        if (!_imageVers[i].getTypeStr().compare(type)) {
            idx = i;
        }
    }
    return idx;
}


string MlnxDev::getFWVersion(bool show_type, bool use_default_ffv)
{
    string st;
    int idx = getImageIndex("FW");

    if (idx == -1) {
        return st;
    }
    if (use_default_ffv) {
        st = _imageVers[idx].getPrintableVersion(_compareFFV, show_type);
    } else {
        st = _imageVers[idx].getPrintableVersion(0, show_type);
    }
    return st;
}




dev_info* MlnxDev::getDevInfo()
{
    return _devinfo;
}

string MlnxDev::getDescription()
{
    return _description;
}

string MlnxDev::getPartNumber()
{
    return _partNumber;
}

bool MlnxDev::checkExistence(vector<MlnxDev*>& devs)
{
    for (vector<MlnxDev*>::iterator it = devs.begin(); it != devs.end(); it++) {
        if (this->equals(*it) == true) {
            return true;
        }
    }
    return false;
}


bool MlnxDev::equals(MlnxDev *dev)
{
    string devUinqueId = dev->getUniqueId();
    if (_uniqueId != "NA" && devUinqueId != "NA") {
        if (_uniqueId == devUinqueId) {
            return true;
        }
    }
    return false;
}
