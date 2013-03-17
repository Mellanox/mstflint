/*
 *
 * flint_base.cpp - FLash INTerface
 *
 * Copyright (c) 2011 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id: flint_base.cpp 7522 2011-11-16 15:37:21Z mohammad $
 *
 */


#include "flint_base.h"


bool _print_crc     = false;
bool _silent        = false;
bool _assume_yes    = false;
bool _assume_no     = false;

bool _no_erase      = false;
bool _no_burn       = false;

bool _unlock_bypass = false;
bool _byte_write    = false;

const char* g_sectNames[] = {
    "UNKNOWN (0 - Reserved)",
    "DDR"             ,
    "Configuration"   ,
    "Jump addresses"  ,
    "EMT Service"     ,
    "ROM"             ,
    "GUID"            ,
    "BOARD ID"        ,
    "User Data"       ,
    "FW Configuration",
    "Image Info"      ,
    "DDRZ"            ,
    "Hash File"
};

void report(const char *format, ...)
#ifdef __GNUC__
__attribute__ ((format (printf, 1, 2)))
#endif
;
void report(const char *format, ...)
{
    va_list  args;

    if (!_silent) {
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
} // report

/*
void report_erase(const char *format, ...)
{
    va_list  args;
    char buf[256];
    int i;
    int len;

    if (_silent)
        return;

    va_start(args, format);
    vsnprintf(buf, sizeof buf, format, args);
    va_end(args);

    len = strlen(buf);
    for (i=0; i < len; ++i)
        printf("\b");
} // report_erase
*/
void report_repair_msg(const char* common_msg)
{
    printf("\r%s OK         ", common_msg);
}

#define MAX_ERR_STR_LEN 1024
#define PRE_ERR_MSG "-E-"
void report_err(char err_buff[MAX_ERR_STR_LEN], const char *format, ...)
{
    va_list  args;

    va_start(args, format);

    if (vsnprintf(err_buff, MAX_ERR_STR_LEN, format, args) >= MAX_ERR_STR_LEN) {
        strcpy(&err_buff[MAX_ERR_STR_LEN - 5], "...\n");
    }
    fprintf(stderr, PRE_ERR_MSG" %s", err_buff);

    va_end(args);

    return;
}

void report_warn(const char *format, ...)
{
    va_list  args;
    va_start(args, format);
    printf("\n-W- ");
    vfprintf(stdout, format, args);
    printf("\n");
    va_end(args);
}




const CommandInfo* GetCommandInfo(CommandType cmd) {
    for (u_int32_t i = 0 ; i < numbel(g_commands); i++ ) {
        if (cmd == g_commands[i].cmd) {
            return &g_commands[i];
        }
    }

    return NULL;
}


bool ErrMsg::errmsg(const char *format, ...) {
    va_list   args;

    char* prev_err = _err;

    va_start(args, format);
    _err = vprint(format, args);
    va_end(args);

    delete[] prev_err;

    return false;
}


////////////////////////////////////////////////////////////////////////
void Crc16::add(u_int32_t o)
{
    if (_debug)
        printf("Crc16::add(%08x)\n", o);
    for (int i=0; i<32; i++) {
        if (_crc & 0x8000)
            _crc = (u_int16_t) ((((_crc<<1) | (o>>31)) ^  0x100b) & 0xffff);
        else
            _crc= (u_int16_t) (((_crc<<1) | (o>>31)) & 0xffff);
        o = (o<<1) & 0xffffffff;
    }
} // Crc16::add


////////////////////////////////////////////////////////////////////////
void Crc16::finish()
{
    for (int i=0; i<16; i++) {
        if (_crc & 0x8000)
            _crc=((_crc<<1)  ^  0x100b) & 0xffff;
        else
            _crc=(_crc<<1) & 0xffff;
    }

    // Revert 16 low bits
    _crc = _crc ^ 0xffff;

} // Crc16::finish

