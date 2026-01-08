/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "common/tools_algorithm.h"
#include "NVFWresetParser.h"
#include "ResetPlatformInterface.h"
#include "ResetParameterDefs.h"
#define NVFWRESET_TOOL_NAME "nvfwreset"

namespace Filesystem = mstflint::common::algorithm;

/************************************
 * Function: MlxFwResetCmdLineParser Constructor
 ************************************/
NVFWresetParser::NVFWresetParser() : CommandLineRequester("nvfwreset"), _cmdParser("nvfwreset")
{
    initOptions();
    _cmdParser.AddRequester(this);
    _parsedParams = std::unique_ptr<NVFWresetParams>(new NVFWresetParams());
}

void NVFWresetParser::initOptions()
{
    // Required options
    AddOptions("device", 'd', "<device>", "Device to work with", false, true);

    // Reset configuration options
    AddOptions("level", 'l', "<level>", "Run reset with the specified reset-level");
    AddOptions("type", 't', "<type>", "Run reset with the specified reset-type");
    AddOptions("method", 'p', "<method>",
               "Run reset with the specified request method (relevant only for reset-level 3)");
    AddOptions(
      "sync", ' ', "<sync>",
      "Run reset with the specified reset-sync. Sync 0 flow is not supported by BlueField2 and BlueField3 devices");

    // Execution options
    AddOptions("yes", 'y', "", "answer \"yes\" on prompt");
    AddOptions("skip_driver", 's', "", "Skip driver start/stop stage (driver must be stopped manually)");

    // Tool options
    AddOptions("version", 'v', "", "Print tool version");
    AddOptions("help", 'h', "", "show this help message and exit");

    // Driver ignore options
    AddOptions("ignore_list", ' ', "<drivers>", "Skip provided drivers (comma-separated)");

    // Hidden/Advanced options
    AddOptions("no_mst_restart", ' ', "", "Skip mst restart when performing pci reset");
    AddOptions("log", ' ', "<level>", "Log level (critical, error, warning, info, debug)");
    AddOptions(
      "flow_steps", ' ', "<steps>",
      "Run reset with the specified flow steps (comma-separated):\n" + ResetPlatformInterface::ShowResetFlowSteps(),
      true);
}

ParseStatus NVFWresetParser::Parse(int argc, char* argv[])
{
    // Parse options, allowing unknown options (positional commands)
    ParseStatus status = _cmdParser.ParseOptions(argc, argv, true);

    if (status != PARSE_OK && status != PARSE_OK_WITH_EXIT)
    {
        return status;
    }

    // Get positional commands (arguments without dashes like "r" or "reset")
    std::string unknownOpts = _cmdParser.GetUnknownOptions();
    if (!unknownOpts.empty())
    {
        Filesystem::trim(unknownOpts);
        if (!unknownOpts.empty())
        {
            std::string command = unknownOpts;

            // Handle the command
            ParseStatus cmdStatus = ParseCommand(command);
            if (cmdStatus != PARSE_OK)
            {
                return cmdStatus;
            }
        }
    }

    return status;
}

/************************************
 * Function: ParseCommand
 ************************************/
ParseStatus NVFWresetParser::ParseCommand(std::string command)
{
    if (command == "r" || command == "reset")
    {
        _parsedParams->cmdType = ResetCommandType::RESET;
    }
    else
    {
        std::cout << "Unknown command: " << command << std::endl;
        return PARSE_ERROR;
    }
    return PARSE_OK;
}

/************************************
 * Function: HandleOption
 ************************************/
ParseStatus NVFWresetParser::HandleOption(std::string name, std::string value)
{
    if (name == "help" || name == "h")
    {
        std::cout << _cmdParser.GetUsage() << std::endl;
        std::cout << "COMMANDS: " << std::endl;
        std::cout << "  reset | r : Execute reset" << std::endl;
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == "version" || name == "v")
    {
        print_version_string(NVFWRESET_TOOL_NAME, "");
        return PARSE_OK_WITH_EXIT;
    }
    // Required options
    else if (name == "device" || name == "d")
    {
        _parsedParams->device = value;
    }
    // Reset configuration options
    else if (name == "level" || name == "l")
    {
        try
        {
            _parsedParams->resetLevel = static_cast<ResetLevel>(std::stoi(value));
        }
        catch (const std::exception& e)
        {
            std::cout << "Invalid value for --level: " << value << std::endl;
            return PARSE_ERROR;
        }
    }
    else if (name == "type" || name == "t")
    {
        try
        {
            _parsedParams->resetType = static_cast<ResetType>(std::stoi(value));
        }
        catch (const std::exception& e)
        {
            std::cout << "Invalid value for --type: " << value << std::endl;
            return PARSE_ERROR;
        }
    }
    else if (name == "method" || name == "p")
    {
        try
        {
            _parsedParams->method = static_cast<ResetMethod>(std::stoi(value));
        }
        catch (const std::exception& e)
        {
            std::cout << "Invalid value for --method: " << value << std::endl;
            return PARSE_ERROR;
        }
    }
    else if (name == "sync")
    {
        try
        {
            _parsedParams->resetSync = static_cast<ResetSync>(std::stoi(value));
        }
        catch (const std::exception& e)
        {
            std::cout << "Invalid value for --sync: " << value << std::endl;
            return PARSE_ERROR;
        }
    }
    // Execution options
    else if (name == "yes" || name == "y")
    {
        _parsedParams->answerYes = true;
    }
    else if (name == "skip_driver" || name == "s")
    {
        _parsedParams->skipDriver = true;
    }
    // Driver ignore options
    else if (name == "ignore_list")
    {
        // Parse comma-separated list
        std::stringstream ss(value);
        std::string item;
        while (std::getline(ss, item, ','))
        {
            if (!item.empty())
            {
                Filesystem::trim(item);
                _parsedParams->driverIgnoreList.push_back(item);
            }
        }
    }
    else if (name == "flow_steps")
    {
        // Parse comma-separated list
        std::stringstream ss(value);
        std::string item;
        while (std::getline(ss, item, ','))
        {
            Filesystem::trim(item);
            _parsedParams->resetFlowSteps.push_back(static_cast<unsigned int>(std::stoi(item)));
        }
    }
    else if (name == "log")
    {
        _parsedParams->logLevel = value;
    }
    else
    {
        std::cout << "Unknown Flag: " << name << std::endl;
        return PARSE_ERROR;
    }

    return PARSE_OK;
}
