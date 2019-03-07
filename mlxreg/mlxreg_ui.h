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

#ifndef MLXREG_UI_H
#define MLXREG_UI_H

#include <vector>
#include <iostream>
#include <common/compatibility.h>
#include <cmdparser/cmdparser.h>
#include <mtcr.h>
#include "mlxreg_lib.h"
#include "mlxreg_parser.h"

using namespace mlxreg;


typedef enum {
    //Debug register commands
    CMD_SET = 0,
    CMD_GET,
    CMD_SHOW_REG,
    CMD_SHOW_REGS,
    CMD_SHOW_ALL_REGS,
    CMD_UNKNOWN
} MlxRegOper;

class MlxRegUi : public CommandLineRequester
{
public:
    MlxRegUi();
    ~MlxRegUi();
    ParseStatus HandleOption(string name, string value);
    void run(int agc, char **argv);

private:
    void initCmdParser();
    void printHelp();
    void paramValidate();
    bool askUser(const char *question);

    //Print
    void printRegFields(vector<AdbInstance*> nodeFields);
    void printRegNames(std::vector<string> regs);
    void printAdbContext(AdbInstance *node, std::vector<u_int32_t> buff);
    void printBuff(std::vector<u_int32_t> buff);

    CommandLineParser _cmdParser;
    string _device;
    mfile *_mf;
    string _extAdbFile;
    string _regName;
    u_int32_t _regID;
    string _dataStr;
    string _indexesStr;
    u_int32_t _dataLen;
    bool _ignoreCapCheck;
    bool _ignoreRegCheck;
    MlxRegOper _op;
    bool _force;
    MlxRegLib *_mlxRegLib;
    bool _isExternal;
};

#endif /* MLXREG_UI_H */
