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

 #include "common/tools_version.h"
 #include "pldm.h"
 #include "pldm_component.h"
 #include "pldm_utils/pldm_utils.h"
 #include "pldm_arg_parser.h"
 #include <cstdio>
 #include <iostream>
 #include <algorithm>
 
 using std::vector;
 using std::string;
 
 // ********************************************************
 // functions for new Tool
 // ********************************************************
 void genEmptyBook(std::unique_ptr<CmdLineParams>& params)
 {
     if (!params->_cookbookDefinition.empty())
     {
         PLDM::GenerateEmptyCookBookFromJson(params->_cookbookDefinition, params->_reuseComponents, params->_output_file,
                                             params->_keepDescriptorsOrder);
     }
     else
     {
         throw PLDMException("gen_empty_cookbook - cookbook definition file is not provided.\n");
     }
     printf("-I- Empty cookbook File %s generated successfully.\n", params->_output_file.c_str());
 }
 
 void genPldmPackage(std::unique_ptr<CmdLineParams>& params)
 {
     string cookbookContent;
     readFromFile(params->_input_file, cookbookContent);
     string cookbookLower = cookbookContent;
     std::transform(cookbookLower.begin(), cookbookLower.end(), cookbookLower.begin(), ::tolower);
     bool recovery = cookbookLower.find("recovery") != string::npos;
 
     PLDM pldm(cookbookContent, recovery);
     vector<u_int8_t> buff;
     pldm.Pack(buff);
     if (!WriteToFile(params->_output_file, buff))
     {
         fprintf(stderr, "-E- Cannot write to the file %s\n", params->_output_file.c_str());
         exit(1);
     }
     printf("-I- PLDM fwpkg File %s generated successfully.\n", params->_output_file.c_str());
 }

void disableCustomPsid(std::unique_ptr<CmdLineParams>& params)
{
    PLDM::DisableCustomPsid(params->_input_file, params->_output_file, params->_psid, params->_minorVersion);
    printf("-I- Wrote %s: PSID minor digit (and APSKU byte if present) set to %s.\n", params->_output_file.c_str(),
           params->_minorVersion.c_str());
}
 
 int Main(int argc, char* argv[])
 {
     try
     {
         PldmgenCmdLineParser pldmgenCmdParser;
         ParseStatus rc = pldmgenCmdParser.Parse(argv, argc);
         if (rc == PARSE_ERROR)
         {
             return rc;
         }
         if (rc == PARSE_OK_WITH_EXIT)
         {
             return 0;
         }
         pldmgenCmdParser._parsedParams->validateInputParams();
         if (pldmgenCmdParser._parsedParams->_cmd == GEN_EMPTY_COOKBOOK)
         {
             genEmptyBook(pldmgenCmdParser._parsedParams);
         }
         else if (pldmgenCmdParser._parsedParams->_cmd == GEN_PLDM_PACKAGE)
         {
             genPldmPackage(pldmgenCmdParser._parsedParams);
         }
         else if (pldmgenCmdParser._parsedParams->_cmd == DISABLE_CUSTOM_PSID)
         {
             disableCustomPsid(pldmgenCmdParser._parsedParams);
         }
         else
         {
            throw PLDMException("Invalid command. mstpldm_pkg_gen --help for more information.\n");
         }
     }
     catch (PLDMException& e)
     {
         printf("Failed!\n");
         fprintf(stderr, "%s\n", e._err.c_str());
         exit(1);
     }
     return 0;
 }
 
 int main(int argc, char* argv[])
 {
     if (argc < 2) // at least one argument is required
     {
         fprintf(stderr, "No arguments provided.\n");
         return 1;
     }
     return Main(argc, argv);
 }
 