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
 * mlxarchive.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <string>
#include <vector>
#include<iostream>
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
    _date     = "";
    _version  = "";
}

/************************************
 * * Function: initCmdParser
 * ************************************/
void Mlxarchive::initCmdParser()
{
    AddOptions(HELP_FLAG,         HELP_FLAG_SHORT,     "", "Show help message and exit");
    AddOptions(VERSION_FLAG,      VERSION_FLAG_SHORT,  "version", "MFA2 version in the following format: x.x.x");
    AddOptions(DATE_FLAG,         DATE_FLAG_SHORT,     "date", "Date in the following format: dd.MM.yyyy");
    AddOptions(OUT_FILE_FLAG,     OUT_FILE_FLAG_SHORT,  "out_file", "Output file");
    AddOptions(BINS_DIR_FLAG,     BINS_DIR_FLAG_SHORT, "bins_dir", "Directory with the binaries files");
    _cmdParser.AddRequester(this);
}

ParseStatus Mlxarchive::HandleOption(string name, string value)
{
    if (name == HELP_FLAG) {
        cout << _cmdParser.GetUsage();
        return PARSE_OK_WITH_EXIT;
    } else if (name == VERSION_FLAG) {
        _version = value;
        return PARSE_OK;
    } else if (name == DATE_FLAG) {
        _date = value;
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

void Mlxarchive::run(int argc, char **argv)
{
    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);
    if (rc == PARSE_OK_WITH_EXIT) {
        return;
    } else if (rc == PARSE_ERROR) {
        cout << _cmdParser.GetUsage();
        //throw MlxRegException("failed to parse arguments. %s", _cmdParser.GetErrDesc());
        return;
    } else if (rc == PARSE_ERROR_SHOW_USAGE) {
        cout << _cmdParser.GetUsage();
        //throw MlxRegException("failed to parse arguments. %s", _cmdParser.GetErrDesc());
        return;
    }
    string outputFile = _outFile;
    string content = "";
    vector<u_int8_t> buff;
    MFA2PackageGen mfa2PackageGen;
    string dir = _binsDir;
    string version = _version;
    string date = _date;

    buff.clear();
    mfa2PackageGen.generateBinFromFWDirectory(dir, version, date, buff);
    //Save output to a file
    if (!writeToFile(outputFile, buff)) {
        fprintf(stderr, "-E- Cannot write to the file %s\n",   outputFile.c_str());
        exit(1);
    }
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
    mlxarch.run(argc, argv);
}
