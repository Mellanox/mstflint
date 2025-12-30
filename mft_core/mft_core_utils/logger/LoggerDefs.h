/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */
#pragma once

#define PRINT_LOGGER_ENV_VAR "MFT_PRINT_LOG"

enum class eLoggerSeverityLevel
{
    debug = 0,
    info,
    warning,
    error,
    fatal,
    severity_count,
};
