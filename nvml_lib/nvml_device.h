*Copyright(c) 2019 - 2021 NVIDIA CORPORATION & AFFILIATES.All rights reserved.
*
*This software is available to you under a choice of one of two
* licenses.You may choose to be licensed under the terms of the GNU
* General Public License(GPL) Version 2, available from the file
* COPYING in the main directory of this source tree, or the
* OpenIB.org BSD license below:
*
*Redistribution and use in source and binary forms, with or
*     without modification, are permitted provided that the following
*     conditions are met:
*
*-Redistributions of source code must retain the above
* copyright notice, this list of conditions and the following
*        disclaimer.
*
*-Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
*        disclaimer in the documentation and / or other materials
* provided with the distribution.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*


#pragma once

#include <memory>
#include "nvml_lib_wrapper.h"

class NvmlDevice
{
public:
    NvmlDevice(const unsigned int deviceIndex);
    ~NvmlDevice() = default;
    u_int16_t GetPciID();
    int SendPRMRegister(unsigned char    * registerData,
                        const unsigned int registerSize,
                        const unsigned int registerID,
                        int&               registerStatus,
                        bool               isWrite);
private:
    std::unique_ptr < NvmlLibWrapper > _nvmlLibWrapper;
    nvmlDevice_t _nvmlDevice;

    int TranslateNvStatus(unsigned int uNvStatus);
    int AccessRegisterMGIR(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPLIB(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPPSLS(unsigned char    * registerData,
                            const unsigned int registerSize,
                            nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterMTCAP(unsigned char    * registerData,
                            const unsigned int registerSize,
                            nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPAOS(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPDDR(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPGUID(unsigned char    * registerData,
                            const unsigned int registerSize,
                            nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPMAOS(unsigned char    * registerData,
                            const unsigned int registerSize,
                            nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPMLP(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPPAOS(unsigned char    * registerData,
                            const unsigned int registerSize,
                            nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPPCNT(unsigned char    * registerData,
                            const unsigned int registerSize,
                            nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPPHCR(unsigned char    * registerData,
                            const unsigned int registerSize,
                            nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterPTYS(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterSLTP(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterMCAM(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
    int AccessRegisterMORD(unsigned char    * registerData,
                           const unsigned int registerSize,
                           nvmlPRMBuffer_t &  prmBuffer);
};
