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

#ifndef NVTOOLSLOGGER_CONFIG_DEFS_H
#define NVTOOLSLOGGER_CONFIG_DEFS_H

/* ── C-compatible severity definitions (usable from .c and .cpp) ── */

enum mft_severity
{
    MFT_SEV_DEBUG = 0,
    MFT_SEV_INFO,
    MFT_SEV_WARNING,
    MFT_SEV_ERROR,
    MFT_SEV_FATAL,
    MFT_SEV_NONE
};

#ifdef __cplusplus

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

namespace nvtoolslogger
{

enum class Severity
{
    Debug = MFT_SEV_DEBUG,
    Info = MFT_SEV_INFO,
    Warning = MFT_SEV_WARNING,
    Error = MFT_SEV_ERROR,
    Fatal = MFT_SEV_FATAL,
    Default = MFT_SEV_NONE,
};

struct SeverityEntry
{
    Severity level;
    const char* name;
};

inline const std::vector<SeverityEntry>& getSeverityTable()
{
    static const std::vector<SeverityEntry> table = {
      {Severity::Debug, "debug"}, {Severity::Info, "info"},   {Severity::Warning, "warning"},
      {Severity::Error, "error"}, {Severity::Fatal, "fatal"}, {Severity::Default, "off"},
    };
    return table;
}

inline const char* getSeverityName(Severity level)
{
    for (const auto& entry : getSeverityTable())
    {
        if (entry.level == level)
        {
            return entry.name;
        }
    }
    return nullptr;
}

inline bool parseSeverityName(const std::string& name, Severity& out)
{
    std::string lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    for (const auto& entry : getSeverityTable())
    {
        if (lower == entry.name)
        {
            out = entry.level;
            return true;
        }
    }
    return false;
}

enum class Sink
{
    STDOUT = 0,
    STDERR,
    FILE_SINK,
    SYSLOG
};

struct SinkEntry
{
    Sink sink;
    const char* name;
};

inline const std::vector<SinkEntry>& getSinkTable()
{
    static const std::vector<SinkEntry> table = {
      {Sink::STDOUT, "stdout"},
      {Sink::STDERR, "stderr"},
      {Sink::FILE_SINK, "file"},
      {Sink::SYSLOG, "syslog"},
    };
    return table;
}

inline const char* getSinkName(Sink sink)
{
    for (const auto& entry : getSinkTable())
    {
        if (entry.sink == sink)
        {
            return entry.name;
        }
    }
    return nullptr;
}

inline bool parseSinkName(const std::string& name, Sink& out)
{
    std::string lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    for (const auto& entry : getSinkTable())
    {
        if (lower == entry.name)
        {
            out = entry.sink;
            return true;
        }
    }
    return false;
}

// Root-only state directory, so the config (and the log file paths it dictates)
// cannot be tampered with by non-root users. Deliberately under /var/lib/mstflint
// rather than MFT's /var/lib/mft: the two products ship separate layer sets, and a
// shared file would have each one dropping the other's unknown per-layer overrides.
static constexpr const char* DEFAULT_CONFIG_PATH = "/var/lib/mstflint/mstflintlogger.json";
static const Severity DEFAULT_SEVERITY = Severity::Default;
static const uint32_t DEFAULT_MAX_LOG_DIR_FILES = 100;
static const int CONFIG_VERSION = 1;

} // namespace nvtoolslogger

#endif /* __cplusplus */
#endif /* NVTOOLSLOGGER_CONFIG_DEFS_H */
