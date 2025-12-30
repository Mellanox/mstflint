/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
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
