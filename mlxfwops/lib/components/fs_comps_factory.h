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

class FsCompsFactory
{
public:
    static bool IsFsCompsFingerPrint(u_int8_t fingerPrint[16])
    {
        u_int16_t tmp = *(u_int16_t*)fingerPrint;

        if (tmp == FsCompsOperations::CompsFingerPrint::SyncE)
        {
            return true;
        }

        return false;
    }

    static FsCompsOperations* Create(FBase* ioAccess)
    {
        u_int8_t data[16] = {0};
        ioAccess->read(0, data, 16, false, NULL);

        u_int16_t* fingerPrint = (u_int16_t*)data;

        if (*fingerPrint == FsCompsOperations::CompsFingerPrint::SyncE)
        {
            FImage* imageAccess = dynamic_cast<FImage*>(ioAccess);
            if (imageAccess == nullptr)
            {
                throw FsCompsException("SyncE supported only for images");
            }
            return new FsSyncEOperations(imageAccess);
        }

        throw FsCompsException("Couldn't identify component in given io access");
    }
};

#endif /* FS_COMPS_FACTORY */
