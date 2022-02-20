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

static void extractFwVersion(u_int16_t *fwVerArr, u_int32_t fwVersion)
{
    if (!fwVerArr) {
        return;
    }
    fwVerArr[0] = EXTRACT(fwVersion, 24, 8);
    fwVerArr[1] = EXTRACT(fwVersion, 16, 8);
    fwVerArr[2] = EXTRACT(fwVersion, 0, 16);
}

static void extractFwVersion(u_int16_t *fwVerArr,
        const reg_access_hca_rom_version fwVersion) {
    if (!fwVerArr) {
        return;
    }
    fwVerArr[0] = fwVersion.major;
    fwVerArr[1] = fwVersion.minor;
    fwVerArr[2] = fwVersion.build;
}


static void extractFwVersion(u_int16_t *fwVerArr, const char* fwVersion) {
    if (!fwVerArr) {
        return;
    }
    
    char* str = new char[strlen(fwVersion) + 1];
    char* token = NULL;
    int index = 0;

    memset(str, 0, strlen(fwVersion) + 1);
    strcpy(str, fwVersion);    
    token = strtok(str, ".");

    // converting fw version tokens to numbers
    while (token != NULL && index < 3) {
        fwVerArr[index] = atoi(token);
        token = strtok(NULL, ".");
        ++index;
    }

    // 3 tokens are expected in fw version format
    if (token != NULL || index != 3){
        printf("-W- Wrong FW version format.\n");
    }

    delete[] str;
}

static void extractFwBuildTime(u_int16_t *fwRelDate, u_int32_t buildTime)
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
    fwInfoT fwQuery;
    if (!_fwCompsAccess->queryFwInfo(&fwQuery, nextBootFwVer)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to query the FW - Err[%d] - %s", _fwCompsAccess->getLastError(), _fwCompsAccess->getLastErrMsg());
    }
    if (fwQuery.pending_fw_valid) {
        extractFwVersion(_fwImgInfo.ext_info.fw_ver, fwQuery.pending_fw_version.version);
        extractFwBuildTime(_fwImgInfo.ext_info.fw_rel_date, fwQuery.pending_fw_version.build_time);
    } else {
        extractFwVersion(_fwImgInfo.ext_info.fw_ver, fwQuery.running_fw_version.version);
        extractFwBuildTime(_fwImgInfo.ext_info.fw_rel_date, fwQuery.running_fw_version.build_time);
    }
    extractFwVersion(_fwImgInfo.ext_info.running_fw_ver, fwQuery.running_fw_version.version);
    if (fwQuery.running_fw_version.version_string_length) {
        strcpy(_fwImgInfo.ext_info.product_ver, fwQuery.product_ver);
    }

    // get chip type and device sw id
    const u_int32_t *swId = (u_int32_t*) NULL;
    if (!getInfoFromHwDevid(fwQuery.hw_dev_id, _fwImgInfo.ext_info.chip_type, &swId)) {
        return false;
    }

    // Copy version_string to fw version and VSD to branch ver, only for switches fw version
    if (!IS_HCA(_fwImgInfo.ext_info.chip_type)) {
        ExtractSwitchFWVersion(fwQuery);
    }

    // if nextBootFwVer, only fw version is needed and chip type, return.
    if (nextBootFwVer) {
        return true;
    }

    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_mac.uid = fwQuery.base_mac.uid;
    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_mac.num_allocated = fwQuery.base_mac.num_allocated;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_mac.uid = fwQuery.base_mac_orig.uid;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_mac.num_allocated = fwQuery.base_mac_orig.num_allocated;

    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_guid.uid = fwQuery.base_guid.uid;
    _fsCtrlImgInfo.fs3_uids_info.cx4_uids.base_guid.num_allocated = fwQuery.base_guid.num_allocated;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_guid.uid = fwQuery.base_guid_orig.uid;
    _fsCtrlImgInfo.orig_fs3_uids_info.cx4_uids.base_guid.num_allocated = fwQuery.base_guid_orig.num_allocated;

    _fwImgInfo.ext_info.pci_device_id = fwQuery.dev_id;
    _fwImgInfo.ext_info.dev_type = fwQuery.dev_id;
    _hwDevId = fwQuery.hw_dev_id;
    _fwImgInfo.ext_info.dev_rev = fwQuery.rev_id;
    _fwImgInfo.ext_info.is_failsafe = true;

    _fsCtrlImgInfo.security_mode = (security_mode_t)
                                   (SMM_MCC_EN |
                                    ((fwQuery.security_type.debug_fw  == 1) ? SMM_DEBUG_FW  : 0) |
                                    ((fwQuery.security_type.signed_fw == 1) ? SMM_SIGNED_FW : 0) |
                                    ((fwQuery.security_type.secure_fw == 1) ? SMM_SECURE_FW : 0) |
                                    ((fwQuery.security_type.dev_fw    == 1) ? SMM_DEV_FW    : 0));

    _fsCtrlImgInfo.sec_boot = fwQuery.sec_boot;
    _fsCtrlImgInfo.life_cycle = fwQuery.life_cycle;
    _fsCtrlImgInfo.encryption = fwQuery.encryption;
    std::vector<FwComponent> compsMap;
    if (!_fwCompsAccess->getFwComponents(compsMap, false)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to get the FW Components MAP, err[%d]", _fwCompsAccess->getLastError());
    }
    for (std::vector<FwComponent>::iterator it = compsMap.begin(); it != compsMap.end(); it++) {
        if (it->getStatus() == FwComponent::COMPSTAT_PRESENT || it->getStatus() == FwComponent::COMPSTAT_IN_USE) {
            if (it->getType() == FwComponent::COMPID_CS_TOKEN) {
                _fsCtrlImgInfo.security_mode |= SMM_CS_TOKEN;
            }
            if (it->getType() == FwComponent::COMPID_DBG_TOKEN) {
                _fsCtrlImgInfo.security_mode |= SMM_DBG_TOKEN;
            }
            if (it->getType() == FwComponent::COMPID_CRYPTO_TO_COMMISSIONING) {
                _fsCtrlImgInfo.security_mode |= SMM_CRYTO_TO_COMMISSIONING;
            }
            if (it->getType() == FwComponent::COMPID_RMCS_TOKEN) {
                _fsCtrlImgInfo.security_mode |= SMM_RMCS_TOKEN;
            }
            if (it->getType() == FwComponent::COMPID_RMDT_TOKEN) {
                _fsCtrlImgInfo.security_mode |= SMM_RMDT_TOKEN;
            }
        }
    }

    strcpy(_fwImgInfo.ext_info.psid, fwQuery.psid);
    strcpy(_fsCtrlImgInfo.orig_psid, fwQuery.psid);

    /*
     * MFSV (Manangment FW Security Version)
     */
    u_int8_t mfsv_reg_supported = 0;
    reg_access_status_t rc = ME_ERROR;
    mfile* mf = getMfileObj();

    // Check if MFSV (register-id 0x9115) is supported
    tools_open_mcam mcam;
    memset(&mcam, 0, sizeof(mcam));
    mcam.access_reg_group = 2;
    rc = reg_access_mcam(mf, REG_ACCESS_METHOD_GET, &mcam);
    if (rc == ME_OK){
        mfsv_reg_supported = EXTRACT(mcam.mng_access_reg_cap_mask[13], 5, 1); // bit 21 
    }
    DPRINTF(("mfsv_reg_supported = %d\n",mfsv_reg_supported));

    if (_fsCtrlImgInfo.sec_boot == 1 && _fsCtrlImgInfo.life_cycle == GA_SECURED && mfsv_reg_supported == 1){
        _fsCtrlImgInfo.device_security_version_access_method = MFSV;
    } else {
        _fsCtrlImgInfo.device_security_version_access_method = NOT_VALID;
    }

    // GET MFSV 
    if (mfsv_reg_supported == 1){
        struct reg_access_hca_mfsv_reg mfsv_reg;
        memset(&mfsv_reg, 0, sizeof(mfsv_reg));
        rc = reg_access_mfsv(mf, REG_ACCESS_METHOD_GET, &mfsv_reg);
        if (rc == ME_OK){
            //// reg_access_hca_mfsv_reg_print(&mfsv_reg, stdout, 4);
            memcpy(&(_fsCtrlImgInfo.device_security_version_mfsv),  &mfsv_reg,  sizeof(reg_access_hca_mfsv_reg)); 
        }
    }

    //* Read global image status
    if (_fsCtrlImgInfo.sec_boot == true) {        
        try {            
            CRSpaceRegisters cr_space_reg(mf, _fwImgInfo.ext_info.chip_type);
            _fsCtrlImgInfo.global_image_status = cr_space_reg.getGlobalImageStatus();
        }
        catch(logic_error e) {
            printf("%s\n", e.what());
            return false;

        }
        catch(exception e) {
            printf("%s\n", e.what());
            return false;
        }
    }

    /*
     * Fill ROM info
     */

    _fwImgInfo.ext_info.roms_info.num_of_exp_rom = fwQuery.nRoms;
    _fwImgInfo.ext_info.roms_info.exp_rom_found = fwQuery.nRoms > 0;
    for (int i = 0; i < fwQuery.nRoms; i++) {
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_product_id = fwQuery.roms[i].type;
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_proto = 0xff; // NA
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_supp_cpu_arch = fwQuery.roms[i].arch;
        _fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_num_ver_fields = FwOperations::RomInfo::getNumVerFromProdId(_fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_product_id);
        extractFwVersion(_fwImgInfo.ext_info.roms_info.rom_info[i].exp_rom_ver, fwQuery.roms[i].version);
    }

    strncpy(_fsCtrlImgInfo.name, fwQuery.name, NAME_LEN);
    strncpy(_fsCtrlImgInfo.description, fwQuery.description, DESCRIPTION_LEN);
    (strncpy(_fsCtrlImgInfo.deviceVsd, fwQuery.deviceVsd, VSD_LEN));
    if (FwType() == FIT_FS3) {
        memcpy(_fwImgInfo.ext_info.vsd, fwQuery.deviceVsd, VSD_LEN);
    }
    (strncpy(_fsCtrlImgInfo.image_vsd, fwQuery.imageVsd, VSD_LEN));
    return true;
}

void FsCtrlOperations::ExtractSwitchFWVersion(const fwInfoT& fwQuery)
{
    if (VerifyBranchFormat(fwQuery.imageVsd)) {
        strncpy(_fwImgInfo.ext_info.running_branch_ver, fwQuery.imageVsd, BRANCH_LEN);
    }
    if (fwQuery.running_fw_version.version_string_length &&
        fwQuery.running_fw_version.version_string_length <= BRANCH_LEN) {
        extractFwVersion(_fwImgInfo.ext_info.fw_ver, (const char*)fwQuery.running_fw_version.version_string);
        extractFwVersion(_fwImgInfo.ext_info.running_fw_ver, (const char*)fwQuery.running_fw_version.version_string);
    }
    if (fwQuery.pending_fw_version.version_string_length &&
        fwQuery.pending_fw_version.version_string_length <= BRANCH_LEN) {
        extractFwVersion(_fwImgInfo.ext_info.fw_ver, (const char*)fwQuery.pending_fw_version.version_string);
    }

    // Copying VSD to branch_ver makes sure that when checking if pending equals running (operator==)
    // it will evaluate to "true" (this happens in FwVersion class)
    if ((_fwImgInfo.ext_info.fw_ver[0] == _fwImgInfo.ext_info.running_fw_ver[0]) &&
        (_fwImgInfo.ext_info.fw_ver[1] == _fwImgInfo.ext_info.running_fw_ver[1]) &&
        (_fwImgInfo.ext_info.fw_ver[2] == _fwImgInfo.ext_info.running_fw_ver[2])) {
        strncpy(_fwImgInfo.ext_info.branch_ver, fwQuery.imageVsd, BRANCH_LEN);
    }
}

bool FsCtrlOperations::FwReactivateImage()
{
    if (!_fwCompsAccess->fwReactivateImage()) {
        fw_comps_error_t errCode = _fwCompsAccess->getLastError();
        switch (errCode) {
        case FWCOMPS_IMAGE_REACTIVATION_PROHIBITED_FW_VER_ERR:
            return errmsg(MLXFW_IMAGE_REACTIVATION_PROHIBITED_FW_VER_ERR, "Prohibited by current FW version");
        case FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_COPY_FAILED:
            return errmsg(MLXFW_IMAGE_RACTIVATION_FIRST_PAGE_COPY_FAILED, "First page copy failed");
        case FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_ERASE_FAILED:
            return errmsg(MLXFW_IMAGE_REACTIVATION_FIRST_PAGE_ERASE_FAILED, "First page erase failed");
        case FWCOMPS_IMAGE_REACTIVATION_FIRST_PAGE_RESTORE_FAILED:
            return errmsg(MLXFW_IMAGE_REACTIVATION_FIRST_PAGE_RESTORE_FAILED, "First page restore failed");
        case FWCOMPS_IMAGE_REACTIVATION_FW_DEACTIVATION_FAILED:
            return errmsg(MLXFW_IMAGE_REACTIVATION_FW_DEACTIVATION_FAILED, "FW deactivation failed");
        case FWCOMPS_IMAGE_REACTIVATION_FW_ALREADY_ACTIVATED:
            return errmsg(MLXFW_IMAGE_REACTIVATION_FW_ALREADY_ACTIVATED, "FW already reactivated");
        case FWCOMPS_IMAGE_REACTIVATION_ERROR_DEVICE_RESET_REQUIRED:
            return errmsg(MLXFW_IMAGE_REACTIVATION_ERROR_DEVICE_RESET_REQUIRED, "FW reset required");
        case FWCOMPS_IMAGE_REACTIVATION_FW_PROGRAMMING_NEEDED:
            return errmsg(MLXFW_IMAGE_REACTIVATION_FW_PROGRAMMING_NEEDED, "FW programming needed");
        case FWCOMPS_GENERAL_ERR:
            return errmsg(MLXFW_ERR, "FW ICMD related error");
        case FWCOMPS_IMAGE_REACTIVATION_WAITING_TIME_EXPIRED:
            return errmsg(MLXFW_ERR, "Image reactivation - timeout expired");
        case FWCOMPS_IMAGE_REACTIVATION_FW_NOT_SUPPORTED:
            return errmsg(MLXFW_ERR, "Image reactivation - FW doesn't support this operation");
        default:
            return errmsg(MLXFW_IMAGE_REACTIVATION_UNKNOWN_ERROR, "Unknown error occurred");
        }
    }
    return true;
}

bool FsCtrlOperations::FwQuery(fw_info_t *fwInfo, bool readRom, bool isStripedImage, bool quickQuery, bool ignoreDToc, bool verbose)
{
    (void) isStripedImage;
    (void) readRom;
    (void) quickQuery;
    (void) ignoreDToc;
    (void) verbose;
    memcpy(&(fwInfo->fw_info), &(_fwImgInfo.ext_info), sizeof(fw_info_com_t));
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

bool FsCtrlOperations::FwVerifyAdv(ExtVerifyParams &verifyParams)
{
    bool ret = true;
    FwOperations *imageOps = NULL;
    if (!_createImageOps(&imageOps))
    {
        return errmsg("%s", err());
    }

    bool image_encrypted = false;
    if (!imageOps->isEncrypted(image_encrypted)) {
        errmsg(imageOps->getErrorCode(), "%s", imageOps->err());
        ret = false;
    }
    else if (image_encrypted) {
        errmsg("Cannot verify an encrypted flash");
        ret = false;
    }
    else if (!imageOps->FwVerify(verifyParams.verifyCallBackFunc, verifyParams.isStripedImage, verifyParams.showItoc, true)) {
        errmsg(imageOps->getErrorCode(), "%s", imageOps->err());
        ret = false;
    }

    delete imageOps;
    return ret;
}

bool FsCtrlOperations::FwReadData(void *image, u_int32_t *image_size, bool verbose)
{
    (void) image;
    (void) image_size;
    (void) verbose;
    return errmsg("Read image is not supported");
}

bool FsCtrlOperations::ReadBootImage(void *image, u_int32_t *image_size, ProgressCallBackAdvSt *stProgressFunc)
{
    if (image) {
        FwComponent bootImgComp;
        if (!_fwCompsAccess->readComponent(FwComponent::COMPID_BOOT_IMG, bootImgComp, true, (ProgressCallBackAdvSt*) stProgressFunc)) {
            if (!_fwCompsAccess->readComponent(FwComponent::COMPID_BOOT_IMG, bootImgComp, false, (ProgressCallBackAdvSt*) stProgressFunc)) {
                return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to read boot image, %s - RC[%d]", _fwCompsAccess->getLastErrMsg(), (int) _fwCompsAccess->getLastError());
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

bool FsCtrlOperations::FwReadRom(std::vector<u_int8_t> &romSect)
{
    (void) romSect;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwBurnRom(FImage *romImg, bool ignoreProdIdCheck, bool ignoreDevidCheck,
                                 ProgressCallBack progressFunc)
{
    (void) romImg;
    (void) ignoreDevidCheck;
    (void) ignoreProdIdCheck;
    (void) progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    (void) ignoreProdIdCheck;
    (void) progressFunc;
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

bool FsCtrlOperations::BadParamErrMsg(const char *unSupportedOperation, bool isSecure)
{
    const char *noCtrlFwReccomendation = "";
    const char *fwType = "Secure";
    if (!isSecure) {
        noCtrlFwReccomendation = " You can try to run again with the flag \"--no_fw_ctrl\".";
        fwType = "controlled";
    }
    return errmsg(MLXFW_UNSUPPORTED_PARAM, "%s is unsupported under %s FW.%s", unSupportedOperation, fwType, noCtrlFwReccomendation);
}

bool FsCtrlOperations::VerifyAllowedParams(ExtBurnParams &burnParams, bool isSecure)
{
    if (burnParams.vsdSpecified) {
        return BadParamErrMsg("Specifying vsd", isSecure);
    } else if (!burnParams.burnFailsafe) {
        return BadParamErrMsg("Burning in non-failsafe mode", isSecure);
    } else if (burnParams.allowPsidChange) {
        return BadParamErrMsg("Changing PSID", isSecure);
    } else if (burnParams.useImagePs) {
        return BadParamErrMsg("Burning vsd as appears in the given image", isSecure);
    } else if (burnParams.noDevidCheck) {
        return BadParamErrMsg("Not checking device id", isSecure);
    } else if (burnParams.useImgDevData) {
        return BadParamErrMsg("Using image device data", isSecure);
    } else if (burnParams.useDevImgInfo) {
        return BadParamErrMsg("Using device image info", isSecure);
    } else if (burnParams.burnRomOptions == ExtBurnParams::BRO_FROM_DEV_IF_EXIST) {
        return BadParamErrMsg("Burning ROM from device", isSecure);
    }
    return true;
}

bool FsCtrlOperations::_createImageOps(FwOperations** imageOps)
{
    u_int32_t imageSize = 0;
    if (!ReadBootImage(NULL, &imageSize)) {
        return errmsg("Failed to get boot image size");
    }
    std::vector<u_int8_t> imageData;
    imageData.resize(imageSize);
    if (!ReadBootImage((void*)imageData.data(), &imageSize)) {
        return errmsg("Failed to read boot image");
    }
    fw_ops_params_t imageParams;
    memset(&imageParams, 0, sizeof(imageParams));
    imageParams.buffHndl = (u_int32_t*)imageData.data();
    imageParams.buffSize = imageSize;
    imageParams.hndlType = FHT_FW_BUFF;
    imageParams.ignoreCrcCheck = _fwParams.ignoreCrcCheck;
    *imageOps = FwOperations::FwOperationsCreate(imageParams);
    if (!(*imageOps)) {
        return errmsg("Failed to create image ops");
    }
    return true;
}

bool FsCtrlOperations::getITOCAddr(u_int32_t& addr)
{
    vector<u_int8_t> buff(IMAGE_LAYOUT_HW_POINTERS_CARMEL_SIZE);
    if (!FwReadBlock(FS4_HW_PTR_START, buff.size(), buff))
    {
        return errmsg("Failed to read HW pointers from flash");
    }

    struct image_layout_hw_pointers_carmel hw_pointers;
    image_layout_hw_pointers_carmel_unpack(&hw_pointers, buff.data());
    addr = hw_pointers.toc_ptr.ptr;
    return true;
}

bool FsCtrlOperations::CheckITOCSignature(u_int8_t* signature)
{
    const u_int32_t expected_sig[] = {0x49544f43, 0x04081516, 0x2342cafa, 0xbacafe00};
    for (int i = 0; i < 4; i++)
    {
        u_int32_t sig_dword = ((u_int32_t*)signature)[i];
        TOCPU1(sig_dword);
        DPRINTF(("Comparing itoc_sig[%d]=0x%x with expected_sig[%d]=0x%x\n", i, sig_dword, i, expected_sig[i]));
        if (sig_dword != expected_sig[i])
        {
            return false;
        }
    }
    return true;
}

bool FsCtrlOperations::isEncrypted(bool& is_encrypted)
{
    is_encrypted = _fsCtrlImgInfo.encryption;
    DPRINTF(("FsCtrlOperations::isEncrypted() = %s\n", is_encrypted ? "TRUE" : "FALSE"));
    return true;
}

bool FsCtrlOperations::FwBurnAdvanced(std::vector <u_int8_t> imageOps4MData, ExtBurnParams& burnParams, FwComponent::comps_ids_t ComponentId)
{
    return _Burn(imageOps4MData, burnParams, ComponentId);
}

bool FsCtrlOperations::FwBurnAdvanced(FwOperations *imageOps, ExtBurnParams &burnParams)
{
    if (imageOps == NULL) {
        return errmsg("bad parameter is given to FwBurnAdvanced\n");
    }
    if (!FsIntQuery()) {
        return false;
    }
    fw_info_t fw_query;
    memset(&fw_query, 0, sizeof(fw_info_t));
    if (!imageOps->FwQuery(&fw_query, true)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "Failed to query the image\n");
    }
    if (!VerifyAllowedParams(burnParams, fw_query.fs3_info.security_mode & SMM_SECURE_FW)) {
        return false;
    }
    if (!CheckPSID(*imageOps, false)) {
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
    // Check TimeStamp
    if (!TestAndSetTimeStamp(imageOps)) {
        return false;
    }
    std::vector <u_int8_t> imageOps4MData;
    if (!imageOps->FwExtract4MBImage(imageOps4MData, true)) {
        return errmsg(imageOps->getErrorCode(), "Failed to Extract 4MB from the image");
    }
    return _Burn(imageOps4MData, burnParams);
}

bool FsCtrlOperations::burnEncryptedImage(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    return FwBurnAdvanced(imageOps, burnParams);
}

bool FsCtrlOperations::_Burn(std::vector <u_int8_t> imageOps4MData, ExtBurnParams& burnParams, FwComponent::comps_ids_t ComponentId)
{
#ifdef UEFI_BUILD
    burnParams.ProgressFuncAdv.uefi_func = burnParams.progressFunc;
#else
    burnParams.progressFunc = (ProgressCallBack) NULL;
#endif
    FwComponent bootImageComponent;
    std::vector<FwComponent> compsToBurn;

    bootImageComponent.init(imageOps4MData, imageOps4MData.size(), ComponentId);
    compsToBurn.push_back(bootImageComponent);
    if (!_fwCompsAccess->lock_flash_semaphore()) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "%s", _fwCompsAccess->getLastErrMsg());
    }
    if (_fwCompsAccess->isMCDDSupported()) {
        // Checking if BME is disabled to print indication to user
        bool isBmeSet = DMAComponentAccess::isBMESet(_fwCompsAccess->getMfileObj());
        if (!isBmeSet) {
            printf("-W- DMA burning is not supported due to BME is unset (Bus Master Enable).\n");
        }
    }
    if (!_fwCompsAccess->burnComponents(compsToBurn, &burnParams.ProgressFuncAdv)) {
        _fwCompsAccess->unlock_flash_semaphore();
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "%s", _fwCompsAccess->getLastErrMsg());
    }
    _fwCompsAccess->unlock_flash_semaphore();
    return true;
}


bool FsCtrlOperations::FwBurnBlock(FwOperations *imageOps, ProgressCallBack progressFunc)
{
    (void) imageOps;
    (void) progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwWriteBlock(u_int32_t addr, std::vector<u_int8_t> dataVec, ProgressCallBack progressFunc)
{
    (void) addr;
    (void) dataVec;
    (void) progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetGuids(sg_params_t &sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc)
{
    (void) callBackFunc;
    (void) progressFunc;
    mac_guid_t macGuid;

    memset(&macGuid, 0, sizeof(macGuid));

    if (sgParam.userGuids.empty()) {
        return errmsg("Base GUID not found.");
    }
    if (!sgParam.guidsSpecified && !sgParam.macsSpecified && !sgParam.uidSpecified) {
        return errmsg("base GUID/MAC were not specified.");
    }
    if (!sgParam.updateCrc || sgParam.numOfGUIDs != 0 || sgParam.stepSize != 0 || sgParam.numOfGUIDsPP[0] != 0xff || sgParam.numOfGUIDsPP[1] != 0xff || sgParam.stepSizePP[0] != 0xff || sgParam.stepSizePP[1] != 0xff) {
        return errmsg("Tried to set unsupported values. Allowed values to set are mac,guid,uid.");
    }

    if (sgParam.uidSpecified) {
        macGuid.guid = sgParam.userGuids[0];
        u_int64_t baseMac = (((u_int64_t) macGuid.guid.l & 0xffffff) | (((u_int64_t) macGuid.guid.h & 0xffffff00) << 16));
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
                return errmsg("Bad MAC (" MAC_FORMAT ") given: %s. Please specify a valid MAC value", sgParam.userGuids[1].h, sgParam.userGuids[1].l, err());
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
    if (!_fwCompsAccess->setMacsGuids(macGuid)) {
        return errmsg(FwCompsErrToFwOpsErr(_fwCompsAccess->getLastError()), "%s", _fwCompsAccess->getLastErrMsg());
    }
    return true;
}

bool FsCtrlOperations::FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc)
{
    (void) baseGuid;
    (void) callBackFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc)
{
    (void) baseGuid;
    (void) callBackFunc;
    return unsupportedOperation();
}

// use progressFunc when dealing with FS2 image and printFunc when dealing with FS3 image.
bool FsCtrlOperations::FwSetVSD(char *vsdStr, ProgressCallBack progressFunc, PrintCallBack printFunc)
{
    (void) vsdStr;
    (void) printFunc;
    (void) progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetVPD(char *vpdFileStr, PrintCallBack callBackFunc)
{
    (void) vpdFileStr;
    (void) callBackFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc)
{
    (void) userKey;
    (void) progressFunc;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwGetSection(u_int32_t sectType, std::vector<u_int8_t> &sectInfo, bool stripedImage)
{
    (void) sectInfo;
    (void) sectType;
    (void) stripedImage;
    return unsupportedOperation();
}

bool FsCtrlOperations::FwResetNvData()
{
    return unsupportedOperation();
}

bool FsCtrlOperations::FwShiftDevData(PrintCallBack progressFunc)
{
    (void) progressFunc;
    return unsupportedOperation();
}

const char* FsCtrlOperations::FwGetResetRecommandationStr()
{
#if defined(__VMKERNEL_UW_NATIVE__)
    return REBOOT_REQUIRED_STR;
#else
    return REBOOT_OR_FWRESET_REQUIRED_STR;
#endif
}

bool FsCtrlOperations::FwCalcMD5(u_int8_t md5sum[16])
{
    (void) md5sum;
    return unsupportedOperation();
}

FsCtrlOperations::~FsCtrlOperations()
{
    if (_fwCompsAccess) {
        delete _fwCompsAccess;
        _fwCompsAccess = (FwCompsMgr*)NULL;
    }
}

bool FsCtrlOperations::FwReadBlock(u_int32_t addr, u_int32_t size, std::vector<u_int8_t> &dataVec)
{
    DPRINTF(("Read from flash using MCC"));
    if (!_fwCompsAccess->readBlockFromComponent(FwComponent::COMPID_BOOT_IMG, addr, size, dataVec)) {
        fw_comps_error_t errCode = _fwCompsAccess->getLastError();
        if (errCode == FWCOMPS_READ_OUTSIDE_IMAGE_RANGE) {
            return errmsg(MLXFW_BAD_PARAM_ERR, "Reading %#x bytes from address %#x is out of flash limits\n", size, (unsigned int) addr);
        } else {
            return errmsg(MLXFW_FLASH_READ_ERR, "%s", _fwCompsAccess->getLastErrMsg());
        }
    }
    return true;
}

int FsCtrlOperations::FwCompsErrToFwOpsErr(fw_comps_error_t err)
{
    int fwOpsErr = MLXFW_OK;
    switch (err) {
    case FWCOMPS_MCC_ERR_REJECTED_DIGEST_ERR:
        fwOpsErr = MLXFW_BURN_REJECTED_DIGEST_ERR;
        break;

    case FWCOMPS_MCC_ERR_REJECTED_NOT_APPLICABLE:
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


Tlv_Status_t FsCtrlOperations::GetTsObj(TimeStampIFC **tsObj)
{
    *tsObj = TimeStampIFC::getIFC(_fwCompsAccess->getMfileObj());
    return TS_OK;
}

bool FsCtrlOperations::FwSetTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer)
{
    TimeStampIFC *tsObj;
    Tlv_Status_t rc;

    if (GetTsObj(&tsObj)) {
        return errmsg("Failed to set timestamp. %s", err());
    }

    rc = tsObj->setTimeStamp(timestamp, fwVer);
    if (rc) {
        errmsg("%s", tsObj->err());
    }
    delete tsObj;
    return rc ? false : true;
}

bool FsCtrlOperations::FwResetTimeStamp()
{
    TimeStampIFC *tsObj;
    Tlv_Status_t rc;

    if (GetTsObj(&tsObj)) {
        return errmsg("Failed to reset timestamp. %s", err());
    }
    rc = tsObj->resetTimeStamp();
    if (rc) {
        errmsg("%s", tsObj->err());
    }
    delete tsObj;
    return rc ? false : true;
}

bool FsCtrlOperations::FwQueryTimeStamp(struct tools_open_ts_entry& timestamp, struct tools_open_fw_version& fwVer, bool queryRunning)
{
    TimeStampIFC *tsObj;
    Tlv_Status_t rc;

    if (GetTsObj(&tsObj)) {
        return errmsg("Failed to query timestamp. %s", err());
    }

    rc = tsObj->queryTimeStamp(timestamp, fwVer, queryRunning);
    if (rc) {
        errmsg("%s", tsObj->err());
    }
    delete tsObj;
    return rc ? false : true;
}

bool FsCtrlOperations::IsSecureBootSupported()
{
    return _signatureMngr->IsSecureBootSupported();
}

bool FsCtrlOperations::IsLifeCycleSupported()
{
    return _signatureMngr->IsLifeCycleSupported();
}

bool FsCtrlOperations::IsCableQuerySupported()
{
    return _signatureMngr->IsCableQuerySupported();
}

bool FsCtrlOperations::IsEncryptionSupported()
{
    return _signatureMngr->IsEncryptionSupported();
}

bool FsCtrlOperations::IsSecurityVersionViolated(u_int32_t image_security_version)
{
    // Set image security-version
    u_int32_t imageSecurityVersion = image_security_version;
    u_int32_t deviceEfuseSecurityVersion;

    if (getenv("FLINT_IGNORE_SECURITY_VERSION_CHECK") != NULL) {
        return false;
    }
    
    // Set device security-version (from EFUSEs)
    if (_fsCtrlImgInfo.device_security_version_access_method == MFSV) {
        deviceEfuseSecurityVersion = _fsCtrlImgInfo.device_security_version_mfsv.efuses_sec_ver;
    } else if (_fsCtrlImgInfo.device_security_version_access_method == GW) {
        deviceEfuseSecurityVersion = _fsCtrlImgInfo.device_security_version_gw;
    } else {
        deviceEfuseSecurityVersion = 0;
    }

    // Check violation of security-version
    return (imageSecurityVersion < deviceEfuseSecurityVersion);
}