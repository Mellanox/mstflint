/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 *  Version: $Id$
 */

#include "adb_logfile.h"

#define WRITE   "w"

LogFile::LogFile() : _logFile(NULL) {
}

void LogFile::init(string logFileName, bool allowMultipleExceptions) {
    if (logFileName.compare("") != 0) {
        _logFile = fopen(logFileName.c_str(), WRITE);
        if (!_logFile) {
            string  _lastError = "Can't open file (" + logFileName + ") for writing: "
                    + strerror(errno);
            if (allowMultipleExceptions) {
                ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
            } else {
                throw AdbException(_lastError);
            }
        }
    } else {
        _logFile = NULL;
    }
}

LogFile::~LogFile() {
    if (_logFile) {
        fclose (_logFile);
    }
}

void LogFile::appendLogFile(string str) {
    if (_logFile) {
        fprintf(_logFile, "%s", str.c_str());
    }
}
