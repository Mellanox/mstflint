/*
 *
 * subcommands.h - FLash INTerface
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

#ifndef __SUBCOMMANDS_H__
#define __SUBCOMMANDS_H__

#define MAX_PASSWORD_LEN 256

#include <string>
#include "flint_params.h"
#include "mlxfwops/lib/fw_ops.h"
#include "err_msgs.h"
using namespace std;

//we might need to close the log from the main program in case of interrupt
void close_log();
void print_time_to_log();
int print_line_to_log(const char* format, ...);
int write_cmd_to_log(char* av[], int ac, CommandType cmd, bool write=true);
int write_result_to_log(int is_failed, const char* err_msg, bool write=true);

typedef enum what_to_ver {
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
    FwOperations *_fwOps;
    FwOperations *_imgOps;
    FBase* _io;
    what_to_ver_t _v;
    FlintParams _flintParams;
    //info about the Subcommand
    string _name;
    string _desc;
    string _extendedDesc;
    string _flagLong;
    string _flagShort;
    string _param;
    string _paramExp;
    string _example;
    char  _errBuff[FLINT_ERR_LEN];
    sub_cmd_t _cmdType;


    //Methods that are commonly used in the various subcommands:
    //TODO: add middle classes and segregate as much of these common methods between these classes

    virtual bool verifyParams() {return true;};
    bool basicVerifyParams();
    FlintStatus openOps();
    FlintStatus openIo();
    virtual FlintStatus preFwOps();
    virtual FlintStatus preFwAccess();

    bool getRomsInfo(FBase* io, roms_info_t& romsInfo);
    void displayOneExpRomInfo(const rom_info_t& info);
    void displayExpRomInfo(const roms_info_t& romsInfo, const char *preStr);

    static int verifyCbFunc(char* str);
    static int CbCommon(int completion, char*preStr, char* endStr=NULL);
    static int burnCbFs2Func(int completion);
    static int burnCbFs3Func(int completion);
    static int burnBCbFunc(int completion);
    static int vsdCbFunc(int completion);
    static int setKeyCbFunc(int completion);
    static int bromCbFunc(int completion);
    static int dromCbFunc(int completion);
    static int wbCbFunc(int completion);
    static int resetCfgCbFunc(int completion);

    bool printGuidLine(guid_t* new_guids, guid_t* old_guids, int guid_index);
    bool printBxGuids(guid_t* new_guids, guid_t* old_guids, int index,\
                        int num_of_guids, const char* pre_str);
    bool printMacLine(guid_t* new_guids, guid_t* old_guids, int mac_index);
    bool printBxMacs(guid_t* new_guids, guid_t* old_guids, int index, int num_of_guids, const char* pre_str);
    bool printUidsFunc(guid_t* new_guids, guid_t* old_guids);
    bool printGUIDsFunc(guid_t guids[GUIDS],guid_t macs[MACS], guid_t old_guids[GUIDS],\
            guid_t old_macs[MACS], bool print_guids, bool print_macs, int portNum, bool old_guid_fmt);
    bool reportGuidChanges(guid_t* new_guids, guid_t* new_macs,\
                                        guid_t* old_guids, guid_t* old_macs, bool printGuids,\
                                        bool printMacs, bool printUids, int guidNum);
    bool checkGuidsFlags(chip_type_t ct, u_int16_t devType, u_int8_t fwType,
            bool guidsSpecified, bool macsSpecified, bool uidsSpecified);
    void printMissingGuidErr(bool ibDev, bool ethDev, bool bxDev);

    bool extractUIDArgs(std::vector<string>& cmdArgs, u_int8_t& numOfGuids, u_int8_t& stepSize);
    bool getGUIDFromStr(string str, guid_t& guid, string prefixErr="");
    bool  getPasswordFromUser(const char *preStr, char buffer[MAX_PASSWORD_LEN+1]);
    bool askUser(const char* question=NULL, bool printAbrtMsg=true);

    bool isCmdSupportLog();
    void openLog();
    inline void closeLog() {close_log();}
    //print errors to an err buff, log if needed and stdout
    void reportErr(bool shouldPrint, const char *format, ...);


    bool fwVerLessThan(const u_int16_t r1[3], const u_int16_t r2[3]);

    bool writeToFile(string filePath, const std::vector<u_int8_t>& buff);

    bool dumpFile(const char* confFile, std::vector<u_int8_t>& data, const char *sectionName);
    bool unzipDataFile (std::vector<u_int8_t> data, std::vector<u_int8_t> &newData, const char *sectionName);



public:
    SubCommand(): _fwOps(NULL), _imgOps(NULL), _io(NULL), _v(Wtv_Uninitilized)
    {
        _cmdType = SC_No_Cmd;
        memset(_errBuff, 0, sizeof(_errBuff));
    }
    virtual ~SubCommand();
    virtual FlintStatus executeCommand() = 0;
    inline void setParams(const FlintParams& flintParams) {_flintParams = flintParams;}
    inline string& getName() {return this->_name;}
    inline string& getDesc() {return this->_desc;}
    inline string& getExtDesc() {return this->_extendedDesc;}
    inline string& getFlagL() {return this->_flagLong;}
    inline string& getFlagS() {return this->_flagShort;}
    inline string& getParam() {return this->_param;}
    inline string& getParamExp() {return this->_paramExp;}
    inline string& getExample() {return this->_example;}
};

class BurnSubCommand : public SubCommand
{
private:
	u_int8_t _fwType;
    fw_info_t _devInfo;
    fw_info_t _imgInfo;
    FwOperations::ExtBurnParams _burnParams;
    bool _devQueryRes;

    FlintStatus burnFs3();
    FlintStatus burnFs2();
    bool checkFwVersion();
    bool checkPSIDAndIbEth();
    void updateBurnParams();
    void dealWithExpRom();
    bool checkMatchingExpRomDevId(const fw_info_t& info);
    bool dealWithGuids();
    bool dealWithVSD();
public:
    BurnSubCommand();
    ~BurnSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class QuerySubCommand : public SubCommand
{
private:
    FlintStatus printInfo(const fw_info_t& fwInfo, bool fullQuery);
    bool displayFs3Uids(const fw_info_t& fwInfo);
    bool displayFs2Uids(const fw_info_t& fwInfo);
    bool reportBxGuidsQuery(const guid_t* guids, int base1, int guids_num, int index, const char* pre_str);
    bool reportBxMacsQuery(const guid_t* guids, int base1, int guids_num, int index, const char* pre_str);
    bool reportBxMacsWarnings(const guid_t* guids, int index, int warning, int user_uids);
    bool checkMac(u_int64_t mac, string& warrStr);
public:
    QuerySubCommand();
    ~QuerySubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
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

class SwResetSubCommand : public SubCommand
{
private:

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
    bool verifyParams();
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
    fs3_guid_t _baseGuid;
public:
    SmgSubCommand();
    ~SmgSubCommand();
    inline FlintStatus executeCommand();
    inline bool verifyParams();
};

class SetVpdSubCommand : public SubCommand
{
private:

public:
    SetVpdSubCommand();
    ~SetVpdSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
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
private:
    FlintStatus writeImageToFile(const char *file_name, u_int8_t *data, u_int32_t length);
public:
    RiSubCommand();
    ~RiSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
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
    inline bool verifyParams();
};
class RwSubCommand : public SubCommand
{
private:

public:
    RwSubCommand();
    ~RwSubCommand();
    inline FlintStatus executeCommand();
    inline bool verifyParams();
};
class WwSubCommand : public SubCommand
{
private:

public:
    WwSubCommand();
    ~WwSubCommand();
    inline FlintStatus executeCommand();
    inline bool verifyParams();
};

class WwneSubCommand : public SubCommand
{
private:

public:
    WwneSubCommand();
    ~WwneSubCommand();
    inline FlintStatus executeCommand();
    inline bool verifyParams();
};

class WbSubCommand : public SubCommand
{
private:
    bool extractData(const std::vector<string>& cmdParams , u_int32_t* addr, std::vector<u_int8_t>& data);
public:
    WbSubCommand();
    ~WbSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};


class WbneSubCommand : public SubCommand
{
private:
    bool extractData(const std::vector<string>& cmdParams , u_int32_t* addr, std::vector<u_int32_t>& data);
    bool writeBlock(u_int32_t addr, std::vector<u_int32_t> dataVec);
public:
    WbneSubCommand();
    ~WbneSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
};

class RbSubCommand : public SubCommand
{
private:
    bool printToScreen(const std::vector<u_int8_t>& buff);
    bool readBlock(u_int32_t addr, std::vector<u_int8_t>& buff, bool isFlash);
public:
    RbSubCommand();
    ~RbSubCommand();
    FlintStatus executeCommand();
    bool verifyParams();
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

#endif
