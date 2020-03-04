
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

#include <stdlib.h>
#include "adb_expr.h"
#include "adb_parser.h"

/**
 * Function: AdbExpr::AdbExpr
 **/
AdbExpr::AdbExpr() : _varsMap(0)
{

}

/**
 * Function: AdbExpr::~AdbExpr
 **/
AdbExpr::~AdbExpr()
{

}

/**
 * Function: AdbExpr::setVars
 **/
void AdbExpr::setVars(map<string, string> *varsMap)
{
    _varsMap = varsMap;
}

/**
 * Function: AdbExpr::statusStr
 **/
const char* AdbExpr::statusStr(int status)
{
    switch (status)
    {
    case Expr::ERR_RPAR_EXP: return "Right parentheses expected";

    case Expr::ERR_VALUE_EXP: return "Value expected";

    case Expr::ERR_BIN_EXP: return "Binary operation expected ";

    case Expr::ERR_DIV_ZERO: return "Divide zero attempt";

    case Expr::ERR_BAD_NUMBER: return "Bad constant syntax";

    case Expr::ERR_BAD_NAME: return "Variable Name not resolved";

    default:                    return "Unknown error";
    }
}

/**
 * Function: AdbExpr::ResolveName
 **/
int AdbExpr::ResolveName(char *name, u_int64_t *val)
{
    map<string, string>::iterator it = _varsMap->find(name);
    if (it == _varsMap->end()) {
        return ERR_BAD_NAME;
    }

    char *end;
    *val = strtoul(it->second.c_str(), &end, 0);
    if (*end != '\0') {
        return ERR_BAD_NUMBER;
    }

    return 0;
}

/**
 * Function: AdbExpr::Error
 **/
void AdbExpr::Error(const std::string& message)
{
    throw AdbException(string("Expression evaluation error: ") + message);
}
