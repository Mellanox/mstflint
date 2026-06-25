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
#include "mlxreg_sdk.h"
#include "prm_reg_sdk.h"

/*
 * Function: send_prm_access_reg
 * ----------------------------
 * Send an access register request
 *
 * mstDev:          mst device name.
 * regName:         access register name, e.g PDDR
 * method:          access register request method:
 *                      access_type::GET to read access register state
 *                      access_type::SET to write access register (other fields will be zero)
 *                      access_type::SET_READ_MODIFY_WRITE to write access register with the current fields values
 * params:          Access register parameters to send with the request, e.g "local_port=1,pnat=0"
 *
 * responseOutbox:  Access register response, returned in a RegisterMap struct
 * returns:         0 if access register request succeed, ERR_CODE if access register failed
 */
int32_t send_prm_access_reg(const char* mst_dev,
                            const char* reg_name,
                            const access_type method,
                            const char* params,
                            RegisterMap* response_outbox)
{
    PrmRegSdk sdk_inst(mst_dev, reg_name, (uint32_t)method, params);

    return sdk_inst.performRegRequest((void*)response_outbox);
}

int32_t send_raw_access_reg(const char* mst_dev,
                            const uint16_t reg_id,
                            const access_type method,
                            void* data,
                            const uint32_t data_size)
{
    PrmRegSdk sdk_inst(mst_dev, reg_id, (uint32_t)method);

    return sdk_inst.performRawRegRequest(data, data_size);
}

int32_t init_prm_access_manager(const char* mst_dev, void** opaque)
{
    PrmRegSdk* sdk = new PrmRegSdk(mst_dev);
    uint32_t rc = sdk->initRegLib();
    if (rc != 0)
    {
        delete sdk;
    }
    else
    {
        *opaque = (void*)sdk;
    }
    return rc;
}

void free_prm_access_manager(void* opaque)
{
    if (opaque)
    {
        delete (PrmRegSdk*)opaque;
    }
}

int32_t send_seq_prm_access_reg(void* opaque,
                                const char* reg_name,
                                const access_type method,
                                const char* params,
                                RegisterMap* response_outbox)
{
    if (!opaque)
    {
        return ERR_CODE_INVALID_ACCESS_MANAGER;
    }
    ((PrmRegSdk*)opaque)->initPrmCommand(reg_name, (uint32_t)method, params);
    return ((PrmRegSdk*)opaque)->performRegRequest((void*)response_outbox);
}

/*
 * Function: init_response_outbox
 * ------------------------------
 * Initialize the response outbox
 *
 * response_outbox:  Pointer to the response map of type RegisterMap
 * returns:         0 if response outbox initialized successfully, ERR_CODE if response outbox initialization
 * failed
 */
int32_t init_response_outbox(RegisterMap* response_outbox)
{
    if (!response_outbox)
    {
        return ERR_CODE_INVALID_RESPONSE_OUTBOX;
    }
    response_outbox->number_of_fields = 0;
    response_outbox->fields = nullptr;
    return 0;
}

/*
 * Function: free_response_outbox
 * ------------------------------
 * De-allocate the fields inside the response_outbox map struct
 *
 * response_outbox:  Pointer to the response map of type RegisterMap
 */
void free_response_outbox(RegisterMap* response_outbox)
{
    if (response_outbox)
    {
        if (response_outbox->fields)
        {
            free(response_outbox->fields);
        }
        response_outbox->fields = NULL;
    }
}
