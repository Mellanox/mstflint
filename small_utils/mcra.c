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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include "mtcr.h"
#include "tools_version.h"

#define ONES32(size)                    ((size)?(0xffffffff>>(32-(size))):0)
#define MASK32(offset,size)             (ONES32(size)<<(offset))

#define EXTRACT_C(source,offset,size)   ((((unsigned)(source))>>(offset)) & ONES32(size))
#define EXTRACT(src, start,len)          (((len)==32)?(src):EXTRACT_C(src,start,len))

#define MERGE_C(rsrc1,rsrc2,start,len)  ((((rsrc2)<<(start)) & (MASK32((start),(len)))) | ((rsrc1) & (~MASK32((start),(len)))))
#define MERGE(rsrc1,rsrc2,start,len)    (((len)==32)?(rsrc2):MERGE_C(rsrc1,rsrc2,start,len))

#define ADB_DUMP_VAR   "ADB_DUMP"


void usage(const char *n, int with_exit)
{
    printf("  Mellanox Configuration Registers Access tool\n");
    printf("  Usage: %s [-s <i2c-slave>] [-a <adb dump>] [-v] [-h] <device>\n", n);
    printf("         <addr[.<bit offset>:<bit size>]|[,<bytes number>]> [data]\n");
    printf("         If data is given, operation is write. Otherwise it is read.\n");
    printf("         If a bit range is given in the address (E.G.: 0xf0014.16:8):\n");
    printf("              For read  - Only the requested bits are printed.\n");
    printf("              For write - Read-Modify-Write. Only the requested bits are changed.\n");
    printf("         If 'bytes number' is given in the address (E.G.: 0xf0014,16):\n");
    printf("              For read  - Will read a block (its size is the given bytes number).\n");
    printf("              For write - User need to give list of dwrods to write, \n"
           "                          number of dwords should be (bytes number/4).\n\n");
    printf("  -s <i2c-slave> : I2C slave address.\n");
    printf("  -a <dump file> : adb dump file, used for access by path.\n");
    printf("  -h             : Print this help message.\n");
    printf("  -v             : Display version info\n");
    printf("\n");
    printf("Environment Variables:\n");
    printf("   ADB_DUMP      : Holds the path to adb dump, used for access by path (can be overriden by \"-a\").\n");
    if (with_exit) {
        exit(1);
    }
}
#define MCRA_TOOL_NAME "mcra"
#define MCRA_TOOL_VERSON "1.0.0"

int main(int argc, char *argv[])
{
    char*         endp;
    char*         dev = NULL;
    char*         adb_dump = NULL;
    char*         path = NULL;
    int           rc=0;
    unsigned int  addr = 0, val = 0;
    mfile         *mf;
    unsigned int  i2c_slave = 0;
    int           c;
    int           read_op = 0;
    int           bit_offs = 0;
    int           bit_size = 32;
    int           byte_size = 0;
    int           read_block = 0;       /* if 0 then read field according to "addr.bit:size", else read block of size "byte_size" */
    const char*   op_name = "cr write";

#if 0
    int  i, rc1;
    char buf[1024], *p=buf;
    rc1 = mdevices(buf, 1024);
    for (i=0; i<rc1; i++) {
        printf("Found: \"%s\"\n", p);
        p += strlen(p)+1;
    }
    exit(0);
#endif
    (void)rc; // avoid warnings (we dont use it just assign)
    // Parse cmd line:
    if (argc < 2) {
        usage(argv[0], 1);
    }

    while ((c = getopt(argc, argv, "s:a:hv")) != -1) {
        switch (c)  {
        case 's':
            i2c_slave  = strtoul(optarg, &endp, 0);
            if (*endp || i2c_slave == 0 || i2c_slave > 0x7f) {
                fprintf(stderr, "-E- Bad slave address given (%s). Expecting a number [0x1 .. 0x7f]\n", optarg);
                exit(1);
            }
            break;

        case 'a':
            adb_dump = optarg;
            break;

        case 'v':
            print_version_string(MCRA_TOOL_NAME, MCRA_TOOL_VERSON);
            exit(0);

        case 'h':
            usage(argv[0], 0);
            exit(0);

        case '?':
            break;

        default:
            fprintf(stderr, "-E- Unknown flag \"%c\"\n", c);
            exit(1);
        }
    }

    // parse non-optons argv elements
    if (optind >= argc) {
        fprintf(stderr, "-E- Missing device argument\n");
        exit(1);
    } else {
        dev = argv[optind];
        optind++;
    }

    if (optind >= argc) {
        fprintf(stderr, "-E- Missing address argument\n");
        exit(1);
    } else {
         addr = strtoul(argv[optind], &endp, 0);
         if (*endp != '\0' && *endp != '.' && *endp != ',') {
             //fprintf(stderr, "-E- Bad address given (%s). Unparsed string: \"%s\"\n", av[ap] ,endp);
             //exit(1);
             path = argv[optind];
         }

         if (*endp == ',') {
             if (path) {
                 fprintf(stderr, "-E- Can't read block with full path\n");
                 exit(1);
             }
             read_block = 1;
             byte_size = strtoul(endp+1, &endp, 0);

             if (*endp != '\0' || byte_size == 0)
             {
                 fprintf(stderr, "-E- Bad byte size in given address (%s). Unparsed string: \"%s\"\n", argv[optind] ,endp);
                 exit(1);
             }
         }

         if (*endp == '.') {
             if (path) {
                 fprintf(stderr, "-E- Full path with bit address notation is illegal\n");
                 exit(1);
             }

             bit_offs = strtoul(endp+1, &endp, 0);
             if ((*endp != '\0' && *endp != ':') || bit_offs >= 32) {
                 fprintf(stderr, "-E- Bad bit offset in given address (%s). Unparsed string: \"%s\"\n", argv[optind] ,endp);
                 exit(1);
             }
         }

         if (*endp == ':') {
             if (path) {
                 fprintf(stderr, "-E- Full path with bit size notation is illegal\n");
                 exit(1);
             }

             bit_size = strtoul(endp+1, &endp, 0);
             if (*endp != '\0') {
                 fprintf(stderr, "-E- Bad bit size in given address (%s). Unparsed string: \"%s\"\n", argv[optind] ,endp);
                 exit(1);
             }

             if (bit_size + bit_offs > 32) {
                 fprintf(stderr, "-E- Bad bit offset/size in given address (%s) - exceeds 32 bits\n", argv[optind]);

                 exit(1);
             }
         }

         if (!path && *endp) {
             fprintf(stderr, "-E- Bad address given (%s). Unparsed string: \"%s\"\n", argv[optind] ,endp);
             exit(1);
         }

         // Allow the bit_size to be ommited
         if (bit_size + bit_offs > 32)
             bit_size = 32 - bit_offs;

         optind++;
    }


    if (optind >= argc) {
        read_op = 1;
        op_name = "cr read";
    } else {
        val = strtoul(argv[optind], &endp, 0);
        if (*endp) {
            fprintf(stderr, "-E- Bad data given (%s)\n", argv[optind]);
            exit(1);
        }
        optind++;
    }

    if (optind < argc) {
        fprintf(stderr, "-E- Extra argument given (%s)\n", argv[optind]);
        exit(1);
    }

    if (!adb_dump) {
        adb_dump = getenv(ADB_DUMP_VAR);
    }

    // Do the job
    mf = mopen(dev);
    if (!mf) {
        perror("mopen");
        return 1;
    }

    if (i2c_slave)
        mset_i2c_slave(mf, (u_int8_t)i2c_slave);

    if (path) {
        FILE* fp;
        char* fpath;
        char line[1024];
        char *offset, *size;
        int path_found = 0;

        if (!adb_dump) {
            fprintf(stderr, "-E- Can't access by path without providing adb dump file path\n");
            goto error;
        }

        fp = fopen(adb_dump, "r");
        if (!fp) {
            fprintf(stderr, "-E- Can't open adb dump (%s) file: %s\n", adb_dump, strerror(errno));
            goto error;
        }

        while (fgets(line, sizeof(line), fp) != NULL) {
            if (!strstr(line, path)) {
                continue;
            }

            fpath = strtok(line, " ");

            if (strcmp(fpath, path)) {
                continue;
            }

            if (!fpath) {
                fprintf(stderr, "-E- Bad register map file format (%s), Can't find path\n", line);
                fclose(fp);
                goto error;
            }

            offset = strtok(NULL, " ");
            size = strtok(NULL, " ");

            if (!offset || !size) {
                fprintf(stderr, "-E- Bad register map file format (%s), Can't find offset/size\n", line);
                fclose(fp);
                goto error;
            }
            path_found = 1;

            if (sscanf(offset, "0x%x.%d", &addr, &bit_offs) != 2) {
                if (sscanf(offset, "0x%x", &addr) != 1) {
                    fprintf(stderr, "-E- Bad offset format in adb dump file, offset=%s\n", offset);
                    fclose(fp);
                    goto error;
                }

                bit_offs = 0;
            }

            if (sscanf(size, "%d", &bit_size) != 1) {
                fprintf(stderr, "-E- Bad size format in adb dump file, size=%s\n", size);
                fclose(fp);
                goto error;
            }

            break;
        }

        fclose(fp);
        if (!path_found) {
            fprintf(stderr, "-E- Can't find path (%s)\n", path);
            goto error;
        }
    }

    if (read_op) {
        if (read_block) {
            int i;
            int dowrd_size = ((byte_size - 1)/4) + 1;
            u_int32_t* data = malloc(sizeof(u_int32_t)*dowrd_size);

            if (!data) {
                fprintf(stderr, "-E- Failed to allocate memmory for read block buffer\n");
            }

            addr = (addr >> 2) << 2;
            if (mread4_block(mf, addr, data, dowrd_size*4) != dowrd_size*4)
                goto access_error;

            // print the dowrds
            for (i = 0; i < dowrd_size; i++) {
                printf("0x%08x 0x%08x\n", addr + i*4, data[i]);
            }
        } else {
            if (mread4(mf, addr, &val) != 4)
                goto access_error;

            val = EXTRACT(val, bit_offs, bit_size);
            printf("0x%08x\n", val);
        }
    } else {
        if (read_block) {
            fprintf(stderr, "-E- Writing blocks is not supported yet\n");
            exit(1);
        }

        if (bit_offs != 0 || bit_size != 32) {
            // read-modify-write
            u_int32_t tmp_val;
            if (mread4(mf, addr, &tmp_val) != 4)
                goto access_error;

            val = MERGE(tmp_val, val, bit_offs, bit_size);
        }
        if(mwrite4(mf, addr, val) != 4) {
            goto access_error;
        }
    }
    goto success;

access_error:
    perror(op_name);

error:
    mclose(mf);
    return 1;

success:
    mclose(mf);
    return 0;
}

