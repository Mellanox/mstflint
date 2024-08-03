/*
 * Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#if __cplusplus
#include <chrono>
#include <thread>
#else
#include <time.h>
#include <stdint.h>
#endif

#if __cplusplus
namespace nbu
{
namespace mft
{
namespace common
{
/**
 * @brief Pauses the execution of the current thread for at least the specified number of milliseconds.
 * @param msecs The number of milliseconds to sleep.
 *
 * The execution of the current thread is stopped until at least msecs milliseconds has
 # passed from now. Other threads continue their execution.
 */
inline void mft_msleep(uint32_t msecs)
{
    ::std::this_thread::sleep_for(std::chrono::milliseconds(msecs));
}

/**
 * @brief Pauses the execution of the current thread for at least the specified number of microseconds.
 * @param msecs The number of microseconds to sleep.
 *
 * The execution of the current thread is stopped until at least msecs microseconds has
 # passed from now. Other threads continue their execution.
 */
inline void mft_usleep(uint64_t usecs)
{
    ::std::this_thread::sleep_for(std::chrono::microseconds(usecs));
}

} // namespace common
} // namespace mft
} // namespace nbu

#define msleep(x) nbu::mft::common::mft_msleep(x)

#else // C {

/**
 * @brief Pauses the execution of the current thread for at least the specified number of milliseconds.
 * @param msecs The number of milliseconds for which to pause the execution.
 * @return 0 on success, -1 otherwise. If interrupted by a signal, `errno` is set to `EINTR`.
 *
 * The execution of the current thread is stopped until at least msecs milliseconds has passed from now.
 * Other threads continue their execution. There no support for Windows platforms.
 */
static inline int mft_msleep(uint32_t msecs)
{
    struct timespec req;
    req.tv_sec = msecs / 1000;
    req.tv_nsec = ((long int)msecs % 1000) * 1000000;
    return nanosleep(&req, NULL);
}

/**
 * @brief Pauses the execution of the current thread for at least the specified number of microseconds.
 * @param msecs The number of microseconds for which to pause the execution.
  * @return 0 on success, -1 otherwise. If interrupted by a signal, `errno` is set to `EINTR`.
 *
 * The execution of the current thread is stopped until at least msecs microseconds has passed from now.
 * Other threads continue their execution. There no support for Windows platforms.
 */
static inline int mft_usleep(uint64_t usecs)
{
    struct timespec req;
    req.tv_sec = usecs / 1000000;
    req.tv_nsec = ((long int)usecs % 1000000) * 1000;
    return nanosleep(&req, NULL);
}

#define msleep(x) mft_msleep(x)

#endif // } C
