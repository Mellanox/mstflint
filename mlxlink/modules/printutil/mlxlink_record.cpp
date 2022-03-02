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

#include "mlxlink_record.h"

#define MAX_LEN_OF_GRADE             6
#define MAX_LEN_OF_DDM_FIELD         14
#define MAX_LEN_OF_MODULE_PRBS_FIELD 15

bool MlxlinkRecord::jsonFormat = false;
std::ostream* MlxlinkRecord::cOut = &std::cout;
FILE* MlxlinkRecord::stdOut = stdout;

MlxlinkRecord::MlxlinkRecord() {
    key = "";
    val = "N/A";
    color = ANSI_COLOR_RESET;
    visible = true;
    arrayValue = false;
    colorKey = false;
}

MlxlinkRecord::~MlxlinkRecord() {
}


std::vector<std::string> MlxlinkRecord::split(const std::string& str, const std::string &delim)
{
    std::vector<std::string> list;
    std::string tmp = str;
    std::string token;
    std::size_t found = tmp.find(delim);
    while (found != std::string::npos) {
        token = tmp.substr(0, found);
        if (!token.empty()) {
            MlxlinkRecord::trim(token);
            list.push_back(token);
        }
        tmp = tmp.substr(found + delim.length());
        found = tmp.find(delim);
    }
    list.push_back(tmp);
    return list;
}

void MlxlinkRecord::trim(std::string& str, const std::string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    str.erase(str.find_last_not_of(chars) + 1);
}

std::string MlxlinkRecord::ddmFlagValue2Color(u_int32_t val, u_int32_t type)
{
    std::string color;
    if (!val) {
        color = MlxlinkRecord::state2Color(GREEN);
    } else {
        switch (type) {
        case DDM_FLAG_WARN:
            color = MlxlinkRecord::state2Color(YELLOW);
            break;
        case DDM_FLAG_ALARM:
            color = MlxlinkRecord::state2Color(RED);
            break;
        default:
            color = MlxlinkRecord::state2Color(GREEN);
        }
    }
    return color;
}

std::string MlxlinkRecord::state2Color(u_int32_t state)
{
    std::string color;
    switch (state) {
    case RED:
        color = ANSI_COLOR_RED;
        break;

    case BLUE:
        color = ANSI_COLOR_BLUE;
        break;

    case YELLOW:
        color = ANSI_COLOR_YELLOW;
        break;

    case GREEN:
        color = ANSI_COLOR_GREEN;
        break;

    case MAGENTA:
        color = ANSI_COLOR_MAGENTA;
        break;

    case CYAN:
        color = ANSI_COLOR_CYAN;
        break;

    default:
        color = ANSI_COLOR_RESET;
    }
    return color;
}

std::string MlxlinkRecord::supported2Color(const std::string &supported)
{
    return (supported != "") ? ANSI_COLOR_GREEN : ANSI_COLOR_RED;
}

void MlxlinkRecord::changeColorOS(const std::string &color, bool newLine)
{
#if defined(__linux__) || defined(__FreeBSD__)
    std::cout << color << "";
#elif defined(_WIN32) || defined(_WIN64)  || defined(__MINGW32__) || defined(__MINGW64__)
    short unsigned int col = MlxlinkRecord::getWinColor(color);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
#endif
    std::cout << "";
    if (newLine) {
        std::cout << " " << std::endl;
    }
}

#if defined(_WIN32) || defined(_WIN64)  || defined(__MINGW32__) || defined(__MINGW64__)
short unsigned int MlxlinkRecord::getWinColor(const std::string &color)
{
    short unsigned int col = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    if (color == ANSI_COLOR_RESET) {
        col = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    } else if (color == ANSI_COLOR_RED) {
        col = FOREGROUND_RED | FOREGROUND_INTENSITY;
    } else if (color == ANSI_COLOR_GREEN) {
        col = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    } else if (color == ANSI_COLOR_BLUE) {
        col = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    } else if (color == ANSI_COLOR_YELLOW) {
        col = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    } else if (color == ANSI_COLOR_CYAN) {
        col = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    } else if (color == ANSI_COLOR_MAGENTA) {
        col = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }
    return col;
}
#endif

void MlxlinkRecord::printFlagLine(const char flag_s, const std::string &flag_l,
        const std::string &param, const std::string &desc)
{
    std::string sflags_s(1, flag_s);
    if (sflags_s != " ") {
        printf(IDENT2 "-%-2s|--%-10s", sflags_s.c_str(), flag_l.c_str());
    } else {
        printf(IDENT2 "--%-14s", flag_l.c_str());
    }
    if (param.length()) {
        printf(" <%s> ", param.c_str());
    } else {
        printf("\t");
    }
    printf(IDENT3 ": %-30s\n", desc.c_str());
}

std::string MlxlinkRecord::addSpace(const std::string &str, u_int32_t size, bool right)
{
    if (MlxlinkRecord::jsonFormat) {
            return str;
    }
    u_int32_t strSize = (size > str.length()) ? size - str.length() : 0;
    std::string spacesToAdd = std::string(strSize, ' ');
    return right? (spacesToAdd + str) : (str + spacesToAdd);
}

std::string MlxlinkRecord::addSpaceForSlrg(const std::string &str)
{
    return MlxlinkRecord::addSpace(str, MAX_LEN_OF_GRADE);
}

std::string MlxlinkRecord::addSpaceForDDM(const std::string &str)
{
    return MlxlinkRecord::addSpace(str, MAX_LEN_OF_DDM_FIELD, false);
}

std::string MlxlinkRecord::addSpaceForModulePrbs(const std::string &str)
{
    return MlxlinkRecord::addSpace(str, MAX_LEN_OF_MODULE_PRBS_FIELD, false);
}

void MlxlinkRecord::printErrorsSection(const std::string &title, const std::string &lines)
{
    changeColorOS(ANSI_COLOR_RED, true);
    std::cout << std::endl << title << std::endl;
    PRINT_UNDER_TITLE((int )title.length());
    std::cout << lines;
    changeColorOS(ANSI_COLOR_RESET, false);
}

void MlxlinkRecord::printCmdLine(const std::string &line, Json::Value &jsonRoot)
{
    if (MlxlinkRecord::jsonFormat) {
        jsonRoot[JSON_RESULT_SECTION][JSON_CONFIG_SECTION].append(line);
        return;
    }
    std::cout << std::endl << line << "..." << std::endl;
}

void MlxlinkRecord::printErr(const std::string &err)
{
    changeColorOS(ANSI_COLOR_RED, true);
    std::cerr << err << std::endl;
    changeColorOS(ANSI_COLOR_RESET, true);
}

void MlxlinkRecord::printWar(const std::string &war, Json::Value &jsonRoot)
{
    if (MlxlinkRecord::jsonFormat) {
        jsonRoot[JSON_RESULT_SECTION][JSON_WARN_SECTION][JSON_MSG] =
                jsonRoot[JSON_RESULT_SECTION][JSON_WARN_SECTION][JSON_MSG].asString() + war;
        return;
    }
    changeColorOS(ANSI_COLOR_YELLOW, true);
    std::cerr << war << std::endl;
    changeColorOS(ANSI_COLOR_RESET, false);
}

std::ostream & operator << (std::ostream &out, const MlxlinkRecord &mlxlinkRecord)
{
    if (!mlxlinkRecord.visible || mlxlinkRecord.key == "") {
        return out;
    }
    bool changeColor = mlxlinkRecord.color != ANSI_COLOR_RESET;
    out << mlxlinkRecord.key << std::setw(PDDR_LINE_LEN - mlxlinkRecord.key.length()) << ": ";
    if (changeColor) {
        MlxlinkRecord::changeColorOS(mlxlinkRecord.color);
    }
    out << mlxlinkRecord.val << std::endl;
    if (changeColor) {
        MlxlinkRecord::changeColorOS(ANSI_COLOR_RESET);
    }
    return out;

}
