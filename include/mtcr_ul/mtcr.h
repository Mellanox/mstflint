/*
 *
 *  mtcr.h - Mellanox Software tools (mst) driver definitions
 *
 * Author: Michael S. Tsirkin <mst@mellanox.co.il>
 *
 * Copyright (c) 2006 Mellanox Technologies Ltd.  All rights reserved.
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

#ifndef _MST_H
#define _MST_H

//use memory mapped /dev/mem for access
#define CONFIG_ENABLE_MMAP 1
//mmap /dev/mem for memory access (does not work on sparc)
#define CONFIG_USE_DEV_MEM 1
//use pci configuration cycles for access
#define CONFIG_ENABLE_PCICONF 1

#ifndef _XOPEN_SOURCE
#if CONFIG_ENABLE_PCICONF && CONFIG_ENABLE_MMAP
/* For strerror_r */
#define _XOPEN_SOURCE 600
#elif CONFIG_ENABLE_PCICONF
#define _XOPEN_SOURCE 500
#endif
#endif

#if CONFIG_ENABLE_MMAP
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include <unistd.h>

#include <netinet/in.h>
#include <endian.h>
#include <byteswap.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>


#if CONFIG_ENABLE_MMAP
#include <sys/mman.h>
#include <sys/pci.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#endif

#ifndef __be32_to_cpu
#define __be32_to_cpu(x) ntohl(x)
#endif
#ifndef __cpu_to_be32
#define __cpu_to_be32(x) htonl(x)
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
#ifndef __cpu_to_le32
#define  __cpu_to_le32(x) (x)
#endif
#ifndef __le32_to_cpu
#define  __le32_to_cpu(x) (x)
#endif
#elif __BYTE_ORDER == __BIG_ENDIAN
#ifndef __cpu_to_le32
#define  __cpu_to_le32(x) bswap_32(x)
#endif
#ifndef __le32_to_cpu
#define  __le32_to_cpu(x) bswap_32(x)
#endif
#else
#ifndef __cpu_to_le32
#define  __cpu_to_le32(x) bswap_32(__cpu_to_be32(x))
#endif
#ifndef __le32_to_cpu
#define  __le32_to_cpu(x) __be32_to_cpu(bswap_32(x))
#endif
#endif

#define MTCR_MAP_SIZE 0x100000


#ifdef __cplusplus
extern "C" {
#endif

typedef enum Mdevs_t {
    MDEVS_GAMLA     = 0x01, /*  Each device that actually is a Gamla */
    MDEVS_I2CM      = 0x02, /*  Each device that can work as I2C master */
    MDEVS_MEM       = 0x04, /*  Each device that is a memory driver (vtop) */
    MDEVS_TAVOR_DDR = 0x08, /*  Each device that maps to Tavor DDR */
    MDEVS_TAVOR_UAR = 0x10, /*  Each device that maps to Tavor UAR */
    MDEVS_TAVOR_CR  = 0x20, /*  Each device that maps to Tavor CR */
    MDEVS_IF        = 0x40, /*  Standard device  interface */
    MDEVS_REM       = 0x80, /*  Remote devices */
    MDEVS_PPC       = 0x100, /*  PPC devices */
    MDEVS_DEV_I2C   = 0x200, /* Generic linux kernel i2c device */
    MDEVS_IB        = 0x400, /* Cr access over IB Mads */
    MDEVS_MLNX_OS   = 0x800, /* access by CmdIf in MlnxOS */
    MDEVS_TAVOR     = (MDEVS_TAVOR_DDR|MDEVS_TAVOR_UAR|MDEVS_TAVOR_CR),
    MDEVS_ALL       = 0xffffffff
} Mdevs;

/*  All fields in the following structure are not supposed to be used */
/*  or modified by user programs. */
typedef struct mfile_t {
    int           fd;
    void          *ptr;
    int           connectx_flush; /* For ConnectX A0 */
    int           need_flush; /* For ConnectX A0 */
} mfile;

typedef struct dev_info_t
{
    Mdevs         type;
    char          dev_name[512];

    union {
        struct {
            u_int16_t domain;
            u_int8_t  bus;
            u_int8_t  dev;
            u_int8_t  func;

            u_int16_t dev_id;
            u_int16_t vend_id;
            u_int32_t class_id;
            u_int16_t subsys_id;
            u_int16_t subsys_vend_id;

            char      cr_dev[512];
            char      conf_dev[512];
            char**    net_devs;      // Null terminated array
            char**    ib_devs;       // Null terminated array
        } pci;

        struct {
            u_int32_t TBD;
        } usb;

        struct {
            u_int32_t TBD;
        } ib;

        struct {
            u_int32_t TBD;
        } remote;
    };
} dev_info;

#ifndef MTCR_EXPORT
static void mtcr_connectx_flush(void *ptr)
{
	u_int32_t value;
	*((u_int32_t *)((char *)ptr + 0xf0380)) = 0x0;
	do {
		asm volatile ("":::"memory");
		value = __be32_to_cpu(*((u_int32_t *)((char *)ptr + 0xf0380)));
	} while(value);
}
#endif

/*
 * Read 4 bytes, return number of succ. read bytes or -1 on failure
 */
int mread4(mfile *mf, unsigned int offset, u_int32_t *value)
#ifdef MTCR_EXPORT
;
#else
{
#if CONFIG_ENABLE_MMAP
	if (mf->ptr) {
		if (mf->need_flush) {
			mtcr_connectx_flush(mf->ptr);
			mf->need_flush = 0;
		}
		*value = __be32_to_cpu(*((u_int32_t *)((char *)mf->ptr + offset)));
		return 4;
	}
#endif
#if CONFIG_ENABLE_PCICONF
	{
		int rc;
		offset = __cpu_to_le32(offset);
		rc=pwrite(mf->fd, &offset, 4, 22*4);
		if (rc < 0) {
			perror("write offset");
			return rc;
		}
		if (rc != 4)
			return 0;
		rc=pread(mf->fd, value, 4, 23*4);
		if (rc < 0) {
			perror("read value");
			return rc;
		}
		*value = __le32_to_cpu(*value);
		return rc;
	}
#else
	return 0;
#endif
}
#endif

/*
 * Write 4 bytes, return number of succ. written bytes or -1 on failure
 */
int mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
#ifdef MTCR_EXPORT
;
#else
{
#if CONFIG_ENABLE_MMAP
  if (mf->ptr) {
            *((u_int32_t *)((char *)mf->ptr + offset)) = __cpu_to_be32(value);
            mf->need_flush = mf->connectx_flush;
            return 4;
  }
#endif
#if CONFIG_ENABLE_PCICONF
  {
    int rc;
    offset = __cpu_to_le32(offset);
    rc = pwrite(mf->fd, &offset, 4, 22*4);
    if (rc < 0) {
      perror("write offset");
      return rc;
    }
    if (rc != 4)
	    return 0;
    value = __cpu_to_le32(value);
    rc = pwrite(mf->fd, &value, 4, 23*4);
    if (rc < 0) {
      perror("write value");
      return rc;
    }
    return rc;
  }
#else
  return 0;
#endif
}
#endif

#ifndef MTCR_EXPORT
static int
mread_chunk_as_multi_mread4(mfile *mf, unsigned int offset, void *data, int length)
{
    int i;
    if (length % 4) {
        return EINVAL;
    }
    for (i = 0; i < length ; i += 4) {
        u_int32_t value;
        if (mread4(mf, offset + i, &value) != 4) {
            return -1;
        }
        memcpy((char*)data + i , &value,4);
    }
    return length;
}

static int
mwrite_chunk_as_multi_mwrite4(mfile *mf, unsigned int offset, void *data, int length)
{
    int i;
    if (length % 4) {
        return EINVAL;
    }
    for (i = 0; i < length ; i += 4) {
        u_int32_t value;
        memcpy(&value, (char*)data + i ,4);
        if (mwrite4(mf, offset + i, value) != 4) {
            return -1;
        }
    }
    return length;
}


enum mtcr_access_method {
	MTCR_ACCESS_ERROR  = 0x0,
	MTCR_ACCESS_MEMORY = 0x1,
	MTCR_ACCESS_CONFIG = 0x2,
};

static
int mtcr_check_signature(mfile *mf)
{
	unsigned signature;
	int rc;
	rc = mread4(mf, 0xF0014, &signature);
	if (rc != 4) {
		if (!errno)
			errno = EIO;
		return -1;
	}

	switch (signature & 0xffff) {
	case 0x190 : /* 400 */
	case 0x1f5 :
	case 0x1f7 :
		if ((signature == 0xa00190         || 
                    (signature & 0xffff) == 0x1f5  ||
                    (signature & 0xffff) == 0x1f7)    && mf->ptr) {
			mf->connectx_flush = 1;
			mtcr_connectx_flush(mf->ptr);
		}
	case 0x5a44: /* 23108 */
	case 0x6278: /* 25208 */
	case 0x5e8c: /* 24204 */
	case 0x6274: /* 25204 */
	case 0x1b3:  /*   435 */
	case 6100:   /*  6100 */
	case 0x245:
	case 0x1ff:
		return 0;
	default:
		fprintf(stderr, "-W- Unknown dev id: 0x%x\n", signature);
		errno = ENOTTY;
		return -1;
	}
}

#if CONFIG_ENABLE_MMAP
/*
 * The PCI interface treats multi-function devices as independent
 * devices.  The slot/function address of each device is encoded
 * in a single byte as follows:
 *
 *	7:3 = slot
 *	2:0 = function
 */
#define PCI_DEVFN(slot,func)	((((slot) & 0x1f) << 3) | ((func) & 0x07))
#define PCI_SLOT(devfn)		(((devfn) >> 3) & 0x1f)
#define PCI_FUNC(devfn)		((devfn) & 0x07)

static
unsigned long long mtcr_procfs_get_offset(unsigned my_bus, unsigned my_dev,
					  unsigned my_func)
{
	FILE* f;
	unsigned irq;
	unsigned long long base_addr[6], rom_base_addr, size[6], rom_size;

	unsigned bus, dev, func;
	//unsigned vendor_id;
	//unsigned device_id;
	unsigned int cnt;

	unsigned long long offset = (unsigned long long)-1;

	char buf[4048];

	f = fopen("/proc/bus/pci/devices", "r");
	if (!f) return offset;

	for(;;) if (fgets(buf, sizeof(buf) - 1, f)) {
		unsigned dfn, vend;

		cnt = sscanf(buf,
			     "%x %x %x %llx %llx %llx %llx %llx %llx "
			     "%llx %llx %llx %llx %llx %llx %llx %llx",
			     &dfn,
			     &vend,
			     &irq,
			     &base_addr[0],
			     &base_addr[1],
			     &base_addr[2],
			     &base_addr[3],
			     &base_addr[4],
			     &base_addr[5],
			     &rom_base_addr,
			     &size[0],
			     &size[1],
			     &size[2],
			     &size[3],
			     &size[4],
			     &size[5],
			     &rom_size);
		if (cnt != 9 && cnt != 10 && cnt != 17)
		{
			fprintf(stderr,"proc: parse error (read only %d items)\n", cnt);
			fprintf(stderr,"the offending line in " "/proc/bus/pci/devices" " is "
				"\"%.*s\"\n", (int)sizeof(buf), buf);
			goto error;
		}
		bus = dfn >> 8U;
		dev = PCI_SLOT(dfn & 0xff);
		func = PCI_FUNC(dfn & 0xff);
		//vendor_id = vend >> 16U;
		//device_id = vend & 0xffff;

		if (bus == my_bus && dev == my_dev && func == my_func)
			break;
	}
	else
		goto error;

	if (cnt != 17 || size[1] != 0 || size[0] != MTCR_MAP_SIZE) {
		if (0) fprintf(stderr,"proc: unexpected region size values: "
			"cnt=%d, size[0]=%#llx, size[1]=%#llx\n",
			cnt,size[0],size[1]);
		if (0) fprintf(stderr,"the offending line in " "/proc/bus/pci/devices"
			       " is \"%.*s\"\n", (int)sizeof(buf), buf);
		goto error;
	}


	offset = ((unsigned long long)(base_addr[1]) << 32) +
		((unsigned long long)(base_addr[0]) & ~(unsigned long long)(0xfffff));

	fclose(f);
	return offset;

error:
	fclose(f);
	errno = ENXIO;
	return offset;
}

static
unsigned long long mtcr_sysfs_get_offset(unsigned domain, unsigned bus,
					 unsigned dev, unsigned func)
{
	unsigned long long start, end, type;
	unsigned long long offset = (unsigned long long)-1;
	FILE *f;
	int cnt;
	char mbuf[] = "/sys/bus/pci/devices/XXXX:XX:XX.X/resource";
	sprintf(mbuf, "/sys/bus/pci/devices/%4.4x:%2.2x:%2.2x.%1.1x/resource",
		       domain, bus, dev, func);

	f = fopen(mbuf, "r");
	if (!f)
		return offset;

	cnt = fscanf(f, "0x%llx 0x%llx 0x%llx", &start, &end, &type);
	if (cnt != 3 || end != start + MTCR_MAP_SIZE - 1) {
		if (0) fprintf(stderr,"proc: unexpected region size values: "
			"cnt=%d, start=%#llx, end=%#llx\n",
			cnt, start, end);
		goto error;
	}

	fclose(f);
	return start;

error:
	fclose(f);
	errno = ENOENT;
	return offset;
}

static
int mtcr_mmap(mfile *mf, const char *name, off_t off, int ioctl_needed)
{
	int err;

	mf->fd = open(name, O_RDWR | O_SYNC);
	if (mf->fd < 0)
		return -1;

	if (ioctl_needed && ioctl(mf->fd, PCIIOC_MMAP_IS_MEM) < 0) {
		err = errno;
		close(mf->fd);
		errno = err;
		return -1;
	}

	mf->ptr = mmap(NULL, MTCR_MAP_SIZE, PROT_READ | PROT_WRITE,
		       MAP_SHARED, mf->fd, off);

	if (!mf->ptr || mf->ptr == MAP_FAILED) {
		err = errno;
		close(mf->fd);
		errno = err;
		return -1;
	}

	if (mtcr_check_signature(mf)) {
		munmap(mf->ptr, MTCR_MAP_SIZE);
		close(mf->fd);
		errno = EIO;
		return -1;
	}

	return 0;
}
#else
static
unsigned long long mtcr_procfs_get_offset(unsigned my_bus, unsigned my_dev,
					  unsigned my_func)
{
	return -1;
}

static
unsigned long long mtcr_sysfs_get_offset(unsigned domain, unsigned bus,
					 unsigned dev, unsigned func)
{
	return -1;
}

static
int mtcr_mmap(mfile *mf, const char *name, off_t off, int ioctl_needed)
{
	return -1;
}
#endif

#if CONFIG_ENABLE_PCICONF
static
int mtcr_open_config(mfile *mf, const char *name)
{
	unsigned signature;
	int rc, err;

	mf->fd = open(name, O_RDWR | O_SYNC);
	if (mf->fd < 0)
		return -1;

	/* Kernels before 2.6.12 carry the high bit in each byte
	 * on <device>/config writes, overriding higher bits.
	 * Make sure the high bit is set in some signature bytes,
	 * to catch this. */
	/* Do this test before mtcr_check_signature,
	   to avoid system failure on access to an illegal address. */
	signature = 0xfafbfcfd;
	rc = pwrite(mf->fd, &signature, 4, 22*4);
	if (rc != 4) {
		err = errno;
		close(mf->fd);
		errno = err;
		return -1;
	}

	rc = pread(mf->fd, &signature, 4, 22*4);
	if (rc != 4) {
		err = errno;
		close(mf->fd);
		errno = err;
		return -1;
	}

	if (signature != 0xfafbfcfd) {
		close(mf->fd);
		errno = EIO;
		return -1;
	}

	if (mtcr_check_signature(mf)) {
		close(mf->fd);
		errno = EIO;
		return -1;
	}

	return 0;
}
#else
static
int mtcr_open_config(mfile *mf, const char *name)
{
	return -1;
}
#endif

static
enum mtcr_access_method mtcr_parse_name(const char* name, int *force,
				       	unsigned *domain_p, unsigned *bus_p,
				       	unsigned *dev_p, unsigned *func_p)
{
	unsigned my_domain = 0;
	unsigned my_bus;
	unsigned my_dev;
	unsigned my_func;
	int scnt, r;
	char config[] = "/config";
	char resource0[] = "/resource0";
	char procbuspci[] = "/proc/bus/pci/";
	unsigned len = strlen(name);
	unsigned tmp;

	if (len >= sizeof config && !strcmp(config, name + len + 1 - sizeof config)) {
		*force = 1;
		return MTCR_ACCESS_CONFIG;
	}

	if (len >= sizeof resource0 &&
	    !strcmp(resource0, name + len + 1 - sizeof resource0)) {
		*force = 1;
		return MTCR_ACCESS_MEMORY;
	}

	if (!strncmp(name,"/proc/bus/pci/", sizeof procbuspci - 1)) {
		*force = 1;
		return MTCR_ACCESS_CONFIG;
	}

	if (sscanf(name, "mthca%x", &tmp) == 1 ||
	    sscanf(name, "mlx4_%x", &tmp) == 1) {
		char mbuf[4048];
		char pbuf[4048];
		char *base;

		r = snprintf(mbuf, sizeof mbuf, "/sys/class/infiniband/%s/device", name);
		if (r <= 0 || r >= (int)sizeof mbuf) {
			fprintf(stderr,"Unable to print device name %s\n", name);
			goto parse_error;
		}

		r = readlink(mbuf, pbuf, sizeof pbuf - 1);
		if (r < 0) {
			perror("read link");
			fprintf(stderr,"Unable to read link %s\n", mbuf);
			return MTCR_ACCESS_ERROR;
		}
		pbuf[r] = '\0';

		base = basename(pbuf);
		if (!base)
			goto parse_error;
		scnt = sscanf(base, "%x:%x:%x.%x",
			      &my_domain, &my_bus, &my_dev, &my_func);
		if (scnt != 4)
			goto parse_error;
		goto name_parsed;
	}

	scnt = sscanf(name, "%x:%x.%x", &my_bus, &my_dev, &my_func);
	if (scnt == 3)
		goto name_parsed;

	scnt = sscanf(name, "%x:%x:%x.%x", &my_domain, &my_bus, &my_dev, &my_func);
	if (scnt == 4)
		goto name_parsed;

parse_error:
	fprintf(stderr,"Unable to parse device name %s\n", name);
	errno = EINVAL;
	return MTCR_ACCESS_ERROR;

name_parsed:
	*domain_p = my_domain;
	*bus_p = my_bus;
	*dev_p = my_dev;
	*func_p = my_func;
	*force = 0;
	return MTCR_ACCESS_MEMORY;
}
#endif


int mread4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len)
#ifdef MTCR_EXPORT
	;
#else
{
	return mread_chunk_as_multi_mread4(mf, offset, data, byte_len);	
}
#endif

int mwrite4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len)
#ifdef MTCR_EXPORT
	;
#else
{
	return mwrite_chunk_as_multi_mwrite4(mf, offset, data, byte_len);	
}
#endif

int msw_reset(mfile *mf) 
#ifdef MTCR_EXPORT
	;
#else
{
	(void)mf; /* Warning */
    return -1;
}
#endif

/*
 * Get list of MST (Mellanox Software Tools) devices.
 * Put all device names as null-terminated strings to buf.
 *
 * Return number of devices found or -1 if buf overflow
 */
int mdevices(char *buf, int len, int mask)
#ifdef MTCR_EXPORT
	;
#else
{

#define MDEVS_TAVOR_CR  0x20 
#define MLNX_PCI_VENDOR_ID  "0x15b3"

	FILE* f;
    DIR* d;
    struct dirent *dir;
	int pos = 0;
    int sz;
    int rsz;
	int ndevs = 0;

	if (!(mask & MDEVS_TAVOR_CR)) {
		return 0;
	}
    
	char inbuf[64];
    char fname[64];

    d = opendir("/sys/bus/pci/devices");
    if (d == NULL) {
        return -2;
    }

    while ((dir = readdir(d)) != NULL) {
        if (dir->d_name[0] == '.') {
            continue;
        }
        sprintf(fname, "/sys/bus/pci/devices/%s/vendor", dir->d_name);
        sz = strlen(dir->d_name);
	    f = fopen(fname, "r");
        if (f == NULL) {
            ndevs = -2;
            goto cleanup_dir_opened;
        }
        if (fgets(inbuf, sizeof(inbuf), f)) {
            if(!strncmp(inbuf, MLNX_PCI_VENDOR_ID, strlen(MLNX_PCI_VENDOR_ID))) {
                rsz = sz + 1; //dev name size + place for Null char
    			if ((pos + rsz) > len) {
	    			ndevs = -1;
		    		goto cleanup_file_opened;
			    }
    			memcpy(&buf[pos], dir->d_name, rsz);
	    		pos += rsz;
		    	ndevs++;
            }
        }
        fclose(f);
    }
    closedir(d);

    return ndevs;

cleanup_file_opened:
    fclose(f);
cleanup_dir_opened:
    closedir(d);
	return ndevs;
}
#endif


int read_pci_config_header(u_int16_t domain, u_int8_t bus, u_int8_t dev, u_int8_t func, u_int8_t data[0x40])
#ifdef MTCR_EXPORT
	;
#else
{
    char proc_dev[64];
    sprintf(proc_dev, "/sys/bus/pci/devices/%04x:%02x:%02x.%d/config", domain, bus, dev, func);
    FILE* f = fopen(proc_dev, "r");
    if (!f) {
        fprintf(stderr, "Failed to open (%s) for reading: %s\n", proc_dev, strerror(errno));
        return 1;
    }
    setvbuf(f, NULL, _IONBF, 0);
    if (fread(data, 0x40, 1, f) != 1) {
        fprintf(stderr, "Failed to read from (%s): %s\n", proc_dev, strerror(errno));
        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}
#endif

/*
 * Get list of MST (Mellanox Software Tools) devices info records.
 * Return a dynamic allocated array of dev_info records.
 * len will be updated to hold the array length
 *
 */
dev_info* mdevices_info(int mask, int* len)
#ifdef MTCR_EXPORT
	;
#else
{
    char* devs = 0;
    char* dev_name;
    int size = 2048;
    int rc;
    int i;

    // Get list of devices
    do {
        if (devs)
            free(devs);
        size *= 2;
        devs = (char*)malloc(size);
        rc = mdevices(devs, size, mask);
    } while (rc == -1);

    // For each device read
    dev_info* dev_info_arr = (dev_info*) malloc(sizeof(dev_info)*rc);
    memset(dev_info_arr, 0, sizeof(dev_info)*rc);
    dev_name = devs;
    for (i = 0; i < rc; i++) {
        int domain = 0;
        int bus = 0;
        int dev = 0;
        int func = 0;

        dev_info_arr[i].type = (Mdevs)MDEVS_TAVOR_CR;
        u_int8_t conf_header[0x40];
		u_int32_t *conf_header_32p = (u_int32_t*)conf_header;

        // update default device name
        strcpy(dev_info_arr[i].dev_name, dev_name);
        strcpy(dev_info_arr[i].pci.cr_dev, dev_name);

        // update dbdf
        sscanf(dev_name, "%x:%x:%x.%x", &domain, &bus, &dev, &func);
        dev_info_arr[i].pci.domain = domain;
        dev_info_arr[i].pci.bus = bus;
        dev_info_arr[i].pci.dev = dev;
        dev_info_arr[i].pci.func = func;

        // read configuration space header
        if (read_pci_config_header(domain, bus, dev, func, conf_header)) {
            goto next;
        }

        dev_info_arr[i].pci.dev_id = __le32_to_cpu(conf_header_32p[0]) >> 16;
        dev_info_arr[i].pci.vend_id = __le32_to_cpu(conf_header_32p[0]) & 0xffff;
        dev_info_arr[i].pci.class_id = __le32_to_cpu(conf_header_32p[2]) >> 8;
        dev_info_arr[i].pci.subsys_id = __le32_to_cpu(conf_header_32p[11]) >> 16;
        dev_info_arr[i].pci.subsys_vend_id = __le32_to_cpu(conf_header_32p[11]) & 0xffff;

        // set conf device
        snprintf(dev_info_arr[i].pci.conf_dev, sizeof(dev_info_arr[i].pci.conf_dev), "/sys/bus/pci/devices/%04x:%02x:%02x.%x/config", domain, bus,dev, func);


next:
        dev_name += strlen(dev_name) + 1;
    }

    free(devs);
    *len = rc;
    return dev_info_arr;
}
#endif

void mdevice_info_destroy(dev_info* dev_info, int len)
#ifdef MTCR_EXPORT
	;
#else
{
	(void)len; 
	if (dev_info)
		free(dev_info);
}
#endif


/*
 * Open Mellanox Software tools (mst) driver. Device type==TAVOR
 * Return valid mfile ptr or 0 on failure
 */
mfile *mopen(const char *name)
#ifdef MTCR_EXPORT
	;
#else
{
	mfile *mf;
	off_t offset;
	unsigned domain, bus, dev, func;
	enum mtcr_access_method access;
	int force;
	char rbuf[] = "/sys/bus/pci/devices/XXXX:XX:XX.X/resource0";
	char cbuf[] = "/sys/bus/pci/devices/XXXX:XX:XX.X/config";
	char pdbuf[] = "/proc/bus/pci/XXXX:XX/XX.X";
	char pbuf[] = "/proc/bus/pci/XX/XX.X";
	char errbuf[4048]="";
	int err;

	mf = (mfile *)malloc(sizeof(mfile));
	if (!mf)
		return NULL;
	mf->ptr = NULL;
	mf->fd = -1;
	mf->connectx_flush = mf->need_flush = 0;

	access = mtcr_parse_name(name, &force, &domain, &bus, &dev, &func);
	if (access == MTCR_ACCESS_ERROR)
		goto open_failed;

	if (force) {

		if (access == MTCR_ACCESS_CONFIG) {
			if (!mtcr_open_config(mf, name))
				return mf;
		} else {
			if (!mtcr_mmap(mf, name, 0, 0))
				return mf;
		}

		goto open_failed;
	}

	if (access == MTCR_ACCESS_CONFIG)
		goto access_config_forced;

	sprintf(rbuf, "/sys/bus/pci/devices/%4.4x:%2.2x:%2.2x.%1.1x/resource0",
		domain, bus, dev, func);

	if (!mtcr_mmap(mf, rbuf, 0, 0))
		return mf;

	/* Following access methods need the resource BAR */
	offset = mtcr_sysfs_get_offset(domain, bus, dev, func);
	if (offset == -1 && !domain)
		offset = mtcr_procfs_get_offset(bus, dev, func);
	if (offset == -1)
		goto access_config;

	sprintf(pdbuf, "/proc/bus/pci/%4.4x:%2.2x/%2.2x.%1.1x",
		domain, bus, dev, func);

	if (!mtcr_mmap(mf, pdbuf, offset, 1))
		return mf;

	if (!domain) {
		sprintf(pbuf, "/proc/bus/pci/%2.2x/%2.2x.%1.1x",
			bus, dev, func);
		if (!mtcr_mmap(mf, pbuf, offset, 1))
			return mf;
	}

#if CONFIG_USE_DEV_MEM
	/* Non-portable, but helps some systems */
	if (!mtcr_mmap(mf, "/dev/mem", offset, 0))
		return mf;
#endif

access_config:
#if CONFIG_ENABLE_PCICONF && CONFIG_ENABLE_PCICONF
	strerror_r(errno, errbuf, sizeof errbuf);
	fprintf(stderr,
		"Warning: memory access to device %s failed: %s.\n"
		"Warning: Fallback on IO: much slower, and unsafe if device in use.\n",
		name, errbuf);
#endif

access_config_forced:

    // Cleanup the mfile struct from any previous garbage.
    memset(mf, 0, sizeof(mfile));

    sprintf(cbuf, "/sys/bus/pci/devices/%4.4x:%2.2x:%2.2x.%1.1x/config",
		domain, bus, dev, func);
	if (!mtcr_open_config(mf, cbuf))
		return mf;

	sprintf(pdbuf, "/proc/bus/pci/%4.4x:%2.2x/%2.2x.%1.1x",
		domain, bus, dev, func);
	if (!mtcr_open_config(mf, pdbuf))
		return mf;

	if (!domain) {
		sprintf(pbuf, "/proc/bus/pci/%2.2x/%2.2x.%1.1x",
			bus, dev, func);
		if (!mtcr_open_config(mf, pdbuf))
			return mf;
	}

open_failed:
        err = errno;
        free(mf);
        errno = err;
        return NULL;
}
#endif

mfile *mopend(const char *name, int type)
#ifdef MTCR_EXPORT
        ;
#else
{
	if (type != 1) {
		return NULL;
	}
	return mopen(name);
}
#endif

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose(mfile *mf)
#ifdef MTCR_EXPORT
;
#else
{
#if CONFIG_ENABLE_MMAP
  if (mf->ptr)
    munmap(mf->ptr,MTCR_MAP_SIZE);
#endif
  close(mf->fd);
  free(mf);
  return 0;
}
#endif

unsigned char mset_i2c_slave(mfile *mf, unsigned char new_i2c_slave)
#ifdef MTCR_EXPORT
;
#else
{
	(void)mf;
	(void)new_i2c_slave; /* compiler warning */
	fprintf(stderr, "Warning: libmtcr: mset_i2c_slave() is not implemented and has no effect.\n");
    return 0;
}
#endif


int mget_mdevs_flags(mfile *mf, u_int32_t *devs_flags)
#ifdef MTCR_EXPORT
;
#else
{
	(void)mf;
	*devs_flags = MDEVS_TAVOR_CR;
        return 0;
}
#endif

int maccess_reg_mad(mfile *mf, u_int8_t *data)
#ifdef MTCR_EXPORT
;
#else
{
	(void)mf;
	(void)data; /* compiler warning */
	fprintf(stderr, "Warning: libmtcr: maccess_reg_mad() is not implemented and has no effect.\n");
    return -1;
}
#endif

int mos_reg_access(mfile *mf, int reg_access, void *reg_data, u_int32_t cmd_type)
#ifdef MTCR_EXPORT
;
#else
{
	(void)mf;
	(void)reg_data; /* compiler warning */
	(void)cmd_type; /* compiler warning */
	(void)reg_access; /* compiler warning */
	fprintf(stderr, "Warning: libmtcr: maccess_reg_mad() is not implemented and has no effect.\n");
    return -1;
}
#endif

#ifdef __cplusplus
}
#endif

#define DEV_MST_EXAMPLE1 "mthca0"
#define DEV_MST_EXAMPLE2 "03:00.0"


#endif
