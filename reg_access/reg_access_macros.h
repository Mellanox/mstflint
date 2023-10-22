/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
#ifdef _ENABLE_DEBUG_
#define DEBUG_PRINT_SEND(data_struct, struct_name, method, print_func)                        \
    printf("-I- Data Sent (Method: %s):\n", method == REG_ACCESS_METHOD_SET ? "SET" : "GET"); \
    print_func(data_struct, stdout, 1)
#define DEBUG_PRINT_RECEIVE(data_struct, struct_name, method, print_func)                         \
    printf("-I- Data Received (Mehtod: %s):\n", method == REG_ACCESS_METHOD_SET ? "SET" : "GET"); \
    print_func(data_struct, stdout, 1)
#else
#define DEBUG_PRINT_SEND(data_struct, struct_name, method, print_func)
#define DEBUG_PRINT_RECEIVE(data_struct, struct_name, method, print_func)
#endif

// register access for variable size registers (like mfba)
#define REG_ACCESS_GENERIC_VAR_WITH_STATUS(mf, method, reg_id, data_struct, struct_name, reg_size, r_reg_size,      \
                                           w_reg_size, pack_func, unpack_func, size_func, print_func, status,       \
                                           is_dynamic_arr)                                                          \
    int rc;                                                                                                         \
    int max_data_size = size_func();                                                                                \
    u_int8_t* data = NULL;                                                                                          \
    if (is_dynamic_arr)                                                                                             \
    {                                                                                                               \
        max_data_size = reg_size;                                                                                   \
    }                                                                                                               \
    if (method != REG_ACCESS_METHOD_GET && method != REG_ACCESS_METHOD_SET)                                         \
    {                                                                                                               \
        return ME_REG_ACCESS_BAD_METHOD;                                                                            \
    }                                                                                                               \
    data = (u_int8_t*)malloc(sizeof(u_int8_t) * max_data_size);                                                     \
    if (!data)                                                                                                      \
    {                                                                                                               \
        return ME_MEM_ERROR;                                                                                        \
    };                                                                                                              \
    memset(data, 0, max_data_size);                                                                                 \
    pack_func(data_struct, data);                                                                                   \
    DEBUG_PRINT_SEND(data_struct, struct_name, method, print_func);                                                 \
    rc = maccess_reg(mf, reg_id, (maccess_reg_method_t)method, data, reg_size, r_reg_size, w_reg_size, status);     \
    if (rc && is_dynamic_arr)                                                                                   \
    {                                                                                                           \
        free(data);                                                                                             \
    }                                                                                                           \
    else                                                                                                        \
    {                                                                                                           \
        unpack_func(data_struct, data);                                                                         \
        free(data);                                                                                             \
        DEBUG_PRINT_RECEIVE(data_struct, struct_name, method, print_func);                                      \
    }                                                                                                           \

#define REG_ACCESS_GENERIC_VAR(mf, method, reg_id, data_struct, struct_name, reg_size, r_reg_size, w_reg_size,         \
                               pack_func, unpack_func, size_func, print_func, is_dynamic_arr)                          \
    int status = 0;                                                                                                    \
    REG_ACCESS_GENERIC_VAR_WITH_STATUS(mf, method, reg_id, data_struct, struct_name, reg_size, r_reg_size, w_reg_size, \
                                       pack_func, unpack_func, size_func, print_func, &status, is_dynamic_arr)         \
    if (rc || status)                                                                                                  \
    {                                                                                                                  \
        return (reg_access_status_t)rc;                                                                                \
    }                                                                                                                  \
    return ME_OK

/***************************************************/

/* register access for infinite size of arrays with specific size */
/* r_reg_size is how much we want to read from the struct struct_name (fw request), w_reg_size is how much we want to */
/* write to the struct that we are sending for the fw. note that the params data_p_name, data_size_name are the pointer */
/* to the array the fw should read\write to, and the size of it. */
#define REG_ACCESS_GEN_DATA_WITH_STATUS(mf, method, reg_id, data_struct, struct_name, prefix, reg_size, r_reg_size,   \
                                        w_reg_size, size_func, data_p_name, data_size_name)                           \
    u_int32_t reg_size = data_struct->data_size_name + size_func();                                                   \
    u_int32_t* t_data = data_struct->data_p_name;                                                                     \
    u_int32_t  t_offset = size_func();                                                                                \
    u_int32_t  r_size_reg = reg_size;                                                                                 \
    u_int32_t  w_size_reg = reg_size;                                                                                 \
    int        wrapper_needed = 0;                                                                                    \
    if (method == REG_ACCESS_METHOD_GET)                                                                              \
    {                                                                                                                 \
        w_size_reg -= data_struct->data_size_name;                                                                    \
    }                                                                                                                 \
    else if (method == REG_ACCESS_METHOD_SET)                                                                         \
    {                                                                                                                 \
        r_size_reg -= data_struct->data_size_name;                                                                    \
    }                                                                                                                 \
    else                                                                                                              \
    {                                                                                                                 \
        return ME_REG_ACCESS_BAD_METHOD;                                                                              \
    }                                                                                                                 \
    int       status = 0;                                                                                             \
    int       rc;                                                                                                     \
    int       max_data_size = reg_size;                                                                               \
    u_int8_t* data = (u_int8_t*)malloc(max_data_size);                                                                \
    if (!data)                                                                                                        \
    {                                                                                                                 \
        return ME_MEM_ERROR;                                                                                          \
    }                                                                                                                 \
    memset(data, 0, max_data_size);                                                                                   \
    prefix ## _ ## struct_name ## _pack(data_struct, data);                                                           \
    if (t_data)                                                                                                       \
    {                                                                                                                 \
        if ((int)t_offset + data_struct->data_size_name > max_data_size)                                              \
        {                                                                                                             \
            free(data);                                                                                               \
            return ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT;                                                                 \
        }                                                                                                             \
        memcpy(&data[t_offset], t_data, data_struct->data_size_name);                                                 \
    }                                                                                                                 \
    wrapper_needed = check_if_wrapper_needed(mf, reg_id);                                                             \
    if (wrapper_needed)                                                                                               \
    {                                                                                                                 \
        rc = crteate_wrapper_command(mf, reg_id, method, data, reg_size, r_size_reg, w_size_reg, &status);            \
        prefix ## _ ## struct_name ## _unpack(data_struct, data);                                                     \
        if (rc || status)                                                                                             \
        {                                                                                                             \
            free(data);                                                                                               \
            if (!rc)                                                                                                  \
            {                                                                                                         \
                return (reg_access_status_t)status;                                                                   \
            }                                                                                                         \
            return (reg_access_status_t)rc;                                                                           \
        }                                                                                                             \
        if (t_data)                                                                                                   \
        {                                                                                                             \
            data_struct->data_p_name = t_data;                                                                        \
            memcpy(t_data, &(data)[t_offset], data_struct->data_size_name);                                           \
        }                                                                                                             \
        free(data);                                                                                                   \
    }                                                                                                                 \
    rc = (int)maccess_reg(mf, reg_id, (maccess_reg_method_t)method, data, reg_size, r_size_reg, w_size_reg, &status); \
    prefix ## _ ## struct_name ## _unpack(data_struct, data);                                                         \
    if (rc || status)                                                                                                 \
    {                                                                                                                 \
        free(data);                                                                                                   \
        return (reg_access_status_t)rc;                                                                               \
    }                                                                                                                 \
    if (t_data)                                                                                                       \
    {                                                                                                                 \
        data_struct->data_p_name = t_data;                                                                            \
        memcpy(t_data, &data[t_offset], data_struct->data_size_name);                                                 \
    }                                                                                                                 \
    free(data);                                                                                                       \
    return ME_OK;

/* reg access with changing length of read\write in the register struct */
#define REG_ACCCESS_VAR(mf, method, reg_id, data_struct, struct_name, reg_size, r_reg_size, w_reg_size, prefix) \
    REG_ACCESS_GENERIC_VAR(mf, method, reg_id, data_struct, struct_name, reg_size, r_reg_size, w_reg_size,      \
                           prefix##_##struct_name##_pack, prefix##_##struct_name##_unpack,                      \
                           prefix##_##struct_name##_size, prefix##_##struct_name##_print, 0)

#define REG_ACCCESS_VAR_DYNAMIC_ARR(mf, method, reg_id, data_struct, struct_name, prefix, array_size)     \
    int data_size = prefix##_##struct_name##_size() + array_size;                                         \
    REG_ACCESS_GENERIC_VAR(mf, method, reg_id, data_struct, struct_name, data_size, data_size, data_size, \
                           prefix##_##struct_name##_pack, prefix##_##struct_name##_unpack,                \
                           prefix##_##struct_name##_size, prefix##_##struct_name##_print, 1)

// register access for static sized registers
#define REG_ACCCESS(mf, method, reg_id, data_struct, struct_name, prefix) \
    int data_size = prefix##_##struct_name##_size();                      \
    REG_ACCCESS_VAR(mf, method, reg_id, data_struct, struct_name, data_size, data_size, data_size, prefix)
