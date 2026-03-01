/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXLINK_UI_H
#define MLXLINK_UI_H

#include "mlxlink_commander.h"
#include "printutil/mlxlink_record.h"

class MlxlinkUi : public CommandLineRequester
{
public:
    MlxlinkUi();
    virtual ~MlxlinkUi();
    bool isSwitch();
    int run(int argc, char** argv);
    virtual void initMlxlinkCommander();

protected:
    virtual void addCmd(OPTION_TYPE option);
    ParseStatus HandleOption(string name, string value);
    virtual void printSynopsisHeader();
    virtual void printSynopsisQueries();
    virtual void printSynopsisCommands();
    virtual void printSynopsis();
    virtual void printHelp();
    virtual void initCmdParser();
    virtual void commandsCaller();
    virtual void validateMandatoryParams();
    virtual void validatePCIeParams();
    virtual void validateGeneralCmdsParams();
    virtual void validatePRBSParams();
    virtual void validateModulePRBSParams();
    virtual void validateSpeedAndCSVBerParams();
    virtual void validateCableParams();
    virtual void validateTxGroupParams();
    virtual void validateGradeScanParams();
    virtual void validateErrInjParams();
    virtual void validatePortInfoParams();
    virtual void validatePhyRecoveryParams();
    virtual void validateLinkTrainingParams();
    virtual void validatePeriodicEqParams();
    virtual void validateMultiPortInfoParams();
    virtual void validateBkvParams();
    virtual void paramValidate();
    virtual void createMlxlinkCommander();
    virtual void initRegAccessLib();
    virtual void initPortInfo();
    virtual void initPCIDomain();
    virtual void updateSysFsPath(string& sysfsPath);

    void handlePortStr(UserInput& userInput, const string& portStr);
    void strToInt32(char* str, u_int32_t& value);
    std::vector<string> parseParamsFromLine(const string& paramsLine);
    std::map<u_int32_t, u_int32_t> getSltpParamsFromVector(const string& paramsLine);
    std::map<u_int32_t, bool> getprbsLanesFromParams(const string& paramsLine);
    void checkStrLength(const string& str);

    CommandLineParser _cmdParser;
    std::vector<OPTION_TYPE> _sendRegFuncMap;
    MlxlinkCommander* _mlxlinkCommander;
    UserInput _userInput;

    mfile* _mf;
};
#endif /* MLXLINK_UI_H */
