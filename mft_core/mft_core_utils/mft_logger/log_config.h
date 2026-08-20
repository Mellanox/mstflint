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

#pragma once

#include <string>
#include <map>
#include <vector>

#include "mft_logger/log_config_defs.h"

namespace mft_logger
{

class LogConfig
{
public:
    LogConfig();

    bool load(const std::string& path);
    bool save(const std::string& path) const;
    void reset();

    void setGlobalLevel(Severity level);
    Severity getGlobalLevel() const;

    void setModuleLevel(const std::string& moduleName, Severity level);
    void clearModuleLevel(const std::string& moduleName);
    const std::map<std::string, Severity>& getModuleLevels() const;

    /* Single source of truth for what a layer actually logs at, shared by the
       logger itself and by --show so the two can never disagree: a layer's
       per-module override if one exists, otherwise the global level. */
    Severity getEffectiveLevel(const std::string& layerName) const;

    /* True when at least one tool layer is live, i.e. the session will produce
       output. Excludes the logger's own meta layer, which is derived from this. */
    bool isAnyLayerEnabled() const;

    void enableSink(Sink sink);
    void disableSink(Sink sink);
    const std::vector<Sink>& getActiveSinks() const;

    void setMaxLogDirFiles(uint32_t maxFiles);
    uint32_t getMaxLogDirFiles() const;

    void show() const;

private:
    void initDefaults();
    std::string toJson() const;
    bool fromJson(const std::string& jsonStr);

    Severity _globalLevel;
    std::map<std::string, Severity> _moduleLevels;
    std::vector<Sink> _activeSinks;
    uint32_t _maxLogDirFiles;
};

} // namespace mft_logger
