/*
 *
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 */

#include <stdlib.h>
#include "adb_condition.h"

#if __cplusplus >= 201402L
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif

AdbCondition::AdbCondition()
{
}

void AdbCondition::setCondition(std::string condition)
{
    this->condition = condition;
    if(condition != "")
    {
        splitConditionIntoVariables();
    }
}

void AdbCondition::splitConditionIntoVariables()
{
    static const regex EXP_PATTERN("(\\w+)\\s*==");
    match_results<string::const_iterator> match;
    string::const_iterator start = this->condition.begin();
    string::const_iterator end = this->condition.end();
    while(regex_search(start, end, match, EXP_PATTERN)){
        this->varsMap[match[0]] = CondVar();
        start = match[0].second;
    }
}

map<string, CondVar>& AdbCondition::getVarsMap()
{
    return this->varsMap;
}

