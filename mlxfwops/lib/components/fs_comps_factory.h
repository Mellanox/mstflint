/*
* Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
*/

#ifndef FS_COMPS_FACTORY
#define FS_COMPS_FACTORY

#include "fs_comps_ops.h"
#include "fs_synce_ops.h"
#include "fs_cert_ops.h"
#if ENABLE_DPA
#include "fs_dpa_app_ops.h"
#endif

class FsCompsFactory
{
public:
    static bool IsFsCompsFingerPrint(u_int8_t fingerPrint[])
    {
        if (IsSyncEOpsFingerPrint(fingerPrint) || IsCertOpsFingerPrint(fingerPrint)
        #if ENABLE_DPA
                || IsDpaAppFingerPrint(fingerPrint)
        #endif
               )        
        {
            return true;
        }

        return false;
    }

    static FsCompsOperations* Create(FBase* ioAccess)
    {
        u_int8_t fingerPrint[_FP_LENGTH] = {0};

        FImage* imageAccess = dynamic_cast<FImage*>(ioAccess);
        if (imageAccess == nullptr)
        {
            throw FsCompsException("Unknown image format");
        }

        ioAccess->read(0, fingerPrint, _FP_LENGTH, false, NULL);
        if (IsSyncEOpsFingerPrint(fingerPrint))
        {
            return new FsSyncEOperations(imageAccess);
        }
        else if (IsCertOpsFingerPrint(fingerPrint))
        {
            return new FsCertOperations(imageAccess);
        }
        #if ENABLE_DPA
        else if (IsDpaAppFingerPrint(fingerPrint))
        {
            return new FsDpaAppOperations(imageAccess);
        }
        #endif

        throw FsCompsException("Couldn't identify component in given io access");
    }

private:
    static const u_int32_t _FP_LENGTH = 16;

    static bool IsSyncEOpsFingerPrint(const u_int8_t fingerPrint[])
    {
        static const u_int32_t SYNCE_FP_LENGTH = 2;
        const u_int8_t expectedfingerPrint[SYNCE_FP_LENGTH + 1] = {0x55, 0xAA, 0x0};

        return strncmp((const char*)fingerPrint, (const char*)expectedfingerPrint, SYNCE_FP_LENGTH) == 0;
    }

    static bool IsCertOpsFingerPrint(const u_int8_t fingerPrint[])
    {
        static const u_int32_t CERT_FP_LENGTH = 16;
        const u_int8_t expectedfingerPrint[CERT_FP_LENGTH + 1] = "CERTIFICATE.BIN!";

        return strncmp((const char*)fingerPrint, (const char*)expectedfingerPrint, CERT_FP_LENGTH) == 0;
    }
    
    #if ENABLE_DPA
    static bool IsDpaAppFingerPrint(const u_int8_t fingerPrint[])
    {
        static const u_int32_t DPA_APP_FP_LENGTH = 16;
        const u_int8_t expectedfingerPrint[DPA_APP_FP_LENGTH + 1] = "NV_DPA_APP.BIN!!";

        return strncmp((const char*)fingerPrint, (const char*)expectedfingerPrint, DPA_APP_FP_LENGTH) == 0;
    }
    #endif
};

#endif /* FS_COMPS_FACTORY */