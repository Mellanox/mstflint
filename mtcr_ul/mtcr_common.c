/*
 * Copyright(c) 2025 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.You may choose to be licensed under the terms of the GNU
 * General Public License(GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 * Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 * -Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 * -Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and / or other materials
 * provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "mtcr_common.h"

void swap_pci_address_space(mfile* mf)
{
    switch (mf->address_space) {
    case AS_ICMD_EXT:
        mf->address_space = AS_PCI_ICMD;
        break;

    case AS_ND_CRSPACE:
    case AS_CR_SPACE:
        mf->address_space = AS_PCI_CRSPACE;
        break;

    case AS_ICMD:
        mf->address_space = AS_PCI_ALL_ICMD;
        break;

    case AS_SCAN_CRSPACE:
        mf->address_space = AS_PCI_SCAN_CRSPACE;
        break;

    case AS_SEMAPHORE:
        mf->address_space = AS_PCI_GLOBAL_SEMAPHORE;
        break;

    case AS_PCI_ICMD:
        mf->address_space = AS_ICMD_EXT;
        break;

    case AS_PCI_CRSPACE:
        mf->address_space = AS_CR_SPACE;
        break;

    case AS_PCI_ALL_ICMD:
        mf->address_space = AS_ICMD;
        break;

    case AS_PCI_SCAN_CRSPACE:
        mf->address_space = AS_SCAN_CRSPACE;
        break;

    case AS_PCI_GLOBAL_SEMAPHORE:
        mf->address_space = AS_SEMAPHORE;
        break;

    default:
        DBG_PRINTF("MTCR: swap_pci_address_space: no address_space found: %x\n", mf->address_space);
        return;
    }

    DBG_PRINTF("mf->address_space swapped to: %x\n", mf->address_space);
}

const char* m_err2str(MError status)
{
    switch (status) {
    case ME_OK:
        return "Success";

    case ME_ERROR:
        return "General error";

    case ME_BAD_PARAMS:
        return "Bad Parameter error";

    case ME_CR_ERROR:
        return "CRSpace access error";

    case ME_NOT_IMPLEMENTED:
        return "Interface not implemented";

    case ME_SEM_LOCKED:
        return "Semaphore locked";

    case ME_MEM_ERROR:
        return "Memory error";

    case ME_UNSUPPORTED_OPERATION:
        return "Operation not supported";

    case ME_GMP_MAD_UNSUPPORTED_OPERATION:
        return "Sending GMP MAD supports only Get() method, and you are trying to send Set() method\n"
               "to a register which is not small enough to send with SMP MAD.";

    case ME_MAD_SEND_FAILED:
        return "Failed to send MAD";

    case ME_UNKOWN_ACCESS_TYPE:
        return "Unknown access type";

    case ME_UNSUPPORTED_ACCESS_TYPE:
        return "Unsupported access type";

    case ME_UNSUPPORTED_DEVICE:
        return "Unsupported device";

    /* Reg access errors */
    case ME_REG_ACCESS_BAD_STATUS_ERR:
        return "Register access bad status error";

    case ME_REG_ACCESS_BAD_METHOD:
        return "Bad Reg Access method";

    case ME_REG_ACCESS_NOT_SUPPORTED:
        return "Register access is not supported by the device";

    case ME_REG_ACCESS_DEV_BUSY:
        return "Register access failed, device is busy";

    case ME_REG_ACCESS_VER_NOT_SUPP:
        return "Register access Version not supported";

    case ME_REG_ACCESS_UNKNOWN_TLV:
        return "Register access Unknown TLV";

    case ME_REG_ACCESS_REG_NOT_SUPP:
        return "Register not supported";

    case ME_REG_ACCESS_CLASS_NOT_SUPP:
        return "Register access class not supported";

    case ME_REG_ACCESS_METHOD_NOT_SUPP:
        return "Register access Method not supported";

    case ME_REG_ACCESS_BAD_PARAM:
        return "Register access bad parameter";

    case ME_REG_ACCESS_RES_NOT_AVLBL:
        return "Register access resource unavailable";

    case ME_REG_ACCESS_MSG_RECPT_ACK:
        return "Message receipt ack";

    case ME_REG_ACCESS_UNKNOWN_ERR:
        return "Unknown register error";

    case ME_REG_ACCESS_SIZE_EXCEEDS_LIMIT:
        return "Register is too large";

    case ME_REG_ACCESS_CONF_CORRUPT:
        return "Config Section Corrupted";

    case ME_REG_ACCESS_LEN_TOO_SMALL:
        return "The given Register length is too small for the Tlv";

    case ME_REG_ACCESS_BAD_CONFIG:
        return "The configuration is rejected";

    case ME_REG_ACCESS_ERASE_EXCEEDED:
        return "The erase count exceeds its limit";

    case ME_REG_ACCESS_INTERNAL_ERROR:
        return "Firmware internal error";

    case ME_REG_ACCESS_NOT_SUPPORTED_BY_SECONDARY:
        return "Register Access not supported by secondary";

    case ME_REG_ACCESS_INSUFFICIENT_PERMISSIONS:
            return "Unable to send PRM Register due to permission issue, debug token might be needed.";
    
    case ME_REG_ACCESS_BAD_QP_STATE:
        return "Register access bad QP state";

    case ME_REG_ACCESS_BAD_PKT:
        return "Register access bad packet";

    case ME_REG_ACCESS_BAD_SIZE_OUTS_CQES:
        return "Register access bad size outs CQES";

    case ME_REG_ACCESS_BAD_SYS_STATE:
        return "Register access bad system state";

    case ME_REG_ACCESS_EXCEED_LIM:
        return "Register access exceed limit";

    case ME_REG_ACCESS_BAD_RES_STATE:
        return "Register access bad resource state";

    case ME_REG_ACCESS_BAD_INDEX:
        return "Register access bad index";

    case ME_REG_ACCESS_BAD_INPUT_LEN:
        return "Register access bad input length";

    case ME_REG_ACCESS_BAD_OUTPUT_LEN:
        return "Register access bad output length";

    case ME_REG_ACCESS_NOT_READY:
        return "Register access not ready";

    /* ICMD access errors */
    case ME_ICMD_STATUS_CR_FAIL:
        return "ICMD failed due to CRSpace access failure";

    case ME_ICMD_STATUS_SEMAPHORE_TO:
        return "Timed out trying to take the ICMD semaphore";

    case ME_ICMD_STATUS_EXECUTE_TO:
        return "Timed out polling on the ICMD busy-bit to clear";

    case ME_ICMD_STATUS_IFC_BUSY:
        return "ICMD interface busy with prior request, please wait for it to complete and try again";

    case ME_ICMD_STATUS_ICMD_NOT_READY:
        return "ICMD interface not ready, please check static_config_not_done bit";

    case ME_ICMD_UNSUPPORTED_ICMD_VERSION:
        return "Current ICMD version is not supported, Please check icmd_version field";

    case ME_ICMD_NOT_SUPPORTED:
        return "ICMD interface is not supported for this device";

    case ME_ICMD_INVALID_OPCODE:
        return "ICMD error 0x1: Invalid ICMD opcode used, Please check icmd.ctrl.status field";

    case ME_ICMD_INVALID_CMD:
        return "ICMD error 0x2: Invalid ICMD command used, Please check icmd.ctrl.status field";

    case ME_ICMD_OPERATIONAL_ERROR:
        return "ICMD error 0x3: ICMD operational error, Please check icmd.ctrl.status field";

    case ME_ICMD_BAD_PARAM:
        return "ICMD error 0x4: ICMD bad parameter given, Please check icmd.ctrl.status field";

    case ME_ICMD_BUSY:
        return "ICMD error 0x5: ICMD busy, Please check icmd.ctrl.status field";

    case ME_ICMD_ICM_NOT_AVAIL:
        return "ICMD ICM not available";

    case ME_ICMD_WRITE_PROTECT:
        return "ICMD write protect";

    case ME_ICMD_UNKNOWN_STATUS:
        return "ICMD unknown status";

    case ME_ICMD_SIZE_EXCEEDS_LIMIT:
        return "ICMD size exceeds limit";
    
    case ME_ICMD_UNABLE_TO_TAKE_SEMAOHORE:
            return "Failed to take ICMD semaphore (semaphore 62). Semaphore was free (0) but HW failed to set it to locked state when we took it.\nThis might indicate a FW or HW issue.\n";

    /* TOOLS HCR access errors */
    case ME_CMDIF_BUSY:
        return "Tools HCR busy";

    case ME_CMDIF_TOUT:
        return "Tools HCR time out.";

    case ME_CMDIF_BAD_OP:
        return "Operation not supported";

    case ME_CMDIF_NOT_SUPP:
        return "Tools HCR not supported";

    case ME_CMDIF_BAD_SYS:
        return "bad system status (driver may be down or Fw does not support this operation)";

    case ME_CMDIF_UNKN_TLV:
        return "Unknown TLV";

    case ME_CMDIF_RES_STATE:
        return "Bad reset state";

    case ME_CMDIF_UNKN_STATUS:
        return "Unknown status";

    /* MAD IFC errors */
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
        return "Bad attribute modifier or field";

    case ME_MAD_GENERAL_ERR:
        return "Unknown MAD error";

    default:
        return "Unknown error code";
    }
}
