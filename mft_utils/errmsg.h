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
 * errmsg.h - base class that provides the returning of error messages for classes that inherit it.
 *
 *  Created on: May 7, 2014
 *      Author: adrianc
 *
 */

#ifndef ERRMSG_H_
#define ERRMSG_H_

#include <map>
#include <string>

#include <stdarg.h>

/**
 *  ErrMsg Class Provides API for returning both error codes and error messages to the user app.
 */

class ErrMsg {
public:
    ErrMsg();
    ErrMsg(std::map<int, std::string>& errCodeMap);

    virtual ~ErrMsg()                { err_clear();}

    const char* err() const { return _err;}
    void updateErrCodes(std::map<int, std::string>& errCodeMap) {_errMap = errCodeMap; return;}

    const char* getFormatErr(const char *prefix, ...)
#ifdef __GNUC__
    __attribute__ ((format(printf, 2, 3)))
#endif
    ;

    void err_clear();

    int getLastErrCode() const {return _lastErrCode;}

    const char* err2Str(int errCode) const;

protected:
    char* vprint(const char *format, va_list args);

    int errmsg(const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format(printf, 2, 3)))
#endif
    ;

    int errmsg(int errCode, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format(printf, 3, 4)))
#endif
    ;

    int errmsg(int errCode);


    int errmsgConcatMsg(int errCode, const ErrMsg& errMsgObj, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format(printf, 4, 5)))
#endif
    ;

    int errmsgConcatMsg(const ErrMsg& errMsgObj, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format(printf, 3, 4)))
#endif
    ;

    int errmsgConcatMsg(int errCode, const ErrMsg& errMsgObj);

    int errmsgConcatMsg(const ErrMsg& errMsgObj);


    int errmsgConcatErrCd(int errCode, const ErrMsg& errMsgObj, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format(printf, 4, 5)))
#endif
    ;

    int errmsgConcatErrCd(int errCode, const ErrMsg& errMsgObj);

    int errmsgConcatErrCd(const ErrMsg& errMsgObj);

private:
    void errmsgConcatCom(const char *format, va_list args, const char *suffix);

    std::map<int, std::string> _errMap;
    char *_err;
    char *_formatErr;
    int _lastErrCode;
};

#endif /* ERRMSG_H_ */
