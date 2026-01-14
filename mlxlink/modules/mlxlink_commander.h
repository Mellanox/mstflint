/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include "mlxlink_cables_commander.h"
#include "mlxlink_eye_opener.h"
#include "mlxlink_err_inj_commander.h"
#include "mlxlink_port_info.h"
#include "mlxlink_amBER_collector.h"

#ifdef MST_UL
#define MLXLINK_EXEC "mstlink"
#define PKG_NAME "MSTFLINT"
#define PKG_VER MSTFLINT_VERSION_STR
#else
#define MLXLINK_EXEC "mlxlink"
#define PKG_NAME "MFT"
#define PKG_VER MFT_VERSION_STR
#endif

//------------------------------------------------------------
//        Mlxlink OPTIONS Flags

#define HELP_FLAG "help"
#define HELP_FLAG_SHORT 'h'
#define VERSION_FLAG "version"
#define VERSION_FLAG_SHORT 'v'
#define DEVICE_FLAG "device"
#define DEVICE_FLAG_SHORT 'd'
#define LABEL_PORT_FLAG "port"
#define LABEL_PORT_FLAG_SHORT 'p'
#define PORT_TYPE_FLAG "port_type"
#define PORT_TYPE_FLAG_SHORT ' '
#define DEPTH_FLAG "depth"
#define DEPTH_FLAG_SHORT ' '
#define PCIE_INDEX_FLAG "pcie_index"
#define PCIE_INDEX_FLAG_SHORT ' '
#define NODE_FLAG "node"
#define NODE_FLAG_SHORT ' '
#define PRINT_JSON_OUTPUT_FLAG "json"
#define PRINT_JSON_OUTPUT_FLAG_SHORT ' '
//------------------------------------------------------------
//        Mlxlink QUERIES Flags

#define PCIE_LINKS_FLAG "show_links"
#define PCIE_LINKS_FLAG_SHORT ' '
#define MODULE_INFO_FLAG "show_module"
#define MODULE_INFO_FLAG_SHORT 'm'
#define BER_FLAG "show_counters"
#define BER_FLAG_SHORT 'c'
#define EYE_OPENING_FLAG "show_eye"
#define EYE_OPENING_FLAG_SHORT 'e'
#define FEC_DATA_FLAG "show_fec"
#define FEC_DATA_FLAG_SHORT ' '
#define SLTP_SHOW_FLAG "show_serdes_tx"
#define SLTP_SHOW_FLAG_SHORT ' '
#define DEVICE_DATA_FLAG "show_device"
#define DEVICE_DATA_FLAG_SHORT ' '
#define BER_MONITOR_INFO_FLAG "show_ber_monitor"
#define BER_MONITOR_INFO_FLAG_SHORT ' '
#define PEPC_SHOW_FLAG "show_external_phy"
#define PEPC_SHOW_FLAG_SHORT ' '
#define MULTI_PORT_MODULE_INFO_FLAG "show_multi_port_module_info"
#define MULTI_PORT_MODULE_INFO_FLAG_SHORT ' '
#define MULTI_PORT_MODULE_INFO_ACRONYM_FLAG "smpmi"
#define MULTI_PORT_MODULE_INFO_ACRONYM_FLAG_SHORT ' '
#define MULTI_PORT_INFO_FLAG "show_multi_port_info"
#define MULTI_PORT_INFO_FLAG_SHORT ' '
#define MULTI_PORT_INFO_ACRONYM_FLAG "smpi"
#define MULTI_PORT_INFO_ACRONYM_FLAG_SHORT ' '
#define PLR_INFO_FLAG "show_plr"
#define PLR_INFO_FLAG_SHORT ' '
#define KR_INFO_FLAG "show_kr"
#define KR_INFO_FLAG_SHORT ' '
#define RX_RECOVERY_COUNTERS_FLAG "show_rx_recovery_counters"
#define RX_RECOVERY_COUNTERS_FLAG_SHORT ' '
#define BKV_GROUPS_FLAG "show_bkv_groups"
#define BKV_GROUPS_FLAG_SHORT ' '
#define BKV_GROUP_FLAG "show_bkv_group"
#define BKV_GROUP_FLAG_SHORT ' '
#define SET_BKV_GROUP_FLAG "set_bkv_group"
#define SET_BKV_GROUP_FLAG_SHORT ' '
#define BKV_RATES_FLAG "bkv_rates"
#define BKV_RATES_FLAG_SHORT ' '
#define BKV_ROLES_FLAG "bkv_roles"
#define BKV_ROLES_FLAG_SHORT ' '
#define BKV_MODE_B_ROLES_FLAG "bkv_mode_b_roles"
#define BKV_MODE_B_ROLES_FLAG_SHORT ' '
#define SET_BKV_ENTRY_FLAG "set_bkv_entry"
#define SET_BKV_ENTRY_FLAG_SHORT ' '
#define BKV_ENTRY_FLAG "bkv_entry"
#define BKV_ENTRY_FLAG_SHORT ' '
#define BKV_ADDRESS_FLAG "bkv_address"
#define BKV_ADDRESS_FLAG_SHORT ' '
#define BKV_WDATA_FLAG "wdata"
#define BKV_WDATA_FLAG_SHORT ' '
#define BKV_WMASK_FLAG "wmask"
#define BKV_WMASK_FLAG_SHORT ' '
#define PERIODIC_EQ_FLAG "show_peq"
#define PERIODIC_EQ_FLAG_SHORT ' '

//------------------------------------------------------------
//        Mlxlink COMMANDS Flags

#define PAOS_FLAG "port_state"
#define PAOS_FLAG_SHORT 'a'
#define PMAOS_FLAG "module_state"
#define PMAOS_FLAG_SHORT ' '
#define PTYS_FLAG "speeds"
#define PTYS_FLAG_SHORT 's'
#define PPLR_FLAG "loopback"
#define PPLR_FLAG_SHORT 'l'
#define PPLM_FLAG "fec"
#define PPLM_FLAG_SHORT 'k'
#define FEC_SPEED_FLAG "fec_speed"
#define FEC_SPEED_FLAG_SHORT ' '
#define SLTP_SET_FLAG "serdes_tx"
#define SLTP_SET_FLAG_SHORT ' '
#define LANE_FLAG "serdes_tx_lane"
#define LANE_FLAG_SHORT ' '
#define SLTP_TX_POLICY_FLAG "tx_params_override"
#define SLTP_TX_POLICY_FLAG_SHORT ' '
#define DATABASE_FLAG "database"
#define DATABASE_FLAG_SHORT ' '
#define PRBS_MODE_FLAG "test_mode"
#define PRBS_MODE_FLAG_SHORT ' '
#define PPRT_PRBS_FLAG "rx_prbs"
#define PPRT_PRBS_FLAG_SHORT ' '
#define PPTT_PRBS_FLAG "tx_prbs"
#define PPTT_PRBS_FLAG_SHORT ' '
#define PPRT_RATE_FLAG "rx_rate"
#define PPRT_RATE_FLAG_SHORT ' '
#define PPTT_RATE_FLAG "tx_rate"
#define PPTT_RATE_FLAG_SHORT ' '
#define PPRT_MODULATION_FLAG "rx_modulation"
#define PPRT_MODULATION_FLAG_SHORT ' '
#define PPTT_MODULATION_FLAG "tx_modulation"
#define PPTT_MODULATION_FLAG_SHORT ' '
#define PRBS_LANES_FLAG "lanes"
#define PRBS_LANES_FLAG_SHORT ' '
#define PRBS_INVERT_TX_POL_FLAG "invert_tx_polarity"
#define PRBS_INVERT_TX_POL_FLAG_SHORT ' '
#define PRBS_INVERT_RX_POL_FLAG "invert_rx_polarity"
#define PRBS_INVERT_RX_POL_FLAG_SHORT ' '
#define PRBS_DC_COUPLE_ALLOW_FLAG "dc_cpl_allow"
#define PRBS_DC_COUPLE_ALLOW_FLAG_SHORT ' '
#define FORCE_TX_ALLOWED_FLAG "force_tx_allowed"
#define FORCE_TX_ALLOWED_FLAG_SHORT ' '
#define SKIP_POWER_GOOD_CHECK_FLAG "skip_power_good_check"
#define SKIP_POWER_GOOD_CHECK_FLAG_SHORT ' '
#define SYSFS_PATH_FLAG "sysfs_path"
#define SYSFS_PATH_FLAG_SHORT ' '
#define PPRT_TUNING_TYPE_FLAG "tuning_type"
#define PPRT_TUNING_TYPE_FLAG_SHORT ' '
#define BER_COLLECT_FLAG "ber_collect"
#define BER_COLLECT_FLAG_SHORT 'b'
#define BER_LIMIT_FLAG "ber_limit"
#define BER_LIMIT_FLAG_SHORT ' '
#define ITERATION_FLAG "iteration"
#define ITERATION_FLAG_SHORT ' '
#define AMBER_COLLECT_FLAG "amber_collect"
#define AMBER_COLLECT_FLAG_SHORT ' '
#define PPCNT_CLEAR_FLAG "pc"
#define PPCNT_CLEAR_FLAG_SHORT ' '
#define PEPC_SET_FLAG "set_external_phy"
#define PEPC_SET_FLAG_SHORT ' '
#define PEPC_FORCE_MODE_FLAG "twisted_pair_force_mode"
#define PEPC_FORCE_MODE_FLAG_SHORT ' '
#define PEPC_AN_MODE_FLAG "twisted_pair_an_mode"
#define PEPC_AN_MODE_FLAG_SHORT ' '
#define PTYS_LINK_MODE_FORCE_FLAG "link_mode_force"
#define PTYS_LINK_MODE_FORCE_FLAG_SHORT ' '
#define PHY_RECOVERY_FLAG "phy_recovery"
#define PHY_RECOVERY_FLAG_SHORT ' '
#define PHY_RECOVERY_TYPE_FLAG "recovery_type"
#define PHY_RECOVERY_TYPE_FLAG_SHORT ' '
#define LINK_TRAINING_FLAG "link_training"
#define LINK_TRAINING_FLAG_SHORT ' '
#define SET_LINK_PEQ_FLAG "set_link_peq"
#define SET_LINK_PEQ_FLAG_SHORT ' '
#define PLANE_FLAG "plane"
#define PLANE_FLAG_SHORT ' '

//------------------------------------------------------------
//        Mlxlink Cable info flags
#define CABLE_FLAG "cable"
#define CABLE_FLAG_SHORT ' '
#define CABLE_DUMP_FLAG "dump"
#define CABLE_DUMP_FLAG_SHORT ' '
#define CABLE_DDM_FLAG "ddm"
#define CABLE_DDM_FLAG_SHORT ' '
#define CABLE_WRITE_FLAG "write"
#define CABLE_WRITE_FLAG_SHORT ' '
#define CABLE_READ_FLAG "read"
#define CABLE_READ_FLAG_SHORT ' '
#define WRITE_PAGE_FLAG "page"
#define WRITE_PAGE_FLAG_SHORT ' '
#define WRITE_OFFSET_FLAG "offset"
#define WRITE_OFFSET_FLAG_SHORT ' '
#define READ_LEN_FLAG "length"
#define READ_LEN_FLAG_SHORT ' '
#define CABLE_PRBS_SELECT "prbs_select"
#define CABLE_PRBS_SELECT_SHORT ' '
#define CABLE_PRBS_MODE "prbs_mode"
#define CABLE_PRBS_MODE_SHORT ' '
#define CABLE_PRBS_GEN_PAT "generator_pattern"
#define CABLE_PRBS_GEN_PAT_SHORT ' '
#define CABLE_PRBS_GEN_SWAP "swap_generator"
#define CABLE_PRBS_GEN_SWAP_SHORT ' '
#define CABLE_PRBS_GEN_INV "invert_generator"
#define CABLE_PRBS_GEN_INV_SHORT ' '
#define CABLE_PRBS_GEN_LANES "generator_lanes"
#define CABLE_PRBS_GEN_LANES_SHORT ' '
#define CABLE_PRBS_CH_PAT "checker_pattern"
#define CABLE_PRBS_CH_PAT_SHORT ' '
#define CABLE_PRBS_CH_SWAP "swap_checker"
#define CABLE_PRBS_CH_SWAP_SHORT ' '
#define CABLE_PRBS_CH_INV "invert_checker"
#define CABLE_PRBS_CH_INV_SHORT ' '
#define CABLE_PRBS_CH_LANES "checker_lanes"
#define CABLE_PRBS_CH_LANES_SHORT ' '
#define CABLE_PRBS_LANE_RATE "lane_rate"
#define CABLE_PRBS_LANE_RATE_SHORT ' '
#define CABLE_PRBS_SHOW_DIAG "show_diagnostic_info"
#define CABLE_PRBS_SHOW_DIAG_SHORT ' '
#define CABLE_PRBS_CLEAR_DIAG "clear_diagnostic_info"
#define CABLE_PRBS_CLEAR_DIAG_SHORT ' '
#define CTRL_PARAM_FLAG "control_parameters"
#define CTRL_PARAM_FLAG_SHORT ' '
#define CTRL_PARAM_TX_EQ_FLAG "tx_equalization"
#define CTRL_PARAM_TX_EQ_FLAG_SHORT ' '
#define CTRL_PARAM_RX_EMPH_FLAG "rx_emphasis"
#define CTRL_PARAM_RX_EMPH_FLAG_SHORT ' '
#define CTRL_PARAM_RX_POST_EMPH_FLAG "rx_post_emphasis"
#define CTRL_PARAM_RX_POST_EMPH_FLAG_SHORT ' '
#define CTRL_PARAM_RX_AMP_FLAG "rx_amplitude"
#define CTRL_PARAM_RX_AMP_FLAG_SHORT ' '

#define SHOW_TX_GROUP_MAP_FLAG "show_tx_group_map"
#define SHOW_TX_GROUP_MAP_FLAG_SHORT ' '
#define SET_TX_GROUP_MAP_FLAG "tx_group_map"
#define SET_TX_GROUP_MAP_FLAG_SHORT ' '
#define TX_GROUP_PORTS_FLAG "ports"
#define TX_GROUP_PORTS_FLAG_SHORT ' '
//------------------------------------------------------------
//        Mlxlink Eye Opener Flags
#define MARGIN_SCAN_FLAG "margin"
#define MARGIN_SCAN_FLAG_SHORT ' '
#define EYE_SEL_FLAG "eye_select"
#define EYE_SEL_FLAG_SHORT ' '
#define EYE_MEASURE_TIME_FLAG "measure_time"
#define EYE_MEASURE_TIME_FLAG_SHORT ' '
#define LANE_INDEX_FLAG "lane"
#define LANE_INDEX_FLAG_SHORT ' '
#define FORCE_YES_FLAG "yes"
#define FORCE_YES_FLAG_SHORT ' '

//------------------------------------------------------------
//        Mlxlink Error Injection Flags
#define PREI_RX_ERR_INJ_FLAG "rx_error_injection"
#define PREI_RX_ERR_INJ_FLAG_SHORT ' '
#define PREI_MIXER_OFFSET_0 "mixer_offset0"
#define PREI_MIXER_OFFSET_0_SHORT ' '
#define PREI_MIXER_OFFSET_1 "mixer_offset1"
#define PREI_MIXER_OFFSET_1_SHORT ' '
#define PREI_SHOW_MIXERS_FLAG "show_mixers_offset"
#define PREI_SHOW_MIXERS_FLAG_SHORT ' '

//------------------------------------------------------------
//        Mlxlink PCIE Error Injection Flags
#define MPEINJ_PCIE_ERR_INJ_FLAG "pcie_error_injection"
#define MPEINJ_PCIE_ERR_INJ_FLAG_SHORT ' '
#define MPEINJ_ERR_TYPE_FLAG "error_type"
#define MPEINJ_ERR_TYPE_FLAG_SHORT ' '
#define MPEINJ_ERR_DURATION_FLAG "error_duration"
#define MPEINJ_ERR_DURATION_FLAG_SHORT ' '
#define MPEINJ_INJ_DELAY_FLAG "injection_delay"
#define MPEINJ_INJ_DELAY_FLAG_SHORT ' '
#define MPEINJ_ERR_PARAMETERS_FLAG "error_parameters"
#define MPEINJ_ERR_PARAMETERS_FLAG_SHORT ' '
#define MPEINJ_DBDF_FLAG "dbdf"
#define MPEINJ_DBDF_FLAG_SHORT ' '

//------------------------------------------------------------
//        Histogram Counters Flags
#define PPHCR_FEC_HIST_FLAG "rx_fec_histogram"
#define PPHCR_FEC_HIST_FLAG_SHORT ' '
#define PPHCR_SHOW_FEC_HIST_FLAG "show_histogram"
#define PPHCR_SHOW_FEC_HIST_FLAG_SHORT ' '
#define PPHCR_CLEAR_HISTOGRAM_FLAG "clear_histogram"
#define PPHCR_CLEAR_HISTOGRAM_FLAG_SHORT ' '

//------------------------------------------------------------
//        Mlxlink HIDDEN Flags

#define SLTP_SET_ADVANCED_FLAG "advanced"
#define SLTP_SET_ADVANCED_FLAG_SHORT ' '
#define GVMI_ADDRESS_FLAG "gvmi_address"
#define GVMI_ADDRESS_FLAG_SHORT ' '
#define LOG_FLAG "log"
#define LOG_FLAG_SHORT ' '

//------------------------------------------------------------

#define REG_ACCESS_UNION_NODE "access_reg_summary"

//------------------------------------------------------------
//        Mlxlink commands enumerations
enum OPTION_TYPE
{
    SHOW_PDDR = 1,
    SHOW_PCIE,
    SHOW_BER,
    SHOW_EYE,
    SHOW_FEC,
    SHOW_SLTP,
    SHOW_BKV,
    SHOW_BKV_GROUP,
    SET_BKV_GROUP,
    SET_BKV_ENTRY,
    SHOW_SLRP,
    SHOW_MODULE,
    SHOW_DEVICE,
    SHOW_BER_MONITOR,
    SHOW_EXTERNAL_PHY,
    SHOW_LINK_DOWN_BLAME,
    SHOW_TX_GROUP_MAP,
    CABLE_SHOW_DUMP,
    CABLE_SHOW_DDM,
    CABLE_EEPROM_WRITE,
    CABLE_EEPROM_READ,
    CABLE_PRBS_CMDS,
    CABLE_CTRL_PARM,
    SEND_BER_COLLECT,
    SEND_AMBER_COLLECT,
    SEND_PAOS,
    SEND_PMAOS,
    SEND_PTYS,
    SEND_PPLM,
    SEND_PPLR,
    SEND_PRBS,
    SEND_SLTP,
    SEND_CLEAR_COUNTERS,
    SEND_PEPC,
    SHOW_PCIE_LINKS,
    SET_TX_GROUP_MAP,
    GRADE_SCAN_ENABLE,
    ERR_INJ_ENABLE,
    RS_FEC_HISTOGRAM,
    SLRG_TEST,
    PCIE_ERROR_INJ,
    SHOW_MULTI_PORT_INFO,
    SHOW_MULTI_PORT_MODULE_INFO,
    SHOW_PLR,
    SHOW_KR,
    SHOW_RX_RECOVERY_COUNTERS,
    SEND_PHY_RECOVERY,
    SEND_LINK_TRAINING,
    SHOW_PERIODIC_EQ,
    SET_PERIODIC_EQ,

    // Any new function's index should be added before FUNCTION_LAST in this enum
    FUNCTION_LAST
};

///////////
class ModuleField
{
public:
    ModuleField(string uiName, string amberName, bool multiVal, bool perLane, bool requireDdm, bool supported = true);
    ~ModuleField() = default;

    string uiName;
    string amberName;
    bool multiVal;
    bool perLane;
    bool requireDdm;
    bool supported;
};

using namespace std;

class MlxlinkCommander : public MlxlinkRegParser
{
public:
    MlxlinkCommander();
    virtual ~MlxlinkCommander();

    void checkRegCmd();
    bool isBackplane();
    void validatePortToLC();
    virtual void validatePortType(const string& portTypeStr);
    void updatePortType();
    void gearboxBlock(const string& option);
    void checkLocalPortDPNMapping(u_int32_t localPort);
    int getLocalPortFromMPIR(DPN& dpn);
    void checkValidFW();
    u_int32_t getTechnologyFromMGIR();
    void getProductTechnology();
    bool checkPortStatus(u_int32_t localPort);
    void checkAllPortsStatus();
    void handlePortStr(const string& portStr);
    void labelToLocalPort();
    void findFirstValidPort();
    void labelToHCALocalPort();
    void labeltoDSlocalPort();
    bool isDSdevice();
    void labelToLocalPortGenericMapping();
    void labelToIBLocalPort();
    bool isIBSplitReady();
    u_int32_t calculatePanelPort(bool ibSplitReady);
    u_int32_t maxLocalPort();
    void checkStrLength(const string& str);
    void getActualNumOfLanes(u_int32_t linkSpeedActive, bool extended);
    u_int32_t activeSpeed2gNum(u_int32_t mask, bool extended);
    string activeSpeed2Str(u_int32_t mask, bool extended, bool isXdrSlowActive = false);
    void getCableParams();
    bool inPrbsTestMode();
    bool checkGBPpaosDown();
    bool checkPaosDown();
    bool checkPpaosTestMode();
    bool isSpect2WithGb();
    bool isIbLocalPortValid(u_int32_t localPort);
    void fillIbPortGroupMap(u_int32_t localPort, u_int32_t labelPort, u_int32_t group, bool splitReady);
    void
      fillEthPortGroupMap(u_int32_t localPort, u_int32_t labelPort, u_int32_t group, u_int32_t width, bool spect2WithGb);
    bool handleIBLocalPort(u_int32_t labelPort, bool ibSplitReady);
    void handleAllEthLocalPorts(std::vector<string> labelPortsStr, bool spect2WithGb, bool skipException);
    void handleAllGPULocalPorts(std::vector<string> labelPortsStr, bool skipException);
    void handleAllNewSwitchesLocalPorts(std::vector<string> labelPortsStr, bool skipException);
    void handleLabelPorts(std::vector<string> labelPortsStr, bool skipException = false);
    vector<string> localToPortsPerGroup(vector<u_int32_t> localPorts);
    u_int32_t getPortGroup(u_int32_t localPort);
    string getValuesOfActiveLanes(const string& row, bool moduleLanes = false);
    bool checkIfModuleExtSupported();

    // Mlxlink query functions
    virtual void showModuleInfo();
    virtual void operatingInfoPage();
    virtual void supportedInfoPage();
    virtual void troubInfoPage();
    void showPddr();
    void getPtys();
    virtual void showBer();
    virtual void showEye();
    virtual void showFEC();
    virtual void showSltp();
    virtual void showBkv();
    virtual void showBkvGroup(bool showEntries = true, u_int32_t entryFilter = (u_int32_t)-1);
    virtual void setBkvGroup();
    virtual void setBkvEntry();
    void queryBkvCaps(uint8_t& numGroups, uint8_t groupId = (uint8_t)-1);
    void queryBkvCaps(uint8_t& numGroups,
                      uint8_t& numEntries,
                      uint8_t groupId = (uint8_t)-1,
                      uint8_t entryId = (uint8_t)-1);
    void showDeviceData();
    void showBerMonitorInfo();
    void showExternalPhy();
    void showPcie();
    void showPcieLinks();
    virtual void collectAMBER();
    void collectBER();
    void showTxGroupMapping();
    void showPlr();
    void showKr();
    void showRxRecoveryCounters();
    void showPeriodicEq();
    void setPeriodicEq();

    // Query helper functions
    string getCableTechnologyStr(u_int32_t cableTechnology);
    string getCompliaceLabelForCIMIS(u_int32_t hostCompliance, u_int32_t mediaCompliance);
    string getComplianceLabel(u_int32_t compliance, u_int32_t extCompliance, bool ignoreExtBitChk = false);
    string getCableTypeStr(u_int32_t cableType);
    void prepareStaticInfoSection(bool valid);
    void prepareAttenuationAndFwSection(bool valid);
    void preparePowerAndCdrSection(bool valid);
    void prepareDDMSection(bool valid, bool isModuleExtSupported);
    virtual void preparePrtlSection();
    template<typename T, typename Q>
    string getValueAndThresholdsStr(T value, Q lowTH, Q highTH);
    string getSltpFieldStr(const PRM_FIELD& field);
    void prepareSltpEdrHdrGen(vector<vector<string>>& sltpLanes, u_int32_t laneNumber);
    virtual void prepareSltpNdrGen(vector<vector<string>>& sltpLanes, u_int32_t laneNumber);
    virtual void prepareSltpXdrGen(vector<vector<string>>& sltpLanes, u_int32_t laneNumber);
    virtual string getSltpHeader();
    void startSlrgPciScan(u_int32_t numOfLanesToUse);
    void initValidDPNList();
    void updateDPNDomain();
    u_int32_t readBitFromField(const string& fieldName, u_int32_t bitIndex);
    string getSupportedFecForSpeed(const string& speed);
    string fecMaskToUserInputStr(u_int32_t fecCapMask);
    string fecMaskToStr(u_int32_t mask);
    void updateSwControlStatus();
    void initSwControledModule();
    u_int32_t getNumberOfPorts();
    bool checkDPNvSupport();
    void prepareBerModuleInfo(bool valid, const vector<AmberField>& moduleInfoFields);
    void pushSnrModuleInfoFields(bool valid);
    void runningVersion();
    void prepare40_28_16nmEyeInfo(u_int32_t numOfLanesToUse);
    void prepare7nmEyeInfo(u_int32_t numOfLanesToUse);
    void prepare5nmEyeInfo(u_int32_t numOfLanesToUse);
    void getPddrOperInfo();
    bool isTransmitAllowed(u_int32_t localPort, u_int32_t protoActive);

    void showTestMode();
    void showTestModeBer();
    void showMpcntPerformance(DPN& dpn);
    void showMpcntTimers(DPN& dpn);
    void showMpcntLane();
    void showPcieState(DPN& dpn);
    void checkPCIeValidity();
    virtual void prepareBerInfo();
    virtual void prepareBerInfoEDR();
    virtual void getPcieNdrCounters(u_int32_t flitActive = 0);
    virtual vector<AmberField> getBerFields();

    std::map<std::string, std::string> getPprt();
    std::map<std::string, std::string> getPptt();

    std::map<string, string> getRawEffectiveErrors();
    std::map<string, string> getRawEffectiveErrorsinTestMode();
    int prbsModeToMask(const string& mode);
    string prbsMaskToMode(u_int32_t mask, u_int32_t modeSelector);
    string getPrbsModeRX();
    u_int32_t getPrbsRateRX();
    string getSupportedPrbsRates(u_int32_t modeSelector);
    string getSupportedPrbsModes(u_int32_t modeSelector);
    u_int32_t getLoopbackMode(const string& lb);
    string getLoopbackStr(u_int32_t loopbackCapMask);
    int getLinkDown();
    float getRawBERLimit();
    bool getResult(std::map<std::string, float> errors_vector, float raw_ber_limit, int link_down);
    string getDevicePN();
    virtual string getFwVersion();
    void printOuptputVector(vector<MlxlinkCmdPrint>& cmdOut);
    virtual void prepareJsonOut();

    // Cable operation
    bool isPassiveQSFP();
    bool isSFP51Paging();
    void initCablesCommander();
    void initEyeOpener();
    void initErrInj();
    void initPortInfo();
    void setAmBerCollectorFields();
    virtual void initAmBerCollector();
    void showCableDump();
    void showCableDDM();
    vector<u_int8_t> validateBytes(const vector<string>& strBytes);
    void writeCableEEPROM();
    void readCableEEPROM();
    void performModulePrbsCommands();
    void performControlParams();

    MlxlinkCmdPrint _toolInfoCmd;
    MlxlinkCmdPrint _operatingInfoCmd;
    MlxlinkCmdPrint _supportedInfoCmd;
    MlxlinkCmdPrint _troubInfoCmd;
    MlxlinkCmdPrint _testModeInfoCmd;
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
    MlxlinkCmdPrint _cableDumpRawCmd;
    MlxlinkCmdPrint _cableDDMCmd;
    MlxlinkCmdPrint _portGroupMapping;
    MlxlinkCmdPrint _plrInfoCmd;
    MlxlinkCmdPrint _krInfoCmd;
    MlxlinkCmdPrint _rxRecoveryCountersCmd;
    MlxlinkCmdPrint _periodicEqInfoCmd;

    // Mlxlink config functions
    void clearCounters();
    void sendPaos();
    void sendPmaos();
    virtual void handlePrbs();
    virtual void handlePrbsSWControlledChecks();
    void sendPtys();
    virtual void sendPplm();
    virtual void sendSltp();
    void sendPplr();
    void sendPepc();
    void setTxGroupMapping();
    void handleRxErrInj();
    void handlePCIeErrInj();
    void handlePhyRecovery();
    void handleLinkTraining();

    // Config helper functions
    bool isForceDownSupported();
    bool isPmaosResetToggleSupported();
    bool isPPHCRSupported();
    void sendGBPaosCmd(PAOS_ADMIN adminStatus, bool forceDown);
    void sendPaosCmd(PAOS_ADMIN adminStatus, bool forceDown = false);
    void sendPaosDown(bool toggleCommand = false);
    void sendPaosUP();
    void sendPaosToggle();
    void sendPmaosDown();
    void sendPmaosUP();
    void sendPmaosToggle();
    void sendPmaosCmd(PMAOS_ADMIN adminStatus);
    bool checkPmaosDown();
    void checkPRBSModeCap(u_int32_t modeSelector, u_int32_t capMask);
    void checkPrbsRegsCap(const string& prbsReg, const string& laneRate);
    void checkPrbsModulation(const string& prbsReg);
    void checkPrbsPolCap(const string& prbsReg);
    void checkPprtPptt();
    void checkDcCouple();
    void checkPplrCap();
    void sendPrbsPpaos(bool testMode, bool dc_cpl_allow = false);
    void startTuning();
    void prbsConfiguration(const string& prbsReg,
                           bool enable,
                           u_int32_t laneRate,
                           u_int32_t prbsMode,
                           bool perLaneConfig,
                           bool prbsPolInv,
                           u_int32_t modulation = PRBS_MODULATION_DEFAULT);
    void sendPprtPptt();
    void resetPprtPptt();
    u_int32_t ptysSpeedToMask(const string& speed);
    void validateSpeedStr();
    void checkSupportedSpeed(const string& speed, u_int32_t cap, bool extSpeed = false);
    string speedToFecSpeedStr(const string& speed, u_int32_t numOfLanes);
    u_int32_t fecToBit(const string& fec, const string& speedStrG);
    u_int32_t getFecCapForCheck(const string& speedStr);
    void checkPplmCap();
    string updateSltpEdrHdrFields();
    string updateSltpNdrFields();
    virtual string updateSltpXdrFields();
    string getSltpStatus();
    void getSltpAlevOut(u_int32_t lane);
    void getSltpRegAndLeva(u_int32_t lane);
    u_int32_t getLaneSpeed(u_int32_t lane);
    void validateNumOfParamsForNDRGen();
    void validateNumOfParamsForXDRGen();
    void checkSltpParamsSize();
    bool isMpeinjSupported();
    u_int32_t getRateFromPptt();
    void showMultiPortInfo();
    void showMultiPortModuleInfo();
    string getBerString();
    void updateLocalPortGroup();
    std::string getSpeedStrForTableView();
    bool checkAllPortsDown();
    void configurePeqForAllPorts(bool brLanesCap);
    void setPlaneIndex(int planeIndex);

    // Mlxlink params
    UserInput _userInput;
    dm_dev_id_t _devID;
    DPN _dpn;
    vector<u_int32_t> _moduleLanesMapping;
    u_int32_t _numOfLanes;
    u_int32_t _numOfLanesPcie;
    u_int32_t _cableMediaType;
    u_int32_t _fecActive;
    u_int32_t _protoActive;
    int _phyMngrFsmState;
    u_int32_t _anDisable;
    u_int32_t _speedBerCsv;
    u_int32_t _cableIdentifier;
    u_int32_t _cableTechnology;
    u_int32_t _cableAtten12G;
    u_int32_t _cableLen;
    u_int32_t _activeSpeed;
    u_int32_t _activeSpeedEx;
    bool _isXdrSlowActive;
    u_int32_t _laneSpeedFromPptt;
    u_int32_t _protoCapability;
    u_int32_t _deviceCapability;
    u_int32_t _protoAdmin;
    u_int32_t _protoAdminEx;
    u_int32_t _productTechnology;
    u_int32_t _moduleNumber;
    u_int32_t _slotIndex;
    u_int32_t _linkSpeed;
    u_int32_t _groupOpcode;
    u_int32_t _loopbackMode;
    string _extAdbFile;
    string _fwVersion;
    string _speedStrG;
    string _speedForce;
    string _cablePN;
    string _cableSN;
    string _moduleTemp;
    bool _protoCapabilityEx;
    bool _linkUP;
    bool _prbsTestMode;
    bool _plugged;
    bool _linkModeForce;
    bool _useExtAdb;
    bool _ddmSupported;
    u_int32_t _temperature;
    bool _cmisCable;
    bool _qsfpCable;
    bool _portPolling;
    bool _mngCableUnplugged;
    bool _isPam4Speed;
    bool _ignorePortType;
    bool _ignorePortStatus;
    bool _isGboxPort;
    bool _isSwControled;
    bool _isSwControledStandAlone;
    bool _ignoreIbFECCheck;
    bool _isNVLINK;
    std::vector<PortGroup> _localPortsPerGroup;
    std::vector<DPN> _validDpns;
    string _allUnhandledErrors;
    Json::Value _jsonRoot;
    MlxlinkMaps* _mlxlinkMaps;
    MlxlinkCablesCommander* _cablesCommander;
    MlxlinkEyeOpener* _eyeOpener;
    MlxlinkErrInjCommander* _errInjector;
    MlxlinkPortInfo* _portInfo;
    MlxlinkAmBerCollector* _amberCollector;
    string _fomStr;

protected:
    vector<AmberField> _ppcntFields;

    // New helper functions for port info display
    string getLabelPortString(const PortGroup& portInfo);
    void updatePortModuleInfo(vector<string>& tableData, const PortGroup& portInfo, u_int32_t& posToUpdateWidthInVector);
    void updatePortInfo(vector<string>& tableData, const PortGroup& portInfo, u_int32_t& posToUpdateWidthInVector);
    void updatePortStatisticalInfo(vector<string>& tableData, u_int32_t& posToUpdateWidthInVector);
};

#endif /* MLXLINK_COMMANDER_H */
