/*
 * Copyright (c) 2024-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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

#ifndef PSID_UTILS_H
#define PSID_UTILS_H

#include <cstdint>
#include <cstring>
#include <string>

#ifdef __WIN__

#ifdef MLXFWOP_EXPORTS
#define MLXFWOP_API __declspec(dllexport)
#else
#define MLXFWOP_API __declspec(dllimport)
#endif

#else
#define MLXFWOP_API
#endif

namespace psid_utils
{

constexpr size_t PSID_MAX_LEN = 16;

enum class PsidCompatibilityStatus
{
    ALLOWED,
    BLOCKED_PSID_MISMATCH,
    BLOCKED_HEADER_MISMATCH,
    BLOCKED_MAJOR_MISMATCH,
    BLOCKED_MINOR_RESERVED,
    BLOCKED_MINOR_LOCKED,
};

struct MinorPsidLockStatus
{
    bool featureSupported = false;
    bool isLocked = false;
    char lockedPsid[PSID_MAX_LEN + 1] = {};
};

class MLXFWOP_API PsidValidator
{
public:
    PsidValidator(const char* devicePsid, const char* imagePsid, const MinorPsidLockStatus& lockStatus);

    PsidCompatibilityStatus checkCompatibility() const;
    std::string statusToString(PsidCompatibilityStatus status) const;

    static std::string getMinor(const char* psid);

private:
    char _devicePsid[PSID_MAX_LEN + 1];
    char _imagePsid[PSID_MAX_LEN + 1];
    MinorPsidLockStatus _lockStatus;
};

} // namespace psid_utils

#endif // PSID_UTILS_H
