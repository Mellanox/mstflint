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

#include "FS5Image.h"

const string FS5Image::PATH_TO_NCORE_BCH = "fw_image.begin_area.boot2_bch.";
const string FS5Image::PATH_TO_HW_POINTERS = "fw_image.begin_area.hw_pointers.";

bool FS5Image::compileBinaryBoot(AdbInstance* adbNode, int& offset)
{
    offset = adbNode->offset / 8;

    // Reading boot2
    string sectName = adbNode->getInstanceAttr("sectName");
    MSection* mSection = _mfile[sectName.c_str()];

    // Writing boot2
    copyVector(mSection->data, _imageData, offset);
    offset += mSection->data.size();

    // Setting boot2 size in NCORE BCH
    string fieldName = PATH_TO_NCORE_BCH + "size";
    AdbInstance* adabeField = adabe->getChildByPath(fieldName);
    if (adabeField == NULL)
    {
        return errmsg("%s field is missing", fieldName.c_str());
    }
    write4B(adabeField->offset / 8, mSection->data.size());

    // Calculating hashes_table relative offset
    fieldName = PATH_TO_HW_POINTERS + "boot2_ptr.ptr";
    adabeField = adabe->getChildByPath(fieldName);
    if (adabeField == NULL)
    {
        return errmsg("%s field is missing", fieldName.c_str());
    }
    u_int32_t boot2Addr = strtoul(adabeField->getInstanceAttr("default").c_str(), NULL, 0);
    u_int32_t HashesTableAddr = GetHashesTableAddr();
    u_int32_t HashesTableRelativeAddr = HashesTableAddr - boot2Addr;

    // Setting hashes_table relative offset in NCORE BCH
    fieldName = PATH_TO_NCORE_BCH + "hashes_table_relative_offset";
    adabeField = adabe->getChildByPath(fieldName);
    if (adabeField == NULL)
    {
        return errmsg("%s field is missing", fieldName.c_str());
    }
    write4B(adabeField->offset / 8, HashesTableRelativeAddr);

    return true;
}
