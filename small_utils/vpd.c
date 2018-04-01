/*
 *
 *  vpd.c - PCI VPD (Vital Product Data) parser
 *
 * Author: Michael S. Tsirkin <mst@mellanox.co.il>
 *
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


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
#include <ctype.h>

#include "tools_version.h"
#include "mvpd/mvpd.h"


static clock_t timeout_t = 5; // Just for compatibility, no meaning

#define VPD_MAX_SIZE 4096
#define VPD_TOOL_VERSON "2.0.0"

typedef unsigned char vpd_t[VPD_MAX_SIZE];

void print_field(char* key, char* val)
{
    if (strcmp(key, "RV") == 0) {
        return;
    } else if (strlen(val)) {
        printf("%s:      %s\n", key, val);
    }
}

void print_bin_field(char* key, char* val) {
    char* valTmp = malloc((strlen(val) * 2 + 1) * sizeof(char));
    if (!valTmp) {
        printf("-E- Failed to Allocate Memory");
        return;
    }
    memset(valTmp, 0, (strlen(val) * 2 + 1) * sizeof(char));
    int i = 0;
    while (val[i] != '\0') {
        sprintf(valTmp + i * 2, "%02x", (u_int8_t)val[i]);
        i++;
    }
    printf("%s(BIN): %s\n", key, valTmp);
    free(valTmp);
}

int is_printable(char* value){
    int i = 0;
    while (value[i] != '\0') {
        if (isprint(value[i])) {
            i++;
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

//If you want to print all, pass NULL keyword
void find_and_print_vpd_data(vpd_result_t* vpd_data, vpd_tags_type_t vpd_type, const char *keyword)
{
    if (vpd_type & VPD_RO) {
        int i;
        if ( !keyword || strcmp(keyword, "ID") == 0) {
            print_field("ID", vpd_data->id.data);
            if (keyword) {
                return;
            }
        }
        for (i = 0; i < vpd_data->ro_fields_size; i++) {
            if (!keyword || strcmp(vpd_data->ro_fields[i].id, keyword) == 0) {
                print_field(vpd_data->ro_fields[i].id, vpd_data->ro_fields[i].data);
                if (keyword) {
                    return;
                }
            }
        }
    }
    if (vpd_type & VPD_RW) {
        int i;
        for (i = 0; i < vpd_data->rw_fields_size; i++) {
            if (!keyword || strcmp(vpd_data->rw_fields[i].id, keyword) == 0) {
                if (is_printable(vpd_data->rw_fields[i].data) == 1) {
                    print_field(vpd_data->rw_fields[i].id, vpd_data->rw_fields[i].data);
                } else {
                    print_bin_field(vpd_data->rw_fields[i].id, vpd_data->rw_fields[i].data);
                }
                if (keyword) {
                    return;
                }
            }
        }
    }
}


int main(int argc, char **argv)
{
	const char *name;
	char* endptr;
	int i;
	int rc = 0;
	vpd_t d;
	int m = 0;
	int n = 0;
	int strict = 0;
	mfile *mf;
	vpd_result_t *read_result;
	vpd_tags_type_t read_type = VPD_ALL;

	if (argc < 2) {
		rc = 1;
		goto usage;
	}

	do
	{
		i=getopt(argc, argv, "mvhnsrt:");
		if (i<0) {
			break;
		}

		switch (i) {
			case 'm':
				m=1;
				break;
			case 'n':
				n=1;
				break;
            case 's':
                strict = 1;
                break;
			case 'h':
			    rc = 0;
			    goto usage;
			case 'v':
                print_version_string("mstvpd", VPD_TOOL_VERSON);
                exit(0);
			case 'r':
				read_type = VPD_RO;
				break;
			case 't':
				timeout_t = strtol(optarg, &endptr, 0);
				if (*endptr != '\0') {
				    fprintf(stderr, "-E- Invalid timeout argument: %s.\n",  optarg);
				    return 1;
				}
				if ( timeout_t <= 0 ) {
				    fprintf(stderr, "-E- Wrong timeout, it should be > 0 !\n");
				    return 1;
				}
				break;
			default:
			    rc = 1;
				goto usage;
		}
	} while (1 == 1);
				
	name = argv[optind];
	argc -= optind;
	argv += optind;
	if (name == NULL) {
	    fprintf(stderr, "-E- Missing <file> argument !\n");
	    return 33;
	}
	if (! strcmp("-", name)) {
		if (fread(d, VPD_MAX_SIZE, 1, stdin) != 1)
			return 3;
	} else {
	    mf = mopen(name);
	    if (!mf) {
            fprintf(stderr, "-E- Failed to open device %s!\n", name);
            return MVPD_BAD_PARAMS;
	    }
	    int mvpd_len = VPD_MAX_SIZE;
	    rc = mvpd_get_vpd_size(mf, &mvpd_len);
        if (rc != 0) {
            fprintf(stderr, "-E- Failed to get VPD size from %s!\n", name);
            return MVPD_ERR;
        }
		rc = mvpd_get_raw_vpd(mf, (u_int8_t *)d, mvpd_len);
	    if (rc) {
	        fprintf(stderr, "-E- Failed to read VPD from %s!\n", name);
	        return MVPD_ERR;
	    }
	}

	if (m) {
		return fwrite(d, VPD_MAX_SIZE, 1, stdout) != 1;
	}
	rc = mvpd_parse_adv((u_int8_t *)d, VPD_MAX_SIZE, &read_result, read_type, strict, !n);
	if (rc) {
        fprintf(stderr, "-E- Failed to parse VPD from %s!\n", name);
        return MVPD_ERR;
	}
	if (argc == 1) {
	    find_and_print_vpd_data(read_result, read_type, NULL);
	} else {
		for (i = 0; i < argc - 1; ++i) {
			if (!strcmp(argv[i + 1], "--"))
			    continue;
			find_and_print_vpd_data(read_result, read_type, argv[i + 1]);
		}
	}
	if (read_result) {
	    mvpd_result_free(read_result);
	}
	return 0;

usage:
	printf("Usage: %s [-m|-n] [-t ##] <file> [-- keyword ...]\n", argv[0]);
	printf("-h\tPrint this help.\n");
	printf("-v\tPrint tool version.\n");
	printf("-m\tDump raw VPD data to stdout.\n");
	printf("-n\tDo not validate check sum.\n");
	printf("-r\tDo not check and display the VPD_W tag in the vpd data.\n");
	printf("-t ##\tTime out after ## seconds. (Default is 30.)\n\n");  // Currently ignored - for compatibility
	// We have also "-s" ("s" for "strict"), which is a hidden flag used by production.
	// There are cards out there with inconsistent format, ~200K cards,
    // which will cause the tool to fail if this flag is specified.
	printf("file\tThe PCI id number of the HCA (for example, \"2:00.0\"),\n");
	printf("\tthe device name (such as \"mlx4_0\")\n");
	printf("\tthe absolute path to the device (\"/sys/class/infiniband/mlx4_0/device\")\n");
	printf("\tor '-' to read VPD data from the standard input.\n\n");
	printf("keyword(s): Only display the requested information. (ID, PN, EC, SN, etc...)\n");
	return rc;
}
