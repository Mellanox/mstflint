/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 