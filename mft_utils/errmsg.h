/*
 *                 - Mellanox Confidential and Proprietary -
 *
 * Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 * Except as specifically permitted herein, no portion of the information,
 * including but not limited to object code and source code, may be reproduced,
 * modified, distributed, republished or otherwise exploited in any form or by
 * any means for any purpose without the prior written permission of Mellanox
 * Technologies Ltd. Use of software subject to the terms and conditions
 * detailed in the file "LICENSE.txt".
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

/**
 *  ErrMsg Class Provides API for returning both error codes and error messages to the user app.
 */

class ErrMsg {
public:
    ErrMsg();
    ErrMsg(std::map<int, std::string>& errCodeMap);

    ~ErrMsg()                { err_clear();}

    const char* err() const  { return _err;}
    void updateErrCodes(std::map<int, std::string>& errCodeMap) {_errMap = errCodeMap; return;}

    const char* getFormatErr(const char *prefix, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 2, 3)))
#endif
    ;

    void err_clear();

    int getLastErrCode() const {return _lastErrCode;}

    const char* err2Str(int errCode) const;

protected:
    char* vprint(const char *format, va_list args);

    int errmsg(const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 2, 3)))
#endif
    ;

    int errmsg(int errCode, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 3, 4)))
#endif
    ;

    int errmsg(int errCode);


    int errmsgConcatMsg(int errCode, const ErrMsg& errMsgObj, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 4, 5)))
#endif
    ;

    int errmsgConcatMsg(const ErrMsg& errMsgObj, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 3, 4)))
#endif
    ;

    int errmsgConcatMsg(int errCode, const ErrMsg& errMsgObj);

    int errmsgConcatMsg(const ErrMsg& errMsgObj);


    int errmsgConcatErrCd(int errCode, const ErrMsg& errMsgObj, const char *format, ...)
#ifdef __GNUC__
    __attribute__ ((format (printf, 4, 5)))
#endif
    ;

    int errmsgConcatErrCd(int errCode, const ErrMsg& errMsgObj);

    int errmsgConcatErrCd(const ErrMsg& errMsgObj);

private:
    void errmsgConcatCom(const char* format, va_list args, const char* suffix);

    std::map<int, std::string> _errMap;
    char*       _err;
    char*       _formatErr;
    int         _lastErrCode;
};

#endif /* ERRMSG_H_ */
