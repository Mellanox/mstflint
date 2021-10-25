/* 
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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
 */

/*************************** AdbException Implementation ***************************/

#include "adb_exceptionHolder.h"

ExceptionsMap ExceptionHolder::adbExceptionMap;
const string ExceptionHolder::FATAL_EXCEPTION = "FATAL";
const string ExceptionHolder::ERROR_EXCEPTION = "ERROR"; 
const string ExceptionHolder::WARN_EXCEPTION = "WARNING"; 
int ExceptionHolder::exceptionCounter = 0;

AdbException::AdbException() {
}

/**
 * Function: AdbException::AdbException
 **/
AdbException::AdbException(const char *fmt, ...) {
    char tmp[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(tmp, fmt, args);
    va_end(args);
    _msg = tmp;
}

/**
 * Function: AdbException::AdbException
 **/
AdbException::AdbException(string msg) :
    _msg(msg) {
}

/**
 * Function: AdbException::~AdbException
 **/
AdbException::~AdbException() throw () {
}

/**
 * Function: AdbException::what
 **/
const char* AdbException::what() const throw () {
    return _msg.c_str();
}

/**
 * Function: AdbException::what_s
 **/
string AdbException::what_s() const {
    return _msg;
}

int ExceptionHolder::getNumberOfExceptions() {
    return ExceptionHolder::exceptionCounter;
}

/**
 *  * Function: ExceptionHolder::getAdbExceptionsMap
 *   * This function return the adb exception map
 *    **/

ExceptionsMap ExceptionHolder::getAdbExceptionsMap() {
    return ExceptionHolder::adbExceptionMap;
}

/**
 *  * Function: ExceptionHolder::insertNewException
 *   * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 *    * Then it insert it to the adb exception map
 *     **/
void ExceptionHolder::insertNewException(const string exceptionType, string exceptionTxt) {
    ExceptionHolder::adbExceptionMap[exceptionType].push_back(exceptionTxt);
    ExceptionHolder::exceptionCounter += 1;
}
