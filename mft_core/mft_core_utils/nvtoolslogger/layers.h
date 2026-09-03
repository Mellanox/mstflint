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

#ifndef NVTOOLSLOGGER_LAYERS_H
#define NVTOOLSLOGGER_LAYERS_H

/* C-compatible layer definitions (usable from .c and .cpp).
 * MFT_LAYER_COUNT is implicitly the number of real layers since it is the
 * last enumerator. */

enum mft_layer
{
    // Always-enabled meta layer for the logger's own output (e.g. the per-session
    // startup banner). Kept first so it has a stable home as tool layers are added.
    MFT_LAYER_LOGGER = 0,
    MFT_LAYER_MTCR,
    MFT_LAYER_REG_ACCESS,
    MFT_LAYER_FLINT,
    MFT_LAYER_MLXCONFIG,
    MFT_LAYER_MLXLINK,
    MFT_LAYER_MLXREG,
    MFT_LAYER_MFT_CORE,
    MFT_LAYER_MLXFWOPS,
    MFT_LAYER_MST_TOOL,
    MFT_LAYER_EFUSE,
    MFT_LAYER_COMMON,
    MFT_LAYER_HCA_CAPS,

    MFT_LAYER_COUNT
};

#ifdef __cplusplus

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

namespace nvtoolslogger
{

enum class Layer
{
    LOGGER = MFT_LAYER_LOGGER,
    MTCR = MFT_LAYER_MTCR,
    REG_ACCESS = MFT_LAYER_REG_ACCESS,
    FLINT = MFT_LAYER_FLINT,
    MLXCONFIG = MFT_LAYER_MLXCONFIG,
    MLXLINK = MFT_LAYER_MLXLINK,
    MLXREG = MFT_LAYER_MLXREG,
    MFT_CORE = MFT_LAYER_MFT_CORE,
    MLXFWOPS = MFT_LAYER_MLXFWOPS,
    MST_TOOL = MFT_LAYER_MST_TOOL,
    EFUSE = MFT_LAYER_EFUSE,
    COMMON = MFT_LAYER_COMMON,
    HCA_CAPS = MFT_LAYER_HCA_CAPS,
    ALL = MFT_LAYER_COUNT
};

struct LayerEntry
{
    Layer layer;
    const char* name;
};

inline const std::vector<LayerEntry>& getLayerTable()
{
    static const std::vector<LayerEntry> table = {
      {Layer::LOGGER, "logger"},       {Layer::MTCR, "mtcr"},         {Layer::REG_ACCESS, "reg_access"},
      {Layer::FLINT, "flint"},         {Layer::MLXCONFIG, "mlxconfig"}, {Layer::MLXLINK, "mlxlink"},
      {Layer::MLXREG, "mlxreg"},       {Layer::MFT_CORE, "mft_core"}, {Layer::MLXFWOPS, "mlxfwops"},
      {Layer::MST_TOOL, "mst_tool"},   {Layer::EFUSE, "efuse"},       {Layer::COMMON, "common"},
      {Layer::HCA_CAPS, "hca_caps"},   {Layer::ALL, "all"},
    };
    return table;
}

inline const char* getLayerName(Layer layer)
{
    for (const auto& entry : getLayerTable())
    {
        if (entry.layer == layer)
        {
            return entry.name;
        }
    }
    return nullptr;
}

inline bool parseLayerName(const std::string& name, Layer& out)
{
    std::string lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
    for (const auto& entry : getLayerTable())
    {
        if (lower == entry.name)
        {
            out = entry.layer;
            return true;
        }
    }
    return false;
}

} // namespace nvtoolslogger

#endif /* __cplusplus */
#endif /* NVTOOLSLOGGER_LAYERS_H */
