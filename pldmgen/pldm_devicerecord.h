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
 