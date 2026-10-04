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

#include "nvtoolslogger/log_config.h"
#include "nvtoolslogger/layers.h"

#include "json/json.h"
#include "json/reader.h"
#include "json/writer.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

#include <cerrno>
#include <sys/stat.h>

static bool mkdirSingle(const std::string& dir)
{
    return mkdir(dir.c_str(), 0700) == 0 || errno == EEXIST;
}

static bool ensureParentDirExists(const std::string& filePath)
{
    size_t pos = filePath.find_last_of('/');
    if (pos == std::string::npos)
    {
        return true;
    }

    std::string dir = filePath.substr(0, pos);
    if (dir.empty())
    {
        return true;
    }

    // loop finding all directory separators
    size_t i = dir.find_first_of('/', 0);
    while (i != std::string::npos)
    {
        if (i > 0)
        { // Skip leading slash for absolute paths
            std::string base = dir.substr(0, i);
            if (!mkdirSingle(base))
            {
                return false;
            }
        }
        i = dir.find_first_of('/', i + 1);
    }

    return mkdirSingle(dir);
}

namespace nvtoolslogger
{
LogConfig::LogConfig()
{
    initDefaults();
}

void LogConfig::initDefaults()
{
    _globalLevel = DEFAULT_SEVERITY;
    _moduleLevels.clear();
    _activeSinks.clear();
    _maxLogDirFiles = DEFAULT_MAX_LOG_DIR_FILES;
}

void LogConfig::reset()
{
    initDefaults();
}

bool LogConfig::load(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        return false;
    }

    std::stringstream buffer(std::ios_base::in | std::ios_base::out);
    buffer << file.rdbuf();
    file.close();

    return fromJson(buffer.str());
}

bool LogConfig::save(const std::string& path) const
{
    std::string jsonStr = toJson();
    /* Avoid race condition by writing to a temporary file and then renaming it */
    std::string tmpPath = path + ".tmp";

    if (!ensureParentDirExists(path))
    {
        std::cerr << "Error: Cannot create parent directory for config file: " << path << std::endl;
        return false;
    }

    std::ofstream file(tmpPath);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open temp config file for writing: " << tmpPath << std::endl;
        return false;
    }

    file << jsonStr;
    if (!file.good())
    {
        std::cerr << "Error: Failed to write to temp config file: " << tmpPath << std::endl;
        file.close();
        std::remove(tmpPath.c_str());
        return false;
    }
    file.close();

    // rename() over an existing path is atomic on POSIX: a reader starting
    // mid-write sees either the old file or the new one, never a partial one.
    if (std::rename(tmpPath.c_str(), path.c_str()) != 0)
    {
        std::cerr << "Error: Failed to replace old config file." << std::endl;
        return false;
    }

    return true;
}

void LogConfig::setGlobalLevel(Severity level)
{
    _globalLevel = level;
}

Severity LogConfig::getGlobalLevel() const
{
    return _globalLevel;
}

void LogConfig::setModuleLevel(const std::string& moduleName, Severity level)
{
    _moduleLevels[moduleName] = level;
}

void LogConfig::clearModuleLevel(const std::string& moduleName)
{
    _moduleLevels.erase(moduleName);
}

const std::map<std::string, Severity>& LogConfig::getModuleLevels() const
{
    return _moduleLevels;
}

Severity LogConfig::getEffectiveLevel(const std::string& layerName) const
{
    // The logger's own meta layer is not severity-configurable: it is on for any
    // session that logs, so the startup banner always heads the output it describes.
    if (layerName == getLayerName(Layer::LOGGER))
    {
        return isAnyLayerEnabled() ? Severity::Debug : Severity::Default;
    }

    auto it = _moduleLevels.find(layerName);
    return (it != _moduleLevels.end()) ? it->second : _globalLevel;
}

bool LogConfig::isAnyLayerEnabled() const
{
    for (const auto& entry : getLayerTable())
    {
        // LOGGER is derived from this answer; ALL is a CLI parsing alias, not a real layer.
        if (entry.layer == Layer::LOGGER || entry.layer == Layer::ALL)
        {
            continue;
        }
        if (getEffectiveLevel(entry.name) != Severity::Default)
        {
            return true;
        }
    }
    return false;
}

void LogConfig::enableSink(Sink sink)
{
    for (const auto& s : _activeSinks)
    {
        if (s == sink)
        {
            return;
        }
    }
    _activeSinks.push_back(sink);
}

void LogConfig::disableSink(Sink sink)
{
    _activeSinks.erase(std::remove(_activeSinks.begin(), _activeSinks.end(), sink), _activeSinks.end());
}

const std::vector<Sink>& LogConfig::getActiveSinks() const
{
    return _activeSinks;
}

void LogConfig::setMaxLogDirFiles(uint32_t maxFiles)
{
    _maxLogDirFiles = maxFiles;
}

uint32_t LogConfig::getMaxLogDirFiles() const
{
    return _maxLogDirFiles;
}

void LogConfig::show() const
{
    std::cout << "NVIDIA Tools Logger Configuration" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << std::endl;

    std::cout << "Global severity level: " << getSeverityName(_globalLevel) << std::endl;
    std::cout << "Max log directory files: " << _maxLogDirFiles << std::endl;
    std::cout << std::endl;

    std::cout << "Active sinks:";
    if (_activeSinks.empty())
    {
        std::cout << " (none)" << std::endl;
    }
    else
    {
        std::cout << std::endl;
        for (const auto& sink : _activeSinks)
        {
            std::cout << "  - " << getSinkName(sink) << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "Per-module severity overrides:" << std::endl;
    if (_moduleLevels.empty())
    {
        std::cout << "  (none)" << std::endl;
    }
    else
    {
        for (const auto& pair : _moduleLevels)
        {
            std::cout << "  " << pair.first << ": " << getSeverityName(pair.second) << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "Resolved layer settings:" << std::endl;
    for (const auto& entry : getLayerTable())
    {
        // LOGGER is the logger's own meta layer, not user-configurable; ALL is a CLI
        // parsing alias. Neither is a setting the user can act on, so neither is listed.
        if (entry.layer == Layer::LOGGER || entry.layer == Layer::ALL)
        {
            continue;
        }
        const char* source = (_moduleLevels.count(entry.name) != 0) ? "(override)" : "(global)";
        std::cout << "  " << entry.name << ": " << getSeverityName(getEffectiveLevel(entry.name)) << " " << source
                  << std::endl;
    }
}

std::string LogConfig::toJson() const
{
    Json::Value root;
    root["version"] = CONFIG_VERSION;
    root["global_level"] = getSeverityName(_globalLevel);
    root["max_log_dir_files"] = static_cast<Json::UInt>(_maxLogDirFiles);

    Json::Value sinksArray(Json::arrayValue);
    for (const auto& sink : _activeSinks)
    {
        sinksArray.append(getSinkName(sink));
    }
    root["sinks"] = sinksArray;

    Json::Value modules(Json::objectValue);
    for (const auto& pair : _moduleLevels)
    {
        modules[pair.first] = getSeverityName(pair.second);
    }
    root["modules"] = modules;

    Json::StreamWriterBuilder builder;
    return Json::writeString(builder, root) + "\n";
}

bool LogConfig::fromJson(const std::string& jsonStr)
{
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;

    // Use a unique_ptr to manage the reader instance
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

    if (!reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.length(), &root, &errs))
    {
        std::cerr << "Error: Failed to parse config JSON: " << errs << std::endl;
        return false;
    }

    if (root.isMember("global_level") && root["global_level"].isString())
    {
        Severity level;
        if (parseSeverityName(root["global_level"].asString(), level))
        {
            _globalLevel = level;
        }
    }

    if (root.isMember("max_log_dir_files") && root["max_log_dir_files"].isUInt())
    {
        _maxLogDirFiles = root["max_log_dir_files"].asUInt();
    }

    if (root.isMember("sinks") && root["sinks"].isArray())
    {
        _activeSinks.clear();
        for (const auto& sinkVal : root["sinks"])
        {
            if (sinkVal.isString())
            {
                Sink sink;
                if (parseSinkName(sinkVal.asString(), sink))
                {
                    _activeSinks.push_back(sink);
                }
            }
        }
    }

    if (root.isMember("modules") && root["modules"].isObject())
    {
        _moduleLevels.clear();
        for (const auto& key : root["modules"].getMemberNames())
        {
            if (root["modules"][key].isString())
            {
                Layer layer;
                if (!parseLayerName(key, layer))
                {
                    std::cerr << "Warning: Unknown module '" << key << "' in config file, skipping." << std::endl;
                    continue;
                }

                // Drop any stored level for the logger's own meta layer, which earlier
                // versions could write: it has no configurable severity, so keeping it
                // would list an override that does nothing.
                if (layer == Layer::LOGGER)
                {
                    continue;
                }

                Severity level = DEFAULT_SEVERITY;
                if (parseSeverityName(root["modules"][key].asString(), level))
                {
                    _moduleLevels[getLayerName(layer)] = level;
                }
            }
        }
    }

    return true;
}

} // namespace nvtoolslogger
