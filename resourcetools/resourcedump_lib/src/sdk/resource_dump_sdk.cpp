/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include "resource_dump_sdk.h"
#include "resource_dump_error_handling.h"
#include "resource_dump_types.h"
#include "dump_command.h"
#include "query_command.h"
#include "strip_control_segments_filter.h"

#include <common/compatibility.h>

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

constexpr uint16_t ERROR_MESSAGE_LEN{512};
char _g_resource_dump_last_error_message__[ERROR_MESSAGE_LEN] = {'\0'};

enum result_t
  get_resources_menu(device_attributes_t device_attrs, resource_menu_data_t* available_resources, endianess_t endianess)
{
    try
    {
        mft::resource_dump::QueryCommand query_command{device_attrs};

        query_command.execute();

        auto record_data_size = sizeof(mft::resource_dump::menu_record_data) * query_command.menu_records.size();
        available_resources->num_of_resources = query_command.menu_records.size();

        if (__BYTE_ORDER != __BIG_ENDIAN && endianess == endianess_t::RD_BIG_ENDIAN)
        {
            auto big_endian_record_data = query_command.get_big_endian_string();
            memcpy(available_resources->resources, big_endian_record_data.c_str(), record_data_size);
        }
        else
        {
            memcpy(available_resources->resources, &(*query_command.menu_records), record_data_size);
        }
    }
    catch (const mft::resource_dump::ResourceDumpException& rde)
    {
        strncpy(_g_resource_dump_last_error_message__, rde.what(), ERROR_MESSAGE_LEN - 1);
        return static_cast<result_t>(rde.reason);
    }
    catch (const std::exception& e)
    {
        strncpy(_g_resource_dump_last_error_message__,
                (string("Unknown General Error: ") + e.what()).c_str(),
                ERROR_MESSAGE_LEN - 1);
        return RD_ERROR;
    }
    catch (...)
    {
        strncpy(_g_resource_dump_last_error_message__, "- FATAL - Unexpected error occured.", ERROR_MESSAGE_LEN - 1);
        return RD_FATAL;
    }
    return RD_OK;
}

enum result_t dump_resource_to_file(device_attributes_t device_attrs,
                                    dump_request_t segment_params,
                                    uint32_t depth,
                                    const char* filename,
                                    endianess_t endianess)
{
    try
    {
        mft::resource_dump::DumpCommand dump_command{device_attrs, segment_params, depth, string(filename)};
        dump_command.execute();
        if (__BYTE_ORDER != __BIG_ENDIAN && endianess == endianess_t::RD_BIG_ENDIAN)
        {
            dump_command.reverse_fstream_endianess();
        }
    }
    catch (const mft::resource_dump::ResourceDumpException& rde)
    {
        strncpy(_g_resource_dump_last_error_message__, rde.what(), ERROR_MESSAGE_LEN - 1);
        return static_cast<result_t>(rde.reason);
    }
    catch (const std::exception& e)
    {
        strncpy(_g_resource_dump_last_error_message__,
                (string("Unknown General Error: ") + e.what()).c_str(),
                ERROR_MESSAGE_LEN - 1);
        return RD_ERROR;
    }
    catch (...)
    {
        strncpy(_g_resource_dump_last_error_message__, "- FATAL - Unexpected error occured.", ERROR_MESSAGE_LEN - 1);
        return RD_FATAL;
    }
    return RD_OK;
}

const char* get_resource_dump_error()
{
    return _g_resource_dump_last_error_message__;
}

enum result_t dump_resource_to_buffer(device_attributes_t device_attrs,
                                      dump_request_t segment_params,
                                      uint32_t depth,
                                      unsigned char* buffer,
                                      size_t buffer_size,
                                      endianess_t endianess)
{
    try
    {
        mft::resource_dump::DumpCommand dump_command{device_attrs, segment_params, depth};
        dump_command.execute();

        const size_t parsed_size = dump_command.get_dumped_size();

        if (parsed_size > buffer_size)
        {
            throw mft::resource_dump::ResourceDumpException(
              mft::resource_dump::ResourceDumpException::Reason::BUFFER_TOO_SMALL);
        }

        if (__BYTE_ORDER != __BIG_ENDIAN && endianess == endianess_t::RD_BIG_ENDIAN)
        {
            auto big_endian_data = dump_command.get_big_endian_string();
            memcpy(reinterpret_cast<char*>(buffer), big_endian_data.c_str(), parsed_size);
        }
        else
        {
            istream& parsed_stream = dump_command.get_native_stream();
            parsed_stream.read(reinterpret_cast<char*>(buffer), parsed_size);
        }
    }
    catch (const mft::resource_dump::ResourceDumpException& rde)
    {
        strncpy(_g_resource_dump_last_error_message__, rde.what(), ERROR_MESSAGE_LEN - 1);
        return static_cast<result_t>(rde.reason);
    }
    catch (const std::exception& e)
    {
        strncpy(_g_resource_dump_last_error_message__,
                (string("Unknown General Error: ") + e.what()).c_str(),
                ERROR_MESSAGE_LEN - 1);
        return RD_ERROR;
    }
    catch (...)
    {
        strncpy(_g_resource_dump_last_error_message__, "- FATAL - Unexpected error occured.", ERROR_MESSAGE_LEN - 1);
        return RD_FATAL;
    }
    return RD_OK;
}

enum result_t create_resource_dump(device_attributes_t device_attrs,
                                   dump_request_t segment_params,
                                   resource_dump_data_t* dump_data,
                                   uint32_t depth)
{
    try
    {
        auto dump_command = new mft::resource_dump::DumpCommand{device_attrs, segment_params, depth};
        dump_command->execute();

        istream& parsed_stream = dump_command->get_native_stream();
        const size_t parsed_size = dump_command->get_dumped_size();

        dump_data->dump_obj = static_cast<void*>(dump_command);
        dump_data->data = new unsigned char[parsed_size];

        if (__BYTE_ORDER != __BIG_ENDIAN && dump_data->endianess == endianess_t::RD_BIG_ENDIAN)
        {
            auto big_endian_data = dump_command->get_big_endian_string();
            memcpy(dump_data->data, big_endian_data.c_str(), parsed_size);
        }
        else
        {
            parsed_stream.read(reinterpret_cast<char*>(dump_data->data), parsed_size);
        }

        dump_data->size = parsed_size;
        return RD_OK;
    }
    catch (const mft::resource_dump::ResourceDumpException& rde)
    {
        strncpy(_g_resource_dump_last_error_message__, rde.what(), ERROR_MESSAGE_LEN - 1);
        return static_cast<result_t>(rde.reason);
    }
    catch (const std::exception& e)
    {
        strncpy(_g_resource_dump_last_error_message__,
                (string("Unknown General Error: ") + e.what()).c_str(),
                ERROR_MESSAGE_LEN - 1);
        return RD_ERROR;
    }
    catch (...)
    {
        strncpy(_g_resource_dump_last_error_message__, "- FATAL - Unexpected error occured.", ERROR_MESSAGE_LEN - 1);
        return RD_FATAL;
    }
    return RD_OK;
}

void destroy_resource_dump(resource_dump_data_t dump_data)
{
    if (dump_data.data)
    {
        delete[] dump_data.data;
    }
    if (dump_data.dump_obj)
    {
        auto dump_command = static_cast<mft::resource_dump::DumpCommand*>(dump_data.dump_obj);
        delete dump_command;
    }
}

enum result_t strip_control_segments(resource_dump_data_t* dump_data)
{
    try
    {
        auto dump_command = static_cast<mft::resource_dump::DumpCommand*>(dump_data->dump_obj);
        mft::resource_dump::filters::StripControlSegmentsFilter filter{*dump_command};
        auto filtered_view = filter.apply();

        if (__BYTE_ORDER != __BIG_ENDIAN && dump_data->endianess == endianess_t::RD_BIG_ENDIAN)
        {
            auto big_endian_data = filter.get_big_endian_string();
            memcpy(dump_data->data, big_endian_data.c_str(), big_endian_data.size() + 1);
        }
        else
        {
            filtered_view.filtered_stream.read(reinterpret_cast<char*>(dump_data->data), filtered_view.size);
        }

        dump_data->size = filtered_view.size;
    }
    catch (const mft::resource_dump::ResourceDumpException& rde)
    {
        strncpy(_g_resource_dump_last_error_message__, rde.what(), ERROR_MESSAGE_LEN - 1);
        return static_cast<result_t>(rde.reason);
    }
    catch (const std::exception& e)
    {
        strncpy(_g_resource_dump_last_error_message__,
                (string("Unknown General Error: ") + e.what()).c_str(),
                ERROR_MESSAGE_LEN - 1);
        return RD_ERROR;
    }
    catch (...)
    {
        strncpy(_g_resource_dump_last_error_message__, "- FATAL - Unexpected error occured.", ERROR_MESSAGE_LEN - 1);
        return RD_FATAL;
    }
    return RD_OK;
}
