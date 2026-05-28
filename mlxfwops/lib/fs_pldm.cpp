/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *
 *  Version: $Id$
 *
 */

#include "fs_pldm.h"
#include "pldmlib/pldm_dev_id_record.h"
#include "pldmlib/pldm_component_image.h"
#ifdef MFT_LEGACY_BUILD
#include <mft_utils.h>
#else
#include "mft_utils/mft_utils.h"
#endif
#include <string>

// bool FsPldmOperations::FwInit()
// {
//     if (_ioAccess->get_size() < sizeof(_header))
//     {
//         return errmsg("Unknown image format");
//     }
//     if (!_ioAccess->read(0, (u_int32_t*)&_header, sizeof(_header)))
//     {
//         return errmsg("Failed to read Image: %s", _ioAccess->err());
//     }
//     if (_header.headerVersion > 1)
//     {
//         return errmsg("Unknown image format");
//     }
//     return true;
// }

// component are ordered by priority
const vector<string> FsPldmOperations::SupportedComponents = {"FW", "NIC_FW", "FW_SPC6", "VMOD"};

bool FsPldmOperations::FwInit()
{
    FwInitCom();
    // memset(&_fs2ImgInfo, 0, sizeof(_fs2ImgInfo)); init is done as part of the struct constructor
    _fwImgInfo.fwType = FIT_PLDM;
    return true;
}

bool FsPldmOperations::LoadPldmPackage()
{
    FPldm* pldmAccess = static_cast<FPldm*>(_ioAccess);
    if (!pldmAccess)
    {
        return errmsg("File is not a valid PLDM package");
    }

    PldmBuffer buff;
    if (!pldmAccess->is_file())
    {
        buff.loadBuffer((u_int8_t*)(pldmAccess->getBuf()), pldmAccess->getBufLength());
    }
    else
    {
        _pldmFile = std::string(pldmAccess->get_fname());
        if (!buff.loadFile(_pldmFile))
        {
            return false;
        }
    }

    if (!_pkg.unpack(buff))
    {
        return false;
    }
    return true;
}

bool FsPldmOperations::GetImageSize(u_int32_t* image_size)
{
    *image_size = _ioAccess->get_size();
    return true;
}

bool FsPldmOperations::FwReadData(void* image, u_int32_t*, bool)
{
    if (image != NULL)
    {
        u_int32_t size = 0;
        GetImageSize(&size);
        if (!_ioAccess->read(0, (u_int32_t*)image, size))
        {
            return errmsg("Failed to read Image: %s", _ioAccess->err());
        }
    }
    return true;
}

bool FsPldmOperations::GetPldmComponentDataByPsid(string component, string psid, u_int8_t** buff, u_int32_t& buffSize)
{
    DPRINTF(("FsPldmOperations::GetPldmComponentDataByPsid\n"));
    std::string strPsid(psid);
    ComponentIdentifier compIdentifier;
    try
    {
        StringToComponentIdentifier(component, compIdentifier);
    }
    catch (PLDMException& e)
    {
        return errmsg("%s", e._err.c_str());
    }
    bool rc = _pkg.getComponentDataByPsid(compIdentifier, strPsid, buff, buffSize);
    return rc;
}

bool FsPldmOperations::GetPldmDescriptor(string psid, u_int16_t type, u_int16_t& descriptor)
{
    return _pkg.getPldmDescriptorByPsid(psid, type, descriptor);
}

// return the first component data found in the PLDM package
bool FsPldmOperations::GetComponentData(const string& pldmFile,
                                        const vector<ComponentIdentifier>& components,
                                        vector<u_int32_t>& buff)
{
    PldmBuffer pldmBuffer;
    if (!pldmBuffer.loadFile(pldmFile))
    {
        return false;
    }

    PldmPkg pldmPkg;
    if (!pldmPkg.unpack(pldmBuffer))
    {
        return false;
    }
    for (auto component : components)
    {
        u_int8_t* data = nullptr;
        u_int32_t dataSize = 0;
        if (pldmPkg.getComponentDataByPsid(component, "", &data, dataSize))
        {
            if (dataSize % 4 != 0)
            {
                delete[] data;
                return false;
            }
            buff.resize(dataSize / 4);
            memcpy(buff.data(), data, dataSize);
            delete[] data;
            return true;
        }
    }
    return false;
}

string FsPldmOperations::GetPldmVendorDefinedDescriptor(string psid, PldmRecordDescriptor::VendorDefinedType type)
{
    DPRINTF(("FsPldmOperations::GetPldmVendorDefinedDescriptor\n"));
    return _pkg.getPldmVendorDefinedDescriptorByPsid(psid, type);
}

bool FsPldmOperations::CreateFwOpsImage(u_int32_t* buff,
                                        u_int32_t buffSize,
                                        FwOperations** newImageOps,
                                        u_int16_t swDevId,
                                        bool isStripedImage)
{
    DPRINTF(("FsPldmOperations::CreateFwOpsImage\n"));
    if (!CreateBasicImageFromData(buff, buffSize, newImageOps, swDevId, isStripedImage))
    {
        return false;
    }
    return true;
}

FwComponent::comps_ids_t FsPldmOperations::ToCompId(string componentName)
{
    if (componentName == "BFB")
    {
        return FwComponent::comps_ids_t::COMPID_BFB;
    }
    return FwComponent::comps_ids_t::COMPID_UNKNOWN;
}

bool FsPldmOperations::FwOperationsCreate(const char* requestedPsid,
                                        const string& componentType,
                                        FwOperations** newImageOps,
                                        mfile* deviceMfile)
{
    DPRINTF(("FsPldmOperations::FwOperationsCreate\n"));
    u_int8_t* buff;
    u_int32_t buffSize = 0;
    // TODO:: look for the image with relvant psid , if not found try to extract full image and query it.
    std::string recovery = GetPldmVendorDefinedDescriptor("", PldmRecordDescriptor::VendorDefinedType::RECOVERY);
    // if recovery set there is no PSID descriptor - use the first image in PLDM fwpkg
    std::string psid = requestedPsid == nullptr || !recovery.empty() ? "" : requestedPsid;

    if (!GetPldmComponentDataByPsid(componentType, psid, &buff, buffSize))
    {
        return errmsg("Failed to get PLDM component data: %s\n", err());
    }

    u_int16_t swDevId = 0;
    // recovery is special case, the magic-pattern present in the image and the DEVICE ID not needed
    // VMOD is a special case, part of image and the DEVICE ID is not needed
    if (recovery.empty() && componentType != "VMOD")
    {
        // use PSID or if empty take the first image in PLDM fwpkg
        if (!psid.empty() || deviceMfile == nullptr)
        {
            DPRINTF(("FsPldmOperations::FwOperationsCreate: use psid to get swDevId\n"));
            if (!GetPldmDescriptor(psid, DEV_ID_TYPE, swDevId))
            {
                delete[] buff;
                return errmsg("DEVICE ID descriptor is not found in the PLDM fwpkg for PSID: %s.\n", psid.c_str());
            }
        }
        // use device mfile to detect SW DEVICE ID
        else
        {
            DPRINTF(("FsPldmOperations::FwOperationsCreate: use device mfile to get swDevId\n"));
            dm_dev_id_t devid_t = DeviceUnknown;
            u_int32_t devid = 0, revid = 0;
            int rc = dm_get_device_id(deviceMfile, &devid_t, &devid, &revid);
            if (rc != 0)
            {
                delete[] buff;
                return errmsg("Can not detect the device type from device.\n");
            }

            swDevId = dm_dev_type2sw_id(devid_t);
        }
    }

    if (!CreateFwOpsImage((u_int32_t*)buff, buffSize, newImageOps, swDevId, true))
    {
        delete[] buff;
        return errmsg("Failed to use image from PLDM fwpkg. %s\n", err());
    }

    delete[] buff;
    return true;
}

void FsPldmOperations::PrintInfo()
{
    printf("%-26s%s\n", "Image type:", "PLDM");

    u_int8_t deviceRecordCount = _pkg.getDeviceIDRecordCount();
    for (u_int8_t devIdx = 0; devIdx < deviceRecordCount; devIdx++)
    {
        PldmDevIdRecord* devIdRec = _pkg.getDeviceIDRecord(devIdx);
        PrintDeviceRecord(devIdRec, devIdx);
    }
}

void FsPldmOperations::PrintDeviceRecord(PldmDevIdRecord* devIdRec, int index)
{
    printf("\n");
    char deviceRecordLabel[32];
    sprintf(deviceRecordLabel, "Device Record[%d]:", index);
    printf("%-26s%s\n", deviceRecordLabel, devIdRec->getComponentImageSetVersionString().c_str());

    for (auto recordDescriptor : devIdRec->getRecordDescriptors())
    {
        recordDescriptor->printFormatted();
    }

    PrintComponents(devIdRec);
}

void FsPldmOperations::PrintComponents(PldmDevIdRecord* devIdRec)
{
    std::vector<PldmComponenetImage*> applicableComponents;
    u_int16_t comps_count = _pkg.getComponentImageCount();
    std::vector<u_int8_t> appliedComponents = devIdRec->getComponentsIndexes();

    // filter related component to the corresponding device record (0 - not related)
    for (u_int16_t i = 0; i < comps_count; i++)
    {
        if (appliedComponents[i] != 0)
        {
            applicableComponents.push_back(_pkg.getComponentByIndex(i));
        }
    }

    std::string componentNames;
    for (auto comp : applicableComponents)
    {
        ComponentIdentifier identifier = static_cast<ComponentIdentifier>(comp->getComponentIdentifier());
        std::string componentName;
        ComponentIdentifierToStringValue(identifier, ComponentField::Name, componentName);
        if (!componentNames.empty())
        {
            componentNames += ", ";
        }
        componentNames += componentName;
    }
    printf("%-26s%s\n", "Components:", componentNames.c_str());

    // Print versions
    for (auto comp : applicableComponents)
    {
        comp->printFormatted();
    }
}

bool FsPldmOperations::IsComponentInPackage(const string& psid, const string& componentName)
{
    if (componentName.empty())
    {
        return errmsg("Component name is empty");
    }

    if (std::find(SupportedComponents.begin(), SupportedComponents.end(), componentName) == SupportedComponents.end())
    {
        return errmsg("Component %s is not supported.", componentName.c_str());
    }

    if (!_pkg.isComponentInPackage(psid, componentName))
    {
        return errmsg("Component %s is not found in the PLDM package.", componentName.c_str());
    }
    return true;
}

string FsPldmOperations::GetFirstSupportedComponent(const string& psid)
{
    for (const string& component : SupportedComponents)
    {
        if (_pkg.isComponentInPackage(psid, component))
        {
            return component;
        }
    }
    return "";
}

bool FsPldmOperations::FwQuery(fw_info_t* fwInfo, bool, bool, bool, bool, bool)
{
    return true;
}

bool FsPldmOperations::FwVerify(VerifyCallBack verifyCallBackFunc, bool isStripedImage, bool showItoc, bool ignoreDToc)
{
    return Unsupported(__FUNCTION__);
}

bool FsPldmOperations::FwReadRom(std::vector<u_int8_t>& romSect)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurnRom(FImage* romImg,
                                bool ignoreProdIdCheck,
                                bool ignoreDevidCheck,
                                ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwDeleteRom(bool ignoreProdIdCheck, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurn(FwOperations* imageOps, u_int8_t forceVersion, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurnAdvanced(FwOperations* imageOps, ExtBurnParams& burnParams)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwBurnBlock(FwOperations* imageOps, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetGuids(sg_params_t& sgParam, PrintCallBack callBackFunc, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetMFG(fs3_uid_t baseGuid, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetMFG(guid_t baseGuid, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetVSD(char* vsdStr, ProgressCallBack progressFunc, PrintCallBack printFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetVPD(char* vpdFileStr, PrintCallBack callBackFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwSetAccessKey(hw_key_t userKey, ProgressCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwGetSection(u_int32_t sectType, std::vector<u_int8_t>& sectInfo, bool stripedImage)
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwResetNvData()
{
    return Unsupported(__FUNCTION__);
}
bool FsPldmOperations::FwShiftDevData(PrintCallBack progressFunc)
{
    return Unsupported(__FUNCTION__);
}
const char* FsPldmOperations::FwGetResetRecommandationStr()
{
    Unsupported(__FUNCTION__);
    return "";
}
bool FsPldmOperations::FwCalcMD5(u_int8_t md5sum[16])
{
    return Unsupported(__FUNCTION__);
}
