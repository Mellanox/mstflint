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

#include "Linux.h"
#include <sys/stat.h>
#include <termios.h>
#include <chrono>
#include <climits>
#include <iostream>
#include <stdexcept>
#include <thread>
#include "common/compatibility.h"

#if !defined(__linux__)
#define HOST_NAME_MAX 64
#endif

using std::string;
using std::runtime_error;

const string Linux::GetExecutableDir()
{
    string oFullPath(GetExecutablePath());
    return oFullPath.substr(0, oFullPath.find_last_of("/"));
}

const string Linux::GetExecutablePath()
{
    char buf[PATH_MAX + 1];
    ssize_t len = readlink("/proc/self/exe", buf, PATH_MAX);
    if (len == -1)
    {
        throw runtime_error("Failed to get the executable path");
    }
    buf[len] = '\0';
    return string(buf);
}

const string Linux::GetExecutableName()
{
    string oFullPath = GetExecutablePath();
    size_t iFound = oFullPath.find_last_of("/");
    if (iFound == string::npos)
    {
        return oFullPath;
    }
    return oFullPath.substr(iFound + 1);
}

void Linux::CreateDirectoryIfNotExist(const string& poNewDirectory)
{
    // mkdir() returns zero on success, or -1 if an error occurred.
    // in which case, errno is set appropriately.
    if (mkdir(poNewDirectory.c_str(), 0777))
    {
        switch (errno)
        {
            case EEXIST:
            case 0:
                return;

            default:
                throw runtime_error("Cannot create the directory: " + poNewDirectory);
                return;
        }
    }
}

int Linux::GetPID()
{
    return getpid();
}

const string Linux::GetLogDirectory()
{
    return "/var/log/mft/";
}

void Linux::LittleToBig32(uint32_t& uLittleEndianBuffer, const int iLength)
{
    for (int iCounter = 0; iCounter < iLength / 4; iCounter++)
    {
        (&uLittleEndianBuffer)[iCounter] = __be32_to_cpu((&uLittleEndianBuffer)[iCounter]);
    }
}

void Linux::MilliSecondsSleep(int iMilliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(iMilliseconds));
}

void Linux::GetHostName(char* pcHostName)
{
    gethostname(pcHostName, HOST_NAME_MAX);
}

void Linux::InputPassword(char* pcPass, unsigned int uMaxLen)
{
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::cin.getline(pcPass, uMaxLen);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

const string Linux::GetFilePath(const string& oDirName, const string& oFileName)
{
    return oDirName + "/" + oFileName;
}

uint32_t Linux::get_page_size()
{
    return sysconf(_SC_PAGESIZE);
}

std::pair<int, std::string> Linux::execCommand(const std::string& cmd)
{
    std::string output;
    FILE* pipe = popen((cmd + " 2>&1").c_str(), "r");
    if (!pipe)
    {
        return {-1, "popen failed"};
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        output += buffer;
    }

    int status = pclose(pipe);

    return {status, output};
}