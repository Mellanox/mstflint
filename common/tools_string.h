/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
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
