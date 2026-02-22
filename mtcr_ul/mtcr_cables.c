#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdbool.h>
#include "mtcr_cables.h"
#include "mtcr_int_defs.h"
#include "mtcr_common.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/cables_layouts.h"
#include "mtcr_ul_com.h"


#define MAX_PORT_NUM                                       128
#define CABLE_I2C_DEVICE_ADDR                              0x50
#define SECOND_SFP_I2C_ADDR                                0x51
#define CABLE_PAGE_SIZE                                    256
#define NUM_OF_WRITE_PAGE_RETRIES                          5
#define CBLINFO_MAX_SIZE                                   48
#define REG_ID_MCIA                                        0x9014
#define CABLEID_ADDR                                       0x0
#define SFP_DIGITAL_DIAGNOSTIC_MONITORING_IMPLEMENTED_ADDR 92
#define SFP_PAGING_IMPLEMENTED_INDICATOR_ADDR              64

bool is_cable_burn_flow = false;

reg_access_status_t reg_access_mcia(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcia_ext* mcia)
{
    int       data_size = reg_access_hca_mcia_ext_size();
    int       status = 0;
    int       rc;
    int       max_data_size = reg_access_hca_mcia_ext_size();
    u_int8_t* data = ((void *)0);

    if ((method != REG_ACCESS_METHOD_GET) && (method != REG_ACCESS_METHOD_SET)) {
        return ME_REG_ACCESS_BAD_METHOD;
    }
    data = (u_int8_t*)malloc(sizeof(u_int8_t) * max_data_size);
    if (!data) {
        return ME_MEM_ERROR;
    }
    ;
    memset(data, 0, max_data_size);
    reg_access_hca_mcia_ext_pack(mcia, data);
    ;

    /* printf("=======mcia before: ==========\n"); */
    /* reg_access_hca_mcia_ext_dump(mcia, stdout); */
    /* printf("==============================\n"); */

    rc = maccess_reg(mf, REG_ID_MCIA, (maccess_reg_method_t)method, data, data_size, data_size, data_size, &status);
    if (rc && 0) {
        free(data);
    } else {
        reg_access_hca_mcia_ext_unpack(mcia, data);
        /* printf("=======mcia after: ==========\n"); */
        /* reg_access_hca_mcia_ext_dump(mcia, stdout); */
        /* printf("==============================\n"); */
        free(data);
        ;
    } if (rc || status) {
        return (reg_access_status_t)rc;
    }
    return ME_OK;
}


void copy_data(u_int8_t* dest, u_int8_t* src, int size, int be2cpu)
{
    int j = 0;
    int last_bytes = size % 4;

    for (j = 0; j < size / 4; j++) {
        ((u_int32_t*)dest)[j] = __be32_to_cpu(((u_int32_t*)src)[j]);
    }

    if (last_bytes) {
        u_int32_t last_dword = __be32_to_cpu(((u_int32_t*)src)[size / 4]);
        if (be2cpu) {
            memcpy(dest + (size - size % 4), &last_dword, last_bytes);
        } else {
            ((u_int32_t*)dest)[size / 4] = last_dword;
        }
    }
}

/*
 * Implementation of the cable access using access_reg for Read/Write
 */
int cable_access_reg_rw(mfile    * mf,
                        u_int16_t  page_num,
                        u_int16_t  page_off,
                        u_int16_t  size,
                        u_int8_t   port,
                        u_int8_t   page_lock,
                        u_int32_t* data,
                        rw_op_t    _rw)
{
    int ii = 0;
    reg_access_method_t            op = REG_ACCESS_METHOD_GET;
    struct reg_access_hca_mcia_ext cbl_reg_t;

    memset(&cbl_reg_t, 0, sizeof(cbl_reg_t));
    cbl_reg_t.device_address = page_off;
    cbl_reg_t.page_number = page_num;
    cbl_reg_t.i2c_device_address = ((cable_ctx*)(mf->cable_ctx))->i2c_addr;
    cbl_reg_t.module = port;
    cbl_reg_t.size = size;
    cbl_reg_t.l = page_lock;
    if (_rw == WRITE_OP) {
        op = REG_ACCESS_METHOD_SET;
        copy_data((u_int8_t*)cbl_reg_t.dword, (u_int8_t*)data, size, 0);
/* printf("MCIA write: page: %#x, offset: %#x, size: %d\n", page_num, page_off, size); */
/* for (ii=0; ii<size; ii++){ */
/*     printf("MCIA write: data[%d] = %#x \n",ii, cbl_reg_t.dword[ii]); */
/* } */
    }
    reg_access_status_t rc = reg_access_mcia(mf, op, &cbl_reg_t);

    if (rc) {
        DBG_PRINTF("-D- MCIA Failed with rc: %d\n", (int)rc);
        return MCABLES_REG_FAILED;
    }
    if (_rw == READ_OP) {
        copy_data((u_int8_t*)data, (u_int8_t*)cbl_reg_t.dword, size, 1);
        DBG_PRINTF("MCIA read: page: %#x, offset: %#x, size: %d\n", page_num, page_off, size);
        for (ii = 0; ii < size; ii++) {
            DBG_PRINTF("MCIA read: data[%d] = %#x \n", ii, cbl_reg_t.dword[ii]);
        }
    }
/* printf("-D- RW: %d offset: %#x, Len: %#x\n", _rw, page_off, size); */
    return 0;
}

int cable_access_rw(mfile* mf, u_int32_t addr, u_int32_t len, u_int32_t* data, rw_op_t _rw)
{
    MCABLES_ERROR ret = MCABLES_OK;

    if (!mf) {
        return MCABLES_BAD_PARAMS;
    }

    MType      tmp_tp = mf->tp;
    u_int16_t  page_num = addr / CABLE_PAGE_SIZE;
    u_int16_t  device_addr = addr % CABLE_PAGE_SIZE;
    u_int32_t  i = 0;
    int        recover_i2c_addr = 0;
    cable_ctx* ctx = (cable_ctx*)(mf->cable_ctx);

    if (!ctx) {
        return MCABLES_ACCESS_ERROR;
    }

    u_int8_t page_lock = ctx->page_lock;

    mf->tp = ctx->src_tp;
    switch_access_funcs(mf);
    if ((ctx->cable_type == DeviceCableSFP51) || (ctx->cable_type == DeviceCableSFP51Paging)) {
        if (page_num > 0) {
            ctx->i2c_addr = SECOND_SFP_I2C_ADDR;
            page_num--;
            recover_i2c_addr = 1;
        }
    }

    while (i < len) {
        u_int32_t tmp_size = 0;
        u_int32_t page_i = i / CABLE_PAGE_SIZE;
        u_int32_t addr_i = i % CABLE_PAGE_SIZE;
        tmp_size = ((len - i) > CBLINFO_MAX_SIZE) ? CBLINFO_MAX_SIZE : (len - i);
        switch (ctx->cable_access) {
        case MLXCABLES_REG_ACCESS:
            if (cable_access_reg_rw(mf, page_num + page_i, device_addr + addr_i, tmp_size, ctx->port, page_lock,
                                    data + i / 4, _rw)) {
                DBG_PRINTF("cable_access_reg_rw failed\n");
                ret = MCABLES_REG_FAILED;
                goto cleanup;
            }
            break;

        default:
            break;
        }
        i += tmp_size;
    }
cleanup:
    if (recover_i2c_addr) {
        ctx->i2c_addr = CABLE_I2C_DEVICE_ADDR;
    }
    mf->tp = tmp_tp;
    switch_access_funcs(mf);
    /* printf("-D- RW: %d Addr: %#x, Len: %#x, DATA[0]: %#x\n", _rw, addr, len, data[0]); */
    return ret;
}

int mtcr_pciconf_mread4(mfile* mf, unsigned int offset, u_int32_t* value);
int mtcr_pciconf_mwrite4(mfile* mf, unsigned int offset, u_int32_t value);
int mread4_block_pciconf(mfile* mf, unsigned int offset, u_int32_t* value, int byte_len);
int mwrite4_block_pciconf(mfile* mf, unsigned int offset, u_int32_t* value, int byte_len);
int mtcr_pciconf_mclose(mfile* mf);

int mcables_open(mfile* mf, int port)
{
    cable_ctx* cbl;

    mf->flags = MDEVS_CABLE;
    mf->cable_ctx = NULL;

    /* int semaphore_num_of_resources = 1; */

    if (!mf || (port < 0) || (port > MAX_PORT_NUM)) {
        DBG_PRINTF("unable to open cable, invalid args\n");
        return MCABLES_BAD_PARAMS;
    }
    cbl = (cable_ctx*)malloc(sizeof(cable_ctx));
    if (!cbl) {
        return MCABLES_MEM_ERROR;
    }
    memset(cbl, 0, sizeof(cable_ctx));
    cbl->port = port;
    cbl->src_tp = mf->tp;
    cbl->cable_access = MLXCABLES_REG_ACCESS;
    cbl->i2c_addr = CABLE_I2C_DEVICE_ADDR;
    mf->tp = MST_CABLE;
    switch_access_funcs(mf);

    /* // Create the semaphore object. */
    /* cbl->semaphore_handle = create_semaphore(); */
    /* if (!cbl->semaphore_handle) */
    /* { */
    /*     DPRINTF("failed to create cables semaphore\n"); */
    /*     return MCABLES_SEM_CREATE_FAILED; */
    /* } */

    /* int ret_value = semaphore_init(semaphore_num_of_resources, "mcables_sem", cbl->semaphore_handle); */
    /* if (ret_value != SEM_OK && ret_value != SEM_ALREADY_EXISTS) */
    /* { */
    /*     DPRINTF("failed to init cables semaphore\n"); */
    /*     free(cbl->semaphore_handle); */
    /*     cbl->semaphore_handle = NULL; */
    /*     free(cbl); */
    /*     return MCABLES_SEM_INIT_FAILED; */
    /* } */

    /* ret_value = semaphore_lock(cbl->semaphore_handle); */
    /* if (ret_value) */
    /* { */
    /*     DPRINTF("failed to lock cables semaphore\n"); */
    /*     free(cbl->semaphore_handle); */
    /*     cbl->semaphore_handle = NULL; */
    /*     free(cbl); */
    /*     return MCABLES_SEM_LOCK_FAILED; */
    /* } */

    mf->cable_ctx = cbl;

    u_int32_t id = 0;
    int       rw_result = cable_access_rw(mf, 0, 1, (u_int32_t*)&id, READ_OP);

    if (rw_result || (id == 0)) {
        DBG_PRINTF("Failed to read ID from device or id is not supported: id 0x%04x rc %d:\n", id, rw_result);
        mcables_close(mf);

        return MCABLES_ACCESS_ERROR;
    }

    u_int32_t devid = 0;
    int       rc = get_cable_id(mf, &devid, &(cbl->cable_type));

    DBG_PRINTF("cable type: %d\n", cbl->cable_type);
    DBG_PRINTF("devid: %d\n", devid);

    if (rc) {
        DBG_PRINTF("Failed to get dev_mgt device id\n");
        mcables_close(mf);
        return MCABLES_ACCESS_ERROR;
    }
    if ((cbl->cable_type == DeviceCableSFP51) || (cbl->cable_type == DeviceCableSFP51Paging)) {
        cbl->i2c_addr = SECOND_SFP_I2C_ADDR;
        if (cable_access_rw(mf, 0, 1, (u_int32_t*)&id, READ_OP)) {
            /* printf("-D- Failed to read from 0x51 -> return SFP\n"); */
            cbl->cable_type = DeviceCableSFP;
        }
        cbl->i2c_addr = CABLE_I2C_DEVICE_ADDR;
    }

    /* // Semaphore unlock */
    /* ret_value = semaphore_unlock(cbl->semaphore_handle); */
    /* if (ret_value) */
    /* { */
    /*     DPRINTF("failed to unlock cables semaphore\n"); */
    /*     mcables_close(mf); */
    /*     return MCABLES_SEM_UNLOCK_FAILED; */
    /* } */

    DBG_PRINTF("mcables_open finished\n");
    return MCABLES_OK;
}

int mcables_close(mfile* mf)
{
    cable_ctx* cbl = mf->cable_ctx;

    /* semaphore_close(cbl->semaphore_handle); */

    /* // Destroy the semaphore object. */
    /* destroy_semaphore(cbl->semaphore_handle); */

    if (mf && mf->cable_ctx) {
        mf->tp = cbl->src_tp;
        free(mf->cable_ctx);
        mf->cable_ctx = NULL;
    }
    return MCABLES_OK;
}


int mcables_read4(mfile* mf, u_int32_t offset, u_int32_t* value)
{
    if (!mf || !value) {
        return MCABLES_BAD_PARAMS;
    }
    int rc = cable_access_rw(mf, offset, 4, value, READ_OP);

    if (!rc) {
        *value = __cpu_to_le32(*value);
        rc = 4;
    }
    return rc;
}

int mcables_write4(mfile* mf, u_int32_t offset, u_int32_t value)
{
    if (!mf) {
        return MCABLES_BAD_PARAMS;
    }
    int rc = cable_access_rw(mf, offset, 4, &value, WRITE_OP);

    if (!rc) {
        rc = 4;
    }
    return rc;
}

int mcables_read4_block(mfile* mf, u_int32_t offset, u_int32_t* value, int byte_len)
{
    if (!mf || (byte_len % 4) || !value) {
        return MCABLES_BAD_PARAMS;
    }
    int rc = cable_access_rw(mf, offset, byte_len, value, READ_OP);

    if (!rc) {
        int i = 0;
        for (; i < byte_len / 4; i++) {
            value[i] = __cpu_to_le32(value[i]);
        }
        rc = byte_len;
    }
    return rc;
}

int mcables_write4_block(mfile* mf, u_int32_t offset, u_int32_t* value, int byte_len)
{
    if (!mf || (byte_len % 4) || !value) {
        return MCABLES_BAD_PARAMS;
    }
    int rc = cable_access_rw(mf, offset, byte_len, value, WRITE_OP);

    if (!rc) {
        rc = byte_len;
    }
    return rc;
}

int mcables_read_bytes(mfile* mf, u_int32_t offset, u_int8_t* value, int byte_len)
{
    if (!mf || !value) {
        return (int)MCABLES_BAD_PARAMS;
    }
    return (int)cable_access_rw(mf, offset, byte_len, (u_int32_t*)value, READ_OP);
}

int mcables_write_bytes(mfile* mf, u_int32_t offset, u_int8_t* value, int byte_len)
{
    if (!mf || !value) {
        return (int)MCABLES_BAD_PARAMS;
    }
    int rc = (int)cable_access_rw(mf, offset, byte_len, (u_int32_t*)value, WRITE_OP);

    return rc;
}

dm_dev_id_t mcables_get_dm(mfile* mf)
{
    if (mf && mf->cable_ctx) {
        return ((cable_ctx*)(mf->cable_ctx))->cable_type;
    }
    return DeviceUnknown;
}

enum dm_dev_type getCableType(u_int8_t id)
{
    switch (id) {
    case 0xd:
    case 0x11:
    case 0xe:
    case 0xc:
        return DM_QSFP_CABLE;

    case 0x3:
        return DM_SFP_CABLE;

    case 0x18:
    case 0x19:     /* Stallion2 */
    case 0x80:
    case 0x22:
    case 0x1e:
        return DM_CMIS_CABLE;

    default:
        return DM_UNKNOWN;
    }
}


int get_cable_id(mfile* mf, u_int32_t* ptr_hw_dev_id, dm_dev_id_t* ptr_dm_dev_id)
{
    u_int32_t dword = 0;

    /* printf("-D- Getting cable ID\n"); */
    if (mread4(mf, CABLEID_ADDR, &dword) != 4) {
        /* printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno)); */
        return GET_DEV_ID_ERROR;
    }
    /* dword = __cpu_to_le32(dword); // Cable pages are read in LE, no need to swap */
    *ptr_hw_dev_id = 0xffff;
    u_int8_t         id = EXTRACT(dword, 0, 8);
    enum dm_dev_type cbl_type = getCableType(id);

    *ptr_hw_dev_id = id;
    u_int8_t paging;

    if (cbl_type == DM_QSFP_CABLE) {
        /* Get Byte 2 bit 2 ~ bit 18 (flat_mem : upper memory flat or paged. 0=paging, 1=page 0 only) */
        paging = EXTRACT(dword, 18, 1);
        /* printf("DWORD: %#x, paging: %d\n", dword, paging); */
        if (paging == 0) {
            *ptr_dm_dev_id = DeviceCableQSFPaging;
        } else {
            *ptr_dm_dev_id = DeviceCableQSFP;
        }
    } else if (cbl_type == DM_SFP_CABLE) {
        *ptr_dm_dev_id = DeviceCableSFP;
        if (mread4(mf, SFP_DIGITAL_DIAGNOSTIC_MONITORING_IMPLEMENTED_ADDR, &dword) != 4) {
            /* printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno)); */
            return GET_DEV_ID_ERROR;
        }
        u_int8_t byte = EXTRACT(dword, 6, 1); /* Byte 92 bit 6 (digital diagnostic monitoring implemented) */
        if (byte) {
            *ptr_dm_dev_id = DeviceCableSFP51;
            if (mread4(mf, SFP_PAGING_IMPLEMENTED_INDICATOR_ADDR, &dword) != 4) {
                /* printf("FATAL - crspace read (0x%x) failed: %s\n", DEVID_ADDR, strerror(errno)); */
                return GET_DEV_ID_ERROR;
            }
            byte = EXTRACT(dword, 4, 1); /* Byte 64 bit 4 (paging implemented indicator) */
            if (byte) {
                *ptr_dm_dev_id = DeviceCableSFP51Paging;
            }
        }
    } else if (cbl_type == DM_CMIS_CABLE) {
        /* Get Byte 2 bit 7 ~ bit 23 (flat_mem : upper memory flat or paged. 0=paging, 1=page 0 only) */
        paging = EXTRACT(dword, 23, 1);
        if (paging == 0) {
            *ptr_dm_dev_id = DeviceCableCMISPaging;
        } else {
            *ptr_dm_dev_id = DeviceCableCMIS;
        }
    } else {
        *ptr_dm_dev_id = DeviceUnknown;
    }
    return GET_DEV_ID_SUCCESS;
}

void mcables_set_burn_flow(bool burn_flow)
{
    is_cable_burn_flow = burn_flow;
}

MType mcables_get_tp(mfile* mf)
{
    cable_ctx* ctx = (cable_ctx*)(mf->cable_ctx);

    if (!ctx) {
        return 0;
    }
    return ctx->src_tp;
}
