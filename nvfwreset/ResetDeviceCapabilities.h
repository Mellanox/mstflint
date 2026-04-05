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

#ifndef RESET_DEVICE_CAPABILITIES_H
#define RESET_DEVICE_CAPABILITIES_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "NVFWresetParams.h"
#include "ResetParameterDefs.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_hca_layouts.h"

class ResetDeviceCapabilities
{
public:
    ResetDeviceCapabilities(mfile* mf, NVFWresetParams& params);
    const ResetDeviceParam& getResetDeviceParam() const { return _resetDeviceParam; }

private:
    struct ResetDeviceParam _resetDeviceParam;
    reg_access_hca_mroq_ext sendMroqCommand(mfile* mf, NVFWresetParams& params);
    bool isMroqSupported(mfile* mf);
    void parseResetLevels(reg_access_hca_mroq_ext& mroq);
    void parseResetSyncTypes(reg_access_hca_mroq_ext& mroq);
    void parseResetTypes(reg_access_hca_mroq_ext& mroq);
    void parseResetMethods(reg_access_hca_mroq_ext& mroq);
};

#endif // RESET_DEVICE_CAPABILITIES_H