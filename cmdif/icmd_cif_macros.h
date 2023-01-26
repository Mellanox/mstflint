/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef _ICMD_MACROS /* guard */
#define _ICMD_MACROS

int convert_rc(int rc);

/*
 * SEND_ICMD_FLOW macro is designed for the most common icmd flow
 * basically every command that simply packs a struct sends icmd and unpacks it should use
 * this to save code.
 * TODO: Adrianc- if needed separate struct_name to prefix+name in case we need to separate between different
 * 5th gen icmd structures i.e connectib/switchib/connectx4 (use ## to paste them together in the macro)
 */
#define SEND_ICMD_FLOW_GENERIC(mf, op, struct_name, cmd_struct, should_pack, skip_write, pack_func, unpack_func) \
    int _rc;                                                                                                     \
    int       _cmd_size = struct_name ## _size();                                                                \
    u_int8_t* _data = (u_int8_t*)malloc(sizeof(u_int8_t) * _cmd_size);                                           \
    if (!_data)                                                                                                  \
    {                                                                                                            \
        return GCIF_STATUS_NO_MEM;                                                                               \
    }                                                                                                            \
    memset(_data, 0, sizeof(u_int8_t) * _cmd_size);                                                              \
    if (should_pack)                                                                                             \
    {                                                                                                            \
        pack_func(cmd_struct, _data);                                                                            \
    }                                                                                                            \
    _rc = icmd_send_command(mf, op, _data, _cmd_size, skip_write);                                               \
    if (_rc)                                                                                                     \
    {                                                                                                            \
        free(_data);                                                                                             \
        return convert_rc(_rc);                                                                                  \
    }                                                                                                            \
    unpack_func(cmd_struct, _data);                                                                              \
    free(_data);                                                                                                 \
    return GCIF_STATUS_SUCCESS

#define SEND_ICMD_FLOW(mf, op, struct_name, cmd_struct, should_pack, skip_write)                           \
    SEND_ICMD_FLOW_GENERIC(mf, op, struct_name, cmd_struct, should_pack, skip_write, struct_name ## _pack, \
                           struct_name ## _unpack)

#define SEND_UNION_ICMD_FLOW(mf, op, struct_name, cmd_struct, should_pack, skip_write) \
    int _rc;                                                                           \
    int       _cmd_size = struct_name ## _size();                                      \
    u_int8_t* _data = (u_int8_t*)malloc(sizeof(u_int8_t) * _cmd_size);                 \
    if (!_data)                                                                        \
    {                                                                                  \
        return GCIF_STATUS_NO_MEM;                                                     \
    }                                                                                  \
    memset(_data, 0, sizeof(u_int8_t) * _cmd_size);                                    \
    if (should_pack)                                                                   \
    {                                                                                  \
        struct_name ## _in_pack(&(cmd_struct->in), _data);                             \
    }                                                                                  \
    _rc = icmd_send_command(mf, op, _data, _cmd_size, skip_write);                     \
    if (_rc)                                                                           \
    {                                                                                  \
        free(_data);                                                                   \
        return convert_rc(_rc);                                                        \
    }                                                                                  \
    struct_name ## _out_unpack(&(cmd_struct->out), _data);                             \
    free(_data);                                                                       \
    return GCIF_STATUS_SUCCESS

#define SEND_IN_OUT_ICMD_FLOW(mf, op, base_struct_name, cmd_struct_in, cmd_struct_out, should_pack, skip_write) \
    int _rc;                                                                                                    \
    int       _cmd_in_size = base_struct_name ## _in_size();                                                    \
    int       _cmd_out_size = base_struct_name ## _out_size();                                                  \
    int       _cmd_size = _cmd_in_size + _cmd_out_size;                                                         \
    u_int8_t* _data = (u_int8_t*)malloc(sizeof(u_int8_t) * _cmd_size);                                          \
    if (!_data)                                                                                                 \
    {                                                                                                           \
        return GCIF_STATUS_NO_MEM;                                                                              \
    }                                                                                                           \
    memset(_data, 0, sizeof(u_int8_t) * _cmd_size);                                                             \
    if (should_pack)                                                                                            \
    {                                                                                                           \
        base_struct_name ## _in_pack(cmd_struct_in, _data);                                                     \
    }                                                                                                           \
    _rc = icmd_send_command(mf, op, _data, _cmd_size, skip_write);                                              \
    if (_rc)                                                                                                    \
    {                                                                                                           \
        free(_data);                                                                                            \
        return convert_rc(_rc);                                                                                 \
    }                                                                                                           \
    base_struct_name ## _out_unpack(cmd_struct_out, _data + sizeof(u_int8_t) * _cmd_in_size);                   \
    free(_data);                                                                                                \
    return GCIF_STATUS_SUCCESS

#define SEND_GEARBOX_FLOW(mf,                               \
                          method,                           \
                          request_struct_name,              \
                          request_cmd_struct,               \
                          response_struct_name,             \
                          response_cmd_struct,              \
                          should_pack,                      \
                          skip_write)                       \
    SEND_GEARBOX_FLOW_GENERIC(mf,                           \
                              method,                       \
                              request_struct_name,          \
                              request_cmd_struct,           \
                              response_struct_name,         \
                              response_cmd_struct,          \
                              should_pack,                  \
                              skip_write,                   \
                              request_struct_name ## _pack, \
                              response_struct_name ## _unpack)


#define SEND_GEARBOX_FLOW_GENERIC(mf,                                                                                                        \
                                  method,                                                                                                    \
                                  request_struct_name,                                                                                       \
                                  request_cmd_struct,                                                                                        \
                                  response_struct_name,                                                                                      \
                                  response_cmd_struct,                                                                                       \
                                  should_pack,                                                                                               \
                                  skip_write,                                                                                                \
                                  pack_func,                                                                                                 \
                                  unpack_func)                                                                                               \
    int _rc;                                                                                                                                 \
    int       _cmd_request_size = request_struct_name ## _size();                                                                            \
    int       _cmd_response_size = response_struct_name ## _size();                                                                          \
    u_int8_t *_request_data = (u_int8_t*)malloc(sizeof(u_int8_t) * _cmd_request_size);                                                       \
    u_int8_t *_response_data = (u_int8_t*)malloc(sizeof(u_int8_t) * _cmd_response_size);                                                     \
    if (!_request_data || !_response_data) {                                                                                                 \
        /* coverity: In case only 1 malloc successed we need to free it before exit, try free both since free has null check inside anyway*/ \
        free(_request_data);                                                                                                                 \
        free(_response_data);                                                                                                                \
        return GCIF_STATUS_NO_MEM;                                                                                                           \
    }                                                                                                                                        \
    memset(_request_data, 0, sizeof(u_int8_t) * _cmd_request_size);                                                                          \
    memset(_response_data, 0, sizeof(u_int8_t) * _cmd_response_size);                                                                        \
    if (should_pack) {                                                                                                                       \
        pack_func(request_cmd_struct, _request_data);                                                                                        \
    }                                                                                                                                        \
    if (mf->gb_info.gb_conn_type == GEARBPX_OVER_SWITCH) {                                                                                   \
        _rc = create_mddt_wrapper_for_cmd_payload(mf,                                                                                        \
                                                  method,                                                                                    \
                                                  _request_data,                                                                             \
                                                  _response_data,                                                                            \
                                                  _cmd_request_size,                                                                         \
                                                  _cmd_response_size);                                                                       \
    }                                                                                                                                        \
    else {                                                                                                                                   \
        _rc = 0;                                                                                                                             \
        /*_rc = icmd_send_gbox_command_com(mf, _request_data, _cmd_request_size, _response_data, _cmd_response_size, skip_write); */         \
    }                                                                                                                                        \
    if (_rc) {                                                                                                                               \
        free(_request_data);                                                                                                                 \
        free(_response_data);                                                                                                                \
        return convert_rc(_rc);                                                                                                              \
    }                                                                                                                                        \
    unpack_func(response_cmd_struct, _response_data);                                                                                        \
    free(_request_data);                                                                                                                     \
    free(_response_data);                                                                                                                    \
    return GCIF_STATUS_SUCCESS


#endif /* ifndef _ICMD_MACROS */
