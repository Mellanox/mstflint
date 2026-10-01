<NodesDefinition version="2">
<config  define="REWRITE_ACTION_INVALID=0x0" />
<config  define="REWRITE_ACTION_SET=0x1" />
<config  define="REWRITE_ACTION_ADD=0x2" />
<config  define="REWRITE_ACTION_COPY=0x3" />
<config  define="REWRITE_ACTION_INSERT=0x4" />
<config  define="REWRITE_ACTION_REMOVE=0x5" />
<config  define="REWRITE_ACTION_NOP=0x6" />
<config  define="REWRITE_ACTION_REMOVE_WORDS=0x7" />
<config  define="REWRITE_ACTION_FIELD_TO_FIELD=0x8" />
<config  define="REWRITE_ACTION_EXE_CTRL=0x9" />
<config  define="REWRITE_ACTION_FLOW_TIMESTAMP=0xa" />
<config  define="REWRITE_ACTION_PACKET_OP=0xe" />
<config  define="REWRITE_ACTION_LAST=0xe" />
<config  hidden_field_attr="reset_domain" />
<config  hidden_node_attr="reset_domain" />
<config  include_path="../../shared/mng/adabe;../../shared/phy/adabe/;" />
<config  define="GOLAN_DEVREVID=5110" />
<config  define="SHOMRON_DEVREVID=5120" />
<config  define="DOTAN_DEVREVID=5130" />
<config  define="GALIL_DEVREVID=5140" />
<config  define="BLUEFIELD_DEVREVID=5150" />
<config  define="NEGEV_DEVREVID=5160" />
<config  define="ARAVA_DEVREVID=5170" />
<config  define="VIPER_DEVREVID=5180" />
<config  define="TAMAR_DEVREVID=5190" />
<config  define="CARMEL_DEVREVID=5200" />
<config  define="MUSTANG_DEVREVID=5210" />
<config  define="GILBOA_DEVREVID=5220" />
<config  define="ARGAMAN_DEVREVID=5230" />
<config  define="ALPINE_DEVREVID=5240" />
<config  define="__HCA_DEV__" />
<config  include_path=".;../../shared/flash/adabe" />
<config  field_mand="name,descr,size" />
<config  field_attr="name" type="ascii" />
<config  field_attr="descr" type="ascii" />
<config  field_attr="size" type="hexa" />
<config  field_attr="default" type="hexa" />
<config  field_attr="variables" pattern="^((.+=.+)$|(.+=.+)[\s+$])+" type="ascii" />
<config  field_attr="rtl_path" type="ascii" />
<config  field_attr="rtl_name" type="ascii" />
<config  field_attr="rtl_sample_req" type="ascii" />
<config  field_attr="rtl_sample_res" type="ascii" />
<config  field_attr="waive_atomic_access" pattern="^[0-1]$|^$" type="bool" />
<config  field_attr="waive_generic_field" pattern="^[0-1]$|^$" type="bool" />
<config  field_attr="manual_align" pattern="^[0-1]$|^$" type="bool" />
<config  field_attr="dv_manual_check" pattern="^[0-1]$|^$" type="bool" />
<config  field_attr="idle_range" pattern="(\[(0x)?[a-fA-F0-9]+(\.\.(0x)?[a-fA-F0-9]+)?\](,|$))+" type="ascii" />
<config  field_attr="enum" type="enumval" />
<config  field_attr="enum_name" type="ascii" />
<config  field_attr="meta_data" type="ascii" />
<config  field_attr="esn" pattern="(0x)?[0-9a-fA-F]+([a-fA-F0-9])?" type="hexa" used_for="node" />
<config  field_attr="rbv_ref" type="ascii" />
<config  field_attr="broken32" pattern="^[0-1]$|^$" type="bool" />
<config  field_attr="missing_sons" type="ascii" />
<config  define="DEVREVID=5220" />
<config  field_attr="access_type" pattern="RW|RO|WO|ReadSet|WriteOne" type="enum" >
	<enum  name="ReadOnly" value="RO" />
	<enum  name="ReadSet" value="ReadSet" />
	<enum  name="ReadWrite" value="RW" />
	<enum  name="WriteOne" value="WriteOne" />
	<enum  name="WriteOnly" value="WO" />
</config>
<config  field_attr="rtl_type" pattern="generic|default_imp|single_line|manual_table|none" type="enum" >
	<enum  name="default_imp" value="default_imp" />
	<enum  name="generic" value="generic" />
	<enum  name="manual_table" value="manual_table" />
	<enum  name="none" value="none" />
	<enum  name="single_line" value="single_line" />
</config>
<config  field_attr="rtl_reset_domain" pattern="hca_reset|tl_reset|pl_reset" type="enum" >
	<enum  name="hca_reset" value="hca" />
	<enum  name="pl_reset" value="pl" />
	<enum  name="tl_reset" value="tl" />
</config>
<config  big_endian_arr="1" />
<config  fname_pattern="[a-zA-Z_]+[a-zA-Z0-9_]*" />
<config  nname_pattern="[a-zA-Z_]+[a-zA-Z0-9_]*" />
<config  sw_export="name,descr,size,default,variables,rtl_path,dv_manual_check,meta_data,access_type,rtl_type" />
<config  disable_exports="hex" />
<config  include_path=".;..;../patch;../verilog;/verification/golan/adabe/CrSpace;../../shared/phy_xdr/adabe;../../shared/mng/adabe;../../shared/glib/adabe;../../shared/serdes_xdr/adabe;../../shared/algorithm/adabe;../../shared/flash/adabe;../../shared/flash/adabe;../../shared/pci/adabe;../../shared/sys_modules/adabe;../../shared/pme/adabe" />
<config  define="RC=0" />
<config  define="UC=1" />
<config  define="UD=3" />
<config  define="XRC=5" />
<config  define="ETHOIB=8" />
<config  define="IPOIB=9" />
<config  define="DCR=11" />
<config  define="DCI=11" />
<config  define="DCT=12" />
<config  define="ETH=14" />
<config  define="IBL2=15" />
<config  define="REGULAR=1" />
<config  define="SRQ=2" />
<config  define="RCYCLIC=3" />
<config  define="STRIDEDWQE=6" />
<config  include_path=".;../;./generals/" />
<config  define="MNOC_MINOR_VER_0=0" />
<config  include_path=".;../../../adabe" />
<config  include_path="../shared/phy_xdr/adabe;../../shared/phy_xdr/adabe" />
<config  include_path="../shared/serdes_xdr/adabe;../../shared/serdes_xdr/adabe" />
<config  include_path="../shared/algorithm/adabe;../../shared/algorithm/adabe" />
<config  include_path="../shared/pme/adabe/;../../shared/pme/adabe/" />
<config  include_path=".;../shared/host_mng/adabe;../../shared/pme/adabe" />
<config  include_path=".;../shared/mng/adabe" />
<config  define="HW_STEERING_ACTION_NOP=0" />
<config  define="HW_STEERING_ACTION_TRANSMIT=1" />
<config  define="HW_STEERING_ACTION_INLINE_QPN=2" />
<config  define="HW_STEERING_ACTION_QP_LIST=3" />
<config  define="HW_STEERING_ACTION_ITERATOR=4" />
<config  define="HW_STEERING_ACTION_COPY=5" />
<config  define="HW_STEERING_ACTION_SET=6" />
<config  define="HW_STEERING_ACTION_ADD=7" />
<config  define="HW_STEERING_ACTION_REMOVE_BY_SIZE=8" />
<config  define="HW_STEERING_ACTION_REMOVE_HEADERS=9" />
<config  define="HW_STEERING_ACTION_INSERT_INLINE=10" />
<config  define="HW_STEERING_ACTION_INSERT_POINTER=11" />
<config  define="HW_STEERING_ACTION_FLOW_TAG=12" />
<config  define="HW_STEERING_ACTION_QUEUE_ID_SEL=13" />
<config  define="HW_STEERING_ACTION_ACCELERATED_LIST=14" />
<config  define="HW_STEERING_ACTION_MODIFY_LIST=15" />
<config  define="HW_STEERING_ACTION_IPSEC_ENCRYPTION=16" />
<config  define="HW_STEERING_ACTION_IPSEC_DECRYPTION=17" />
<config  define="HW_STEERING_ACTION_ASO=18" />
<config  define="HW_STEERING_ACTION_TRAILER=19" />
<config  define="HW_STEERING_ACTION_COUNTER_ID=20" />
<config  define="HW_STEERING_ACTION_TIR=21" />
<config  define="HW_STEERING_ACTION_PORT_SELECTION=22" />
<config  define="HW_STEERING_ACTION_COUNT_ON_SOURCE_GVMI=23" />
<config  define="HW_STEERING_ACTION_TLS=24" />
<config  define="HW_STEERING_ACTION_CLEAR=25" />
<config  define="HW_STEERING_ACTION_MISC=26" />
<config  define="HW_STEERING_ACTION_ADD_FROM_SOURCE=27" />
<config  define="HW_STEERING_ACTION_DOUBLE_NOP=28" />
<config  define="HW_STEERING_ACTION_MACSEC_ENCRYPTION=29" />
<config  define="HW_STEERING_ACTION_MACSEC_DECRYPTION=30" />
<config  define="HW_STEERING_ACTION_PSP_ENCRYPTION=31" />
<config  define="HW_STEERING_ACTION_PSP_DECRYPTION=32" />
<config  define="HW_STEERING_ACTION_PSP_ENCRYPTION_OPTIMIZED=33" />
<config  define="HW_STEERING_ACTION_FUNCTION_CALL=34" />
<config  define="HW_STEERING_ACTION_ASO_32b=35" />
<config  define="HW_STEERING_ACTION_GENERIC_CRYPTO=36" />
<config  define="HW_STEERING_ACTION_ACCMODLIST_32b=37" />
<config  define="HW_STEERING_ACTION_ACTIONLIST_END=38" />
<config  define="HW_STEERING_ACTION_PARSER=39" />
<config  define="HW_STEERING_ACTION_CQE=40" />
<config  define="HW_STEERING_ACTION_TIMESTAMP=41" />
<config  define="HW_STEERING_STE_FORMAT_MATCH_MASK_BWC_BYTES=0" />
<config  define="HW_STEERING_STE_FORMAT_MATCH_MASK_BWC_DWS=1" />
<config  define="HW_STEERING_STE_FORMAT_MATCH_MASK_BYTES=2" />
<config  define="HW_STEERING_STE_FORMAT_MATCH_MASK_DWS=3" />
<config  define="HW_STEERING_STE_FORMAT_MATCH=4" />
<config  define="HW_STEERING_STE_FORMAT_JUMBO_MATCH=5" />
<config  define="HW_STEERING_STE_FORMAT_RX_RSS=6" />
<config  define="HW_STEERING_STE_FORMAT_MATCH_RANGES=7" />
<config  define="HW_STEERING_STE_FORMAT_EXTENDED_MATCH_RANGES=8" />
<config  define="HW_STEERING_STE_FORMAT_COMPRESSED=9" />
<config  define="HW_STEERING_STE_FORMAT_COMPRESSED_ALWAYS_HIT=10" />
<config  define="HW_STEERING_STE_FORMAT_COMPRESSED_DIRECT_NEXT=11" />
<info source_doc_name="" source_doc_version="" />
<node name="link0_cr_link_status"                 size="0x4" descr="================================================================================\;//\;//NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL\;//-----------------------------------------\;//\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL(i)                                               NV_XPL_LINK_CFG_PER_LINK_BASE_ADDR+0x000000030+4*(i)      / * R--4A * /\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL__SIZE_1                                       NV_XPL_CONFIG_NUM_LANES      / *       * /\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL__PRIV_LEVEL_MASK                                          NV_XPL_LINK_CONFIG_PRIV_LEVEL_MASK                                    / *       * /\;//\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET                                               3:0                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET_INIT                                   0x0000000f                  / * R-C-V * /\;//\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_DSP_RX_PRESET_HINT                                               6:4                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_DSP_RX_PRESET_HINT_INIT                                   0x00000007                  / * R-C-V * /\;//\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET                                              10:7                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET_INIT                                   0x0000000f                  / * R-C-V * /\;//\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_USP_RX_PRESET_HINT                                             13:11                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_LANE_EQUALIZATION_CONTROL_USP_RX_PRESET_HINT_INIT                                   0x00000007                  / * R-C-V * /\;//\;//================================================================================\;//\;//NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL\;//-----------------------------------------\;//\;//#define NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL(i)                                               NV_XPL_LINK_CFG_PER_LINK_BASE_ADDR+ 0x000000070+4*(i)      / * R--4A * /\;//#define NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL__SIZE_1                                       NV_XPL_CONFIG_NUM_LANES      / *       * /\;//#define NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL__PRIV_LEVEL_MASK                                          NV_XPL_LINK_CONFIG_PRIV_LEVEL_MASK                                    / *       * /\;//\;//#define NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET                                               3:0                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET_INIT                                   0x0000000f                  / * R-C-V * /\;//\;//#define NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET                                               7:4                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_16GT_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET_INIT                                   0x0000000f                  / * R-C-V * /\;//\;//================================================================================\;//\;//NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL\;//-----------------------------------------\;//\;//#define NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL(i)                                               NV_XPL_LINK_CFG_PER_LINK_BASE_ADDR+ 0x0000000B0+4*(i)       / * R--4A * /\;//#define NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL__SIZE_1                                       NV_XPL_CONFIG_NUM_LANES      / *       * /\;//#define NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL__PRIV_LEVEL_MASK                                          NV_XPL_LINK_CONFIG_PRIV_LEVEL_MASK                                    / *       * /\;//\;//#define NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET                                               3:0                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET_INIT                                   0x0000000f                  / * R-C-V * /\;//\;//#define NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET                                               7:4                  / * R-CVF * /\;//#define NV_XPL_LINK_CR_32GT_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET_INIT                                   0x0000000f                  / * R-C-V * /\;//\;//================================================================================\;//NV_XPL_CR_64GT_LANE_EQUALIZATION_CONTROL\;//-----------------------------------------\;//\;//#define NV_XPL_LINK_CR_64GT_LANE_EQUALIZATION_CONTROL(i)                                            NV_XPL_LINK_CFG_PER_LINK_BASE_ADDR + 0xF0+4*(i)      / * R--4A * /\;//#define NV_XPL_LINK_CR_64GT_LANE_EQUALIZATION_CONTROL__SIZE_1                                       NV_XPL_CONFIG_NUM_LANES      / *       * /\;//#define NV_XPL_LINK_CR_64GT_LANE_EQUALIZATION_CONTROL__PRIV_LEVEL_MASK                                          NV_XPL_LINK_CONFIG_PRIV_LEVEL_MASK                                    / *       * /\;//\;//#define NV_XPL_LINK_CR_64GT_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET                                               3:0                 / * R-CVF * /\;//#define NV_XPL_LINK_CR_64GT_LANE_EQUALIZATION_CONTROL_DSP_TX_PRESET_INIT                                   0x0000000f                 / * R-C-V * /\;//\;//#define NV_XPL_LINK_CR_64GT_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET                                              10:7                 / * R-CVF * /\;//#define NV_XPL_LINK_CR_64GT_LANE_EQUALIZATION_CONTROL_USP_TX_PRESET_INIT                                   0x0000000f                 / * R-C-V * /\;//\;================================================================================\;\;NV_XPL_LINK_CR_LINK_STATUS\;-----------------------------------------\;CURRENT_LINK_SPEED:\;-----------------------------------------\;This field indicates the negotiated Link speed of the given PCI Express Link.\;The encoding is the binary value of the bit location in the Supported Link Speeds Vector\;(in the Link Capabilities 2 register) that corresponds to the current Link speed.\;0001b = 2.5 Gb/s PCI Express Link\;0010b = 5.0 Gb/s PCI Express Link\;0011b = 8.0 Gb/s PCI Express Link\;The value in this field is undefined when the Link is not up.\;\;RO override for this field is not verified in functional tests\;\;NEGOTIATED_LINK_WIDTH:\;-----------------------------------------\;This field indicates the negotiated width of the given PCI Express\;Link. Defined encodings are:\;\;.---------------------.\;| 000001b | x1        |\;`---------------------&amp;apos;\;| 000010b | x2        |\;`---------------------&amp;apos;\;| 000100b | x4        |\;`---------------------&amp;apos;\;| 001000b | x8        |\;`---------------------&amp;apos;\;| 001100b | x12       |\;`---------------------&amp;apos;\;| 010000b | x16       |\;`---------------------&amp;apos;\;| 100000b | x32       |\;`---------------------&amp;apos;\;\;RO override for this field is not verified in functional tests\;\;UNDEFINED:\;-----------------------------------------\;This field indicates the negotiated width of the given PCI Express\;Link. Defined encodings are:\;\;.---------------------.\;| 000001b | x1        |\;`---------------------&amp;apos;\;| 000010b | x2        |\;`---------------------&amp;apos;\;| 000100b | x4        |\;`---------------------&amp;apos;\;| 001000b | x8        |\;`---------------------&amp;apos;\;| 001100b | x12       |\;`---------------------&amp;apos;\;| 010000b | x16       |\;`---------------------&amp;apos;\;| 100000b | x32       |\;`---------------------&amp;apos;\;\;RO override for this field is not verified in functional tests\;\;LINK_TRAINING:\;-----------------------------------------\;This read-only bit indicates that the Physical Layer LTSSM is\;in the Configuration or Recovery state, or that 1b was written to the Retrain\;Link bit but Link training has not yet begun. Hardware clears this bit when\;the LTSSM exits the Configuration/Recovery state.\;This bit is not applicable and Reserved for Endpoints, PCI Express to PCI/\;PCI-X bridges, and Upstream Ports of Switches, and must be hardwired to\;0b.\;\;RO override for this field is not verified in functional tests\;\;LINK_BANDWIDTH_MGT_STATUS\;-----------------------------------------\;This bit is Set by hardware to indicate that either of the following\;has occurred without the Port transitioning through DL_Down status:\;  A Link retraining has completed following a write of 1b to the Retrain Link bit.\;Note: This bit is Set following any write of 1b to the Retrain Link bit, including when the Link is\;in the process of retraining for some other reason.\;  Hardware has changed Link speed or width to attempt to correct unreliable Link operation,\;either through an LTSSM timeout or a higher level process.\;\;This bit must be set if the Physical Layer reports a speed or width change was initiated by the\;Downstream component that was not indicated as an autonomous change.\;This bit is not applicable and is Reserved for Endpoints, PCI Express-to-PCI/PCI-X bridges, and Upstream\;Ports of Switches.\;Functions that do not implement the Link Bandwidth Notification Capability must hardwire this bit to 0b.\;\;AUTO_LINK_BANDWIDTH_MGT_STATUS\;-----------------------------------------\;This bit is Set by hardware to indicate that hardware has\;autonomously changed Link speed or width, without the Port transitioning through DL_Down status, for\;reasons other than to attempt to correct unreliable Link operation.\;This bit must be set if the Physical Layer reports a speed or width change was initiated by the\;Downstream component that was indicated as an autonomous change.\;This bit is not applicable and is Reserved for Endpoints, PCI Express-to-PCI/PCI-X bridges, and Upstream\;Ports of Switches.\;Functions that do not implement the Link Bandwidth Notification Capability must hardwire this bit to 0b.\;\;\;SLOT_CLOCK_CONFIGURATION:\;-----------------------------------------\;This bit indicates that the component uses the\;same physical reference clock that the platform provides on the connector.\;If the device uses an independent clock irrespective of the presence of a\;reference clock on the connector, this bit must be clear.\;For a Multi-Function Device, each Function must report the same value for\;this bit.\;\;RO override for this field is not verified in functional tests\;\;DATA_LINK_LAYER_LINK_ACTIVE\;-----------------------------------------\;This bit indicates the status of the Data Link Control and Management\;State Machine. It returns a 1b to indicate the DL_Active state, 0b otherwise.\;This bit must be implemented if the Data Link Layer Link Active Reporting Capable bit is 1b.\;Otherwise, this bit must be hardwired to 0b." >
	<field name="current_link_speed"              offset="0x0.0"    size="0x0.4" access_type="RO" default="0x1" enum="GEN1=1, GEN2=2, GEN3=3, GEN4=4, GEN5=5, GEN6=6" rtl_name="link0_cr_link_status_current_link_speed" rtl_path="link0_cr_link_status_current_link_speed" descr="" />
	<field name="negotiated_link_width"           offset="0x0.4"    size="0x0.6" access_type="RO" default="0x1" enum="X1=0x1, X2=0x2, X4=0x4, X8=0x8, X16=0x10, X32=0x20" rtl_name="link0_cr_link_status_negotiated_link_width" rtl_path="link0_cr_link_status_negotiated_link_width" descr="" />
	<field name="link_training"                   offset="0x0.10"   size="0x0.1" access_type="RO" default="0x0" rtl_name="link0_cr_link_status_link_training" rtl_path="link0_cr_link_status_link_training" descr="" />
	<field name="link_bandwidth_mgt_status"       offset="0x0.11"   size="0x0.1" default="0x0" enum="NO_PENDING=0, RESET=1, PENDING=1" rtl_name="link0_cr_link_status_link_bandwidth_mgt_status" rtl_path="link0_cr_link_status_link_bandwidth_mgt_status" descr="" />
	<field name="auto_link_bandwidth_mgt_status"  offset="0x0.12"   size="0x0.1" default="0x0" enum="NO_PENDING=0, RESET=1, PENDING=1" rtl_name="link0_cr_link_status_auto_link_bandwidth_mgt_status" rtl_path="link0_cr_link_status_auto_link_bandwidth_mgt_status" descr="" />
	<field name="slot_clock_configuration"        offset="0x0.13"   size="0x0.1" access_type="RO" default="0x0" rtl_name="link0_cr_link_status_slot_clock_configuration" rtl_path="link0_cr_link_status_slot_clock_configuration" descr="" />
	<field name="data_link_layer_link_active"     offset="0x0.14"   size="0x0.1" access_type="RO" default="0x0" rtl_name="link0_cr_link_status_data_link_layer_link_active" rtl_path="link0_cr_link_status_data_link_layer_link_active" descr="" />
</node>

<node name="link0_dl_ltssm_dfd_logger_ctrl2"      size="0x4" descr="================================================================================\;NV_XPL_LINK_DL_LTSSM_DFD_LOGGER_CTRL2\;-------------------\;NV_XPL_LINK_DL_LTSSM_DFD_LOGGER_CTRL2_CURRENT_INDEX\;------------------\;Current index of the logger\;\;NV_XPL_LINK_DL_LTSSM_DFD_LOGGER_CTRL2_CURRENT_LOGGED_SIZE\;------------------\;Size of the logger." >
	<field name="current_index"                   offset="0x0.0"    size="0x0.7" rtl_name="link0_dl_ltssm_dfd_logger_ctrl2_current_index" descr="" />
	<field name="current_logged_size"             offset="0x0.16"   size="0x0.8" access_type="RO" rtl_name="link0_dl_ltssm_dfd_logger_ctrl2_current_logged_size" descr="" />
</node>

<node name="link0_dl_ltssm_dfd_logger_line"       size="0x4" descr="================================================================================\;\;\;//NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST\;//------------------------------\;//Injects Correctable and uncorrectable error in data being written to DL RX RAM&amp;apos;s.\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST                                   NV_XPL_LINK_DL_RAM_ECC_BASE_ADDR + 0x0      / * RW-4R * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST__PRIV_LEVEL_MASK                   NV_XPL_LINK_DL_LINK_DEBUG_PRIV_LEVEL_MASK  / *       * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_CORRECTED_ERR_RBUF_FIFO                                           0:0  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_CORRECTED_ERR_RBUF_FIFO_INIT                               0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_CORRECTED_ERR_RBUF_FIFO_BUSY                               0x00000001  / * R---V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_CORRECTED_ERR_RBUF_FIFO_DONE                               0x00000000  / * R---V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_CORRECTED_ERR_RBUF_FIFO_START                              0x00000001  / * -W--V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_CORRECTED_ERR_RBUF_FIFO_CLEAR                              0x00000000  / * -W--V * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_UNCORRECTED_ERR_RBUF_FIFO                                         1:1  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_UNCORRECTED_ERR_RBUF_FIFO_INIT                             0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_UNCORRECTED_ERR_RBUF_FIFO_BUSY                             0x00000001  / * R---V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_UNCORRECTED_ERR_RBUF_FIFO_DONE                             0x00000000  / * R---V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_UNCORRECTED_ERR_RBUF_FIFO_START                            0x00000001  / * -W--V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_TEST_INJECT_UNCORRECTED_ERR_RBUF_FIFO_CLEAR                            0x00000000  / * -W--V * /\;//\;//\;//\;//NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS\;//------------------------------\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS                                 NV_XPL_LINK_DL_RAM_ECC_BASE_ADDR + 0x4      / * RW-4R * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS__PRIV_LEVEL_MASK                NV_XPL_LINK_DL_LINK_STATUS_PRIV_LEVEL_MASK  / *       * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR                                                          0:0  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_INIT                                              0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_CLEAR                                             0x00000001  / * -W--V * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR                                                        1:1  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_INIT                                            0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_CLEAR                                           0x00000001  / * -W--V * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_TOTAL_COUNTER_OVERFLOW                                   2:2  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_TOTAL_COUNTER_OVERFLOW_INIT                       0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_TOTAL_COUNTER_OVERFLOW_CLEAR                      0x00000001  / * -W--V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_UNIQUE_COUNTER_OVERFLOW                                  3:3  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_UNIQUE_COUNTER_OVERFLOW_INIT                      0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_CORRECTED_ERR_UNIQUE_COUNTER_OVERFLOW_CLEAR                     0x00000001  / * -W--V * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_TOTAL_COUNTER_OVERFLOW                                 4:4  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_TOTAL_COUNTER_OVERFLOW_INIT                     0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_TOTAL_COUNTER_OVERFLOW_CLEAR                    0x00000001  / * -W--V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_UNIQUE_COUNTER_OVERFLOW                                5:5  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_UNIQUE_COUNTER_OVERFLOW_INIT                    0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_UNCORRECTED_ERR_UNIQUE_COUNTER_OVERFLOW_CLEAR                   0x00000001  / * -W--V * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_RESET                                                                  6:6  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_RESET_INIT                                                      0x00000000  / * RWC-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_RESET_DONE                                                      0x00000000  / * R---V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_STATUS_RESET_PENDING                                                   0x00000001  / * -W--T * /\;//\;//  \;//\;//\;//NV_XPL_LINK_DL_RX_RAM_1_ECC_ADDRESS\;//------------------------------\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_ADDRESS                                 NV_XPL_LINK_DL_RAM_ECC_BASE_ADDR + 0x8      / * R--4R * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_ADDRESS__PRIV_LEVEL_MASK                NV_XPL_LINK_DL_LINK_STATUS_PRIV_LEVEL_MASK  / *       * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_ADDRESS_VALUE                                                                  0:0  / * R-CVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_ADDRESS_VALUE_INIT                                                      0x00000000  / * R-C-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_ADDRESS_VALUE_RBUF_FIFO                                                 0x00000001  / * R---V * /\;//\;//\;//\;//\;//NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT\;//------------------------------\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT                                 NV_XPL_LINK_DL_RAM_ECC_BASE_ADDR + 0xC      / * RW-4R * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT__PRIV_LEVEL_MASK                NV_XPL_LINK_DL_LINK_STATUS_PRIV_LEVEL_MASK  / *       * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT_TOTAL                                                                 15:0  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT_TOTAL_INIT                                                      0x00000000  / * R-C-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT_TOTAL_CLEAR                                                     0x00000001  / * -W--V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT_UNIQUE                                                               31:16  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT_UNIQUE_INIT                                                     0x00000000  / * R-C-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_CORRECTED_ERR_COUNT_UNIQUE_CLEAR                                                    0x00000001  / * -W--V * /\;//\;//\;//\;//\;//NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT\;//------------------------------\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT                               NV_XPL_LINK_DL_RAM_ECC_BASE_ADDR + 0x10     / * RW-4R * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT__PRIV_LEVEL_MASK              NV_XPL_LINK_DL_LINK_STATUS_PRIV_LEVEL_MASK  / *       * /\;//\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT_TOTAL                                                               15:0  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT_TOTAL_INIT                                                    0x00000000  / * R-C-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT_TOTAL_CLEAR                                                   0x00000001  / * -W--V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT_UNIQUE                                                             31:16  / * RWCVF * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT_UNIQUE_INIT                                                   0x00000000  / * R-C-V * /\;//#define NV_XPL_LINK_DL_RX_RAM_1_ECC_UNCORRECTED_ERR_COUNT_UNIQUE_CLEAR                                                  0x00000001  / * -W--V * /\;\;\;\;\;\;================================================================================\;    SECTION 3.10 : NV_XPL_LINK_DL_DFD                         \;================================================================================\;NV_XPL_LINK_DL_LTSSM_DFD_LOGGER_LINE\;---------------------------------\;LTSSM is locarted under DL because there are no RAMS in PL\;\;\;STATE:\;-----------------\;Current LTSSM state \;\;REASON:\;-----------------\;Reason for state change\;\;SPEED:\;-----------------\;Current link speed\;\;WIDTH:\;-----------------\;Current link width\;\;TIME:\;-----------------\;Timestamp for transition" >
	<field name="state"                           offset="0x0.0"    size="0x0.8" rtl_name="link0_dl_ltssm_dfd_logger_line_state$(IDX)" descr="" />
	<field name="reason"                          offset="0x0.8"    size="0x0.3" rtl_name="link0_dl_ltssm_dfd_logger_line_reason$(IDX)" descr="" />
	<field name="speed"                           offset="0x0.11"   size="0x0.3" rtl_name="link0_dl_ltssm_dfd_logger_line_speed$(IDX)" descr="" />
	<field name="width"                           offset="0x0.14"   size="0x0.3" rtl_name="link0_dl_ltssm_dfd_logger_line_width$(IDX)" descr="" />
	<field name="time"                            offset="0x0.17"   size="0x0.15" rtl_name="link0_dl_ltssm_dfd_logger_line_time$(IDX)" descr="" />
</node>

<node name="link0_pl_ltssm_state"                 size="0x4" descr="=============================================================================================================================\;\;================================================================================\;SECTION 1.8 : NV_XPL_LINK_PL_LTSSM - DEBUG          \;================================================================================\;\;NV_XPL_LINK_PL_LTSSM_STATE\;-------------------\;This register reflects the current LTSSM state as well as specific\;status for some important states to be used by GC6.\;\;LTSSM_STATE_FULL\;----------------\;Reports the 8 bit binary encoded LTSSM state. See\;vmod/xp3g/pl/ltssm/__PROJ__XPL_PL_ltssm.vh for more details about the\;encoding\;\;LTSSM_STATE_IS_L0\;-----------------\;Indicates that the current LTSSM state is L0 \;//XPL_PM : and neither tx nor rx are in any L0s state.\;\;LTSSM_STATE_IS_L1\;-----------------\;Indicates that the current LTSSM state is L1.idle\;\;LTSSM_STATE_IS_L2\;-----------------\;Indicates that the current LTSSM state is L2.idle\;\;LTSSM_STATE_IS_L1_PLL_PD\;----------------------\;Indicates that the current LTSSM state is L1.idle and UPHY PLL is powered down.\;\;//XPL_PM : NV_XPL_LINK_LTSSM_STATE_IS_TX_L0S\;//XPL_PM : -----------------------------\;//XPL_PM : Indicates that the current LTSSM state is L0s on the Tx\;\;//XPL_PM : NV_XPL_LINK_LTSSM_STATE_IS_RX_L0S\;//XPL_PM : ------------------------------\;//XPL_PM : Indicates that the current LTSSM state is L0s on the Rx\;\;NV_XPL_LINK_LTSSM_STATE_IS_DETECT\;------------------------------\;Indicates that the current LTSSM state is Detect.Quiet or Detect.Active.\;\;NV_XPL_LINK_LTSSM_STATE_IS_POLLING_COMPLIANCE\;-----------------------------------------\;Indicates that the current LTSSM state is Polling.Compliance\;\;NV_XPL_LINK_LTSSM_STATE_IS_RECOVERY_EQZN\;------------------------------------\;Indicates that the current LTSSM state is Recovery.Equalization\;\;NV_XPL_LINK_LTSSM_STATE_IS_LINK_DOWN\;--------------------------------\;Indicates that the link is down\;\;NV_XPL_LINK_LTSSM_STATE_IS_LINK_READY\;---------------------------------\;Indicates that the link is ready to transmit upper layer data\;\;NV_XPL_LINK_LTSSM_STATE_IS_DISABLED\;---------------------------------\;Indicates that the current LTSSM state is Disabled.\;\;NV_XPL_LINK_LTSSM_STATE_LANES_IN_SLEEP                             \;----------------------------------\;Indicates that all the lanes are in sleep" >
	<field name="full"                            offset="0x0.0"    size="0x0.8" access_type="RO" default="0x0" rtl_name="link0_pl_ltssm_state_full" rtl_path="link0_pl_ltssm_state_full" descr="" />
	<field name="is_l0"                           offset="0x0.8"    size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_l0" rtl_path="link0_pl_ltssm_state_is_l0" descr="" />
	<field name="is_l1"                           offset="0x0.9"    size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_l1" rtl_path="link0_pl_ltssm_state_is_l1" descr="" />
	<field name="is_l2"                           offset="0x0.10"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_l2" rtl_path="link0_pl_ltssm_state_is_l2" descr="" />
	<field name="is_l1_pll_pd"                    offset="0x0.11"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_l1_pll_pd" rtl_path="link0_pl_ltssm_state_is_l1_pll_pd" descr="" />
	<field name="is_detect"                       offset="0x0.14"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_detect" rtl_path="link0_pl_ltssm_state_is_detect" descr="XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_TX_L0S                                  12:12  / * R-CVF * /\;//XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_TX_L0S_INIT                        0x00000000  / * R-C-V * /\;//XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_TX_L0S_FALSE                       0x00000000  / * R---V * /\;//XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_TX_L0S_TRUE                        0x00000001  / * R---V * /\;\;//XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_RX_L0S                                  13:13  / * R-CVF * /\;//XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_RX_L0S_INIT                        0x00000000  / * R-C-V * /\;//XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_RX_L0S_FALSE                       0x00000000  / * R---V * /\;//XPL_PM : #define NV_XPL_LINK_PL_LTSSM_STATE_IS_RX_L0S_TRUE                        0x00000001  / * R---V * /" />
	<field name="is_polling_compliance"           offset="0x0.15"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_polling_compliance" rtl_path="link0_pl_ltssm_state_is_polling_compliance" descr="" />
	<field name="is_recovery_eqzn"                offset="0x0.16"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_recovery_eqzn" rtl_path="link0_pl_ltssm_state_is_recovery_eqzn" descr="" />
	<field name="is_link_down"                    offset="0x0.17"   size="0x0.1" access_type="RO" default="0x1" enum="FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_link_down" rtl_path="link0_pl_ltssm_state_is_link_down" descr="" />
	<field name="is_link_ready"                   offset="0x0.18"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_link_ready" rtl_path="link0_pl_ltssm_state_is_link_ready" descr="" />
	<field name="is_disabled"                     offset="0x0.19"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_disabled" rtl_path="link0_pl_ltssm_state_is_disabled" descr="" />
	<field name="is_l1_cpm"                       offset="0x0.20"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_l1_cpm" rtl_path="link0_pl_ltssm_state_is_l1_cpm" descr="" />
	<field name="is_l1_1"                         offset="0x0.21"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_l1_1" rtl_path="link0_pl_ltssm_state_is_l1_1" descr="" />
	<field name="is_l1_2"                         offset="0x0.22"   size="0x0.1" access_type="RO" default="0x0" enum="INIT=0, FALSE=0, TRUE=1" rtl_name="link0_pl_ltssm_state_is_l1_2" rtl_path="link0_pl_ltssm_state_is_l1_2" descr="" />
	<field name="lanes_in_sleep"                  offset="0x0.31"   size="0x0.1" access_type="RO" default="0x1" enum="FALSE=0, INIT=1, TRUE=1" rtl_name="link0_pl_ltssm_state_lanes_in_sleep" rtl_path="link0_pl_ltssm_state_lanes_in_sleep" descr="" />
</node>

<node name="ltssm_Nodes"                          size="0x480000.0" descr="" >
	<field name="pcore_top_pcore_pxdp_xpl_top"    offset="0x300000.0" size="0x180000.0" subnode="pcore_top_pcore_pxdp_xpl_top_node" high_bound="2" low_bound="0" descr="" />
</node>

<node name="pcore_top_pcore_pxdp_xpl_top_node"    size="0x80000.0" descr="" >
	<field name="xpl_nv_xpl"                      offset="0x40000.0" size="0x20000.0" subnode="pcore_top_pcore_pxdp_xpl_top_xpl_nv_xpl_node" high_bound="7" low_bound="0" descr="" />
</node>

<node name="pcore_top_pcore_pxdp_xpl_top_xpl_nv_xpl_node" size="0x4000.0" descr="" >
	<field name="link0_cr_link_status"            offset="0x2b78.0" size="0x4.0" subnode="link0_cr_link_status" descr="" />
	<field name="link0_pl_ltssm_state"            offset="0x3200.0" size="0x4.0" subnode="link0_pl_ltssm_state" descr="" />
	<field name="link0_dl_ltssm_dfd_logger_line"  offset="0x3500.0" size="0x200.0" subnode="link0_dl_ltssm_dfd_logger_line" high_bound="127" low_bound="0" descr="" />
	<field name="link0_dl_ltssm_dfd_logger_ctrl2" offset="0x370c.0" size="0x4.0" subnode="link0_dl_ltssm_dfd_logger_ctrl2" descr="" />
</node>

<node name="root"                                 size="0x480000.0" descr="" >
	<field name="ltssm_Nodes"                     offset="0x0.0"    size="0x480000.0" subnode="ltssm_Nodes" descr="" />
</node>

</NodesDefinition>
