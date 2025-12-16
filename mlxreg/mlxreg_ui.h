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

#ifndef MLXREG_UI_H
#define MLXREG_UI_H

#include <vector>
#include <iostream>
#include <common/compatibility.h>
#include <cmdparser/cmdparser.h>
#include <mtcr.h>
#include <mlxreg_lib/mlxreg_lib.h>
#include <mlxreg_lib/mlxreg_parser.h>

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

    // Helper class template for ADB-dependent operations
    template<bool dynamic>
    class MlxRegUiImpl
    {
    public:
        // Type aliases for this template instantiation
        using MlxRegLib = _MlxRegLib_impl<dynamic>;
        using RegAccessParser = _RegAccessParser_impl<dynamic>;
        using AdbInstance = typename MlxRegLib::AdbInstance;
        using Adb = typename MlxRegLib::Adb;

    private:
        MlxRegUi* _ui;

    public:
        MlxRegUiImpl(MlxRegUi* ui);

        size_t getLongestNodeLen(const std::vector<AdbInstance*>& root, bool full_path);
        void printRegFields(const std::vector<AdbInstance*>& nodeFields);
        static void onTraverseSaveFieldData(const string& calculated_path,
                                            uint64_t calculated_offset,
                                            uint64_t calculated_value,
                                            AdbInstance* instance,
                                            void* context);
        void printAdbContext(AdbInstance* node, const std::vector<u_int32_t>& buff, MlxRegLib* mlxRegLib);
        void sendCmdBasedOnFileIo(maccess_reg_method_t cmd, int reg_size, MlxRegLib* mlxRegLib);
        void run();
    };

    size_t getLongestNodeLen(std::vector<std::tuple<std::string, uint64_t>> parsed_fields);

    // Print
    void printRegNames(std::vector<string> regs);
    void printBuff(std::vector<u_int32_t> buff);

    void readFromFile(string file_name, vector<u_int32_t>& buff, int len);
    void writeToFile(string file_name, vector<u_int32_t> buff);

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
    bool _isExternal;
    bool _ignore_ro;
    string _output_file;
    string _file_io;
    bool _overwrite;
    bool _full_path;
    bool _use_dynamic;
    std::vector<std::tuple<std::string, uint64_t>> _parsed_fields;
};

#endif /* MLXREG_UI_H */
