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

#ifndef RESOURCE_DUMP_SDK_H
#define RESOURCE_DUMP_SDK_H

#include "resource_dump_segments.h"
#include "resource_dump_types.h"

#include <stdint.h>
#include <stdlib.h>

enum result_t
{
    RD_OK = 0,
    RD_ERROR = 1,
    RD_FATAL
};

#ifdef __cplusplus
typedef mft::resource_dump::menu_record_data menu_record_data_t;
typedef mft::resource_dump::device_attributes device_attributes_t;
typedef mft::resource_dump::dump_request_t dump_request_t;
typedef mft::resource_dump::endianess_t_ endianess_t;
#endif

typedef struct resource_menu_data
{
    /* number of available resources. */
    uint16_t num_of_resources;

    /* see struct definition.
     * TODO in phaseII, cast to more readable struct with parameter availability enums. */
    menu_record_data_t* resources;
} resource_menu_data_t;

typedef struct resource_dump_data
{
    void* dump_obj;        // opaque object, uniquely represents a dump command to the fw and it's reply
    unsigned char* data;   // dump data, returned by resource-dump, or altered by filters
    uint32_t size;         // valid size of the data
    endianess_t endianess; // endianness of the data, if non-zero value provided by the user, data byte order can be
                           // reversed to match selection
} resource_dump_data_t;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

    /*
     * Function: get_resources_menu
     * ----------------------------
     * Provides a list of all the available resources for a given device.
     *
     * device_attrs:        represents the input device.
     *                      see device_attributes struct definition.
     * available_resources: the output list of resources with their parameters.
     *                      see resource_menu_data struct definition.
     * endianess:           required endianness of the data, data byte order can be reversed to match selection.
     *
     * returns: OK if returned a valid result.
     *          Error reason from resource_dump_error_handling.h on error.
     */
    enum result_t get_resources_menu(device_attributes_t device_attrs,
                                     resource_menu_data_t* available_resources,
                                     endianess_t endianess);

    /*
     * Function: dump_resource_to_file
     * ----------------------------
     * Dumps a requested resource into a binary file.
     *
     * device_attrs:    represents the input device.
     *                  see device_attributes struct definition.
     * dump_request_t:  the requested segment to dump, optionally with parameters.
     * depth:           depth of reference segments.
     * filename:        path to the output file.
     * endianess:       required endianness of the data, data byte order can be reversed to match selection.
     *
     * returns: OK if returned a valid result.
     *          Error reason from resource_dump_error_handling.h on error.
     */
    enum result_t dump_resource_to_file(device_attributes_t device_attrs,
                                        dump_request_t segment_params,
                                        uint32_t depth,
                                        const char* filename,
                                        endianess_t endianess);

    /*
     * Function: dump_resource_to_buffer
     * ----------------------------
     * Dumps a requested resource into a binary file.
     *
     * device_attrs:    represents the input device.
     *                  see device_attributes struct definition.
     * dump_request_t:  the requested segment to dump, optionally with parameters.
     * depth:           depth of reference segments.
     * buffer:          buffer for the dump. assuming that the stated size is allocated
     * buffer_size:     allocated size of the provided buffer
     * endianess:       required endianness of the data, data byte order can be reversed to match selection.
     *
     * returns: OK if returned a valid result.
     *          Error reason from resource_dump_error_handling.h on error.
     */
    enum result_t dump_resource_to_buffer(device_attributes_t device_attrs,
                                          dump_request_t segment_params,
                                          uint32_t depth,
                                          unsigned char* buffer,
                                          size_t buffer_size,
                                          endianess_t endianess);

    /*
     * Function: create_resource_dump
     * ----------------------------
     * Requests the requested resource from FW, allocates the required buffer and returns it.
     *
     * device_attrs:    represents the input device.
     *                  see device_attributes struct definition.
     * dump_request_t:  the requested segment to dump, optionally with parameters.
     * depth:           depth of reference segments.
     * dump_data:       pointer to the filled dump result data
     *
     * returns: OK if returned a valid result.
     *          Error reason from resource_dump_error_handling.h on error.
     */
    enum result_t create_resource_dump(device_attributes_t device_attrs,
                                       dump_request_t segment_params,
                                       resource_dump_data_t* dump_data,
                                       uint32_t depth);

    /*
     * Function: destroy_resource_dump create_resource_dump
     * ----------------------------
     * Frees the memory allocated by
     *
     * dump_data:    a struct filled by create_resource_dump for destruction
     */
    void destroy_resource_dump(resource_dump_data_t dump_data);

    /*
     * Function: strip_control_segments
     * ----------------------------
     * Stripts a resource-dump buffer from control segments
     *
     * dump_data:       pointer to the filled dump result data, changes by the filter application
     *
     * returns:         a buffer to a sequence of resource-only segments
     */
    enum result_t strip_control_segments(resource_dump_data_t* dump_obj);

    // /*
    //  * Function: filter_segments
    //  * ----------------------------
    //  * filters resource-dump buffer according to a list of required segments-ids
    //  *
    //  * dump_buffer: a buffer contains a valid sequence of resource-dump segments
    //  *
    //  * returns:     a buffer to the filtered result
    //  */
    // unsigned char* filter_segments(unsigned char* dump_buffer, const uint16_t* segment_ids, uint16_t num_ids);

    /*
     * Function: get_resource_dump_error
     * ----------------------------
     * returns:  an error message of the last error occured.
     */
    const char* get_resource_dump_error();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // RESOURCE_DUMP_SDK_H
