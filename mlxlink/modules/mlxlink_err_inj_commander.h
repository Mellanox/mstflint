/*
 * Copyright (C) 2021 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef MLXLINK_ERR_INJ_COMMANDER_H
#define MLXLINK_ERR_INJ_COMMANDER_H

#include "mlxlink_reg_parser.h"

#define MAX_MIXER_OFFSET_0 0x7ff
#define MAX_MIXER_OFFSET_1 0x3ff

enum PPCNT_GROUPS {
    PPCNT_PHY_GROUP = 0x12,
    PPCNT_STATISTICAL_GROUP = 0x16,
    PPCNT_IB_PORT_COUNTERS_GROUP = 0x20,
    PPCNT_ALL_GROUPS = 63
};

using namespace std;

class MlxlinkErrInjCommander :public MlxlinkRegParser{

public:
    MlxlinkErrInjCommander(Json::Value &jsonRoot);
    virtual ~MlxlinkErrInjCommander();

    void showMixersOffset();
    void updateMixerOffsets();

    u_int32_t _localPort;
    u_int32_t _pnat;
    int _mixerOffset0;
    int _mixerOffset1;
    bool _force;

private:
    bool getUserConfirm();
    u_int16_t getMixerOffset(u_int32_t id);
    void setMixersOffset();

    Json::Value &_jsonRoot;
    MlxlinkCmdPrint _errInjOutput;
    u_int32_t _origMixerOffset0;
    u_int32_t _origMixerOffset1;
};

#endif /* MLXLINK_ERR_INJ_COMMANDER_H */
