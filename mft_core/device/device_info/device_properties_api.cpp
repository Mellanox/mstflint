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

#include "device_properties_api.h"
#include "device_properties_data.h"
#include "mft_core/mft_core_utils/mft_exceptions/DevicePropertyNotFoundException.h"
#include "mft_core/mft_core_utils/logger/Logger.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

// The properties_by_device_id map is defined in device_properties_data.h (included above)

// Helper function
static inline std::string device_id_to_hex_string(uint32_t device_id)
{
    char device_id_str[32];
    snprintf(device_id_str, sizeof(device_id_str), "0x%x", device_id);
    return std::string(device_id_str);
}

// ============================================================================
// C++ API - These functions throw exceptions on error
// ============================================================================

std::string get_property_as_string(uint32_t device_id, const std::string& property_name)
{
    if (property_name.empty())
    {
        std::string error_msg = "-E- property_name cannot be empty";
        LOG.Error(error_msg);
        throw mft_core::MftGeneralException(error_msg);
    }

    std::string device_id_str = device_id_to_hex_string(device_id);

    // lookup the device's property map in the properties_by_device_id map
    auto device_it = properties_by_device_id.find(device_id_str);
    if (device_it == properties_by_device_id.end())
    {
        std::string error_msg = "-E- Unsupported Device ID " + device_id_str;
        LOG.Error(error_msg);
        throw mft_core::MftGeneralException(error_msg);
    }

    // lookup the property in the device's property map
    auto property_it = device_it->second.find(property_name);
    if (property_it == device_it->second.end())
    {
        std::string error_msg = "-E- the following field is not available in device_info: \"" + property_name + "\"";
        LOG.Error(error_msg);
        throw mft_core::DevicePropertyNotFoundException(error_msg);
    }

    std::string result = property_it->second;
    LOG.Debug("device_id=" + device_id_str + ", " + property_name + "=" + result);

    return result;
}

uint32_t get_property_as_uint_cpp(uint32_t device_id, const std::string& property_name)
{
    if (property_name.empty())
    {
        std::string error_msg = "-E- property_name cannot be empty";
        LOG.Error(error_msg);
        throw mft_core::MftGeneralException(error_msg);
    }

    std::string device_id_str = device_id_to_hex_string(device_id);

    // Will throw if device is invalid or property not found
    std::string value = get_property_as_string(device_id, property_name);

    uint32_t result = 0;
    if (value.substr(0, 2) == "0x")
    {
        char* endptr;
        result = strtoul(value.c_str() + 2, &endptr, 16);
        if (*endptr != '\0')
        {
            std::string error_msg = "-E- Invalid numeric value for property \"" + property_name + "\": " + value;
            LOG.Error(error_msg);
            throw mft_core::MftGeneralException(error_msg);
        }
    }
    else
    {
        char* endptr;
        result = strtoul(value.c_str(), &endptr, 10);
        if (*endptr != '\0')
        {
            std::string error_msg = "-E- Invalid numeric value for property \"" + property_name + "\": " + value;
            LOG.Error(error_msg);
            throw mft_core::MftGeneralException(error_msg);
        }
    }

    std::ostringstream oss;
    oss << "device_id=" << device_id_str << ", " << property_name << "=" << std::dec << result << " (0x" << std::hex
        << result << ")";
    LOG.Debug(oss.str());

    return result;
}

bool get_property_as_bool_cpp(uint32_t device_id, const std::string& property_name)
{
    if (property_name.empty())
    {
        std::string error_msg = "-E- property_name cannot be empty";
        LOG.Error(error_msg);
        throw mft_core::MftGeneralException(error_msg);
    }

    std::string device_id_str = device_id_to_hex_string(device_id);

    // Will throw if device is invalid or property not found
    std::string value = get_property_as_string(device_id, property_name);

    // JSON boolean fields are emitted as "true"/"false", so only "true" is truthy
    // (matches get_property_as_bool in device_properties_api.py).
    bool result = (value == "true");

    LOG.Debug("device_id=" + device_id_str + ", " + property_name + "=" + (result ? "true" : "false"));

    return result;
}

// ============================================================================
// File-local helpers
// ============================================================================
static const std::vector<eDeviceID>& GetDeviceVector()
{
    static const std::vector<eDeviceID> DeviceVector = []()
    {
        std::vector<eDeviceID> v;
        v.reserve(properties_by_device_id.size());
        for (const auto& entry : properties_by_device_id)
        {
            uint32_t id = (uint32_t)strtoul(entry.first.c_str() + 2, nullptr, 16);
            v.push_back(static_cast<eDeviceID>(id));
        }
        std::sort(v.begin(), v.end());
        return v;
    }();
    return DeviceVector;
}

// ============================================================================
// C API - These functions catch exceptions and return sentinel values
// ============================================================================

extern "C"
{
    // C version returns const char* (pointer to data in static map, safe to use)
    // Returns "" on error since C can't throw exceptions
    const char* get_property_as_cstring(uint32_t device_id, const char* property_name)
    {
        try
        {
            if (!property_name)
            {
                LOG.Error("-E- property_name cannot be null");
                return "";
            }

            // Use C++ function for validation (throws on error with proper logging)
            // to ensure consistent error handling between C and C++ APIs
            get_property_as_string(device_id, property_name);

            // Get a stable pointer to the data in the static map
            // (can't use get_property_as_string result as it returns a copy)
            std::string device_id_str = device_id_to_hex_string(device_id);
            const auto& device_props = properties_by_device_id.at(device_id_str);
            return device_props.at(property_name).c_str();
        }
        catch (const std::exception& e)
        {
            LOG.Debug(std::string("get_property_as_cstring: ") + e.what());
            return "";
        }
    }

    // C version returns 0 on error since C can't throw exceptions
    uint32_t get_property_as_uint(uint32_t device_id, const char* property_name)
    {
        try
        {
            if (!property_name)
            {
                LOG.Error("-E- property_name cannot be null");
                return 0;
            }
            return get_property_as_uint_cpp(device_id, property_name);
        }
        catch (const std::exception& e)
        {
            LOG.Debug(std::string("get_property_as_uint: ") + e.what());
            return 0;
        }
    }

    // C version returns 0 on error since C can't throw exceptions
    int get_property_as_int(uint32_t device_id, const char* property_name)
    {
        try
        {
            if (!property_name)
            {
                LOG.Error("-E- property_name cannot be null");
                return 0;
            }
            return static_cast<int>(get_property_as_uint_cpp(device_id, property_name));
        }
        catch (const std::exception& e)
        {
            LOG.Debug(std::string("get_property_as_int: ") + e.what());
            return 0;
        }
    }

    // C version returns false on error since C can't throw exceptions
    bool get_property_as_bool(uint32_t device_id, const char* property_name)
    {
        try
        {
            if (!property_name)
            {
                LOG.Error("-E- property_name cannot be null");
                return false;
            }
            return get_property_as_bool_cpp(device_id, property_name);
        }
        catch (const std::exception& e)
        {
            LOG.Debug(std::string("get_property_as_bool: ") + e.what());
            return false;
        }
    }

    // -------------------------------------------------------------------------
    // Convenience type-check functions
    // -------------------------------------------------------------------------

    bool is_nic(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_DEVICE_TYPE), DEVICE_TYPE_NIC) == 0;
    }

    bool is_switch(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_DEVICE_TYPE), DEVICE_TYPE_SWITCH) == 0;
    }

    bool is_cable(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_DEVICE_TYPE), DEVICE_TYPE_CABLE) == 0;
    }

    bool is_linkx(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_DEVICE_TYPE), DEVICE_TYPE_LINKX) == 0;
    }

    bool is_retimer(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_DEVICE_TYPE), DEVICE_TYPE_RETIMER) == 0;
    }

    bool is_4th_gen_nic(uint32_t /* device_id */)
    {
        return false;
    }

    bool is_5th_gen_nic(uint32_t device_id)
    {
        return is_nic(device_id) && !is_4th_gen_nic(device_id);
    }

    bool is_fs_dump_supported(uint32_t device_id)
    {
        return device_id == (uint32_t)ConnectX4 || device_id == (uint32_t)ConnectX4LX ||
               device_id == (uint32_t)ConnectX5 || device_id == (uint32_t)ConnectX6 ||
               device_id == (uint32_t)ConnectX6DX || device_id == (uint32_t)ConnectX6LX ||
               device_id == (uint32_t)ConnectX7 || device_id == (uint32_t)BlueField ||
               device_id == (uint32_t)BlueField2 || device_id == (uint32_t)BlueField3;
    }

    bool is_fs2(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_IMAGE_LAYOUT_FORMAT), IMAGE_LAYOUT_FS2) == 0;
    }

    bool is_fs3(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_IMAGE_LAYOUT_FORMAT), IMAGE_LAYOUT_FS3) == 0;
    }

    bool is_fs4(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_IMAGE_LAYOUT_FORMAT), IMAGE_LAYOUT_FS4) == 0;
    }

    bool is_fs5(uint32_t device_id)
    {
        return strcmp(get_property_as_cstring(device_id, PROP_IMAGE_LAYOUT_FORMAT), IMAGE_LAYOUT_FS5) == 0;
    }

    // -------------------------------------------------------------------------
    // Enumeration utilities
    // -------------------------------------------------------------------------

    bool device_props_is_supported_device_id(uint32_t device_id)
    {
        std::string device_id_str = device_id_to_hex_string(device_id);
        return properties_by_device_id.find(device_id_str) != properties_by_device_id.end();
    }

    eDeviceID get_device_id_from_str(const char* dev_name)
    {
        if (!dev_name)
        {
            return DEVICE_HW_ID_UNKNOWN;
        }
        // "BlueField4" resolves to BlueField4_PCIID (0xa2df) via the loop below,
        // because 0x224's JSON entry is named "ConnectX9" and 0xa2df's is "BlueField4".
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        for (eDeviceID dev_id : devices)
        {
            if (strcmp(get_property_as_cstring((uint32_t)dev_id, PROP_DEVICE_NAME), dev_name) == 0)
            {
                return dev_id;
            }
        }
        return DEVICE_HW_ID_UNKNOWN;
    }

    void get_device_name_by_index(int i, char* dest, size_t dest_size)
    {
        if (!dest || dest_size == 0)
        {
            return;
        }
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        if (i < 0 || (size_t)i >= devices.size())
        {
            dest[0] = '\0';
            return;
        }
        snprintf(dest, dest_size, "%s", get_property_as_cstring((uint32_t)devices[i], PROP_DEVICE_NAME));
    }

    void get_device_name_by_id(int dev_id, char* dest, size_t dest_size)
    {
        if (!dest || dest_size == 0)
        {
            return;
        }
        snprintf(dest, dest_size, "%s", get_property_as_cstring((uint32_t)dev_id, PROP_DEVICE_NAME));
    }

    unsigned int get_num_of_devices()
    {
        return (unsigned int)GetDeviceVector().size();
    }

    unsigned int get_num_of_tracer_supported_devices()
    {
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        unsigned int count = 0;
        for (eDeviceID dev : devices)
        {
            if (is_nic((uint32_t)dev) || is_switch((uint32_t)dev) || dev == ArcusE || dev == Arcus2)
            {
                count++;
            }
        }
        return count;
    }

    int get_all_device_ids(eDeviceID* device_ids)
    {
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        int size = (int)devices.size();
        memcpy(device_ids, devices.data(), sizeof(eDeviceID) * size);
        return size;
    }

    void get_all_tracer_supported_ids(eDeviceID* device_ids)
    {
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        std::vector<eDeviceID> supported;
        for (eDeviceID dev : devices)
        {
            if (is_nic((uint32_t)dev) || is_switch((uint32_t)dev) || dev == ArcusE || dev == Arcus2)
            {
                supported.push_back(dev);
            }
        }
        memcpy(device_ids, supported.data(), sizeof(eDeviceID) * supported.size());
    }

    int get_all_5th_gen_nics(eDeviceID* device_ids)
    {
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        std::vector<eDeviceID> result;
        for (eDeviceID dev : devices)
        {
            if (is_5th_gen_nic((uint32_t)dev))
            {
                result.push_back(dev);
            }
        }
        memcpy(device_ids, result.data(), sizeof(eDeviceID) * result.size());
        return (int)result.size();
    }

    void print_all_supported_nics()
    {
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        for (eDeviceID dev_id : devices)
        {
            if (is_nic((uint32_t)dev_id))
            {
                printf("%s\n", get_property_as_cstring((uint32_t)dev_id, PROP_DEVICE_NAME));
            }
        }
    }

    void print_all_supported_switches()
    {
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        for (eDeviceID dev_id : devices)
        {
            // TODO - when FN100 will be ready: ommit it from the if.
            // TODO - when NVLink8_Switch will be ready: ommit it from the if.
            if (is_switch((uint32_t)dev_id) && dev_id != FN100 && dev_id != NVLink8_Switch)
            {
                printf("%s\n", get_property_as_cstring((uint32_t)dev_id, PROP_DEVICE_NAME));
            }
        }
    }

    void print_all_supported_retimers()
    {
        const std::vector<eDeviceID>& devices = GetDeviceVector();
        for (eDeviceID dev_id : devices)
        {
            if (is_retimer((uint32_t)dev_id) && dev_id != Libra)
            {
                printf("%s\n", get_property_as_cstring((uint32_t)dev_id, PROP_DEVICE_NAME));
            }
        }
    }

    uint32_t resolve_functional_device_id(uint32_t hw_dev_id, int rev_id, uint32_t pci_device_id)
    {
        // Priority 1: PCI device ID match (e.g. BlueField4, which shares hw_dev_id
        // 0x224 with ConnectX9 and is disambiguated by its PCI device id).
        if (pci_device_id != 0)
        {
            for (unsigned int i = 0; i < device_identity_index_size; ++i)
            {
                if (device_identity_index[i].pci_device_id == pci_device_id)
                {
                    return pci_device_id;
                }
            }
        }

        // Priority 2: Exact revision match (e.g. GR150A01P via rev_id==1)
        if (rev_id >= 0)
        {
            for (unsigned int i = 0; i < device_identity_index_size; ++i)
            {
                const struct DeviceIdentityEntry& e = device_identity_index[i];
                if (e.hw_dev_id == hw_dev_id && e.hw_rev_id == rev_id)
                {
                    return DEVICE_IDENTITY(e.hw_dev_id, e.hw_rev_id);
                }
            }
        }

        // Priority 3: Base hw_dev_id
        return hw_dev_id;
    }

} // extern "C"
