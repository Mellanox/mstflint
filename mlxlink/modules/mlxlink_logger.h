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

#ifndef MLXLINK_LOGGER_H
#define MLXLINK_LOGGER_H

#include <string>
#include <cstring>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdarg.h>

#define LINE_WIDTH 103
#define LINE_PATTERN '-'

using namespace std;

enum LOG_LEVEL {
    LEVEL_ERROR,
    LEVEL_WORNING,
    LEVEL_INFO,
    LEVEL_DEBUG
};

class MlxlinkLogger {

public:
    MlxlinkLogger(const string &filePath, LOG_LEVEL logLevel = LEVEL_DEBUG);
    virtual ~MlxlinkLogger();
    void debugLog(const char* format, ...);
    void printHeaderWithUnderLine(const char* title);
    void printHeader(const char* title);
    void printLine(const char* line);
private:
    void printTimeStamp();
    LOG_LEVEL _logLevel;
    FILE* _logFile;
    char _underLine[LINE_WIDTH];
};

#endif /* MLXLINK_LOGGER_H */
