/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <sys/memrange.h>
#include <sys/mman.h>
#include <err.h>
#define _WITH_GETLINE
#include <stdio.h>
#include <sys/agpio.h>
#include <sys/pciio.h>
#include <sys/stat.h>

#include <dev/agp/agpreg.h>
#include <dev/pci/pcireg.h>
#include <sched.h>

#include "mtcr_common.h"
#include "mtcr.h"
#include "common/compatibility.h"
#include "common/bit_slice.h"
#include "common/tools_time.h"
#include <stdlib.h>
#include "tools_dev_types.h"

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
#include <sys/file.h>

#define MST_VPD_DFLT_TIMEOUT 2000
#define PCI_VPD_ADDR 0x2
#define PCI_CAP_ID_VPD 0x3
#define PCI_VPD_DATA 0x4
#define HW_ID_ADDR 0xf0014

/* Mellanox VSC */
#define MLX_VSC_TYPE_OFFSET 24
#define MLX_VSC_TYPE_LEN 8
#define FUNCTIONAL_VSC 0
#define RECOVERY_VSC 2

#define _PATH_DEVPCI "/dev/pci"

typedef enum
{
    Clear_Vsec_Semaphore = 0x1
} adv_opt_t;

#define FREEBSD_LOCK_FILE_DIR "/tmp/mft_lockfiles"
#define FREEBSD_LOCK_FILE_FORMAT "/tmp/mft_lockfiles/%s"

#define CHECK_LOCK(rc) \
    if (rc)            \
    {                  \
        return rc;     \
    }

#define FREEBSD_MAX_RETRY_CNT 8192
static int _flock_int(int fdlock, int operation)
{
    int cnt = 0;

    if (fdlock == 0)
    {
        /* in case we failed to create the lock file we ignore the locking mechanism */
        return 0;
    }
    do
    {
        if (flock(fdlock, operation | LOCK_NB) == 0)
        {
            return 0;
        }
        else if (errno != EWOULDBLOCK)
        {
            break; /* BAD! lock/free failed */
        }
        mft_usleep(10);
        cnt++;
    } while (cnt < FREEBSD_MAX_RETRY_CNT);
    perror("failed to perform lock operation.");
    return -1;
}

static int _create_lock(mfile* mf, char* devname)
{
    char fname[64] = {0};
    int rc;
    int fd = 0;

    snprintf(fname, sizeof(fname) - 1, FREEBSD_LOCK_FILE_FORMAT, devname);
    rc = mkdir("/tmp", 0777);
    if (rc && (errno != EEXIST))
    {
        goto cl_clean_up;
    }
    rc = mkdir(FREEBSD_LOCK_FILE_DIR, 0777);
    if (rc && (errno != EEXIST))
    {
        goto cl_clean_up;
    }

    fd = open(fname, O_RDONLY | O_CREAT, 0777);
    if (fd < 0)
    {
        goto cl_clean_up;
    }

    mf->fdlock = fd;
    return 0;

cl_clean_up:
    fprintf(stderr, "Warrning: Failed to create lockfile: %s (parallel access not supported)\n", fname);
    return 0;
}
/*End of Lock file section */

void mtcr_connectx_flush(void* ptr, int fdlock)
{
    u_int32_t value;
    int rc = _flock_int(fdlock, LOCK_EX);

    if (rc)
    {
        return;
    }
    *((u_int32_t*)((char*)ptr + 0xf0380)) = 0x0;
    do
    {
        asm volatile("" ::: "memory");
        value = __be32_to_cpu(*((u_int32_t*)((char*)ptr + 0xf0380)));
    } while (value);
    rc = _flock_int(fdlock, LOCK_UN);
    if (rc)
    {
        return;
    }
}

int read_device_id(mfile* mf, u_int32_t* device_id)
{
    if (!mf || !device_id)
    {
        return -1;
    }

    unsigned hw_id_address = mf->cr_space_offset + HW_ID_ADDR;

    mf->rev_id = EXTRACT(*device_id, 16, 4);
    *device_id = (*device_id & 0xffff);
    mf->hw_dev_id = (*device_id & 0xffff);

    return mread4(mf, hw_id_address, device_id);
}

int mtcr_check_signature(mfile* mf)
{
    unsigned signature;
    int rc;

    rc = read_device_id(mf, &signature);
    if (rc != 4)
    {
        if (!errno)
        {
            errno = EIO;
        }
        return -1;
    }

    switch (signature & 0xffff)
    {
        case 0x190: /* 400 */
            if ((signature == 0xa00190) && mf->ptr)
            {
                mf->connectx_flush = 1;
                mtcr_connectx_flush(mf->ptr, mf->fdlock);
            }
            break;

        case 0x5a44: /* 23108 */
        case 0x6278: /* 25208 */
        case 0x5e8c: /* 24204 */
        case 0x6274: /* 25204 */
            return 0;

        default:
            errno = ENOTTY;
            return -1;
    }
    return 0;
}

#define READ4_PCI(mf, val_ptr, pci_offs, err_prefix, action_on_fail) \
    do                                                               \
    {                                                                \
        int rc;                                                      \
        int lock_rc;                                                 \
        lock_rc = _flock_int(mf->fdlock, LOCK_EX);                   \
        if (lock_rc)                                                 \
        {                                                            \
            perror(err_prefix);                                      \
            action_on_fail;                                          \
        }                                                            \
        rc = read_config(mf, pci_offs, val_ptr, 4);                  \
        lock_rc = _flock_int(mf->fdlock, LOCK_UN);                   \
        if (lock_rc)                                                 \
        {                                                            \
            perror(err_prefix);                                      \
            action_on_fail;                                          \
        }                                                            \
        if (rc)                                                      \
        {                                                            \
            return rc;                                               \
        }                                                            \
    } while (0)

#define WRITE4_PCI(mf, val, pci_offs, err_prefix, action_on_fail) \
    do                                                            \
    {                                                             \
        int rc;                                                   \
        int lock_rc;                                              \
        lock_rc = _flock_int(mf->fdlock, LOCK_EX);                \
        if (lock_rc)                                              \
        {                                                         \
            perror(err_prefix);                                   \
            action_on_fail;                                       \
        }                                                         \
        rc = write_config(mf, pci_offs, val, 4);                  \
        lock_rc = _flock_int(mf->fdlock, LOCK_UN);                \
        if (lock_rc)                                              \
        {                                                         \
            perror(err_prefix);                                   \
            action_on_fail;                                       \
        }                                                         \
        if (rc)                                                   \
        {                                                         \
            return rc;                                            \
        }                                                         \
    } while (0)

#define WRITE2_PCI(mf, val, pci_offs, err_prefix, action_on_fail) \
    do                                                            \
    {                                                             \
        int rc;                                                   \
        int lock_rc;                                              \
        lock_rc = _flock_int(mf->fdlock, LOCK_EX);                \
        if (lock_rc)                                              \
        {                                                         \
            perror(err_prefix);                                   \
            action_on_fail;                                       \
        }                                                         \
        rc = write_config(mf, pci_offs, val, 2);                  \
        lock_rc = _flock_int(mf->fdlock, LOCK_UN);                \
        if (lock_rc)                                              \
        {                                                         \
            perror(err_prefix);                                   \
            action_on_fail;                                       \
        }                                                         \
        if (rc)                                                   \
        {                                                         \
            return rc;                                            \
        }                                                         \
    } while (0)

#define PCI_CONF_ADDR (0x00000058)
#define PCI_CONF_DATA (0x0000005c)
#define VENDOR_SPECIFIC_CAP_ID 0x9

/* PCI address space related enum*/
enum
{
    PCI_CAP_PTR = 0x34,
    PCI_HDR_SIZE = 0x40,
    PCI_EXT_SPACE_ADDR = 0xff,

    PCI_CTRL_OFFSET = 0x4, /* for space / semaphore / auto-increment bit */
    PCI_COUNTER_OFFSET = 0x8,
    PCI_SEMAPHORE_OFFSET = 0xc,
    PCI_ADDR_OFFSET = 0x10,
    PCI_DATA_OFFSET = 0x14,

    PCI_FLAG_BIT_OFFS = 31,

    PCI_SPACE_BIT_OFFS = 0,
    PCI_SPACE_BIT_LEN = 16,

    PCI_STATUS_BIT_OFFS = 29,
    PCI_STATUS_BIT_LEN = 3,

    PCI_SYNDROME_BIT_OFFSET = 30,
    PCI_SYNDROME_BIT_LEN = 1,
    PCI_SYNDROME_CODE_BIT_OFFSET = 24,
    PCI_SYNDROME_CODE_BIT_LEN = 4,

    PCI_HEADER_OFFS = 0x0,
    PCI_SUBSYS_OFFS = 0x2c,
    PCI_CLASS_OFFS = 0x8,
};

/* Mellanox vendor specific enum */
enum
{
    CAP_ID = 0x9,
    IFC_MAX_RETRIES = 0x10000,
    SEM_MAX_RETRIES = 0x1000
};

int read_config(mfile* mf, unsigned int reg, uint32_t* data, int width)
{
    struct pci_io pi = {};

    memset(&pi, 0, sizeof(pi));

    pi.pi_sel = mf->sel;
    pi.pi_reg = reg;
    pi.pi_width = width;

    if (ioctl(mf->fd, PCIOCREAD, &pi) < 0)
    {
        /* printf("PCIOCREAD ioctl failed when trying to access this space: %d. errno: %d\n", */
        /*             mf->address_space, errno); */
        errno = EIO;
        return -1;
    }

    /* printf("%s:  dev:%d reg=%x width=%d data=%x\n", __FUNCTION__, pi.pi_sel.pc_dev, reg, width, pi.pi_data); */
    *data = (pi.pi_data);

    return 0;
}

int write_config(mfile* mf, unsigned int reg, uint32_t data, int width)
{
    struct pci_io pi = {};

    memset(&pi, 0, sizeof(pi));

    pi.pi_sel = mf->sel;
    pi.pi_reg = reg;
    pi.pi_width = width;
    pi.pi_data = data;

    /* printf("%s: dev:%d reg:%x width:%d data:%x\n", __FUNCTION__, pi.pi_sel.pc_dev, pi.pi_reg, pi.pi_width, */
    /* pi.pi_data); */
    if (ioctl(mf->fd, PCIOCWRITE, &pi) < 0)
    {
        /* printf("PCIOCWRITE ioctl failed when trying to access this space: %d. errno: %d\n", */
        /*             mf->address_space, errno); */
        errno = EIO;
        return -1;
    }

    return 0;
}

#define WO_REG_ADDR_DATA 0xbadacce5
#define PCICONF_ADDR_OFF 0x58
#define PCICONF_DATA_OFF 0x5c

static int is_wo_pciconf_gw(mfile* mf)
{
    unsigned offset = HW_ID_ADDR;
    u_int32_t data = 0;
    int lock_rc;

    lock_rc = _flock_int(mf->fdlock, LOCK_EX);
    if (lock_rc)
    {
        return 0;
    }
    int rc = write_config(mf, PCI_CONF_ADDR, (unsigned long)offset, 4);

    if (rc < 0)
    {
        goto cleanup;
    }
    rc = read_config(mf, PCI_CONF_ADDR, &data, 4);
    if (rc < 0)
    {
        rc = 0;
        goto cleanup;
    }
    /* printf("-D- Data: %#x\n", data); */
    if (data == WO_REG_ADDR_DATA)
    {
        rc = 1;
    }
cleanup:
    lock_rc = _flock_int(mf->fdlock, LOCK_UN);
    if (lock_rc)
    {
        return rc;
    }
    return rc;
}

/*Find PCI Capability*/

/*semaphore*/

/*set addr space*/

/* Read Write new functions (4Bytes, Block)*/
int pci_find_capability(mfile* mf, int cap_id)
{
    unsigned offset;
    unsigned char visited[256] = {0}; /* Prevent infinite loops */
    uint32_t reg;
    int ret;
    int curr_cap;
    int lock_rc;

    lock_rc = _flock_int(mf->fdlock, LOCK_EX);
    if (lock_rc)
    {
        return 0;
    }
    ret = read_config(mf, PCI_CAP_PTR, &reg, 4);

    if (ret)
    {
        ret = 0;
        goto cleanup;
    }

    offset = ((unsigned char*)&reg)[0];
    while (1)
    {
        if ((offset < PCI_HDR_SIZE) || (offset > PCI_EXT_SPACE_ADDR))
        {
            ret = 0;
            goto cleanup;
        }
        ret = read_config(mf, offset, &reg, 4);
        if (ret)
        {
            ret = 0;
            goto cleanup;
        }

        visited[offset] = 1;
        curr_cap = ((unsigned char*)&reg)[0];
        if (curr_cap == cap_id)
        {
            ret = offset;
            goto cleanup;
        }

        offset = ((unsigned char*)&reg)[1];
        if (visited[offset])
        {
            ret = 0;
            goto cleanup;
        }
    }
cleanup:
    lock_rc = _flock_int(mf->fdlock, LOCK_UN);
    if (lock_rc)
    {
        return ret;
    }
    return ret;
}

static int _vendor_specific_sem(mfile* mf, int state)
{
    uint32_t lock_val;
    uint32_t counter = 0;
    int retries = 0;

    if (!state)
    {
        /* unlock */
        WRITE4_PCI(mf, 0, mf->vsec_addr + PCI_SEMAPHORE_OFFSET, "unlock semaphore", return -1);
    }
    else
    {
        /* lock */
        do
        {
            if (retries > SEM_MAX_RETRIES)
            {
                return -1;
            }
            /* read semaphore untill 0x0 */
            READ4_PCI(mf, &lock_val, mf->vsec_addr + PCI_SEMAPHORE_OFFSET, "read counter", return -1);
            if (lock_val)
            {
                /* semaphore is taken */
                retries++;
                msleep(1); /* wait for current op to end */
                continue;
            }
            /* read ticket */
            READ4_PCI(mf, &counter, mf->vsec_addr + PCI_COUNTER_OFFSET, "read counter", return -1);
            /* write ticket to semaphore dword */
            WRITE4_PCI(mf, counter, mf->vsec_addr + PCI_SEMAPHORE_OFFSET, "write counter to semaphore", return -1);
            /* read back semaphore make sure ticket == semaphore else repeat */
            READ4_PCI(mf, &lock_val, mf->vsec_addr + PCI_SEMAPHORE_OFFSET, "read counter", return -1);
            retries++;
        } while (counter != lock_val);
    }
    return 0;
}

static int _wait_on_flag(mfile* mf, u_int8_t expected_val)
{
    int retries = 0;
    uint32_t flag;

    do
    {
        if (retries > IFC_MAX_RETRIES)
        {
            return -1;
        }

        READ4_PCI(mf, &flag, mf->vsec_addr + PCI_ADDR_OFFSET, "read flag", return -1);

        flag = EXTRACT(flag, PCI_FLAG_BIT_OFFS, 1);
        retries++;
        if ((retries & 0xf) == 0)
        {
            /* dont sleep always */
            /* usleep_range(1,5); */
        }
    } while (flag != expected_val);
    return 0;
}

int get_syndrome_code(mfile* mf, u_int8_t* syndrome_code)
{
    /* in case syndrome is set, if syndrome_code is 0x3 (address_out_of_range), we need to swap from CORE address_space */
    /* to PCI address_space. */

    u_int32_t syndrome = 0;

    *syndrome_code = 0;
    READ4_PCI(mf, &syndrome, mf->vsec_addr + PCI_ADDR_OFFSET, "read domain", return ME_PCI_READ_ERROR);

    syndrome = EXTRACT(syndrome, PCI_SYNDROME_BIT_OFFSET, PCI_SYNDROME_BIT_LEN);
    if (syndrome)
    {
        u_int32_t syndrome_code_dword = 0;
        READ4_PCI(mf, &syndrome_code_dword, mf->vsec_addr + PCI_CTRL_OFFSET, "read domain", return ME_PCI_READ_ERROR);
        *syndrome_code = EXTRACT(syndrome_code_dword, PCI_SYNDROME_CODE_BIT_OFFSET, PCI_SYNDROME_CODE_BIT_LEN);
    }
    return ME_OK;
}

static int _set_addr_space(mfile* mf, u_int16_t space)
{
    WRITE2_PCI(mf, space, mf->vsec_addr + PCI_CTRL_OFFSET, "write domain", return -1);

    /* Check if we succedded to write the space (i.e. that its MSB is not ignored by FW) */
    u_int32_t read_val = 0;

    READ4_PCI(mf, &read_val, mf->vsec_addr + PCI_CTRL_OFFSET, "read status", return -1);

    u_int16_t actual_value = (uint16_t)EXTRACT(read_val, 0, 16); /* Extract only the first 16 bits, as we need to check what's written in "space" */

    /* Check if the space written is indeed the space we attempted to write */
    if (actual_value != space)
    {
        /* printf("VSC address space: 0x%x is not supported.\n", space); */
        return ME_PCI_SPACE_NOT_SUPPORTED;
    }

    /* read status and make sure space is supported */
    if (EXTRACT(read_val, PCI_STATUS_BIT_OFFS, PCI_STATUS_BIT_LEN) == 0)
    {
        /* printf("VSC address space: 0x%x is not supported. status bit is 0.\n", space); */
        return -1;
    }
    return 0;
}

static int _pciconf_rw(mfile* mf, unsigned int offset, uint32_t* data, int rw)
{
    int ret = 0;
    uint32_t address = offset;

    /* last 2 bits must be zero as we only allow 30 bits addresses */
    if (EXTRACT(address, 30, 2))
    {
        return -1;
    }

    address = MERGE(address, (rw ? 1 : 0), PCI_FLAG_BIT_OFFS, 1);
    if (rw == WRITE_OP)
    {
        /* write data */
        WRITE4_PCI(mf, *data, mf->vsec_addr + PCI_DATA_OFFSET, "write value", return -1);
        /* write address */
        WRITE4_PCI(mf, address, mf->vsec_addr + PCI_ADDR_OFFSET, "write offset", return -1);
        /* wait on flag */
        ret = _wait_on_flag(mf, 0);
    }
    else
    {
        /* write address */
        WRITE4_PCI(mf, address, mf->vsec_addr + PCI_ADDR_OFFSET, "write offset", return -1);
        /* wait on flag */
        ret = _wait_on_flag(mf, 1);
        if (ret == -1)
        {
            /* printf("MTCR: _pciconf_rw: _wait_on_falg failed !\n"); */
        }
        /* read data */
        READ4_PCI(mf, data, mf->vsec_addr + PCI_DATA_OFFSET, "read value", return -1);
    }
    return ret;
}

static int _send_pci_cmd_int(mfile* mf, int space, unsigned int offset, uint32_t* data, int rw)
{
    int ret = 0;

    /* take semaphore */
    ret = _vendor_specific_sem(mf, 1);
    if (ret)
    {
        /* printf("-D- Failed to take Semaphore!\n"); */
        return ret;
    }
    /* set address space */
    ret = _set_addr_space(mf, space);
    if (ret)
    {
        /* printf("-D- Failed to set space!\n"); */
        goto cleanup;
    }
    /* read/write the data */
    ret = _pciconf_rw(mf, offset, data, rw);
cleanup:
    /* clear semaphore */
    _vendor_specific_sem(mf, 0);
    return ret;
}

static int _block_op(mfile* mf, int space, unsigned int offset, int size, uint32_t* data, int rw)
{
    int i;
    int ret = 0;
    int wrote_or_read = size;

    if (size % 4)
    {
        return -1;
    }
    /* lock semaphore and set address space */
    ret = _vendor_specific_sem(mf, 1);
    if (ret)
    {
        return -1;
    }
    /* set address space */
    ret = _set_addr_space(mf, space);
    if (ret)
    {
        wrote_or_read = -1;
        goto cleanup;
    }

    for (i = 0; i < size; i += 4)
    {
        if (_pciconf_rw(mf, offset + i, &(data[(i >> 2)]), rw))
        {
            wrote_or_read = i;
            goto cleanup;
        }
    }

cleanup:
    _vendor_specific_sem(mf, 0);
    return wrote_or_read;
}

static int mwrite4_new(mfile* mf, unsigned int offset, uint32_t data)
{
    int rc;

    rc = _send_pci_cmd_int(mf, mf->address_space, offset, &data, WRITE_OP);

    if (rc)
    { /* OPERATIONAL error */
        return -1;
    }

    /* Support PCI space */
    if (VSEC_PXIR_SUPPORT(mf))
    {
        u_int8_t syndrome_code = 0;
        if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
        { /* OPERATIONAL failure before retry */
            /* printf("Reading syndrome failed, aborting\n"); */
            return -1;
        }
        else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
        { /* LOGICAL failure */
            /* printf( */
            /*   "mwrite4_new: mtcr_pciconf_send_pci_cmd_int failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE) when trying to access address_space: 0x%x at offset: 0x%x\n", */
            /*   mf->address_space, offset); */

            swap_pci_address_space(mf);
            rc = _send_pci_cmd_int(mf, mf->address_space, offset, &data, WRITE_OP);

            if (rc)
            { /* OPERATIONAL failure after retry */
                /* printf( */
                /*   "mwrite4_new: mtcr_pciconf_send_pci_cmd_int failed (OPERATIONAL error), after retry, when trying to access address_space: 0x%x at offset: 0x%x\n", */
                /*   mf->address_space, offset); */
                return -1;
            }
            if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
            { /* OPERATIONAL failure after retry */
                /* printf("Reading syndrome failed, aborting\n"); */
                return -1;
            }
            else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
            { /* LOGICAL failure after retry */
                /* printf( */
                /*   "mwrite4_new: mtcr_pciconf_send_pci_cmd_int failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE), after retry, when trying to access address_space: 0x%x at offset:
                 * 0x%x\n", */
                /*   mf->address_space, offset); */
                return -1;
            }
            else
            { /* LOGICAL and OPERATIONAL success after retry */
                /* printf( */
                /*   "mwrite4_new: mtcr_pciconf_send_pci_cmd_int, after retry, successfully accessed address_space: 0x%x at offset: 0x%x\n", */
                /*   mf->address_space, offset); */
                return 4;
            }
        }
        else
        { /* OPERATIONAL and LOGICAL success */
            return 4;
        }
    }

    return 4; /* OPERATIONAL and LOGICAL success (PCI VSC address_spaces not supported) */
}

static int mread4_new(mfile* mf, unsigned int offset, uint32_t* data)
{
    int rc;

    rc = _send_pci_cmd_int(mf, mf->address_space, offset, data, READ_OP);

    if (rc)
    { /* OPERATIONAL error */
        return -1;
    }

    /* Support PCI space */
    if (VSEC_PXIR_SUPPORT(mf))
    {
        u_int8_t syndrome_code = 0;
        if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
        { /* OPERATIONAL failure before retry */
            /* printf("Reading syndrome failed, aborting\n"); */
            return -1;
        }
        else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
        { /* LOGICAL failure */
            /* printf( */
            /*   "mread4_new: mtcr_pciconf_send_pci_cmd_int failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE) when trying to access address_space: 0x%x at offset: 0x%x\n", */
            /*   mf->address_space, offset); */

            swap_pci_address_space(mf);
            rc = _send_pci_cmd_int(mf, mf->address_space, offset, data, READ_OP);

            if (rc)
            { /* OPERATIONAL failure after retry */
                /* printf( */
                /*   "mread4_new: mtcr_pciconf_send_pci_cmd_int failed (OPERATIONAL error), after retry, when trying to access address_space: 0x%x at offset: 0x%x\n", */
                /*   mf->address_space, offset); */
                return -1;
            }
            if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
            { /* OPERATIONAL failure after retry */
                /* printf("Reading syndrome failed, aborting\n"); */
                return -1;
            }
            else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
            { /* LOGICAL failure after retry */
                /* printf( */
                /*   "mread4_new: mtcr_pciconf_send_pci_cmd_int failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE), after retry, when trying to access address_space: 0x%x at offset:
                 * 0x%x\n", */
                /*   mf->address_space, offset); */
                return -1;
            }
            else
            { /* LOGICAL and OPERATIONAL success after retry */
                /* printf( */
                /*   "mread4_new: mtcr_pciconf_send_pci_cmd_int, after retry, successfully accessed address_space: 0x%x at offset: 0x%x\n", */
                /*   mf->address_space, offset); */
                return 4;
            }
        }
        else
        { /* OPERATIONAL and LOGICAL success */
            return 4;
        }
    }

    return 4; /* OPERATIONAL and LOGICAL success (PCI VSC address_spaces not supported) */
}

static int mwrite4_block_new(mfile* mf, unsigned int offset, int size, uint32_t* data)
{
    int bytes_written = _block_op(mf, mf->address_space, offset, size, data, WRITE_OP);

    /* Support PCI space */
    if (VSEC_PXIR_SUPPORT(mf))
    {
        u_int8_t syndrome_code = 0;
        if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
        { /* OPERATIONAL failure before retry */
            /* printf("Reading syndrome failed. bytes_written: 0x%x\n", bytes_written); */
        }
        else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
        { /* LOGICAL failure */
            /* printf( */
            /*   "mwrite4_block_new: block_op_pciconf failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE) when trying to access address_space: 0x%x at offset: 0x%x. bytes_written:
             * 0x%x\n", */
            /*   mf->address_space, offset, bytes_written); */

            swap_pci_address_space(mf);
            bytes_written = _block_op(mf, mf->address_space, offset, size, data, WRITE_OP);

            if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
            { /* OPERATIONAL failure after retry */
                /* printf("Reading syndrome failed. bytes_written: 0x%x\n", bytes_written); */
            }
            else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
            { /* LOGICAL failure after retry */
                /* printf( */
                /*   "mwrite4_block_new: block_op_pciconf failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE) after retry. when trying to access address_space: 0x%x at offset: 0x%x.
                 * bytes_written: 0x%x\n", */
                /*   mf->address_space, offset, bytes_written); */
            }
        }
    }

    return bytes_written;
}

static int mread4_block_new(mfile* mf, unsigned int offset, int size, uint32_t* data)
{
    int bytes_read = _block_op(mf, mf->address_space, offset, size, data, READ_OP);

    /* Support PCI space */
    if (VSEC_PXIR_SUPPORT(mf))
    {
        u_int8_t syndrome_code = 0;
        if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
        { /* OPERATIONAL failure before retry */
            /* printf("Reading syndrome failed. bytes_read: 0x%x\n", bytes_read); */
        }
        else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
        { /* LOGICAL failure */
            /* printf( */
            /*   "mread4_block_new: block_op_pciconf failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE) when trying to access address_space: 0x%x at offset: 0x%x. bytes_read: 0x%x\n",
             */
            /*   mf->address_space, offset, bytes_read); */

            swap_pci_address_space(mf);
            bytes_read = _block_op(mf, mf->address_space, offset, size, data, READ_OP);

            if (get_syndrome_code(mf, &syndrome_code) == ME_PCI_READ_ERROR)
            { /* OPERATIONAL failure after retry */
                /* printf("Reading syndrome failed. bytes_read: 0x%x\n", bytes_read); */
            }
            else if (syndrome_code == ADDRESS_OUT_OF_RANGE)
            { /* LOGICAL failure after retry */
                /* printf( */
                /*   "mread4_block_new: block_op_pciconf failed (syndrome is set and syndrome_code is ADDRESS_OUT_OF_RANGE) after retry. when trying to access address_space: 0x%x at offset: 0x%x.
                 * bytes_read: 0x%x\n", */
                /*   mf->address_space, offset, bytes_read); */
            }
        }
    }

    return bytes_read;
}

static int vsec_spaces_supported(mfile* mf)
{
    /* take semaphore */
    int supported = 1;
    int ret = _vendor_specific_sem(mf, 1);

    if (ret)
    {
        return supported;
    }
    if (_set_addr_space(mf, AS_CR_SPACE) || _set_addr_space(mf, AS_ICMD) || _set_addr_space(mf, AS_SEMAPHORE))
    {
        supported = 0;
    }
    /* clear semaphore */
    _vendor_specific_sem(mf, 0);
    return supported;
}

static int pci_vsec_spaces_supported(mfile* mf)
{
    /* take semaphore */
    int ret = _vendor_specific_sem(mf, 1);

    if (ret)
    {
        return 0;
    }

    int supported = 1;

    if (_set_addr_space(mf, AS_PCI_CRSPACE) || _set_addr_space(mf, AS_PCI_ALL_ICMD) || _set_addr_space(mf, AS_PCI_GLOBAL_SEMAPHORE))
    {
        supported = 0;
    }

    /* clear semaphore */
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

#if __FreeBSD_version > 700000
int getsel(const char* str, struct pcisel* selout)
{
    char* ep = strchr(str, '@');
    char* epbase;
    struct pcisel sel;
    unsigned long selarr[4];
    int i;

    /* printf("__FreeBSD_version > 700000 detected.\n"); */

    if (ep == NULL)
    {
        ep = (char*)str;
    }
    else
    {
        ep++;
    }

    epbase = ep;

    if (strncmp(ep, "pci", 3) == 0)
    {
        ep += 3;
        i = 0;
        do
        {
            selarr[i++] = strtoul(ep, &ep, 10);
        } while ((*ep == ':' || *ep == '.') && *++ep != '\0' && i < 4);

        if (i > 2)
        {
            sel.pc_func = selarr[--i];
        }
        else
        {
            sel.pc_func = 0;
        }
        sel.pc_dev = selarr[--i];
        sel.pc_bus = selarr[--i];
        if (i > 0)
        {
            sel.pc_domain = selarr[--i];
        }
        else
        {
            sel.pc_domain = 0;
        }
    }
    if ((*ep != '\x0') || (ep == epbase))
    {
        return 1;
        /* errx(1, "cannot parse selector %s ep:'%s' epbase:%s, %d", str, ep, epbase, *ep); */
    }

    *selout = sel;

    return 0;
}
#else
int getsel(const char* str, struct pcisel* selout)
{
    char* ep = strchr(str, '@');
    char* epbase;
    struct pcisel sel;

    /* printf("__FreeBSD_version < 700000 detected: %d\n", __FreeBSD_version); */

    if (ep == NULL)
    {
        ep = (char*)str;
    }
    else
    {
        ep++;
    }

    epbase = ep;

    if (strncmp(ep, "pci", 3) == 0)
    {
        ep += 3;
        sel.pc_bus = strtoul(ep, &ep, 0);
        if (!ep || (*ep++ != ':'))
        {
            errno = EINVAL;
            return 1;
            /* errx(1, "cannot parse selector %s", str); */
        }
        sel.pc_dev = strtoul(ep, &ep, 0);
        if (!ep || (*ep != ':'))
        {
            sel.pc_func = 0;
        }
        else
        {
            ep++;
            sel.pc_func = strtoul(ep, &ep, 0);
        }
        if (*ep == ':')
        {
            ep++;
        }
    }
    if ((*ep != '\x0') || (ep == epbase))
    {
        return 1;
        /* errx(1, "cannot parse selector %s", str); */
    }

    *selout = sel;

    return 0;
}
#endif /* if __FreeBSD_version > 700000 */

int mtcr_open_config(mfile* mf, const char* name)
{
    /* printf("open_config %s %s mf:%p\n", name, _PATH_DEVPCI, mf); */

    if (!mf)
    {
        printf("Internal: Uninitialized mfile\n");
        exit(1);
    }

    mf->fd = open(_PATH_DEVPCI, O_RDWR, 0);
    if (mf->fd < 0)
    {
        printf("err opening: %s", _PATH_DEVPCI);
        return -1;
    }

    /* printf("open_config name:%s fd:%d\n", name, mf->fd); */
    int ret = getsel(name, &mf->sel);

    /* printf("open_config getsel done %d\n", mf->sel.pc_dev); */
    mf->tp = MST_PCICONF;

    return ret;
}

mfile* mopen_int(const char* name, u_int32_t adv_opt)
{
    char* real_name = (char*)name;
    int is_cable = 0;

#ifndef MST_UL
    int port = 0;
#endif
    if (getuid() != 0)
    {
        errno = EACCES;
        return NULL;
    }
    /* printf("%s: open %s\n", __FUNCTION__, name); */
#ifndef MST_UL
    char tmp_name[512] = {0};
    char* p_cable = strstr(name, "_cable");
    if (p_cable != 0)
    {
        strncpy(tmp_name, name, 512 - 1);
        tmp_name[p_cable - name] = 0;
        is_cable = 1;
        real_name = tmp_name;

        /* printf("-D- splitting name: %s\n", real_name); */
        if (strstr(p_cable + 1, "_") != NULL)
        {
            p_cable += 7;
            if (*p_cable != '\0')
            {
                port = atoi(p_cable);
            }
        }
    }
#endif
    if (!device_exists(real_name))
    {
        errno = ENOENT;
        return NULL;
    }
    mfile* mf = malloc(sizeof(mfile));
    memset(mf, 0, sizeof(mfile));
    if (!mf)
    {
        return NULL;
    }
    mf->sock = -1;
    mf->user_page_list.page_amount = 0;

    mf->flags = MDEVS_TAVOR_CR;
    if (!mtcr_open_config(mf, real_name))
    {
        _create_lock(mf, real_name);
        mf->wo_addr = is_wo_pciconf_gw(mf);
        /* printf("-D- is_wo_pciconf_gw: %d\n", mf->wo_addr); */
        mf->vsec_addr = pci_find_capability(mf, VENDOR_SPECIFIC_CAP_ID);

        uint32_t vsec_type = 0;
        int rc = read_config(mf, mf->vsec_addr, &vsec_type, 4);
        if (rc)
        {
            /* printf("-E- Failed to read first dword from VSC - Attempt to read VSC type failed.\n"); */
        }
        mf->vsec_type = EXTRACT(vsec_type, MLX_VSC_TYPE_OFFSET, MLX_VSC_TYPE_LEN);
        /* printf("Device ID: %d mf->wo_addr:%d mf->vsec_addr:%#x mf->vsec_type:%d\n", mf->hw_dev_id, mf->wo_addr, mf->vsec_addr, mf->vsec_type); */

        mf->vpd_cap_addr = pci_find_capability(mf, PCI_CAP_ID_VPD);
        mf->is_cable = is_cable;
        mf->functional_vsec_supp = 0;
        if (mf->vsec_addr && (mf->vsec_type == FUNCTIONAL_VSC))
        {
            if (adv_opt & Clear_Vsec_Semaphore)
            {
                _vendor_specific_sem(mf, 0); /* Clear semaphore */
            }
            mf->pxir_vsec_supp = pci_vsec_spaces_supported(mf);
            mf->functional_vsec_supp = vsec_spaces_supported(mf);
            mf->address_space = AS_CR_SPACE;

            /* printf( */
            /*   "MTCR_UL: mopen_int: HW Device ID: %d mf->wo_addr:%d mf->vsec_addr:%#x mf->vsec_type:%d mf->pxir_vsec_supp:%d\n", */
            /*   mf->hw_dev_id, mf->wo_addr, mf->vsec_addr, mf->vsec_type, mf->pxir_vsec_supp); */
        }
        /* printf("mtcr_open_config Succeeded FUNCTIONAL_VSEC_SUPP: %d\n", mf->functional_vsec_supp); */
#ifndef MST_UL
        if (mf->is_cable)
        {
            mf->flags = MDEVS_CABLE;
            mf->dl_context = mtcr_utils_load_dl_ctx(DL_CABLES);
            dl_handle_t* hdl = (dl_handle_t*)mf->dl_context;
            if (!hdl || !hdl->mcables.mcables_open || hdl->mcables.mcables_open(mf, port))
            {
                mclose(mf);
                return 0;
            }
        }
#endif
        return mf;
    }
    else
    {
        /* printf("mtcr_open_config failed\n"); */
        errno = ENOENT;
        free(mf);
        return NULL;
    }
}

mfile* mopen(const char* name)
{
    return mopen_adv(name, MST_DEFAULT);
}
mfile* mopend(char const* name, DType dtype)
{
    (void)dtype;
    return mopen_int(name, 0);
}

mfile* mopen_adv(const char* name, MType mtype)
{
    mfile* mf = mopend(name, MST_TAVOR);

    if (mf)
    {
        if (mf->tp & mtype)
        {
            return mf;
        }
        else
        {
            errno = EPERM;
            mclose(mf);
            return NULL;
        }
    }
    return mf;
}

mfile* mopen_fw_ctx(void* fw_cmd_context, void* fw_cmd_func, void* dma_func, void* extra_data)
{
    /* not relevant for freebsd */
    (void)fw_cmd_context;
    (void)fw_cmd_func;
    (void)dma_func;
    (void)extra_data;
    return NULL;
}

/*
 * Close Mellanox driver
 * req. descriptor
 */
int mclose(mfile* mf)
{
    if (!mf)
    {
        return 0;
    }
#ifndef MST_UL
    if (mf->tp == MST_CABLE)
    {
        int ret = -1;
        CALL_DL_FUNC(mcables, mcables_close, ret, mf);
        if (ret != -1)
        {
            mtcr_utils_free_dl_ctx(mf->dl_context);
        }
    }
#endif
    /* printf("closing\n"); */
    close(mf->fd);
    if (mf->fdlock)
    {
        close(mf->fdlock);
    }

    if (mf->user_page_list.page_amount)
    {
        release_dma_pages(mf, mf->user_page_list.page_amount);
    }

    /* printf("freeing\n"); */
    free(mf);
    return 0;
}

#define MY_DELAY 20

/*
 * Read 4 bytes, return number of succ. read bytes or -1 on failure
 */
int mread4_old(mfile* mf, unsigned int offset, u_int32_t* value)
{
    int rc;

    offset = __cpu_to_le32(offset);
    if (mf->wo_addr)
    {
        offset |= 0x1;
    }

    int lock_rc;

    lock_rc = _flock_int(mf->fdlock, LOCK_EX);
    if (lock_rc)
    {
        return 0;
    }
    rc = write_config(mf, PCI_CONF_ADDR, (unsigned long)offset, 4);
    if (rc)
    {
        goto cleanup;
    }

    rc = read_config(mf, PCI_CONF_DATA, value, 4);

    if (rc)
    {
        goto cleanup;
    }

    *value = __le32_to_cpu(*value);
cleanup:
    lock_rc = _flock_int(mf->fdlock, LOCK_UN);
    if (lock_rc || rc)
    {
        return 0;
    }
    return 4;
}

int mread4(mfile* mf, unsigned int offset, u_int32_t* value)
{
#ifndef MST_UL
    if (mf->tp == MST_CABLE)
    {
        int rc = 0;
        CALL_DL_FUNC(mcables, mcables_read4, rc, mf, offset, value);
        if (!rc)
        {
            return 4;
        }
        else
        {
            return -1;
        }
    }
#endif
    if (mf->functional_vsec_supp)
    {
        return mread4_new(mf, offset, value);
    }
    return mread4_old(mf, offset, value);
}

/*
 * HACK- Only to pass freebsd compilation
 */
int mread64(mfile* mf, unsigned int offset, void* data, int length)
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
int mwrite64(mfile* mf, unsigned int offset, void* data, int length)
{
    (void)mf;
    (void)offset;
    (void)data;
    (void)length;
    return -1;
}

/* read_config(int fd, struct pcisel *sel, unsigned long reg, int width); */
/* write_config(mf->fd, int fd, struct pcisel *sel, unsigned long reg, unsigned long data, int width) */

/*
 * Write 4 bytes, return number of succ. written bytes or -1 on failure
 */
int mwrite4_old(mfile* mf, unsigned int offset, u_int32_t value)
{
    int rc;

    offset = __cpu_to_le32(offset);
    value = __cpu_to_le32(value);

    int lock_rc;

    lock_rc = _flock_int(mf->fdlock, LOCK_EX);
    if (lock_rc)
    {
        return 0;
    }
    if (mf->wo_addr)
    {
        rc = write_config(mf, PCI_CONF_DATA, (unsigned long)value, 4);
        if (rc)
        {
            goto cleanup;
        }
        rc = write_config(mf, PCI_CONF_ADDR, (unsigned long)offset, 4);
        if (rc)
        {
            goto cleanup;
        }
    }
    else
    {
        rc = write_config(mf, PCI_CONF_ADDR, (unsigned long)offset, 4);
        if (rc)
        {
            goto cleanup;
        }
        rc = write_config(mf, PCI_CONF_DATA, (unsigned long)value, 4);
        if (rc)
        {
            goto cleanup;
        }
    }

cleanup:
    lock_rc = _flock_int(mf->fdlock, LOCK_UN);
    if (lock_rc || rc)
    {
        return 0;
    }
    return 4;
}

int mwrite4(mfile* mf, unsigned int offset, u_int32_t value)
{
#ifndef MST_UL
    if (mf->tp == MST_CABLE)
    {
        int rc = 0;
        CALL_DL_FUNC(mcables, mcables_write4, rc, mf, offset, value);
        if (!rc)
        {
            return 4;
        }
        else
        {
            return -1;
        }
    }
#endif
    if (mf->functional_vsec_supp)
    {
        return mwrite4_new(mf, offset, value);
    }
    return mwrite4_old(mf, offset, value);
}
/*////////// NEW   //////////////////// */

static int mread_chunk_as_multi_mread4(mfile* mf, unsigned int offset, void* data, int length)
{
    int i;

    if (length % 4)
    {
        return -EINVAL;
    }
    for (i = 0; i < length; i += 4)
    {
        u_int32_t value;
        if (mread4(mf, offset + i, &value) != 4)
        {
            return -1;
        }
        memcpy((char*)data + i, &value, 4);
    }
    return length;
}

static int mwrite_chunk_as_multi_mwrite4(mfile* mf, unsigned int offset, void* data, int length)
{
    int i;

    if (length % 4)
    {
        return -EINVAL;
    }
    for (i = 0; i < length; i += 4)
    {
        u_int32_t value;
        memcpy(&value, (char*)data + i, 4);
        if (mwrite4(mf, offset + i, value) != 4)
        {
            return -1;
        }
    }
    return length;
}

int mread4_block(mfile* mf, unsigned int offset, u_int32_t* data, int byte_len)
{
    int rc = byte_len;

#ifndef MST_UL
    if (mf->tp == MST_CABLE)
    {
        int ret = 0;
        CALL_DL_FUNC(mcables, mcables_read4_block, ret, mf, offset, data, byte_len);
        if (ret != 0)
        {
            rc -= ret; /* Return less than byte_len to ensure error in reading */
        }
        return rc;
    }
#endif
    if (mf->functional_vsec_supp)
    {
        int rc = mread4_block_new(mf, offset, byte_len, data);
        /* printf("-D- MREAD BLOCK LEN: %d, RC: %d\n", byte_len, rc); */
        return rc;
    }
    rc = mread_chunk_as_multi_mread4(mf, offset, data, byte_len);
    return rc;
}

int mwrite4_block(mfile* mf, unsigned int offset, u_int32_t* data, int byte_len)
{
    int rc = byte_len;

#ifndef MST_UL
    if (mf->tp == MST_CABLE)
    {
        int ret = 0;
        CALL_DL_FUNC(mcables, mcables_write4_block, ret, mf, offset, data, byte_len);
        if (ret != 0)
        {
            rc -= ret; /* Return less than byte_len to ensure error in reading */
        }
        return rc;
    }
#endif
    if (mf->functional_vsec_supp)
    {
        return mwrite4_block_new(mf, offset, byte_len, data);
    }
    rc = mwrite_chunk_as_multi_mwrite4(mf, offset, data, byte_len);
    return rc;
}

int msw_reset(mfile* mf)
{
    (void)mf;
    return -1;
}

int mhca_reset(mfile* mf)
{
    (void)mf;
    return -1;
}

int mi2c_detect(mfile* mf, u_int8_t slv_arr[SLV_ADDRS_NUM])
{
    (void)mf;
    (void)slv_arr;
    return 1;
}
int mread_i2cblock(mfile* mf, unsigned char i2c_slave, u_int8_t addr_width, unsigned int offset, void* data, int length)
{
    (void)mf;
    (void)i2c_slave;
    (void)addr_width;
    (void)offset;
    (void)data;
    (void)length;
    return 0;
}

int mwrite_i2cblock(mfile* mf, unsigned char i2c_slave, u_int8_t addr_width, unsigned int offset, void* data, int length)
{
    (void)mf;
    (void)i2c_slave;
    (void)addr_width;
    (void)offset;
    (void)data;
    (void)length;
    return 0;
}

int force_i2c_address = -1;
void set_force_i2c_address(int i2c_address)
{
    (void)i2c_address;
}

/* TODO: Introduce a module to keep platform-independent routines like this one below */
void mtcr_fix_endianness(u_int32_t* buf, int len)
{
    int i;

    for (i = 0; i < (len / 4); ++i)
    {
        /* printf("-D- before: buf[%d] = %#x\n", i, buf[i]); */
        buf[i] = __be32_to_cpu(buf[i]);
        /* printf("-D- before: buf[%d] = %#x\n", i, buf[i]); */
    }
}

int mread_buffer(mfile* mf, unsigned int offset, u_int8_t* data, int byte_len)
{
    int rc;

    rc = mread4_block(mf, offset, (u_int32_t*)data, byte_len);
    mtcr_fix_endianness((u_int32_t*)data, byte_len);
    return rc;
}

int mwrite_buffer(mfile* mf, unsigned int offset, u_int8_t* data, int byte_len)
{
    mtcr_fix_endianness((u_int32_t*)data, byte_len);
    return mwrite4_block(mf, offset, (u_int32_t*)data, byte_len);
}

int mget_mdevs_flags(mfile* mf, u_int32_t* devs_flags)
{
    if ((mf == NULL) || (devs_flags == NULL))
    {
        errno = -EINVAL;
        return 1;
    }

    *devs_flags = mf->flags;
    return 0;
}

int mget_mdevs_type(mfile* mf, u_int32_t* mtype)
{
    if ((mf == NULL) || (mtype == NULL))
    {
        errno = -EINVAL;
        return 1;
    }

    *mtype = mf->tp;
    return 0;
}

unsigned char mset_i2c_secondary(mfile* mf, unsigned char new_i2c_slave)
{
    unsigned char ret;

    if (mf)
    {
        ret = mf->i2c_secondary;
        mf->i2c_secondary = new_i2c_slave;
    }
    else
    {
        ret = 0xff;
    }
    return ret;
}

int mget_i2c_secondary(mfile* mf, unsigned char* new_i2c_slave_p)
{
    if (mf)
    {
        *new_i2c_slave_p = mf->i2c_secondary;
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

    if (!mf)
    {
        return 1;
    }

    int lock_rc = _flock_int(mf->fdlock, LOCK_EX);

    if (lock_rc)
    {
        return 1;
    }
    rc = read_config(mf, PCI_HEADER_OFFS, &buf, 4);
    if (rc)
    {
        goto exit;
    }
    dinfo->pci.vend_id = EXTRACT(buf, 0, 16);
    dinfo->pci.dev_id = EXTRACT(buf, 16, 16);

    rc = read_config(mf, PCI_CLASS_OFFS, &buf, 4);
    if (rc)
    {
        goto exit;
    }
    dinfo->pci.class_id = EXTRACT(buf, 8, 24);
    rc = read_config(mf, PCI_SUBSYS_OFFS, &buf, 4);
    if (rc)
    {
        goto exit;
    }
    dinfo->pci.subsys_vend_id = EXTRACT(buf, 0, 16);
    dinfo->pci.subsys_id = EXTRACT(buf, 16, 16);

exit:
    lock_rc = _flock_int(mf->fdlock, LOCK_UN);
    mclose(mf);
    if (lock_rc)
    {
        return 1;
    }
    return rc;
}
static int get_dev_dbdf(const char* dev_name, unsigned int* domain, unsigned int* bus, unsigned int* dev, unsigned int* func)
{
    char* dbdf_str = strstr(dev_name, "pci");
    int rc = 0;

    if (!dbdf_str)
    {
        return 1;
    }
    rc = sscanf(dbdf_str, "pci%u:%u:%u:%u", domain, bus, dev, func);
    if (rc != 4)
    {
        return 1;
    }
    return 0;
}

int get_device_flags(const char* name)
{
    int mask = 0;

    mask = MDEVS_TAVOR_CR;
    if (strstr(name, "cable"))
    {
        mask = MDEVS_CABLE;
    }
    return mask;
}

#define CABLES_DIR "/etc/mft/cables"
#define PUTC(c)            \
    do                     \
    {                      \
        *p++ = (c);        \
        if (++cnt >= len)  \
        {                  \
            closedir(dir); \
            return -1;     \
        }                  \
    } while (0)
#define PUTS(s)                  \
    do                           \
    {                            \
        for (i = 0; (s)[i]; i++) \
        {                        \
            PUTC((s)[i]);        \
        }                        \
    } while (0)

int mdevices_v(char* buf, int len, int mask, int verbosity)
{
    int i;
    int s, b, d, f, tmp;
    int rc = 0;
    int cnt = 0;
    FILE* fp;
    char dev_line[1035];
    char* p = buf;

    if (mask & MDEVS_TAVOR_CR)
    {
        /* Get all Mellanox devices - this cmd will return the needed devices one in every line */
        fp = popen("pciconf -lv | grep -B 1 Mellanox | grep pci | cut -f1 | cut -f2 -d \"@\" | cut -f1-4 -d \":\"", "r");
        if (fp == NULL)
        {
            return -1;
        }

        /* Read the output one line at a time */
        while (fgets(dev_line, sizeof(dev_line) - 1, fp) != NULL)
        {
            tmp = sscanf(dev_line, "pci%d:%d:%d:%d\n", &s, &b, &d, &f);
            (void)tmp; /* TODO: check sscanf ret value */
            if (!verbosity && (f != 0))
            {
                continue;
            }
            for (i = 0; !(dev_line[i] == '\n'); i++)
            {
                *p++ = dev_line[i];
                if (++cnt >= len)
                {
                    pclose(fp);
                    return -1;
                }
            }
            *p++ = 0; /* terminate device */
            rc++;     /* increament the device count */
        }
        /* close */
        pclose(fp);
    }
    if (mask & MDEVS_CABLE)
    {
        /*
         * Get cables
         */
        DIR* dir = opendir(CABLES_DIR);
        struct dirent* dirent;
        if (dir != NULL)
        {
            dirent = readdir(dir);
            while (dirent != NULL)
            {
                char* name = dirent->d_name;
                /* According to mask */
                if (get_device_flags(name) & MDEVS_CABLE)
                {
                    PUTS(name);
                    PUTC('\0');
                    rc++;
                }
                dirent = readdir(dir);
            }
            closedir(dir);
        }
    }
    return rc;
}

int mdevices(char* buf, int len, int mask)
{
    return mdevices_v(buf, len, mask, 0);
}

static void remove_newline_chars(char* str)
{
    int i;

    for (i = strlen(str) - 1; i >= 0 && (str[i] == '\n' || str[i] == '\r'); i--)
    {
        str[i] = '\0';
    }
}

/* replace with a new string */
/* free the old one */
static char* manipulate_ib_dev_line(char* line)
{
    if (!line)
    {
        return NULL;
    }
    char* old_str = line;
    char* new_str = NULL;

    while (*line != '.')
    {
        if (!(*line))
        {
            goto cleanup;
        }
        line++;
    }
    line++;

    char* end = line;
    char* num = NULL;
    int count_dots = 0;

    while (1)
    {
        if (!(*end))
        {
            goto cleanup;
        }
        else if (*end == '.')
        {
            if (count_dots)
            {
                *end = '\0';
                break;
            }
            else
            {
                count_dots++;
                if (*(end + 1))
                {
                    num = end + 1;
                }
                else
                {
                    goto cleanup;
                }
            }
        }
        else if (*end == '_')
        {
            *(end + 1) = '\0';
        }
        end++;
    }
    line = strcat(line, num);
    new_str = (char*)malloc(strlen(line) + 1);
    if (!new_str)
    {
        errno = ENOMEM;
        goto cleanup;
    }
    strcpy(new_str, line);
cleanup:
    free(old_str);

    return new_str;
}

/* number_of_first_entries_to_skip should be 0 for regular array destruction */
static void destroy_str_arr(char** arr, int number_of_first_entries_to_skip)
{
    if (!arr)
    {
        return;
    }
    int i;

    for (i = number_of_first_entries_to_skip; arr[i]; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}

/* copying file lines into a an array of char*, while manipulating each line with a special function (if supplied) */
/* caller should destroy the array */
static char** file2array(FILE* fp, char* (*string_mainpulation_func_ptr)(char*))
{
    char* line = NULL;
    size_t len = 0;
    int lines_allocated = 8; /* can realloc later */
    int error = 0;
    int i = 0;
    char** arr = (char**)malloc((lines_allocated + 1) * sizeof(char*));

    if (!arr)
    {
        errno = ENOMEM;
        error = 1;
        goto cleanup;
    }
    memset(arr, 0, (lines_allocated + 1) * sizeof(char*));

    while (getline(&line, &len, fp) != -1)
    {
        arr[i] = (char*)malloc(len * sizeof(char));
        if (!arr[i])
        {
            errno = ENOMEM;
            error = 1;
            goto cleanup;
        }
        strcpy(arr[i], line);
        free(line);
        line = NULL;
        len = 0;

        remove_newline_chars(arr[i]);
        if (string_mainpulation_func_ptr)
        {
            arr[i] = (*string_mainpulation_func_ptr)(arr[i]);
        }
        if (!arr[i])
        {
            continue;
        }
        i++;
        if (i >= lines_allocated)
        {
            lines_allocated *= 2;
            char** tmp = realloc(arr, (lines_allocated + 1) * sizeof(char*));
            if (!tmp)
            {
                errno = ENOMEM;
                error = 1;
                goto cleanup;
            }
            arr = tmp;
        }
    }
cleanup:
    /* This is done so the caller can free all the array cells without knowing its size */
    /* Iterate until NULL termination */
    if (arr)
    {
        arr[i] = NULL;
    }
    if (line)
    {
        free(line);
    }
    if (error || (i == 0))
    {
        destroy_str_arr(arr, 0);
        return NULL;
    }

    return arr;
}

/* Execute cmd and get output in a strings array, after desired output manipulation */
/* via a speacial manipulation function (if supplied) */
/* if there is relevant input to the special function pass it as well. */
static char** exec_cmd_get_output(char* cmd, char* (*string_mainpulation_func_ptr)(char*))
{
    char* wrapped_cmd = (char*)malloc(strlen(cmd) + strlen(" 2>/dev/null") + 2);

    if (!wrapped_cmd)
    {
        return NULL;
    }
    sprintf(wrapped_cmd, "%s %s", cmd, " 2>/dev/null");
    FILE* fp = popen(wrapped_cmd, "r");

    free(wrapped_cmd);
    if (!fp)
    {
        return NULL;
    }
    char** output = file2array(fp, string_mainpulation_func_ptr);

    pclose(fp);
    return output;
}

static char* exec_cmd_get_output_first_line(char* cmd, char* (*string_mainpulation_func_ptr)(char*))
{
    char** res = exec_cmd_get_output(cmd, string_mainpulation_func_ptr);
    char* out = res[0];

    destroy_str_arr(res, 1);
    return out;
}

static char** get_ports(char* ib_dev)
{
    char* cmd = (char*)malloc(strlen("sysctl sys.class.infiniband..ports | awk -F. '{print $6}' | uniq | sort") + strlen(ib_dev) + 1);

    if (!cmd)
    {
        return NULL;
    }
    sprintf(cmd, "sysctl sys.class.infiniband.%s.ports | awk -F. '{print $6}' | uniq | sort", ib_dev);
    char** out = exec_cmd_get_output(cmd, NULL);

    free(cmd);
    return out;
}

static char* get_link_layer(char* ib_dev, char* port)
{
    char* cmd = (char*)malloc(strlen("sysctl -n sys.class.infiniband..ports..link_layer") + strlen(ib_dev) + strlen(port) + 1);

    if (!cmd)
    {
        return NULL;
    }
    sprintf(cmd, "sysctl -n sys.class.infiniband.%s.ports.%s.link_layer", ib_dev, port);
    char* out = exec_cmd_get_output_first_line(cmd, NULL);

    free(cmd);
    return out;
}

static char* get_eth_net_dev(char* ib_dev, char* port)
{
    char* cmd = (char*)malloc(strlen("sysctl -n sysctl sys.class.infiniband..ports..gid_attrs.ndevs.0") + strlen(ib_dev) + strlen(port) + 1);

    if (!cmd)
    {
        return NULL;
    }
    sprintf(cmd, "sysctl -n sysctl sys.class.infiniband.%s.ports.%s.gid_attrs.ndevs.0", ib_dev, port);
    char* out = exec_cmd_get_output_first_line(cmd, NULL);

    free(cmd);
    return out;
}

static char** get_ifcs()
{
    return exec_cmd_get_output("ifconfig -l | tr \" \" \"\\n\"", NULL);
}

static char* get_gid(char* ib_dev, char* port)
{
    char* cmd = (char*)malloc(strlen("sysctl -n sys.class.infiniband..ports..gids.0 |"
                                     " cut -b 21- | sed -e 's/://g'") +
                              strlen(ib_dev) + strlen(port) + 1);

    if (!cmd)
    {
        return NULL;
    }
    sprintf(cmd, "sysctl -n sys.class.infiniband.%s.ports.%s.gids.0 | cut -b 21- | sed -e 's/://g'", ib_dev, port);
    char* out = exec_cmd_get_output_first_line(cmd, NULL);

    free(cmd);
    return out;
}

static char* lladdr_to_gid_format(char* lladdr)
{
    if (!lladdr)
    {
        return NULL;
    }

    int end = strlen(lladdr) - 1;
    int i;
    int dot_count = 0;

    for (i = end; i >= 0; i--)
    {
        if (lladdr[i] == '.')
        {
            dot_count++;
        }
        if (dot_count == 8)
        {
            lladdr = &lladdr[i];
            break;
        }
        if (i == 0)
        {
            return NULL;
        }
    }
    if (*(lladdr + 1) && *(lladdr + 2) && (*(lladdr + 2) != '.'))
    {
        lladdr++;
    }
    char* curptr = lladdr;

    while (*curptr)
    {
        if (*curptr == '.')
        {
            if (*(curptr + 1) && ((*(curptr + 2) == '.') || !(*(curptr + 2))))
            {
                *curptr = '0';
                curptr++;
            }
            else
            {
                *curptr = '\0';
                if (*(curptr + 1))
                {
                    lladdr = strcat(lladdr, curptr + 1);
                }
            }
        }
        else
        {
            curptr++;
        }
    }
    return lladdr;
}

static char* get_lladdr(char* ifc)
{
    char* cmd = (char*)malloc(strlen("ifconfig  | grep lladdr | awk '{print $2}'") + strlen(ifc) + 1);

    if (!cmd)
    {
        return NULL;
    }
    sprintf(cmd, "ifconfig %s | grep lladdr | awk '{print $2}'", ifc);
    char* lladdr = exec_cmd_get_output_first_line(cmd, NULL);

    free(cmd);
    return lladdr_to_gid_format(lladdr);
}

static char* get_inband_net_dev(char* ib_dev, char* port, char** ifcs)
{
    char* gid = get_gid(ib_dev, port);

    if (!gid)
    {
        return NULL;
    }
    int i;

    for (i = 0; ifcs[i]; i++)
    {
        if (strstr(ifcs[i], "ib") == ifcs[i])
        {
            char* lladdr = get_lladdr(ifcs[i]);
            if (!strcmp(lladdr, gid))
            {
                free(lladdr);
                free(gid);
                char* netdev = (char*)malloc(strlen(ifcs[i]) + 1);
                if (!netdev)
                {
                    errno = ENOMEM;
                    return NULL;
                }
                strcpy(netdev, ifcs[i]);
                return netdev;
            }
            free(lladdr);
        }
    }
    free(gid);
    return NULL;
}

static char** get_net_devs(char** ib_devs)
{
    if (!ib_devs)
    {
        return NULL;
    }
    char** ifcs = get_ifcs();

    if (!ifcs)
    {
        return NULL;
    }
    char** ports = NULL;
    char* link_layer = NULL;
    int i;
    int error = 0;
    int lines_allocated = 8; /* can realloc later */
    char** net_devs = (char**)malloc((lines_allocated + 1) * sizeof(char*));

    if (!net_devs)
    {
        errno = ENOMEM;
        error = 1;
        goto cleanup;
    }
    memset(net_devs, 0, (lines_allocated + 1) * sizeof(char*));
    int k = 0;

    for (i = 0; ib_devs[i]; i++)
    {
        ports = get_ports(ib_devs[i]);
        if (!ports)
        {
            error = 1;
            goto cleanup;
        }
        int j;
        for (j = 0; ports[j]; j++)
        {
            link_layer = get_link_layer(ib_devs[i], ports[j]);
            if (!link_layer)
            {
                error = 1;
                goto cleanup;
            }
            char* netdev;
            if (!strcmp(link_layer, "Ethernet"))
            {
                netdev = get_eth_net_dev(ib_devs[i], ports[j]);
            }
            else if (!strcmp(link_layer, "InfiniBand"))
            {
                netdev = get_inband_net_dev(ib_devs[i], ports[j], ifcs);
            }
            else
            {
                error = 1;
                goto cleanup;
            }
            if (netdev)
            {
                net_devs[k] = netdev;
                k++;
                if (k > lines_allocated)
                {
                    lines_allocated *= 2;
                    char** tmp = realloc(net_devs, (lines_allocated + 1) * sizeof(char*));
                    if (!tmp)
                    {
                        errno = ENOMEM;
                        error = 1;
                        goto cleanup;
                    }
                    net_devs = tmp;
                }
            }
        }
    }
    net_devs[k] = NULL;
cleanup:
    if (error)
    {
        destroy_str_arr(net_devs, 0);
        net_devs = NULL;
    }
    destroy_str_arr(ifcs, 0);
    destroy_str_arr(net_devs, 0);
    destroy_str_arr(ports, 0);
    free(link_layer);
    return net_devs;
}

static char** get_ib_devs(char conf_dev[512])
{
    char* cmd = (char*)malloc(strlen("sysctl -a | grep mlx | grep pci | grep ") + strlen(conf_dev) + 1);

    if (!cmd)
    {
        return NULL;
    }
    sprintf(cmd, "sysctl -a | grep mlx | grep pci | grep %s", conf_dev);
    char** ib_devs = exec_cmd_get_output(cmd, manipulate_ib_dev_line);

    free(cmd);
    return ib_devs;
}

dev_info* mdevices_info(int mask, int* len)
{
    return mdevices_info_v(mask, len, 0);
}

dev_info* mdevices_info_v(int mask, int* len, int verbosity)
{
    char* devs = 0;
    char* dev_name;
    int size = 2048;
    int rc;
    int i;

    /* Get list of devices */
    do
    {
        if (devs)
        {
            free(devs);
        }
        size *= 2;
        devs = malloc(size);
        if (!devs)
        {
            errno = ENOMEM;
            return NULL;
        }
        rc = mdevices_v(devs, size, mask, verbosity);
    } while (rc == -1);
    *len = rc;
    dev_info* dev_info_arr = malloc(sizeof(dev_info) * rc);

    if (!dev_info_arr)
    {
        errno = ENOMEM;
        free(devs);
        return NULL;
    }
    memset(dev_info_arr, 0, sizeof(dev_info) * rc);
    dev_name = devs;
    for (i = 0; i < *len; i++)
    {
        unsigned int domain = 0;
        unsigned int bus = 0;
        unsigned int dev = 0;
        unsigned int func = 0;
        dev_info_arr[i].type = get_device_flags(dev_name);
        strcpy(dev_info_arr[i].dev_name, dev_name);
        strcpy(dev_info_arr[i].pci.conf_dev, dev_name);
        if (dev_info_arr[i].type & MDEVS_TAVOR_CR)
        {
            if (get_dev_dbdf(dev_name, &domain, &bus, &dev, &func))
            {
                goto next;
            }
            dev_info_arr[i].pci.domain = domain;
            dev_info_arr[i].pci.bus = bus;
            dev_info_arr[i].pci.dev = dev;
            dev_info_arr[i].pci.func = func;
            if (get_device_ids(dev_name, &dev_info_arr[i]))
            {
                goto next;
            }
        }
        if (verbosity)
        {
            dev_info_arr[i].pci.ib_devs = get_ib_devs(dev_info_arr[i].pci.conf_dev);
            dev_info_arr[i].pci.net_devs = get_net_devs(dev_info_arr[i].pci.ib_devs);
        }
    next:
        dev_name += strlen(dev_name) + 1;
    }
    free(devs);
    return dev_info_arr;
}

void mdevices_info_destroy(dev_info* dev_info, int len)
{
    int i;

    if (dev_info)
    {
        for (i = 0; i < len; i++)
        {
            if (dev_info[i].pci.ib_devs)
            {
                destroy_str_arr(dev_info[i].pci.ib_devs, 0);
            }
            if (dev_info[i].pci.net_devs)
            {
                destroy_str_arr(dev_info[i].pci.net_devs, 0);
            }
        }
        free(dev_info);
        dev_info = NULL;
    }
}

#define TLV_OPERATION_SIZE 4
#define OP_TLV_SIZE 16
#define REG_TLV_HEADER_LEN 4
static int supports_icmd(mfile* mf);
static int supports_tools_cmdif_reg(mfile* mf);
static int mreg_send_wrapper(mfile* mf, u_int8_t* data, int r_icmd_size, int w_icmd_size);
static int mreg_send_raw(mfile* mf, u_int16_t reg_id, maccess_reg_method_t method, void* reg_data, u_int32_t reg_size, u_int32_t r_size_reg, u_int32_t w_size_reg, int* reg_status);
int mget_max_reg_size(mfile* mf, maccess_reg_method_t reg_method);

/* maccess_reg: Do a reg_access for the mf device. */
/* - reg_data is both in and out */
/* TODO: When the reg operation succeeds but the reg status is != 0, */
/*       a specific */

int maccess_reg(mfile* mf, u_int16_t reg_id, maccess_reg_method_t reg_method, void* reg_data, u_int32_t reg_size, u_int32_t r_size_reg, u_int32_t w_size_reg, int* reg_status)
{
    int rc;

    if ((mf == NULL) || (reg_data == NULL) || (reg_status == NULL) || (reg_size <= 0))
    {
        return ME_BAD_PARAMS;
    }
    /* check register size */
    u_int32_t max_size = (u_int32_t)mget_max_reg_size(mf, reg_method);

    if (reg_size > max_size)
    {
        /* reg too big */
        return ME_REG_ACCESS_SIZE_EXCEEDS_LIMIT;
    }
    rc = mreg_send_raw(mf, reg_id, reg_method, reg_data, reg_size, r_size_reg, w_size_reg, reg_status);
    /* support PCI space */
    if (*reg_status == ME_REG_ACCESS_REG_NOT_SUPP)
    {
        if (VSEC_PXIR_SUPPORT(mf))
        { /* If supported - attempt to */
            /* send the register on PCI VSC */
            /* space */
            swap_pci_address_space(mf);
            rc = mreg_send_raw(mf, reg_id, reg_method, reg_data, reg_size, r_size_reg, w_size_reg, reg_status);
            DBG_PRINTF(
              "Entered PCI VSC space support flow. Second attempt to run mreg_send_raw with VSC address space: %d returned with rc: %d. Restoring address space back to CORE's address space\n",
              mf->address_space,
              rc);
        }
    }

    if (rc)
    {
        return rc;
    }
    else if (*reg_status)
    {
        switch (*reg_status)
        {
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

            case 0xe:
                return ME_REG_ACCESS_NOT_SUPPORTED_BY_SECONDARY;

            case 0x22:
                return ME_REG_ACCESS_CONF_CORRUPT;

            case 0x24:
                return ME_REG_ACCESS_LEN_TOO_SMALL;

            case 0x20:
                return ME_REG_ACCESS_BAD_CONFIG;

            case 0x21:
                return ME_REG_ACCESS_ERASE_EXCEEDED;

            case 0x70:
                return ME_REG_ACCESS_INTERNAL_ERROR;

            default:
                return ME_REG_ACCESS_UNKNOWN_ERR;
        }
    }
    return ME_OK;
}

/*/////////////////  Function that sends the register via the correct interface /////////////////////////// */

static int mreg_send_wrapper(mfile* mf, u_int8_t* data, int r_icmd_size, int w_icmd_size)
{
    int rc;

    if (supports_icmd(mf))
    {
        rc = icmd_send_command_int(mf, FLASH_REG_ACCESS, data, w_icmd_size, r_icmd_size, 0);
        if (rc)
        {
            return rc;
        }
    }
    else if (supports_tools_cmdif_reg(mf))
    {
        rc = tools_cmdif_reg_access(mf, data, w_icmd_size, r_icmd_size);
        if (rc)
        {
            return rc;
        }
    }
    else
    {
        return ME_NOT_IMPLEMENTED;
    }
    return ME_OK;
}

static int mreg_send_raw(mfile* mf, u_int16_t reg_id, maccess_reg_method_t method, void* reg_data, u_int32_t reg_size, u_int32_t r_size_reg, u_int32_t w_size_reg, int* reg_status)
{
    /* printf("-D- reg_id = %d, reg_size = %d, r_size_reg = %d , w_size_reg = */
    /* %d\n",reg_id,reg_size,r_size_reg,w_size_reg); */
    int mad_rc, cmdif_size = 0;
    struct OperationTlv tlv;
    struct reg_tlv tlv_info;
    u_int8_t buffer[1024];

    init_operation_tlv(&(tlv), reg_id, method);
    /* Fill Reg TLV */
    memset(&tlv_info, 0, sizeof(tlv_info));
    tlv_info.Type = TLV_REG;
    tlv_info.len = (reg_size + REG_TLV_HEADER_LEN) >> 2; /* length is in dwords */
    /* Pack the mad */

    cmdif_size += OperationTlv_pack(&tlv, buffer);
    cmdif_size += reg_tlv_pack(&tlv_info, buffer + OP_TLV_SIZE);
    /* put the reg itself into the buffer */
    memcpy(buffer + OP_TLV_SIZE + REG_TLV_HEADER_LEN, reg_data, reg_size);
    cmdif_size += reg_size;

#ifdef _ENABLE_DEBUG_
    fprintf(stdout, "-I-Tlv's of Data Sent:\n");
    fprintf(stdout, "\tOperation Tlv\n");
    OperationTlv_dump(&tlv, stdout);
    fprintf(stdout, "\tReg Tlv\n");
    reg_tlv_dump(&tlv_info, stdout);
#endif
    /* printf("-D- reg_info.len = |%d, OP_TLV: %d, REG_TLV= %d, cmdif_size = %d\n", reg_info.len, OP_TLV_SIZE, */
    /* REG_RLV_HEADER_LEN, cmdif_size); update r/w_size_reg with the size of op tlv and reg tlv as we need to read/write */
    /* them as well */
    r_size_reg += OP_TLV_SIZE + REG_TLV_HEADER_LEN;
    w_size_reg += OP_TLV_SIZE + REG_TLV_HEADER_LEN;
    /* printf("-D- reg_size = %d, r_size_reg = %d , w_size_reg = %d\n",reg_size,r_size_reg,w_size_reg); */

    mad_rc = mreg_send_wrapper(mf, buffer, r_size_reg, w_size_reg);
    /* Unpack the mad */
    OperationTlv_unpack(&tlv, buffer);
    reg_tlv_unpack(&tlv_info, buffer + OP_TLV_SIZE);
    /* copy register back from the buffer */
    memcpy(reg_data, buffer + OP_TLV_SIZE + REG_TLV_HEADER_LEN, reg_size);

#ifdef _ENABLE_DEBUG_
    fprintf(stdout, "-I-Tlv's of Data Received:\n");
    fprintf(stdout, "\tOperation Tlv\n");
    OperationTlv_dump(&tlv, stdout);
    fprintf(stdout, "\tReg Tlv\n");
    reg_tlv_dump(&tlv_info, stdout);
#endif
    /* Check the return value */
    *reg_status = tlv.status;
    if (mad_rc)
    {
        return mad_rc;
    }

    return ME_OK;
}

#define CONNECTX3_HW_ID 0x1f5
#define CONNECTX3_PRO_HW_ID 0x1f7

static int supports_icmd(mfile* mf)
{
    u_int32_t dev_id;

    if (read_device_id(mf, &dev_id) != 4)
    {
        /* cr might be locked and retured 0xbad0cafe but we dont care we search for device that supports icmd */
        return 0;
    }
    switch (dev_id & 0xffff)
    { /* that the hw device id */
        case CONNECTX3_HW_ID:
        case CONNECTX3_PRO_HW_ID:
            return 0;

        default:
            break;
    }
    return 1;
}

static int supports_tools_cmdif_reg(mfile* mf)
{
    u_int32_t dev_id;

    if (read_device_id(mf, &dev_id) != 4)
    {
        return 0;
    }
    switch (dev_id & 0xffff)
    {                             /* that the hw device id */
        case CONNECTX3_HW_ID:     /* Cx3 */
        case CONNECTX3_PRO_HW_ID: /* Cx3-pro */
            if (tools_cmdif_is_supported(mf) == ME_OK)
            {
                return 1;
            }
            return 0;

        default:
            return 0;
    }
}

int mget_max_reg_size(mfile* mf, maccess_reg_method_t reg_method)
{
    if (mf->acc_reg_params.max_reg_size[reg_method])
    {
        return mf->acc_reg_params.max_reg_size[reg_method];
    }
    else if (supports_icmd(mf))
    {
        /* we support icmd and we dont use IB interface -> we use icmd for reg access */
        /* TOOD: get size dynamically from icmd_params once we have support by fw for mfba with size field greater than */
        /* 8 bits */
        mf->acc_reg_params.max_reg_size[reg_method] = ICMD_MAX_REG_SIZE;
    }
    else if (supports_tools_cmdif_reg(mf))
    {
        mf->acc_reg_params.max_reg_size[reg_method] = TOOLS_HCR_MAX_REG_SIZE;
    }
    return mf->acc_reg_params.max_reg_size[reg_method];
}

void mpci_change(mfile* mf)
{
    (void)mf;
}

int mib_smp_get(mfile* mf, u_int8_t* data, u_int16_t attr_id, u_int32_t attr_mod)
{
    (void)mf;
    (void)data;
    (void)attr_id;
    (void)attr_mod;
    errno = ENOSYS;
    return -1;
}

int mib_smp_set(mfile* mf, u_int8_t* data, u_int16_t attr_id, u_int32_t attr_mod)
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

int is_gw_access(mfile* mf)
{
    if (mf->tp == MST_BAR0_GW_PCI)
    {
        return 1;
    }
    return mf->functional_vsec_supp;
}

int mget_addr_space(mfile* mf)
{
    return mf->address_space;
}

/* Return 0 on success like linux implementation */
int mset_addr_space(mfile* mf, int space)
{
    if ((space < 0) || (space >= AS_END))
    {
        return -1;
    }

    /* take semaphore */
    int ret = _vendor_specific_sem(mf, 1);

    if (ret)
    {
        return ret;
    }

    if (_set_addr_space(mf, space))
    {
        /* printf("failed to set VSC address space to: %d. mf->address_space = %d\n", space, mf->address_space); */

        /* clear semaphore */
        _vendor_specific_sem(mf, 0);
        return -1;
    }

    /* clear semaphore */
    _vendor_specific_sem(mf, 0);

    mf->address_space = space;
    /* printf("VSC address space was set successfully to: %d\n", mf->address_space); */
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

    /* Get list of devices */
    do
    {
        if (devs)
        {
            free(devs);
        }
        size *= 2;
        devs = malloc(size);
        if (!devs)
        {
            errno = ENOMEM;
            return 0;
        }
        rc = mdevices_v(devs, size, MDEVS_ALL, 1);
    } while (rc == -1);
    pdevs = devs;
    while (i < rc)
    {
        if (!strcmp(devname, pdevs))
        {
            res = 1;
            goto cleanup;
        }
        pdevs += strlen(pdevs) + 1;
        i++;
    }
cleanup:
    if (devs)
    {
        free(devs);
    }
    return res;
}

int mclear_pci_semaphore(const char* name)
{
    mfile* mf;
    int rc = ME_OK;

    mf = mopen_int(name, Clear_Vsec_Semaphore);
    if (!mf)
    {
        return ME_ERROR;
    }
    if (mf->tp != MST_PCICONF)
    {
        rc = ME_UNSUPPORTED_ACCESS_TYPE;
    }
    mclose(mf);
    return rc;
}

int mvpd_read4_int(mfile* mf, unsigned int offset, u_int8_t value[4])
{
    int vpd_cap = mf->vpd_cap_addr;
    uint16_t write_addr;
    uint32_t read_addr;
    int res;
    int count_to_timeout;
    int done = 0;

    if (!mf || !value)
    {
        return ME_BAD_PARAMS;
    }
    if (!vpd_cap)
    {
        return ME_UNSUPPORTED_OPERATION;
    }
    int lock_rc = _flock_int(mf->fdlock, LOCK_EX);

    if (lock_rc)
    {
        perror("READ VPD");
        return ME_ERROR;
    }
    /* sets F bit to zero and write VPD addr */
    write_addr = (0x7fff & offset);
    res = write_config(mf, vpd_cap + PCI_VPD_ADDR, write_addr, 2);
    if (res)
    {
        res = ME_CR_ERROR;
        goto cleanup;
    }

    /* wait for data until F bit is set with one */
    for (count_to_timeout = 0; count_to_timeout < MST_VPD_DFLT_TIMEOUT; count_to_timeout++)
    {
        res = read_config(mf, vpd_cap + PCI_VPD_ADDR, &read_addr, 2);
        if (res)
        {
            res = ME_CR_ERROR;
            goto cleanup;
        }
        if (read_addr & 0x8000)
        {
            done = 1;
            break;
        }
        sched_yield();
    }
    if (done)
    {
        res = read_config(mf, vpd_cap + PCI_VPD_DATA, (uint32_t*)value, 4);
        if (res)
        {
            res = ME_CR_ERROR;
        }
    }
    else
    {
        res = ME_TIMEOUT;
    }
cleanup:
    lock_rc = _flock_int(mf->fdlock, LOCK_UN);
    if (lock_rc)
    {
        perror("READ VPD");
        return ME_ERROR;
    }
    return res;
}

int mvpd_read4(mfile* mf, unsigned int offset, u_int8_t value[4])
{
    if (offset % 4)
    {
        u_int8_t qword[8] = {0};
        int rc = 0;
        unsigned int aligned_offset = (offset / 4) * 4;
        rc = mvpd_read4_int(mf, aligned_offset, qword);
        if (rc)
        {
            return rc;
        }
        rc = mvpd_read4_int(mf, aligned_offset + 4, qword + 4);
        memcpy(value, qword + (offset % 4), 4);
        return 0;
    }
    else
    {
        return mvpd_read4_int(mf, offset, value);
    }
}

int mvpd_write4(mfile* mf, unsigned int offset, u_int8_t value[4])
{
    (void)mf;
    (void)offset;
    (void)value;
    return ME_UNSUPPORTED_OPERATION;
}

int supports_reg_access_gmp(mfile* mf, maccess_reg_method_t reg_method)
{
    (void)mf;
    (void)reg_method;

    return 0;
}

int get_dma_pages(mfile* mf, struct mtcr_page_info* page_info, int page_amount)
{
    int page_allocated_counter = 0;
    int page_counter = 0;
    int ret_code = ME_OK;

    /* Parameter validation. */
    if (!mf || !page_info)
    {
        return ME_BAD_PARAMS;
    }

    /* Open the memory device file. */
    int file_descriptor = open("/dev/mem", O_RDWR);

    /* Pin the memory in the kernel space. */
    for (page_counter = 0; page_counter < page_amount; page_counter++)
    {
        /* Allocate the buffer. */
        char* current_page = aligned_alloc(PAGE_SIZE, PAGE_SIZE);

        /* Page allocated ? */
        if (!current_page)
        {
            ret_code = ME_MEM_ERROR;
            break;
        }

        page_allocated_counter++;

        if ((uintptr_t)current_page % PAGE_SIZE)
        {
            ret_code = ME_MEM_ERROR;
            break;
        }

        /* We need to call mlock after the pages allocation in order to */
        /*   lock the virtual address space into RAM and preventing that */
        /*   memory from being paged to the swap area. */
        if (mlock(current_page, PAGE_SIZE))
        {
            ret_code = ME_MEM_ERROR;
            break;
        }

        /* Save the virtual address in order to deallocate */
        /*   the memory at the close function. */
        mf->user_page_list.page_list[page_counter] = current_page;

        /* Building the ioctl structure. */
        struct mem_extract memory_user = {};
        memory_user.me_vaddr = (uintptr_t)current_page;

        /* Pin the user memory in the kernel space. */
        int return_code = ioctl(file_descriptor, MEM_EXTRACT_PADDR, &memory_user);

        if (return_code || (memory_user.me_state != ME_STATE_MAPPED))
        {
            ret_code = ME_MEM_ERROR;
            break;
        }

        /* Save the PA and VA for the tool. */
        page_info->page_addresses_array[page_counter].dma_address = memory_user.me_paddr;
        page_info->page_addresses_array[page_counter].virtual_address = (uintptr_t)current_page;
    }

    /* Close the device file /dev/mem. */
    close(file_descriptor);

    if (ret_code)
    {
        release_dma_pages(mf, page_allocated_counter);
    }
    else
    {
        mf->user_page_list.page_amount = page_amount;
    }

    return ret_code;
}

int release_dma_pages(mfile* mf, int page_amount)
{
    /* Parameter validation. */
    if (!mf)
    {
        return -1;
    }

    /* Deallocate the pages. */
    for (int page_counter = 0; page_counter < page_amount; page_counter++)
    {
        if (!mf->user_page_list.page_list[page_counter])
        {
            continue;
        }

        /* Unlocking the virtual address of the page, */
        /*    so that pages in the specified virtual address range may */
        /*    once more to be swapped out if required by the kernel memory manager. */
        munlock(mf->user_page_list.page_list[page_counter], PAGE_SIZE);

        /* Free the user space memory. */
        free(mf->user_page_list.page_list[page_counter]);

        mf->user_page_list.page_list[page_counter] = NULL;
    }

    mf->user_page_list.page_amount = 0;

    return 0;
}

int mset_i2c_addr_width(mfile* mf, u_int8_t addr_width)
{
    (void)mf;
    (void)addr_width;
    return 1;
}
int mget_i2c_addr_width(mfile* mf, u_int8_t* addr_width)
{
    (void)mf;
    (void)addr_width;
    return 1;
}

int set_i2c_freq(mfile* mf, u_int8_t freq)
{
    (void)mf;
    (void)freq;
    return 1;
}

int get_i2c_freq(mfile* mf, u_int8_t* freq)
{
    (void)mf;
    (void)freq;
    return 1;
}

int read_dword_from_conf_space(mfile* mf, u_int32_t offset, u_int32_t* data)
{
    int ret = 0;

    /* Parameters validation. */
    if (!mf || !data)
    {
        return -1;
    }

    /* take semaphore. */
    ret = _vendor_specific_sem(mf, 1);
    if (ret)
    {
        return ret;
    }

    /* set address space. */
    ret = _set_addr_space(mf, mf->address_space);

    if (!ret)
    {
        /* read the data. */
        READ4_PCI(mf, data, offset, "read value", return -1);
    }

    /* clear semaphore */
    _vendor_specific_sem(mf, 0);

    return ret;
}

int mcables_remote_operation_server_side(mfile* mf, u_int32_t address, u_int32_t length, u_int8_t* data, int remote_op)
{
    (void)mf;
    (void)address;
    (void)length;
    (void)data;
    (void)remote_op;
    return 0;
}

int mcables_remote_operation_client_side(mfile* mf, u_int32_t address, u_int32_t length, u_int8_t* data, int remote_op)
{
    (void)mf;
    (void)address;
    (void)length;
    (void)data;
    (void)remote_op;
    return 0;
}

int mlxcables_remote_operation_client_side(mfile* mf, const char* device_name, char op, char flags, const char* reg_name)
{
    (void)mf;
    (void)device_name;
    (void)op;
    (void)flags;
    (void)reg_name;
    return 0;
}

int is_pcie_switch_device(mfile* mf)
{
    (void)mf;

    return 0;
}

int is_remote_dev(mfile* mf)
{
    if (mf)
    {
        return mf->is_remote;
    }

    return 0;
}

static int check_zf_through_memory(mfile* mf)
{
    uint32_t gis = 0; /* Global image status */
    size_t gis_address = 0;

    switch (mf->device_hw_id)
    {
        case DeviceQuantum3_HwId:
        case DeviceNVLink6_Switch_HwId:
            gis_address = 0x152080;
            break;

        default:
            return 0; /* Device does not support Zombiefish mode */
    }
    int rc = mread4(mf, gis_address, &gis);

    if (rc != 4)
    {
        /* printf("-E- Failed to read global_image_status from CR space (BAR0).\n"); */
        return 0;
    }
    gis = EXTRACT(gis, 0, 16); /* Extract the first 16 bits */
    return gis == AUTHENTICATION_FAILURE;
}

static int check_zf_through_vsc(mfile* mf)
{
    int prev_address_space = mf->address_space;

    /* If the device is in LF mode or the recovery space is not supported, the device is not in Zombiefish mode. */
    if (is_livefish_device(mf) || (mset_addr_space(mf, AS_RECOVERY) == -1))
    {
        return 0;
    }

    uint32_t first_dword = 0;
    int rc = mread4(mf, INITIALIZING_BIT_OFFSET_IN_VSC_RECOVERY_SPACE, &first_dword);

    if (rc != 4)
    {
        mset_addr_space(mf, prev_address_space);
        /* printf("-E- Failed to read the first dword in VSC recovery space.\n"); */
        return 0;
    }

    uint32_t in_recovery = EXTRACT(first_dword, 1, 1);       /* Extract bit 1 */
    uint32_t flash_control_vld = EXTRACT(first_dword, 2, 1); /* Extract bit 2 */
    uint32_t initializing = EXTRACT(first_dword, 0, 1);      /* Extract bit 0 */

    mf->vsc_recovery_space_flash_control_vld = flash_control_vld;
    mset_addr_space(mf, prev_address_space);

    if (in_recovery && initializing)
    {
        /* printf("Device with HW ID: %u is in ZombieFish mode. flash_control_vld: %u\n", mf->device_hw_id, */
        /*            flash_control_vld); */
        return 1;
    }

    return 0;
}

int is_zombiefish_device(mfile* mf)
{
    u_int32_t dev_id = 0;

    if (read_device_id(mf, &dev_id) != 4)
    {
        return 0;
    }
    if ((mf->device_hw_id != DeviceConnectX8_HwId) && (mf->device_hw_id != DeviceConnectX8_Pure_PCIe_Switch_HwId) && (mf->device_hw_id != DeviceQuantum3_HwId) &&
        (mf->device_hw_id != DeviceConnectX9_HwId) && (mf->device_hw_id != DeviceNVLink6_Switch_HwId) && (mf->device_hw_id != DeviceConnectX7_HwId) &&
        (mf->device_hw_id != DeviceBlueField3_HwId) && (mf->device_hw_id != DeviceConnectX9_Pure_PCIe_Switch_HwId))
    {
        return 0;
    }

    switch (mf->tp)
    {
        case MST_PCI:
            mf->is_zombiefish = check_zf_through_memory(mf);
            return mf->is_zombiefish;

        case MST_PCICONF:
            mf->is_zombiefish = check_zf_through_vsc(mf);
            return mf->is_zombiefish;

        default:
            return 0;
    }
}

void set_fwctl_dev(char* fwctl_dev, u_int16_t domain, u_int8_t bus, u_int8_t dev, u_int8_t func)
{
    (void)fwctl_dev;
    (void)domain;
    (void)bus;
    (void)dev;
    (void)func;
}