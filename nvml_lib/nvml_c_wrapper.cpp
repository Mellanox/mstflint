/*
 * Copyright(c) 2025 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.You may choose to be licensed under the terms of the GNU
 * General Public License(GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 * Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 * -Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 * -Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and / or other materials
 * provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <iostream>
#include <string.h>

#include "nvml_c_wrapper.h"
#include "nvml_device.h"
#include "nvml_exception.h"


unsigned int get_nvml_device_index(const char* device_name)
{
    char  *endptr;
    char   device_name_prefix[] = "/dev/nvidia";
    char * device_index_location = strstr((char*)device_name, device_name_prefix);

    if (device_index_location == nullptr) {
        throw NvmlException("Invalid device name: %s\n", device_name);
    }

    unsigned int device_index = strtoul(device_index_location + (sizeof(device_name_prefix) - 1), &endptr, 10);

    if ((device_index == 0) && (endptr == device_name)) {
        throw NvmlException("Invalid device name: %s\n", device_name);
    }
    return device_index;
}

int init_nvml_device(const char* device_name, void** device_pointer)
{
    try
    {
        unsigned int device_index = get_nvml_device_index(device_name);
        *device_pointer = (void*) new NvmlDevice(device_index);
        return 0;
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }
}

int destroy_nvml_device(void* device_pointer)
{
    try
    {
        if (device_pointer) {
            delete static_cast < NvmlDevice* > (device_pointer);
            device_pointer = nullptr;
        }
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }

    return 0;
}

int nvml_reg_access(unsigned char    * reg_data,
                    const unsigned int reg_size,
                    const unsigned int reg_id,
                    int              * reg_status,
                    bool               is_write,
                    void             * device_pointer)
{
    try
    {
        return static_cast < NvmlDevice * > (device_pointer)->SendPRMRegister(reg_data,
                                                                              reg_size,
                                                                              reg_id,
                                                                              *reg_status,
                                                                              is_write);
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }
}

u_int16_t nvml_get_pci_id(void* device_pointer)
{
    try
    {
        return static_cast < NvmlDevice * > (device_pointer)->GetPciID();
    }
    catch(const NvmlException& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }
}
