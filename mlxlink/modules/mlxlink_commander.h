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

#ifndef MLXLINK_COMMANDER_H
#define MLXLINK_COMMANDER_H

#include <common/tools_utils.h>
#include <common/tools_version.h>
#include <mft_utils/mft_sig_handler.h>
#ifndef MST_UL
#include <cmdif/cib_cif.h>
#else
#include <cmdif/icmd_cif_open.h>
#endif
#include <cmdparser/cmdparser.h>
#include <mtcr.h>
#include "mlxlink_utils.h"
#include "mlxlink_reg_parser.h"

#ifdef MST_UL
#define MLXLINK_EXEC "mstlink"
#else
#define MLXLINK_EXEC "mlxlink"
#endif

//------------------------------------------------------------
//        Mlxlink OPTIONS Flags

#define HELP_FLAG                    "help"
#define HELP_FLAG_SHORT              'h'
#define VERSION_FLAG                 "version"
#define VERSION_FLAG_SHORT           'v'
#define DEVICE_FLAG                  "device"
#define DEVICE_FLAG_SHORT            'd'
#define LABEL_PORT_FLAG              "port"
#define LABEL_PORT_FLAG_SHORT        'p'
#define PORT_TYPE_FLAG               "port_type"
#define PORT_TYPE_FLAG_SHORT         ' '
#define DEPTH_FLAG                   "depth"
#define DEPTH_FLAG_SHORT             ' '
#define PCIE_INDEX_FLAG              "pcie_index"
#define PCIE_INDEX_FLAG_SHORT        ' '
#define NODE_FLAG                    "node"
#define NODE_FLAG_SHORT              ' '
#define PRINT_JSON_OUTPUT_FLAG       "json"
#define PRINT_JSON_OUTPUT_FLAG_SHORT ' '
//------------------------------------------------------------
//        Mlxlink QUERIES Flags

#define PCIE_LINKS_FLAG                 "show_links"
#define PCIE_LINKS_FLAG_SHORT            ' '
#define MODULE_INFO_FLAG                "show_module"
#define MODULE_INFO_FLAG_SHORT          'm'
#define BER_FLAG                        "show_counters"
#define BER_FLAG_SHORT                  'c'
#define EYE_OPENING_FLAG                "show_eye"
#define EYE_OPENING_FLAG_SHORT          'e'
#define FEC_DATA_FLAG                   "show_fec"
#define FEC_DATA_FLAG_SHORT             ' '
#define SLTP_SHOW_FLAG                  "show_serdes_tx"
#define SLTP_SHOW_FLAG_SHORT            ' '
#define DEVICE_DATA_FLAG                "show_device"
#define DEVICE_DATA_FLAG_SHORT          ' '
#define BER_MONITOR_INFO_FLAG           "show_ber_monitor"
#define BER_MONITOR_INFO_FLAG_SHORT     ' '
#define PEPC_SHOW_FLAG                  "show_external_phy"
#define PEPC_SHOW_FLAG_SHORT            ' '
#define LINK_DOWN_BLAME_INFO_FLAG       "show_link_down_blame"
#define LINK_DOWN_BLAME_INFO_FLAG_SHORT ' '

//------------------------------------------------------------
//        Mlxlink COMMANDS Flags

#define PAOS_FLAG                          "port_state"
#define PAOS_FLAG_SHORT                    'a'
#define PTYS_FLAG                          "speeds"
#define PTYS_FLAG_SHORT                    's'
#define PPLR_FLAG                          "loopback"
#define PPLR_FLAG_SHORT                    'l'
#define PPLM_FLAG                          "fec"
#define PPLM_FLAG_SHORT                    'k'
#define FEC_SPEED_FLAG                     "fec_speed"
#define FEC_SPEED_FLAG_SHORT               ' '
#define SLTP_SET_FLAG                      "serdes_tx"
#define SLTP_SET_FLAG_SHORT                ' '
#define LANE_FLAG                          "serdes_tx_lane"
#define LANE_FLAG_SHORT                    ' '
#define DATABASE_FLAG                      "database"
#define DATABASE_FLAG_SHORT                ' '
#define PRBS_MODE_FLAG                     "test_mode"
#define PRBS_MODE_FLAG_SHORT               ' '
#define PPRT_PRBS_FLAG                     "rx_prbs"
#define PPRT_PRBS_FLAG_SHORT               ' '
#define PPTT_PRBS_FLAG                     "tx_prbs"
#define PPTT_PRBS_FLAG_SHORT               ' '
#define PPRT_RATE_FLAG                     "rx_rate"
#define PPRT_RATE_FLAG_SHORT               ' '
#define PPTT_RATE_FLAG                     "tx_rate"
#define PPTT_RATE_FLAG_SHORT               ' '
#define PRBS_LANES_FLAG                    "lanes"
#define PRBS_LANES_FLAG_SHORT              ' '
#define PPRT_TUNING_TYPE_FLAG              "tuning_type"
#define PPRT_TUNING_TYPE_FLAG_SHORT        ' '
#define BER_COLLECT_FLAG                   "ber_collect"
#define BER_COLLECT_FLAG_SHORT             'b'
#define BER_LIMIT_FLAG                     "ber_limit"
#define BER_LIMIT_FLAG_SHORT               ' '
#define ITERATION_FLAG                     "iteration"
#define ITERATION_FLAG_SHORT               ' '
#define PPCNT_CLEAR_FLAG                   "pc"
#define PPCNT_CLEAR_FLAG_SHORT             ' '
#define PEPC_SET_FLAG                      "set_external_phy"
#define PEPC_SET_FLAG_SHORT                ' '
#define PEPC_FORCE_MODE_FLAG               "twisted_pair_force_mode"
#define PEPC_FORCE_MODE_FLAG_SHORT         ' '
#define PEPC_AN_MODE_FLAG                  "twisted_pair_an_mode"
#define PEPC_AN_MODE_FLAG_SHORT            ' '
#define PTYS_LINK_MODE_FORCE_FLAG          "link_mode_force"
#define PTYS_LINK_MODE_FORCE_FLAG_SHORT    ' '

//------------------------------------------------------------
//        Mlxlink HIDDEN Flags

#define SLTP_SET_ADVANCED_FLAG              "advanced"
#define SLTP_SET_ADVANCED_FLAG_SHORT        ' '
#define GVMI_ADDRESS_FLAG                   "gvmi_address"
#define GVMI_ADDRESS_FLAG_SHORT             ' '
#define LOG_FLAG                            "log"
#define LOG_FLAG_SHORT                      ' '

//------------------------------------------------------------

#define REG_ACCESS_UNION_NODE "access_reg_summary"

//------------------------------------------------------------
//        Mlxlink Values definition
#define SWID                        0
#define PPRT_PPTT_ENABLE            1
#define PPRT_PPTT_START_TUNING      1
#define PHY_TEST_MODE_STATUS        1

#define PDDR_STATUS_MESSAGE_LENGTH_HCA  236
#define PDDR_STATUS_MESSAGE_LENGTH_SWITCH 59

#define OB_TAP_SUM                  120
#define OB_TAP_DIFF                 10
#define OB_BIAS_LOW_THRESHOLD       15
#define OB_BIAS_MID_1_THRESHOLD     31
#define OB_BIAS_MID_2_THRESHOLD     48
#define OB_BIAS_HIGH_THRESHOLD      63

#define MAX_LOCAL_PORT_ETH          64
#define MAX_LOCAL_PORT_IB           36
#define MAX_LOCAL_PORT_QUANTUM      82
#define MAX_LOCAL_PORT_SPECTRUM2    128

#define DBN_TO_LOCAL_PORT_BASE      60

#define MAX_LANES_NUMBER            4

#define PCAM_FORCE_DOWN_CAP_MASK    0x2000

//------------------------------------------------------------
//        Mlxlink enumerations
enum SHOW_FUNCTIONS {
    SHOW_PDDR = 1,
    SHOW_PCIE,
    SHOW_BER,
    SHOW_EYE,
    SHOW_FEC,
    SHOW_SLTP,
    SHOW_SLRP,
    SHOW_MODULE,
    SHOW_DEVICE,
    SHOW_BER_MONITOR,
    SHOW_EXTERNAL_PHY,
    SHOW_LINK_DOWN_BLAME,
    SEND_BER_COLLECT,
    SEND_PAOS,
    SEND_PTYS,
    SEND_PPLM,
    SEND_PPLR,
    SEND_PRBS,
    SEND_SLTP,
    SEND_CLEAR_COUNTERS,
    SEND_PEPC,
    SHOW_PCIE_LINKS,
    // Any new function's index should be added before SHOW_SEND_LAST in this enum
    FUNCTION_LAST
};

enum PNAT_ACCESS {
    PNAT_LOCAL = 0, PNAT_LABEL = 1, PNAT_PCIE = 3
};

enum PDDR_PAGES {
    PDDR_OPERATIONAL_INFO_PAGE = 0,
    PDDR_TROUBLESHOOTING_INFO_PAGE = 1,
    PDDR_MODULE_INFO_PAGE = 3,
};

enum PPCNT_GROUPS {
    PPCNT_PHY_GROUP = 0x12,
    PPCNT_STATISTICAL_GROUP = 0x16,
    PPCNT_IB_PORT_COUNTERS_GROUP = 0x20,
    PPCNT_ALL_GROUPS = 63
};

enum MPCNT_GROUPS {
    MPCNT_PERFORMANCE_GROUP = 0, MPCNT_LANE_GROUP = 1, MPCNT_TIMERS_GROUPS = 2
};

enum PPAOS_ADMIN {
    PPAOS_REGULAR_OPERATION = 0, PPAOS_PHY_TEST_MODE = 1
};

enum GROUP_OPCODE {
    MONITOR_OPCODE = 0, ADVANCED_OPCODE = 1
};

enum SLTP_PARAMS {
    POLARITY,
    OB_TAP0,
    OB_TAP1,
    OB_TAP2,
    OB_BIAS,
    OB_PREEMP_MODE,
    OB_REG,
    OB_LEVA
};

enum SLTP_16NM_PARAMS {
    PRE_2_TAP,
    PRE_TAP,
    MAIN_TAP,
    POST_TAP,
    OB_M2LP,
    OB_AMP,
    OB_ALEV_OUT
};

enum BER_LIMIT {
    NOMINAL_25G_NO_FEC = -15,
    NOMINAL_25G_LOW_ATTN = -13,
    NOMINAL_25G_HIGH_ATTN = -9,
    NOMINAL_10G = -14,
    NOMINAL_56G_40G = -15,
    NOMINAL_DEFAULT = -15,
    CORNER_25G_NO_FEC = -14,
    CORNER_25G_LOW_ATTN = -10,
    CORNER_25G_HIGH_ATTN = -7,
    CORNER_10G = -13,
    CORNER_56G_40G = -14,
    CORNER_DEFAULT = -14
};

enum PAOS_ADMIN {
    PAOS_UP = 1, PAOS_DOWN = 2
};

enum PRODUCT_TECHNOLOGY {
    PRODUCT_40NM = 0,
    PRODUCT_28NM = 1,
    PRODUCT_16NM = 3
};

enum PCIE_PORT_TYPE {
    PORT_TYPE_EP = 0,
    PORT_TYPE_US = 5,
    PORT_TYPE_DS = 6
};

struct DPN {
    DPN()
    {
        depth =0;
        pcieIndex=0;
        node=0;
    }
    DPN(u_int32_t d, u_int32_t p, u_int32_t n)
    {
        depth = d;
        pcieIndex = p;
        node = n;
    }
    u_int32_t depth;
    u_int32_t pcieIndex;
    u_int32_t node;
};

#define PRINT_LOG(mlxlinklogger, title)\
    if (mlxlinklogger) {\
        mlxlinklogger->printHeaderWithUnderLine(title);\
    }\

#define DEBUG_LOG(mlxlinklogger, format, ...)\
    if (mlxlinklogger) {\
        mlxlinklogger->debugLog(format, __VA_ARGS__);\
    }\

using namespace mlxreg;

class MlxlinkCommander: public MlxlinkRegParser {

public:
    MlxlinkCommander();
    virtual ~MlxlinkCommander();

    void setParseMethod();
    void resetParser(const string &regName);
    void genBuffSendRegister(const string &regName, maccess_reg_method_t method);
    void updateField(const string &field_name, u_int32_t value);
    u_int32_t getFieldValue(const string &field_name, std::vector<u_int32_t>& buff);
    u_int32_t getFieldValue(string field_name) { return MlxlinkRegParser::getFieldValue(field_name); }
    string getFieldStr(const string &field);
    void checkRegCmd();
    void checkLocalPortDPNMapping(u_int32_t localPort);
    int getLocalPortFromMPIR(DPN& dpn);
    void checkValidFW();
    int getProductTechnology();
    bool checkPortStatus(u_int32_t localPort);
    void checkAllPortsStatus();
    void labelToLocalPort();
    void labelToHCALocalPort();
    void labelToSpectLocalPort();
    void labelToIBLocalPort();
    bool isIBSplitReady();
    void toIBLabelPort(u_int32_t &labelPort, bool ibSplitReady);
    void checkWidthSplit(u_int32_t localPort);
    void checkUnSplit(u_int32_t localPort);
    u_int32_t maxLocalPort();
    string getAscii(const string & name, u_int32_t size = 4);
    string getRxTxCDRState(u_int32_t state);
    void getActualNumOfLanes(u_int32_t linkSpeedActive, bool extended);
    void getActualNumOfLanesIB();
    void getActualNumOfLanesETH(u_int32_t linkSpeedActive, bool extended);
    u_int32_t activeSpeed2gNum(u_int32_t mask, bool extended);
    string activeSpeed2Str(u_int32_t mask, bool extended);
    void getCableParams();
    bool inPrbsTestMode();
    bool checkPaosDown();
    bool checkPpaosTestMode();
    u_int32_t getPtysCap();
    void getSltpParamsFromVector(std::vector<string> sltpParams);
    void getprbsLanesFromParams(std::vector<string> prbsLanesParams);
    std::vector<string> parseParamsFromLine(const string & ParamsLine);
    void setPrintTitle(MlxlinkCmdPrint &mlxlinkCmdPrint, string title,
            u_int32_t size, bool print = true);
    void setPrintVal(MlxlinkCmdPrint &mlxlinkCmdPrint, int index, string key,
            string value, string color = ANSI_COLOR_RESET, bool print = true,
            bool valid = true, bool arrayValue = false);
    void writeGvmi(u_int32_t data);

    //Mlxlink query functions
    void showModuleInfo();
    virtual void operatingInfoPage();
    virtual void supportedInfoPage();
    virtual void troubInfoPage();
    virtual void showPddr();
    void getPtys();
    virtual void showBer();
    void showEye();
    void showFEC();
    virtual void showSltp();
    void showDeviceData();
    void showBerMonitorInfo();
    void showExternalPhy();
    void showPcie();
    void showPcieLinks();
    void collectBER();

    // Query helper functions
    string getCompliance(u_int32_t compliance, std::map<u_int32_t,
            std::string> complianceMap, bool bitMasked = false);
    string getComplianceLabel(u_int32_t compliance,  u_int32_t extCompliance,
            u_int32_t cable_identifier, bool ignoreExtBitChk = false);
    string getLosAlarm();
    template<typename T, typename Q> string getValueAndThresholdsStr(T value, Q lowTH, Q highTH);
    void prepareSltp28_40nm(std::vector<std::vector<string> > &sltpLanes,
            u_int32_t laneNumber);
    void prepareSltp16nm(std::vector<std::vector<string> > &sltpLanes,
            u_int32_t laneNumber);
    void initValidDPNList();

    void showTestMode();
    void showTestModeBer();
    void showMpcntPerformance(DPN& dpn);
    void showMpcntTimers(DPN& dpn);
    void showMpcntLane();
    void showPcieState(DPN& dpn);
    void checkForPcie();

    std::map<std::string, std::string>  getPprt();
    std::map<std::string, std::string>  getPptt();

    std::map<std::string, float>  getRawEffectiveErrors();
    std::map<std::string, float>  getRawEffectiveErrorsinTestMode();
    int prbsModeToMask(const string &mode);
    string prbsMaskToMode(u_int32_t mask, u_int32_t modeSelector);
    string getPrbsModeRX();
    u_int32_t getPrbsRateRX();
    string getSupportedPrbsModes(u_int32_t modeSelector);
    virtual u_int32_t getLoopbackMode(const string &lb);
    int getLinkDown();
    float getRawBERLimit();
    bool getResult(std::map<std::string, float>  errors_vector,
                   float raw_ber_limit, int link_down);
    string getDevicePN(bool queryMSGI = false);
    string getDeviceSN(bool queryMSGI = false);
    string getDeviceProductName(bool queryMSGI = false);
    string getDeviceRev(bool queryMSGI = false);
    string getDeviceFW();
    string getVendorRev(const string & name);

    void prepareJsonOut();

    MlxlinkCmdPrint _operatingInfoCmd;
    MlxlinkCmdPrint _supportedInfoCmd;
    MlxlinkCmdPrint _troubInfoCmd;
    MlxlinkCmdPrint _testModeInfoCmd;
    MlxlinkCmdPrint _pcieInfoCmd;
    MlxlinkCmdPrint _moduleInfoCmd;
    MlxlinkCmdPrint _berInfoCmd;
    MlxlinkCmdPrint _testModeBerInfoCmd;
    MlxlinkCmdPrint _mpcntPerfInfCmd;
    MlxlinkCmdPrint _mpcntTimerInfCmd;
    MlxlinkCmdPrint _eyeOpeningInfoCmd;
    MlxlinkCmdPrint _fecCapInfoCmd;
    MlxlinkCmdPrint _sltpInfoCmd;
    MlxlinkCmdPrint _showDeviceInfoCmd;
    MlxlinkCmdPrint _showBerMonitorInfo;
    MlxlinkCmdPrint _extPhyInfoCmd;
    MlxlinkCmdPrint _linkBlameInfoCmd;
    MlxlinkCmdPrint _validPcieLinks;

    // Mlxlink config functions
    void clearCounters();
    void sendPaos();
    void handlePrbs();
    void sendPtys();
    void sendPplm();
    virtual void sendSltp();
    void sendPplr();
    virtual void sendPepc();

    // Config helper functions
    bool isForceDownSupported();
    void sendPaosCmd(PAOS_ADMIN adminStatus, bool forceDown = false);
    void sendPaosDown();
    void sendPaosUP();
    void sendPaosToggle();
    void checkPRBSModeCap(u_int32_t modeSelector, u_int32_t capMask);
    void checkPrbsRegsCap(const string &prbsReg, const string &laneRate);
    void checkPprtPptt();
    void checkPplrCap();
    void sendPrbsPpaos(bool);
    void startTuning();
    void prbsConfiguration(const string &prbsReg, bool enable, u_int32_t laneRate,
            u_int32_t prbsMode, bool perLaneConfig = false);
    void sendPprtPptt();
    void resetPprtPptt();
    u_int32_t ptysSpeedToMask(const string & speed, u_int32_t cap);
    u_int32_t ptysSpeedToExtMask(const string & speed);
    void checkSupportedSpeed(const string & speed, u_int32_t cap, bool extSpeed = false);
    void checkPplmCap();
    void updateSltp28_40nmFields();
    void updateSltp16nmFields();
    void getSltpRegAndLeva(u_int32_t lane);
    virtual void checkSltpParamsSize();

    // Mlxlink params
    MlxRegLib *_mlxLinkLib;
    UserInput _userInput;
    mfile *_mf;
    MlxlinkLogger *_mlxlinkLogger;
    dm_dev_id_t _devID;
    u_int32_t _localPort;
    DPN _dpn;
    u_int32_t _numOfLanes;
    u_int32_t _numOfLanesPcie;
    u_int32_t _cableMediaType;
    u_int32_t _fecActive;
    u_int32_t _protoActive;
    u_int32_t _uniqueCmds;
    u_int32_t _uniqueCableCmds;
    u_int32_t _networkCmds;
    u_int32_t _anDisable;
    u_int32_t _speedBerCsv;
    u_int32_t _cableIdentifier;
    u_int32_t _cableAtten12G;
    u_int32_t _cableLen;
    u_int32_t _activeSpeed;
    u_int32_t _activeSpeedEx;
    u_int32_t _protoCapability;
    u_int32_t _protoAdmin;
    u_int32_t _protoAdminEx;
    u_int32_t _productTechnology;
    string _extAdbFile;
    string _device;
    string _fwVersion;
    string _speedStrG;
    string _speedForce;
    string _cablePN;
    string _cableSN;
    string _moduleTemp;
    bool _protoCapabilityEx;
    bool _writeGvmi;
    bool _splitted;
    bool _linkUP;
    bool _prbsTestMode;
    bool _plugged;
    bool _linkModeForce;
    bool _useExtAdb;
    bool _isHCA;
    bool _portActive;
    std::vector<std::string> _ptysSpeeds;
    std::vector<DPN> _validDpns;
    string _allUnhandledErrors;
    Json::Value _jsonRoot;
    MlxlinkMaps* _mlxlinkMaps;
};

#endif /* MLXLINK_COMMANDER_H */
