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
#ifdef UEFI_BUILD
    #include "uefi_c.h"
#endif

int mlxfw_open_int(mlxfwops_t** mlxfwops_p, void* fw_hndl, void* extra, char* psid, fw_hndl_type_t hndl_type)
{
     *mlxfwops_p = (mlxfwops_t*) FwOperations::FwOperationsCreate((void*)fw_hndl, extra, psid, hndl_type);
     if (*mlxfwops_p == NULL) {
         return MLXFW_MEM_ERR;
     }
     return MLXFW_OK;
}

MLXFWOP_API int MLXFWOPCALL mlxfw_fw_ver_less_than(u_int16_t ver_a[3], u_int16_t ver_b[3])
{
    return FwOperations::FwVerLessThan(ver_a, ver_b);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_open_device(mlxfwops_t** mlxfwops_p, char *handle_name)
{
    return mlxfw_open_int(mlxfwops_p, handle_name, NULL, (char*)NULL, FHT_MST_DEV);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_open_image(mlxfwops_t** mlxfwops_p, char *file_name, char *psid)
{
    return mlxfw_open_int(mlxfwops_p, file_name, NULL, psid, FHT_FW_FILE);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_open_buffer(mlxfwops_t** mlxfwops_p, void* buffer, u_int32_t size, char *psid)
{
    return mlxfw_open_int(mlxfwops_p, buffer, &size, psid, FHT_FW_BUFF);
}

#ifdef UEFI_BUILD
MLXFWOP_API int MLXFWOPCALL mlxfw_open_uefi(mlxfwops_t** mlxfwops_p, uefi_Dev_t* dev, f_fw_cmd fw_cmd_func)
{
    return mlxfw_open_int(mlxfwops_p, dev, (void*)fw_cmd_func, (char*)NULL, FHT_UEFI_DEV);

}

MLXFWOP_API int MLXFWOPCALL mlxfw_set_print(mlxfwops_t* mlxfwops, f_prog_func_str print_func)
{
    return !static_cast<FwOperations*>((void*)mlxfwops)->FwSetPrint(print_func);
}

#endif
/*
int mlxfw_burn(mlxfwops_t* mlxfwops, char *image_file, u_int8_t force_version)
{
    return 0;
}
*/

MLXFWOP_API int MLXFWOPCALL mlxfw_burn(mlxfwops_t* dev_mlxfwops, mlxfwops_t* img_mlxfwops, u_int8_t force_version, f_prog_func prog_func)
{
    return !static_cast<FwOperations*>((void*)dev_mlxfwops)->FwBurn(static_cast<FwOperations*>((void*)img_mlxfwops),force_version, prog_func);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_query(mlxfwops_t* mlxfwops, fw_info_t* fw_info)
{
    return (static_cast<FwOperations*>((void*)mlxfwops)->FwQuery(fw_info, true) == true) ? MLXFW_OK :  MLXFW_ERR_IN_STR;
}

MLXFWOP_API const char* MLXFWOPCALL mlxfw_exp_rom_type_to_str(u_int16_t type)
{
	return FwOperations::expRomType2Str(type);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_verify(mlxfwops_t* mlxfwops)
{
    return !static_cast<FwOperations*>((void*)mlxfwops)->FwVerify((f_prog_func_str)NULL);
}

MLXFWOP_API int MLXFWOPCALL mlxfw_read_image(mlxfwops_t* mlxfwops, void* image, u_int32_t* image_size)
{
    return !(static_cast<FwOperations*>((void*)mlxfwops)->FwReadData(image, image_size));
}

MLXFWOP_API void MLXFWOPCALL mlxfw_close(mlxfwops_t* mlxfwops)
{
    static_cast<FwOperations*>((void*)mlxfwops)->FwCleanUp();
    delete static_cast<FwOperations*>((void*)mlxfwops);
    return;
}

MLXFWOP_API const char* MLXFWOPCALL mlxfw_get_last_error(mlxfwops_t* mlxfwops)
{
    if (mlxfwops == NULL) {
        return "Cannot get last error - No mlxfwops handle";
    }
    return (static_cast<FwOperations*>((void*)mlxfwops)->err());
}
