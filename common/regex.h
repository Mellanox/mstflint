/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */

#ifndef MSTFLINT_REGEX_H
#define MSTFLINT_REGEX_H

#include "config.h"

#ifdef USE_BOOST_REGEX
#include <boost/regex.hpp>
#else
#include <regex>
#endif

namespace mstflint
{
namespace common
{
namespace regex
{
#ifdef USE_BOOST_REGEX
using boost::regex;
using boost::match_results;
using boost::regex_search;
using boost::smatch;
using boost::regex_replace;
using boost::regex_match;
#else
using std::regex;
using std::match_results;
using std::regex_search;
using std::smatch;
using std::regex_replace;
using std::regex_match;
#endif

} // namespace regex
} // namespace common
} // namespace mstflint
#endif // MSTFLINT_REGEX_H
