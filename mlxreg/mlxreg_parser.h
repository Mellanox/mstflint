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

#ifndef MLXREG_PARSER_H
#define MLXREG_PARSER_H

#include <string>
#include <algorithm>
#include <adb_parser/adb_parser.h>
#include "mlxreg_exception.h"

namespace mlxreg {

#define MAX_REG_SIZE 0x2000

typedef enum {
    Pm_Known = 0,
    Pm_Unknown
} parseMode;

class RegAccessParser
{
public:
    RegAccessParser(string data, string indexes, AdbInstance *regNode, std::vector<u_int32_t> buffer);
    RegAccessParser(string data, string indexes, AdbInstance *regNode, u_int32_t len);
    std::vector<u_int32_t> genBuff();
    u_int32_t getDataLen() {return _len;};
    static void strToUint32(char *str, u_int32_t &uint);
protected:
    string _data;
    string _indexes;
    u_int32_t _len;
    AdbInstance *_regNode;
    parseMode _parseMode;
    std::vector<u_int32_t>    _buffer;
    std::vector<u_int32_t> genBuffUnknown();
    std::vector<u_int32_t> genBuffKnown();
    void parseIndexes();
    void parseData();
    void parseUnknown();
    AdbInstance* getField(string name);
    std::vector<string> strSplit(string str, char delimiter, bool forcePairs);
    void updateBuffer(u_int32_t offset, u_int32_t size, u_int32_t val);
    void updateBufferUnknwon(std::vector<string> fieldTokens);
    void updateField(string field_name, u_int32_t value);
    u_int32_t getFieldValue(string field_name, std::vector<u_int32_t>& buff);
    bool isRO(AdbInstance *field);
    bool isIndex(AdbInstance *field);
    std::vector<string> getAllIndexes(AdbInstance *node);
};

}
#endif /* MLXREG_PARSER_H */
