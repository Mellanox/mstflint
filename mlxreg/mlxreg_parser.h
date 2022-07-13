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

#ifndef MLXREG_PARSER_H
#define MLXREG_PARSER_H

#include <string>
#include <algorithm>
#include <adb_parser/adb_parser.h>
#include "mlxreg_exception.h"

namespace mlxreg
{
#define MAX_REG_SIZE 0x2000

typedef enum
{
    Pm_Known = 0,
    Pm_Unknown
} parseMode;

class RegAccessParser
{
public:
    RegAccessParser(string data,
                    string indexes,
                    string ops,
                    AdbInstance* regNode,
                    std::vector<u_int32_t> buffer,
                    bool ignore_ro = false);
    RegAccessParser(string data, string indexes, string ops, AdbInstance* regNode, u_int32_t len, bool ignore_ro = false);
    std::vector<u_int32_t> genBuff();
    u_int32_t getDataLen() { return _len; };
    static void strToUint32(char* str, u_int32_t& uint);
    static string getAccess(const AdbInstance* field);
    enum access_type_t
    {
        INDEX,
        OP
    };

protected:
    string _data;
    string _indexes;
    string _ops;
    u_int32_t _len;
    AdbInstance* _regNode;
    parseMode _parseMode;
    string output_file;
    std::vector<u_int32_t> _buffer;
    bool _ignore_ro;
    std::vector<u_int32_t> genBuffUnknown();
    std::vector<u_int32_t> genBuffKnown();
    void parseAccessType(std::vector<string> tokens, std::vector<string> validTokens, access_type_t accessType);
    void parseIndexes();
    void parseOps();
    void parseData();
    void parseUnknown();
    bool checkFieldWithPath(AdbInstance* field, u_int32_t idx, std::vector<string>& fieldsChain);
    AdbInstance* getField(string name);
    std::vector<string> strSplit(string str, char delimiter, bool forcePairs);
    void updateBuffer(u_int32_t offset, u_int32_t size, u_int32_t val);
    void updateBufferUnknwon(std::vector<string> fieldTokens);
    void updateField(string field_name, u_int32_t value);
    u_int32_t getFieldValue(string field_name, std::vector<u_int32_t>& buff);
    bool isRO(AdbInstance* field);
    bool isIndex(AdbInstance* field);
    bool isOP(AdbInstance* field);
    std::vector<string> getAllIndexes(AdbInstance* node);
    std::vector<string> getAllOps(AdbInstance* node);
    const std::string accessTypeToString(access_type_t accessType);

private:
    bool checkAccess(const AdbInstance* field, const string accessStr);
};

} // namespace mlxreg
#endif /* MLXREG_PARSER_H */
