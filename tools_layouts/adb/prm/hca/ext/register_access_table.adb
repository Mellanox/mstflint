<NodesDefinition>
<config  field_mand="name, descr, size" />
<config  field_attr="name" type="ascii" />
<config  field_attr="descr" type="ascii" />
<config  field_attr="size" type="hexa" />
<config  field_attr="type" type="ascii" />
<config  field_attr="rw" type="enum" >
	<enum  name="OP" value="OP" />
	<enum  name="ReadOnly" value="RO" />
	<enum  name="ReadWrite" value="RW" />
	<enum  name="WriteOnly" value="WO" />
</config>
<config  field_attr="access" type="enum" >
	<enum  name="Index" value="INDEX" />
	<enum  name="OP" value="OP" />
	<enum  name="ReadOnly" value="RO" />
	<enum  name="ReadWrite" value="RW" />
	<enum  name="WriteOnly" value="WO" />
</config>
<config  field_attr="enum" type="enumval" />
<config  big_endian_arr="1" />
<config  field_attr="selected_by" type="ascii" used_for="node" />
<config  field_attr="union_selector" type="ascii" used_for="node" />
<config  field_attr="mlxconfig_desc" type="ascii" />
<config  field_attr="mlxconfig_name" type="ascii" />
<config  field_attr="xuefi" type="ascii" />
<config  field_attr="supported_from_version" type="ascii" />
<config  field_attr="dependency" type="ascii" />
<config  field_attr="valid_bit" type="ascii" />
<config  field_attr="tempvars" type="ascii" />
<config  field_attr="minval" type="ascii" />
<config  field_attr="maxval" type="ascii" />
<config  field_attr="rule" type="ascii" />
<config  field_attr="regex" type="ascii" />
<config  field_attr="capability" type="ascii" />
<config  field_attr="target" type="ascii" />
<config  field_attr="version" type="ascii" />
<info source_doc_name="" source_doc_version="" />
<node name="IB_long_portcntrs_attribute_grp_data_ext" descr="" size="0xf8.0" >
	<field name="symbol_error_counter_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="symbol_error_counter_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="link_error_recovery_counter_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="link_error_recovery_counter_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="link_downed_counter_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="link_downed_counter_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="port_rcv_errors_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="port_rcv_errors_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="port_rcv_remote_physical_errors_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_rcv_remote_physical_errors_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="port_rcv_switch_relay_errors_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="port_rcv_switch_relay_errors_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="port_xmit_discards_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="port_xmit_discards_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="port_xmit_constraint_errors_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="port_xmit_constraint_errors_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="port_rcv_constraint_errors_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="port_rcv_constraint_errors_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="local_link_integrity_errors_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="local_link_integrity_errors_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="excessive_buffer_overrun_errors_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="excessive_buffer_overrun_errors_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="vl_15_dropped_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="vl_15_dropped_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="port_xmit_data_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="port_xmit_data_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="port_rcv_data_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="port_rcv_data_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="port_xmit_pkts_high" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="port_xmit_pkts_low" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="port_rcv_pkts_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="port_rcv_pkts_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="port_xmit_wait_high" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="port_xmit_wait_low" descr="For counter description please refer to the InfiniBand \;specification\;" access="RO" offset="0x84.0" size="0x4.0" />
</node>

<node name="IB_portcntrs_attribute_grp_data_ext" descr="" size="0xf8.0" >
	<field name="link_downed_counter" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="link_error_recovery_counter" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="symbol_error_counter" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="port_rcv_remote_physical_errors" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="port_rcv_errors" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="port_xmit_discards" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="port_rcv_switch_relay_errors" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="excessive_buffer_overrun_errors" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0xC.0" size="0x0.4" />
	<field name="local_link_integrity_errors" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0xC.4" size="0x0.4" />
	<field name="port_rcv_constraint_errors" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="port_xmit_constraint_errors" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="vl_15_dropped" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="port_xmit_data" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="port_rcv_data" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="port_xmit_pkts" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="port_rcv_pkts" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_xmit_wait" descr="For counter description please refer to the InfiniBand \;specification" access="RO" offset="0x24.0" size="0x4.0" />
</node>

<node name="access_reg_summary_ctrl_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="id" descr="" subnode="enum_entry" enum="UNIT_PERF_COUNTERS_=0x100,MISC_COUNTERS=0x104,Loopback_Control_Register=0x700,DB_TRESHOLD=0x701,DCBX_PARAM=0x4020,DCBX_APPLICATION=0x4021,QPTS=0x4002,QETCR=0x4005,QSHR=0x4030,QPDP=0x4007,QPRT=0x4008,QTCT=0x400a,QSPIP=0x400e,QSPCP=0x401e,QHLL=0x4016,QCAM=0x4019,ROCE_ACCL=0x402c,PCAM=0x507f,PCAP=0x5001,PTYS=0x5004,PAOS=0x5006,PLTC=0x5046,PPCNT=0x5008,PGMR=0x5039,PTER=0x5055,PREI=0x5058,PGUID=0x5066,PPCC=0x506e,PMLP=0x5002,PMAOS=0x5012,PMMP=0x5044,PMCR=0x5045,PMPT=0x5064,PMPD=0x5065,PPLR=0x5018,PPLM=0x5023,SLTP=0x5027,SLRG=0x5028,PDDR=0x5031,PPTT=0x5036,PPRT=0x5037,PPHCR=0x503e,PPAOS=0x5040,SLRED=0x505a,PMTU=0x5003,PPAD=0x5005,PFCC=0x5007,PPTB=0x500b,PBMC=0x500c,PVLC=0x500f,PBSR=0x5038,PCMR=0x5041,PVLS=0x504b,SET_NODE=0x6001,POWER_SETTINGS=0x7001,FP_SL_MAP=0x7002,HOST_ENDIANNESS=0x7004,MFCR=0x9001,MFSC=0x9002,MFSM=0x9003,MFSL=0x9004,FORE=0x9007,MFNR=0x903b,MTCAP=0x9009,MTECR=0x9109,MTMP=0x900a,MTWE=0x900b,MTEWE=0x910b,MVCAP=0x902e,MVCR=0x900c,MSPS=0x900d,MCPP=0x900e,MTBR=0x900f,MFPA=0x9010,MFBA=0x9011,MFBE=0x9012,MFMC=0x9013,MCIA=0x9014,MCION=0x9052,MMIA=0x9016,MMDIO=0x2339,MPGR=0x9019,MFM=0x901d,MHSR=0x901e,MJTAG=0x901f,MSGI=0x9021,MSCI=0x902a,MPCIR=0x905a,MRTC=0x902d,MGIR=0x9020,MGPIR=0x9100,MDIR=0x911a,MSSIR=0x9105,MHMPR=0x905d,MPFM=0x9022,MRSR=0x9023,MPGO=0x9058,MNVDA=0x9024,MNVDI=0x9025,MNVQC=0x9030,MNVIA=0x9033,MNVGC=0x9034,MNVGN=0x9035,MGNLE=0x9036,MTRC_CAP=0x9040,MTRC_CONF=0x9041,MTRC_STDB=0x9042,MTRC_CTRL=0x9043,MLCR=0x902b,MGCR=0x903a,MERR=0x903c,MPEIN=0x9050,MPCNT=0x9051,MTPPS=0x9053,MTPTP=0x9153,MTUTC=0x9055,MPIR=0x9059,MPECS=0x905b,MCQS=0x9060,MCQI=0x9061,MCC=0x9062,MCDA=0x9063,MTCQ=0x9065,MKDC=0x9066,MBCT=0x9120,MQIS=0x9064,MIRC=0x9162,MCDD=0x905c,MDFCR=0x9101,MDCR=0x9111,MDDT=0x9160,MDDQ=0x9161,MDDC=0x9163,MDRCR=0x9102,MDSR=0x9110,MFSV=0x9115,MQDIK=0x9116,MRPR=0x9117,MCAM=0x907f,MFRL=0x9028,MMHI=0x904a,CWGCR=0x2801,CWTP=0x2802,CWPP=0x2804,CWTPM=0x2803,CPQE=0x2806,CHLTR=0x2810,CHLTM=0x2811,CHLMM=0x2812,CNCT=0x2030,CPCS=0x2031,CPID=0x2032,CNMC=0x2033,CWCAM=0x281f,SBGCR=0xb000,SBPR=0xb001,SBCM=0xb002,SBPM=0xb003,SBMM=0xb004,SBME=0xb00e,SBSR=0xb005,SBIB=0xb006,SBDCC=0xb007,SBDCM=0xb008,SBDCR=0xb019,SBHBR=0xb00a,SBHRR=0xb00b,SBHBR_V2=0xb011,SBHRR_V2=0xb012,SBCTC=0xb00c,SBCTR=0xb00d,SBCTS=0xb00f,SBHPC=0xb013,SBSNT=0xb020,SBSNS=0xb021,SBSNTE=0xb022,SBCAM=0xb01f,NCFG=0xc001,CRYPTO_OPERATIONAL=0xc002,IMPORT_KEK_HANDLE=0xc004,CREDENTIAL_HANDLE=0xc005,ZTT=0xc006,VHCA_TRUST_LEVEL=0xc007,PORT_STATE_BEHAVIOR=0xc008,HCA_CMD_ENCAP=0xc009,NVMF_TARGET_PACER_DEFAULTS=0xc00a" offset="0x0.0" size="0x4.0" />
</node>

<node name="access_reg_summary_ext" descr="" attr_is_union="1" size="0x420" >
	<field name="register_unti_perf_global_ctrl" descr="" subnode="register_unti_perf_global_ctrl_ext" capability="0" offset="0x0.0" selected_by="UNIT_PERF_COUNTERS_" size="0x10" />
	<field name="register_misc_counters" descr="" subnode="register_misc_counters_ext" capability="0" offset="0x0.0" selected_by="MISC_COUNTERS" size="0x20" />
	<field name="register_loopback_control" descr="" subnode="register_loopback_control_ext" capability="0" offset="0x0.0" selected_by="Loopback_Control_Register" size="0x10" />
	<field name="db_threshold_register_layout" descr="" subnode="db_threshold_register_layout_ext" capability="0" offset="0x0.0" selected_by="DB_TRESHOLD" size="0x10" />
	<field name="dcbx_param_reg" descr="" subnode="dcbx_param_reg_ext" capability="0" offset="0x0.0" selected_by="DCBX_PARAM" size="0x40" />
	<field name="dcbx_app_reg" descr="" subnode="dcbx_app_reg_ext" capability="0" offset="0x0.0" selected_by="DCBX_APPLICATION" size="0x14" />
	<field name="qpts" descr="" subnode="qpts_ext" capability="0" offset="0x0.0" selected_by="QPTS" size="0x8" />
	<field name="qetcr" descr="" subnode="qetcr_ext" capability="0" offset="0x0.0" selected_by="QETCR" size="0x50" />
	<field name="qshr" descr="" subnode="qshr_ext" capability="0" offset="0x0.0" selected_by="QSHR" size="0x50" />
	<field name="qpdp" descr="" subnode="qpdp_ext" capability="0" offset="0x0.0" selected_by="QPDP" size="0x8" />
	<field name="qprt" descr="" subnode="qprt_ext" capability="0" offset="0x0.0" selected_by="QPRT" size="0x8" />
	<field name="qtct" descr="" subnode="qtct_ext" capability="0" offset="0x0.0" selected_by="QTCT" size="0x8" />
	<field name="qspip" descr="" subnode="qspip_ext" capability="0" offset="0x0.0" selected_by="QSPIP" size="0x8" />
	<field name="qspcp" descr="" subnode="qspcp_ext" capability="0" offset="0x0.0" selected_by="QSPCP" size="0xc" />
	<field name="qhll" descr="" subnode="qhll_ext" capability="0" offset="0x0.0" selected_by="QHLL" size="0xc" />
	<field name="qcam" descr="" subnode="qcam_ext" capability="0" offset="0x0.0" selected_by="QCAM" size="0x48" />
	<field name="roce_accl_reg" descr="" subnode="roce_accl_reg_ext" capability="0" offset="0x0.0" selected_by="ROCE_ACCL" size="0x40" />
	<field name="pcam_reg" descr="" subnode="pcam_reg_ext" capability="0" offset="0x0.0" selected_by="PCAM" size="0x50" />
	<field name="pcap_reg" descr="" subnode="pcap_reg_ext" capability="0" offset="0x0.0" selected_by="PCAP" size="0x14" />
	<field name="ptys_reg" descr="" subnode="ptys_reg_ext" capability="0" offset="0x0.0" selected_by="PTYS" size="0x40" />
	<field name="paos_reg" descr="" subnode="paos_reg_ext" capability="0" offset="0x0.0" selected_by="PAOS" size="0x10" />
	<field name="pltc_reg" descr="" subnode="pltc_reg_ext" capability="0" offset="0x0.0" selected_by="PLTC" size="0x10" />
	<field name="ppcnt_reg" descr="" subnode="ppcnt_reg_ext" capability="0" offset="0x0.0" selected_by="PPCNT" size="0x100" />
	<field name="pgmr" descr="" subnode="pgmr_ext" capability="0" offset="0x0.0" selected_by="PGMR" size="0x18" />
	<field name="pter_reg" descr="" subnode="pter_reg_ext" capability="0" offset="0x0.0" selected_by="PTER" size="0x20" />
	<field name="prei_reg" descr="" subnode="prei_reg_ext" capability="0" offset="0x0.0" selected_by="PREI" size="0x18" />
	<field name="pguid_reg" descr="" subnode="pguid_reg_ext" capability="0" offset="0x0.0" selected_by="PGUID" size="0x60" />
	<field name="ppcc_reg" descr="" subnode="ppcc_reg_ext" capability="0" offset="0x0.0" selected_by="PPCC" size="0xfc" />
	<field name="pmlp_reg" descr="" subnode="pmlp_reg_ext" capability="0" offset="0x0.0" selected_by="PMLP" size="0x40" />
	<field name="pmaos_reg" descr="" subnode="pmaos_reg_ext" capability="0" offset="0x0.0" selected_by="PMAOS" size="0x10" />
	<field name="pmmp_reg" descr="" subnode="pmmp_reg_ext" capability="0" offset="0x0.0" selected_by="PMMP" size="0x28" />
	<field name="pmcr_reg" descr="" subnode="pmcr_reg_ext" capability="0" offset="0x0.0" selected_by="PMCR" size="0x1c" />
	<field name="pmpt_reg" descr="" subnode="pmpt_reg_ext" capability="0" offset="0x0.0" selected_by="PMPT" size="0x1c" />
	<field name="pmpd_reg" descr="" subnode="pmpd_reg_ext" capability="0" offset="0x0.0" selected_by="PMPD" size="0x30" />
	<field name="pplr_reg" descr="" subnode="pplr_reg_ext" capability="0" offset="0x0.0" selected_by="PPLR" size="0x8" />
	<field name="pplm_reg" descr="" subnode="pplm_reg_ext" capability="0" offset="0x0.0" selected_by="PPLM" size="0x50" />
	<field name="sltp_reg" descr="" subnode="sltp_reg_ext" capability="0" offset="0x0.0" selected_by="SLTP" size="0x4c" />
	<field name="slrg_reg" descr="" subnode="slrg_reg_ext" capability="0" offset="0x0.0" selected_by="SLRG" size="0x28" />
	<field name="pddr_reg" descr="" subnode="pddr_reg_ext" capability="0" offset="0x0.0" selected_by="PDDR" size="0x100" />
	<field name="pptt_reg" descr="" subnode="pptt_reg_ext" capability="0" offset="0x0.0" selected_by="PPTT" size="0x1c" />
	<field name="pprt_reg" descr="" subnode="pprt_reg_ext" capability="0" offset="0x0.0" selected_by="PPRT" size="0x24" />
	<field name="pphcr" descr="" subnode="pphcr_ext" capability="0" offset="0x0.0" selected_by="PPHCR" size="0x50" />
	<field name="ppaos_reg" descr="" subnode="ppaos_reg_ext" capability="0" offset="0x0.0" selected_by="PPAOS" size="0x10" />
	<field name="slred_reg" descr="" subnode="slred_reg_ext" capability="0" offset="0x0.0" selected_by="SLRED" size="0xa8" />
	<field name="pmtu_reg" descr="" subnode="pmtu_reg_ext" capability="0" offset="0x0.0" selected_by="PMTU" size="0x10" />
	<field name="ppad_reg" descr="" subnode="ppad_reg_ext" capability="0" offset="0x0.0" selected_by="PPAD" size="0x10" />
	<field name="pfcc_reg" descr="" subnode="pfcc_reg_ext" capability="0" offset="0x0.0" selected_by="PFCC" size="0x20" />
	<field name="pptb_reg" descr="" subnode="pptb_reg_ext" capability="0" offset="0x0.0" selected_by="PPTB" size="0xc" />
	<field name="pbmc_reg" descr="" subnode="pbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PBMC" size="0x6c" />
	<field name="pvlc_reg" descr="" subnode="pvlc_reg_ext" capability="0" offset="0x0.0" selected_by="PVLC" size="0x10" />
	<field name="pbsr_reg" descr="" subnode="pbsr_reg_ext" capability="0" offset="0x0.0" selected_by="PBSR" size="0x64" />
	<field name="pcmr_reg" descr="" subnode="pcmr_reg_ext" capability="0" offset="0x0.0" selected_by="PCMR" size="0xc" />
	<field name="pvls" descr="" subnode="pvls_ext" capability="0" offset="0x0.0" selected_by="PVLS" size="0x8" />
	<field name="set_node_in" descr="" subnode="set_node_in_ext" capability="0" offset="0x0.0" selected_by="SET_NODE" size="0x40" />
	<field name="register_power_settings" descr="" subnode="register_power_settings_ext" capability="0" offset="0x0.0" selected_by="POWER_SETTINGS" size="0x10" />
	<field name="fp_sl_map_arg" descr="" subnode="fp_sl_map_arg_ext" capability="0" offset="0x0.0" selected_by="FP_SL_MAP" size="0x4" />
	<field name="register_host_endianness" descr="" subnode="register_host_endianness_ext" capability="0" offset="0x0.0" selected_by="HOST_ENDIANNESS" size="0x10" />
	<field name="mfcr" descr="" subnode="mfcr_ext" capability="0" offset="0x0.0" selected_by="MFCR" size="0x8" />
	<field name="mfsc" descr="" subnode="mfsc_ext" capability="0" offset="0x0.0" selected_by="MFSC" size="0x8" />
	<field name="mfsm" descr="" subnode="mfsm_ext" capability="0" offset="0x0.0" selected_by="MFSM" size="0x8" />
	<field name="mfsl" descr="" subnode="mfsl_ext" capability="0" offset="0x0.0" selected_by="MFSL" size="0xc" />
	<field name="fore" descr="" subnode="fore_ext" capability="0" offset="0x0.0" selected_by="FORE" size="0xc" />
	<field name="mfnr" descr="" subnode="mfnr_ext" capability="0" offset="0x0.0" selected_by="MFNR" size="0x30" />
	<field name="mtcap" descr="" subnode="mtcap_ext" capability="0" offset="0x0.0" selected_by="MTCAP" size="0x10" />
	<field name="mtecr" descr="" subnode="mtecr_ext" capability="0" offset="0x0.0" selected_by="MTECR" size="0x60" />
	<field name="mtmp" descr="" subnode="mtmp_ext" capability="0" offset="0x0.0" selected_by="MTMP" size="0x20" />
	<field name="mtwe" descr="" subnode="mtwe_ext" capability="0" offset="0x0.0" selected_by="MTWE" size="0x10" />
	<field name="mtewe" descr="" subnode="mtewe_ext" capability="0" offset="0x0.0" selected_by="MTEWE" size="0x5c" />
	<field name="mvcap_reg" descr="" subnode="mvcap_reg_ext" capability="0" offset="0x0.0" selected_by="MVCAP" size="0x10" />
	<field name="mvcr" descr="" subnode="mvcr_ext" capability="0" offset="0x0.0" selected_by="MVCR" size="0x18" />
	<field name="msps" descr="" subnode="msps_ext" capability="0" offset="0x0.0" selected_by="MSPS" size="0xa0" />
	<field name="mcpp_reg" descr="" subnode="mcpp_reg_ext" capability="0" offset="0x0.0" selected_by="MCPP" size="0x10" />
	<field name="mtbr_reg" descr="" subnode="mtbr_reg_ext" capability="0" offset="0x0.0" selected_by="MTBR" size="0x18" />
	<field name="mfpa_reg" descr="" subnode="mfpa_reg_ext" capability="0" offset="0x0.0" selected_by="MFPA" size="0x20" />
	<field name="mfba_reg" descr="" subnode="mfba_reg_ext" capability="0" offset="0x0.0" selected_by="MFBA" size="0x10c" />
	<field name="mfbe_reg" descr="" subnode="mfbe_reg_ext" capability="0" offset="0x0.0" selected_by="MFBE" size="0xc" />
	<field name="mfmc_reg" descr="" subnode="mfmc_reg_ext" capability="0" offset="0x0.0" selected_by="MFMC" size="0x1c" />
	<field name="mcia" descr="" subnode="mcia_ext" capability="0" offset="0x0.0" selected_by="MCIA" size="0x90" />
	<field name="mcion" descr="" subnode="mcion_ext" capability="0" offset="0x0.0" selected_by="MCION" size="0xc" />
	<field name="mmia" descr="" subnode="mmia_ext" capability="0" offset="0x0.0" selected_by="MMIA" size="0xc" />
	<field name="mmdio" descr="" subnode="mmdio_ext" capability="0" offset="0x0.0" selected_by="MMDIO" size="0xc" />
	<field name="mpgr" descr="" subnode="mpgr_ext" capability="0" offset="0x0.0" selected_by="MPGR" size="0x20" />
	<field name="mfm" descr="" subnode="mfm_ext" capability="0" offset="0x0.0" selected_by="MFM" size="0x18" />
	<field name="mhsr" descr="" subnode="mhsr_ext" capability="0" offset="0x0.0" selected_by="MHSR" size="0x8" />
	<field name="mjtag" descr="" subnode="mjtag_ext" capability="0" offset="0x0.0" selected_by="MJTAG" size="0x30" />
	<field name="msgi" descr="" subnode="msgi_ext" capability="0" offset="0x0.0" selected_by="MSGI" size="0x80" />
	<field name="msci" descr="" subnode="msci_ext" capability="0" offset="0x0.0" selected_by="MSCI" size="0xc" />
	<field name="mpcir" descr="" subnode="mpcir_ext" capability="0" offset="0x0.0" selected_by="MPCIR" size="0x10" />
	<field name="mrtc_reg" descr="" subnode="mrtc_reg_ext" capability="0" offset="0x0.0" selected_by="MRTC" size="0x10" />
	<field name="mgir" descr="" subnode="mgir_ext" capability="0" offset="0x0.0" selected_by="MGIR" size="0xa0" />
	<field name="mgpir" descr="" subnode="mgpir_ext" capability="0" offset="0x0.0" selected_by="MGPIR" size="0xa0" />
	<field name="mdir_reg" descr="" subnode="mdir_reg_ext" capability="0" offset="0x0.0" selected_by="MDIR" size="0x40" />
	<field name="mssir_reg" descr="" subnode="mssir_reg_ext" capability="0" offset="0x0.0" selected_by="MSSIR" size="0x80" />
	<field name="mhmpr_reg" descr="" subnode="mhmpr_reg_ext" capability="0" offset="0x0.0" selected_by="MHMPR" size="0x14" />
	<field name="mpfm" descr="" subnode="mpfm_ext" capability="0" offset="0x0.0" selected_by="MPFM" size="0x8" />
	<field name="mrsr" descr="" subnode="mrsr_ext" capability="0" offset="0x0.0" selected_by="MRSR" size="0x8" />
	<field name="mpgo_reg" descr="" subnode="mpgo_reg_ext" capability="0" offset="0x0.0" selected_by="MPGO" size="0x14" />
	<field name="mnvda_reg" descr="" subnode="mnvda_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDA" size="0x10" />
	<field name="mnvdi_reg" descr="" subnode="mnvdi_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDI" size="0xc" />
	<field name="mnvqc_reg" descr="" subnode="mnvqc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVQC" size="0x8" />
	<field name="mnvia_reg" descr="" subnode="mnvia_reg_ext" capability="0" offset="0x0.0" selected_by="MNVIA" size="0x8" />
	<field name="mnvgc_reg" descr="" subnode="mnvgc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGC" size="0x10" />
	<field name="mnvgn_reg" descr="" subnode="mnvgn_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGN" size="0x20" />
	<field name="mgnle_reg" descr="" subnode="mgnle_reg_ext" capability="0" offset="0x0.0" selected_by="MGNLE" size="0x20" />
	<field name="mtrc_cap_reg" descr="" subnode="mtrc_cap_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CAP" size="0x84" />
	<field name="mtrc_conf_reg" descr="" subnode="mtrc_conf_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CONF" size="0x80" />
	<field name="mtrc_stdb_reg" descr="" subnode="mtrc_stdb_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_STDB" size="0xc" />
	<field name="mtrc_ctrl_reg" descr="" subnode="mtrc_ctrl_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CTRL" size="0x40" />
	<field name="mlcr" descr="" subnode="mlcr_ext" capability="0" offset="0x0.0" selected_by="MLCR" size="0xc" />
	<field name="mgcr_reg" descr="" subnode="mgcr_reg_ext" capability="0" offset="0x0.0" selected_by="MGCR" size="0x20" />
	<field name="merr" descr="" subnode="merr_ext" capability="0" offset="0x0.0" selected_by="MERR" size="0x14" />
	<field name="mpein_reg" descr="" subnode="mpein_reg_ext" capability="0" offset="0x0.0" selected_by="MPEIN" size="0x30" />
	<field name="mpcnt_reg" descr="" subnode="mpcnt_reg_ext" capability="0" offset="0x0.0" selected_by="MPCNT" size="0x100" />
	<field name="mtpps_reg" descr="" subnode="mtpps_reg_ext" capability="0" offset="0x0.0" selected_by="MTPPS" size="0x38" />
	<field name="mtptp" descr="" subnode="mtptp_ext" capability="0" offset="0x0.0" selected_by="MTPTP" size="0x40" />
	<field name="mtutc_reg" descr="" subnode="mtutc_reg_ext" capability="0" offset="0x0.0" selected_by="MTUTC" size="0x1c" />
	<field name="mpir" descr="" subnode="mpir_ext" capability="0" offset="0x0.0" selected_by="MPIR" size="0x10" />
	<field name="mpecs_reg" descr="" subnode="mpecs_reg_ext" capability="0" offset="0x0.0" selected_by="MPECS" size="0x20" />
	<field name="mcqs_reg" descr="" subnode="mcqs_reg_ext" capability="0" offset="0x0.0" selected_by="MCQS" size="0x10" />
	<field name="mcqi_reg" descr="" subnode="mcqi_reg_ext" capability="0" offset="0x0.0" selected_by="MCQI" size="0x94" />
	<field name="mcc_reg" descr="" subnode="mcc_reg_ext" capability="0" offset="0x0.0" selected_by="MCC" size="0x20" />
	<field name="mcda_reg" descr="" subnode="mcda_reg_ext" capability="0" offset="0x0.0" selected_by="MCDA" size="0x90" />
	<field name="mtcq_reg" descr="" subnode="mtcq_reg_ext" capability="0" offset="0x0.0" selected_by="MTCQ" size="0x70" />
	<field name="mkdc_reg" descr="" subnode="mkdc_reg_ext" capability="0" offset="0x0.0" selected_by="MKDC" size="0x2c" />
	<field name="mbct" descr="" subnode="mbct_ext" capability="0" offset="0x0.0" selected_by="MBCT" size="0x420" />
	<field name="mqis_reg" descr="" subnode="mqis_reg_ext" capability="0" offset="0x0.0" selected_by="MQIS" size="0x18" />
	<field name="mirc_reg" descr="" subnode="mirc_reg_ext" capability="0" offset="0x0.0" selected_by="MIRC" size="0x8" />
	<field name="mcdd_reg" descr="" subnode="mcdd_reg_ext" capability="0" offset="0x0.0" selected_by="MCDD" size="0x20" />
	<field name="mdfcr_reg" descr="" subnode="mdfcr_reg_ext" capability="0" offset="0x0.0" selected_by="MDFCR" size="0x60" />
	<field name="mdcr" descr="" subnode="mdcr_ext" capability="0" offset="0x0.0" selected_by="MDCR" size="0x60" />
	<field name="mddt_reg" descr="" subnode="mddt_reg_ext" capability="0" offset="0x0.0" selected_by="MDDT" size="0x110" />
	<field name="mddq" descr="" subnode="mddq_ext" capability="0" offset="0x0.0" selected_by="MDDQ" size="0x30" />
	<field name="mddc" descr="" subnode="mddc_ext" capability="0" offset="0x0.0" selected_by="MDDC" size="0x30" />
	<field name="mdrcr" descr="" subnode="mdrcr_ext" capability="0" offset="0x0.0" selected_by="MDRCR" size="0x30" />
	<field name="mdsr_reg" descr="" subnode="mdsr_reg_ext" capability="0" offset="0x0.0" selected_by="MDSR" size="0x30" />
	<field name="mfsv_reg" descr="" subnode="mfsv_reg_ext" capability="0" offset="0x0.0" selected_by="MFSV" size="0x30" />
	<field name="mqdik_reg" descr="" subnode="mqdik_reg_ext" capability="0" offset="0x0.0" selected_by="MQDIK" size="0x208" />
	<field name="mrpr_reg" descr="" subnode="mrpr_reg_ext" capability="0" offset="0x0.0" selected_by="MRPR" size="0x108" />
	<field name="mcam_reg" descr="" subnode="mcam_reg_ext" capability="0" offset="0x0.0" selected_by="MCAM" size="0x48" />
	<field name="mfrl_reg" descr="" subnode="mfrl_reg_ext" capability="0" offset="0x0.0" selected_by="MFRL" size="0x8" />
	<field name="mmhi_reg" descr="" subnode="mmhi_reg_ext" capability="0" offset="0x0.0" selected_by="MMHI" size="0x80" />
	<field name="cwgcr" descr="" subnode="cwgcr_ext" capability="0" offset="0x0.0" selected_by="CWGCR" size="0x14" />
	<field name="cwtp" descr="" subnode="cwtp_ext" capability="0" offset="0x0.0" selected_by="CWTP" size="0x40" />
	<field name="cwpp" descr="" subnode="cwpp_ext" capability="0" offset="0x0.0" selected_by="CWPP" size="0x20" />
	<field name="cwtpm" descr="" subnode="cwtpm_ext" capability="0" offset="0x0.0" selected_by="CWTPM" size="0x44" />
	<field name="cpqe" descr="" subnode="cpqe_ext" capability="0" offset="0x0.0" selected_by="CPQE" size="0xc" />
	<field name="chltr" descr="" subnode="chltr_ext" capability="0" offset="0x0.0" selected_by="CHLTR" size="0xc" />
	<field name="chltm" descr="" subnode="chltm_ext" capability="0" offset="0x0.0" selected_by="CHLTM" size="0x14" />
	<field name="chlmm" descr="" subnode="chlmm_ext" capability="0" offset="0x0.0" selected_by="CHLMM" size="0x14" />
	<field name="cnct" descr="" subnode="cnct_ext" capability="0" offset="0x0.0" selected_by="CNCT" size="0x8" />
	<field name="cpcs" descr="" subnode="cpcs_ext" capability="0" offset="0x0.0" selected_by="CPCS" size="0x18" />
	<field name="cpid" descr="" subnode="cpid_ext" capability="0" offset="0x0.0" selected_by="CPID" size="0xc" />
	<field name="cnmc" descr="" subnode="cnmc_ext" capability="0" offset="0x0.0" selected_by="CNMC" size="0x4" />
	<field name="cwcam" descr="" subnode="cwcam_ext" capability="0" offset="0x0.0" selected_by="CWCAM" size="0x50" />
	<field name="sbgcr" descr="" subnode="sbgcr_ext" capability="0" offset="0x0.0" selected_by="SBGCR" size="0x4" />
	<field name="sbpr" descr="" subnode="sbpr_ext" capability="0" offset="0x0.0" selected_by="SBPR" size="0x18" />
	<field name="sbcm" descr="" subnode="sbcm_ext" capability="0" offset="0x0.0" selected_by="SBCM" size="0x28" />
	<field name="sbpm" descr="" subnode="sbpm_ext" capability="0" offset="0x0.0" selected_by="SBPM" size="0x20" />
	<field name="sbmm" descr="" subnode="sbmm_ext" capability="0" offset="0x0.0" selected_by="SBMM" size="0x28" />
	<field name="sbme" descr="" subnode="sbme_ext" capability="0" offset="0x0.0" selected_by="SBME" size="0x28" />
	<field name="sbsr" descr="" subnode="sbsr_ext" capability="0" offset="0x0.0" selected_by="SBSR" size="0xfc" />
	<field name="sbib" descr="" subnode="sbib_ext" capability="0" offset="0x0.0" selected_by="SBIB" size="0x10" />
	<field name="sbdcc" descr="" subnode="sbdcc_ext" capability="0" offset="0x0.0" selected_by="SBDCC" size="0x210" />
	<field name="sbdcm" descr="" subnode="sbdcm_ext" capability="0" offset="0x0.0" selected_by="SBDCM" size="0x14" />
	<field name="sbdcr" descr="" subnode="sbdcr_ext" capability="0" offset="0x0.0" selected_by="SBDCR" size="0x14" />
	<field name="sbhbr" descr="" subnode="sbhbr_ext" capability="0" offset="0x0.0" selected_by="SBHBR" size="0x1c" />
	<field name="sbhrr" descr="" subnode="sbhrr_ext" capability="0" offset="0x0.0" selected_by="SBHRR" size="0x60" />
	<field name="sbhbr_v2" descr="" subnode="sbhbr_v2_ext" capability="0" offset="0x0.0" selected_by="SBHBR_V2" size="0x1c" />
	<field name="sbhrr_v2" descr="" subnode="sbhrr_v2_ext" capability="0" offset="0x0.0" selected_by="SBHRR_V2" size="0x90" />
	<field name="sbctc" descr="" subnode="sbctc_ext" capability="0" offset="0x0.0" selected_by="SBCTC" size="0x14" />
	<field name="sbctr" descr="" subnode="sbctr_ext" capability="0" offset="0x0.0" selected_by="SBCTR" size="0x10" />
	<field name="sbcts" descr="" subnode="sbcts_ext" capability="0" offset="0x0.0" selected_by="SBCTS" size="0x14" />
	<field name="sbhpc" descr="" subnode="sbhpc_ext" capability="0" offset="0x0.0" selected_by="SBHPC" size="0x24" />
	<field name="sbsnt" descr="" subnode="sbsnt_ext" capability="0" offset="0x0.0" selected_by="SBSNT" size="0x4" />
	<field name="sbsns" descr="" subnode="sbsns_ext" capability="0" offset="0x0.0" selected_by="SBSNS" size="0x18" />
	<field name="sbsnte" descr="" subnode="sbsnte_ext" capability="0" offset="0x0.0" selected_by="SBSNTE" size="0x10" />
	<field name="sbcam" descr="" subnode="sbcam_ext" capability="0" offset="0x0.0" selected_by="SBCAM" size="0x4c" />
	<field name="ncfg_reg" descr="" subnode="ncfg_reg_ext" capability="0" offset="0x0.0" selected_by="NCFG" size="0x40" />
	<field name="crypto_operational" descr="" subnode="crypto_operational_ext" capability="0" offset="0x0.0" selected_by="CRYPTO_OPERATIONAL" size="0x80" />
	<field name="import_kek_handle" descr="" subnode="import_kek_handle_ext" capability="0" offset="0x0.0" selected_by="IMPORT_KEK_HANDLE" size="0x300" />
	<field name="credential_handle" descr="" subnode="credential_handle_ext" capability="0" offset="0x0.0" selected_by="CREDENTIAL_HANDLE" size="0x300" />
	<field name="ztt" descr="" subnode="ztt_ext" capability="0" offset="0x0.0" selected_by="ZTT" size="0x10" />
	<field name="vhca_trust_level" descr="" subnode="vhca_trust_level_ext" capability="0" offset="0x0.0" selected_by="VHCA_TRUST_LEVEL" size="0x10" />
	<field name="port_state_behavior" descr="" subnode="port_state_behavior_ext" capability="0" offset="0x0.0" selected_by="PORT_STATE_BEHAVIOR" size="0x10" />
	<field name="hca_cap_encap" descr="" subnode="hca_cap_encap_ext" capability="0" offset="0x0.0" selected_by="HCA_CMD_ENCAP" size="0x60" />
	<field name="nvmf_target_pacer_defaults" descr="" subnode="nvmf_target_pacer_defaults_ext" capability="0" offset="0x0.0" selected_by="NVMF_TARGET_PACER_DEFAULTS" size="0x40" />
</node>

<node name="access_reg_summary_selector_ext" descr="" attr_is_union="1" size="0x420" >
	<field name="access_reg_summary" descr="" subnode="access_reg_summary_ext" offset="0x0.0" size="0x420" union_selector="$(parent).ctrl.id" />
	<field name="ctrl" descr="" subnode="access_reg_summary_ctrl_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="application_prio_entry_ext" descr="" size="0x4.0" >
	<field name="protocol_id" descr="According to 802.1Q application priority TLV" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="sel" descr="According to 802.1Q application priority TLV" access="RO" offset="0x0.16" size="0x0.3" />
	<field name="priority" descr="This field is reserved when HCA_CAP.num_ports ==1. \;Table  1939, &quot;QUERY_HCA_CAP Input Structure Layout,&quot; on \;page  2193. According to 802.1Q application priority TLV" access="RO" offset="0x0.21" size="0x0.3" />
</node>

<node name="bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="size" descr="The part of the packet buffer array is allocated for the spe\;cific buffer.\;Units are represented in cells.\;For shared_headroom_pool, this field represents the maxi\;mum load from the shared headroom pool and it can be set \;only when port_shared_buffer is enabled. \;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="epsb" descr="Eligible for Port Shared buffer.\;If epsb is set, packets assigned to bufferX are allowed to \;insert the port shared buffer.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved.\;When lossy==1 this field is reserved.\;The field is reserved for Switch-X/-2." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="lossy" descr="The field indicates if the buffer is lossy.\;0: Lossless\;1: Lossy\;\;The field is reserved for Switch-X/-2.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved.\;NOTE: This field does NOT affect the pause control. Pause \;control is configured using PFCC register." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="xon_threshold" descr="When the amount of data in the buffer goes below this value, \;device stops sending pause frames for the Prios associated \;with the buffer. Units are represented in cells.\;In Spectrum xon_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_threshold" descr="Once the amount of data in the buffer goes above this value, \;device starts sending Pause frames for all Prios associated \;with the buffer. Units are represented in cells.\;In Spectrum xoff_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x4.16" size="0x0.16" />
</node>

<node name="chlmm_ext" descr="" size="0x14.0" >
	<field name="switch_prio" descr="Switch Priority" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="hlt_table_pointer" descr="High Latency Table pointer for multicast packets\;Range 0 .. cap_max_high_latency_table - 1\;" access="RW" offset="0x10.0" size="0x0.8" />
</node>

<node name="chltm_ext" descr="" size="0x14.0" >
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_data-1" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="hlt_table_pointer" descr="High Latency Table pointer for unicast packets\;Range 0 .. cap_max_high_latency_table - 1\;" access="RW" offset="0x10.0" size="0x0.8" />
</node>

<node name="chltr_ext" descr="" size="0xc.0" >
	<field name="hlt_table_index" descr="High Latency Table index\;Range 0 .. cap_max_high_latency_table - 1\;" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="high_latency_thr" descr="High latency threshold\;Units of 1uSec\;\;Note: HW has latency measurement error of   250nSec\;Note: packets with a latency larger than 4Sec latency may \;not be latency-mirrored. Thus it is recommended to set \;SLL to 4Sec\;\;" access="RW" offset="0x8.0" size="0x0.20" />
</node>

<node name="cnct_ext" descr="" size="0x8.0" >
	<field name="prio" descr="Priority" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="local_port" descr="Local port number. If the Index value is 0xFF the opera\;tion is applied for all the ports of the device." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="re" descr="Enable write operation into the r bit" access="WO" offset="0x4.14" size="0x0.1" />
	<field name="ee" descr="Enable write operation into the e bit" access="WO" offset="0x4.15" size="0x0.1" />
	<field name="r" descr="CNTag Remove (Default = 0)\;0: keep CNTags on frames egressing to this port\;1: remove CNTags from frames egressing to this port\;written only if re is set\;(Default = 0)" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="e" descr="CNP Enable (Default = 0)\;0: disable congestion notification for this egress port\;1: enable congestion notification for this egress port\;written only if ee is set" access="RW" offset="0x4.31" size="0x0.1" />
</node>

<node name="cnmc_ext" descr="" size="0x4.0" >
	<field name="prio" descr="Priority" access="RW" offset="0x0.8" size="0x0.3" />
</node>

<node name="command_payload_ext" descr="" size="0x104.0" >
	<field name="data" descr="Command data. It may be a request or a response data." access="RW" high_bound="64" low_bound="0" offset="0x0.0" size="0x104.0" />
</node>

<node name="config_item_ext" descr="" size="0xc.0" >
	<field name="length" descr="Length of configuration item data in bytes (not including \;header). Must be between 0 and 256." access="RW" offset="0x0.0" size="0x0.9" />
	<field name="host_id_valid" descr="Host ID valid:\;1: the type_index.host_id field is valid\;Valid only when MNVGC.priv_nv_other_host=1 and the type_\;class is a Host" access="RO" offset="0x0.9" size="0x0.1" />
	<field name="version" descr="Configuration item version - defines the data structure follow\;ing the header (together with the type field)." access="RW" offset="0x0.12" size="0x0.4" />
	<field name="writer_id" descr="The entity which configured this parameter\;0x0: UNSPECIFIED\;0x1: CHASSIS_BMC\;0x2: MAD\;0x3: BMC\;0x4: COMMAND_INTERFACE\;0x5: ICMD - with unspecified source\;0x6: ICMD_UEFI_HII - configured by the NIC&apos;s UEFI expansion \;ROM&quot;s HII menu.\;0x7: ICMD_UEFI_CLP - configured by the NIC&apos;s expansion \;ROM&quot;s CLP.\;0x8: ICMD_Flexboot - configured by the NIC&quot;s legacy expansion \;ROM.\;0x9: ICMD_mlxconfig - configured by Mellanox mlxconfig tool\;0xA: ICMD_USER1 - value available for customer created tools \;that uses the ICMD interface for writing TLVs.\;0xB: ICMD_USER2 - value available for customer created tools \;that uses the ICMD interface for writing TLVs.\;0xC: ICMD_MLXCONFIG_SET_RAW - configures by\;mlxconfig set raw operation.\;0xD: ICMD_FLEXBOOT_CLP - configured by Legacy Expansion \;ROM CLP\;0x10: BMC_APP1 - Configuration was done over the BMC by \;application #1 (application name is OEM specific)\;0x11: BMC_APP2 - Configuration was done over the BMC by \;application #2 (application name is OEM specific)\;0x12: BMP_APP3 - Configuration was done over the BMC by \;application #3 (application name is OEM specific)\;0x1F: OTHER - the parameter was written by the NIC due to \;other reasons. \;\;Note - This field is writeable only when using the ICMD inter\;face. The only value that are valid for writes are 0x6 through \;0xB. Other values will be replaced by 0x5ICMD." access="RO" enum="UNSPECIFIED=0x0,CHASSIS_BMC=0x1,MAD=0x2,BMC=0x3,COMMAND_INTERFACE=0x4,ICMD=0x5,ICMD_UEFI_HII=0x6,ICMD_UEFI_CLP=0x7,ICMD_Flexboot=0x8,ICMD_mlxconfig=0x9,ICMD_USER1=0xa,ICMD_USER2=0xb,ICMD_MLXCONFIG_SET_RAW=0xc,ICMD_FLEXBOOT_CLP=0xd,BMC_APP1=0x10,BMC_APP2=0x11,BMP_APP3=0x12,OTHER=0x1f" offset="0x0.16" size="0x0.5" />
	<field name="access_mode" descr="Defines which value of the Configuration Item will be accessed.\;0: NEXT - Next value to be applied \;1: CURRENT - Currently set values (only valid for Query \;operation) Supported only if NVGC.nvda_read_current_set\;tings==1.\;2: FACTORY - Default factory values (only valid for Query opera\;tion). Supported only if NVGC.nvda_read_factory_settings==1." access="INDEX" enum="NEXT=0x0,CURRENT=0x1,FACTORY=0x2" offset="0x0.22" size="0x0.2" />
	<field name="type_index" descr="Configuration item index according to its type_class. \;Table 1783, &quot;Configuration Item Data Type Class Global \;Layout,&quot; on page 2048\;Table 1785, &quot;Configuration Item Data Type Class Physical \;Port Layout,&quot; on page 2049\;Table 1787, &quot;Configuration Item Data Type Class Per \;Host-PF Layout,&quot; on page 2049\;Table 1789, &quot;Configuration Item Data Type Class Log Lay\;out,&quot; on page 2050\;Table 1791, &quot;Configuration Item Data Type Class File Lay\;out,&quot; on page 2050\;Table 1793, &quot;Configuration Item Data Type Class Host \;Layout,&quot; on page 2051\;" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="type_class" descr="Type Class.\;0x0: Global\;0x1: Port\;0x3: Host_PF\;0x5: Log\;0x6: File\;0x7: Host\;" access="INDEX" enum="Global=0x0,Port=0x1,Host_PF=0x3,Log=0x5,File=0x6,Host=0x7" offset="0x4.24" size="0x0.8" />
</node>

<node name="cpcs_ext" descr="" size="0x18.0" >
	<field name="tclass" descr="Traffic Class" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="cpmhoe" descr="Enable write operation into cp_min_header_octets." access="WO" offset="0x4.28" size="0x0.1" />
	<field name="cpsbe" descr="Enable write operation into cp_sample_base." access="WO" offset="0x4.29" size="0x0.1" />
	<field name="log2_cpwe" descr="Enable write operation into cpw." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="cpqspe" descr="Enable write operation into cpqsp." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="cpqsp" descr="The set point for the queue, this is the target number of octets \;in the CP&apos;s queue. Default value is 26048.\;Values configured to this register must be 64B aligned. Maxi\;mum value for this register is 4194240.\;Written only if cpqspe is set." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="log2_cpw" descr="The weight (cpW) of the congestion point is equal to two to the \;power of this object.\;Thus, if this object contains a -1, cpW = 1/2.\;Written only if log2_cpwe is set." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="cp_sample_base" descr="The minimum number of octets to enqueue in the CP&apos;s queue \;between CNM PDU transmissions. Default value 150016\;Values configured to this register must be 64B aligned. Maxi\;mum value for the register is 2147483584.\;Written only if cpsbe is set" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="cp_min_header_octets" descr="The minimum number of octets that the CP is to return in the \;Encapsulated MSDU field (IEEE 802.1Qau 33.4.10) of each \;CNM it generates (IEEE 802.1Qau 32.9.4). Default value 0.\;Written only if cpmhoe is set." access="RW" offset="0x14.0" size="0x4.0" />
</node>

<node name="cpid_ext" descr="" size="0xc.0" >
	<field name="prio" descr="Priority" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="local_port" descr="Local port number. if the Index value is 0xFF the oper\;ation will be applied for all the ports of the device." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cpid_high" descr="IEEE 802.1Qau Congestion Point Identifier." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="cpid_low" descr="IEEE 802.1Qau Congestion Point Identifier." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="cpqe_ext" descr="" size="0xc.0" >
	<field name="local_port" descr="Egress Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="marking_percent" descr="ECN Marking percentage when the local_port rate is \;above the phantom queue rate as configured by phan\;tom_queue_rate in QEEC, see Section 19.3.4, &quot;QEEC - \;QoS ETS Element Configuration&quot;, on page 1160\;Range is 0..100, units of integer percentage" access="RW" offset="0x8.16" size="0x0.7" />
</node>

<node name="credential_handle_ext" descr="" size="0x300.0" >
	<field name="crypto_login_object" descr="Information required to identify an officer.\;modify_field_select is reserved.\;Needed for all operations." subnode="crypto_login_obj_ext" access="RW" offset="0x0.0" size="0x100.0" />
	<field name="credential_object" descr="The import_KEK to add.\;For add, this is input (WO) of new KEK info.\;For query, this output (RO) with limited info of KEK.\;modify_field_select is reserved.\;For delete this field is reserved." subnode="credential_obj_ext" access="RW" offset="0x100.0" size="0x100.0" />
	<field name="credential_id" descr="For query/delete ops, this is input (WO).\;For add, input to this field is ignored, output is the \;selected\;ID." access="INDEX" offset="0x200.0" size="0x0.24" />
	<field name="write_operation" descr="0x1: ADD_OPERATION\;0x2: DELETE_OPERATION" access="WO" enum="ADD_OPERATION=0x1,DELETE_OPERATION=0x2" offset="0x200.24" size="0x0.4" />
</node>

<node name="credential_obj_ext" descr="" size="0x100.0" >
	<field name="modify_field_select" descr="Field select indicates in QUERY which fields are modi\;fiable (1 means modifiable), and in MODIFY which \;fields to modify." subnode="uint64" offset="0x0.0" size="0x8.0" />
	<field name="credential_role" descr="0x0: role_officer - Officer role. \;0x1: role_user - User role." enum="role_officer=0x0,role_user=0x1" offset="0x8.0" size="0x0.8" />
	<field name="state" descr="Credential state, Valid for Query command only.\;0x0: READY - the Credential state when first created\;0x1: ERROR - Credential unusable, need to destroy and \;re-create this credential." enum="READY=0x0,ERROR=0x1" offset="0x8.24" size="0x0.8" />
	<field name="credential" descr="The actual secret. Should be wrapped by import_KEK \;since\;credentials are only used in wrapped import method. \;Size includes\;8 bytes IV for wrapping." high_bound="11" low_bound="0" offset="0x40.0" size="0x30.0" />
</node>

<node name="crspace_access_payload_ext" descr="" size="0x104.0" >
	<field name="address" descr="Starting address" access="WO" offset="0x0.0" size="0x4.0" />
	<field name="data" descr="CrSpace data" access="RW" high_bound="63" low_bound="0" offset="0x4.0" size="0x100.0" />
</node>

<node name="crypto_login_obj_ext" descr="" size="0x100.0" >
	<field name="modify_field_select" descr="Field select indicates in QUERY which fields are mod\;ifiable (1 means modifiable), and in MODIFY which \;fields to modify." subnode="uint64" offset="0x0.0" size="0x8.0" />
	<field name="credential_pointer" descr="Credential pointer" offset="0x10.0" size="0x0.24" />
	<field name="state" descr="0x0: VALID - login is valid.\;0x1: INVALID - login is invalid, software can&quot;t manage \;wrapped crypto keys anymore, should destroy this \;login object and create a new one if needed. May \;happen, for example, due to a KEK or Credential used \;in this login being removed." enum="VALID=0x0,INVALID=0x1" offset="0x10.24" size="0x0.4" />
	<field name="session_import_kek_ptr" descr="Import_KEK pointer to be used for all secured \;information communicated in crypto commands (key \;fields), including the provided credential in this \;command" offset="0x14.0" size="0x0.24" />
	<field name="credential" descr="The credential secret, wrapped by the import_KEK \;indicated in this command. Size includes 8 bytes IV \;for wrapping" high_bound="11" low_bound="0" offset="0x40.0" size="0x30.0" />
</node>

<node name="crypto_operational_ext" descr="" size="0x80.0" >
	<field name="kek_size" descr="0x0: SIZE_128\;0x1: SIZE_256" access="WO" enum="SIZE_128=0x0,SIZE_256=0x1" offset="0x0.0" size="0x0.4" />
	<field name="wrapped_crypto_going_to_commissioning" descr="When set to 1, the device receives an authenticated \;command to go back to crypto commissioning mode. \;This will happen after the next FW reset. \;Valid only when wrapped_crypto_operational=1. \;After FW reset, wrapped_crypto_operational will be \;unset to 0, and this bit will be unset to 0 as well." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="wrapped_crypto_operational" descr="If set to 1, device is in operational mode. Read only." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="credential" descr="Plaintext credential secret for non-volatile index 0" access="WO" high_bound="9" low_bound="0" offset="0x8.0" size="0x28.0" />
	<field name="kek" descr="Plaintext import_KEK for non-volatile index 0.\;In 128bit KEK, Only the 128 MSBs are valid. LSBs are \;reserved." access="WO" high_bound="7" low_bound="0" offset="0x30.0" size="0x20.0" />
</node>

<node name="cwcam_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups\;0: RegID_0x2800_to_0x287F\;Values 1-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features \;Values 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="cw_access_reg_cap_mask" descr="Supported port&apos;s access register bitmaks. Based on \;access_reg_group index.\;7When bit is set, The register is supported in the device. \;When access_reg_group == 0 :\;Bit_2: 0x2802_CWTP\;Bit_3: 0x2803_CWTPM\;Bit_31: 0x281f_CWCAM" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="Supported port&apos;s enhanced features. Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bits 0-127 are Reserved" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="cwgcr_ext" descr="" size="0x14.0" >
	<field name="aqs_time" descr="Average queue size time\;Time from current_queue_size to previous_aqs\;The time is 2^aqs_time * 64nSec\;Valid range is 0..24" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="aqs_weight" descr="Average queue size weight.\;The average queue size (aqs) is calculated by:\;aqs = ((current_queue_size)*2^-w) + ((previous_aqs)*(1-2^-w)) \;where w is aqs_weight\;The time between current_queue_size and previous_aqs is con\;figured by aqs_time\;Note: when mode=percentage then there is no moving average \;(the aqs_weight is effectively 0). See Section 25.31.2, &quot;CWTP - \;Congestion WRED ECN TClass Profile Register&quot;, on page 1872" access="RW" offset="0x0.8" size="0x0.4" />
	<field name="scd" descr="Enable ECN Source Congestion Detection only. Don&apos;t mark vic\;tim packets.\;" access="RW" offset="0x0.16" size="0x0.1" />
	<field name="en" descr="enable bits:\;bit2: WRED drop enable\;" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="cece" descr="Count ECN for Congestion Experienced\;0: do not count &quot;ECN mark&quot; for a packet which has Congestion \;Experienced (ECN=11 at ingress) \;1: do count ECN mark for a packet which has Congestion Expe\;rienced (ECN=11 at ingress) and experiences congestion in the \;switch (default)\;In any case, a packet coming with ECN=00 is not counted as \;ECN." access="RW" offset="0x4.0" size="0x0.1" />
	<field name="mece" descr="Mirror ECN for Congestion Experienced\;0: do not ecn-mirror a packet which has Congestion Experi\;enced (ECN=11 at ingress)\;1: do ecn-mirror for a packet which has Congestion Experienced \;(ECN=11 at ingress) and experiences congestion in the switch \;(default)\;In any case, a packet coming with ECN=00 is not ecn-mirrored\;Reserved when Spectrum-1\;Reserved when Quantum which always does ecn-mirror regard\;less of fecn in the packet" access="RW" offset="0x4.1" size="0x0.1" />
</node>

<node name="cwpp_ext" descr="" size="0x20.0" >
	<field name="pool" descr="Egress pool in the switch shared buffer\;Range is 0..cap_num_pool_supported-1" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="profile1_min" descr="Minimum Average Queue Size of the profile number &lt;i&gt;, in \;cells. Valid inputs are 0..cap_total_buffer_size/cap_cell_\;size\;For Spectrum: must be a multiple of 64" access="RW" offset="0x8.0" size="0x0.20" />
	<field name="profile1_max" descr="Maximum Average Queue Size of the profile number &lt;i&gt;, in \;cells. Valid inputs are 0..cap_total_buffer_size/cap_cell_\;size\;For Spectrum: must be a multiple of 64" access="RW" offset="0xC.0" size="0x0.20" />
	<field name="profile1_percent" descr="Percentage of WRED and ECN marking for Maximum Aver\;age Queue Size of the profile number &lt;i&gt;\;Range is 0..100, units of integer percentage\;Default is 0" access="RW" offset="0xC.24" size="0x0.7" />
	<field name="profile2_min" descr="Same as above." access="RW" offset="0x10.0" size="0x0.20" />
	<field name="profile2_max" descr="Same as above." access="RW" offset="0x14.0" size="0x0.20" />
	<field name="profile2_percent" descr="Same as above." access="RW" offset="0x14.24" size="0x0.7" />
	<field name="profile3_min" descr="Same as above." access="RW" offset="0x18.0" size="0x0.20" />
	<field name="profile3_max" descr="Same as above." access="RW" offset="0x1C.0" size="0x0.20" />
	<field name="profile3_percent" descr="Same as above." access="RW" offset="0x1C.24" size="0x0.7" />
</node>

<node name="cwtp_ext" descr="" size="0x40.0" >
	<field name="pnat" descr="Port number access type. Determines the way local_port \;is interpreted:\;2: host_port_number" access="INDEX" enum="host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_sb-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="mode" descr="Mode of thresholds for WRED and ECN:\;0: Fixed\;1: Percentage" access="RW" enum="Fixed=0x0,Percentage=0x1" offset="0x24.24" size="0x0.1" />
	<field name="profile1_min" descr="Minimum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_\;cell_size.\;For Spectrum: must be a multiple of 64\;Note: for Spectrum, must be larger than 2^aqs_weight \;cells, see Section 25.31.1, &quot;CWGCR - Congestion WRED \;ECN General Configuration Register&quot;, on page 1870\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. \;Range is 0..100, units of integer percentage. When ECN \;Source Congestion Detection is enabled then congestion \;occurs when there are at least 256 cells in the buffer\;" access="RW" offset="0x28.0" size="0x0.20" />
	<field name="profile1_max" descr="Maximum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_\;cell_size\;For Spectrum: must be a multiple of 64\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. \;Range is 0..100, units of integer percentage.\;profile&lt;i&gt;_max must always be equal or greater than \;profile&lt;i&gt;_min" access="RW" offset="0x2C.0" size="0x0.20" />
	<field name="profile1_percent" descr="Percentage of WRED and ECN marking for Maximum \;Average Queue Size of the profile number &lt;i&gt;\;Range is 0..100, units of integer percentage\;Default is 0" access="RW" offset="0x2C.24" size="0x0.7" />
	<field name="profile2_min" descr="Same as above." access="RW" offset="0x30.0" size="0x0.20" />
	<field name="profile2_max" descr="Same as above." access="RW" offset="0x34.0" size="0x0.20" />
	<field name="profile2_percent" descr="Same as above." access="RW" offset="0x34.24" size="0x0.7" />
	<field name="profile3_min" descr="Same as above." access="RW" offset="0x38.0" size="0x0.20" />
	<field name="profile3_max" descr="Same as above." access="RW" offset="0x3C.0" size="0x0.20" />
	<field name="profile3_percent" descr="Same as above." access="RW" offset="0x3C.24" size="0x0.7" />
</node>

<node name="cwtpm_ext" descr="" size="0x44.0" >
	<field name="pnat" descr="Port number access type. Determines the way local_port \;is interpreted:\;2: host_port_number" access="INDEX" enum="host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_sb-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="ee" descr="Enable ECN on traffic class\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.0" size="0x0.1" />
	<field name="ew" descr="Enable WRED on traffic class:\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.1" size="0x0.1" />
</node>

<node name="db_threshold_register_layout_ext" descr="" size="0x10.0" >
	<field name="threshold" descr="Required upper watermark.\;When FIFO/buffer reaches this size- an event will be sent" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="size" descr="Current FIFO/buffer size" access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="dcbx_app_reg_ext" descr="" size="0x14.0" >
	<field name="port_number" descr="Physical port number.\;This field is reserved when HCA_CAP.num_ports ==1. \;Table  1939, &quot;QUERY_HCA_CAP Input Structure Layout,&quot; on \;page  2193" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="num_app_prio" descr="" access="RO" offset="0x4.0" size="0x0.6" />
	<field name="app_prio" descr="Application priority entry. \;" subnode="application_prio_entry_ext" access="RO" high_bound="VARIABLE" low_bound="0" offset="0x10.0" size="0x4.0" />
</node>

<node name="dcbx_param_reg_ext" descr="" size="0x40.0" >
	<field name="max_application_table_size" descr="The maximum size of DCBX application table." access="RO" offset="0x0.0" size="0x0.6" />
	<field name="port_number" descr="Physical port number.\;This field is reserved when HCA_CAP.num_ports ==1. \;Table  1939, &quot;QUERY_HCA_CAP Input Structure Layout,&quot; on \;page  2193" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dcbx_standby_cap" descr="If set, device supports DCBX on standby mode (aux power)." access="RO" offset="0x0.29" size="0x0.1" />
	<field name="dcbx_ieee_cap" descr="If set, DCBX IEEE version is supported." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="dcbx_cee_cap" descr="If set, DCBX CEE version is supported." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="version_admin" descr="Set the DCBX version.\;0x0: disabled- host is in charge \;0x1: CEE - supported only when dcbx_cee_cap==1\;0x2: IEEE - supported only when dcbx_ieee_cap==1\;0x3: CEE_and_IEEE - CEE and IEEE auto select. When using \;this mode, the device uses IEEE mode. If handshake with \;other party succeed, it will continue on using IEEE, other\;wise it will fall back to CEE. Supported only when dcbx_\;cee_cap==1 and cbx_ieee_cap==1." access="RW" enum="disabled=0x0,CEE=0x1,IEEE=0x2,CEE_and_IEEE=0x3" offset="0x4.0" size="0x0.3" />
	<field name="version_oper" descr="0x0: disabled - host is in charge.\;0x1: CEE_enabled\;0x2: IEEE_enabled\;If the DCBX_PARAM.version_oper is 0x0, all oper and \;remote fields in DCBX_PARAM () are invalid. DCBX_APPLI\;CATION.num_app_prio is 0\;DCBX_PARAM.version is 0x0 until a successful handshake \;with remote party.\;" access="RO" enum="disabled=0x0,CEE_enabled=0x1,IEEE_enabled=0x2" offset="0x4.8" size="0x0.3" />
	<field name="num_of_tc_admin" descr="Number of TCs." access="RW" offset="0x8.0" size="0x0.4" />
	<field name="num_of_tc_oper" descr="Number of TCs - operational state after negotiation with \;remote party.\;" access="RO" offset="0x8.8" size="0x0.4" />
	<field name="pfc_cap_admin" descr="Number of traffic classes that may simultaneously support \;PFC. Can be set in the range 0   8" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="pfc_cap_oper" descr="Number of traffic classes that may simultaneously support \;PFC. Can be set in the range 0   8 - operational state after \;negotiation with remote party.\;" access="RO" offset="0x8.24" size="0x0.4" />
	<field name="willing_admin" descr="0x0: non_willing\;0x1: willing" access="RW" enum="non_willing=0x0,willing=0x1" offset="0x8.31" size="0x0.1" />
	<field name="remote_num_of_tc" descr="Remote side&apos;s number of TCs. Valid only after negotiation \;with remote party." access="RO" offset="0xC.0" size="0x0.4" />
	<field name="remote_pfc_cap" descr="Remote side&apos;s number of traffic classes that may simultane\;ously support PFC. Valid only after negotiation with remote \;party." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="remote_willing" descr="Remote side&apos;s willing state. Valid only after negotiation with \;remote party" access="RO" offset="0xC.31" size="0x0.1" />
	<field name="error" descr="Bitmask indicates errors reported.\;Bit 0: not enough TC to comply with remote \;Bit 1: not enough pfc to comply with remote \;Bit 2: TSA unsupported" access="RO" offset="0x10.0" size="0x0.8" />
</node>

<node name="device_info_ext" descr="" size="0x20.0" >
	<field name="device_index" descr="Device index\;The first device should number 0" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="flash_id" descr="The flash ID that the device is using." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="lc_pwr_on" descr="If set to &apos;1&apos;, the fields related to the device are valid since the \;line-card is powered on and plugged and matching the INI ver\;sion. \;Note: this bit is not an indication to validity of the fields related \;to the specific FW capabilities and version." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="thermal_sd" descr="Thermal Shutdown. If set, the device was shut down due to \;thermal event." access="RO" offset="0x0.29" size="0x0.1" />
	<field name="flash_owner" descr="If set to &apos;1&apos;, the device is the flash owner. Otherwise, a shared \;flash is used by this device (another device is the flash owner)." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="uses_flash" descr="If set, the device uses a flash" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="device_type" descr="0: Amos Gearbox\;1: Abir Gearbox" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fw_major" descr="Major FW version number. Valid only after the FW is burnt. Oth\;erwise, the value should be &apos;0&apos;." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="fw_sub_minor" descr="Sub-minor FW version number. Valid only after the FW is \;burnt. Otherwise, the value should be &apos;0&apos;." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fw_minor" descr="Minor FW version number. Valid only after the FW is burnt. \;Otherwise, the value should be &apos;0&apos;." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="max_cmd_write_size_supp" descr="Maximum write size (in D-Words) that the device supports for \;its PRM commands." access="RO" offset="0xC.0" size="0x0.8" />
	<field name="max_cmd_read_size_supp" descr="Maximum read size (in D-Words) that the device supports for \;its PRM commands." access="RO" offset="0xC.8" size="0x0.8" />
	<field name="device_type_name" descr="Device type ASCII name. Up to 8 chars\;" access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
</node>

<node name="enum_entry" descr="" size="0x4.0" >
</node>

<node name="eth_2819_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="ether_stats_drop_events_high" descr="The total number of events in which packets \;were dropped by the probe due to lack of \;resources.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ether_stats_drop_events_low" descr="The total number of events in which packets \;were dropped by the probe due to lack of \;resources.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ether_stats_octets_high" descr="The total number of octets of data (including \;those in bad packets) received (excluding \;framing bits but including FCS octets).\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ether_stats_octets_low" descr="The total number of octets of data (including \;those in bad packets) received (excluding \;framing bits but including FCS octets).\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ether_stats_pkts_high" descr="The total number of packets (including bad \;packets, broadcast packets, and multicast \;packets) received.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ether_stats_pkts_low" descr="The total number of packets (including bad \;packets, broadcast packets, and multicast \;packets) received.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_high" descr="The total number of good packets received \;that were directed to the broadcast address. \;Note: This does not include multicast pack\;ets.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_low" descr="The total number of good packets received \;that were directed to the broadcast address. \;Note: This does not include multicast pack\;ets.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_high" descr="The total number of good packets received \;that were directed to a multicast MAC \;address. \;Note: This number does not include packets \;directed to the broadcast address.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_low" descr="The total number of good packets received \;that were directed to a multicast MAC \;address. \;Note: This number does not include packets \;directed to the broadcast address.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_high" descr="The total number of packets received that \;had a length (excluding framing bits, but \;including FCS octets) of between 64 and \;MTU octets, inclusive, but had either a bad \;frame check sequence (FCS) with an inte\;gral number of octets (FCS error) or a bad \;FCS with a non-integral number of octets \;(alignment error).\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_low" descr="The total number of packets received that \;had a length (excluding framing bits, but \;including FCS octets) of between 64 and \;MTU octets, inclusive, but had either a bad \;frame check sequence (FCS) with an inte\;gral number of octets (FCS error) or a bad \;FCS with a non-integral number of octets \;(alignment error).\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_high" descr="The total number of packets received that \;were less than 64 octets long (excluding \;framing bits, but including FCS octets) and \;were otherwise well formed.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_low" descr="The total number of packets received that \;were less than 64 octets long (excluding \;framing bits, but including FCS octets) and \;were otherwise well formed.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_high" descr="The total number of packets received that \;were longer than MTU octets (excluding \;framing bits, but including FCS octets) but \;were otherwise well formed.\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_low" descr="The total number of packets received that \;were longer than MTU octets (excluding \;framing bits, but including FCS octets) but \;were otherwise well formed.\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="ether_stats_fragments_high" descr="The total number of packets received that \;were less than 64 octets in length (excluding \;framing bits but including FCS octets) and \;had either a bad FCS with an integral num\;ber of octets (FCS error) or a bad FCS with a \;non-integral number of octets (alignment \;error).\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="ether_stats_fragments_low" descr="The total number of packets received that \;were less than 64 octets in length (excluding \;framing bits but including FCS octets) and \;had either a bad FCS with an integral num\;ber of octets (FCS error) or a bad FCS with a \;non-integral number of octets (alignment \;error).\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="ether_stats_jabbers_high" descr="The total number of packets received that \;were longer than MTU octets (excluding \;framing bits, but including FCS octets), and \;had either a bad FCS with an integral num\;ber of octets (FCS error) or a bad FCS with a \;non-integral number of octets (alignment \;error).\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="ether_stats_jabbers_low" descr="The total number of packets received that \;were longer than MTU octets (excluding \;framing bits, but including FCS octets), and \;had either a bad FCS with an integral num\;ber of octets (FCS error) or a bad FCS with a \;non-integral number of octets (alignment \;error).\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="ether_stats_collisions_high" descr="The best estimate of the total number of \;collisions on this Ethernet segment.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ether_stats_collisions_low" descr="The best estimate of the total number of \;collisions on this Ethernet segment.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_high" descr="The total number of packets (including bad \;packets) received that were 64 octets in \;length (excluding framing bits but including \;FCS octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_low" descr="The total number of packets (including bad \;packets) received that were 64 octets in \;length (excluding framing bits but including \;FCS octets)." access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_high" descr="The total number of packets (including bad \;packets) received that were between 65 and \;127 octets in length (excluding framing bits \;but including FCS octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_low" descr="The total number of packets (including bad \;packets) received that were between 65 and \;127 octets in length (excluding framing bits \;but including FCS octets)." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_high" descr="The total number of packets (including bad \;packets) received that were between 128 \;and 255 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_low" descr="The total number of packets (including bad \;packets) received that were between 128 \;and 255 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_high" descr="The total number of packets (including bad \;packets) received that were between 256 \;and 511 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_low" descr="The total number of packets (including bad \;packets) received that were between 256 \;and 511 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_high" descr="The total number of packets (including bad \;packets) received that were between 512 \;and 1023 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_low" descr="The total number of packets (including bad \;packets) received that were between 512 \;and 1023 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad \;packets) received that were between 1024 \;and 1518 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_low" descr="The total number of packets (including bad \;packets) received that were between 1024 \;and 1518 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad \;packets) received that were between 1519 \;and 2047 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_low" descr="The total number of packets (including bad \;packets) received that were between 1519 \;and 2047 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad \;packets) received that were between 2048 \;and 4095 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_low" descr="The total number of packets (including bad \;packets) received that were between 2048 \;and 4095 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x94.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad \;packets) received that were between 4096 \;and 8191 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x98.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_low" descr="The total number of packets (including bad \;packets) received that were between 4096 \;and 8191 octets in length (excluding framing \;bits but including FCS octets)." access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad \;packets) received that were between 8192 \;and 10239 octets in length (excluding fram\;ing bits but including FCS octets).\;" access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_low" descr="The total number of packets (including bad \;packets) received that were between 8192 \;and 10239 octets in length (excluding fram\;ing bits but including FCS octets).\;" access="RO" offset="0xA4.0" size="0x4.0" />
</node>

<node name="eth_2863_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="if_in_octets_high" descr="The total number of octets received, including \;framing characters. Including MAC control frames.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="if_in_octets_low" descr="The total number of octets received, including \;framing characters. Including MAC control frames.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_high" descr="The number of packets successfully received, \;which were not addressed to a multicast or broad\;cast MAC address.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_low" descr="The number of packets successfully received, \;which were not addressed to a multicast or broad\;cast MAC address.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="if_in_discards_high" descr="The number of inbound packets which were chosen \;to be discarded even though no errors had been \;detected to prevent their being deliverable to a \;higher-layer protocol.\;\;\;\;\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="if_in_discards_low" descr="The number of inbound packets which were chosen \;to be discarded even though no errors had been \;detected to prevent their being deliverable to a \;higher-layer protocol.\;\;\;\;\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="if_in_errors_high" descr="The number of inbound packets that contained \;errors preventing them from being deliverable to a \;higher-layer protocol. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="if_in_errors_low" descr="The number of inbound packets that contained \;errors preventing them from being deliverable to a \;higher-layer protocol. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="if_in_unknown_protos_high" descr="The number of packets received via the interface \;which were discarded because of an unknown or \;unsupported protocol.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="if_in_unknown_protos_low" descr="The number of packets received via the interface \;which were discarded because of an unknown or \;unsupported protocol.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="if_out_octets_high" descr="The total number of octets transmitted out of the \;interface, including framing characters.\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="if_out_octets_low" descr="The total number of octets transmitted out of the \;interface, including framing characters.\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_high" descr="The total number of packets that higher-level pro\;tocols requested be transmitted and were not \;addressed to a multicast or broadcast MAC \;address, including those that were discarded or not \;sent.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_low" descr="The total number of packets that higher-level pro\;tocols requested be transmitted and were not \;addressed to a multicast or broadcast MAC \;address, including those that were discarded or not \;sent.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="if_out_discards_high" descr="The number of outbound packets which were cho\;sen to be discarded, even though no errors had \;been detected to prevent their being transmitted. \;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="if_out_discards_low" descr="The number of outbound packets which were cho\;sen to be discarded, even though no errors had \;been detected to prevent their being transmitted. \;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="if_out_errors_high" descr="The number of outbound packets that could not be \;transmitted because of errors.\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="if_out_errors_low" descr="The number of outbound packets that could not be \;transmitted because of errors.\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_high" descr="The number of packets successfully received, \;which were addressed to a multicast MAC address.\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_low" descr="The number of packets successfully received, \;which were addressed to a multicast MAC address.\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_high" descr="The number of packets successfully received, \;which were addressed to a broadcast MAC address.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_low" descr="The number of packets successfully received, \;which were addressed to a broadcast MAC address.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_high" descr="The total number of packets that higher-level pro\;tocols requested be transmitted, and which were \;addressed to a multicast MAC address, including \;those that were discarded or not sent.\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_low" descr="The total number of packets that higher-level pro\;tocols requested be transmitted, and which were \;addressed to a multicast MAC address, including \;those that were discarded or not sent.\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_high" descr="The total number of packets that higher-level pro\;tocols requested be transmitted, and which were \;addressed to a broadcast MAC address, including \;those that were discarded or not sent.\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_low" descr="The total number of packets that higher-level pro\;tocols requested be transmitted, and which were \;addressed to a broadcast MAC address, including \;those that were discarded or not sent.\;" access="RO" offset="0x64.0" size="0x4.0" />
</node>

<node name="eth_3635_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="dot3stats_alignment_errors_high" descr="A count of frames received that are not an inte\;gral number of octets in length and do not pass \;the FCS check.\;" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="dot3stats_alignment_errors_low" descr="A count of frames received that are not an inte\;gral number of octets in length and do not pass \;the FCS check.\;" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_high" descr="A count of frames received that are an integral \;number of octets in length but do not pass the \;FCS check. This count does not include frames \;received with frame-too-long or frame-too-\;short errors.\;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_low" descr="A count of frames received that are an integral \;number of octets in length but do not pass the \;FCS check. This count does not include frames \;received with frame-too-long or frame-too-\;short errors.\;" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_high" descr="A count of frames that are involved in a single \;collision, and are subsequently transmitted \;successfully.\;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_low" descr="A count of frames that are involved in a single \;collision, and are subsequently transmitted \;successfully.\;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_high" descr="A count of frames that are involved in more than \;one collision and are subsequently transmitted \;successfully. \;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_low" descr="A count of frames that are involved in more than \;one collision and are subsequently transmitted \;successfully. \;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_high" descr="A count of times that the SQE TEST ERROR is \;received on a particular interface.\;This counter does not increment on interfaces \;operating at speeds greater than 10 Mb/s, or on \;interfaces operating in full-duplex mode. \;" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_low" descr="A count of times that the SQE TEST ERROR is \;received on a particular interface.\;This counter does not increment on interfaces \;operating at speeds greater than 10 Mb/s, or on \;interfaces operating in full-duplex mode. \;" access="RW" offset="0x24.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_high" descr="A count of frames for which the first transmis\;sion attempt on a particular interface is delayed \;because the medium is busy. \;This counter does not increment when the \;interface is operating in full-duplex mode. \;" access="RW" offset="0x28.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_low" descr="A count of frames for which the first transmis\;sion attempt on a particular interface is delayed \;because the medium is busy. \;This counter does not increment when the \;interface is operating in full-duplex mode. \;" access="RW" offset="0x2C.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_high" descr="The number of times that a collision is detected \;on a particular interface later than one slotTime \;into the transmission of a packet.\;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x30.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_low" descr="The number of times that a collision is detected \;on a particular interface later than one slotTime \;into the transmission of a packet.\;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x34.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_high" descr="A count of frames for which transmission on a \;particular interface fails due to excessive colli\;sions.\;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x38.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_low" descr="A count of frames for which transmission on a \;particular interface fails due to excessive colli\;sions.\;This counter does not increment when the \;interface is operating in full-duplex mode.\;" access="RW" offset="0x3C.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_high" descr="A count of frames for which transmission failed \;and were discarded even though no errors had \;been detected to prevent their being deliverable \;to a higher-layer protocol.\;" access="RW" offset="0x40.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_low" descr="A count of frames for which transmission failed \;and were discarded even though no errors had \;been detected to prevent their being deliverable \;to a higher-layer protocol.\;" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_high" descr="The number of times that the carrier sense con\;dition was lost or never asserted when attempt\;ing to transmit a frame on a particular \;interface. \;This counter does not increment when the \;interface is operating in full-duplex mode. \;" access="RW" offset="0x48.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_low" descr="The number of times that the carrier sense con\;dition was lost or never asserted when attempt\;ing to transmit a frame on a particular \;interface. \;This counter does not increment when the \;interface is operating in full-duplex mode. \;" access="RW" offset="0x4C.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_high" descr="A count of frames received that exceed the max\;imum permitted frame size.\;" access="RW" offset="0x50.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_low" descr="A count of frames received that exceed the max\;imum permitted frame size.\;" access="RW" offset="0x54.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_high" descr="A count of frames for which reception failed and \;were discarded even though no errors had been \;detected to prevent their being deliverable to a \;higher-layer protocol.\;" access="RW" offset="0x58.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_low" descr="A count of frames for which reception failed and \;were discarded even though no errors had been \;detected to prevent their being deliverable to a \;higher-layer protocol.\;" access="RW" offset="0x5C.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_high" descr="The number of times the receiving media is \;non-idle (a carrier event) for a period of time \;equal to or greater than minFrameSize, and \;during which there was at least one occurrence \;of an event that causes the PHY to indicate \;&quot;Receive Error&quot;.\;\;" access="RW" offset="0x60.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_low" descr="The number of times the receiving media is \;non-idle (a carrier event) for a period of time \;equal to or greater than minFrameSize, and \;during which there was at least one occurrence \;of an event that causes the PHY to indicate \;&quot;Receive Error&quot;.\;\;" access="RW" offset="0x64.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_high" descr="A count of MAC Control frames received that \;contain an opcode that is not supported.\;" access="RW" offset="0x68.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_low" descr="A count of MAC Control frames received that \;contain an opcode that is not supported.\;" access="RW" offset="0x6C.0" size="0x4.0" />
	<field name="dot3in_pause_frames_high" descr="A count of MAC Control frames received with an \;opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x70.0" size="0x4.0" />
	<field name="dot3in_pause_frames_low" descr="A count of MAC Control frames received with an \;opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x74.0" size="0x4.0" />
	<field name="dot3out_pause_frames_high" descr="A count of MAC Control frames transmitted with \;an opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x78.0" size="0x4.0" />
	<field name="dot3out_pause_frames_low" descr="A count of MAC Control frames transmitted with \;an opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x7C.0" size="0x4.0" />
</node>

<node name="eth_802_3_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="a_frames_transmitted_ok_high" descr="A count of frames that are successfully trans\;mitted. \;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="a_frames_transmitted_ok_low" descr="A count of frames that are successfully trans\;mitted. \;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="a_frames_received_ok_high" descr="A count of frames that are successfully \;received. This does not include frames \;received with frame-too-long, frame check \;sequence (FCS), length or alignment errors, \;or frames lost due to other MAC errors.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="a_frames_received_ok_low" descr="A count of frames that are successfully \;received. This does not include frames \;received with frame-too-long, frame check \;sequence (FCS), length or alignment errors, \;or frames lost due to other MAC errors.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="a_frame_check_sequence_errors_high" descr="A count of receive frames that are an integral \;number of octets in length and do not pass the \;FCS check. This does not include frames \;received with frame-too-long, or frame-too-\;short (frame fragment) errors.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="a_frame_check_sequence_errors_low" descr="A count of receive frames that are an integral \;number of octets in length and do not pass the \;FCS check. This does not include frames \;received with frame-too-long, or frame-too-\;short (frame fragment) errors.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="a_alignment_errors_high" descr="A count of frames that are not an integral \;number of octets in length and do not pass the \;FCS check.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="a_alignment_errors_low" descr="A count of frames that are not an integral \;number of octets in length and do not pass the \;FCS check.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="a_octets_transmitted_ok_high" descr="A count of data and padding octets of frames \;that are successfully transmitted.\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="a_octets_transmitted_ok_low" descr="A count of data and padding octets of frames \;that are successfully transmitted.\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="a_octets_received_ok_high" descr="A count of data and padding octets in frames \;that are successfully received. This does not \;include octets in frames received with frame-\;too-long, FCS, length or alignment errors, or \;frames lost due to other MAC errors.\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="a_octets_received_ok_low" descr="A count of data and padding octets in frames \;that are successfully received. This does not \;include octets in frames received with frame-\;too-long, FCS, length or alignment errors, or \;frames lost due to other MAC errors.\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="a_multicast_frames_xmitted_ok_high" descr="A count of frames that are successfully trans\;mitted to a group destination address other \;than broadcast.\;\; \;\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="a_multicast_frames_xmitted_ok_low" descr="A count of frames that are successfully trans\;mitted to a group destination address other \;than broadcast.\;\; \;\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="a_broadcast_frames_xmitted_ok_high" descr="A count of the frames that were successfully \;transmitted to the broadcast address. Frames \;transmitted to multicast addresses are not \;broadcast frames and are excluded.\;\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="a_broadcast_frames_xmitted_ok_low" descr="A count of the frames that were successfully \;transmitted to the broadcast address. Frames \;transmitted to multicast addresses are not \;broadcast frames and are excluded.\;\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="a_multicast_frames_received_ok_high" descr="A count of frames that are successfully \;received and directed to an active nonbroad\;cast group address. This does not include \;frames received with frame-too-long, FCS, \;length or alignment errors, or frames lost due \;to internal MAC sublayer error. \;  \;\;\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="a_multicast_frames_received_ok_low" descr="A count of frames that are successfully \;received and directed to an active nonbroad\;cast group address. This does not include \;frames received with frame-too-long, FCS, \;length or alignment errors, or frames lost due \;to internal MAC sublayer error. \;  \;\;\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="a_broadcast_frames_received_ok_high" descr="A count of the frames that were successfully \;transmitted to the broadcast address. Frames \;transmitted to multicast addresses are not \;broadcast frames and are excluded. \;\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="a_broadcast_frames_received_ok_low" descr="A count of the frames that were successfully \;transmitted to the broadcast address. Frames \;transmitted to multicast addresses are not \;broadcast frames and are excluded. \;\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="a_in_range_length_errors_high" descr="A count of frames with a length/type field \;value between the minimum unpadded MAC \;client data size and the maximum allowed \;MAC client data size, inclusive, that does not \;match the number of MAC client data octets \;received. The counter also increments for \;frames whose length/type field value is less \;than the minimum allowed unpadded MAC cli\;ent data size and the number of MAC client \;data octets received is greater than the mini\;mum unpadded MAC client data size.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="a_in_range_length_errors_low" descr="A count of frames with a length/type field \;value between the minimum unpadded MAC \;client data size and the maximum allowed \;MAC client data size, inclusive, that does not \;match the number of MAC client data octets \;received. The counter also increments for \;frames whose length/type field value is less \;than the minimum allowed unpadded MAC cli\;ent data size and the number of MAC client \;data octets received is greater than the mini\;mum unpadded MAC client data size.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="a_out_of_range_length_field_high" descr="A count of frames with a length field value \;greater than the maximum allowed LLC data \;size. \;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="a_out_of_range_length_field_low" descr="A count of frames with a length field value \;greater than the maximum allowed LLC data \;size. \;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="a_frame_too_long_errors_high" descr="A count of frames received that exceed the \;maximum permitted frame size by IEEE 802.3 \;(MTU size).\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="a_frame_too_long_errors_low" descr="A count of frames received that exceed the \;maximum permitted frame size by IEEE 802.3 \;(MTU size).\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="a_symbol_error_during_carrier_high" descr="For full duplex operation at 1000 Mb/s, it is a \;count of the number of times the receiving \;media is non-idle (a carrier event) for a period \;of time equal to or greater than minFrameS\;ize, and during which there was at least one \;occurrence of an event that causes the PHY to \;indicate &quot;Data reception error&quot;.\;For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/\;s, it is a count of the number of times the \;receiving media is non-idle for a period of time \;equal to or greater than minFrameSize, and \;during which there was at least one occur\;rence of an event that causes the PHY to indi\;cate\;Error.\;\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="a_symbol_error_during_carrier_low" descr="For full duplex operation at 1000 Mb/s, it is a \;count of the number of times the receiving \;media is non-idle (a carrier event) for a period \;of time equal to or greater than minFrameS\;ize, and during which there was at least one \;occurrence of an event that causes the PHY to \;indicate &quot;Data reception error&quot;.\;For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/\;s, it is a count of the number of times the \;receiving media is non-idle for a period of time \;equal to or greater than minFrameSize, and \;during which there was at least one occur\;rence of an event that causes the PHY to indi\;cate\;Error.\;\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="a_mac_control_frames_transmitted_high" descr="A count of MAC Control frames passed to the \;MAC sublayer for transmission.\;\;" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="a_mac_control_frames_transmitted_low" descr="A count of MAC Control frames passed to the \;MAC sublayer for transmission.\;\;" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="a_mac_control_frames_received_high" descr="A count of MAC Control frames passed by the \;MAC sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="a_mac_control_frames_received_low" descr="A count of MAC Control frames passed by the \;MAC sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="a_unsupported_opcodes_received_high" descr="A count of MAC Control frames received that \;contain an opcode that is not supported by the \;device.\;\;" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="a_unsupported_opcodes_received_low" descr="A count of MAC Control frames received that \;contain an opcode that is not supported by the \;device.\;\;" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_received_high" descr="A count of MAC PAUSE frames passed by the \;MAC sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_received_low" descr="A count of MAC PAUSE frames passed by the \;MAC sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_transmitted_high" descr="A count of PAUSE frames passed to the MAC \;sublayer for transmission.\;\;" access="RO" offset="0x90.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_transmitted_low" descr="A count of PAUSE frames passed to the MAC \;sublayer for transmission.\;\;" access="RO" offset="0x94.0" size="0x4.0" />
</node>

<node name="eth_discard_cntrs_grp_ext" descr="" size="0xf8.0" >
	<field name="ingress_general_high" descr="Ingress general \;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ingress_general_low" descr="Ingress general \;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ingress_policy_engine_high" descr="Ingress policy engine discards" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ingress_policy_engine_low" descr="Ingress policy engine discards" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ingress_vlan_membership_high" descr="Ingress VLAN membership filter discards" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ingress_vlan_membership_low" descr="Ingress VLAN membership filter discards" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_high" descr="Ingress VLAN tag allowance (tagged, untagged and \;prio-tagged) filter discards" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_low" descr="Ingress VLAN tag allowance (tagged, untagged and \;prio-tagged) filter discards" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="egress_vlan_membership_high" descr="Egress VLAN membership filter discards" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="egress_vlan_membership_low" descr="Egress VLAN membership filter discards" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="loopback_filter_high" descr="Loop-back filter discards" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="loopback_filter_low" descr="Loop-back filter discards" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="egress_general_high" descr="Egress general discards\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="egress_general_low" descr="Egress general discards\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="egress_hoq_high" descr="Head-of-Queue time-out discards" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="egress_hoq_low" descr="Head-of-Queue time-out discards" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="port_isolation_high" descr="Port isolation filter discards\;[IInternal] Not supported due to HW bug." access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_isolation_low" descr="Port isolation filter discards\;[IInternal] Not supported due to HW bug." access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="egress_policy_engine_high" descr="Egress policy engine discards" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="egress_policy_engine_low" descr="Egress policy engine discards" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="ingress_tx_link_down_high" descr="Per ingress port count dropped packets due to \;egress link down" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="ingress_tx_link_down_low" descr="Per ingress port count dropped packets due to \;egress link down" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="egress_stp_filter_high" descr="Egress spanning tree filter" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="egress_stp_filter_low" descr="Egress spanning tree filter" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="egress_hoq_stall_high" descr="Number of sequential packets dropped, due to Head-\;Of-Queue Lifetime Limit, that causes the port to \;enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="egress_hoq_stall_low" descr="Number of sequential packets dropped, due to Head-\;Of-Queue Lifetime Limit, that causes the port to \;enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="egress_sll_high" descr="Number of packets dropped, because the Switch \;Lifetime Limit was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="egress_sll_low" descr="Number of packets dropped, because the Switch \;Lifetime Limit was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ingress_discard_all_high" descr="Number of packets dropped, because of any reason.\; Note: see description in the description area for lim\;itations of this counter.\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ingress_discard_all_low" descr="Number of packets dropped, because of any reason.\; Note: see description in the description area for lim\;itations of this counter.\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x7C.0" size="0x4.0" />
</node>

<node name="eth_extended_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="port_transmit_wait_high" descr="The time (in 4ns resolution) during which the port \;selected had data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="port_transmit_wait_low" descr="The time (in 4ns resolution) during which the port \;selected had data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_high" descr="A count of packets marked as ECN or potentially \;marked as ECN.\;ECN Counting enable/disable is configurable. \;Valid only for Spectrum family.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_low" descr="A count of packets marked as ECN or potentially \;marked as ECN.\;ECN Counting enable/disable is configurable. \;Valid only for Spectrum family.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_high" descr="The number of multicast packets dropped due to lack \;of egress buffer resources.\;Valid only for Spectrum.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_low" descr="The number of multicast packets dropped due to lack \;of egress buffer resources.\;Valid only for Spectrum.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="rx_ebp_high" descr="The number of received EBP packets.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="rx_ebp_low" descr="The number of received EBP packets.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="tx_ebp_high" descr="The number of transmitted EBP packets.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="tx_ebp_low" descr="The number of transmitted EBP packets.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_high" descr="The number of events where the port rx buffer has \;passed a fullness threshold \;\;Reserved for Switches." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_low" descr="The number of events where the port rx buffer has \;passed a fullness threshold \;\;Reserved for Switches." access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="rx_buffer_full_high" descr="The number of events where the port rx buffer has \;reached 100% fullness \;\;Reserved for Switches." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="rx_buffer_full_low" descr="The number of events where the port rx buffer has \;reached 100% fullness \;\;Reserved for Switches." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_high" descr="The number of roce packets with ICRC error\;\;Reserved for Switches." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_low" descr="The number of roce packets with ICRC error\;\;Reserved for Switches." access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_high" descr="The total number of packets (including bad packets) \;transmitted that were 64 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_low" descr="The total number of packets (including bad packets) \;transmitted that were 64 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 65 and 127 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 65 and 127 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 128 and 255 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 128 and 255 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 256 and 511 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 256 and 511 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 512 and 1023 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 512 and 1023 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 1024 and 1518 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 1024 and 1518 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 1519 and 2047 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 1519 and 2047 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 2048 and 4095 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 2048 and 4095 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 4096 and 8191 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 4096 and 8191 octets \;in length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x94.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad packets) \;transmitted that were between 8192 and 10239 \;octets in length (excluding framing bits but including \;FCS octets).transmitted\;" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_low" descr="The total number of packets (including bad packets) \;transmitted that were between 8192 and 10239 \;octets in length (excluding framing bits but including \;FCS octets).transmitted\;" access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="ece_marked_high" descr="A count of packets marked as ECE or potentially \;marked as ECE." access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="ece_marked_low" descr="A count of packets marked as ECE or potentially \;marked as ECE." access="RO" offset="0xA4.0" size="0x4.0" />
</node>

<node name="eth_oob_port_cntrs_ext" descr="" size="0xf8.0" >
	<field name="if_in_ucast_pkts_high" descr="The number of packets successfully received, which were \;not addressed to a multicast or broadcast MAC address.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_low" descr="The number of packets successfully received, which were \;not addressed to a multicast or broadcast MAC address.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="if_in_octets_high" descr="The total number of octets received, including framing char\;acters. Including MAC control frames.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="if_in_octets_low" descr="The total number of octets received, including framing char\;acters. Including MAC control frames.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="if_in_discards_high" descr="The number of inbound packets which were chosen to be \;discarded even though no errors had been detected to pre\;vent their being deliverable to a higher-layer protocol.\;\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="if_in_discards_low" descr="The number of inbound packets which were chosen to be \;discarded even though no errors had been detected to pre\;vent their being deliverable to a higher-layer protocol.\;\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="if_in_errors_high" descr="The number of inbound packets that contained errors pre\;venting them from being deliverable to a higher-layer proto\;col. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="if_in_errors_low" descr="The number of inbound packets that contained errors pre\;venting them from being deliverable to a higher-layer proto\;col. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_high" descr="e total number of packets received that had a length \;(excluding framing bits, but including FCS octets) of \;between 64 and MTU octets, inclusive, but had either a bad \;frame check sequence (FCS) with an integral number of \;octets (FCS error) or a bad FCS with a non-integral number \;of octets (alignment error).\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_low" descr="e total number of packets received that had a length \;(excluding framing bits, but including FCS octets) of \;between 64 and MTU octets, inclusive, but had either a bad \;frame check sequence (FCS) with an integral number of \;octets (FCS error) or a bad FCS with a non-integral number \;of octets (alignment error).\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_high" descr="The total number of packets received that were less than 64 \;octets long (excluding framing bits, but including FCS \;octets) and were otherwise well formed.\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_low" descr="The total number of packets received that were less than 64 \;octets long (excluding framing bits, but including FCS \;octets) and were otherwise well formed.\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_high" descr="The total number of packets received that were longer than \;MTU octets (excluding framing bits, but including FCS \;octets) but were otherwise well formed.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_low" descr="The total number of packets received that were longer than \;MTU octets (excluding framing bits, but including FCS \;octets) but were otherwise well formed.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_high" descr="he number of times the receiving media is non-idle (a car\;rier event) for a period of time equal to or greater than min\;FrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate \;&quot;Receive Error&quot;.\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_low" descr="he number of times the receiving media is non-idle (a car\;rier event) for a period of time equal to or greater than min\;FrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate \;&quot;Receive Error&quot;.\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="dot3in_pause_frames_high" descr="A count of MAC Control frames received with an opcode \;indicating the PAUSE operation.\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="dot3in_pause_frames_low" descr="A count of MAC Control frames received with an opcode \;indicating the PAUSE operation.\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_high" descr="A count of MAC Control frames received that contain an \;opcode that is not supported.\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_low" descr="A count of MAC Control frames received that contain an \;opcode that is not supported.\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_high" descr="The total number of packets that higher-level protocols \;requested be transmitted and were not addressed to a mul\;ticast or broadcast MAC address, including those that were \;discarded or not sent.\;\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_low" descr="The total number of packets that higher-level protocols \;requested be transmitted and were not addressed to a mul\;ticast or broadcast MAC address, including those that were \;discarded or not sent.\;\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="if_out_octets_high" descr="The total number of octets transmitted out of the interface, \;including framing characters.\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="if_out_octets_low" descr="The total number of octets transmitted out of the interface, \;including framing characters.\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="dot3out_pause_frames_high" descr="A count of MAC Control frames transmitted with an opcode \;indicating the PAUSE operation.\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="dot3out_pause_frames_low" descr="A count of MAC Control frames transmitted with an opcode \;indicating the PAUSE operation.\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="if_out_errors_high" descr="The number of outbound packets that could not be trans\;mitted because of errors.\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="if_out_errors_low" descr="The number of outbound packets that could not be trans\;mitted because of errors.\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="phy_time_since_last_clear_high" descr="The time passed since the last phy counters clear event in \;msec." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="phy_time_since_last_clear_low" descr="The time passed since the last phy counters clear event in \;msec." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="phy_received_bits_high" descr="This counter provides information on the total amount of \;traffic (bits) received." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="phy_received_bits_low" descr="This counter provides information on the total amount of \;traffic (bits) received." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="phy_symbol_errors_high" descr="This counter provides information on error bits." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="phy_symbol_errors_low" descr="This counter provides information on error bits." access="RO" offset="0x84.0" size="0x4.0" />
</node>

<node name="eth_per_prio_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="rx_octets_high" descr="The total number of octets received, including framing char\;acters.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="rx_octets_low" descr="The total number of octets received, including framing char\;acters.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="rx_frames_high" descr="The total number of packets received for this priority \;(including control frames).\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="rx_frames_low" descr="The total number of packets received for this priority \;(including control frames).\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_octets_high" descr="The total number of octets transmitted, including framing \;characters.\;\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="tx_octets_low" descr="The total number of octets transmitted, including framing \;characters.\;\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="tx_frames_high" descr="The total number of packets transmitted.\;\;\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="tx_frames_low" descr="The total number of packets transmitted.\;\;\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="rx_pause_high" descr="The total number of PAUSE frames received from the far-\;end port.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="rx_pause_low" descr="The total number of PAUSE frames received from the far-\;end port.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="rx_pause_duration_high" descr="The total time in microseconds that transmission of packets \;to the far-end port have been paused.\;\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="rx_pause_duration_low" descr="The total time in microseconds that transmission of packets \;to the far-end port have been paused.\;\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="tx_pause_high" descr="The total number of PAUSE or PFC frames sent to the far-\;end port.\;\;\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_pause_low" descr="The total number of PAUSE or PFC frames sent to the far-\;end port.\;\;\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_pause_duration_high" descr="The total time in microseconds that the far-end port have \;been requested to pause.\;\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_pause_duration_low" descr="The total time in microseconds that the far-end port have \;been requested to pause.\;\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="rx_pause_transition_high" descr="Counts the number of transitions from Xoff to Xon.\;\;" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="rx_pause_transition_low" descr="Counts the number of transitions from Xoff to Xon.\;\;" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rx_discards_high" descr="The number of inbound packets which were chosen to be \;discarded even though no errors had been detected to pre\;vent their being deliverable to a higher-layer protocol.\;\;\;\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rx_discards_low" descr="The number of inbound packets which were chosen to be \;discarded even though no errors had been detected to pre\;vent their being deliverable to a higher-layer protocol.\;\;\;\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_high" descr="The number of times the device detected a stalled state for a \;period longer than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all \;events on all priorities (including global pause)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_low" descr="The number of times the device detected a stalled state for a \;period longer than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all \;events on all priorities (including global pause)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_high" descr="The number of times the device detected a stalled state for a \;period longer than device_stall_critical_watermark\;The counter is presented in priority 0, but is a sum of all \;events on all priorities (including global pause).\;" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_low" descr="The number of times the device detected a stalled state for a \;period longer than device_stall_critical_watermark\;The counter is presented in priority 0, but is a sum of all \;events on all priorities (including global pause).\;" access="RO" offset="0x8C.0" size="0x4.0" />
</node>

<node name="eth_per_receive_buffer_grp_ext" descr="" size="0xf8.0" >
	<field name="rx_no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of \;ingress shared buffer resources. \;Not supported by Spectrum.\;Supported by Spectrum-2." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="rx_no_buffer_discard_uc_low" descr="The number of unicast packets dropped due to lack of \;ingress shared buffer resources. \;Not supported by Spectrum.\;Supported by Spectrum-2." access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_cong_layout_ext" descr="" size="0xf8.0" >
	<field name="wred_discard_high" descr="The number of packet that are dropped by the Weighted \;Random Early Detection (WRED) function.\;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt \;eth per tc cong group supported&quot; is set." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="wred_discard_low" descr="The number of packet that are dropped by the Weighted \;Random Early Detection (WRED) function.\;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt \;eth per tc cong group supported&quot; is set." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_tc_high" descr="A count of packets marked as ECN or potentially \;marked as ECN.\;ECN Counting enable/disable is configurable. \;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt \;eth per tc cong group supported&quot; is set.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_tc_low" descr="A count of packets marked as ECN or potentially \;marked as ECN.\;ECN Counting enable/disable is configurable. \;For HCAs - valid when PCAM.feature_cap_mask &quot;ppcnt \;eth per tc cong group supported&quot; is set.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_layout_ext" descr="" size="0xf8.0" >
	<field name="transmit_queue_high" descr="Contains the transmit queue depth in bytes on traffic \;class selected by traffic_class of the port selected by \;local_port.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="transmit_queue_low" descr="Contains the transmit queue depth in bytes on traffic \;class selected by traffic_class of the port selected by \;local_port.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of \;shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_low" descr="The number of unicast packets dropped due to lack of \;shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="ets_ext" descr="" size="0x8.0" >
	<field name="bw_allocation" descr="For NICs:\;The weight assigned to the TClass within its TClass Group.  \;The percentage of bandwidth guaranteed is calculated by \;the TClass weight divided by the sum of all weights of the \;TClasses in the group.\;Valid values are 1-100." access="RW" offset="0x0.0" size="0x0.7" />
	<field name="group" descr="TClass Group assigned to a TClass.\;Range 0..7\;" access="RW" offset="0x0.16" size="0x0.4" />
	<field name="r" descr="Rate limit update. Enables update of the rate limiter (with \;the max_bw_units, max_bw_value). If this bit is cleared, the \;rate limiter value will not change." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="b" descr="Bandwidth allocation update. Enables update of the ETS \;bandwidth allocation (with the bw_allocation). If this bit is \;cleared, the bandwidth allocation value will not change." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="g" descr="Group update. Enables update of the group assigned to the \;TClass. If this bit is cleared, the group value will not change." access="WO" offset="0x0.31" size="0x0.1" />
	<field name="max_bw_value" descr="The maximal bandwidth allowed for the use TClass\;Units according to max_bw_units\;Reserved when max_bw_units = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_bw_units" descr="Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps \;units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response returns value in units that allow the \;most accurate number, not in the units configured using \;Set()." access="RW" enum="DISABLED=0x0,HUNDREDS_MBPS=0x3,GBPS=0x4" offset="0x4.16" size="0x0.4" />
</node>

<node name="ets_global_ext" descr="" size="0x8.0" >
	<field name="r" descr="Rate limit update. Enables update of the rate limiter (with \;the max_bw_units, max_bw_value). If this bit is cleared, the \;rate limiter value will not change." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="max_bw_value" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps \;units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow \;the most accurate number, not in the units configured using \;Set()." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_bw_units" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps \;units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow \;the most accurate number, not in the units configured using \;Set()." access="RW" enum="DISABLED=0x0,HUNDREDS_MBPS=0x3,GBPS=0x4" offset="0x4.16" size="0x0.4" />
</node>

<node name="fore_ext" descr="" size="0xc.0" >
	<field name="fan_under_limit" descr="Fan speed is below the low limit defined in MFSL register. \;Each bit relates to a single tachometer and indicates the spe\;cific tachometer reading is below the threshold." access="RO" offset="0x0.16" size="0x0.10" />
	<field name="fan_under_limit_msb" descr="6 MSB indexes of the tachometers. \;Fan speed is below the low limit defined in MFSL register. \;Each bit relates to a single tachometer and indicates the spe\;cific tachometer reading is below the threshold." access="RO" offset="0x0.26" size="0x0.6" />
	<field name="fan_over_limit" descr="Fan speed is above the high limit defined in MFSL register. \;Each bit relates to a single tachometer and indicates the spe\;cific tachometer reading is above the threshold." access="RO" offset="0x4.16" size="0x0.10" />
	<field name="fan_over_limit_msb" descr="6 MSB indexes of the tachometers. \;Fan speed is above the high limit defined in MFSL register. \;Each bit relates to a single tachometer and indicates the spe\;cific tachometer reading is above the threshold." access="RO" offset="0x4.26" size="0x0.6" />
</node>

<node name="fp_sl_map_arg_ext" descr="" size="0x4.0" >
	<field name="port" descr="0x0 - reserved\;0x1-0x2 - port number\;0x3-0xff - reserved" access="RW" offset="0x0.0" size="0x0.8" />
</node>

<node name="hca_cap_encap_ext" descr="" size="0x60.0" >
	<field name="cmd_data_offset" descr="Defines the start offset of the data (cmd_data_value \;and cmd_data_mask) that is needed to be set/que\;ried by QUERY_HCA_CAP and SET_HCA_CAP) in \;granularity of 4Bytes.\;The offset starts from the beginning of the command. \;i.e. includes the command header." access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="cmd_data_mask" descr="For set commands: Bitmask that indicates which bits \;in cmd_data_value should be written.\;An unset bit in this mask will leave the matching bit \;in the cmd_data_value unchanged. \;For query commands (QUERY_HCA_CAP): must be 0" access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="cmd_data_value" descr="For set commands: The value to apply starting from \;cmd_data_offset (in conjunction with the cmd_\;data_mask defined above). Set by the user.\;For query commands (QUERY_HCA_CAP): User \;should set to 0; will hold the value the device \;retrieved." access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="cmd_header" descr="Icommand_header_in and command_header_out (16 \;bytes) of QUERY_HCA_CAP or SET_HCA_CAP.\;command_header_in is set by user when issuing the \;register.\;command_header_out is returned by the device after \;executing the register." access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
</node>

<node name="import_kek_handle_ext" descr="" size="0x300.0" >
	<field name="crypto_login_object" descr="Information required to identify an officer.\;modify_field_select is reserved.\;Needed for all operations." subnode="crypto_login_obj_ext" access="RW" offset="0x0.0" size="0x100.0" />
	<field name="import_kek_object" descr="The import_KEK to add.\;For add, this is input (WO) of new KEK info.\;For query, this output (RO) with limited info of KEK.\;modify_field_select is reserved.\;For delete this field is reserved." subnode="import_kek_object_ext" access="RW" offset="0x100.0" size="0x100.0" />
	<field name="import_kek_id" descr="For query/delete ops, this is input (WO).\;For add, input to this field is ignored, output is the \;selected\;ID." access="INDEX" offset="0x200.0" size="0x0.24" />
	<field name="write_operation" descr="0x1: ADD_OPERATION\;0x2: DELETE_OPERATION" access="WO" enum="ADD_OPERATION=0x1,DELETE_OPERATION=0x2" offset="0x200.24" size="0x0.4" />
</node>

<node name="import_kek_object_ext" descr="" size="0x100.0" >
	<field name="modify_field_select" descr="Field select indicates in QUERY which fields are mod\;ifiable (1 means modifiable), and in MODIFY which \;fields to modify." subnode="uint64" offset="0x0.0" size="0x8.0" />
	<field name="key_size" descr="Key size\;0x0: SIZE_128\;0x1: SIZE_256" enum="SIZE_128=0x0,SIZE_256=0x1" offset="0x8.8" size="0x0.4" />
	<field name="state" descr="Key state, Valid for Query command only.\;0x0: READY - the key state when first created\;0x1: ERROR - key unusable, need to destroy and re-\;create this key" enum="READY=0x0,ERROR=0x1" offset="0x8.24" size="0x0.8" />
	<field name="key" descr="Actual size and layout of this field described in \;Table 347, &quot;IMPORT_KEK Field Construction \;Summary,&quot; on page 566 below. Note that the layout \;explained in following table should be used from the \;MSBs and on." high_bound="31" low_bound="0" offset="0x40.0" size="0x80.0" />
</node>

<node name="lane_2_module_mapping_ext" descr="" size="0x4.0" >
	<field name="module" descr="Module number" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA \;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="tx_lane" descr="TX lane. \;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is cleared, this field is used for RX as well." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="rx_lane" descr="RX lane.\;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is cleared, this field is ignored and RX lane is \;equal to TX lane." access="RW" offset="0x0.24" size="0x0.4" />
</node>

<node name="link_level_retrans_cntr_grp_data_ext" descr="" size="0xf8.0" >
	<field name="llr_rx_cells_high" descr="The total number of cells received (including bad cells)." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="llr_rx_cells_low" descr="The total number of cells received (including bad cells)." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="llr_rx_error_high" descr="The total number of bad cells received (including CRC \;error).\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="llr_rx_error_low" descr="The total number of bad cells received (including CRC \;error).\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="llr_rx_crc_error_high" descr="The total number of cells received with CRC error.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="llr_rx_crc_error_low" descr="The total number of cells received with CRC error.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="llr_tx_cells_high" descr="The total number of cells transmitted (including retrans\;mitted cells)." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="llr_tx_cells_low" descr="The total number of cells transmitted (including retrans\;mitted cells)." access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="llr_tx_ret_cells_high" descr="The total number of cells retransmitted." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="llr_tx_ret_cells_low" descr="The total number of cells retransmitted." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="llr_tx_ret_events_high" descr="The total number of retransmission events." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="llr_tx_ret_events_low" descr="The total number of retransmission events." access="RO" offset="0x2C.0" size="0x4.0" />
</node>

<node name="mbct_ext" descr="" size="0x420.0" >
	<field name="slot_index" descr="Slot index. \;0: Reserved." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="data_size" descr="actual data field size in bytes for the current data transfer" access="WO" offset="0x4.0" size="0x0.11" />
	<field name="ini_status" descr="ini status\;0: Empty_not_valid\;1: Valid - (Magic Pattern applied)\;2: Ready_to_use\;3: In_use\;Other values are Reserved" access="RO" enum="Empty_not_valid=0x0,Valid=0x1,Ready_to_use=0x2,In_use=0x3" offset="0x4.29" size="0x0.3" />
	<field name="oee" descr="Opcode Event Enable. When set to &apos;1&apos;, an event will be sent \;once the opcode was executed and the fsm_state has \;changed. This bit will be cleared once the event was sent." access="WO" offset="0x8.25" size="0x0.1" />
	<field name="last" descr="Indicates that the current data field is the last chunk of the \;INI." access="WO" offset="0x8.26" size="0x0.1" />
	<field name="op" descr="When the register is used in a &apos;Query&apos; mode, only option 7 \;(Query Status) is legal.\;0: Reserved\;1: Erase_INI_image\;2: Data_transfer - (download)\;3: Activate\;4: Deactivate\;5: Abort\;6: Clear_Errors\;7: Query_Status\;Other values are Reserved" access="WO" enum="Reserved=0x0,Erase_INI_image=0x1,Data_transfer=0x2,Activate=0x3,Deactivate=0x4,Abort=0x5,Clear_Errors=0x6,Query_Status=0x7" offset="0x8.28" size="0x0.4" />
	<field name="fsm_state" descr="0: Idle\;1: Data_transfer - (download)\;2: Magic_Pattern_Valid\;3: Ready\;4: Erase\;5: INI_in_use\;6: Error\;Other values are Reserved" access="RO" enum="Idle=0x0,Data_transfer=0x1,Magic_Pattern_Valid=0x2,Ready=0x3,Erase=0x4,INI_in_use=0x5,Error=0x6" offset="0xC.16" size="0x0.4" />
	<field name="status" descr="Status\;0: NA\;1: Busy\;2: Partial - partial data transfer completed successfully and \;ready for next data transfer\;3: Last_data - last data transfer completed, applying magic \;pattern. \;4: Erase_is_complete\;5: Error_Attempted_Erase_INI_in_use - Trying to erase INI \;while it being used.\;6: Transfer_failure - (bad data received or write error)\;7: Erase_failure\;8: INI_error\;9: Activation_of_INI_failed\;10: Deactivation_of_INI_failed\;11: Error_Illegal_operation\;Other values are Reserved" access="RO" enum="NA=0x0,Busy=0x1,Partial=0x2,Last_data=0x3,Erase_is_complete=0x4,Error_Attempted_Erase_INI_in_use=0x5,Transfer_failure=0x6,Erase_failure=0x7,INI_error=0x8,Activation_of_INI_failed=0x9,Deactivation_of_INI_failed=0xa,Error_Illegal_operation=0xb" offset="0xC.24" size="0x0.5" />
	<field name="data" descr="Up to 1KB of data." access="WO" high_bound="255" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="mcam_reg_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First_128_REG_ID - Register IDs 0x9001 - 0x907F)\;1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask \;represent register ID 0x9080 while bit 127 represents register ID \;0x90FF).\;2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask \;represent register ID 0x9100 while bit 127 represents register ID \;0x917F)." access="INDEX" enum="First_128_REG_ID=0x0,Register_IDs_0x9080=0x1,Register_IDs_0x9100=0x2" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="mng_access_reg_cap_mask" descr="Supported management&apos;s access register bitmaks.Based on \;access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: MFCR_0x9001\;Bit 2: MFSC_0x9002\;Bit 3: MFSM_0x9003\;Bit 4: MFSL_0x9004\;Bit 58: MGCR_0x903A\;Bit 73: MPPF_0x9049\;Bit 127: MCAP_0x907F" access="RO" enum="MFCR_0x9001=0x2,MFSC_0x9002=0x4,MFSM_0x9003=0x8,MFSL_0x9004=0x10,MGCR_0x903A=0x4000000,MPPF_0x9049=0x200,MCAP_0x907F=0x80000000" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="mng_feature_cap_mask" descr="Supported port&apos;s enhanced features.Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bit 0: MPCNT counter group- PCIE performance counters supported\;Bit 1: mtpps_fs - If set, field_select field in MTPPS register is supported.\;Bit 2: mtpps_enhanced_out_periodic_adjustment - If set, enhanced_out_periodic_ad\;justment field in MTPPS register is supported.\;Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter in MPCNT regis\;ter is supported.\;Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads, out\;bound_stalled_writes, outbound_stalled_reads_events and out\;bound_stalled_writes_events counters in MPCNT are supported.\;Bit 5: Management pass through is supported\;Bit 6: sensor_map - If set, sensor_map is supported in MTCAP register.\;Bit 7 - if set, module_status bit 8 (Module Low Power) in MCION register is supported. \;Bit 8 - beacon_capability_disable - If set, beacon feature, as appears in MLCR register, \;in not supported by the device. \;Bit 9 - dynamic_tx_overflow - If set, tx_overflow_sense field is supported in MPEGC reg\;ister. \;Bit 10 - mark_tx_action_cqe is supported if set to &apos;1&apos;.\;Bit 11 - mark_tx_action_cnp is supported if set to &apos;1&apos;.\;Bit 12 - dev_info is supported in  register is set to &apos;1&apos;.\;Bit 13 - sensor_count field is 12bit size in MTMP and MTBR\;Bit 14 - cs_tokens_supported is supported \;Bit 15 - debug_fw_tokens_supported is \;Bit 16 - long_keys is supported \;Bit 17 - pwr_status and pci_power are supported in MPEIN\;Bit 18 - If set, accessing through device_type and device_index is supported in MCC, \;MCQI and MCQS\;Bit 19 - pcie_sync_for_fw_update_supported is set to &apos;1&apos;\;Bit 20 - ptpCyc2Realtime_modify - If set, the cycle to realtime translation offload is sup\;ported\;Bit 21 - If set to &apos;1&apos;, reset_state in MFRL is supported\;Bit 22 - If set to &apos;1&apos;, link_peer_max_speed is supported in MPEIN Register\;Bit 23 - If set to &apos;1&apos;, slot_index field is supported in: MCIA, MCAS, MCION, MQSP, \;MTCAP, MTECR, MTMP, MTEWE, MTBR, MVCAP, MVCR, MGPIR, MDDT, MDCR.\;Bit 24 - If set, transceiver burn flow is supported in MCC, MCQI and MCQS.\;\;Bit 26: If set, progress field is supported in MCQS\;\;Bit 28: If set, number_of_slots field is supported in MGPIR.\;Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.\;Bit 30: If set, my_pf_number is supported in MPPF.\;Bit 31: If set, sdee is supported in MTMP\;Bit 32: If set, npps_period is supported in MTPPS.\;Bit 33: If set, out_pulse_duration_ns is supported in MTPPS.\;Bit 34: If set, MCIA supports 32 D-words. Otherwise, 12 D-words.\;Bit 35: If set, MGIR.hw_info.technology is supported. \;\;Bit 37: If set, lp_msb is supported for MLCR, MPIR \;\;Bit 39: If set, MRCS and RMDT tokens are supported in MCQS\;Bit 40: If set, &apos;encryption&apos; field in MGIR is supported\;\;Bit 42: If set, operation 5, ts_correction_admin_status and ts_correction_oper_status \;are supported in MTUTC.\;Bit 43: If set, MFCR supports tacho_active_msb field\;Bit 44: If set, FORE supports fan_under_limit_msb and fan_over_limit_msb fields" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="mcc_reg_ext" descr="" size="0x20.0" >
	<field name="instruction" descr="Command to be executed by the FSM\;0x1: LOCK_UPDATE_HANDLE\;0x2: RELEASE_UPDATE_HANDLE \;0x3: UPDATE_COMPONENT\;0x4: VERIFY_COMPONENT\;0x5: ACTIVATE_COMPONENET \;0x6: ACTIVATE\;0x7: READ_COMPONENT\;0x8: CANCEL\;0x9: CHECK_UPDATE_HANDLE\;0xA: FORCE_HANDLE_RELEASE\;0xB: READ_PENDING_COMPONENT\;0xC: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved. Applicable for write opera\;tion only." access="RW" enum="LOCK_UPDATE_HANDLE=0x1,RELEASE_UPDATE_HANDLE=0x2,UPDATE_COMPONENT=0x3,VERIFY_COMPONENT=0x4,ACTIVATE_COMPONENET=0x5,ACTIVATE=0x6,READ_COMPONENT=0x7,CANCEL=0x8,CHECK_UPDATE_HANDLE=0x9,FORCE_HANDLE_RELEASE=0xa,READ_PENDING_COMPONENT=0xb,DOWNSRTEAM_DEVICE_TRANSFER=0xc" offset="0x0.0" size="0x0.8" />
	<field name="activation_delay_sec" descr="This is a configuration that delays the activation of the \;component in seconds. Relevant only for activate com\;mand.\;This configuration is volatile." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="time_elapsed_since_last_cmd" descr="The number of seconds elapsed since the update_han\;dle owner last issued a command. The time saturates \;at 0xFFF." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="component_index" descr="Index of the accessed component. Valid for \;UPDATE_COMPONENT, ACTIVATE_COMPONENET, \;READ_COMPONENT and READ_PENDING_COMPO\;NENT instructions. Otherwise, this field is reserved." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="update_handle" descr="Token representing the current flow executed by the \;FSM.\;See Section 10.2.1, &quot;Component Update State&quot;, on \;page 806." access="RW" offset="0x8.0" size="0x0.24" />
	<field name="auto_update" descr="Auto-update to all matching downstream devices is \;requested." access="WO" offset="0x8.31" size="0x0.1" />
	<field name="control_state" descr="Current Update FSM state, See Section 10.3.8, &quot;FSM \;States&quot;, on page 810\;0x0: IDLE\;0x1: LOCKED\;0x2: INITIALIZE\;0x3: DOWNLOAD\;0x4: VERIFY\;0x5: APPLY\;0x6: ACTIVATE\;0x7: UPLOAD\;0x8: UPLOAD_PENDING\;0x9: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved" access="RO" enum="IDLE=0x0,LOCKED=0x1,INITIALIZE=0x2,DOWNLOAD=0x3,VERIFY=0x4,APPLY=0x5,ACTIVATE=0x6,UPLOAD=0x7,UPLOAD_PENDING=0x8,DOWNSRTEAM_DEVICE_TRANSFER=0x9" offset="0xC.0" size="0x0.4" />
	<field name="error_code" descr="Indicates the successful completion of the instruction, \;or the reason it failed. See Section 10.3.7, &quot;Error \;Handling&quot;, on page 809\;0x0: OK\;0x1: ERROR\;0x2: REJECTED_DIGEST_ERR\;0x3: REJECTED_NOT_APPLICABLE\;0x4: REJECTED_UNKNOWN_KEY\;0x5: REJECTED_AUTH_FAILED\;0x6: REJECTED_UNSIGNED\;0x7: REJECTED_KEY_NOT_APPLICABLE\;0x8: REJECTED_BAD_FORMAT\;0x9: BLOCKED_PENDING_RESET\;0xA: REJECTED_NOT_A_SECURED_FW\;0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED\;0xC: REJECTED_NO_DEBUG_TOKEN\;0xD: REJECTED_VERSION_NUM_MISMATCH\;0xE: REJECTED_USER_TIMESTAMP_MISMATCH\;0xF: REJECTED_FORBIDDEN_VERSION\;0x10: FLASH_ERASE_ERROR\;0x11: REJECTED_REBURN_RUNNING_AND_RETRY\;0x12: REJECTED_LINKX_TYPE_NOT_SUPPORTED\;0x13: REJECTED_HOST_STORAGE_IN_USE\;0x14: REJECTED_LINKX_TRANSFER (see module \;index in rejected_device_index)\;0x15: REJECTED_LINKX_ACTIVATE (see module index \;in rejected_device_index)\;0x16: REJECTED_TOKEN_ALREADY_APPLIED\;Other values should be treated as an unknown error." access="RO" offset="0xC.8" size="0x0.8" />
	<field name="control_progress" descr="Indicates the estimated progress status of the current \;operation executed by the FSM. Valid values are 0..100.\;101 indicates that progress reporting is not supported \;for this update state." access="RO" offset="0xC.16" size="0x0.7" />
	<field name="handle_owner_host_id" descr="For handle_owner_type BMC, command-interface and \;ICMD, indicates the identifier of the host of the handle \;owner.\;Otherwise reserved" access="RO" offset="0xC.24" size="0x0.4" />
	<field name="handle_owner_type" descr="Type of entity holding the update handle:\;0x0: unspecified\;0x1: Chassis BMC\;0x2: MAD\;0x3: BMC\;0x4: command interface\;0x5: ICMD \;Other values are reserved." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="component_size" descr="Component size in bytes. \;Valid for UPDATE_COMPONENT instruction. Specifying \;the size may shorten the update time.\;Value 0x0 means that size is unspecified." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" enum="Switch_or_NIC=0x0,Gearbox=0x1" offset="0x14.0" size="0x0.8" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index \;starting at index 1. Index 0 indicates the host device." access="INDEX" offset="0x14.16" size="0x0.12" />
	<field name="device_index_size" descr="In multiple downstream devices action, the action will \;be executed starting on device_index and ending on \;device_index + device_index_size - 1." access="RW" offset="0x18.0" size="0x0.12" />
	<field name="rejected_device_index" descr="The device index that the action has been rejected to." access="RO" offset="0x18.16" size="0x0.12" />
</node>

<node name="mcda_reg_ext" descr="" size="0x90.0" >
	<field name="update_handle" descr="Update handle registered when the FSM was activated." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="offset" descr="Offset of accessed address relative to component start. \;Accesses must be in accordance to log_mcda_word_\;size in Table 1854, &quot;MCQI CAPABILITIES Info Lay\;out,&quot; on page 2103" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="size" descr="Size of the data accessed, given in bytes" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="data" descr="Data block accessed" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
</node>

<node name="mcdd_reg_ext" descr="" size="0x20.0" >
	<field name="update_handle" descr="Update handle registered when the FSM was activated." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="offset" descr="Offset of accessed address relative to component start." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="size" descr="Size of the data accessed, given in bytes" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="data_page_phys_addr_msb" descr="Physical address of the FW component data page." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="data_page_phys_addr_lsb" descr="Physical address of the FW component data page." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="mailbox_page_phys_addr_msb" descr="Physical address of the mailbox page." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="mailbox_page_phys_addr_lsb" descr="Physical address of the mailbox page." access="RW" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mcia_ext" descr="" size="0x90.0" >
	<field name="status" descr="Module Status\;0h - GOOD\;1h - NO_EEPROM_MODULE. No response from module&apos;s \;EPROM.\;2h - MODULE_NOT_SUPPORTED. Module type not sup\;ported by the device. \;3h - MODULE_NOT_CONNECTED. No module present indi\;cation. \;9h - I2C_ERROR. Error occurred while trying to access the \;module&apos;s EPROM using I2C.\;10h - MODULE_DISABLED - module is disabled \;[Internal] 11h - Page Access Failed - page not supported or \;trying to access a protected page with bad password." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="l" descr="Lock bit. Setting this bit will lock the access to the specific \;cable.\;Used for updating a full page in a cable EPROM. Any access \;other then subsequence writes will fail while the port is \;locked." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="device_address" descr="Device address" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="page_number" descr="Page number" access="INDEX" offset="0x4.16" size="0x0.8" />
	<field name="i2c_device_address" descr="I2C device address" access="INDEX" offset="0x4.24" size="0x0.8" />
	<field name="size" descr="Number of bytes to read/write (up to 128 bytes)" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="bank_number" descr="Bank number" access="INDEX" offset="0x8.16" size="0x0.8" />
	<field name="dword" descr="Bytes to read/write" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
</node>

<node name="mcion_ext" descr="" size="0xc.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_status_bits" descr="Module IO status, as defined by SFF:\;Bit 0 - Present\;Bit 1 - RX_LOS\;Bit 2 - TX_Fault\;\;" access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="mcpp_reg_ext" descr="" size="0x10.0" >
	<field name="enoc" descr="Enable Over Current Events\;Enable power policer according to indication of Over Cur\;rent which is provided by device interface (e.g. OC_WARN \;pin in Spectrum)\;0 - disable \;1 - enable (default)" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="ent" descr="Enable Temperature Events\;Enable power policer according to high temperature\;0 - disable (default)\;1 - enable" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="hysteresis_temperature" descr="Below this temperature the Temperature Event is cleared. \;Units are Celsius\;Default 95\;hysteresis_temperature must be lower or equal to warn\;ing_temperature\;Reserved when ent = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="warning_temperature" descr="Above this temperature the Temperature Event is set. Units \;are Celsius\;Default 105\;Reserved when ent = 0" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="wsoc" descr="Warning State due to Over Current Event:\;0 - Yellow_State\;1 - Red_State (default)" access="RW" offset="0x8.30" size="0x0.1" />
	<field name="wst" descr="Warning State due to Temperature Event:\;0 - Yellow_State (default)\;1 - Red_State" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="yellow_state_rate" descr="Port rate at Yellow_State. Units are percentage from \;Green_State port rate\;Default 50" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="red_state_rate" descr="Port rate at Red_State. Units are percentage from \;Green_State port rate\;red_state_rate must be lower or equal to yellow_state_rate\;Default 0" access="RW" offset="0xC.16" size="0x0.8" />
</node>

<node name="mcqi_activation_method_ext" descr="" size="0x7c.0" >
	<field name="all_hosts_sync" descr="When set, the operation needed to move the compo\;nent form ACTIVE_PENDING_RESET to ACTIVE should \;happen simultaneously on all hosts." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="auto_activate" descr="This component will be ACTIVE or ACTIVE_PEND\;ING_RESET after the APPLY state." access="RO" offset="0x0.1" size="0x0.1" />
	<field name="pending_fw_reset" descr="This component goes to ACTIVE_PENDING_RESET \;after activation.\;A FW reset will move it to ACTIVE state." access="RO" offset="0x0.2" size="0x0.1" />
	<field name="pending_server_reboot" descr="This component goes to ACTIVE_PENDING_RESET \;state after activation.\;A server reset (PCIe PERST#), will move it ACTIVE \;state." access="RO" offset="0x0.3" size="0x0.1" />
	<field name="pending_server_dc_power_cycle" descr="This component goes to ACTIVE_PENDING_RESET \;state after activation.\;DC power cycle (power cycle of PCI power rails), will \;move it ACTIVE state." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="pending_server_ac_power_cycle" descr="This component goes to ACTIVE_PENDING_RESET \;state after activation.\;AC power cycle (power cycle for both PCI power rails \;and AUX power), will move it ACTIVE state." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="self_activation" descr="When set, the component supports self activation. For \;cables, please refer to activation_type in LINKX_PROP\;ERTIES data for more details." access="RO" offset="0x0.6" size="0x0.1" />
</node>

<node name="mcqi_cap_ext" descr="" size="0x7c.0" >
	<field name="supported_info_bitmask" descr="Bitmask indicating which info_type(s) are supported \;for this component. Set bit indicates the property set is \;supported\;bit 1: VERSION\;bit 5: ACTIVATION_METHOD\;Other bits are reserved. CAPABILITIES set is always \;supported." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="component_size" descr="The size of the component given in bytes. Value 0x0 \;indicates that the size in unknown.\;For some components, size may only be available in \;the READ_COMPONENT state." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="max_component_size" descr="Maximum size for this component, given in bytes." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="mcda_max_write_size" descr="Maximal write size for MCDA" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="log_mcda_word_size" descr="Log 2 of the access word size in bytes.\;Read and write access must be aligned to the word \;size. Write access must be done for an integer number \;of words." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="match_base_guid_mac" descr="The device only accepts updates for this component \;that explicitly lists its base MAC and/or base GUID" access="RW" offset="0x10.26" size="0x0.1" />
	<field name="check_user_timestamp" descr="A user defined timestamp (MVTS) is active for this \;component." access="RW" offset="0x10.27" size="0x0.1" />
	<field name="match_psid" descr="PSID is validated for this component update." access="RW" offset="0x10.28" size="0x0.1" />
	<field name="match_chip_id" descr="Chip ID (device_hw_revision) is validated for this com\;ponent update." access="RW" offset="0x10.29" size="0x0.1" />
	<field name="rd_en" descr="When set, this components may be read, see \;Section 10.3.4, &quot;Read Flow&quot;, on page 809." access="RO" offset="0x10.31" size="0x0.1" />
</node>

<node name="mcqi_linkx_properties_ext" descr="" size="0x7c.0" >
	<field name="fw_image_status_bitmap" descr="Bit 0: Image A is running\;Bit 1: Image A is committed, module boots from image \;A\;Bit 2: Image A is erased / empty\;Bit 3: Reserved\;Bit 4: Image B is running\;Bit 5: Image B is committed, module boots from image \;B\;Bit 6: Image B is erased / empty\;Bit 7: Reserved" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="fw_image_info_bitmap" descr="Bit 0: FW image A is present \;Bit 1: FW image B is present\;Bit 2: Factory / boot image is present\;Bits 3-7: Reserved" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="image_a_minor" descr="Image A FW minor version" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="image_a_major" descr="Image A FW major version" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="image_a_subminor" descr="Image A FW subminor number" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="image_b_minor" descr="Image B FW minor version" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="image_b_major" descr="Image B FW major version" access="RO" offset="0xC.8" size="0x0.8" />
	<field name="image_b_subminor" descr="Image B FW subminor number" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="factory_image_minor" descr="Factory / boot image FW minor version" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="factory_image_major" descr="Factory / boot image FW major version" access="RO" offset="0x14.8" size="0x0.8" />
	<field name="factory_image_subminor" descr="Factory / boot image FW subminor number" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="management_interface_protocol" descr="0: Does not support either one of the FW update proce\;dures defined below\;1: SFF-8636 management interface and pseudo-CMIS \;FW. Update is supported\;2: CMIS 4.0 is implemented" access="RO" offset="0x1C.0" size="0x0.6" />
	<field name="activation_type" descr="0: HW reset is required. Host should be prepared to \;power cycle a cable after sending a RunFWImage com\;mand.\;1: Self-activation with HW reset contained in the RunF\;WImage command. No additional actions required \;from the host.\;2:Self-activation with hitless reset contained in the \;RunFWImage command. No additional actions \;required from the host.\;3-15: Reserved" access="RO" offset="0x1C.10" size="0x0.4" />
	<field name="vendor_sn" descr="Vendor Serial Number" access="RO" offset="0x20.0" size="0x0.16" />
</node>

<node name="mcqi_reg_data_auto_ext" descr="" attr_is_union="1" size="0x7c.0" >
	<field name="mcqi_cap_ext" descr="" subnode="mcqi_cap_ext" offset="0x0.0" selected_by="CAPABILITIES" size="0x7c.0" />
	<field name="mcqi_version_ext" descr="" subnode="mcqi_version_ext" offset="0x0.0" selected_by="VERSION" size="0x7c.0" />
	<field name="mcqi_activation_method_ext" descr="" subnode="mcqi_activation_method_ext" offset="0x0.0" selected_by="ACTIVATION_METHOD" size="0x7c.0" />
	<field name="mcqi_linkx_properties_ext" descr="" subnode="mcqi_linkx_properties_ext" offset="0x0.0" selected_by="LINKX_PROPERTIES" size="0x7c.0" />
</node>

<node name="mcqi_reg_ext" descr="" size="0x94.0" >
	<field name="component_index" descr="Component index gathered by &quot;MCQS - Management \;Component Query Status&quot;" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index \;starting at index 1. Index 0 indicates the host device." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="read_pending_component" descr="When set, the register will return information about \;the pending component (if available)" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch / NIC\;1: Gearbox" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="info_type" descr="Component properties set.\;0x0: CAPABILITIES\;0x1: VERSION\;0x5: ACTIVATION_METHOD\;0x6: LINKX_PROPERTIES\;Other values are reserved" access="RW" enum="CAPABILITIES=0x0,VERSION=0x1,ACTIVATION_METHOD=0x5,LINKX_PROPERTIES=0x6" offset="0x8.0" size="0x0.5" />
	<field name="info_size" descr="Properties set structure size, given in bytes." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="offset" descr="The requested/returned data offset from the section \;start, given in bytes.\;Must be DWORD aligned." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="data_size" descr="The requested/returned data size, given in bytes.\;If data_size is not DWORD aligned, the last bytes are \;zero padded." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="data" descr="Properties set structure according to info_type.\;CAPABILITIES - See Table 1854, &quot;MCQI CAPABILI\;TIES Info Layout,&quot; on page 2103\;VERSION - See Table 1856, &quot;MCQI VERSION Info \;Layout,&quot; on page 2105\;ACTIVATION_METHOD - See Table 1860, &quot;MCQI \;ACTIVATION_METHOD Info Layout,&quot; on page 2107\;LINKX_PREPERTIES - See Table 1862, &quot;MCQI \;LINKX_PROPERTIES Info Layout,&quot; on page 2108" subnode="mcqi_reg_data_auto_ext" access="RO" offset="0x18.0" size="0x7c.0" union_selector="$(parent).info_type" />
</node>

<node name="mcqi_version_ext" descr="" size="0x7c.0" >
	<field name="version_string_length" descr="" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="user_defined_time_valid" descr="When set, the component has a valid user-defined ver\;sion time-stamp in user_defined_time" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="build_time_valid" descr="When set, the component has a valid creation time-\;stamp in build_time" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="version" descr="Version number" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="build_time" descr="Time of component creation. Valid only if build_\;time_valid is set. See Table 1858, &quot;Date-Time Lay\;out,&quot; on page 2106" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="user_defined_time" descr="User-defined time assigned to the component version. \;Valid only if user_defined_time_valid is set. See \;Table 1858, &quot;Date-Time Layout,&quot; on page 2106" subnode="uint64" access="RW" offset="0x10.0" size="0x8.0" />
	<field name="build_tool_version" descr="Build tool version number.\;Valid only when not equal to 0" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="version_string" descr="NULL terminated string representing the version." access="RW" high_bound="91" low_bound="0" offset="0x20.24" size="0x5c.0" />
</node>

<node name="mcqs_reg_ext" descr="" size="0x10.0" >
	<field name="component_index" descr="Component Index. Values range from 1 to the last \;component indicated by last_index_flag." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index \;starting at index 1. Index 0 indicates the host device." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="last_index_flag" descr="When set, this component is the last component (high\;est component_index)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="identifier" descr="This field uniquely identifies a specific component type. \;0x1: BOOT_IMG\;0x4: OEM_NVCONFIG\;0x5: MLNX_NVCONFIG\;0x6: CS_TOKEN\;0x7: DBG_TOKEN\;0xA: Gearbox\;0xB: CC_ALGO - Congestion Control Algorithm\;0xC: LINKX_IMG\;0xD: CRYPTO_TO_COMMISSIONING\;0xE: RMCS_TOKEN\;0xF: RMDT_TOKEN\;Other values are reserved" access="RO" enum="BOOT_IMG=0x1,OEM_NVCONFIG=0x4,MLNX_NVCONFIG=0x5,CS_TOKEN=0x6,DBG_TOKEN=0x7,Gearbox=0xa,CC_ALGO=0xb,LINKX_IMG=0xc,CRYPTO_TO_COMMISSIONING=0xd,RMCS_TOKEN=0xe,RMDT_TOKEN=0xf" offset="0x4.0" size="0x0.16" />
	<field name="component_update_state" descr="Component state in update flow, see Section 10.2.1, \;&quot;Component Update State&quot;, on page 806:\;0x0: IDLE\;0x1: IN_PROGRESS\;0x2: APPLIED\;0x3: ACTIVE \;0x4: ACTIVE_PENDING_RESET\;0x5: FAILED\;0x6: CANCELED\;0x7: BUSY\;\;Other values are reserved" access="RO" enum="IDLE=0x0,IN_PROGRESS=0x1,APPLIED=0x2,ACTIVE=0x3,ACTIVE_PENDING_RESET=0x4,FAILED=0x5,CANCELED=0x6,BUSY=0x7" offset="0x8.0" size="0x0.4" />
	<field name="component_status" descr="The status of the component:\;0x0: NOT_PRESENT - The component is supported by \;the device but, currently not present\;0x1: PRESENT - This component is present. For down\;stream devices link LinkX component, this is an indica\;tion that the binary image is present at the host device \;memory.\;0x2: IN_USE - The component is present and currently \;in use." access="RO" enum="NOT_PRESENT=0x0,PRESENT=0x1,IN_USE=0x2" offset="0x8.4" size="0x0.5" />
	<field name="progress" descr="Progress in percentage (from 0 to 100). This field is \;only relevant for cables." access="RO" offset="0x8.9" size="0x0.7" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" offset="0xC.0" size="0x0.8" />
	<field name="last_update_state_changer_host_id" descr="For last_update_state_changer_type BMC, command-\;interface and ICMD, indicates the identifier of the host \;of the handle owner. Otherwise reserved." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="last_update_state_changer_type" descr="Indicates which entity was the last to change the com\;ponent_update_state of this component.\;0x0: unspecified\;0x1: Chassis_BMC\;0x2: MAD\;0x3: BMC\;0x4: command_interface\;0x5: ICMD\;\;Other values are reserved" access="RO" enum="unspecified=0x0,Chassis_BMC=0x1,MAD=0x2,BMC=0x3,command_interface=0x4,ICMD=0x5" offset="0xC.28" size="0x0.4" />
</node>

<node name="mdcr_ext" descr="" size="0x60.0" >
	<field name="device_type" descr="Peripheral device type\;1: XM" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="device_status_data" descr="Device initialization Data. \;For XM status, see Table 1884, &quot;MDCR - XM Data Layout,&quot; \;on page 2127" subnode="mdcr_xm_data_ext" access="RO" offset="0x10.0" size="0x50.0" />
</node>

<node name="mdcr_xm_data_ext" descr="" size="0x50.0" >
	<field name="xm_status" descr="XM load status.\;0: Pending\;1: No connection (At least 1 of the two Ethernet ports is not up)\;2: Version mismatch (major and minor are different from \;major_expected and minor_expected)\;3: Loaded successfully" access="RO" offset="0x0.20" size="0x0.4" />
	<field name="xm_major" descr="XM major version" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="xm_minor" descr="XM minor version" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="xm_build_id" descr="XM build ID" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="xm_expected_major" descr="XM expected major version" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="xm_expected_minor" descr="XM expected minor version" access="RO" offset="0x14.0" size="0x0.16" />
</node>

<node name="mddc_ext" descr="" size="0x30.0" >
	<field name="slot_index" descr="Slot index\;0: Reserved" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="index" descr="Index related to the specific granularity type.\;For level = 0, this field is neglected" access="INDEX" offset="0x0.9" size="0x0.8" />
	<field name="level" descr="Granularity of control and configuration.\;0: Configurations per line card \;1: Configuration per device\;2-15: Reserved" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="device_enable" descr="When set, FW is the manager and allowed to program the \;Downstream Device." access="RW" offset="0x4.28" size="0x0.1" />
	<field name="rst" descr="Reset request\;0: No reset\;1: Soft Reset\;2-7: Reserved" access="OP" offset="0x4.29" size="0x0.3" />
</node>

<node name="mddq_data_auto_ext" descr="" attr_is_union="1" size="0x20.0" >
	<field name="slot_info_ext" descr="" subnode="slot_info_ext" offset="0x0.0" selected_by="slot_info" size="0x20.0" />
	<field name="device_info_ext" descr="" subnode="device_info_ext" offset="0x0.0" selected_by="device_info" size="0x20.0" />
	<field name="slot_name_ext" descr="" subnode="slot_name_ext" offset="0x0.0" selected_by="slot_name" size="0x20.0" />
</node>

<node name="mddq_ext" descr="" size="0x30.0" >
	<field name="slot_index" descr="Slot index\;0: Reserved" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="query_type" descr="0: Reserved\;1: slot_info\;2: device_info - for a device on the slot. If there are no devices \;on the slot, data_valid will be &apos;0&apos;.\;3: slot_name - Name of the slot (string)" access="INDEX" enum="Reserved=0x0,slot_info=0x1,device_info=0x2,slot_name=0x3" offset="0x0.16" size="0x0.8" />
	<field name="sie" descr="Slot info event enable\;When set to &apos;1&apos;, each change in the MDDQ.slot_info.provi\;sioned / sr_valid / active / ready will generate an DSDSC event." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="request_message_sequence" descr="Request message sequential number. \;The first message number should be 0" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="response_message_sequence" descr="Response message sequential number. \;For a specific request, the response message sequential num\;ber is the following one. \;In addition, the last message should be 0." access="RO" offset="0x4.16" size="0x0.8" />
	<field name="query_index" descr="Index related to the specific query_type. \;For query_type = 1,2,3 this field is neglected." access="INDEX" offset="0x8.0" size="0x0.8" />
	<field name="data_valid" descr="If set, the data in the data field is valid and contain the informa\;tion for the queried index. \;Note: This field is not reflecting any validity of the data while \;accessing a non-existing query entity. Querying with an out of \;range index will lead to BAD_PARAM status of the register." access="RO" offset="0x8.31" size="0x0.1" />
	<field name="data" descr="Properties of that field are based on query_type.\;For slot information query_type data - see Table 1896, \;&quot;slot_info Register Layout,&quot; on page 2133\;For devices on slot query_type data - see Table 1898, \;&quot;device_info Register Layout,&quot; on page 2134\;For slot name query_type data - see Table 1900, &quot;slot_name \;Register Layout,&quot; on page 2135" subnode="mddq_data_auto_ext" access="RO" offset="0x10.0" size="0x20.0" union_selector="$(parent).query_type" />
</node>

<node name="mddt_reg_ext" descr="" size="0x110.0" >
	<field name="device_index" descr="Device index" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="type" descr="0: PRM_Register\;1: Command\;2: CrSpace_access - [Internal]" access="OP" enum="PRM_Register=0x0,Command=0x1,CrSpace_access=0x2" offset="0x4.0" size="0x0.2" />
	<field name="write_size" descr="Write size in D-Words." access="OP" offset="0x4.16" size="0x0.8" />
	<field name="read_size" descr="Read size in D-Words." access="OP" offset="0x4.24" size="0x0.8" />
	<field name="payload" descr="Payload\;For PRM Register type payload- See Table 1888, \;&quot;PRM Register Payload Layout,&quot; on page 2130\;For Command type payload - See Table 1890, &quot;Com\;mand Payload Layout,&quot; on page 2130\;For CrSpace type payload - See Table 1892, \;&quot;CrSpace access Payload Layout,&quot; on page 2131" subnode="mddt_reg_payload_auto_ext" access="RW" offset="0xC.0" size="0x104.0" union_selector="$(parent).type" />
</node>

<node name="mddt_reg_payload_auto_ext" descr="" attr_is_union="1" size="0x104.0" >
	<field name="prm_register_payload_ext" descr="" subnode="prm_register_payload_ext" offset="0x0.0" selected_by="PRM_Register" size="0x104.0" />
	<field name="command_payload_ext" descr="" subnode="command_payload_ext" offset="0x0.0" selected_by="Command" size="0x104.0" />
	<field name="crspace_access_payload_ext" descr="" subnode="crspace_access_payload_ext" offset="0x0.0" selected_by="CrSpace_access" size="0x104.0" />
</node>

<node name="mdfcr_reg_ext" descr="" size="0x60.0" >
	<field name="device_type" descr="Peripheral device type\;1: Vega_Gearbox\;2: Tile" access="INDEX" enum="Vega_Gearbox=0x1,Tile=0x2" offset="0x0.0" size="0x0.8" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="all" descr="All devices are selected and device_index is ignored\;When set to &apos;1&apos;, the fw_status should represent the worst case \;of any of the devices. fw_version, build_id, major and minor \;should be of device number 0." access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="first_fw_status_device" descr="The first device representing the fw_status" access="RO" offset="0xC.0" size="0x0.12" />
	<field name="fw_status" descr="FW load status.\;0: No errors, FW has loaded successfully. \;1: Flash error. \;2: FW load error. 15: Not ready yet for displaying the status." access="RO" offset="0xC.20" size="0x0.4" />
	<field name="expected_fw_version" descr="Expected FW version" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="fw_version" descr="FW version" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="build_id" descr="FW build ID" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="major" descr="FW major version" access="RO" offset="0x1C.0" size="0x0.8" />
	<field name="minor" descr="FW minor version" access="RO" offset="0x20.0" size="0x0.8" />
	<field name="error_id" descr="FW burning status error.\;\;1: no_errors\;2: error_in_total_size\;3: error_in_iRAM_size_read\;4: error_in_DRAM_size_read\;5: SPI_read_from_EEPROM_time-out\;6: CRC_on_downloaded_EEPROM_content\;7: Download_process_is_on-going\;8: SPI_reset_time-out\;9: memory_protection\;10: unknown_parameter_was_received_by_bootloader \;11: invalid_message_was_received_by_bootloader\;12: message_was_aborted_by_host\;\;Values from 13-32 are reserved" access="RO" enum="no_errors=0x1,error_in_total_size=0x2,error_in_iRAM_size_read=0x3,error_in_DRAM_size_read=0x4,SPI_read_from_EEPROM_time=0x5,CRC_on_downloaded_EEPROM_content=0x6,Download_process_is_on=0x7,SPI_reset_time=0x8,memory_protection=0x9,unknown_parameter_was_received_by_bootloader=0xa,invalid_message_was_received_by_bootloader=0xb,message_was_aborted_by_host=0xc" offset="0x24.11" size="0x0.5" />
</node>

<node name="mdir_reg_ext" descr="" size="0x40.0" >
	<field name="device_id" descr="Device ID" access="RO" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="mdrcr_ext" descr="" size="0x30.0" >
	<field name="device_type" descr="Peripheral device type\;1: Gearbox\;" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="all" descr="All devices are selected and device_index is ignored\;When set to &apos;1&apos;, the rst_status should represent the worst case \;of any of the devices." access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="rst_op" descr="Reset Operation.\;0: Query of the reset status which is displayed through rst_sta\;tus.\;1: Full Reset of the selected device(s).\;2-8: Reserved." access="RW" offset="0xC.0" size="0x0.3" />
	<field name="rst_status" descr="Reset status.\;0: Reset completed successfully. 1: Reset operation has not \;finished yet." access="RO" offset="0xC.16" size="0x0.4" />
</node>

<node name="mdsr_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0: The debug session ended successfully\;1: Failed to execute the operation. See additional_info for \;more details.\;2: Debug session active. See type_of_token for more details.\;3: No token applied\;4: Challenge provided, no token installed yet, see type_of_to\;ken for details.\;5: Timeout before token installed, see type_of_token for \;details\;6: Timeout of active token.\;7-15: Reserved\;\;Note: Status might be &apos;0&apos; even when debug query is not \;allowed and additional_info field will expose the reason." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="additional_info" descr="0: No additional information available \;1: There is no debug session in progress\;2: FW is not secured, debug session cannot be ended\;3: Fail - Debug end request cannot be accepted. \;4: Fail - Host is not allowed to query debug session\;5: Debug session active" access="RO" offset="0x0.8" size="0x0.6" />
	<field name="type_of_token" descr="0: Debug FW token 1: CS token \;2: FRC token \;3: RMCS token\;4: RMDS token \;5: CRCS token \;6: CRDT token" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="end" descr="Set to &apos;1&apos; to end debug session.\;Setting to &apos;0&apos; will not trigger any operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="time_left" descr="Time left in seconds.\;In case that status is 2 (debug session active) - time left for \;token operation\;In case that status is 4 (challenge provided, no token \;installed yet) - time left for token installation\;For any other status, field should be zero" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="merr_ext" descr="" size="0x14.0" >
	<field name="ent_type" descr="Entity type.\;0: Reserved\;1: QSFP Module (the relevant signals are: present, reset, \;interrupt, power enable, low power mode, power good, mod\;sel, QSFP LEDs)" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="current_index" descr="Current entity index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="target_index" descr="Entity number to be mapped to." access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="mfba_reg_ext" descr="" size="0x10c.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="The size of the data to be written or read in bytes\;Should comply with block_size and block_alignment fields in \;MFPA." access="OP" offset="0x4.0" size="0x0.9" />
	<field name="address" descr="The start address of this read or write access in bytes. Should \;comply with block_size and block_alignment fields in MFPA." access="INDEX" offset="0x8.0" size="0x4.0" />
	<field name="data" descr="The data to be written or read data." access="RW" high_bound="63" low_bound="0" offset="0xC.0" size="0x100.0" />
</node>

<node name="mfbe_reg_ext" descr="" size="0xc.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device. \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="bulk_64kb_erase" descr="Erase a 64KB flash area in one bulk operation." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="bulk_32kb_erase" descr="Erase a 32KB flash area in one bulk operation." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="address" descr="The start address (in bytes) of this erase operation. Must be \;aligned with the selected erase size (sector, 32KB or 64KB)." access="INDEX" offset="0x8.0" size="0x4.0" />
</node>

<node name="mfcr_ext" descr="" size="0x8.0" >
	<field name="pwm_frequency" descr="Controls the frequency of the PWM signal.\;Supported frequencies are:\;0x0: 11Hz \;0x1: 14.7Hz\;0x2: 22.1Hz\;0x3 - 0111111: Reserved\;0x40: 1.4KHz\;0x41: 5KHz\;0x42: 20KHz\;0x43: 22.5KHz\;0x44: 25KHz\;0x45 - 0x7F: Reserved" access="RW" offset="0x0.0" size="0x0.7" />
	<field name="pwm_active" descr="Indicates which of the PWM control is active (bit per PWM)" access="RO" offset="0x4.0" size="0x0.5" />
	<field name="tacho_active" descr="Indicates which of the tachometer is active (bit per tachome\;ter)" access="RO" offset="0x4.16" size="0x0.10" />
	<field name="tacho_active_msb" descr="6 MSB indexes of the tachometers. \;Indicates which of the tachometer is active (bit per tachome\;ter)" access="RO" offset="0x4.26" size="0x0.6" />
</node>

<node name="mfm_ext" descr="" size="0x18.0" >
	<field name="index" descr="Index to the fabric memory table." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="memory_high" descr="Holds software-written data.\;Default value: 0x0\;Device reset will reset to the default value." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="memory_low" descr="Holds software-written data.\;Default value: 0x0\;Device reset will reset to the default value." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="memory_mask_high" descr="On write commands, indicates which of the bits from mem\;ory field are updated. Reserved on read operations." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="memory_mask_low" descr="On write commands, indicates which of the bits from mem\;ory field are updated. Reserved on read operations." access="WO" offset="0x14.0" size="0x4.0" />
</node>

<node name="mfmc_reg_ext" descr="" size="0x1c.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device. \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="wrp_block_count" descr="Power of 2 of the write protect block count\;0: 1 block\;1: 2 blocks\;2: 4 blocks\;3: 8 blocks etc.\;Range 0..5\;Note that per flash device there may be invalid configurations\;Reserved when wrp_en = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="block_size" descr="Block size\;0: write protect sub-sector blocks\;1: write protect sector blocks\;Reserved when wrp_en = 0\;Note that not all block sizes are supported on all flash device, \;need to check MFPA capabilities" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="wrp_en" descr="Write protect enable\;Set write protect of flash device" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="sub_sector_protect_size" descr="Power of 2 for sub_sector size in 4Kbytes.\;0: 4Kbyte.\;1: 8 Kbyte\;2: 16Kbyte.\;Etc." access="RO" offset="0x8.0" size="0x0.6" />
	<field name="sector_protect_size" descr="Power of 2 for sector size in 4Kbytes.\;0: 4Kbyte.\;1: 8 Kbyte\;2: 16Kbyte.\;Etc." access="RO" offset="0x8.8" size="0x0.6" />
	<field name="quad_en" descr="Quad enable IO bit in the device status register" access="RW" offset="0x10.24" size="0x0.1" />
	<field name="dummy_clock_cycles" descr="The number of dummy clock cycles subsequent to all FAST \;READ commands. \;Reserved if not supported by the device" access="RW" offset="0x18.0" size="0x0.4" />
</node>

<node name="mfnr_ext" descr="" size="0x30.0" >
	<field name="fan_index" descr="Fan tachometer index." access="INDEX" offset="0x0.0" size="0x0.5" />
	<field name="serial_number" descr="Fan serial number (ASCII string)\;Value of &apos;0&apos;: Some error (Fan not present, disconnected etc.)" access="RO" high_bound="5" low_bound="0" offset="0x4.0" size="0x18.0" />
	<field name="part_number" descr="Fan part number (ASCII string)\;Value of &apos;0&apos;: Some error (Fan not present, disconnected etc.)" access="RO" high_bound="4" low_bound="0" offset="0x1C.0" size="0x14.0" />
</node>

<node name="mfpa_reg_ext" descr="" size="0x20.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device.\;Range between 0 .. flash_num -1\;" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, boot_address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="boot_address" descr="The flash address from which the firmware will boot in the next \;reset (warm start)." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="flash_num" descr="The number of flash devices\;1: there is 1 flash device, etc." access="RO" offset="0x10.0" size="0x0.4" />
	<field name="sub_sector_wrp_en" descr="If set, MFMC register supports setting write protect with sub-\;sector- blocks\;Sub-sector block size is available in MFMC.sub_sector_pro\;tect_size" access="RO" offset="0x10.16" size="0x0.1" />
	<field name="sector_wrp_en" descr="If set, MFMC register supports setting write protect with sector \;blocks.\;Sector block size is available in MFMC.sector_protect_size" access="RO" offset="0x10.17" size="0x0.1" />
	<field name="bulk_64kb_erase_en" descr="If set, MFBE register supports 64KB bulk erase operation.\;" access="RO" offset="0x10.29" size="0x0.1" />
	<field name="bulk_32kb_erase_en" descr="If set, MFBE register supports 32KB bulk erase operation." access="RO" offset="0x10.30" size="0x0.1" />
	<field name="wip" descr="Work In Progress. Indicates that the flash is currently busy." access="RO" offset="0x10.31" size="0x0.1" />
	<field name="jedec_id" descr="Return the flash JEDEC ID value returned by the standard \;Read JEDEC ID command that is available in most flash \;devices." access="RO" offset="0x14.0" size="0x0.24" />
	<field name="sector_size" descr="The minimal unit that can be erased with and MFBE command \;(in bytes)." access="RO" offset="0x18.0" size="0x0.10" />
	<field name="block_alignment" descr="Log 2 of the requested write alignment in bytes. Write access \;to the flash\;must not cross this alignment.\;Read and write access must be aligned to this value." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="block_size" descr="The block size in byes of the flash device, max read size for \;MFBA (typically 128 bytes)." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="capability_mask" descr="Bitmask indicates which capabilities are supported.\;Bit 15..0: reserved \;\;Bit 16: Set write protect supported (register MFMC supports \;setting write protection)\;Bit 17: quad enable read write is supported (register MFMC \;supports setting quad enable)\;Bit 18: set dummy cycle supported (register MFMC supports \;setting dummy cycles)" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mfrl_reg_ext" descr="" size="0x8.0" >
	<field name="reset_trigger" descr="The firmware reset trigger. \;Only a single bit may be set.\;Bit 0: TRIGGER0 (live-patch)\;Bit 3: TRIGGER3 (PCIe link toggle)\;Bit 6: TRIGGER6 (PERST)\;Other bits are reserved." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="reset_type" descr="Each bit represents a chip reset type.\;If set to &apos;1&apos;, the reset is supported. \;Bit 0: Full chip reset\;Bit 1: Keep network port active during reset\;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="rst_type_sel" descr="The requested reset type." access="RW" offset="0x4.24" size="0x0.3" />
	<field name="pci_sync_for_fw_update_resp" descr="Response of the driver for the reset request.\;1: Acknowledgment\;2: Dis-acknowledgment\;3: Reserved" access="WO" enum="Acknowledgment=0x1,Dis=0x2,Reserved=0x3" offset="0x4.27" size="0x0.2" />
	<field name="pci_sync_for_fw_update_start" descr="Setting this bit to &apos;1&apos; will request a synced driver flow and &apos;0&apos; \;for the legacy flow.\;Synced driver flow will not require to issue MFRL command \;from other hosts (x86 / ARM for SoC)" access="WO" offset="0x4.29" size="0x0.1" />
</node>

<node name="mfsc_ext" descr="" size="0x8.0" >
	<field name="pwm" descr="Fan pwm to control / monitor" access="INDEX" offset="0x0.24" size="0x0.3" />
	<field name="pwm_duty_cycle" descr="Controls the duty cycle of the PWM. Value range from 0..255 \;to represent duty cycle of 0%...100%" access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="mfsl_ext" descr="" size="0xc.0" >
	<field name="ie" descr="Interrupt Enable. If the ie bit is set and the Tachometer reading \;is out of range as defined by tach_min and tach_max, the \;FERR# will be asserted." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="ee" descr="Event Enable.\;0 - Do not generate event\;1 - Generate Event \;2 - Generate single event\;For Fan Error Evet details refer to Section  25.36.5, &quot;FORE - Fan \;Out of Range Event&quot;." access="RW" offset="0x0.2" size="0x0.2" />
	<field name="tacho" descr="Fan tachometer index" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="tach_min" descr="Tachometer minimum value (minimum RPM)." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="tach_max" descr="Tachometer maximum value (maximum RPM)." access="RW" offset="0x8.0" size="0x0.16" />
</node>

<node name="mfsm_ext" descr="" size="0x8.0" >
	<field name="n" descr="" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="tacho" descr="Fan tachometer index" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rpm" descr="Fan speed (round per minute) calculated based on the time \;measurement between n fan pulses.\;Note that in order for the RPM to be correct, the n value should \;correspond to the number of tach pulses per rotation mea\;sured by the tachometer." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="mfsv_reg_ext" descr="" size="0x30.0" >
	<field name="efuses_prog_en" descr="When this bit is set, it indicates that it is allowed for the boot \;FW to program the FW security version related EFUSEs if \;needed. This bit is not relevant in case the FW operates in an \;automatically EFUSEs programming approach (set in the INI \;file). Once set to 1, this configuration will be relevant only for \;the upcoming boot, thus this configuration will be set back to \;0 upon next boot. In addition, once this bit was set to 1 there \;is no option to clear it. option to clear it. In addition, once this \;bit was set to 1, there is no option to clear it." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="fw_sec_ver_stat" descr="Firmware security version status.\;0: EFUSEs value is equal to the currently running FW image \;value. No change is needed.\;1: EFUSEs value is smaller than the currently running FW \;image value. An update to the EFUSEs is required.\;2-3: Reserved" access="RO" offset="0x0.1" size="0x0.2" />
	<field name="efuses_prog_method" descr="EFUSEs programming method.\;0: manually. Upon boot, if FW indicates that \;FW_sec_ver_stat is 1 and only if EFUSEs_prog_en is 1, it will \;program the EFUSEs as needed.\;1: automatically. Upon boot, if FW indicates that \;FW_sec_ver_stat is 1, it will program the EFUSEs as needed." access="RO" offset="0x0.3" size="0x0.1" />
	<field name="img_sec_ver" descr="Image security version value" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="efuses_sec_ver" descr="EFUSEs security version value" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mgcr_reg_ext" descr="" size="0x20.0" >
	<field name="segment" descr="The GPIO segment which the command&apos;s parameters apply" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="segments_count" descr="Ceiling function of total number of GPIOs / 32 in the system." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="GPIO_data_in" descr="Input value of accessible GPIO[i] signals.\;When GPIO_access_en[i] = 0, GPIO_data_in[i] always returns \;0" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="GPIO_data_out" descr="Output value of accessible GPIO signals.\;When GPIO_access_en[i] = 0, GPIO_data_out[i] always \;returns 0" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="GPIO_set" descr="These 2 fields are used together to control GPIO signals in \;the following manner:\;GPIO_set[i]=0, GPIO_clear[i]=0 : GPIO_data_out[i] = No \;Change\;GPIO_set[i]=0, GPIO_clear[i]=1 : GPIO_data_out[i] = 0\;GPIO_set[i]=1, GPIO_clear[i]=0 : GPIO_data_out[i] = 1\;GPIO_set[i]=1, GPIO_clear[i]=1 : GPIO_data_out[i] = not(GPI\;O_data_out[i])\;Ignored for non-controllable GPIO signals." access="WO" offset="0xC.0" size="0x4.0" />
	<field name="GPIO_clear" descr="These 2 fields are used together to control GPIO signals in \;the following manner:\;GPIO_set[i]=0, GPIO_clear[i]=0 : GPIO_data_out[i] = No \;Change\;GPIO_set[i]=0, GPIO_clear[i]=1 : GPIO_data_out[i] = 0\;GPIO_set[i]=1, GPIO_clear[i]=0 : GPIO_data_out[i] = 1\;GPIO_set[i]=1, GPIO_clear[i]=1 : GPIO_data_out[i] = not(GPI\;O_data_out[i])\;Ignored for non-controllable GPIO signals." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="GPIO_access_en" descr="Access allowance to the corresponding GPIO signal.\;0: GPIO[i] is not observable / controllable by the host SW.\;1: GPIO[i] is observable / controllable by the host SW." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="direction" descr="0: GPIO[i] is an input only signal\;1: GPIO[i] is an output signal. Data out can be updates by the \;host SW and data in can be queried by the host SW.\;For non-accessible GPIOs, the corresponding value is 0." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="drive_type" descr="0: GPIO[i] is an open drain output. The device can only drive \;the GPIO[i] output pin low when GPIO_data_out[i] is 0. When \;GPIO_data_out[i] is 1, GPIO[i] is in HighZ. \;1: GPIO[i] is a full-drive output pin\;When GPIO_access_en[i] =0, direction[i] and drive_type[i] are \;always read as 0." access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see Table 1743, &quot;Hardware Info \;Layout,&quot; on page 2021" subnode="mgir_hardware_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
	<field name="fw_info" descr="Firmware Information, see Table 1745, &quot;Firmware Info \;Layout,&quot; on page 2023" subnode="mgir_fw_info_ext" access="RW" offset="0x20.0" size="0x40.0" />
	<field name="sw_info" descr="Software Information, see Table 1747, &quot;Software Info Lay\;out,&quot; on page 2025\;This field indicates the oldest software version compati\;ble with the current firmware" subnode="mgir_sw_info_ext" access="RW" offset="0x60.0" size="0x20.0" />
</node>

<node name="mgir_fw_info_ext" descr="" size="0x40.0" >
	<field name="sub_minor" descr="Sub-minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_sub_minor." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_minor." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_major." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="secured" descr="When set, the device is running firmware with \;secure-firmware updates capabilities." access="RO" offset="0x0.24" size="0x0.1" />
	<field name="signed_fw" descr="When set the device is running a signed FW binaries." access="RO" offset="0x0.25" size="0x0.1" />
	<field name="debug" descr="When set, the device is running a debug firmware. \;&apos;debug&apos; binary can only be installed on specific \;devices (identified by their &apos;Factory base MAC&apos;), \;which currently run a specific firmware version. \;These restrictions are expressed by a signed &apos;debug&apos; \;token that must be loaded to the device before \;installing the debug binary." access="RO" offset="0x0.26" size="0x0.1" />
	<field name="dev" descr="*NOTE* this field has diff meaning for Switch vs. NIC \;\;\;NIC:\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version\;\;Switch:\;The device is running:\;0: regular FW branch\;1: development branch" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="string_tlv" descr="When set, string-TLV is supported." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="dev_sc" descr="*NOTE* for NICs same as dev field\;Development-secure:\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="build_id" descr="Firmware Build ID. Optional. ." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="year" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= \;0x05, Day= 0x03, and Year= 0x04" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="day" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= \;0x05, Day= 0x03, and Year= 0x04" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="month" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= \;0x05, Day= 0x03, and Year= 0x04" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="hour" descr="Firmware installation hour.\;For example 17:43 will be coded as 0x1743" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="psid" descr="To be defined later." access="RO" high_bound="15" low_bound="0" offset="0x10.24" size="0x10.0" />
	<field name="ini_file_version" descr="User-configured version number of the current INI \;file." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="extended_major" descr="FW version&apos;s Major field in extended (32b) format." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="extended_minor" descr="FW version&apos;s Minor field in extended (32b) format." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="extended_sub_minor" descr="FW version&apos;s SubMinor field in extended (32b) for\;mat." access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="isfu_major" descr="" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="life_cycle" descr="0: Production\;1: GA Secured\;2: GA Non-Secured\;3: RMA" access="RO" offset="0x34.0" size="0x0.2" />
	<field name="sec_boot" descr="0: Disable\;1: Enable" access="RO" offset="0x34.2" size="0x0.1" />
	<field name="encryption" descr="0: Disable\;1: Enable" access="RO" offset="0x34.3" size="0x0.1" />
</node>

<node name="mgir_hardware_info_ext" descr="" size="0x20.0" >
	<field name="device_id" descr="PCI device ID." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="device_hw_revision" descr="\;SwitchX Devices:\;0x00A0: Device step A0, FCC package\;0x00A1: Device step A1, FCC package\;0x00A2: Device step A2, FCC package\;\;Switch-IB Devices:\;0x00A0: Switch-IB device step A0, FCC package\;0x0000 is a valid value for some devices not included \;in PRM." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="pvs" descr="Process Voltage Scaling\;Supported nominal V_CORE voltage (in 50mV units) \;for the device." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="technology" descr="Process technology\;0: N/A\;1: 40nm\;2: 28nm\;3: 16nm\;4: 7nm\;5: 5nm\;6-31: Reserved" access="RO" offset="0x4.11" size="0x0.5" />
	<field name="num_ports" descr="Number of physical port the device supports." access="RO" offset="0x4.16" size="0x0.8" />
	<field name="hw_dev_id" descr="The PCI device-ID of the NIC/HCA in recovery (Live\;fish) mode." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="manufacturing_base_mac_47_32" descr="MSB of the &quot;base&quot; MAC address of the NIC that was \;allocate during manufacturing. The NIC derives the \;MAC addresses for the different PCI PFs from this \;MAC address. This parameter can be used as a \;canonical unique identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not \;supported." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="manufacturing_base_mac_31_0" descr="LSB of the &quot;base&quot; MAC address of the NIC that was \;allocate during manufacturing. The NIC derives the \;MAC addresses for the different PCI PFs from this \;MAC address. This parameter can be used as a \;canonical unique identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not \;supported." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="uptime" descr="Time (in secs.) since last reset0" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgir_sw_info_ext" descr="" size="0x20.0" >
	<field name="sub_minor" descr="Sub-minor Driver version number.\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor Driver version number.\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major Driver version number.\;" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="rom3_type" descr="ROM 3 type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="rom3_arch" descr="Arch type of ROM 3:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting \;both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="rom2_type" descr="ROM 2type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="rom2_arch" descr="Arch type of ROM 2:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting \;both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="rom1_type" descr="ROM 1type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="rom1_arch" descr="Arch type of ROM 1:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting \;both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.20" size="0x0.4" />
	<field name="rom0_type" descr="ROM 0 type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="rom0_arch" descr="Arch type of ROM 0:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting \;both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="rom0_version" descr="ROM 0 version." subnode="rom_version_ext" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="rom1_version" descr="ROM 1 version." subnode="rom_version_ext" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="rom2_version" descr="ROM 2version." subnode="rom_version_ext" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="rom3_version" descr="ROM 3 version." subnode="rom_version_ext" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="mgnle_reg_ext" descr="" size="0x20.0" >
	<field name="le_pointer" descr="Pointer to the log entry (see description above for more \;information)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="lost_events" descr="The number of events that the system failed to log since \;the previous log entry.\;15 should be interpreted as &apos;15 or more events were \;lost&apos;" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="synced_time" descr="0x0: Boot - time is measured since NIC bootup.\;0x1: Synced - time was synced by the host." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="time_h" descr="The 32 MSB of the 64bit timestamp.  In microseconds\;When &quot;time_synced&quot; bit is set this is the time passed \;since the 1/1/1970 epoch.\;When &quot;time_synced&quot; is cleared this is the NIC uptime." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_l" descr="The 32 LSB of the 64bit timestamp.  In microseconds" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RO" offset="0x10.0" size="0xc.0" />
	<field name="log_data" descr="The logged data. Format is  different per the according \;to the log type." access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgpir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see Table 1755, &quot;Hardware Info \;Layout,&quot; on page 2030" subnode="mgpir_hw_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
</node>

<node name="mgpir_hw_info_ext" descr="" size="0x20.0" >
	<field name="num_of_devices" descr="Number of devices of device_type. \;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="devices_per_flash" descr="Number of devices of device_type per flash. \;" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="device_type" descr="Device type.\;0: No devices on system of that type.\;1: Vega gearbox dice\;2: Tiles\;3: No Info Available\;4: XM" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="num_of_modules" descr="Number of modules. \;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="num_of_slots" descr="Number of slots in the system. To eliminate receiving \;&apos;bad param&apos; status, the user should query that field \;with slot_index set to 0." access="RO" offset="0x4.8" size="0x0.8" />
	<field name="max_modules_per_slot" descr="Maximum number of modules that can be connected \;per slot." access="RO" offset="0x4.16" size="0x0.8" />
</node>

<node name="mhmpr_reg_ext" descr="" size="0x14.0" >
	<field name="upm" descr="&apos;0&apos; - if the ports are managed by host.\;&apos;1&apos; - if the ports are not managed by host" access="RW" offset="0x0.0" size="0x0.1" />
</node>

<node name="mhsr_ext" descr="" size="0x8.0" >
	<field name="health" descr="Software health state:\;0 - Failure\;1 - Reserved\;2 - Normal Operation\;3 - Boot / Init (default state)" access="WO" offset="0x0.0" size="0x0.4" />
</node>

<node name="mirc_reg_ext" descr="" size="0x8.0" >
	<field name="status_code" descr="Indicates the successful completion of the instruction, \;or the reason it failed. See Section 10.3.7, &quot;Error \;Handling&quot;, on page 809\;0x0: OK\;0x1: BUSY\;0x2: PROHIBITED_FW_VER_ERR\;0x3: FIRST_PAGE_COPY_FAILED\;0x4: FIRST_PAGE_ERASE_FAILED\;0x5: FIRST_PAGE_RESTORE_FAILED\;0x6: CANDIDATE_FW_DEACTIVATION_FAILED\;0x7: FW_ALREADY_ACTIVATED\;0x8: ERROR_DEVICE_RESET_REQUIRED\;0x9: ERROR_FW_PROGRAMMING_NEEDED\;Other values should be treated as an unknown error." access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="mjtag_ext" descr="" size="0x30.0" >
	<field name="size" descr="Size of operation - relevant for JTAG interface access com\;mands only, indicating the number of transaction bytes to \;execute. Maximum size supported is 40.\;Note: when size=0, no operation is performed (clock is not \;toggled). The tdo is sampled and provided in the response \;at jtag_transaction_set_0." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="sequence_number" descr="Command sequence number - to prevent re-execution of \;the same command due to command retransmission, this \;command includes a sequence number.\;The enable and disable commands MUST be issues with \;sequence_number = 0 while any JTAG access command \;must increase the sequence_number by 1 (the first JTAG \;access command should start at sequence_number = 1)." access="WO" offset="0x0.24" size="0x0.4" />
	<field name="cmd" descr="Command\;0 - JTAG interface disable - JTAG interface is disabled\;1 - JTAG interface enable - enabling JTAG interface\;2 - JTAG interface access" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="jtag_transaction_set" descr="See Table 1733, &quot;JTAG Transaction Set Byte Layout,&quot; \;on page 2015" access="RW" high_bound="43" low_bound="0" offset="0x4.24" size="0x2c.0" />
</node>

<node name="mkdc_reg_ext" descr="" size="0x2c.0" >
	<field name="error_code" descr="Indicates the successful completion of the instruction \;or the reason it failed:\;0: OK\;1: BAD_SESSION_ID\;2: BAD_KEEP_ALIVE_COUNTER\;3: BAD_SOURCE_ADDRESS\;4: SESSION_TIMEOUT\;Other values are Reserved." access="RO" enum="OK=0x0,BAD_SESSION_ID=0x1,BAD_KEEP_ALIVE_COUNTER=0x2,BAD_SOURCE_ADDRESS=0x3,SESSION_TIMEOUT=0x4" offset="0x0.0" size="0x0.4" />
	<field name="session_id" descr="Unique debug session identifier." access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="current_keep_alive_counter" descr="Running counter that states the current sequence \;number of each keep-alive session." access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="next_keep_alive_counter" descr="Running counter that states the expected next \;sequence number of each keep-alive session." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mlcr_ext" descr="" size="0xc.0" >
	<field name="led_type" descr="Led type (only supported when cap_local_or_uid_only==1.)\;0: LOCALP_AND_UID - local port and uid\;1: UID\;2: LOCALP - local port" access="RW" enum="LOCALP_AND_UID=0x0,UID=0x1,LOCALP=0x2" offset="0x0.0" size="0x0.4" />
	<field name="cap_local_or_uid_only" descr="If set, led_type of type UID and LOCAL Port only are sup\;ported." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="operation_cap" descr="If set to &apos;1&apos;, operation field is supported." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="operation" descr="0: Controlled by HW / Beacon\;1: LED on - if bi-color, apply amber.\;2: LED off\;Others: Reserved\;" access="RW" offset="0x0.12" size="0x0.4" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port\;(only supported when cap_local_or_uid_only==1.)" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the \;local_port[9:8] bits" access="RW" offset="0x0.24" size="0x0.2" />
	<field name="beacon_duration" descr="Duration of the beacon to be active, units of seconds\;The value of 0x0 will turn off the beacon\;The value of 0xffff will set the beacon to infinity" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="beacon_remain" descr="Remaining duration of the beacon, units of seconds\;The value of 0xffff means infinity" access="RO" offset="0x8.0" size="0x0.16" />
</node>

<node name="mmdio_ext" descr="" size="0xc.0" >
	<field name="operation" descr="0 - NOP\;1 - Address (reserved for Clause 22)\;2 - Read\;3 - Write\;4 - Post Read Increment Address (reserved for Clause 22)\;6 - Address + Read - Generates Address cycle and then \;Read cycle in Clause 45 (reserved for Clause 22)\;7 - Address + Write - Generates Address cycle and then \;Write cycle in Clause 45 (reserved for Clause 22)" access="WO" offset="0x0.0" size="0x0.3" />
	<field name="clause" descr="MDIO Definition:\;0 - Clause 22\;1 - Clause 45" access="WO" offset="0x0.8" size="0x0.2" />
	<field name="mdio_index" descr="Selection of the MDIO interface" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="reg_adr" descr="Reg Address (Clause 22) / Dev Type (Clause 45)" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="phy_adr" descr="PHY Address (PHYAD)" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="data" descr="Data (Clause 22) / Address/Data (Clause 45)" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="address" descr="Address (Clause 45)\;This field is only valid for Address + Read and Address + \;Write operations, providing the address. For other Clause 45 \;operations the data field provides the address when appro\;priate." access="RW" offset="0x8.16" size="0x0.16" />
</node>

<node name="mmhi_reg_ext" descr="" size="0x80.0" >
	<field name="host_number" descr="Identifier for the host used to access the register" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="host_en" descr="Bit per Host indicating this host is valid in the cur\;rent Multi-Host configuration.\;value 0x0 indicates this in not valid." access="RO" offset="0x8.0" size="0x0.16" />
</node>

<node name="mmia_ext" descr="" size="0xc.0" >
	<field name="operation" descr="0 - NOP\;1 - Erase\;2 - Read\;3 - Write" access="WO" offset="0x0.0" size="0x0.3" />
	<field name="Data" descr="" access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mnvda_reg_ext" descr="" size="0x10.0" >
	<field name="configuration_item_header" descr="Configuration Item Header" subnode="config_item_ext" access="RW" offset="0x0.0" size="0xc.0" />
	<field name="configuration_item_data" descr="Configuration Item Data\;" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="mnvdi_reg_ext" descr="" size="0xc.0" >
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RW" offset="0x0.0" size="0xc.0" />
</node>

<node name="mnvgc_reg_ext" descr="" size="0x10.0" >
	<field name="nvda_read_factory_settings" descr="NVDA Read factory settings. Indicates if reading the \;factory settings by NVDA is supported.\;0:unsupported\;1: supported" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="nvda_read_current_settings" descr="NVDA Read current settings. Indicates if reading the \;current settings by NVDA is supported.\;0: unsupported\;1: supported" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="priv_nv_other_host" descr="When set, TLVs of other hosts may be modified." access="RO" offset="0x0.2" size="0x0.1" />
</node>

<node name="mnvgn_reg_ext" descr="" size="0x20.0" >
	<field name="nv_pointer" descr="Pointer to the NV parameter (see description above for \;more information)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RO" offset="0x10.0" size="0xc.0" />
	<field name="configuration_item_data" descr="" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mnvia_reg_ext" descr="" size="0x8.0" >
	<field name="target" descr="Information targeted for invalidation\;0: ALL - all NVRAM parameters.\; All other values are reserved." access="WO" offset="0x0.0" size="0x0.3" />
	<field name="writer_id" descr="The entity which perform the invalidate.\;The encoding same as writer_id in Configuration Item \;register (See Table 1781, &quot;Configuration Item \;Header Layout,&quot; on page 2046)." access="RW" offset="0x0.4" size="0x0.5" />
</node>

<node name="mnvqc_reg_ext" descr="" size="0x8.0" >
	<field name="type" descr="Configuration item type. \;Table 1783, &quot;Configuration Item Data Type \;Class Global Layout,&quot; on page 2048\;Table 1785, &quot;Configuration Item Data Type \;Class Physical Port Layout,&quot; on page 2049\;Table 1787, &quot;Configuration Item Data Type \;Class Per Host-PF Layout,&quot; on page 2049" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="support_rd" descr="The configuration item is supported and can be read" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_wr" descr="The configuration item is supported and can be \;updated" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="version" descr="The maximal version of the configuration item sup\;ported by the device" access="RO" offset="0x4.4" size="0x0.4" />
</node>

<node name="module_latched_flag_info_ext" descr="" size="0xf8.0" >
	<field name="dp_fw_fault" descr="Valid for CMIS based modules only\;Latched modules Datapath fw fault flag" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="mod_fw_fault" descr="Valid for CMIS based modules only\;Latched module fw fault flag" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="vcc_flags" descr="Latched VCC flags of module\;Bit 0: high_vcc_alarm\;Bit 1: low_vcc_alarm\;Bit 2: high_vcc_warning\;Bit 3: low_vcc_warning" access="RO" enum="high_vcc_alarm=0x1,low_vcc_alarm=0x2,high_vcc_warning=0x4,low_vcc_warning=0x8" offset="0x0.24" size="0x0.4" />
	<field name="temp_flags" descr="Latched temperature flags of module\;Bit 0: high_temp_alarm\;Bit 1: low_temp_alarm\;Bit 2: high_temp_warning\;Bit 3: low_temp_warning" access="RO" enum="high_temp_alarm=0x1,low_temp_alarm=0x2,high_temp_warning=0x4,low_temp_warning=0x8" offset="0x0.28" size="0x0.4" />
	<field name="tx_ad_eq_fault" descr="Reserved for SFP\;Bitmask for latched Tx adaptive equalization fault flag per \;lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="tx_cdr_lol" descr="Bitmask for latched Tx cdr loss of lock flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="tx_los" descr="Reserved for SFP\;Bitmask for latched Tx loss of signal flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="tx_fault" descr="Bitmask for latched Tx fault flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="tx_power_lo_war" descr="Bitmask for latched Tx power low warning flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="tx_power_hi_war" descr="Bitmask for latched Tx power high warning flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="tx_power_lo_al" descr="Bitmask for latched Tx power low alarm flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="tx_power_hi_al" descr="Bitmask for latched Tx power high alarm flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="tx_bias_lo_war" descr="Bitmask for latched Tx bias low warning flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="tx_bias_hi_war" descr="Bitmask for latched Tx bias high warning flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0xC.8" size="0x0.8" />
	<field name="tx_bias_lo_al" descr="Bitmask for latched Tx bias low alarm flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="tx_bias_hi_al" descr="Bitmask for latched Tx bias high alarm flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="rx_cdr_lol" descr="Bitmask for latched Rx cdr loss of lock flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="rx_los" descr="Bitmask for latched Rx loss of signal flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x10.24" size="0x0.8" />
	<field name="rx_power_lo_war" descr="Bitmask for latched Rx power low warning flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="rx_power_hi_war" descr="Bitmask for latched Rx power high warning flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x14.8" size="0x0.8" />
	<field name="rx_power_lo_al" descr="Bitmask for latched Rx power low alarm flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x14.16" size="0x0.8" />
	<field name="rx_power_hi_al" descr="Bitmask for latched Rx power high alarm flag per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x14.24" size="0x0.8" />
	<field name="rx_output_valid_change" descr="Bitmask for latched rx output valid change per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x18.0" size="0x0.8" />
	<field name="rx_input_valid_change" descr="Bitmask for latched rx input valid change per lane.\;Bit 0 - lane 0 ... Bit 7 - lane 7" access="RO" offset="0x18.8" size="0x0.8" />
</node>

<node name="mpcir_ext" descr="" size="0x10.0" >
	<field name="all" descr="If set to &apos;01&apos;, activates the flow of preparation for FW ISSU, on \;all services. The values in op-codes for &quot;per-service&quot; are \;ignored.\;If set to &apos;10&apos;, returns to operational state on all services. The \;values in op-codes for &quot;per-service&quot; are ignored.\;11 - Reserved" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="ports" descr="For each of the services, the following operations are avail\;able:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in correspond\;ing _stat fields." access="OP" offset="0x4.0" size="0x0.2" />
	<field name="ports_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done \;service handling [Internal]: busy with some other critical \;flow).\;For not implemented services on a particular system, the \;status should be &apos;1&apos;." access="RO" offset="0xC.0" size="0x0.2" />
</node>

<node name="mpcnt_reg_counter_set_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="pcie_perf_counters_ext" descr="" subnode="pcie_perf_counters_ext" offset="0x0.0" selected_by="PCIE_performance_counters" size="0xf8.0" />
	<field name="pcie_lanes_counters_ext" descr="" subnode="pcie_lanes_counters_ext" offset="0x0.0" selected_by="PCIE_lane_counters" size="0xf8.0" />
	<field name="pcie_timers_states_ext" descr="" subnode="pcie_timers_states_ext" offset="0x0.0" selected_by="PCIE_timers_and_states" size="0xf8.0" />
</node>

<node name="mpcnt_reg_ext" descr="" size="0x100.0" >
	<field name="grp" descr="Performance counter group.\;0: PCIE_performance_counters\;1: PCIE_lane_counters \;2: PCIE_timers_and_states \;\;" access="INDEX" enum="PCIE_performance_counters=0x0,PCIE_lane_counters=0x1,PCIE_timers_and_states=0x2" offset="0x0.0" size="0x0.6" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIe index number (Internal domain index)\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value \;for all counters in the counter group. This bit can be set for \;both Set() and Get() operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;Table 1824, &quot;PCIe Performance Counters Data Layout,&quot; \;on page 2072\;Table 1828, &quot;PCIE lanes counters Data Layout,&quot; on \;page 2076 - [Internal] \;Table 1826, &quot;PCIE timers and states Data Layout,&quot; on \;page 2074 - [Internal]" subnode="mpcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="mpecs_reg_ext" descr="" size="0x20.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIE index number\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="capability_id" descr="capability ID as defined in PCIE spec" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="reg_num" descr="Register number\;Byte offset from the beginning of the capability ID" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="byte_enable" descr="Enable bit per byte\;bit 0 - byte 0 (bits 7:0)\;bit 1 - byte 1 (bits 15:8)\;bit 2 - byte 2 (bits 23:16)\;bit 3 - byte 3 (bits 31:24)\;Reserved for read operation." access="WO" offset="0xC.0" size="0x0.4" />
	<field name="status" descr="PCIE configuration space access status: \;0x0: SUCCESS - successful access\;0x1: FUNC_NUM_FAILURE - accessing unsupported configu\;ration space function number\;0x2: CAP_ID_FAILURE - accessing unsupported configuration \;space capability ID number\;0x3: REG_NUM_FAILURE - accessing unsupported configura\;tion space register number\;0x4: WRITE_FAILURE - write access to read-only configuration \;space\;0x5: PROTECTED_FAILURE - protected configuration" access="RO" enum="SUCCESS=0x0,FUNC_NUM_FAILURE=0x1,CAP_ID_FAILURE=0x2,REG_NUM_FAILURE=0x3,WRITE_FAILURE=0x4,PROTECTED_FAILURE=0x5" offset="0xC.8" size="0x0.8" />
	<field name="func_num" descr="Function number\;physical function index - see PCIE spec" access="INDEX" offset="0xC.16" size="0x0.8" />
	<field name="ext" descr="Extended or regular configuration space, as defined in PCIE \;spec:\;0 - Regular\;1 - Extended" access="INDEX" offset="0x10.0" size="0x0.2" />
	<field name="data" descr="" access="RW" offset="0x14.0" size="0x4.0" />
</node>

<node name="mpein_reg_ext" descr="" size="0x30.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIe index number (Internal domain index)\;Reserved when access is from the host, but can be used when \;operating in Socket-Direct mode." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="link_speed_enabled" descr="Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="link_width_enabled" descr="Maximum Link Width enabled:\;0: 1x\;1: 2x\;2: 4x\;3: 8x\;4: 16x" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="link_speed_active" descr="Current Link Speed:\;Bit 0: 2.5G (Gen1)\;Bit 1: 5G (Gen2)\;Bit 2: 8G (Gen3)\;Bit 4: 16G (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="link_width_active" descr="Negotiated Link Width, pcie_link_width active:\;0 - 1x\;1 - 2x\;2 - 4x\;3 - 8x\;4 - 16x" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="lane0_physical_position" descr="The physical lane position of logical lane0" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="num_of_vfs" descr="Number of Total Virtual Functions (for all PFs)" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="num_of_pfs" descr="Number of Physical Functions (PFs)" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="bdf0" descr="Bus Device Function - only for function0" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="lane_reversal" descr="Reversal mode of the link:\;0 - straight \;1 - reversal\;\;Note: together with lane0_physical_position provide the physi\;cal lane." access="RO" offset="0x18.0" size="0x0.1" />
	<field name="port_type" descr="Indicates the specific type of this PCI Express Function. Note \;that different Functions in a multi-Function device can gener\;ally be of different types.\;0 - PCI Express Endpoint port\;4 - Root Port of PCI Express Root Complex\;5 - PCI Express Upstream port\;6 - PCI Express Downstream port" access="RO" offset="0x18.12" size="0x0.4" />
	<field name="pwr_status" descr="Indicates the status of PCI power consumption limitations.\;0: PCI power report could not be read.\;1: Sufficient power reported.\;2: Insufficient power reported.\;3-7: Reserved" access="RO" offset="0x18.16" size="0x0.3" />
	<field name="max_payload_size" descr="Max payload size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.24" size="0x0.4" />
	<field name="max_read_request_size" descr="Max read request size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.28" size="0x0.4" />
	<field name="pci_power" descr="Power reported by the PCI device. The units are in Watts.\;0: Power is unknown." access="RO" offset="0x1C.0" size="0x0.12" />
	<field name="link_peer_max_speed" descr="Peer Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="device_status" descr="device_status bit mask:\;Bit 0: Correctable_error\;Bit 1: Non_Fatal_Error_detection\;Bit 2: Fatal_Error_detected\;Bit 3: Unsupported_request_detected\;Bit 4: AUX_power \;Bit 5: Transaction_Pending" access="RO" enum="Correctable_error=0x1,Non_Fatal_Error_detection=0x2,Fatal_Error_detected=0x4,Unsupported_request_detected=0x8,AUX_power=0x10,Transaction_Pending=0x20" offset="0x24.16" size="0x0.16" />
</node>

<node name="mpfm_ext" descr="" size="0x8.0" >
	<field name="mode" descr="PCIe Failure Mode.\;0 - normal. PCIe failure causes SwitchX reset.\;1 - independent. PCIe failure does not cause SwitchX reset." access="RW" offset="0x0.0" size="0x0.4" />
</node>

<node name="mpgo_reg_ext" descr="" size="0x14.0" >
	<field name="set_pd" descr="Set pulse duration" access="WO" offset="0x0.0" size="0x0.1" />
	<field name="next_pulse_time_stamp" descr="Next Pulse Time Stamp\;Start time of next trigger\;Units are device time units" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="pulse_duration" descr="Pulse Duration\;Units are mSec\;Default is 100\;Set only when set_pd = &apos;1&apos;" access="RW" offset="0x10.0" size="0x0.10" />
</node>

<node name="mpgr_ext" descr="" size="0x20.0" >
	<field name="fsps_admin" descr="Frequency Scaling Power Save Admin state:\;0 - Disable Frequency Scaling - Force device to highest fre\;quency supported\;1 - Force Frequency Scaling - Force device to highest frequency \;supported\;2 - Auto - Automatic Frequency Scaling (based on port&apos;s speed)." access="RW" offset="0x0.0" size="0x0.4" />
	<field name="fsps_status" descr="Actual Frequency\;0 - High Frequency\;1 - Low Frequency" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="vsps_admin" descr="Voltage Scaling Power Save Admin state:\;0 - Disable Voltage Scaling - Force device to high voltage\;1 - Force Voltage Scaling - Force device to low voltage\;2 - Auto - Automatic Voltage Scaling (based on device active \;frequency)." access="RW" offset="0x10.0" size="0x0.4" />
	<field name="vsps_status" descr="Actual Voltage\;0 - High Voltage\;1 - Low Voltage" access="RO" offset="0x14.0" size="0x0.4" />
</node>

<node name="mpir_ext" descr="" size="0x10.0" >
	<field name="host_buses" descr="Number of PCIe buses available for the host to connect ot \;the device.\;&apos;0&apos; when operating in non-Socket-Direct mode." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="Internal domain index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="sdm" descr="Socket-Direct mode indication.\;0: non-Socket-Direct mode (single host or multi-host)\;1: Socket-Direct mode, for querying host" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="subordinate_bus" descr="sunbordinate bus - the highest bus number that subordi\;nates to switch.\;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="secondary_bus" descr="secondary bus - the internal logic bus in the switch. \;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.8" size="0x0.8" />
	<field name="device" descr="PCIe device number." access="RO" offset="0x8.3" size="0x0.5" />
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the \;local_port[9:8] bits" access="RO" offset="0x8.12" size="0x0.2" />
	<field name="bus" descr="PCIe bus number." access="RO" offset="0x8.16" size="0x0.8" />
	<field name="local_port" descr="Local port number" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="slot_number" descr="Slot number" access="RO" offset="0xC.0" size="0x0.13" />
	<field name="num_con_devices" descr="number of PCIe connected deices / EP on the current port." access="RO" offset="0xC.16" size="0x0.8" />
	<field name="slot_cap" descr="If set to &apos;1&apos;, slot_number field is supported." access="RO" offset="0xC.31" size="0x0.1" />
</node>

<node name="mqdik_reg_ext" descr="" size="0x208.0" >
	<field name="algorithm" descr="0: ECC. Used for any of the P256, P385, P521 curves.\;1: RSA. Used for 2048 or 4096 keys." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="key_size" descr="Number of Bytes in the public_key" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="status" descr="0: Key is not ready for query\;1: Key is provided in the response" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="public_key" descr="Public-key value, per the specific algorithm." access="RO" high_bound="127" low_bound="0" offset="0x8.0" size="0x200.0" />
</node>

<node name="mqis_reg_ext" descr="" size="0x18.0" >
	<field name="info_type" descr="Type of information string to be queried:\;0x0: VPD - Read the PCI Vital Product Data capability \;content.\;0x1: MODEL_NAME\;0x2: MODEL_DESCRIPTION\;0x3: IMAGE_VSD\;0x4: DEVICE_VSD\;0x5: ROM_INFO\;other values are reserved." access="INDEX" enum="MODEL_NAME=0x1,MODEL_DESCRIPTION=0x2,IMAGE_VSD=0x3,DEVICE_VSD=0x4,ROM_INFO=0x5" offset="0x0.0" size="0x0.8" />
	<field name="info_length" descr="Total size of the information string, according to info_\;type. Value given in bytes." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="read_length" descr="Number of bytes requested. The device returns the \;number of bytes actually read." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="read_offset" descr="Offset in bytes of the first byte requested to read." access="INDEX" offset="0x8.16" size="0x0.16" />
	<field name="info_string" descr="Information string accessed, according to info_type. If \;the information is not available, a NULL string is \;returned." access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
</node>

<node name="mrpr_reg_ext" descr="" size="0x108.0" >
	<field name="type" descr="Runtime parameter to access or query\;" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="status" descr="0: Parameter is not supported\;1: Parameter is supported but is not ready for read\;2: Successful read\;3: Successful write\;Else - Reserved" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="length" descr="Number of Bytes in the parameter data section.\;When reading an unsupported /unavailable parameter, \;this field is 0 and there is no data field in the read \;response." access="RW" offset="0x0.24" size="0x0.8" />
	<field name="data" descr="Parameter data.\;Writing to this field for read-only parameter has no \;effect. \;Reading this field for a write-only parameter returns \;unpredicted value." access="RW" high_bound="63" low_bound="0" offset="0x8.0" size="0x100.0" />
</node>

<node name="mrsr_ext" descr="" size="0x8.0" >
	<field name="command" descr="Reset/shutdown command\;0 - do nothing\;1 - software reset\;2 - hardware reset\;3 - enclosure reset (requires system support)\;4 - shutdown (requires system support)\;5 - fast reset" access="WO" offset="0x0.0" size="0x0.4" />
</node>

<node name="mrtc_reg_ext" descr="" size="0x10.0" >
	<field name="time_synced" descr="If set, the time returned in time_l/time_h is the number of micro\;seconds passed since 1/1/1970. \;otherwise, the time_l/time_h measures the time since the NIC \;boot." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="time_h" descr="MSB of timestemp depnding on time_synced" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="time_l" descr="LSB of timestemp depnding on time_synced" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="msci_ext" descr="" size="0xc.0" >
	<field name="index" descr="CPLD index" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="version" descr="CPLD version" access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="msgi_ext" descr="" size="0x80.0" >
	<field name="serial_number" descr="System serial number (ASCII string)" access="RO" high_bound="5" low_bound="0" offset="0x0.0" size="0x18.0" />
	<field name="part_number" descr="System part number (ASCII string)" access="RO" high_bound="4" low_bound="0" offset="0x20.0" size="0x14.0" />
	<field name="revision" descr="Revision (ASCII string)" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="product_name" descr="Product Name (ASCII string)" access="RO" high_bound="15" low_bound="0" offset="0x40.0" size="0x40.0" />
</node>

<node name="msps_ext" descr="" size="0xa0.0" >
	<field name="psu0" descr="System Power Supply 0 Status" access="RO" high_bound="19" low_bound="0" offset="0x0.0" size="0x50.0" />
	<field name="psu1" descr="System Power Supply 1 Status" access="RO" high_bound="19" low_bound="0" offset="0x50.0" size="0x50.0" />
</node>

<node name="mssir_reg_ext" descr="" size="0x80.0" >
	<field name="crc" descr="Each bit represent whether a CRC error occured on \;the management interface to the tile number." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="bypass" descr="Each bit represent whether a bypass clock is run on \;the corresponding tile." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="fatal_dft" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="freq0" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0xC.0" size="0x0.5" />
	<field name="freq1" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0xC.5" size="0x0.5" />
	<field name="freq2" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0xC.10" size="0x0.5" />
	<field name="freq3" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0xC.15" size="0x0.5" />
	<field name="freq4" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0xC.20" size="0x0.5" />
	<field name="freq5" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0xC.25" size="0x0.5" />
	<field name="freq6" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0x10.0" size="0x0.5" />
	<field name="freq7" descr="Each field represent the frequency dividing factor for \;the core clock for each of the tiles" access="RO" offset="0x10.5" size="0x0.5" />
</node>

<node name="mtbr_reg_ext" descr="" size="0x18.0" >
	<field name="base_sensor_index" descr="Base sensor index\;Sensors are read starting from base_sensor_index\;Sensor 0 is the ASIC sensor, sensors 1-63 are ambient sen\;sors and sensors 64-127 are mapped to the SFP+/QSFP \;modules sequentially (module 0 is mapped to sensor 64, \;module 1 to sensor 65 and so on). Gearbox sensors starts \;from 256 index." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="num_rec" descr="Number of records to read\;Range 1..255" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="temperature_record" descr="Temperature record\;See Table 1693, &quot;MTBR - Temperature Record Layout,&quot; \;on page 1989" subnode="mtbr_temp_record_ext" access="RO" high_bound="1" low_bound="0" offset="0x10.0" size="0x8.0" />
</node>

<node name="mtbr_temp_record_ext" descr="" size="0x4.0" >
	<field name="temperature" descr="Temperature reading from the sensor. Units of 0.125 Celsius \;degrees.\;If no ambient sensor is present then the value is &apos;0&apos;. Also for \;a passive copper case.\;0x8000:NO_CONN- No cable or device&apos;s sensor is con\;nected.\;0x8001: NO_TEMP_SENS - In case a cable or device is con\;nected but the temperature sensing is not supported.\;0x8002: INDX_NA- No such cable or device&apos;s sensor index. \;Bigger than the number of modules.\;0x8003: INCORRECT_SENS_INFO - Sensor information is \;incorrect." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.\;When the bit relevant MTMP.mte is cleared, the field max_\;temperature is reserved.\;The value will be &apos;0&apos; for any of the &apos;800X&apos; temperature values \;and for &apos;0&apos; value." access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="mtcap_ext" descr="" size="0x10.0" >
	<field name="sensor_count" descr="Number of sensors supported by the device\;This includes the ASIC and the ambient sensors. QSFP module \;sensors are not included." access="RO" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Only ASIC \;and ambient sensors are supported. Each bit represents a sen\;sor.\;0: Not_connected_or_not_supported\;1: Supports_temperature_measurements" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="mtcq_reg_ext" descr="" size="0x70.0" >
	<field name="status" descr="Indicates the status of the desired token we are gener\;ating the challenge for.\;0x0 - OK\;0x1 - TOKEN_ALREADY_APPLIED\;0x2 - TOKEN_NOT_SUPPORTED\;0x3 - NO_KEY_CONFIGURED (there is no public_key \;that can be used for this token) \;0x4 - INTERFACE_NOT_ALLOWED (asking for local \;token from remote interface, or remote token from \;local interface)" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="token_opcode" descr="The token which a challenge is generated for.\;0: RMSC\;1: RMDT\;\;Other: Reserved" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="keypair_uuid" descr="The UUID of the key used to generate the challenge." access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="base_mac" descr="Device base MAC address / unique identifier." subnode="uint64" access="RO" offset="0x14.0" size="0x8.0" />
	<field name="psid" descr="Device PSID" access="RO" high_bound="3" low_bound="0" offset="0x1C.0" size="0x10.0" />
	<field name="fw_version" descr="Device FW version" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="source_address" descr="Source address of debug requester. DLID for Infini\;band, ETH / IBg2 - TBD.\;Valid only for RMCS/RMDT." access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
	<field name="session_id" descr="Unique debug session identifier. \;See details in REMOTE_DEBUG_KEEP_ALIVE.\;Valid only for RMCS." access="RO" offset="0x44.0" size="0x0.16" />
	<field name="challenge_version" descr="Version of the challenge format." access="RO" offset="0x44.24" size="0x0.8" />
	<field name="challenge" descr="Random generated field. Used for randomness and \;replay-protection." access="RO" high_bound="7" low_bound="0" offset="0x48.0" size="0x20.0" />
</node>

<node name="mtecr_ext" descr="" size="0x60.0" >
	<field name="sensor_count" descr="Number of sensors supported by the device\;This includes the ASIC, ambient sensors, Gearboxes etc. QSFP \;module sensors are not included." access="RO" offset="0x0.0" size="0x0.12" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read from.\;" access="RO" offset="0x0.16" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x4.28" size="0x0.4" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit \;represents a sensor.\;This field is size variable based on the last_sensor field and in \;granularity of 32bits.\;0: Not connected or not supported\;1: Supports temperature measurements" access="RO" high_bound="21" low_bound="0" offset="0x8.0" size="0x58.0" />
</node>

<node name="mtewe_ext" descr="" size="0x5c.0" >
	<field name="sensor_count" descr="Number of sensors supported by the device\;This includes the ASIC, ambient sensors, Gearboxes etc. \;QSFP module sensors are not included." access="RO" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read \;from." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="sensor_warning" descr="Bit vector indicating which of the sensor reading is above \;threshold.\;This field is size dependent and based on last_sensor field \;and in granularity of 32bits." access="RO" high_bound="21" low_bound="0" offset="0x4.0" size="0x58.0" />
</node>

<node name="mtmp_ext" descr="" size="0x20.0" >
	<field name="sensor_index" descr="Sensors index to access.\;\;64-127 of sensor_index are mapped to the SFP+/QSFP \;modules sequentially (module 0 is mapped to sensor_index \;64, module 1 to sensor_index 65 and so on). Gearbox sen\;sors are from index 256 (Gearbox 0 is mapped to sen\;sor_index 256 and so on)" access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="temperature" descr="Temperature reading from the sensor. \;Units of 0.125 Celsius degrees.\;For negative values 2&apos;s complement is used (for example: -\;3.25 Celsius will read as 0xFFE6)" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.\;When the bit mte is cleared, the field max_temperature is \;reserved." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="sdme" descr="Shut Down Events Modify Enable - when set along with \;sdee set to receiving thermal shut down events, all other \;fields of the register are neglected and should not be set." access="OP" offset="0x8.28" size="0x0.1" />
	<field name="weme" descr="Warning Events Modify Enable - when set along with tee set \;to receiving warning events, all other fields of the register \;are neglected and should not be set." access="OP" offset="0x8.29" size="0x0.1" />
	<field name="mtr" descr="Max Temperature Reset - clears the value of the max tem\;perature register" access="OP" offset="0x8.30" size="0x0.1" />
	<field name="mte" descr="Max Temperature Enable - enables measuring the max \;temperature on a sensor" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="temperature_threshold_hi" descr="temperature_threshold_hi refers to the high threshold of \;Warning Event. If the sensor temperature measurement is \;above the threshold (and events are enabled), an event will \;be generated.\;threshold_hi and threshold_lo implements hysteresis \;mechanism of the threshold preventing toggling of the \;indication.\;Note that temperature_threshold_hi must be equal or \;lower than the system requirement.\;System requirement for module is the module warning \;temperature.\;System requirement for board/silicon sensors is according \;to product information parameters\;Note that the temperature threshold can be used to gener\;ate an event message or an interrupt using GPIO" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="sdee" descr="Temperature Shut Down Event Enable (MTSDE Register)\;0: do_not_generate_event\;1: generate_event\;2: generate_single_event\;\;Supported in downstream devices (devices on slots)." access="RW" offset="0xC.28" size="0x0.2" />
	<field name="tee" descr="Temperature Event Enable (MTEWE Register)\;0: do_not_generate_event\;1: generate_event\;2: generate_single_event\;\;Note - Events may be delayed by up to 60 Seconds from \;&quot;generate event&quot; or &quot;generate single event&quot;\;Supported Only for switch devices. For HCA devices, SW \;should register Temperature Warning Event to an EQ." access="RW" enum="do_not_generate_event=0x0,generate_event=0x1,generate_single_event=0x2" offset="0xC.30" size="0x0.2" />
	<field name="temperature_threshold_lo" descr="temperature_threshold_hi refers to the low threshold of \;Warning Event. The offset threshold_lo implements the \;lower threshold for the hysteresis mechanism of over tem\;perature alert. Once alert is set, if the temperature goes \;below this threshold, the alert is cleared.\;Note that temperature_threshold_lo must be at least 5 \;degrees lower than temperature_threshold_hi" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="sensor_name_hi" descr="Sensor Name\;8 character long sensor name" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="sensor_name_lo" descr="Sensor Name\;8 character long sensor name" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mtpps_reg_ext" descr="" size="0x38.0" >
	<field name="cap_max_num_of_pps_out_pins" descr="Maximum number of pps out pins supported on device." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="cap_max_num_of_pps_in_pins" descr="Maximum number of pps in pins supported on device." access="RO" offset="0x0.8" size="0x0.4" />
	<field name="cap_number_of_pps_pins" descr="Total number of pps pins supported on device.\;The virtual pins are not counted here" access="RO" offset="0x0.16" size="0x0.4" />
	<field name="cap_pin_0_mode" descr="Capability of PPS pin #0\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.0" size="0x0.4" />
	<field name="cap_pin_1_mode" descr="Capability of PPS pin #1\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.8" size="0x0.4" />
	<field name="cap_pin_2_mode" descr="Capability of PPS pin #2\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.16" size="0x0.4" />
	<field name="cap_pin_3_mode" descr="Capability of PPS pin #3\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0x8.24" size="0x0.4" />
	<field name="cap_pin_4_mode" descr="Capability of PPS pin #4\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.0" size="0x0.4" />
	<field name="cap_pin_5_mode" descr="Capability of PPS pin #5\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.8" size="0x0.4" />
	<field name="cap_pin_6_mode" descr="Capability of PPS pin #6\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.16" size="0x0.4" />
	<field name="cap_pin_7_mode" descr="Capability of PPS pin #7\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.24" size="0x0.4" />
	<field name="field_select" descr="Field select indicates which fields to modify in write operation to \;this register. This field selector supported only when \;MCAM.mtpps_fs==1. if MCAM.mtpps_fs==0 then SW should \;ensure that all the WO/RW fields are valid. \;Bit 0: enable\;Bit 1: Reserved\;\;Bit 2: pattern\;Bit 3: pin_mode\;Bit 4: time_stamp\;Bit 5: out_pulse_duration\;Bit 6: out_periodic_adjustment\;Bit 7: enhanced_out_periodic_adjustment\;Bit 8: npps\;Bit 9: npps_period\;Bit 10: out_pulse_duration_ns" access="WO" enum="enable=0x1,Reserved=0x2,pattern=0x4,pin_mode=0x8,time_stamp=0x10,out_pulse_duration=0x20,out_periodic_adjustment=0x40,enhanced_out_periodic_adjustment=0x80,npps=0x100,npps_period=0x200,out_pulse_duration_ns=0x400" offset="0x10.0" size="0x4.0" />
	<field name="npps_period" descr="Period between periodical pps signal. The generated period \;depends on device capability and might be rounded.\;&apos;0&apos; disables periodic pps.\;Supported only when pin_mode = 0x01 and \;MCAM.mtpps_npps_period is set.\;Supported only when MTUTC.time_stamp_mode is \;REAL_TIME." subnode="uint64" access="RW" offset="0x14.0" size="0x8.0" />
	<field name="pin" descr="Pin to be configured or queried out of the supported pins." access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="pin_mode" descr="Pin mode to be used. The mode must comply with the supported \;modes of the requested pin.\;0x0: pps_in\;0x1: pps_out\;0x2: virtual_pin\;0x3: pps_out_and_virtual_pin\;\;Operation will fail if pin does not support the required mode." access="RW" enum="pps_in=0x0,pps_out=0x1,virtual_pin=0x2,pps_out_and_virtual_pin=0x3" offset="0x20.8" size="0x0.4" />
	<field name="pattern" descr="When pin_mode = pps_in:\;0x0: Rising edge \;0x1: Falling edge \;\;When pin_mode = pps_out:\;0x0: Pulse - (one shot) The device will generate a pulse at \;time_stamp time with a duration of out_pulse_duration. \;0x1: Periodic - the device will generate periodical pulses with \;pulse duration  of  out_pulse_duration every 1 second according \;to internal clock. The 1st pulse will be generated at time_stamp \;time.\;Reserved when pin_mode = 0x2 virtual_pin\;\;" access="RW" offset="0x20.16" size="0x0.4" />
	<field name="enable" descr="Enables the PPS functionality the specific pin.\;0x0: Disable \;0x1: Enable" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x20.31" size="0x0.1" />
	<field name="out_pulse_duration_ns" descr="Output pulse duration in units of nSec. The generated dura\;tion depends on device capability and might be rounded.\;Default values will be used if set to 0.\;Reserved when pin_mode != ptp_out. This field is mutual \;exclusive with out_pulse_duration. Supported only when \;MCAM.out_pulse_duration_ns is set." access="RW" offset="0x24.0" size="0x0.30" />
	<field name="time_stamp" descr="When pin_mode = pps_in, the latched device time when it was \;triggered from the external GPIO pin. \;When pin_mode = pps_out or virtual_pin or \;pps_out_and_virtual_pin, the target time to generate \;next output signal. \;\;When time_stamp_mode in MTUTC register is \;REAL_TIME, Bits 29:0 are nSec, bits 47:30 are Sec. \;Otherwise, time is in units of device clock. \;" subnode="uint64" access="RW" offset="0x28.0" size="0x8.0" />
	<field name="out_periodic_adjustment" descr="Frequency adjustment: Every PPS the HW frequency will be \;adjusted by this value. Units of HW clock, where HW counts \;10^9 HW clocks for 1 HW second.\;Range is from -32768 to +32767\;The hardware does consecutive frequency adjustment \;Reserved when pin_mode != ptp_out\;Reserved when switches\;" access="RW" offset="0x30.0" size="0x0.16" />
	<field name="out_pulse_duration" descr="Output pulse duration in units of mSec. \;Range is 1 to 1000. \;Reserved when pin_mode != ptp_out\;In case the set value is 0, device default will be used." access="RW" offset="0x30.16" size="0x0.16" />
	<field name="enhanced_out_periodic_adjustment" descr="Same as out_periodic_adjustment field, but supports a wider \;range.\;supported only when \;MCAM.mtpps_enhanced_out_periodic_adjustment==1.\;mutual exclusive with out_periodic_adjustment, i.e. when \;enhanced_out_periodic_adjustment!=0, out_periodic_adjustment \;is invalid.\;Reserved when switches" access="RW" offset="0x34.0" size="0x4.0" />
</node>

<node name="mtptp_ext" descr="" size="0x40.0" >
	<field name="portnumber" descr="Identifying a specific PTP port" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="grandmasteridentity" descr="Up to 8 octets of clock identities. Part of SourcePortIdentity" access="RW" high_bound="7" low_bound="0" offset="0x8.24" size="0x8.0" />
	<field name="time_source" descr="The time source according to timeSource enumeration as \;defined in IEEE 1588 spec:\;0x10: ATOMIC_CLOCK\;0x20: GPS\;0x30: TERRESTRIAL_RADIO\;0x40: PTP\;0x50: NTP\;0x60: HAND_SET\;0x90: OTHER\;0xA0: INTERNAL_OSCILLATOR\;FE-F0: For use by alternate PTP profiles" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="li61" descr="LI-61 (leap61). The last minute of the current UTC day con\;tains 61 seconds. Valid only when utcv is true." access="RW" offset="0x14.8" size="0x0.1" />
	<field name="li59" descr="LI-59 (leap59). The last minute of the current UTC day con\;tains 59 seconds. Valid only when utcv is true." access="RW" offset="0x14.9" size="0x0.1" />
	<field name="utcv" descr="If set to &apos;1&apos;, the current_utc_offset, li61 and li59 are valid." access="RW" offset="0x14.10" size="0x0.1" />
	<field name="ptp" descr="If set to &apos;1&apos;, the" access="RW" offset="0x14.11" size="0x0.1" />
	<field name="ttra" descr="If set to &apos;1&apos;, the timescale and the value of current_utc_off\;set are raceable to primary reference." access="RW" offset="0x14.12" size="0x0.1" />
	<field name="ftra" descr="If set to &apos;1&apos;, the frequency determining the timescale is \;traceable to primary reference." access="RW" offset="0x14.13" size="0x0.1" />
	<field name="current_utc_offset" descr="Equals to TAI-UTC. Valid only when UTCV is true in sec" access="RW" offset="0x14.16" size="0x0.16" />
</node>

<node name="mtrc_cap_reg_ext" descr="" size="0x84.0" >
	<field name="num_string_db" descr="Number of different string sections building the database" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="trc_ver" descr="Indicates the version of the tracing mechanism.\;See, Section 27.3.4.1, &quot;Timestamp Event Traces&quot;, on \;page 1283\;0x0: VER_0\;0x1: VER_1\;other values are reserved" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="trace_to_memory" descr="When set the device supports logging traces to memory" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="trace_owner" descr="Write 0x1 to register for tracer ownership, write 0x0 to de-\;register.\;Read value 0x1 indicates tracer ownership is granted" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="num_string_trace" descr="The number of consecutive event_id that should be inter\;preted as a string trace" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="first_string_trace" descr="The lowest event_id that should be interpreted as a string \;trace" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="log_max_trace_buffer_size" descr="Log 2 of the maximal size of the trace buffer given in units of \;4KB" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="string_db_param" descr="String DB section parameters." subnode="string_db_parameters_ext" access="RO" high_bound="7" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mtrc_conf_reg_ext" descr="" size="0x80.0" >
	<field name="trace_mode" descr="Tracing mode\;0x1: TRACE_TO_MEMORY\;Other values are reserved." access="RW" offset="0x0.0" size="0x0.4" />
	<field name="log_trace_buffer_size" descr="Log 2 of the Size of the trace buffer, given in units of 4KB.\;Value should not exceed log_max_trace_buffer_size.\;Valid only for trace_mode TRACE_TO_MEMORY.\;Modifying this parameter after the tracer was active may \;cause loss of sync regarding the location of the next trace." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="trace_mkey" descr="MKey registered for the trace buffer access.\;Valid only for trace_mode TRACE_TO_MEMORY.\;Modifying this parameter after the tracer was active may \;cause loss of sync regarding the location of the next trace." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mtrc_ctrl_reg_ext" descr="" size="0x40.0" >
	<field name="modify_field_select" descr="Field select indicated which writable fields to modify\;bit 0: trace_status\;Other bits are reserved." access="WO" offset="0x0.0" size="0x0.16" />
	<field name="arm_event" descr="When set, an event will be generated if new Tracer events \;were logged since last event." access="WO" offset="0x0.27" size="0x0.1" />
	<field name="trace_status" descr="Current status of the tracer\;0x0: DISABLED - logging traces is stopped\;0x1: ACTIVE - logging traces is active" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="current_timestamp_52_32" descr="MSB of the current timesatmp counter" access="RO" offset="0x8.0" size="0x0.21" />
	<field name="current_timestamp_31_0" descr="LSB of the current timesatmp counter" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="mtrc_stdb_reg_ext" descr="" size="0xc.0" >
	<field name="read_size" descr="The number of bytes to read from the String DB. The num\;ber of bytes must:\;Be a multiple of 64B\;Not exceed the String DB section (with start_offset)\;Not exceed the limitations defined by the medium carrying the \;Register." access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="string_db_index" descr="The section of the String DB being accessed" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="start_offset" descr="The offset in the String DB to read from, given in Bytes. The \;offset must:\;Be a multiple of 64B\;Not exceed the String DB section (with read_size)" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="string_db_data" descr="Strings from the database. The size of this field is defined by \;read_size" access="RO" high_bound="VARIABLE" low_bound="0" offset="0x8.0" size="0x4.0" />
</node>

<node name="mtutc_reg_ext" descr="" size="0x1c.0" >
	<field name="operation" descr="Operation:\;\;1: SET_TIME_IMMEDIATE - reserved when Spectrum-1\;2: ADJUST_TIME\;3: ADJUST_FREQ_UTC \;4: ADJUST_FREQ_FRC - Free Running Clock\;\;5: CHANGE_TS_CORRECTION_STATUS - For this operation, \;there should be no open SQ with ts_cqe_to_dest_cqn != 0." access="OP" enum="ADJUST_TIME=0x2,ADJUST_FREQ_UTC=0x3,ADJUST_FREQ_FRC=0x4,CHANGE_TS_CORRECTION_STATUS=0x5" offset="0x0.0" size="0x0.4" />
	<field name="time_stamp_state" descr="Internal stamp state\;0: FREE_RUNNING\;1: SYNCED" access="RO" offset="0x0.28" size="0x0.2" />
	<field name="time_stamp_mode" descr="Internal stamp mode\;0: INTERNAL_TIMER\;1: REAL_TIME\;2-3: Reserved." access="RO" offset="0x0.30" size="0x0.2" />
	<field name="freq_adjustment" descr="Frequency adjustment: Every PPS the HW frequency will be \;adjusted by this value. Units of HW clock, where HW counts \;10^9 HW clocks for 1 HW second. The values are represented in \;two&apos;s complement.\;Range is from -50,000,000 to +50,000,000\;Updated when operation is ADJUST_FREQ" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="ts_correction_oper_status" descr="Operational state of the TX timestamp correction daemon:\;0: Disabled\;1: Timestamp correction enabled" access="RO" offset="0x8.0" size="0x0.3" />
	<field name="ts_correction_admin_status" descr="Administrative state of the TX timestamp correction daemon (the \;desired state of the daemon):\;0: Disabled\;1: Timestamp correction enabled\;\;Updated when operation is \;CHANGE_TS_CORRECTION_STATUS" access="RW" offset="0x8.3" size="0x0.3" />
	<field name="utc_sec" descr="UTC seconds\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x10.0" size="0x4.0" />
	<field name="utc_nsec" descr="UTC nSecs\;Range 0..(10^9-1)\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x14.0" size="0x0.30" />
	<field name="time_adjustment" descr="Time adjustment\;Units of nSec\;Range is from -32768 to +32767\;Updated when operation is ADJUST_TIME." access="WO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mtwe_ext" descr="" size="0x10.0" >
	<field name="sensor_warning" descr="Bit vector indicating which of the sensor reading is above \;threshold.\;Address 00h bit31 is sensor_warning[127]\;Address 0Ch bit0 is sensor_warning[0]" access="RO" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="mvcap_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each \;bit represents a sensor.\;0: Not connected or not supported\;1: Supports voltage and current measurements" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x8.0" size="0x0.4" />
</node>

<node name="mvcr_ext" descr="" size="0x18.0" >
	<field name="sensor_index" descr="Sensors index to access\;Mapping of system sensors to index is system specific, and \;detail can be found in the system specification. 64-127 of \;sensor_index are mapped to the SFP+/QSFP modules \;sequentially (module 0 is mapped to sensor_index 64, mod\;ule 1 to sensor_index 65 and so on)." access="INDEX" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="voltage_sensor_value" descr="Voltage reading from the sensor. \;Voltage units are 0.01V." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="current_sensor_value" descr="Current reading from the sensor." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="sensor_name" descr="Sensor Name\;8 character long sensor name" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="ncfg_reg_ext" descr="" size="0x40.0" >
	<field name="field_select" descr="In Query, indicates which fields are supported.\;In Write, indicates which field to modify.\;Bit 0x0: roce_offload_disable" subnode="uint64" access="RW" offset="0x0.0" size="0x8.0" />
	<field name="roce_offload_disable" descr="If set, then ROCE is disabled for VFs/SFs belong to it." access="RW" offset="0x8.0" size="0x0.1" />
</node>

<node name="nvmf_target_pacer_defaults_ext" descr="" size="0x40.0" >
	<field name="modify_field_select" descr="Bitmask indicates which in read which filed can be \;modifiable and in write which field to modify.\;Bit 0x0: enable\;Bit 0x1: pacer_tuner_factor\;Bit 0x2: max_inflight_threshold\;Bit 0x3: min_pacer_period\;Bit 0x4: max_pacer_period\;Bit 0x5: credit_limit\;Bit 0x6: max_credit_limit\;Bit 0x7: read_bypass_block_size\;Bit 0x8: write_bypass_block_size\;Bit 0x9: margin\;Bit 0xA: tuner_time\;Bit 0xB: log_num_pacers_per_port\;Bit 0xC: enable_max_bif_capping" access="RW" enum="enable=0x1,pacer_tuner_factor=0x2,max_inflight_threshold=0x4,min_pacer_period=0x8,max_pacer_period=0x10,credit_limit=0x20,max_credit_limit=0x40,read_bypass_block_size=0x80,write_bypass_block_size=0x100,margin=0x200,tuner_time=0x400,log_num_pacers_per_port=0x800,enable_max_bif_capping=0x1000" offset="0x0.0" size="0x4.0" />
	<field name="pacer_tuner_factor" descr="" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="log_num_pacers_per_port" descr="Log (base 2) of number of pacers per port.\;Must be &lt;= HCA_CAP.log_max_num_pac\;ers_per_port." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="enable_max_bif_capping" descr="Enable/Disable the amount of request to disk from \;pacer limited to the maximum allowed bytes. If this is \;enable then there is no further request to disk if cur\;rent data requested is more than maximum allowed \;bytes.\;0x0: Disable - disable the capping of the request to \;disk to maximum allowed bytes.\;0x1: Enable - enable the capping of the request to \;disk to maximum allowed bytes." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="pacer_mode" descr="0x0 : DEFAULT_PACER_DISABLED\;0x1 : DEFAULT_PACER_ENABLED\;Note that modifying this field must be done before \;creating XRQs." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="max_inflight_threshold" descr="" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="max_pacer_period" descr="" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="min_pacer_period" descr="" access="RW" offset="0xC.16" size="0x0.16" />
	<field name="max_credit_limit" descr="" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="credit_limit" descr="" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="log_write_bypass_block_size" descr="" access="RW" offset="0x14.0" size="0x0.4" />
	<field name="log_read_bypass_block_size" descr="" access="RW" offset="0x14.8" size="0x0.4" />
	<field name="margin" descr="" access="RW" offset="0x14.16" size="0x0.8" />
	<field name="tuner_time" descr="" access="RW" offset="0x18.0" size="0x0.16" />
</node>

<node name="paos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:\;1: up\;2: down\;4: down_by_port_failure - (transitioned by the hard\;ware)\;" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the \;interface):\;1: up\;2: down_by_configuration\;3: up_once - if the port goes up and then down, the \;operational status should go to &quot;down by port failure&quot; \;and can only go back up upon explicit command\;4: disabled_by_system - this mode cannot be set by \;the software, only by the hardware.\;5: up_lowest_rate - when set, if port in down state, \;there will be an attempt to raise the link in the lowest \;available rate. \;\;[Internal] opcode 5 is used only in NIC, for fast link up \;drivers after device boot. For most usecase the rate \;will be SDR, lowest rate support in IB systems. \;\;" access="RW" enum="up=0x1,down_by_configuration=0x2,up_once=0x3,disabled_by_system=0x4,up_lowest_rate=0x5" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the \;router port. In this case, the swid indicates which of \;the router ports to configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="e" descr="Event generation on operational state change:\;0: Do_not_generate_event\;1: Generate_Event \;2: Generate_Single_Event\;\;Not Supported for HCA." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="fd" descr="Force down.\;Supported only when indicated in PCAM\;Can be set only with admin_status = 2 (&apos;down_by_con\;figuration&apos;), will force link to be down. \;" access="RW" offset="0x4.8" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation \;will be updated based on the e field. Only relevant on \;Set operations.\;Not Supported for HCA." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin \;state will be updated based on admin_state field. Only \;relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pbmc_reg_ext" descr="" size="0x6c.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="xoff_refresh" descr="The time before a new pause frame should be sent to \;refresh the pause state. Using the same units as xoff_tim\;er_value above." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_timer_value" descr="When device generates a pause frame, it uses this value as \;the pause timer.\;The pause timer is measured in units of pause &quot;quanta&quot;, \;where each unit is equal to 512 bit times." access="RW" offset="0x4.16" size="0x0.16" />
	<field name="port_buffer_size" descr="Total packet buffer array available for the port. The sum of \;buffer array allocated to bufferX must not exceed \;port_buffer_size.\;In Spectrum and above- Max supported Headroom buffer \;for port. \;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fullness_threshold" descr="Almost full threshold configuration.\;Percentage of buffer fullness which indicates &quot;almost full&quot; \;occurrence\;Range: 0-100%\;Reserved for Switches." access="RW" offset="0x8.16" size="0x0.7" />
	<field name="buffer" descr="Configuring per-buffer parameters. i=0..9\;" subnode="bufferx_reg_ext" access="RW" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="shared_headroom_pool" descr="Configuring shared haeadroom pool parameters. Using the \;same layout as in BufferX, for details see Table 1512, \;&quot;bufferX Register Layout,&quot; on page 1842.\;Not supported in SwitchX and SwitchX-2\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support \;bit)." subnode="uint64" access="RW" offset="0x5C.0" size="0x8.0" />
	<field name="port_shared_buffer" descr="Configuring port shared buffer parameters. Using the same \;layout as in BufferX, for details see Table 1512, &quot;bufferX \;Register Layout,&quot; on page 1842.\;Not supported in SwitchX and SwitchX-2\;Valid for HCA when pbmc_port_shared_buffer is set in \;PCAM." subnode="uint64" access="RW" offset="0x64.0" size="0x8.0" />
</node>

<node name="pbsr_reg_ext" descr="" size="0x64.0" >
	<field name="buffer_type" descr="Valid only for 8x port setting (see PMLP): \;1: Main buffer\;2: Secondary buffer" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear_wm_buff_mask" descr="Each bit represents a stat_buffer\;per bit:\;0: do not clear watermark\;1: clear watermark\;Reserved when clear_wm = 1" access="OP" offset="0x4.0" size="0x0.10" />
	<field name="used_shared_headroom_buffer" descr="Number of currently used shared headroom buffer cells." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="clear_wm" descr="Clear watermarks for all PGs" access="OP" offset="0x8.31" size="0x0.1" />
	<field name="stat_buffer" descr="status per-buffer parameters. i=0..9\;" subnode="stat_bufferx_reg_ext" access="RW" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="stat_shared_headroom_pool" descr="status of shared haeadroom pool parameters. Using the \;same layout as in stat_BufferX, for details see Table 1529, \;&quot;stat_bufferX Register Layout,&quot; on page 1853.\;Not supported in SwitchX and SwitchX-2\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support \;bit)." subnode="stat_bufferx_reg_ext" access="RW" offset="0x5C.0" size="0x8.0" />
</node>

<node name="pcam_reg_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups\;0: RegID_0x5000_to_0x507F\;Values 1-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features \;Values 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="port_access_reg_cap_mask" descr="Supported port&apos;s access register bitmaks. Based on \;access_reg_group index.\;When bit is set , The register is supported in the device. \;When access_reg_group == 0 :\;Bit_0: 0x5000 \;Bit_1: 0x5001 (PCAP)\;Bit_2: 0x5002 (PMLP)\;Bit_3: 0x5003 (PMTU)\;Bit_4: 0x5004 (PTYS)\;.\;.\;Bit_127: 0x507F (PCAM)\;" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="Supported port&apos;s enhanced features. Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bit 0: PPCNT_counter_group_Phy_statistical_counter_group \;Bit 1 - PPCNT_counter_group_Discard_counter_group\;Bit 9: PFCC - support of stall mask and global rx,tx mask. \;Bit 10: PMCR - support of tx_disable override.\;Bit 11: PPCNT_counter_group - IB Extended port counter group\;Bit 12: PPCNT_Extended_Ethernet_group - tx packet size histograms\;Bit 13: PTYS_extended_Ethernet_support\;Bit 14: PMAOS_reset_toggle_support\;Bit 15: Set_Module_low_power_supported \;Bit 16: Module_power_optimization_is_supported_in_PPSC\;Bit 17: Support_of_IB_force_state_machine_in_PTYS - (an_disable)\;Bit 18: PPCNT_Extended_Ethernet_group_icrc_counter\;Bit 19: cm2_en_is_supported_in_PCAP\;Bit 20: time_tolink_up_is_supported_in_PDDR\;Bit 21: gearbox_die_num_field_is_supported_in_PMDR\;Bit 22: force_entropy_entropy_calc_entropy_gre_calc - and capability bits are supported \;in PCMR\;Bit 23: FEC_override_support_for_50G_per_lane_is_supported_in_PPLM\;Bit 25: PTYS_allow_both_extended_and_legacy_protocol_masks\;Bit 26: PPCNT_eth_per_tc_cong_group_supported\;Bit 27: pnat_sup_host - the device supports pnat = 2 (host) when set to &apos;1&apos;\;Bit 28: ppcnt_no_buffer_discard_uc - this counter is supported in PPCNT when set to &apos;1&apos;\;Bit 29: pbmc_port_shared_buffer - supported in PBMC.\;Bit 30: PLR_max_retry_window_support - PPCNT group 0x22 max retry per window\;\;Bit 32: PDDR_ext_eth_proto_support\;Bit 40: PAOS - support of admin_status opcode 5: &quot;up_lowest_rate&quot;\;Bit 41: PMAOS - support of &quot;opertional_notifcation&quot; field\;Bit 42: PRBS_polarity_support - support of polarity bits in PPTT and PPRT \;Bit 43: PDDR_register_is_supported\;Bit 44: pfcc_buffer_onwership - PFCC buffer ownership is supported. \;Bit 45: force_down - supported in PAOS reg.\;Bit 46: pmlp_lane_mapping_off - Support of m_lane_m field in PMLP. \;Bit 51: ppcnt_symobl_ber\;Bit 52: shp_pbmc_pbsr_support\;\;Bit 54: ppcnt_effective_error_counter\;Bit 55: FEC_override_support_for_100G_per_lane_is_supported_in_PPLM\;\;Bit 57: PMECR_option_to_not_generate_events_upon_PMLP_set\;Bit 64: Local_port_MSB - bits [9:8] supported\;Bit 65: PDDR_moule_latched_info_page_supported\;Bit 66: PDDR_module_info_ext_supported\;Bit 67: PMDR.pll_index_supported\;Bit 68: PPCNT.raw_ber_per_lane_supported\;Bit 69: PMMP.sticky_bit_supported\;Bit 70: SLTP_tx_policy_supported\;Bit 71: pmcr_capability_bits_supported\;Bit 72: pmtu_max_admin_mtu_supported\;" access="RO" enum="PPCNT_counter_group_Phy_statistical_counter_group=0x1,PFCC=0x200,PMCR=0x400,PPCNT_counter_group=0x800,PPCNT_Extended_Ethernet_group=0x1000,PTYS_extended_Ethernet_support=0x2000,PMAOS_reset_toggle_support=0x4000,Set_Module_low_power_supported=0x8000,Module_power_optimization_is_supported_in_PPSC=0x10000,Support_of_IB_force_state_machine_in_PTYS=0x20000,PPCNT_Extended_Ethernet_group_icrc_counter=0x40000,cm2_en_is_supported_in_PCAP=0x80000,time_tolink_up_is_supported_in_PDDR=0x100000,gearbox_die_num_field_is_supported_in_PMDR=0x200000,force_entropy_entropy_calc_entropy_gre_calc=0x400000,FEC_override_support_for_50G_per_lane_is_supported_in_PPLM=0x800000,PTYS_allow_both_extended_and_legacy_protocol_masks=0x2000000,PPCNT_eth_per_tc_cong_group_supported=0x4000000,pnat_sup_host=0x8000000,ppcnt_no_buffer_discard_uc=0x10000000,pbmc_port_shared_buffer=0x20000000,PLR_max_retry_window_support=0x40000000,PDDR_ext_eth_proto_support=0x1,PAOS=0x100,PMAOS=0x200,PRBS_polarity_support=0x400,PDDR_register_is_supported=0x800,pfcc_buffer_onwership=0x1000,force_down=0x2000,pmlp_lane_mapping_off=0x4000,ppcnt_symobl_ber=0x80000,shp_pbmc_pbsr_support=0x100000,ppcnt_effective_error_counter=0x400000,FEC_override_support_for_100G_per_lane_is_supported_in_PPLM=0x800000,PMECR_option_to_not_generate_events_upon_PMLP_set=0x2000000,Local_port_MSB=0x1,PDDR_moule_latched_info_page_supported=0x2,PDDR_module_info_ext_supported=0x4,PMDR_pll_index_supported=0x8,PPCNT_raw_ber_per_lane_supported=0x10,PMMP_sticky_bit_supported=0x20,SLTP_tx_policy_supported=0x40,pmcr_capability_bits_supported=0x80,pmtu_max_admin_mtu_supported=0x100" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="pcap_reg_ext" descr="" size="0x14.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cm2_en" descr="port_capability_mask[95:80] is supported if set to &apos;1&apos;." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="port_capability_mask" descr="Sets the PortInfoCapabilityMask:\;Specifies the supported capabilities of this node. A bit set to 1 \;for affirmation of supported capability.\;port_capability_mask[127:96] is mapped to CapabilityMask in \;PortInfo MAD.\;port_capability_mask[95:80] is mapped to CapabilityMask2 in \;PortInfo MAD.\;\;\;" access="RW" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
</node>

<node name="pcie_lanes_counters_ext" descr="" size="0xf8.0" >
	<field name="error_counter_lane0" descr="Number of errors detected on logical lane 0" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="error_counter_lane1" descr="Number of errors detected on logical lane 1" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="error_counter_lane2" descr="Number of errors detected on logical lane 2" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="error_counter_lane3" descr="Number of errors detected on logical lane 3" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="error_counter_lane4" descr="Number of errors detected on logical lane 4" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="error_counter_lane5" descr="Number of errors detected on logical lane 5" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="error_counter_lane6" descr="Number of errors detected on logical lane 6" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="error_counter_lane7" descr="Number of errors detected on logical lane 7" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="error_counter_lane8" descr="Number of errors detected on logical lane 8" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="error_counter_lane9" descr="Number of errors detected on logical lane 9" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="error_counter_lane10" descr="Number of errors detected on logical lane 10" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="error_counter_lane11" descr="Number of errors detected on logical lane 11" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="error_counter_lane12" descr="Number of errors detected on logical lane 12" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="error_counter_lane13" descr="Number of errors detected on logical lane 13" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="error_counter_lane14" descr="Number of errors detected on logical lane 14" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="error_counter_lane15" descr="Number of errors detected on logical lane 15" access="RO" offset="0x44.0" size="0x4.0" />
</node>

<node name="pcie_perf_counters_ext" descr="" size="0xf8.0" >
	<field name="rx_errors" descr="Number of transitions to recovery due to \;Framing errors and CRC (dlp and tlp) errors." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="tx_errors" descr="Number of transitions to recovery due to \;EIEOS and TS errors." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="crc_error_dllp" descr="Number of transitions to recovery due to iden\;tifying CRC DLLP errors" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="crc_error_tlp" descr="Number of transitions to recovery due to iden\;tifying CRC TLP errors" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_overflow_buffer_pkt" descr="The number of packets dropped due to lack of \;PCIe buffers or receive path from NIC port \;toward the hosts." subnode="uint64" access="RO" offset="0x28.0" size="0x8.0" />
	<field name="outbound_stalled_reads" descr="The percentage of time within the last second \;that the NIC had outbound non-posted read \;requests but could not perform the operation \;due to insufficient non-posted credits.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="outbound_stalled_writes" descr="The percentage of time within the last second \;that the NIC had outbound posted writes \;requests but could not perform the operation \;due to insufficient posted credits.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="outbound_stalled_reads_events" descr="The number of events where out\;bound_stalled_reads was above a threshold.\;The threshold is configured by out\;bound_stalled_reads_th in MPEGC.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="outbound_stalled_writes_events" descr="The number of events where out\;bound_stalled_writes was above a threshold.\;The threshold is configured by out\;bound_stalled_writes_th in MPEGC.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="tx_overflow_buffer_marked_pkt" descr="The number of packets marked due to lack of \;PCIe buffers or receive path from NIC port \;toward the hosts.\;Supported only if MCAM.mark_tx_action_cqe \;or MCAM.mark_tx_action_cnp are set to &apos;1&apos;." subnode="uint64" access="RO" offset="0x40.0" size="0x8.0" />
	<field name="effective_ber_coef" descr="Effective_BER = \;effective_ber_coef*10^(-effective_ber_magnitude)" access="RO" offset="0x48.0" size="0x0.4" />
	<field name="effective_ber_magnitude" descr="Effective_BER = \;effective_ber_coef*10^(-effective_ber_magnitude)" access="RO" offset="0x48.8" size="0x0.8" />
</node>

<node name="pcie_timers_states_ext" descr="" size="0xf8.0" >
	<field name="time_to_boot_image_start" descr="Time form start until FW boot image starts running \;in usec. \;Note: can&apos;t be cleared." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_to_link_image" descr="Time form start until FW pci_link image starts run\;ning in usec." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="calibration_time" descr="Time it took FW to do calibration in usec." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_to_first_perst" descr="Time form start until FW handle first prest" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="time_to_detect_state" descr="Time form start until first transition to \;LTSSM.Detect_Q" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="time_to_l0" descr="Time form start until first transition to LTSSM.L0" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="time_to_crs_en" descr="Time form start until crs is enabled" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="time_to_plastic_image_start" descr="Time form start until FW plastic image starts run\;ning in usec." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="time_to_iron_image_start" descr="Time form start until FW iron image starts running \;in usec." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="perst_handler" descr="Number of persts arrived" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="times_in_l1" descr="Number of times LTSSM entered L1 flow" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="times_in_l23" descr="Number of times LTSSM entered L23 flow" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="dl_down" descr="Number of moves for DL_active to DL_down" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="config_cycle1usec" descr="Number of configuration requests that FW handled \;in less then 1 usec" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="config_cycle2to7usec" descr="Number of configuration requests that FW handled \;within 2 to 7 usec" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="config_cycle8to15usec" descr="Number of configuration requests that FW handled \;within 8 to 15 usec" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="config_cycle16to63usec" descr="Number of configuration requests that FW handled \;within 16 to 63 usec" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="config_cycle64usec" descr="Number of configuration requests that FW handled \;took more than 64 usec" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="correctable_err_msg_sent" descr="Number of correctable error msg sent" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="non_fatal_err_msg_sent" descr="Number of Non-Fatal error msg sent" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fatal_err_msg_sent" descr="Number of Fatal error msg sent" access="RO" offset="0x58.0" size="0x4.0" />
</node>

<node name="pcmr_reg_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fcs_cap" descr="Specifies the check enable/disable capabilities of the local \;port. A bit set to 1 for affirmation of supported enable/disable \;capability: \;FCS check disable/enable capability" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="rx_ts_over_crc_cap" descr="Specifies the ingress timestamps enable/disable capabilities \;of the local port. A bit set to 1 for affirmation of supported \;enable/disable capability:" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="rx_fcs_drop_cap" descr="Specifies the ingress drop enable/disable capabilities of the \;local port. A bit set to 1 for affirmation of supported enable/\;disable capability:" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="tx_fcs_recalc_cap" descr="Specifies the egress drop enable/disable capabilities of the \;local port. A bit set to 1 for affirmation of supported enable/\;disable capability:" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="tx_ts_over_crc_cap" descr="Specifies the egress timestamps enable/disable capabilities of \;the local port. A bit set to 1 for affirmation of supported \;enable/disable capability:" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="entropy_gre_calc_cap" descr="Specifies the egress GRE tunnel protocol entropy calculation \;enable/disable capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capa\;bility:" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="entropy_calc_cap" descr="Specifies the egress tunnel protocol entropy calculation \;enable/disable capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capa\;bility:" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="force_entropy_cap" descr="Specifies the egress tunnel protocol entropy calculation force \;capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capa\;bility:" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="fcs_chk" descr="FCS check\;Values:\;0: disable check. \;1: perform check\;Note: when disabling a check, it will also affects the relevant count\;ers." access="RW" offset="0x8.1" size="0x0.1" />
	<field name="rx_ts_over_crc" descr="RX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS" access="RW" offset="0x8.13" size="0x0.1" />
	<field name="rx_fcs_drop" descr="RX FCS drop control:\;0: ingress port will drop a packet with bad FCS (Default)\;1: ingress port will not drop a packet with bad FCS\;NOTE: All FCS counters (PPCNT) are valid for both drop \;modes.\;NOTE: Reserved when PCMR.fcs_cap=1 &amp; PCMR.fcs_chk=0" access="RW" offset="0x8.14" size="0x0.1" />
	<field name="tx_fcs_recalc" descr="TX FCS drop control:\;0: egress port will recalculate and overwrite FCS value \;(Default) \;1: egress port will not overwrite FCS value \;NOTE: when this bit is set, any modification of the packet will \;result in a bad FCS." access="RW" offset="0x8.15" size="0x0.1" />
	<field name="tx_ts_over_crc" descr="TX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Reserved when tx_fcs_recalc is set" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="entropy_gre_calc" descr="0: DISABLE - entropy calculation is disabled for GRE tunneling \;protocol.\;1: ENABLE - entropy calculation is enabled for GRE tunneling \;protocol, if entropy_calc is enabled as well. valid only if \;force_entropy is activated." access="RW" offset="0x8.29" size="0x0.1" />
	<field name="entropy_calc" descr="0: DISABLE - entropy calculation is disabled for all supported \;tunneling protocols.\;1: ENABLE - entropy calculation is enabled for all supported \;tunneling protocols. GRE also depends on the entropy_gre_\;calc valid only if force_entropy is activated." access="RW" offset="0x8.30" size="0x0.1" />
	<field name="force_entropy" descr="0: DEFAULT - use device defaults for tunnel entropy calcula\;tion. This mode should be used if entropy calculation require\;ment is unknown.\;1: FORCE - force the entropy calculation according to entro\;py_calc and entropy_gre_calc." access="RW" offset="0x8.31" size="0x0.1" />
</node>

<node name="pddr_advanced_opcode_ext" descr="" size="0x4.0" >
	<field name="advanced_opcode" descr="Status opcode: \;PHY FW indication (0 - 1023):\;0 - No issue observed\;1 - Port is close by command (see PAOS).\;2 - AN no partner detected.\;3 - AN ack not received. \;4 - AN next-page exchange failed. \;5 - KR frame lock not acquired.\;6 - KR link inhibit timeout \;7 - KR Link partner didn&apos;t set receiver ready\;8 - KR tuning didn&apos;t completed \;9 - PCS didn&apos;t acquire block lock. \;10 - PCS didn&apos;t acquire AM lock (NO FEC) \;11 - PCS didn&apos;t get align_status.\;12 - FC FEC isn&apos;t locked\;13 - RS FEC isn&apos;t locked\;14 - Remote fault received\;15 - Bad Signal integrity \;16 - Compliance code mismatch (protocol mismatch between cable and port)\;17 - Large number of physical errors (high BER). \;18 - Port is disabled by Ekey\;19- Phase EO failure\;20- stamping of Non Mellanox Cables/Modules\;21 - Down by PortInfo MAD\;22 - Disabled by Verification\;23 - Calibration failure\;24 - EDR speed is not allowed due to cable stamping: EDR stamping\;25 - FDR10 speed is not allowed due to cable stamping: FDR10 stamping\;26 - Port is closed due to cable stamping: Ethernet_compliace_code_zero\;27 - Port is closed due to cable stamping: 56GE stamping\;28 - Port is closed due to cable stamping: non-Mellanox QSFP28\;29 - Port is closed due to cable stamping: non-Mellanox SFP28\;30 - Port is closed, no backplane enabled speed over backplane channel\;31 - Port is closed, no passive protocol enabled over passive copper channel\;32 - Port is closed, no active protocol enabled over active channel\;33 - Port width is doesn&apos;t match the port speed enabled\;34 - Local speed degradation\;35 - Remote speed degradation\;36 - No Partner detected during force mode. \;37 - Partial link indication during force mode. \;38 - AN Failure - FEC mismatch during override \;39 - AN Failure - No HCD\;40 - VPI protocol don&apos;t match\;41 - Port is closed, module can&apos;t be set to the enabled rate\;42 - Bad SI, cable is configured to non optimal rate \;43 - No Partner detected during force mode, while port is running fast link-up\;44 - Partial link indication during force mode, while port is running fast link-up\;45 - Main USR logic didn&apos;t get align_status.\;46 - Tile USR logic didn&apos;t get align_status;\;47 - no CDR lock\;48 - uphy_peq_adc_overload\;49 - uphy_feq_adc_overload\;50 - uphy_imem_chksm_error\;51 -hst_mismatch\;52 - eq_fail\;53 - link_fail_due_mcb_at_linkup \;54 - plr_didnt_get_rx_good_non_sync_cell\;55 - psi_fatal_error\;56 - module_lanes_frequency_not_synced\;128 - Troubleshooting in process\;1023- Info not available\;MNG FW issues (1024 - 2047):\;1024 - Cable is unplugged/powered off\;1025 - Long Range for non MLNX cable/module .\;1026 - Bus stuck (I2C Data or clock shorted) \;1027 - bad/unsupported EEPROM \;1028 - part number list\;1029 - unsupported cable.\;1030 - module temperature shutdown\;1031 - Shorted cable\;1032 - Power Budget Exceeded\;1033 - Management force down the port\;1034 - Module is disabled by command\;1035 - System Power is Exceeded therefore the module is powered off. \;1036 - Module&apos;s PMD type is not enabled (see PMTPS).\;1042 -CMIS Module State didn&apos;t reach ModuleReady state\;1043 - NDR speed is not allowed due to cable stamping: NDR stamping\;1044 - HDR speed is not allowed due to cable stamping: HDR stamping\;1045 - EDR speed is not allowed due to cable stamping: EDR stamping\;1046 - FDR10 speed is not allowed due to cable stamping: FDR10 stamping\;1047 - CMIS unsupported application\;1048 - CMIS Datapath didn&apos;t reach DPActivated after apply\;1049 - Link could not be raised due to module configured to test mode\;Core/Driver (2048 - 3072):" access="RW" offset="0x0.0" size="0x0.16" />
</node>

<node name="pddr_c2p_link_enabed_eth_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_pro\;to_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_c2p_link_enabed_ib_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_proto_enabled" descr="ib link enabled speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80" offset="0x0.0" size="0x0.16" />
	<field name="core_to_phy_link_width_enabled" descr="ib link enabled width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;Bit 3: 8x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_cable_cap_eth_ext" descr="" size="0x4.0" >
	<field name="cable_ext_eth_proto_cap" descr="Cable Ethernet protocols cap. \;If PTYS.ext_eth_proto_cap filed is supported, use for \;opcode definition PTYS.ext_eth_proto_cap\;If PTYS.ext_eth_proto_capability mask is empty, use For \;opcode definition PTYS.eth_proto_cap." access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_ib_ext" descr="" size="0x4.0" >
	<field name="cable_link_speed_cap" descr="Cable support IB speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80" offset="0x0.0" size="0x0.16" />
	<field name="cable_link_width_cap" descr="Cable support IB width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;Bit 3: 8x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_device_events_page_ext" descr="" size="0xf8.0" >
	<field name="invalid_port_access_sv" descr="invalid port access severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="pll_state_mask_center0" descr="" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="pll_state_sv_0" descr="PLL invalid state severity for center0" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="pll_state_mask_center1" descr="" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="pll_state_sv_1" descr="PLL invalid state severity for center1" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="varactors_calib_fail_center0" descr="" access="RO" offset="0x8.0" size="0x0.1" />
	<field name="varactors_calib_fail_center0_sv" descr="" access="RO" offset="0x8.1" size="0x0.1" />
	<field name="varactors_calib_fail_center1" descr="" access="RO" offset="0x8.2" size="0x0.1" />
	<field name="varactors_calib_fail_center1_sv" descr="" access="RO" offset="0x8.3" size="0x0.1" />
	<field name="logical_phy_to" descr="PLU timeout indication" access="RO" offset="0x8.4" size="0x0.1" />
	<field name="logical_phy_to_sv" descr="PLU timeout severity" access="RO" offset="0x8.5" size="0x0.1" />
	<field name="analog_phy_to" descr="SerDes timeout indication" access="RO" offset="0x8.6" size="0x0.1" />
	<field name="analog_phy_to_sv" descr="SerDes timeout severity" access="RO" offset="0x8.7" size="0x0.1" />
	<field name="cr_space_timeout" descr="" access="RO" offset="0x8.16" size="0x0.1" />
	<field name="cr_space_timeout_sv" descr="" access="RO" offset="0x8.17" size="0x0.1" />
	<field name="cr_space_timeout_mcm_main" descr="" access="RO" offset="0x8.18" size="0x0.1" />
	<field name="plu_timeout4" descr="HDR: -\;NDR: serdes" access="RO" offset="0x8.25" size="0x0.1" />
	<field name="plu_timeout3" descr="HDR: pll\;NDR: pmux" access="RO" offset="0x8.26" size="0x0.1" />
	<field name="plu_timeout2" descr="HDR: serdes_1\;NDR: plrx[1]" access="RO" offset="0x8.27" size="0x0.1" />
	<field name="plu_timeout1" descr="HDR: serdes_0\;NDR: plrx[0]" access="RO" offset="0x8.28" size="0x0.1" />
	<field name="plu_timeout0" descr="HDR: plu\;NDR: pltx" access="RO" offset="0x8.29" size="0x0.1" />
	<field name="tile_irisc_timeout" descr="" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="main_irisc_timeout" descr="" access="RO" offset="0x8.31" size="0x0.1" />
	<field name="irisc_stuck_mask_sv" descr="" access="RO" offset="0xC.31" size="0x0.1" />
	<field name="pll_unlocl_mask_center0" descr="" access="RO" offset="0x14.0" size="0x0.4" />
	<field name="pll_lock_sv_0" descr="" access="RO" offset="0x14.8" size="0x0.1" />
	<field name="pll_unlocl_mask_center1" descr="" access="RO" offset="0x14.16" size="0x0.4" />
	<field name="pll_lock_sv_1" descr="" access="RO" offset="0x14.24" size="0x0.1" />
	<field name="iopl_err_center0" descr="" access="RO" offset="0x18.0" size="0x0.1" />
	<field name="iopl_err_center0_sv" descr="" access="RO" offset="0x18.1" size="0x0.1" />
	<field name="iopl_err_center1" descr="" access="RO" offset="0x18.2" size="0x0.1" />
	<field name="iopl_err_center1_sv" descr="" access="RO" offset="0x18.3" size="0x0.1" />
	<field name="pwr_governor_err" descr="" access="RO" offset="0x18.16" size="0x0.1" />
	<field name="pwr_governor_err_sv" descr="" access="RO" offset="0x18.17" size="0x0.1" />
	<field name="uc_crspace_timeout" descr="uC crspace timeout event. See uc_scrspace_timeout_cl and \;uc_scrspace_timeout_lane for location of last event" access="RO" offset="0x18.24" size="0x0.1" />
	<field name="uc_stack_overflow" descr="uC stack overflow event. See uc_stack_overflow_cl and \;uc_stack_overflow_lane for location of last event" access="RO" offset="0x18.25" size="0x0.1" />
	<field name="clr_mask" descr="Valid only when PDDR.clr is set\;Bit mask for page bits 255:0, when bits 31:0 assigned to off\;set 00h bits 31:0.\;bits 63:32 assigned to offset 04h bits 31:0.\;bits 95:64 assigned to offset 08h bits 31:0.\;bits 127:69 assigned to offset 0Ch bits 31:0.\;Only when PDDR.clr is set and the appropriate bit in the \;mask is set, the event will be cleared" access="OP" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="main_irisc_address" descr="" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="main_irisc_ip" descr="" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="tile_irisc_address" descr="" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="tile_irisc_ip" descr="" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="plu_timeout1_address" descr="" access="RO" offset="0x50.0" size="0x0.16" />
	<field name="plu_timeout0_address" descr="" access="RO" offset="0x50.16" size="0x0.16" />
	<field name="plu_timeout3_address" descr="" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="plu_timeout2_address" descr="" access="RO" offset="0x54.16" size="0x0.16" />
	<field name="plu_timeout4_address" descr="" access="RO" offset="0x58.16" size="0x0.16" />
	<field name="plu_timeout3_cluster" descr="" access="RO" offset="0x5C.0" size="0x0.6" />
	<field name="plu_timeout2_cluster" descr="" access="RO" offset="0x5C.8" size="0x0.6" />
	<field name="plu_timeout1_cluster" descr="" access="RO" offset="0x5C.16" size="0x0.6" />
	<field name="plu_timeout0_cluster" descr="" access="RO" offset="0x5C.24" size="0x0.6" />
	<field name="irisc_tile_idx" descr="" access="RO" offset="0x60.0" size="0x0.4" />
	<field name="plu_timeout4_cluster" descr="" access="RO" offset="0x60.24" size="0x0.6" />
	<field name="uc_stack_overflow_cl" descr="" access="RW" offset="0x64.0" size="0x0.6" />
	<field name="uc_stack_overflow_lane" descr="" access="RW" offset="0x64.8" size="0x0.3" />
	<field name="uc_crspace_timeout_cl" descr="" access="RW" offset="0x64.16" size="0x0.6" />
	<field name="uc_crspace_timeout_lane" descr="" access="RW" offset="0x64.24" size="0x0.3" />
</node>

<node name="pddr_link_active_eth_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active : see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_active_ib_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="ib link active speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="ib link active width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;Bit 3: 8x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_link_down_events_page_ext" descr="" size="0x20.0" >
	<field name="ib_port_events" descr="Bit mask for IB port causes:\;Bit 0: ts_at_linkup\;Bit 1: ibl_link_retrain\;Bit 2: rx_comskp_timeout\;Bit 3: minor_threshold_reached\;Bit 4: watch_dog\;Bit 5: excessive_buffer\;Bit 6: lli_err\;Bit 7: llr_link_retrain\;Bit 8: block_lock\;Bit 9: skip_or_COM_alignment_loss\;Bit 10: FEC_lock_loss\;Bit 11: MAD_down_command" access="RO" enum="ts_at_linkup=0x1,ibl_link_retrain=0x2,rx_comskp_timeout=0x4,minor_threshold_reached=0x8,watch_dog=0x10,excessive_buffer=0x20,lli_err=0x40,llr_link_retrain=0x80,block_lock=0x100,skip_or_COM_alignment_loss=0x200,FEC_lock_loss=0x400,MAD_down_command=0x800" offset="0x0.0" size="0x4.0" />
	<field name="etherent_port_events" descr="Bit 0: remote_fault_at_linkup\;Bit 1: PCS_hi_ber_event\;Bit 2: FEC_hi_ser_event\;Bit 3: Block_lock_loss\;Bit 4: Alignment_loss\;Bit 5: FEC_block_lock_loss\;Bit 6" access="RO" enum="remote_fault_at_linkup=0x1,PCS_hi_ber_event=0x2,FEC_hi_ser_event=0x4,Block_lock_loss=0x8,Alignment_loss=0x10,FEC_block_lock_loss=0x20" offset="0x8.0" size="0x4.0" />
	<field name="general_port_events" descr="Bit 0: fifo_full_err\;Bit 1: PAOS_down_command\;Bit 2: disable_mask_event\;Bit 3: port_event - (see page 4 of PDDR)\;Bit 4: device_event - (see page 5 of PDDR)\;Bit 5: spike_detected - TBD analog capability?" access="RO" enum="fifo_full_err=0x1,PAOS_down_command=0x2,disable_mask_event=0x4,port_event=0x8,device_event=0x10,spike_detected=0x20" offset="0x10.0" size="0x4.0" />
</node>

<node name="pddr_link_down_info_ext_16nm_lr_ext" descr="" size="0xf8.0" >
	<field name="cause_fec_rx_sync_m_reached_max0" descr="" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="cause_deskew_fifo_overrun" descr="" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="cause_tx_lane_fifo_underrun_l0" descr="" access="RO" offset="0x0.16" size="0x0.2" />
	<field name="cause_rs_rx_lane0_symbol_error" descr="" access="RO" offset="0x0.18" size="0x0.2" />
	<field name="cause_high_ser" descr="" access="RO" offset="0x0.20" size="0x0.2" />
	<field name="cause_as_detected_not_on_slot" descr="" access="RO" offset="0x0.22" size="0x0.2" />
	<field name="symbol_error_counter_lo" descr="" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="symbol_error_counter_hi" descr="" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="uncorrectable_block_counter_lo" descr="" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="uncorrectable_block_counter_hi" descr="" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="block_lock_mask_at_fail_port0" descr="" access="RO" offset="0x14.0" size="0x0.4" />
	<field name="block_lock_mask_at_fail_port1" descr="" access="RO" offset="0x14.4" size="0x0.4" />
	<field name="link_fail_due_align_loss" descr="" access="RO" offset="0x14.8" size="0x0.1" />
	<field name="link_down_counter" descr="" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="raw_ber_magnitude" descr="" access="RO" offset="0x1C.0" size="0x0.4" />
	<field name="raw_ber_coef" descr="" access="RO" offset="0x1C.4" size="0x0.8" />
	<field name="effective_ber_magnitude" descr="" access="RO" offset="0x1C.12" size="0x0.4" />
	<field name="effective_ber_coef" descr="" access="RO" offset="0x1C.16" size="0x0.8" />
</node>

<node name="pddr_link_down_info_page_ext" descr="" size="0x30.0" >
	<field name="down_blame" descr="Which receiver caused last link down: \;0: Unknown\;1: Local_phy\;2: Remote_phy" access="RO" enum="Unknown=0x0,Local_phy=0x1,Remote_phy=0x2" offset="0x0.0" size="0x0.4" />
	<field name="local_reason_opcode" descr="Opcde of link down reason: \;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_SER_or_Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Thermal_shutdown \;26: Current_issue \;27: Power_budget\;" access="RO" enum="No_link_down_indication=0x0,Unknown_reason=0x1,Hi_SER_or_Hi_BER=0x2,Block_Lock_loss=0x3,Alignment_loss=0x4,FEC_sync_loss=0x5,PLL_lock_loss=0x6,FIFO_overflow=0x7,false_SKIP_condition=0x8,Minor_Error_threshold_exceeded=0x9,Physical_layer_retransmission_timeout=0xa,Heartbeat_errors=0xb,Link_Layer_credit_monitoring_watchdog=0xc,Link_Layer_integrity_threshold_exceeded=0xd,Link_Layer_buffer_overrun=0xe,Down_by_outband_command_with_healthy_link=0xf,Down_by_outband_command_for_link_with_hi_ber=0x10,Down_by_inband_command_with_healthy_link=0x11,Down_by_inband_command_for_link_with_hi_ber=0x12,Down_by_verification_GW=0x13,Received_Remote_Fault=0x14,Received_TS1=0x15,Down_by_management_command=0x16,Cable_was_unplugged=0x17,Cable_access_issue=0x18,Thermal_shutdown=0x19,Current_issue=0x1a,Power_budget=0x1b" offset="0x4.0" size="0x0.8" />
	<field name="remote_reason_opcode" descr="see local_reason_opcode" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="e2e_reason_opcode" descr="see local_reason_opcode for local reason opcode\;for remote reason opcode: local_reason_opcode+100" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="ber_exp" descr="" access="RO" offset="0x10.0" size="0x0.8" />
	<field name="ber_mantissa" descr="" access="RO" offset="0x10.8" size="0x0.4" />
	<field name="last_ber_exp" descr="" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="last_ber_mantissa" descr="" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="max_ber_exp" descr="" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="max_ber_mantissa" descr="" access="RO" offset="0x14.8" size="0x0.4" />
	<field name="min_ber_exp" descr="" access="RO" offset="0x14.16" size="0x0.8" />
	<field name="min_ber_mantissa" descr="" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="num_of_ber_alarams" descr="" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="time_to_link_down_to_disable" descr="Time in msec to link down to disable state, once a paos down \;is set or a link down event occurs.\;If the phy manager state is different then disable the timer \;will return 0." access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="time_to_link_down_to_rx_loss" descr="Time in msec to link down to rx disable state, once a link \;down event occurs.\;If the phy manager state is different then rx disable the timer \;will return 0.\;Internal: Only for NDR devices." access="RO" offset="0x20.0" size="0x4.0" />
</node>

<node name="pddr_link_up_info_page_ext" descr="" size="0xf8.0" >
	<field name="up_reason_mng" descr="invalid port access severity\;0 - No down command / unknown\;1 - BMC force linkup\;2 - WOL force linkup\;\;3 - ASN.1 force link up" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="up_reason_drv" descr="invalid port access severity\;0 - No down command / unknown\;1 - Up by at least one of the hosts" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="up_reason_pwr" descr="invalid port access severity\;0 - No down command / unknown\;1 - Keep link up on boot \;2 - Keep link up Eth/IB\;3 - Keep link up on standby" access="RO" offset="0x0.16" size="0x0.4" />
	<field name="time_to_link_up" descr="Time in msec to link up from disable until phy up state.\;While the phy manager did not reach phy up state the timer \;will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while \;working at force mode." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="fast_link_up_status" descr="Indicates if fast link-up was performed in the link: \;0: Unknown\;1: Fast Link-UP was performed. \;2: Regular link-up flow was performed due to changes in \;cable\;3: Regular link-up flow was performed due to changes in pro\;tocol (speed or FEC)\;4: Regular link-up flow was performed due to a non-fastboot\;able FW version (PCNR is not supported)\;5: Regular link-up performed due to MLPN flow\;6: Regular link-up performed due to PCNR.tuning_override \;configuration while port was in &quot;down&quot; state.\;7: Invalid fastboot data struct (0xCAFECAFE magic value is \;not present. For example, SW reset was executed before fin\;ish saving data during PCNR flow)\;8 - fast link-up timeout\;9 - fast link-up flaps issue\;10 - fast link-up failed during link-up" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="time_to_link_up_phy_up_to_active" descr="Time in msec to link up from phy up until active state.\;While the phy manager did not reach active state the timer \;will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while \;working at force mode." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="time_to_link_up_sd_to_phy_up" descr="Time in msec to link up from signal detect until phy up state.\;While the phy manager did not reach phy up state the timer \;will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while \;working at force mode." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_to_link_up_disable_to_sd" descr="Time in msec to link up from disable until signal detect state.\;While the phy manager did not reach signal detect state the \;timer will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while \;working at force mode.\;Internal: for HDR/EDR devices the timers: time_to_link_up_\;disable_to_sd, time_to_link_up_disable_to_pd will return \;the same value." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="time_to_link_up_disable_to_pd" descr="Time in msec to link up from disable until protocol detect \;state.\;While the phy manager did not reach protocol detect state the \;timer will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while \;working at force mode.\;Internal: for HDR/EDR devices the timers: time_to_link_up_\;disable_to_sd, time_to_link_up_disable_to_pd will return \;the same value." access="RO" offset="0x18.0" size="0x4.0" />
</node>

<node name="pddr_mng_debug_page_ext" descr="" size="0xf8.0" >
	<field name="fw_module_state" descr="Module FSM state:\;\;0x0: MS_READ_CHOOSE_MODULE\;0x1: MS_READ_DEACTIVATE_LANES_STATE\;0x2: MS_READ_VERFIY_MODULE_STATE\;0x3: MS_READ_SET_APPLY\;0x4: MS_READ_SET_DATAPATH_INIT\;0x5: MS_READ_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: MS_READ_MODULE_STATE_READ\;0x7: MS_READ_FINISH\;" access="RO" enum="MS_READ_CHOOSE_MODULE=0x0,MS_READ_DEACTIVATE_LANES_STATE=0x1,MS_READ_VERFIY_MODULE_STATE=0x2,MS_READ_SET_APPLY=0x3,MS_READ_SET_DATAPATH_INIT=0x4,MS_READ_UPDATE_MODULE_DB_ACTIVE_SET=0x5,MS_READ_MODULE_STATE_READ=0x6,MS_READ_FINISH=0x7" offset="0x0.0" size="0x0.4" />
	<field name="fw_dp_state_lane0" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="fw_dp_state_lane1" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="fw_dp_state_lane2" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="fw_dp_state_lane3" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="fw_dp_state_lane4" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="fw_dp_state_lane5" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" offset="0x4.20" size="0x0.4" />
	<field name="fw_dp_state_lane6" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="fw_dp_state_lane7" descr="FW FSM current state for each lane\;\;0x0: LANE_STATE_NOT_IN_USE\;0x1: LANE_STATE_DEACTIVATE_PAOS\;0x2: LANE_STATE_DEACTIVATE_SPEED_OR_AP\;PLY_CHANGE\;0x3: LANE_STATE_VERIFY\;0x4: LANE_STATE_SET_APPLY \;0x5: LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET\;0x6: LANE_STATE_ACTIVATE_LANE \;0x7: LANE_STATE_VERIFY_ACTIVATE \;0x8: LANE_STATE_ACTIVE" access="RO" enum="LANE_STATE_NOT_IN_USE=0x0,LANE_STATE_DEACTIVATE_PAOS=0x1,LANE_STATE_DEACTIVATE_SPEED_OR_APPLY_CHANGE=0x2,LANE_STATE_VERIFY=0x3,LANE_STATE_SET_APPLY=0x4,LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET=0x5,LANE_STATE_ACTIVATE_LANE=0x6,LANE_STATE_VERIFY_ACTIVATE=0x7,LANE_STATE_ACTIVE=0x8" offset="0x4.28" size="0x0.4" />
	<field name="dp_req_status_lane0" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="dp_req_status_lane1" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" offset="0x8.4" size="0x0.4" />
	<field name="dp_req_status_lane2" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" offset="0x8.8" size="0x0.4" />
	<field name="dp_req_status_lane3" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" offset="0x8.12" size="0x0.4" />
	<field name="dp_req_status_lane4" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" offset="0x8.16" size="0x0.4" />
	<field name="dp_req_status_lane5" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" offset="0x8.20" size="0x0.4" />
	<field name="dp_req_status_lane6" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" offset="0x8.24" size="0x0.4" />
	<field name="dp_req_status_lane7" descr="CMIS Error Code Status:\;\;0x0:CONFIG_UNDEFINED\;0x1: CONFIG_SUCCESS\;0x2: CONFIG_REJECTEC_UNKOWN_REASON\;0x3: CONFIG_REJECTEC_INVALID_APPSEL\;0x4: CONFIG_REJECTEC_INVALID_DATAPATH\;0x5: CONFIG_REJECTEC_INVALID_SI\;0x6: CONFIG_REJECTEC_LANE_IN_USE\;0x7: CONFIG_REJECTEC_PARTIAL_DATAPATH \;0xB: CONFIG_FAILED\;0XC: CONFIG_IN_PROGRESS\;0XD: CUSTOM_REJECTED_VENDOR_SPECIFIC" access="RO" enum="CONFIG_UNDEFINED=0x0,CONFIG_SUCCESS=0x1,CONFIG_REJECTEC_UNKOWN_REASON=0x2,CONFIG_REJECTEC_INVALID_APPSEL=0x3,CONFIG_REJECTEC_INVALID_DATAPATH=0x4,CONFIG_REJECTEC_INVALID_SI=0x5,CONFIG_REJECTEC_LANE_IN_USE=0x6,CONFIG_REJECTEC_PARTIAL_DATAPATH=0x7,CONFIG_FAILED=0xb,CONFIG_IN_PROGRESS=0xc,CUSTOM_REJECTED_VENDOR_SPECIFIC=0xd" offset="0x8.28" size="0x0.4" />
	<field name="dpsm_apply_state_lane0" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.0" size="0x0.4" />
	<field name="dpsm_apply_state_lane1" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.4" size="0x0.4" />
	<field name="dpsm_apply_state_lane2" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.8" size="0x0.4" />
	<field name="dpsm_apply_state_lane3" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.12" size="0x0.4" />
	<field name="dpsm_apply_state_lane4" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.16" size="0x0.4" />
	<field name="dpsm_apply_state_lane5" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.20" size="0x0.4" />
	<field name="dpsm_apply_state_lane6" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.24" size="0x0.4" />
	<field name="dpsm_apply_state_lane7" descr="DPSM state that was applied in per lane\;\;" access="RO" offset="0xC.28" size="0x0.4" />
</node>

<node name="pddr_module_info_ext" descr="" size="0xf8.0" >
	<field name="ethernet_compliance_code" descr="QSFP:\;Ethernet Compliance Codes bit mask (10/40G/100G)\;Byte131 per SFF-8636 \;Bit 7 - Extended Specification Compliance valid\;Bit 6 - 10GBASE-LRM\;Bit 5 - 10GBASE-LR\;Bit 4 - 10GBASE-SR\;Bit 3 - 40GBASE-CR4\;Bit 2 - 40GBASE-SR4\;Bit 1 - 40GBASE-LR4\;Bit 0 - 40G Active Cable (XLPPI)\;\;SFP : \;10G Ethernet Compliance Codes\;Byte3 per SFF-8472:\;Bit 7 - 10G Base-ER \;Bit 6 - 10G Base-LRM \;Bit 5 - 10G Base-LR \;Bit 4 - 10G Base-SR\;\;CMIS based (QSFP-DD/ SFP-DD / OSFP)\;Byte 87 - Module Media Interface" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes \;for SFP:\;byte 36 per SFF-8472\;\;for QSFP:\;byte192 per SFF-8636 (QSFP28) \;\;for CMIS (SFP-DD / QSFP-DD/ OSFP):\;Byte 86 - Host Electrical Interface" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="cable_breakout" descr="Reserved for SFP. \;\;For QSFP:\;Byte113 per SFF-8636\;\;For CMIS based modules:\;\;XX naming is according to cable_identifier name\;For example: if cable_identifier = ,6 XX string is QSFP-DD\;\;0 - Unspecified\;1 - XX to XX\;2 - XX to 2xQSFP or 2xXX (depopulated / 4 lanes)\;3 - XX to 4xDSFP or 4xQSFP (depopulated / 2 lanes)\;4 - XX to 8xSFP\;5 - XX (depopulated / 4 lanes) to QSFP or XX (depopulated / 4 \;lanes)\;6 - XX (depopulated / 4 lanes) to 2xXX(depopulated / 2 lanes) \;or 2xSFP-DD\;7 - XX (depopulated / 4 lanes) to 4xSFP\;8 - XX(/ 2 lane module) to XX\;9 - XX(/ 2 lane module) to 2xSFP" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="cable_technology" descr="QSFP: \;Byte 147 per SFF-8636.\;\;SFP:\;SFP+ Cable Technology: \;byte8 per SFF-8472:\;Bit 3 - Active Cable\;Bit 2 - Passive Cable\;\;CMIS based (QSFP-DD / OSFP/ SFP-DD):\;Byte 212" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="cable_power_class" descr="Module maximum power consumption for SFP/QSFP:\;0: Power_Class_0 - (1.0 W max)\;1: Power_Class_1 - (1.5 W max)\;2: Power_Class_2 - (2.0 W max)\;3: Power_Class_3 - (2.5 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (4.0 W max)\;6: Power_Class_6 - (4.5 W max)\;7: Power_Class_7 - (5.0 W max)\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for SFP-DD:\;0: Power_Class_0 - (0.5 W max)\;1: Power_Class_1 - (1.0 W max)\;2: Power_Class_2 - (1.5 W max)\;3: Power_Class_3 - (2.0 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (5.0 W max)\;6: reserved\;7: reserved\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for QSFP-DD/OSFP:\;1 - Power_Class_1 - (1.5 W max)\;2 - Power_Class_2 - (3.5 W max)\;3 - Power_Class_3 - (7.0 W max)\;4 - Power_Class_4 - (8.0 W max)\;5 - Power_Class_5 - (10 W max)\;6 - Power_Class_6 - (12 W max)\;7 - Power_Class_7 - (14 W max)\;8 - Power_Class_8 - (power from max_power field)" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="cable_identifier" descr="0: QSFP28\;1: QSFP_Plus\;2: SFP28_or_SFP_Plus\;3: QSA - (QSFP-&gt;SFP)\;4: Backplane\;5: SFP_DD\;6: QSFP_DD\;7: QSFP_CMIS\;8: OSFP\;9: C2C\;10: DSFP\;11: QSFP_Split_Cable\;\;identifiers that are CMIS compliant are: 5,6,7,8,10" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="cable_length" descr="Cable length in 1m units.\;\;For CMIS modules:\;bits 6:7 represent cable_length_multiplier for calculating \;cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;bits 0:5 represent cable_length_value for calculating cable \;length.\;length is calculated with cable_length_value * \;cable_length_multiplier" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="cable_vendor" descr="Cable vendor:\;0: Other\;1: Mellanox\;2: Known_OUI\;3: NVIDIA\;" access="RO" enum="Other=0x0,Mellanox=0x1,Known_OUI=0x2,NVIDIA=0x3" offset="0x4.24" size="0x0.4" />
	<field name="cable_type" descr="Cable/module type:\;0: Unidentified\;1: Active_cable - (active copper / optics)\;2: Optical_Module - (separated)\;3: Passive_copper_cable\;4: Cable_unplugged\;5: Twisted_pair\;" access="RO" enum="Unidentified=0x0,Active_cable=0x1,Optical_Module=0x2,Passive_copper_cable=0x3,Cable_unplugged=0x4,Twisted_pair=0x5" offset="0x4.28" size="0x0.4" />
	<field name="cable_tx_equalization" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="cable_rx_emphasis" descr="\;For CMIS (QSFP-DD/ SFP-DD/ OSFP) field will represent Rx \;pre-emphasis." access="RO" offset="0x8.8" size="0x0.8" />
	<field name="cable_rx_amp" descr="Reserved for SFP\;" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="max_power" descr="Reserved for SFP, QSFP\;Byte 201 for CMIS (QSFP-DD/ SFP-DD/ OSFP)\;Other Cable ignore field." access="RO" offset="0x8.24" size="0x0.8" />
	<field name="cable_attenuation_5g" descr="Reserved for SFP" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="cable_attenuation_7g" descr="Reserved for SFP" access="RO" offset="0xC.8" size="0x0.8" />
	<field name="cable_attenuation_12g" descr="Reserved for SFP" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="cable_attenuation_25g" descr="Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)\;Other Cable ignore field." access="RO" offset="0xC.24" size="0x0.8" />
	<field name="tx_cdr_state" descr="Reserved for SFP\;\;Bit 0 - TX CDR on/off on channel 0 \;Bit 1 - TX CDR on/off on channel 1 \;Bit 2 - TX CDR on/off on channel 2 \;Bit 3 - TX CDR on/off on channel 3 \;Bit 4 - TX CDR on/off on channel 4 \;Bit 5 - TX CDR on/off on channel 5 \;Bit 6 - TX CDR on/off on channel 6 \;Bit 7 - TX CDR on/off on channel 7 \;\;CDR on - when bit is set.\;CDR off - when bit is clear.\;" access="RO" offset="0x10.0" size="0x0.8" />
	<field name="rx_cdr_state" descr="Reserved for SFP\;\;Bit 0 - RX CDR on/off on channel 0 \;Bit 1 - RX CDR on/off on channel 1 \;Bit 2 - RX CDR on/off on channel 2 \;Bit 3 - RX CDR on/off on channel 3\;Bit 4 - RX CDR on/off on channel 4 \;Bit 5 - RX CDR on/off on channel 5 \;Bit 6 - RX CDR on/off on channel 6 \;Bit 7 - RX CDR on/off on channel 7 \;\;CDR on - when bit is set.\;CDR off - when bit is clear.\;" access="RO" offset="0x10.8" size="0x0.8" />
	<field name="tx_cdr_cap" descr="0 - No CDR\;1 - Build-in CDR with on/off control \;2 - Build-in CDR without on/off control" access="RO" offset="0x10.16" size="0x0.4" />
	<field name="rx_cdr_cap" descr="0 - No CDR\;1 - Build-in CDR with on/off control \;2 - Build-in CDR without on/off control" access="RO" offset="0x10.20" size="0x0.4" />
	<field name="cable_rx_post_emphasis" descr="Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)\;Rx post-emphasis." access="RO" offset="0x10.24" size="0x0.8" />
	<field name="vendor_name" descr="ASCII Vendor name left-aligned and padded on the right with\;ASCII spaces (20h)" access="RO" high_bound="3" low_bound="0" offset="0x14.0" size="0x10.0" />
	<field name="vendor_pn" descr="Vendor Part Number left-aligned and padded on the right \;with ASCII spaces (20h)" access="RO" high_bound="3" low_bound="0" offset="0x24.0" size="0x10.0" />
	<field name="vendor_rev" descr="ASCII Vendor revision aligned to right padded with 0h on the \;left" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fw_version" descr="If information is not available by the module: set to 0" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="vendor_sn" descr="Vendor Serial Number" access="RO" high_bound="3" low_bound="0" offset="0x3C.0" size="0x10.0" />
	<field name="voltage" descr="Internally measured supply voltage in 100uV" access="RO" offset="0x4C.00" size="0x0.16" />
	<field name="temperature" descr="module temperature in 1/256 C" access="RO" offset="0x4C.16" size="0x0.16" />
	<field name="rx_power_lane1" descr="RX measured power channel 1.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x50.0" size="0x0.16" />
	<field name="rx_power_lane0" descr="RX measured power channel 0.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x50.16" size="0x0.16" />
	<field name="rx_power_lane3" descr="RX measured power channel 3.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="rx_power_lane2" descr="RX measured power channel 2.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x54.16" size="0x0.16" />
	<field name="rx_power_lane5" descr="RX measured power channel 5.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="rx_power_lane4" descr="RX measured power channel 4.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x58.16" size="0x0.16" />
	<field name="rx_power_lane7" descr="RX measured power channel 7.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x5C.0" size="0x0.16" />
	<field name="rx_power_lane6" descr="RX measured power channel 6.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x5C.16" size="0x0.16" />
	<field name="tx_power_lane1" descr="TX measured power channel 1.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x60.0" size="0x0.16" />
	<field name="tx_power_lane0" descr="TX measured power channel 0.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x60.16" size="0x0.16" />
	<field name="tx_power_lane3" descr="TX measured power channel 3.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x64.0" size="0x0.16" />
	<field name="tx_power_lane2" descr="TX measured power channel 2.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x64.16" size="0x0.16" />
	<field name="tx_power_lane5" descr="TX measured power channel 5.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x68.0" size="0x0.16" />
	<field name="tx_power_lane4" descr="TX measured power channel 4.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x68.16" size="0x0.16" />
	<field name="tx_power_lane7" descr="TX measured power channel 7.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x6C.0" size="0x0.16" />
	<field name="tx_power_lane6" descr="TX measured power channel 6.\;measured in dBm/uW according to module_info_ext value" access="RO" offset="0x6C.16" size="0x0.16" />
	<field name="tx_bias_lane1" descr="TX measured bias current on channel 1 in 2uA" access="RO" offset="0x70.0" size="0x0.16" />
	<field name="tx_bias_lane0" descr="TX measured bias current on channel 0 in 2uA" access="RO" offset="0x70.16" size="0x0.16" />
	<field name="tx_bias_lane3" descr="TX measured bias current on channel 3 in 2uA" access="RO" offset="0x74.0" size="0x0.16" />
	<field name="tx_bias_lane2" descr="TX measured bias current on channel 2 in 2uA" access="RO" offset="0x74.16" size="0x0.16" />
	<field name="tx_bias_lane5" descr="TX measured bias current on channel 5 in 2uA" access="RO" offset="0x78.0" size="0x0.16" />
	<field name="tx_bias_lane4" descr="TX measured bias current on channel 4 in 2uA" access="RO" offset="0x78.16" size="0x0.16" />
	<field name="tx_bias_lane7" descr="TX measured bias current on channel 7 in 2uA" access="RO" offset="0x7C.0" size="0x0.16" />
	<field name="tx_bias_lane6" descr="TX measured bias current on channel 6 in 2uA" access="RO" offset="0x7C.16" size="0x0.16" />
	<field name="temperature_low_th" descr="Alarm low temperature threshold in 1/256 C" access="RO" offset="0x80.0" size="0x0.16" />
	<field name="temperature_high_th" descr="Alarm high temperature threshold in 1/256 C" access="RO" offset="0x80.16" size="0x0.16" />
	<field name="voltage_low_th" descr="Alarm low Voltage threshold in 100uV" access="RO" offset="0x84.0" size="0x0.16" />
	<field name="voltage_high_th" descr="Alarm high Voltage threshold in 100uV" access="RO" offset="0x84.16" size="0x0.16" />
	<field name="rx_power_low_th" descr="Alarm low RX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x88.0" size="0x0.16" />
	<field name="rx_power_high_th" descr="Alarm high RX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x88.16" size="0x0.16" />
	<field name="tx_power_low_th" descr="Alarm low TX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x8C.0" size="0x0.16" />
	<field name="tx_power_high_th" descr="Alarm high TX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x8C.16" size="0x0.16" />
	<field name="tx_bias_low_th" descr="Alarm low TX Bias current threshold in 2 uA." access="RO" offset="0x90.0" size="0x0.16" />
	<field name="tx_bias_high_th" descr="Alarm high TX Bias current threshold in 2 uA." access="RO" offset="0x90.16" size="0x0.16" />
	<field name="wavelength" descr="Nominal laser wavelength in nm" access="RO" offset="0x94.0" size="0x0.16" />
	<field name="smf_length" descr="SMF link length\;SFP per byte 14,15.\;QSFP per byte 142\;for CMIS based modules, per byte 132\;\;bit 9:8 - 00 length base in 1 km units\;bit 9:8 - 01 length base in 100m units\;bits 7:0 - length base" access="RO" offset="0x94.16" size="0x0.10" />
	<field name="did_cap" descr="set in case of Linear Direct Drive module" access="RO" offset="0x94.27" size="0x0.1" />
	<field name="rx_power_type" descr="rx power measurement type\;0: OMA\;1: Average_power" access="RO" enum="OMA=0x0,Average_power=0x1" offset="0x94.28" size="0x0.1" />
	<field name="module_st" descr="Valid for CMIS modules only.\;Module state:\;0: reserved\;1: LowPwr_state\;2: PwrUp_state\;3: Ready_state\;4: PwrDn_state\;5: Fault_state" access="RO" enum="reserved=0x0,LowPwr_state=0x1,PwrUp_state=0x2,Ready_state=0x3,PwrDn_state=0x4,Fault_state=0x5" offset="0x94.29" size="0x0.3" />
	<field name="ib_compliance_code" descr="Byte 164 of SFF-8636\;For CMIS modules IB Protocols." access="RO" offset="0x98.0" size="0x0.8" />
	<field name="active_set_media_compliance_code" descr="Valid for CMIS modules only.\;According to current Active set, value of Module Media Inter\;face byte" access="RO" offset="0x98.16" size="0x0.8" />
	<field name="active_set_host_compliance_code" descr="Valid for CMIS modules only.\;According to current Active set, value of Host Electrical Inter\;face byte" access="RO" offset="0x98.24" size="0x0.8" />
	<field name="ib_width" descr="Bitmask of width of IB Protocols" access="RO" offset="0x9C.0" size="0x0.6" />
	<field name="monitor_cap_mask" descr="monitoring capabilities mask\;Bit 0 - temperature monitoring implemented\;Bit 1 - voltage monitoring implemented\;Bit 2 - tx power monitoring implemented\;Bit 3 - rx power monitoring implemented\;Bit 4 - tx bias monitoring implemented" access="RO" offset="0x9C.8" size="0x0.8" />
	<field name="nbr100" descr="Nominal bit rate in units of 100Mb/s" access="RO" offset="0x9C.16" size="0x0.8" />
	<field name="nbr250" descr="Nominal bit rate in units of 250Mb/s" access="RO" offset="0x9C.24" size="0x0.8" />
	<field name="dp_st_lane7" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" offset="0xA0.0" size="0x0.4" />
	<field name="dp_st_lane6" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" offset="0xA0.4" size="0x0.4" />
	<field name="dp_st_lane5" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" offset="0xA0.8" size="0x0.4" />
	<field name="dp_st_lane4" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" offset="0xA0.12" size="0x0.4" />
	<field name="dp_st_lane3" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" offset="0xA0.16" size="0x0.4" />
	<field name="dp_st_lane2" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" offset="0xA0.20" size="0x0.4" />
	<field name="dp_st_lane1" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" offset="0xA0.24" size="0x0.4" />
	<field name="dp_st_lane0" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" enum="DPDeactivated=0x1,DPInit=0x2,DPDeinit=0x3,DPActivated=0x4,DPTxTurnOn=0x5,DPTxTurnOff=0x6,DPInitialized=0x7" offset="0xA0.28" size="0x0.4" />
	<field name="length_om5" descr="OM5 fiber length supported in units of 2m" access="RO" offset="0xA4.0" size="0x0.8" />
	<field name="length_om4" descr="OM4 fiber length supported in units of 2m\;SFP in units of 10m" access="RO" offset="0xA4.8" size="0x0.8" />
	<field name="length_om3" descr="OM3 fiber length supported in units of 2m\;SFP in units of 10m" access="RO" offset="0xA4.16" size="0x0.8" />
	<field name="length_om2" descr="OM2 fiber length supported in units of 1m\;SFP in units of 10m" access="RO" offset="0xA4.24" size="0x0.8" />
	<field name="memory_map_rev" descr="memory map revision" access="RO" offset="0xA8.0" size="0x0.8" />
	<field name="wavelength_tolerance" descr="16-bit integer value for the laser wavelength tolerance in nm \;divided by 200 (units of 0.005nm)." access="RO" offset="0xA8.8" size="0x0.16" />
	<field name="length_om1" descr="OM1 fiber length supported in units of 10m" access="RO" offset="0xA8.24" size="0x0.8" />
	<field name="memory_map_compliance" descr="memory map compliance in ASCII.\;SFF-8472 / SFF-8636/ CMIS" access="RO" offset="0xAC.0" size="0x4.0" />
	<field name="date_code" descr="ASCII code for vendor&apos;s date code.\;63:48- 2 digit for date code year, 00 = year 2000\;47:32 - 2 digit for date code month.\;31:16 - 2 digit for day of the month code.\;15:0 - 2 digit LOT code." subnode="uint64" access="RO" offset="0xB0.0" size="0x8.0" />
	<field name="vendor_oui" descr="vendor oui" access="RO" offset="0xB8.0" size="0x0.24" />
	<field name="connector_type" descr="connector type based on SFF-8024" access="RO" offset="0xB8.24" size="0x0.8" />
	<field name="rx_output_valid" descr="Rx output status indication per lane" access="RO" offset="0xBC.0" size="0x0.8" />
	<field name="rx_input_valid" descr="Rx input status indication per lane" access="RO" offset="0xBC.8" size="0x0.8" />
	<field name="tx_input_freq_sync" descr="Defines which Tx input lanes must be frequency synchronous.\;0: Tx_input_lanes_1_8\;1: Tx_input_lanes_1_4_and_5-8\;2: Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8\;3: Lanes_may_be_asynchronous_in_frequency" access="RO" enum="Tx_input_lanes_1_8=0x0,Tx_input_lanes_1_4_and_5=0x1,Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8=0x2,Lanes_may_be_asynchronous_in_frequency=0x3" offset="0xBC.16" size="0x0.2" />
	<field name="error_code" descr="Relevant for CMIS modules only\;Error Code response for ConrolSet configuration of DataPath.\;0x0: ConfigUndefined\;0x1: ConfigSuccess\;0x2: ConfigRejected\;0x3: ConfigRejectedInvalidAppSel\;0x4: ConfigRejectedInvalidDataPath\;0x5: ConfigRejectedInvalidSI\;0x6: ConfigRejectedLanesInUse\;0x7: ConfigRejectedPartialDataPath\;0xC: ConfigInProgress" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc" offset="0xC0.0" size="0x0.4" />
	<field name="max_fiber_length" descr="Maximum length of allowed fiber in meters" access="RO" offset="0xC0.16" size="0x0.16" />
</node>

<node name="pddr_monitor_opcode_ext" descr="" size="0x4.0" >
	<field name="monitor_opcode" descr="Status opcode: \;\;PHY FW indication (0 - 1023):\;0 - No issue observed\;1 - Port is close by command (see PAOS).\;2,3,4,38,39 - AN failure \;5,6,7,8 - Link training failure. \;9,10,11,12,13 - Logical mismatch between link partners\;14 - Remote fault received\;15,42,17 - Bad signal integrity \;16,24-32 - Cable compliance code mismatch (protocol mis\;match between cable and port) \;23,22,19,18- Internal error\;34,35 - Speed degradation\;56 - module_lanes_frequency_not_synced\;128 - Troubleshooting in process\;1023- Info not available\;\;MNG FW issues (1024 - 2047):\;1024 - Cable is unplugged\;1025 - Long Range for non Mellanox cable/module .\;1026 - Bus stuck (I2C Data or clock shorted) \;1027 - Bad/unsupported EEPROM \;1028 - Part number list\;1029 - Unsupported cable.\;1030 - Module temperature shutdown\;1031 - Shorted cable\;1032 - Power budget exceeded\;1033 - Management forced down the port\;1034 - Module is disabled by command\;1036 - Module&apos;s PMD type is not enabled (see PMTPS).\;1040 - pcie system power slot Exceeded\;1042 - Module state machine fault\;1043,1044,1045,1046 - Module&apos;s stamping speed \;degeneration\;1047, 1048 - Modules DataPath FSM fault\;\;Core/Driver (2048 - 3071):" access="RW" offset="0x0.0" size="0x0.16" />
</node>

<node name="pddr_operation_info_page_cable_proto_cap_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_cable_cap_ib_ext" descr="" subnode="pddr_cable_cap_ib_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_cable_cap_eth_ext" descr="" subnode="pddr_cable_cap_eth_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_c2p_link_enabed_ib_ext" descr="" subnode="pddr_c2p_link_enabed_ib_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_c2p_link_enabed_eth_ext" descr="" subnode="pddr_c2p_link_enabed_eth_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_ext" descr="" size="0xf8.0" >
	<field name="proto_active" descr="Active protocol:\;Bit 0: InfiniBand\;Bit 2: Ethernet" access="RO" offset="0x0.20" size="0x0.4" />
	<field name="ib_phy_fsm_state" descr="FW IB state machine:\;0x0: IB_AN_FSM_DISABLED\;0x1: IB_AN_FSM_INITIALY\;0x2: IB_AN_FSM_RCVR_CFG\;0x3: IB_AN_FSM_CFG_TEST\;0x4: IB_AN_FSM_WAIT_RMT_TEST\;0x5: IB_AN_FSM_WAIT_CFG_ENHANCED\;0x6: IB_AN_FSM_CFG_IDLE\;0x7: IB_AN_FSM_LINK_UP\;0x8: IB_AN_FSM_POLLING\;0x9: IB_AN_FSM_SYNC_CHECK - [Internal]" access="RO" enum="IB_AN_FSM_DISABLED=0x0,IB_AN_FSM_INITIALY=0x1,IB_AN_FSM_RCVR_CFG=0x2,IB_AN_FSM_CFG_TEST=0x3,IB_AN_FSM_WAIT_RMT_TEST=0x4,IB_AN_FSM_WAIT_CFG_ENHANCED=0x5,IB_AN_FSM_CFG_IDLE=0x6,IB_AN_FSM_LINK_UP=0x7,IB_AN_FSM_POLLING=0x8,IB_AN_FSM_SYNC_CHECK=0x9" offset="0x4.8" size="0x0.8" />
	<field name="eth_an_fsm_state" descr="Ethernet (CL73) Auto-negotiation FSM state:\;0x0: ETH_AN_FSM_ENABLE\;0x1: ETH_AN_FSM_XMIT_DISABLE\;0x2: ETH_AN_FSM_ABILITY_DETECT\;0x3: ETH_AN_FSM_ACK_DETECT\;0x4: ETH_AN_FSM_COMPLETE_ACK\;0x5: ETH_AN_FSM_AN_GOOD_CHECK\;0x6: ETH_AN_FSM_AN_GOOD\;0x7: ETH_AN_FSM_NEXT_PAGE_WAIT\;0x8: ETH_AN_FSM_LINK_STAT_CHECK - [Internal] \;0x9: ETH_AN_FSM_EXTRA_TUNE - [Internal] \;0xa: ETH_AN_FSM_FIX_REVERSALS - [Internal] \;0xb: ETH_AN_FSM_IB_FAIL - [Internal] \;0xc: ETH_AN_FSM_POST_LOCK_TUNE - [Internal] \;\;NDR gen - \;0x0: ETH_AN_FSM_ENABLE\;0x1: ETH_AN_FSM_XMIT_DISABLE\;0x2: ETH_AN_FSM_ABILITY_DETECT\;0x3: ETH_AN_FSM_ACK_DETECT\;0x4: ETH_AN_FSM_COMPLETE_ACK\;0x5: ETH_AN_FSM_AN_GOOD_CHECK\;0x6: ETH_AN_FSM_AN_GOOD\;0x7: ETH_AN_FSM_NEXT_PAGE_WAIT\;0x8: ETH_AN_FSM_FIX_REVERSALS - [Internal] \;0x9: ETH_AN_FSM_SUBFSM_FAIL - [Internal] \;0xa: ETH_AN_FSM_HCD_TX_TAPS - [Internal]" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="phy_mngr_fsm_state" descr="FW Phy Manager FSM state:\;0: Disabled \;1: Open_port\;2: Polling\;3: Active_or_Linkup\;4: Close_port\;5: Phy_up\;7: Rx_disable" access="RO" enum="Disabled=0x0,Open_port=0x1,Polling=0x2,Active_or_Linkup=0x3,Close_port=0x4,Phy_up=0x5,Rx_disable=0x7" offset="0x4.24" size="0x0.8" />
	<field name="phy_manager_link_enabled" descr="For IB: Table  1367, &quot;PDDR - Phy manager link enabled IB lay\;out,&quot; on page  1670\;For Ethernet: Table  1369, &quot;PDDR - Phy manager link enabled \;Eth layout,&quot; on page  1670\;" subnode="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="core_to_phy_link_enabled" descr="For IB: Table  1371, &quot;PDDR - core2phy link enabled IB layout,&quot; \;on page  1671\;For Ethernet: Table  1373, &quot;PDDR - Core2Phy link enabled Eth \;layout,&quot; on page  1672" subnode="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="cable_proto_cap" descr="For IB: Table  1375, &quot;PDDR - cable cap IB layout,&quot; on \;page  1673\;For Ethernet: Table  1377, &quot;PDDR - cable cap Eth layout,&quot; on \;page  1674\;" subnode="pddr_operation_info_page_cable_proto_cap_auto_ext" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="link_active" descr="For IB: Table  1379, &quot;PDDR - Link Active IB layout,&quot; on \;page  1675\;For Ethernet: Table  1381, &quot;PDDR - Link Active Eth layout,&quot; on \;page  1675" subnode="pddr_operation_info_page_link_active_auto_ext" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="loopback_mode" descr="0: No_loopback_active\;1: Phy_remote_loopback \;2: Phy_local_loopback -When set the port&apos;s egress traffic is \;looped back to the receiver and the port transmitter is dis\;abled. \;4: External_local_loopback -Enables the port&apos;s transmitter to \;link with the port&apos;s receiver using an external loopback con\;nector. \;8: Near_end_analog_loopback - [Internal]\;16: Near_end_digital_loopback - [Internal]\;128: LL_local_loopback - [Internal]" access="RO" enum="No_loopback_active=0x0,Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,Near_end_analog_loopback=0x8,Near_end_digital_loopback=0x10,LL_local_loopback=0x80" offset="0x18.0" size="0x0.8" />
	<field name="fec_mode_request" descr="FEC mode request\;See fec_mode_active\;for supported retransmission mode see PPLM.fec_mode_ca\;pability" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="fec_mode_active" descr="FEC mode active\;0: No_FEC\;1: Firecode_FEC\;2: Standard_RS_FEC - RS(528,514)\;3: Standard_LL_RS_FEC - RS(271,257)\;4: Reserved - [Internal]\;5: reserved - [Internal]\;6: Interleaved_Standard_RS-FEC - (544,514)\;7: Standard_RS-FEC - (544,514)\;8: Zero_Latency_FEC - [Internal]\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - \;(272,257+1)\;11: Interleaved_Standard_RS_FEC_PLR - (544,514)- [Inter\;nal]\;12: RS-FEC - (544,514) + PLR- [Internal]\;13: LL-FEC - (271,257) + PLR- [Internal]\;14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - \;(272,257+1) [Internal] \;15: Interleaved_Ethernet_Consor\;tium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]\;\;For supported retransmission mode see PPLM.fec_mode_ca\;pability" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Reserved=0x4,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Zero_Latency_FEC=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS=0xc,LL=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf" offset="0x1C.16" size="0x0.16" />
	<field name="eth_100g_fec_support" descr="FEC 100G (25Gb/s per lane) supported FEC include override \;masking , should reflect current phy configuration\;Bit 0 - No FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="eth_25g_50g_fec_support" descr="FEC 25G/50G (25Gb/s per lane) supported FEC include over\;ride masking , should reflect current phy configuration\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.4" size="0x0.4" />
</node>

<node name="pddr_operation_info_page_link_active_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_link_active_ib_ext" descr="" subnode="pddr_link_active_ib_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_link_active_eth_ext" descr="" subnode="pddr_link_active_eth_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_phy_manager_link_enabed_ib_ext" descr="" subnode="pddr_phy_manager_link_enabed_ib_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabed_eth_ext" descr="" subnode="pddr_phy_manager_link_enabed_eth_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_debug_page_ext" descr="" size="0xf8.0" >
	<field name="tracer_enable" descr="Enables tracer operation" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="reset_tracer" descr="Resets all tracer parameters and tracer DB" access="OP" offset="0x0.1" size="0x0.1" />
	<field name="tracer_mode" descr="0 - PHY_TRACER_MODE_SINGLE_CYCLE\;1 - PHY_TRACER_MODE_WRAPAROUND\;3 - PHY_TRACER_MODE_TRIGGER" access="INDEX" offset="0x0.2" size="0x0.3" />
	<field name="pre_trigger_buff_mode" descr="0 - pre 0%, post 100%\;1 - pre 25%, post 75%\;2 - pre 50%, post 50%\;3 - pre 75%, post 25%\;4 - pre 100%, post 0%" access="INDEX" offset="0x0.5" size="0x0.3" />
	<field name="trigger_cond_fsm" descr="Which FSM should trigger the tracer:" access="INDEX" offset="0x0.8" size="0x0.5" />
	<field name="trigger_cond_state_or_event" descr="Which occurrence should trigger the tracer:\;0 - state\;1 - event" access="INDEX" offset="0x0.13" size="0x0.1" />
	<field name="trigger_cond_state_event_val" descr="Which occurrence value should trigger the tracer" access="INDEX" offset="0x0.14" size="0x0.7" />
	<field name="trigger_active" descr="trigger was caught and tracer activated" access="RO" offset="0x0.21" size="0x0.1" />
	<field name="pport" descr="" access="INDEX" offset="0x0.22" size="0x0.8" />
	<field name="fsm_mask" descr="Bit 1 - ETH_AN_FSM\;Bit 2 - IB_AN_FSM\;Bit 3 - PM_FSM\;Bit 6 - ETH_1G_AN_FSM\;Bit 7 - PORT_KR_STARTUP_FSM\;Bit 8 - LINK_MAINTENANCE\;Bit 9 - PSI_FSM\;Bit 10 - PORT_BER_MONITOR_FSM\;Bit 12 - PHY_TEST_MODE_FSM\;Bit 13 - PTER\;Bit 14 - PD_FSM\;\;0xffff - all FSMs" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="buffer_size" descr="tracer size in DWORDs" access="RO" offset="0x8.0" size="0x0.12" />
	<field name="trigger_ptr" descr="trigger pointer in the buffer" access="RO" offset="0x8.12" size="0x0.12" />
	<field name="ptr_next_write" descr="" access="RO" offset="0xC.0" size="0x0.12" />
	<field name="ptr_log_data" descr="pointer of the last relevant data the tracer has (once trigger \;was asserted)" access="RO" offset="0xC.12" size="0x0.12" />
	<field name="buffer_base_address" descr="Address of the first DWORD of the tracer DB" access="RO" offset="0x10.0" size="0x4.0" />
</node>

<node name="pddr_phy_info_page_ext" descr="" size="0xf8.0" >
	<field name="port_notifications" descr="Port notifications bit mask\;Bit 0 - Link partner advertised capabilities \;Bit 1 - Speed degradation" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="remote_device_type" descr="Remote device type: \;0 - Unknown (3rd party , Force , legacy MLPN)  \;1 - CX4\;2 - CX4_LX\;3 - CX5\;4 - CX5_LX\;5 - CX6\;6 - CX6_LX\;7 - CX6_DX\;8 - CX7\;9 - Bluefield-2\;10 - CX8\;11 - Bluefield-3\;12-99 Reserved\;100 - SwitchIB\;101 - Spectrum \;102 - SwitchIB-2\;103 - Quantum\;104 - Spectrum-2\;105 - Spectrum-3\;106 - Quantum-2\;107 - Spectrum-4\;108 -Quantum-3\;109-255 Reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="lp_ib_revision" descr="Link partner IB TS revision \;\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ib_revision" descr="IB TS revision \;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="num_of_negotiation_attempts" descr="Negotiation attempt counter" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="phy_manger_disable_mask" descr="Phy manager disable bit mask: \;Bit 0 - Module not present (module absence/cage power off)\;Bit 1 - PAOS command\;Bit 2 - MAD IB PortInfo down command\;Bit 3 - Long range cable (Non Mellanox) \;Bit 4 - Verification command\;Bit 5 - ekey command\;Bit 6 - High power - cable require higher power than allowed.\;Bit 7 - Unknown Identifier (Module)\;Bit 8 - PAOS up once \;Bit 9 - Stamping failure\;Bit 10 - Calibration not done\;[Internal] Bit 11 - Module Locking\;[Internal] Bit 13 - Power budget exceeded\;[Internal] Bit 14 - Interrupt Event / Module Temp\;[Internal] Bit 15 - TEC flow / module bring up issue" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="hw_link_phy_state" descr="IBP HW FSM Reflected State:\;0x10 - sleeping delay\;0x11 - sleeping quiet\;0x20 - polling active\;0x21 - polling quiet\;0x30 - disable\;0x40 - config debounce\;0x41 - config receiver\;0x42 - config wait remote\;0x43 - config tx reverse lanes\;0x44 - config enhanced    \;0x45 - config test\;0x46 - confg wait remote test\;0x47 - config wait cfg enhanced\;0x48 - config idle\;0x50 - linkup\;0x60 - recover retrain\;0x61 - recover wait remote\;0x62 - recover idle\;0x70 - test\;\;Force Modes:\;0x80 - Force     send ts1 (command may be given only on dis\;able state)\;0x90 - Force send ts2\;0xA0 - Force Sent Idle\;0xB0 -  Force send ts Mlnx\;0xC0 - Force send ts3\;0xD0 - Force LinkUp" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="pcs_phy_state" descr="PCS HW state:\;Bits 0-7: Block lock\;Bits 8-15: AM lock\;Bits 16-23: FEC lock\;Bits 24: Align_status\;Bits 25: Hi_BER\;Bits 26: Hi_SER" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="lp_proto_enabled" descr="IB ports : \;Link partner advertised speeds (first TS3)\;See ib_link_speed_enabled encoding.\;\;Ethernet ports:\;Link partner advertised Ethernet protocols active state: see \;PTYS.lp_advertise" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="lp_fec_mode_request" descr="Reserved when negotiation wasn&apos;t performed according to \;port_notifications.Link partner advertised capabilities value.\;Advertised link partner FEC mode request" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="lp_fec_mode_support" descr="Reserved when negotiation wasn&apos;t performed according to \;port_notifications.Link partner advertised capabilities value.\;\;Advertised link partner FEC mode support\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;Bit 3 - Standard LL RS-FEC - RS(271,257)\;Bit 4 - Mellanox Strong RS-FEC - RS(277,257)\;Bit 5 - Mellanox LL RS-FEC - RS(163,155)\;Bit 6 - Reserved\;Bit 7 - Standard RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;\;for supported retransmission mode see PPLM.fec_mode_ca\;pability" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ib_last_link_down_reason" descr="Bit 0 - heartbeat_ack_received\;Bit 1 - heartbeat_send_received\;Bit 2 - heartbeat_err\;Bit 3 - tx_width_reduction_done_1x\;Bit 4 - tx_width_reduction_done_full\;Bit 5 - rx_width_reduction_done_1x\;Bit 6 - rx_width_reduction_done_full\;Bit 7 - width_reduction_timeout\;Bit 8 - ibl_link_retrain\;Bit 9 - rx_comskp_timeout\;Bit 10 - fifo_full_err\;Bit 11 - ts_at_linkup\;Bit 12 - minor_threshold_reached\;Bit 13 - link_fail\;Bit 14 - rx_eb_full_r\;Bit 15 - rx_8_10_lane_err\;Bit 16 - llr_link_retrain_set\;Bit 17 - fc_timeout\;Bit 18 - phy_error\;Bit 19 - lli_err\;Bit 20 - excessive_buffer_err\;Bit 21 - remote_init\;Bit 22 - plr_retry_expired\;Bit 23 - port_didnt_exit_plr_sync\;Bit 24 - eq_failed\;Bits 31-24 - Reserved" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="eth_last_link_down_lane" descr="Bit 0 - block_lock_failed\;Bit 1 - skip_detected\;Bit 2 - fec_sync_failed\;Bit 3 - fec_block_sync\;Bit 4 - fec_block_sync_lost" access="RO" high_bound="3" low_bound="0" offset="0x1C.24" size="0x4.0" />
	<field name="speed_deg_db" descr="Bit 0 - Speed degradation database Valid\;Bit 1 - Speed degradation Serdes Rx database valid\;BIts 3-2 - reserved\;Bit 4 - rx_reversal\;Bit 5 - tx_reversal\;Bit 7-6 - reserved\;Bits 11:8 - failed_qdr/fdr10 - bit per lane.\;Bits 15:12 - failed_fdr - bit per lane.\;Bits 19:16- failed_edr - bit per lane.\;Bits 24:20 - peer_failed_test\;Bits 26-25 - reserved\;Bit 27 - first_test_speed" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="degrade_grade_lane0" descr="Valid only when port_notifications.Speed degradation is \;asserted \;" access="RO" offset="0x28.0" size="0x0.24" />
	<field name="degrade_grade_lane1" descr="Valid only when port_notifications.Speed degradation is \;asserted \;" access="RO" offset="0x2C.0" size="0x0.24" />
	<field name="degrade_grade_lane2" descr="Valid only when port_notifications.Speed degradation is \;asserted \;" access="RO" offset="0x30.0" size="0x0.24" />
	<field name="degrade_grade_lane3" descr="Valid only when port_notifications.Speed degradation is \;asserted \;" access="RO" offset="0x34.0" size="0x0.24" />
	<field name="num_of_presets_tested_lane3" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.0" size="0x0.5" />
	<field name="num_of_presets_tested_lane2" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.8" size="0x0.5" />
	<field name="num_of_presets_tested_lane1" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.16" size="0x0.5" />
	<field name="num_of_presets_tested_lane0" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.24" size="0x0.5" />
	<field name="kr_startup_fsm_lane" descr="Per lane KR startup state:\;0 - KR_FSM_INITIALIZE\;1 - KR_FSM_SEND_TRAINING\;2 - KR_FSM_TRAIN_LOCAL_TX\;3 - KR_FSM_TRAIN_LOCAL_RX\;4 - KR_FSM_TRAIN_REMOTE\;5 - KR_FSM_LINK_READY\;6 - KR_FSM_SEND_DATA" access="RO" high_bound="3" low_bound="0" offset="0x48.24" size="0x4.0" />
	<field name="eth_an_debug_indication" descr="eth_an_debug bit mask:\;Bit 0 - Force link up\;Bit 1 - No HCD\;Bit 2 - Entered ACK_detect\;Bit 3 - Entered Good\;Bit 4 - Entered Good_Check\;Bit 5 - Entered Extra_tune\;Bit 6 - Entered Fix_Reversals\;Bit 7 - Entered Next_Page\;Bit 8 - Entered Sub-FSM Fail\;Bit 9 - Tuning timeout\;Bit 10 - No markers detected (during Good check)\;Bit 11 - Do KR-startup\;Bits 15:18 - KR startup failure mask" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ib_phy_fsm_state_trace" descr="FW IB state machine:\;HDR Gen\;Bit 0 - entered IB_AN_FSM_DISABLED\;Bit 1 - entered IB_AN_FSM_INITIALY\;Bit 2 - entered IB_AN_FSM_RCVR_CFG\;Bit 3 - entered IB_AN_FSM_CFG_TEST\;Bit 4 - entered IB_AN_FSM_WAIT_RMT_TEST\;Bit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCED\;Bit 6 - entered IB_AN_FSM_CFG_IDLE\;Bit 7 - entered IB_AN_FSM_LINK_UP\;Bit 8 - Failed from CFG_IDLE\;\;NDR Gen:\;Bit 0 - entered IB_AN_FSM_DISABLED\;Bit 1 - entered IB_AN_FSM_POLLING\;Bit 2 - entered IB_AN_FSM_INITIALY\;Bit 3 - entered IB_AN_FSM_CFG_TEST\;Bit 4 - entered IB_AN_FSM_WAIT_RMT_TEST\;Bit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCED\;Bit 6 - entered IB_AN_FSM_CFG_IDLE\;Bit 7 - entered IB_AN_FSM_SYNC_CHECK\;Bit 8 - entered IB_AN_FSM_LINK_UP\;Bit 9 - Failed from CFG_IDLE\;Bit 10 - peer requested KR\;Bit 11 - speed degradation needed - &quot;best_grade&quot; didn&quot;t \;reach threshold\;\;" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="rounds_waited_for_peer_to_end_test" descr="" access="RO" offset="0x54.16" size="0x0.5" />
	<field name="eth_an_watchdog_cnt" descr="counts ETH Watchdog was performed (and closed the IB \;fsm)." access="RO" offset="0x54.21" size="0x0.2" />
	<field name="fall_from_cfg_idle_cdr_cnt" descr="count falls from Cfg_idle (before linkup) due cdr not lock" access="RO" offset="0x54.23" size="0x0.3" />
	<field name="fall_from_cfg_idle_cnt" descr="count falls from Cfg_idle (before linkup) due amps lock on \;PLU" access="RO" offset="0x54.26" size="0x0.3" />
	<field name="cdr_not_locked_cnt" descr="count the cdr not locked after EQ" access="RO" offset="0x54.29" size="0x0.3" />
	<field name="kr_startup_debug_indications" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - PRBS lock failed\;Bit 1 - Entered send training\;Bit 2 - Entered train local RX\;Bit 3 - Entered train remote \;Bit 4 - Entered link ready\;Bit 5 - Entered Send_Data\;Bit 6 - Didn&apos;t get receiver ready \;Bit 7 - tuning timeout\;Bit 8 - No frame lock\;Bit 9 - No response from peer\;Bit 10 - frames lock tuning not done" access="RO" high_bound="3" low_bound="0" offset="0x58.16" size="0x8.0" />
	<field name="tx_tuning_stages_lane3" descr="Stages mask per lane:\;Bit 0 - Single preset stage\;Bit 1 - multiple preset stage\;Bit 2 - LMS" access="RO" offset="0x60.16" size="0x0.4" />
	<field name="tx_tuning_stages_lane2" descr="Stages mask per lane:\;Bit 0 - Single preset stage\;Bit 1 - multiple preset stage\;Bit 2 - LMS" access="RO" offset="0x60.20" size="0x0.4" />
	<field name="tx_tuning_stages_lane1" descr="Stages mask per lane:\;Bit 0 - Single preset stage\;Bit 1 - multiple preset stage\;Bit 2 - LMS" access="RO" offset="0x60.24" size="0x0.4" />
	<field name="tx_tuning_stages_lane0" descr="Stages mask per lane:\;Bit 0 - Single preset stage\;Bit 1 - multiple preset stage\;Bit 2 - LMS" access="RO" offset="0x60.28" size="0x0.4" />
	<field name="irisc_status" descr="" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="stamping_reason" descr="Bit 0 - com_codes_is_zero \;Bit 1- rx_cdr_check_force_mode \;Bit 2- com_code_complaince \;Bit 3- eth_56g_stamped\;Bit 4- non_mlx_qsfp_tranciver\;Bit 5- non_mlx_sfp_tranciver\;Bit 6-ib_comp_codes\;Bit 7-edr_comp\;Bit 8-fdr_comp" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="kr_frame_lock_tuning_failure_events_count" descr="Number of times that fast tuning (50ms) for KR lock failed to \;achieve frame lock." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="kr_full_tuning_failure_count" descr="Number of times that full tuning (0.5sec/3sec) for KR full \;tuning flow failed to achieve desire SI performance" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="pm_debug_indication" descr="Bit 0: phy_test_mode\;Bit 1: force_mode_en" access="RO" enum="phy_test_mode=0x1,force_mode_en=0x2" offset="0x78.0" size="0x0.16" />
	<field name="ib_debug_indication" descr="Bit 0: cause_plr_tx_max_outstanding_cells" access="RW" enum="cause_plr_tx_max_outstanding_cells=0x1" offset="0x78.16" size="0x0.16" />
	<field name="pd_debug_indication" descr="Bit 0: speed_change_high_speed_module\;Bit 1: False_positive_signal_detect\;Bit 2: Nv2nv_force\;Bit 3: bad_kr_mask \;Bit 4: kr_mlx_peer\;Bit 5: entered_signal_detect\;Bit 6: entered_rate_config\;Bit 7: entered_activate_sunfsm\;Bit 8: entered_done\;Bit 9: entered_subfsm_fail" access="RO" enum="speed_change_high_speed_module=0x1,False_positive_signal_detect=0x2,Nv2nv_force=0x4,bad_kr_mask=0x8,kr_mlx_peer=0x10,entered_signal_detect=0x20,entered_rate_config=0x40,entered_activate_sunfsm=0x80,entered_done=0x100,entered_subfsm_fail=0x200" offset="0x80.0" size="0x4.0" />
	<field name="pd_count" descr="Parallel detect cycles counter" access="RO" offset="0x84.0" size="0x0.6" />
	<field name="fp_signal_detect_count" descr="False Positive signal detect count" access="RO" offset="0x84.8" size="0x0.6" />
	<field name="hst_mismatch_reason" descr="0: speed\;1: FEC\;2: precoding\;3: Gray coding" access="RO" offset="0x84.16" size="0x0.2" />
	<field name="psi_collision2" descr="FSM 2 to call sub fsm of PSI that caused collision\;see fsm_mask in debug page for FSM numbering" access="RO" offset="0x84.22" size="0x0.5" />
	<field name="psi_collision1" descr="FSM 1 to call sub fsm of PSI that caused collision\;see fsm_mask in debug page for FSM numbering" access="RO" offset="0x84.27" size="0x0.5" />
</node>

<node name="pddr_phy_manager_link_enabed_eth_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_pro\;to_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_manager_link_enabed_ib_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_proto_enabled" descr="ib link enabled speed:\;Bit 0 - SDR\;Bit 1 - DDR\;Bit 2 - QDR\;Bit 3 - FDR10\;Bit 4 - FDR\;Bit 5 - EDR\;Bit 6 - HDR\;Bit 7 - NDR" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="phy_manager_link_width_enabled" descr="ib link enabled width:\;Bit 0 - 1x\;Bit 1 - 2x\;Bit 2 - 4x\;Bit 3 - 8x\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_port_events_page_layout_ext" descr="" size="0xf8.0" >
	<field name="invalid_fsm_sv" descr="invalid_fsm_ps severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="protocol_check" descr="illegal_protocol indication" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="protocol_check_sv" descr="illegal_protocol severity" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="pm_fifo_full" descr="Phy Manager fifo full indication" access="RO" offset="0x4.2" size="0x0.1" />
	<field name="pm_fifo_full_sv" descr="Phy Manager fifo full severity" access="RO" offset="0x4.3" size="0x0.1" />
	<field name="mod_adapt_faild" descr="Module adaptive tuning failed indication" access="RO" offset="0x4.4" size="0x0.1" />
	<field name="mod_adapt_faild_sv" descr="Module adaptive tuning failed severity" access="RO" offset="0x4.5" size="0x0.1" />
	<field name="mod_config_to" descr="Module configuration timeout indication" access="RO" offset="0x4.6" size="0x0.1" />
	<field name="mod_config_to_sv" descr="Module configuration timeout severity" access="RO" offset="0x4.7" size="0x0.1" />
	<field name="mod_req_busy" descr="" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="mod_req_busy_sv" descr="" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="mod_req_nack" descr="" access="RO" offset="0x4.10" size="0x0.1" />
	<field name="mod_req_nack_sv" descr="TBD - move to per port" access="RO" offset="0x4.11" size="0x0.1" />
	<field name="kr_false_ready" descr="KR startup false remote ready indication" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="kr_false_ready_sv" descr="KR startup false remote ready severity" access="RO" offset="0x4.17" size="0x0.1" />
	<field name="input_event_sv" descr="invalid_fsm_ps severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x8.31" size="0x0.1" />
	<field name="qsfp_zero_atten_sv" descr="QSFP zero attenuation severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0xC.1" size="0x0.1" />
	<field name="lane_mapping" descr="" access="RO" offset="0xC.2" size="0x0.1" />
	<field name="lane_mapping_sv" descr="" access="RO" offset="0xC.3" size="0x0.1" />
	<field name="init_all_gains_bad_val_sv" descr="init_all_gains_bad_val severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x10.1" size="0x0.1" />
	<field name="single_gains_bad_val" descr="" access="RO" offset="0x10.2" size="0x0.1" />
	<field name="single_gains_bad_val_sv" descr="single_gains_bad_val severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x10.3" size="0x0.1" />
	<field name="mono_flow_height_sv" descr="mono_flow_height severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x10.5" size="0x0.1" />
	<field name="mono_reach_high_limit" descr="" access="RO" offset="0x10.6" size="0x0.1" />
	<field name="mono_reach_high_limit_sv" descr="mono_reach_high_limit severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x10.7" size="0x0.1" />
	<field name="mono_reach_low_limit" descr="" access="RO" offset="0x10.8" size="0x0.1" />
	<field name="mono_reach_low_limit_sv" descr="mono_reach_low_limit severity\;0 - misconfiguration\;1 - fatal" access="RO" offset="0x10.9" size="0x0.1" />
	<field name="clr_mask" descr="Valid only when PDDR.clr is set\;Bit mask for page bits 255:0, when bits 31:0 assigned to off\;set 00h bits 31:0.\;bits 63:32 assigned to offset 04h bits 31:0.\;bits 95:64 assigned to offset 08h bits 31:0.\;bits 127:69 assigned to offset 0Ch bits 31:0.\;Only when PDDR.clr is set and the appropriate bit in the \;mask is set, the event will be cleared. \;For example: To clear the kr_false_ready need set PDDR.clr , \;select the &quot;port event page&quot; and set bit 48 in clr_mask." access="OP" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
</node>

<node name="pddr_reg_ext" descr="" size="0x100.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_port\;1: Near_End_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;4: USR_main\;5: USR_tile\;Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3,USR_main=0x4,USR_tile=0x5" offset="0x0.4" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0: Local_port_number\;1: IB_or_label_port_number\;" access="INDEX" enum="Local_port_number=0x0,IB_or_label_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number.\;If dev is set to 1, device index number.\;0: main die\;1-8: tile index number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:\;0: Operational_info_page\;1: Troubleshooting_info_page\;2: Phy_info_page - [Internal]\;3: Module_info_page\;4: port_events_page - [internal]\;5: device_events_page - [internal]\;6: link_down_info - [EMC only]\;7: link_down_events - [internal]\;8: Link_up_info - [Internal]\;9: Module_latched_flag_info_page\;10: link_down_info_ext\;11: link_partner_info_page\;0xFE: mng_debug_page\;0xFF: phy_debug_page" access="INDEX" enum="Operational_info_page=0x0,Troubleshooting_info_page=0x1,Phy_info_page=0x2,Module_info_page=0x3,port_events_page=0x4,device_events_page=0x5,link_down_info=0x6,link_down_events=0x7,Link_up_info=0x8,Module_latched_flag_info_page=0x9,link_down_info_ext=0xa,link_partner_info_page=0xb,mng_debug_page=0xfe,phy_debug_page=0xff" offset="0x4.0" size="0x0.8" />
	<field name="module_info_ext" descr="Module info extended configurations.\;resolution for rx_power and tx_power in module info page\;0: dbm\;1: uW" access="RW" enum="dbm=0x0,uW=0x1" offset="0x4.29" size="0x0.2" />
	<field name="page_data" descr="Table  1359, &quot;Operation Info Page Layout,&quot; on page  1648\;Table  1401, &quot;Troubleshooting info Page layout,&quot; on page  1706\;Table  1393, &quot;Phy info page layout,&quot; on page  1679\;Table  1399, &quot;Module Info Page Layout,&quot; on page  1693\;Table  1407, &quot;Port events Page Layout,&quot; on page  1710\;Table  1409, &quot;Device events Page Layout,&quot; on page  1714\;Table  1395, &quot;Link Down Info Page layout,&quot; on page  1689\;Table  1397, &quot;Link down events page layout,&quot; on page  1692\;Table  1411, &quot;Link Up Info Page Layout,&quot; on page  1720\;Table  1413, &quot;Module Latched Flag Info Page Layout,&quot; on \;page  1723\;Table  1415, &quot;phy debug page layout,&quot; on page  1726\;Table  1417, &quot;Mng debug page layout,&quot; on page  1728\;Table  1421, &quot;link down info ext for 16nm LR layout,&quot; on \;page  1733" subnode="pddr_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
</node>

<node name="pddr_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="pddr_operation_info_page_ext" descr="" subnode="pddr_operation_info_page_ext" offset="0x0.0" selected_by="Operational_info_page" size="0xf8.0" />
	<field name="pddr_troubleshooting_page_ext" descr="" subnode="pddr_troubleshooting_page_ext" offset="0x0.0" selected_by="Troubleshooting_info_page" size="0xf8.0" />
	<field name="pddr_phy_info_page_ext" descr="" subnode="pddr_phy_info_page_ext" offset="0x0.0" selected_by="Phy_info_page" size="0xf8.0" />
	<field name="pddr_module_info_ext" descr="" subnode="pddr_module_info_ext" offset="0x0.0" selected_by="Module_info_page" size="0xf8.0" />
	<field name="pddr_port_events_page_layout_ext" descr="" subnode="pddr_port_events_page_layout_ext" offset="0x0.0" selected_by="port_events_page" size="0xf8.0" />
	<field name="pddr_device_events_page_ext" descr="" subnode="pddr_device_events_page_ext" offset="0x0.0" selected_by="device_events_page" size="0xf8.0" />
	<field name="pddr_link_down_info_page_ext" descr="" subnode="pddr_link_down_info_page_ext" offset="0x0.0" selected_by="link_down_info" size="0x30.0" />
	<field name="pddr_link_down_events_page_ext" descr="" subnode="pddr_link_down_events_page_ext" offset="0x0.0" selected_by="link_down_events" size="0x20.0" />
	<field name="pddr_link_up_info_page_ext" descr="" subnode="pddr_link_up_info_page_ext" offset="0x0.0" selected_by="Link_up_info" size="0xf8.0" />
	<field name="module_latched_flag_info_ext" descr="" subnode="module_latched_flag_info_ext" offset="0x0.0" selected_by="Module_latched_flag_info_page" size="0xf8.0" />
	<field name="pddr_phy_debug_page_ext" descr="" subnode="pddr_phy_debug_page_ext" offset="0x0.0" selected_by="phy_debug_page" size="0xf8.0" />
	<field name="pddr_mng_debug_page_ext" descr="" subnode="pddr_mng_debug_page_ext" offset="0x0.0" selected_by="mng_debug_page" size="0xf8.0" />
	<field name="pddr_link_down_info_ext_16nm_lr_ext" descr="" subnode="pddr_link_down_info_ext_16nm_lr_ext" offset="0x0.0" selected_by="link_down_info_ext" size="0xf8.0" />
</node>

<node name="pddr_troubleshooting_page_ext" descr="" size="0xf8.0" >
	<field name="group_opcode" descr="0: Monitor_opcodes\;1: Advanced_debug_opcodes - [Internal]" access="INDEX" enum="Monitor_opcodes=0x0,Advanced_debug_opcodes=0x1" offset="0x0.0" size="0x0.16" />
	<field name="status_opcode" descr="Status opcode described in:\;Table  1403, &quot;PDDR - Monitor opcodes layout,&quot; on page  1707\;Table  1405, &quot;PDDR - Advanced opcodes layout,&quot; on page  1708" subnode="pddr_troubleshooting_page_status_opcode_auto_ext" access="RO" offset="0x4.0" size="0x4.0" union_selector="$(parent).group_opcode" />
	<field name="status_message" descr="ASCII code message\;All Messages are terminated by a Null character &apos;\0&apos;" access="RO" high_bound="58" low_bound="0" offset="0xC.0" size="0xec.0" />
</node>

<node name="pddr_troubleshooting_page_status_opcode_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_monitor_opcode_ext" descr="" subnode="pddr_monitor_opcode_ext" offset="0x0.0" selected_by="Monitor_opcodes" size="0x4.0" />
	<field name="pddr_advanced_opcode_ext" descr="" subnode="pddr_advanced_opcode_ext" offset="0x0.0" selected_by="Advanced_debug_opcodes" size="0x4.0" />
</node>

<node name="pfcc_reg_ext" descr="" size="0x20.0" >
	<field name="shl_opr" descr="Send to higher layers operation:\;0: Pause and PFC are handled by the port (default)\;1: Pause and PFC are handled by the port and are also been \;send to higher layers.\;Only valid if shl_cap = 1." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="shl_cap" descr="Send to higher layers capabilities:\;0: No capability of sending Pause and PFC to higher layers\;1: Device has capability of send Pause and PFC to higher \;layers\;NOTE: This relates to IEEE 802.3 PAUSE and IEEE 802.3 \;PFC." access="RO" offset="0x0.1" size="0x0.1" />
	<field name="critical_stall_mask" descr="Valid only on HCAs.\;Mask bit indicating if device_stall_critical_watermark \;should be updated.\;If set to &quot;1&quot;, device_stall_critical_watermark will be updated" access="WO" offset="0x0.2" size="0x0.1" />
	<field name="minor_stall_mask" descr="Valid only on HCAs.\;Mask bit indicating if device_stall_minor_watermark should \;be updated.\;If set to &quot;1&quot;, device_stall_minor_watermark will be updated" access="WO" offset="0x0.3" size="0x0.1" />
	<field name="ppan_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if ppan should be \;updated.\;If set to &quot;0&quot;, ppan will be updated" access="WO" offset="0x0.4" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0: Local port number\;1: IB / label port number\;[Internal] 3: Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="set_buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;\;Buffer ownership configuration. when this bits are set to a \;value other than 0, device will ignore all other fields pfcc \;register\;0: unknown \;1: device owned, all buffer configuration will return to its \;defaults." access="WO" offset="0x0.24" size="0x0.2" />
	<field name="buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;Current status of buffer ownership\;0: unknown\;1: device owned\;2: software owned" access="RO" offset="0x0.26" size="0x0.2" />
	<field name="cap_remote_admin" descr="Indicates if operation of remote admin parameters (dcx\;b_operation_type 0x2) is supported. \;" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation of local admin parameters (dcxb_op\;eration_type 0x1) is supported. \;" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="dcbx_operation_type" descr="The Operation type, valid only on HCAs.\;0: local_operative_parameters\;1: local_admin_parameters - supported only when cap_lo\;cal_admin==1.\;2: remote_admin_parameters - supported only when \;cap_remote_admin==1.\;Only pfctx and pfcrx are supported on remote device" access="INDEX" enum="local_operative_parameters=0x0,local_admin_parameters=0x1,remote_admin_parameters=0x2" offset="0x0.30" size="0x0.2" />
	<field name="prio_mask_rx" descr="Bit per prio indicating if RX flow control policy should be \;updated based on bit pfcrx ." access="WO" offset="0x4.0" size="0x0.8" />
	<field name="prio_mask_tx" descr="Bit per prio indicating if TX flow control policy should be \;updated based on bit pfctx ." access="WO" offset="0x4.16" size="0x0.8" />
	<field name="ppan" descr="Pause policy auto negotiation\;0: disabled - generate and ignore pause frames based on \;pptx, pprx\;1: enabled - when auto-negotiation is performed, set the \;pause policy based on the auto-negotiation resolution.\;" access="RW" enum="disabled=0x0,enabled=0x1" offset="0x4.28" size="0x0.4" />
	<field name="fctx_disabled" descr="Valid only on HCAs.\;The bit is set if the device has passed the device_stall_criti\;cal_watermark ( for global flow control or any priority when \;using priority flow control) and has become stalled. \;When fctx_disabled is set, the device will not send flow con\;trol and priority flow control (PFC) packets." access="RO" offset="0x8.8" size="0x0.1" />
	<field name="pfctx" descr="Priority based flow control policy on TX[7:0]. Per priority bit \;mask:\;0: never generate pause frames on the specified priority \;(default)\;1: generate pause frames according to RX buffer threshold \;on the specified priority\;pfctx, pptx must be mutually exclusive (for example, only one \;of them at most can be set)." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="pptx_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if pptx should be \;updated.\;If set to &quot;0&quot;, pptx will be updated" access="WO" offset="0x8.29" size="0x0.1" />
	<field name="aptx" descr="Active (operational) pause policy on TX\;0: do not generate pause frames\;1: generate pause frames according to RX buffer threshold" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="pptx" descr="Admin pause policy on TX (see also pfctx):\;0: never generate pause frames (default)\;1: generate pause frames according to RX buffer threshold" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="pfcrx" descr="Priority based flow control policy on RX[7:0]. Per priority bit \;mask:\;0: ignore incoming pause frames on the specified priority \;(default)\;1: respect incoming pause frames on the specified priority" access="RW" offset="0xC.16" size="0x0.8" />
	<field name="pprx_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if pprx should be \;updated.\;If set to &quot;0&quot;, pprx will be updated" access="WO" offset="0xC.29" size="0x0.1" />
	<field name="aprx" descr="Active (operational) pause policy on RX\;0: ignore received pause frames\;1: respect received pause frames" access="RO" offset="0xC.30" size="0x0.1" />
	<field name="pprx" descr="Admin pause policy on RX (see also pfcrx):\;0: ignore received pause frames (default)\;1: respect received pause frames" access="RW" offset="0xC.31" size="0x0.1" />
	<field name="device_stall_critical_watermark" descr="Valid only on HCAs (When health_mon_rx_activity is set).\;The maximum period for a single received packet process\;ing, if the packet was not processed during this time, the \;device will be declared as stalled and will increase the \;device_stall_critical_watermark_cnt (PPCNT) counter. Value \;given in mSec, The maximum period is 8 sec. \;The special value of 0, indicates that the device_stall_criti\;cal_watermark is inactive.\;Range: 0x0050 - 0x1F40 \;see also critical_stall_mask" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="device_stall_minor_watermark" descr="Valid only on HCAs (When health_mon_rx_activity is set).\;The maximum period for a single received packet process\;ing, if the packet was not processed during this time, the \;device will increase the device_stall_minor_watermark_cnt \;(PPCNT). Value given in mSec, The maximum period is 8 \;sec. \;The special value of 0, indicates that the device_stall_mi\;nor_watermark is inactive.\;Range: 0x0050 - 0x1F40 \;see also critical_stall_mask" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="pgmr_ext" descr="" size="0x18.0" >
	<field name="pg_sel" descr="Selection between an operation on a local port or a group, \;for &apos;set&apos; and &apos;get&apos; operations. \;0 - local port (group field is neglected even if set)\;1 - group (local_port field is neglected even if set)" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR Main\;5 - USR Tile\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="group" descr="Group number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB / label port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="group_of_port" descr="The corresponding group number for the local_port" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="ports_mapping_of_group" descr="A bit map of all available local ports in the system (each bit \;represents a local port). \;The corresponding bits which represent the local ports for \;the specific group in the group field, are set to &apos;1&apos;.\;If set to &apos;0&apos; - not in that specific group or not available." access="RW" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
</node>

<node name="pguid_reg_ext" descr="" size="0x60.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sys_guid" descr="System GUID" access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="node_guid" descr="Node GUID" access="RO" high_bound="3" low_bound="0" offset="0x14.0" size="0x10.0" />
	<field name="port_guid" descr="Port GUID" access="RO" high_bound="3" low_bound="0" offset="0x24.0" size="0x10.0" />
	<field name="allocated_guid" descr="Allocated GUID" access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
</node>

<node name="phys_layer_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear \;event in msec.\;[Internal] supported in USR" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear \;event in msec.\;[Internal] supported in USR" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="symbol_errors_high" descr="Perf.PortCounters(SymbolErrorCounter) = \;Perf.PortCounters(UnknownSymbol)\;[Internal] supported in USR" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="symbol_errors_low" descr="Perf.PortCounters(SymbolErrorCounter) = \;Perf.PortCounters(UnknownSymbol)\;[Internal] supported in USR" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="sync_headers_errors_high" descr="Perf.PortExtendedSpeedsCounters(Synch\;HeaderErrorCounter)" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="sync_headers_errors_low" descr="Perf.PortExtendedSpeedsCounters(Synch\;HeaderErrorCounter)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane0Counter) / BIP error counter, \;lane 0\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 0\;[Internal] supported in USR" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane0Counter) / BIP error counter, \;lane 0\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 0\;[Internal] supported in USR" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane1Counter) / BIP error counter, \;lane 1\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 1\;[Internal] supported in USR" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane1Counter) / BIP error counter, \;lane 1\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 1\;[Internal] supported in USR" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane2Counter) / BIP error counter, \;lane 2\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 2\;[Internal] supported in USR" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane2Counter) / BIP error counter, \;lane 2\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 2\;[Internal] supported in USR" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane3Counter) / BIP error counter, \;lane 3\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 3\;[Internal] supported in USR" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDe\;tectionPerLane3Counter) / BIP error counter, \;lane 3\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 3\;[Internal] supported in USR" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;recableBlockCounter)" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;recableBlockCounter)" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FEUncor\;recableBlockCounter)" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_low" descr="Perf.PortExtendedSpeedsCounters(FEUncor\;recableBlockCounter)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_high" descr="The number of RS-FEC blocks received that \;had no errors.\;Note: Total rs_fec blocks received = \;rs_fec_corrected_blocks + rs_fec_uncorrect\;able_blocks + rs_fec_no_errors_blocks" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_low" descr="The number of RS-FEC blocks received that \;had no errors.\;Note: Total rs_fec blocks received = \;rs_fec_corrected_blocks + rs_fec_uncorrect\;able_blocks + rs_fec_no_errors_blocks" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_high" descr="Perf.PortExtendedSpeedCounters(PortFEC\;CorrectedSymbolCounter)" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_low" descr="Perf.PortExtendedSpeedCounters(PortFEC\;CorrectedSymbolCounter)" access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_high" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane0)" access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_low" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane0)" access="RO" offset="0xA4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_high" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane1)" access="RO" offset="0xA8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_low" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane1)" access="RO" offset="0xAC.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_high" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane2)" access="RO" offset="0xB0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_low" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane2)" access="RO" offset="0xB4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_high" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane3)" access="RO" offset="0xB8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_low" descr="Perf.PortExtendedSpeedCounters(FECCor\;rectedSymbolCounterLane3)" access="RO" offset="0xBC.0" size="0x4.0" />
</node>

<node name="phys_layer_stat_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear \;event in msec.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear \;event in msec.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="phy_received_bits_high" descr="This counter provides information on the total \;amount of traffic (bits) received.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="phy_received_bits_low" descr="This counter provides information on the total \;amount of traffic (bits) received.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="phy_symbol_errors_high" descr="This counter provides information on error \;bits that were not corrected by phy correction \;mechanisms. (FEC + PLR)\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="phy_symbol_errors_low" descr="This counter provides information on error \;bits that were not corrected by phy correction \;mechanisms. (FEC + PLR)\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="phy_corrected_bits_high" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="phy_corrected_bits_low" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_high" descr="This counter provides information on error \;bits that were identified on lane 0. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_low" descr="This counter provides information on error \;bits that were identified on lane 0. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_high" descr="This counter provides information on error \;bits that were identified on lane 1. \;When FEC is enabled this induction corre\;sponds to corrected errors\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 1\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_low" descr="This counter provides information on error \;bits that were identified on lane 1. \;When FEC is enabled this induction corre\;sponds to corrected errors\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 1\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_high" descr="This counter provides information on error \;bits that were identified on lane 2. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 2\;\;\;\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_low" descr="This counter provides information on error \;bits that were identified on lane 2. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 2\;\;\;\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_high" descr="This counter provides information on error \;bits that were identified on lane 3. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 3\;\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_low" descr="This counter provides information on error \;bits that were identified on lane 3. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 3\;\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_high" descr="This counter provides information on error \;bits that were identified on lane 4. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 4\;\;\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_low" descr="This counter provides information on error \;bits that were identified on lane 4. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 4\;\;\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_high" descr="This counter provides information on error \;bits that were identified on lane 5. \;When FEC is enabled this induction corre\;sponds to corrected errors\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 5\;\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_low" descr="This counter provides information on error \;bits that were identified on lane 5. \;When FEC is enabled this induction corre\;sponds to corrected errors\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 5\;\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_high" descr="This counter provides information on error \;bits that were identified on lane 6. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 6\;\;\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_low" descr="This counter provides information on error \;bits that were identified on lane 6. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 6\;\;\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_high" descr="This counter provides information on error \;bits that were identified on lane 7. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 7\;\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_low" descr="This counter provides information on error \;bits that were identified on lane 7. \;When FEC is enabled this induction corre\;sponds to corrected errors.\;In PRBS test mode, indicates the number of \;PRBS errors\;on lane 7\;\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="raw_ber_coef" descr="Raw_BER = raw_ber_coef*10^(-raw_ber_\;magnitude)\;" access="RO" offset="0x60.0" size="0x0.4" />
	<field name="raw_ber_magnitude" descr="Raw_BER = raw_ber_coef*10^(-raw_ber_\;magnitude)\;" access="RO" offset="0x60.8" size="0x0.8" />
	<field name="effective_ber_coef" descr="post_fec_BER = \;post_fec_ber_coef*10^(-post_fec_ber_mag\;nitude)\;" access="RO" offset="0x64.0" size="0x0.4" />
	<field name="effective_ber_magnitude" descr="post_fec_BER = \;post_fec_ber_coef*10^(-post_fec_ber_mag\;nitude)\;" access="RO" offset="0x64.8" size="0x0.8" />
	<field name="symbol_fec_ber_coef" descr="Symbol_BER = \;symbol_ber_coef*10^(-symbol_ber_magni\;tude)" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="symbol_ber_magnitude" descr="Symbol_BER = \;symbol_ber_coef*10^(-symbol_ber_magni\;tude)" access="RO" offset="0x68.8" size="0x0.8" />
	<field name="phy_effective_errors_high" descr="This counter provides information on error \;bits that were not corrected by FEC correction \;algorithm or that FEC is not active.\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="phy_effective_errors_low" descr="This counter provides information on error \;bits that were not corrected by FEC correction \;algorithm or that FEC is not active.\;" access="RO" offset="0x80.0" size="0x4.0" />
</node>

<node name="pltc_reg_ext" descr="" size="0x10.0" >
	<field name="lane_mask" descr="for set operation, lane bitmask\;for query operation, one-hot key" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way \;local_port is interpreted:\;0: Local_port_number\;1: Label_port_number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="local_tx_precoding_cap_mask" descr="0x0 - no tx precoding available / no override capabilty\;Note: All PAM4 devices of 16nm should be updated to \;have precoding\;\;Bit 0- tx precoding override possible via local_tx_pre\;coding_admin field" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="local_tx_precoding_admin" descr="0 - auto\;1 - force Tx precoding\;2 - force Tx without precoding" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="local_rx_precoding_admin" descr="Rx configuration override for 100g Pam4 per lane pro\;tocols.\;0 - auto\;1 - Rx precoding enabled. \;if negotiated, request Tx precoding from peer.\;2 - Rx precoding disabled. \;if negotiated, request no Tx precoding from peer\;" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="local_tx_precoding_oper" descr="0 - unknown / no active link\;1 - Tx precoding enabled.\;2 - Tx precoding disabled." access="RO" offset="0xC.0" size="0x0.2" />
	<field name="local_rx_precoding_oper" descr="Rx precoding operational mode\;0 - unknown / no active link\;1 - Rx precoding enabled. \;2 - Rx precoding disabled." access="RO" offset="0xC.16" size="0x0.2" />
</node>

<node name="pmaos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Module state (reserved while admin_status is dis\;abled):\;0: initializing\;1: plugged_enabled\;2: unplugged\;3: module_plugged_with_error - (details in error_\;type).\;4: plugged_disabled" access="RO" enum="initializing=0x0,plugged_enabled=0x1,unplugged=0x2,module_plugged_with_error=0x3,plugged_disabled=0x4" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Module administrative state (the desired state of the \;module):\;1: enabled\;2: disabled_by_configuration\;3: enabled_once - if the module is active and then \;unplugged, or module experienced an error event, the \;operational status should go to &quot;disabled&quot; and can \;only be enabled upon explicit enable command.\;\;Note - To disable a module, all ports associated with \;the port must be disabled first.\;" access="RW" enum="enabled=0x1,disabled_by_configuration=0x2,enabled_once=0x3" offset="0x0.8" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is \;available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rst" descr="Module Reset toggle\;NOTE: setting reset while module is plugged-in will \;result in transition of oper_status to initialization." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="e" descr="Event Generation on operational state change:\;0: Do_not_generate_event\;1: Generate_Event \;2: Generate_Single_Event" access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="error_type" descr="Module error details:\;0x0: Power_Budget_Exceeded\;0x1: Long_Range_for_non_MLNX_cable_or_module\;0x2: Bus_stuck - (I2C Data or clock shorted)\;0x3: bad_or_unsupported_EEPROM\;0x4: Enforce_part_number_list\;0x5: unsupported_cable\;0x6: High_Temperature\;0x7: bad_cable - (Module/Cable is shorted)\;0x8: PMD_type_is_not_enabled - (see PMTPS).\;0xc: pcie_system_power_slot_Exceeded\;Valid only when oper_status = 4&apos;b0011." access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc" offset="0x4.8" size="0x0.4" />
	<field name="operational_notification" descr="This notification can occur only if module passed ini\;tialization process\;0x0: No notifications.\;0x1: Speed degradation - the module is not enabled in \;its full speed due to incompatible transceiver/cable \;Valid only when oper_status = 4&apos;b0001." access="RO" offset="0x4.16" size="0x0.4" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation \;will be updated based on the e field. Only relevant on \;Set operations." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin \;state will be updated based on admin_state field. Only \;relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pmcr_reg_ext" descr="" size="0x1c.0" >
	<field name="error_code_response" descr="Valid for CMIS modules.\;error code response on override values.\;0x0: ConfigUndefined\;0x1: ConfigSuccess\;0x2: ConfigRejected\;0x3: ConfigRejectedInvalidAppSel\;0x4: ConfigRejectedInvalidDataPath\;0x5: ConfigRejectedInvalidSI\;0x6: ConfigRejectedLanesInUse\;0x7: ConfigRejectedPartialDataPath\;0xC: ConfigInProgress" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cs_sel" descr="Valid only for CMIS (QSFP-DD / SFP-DD / OSFP) compliant \;modules.\;If Control Set 1 not implemented or non CMIS module ignore \;field.\;0 - Auto (default)\;1 - Use Control Set 0\;2 - Use Control Set 1" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="cdr_override_cntl" descr="Module CDR override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="cdr_override_cap" descr="Module TX and RX override control capability.\;Bit 0 - RX CDR control is possible\;Bit 0 - TX CDR control is possible" access="RO" offset="0x4.2" size="0x0.2" />
	<field name="cdr_override_value" descr="Valid only in case CDR is configured to override mode by \;cdr_override_cntl: \;0 - RX OFF, TX OFF\;1 - RX ON , TX OFF\;2 - RX OFF, TX ON\;3 - RX ON, TX ON" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="tx_disable_override_cntl" descr="In HCA, valid based on PCAM feature capabilities. \;Module TX_DISABLE override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="tx_disable_override_value" descr="Valid only in case TX_DISABLE is configured to override mode \;by tx_disable_override_cntl: \;0 - TX_DISABLE is low (i.e. TX is enabled)\;1 - TX_DISABLE is high (i.e. TX is disabled)" access="RW" offset="0x4.24" size="0x0.2" />
	<field name="rx_amp_override_cntl" descr="Module RX amplitude override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="rx_amp_override_value" descr="Valid only in case RX amplitude is configured to override \;mode by rx_amp_override_cntl" access="RW" offset="0x8.8" size="0x0.4" />
	<field name="rx_los_override_cntl" descr="Valid only in case RX _LOS is configured to override mode by \;rx_los_override_admin" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="rx_los_override_admin" descr="Module RX _LOS override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x8.24" size="0x0.2" />
	<field name="rx_emp_override_cntl" descr="Module RX emphasis override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0xC.0" size="0x0.2" />
	<field name="rx_emp_override_value" descr="For CMIS modules, pre emphasis equalization value.\;For SFF modules, emphasis equalization value.\;Valid only in case RX emphasis is configured to override mode \;by rx_emp_override_cntl" access="RW" offset="0xC.8" size="0x0.4" />
	<field name="rx_post_emp_override_cntl" descr="Module RX emphasis override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0xC.16" size="0x0.2" />
	<field name="rx_post_emp_override_value" descr="Valid for CMIS modules only.\;Post emphasis equalization value.\;Valid only in case RX emphasis is configured to override mode \;by rx_post_emp_override_cntl" access="RW" offset="0xC.24" size="0x0.4" />
	<field name="tx_equ_override_cntl" descr="Module TX equalization override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x10.0" size="0x0.2" />
	<field name="tx_equ_override_value" descr="Valid only in case TX equalization is configured to override \;mode by tx_equ_override_cntl." access="RW" offset="0x10.8" size="0x0.4" />
	<field name="tx_adaptive_override_value" descr="0 - disable adaptive Tx Equailization\;1 - enable adaptive Tx equalization\;Valid only in case TX equalization is configured to override \;mode by tx_adaptive_override_cntrl." access="RW" offset="0x10.17" size="0x0.1" />
	<field name="tx_adaptive_override_cntrl" descr="Module adaptive tuning flow override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - override" access="RW" offset="0x10.24" size="0x0.2" />
	<field name="ap_sel_override_cntrl" descr="Module Application select override control:\;0 - Auto (default)\;1 - Use Module&apos;s Default application value\;2 - Override" access="RW" offset="0x18.0" size="0x0.2" />
	<field name="ap_sel_override_value" descr="Application Select from the applications list advertised by the \;module. Up to 15 applications available.\;\;Values range from 1 to 15.\;\;Note: application can be set with default SI values defined by \;the module or SI defined by the host" access="RW" offset="0x18.8" size="0x0.4" />
</node>

<node name="pmlp_reg_ext" descr="" size="0x40.0" >
	<field name="width" descr="0: unmap_local_port\;1: x1 - lane 0 is used\;2: x2 - lanes 0,1 are used\;4: x4 - lanes 0,1,2 and 3 are used\;8: x8 - lanes 0-7 are used\;\;Other - reserved" access="RW" enum="unmap_local_port=0x0,x1=0x1,x2=0x2,x4=0x4,x8=0x8" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="m_lane_m" descr="Module lane mapping: \;0 - Local to Module mapping include module lanes mapping\;1 - Local to Module mapping only, without lane mapping\;\;When this operational is set (&apos;1&apos;), the following fields are \;ignored in SET command and should return the value &quot;0&quot; in \;GET commands: \;PMLP.rxtx\;PMLP.lane&lt;i&gt;_module_mapping.tx_lane\;PMLP.lane&lt;i&gt;_module_mapping.rx_lane" access="OP" offset="0x0.28" size="0x0.1" />
	<field name="rxtx" descr="Use different configuration for RX and TX.\;If this bit is cleared, the TX value is used for both RX and TX. \;When set, the RX configuration is taken from the separate \;field. This is to enable backward compatible implementation." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="lane_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;See Table 1237, &quot;Lane to Module Mapping Layout,&quot; on \;page 1522." subnode="lane_2_module_mapping_ext" access="RW" high_bound="7" low_bound="0" offset="0x4.0" size="0x20.0" />
</node>

<node name="pmmp_reg_ext" descr="" size="0x28.0" >
	<field name="sticky" descr="When set will keep eeprom_override values after plug out \;event" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is avail\;able." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="eeprom_override" descr="Override/ignore EEPROM advertisement properties bitmask: \;Bit 0 - Override cable protocols and technology for QSFP\;Bit 1 - Override cable protocols and technology for SFP\;Bit 2 - Ignore Power Class (set high power)\;Bit 3 - Override Cable Length \;Bit 4 - Override Attenuation\;\;Bit 8 - Set Module to Low Power\;Bit 9 - Override cable protocols and technology for CMIS \;based modules (QSFP-DD/ OSFP/ DSFP/ SFP-DD)" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="eeprom_override_mask" descr="Write Mask bit (negative polarity):\;0 - allow write\;1 - ignore write\;On write commands, indicates which of the bits from \;eeprom_override field are updated.\;Reserved on read operations." access="WO" offset="0x4.16" size="0x0.16" />
	<field name="qsfp_cable_protocol_technology" descr="Protocol technology override for QSFP cable or CMIS based \;cable (QSFP-DD/OSFP)\;Valid only when the protocols and technology for QSFP is \;overridden as indicated by eeprom_override\;Table  1261, &quot;PMMP - QSFP Protocol Bytes Override Layout,&quot; \;on page  1539\;\;Valid only when the protocols and technology is overridden as \;indicated by eeprom_override\;Table  1265, &quot;PMMP - CMIS Protocol Bytes Override Layout,&quot; \;on page  1544" access="RW" high_bound="2" low_bound="0" offset="0x8.0" size="0xc.0" />
	<field name="sfp_cable_protocol_technology" descr="Valid only when the protocols and technology is overridden as \;indicated by eeprom_override\;Table  1263, &quot;PMMP - SFP Protocol Bytes Override Layout,&quot; \;on page  1542" access="RW" high_bound="2" low_bound="0" offset="0x14.0" size="0xc.0" />
	<field name="cable_length" descr="Length of cable assembly, units of 1 m for non CMIS cables.\;\;for CMIS cables, represents cable length field:\;bits 6:7 represent cable_length_multiplier for calculating \;cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;Valid only when the cable length is overridden as indicated by \;eeprom_override." access="RW" offset="0x20.0" size="0x0.8" />
	<field name="attenuation_5g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x24.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 7GHz in db." access="RW" offset="0x24.8" size="0x0.8" />
	<field name="attenuation_12g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 12GHz in db." access="RW" offset="0x24.16" size="0x0.8" />
	<field name="attenuation_25g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 25GHz in db." access="RW" offset="0x24.24" size="0x0.8" />
</node>

<node name="pmpd_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0 - Diagnostic data not supported\;1 - Normal mission mode. \;2 - PRBS checker is not locked. \;3 - PRBS checker is locked." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="cl" descr="clear counters" access="OP" offset="0x0.4" size="0x0.1" />
	<field name="lane" descr="Module lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="host_media" descr="Host or Media lanes\;0 - Media lanes\;1 - Host lanes" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="module" descr="module to access" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is avail\;able." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="errors_cap" descr="Bits Errors count capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="ber_cap" descr="BER measure capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="snr_cap" descr="SNR measure capability" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="prbs_bits_high" descr="This counter provides information on the total amount of \;prbs traffic (bits) received on module&apos;s side." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="prbs_bits_low" descr="This counter provides information on the total amount of \;prbs traffic (bits) received on module&apos;s side." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="prbs_errors_high" descr="This counter provides information on the total amount of \;prbs errors detected on module&apos;s side." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="prbs_errors_low" descr="This counter provides information on the total amount of \;prbs errors detected on module&apos;s side." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="measured_snr" descr="SNR in dB\;0 - not supported." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ber_coef" descr="BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x18.0" size="0x0.4" />
	<field name="ber_magnitude" descr="BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x18.8" size="0x0.8" />
</node>

<node name="pmpt_reg_ext" descr="" size="0x1c.0" >
	<field name="status" descr="0 - Normal mission mode. \;1 - Module is not connected OR module doesn&apos;t support \;PRBS and diagnostics data\;2 - unsupported configuration setting\;3 - PRBS Generator only\;4 - PRBS Checker only \;5 - PRBS traffic both Checker and Generator\;Note: For lock status on PRBS data see PMPD.status" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="lane_mask" descr="Reserved when (le=0 or ls = 0)\;Logical lane number mask.\;For Get operation One-Hot key (Only one bit set)" access="INDEX" offset="0x0.4" size="0x0.8" />
	<field name="host_media" descr="Host or Media lanes\;0 - Media lanes\;1 - Host lanes" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="invt_cap" descr="PRBS inversion is supported" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="swap_cap" descr="PAM4 MSB&lt;-&gt; LSB swapping is supported by the module" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="module" descr="module index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is avail\;able." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PMPT \;configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane \;based on lane index" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support/capability: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS is disabled.\;1 - PRBS is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="Supported module&apos;s PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23 (x^23 + x^18 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 17 - PRBS13 (x^13 + x^12 + x^2+ x + 1)\;Bit 21 - SSPR\;Bit 22 - SSPRQ" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; \;7):\;0 - NRZ test pattern\;1 - PAM4 encoding" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="ch_ge" descr="0 - Access is for both Checker and Generator (Can be used \;for Set operations only)\;1 - Access is for Generator\;2 - Access if for Checker\;Note: Checker and Generator must be in same rate" access="INDEX" offset="0x8.4" size="0x0.2" />
	<field name="invt_admin" descr="PRBS inversion enable bit, see ivnt_cap:\;0 - NO PRBS inversion\;1 - PRBS inversion" access="RW" offset="0x8.8" size="0x0.1" />
	<field name="swap_admin" descr="PAM4 MSB&lt;-&gt; LSB swapping enable bit, see swap_cap. \;0 - NO MSB&lt;-&gt; LSB swapping \;1 - MSB &lt;-&gt; LSB swapping" access="RW" offset="0x8.9" size="0x0.1" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23 (x^23 + x^18 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0x11 - PRBS13 (x^13 + x^12 + x^2+ x + 1)\;0x15 - SSPR\;0x16 - SSPRQ" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - Reserved\;Bit 3- 10GE/40GE (10.3125 Gb/s) \;Bit 4- FDR (14.0625 Gb/s) \;Bit 5- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 6- Reserved \;Bit 7- HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s) \;Bit 8- NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / \;106.25Gb/s)" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - Non selected. \;1 - 1GE (1.25 Gb/s)\;2 - SDR (2.5 Gb/s) \;8 - 10GE/40GE (10.3125 Gb/s) \;16 - FDR (14.0625 Gb/s) \;32 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;128 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s) \;256 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / \;106.25Gb/s)\;" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="pmtu_reg_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="max_mtu" descr="Maximum MTU supported on the port (Read Only).\;MTU depends on the port type. When port type (Eth/IB/FC) is \;configured, the relevant MTU is reported. When the port type \;is not configured, the minimum between the max_mtu for \;the different types (Eth/IB/FC) is reported." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="admin_mtu" descr="Administratively configured MTU on the port. Must be \;smaller or equal to max_mtu." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="oper_mtu" descr="Operational MTU. This is the actual MTU configured on the \;ports. Packets exceeding this size will be dropped.\;Note: In Ethernet or FC, oper_mtu is equal to admin_mtu. In \;InfiniBand, the actual operational MTU is reported which \;may be smaller than admin_mtu." access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="port_state_behavior_ext" descr="" size="0x10.0" >
	<field name="enforce_port_state_enabled" descr="0x0: DISABLED\;0x1: ENABLED - regular driver will be able to enforce \;physical port state." access="RW" enum="DISABLED=0x0,ENABLED=0x1" offset="0x0.31" size="0x0.1" />
</node>

<node name="ppad_reg_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="If single_base_mac = 0 - base MAC address, \;\;For HCA mac[7:0] is reserved \;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Port number\;Reserved when single_base_mac = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="single_base_mac" descr="0: base_mac, local_port should be 0 and mac[6:0]and mac \;[5:0] are reserved in Spectrum-2 and Spectrum accor\;dantly.HW will set incremental \;1: single_mac - mac of the local_port\;Reserved for SwitchX/-2." access="OP" offset="0x0.28" size="0x0.1" />
	<field name="mac_31_0" descr="If single_base_mac = 0 - base MAC address, \;\;For HCA mac[7:0] is reserved \;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="ppaos_reg_ext" descr="" size="0x10.0" >
	<field name="phy_test_mode_status" descr="Port extended down status:\;0: regular_operation - (port down/up according to \;PAOS) \;1: phy_test_mode\;phy test mode can be valid only when PAOS.admin\;_status=2 and PAOS.oper_status=2 (i.e port is down)." access="RO" enum="regular_operation=0x0,phy_test_mode=0x1" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR Main\;5 - USR Tile\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="phy_test_mode_admin" descr="Port extended administrative down status:\;0: regular_operation (port down/up according to \;PAOS) \;1: phy_test_mode \;\;The phy test mode (1) can be set only when \;PAOS.admin_status=2 (i.e port configuration is down)." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the \;router port. In this case, the swid indicates which of \;the router ports to configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="phy_status" descr="rx phy status:\;0: rx_phy_down\;1: rx_phy_up\;2: rx_phy_down_by_command\;\;Note: The phy up indication is according to protocol \;(up == align_status=true)\;i.g. In PRBS test mode phy up is when PRB is lock \;(up== prbs lock)" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="phy_status_admin" descr="rx phy port admin. Controls phy entities operational \;port status.\;valid for port_type &lt;&gt; &apos;0&apos;.\;to operate link status for port_type &apos;0&apos; use \;PAOS.admin_status.\;0: rx_phy_down\;1: rx_phy_up\;" access="RW" offset="0x4.8" size="0x0.4" />
</node>

<node name="ppcc_reg_ext" descr="" size="0xfc.0" >
	<field name="cmd_type" descr="0x0- get algo info\;0x1- enable algo\;0x2- disable algo\;0x3- get algo enabling status\;0x4- get num of params\;0x5- get param info\;0x6- get param\;0x7- get &amp; clear param\;0x8- set param\;" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="algo_index" descr="Selects the algo to operate on (0 - algo at bit #0, 1 - algo at bit \;#1, etc). \;For command types other than 0 (get algo info), must point to \;a present algo (an algo with a non-zero algo number - as \;returned via Command type 0)" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="algo_param_index" descr="Selects the specific param to get/set (if applicable, 0 if not). \;Index is zero-based. Must be smaller than value returned in \;&quot;get_num_of_params." access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="value" descr="For cmd_type = 0x0: returns 32-bit algo_num or 0 if no algo is \;available at this index\;For cmd_type = 0x3: returns 1 if enabled, 0 otherwise\;For cmd_type = 0x4: returns num of params algo has\;For cmd_type = 0x6:: returns value of param (selected by \;param index)\;For cmd_type = 0x7: returns value of param (selected by \;param index) and clears param\;For cmd_type = 0x8: The value to write to param (selected by \;param index). Set by the user. Set command is silently ignored \;if value outside min..max values (comparison is unsigned) or \;if param permission is not read-write.\;\;For cmd_type = 0x1 OR 0x2 OR 0x5 : returns 0 \;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="param_value1" descr="For cmd_type = 0x5: return default value of param\;\;\;\;Reserved for other commands\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="param_value2" descr="For cmd_type = 0x5: return min legal value of param\;\;\;\;Reserved for other commands\;\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="param_value3" descr="For cmd_type = 0x5: return max legal value of param\;\;\;\;Reserved for other commands\;\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="prm" descr="For cmd_type = 0x5:\;0-param is read-only\;1-param is read-write\;2-param is read-only but may also be accessed and cleared \;via &quot;get &amp; clear&quot; command\;\;Reserved for other commands\;" access="RO" offset="0x1C.0" size="0x0.2" />
	<field name="text_length" descr="For cmd_type = 0x5 OR cmd_type = 0x0  :Length in bytes of \;text field\;Reserved for other commands\;" access="RO" offset="0x1C.8" size="0x0.8" />
	<field name="text" descr="ASCII string \;For get cmd_type = 0x0: algo textual description \;For get cmd_type = 0x5: param textual description\;Reserved for other commands" access="RO" high_bound="54" low_bound="0" offset="0x20.0" size="0xdc.0" />
</node>

<node name="ppcnt_infiniband_packets_counter_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear \;event in msec." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear \;event in msec." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_high" descr="" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_low" descr="" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_high" descr="" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_low" descr="" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="sync_header_error_counter_high" descr="" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="sync_header_error_counter_low" descr="" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="port_local_physical_errors_high" descr="" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_local_physical_errors_low" descr="" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="port_malformed_packet_errors_high" descr="" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="port_malformed_packet_errors_low" descr="" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="port_buffer_overrun_errors_high" descr="" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="port_buffer_overrun_errors_low" descr="" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="port_dlid_mapping_errors_high" descr="" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="port_dlid_mapping_errors_low" descr="" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="port_vl_mapping_errors_high" descr="" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="port_vl_mapping_errors_low" descr="" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="port_looping_errors_high" descr="" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_looping_errors_low" descr="" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="port_inactive_discards_high" descr="" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="port_inactive_discards_low" descr="" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="port_neighbor_mtu_discards_high" descr="" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="port_neighbor_mtu_discards_low" descr="" access="RO" offset="0x5C.0" size="0x4.0" />
</node>

<node name="ppcnt_plr_counters_ext" descr="" size="0xf8.0" >
	<field name="plr_rcv_codes_high" descr="Number of received PLR codewords\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="plr_rcv_codes_low" descr="Number of received PLR codewords\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="plr_rcv_code_err_high" descr="The total number of bad codewords received \;(including uncorrectable)." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="plr_rcv_code_err_low" descr="The total number of bad codewords received \;(including uncorrectable)." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="plr_rcv_uncorrectable_code_high" descr="The number of uncorrectable codewords \;received\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="plr_rcv_uncorrectable_code_low" descr="The number of uncorrectable codewords \;received\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="plr_xmit_codes_high" descr="Number of transmitted PLR codewords" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="plr_xmit_codes_low" descr="Number of transmitted PLR codewords" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_high" descr="The total number of codewords retransmitted." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_low" descr="The total number of codewords retransmitted." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_high" descr="The total number of retransmitted event. \;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_low" descr="The total number of retransmitted event. \;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="plr_sync_events_high" descr="The number of sync events" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="plr_sync_events_low" descr="The number of sync events" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="hi_retransmission_rate_high" descr="High retransmission rate\;The number of the retransmission rate has \;crossed the retransmission rate threshold\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="hi_retransmission_rate_low" descr="High retransmission rate\;The number of the retransmission rate has \;crossed the retransmission rate threshold\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_within_t_sec_max_high" descr="The maximum number of retransmitted \;events in t sec window\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_within_t_sec_max_low" descr="The maximum number of retransmitted \;events in t sec window\;" access="RO" offset="0x44.0" size="0x4.0" />
</node>

<node name="ppcnt_reg_counter_set_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="eth_802_3_cntrs_grp_data_layout_ext" descr="" subnode="eth_802_3_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="IEEE_802_3_Counters" size="0xf8.0" />
	<field name="eth_2863_cntrs_grp_data_layout_ext" descr="" subnode="eth_2863_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_2863_Counters" size="0xf8.0" />
	<field name="eth_2819_cntrs_grp_data_layout_ext" descr="" subnode="eth_2819_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_2819_Counters" size="0xf8.0" />
	<field name="eth_3635_cntrs_grp_data_layout_ext" descr="" subnode="eth_3635_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_3635_Counters" size="0xf8.0" />
	<field name="eth_extended_cntrs_grp_data_layout_ext" descr="" subnode="eth_extended_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="Ethernet_Extended_Counters" size="0xf8.0" />
	<field name="eth_discard_cntrs_grp_ext" descr="" subnode="eth_discard_cntrs_grp_ext" offset="0x0.0" selected_by="Ethernet_Discard_Counters" size="0xf8.0" />
	<field name="link_level_retrans_cntr_grp_data_ext" descr="" subnode="link_level_retrans_cntr_grp_data_ext" offset="0x0.0" selected_by="Link_Level_Retransmission_Counters" size="0xf8.0" />
	<field name="eth_per_prio_grp_data_layout_ext" descr="" subnode="eth_per_prio_grp_data_layout_ext" offset="0x0.0" selected_by="Per_Priority_Counters" size="0xf8.0" />
	<field name="eth_per_traffic_class_layout_ext" descr="" subnode="eth_per_traffic_class_layout_ext" offset="0x0.0" selected_by="Per_Traffic_Class_Counters" size="0xf8.0" />
	<field name="phys_layer_cntrs_ext" descr="" subnode="phys_layer_cntrs_ext" offset="0x0.0" selected_by="Physical_Layer_Counters" size="0xf8.0" />
	<field name="eth_per_traffic_class_cong_layout_ext" descr="" subnode="eth_per_traffic_class_cong_layout_ext" offset="0x0.0" selected_by="Per_Traffic_Class_Congestion_Counters" size="0xf8.0" />
	<field name="eth_per_receive_buffer_grp_ext" descr="" subnode="eth_per_receive_buffer_grp_ext" offset="0x0.0" selected_by="Per_Receive_Buffer_Counters" size="0xf8.0" />
	<field name="phys_layer_stat_cntrs_ext" descr="" subnode="phys_layer_stat_cntrs_ext" offset="0x0.0" selected_by="Physical_Layer_Statistical_Counters" size="0xf8.0" />
	<field name="eth_oob_port_cntrs_ext" descr="" subnode="eth_oob_port_cntrs_ext" offset="0x0.0" selected_by="Out_of_Band_Port_Counters" size="0xf8.0" />
	<field name="IB_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_portcntrs_attribute_grp_data_ext" offset="0x0.0" selected_by="InfiniBand_Port_Counters" size="0xf8.0" />
	<field name="IB_long_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_long_portcntrs_attribute_grp_data_ext" offset="0x0.0" selected_by="InfiniBand_Extended_Port_Counters" size="0xf8.0" />
	<field name="ppcnt_plr_counters_ext" descr="" subnode="ppcnt_plr_counters_ext" offset="0x0.0" selected_by="PLR_counters_group" size="0xf8.0" />
	<field name="ppcnt_rs_fec_histograms_counters_ext" descr="" subnode="ppcnt_rs_fec_histograms_counters_ext" offset="0x0.0" selected_by="RS_FEC_Histogram_group" size="0xf8.0" />
	<field name="usr_xsr_physical_layer_ext" descr="" subnode="usr_xsr_physical_layer_ext" offset="0x0.0" selected_by="USR_XSR_Physical_layer_counters_group" size="0xf8.0" />
	<field name="ppcnt_infiniband_packets_counter_ext" descr="" subnode="ppcnt_infiniband_packets_counter_ext" offset="0x0.0" selected_by="Infiniband_pkts_counters" size="0xf8.0" />
</node>

<node name="ppcnt_reg_ext" descr="" size="0x100.0" >
	<field name="grp" descr="Performance counter group.\;Group 63 indicates all groups (include all per priority/TC/Receive Buffer \;counters). Only valid on Set() operation with clr bit set.\;0x0: IEEE_802_3_Counters\;0x1: RFC_2863_Counters\;0x2: RFC_2819_Counters\;0x3: RFC_3635_Counters\;0x5: Ethernet_Extended_Counters\;0x6: Ethernet_Discard_Counters \;0x8: Link_Level_Retransmission_Counters - [Internal]\;0x10: Per_Priority_Counters - \;0x11: Per_Traffic_Class_Counters - \;0x12: Physical_Layer_Counters\;0x13: Per_Traffic_Class_Congestion_Counters\;0x15: Per_Receive_Buffer_Counters - [Internal]\;0x16: Physical_Layer_Statistical_Counters\;0x19: Out_of_Band_Port_Counters - Note: This group is valid only for OOB \;ports - [Internal]\;0x20: InfiniBand_Port_Counters\;0x21: InfiniBand_Extended_Port_Counters\;0x22: PLR_counters_group\;0x23: RS_FEC_Histogram_group\;0x24: USR_XSR_Physical_layer_counters_group - [Internal]\;0x25: Infiniband_pkts_counters - [Internal]\;" access="INDEX" enum="IEEE_802_3_Counters=0x0,RFC_2863_Counters=0x1,RFC_2819_Counters=0x2,RFC_3635_Counters=0x3,Ethernet_Extended_Counters=0x5,Ethernet_Discard_Counters=0x6,Link_Level_Retransmission_Counters=0x8,Per_Priority_Counters=0x10,Per_Traffic_Class_Counters=0x11,Physical_Layer_Counters=0x12,Per_Traffic_Class_Congestion_Counters=0x13,Per_Receive_Buffer_Counters=0x15,Physical_Layer_Statistical_Counters=0x16,Out_of_Band_Port_Counters=0x19,InfiniBand_Port_Counters=0x20,InfiniBand_Extended_Port_Counters=0x21,PLR_counters_group=0x22,RS_FEC_Histogram_group=0x23,USR_XSR_Physical_layer_counters_group=0x24,Infiniband_pkts_counters=0x25" offset="0x0.0" size="0x0.6" />
	<field name="port_type" descr="Supported only when indicated by PCAM on FPGA based NICs:\;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;1: IB_port_number\;2: host_port_number\;3: OOB_port_number - Internal\;\;Note - pnat=2 is supported for &quot;Per Traffic Class Congestion \;Counters&quot; and &quot;Per Traffic Class Counters&quot; groups." access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,host_port_number=0x2,OOB_port_number=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number. \;255 indicates all ports on the device, and is only allowed for \;Set() operation." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must be always 0.\;Switch partition ID to associate port with.\;Switch partitions are numbered from 0 to 7 inclusively.\;Switch partition 254 indicates stacking ports.\;Switch partition 255 indicates all switch partitions.\;Only valid on Set() operation with local_port=255." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="prio_tc" descr="Priority index for per priority counter sets, valid values: 0-7\;For Spectrum-2 and on at tx side range can be 0 .. cap_max_t\;class_data-1, see QGCR.tx_cnt_tclass\;\;Traffic class index for per traffic class counter set, valid val\;ues: \;For Switches, valid values: 0 .. cap_max_tclass_data-1 \;\;For HCA, valid values: 0.. HCA_CAP.max_tc\;\;Otherwise must be 0." access="INDEX" offset="0x4.0" size="0x0.5" />
	<field name="lp_gl" descr="Local Port global variable\;0: local_port port 255 = all ports of the device.\;1: local_port index indicates Local port number." access="OP" offset="0x4.30" size="0x0.1" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value \;for all counters in the counter group. This bit can be set for \;both Set() and Get() operation.\;\;" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;Table  1169, &quot;Ethernet IEEE 802.3 Counters Group Data Lay\;out,&quot; on page  1444\;Table  1171, &quot;Ethernet RFC 2863 Counter Group Data Layout,&quot; \;on page  1449\;Table  1173, &quot;Ethernet RFC 2819 Counter Group Data Layout,&quot; \;on page  1452\;Table  1175, &quot;Ethernet RFC 3635 Counter Group Data Layout,&quot; \;on page  1457\;Table  1177, &quot;Ethernet Extended Counter Group Data Layout,&quot; \;on page  1461\;Table  1180, &quot;Ethernet Discard Counter Group Fields,&quot; on \;page  1466\;Table  1191, &quot;Link Level Retransmission Counter Group Data \;Layout,&quot; on page  1479\;Table  1181, &quot;Ethernet Per Priority Group Data Layout,&quot; on \;page  1468\;Table  1185, &quot;Ethernet Per Traffic Class Group data layout,&quot; on \;page  1476\;Table  1197, &quot;Physical Layer Counters Data Layout,&quot; on \;page  1487\;Table  1187, &quot;Ethernet Per Traffic Class Congestion Group data \;layout,&quot; on page  1477\;Table  1189, &quot;Ethernet Per Receive Buffer Group data layout,&quot; \;on page  1478\;Table  1201, &quot;Physical Layer Statistical Counters Data Layout,&quot; \;on page  1496 \;Table  1183, &quot;Ethernet OOB Port Counters Data Layout,&quot; on \;page  1472 - [Internal]\;Table  1193, &quot;InfiniBand PortCounters Attribute Group Data \;Layout,&quot; on page  1481\;Table  1195, &quot;InfiniBand Extended PortCounters Attribute \;Group Data Layout,&quot; on page  1483\;Table  1203, &quot;PLR Counters Data Layout,&quot; on page  1501 - \;[Internal]\;Table  1205, &quot;RS-Histograms Data Layout,&quot; on page  1503 \;Table  1199, &quot;USR_XSR Physical Layer Counters Data Layout,&quot; \;on page  1492\;Table  1207, &quot;Infiniband Packets Counters Data Layout,&quot; on \;page  1504" subnode="ppcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="ppcnt_rs_fec_histograms_counters_ext" descr="" size="0xf8.0" >
	<field name="hist" descr="Value of RS-hist" subnode="uint64" access="RO" high_bound="15" low_bound="0" offset="0x0.0" size="0x80.0" />
</node>

<node name="pphcr_bin_range_ext" descr="" size="0x4.0" >
	<field name="low_val" descr="low range of bin&apos;s measurement" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="high_val" descr="high range of bin&apos;s measurement" access="RW" offset="0x0.16" size="0x0.4" />
</node>

<node name="pphcr_ext" descr="" size="0x50.0" >
	<field name="we" descr="Support of histogram bins configuration. \;In case this bit is cleared, the port doesn&apos;t support configu\;ration of the histogram bins, for the specific hist_type." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="active_hist_type" descr="0 - invalid (Link down / unsupported) \;1 - KP4 RS-FEC (544,514) errors \;2 - LL RS-FEC (271,257) / (272,257+1) errors\;3 - KR4 RS-FEC (528,514) errors" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="hist_type" descr="0: According to active link\;1: KP4 RS-FEC (544,514) errors \;2: LL RS-FEC (271,257) / (272,257+1) errors\;3: KR4 RS-FEC (528,514) errors" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="num_of_bins" descr="Available number of bins \;" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="hist_min_measurement" descr="Lowest measurement/low limit of the histogram \;Example:\;In case of hist_type = 1, represent KP4 RS FEC symbol \;errors(= 0)\;In case of hist_type = 2, represent LL RS FEC symbol \;errors ( = 0)\;" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="hist_max_measurement" descr="Highest measurement/high limit of the histogram:\;Example:\;In case of hist_type = 1, represent KP4 RS FEC symbol \;errors ( = 15)\;In case of hist_type = 2, represent LL RS FEC symbol \;errors ( = 7)" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="bin_range_write_mask" descr="Valid only if we (write enable) = 1 \;Ignored on GET \;Write mask for the bin_range array. \;If bit X is set, bin_range [X] write should be execute\;Else if bit X is clear, ignored value in written to bin_range \;[X]" access="WO" offset="0xC.0" size="0x0.16" />
	<field name="bin_range" descr="Write to bin_range[x] is applicable only if we = 1 &amp; the cor\;responding bits in bin_range_write_mask is set.\;Mapping of measurement units to a bin\;See Table 1435, &quot;PPHCR - Port Phy Bin Range Histogram \;Configuration Layout,&quot; on page 1754" subnode="pphcr_bin_range_ext" access="RW" high_bound="15" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="pplm_reg_ext" descr="" size="0x50.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Gearbox - Host side)\;2 - Internal IC Port \;3 - Far-End Port (For Gearbox - Line side)\;Other values are reserved.\;\;Using port_type &apos;0&apos; will override all different parts of the link \;structure\;Using port_type &apos;1&apos; will configure also port_type &apos;2&apos; accord\;ingly and vise versa" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fec_mode_active" descr="Active FEC (bitmask)\;0: No_FEC\;1: Firecode_FEC\;2: Standard_RS_FEC - RS(528,514)\;3: Standard_LL_RS_FEC - RS(271,257)\;4: Reserved - [Internal]\;5: reserved - [Internal]\;6: Interleaved_Standard_RS-FEC - (544,514)\;7: Standard_RS-FEC - (544,514)\;8: Zero_Latency_FEC - [Internal]\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - \;(272,257+1)\;11: Interleaved_Standard_RS_FEC_PLR - (544,514)\;12: RS-FEC - (544,514) + PLR\;13: LL-FEC - (271,257) + PLR\;14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - \;(272,257+1) [Internal] \;15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR \;- (272,257+1) [Internal]" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Reserved=0x4,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Zero_Latency_FEC=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS=0xc,LL=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf" offset="0xC.0" size="0x0.24" />
	<field name="fec_override_cap_10g_40g" descr="10GE/40GE Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: Reserved2\;3: Reserved3\;\;" access="RO" enum="No=0x0,Firecode_FEC=0x1,Reserved2=0x2,Reserved3=0x3" offset="0x10.0" size="0x0.4" />
	<field name="fec_override_cap_25g" descr="25GE Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: RS-FEC\;3: Reserved" access="RO" enum="No=0x0,Firecode_FEC=0x1,RS=0x2,Reserved=0x3" offset="0x10.4" size="0x0.4" />
	<field name="fec_override_cap_50g" descr="50GE (2 lanes) Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: RS-FEC\;3: Reserved" access="RO" enum="No=0x0,Firecode_FEC=0x1,RS=0x2,Reserved=0x3" offset="0x10.8" size="0x0.4" />
	<field name="fec_override_cap_100g" descr="100GE (4 lanes) Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Reserved1\;2: RS-FEC - (528,514)\;3: Reserved3" access="RO" enum="No=0x0,Reserved1=0x1,RS=0x2,Reserved3=0x3" offset="0x10.12" size="0x0.4" />
	<field name="fec_override_cap_56g" descr="56GE Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: Reserved2\;3: Reserved3" access="RO" enum="No=0x0,Firecode_FEC=0x1,Reserved2=0x2,Reserved3=0x3" offset="0x10.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_cap" descr="RS-FEC correction bypass override capability:\;0: NO_correction_bypass\;1: RS-FEC_correction_bypass" access="RO" enum="NO_correction_bypass=0x0,RS=0x1" offset="0x10.28" size="0x0.4" />
	<field name="fec_override_admin_10g_40g" descr="10GE/40GE Ethernet FEC override admin, see \;10g_40g_fec_override_cap.\;(one-hot setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC\;\;" access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.0" size="0x0.4" />
	<field name="fec_override_admin_25g" descr="25GE Ethernet FEC override admin, see 25g_fec_override_\;cap. (one-hot setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC\;4: RS-FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_ad\;min must be set with the same value." access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2,RS=0x4" offset="0x14.4" size="0x0.4" />
	<field name="fec_override_admin_50g" descr="50GE Ethernet FEC override admin, see 50g_fec_override_\;cap. (one-hot setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC\;4: RS-FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_ad\;min must be set with the same value." access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2,RS=0x4" offset="0x14.8" size="0x0.4" />
	<field name="fec_override_admin_100g" descr="100GE Ethernet FEC override admin, see 100g_fec_over\;ride_cap. (one-hot setting): \;0: auto_mode - no override\;1: No_FEC\;4: RS-FEC" access="RW" enum="auto_mode=0x0,No_FEC=0x1,RS=0x4" offset="0x14.12" size="0x0.4" />
	<field name="fec_override_admin_56g" descr="56GE Ethernet FEC override admin, see 56g_fec_override_\;cap. (one-hot setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC" access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_admin" descr="RS-FEC correction bypass override admin: (one-hot setting): \;0: auto_mode - no override \;1: NO_correction_bypass\;2: RS-FEC_correction_bypass" access="RW" enum="auto_mode=0x0,NO_correction_bypass=0x1,RS=0x2" offset="0x14.28" size="0x0.4" />
	<field name="fec_override_cap_200g_4x" descr="200GE FEC override capability bitmask:\;Bit 0 - Reserved \;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved \;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium LL RS-FEC (272,257+1)\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;[Internal] Bit 14 - ELL (272,257+1) + PLR\;" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="fec_override_cap_400g_8x" descr="400GE FEC override capability bitmask:\;Bit 0 - Reserved \;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved\;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium LL RS-FEC (272,257+1)\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;[Internal] Bit 14 - ELL (272,257+1) + PLR\;" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="fec_override_cap_50g_1x" descr="50GE single lane override capability bitmask:\;Bit 0 - Reserved \;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved \;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium LL RS-FEC (272,257+1)\;[Internal] Bit 12 - RS-FEC - (544,514) + PLR\;[Internal] Bit 13 - LL-FEC - (271,257) + PLR\;[Internal] Bit 14 - ELL - (272,257+1) + PLR" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="fec_override_cap_100g_2x" descr="100GE over 2 lanes, FEC override capability bitmask:\;Bit 0 - Reserved\;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved \;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium Low Latency RS-FEC \;(272,257+1)\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;[Internal] Bit 14 - ELL (272,257+1) + PLR\;" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="fec_override_admin_200g_4x" descr="200GE FEC override admin bitmask (one-hot setting) \;0: Auto_mode\;7: RS-FEC - (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;Bit 9 is set - RS-FEC (272,257+1)\;[Internal] Bit 12 is set - RS-FEC (544,514) + PLR\;[Internal] Bit 13 is set - LL-FEC (271,257) + PLR \;[Internal] Bit 14 is set - LL-FEC (272,257+1) + PLR" access="RW" offset="0x20.0" size="0x0.16" />
	<field name="fec_override_admin_400g_8x" descr="400GE FEC override admin bitmast (one-hot setting): \;0: Auto_mode\;7: RS-FEC_(544,514)\;8: Zero_Latency_FEC \;9: RS-FEC_(272,257+1)\;12: RS-FEC_(544,514) - + PLR [Internal]\;13: LL-FEC_(271,257) - + PLR [Internal]\;14: LL-FEC_(272,257+1) - + PLR [Internal]" access="RW" offset="0x20.16" size="0x0.16" />
	<field name="fec_override_admin_50g_1x" descr="50GE, 1lanes FEC override admin bitmask (one-hot setting)\;0 - Auto mode\;Bit 7 is set- RS-FEC (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;Bit 9 is set - RS-FEC (272,257+1)\;[Internal] Bit 12 is set - RS-FEC (544,514) + PLR\;[Internal] Bit 13 is set - LL-FEC (271,257) + PLR \;[Internal] Bit 14 is set - LL-FEC (272,257+1) + PLR" access="RW" offset="0x24.0" size="0x0.16" />
	<field name="fec_override_admin_100g_2x" descr="100GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 0 is set - Reserved\;Bit 2 is set - Reserved \;Bit 7 is set- RS-FEC (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;Bit 9 is set - RS-FEC (272,257+1)\;[Internal] Bit 12 is set - RS-FEC (544,514) + PLR\;[Internal] Bit 13 is set - LL-FEC (271,257) + PLR \;[Internal] Bit 14 is set - LL-FEC (272,257+1) + PLR" access="RW" offset="0x24.16" size="0x0.16" />
	<field name="fec_override_cap_400g_4x" descr="400GE, 4 lanes FEC override capability bitmask :\;Bit 0 -Reserved\;Bit 1- Reserved\;Bit 2- Reserved\;Bit 3- Reserved\;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;Bit 8 - Reserved\;Bit 9- Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;Bit 10- Reserved\;Bit 11 -Reserved\;12: RS-FEC - (544,514) + PLR\;Bit 13 - Reserved\;14: Ethernet_Consortium_LL_50G_RS-FEC - (272,257+1)+ \;PLR [Internal] \;Bit 15 - Reserved" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="fec_override_cap_800g_8x" descr="800GE, 8 lanes FEC override capability bitmask:\;Bit 0 -Reserved\;Bit 1- Reserved\;Bit 2- Reserved\;Bit 3- Reserved\;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;Bit 8 - Reserved\;Bit 9- Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;Bit 10- Reserved\;Bit 11 -Reserved\;12: RS-FEC - (544,514) + PLR\;Bit 13 - Reserved\;14: Ethernet_Consortium_LL_50G_RS-FEC - (272,257+1)+ \;PLR [Internal] \;Bit 15 - Reserved" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="fec_override_cap_100g_1x" descr="100GE, 1 lane FEC override capability bitmask :\;Bit 0 -Reserved\;Bit 1- Reserved\;Bit 2- Reserved\;Bit 3- Reserved \;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Interleaved RS-FEC - (544,514)\;Bit 7 - RS-FEC (544,514)\;Bit 8 - Reserved\;Bit 9- Ethernet Consortium Low Latency RS-FEC (272,257+1)\;Bit 10- interleaved Ethernet_Consortium_LL_50G_RS-FEC- \;(272,257+1)\;11:Interleaved RS-FEC - (544,514) + PLR\;12: RS-FEC - (544,514) + PLR\;13: LL-FEC - (271,257) + PLR\;14: Ethernet_Consortium_LL_50G_RS-FEC - (272,257+1)+ \;PLR [Internal] \;15: Interleave Ethernet_Consortium_LL_50G_RS-FEC- \;(272,257+1) + PLR [Internal]" access="RO" offset="0x2C.0" size="0x0.16" />
	<field name="fec_override_cap_200g_2x" descr="200GE, 2 lanes FEC override capability bitmask :\;Bit 0 -Reserved\;Bit 1- Reserved\;Bit 2- Reserved\;Bit 3- Reserved\;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;Bit 8 - Reserved\;Bit 9- Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;Bit 10- Reserved\;Bit 11 -Reserved\;12: RS-FEC - (544,514) + PLR\;Bit 13 - Reserved\;14: Ethernet_Consortium_LL_50G_RS-FEC - (272,257+1)+ \;PLR [Internal] \;Bit 15 - Reserved" access="RO" offset="0x2C.16" size="0x0.16" />
	<field name="fec_override_admin_400g_4x" descr="400GE, 4 lanes FEC override admin bitmask (one-hot setting):\;0 - Auto mode\;Bit 7 - RS-FEC (544,514)\;Bit 9 - Ethernet Consortium Low Latency RS-FEC (272,257+1)\;Bit 12 - RS-FEC - (544,514) + PLR\;Bit 14 is set: Ethernet_Consortium_LL_50G_RS-FEC - \;(272,257+1)+ PLR [Internal]" access="RW" offset="0x44.0" size="0x0.16" />
	<field name="fec_override_admin_800g_8x" descr="800GE, 8 lanes FEC override admin bitmask (one-hot setting):\;0 - Auto mode\;Bit 7 - RS-FEC (544,514)\;Bit 9 - Ethernet Consortium Low Latency RS-FEC (272,257+1)\;Bit 12 - RS-FEC - (544,514) + PLR\;Bit 14 is set: Ethernet_Consortium_LL_50G_RS-FEC - \;(272,257+1)+ PLR [Internal]" access="RW" offset="0x44.16" size="0x0.16" />
	<field name="fec_override_admin_100g_1x" descr="100GE, 1 lane FEC override admin bitmask (one-hot setting):\;0 - Auto mode\;Bit 6 - Interleaved RS-FEC - (544,514)\;Bit 7 - RS-FEC (544,514)\;Bit 9 - 50G Ethernet Consortium Low Latency RS-FEC \;(272,257+1)\;Bit 10 - interleaved Ethernet_Consortium_LL_50G_RS-FEC- \;(272,257+1)\;Bit 11 is set - Interleaved RS-FEC - (544,514) + PLR\;Bit 12 is set: RS-FEC - (544,514) + PLR\;Bit 14 is set: Ethernet_Consortium_LL_50G_RS-FEC - \;(272,257+1)+ PLR [Internal] \;Bit 15 is set: Interleave Ethernet_Consortium_LL_50G_RS-\;FEC- (272,257+1) + PLR [Internal]" access="RW" offset="0x48.0" size="0x0.16" />
	<field name="fec_override_admin_200g_2x" descr="200GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0 - Auto mode\;Bit 7 - RS-FEC (544,514)\;Bit 9 - Ethernet Consortium Low Latency RS-FEC (272,257+1)\;Bit 12 - RS-FEC - (544,514) + PLR\;Bit 14 is set: Ethernet_Consortium_LL_50G_RS-FEC - \;(272,257+1)+ PLR [Internal]" access="RW" offset="0x48.16" size="0x0.16" />
</node>

<node name="pplr_reg_ext" descr="" size="0x8.0" >
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: Near-End_Port- (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far-End_Port - (For Retimer/Gearbox - Line side)\;4: USR_Main\;5: USR_Tile\;Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near=0x1,Internal_IC_LR_Port=0x2,Far=0x3,USR_Main=0x4,USR_Tile=0x5" offset="0x0.4" size="0x0.4" />
	<field name="op_mod" descr="operational mode for link configurations for phy_ local_loop\;back mode.\;0 - link will operate in optimal latency performance mode\;1 - link will operate in same configurations as operational \;port.\;\;Note: for FEC override via PPLM register, chosen FEC will be \;according to the PPLM configuration that was set and this bit \;will be ignored for FEC purposes" access="OP" offset="0x0.8" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lb_en" descr="Loopback enable - One-hot key.\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback\;Bit 2: External_local_loopback\;Bit 3: Near_end_analog_loopback - [Internal]\;Bit 4: Near_end_digital_loopback - [Internal]\;Bit 7: LL_local_loopback" access="RW" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,Near_end_analog_loopback=0x8,Near_end_digital_loopback=0x10,LL_local_loopback=0x80" offset="0x4.0" size="0x0.8" />
	<field name="lb_cap" descr="Loopback capability - bitmask\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback - When set the port&apos;s egress traffic \;is looped back to the receiver and the port transmitter is dis\;abled.\;Bit 2: External_local_loopback - Enables the port&apos;s transmit\;ter to link with the port&apos;s receiver using an external loopback \;connector.\;Bit 3: Near_end_analog_loopback - [Internal]\;Bit 4: Near_end_digital_loopback - [Internal]\;Bit 7: LL_local_loopback - When set the port&apos;s egress Link \;layer traffic is looped back to the receiver. Physical port in \;this loopback mode is down.\;\;Note - Phy remote loopback can be supported only for lane \;rate higher than 25Gbuad in the 16nm devices.\;" access="RO" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,Near_end_analog_loopback=0x8,Near_end_digital_loopback=0x10,LL_local_loopback=0x80" offset="0x4.16" size="0x0.8" />
</node>

<node name="pprt_reg_ext" descr="" size="0x24.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPRT \;configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane \;based on lane index" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="Supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR main\;5 - USR tail\;Other values are reserved.\;" access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)\;Logical lane number\;[internal] Mapping to physical lane number can be queried \;in PMDR register" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols support\;if this bit is cleared - bit 25 (&apos;s&apos;) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols\;0 - No Swap.\;1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="p_c" descr="PRBS RX polarity support indication\;if this bit is cleared - bit 28 (&apos;p&apos;) is ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS RX polarity - NOT gate in PRBS (not Physical lane \;Polarity)\;0 - No polarity inversion.\;1 - PRBS RX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="tun_ovr" descr="[Internal]: If set to &apos;1&apos;, the value in tuning_type field will \;override the default adaptation flow (BER Bath for IB and \;XOR for Eth), which is set automatically when tun_ovr is &apos;0&apos;." access="OP" offset="0x0.29" size="0x0.1" />
	<field name="s" descr="start tuning:\;1 - start RX_tuning based on PRBS pattern \;Note: assuming peer transmitting PRBS. \;cannot be set when prbs_rx_tuning_status = 1 (during tun\;ing)" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS RX is disabled.\;1 - PRBS RX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave : Non error based tune\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; \;13):\;0 - NRZ test pattern\;1 - PAM4 encoding [interlnal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave : Non error based tune \;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - XAUI/2.5GE (3.125 Gb/s)\;Bit 3- DDR (5 Gb/s) \;Bit 4- QDR (10 Gb/s) \;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) \;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / \;106.25Gb/s)" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_oper" descr="Lane rate to be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s)\;1 - DDR (5 Gb/s) \;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s)\;4 - FDR (14.0625 Gb/s) \;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/\;s) \;8 - 9 - reserved\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s) \;\;Note: All lanes must be set to the same rate" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="prbs_lock_status_ext" descr="PRBS lock on PRBS pattern status for lanes 7-4: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_sta\;tus will return to 0 (Not locked)" access="RO" offset="0x14.20" size="0x0.4" />
	<field name="prbs_lock_status" descr="PRBS lock on PRBS pattern status for lanes 3-0: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_sta\;tus will return to 0 (Not locked)" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="prbs_rx_tuning_status" descr="Tuning status: \;0 - PRBS mode tuning was not performed.\;1 - Performing PRBS mode tuning.\;2 - PRBS mode tuning completed.\;3 - Signal Detect in progress\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_sta\;tus will return to 0." access="RO" offset="0x14.28" size="0x0.4" />
</node>

<node name="pptb_reg_ext" descr="" size="0xc.0" >
	<field name="pm" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="um" descr="untagged_buff mask - enables update of the untagged_buff \;field.\;Reserved for Spectrum family.\;Reserved for HCA devices." access="WO" offset="0x0.8" size="0x0.1" />
	<field name="cm" descr="ctrl_buff mask - enables update of the ctrl_buff field.\;NOTE: This field is ignored by the device, and control traffic \;is mapped to a pre-defined buffer (buffer - 9).\;In some old implementations (on SwitchX and SwitchX-2) \;software is required to use the value 9 in this field, later \;devices ignore this field.\;Reserved for HCA devices" access="WO" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mm" descr="Mapping mode\;0: Mapping both Unicast and Multicast packets to the same \;buffer\;In get operation, 0 means Unicast only.\;1: Mapping Unicast only\;2: Mapping Multicast only\;This field is reserved for HCA devices\;SwitchX/-2 support &apos;0&apos; only" access="INDEX" offset="0x0.28" size="0x0.2" />
	<field name="prio0buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="prio1buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="prio2buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="prio3buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.12" size="0x0.4" />
	<field name="prio4buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="prio5buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="prio6buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.24" size="0x0.4" />
	<field name="prio7buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated \;receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.28" size="0x0.4" />
	<field name="untagged_buff" descr="Mapping of untagged frames to one of the allocated receive \;port buffers.\;NOTE: In SwitchX/-2, this field must be mapped to a buffer \;8.\;\;Reserved for Spectrum. Spectrum maps untagged packets \;based on the Switch Priority.\;Reserved for HCA devices" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="ctrl_buff" descr="Mapping of control frames to one of the allocated receive \;port buffers.\;NOTE: This field is ignored by the device, and control traffic \;is mapped to a pre-defined buffer (buffer - 9).\;In some old implementations (on SwitchX and SwitchX-2), \;software is required to use the value 9 in this field, later \;devices ignore this field.\;Reserved for HCA devices" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="pm_msb" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i+8.\;Reserved for HCA device" access="WO" offset="0x8.24" size="0x0.8" />
</node>

<node name="pptt_reg_ext" descr="" size="0x1c.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPTT \;configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane \;based on lane index" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support/capability: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR Main [internal] \;5 - USR Tail [internal] \;Other values are reserved.\;Note: PRBS can be enabled only for two entities that \;directly connected to each other.\;For non MCM and no Retimer/Gearbox only 0 allowed.\;For non MCM and with Retimer/Gearbox 2-1 or 3 or 0.\;For MCM without Retimer/Gearbox 4-5 or 2 or 0.\;For MCM with Retimer/Gearbox 4-5 or 2-1 or 3 or 0.\;all the port will be in test mode when PRBS is enabled." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)\;Logical lane number\;[internal] Mapping to physical lane number can be queried \;in PMDR register" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols support\;if this bit is cleared - bit 25 (&apos;s&apos;) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols\;0 - No Swap.\;1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="p_c" descr="PRBS TX polarity support indication.\;if this bit is cleared - bit 28 (&apos;p&apos;) is been ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS TX polarity - NOT gate in PRBS (not Physical lane \;Polarity)\;0 - No polarity inversion.\;1 - PRBS TX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS TX is disabled.\;1 - PRBS TX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave8 (8 ones , 8 zeros)\;Bit 14 - Square_wave4 (4 ones , 4zeros)\;Bit 15 - Square_wave2 (2 ones , 2zeros)\;Bit 16 - Square_wave1 (one , zero)\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; \;13):\;0 - NRZ test pattern\;1 - PAM4 encoding [interlnal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave8 (8 ones , 8 zeros)\;0xE - Square_wave4 (4 ones , 4zeros)\;0xF - Square_wave2 (2 ones , 2zeros)\;0x10 - Square_wave1 (one , zero)\;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - XAUI/2.5GE (3.125 Gb/s)\;Bit 3- DDR (5 Gb/s) \;Bit 4- QDR (10 Gb/s) \;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) \;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / \;106.25Gb/s)\;" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s)\;1 - DDR (5 Gb/s) \;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/40GE (10.3125 Gb/s)\;4 - FDR (14.0625 Gb/s) \;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / \;106.25Gb/s)\;8- 9 - reserved\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s)\;\;Note: All lanes must be set to the same rate" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="prei_reg_28nm_ext" descr="" size="0x8.0" >
	<field name="mixer_offset1" descr="eye centering control.\;may cause link degradation when set." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="mixer_offset0" descr="eye centering control.\;may cause link degradation when set." access="RW" offset="0x0.16" size="0x0.16" />
</node>

<node name="prei_reg_ext" descr="" size="0x18.0" >
	<field name="status" descr="0 - No error injection\;1 - Work in progress\;2 - Done, desired BER reached\;3 - Error, desired BER can&apos;t be reached" access="RO" offset="0x0.0" size="0x0.2" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB / label port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="1 - 28nm products\;3 - 16nm products\;" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="ber_exp" descr="Desired Raw BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)\;Valid BER mantissa are 1,5" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ber_mantissa" descr="Desired Raw BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)\;Valid BER mantissa are 1,5" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="en" descr="1 - start the error injection process" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="lane_rate_cap" descr="Per lane rate capability for feature (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - XAUI/2.5GE (3.125 Gb/s)\;Bit 3- DDR (5 Gb/s) \;Bit 4- QDR (10 Gb/s) \;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) \;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s)" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="page_data" descr="Table  1227, &quot;PREI - Port Receive Error Injection Register Lay\;out for 28nm,&quot; on page  1516" subnode="prei_reg_28nm_ext" access="RW" offset="0x10.0" size="0x8.0" />
</node>

<node name="prm_register_payload_ext" descr="" size="0x104.0" >
	<field name="register_id" descr="Register ID" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="method" descr="0: Query\;1: Write" access="OP" offset="0x0.22" size="0x0.2" />
	<field name="status" descr="Return code of the Downstream Device to the register \;that was sent.\;0x0: OK - Operation was successfully executed\;0x1: BUSY \;0x4: NOT_SUPP_REG - The Switch register requested \;is not supported on that device\;0x7: BAD_PARAM - Incomplete or erroneous parameter \;set\;0x70: INTERNAL_ERR - Internal error" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="register_data" descr="Register data" access="RW" high_bound="63" low_bound="0" offset="0x4.0" size="0x100.0" />
</node>

<node name="pter_phy_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate\;0 - No Error\;---- Physical Errors ----\;1 - Raw BER\;2 - Effective BER\;" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities \;Bit 0 - Raw BER\;Bit 1 - Effective BER\;\;\;\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection opertional status\;0x0 - No error injection\;0x1 - Performing error injection" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="ber_exp" descr="BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ber_mantissa" descr="BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="error_injection_time" descr="Duration in 10 msec the port will generate errors.\;Reading this field will return the time left for errors to inject \;in msec\;\;\;0x0000 indicates no generation of errors.\;When set to 0xFFFF - No decremental operation, meaning \;the errors will be injected continuously without stop condi\;tion.\;" access="RW" offset="0x4.12" size="0x0.16" />
</node>

<node name="pter_port_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate\;0 - No Error\;---- Port Errors ----\;1 - Corrupt data packet ICRC\;2 - Corrupt data packet VCRC\;4- Corrupt credit packet LPCRC" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities \;Bit 0- Corrupt data packet ICRC\;Bit 1- Corrupt data packet VCRC\;Bit 2- Corrupt credit packet LPCRC\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="error_count" descr="Error Count\;Number of times the port will generate the configured error.\;0 indicates not to generate error.\;Reading error_count will return the number of left errors to \;inject. When 0, all requested errors has been injected." access="RW" offset="0x4.12" size="0x0.5" />
</node>

<node name="pter_reg_ext" descr="" size="0x20.0" >
	<field name="status" descr="Error injection status: \;0x0 -Good status\;0x2 - No available sources for Error injection\;0x3 - Error injection configuration when port is in non opera\;tional state (port is neither in UP or TEST MODE)\;0x4 - out of range BER setting" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB / label port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="error_page" descr="Error_page selection: \;0: Injection_of_Phy_Errors\;1: Injection_of_Port_Errors" access="INDEX" enum="Injection_of_Phy_Errors=0x0,Injection_of_Port_Errors=0x1" offset="0x0.24" size="0x0.4" />
	<field name="page_data" descr="error injection page data: \;Table  1221, &quot;PTER- Port Transmit Errors Register Phy Level \;Layout,&quot; on page  1512\;Table  1223, &quot;PTER- Port Transmit Errors Register Port Level \;Fields,&quot; on page  1513" subnode="pter_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x1c.0" union_selector="$(parent).error_page" />
</node>

<node name="pter_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="pter_phy_page_reg_ext" descr="" subnode="pter_phy_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Phy_Errors" size="0x1c.0" />
	<field name="pter_port_page_reg_ext" descr="" subnode="pter_port_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Port_Errors" size="0x1c.0" />
</node>

<node name="ptys_reg_ext" descr="" size="0x40.0" >
	<field name="proto_mask" descr="Protocol Mask. Indicates which of the protocol data is valid\;Bit 0: InfiniBand\;Bit 1: Reserved\;Bit 2: Ethernet" access="INDEX" enum="InfiniBand=0x1,Reserved=0x2,Ethernet=0x4" offset="0x0.0" size="0x0.3" />
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_Port\;1: Near-End_Port - (For Gearbox - Host side)\;2: Internal_IC_Port \;3: Far-End_Port - (For Gearbox - Line side)\;\;Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near=0x1,Internal_IC_Port=0x2,Far=0x3" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="force_tx_aba_param" descr="When AN is disabled, use aba TX set. \;" access="RW" offset="0x0.24" size="0x0.1" />
	<field name="an_disable_cap" descr="Auto Negotiation disable capability:\;0 - Device does not support AN disable\;1 - Device Supports  AN disable" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="an_disable_admin" descr="Auto Negotiation disable:\;0 - Normal operation \;1 - Disable AN.\;Note: In Ethernet port, when Disabling AN, the &quot;eth_pro\;to_admin&quot; bit mask must comply to single speed rate set.\;In IB port, when Disabling AN, the &quot;ib_proto_admin&quot; bit \;mask must comply to single speed rate set.\;It&apos;s recommended to validate the FEC override bits in PPLM \;when operating with AN. \;\;" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="reserved_high" descr="THIS BIT MUST BE TIED TO 1!\;This is old capability bit that address AN_DISABLE capability \;with only one enabled protocol." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="data_rate_oper" descr="Port data rate in resolution of 100 Mb/s (data_rate_oper * \;100 Mb/s)\;Value 0x0 indicates this field is not supported." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_port_rate" descr="Port maxium data rate in resolution of 1 Gb/s \;(data_rate_oper * 1 Gb/s)\;Value 0x0 indicates this field is not supported.\;" access="RO" offset="0x4.16" size="0x0.12" />
	<field name="an_status" descr="Auto Negotiation status: \;0: Status_is_unavailable\;1: AN_completed_successfully \;2: AN_performed_but_failed\;3: AN_was_not_performed_link_is_up \;4: AN_was_not_performed_link_is_down" access="RO" enum="Status_is_unavailable=0x0,AN_completed_successfully=0x1,AN_performed_but_failed=0x2,AN_was_not_performed_link_is_up=0x3,AN_was_not_performed_link_is_down=0x4" offset="0x4.28" size="0x0.4" />
	<field name="ext_eth_proto_capability" descr="For HCA: See also PCAM.feature_cap_mask bit 13 for \;Extended Ethernet protocol support.\;Extended Ethernet port speed/protocols supported (bit\;mask):\;Bit 0: SGMII_100M\;Bit 1: 1000BASE-X / SGMII\;Bit 3: 5GBASE-R\;Bit 4: XFI / XAUI-1 // 10G\;Bit 5: XLAUI-4/XLPPI-4 // 40G \;Bit 6: 25GAUI-1/ 25GBASE-CR / KR \;Bit 7: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 \;Bit 8: 50GAUI-1 /50GBASE-CR / KR\;Bit 9: CAUI-4 / 100GBASE-CR4 / KR4\;Bit 10: 100GAUI-2 / 100GBASE-CR2 / KR2 \;Bit 11: 100GAUI-1 / 100GBASE-CR / KR\;Bit 12: 200GAUI-4 / 200GBASE-CR4/KR4\;Bit 13: 200GAUI-2 / 200GBASE-CR2/KR2\;Bit 14: Reserved [internal] Placeholder for 200GAUI-1\;Bit 15: 400GAUI-8/ 400GBASE-CR8\;Bit 16: 400GAUI-4/ 400GBASE-CR4\;Bit 17: Reserved [internal] Placeholder for 400GAUI-2\;Bit 18: Reserved [internal] Placeholder for 400GAUI-1\;Bit 19: 800GAUI-8/ 800GBASE-CR8\;Bit 31: SGMII_10M\;Other - Reserved" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="eth_proto_capability" descr="Ethernet port speed/protocols supported (bitmask)\;Bit 31 - 50GBase-KR2\;Bit 30 - 50GBase-CR2\;Bit 29 - 25GBase-SR\;Bit 28 - 25GBase-KR\;Bit 27 - 25GBase-CR\;Bit 26 - 10GBase-T \;Bit 25 - 1000Base-T\;Bit 24 - 100Base-TX\;Bit 23 - 100GBase LR4/ER4\;Bit 22 - 100GBase KR4\;Bit 21 - 100GBase SR4\;Bit 20 - 100GBase CR4\;Bit 19 - 50GBase-KR4\;Bit 18 - 50GBase-SR2\;Bit 16 - 40GBase LR4/ER4\;Bit 15 - 40GBase SR4\;Bit 14 - 10GBase ER/LR\;Bit 13 - 10GBase SR\;Bit 12 - 10GBase CR\;Bit 10 - 10Base-T\;Bit 9 - SGMII_100Base\;[Internal] Bit 8 - 56GBase *R4\;Bit 7 - 40GBase KR4\;Bit 6 - 40GBase CR4\;[internal] Bit 5 - 20GBase-KR2\;Bit 4 - 10GBase KR\;Bit 3 - 10GBase KX4\;Bit 2 - 10GBase-CX4\;Bit 1 - 1000Base KX\;Bit 0 - SGMII" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ib_proto_capability" descr="InfiniBand port speed supported (bitmask)\;ib_link_speed &lt;= ib_proto_capability[7:0]\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80" offset="0x10.0" size="0x0.16" />
	<field name="ib_link_width_capability" descr="ib_link_width &lt;= ib_proto_capability\;Bit 0 - 1x\;Bit 1 - 2x\;Bit 2 - 4x\;Bit 3 - 8x\;Bit 4 - 12x" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="ext_eth_proto_admin" descr="Ethernet port extended speed/protocols bitmask\;NOTE: This field and &quot;eth_proto_admin&quot; are mutual exclu\;sive, meaning that only one of the field can be set on write \;command." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="eth_proto_admin" descr="Ethernet port speed/protocols bitmask" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="ib_proto_admin" descr="InfiniBand port speed bitmask" access="RW" offset="0x1C.0" size="0x0.16" />
	<field name="ib_link_width_admin" descr="InfiniBand port link width bitmask\;" access="RW" offset="0x1C.16" size="0x0.16" />
	<field name="ext_eth_proto_oper" descr="Ethernet port extended speed/protocols bitmask" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="eth_proto_oper" descr="Ethernet port speed/protocols bitmask" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ib_proto_oper" descr="InfiniBand port speed bitmask" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="ib_link_width_oper" descr="InfiniBand port link width bitmask\;" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="connector_type" descr="Connector type indication\;0: No_connector_or_unknown \;1: PORT_NONE - None\;2: PORT_TP - Twisted Pair\;3: PORT_AUI - AUI\;4: PORT_BNC - BNC\;5: PORT_MII - MII\;6: PORT_FIBRE - FIBRE\;7: PORT_DA - Direct Attach Copper\;8: PORT_OTHER - Other" access="RO" enum="No_connector_or_unknown=0x0,PORT_NONE=0x1,PORT_TP=0x2,PORT_AUI=0x3,PORT_BNC=0x4,PORT_MII=0x5,PORT_FIBRE=0x6,PORT_DA=0x7,PORT_OTHER=0x8" offset="0x2C.0" size="0x0.4" />
	<field name="force_kr_frames_admin" descr="Ethernet Force mode options when AN disable is set.\;0 - auto, keep normal operation\;1 - Do Force KR Startup LT flow\;2 - Do not do Force KR Startup LT flow\;\;Note: Ignored when an_disable_admin is not set\;Force KR Flow is possible for PAM4 links only" access="RW" offset="0x2C.28" size="0x0.2" />
	<field name="force_kr_frames_cap" descr="0 - device does not support Force KR Startup LT flow\;1 - device supports Force KR Startup LT flow\;\;Note: Ignored when an_disable_admin is not set\;Force KR Flow is possible for PAM4 links only" access="RO" offset="0x2C.30" size="0x0.1" />
	<field name="eth_proto_lp_valid" descr="If set indicates that eth_proto_lp_advertise has valid adver\;tisement" access="RO" offset="0x2C.31" size="0x0.1" />
	<field name="eth_proto_lp_advertise" descr="Ethernet port&apos;s link partner advertised protocols according \;to PTYS.ext_eth_proto_capability mask. \;Returns the protocols that were advertised by the link part\;ner during auto-negotiation.\;Valid only if eth_proto_lp_valid is set" access="RO" offset="0x30.0" size="0x4.0" />
</node>

<node name="pvlc_reg_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="vl_hw_cap" descr="Virtual Lanes supported on this port.\;0 - Reserved\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="vl_admin" descr="Virtual Lanes enabled by the local admin on this port.\;0: No change; valid only on Set()\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="vl_operational" descr="Operational VLs as configured by the SM on this port:\;0: No change; valid only on Set()\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14\;Changing vl_operational in certain PortStates may cause in \;flow control update errors which may initiate Link/PHY \;retraining.\;vl_operational value is valid only when link state is UP." access="RO" offset="0xC.0" size="0x0.4" />
</node>

<node name="pvls_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="vl_suspend" descr="VL suspend, bitmap per VL\;Per bit:\;0: VL enabled (default)\;1: VL disabled" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="qcam_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First 128 REG_ID" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index\;0: Enhanced features" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="qos_access_reg_cap_mask" descr="Supported QoS access register bitmasks. Based on \;access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: QCAP (0x4001)\;Bit 2: QPTS (0x4002)\;Bit 3: QDPM (0x4003)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="qos_feature_cap_mask" descr="Supported QoS enhanced features based on feature_group \;index.\;When bit is set, the feature is supported in the device\;Bit 0: QPTS_TRUST_BOTH - trust_both is supported in QPTS \;register" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="qetcr_ext" descr="" size="0x50.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cap_remote_admin" descr="Indicates if operation_type==remote_admin_parameters \;is supported\;NIC only, Reserved for Switches" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation_type==local_admin_parameters is \;supported\;NIC only, Reserved for Switches" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="operation_type" descr="Operation type.\;0x0: local operative parameters.\;0x1: local admin parameters. Supported only when \;cap_local_admin==1.\;0x2: remote admin parameters. Supported only when \;cap_remote_admin==1. \;NIC only, Reserved for Switches" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="tc_configuration" descr="Per-tclass configuration. For details, refer to Table 941, \;&quot;ETS tcN Configuration Register Layout&quot;." subnode="ets_ext" access="RW" high_bound="7" low_bound="0" offset="0x8.0" size="0x40.0" />
	<field name="global_configuration" descr="Global configuration. For details, refer to Table 943, &quot;ETS \;Global Configuration Register Layout&quot;.\;Reserved for NICs" subnode="ets_global_ext" access="RW" offset="0x48.0" size="0x8.0" />
</node>

<node name="qhll_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="hll_time" descr="HLL Time\;HLL Time = 4.096uSec * 2^hll_time\;Default is 17 (0.54Sec)\;Range is 0 ..19\;Values of 20-31 means infinite (no HLL)" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="stall_cnt" descr="Stall count. Number of HLL discarded packets required to \;enter the Stall-State.\;Default is 7\;Range 1..7\;Reserved when stall_en = 0" access="RW" offset="0x8.0" size="0x0.3" />
	<field name="stall_en" descr="Stall enable\;0: Stall disabled\;1: Stall enabled (default)" access="RW" offset="0x8.31" size="0x0.1" />
</node>

<node name="qpdp_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port.\;Supported for data packets from CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="switch_prio" descr="Default port Switch Priority (default 0)\;For NIC devices only 8 priorities are supported" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="color" descr="Default port color (default=0)\;0x0: GREEN\;0x1: YELLOW\;0x2: RED\;For Switch only, Reserved for NICs" access="RW" enum="GREEN=0x0,YELLOW=0x1,RED=0x2" offset="0x4.8" size="0x0.2" />
</node>

<node name="qprt_ext" descr="" size="0x8.0" >
	<field name="pcp" descr="Packet&apos;s PCP value" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="dei" descr="Packet&apos;s DEI value.\;when" access="INDEX" offset="0x0.11" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rprio" descr="For SwitchX/-2: Regeneration Priority.\;For Spectrum family: Switch Priority\;The default value for the table is: PCP i -&gt;Regeneration Pri\;ority i\; For NIC devices only 8 priorities are supported" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="color" descr="Packet Color.\;0: GREEN\;1: YELLOW\;2: RED\;For Switch only, Reserved for NICs" access="RW" enum="GREEN=0x0,YELLOW=0x1,RED=0x2" offset="0x4.8" size="0x0.2" />
</node>

<node name="qpts_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local Port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="trust_state" descr="0: TRUST_PORT - reserved for NIC devices\;1: TRUST_PCP - default\;2: TRUST_DSCP\;3: TRUST_BOTH - For NIC devices suported only when \;QCAM.QPTS_TRUST_BOTH == 1" access="RW" enum="TRUST_PCP=0x1,TRUST_DSCP=0x2,TRUST_BOTH=0x3" offset="0x4.0" size="0x0.3" />
</node>

<node name="qshr_ext" descr="" size="0x50.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fr" descr="Fast Response - the device will shape the rate to its mini\;mum value upon receive of WQE LWM (Low WaterMark) \;event \;0: disable\;1: enable" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="ch" descr="Connected host:\;0: The configuration will be applied on the host calling \;QSHR. \;1: The configuration will be applied on the host connected \;to the function calling the QSHR." access="INDEX" offset="0x0.27" size="0x0.1" />
	<field name="global_configuration" descr="Global configuration. For details, refer to Table 943, &quot;ETS \;Global Configuration Register Layout&quot;." subnode="ets_global_ext" access="RW" offset="0x48.0" size="0x8.0" />
</node>

<node name="qspcp_ext" descr="" size="0xc.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to Counting Priority.\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port\;No support for CPU port\;No support for router port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rx_counting_prio" descr="The Rx Counting Priority value for the relevant Switch Priority \;value.\;default: \;for i=[0..7]: switch_prio i: rx_counting_prio i\;for i=[8..15]: switch_prio i: rx_counting_prio (i-8)" access="RW" offset="0x4.0" size="0x0.3" />
	<field name="tx_counting_prio" descr="The Tx Counting Priority value for the relevant Switch Priority \;value.\;default: \;for i=[0..7]: switch_prio i: tx_counting_prio i\;for i=[8..15]: switch_prio i: tx_counting_prio (i-8)\;[Spectrum2] This field is reserved when QGCR.tx_cnt_tclass \;is set" access="RW" offset="0x8.0" size="0x0.3" />
</node>

<node name="qspip_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to IEEE Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="ieee_prio" descr="The new IEEE Priority value for the relevant Switch Priority \;value.\;default: \;for i=[0..7]: switch_prio i: ieee_prio i\;for i=[8..15]: switch_prio i: ieee_prio (i-8)\;Note: Different switch_prio values assigned to a given buffer \;(see PPTB) may be assigned to different ieee_prio values." access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="qtct_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number (transmit port)\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cap_remote_admin" descr="Indicates if operation_type==remote_admin_parameters is \;supported.\;when" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation_type==local_admin_parameters is \;supported\;when" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="operation_type" descr="Operation type.\;0x0: local_operative_parameters\;0x1: local_admin_parameters - Supported only when \;cap_local_admin==1\;0x2: remote_admin_parameters- Supported only when \;cap_remote_admin==1\;when" access="INDEX" enum="local_operative_parameters=0x0,local_admin_parameters=0x1,remote_admin_parameters=0x2" offset="0x0.30" size="0x0.2" />
	<field name="tclass" descr="Traffic Class\;Default values are: \;- switch_prio=0: tclass=1 \;- switch_prio=1: tclass=0\;- switch_prio&gt;1: tclass = switch_prio\;\;When MC aware mode is enabled, setting values greater or \;equal to (cap_max_tclass_data)/2) is not allowed" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="register_host_endianness_ext" descr="" size="0x10.0" >
	<field name="he" descr="0: LITTLE_ENDIAN\;1: BIG_ENDIAN" access="RW" enum="LITTLE_ENDIAN=0x0,BIG_ENDIAN=0x1" offset="0x0.31" size="0x0.1" />
</node>

<node name="register_loopback_control_ext" descr="" size="0x10.0" >
	<field name="port" descr="1 - port 1\;2 - port 2\;255 - both ports\;otherwise - reserved" offset="0x0.16" size="0x0.8" />
	<field name="no_lb" descr="When set, the HCA will always send packets meant for the \;same port to wire, rather than perform internal loopback" offset="0x0.31" size="0x0.1" />
</node>

<node name="register_misc_counters_ext" descr="" size="0x20.0" >
	<field name="counter_select" descr="When performing a WRITE operation - , the counter select bit\;mask determines which registers are set:\;Bit 0 - ECC\;Bit 1 - LDB silent drop" offset="0x4.0" size="0x4.0" />
	<field name="ecc" descr="Counts number of arrays which encountered a bit error" offset="0xC.0" size="0x4.0" />
	<field name="ldb_silent_drop" descr="Counts number of packets silently dropped due to LDB error" offset="0x10.0" size="0x4.0" />
</node>

<node name="register_power_settings_ext" descr="" size="0x10.0" >
	<field name="power_settings_level" descr="0x0 - minimum power (maximum latency penalty)\;0x1-0xfe - reserved\;0xff - maximum power (minimum latency penalty)" access="RW" offset="0x0.0" size="0x0.8" />
</node>

<node name="register_unti_perf_global_ctrl_ext" descr="" size="0x10.0" >
	<field name="cmd" descr="0x0 - stop counting in all performance counters\;0x1 - start counting in all performance counters \;Otherwise - reserved" access="WO" offset="0x0.0" size="0x0.8" />
</node>

<node name="roce_accl_reg_ext" descr="" size="0x40.0" >
	<field name="roce_adp_retrans_field_select" descr="In Query, indicates if roce_tx_windo mode is sup\;ported.\;If set, indicates roce_tx_window_en field is valid." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="roce_tx_window_field_select" descr="In Query, indicates whether roce_tx_window mode \;is supported.\;If set, indicates roce_tx_window_enfield is valid." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="roce_slow_restart_field_select" descr="In Query, indicates whether roce_slow_restart \;mode is supported.\;If set, indicates roce_slow_restart_en field is \;valid." access="RW" offset="0x0.2" size="0x0.1" />
	<field name="roce_slow_restart_idle_field_select" descr="In Query, indicates whether roce_slow_restart_idle \;mode is supported. If set, indicates roce_slow_re\;start_idle_en field is valid" access="RW" offset="0x0.3" size="0x0.1" />
	<field name="roce_adp_retrans_en" descr="If set, the adaptive retransmission window function\;ality is enabled.\;Valid only when roce_adp_retrans_field_select \;== 1." access="RW" offset="0x4.0" size="0x0.1" />
	<field name="roce_tx_window_en" descr="If set, the Transmission window functionality is \;enabled. \;Valid only when roce_tx_window_field_select == \;1." access="RW" offset="0x4.1" size="0x0.1" />
	<field name="roce_slow_restart_en" descr="If set, the Slow restart functionality is enabled.\;When used, slow restart is initiated when conges\;tion is identified on the network.\;Valid only when roce_slow_restart_field_select \;== 1." access="RW" offset="0x4.2" size="0x0.1" />
	<field name="roce_slow_restart_idle_en" descr="If set, the Slow restart after idle functionality is \;enabled. When used, slow restart is initiated when \;qp was idling. Valid only when roce_slow_re\;start_idle_field_select ==1" access="RW" offset="0x4.3" size="0x0.1" />
</node>

<node name="rom_version_ext" descr="" size="0x4.0" >
	<field name="build" descr="Build version" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="minor" descr="Minor version" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="major" descr="Major version" access="RO" offset="0x0.24" size="0x0.8" />
</node>

<node name="sbcam_ext" descr="" size="0x4c.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First 128 REG_ID" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index\;0: Enhanced features" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sb_access_reg_cap_mask" descr="Supported Shared Buffer access register bitmasks. Based \;on access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: SBPR_(0xB001)\;Bit 2: SBCM_(0xB002)\;Bit 3: SBPM_(0xB003)\;Bit 5: SBSR_(0xB005)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="sb_feature_cap_mask" descr="Supported Shared Buffer enhanced features based on fea\;ture_group index.\;When bit is set, the feature is supported in the device\;Bit 0: descriptors_cap - (desc) is supported \;Bit 1: ext_buff_occupancy_cap - is supported \;Bit 2: exclude_cap - bit is supported\;Bit 3: sb_own_res - user can configure ePort per tc shared \;buffer configuration    \;Bit 4: sb_global_res - user can configure ePort, iPort and \;iPort per pg shared buffer configuration  " access="RO" enum="descriptors_cap=0x1,ext_buff_occupancy_cap=0x2,exclude_cap=0x4,sb_own_res=0x8,sb_global_res=0x10" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
	<field name="cap_total_descriptors" descr="Total amount of descriptors in the device - 16 bits" access="RO" offset="0x3C.16" size="0x0.16" />
	<field name="cap_total_buffer_size" descr="Total buffer size in the device. \;Units of Bytes." access="RO" offset="0x40.0" size="0x4.0" />
	<field name="cap_num_pool_supported" descr="Number of shared buffer pools supported" access="RO" offset="0x44.0" size="0x0.8" />
	<field name="cap_max_pg_buffers" descr="Maximum number of port group buffers" access="RO" offset="0x44.8" size="0x0.8" />
	<field name="cap_cell_size" descr="Buffer cell size (Bytes)" access="RO" offset="0x44.16" size="0x0.16" />
	<field name="cap_max_cpu_ingress_tclass_sb" descr="Maximum number of tclasses for bmc port" access="RO" offset="0x48.0" size="0x0.8" />
	<field name="cap_max_tclass_sb" descr="Maximum number of tclasses" access="RO" offset="0x48.8" size="0x0.8" />
	<field name="cap_sbsr_stat_size" descr="SBSR register number of responses\;" access="RO" offset="0x48.16" size="0x0.8" />
</node>

<node name="sbcm_ext" descr="" size="0x28.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class \;(dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class: range is 0..cap_max_tclass_sb - 1\;\;For  traffic class to CPU port: range is 0..cap_max\;_cpu_ingress_tclass_sb - 1\;For traffic class to BMC port: range is 0..cap_max_b\;mc_tc_sb - 1\;\;\;" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;2: Host_port_number" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="exc" descr="Exclude - no accounting in the pool\;0: the tclass is accounted in the pool (default)\;1: the tclass is not accounted in the pool \;\;For NIC: Supported when descriptors_cap is set\;" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy\;This includes cells at the pool and at the min_buff" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. \;This includes cells at the pool and at the min_buff\;Cleared by writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is \;cleared (and a new max value is tracked from the time \;the clear was performed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size for the limiter\;The minimum buffer is not part of the pool area.\;Units of cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="The maximum buffer threshold in the pool area.\;When the pool that is associated to the port-pg/tclass is \;configured to static, then max_buff is configured in cells\;When the pool that is associated to the port-pg/tclass is \;configured to dynamic, then max_buff holds the &quot;alpha&quot; \;parameter, supporting the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1\;\;" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool\;Range 0 .. cap_num_pool_supported - 1\;" access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbctc_ext" descr="" size="0x14.0" >
	<field name="mode" descr="Mode of threshold:\;0: Fixed\;1: Percentage\;Reserved when Spectrum-1 and Quantum\;" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="res" descr="When SBGCR.tele_entity = BOTH then resolution index:\;0: TCLASS\;1: PORT\;Reserved (has no meaning) when SBGCR.tele_entity != 2 \;(BOTH)\;" access="INDEX" offset="0x0.4" size="0x0.1" />
	<field name="local_port" descr="Local port number for egress sport\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dir_ing" descr="Direction\;0: Egress Tclass\;1: Ingress PG\;Reserved when Spectrum-1" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="event" descr="Event generation on crossing thr max for this port:\;0: NO_EVENT - Do not generate event\;1: EVENTS - Generate events for crossing up and down\;Not configured when en_config = 0" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="en_config" descr="Enable configuration of all fields except event field" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="tclass_en_high" descr="TClass/PG Trap enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits when SBGCR.tele_entity = PORT: bit0 (all \;tclasses), else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tclass_en_low" descr="TClass/PG Trap enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits when SBGCR.tele_entity = PORT: bit0 (all \;tclasses), else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="thr_max" descr="Threshold max\;When an egress port TClass crosses the threshold (cross \;up or down) then the HW will emit an event of SB_CON\;G_TX_PORT and the status can be read by SBCTR\;For Quantum and Spectrum-2: When an egress port \;TClass/PG crosses the threshold then congestion mirror is \;enabled\;\;When congestion mode is Fixed:\;- Cells. Valid inputs are 1..cap_total_buffer_size/cap_\;cell_size\;When congestion mode is Percentage:\;- Percentage of the quota of local_port,traffic_class. Range \;is 0,..100, units of integer percentage.\;\;Written only if en_config = 1\;\;" access="RW" offset="0x10.0" size="0x0.24" />
</node>

<node name="sbctr_ext" descr="" size="0x10.0" >
	<field name="entity" descr="Entity type:\;0: TCLASS\;1: PORT\;This field represents the value configured by \;SBGCR.tele_entity" access="RO" offset="0x0.0" size="0x0.2" />
	<field name="fp" descr="False Positive\;When a trap: this is a false positive trap\;Reserved when Switch-IB/2, Quantum and Spectrum-2" access="RO" offset="0x0.4" size="0x0.1" />
	<field name="dir_ing" descr="Direction\;0: Egress Tclass\;1: Ingress PG\;Reserved when Spectrum-1" access="INDEX" offset="0x0.8" size="0x0.2" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ievent" descr="Invoke event \;0: Read only\;1: Does both reading and invoke an event of type SB_CON\;G_TX_PORT" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="tclass_vector_high" descr="Tclass vector\;Each bit represents corresponding tclass\;0: Tclass is below the congestion threshold\;1: Tclass is above the congestion threshold\;Note that a TClass which is disabled from threshold will \;always be below the congested threshold. See SBCTC\;Valid bits when entity = PORT: bit0 (all tclasses), else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="tclass_vector_low" descr="Tclass vector\;Each bit represents corresponding tclass\;0: Tclass is below the congestion threshold\;1: Tclass is above the congestion threshold\;Note that a TClass which is disabled from threshold will \;always be below the congested threshold. See SBCTC\;Valid bits when entity = PORT: bit0 (all tclasses), else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="sbcts_ext" descr="" size="0x14.0" >
	<field name="clear" descr="Clear counter\;0: Do not clear\;1: Clear the counter" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="trap_overflow_counter" descr="Trap Overflow Counter\;Counts how many congestion traps (SB_CONG_TX_PORT) \;were not invoked by the device due to trap overflow\;Counter is sticky when reaching 2^24-1" access="RO" offset="0x10.0" size="0x0.24" />
</node>

<node name="sbdcc_ext" descr="" size="0x210.0" >
	<field name="clr" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="no_buffer_discard_cpu_tclass" descr="Count the number of unicast packets to CPU dropped due \;to lack of shared buffer resources\;For tclass i\;Range is 0.. cap_max_cpu_ingress_tclass-1\;See Table 1599, &quot;SBDCC - counter Layout,&quot; on page 1918" subnode="uint64" access="RO" high_bound="63" low_bound="0" offset="0x10.0" size="0x200.0" />
</node>

<node name="sbdcm_ext" descr="" size="0x14.0" >
	<field name="counter_index" descr="Counter Index for flow counters, counting no buffer dis\;card per switch priority.\;" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;default: type=0 (disabled)\;Not supported by SwitchX/-2 and Spectrum-1" access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="sbdcr_ext" descr="" size="0x14.0" >
	<field name="counter_index" descr="Counter Index for flow counters, counting no buffer dis\;card per switch priority.\;Reserves a counter range of num_ports*num_PGs:\;PG 0..7 - PGs\;PG 8 - Control PG\;PG 9 - Mirror PG\;PG 10 - egress-traps, reserved when Spectrum-2 \;\;" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters." access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="sbgcr_ext" descr="" size="0x4.0" >
	<field name="tele_entity" descr="Telemetry entity type:\;0: TCLASS\;1: PORT\;2: BOTH - support both TCLASS and PORT. Indexed by \;SBCTC.res \;Note: change of this field is allowed only when conges\;tion threshold is disabled on all ports and tclasses, see \;SBCTC\;Reserved when Spectrum/-2" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="cong_fp" descr="Congestion false positive\;For Tclass Congestion:\;0: False Negative - allow trap and rules only for con\;gested Tclass. Response may be delayed by a few uSec\;1: False Positive - allow fp-trap and rules for all Tclasses, \;converging over time to only congested Tclasses. Pro\;vided immediate response \;Reserved when SwitchX/-2, Switch-IB/2, Quantum and \;Spectrum-2" access="RW" offset="0x0.4" size="0x0.1" />
</node>

<node name="sbhbr_ext" descr="" size="0x1c.0" >
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="opcode" descr="Opcode:\;0: Bind a hist_id\;1: Unbind a hist_id (default)" access="RW" offset="0x0.28" size="0x0.4" />
	<field name="hist_id" descr="Histogram id to bind\;from 0 to cap_max_queue_hist_id - 1" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="hist_type" descr="0x1000: Queue_Depth_Traffic_Class\;See Table 1607, &quot;SBHBR - Histograms Hist-type for queue \;histograms,&quot; on page 1923" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="hist_parameters" descr="According to hist_type\;See Table 1607, &quot;SBHBR - Histograms Hist-type for queue \;histograms,&quot; on page 1923" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="hist_min_value" descr="Min value for histogram main range\;Units according to the units of the hist_type" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="hist_max_value" descr="Max value for histogram main range\;Note: for Spectrum device, hist_group=1 this rule must be \;meet:\;hist_max_value = hist_min_value + 2^n, n &gt;= 3\;Units according to the units of the hist_type" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="sample_time" descr="Sample time interval. \;Allowed range:\;time = 2^sample_time * 128nSec\;sample_time range is 0..cap_max_sample_time-1\;Note: for Spectrum the sample_time is global for all ports \;and all tclass \;For Spectrum-2 the sample_time is per port.tclass." access="RW" offset="0x18.0" size="0x0.6" />
</node>

<node name="sbhbr_v2_ext" descr="" size="0x1c.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota\;Reserved when hist_type = Queue_Latency and this field is \;treated as &apos;1&apos; Egress port quota\;" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class, hist_type of Queue_Depth_Traffic_Class: \;range is 0..cap_max_tclass - 1\;For traffic class, hist_type of Queue_Latency: range is \;0..cap_max_tclass_data - 1\;For traffic class to CPU port: range is 0..cap_max_cpu_in\;gress_tclass- 1\;For Spectrum: no admission on Tx.Tclass, so when traffic \;class is in MC aware mode then the traffic classes which \;are MC aware must not be configured, but can be read. \;Spectrum-2 has admission on Tx.Tclass so all traffic \;classes can be configured also for MC aware mode. \;" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="local_port" descr="Local port number.\;For Ingress: excludes CPU port and Router port\;For Egress: excludes IP Router\;For Egress hist_type of Queue_Latency: exludes also CPU \;port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="en" descr="When hist_type = Queue_Depth_Traffic_Class:\;Enable the histogram\;When hist_type = Queue_Latency:\;This is a WO for clearing the histograms and the counters" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="hist_type" descr="0x1000: Queue_Depth_Traffic_Class\;0x1002: Queue_Latency\;See Table 1607, &quot;SBHBR - Histograms Hist-type for queue \;histograms,&quot; on page 1923" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="mode" descr="mode\;0: Linear histogram\;1: Exponential histogram" access="RW" offset="0x8.28" size="0x0.3" />
	<field name="hist_min_value" descr="Min value for histogram main range\;Units according to the units of the hist_type" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="hist_max_value" descr="Max value for histogram main range\;When mode=0 (linear), then this rule must be meet:\;hist_max_value = hist_min_value + 2^n, n &gt;= 3\;When mode=1 (exponential), then this rule must be meet:\;hist_max_value = hist_min_value + 255*2^n, n &gt;= 0\;Units according to the units of the hist_type" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="sample_time" descr="Sample time interval. \;Allowed range:\;time = 2^sample_time * 128nSec\;sample_time range is 0..cap_max_sample_time-1\;For Spectrum-1 the sample_time is global for all ports and \;all tclass \;For Spectrum-2 the sample_time is per port.tclass. \;Reserved when hist_type = Queue_Latency" access="RW" offset="0x18.0" size="0x0.6" />
</node>

<node name="sbhpc_ext" descr="" size="0x24.0" >
	<field name="max_buff" descr="Maximum SHP (Shared Headroom Pool) size. \;Default:0\;When max_buff&gt;0 then ports which have PBMC.shp_max\;_loan&gt;0 may use the SHP" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="buff_occupancy" descr="Current SHP occupancy\;" access="RO" offset="0x20.0" size="0x0.24" />
</node>

<node name="sbhrr_ext" descr="" size="0x60.0" >
	<field name="clr" descr="Clear:\;0: Read the data in the histogram agent\;1: Read and clear the data in the histogram agent" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="hist_id" descr="see SBHBR" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="bin" descr="Value of bin \;Units according to the units of the hist_type which is used \;for the hist_id\;Max bins is according to cap_hist_num_bins\;Bin is saturated at (2^cap_hist_bin_size_type1-1). When \;any bin is saturated all bins stop incrementing.\;See Table 1612, &quot;SBHRR - Bin Layout,&quot; on page 1925" subnode="uint64" access="RO" high_bound="9" low_bound="0" offset="0x10.0" size="0x50.0" />
</node>

<node name="sbhrr_v2_ext" descr="" size="0x90.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota\;Reserved when hist_type = Queue_Latency and this field is \;treated as &apos;1&apos; Egress port quota" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class: range is 0..cap_max_tclass - 1\;For traffic class to CPU port: range is 0..cap_max_cpu_in\;gress_tclass- 1\;" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="local_port" descr="Local port number.\;For Ingress: excludes CPU port\;For Egress: includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clr" descr="Clear:\;0: Read the data in the histogram agent\;1: Read and clear the data in the histogram agent" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="hist_type" descr="0x1000: Queue_Depth_Traffic_Class\;0x1002: Queue_Latency\;See Table 1607, &quot;SBHBR - Histograms Hist-type for queue \;histograms,&quot; on page 1923" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="min_sampled_high" descr="min_sampled\;Cleared when clr = 1, cleared to 0xffff_ffff_ffff_ffff\;Units according to the units of the hist_type which is used \;for the hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="min_sampled_low" descr="min_sampled\;Cleared when clr = 1, cleared to 0xffff_ffff_ffff_ffff\;Units according to the units of the hist_type which is used \;for the hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="max_sampled_high" descr="max_sampled\;Cleared when clr = 1, cleared to 0\;Units according to the units of the hist_type which is used \;for the hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="max_sampled_low" descr="max_sampled\;Cleared when clr = 1, cleared to 0\;Units according to the units of the hist_type which is used \;for the hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="bin" descr="Value of bin \;Units according to the units of the hist_type which is used \;for the hist_id\;Max bins is according to cap_hist_num_bins.\;Bin is saturated at (2^cap_hist_bin_size_type1-1). When \;any bin is saturated all bins stop incrementing.\;See Table 1618, &quot;SBHRR_V2 - Bin Layout,&quot; on page 1931" subnode="uint64" access="RO" high_bound="9" low_bound="0" offset="0x40.0" size="0x50.0" />
</node>

<node name="sbib_ext" descr="" size="0x10.0" >
	<field name="int_buffer_index" descr="Internal Buffer Index \;Spectrum supports only 1 index per port with value of 0" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port\;Not supported for Router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="status" descr="Status:\;0: the internal buffer status is not yet at the size of buff_\;size\;1: the internal buffer status is equal to buff_size" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="buff_size" descr="Buffer size\;Units represented in cells\;Allowed range is 0 to (cap_max_headroom_size - 1)\;Default is 0" access="RW" offset="0x8.0" size="0x0.24" />
</node>

<node name="sbme_ext" descr="" size="0x28.0" >
	<field name="local_port" descr="Local port number for egress ports\;Includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool\;" access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbmm_ext" descr="" size="0x28.0" >
	<field name="prio" descr="Switch Priority" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;Reserved when Spectrum-1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared \;by writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is \;cleared (and a new max value is tracked from the time \;the clear was performed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size for the limiter, in cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="When the pool associated to the port-pg/tclass is config\;ured to static, Maximum buffer size for the limiter config\;ured in cells.\;When the pool associated to the port-pg/tclass is config\;ured to dynamic, the max_buff holds the &quot;alpha&quot; param\;eter, supporting the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool" access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbpm_ext" descr="" size="0x20.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pool" descr="The pool associated to quota counting on the local_port\;Range 0 .. cap_num_pool_supported - 1\;" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;2: Host_port_number" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;For Ingress: excludes CPU port\;For Egress: includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy of the port.pool \;This includes cells at the pool and at the min_buff" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. \;This includes cells at the pool and at the min_buff\;Cleared by writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, max_buff_occupancy field is cleared \;(and a new max value is tracked from the time the clear \;was performed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size\;The minimum buffer is not part of the pool area.\;Units of cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="The maximum buffer threshold in the pool area.\;When the pool is configured to static, then max_buf is \;configured in cells.\;When the pool is configured to dynamic, then max_buff \;holds the &quot;alpha&quot; parameter, supporting the following \;values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1\;\;" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
</node>

<node name="sbpr_ext" descr="" size="0x18.0" >
	<field name="pool" descr="Pool index\;Range 0 .. cap_num_pool_supported - 1\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="dir" descr="Direction\;0: Ingress pools\;1: Egress pools" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For Spectrum-1: Total 84960 descriptors\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="Pool size in buffer cells\;Reserved when infi_size = 1\;" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="infi_size" descr="size is infinite\;When set, the size field is reserved" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="mode" descr="Pool quota calculation mode:\;0: Static\;1: Dynamic" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0xC.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared \;by writing to the clr field" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is \;cleared (and a new max value is tracked from the time \;the clear was performed)" access="OP" offset="0x10.31" size="0x0.1" />
	<field name="ext_buff_occupancy" descr="Extended current buffer occupancy\;Includes also all of the min_buff of the relevant PG buffer \;or traffic class associated to this pool\;Reserved when Spectrum-1, supported by Spectrum-2 \;and Quantum. Note: currenty not supported by Switch FW\;For NIC: Supported when ext_buff_occupancy_cap is set" access="RO" offset="0x14.0" size="0x0.24" />
</node>

<node name="sbsns_ext" descr="" size="0x18.0" >
	<field name="status" descr="Snapshot status:\;0: RELEASED - snapshot is non-active\;1: LOCKED - snapshot is active\;" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="trigger_id" descr="Tells which trigger id has trigger the snapshot.\;" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="trigger_parameters" descr="Trigger parameters.\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="time_high" descr="Snapshot time:\;The time when the last snapshot was taken as free_run\;ning_clock\;" access="RO" offset="0x10.0" size="0x0.6" />
	<field name="time_low" descr="Snapshot time:\;The time when the last snapshot was taken as free_run\;ning_clock\;" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="sbsnt_ext" descr="" size="0x4.0" >
	<field name="take" descr="Take snapshot:\;0: RELEASE - release snapshot\;1: TAKE_AND_TRAP - take snapshot of the guages and \;invoke trap SB_SNAPSHOT \;2: TAKE_NO_TRAP - take snapshot of the guages without \;invoking a trap\;When snapshot status is LOCKED then the TAKE will be \;ignored\;When snapshot status is RELEASED then the RELEASE \;will be ignored\;See SBSNS.status" access="OP" offset="0x0.0" size="0x0.2" />
</node>

<node name="sbsnte_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="type" descr="Type:\;0x20: WRED, egress, no CPU port\;0x31: Shared-buffer-per-Tclass, egress0x40: ING-CONG, \;ingress\;0x50: EGR-CONG, egress\;" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="tclass_en_high" descr="TClass/PG snapshot trigger enable (for IB switches this is VL \;enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tclass_en_low" descr="TClass/PG snapshot trigger enable (for IB switches this is VL \;enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="sbsr_ext" descr="" size="0xfc.0" >
	<field name="ports" descr="Ports:\;0: read per pg_buff and/or tclass\;1: ports, read per port\;" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;2: Host_port_number" access="INDEX" enum="Local_port_number=0x0,Host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="snap" descr="Read the snapshot gauge\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is \;cleared (and a new max value is tracked from the time \;the clear was performed)" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For NIC: Supported when descriptors_cap is set" access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="ingress_port_mask" descr="Bit vector for all ingress network port.\;Indicates which of the ports (for which the relevant bit is \;set) are affected by the set operation. Configuration of \;any other port does not change." access="INDEX" high_bound="7" low_bound="0" offset="0x10.0" size="0x20.0" />
	<field name="pg_buff_mask" descr="Bit vector for all priority groups.\;Indicates which of the priorities (for which the relevant bit \;is set) are affected by the set operation. Configuration of \;any other priority does not change.\;Range is 0..cap_max_pg_buffers - 1\;Reserved when ports = 1" access="INDEX" offset="0x30.0" size="0x0.10" />
	<field name="egress_port_mask" descr="Bit vector for all egress network port.\;Indicates which of the ports (for which the relevant bit is \;set) are affected by the set operation. Configuration of \;any other port does not change." access="INDEX" high_bound="7" low_bound="0" offset="0x34.0" size="0x20.0" />
	<field name="tclass_mask" descr="Bit vector for all traffic classes.\;Indicates which of the traffic classes (for which the rele\;vant bit is set) are affected by the set operation. Configu\;ration of any other priority does not change.\;Range is 0..cap_max_tclass - 1\;For traffic class to CPU port: range is 0..cap_max\;_cpu_ingress_tclass- 1\;Reserved when ports = 1" subnode="uint64" access="INDEX" offset="0x54.0" size="0x8.0" />
	<field name="shared_buffer_status" descr="Shared Buffer Properties, see Table 1594, &quot;Shared Buffer \;Status Fields,&quot; on page 1916\;This field is a collection of all the statuses of the \;requested quotas, while i=0..min{requested quotas, \;cap_sbsr_stat_size-1}\;The ith status refers a quota as follows;\;The occurrences of the masked ingress quotas are writ\;ten before the masked egress quotas.\;All the occurrences associated to port are written \;together from the smallest masked port index. In each \;port, the occurrences of the masked priority groups/ traf\;fic classes are written from the lowest to the highest." subnode="shared_buffer_status_ext" access="RO" high_bound="19" low_bound="0" offset="0x5C.0" size="0xa0.0" />
</node>

<node name="set_node_in_ext" descr="" size="0x40.0" >
	<field name="node_description" descr="Text describing the node" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
</node>

<node name="shared_buffer_status_ext" descr="" size="0x8.0" >
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0x0.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared \;by writing to the clr field" access="RO" offset="0x4.0" size="0x0.24" />
</node>

<node name="slot_info_ext" descr="" size="0x20.0" >
	<field name="active" descr="If set, the FW has completed the MDDC.device_enable com\;mand" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="lc_ready" descr="If set, the LC is powered on, matching the INI version and a \;new FW version can be burnt (if necessary)\;0: Not ready\;1: Ready\;2: Error\;3: Reserved" access="RO" offset="0x0.28" size="0x0.2" />
	<field name="sr_valid" descr="If set, Shift Register is valid (after being provisioned) and data \;can be sent from the switch ASIC to the line-card CPLD over \;Shift-Register." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="provisioned" descr="If set, the INI file is ready and the card is provisioned" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="ini_file_version" descr="User-configured version number of the current INI file.\;Valid only when active or lc_ready are &apos;1&apos;." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="hw_revision" descr="HW revision of the line-card as it appears in the current INI file.\;Valid only when active or lc_ready are &apos;1&apos;." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="card_type" descr="Card type\;0x00: Buffalo 4x400G\;0x01: Buffalo 8x200G\;0x02: Buffalo 16x100G" access="RO" offset="0x8.0" size="0x0.8" />
</node>

<node name="slot_name_ext" descr="" size="0x20.0" >
	<field name="slot_ascii_name" descr="Slot&apos;s ASCII name. Up to 20 chars\;" access="RO" high_bound="19" low_bound="0" offset="0x0.24" size="0x14.0" />
</node>

<node name="slred_info_page_ext" descr="" size="0x24.0" >
	<field name="mv_ticks_res" descr="resolution for each tick in the voltage axis in units of 0.1mV" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="ps_ticks_res" descr="resolution for each tick in the phase axis in units of 0.01ps" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="mv_center_pos" descr="center position of eye in 0.1mV" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="ps_center_pos" descr="center position of eye in 0.01ps" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="margin" descr="The margin that the lane received based on a specific config\;uration." access="RO" offset="0x8.0" size="0x0.24" />
	<field name="margin_version" descr="[internal] 0 - no margin available\;[internal] 1 - Figure of Merit" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="height_eo_neg" descr="Voltage offset from eye center to the negative side of the \;upper eye in 0.1mV." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="height_eo_pos" descr="Voltage offset from eye center to the positive side of the \;upper eye in 0.1mV." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="phase_eo_neg" descr="The offset from the eye center to the negative (left) side of the \;upper eye in 0.01ps." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="phase_eo_pos" descr="The offset from the eye center to the positive (right) side of \;the upper eye in 0.01ps." access="RO" offset="0x10.16" size="0x0.16" />
</node>

<node name="slred_page_data_ext" descr="" size="0xa0.0" >
	<field name="err_val" descr="Each err_val is 4 bits in ascending order. Each page contains \;320 err values." access="RO" high_bound="319" low_bound="0" offset="0x0.28" size="0xa0.0" />
</node>

<node name="slred_reg_ext" descr="" size="0xa8.0" >
	<field name="page_data_sel" descr="select page data number to display.\;0 - info page data\;1 - page data 1 (indexes 0 to 319)\;2 - page data 2 (indexes 320 to 639)\;3 - page data 3 (indexes 640 to 959)\;4 - page data 4 (indexes 960 to 1279)\;5 - page data 5 (indexes 1280 to 1599)\;6 - page data 6 (indexes 1600 to 1919)\;7 - page data 7 (indexes 1920 to 2239)" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lane" descr="Logical lane number\;[internal] Mapping to physical lane number can be queried in \;PMDR register" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB / label port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="1 - 28nm products\;3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="eye scan status:\;0 - eye scan was not performed.\;1 - unsupported scan for current speed.\;2 - system busy.\;3 - Performing eye scan.\;4 - eye scan completed. \;5 - error, eye scan not completed." access="RO" offset="0x0.28" size="0x0.4" />
	<field name="lane_speed" descr="The lane speed on which the eye scan was measured\;0-1 - reserved\;2 - QDR (10 Gb/s) / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE) (10.3125 Gb/s) \;4 - FDR (56GE) (14.0625 Gb/s) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) (25.78125 Gb/s) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE) (26.5625Gbd / 53.125Gb/s) \;7 - 15 - reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="abort" descr="gracefully abort the scan process.\;abort and en bits cannot be set together." access="WO" offset="0x4.14" size="0x0.1" />
	<field name="err_res_base" descr="base value for calculating err_val legend. \;0 - err_res_base is 2\;1 - err_res_base is 3\;2 - err_res_base is 5\;3 - err_res_base is 1\;4-7 - reserved\;\;if err_res_scale is exponential:\;err value &gt; 0 will represent errors between \;err_res_base ^(err_val - 1) +1 to err_res_base^err_val\;\;For example if err_res_base is 2:\;0 err_value represents 0 errors\;1 err_value represents 1-2 errors\;2 err_value represents 3-4 errors\;3 err_value represents 5-8 errors\;...\;7 err_value represents 2^6+1 and above\;\;if err_res_scale is linear:\;err value &gt; 0 will represent errors between \;err_res_base *(err_val-1) + 1 to err_res_base *err_val\;\;For example if err_res_base is 2:\;0 err_value represents 0 errors\;1 err_value represents 1-2 errors\;2 err_value represents 3-4 errors\;3 err_value represents 5-6 errors\;...\;7 err_value represents 2*6 + 1 and above\;" access="RW" offset="0x4.15" size="0x0.3" />
	<field name="eye_sel" descr="eye selection for PAM4 signals.\;0 - up\;1 - mid\;2 - down\;Note: for NRZ field is ignored" access="RW" offset="0x4.18" size="0x0.2" />
	<field name="measure_time" descr="max measure time in seconds for single eye diagram.\;0 - 10 sec\;1 - 30 sec\;2 - 60 sec\;3 - 90 sec\;4 - 120 sec\;5 - 240 sec\;6 - 480 sec\;7 - 600 sec\;8 - 900 sec\;9-15 reserved\;each tic measure time will be measure_time / (hight_dim x \;width_dim)" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="eye_diag_dim" descr="dimensions of eye scan matrix in the format of hight_dim x \;width_dim\;0 - 16x16 (256 err val)\;1 - 32x32 (1024 err val)\;2 - 32x64 (1024 err val)\;3 - 64x32 (2048 err val)" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="err_res_scale" descr="error res multiplier for err_res_base field\;0 - exponential scale\;1 - linear scale\;2-3 - reserved" access="RW" offset="0x4.27" size="0x0.2" />
	<field name="destructive_ctrl" descr="0 - non destructive scan\;1 - destructive scan\;Note: if non destructive scan is not supported this field is \;ignored and a destructive scan will be operated" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="last_scan" descr="set to &apos;1&apos; when performing last eye scan for lane.\;For example: when scanning 3 eyes in the order of up, mid, \;down. field should be set when scanning down eye.\;If scanning only 1 eye, field should be set." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="en" descr="start eye scan" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="page_data" descr="page data for index page_data_sel\;page 0 will contain info page data.\;Table  1467, &quot;SLRED - Serdes Lane Receive Eye Diagram Reg\;ister Layout for info page,&quot; on page  1789\;the page data 1-7 will contain the err_val for each index in \;ascending order.\;Table  1469, &quot;SLRED - Serdes Lane Receive Eye Diagram Reg\;ister Layout for page_data,&quot; on page  1791\;Each err_val[i] represents the bit errors of row floor(i / \;width_dim)\;and column i mod width_dim.\;Matrix is built starting from the left bottom corner.\;each err_val indicates the number of bit errors for one tick" subnode="slred_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xa0.0" />
</node>

<node name="slred_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xa0.0" >
	<field name="slred_info_page_ext" descr="" subnode="slred_info_page_ext" offset="0x0.0" size="0x24.0" />
	<field name="slred_page_data_ext" descr="" subnode="slred_page_data_ext" offset="0x0.0" size="0xa0.0" />
</node>

<node name="slrg_16nm_ext" descr="" size="0x24.0" >
	<field name="grade_lane_speed" descr="The lane speed on which the grade was measured:\;0 - SDR / PCIe Gen 1\;1 - DDR / PCIe Gen 2\;2 - QDR / PCIe Gen 3\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / PCIe Gen 4\;5 - EDR (25GE / 50GE / 100GE) / PCIe Gen 5\;6 - HDR (50GE / 200GE / 400GE)\;7- 9 - reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13 - 15 - reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="grade" descr="The grade that the lane received based on a specific configu\;ration.\;" access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg_up" descr="Voltage offset from eye center to the negative side of the \;upper eye. Only applicable for PAM4 signal." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="height_eo_pos_up" descr="Voltage offset from eye center to the positive side of the \;upper eye.\;Only applicable for PAM4 signal." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="height_eo_pos_mid" descr="Voltage offset from eye center to the positive side of the mid\;dle eye." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="phase_eo_neg_up" descr="The offset from the eye center to the negative (left) side of the \;upper eye. Only applicable for PAM4 signal." access="RO" offset="0xC.16" size="0x0.8" />
	<field name="phase_eo_pos_up" descr="The offset from the eye center to the positive (right) side of \;the upper eye. Only applicable for PAM4 signal." access="RO" offset="0xC.24" size="0x0.8" />
	<field name="phase_eo_neg_mid" descr="The offset from the eye center to the negative (left) side of the \;middle eye." access="RO" offset="0x10.0" size="0x0.8" />
	<field name="phase_eo_pos_mid" descr="The offset from the eye center to the positive (right) side of \;the middle eye." access="RO" offset="0x10.8" size="0x0.8" />
	<field name="height_eo_neg_mid" descr="Voltage offset from eye center to the negative side of the mid\;dle eye." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="height_eo_neg_low" descr="Voltage offset from eye center to the negative side of the \;lower eye. Only applicable for PAM4 signal." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos_low" descr="Voltage offset from eye center to the positive side of the lower \;eye. Only applicable for PAM4 signal." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg_low" descr="The offset from the eye center to the negative (left) side of the \;lower eye. Only applicable for PAM4 signal." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="phase_eo_pos_low" descr="The offset from the eye center to the positive (right) side of \;the lower eye. Only applicable for PAM4 signal." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="up_eye_grade" descr="upper eye grade" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="mid_eye_grade" descr="middle eye grade" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="dn_eye_grade" descr="lower eye grade" access="RO" offset="0x20.0" size="0x0.16" />
</node>

<node name="slrg_40nm_28nm_ext" descr="" size="0x24.0" >
	<field name="grade_lane_speed" descr="The lane speed on which the grade was measured:\;0 - SDR\;1 - DDR\;2 - QDR\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE)\;5 - EDR (25GE / 50GE / 100GE)\;6 - 9 - reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13 - 15 - reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="grade" descr="" access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg" descr="Voltage offset from eye center to the negative side." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos" descr="Voltage offset from eye center to the positive side." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg" descr="The offset from the eye center to the negative side." access="RO" offset="0x1C.0" size="0x0.8" />
	<field name="phase_eo_pos" descr="The offset from the eye center to the positive side." access="RO" offset="0x1C.16" size="0x0.8" />
</node>

<node name="slrg_7nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurment" descr="Bitmask for measurement activation\;Bit 0 - Upper eye\;Bit 1 - Middle eye\;Bit 2 - Lower eye\;Bit 3- Composite eye\;Note: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.\;valid only when SLRG.status is &apos;1&apos;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="fom_mode" descr="fom mode:\;FOM eye mode to search\;0x0: FOM_MODE_EYEC\;0x1: FOM_MODE_EYEO\;0x2: FOM_MODE_EYEM\;0x3: FOM_MODE_BER\;0x4:FOM_MODE_EYEC_VN\;0x5:FOM_MODE_EYEC_VP\;0x6:FOM_MODE_EYEM_VN\;0x7:FOM_MODE_EYEM_VP" access="RO" enum="FOM_MODE_EYEC=0x0,FOM_MODE_EYEO=0x1,FOM_MODE_EYEM=0x2,FOM_MODE_BER=0x3,FOM_MODE_EYEC_VN=0x4,FOM_MODE_EYEC_VP=0x5,FOM_MODE_EYEM_VN=0x6,FOM_MODE_EYEM_VP=0x7" offset="0x4.16" size="0x0.3" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.\;valid only if eom_measurment bit &apos;2&apos; is set" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.\;valid only if eom_measurment bit &apos;1&apos; is set" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.\;valid only if eom_measurment bit &apos;0&apos; is set" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.\;valid only if eom_measurment bit &apos;3&apos; is set" access="RO" offset="0x8.24" size="0x0.8" />
</node>

<node name="slrg_7nm_testing_ext" descr="" size="0x1c.0" >
	<field name="iterations" descr="Number of iterations to run FOM\;0 - fw default" access="OP" offset="0x0.0" size="0x0.10" />
	<field name="status" descr="0 - measure not preformed\;1 - measuring in progress\;2 - measuring done" access="RO" offset="0x0.16" size="0x0.3" />
	<field name="lane_meas_info" descr="FOM measurements info for lane &lt;i&gt;\;See Table 1331, &quot;Lane Measure Info layout,&quot; on page 1626." subnode="slrg_lane_measure_info_ext" access="RO" offset="0x4.0" size="0x18.0" />
</node>

<node name="slrg_lane_measure_info_ext" descr="" size="0x18.0" >
	<field name="comp_max" descr="maximum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="lower_max" descr="maximum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="mid_max" descr="maximum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="upper_max" descr="maximum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="comp_min" descr="minimum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="lower_min" descr="minimum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="mid_min" descr="minimum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="upper_min" descr="minimum measured FOM out of all the measurements for \;every eye.\;NRZ have only composite eye value" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="mid_std" descr="Value of standard deviation square in 0.1 units. To get the \;value of the standard deviation, need to apply square root \;function on value.\;Calculated on all FOM measurements for every eye.\;NRZ have only composite eye value" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="upper_std" descr="Value of standard deviation square in 0.1 units. To get the \;value of the standard deviation, need to apply square root \;function on value.\;Calculated on all FOM measurements for every eye.\;NRZ have only composite eye value" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="comp_std" descr="Value of standard deviation square in 0.1 units. To get the \;value of the standard deviation, need to apply square root \;function on value.\;Calculated on all FOM measurements for every eye.\;NRZ have only composite eye value" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="lower_std" descr="Value of standard deviation square in 0.1 units. To get the \;value of the standard deviation, need to apply square root \;function on value.\;Calculated on all FOM measurements for every eye.\;NRZ have only composite eye value" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="mid_avg" descr="average measured FOM in 0.1 units out of all the measure\;ments for every eye.\;NRZ have only composite eye value" access="RO" offset="0x10.0" size="0x0.12" />
	<field name="upper_avg" descr="average measured FOM in 0.1 units out of all the measure\;ments for every eye.\;NRZ have only composite eye value" access="RO" offset="0x10.16" size="0x0.12" />
	<field name="comp_avg" descr="average measured FOM in 0.1 units out of all the measure\;ments for every eye.\;NRZ have only composite eye value" access="RO" offset="0x14.0" size="0x0.12" />
	<field name="lower_avg" descr="average measured FOM in 0.1 units out of all the measure\;ments for every eye.\;NRZ have only composite eye value" access="RO" offset="0x14.16" size="0x0.12" />
</node>

<node name="slrg_reg_ext" descr="" size="0x28.0" >
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR Main\;5 - USR Tile\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number\;[internal] Mapping to physical lane number can be queried in \;PMDR register" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB / label port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 40nm products\;1 - 28nm products\;3 - 16nm products\;4 - 7nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid\;" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="Table 1323, &quot;SLRG - Serdes Lane Receive Grade Register \;Layout for 40nm and 28nm,&quot; on page 1621\;Table 1325, &quot;SLRG - Serdes Lane Receive Grade Register \;Layout for 16nm,&quot; on page 1622\;Table 1327, &quot;SLRG - Serdes Lane Receive Grade Register \;Layout for 7nm,&quot; on page 1624\;Table 1329, &quot;SLRG - Serdes Lane Receive Grade Register \;Layout for 7nm Testing,&quot; on page 1625" subnode="slrg_reg_page_data_auto_ext" access="RO" offset="0x4.0" size="0x24.0" />
</node>

<node name="slrg_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x24.0" >
	<field name="slrg_40nm_28nm_ext" descr="" subnode="slrg_40nm_28nm_ext" offset="0x0.0" size="0x24.0" />
	<field name="slrg_16nm_ext" descr="" subnode="slrg_16nm_ext" offset="0x0.0" size="0x24.0" />
	<field name="slrg_7nm_ext" descr="" subnode="slrg_7nm_ext" offset="0x0.0" size="0x18.0" />
	<field name="slrg_7nm_testing_ext" descr="" subnode="slrg_7nm_testing_ext" offset="0x0.0" size="0x1c.0" />
</node>

<node name="sltp_16nm_ext" descr="" size="0x18.0" >
	<field name="post_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 \;or smaller.\;" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="main_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 \;or smaller.\;" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="pre_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 \;or smaller.\;" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="pre_2_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 \;or smaller.\;" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="ob_alev_out" descr="Output common mode. Values can be set in the range of (0-\;30)" access="RW" offset="0x8.0" size="0x0.5" />
	<field name="ob_amp" descr="Output amplitude. Values can be set in the range of (10-100)." access="RW" offset="0x8.8" size="0x0.7" />
	<field name="ob_m2lp" descr="MSB to LSB proportion. \;Values can be set between -10 to 50. \;\;MSB emphasis achieved when value is between -10 to -1 \;LSB emphasis achieved when value is between 1 to 50. \;When set to 0 - equal proportion." access="RW" offset="0x8.25" size="0x0.7" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;0: configuration_warning - taps values can&apos;t be set to serdes \;due to internal limitations. Actual TX configuration is modify \;internally with the same sum of taps weight.\;11: Illegal_ob_combination - ob_m2lp, ob_amp and ob_alev \;is in legal range each, but the total combination can&apos;t be set \;to serdes due to internal limitations, the Set command is \;ignored.\;12: Illegal_ob_m2lp\;13: Illegal_ob_amp\;14: Illegal_ob_alev_out\;15: Illegal_taps\;\;Bit 12-0 - Reserved /Unknown" access="RO" enum="configuration_warning=0x0,Illegal_ob_combination=0xb,Illegal_ob_m2lp=0xc,Illegal_ob_amp=0xd,Illegal_ob_alev_out=0xe,Illegal_taps=0xf" offset="0xC.16" size="0x0.16" />
</node>

<node name="sltp_28nm_40nm_ext" descr="" size="0x10.0" >
	<field name="ob_tap2" descr="" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ob_tap1" descr="" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="ob_tap0" descr="" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="polarity" descr="Tx lane polarity" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="ob_bias" descr="" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="ob_reg" descr="(ref_txcml100_reg)" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="ob_preemp_mode" descr="Concatenation of taps polarity + preemp_sel" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="ob_leva" descr="" access="RW" offset="0x8.20" size="0x0.4" />
	<field name="ob_bad_stat" descr="Bitmask for bad SET status:\;Bit 0 - Illegal ob_bais value\;Bit 1 - Illegal ob taps polarity (distance between taps)" access="RO" offset="0xC.29" size="0x0.2" />
	<field name="ob_norm" descr="OB Normalization status:\;0 - No Normalization was done\;1 - Normalization performed" access="RO" offset="0xC.31" size="0x0.1" />
</node>

<node name="sltp_7nm_ext" descr="" size="0x18.0" >
	<field name="fir_pre2" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3), f\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude \;equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from \;the value that has been set." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="fir_pre3" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3), f\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude \;equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from \;the value that has been set." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0: pre3_is_out_of_range\;Bit 1: pre2_is_out_of_range\;Bit 2: pre1_is_out_of_range\;Bit 3: main_tap_is_out_of_range\;Bit 4: post1_is_out_of_range\;Bit 5: sum_of_taps_is_out_of_range\;Bit 6: taps_not_alinged_with_speed" access="RO" enum="pre3_is_out_of_range=0x1,pre2_is_out_of_range=0x2,pre1_is_out_of_range=0x4,main_tap_is_out_of_range=0x8,post1_is_out_of_range=0x10,sum_of_taps_is_out_of_range=0x20,taps_not_alinged_with_speed=0x40" offset="0x0.16" size="0x0.8" />
	<field name="fir_post1" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3), f\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude \;equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from \;the value that has been set." access="RW" offset="0x4.8" size="0x0.8" />
	<field name="fir_main" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3), f\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude \;equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from \;the value that has been set." access="RW" offset="0x4.16" size="0x0.8" />
	<field name="fir_pre1" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3), f\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude \;equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from \;the value that has been set." access="RW" offset="0x4.24" size="0x0.8" />
</node>

<node name="sltp_lut_7nm_ext" descr="" size="0x48.0" >
	<field name="fir_pre2" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Valid values for taps:\;fir_pre2 [0,8]\;fir_pre3 [-5,0]" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="fir_pre3" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Valid values for taps:\;fir_pre2 [0,8]\;fir_pre3 [-5,0]" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0: pre3_is_out_of_range\;Bit 1: pre2_is_out_of_range\;Bit 7: LUT_value_is_out_of_range" access="RO" enum="pre3_is_out_of_range=0x1,pre2_is_out_of_range=0x2,LUT_value_is_out_of_range=0x80" offset="0x0.16" size="0x0.8" />
	<field name="lut0" descr="Lookup Table values per entry" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="lut1" descr="Lookup Table values per entry" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="lut2" descr="Lookup Table values per entry" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="lut3" descr="Lookup Table values per entry" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lut4" descr="Lookup Table values per entry" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="lut5" descr="Lookup Table values per entry" access="RW" offset="0xC.8" size="0x0.8" />
	<field name="lut6" descr="Lookup Table values per entry" access="RW" offset="0xC.16" size="0x0.8" />
	<field name="lut7" descr="Lookup Table values per entry" access="RW" offset="0xC.24" size="0x0.8" />
	<field name="lut8" descr="Lookup Table values per entry" access="RW" offset="0x10.0" size="0x0.8" />
	<field name="lut9" descr="Lookup Table values per entry" access="RW" offset="0x10.8" size="0x0.8" />
	<field name="lut10" descr="Lookup Table values per entry" access="RW" offset="0x10.16" size="0x0.8" />
	<field name="lut11" descr="Lookup Table values per entry" access="RW" offset="0x10.24" size="0x0.8" />
	<field name="lut12" descr="Lookup Table values per entry" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="lut13" descr="Lookup Table values per entry" access="RW" offset="0x14.8" size="0x0.8" />
	<field name="lut14" descr="Lookup Table values per entry" access="RW" offset="0x14.16" size="0x0.8" />
	<field name="lut15" descr="Lookup Table values per entry" access="RW" offset="0x14.24" size="0x0.8" />
	<field name="lut16" descr="Lookup Table values per entry\;" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="lut17" descr="Lookup Table values per entry\;" access="RW" offset="0x18.8" size="0x0.8" />
	<field name="lut18" descr="Lookup Table values per entry\;" access="RW" offset="0x18.16" size="0x0.8" />
	<field name="lut19" descr="Lookup Table values per entry\;" access="RW" offset="0x18.24" size="0x0.8" />
	<field name="lut20" descr="Lookup Table values per entry\;" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="lut21" descr="Lookup Table values per entry\;" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="lut22" descr="Lookup Table values per entry\;" access="RW" offset="0x1C.16" size="0x0.8" />
	<field name="lut23" descr="Lookup Table values per entry\;" access="RW" offset="0x1C.24" size="0x0.8" />
	<field name="lut24" descr="Lookup Table values per entry\;" access="RW" offset="0x20.0" size="0x0.8" />
	<field name="lut25" descr="Lookup Table values per entry\;" access="RW" offset="0x20.8" size="0x0.8" />
	<field name="lut26" descr="Lookup Table values per entry\;" access="RW" offset="0x20.16" size="0x0.8" />
	<field name="lut27" descr="Lookup Table values per entry\;" access="RW" offset="0x20.24" size="0x0.8" />
	<field name="lut28" descr="Lookup Table values per entry\;" access="RW" offset="0x24.0" size="0x0.8" />
	<field name="lut29" descr="Lookup Table values per entry\;" access="RW" offset="0x24.8" size="0x0.8" />
	<field name="lut30" descr="Lookup Table values per entry\;" access="RW" offset="0x24.16" size="0x0.8" />
	<field name="lut31" descr="Lookup Table values per entry\;" access="RW" offset="0x24.24" size="0x0.8" />
	<field name="lut32" descr="Lookup Table values per entry\;" access="RW" offset="0x28.0" size="0x0.8" />
	<field name="lut33" descr="Lookup Table values per entry\;" access="RW" offset="0x28.8" size="0x0.8" />
	<field name="lut34" descr="Lookup Table values per entry\;" access="RW" offset="0x28.16" size="0x0.8" />
	<field name="lut35" descr="Lookup Table values per entry\;" access="RW" offset="0x28.24" size="0x0.8" />
	<field name="lut36" descr="Lookup Table values per entry\;" access="RW" offset="0x2C.0" size="0x0.8" />
	<field name="lut37" descr="Lookup Table values per entry\;" access="RW" offset="0x2C.8" size="0x0.8" />
	<field name="lut38" descr="Lookup Table values per entry\;" access="RW" offset="0x2C.16" size="0x0.8" />
	<field name="lut39" descr="Lookup Table values per entry\;" access="RW" offset="0x2C.24" size="0x0.8" />
	<field name="lut40" descr="Lookup Table values per entry\;" access="RW" offset="0x30.0" size="0x0.8" />
	<field name="lut41" descr="Lookup Table values per entry\;" access="RW" offset="0x30.8" size="0x0.8" />
	<field name="lut42" descr="Lookup Table values per entry\;" access="RW" offset="0x30.16" size="0x0.8" />
	<field name="lut43" descr="Lookup Table values per entry\;" access="RW" offset="0x30.24" size="0x0.8" />
	<field name="lut44" descr="" access="RW" offset="0x34.0" size="0x0.8" />
	<field name="lut45" descr="Lookup Table values per entry\;" access="RW" offset="0x34.8" size="0x0.8" />
	<field name="lut46" descr="Lookup Table values per entry\;" access="RW" offset="0x34.16" size="0x0.8" />
	<field name="lut47" descr="Lookup Table values per entry\;" access="RW" offset="0x34.24" size="0x0.8" />
	<field name="lut48" descr="Lookup Table values per entry\;" access="RW" offset="0x38.0" size="0x0.8" />
	<field name="lut49" descr="Lookup Table values per entry\;" access="RW" offset="0x38.8" size="0x0.8" />
	<field name="lut50" descr="Lookup Table values per entry\;" access="RW" offset="0x38.16" size="0x0.8" />
	<field name="lut51" descr="Lookup Table values per entry\;" access="RW" offset="0x38.24" size="0x0.8" />
	<field name="lut52" descr="Lookup Table values per entry\;" access="RW" offset="0x3C.0" size="0x0.8" />
	<field name="lut53" descr="Lookup Table values per entry\;" access="RW" offset="0x3C.8" size="0x0.8" />
	<field name="lut54" descr="Lookup Table values per entry\;" access="RW" offset="0x3C.16" size="0x0.8" />
	<field name="lut55" descr="Lookup Table values per entry\;" access="RW" offset="0x3C.24" size="0x0.8" />
	<field name="lut56" descr="Lookup Table values per entry\;" access="RW" offset="0x40.0" size="0x0.8" />
	<field name="lut57" descr="Lookup Table values per entry\;" access="RW" offset="0x40.8" size="0x0.8" />
	<field name="lut58" descr="Lookup Table values per entry\;" access="RW" offset="0x40.16" size="0x0.8" />
	<field name="lut59" descr="Lookup Table values per entry\;" access="RW" offset="0x40.24" size="0x0.8" />
	<field name="lut60" descr="Lookup Table values per entry\;" access="RW" offset="0x44.0" size="0x0.8" />
	<field name="lut61" descr="Lookup Table values per entry\;" access="RW" offset="0x44.8" size="0x0.8" />
	<field name="lut62" descr="Lookup Table values per entry\;" access="RW" offset="0x44.16" size="0x0.8" />
	<field name="lut63" descr="Lookup Table values per entry\;" access="RW" offset="0x44.24" size="0x0.8" />
</node>

<node name="sltp_reg_ext" descr="" size="0x4c.0" >
	<field name="c_db" descr="copy transmitter parameters to Data Base. \;" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" offset="0x0.1" size="0x0.3" />
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe) / 5GBASE-R\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / \;106.25Gb/s)\;8-9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13-15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number\;[internal] Mapping to physical lane number can be queried in \;PMDR register" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="tx_policy" descr="Configures Tx parameter set policy\;0 - Tx parameters will be set according to best possible con\;figuration chosen by the system\;1 - Tx parameters will be set according to Data Base only and \;will not be overridden by link training (e.g KR-Startup)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is \;interpreted:\;0 - Local port number\;1 - IB / label port number\;3 - PCI / Out of Band" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm\;1: prod_28nm\;3: prod_16nm\;4: prod_7nm\;7: prod_lut_7nm" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_lut_7nm=0x7" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid" access="RO" offset="0x0.28" size="0x0.2" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="Table  1311, &quot;SLTP - Serdes Lane Transmit Parameters Reg\;ister Layout for 28nm and 40nm,&quot; on page  1611\;Table  1313, &quot;SLTP - Serdes Lane Transmit Parameters Reg\;ister Layout for 16nm,&quot; on page  1612\;Table  1317, &quot;SLTP - Serdes Lane Transmit Parameters Reg\;ister Layout for 7nm,&quot; on page  1614\;Table  1319, &quot;SLTP - Serdes Lane Transmit Parameters Reg\;ister Layout for LUT 7nm,&quot; on page  1615" subnode="sltp_reg_page_data_auto_ext" access="RO" offset="0x4.0" size="0x48.0" union_selector="$(parent).version" />
</node>

<node name="sltp_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x48.0" >
	<field name="sltp_28nm_40nm_ext" descr="" subnode="sltp_28nm_40nm_ext" offset="0x0.0" selected_by="prod_28nm" size="0x10.0" />
	<field name="sltp_16nm_ext" descr="" subnode="sltp_16nm_ext" offset="0x0.0" selected_by="prod_16nm" size="0x18.0" />
	<field name="sltp_7nm_ext" descr="" subnode="sltp_7nm_ext" offset="0x0.0" selected_by="prod_7nm" size="0x18.0" />
	<field name="sltp_lut_7nm_ext" descr="" subnode="sltp_lut_7nm_ext" offset="0x0.0" selected_by="prod_lut_7nm" size="0x48.0" />
</node>

<node name="stat_bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="watermark" descr="Watermark in cells (max buffer usage since last clear)\;For stat_shared_headroom_pool, this field is reserved." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="used_buffer" descr="Number of used buffer cells." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="string_db_parameters_ext" descr="" size="0x8.0" >
	<field name="string_db_base_address" descr="Offset of the first string of the section, relative to the entire \;string data base, given in bytes." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="string_db_size" descr="Size of string database section, given in bytes" access="RO" offset="0x4.0" size="0x0.24" />
</node>

<node name="uint64" descr="" size="0x8.0" >
	<field name="hi" descr="" offset="0x0.0" size="0x4.0" />
	<field name="lo" descr="" offset="0x4.0" size="0x4.0" />
</node>

<node name="usr_xsr_physical_layer_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear \;event in msec.\;[Internal] supported in USR" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear \;event in msec.\;[Internal] supported in USR" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane4_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane4_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane5_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane5_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane6_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane6_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane7_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane7_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane4_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane4_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane5_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane5_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane6_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane6_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane7_high" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane7_low" descr="Perf.PortExtendedSpeedsCounters(FECCor\;rectableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="link_down_events" descr="Perf.PortCounters(LinkDownedCounter)\;[Internal] supported in USR" access="RO" offset="0x88.0" size="0x4.0" />
</node>

<node name="vhca_trust_level_ext" descr="" size="0x10.0" >
	<field name="vhca_id" descr="Valid only when all_vhca==0" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="all_vhca" descr="If set, set turst_level to all vHCAs that belong to this \;vport_group_manager." access="WO" offset="0x0.31" size="0x0.1" />
	<field name="trust_level" descr="Bitmask indicates trust levels supported for a vhca\;Bit 0x0: FULL_TRUST" access="WO" enum="FULL_TRUST=0x1" offset="0x4.0" size="0x4.0" />
</node>

<node name="ztt_ext" descr="" size="0x10.0" >
	<field name="operation" descr="0x0: DISABLE\;0x1: ENABLED\;0x2: RESET" access="WO" enum="DISABLE=0x0,ENABLED=0x1,RESET=0x2" offset="0x0.0" size="0x0.3" />
	<field name="status" descr="0x0: ZTT_DISABLED\;0x1: ZTT_ENABLED\;0x2: ZTT_ERROR" access="RO" enum="ZTT_DISABLED=0x0,ZTT_ENABLED=0x1,ZTT_ERROR=0x2" offset="0x0.8" size="0x0.3" />
</node>

<node name="root" size="0x420.0" descr="" >
	<field name="register_access_table_hca_ext_Nodes" offset="0x0.0" size="0x420.0" subnode="register_access_table_hca_ext_Nodes" descr="" />
</node>

<node name="register_access_table_hca_ext_Nodes" size="0x420.0" attr_is_union="1" descr="" >
	<field name="access_reg_summary_selector_ext" offset="0x0.0" size="0x420.0" subnode="access_reg_summary_selector_ext" descr="" />
</node>
</NodesDefinition>
