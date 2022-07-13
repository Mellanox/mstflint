/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
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

typedef enum
{
    // Debug register commands
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
    void run(int agc, char** argv);

private:
    void initCmdParser();
    void printHelp();
    void paramValidate();
    bool askUser(const char* question);

    // Print
    void printRegFields(vector<AdbInstance*> nodeFields);
    void printRegNames(std::vector<string> regs);
    void printAdbContext(AdbInstance* node, std::vector<u_int32_t> buff);
    void printBuff(std::vector<u_int32_t> buff);

    void readFromFile(string file_name, vector<u_int32_t>& buff, int len);
    void writeToFile(string file_name, vector<u_int32_t> buff);
    void sendCmdBasedOnFileIo(maccess_reg_method_t cmd, int reg_size);

    CommandLineParser _cmdParser;
    string _device;
    mfile* _mf;
    string _extAdbFile;
    string _regName;
    u_int32_t _regID;
    string _dataStr;
    string _indexesStr;
    string _opsStr;
    u_int32_t _dataLen;
    bool _ignoreCapCheck;
    MlxRegOper _op;
    bool _force;
    MlxRegLib* _mlxRegLib;
    bool _isExternal;
    bool _ignore_ro;
    string _output_file;
    string _file_io;
};

#endif /* MLXREG_UI_H */
