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

 #include "pldm_params.h"
 #include <iostream>
 #include <stdexcept>
 
 CmdLineParams::CmdLineParams() :
     _input_file(""),
     _output_file(""),
     _cmd(MISSING_RUN_MODE),
     _componentCount(0),
     _deviceRecordCount(0),
     _cookbookDefinition(""),
     _reuseComponents(false),
     _keepDescriptorsOrder(false)
 {
 }
 
 void CmdLineParams::validateInputParams()
 {
     if (_cmd == MISSING_RUN_MODE)
     {
        throw PLDMException("Invalid mstpldm_pkg_gen command.");
     }
     if (_cmd == GEN_EMPTY_COOKBOOK)
     {
         if (_output_file.empty())
         {
             throw PLDMException("Invalid arguments for gen_empty_cookbook. Output file must be specified.");
         }
         else if (!_input_file.empty())
         {
             throw PLDMException(
               "Invalid arguments for gen_empty_cookbook. --input_file is not supported for gen_empty_cookbook.");
         }
         else if (_cookbookDefinition.empty())
         {
             throw PLDMException("Invalid arguments for gen_empty_cookbook. --cookbook_definition must be specified.");
         }
     }
     else if (_cmd == GEN_PLDM_PACKAGE)
     {
         if (_input_file.empty())
         {
             throw PLDMException("Invalid arguments for gen_pldm_package. Input file must be specified.");
         }
         else if (!_cookbookDefinition.empty())
         {
             throw PLDMException(
               "Invalid arguments for gen_pldm_package. --cookbook_definition is not supported for gen_pldm_package.");
         }
         else if (_output_file.empty())
         {
             throw PLDMException("Invalid arguments for gen_pldm_package. --output_file must be specified.");
         }
     }
 }