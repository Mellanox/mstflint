/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
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
