/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#pragma once

#include <string>

namespace nbu
{
namespace mft
{
namespace common
{
/**
 * @brief Format a string using printf-style formatting.
 * @param format A C-style format string, similar to that used in printf.
 * @param ... Additional arguments to be formatted into the resulting string.
 *            These arguments should correspond to the format specifiers in the
 *            format string.
 * @return A std::string containing the formatted string.
 *
 * This function behaves similarly to sprintf but returns a std::string instead
 * of writing to a character array. It accepts a format string and additional
 * arguments which are formatted according to the format specifier in the format
 * string.
 *
 * Example usage:
 * @code
 * std::string formatted = string_format("Hello, %s! The answer to the Ultimate Question of Life, the Universe, and
 * Everything is %d.", "%Username%", 42); std::cout << formatted << std::endl;  // Output: Hello, %Username%! The answer
 * to the Ultimate Question of Life, the Universe, and Everything is 42.
 * @endcode
 */
::std::string string_format(const char* format, ...);

} // namespace common
} // namespace mft
} // namespace nbu
