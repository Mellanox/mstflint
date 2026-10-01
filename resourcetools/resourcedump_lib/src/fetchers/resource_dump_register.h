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
 *
 */

#ifndef RESOURCE_DUMP_REGISTER_H
#define RESOURCE_DUMP_REGISTER_H

#include "resource_dump_segments.h"

#include "tools_layouts/reg_access_hca_layouts.h"
#include "tools_layouts/reg_access_switch_layouts.h"

#include "reg_access/reg_access.h"

#include <cstdint>
#include <ostream>
#include <vector>

struct mfile_t;

namespace mft
{
namespace resource_dump
{
namespace fetchers
{
/*
 * Encapsulates a resource-dump register layout and the direct operations performed on it
 * (init / reset / send over reg-access / payload extraction). Concrete flavors select the
 * underlying register layout and wire register-id, allowing RegAccessResourceDumpFetcher to
 * stay agnostic of the device-specific register variant.
 */

/***** Note for developers: **********************************************************/
/* Currently, there are two types of used registers.                                 */
/* If there will be a need for more (which is discouraged),                          */
/* define a template mid level to avoid the boilerplate code of init/reset/getters.  */
/*************************************************************************************/
class ResourceDumpRegister
{
public:
    explicit ResourceDumpRegister(uint16_t reg_id) : _reg_id{reg_id} {}

    virtual ~ResourceDumpRegister() = default;

    // Populate the register for the first dump call of a (sub-)segment. The optional inline_dump /
    // mkey / size / address arguments configure memory-key (non-inline) mode; the defaults select
    // inline mode, which is what the plain inline fetcher uses.
    virtual void init(const reference_segment_data& params,
                      uint8_t seq_num,
                      uint16_t vhca,
                      bool inline_dump = true,
                      uint32_t mkey = 0,
                      uint32_t size = 0,
                      uint64_t address = 0) = 0;

    // Re-arm the register between consecutive more_dump iterations. Takes the same optional
    // memory-key configuration as init().
    virtual void reset(const reference_segment_data& params,
                       uint16_t vhca,
                       bool inline_dump = true,
                       uint32_t mkey = 0,
                       uint32_t size = 0,
                       uint64_t address = 0) = 0;

    // Issue the reg-access GET for this register variant.
    virtual reg_access_status_t send(mfile_t* mf) = 0;

    virtual bool more_dump() const = 0;

    virtual uint8_t seq_num() const = 0;

    // Actual size (in bytes) the device reports it has written. Used by the mkey
    // (non-inline) path to read the dumped buffer; 0 for variants that do not report it.
    virtual uint32_t reply_size() const { return 0; }

    // Write the inline payload returned by the device to the output stream.
    virtual void write_payload(std::ostream& os) const = 0;

protected:
    uint16_t _reg_id;
};

/*
 * Basic resource-dump variant shared by NIC (REG_ID_RES_DUMP) and Switch (REG_ID_MORD): the
 * switch MORD (v1) register has the exact same layout as the HCA RESOURCE_DUMP register. Uses
 * the fixed-size layout with an inline data array of NUM_INLINE_DATA_DWORDS dwords.
 */
class BasicResourceDumpRegister : public ResourceDumpRegister
{
public:
    explicit BasicResourceDumpRegister(uint16_t reg_id);

    void init(const reference_segment_data& params,
              uint8_t seq_num,
              uint16_t vhca,
              bool inline_dump = true,
              uint32_t mkey = 0,
              uint32_t size = 0,
              uint64_t address = 0) override;

    void reset(const reference_segment_data& params,
               uint16_t vhca,
               bool inline_dump = true,
               uint32_t mkey = 0,
               uint32_t size = 0,
               uint64_t address = 0) override;

    reg_access_status_t send(mfile_t* mf) override;

    bool more_dump() const override { return _layout.more_dump; }

    uint8_t seq_num() const override { return _layout.seq_num; }

    uint32_t reply_size() const override { return _layout.size; }

    void write_payload(std::ostream& os) const override;

private:
    reg_access_hca_resource_dump_ext _layout{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}};
};

/*
 * GPU variant (REG_ID_MORD_V2). Uses the switch mord_v2 layout, whose inline_data is a
 * caller-allocated buffer; the buffer is sized dynamically from the device's maximum
 * register size (mget_max_reg_size).
 */
class MordV2ResourceDumpRegister : public ResourceDumpRegister
{
public:
    explicit MordV2ResourceDumpRegister(mfile_t* mf);

    void init(const reference_segment_data& params,
              uint8_t seq_num,
              uint16_t vhca,
              bool inline_dump = true,
              uint32_t mkey = 0,
              uint32_t size = 0,
              uint64_t address = 0) override;

    void reset(const reference_segment_data& params,
               uint16_t vhca,
               bool inline_dump = true,
               uint32_t mkey = 0,
               uint32_t size = 0,
               uint64_t address = 0) override;

    reg_access_status_t send(mfile_t* mf) override;

    bool more_dump() const override { return _layout.more_dump; }

    uint8_t seq_num() const override { return _layout.seq_num; }

    void write_payload(std::ostream& os) const override;

private:
    reg_access_switch_mord_v2_ext _layout{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, nullptr};
    std::vector<uint32_t> _inline_data;
    uint32_t _inline_bytes{0};
};

} // namespace fetchers
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_REGISTER_H
