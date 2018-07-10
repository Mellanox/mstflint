/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 * errmsg.cpp - ErrMsg class implementation.
 *
 *  Created on: May 7, 2014
 *      Author: adrianc
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "errmsg.h"

enum {
    SUCCESS = 0,
    FAILURE = 1
};

ErrMsg::ErrMsg()
{
    _errMap[SUCCESS] = "SUCCESS";
    _errMap[FAILURE] = "FAILURE";
    _err = NULL;
    _formatErr = NULL;
    _lastErrCode = SUCCESS;
}

ErrMsg::ErrMsg(std::map<int, std::string>& errCodeMap)
{
    _errMap = errCodeMap;
    _err = NULL;
    _formatErr = NULL;
    _lastErrCode = SUCCESS;
}

const char* ErrMsg::getFormatErr(const char *prefix, ...)
{
    va_list args;
    char *prevFormatErr = _formatErr;
    va_start(args, prefix);
    char *preStr = vprint(prefix, args);
    int formatErrSz = strlen(_err) + strlen(preStr) + 10;
    _formatErr = new char[formatErrSz];
    snprintf(_formatErr, formatErrSz, "-E- %s. %s", preStr, _err);
    va_end(args);
    delete[] prevFormatErr;
    delete[] preStr;
    return _formatErr;
}

const char* ErrMsg::err2Str(int errCode) const
{
    std::map<int, std::string>::const_iterator it;
    if ( (it = _errMap.find(errCode)) == _errMap.end()) {
        return "Unknown Error Code";
    }
    return it->second.c_str();
}

char* ErrMsg::vprint(const char *format, va_list args)
{
    const int INIT_VAL = 1024;
    int max_str, max_buf = INIT_VAL;
    char      *out_buf;

    while (1) {
        out_buf = new char[max_buf];
        max_str = max_buf - 1;

        if (vsnprintf(out_buf, max_str, format, args) < max_str) {
            return out_buf;
        }
        delete [] out_buf;
        max_buf *= 2;
    }
}

int ErrMsg::errmsg(const char *format, ...)
{
    va_list args;

    char *prev_err = _err;

    va_start(args, format);
    _err = vprint(format, args);
    va_end(args);

    delete[] prev_err;
    _lastErrCode = FAILURE;
    return FAILURE;
}

int ErrMsg::errmsg(int errCode, const char *format, ...)
{
    va_list args;
    char *prev_err = _err;

    va_start(args, format);
    _err = vprint(format, args);
    va_end(args);

    delete[] prev_err;
    _lastErrCode = errCode;
    return errCode;
}

int ErrMsg::errmsg(int errCode)
{
    char *prevErr = _err;
    int errSz = strlen(err2Str(errCode)) + 1;
    char *newError = new char[errSz];
    snprintf(newError, errSz, "%s", err2Str(errCode));
    _err = newError;
    delete[] prevErr;
    _lastErrCode = errCode;
    return errCode;

}
void ErrMsg::errmsgConcatCom(const char *format, va_list args, const char *suffix)
{
    char *prevErr = _err;
    char *currError = vprint(format, args);
    int errSz = strlen(currError) + strlen(suffix) + 10;
    char *newError = new char[errSz];
    if (strlen(currError) == 0) {
        snprintf(newError, errSz, "%s", suffix);
    } else {
        if (strlen(suffix) == 0) {
            snprintf(newError, errSz, "%s", currError);
        } else {
            snprintf(newError, errSz, "%s. %s", currError, suffix);
        }
    }
    _err = newError;

    delete[] prevErr;
    delete[] currError;
}

int ErrMsg::errmsgConcatMsg(int errCode, const ErrMsg& errMsgObj, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    errmsgConcatCom(format, args, errMsgObj.err());
    va_end(args);
    _lastErrCode = errCode;
    return errCode;
}

int ErrMsg::errmsgConcatMsg(const ErrMsg& errMsgObj, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    errmsgConcatCom(format, args, errMsgObj.err());
    va_end(args);
    _lastErrCode = FAILURE;
    return FAILURE;
}

int ErrMsg::errmsgConcatMsg(int errCode, const ErrMsg& errMsgObj)
{
    return errmsg(errCode, "%s", errMsgObj.err());
}

int ErrMsg::errmsgConcatMsg(const ErrMsg& errMsgObj)
{
    return errmsg("%s", errMsgObj.err());
}

int ErrMsg::errmsgConcatErrCd(int errCode, const ErrMsg& errMsgObj, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    errMsgObj.getLastErrCode();
    errmsgConcatCom(format, args, errMsgObj.err2Str(errMsgObj.getLastErrCode()));
    va_end(args);
    _lastErrCode = errCode;
    return errCode;
}

int ErrMsg::errmsgConcatErrCd(int errCode, const ErrMsg& errMsgObj)
{
    return errmsg(errCode, "%s", errMsgObj.err2Str(errMsgObj.getLastErrCode()));
}

int ErrMsg::errmsgConcatErrCd(const ErrMsg& errMsgObj)
{
    return errmsg("%s", errMsgObj.err2Str(errMsgObj.getLastErrCode()));
}

void ErrMsg::err_clear()
{
    delete [] _err;
    delete [] _formatErr;
    _err = NULL;
    _formatErr = NULL;
}


