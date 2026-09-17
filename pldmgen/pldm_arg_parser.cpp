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

 #include "pldm_arg_parser.h"
 #include <cstdio>
 #include <iostream>
 #include <string>
 #include <memory>
 #include <cstring>
 #include "common/tools_version.h"
 
 using namespace std;
 #define IDENT "\t"
 #define PLDM_PKG_GEN_NAME "mstpldm_pkg_gen"
 
 /************************************
  * Function: PldmgenCmdLineParser Constructor
  ************************************/
 PldmgenCmdLineParser::PldmgenCmdLineParser() :
     CommandLineRequester(PLDM_PKG_GEN_NAME), _cmdParser(PLDM_PKG_GEN_NAME)
 {
     initOptions();
     _cmdParser.AddRequester(this);
     _parsedParams = unique_ptr<CmdLineParams>(new CmdLineParams());
 }
 
 bool PldmgenCmdLineParser::isFlag(const string& arg)
 {
     return arg.length() > 0 && arg[0] == '-';
 }
 
 /************************************
  * Function: Parse
  ************************************/
 ParseStatus PldmgenCmdLineParser::Parse(char** argv, int argc)
 {
     // If last argument is a command, exclude it from option parsing
     string lastArg = argv[argc - 1];
     bool lastArgIsFlag = isFlag(lastArg);
     int argCount = lastArgIsFlag ? argc : argc - 1;
     ParseStatus rc;
     // Only parse command if last argument is not a flag
     if (!lastArgIsFlag)
     {
         rc = ParseCommand(lastArg);
         if (rc != PARSE_OK)
         {
             cout << _cmdParser.GetUsage();
             throw PLDMException("-E- Command input parameter");
         }
     }
 
     vector<char*> modifiedArgv(argv, argv + argCount);
     int modifiedArgc = static_cast<int>(modifiedArgv.size());
     rc = _cmdParser.ParseOptions(modifiedArgc, modifiedArgv.data());
     if (rc == PARSE_OK_WITH_EXIT)
     {
         return PARSE_OK_WITH_EXIT;
     }
     else if (rc != PARSE_OK)
     {
         cout << _cmdParser.GetUsage();
         throw PLDMException("-E- Bad input parameter");
     }
     return rc;
 }
 
 /************************************
  * Function: ParseCommand
  ************************************/
 ParseStatus PldmgenCmdLineParser::ParseCommand(string& command)
 {
     if (command == "gen_empty_cookbook")
     {
         _parsedParams->_cmd = GEN_EMPTY_COOKBOOK;
     }
     else if (command == "gen_pldm_package")
     {
         _parsedParams->_cmd = GEN_PLDM_PACKAGE;
     }
     else if (command == "disable_custom_psid")
     {
         _parsedParams->_cmd = DISABLE_CUSTOM_PSID;
     }
     else
     {
         cout << "Unknown command: " << command << endl;
         return PARSE_ERROR;
     }
     return PARSE_OK;
 }
 
 /************************************
  * Function: HandleOption
  ************************************/
 ParseStatus PldmgenCmdLineParser::HandleOption(string name, string value)
 {
     if (name == "cookbook_definition" || name == "cd")
     {
         _parsedParams->_cookbookDefinition = value;
     }
     else if (name == "output_file" || name == "o")
     {
         _parsedParams->_output_file = value;
     }
     else if (name == "input_file" || name == "i")
     {
         _parsedParams->_input_file = value;
     }
     else if (name == "reuse_components" || name == "rc")
     {
         _parsedParams->_reuseComponents = true;
     }
     else if (name == "keep_descriptors_order" || name == "kdo")
     {
         _parsedParams->_keepDescriptorsOrder = true;
     }
     else if (name == "psid")
     {
         _parsedParams->_psid = value;
     }
     else if (name == "minor_version")
     {
         _parsedParams->_minorVersion = value;
     }
     else if (name == "help" || name == "h")
     {
         printUsage();
         return PARSE_OK_WITH_EXIT;
     }
     else if (name == "version" || name == "v")
     {
         print_version_string(PLDM_PKG_GEN_NAME, "");
         return PARSE_OK_WITH_EXIT;
     }
     else
     {
         cout << "Unknown Flag: " << name;
         return PARSE_ERROR;
     }
 
     return PARSE_OK;
 }
 
 /************************************
  * Function: initOptions
  ************************************/
 void PldmgenCmdLineParser::initOptions()
 {
     AddDescription("PLDM package generation tool");
 
     AddOptions("help", 'h', "", "Print help and exit");
     AddOptions("version", 'v', "", "Print version and exit");
     AddOptions("output_file", 'o', "<file_path>", "Output file path");
     AddOptions("input_file", 'i', "<file_path>", "Input file path");
     AddOptions("cookbook_definition", ' ', "<file_path>", "Cookbook definition file path");
     AddOptions("cd", ' ', "<file_path>", "short for cookbook_definition");
     AddOptions("reuse_components", ' ', "", "Reuse components in the cookbook, default is true");
     AddOptions("rc", ' ', "", "short for reuse_components");
     AddOptions("keep_descriptors_order", ' ', "", "Keep descriptors in the order from cookbook definition");
     AddOptions("kdo", ' ', "", "short for keep_descriptors_order");
     AddOptions("psid", ' ', "<psid>", "PSID of the FD to edit (required only when the package has multiple FDs)");
     AddOptions("minor_version", ' ', "<XX>",
                "Minor byte (2 hex digits, e.g. 1A or 0x1A) to set in the PSID and matching APSKU byte; default 00");
     AddOptionalSectionData("COMMANDS SUMMARY", "gen_empty_cookbook", "Generates an empty cookbook");
     AddOptionalSectionData("COMMANDS SUMMARY", "gen_pldm_package", "Generates a PLDM package");
     AddOptionalSectionData(
       "COMMANDS SUMMARY", "disable_custom_psid",
       "Set the PSID minor digits and matching APSKU byte in an existing PLDM package (default 00)");
 }
 
 /************************************
  * Function: printUsage
  ************************************/
 void PldmgenCmdLineParser::printUsage()
 {
    printf("%s", _cmdParser.GetUsage().c_str());
 
    printf("TEMPLATES\n");
    printf(IDENT
           "mstpldm_pkg_gen --output_file/-o <output> --components/-c 2 --device_records/-d 4 gen_empty_cookbook \n");
    printf(
       IDENT
       "mstpldm_pkg_gen --cookbook_definition/-cd <cookbook_def.json> --output_file/-o <output> gen_empty_cookbook \n");
 
    printf(IDENT "mstpldm_pkg_gen --input_file/-i <input cookbook> --output_file/-o <output_pldm> gen_pldm_package \n");
    printf(IDENT "mstpldm_pkg_gen --input_file/-i <input.fwpkg> --output_file/-o <output.fwpkg> "
        "[--psid <CURRENT_PSID>] [--minor_version <XX>] disable_custom_psid \n");

    printf("\n");
    printf("EXAMPLES\n");
    printf(IDENT "mstpldm_pkg_gen --cd cookbook_def.json -o cookbook.json gen_empty_cookbook\n");
    printf(IDENT "mstpldm_pkg_gen -i cookbook.json -o pldm.fwpkg gen_pldm_package\n");
    printf(IDENT "mstpldm_pkg_gen -i in.fwpkg -o out.fwpkg disable_custom_psid\n");
 }