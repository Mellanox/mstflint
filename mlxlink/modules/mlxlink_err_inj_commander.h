/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
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
