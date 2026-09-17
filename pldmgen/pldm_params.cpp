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
     _keepDescriptorsOrder(false),
     _psid(""),
     _minorVersion("00")
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
     else if (_cmd == DISABLE_CUSTOM_PSID)
     {
         if (_input_file.empty())
         {
             throw PLDMException("Invalid arguments for disable_custom_psid. --input_file must be specified.");
         }
         else if (_output_file.empty())
         {
             throw PLDMException("Invalid arguments for disable_custom_psid. --output_file must be specified.");
         }
         else if (!_cookbookDefinition.empty())
         {
             throw PLDMException(
               "Invalid arguments for disable_custom_psid. --cookbook_definition is not supported for disable_custom_psid.");
         }
         else if (!ValidSizeAndFormat(_minorVersion, 1))
         {
             throw PLDMException("Invalid --minor_version '%s'; expected a hex byte (e.g. 1A or 0x1A).",
                                 _minorVersion.c_str());
         }
     }
 }
 