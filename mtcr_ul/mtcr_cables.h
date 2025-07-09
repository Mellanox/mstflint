#ifndef _MTCR_CABLES_H
#define _MTCR_CABLES_H

#include "mtcr.h"
#include "mtcr_com_defs.h"
#include "dev_mgt/tools_dev_types.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_hca_layouts.h"

typedef reg_access_status_t (*f_reg_access_mcia)(mfile* mf, reg_access_method_t method, struct reg_access_hca_mcia_ext* mcia);

typedef enum {
    MCABLES_OK = 0,
    MCABLES_BAD_PARAMS,
    MCABLES_MEM_ERROR,
    MCABLES_REG_FAILED,
    MCABLES_MAD_FAILED,
    MCABLES_MTUSB_FAILED,
    MCABLES_ACCESS_ERROR,
    MCABLES_NOT_SUPPORTED,

    /* Semaphore errors. */
    MCABLES_SEM_CREATE_FAILED,
    MCABLES_SEM_INIT_FAILED,
    MCABLES_SEM_CLOSE_FAILED,
    MCABLES_SEM_LOCK_FAILED,
    MCABLES_SEM_UNLOCK_FAILED
} MCABLES_ERROR;

typedef enum {
    MLXCABLES_REG_ACCESS = 1,
} cable_access_type_t;


typedef struct {
    int                 port;
    cable_access_type_t cable_access;
    MType               src_tp;
    int                 page_lock;
    unsigned            active;
    unsigned            oui;
    unsigned            page;
    unsigned            fw_gw_version;
    unsigned char       i2c_addr;
    dm_dev_id_t         cable_type;
    void              * semaphore_handle;
    f_reg_access_mcia reg_access_mcia;
} cable_ctx;


/*
 * @brief mcables_open : open the cable device
 * @effect Initialize cable connected to device, update the mfile according
 * @param[in/out] mf - mfile pointer of the device
 * @param[in] port - the port where the cable is connected
 * @return 0 in Success, otherwise in failure
 */
int mcables_open(mfile* mf, int port);

/*
 * @brief mcables_close: close the cable
 * @effect finalize the connection to the cable and free the allocated context
 * @param[in/out] mf - mfile pointer of the device
 * @return 0 in Success, otherwise in failure
 */
int mcables_close(mfile* mf);
/*
 * @brief mcables_read4: read 4 bytes from the cable
 * @effect Read 4 bytes from the cable pages, the address contain page number and offset
 * @param[in]  mf - mfile pointer of the device
 * @param[in]  offset - The address from it to read (0x<PAGE_NUM><PAGE_OFFSET>)
 * @param[out] value - a pointer for dword where the data will be read into it
 * @return 0 in Success, otherwise in failure
 */
int mcables_read4(mfile* mf, u_int32_t offset, u_int32_t* value);

/*
 * @brief mcables_write4: write 4 bytes to the cable
 * @effect Write 4 bytes to the cable pages, the address contain page number and offset
 * @param[in]  mf - mfile pointer of the device
 * @param[in]  offset - The address to it will be written (0x<PAGE_NUM><PAGE_OFFSET>)
 * @param[out] value - a dword to the written data
 * @return 0 in Success, otherwise in failure
 */
int mcables_write4(mfile* mf, u_int32_t offset, u_int32_t value);

/*
 * @brief mcables_read4_block: read dword aligned block from the cable
 * @effect Read block of data from the cable pages, the address contain page number and offset
 * @param[in]  mf - mfile pointer of the device
 * @param[in]  offset - The address from it to read (0x<PAGE_NUM><PAGE_OFFSET>)
 * @param[out] value - a pointer for dwords where the data will be read into it
 * @param[out] byte_len - The length of the data (multiples of 4)
 * @return 0 in Success, otherwise in failure
 */
int mcables_read4_block(mfile* mf, u_int32_t offset, u_int32_t* value, int byte_len);

/*
 * @brief mcables_write4_block: write dword aligned block from the cable
 * @effect Write block of data to the cable pages, the address contain page number and offset
 * @param[in]  mf - mfile pointer of the device
 * @param[in]  offset - The address to it will be written (0x<PAGE_NUM><PAGE_OFFSET>)
 * @param[out] value - a pointer for dwords where the data to be written
 * @param[in] byte_len - The length of the data (multiples of 4)
 * @return 0 in Success, otherwise in failure
 */
int mcables_write4_block(mfile* mf, u_int32_t offset, u_int32_t* value, int byte_len);

#endif /* _MTCR_CABLES_H */
