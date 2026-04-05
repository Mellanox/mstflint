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

#include "psid_utils.h"
#include "mlxfwops_com.h"
#include <cstdio>
#include <cstdlib>

namespace psid_utils
{

constexpr size_t PSID_MAJOR_MINOR_LEN = 13;
constexpr size_t PSID_HEADER_LEN = 5;
constexpr size_t PSID_MINOR_LEN = 2;
constexpr size_t PSID_MAJOR_LEN = 6;
constexpr size_t PSID_MINOR_OFFSET = PSID_HEADER_LEN;
constexpr size_t PSID_MAJOR_OFFSET = PSID_HEADER_LEN + PSID_MINOR_LEN;

static_assert(PSID_MAX_LEN == PSID_LEN, "psid_utils::PSID_MAX_LEN must match mlxfwops_com.h PSID_LEN");

static const char* const ALLOWED_HEADERS[] = {"MT_00", "NVD00"};
static const size_t ALLOWED_HEADERS_COUNT = sizeof(ALLOWED_HEADERS) / sizeof(ALLOWED_HEADERS[0]);

static bool isFwCompsDebugEnabled()
{
    static const bool enabled = (getenv("FW_COMPS_DEBUG") != nullptr);
    return enabled;
}

#define PSID_DBG(fmt, ...)                                          \
    do                                                              \
    {                                                               \
        if (isFwCompsDebugEnabled())                                \
        {                                                           \
            printf("psid_utils:%s: " fmt, __func__, ##__VA_ARGS__); \
            fflush(stdout);                                         \
        }                                                           \
    } while (0)

static bool hasAllowedHeader(const char* psid)
{
    if (psid == nullptr || strlen(psid) < PSID_HEADER_LEN)
    {
        return false;
    }
    for (size_t i = 0; i < ALLOWED_HEADERS_COUNT; ++i)
    {
        if (strncmp(psid, ALLOWED_HEADERS[i], PSID_HEADER_LEN) == 0)
        {
            return true;
        }
    }
    return false;
}

static bool isPsidMajorMinorFormat(const char* psid)
{
    if (psid == nullptr)
    {
        return false;
    }
    size_t len = strlen(psid);
    if (len != PSID_MAJOR_MINOR_LEN)
    {
        return false;
    }
    return hasAllowedHeader(psid);
}

static std::string getHeader(const char* psid)
{
    if (psid == nullptr || strlen(psid) < PSID_HEADER_LEN)
    {
        return "";
    }
    return std::string(psid, PSID_HEADER_LEN);
}

static std::string getMajor(const char* psid)
{
    if (psid == nullptr || strlen(psid) < PSID_MAJOR_OFFSET + PSID_MAJOR_LEN)
    {
        return "";
    }
    return std::string(psid + PSID_MAJOR_OFFSET, PSID_MAJOR_LEN);
}

static bool isMinorReserved(const std::string& minor)
{
    if (minor.empty())
    {
        return false;
    }
    char first = minor[0];
    return (first == 'X' || first == 'Y' || first == 'Z');
}

PsidValidator::PsidValidator(const char* devicePsid, const char* imagePsid, const MinorPsidLockStatus& lockStatus) :
    _lockStatus(lockStatus)
{
    if (devicePsid != nullptr)
    {
        strncpy(_devicePsid, devicePsid, PSID_MAX_LEN);
    }
    else
    {
        _devicePsid[0] = '\0';
    }
    _devicePsid[PSID_MAX_LEN] = '\0';

    if (imagePsid != nullptr)
    {
        strncpy(_imagePsid, imagePsid, PSID_MAX_LEN);
    }
    else
    {
        _imagePsid[0] = '\0';
    }
    _imagePsid[PSID_MAX_LEN] = '\0';
}

std::string PsidValidator::getMinor(const char* psid)
{
    if (psid == nullptr || strlen(psid) < PSID_MINOR_OFFSET + PSID_MINOR_LEN)
    {
        return "";
    }
    return std::string(psid + PSID_MINOR_OFFSET, PSID_MINOR_LEN);
}

PsidCompatibilityStatus PsidValidator::checkCompatibility() const
{
    bool exactMatch = (strncmp(_devicePsid, _imagePsid, PSID_MAX_LEN) == 0);
    PSID_DBG("dev=%s img=%s supported=%d locked=%d lockedPsid=%s exact=%d\n", _devicePsid, _imagePsid,
             _lockStatus.featureSupported ? 1 : 0, _lockStatus.isLocked ? 1 : 0,
             _lockStatus.lockedPsid[0] ? _lockStatus.lockedPsid : "<none>", exactMatch ? 1 : 0);

    if (!_lockStatus.featureSupported)
    {
        PSID_DBG("feature not supported -> %s\n", exactMatch ? "ALLOWED" : "BLOCKED_PSID_MISMATCH");
        return exactMatch ? PsidCompatibilityStatus::ALLOWED : PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH;
    }

    bool deviceSplittable = isPsidMajorMinorFormat(_devicePsid);
    bool imageSplittable = isPsidMajorMinorFormat(_imagePsid);

    if (!deviceSplittable || !imageSplittable)
    {
        PSID_DBG("not splittable dev=%d img=%d -> %s\n", deviceSplittable ? 1 : 0, imageSplittable ? 1 : 0,
                 exactMatch ? "ALLOWED" : "BLOCKED_PSID_MISMATCH");
        return exactMatch ? PsidCompatibilityStatus::ALLOWED : PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH;
    }

    std::string deviceHeader = getHeader(_devicePsid);
    std::string imageHeader = getHeader(_imagePsid);
    std::string deviceMajor = getMajor(_devicePsid);
    std::string imageMajor = getMajor(_imagePsid);
    std::string imageMinor = getMinor(_imagePsid);
    PSID_DBG("parsed dev(%s/%s) img(%s/%s/%s)\n", deviceHeader.c_str(), deviceMajor.c_str(), imageHeader.c_str(),
             imageMajor.c_str(), imageMinor.c_str());

    if (deviceHeader != imageHeader)
    {
        PSID_DBG("BLOCKED_HEADER_MISMATCH %s vs %s\n", deviceHeader.c_str(), imageHeader.c_str());
        return PsidCompatibilityStatus::BLOCKED_HEADER_MISMATCH;
    }

    if (deviceMajor != imageMajor)
    {
        PSID_DBG("BLOCKED_MAJOR_MISMATCH %s vs %s\n", deviceMajor.c_str(), imageMajor.c_str());
        return PsidCompatibilityStatus::BLOCKED_MAJOR_MISMATCH;
    }

    if (isMinorReserved(imageMinor))
    {
        PSID_DBG("BLOCKED_MINOR_RESERVED minor=%s\n", imageMinor.c_str());
        return PsidCompatibilityStatus::BLOCKED_MINOR_RESERVED;
    }

    if (_lockStatus.isLocked)
    {
        if (strncmp(_imagePsid, _lockStatus.lockedPsid, PSID_MAX_LEN) != 0)
        {
            PSID_DBG("BLOCKED_MINOR_LOCKED lockedPsid=%s\n", _lockStatus.lockedPsid);
            return PsidCompatibilityStatus::BLOCKED_MINOR_LOCKED;
        }
    }

    PSID_DBG("ALLOWED\n");
    return PsidCompatibilityStatus::ALLOWED;
}

std::string PsidValidator::statusToString(PsidCompatibilityStatus compatibilityStatus) const
{
    switch (compatibilityStatus)
    {
        case PsidCompatibilityStatus::ALLOWED:
            return "";

        case PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH:
            return std::string("PSID mismatch. Device PSID (") + _devicePsid + ") differs from image PSID (" +
                   _imagePsid + ").";

        case PsidCompatibilityStatus::BLOCKED_HEADER_MISMATCH:
            return std::string("PSID header mismatch. Device header (") + getHeader(_devicePsid) +
                   ") differs from image header (" + getHeader(_imagePsid) + "). Cannot change PSID across headers.";

        case PsidCompatibilityStatus::BLOCKED_MAJOR_MISMATCH:
            return std::string("PSID major mismatch. Device major (") + getMajor(_devicePsid) +
                   ") differs from image major (" + getMajor(_imagePsid) + "). Only minor PSID changes are allowed.";

        case PsidCompatibilityStatus::BLOCKED_MINOR_RESERVED:
            return std::string("Image minor PSID (") + getMinor(_imagePsid) +
                   ") is reserved (starts with X, Y, or Z). FW update to reserved minor PSIDs is not allowed.";

        case PsidCompatibilityStatus::BLOCKED_MINOR_LOCKED:
            return std::string("Minor PSID is locked. Image PSID (") + _imagePsid +
                   ") does not match the locked PSID (" + _lockStatus.lockedPsid + ").";
    }
    return "Unknown PSID validation error.";
}

} // namespace psid_utils
