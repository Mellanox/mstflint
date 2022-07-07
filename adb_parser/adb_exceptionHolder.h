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
/*************************** ExceptionHolder ***************************/

#ifndef ADB_EXCEPTIONHOLDER_H
#define ADB_EXCEPTIONHOLDER_H

#include <string>
#include <map>
#include <vector>
#include <cstdarg>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

typedef vector<string> StringVector;
typedef map<string, StringVector> ExceptionsMap;

class ExceptionHolder
{
public:
    // METHODS
    static void insertNewException(const string exceptionType, string exceptionTxt);
    static ExceptionsMap getAdbExceptionsMap();
    static int getNumberOfExceptions();

public:
    // VARIABLES
    static ExceptionsMap adbExceptionMap;
    static const string FATAL_EXCEPTION;
    static const string ERROR_EXCEPTION;
    static const string WARN_EXCEPTION;
    static int exceptionCounter;
};

/*************************** AdbException ***************************/
class AdbException : public std::exception
{
public:
    // Methods
    AdbException();
    AdbException(const char* msg, ...) __attribute__((format(__printf__, 2, 3)));
    AdbException(string msg);
    virtual ~AdbException() throw();
    virtual const char* what() const throw();
    virtual string what_s() const;

private:
    string _msg;
};

/**
 * Function: ExceptionHolder::getNumberOfExceptions
 * This function return the number of exceptions found
 **/

/*int ExceptionHolder::getNumberOfExceptions() {
    return ExceptionHolder::exceptionCounter;
}*/

/**
 * Function: ExceptionHolder::getAdbExceptionsMap
 * This function return the adb exception map
 **/

/*ExceptionsMap ExceptionHolder::getAdbExceptionsMap() {
    return ExceptionHolder::adbExceptionMap;
}*/

/**
 * Function: ExceptionHolder::insertNewException
 * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 * Then it insert it to the adb exception map
 **/
/*void ExceptionHolder::insertNewException(const string exceptionType, string exceptionTxt) {
    ExceptionHolder::adbExceptionMap[exceptionType].push_back(exceptionTxt);
    ExceptionHolder::exceptionCounter += 1;
}*/

#endif
