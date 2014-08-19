/*
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
 *  mtcr_ul.c - Mellanox Hardware Access implementation
 *
 */


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

#define MTCR_MAP_SIZE 0x100000

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include <unistd.h>

#include <netinet/in.h>
#include <endian.h>
#include <byteswap.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/file.h>


#if CONFIG_ENABLE_MMAP
#include <sys/mman.h>
#include <sys/pci.h>
#include <sys/ioctl.h>
#endif

#include <mtcr.h>
#include "tools_utils.h"
#include "mtcr_int_defs.h"
#include "mtcr_ib.h"
#include "packets_layout.h"
#include "mtcr_tools_cif.h"

#ifdef MST_UL_ICMD
#include "mtcr_icmd_cif.h"
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

struct pcicr_context {
    int              fd;
    void            *ptr;
    int              connectx_flush; /* For ConnectX/ConnectX3 */
    int              need_flush; /* For ConnectX/ConnectX3 */
};

struct pciconf_context {
    int              fd;
};

/*
 * Lock file section:
 *
 * in order to support concurrency on both MEMORY/CONFIG_CYCLES access methods
 * there is need for a sync mechanism between mtcr_ul using processes
 *
 * solution: each mfile obj shall contain a file descriptor linked to a unique, device determined file
 *           which will be used as a lock for the critical sections in read/write operations.
 *           these lock files will be created per device (dbdf format) AND per interface (memory/configuration cycles).
 */

#define LOCK_FILE_DIR "/tmp/mstflint_lockfiles"
#define LOCK_FILE_FORMAT "/tmp/mstflint_lockfiles/%04x:%02x:%02x.%x_%s"
// lockfile example : /tmp/mstflint_lockfiles/0000:0b:00.0_config
//                    /tmp/mstflint_lockfiles/0000:0b:00.0_mem
// general format : /tmp/mstflint_lockfiles/<domain:bus:device.function>_<config|mem>
#define CHECK_LOCK(rc) \
    if(rc) {\
        return rc;\
    }

#define MAX_RETRY_CNT 4096
static int _flock_int(int fdlock, int operation) {
    int cnt = 0;
    if (fdlock == 0) { // in case we failed to create the lock file we ignore the locking mechanism
        return 0;
    }
    do {
        if (flock(fdlock, operation | LOCK_NB) == 0) {
            return 0;
        } else if(errno != EWOULDBLOCK){
            break; // BAD! lock/free failed
        }
        if ((cnt & 0xf) == 0) {// sleep every 16 retries
            usleep(1);
        }
        cnt++;
    } while (cnt < MAX_RETRY_CNT);
    perror("failed to perform lock operation.");
    return -1;

}

static int _create_lock(mfile* mf, unsigned domain, unsigned bus, unsigned dev, unsigned func, mtcr_access_method_t access)
{
    char fname[64] = {0};
    int rc;
    snprintf(fname, 64,LOCK_FILE_FORMAT, domain, bus, dev, func, access == MTCR_ACCESS_CONFIG ? "config" : "mem");
    rc = mkdir ("/tmp", 0777);
    if (rc && errno != EEXIST) {
        goto cl_clean_up;
    }

    rc = mkdir(LOCK_FILE_DIR, 0777);
    if (rc && errno != EEXIST) {
        goto cl_clean_up;
    }

    int fd = open(fname, O_RDONLY | O_CREAT, 0777);
    if (fd < 0) {
        goto cl_clean_up;
    }
    mf->fdlock = fd;
    return 0;

cl_clean_up:
    fprintf(stderr, "Warrning: Failed to create lockfile: %s (parallel access not supported)\n" ,fname);
    return 0;
}
/*End of Lock file section */

static int _extract_dbdf_from_full_name(const char *name, unsigned* domain, unsigned* bus, unsigned* dev, unsigned* func)
{
    if (sscanf(name, "/sys/bus/pci/devices/%4x:%2x:%2x.%d/resource0", domain, bus, dev, func) == 4) {
        return 0;
    } else if (sscanf(name, "/sys/bus/pci/devices/%4x:%2x:%2x.%d/config", domain, bus, dev, func) == 4) {
        return 0;
    } else if (sscanf(name, "/proc/bus/pci/%4x:%2x/%2x.%d", domain, bus, dev, func) == 4) {
        return 0;
    } else if (sscanf(name, "/proc/bus/pci/%2x/%2x.%d", bus, dev, func) == 3) {
        *domain = 0;
        return 0;
    }
    // failed to extract dbdf format from name
    errno = EINVAL;
    return -1;
}

static int mtcr_connectx_flush(void *ptr, int fdlock)
{
    u_int32_t value;
    int rc;
    rc = _flock_int(fdlock, LOCK_EX); CHECK_LOCK(rc);
    *((u_int32_t *)((char *)ptr + 0xf0380)) = 0x0;
    do {
        asm volatile ("":::"memory");
        value = __be32_to_cpu(*((u_int32_t *)((char *)ptr + 0xf0380)));
    } while(value);
    rc = _flock_int(fdlock, LOCK_UN); CHECK_LOCK(rc)
    return 0;
}

int mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
    return mf->mread4(mf,offset,value);
}

int mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
    return mf->mwrite4(mf,offset,value);
}

// TODO: Verify change 'data' type from void* to u_in32_t* does not mess up things
static int
mread_chunk_as_multi_mread4(mfile *mf, unsigned int offset, u_int32_t* data, int length)
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
mwrite_chunk_as_multi_mwrite4(mfile *mf, unsigned int offset, u_int32_t* data, int length)
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

/*
* Return values:
* 0:  OK
* <0: Error
* 1 : Device does not support memory access
*
*/
static
int mtcr_check_signature(mfile *mf)
{
    unsigned signature;
    int rc;
    char* connectx_flush = getenv("CONNECTX_FLUSH");
    rc = mread4(mf, 0xF0014, &signature);
    if (rc != 4) {
        if (!errno)
            errno = EIO;
        return -1;
    }

    switch (signature) {
    case 0xbad0cafe:  /* secure host mode device id */
        return 0;
    case 0xbadacce5:  /* returned upon mapping the UAR bar */
    case 0xffffffff:  /* returned when pci mem access is disabled (driver down) */
        return 1;
    }

    switch (signature & 0xffff) {
    case 0x190 : /* 400 */
    case 0x1f5 :
    case 0x1f7 :
        if (connectx_flush == NULL || strcmp(connectx_flush, "0")) {
            if ((signature == 0xa00190         ||
                        (signature & 0xffff) == 0x1f5  ||
                        (signature & 0xffff) == 0x1f7)    && mf->access_type == MTCR_ACCESS_MEMORY) {
                struct pcicr_context* ctx = mf->ctx;
                ctx->connectx_flush = 1;
                if (mtcr_connectx_flush(ctx->ptr, mf->fdlock)) {
                    return -1;
                }
            }
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
 *  7:3 = slot
 *  2:0 = function
 */
#define PCI_DEVFN(slot,func)    ((((slot) & 0x1f) << 3) | ((func) & 0x07))
#define PCI_SLOT(devfn)     (((devfn) >> 3) & 0x1f)
#define PCI_FUNC(devfn)     ((devfn) & 0x07)

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

//
// PCI MEMORY ACCESS FUNCTIONS
//

static
int mtcr_pcicr_mclose(mfile *mf)
{
    struct pcicr_context* ctx = mf->ctx;
    if (ctx) {
        if (ctx->ptr) {
            munmap(ctx->ptr,MTCR_MAP_SIZE);
        }

        if (ctx->fd != -1) {
            close(ctx->fd);
        }
        free(ctx);
        mf->ctx = NULL;
    }

    return 0;
}

static
int mtcr_mmap(struct pcicr_context *mf, const char *name, off_t off, int ioctl_needed)
{
    int err;
    /*
    static const char sysbuspcidevices[] = "/sys/bus/pci/devices/";
    // Enable PCI device before mmapping it
    // this allows to flash a device even if mlx4_core fails to load with some kernels.
    if (!strncmp(name, sysbuspcidevices, sizeof(sysbuspcidevices)-1)) {
        // Accessing through sysfs: need to enable PCI device.
        // We need to write 1 to 'enable' file located in
        // parent dir for 'name'
        int fd;
        char fname[4096];
        int i = strrchr(name, '/') - name;  //always ok
        if (i + sizeof("enable") >= sizeof(fname)) {
            return -1;
            }
        strncpy(fname, name, i+1);
        strcpy(fname + i + 1, "enable");

        fd = open(fname, O_WRONLY | O_SYNC);
        if (fd < 0) {
            return -1;
            }
        i = write(fd, "1", 1);
        err = errno;
        close(fd);
        errno = err;
        if (1 != i) {
            return -1;
            }
        }
     */
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

    return 0;
}

int mtcr_pcicr_mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
    struct pcicr_context *ctx = mf->ctx;

    if (offset >= MTCR_MAP_SIZE) {
        errno = EINVAL;
        return 0;
    }
    if (ctx->need_flush) {
        if (mtcr_connectx_flush(ctx->ptr, mf->fdlock)) {
            return 0;
        }
        ctx->need_flush = 0;
    }
    *value = __be32_to_cpu(*((u_int32_t *)((char *)ctx->ptr + offset)));
    return 4;
}

int mtcr_pcicr_mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
    struct pcicr_context *ctx = mf->ctx;

    if (offset >= MTCR_MAP_SIZE) {
        errno = EINVAL;
        return 0;
    }
    *((u_int32_t *)((char *)ctx->ptr + offset)) = __cpu_to_be32(value);
    ctx->need_flush = ctx->connectx_flush;
    return 4;
}

static
int mtcr_pcicr_open(mfile *mf, const char *name, off_t off, int ioctl_needed)
{
    int rc;
    struct pcicr_context *ctx;
    mf->access_type   = MTCR_ACCESS_MEMORY;

    mf->mread4        = mtcr_pcicr_mread4;
    mf->mwrite4       = mtcr_pcicr_mwrite4;
    mf->mread4_block  = mread_chunk_as_multi_mread4;
    mf->mwrite4_block = mwrite_chunk_as_multi_mwrite4;
    mf->mclose        = mtcr_pcicr_mclose;

    ctx = (struct pcicr_context*)malloc(sizeof(struct pcicr_context));
    if (!ctx)
        return 1;

    ctx->ptr = NULL;
    ctx->fd = -1;
    ctx->connectx_flush = 0;
    ctx->need_flush = 0;

    mf->ctx = ctx;

    rc = mtcr_mmap(ctx, name, off, ioctl_needed);
    if (rc) {
        goto end;
    }

    rc = mtcr_check_signature(mf);

end:
    if (rc) {
        mtcr_pcicr_mclose(mf);
    }

    return rc;
}


//
// PCI CONF ACCESS FUNCTIONS
//


#if CONFIG_ENABLE_PCICONF

int mtcr_pciconf_mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
    struct pciconf_context *ctx = mf->ctx;
    int rc;
    offset = __cpu_to_le32(offset);
    rc = _flock_int(mf->fdlock, LOCK_EX);
    if (rc) {
        goto pciconf_read_cleanup;
    }
    rc=pwrite(ctx->fd, &offset, 4, 22*4);
    if (rc < 0) {
        perror("write offset");
        goto pciconf_read_cleanup;
    }
    if (rc != 4) {
        rc = 0;
        goto pciconf_read_cleanup;
    }

    rc = pread(ctx->fd, value, 4, 23*4);
    if (rc < 0) {
        perror("read value");
        goto pciconf_read_cleanup;
    }
    *value = __le32_to_cpu(*value);
pciconf_read_cleanup:
    _flock_int(mf->fdlock, LOCK_UN);
    return rc;
}

int mtcr_pciconf_mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
    struct pciconf_context *ctx = mf->ctx;
    int rc;
    offset = __cpu_to_le32(offset);
    rc = _flock_int(mf->fdlock, LOCK_EX);
    if (rc) {
        goto pciconf_write_cleanup;
    }
    rc = pwrite(ctx->fd, &offset, 4, 22*4);
    if (rc < 0) {
        perror("write offset");
        goto pciconf_write_cleanup;
    }
    if (rc != 4) {
        rc = 0;
        goto pciconf_write_cleanup;
    }
    value = __cpu_to_le32(value);
    rc = pwrite(ctx->fd, &value, 4, 23*4);
    if (rc < 0) {
        perror("write value");
        goto pciconf_write_cleanup;
    }
pciconf_write_cleanup:
    _flock_int(mf->fdlock, LOCK_UN);
    return rc;
}

static
int mtcr_pciconf_mclose(mfile *mf)
{
    struct pciconf_context *ctx = mf->ctx;
    unsigned int word;

    if (ctx) {
        mread4(mf, 0xf0014, &word);
        if (ctx->fd != -1) {
            close(ctx->fd);
        }
        free(ctx);
        mf->ctx = NULL;
    }

    return 0;
}

static
int mtcr_pciconf_open(mfile *mf, const char *name)
{
    unsigned signature;
    int err;
    int rc;
    struct pciconf_context *ctx;

    mf->access_type   = MTCR_ACCESS_CONFIG;

    mf->mread4        = mtcr_pciconf_mread4;
    mf->mwrite4       = mtcr_pciconf_mwrite4;
    mf->mread4_block  = mread_chunk_as_multi_mread4;
    mf->mwrite4_block = mwrite_chunk_as_multi_mwrite4;
    mf->mclose        = mtcr_pciconf_mclose;

    ctx = (struct pciconf_context*)malloc(sizeof(struct pciconf_context));
    if (!ctx)
        return 1;

    mf->ctx = ctx;

    ctx->fd = -1;
    ctx->fd = open(name, O_RDWR | O_SYNC);
    if (ctx->fd < 0)
        return -1;

    /* Kernels before 2.6.12 carry the high bit in each byte
     * on <device>/config writes, overriding higher bits.
     * Make sure the high bit is set in some signature bytes,
     * to catch this. */
    /* Do this test before mtcr_check_signature,
       to avoid system failure on access to an illegal address. */
    signature = 0xfafbfcfd;

    rc = _flock_int(mf->fdlock, LOCK_EX);
    if (rc) {
        goto end;
    }

    rc = pwrite(ctx->fd, &signature, 4, 22*4);
    if (rc != 4) {
        _flock_int(mf->fdlock, LOCK_UN);
        rc = -1;
        goto end;
    }

    rc = pread(ctx->fd, &signature, 4, 22*4);
    _flock_int(mf->fdlock, LOCK_UN);
    if (rc != 4) {
        rc = -1;
        goto end;
    }

    if (signature != 0xfafbfcfd) {
        rc = -1;
        errno = EIO;
        goto end;
    }

    rc = mtcr_check_signature(mf);
    if (rc) {
        rc = -1;
        goto end;
    }
end:
    if (rc) {
        err = errno;
        mtcr_pciconf_mclose(mf);
        errno = err;
    }
    return rc;
}
#else
static
int mtcr_pciconf_open(mfile *mf, const char *name)
{
    return -1;
}
#endif

//
// IN-BAND ACCESS FUNCTIONS
//


static
int mtcr_inband_open(mfile* mf, const char* name)
{

#ifndef NO_INBAND
    mf->access_type   = MTCR_ACCESS_INBAND;
    mf->mread4        = mib_read4;
    mf->mwrite4       = mib_write4;
    mf->mread4_block  = mib_readblock;
    mf->mwrite4_block = mib_writeblock;
    mf->maccess_reg   = mib_acces_reg_mad;
    mf->mclose        = mib_close;

    return mib_open(name,mf,0);

#else
    (void) name;
    (void) mf;
    errno = ENOSYS;
    return -1;
#endif
}



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

    if (sscanf(name, "lid-%x", &tmp) == 1  ||
        sscanf(name, "ibdr-%x", &tmp) == 1 ||
        strstr(name, "lid-") != 0 || strstr(name, "ibdr-") != 0) {
        *force = 1;
        return MTCR_ACCESS_INBAND;
    }


    if (sscanf(name, "mthca%x", &tmp) == 1 ||
        sscanf(name, "mlx4_%x", &tmp) == 1 ||
        sscanf(name, "mlx5_%x", &tmp) == 1) {
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
#ifdef __aarch64__
    // on ARM processors MMAP not supported
    return MTCR_ACCESS_CONFIG;
#else
    return MTCR_ACCESS_MEMORY;
#endif
}
#endif

int mread4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len)
{
    return mread_chunk_as_multi_mread4(mf, offset, data, byte_len);
}

int mwrite4_block (mfile *mf, unsigned int offset, u_int32_t* data, int byte_len)
{
    return mwrite_chunk_as_multi_mwrite4(mf, offset, data, byte_len);
}

int msw_reset(mfile *mf)
{
    (void)mf; /* Warning */
    return -1;
}

int mdevices(char *buf, int len, int mask)
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
        sz = strlen(dir->d_name);
        if (sz > 4 && strcmp(dir->d_name + sz - 4, "00.0")) {
        // Skip virtual functions
            continue;
        }
        sprintf(fname, "/sys/bus/pci/devices/%s/vendor", dir->d_name);
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

static
int read_pci_config_header(u_int16_t domain, u_int8_t bus, u_int8_t dev, u_int8_t func, u_int8_t data[0x40])
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

dev_info* mdevices_info(int mask, int* len)
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

    if ( rc <= 0 ) {
        len = 0;
        return NULL;
    }
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

        // set pci conf device
        snprintf(dev_info_arr[i].pci.conf_dev, sizeof(dev_info_arr[i].pci.conf_dev), "/sys/bus/pci/devices/%04x:%02x:%02x.%x/config", domain, bus,dev, func);
        //Copy to dev_name as default device
        snprintf(dev_info_arr[i].dev_name, sizeof(dev_info_arr[i].dev_name), "/sys/bus/pci/devices/%04x:%02x:%02x.%x/config", domain, bus,dev, func);

next:
        dev_name += strlen(dev_name) + 1;
    }

    free(devs);
    *len = rc;
    return dev_info_arr;
}


void mdevices_info_destroy(dev_info* dev_info, int len)
{
    (void)len;
    if (dev_info)
        free(dev_info);
}

mfile *mopen(const char *name)
{
    mfile *mf;
    off_t offset;
    unsigned domain = 0, bus = 0, dev = 0, func = 0;
    mtcr_access_method_t access;
    int force;
    char rbuf[] = "/sys/bus/pci/devices/XXXX:XX:XX.X/resource0";
    char cbuf[] = "/sys/bus/pci/devices/XXXX:XX:XX.X/config";
    char pdbuf[] = "/proc/bus/pci/XXXX:XX/XX.X";
    char pbuf[] = "/proc/bus/pci/XX/XX.X";
    char errbuf[4048]="";
    int err;
    int rc;

    if (geteuid() != 0) {
    	errno = EACCES;
    	return NULL;
    }
    mf = (mfile *)malloc(sizeof(mfile));
    if (!mf)
        return NULL;

    memset(mf, 0, sizeof(mfile));
    mf->dev_name = strdup(name);
    if (!mf->dev_name)
        goto open_failed;

    access = mtcr_parse_name(name, &force, &domain, &bus, &dev, &func);
    if (access == MTCR_ACCESS_ERROR)
        goto open_failed;

    if (access == MTCR_ACCESS_CONFIG || access == MTCR_ACCESS_MEMORY) {
        // allocate lock to sync between parallel cr space requests (CONF/MEMORY only)
        if (force) {
            // need to extract the dbdf format from the full name
            if (_extract_dbdf_from_full_name(name, &domain, &bus, &dev, &func)){
                goto open_failed;
            }
        }
        if (_create_lock(mf, domain, bus, dev, func , access)) {
            goto open_failed;
        }
    }
    if (force) {
        switch (access) {
        case MTCR_ACCESS_CONFIG:
            rc = mtcr_pciconf_open(mf, name);
            break;
        case MTCR_ACCESS_MEMORY:
            rc = mtcr_pcicr_open(mf, name, 0, 0);
            break;
        case MTCR_ACCESS_INBAND:
            rc = mtcr_inband_open(mf, name);
            break;
        default:
            goto open_failed;
        }

        if (0 == rc) {
            return mf;
        } else {
            goto open_failed;
        }
    }

    if (access == MTCR_ACCESS_CONFIG)
        goto access_config_forced;

    sprintf(rbuf, "/sys/bus/pci/devices/%4.4x:%2.2x:%2.2x.%1.1x/resource0",
        domain, bus, dev, func);

    rc = mtcr_pcicr_open(mf, rbuf, 0, 0);
    if (rc == 0) {
        return mf;
    } else if (rc == 1) {
        goto access_config_forced;
    }

    /* Following access methods need the resource BAR */
    offset = mtcr_sysfs_get_offset(domain, bus, dev, func);
    if (offset == -1 && !domain)
        offset = mtcr_procfs_get_offset(bus, dev, func);
    if (offset == -1)
        goto access_config;

    sprintf(pdbuf, "/proc/bus/pci/%4.4x:%2.2x/%2.2x.%1.1x",
        domain, bus, dev, func);
    rc = mtcr_pcicr_open(mf, pdbuf, offset, 1);
    if (rc == 0) {
        return mf;
    } else if (rc == 1) {
        goto access_config;
    }

    rc = mtcr_pcicr_open(mf, pdbuf, offset, 1);
    if (rc == 0) {
        return mf;
    } else if (rc == 1) {
        goto access_config;
    }

    if (!domain) {
        sprintf(pbuf, "/proc/bus/pci/%2.2x/%2.2x.%1.1x",
            bus, dev, func);
        rc = mtcr_pcicr_open(mf, pbuf, offset, 1);
        if (rc == 0) {
            return mf;
        } else if (rc == 1) {
            goto access_config;
        }
    }

#if CONFIG_USE_DEV_MEM
    /* Non-portable, but helps some systems */
    if (!mtcr_pcicr_open(mf, "/dev/mem", offset, 0))
        return mf;
#endif

access_config:
#if CONFIG_ENABLE_PCICONF && CONFIG_ENABLE_PCICONF
    strerror_r(errno, errbuf, sizeof errbuf);
    fprintf(stderr,
            "Warning: memory access to device %s failed: %s. Switching to PCI config access.\n",
            name, errbuf);
#endif

access_config_forced:

    sprintf(cbuf, "/sys/bus/pci/devices/%4.4x:%2.2x:%2.2x.%1.1x/config",
        domain, bus, dev, func);
    if (!mtcr_pciconf_open(mf, cbuf))
        return mf;

    sprintf(pdbuf, "/proc/bus/pci/%4.4x:%2.2x/%2.2x.%1.1x",
        domain, bus, dev, func);
    if (!mtcr_pciconf_open(mf, pdbuf))
        return mf;

    if (!domain) {
        sprintf(pbuf, "/proc/bus/pci/%2.2x/%2.2x.%1.1x",
            bus, dev, func);
        if (!mtcr_pciconf_open(mf, pdbuf))
            return mf;
    }

open_failed:
        err = errno;
        mclose(mf);
        errno = err;
        return NULL;
}


mfile *mopend(const char *name, int type)
{
    if (type != 1) {
        return NULL;
    }
    return mopen(name);
}

int mclose(mfile *mf)
{
    if (mf != NULL){
        if (mf->mclose != NULL && mf->ctx != NULL) {
            #ifdef MST_UL_ICMD
            // close icmd if if needed
            if (mf->icmd.icmd_opened) {
                icmd_close(mf);
            }
            #endif
            mf->mclose(mf);
        }
        if (mf->dev_name) {
            free(mf->dev_name);
        }
        if (mf->fdlock) {
            close(mf->fdlock);
        }
        free(mf);
    }
    return 0;
}

mfile *mopen_fw_ctx(void* fw_cmd_context, void* fw_cmd_func)
{
	// not implemented
    TOOLS_UNUSED(fw_cmd_context);
    TOOLS_UNUSED(fw_cmd_func);
	return NULL;
}

unsigned char mset_i2c_slave(mfile *mf, unsigned char new_i2c_slave)
{
    (void)mf;
    (void)new_i2c_slave; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: mset_i2c_slave() is not implemented and has no effect.\n");
    return 0;
}


int mget_mdevs_flags(mfile *mf, u_int32_t *devs_flags)
{
    switch (mf->access_type) {
    case MTCR_ACCESS_INBAND: *devs_flags = MDEVS_IB; break;
    case MTCR_ACCESS_MEMORY:
    case MTCR_ACCESS_CONFIG: *devs_flags = MDEVS_TAVOR_CR; break;
    default:
        return -1;
    }
    return 0;
}

int mget_mdevs_type(mfile *mf, u_int32_t *mtype)
{
    if (mf == NULL || mtype == NULL) {
        errno = EINVAL;
        return 1;
    }

    *mtype = mf->access_type;
    return 0;
}


#define IBDR_MAX_NAME_SIZE 128
#define BDF_NAME_SIZE 12
#define DEV_DIR_MAX_SIZE 128
static
int get_inband_dev_from_pci(char* inband_dev, char* pci_dev)
{
    unsigned domain = 0, bus = 0, dev = 0, func = 0;
    int force = 0;
    enum mtcr_access_method access;
    DIR* d;
    struct dirent *dir;
    char dirname[DEV_DIR_MAX_SIZE], subdirname[DEV_DIR_MAX_SIZE], linkname[DEV_DIR_MAX_SIZE];
    int found = 0;

    access = mtcr_parse_name(pci_dev, &force, &domain, &bus, &dev, &func);

    strcpy(dirname, "/sys/class/infiniband");
    d = opendir(dirname);
    if (d == NULL) {
        errno = ENODEV;
        return -2;
    }
  
    while ((dir = readdir(d)) != NULL) {
        unsigned curr_domain = 0, curr_bus = 0, curr_dev = 0, curr_func = 0;
        int curr_force = 0, link_size;
        if (dir->d_name[0] == '.') {
            continue;
        }
        sprintf(subdirname, "%s/%s/device", dirname, dir->d_name);
        link_size = readlink(subdirname, linkname, DEV_DIR_MAX_SIZE);
        access = mtcr_parse_name(&linkname[link_size - BDF_NAME_SIZE], &curr_force, &curr_domain, &curr_bus, &curr_dev, &curr_func);
                 
        if (domain == curr_domain && bus == curr_bus && dev == curr_dev && func == curr_func) {
            sprintf(inband_dev, "ibdr-0,%s,1", dir->d_name);
            found = 1;
            break;
        }
    }

    closedir(d);
    (void)access; // avoid compiler warrnings
    if (found) {
        return 0;
    } else {
        errno = ENODEV;
        return -1;
    }
}

static
int reopen_pci_as_inband(mfile* mf)
{
    int rc;
    char inband_dev[IBDR_MAX_NAME_SIZE];
    rc = get_inband_dev_from_pci(inband_dev, mf->dev_name);
    if (rc) {
        errno = ENODEV;
        return -1;
    }

    mf->mclose(mf);
    free(mf->dev_name);
    mf->dev_name = strdup(inband_dev);

    rc = mtcr_inband_open(mf, inband_dev);
    return rc;
}

int maccess_reg_mad(mfile *mf, u_int8_t *data)
{
    int rc;

    if (mf == NULL || data == NULL) {
        return ME_BAD_PARAMS;
    }

    if (mf->access_type != MTCR_ACCESS_INBAND) {
        // Close current device and re-open as inband
        rc = reopen_pci_as_inband(mf);
        if (rc) {
            errno = ENODEV; // for compatibility untill we change mtcr to use error code
            return ME_REG_ACCESS_UNKNOWN_ERR;
        }
    }

    return mf->maccess_reg(mf, data);
}

int mos_reg_access(mfile *mf, int reg_access, void *reg_data, u_int32_t cmd_type)
{
    (void)mf;
    (void)reg_data; /* compiler warning */
    (void)cmd_type; /* compiler warning */
    (void)reg_access; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: mos_reg_access() is not implemented and has no effect.\n");
    return ME_NOT_IMPLEMENTED;
}

int maccess_reg_cmdif(mfile *mf, reg_access_t reg_access, void *reg_data, u_int32_t cmd_type)
{
    (void)mf;
    (void)reg_data; /* compiler warning */
    (void)cmd_type; /* compiler warning */
    (void)reg_access; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: maccess_reg_cmdif() is not implemented and has no effect.\n");
    return ME_NOT_IMPLEMENTED;
}

static void mtcr_fix_endianness(u_int32_t *buf, int len)
{
    int i;

    for (i = 0; i < (len/4); ++i) {
        buf[i] = __be32_to_cpu(buf[i]);
    }
}

int mread_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len)
{
    int rc;
    rc = mread4_block(mf, offset, (u_int32_t*)data, byte_len);
    mtcr_fix_endianness((u_int32_t*)data, byte_len);
    return rc;

}

int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len)
{
    mtcr_fix_endianness((u_int32_t*)data, byte_len);
    return mwrite4_block(mf, offset, (u_int32_t*)data, byte_len);
}

/*
 * Reg Access Section
 */

#ifndef MST_UL_ICMD
int icmd_send_command(mfile *mf, int opcode, void* data, int data_size, int skip_write) {
    (void)mf;
    (void)opcode; /* compiler warning */
    (void)data; /* compiler warning */
    (void)data_size; /* compiler warning */
    (void)skip_write; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: icmd_send_command() is not implemented and has no effect.\n");
    return ME_NOT_IMPLEMENTED;
}

static int icmd_send_command_int(mfile *mf, int opcode, void* data, int w_data_size, int r_data_size, int skip_write) {
    (void)mf;
    (void)opcode; /* compiler warning */
    (void)data; /* compiler warning */
    (void)w_data_size; /* compiler warning */
    (void)r_data_size; /* compiler warning */
    (void)skip_write; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: icmd_send_command_int() is not implemented and has no effect.\n");
    return ME_NOT_IMPLEMENTED;
}

int icmd_clear_semaphore(mfile *mf) {
    (void)mf; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: icmd_clear_semaphore() is not implemented and has no effect.\n");
    return ME_NOT_IMPLEMENTED;
}
#endif

#define TLV_OPERATION_SIZE 4
#define OP_TLV_SIZE        16
#define REG_TLV_HEADER_LEN 4

enum {
    MAD_CLASS_REG_ACCESS = 1,
};
enum {
    TLV_END       = 0,
    TLV_OPERATION = 1,
    TLV_DR        = 2,
    TLV_REG       = 3,
    TLV_USER_DATA = 4,
};

#define INBAND_MAX_REG_SIZE 44
#define ICMD_MAX_REG_SIZE 236

static int supports_icmd(mfile* mf);
static int supports_tools_cmdif_reg(mfile* mf);
static int init_operation_tlv(struct OperationTlv *operation_tlv, u_int16_t reg_id, u_int8_t method);
static int mreg_send_wrapper(mfile* mf, u_int8_t *data, int r_icmd_size, int w_icmd_size);
static int mreg_send_raw(mfile *mf, u_int16_t reg_id, maccess_reg_method_t method, void *reg_data, u_int32_t  reg_size, u_int32_t r_size_reg, u_int32_t	w_size_reg, int *reg_status);
int mget_max_reg_size(mfile *mf);

// maccess_reg: Do a reg_access for the mf device.
// - reg_data is both in and out
// TODO: When the reg operation succeeds but the reg status is != 0,
//       a specific

int maccess_reg(mfile     *mf,
                u_int16_t  reg_id,
                maccess_reg_method_t reg_method,
                void*      reg_data,
                u_int32_t  reg_size,
                u_int32_t	r_size_reg,
                u_int32_t	w_size_reg,
                int       *reg_status)
{
    int rc;
    if (mf == NULL || reg_data == NULL || reg_status == NULL || reg_size <= 0) {
        return ME_BAD_PARAMS;
    }
    // check register size
    int max_size = mget_max_reg_size(mf);
    if ( max_size != -1 && reg_size > (unsigned int)max_size) {
    	//reg too big
    	return ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT;
    }
#ifndef MST_UL
    // TODO: add specific checks for each FW access method where needed
    if (mf->flags & MDEVS_MLNX_OS){
    	rc = mos_reg_access_raw(mf, reg_id, reg_method, reg_data, reg_size, reg_status);
    } else if ((mf->flags & (MDEVS_IB | MDEVS_FWCTX)) || (mf->flags != MDEVS_IB && (supports_icmd(mf) || supports_tools_cmdif_reg(mf)))) {
    	rc = mreg_send_raw(mf, reg_id, reg_method, reg_data, reg_size, r_size_reg, w_size_reg, reg_status);
    }else {
        return ME_REG_ACCESS_NOT_SUPPORTED;
    }
#else
    if (mf->access_type == MTCR_ACCESS_INBAND || (supports_icmd(mf) || supports_tools_cmdif_reg(mf)) ) {
        	rc = mreg_send_raw(mf, reg_id, reg_method, reg_data, reg_size, r_size_reg, w_size_reg, reg_status);
        }else {
            return ME_REG_ACCESS_NOT_SUPPORTED;
        }
#endif

    if (rc ) {
         return rc;
    } else if (*reg_status) {
        switch (*reg_status) {
        case 1:
            return ME_REG_ACCESS_DEV_BUSY;
        case 2:
            return ME_REG_ACCESS_VER_NOT_SUPP;
        case 3:
            return ME_REG_ACCESS_UNKNOWN_TLV;
        case 4:
            return ME_REG_ACCESS_REG_NOT_SUPP;
        case 5:
            return ME_REG_ACCESS_CLASS_NOT_SUPP;
        case 6:
            return ME_REG_ACCESS_METHOD_NOT_SUPP;
        case 7:
            return ME_REG_ACCESS_BAD_PARAM;
        case 8:
            return ME_REG_ACCESS_RES_NOT_AVLBL;
        case 9:
            return ME_REG_ACCESS_MSG_RECPT_ACK;
        case 0x22:
        	return ME_REG_ACCESS_CONF_CORRUPT;
        case 0x24:
        	return ME_REG_ACCESS_LEN_TOO_SMALL;
        case 0x20:
        	return ME_REG_ACCESS_BAD_CONFIG;
        case 0x21:
        	return ME_REG_ACCESS_ERASE_EXEEDED;
        default:
            return ME_REG_ACCESS_UNKNOWN_ERR;
        }
    }

    return ME_OK;
}


static int init_operation_tlv(struct OperationTlv *operation_tlv, u_int16_t reg_id, u_int8_t method)
{
    memset(operation_tlv, 0, sizeof(*operation_tlv));

    operation_tlv->Type        = TLV_OPERATION;
    operation_tlv->class       = MAD_CLASS_REG_ACCESS;
    operation_tlv->len         = TLV_OPERATION_SIZE;
    operation_tlv->method      = method;
    operation_tlv->register_id = reg_id;
    return 0;
}

///////////////////  Function that sends the register via the correct interface ///////////////////////////

static int mreg_send_wrapper(mfile* mf, u_int8_t *data, int r_icmd_size, int w_icmd_size)
{
    int rc;
    if (mf->access_type == MTCR_ACCESS_INBAND) {//inband access
            rc = maccess_reg_mad(mf, data);
            if (rc) {
                //printf("-E- 2. Access reg mad failed with rc = %#x\n", rc);
                return ME_MAD_SEND_FAILED;
            }
    } else if (supports_icmd(mf)) {
    #if defined(MST_UL) && !defined(MST_UL_ICMD) //ugly hack to avoid compiler warrnings
        if (0) {
            rc = icmd_send_command_int(mf, FLASH_REG_ACCESS, data, w_icmd_size, r_icmd_size, 0);
        }
        // in mstflint we send reg_access via MADS
        rc = maccess_reg_mad(mf, data);
    #else
        rc = icmd_send_command_int(mf, FLASH_REG_ACCESS, data, w_icmd_size, r_icmd_size, 0);
    #endif
        if (rc) {
        	return rc;
        }
    } else if (supports_tools_cmdif_reg(mf)) {
    	rc = tools_cmdif_reg_access(mf, data, w_icmd_size, r_icmd_size);
    	if (rc) {
    		return rc;
    	}
    }else{
        return ME_NOT_IMPLEMENTED;
    }
    return ME_OK;
}


static int mreg_send_raw(mfile *mf, u_int16_t reg_id, maccess_reg_method_t method, void *reg_data, u_int32_t  reg_size,\
							u_int32_t r_size_reg, u_int32_t	w_size_reg, int *reg_status)
{
	//printf("-D- reg_id = %d, reg_size = %d, r_size_reg = %d , w_size_reg = %d \n",reg_id,reg_size,r_size_reg,w_size_reg);
    int mad_rc, cmdif_size = 0;
    struct OperationTlv tlv;
    struct reg_tlv tlv_info;
    u_int8_t buffer[1024];

    init_operation_tlv(&(tlv), reg_id, method);
    // Fill Reg TLV
    memset(&tlv_info, 0, sizeof(tlv_info));
    tlv_info.Type = TLV_REG;
    tlv_info.len  = (reg_size + REG_TLV_HEADER_LEN) >> 2; // length is in dwords

    // Pack the mad

    cmdif_size += OperationTlv_pack(&tlv, buffer);
    cmdif_size += reg_tlv_pack(&tlv_info, buffer + OP_TLV_SIZE);
    //put the reg itself into the buffer
    memcpy(buffer + OP_TLV_SIZE + REG_TLV_HEADER_LEN, reg_data, reg_size);
    cmdif_size += reg_size;

#ifdef _ENABLE_DEBUG_
    	fprintf(stdout, "-I-Tlv's of Data Sent:\n");
        fprintf(stdout, "\tOperation Tlv\n");
        OperationTlv_dump(&tlv, stdout);
    	fprintf(stdout, "\tReg Tlv\n");
        reg_tlv_dump(&tlv_info, stdout);
#endif
    // printf("-D- reg_info.len = |%d, OP_TLV: %d, REG_TLV= %d, cmdif_size = %d\n", reg_info.len, OP_TLV_SIZE, REG_RLV_HEADER_LEN, cmdif_size);
    // update r/w_size_reg with the size of op tlv and reg tlv as we need to read/write them as well
    r_size_reg += OP_TLV_SIZE + REG_TLV_HEADER_LEN;
    w_size_reg += OP_TLV_SIZE + REG_TLV_HEADER_LEN;
	//printf("-D- reg_size = %d, r_size_reg = %d , w_size_reg = %d \n",reg_size,r_size_reg,w_size_reg);

    mad_rc = mreg_send_wrapper(mf, buffer, r_size_reg, w_size_reg);
    // Unpack the mad
    OperationTlv_unpack(&tlv, buffer);
    reg_tlv_unpack(&tlv_info, buffer + OP_TLV_SIZE);
    // copy register back from the buffer
    memcpy(reg_data, buffer + OP_TLV_SIZE + REG_TLV_HEADER_LEN, reg_size);

#ifdef _ENABLE_DEBUG_
    	fprintf(stdout, "-I-Tlv's of Data Recieved:\n");
    	fprintf(stdout, "\tOperation Tlv\n");
        OperationTlv_dump(&tlv, stdout);
    	fprintf(stdout, "\tReg Tlv\n");
        reg_tlv_dump(&tlv_info, stdout);
#endif
    // Check the return value
    *reg_status = tlv.status;
    if (mad_rc) {
    	return mad_rc;
    }
    return ME_OK;
}


#define CIB_HW_ID 511
#define CX4_HW_ID 521
#define SW_IB_HW_ID 583
#define CX3_PRO_HW_ID 0x1F7
#define CX3_HW_ID_REV 0x1f5

#define HW_ID_ADDR 0xf0014

static int supports_icmd(mfile* mf) {
#if !defined(MST_UL_ICMD) && !defined(MST_UL)
	(void)mf; // avoid warnings
	return 0;
#endif
	u_int32_t dev_id;
	mread4(mf,HW_ID_ADDR, &dev_id); // cr might be locked and retured 0xbad0cafe but we dont care we search for device that supports icmd
	switch (dev_id & 0xffff) { // that the hw device id
		case CIB_HW_ID :
		case CX4_HW_ID :
		case SW_IB_HW_ID :
			return 1;
		default:
			break;
	}
   return 0;
}

static int supports_tools_cmdif_reg(mfile* mf) {
	u_int32_t dev_id;
	mread4(mf,HW_ID_ADDR, &dev_id); // cr might be locked and retured 0xbad0cafe but we dont care we search for device that supports tools cmdif
	switch (dev_id & 0xffff) { // that the hw device id
		case CX3_HW_ID_REV : //Cx3
		case CX3_PRO_HW_ID : // Cx3-pro
			if (tools_cmdif_query_dev_cap(mf, 0, NULL) == ME_OK) {
				return 1;
			}
			break;
		default:
			break;
		 }
   return 0;
}


int mget_max_reg_size(mfile *mf) {
    if (mf->access_type == MTCR_ACCESS_INBAND) {
        return INBAND_MAX_REG_SIZE;
    }
    if (supports_icmd(mf)){ // we support icmd and we dont use IB interface -> we use icmd for reg access
    #ifdef MST_UL
        return INBAND_MAX_REG_SIZE;
    #else
        return ICMD_MAX_REG_SIZE;
    #endif
    }
    if (supports_tools_cmdif_reg(mf)) {
        return TOOLS_HCR_MAX_MBOX;
    }
    return 0;
}

/************************************
 * Function: m_err2str
 ************************************/
const char* m_err2str(MError status)
{
   switch(status) {
   case ME_OK:
       return "ME_OK";
   case ME_ERROR:
       return "General error";
   case ME_BAD_PARAMS:
       return "ME_BAD_PARAMS";
   case ME_CR_ERROR:
       return "ME_CR_ERROR";
   case ME_NOT_IMPLEMENTED:
       return "ME_NOT_IMPLEMENTED";
   case ME_SEM_LOCKED:
       return "Semaphore locked";
   case ME_MEM_ERROR:
       return "ME_MEM_ERROR";

   case ME_MAD_SEND_FAILED:
       return "ME_MAD_SEND_FAILED";
   case ME_UNKOWN_ACCESS_TYPE:
       return "ME_UNKOWN_ACCESS_TYPE";
   case ME_UNSUPPORTED_DEVICE:
       return "ME_UNSUPPORTED_DEVICE";

   // Reg access errors
   case ME_REG_ACCESS_BAD_STATUS_ERR:
       return "ME_REG_ACCESS_BAD_STATUS_ERR";
   case ME_REG_ACCESS_BAD_METHOD:
       return "Bad method";
   case ME_REG_ACCESS_NOT_SUPPORTED:
       return "Register access isn't supported by device";
   case ME_REG_ACCESS_DEV_BUSY:
       return "Device is busy";
   case ME_REG_ACCESS_VER_NOT_SUPP:
       return "Version not supported";
   case ME_REG_ACCESS_UNKNOWN_TLV:
       return "Unknown TLV";
   case ME_REG_ACCESS_REG_NOT_SUPP:
       return "Register not supported";
   case ME_REG_ACCESS_CLASS_NOT_SUPP:
       return "Class not supported";
   case ME_REG_ACCESS_METHOD_NOT_SUPP:
       return "Method not supported";
   case ME_REG_ACCESS_BAD_PARAM:
       return "Bad parameter";
   case ME_REG_ACCESS_RES_NOT_AVLBL:
       return "Resource not available";
   case ME_REG_ACCESS_MSG_RECPT_ACK:
       return "Message receipt ack";
   case ME_REG_ACCESS_UNKNOWN_ERR:
       return "Unknown register error";
   case ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT:
       return "Register is too large";
   case ME_REG_ACCESS_CONF_CORRUPT:
	   return "Config Section Corrupted";
   case ME_REG_ACCESS_LEN_TOO_SMALL:
	   return "given register length too small for Tlv";
   case ME_REG_ACCESS_BAD_CONFIG:
	   return "configuration refused";
   case ME_REG_ACCESS_ERASE_EXEEDED:
	   return	"erase count exceeds limit";

   // ICMD access errors
   case ME_ICMD_STATUS_CR_FAIL:
       return "ME_ICMD_STATUS_CR_FAIL";
   case ME_ICMD_STATUS_SEMAPHORE_TO:
       return "ME_ICMD_STATUS_SEMAPHORE_TO";
   case ME_ICMD_STATUS_EXECUTE_TO:
       return "ME_ICMD_STATUS_EXECUTE_TO";
   case ME_ICMD_STATUS_IFC_BUSY:
       return "ME_ICMD_STATUS_IFC_BUSY";
   case ME_ICMD_STATUS_ICMD_NOT_READY:
       return "ME_ICMD_STATUS_ICMD_NOT_READY";
   case ME_ICMD_UNSUPPORTED_ICMD_VERSION:
       return "ME_ICMD_UNSUPPORTED_ICMD_VERSION";
   case ME_ICMD_NOT_SUPPORTED:
       return "ME_REG_ACCESS_ICMD_NOT_SUPPORTED";
   case ME_ICMD_INVALID_OPCODE:
       return "ME_ICMD_INVALID_OPCODE";
   case ME_ICMD_INVALID_CMD:
       return "ME_ICMD_INVALID_CMD";
   case ME_ICMD_OPERATIONAL_ERROR:
       return "ME_ICMD_OPERATIONAL_ERROR";
   case ME_ICMD_BAD_PARAM:
       return "ME_ICMD_BAD_PARAM";
   case ME_ICMD_BUSY:
       return "ME_ICMD_BUSY";
   case ME_ICMD_ICM_NOT_AVAIL:
       return "ME_ICMD_ICM_NOT_AVAIL";
   case ME_ICMD_WRITE_PROTECT:
       return "ME_ICMD_WRITE_PROTECT";
   case ME_ICMD_UNKNOWN_STATUS:
       return "ME_ICMD_UNKNOWN_STATUS";

       // TOOLS HCR access errors
   case ME_CMDIF_BUSY:
	   return "Tools HCR busy";
   case ME_CMDIF_TOUT:
	   return "Tools HCR time out";
   case ME_CMDIF_BAD_OP:
	   return "Operation not supported";
   case ME_CMDIF_NOT_SUPP:
	   return "Tools HCR not supported";
   case ME_CMDIF_BAD_SYS:
	   return "bad system status (driver may be down or Fw does not support this operation)";
   case ME_CMDIF_UNKN_TLV:
       return "Unknown TLV";

    // MAD IFC errors
   case ME_MAD_BUSY:
       return "Temporarily busy. MAD discarded. This is not an error";
   case ME_MAD_REDIRECT:
       return "Redirection. This is not an error";
   case ME_MAD_BAD_VER:
       return "Bad version";
   case ME_MAD_METHOD_NOT_SUPP:
       return "Method not supported";
   case ME_MAD_METHOD_ATTR_COMB_NOT_SUPP:
       return "Method and attribute combination isn't supported";
   case ME_MAD_BAD_DATA:
       return "Bad attribute modifer or field";
   case ME_MAD_GENERAL_ERR:
       return "Unknown MAD error";

   default:
       return "Unknown error code";
   }
}

