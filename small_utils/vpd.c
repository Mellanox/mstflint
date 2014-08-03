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

#define _XOPEN_SOURCE 500
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <libgen.h>
#include <sys/times.h>
#include "tools_version.h"

/* pread is non-blocking, so we loop until we find data.  Unfortunately, 
 * we can loop forever if the HCA is crashed or if the wrong device is
 * specified as an argument. So, we set time outs.
 */
static clock_t ticks_per_sec, start_t, curr_t, timeout_t = 5;

struct vpd_cap {
	unsigned char id;
	unsigned char ptr;
	unsigned char addr_low;
	unsigned char addr_high_flag;
	unsigned char data[4];
};

enum {
	VPD_CAP_ID           = 0x03,
	PCI_CAP_PTR          = 0x34,
	PCI_HDR_SIZE         = 0x40,
	VPD_FLAG             = 0x80,
	VPD_FLAG_WRITE_START = 0x80,
	VPD_FLAG_WRITE_READY = 0x00,
	VPD_FLAG_READ_START  = 0x00,
	VPD_FLAG_READ_READY  = 0x80,
	VPD_ADDR_OFFSET      = 0x02,
	VPD_DATA_OFFSET      = 0x04,
	VPD_MAX_SIZE         = 1<<12
};

struct vpd_field {
	unsigned char keyword[2];
	unsigned char length;
	unsigned char data[0];
} __attribute__((packed));

union vpd_data {
	struct vpd_field fields[0];
	unsigned char bytes[0];
} __attribute__((packed));

struct vpd_small_data {
	unsigned char type;
	union vpd_data data;
} __attribute__((packed));

struct vpd_large_data {
	unsigned char type;
	unsigned char length_lsb;
	unsigned char length_msb;
	union vpd_data data;
} __attribute__((packed));

union vpd_data_type {
	unsigned char type;
	struct vpd_small_data small;
	struct vpd_large_data large;
	unsigned char bytes[0];
} __attribute__((packed));

typedef unsigned char vpd_t[VPD_MAX_SIZE];

#define VPD_TAG_LARGE(d) ((d)->type & 0x80)

#define VPD_TAG_LENGTH(d) ((unsigned)(VPD_TAG_LARGE(d) ? ((((d)->large.length_msb) << 8) | \
					       ((d)->large.length_lsb)) :       \
			   ((d)->type & 0x7)))

#define VPD_TAG_HEAD(d) (VPD_TAG_LARGE(d) ? sizeof (d)->large : sizeof (d)->small)

#define VPD_TAG_NAME(d) (VPD_TAG_LARGE(d) ? ((d)->type & 0x7F) : ((d)->type >> 3))

#define VPD_TAG_DATA(d) (VPD_TAG_LARGE(d) ? &(d)->large.data : &(d)->small.data)

enum {
	VPD_TAG_ID = 0x02, /* Product name of te device */
	VPD_TAG_R  = 0x10, /* Read-only keywords */
	VPD_TAG_W  = 0x11, /* Read-write keywords */
	VPD_TAG_F  = 0x0F, /* End Tag */
};

#define VPD_FIELD_CHECKSUM "RV"
#define VPD_FIELD_RW       "RW"

#define VPD_TOOL_VERSON "2.0.0"

int pci_find_capability(int fd, int cap_id)
{
	unsigned offset;
	unsigned char visited[256] = {}; /* Prevent infinite loops */
	unsigned char data[2];
	int ret;

	ret = pread(fd, data, 1, PCI_CAP_PTR);
	if (ret != 1) {
		return 0;
	}
	offset = data[0];

	for(;;) {
		if (offset < PCI_HDR_SIZE) {
			return 0;
		}

		ret = pread(fd, data, sizeof data, offset);
		if (ret != sizeof data) {
			return 0;
		}

		visited[offset] = 1;

		if (data[0] == cap_id) {
			return offset;
		}

		offset = data[1];
		if (visited[offset]) {
			return 0;
		}
	}
	return 0;
}

int pci_read_vpd_dword_file(int fd, unsigned offset, unsigned char data[4])
{
    if (offset >= VPD_MAX_SIZE || (offset & 0x3)) {
        return -1;
    }

    if (lseek(fd, offset, SEEK_SET) < 0)
    {
        fprintf(stderr, "Reached End Of VPD region: %s\n", strerror(errno));
        return errno;
    }
    if (read(fd, data, 0x4) != 4) {
        fprintf(stderr, "Failed to read VPD: %s\n", strerror(errno));
        return errno;
    }
    return 0;
}

int pci_read_vpd_dword_gw(int fd, int vpd_cap_offset, unsigned offset, unsigned char data[4])
{
	unsigned char addr_flag[2];
	int ret;

	if (offset >= VPD_MAX_SIZE || (offset & 0x3)) {
		return -1;
	}

	addr_flag[0] = (offset) & ~0x3;
	addr_flag[1] = ((offset) >> 8) | VPD_FLAG_READ_START;

	ret = pwrite(fd, addr_flag, sizeof addr_flag,
		     vpd_cap_offset + VPD_ADDR_OFFSET);

	if (ret != sizeof addr_flag) {
		return ret;
	}

	start_t = times(NULL);
	while((addr_flag[1] & VPD_FLAG) != VPD_FLAG_READ_READY) {
		curr_t = times(NULL);
		if ((curr_t - start_t) / ticks_per_sec > timeout_t) {
			fprintf(stderr, "-E- VPD read timeout\n");
			return -EIO;
		}

		ret = pread(fd, addr_flag, sizeof addr_flag,
			     vpd_cap_offset + VPD_ADDR_OFFSET);
		if (ret != sizeof addr_flag) {
			return ret;
		}
	}

	ret = pread(fd, data, sizeof data, vpd_cap_offset + VPD_DATA_OFFSET);
	if (ret != sizeof data) {
		return ret;
	}

	return 0;
}

int vpd_read(int fd, vpd_t vpd, int vpd_path_exists)
{
    if (vpd_path_exists) {
        unsigned offset;
        int ret;
        for (offset = 0; offset < VPD_MAX_SIZE; offset += 0x4) {
            ret = pci_read_vpd_dword_file(fd, offset, vpd + offset);
            if (ret) {
                return ret;
            }
        }
    } else {
        unsigned offset;
        int ret;
        int vpd_cap_offset;
        vpd_cap_offset = pci_find_capability(fd, VPD_CAP_ID);
        if (!vpd_cap_offset) {
            return -1;
        }

        for (offset = 0; offset < VPD_MAX_SIZE; offset += 0x4) {
            ret = pci_read_vpd_dword_gw(fd, vpd_cap_offset, offset, vpd + offset);
            if (ret) {
                return ret;
            }
        }
    }
    return 0;
}

/* Verify that keywords in R and W sections fit in length. */
int vpd_check_one(union vpd_data_type *d, unsigned offset)
{
	unsigned i;
	struct vpd_field *field;

	if (VPD_TAG_NAME(d) == VPD_TAG_R ||
	    VPD_TAG_NAME(d) == VPD_TAG_W)
		for (i = 0; i < VPD_TAG_LENGTH(d); i += 0x3 + field->length) {
			field = (struct vpd_field *)(VPD_TAG_DATA(d)->bytes + i);
			if (i + 0x3 + field->length > VPD_TAG_LENGTH(d)) {
				fprintf(stderr, "-E- Tag %s, Offset 0x%x+0x%x: "
					"field length 0x%x exceeds total 0x%x",
					VPD_TAG_NAME(d) == VPD_TAG_R ? "VPD_R" : "VPD_W",
					offset, i, field->length, VPD_TAG_LENGTH(d));
				if (VPD_TAG_NAME(d) == VPD_TAG_W)
					fprintf(stderr, ". Use -r flag to skip VPD_W tag checks");
				fprintf(stderr, "\n");
				return -1;
			}
		}
	return 0;
}

/* Find length to checksum. */
void vpd_checksum_length(union vpd_data_type *d, unsigned offset, unsigned *checksum_len)
{
	unsigned i;
	struct vpd_field *field;

	if (VPD_TAG_NAME(d) != VPD_TAG_R) {
		return;
	}

	for (i = 0; i < VPD_TAG_LENGTH(d); i += 0x3 + field->length) {
		field = (struct vpd_field *)(VPD_TAG_DATA(d)->bytes + i);
		if (!memcmp(VPD_FIELD_CHECKSUM, field->keyword,
			    sizeof field->keyword)) {
			*checksum_len = offset + VPD_TAG_HEAD(d) + i + 0x3 + 1;
		}
	}
}

void vpd_show_field(FILE *f, struct vpd_field *field)
{
	int i;

	if (!memcmp(VPD_FIELD_CHECKSUM, field->keyword, sizeof field->keyword) ||
		!memcmp(VPD_FIELD_RW      , field->keyword, sizeof field->keyword)) {
		return;
	}
	fputc(field->keyword[0], f);
	fputc(field->keyword[1], f);
	fputs(": ", f);
	for (i = 0; i < field->length; ++i) {
		if (!field->data[i]) {
			break;
		}
		fputc(field->data[i], f);
	}
	fputc('\n', f);
}

void vpd_show_fields(FILE *f, union vpd_data_type *d, const char *keyword)
{
	struct vpd_field *field;
	unsigned i;

	for (i = 0; i < VPD_TAG_LENGTH(d); i += 0x3 + field->length) {
		field = (struct vpd_field *)(VPD_TAG_DATA(d)->bytes + i);
		if (!keyword ||
			!memcmp(keyword, field->keyword, sizeof field->keyword)) {
				vpd_show_field(f, field);
		}
	}
}

void vpd_show_id(FILE *f, union vpd_data_type *d)
{
	unsigned i;

	fputs("ID: ", f);
	for (i = 0; i < VPD_TAG_LENGTH(d); ++i) {
		fputc(VPD_TAG_DATA(d)->bytes[i], f);
	}
	fputc('\n', f);
}

void vpd_show_one(FILE *f, union vpd_data_type* d, const char *keyword)
{
	switch(VPD_TAG_NAME(d)) {
	case VPD_TAG_ID:
		if (!keyword || !memcmp("ID", keyword, 2)) {
			vpd_show_id(f, d);
		}
		break;
	case VPD_TAG_R:
		vpd_show_fields(f, d, keyword);
		break;
	case VPD_TAG_W:
		vpd_show_fields(f, d, keyword);
		break;
	case VPD_TAG_F:
		break;
	default:
		if (!keyword) {
			fprintf(f, "??: 0x%x\n", VPD_TAG_NAME(d));
		}
	}
}

int vpd_check(vpd_t vpd, int checksum, int ignore_w)
{
	unsigned char b;
	unsigned i;
	unsigned offset;
	int rc;
	union vpd_data_type *d = NULL;
	unsigned checksum_len = 0;

	for (offset = 0; offset < VPD_MAX_SIZE && (!d || VPD_TAG_NAME(d) != VPD_TAG_F);
			offset += VPD_TAG_HEAD(d) + VPD_TAG_LENGTH(d)) {
		d = (union vpd_data_type *)(vpd + offset);

		if (!(VPD_TAG_NAME(d) == VPD_TAG_W && ignore_w)) {
			rc = vpd_check_one(d, offset);
			if (rc) {
				return rc;
			}
		}

		vpd_checksum_length(d, offset, &checksum_len);
	}

	if (VPD_TAG_NAME(d) != VPD_TAG_F) {
		fprintf(stderr, "-E- Mandatory End(0xF) tag not found.\n");
		return 1;
	}

    if (!checksum_len) {
        fprintf(stderr, "-E- No VPD was found.\n");
        return 1;
    }

	if (!checksum) {
		return 0;
	}

	b = 0;
	for (i = 0; i < checksum_len; ++i) {
		b+= vpd[i];
	}

	if (b) {
		fprintf(stderr, "-E- Len 0x%x: checksum mismatch: 0x%x\n",
			checksum_len, b);
		return 1;
	}

	return 0;
}

void vpd_show(FILE *f, vpd_t vpd, const char *keyword, int ignore_w)
{
	unsigned offset;
	union vpd_data_type *d = NULL;
	for (offset = 0; !d || VPD_TAG_NAME(d) != VPD_TAG_F;
	     offset += VPD_TAG_HEAD(d) + VPD_TAG_LENGTH(d)) {
		d = (union vpd_data_type *)(vpd + offset);
		if (!(VPD_TAG_NAME(d) == VPD_TAG_W && ignore_w))
			vpd_show_one(f, d, keyword);
	}
}

int is_file_exist(const char *fname)
{
    int fd = open(fname, O_RDONLY);
    if (fd > 0) {
        u_int8_t data[4];
        if (read(fd, data, 0x4) != 4){
            close(fd);
            return 0;
        } else {
            close(fd);
            return 1;
        }
    }
    return 0;
}

int pci_parse_name(const char *name, char buf[4096], int* vpd_path_exists)
{
	int domain, bus, dev, func, tmp;
	struct stat dummybuf;

	if (*name == '/') {
		if (strlen(name) >= 4096)
			return -1;
		strcpy(buf, name);
		return 0;
	}

	if (sscanf(name,"mthca%x", & tmp) == 1 ||
	    sscanf(name,"mlx4_%x", & tmp) == 1 ||
	    sscanf(name,"mlx5_%x", & tmp) == 1   ) {
		char mbuf[4096];
		char pbuf[4096];
		char *base;

		tmp = snprintf(mbuf, sizeof mbuf, "/sys/class/infiniband/%s/device", name);
		if (tmp <= 0 || tmp >= (int)sizeof mbuf) {
			fprintf(stderr,"-E- Unable to print device name %s\n", name);
			return 1;
		}

		if (readlink(mbuf, pbuf, sizeof pbuf) < 0) {
			perror("-E- read link");
			fprintf(stderr,"-E- Unable to read link %s\n", mbuf);
			return 1;
		}

		base = basename(pbuf);
		if (!base) {
			return 1;
		}
		if (sscanf(base, "%x:%x:%x.%x", &domain, &bus, &dev, &func) != 4) {
			return 1;
		}
	} else if (sscanf(name, "%x:%x:%x.%x", &domain, &bus, &dev, &func) != 4) {
		domain = 0;
		if (sscanf(name, "%x:%x.%x", &bus, &dev, &func) != 3) {
			return -2;
		}
	}
	
	snprintf(buf, 4096, "/sys/bus/pci/devices/%04x:%02x:%02x.%d/vpd", domain, bus, dev, func);
	if (is_file_exist(buf)) {
	    *vpd_path_exists = 1;
	    return 0;
	}
	*vpd_path_exists = 0;

	snprintf(buf, 4096, "/proc/bus/pci/%2.2x/%2.2x.%1.1x", bus, dev, func);
	if (stat(buf, &dummybuf)) {
		snprintf(buf, 4096, "/proc/bus/pci/%4.4x:%2.2x/%2.2x.%1.1x",
			 domain, bus,dev,func);
	}

	if (stat(buf, &dummybuf)) {
		return -3;
	}

	return 0;
}

int vpd_open(const char *name, int* vpd_path_exists)
{
	int fd;
	char buf[4096];

	if (pci_parse_name(name, buf, vpd_path_exists)) {
		fprintf(stderr, "-E- Unable to parse device name %s\n", name);
		return -1;
	}
	fd = open(buf, O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "-E- Unable to open file %s: %s\n", buf, strerror(errno));
	}
	return fd;
}

int main(int argc, char **argv)
{
	const char *name;
	char* endptr;
	int fd;
	int i;
	int rc = 0;
	vpd_t d;
	int m = 0;
	int n = 0;
	int ignore_w = 0;
	int vpd_path_exists = 0;

	if (argc < 2) {
		rc = 1;
		goto usage;
	}

	ticks_per_sec = sysconf(_SC_CLK_TCK);

	do
	{
		i=getopt(argc, argv, "mvhnrt:");
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
			case 'h':
			    rc = 0;
			    goto usage;
			case 'v':
                print_version_string("mstvpd", VPD_TOOL_VERSON);
                exit(0);
			case 'r':
				ignore_w=1;
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
		fd = vpd_open(name, &vpd_path_exists);
		if (fd < 0)
			return 4;

		if (vpd_read(fd, d, vpd_path_exists)) {
		    fprintf(stderr, "-E- Failed to read VPD from %s!\n", name);
		    return 5;
		}

	}

	if (m)
		return fwrite(d, VPD_MAX_SIZE, 1, stdout) != 1;

	if (vpd_check(d, !n, ignore_w))
		return 6;

	if (argc == 1)
		vpd_show(stdout, d, NULL, ignore_w);
	else
		for (i = 0; i < argc - 1; ++i) {
			if (!strcmp(argv[i + 1], "--"))
			    continue;
			vpd_show(stdout, d, argv[i + 1], ignore_w);
		}

	return 0;

usage:
	fprintf(stderr, "Usage: %s [-m|-n] [-t ##] <file> [-- keyword ...]\n", argv[0]);
	fprintf(stderr, "-h\tPrint this help.\n");
	fprintf(stderr, "-v\tPrint tool version.\n");
	fprintf(stderr, "-m\tDump raw VPD data to stdout.\n");
	fprintf(stderr, "-n\tDo not validate check sum.\n");
	fprintf(stderr, "-r\tDo not check and display the VPD_W tag in the vpd data.\n");
	fprintf(stderr, "-t ##\tTime out after ## seconds. (Default is 30.)\n\n");
	fprintf(stderr, "file\tThe PCI id number of the HCA (for example, \"2:00.0\"),\n");
	fprintf(stderr, "\tthe device name (such as \"mlx4_0\")\n");
	fprintf(stderr, "\tthe absolute path to the device (\"/sys/class/infiniband/mlx4_0/device\")\n");
	fprintf(stderr, "\tor '-' to read VPD data from the standard input.\n\n");
	fprintf(stderr, "keyword(s): Only display the requested information. (ID, PN, EC, SN, etc...)\n");
	return rc;
}
