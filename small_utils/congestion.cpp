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

#include "congestion.h"
#include "reg_access/reg_access.h"
#include <dev_mgt/tools_dev_types.h>
#include <common/tools_version.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

enum {
    BIT_TX_LOSSY_OPER = 1,
    BIT_TX_SENSE = 1 << 3,
    BIT_MARK_TX_CQE = 1 << 4,
    BIT_MARK_TX_CNP = 1 << 5,
};

int main(int argc, char **argv)
{
    CongestionUI congestObject;
    CongestionUI::exit_status_t exit_code = congestObject.run(argc, argv);
    int rc = 0;
    switch(exit_code) {
    case CongestionUI::EXIT_STATUS_OK:
        congestObject.printSuccess();
        break;
    case CongestionUI::EXIT_STATUS_ERROR:
        congestObject.printError();
        rc = 1;
        break;
    case CongestionUI::EXIT_STATUS_USAGE:
        congestObject.printUsage();
        rc = 1;
        break;
    case CongestionUI::EXIT_STATUS_DEV_ID_ERR:
        congestObject.printErrorNotSupported();
        rc = 1;
        break;
    case CongestionUI::EXIT_STATUS_CAP_ERR:
        congestObject.printErrorNotSupported();
        rc = 1;
        break;
    }
    return rc;
}


CongestionUI::CongestionUI() :
            CommandLineRequester("mstcongestion [OPTIONS]"),
            _cmdParser("mstcongestion")
{
    _devname = "";
    _mf = NULL;
    _action = ACTION_NA;
    _mode = MODE_NA;
    _query = false;
    _ops = 0;
    _dynamicSupp = 0;
    _markCqeSupp = 0;
    _markCnpSupp = 0;
    initCmdParser();
}

CongestionUI::~CongestionUI()
{
    if (_mf) {
        mclose(_mf);
        _mf = NULL;
    }
}

void CongestionUI::initCmdParser()
{

    AddOptions("device", 'd', "<PCI DEVICE>", "Mellanox PCI device address", false, true);
    AddOptions("mode", ' ', "<MODE>", "Set Mode, options are: [aggressive | dynamic]");
    AddOptions("action", ' ', "<ACTION>", "Set Action, options are: [disabled | drop | mark]");
    AddOptions("query", 'q', "", "Query congestion");
    AddOptions("help", 'h', "", "Show help message and exit");
    AddOptions("version", 'v', "", "Show version and exit");
    AddDescription("mstcongestion is a utility for configuring Mellanox device's receive congestion handling.");
    _cmdParser.AddRequester(this);
}

bool CongestionUI::isDeviceSupported(dm_dev_id_t devid)
{ // Supported devices are CX4+
    return (dm_is_5th_gen_hca(devid) && !dm_is_connectib(devid));
}

ParseStatus CongestionUI::HandleOption(string name, string value)
{
    if (name == "device") {
        _devname = value;
    } else if (name == "mode" ) {
        _ops++;
        if (value == "aggressive") {
            _mode = MODE_AGGRESSIVE;
        } else if (value == "dynamic") {
            _mode = MODE_DYNAMIC;
        } else {
            _errorMsg = "Invalid mode, options are: [aggressive | dynamic]";
            return PARSE_ERROR;
        }
    } else if (name == "action") {
        _ops++;
        if (value == "disabled") {
            _action = ACTION_DISABLED;
        } else if (value == "drop") {
            _action = ACTION_DROP;
        } else if (value == "mark") {
            _action = ACTION_MARK;
        } else {
            _errorMsg = "Invalid action, options are: [disabled | drop | mark]";
            return PARSE_ERROR;
        }
    } else if (name == "help") {
        printUsage();
        return PARSE_OK_WITH_EXIT;
    } else if (name == "version") {
        print_version_string("mstcongestion", NULL);
        return PARSE_OK_WITH_EXIT;
    } else if (name == "query") {
        _ops++;
        _query = true;
    } else {
        _errorMsg = "Invalid option: " + name;
        return PARSE_ERROR;
    }
    return PARSE_OK;
}

CongestionUI::exit_status_t CongestionUI::run(int argc, char** argv)
{
    ParseStatus rc = _cmdParser.ParseOptions(argc, argv);
    if (rc == PARSE_OK && _devname == "") {
        _errorMsg = "Missing device.";
        rc = PARSE_ERROR;
    }

    if (rc == PARSE_OK_WITH_EXIT) {
        return EXIT_STATUS_OK;
    } else if (rc == PARSE_ERROR) {
        if (_errorMsg == "") {
            _errorMsg = "Failed while parsing the arguments.";
        }
        return EXIT_STATUS_USAGE;
    } else if (rc == PARSE_ERROR_SHOW_USAGE) {
        return EXIT_STATUS_USAGE;
    }

    _mf = mopen(_devname.c_str());
    if (!_mf) {
        _errorMsg = "Failed to open device: " + _devname;
        return EXIT_STATUS_ERROR;
    }
    // Check supported device 
    dm_dev_id_t devID = DeviceUnknown;
    u_int32_t hwDevID = 0;
    u_int32_t hwChipRev = 0;
    dm_get_device_id(_mf, &devID, &hwDevID, &hwChipRev);
    if (!isDeviceSupported(devID))
    {
        _errorMsg = "mstcongestion is supported for CX4+ devices.";
        return EXIT_STATUS_DEV_ID_ERR;
    }

    struct tools_open_mcam mcam;
    memset(&mcam, 0, sizeof(mcam));
    reg_access_status_t status = reg_access_mcam(_mf, REG_ACCESS_METHOD_GET, &mcam);
    if (status) {
        _errorMsg = "mstcongestion is not supported on this device (Failed to get device capabilities).";
        return EXIT_STATUS_CAP_ERR;
    }
    u_int8_t caps = mcam.mng_feature_cap_mask[14];
    _dynamicSupp = caps & 0x2;
    _markCqeSupp = caps & 0x4;
    _markCnpSupp = caps & 0x8;
    if (_ops != 1) {
        _errorMsg = "Please choose one operation.";
        return EXIT_STATUS_ERROR;
    }
    bool op_ret = true;
    if (_mode != MODE_NA) {
        op_ret = setMode(_mode);
    } else if (_action != ACTION_NA) {
        op_ret = setAction(_action);
    } else if (_query) {
        op_ret = query();
    }
    return op_ret? EXIT_STATUS_OK : EXIT_STATUS_ERROR;
}


bool CongestionUI::setMode(cong_mode_t mode)
{
    if (!_dynamicSupp) {
        _errorMsg = "Dynamic overflow is not supported.";
        return false;
    }
    _successMsg = "Mode was set successfully.";
    struct reg_access_hca_mpegc_reg mpegc;
    memset(&mpegc, 0, sizeof (mpegc));
    mpegc.tx_overflow_sense = (int)mode;
    mpegc.field_select |= BIT_TX_SENSE;
    reg_access_status_t status = reg_access_mpegc(_mf, REG_ACCESS_METHOD_SET, &mpegc);
    if (status) {
        _errorMsg = string(reg_access_err2str(status));
        return false;
    }
    return true;
}

bool CongestionUI::setAction(cong_action_t action)
{
    _successMsg = "Action was set successfully.";
    struct reg_access_hca_mpegc_reg mpegc;
    memset(&mpegc, 0, sizeof (mpegc));
    mpegc.tx_lossy_overflow_oper = (int)action;
    mpegc.field_select |= BIT_TX_LOSSY_OPER;
    if (action == ACTION_MARK) {
        if (_markCqeSupp) {
            mpegc.field_select |= BIT_MARK_TX_CQE;
            mpegc.mark_cqe = 1;
        }
        if (_markCnpSupp) {
            mpegc.field_select |= BIT_MARK_TX_CNP;
            mpegc.mark_cnp = 1;
        }
        if(!mpegc.mark_cnp && !mpegc.mark_cqe) {
            _errorMsg = "Mark action is not supported!";
            return false;
        }
    }
    reg_access_status_t status = reg_access_mpegc(_mf, REG_ACCESS_METHOD_SET, &mpegc);
    if (status) {
        _errorMsg = string(reg_access_err2str(status));
        return false;
    }
    return true;
}

bool CongestionUI::query()
{
    struct reg_access_hca_mpegc_reg mpegc;
    memset(&mpegc, 0, sizeof (mpegc));
    reg_access_status_t status = reg_access_mpegc(_mf, REG_ACCESS_METHOD_GET, &mpegc);
    if (status) {
        _errorMsg = string(reg_access_err2str(status));
        return false;
    }
    printf("Action: %s\nMode: %s\n", getActionString((cong_action_t)mpegc.tx_lossy_overflow_oper).c_str(),
           getModeString((cong_mode_t)mpegc.tx_overflow_sense).c_str());
    return true;
}


string CongestionUI::getModeString(cong_mode_t mode)
{
    switch (mode) {
    case MODE_AGGRESSIVE:
        return "aggressive";
    case MODE_DYNAMIC:
        return "dynamic";
    default:
        return "N/A";
    }
}

string CongestionUI::getActionString(cong_action_t action)
{
    switch (action) {
    case ACTION_DISABLED:
        return "disabled";
    case ACTION_DROP:
        return "drop";
    case ACTION_MARK:
        return "mark";
    default:
        return "N/A";
    }
}

void CongestionUI::printUsage()
{
    if(getError() != "") {
        cout << "-E- Usage error: " << getError() << endl;
    }
    cout << _cmdParser.GetUsage() << endl;
}

void CongestionUI::printError()
{
    cout << "-E- Failed to perform the operation: " << getError() << endl;
}

void CongestionUI::printErrorNotSupported()
{
    cout << "-E- Not supported device: " << getError() << endl;
}

void CongestionUI::printSuccess()
{
    if (getSuccess() != "") {
        cout << "-I- " << getSuccess() << endl;
    }
}
