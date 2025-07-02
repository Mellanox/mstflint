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

#include <cstring>
#include <iostream>
#include <nvml.h>
#include "nvml_device.h"
#include "nvml_lib_wrapper.h"
#include "nvml_exception.h"
#include "reg_access/reg_ids.h"
#include "tools_layouts/reg_access_hca_layouts.h"
#include "tools_layouts/reg_access_gpu_layouts.h"

NvmlDevice::NvmlDevice(const unsigned int deviceIndex)
{
    nvmlReturn_t error = NVML_SUCCESS;

    _nvmlDevice = nullptr;
    _nvmlLibWrapper = std::unique_ptr < NvmlLibWrapper > (new NvmlLibWrapper());


    /* Init device handle by index (e.g. /dev/nvidiaX) */
    error = _nvmlLibWrapper->nvmlDeviceGetHandleByIndex_v2(deviceIndex, &_nvmlDevice);

    if (_nvmlDevice == nullptr) {
        throw NvmlException("Failed to open MVNL GPU device by index: %d: %s\n",
                            deviceIndex,
                            _nvmlLibWrapper->nvmlErrorString(error));
    }
}

u_int16_t NvmlDevice::GetPciID()
{
    nvmlPciInfo_t pci;

    memset(&pci, 0, sizeof(pci));

    nvmlReturn_t error = _nvmlLibWrapper->nvmlDeviceGetPciInfo_v3(_nvmlDevice, &pci);

    if (error) {
        throw NvmlException("Failed to obtain PCI ID: %s\n",
                            _nvmlLibWrapper->nvmlErrorString(error));
    }
    /* Mask out vendor ID on the lower 16  bits. */
    return ((pci.pciDeviceId & 0xffff0000) >> 16);
}

int NvmlDevice::SendPRMRegister(unsigned char    * registerData,
                                const unsigned int registerSize,
                                const unsigned int registerID,
                                int&               registerStatus,
                                bool               isWrite)
{
    /* Set PRM Buffer version. */
    nvmlPRMBuffer_t prmBuffer;

    memset(&prmBuffer, 0, sizeof(prmBuffer));
    prmBuffer.version = nvmlPRMBuffer_v1;
    prmBuffer.isWrite = isWrite;

    switch (registerID) {
    case REG_ID_MGIR:
        registerStatus = AccessRegisterMGIR(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PLIB:
        registerStatus = AccessRegisterPLIB(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PMLP:
        registerStatus = AccessRegisterPMLP(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PTYS:
        registerStatus = AccessRegisterPTYS(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PAOS:
        registerStatus = AccessRegisterPAOS(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PPCNT:
        registerStatus = AccessRegisterPPCNT(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PMAOS:
        registerStatus = AccessRegisterPMAOS(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_SLTP:
        registerStatus = AccessRegisterSLTP(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PDDR:
        registerStatus = AccessRegisterPDDR(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PPHCR:
        registerStatus = AccessRegisterPPHCR(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PPAOS:
        registerStatus = AccessRegisterPPAOS(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PGUID:
        registerStatus = AccessRegisterPGUID(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_PPSLS:
        registerStatus = AccessRegisterPPSLS(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_MTCAP:
        registerStatus = AccessRegisterMTCAP(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_MORD:
        registerStatus = AccessRegisterMORD(registerData, registerSize, prmBuffer);
        break;

    case REG_ID_MCAM:
        registerStatus = AccessRegisterMCAM(registerData, registerSize, prmBuffer);
        break;

    default:
        throw NvmlException("NVML does not support register ID 0x%x\n", registerID);
    }

    return 0;
}

/* int NvmlDevice::TranslateNvStatus(unsigned int uNvStatus) */
/* { */
/*     switch (uNvStatus) { */
/*     case NV_OK: */
/*         return 0x0; */

/*     case NVML_ERROR_BUSY_RETRY: */
/*         return 0x1; */

/*     case NVML_ERROR_INVALID_PARAM_STRUCT: */
/*         return 0x3; */

/*     case NVML_ERROR_INVALID_FUNCTION: */
/*         return 0x4; */

/*     case NVML_ERROR_INVALID_CLASS: */
/*         return 0x5; */

/*     case NVML_ERROR_INVALID_METHOD: */
/*         return 0x6; */

/*     case NVML_ERROR_INVALID_PARAMETER: */
/*         return 0x7; */

/*     case NVML_ERROR_IN_USE: */
/*         return 0x8; */

/*     case NVML_ERROR_MORE_PROCESSING_REQUIRED: */
/*         return 0x9; */

/*     case NVML_ERROR_INVALID_STATE: */
/*         return 0x70; */

/*     default: */
/*         return uNvStatus; */
/*     } */
/* } */

int NvmlDevice::AccessRegisterMGIR(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t&   prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.mgir.version = nvmlMGIR_v1;
    prmBuffer.regId = NVML_GPU_PRM_MGIR;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending MGIR: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}


int NvmlDevice::AccessRegisterPLIB(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.plib.version = nvmlPLIB_v1;
    prmBuffer.regId = NVML_GPU_PRM_PLIB;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_plib_reg_ext plibReg;

    memset(&plibReg, 0, sizeof(plibReg));
    reg_access_gpu_plib_reg_ext_unpack(&plibReg, registerData);
    prmBuffer.plib.ibPort = plibReg.ib_port;
    prmBuffer.plib.lpMsb = plibReg.lp_msb;
    prmBuffer.plib.localPort = plibReg.local_port;
    prmBuffer.plib.splitNum = plibReg.split_num;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PLIB: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPPSLS(unsigned char    * registerData,
                                    const unsigned int registerSize,
                                    nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.ppsls.version = nvmlPPSLS_v1;
    prmBuffer.regId = NVML_GPU_PRM_PPSLS;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_ppsls_ext ppslsReg;

    memset(&ppslsReg, 0, sizeof(ppslsReg));
    reg_access_gpu_ppsls_ext_unpack(&ppslsReg, registerData);
    prmBuffer.ppsls.lpMsb = ppslsReg.lp_msb;
    prmBuffer.ppsls.localPort = ppslsReg.local_port;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PPSLS: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterMTCAP(unsigned char    * registerData,
                                    const unsigned int registerSize,
                                    nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.mtcap.version = nvmlMTCAP_v1;
    prmBuffer.regId = NVML_GPU_PRM_MTCAP;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_mtcap_ext mtcapReg;

    memset(&mtcapReg, 0, sizeof(mtcapReg));
    reg_access_gpu_mtcap_ext_unpack(&mtcapReg, registerData);
    prmBuffer.mtcap.slotIndex = mtcapReg.slot_index;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending MTCAP: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPAOS(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.paos.version = nvmlPAOS_v1;
    prmBuffer.regId = NVML_GPU_PRM_PAOS;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_paos_reg_ext paosReg;

    memset(&paosReg, 0, sizeof(paosReg));
    reg_access_gpu_paos_reg_ext_unpack(&paosReg, registerData);
    prmBuffer.paos.planeInd = paosReg.plane_ind;
    prmBuffer.paos.adminStatus = paosReg.admin_status;
    prmBuffer.paos.lpMsb = paosReg.lp_msb;
    prmBuffer.paos.localPort = paosReg.local_port;
    prmBuffer.paos.swid = paosReg.swid;
    prmBuffer.paos.e = paosReg.e;
    prmBuffer.paos.fd = paosReg.fd;
    prmBuffer.paos.psE = paosReg.ps_e;
    prmBuffer.paos.lsE = paosReg.ls_e;
    prmBuffer.paos.eePs = paosReg.ee_ps;
    prmBuffer.paos.eeLs = paosReg.ee_ls;
    prmBuffer.paos.ee = paosReg.ee;
    prmBuffer.paos.ase = paosReg.ase;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PAOS: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPDDR(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.pddr.version = nvmlPDDR_v1;
    prmBuffer.regId = NVML_GPU_PRM_PDDR;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_pddr_reg_ext pddrReg;

    memset(&pddrReg, 0, sizeof(pddrReg));
    reg_access_gpu_pddr_reg_ext_unpack(&pddrReg, registerData);
    prmBuffer.pddr.portType = pddrReg.port_type;
    prmBuffer.pddr.planeInd = pddrReg.plane_ind;
    prmBuffer.pddr.lpMsb = pddrReg.lp_msb;
    prmBuffer.pddr.pnat = pddrReg.pnat;
    prmBuffer.pddr.localPort = pddrReg.local_port;
    prmBuffer.pddr.pageSelect = pddrReg.page_select;
    prmBuffer.pddr.moduleInfoExt = pddrReg.module_info_ext;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PDDR: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPGUID(unsigned char    * registerData,
                                    const unsigned int registerSize,
                                    nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.pguid.version = nvmlPGUID_v1;
    prmBuffer.regId = NVML_GPU_PRM_PGUID;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_pguid_reg_ext pguidReg;

    memset(&pguidReg, 0, sizeof(pguidReg));
    reg_access_gpu_pguid_reg_ext_unpack(&pguidReg, registerData);
    prmBuffer.pguid.lpMsb = pguidReg.lp_msb;
    prmBuffer.pguid.pnat = pguidReg.pnat;
    prmBuffer.pguid.localPort = pguidReg.local_port;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PGUID: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPMAOS(unsigned char    * registerData,
                                    const unsigned int registerSize,
                                    nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.pmaos.version = nvmlPMAOS_v1;
    prmBuffer.regId = NVML_GPU_PRM_PMAOS;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_pmaos_reg_ext pmaosReg;

    memset(&pmaosReg, 0, sizeof(pmaosReg));
    reg_access_gpu_pmaos_reg_ext_unpack(&pmaosReg, registerData);
    prmBuffer.pmaos.adminStatus = pmaosReg.admin_status;
    prmBuffer.pmaos.module = pmaosReg.module;
    prmBuffer.pmaos.slotIndex = pmaosReg.slot_index;
    prmBuffer.pmaos.rst = pmaosReg.rst;
    prmBuffer.pmaos.e = pmaosReg.e;
    prmBuffer.pmaos.ee = pmaosReg.ee;
    prmBuffer.pmaos.ase = pmaosReg.ase;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PMAOS: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPMLP(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.pmlp.version = nvmlPMLP_v1;
    prmBuffer.regId = NVML_GPU_PRM_PMLP;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_pmlp_reg_ext pmlpReg;

    memset(&pmlpReg, 0, sizeof(pmlpReg));
    reg_access_gpu_pmlp_reg_ext_unpack(&pmlpReg, registerData);
    prmBuffer.pmlp.width = pmlpReg.width;
    prmBuffer.pmlp.planeInd = pmlpReg.plane_ind;
    prmBuffer.pmlp.lpMsb = pmlpReg.lp_msb;
    prmBuffer.pmlp.localPort = pmlpReg.local_port;
    prmBuffer.pmlp.mLaneM = pmlpReg.m_lane_m;
    prmBuffer.pmlp.rxtx = pmlpReg.rxtx;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PMLP: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPPAOS(unsigned char    * registerData,
                                    const unsigned int registerSize,
                                    nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.ppaos.version = nvmlPPAOS_v1;
    prmBuffer.regId = NVML_GPU_PRM_PPAOS;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_ppaos_reg_ext ppaosReg;

    memset(&ppaosReg, 0, sizeof(ppaosReg));
    reg_access_gpu_ppaos_reg_ext_unpack(&ppaosReg, registerData);
    prmBuffer.ppaos.portType = ppaosReg.port_type;
    prmBuffer.ppaos.phyTestModeAdmin = ppaosReg.phy_test_mode_admin;
    prmBuffer.ppaos.lpMsb = ppaosReg.lp_msb;
    prmBuffer.ppaos.localPort = ppaosReg.local_port;
    prmBuffer.ppaos.swid = ppaosReg.swid;
    prmBuffer.ppaos.planeInd = ppaosReg.plane_ind;
    prmBuffer.ppaos.phyStatusAdmin = ppaosReg.phy_status_admin;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PPAOS: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPPCNT(unsigned char    * registerData,
                                    const unsigned int registerSize,
                                    nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.ppcnt.version = nvmlPPCNT_v1;
    prmBuffer.regId = NVML_GPU_PRM_PPCNT;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_ppcnt_reg_ext ppcntReg;

    memset(&ppcntReg, 0, sizeof(ppcntReg));
    reg_access_gpu_ppcnt_reg_ext_unpack(&ppcntReg, registerData);
    prmBuffer.ppcnt.grp = ppcntReg.grp;
    prmBuffer.ppcnt.portType = ppcntReg.port_type;
    prmBuffer.ppcnt.lpMsb = ppcntReg.lp_msb;
    prmBuffer.ppcnt.pnat = ppcntReg.pnat;
    prmBuffer.ppcnt.localPort = ppcntReg.local_port;
    prmBuffer.ppcnt.swid = ppcntReg.swid;
    prmBuffer.ppcnt.prioTc = ppcntReg.prio_tc;
    prmBuffer.ppcnt.grpProfile = ppcntReg.grp_profile;
    prmBuffer.ppcnt.planeInd = ppcntReg.plane_ind;
    prmBuffer.ppcnt.countersCap = ppcntReg.counters_cap;
    prmBuffer.ppcnt.lpGl = ppcntReg.lp_gl;
    prmBuffer.ppcnt.clr = ppcntReg.clr;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PPCNT: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPPHCR(unsigned char    * registerData,
                                    const unsigned int registerSize,
                                    nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.pphcr.version = nvmlPPHCR_v1;
    prmBuffer.regId = NVML_GPU_PRM_PPHCR;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_pphcr_ext pphcrReg;

    memset(&pphcrReg, 0, sizeof(pphcrReg));
    reg_access_gpu_pphcr_ext_unpack(&pphcrReg, registerData);
    prmBuffer.pphcr.planeInd = pphcrReg.plane_ind;
    prmBuffer.pphcr.portType = pphcrReg.port_type;
    prmBuffer.pphcr.lpMsb = pphcrReg.lp_msb;
    prmBuffer.pphcr.pnat = pphcrReg.pnat;
    prmBuffer.pphcr.localPort = pphcrReg.local_port;
    prmBuffer.pphcr.histType = pphcrReg.hist_type;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PPHCR: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterPTYS(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t &  prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.ptys.version = nvmlPTYS_v1;
    prmBuffer.regId = NVML_GPU_PRM_PTYS;

    /* convert the raw data buffer to PRM struct */
    reg_access_gpu_ptys_reg_ext ptysReg;

    memset(&ptysReg, 0, sizeof(ptysReg));
    reg_access_gpu_ptys_reg_ext_unpack(&ptysReg, registerData);
    prmBuffer.ptys.protoMask = ptysReg.proto_mask;
    prmBuffer.ptys.transmitAllowed = ptysReg.transmit_allowed;
    prmBuffer.ptys.planeInd = ptysReg.plane_ind;
    prmBuffer.ptys.portType = ptysReg.port_type;
    prmBuffer.ptys.lpMsb = ptysReg.lp_msb;
    prmBuffer.ptys.localPort = ptysReg.local_port;
    prmBuffer.ptys.txReadyE = ptysReg.tx_ready_e;
    prmBuffer.ptys.eeTxReady = ptysReg.ee_tx_ready;
    prmBuffer.ptys.anDisableAdmin = ptysReg.an_disable_admin;
    prmBuffer.ptys.extEthProtoAdmin = ptysReg.ext_eth_proto_admin;
    prmBuffer.ptys.ethProtoAdmin = ptysReg.eth_proto_admin;
    prmBuffer.ptys.ibProtoAdmin = ptysReg.ib_proto_admin;
    prmBuffer.ptys.ibLinkWidthAdmin = ptysReg.ib_link_width_admin;
    prmBuffer.ptys.xdr2xSlowAdmin = ptysReg.xdr_2x_slow_admin;
    prmBuffer.ptys.forceLtFramesAdmin = ptysReg.force_lt_frames_admin;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending PTYS: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return prmBuffer.status;
}
int NvmlDevice::AccessRegisterSLTP(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t &  prmBuffer)
{
    {
        nvmlReturn_t error = NVML_SUCCESS;

        /* Set PRM Register version & ID. */
        prmBuffer.sltp.version = nvmlSLTP_v1;
        prmBuffer.regId = NVML_GPU_PRM_SLTP;

        /* convert the raw data buffer to PRM struct */
        reg_access_gpu_sltp_reg_ext sltpReg;

        memset(&sltpReg, 0, sizeof(sltpReg));
        reg_access_gpu_sltp_reg_ext_unpack(&sltpReg, registerData);
        prmBuffer.sltp.cDb = sltpReg.c_db;
        prmBuffer.sltp.portType = sltpReg.port_type;
        prmBuffer.sltp.laneSpeed = sltpReg.lane_speed;
        prmBuffer.sltp.lane = sltpReg.lane;
        prmBuffer.sltp.txPolicy = sltpReg.tx_policy;
        prmBuffer.sltp.pnat = sltpReg.pnat;
        prmBuffer.sltp.localPort = sltpReg.local_port;
        prmBuffer.sltp.lpMsb = sltpReg.lp_msb;

        /* Send the PRM to the driver. */
        error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
        if (error) {
            std::cout << "Error sending SLTP: " << _nvmlLibWrapper->nvmlErrorString(error);
        }

        /* Copy back the register data. */
        memcpy(registerData, prmBuffer.data, registerSize);
        return prmBuffer.status;
    }
}

int NvmlDevice::AccessRegisterMORD(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t&   prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.mord.version = nvmlMORD_v1;
    prmBuffer.regId = NVML_GPU_PRM_MORD;

    /* convert the raw data buffer to HCA PRM struct. */
    reg_access_hca_resource_dump_ext mordHcaReg;

    memset(&mordHcaReg, 0, sizeof(mordHcaReg));
    reg_access_hca_resource_dump_ext_unpack(&mordHcaReg, registerData);
    prmBuffer.mord.segmentType = mordHcaReg.segment_type;
    prmBuffer.mord.seqNum = mordHcaReg.seq_num;
    prmBuffer.mord.vhcaIdValid = mordHcaReg.vhca_id_valid;
    prmBuffer.mord.inlineDump = mordHcaReg.inline_dump;
    prmBuffer.mord.vhcaId = mordHcaReg.vhca_id;
    prmBuffer.mord.index1 = mordHcaReg.index1;
    prmBuffer.mord.index2 = mordHcaReg.index2;
    prmBuffer.mord.numOfObj2 = mordHcaReg.num_of_obj2;
    prmBuffer.mord.numOfObj1 = mordHcaReg.num_of_obj1;
    prmBuffer.mord.deviceOpaque = mordHcaReg.device_opaque;
    prmBuffer.mord.mkey = mordHcaReg.mkey;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending MORD: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Convert the IOCTL Data to GPUNet struct. */
    memset(&mordHcaReg, 0, sizeof(mordHcaReg));
    reg_access_gpu_resource_dump_ext mordGpuReg;

    memset(&mordGpuReg, 0, sizeof(mordGpuReg));
    reg_access_gpu_resource_dump_ext_unpack(&mordGpuReg, prmBuffer.data);

    /* Convert the GPUNet struct to original HCA struct. */
    mordHcaReg.segment_type = mordGpuReg.segment_type;
    mordHcaReg.seq_num = mordGpuReg.seq_num;
    mordHcaReg.inline_dump = mordGpuReg.inline_dump;
    mordHcaReg.more_dump = mordGpuReg.more_dump;
    mordHcaReg.index1 = mordGpuReg.index1;
    mordHcaReg.index2 = mordGpuReg.index2;
    mordHcaReg.num_of_obj2 = mordGpuReg.num_of_obj2;
    mordHcaReg.num_of_obj1 = mordGpuReg.num_of_obj1;
    mordHcaReg.device_opaque = mordGpuReg.device_opaque;
    mordHcaReg.size = mordGpuReg.size;
    mordHcaReg.vhca_id_valid = mordGpuReg.vhca_id_valid;
    mordHcaReg.vhca_id = mordGpuReg.vhca_id;
    memcpy(mordHcaReg.inline_data, mordGpuReg.inline_data, sizeof(mordGpuReg.inline_data));

    reg_access_hca_resource_dump_ext_pack(&mordHcaReg, registerData);
    return error;
}


int NvmlDevice::AccessRegisterMCAM(unsigned char    * registerData,
                                   const unsigned int registerSize,
                                   nvmlPRMBuffer_t&   prmBuffer)
{
    nvmlReturn_t error = NVML_SUCCESS;

    /* Set PRM Register version & ID. */
    prmBuffer.mcam.version = nvmlMCAM_v1;
    prmBuffer.regId = NVML_GPU_PRM_MCAM;

    /* convert the raw data buffer to PRM struct. */
    reg_access_gpu_mcam_reg_ext mcamReg;

    memset(&mcamReg, 0, sizeof(mcamReg));
    reg_access_gpu_mcam_reg_ext_unpack(&mcamReg, registerData);
    prmBuffer.mcam.accessRegGroup = mcamReg.access_reg_group;
    prmBuffer.mcam.featureGroup = mcamReg.feature_group;

    /* Send the PRM to the driver. */
    error = _nvmlLibWrapper->nvmlDeviceReadWritePRM(_nvmlDevice, &prmBuffer);
    if (error) {
        std::cout << "Error sending MCAM: " << _nvmlLibWrapper->nvmlErrorString(error);
    }

    /* Copy back the register data. */
    memcpy(registerData, prmBuffer.data, registerSize);
    return error;
}
