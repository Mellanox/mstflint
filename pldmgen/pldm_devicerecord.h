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

 #ifndef PLDM_DEVICERECORD_H_
 #define PLDM_DEVICERECORD_H_
 
 #include <string>
 #include <vector>
 
 #include "common/compatibility.h"
 #include "pldm_descriptor.h"
 
 #define DEVICE_UPDATE_OPTION_FLAGS_VALUE 0x0
 
 class PLDMDeviceRecord
 {
 public:
     std::string _setVersion;
     std::vector<u_int8_t> _appliedComponentsBitMap;
     std::vector<PLDMDescriptor> _descriptors;
     u_int32_t _updateOptionFlags;
 
     PLDMDeviceRecord(const std::string& setVersion,
                      const std::string& updateOptionFlags,
                      const std::vector<u_int8_t>& appliedComponentsBitMap,
                      const std::vector<PLDMDescriptor>& descriptors);
     void Pack(std::vector<u_int8_t>& buff);
 };
 
 #endif
 