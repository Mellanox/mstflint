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

/*
 * Pure C interface for the NVIDIA Tools Logger.
 */

#ifndef NVTOOLSLOGGER_C_H
#define NVTOOLSLOGGER_C_H

#include "nvtoolslogger/layers.h"
#include "nvtoolslogger/log_config_defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void mft_log(int layer, int severity, const char* file, int line, const char* func, const char* message);

    void mft_log_fmt(int layer, int severity, const char* file, int line, const char* func, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

/* ── Plain message macros ── */

#define MFT_LOG_C_DEBUG(layer, msg) mft_log(layer, MFT_SEV_DEBUG, __FILE__, __LINE__, __func__, msg)

#define MFT_LOG_C_INFO(layer, msg) mft_log(layer, MFT_SEV_INFO, __FILE__, __LINE__, __func__, msg)

#define MFT_LOG_C_WARNING(layer, msg) mft_log(layer, MFT_SEV_WARNING, __FILE__, __LINE__, __func__, msg)

#define MFT_LOG_C_ERROR(layer, msg) mft_log(layer, MFT_SEV_ERROR, __FILE__, __LINE__, __func__, msg)

#define MFT_LOG_C_FATAL(layer, msg) mft_log(layer, MFT_SEV_FATAL, __FILE__, __LINE__, __func__, msg)

/* ── Format string macros ── */

#define MFT_LOG_C_DEBUGF(layer, fmt, ...) \
    mft_log_fmt(layer, MFT_SEV_DEBUG, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define MFT_LOG_C_INFOF(layer, fmt, ...) \
    mft_log_fmt(layer, MFT_SEV_INFO, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define MFT_LOG_C_WARNINGF(layer, fmt, ...) \
    mft_log_fmt(layer, MFT_SEV_WARNING, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define MFT_LOG_C_ERRORF(layer, fmt, ...) \
    mft_log_fmt(layer, MFT_SEV_ERROR, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define MFT_LOG_C_FATALF(layer, fmt, ...) \
    mft_log_fmt(layer, MFT_SEV_FATAL, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#endif /* NVTOOLSLOGGER_C_H */
