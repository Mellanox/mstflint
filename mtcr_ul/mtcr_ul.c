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

#include <mtcr_ul_com.h>
#include <mtcr_ib.h>
#include <errno.h>
#include <common/tools_utils.h>
#include <stdlib.h>

int mread4(mfile *mf, unsigned int offset, u_int32_t *value)
{
    return mread4_ul(mf, offset, value);
}

int mwrite4(mfile *mf, unsigned int offset, u_int32_t value)
{
    return mwrite4_ul(mf, offset, value);
}

int mread4_block(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len)
{
    return mread4_block_ul(mf, offset, data, byte_len);
}

int mwrite4_block(mfile *mf, unsigned int offset, u_int32_t *data, int byte_len)
{
    return mwrite4_block_ul(mf, offset, data, byte_len);
}

int msw_reset(mfile *mf)
{
#ifndef NO_INBAND
    switch (mf->tp) {
    case MST_IB:
        return mib_swreset(mf);

    default:
        errno = EPERM;
        return -1;
    }
#else
    (void)mf;
    return -1;
#endif
}

int mhca_reset(mfile *mf)
{
    (void) mf;
    errno = ENOTSUP;
    return -1;
}

int mdevices(char *buf, int len, int mask)
{
    return mdevices_ul(buf, len, mask);
}


dev_info* mdevices_info(int mask, int *len)
{
    return mdevices_info_ul(mask, len);
}

dev_info* mdevices_info_v(int mask, int *len, int verbosity)
{
    return mdevices_info_v_ul(mask, len, verbosity);
}

void mdevices_info_destroy(dev_info *dev_info, int len)
{
    int i, j;
    if (dev_info) {
        for (i = 0; i < len; i++) {
            if (dev_info[i].type == MDEVS_TAVOR_CR &&
                dev_info[i].pci.ib_devs) {
                for (j = 0; dev_info[i].pci.ib_devs[j]; j++) {
                    if (dev_info[i].pci.ib_devs[j]) {
                        free(dev_info[i].pci.ib_devs[j]);
                    }
                }
                free(dev_info[i].pci.ib_devs);
            }
            if (dev_info[i].type == MDEVS_TAVOR_CR &&
                dev_info[i].pci.net_devs) {
                for (j = 0; dev_info[i].pci.net_devs[j]; j++) {
                    if (dev_info[i].pci.net_devs[j]) {
                        free(dev_info[i].pci.net_devs[j]);
                    }
                }
                free(dev_info[i].pci.net_devs);
            }

        }
        free(dev_info);
    }
}

mfile* mopen(const char *name)
{
    return mopen_ul(name);
}

mfile* mopend(const char *name, DType dtype)
{
    if (dtype != MST_TAVOR) {
        return NULL;
    }
    return mopen(name);
}

int mclose(mfile *mf)
{
    return mclose_ul(mf);
}

mfile* mopen_adv(const char *name, MType mtype)
{
    mfile *mf = mopend(name, MST_TAVOR);
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

mfile* mopen_fw_ctx(void *fw_cmd_context, void *fw_cmd_func, void *extra_data)
{
    // not implemented
    TOOLS_UNUSED(fw_cmd_context);
    TOOLS_UNUSED(fw_cmd_func);
    TOOLS_UNUSED(extra_data);
    return NULL;
}

unsigned char mset_i2c_slave(mfile *mf, unsigned char new_i2c_slave)
{
    (void) mf;
    (void) new_i2c_slave; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: mset_i2c_slave() is not implemented and has no effect.\n");
    return 0;
}



int maccess_reg_mad(mfile *mf, u_int8_t *data)
{
    return maccess_reg_mad_ul(mf, data);
}

int mos_reg_access(mfile *mf, int reg_access, void *reg_data, u_int32_t cmd_type)
{
    (void) mf;
    (void) reg_data; /* compiler warning */
    (void) cmd_type; /* compiler warning */
    (void) reg_access; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: mos_reg_access() is not implemented and has no effect.\n");
    return ME_NOT_IMPLEMENTED;
}

int maccess_reg_cmdif(mfile *mf, reg_access_t reg_access, void *reg_data, u_int32_t cmd_type)
{
    (void) mf;
    (void) reg_data; /* compiler warning */
    (void) cmd_type; /* compiler warning */
    (void) reg_access; /* compiler warning */
    fprintf(stderr, "Warning: libmtcr: maccess_reg_cmdif() is not implemented and has no effect.\n");
    return ME_NOT_IMPLEMENTED;
}

int mread_buffer(mfile *mf, unsigned int offset, u_int8_t *data, int byte_len)
{
    return mread_buffer_ul(mf, offset, data, byte_len);
}

int mwrite_buffer(mfile *mf, unsigned int offset, u_int8_t *data, int byte_len)
{
    return mwrite_buffer_ul(mf, offset, data, byte_len);
}

int maccess_reg(mfile *mf, u_int16_t reg_id, maccess_reg_method_t reg_method, void *reg_data, u_int32_t reg_size,
                u_int32_t r_size_reg, u_int32_t w_size_reg, int *reg_status)
{
    return maccess_reg_ul(mf, reg_id, reg_method, reg_data, reg_size, r_size_reg, w_size_reg, reg_status);
}

int mget_max_reg_size(mfile *mf, maccess_reg_method_t reg_method)
{
    return mget_max_reg_size_ul(mf, reg_method);
}

int supports_reg_access_gmp(mfile *mf, maccess_reg_method_t reg_method)
{
    return supports_reg_access_gmp_ul(mf, reg_method);
}

int mget_vsec_supp(mfile *mf)
{
    return mf->vsec_supp;
}

MTCR_API int mget_addr_space(mfile *mf)
{
    return mf->address_space;
}

MTCR_API int mset_addr_space(mfile *mf, int space)
{
    if (space < 0 || space >= AS_END) {
         return -1;
     }
    if (VSEC_SUPPORTED_UL(mf) && (mf->vsec_cap_mask & (1 << space_to_cap_offset(space)))) {
         mf->address_space = space;
         return 0;
     }
     return -1;
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

int mclear_pci_semaphore(const char *name)
{
    return mclear_pci_semaphore_ul(name);
}

int mvpd_read4(mfile *mf, unsigned int offset, u_int8_t value[4])
{
    return mvpd_read4_ul(mf, offset, value);
}

int mvpd_write4(mfile *mf, unsigned int offset, u_int8_t value[4])
{
    (void)mf;
    (void)offset;
    (void)value;
    return ME_UNSUPPORTED_OPERATION;
}

