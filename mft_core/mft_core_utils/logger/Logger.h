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

#ifndef LOGGER_H
#define LOGGER_H

#include <exception>
#include <array>
#include <sstream>

#include "LoggerDefs.h"

namespace mft_core
{
class Logger
{
private:
    // Singleton.
    Logger();
    Logger(const std::string envVariable = PRINT_LOGGER_ENV_VAR);
    virtual ~Logger() = default;
    static Logger* s_poLogger;

    // Severity level map.
    std::array<std::string, static_cast<std::size_t>(eLoggerSeverityLevel::severity_count)> s_oSeverityLevelMap;

    void InitSeverityLevelMap();

    // Write the log to the stream buffer.
    void Log(eLoggerSeverityLevel eSeverityLevel, const std::string& poLogMessage);

    // Create current time string.
    const std::string GetDateTime();

    // Build the prefix message: [severity level] | date.
    const std::string GetPrefix(eLoggerSeverityLevel eSeverityLevel);

    // Check if we allowed to write the log message
    //   according to the severity level.
    bool CheckSeverityLevel(eLoggerSeverityLevel eSeverityLevel);

    void SetLocation(const std::string& oLocation);

    // String buffer for hexify function.
    std::stringstream m_oHexBuffer;

    std::string m_oLocation;

    // Severity level.
    eLoggerSeverityLevel m_eSeverityLevel;

    // Print Logger to Screen.
    char* m_pcPrintToScreen;

    // Severity from which to print to the screen.
    unsigned int m_uPrintToScreenLevel;

public:
    // Get the logger OS instance.
    static Logger& GetInstance(const std::string& oLocation = std::string(),
                               const std::string& envVariable = PRINT_LOGGER_ENV_VAR);
    static void DeleteInstance();
    void UpdateEnvVariable(const std::string& envVariable);

    // Initialize the logger.
    void Init(eLoggerSeverityLevel eSeverityLevel = eLoggerSeverityLevel::debug);

    // API for writing the log message.
    void Debug(const std::string& poLogMessage);
    void Info(const std::string& poLogMessage);
    void Warning(const std::string& poLogMessage);
    void Error(const std::string& poLogMessage);
    void Fatal(const std::string& poLogMessage);

    // Convert number to hex in string format.
    std::string Hexify(int iNum);
};

#define _MFT_CORE_LOGGER_STRINGIFY(s) #s
#define MFT_CORE_LOGGER_STRINGIFY(s) _MFT_CORE_LOGGER_STRINGIFY(s)
#define LOCATION \
    std::string(" [" __FILE__ "_").append(__FUNCTION__).append("():" MFT_CORE_LOGGER_STRINGIFY(__LINE__) "]")

#define LOG mft_core::Logger::GetInstance(LOCATION)

#define HEXIFY(iNum) LOG.Hexify(iNum)

struct LoggerException : public std::exception
{
    const char* what() const throw() { return "Cannot create the logger instance"; }
};

} // namespace mft_core

#endif // LOGGER_H
