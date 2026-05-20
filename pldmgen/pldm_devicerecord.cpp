/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

 #include <sstream>

 #include "pldm_devicerecord.h"
 
 using namespace std;
 
 PLDMDeviceRecord::PLDMDeviceRecord(const string& setVersion,
                                    const string& updateOptionFlags,
                                    const vector<u_int8_t>& appliedComponentsBitMap,
                                    const vector<PLDMDescriptor>& descriptors) :
     _setVersion(setVersion), _appliedComponentsBitMap(appliedComponentsBitMap), _descriptors(descriptors)
 {
     _updateOptionFlags = 0x0;
     if (!updateOptionFlags.empty())
     {
         std::istringstream(updateOptionFlags) >> std::hex >> _updateOptionFlags;
     }
 }
 
 void PLDMDeviceRecord::Pack(vector<u_int8_t>& buff)
 {
     u_int32_t recordLengthFieldOffset;
     u_int32_t buffSizeBeforePack = buff.size();
 
     // RecordLength, save the offset in order to set the value later
     recordLengthFieldOffset = buff.size();
     dumpUInt16(buff, 0);
 
     // DescriptorCount
     dumpUInt8(buff, _descriptors.size());
 
     // DeviceUpdateOptionFlags
     u_int16_t updateOptionFlagsValue = DEVICE_UPDATE_OPTION_FLAGS_VALUE;
     if (_updateOptionFlags != 0x0)
     {
         updateOptionFlagsValue = _updateOptionFlags;
     }
     dumpUInt32(buff, updateOptionFlagsValue);
 
     // ComponentImageSetVersionStringType
     dumpUInt8(buff, VERSION_STRING_TYPE_ASCII);
 
     // ComponentImageSetVersionStringLength
     dumpUInt8(buff, _setVersion.length());
 
     // FirmwareDevicePackageDataLength
     dumpUInt16(buff, 0x0);
 
     // ApplicableComponents
     dumpBytesArray(buff, _appliedComponentsBitMap.data(), _appliedComponentsBitMap.size());
 
     // ComponentImageSetVersionString
     dumpString(buff, _setVersion);
 
     // Descriptors
     for (unsigned int i = 0; i < _descriptors.size(); i++)
     {
         _descriptors[i].Pack(buff);
     }
 
     // FirmwareDevicePackageData
     // No need as the length above is zero
 
     // RecordLength
     ((u_int16_t*)(buff.data() + recordLengthFieldOffset))[0] = __cpu_to_le16(buff.size() - buffSizeBeforePack);
 }
 