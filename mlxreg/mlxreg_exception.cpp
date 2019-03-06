/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

#include <cstdio>
#include <cstdarg>
#include "mlxreg_exception.h"
using namespace mlxreg;

/************************************
* Function: MlxRegException
************************************/
MlxRegException::MlxRegException(const char *fmt, ...)
{
    char tmp[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(tmp, fmt, args);
    va_end(args);
    _msg = tmp;
}

/************************************
* Function: MlxRegException
************************************/
MlxRegException::MlxRegException(const std::string& msg) :
    _msg(msg)
{
}

/************************************
* Function: ~MlxRegException
************************************/
MlxRegException::~MlxRegException() throw()
{

}

/************************************
* Function: what_s
************************************/
std::string MlxRegException::what_s() const
{
    return _msg;
}

/************************************
* Function: what
************************************/
const char* MlxRegException::what() const throw()
{
    return _msg.c_str();
}


