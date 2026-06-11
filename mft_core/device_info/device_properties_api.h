/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef DEVICE_PROPERTIES_API_H
#define DEVICE_PROPERTIES_API_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "device_properties_constants.h"
#include "device_hw_ids.h"

#ifdef __cplusplus
#include <string>

// C++ API - throws exceptions on error
std::string get_property_as_string(uint32_t device_id, const std::string& property_name);
uint32_t get_property_as_uint_cpp(uint32_t device_id, const std::string& property_name);
bool get_property_as_bool_cpp(uint32_t device_id, const std::string& property_name);

extern "C"
{
#endif

    // C API - returns sentinel values on error because there are no exceptions in C
    // Returns "" on error
    const char* get_property_as_cstring(uint32_t device_id, const char* property_name);

    // Returns 0 on error
    uint32_t get_property_as_uint(uint32_t device_id, const char* property_name);

    // Returns 0 on error
    int get_property_as_int(uint32_t device_id, const char* property_name);

    // Returns false on error
    bool get_property_as_bool(uint32_t device_id, const char* property_name);

    // -------------------------------------------------------------------------
    // Convenience type-check functions
    // -------------------------------------------------------------------------

    bool is_nic(uint32_t device_id);
    bool is_switch(uint32_t device_id);
    bool is_cable(uint32_t device_id);
    bool is_gearbox(uint32_t device_id);
    bool is_linkx(uint32_t device_id);
    bool is_retimer(uint32_t device_id);
    bool is_4th_gen_nic(uint32_t device_id);
    bool is_5th_gen_nic(uint32_t device_id);
    bool is_fs_dump_supported(uint32_t device_id);
    bool is_fs2(uint32_t device_id);
    bool is_fs3(uint32_t device_id);
    bool is_fs4(uint32_t device_id);
    bool is_fs5(uint32_t device_id);
    bool device_props_is_supported_device_id(uint32_t device_id);

    // -------------------------------------------------------------------------
    // Enumeration utilities
    // -------------------------------------------------------------------------

    eDeviceID get_device_id_from_str(const char* dev_name);
    void get_device_name_by_index(int i, char* dest, size_t dest_size);
    void get_device_name_by_id(int dev_id, char* dest, size_t dest_size);
    unsigned int get_num_of_devices();
    unsigned int get_num_of_tracer_supported_devices();
    // Caller must allocate at least get_num_of_devices() elements. Returns the number of IDs written.
    int get_all_device_ids(eDeviceID* device_ids);
    // Caller must allocate at least get_num_of_tracer_supported_devices() elements.
    void get_all_tracer_supported_ids(eDeviceID* device_ids);
    // Caller must allocate at least get_num_of_devices() elements. Returns the number of IDs written.
    int get_all_5th_gen_nics(eDeviceID* device_ids);

    // Print helpers (output to stdout)
    void print_all_supported_nics();
    void print_all_supported_switches();
    void print_all_supported_retimers();

#ifdef __cplusplus
}
#endif

#endif // DEVICE_PROPERTIES_API_H
