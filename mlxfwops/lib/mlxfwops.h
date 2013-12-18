
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

#ifndef MLXFWOP_H
#define MLXFWOP_H

#include <stdio.h>
#include "mlxfwops_com.h"

//#include ".h"
// struct FwOperations;
#ifdef __cplusplus
extern "C" {
#endif

typedef struct mlxfwops mlxfwops_t;

enum {
    MLXFW_OK = 0,
    MLXFW_ERR,
    MLXFW_MEM_ERR,
    MLXFW_ERR_IN_STR,
};

struct image_context {
    void * data;
    u_int32_t size;
};

MLXFWOP_API int MLXFWOPCALL mlxfw_open_device(mlxfwops_t** mlxfwops_p, char *device_name);

MLXFWOP_API int MLXFWOPCALL mlxfw_open_image(mlxfwops_t** mlxfwops_p, char *file_name, char *psid);

MLXFWOP_API int MLXFWOPCALL mlxfw_open_buffer(mlxfwops_t** mlxfwops_p, void* buffer, u_int32_t size, char *psid);


#ifdef UEFI_BUILD

MLXFWOP_API int MLXFWOPCALL mlxfw_open_uefi(mlxfwops_t** mlxfwops_p, uefi_Dev_t* dev, f_fw_cmd fw_cmd_func);
MLXFWOP_API int MLXFWOPCALL mlxfw_set_print(mlxfwops_t* mlxfwops, f_prog_func_str print_func);

#endif

MLXFWOP_API const char* MLXFWOPCALL mlxfw_get_last_error(mlxfwops_t* mlxfwops);

MLXFWOP_API int MLXFWOPCALL mlxfw_burn(mlxfwops_t* dev_mlxfwops, mlxfwops_t* img_mlxfwops, u_int8_t force_version, f_prog_func prog_func);

MLXFWOP_API int MLXFWOPCALL mlxfw_read_image(mlxfwops_t* mlxfwops, void* image, u_int32_t* image_size);

MLXFWOP_API int MLXFWOPCALL mlxfw_verify(mlxfwops_t* mlxfwops);

MLXFWOP_API int MLXFWOPCALL mlxfw_query(mlxfwops_t* mlxfwops, fw_info_t* fw_query);

MLXFWOP_API int MLXFWOPCALL mlxfw_type_match(mlxfwops_t* dev_mlxfwops, mlxfwops_t* img_mlxfwops);

MLXFWOP_API int MLXFWOPCALL mlxfw_fw_ver_less_than(u_int16_t ver_a[3], u_int16_t ver_b[3]);

MLXFWOP_API const char* MLXFWOPCALL mlxfw_exp_rom_type_to_str(u_int16_t type);

MLXFWOP_API void MLXFWOPCALL mlxfw_close(mlxfwops_t* mlxfwops);

MLXFWOP_API int MLXFWOPCALL mlxfw_test(mlxfwops_t* mlxfwops, u_int32_t *read_data);

#ifdef __cplusplus
}
#endif

#endif
