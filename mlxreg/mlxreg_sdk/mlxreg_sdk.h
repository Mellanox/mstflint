/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *  Version: $Id$
 *
 */

#ifndef MLXREG_SDK_H_
#define MLXREG_SDK_H_

#include <stdint.h>

/* An environment variable can be used to provide an external adb file.
 * By default if the MFT is installed, then no need to set this variable, but if there is no MFT installed, then a path
 * to the external adb file (NIC or SWITCH) should be exported using this environment variable, e.g:
 * export EXTERNAL_ADB_PATH=/path/to/register_access_table.adb.
 */
#define EXTERNAL_ADB_PATH "EXTERNAL_ADB_PATH"

typedef enum
{
    GET = 1,
    SET,
    SET_READ_MODIFY_WRITE
} access_type;

typedef enum
{
    ERR_CODE_SUCCESS = 0,
    ERR_CODE_FAILD_TO_OPEN_MST_DEV = -1,
    ERR_CODE_FAILD_TO_SEND_ACCESS_REG = -2,
    ERR_CODE_FAILD_TO_PARSE_PARAMS = -3,
    ERR_CODE_FAILD_TO_INIT_REG_LIB = -4,
    ERR_CODE_FAILD_TO_FIND_REG_NODE = -5,
    ERR_CODE_FAILD_TO_PARSE_FIELD = -6,
    ERR_CODE_INVALID_FIELD_ARG = -7,
    ERR_CODE_INVALID_METHOD = -8,
    ERR_CODE_INVALID_ACCESS_MANAGER = -9,
    ERR_CODE_INVALID_RESPONSE_OUTBOX = -10,
} ERR_CODE;

typedef struct Field
{
    char name[128];
    uint32_t value;
} Field;

typedef struct RegisterMap
{
    uint32_t number_of_fields;
    Field* fields;
} RegisterMap;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    /*
     * Function: send_prm_access_reg
     * ----------------------------
     * Send an access register request
     *
     * mst_dev:         mst device name.
     * reg_name:        access register name, e.g PDDR
     * method:          access register request method:
     *                      access_type::GET to read access register state
     *                      access_type::SET to write access register (other fields will be zero)
     *                      access_type::SET_READ_MODIFY_WRITE to write access register with the current fields values
     * params:          Access register parameters to send with the request, e.g "local_port=1,pnat=0"
     *
     * response_outbox: Access register response, returned in a RegisterMap struct
     * returns:         0 if access register request succeed, ERR_CODE if access register failed
     */
    int32_t send_prm_access_reg(const char* mst_dev,
                                const char* reg_name,
                                const access_type method,
                                const char* params,
                                RegisterMap* response_outbox);

    /*
     * Function: send_raw_access_reg
     * ----------------------------
     * Send an access register request
     *
     * mst_dev:         mst device name.
     * reg_id:          access register id, e.g 0x5031
     * method:          access register request method:
     *                      access_type::GET to read access register state
     *                      access_type::SET to write access register (other fields will be zero)
     *                      access_type::SET_READ_MODIFY_WRITE to write access register with the current fields values
     *
     * data:            allocated buffer for the access register
     * data_size:       allocated size
     * returns:         0 if access register request succeed, ERR_CODE if access register failed
     */
    int32_t send_raw_access_reg(const char* mst_dev,
                                const uint16_t reg_id,
                                const access_type method,
                                void* data,
                                const uint32_t data_size);

    /*
     * Function: init_prm_access_manager
     * ----------------------------
     * Initialize the PRM access manager
     *
     * mst_dev:         mst device name.
     * opaque:          Handle to the PRM access manager
     * returns:         0 if PRM access manager initialized successfully, ERR_CODE if PRM access manager initialization
     * failed
     */
    int32_t init_prm_access_manager(const char* mst_dev, void** opaque);

    /*
     * Function: free_prm_access_manager
     * ----------------------------
     * Free the PRM access manager
     *
     * opaque:          Pointer to the PRM access manager
     */
    void free_prm_access_manager(void* opaque);

    /*
     * Function: send_seq_prm_access_reg
     * ----------------------------
     * Send a sequence of PRM access register requests
     *
     * opaque:          Pointer to the PRM access manager
     */
    int32_t send_seq_prm_access_reg(void* opaque,
                                    const char* reg_name,
                                    const access_type method,
                                    const char* params,
                                    RegisterMap* response_outbox);

    /*
     * Function: init_response_outbox
     * ----------------------------
     * Initialize the response outbox
     *
     * response_outbox:  Pointer to the response map of type RegisterMap
     * returns:         0 if response outbox initialized successfully, ERR_CODE if response outbox initialization
     * failed
     */
    int32_t init_response_outbox(RegisterMap* response_outbox);

    /*
     * Function: free_response_outbox
     * ------------------------------
     * De-allocate the fields inside the response_outbox map struct
     *
     * response_outbox:  Pointer to the response map of type RegisterMap
     */
    void free_response_outbox(RegisterMap* response_outbox);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* MLXREG_SDK_H_ */
