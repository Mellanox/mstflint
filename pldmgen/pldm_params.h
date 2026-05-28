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

 #pragma once
 #include <string>
 #include "pldm_utils/pldm_utils.h"
 
 using namespace std;
 
 enum PldmgenCmd
 {
     MISSING_RUN_MODE,
     GEN_EMPTY_COOKBOOK,
     GEN_PLDM_PACKAGE,
     DISABLE_CUSTOM_PSID,
 };
 
 class CmdLineParams
 {
 public:
     string _input_file;
     string _output_file;
     PldmgenCmd _cmd;
     int _componentCount;
     int _deviceRecordCount;
     string _cookbookDefinition;
     bool _reuseComponents;
     bool _keepDescriptorsOrder;
     string _psid;
     
     CmdLineParams();
     virtual ~CmdLineParams() = default;
     void validateInputParams();
 };