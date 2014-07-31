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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>

#include <tools_dev_types.h>

#include "mlxcfg_ui.h"

// Signal handler section
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
    printf("\n Received signal %d.\n", signum);
    fflush(stdout);
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
            exit(MLX_CFG_ERROR);
        }
    }
}

//End of signal handler section.


#define MAX_ERR_STR_LEN 1024
#define MAX_BUF_SIZE 1024
#define PRE_ERR_MSG "-E-"

#ifdef MST_UL
    #define NO_DEV_ERR "No devices found."
#else
    #define NO_DEV_ERR "No devices found, mst might be stopped. You may need to run 'mst start' to load MST modules. "
#endif

std::string MlxCfgParams::param2str[Mcp_Last]= {"SRIOV_EN", "NUM_OF_VFS", "WOL_MAGIC_EN_P1", "WOL_MAGIC_EN_P2",\
                                                "LINK_TYPE_P1", "LINK_TYPE_P2", "LOG_BAR_SIZE"};

u_int32_t MlxCfgParams::getParamVal(mlxCfgParam p)
{
    for (std::vector<cfgInfo>::iterator it = params.begin() ; it != params.end() ; it++) {
        if (it->first == p) {
            return it->second;
        }
    }
    return MLXCFG_UNKNOWN;
}

mlxCfgStatus MlxCfg::err(bool report, const char* fmt, ...)
{
     va_list  args;
     va_start(args, fmt);
     char errBuff[MAX_ERR_STR_LEN] = {0};

     if (vsnprintf(errBuff, MAX_ERR_STR_LEN, fmt, args) >= MAX_ERR_STR_LEN) {
         strcpy(&errBuff[MAX_ERR_STR_LEN - 5], "...");
    }
     _errStr = errBuff;
     if (report) {
         fprintf(stdout,PRE_ERR_MSG" %s\n", _errStr.c_str());
     }
     va_end(args);
     return MLX_CFG_ERROR;
}

void MlxCfg::printErr()
{
    fprintf(stdout,PRE_ERR_MSG" %s\n", _errStr.c_str());
}


bool MlxCfg::askUser(const char* question)
{
if (question == NULL) {
     printf("\n Do you want to continue ? (y/n) [n] : ");
 } else {
     printf("\n %s ? (y/n) [n] : ", question);
 }

 if (_mlxParams.yes)
     printf("y\n");
 else {
     char ansbuff[32];
     ansbuff[0] = '\0';
     fflush(stdout);
     int cnt=fscanf(stdin, "%30s", ansbuff);
     (void)cnt; // avoid warnings

     if (  strcasecmp(ansbuff, "y") &&
           strcasecmp(ansbuff, "yes"))  {

         err(false, "Aborted by user.");
         return false;
     }
 }
 return true;
}

mlxCfgStatus MlxCfg::queryDevsCfg()
{
    bool shouldFail= false;
    if (_mlxParams.device.length()) {
        if (queryDevCfg(_mlxParams.device.c_str())) {
            printErr();
            shouldFail= true;
        }
    } else {
        int  numOfDev;
        dev_info* dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL) {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0) {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        //printf("-D- num of dev: %d , 1st dev : %s\n", numOfDev, buf);
        dev_info  *devPtr = dev;
        char pcibuf[32]= {0};

        for(int i=0 ; i < numOfDev ; i++) {
            snprintf(pcibuf,32, "%04x:%02x:%02x.%x", devPtr->pci.domain, devPtr->pci.bus,\
                    devPtr->pci.dev, devPtr->pci.func);
            if (queryDevCfg(devPtr->pci.conf_dev, pcibuf, i+1)){
                printErr();
                shouldFail = true;
            }
            devPtr++;
        }
        mdevices_info_destroy(dev, numOfDev);
    }
    return shouldFail? MLX_CFG_ERROR : MLX_CFG_OK;
}

static void printParam(u_int32_t param)
{
    if (param == MLXCFG_UNKNOWN) {
            printf("%-8s", "N/A");
        } else {
            printf("%-8d", param);
        }
    return;
}

static void printOneParam(const char* name, u_int32_t currVal, bool printNewCfg=false, u_int32_t newVal= MLXCFG_UNKNOWN)
{
    printf("         %-16s", name);
    printParam(currVal);
    if (printNewCfg) {
        if (newVal == MLXCFG_UNKNOWN) {
            printParam(currVal);
        } else {
            printf("%-8d", newVal);
        }
    }
    printf("\n");
    return;

}
const char* MlxCfg::getDeviceName(const char* dev)
{
    mfile* mf;
    dm_dev_id_t dev_type;
    u_int32_t dev_id;
    u_int32_t chip_rev;

    mf = mopen(dev);
    if (!mf) {
        return "";
    }
    if (dm_get_device_id(mf, &dev_type, &dev_id, &chip_rev)) {
        mclose(mf);
        return "";
    }
    mclose(mf);
    return dm_dev_type2str(dev_type);
}

mlxCfgStatus MlxCfg::queryDevCfg(const char* dev,const char* pci, int devIndex, bool printNewCfg)
{
    MlxCfgOps ops;
    bool rc;
    bool failedToGetCfg = false;
    bool nothingSupported = true;
    (void) pci;
    // print opening
    printf("\nDevice #%d:\n", devIndex);
    printf("----------\n\n");
    printf("%-16s%-16s\n", "Device type:", getDeviceName(dev));
    printf("%-16s%-16s\n", "PCI device:", dev);
    // TODO : get this info
    //printf("%-16s%-16s\n", "Part Number:", "123456");
    //printf("%-16s%-16s\n", "Psid:", "78901111");
    printf("\n");

    rc = ops.open(dev);
    if (rc) {
        err(false, "Failed to query device: %s. %s", dev, ops.err());
        return MLX_CFG_ERROR_EXIT;
    }

    //print configuration Header
    printf("%-16s%16s","Configurations:","Current");
    if (printNewCfg) {
        printf(" %s", "New");
    }
    printf("\n");

    for (int p = (int)Mcp_Sriov_En ; p < (int)Mcp_Last; ++p) {
        if (p == Mcp_Log_Bar_Size) { // we dont support bar size atm
            continue;
        }
        if (!ops.supportsParam((mlxCfgParam)p)) {
            continue;
        }
        nothingSupported= false;
        u_int32_t currentParam = MLXCFG_UNKNOWN ;
        u_int32_t newParam = _mlxParams.getParamVal((mlxCfgParam)p);
        rc = ops.getCfg((mlxCfgParam)p, currentParam);
        if (rc) {
            failedToGetCfg = true;
            printf("         %-16s%-16s %s\n", MlxCfgParams::param2str[p].c_str(), "failed to get current configuration.",\
                    ops.err());
            err(false, "Failed to query device configuration");
        } else {
            printOneParam(MlxCfgParams::param2str[p].c_str(), currentParam, printNewCfg, newParam);
        }
    }
    if (nothingSupported) {
        err(false, "Device Doesn't support any configuration changes.");
        return MLX_CFG_ERROR_EXIT;
    }
    return failedToGetCfg ? MLX_CFG_ERROR : MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::setDevCfg()
{
    if (queryDevCfg(_mlxParams.device.c_str(), NULL, 1, true) == MLX_CFG_ERROR_EXIT){
        printErr();
        return MLX_CFG_ERROR;
    }
    // even if there is problem fetching the current cfg we will attempt to write the new info
    // if the user agrees

    if (_mlxParams.force) {
        printf("\n-W- Force flag specified, the validity of the Parameters will not be checked !\n");
        printf("-W- Incorrect configuration might yield unexpected results. running in this mode is not recommended.");
    }
    // ask user
    if(!askUser("Apply new Configuration?")) {
        printErr();
        return MLX_CFG_ABORTED;
    }

    // write cfgs
    MlxCfgOps ops;
    bool rc;

    rc = ops.open(_mlxParams.device.c_str());
    if (rc) {
        return err(false, "Failed to set configuration on device: %s. %s", _mlxParams.device.c_str(), \
               ops.err());
    }
    printf("Applying... ");
    // set Configuration
    rc = ops.setCfg(_mlxParams.params, _mlxParams.force);
    if (rc) {
        printf("Failed!\n");
        err(true, "Failed to set configuration: %s", ops.err());
        return MLX_CFG_ERROR;
    }

    printf("Done!\n");
    printf("-I- Please reboot machine to load new configurations.\n");
    return MLX_CFG_OK;

}

mlxCfgStatus MlxCfg::resetDevsCfg()
{
    // check if a single device was specified and apply reset for this device only
    if (_mlxParams.device.length()) {
        char buff[256] = {0};
        snprintf(buff,256,"Reset configuration for device %s? ", _mlxParams.device.c_str());
        if (!askUser(buff)){
            printErr();
            return MLX_CFG_ABORTED;
        }

        printf("Applying... ");
        if (resetDevCfg(_mlxParams.device.c_str())) {
            printf("Failed!\n");
            printErr();
            return MLX_CFG_ERROR;
        }
    } else {
        // reset all devices.
        int  numOfDev;
        dev_info* dev = mdevices_info(MDEVS_TAVOR_CR, &numOfDev);

        if (dev == NULL) {
            return err(true, "Failed to get devices.");
        }
        if (numOfDev == 0) {
            mdevices_info_destroy(dev, numOfDev);
            return err(true, NO_DEV_ERR);
        }
        if (!askUser("Reset configuration for all devices? ")){
            printErr();
            mdevices_info_destroy(dev, numOfDev);
            return MLX_CFG_ABORTED;
        }
        printf("Applying... ");

        dev_info *devPtr = dev;
        bool shouldFail= false;

        for(int i=0 ; i < numOfDev ; i++) {
            if (resetDevCfg(devPtr->pci.conf_dev)){
                shouldFail = true;
            }
            devPtr++;

        }
        mdevices_info_destroy(dev, numOfDev);
        if (shouldFail) {
            printf("Failed!\n");
            return MLX_CFG_ERROR;
        }

    }
    // done successfully
    printf("Done!\n");
    printf("-I- Please reboot machine to load new configurations.\n");
    return MLX_CFG_OK;
}

mlxCfgStatus MlxCfg::resetDevCfg(const char* dev)
{
    MlxCfgOps ops;
    bool rc;

    rc = ops.open(dev);
    if (rc) {
        return err(false, "Failed to open device: %s. %s", dev, ops.err());
    }

    // reset cfg
    rc = ops.invalidateCfgs();
    if (rc) {
        return err(false, "failed to reset configurations. %s", ops.err());
    }

    return MLX_CFG_OK;
}


mlxCfgStatus MlxCfg::execute(int argc, char* argv[])
{
    mlxCfgStatus rc = parseArgs(argc, argv);
    if (rc) {
        if (rc == MLX_CFG_OK_EXIT) {
            rc = MLX_CFG_OK;
        } else {
            printUsage();
        }
        return rc;
    }
    //return test(_mlxParams.device.c_str());
    mlxCfgStatus ret;
    switch (_mlxParams.cmd) {

    case Mc_Query:
        ret = queryDevsCfg();
        break;
    case Mc_Set:
        ret = setDevCfg();
        break;
    case Mc_Reset:
        ret = resetDevsCfg();
        break;
    default:
        // should not reach here.
        return err(true, "invalid command.");
    }
    return ret;
}

mlxCfgStatus MlxCfg::test(const char* dev)
{
    bool rc;
    MlxCfgOps ops;
    rc = ops.open(dev);
    if (rc) {
        return err(true, "Failed to open device: %s. %s", dev, ops.err());
    }
    u_int32_t val;
    rc =ops.invalidateCfgs();
    printf("after invalidate all : rc = %d\n", rc);
    rc =ops.getCfg(Mcp_Wol_Magic_En_P1, val);
    printf("get sriov_en get before set : rc = %d , val = %d\n", rc,val);
    rc = ops.setCfg(_mlxParams.params);
    printf("get sriov_en set : rc = %d , val = %d\n", rc,val);
    rc =ops.getCfg(Mcp_Wol_Magic_En_P1, val);
    printf("get sriov_en get after set : rc = %d , val = %d\n", rc,val);
    if (rc) {
        printf("-D- %s\n",ops.err());
    }
    return MLX_CFG_OK;
}


int main(int argc, char* argv[])
{
    try
    {
    initHandler();
    MlxCfg mc;
    return mc.execute(argc, argv);
    }
    catch (std::exception& e)
    {
        printf("-E- %s\n", e.what());
        return MLX_CFG_ERROR;
    }
}


