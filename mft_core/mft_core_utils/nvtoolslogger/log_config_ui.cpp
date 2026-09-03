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
 */

#include "nvtoolslogger/log_config_ui.h"

#include <iostream>
#include <cstring>

#include "common/tools_version.h"

#define SET_LEVEL_FLAG "set-level"
#define SET_LEVEL_FLAG_SHORT 'l'

#define SET_MODULE_FLAG "set-module"
#define SET_MODULE_FLAG_SHORT 'm'

#define CLEAR_MODULE_FLAG "clear-module"
#define CLEAR_MODULE_FLAG_SHORT 'M'

#define ENABLE_OUTPUT_FLAG "enable-output"
#define ENABLE_OUTPUT_FLAG_SHORT 'o'

#define DISABLE_OUTPUT_FLAG "disable-output"
#define DISABLE_OUTPUT_FLAG_SHORT 'O'

#define SHOW_FLAG "show"
#define SHOW_FLAG_SHORT 's'

#define RESET_FLAG "reset"
#define RESET_FLAG_SHORT 'r'

#define CONFIG_FILE_FLAG "config-file"
#define CONFIG_FILE_FLAG_SHORT 'c'

#define SET_MAX_LOG_FILES_FLAG "set-max-log-files"
#define SET_MAX_LOG_FILES_FLAG_SHORT 'n'

#define HELP_FLAG "help"
#define HELP_FLAG_SHORT 'h'

#define VERSION_FLAG "version"
#define VERSION_FLAG_SHORT 'v'

#define TOOL_NAME "mstflintlogger"

namespace nvtoolslogger
{

LogConfigUi::LogConfigUi() :
    CommandLineRequester(TOOL_NAME),
    _cmdParser(TOOL_NAME),
    _configFilePath(DEFAULT_CONFIG_PATH),
    _action(Action::NONE),
    _hasGlobalLevel(false),
    _globalLevel(DEFAULT_SEVERITY),
    _hasMaxLogDirFiles(false),
    _maxLogDirFiles(DEFAULT_MAX_LOG_DIR_FILES)
{
    initCmdParser();
}

void LogConfigUi::initCmdParser()
{
    AddDescription("NVIDIA Tools Logger configuration tool. Manages logging severity levels, output sinks, "
                   "and per-module overrides.");

    AddOptions(SET_LEVEL_FLAG, SET_LEVEL_FLAG_SHORT, "LEVEL",
               "Set global severity threshold (debug|info|warning|error|fatal|off)");

    AddOptions(SET_MODULE_FLAG, SET_MODULE_FLAG_SHORT, "MODULE:LEVEL",
               "Set per-module severity (e.g., mtcr:debug). Can be specified multiple times");

    AddOptions(CLEAR_MODULE_FLAG, CLEAR_MODULE_FLAG_SHORT, "MODULE",
               "Remove per-module severity override, reverting to global level. Use 'all' to clear all overrides");

    AddOptions(ENABLE_OUTPUT_FLAG, ENABLE_OUTPUT_FLAG_SHORT, "SINK",
               "Enable an output sink (stdout|stderr|file|syslog). Can be specified multiple times");

    AddOptions(DISABLE_OUTPUT_FLAG, DISABLE_OUTPUT_FLAG_SHORT, "SINK",
               "Disable an output sink (stdout|stderr|file|syslog). Can be specified multiple times");

    AddOptions(SET_MAX_LOG_FILES_FLAG, SET_MAX_LOG_FILES_FLAG_SHORT, "COUNT",
               "Set maximum number of log files in the log directory (default: " +
                 std::to_string(DEFAULT_MAX_LOG_DIR_FILES) + ")");

    AddOptions(SHOW_FLAG, SHOW_FLAG_SHORT, "", "Display the active configuration and resolved layer settings");

    AddOptions(RESET_FLAG, RESET_FLAG_SHORT, "", "Reset the logging configuration to defaults");

    AddOptions(CONFIG_FILE_FLAG, CONFIG_FILE_FLAG_SHORT, "PATH",
               "Override config file path (default: " + std::string(DEFAULT_CONFIG_PATH) + ")");

    AddOptions(HELP_FLAG, HELP_FLAG_SHORT, "", "Show this help message and exit");

    AddOptions(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");

    _cmdParser.AddRequester(this);
}

ParseStatus LogConfigUi::HandleOption(std::string name, std::string value)
{
    if (name == HELP_FLAG)
    {
        printHelp();
        return PARSE_OK_WITH_EXIT;
    }

    if (name == VERSION_FLAG)
    {
        print_version_string(TOOL_NAME, "");
        return PARSE_OK_WITH_EXIT;
    }

    if (name == CONFIG_FILE_FLAG)
    {
        _configFilePath = value;
        return PARSE_OK;
    }

    if (name == SET_LEVEL_FLAG)
    {
        Severity level;
        if (!parseSeverityName(value, level))
        {
            std::cerr << "Error: Invalid severity level '" << value << "'. "
                      << "Valid levels: " << buildValidSeverityList() << std::endl;
            return PARSE_ERROR;
        }
        _hasGlobalLevel = true;
        _globalLevel = level;
        return PARSE_OK;
    }

    if (name == SET_MODULE_FLAG)
    {
        size_t colonPos = value.find(':');
        if (colonPos == std::string::npos || colonPos == 0 || colonPos == value.size() - 1)
        {
            std::cerr << "Error: Invalid module format '" << value << "'. "
                      << "Expected format: MODULE:LEVEL (e.g., mtcr:debug)" << std::endl;
            return PARSE_ERROR;
        }

        std::string moduleName = value.substr(0, colonPos);
        std::string levelStr = value.substr(colonPos + 1);

        Layer layer;
        if (!isConfigurableModule(moduleName, layer))
        {
            std::cerr << "Error: Unknown module '" << moduleName << "'. "
                      << "Valid modules: " << buildValidLayerList() << std::endl;
            return PARSE_ERROR;
        }

        if (layer == Layer::ALL)
        {
            Severity level;
            if (!parseSeverityName(levelStr, level))
            {
                std::cerr << "Error: Invalid severity level '" << levelStr << "'. "
                          << "Valid levels: " << buildValidSeverityList() << std::endl;
                return PARSE_ERROR;
            }
            for (const auto& entry : getLayerTable())
            {
                if (entry.layer != Layer::ALL && entry.layer != Layer::LOGGER)
                {
                    _moduleOverrides.push_back({entry.name, level});
                }
            }
            return PARSE_OK;
        }

        Severity level;
        if (!parseSeverityName(levelStr, level))
        {
            std::cerr << "Error: Invalid severity level '" << levelStr << "'. "
                      << "Valid levels: " << buildValidSeverityList() << std::endl;
            return PARSE_ERROR;
        }

        _moduleOverrides.push_back({getLayerName(layer), level});
        return PARSE_OK;
    }

    if (name == CLEAR_MODULE_FLAG)
    {
        Layer layer;
        if (!isConfigurableModule(value, layer))
        {
            std::cerr << "Error: Unknown module '" << value << "'. "
                      << "Valid modules: " << buildValidLayerList() << std::endl;
            return PARSE_ERROR;
        }

        if (layer == Layer::ALL)
        {
            for (const auto& entry : getLayerTable())
            {
                if (entry.layer != Layer::ALL && entry.layer != Layer::LOGGER)
                {
                    _modulesToClear.push_back(entry.name);
                }
            }
        }
        else
        {
            _modulesToClear.push_back(getLayerName(layer));
        }
        return PARSE_OK;
    }

    if (name == ENABLE_OUTPUT_FLAG)
    {
        Sink sink;
        if (!parseSinkName(value, sink))
        {
            std::cerr << "Error: Unknown sink '" << value << "'. "
                      << "Valid sinks: " << buildValidSinkList() << std::endl;
            return PARSE_ERROR;
        }
        _sinksToEnable.push_back(sink);
        return PARSE_OK;
    }

    if (name == DISABLE_OUTPUT_FLAG)
    {
        Sink sink;
        if (!parseSinkName(value, sink))
        {
            std::cerr << "Error: Unknown sink '" << value << "'. "
                      << "Valid sinks: " << buildValidSinkList() << std::endl;
            return PARSE_ERROR;
        }
        _sinksToDisable.push_back(sink);
        return PARSE_OK;
    }

    if (name == SET_MAX_LOG_FILES_FLAG)
    {
        try
        {
            int val = std::stoi(value);
            if (val <= 0)
            {
                std::cerr << "Error: --" << SET_MAX_LOG_FILES_FLAG << " must be a positive integer." << std::endl;
                return PARSE_ERROR;
            }
            _hasMaxLogDirFiles = true;
            _maxLogDirFiles = static_cast<uint32_t>(val);
        }
        catch (const std::exception&)
        {
            std::cerr << "Error: Invalid value '" << value << "' for --" << SET_MAX_LOG_FILES_FLAG
                      << ". Expected a positive integer." << std::endl;
            return PARSE_ERROR;
        }
        return PARSE_OK;
    }

    if (name == SHOW_FLAG)
    {
        _action = Action::SHOW;
        return PARSE_OK;
    }

    if (name == RESET_FLAG)
    {
        _action = Action::RESET;
        return PARSE_OK;
    }

    std::cerr << "Error: Unknown option '" << name << "'" << std::endl;
    return PARSE_ERROR;
}

int LogConfigUi::run(int argc, char** argv)
{
    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);

    if (rc == PARSE_OK_WITH_EXIT)
    {
        return 0;
    }

    if (rc != PARSE_OK)
    {
        std::cerr << _cmdParser.GetErrDesc() << std::endl;
        std::cerr << "Run '" << TOOL_NAME << " --help' for usage information." << std::endl;
        return 1;
    }

    bool hasModifications = _hasGlobalLevel || _hasMaxLogDirFiles || !_moduleOverrides.empty() ||
                            !_modulesToClear.empty() || !_sinksToEnable.empty() || !_sinksToDisable.empty();

    if (_action == Action::NONE && !hasModifications)
    {
        std::cerr << "Error: No action specified. Use --show, --reset, or a modification flag." << std::endl;
        std::cerr << "Run '" << TOOL_NAME << " --help' for usage information." << std::endl;
        return 1;
    }

    LogConfig config;

    if (_action == Action::RESET)
    {
        config.reset();
        if (!config.save(_configFilePath))
        {
            return 1;
        }
        std::cout << "Configuration reset to defaults." << std::endl;

        if (hasModifications)
        {
            std::cerr << "Warning: Modification flags ignored due to --reset." << std::endl;
        }
        return 0;
    }

    config.load(_configFilePath);

    if (hasModifications)
    {
        if (_hasGlobalLevel)
        {
            config.setGlobalLevel(_globalLevel);
        }

        if (_hasMaxLogDirFiles)
        {
            config.setMaxLogDirFiles(_maxLogDirFiles);
        }

        for (const auto& moduleName : _modulesToClear)
        {
            config.clearModuleLevel(moduleName);
        }

        for (const auto& override : _moduleOverrides)
        {
            config.setModuleLevel(override.moduleName, override.level);
        }

        for (const auto& sink : _sinksToEnable)
        {
            config.enableSink(sink);
        }

        for (const auto& sink : _sinksToDisable)
        {
            config.disableSink(sink);
        }

        if (!config.save(_configFilePath))
        {
            return 1;
        }
        std::cout << "Configuration saved to " << _configFilePath << std::endl;
        std::cout << std::endl;
    }
    else if (_action == Action::SHOW)
    {
        config.show();
    }

    return 0;
}

void LogConfigUi::printHelp()
{
    std::cout << _cmdParser.GetUsage() << std::endl;
}

/* The logger's own meta layer is enabled automatically for any session that logs,
   so it is not addressable as a module: treating it as unknown keeps the CLI from
   accepting a setting it would never apply. */
bool LogConfigUi::isConfigurableModule(const std::string& moduleName, Layer& layer) const
{
    return parseLayerName(moduleName, layer) && layer != Layer::LOGGER;
}

std::string LogConfigUi::buildValidLayerList() const
{
    std::string result;
    for (const auto& entry : getLayerTable())
    {
        if (entry.layer == Layer::LOGGER)
        {
            continue;
        }
        if (!result.empty())
        {
            result += ", ";
        }
        result += entry.name;
    }
    return result;
}

std::string LogConfigUi::buildValidSeverityList() const
{
    std::string result;
    for (const auto& entry : getSeverityTable())
    {
        if (!result.empty())
        {
            result += ", ";
        }
        result += entry.name;
    }
    return result;
}

std::string LogConfigUi::buildValidSinkList() const
{
    std::string result;
    for (const auto& entry : getSinkTable())
    {
        if (!result.empty())
        {
            result += ", ";
        }
        result += entry.name;
    }
    return result;
}

} // namespace nvtoolslogger
