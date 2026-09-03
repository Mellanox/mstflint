/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include "nvtoolslogger/layers.h"
#include "nvtoolslogger/log_config_defs.h"

/*
 * Compiler intrinsics used to auto-capture call-site information when the
 * log()/logf() default arguments are taken. Evaluated at the call site
 * (not at the function definition), so log("msg") records the caller's
 * file/line/function, not NvToolsLogger.cpp's. GCC and Clang both provide them.
 */
#define MFT_LOG_DEFAULT_FILE __builtin_FILE()
#define MFT_LOG_DEFAULT_LINE __builtin_LINE()
#define MFT_LOG_DEFAULT_FUNC __builtin_FUNCTION()

namespace nvtoolslogger
{

/*
 * NvToolsLogger - process-wide singleton, public C++ entry point.
 *
 * NOT thread safe: the underlying spdlog sinks are the lock-free _st variants,
 * chosen so an enabled layer costs a level compare rather than a mutex. Call
 * the MFT_LOG_* macros from a single thread per process.
 */
class NvToolsLogger
{
public:
    static NvToolsLogger& getInstance();

    /* Plain message log. file/line/func default to the call site via
       compiler builtins, so `L.log(layer, sev, "msg")` works without
       repeating __FILE__/__LINE__/__func__. The MFT_LOG_* macros below
       are functionally equivalent. */
    void log(Layer layer,
             Severity severity,
             const char* message,
             const char* file = MFT_LOG_DEFAULT_FILE,
             int line = MFT_LOG_DEFAULT_LINE,
             const char* func = MFT_LOG_DEFAULT_FUNC);

    /* Per-severity convenience overloads. Same auto-capture as log():
           L.info(Layer::MTCR, "msg");
       records the caller's file/line/function on GCC/Clang. */
    void debug(Layer layer,
               const char* message,
               const char* file = MFT_LOG_DEFAULT_FILE,
               int line = MFT_LOG_DEFAULT_LINE,
               const char* func = MFT_LOG_DEFAULT_FUNC);

    void info(Layer layer,
              const char* message,
              const char* file = MFT_LOG_DEFAULT_FILE,
              int line = MFT_LOG_DEFAULT_LINE,
              const char* func = MFT_LOG_DEFAULT_FUNC);

    void warning(Layer layer,
                 const char* message,
                 const char* file = MFT_LOG_DEFAULT_FILE,
                 int line = MFT_LOG_DEFAULT_LINE,
                 const char* func = MFT_LOG_DEFAULT_FUNC);

    void error(Layer layer,
               const char* message,
               const char* file = MFT_LOG_DEFAULT_FILE,
               int line = MFT_LOG_DEFAULT_LINE,
               const char* func = MFT_LOG_DEFAULT_FUNC);

    void fatal(Layer layer,
               const char* message,
               const char* file = MFT_LOG_DEFAULT_FILE,
               int line = MFT_LOG_DEFAULT_LINE,
               const char* func = MFT_LOG_DEFAULT_FUNC);

    /* printf-style log; up to ~4 KiB per message. */
    void logf(Layer layer, Severity severity, const char* file, int line, const char* func, const char* fmt, ...)
      __attribute__((format(printf, 7, 8)));

private:
    NvToolsLogger();
    ~NvToolsLogger();
    NvToolsLogger(const NvToolsLogger&) = delete;
    NvToolsLogger& operator=(const NvToolsLogger&) = delete;

    void initialize();
    void destroy();

    struct Impl;
    Impl* _impl;
};

} // namespace nvtoolslogger

/* ── Plain message macros: MFT_LOG_<SEVERITY>(layer, msg) ── */

#define MFT_LOG_DEBUG(layer, msg)               \
    ::nvtoolslogger::NvToolsLogger::getInstance().log( \
      (layer), ::nvtoolslogger::Severity::Debug, (msg), __FILE__, __LINE__, __func__)

#define MFT_LOG_INFO(layer, msg)                \
    ::nvtoolslogger::NvToolsLogger::getInstance().log( \
      (layer), ::nvtoolslogger::Severity::Info, (msg), __FILE__, __LINE__, __func__)

#define MFT_LOG_WARNING(layer, msg)             \
    ::nvtoolslogger::NvToolsLogger::getInstance().log( \
      (layer), ::nvtoolslogger::Severity::Warning, (msg), __FILE__, __LINE__, __func__)

#define MFT_LOG_ERROR(layer, msg)               \
    ::nvtoolslogger::NvToolsLogger::getInstance().log( \
      (layer), ::nvtoolslogger::Severity::Error, (msg), __FILE__, __LINE__, __func__)

#define MFT_LOG_FATAL(layer, msg)               \
    ::nvtoolslogger::NvToolsLogger::getInstance().log( \
      (layer), ::nvtoolslogger::Severity::Fatal, (msg), __FILE__, __LINE__, __func__)

/* ── Format string macros: MFT_LOG_<SEVERITY>F(layer, fmt, ...) ── */

#define MFT_LOG_DEBUGF(layer, fmt, ...)          \
    ::nvtoolslogger::NvToolsLogger::getInstance().logf( \
      (layer), ::nvtoolslogger::Severity::Debug, __FILE__, __LINE__, __func__, (fmt), ##__VA_ARGS__)

#define MFT_LOG_INFOF(layer, fmt, ...)           \
    ::nvtoolslogger::NvToolsLogger::getInstance().logf( \
      (layer), ::nvtoolslogger::Severity::Info, __FILE__, __LINE__, __func__, (fmt), ##__VA_ARGS__)

#define MFT_LOG_WARNINGF(layer, fmt, ...)        \
    ::nvtoolslogger::NvToolsLogger::getInstance().logf( \
      (layer), ::nvtoolslogger::Severity::Warning, __FILE__, __LINE__, __func__, (fmt), ##__VA_ARGS__)

#define MFT_LOG_ERRORF(layer, fmt, ...)          \
    ::nvtoolslogger::NvToolsLogger::getInstance().logf( \
      (layer), ::nvtoolslogger::Severity::Error, __FILE__, __LINE__, __func__, (fmt), ##__VA_ARGS__)

#define MFT_LOG_FATALF(layer, fmt, ...)          \
    ::nvtoolslogger::NvToolsLogger::getInstance().logf( \
      (layer), ::nvtoolslogger::Severity::Fatal, __FILE__, __LINE__, __func__, (fmt), ##__VA_ARGS__)
