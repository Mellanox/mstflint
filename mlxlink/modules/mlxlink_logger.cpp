/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

#include "mlxlink_logger.h"

MlxlinkLogger::MlxlinkLogger(const string &filePath, LOG_LEVEL logLevel)
{
    _logLevel = logLevel;
    _logFile = fopen (filePath.c_str(),"w");
    memset(_underLine, LINE_PATTERN, LINE_WIDTH);
}

MlxlinkLogger::~MlxlinkLogger()
{
    if (_logFile) {
        fclose(_logFile);
    }
}

void MlxlinkLogger::printTimeStamp()
{
    static char buf[128];
    struct timeval tv;
    time_t curtime;
    gettimeofday(&tv, NULL);
    curtime = tv.tv_sec;
    strftime(buf, sizeof(buf), "%x %H:%M:%S", localtime(&curtime));
    fprintf(_logFile, "[%s.%03ld]  ", buf, tv.tv_usec/1000);

}

void MlxlinkLogger::debugLog(const char* format, ...)
{
    if (_logFile) {
        printTimeStamp();
        fprintf(_logFile, "-D- ");
        va_list args;
        va_start (args, format);
        vfprintf (_logFile, format, args);
        va_end (args);
        fflush(_logFile);
    }
}

void MlxlinkLogger::printHeaderWithUnderLine(const char* title)
{
    if (_logFile) {
        fprintf(_logFile, "%s", _underLine);
        fprintf(_logFile, "\n");
        fprintf(_logFile, "FUNCTION\t\t");
        fprintf(_logFile, "%s", title);
        fprintf(_logFile, "\n");
        fprintf(_logFile, "%s", _underLine);
        fprintf(_logFile, "\n");
        fflush(_logFile);
    }
}
