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

#include "Logger.h"

#include <iostream>
#include <memory>
#include <mutex>

using std::string;
using std::cout;
using std::endl;
using std::hex;
using std::to_string;
using std::stoi;
using std::unique_ptr;
using std::exception;

namespace mft_core
{
Logger* Logger::s_poLogger = NULL;

std::mutex logger_mutex;

void Logger::InitSeverityLevelMap()
{
    s_oSeverityLevelMap[static_cast<std::size_t>(eLoggerSeverityLevel::debug)] = "Debug";
    s_oSeverityLevelMap[static_cast<std::size_t>(eLoggerSeverityLevel::info)] = "Info",
    s_oSeverityLevelMap[static_cast<std::size_t>(eLoggerSeverityLevel::warning)] = "Warning";
    s_oSeverityLevelMap[static_cast<std::size_t>(eLoggerSeverityLevel::error)] = "Error";
    s_oSeverityLevelMap[static_cast<std::size_t>(eLoggerSeverityLevel::fatal)] = "Fatal";
}

Logger::Logger() : Logger(PRINT_LOGGER_ENV_VAR){};

Logger::Logger(const string envVariable) : m_eSeverityLevel(eLoggerSeverityLevel::debug)
{
    m_pcPrintToScreen = getenv(envVariable.c_str());

    InitSeverityLevelMap();

    try
    {
        if (m_pcPrintToScreen == NULL)
        { // In some compilers stoi doesn't throw on NULL so we need an explicit check
            throw std::invalid_argument("Uninitialised environment argument");
        }
        m_uPrintToScreenLevel = stoi(m_pcPrintToScreen);
        if (m_uPrintToScreenLevel >= s_oSeverityLevelMap.size())
        {
            m_uPrintToScreenLevel = 0;
        }
    }
    catch (exception& e)
    {
        m_uPrintToScreenLevel = 0;
    }
}

Logger& Logger::GetInstance(const string& oLocation, const string& envVariable)
{
    std::lock_guard<std::mutex> guard(logger_mutex); // protect from here to the end of the function.
    if (!s_poLogger)
    {
        s_poLogger = new Logger(envVariable);
    }
    s_poLogger->SetLocation(oLocation);

    return *s_poLogger;
}

void Logger::SetLocation(const string& oLocation)
{
    m_oLocation = oLocation;
}

void Logger::UpdateEnvVariable(const string& envVariable)
{
    char* pcPrintToScreen = getenv(envVariable.c_str());

    if (pcPrintToScreen == NULL)
    {
        s_poLogger->m_pcPrintToScreen = 0; // stop printing.
        return;
    }
    unsigned int uPrintToScreenLevel = stoi(pcPrintToScreen);
    if (uPrintToScreenLevel >= s_poLogger->s_oSeverityLevelMap.size())
    {
        uPrintToScreenLevel = 0;
    }
    s_poLogger->m_pcPrintToScreen = pcPrintToScreen;
    s_poLogger->m_uPrintToScreenLevel = uPrintToScreenLevel;
}

void Logger::DeleteInstance()
{
    if (s_poLogger)
    {
        delete s_poLogger;
        s_poLogger = NULL;
    }
}

void Logger::Init(eLoggerSeverityLevel eSeverityLevel)
{
    // Set the severity level.
    m_eSeverityLevel = eSeverityLevel;
}

const string Logger::GetDateTime()
{
    time_t sTimeNow = time(0);
    struct tm psTime = *localtime(&sTimeNow);
    char cBuffer[80];

    strftime(cBuffer, sizeof(cBuffer), "%Y-%m-%d_%X", &psTime);

    // The return type is "const string", so it is returned by value and
    //   then a copy of buffer is made, before releasing it.
    return string(cBuffer);
}

const string Logger::GetPrefix(eLoggerSeverityLevel eSeverityLevel)
{
    // Build the prefix: '[Severity] DATE |'
    return string("[" + s_oSeverityLevelMap[static_cast<std::size_t>(eSeverityLevel)] + "] " + GetDateTime() +
                  m_oLocation + " | ");
}

bool Logger::CheckSeverityLevel(eLoggerSeverityLevel eSeverityLevel)
{
    // Check the severity level.
    if (eSeverityLevel >= m_eSeverityLevel)
    {
        return true;
    }

    return false;
}

// FIXME not thread safe
string Logger::Hexify(int iNum)
{
    m_oHexBuffer.str(std::string());
    m_oHexBuffer << "0x" << hex << iNum;
    return m_oHexBuffer.str();
}

void Logger::Log(eLoggerSeverityLevel eSeverityLevel, const string& poLogMessage)
{
    if (m_pcPrintToScreen && static_cast<unsigned int>(eSeverityLevel) >= m_uPrintToScreenLevel)
    {
        cout << GetPrefix(eSeverityLevel) << poLogMessage << endl;
    }
}

void Logger::Debug(const string& poLogMessage)
{
    if (CheckSeverityLevel(eLoggerSeverityLevel::debug))
    {
        Log(eLoggerSeverityLevel::debug, poLogMessage);
    }
}

void Logger::Info(const string& poLogMessage)
{
    if (CheckSeverityLevel(eLoggerSeverityLevel::info))
    {
        Log(eLoggerSeverityLevel::info, poLogMessage);
    }
}

void Logger::Warning(const string& poLogMessage)
{
    if (CheckSeverityLevel(eLoggerSeverityLevel::warning))
    {
        Log(eLoggerSeverityLevel::warning, poLogMessage);
    }
}

void Logger::Error(const string& poLogMessage)
{
    if (CheckSeverityLevel(eLoggerSeverityLevel::error))
    {
        Log(eLoggerSeverityLevel::error, poLogMessage);
    }
}

void Logger::Fatal(const string& poLogMessage)
{
    if (CheckSeverityLevel(eLoggerSeverityLevel::fatal))
    {
        Log(eLoggerSeverityLevel::fatal, poLogMessage);
    }
}

} // namespace mft_core
