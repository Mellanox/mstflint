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
 *
 *  Alaa Al-barari Abarari@asaltech.com
 *  Version: $Id: crdump.c 20-Feb-2013 $
 *
 */

#define _GNU_SOURCE
#include <crdump.h>
#include <dev_mgt/tools_dev_types.h>
#include <common/bit_slice.h>
#include <ctype.h>
#include <compatibility.h>
#include <stdio.h>
#include <tools_layouts/reg_access_switch_layouts.h>
#include <reg_access/reg_access.h>
#include <mft_utils/mft_sig_handler.h>
#include <stdbool.h>

#define CRD_CHECK_NULL(var)                        \
    if (var == NULL)                               \
        do                                         \
        {                                          \
            CRD_DEBUG("Sent %s is null!\n", #var); \
            return CRD_INVALID_PARM;               \
    } while (0)

#if defined(__WIN__)
#define strcasecmp _stricmp
#define CRD_MTCR_DLL_NAME "libmtcr-1.dll"
#endif

//#define CRD_DEBUG_BUILD
#ifdef CRD_DEBUG_BUILD
#define CRD_DEBUG(fmt, ...) printf("%s:%s:%d: " fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define CRD_DEBUG(fmt, ...)
#endif

#define CRD_EMPTY "EMPTY"
#define CRD_UNKOWN "UNKNOWN"

#define CRD_MAXLINESIZE 1024
#define CRD_MAXFLDS 3     /* maximum possible number of fields */
#define CRD_MAXFLDSIZE 32 /* longest possible field + 1 = 31 byte field */
#define CRD_CSV_PATH_SIZE 1024
#define CRD_MAX_REG_ACCESS_BLOCK 256

// Scratchpad 2
#define CRD_SP2_TLV_FIRST_ADDRESS 0x18         /* This first tlv address is valid only for HCA */
#define CRD_SP2_TLV_FIRST_ADDRESS_CX8 0x1A00018 /* This first tlv address is valid only for CX8 and up */
#define CRD_SP2_TLV_SIGNATURE_VALUE 0x54306F6C /* signature value is T0ol */

typedef struct crd_sp2_tlv
{
    u_int32_t signature;
    u_int32_t size;
    u_int32_t writable;
    u_int32_t fw;
    u_int32_t version;
    u_int32_t address;
} crd_sp2_tlv_t;

typedef struct crd_parsed_csv
{
    u_int32_t addr;
    u_int32_t len;
    char enable_addr[100];

} crd_parsed_csv_t;

struct crd_ctxt
{
    mfile* mf;
    u_int32_t dev_type;
    u_int32_t number_of_dwords;
    int is_full;
    int cause_addr;
    int cause_off;
    char csv_path[CRD_CSV_PATH_SIZE];
    u_int32_t block_count;
    crd_parsed_csv_t* blocks;
};

static char crd_error[CRD_CSV_PATH_SIZE + 50];

/*
   Store the csv file path at csv_file_path.
 */
static int crd_get_csv_path(IN dm_dev_id_t dev_type,
                            OUT char* csv_file_path,
                            IN const char* db_path,
                            const char* csv_path_from_user);

/*
   count number of dwords, and store all needed data from csv file at parsed_csv
 */
static int crd_count_double_word(IN mfile* mf,
                                 IN char* csv_file_path,
                                 IN dm_dev_id_t dev_type,
                                 OUT u_int32_t* number_of_dwords,
                                 OUT crd_parsed_csv_t blocks[],
                                 IN int is_full,
                                 IN u_int8_t read_single_dword,
                                 IN u_int8_t with_sp2);

/*
   Fill addresses at dword_arr
 */
static int crd_fill_address(IN crd_ctxt_t* context, OUT crd_dword_t* dword_arr);

/*
   Read a line from csv file
 */
static int crd_read_line(IN FILE* fd, OUT char* tmp);

/*
   Tokenize line for address, len, and enable_adder
 */

static void crd_parse(IN char* record, IN char* delim, OUT char arr[][CRD_MAXFLDSIZE], OUT int* field_count);

static int crd_update_csv_path(IN OUT char* csv_file_path, IN const char* db_path);

static int crd_count_blocks(IN char* csv_file_path, OUT u_int32_t* block_count, u_int8_t read_single_dword);

static int crd_count_tlv_blocks_and_dwords(IN mfile* mf,
                                           IN u_int32_t tlv_start_address,
                                           OUT u_int32_t* block_count,
                                           OUT u_int32_t* number_of_dwords);

static int crd_get_tlv_from_address(IN mfile* mf, IN u_int32_t address, OUT crd_sp2_tlv_t* crd_sp2_tlv);

static int crd_is_tlv_signature_valid(IN u_int32_t signature);

static int crd_is_tlv_address_valid(IN u_int32_t address);

static int crd_set_tlv_blocks(IN mfile* mf,
                              IN dm_dev_id_t dev_type,
                              OUT crd_parsed_csv_t blocks[],
                              IN u_int32_t sp2_start_block);

static uint32_t crd_get_sp2_start_block(IN dm_dev_id_t dev_type);

#if !defined(__WIN__) && !defined(MST_UL)
static char* crd_trim(char* s);

static char* crd_rtrim(char* s);

static char* crd_ltrim(char* s);
#endif

#if defined(__WIN__)
static int crd_replace(INOUT char* st, IN char* orig, IN char* repl);

static int crd_get_exec_name_from_path(IN char* str, OUT char* exec_name);
#endif

int crd_init(OUT crd_ctxt_t** context,
             IN mfile* mf,
             IN int is_full,
             IN int cause_addr,
             IN int cause_off,
             IN const char* db_path,
             const char* csv_path_from_user)
{
    dm_dev_id_t dev_type = DeviceUnknown;
    u_int32_t with_sp2 = 0;
    u_int32_t dev_id = 0;
    u_int32_t chip_rev = 0;
    u_int32_t number_of_dwords = 0;
    u_int32_t block_count = 0;
    u_int32_t sp2_number_of_dwords = 0;
    u_int32_t sp2_block_count = 0;
    u_int8_t read_single_dword = 0;
    char csv_file_path[CRD_CSV_PATH_SIZE] = {0x0};

    int rc = CRD_OK;

    CRD_CHECK_NULL(mf);
    CRD_CHECK_NULL(context);

    if (cause_addr >= 0 && cause_off < 0)
    {
        CRD_DEBUG("cause_off is negative : %d ", cause_off);
        return CRD_INVALID_PARM;
    }

    if (cause_addr >= 0 && cause_off >= 0)
    {
        read_single_dword = 1;
    }
    CRD_DEBUG("getting device id\n");
    if (dm_get_device_id(mf, &dev_type, &dev_id, &chip_rev))
    {
        CRD_DEBUG("Failed to identify device.");
        return CRD_UNKOWN_DEVICE;
    }

    CRD_DEBUG("Device type : 0x%x, device id : 0x%x, chip rev : 0x%x\n", dev_type, dev_id, chip_rev);
    if ((rc = crd_get_csv_path(dev_type, csv_file_path, db_path, csv_path_from_user)) != CRD_OK)
    {
        return rc;
    }

    CRD_DEBUG("allocating struct\n");
    *context = (crd_ctxt_t*)malloc(sizeof(crd_ctxt_t));
    if (*context == NULL)
    {
        CRD_DEBUG("Failed to allocate memmory for context \n");
        return CRD_MEM_ALLOCATION_ERR;
    }

    if (dm_dev_is_hca(dev_type))
    {
        with_sp2 = 1;
        uint32_t tlv_start_address = crd_get_sp2_start_block(dev_type);
        rc = crd_count_tlv_blocks_and_dwords(mf, tlv_start_address, &sp2_block_count, &sp2_number_of_dwords);
        if (rc)
        {
            return rc;
        }
    }

    rc = crd_count_blocks(csv_file_path, &block_count, read_single_dword);
    if (rc)
    {
        free(*context);
        return rc;
    }

    CRD_DEBUG("Block count : %d\n", block_count);
    (*context)->blocks = (crd_parsed_csv_t*)malloc(sizeof(crd_parsed_csv_t) * (block_count + sp2_block_count));
    if ((*context)->blocks == NULL)
    {
        CRD_DEBUG("Failed to allocate memmory for csv blocks\n");
        free(*context);
        return CRD_MEM_ALLOCATION_ERR;
    }

    rc = crd_count_double_word(mf, csv_file_path, dev_type, &number_of_dwords, (*context)->blocks, is_full,
                               read_single_dword, with_sp2);
    if (rc)
    {
        goto Cleanup;
    }

    mset_addr_space(mf, AS_ND_CRSPACE);

    CRD_DEBUG("Number of found dwords are : %d \n", number_of_dwords);
    (*context)->mf = mf;
    (*context)->dev_type = dev_type;
    (*context)->number_of_dwords = number_of_dwords + sp2_number_of_dwords;
    (*context)->is_full = is_full;
    (*context)->block_count = block_count + sp2_block_count;
    (*context)->cause_addr = cause_addr;
    (*context)->cause_off = cause_off;
    strcpy((*context)->csv_path, csv_file_path);
    return rc;

Cleanup:
    crd_free(*context);
    return rc;
}

int crd_get_addr_list(IN crd_ctxt_t* context, OUT crd_dword_t* dword_arr)
{
    int rc;

    CRD_CHECK_NULL(context);
    CRD_CHECK_NULL(dword_arr);

    rc = crd_fill_address(context, dword_arr);
    if (rc)
    {
        return rc;
    }

    return CRD_OK;
}

int crd_dump_data(IN crd_ctxt_t* context, OUT crd_dword_t* dword_arr, IN crd_callback_t func)
{
    u_int32_t i = 0;
    u_int32_t j = 0;
    u_int32_t rc;
    u_int32_t addr;
    u_int32_t cause_reg = 0;

    int total = 0;
    char* data;
    crd_dword_t tmp_dword;

    CRD_CHECK_NULL(context);

    if (dword_arr == NULL && func == NULL)
    {
        CRD_DEBUG("Nothing to do\n");
        return CRD_INVALID_PARM;
    }

    for (i = 0; i < context->block_count; i++)
    {
        if (!context->is_full && strcmp(context->blocks[i].enable_addr, CRD_EMPTY))
        {
            continue;
        }

        data = (char*)malloc(context->blocks[i].len * sizeof(u_int32_t));
        if (data == NULL)
        {
            return CRD_MEM_ALLOCATION_ERR;
        }
        memset(data, 0, context->blocks[i].len * sizeof(u_int32_t));

        rc = mread4_block(context->mf, context->blocks[i].addr, (u_int32_t*)data,
                          context->blocks[i].len * sizeof(u_int32_t));
        if (context->blocks[i].len * sizeof(u_int32_t) != rc)
        {
            sprintf(crd_error, "Cr read (0x%08x) failed: %s(%d)", context->blocks[i].addr, strerror(errno),
                    (u_int32_t)errno);
            free(data);
            return CRD_CR_READ_ERR;
        }

        for (j = 0; j < context->blocks[i].len; j++)
        {
            if (mft_signal_is_fired())
            {
                free(data);
                return CRD_SIGNAL_INTERRUPTED;
            }
            if ((u_int32_t)total >= context->number_of_dwords)
            { // dummy check tadah!
                CRD_DEBUG("value exceeded, something wrong in calculation!");
                free(data);
                return CRD_EXCEED_VALUE;
            }
            addr = context->blocks[i].addr + (j * sizeof(u_int32_t));

            if (context->cause_addr >= 0)
            { // if we want to check cause bit - read it and verify it hasn't been raised
                if (mread4(context->mf, context->cause_addr, &cause_reg) != sizeof(u_int32_t))
                {
                    CRD_DEBUG("Cr read (0x%08x) failed: %s(%d)\n", context->cause_addr, strerror(errno),
                              (u_int32_t)errno);
                    sprintf(crd_error, "Cr read (0x%08x) failed: %s(%d)", context->cause_addr, strerror(errno),
                            (u_int32_t)errno);
                    free(data);
                    return CRD_CR_READ_ERR;
                }
                cause_reg = EXTRACT(cause_reg, context->cause_off, 1);
                if (cause_reg)
                {
                    CRD_DEBUG("Cause bit set by read from address 0x%x\n", addr);
                    sprintf(crd_error, "Cause bit set by read from address 0x%x", addr);
                    free(data);
                    return CRD_CAUSE_BIT;
                }
            }

            if (dword_arr != NULL)
            {
                dword_arr[total].addr = addr;
                dword_arr[total].data = ((u_int32_t*)data)[j];
            }
            if (func != NULL)
            {
                tmp_dword.addr = addr;
                tmp_dword.data = ((u_int32_t*)data)[j];
                func(&tmp_dword);
            }
            total += 1;
        }
        free(data);
    }
    return CRD_OK;
}

int crd_get_dword_num(IN crd_ctxt_t* context, OUT u_int32_t* arr_size)
{
    CRD_CHECK_NULL(context);
    *arr_size = context->number_of_dwords;
    return CRD_OK;
}

static bool ends_with(char* str, char* suffix)
{
    int str_len = strlen(str);
    int suffix_len = strlen(suffix);
    int i = 0;

    bool ends_with = false;
    if (suffix_len <= str_len)
    {
        for (i = 0; i < suffix_len; i++)
        {
            if (str[i + str_len - suffix_len] != suffix[i])
            {
                ends_with = false;
                break;
            }
            ends_with = true;
        }
    }
    return ends_with;
}

static bool is_valid_csv(char* csv_path_from_user)
{
    if (!ends_with((char*)csv_path_from_user, ".csv"))
    {
        return false; // not a .csv file
    }

    FILE* file = fopen(csv_path_from_user, "r");
    if (!file)
    {
        return false; // file does not exist
    }

    // check the format is valid
    char line[256] = {0};
    // char* line = calloc(256, sizeof(char));
    // if (line == NULL) {
    //     goto cleanup;
    // }
    int buf_len = sizeof(line);
    size_t len = 0;
    size_t i = 0;
    bool ret = true; // assume format is valid
    int count = 0;
    int digit_counter = 0;
    while (fgets(line, buf_len, file) != NULL)
    {
        if (line[0] == '#')
        {
            continue; // skipping lines that are a comment
        }
        len = strlen(line);
        digit_counter = 0;
        if (len > 1)
        { // skip blank lines
            count = 0;
            for (i = 0; i < len; i++)
            {
                if (line[i] == ',')
                {
                    count++;
                }

                if (isxdigit(line[i]) != 0 && count < 1)
                {
                    digit_counter++;
                }

            }

            if ((count < 1) || (count > 2) || (digit_counter < 2) || (digit_counter > 9))
            { // support a,b or a,b, format
                ret = false;
                goto cleanup;
            }
        }
    }
cleanup:
    fclose(file);
    return ret;
}

static int crd_get_csv_path(IN dm_dev_id_t dev_type,
                            OUT char* csv_file_path,
                            IN const char* db_path,
                            const char* csv_path_from_user)
{
    const int dev_name_len = 100;
    char dev_name[100] = {0};
    int rc;

    strncpy(dev_name, dm_dev_type2str(dev_type), dev_name_len - 1);

    if (!strcmp(dev_name, "Unknown Device"))
    {
        return CRD_UNKOWN_DEVICE;
    }

    // if user specified DB path via cmdline, use it instead of the DB in the default location.
    // check the user gave a valid path.
    if (strlen(csv_path_from_user) > 0)
    {
        if (is_valid_csv((char*)csv_path_from_user))
        {
            strcpy(csv_file_path, csv_path_from_user);
            return CRD_OK;
        }
        else
        {
            sprintf(crd_error, "Invalid csv file: %s\n", csv_path_from_user);
            return CRD_CSV_BAD_FORMAT;
        }
    }
    else // user did not specify DB path
    {
        rc = crd_update_csv_path(csv_file_path, db_path);
        if (rc != CRD_OK)
        {
            return rc;
        }
        strcat(csv_file_path, dev_name);
        strcat(csv_file_path, ".csv");
        return CRD_OK;
    }
    return 0;
}

static void crd_parse(IN char* record, IN char* delim, OUT char arr[][CRD_MAXFLDSIZE], OUT int* field_count)
{
    char* p = strtok(record, delim);
    int field = 0;
    strcpy(arr[0], "\0");
    strcpy(arr[1], "\0");
    strcpy(arr[2], "\0");
    while (p)
    {
        strcpy(arr[field], p);
        field++;
        p = strtok(NULL, delim);
    }
    *field_count = field;
}

static int crd_is_tlv_signature_valid(IN u_int32_t signature)
{
    int is_signature_valid = CRD_TLV_SIGNATURE_INVALID;
    if (signature == CRD_SP2_TLV_SIGNATURE_VALUE)
    {
        is_signature_valid = CRD_OK;
    }

    return is_signature_valid;
}

static int crd_is_tlv_address_valid(IN u_int32_t address)
{
    int is_address_valid = CRD_TLV_ADDRESS_INVALID;
    if ((int)address != -1)
    {
        is_address_valid = CRD_OK;
    }

    return is_address_valid;
}

static int crd_count_tlv_blocks_and_dwords(IN mfile* mf,
                                           IN u_int32_t tlv_start_address,
                                           OUT u_int32_t* block_count,
                                           OUT u_int32_t* number_of_dwords)
{
    int rc = 0;
    crd_sp2_tlv_t current_tlv;
    u_int32_t tlv_signature = 0;
    u_int32_t tlv_address = 0;
    *block_count = 0;
    *number_of_dwords = 0;
    rc = crd_get_tlv_from_address(mf, tlv_start_address, &current_tlv);
    if (rc)
    {
        return rc;
    }
    tlv_signature = current_tlv.signature;
    tlv_address = current_tlv.address;

    while (crd_is_tlv_signature_valid(tlv_signature) == CRD_OK && crd_is_tlv_address_valid(tlv_address) == CRD_OK)
    {
        (*block_count)++;
        (*number_of_dwords) += current_tlv.size;

        rc = crd_get_tlv_from_address(mf, current_tlv.address, &current_tlv);
        if (rc)
        {
            return rc;
        }
        tlv_signature = current_tlv.signature;
        tlv_address = current_tlv.address;
    }
    return CRD_OK;
}

static int
  crd_set_tlv_blocks(IN mfile* mf, IN dm_dev_id_t dev_type, OUT crd_parsed_csv_t blocks[], IN u_int32_t sp2_start_block)
{
    int rc = 0;
    crd_sp2_tlv_t current_tlv;
    u_int32_t tlv_signature = 0;
    u_int32_t tlv_address = 0;
    u_int32_t block_number = sp2_start_block;
    uint32_t tlv_start_address = crd_get_sp2_start_block(dev_type);

    rc = crd_get_tlv_from_address(mf, tlv_start_address, &current_tlv);
    if (rc)
    {
        return rc;
    }
    tlv_signature = current_tlv.signature;
    tlv_address = current_tlv.address;

    while (crd_is_tlv_signature_valid(tlv_signature) == CRD_OK && crd_is_tlv_address_valid(tlv_address) == CRD_OK)
    {
        blocks[block_number].addr = current_tlv.address;
        blocks[block_number].len = current_tlv.size;
        strcpy(blocks[block_number].enable_addr, CRD_EMPTY);

        block_number++;
        rc = crd_get_tlv_from_address(mf, current_tlv.address, &current_tlv);
        if (rc)
        {
            return rc;
        }
        tlv_signature = current_tlv.signature;
        tlv_address = current_tlv.address;
    }
    return CRD_OK;
}

static int crd_get_tlv_from_address(IN mfile* mf, IN u_int32_t address, OUT crd_sp2_tlv_t* crd_sp2_tlv)
{
    u_int32_t data = 0;

    // read signature
    if (mread4(mf, address, &data) != sizeof(u_int32_t))
    {
        CRD_DEBUG("Cr read (0x%08x) failed: %s(%d)\n", address, strerror(errno), (u_int32_t)errno);
        sprintf(crd_error, "Cr read (0x%08x) failed: %s(%d)", address, strerror(errno), (u_int32_t)errno);
        return CRD_CR_READ_ERR;
    }
    else
    {
        crd_sp2_tlv->signature = data;
    }

    // read size, writable, fw, version
    if (mread4(mf, address + 4, &data) != sizeof(u_int32_t))
    {
        CRD_DEBUG("Cr read (0x%08x) failed: %s(%d)\n", address + 4, strerror(errno), (u_int32_t)errno);
        sprintf(crd_error, "Cr read (0x%08x) failed: %s(%d)", address + 4, strerror(errno), (u_int32_t)errno);
        return CRD_CR_READ_ERR;
    }
    else
    {
        crd_sp2_tlv->size = EXTRACT(data, 0, 20);
        crd_sp2_tlv->writable = EXTRACT(data, 20, 1);
        crd_sp2_tlv->fw = EXTRACT(data, 21, 1);
        crd_sp2_tlv->version = EXTRACT(data, 28, 4);
    }

    // read address
    if (mread4(mf, address + 8, &data) != sizeof(u_int32_t))
    {
        CRD_DEBUG("Cr read (0x%08x) failed: %s(%d)\n", address + 8, strerror(errno), (u_int32_t)errno);
        sprintf(crd_error, "Cr read (0x%08x) failed: %s(%d)", address + 8, strerror(errno), (u_int32_t)errno);
        return CRD_CR_READ_ERR;
    }
    else
    {
        crd_sp2_tlv->address = data;
    }
    return CRD_OK;
}

static uint32_t crd_get_sp2_start_block(IN dm_dev_id_t dev_type)
{
    uint32_t sp2_start_block = 0;

    if (dm_dev_is_hca(dev_type))
    {
        if (dm_is_cx8(dev_type) || dm_is_cx9(dev_type))
        {
            sp2_start_block = CRD_SP2_TLV_FIRST_ADDRESS_CX8;
        }
        else
        {
            sp2_start_block = CRD_SP2_TLV_FIRST_ADDRESS;
        }
    }
    return sp2_start_block;
}
static int crd_count_blocks(IN char* csv_file_path, OUT u_int32_t* block_count, u_int8_t read_single_dword)
{
    char tmp[1024] = {0x0};
    char arr[CRD_MAXFLDS][CRD_MAXFLDSIZE];
    int field_count = 0;
    *block_count = 0;

    CRD_DEBUG("CSV file path : %s\n", csv_file_path);
    FILE* fd = fopen(csv_file_path, "r");
    if (fd == NULL)
    {
        CRD_DEBUG("Failed to open csv file : '%s'\n", csv_file_path);
        sprintf(crd_error, "Failed to open csv file : '%s'", csv_file_path);
        return CRD_OPEN_FILE_ERROR;
    }
    while (!feof(fd))
    {
        if (mft_signal_is_fired())
        {
            fclose(fd);
            return CRD_SIGNAL_INTERRUPTED;
        }
        int read_line_result = crd_read_line(fd, tmp);
        if (read_line_result == CRD_SKIP)
        {
            continue;
        }

        // if the given address has invalid char in it
        if (read_line_result == CRD_CSV_BAD_FORMAT)
        {
            CRD_DEBUG("CSV File has bad format - invalid char in address");
            sprintf(crd_error, "CSV File has bad format");
            fclose(fd);
            return CRD_CSV_BAD_FORMAT;
        }
        crd_parse(tmp, ",", arr, &field_count); /* whack record into fields */
        if (field_count < 2)
        {
            CRD_DEBUG("CSV File has bad format, line : %s\n", tmp);
            sprintf(crd_error, "CSV File has bad format, line : %s", tmp);
            fclose(fd);
            return CRD_CSV_BAD_FORMAT;
        }
        if (read_single_dword)
        {
            *block_count += atoi(arr[1]);
        }
        else
        {
            *block_count += 1;
        }
    }
    fclose(fd);
    return CRD_OK;
}

static int crd_count_double_word(IN mfile* mf,
                                 IN char* csv_file_path,
                                 IN dm_dev_id_t dev_type,
                                 OUT u_int32_t* number_of_dwords,
                                 OUT crd_parsed_csv_t blocks[],
                                 IN int is_full,
                                 IN u_int8_t read_single_dword,
                                 IN u_int8_t with_sp2)
{
    int rc = 0;
    int field_count = 0;
    int block_count = 0;
    u_int32_t addr = 0;
    u_int32_t len = 0;
    u_int32_t i = 0;
    char enable_addr[100] = {0};
    char tmp[1024] = {0x0};
    char arr[CRD_MAXFLDS][CRD_MAXFLDSIZE];

    *number_of_dwords = 0;

    CRD_DEBUG("CSV file path : %s\n", csv_file_path);
    FILE* fd = fopen(csv_file_path, "r");
    if (fd == NULL)
    {
        CRD_DEBUG("Failed to open csv file : '%s'\n", csv_file_path);
        sprintf(crd_error, "Failed to open csv file : '%s'", csv_file_path);
        return CRD_OPEN_FILE_ERROR;
    }

    while (!feof(fd))
    {
        if (mft_signal_is_fired())
        {
            fclose(fd);
            return CRD_SIGNAL_INTERRUPTED;
        }
        int read_line_result = crd_read_line(fd, tmp);
        if (read_line_result == CRD_SKIP)
        {
            continue;
        }

        // if the given address has invalid char in it
        if (read_line_result == CRD_CSV_BAD_FORMAT)
        {
            CRD_DEBUG("CSV File has bad format - invalid char in address");
            sprintf(crd_error, "CSV File has bad format");
            fclose(fd);
            return CRD_CSV_BAD_FORMAT;
        }

        crd_parse(tmp, ",", arr, &field_count); /* whack record into fields */
        if (field_count < 2)
        {
            CRD_DEBUG("CSV File has bad format, line : %s\n", tmp);
            sprintf(crd_error, "CSV File has bad format, line : %s", tmp);
            fclose(fd);
            return CRD_CSV_BAD_FORMAT;
        }
        addr = (u_int32_t)strtol(arr[0], NULL, 0);
        len = atoi(arr[1]);
        if (!read_single_dword)
        {
            blocks[block_count].addr = addr;
            blocks[block_count].len = len;
            if (field_count > 2)
            {
                strcpy(blocks[block_count].enable_addr, arr[2]);
                if (is_full || (!is_full && !strcmp(blocks[block_count].enable_addr, CRD_EMPTY)))
                {
                    *number_of_dwords += len;
                }
            }
            else
            {
                strcpy(blocks[block_count].enable_addr, CRD_EMPTY);
                *number_of_dwords += len;
            }
            block_count += 1;
        }
        else
        {
            if (field_count > 2)
            {
                strcpy(enable_addr, arr[2]);
            }
            else
            {
                strcpy(enable_addr, CRD_EMPTY);
            }
            if (is_full || (!is_full && !strcmp(enable_addr, CRD_EMPTY)))
            {
                *number_of_dwords += len;
            }
            for (i = 0; i < len; i++)
            {
                blocks[block_count].addr = addr;
                blocks[block_count].len = 1;
                strcpy(blocks[block_count].enable_addr, enable_addr);
                block_count += 1;
                addr += 4;
            }
        }
    }
    fclose(fd);

    if (with_sp2)
    {
        rc = crd_set_tlv_blocks(mf, dev_type, blocks, block_count);
        if (rc)
        {
            return rc;
        }
    }

    return CRD_OK;
}

static int crd_fill_address(IN crd_ctxt_t* context, OUT crd_dword_t* dword_arr)
{
    u_int32_t i = 0;
    u_int32_t j = 0;
    int total = 0;

    for (i = 0; i < context->block_count; i++)
    {
        for (j = 0; j < context->blocks[i].len; j++)
        {
            // CRD_UNKOWN, CRD_EMPTY
            if (!context->is_full && strcmp(context->blocks[i].enable_addr, CRD_EMPTY))
            {
                break;
            }
            if ((u_int32_t)total >= context->number_of_dwords)
            {
                CRD_DEBUG("value exceeded, something wrong in calculation!");
                return CRD_EXCEED_VALUE;
            }
            dword_arr[total].addr = context->blocks[i].addr + (j * 4);
            total += 1;
        }
    }
    return CRD_OK;
}

static int crd_read_line(IN FILE* fd, OUT char* tmp)
{
    int i = 0;
    int j = 0;
    int has_comma = 0;
    for (i = 0; i < CRD_MAXLINESIZE;)
    { // This loop to read line by line no matter the length of the line.
        if (!feof(fd))
        {
            int c = fgetc(fd);
            if (c == '#')
            {
                if (!fgets(tmp, 300, fd))
                { // Avoid warning
                }
                tmp[0] = 0;
                continue;
            }
            else if (c == '\r')
            {
                break;
            }
            else if (c == '\n')
            {
                break;
            }
            else if (feof(fd))
            {
                break;
            }
            else if (c == ' ')
            {
                continue;
            }
            else if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) &&
                     !(i == 1 && c == 'x') && !(has_comma < 2 && c == ','))
            {
                printf("Error - the character %c is not valid for address!\n", c);
                return CRD_CSV_BAD_FORMAT;
            }
            else
            {
                if (c == ',')
                {
                    has_comma++;
                }
                j++;
                tmp[i] = c;
                i++;
            }
        }
        else
        {
            return CRD_SKIP;
        }
    }
    if (!j)
    {
        return CRD_SKIP;
    }
    tmp[i] = 0;
    return CRD_OK;
}

#if defined(__WIN__)

static int crd_replace(INOUT char* st, IN char* orig, IN char* repl)
{
    char buffer[CRD_CSV_PATH_SIZE] = {0x0};
    char* ch;

    if (!(ch = strstr(st, orig)))
    {
        return CRD_OK;
    }
    strncpy(buffer, st, ch - st);
    buffer[ch - st] = 0;
    sprintf(buffer + (ch - st), "%s%s", repl, ch + strlen(orig));
    strcpy(st, buffer);

    return CRD_OK;
}

static int crd_get_exec_name_from_path(IN char* str, OUT char* exec_name)
{
    char* tmp_str = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    if (tmp_str == NULL)
    {
        CRD_DEBUG("Failed to allocate memmory\n");
        return CRD_MEM_ALLOCATION_ERR;
    }
    char* pch;
    strcpy(tmp_str, str);
    pch = strtok(tmp_str, "\\");
    while (pch != NULL)
    {
        strcpy(exec_name, pch);
        pch = strtok(NULL, "\\");
    }
    free(tmp_str);
    return CRD_OK;
}
#endif

#if !defined(__WIN__) && !defined(MST_UL)
static char* crd_ltrim(char* s)
{
    while (isspace(*s))
    {
        s++;
    }
    return s;
}

static char* crd_rtrim(char* s)
{
    char* back;
    int len = strlen(s);

    if (len == 0)
    {
        return (s);
    }
    back = s + len;
    while (isspace(*--back))
    {
        ;
    }
    *(back + 1) = '\0';
    return s;
}

static char* crd_trim(char* s)
{
    return crd_rtrim(crd_ltrim(s));
}
#endif

static int crd_update_csv_path(IN OUT char* csv_file_path, IN const char* db_path)
{
    int found = 0;
#ifdef __WIN__
    char exec_name[CRD_CSV_PATH_SIZE];
    (void)db_path;
    GetModuleFileName(GetModuleHandle(CRD_MTCR_DLL_NAME), csv_file_path, CRD_CSV_PATH_SIZE);
    crd_get_exec_name_from_path(csv_file_path, exec_name);
    crd_replace(csv_file_path, exec_name, "mstdump_dbs\\");
    found = 1;

#elif defined MST_UL
    (void)db_path;
    strcat(csv_file_path, DATA_PATH "/");
    found = 1;

#else
    char conf_path[256] = ROOT_PATH;
    char data_path[CRD_CSV_PATH_SIZE] = {0x0};
    char prefix[CRD_CSV_PATH_SIZE] = {0x0};
    char* tmp_value = NULL;
    char line[CRD_MAXLINESIZE] = {0};
    FILE* fd;

    if (db_path != NULL && *db_path != '\0')
    {
        strncpy(csv_file_path, db_path, CRD_CSV_PATH_SIZE - 1);
        return CRD_OK;
    }
    strcat(conf_path, "etc/mft/mft.conf");
    fd = fopen(conf_path, "r");
    if (fd == NULL)
    {
        CRD_DEBUG("Failed to open conf file : %s\n", conf_path);
        sprintf(crd_error, "Failed to open conf file : %s", conf_path);
        return CRD_OPEN_FILE_ERROR;
    }

    while ((fgets(line, CRD_MAXLINESIZE, fd)))
    {
        if (strstr(line, "mstdump_dbs") != NULL)
        {
            tmp_value = strtok(line, "=");
            if (tmp_value != NULL)
            {
                tmp_value = strtok(NULL, "=");
                crd_trim(tmp_value);
                strncpy(data_path, tmp_value, CRD_CSV_PATH_SIZE - 1);
            }
        }
        else if (strstr(line, "mft_prefix_location") != NULL)
        {
            tmp_value = strtok(line, "=");
            if (tmp_value != NULL)
            {
                tmp_value = strtok(NULL, "=");
                crd_trim(tmp_value);
                strncpy(prefix, tmp_value, CRD_CSV_PATH_SIZE - 1);
            }
        }
    }
    if (strlen(prefix) && strlen(data_path))
    {
        strcpy(csv_file_path, prefix);
        strcat(csv_file_path, data_path);
        strcat(csv_file_path, "/");
        found = 1;
    }

    fclose(fd);
#endif
    if (!found)
    {
        return CRD_CONF_BAD_FORMAT;
    }
    return CRD_OK;
}

void crd_free(IN crd_ctxt_t* context)
{
    free(context->blocks);
    free(context);
}

const char* crd_err_str(int rc)
{
    switch (rc)
    {
        case CRD_OK:
            return "Ok";

        case CRD_MEM_ALLOCATION_ERR:
            return "Memory allocation error";

        case CRD_CR_READ_ERR:
            return crd_error;

        case CRD_INVALID_PARM:
            return "Invalid parameter";

        case CRD_UNKOWN_DEVICE:
            return "Unknown/Unsupported device";

        case CRD_CSV_BAD_FORMAT:
            return crd_error;

        case CRD_CONF_BAD_FORMAT:
            return "Conf file has no valid mstdumb_db path.";

        case CRD_OPEN_FILE_ERROR:
            return crd_error;

        case CRD_SKIP:
            return "Skip";

        case CRD_NOT_SUPPORTED:
            return "Not supported";

        case CRD_EXCEED_VALUE:
            return "Value exceed";

        case CRD_CAUSE_BIT:
            return crd_error;

        case CRD_SIGNAL_INTERRUPTED:
            return "Interrupted";

        default:
            return "Unknown error";
    }
}
