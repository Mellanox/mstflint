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
 */

#include <crdump.h>
#include <dev_mgt/tools_dev_types.h>
#include <common/tools_version.h>
#include <common/bit_slice.h>


#define CAUSE_FLAG "--cause"

// string explaining the cmd-line structure
char correct_cmdline[] = "   Mellanox mstdump utility, dumps device internal configuration data\n\
   Usage: mstdump [-full] <device> [i2c-slave] [-v[ersion] [-h[elp]]]\n\n\
   -full              :  Dump more expanded list of addresses\n\
                         Note : be careful when using this flag, None safe addresses might be read.\n\
   -v                 :  Display version info\n\
   -h                 :  Print this help message\n\
   Example :\n\
            mstdump /dev/mst/mt4099_pci_cr0\n";


void print_dword(crd_dword_t *dword) {
    printf("0x%8.8x 0x%8.8x\n", dword->addr, dword->data);
}

int main(int argc, char** argv) {
    int i ;
    mfile *mf;
    int rc;
    int full = 0;
    int cause_addr = -1, cause_off = -1;

    if (argc < 2 || argc > 4) {
        fprintf(stderr, "%s", correct_cmdline);
        return 2;
    }

    for (i = 1; i < argc; ++i) {
        /* check position-independent flags */
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "-help")) {
            fprintf(stderr, "%s", correct_cmdline);
            exit (0);
        }
        else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "-version")) {
            print_version_string("mstdump", "");
            exit(0);
        }
        else if (!strncmp(argv[i], CAUSE_FLAG, strlen(CAUSE_FLAG))) {
            if (sscanf(argv[i], CAUSE_FLAG"=%i.%d", &cause_addr, &cause_off) != 2) {
                fprintf(stderr, "Invalid parameters to " CAUSE_FLAG " flag\n");
                exit(1);
            }
            if (cause_addr < 0 || cause_off < 0) {
                fprintf(stderr, "Parameters to " CAUSE_FLAG " flag must be non-negative values\n");
                exit(1);
            }
        }
    }

    i = 1;  // i points to the current command line argument

    if (i < argc && !strcasecmp(argv[i], "-full")) {
        full = 1;
        ++i;
    }

    if (i >= argc || !( mf=mopen(argv[i]) )) {
        fprintf(stderr, "Unable to open device %s. Exiting.\n",
                (i < argc) ? argv[i] : "(not specified in command line)");
        return 1;
    }
    ++i;    // move past the device parameter

    if (i < argc) {
        mset_i2c_slave(mf, (u_int8_t)strtoul(argv[i], 0, 0));
    }

    rc = CRD_OK;
    crd_ctxt_t *context;

    rc = crd_init(&context, mf, full, cause_addr, cause_off);
    if (rc) {
        mclose(mf);
        goto error;
    }

    //printf("Number of blocks : 0x%d\n",(context)->block_count);
    u_int32_t arr_size = 0;
    rc = crd_get_dword_num(context, &arr_size);
    if (rc) {
        crd_free(context);
        mclose(mf);
        goto error;
    }

    rc = crd_dump_data(context, NULL, print_dword);
    if (rc) {
        crd_free(context);
        mclose(mf);
        goto error;
    }
    crd_free(context);
    mclose(mf);
    return 0;

    error :
        printf("-E- %s\n", crd_err_str(rc));
        return rc;
}

