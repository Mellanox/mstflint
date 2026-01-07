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

#include <cstdarg>
#include <string>

namespace nbu
{
namespace mft
{
namespace common
{
static void string_appendv(std::string& out, const char* format, va_list args)
{
    static const int FIT_MOST_OF_THE_CASES = 1024;
    char buffer[FIT_MOST_OF_THE_CASES];
    size_t length = sizeof(buffer);

    ::std::va_list tmp_args;
    va_copy(tmp_args, args);
    // Coverity is raising a warning about the use of an uninitialized value tmp_args when calling vsnprintf.
    // However, tmp_args is actually initialized by va_copy as a copy of args.
    // See https://en.cppreference.com/w/cpp/utility/variadic/va_copy for reference.
    // coverity[uninit_use_in_call : FALSE]
    int bytes_written = ::std::vsnprintf(buffer, length, format, tmp_args);
    va_end(tmp_args);

    if (bytes_written >= 0 && static_cast<size_t>(bytes_written) < length)
    {
        out.append(buffer, bytes_written);
        return;
    }

    if (bytes_written < 0)
    {
        out.append("encoding error formatting string :");
        out.append(format);
        return;
    }

    // if we reached this point than "bytes_written" represents the number of characters
    // that would have been written if buffer had been sufficiently large, not counting
    // the terminating null character

    length = bytes_written + 1;

    char* rubber_buffer(new char[length]);
    va_copy(tmp_args, args);
    bytes_written = ::std::vsnprintf(rubber_buffer, length, format, tmp_args);
    va_end(tmp_args);

    if (bytes_written >= 0 && static_cast<size_t>(bytes_written) < length)
    {
        out.append(rubber_buffer, bytes_written);
        delete[] rubber_buffer;
        return;
    }

    if (bytes_written < 0)
    {
        out.append("encoding error formatting string");
        out.append(format);
        delete[] rubber_buffer;
        return;
    }

    delete[] rubber_buffer;
    return;
}

std::string string_format(const char* format, ...)
{
    ::std::va_list args;
    va_start(args, format);
    std::string out;
    string_appendv(out, format, args);
    va_end(args);
    return out;
}

} // namespace common
} // namespace mft
} // namespace nbu
