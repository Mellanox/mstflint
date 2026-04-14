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
#include <type_traits>
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

        struct FieldBase
        {
            string name;
            static bool on_traverse(const string& calculated_path,
                                    uint64_t calculated_offset,
                                    uint64_t calculated_value,
                                    AdbInstance* instance,
                                    void* context) = delete;
        };

        struct SentField : FieldBase
        {
            uint64_t value;

            // Metadata for detailed output (--detailed flag)
            std::string enum_name;

            SentField() : value(0) {}

            static bool on_traverse(const string& calculated_path,
                                    uint64_t calculated_offset,
                                    uint64_t calculated_value,
                                    AdbInstance* instance,
                                    void* context);
        };

        struct QueryField : FieldBase
        {
            uint64_t offset;
            uint64_t size;
            string access;

            // Metadata for enum support
            std::map<uint64_t, std::string> enum_values; // value -> name mapping, empty if no enum

            // Metadata for advanced output (--advanced flag)
            std::string description;
            ParamType param_type;

            QueryField() : offset(0), size(0), param_type(ParamType::DATA) {}

            static bool on_traverse(const string& calculated_path,
                                    uint64_t calculated_offset,
                                    uint64_t calculated_value,
                                    AdbInstance* instance,
                                    void* context);
        };

    private:
        MlxRegUi* _ui;
        MlxRegLib* _mlxRegLib{nullptr};

        std::vector<SentField> _parsed_fields;
        std::vector<QueryField> _query_fields;

        // Formatting methods for GET/SET operations (SentField)
        void printSentFieldsStandard(const std::vector<SentField>& fields) const;
        void printSentFieldsDetailed(const std::vector<SentField>& fields) const;

        // Formatting methods for SHOW_REG operations (QueryField)
        void printQueryFieldsStandard(const std::vector<QueryField>& fields) const;
        void printQueryFieldsAdvanced(const std::vector<QueryField>& fields, const std::string& filter_field = "");

        // Helper for text wrapping in Description column
        std::vector<std::string> wrapTextToWidth(const std::string& text, int width);

        // Helper for description text processing
        std::string cleanDescriptionText(const std::string& text);
        std::string truncateDescription(const std::string& text, int width);

        void printTableSeparator(int width) const;

        template<typename T>
        std::vector<T> applyFieldFilter(const std::vector<T>& fields, const std::string& filter_field) const;

        void printFieldGroupWithDescription(const std::vector<QueryField>& fields,
                                            const std::vector<size_t>& group_indices,
                                            int nameWidth,
                                            int descWidth);

        void printEnumValues(const QueryField& field, int nameWidth, const std::string& fieldName);

    public:
        MlxRegUiImpl(MlxRegUi* ui);
        ~MlxRegUiImpl();

        template<typename T, typename = typename std::enable_if<std::is_base_of<FieldBase, T>::value>::type>
        size_t getLongestNodeLen(const std::vector<T>& parsed_fields) const;
        void printRegFields(AdbInstance* node);
        void printAdbContext(AdbInstance* node, const std::vector<u_int32_t>& buff);
        void sendCmdBasedOnFileIo(maccess_reg_method_t cmd, int reg_size);
        void run();
    };

    // Print
    void printRegNames(std::vector<string> regs);
    void printBuff(std::vector<u_int32_t> buff);
    void printRawBuffer(std::vector<u_int32_t> buff);

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
    bool _detailed;
    bool _advanced;
    bool _full_desc;
    std::string _field_name;
    std::string _gen_cmd_buffer_device_type;
};

#endif /* MLXREG_UI_H */
