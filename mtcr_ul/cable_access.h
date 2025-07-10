#ifndef _CABLE_ACCESS_
#define _CABLE_ACCESS_


#include <string>
#include "mtcr.h"
#include "dev_mgt/tools_dev_types.h"
 
 using namespace std;
 
 #define ID_LEN 16
 #define CMIS_FIRST_8_APP_LEN 32
 #define CMIS_LAST_7_APP_LEN 28
 #define CABLE_PAGE_SIZE 0x100
 
 typedef enum
 {
     FW_UPGRADE = 0x1,
     FW_READ_DB,
     FW_VERIFY_NEW,
     CMD_RESET = 0xb1,
     CMD_LOAD_APP = 0x1d,
     CMD_LOAD_APP_NO_CONF = 0x2d,
     /*
      * New GW commands
      */
     ISFU_CMD_UPDATE_FW = 0x11,
     ISFU_CMD_LOAD_FW_REINIT = 0x12,
     ISFU_CMD_LOAD_FW_IN_SERVICE = 0x13,
     ISFU_CMD_RESET_MODULE = 0x14,
     ISFU_CMD_FINALIZE_BURN = 0x15,
     ISFU_CMD_READ_FW_VER = 0x16,
 } cable_op_t;
 
 typedef enum
 {
     RECORD_CRC,
     OPCODE,
     FW_UPDATE_STATUS,
     HASH_ID,
     OPERATION_STATUS,
     IMAGE_SIZE,
     IMAGE_SIZE_CHECKSUM,
     SEQUENCE_NUM,
 } attr_t;
 
 enum
 {
     ATTR_IDENTIFIER = 0x1,
     ATTR_OPERATION_STATUS = 0x2,
     ATTR_FWUP_STATUS = 0x4,
     ATTR_FW_GW_REV = 0x8,
     ATTR_FW_GW_MIN_REV = 0x10,
     ATTR_FW_REV = 0x20,
     ATTR_EXPECTED_SN = 0x40,
     ATTR_DEV_FW_ID = 0x80,
     ATTR_IMAGE_SIZE = 0x100,
     ATTR_HASH_ID = 0x200,
     ATTR_STATUS = 0x400,
 };
 
 enum
 {
     FW_ID_THUNDER = 0x20,
     FW_ID_LIGHTNING,
     FW_ID_ISFU
 };
 
 typedef struct
 {
     u_int16_t identifier;
     u_int16_t operation_status;
     u_int16_t fw_update_status;
     u_int8_t fw_gw_revision;
     u_int8_t fw_gw_minor_revision;
     u_int32_t fw_revision;
     u_int16_t expected_sn;
     u_int16_t device_fw_id;
     u_int16_t image_size;
     u_int8_t hash_id;
     u_int8_t status;
     u_int32_t valid_mask;
 } cable_gw_attr_t;
 
 typedef struct
 {
     char vendor[ID_LEN + 1];
     char partNumber[ID_LEN + 1];
     char serialNumber[ID_LEN + 1];
     u_int8_t OUI[3];
     char rev[5];
     u_int8_t length;
     u_int8_t length_in_decimeter; // 1 [dm] = 0.1 [m]
     u_int8_t length_new_fb_arch;
     u_int8_t guage;
     u_int8_t temp;
     u_int8_t identifier;
     u_int8_t device_technology;
     u_int8_t device_tech_valid;
     u_int8_t sfp_device_tech_valid;
     u_int8_t cmis_connector_type_valid;
     u_int8_t cmis_power_valid;
     u_int8_t compliance;
     u_int8_t compliance_valid;
     u_int8_t ext_compliance;
     u_int8_t ext_compliance_valid;
     u_int8_t wavelength_or_attenuation[2];
     u_int8_t wavelength_tolerance_or_attenuation[2];
     u_int8_t length_om1;
     u_int8_t attenuation_valid;
     u_int8_t connector_type;
     u_int8_t infiniband_speed;
     u_int8_t cdr_rx;
     u_int8_t cdr_tx;
     u_int16_t volt;
     u_int8_t power_class;
     u_int8_t cmis_max_power;
     u_int8_t attenuation_5g;
     u_int8_t attenuation_7g;
     u_int8_t attenuation_12g;
     u_int8_t attenuation_25g;
     u_int8_t fw_version_minor;
     u_int8_t fw_version_major;
     u_int16_t wavelength_cmis;
     u_int8_t cmis_module_media_type;
     u_int8_t cmis_connector_type;
     u_int8_t cmis_cable_tech;
     u_int8_t cmis_ext_ethernet_compliance_code;
     u_int8_t cmis_ethernet_compliance_code;
     u_int16_t bias_current[8];
     u_int16_t rx_power_current[8];
     u_int16_t tx_power_current[8];
     u_int8_t cmis_app_date[60];
 } cable_ids_t;
 
 typedef struct
 {
     u_int16_t val;
     u_int16_t high_warn;
     u_int16_t low_warn;
     u_int16_t high_alarm;
     u_int16_t low_alarm;
     u_int32_t warning;
     u_int32_t alarm;
 } ddm_thres_t;
 
 typedef struct
 {
     ddm_thres_t temperature;
     ddm_thres_t voltage;
     ddm_thres_t rx_power[4];
     ddm_thres_t tx_power[4];
     ddm_thres_t tx_bias[4];
     int channels;
 } cable_ddm_q_t;
 
 typedef enum
 {
     CBL_SUCCESS,
     CBL_HEADER_ERR = 0x100,
     CBL_OP_NOT_SUPP,
     CBL_FAILED,
 
     ISFU_ST_INIT = 0x0,
     ISFU_ST_SUCCESS,
     ISFU_ST_CMD_NOT_SUPP,
     ISFU_ST_FWUP_PSN_ERR,
     ISFU_ST_FLASH_WRITE_ERR,
     ISFU_ST_FW_BURN_IN_PROCESS,
     ISFU_ST_FW_LOAD_FAILED
 } CBL_ERROR;
 
 enum EXT_ETH_COMPLIANCE
 {
     EXT_ETH_COMPLIANCE_Unspecified = 0,
     EXT_ETH_COMPLIANCE_100G_AOC_FEC = 0x1,
     EXT_ETH_COMPLIANCE_100GBASE_SR4 = 0x2,
     EXT_ETH_COMPLIANCE_100GBASE_LR4 = 0x3,
     EXT_ETH_COMPLIANCE_100GBASE_ER4 = 0x4,
     EXT_ETH_COMPLIANCE_100GBASE_SR10 = 0x5,
     EXT_ETH_COMPLIANCE_100G_CWDM4 = 0x6,
     EXT_ETH_COMPLIANCE_100G_PSM4 = 0x7,
     EXT_ETH_COMPLIANCE_100G_ACC_FEC = 0x8,
     EXT_ETH_COMPLIANCE_100GBASE_CR4 = 0xB,
     EXT_ETH_COMPLIANCE_25GBASE_CR_CA_S = 0xC,
     EXT_ETH_COMPLIANCE_25GBASE_CR_CA_N = 0xD,
     EXT_ETH_COMPLIANCE_40GBASE_ER4 = 0x10,
     EXT_ETH_COMPLIANCE_4_x_10GBASE_SR = 0x11,
     EXT_ETH_COMPLIANCE_40G_PSM4 = 0x12,
     EXT_ETH_COMPLIANCE_G959_1_P1I1_2D1 = 0x13,
     EXT_ETH_COMPLIANCE_G959_1_P1S1_2D2 = 0x14,
     EXT_ETH_COMPLIANCE_G959_1_P1L1_2D2 = 0x15,
     EXT_ETH_COMPLIANCE_10GBASE_T = 0x16,
     EXT_ETH_COMPLIANCE_100G_CLR4 = 0x17,
     EXT_ETH_COMPLIANCE_100G_AOC = 0x18,
     EXT_ETH_COMPLIANCE_100G_ACC = 0x19,
     EXT_ETH_COMPLIABCE_100G_DWDM2 = 0X1A,
     EXT_ETH_COMPLIABCE_100G_1550NM_WDM = 0X1B,
     EXT_ETH_COMPLIABCE_10GBASE_T = 0X1C,
     EXT_ETH_COMPLIABCE_5GBASE_T = 0X1D,
     EXT_ETH_COMPLIABCE_2_5GBASE_T = 0X1E,
     EXT_ETH_COMPLIABCE_40G_SWDM4 = 0X1F,
     EXT_ETH_COMPLIABCE_100G_SWDM4 = 0X20,
     EXT_ETH_COMPLIABCE_100G_PAM4 = 0X21,
     EXT_ETH_COMPLIABCE_4WDM10_MSA = 0X22,
     EXT_ETH_COMPLIABCE_4WDM20_MSA = 0X23,
     EXT_ETH_COMPLIABCE_4WDM40_MSA = 0X24,
     EXT_ETH_COMPLIABCE_100GBASE_DR = 0X25,
     EXT_ETH_COMPLIABCE_100G_FR = 0X26,
     EXT_ETH_COMPLIABCE_100G_LR = 0X27,
     EXT_ETH_COMPLIABCE_ACC_10_6 = 0X30,
     EXT_ETH_COMPLIABCE_AOC_10_6 = 0X31,
     EXT_ETH_COMPLIABCE_ACC_10_4 = 0X32,
     EXT_ETH_COMPLIABCE_AOC_10_4 = 0X33,
     EXT_ETH_COMPLIABCE_50GBASE_CR = 0X40,
     EXT_ETH_COMPLIABCE_50GBASE_SR = 0X41,
     EXT_ETH_COMPLIABCE_50GBASE_FR = 0X42,
     EXT_ETH_COMPLIABCE_200GBASE_FR4 = 0X43,
     EXT_ETH_COMPLIABCE_200GBASE_1550NM_PSM4 = 0X44,
     EXT_ETH_COMPLIABCE_50GBASE_LR = 0X45,
     EXT_ETH_COMPLIABCE_200GBASE_LR4 = 0X46
 };
 
 enum ETHERNET_COMPLIANCE_CODE
 {
     COMPLIANCE_CODE_Unspecified = 0,
     COMPLIANCE_CODE_40G_ACTIVE_CABLE_XLPPI = 0x1,
     COMPLIANCE_CODE_40GBASE_LR4 = 0x2,
     COMPLIANCE_CODE_40GBASE_SR4 = 0x4,
     COMPLIANCE_CODE_40GBASE_CR4 = 0x8,
     COMPLIANCE_CODE_10GBASE_SR = 0x10,
     COMPLIANCE_CODE_10GBASE_LR = 0x20,
     COMPLIANCE_CODE_10GBASE_LRM = 0x40,
     COMPLIANCE_CODE_EXT = 0x80,
 };
 
 struct reg_val
 {
     string reg_name;
     vector<u_int8_t> reg_bytes;
     u_int32_t offset;
     u_int32_t length;
 };
 
 struct classcomp
 {
     bool operator()(const string& lhs, const string& rhs) const
     {
         int cmp = lhs.compare(0, 6, rhs.substr(0, 6));
         if (cmp != 0)
         {
             return (cmp < 0);
         }
         return (lhs.compare(7, 3, "low") == 0);
     }
 };
 
 typedef struct
 {
     u_int8_t page_num;
     u_int8_t offset;
     u_int8_t size;
 } page_info_t;
 
 
 class cableAccess
 {
 public:
    cableAccess();
    cableAccess(const char* mstDevName, mfile* mf = NULL);
    ~cableAccess();
    bool init();

    bool read(u_int32_t addr, u_int32_t len, u_int8_t* data);
    bool write(u_int32_t addr, u_int32_t len, u_int8_t* data);

    string getLastErrMsg();
    void setBurnFlow(bool isBurnFlow);
 
 private:
 
     mfile* _mf;
     bool _mfCreatedInClass;
     dm_dev_id_t _cable_type;
     bool _deviceOpened;
     unsigned _lidNumber;
     string _mstDevName;
     bool _isLegacyGw;
     bool _fwUpPageOpened;
     bool _supportFwUp;
     cable_gw_attr_t _attr;
     string _fieldName;
     u_int32_t _pageFields;
     cable_ids_t _cblIds;
     string _pageOpened;
     string _errMsg;
 };
 
 #endif /* _CABLE_ACCESS_ */
 