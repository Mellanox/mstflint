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
 */

#include "fsctrl_ops.h"

#include <tools_utils.h>
#include <bit_slice.h>
#include <vector>

bool FsCtrlOperations::unsupportedOperation()
{
    if (_fsCtrlImgInfo.security_mode & SMM_SECURE_FW) {
            return errmsg("Unsupported operation under Secure FW");
    } else {
        return errmsg("Unsupported operation under Controlled FW, please retry with --no_fw_ctrl <command>");
    }
}

u_int8_t FsCtrlOperations::FwType()
{
    if (!_hwDevId) {
        if (!FsIntQuery()) {
            return FS_UNKNOWN_IMG;
        }
    }
    u_int8_t fwFormat = GetFwFormatFromHwDevID(_hwDevId);
    if (fwFormat == FS_FS2_GEN) {
        return FIT_FS2;
    } else if (fwFormat == FS_FS3_GEN) {
        return FIT_FS3;
    } else if (fwFormat == FS_FS4_GEN) {
        return FIT_FS4;
    }
    return FIT_FSCTRL;

}

bool FsCtrlOperations::FwInit()
{
    FwInitCom();
    _fwImgInfo.fwType = FIT_FSCTRL;
    memset(&(_fsCtrlImgInfo), 0, sizeof(fs3_info_t));
    if (!FsIntQuery()) {
        return false;
    }
    return true;
}

static void extractFwVersion(u_int16_t* fwVerArr, u_int32_t fwVersion)
{
    if (!fwVerArr) {
        return;
    }
    fwVerArr[0] = EXTRACT(fwVersion, 24, 8);
    fwVerArr[1] = EXTRACT(fwVersion, 16, 8);
    fwVerArr[2] = EXTRACT(fwVersion, 0, 16);
}

static void extractFwBuildTime(u_int16_t* fwRelDate, u_int32_t buildTime)
{
    if (!fwRelDate) {
        return;
    }
    fwRelDate[0] = EXTRACT(buildTime, 0, 8);
    fwRelDate[1] = EXTRACT(buildTime, 8, 8);
    fwRelDate[2] = EXTRACT(buildTime, 16, 16);
}

bool FsCtrlOperations::FsIntQuery()
{
    fwInfoT fwQery;
    if (!_fwCompsAccess->queryFwInfo(&fwQery)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to query the FW - Err[%d] - %s", _fwCompsAccess->getLastError(), _fwCompsAccess->getLastErrMsg());
    }
    if (fwQery.pending_fw_valid) {
        extractFwVersion(_fwImgInfo.ext_info.fw_ver, fwQery.pending_fw_version.version);
        extractFwBuildTime(_fwImgInfo.ext_info.fw_rel_date, fwQery.pending_fw_version.build_time);
    } else {
        extractFwVersion(_fwImgInfo.ext_info.fw_ver, fwQery.running_fw_version.version);
        extractFwBuildTime(_fwImgInfo.ext_info.fw_rel_date, fwQery.running_fw_version.build_time);
    }
    extractFwVersion(_fwImgInfo.ext_info.running_fw_ver, fwQery.running_fw_version.version);
    if (fwQery.running_fw_version.version_string_length) {
        strcpy(_fwImgInfo.ext_info.product_ver, fwQery.product_ver);
    }

    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_mac.uid                  = fwQery.base_mac.uid;
    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_mac.num_allocated        = fwQery.base_mac.num_allocated;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_mac.uid             = fwQery.base_mac_orig.uid;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_mac.num_allocated   = fwQery.base_mac_orig.num_allocated;


    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_guid.uid                  = fwQery.base_guid.uid;
    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_guid.num_allocated        = fwQery.base_guid.num_allocated;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_guid.uid             = fwQery.base_guid_orig.uid;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_guid.num_allocated   = fwQery.base_guid_orig.num_allocated;

    _fwImgInfo.ext_info.pci_device_id = fwQery.dev_id;
    _fwImgInfo.ext_info.dev_type = fwQery.dev_id;
    _hwDevId = fwQery.hw_dev_id;
    _fwImgInfo.ext_info.dev_rev = fwQery.rev_id;
    _fwImgInfo.ext_info.is_failsafe        = true;
    // get chip type and device sw id, from device/image
    const u_int32_t* swId = (u_int32_t*)NULL;
    if (!getInfoFromHwDevid(fwQery.hw_dev_id, _fwImgInfo.ext_info.chip_type, &swId)) {
        return false;
    }

    _fsCtrlImgInfo.security_mode = (security_mode_t)
                                         (SMM_MCC_EN |
                                         ((fwQery.security_type.debug_fw  == 1) ? SMM_DEBUG_FW  : 0) |
                                         ((fwQery.security_type.signed_fw == 1) ? SMM_SIGNED_FW : 0) |
                                         ((fwQery.security_type.secure_fw == 1) ? SMM_SECURE_FW : 0) |
                                         ((fwQery.security_type.dev_fw    == 1) ? SMM_DEV_FW    : 0));


    strcpy(_fwImgInfo.ext_info.psid, fwQery.psid);
    strcpy(_fsCtrlImgInfo.orig_psid, fwQery.psid);

    /*
     * Fill ROM info
     */

    _fwImgInfo.ext_info.roms_info.num_of_exp_rom = fwQery.nRoms;
    _fwImgInfo.ext_info.roms_info.exp_rom_found = fwQery.nRoms > 0;
    for (int i = 0; i < fwQery.nRoms; i++) {
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_product_id = fwQery.roms[i].type;
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_proto = 0xff; // NA
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_supp_cpu_arch = fwQery.roms[i].arch;
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_num_ver_fields = FwOperations::RomInfo::getNumVerFromProdId(_fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_product_id);
        extractFwVersion(_fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_ver, fwQery.roms[i].version);
    }
    return true;
}

bool FsCtrlOperations::FwQuery(fw_info_t *fwInfo, bool readRom, bool isStripedImage)
{
    (void)isStripedImage;
    (void)readRom;
    memcpy(&(fwInfo->fw_info),  &(_fwImgInfo.ext_info),  sizeof(fw_info_com_t));
    memcpy(&(fwInfo->fs3_info), &(_fsCtrlImgInfo), sizeof(fs3_info_t));
    fwInfo->fs3_info.fs3_uids_info.valid_field = 1;
    fwInfo->fw_type = FwType();

    return true;
}

bool FsCtrlOperations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc, bool ignoreDToc)
{
    ExtVerifyParams extVerParams(verifyCallBackFunc);
    extVerParams.isStripedImage = isStripedImage;
    extVerParams.showItoc = showItoc;
    extVerParams.ignoreDToc = ignoreDToc;
    return FwVerifyAdv(extVerParams);
}

bool FsCtrlOperations::FwVerifyAdv(ExtVerifyParams& verifyParams)
{
    bool ret = true;
    std::vector<FwComponent> compsMap;
    if (!_fwCompsAccess->getFwComponents(compsMap, false)) {

        return errmsg("Failed to get the FW Components MAP, err[%d]", _fwCompsAccess->getLastError());
    }

    u_int32_t imageSize = 0;
    if (!ReadBootImage(NULL, &imageSize)) {
        return false;
    }
    std::vector<u_int8_t> imageData;
    imageData.resize(imageSize);
    if (!ReadBootImage((void*)imageData.data(), &imageSize, verifyParams.progressFuncAdv)) {
        return false;
    }
    fw_ops_params_t imageParams;
    memset(&imageParams, 0, sizeof(imageParams));
    imageParams.buffHndl = (u_int32_t*)imageData.data();
    imageParams.buffSize = imageSize;
    imageParams.hndlType = FHT_FW_BUFF;
    FwOperations* imageOps = FwOperations::FwOperationsCreate(imageParams);
    if (!imageOps) {
        return errmsg("Failed to get boot image");
    }
    if (!imageOps->FwVerify(verifyParams.verifyCallBackFunc, verifyParams.isStripedImage, verifyParams.showItoc, true)) {
        errmsg(imageOps->getErrorCode(), "%s", imageOps->err());
        ret = false;
    }
    delete imageOps;
    return ret;
}

bool FsCtrlOperations::FwReadData(void* image, u_int32_t* image_size)
{
    (void)image;
    (void)image_size;
    return errmsg("Read image is not supported");
}

bool FsCtrlOperations::ReadBootImage(void* image, u_int32_t* image_size, ProgressCallBackAdvSt* stProgressFunc)
{
    if (image) {
        FwComponent bootImgComp;
        if (!_fwCompsAccess->readComponent(FwComponent::COMPID_BOOT_IMG, bootImgComp, true, (ProgressCallBackAdvSt*)stProgressFunc)) {
            if (!_fwCompsAccess->readComponent(FwComponent::COMPID_BOOT_IMG, bootImgComp, false, (ProgressCallBackAdvSt*)stProgressFunc)) {
                return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to read boot image, %s - RC[%d]",
                        _fwCompsAccess->getLastErrMsg(), (int)_fwCompsAccess->getLastError());
            }
        }
        *image_size = bootImgComp.getSize();
        memcpy(image, bootImgComp.getData().data(), *image_size);
        return true;
    } else {
        std::vector<FwComponent> compsMap;
        if (!_fwCompsAccess->getFwComponents(compsMap, false)) {
            return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to get the FW Components MAP, err[%d]", _fwCompsAccess->getLastError());
        }
        for (std::vector<FwComponent>::iterator it = compsMap.begin(); it != compsMap.end(); it++) {
            if (it->getType() == FwComponent::COMPID_BOOT_IMG) {
                *image_size = it->getSize();
                return true;
            }
        }
        return errmsg("Failed to get the Boot image");

    }
}

bool FsCtrlOperations::FwReadRom(std::vector<u_int8_t>& romSect)
{
    (void)romSect;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwBurnRom(FImage* romImg, bool ignoreProdIdCheck, bool ignoreDevidCheck, ProgressCallBack progressFunc)
{
    (void)romImg;
    (void)ignoreDevidCheck;
    (void)ignoreProdIdCheck;
    (void)progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    (void)ignoreProdIdCheck;
    (void)progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwBurn(FwOperations *imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc)
{
    if (imageOps == NULL) {
        return errmsg("bad parameter is given to FwBurnAdvanced\n");
    }
    ExtBurnParams params = ExtBurnParams();
    params.ignoreVersionCheck = forceVersion;
    params.progressFunc = progressFunc;
    return FwBurnAdvanced(imageOps, params);
}

bool FsCtrlOperations::FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams& burnParams)
{
    if (imageOps == NULL) {
        return errmsg("bad parameter is given to FwBurnAdvanced\n");
    }
    if (!FsIntQuery()) {
        return false;
    }
    fw_info_t fw_query;
    std::vector<FwComponent> compsToBurn;
    FwComponent bootImageComponent;

    memset(&fw_query, 0, sizeof(fw_info_t));
    if(!imageOps->FwQuery(&fw_query, true)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to query the image\n");
    }
    if(!CheckPSID(*imageOps, false)) {
        if (burnParams.allowPsidChange) {
            return errmsg(MLXFW_PSID_MISMATCH_ERR, "Changing PSID is not supported under controlled FW.");
        }
        return false;
    }
    // Check if the burnt FW version is OK
    if (!CheckFwVersion(*imageOps, burnParams.ignoreVersionCheck)) {
        return false;
    }
    if (fw_query.fs3_info.security_mode == SM_NONE) {
        return errmsg(MLXFW_MISSING_IMAGE_SIGNATURE, "This is an old image format that does not have a signature or does not support FW control commands.\n-E- please retry with --no_fw_ctrl flag\n");
    }
    std::vector<u_int8_t> imageOps4MData;
    if (!imageOps->FwExtract4MBImage(imageOps4MData, true)) {
        return errmsg(imageOps->getErrorCode(), "Failed to Extract 4MB from the image");
    }
    burnParams.progressFunc = (ProgressCallBack)NULL;
    bootImageComponent.init(imageOps4MData, imageOps4MData.size(), FwComponent::COMPID_BOOT_IMG);
    compsToBurn.push_back(bootImageComponent);
    if (!_fwCompsAccess->burnComponents(compsToBurn, &burnParams.ProgressFuncAdv)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "%s", _fwCompsAccess->getLastErrMsg());
    }

    return true;
}

bool FsCtrlOperations::FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc)
{
    (void)imageOps;
    (void)progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwWriteBlock(u_int32_t addr, std::vector<u_int8_t> dataVec, ProgressCallBack progressFunc)
{
    (void)addr;
    (void)dataVec;
    (void)progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc)
{
    (void)callBackFunc;
    (void)progressFunc;
    mac_guid_t macGuid;

    memset(&macGuid, 0, sizeof(macGuid));

    if (sgParam.userGuids.empty()) {
        return errmsg("Base GUID not found.");
    }
    if (!sgParam.guidsSpecified  && !sgParam.macsSpecified && !sgParam.uidSpecified) {
        return errmsg("base GUID/MAC were not specified.");
    }
    if (!sgParam.updateCrc || sgParam.numOfGUIDs != 0 || sgParam.stepSize != 0 ||
        sgParam.numOfGUIDsPP[0] != 0xff || sgParam.numOfGUIDsPP[1] != 0xff ||
            sgParam.stepSizePP[0] != 0xff || sgParam.stepSizePP[1] != 0xff) {
        return errmsg("Tried to set unsupported values. Allowed values to set are mac,guid,uid.");
    }

    if (sgParam.uidSpecified) {
        macGuid.guid = sgParam.userGuids[0];
        u_int64_t baseMac = (((u_int64_t)macGuid.guid.l & 0xffffff) | (((u_int64_t)macGuid.guid.h & 0xffffff00) << 16));
        macGuid.mac.h = baseMac >> 32;
        macGuid.mac.l = baseMac & 0x00000000ffffffff;
    } else {
        fwInfoT fwQuery;
        if (!_fwCompsAccess->queryFwInfo(&fwQuery)) {
            return false;
        }
        if (sgParam.macsSpecified) {
            if (sgParam.userGuids.size() < 2) {
                return errmsg("MAC was not found.");
            }
            // check base mac
            if (!CheckMac(sgParam.userGuids[1])) {
                return errmsg("Bad MAC (" MAC_FORMAT ") given: %s. Please specify a valid MAC value",
                    sgParam.userGuids[1].h, sgParam.userGuids[1].l, err());
            }
            macGuid.mac = sgParam.userGuids[1];
        } else {
            macGuid.mac.h = fwQuery.base_mac.uid >> 32;
            macGuid.mac.l = fwQuery.base_mac.uid & 0x00000000ffffffff;
        }
        if (sgParam.guidsSpecified) {
             macGuid.guid = sgParam.userGuids[0];
        } else {
            macGuid.guid.h = fwQuery.base_guid.uid >> 32;
            macGuid.guid.l = fwQuery.base_guid.uid & 0x00000000ffffffff;
        }
    }
    if  (!_fwCompsAccess->setMacsGuids(macGuid)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "%s", _fwCompsAccess->getLastErrMsg());
    }
    return true;
}

bool FsCtrlOperations::FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc)
{
    (void)baseGuid;
    (void)callBackFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc)
{
    (void)baseGuid;
    (void)callBackFunc;
    return unsupportedOperation();
}

// use progressFunc when dealing with FS2 image and printFunc when dealing with FS3 image.
bool FsCtrlOperations::FwSetVSD(char* vsdStr, ProgressCallBack progressFunc, PrintCallBack printFunc)
{
    (void)vsdStr;
    (void)printFunc;
    (void)progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc)
{
    (void)vpdFileStr;
    (void)callBackFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc)
{
    (void)userKey;
    (void)progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwGetSection (u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage)
{
    (void)sectInfo;
    (void)sectType;
    (void)stripedImage;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwResetNvData()
{
    return unsupportedOperation();
}

bool FsCtrlOperations::FwShiftDevData(PrintCallBack progressFunc)
{
    (void)progressFunc;
    return unsupportedOperation();
}

const char*  FsCtrlOperations::FwGetResetRecommandationStr()
{
    return "To load new FW run mlxfwreset or reboot machine.";
}

bool FsCtrlOperations::FwCalcMD5(u_int8_t md5sum[16])
{
    (void)md5sum;
    return unsupportedOperation();
}

FsCtrlOperations::~FsCtrlOperations()
{
    if (_fwCompsAccess) {
        delete _fwCompsAccess;
        _fwCompsAccess = (FwCompsMgr*)NULL;
    }
}

bool FsCtrlOperations::FwReadBlock(u_int32_t addr, u_int32_t size, std::vector<u_int8_t>& dataVec)
{
    if (!_fwCompsAccess->readBlockFromComponent(FwComponent::COMPID_BOOT_IMG, addr, size, dataVec)) {
        fw_comps_error_t errCode = _fwCompsAccess->getLastError();
        if (errCode == FWCOMPS_READ_OUTSIDE_IMAGE_RANGE) {
            return errmsg(MLXFW_BAD_PARAM_ERR, "Reading %#x bytes from address %#x is out of flash limits\n",
                    size, (unsigned int)addr);
        } else {
            return errmsg(MLXFW_FLASH_READ_ERR, "%s", _fwCompsAccess->getLastErrMsg());
        }
    }
    return true;
}

int  FsCtrlOperations::FwCompsErrToFwOpsErr(fw_comps_error_t err)
{
    int fwOpsErr = MLXFW_OK;
    switch (err) {
        case FWCOMPS_MCC_ERR_REJECTED_DIGEST_ERR:
            fwOpsErr = MLXFW_BURN_REJECTED_DIGEST_ERR;
            break;
        case FWCOMPS_MCC_ERR_REJECTED_NOT_APPLICABLE :
            fwOpsErr = MLXFW_BURN_REJECTED_NOT_APPLICABLE;
            break;
        case FWCOMPS_MCC_ERR_REJECTED_UNKNOWN_KEY:
            fwOpsErr = MLXFW_BURN_REJECTED_UNKNOWN_KEY;
            break;
        case FWCOMPS_MCC_ERR_REJECTED_AUTH_FAILED:
            fwOpsErr = MLXFW_BURN_REJECTED_AUTH_FAILED;
            break;
        case FWCOMPS_MCC_ERR_REJECTED_UNSIGNED:
            fwOpsErr = MLXFW_BURN_REJECTED_UNSIGNED;
            break;
        case FWCOMPS_MCC_ERR_REJECTED_KEY_NOT_APPLICABLE:
            fwOpsErr = MLXFW_BURN_REJECTED_KEY_NOT_APPLICABLE;
            break;
        case FWCOMPS_MCC_ERR_REJECTED_BAD_FORMAT:
            fwOpsErr = MLXFW_BURN_REJECTED_BAD_FORMAT;
            break;
        case FWCOMPS_MCC_ERR_BLOCKED_PENDING_RESET:
            fwOpsErr = MLXFW_BURN_BLOCKED_PENDING_RESET;
            break;
        case FWCOMPS_MCC_UNEXPECTED_STATE:
            fwOpsErr = MLXFW_FSM_UNEXPECTED_STATE;
            break;
        case FWCOMPS_MCC_REJECTED_NOT_A_SECURED_FW:
            fwOpsErr = MLXFW_REJECTED_NOT_A_SECURED_FW;
            break;
        case FWCOMPS_MCC_REJECTED_MFG_BASE_MAC_NOT_LISTED:
            fwOpsErr = MLXFW_REJECTED_MFG_BASE_MAC_NOT_LISTED;
            break;
        case FWCOMPS_MCC_REJECTED_NO_DEBUG_TOKEN:
            fwOpsErr = MLXFW_REJECTED_NO_DEBUG_TOKEN;
            break;
        case FWCOMPS_MCC_REJECTED_VERSION_NUM_MISMATCH:
            fwOpsErr = MLXFW_REJECTED_VERSION_NUM_MISMATCH;
            break;
        case FWCOMPS_MCC_REJECTED_USER_TIMESTAMP_MISMATCH:
            fwOpsErr = MLXFW_REJECTED_USER_TIMESTAMP_MISMATCH;
            break;
        case FWCOMPS_MCC_REJECTED_FORBIDDEN_VERSION:
            fwOpsErr = MLXFW_REJECTED_FORBIDDEN_VERSION;
            break;
        case FWCOMPS_MCC_FLASH_ERASE_ERROR:
            fwOpsErr = MLXFW_FLASH_ERASE_ERROR;
            break;
        case FWCOMPS_MEM_ALLOC_FAILED:
            fwOpsErr = MLXFW_MEM_ERR;
            break;
        case FWCOMPS_MCC_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION:
            fwOpsErr = MLXFW_REJECTED_IMAGE_CAN_NOT_BOOT_FROM_PARTITION;
            break;
        default:
            if (err != FWCOMPS_SUCCESS) {
                fwOpsErr = MLXFW_ERR;
            }
            break;
    }
    return fwOpsErr;
}
