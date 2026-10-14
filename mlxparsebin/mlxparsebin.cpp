/*
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include "mlxparsebin/mlxparsebin_exception.h"
#include "mlxparsebin.h"

/************************************
 * Function: MlxParseBin
 ************************************/
MlxParseBin::MlxParseBin(int argc, char** argv) :
    CommandLineRequester("mlxparsebin"), _argc(argc), _argv(argv), _cmdParser("mlxparsbin")
{
}

/************************************
 * Function: run
 ************************************/
void MlxParseBin::run()
{
    if (parseCmdLine())
    {
        return;
    }

    MlxParseBinLib parser(_options);

    parser.load();
    parser.printDump();
}

/************************************
 * Function: parseCmdLine
 ************************************/
int MlxParseBin::parseCmdLine()
{
    AddOptions("adb", 'a', "ADB_FILE", "ADB file name", false, true);
    AddOptions("bin", 'b', "BIN_FILE", "Binary dump file, supported formats: mstdump,raw", false, true);
    AddOptions("from", ' ', "START_ADDR", "Print fields with address greater than \"from\"");
    AddOptions("to", ' ', "END_ADDR", "Print fields with address lesser than \"to\"");
    AddOptions("filter_path", ' ', "PATH", "Print fields under the given path");
    AddOptions("adb_root", ' ', "ADB_NODE", "Use the given adabe root node");
    AddOptions("root_offset", ' ', "OFFSET", "Byte address of the adb root node inside the dump");
    AddOptions("csv", ' ', "", "Switch to csv ouput format");
    AddOptions("help", 'h', "", "Print help and exit");

    _cmdParser.AddRequester(this);
    int rc = _cmdParser.ParseOptions(_argc, _argv, false);

    if (rc == PARSE_ERROR_SHOW_USAGE)
    {
        printf("%s\n", _cmdParser.GetUsage().c_str());
        return 1;
    }
    else if (rc == PARSE_OK_WITH_EXIT)
    { // OK but need to exit[13:11:45][wasim@mtldesk062]:*/~
        return 1;
    }
    else if (rc == PARSE_ERROR)
    { // error but no need to dump usage
        printf("%s\n", _cmdParser.GetUsage().c_str());
        throw MlxParseBinException(_cmdParser.GetErrDesc());
    }

    return 0;
}

/************************************
 * Function: HandleOption
 ************************************/
ParseStatus MlxParseBin::HandleOption(string name, string value)
{
    char* p;

    if (name == "adb")
    {
        _options.adbFile = value;
        return PARSE_OK;
    }
    else if (name == "bin")
    {
        _options.binFile = value;
        return PARSE_OK;
    }
    else if (name == "from")
    {
        _options.filterFrom = strtoul(value.c_str(), &p, 0);
        if (*p)
        {
            printf("-E- Failed to parse filter_from integer value %s\n", value.c_str());
            return PARSE_ERROR;
        }
        return PARSE_OK;
    }
    else if (name == "to")
    {
        _options.filterTo = strtoul(value.c_str(), &p, 0);
        if (*p)
        {
            printf("-E- Failed to parse filter_to integer value %s\n", value.c_str());
            return PARSE_ERROR;
        }
        return PARSE_OK;
    }
    else if (name == "filter_path")
    {
        _options.filterPath = value;
        return PARSE_OK;
    }
    else if (name == "adb_root")
    {
        _options.adbRootNode = value;
        return PARSE_OK;
    }
    else if (name == "root_offset")
    {
        _options.rootOffsetBytes = strtoull(value.c_str(), &p, 0);
        if (*p)
        {
            printf("-E- Failed to parse root_offset integer value %s\n", value.c_str());
            return PARSE_ERROR;
        }
        return PARSE_OK;
    }
    else if (name == "csv")
    {
        _options.csvMode = true;
        return PARSE_OK;
    }
    else if (name == "help")
    {
        printf("%s\n", _cmdParser.GetUsage().c_str());
        return PARSE_OK_WITH_EXIT;
    }
    else
    {
        return PARSE_ERROR_SHOW_USAGE;
    }
}
