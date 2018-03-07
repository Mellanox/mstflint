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

#include <sys/types.h>

#include <err.h>
#include <stdio.h>
#include <sys/agpio.h>
#include <sys/pciio.h>

#include <dev/agp/agpreg.h>
#include <dev/pci/pcireg.h>
#include <sched.h>

#include "mtcr.h"
#include <compatibility.h>
#include <bit_slice.h>
#include <stdlib.h>

#include <unistd.h>

#include "mtcr_icmd_cif.h"
#include "mtcr_tools_cif.h"
#ifndef MST_UL
#include "mtcr_utils.h"
#else
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/param.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/queue.h>
#endif

#include "packets_common.h"
#include "packets_layout.h"
#include <dlfcn.h>
#include <dirent.h>


#define MST_VPD_DFLT_TIMEOUT   2000
#define PCI_VPD_ADDR   0x2
#define PCI_CAP_ID_VPD 0x3
#define PCI_VPD_DATA   0x4




#ifdef MST_UL
#define u64     uint64_t
#define u32     uint32_t
#define u16     uint16_t
#define u8      uint8_t

#define __be64  uint64_t
#define __be32  uint32_t
#define __be16  uint16_t

#define BITS_PER_LONG __LONG_BIT

//#ifndef __be32_to_cpu
//#define __be32_to_cpu(x) ntohl(x)
//#endif
//#ifndef __cpu_to_be32
//#define __cpu_to_be32(x) htonl(x)
//#endif

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


/*
 * Byteswapping
 */
#define cpu_to_be16(x) htobe16(x)
#define cpu_to_be32(x) htobe32(x)
#define cpu_to_be64(x) htobe64(x)
#define be16_to_cpu(x) be16toh(x)
#define be32_to_cpu(x) be32toh(x)
#define be64_to_cpu(x) be64toh(x)

#define _PATH_DEVPCI    "/dev/pci"
#define SLV_ADDRS_NUM 128
#endif //MST_UL





typedef enum {
    Clear_Vsec_Semaphore = 0x1
} adv_opt_t;

void mtcr_connectx_flush(void *ptr)
{
    u_int32_t value;
    *((u_int32_t *) ((char *) ptr + 0xf0380)) = 0x0;
    do {
        asm volatile ("":::"memory");
        value = __be32_to_cpu(*((u_int32_t *) ((char *) ptr + 0xf0380)));
    } while (value);
}

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
        case 0x190: /* Fallthrough 400 */
            if (signature == 0xa00190 && mf->ptr) {
                mf->connectx_flush = 1;
                mtcr_connectx_flush(mf->ptr);
            }
	    return 0;

        case 0x5a44: /* 23108 */
        case 0x6278: /* 25208 */
        case 0x5e8c: /* 24204 */
        case 0x6274: /* 25204 */
            return 0;
        default:
            errno = ENOTTY;
            return -1;
    }
}

#define PCI_CONF_ADDR   (0x00000058)
#define PCI_CONF_DATA   (0x0000005c)
#define MLNX_VENDOR_SPECIFIC_CAP_ID 0x9

/* PCI address space related enum*/
enum {
    PCI_CAP_PTR = 0x34, PCI_HDR_SIZE = 0x40, PCI_EXT_SPACE_ADDR = 0xff,

    PCI_CTRL_OFFSET = 0x4, // for space / semaphore / auto-increment bit
    PCI_COUNTER_OFFSET = 0x8,
    PCI_SEMAPHORE_OFFSET = 0xc,
    PCI_ADDR_OFFSET = 0x10,
    PCI_DATA_OFFSET = 0x14,

    PCI_FLAG_BIT_OFFS = 31,

    PCI_SPACE_BIT_OFFS = 0,
    PCI_SPACE_BIT_LEN = 16,

    PCI_STATUS_BIT_OFFS = 29,
    PCI_STATUS_BIT_LEN = 3,

    PCI_HEADER_OFFS = 0x0, PCI_SUBSYS_OFFS = 0x2c, PCI_CLASS_OFFS = 0x8,
};

/* Mellanox vendor specific enum */
enum {
    CAP_ID = 0x9, IFC_MAX_RETRIES = 0x10000, SEM_MAX_RETRIES = 0x1000
};

/* PCI operation enum(read or write)*/
enum {
    READ_OP = 0, WRITE_OP = 1,
};

int read_config(int fd, struct pcisel *sel, unsigned int reg, uint32_t* data,
        int width)
{
    struct pci_io pi;

    pi.pi_sel = *sel;
    pi.pi_reg = reg;
    pi.pi_width = width;

    if (ioctl(fd, PCIOCREAD, &pi) < 0) {
        errno = EIO;
        return -1;
    }
    //printf("%s:  dev:%d reg=%x width=%d data=%x\n", __FUNCTION__, pi.pi_sel.pc_dev, reg, width, pi.pi_data);
    *data = (pi.pi_data);
    return 0;
}

int write_config(int fd, struct pcisel *sel, unsigned int reg, uint32_t data,
        int width)
{
    struct pci_io pi;

    pi.pi_sel = *sel;
    pi.pi_reg = reg;
    pi.pi_width = width;
    pi.pi_data = data;

    //printf("%s: dev:%d reg:%x width:%d data:%x\n", __FUNCTION__, pi.pi_sel.pc_dev, pi.pi_reg, pi.pi_width, pi.pi_data);
    if (ioctl(fd, PCIOCWRITE, &pi) < 0) {
        errno = EIO;
        return -1;
    }
    return 0;
}



#define WO_REG_ADDR_DATA 0xbadacce5
#define DEVID_OFFSET     0xf0014
#define PCICONF_ADDR_OFF 0x58
#define PCICONF_DATA_OFF 0x5c

static int is_wo_pciconf_gw(mfile* mf)
{
    unsigned offset = DEVID_OFFSET;
    u_int32_t data = 0;
    int rc = write_config(mf->fd, &mf->sel, PCI_CONF_ADDR, (unsigned long) offset, 4);
    if (rc < 0) {
        return 0;
    }
    rc = read_config(mf->fd, &mf->sel, PCI_CONF_ADDR, &data, 4);
    if (rc < 0) {
        return 0;
    }
    //printf("-D- Data: %#x\n", data);
    if ( data == WO_REG_ADDR_DATA) {
        return 1;
    }
    return 0;
}

/*Find PCI Capability*/

/*semaphore*/

/*set addr space*/

/* Read Write new functions (4Bytes, Block)*/
int pci_find_capability(mfile* mf, int cap_id)
{
    unsigned offset;
    unsigned char visited[256] = { 0 }; /* Prevent infinite loops */
    uint32_t reg;
    int ret;
    int curr_cap;

    ret = read_config(mf->fd, &mf->sel, PCI_CAP_PTR, &reg, 4);

    if (ret) {
        return 0;
    }

    offset = ((unsigned char*) &reg)[0];
    while (1) {
        if (offset < PCI_HDR_SIZE || offset > PCI_EXT_SPACE_ADDR) {
            return 0;
        }

        ret = read_config(mf->fd, &mf->sel, offset, &reg, 4);

        if (ret) {

            return 0;
        }

        visited[offset] = 1;
        curr_cap = ((unsigned char*) &reg)[0];
        if (curr_cap == cap_id) {
            return offset;
        }

        offset = ((unsigned char*) &reg)[1];
        if (visited[offset]) {
            return 0;
        }
    }
    return 0;
}

static int _vendor_specific_sem(mfile* mf, int state)
{
    uint32_t lock_val;
    uint32_t counter = 0;
    int retries = 0;
    int ret;
    if (!state) { // unlock
        ret = write_config(mf->fd, &mf->sel,
                mf->vsec_addr + PCI_SEMAPHORE_OFFSET, 0, 4);
        if (ret)
            return ret;
    } else { // lock
        do {
            if (retries > SEM_MAX_RETRIES) {
                return -1;
            }
            // read semaphore untill 0x0
            ret = read_config(mf->fd, &mf->sel,
                    mf->vsec_addr + PCI_SEMAPHORE_OFFSET, &lock_val, 4);
            if (ret)
                return ret;

            if (lock_val) { //semaphore is taken
                retries++;
                msleep(1); // wait for current op to end
                continue;
            }
            //read ticket
            ret = read_config(mf->fd, &mf->sel,
                    mf->vsec_addr + PCI_COUNTER_OFFSET, &counter, 4);
            if (ret)
                return ret;
            //write ticket to semaphore dword
            ret = write_config(mf->fd, &mf->sel,
                    mf->vsec_addr + PCI_SEMAPHORE_OFFSET, counter, 4);
            if (ret)
                return ret;
            // read back semaphore make sure ticket == semaphore else repeat
            ret = read_config(mf->fd, &mf->sel,
                    mf->vsec_addr + PCI_SEMAPHORE_OFFSET, &lock_val, 4);
            if (ret)
                return ret;
            retries++;
        } while (counter != lock_val);
    }
    return 0;
}

static int _wait_on_flag(mfile* mf, u8 expected_val)
{
    int retries = 0;
    int ret;
    uint32_t flag;
    do {
        if (retries > IFC_MAX_RETRIES) {
            return -1;
        }

        ret = read_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_ADDR_OFFSET,
                &flag, 4);
        if (ret)
            return ret;

        flag = EXTRACT(flag, PCI_FLAG_BIT_OFFS, 1);
        retries++;
        if ((retries & 0xf) == 0) { // dont sleep always
            //usleep_range(1,5);
        }
    } while (flag != expected_val);
    return 0;
}

static int _set_addr_space(mfile* mf, u16 space)
{
    // read modify write
    uint32_t val;
    int ret;
    ret = read_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_CTRL_OFFSET, &val,
            4);
    if (ret)
        return ret;
    val = MERGE(val, space, PCI_SPACE_BIT_OFFS, PCI_SPACE_BIT_LEN);
    ret = write_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_CTRL_OFFSET, val,
            4);
    if (ret)
        return ret;
    // read status and make sure space is supported
    ret = read_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_CTRL_OFFSET, &val,
            4);
    if (ret)
        return ret;

    if (EXTRACT(val, PCI_STATUS_BIT_OFFS, PCI_STATUS_BIT_LEN) == 0) {

        return -1;
    }
    return 0;
}

static int _pciconf_rw(mfile* mf, unsigned int offset, uint32_t* data, int rw)
{
    int ret = 0;
    uint32_t address = offset;

    //last 2 bits must be zero as we only allow 30 bits addresses
    if (EXTRACT(address, 30, 2)) {
        return -1;
    }

    address = MERGE(address, (rw ? 1 : 0), PCI_FLAG_BIT_OFFS, 1);
    if (rw == WRITE_OP) {
        // write data
        ret = write_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_DATA_OFFSET,
                *data, 4);
        if (ret)
            return ret;
        // write address
        ret = write_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_ADDR_OFFSET,
                address, 4);
        if (ret)
            return ret;
        // wait on flag
        ret = _wait_on_flag(mf, 0);
    } else {
        // write address
        ret = write_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_ADDR_OFFSET,
                address, 4);
        if (ret)
            return ret;
        // wait on flag
        ret = _wait_on_flag(mf, 1);
        // read data
        ret = read_config(mf->fd, &mf->sel, mf->vsec_addr + PCI_DATA_OFFSET,
                data, 4);
        if (ret)
            return ret;
    }
    return ret;
}

static int _send_pci_cmd_int(mfile* mf, int space, unsigned int offset,
        uint32_t* data, int rw)
{
    int ret = 0;

    // take semaphore
    ret = _vendor_specific_sem(mf, 1);
    if (ret) {
        //printf("-D- Failed to take Semaphore!\n");
        return ret;
    }
    // set address space
    ret = _set_addr_space(mf, space);
    if (ret) {
        //printf("-D- Failed to set space!\n");
        goto cleanup;
    }
    // read/write the data
    ret = _pciconf_rw(mf, offset, data, rw);
    cleanup:
    // clear semaphore
    _vendor_specific_sem(mf, 0);
    return ret;
}

static int _block_op(mfile* mf, int space, unsigned int offset, int size,
        uint32_t* data, int rw)
{
    int i;
    int ret = 0;
    int wrote_or_read = size;
    if (size % 4) {
        return -1;
    }
    // lock semaphore and set address space
    ret = _vendor_specific_sem(mf, 1);
    if (ret) {
        return -1;
    }
    // set address space
    ret = _set_addr_space(mf, space);
    if (ret) {
        wrote_or_read = -1;
        goto cleanup;
    }
    for (i = 0; i < size; i += 4) {
        if (_pciconf_rw(mf, offset + i, &(data[(i >> 2)]), rw)) {
            wrote_or_read = i;
            goto cleanup;
        }
    }
    cleanup: _vendor_specific_sem(mf, 0);
    return wrote_or_read;
}

static int mwrite4_new(mfile* mf, unsigned int offset, uint32_t data)
{
    int ret;

    ret = _send_pci_cmd_int(mf, mf->address_space, offset, &data, WRITE_OP);
    if (ret) {
        return -1;
    }
    return 4;
}

static int mread4_new(mfile* mf, unsigned int offset, uint32_t* data)
{
    int ret;

    ret = _send_pci_cmd_int(mf, mf->address_space, offset, data, READ_OP);
    if (ret) {
        return -1;
    }
    return 4;
}

static int mwrite4_block_new(mfile* mf, unsigned int offset, int size,
        uint32_t* data)
{
    return _block_op(mf, mf->address_space, offset, size, data, WRITE_OP);
}

static int mread4_block_new(mfile* mf, unsigned int offset, int size,
        uint32_t* data)
{
    return _block_op(mf, mf->address_space, offset, size, data, READ_OP);
}

static int vsec_spaces_supported(mfile* mf)
{
    // take semaphore
    int supported = 1;
    int ret = _vendor_specific_sem(mf, 1);
    if (ret) {
        return supported;
    }
    if (_set_addr_space(mf, AS_CR_SPACE) || _set_addr_space(mf, AS_ICMD)
            || _set_addr_space(mf, AS_SEMAPHORE)) {
        supported = 0;
    }
    // clear semaphore
    _vendor_specific_sem(mf, 0);
    return supported;
}

/*
 * End of Capabilities section
 */


/*
 * Open Mellanox Software tools (mst) driver. Device type==INFINIHOST
 * Return valid mfile ptr or 0 on failure
 */

int device_exists(const char* devname);
int mtcr_open_config(mfile *mf, const char *name);


mfile *mopen_int(const char *name, u_int32_t adv_opt)
{
    char* real_name = (char*)name;
#ifndef MST_UL
    int port;
    char* p_cable;
    char tmp_name[512] = {0};
#endif
    int is_cable = 0;
    if (getuid() != 0) {
        errno = EACCES;
        return NULL;
    }
    //printf("%s: open %s\n", __FUNCTION__, name);
#ifndef MST_UL
    if ((p_cable = strstr(name, "_cable")) != 0) {
        strncpy (tmp_name, name, 512);
        tmp_name[p_cable-name] = 0;
        is_cable = 1;
        real_name = tmp_name;

        //printf("-D- splitting name: %s\n", real_name);
        if (strstr(p_cable + 1, "_") != NULL) {
            p_cable += 7;
            if (*p_cable == '\0') {
                port = 0;
            } else {
                //printf("-D- splitting port: %s\n", p_cable);
                port = atoi(p_cable);
            }
        } else {
            port = 0;
        }
    }
#endif
    if (!device_exists(real_name)) {
        errno = ENOENT;
        return NULL;
    }
    mfile *mf = malloc(sizeof(mfile));
    memset(mf, 0, sizeof(mfile));
    if (!mf) {
        return NULL;
    }

    mf->flags = MDEVS_TAVOR_CR;
    if (!mtcr_open_config(mf, real_name)) {
        mf->wo_addr = is_wo_pciconf_gw(mf);
        //printf("-D- is_wo_pciconf_gw: %d\n", mf->wo_addr);
        mf->vsec_addr = pci_find_capability(mf, MLNX_VENDOR_SPECIFIC_CAP_ID);
        mf->vpd_cap_addr = pci_find_capability(mf, PCI_CAP_ID_VPD);
        mf->is_cable = is_cable;
        mf->vsec_supp = 0;
        if (mf->vsec_addr) {
            if (adv_opt & Clear_Vsec_Semaphore) {
                _vendor_specific_sem(mf, 0);
            }
            mf->vsec_supp = vsec_spaces_supported(mf);
            mf->address_space = AS_CR_SPACE;
        }
        //printf("mtcr_open_config Succeeded VSEC_SUPP: %d\n", mf->vsec_supp);
#ifndef MST_UL
        if (mf->is_cable) {
            mf->flags = MDEVS_CABLE;
            mf->dl_context = mtcr_utils_load_dl_ctx(DL_CABLES);
            dl_handle_t* hdl = (dl_handle_t*)mf->dl_context;
            if (!hdl || !hdl->mcables.mcables_open || hdl->mcables.mcables_open(mf, port)) {
                mclose(mf);
                return 0;
            }
        }
#endif
        return mf;
    } else {
        //printf("mtcr_open_config failed\n");
        errno = ENOENT;
        free(mf);
        return NULL;
    }
}

mfile *mopen(const char *name)
{
    return mopen_adv(name, MST_DEFAULT);
}
mfile *mopend(const char *name, int dtype)
{
    (void)dtype;

    return mopen_int(name, 0);
}

mfile *mopen_adv(const char *name, MType mtype)
{
    mfile* mf = mopend(name, MST_TAVOR);
    if (mf) {
        if (mf->tp & mtype) {
            return mf;
        } else {
            errno = EPERM;
            mclose(mf);
            return NULL;
        }
    }
    return mf;
}

mfile* mopen_fw_ctx(void* fw_cmd_context, void* fw_cmd_func, void* extra_data)
{
    (void)fw_cmd_context;
    (void)fw_cmd_func;
    (void)extra_data;

    // not relevant for freebsd
    return NULL;
}

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose(mfile *mf)
{
    if (!mf) {
        return 0;
    }
#ifndef MST_UL
    if (mf->tp == MST_CABLE) {
        int ret = -1;
        CALL_DL_FUNC(mcables, mcables_close, ret, mf);
        if (ret != -1) {
            mtcr_utils_free_dl_ctx(mf->dl_context);
        }
    }
#endif
    //printf("closing\n");
    close(mf->fd);
    //printf("freeing\n");
    free(mf);
    return 0;
}

#if __FreeBSD_version > 700000
int
getsel(const char *str, struct pcisel *selout)
{
    char *ep = strchr(str, '@');
    char *epbase;
    struct pcisel sel;
    unsigned long selarr[4];
    int i;
    //printf("__FreeBSD_version > 700000 detected.\n");

    if (ep == NULL)
    ep = (char *)str;
    else
    ep++;

    epbase = ep;

    if (strncmp(ep, "pci", 3) == 0) {
        ep += 3;
        i = 0;
        do {
            selarr[i++] = strtoul(ep, &ep, 10);
        }while ((*ep == ':' || *ep == '.') && *++ep != '\0' && i < 4);

        if (i > 2)
        sel.pc_func = selarr[--i];
        else
        sel.pc_func = 0;
        sel.pc_dev = selarr[--i];
        sel.pc_bus = selarr[--i];
        if (i > 0)
        sel.pc_domain = selarr[--i];
        else
        sel.pc_domain = 0;
    }
    if (*ep != '\x0' || ep == epbase) {
        return 1;
        //errx(1, "cannot parse selector %s ep:'%s' epbase:%s, %d", str, ep, epbase, *ep);
    }

    *selout = sel;

    return 0;
}
#else
int getsel(const char *str, struct pcisel *selout)
{
    char *ep = strchr(str, '@');
    char *epbase;
    struct pcisel sel;

    //printf("__FreeBSD_version < 700000 detected: %d\n", __FreeBSD_version);

    if (ep == NULL)
        ep = (char *) str;
    else
        ep++;

    epbase = ep;

    if (strncmp(ep, "pci", 3) == 0) {
        ep += 3;
        sel.pc_bus = strtoul(ep, &ep, 0);
        if (!ep || *ep++ != ':') {
            errno = EINVAL;
            return 1;
            //errx(1, "cannot parse selector %s", str);
        }
        sel.pc_dev = strtoul(ep, &ep, 0);
        if (!ep || *ep != ':') {
            sel.pc_func = 0;
        } else {
            ep++;
            sel.pc_func = strtoul(ep, &ep, 0);
        }
        if (*ep == ':')
            ep++;
    }
    if (*ep != '\x0' || ep == epbase) {
        return 1;
        //errx(1, "cannot parse selector %s", str);
    }

    *selout = sel;

    return 0;
}
#endif

int mtcr_open_config(mfile *mf, const char *name)
{
    //char tmp[256];
    //memcpy(&tmp, name, strlen(name)+1);

    //printf("open_config %s %s mf:%p\n", name, _PATH_DEVPCI, mf);

    if (!mf) {
        printf("Internal: Uninitialized mfile\n");
        exit(1);
    }

    mf->fd = open(_PATH_DEVPCI, O_RDWR, 0);
    if (mf->fd < 0) {
        printf("err opening: %s", _PATH_DEVPCI);
        return -1;
    }

    //printf("open_config name:%s fd:%d\n", name, mf->fd);
    int ret = getsel(name, &mf->sel);
    //printf("open_config getsel done %d\n", mf->sel.pc_dev);
    mf->tp = MST_PCICONF;

    return ret;
}


#define MY_DELAY 20

/*
 * Read 4 bytes, return number of succ. read bytes or -1 on failure
 */
int mread4_old(mfile *mf, unsigned int offset, u_int32_t *value)
{
    int rc;
    offset = __cpu_to_le32(offset);
    if (mf->wo_addr) {
        offset |= 0x1;
    }
    rc = write_config(mf->fd, &mf->sel, PCI_CONF_ADDR, (unsigned long) offset,
            4);
    if (rc) {
        return rc;
    }

    rc = read_config(mf->fd, &mf->sel, PCI_CONF_DATA, value, 4);

    if (rc) {
        return rc;
    }

    *value = __le32_to_cpu(*value);
    return 4;
}

int mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
#ifndef MST_UL
    if (mf->tp == MST_CABLE) {
        int rc = 0;
        CALL_DL_FUNC(mcables, mcables_read4, rc, mf, offset, value);
        if (!rc) {
            return 4;
        } else {
            return -1;
        }
    }
#endif
    if (mf->vsec_supp) {
        return mread4_new(mf, offset, value);
    }
    return mread4_old(mf, offset, value);
}

/*
 * HACK- Only to pass freebsd compilation
 */
int mread64(mfile *mf, unsigned int offset, void *data, int length)
{
    (void)mf;
    (void)offset;
    (void)data;
    (void)length;

    return -1;
}

/*
 * HACK- Only to pass freebsd compilation
 */
int mwrite64(mfile *mf, unsigned int offset, void *data, int length)
{
    (void)mf;
    (void)offset;
    (void)data;
    (void)length;

    return -1;
}

//read_config(int fd, struct pcisel *sel, unsigned long reg, int width);
//write_config(mf->fd, int fd, struct pcisel *sel, unsigned long reg, unsigned long data, int width)

/*
 * Write 4 bytes, return number of succ. written bytes or -1 on failure
 */
int mwrite4_old(mfile *mf, unsigned int offset, u_int32_t value)
{
    int rc;

    offset = __cpu_to_le32(offset);
    value = __cpu_to_le32(value);
    if (mf->wo_addr) {
        rc = write_config(mf->fd, &mf->sel, PCI_CONF_DATA, (unsigned long) value, 4);
        if (rc) {
            return rc;
        }
        rc = write_config(mf->fd, &mf->sel, PCI_CONF_ADDR, (unsigned long) offset, 4);
        if (rc) {
            return rc;
        }
    } else {
        rc = write_config(mf->fd, &mf->sel, PCI_CONF_ADDR, (unsigned long) offset, 4);
        if (rc) {
            return rc;
        }
        rc = write_config(mf->fd, &mf->sel, PCI_CONF_DATA, (unsigned long) value, 4);
        if (rc) {
            return rc;
        }
    }

    return 4;
}

int mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
#ifndef MST_UL
    if (mf->tp == MST_CABLE) {int rc = 0;
        CALL_DL_FUNC(mcables, mcables_write4, rc, mf, offset, value);
        if (!rc) {
            return 4;
        } else {
            return -1;
        }
    }
#endif
    if (mf->vsec_supp) {
        return mwrite4_new(mf, offset, value);
    }
    return mwrite4_old(mf, offset, value);
}
//////////// NEW   ////////////////////

static int mread_chunk_as_multi_mread4(mfile *mf, unsigned int offset,
        void *data, int length)
{
    int i;
    if (length % 4) {
        return EINVAL;
    }
    for (i = 0; i < length; i += 4) {
        u_int32_t value;
        if (mread4(mf, offset + i, &value) != 4) {
            return -1;
        }
        memcpy((char*) data + i, &value, 4);
    }
    return length;
}

static int mwrite_chunk_as_multi_mwrite4(mfile *mf, unsigned int offset,
        void *data, int length)
{
    int i;
    if (length % 4) {
        return EINVAL;
    }
    for (i = 0; i < length; i += 4) {
        u_int32_t value;
        memcpy(&value, (char*) data + i, 4);
        if (mwrite4(mf, offset + i, value) != 4) {
            return -1;
        }
    }
    return length;
}

int mread4_block(mfile *mf, unsigned int offset, u_int32_t* data, int byte_len)
{
#ifndef MST_UL
    int rc = byte_len;

    if (mf->tp == MST_CABLE) {
        int ret = 0;
        CALL_DL_FUNC(mcables, mcables_read4_block, ret, mf, offset, data, byte_len);
        if ( ret != 0 ) {
            rc -= ret; // Return less than byte_len to ensure error in reading
        }
        return rc;
    }
#endif
    if (mf->vsec_supp) {
        int rc = mread4_block_new(mf, offset, byte_len, data);
        //printf("-D- MREAD BLOCK LEN: %d, RC: %d\n", byte_len, rc);
        return rc;
    }
    return mread_chunk_as_multi_mread4(mf, offset, data, byte_len);
}

int mwrite4_block(mfile *mf, unsigned int offset, u_int32_t* data, int byte_len)
{
#ifndef MST_UL
    int rc = byte_len;

    if (mf->tp == MST_CABLE) {
        int ret = 0;
        CALL_DL_FUNC(mcables, mcables_write4_block, ret, mf, offset, data, byte_len);
        if ( ret != 0 ) {
            rc -= ret; // Return less than byte_len to ensure error in reading
        }
        return rc;
    }
#endif
    if (mf->vsec_supp) {
        return mwrite4_block_new(mf, offset, byte_len, data);
    }
    return mwrite_chunk_as_multi_mwrite4(mf, offset, data, byte_len);
}

int msw_reset(mfile *mf)
{
    (void)mf;

    return -1;
}

int mhca_reset(mfile *mf)
{
    (void)mf;

    return -1;
}

int mi2c_detect(mfile *mf, u_int8_t slv_arr[SLV_ADDRS_NUM])
{
    (void)mf;
    (void)slv_arr;

    return 1;
}
int mread_i2cblock(mfile *mf, unsigned char i2c_slave, u_int8_t addr_width,
        unsigned int offset, void *data, int length)
{
    (void)mf;
    (void)i2c_slave;
    (void)addr_width;
    (void)offset;
    (void)data;
    (void)length;

    return 0;
}

int mwrite_i2cblock(mfile *mf, unsigned char i2c_slave, u_int8_t addr_width,
        unsigned int offset, void *data, int length)
{
    (void)mf;
    (void)i2c_slave;
    (void)addr_width;
    (void)offset;
    (void)data;
    (void)length;

    return 0;
}

static void fix_endianness(u_int32_t *buf, int len)
{
    int i;

    for (i = 0; i < (len / 4); ++i) {
        //printf("-D- before: buf[%d] = %#x\n", i, buf[i]);
        buf[i] = __be32_to_cpu(buf[i]);
        //printf("-D- before: buf[%d] = %#x\n", i, buf[i]);
    }
}

int mread_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len)
{
    int rc;
    rc = mread4_block(mf, offset, (u_int32_t*) data, byte_len);
    fix_endianness((u_int32_t*) data, byte_len);
    return rc;

}

int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t* data, int byte_len)
{
    fix_endianness((u_int32_t*) data, byte_len);
    return mwrite4_block(mf, offset, (u_int32_t*) data, byte_len);
}

int mget_mdevs_flags(mfile *mf, u_int32_t *devs_flags)
{
    if (mf == NULL || devs_flags == NULL) {
        errno = EINVAL;
        return 1;
    }

    *devs_flags = mf->flags;
    return 0;
}

int mget_mdevs_type(mfile *mf, u_int32_t *mtype)
{
    if (mf == NULL || mtype == NULL) {
        errno = EINVAL;
        return 1;
    }

    *mtype = mf->tp;
    return 0;
}

unsigned char mset_i2c_slave(mfile *mf, unsigned char new_i2c_slave)
{
    unsigned char ret;
    if (mf) {
        ret = mf->i2c_slave;
        mf->i2c_slave = new_i2c_slave;
    } else
        ret = 0xff;
    return ret;
}

int mget_i2c_slave(mfile *mf, unsigned char *new_i2c_slave_p)
{
    if (mf) {
        *new_i2c_slave_p = mf->i2c_slave;
        return 0;
    }
    return -1;
}

#define MLX_DEV_PREFIX1 "mlx4_core"
#define MLX_DEV_PREFIX2 "mlx5_core"

static int get_device_ids(const char* dev_name, dev_info* dinfo)
{
    mfile* mf = mopen(dev_name);
    int rc = 0;
    u_int32_t buf = 0;
    if (!mf) {
        return 1;
    }
    rc = read_config(mf->fd, &mf->sel, PCI_HEADER_OFFS,&buf, 4);
    if (rc) {
        goto exit;
    }
    dinfo->pci.vend_id = EXTRACT(buf, 0, 16);
    dinfo->pci.dev_id = EXTRACT(buf, 16, 16);
    rc = read_config(mf->fd, &mf->sel, PCI_CLASS_OFFS, &buf, 4);
    if (rc) {
        goto exit;
    }
    dinfo->pci.class_id = EXTRACT(buf, 8, 24);
    rc = read_config(mf->fd, &mf->sel, PCI_SUBSYS_OFFS, &buf, 4);
    if (rc) {
        goto exit;
    }
    dinfo->pci.subsys_vend_id = EXTRACT(buf, 0, 16);
    dinfo->pci.subsys_id = EXTRACT(buf, 16, 16);

exit:
    mclose(mf);
    return rc;
}
static int get_dev_dbdf(const char* dev_name, unsigned int * domain,
        unsigned int * bus, unsigned int * dev, unsigned int * func)
{
    char* dbdf_str = strstr(dev_name, "pci");
    int rc = 0;
    if (!dbdf_str) {
        return 1;
    }
    rc = sscanf(dbdf_str, "pci%u:%u:%u:%u", domain, bus, dev, func);
    if (rc != 4) {
        return 1;
    }
    return 0;
}

int get_device_flags(const char *name)
{
    int mask=0;

    mask = MDEVS_TAVOR_CR;
    if ( strstr(name, "cable") ) {
        mask = MDEVS_CABLE;
    }
    return mask;
}

#define CABLES_DIR   "/etc/mft/cables"
#define PUTC(c) do {     \
    *p++ = (c);        \
     if (++cnt >= len) { \
         closedir(dir);  \
         return -1;      \
     } } while(0)
#define PUTS(s) do { for(i=0; (s)[i]; i++) PUTC((s)[i]); } while (0)


int mdevices_v(char *buf, int len, int mask, int verbosity)
{
    int i;
    int s, b, d, f;
    int rc = 0;
    int cnt = 0;
    FILE *fp;
    char dev_line[1035];
    char *p = buf;
    if (mask & MDEVS_TAVOR_CR) {
        /* Get all Mellanox devices - this cmd will return the needed devices one in every line */
        fp =
                popen(
                        "pciconf -lv | grep -B 1 Mellanox | grep pci | cut -f1 | cut -f2 -d \"@\" | cut -f1-4 -d \":\"",
                        "r");
        if (fp == NULL) {
            return -1;
        }

        /* Read the output one line at a time */
        while (fgets(dev_line, sizeof(dev_line) - 1, fp) != NULL) {
            sscanf(dev_line, "pci%d:%d:%d:%d\n", &s, &b, &d, &f);
            if (!verbosity && f != 0) {
                continue;
            }
            for (i = 0; !(dev_line[i] == '\n'); i++) {
                *p++ = dev_line[i];
                if (++cnt >= len) {
                    pclose(fp);
                    return -1;
                }
            }
            *p++ = 0; /* terminate device */
            rc++; /* increament the device count */
        }
        /* close */
        pclose(fp);
    }
    if (mask & MDEVS_CABLE) {
        /*
         * Get cables
         */
        DIR           *dir;
        struct dirent *dirent;
        if ((dir = opendir(CABLES_DIR)) != NULL) {

           while ((dirent = readdir(dir)) != NULL) {
               char *name = dirent->d_name;
               /* According to mask */
               if (get_device_flags(name) & MDEVS_CABLE) {
                   PUTS(name);
                   PUTC('\0');
                   rc++;
               }
           }
           closedir(dir);
        }
    }
    return rc;
}

int mdevices(char *buf, int len, int mask)
{
    return mdevices_v(buf, len, mask, 0);
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
        if (devs) {
            free(devs);
        }
        size *= 2;
        devs = malloc(size);
        if (!devs) {
            errno = ENOMEM;
            return NULL;
        }
        rc = mdevices(devs, size, mask);
    } while (rc == -1);
    *len = rc;
    dev_info* dev_info_arr = malloc(sizeof(dev_info) * rc);
    if (!dev_info_arr) {
        errno = ENOMEM;
        free(devs);
        return NULL;
    }
    memset(dev_info_arr, 0, sizeof(dev_info) * rc);
    dev_name = devs;
    for (i = 0; i < *len; i++) {
        unsigned int domain = 0;
        unsigned int bus = 0;
        unsigned int dev = 0;
        unsigned int func = 0;
        dev_info_arr[i].type = get_device_flags(dev_name);
        strcpy(dev_info_arr[i].dev_name, dev_name);
        strcpy(dev_info_arr[i].pci.conf_dev, dev_name);
        if (dev_info_arr[i].type & MDEVS_TAVOR_CR) {
            if (get_dev_dbdf(dev_name, &domain, &bus, &dev, &func)) {
                goto next;
            }
            dev_info_arr[i].pci.domain = domain;
            dev_info_arr[i].pci.bus = bus;
            dev_info_arr[i].pci.dev = dev;
            dev_info_arr[i].pci.func = func;
            if (get_device_ids(dev_name, &dev_info_arr[i])) {
                goto next;
            }
        }
        next:
            dev_name += strlen(dev_name) + 1;
    }
    free(devs);
    return dev_info_arr;
}

void mdevices_info_destroy(dev_info* dev_info, int len)
{
    (void)len;

    if (dev_info) {
        free(dev_info);
    }
}

#define TLV_OPERATION_SIZE 4
#define OP_TLV_SIZE        16
#define REG_TLV_HEADER_LEN 4

enum {
    MAD_CLASS_REG_ACCESS = 1,
};
enum {
    TLV_END = 0, TLV_OPERATION = 1, TLV_DR = 2, TLV_REG = 3, TLV_USER_DATA = 4,
};

#define REGISTER_HEADERS_SIZE 20
#define INBAND_MAX_REG_SIZE 44
#define ICMD_MAX_REG_SIZE (ICMD_MAX_CMD_SIZE - REGISTER_HEADERS_SIZE)
#define FWCTX_MAX_REG_SIZE 16
#define TOOLS_HCR_MAX_REG_SIZE (TOOLS_HCR_MAX_MBOX - REGISTER_HEADERS_SIZE)

static int supports_icmd(mfile* mf);
static int supports_tools_cmdif_reg(mfile* mf);
static int init_operation_tlv(struct OperationTlv *operation_tlv,
        u_int16_t reg_id, u_int8_t method);
static int mreg_send_wrapper(mfile* mf, u_int8_t *data, int r_icmd_size,
        int w_icmd_size);
static int mreg_send_raw(mfile *mf, u_int16_t reg_id,
        maccess_reg_method_t method, void *reg_data, u_int32_t reg_size,
        u_int32_t r_size_reg, u_int32_t w_size_reg, int *reg_status);
int mget_max_reg_size(mfile *mf);

// maccess_reg: Do a reg_access for the mf device.
// - reg_data is both in and out
// TODO: When the reg operation succeeds but the reg status is != 0,
//       a specific

int maccess_reg(mfile *mf, u_int16_t reg_id, maccess_reg_method_t reg_method,
        void* reg_data, u_int32_t reg_size, u_int32_t r_size_reg,
        u_int32_t w_size_reg, int *reg_status)
{
    int rc;
    if (mf == NULL || reg_data == NULL || reg_status == NULL || reg_size <= 0) {
        return ME_BAD_PARAMS;
    }
    // check register size
    int max_size = mget_max_reg_size(mf);
    if (max_size < 0 ) {
        return ME_ERROR;
    }
    if (reg_size > (unsigned)max_size) {
        //reg too big
        return ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT;
    }
    rc = mreg_send_raw(mf, reg_id, reg_method, reg_data, reg_size, r_size_reg,
            w_size_reg, reg_status);

    if (rc) {
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
            case 0x70:
                return ME_REG_ACCESS_INTERNAL_ERROR;
            default:
                return ME_REG_ACCESS_UNKNOWN_ERR;
        }
    }
    return ME_OK;
}

static int init_operation_tlv(struct OperationTlv *operation_tlv,
        u_int16_t reg_id, u_int8_t method)
{
    memset(operation_tlv, 0, sizeof(*operation_tlv));

    operation_tlv->Type = TLV_OPERATION;
    operation_tlv->class = MAD_CLASS_REG_ACCESS;
    operation_tlv->len = TLV_OPERATION_SIZE;
    operation_tlv->method = method;
    operation_tlv->register_id = reg_id;
    return 0;
}

///////////////////  Function that sends the register via the correct interface ///////////////////////////

static int mreg_send_wrapper(mfile* mf, u_int8_t *data, int r_icmd_size,
        int w_icmd_size)
{
    int rc;
    if (supports_icmd(mf)) {
        rc = icmd_send_command_int(mf, FLASH_REG_ACCESS, data, w_icmd_size,
                r_icmd_size, 0);
        if (rc) {
            return rc;
        }
    } else if (supports_tools_cmdif_reg(mf)) {
        rc = tools_cmdif_reg_access(mf, data, w_icmd_size, r_icmd_size);
        if (rc) {
            return rc;
        }
    } else {
        return ME_NOT_IMPLEMENTED;
    }
    return ME_OK;
}

static int mreg_send_raw(mfile *mf, u_int16_t reg_id,
        maccess_reg_method_t method, void *reg_data, u_int32_t reg_size,
        u_int32_t r_size_reg, u_int32_t w_size_reg, int *reg_status)
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
    tlv_info.len = (reg_size + REG_TLV_HEADER_LEN) >> 2; // length is in dwords
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


#define HW_ID_ADDR 0xf0014

#define CONNECTX3_HW_ID 0x1f5
#define CONNECTX3_PRO_HW_ID 0x1f7
#define SWITCHX_HW_ID 0x245
#define INFINISCALE4_HW_ID 0x1b3

static int supports_icmd(mfile* mf) {
    u_int32_t dev_id;

    if (mread4(mf,HW_ID_ADDR, &dev_id) != 4) { // cr might be locked and retured 0xbad0cafe but we dont care we search for device that supports icmd
        return 0;
    }
    switch (dev_id & 0xffff) { // that the hw device id
        case INFINISCALE4_HW_ID :
        case CONNECTX3_HW_ID :
        case CONNECTX3_PRO_HW_ID :
        case SWITCHX_HW_ID :
            return 0;
        default:
            break;
    }
    return 1;
}

static int supports_tools_cmdif_reg(mfile* mf)
{
    u_int32_t dev_id;

    if (mread4(mf, HW_ID_ADDR, &dev_id) != 4) {
        return 0;
    }
    switch (dev_id & 0xffff) { // that the hw device id
        case CONNECTX3_HW_ID: //Cx3
        case CONNECTX3_PRO_HW_ID: // Cx3-pro
            if (tools_cmdif_is_supported(mf) == ME_OK) {
                return 1;
            }
            return 0;
        default:
            return 0;
    }

}

int mget_max_reg_size(mfile *mf)
{
    if (mf->acc_reg_params.max_reg_size) {
        return mf->acc_reg_params.max_reg_size;
    } else if (supports_icmd(mf)) { // we support icmd and we dont use IB interface -> we use icmd for reg access
        //TOOD: get size dynamically from icmd_params once we have support by fw for mfba with size field greater than 8 bits
        mf->acc_reg_params.max_reg_size = ICMD_MAX_REG_SIZE;
    } else if (supports_tools_cmdif_reg(mf)) {
        mf->acc_reg_params.max_reg_size = TOOLS_HCR_MAX_REG_SIZE;
    }
    return mf->acc_reg_params.max_reg_size;
}

/************************************
 * Function: m_err2str
 ************************************/
const char* m_err2str(MError status)
{
    switch (status) {
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
        case ME_UNSUPPORTED_OPERATION:
            return "ME_UNSUPPORTED_OPERATION";

        case ME_MAD_SEND_FAILED:
            return "ME_MAD_SEND_FAILED";
        case ME_UNKOWN_ACCESS_TYPE:
            return "ME_UNKOWN_ACCESS_TYPE";
        case ME_UNSUPPORTED_ACCESS_TYPE:
            return "ME_UNSUPPORTED_ACCESS_TYPE";
        case ME_UNSUPPORTED_DEVICE:
            return "ME_UNSUPPORTED_DEVICE";

        // Reg access errors
        case ME_REG_ACCESS_BAD_STATUS_ERR:
            return "ME_REG_ACCESS_BAD_STATUS_ERR";
        case ME_REG_ACCESS_BAD_METHOD:
            return "Bad method";
        case ME_REG_ACCESS_NOT_SUPPORTED:
            return "The Register access is not supported by the device";
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
            return "Resource unavailable";
        case ME_REG_ACCESS_MSG_RECPT_ACK:
            return "Message receipt ack";
        case ME_REG_ACCESS_UNKNOWN_ERR:
            return "Unknown register error";
        case ME_REG_ACCESS_SIZE_EXCCEEDS_LIMIT:
            return "Register is too large";
        case ME_REG_ACCESS_CONF_CORRUPT:
            return "Config Section Corrupted";
        case ME_REG_ACCESS_LEN_TOO_SMALL:
            return "The given Register length is too small for the Tlv";
        case ME_REG_ACCESS_BAD_CONFIG:
            return "The configuration is rejected";
        case ME_REG_ACCESS_ERASE_EXEEDED:
            return   "The erase count exceeds its limit";
        case ME_REG_ACCESS_INTERNAL_ERROR:
            return "Firmware internal error";

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
        case ME_ICMD_SIZE_EXCEEDS_LIMIT:
            return "ME_ICMD_SIZE_EXCEEDS_LIMIT";

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

void mpci_change(mfile* mf)
{
    (void) mf;
}

int mib_smp_get(mfile* mf, u_int8_t* data, u_int16_t attr_id,
        u_int32_t attr_mod)
{
    (void)mf;
    (void)data;
    (void)attr_id;
    (void)attr_mod;

    errno = ENOSYS;
    return -1;
}

int mib_smp_set(mfile* mf, u_int8_t* data, u_int16_t attr_id,
        u_int32_t attr_mod)
{
    (void)mf;
    (void)data;
    (void)attr_id;
    (void)attr_mod;

    errno = ENOSYS;
    return -1;
}

int mset_cr_access(mfile* mf, int access)
{
    (void)mf;
    (void)access;

    errno = ENOSYS;
    return -1;
}

int mget_vsec_supp(mfile* mf)
{
    return mf->vsec_supp;
}

int mget_addr_space(mfile* mf)
{
    return mf->address_space;
}
int mset_addr_space(mfile* mf, int space)
{
    switch (space) {
        case AS_CR_SPACE:
        case AS_ICMD:
        case AS_SEMAPHORE:
            break;
        default:
            return -1;
    }
    mf->address_space = space;
    return 0;
}

int device_exists(const char* devname)
{
    char* devs = NULL;
    char* pdevs;
    int size = 512;
    int rc = 0;
    int i = 0;
    int res = 0;
    // Get list of devices
    do {
        if (devs) {
            free(devs);
        }
        size *= 2;
        devs = malloc(size);
        if (!devs) {
            errno = ENOMEM;
            return 0;
        }
        rc = mdevices_v(devs, size, MDEVS_ALL, 1);
    } while (rc == -1);
    pdevs = devs;
    while (i < rc) {
        if (!strcmp(devname, pdevs)) {
            res = 1;
            goto cleanup;
        }
        pdevs += strlen(pdevs) + 1;
        i ++;
    }
cleanup:
    if (devs) {
        free(devs);
    }
    return res;
}

int mclear_pci_semaphore(const char* name)
{
    mfile* mf;
    int rc = ME_OK;
    mf = mopen_int(name, Clear_Vsec_Semaphore);
    if (!mf) {
        return ME_ERROR;
    }
    if (mf->tp != MST_PCICONF) {
        rc = ME_UNSUPPORTED_ACCESS_TYPE;
    }
    mclose(mf);
    return rc;
}

int mvpd_read4_int(mfile *mf, unsigned int offset, u_int8_t value[4])
{
    int vpd_cap = mf->vpd_cap_addr;
    uint16_t write_addr;
    uint32_t read_addr;
    int res;
    int count_to_timeout;
    int done = 0;
	
    if (!mf || !value) {
        return ME_BAD_PARAMS;
    }
    if (!vpd_cap) {
        return ME_UNSUPPORTED_OPERATION;
    }

    /* sets F bit to zero and write VPD addr */
    write_addr = (0x7fff & offset);
    res = write_config(mf->fd, &mf->sel, vpd_cap + PCI_VPD_ADDR, write_addr, 2);
    if (res) {
        return res;
    }

    /* wait for data until F bit is set with one */
    for (count_to_timeout = 0; count_to_timeout < MST_VPD_DFLT_TIMEOUT; count_to_timeout++) {
        res = read_config(mf->fd, &mf->sel, vpd_cap + PCI_VPD_ADDR, &read_addr, 2);
        if (res) {
            return res;
        }
        if (read_addr & 0x8000) {
            done = 1;
            break;
        }
        sched_yield();
    }
    if (done) {
        return read_config(mf->fd, &mf->sel, vpd_cap + PCI_VPD_DATA, (uint32_t *)value, 4);
    } else {
        return ME_TIMEOUT;
    }
}

int mvpd_read4(mfile *mf, unsigned int offset, u_int8_t value[4])
{

    if (offset % 4) {
        u_int8_t qword[8] = {0};
        int rc = 0;
        unsigned int aligned_offset = (offset / 4) * 4;
        rc = mvpd_read4_int(mf, aligned_offset, qword);
        if (rc) {
            return rc;
        }
        rc = mvpd_read4_int(mf, aligned_offset + 4, qword + 4);
        memcpy(value, qword + (offset % 4), 4);
        return 0;
    } else {
        return mvpd_read4_int(mf, offset, value);
    }
}

int mvpd_write4(mfile *mf, unsigned int offset, u_int8_t value[4])
{
    (void)mf;
    (void)offset;
    (void)value;
    return 0;
}

