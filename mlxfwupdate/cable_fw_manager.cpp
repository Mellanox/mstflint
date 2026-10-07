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

#include "cable_fw_manager.h"
#include "err_msgs.h"

CableFwManager::CableFwManager(const CmdLineParams& cmdParams) : _cmdParams(cmdParams), _errMsg(""), _log("") {}

CableFwManager::~CableFwManager() {}

int CableFwManager::run()
{
    int rc = discoverSystem();
    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }

    rc = discoverCables();
    if (rc != MLX_FWM_SUCCESS)
    {
        return rc;
    }

    if (_cmdParams.cable_dry_run || _cmdParams.cable_update)
    {
        rc = buildUpdatePlan();
        if (rc != MLX_FWM_SUCCESS)
        {
            return rc;
        }
    }

    if (_cmdParams.cable_update)
    {
        // Keep the burn result and report anyway: phase 5 is what tells the user which
        // cables failed, and it is most needed exactly when phase 4 did not go cleanly.
        rc = downloadAndActivate();
    }

    int reportRc = verifyAndReport();
    return (rc != MLX_FWM_SUCCESS) ? rc : reportRc;
}

int CableFwManager::discoverSystem()
{
    _errMsg = "Phase 1 (ASIC discovery) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}

int CableFwManager::discoverCables()
{
    _errMsg = "Phase 2 (cable discovery) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}

int CableFwManager::buildUpdatePlan()
{
    _errMsg = "Phase 3 (analysis and planning) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}

int CableFwManager::downloadAndActivate()
{
    _errMsg = "Phase 4 (download and activate) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}

int CableFwManager::verifyAndReport()
{
    _errMsg = "Phase 5 (verification and report) is not implemented yet";
    return ERR_CODE_CABLE_UPDATE_FAILED;
}
