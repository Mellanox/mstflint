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


// #include <stdlib.h>

#include "mlxfwops.h"
#include "fw_ops.h"
#include "fs_checks.h"
#ifdef UEFI_BUILD
    #include "uefi_c.h"
#endif

#define ERR_BUFF_SIZE 1024

bool nextBootFwVer = false;

MLXFWOP_API int MLXFWOPCALL mlxfw_open_device_adv(mlxfwops_t **mlxfwops_p, fwops_params_t* params)
{
    FwOperations::fw_ops_params_t fwParams;
    memset(&fwParams, 0, sizeof(fwParams));
    fwParams.mstHndl = params->device_name;
    fwParams.errBuff = params->buf;
    fwParams.errBuffSize = params->buf_size;
    fwParams.mccUnsupported = params->mcc_unsupported;
    fwParams.noFwCtrl = params->no_fw_ctrl;
    fwParams.hndlType = FHT_MST_DEV;
    fwParams.forceLock = false;
    fwParams.readOnly = false;
    fwParams.numOfBanks = -1;
    fwParams.ignoreCacheRep = 0;
    fwParams.noFlashVerify = false;
    fwParams.flashParams = (flash_params_t*)NULL;
    fwParams.shortErrors = true;
    *mlxfwops_p = (mlxfwops_t*) FwOperations::FwOperationsCreate(fwParams);
    if (*mlxfwops_p == NULL) {
        return MLXFW_MEM_ERR;
    }
    return MLXFW_OK;
}

int mlxfw_open_int(mlxfwops_t **mlxfwops_p, void *fw_hndl, void *extra, char *psid, fw_hndl_type_t hndl_type, char *err_buf, int buf_size)
{
    *mlxfwops_p = (mlxfwops_t*) FwOperations::FwOperationsCreate((void*)fw_hndl, extra, psid, hndl_type, err_buf, buf_size);
    if (*mlxfwops_p == NULL) {
        return MLXFW_MEM_ERR;
    }
    return MLXFW_OK;
}

FwOperations::ExtBurnParams initBurnParams(u_int8_t force_version, f_prog_func prog_func, int allow_psid_change)
{
    FwOperations::ExtBurnParams burnParams = FwOperations::ExtBurnParams();
    burnParams.ignoreVersionCheck = force_version;
    burnParams.progressFunc = prog_func;
    burnParams.allowPsidChange = allow_psid_change ? true : false;
    burnParams.shift8MBIfNeeded = true;
    return burnParams;
}

MLXFWOP_API int MLXFWOPCALL mlxfw_open_device_verbose(mlxfwops_t **mlxfwops_p, char *device_name, char *buf, int buf_size)
{
    return mlxfw_open_int(mlxfwops_p, device_name, NULL, (char*)NULL, FHT_MST_DEV, buf, buf_size);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_open_device(mlxfwops_t **mlxfwops_p, char *handle_name)
{
    return mlxfw_open_int(mlxfwops_p, handle_name, NULL, (char*)NULL, FHT_MST_DEV, (char*)NULL, 0);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_open_image(mlxfwops_t **mlxfwops_p, char *file_name, char *psid)
{
    return mlxfw_open_int(mlxfwops_p, file_name, NULL, psid, FHT_FW_FILE, (char*)NULL, 0);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_open_buffer(mlxfwops_t **mlxfwops_p, void *buffer, u_int32_t size, char *psid)
{
    return mlxfw_open_int(mlxfwops_p, buffer, &size, psid, FHT_FW_BUFF, (char*)NULL, 0);
}

#ifdef CABLES_SUPP
MLXFWOP_API int MLXFWOPCALL mlxfw_open_cable(mlxfwops_t **mlxfwops_p, char *handle_name, int port)
{
    return mlxfw_open_int(mlxfwops_p, handle_name, &port, (char*)NULL, FHT_CABLE_DEV, (char*)NULL, 0);
}
#endif

#ifdef UEFI_BUILD

MLXFWOP_API int MLXFWOPCALL mlxfw_open_uefi(mlxfwops_t **mlxfwops_p, uefi_Dev_t *dev, f_fw_cmd fw_cmd_func, uefi_dev_info_t *dev_info)
{
    uefi_dev_extra_t dev_extra;
    memset(&dev_extra, 0, sizeof(dev_extra));
    dev_extra.fw_cmd_func = fw_cmd_func;
    dev_extra.dev_info = (uefi_dev_info_t)*dev_info;
    return mlxfw_open_int(mlxfwops_p, dev, (void*)&dev_extra, (char*)NULL, FHT_UEFI_DEV, (char*)NULL, 0);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_set_print(mlxfwops_t *mlxfwops, f_prog_func_str print_func)
{
    if (mlxfwops == NULL) {
        return MLXFW_BAD_PARAM_ERR;
    }
    return !static_cast<FwOperations*>((void*)mlxfwops)->FwSetPrint(print_func);
}

MLXFWOP_API const char* MLXFWOPCALL mlxfw_err2str(int err)
{
    switch (err) {
    case 0:
        return "";

    case MLXFW_ERR:
        return "General Error";

    case MLXFW_MEM_ERR:
        return "Memory allocation Error";

    case MLXFW_ERR_IN_STR:
        return "Error in String";

    case MLXFW_PSID_MISMATCH_ERR:
        return "PSID Mismatch";

    case MLXFW_FLASH_WRITE_ERR:
        return "Flash write Failed";

    case MLXFW_NO_VALID_IMAGE_ERR:
        return "No valid image found";

    case MLXFW_MULTIPLE_VALID_IMAGES_ERR:
        return "More than one valid image found";

    case MLXFW_BAD_CRC_ERR:
        return "Bad CRC";

    case MLXFW_BAD_CHECKSUM_ERR:
        return "Bad Checksum";

    case MLXFW_SECTION_TOO_LARGE_ERR:
        return "Section too large";

    case MLXFW_SECTION_CORRUPTED_ERR:
        return "Section is corrupted";

    case MLXFW_IMAGE_NOT_FS_ERR:
        return "Image is not failsafe";

    case MLXFW_IMAGE_TOO_LARGE_ERR:
        return "Image too large";

    case MLXFW_IMAGE_FORMAT_ERR:
        return "Incompatible image format";

    case MLXFW_DEVICE_IMAGE_MISMATCH_ERR:
        return "FW image does not match device";

    case MLXFW_IMAGE_CORRUPTED_ERR:
        return "FW image corrupted";

    case MLXFW_FS_INFO_MISMATCH_ERR:
        return "Failsafe information mismatch";

    case MLXFW_DEV_ID_ERR:
        return "Unsupported device ID";

    case MLXFW_UNSUPPORTED_BIN_VER_ERR:
        return "Unsupported binary version";

    case MLXFW_NO_VALID_ITOC_ERR:
        return "No valid ITOC found";

    case MLXFW_NO_MFG_ERR:
        return "No MFG_INFO section found";

    case MLXFW_UNKNOWN_SECT_VER_ERR:
        return "Unknown Section Version";

    case MLXFW_OCR_ERR:
        return "-ocr flag must be specified";

    case MLXFW_OPEN_OCR_ERR:
        return "Failed to open device for flash direct access";

    case MLXFW_FW_ALREADY_UPDATED_ERR:
        return "FW already updated";

    case MLXFW_ROM_UPDATE_IN_IMAGE_ERR:
        return "Failed to update Exp-ROM in image";

    case MLXFW_GET_SECT_ERR:
        return "Failed to get Section";

    case MLXFW_UPDATE_SECT_ERR:
        return "Failed to update section";

    case MLXFW_BAD_PARAM_ERR:
        return "Bad parameter";
    case MLXFW_FS_CHECKS_ERR:
        return "Fixes are needed for Flash layout, an error occurred while preparing the operation";
    default:
        return "Unknown Error";
    }
}

#endif

MLXFWOP_API int MLXFWOPCALL mlxfw_burn(mlxfwops_t *dev_mlxfwops, mlxfwops_t *img_mlxfwops, u_int8_t force_version, f_prog_func prog_func, int allow_psid_change)
{
    if (dev_mlxfwops == NULL || img_mlxfwops == NULL) {
        return MLXFW_BAD_PARAM_ERR;
    }
    FwOperations::ExtBurnParams burnParams = initBurnParams(force_version, prog_func, allow_psid_change);
    bool rc = !static_cast<FwOperations*>((void*)dev_mlxfwops)->FwBurnAdvanced(static_cast<FwOperations*>((void*)img_mlxfwops),burnParams);
    int errorCode = static_cast<FwOperations*>((void*)dev_mlxfwops)->getErrorCode(); // the class's verbose error code
    return rc ? ( errorCode ? errorCode : rc) : rc;
}

MLXFWOP_API int MLXFWOPCALL mlxfw_fs_check_and_update(fw_info_t *fw_info, mlxfwops_t **dev_mlxfwops_p, mlxfwops_t *img_mlxfwops,
        u_int8_t force_version, f_prog_func prog_func, int allow_psid_change/*, mlxfwparams_t* fwParams*/)
{
    if (dev_mlxfwops_p == NULL || *dev_mlxfwops_p == NULL || img_mlxfwops == NULL) {
        return MLXFW_BAD_PARAM_ERR;
    }

    mlxfwops_t* dev_mlxfwops= *dev_mlxfwops_p;

    FwOperations::ExtBurnParams burnParams = initBurnParams(force_version, prog_func, allow_psid_change);
    FwOperations::fw_ops_params_t fwParams;
    (static_cast<FwOperations*>((void*)dev_mlxfwops))->GetFwParams(fwParams);

    FsChecks fsChecks(*fw_info, static_cast<FwOperations*>((void*)dev_mlxfwops),
            static_cast<FwOperations*>((void*)img_mlxfwops), burnParams,
            fwParams);
    if (!fsChecks.ExecuteChecks( static_cast<FwOperations**>((void*)dev_mlxfwops_p), burnParams, *fw_info)) {
        return MLXFW_FS_CHECKS_ERR;
    }

    return MLXFW_OK;
}

MLXFWOP_API int MLXFWOPCALL mlxfw_query(mlxfwops_t *mlxfwops, fw_info_t *fw_info)
{
    if (mlxfwops == NULL) {
        return MLXFW_BAD_PARAM_ERR;
    }
#ifdef UEFI_BUILD
    // skip reading ROM in UEFI due to performance issues
    return (static_cast<FwOperations*>((void*)mlxfwops)->FwQuery(fw_info, false) == true) ? MLXFW_OK :  MLXFW_ERR_IN_STR;
#else
    return (static_cast<FwOperations*>((void*)mlxfwops)->FwQuery(fw_info, true) == true) ? MLXFW_OK :  MLXFW_ERR_IN_STR;
#endif
}

MLXFWOP_API const char* MLXFWOPCALL mlxfw_exp_rom_type_to_str(u_int16_t type)
{
    return FwOperations::expRomType2Str(type);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_verify(mlxfwops_t *mlxfwops)
{
    if (mlxfwops == NULL) {
        return MLXFW_BAD_PARAM_ERR;
    }
    return !static_cast<FwOperations*>((void*)mlxfwops)->FwVerify((f_prog_func_str)NULL);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_read_image(mlxfwops_t *mlxfwops, void *image, u_int32_t *image_size)
{
    if (mlxfwops == NULL) {
        return MLXFW_BAD_PARAM_ERR;
    }
    return !(static_cast<FwOperations*>((void*)mlxfwops)->FwReadData(image, image_size));
}

MLXFWOP_API void MLXFWOPCALL mlxfw_close(mlxfwops_t *mlxfwops)
{
    if (mlxfwops) {
        static_cast<FwOperations*>((void*)mlxfwops)->FwCleanUp();
        delete static_cast<FwOperations*>((void*)mlxfwops);
        mlxfwops = (mlxfwops_t*)NULL;
    }
    return;
}

MLXFWOP_API const char* MLXFWOPCALL mlxfw_get_last_error(mlxfwops_t *mlxfwops)
{
    if (mlxfwops == NULL) {
        return "Cannot get last error - No mlxfwops handle";
    }
    return (static_cast<FwOperations*>((void*)mlxfwops)->err());
}

MLXFWOP_API int MLXFWOPCALL mlxfw_get_last_error_code(mlxfwops_t *mlxfwops)
{
    if (mlxfwops == NULL) {
        return MLXFW_BAD_PARAM_ERR;
    }
    return (static_cast<FwOperations*>((void*)mlxfwops)->getErrorCode());
}
