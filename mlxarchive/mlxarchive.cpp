
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
#include <iostream>
#include <compatibility.h>
#if __cplusplus >= 201402L || defined(_MSC_VER)
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif
#include "mlxarchive_mfa2_package_gen.h"
#include <cmdparser/cmdparser.h>
#include "mlxarchive.h"

#define IDENT            "    "
#define IDENT2           IDENT IDENT
#define IDENT3           "\t\t"

#ifdef MST_UL
#define MLXARCHIVE_EXEC  "mstarchive"
#else
#define MLXARCHIVE_EXEC  "mlxarchive"
#endif

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
#define MFA2_FILE_FLAG              "mfa2-file"
#define MFA2_FILE_FLAG_SHORT        'm'

using namespace mlxarchive;
bool writeToFile(const string&, const vector<u_int8_t>&);

/************************************
 * * Function: Mlxarchive
 * ************************************/
Mlxarchive::Mlxarchive() :
    CommandLineRequester(MLXARCHIVE_EXEC " OPTIONS"),
    _cmdParser(MLXARCHIVE_EXEC)
{
    initCmdParser();
    _binsDir  = "";
    _outFile  = "";
    _version  = "";
    _mfa2file = "";
    _printMiniDump = false;
}

/************************************
 * * Function: initCmdParser
 * ************************************/
void Mlxarchive::initCmdParser()
{
    AddDescription("Allows the user to create a file with the MFA2 extension. The new file contains several "
                    "binary files of a given firmware for different adapter cards.");
    AddOptions(HELP_FLAG,         HELP_FLAG_SHORT,     "", "Show help message and exit");
    AddOptions(VERSION_FLAG,      VERSION_FLAG_SHORT,  "version", "MFA2 version in the following format: x.x.x, if creating MFA2 file or existing MFA2 file for print its version");
    AddOptions(OUT_FILE_FLAG,     OUT_FILE_FLAG_SHORT, "out_file", "Output file");
    AddOptions(BINS_DIR_FLAG,     BINS_DIR_FLAG_SHORT, "bins_dir", "Directory with the binaries files");
    AddOptions(MFA2_FILE_FLAG,    MFA2_FILE_FLAG_SHORT, "mfa2_file", "Mfa2 file to parse");
    _cmdParser.AddRequester(this);
}

void Mlxarchive::paramValidate()
{
    std::string err = "Missing mandatory parameter: %s\n";
    std::string big_err = "Missing mandatory parameters: %s %s %s\n";
    std::string err_regex = "Bad format in: %s(%s), the format should be like: %s\n";
    boost::smatch match;
    bool status_match;
    bool success = true;
    if(!_mfa2file.empty()) {
        if(!(_binsDir.empty() && _outFile.empty() && _version.empty())) {
            fprintf(stderr, "Cannot use any parameter when using mfa2_file parameter!\n");
            exit(1);
        }
        return;
    }

    if (_binsDir.empty() && _outFile.empty()) {
        if (!_version.empty()) {
            _printMiniDump = true;
            _mfa2file = _version;
            _version.clear();
        }
        else {//all three options are empty!
            fprintf(stderr, big_err.c_str(), "bins_dir", "out_file", "version");
            success = false;
        }
    }
    else {
        if (_binsDir.empty()) {
            fprintf(stderr, err.c_str(), "bins_dir");
            success = false;
        }
        if (_outFile.empty()) {
            fprintf(stderr, err.c_str(), "out_file");
            success = false;
        }
        else {
            if (fexists(_outFile)) {
                if (!isFile(_outFile)) {
                    fprintf(stderr, "Output file: %s is expected to be a file\n", _outFile.c_str());
                }
                else {
                    fprintf(stderr, "Output file: %s already exists\n", _outFile.c_str());
                }
                success = false;
            }
        }
        if (_version.empty()) {
            fprintf(stderr, err.c_str(), "version");
            success = false;
        }
        else {
            regex version_expression("^[0-9].[0-9].[0-9]$");
            status_match = regex_match(_version, match, version_expression);
            if (!status_match) {
                fprintf(stderr, err_regex.c_str(), "version", _version.c_str(), "x.x.x");
                success = false;
            }
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
        if (_version.empty() == false) {
            cout << "Version flag cannot be specified more than once" << endl;
            return PARSE_ERROR;
        }
        _version = value;
        return PARSE_OK;
    } else if (name == OUT_FILE_FLAG) {
        if (_outFile.empty() == false) {
            cout << "Output file flag cannot be specified more than once" << endl;
            return PARSE_ERROR;
        }
        _outFile = value;
        return PARSE_OK;
    } else if (name == BINS_DIR_FLAG) {
        if (_binsDir.empty() == false) {
            cout << "Binary directory flag cannot be specified more than once" << endl;
            return PARSE_ERROR;
        }
        _binsDir = value;
        return PARSE_OK;
    } else if (name == MFA2_FILE_FLAG) {
        if (_mfa2file.empty() == false) {
            cout << "MFA2 file flag cannot be specified more than once" << endl;
            return PARSE_ERROR;
        }
        _mfa2file = value;
        return PARSE_OK;
    }
    else{
        cout << "Unknown flag specified" << endl;
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
        cerr << "Failed to parse arguments: " <<  _cmdParser.GetErrDesc() << endl;
        return 1;
    } else if (rc == PARSE_ERROR_SHOW_USAGE) {
        cerr << "Failed to parse arguments: " << _cmdParser.GetErrDesc() << endl;
        return 1;
    }
    paramValidate();
    if(_mfa2file.empty()) {
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
    } else {
        MFA2 * mfa2Pkg = MFA2::LoadMFA2Package(_mfa2file);
        if(!mfa2Pkg) {
            fprintf(stderr, "-E- Failed to parse mfa2 file %s\n", _mfa2file.c_str());
            exit(1);
        }
        if (_printMiniDump) {
            mfa2Pkg->minidump();
        }
        else {
            mfa2Pkg->dump();
        }
        delete mfa2Pkg;
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
