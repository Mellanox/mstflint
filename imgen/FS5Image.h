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

#ifndef FS5_IMAGE_H
#define FS5_IMAGE_H

#include "FS4Image.h"

class FS5Image : public FS4Image
{
public:
    FS5Image(MultiFile& mfile, map<string, string> cli_params, u_int32_t alignValue) :
        FS4Image(mfile, cli_params, alignValue){};
    ~FS5Image(){};

protected:
    static const string PATH_TO_NCORE_BCH;
    static const string PATH_TO_HW_POINTERS;
    bool compileBinaryBoot(AdbInstance* adbNode, int& offset) override;

    // private:
};

#endif
