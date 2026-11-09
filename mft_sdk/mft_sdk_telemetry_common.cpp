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

#include <cstring>

#include "mft_sdk/mft_sdk_telemetry_common.hpp"

std::string TelemetryContextView::getPort() const
{
    if (!has(offsetof(MstTelemetryContext_t, label_port) + sizeof(_context.label_port)))
    {
        return std::string();
    }
    return std::string(_context.label_port, strnlen(_context.label_port, MST_TELEMETRY_PORT_MAX_LENGTH));
}

MstTelemetryPortType TelemetryContextView::getPortType() const
{
    if (!has(offsetof(MstTelemetryContext_t, port_type) + sizeof(_context.port_type)))
    {
        return MST_TELEMETRY_PORT_TYPE_NETWORK;
    }
    return _context.port_type == MST_TELEMETRY_PORT_TYPE_PCIE ? MST_TELEMETRY_PORT_TYPE_PCIE :
                                                                MST_TELEMETRY_PORT_TYPE_NETWORK;
}

PcieDpn TelemetryContextView::getDpn() const
{
    PcieDpn dpn;
    if (!has(offsetof(MstTelemetryContext_t, node) + sizeof(_context.node)) || !_context.has_dpn)
    {
        return dpn;
    }
    dpn.hasDpn = true;
    dpn.depth = _context.depth;
    dpn.pcieIndex = _context.pcie_index;
    dpn.node = _context.node;
    return dpn;
}

bool TelemetryContextView::hasConflictingPortSelection() const
{
    return !getPort().empty() && getPortType() == MST_TELEMETRY_PORT_TYPE_PCIE && getDpn().hasDpn;
}

const MstTelemetryContext& defaultTelemetryContext()
{
    static const MstTelemetryContext defaults = []
    {
        MstTelemetryContext c;
        MST_TELEMETRY_CONTEXT_INIT(&c);
        return c;
    }();
    return defaults;
}
