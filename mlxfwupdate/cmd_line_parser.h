/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
 * End of legal section ......................................................
 *
 *  cmd_line_parser.h - FWUpdater Command Line Parser
 *
 *  Version: $Id$
 *
 *  Author: Sami (sami@mellanox.com)
 */

#include <string>
#include <cmdparser.h>
#include "cmd_line_params.h"

class CmdLineParser : public CommandLineRequester
{
public:
    CmdLineParser(CmdLineParams *params, char **argv, int argc);
    ~CmdLineParser();
    bool parse(char **argv, int argc);
    ParseStatus HandleOption(string name, string value);

private:
    void initOptions();

private:
    CommandLineParser _cmdParser;
    CmdLineParams *_cmdLineParams;
};
