/*
 *
 * mstdump.c - crspace dump for Mellanox Technologies Devices.
 *
 * Copyright (c) 2005 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id: mstdump.c,v 1.9 2007-06-25 12:45:33 yoniy Exp $
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mtcr.h>


typedef struct address_range {
    int address;
    int length;
} address_range;

address_range MT25204_address_list[] = {
    #include "MT25204.crb"      // Sinai
};
address_range MT25208_address_list[] = {
    #include "MT25208.crb"      // Arbel
};
address_range MT23108_address_list[] = {
    #include "MT23108.crb"      // Tavor
};
address_range MT48436_address_list[] = {
    #include "MT48436.crb"      // Shaldag
};
address_range MT47396_address_list[] = {
    #include "MT47396.crb"      // Anafa2
};
address_range MT25408_address_list[] = {
    #include "MT25408.crb"      // Hermon A0
};
address_range MT25408B0_address_list[] = {
    #include "MT25408B0.crb"    // Hermon B0
};
address_range MT64102_address_list[] = {
    #include "MT64102.crb"      // Dolev
};
address_range MT64102safe_address_list[] = {
    #include "MT64102safe.crb"      // Dolev safe address list (should not cause cr-timeouts)
};


//Same as mread4 but prints out an error message if there's an error
#define MREAD4(mf,offs, val)  do { if (mread4 (mf, offs, val) != 4) { \
                                  fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), strerror(errno), (u_int32_t)errno); \
                                  exit(2); } \
                                  if (0) printf("R %06x:%08x\n", (u_int32_t)offs, (u_int32_t)*(val)); \
                                  } while (0)


/* set list and list_size parameters appropriate for given device.
 * it is important that this macro is called in a context where list
 * and list_size are defined.
 * also make sure that the address array for the device is named
 * <device>_address_list
 */
#define select_device(dev_name)                                                 \
  do {                                                                          \
    list=dev_name ## _address_list ;                                            \
    list_size=sizeof( dev_name ## _address_list ) / sizeof(address_range);      \
  } while (0)


// string explaining the cmd-line structure
char correct_cmdline[] = "[-full] <device> [i2c-slave]";

#if defined(__WIN__)
    #define strcasecmp    _stricmp
#endif


int main(int argc, char** argv)
{
    int i, j;
    mfile * f;
    unsigned dev_id=0x0, prev_id=0x0;
    unsigned rev_id;

    int list_size;
    address_range* list;
    int full = 0;

    if (argc < 2 || argc > 4) {
        fprintf(stderr,"Usage: %s %s.\n", argv[0], correct_cmdline);
        return 2;
    }

    i = 1;  // i points to the current command line argument

    if (i < argc && !strcasecmp(argv[i], "-full")) {
        full = 1;
        ++i;
    }

    if (i >= argc || !( f=mopen(argv[i]) )) {
        fprintf(stderr,"Unable to open device %s. Exiting.\n",
                (i < argc) ? argv[i] : "(not specified in command line)");
        return 1;
    }

    ++i;    // move past the device parameter

    //if (i < argc)
    //    mset_i2c_slave(f, (u_int8_t)strtoul(argv[i],0,0));

    MREAD4(f,0xF0014,&dev_id);
    rev_id = (dev_id & 0xFF0000) >> 16;     // mask out revision id
    dev_id &= 0xFFFF;                       // mask out device id

    //Figure out which device to use. Select the address list accordingly.
    switch (dev_id) {
        case 0x5e8c:
        case 0x6274:
            select_device(MT25204);
            break;
        case 0x6278:
            select_device(MT25208);
            break;
        case 0x5a44:
            select_device(MT23108);
            break;
        case 0x0190:
            switch (rev_id) {
                case 0xA0:
                    select_device(MT25408);
                    break;
                case 0xB0:
                    select_device(MT25408B0);
                    break;
                default:
                    fprintf(stderr,"Unexpected revision number. Device id: 0x%8.8x. Rev: 0x%2.2x. Exiting.\n",
                            dev_id, rev_id);
                    mclose(f);
                    return 1;
            }
            break;
        case 435:
            select_device(MT48436);
            break;
        case 0x17d4:
            if (full)
                select_device(MT64102);     // user wants full dump
            else
                select_device(MT64102safe); // make cautious dump
            break;
        default:
            // could still be InfiniScaleIII...
            prev_id = dev_id;
            MREAD4(f,0x60014,&dev_id);
            dev_id &= 0xFFFF;
            if (dev_id == 47396) {
                select_device(MT47396);
            } else {
                fprintf(stderr, "Unexpected device id: 0x%8.8x/0x%8.8x. Exiting.\n", prev_id, dev_id);
                mclose(f);
                return 1;
            }
    }

    for (i=0;i<list_size;++i) {
        unsigned data, address;
        for (j=list[i].length, address=list[i].address; j > 0; --j, address += 4) {
            MREAD4(f,address,&data);
            printf("0x%8.8x 0x%8.8x\n", address, data);
        }
    }

    mclose(f);
    return 0;
}

