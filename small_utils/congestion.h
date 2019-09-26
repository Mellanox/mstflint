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
 *
 */

#include "cmdparser/cmdparser.h"
#include <dev_mgt/tools_dev_types.h>
#include <mtcr.h>
#include <string.h>

using namespace std;

class CongestionUI : public CommandLineRequester {
public:
    typedef enum {
        EXIT_STATUS_OK = 0,
        EXIT_STATUS_ERROR = 1,
        EXIT_STATUS_USAGE = 2,
        EXIT_STATUS_DEV_ID_ERR = 3,
        EXIT_STATUS_CAP_ERR = 4
    } exit_status_t;
    CongestionUI();
    ~CongestionUI();
    ParseStatus HandleOption(string name, string value);

    exit_status_t run(int argc, char **argv);

    void printUsage();
    void printError();
    void printSuccess();
    void printErrorNotSupported();
    string getError() { return _errorMsg; };
    string getSuccess() { return _successMsg; };

private:

    typedef enum {
        MODE_AGGRESSIVE = 0,
        MODE_DYNAMIC = 1,
        MODE_NA
    } cong_mode_t;

    typedef enum {
        ACTION_DISABLED = 0,
        ACTION_DROP = 1,
        ACTION_MARK = 2,
        ACTION_NA
    } cong_action_t;

    bool setMode(cong_mode_t mode);
    bool setAction(cong_action_t action);
    bool query();
    void initCmdParser();
    bool isDeviceSupported(dm_dev_id_t dev_id);
    string getModeString(cong_mode_t mode);
    string getActionString(cong_action_t action);

private:
    CommandLineParser _cmdParser;
    string _devname;
    cong_action_t _action;
    cong_mode_t _mode;
    mfile *_mf;
    string _errorMsg;
    string _successMsg;
    bool _query;
    int _ops;
    u_int8_t _dynamicSupp;
    u_int8_t _markCqeSupp;
    u_int8_t _markCnpSupp;
};

