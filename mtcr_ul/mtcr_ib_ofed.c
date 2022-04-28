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
 */

/********************************************************
**
*   ibvsmad.c
*
*   the ibvsmad library.
*   this library provides vendor specific mad capabilities.
*
*   mread64, mwrite64 - IS3 I2C bus access MAD - ExtPortAccess -> I2C compliant port #1
*   mread4 , mwrite4  - IS3 CR-Space access MAD - ConfigSpaceAccess
*
*
*   author: yoniy@mellanox.co.il , Apr. 16th 2007
*/



#if HAVE_CONFIG_H
#  include <config.h>
#endif
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <signal.h>

#ifdef MST_UL
#include <errno.h>
#include "mtcr_int_defs.h"
#endif

#include "mtcr_ib.h"

#ifndef __WIN__
#include "mtcr_mf.h"
#include "mtcr_com_defs.h"
#endif

#include <infiniband/mad.h>

#ifdef __WIN__
    #include <windows.h>
    #include "com_def.h"

    #define BAD_RET_VAL 1
    #define LIB_IBMAD  "libibmad"

    #define MY_GetPointerAddress(ivm, func_name, f_type) do { \
        ivm->func_name = (f_type)GetProcAddress(ivm->dl_handle, #func_name); \
        if (ivm->func_name == NULL) { \
            IBERROR(("Failed to find %s function on ibal.dll file.\n", #func_name)); \
            errno = ENOSYS; \
            return -1; \
        } \
} while (0)

    #define MY_GetProcAddress(ivm, func_name)  MY_GetPointerAddress(ivm, func_name, f_##func_name)
    #define MY_GetProcAddressIgnoreFail(ivm, func_name) \
    ivm->func_name = (f_##func_name)GetProcAddress(ivm->dl_handle, #func_name)
    #define MY_GetVarAddress(ivm, var_name)    MY_GetPointerAddress(ivm, var_name, void*)

    #define DLL_HANDLE HINSTANCE
    #define OP_NOT_SUPPORTED EINVAL
    #define IBMAD_CALL_CONV __stdcall


#else
    #include <getopt.h>
    #include <unistd.h>
    #include <dlfcn.h>
    #include <asm/byteorder.h>

    #define DLL_HANDLE void*
    #define BAD_RET_VAL ~0llu
    #define MY_DLSYM(mf, func_name) do { \
        const char *dl_error; \
        mf->func_name = dlsym(mf->dl_handle, #func_name); \
        if ((dl_error = dlerror()) != NULL)  { \
            IBERROR(("%s", dl_error)); \
            return -1; \
        } \
} while (0)

    #define MY_DLSYM_IGNORE_FAIL(mf, func_name) \
    mf->func_name = dlsym(mf->dl_handle, #func_name)

    #define OP_NOT_SUPPORTED EOPNOTSUPP
    #define IBMAD_CALL_CONV


#endif


#define __BUILD_VERSION_TAG__ 1.1
//#include "ibvsmad.h"

#undef DEBUG
// TODO: Ask Mohammad why was the iberror changed ?

// #define DEBUG(fmt, args...)  if (verbose) iberror(0, __FUNCTION__, fmt, ## args)
// #define IBERROR(fmt, args...)   iberror(1, __FUNCTION__, fmt, ## args)

#define IBERROR(args) do {               printf("-E- ibvsmad : "); \
                                         printf args; \
                                         printf("\n"); \
                                         errno = EINVAL; \
} while (0)
#define DEBUG(args) do {   if (verbose) { \
                               printf("-D- ibvsmad : "); \
                               printf args; \
                               printf("\n"); \
                               errno = EINVAL; \
                           } \
} while (0)

// BIT Slicing macros
#define ONES32(size)                    ((size) ? (0xffffffff >> (32 - (size))) : 0)
#define MASK32(offset, size)             (ONES32(size) << (offset))

#define EXTRACT_C(source, offset, size)   ((((unsigned)(source)) >> (offset)) & ONES32(size))
#define EXTRACT(src, start, len)          (((len) == 32) ? (src) : EXTRACT_C(src, start, len))

#define MERGE_C(rsrc1, rsrc2, start, len)  ((((rsrc2) << (start)) & (MASK32((start), (len)))) | ((rsrc1) & (~MASK32((start), (len)))))
#define MERGE(rsrc1, rsrc2, start, len)    (((len) == 32) ? (rsrc2) : MERGE_C(rsrc1, rsrc2, start, len))

#define SWAPL(l) bswap_32(l)


#define IB_VENDOR_SPECIFIC_CLASS_0xA    0x0A
#define IB_VENDOR_SPECIFIC_CLASS_0x9    0x09

#define NUMBER_OF_MGMT_ELEMENTS         4

#define IB_VS_ATTR_SW_RESET             0x12
#define IB_VS_ATTR_EXT_PORT_INFO        0x13
#define IB_VS_ATTR_CR_ACCESS            0x50
#define IB_VS_ATTR_GENERAL_INFO         0x17
#define IB_VS_ATTR_ACCESS_REGISTER_GMP  0x51

#define IB_VS_ATTRMOD_CR            0x00008000
#define IB_VS_ATTR_EPI_ATTRMOD_I2C1 0x02

#define IB_VS_CR_NUM_OF_RECORDS     1
#define IB_VS_CR_ONE_RECORD_SIZE    4

#define I2C_CHUNK_SIZE  64
#define I2C_DEVICE_ID   0x56
#define I2C_MEMORY_ADDR 0

#define KEY_GUID_SIZE  32

#define UNSUPP_DEVS_NUM   15
#define DEVID_ADDRESS     0xf0014

#define CLASS_VS_SIZE_BYTES 224
#define CLASS_VS_DATA_OFFSET 0x20

// ConfigSpaceAccess Mode 0 supports address of up to 24 bits.
#define MODE_0_MAX_ADDRESS_RANGE 0x7FFFFF
#define MODE_2_MAX_RECORDS_NUM   18
#define MODE_2_MAX_DATA_SIZE     (MODE_2_MAX_RECORDS_NUM * 4)

// Convert BYTES - DWORDS with MEMCPY BE
#define BYTES_TO_DWORD_BE(dw_dest, byte_src) do {   u_int32_t tmp; \
                                                    memcpy(&tmp, byte_src, 4); \
                                                    *(dw_dest) = __be32_to_cpu(tmp); \
} while (0)

#define DWORD_TO_BYTES_BE(bytes_dest, dw_src) do { u_int32_t tmp; \
                                                   tmp = __cpu_to_be32(*(dw_src)); \
                                                   memcpy(bytes_dest, &tmp, 4); \
} while (0)

#define CHECK_NULL(pointer) if (pointer == NULL) {return -1;}

typedef struct ibmad_port*IBMAD_CALL_CONV (*f_mad_rpc_open_port)(char *dev_name, int dev_port,
                                                                 int *mgmt_classes,
                                                                 int num_classes);
typedef void IBMAD_CALL_CONV (*f_mad_rpc_close_port)(struct ibmad_port *srcport);
typedef int IBMAD_CALL_CONV (*f_ib_resolve_portid_str_via)(ib_portid_t *portid, char *addr_str,
                                                           int dest, ib_portid_t *sm_id, const struct ibmad_port *srcport);
typedef uint8_t*IBMAD_CALL_CONV (*f_ib_vendor_call_via)(void *data, ib_portid_t *portid, ib_vendor_call_t *call,
                                                        const struct ibmad_port *srcport);
typedef uint8_t*IBMAD_CALL_CONV (*f_smp_query_via)(void *buf, ib_portid_t *id, unsigned attrid, unsigned mod,
                                                   unsigned timeout, const struct ibmad_port *srcport);
typedef uint8_t*IBMAD_CALL_CONV (*f_smp_query_status_via)(void *buf, ib_portid_t *id, unsigned attrid, unsigned mod,
                                                          unsigned timeout, int *rstatus, const struct ibmad_port *srcport);
typedef uint8_t*IBMAD_CALL_CONV (*f_smp_set_via)(void *buf, ib_portid_t *id, unsigned attrid, unsigned mod,
                                                 unsigned timeout, const struct ibmad_port *srcport );
typedef uint8_t*IBMAD_CALL_CONV (*f_smp_set_status_via)(void *buf, ib_portid_t *id, unsigned attrid, unsigned mod,
                                                        unsigned timeout, int *rstatus, const struct ibmad_port *srcport );
typedef void IBMAD_CALL_CONV (*f_smp_mkey_set)(struct ibmad_port *srcport, uint64_t mkey);

typedef void IBMAD_CALL_CONV (*f_mad_rpc_set_retries)(struct ibmad_port *port, int retries);
typedef void IBMAD_CALL_CONV (*f_mad_rpc_set_timeout)(struct ibmad_port *port, int timeout);
typedef uint32_t IBMAD_CALL_CONV (*f_mad_get_field)(void *buf, int base_offs, enum MAD_FIELDS field);

typedef char*IBMAD_CALL_CONV (*f_portid2str)(ib_portid_t *portid);

typedef void* IBMAD_CALL_CONV (*f_mad_rpc_rmpp) (const struct ibmad_port *srcport, ib_rpc_t * rpc,
                                                 ib_portid_t * dport, ib_rmpp_hdr_t * rmpp,
                                                 void *data);

typedef int IBMAD_CALL_CONV (*f_mad_send_via) (ib_rpc_t * rpc, ib_portid_t * dport,
                                               ib_rmpp_hdr_t * rmpp, void *data,
                                               struct ibmad_port *srcport);

typedef void* IBMAD_CALL_CONV (*f_mad_rpc) (const struct ibmad_port *srcport, ib_rpc_t* rpc,
                                            ib_portid_t* dport, void *payload, void* rcvdata);


struct __ibvsmad_hndl_t
{
    struct ibmad_port *srcport;

    ib_portid_t portid;
    int sock;
    int tp;
    int i2c_slave;
    int use_smp;
    int use_class_a;
    u_int64_t mkey;
    int mkey_is_supported;
    int timeout;
    int retries_num;
    u_int64_t vskey;
    int vskey_is_supported;
    enum MAD_DEST dest_type;

    DLL_HANDLE dl_handle;

    f_mad_rpc_open_port mad_rpc_open_port;
    f_mad_rpc_close_port mad_rpc_close_port;
    f_ib_vendor_call_via ib_vendor_call_via;
    f_ib_resolve_portid_str_via ib_resolve_portid_str_via;
    f_smp_query_via smp_query_via;
    f_smp_query_status_via smp_query_status_via;
    f_smp_set_via smp_set_via;
    f_smp_set_status_via smp_set_status_via;
    f_mad_rpc_set_retries mad_rpc_set_retries;
    f_mad_rpc_set_timeout mad_rpc_set_timeout;
    f_mad_rpc_rmpp mad_rpc_rmpp;
    f_mad_get_field mad_get_field;
    f_portid2str portid2str;
    f_smp_mkey_set smp_mkey_set;
    f_mad_send_via mad_send_via;
    f_mad_rpc mad_rpc;

    void *ibdebug;
};

typedef struct __ibvsmad_hndl_t ibvs_mad;

static int verbose = 0;

/********************************************************
**
*    Management class :     0x09 VendorSpecific
*    Management attribute : 0x50 ConfigSpaceAccess
*
*/

#define IB_SMP_ATTR_CR_ACCESS 0xff50
#define IB_DATA_INDEX     8
#define MAX_IB_SMP_DATA_SIZE    (IB_SMP_DATA_SIZE - IB_DATA_INDEX)
#define MAX_IB_SMP_DATA_DW_NUM  MAX_IB_SMP_DATA_SIZE / 4

#define CONFIG_ACCESS_MODE_2_DATA_OFFSET 4
#define CONFIG_ACCESS_MODE_2_BITMASK_OFFSET 8

void set_mkey_for_smp_mad(ibvs_mad *vsmad)
{
#ifdef __linux__
    if (vsmad->mkey) {
        vsmad->smp_mkey_set(vsmad->srcport, vsmad->mkey);
    } else {
        vsmad->smp_mkey_set(vsmad->srcport, 0);
    }
#else
    (void)vsmad;
#endif
}

// Attribute modifier for mode 0:
// Bits 24-31: Address MSB
// Bits 22-23: Mode = 0
// Bits 16-21: Number of dwords
// Bits 0-15: Address LSB
static u_int32_t create_attribute_mode_0(u_int32_t memory_address, u_int8_t num_of_dwords)
{
    return ( (EXTRACT(memory_address, 0, 16) << 00) & 0x0000ffff ) |
           ( (num_of_dwords << 16) & 0x00ff0000 ) |
           ( (EXTRACT(memory_address, 16, 8) << 24) & 0xff000000 );
}

// Attribute modifier for mode 2:
// Bits 22-23: Mode = 2
// Bits 16-21: Number of records (= number of dwords)
static u_int32_t create_attribute_mode_2(u_int8_t num_of_dwords)
{
    return  ( ( ( 2 << 22) & 0x800000 ) |
            ( (num_of_dwords << 16) & 0x00ff0000 ));
}

// For ConfigSpaceAccess Mad we use mode 2
// only for accessing addresses larger than 24 bits.
static unsigned int should_use_mode_2(u_int32_t memory_address, u_int8_t num_of_dwords)
{
    return memory_address + (num_of_dwords * 4) >
           MODE_0_MAX_ADDRESS_RANGE ? 1 : 0;
}

static void set_mad_data_for_mode_2(u_int32_t memory_address, u_int8_t num_of_dwords,
                                    u_int8_t* mad_data, u_int32_t* attribute_mod,
                                    u_int32_t* mask, unsigned int* data_offset)
{
    int i = 0;
    *attribute_mod = create_attribute_mode_2(num_of_dwords);

    // First dword of each record of ConfigSpaceAccess mode 2
    // contains the current address.
    for (i = 0; i < num_of_dwords; i++) {
        u_int32_t record_offset = memory_address + i;
        DWORD_TO_BYTES_BE(mad_data + IB_DATA_INDEX + (i * 4), &record_offset);
    }

    // Second dword contains the data.
    *data_offset = CONFIG_ACCESS_MODE_2_DATA_OFFSET;

    // Third dword contains the bitmask.
    *mask = 0xFFFFFFFF;
}

static uint64_t ibvsmad_craccess_rw_smp(ibvs_mad *h, u_int32_t memory_address, int method, u_int8_t num_of_dwords, u_int32_t *data)
{
    u_int8_t mad_data[IB_SMP_DATA_SIZE] = {0};
    int i;
    u_int8_t *p;
    u_int32_t attribute_mod = 0;
    u_int64_t mkey = 0;
    u_int32_t mask = 0;
    unsigned int data_offset = 0;
    unsigned int use_mode_2 = should_use_mode_2(memory_address, num_of_dwords);

    if (num_of_dwords > MAX_IB_SMP_DATA_DW_NUM) {
        IBERROR(("size is too big, maximum number of dwords is %d", MAX_IB_SMP_DATA_DW_NUM));
        return BAD_RET_VAL;
    }

    // Set the mkey
    mkey = __cpu_to_be64(h->mkey);
    memcpy(&mad_data[0], &mkey, 8);
    set_mkey_for_smp_mad(h);

    if (use_mode_2) {
        set_mad_data_for_mode_2(memory_address, num_of_dwords,
                                mad_data, &attribute_mod,
                                &mask, &data_offset);

    } else {
        attribute_mod = create_attribute_mode_0(memory_address, num_of_dwords);
    }

    DEBUG(("Sending ConfigSpaceAccess SMP MAD...\n"));
    if (h->portid.lid) {
        DEBUG(("Management Class: 0x1\n"));
    } else {
        DEBUG(("Management Class: 0x81\n"));
    }
    DEBUG(("Attribute Modifier = 0x%08x\n", attribute_mod));
     if (use_mode_2) {
        DEBUG(("Mode: 2\n"));
    } else {
        DEBUG(("Mode: 0\n"));
    }
    DEBUG(("Attribute ID = 0x%08x\n", IB_SMP_ATTR_CR_ACCESS));
    DEBUG(("Memory Address = 0x%08x\n", memory_address));
    DEBUG(("Number of dwords = %d\n", num_of_dwords));

    if (method == IB_MAD_METHOD_GET) {
        p = h->smp_query_via(mad_data, &h->portid, IB_SMP_ATTR_CR_ACCESS, attribute_mod, 0, h->srcport);

        if (!p) {
            return BAD_RET_VAL;
        }

        for (i = 0; i < num_of_dwords; i++) {
            BYTES_TO_DWORD_BE(data + i, mad_data + IB_DATA_INDEX + data_offset + (i * 4));
        }
    } else {
        for (i = 0; i < num_of_dwords; i++) {
            DWORD_TO_BYTES_BE(mad_data + IB_DATA_INDEX + data_offset + (i * 4), data + i);
            DWORD_TO_BYTES_BE(mad_data + IB_DATA_INDEX + CONFIG_ACCESS_MODE_2_BITMASK_OFFSET + (i * 4), &mask);
        }
        p = h->smp_set_via(mad_data, &h->portid, IB_SMP_ATTR_CR_ACCESS, attribute_mod, 0, h->srcport);
        if (!p) {
            return BAD_RET_VAL;
        }
    }

    return 0;
}

// TODO: Correct this value.
#define  MAX_VS_DATA_SIZE (IB_VENDOR_RANGE1_DATA_SIZE -  IB_DATA_INDEX)
#define  MAX_IB_VS_DATA_DW_NUM  MAX_VS_DATA_SIZE / 4

static uint64_t ibvsmad_craccess_rw_vs(ibvs_mad *h, u_int32_t memory_address,
                                       int method, u_int8_t num_of_dwords,
                                       u_int32_t *data, int class)
{
    u_int8_t vsmad_data[IB_VENDOR_RANGE1_DATA_SIZE] = {0};
    ib_vendor_call_t call;
    int i;
    u_int8_t *p;
    u_int32_t attribute_mod = 0;
    u_int32_t mask = 0;
    u_int64_t vskey = 0;
    unsigned int data_offset = 0;
    int use_mode_2 = should_use_mode_2(memory_address, num_of_dwords);

    if (h == NULL || data == NULL) {
        return BAD_RET_VAL;
    }

    if (num_of_dwords > MAX_IB_VS_DATA_DW_NUM) {
        IBERROR(("size (%d) is too big, maximum num of dwords is %d", num_of_dwords,
                 MAX_IB_VS_DATA_DW_NUM));
        return BAD_RET_VAL;
    }

    if (use_mode_2) {
        set_mad_data_for_mode_2(memory_address, num_of_dwords,
                                vsmad_data, &attribute_mod,
                                &mask, &data_offset);
    } else {
        attribute_mod = create_attribute_mode_0(memory_address, num_of_dwords);
    }

    call.method     = method;
    call.mgmt_class = class;
    call.attrid     = IB_VS_ATTR_CR_ACCESS;
    call.mod        = attribute_mod;
    call.oui        = IB_OPENIB_OUI;
    call.timeout    = 0;
    memset(&call.rmpp, 0, sizeof(call.rmpp));

    DEBUG(("Sending ConfigSpaceAccess VS MAD...\n"));
    DEBUG(("Management Class = 0x%02x\n", call.mgmt_class));
    DEBUG(("Attribute Modifier = 0x%08x\n", call.mod));
    if (use_mode_2) {
        DEBUG(("Mode: 2\n"));
    } else {
        DEBUG(("Mode: 0\n"));
    }
    DEBUG(("Attribute ID = 0x%08x\n", call.attrid));
    DEBUG(("Memory Address = 0x%08x\n", memory_address));
    DEBUG(("Number of dwords = %d\n", num_of_dwords));

    // Set the VSkey.
    vskey = __cpu_to_be64(h->vskey);
    memcpy(vsmad_data, &vskey, 8);

    for (i = 0; i < num_of_dwords; i++) {
        if (method == IB_MAD_METHOD_SET) {
            DWORD_TO_BYTES_BE(vsmad_data + IB_DATA_INDEX + data_offset + (i * 4), data + i);
            DWORD_TO_BYTES_BE(vsmad_data + IB_DATA_INDEX + CONFIG_ACCESS_MODE_2_BITMASK_OFFSET + (i * 4), &mask);
        }
    }

    p = h->ib_vendor_call_via(vsmad_data, &h->portid, &call, h->srcport);
    if (!p) {
        return BAD_RET_VAL;
    }

    for (i = 0; i < num_of_dwords; i++) {
        BYTES_TO_DWORD_BE(data + i, vsmad_data + IB_DATA_INDEX + data_offset + (i * 4));
    }

    return 0;
}

static uint64_t ibvsmad_craccess_rw(ibvs_mad *h, u_int32_t memory_address, int method, u_int8_t num_of_dwords, u_int32_t *data)
{
    if (h->use_smp) {
        return ibvsmad_craccess_rw_smp(h, memory_address, method, num_of_dwords, data);
    } else {
        if (h->use_class_a) {
            return ibvsmad_craccess_rw_vs(h, memory_address,
                                          method, num_of_dwords,
                                          data, IB_VENDOR_SPECIFIC_CLASS_0xA);
        } else {
            // Backward compatibility: Sending class 0x9.
            return ibvsmad_craccess_rw_vs(h, memory_address,
                                          method, num_of_dwords,
                                          data, IB_VENDOR_SPECIFIC_CLASS_0x9);
        }

    }
    return 0;
}

#ifdef __WIN__


int process_dynamic_linking(ibvs_mad *ivm, int mad_init)
{

    ivm->dl_handle = LoadLibrary(TEXT(LIB_IBMAD));

    if (ivm->dl_handle != NULL) {
        MY_GetProcAddress(ivm, mad_rpc_open_port        );
        MY_GetProcAddress(ivm, mad_rpc_close_port       );
        MY_GetProcAddress(ivm, ib_vendor_call_via       );
        MY_GetProcAddress(ivm, ib_resolve_portid_str_via);
        MY_GetProcAddress(ivm, smp_query_via            );
        MY_GetProcAddressIgnoreFail(ivm, smp_query_status_via );
        MY_GetProcAddress(ivm, smp_set_via              );
        MY_GetProcAddressIgnoreFail(ivm, smp_set_status_via );
        MY_GetProcAddress(ivm, mad_rpc_set_retries      );
        MY_GetProcAddress(ivm, mad_rpc_set_timeout      );
        MY_GetProcAddress(ivm, mad_rpc_rmpp             );
        MY_GetProcAddress(ivm, mad_rpc                  );
        MY_GetProcAddress(ivm, portid2str               );
        MY_GetProcAddress(ivm, mad_get_field            );
        MY_GetProcAddress(ivm, mad_send_via             );
        MY_GetVarAddress(ivm,  ibdebug                  );

    } else {

        IBERROR(("Failed to load "LIB_IBMAD ".dll library %#x", (unsigned int)GetLastError()));
        errno = ENOENT;
        return -1;
    }
    return 0;
}

int free_dll_handle(mfile *mf)
{
    return FreeLibrary(((ibvs_mad*)(mf->ctx))->dl_handle);
}

#else

int process_dynamic_linking(ibvs_mad *ivm, int mad_init)
{

    char *libs[] = {"libibmad.so.5", "libibmad.so.12"};

    u_int32_t i;
    (void)mad_init;
    for (i = 0; i < sizeof(libs) / sizeof(libs[0]); i++) {
        ivm->dl_handle = dlopen(libs[i], RTLD_LAZY);
        if (ivm->dl_handle) {
            break;
        }
    }
    if (!ivm->dl_handle) {
        const char *errstr = dlerror();
        IBERROR(("%s", errstr));
        //free(ivm);
        return -1;

    }

    dlerror();

    MY_DLSYM(ivm, mad_rpc_open_port        );
    MY_DLSYM(ivm, mad_rpc_close_port       );
    MY_DLSYM(ivm, ib_vendor_call_via       );
    MY_DLSYM(ivm, ib_resolve_portid_str_via);
    MY_DLSYM(ivm, smp_query_via            );
    MY_DLSYM_IGNORE_FAIL(ivm, smp_query_status_via );
    MY_DLSYM(ivm, smp_set_via              );
    MY_DLSYM_IGNORE_FAIL(ivm, smp_set_status_via   );
    MY_DLSYM(ivm, mad_rpc_set_retries      );
    MY_DLSYM(ivm, mad_rpc_set_timeout      );
    MY_DLSYM(ivm, mad_rpc_rmpp             );
    MY_DLSYM(ivm, mad_get_field            );
    MY_DLSYM(ivm, portid2str               );
    MY_DLSYM(ivm, smp_mkey_set             );
    MY_DLSYM(ivm, mad_send_via             );
    MY_DLSYM(ivm, mad_rpc                  );
    MY_DLSYM(ivm, ibdebug                  );
    return 0;
}


int free_dll_handle(mfile *mf)
{
    return dlclose(((ibvs_mad*)(mf->ctx))->dl_handle);
}

#endif

char* my_strdup(const char *name)
{
    int len;
    char *buf;

    if (name == NULL) {
        return NULL;
    }
    len = strlen(name);

    buf = malloc((len + 1) * sizeof(char));
    if (buf == NULL) {
        return NULL;

    }
    strcpy(buf, name);

    return buf;
}
#define MTCR_IB_TIMEOUT     "MTCR_IB_TIMEOUT"
#define MTCR_IB_RETRIES     "MTCR_IB_RETRIES"
#define MTCR_IB_VKEY        "MTCR_IB_VKEY"
#define MTCR_IBMAD_DEBUG "MTCR_IBMAD_DEBUG"

int get_env_var(char *env_name, int *env_var)
{
    char *env_val;
    env_val = getenv(env_name);
    if (env_val) {
        *env_var = atol(env_val);
    }
    return 0;
}
int get_64_env_var(char *env_name, u_int64_t *env_var)
{
    char *env_val, *endp = NULL;
    env_val = getenv(env_name);
    if (env_val) {
        *env_var = strtoull(env_val, &endp, 0);
    }
    return 0;
}

int get_env_vars(ibvs_mad *ivm)
{
    get_env_var(MTCR_IB_TIMEOUT, &(ivm->timeout));
    get_env_var(MTCR_IB_RETRIES, &(ivm->retries_num));
    get_64_env_var(MTCR_IB_VKEY, &((ivm->vskey)));
    return 0;
}



int is_vs_crspace_supported(ibvs_mad *h)
{
    u_int8_t *p;
    u_int8_t mad_data[IB_SMP_DATA_SIZE] = {0};
    u_int32_t dev_id;
    u_int32_t data = 0;
    int i = 0;
    u_int32_t unsupported_devs[UNSUPP_DEVS_NUM] = {
        0x6746,     /* MT26438 [ConnectX-2 VPI w/ Virtualization+]"*/
        0x6764,     /* MT26468 [Mountain top]"                     */
        0xbd34,     /* IS4 IB SDR"                                 */
        0xbd35,     /* IS4 IB DDR"                                 */
        0xbd36,     /* IS4 IB QDR"                                 */
        0xfa66,     /* BridgeX VPI up, E/FC down"                  */
        0xfa7a,     /* BridgeX EN up, E/FC down"                   */
        0x1001,     /* ConnectX-2 VF"                              */
        0x1003,     /* MT27500 [ConnectX-3]"                       */
        0x1005,     /* MT27510 Family"                             */
        0x1007,     /* MT27520 ConnectX-3 Pro Family"              */

    };

    uint64_t ret = ibvsmad_craccess_rw_vs(h, DEVID_ADDRESS,
                                          IB_MAD_METHOD_GET, 1,
                                          &data, IB_VENDOR_SPECIFIC_CLASS_0xA);
    if (!ret) {
        h->use_class_a = 1;
        return 1;
    }

    DEBUG(("Vendor Specific is not supported, checking SMP .. "));
    set_mkey_for_smp_mad(h);
    p = h->smp_query_via(mad_data, &h->portid, IB_ATTR_NODE_INFO, 0, 0, h->srcport);

    if (NULL == p) {
        return 1;
    }

    dev_id  = h->mad_get_field(mad_data, 0, IB_NODE_DEVID_F);

    for (i = 0; i < UNSUPP_DEVS_NUM; i++) {
        if (dev_id == unsupported_devs[i]) {
            return 1;
        }
    }

    return 0;
}




typedef enum key_type_t {
    MKEY,
    VSKEY
} key_type;




char* trim(char* string)
{
    char* back;

    // Left trim.
    while (isspace(*string)) {
        string++;
    }

    int len = strlen(string);

    if (len == 0) {
        return(string);
    }

    // Right trim.
    back = string + len;

    while (isspace(*--back)) {}

    *(back + 1) = '\0';

    return string;
}




int get_mft_conf_field_value(char* line, char* field_name,
                             char* value, int* is_empty)
{
    char* delimiter = "=";
    char* tmp_value;

    if (strstr(line, field_name) != NULL)
    {
        // Get the value.
        tmp_value = strtok(line, delimiter);
        tmp_value = strtok(NULL, delimiter);

        // Remove spaces.
        tmp_value = trim(tmp_value);

        if (strlen(tmp_value))
        {
            memcpy(value, tmp_value, sizeof(strlen(tmp_value)));
        }
        else
        {
            *is_empty = 1;
        }

        return 0;
    }

    return -1;
}




int load_file(FILE** file_descriptor, const char* file_name_path)
{
    // Open the file.
    *file_descriptor = fopen(file_name_path, "r");

    if (!(*file_descriptor))
    {
        // Failed to open the file.
        return -1;
    }

    return 0;
}




int parse_mft_cfg_file(char* sm_config_path, key_type key)
{
    const char* sm_config_default_path = "/var/cache/opensm/";
    const char* mft_conf_file_path = "/etc/mft/mft.conf";
    int is_key_enabled = 0;
    int is_empty = 0;
    int ret_value = -1;
    char line[1024] = {0};
    char value[256] = {0};
    char* key_enabled_field;
    if (key == MKEY)
    {
        key_enabled_field = "mkey_enable";
    }

    else
    {
        key_enabled_field = "vskey_enable";
    }

    FILE* mft_conf_file_descriptor = NULL;


    // Load the mft configuration file.
    if (load_file(&mft_conf_file_descriptor, mft_conf_file_path))
    {
        // Failed to open the file.
        return -1;
    }

    // Go over the content file.
    while ((fgets(line, 1024, mft_conf_file_descriptor)))
    {
        // Check if the mkey feature is enable.
        if (!get_mft_conf_field_value(line, key_enabled_field,
                                      value, &is_empty))
        {
            // key feature is supported ?
            if(strcmp(value, "yes"))
            {
                // Mkey is unsuppurted.
                break;
            }

            is_key_enabled = 1;
        }

        // Check if the user changed the default mkey directory.
        else if (!get_mft_conf_field_value(line, "sm_config_dir",
                                           value, &is_empty))
        {
            if (!is_key_enabled)
            {
                // key feature is disabled.
                break;
            }

            // Empty value ?
            if (is_empty)
            {
                // Use the default sm path.
                memcpy(sm_config_path, sm_config_default_path, strlen(sm_config_default_path));
            }
            else
            {
                memcpy(sm_config_path, value, strlen(value));
            }

            // sm_config_path found.
            ret_value = 0;
        }
    }

    // Close the file.
    fclose(mft_conf_file_descriptor);

    return ret_value;
}



void get_lid_integer(char* lid, int* lid_integer)
{
    int base = 10;

    // Check if we have '0x' in the beginning of the string.
    if ((strlen(lid) > 1) && (lid[0] == '0') &&
            ((lid[1] == 'x') || (lid[1] == 'X')))
    {
        base = 16;
    }

    *lid_integer = strtol(lid, NULL, base);
}



int find_guid(char* lid, char* guid,
              char* line)
{
    char* delimiter = " ";
    char* tmp_value;
    char* tmp_guid;
    int ret_value = -1;
    int lid_lower_bound;
    int lid_upper_bound;
    int lid_from_device;

    CHECK_NULL(guid)

    // Get the lid ranges from device,
    // remove spaces and convert to integer
    get_lid_integer(trim(lid), &lid_from_device);

    tmp_guid = strtok(line, delimiter);
    CHECK_NULL(tmp_guid)

    tmp_value = strtok(NULL, delimiter);
    CHECK_NULL(tmp_value)

    get_lid_integer(trim(tmp_value), &lid_lower_bound);

    tmp_value = strtok(NULL, delimiter);
    CHECK_NULL(tmp_value)

    get_lid_integer(trim(tmp_value), &lid_upper_bound);

    if (lid_from_device >= lid_lower_bound && lid_from_device <= lid_upper_bound)
        {
            strcpy(guid, tmp_guid);
            ret_value = 0;
        }

    return ret_value;
}


int parse_lid2guid_file(char* sm_config_path, char* lid,
                        char* guid)
{
    const char* guid2lid= "guid2lid";
    FILE* file_descriptor = NULL;
    char line[1024] = {0};
    char conf_path[256];
    int ret_value = -1;


    // Parse the guid2lid file.
    strcpy(conf_path, sm_config_path);
    strcat(conf_path, guid2lid);

    if (load_file(&file_descriptor, conf_path))
    {
        // Failed to open file.
        return -1;
    }

    // Go over the content of the guid2lid file.
    while ((fgets(line, 1024, file_descriptor)))
    {
        if (!find_guid(lid, guid,
                       line))
        {
            ret_value = 0;
            break;
        }
    }

    fclose(file_descriptor);

    // No guid found.
    return ret_value;
}


int parse_guid2key_file(ibvs_mad* ivm, char* sm_config_path,
                         char* guid, key_type key)
{
    char* guid2key_filename;
    char* delimiter = " ";
    char* tmp_value;
    FILE* file_descriptor = NULL;
    char line[1024] = {0};
    char conf_path[256];
    int ret_value = -1;

    if (key == MKEY)
    {
        guid2key_filename = "guid2mkey";
    }

    else
    {
        guid2key_filename = "guid2vskey";
    }

    // Parse the guid2lid file.
    strcpy(conf_path, sm_config_path);
    strcat(conf_path, guid2key_filename);

    if (load_file(&file_descriptor, conf_path))
    {
        // Failed to open file.
        return -1;
    }

    // Go over the content of the guid2key file.
    while ((fgets(line, 1024, file_descriptor)))
    {
        // Get the key.
        tmp_value = strtok(line, delimiter);

        if (!strcmp(tmp_value, guid))
        {
            tmp_value = strtok(NULL, delimiter);

            if (key == MKEY)
            {
                ivm->mkey = strtoull(tmp_value, NULL, 0);
            }

            else
            {
                ivm->vskey = strtoull(tmp_value, NULL, 0);
            }

            ret_value = 0;
            break;
        }
    }

    fclose(file_descriptor);

    // Failed to get the mkey.
    return ret_value;
}




int extract_key(ibvs_mad* ivm, char* sm_config_path,
                 char* lid, key_type key)
{
    char guid[KEY_GUID_SIZE];

    // Parse the lid2guid file.
    if (parse_lid2guid_file(sm_config_path, lid,
                            guid))
    {
        return -1;
    }

    // Parse the guid2key file.
    if (parse_guid2key_file(ivm, sm_config_path,
                             guid, key))
    {
        return -1;
    }

    return 0;
}




int get_key(ibvs_mad* ivm, char* lid, key_type key)
{
    char sm_config_path[256] = {0};


    // Parameters validation.
    if(!ivm || !lid)
    {
        return -1;
    }

    // Parse the configuration file in order to extract the key info.
    if(parse_mft_cfg_file(sm_config_path, key))
    {
        // Failed to parse the key fields from
        //   the mft configuration file.
        return -1;
    }

    // Extract the key.
    if(extract_key(ivm, sm_config_path,
                    lid, key))
    {
        // Failed to extract the key.
        return -1;
    }

    return 0;
}


/********************************************************
**
*    Initialize madrpc; Register the vendor specific management classes under
*    the libibmad library; Resolve destination lid from input.
*
*/
int mib_open(const char *name, mfile *mf, int mad_init)
{
    char        *ca              = 0;
    int mgmt_classes[NUMBER_OF_MGMT_ELEMENTS] = {IB_SMI_CLASS,
                                                 IB_SMI_DIRECT_CLASS,
                                                 IB_VENDOR_SPECIFIC_CLASS_0x9,
                                                 IB_VENDOR_SPECIFIC_CLASS_0xA};
    ib_portid_t *sm_id           = 0;
    int ca_port         = 0;
    ibvs_mad    *ivm             = NULL;
    char        *nbuf            = NULL;
    char        *path_str, *p;
    int rc              = -1;
    int lid_provided = 0;
    char        *sl_str;

    char *first_comma;
    char *second_comma;
    //ibdebug = 1;
    if (!mf || !name) {
        IBERROR(("Bad(null) device argument for inband access"));
        errno = EINVAL;
        goto end;
    }
    if (!(ivm = (ibvs_mad*)malloc(sizeof(ibvs_mad)))) {
        IBERROR(("can't allocate ibvsmad_mfile"));
        errno = ENOMEM;
        goto end;
    }
    memset(ivm, 0, sizeof(ibvs_mad));

    nbuf = my_strdup(name);
    if (nbuf == NULL) {
        errno = ENOMEM;
        goto end;
    }

    ivm->mkey_is_supported = 0;
    ivm->vskey_is_supported = 0;

    if (strncmp("ibdr-", nbuf, 5) == 0) {
        ivm->use_smp = 1;
        ivm->dest_type = IB_DEST_DRPATH;
        path_str  = nbuf + 5;
    } else if (strncmp("iblid-", nbuf, 6) == 0) {
        ivm->use_smp = 1;
        ivm->dest_type = IB_DEST_LID;
        path_str  = nbuf + 6;
    } else if ((p = strstr(nbuf, "lid-")) != 0) {
#ifdef __linux__
        ivm->mkey_is_supported = 1;
        ivm->vskey_is_supported = 1;
#endif
        lid_provided = 1;
        ivm->dest_type = IB_DEST_LID;
        path_str  = p + 4;

    } else if ((p = strstr(nbuf, "lid_noinit-")) != 0) {
#ifdef __linux__
        ivm->mkey_is_supported = 1;
        ivm->vskey_is_supported = 1;
#endif
        lid_provided = 1;
        ivm->dest_type = IB_DEST_LID;
        path_str  = p + 11;
        mad_init = 0;

    } else {
        IBERROR(("Bad device argument for inband access"));
        errno = EINVAL;
        goto end;
    }

    first_comma = strstr(nbuf, ",");
    if (first_comma) {
        *first_comma = '\0';
        ca = first_comma + 1;

        second_comma = strstr(ca, ",");
        if (second_comma) {
            char *ep;
            *second_comma = '\0';

            ca_port = strtol(second_comma + 1, &ep, 0);

            if (*ep != '\0') {
                IBERROR(("Bad port number format (%s)", second_comma + 1));
                errno = EINVAL;
                goto end;
            }

        }
    }

    ivm->retries_num = MAD_DEF_RETRIES;
    ivm->timeout     = MAD_DEF_TIMEOUT_MS;
    // Get env variables.
    get_env_vars(ivm);
    // The DR in the device name is a '.' separated list.
    // Change it to a ',' separated list like ibmad likes.
    if (ivm->dest_type == IB_DEST_DRPATH) {
        char *c;
        for (c = path_str; *c; c++) {
            if (*c == '.') {
                *c = ',';
            }
        }
    }

#ifdef IBVSMAD_DLOPEN

    ivm->mad_rpc_open_port         = mad_rpc_open_port;
    ivm->mad_rpc_close_port        = mad_rpc_close_port;
    ivm->ib_vendor_call_via        = ib_vendor_call_via;
    ivm->ib_resolve_portid_str_via = ib_resolve_portid_str_via;
    ivm->smp_query_via             = smp_query_via;
    ivm->smp_set_via               = smp_set_via;
    ivm->mad_rpc_set_retries       = mad_rpc_set_retries;
    ivm->mad_rpc_set_timeout       = mad_rpc_set_timeout;
    ivm->mad_get_field             = mad_get_field;
    ivm->portid2str                = portid2str;

#ifdef __linux__
    ivm->smp_mkey_set              = smp_mkey_set;
#endif

#else
    if (process_dynamic_linking(ivm, mad_init) == -1) {
        goto end;
    }
#endif
    get_env_var(MTCR_IBMAD_DEBUG, ivm->ibdebug);

    ivm->srcport = ivm->mad_rpc_open_port(ca, ca_port,
                                          mgmt_classes, NUMBER_OF_MGMT_ELEMENTS);
    if (ivm->srcport == NULL) {
        goto end;
    }

    ivm->mad_rpc_set_retries(ivm->srcport, ivm->retries_num);
    ivm->mad_rpc_set_timeout(ivm->srcport, ivm->timeout);

    // Initialize the mkey & vskey.
    ivm->mkey = 0;
    ivm->vskey = 0;

    if (ivm->mkey_is_supported) {
        rc = get_key(ivm, path_str, MKEY);
        // Do we have an mkey?
        if (!rc) {
            // Set the mkey.
            ivm->smp_mkey_set(ivm->srcport, ivm->mkey);
        }
    }

    if (ivm->vskey_is_supported) {
        get_key(ivm, path_str, VSKEY);
    }

    rc = ivm->ib_resolve_portid_str_via(&ivm->portid, (char*)path_str,
            ivm->dest_type, sm_id, ivm->srcport);
    if (rc != 0) {
        IBERROR(("can't resolve destination port %s", path_str));
        goto end;
    }

    //TODO: Remove the SL setting if DR method is mainly used.

    // For ConnectIB:
    // If the target device is connectib or SX and we use LID rout, use the SMP LID route and not the GPM
    if (lid_provided) {
        if (is_vs_crspace_supported(ivm)) {
            DEBUG(("For this LID using VS MAD"));
            ivm->use_smp = 0;
        } else {
            DEBUG(("For this LID using SMP MAD"));
            ivm->use_smp = 1;
        }
    }

#define MTCR_IBSL_ENV "MTCR_IB_SL"

    if (!ivm->use_smp) {
        sl_str = getenv(MTCR_IBSL_ENV);
        if (sl_str) {
            char *ep;
            u_int32_t sl = strtoul(sl_str, &ep, 0);
            if (*ep) {
                fprintf(stderr, "-E- Failed to parse env var %s (%s). Ignoring\n", MTCR_IBSL_ENV, sl_str);
            } else {
                ivm->portid.sl = (u_int8_t)sl;
            }
        }
    }

    mf->ctx = ivm;

    if (nbuf) {
        free(nbuf);
    }

    return 0;
end:
    if (ivm) {
#ifndef __WIN__
        if (ivm->dl_handle) {
            dlclose(ivm->dl_handle);
        }
#endif
        free(ivm);
    }
    if (nbuf) {
        free(nbuf);
    }
    return -1;
}



/********************************************************
**
*    Free resources
*
*/
int mib_close(mfile *mf)
{
    if (mf) {
        if (mf->ctx) {
            // TODO: free the ddl handlers
            ibvs_mad *h = (ibvs_mad*)(mf->ctx);
            h->mad_rpc_close_port(h->srcport);
    #ifndef IBVSMAD_DLOPEN
            free_dll_handle(mf);
    #endif
            free(mf->ctx);
            mf->ctx = NULL;
        }
    }
    return 0;
}

#define CHECK_ALIGN(length) { \
        if (length % 4) {                                       \
            IBERROR(("Size must be 4 aligned, got %d", length)); \
            return -1;                                          \
        }                                                       \
}


int mib_get_chunk_size(mfile *mf)
{
    if (!mf || !mf->ctx) {
        IBERROR(("get chunk size failed. Null Param."));
        return -1;
    }
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);
    if (h->use_smp) {
        return MAX_IB_SMP_DATA_SIZE;
    }
    return MAX_VS_DATA_SIZE;
}


/********************************************************
**
*    Read an IS3 CR-Space 32 bit register
*
*/
int mib_read4(mfile *mf, u_int32_t memory_address, u_int32_t *data)
{
    if (!mf || !mf->ctx || !data) {
        IBERROR(("cr access read failed. Null Param."));
        return -1;
    }
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);

    DEBUG(("mread4 of 0x%08x", memory_address));
    if (ibvsmad_craccess_rw(h, memory_address, IB_MAD_METHOD_GET, 1, data) == ~0ull) {
        IBERROR(("cr access read to %s failed", h->portid2str(&h->portid)));
        return -1;
    }
    return 4;
}

/********************************************************
**
*    Write an IS3 CR-Space 32 bit register
*
*/
int mib_write4(mfile *mf, u_int32_t memory_address, u_int32_t _data)
{
    if (!mf || !mf->ctx) {
        IBERROR(("cr access write failed. Null Param."));
        return -1;
    }
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);

    u_int32_t data = _data;
    DEBUG(("mwrite4 of 0x%08x\n", memory_address));

    if (ibvsmad_craccess_rw(h, memory_address, IB_MAD_METHOD_SET, 1, &data) == ~0ull) {
        IBERROR(("cr access write to %s failed", h->portid2str(&h->portid)));
        return -1;
    }
    return 4;
}

enum {
    BLOCKOP_READ,
    BLOCKOP_WRITE
};

int mib_block_op(mfile *mf, unsigned int offset, u_int32_t *data, int length, int op)
{
    if (!mf || !mf->ctx || !data) {
        IBERROR(("cr access read failed. Null Param."));
        return -1;
    }
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);
    int method = IB_MAD_METHOD_GET;
    if (op == BLOCKOP_WRITE) {
        method = IB_MAD_METHOD_SET;
    }
    CHECK_ALIGN(length);
    int chunk_size = mib_get_chunk_size(mf);
    // for addresses > 24 bits we use ConfigSpaceAccess mode 2
    // which is limited to 72 bytes.
    if (offset + MAX_VS_DATA_SIZE > MODE_0_MAX_ADDRESS_RANGE) {
        chunk_size = MODE_2_MAX_DATA_SIZE;
    }
    int t_offset = 0;
    while (t_offset < length) {
        int left_size = length - t_offset;
        int to_op = left_size > chunk_size ? chunk_size : left_size;
        unsigned int curret_offset = offset + t_offset;
        if (ibvsmad_craccess_rw(h, curret_offset, method, (to_op / 4), data + t_offset / 4) == ~0ull) {
            IBERROR(("cr access %s to %s failed", op == BLOCKOP_READ ? "read" : "write",
                     h->portid2str(&h->portid)));
            return -1;
        }
        // If approaching addresses > 24 bits we will switch to mode 2.
        if (curret_offset + chunk_size > MODE_0_MAX_ADDRESS_RANGE) {
            chunk_size = MODE_2_MAX_DATA_SIZE;
        }
        t_offset += chunk_size;
    }
    return length;
}

MTCR_API int mib_readblock(mfile *mf, unsigned int offset, u_int32_t *data, int length)
{
    return mib_block_op(mf, offset, data, length, BLOCKOP_READ);
}
MTCR_API int mib_writeblock(mfile *mf, unsigned int offset, u_int32_t *data, int length)
{
    return mib_block_op(mf, offset, data, length, BLOCKOP_WRITE);
}

int is_managed_node_supports_swreset(mfile *mf)
{
    ib_vendor_call_t call;
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);
    u_int8_t *p;
    u_int32_t vsmad_data[IB_VENDOR_RANGE1_DATA_SIZE/4] = {0};

    call.method     = IB_MAD_METHOD_GET;
    call.mgmt_class = IB_VENDOR_SPECIFIC_CLASS_0xA;
    call.attrid     = IB_VS_ATTR_GENERAL_INFO;
    call.mod        = 0;
    call.oui        = IB_OPENIB_OUI;
    call.timeout    = 0;
    memset(&call.rmpp, 0, sizeof (call.rmpp));

    p = h->ib_vendor_call_via(vsmad_data, &h->portid, &call, h->srcport);
    if (!p) {
        fprintf(stderr, "-E- ib mad method call failed.\n");
        return 0;
    }

    int i;
    for (i = 0; i < IB_VENDOR_RANGE1_DATA_SIZE/4; i++) {
        vsmad_data[i] = __be32_to_cpu(vsmad_data[i]);
    }

    // vend_key 0x8 bytes, which present in any vendor specific MAD return in vsmad_data.
    // We want to skip them when relating GeneralInfo MAD fields in specific.
    // The capability_mask offset which is 0x80, is calculated from the beginning of GeneralInfo MAD fields.
    // So overall we have an offset of 0x8+0x80 bytes.
    const int capability_mask_byte_offset = 0x8+0x80;
    const int is_enh_port0_device_reset_supported_bit_offset = 25;
    return EXTRACT(vsmad_data[capability_mask_byte_offset/4],
                   is_enh_port0_device_reset_supported_bit_offset,
                   1);
}

int is_node_managed(ibvs_mad *h)
{
    u_int8_t *p;
    u_int8_t mad_data[IB_SMP_DATA_SIZE] = {0};
    u_int8_t enhanced_port;

    // Set the mkey.
    u_int64_t mkey = __cpu_to_be64(h->mkey);
    memcpy(&mad_data[0], &mkey, 8);
    set_mkey_for_smp_mad(h);

    p = h->smp_query_via(mad_data, &h->portid, IB_ATTR_SWITCH_INFO, 0, 0, h->srcport);

    if (NULL == p) {
        return 0;
    }

    enhanced_port = EXTRACT(mad_data[16], /* Big endian */ 3, 1);
    return enhanced_port;
}
/********************************************************
**
*    Management class :     0x0A VendorSpecific
*    Management attribute : 0x12 SwReset
*

*/
#define MTCR_SWRESET_ENV "MTCR_SWRESET_TIMER"
int mib_swreset(mfile *mf)
{
    if (!mf || !mf->ctx) {
        errno = EINVAL;
        IBERROR(("swreset write failed. Null Param."));
        return -1;
    }

    u_int32_t swreset_timer = 15;
    char *ep;
    char *swreset_env;
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);
    u_int8_t *p;
    u_int8_t vsmad_data[IB_VENDOR_RANGE1_DATA_SIZE] = {0};
    ib_vendor_call_t call;

    swreset_env = getenv(MTCR_SWRESET_ENV);
    if (swreset_env) {

        u_int32_t new_timer = strtol(swreset_env, &ep, 0);
        if (*ep != '\0') {
            fprintf(stderr, "-W- Bad %s env var format. Ignoring\n", MTCR_SWRESET_ENV);
        } else if (new_timer > 255) {
            fprintf(stderr, "-W- Bad %s env var value ( > 255). Ignoring\n", MTCR_SWRESET_ENV);
        } else {
            /* All OK */
            fprintf(stderr, "-I- Set reset timer to %d seconds\n", new_timer);
            swreset_timer = new_timer;
        }
    }

    if (is_node_managed(h) && !is_managed_node_supports_swreset(mf)) {
        errno = OP_NOT_SUPPORTED;
        return -1;
    }

    call.method     = IB_MAD_METHOD_SET;
    call.mgmt_class = IB_VENDOR_SPECIFIC_CLASS_0xA;
    call.attrid     = IB_VS_ATTR_SW_RESET;
    call.mod        = swreset_timer;
    call.oui        = IB_OPENIB_OUI;
    call.timeout    = 0;
    memset(&call.rmpp, 0, sizeof call.rmpp);

    p = h->ib_vendor_call_via(vsmad_data, &h->portid, &call, h->srcport);
    if (!p) {
        return -1;
    }

    return 0;
}

#define IB_SMP_ATTR_REG_ACCESS 0xff52

static int mib_status_translate(int status)
{
    switch ((status >> 2) & 0x7) {
    case 1:
        return ME_MAD_BAD_VER;

    case 2:
        return ME_MAD_METHOD_NOT_SUPP;

    case 3:
        return ME_MAD_METHOD_ATTR_COMB_NOT_SUPP;

    case 7:
        return ME_MAD_BAD_DATA;
    }

    if (status & 0x1) {
        return ME_MAD_BUSY;
    } else if ((status >> 1) & 0x1) {
        return ME_MAD_REDIRECT;
    }

    return ME_MAD_GENERAL_ERR;
}

uint8_t *cls_a_query_via(void* rcvbuf, ibvs_mad* vsmad,
                         ib_portid_t* dest, const unsigned timeout,
                         const unsigned attribute_id, const struct ibmad_port* srcport,
                         int* return_status)
{
    ib_rpc_v1_t rpc;
    rpc.rstatus = 0;
    ib_rpc_t* rpcold = (ib_rpc_t*)(void*)&rpc;
    int lid = dest->lid;
    void* p_ret;

    if (lid == -1) {
        IBWARN("only lid routed is supported");
        return NULL;
    }

    rpc.mgtclass = IB_VENDOR_SPECIFIC_CLASS_0xA | IB_MAD_RPC_VERSION1;
    rpc.method = MACCESS_REG_METHOD_SET;
    rpc.attr.id = attribute_id;
    rpc.attr.mod = 0;
    rpc.timeout = timeout;
    rpc.datasz = CLASS_VS_SIZE_BYTES;
    rpc.dataoffs = CLASS_VS_DATA_OFFSET;
    // There is no member for VSKey in rpc struct,
    // but the offset for VSKey & MKey in the mad is the same.
    rpc.mkey = vsmad->vskey;

    if (!dest->qp) {
        dest->qp = 1;
    }
    if (!dest->qkey) {
        dest->qkey = IB_DEFAULT_QP1_QKEY;
    }

    p_ret = vsmad->mad_rpc(srcport, rpcold, dest, rcvbuf, rcvbuf);
    errno = rpc.error;
    *return_status = rpc.rstatus;
    return p_ret;
}

int mib_send_cls_a_access_reg_mad(mfile *mf, u_int8_t *data)
{
    if (!mf || !mf->ctx || !data) {
        IBERROR(("mib_send_cls_a_access_reg_mad failed. Null Param."));
        return ME_BAD_PARAMS;
    }
    ibvs_mad* vsmad = (ibvs_mad*)(mf->ctx);
    u_int8_t* call_result;
    int return_status = -1;

    //Set the VSKey.
    if (vsmad->vskey) {
        vsmad->smp_mkey_set(vsmad->srcport, vsmad->vskey);
    } else {
        vsmad->smp_mkey_set(vsmad->srcport, 0);
    }

    call_result = cls_a_query_via(data, vsmad, &vsmad->portid,
                                  0, IB_SMP_ATTR_REG_ACCESS,
                                  vsmad->srcport, &return_status);

    if (!call_result || return_status > 0) {
        if (return_status > 0) {
            return mib_status_translate(return_status);
        }
        return -1;
    }

    return ME_OK;
}

int response_expected(int method)
{
    return method == IB_MAD_METHOD_GET ||
           method == IB_MAD_METHOD_SET ||
           method == IB_MAD_METHOD_TRAP;
}


uint8_t* ib_vendor_call_status_via(ibvs_mad* vsmad, void* data,
                                   ib_portid_t* portid, ib_vendor_call_t* call,
                                   struct ibmad_port* srcport, int* return_status)
{
    ib_rpc_v1_t rpc;
    rpc.rstatus = 0;
    ib_rpc_t* rpcold = (ib_rpc_t*)(void*)&rpc;
    int range1 = 0, resp_expected;
    void *p_ret;

    if (portid->lid <= 0) {
        return NULL;    /* no direct SMI */
    }

    if (!(range1 = mad_is_vendor_range1(call->mgmt_class)) &&
        !(mad_is_vendor_range2(call->mgmt_class))) {
        return NULL;
    }

    resp_expected = response_expected(call->method);

    rpc.mgtclass = call->mgmt_class | IB_MAD_RPC_VERSION1;
    rpc.method = call->method;
    rpc.attr.id = call->attrid;
    rpc.attr.mod = call->mod;
    rpc.timeout = resp_expected ? call->timeout : 0;
    rpc.datasz =
        range1 ? IB_VENDOR_RANGE1_DATA_SIZE : IB_VENDOR_RANGE2_DATA_SIZE;
    rpc.dataoffs =
        range1 ? IB_VENDOR_RANGE1_DATA_OFFS : IB_VENDOR_RANGE2_DATA_OFFS;

    if (!range1) {
        rpc.oui = call->oui;
    }

    portid->qp = 1;
    if (!portid->qkey) {
        portid->qkey = IB_DEFAULT_QP1_QKEY;
    }

    if (resp_expected) {
        p_ret = vsmad->mad_rpc_rmpp(srcport, rpcold, portid, NULL, data);
        errno = rpc.error;
        *return_status = rpc.rstatus;
        return p_ret;
    }

    return vsmad->mad_send_via(rpcold, portid, NULL, data, srcport) < 0 ? NULL : data;
}

// AccessRegisterGMP does not use OperationTLV struct
// and encodes the register operation status in the
// returned status field of the MAD.
// The translation table is available in the MADs PRM.
int translate_mad_status_to_reg_status_gmp(int mad_status)
{
    switch(mad_status) {
        case 0:
            return ME_OK;
        case 1:
            return ME_REG_ACCESS_DEV_BUSY;
        case 4:
            return ME_REG_ACCESS_CLASS_NOT_SUPP;
        case 20:
            return ME_REG_ACCESS_REG_NOT_SUPP;
        case 12:
            return ME_REG_ACCESS_METHOD_NOT_SUPP;
        case 28:
            return ME_REG_ACCESS_BAD_PARAM;
        default:
            return ME_REG_ACCESS_UNKNOWN_ERR;
    }
}

int mib_send_gmp_access_reg_mad(mfile *mf, u_int32_t *data,
                                u_int32_t reg_size, u_int32_t reg_id,
                                maccess_reg_method_t reg_method, int *reg_status)
{
    // The buffer should contain:
    // 2 dwords for the vskey,
    // 1 dword for a configuration dword,
    // 55 dwords for data.
    // All sizes and offsets are in dword unit.
    const int vskey_offset = 0;
    const int vskey_size = 2;
    const int config_offset = 2;
    const int config_size = 1;
    const int data_offset = 3;
    const int data_size = 55;
    const int buffer_size = vskey_size + config_size + data_size; // == 58
    u_int32_t vsmad_data[buffer_size];
    u_int32_t orig_vsmad_data[buffer_size];

    if (!mf || !mf->ctx || !data) {
        IBERROR(("mib_send_gmp_access_reg_mad failed. Null Param."));
        return ME_BAD_PARAMS;
    }
    if (!mib_supports_reg_access_gmp(mf, reg_method)) {
        return ME_GMP_MAD_UNSUPPORTED_OPERATION;
    }

    memset(vsmad_data, 0x0, buffer_size);
    memset(orig_vsmad_data, 0x0, buffer_size);

    ibvs_mad *vsmad = (ibvs_mad*)(mf->ctx);
    u_int64_t vskey = __cpu_to_be64(vsmad->vskey);
    memcpy(&vsmad_data[vskey_offset], &vskey, vskey_size * 4);
    memcpy(&vsmad_data[data_offset], data, data_size * 4);
    memcpy(&orig_vsmad_data[0], vsmad_data, buffer_size * 4);

    ib_vendor_call_t call;
    u_int8_t *call_result;
    call.method     = reg_method;
    call.mgmt_class = IB_VENDOR_SPECIFIC_CLASS_0xA;
    call.attrid     = IB_VS_ATTR_ACCESS_REGISTER_GMP;
    call.mod        = reg_id;
    call.oui        = IB_OPENIB_OUI;
    call.timeout    = 0;
    memset(&call.rmpp, 0, sizeof(call.rmpp));

    int num_of_blocks = (reg_size / (data_size * 4)) + ((reg_size % (data_size * 4)) ? 1 : 0);
    int block_num;
    u_int32_t block_dword;
    int return_status = -1;

    for (block_num = 0; block_num < num_of_blocks; block_num++) {
        block_dword = __cpu_to_be32(((u_int32_t)block_num) << 16); //block offset in the config dword, see PRM for details
        memcpy(&vsmad_data[config_offset], &block_dword, config_size * 4);
        call_result = ib_vendor_call_status_via(vsmad, vsmad_data, &vsmad->portid, &call, vsmad->srcport, &return_status);
        if (!call_result) {
            return -1;
        }

        if (return_status > 0) {
            *reg_status = translate_mad_status_to_reg_status_gmp(return_status);
        }
        int num_of_bytes = (block_num == num_of_blocks - 1) ? ((int)reg_size % (data_size * 4)) : (data_size * 4);
        memcpy(&data[(block_num * data_size)], &vsmad_data[data_offset], num_of_bytes);

        memcpy(vsmad_data, orig_vsmad_data, buffer_size * 4);
    }
    return ME_OK;
}

int mib_get_gmp(mfile *mf, unsigned attr_id, unsigned mod, u_int32_t *vsmad_data, size_t vsmad_data_len)
{
    if (!mf || !mf->ctx || !vsmad_data || vsmad_data_len != IB_VENDOR_RANGE1_DATA_SIZE/4) {
        return ME_BAD_PARAMS;
    }

    ib_vendor_call_t call;
    ibvs_mad *vs_mad = (ibvs_mad*)(mf->ctx);
    u_int8_t *call_result;

    call.method     = IB_MAD_METHOD_GET;
    call.mgmt_class = IB_VENDOR_SPECIFIC_CLASS_0xA;
    call.attrid     = attr_id;
    call.mod        = mod;
    call.oui        = IB_OPENIB_OUI;
    call.timeout    = 0;
    memset(&call.rmpp, 0, sizeof (call.rmpp));

    call_result = vs_mad->ib_vendor_call_via(vsmad_data, &vs_mad->portid, &call, vs_mad->srcport);
    if (!call_result) {
        return -1;
    }

    int i;
    for (i = 0; i < IB_VENDOR_RANGE1_DATA_SIZE/4; i++) {
        vsmad_data[i] = __be32_to_cpu(vsmad_data[i]);
    }
    return ME_OK;
}

int mib_get_general_info_gmp(mfile *mf, u_int32_t *vsmad_data, size_t vsmad_data_len)
{
    return mib_get_gmp(mf, IB_VS_ATTR_GENERAL_INFO, 0, vsmad_data, vsmad_data_len);
}

int mib_supports_reg_access_gmp(mfile *mf, maccess_reg_method_t reg_method)
{
    if (!mf || !mf->ctx) {
        return 0;
    }

    if (!((mf->flags & MDEVS_IB) && (((ibvs_mad *)(mf->ctx))->dest_type == IB_DEST_LID) &&
            (reg_method == MACCESS_REG_METHOD_GET))) {
        return 0;
    }

    u_int32_t vsmad_data[IB_VENDOR_RANGE1_DATA_SIZE/4] = {0};
    if (mib_get_general_info_gmp(mf, vsmad_data, IB_VENDOR_RANGE1_DATA_SIZE/4)) {
        return 0;
    }

    // vend_key 0x8 bytes, which present in any vendor specific MAD return in vsmad_data.
    // We want to skip them when relating GeneralInfo MAD fields in specific.
    // The capability_mask offset which is 0x80, is calculated from the beginning of GeneralInfo MAD fields.
    // So overall we have an offset of 0x8+0x80 bytes.
    const int capability_mask_byte_offset = 0x8+0x80;
    const int is_access_register_supported_bit_offset = 20;
    return EXTRACT(vsmad_data[capability_mask_byte_offset/4], is_access_register_supported_bit_offset, 1);
}

int mib_acces_reg_mad(mfile *mf, u_int8_t *data)
{
    if (!mf || !mf->ctx || !data) {
        IBERROR(("mib_acces_reg_mad failed. Null Param."));
        return ME_BAD_PARAMS;
    }
    u_int8_t *p;
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);
    int status = -1;

    // Set the MKey.
    set_mkey_for_smp_mad(h);

    // Call smp set function
    if (h->smp_set_status_via) {
        p = h->smp_set_status_via(data, &(h->portid), IB_SMP_ATTR_REG_ACCESS, 0, 0, &status, h->srcport);
    } else {
        p = h->smp_set_via(data, &(h->portid), IB_SMP_ATTR_REG_ACCESS, 0, 0, h->srcport);
    }
    if (!p || status > 0) {
        if (status != -1) {
            return mib_status_translate(status);
        } else {
            return -1;
        }
    }

    return ME_OK;
}

int mib_smp_set(mfile *mf, u_int8_t *data, u_int16_t attr_id, u_int32_t attr_mod)
{
    if (!mf || !mf->ctx || !data) {
        IBERROR(("mib_smp_set failed. Null Param."));
        return ME_BAD_PARAMS;
    }
    u_int8_t *p;
    int status = -1;
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);

    // Set the MKey.
    set_mkey_for_smp_mad(h);

    // Call smp set function
    if (h->smp_set_status_via) {
        p = h->smp_set_status_via(data, &(h->portid), attr_id, attr_mod, 0, &status, h->srcport);
    } else {
        p = h->smp_set_via(data, &(h->portid), attr_id, attr_mod, 0, h->srcport);
    }
    if (!p || status > 0) {
        if (status != -1) {
            return mib_status_translate(status);
        } else {
            return -1;
        }
    }

    return ME_OK;
}

int mib_smp_get(mfile *mf, u_int8_t *data, u_int16_t attr_id, u_int32_t attr_mod)
{
    if (!mf || !mf->ctx || !data) {
        IBERROR(("mib_smp_get failed. Null Param."));
        return ME_BAD_PARAMS;
    }
    u_int8_t *p;
    int status = -1;
    ibvs_mad *h = (ibvs_mad*)(mf->ctx);

    // Set the MKey.
    set_mkey_for_smp_mad(h);

    // Call smp set function
    if (h->smp_query_status_via) {
        p = h->smp_query_status_via(data, &(h->portid), attr_id, attr_mod, 0, &status, h->srcport);
    } else {
        p = h->smp_query_via(data, &(h->portid), attr_id, attr_mod, 0, h->srcport);
    }

    if (!p || status > 0) {
        if (status != -1) {
            return mib_status_translate(status);
        } else {
            return -1;
        }
    }

    return ME_OK;
}

int mib_semaphore_lock_smp(mfile *mf, u_int8_t *data, sem_lock_method_t method)
{
    if (!mf || !mf->ctx || !data) {
        IBERROR(("mib_semaphore_lock_smp failed. Null Param."));
        return ME_BAD_PARAMS;
    }
    u_int8_t *smp_result;
    int status = -1;
    ibvs_mad *vs_mad = (ibvs_mad*)(mf->ctx);

    // Setting MKey for this attribute caused MAD failures
    // and was disabled.

    if (method == SEM_LOCK_SET) {
        if (vs_mad->smp_set_status_via) {
            smp_result = vs_mad->smp_set_status_via(data, &(vs_mad->portid), SMP_SEMAPHOE_LOCK_CMD, 0, 0, &status, vs_mad->srcport);
        } else {
            smp_result = vs_mad->smp_set_via(data, &(vs_mad->portid), SMP_SEMAPHOE_LOCK_CMD, 0, 0, vs_mad->srcport);
        }
    } else {
        if (vs_mad->smp_query_status_via) {
            smp_result = vs_mad->smp_query_status_via(data, &(vs_mad->portid), SMP_SEMAPHOE_LOCK_CMD, 0, 0, &status, vs_mad->srcport);
        } else {
            smp_result = vs_mad->smp_query_via(data, &(vs_mad->portid), SMP_SEMAPHOE_LOCK_CMD, 0, 0, vs_mad->srcport);
        }
    }


    if (!smp_result || status > 0) {
        if (status != -1) {
            return mib_status_translate(status);
        } else {
            return -1;
        }
    }

    return ME_OK;
}

int mib_supports_reg_access_cls_a(mfile *mf, maccess_reg_method_t reg_method)
{
    if (!mf || !mf->ctx) {
        return 0;
    }

    if (!((mf->flags & MDEVS_IB) &&
         (((ibvs_mad *)(mf->ctx))->dest_type == IB_DEST_LID) &&
         (reg_method == MACCESS_REG_METHOD_SET || reg_method == MACCESS_REG_METHOD_GET))) {
        return 0;
    }

    u_int32_t vsmad_data[IB_VENDOR_RANGE1_DATA_SIZE/4] = {0};
    if (mib_get_general_info_gmp(mf, vsmad_data, IB_VENDOR_RANGE1_DATA_SIZE/4)) {
        return 0;
    }

    // vend_key 0x8 bytes, which present in any vendor specific MAD return in vsmad_data.
    // We want to skip them when relating GeneralInfo MAD fields in specific.
    // The capability_mask offset which is 0x80, is calculated from the beginning of GeneralInfo MAD fields.
    // So overall we have an offset of 0x8+0x80 bytes.
    const int capability_mask_byte_offset = 0x8+0x80;
    const int is_access_register_supported_bit_offset = 20;
    const int is_supported = EXTRACT(vsmad_data[capability_mask_byte_offset/4], is_access_register_supported_bit_offset, 1);
    return is_supported;
}
