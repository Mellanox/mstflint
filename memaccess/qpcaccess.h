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

// qpcaccess - Qpc access lib.
//
// This lib provides interface for reading/writing qpc
// through the HCA (qpc GW) .
//

#ifndef QPCACCESS_H
#define QPCACCESS_H

#ifdef __cplusplus
#define EXTERN_C_START extern "C" {
#define EXTERN_C_END   }
#else
#define EXTERN_C_START
#define EXTERN_C_END
#endif

EXTERN_C_START

typedef enum QpcSrc {QSnd = 0x0, QRcv = 0x1, QCmp = 0x2, QSrq = 0x3, QEqe = 0x4, RDB = 0x5, B0_Mcg = 0x6} QpcSrc;

typedef enum {RC = 0, UC = 1, RD = 2, UD = 3, FCP = 4, SRQ = 6, MLX = 7,
              RMC, SRC, RSS, L2, FCPRaw, FCPDefault, FCPCmd, Special, CNP, IBRaw, QpcGw, SW} TransportService;

typedef enum QpcOpt {
    HQO_IGNORE_LOCK = 0,
    HQO_LOCK_RETRY,
    HQO_QPC_GW_ID, //SX=0,LDB=1,RX=2  make default = sx
    HQO_UNIT_ID, //make default value = 0xff13
    HQO_FREE_ON_CLOSE,
    HQO_FAST_READ,
    HQO_CRS_BASE_ADDR, // crspace base address
    HQO_INDEX_REQUEST,
    HQO_ACCESS_VIA_GW, // 0 will be default access by FW, 1 using GW
    HQO_LAST
} QpcOpt;

typedef enum QpcGwAddr {
    QPCGW_SXD = 0x1E600,
    QPCGW_LDB = 0x34800,
    QPCGW_RX  = 0x68800
} QpcGwAddr;

typedef enum QpcError {
    HQE_OK = 0,
    HQE_ERROR,
    HQE_BAD_PARAMS,
    HQE_CR_ERROR,
    HQE_INVAL,
    HQE_NOT_IMPLEMENTED,
    HQE_TIMEOUT,
    HQE_BAD_ALIGN,
    HQE_GW_LOCKED,
    HQE_LAST_STATUS,
    HQE_LAST,
    HQE_BAD_QP
} QpcError;

typedef struct QpcAccess {
    mfile *mf;
    u_int32_t opt[HQO_LAST + 1];
    u_int32_t last_status;
} QpcAccess;

typedef enum QpcOpcode {QpcRd = 0x41, QpcWr = 0x81, QpAdd = 0x82, QpSub = 0x83, QpAnd = 0x84,
                        QpcOr = 0x85, QpXor = 0x86, FtcAd = 0xc2, FtcSb = 0xc3, FtcAnd = 0xc4, FtcOr = 0xc5, FtcXo = 0xc6} QpcOpcode;


typedef struct QpcReq {
    u_int32_t ByteEnable[4];
    u_int8_t Condition;
    u_int32_t CompareOP;
    u_int32_t Mask;
    QpcOpcode Opcode;
    u_int32_t QpNum;
    u_int8_t FastRead[32]; //used to read spesific dw - hot bit per dw
    QpcSrc Source;
    u_int8_t LE;   //4 bits
    u_int8_t MoreCommand;
    u_int8_t QpIndexReq;
    u_int8_t Interrupt;
    u_int8_t DontHWRplace;
    u_int8_t ReadOp;
    u_int8_t DiscardBit; //on write opcode do it all except writing to cache
} QpcReq;

////////////////////////////
//
// Interface functions
//
////////////////////////////

// append an exist device for qpc access
int     qpc_opend(QpcAccess **qpc, mfile *mf);
int     qpc_opend_adv(QpcAccess **qpc, mfile *mf, int force_gw);
/* close access to qpc */
int     qpc_close(QpcAccess *qpc);

/* reads/write qp context according to Req */
int     qpc_read(QpcAccess *qpc, QpcReq *Req, u_int32_t *data, int *status);
int     qpc_write(QpcAccess *qpc, QpcReq *Req, u_int32_t *data, int *status);

/* options set/get */
int     qpc_set_opt(QpcAccess *qpc, QpcOpt opt, u_int32_t val);
int     qpc_get_opt(QpcAccess *qpc, QpcOpt opt, u_int32_t *val);

/* reads fully qpcontext by src and qpnum. user must supplay 1024 bit array with dw alements. */
int     qpc_get_context(QpcAccess *qpc, u_int32_t qpnum, u_int32_t *data, QpcSrc Source); //read qpc

/* same as above only extract dw's according to FastRead[dw] boolean array (for fast access specific fields)*/
int     qpc_get_contextf(QpcAccess *qpc, u_int32_t qpnum, u_int32_t *data, QpcSrc Source, u_int8_t fastread[32], u_int8_t ignore_lock, int *status); //fast read

/* write qpc context */
int     qpc_set_context(QpcAccess *qpc, u_int32_t qpnum, u_int32_t *data, QpcSrc Source); //write qpc



int     qpc_get_last_status(QpcAccess *qpc, u_int32_t *status);

/* error to string */
const char* qpc_err2str(int errCode);

/* Clear qpc gw lock */
int     qpc_clear_semaphore(QpcAccess *qpc);
/*******-----------------------****/
EXTERN_C_END

#endif



