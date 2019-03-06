
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
void AdbExpr::Error(char *message)
{
    throw AdbException(string("Expression evaluation error: ") + message);
}
