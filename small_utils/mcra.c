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
/*
 *
 *  mcra.c - Mellanox Configuratio Register Access tool
 *
 */

#include "mtcr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ONES32(size)                    ((size)?(0xffffffff>>(32-(size))):0)
#define MASK32(offset,size)             (ONES32(size)<<(offset))

#define EXTRACT_C(source,offset,size)   ((((unsigned)(source))>>(offset)) & ONES32(size))
#define EXTRACT(src,start,len)          (((len)==32)?(src):EXTRACT_C(src,start,len))

#define MERGE_C(rsrc1,rsrc2,start,len)  ((((rsrc2)<<(start)) & (MASK32((start),(len)))) | ((rsrc1) & (~MASK32((start),(len)))))
#define MERGE(rsrc1,rsrc2,start,len)    (((len)==32)?(rsrc2):MERGE_C(rsrc1,rsrc2,start,len))

															 

void usage(const char *n)
{
    printf("  Mellanox Configuration Registers Access tool\n");
    printf("  Usage: %s  <device> <addr[.<bit offset>:<bit size>]> [data]\n", n);
    printf("         If data is given, operation is write. Otherwise it is read.\n");
    printf("         If a bit range is given in the address (E.G.: 0xf0014.16:8):.\n");
    printf("              For read  - Only the requested bits are printed.\n");
    printf("              For write - Read-Modify-Write. Only the requested bits are changed.\n");
    exit(1);
}

int main(int ac, char *av[])
{
    char*         endp;
    char*         dev = NULL;
    int           rc=0;
    unsigned int  addr = 0, val = 0;
    mfile         *mf;
    unsigned int  i2c_slave = 0;
    int           ap = 1;
    int           read_op = 0;
	int           bit_offs = 0;
	int           bit_size = 32;
    char*         op_name = "cr write";

#if 0
    int  i, rc1;
    char buf[1024], *p=buf;
    rc1 = mdevices(buf, 1024);
    for (i=0; i<rc1; i++)
    {
        printf("Found: \"%s\"\n", p);
        p += strlen(p)+1;
    }
    exit(0);
#endif

    // Parse cmd line:
    if (ac < 3 || ac > 6)
        usage(av[0]);

    // I2c slave stuff
    if (av[1][0] == '-') {
        if (!strcmp(av[1], "-s")) {
            i2c_slave  = strtoul(av[2], &endp, 0);
            if (*endp || i2c_slave == 0 || i2c_slave > 0x7f) {
                fprintf(stderr, "-E- Bad slave address given (%s). Expecting a number [0x1 .. 0x7f]\n", av[2]);
                exit(1);
            } 
            ap = 3;
        }else {
            fprintf(stderr, "-E- Unknown flag \"%s\"\n", av[2]);
            exit(1);
        }
    }

    if (ap >= ac) {
        fprintf(stderr, "-E- Missing device argument\n");
        exit(1);
    } else {
        dev = av[ap];
        ap++;
    }

    if (ap >= ac) {
        fprintf(stderr, "-E- Missing address argument\n");
        exit(1);
    } else {
        addr = strtoul(av[ap], &endp, 0);
		if (*endp != '\0' && *endp != '.') {
			fprintf(stderr, "-E- Bad address given (%s). Unparsed string: \"%s\"\n", av[ap] ,endp);
			exit(1);
		}
		
		if (*endp == '.') {
			bit_offs = strtoul(endp+1, &endp, 0);
			if ((*endp != '\0' && *endp != ':') || bit_offs >= 32) {
				fprintf(stderr, "-E- Bad bit offset in given address (%s). Unparsed string: \"%s\"\n", av[ap] ,endp);
				exit(1);
			}
		}

		if (*endp == ':') {
			bit_size = strtoul(endp+1, &endp, 0);
			if (*endp != '\0') {
				fprintf(stderr, "-E- Bad bit size in given address (%s). Unparsed string: \"%s\"\n", av[ap] ,endp);
				exit(1);
			}

			if (bit_size + bit_offs > 32) {
				fprintf(stderr, "-E- Bad bit offset/size in given address (%s) - exceeds 32 bits\n", av[ap]);
				
				exit(1);
			}
		}  
		
		if (*endp) {
			fprintf(stderr, "-E- Bad address given (%s). Unparsed string: \"%s\"\n", av[ap] ,endp);
			exit(1);
		}
		
		// Allow the bit_size to be ommited 
		if (bit_size + bit_offs > 32)
			bit_size = 32 - bit_offs;
		
        ap++;
    }

    if (ap >= ac) {
        read_op = 1;
        op_name = "cr read";
    } else {
        val = strtoul(av[ap], &endp, 0);
        if (*endp) {
            fprintf(stderr, "-E- Bad data given (%s)\n", av[ap]);
            exit(1);
        }
        ap++;
    }

    if (ap < ac) {
        fprintf(stderr, "-E- Extra argument given (%s)\n", av[ap]);
        exit(1);
    }


    // Do the job
    mf = mopen(dev);
    if (!mf)
    {
        perror("mopen");
        return 1;
    }

    //if (i2c_slave)
    //    mset_i2c_slave(mf, (u_int8_t)i2c_slave);

    if (read_op) {
        rc = mread4(mf, addr, &val);
		val = EXTRACT(val, bit_offs, bit_size);
    } else {
		if (bit_offs != 0 || bit_size != 32) {
			// read-modify-write
			u_int32_t tmp_val;
			rc = mread4(mf, addr, &tmp_val);
			if (rc != 4) {
				perror(op_name);
				exit(1);
			}

			val = MERGE(tmp_val, val, bit_offs, bit_size);
		}
        rc = mwrite4(mf, addr, val);
    }

    if (rc != 4) {
        perror(op_name);
    } else {
        if (read_op)
            printf("0x%08x\n", val);

        rc = 0;
    }

    mclose(mf);
    return rc;
}

