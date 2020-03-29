/* 
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef MLXREG_LIB_H
#define MLXREG_LIB_H

#include <vector>
#include <mtcr.h>
#include <adb_parser/adb_parser.h>
#include <dev_mgt/tools_dev_types.h>
#include <mft_utils/errmsg.h>
#include "mlxreg_exception.h"


namespace mlxreg {

typedef enum {
    MRLS_SUCCESS = 0,
    MRLS_GENERAL
} MlxRegLibStatus;

class MlxRegLib : public ErrMsg {
public:
    MlxRegLib(mfile *mf, string extAdbFile, bool isExternal = true);
    ~MlxRegLib(); // Dto'r
    /* * * * * * * * * * * * * *
    * library Getters/Setters *
    * * * * * * * * * * * * * */
    AdbInstance* findAdbNode(string name);
    AdbInstance* getAdbTable() { return _regAccessRootNode; };
    /* * * * * * * *
    * library API *
    * * * * * * * */
    string getLastErrMsg();
    MlxRegLibStatus showRegisters(std::vector<string> &regs); // Return all available register names
    MlxRegLibStatus showRegister(string regName, std::vector<AdbInstance*> &fields); // Return all fields of given register
    MlxRegLibStatus sendRegister(string regName, int method, std::vector<u_int32_t> &data); // Send register by name
    MlxRegLibStatus sendRegister(u_int16_t regId, int method, std::vector<u_int32_t> &data); // Send register by ID
    dm_dev_id_t getDevId();
    static dm_dev_id_t getDevId(mfile *mf);
    static bool isDeviceSupported(mfile *mf);
    static void isAccessRegisterSupported(mfile *mf);
    bool isAccessRegisterGMPSupported(maccess_reg_method_t reg_method);
    bool isIBDevice();
protected:
    /* Functions */
    bool isRegSizeSupported(string regName);
    int sendMaccessReg(u_int16_t regId, int method, std::vector<u_int32_t> &data);
    void initAdb(string extAdbFile);

    /* Data Members */
    mfile *_mf;
    static map<dm_dev_id_t, Adb*> _adbDBs;
    static const int RETRIES_COUNT;
    static const int SLEEP_INTERVAL;
    Adb *_adb;
    AdbInstance *_regAccessRootNode;
    AdbInstance *_regAccessUnionNode;
    std::map<string, u_int64_t>   _regAccessMap;
    bool _isExternal;
};

}
#endif /* MLXREG_LIB_H */
