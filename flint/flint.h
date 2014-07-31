/*
 *
 * flint2.h - FLash INTerface
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id$
 *
 */

#ifndef __FLINT_H__
#define __FLINT_H__

#include <string.h>
#include "flint_params.h"
#include "subcommands.h"
#include <cmdparser/cmdparser.h>
#include "err_msgs.h"

using namespace std;

typedef map <sub_cmd_t, SubCommand*> map_sub_cmd_t_to_subcommand;
typedef map <string, string> map_string_to_string;
typedef map <string, int> map_string_to_int;

map_string_to_string initShortToLongFlagMap();
map_string_to_int initLongFlagToNumOfArgsMap();
void deInitSubcommandMap(map_sub_cmd_t_to_subcommand cmdMap);
map_sub_cmd_t_to_subcommand initSubcommandMap();

class Flint : public CommandLineRequester
{
private:
    FlintParams _flintParams;
    CommandLineParser   _cmdParser;
    map_sub_cmd_t_to_subcommand _subcommands;

    //methods
    map_sub_cmd_t_to_subcommand initSubcommandMap();
    void deInitSubcommandMap(map_sub_cmd_t_to_subcommand cmdMap);

public:
    Flint();
    ~Flint();
    void initCmdParser();
    virtual ParseStatus HandleOption(string name, string value);
    ParseStatus parseCmdLine(int argc, char* argv[]);
    FlintStatus run(int argc, char* argv[]);
};
#endif
