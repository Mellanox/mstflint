/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef LTSSM_TRACE_SDK_H
#define LTSSM_TRACE_SDK_H

#include <stdint.h>
#include <stdlib.h>

enum ltssm_trace_result_t
{
    LTSSM_TRACE_OK = 0,
    LTSSM_TRACE_BAD_PARAM = 1,
    LTSSM_TRACE_ERROR = 2
};

/* One LTSSM leaf field of the requested link. "name" is the field path below
 * the link node, built from the node names ltssm_trace_get_device_info reports,
 * e.g. "<ring_node>[17].state", and is owned by the library until
 * ltssm_trace_free_fields is called. The location the value came from is
 * reported too, so that a consumer can rebuild a raw dword out of the fields
 * sharing an address - which the FW-event number overlaid on the ring line
 * requires, as no ADB field describes it. */
typedef struct ltssm_trace_field
{
    const char* name;
    uint32_t value;
    uint32_t address;
    uint32_t start_bit;
    uint32_t size;
} ltssm_trace_field_t;

/* The device a dump was taken from, together with the node names that device's
 * reduced ADB spells the LTSSM hierarchy with. The names differ per device
 * because each reduced ADB inherits the naming of the family ADB behind it, so
 * a consumer addresses fields through these rather than through literals of its
 * own. Every string is owned by the library and stays valid until the handle is
 * closed. */
typedef struct ltssm_trace_device_info
{
    uint32_t hw_device_id;
    const char* device_name;
    const char* pcore_node;
    const char* link_node;
    const char* link_status_node;
    const char* state_node;
    const char* ring_node;
    const char* logger_ctrl_node;
} ltssm_trace_device_info_t;

typedef void* ltssm_trace_handle_t;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    /*
     * Function: ltssm_trace_open
     * ----------------------------
     * Opens a dump, resolves the device it was taken from and loads the LTSSM
     * layout of that device.
     *
     * dump_file:   path to an mstdump or a raw dump text file.
     * device_name: the device the dump was taken from, as dm_dev_type2str
     *              spells it, e.g. "ConnectX8". NULL or empty reads the device id
     *              out of the dump instead, which a dump whose address range
     *              holds no device id cannot answer.
     * handle:      receives the handle. It is allocated even when this call
     *              fails, so that ltssm_trace_get_error can be read from it,
     *              and must be released with ltssm_trace_close in either case.
     *              NULL when the parameters are invalid or the allocation
     *              itself failed, so closing what this call returned is always
     *              safe.
     *
     * returns: LTSSM_TRACE_OK on success, otherwise the failure reason.
     */
    enum ltssm_trace_result_t
      ltssm_trace_open(const char* dump_file, const char* device_name, ltssm_trace_handle_t* handle);

    /*
     * Function: ltssm_trace_get_device_info
     * ----------------------------
     * The device the dump was taken from and its LTSSM node names, both as
     * resolved by ltssm_trace_open.
     *
     * info: receives the identity and the node names. Its strings are owned by
     *       the library and stay valid until ltssm_trace_close.
     *
     * returns: LTSSM_TRACE_OK on success, otherwise the failure reason.
     */
    enum ltssm_trace_result_t ltssm_trace_get_device_info(ltssm_trace_handle_t handle, ltssm_trace_device_info_t* info);

    /*
     * Function: ltssm_trace_read_link
     * ----------------------------
     * Reads every LTSSM field of one link out of the dump.
     *
     * pcore:         pcore index of the link.
     * link:          link index within the pcore.
     * fields:        receives an array allocated by the library, to be released
     *                with ltssm_trace_free_fields.
     * num_of_fields: receives the number of entries in that array.
     *
     * returns: LTSSM_TRACE_OK on success, otherwise the failure reason.
     */
    enum ltssm_trace_result_t ltssm_trace_read_link(ltssm_trace_handle_t handle,
                                                    uint32_t pcore,
                                                    uint32_t link,
                                                    ltssm_trace_field_t** fields,
                                                    uint32_t* num_of_fields);

    /*
     * Function: ltssm_trace_free_fields
     * ----------------------------
     * Releases an array returned by ltssm_trace_read_link.
     */
    void ltssm_trace_free_fields(ltssm_trace_field_t* fields, uint32_t num_of_fields);

    /*
     * Function: ltssm_trace_close
     * ----------------------------
     * Releases a handle returned by ltssm_trace_open.
     */
    void ltssm_trace_close(ltssm_trace_handle_t handle);

    /*
     * Function: ltssm_trace_get_error
     * ----------------------------
     * returns: the message of the last failure on this handle, owned by the
     *          library, or an empty string when there was none.
     */
    const char* ltssm_trace_get_error(ltssm_trace_handle_t handle);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LTSSM_TRACE_SDK_H
