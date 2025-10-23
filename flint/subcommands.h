/*
 *
 * subcommands.h - FLash INTerface
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef __SUBCOMMANDS_H__
#define __SUBCOMMANDS_H__

#define MAX_PASSWORD_LEN 256

#include <string>
#include <memory>
#include <map>

#include <tools_layouts/tools_open_layouts.h>
#include "tools_layouts/image_layout_layouts.h"
#include "flint_params.h"
#include "mlxfwops/lib/fw_ops.h"
#include "mlxfwops/lib/fs_checks.h"
#include "err_msgs.h"
#include "mlxfwops/lib/fs_pldm.h"

using namespace std;

#ifndef NO_MSTARCHIVE
#include "mlxarchive/mlxarchive_mfa2_package_gen.h"
#include "mlxarchive/mlxarchive_mfa2_utils.h"
using namespace mfa2;
#endif
// we might need to close the log from the main program in case of interrupt
void close_log();
void print_time_to_log();
int print_line_to_log(const char* format, ...);
int write_cmd_to_log(char* av[], int ac, CommandType cmd, bool write = true);
int write_result_to_log(int is_failed, const char* err_msg, bool write = true);

typedef enum what_to_ver
{
    Wtv_Img,
    Wtv_Dev,
    Wtv_Dev_And_Img,
    Wtv_Dev_Or_Img,
    Wtv_Uninitilized
} what_to_ver_t;
/*Subcommand classes:*/

#define FLINT_ERR_LEN 1024

class SubCommand
{
protected:
    FwOperations* _fwOps;
    FwOperations* _imgOps;
    FBase* _io;

    what_to_ver_t _v;
    int _maxCmdParamNum;
    int _minCmdParamNum;
    FlintParams _flintParams;
    // info about the Subcommand
    string _name;
    string _desc;
    string _extendedDesc;
    string _flagLong;
    string _flagShort;
    string _param;
    string _paramExp;
    string _example;
    char _errBuff[FLINT_ERR_LEN];
    sub_cmd_t _cmdType;
    bool _mccSupported;
    bool _imageReactivation;
#ifndef NO_MSTARCHIVE
    MFA2* _mfa2Pkg;
#endif
    // Methods that are commonly used in the various subcommands:
    // TODO: add middle classes and segregate as much of these common methods between these classes

    virtual bool verifyParams() { return true; };
    bool basicVerifyParams();
    void initDeviceFwParams(char* errBuff, FwOperations::fw_ops_params_t& fwParams);
    FlintStatus openOps(bool ignoreSecurityAttributes = false, bool ignoreDToc = false);
    FlintStatus openIo();
    virtual FlintStatus preFwOps(bool ignoreSecurityAttributes = false, bool ignoreDToc = false);
    virtual FlintStatus preFwAccess();

    bool getRomsInfo(FBase* io, roms_info_t& romsInfo);
    void displayOneExpRomInfo(const rom_info_t& info);
    void displayExpRomInfo(const roms_info_t& romsInfo, const char* preStr);
    string getExpRomVerStr(const rom_info_t& info);
    string getRomProtocolStr(u_int8_t proto);
    string getRomSuppCpuStr(u_int8_t suppCpu);
    u_int32_t getUserChoice(u_int32_t maximumValue);
    static int verifyCbFunc(char* str);
    static int CbCommon(int completion, char* preStr, char* endStr = NULL);
    static int burnCbFs2Func(int completion);
    static int burnCbFs3Func(int completion);
    static int advProgressFunc(int completion, const char* stage, prog_t type, int* unknownProgress);
    static int burnBCbFunc(int completion);
    static int vsdCbFunc(int completion);
    static int setKeyCbFunc(int completion);
    static int bromCbFunc(int completion);
    static int dromCbFunc(int completion);
    static int wbCbFunc(int completion);
    static int resetCfgCbFunc(int completion);
    
    bool printGuidLine(guid_t* new_guids, guid_t* old_guids, int guid_index);
    bool printMacLine(guid_t* new_guids, guid_t* old_guids, int mac_index);
    bool printGUIDsFunc(guid_t guids[GUIDS],
                        guid_t macs[MACS],
                        guid_t old_guids[GUIDS],
                        guid_t old_macs[MACS],
                        bool print_guids,
                        bool print_macs,
                        int portNum,
                        bool old_guid_fmt);
    bool reportGuidChanges(guid_t* new_guids,
                           guid_t* new_macs,
                           guid_t* old_guids,
                           guid_t* old_macs,
                           bool printGuids,
                           bool printMacs,
                           int guidNum);
    bool checkGuidsFlags(u_int16_t devType,
                         u_int8_t fwType,
                         bool guidsSpecified,
                         bool macsSpecified,
                         bool uidSpecified,
                         bool ibDev,
                         bool ethDev);
    void printMissingGuidErr(bool ibDev, bool ethDev);

    bool extractUIDArgs(std::vector<string>& cmdArgs, u_int16_t numOfGuids[2], u_int8_t stepSize[2]);
    bool extractValuesFromString(string valStr, u_int16_t values[2], string origArg);
    bool extractValuesFromString(string valStr, u_int8_t values[2], string origArg);
    bool extractValuesFromStringAux(string valStr, u_int32_t values[2], string origArg);
    bool getGUIDFromStr(string str, guid_t& guid, string prefixErr = "");
    bool getPasswordFromUser(const char* preStr, char buffer[MAX_PASSWORD_LEN + 1]);
    bool askUser(const char* question = NULL, bool printAbrtMsg = true);

    bool isCmdSupportLog();
    void openLog();
    inline void closeLog() { close_log(); }
    // print errors to an err buff, log if needed and stdout
    void reportErr(bool shouldPrint, const char* format, ...);
    bool readFromFile(const string& filePath, std::vector<u_int8_t>& buff);
    bool getFileSize(const string& filePath, long& fileSize);
    bool writeToFile(string filePath, const std::vector<u_int8_t>& buff);
    FlintStatus writeImageToFile(const char* file_name, u_int8_t* data, u_int32_t length);
    
    bool dumpFile(const char* confFile, std::vector<u_int8_t>& data, const char* sectionName);
    bool unzipDataFile(std::vector<u_int8_t> data, std::vector<u_int8_t>& newData, const char* sectionName);
    const char* fwImgTypeToStr(u_int8_t fwImgType);
    FlintStatus UnlockDevice(FwOperations*);
    FlintStatus LockDevice(FwOperations*);
    void ClearGuidStruct(FwOperations::sg_params_t& sgParams);
    bool stringsCommaSplit(string str, std::vector<u_int32_t>& deviceIds);

public:
    SubCommand() :
        _fwOps(NULL),
        _imgOps(NULL),
        _io(NULL),
        _v(Wtv_Uninitilized),
        _maxCmdParamNum(-1),
        _minCmdParamNum(-1),
        _mccSupported(false),
        _imageReactivation(false)
#ifndef NO_MSTARCHIVE
        ,
        _mfa2Pkg(NULL)
#endif
    {
        _cmdType = SC_No_Cmd;
        memset(_errBuff, 0, sizeof(_errBuff));
    }
    virtual ~SubCommand();
    virtual FlintStatus executeCommand() = 0;
    virtual void cleanInterruptedCommand() {} // by default do nothing
    inline void setParams(const FlintParams& flintParams) { _flintParams = flintParams; }
    inline string& getName() { return this->_name; }
    inline string& getDesc() { return this->_desc; }
    inline string& getExtDesc() { return this->_extendedDesc; }
    inline string& getFlagL() { return this->_flagLong; }
    inline string& getFlagS() { return this->_flagShort; }
    inline string& getParam() { return this->_param; }
    inline string& getParamExp() { return this->_paramExp; }
    inline string& getExample() { return this->_example; }
};

class BurnSubCommand : public SubCommand
{
private:

    enum class CableBurnFlow
    {
        Burn3rdParty,
        Unknown
    };

    u_int8_t _fwType;
    fw_info_t _devInfo;
    fw_info_t _imgInfo;
    FwOperations::ExtBurnParams _burnParams;
    bool _devQueryRes;
    bool _shouldSkip;
    int _unknownProgress; // used to trace the progress of unknown progress.
    FwCompsMgr* fwCompsAccess;
    FlintStatus burnPldmComp(FsPldmOperations* pldmOps, string& componentType);
    FlintStatus burnFs3();
    FlintStatus burnFs2();
    bool checkFwVersion(bool CreateFromImgInfo = true,
                        u_int16_t fw_ver0 = 0,
                        u_int16_t fw_ver1 = 0,
                        u_int16_t fw_ver2 = 0);
    bool checkPSID();
    void updateBurnParams();
    bool dealWithExpRom();
    bool checkMatchingExpRomDevId(const fw_info_t& info);
    bool dealWithGuids();
    bool dealWithVSD();
    FlintStatus burnMFA2();
    FlintStatus burnMFA2LiveFish(dm_dev_id_t devid_t);
    FlintStatus burnCongestionControl();
    bool verifyMFA2Params(bool IsLiveFish);
    FlintStatus BurnLinkX(string deviceName,
                          int deviceIndex,
                          int deviceSize,
                          string binaryFileName,
                          bool linkx_auto_update,
                          bool activationNeeded,
                          bool downloadTransferNeeded,
                          int activate_delay_sec,
                          ProgressCallBackAdvSt* ProgressFuncAdv,
                          FwComponent::comps_ids_t fwComponent);
    FlintStatus BurnCMISCable();
    FlintStatus ResetModule(string device);
    FlintStatus WaitForModuleInit(string device);
    FlintStatus PerformBurn(std::vector<u_int8_t>& fwImage, std::vector<u_int8_t>& vendorData);
    FlintStatus PldmToFwOps(FsPldmOperations* pldmOps);

public:
    BurnSubCommand();
    ~BurnSubCommand();
    FlintStatus executeCommand();
    virtual void cleanInterruptedCommand();
    bool verifyParams();
};

class BinaryCompareSubCommand : public SubCommand
{
private:
    fw_info_t _devInfo;
    fw_info_t _imgInfo;
    FwOperations::ExtBurnParams _burnParams;
    bool _devQueryRes;
    int _unknownProgress; // used to trace the progress of unknown progress.
    FlintStatus compareMFA2();
    bool ReadFwOpsImageData(vector<u_int8_t>& deviceBuff, vector<u_int8_t>& imgBuff);
    bool CompareEncryptedFwOpsViaDirectAccess(bool& res);
    bool CompareEncryptedFwOpsViaMCC(bool& res);
    bool CompareEncryptedFwOps(bool& res);
    bool CompareFwOps(bool& res);

public:
    BinaryCompareSubCommand();
    ~BinaryCompareSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class QuerySubCommand : public SubCommand
{
private:
    fw_info_t _imgInfo;
    FlintStatus printImageInfo(const fw_info_t& fwInfo);
    string printSecurityAttrInfo(u_int32_t m);
    FlintStatus printInfo(const fw_info_t& fwInfo, bool fullQuery);
    bool displayFs4Uids(const fw_info_t& fwInfo);
    bool displayFs3Uids(const fw_info_t& fwInfo, bool isStripedImage);
    bool displayFs2Uids(const fw_info_t& fwInfo);
    bool checkMac(u_int64_t mac, string& warrStr);
    FlintStatus queryMFA2();
    void AddTableHeaderForCSVFormat(string& outputString);
    bool PrintLinkXQuery(string& outputString,
                         const string& host,
                         int deviceIndex,
                         const comp_status_st& ComponentStatus,
                         const component_linkx_st& linkx_data,
                         char* delimeter,
                         bool isCSV);
    FlintStatus QueryLinkX(string deviceName, string outputFile, std::vector<int> deviceIds);
    FlintStatus QueryCableAttributes();
    void PrintLifeCycle(const life_cycle_t& lifeCycle);

public:
    QuerySubCommand();
    ~QuerySubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class QueryComponentSubCommand : public SubCommand
{
public:
    QueryComponentSubCommand();
    ~QueryComponentSubCommand();
    FlintStatus executeCommand() override;
    bool verifyParams() override;
    FlintStatus querySyncE();
    FlintStatus QueryCertStatus();
    FlintStatus QueryDpaApps();
private:
    FwComponent::comps_ids_t _comp;
};


class QueryBfbComponentsSubCommand : public SubCommand
{
public:
    QueryBfbComponentsSubCommand();
    ~QueryBfbComponentsSubCommand();
    bool verifyParams() override;
    FlintStatus executeCommand() override;

private:
    bool _pending;
    std::map<std::string, std::string> _name_to_version;

    bool isDeviceSupported();
    void printComponents();
};

class Extract4MBImageSubCommand : public SubCommand
{
private:
public:
    Extract4MBImageSubCommand();
    ~Extract4MBImageSubCommand();
    FlintStatus executeCommand();
};

class AddHmacSubCommand : public SubCommand
{
private:
public:
    AddHmacSubCommand();
    ~AddHmacSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};
class SignSubCommand : public SubCommand
{
private:
public:
    SignSubCommand();
    ~SignSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class ExportPublicSubCommand : public SubCommand
{
public:
    ExportPublicSubCommand();
    ~ExportPublicSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class SignRSASubCommand : public SubCommand
{
private:
public:
    SignRSASubCommand();
    ~SignRSASubCommand();
    FlintStatus executeCommand();
    bool verifyParams();

protected:
    unique_ptr<MlxSign::Signer> createSigner();
};

class SetPublicKeysSubCommand : public SubCommand
{
private:
public:
    SetPublicKeysSubCommand();
    ~SetPublicKeysSubCommand();
    FlintStatus executeCommand();
};

class SetForbiddenVersionsSubCommand : public SubCommand
{
private:
public:
    SetForbiddenVersionsSubCommand();
    ~SetForbiddenVersionsSubCommand();
    FlintStatus executeCommand();
};

class VerifySubCommand : public SubCommand
{
private:
public:
    VerifySubCommand();
    ~VerifySubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class ImageReactivationSubCommand : public SubCommand
{
public:
    ImageReactivationSubCommand();
    virtual ~ImageReactivationSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class SwResetSubCommand : public SubCommand
{
private:
    bool IsDeviceSupported(dm_dev_id_t dev_id);

public:
    SwResetSubCommand();
    ~SwResetSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class BromSubCommand : public SubCommand
{
private:
    fw_info_t _info;
    roms_info_t _romsInfo;
    FImage _fRom;

public:
    BromSubCommand();
    ~BromSubCommand();
    inline FlintStatus executeCommand();
    bool getExpRomStrVer(roms_info_t& roms_info, char* version);
};

class DromSubCommand : public SubCommand
{
public:
    DromSubCommand();
    ~DromSubCommand();
    FlintStatus executeCommand();
    inline bool verifyParams();
};

class RromSubCommand : public SubCommand
{
private:
public:
    RromSubCommand();
    ~RromSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class BbSubCommand : public SubCommand
{
private:
public:
    BbSubCommand();
    ~BbSubCommand();
    FlintStatus executeCommand();
    inline bool verifyParams();
};

class SgSubCommand : public SubCommand
{
private:
    fw_info_t _info;
    FwOperations* _ops;
    FwOperations::sg_params_t _sgParams;

    FlintStatus sgFs2();
    FlintStatus sgFs3();
    void setUserGuidsAndMacs();
    bool CheckSetGuidsFlags();

public:
    SgSubCommand();
    ~SgSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class SmgSubCommand : public SubCommand
{
private:
    fs3_uid_t _baseGuid;
    fw_info_t _info;
    FwOperations* _ops;

public:
    SmgSubCommand();
    ~SmgSubCommand();
    inline FlintStatus executeCommand();
    inline bool verifyParams();
};

class SetCertChainSubCommand : public SubCommand
{
public:
    SetCertChainSubCommand();
    ~SetCertChainSubCommand(){};
    FlintStatus executeCommand();
};

class SetVpdSubCommand : public SubCommand
{
public:
    SetVpdSubCommand();
    ~SetVpdSubCommand(){};
    FlintStatus executeCommand();
};

class SvSubCommand : public SubCommand
{
private:
public:
    SvSubCommand();
    ~SvSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};
class RiSubCommand : public SubCommand
{
public:
    RiSubCommand();
    ~RiSubCommand();
    FlintStatus executeCommand();
};

class DcSubCommand : public SubCommand
{
private:
    std::vector<u_int8_t> _sect;

public:
    DcSubCommand();
    ~DcSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};
class DhSubCommand : public SubCommand
{
private:
    std::vector<u_int8_t> _sect;

public:
    DhSubCommand();
    ~DhSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class SetKeySubCommand : public SubCommand
{
private:
    hw_key_t _userKey;
    bool _getKeyInter;
    bool getKeyInteractively();

public:
    SetKeySubCommand();
    ~SetKeySubCommand();
    inline FlintStatus executeCommand();
    inline bool verifyParams();
};
class HwAccessSubCommand : public SubCommand
{
private:
    FlintStatus disableHwAccess();
    FlintStatus enableHwAccess();

public:
    HwAccessSubCommand();
    ~HwAccessSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class HwSubCommand : public SubCommand
{
private:
    FlintStatus printAttr(const ext_flash_attr_t& attr);
    bool PrintWriteProtectedBits(const ext_flash_attr_t& attr);
    bool FillAttrIfNeeded(ext_flash_attr_t& attr, char* param_val_str, char* param_name);

public:
    HwSubCommand();
    ~HwSubCommand();
    inline FlintStatus executeCommand();
    inline bool verifyParams();
};
class EraseSubCommand : public SubCommand
{
private:
public:
    EraseSubCommand();
    ~EraseSubCommand();
    inline FlintStatus executeCommand();
};
class RwSubCommand : public SubCommand
{
private:
public:
    RwSubCommand();
    ~RwSubCommand();
    inline FlintStatus executeCommand();
};
class WwSubCommand : public SubCommand
{
private:
public:
    WwSubCommand();
    ~WwSubCommand();
    inline FlintStatus executeCommand();
};

class WwneSubCommand : public SubCommand
{
private:
public:
    WwneSubCommand();
    ~WwneSubCommand();
    inline FlintStatus executeCommand();
};

class WbSubCommand : public SubCommand
{
private:
    bool extractData(const std::vector<string>& cmdParams, u_int32_t* addr, std::vector<u_int8_t>& data);

public:
    WbSubCommand();
    ~WbSubCommand();
    FlintStatus executeCommand();
};

class WbneSubCommand : public SubCommand
{
private:
    bool extractData(const std::vector<string>& cmdParams, u_int32_t* addr, std::vector<u_int32_t>& data);
    bool writeBlock(u_int32_t addr, std::vector<u_int32_t> dataVec);

public:
    WbneSubCommand();
    ~WbneSubCommand();
    FlintStatus executeCommand();
};

class RbSubCommand : public SubCommand
{
private:
    bool printToScreen(const std::vector<u_int8_t>& buff, bool hexdump_format);
    bool readBlock(u_int32_t addr, std::vector<u_int8_t>& buff, bool isFlash);

public:
    RbSubCommand();
    ~RbSubCommand();
    FlintStatus executeCommand();
};

class ClearSemSubCommand : public SubCommand
{
private:
public:
    ClearSemSubCommand();
    ~ClearSemSubCommand();
    FlintStatus executeCommand();
};

class RomQuerySubCommand : public SubCommand
{
private:
    roms_info_t _romsInfo;

public:
    RomQuerySubCommand();
    ~RomQuerySubCommand();
    FlintStatus executeCommand();
};

class ResetCfgSubCommand : public SubCommand
{
public:
    ResetCfgSubCommand();
    ~ResetCfgSubCommand();
    FlintStatus executeCommand();
};

class FiSubCommand : public SubCommand
{
public:
    FiSubCommand();
    ~FiSubCommand();
    FlintStatus executeCommand();
};

class CheckSumSubCommand : public SubCommand
{
public:
    CheckSumSubCommand();
    ~CheckSumSubCommand();
    FlintStatus executeCommand();

private:
    bool extractChecksumFromStr(string str, u_int8_t checkSum[16]);
    string checkSum2Str(u_int8_t checkSum[16]);
    u_int8_t _checkSum[16];
};

class TimeStampSubCommand : public SubCommand
{
public:
    TimeStampSubCommand();
    ~TimeStampSubCommand();
    FlintStatus executeCommand();

private:
    enum
    {
        TS_No_Command,
        TS_Query,
        TS_Set,
        TS_Reset
    };

    bool verifyParams();
    bool parseTimeStamp(string tsStr);
    bool parseFwVersion(string verStr);
    inline u_int8_t getDaysInMonth(u_int16_t year, u_int8_t month);
    inline void printTsAndFwVer(string prefix, struct tools_open_ts_entry& tsEntry, struct tools_open_fw_version& fwVer);
    void getMachineUTCTime();
    bool queryTs();
    bool setTs();
    bool resetTs();

    int _operation;
    FwOperations* _ops;
    struct tools_open_ts_entry _userTsEntry;
    struct tools_open_fw_version _userFwVer;
};

class CacheImageSubCommand : public SubCommand
{
public:
    CacheImageSubCommand();
    ~CacheImageSubCommand();
    FlintStatus executeCommand();
};

#endif
