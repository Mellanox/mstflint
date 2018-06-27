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
 *
 * mlxcfg_expression.cpp
 *
 *  Created on: May 07, 2017
 *      Author: Ahmad Soboh
 */

#include <algorithm>

#include <muParser.h>
#include "mlxcfg_utils.h"
#include "mlxcfg_expression.h"

using namespace std;
using namespace mlxcfg;

void extractVars(const string& expression, vector<string>& vars)
{
    string var;
    for (unsigned int i = 0; i < expression.size(); i++) {
        if (expression[i] == '$') {
            var = "$";
            i++;
            while (i < expression.size() &&
                   (expression[i] == '_' ||
                    expression[i] == '.' ||
                    ('a' <= expression[i] && expression[i] <= 'z') ||
                    ('A' <= expression[i] && expression[i] <= 'Z') ||
                    ('0' <= expression[i] && expression[i] <= '9'))) {
                var += expression[i];
                i++;
            }
            vars.push_back(var);
        }
    }
    if (!var.empty()) {
        vars.push_back(var);
    }
}

void substituteVarsValues(const string& orgExpr,
                          const map<string, double>& var2ValMap, string& expr)
{
    string var = "";

    expr = "";
    for (unsigned int j = 0; j < orgExpr.size(); j++) {
        if (orgExpr[j] == '$') {
            var = "$";
            j++;
            while (j < orgExpr.size()
                   && (orgExpr[j] == '_' || orgExpr[j] == '.'
                       || ('a' <= orgExpr[j] && orgExpr[j] <= 'z')
                       || ('A' <= orgExpr[j] && orgExpr[j] <= 'Z')
                       || ('0' <= orgExpr[j] && orgExpr[j] <= '9'))) {
                var += orgExpr[j];
                j++;
            }
            map<string, double>::const_iterator it = var2ValMap.find(var);
            if (it == var2ValMap.end()) {
                expr += var; //no value for var, so append it to expr
            } else {
                stringstream ss;
                ss << ((u_int32_t)it->second);
                expr += ss.str();
            }
            if (j < orgExpr.size()) {
                expr += orgExpr[j];
            }
        } else {
            expr += orgExpr[j];
        }
    }
}

Expression::Expression(const string& expression) : _expression(expression)
{
    extractVars(expression, _vars);
}

void Expression::getVars(vector<string>& vars) const
{
    vars.insert(vars.begin(), _vars.begin(), _vars.end());
}

double Expression::getVarVal(const string& var) const
{
    map<string, double>::const_iterator it = _varsVal.find(var);
    if (it == _varsVal.end()) {
        throw MlxcfgException("Unknown variable: %s", var.c_str());
    }
    return it->second;
}

void Expression::setVarVal(const string& var, double val)
{
    if (find(_vars.begin(), _vars.end(), var) == _vars.end()) {
        throw MlxcfgException("Unknown variable: %s", var.c_str());
    }
    _varsVal[var] = val;
}

double Expression::evaluate()
{
    string expression;
    string varXName;
    mu::Parser p;

    substituteVarsValues(_expression, _varsVal, expression);

    //find the unknown variable value
    VECTOR_ITERATOR(string, _vars, it) {
        if (_varsVal.find(*it) == _varsVal.end()) {
            if (varXName.empty()) {
                varXName = *it;
            } else {
                throw MlxcfgException(
                          "Found More than one variable "
                          "with unknown value in the expression: %s",
                          _expression.c_str());
            }
        }
    }

    try {
        //currently lets support only one var with unknown val
        if (varXName.empty()) {
            p.SetExpr(expression);
            return p.Eval();
        } else {
            double x;
            const string varXTempName = "x";
            size_t pos = expression.find(varXName);
            if (pos == string::npos) {
                throw MlxcfgException("Unexpected error - "
                                      "The variable '%s' was not found in "
                                      "the expression '%s'",
                                      varXName.c_str(), expression.c_str());
            }
            expression.replace(pos,
                               varXName.length(),
                               varXTempName);
            p.DefineVar(varXTempName, &x);
            p.SetExpr(expression);
            double result = p.Eval();
            _varsVal[varXName] = x;
            return result;
        }
    } catch (mu::Parser::exception_type &e) {
        throw MlxcfgException("Failed to evaluate the expression(%s): %s\n"
                              " the original expression is: %s",
                              expression.c_str(),
                              e.GetMsg().c_str(),
                              _expression.c_str());
    }
}
