/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 * mlxcfg_utils.cpp
 *
 *  Created on: Jun 21, 2016
 *      Author: ahmads
 */

#include <sstream>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <iomanip>
#include <mft_sig_handler.h>
#include <bit_slice.h>
#include <cmdif/tools_cif.h>
#include <compatibility.h>

#include <tools_layouts/tools_open_layouts.h>
#include <tools_layouts/reg_access_hca_layouts.h>
#include <mft_utils.h>
#include "mlxcfg_utils.h"

#include "common/tools_regex.h"
using namespace std;
#include <cstdlib>

bool mlxcfg_is_debug_enabled()
{
    static int debug_enabled = -1;
    if (debug_enabled == -1)
    {
        const char* env_val = getenv("MLXCONFIG_DEBUG");
        debug_enabled = (env_val != NULL) && (env_val[0] != '\0') && (env_val[0] != '0') ? 1 : 0;
    }
    return debug_enabled;
}

typedef struct reg_access_hca_mqis_reg_ext mqisReg;
#define MAX_REG_DATA 128

void dealWithSignal()
{
    int sig;
    sig = mft_signal_is_fired();
    if (sig)
    {
        // reset received signal
        mft_signal_set_fired(0);
        // retore prev handler
        mft_signal_set_handling(0);
        // raise signal to let the previous handle deal with it.
        raise(sig);
    }
    mft_signal_set_handling(0);
    return;
}

MError mnvaCom5thGen(mfile* mf,
                     u_int8_t* buff,
                     u_int16_t len,
                     u_int32_t tlvType,
                     reg_access_method_t method,
                     QueryType qT,
                     bool is_host_id_valid)
{
    struct tools_open_mnvda mnvaTlv;
    memset(&mnvaTlv, 0, sizeof(struct tools_open_mnvda));

    if (method == REG_ACCESS_METHOD_GET && mf->tp != MST_IB)
    {
        mnvaTlv.nv_hdr.length = sizeof(mnvaTlv.data);
    }
    else
    {
        mnvaTlv.nv_hdr.length = len;
    }
    mnvaTlv.nv_hdr.rd_en = 0;
    mnvaTlv.nv_hdr.over_en = 1;
    mnvaTlv.nv_hdr.writer_id = WRITER_ID_ICMD_MLXCONFIG;
    mnvaTlv.nv_hdr.writer_host_id = is_host_id_valid ? 1 : 0;
    if (qT == QueryDefault)
    {
        mnvaTlv.nv_hdr.default_ = 1;
    }
    else if (qT == QueryCurrent)
    {
        mnvaTlv.nv_hdr.read_current = 1;
    }
    // tlvType should be in the correct endianess
    mnvaTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw = __be32_to_cpu(tlvType);
    memcpy(mnvaTlv.data, buff, len);
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    DEBUG_PRINT_SEND(&mnvaTlv, mnvda);
    rc = reg_access_mnvda(mf, method, &mnvaTlv);
    DEBUG_PRINT_RECEIVE(&mnvaTlv, mnvda);
    dealWithSignal();
    if (rc)
    {
        return rc;
    }
    memcpy(buff, mnvaTlv.data, len);
    return ME_OK;
}

MError nvqcCom5thGen(mfile* mf, u_int32_t tlvType, bool& suppRead, bool& suppWrite, u_int32_t& version)
{
    struct reg_access_hca_mnvqc_reg_ext nvqcTlv;
    memset(&nvqcTlv, 0, sizeof(struct reg_access_hca_mnvqc_reg_ext));

    // tlvType should be in the correct endianess
    nvqcTlv.type = __be32_to_cpu(tlvType);
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    rc = reg_access_mnvqc(mf, REG_ACCESS_METHOD_GET, &nvqcTlv);
    dealWithSignal();
    if (rc)
    {
        return rc;
    }
    suppRead = nvqcTlv.support_rd;
    suppWrite = nvqcTlv.support_wr;
    version = nvqcTlv.version;

    // printf("-D- nvqcTlv.support_rd=%d nvqcTlv.support_wr=%d\n", nvqcTlv.support_rd, nvqcTlv.support_wr);
    return ME_OK;
}

MError nvdiCom5thGen(mfile* mf, u_int32_t tlvType, bool is_host_id_valid)
{
    struct tools_open_mnvdi mnvdiTlv;
    memset(&mnvdiTlv, 0, sizeof(struct tools_open_mnvdi));

    mnvdiTlv.nv_hdr.rd_en = 0;
    mnvdiTlv.nv_hdr.over_en = 1;
    mnvdiTlv.nv_hdr.writer_id = WRITER_ID_ICMD_MLXCONFIG;
    mnvdiTlv.nv_hdr.writer_host_id = is_host_id_valid ? 1 : 0;
    // tlvType should be in the correct endianess
    mnvdiTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw = __be32_to_cpu(tlvType);

    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    DEBUG_PRINT_SEND(&mnvdiTlv, mnvdi);
    rc = reg_access_mnvdi(mf, REG_ACCESS_METHOD_SET, &mnvdiTlv);
    DEBUG_PRINT_RECEIVE(&mnvdiTlv, mnvdi);
    dealWithSignal();
    if (rc)
    {
        return rc;
    }
    return ME_OK;
}

bool strToNum(string str, u_int32_t& num, int base)
{
    char* endp;
    char* numStr = strcpy(new char[str.size() + 1], str.c_str());
    unsigned long tmpNum = strtoul(numStr, &endp, base);

    if (*endp)
    {
        delete[] numStr;
        return false;
    }
    delete[] numStr;
    // errno will only be set in 32bit arch, in 64bit it can parse much larger numbers, which will be cought on the
    // second part
    if (errno == ERANGE || (tmpNum > 0xFFFFFFFF))
    {
        throw MlxcfgException("value is out of range");
    }
    num = tmpNum;
    return true;
}

string numToStr(u_int32_t num, bool isHex)
{
    stringstream ss;

    if (isHex)
    {
        ss << std::uppercase << "0x" << std::hex;
    }

    ss << num;
    return ss.str();
}

string numToStrFormatted(u_int32_t num, bool isHex)
{
    stringstream ss;

    if (isHex)
    {
        ss << std::uppercase << std::hex;
    }

    ss << std::setfill('0') << std::setw(8) << num;
    return ss.str();
}

vector<string> splitStr(const string s, char d)
{
    vector<string> v;
    stringstream ss(s);
    string to;

    while (std::getline(ss, to, d))
    {
        v.push_back(to);
    }

    return v;
}

string mlxcfg_ltrim(string s)
{
    const char* cs = s.c_str();
    while (isspace(*cs))
    {
        cs++;
    }
    return string(cs);
}

string mlxcfg_rtrim(string s)
{
    // todo rewrite it
    unsigned int i = s.size();
    if (i == 0)
    {
        return s;
    }
    while (--i > 0 && isspace(s[i]))
    {
        ;
    }
    if (i == 0 && isspace(s[i]))
    {
        return "";
    }
    return s.substr(0, i + 1);
}

string mlxcfg_trim(string s)
{
    return mlxcfg_rtrim(mlxcfg_ltrim(s));
}

string writerIdToStr(WriterId writerId)
{
    switch (writerId)
    {
        case WRITER_ID_UNSPECIFIED:
            return "Unspecified";

        case WRITER_ID_CHASSIS_BMC:
            return "Chassis BMC";

        case WRITER_ID_MAD:
            return "MAD";

        case WRITER_ID_BMC:
            return "BMC";

        case WRITER_ID_CMD_IF:
            return "CMD IF";

        case WRITER_ID_ICMD:
            return "ICMD";

        case WRITER_ID_ICMD_UEFI_HII:
            return "ICMD UEFI HII";

        case WRITER_ID_ICMD_UEFI_CLP:
            return "ICMD UEFI CLP";

        case WRITER_ID_ICMD_FLEXBOOT:
            return "ICMD FLEXBOOT";

        case WRITER_ID_ICMD_MLXCONFIG:
            return "ICMD MLXCONFIG";

        case WRITER_ID_ICMD_USER1:
            return "ICMD USER1";

        case WRITER_ID_ICMD_USER2:
            return "ICMD USER2";

        case WRITER_ID_ICMD_MLXCONFIG_SET_RAW:
            return "ICMD MLXCONFIG SET RAW";

        case WRITER_ID_OTHER:
            return "OTHER";

        default:
            return "Unknown";
    }
};

void copyDwVectorToBytesVector(const vector<u_int32_t>& dwV, vector<u_int8_t>& bV)
{
    bV.resize(dwV.size() << 2);
    memcpy(bV.data(), dwV.data(), bV.size());
}

void copyBytesVectorToDwVector(const vector<u_int8_t>& bV, vector<u_int32_t>& dwV)
{
    dwV.resize(bV.size() >> 2);
    memcpy(dwV.data(), bV.data(), bV.size());
}

string parseIndexStr(const string& indexedMlxconfigName)
{
    size_t pl = indexedMlxconfigName.find('[');
    size_t pr = indexedMlxconfigName.find(']');
    if (pl == std::string::npos || pr == std::string::npos)
    {
        throw MlxcfgException("Expected a parameter with index");
    }
    return indexedMlxconfigName.substr(pl + 1, pr - pl - 1);
}

string increaseIndexIfNeeded(const string& name)
{
    string increasedName = name;

    if (isIndexedMlxconfigName(name))
    {
        size_t pl = name.find('[');
        size_t pr = name.find(']');
        if (isIndexedStartFromOneSupported(name.substr(0, pl)))
        {
            u_int32_t increasedIndex = 0;
            if (strToNum(name.substr(pl + 1, pr - pl - 1), increasedIndex))
            {
                increasedIndex++;
                increasedName = name.substr(0, pl) + "[" + numToStr(increasedIndex) + "]";
            }
        }
    }

    return increasedName;
}

bool isIndexedStartFromOneSupported(const string& mlxconfigName)
{
#if defined(MST_UL)
    (void)mlxconfigName;
    return false;
#else
    return mlxconfigName == "SPLIT_PORT";
#endif
}

void parseIndexedMlxconfigName(const string& indexedMlxconfigName, string& mlxconfigName, u_int32_t& index)
{
    string indexStr = parseIndexStr(indexedMlxconfigName);

    if (!strToNum(indexStr, index))
    {
        throw MlxcfgException("Can not parse the index of %s\n", indexedMlxconfigName.c_str());
    }

    size_t p = indexedMlxconfigName.find('[');
    if (p == std::string::npos)
    {
        throw MlxcfgException("Expected a parameter with index");
    }
    mlxconfigName = indexedMlxconfigName.substr(0, p);
}

void extractIndexes(const string& indexesStr, vector<u_int32_t>& indexes)
{
    size_t p = indexesStr.find("..");
    if (p != string::npos)
    {
        unsigned int leftIndex = 0, rightIndex = 0;
        string leftIndexStr = indexesStr.substr(0, p);
        string rightIndexStr = indexesStr.substr(p + 2);
        if (!strToNum(leftIndexStr, leftIndex))
        {
            throw MlxcfgException("Can not parse the index %s", leftIndexStr.c_str());
        }
        if (!strToNum(rightIndexStr, rightIndex))
        {
            throw MlxcfgException("Can not parse the index %s", rightIndexStr.c_str());
        }
        if (leftIndex > rightIndex)
        {
            throw MlxcfgException("Left index %d can not be greater than right index %d", leftIndex, rightIndex);
        }
        while (rightIndex >= leftIndex)
        {
            indexes.push_back(leftIndex);
            leftIndex++;
        }
    }
    else
    {
        u_int32_t index = 0;
        if (!strToNum(indexesStr, index))
        {
            throw MlxcfgException("Can not parse the index %s", indexesStr.c_str());
        }
        indexes.push_back(index);
    }
}

bool isIndexedMlxconfigName(const string& mlxconfigName)
{
    return (mlxconfigName.find("[") != string::npos);
}

string getArraySuffix(const string& mlxconfigName)
{
#if defined(MST_UL)
    (void)mlxconfigName;
    return "";
#else
    static const mstflint::common::regex::regex EXP_PATTERN("(_[0-9]{2}_[0-9]+)");
    string suffix = "";
    mstflint::common::regex::smatch match;

    if (mstflint::common::regex::regex_search(mlxconfigName, match, EXP_PATTERN))
    {
        suffix = match.str();
    }

    return suffix;
#endif
}

string getArrayPrefix(const string& mlxconfigName)
{
    string prefix = mlxconfigName;

    return prefix.substr(0, mlxconfigName.size() - getArraySuffix(mlxconfigName).size());
}

string getArraySuffixByInterval(u_int32_t interval)
{
    string suffix = "_";
    u_int32_t low_bound = ((interval / MAX_ARRAY_SIZE) * MAX_ARRAY_SIZE) + 1;
    u_int32_t upper_bound = low_bound + MAX_ARRAY_SIZE - 1;

    suffix += numToStr(upper_bound) + "_" + numToStr(low_bound);

    return suffix;
}

bool getDeviceInformationString(mfile* mf, info_type_t op, vector<char>& infoString)
{
    mqisReg mqisRegister;
    reg_access_status_t rc;
    int maxDataSize = sizeof(mqisRegister.info_string);

    memset(&mqisRegister, 0, sizeof(mqisReg));
    if (op == Device_Name)
    {
        mqisRegister.info_type = 0x1;
    }
    else if (op == Device_Description)
    {
        mqisRegister.info_type = 0x2;
    }
    else
    {
        return false;
    }
    mqisRegister.read_length = maxDataSize;
    mft_signal_set_handling(1);

    rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqisRegister);
    dealWithSignal();
    if (rc)
    {
        return false;
    }
    // reg_access_hca_mqis_reg_print(&mqisRegister, stdout, 4);
    int infoSize = mqisRegister.info_length;
    if (infoSize == 0)
    {
        return false;
    }
    infoString.resize(infoSize + 1, 0);

    // copy the output
    memcpy(infoString.data(), mqisRegister.info_string, mqisRegister.read_length);

    if (infoSize > mqisRegister.read_length)
    {
        int leftSize = infoSize - mqisRegister.read_length;
        while (leftSize > 0)
        {
            mqisRegister.read_offset = infoSize - leftSize;
            mqisRegister.read_length = leftSize > maxDataSize ? maxDataSize : leftSize;
            mft_signal_set_handling(1);

            rc = reg_access_mqis(mf, REG_ACCESS_METHOD_GET, &mqisRegister);
            dealWithSignal();
            if (rc)
            {
                return false;
            }
            // reg_access_hca_mqis_reg_print(&mqisRegister, stdout, 4);
            memcpy(infoString.data() + mqisRegister.read_offset, (mqisRegister.info_string), mqisRegister.read_length);
            leftSize -= mqisRegister.read_length;
        }
    }

    string str = string(infoString.data());
    if (str.length() == 0)
    {
        return false;
    }
    return true;
}

Device_Type getDeviceTypeFromString(string inStr)
{
    mft_utils::to_lowercase(inStr);
    if (inStr == "switch")
    {
        return Device_Type::Switch;
    }
    else if (inStr == "hca")
    {
        return Device_Type::HCA;
    }
    else if (inStr == "retimer")
    {
        return Device_Type::Retimer;
    }
    else
    {
        return Device_Type::UNSUPPORTED_DEVICE;
    }
}

MlxcfgException::MlxcfgException(const char* fmt, ...)
{
    const unsigned int max = 1024;
    char tmp[max];
    va_list args;

    va_start(args, fmt);
    vsnprintf(tmp, max, fmt, args);
    va_end(args);
    _err = tmp;
}

MlxcfgTLVNotFoundException::MlxcfgTLVNotFoundException(const char* cTLVName) :
    MlxcfgException("The TLV configuration %s was not found", cTLVName)
{
}
