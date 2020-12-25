/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

#define UNSUPP_DEVS_NUM   15
#define DEVID_ADDRESS     0xf0014

// Convert BYTES - DWORDS with MEMCPY BE
#define BYTES_TO_DWORD_BE(dw_dest, byte_src) do {   u_int32_t tmp; \
                                                    memcpy(&tmp, byte_src, 4); \
                                                    *(dw_dest) = __be32_to_cpu(tmp); \
} while (0)

#define DWORD_TO_BYTES_BE(bytes_dest, dw_src) do { u_int32_t tmp; \
                                                   tmp = __cpu_to_be32(*(dw_src)); \
                                                   memcpy(bytes_dest, &tmp, 4); \
} while (0)


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

typedef void IBMAD_CALL_CONV (*f_mad_rpc_set_retries)(struct ibmad_port *port, int retries);
typedef void IBMAD_CALL_CONV (*f_mad_rpc_set_timeout)(struct ibmad_port *port, int timeout);
typedef uint32_t IBMAD_CALL_CONV (*f_mad_get_field)(void *buf, int base_offs, enum MAD_FIELDS field);

typedef char*IBMAD_CALL_CONV (*f_portid2str)(ib_portid_t *portid);


struct __ibvsmad_hndl_t
{
    struct ibmad_port *srcport;

    ib_portid_t portid;
    int sock;
    int tp;
    int i2c_slave;
    int use_smp;

    int timeout;
    int retries_num;
    u_int64_t vkey;
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
    f_mad_get_field mad_get_field;
    f_portid2str portid2str;

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

static uint64_t ibvsmad_craccess_rw_smp(ibvs_mad *h, u_int32_t memory_address, int method, u_int8_t num_of_dwords, u_int32_t *data)
{
    u_int8_t mad_data[IB_SMP_DATA_SIZE] = {0};
    int i;
    u_int32_t att_mod = 0;
    u_int8_t *p;
    u_int64_t vkey;

    if (num_of_dwords > MAX_IB_SMP_DATA_DW_NUM) {
        IBERROR(("size is too big, maximum number of dwords is %d", MAX_IB_SMP_DATA_DW_NUM));
        return BAD_RET_VAL;
    }
    // Mode 0 - block write
    // att_mod = MERGE(att_mod, 0, 22, 2); // commented - already 0

    // Cr addr:
    att_mod = MERGE(att_mod, memory_address, 0, 16);
    att_mod = MERGE(att_mod, EXTRACT(memory_address, 16, 8), 24, 8);

    // Set the vkey
    vkey = __cpu_to_be64(h->vkey);
    memcpy(&mad_data[0], &vkey, 8);

    // DW Size:
    att_mod = MERGE(att_mod, num_of_dwords, 16, 6);

    if (method == IB_MAD_METHOD_GET) {
        p = h->smp_query_via(mad_data, &h->portid, IB_SMP_ATTR_CR_ACCESS, att_mod, 0, h->srcport);

        if (!p) {
            return BAD_RET_VAL;
        }

        for (i = 0; i < num_of_dwords; i++) {
            BYTES_TO_DWORD_BE(data + i, mad_data + IB_DATA_INDEX + i * 4);
        }
    } else {
        for (i = 0; i < num_of_dwords; i++) {
            DWORD_TO_BYTES_BE(mad_data + IB_DATA_INDEX + i * 4, data + i);
        }
        p = h->smp_set_via(mad_data, &h->portid, IB_SMP_ATTR_CR_ACCESS, att_mod, 0, h->srcport);
        if (!p) {
            return BAD_RET_VAL;
        }
    }

    return 0;
}

// TODO: Correct this value.
#define  MAX_VS_DATA_SIZE (IB_VENDOR_RANGE1_DATA_SIZE -  IB_DATA_INDEX)
#define  MAX_IB_VS_DATA_DW_NUM  MAX_VS_DATA_SIZE / 4

static uint64_t ibvsmad_craccess_rw_vs(ibvs_mad *h, u_int32_t memory_address, int method, u_int8_t num_of_dwords, u_int32_t *data)
{
    u_int8_t vsmad_data[IB_VENDOR_RANGE1_DATA_SIZE] = {0};
    ib_vendor_call_t call;
    int i;
    u_int8_t *p;
    u_int64_t vkey;

    call.method     = method;
    call.mgmt_class = IB_VENDOR_SPECIFIC_CLASS_0x9;
    call.attrid     = IB_VS_ATTR_CR_ACCESS;

    if (h == NULL || data == NULL) {
        return BAD_RET_VAL;
    }

    if (num_of_dwords > MAX_IB_VS_DATA_DW_NUM) {
        IBERROR(("size (%d) is too big, maximum num of dwords is %d", num_of_dwords,
                 MAX_IB_VS_DATA_DW_NUM)); // TBD try max size
        return BAD_RET_VAL;
    }

    // TODO: Add the dword.
    call.mod        = ( (EXTRACT(memory_address, 0, 16) << 00) & 0x0000ffff ) |
                      ( (num_of_dwords << 16) & 0x00ff0000 ) |
                      ( (EXTRACT(memory_address, 16, 8) << 24) & 0xff000000 );

    DEBUG(("attrmod = %08x\n", call.mod));

    call.oui        = IB_OPENIB_OUI;
    call.timeout    = 0;
    memset(&call.rmpp, 0, sizeof(call.rmpp));

    DEBUG(("memory_address = 0x%08x\n", memory_address));
    /* set MAD data section */

    // TBD: currently work for 1 record only, fix for more than one.
    // building one record:

    // Set the Vkey.
    vkey = __cpu_to_be64(h->vkey);
    memcpy(vsmad_data, &vkey, 8);

    if (method == IB_MAD_METHOD_SET) {
        for (i = 0; i < num_of_dwords; i++) {
            DWORD_TO_BYTES_BE(vsmad_data + IB_DATA_INDEX + i * 4, data + i);
        }
    }

    p = h->ib_vendor_call_via(vsmad_data, &h->portid, &call, h->srcport);
    if (!p) {
        return BAD_RET_VAL;
    }

    for (i = 0; i < num_of_dwords; i++) {
        BYTES_TO_DWORD_BE(data + i, vsmad_data + IB_DATA_INDEX + i * 4);
    }

    return 0;
}

static uint64_t ibvsmad_craccess_rw(ibvs_mad *h, u_int32_t memory_address, int method, u_int8_t num_of_dwords, u_int32_t *data)
{
    if (h->use_smp) {
        return ibvsmad_craccess_rw_smp(h, memory_address, method, num_of_dwords, data);
    } else {
        return ibvsmad_craccess_rw_vs(h, memory_address, method, num_of_dwords, data);
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
        MY_GetProcAddress(ivm, portid2str               );
        MY_GetProcAddress(ivm, mad_get_field            );
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
    MY_DLSYM(ivm, mad_get_field            );
    MY_DLSYM(ivm, portid2str               );
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
    get_64_env_var(MTCR_IB_VKEY, &((ivm->vkey)));
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
    uint64_t ret = ibvsmad_craccess_rw_vs(h, DEVID_ADDRESS, IB_MAD_METHOD_GET, 1, &data);
    if (!ret) {
        return 1;
    }
    DEBUG(("Vendor Specific is not supported, checking SMP .. "));
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


/********************************************************
**
*    Initialize madrpc; Register the vendor specific management classes under
*    the libibmad library; Resolve destination lid from input.
*
*/
int mib_open(const char *name, mfile *mf, int mad_init)
{
    char        *ca              = 0;
    int mgmt_classes[4] = {IB_SMI_CLASS,
                           IB_SMI_DIRECT_CLASS,
                           IB_VENDOR_SPECIFIC_CLASS_0xA,
                           IB_VENDOR_SPECIFIC_CLASS_0x9};
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

    if (strncmp("ibdr-", nbuf, 5) == 0) {
        ivm->use_smp = 1;
        ivm->dest_type = IB_DEST_DRPATH;
        path_str  = nbuf + 5;
    } else if (strncmp("iblid-", nbuf, 6) == 0) {
        ivm->use_smp = 1;
        ivm->dest_type = IB_DEST_LID;
        path_str  = nbuf + 6;
    } else if ((p = strstr(nbuf, "lid-")) != 0) {
        lid_provided = 1;
        ivm->dest_type = IB_DEST_LID;
        path_str  = p + 4;

    } else if ((p = strstr(nbuf, "lid_noinit-")) != 0) {
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
#else
    if (process_dynamic_linking(ivm, mad_init) == -1) {
        goto end;
    }
#endif
    get_env_var(MTCR_IBMAD_DEBUG, ivm->ibdebug);

    ivm->srcport = ivm->mad_rpc_open_port(ca, ca_port, mgmt_classes, 4);
    if (ivm->srcport == NULL) {
        goto end;
    }

    ivm->mad_rpc_set_retries(ivm->srcport, ivm->retries_num);
    ivm->mad_rpc_set_timeout(ivm->srcport, ivm->timeout);

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
    int t_offset = 0;
    while (t_offset < length) {
        int left_size = length - t_offset;
        int to_op = left_size > chunk_size ? chunk_size : left_size;
        if (ibvsmad_craccess_rw(h, offset + t_offset, method, (to_op / 4), data + t_offset / 4) == ~0ull) {
            IBERROR(("cr access %s to %s failed", op == BLOCKOP_READ ? "read" : "write",
                     h->portid2str(&h->portid)));
            return -1;
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

int mib_send_gmp_access_reg_mad(mfile *mf, u_int32_t *data, u_int32_t reg_size, u_int32_t reg_id, maccess_reg_method_t reg_method)
{
    // The buffer should contain:
    // 2 dwords for the vkey,
    // 1 dword for a configuration dword,
    // 55 dwords for data.
    // All sizes and offsets are in dword unit.
    const int vkey_offset = 0;
    const int vkey_size = 2;
    const int config_offset = 2;
    const int config_size = 1;
    const int data_offset = 3;
    const int data_size = 55;
    const int buffer_size = vkey_size + config_size + data_size; // == 58
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
    u_int64_t vkey = __cpu_to_be64(vsmad->vkey);
    memcpy(&vsmad_data[vkey_offset], &vkey, vkey_size * 4);
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

    for (block_num = 0; block_num < num_of_blocks; block_num++) {
        block_dword = __cpu_to_be32(((u_int32_t)block_num) << 16); //block offset in the config dword, see PRM for details
        memcpy(&vsmad_data[config_offset], &block_dword, config_size * 4);
        call_result = vsmad->ib_vendor_call_via(vsmad_data, &vsmad->portid, &call, vsmad->srcport);
        if (!call_result) {
            return -1;
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

int mib_supports_reg_access_cls_a(mfile *mf, maccess_reg_method_t reg_method)
{
    if (!mf || !mf->ctx) {
        return 0;
    }

    if (!((mf->flags & MDEVS_IB) && (((ibvs_mad *)(mf->ctx))->dest_type == IB_DEST_LID) && (reg_method == MACCESS_REG_METHOD_GET ||
             reg_method == MACCESS_REG_METHOD_SET))) {
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
