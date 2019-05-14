/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

MlxlinkRecord::MlxlinkRecord() {
    key = "";
    val = "N/A";
    color = ANSI_COLOR_RESET;
    visible = true;
}

MlxlinkRecord::~MlxlinkRecord() {
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

std::ostream & operator << (std::ostream &out, const MlxlinkRecord &c)
{

    if (!c.visible) {
        return out;
    }

    out << c.key << std::setw(PDDR_LINE_LEN - c.key.length()) << ": ";
    MlxlinkRecord::changeColorOS(c.color);
    out << c.val << std::endl;
    MlxlinkRecord::changeColorOS(ANSI_COLOR_RESET);
    return out;
}
