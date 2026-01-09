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

#ifndef LINUX_RESET_PLATFORM_H
#define LINUX_RESET_PLATFORM_H

#include <map>
#include "ResetPlatformInterface.h"
#include "CommonResetPlatform.h"
#include "HotResetManager.h"
#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"

class LinuxResetPlatform : public CommonResetPlatform
{
public:
    LinuxResetPlatform(mfile* mf,
                       const ResetFlowParameters& resetParams,
                       const std::vector<std::string>& asicDBDFTargets);
    virtual ~LinuxResetPlatform() override;
    virtual void StopNicDriver() override;
    virtual void StartNicDriver() override;
    virtual void DisableLinks() override;
    virtual void HotReset() override;
    virtual void LinkDisableReset() override;
    virtual void PciReset() override;
    virtual void WaitForReady() override;
    virtual void MSTRestart() override;
    virtual void PreConditionForHotReset(const std::vector<std::string>& ignoreList) override;

private:
    HotResetManager _hotResetManager;
    std::unique_ptr<OperatingSystemAPI> _operatingSystemAPI;
    void ToggleNicDriver(const std::string& asicDBDFTarget, bool unbind);
    bool IsNicDriverBound(const std::string& asicDBDFTarget);
};

#endif // LINUX_RESET_PLATFORM_H