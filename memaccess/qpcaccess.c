/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Aug 2010, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 *  End of legal section ......................................................
 */
#include "bit_slice.h"
#define MTCR_EXPORT
#include <mtcr.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "qpcaccess.h"
#include <cmdif/tools_cif.h>
#include "compatibility.h"
#include <dev_mgt/tools_dev_types.h>
//QpcRd=0x41,QpcWr=0x81S
// Base 1e600


#define QMREAD4(qpa, addr, reg)     if ((mread4(qpa->mf, qpa->opt[HQO_CRS_BASE_ADDR] + addr, &reg)) != 4)  { return HQE_CR_ERROR; }
#define QMWRITE4(qpa, addr, reg)    if ((mwrite4(qpa->mf, qpa->opt[HQO_CRS_BASE_ADDR] + addr, reg)) == -1) { return HQE_CR_ERROR; }
#define CHECK_QPA(qpa)      if (qpa == NULL) {return HQE_ERROR;}
#define CHECK_DATA(data)    if (data == NULL) {return HQE_ERROR;}

#define QPC_GW_ENV_VAR               "HMA_QPC_GW"
#define QPC_V_ENV_VAR                "HMA_QPC_VERBOS"

//int QMREAD4 (mfile *mf, unsigned int offset, u_int32_t value);
//int QMWRITE4(mfile *mf, unsigned int offset, u_int32_t value);

/* offset from gw-base address */
#define QPC_CONF 0x04
#define QPC_CMP_OP 0x0c
#define QPC_MSK 0x08
#define QPC_UID 0x10
#define QPC_QPN 0x0
#define QPC_BUSY 0x100
#define QPC_LE 0x20
#define QPC_DW(i)  0x1fc - i * 4
#define QPC_BE(i)  0x02c - i * 4

/*   4 Bytes: Syndrom
 * 128 Bytes: QPC Context
 */
#define QPC_CONTEXT_DATA_SIZE 148
/*
 * 0x0: 32 bit (Line enable) : 4 bit enable (MSB)
 * 0x4 - 0x10 Byte enable (32-bit mask per line - 4 lines)
 * 128: Data to write
 */
#define ENABLE_MASKS_SIZE 20
#define WRITE_QPC_DATA_SIZE   148

#define DPRINTF(args)        do { char *qpc_verbos = getenv(QPC_V_ENV_VAR); \
                                  if (qpc_verbos != NULL) { \
                                      printf("[QPCACCESS]: -D- "); printf args;} } while (0)
enum {
    QPC_BY_FW_SUPPORTED = 0,
    QPC_BY_FW_NOT_SUPPORTED = 1,
    QPC_BY_FW_ERROR
};
/****** Check if Get QPContext by FW is supported ***********
 *
 * @param mf
 * @return QPC_BY_FW_NOT_SUPPORTED (GW) - Not supported, QPC_BY_FW_SUPPORTED (SUCCESS) - Supported, QPC_BY_FW_ERROR Supported with errors (EXIT)
 */
int check_if_get_qpc_by_fw_is_supported(mfile *mf)
{
#ifndef __FreeBSD__
    dm_dev_id_t dev_type = DeviceUnknown;
    u_int32_t dev_id, chip_rev;
    int rc = 0;
    if (dm_get_device_id(mf, &dev_type, &dev_id, &chip_rev)) {
        return QPC_BY_FW_ERROR;
    }
    if ((dev_type == DeviceConnectX3 || dev_type == DeviceConnectX3Pro) &&
        (mf->tp == MST_PCI || mf->tp == MST_PCICONF)) {
        u_int8_t data[QPC_CONTEXT_DATA_SIZE] = {0};
        rc = tcif_qpc_context_read(mf, 0x0, QSnd, data, QPC_CONTEXT_DATA_SIZE);
        if (rc == ME_CMDIF_BAD_OP) { // command not supported
            return QPC_BY_FW_NOT_SUPPORTED;
        } else if (rc == ME_OK) { //supported
            return QPC_BY_FW_SUPPORTED;
        } else { //internal error
            return QPC_BY_FW_ERROR;
        }
    } else {
        rc = QPC_BY_FW_NOT_SUPPORTED;
    }
    return rc;
#else
    (void)mf;
    return QPC_BY_FW_NOT_SUPPORTED;
#endif
}



/*******************************************************************************************************/

/***************************************qpc_opend****************************************************************/

int     qpc_opend(QpcAccess **qpc, mfile *mf)
{
    return qpc_opend_adv(qpc, mf, 1);
}

int     qpc_opend_adv(QpcAccess **qpc, mfile *mf, int force_gw)
{

    int i;
    char *env_gw;
    *qpc = (QpcAccess*)malloc(sizeof(QpcAccess));
    CHECK_QPA(*qpc);

    (*qpc)->mf = mf;

    for (i = 0; i < HQO_LAST; i++) { /*initalize */
        (*qpc)->opt[i] = 0;
    }
    /*defaults*/
    // SX=0,LDB=1,RX=2  make default = sx
    // UnitID = 0xff13
    (*qpc)->opt[HQO_QPC_GW_ID]     = 0;
    (*qpc)->opt[HQO_UNIT_ID]       = 0xff13;
    (*qpc)->opt[HQO_FREE_ON_CLOSE] = 1;
    (*qpc)->opt[HQO_CRS_BASE_ADDR] = QPCGW_LDB; //   default
    (*qpc)->opt[HQO_LOCK_RETRY]    = 20;
    if (!force_gw) {
        int rc = check_if_get_qpc_by_fw_is_supported(mf);
        if (rc == QPC_BY_FW_ERROR) {
            free(*qpc);
            return HQE_ERROR;
        } else if (rc == QPC_BY_FW_SUPPORTED) {
            (*qpc)->opt[HQO_ACCESS_VIA_GW] = 0;
        } else {
            (*qpc)->opt[HQO_ACCESS_VIA_GW] = 1;
        }
    } else {
        (*qpc)->opt[HQO_ACCESS_VIA_GW] = 1;
    }
    env_gw = getenv(QPC_GW_ENV_VAR);
    if (env_gw != NULL) {
        if      (!strcmp(env_gw, "LDB")) {
            (*qpc)->opt[HQO_CRS_BASE_ADDR] = QPCGW_LDB;
        } else if (!strcmp(env_gw, "RX")) {
            (*qpc)->opt[HQO_CRS_BASE_ADDR] = QPCGW_RX;
        } else if (!strcmp(env_gw, "SXD")) {
            (*qpc)->opt[HQO_CRS_BASE_ADDR] = QPCGW_SXD;
        } else {
            fprintf(stderr, "-W- Bad value in env var %s (%s) expecting LDB|RX|SXD. Ignoring.\n",
                    QPC_GW_ENV_VAR,
                    env_gw);
        }
    }

    return HQE_OK;
}

/*******************************************************************************************************/




/***************************************qpc_close****************************************************************/
int     qpc_close(QpcAccess *qpc)
{
    CHECK_QPA(qpc);
    if (qpc->opt[HQO_FREE_ON_CLOSE] == 1) {
        free(qpc);
    }
    return HQE_OK;
}


/*******************************************************************************************************/


/***************************************qpc_drive_req****************************************************************/
int     qpc_drive_req(QpcAccess *qpa, QpcReq *Req, u_int32_t *data, int *status    )
{
    u_int32_t Register = 0;
    u_int8_t Lock = 0;
    u_int8_t Busy;
    int i;
    u_int32_t counter = 0;
    u_int8_t RW_ = (Req->Opcode > 0x90 || Req->Opcode < 0x80) ? 1 : Req->ReadOp; // 0x80<write_op<0x90

    /* handle Lock macanism */
    CHECK_QPA(qpa);
    CHECK_DATA(data);

    //Register=0;
    //QMWRITE4(mf,QPC_BUSY,Register);
    //printf("unlocking gw....");
    QMREAD4(qpa, QPC_BUSY, Register);    // Lock (at lease try) even if HQO_IGNORE_LOCK is set
    if (!qpa->opt[HQO_IGNORE_LOCK]) {  /* dont ignore lock */

        Lock =  (EXTRACT(Register, 31, 1) == 1);
        if (Lock) {  /* gw is locked */
            if (!qpa->opt[HQO_LOCK_RETRY]) {  /* locked and not wait */
                return HQE_GW_LOCKED;
            } else {  /* pooling on loc */
                while (Lock && counter < qpa->opt[HQO_LOCK_RETRY]) {
                    QMREAD4(qpa, QPC_BUSY, Register);
                    Lock =  (EXTRACT(Register, 31, 1) == 1);
                    counter++;
                }
            }
        }
    }

    //TODO: orenk: unify it with the lock loop.
    if (Lock && counter >= qpa->opt[HQO_LOCK_RETRY]) {
        //printf("-D- HQE_GW_LOCKED counter = %d \n",counter);

        return HQE_GW_LOCKED;
    }

    // write BE for write
    if (Req->Opcode != QpcRd) {
        for (i = 0; i < 4; i++) {
            QMWRITE4(qpa, QPC_BE(i), Req->ByteEnable[i]);
        }
    }

    // write configuration
    Register = Req->Condition;
    Register = MERGE(Register, Req->LE, 16, 4);
    Register = MERGE(Register, Req->ReadOp, 25, 1);
    Register = MERGE(Register, Req->DiscardBit, 26, 1);
    Register = MERGE(Register, Req->QpIndexReq, 27, 1);
    Register = MERGE(Register, Req->MoreCommand, 28, 1);
    Register = MERGE(Register, Req->DontHWRplace, 30, 1);
    Register = MERGE(Register, Req->Interrupt, 21, 1);
    QMWRITE4(qpa, QPC_CONF, Register );
    // write cmp_op
    QMWRITE4(qpa, QPC_CMP_OP, Req->CompareOP);
    //write mask
    QMWRITE4(qpa, QPC_MSK, Req->Mask);
    //write uid
    Register = 0;
    Register = MERGE(Register, (u_int32_t)qpa->opt[HQO_UNIT_ID], 16, 16);
    QMWRITE4(qpa, QPC_UID, Register);
    // write qpn & src
    Register = Req->QpNum;
    Register = MERGE(Register, Req->Source, 24, 4);

    QMWRITE4(qpa, QPC_QPN, Register);

    //write data
    if (RW_ == 0) { //write
        Register = 0xffffffff;
        for (i = 0; i < 4; i++) {
            QMWRITE4(qpa, QPC_LE + 4 * i, Register);

        }

        // write 32 dw to the qpcgw

        for (i = 0; i < 32; i++) {
            if (EXTRACT(Req->LE, i / 8, 1) == 1) { //if dw enable
                QMWRITE4(qpa, QPC_DW(i), data[i]);
            }
        }
    }

    // activate
    Register = 0;
    Register = MERGE(Register, Req->Opcode, 20, 8);
    Register = MERGE(Register, RW_, 29, 1);
    Register = MERGE(Register, 3, 30, 2); // busy and lock

    QMWRITE4(qpa, QPC_BUSY, Register);

    /*wait for busy*/
    Busy = true;
    counter = 5000;
    while (Busy && counter) {
        QMREAD4(qpa, QPC_BUSY, qpa->last_status);           // -M-
        Busy = (EXTRACT(qpa->last_status, 30, 1) == 1);   // -M-
        counter--;
    }
    if (counter == 0) {
        return HQE_TIMEOUT;
    }

    *status = EXT(qpa->last_status, 7, 0);  // -M-

    if (*status != 0) {
        // printf("-D- error reported from gw: 0x%02x\n", *status  );
        // unlock:
        Register = 0;
        //Register = MERGE(Register,0,31,1);
        QMWRITE4(qpa, QPC_BUSY, Register);
        return HQE_BAD_QP;
    }

    /*read response if read */
    if (RW_ != 0) {
        for (i = 0; i < 32; i++) {
            if (qpa->opt[HQO_FAST_READ] == 0 || (qpa->opt[HQO_FAST_READ] == 1 && Req->FastRead[i] == 1)) {

                QMREAD4(qpa, QPC_DW(i), data[i]);
            }
        }
    }

    // todo : check for syndrom

    Register = 0;
    QMWRITE4(qpa, QPC_BUSY, Register); //unlock gw

    return HQE_OK;
}

/*******************************************************************************************************/




/***************************************qpc_get_contextf****************************************************************/

int   qpc_get_contextf( QpcAccess *qpc,
                        u_int32_t qpnum,
                        u_int32_t *data,
                        QpcSrc Source,
                        u_int8_t FastRead[32],
                        u_int8_t ignore_lock,
                        int *status)
{ //fast read
    int i;
    u_int32_t val = 0;
    QpcReq MyReq;
    CHECK_QPA(qpc);
    CHECK_QPA(data);
    qpc_get_opt(qpc, HQO_INDEX_REQUEST, &val);
    u_int32_t qpcIndex;

    if (Source == B0_Mcg) {
        u_int8_t logStride;
        u_int32_t reg = 0, addr;
#define MCG_LOG_ENTRY_SIZE 0x44240
        addr = MCG_LOG_ENTRY_SIZE;
        int rc = mread4(qpc->mf, addr, &reg);
        if (rc != 4) {
            return HQE_CR_ERROR;
        }
        logStride = reg & 0x1f;
        qpcIndex = qpnum << logStride;
    } else {
        qpcIndex = qpnum;
    }


    MyReq.ReadOp = 0;
    MyReq.DiscardBit = 0;
    MyReq.DontHWRplace = 0;
    MyReq.Interrupt = 0;
    MyReq.Mask = 0;
    MyReq.MoreCommand = 0;
    MyReq.Opcode = QpcRd;
    MyReq.QpNum = qpcIndex;
    MyReq.Source = Source;
    MyReq.Condition = 0;
    MyReq.CompareOP = 0;
    MyReq.QpIndexReq = (u_int8_t) val;

    qpc_set_opt(qpc, HQO_FAST_READ, 1);
    if (ignore_lock) {
        qpc_set_opt(qpc, HQO_IGNORE_LOCK, 1);
    }


    for (i = 0; i < 32; i++) {
        MyReq.FastRead[i] = FastRead[i];
    }

    return qpc_read(qpc, &MyReq, data, status);
}

/*******************************************************************************************************/




/*********************************************qpc_set_context**********************************************************/
int     qpc_set_context(QpcAccess *qpc, u_int32_t qpnum, u_int32_t *data, QpcSrc Source)
{
    QpcReq MyReq;
    int status;
    CHECK_QPA(data);
    CHECK_DATA(qpc);

    MyReq.ReadOp = 0;
    MyReq.DiscardBit = 0;
    MyReq.DontHWRplace = 0;
    MyReq.Interrupt = 0;
    MyReq.Mask = 0;
    MyReq.MoreCommand = 0;
    MyReq.Opcode = QpcWr;
    MyReq.QpIndexReq = 0;
    MyReq.QpNum = qpnum;
    MyReq.Source = Source;
    MyReq.Condition = 0;
    MyReq.CompareOP = 0;
    MyReq.LE = 0xf;

    return qpc_write(qpc, &MyReq, data, &status);
}


/***************************************qpc_get_context****************************************************************/

int qpc_get_context(QpcAccess *qpc, u_int32_t qpnum, u_int32_t *data, QpcSrc Source )
{
    QpcReq MyReq;
    int i, status;
    CHECK_QPA(data);
    CHECK_DATA(qpc);

    MyReq.ReadOp = 0;
    MyReq.DiscardBit = 0;
    MyReq.DontHWRplace = 0;
    MyReq.Interrupt = 0;
    MyReq.Mask = 0;
    MyReq.MoreCommand = 0;
    MyReq.Opcode = QpcRd;
    MyReq.QpIndexReq = 0;
    MyReq.QpNum = qpnum;
    MyReq.Source = Source;
    MyReq.Condition = 0;
    MyReq.CompareOP = 0;

    qpc_set_opt(qpc, HQO_FAST_READ, 0);
    for (i = 0; i < 32; i++) {
        MyReq.FastRead[i] = 0;
    }

    return qpc_read(qpc, &MyReq, data, &status);
}

/*******************************************************************************************************/


/***************************************qpc_read****************************************************************/
int     qpc_read(QpcAccess *qpc, QpcReq *Req, u_int32_t *data, int *status)
{
#ifndef __FreeBSD__
    int rc = 0;
    int i = 0;
    u_int32_t tdata[QPC_CONTEXT_DATA_SIZE / 4] = {0};
    if (qpc->opt[HQO_ACCESS_VIA_GW]) { // Using GW (Force / Not supported)
#endif
    DPRINTF(("Getting QPC Context via GW - Src: 0x%x QPN: 0x%x\n", Req->Source, Req->QpNum));
    return qpc_drive_req(qpc, Req, data, status);
#ifndef __FreeBSD__
} else {
    DPRINTF(("Getting QPC Context via FW command - Src: 0x%x QPN: 0x%x\n", Req->Source, Req->QpNum));
    rc = tcif_qpc_context_read(qpc->mf, Req->QpNum, Req->Source, (u_int8_t*)tdata, QPC_CONTEXT_DATA_SIZE);
    if (rc) {
        return HQE_ERROR;
    }
    qpc->last_status = __be32_to_cpu(tdata[0]);
    *status = EXT(qpc->last_status, 7, 0);
    if (*status) {
        return HQE_BAD_QP;
    }
    for (i = 5; i < QPC_CONTEXT_DATA_SIZE / 4; i++) {
        int j = i - 5;
        int k = QPC_CONTEXT_DATA_SIZE / 4 - j - 1;
        data[j] = __be32_to_cpu(tdata[k]);
    }
    return HQE_OK;
}
#endif
}

/*******************************************************************************************************/

/***************************************ADVANCE qpc_write****************************************************************/

/*
   int qpc_write_advanced(QpcAccess* qpc, QpcReq* Req, u_int32_t* data, u_int32_t* mask, int* status)
   {
    u_int32_t tdata[WRITE_QPC_DATA_SIZE / 4]= {0};
    int rc = 0;
    int i = 0;
    for (i = 0; i < ENABLE_MASKS_SIZE / 4; i++) {
        tdata[i] = mask[i];
    }
    memcpy(tdata + i, data, QPC_CONTEXT_DATA_SIZE - (i * 4));
    rc = tcif_qpc_context_write(qpc->mf, Req->QpNum, Req->Source,(u_int8_t*) data, WRITE_QPC_DATA_SIZE);
    if (rc) {
        return HQE_ERROR;
    }
    qpc->last_status = __be32_to_cpu(tdata[0]);
 * status = EXT(qpc->last_status,7,0);
    if (*status) {
        return HQE_BAD_QP;
    }
    return HQE_OK;
   }
 */


/***************************************qpc_write****************************************************************/
int     qpc_write(QpcAccess *qpc, QpcReq *Req, u_int32_t *data, int *status)
{
    //
/*#ifndef __FreeBSD__
    if (qpc->opt[HQO_ACCESS_VIA_GW]) { // Using GW
 #endif*/
    return qpc_drive_req(qpc, Req, data, status);
/*#ifndef __FreeBSD__
    } else {
        u_int32_t bytes_enable[ENABLE_MASKS_SIZE / 4] = {0xf0000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
        return qpc_write_advanced(qpc, Req, data, bytes_enable, status);
    }
 #endif*/
}

/*******************************************************************************************************/


/***************************************qpc_set_opt****************************************************************/
int     qpc_set_opt(QpcAccess *qpc, QpcOpt opt, u_int32_t val)
{
    if (qpc != NULL && (int)opt >= 0 && opt <= HQO_LAST) {
        qpc->opt[opt] = val;
    } else {
        return HQE_BAD_PARAMS; // hma NULL
    }
    return HQE_OK;
}

/*******************************************************************************************************/


/***************************************qpc_get_opt****************************************************************/
int     qpc_get_opt(QpcAccess *qpc, QpcOpt opt, u_int32_t *val)
{
    if (qpc != NULL && val != NULL && (int)opt >= 0 && opt <= HQO_LAST) {
        *val = qpc->opt[opt];
    } else {
        return HQE_BAD_PARAMS; // hma or val are NULL
    }
    return HQE_OK;
}

u_int64_t QPC_DEC(u_int32_t *data, int end, int start)
{
    u_int64_t res;
    if (start / 32 == end / 32) {
        return EXT(data[start / 32], end % 32, start % 32);
    } else {
        res = EXT(data[start / 32], 31, (start % 32));
        return MERGE64(res, EXT(data[end / 32], end % 32, 0), 32 - (start % 32), (end % 32) + 1);
    }
}

/*******************************************************************************************************/


/***************************************qpc_get_last_satatus***************************************************/
int     qpc_get_last_status(QpcAccess *qpc, u_int32_t *status)
{
    *status = qpc->last_status;
    return HQE_OK;

}

#define QPCARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))
const char* qpc_err2str(int errCode)
{
    static char *qpc_err_str[] = {
        "HQE_OK",
        "HQE_ERROR",
        "HQE_BAD_PARAMS",
        "HQE_CR_ERROR",
        "HQE_INVAL",
        "HQE_NOT_IMPLEMENTED",
        "HQE_TIMEOUT",
        "HQE_BAD_ALIGN",
        "HQE_GW_LOCKED",
        "HQE_LAST_STATUS",
        "HQE_LAST",
        "HQE_BAD_QP"
    };
    return errCode < (int)QPCARRSIZE(qpc_err_str) ? qpc_err_str[errCode] : "Unknown error";
}

int qpc_clear_semaphore(QpcAccess *qpc)
{
    int reg = 0;
    if (!qpc) {
        return HQE_BAD_PARAMS;
    }
    QMWRITE4(qpc, QPC_BUSY, reg); //unlock gw
    return HQE_OK;
}
