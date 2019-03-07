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
    MlxRegLib(mfile *mf, string extAdbFile, bool onlyKnown = true, bool isExternal = true);
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
    MlxRegLibStatus showRegisters(std::vector<string> &regs); // Return all supported register names
    MlxRegLibStatus showAllRegisters(std::vector<string> &regs); // Return all available register names
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
    std::map<string, u_int64_t> genSuppRegsList(std::map<string, u_int64_t> availableRegs);
    bool isRegAccessSupported(u_int64_t regID);
    bool isRegSizeSupported(string regName);
    int sendMaccessReg(u_int16_t regId, int method, std::vector<u_int32_t> &data);
    void initAdb(string extAdbFile);

    /* Data Members */
    mfile *_mf;
    static map<dm_dev_id_t, Adb*> _adbDBs;
    static const u_int64_t _gSupportedRegisters[];
    static const int RETRIES_COUNT;
    static const int SLEEP_INTERVAL;
    Adb *_adb;
    AdbInstance *_regAccessRootNode;
    AdbInstance *_regAccessUnionNode;
    std::map<string, u_int64_t>   _regAccessMap;
    std::map<string, u_int64_t>   _supportedRegAccessMap;
    bool _onlyKnownRegs;
    bool _isExternal;
};

}
#endif /* MLXREG_LIB_H */
