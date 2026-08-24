/*
 * SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: LicenseRef-NvidiaProprietary
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

 #ifndef PLDM_TIME_H_
 #define PLDM_TIME_H_
 
 #include <string>
 #include <vector>
 
 #include "common/compatibility.h"
 
 void dumpTimeStamp104(std::vector<u_int8_t>& buff, const std::string& releaseDateTime);
 long getUTCOffsetInSecond(time_t t);
 
 #endif /* PLDM_TIME_H_ */