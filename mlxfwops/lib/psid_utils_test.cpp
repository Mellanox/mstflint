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

#include "gtest/gtest.h"
#include "mlxfwops/lib/psid_utils.h"

using namespace psid_utils;

static MinorPsidLockStatus makeLockStatus(bool featureSupported, bool isLocked, const char* lockedPsid = "")
{
    MinorPsidLockStatus s;
    s.featureSupported = featureSupported;
    s.isLocked = isLocked;
    strncpy(s.lockedPsid, lockedPsid, PSID_MAX_LEN);
    s.lockedPsid[PSID_MAX_LEN] = '\0';
    return s;
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature NOT supported (old logic)
// ============================================================================

TEST(CheckPsidCompatibility, FeatureNotSupported_IdenticalPsids_Allowed)
{
    PsidValidator v("MT_0000000129", "MT_0000000129", makeLockStatus(false, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureNotSupported_DifferentPsids_Blocked)
{
    PsidValidator v("MT_0000000129", "MT_00AB000129", makeLockStatus(false, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH);
}

TEST(CheckPsidCompatibility, FeatureNotSupported_CompletelyDifferent_Blocked)
{
    PsidValidator v("MT_0000000129", "NVD0000001644", makeLockStatus(false, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH);
}

TEST(CheckPsidCompatibility, FeatureNotSupported_IgnoresLockState_ExactMatchAllowed)
{
    PsidValidator v("MT_0000000129", "MT_0000000129", makeLockStatus(false, true, "MT_00AB000129"));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureNotSupported_IgnoresLockState_MismatchBlocked)
{
    PsidValidator v("MT_0000000129", "MT_00AB000129", makeLockStatus(false, true, "MT_00AB000129"));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH);
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature supported, identical PSIDs
// ============================================================================

TEST(CheckPsidCompatibility, FeatureSupported_IdenticalPsids_Allowed)
{
    PsidValidator v("MT_0000000129", "MT_0000000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureSupported_IdenticalPsids_Locked_Allowed)
{
    PsidValidator v("MT_0000000129", "MT_0000000129", makeLockStatus(true, true, "MT_0000000129"));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature supported, different minor, not locked
// ============================================================================

TEST(CheckPsidCompatibility, FeatureSupported_DifferentMinor_NotLocked_Allowed)
{
    PsidValidator v("MT_0000000129", "MT_00AB000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureSupported_GenericToCustomized_Allowed)
{
    PsidValidator v("MT_0000000129", "MT_0001000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureSupported_CustomizedToGeneric_Allowed)
{
    PsidValidator v("MT_0001000129", "MT_0000000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureSupported_CustomizedToCustomized_Allowed)
{
    PsidValidator v("MT_0001000129", "MT_0002000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature supported, different minor, locked
// ============================================================================

TEST(CheckPsidCompatibility, FeatureSupported_DifferentMinor_LockedToImage_Allowed)
{
    PsidValidator v("MT_0000000129", "MT_00AB000129", makeLockStatus(true, true, "MT_00AB000129"));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureSupported_DifferentMinor_LockedToDifferent_Blocked)
{
    PsidValidator v("MT_0000000129", "MT_00AB000129", makeLockStatus(true, true, "MT_00CD000129"));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MINOR_LOCKED);
}

TEST(CheckPsidCompatibility, FeatureSupported_SameMinor_LockedToDifferent_Blocked)
{
    PsidValidator v("MT_0001000129", "MT_0001000129", makeLockStatus(true, true, "MT_00AB000129"));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MINOR_LOCKED);
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature supported, header mismatch
// ============================================================================

TEST(CheckPsidCompatibility, FeatureSupported_DifferentHeader_Blocked)
{
    PsidValidator v("MT_0000000129", "NVD0000000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_HEADER_MISMATCH);
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature supported, major mismatch
// ============================================================================

TEST(CheckPsidCompatibility, FeatureSupported_DifferentMajor_Blocked)
{
    PsidValidator v("MT_0000000129", "MT_0000000999", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MAJOR_MISMATCH);
}

TEST(CheckPsidCompatibility, FeatureSupported_DifferentMajorAndMinor_Blocked)
{
    PsidValidator v("MT_0000000129", "MT_00AB000999", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MAJOR_MISMATCH);
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature supported, reserved minor
// ============================================================================

TEST(CheckPsidCompatibility, FeatureSupported_ReservedMinorX0_Blocked)
{
    PsidValidator v("MT_0000000129", "MT_00X0000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MINOR_RESERVED);
}

TEST(CheckPsidCompatibility, FeatureSupported_ReservedMinorY5_Blocked)
{
    PsidValidator v("MT_0000000129", "MT_00Y5000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MINOR_RESERVED);
}

TEST(CheckPsidCompatibility, FeatureSupported_ReservedMinorZZ_Blocked)
{
    PsidValidator v("MT_0000000129", "MT_00ZZ000129", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MINOR_RESERVED);
}

// ============================================================================
// PsidValidator::checkCompatibility - Feature supported but PSID doesn't support split
// ============================================================================

TEST(CheckPsidCompatibility, FeatureSupported_NonSplittablePsid_IdenticalAllowed)
{
    PsidValidator v("OMN0000000006", "OMN0000000006", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, FeatureSupported_NonSplittablePsid_DifferentBlocked)
{
    PsidValidator v("OMN0000000006", "OMN0000000007", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH);
}

// ============================================================================
// PsidValidator::checkCompatibility - NVD00 header variations
// ============================================================================

TEST(CheckPsidCompatibility, NVD00_DifferentMinor_NotLocked_Allowed)
{
    PsidValidator v("NVD0000001644", "NVD00AB001644", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, NVD00_DifferentMajor_Blocked)
{
    PsidValidator v("NVD0000001644", "NVD0000009999", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_MAJOR_MISMATCH);
}

TEST(CheckPsidCompatibility, NVD00_LockedToCorrect_Allowed)
{
    PsidValidator v("NVD0000001644", "NVD00AB001644", makeLockStatus(true, true, "NVD00AB001644"));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

// ============================================================================
// PsidValidator::checkCompatibility - Edge cases
// ============================================================================

TEST(CheckPsidCompatibility, EmptyPsids_FeatureNotSupported_Allowed)
{
    PsidValidator v("", "", makeLockStatus(false, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::ALLOWED);
}

TEST(CheckPsidCompatibility, EmptyDevicePsid_FeatureNotSupported_Mismatch)
{
    PsidValidator v("", "MT_0000000129", makeLockStatus(false, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH);
}

TEST(CheckPsidCompatibility, DeviceSupportsButImageDoesNot_Blocked)
{
    PsidValidator v("MT_0000000129", "SHORTPSID", makeLockStatus(true, false));
    EXPECT_EQ(v.checkCompatibility(), PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH);
}

// ============================================================================
// PsidValidator::statusToString
// ============================================================================

TEST(PsidCompatibilityStatusToString, AllowedReturnsEmpty)
{
    PsidValidator v("MT_0000000129", "MT_0000000129", makeLockStatus(false, false));
    std::string msg = v.statusToString(PsidCompatibilityStatus::ALLOWED);
    EXPECT_TRUE(msg.empty());
}

TEST(PsidCompatibilityStatusToString, ExactMismatchContainsBothPsids)
{
    PsidValidator v("MT_0000000129", "NVD0000001644", makeLockStatus(false, false));
    std::string msg = v.statusToString(PsidCompatibilityStatus::BLOCKED_PSID_MISMATCH);
    EXPECT_NE(msg.find("MT_0000000129"), std::string::npos);
    EXPECT_NE(msg.find("NVD0000001644"), std::string::npos);
}

TEST(PsidCompatibilityStatusToString, HeaderMismatchContainsHeaders)
{
    PsidValidator v("MT_0000000129", "NVD0000000129", makeLockStatus(false, false));
    std::string msg = v.statusToString(PsidCompatibilityStatus::BLOCKED_HEADER_MISMATCH);
    EXPECT_NE(msg.find("MT_00"), std::string::npos);
    EXPECT_NE(msg.find("NVD00"), std::string::npos);
}

TEST(PsidCompatibilityStatusToString, MajorMismatchContainsMajors)
{
    PsidValidator v("MT_0000000129", "MT_0000000999", makeLockStatus(false, false));
    std::string msg = v.statusToString(PsidCompatibilityStatus::BLOCKED_MAJOR_MISMATCH);
    EXPECT_NE(msg.find("000129"), std::string::npos);
    EXPECT_NE(msg.find("000999"), std::string::npos);
}

TEST(PsidCompatibilityStatusToString, ReservedMinorContainsMinor)
{
    PsidValidator v("MT_0000000129", "MT_00X0000129", makeLockStatus(false, false));
    std::string msg = v.statusToString(PsidCompatibilityStatus::BLOCKED_MINOR_RESERVED);
    EXPECT_NE(msg.find("X0"), std::string::npos);
    EXPECT_NE(msg.find("reserved"), std::string::npos);
}

TEST(PsidCompatibilityStatusToString, LockedMinorContainsLockedPsid)
{
    PsidValidator v("MT_0000000129", "MT_00AB000129", makeLockStatus(true, true, "MT_00CD000129"));
    std::string msg = v.statusToString(PsidCompatibilityStatus::BLOCKED_MINOR_LOCKED);
    EXPECT_NE(msg.find("MT_00AB000129"), std::string::npos);
    EXPECT_NE(msg.find("MT_00CD000129"), std::string::npos);
    EXPECT_NE(msg.find("locked"), std::string::npos);
}
