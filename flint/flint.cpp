/*
 *
 * flint.cpp - FLash INTerface
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

#include <iostream>
#include <signal.h>

#include "flint.h"

//Globals:
Flint* gFlint = NULL;
extern FILE* flint_log_fh;
//signal handler section

#define BURN_INTERRUPTED 0x1234

void TerminationHandler(int signum);

#ifdef __WIN__
#include <windows.h>

static BOOL CtrlHandler( DWORD fdwCtrlType )
{
    switch( fdwCtrlType )
    {
      // Handle the CTRL-C signal.
      case CTRL_C_EVENT:
      // CTRL-CLOSE: confirm that the user wants to exit.
      case CTRL_CLOSE_EVENT:
      // Pass other signals to the next handler.
      case CTRL_BREAK_EVENT:
      case CTRL_LOGOFF_EVENT:
      case CTRL_SHUTDOWN_EVENT:
    	  TerminationHandler(SIGINT);
          return TRUE;

      default:
        return FALSE;
    }
 }

#endif


void TerminationHandler(int signum)
{
    static volatile sig_atomic_t fatal_error_in_progress = 0;

    if (fatal_error_in_progress) {
        raise (signum);
    }
    fatal_error_in_progress = 1;

    signal (signum, SIG_DFL);
    write_result_to_log(BURN_INTERRUPTED, "");
    close_log();
    if (gFlint != NULL) {
        printf("\n Received signal %d. Cleaning up ...\n", signum);
        fflush(stdout);
        //sleep(1); // Legacy from the Old Flint
        delete gFlint;
        gFlint = NULL;
        printf(" Done.\n");
    }
    raise(signum);
}


void initHandler()
{
#ifdef __WIN__
#define SIGNAL_NUM 3
    int signalList[SIGNAL_NUM] = {SIGINT, SIGTERM, SIGABRT};
    SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, true );
#else
#define SIGNAL_NUM 4
    int signalList[SIGNAL_NUM] = {SIGINT, SIGTERM, SIGPIPE, SIGHUP};
#endif

    //set the signal handler
    for (int i=0; i < SIGNAL_NUM ; i++) {
        void (*prevFunc)(int);
        prevFunc = signal(signalList[i],TerminationHandler);
        if (prevFunc == SIG_ERR) {
            printf("-E- failed to set signal Handler.");
            exit(FLINT_FAILED);
        }
    }
}

//End of signal handler section.


map_sub_cmd_t_to_subcommand Flint::initSubcommandMap()
{
    map_sub_cmd_t_to_subcommand cmdMap;
    cmdMap[SC_Burn] = new BurnSubCommand();
    cmdMap[SC_Query] = new QuerySubCommand();
    cmdMap[SC_Verify] = new VerifySubCommand();
    cmdMap[SC_Swreset] = new SwResetSubCommand();
    cmdMap[SC_ResetCfg] = new ResetCfgSubCommand();
    cmdMap[SC_Brom] = new BromSubCommand();
    cmdMap[SC_Drom] = new DromSubCommand();
    cmdMap[SC_Rrom] = new RromSubCommand();
    cmdMap[SC_Qrom] = new RomQuerySubCommand();
    cmdMap[SC_Bb] = new BbSubCommand();
    cmdMap[SC_Sg] = new SgSubCommand();
#ifndef EXTERNAL
    cmdMap[SC_Smg] = new SmgSubCommand();
    cmdMap[SC_Set_Vpd] = new SetVpdSubCommand();
    cmdMap[SC_Fix_Img] = new FiSubCommand();
#endif
    cmdMap[SC_Sv] = new SvSubCommand();
    cmdMap[SC_Ri] = new RiSubCommand();
    cmdMap[SC_Dc] = new DcSubCommand();
    cmdMap[SC_Dh] = new DhSubCommand();
    cmdMap[SC_Set_Key] = new SetKeySubCommand();
    cmdMap[SC_Hw_Access] = new HwAccessSubCommand();
    cmdMap[SC_Hw] = new HwSubCommand();
    cmdMap[SC_Erase] = new EraseSubCommand();
    cmdMap[SC_Rw] = new RwSubCommand();
    cmdMap[SC_Ww] = new WwSubCommand();
    cmdMap[SC_Wwne] = new WwneSubCommand();
    cmdMap[SC_Wbne] = new WbneSubCommand();
    cmdMap[SC_Wb] = new WbSubCommand();
    cmdMap[SC_Rb] = new RbSubCommand();
    return cmdMap;
}

void Flint::deInitSubcommandMap(map_sub_cmd_t_to_subcommand cmdMap)
{
    for (map_sub_cmd_t_to_subcommand::iterator it = cmdMap.begin(); it != cmdMap.end(); ++it)
        delete it->second;
}


Flint::Flint():
        CommandLineRequester(FLINT_DISPLAY_NAME" [OPTIONS] <command> [Parameters]"),
        _flintParams(),
        _cmdParser(FLINT_DISPLAY_NAME" - Flash Interface"),
        _subcommands(initSubcommandMap())
{
    initCmdParser();
}

Flint::~Flint()
{
    deInitSubcommandMap(_subcommands);
    if (_flintParams.flash_params.type_name) {
        delete[] _flintParams.flash_params.type_name;
    }
}

FlintStatus Flint::run(int argc, char* argv[])
{
    //Step1 parse input
    //There are some memory allocations parseCmdLine
    ParseStatus status;
    try {
        status = this->parseCmdLine(argc, argv);;
    } catch (exception& e) {
        cout << "-E- " << e.what() << endl;
        return FLINT_FAILED;
    }
    if (status == PARSE_OK_WITH_EXIT) {
        return FLINT_SUCCESS;
    } else if (status == PARSE_ERROR || status == PARSE_ERROR_SHOW_USAGE) {
        if (string(_cmdParser.GetErrDesc()).length() > 0) {
            cout << "-E- " << this->_cmdParser.GetErrDesc() << endl;
        }
        return FLINT_FAILED;
    }

    if (_flintParams.cmd == SC_No_Cmd && !_flintParams.clear_semaphore)
    {
        cout << FLINT_NO_COMMAND_ERROR << endl;
        return FLINT_FAILED;
    }
    if (_flintParams.clear_semaphore) {
        if (_flintParams.cmd != SC_No_Cmd) {
            printf(FLINT_CLEAR_SEM_CMD_ERROR);
            return FLINT_FAILED;
        }
        _subcommands[SC_Clear_Sem] = new ClearSemSubCommand();
        _flintParams.cmd = SC_Clear_Sem;
    }
    // Step 2 save argv as a single cmd string in flint params for the log functionallity
    for(int i=0; i<argc; i++) {
        _flintParams.fullCmd = _flintParams.fullCmd + argv[i] + " ";
    }
    //TODO: Step 3 check flintParams for contradictions?
    //Step 4 execute command from the correct subcommand class
    _subcommands[_flintParams.cmd]->setParams(_flintParams);
    return _subcommands[_flintParams.cmd]->executeCommand();
}


int main(int argc, char* argv[])
{
    initHandler();
    try
    {
    gFlint = new Flint();
    FlintStatus rc = gFlint->run(argc, argv);
    if (gFlint) {
        delete gFlint;
        gFlint = NULL;
       }
    return rc;
    }
    catch (std::exception& e)
    {
        cout<<"-E- "<<e.what()<<endl;
        return FLINT_FAILED;
    }
}
