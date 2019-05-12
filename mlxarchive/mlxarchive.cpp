
/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 */

/*
 * mlxarchive.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <string>
#include <vector>
#include<iostream>
#include <boost/regex.hpp>
#include <compatibility.h>
#include "mlxarchive_mfa2_package_gen.h"
#include <cmdparser/cmdparser.h>
#include "mlxarchive.h"

#define IDENT            "    "
#define IDENT2           IDENT IDENT
#define IDENT3           "\t\t"
#define MLXARCHIVE_EXEC  "mlxarchive"

/************************************
 * * FLAGS Constants
 * ************************************/
#define HELP_FLAG                   "help"
#define HELP_FLAG_SHORT             'h'
#define BINS_DIR_FLAG               "bins-dir"
#define BINS_DIR_FLAG_SHORT         'b'
#define OUT_FILE_FLAG               "out-file"
#define OUT_FILE_FLAG_SHORT         'o'
#define DATE_FLAG                   "date"
#define DATE_FLAG_SHORT             'd'
#define VERSION_FLAG                "version"
#define VERSION_FLAG_SHORT          'v'

using namespace mlxarchive;
bool writeToFile(const string&, const vector<u_int8_t>&);

/************************************
 * * Function: Mlxarchive
 * ************************************/
Mlxarchive::Mlxarchive() :
    CommandLineRequester("mlxarchive OPTIONS"),
    _cmdParser("mlxarchive")
{
    initCmdParser();
    _binsDir  = "";
    _outFile  = "";
    _version  = "";
}

/************************************
 * * Function: initCmdParser
 * ************************************/
void Mlxarchive::initCmdParser()
{
    AddOptions(HELP_FLAG,         HELP_FLAG_SHORT,     "", "Show help message and exit");
    AddOptions(VERSION_FLAG,      VERSION_FLAG_SHORT,  "version", "MFA2 version in the following format: x.x.x");
    AddOptions(OUT_FILE_FLAG,     OUT_FILE_FLAG_SHORT, "out_file", "Output file");
    AddOptions(BINS_DIR_FLAG,     BINS_DIR_FLAG_SHORT, "bins_dir", "Directory with the binaries files");
    _cmdParser.AddRequester(this);
}

void Mlxarchive::paramValidate()
{
    std::string err = "Missing mandatory parameter: %s\n";
    std::string err_regex = "Bad format in: %s(%s), the format should be like: %s\n";
    boost::smatch match;
    bool status_match;
    bool success = true;
    if(_binsDir.empty()) {
        fprintf(stderr, err.c_str(), "bins_dir");
        success = false;
    }
    if(_outFile.empty()) {
        fprintf(stderr, err.c_str(), "out_file");
        success = false;
    }
    else {
        if(fexists(_outFile)) {
            fprintf(stderr, "Output file: %s already exists\n", _outFile.c_str());
            success = false;
        }
    }
    if(_version.empty()) {
        fprintf(stderr, err.c_str(), "version");
        success = false;
    }
    else {
        boost::regex version_expression("^[0-9].[0-9].[0-9]$");
        status_match = boost::regex_match(_version, match, version_expression);
        if(!status_match) {
            fprintf(stderr, err_regex.c_str(), "version", _version.c_str(), "x.x.x");
            success = false;
        }
    }
    if(!success) {
        exit(1);
    }
}

ParseStatus Mlxarchive::HandleOption(string name, string value)
{
    if (name == HELP_FLAG) {
        cout << _cmdParser.GetUsage();
        return PARSE_OK_WITH_EXIT;
    } else if (name == VERSION_FLAG) {
        _version = value;
        return PARSE_OK;
    } else if (name == OUT_FILE_FLAG) {
        _outFile = value;
        return PARSE_OK;
    } else if (name == BINS_DIR_FLAG) {
        _binsDir = value;
        return PARSE_OK;
    }
    else{
        return PARSE_ERROR;
    }
 return PARSE_ERROR;
}

int Mlxarchive::run(int argc, char **argv)
{
    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);
    if (rc == PARSE_OK_WITH_EXIT) {
        return 0;
    } else if (rc == PARSE_ERROR) {
        cout << _cmdParser.GetUsage();
        //throw MlxRegException("failed to parse arguments. %s", _cmdParser.GetErrDesc());
        return 1;
    } else if (rc == PARSE_ERROR_SHOW_USAGE) {
        cout << _cmdParser.GetUsage();
        //throw MlxRegException("failed to parse arguments. %s", _cmdParser.GetErrDesc());
        return 1;
    }
    paramValidate();
    string outputFile = _outFile;
    string content = "";
    vector<u_int8_t> buff;
    MFA2PackageGen mfa2PackageGen;
    string dir = _binsDir;
    string version = _version;

    buff.clear();
    mfa2PackageGen.generateBinFromFWDirectory(dir, version, buff);
    //Save output to a file
    if (!writeToFile(outputFile, buff)) {
        fprintf(stderr, "-E- Cannot write to the file %s\n",   outputFile.c_str());
        exit(1);
    }

    return 0;
}

Mlxarchive::~Mlxarchive() {};

bool writeToFile(const string& fname, const vector<u_int8_t>& data)
{
    FILE* fh;

    if ((fh = fopen(fname.c_str(), "wb")) == NULL) {
        return false;
    }

    // Write output
    if (fwrite(data.data(), 1, data.size(), fh) != data.size()) {
        fclose(fh);
        return false;
    }

    fclose(fh);

    return true;
}

int main(int argc, char* argv[])
{
    Mlxarchive mlxarch;
    return mlxarch.run(argc, argv);
}
