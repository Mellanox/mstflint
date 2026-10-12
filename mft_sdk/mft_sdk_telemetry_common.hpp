/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 *  Version: $Id$
 *
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <mft_sdk/mft_sdk_telemetry_types.h>

// A specific PCIe link (depth/pcieIndex/node) to bind to under MST_TELEMETRY_PORT_TYPE_PCIE;
// hasDpn tells "no DPN requested" apart from the valid DPN 0/0/0.
struct PcieDpn
{
    bool hasDpn = false;
    uint32_t depth = 0;
    uint32_t pcieIndex = 0;
    uint32_t node = 0;

    bool operator==(const PcieDpn& other) const
    {
        return hasDpn == other.hasDpn && depth == other.depth && pcieIndex == other.pcieIndex && node == other.node;
    }
    bool operator!=(const PcieDpn& other) const { return !(*this == other); }
};

// Reads the port selection of a caller's MstTelemetryContext, which MstAmberContext also embeds as its
// base. Each field is read only if the caller's struct is large enough to contain it; a smaller (older)
// caller gets the defaults a zeroed field would give.
class TelemetryContextView
{
public:
    explicit TelemetryContextView(const MstTelemetryContext& context) : _context(context) {}

    std::string getPort() const;
    MstTelemetryPortType getPortType() const;
    PcieDpn getDpn() const;

    // Matches MlxlinkUi::validatePCIeParams(): rejects port + DPN together, not port + PCIe alone.
    bool hasConflictingPortSelection() const;

private:
    bool has(size_t memberEnd) const { return _context.size >= memberEnd; }

    const MstTelemetryContext& _context;
};

// The device-defaults context, initialized once and shared.
const MstTelemetryContext& defaultTelemetryContext();
