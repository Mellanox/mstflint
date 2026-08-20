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

#include "mft_logger/mft_logger.h"
#include "mft_logger/mft_logger_c.h"
#include "mft_logger/log_config.h"
#include "mft_logger/log_config_defs.h"
#include "mft_logger/layers.h"

#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"
#include "common/tools_version.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/syslog_sink.h>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

static const size_t LOG_FORMAT_BUFFER_SIZE = 4096;
static const size_t LOG_FILE_MAX_SIZE = 10 * 1024 * 1024; // 10 MB
static const size_t LOG_FILE_MAX_FILES = 5;

// Standard event pattern: timestamp, colored severity, layer name, source location, message.
static const char* const LOG_PATTERN_STANDARD = "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%n] [%s:%# %!] %v";
// Startup banner pattern: no severity tag or source location - the banner
// describes the session, not an event, and bypasses level filtering.
static const char* const LOG_PATTERN_BANNER = "[%Y-%m-%d %H:%M:%S.%e] [%n] %v";

struct LogFileInfo
{
    std::string path;
    uint64_t lastModified;

    bool operator<(const LogFileInfo& other) const { return lastModified < other.lastModified; }
};

static std::string getBaseLogDirectory()
{
    // Standard system log directory
    return "/var/log/mstflint/";
}

static void cleanupOldLogFiles(std::string& logDir, size_t maxFiles)
{
    std::vector<LogFileInfo> files;

    // Perform exactly ONE directory scan
    DIR* dir = opendir(logDir.c_str());
    if (dir != nullptr)
    {
        struct dirent* ent;
        while ((ent = readdir(dir)) != nullptr)
        {
            std::string name(ent->d_name);

            // Target only log files and ignore "." and ".."
            if (name == "." || name == ".." || name.find(".log") == std::string::npos)
            {
                continue;
            }

            std::string fullPath = logDir + name;
            struct stat st;

            // stat() safely identifies regular files across ALL Linux filesystems (ext4, XFS, etc.)
            if (stat(fullPath.c_str(), &st) == 0 && S_ISREG(st.st_mode))
            {
                files.push_back({fullPath, static_cast<uint64_t>(st.st_mtime)});
            }
        }
        closedir(dir);
    }

    // Delete excess files
    if (files.size() > maxFiles)
    {
        std::sort(files.begin(), files.end());

        size_t filesToDelete = files.size() - maxFiles;
        for (size_t i = 0; i < filesToDelete; ++i)
        {
            // If std::remove returns != 0, it means the file
            // is locked or another process just deleted it. We safely ignore the failure
            // and continue cleaning up the rest.
            std::remove(files[i].path.c_str());
        }
    }
}

static spdlog::level::level_enum toSpdlogLevel(mft_logger::Severity severity)
{
    switch (severity)
    {
        case mft_logger::Severity::Debug:
            return spdlog::level::debug;
        case mft_logger::Severity::Info:
            return spdlog::level::info;
        case mft_logger::Severity::Warning:
            return spdlog::level::warn;
        case mft_logger::Severity::Error:
            return spdlog::level::err;
        case mft_logger::Severity::Fatal:
            return spdlog::level::critical;
        case mft_logger::Severity::Default:
            return spdlog::level::off;
        default:
            return spdlog::level::off;
    }
}

static spdlog::level::level_enum toSpdlogLevel(int severity)
{
    return toSpdlogLevel(static_cast<mft_logger::Severity>(severity));
}

static std::string getProcessLogName()
{
    std::string name = "mft";
    char buf[256] = {0};
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len > 0)
    {
        buf[len] = '\0';
        std::string path(buf);
        size_t pos = path.rfind('/');
        name = (pos != std::string::npos) ? path.substr(pos + 1) : path;
    }
    return name + "_" + std::to_string(getpid());
}

namespace mft_logger
{
struct MftLogger::Impl
{
    bool _initialized;
    std::array<std::shared_ptr<spdlog::logger>, MFT_LAYER_COUNT> _loggers;

    Impl() : _initialized(false) {}

    void initialize()
    {
        if (_initialized)
        {
            return;
        }

        mft_logger::LogConfig config;
        bool success = config.load(mft_logger::DEFAULT_CONFIG_PATH);
        if (!success)
        {
            return;
        }

        // Deliberately the _st (single-threaded) sink variants: they take no lock,
        // so a log record costs a level compare and a formatted write. The contract
        // this buys is on the call sites, not here - MFT_LOG_* must be called from
        // one thread per process. A tool that needs to log from several threads has
        // to move this file to the _mt variants first; sharing sink instances across
        // layers means there is no way to make only one layer thread-safe.
        std::vector<spdlog::sink_ptr> sinks;
        for (const auto& sink : config.getActiveSinks())
        {
            switch (sink)
            {
                case mft_logger::Sink::STDOUT:
                    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
                    break;
                case mft_logger::Sink::STDERR:
                    sinks.push_back(std::make_shared<spdlog::sinks::stderr_color_sink_st>());
                    break;
                case mft_logger::Sink::FILE_SINK:
                {
                    std::string logDir = getBaseLogDirectory();
                    cleanupOldLogFiles(logDir, config.getMaxLogDirFiles());
                    std::string logPath = logDir + getProcessLogName() + ".log";
                    try
                    {
                        sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_st>(
                          logPath, LOG_FILE_MAX_SIZE, LOG_FILE_MAX_FILES));
                    }
                    catch (const spdlog::spdlog_ex& ex)
                    {
                        fprintf(stderr, "Failed to initialize file logger: %s\n", ex.what());
                    }
                    break;
                }
                case mft_logger::Sink::SYSLOG:
                    sinks.push_back(std::make_shared<spdlog::sinks::syslog_sink_st>("mft", LOG_PID, LOG_USER, false));
                    break;
                default:
                    break;
            }
        }

        if (sinks.empty())
        {
            sinks.push_back(std::make_shared<spdlog::sinks::stderr_color_sink_st>());
        }

        const auto& layerTable = mft_logger::getLayerTable();
        for (const auto& entry : layerTable)
        {
            if (entry.layer == mft_logger::Layer::ALL)
            {
                continue;
            }

            int idx = static_cast<int>(entry.layer);
            if (idx < 0 || idx >= MFT_LAYER_COUNT)
            {
                continue;
            }

            auto logger = std::make_shared<spdlog::logger>(std::string(entry.name), sinks.begin(), sinks.end());

            logger->set_level(toSpdlogLevel(config.getEffectiveLevel(entry.name)));

            // All layer loggers share the same sink instances
            logger->set_pattern(LOG_PATTERN_STANDARD);
            logger->flush_on(spdlog::level::err);

            _loggers[idx] = logger;
        }

        _initialized = true;
        logStartupInfo();
    }

    // Records process identity once per session so every log file/stream is
    // self-describing: which process wrote it, how it was invoked, and which
    // MFT build produced it. Emitted on the always-enabled LOGGER layer so it
    // surfaces regardless of which tool layers are active. Best effort: any
    // failure here is swallowed so it can never prevent the logger from being
    // created.
    void logStartupInfo()
    {
        const int layer = static_cast<int>(mft_logger::Layer::LOGGER);
        auto& metaLogger = _loggers[layer];
        if (!metaLogger)
        {
            return;
        }

        // Gather the metadata first: these OS/version calls can throw, and we
        // must not touch the shared sink patterns until we know we have lines to
        // emit (otherwise a throw could leave the sinks in banner mode).
        std::string pidLine;
        std::string cmdLine;
        std::string versionLine;
        try
        {
            auto os = FactoryOperatingSystemAPI::GetInstance();

            std::string exeName;
            try
            {
                exeName = os->GetExecutableName();
            }
            catch (const std::exception&)
            {
                exeName = "mft";
            }

            char versionBuf[512] = {0};
            get_version_string(versionBuf, sizeof(versionBuf), exeName.c_str(), "");

            pidLine = "PID: " + std::to_string(os->GetPID());
            cmdLine = "Command line: " + os->GetCommandLineString();
            versionLine = std::string("MFT version: ") + versionBuf;
        }
        catch (...)
        {
            // Startup metadata is diagnostic only; never let it break logging.
            return;
        }

        // Emit the banner under the label-free pattern, then restore the standard
        // pattern so all subsequent logging (through the shared sinks) is normal.
        const int severity = static_cast<int>(mft_logger::Severity::Debug);
        metaLogger->set_pattern(LOG_PATTERN_BANNER);
        log(layer, severity, __FILE__, __LINE__, __func__, pidLine.c_str());
        log(layer, severity, __FILE__, __LINE__, __func__, cmdLine.c_str());
        log(layer, severity, __FILE__, __LINE__, __func__, versionLine.c_str());
        metaLogger->set_pattern(LOG_PATTERN_STANDARD);
    }

    void destroy()
    {
        if (!_initialized)
        {
            return;
        }
        for (auto& logger : _loggers)
        {
            logger.reset();
        }
        _initialized = false;
    }

    void log(int layer, int severity, const char* file, int line, const char* func, const char* message)
    {
        if (layer < 0 || layer >= MFT_LAYER_COUNT)
        {
            return;
        }

        auto& logger = _loggers[layer];
        if (!logger)
        {
            return;
        }
        if (message == nullptr)
        {
            return;
        }
        logger->log(spdlog::source_loc{file, line, func}, toSpdlogLevel(severity), message);
    }
};

MftLogger& MftLogger::getInstance()
{
    static MftLogger instance;
    return instance;
}

MftLogger::MftLogger() : _impl(new Impl())
{
    initialize();
}

MftLogger::~MftLogger()
{
    destroy();
    delete _impl;
}

void MftLogger::initialize()
{
    _impl->initialize();
}

void MftLogger::destroy()
{
    _impl->destroy();
}

void MftLogger::log(Layer layer, Severity severity, const char* message, const char* file, int line, const char* func)
{
    _impl->log(static_cast<int>(layer), static_cast<int>(severity), file, line, func, message);
}

void MftLogger::debug(Layer layer, const char* message, const char* file, int line, const char* func)
{
    log(layer, Severity::Debug, message, file, line, func);
}

void MftLogger::info(Layer layer, const char* message, const char* file, int line, const char* func)
{
    log(layer, Severity::Info, message, file, line, func);
}

void MftLogger::warning(Layer layer, const char* message, const char* file, int line, const char* func)
{
    log(layer, Severity::Warning, message, file, line, func);
}

void MftLogger::error(Layer layer, const char* message, const char* file, int line, const char* func)
{
    log(layer, Severity::Error, message, file, line, func);
}

void MftLogger::fatal(Layer layer, const char* message, const char* file, int line, const char* func)
{
    log(layer, Severity::Fatal, message, file, line, func);
}

void MftLogger::logf(Layer layer, Severity severity, const char* file, int line, const char* func, const char* fmt, ...)
{
    if (fmt == nullptr)
    {
        return;
    }
    char buffer[LOG_FORMAT_BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    buffer[sizeof(buffer) - 1] = '\0';
    va_end(args);

    _impl->log(static_cast<int>(layer), static_cast<int>(severity), file, line, func, buffer);
}

} // namespace mft_logger

extern "C" void mft_log(int layer, int severity, const char* file, int line, const char* func, const char* message)
{
    if (layer < 0 || layer >= MFT_LAYER_COUNT)
    {
        return;
    }
    if (message == nullptr)
    {
        return;
    }
    mft_logger::MftLogger::getInstance().log(static_cast<mft_logger::Layer>(layer),
                                             static_cast<mft_logger::Severity>(severity), message, file, line, func);
}

extern "C" void mft_log_fmt(int layer, int severity, const char* file, int line, const char* func, const char* fmt, ...)
{
    if (fmt == nullptr)
    {
        return;
    }
    if (layer < 0 || layer >= MFT_LAYER_COUNT)
    {
        return;
    }
    char buffer[LOG_FORMAT_BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    buffer[sizeof(buffer) - 1] = '\0';
    va_end(args);

    mft_logger::MftLogger::getInstance().log(static_cast<mft_logger::Layer>(layer),
                                             static_cast<mft_logger::Severity>(severity), buffer, file, line, func);
}
