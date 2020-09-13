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
<info source_doc_name="" source_doc_version="Rev 1.55.014" />
<node name="IB_long_portcntrs_attribute_grp_data_ext" descr="" size="0xf8.0" >
	<field name="symbol_error_counter_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="symbol_error_counter_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="link_error_recovery_counter_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="link_error_recovery_counter_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="link_downed_counter_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="link_downed_counter_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="port_rcv_errors_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="port_rcv_errors_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="port_rcv_remote_physical_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_rcv_remote_physical_errors_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="port_rcv_switch_relay_errors_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="port_rcv_switch_relay_errors_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="port_xmit_discards_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="port_xmit_discards_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="port_xmit_constraint_errors_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="port_xmit_constraint_errors_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="port_rcv_constraint_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="port_rcv_constraint_errors_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="local_link_integrity_errors_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="local_link_integrity_errors_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="excessive_buffer_overrun_errors_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="excessive_buffer_overrun_errors_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="vl_15_dropped_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="vl_15_dropped_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="port_xmit_data_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="port_xmit_data_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="port_rcv_data_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="port_rcv_data_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="port_xmit_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="port_xmit_pkts_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="port_rcv_pkts_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="port_rcv_pkts_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="port_xmit_wait_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="port_xmit_wait_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x84.0" size="0x4.0" />
</node>

<node name="IB_portcntrs_attribute_grp_data_ext" descr="" size="0xf8.0" >
	<field name="link_downed_counter" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="link_error_recovery_counter" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="symbol_error_counter" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="port_rcv_remote_physical_errors" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="port_rcv_errors" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="port_xmit_discards" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="port_rcv_switch_relay_errors" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="excessive_buffer_overrun_errors" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xC.0" size="0x0.4" />
	<field name="local_link_integrity_errors" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xC.4" size="0x0.4" />
	<field name="port_rcv_constraint_errors" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="port_xmit_constraint_errors" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="vl_15_dropped" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="port_xmit_data" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="port_rcv_data" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="port_xmit_pkts" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="port_rcv_pkts" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_xmit_wait" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x24.0" size="0x4.0" />
</node>

<node name="SLCRV2_ext" descr="" size="0x38.0" >
	<field name="type" descr="Hash type\;0: CRC (default)\;1: XOR \;2: Random\;3: CRC2, For Spectrum-2 and on\;4: XOR2 - this is a always symmetric hash function, always sym\;metric also for inner fields (L2, L3,L4). When enabled the sh is \;reserved. For Spectrum-2 and on. Currently not Supported by FW.  \;" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="sh" descr="Symmetric hash \;When set, the hash calculation will result in the same hash value as \;when the source address (layer 2 and layer 3) is swapped. This \;ensures that the same conversions will result in the same hash \;value.\;Note: When this bit is set, enabling addresses in outer_header_\;fields_enables and inner_header_fields_enables\;For SwitchX/-2 must be in couples - both source and destination. \;This includes the following sets:\;- SMAC, DMAC\;- SIP, DIP\;- TCP/UDP source port, TCP/UDP destination port\;- SID, DID, for SwitchX/-2 only\;" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="local_port" descr="Ingress Local port number\;Supported from CPU port\;Not supported from router port\;Reserved when pp = Global Configuration" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pp" descr="Per Port Configuration\;0: Global Configuration (for all ports)\;1: Per port configuration, based on local_port field.\;Note: SW must not read as global if last write was not global." access="INDEX" offset="0x0.24" size="0x0.1" />
	<field name="seed" descr="LAG seed value\;The seed is the same for all ports (latest configuration configures \;the seed for all ports)." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="general_fields" descr="This is a bit mask, in which each bit enables a specific field to be \;included in the hash calculation. \;Bit 0: Ingress port\;Bit i: custom_bytes i-2\;i = 2 .. 2 + (cap_max_custom_byte_sets_for_hash * cap_cus\;tom_byte_entry_size - 1)\;See Section 10.3.14, &quot;Custom Bytes,&quot; on page 1356" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="outer_header_enables" descr="Outer header enables. Each bit enables a specific layer field to be \;included in the hash calculation. Layers that are not listed below \;are enabled by default.\;Bit 0: Enable Layer2 fields if packet is not IPv4/6\;Bit 1: Enable Layer2 fields if packet is IPv4\;Bit 2: Enable Layer2 fields if packet is IPv6\;Bit 3: Enable IPv4 fields if packet is not TCP and not UDP\;Bit 4: Enable IPv4 fields if packet is either TCP or UDP\;Bit 5: Enable IPv6 fields if packet is not TCP and not UDP\;Bit 6: Enable IPv6 fields if packet is either TCP or UDP\;Bit 7: Enable TCP/UDP header fields if packet is IPv4\;Bit 8: Enable TCP/UDP header fields if packet is IPv6" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="outer_header_fields_enable" descr="Layer2 fields, subject to outer_header_enables:\;Bit 0: SMAC\;Bit 1: DMAC\;Bit 2: Ethertype\;Bit 3: Outer VID\;Bit 4: Outer PCP\;Bit 5: Outer DEI\;Bit 6: Inner VID\;Bit 7: Inner PCP\;Bit 8: Inner DEI\;\;IPv4 fields, subject to outer_header_enables:\;Bits 12:9: IPv4 SIP 0-3 enable per byte. For ARP all bytes are used\;Bits 16:13: IPv4 DIP 0-3 enable per byte. For ARP all bytes are \;used\;Bit 17: IPv4 Protocol\;Bit 18: IPv4 DSCP\;Bit 19: IPv4 ECN\;Bit 20: IPv4 IP L3 Length - length field bits [13:10]\;\;IPv6 fields, subject to outer_header_enables:\;Bits 21: IPv6 enable bytes of SIP 0-7. For ARP all bytes are used\;Bits 28:22 reserved\;Bits 36:29: IPv6 SIP 8-15 enable per byte. For ARP all bytes are \;used\;Bits 37: IPv6 enable bytes of DIP 0-7. For ARP all bytes are used\;Bits 44:38 reserved\;Bits 52:45: IPv6 DIP 8-15 enable per byte. For ARP all bytes are \;used\;Bit 53: IPv6 Next Header\;Bit 54: IPv6 DSCP\;Bit 55: IPv6 ECN\;Bit 56: IPv6 IP L3 Length - length field bits [13:10]\;Bit 57: IPv6 Flow label\;\;RoCE v1 fields: [TBD]\;Bit 58: [TBD] GRH SIP\;Bit 59: [TBD] GRH DIP\;Bit 60: [TBD] GRH Next Protocol\;Bit 61: [TBD] GRH DSCP\;Bit 62: [TBD] GRH ECN\;Bit 63: [TBD] GRH L3 Length\;Bit 64: [TBD] GRH Flow label" access="RW" high_bound="4" low_bound="0" offset="0x14.0" size="0x14.0" />
	<field name="inner_header_enables" descr="Inner header enables. Each bit enables a specific layer field to be \;included in the hash calculation. Layers that are not listed below \;are enabled by default.\;Bit 0: Enable inner Layer2 fields if inner packet is not IPv4/6\;Bit 1: Enable inner Layer2 fields if inner packet is IPv4\;Bit 2: Enable inner Layer2 fields if inner packet is IPv6\;Bit 3: Enable inner IPv4 fields if inner packet is not TCP and not \;UDP\;Bit 4: Enable inner IPv4 fields if inner packet is either TCP or \;UDP\;Bit 5: Enable inner IPv6 fields if inner packet is not TCP and not \;UDP\;Bit 6: Enable inner IPv6 fields if inner packet is either TCP or \;UDP\;Bit 7: Enable inner TCP/UDP header fields if inner packet is IPv4\;Bit 8: Enable inner TCP/UDP header fields if inner packet is IPv6\;others: reserved" access="RW" offset="0x2C.0" size="0x0.16" />
	<field name="inner_header_fields_enable" descr="Inner header fields enable.\;\;Inner Layer2 fields, subject to inner_header_enables:\;Bit 0: SMAC\;Bit 1: DMAC\;Bit 2: Ethertype\;\;Inner IPv4 fields, subject to inner_header_enables:\;Bits 6:3: IPv4 SIP 0-3 enable per byte\;Bits 10:7: IPv4 DIP 0- 3 enable per byte\;Bit 11: IPv4 Protocol\;\;Inner IPv6 fields, subject to inner_header_enables:\;Bits 12: IPv6 enable bytes of SIP 0-7\;Bits 19:13 reserved\;Bits 27:20: IPv6 SIP 8-15 enable per byte\;Bits 28: IPv6 enable bytes of DIP 0-7\;Bits 35:29 reserved\;Bits 43:36: IPv6 DIP 8-15 enable per byte\;Bit 44: IPv6 Next Header\;Bit 45: IPv6 Flow label\;\;Inner TCP /UDP header fields, subject to inner_header_enables:\;Bit 46: TCP/UDP source port\;Bit 47: TCP/UDP destination port\;others: reserved" subnode="uint64" access="RW" offset="0x30.0" size="0x8.0" />
</node>

<node name="access_reg_summary_ctrl_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="id" descr="" subnode="enum_entry" enum="HGCR=0x7000,HCAP=0x7001,HPKT=0x7003,HTGT=0x7002,HOPF=0x7081,HMCB=0x7082,HMON=0x7084,HRWC=0x7088,HCTR=0x7083,HTAC=0x7085,HCOT=0x7087,MPAT=0x901a,MPAR=0x901b,MPAGR=0x9089,MOMTE=0x908d,MPSC=0x9080,MGPC=0x9081,MPRS=0x9083,MDRI=0x9084,MOGCR=0x9086,MRRR=0x9087,MAFCR=0x908a,MAFTI=0x908b,MAFRI=0x908c,MTPPPC=0x9090,MTPPTR=0x9091,MTPTPT=0x9092,MTPCPC=0x9093,MTPSPU=0x9094,MONI=0x90f4,SGCR=0x2000,SPAD=0x2002,SFDAT=0x2009,SFD=0x200a,SFN=0x200b,SFDD=0x2024,SFDB=0x2028,SPGT=0x200c,SMID=0x2007,SMPU=0x2006,SSPR=0x2008,SPMS=0x200d,SPVID=0x200e,SPVTR=0x201d,SPVM=0x200f,SPAFT=0x2010,SFGC=0x2011,SFTR=0x2012,SVFA=0x201c,SFDF=0x2013,SLCR=0x2015,SLCR_V2=0x2021,SFDT=0x2022,SLCOR=0x2016,SLECR=0x2017,SPMLR=0x2018,SVMLR=0x2019,SPVMLR=0x2020,SVPE=0x201e,SFMR=0x201f,SVER=0x2025,SPVC=0x2026,SPFSR=0x2023,SFFP=0x2029,SMPE=0x202b,SMPEB=0x202c,PMLP=0x5002,PMTU=0x5003,PTYS=0x5004,PPAD=0x5005,PAOS=0x5006,PPAOS=0x5040,PMAOS=0x5012,PFCC=0x5007,PPCNT=0x5008,PUDE=0x5009,PMPE=0x5024,PMPC=0x501f,PLIB=0x500a,PFSC=0x5043,PMMP=0x5044,PMCR=0x5045,PGMR=0x5039,PPTB=0x500b,PBMC=0x500c,PBSR=0x5038,PSPA=0x500d,PVLC=0x500f,PPSC=0x5011,PLBF=0x5015,PIFR=0x5016,PIPG=0x5017,PPLR=0x5018,PMPR=0x5013,PPLM=0x5023,SLTP=0x5027,SLRG=0x5028,SLRED=0x505a,PHBR=0x5034,PHCR=0x503a,PHRR=0x5035,PPTT=0x5036,PPRT=0x5037,PCMR=0x5041,PDDR=0x5031,PPBMP=0x5051,PPBMC=0x5052,PPBME=0x5053,PTER=0x5055,PEPC=0x5056,MFCR=0x9001,MFSC=0x9002,MFSM=0x9003,MFSL=0x9004,FORE=0x9007,MFNR=0x903b,MTCAP=0x9009,MTECR=0x9109,MTMP=0x900a,MTWE=0x900b,MTEWE=0x910b,MVCAP=0x902e,MVCR=0x900c,MSPS=0x900d,MCPP=0x900e,MTBR=0x900f,MFPA=0x9010,MFBA=0x9011,MFBE=0x9012,MFMC=0x9013,MCIA=0x9014,MCION=0x9052,MMIA=0x9016,MPGR=0x9019,MFM=0x901d,MHSR=0x901e,MJTAG=0x901f,MSGI=0x9021,MSCI=0x902a,MPCIR=0x905a,MRTC=0x902d,MGIR=0x9020,MGPIR=0x9100,MDIR=0x911a,MSSIR=0x9105,MHMPR=0x905d,MPFM=0x9022,MRSR=0x9023,MPGO=0x9052,MNVDA=0x9024,MNVDI=0x9025,MNVQC=0x9030,MNVIA=0x9033,MNVGC=0x9034,MNVGN=0x9035,MGNLE=0x9036,MTRC_CAP=0x9040,MTRC_CONF=0x9041,MTRC_STDB=0x9042,MTRC_CTRL=0x9043,MLCR=0x902b,MGCR=0x903a,MERR=0x903c,MPEIN=0x9050,MPCNT=0x9051,MTPPS=0x9053,MTPTP=0x9153,MTUTC=0x9055,MPIR=0x9059,MPECS=0x905b,MCQS=0x9060,MCQI=0x9061,MCC=0x9062,MCDA=0x9063,MQIS=0x9064,MIRC=0x9162,MCDD=0x905c,MDFCR=0x9101,MDCR=0x9111,MDDT=0x9160,MDRCR=0x9102,MDSR=0x9110,MFRL=0x9028,IGCR=0x3801,IDDD=0x3802,IDDDS=0x3803,IEDR=0x3804,IEDS=0x3805,IFBO=0x3810,IICR=0x3811,ICSR=0x38f0,ICAM=0x387f,SPZR=0x6002,IBFMR=0x6003,IBFMRC=0x6004,SBGCR=0xb000,SBPR=0xb001,SBCM=0xb002,SBPM=0xb003,SBMM=0xb004,SBME=0xb00e,SBSR=0xb005,SBIB=0xb006,SBDCC=0xb007,SBDCM=0xb008,SBDCR=0xb019,SBHBR=0xb00a,SBHRR=0xb00b,SBHBR_V2=0xb011,SBHRR_V2=0xb012,SBCTC=0xb00c,SBCTR=0xb00d,SBCTS=0xb00f,SBHPC=0xb013,SBSNT=0xb020,SBSNS=0xb021,SBSNTE=0xb022,SBCAM=0xb01f,MPGCR=0x8801,MPILM=0x8802,MPIBE=0x8803,MPNHLFE=0x8804,MPNHLFEB=0x8805,MPFT=0x8806,MPEPM=0x8810,MPQDR=0x8811,MPILEM=0x8812,MPELEM=0x8813,TNGCR=0xa001,TNPC=0xa020,TNGEE=0xa021,TNCR=0xa002,TNCR_V2=0xa004,TNUMT=0xa003,TNQCR=0xa010,TNQDR=0xa011,TNEEM=0xa012,TNDEM=0xa013,TNIFR=0xa014,TIGCR=0xa801,TIQCR=0xa810,TIQDR=0xa811,TIEEM=0xa812,TIDEM=0xa813,RCAP=0x8000,RGCR=0x8001,RITR=0x8002,RIGR=0x8003,RIGR_V2=0x8023,RTAR=0x8004,RECR=0x8005,RECR_V2=0x8025,RUFT=0x8006,RUHT=0x800c,RMFT=0x8007,RMFT_V2=0x8027,RMFTAD=0x8028,RRCR=0x800f,RATR=0x8008,RATRB=0x8024,RATRAD=0x8022,RTDP=0x8020,RIPS=0x8021,RDPM=0x8009,RICA=0x800a,RICNT=0x800b,RALTA=0x8010,RALST=0x8011,RALTB=0x8012,RALUE=0x8013,RAUHT=0x8014,RAUHTD=0x8018,RALEU=0x8015,RALBU=0x8016,RALCM=0x8017,RMID=0x8030,RMPE=0x8031,RMPU=0x8032,RMEIR=0x8033,REIV=0x8034,RXLTE=0x8050,RXLTM=0x8051,RXLTCC=0x8052,RLCME=0x8053,RLCMLE=0x8054,RLCMLD=0x8055,RARPC=0x8060,RARPR=0x8061,RARCL=0x8062,RARCTM=0x8063,RARFT=0x8064,RARLPGT=0x8065,RSNH=0x8066,RTCA=0x800d,RTPS=0x800e,CWGCR=0x2801,CWTP=0x2802,CWPP=0x2804,CWTPM=0x2803,CPQE=0x2806,CHLTR=0x2810,CHLTM=0x2811,CHLMM=0x2812,CNCT=0x2030,CPCS=0x2031,CPID=0x2032,CNMC=0x2033,QGCR=0x4000,QCAP=0x4001,QPTS=0x4002,QDPM=0x4003,QPDPM=0x4013,QEPM=0x4014,QPCR=0x4004,QPBR=0x400c,QETCR=0x4005,QEGCS=0x4006,QEEC=0x400d,QPDP=0x4007,QPDPC=0x4017,QPRT=0x4008,QSPTC=0x4009,QTCT=0x400a,QTCTM=0x401a,QSTCT=0x400b,QSPIP=0x400e,QSPCP=0x401e,QRWE=0x400f,QPEM=0x4010,QPDSM=0x4011,QPPM=0x4012,QSLL=0x4015,QHLL=0x4016,QCAM=0x4019,PGCR=0x3001,PPBT=0x3002,PEVPB=0x302e,PVGT=0x3009,PVBT=0x3003,PRBT=0x3013,PEMRBT=0x3014,PERB=0x3040,PERBRG=0x3041,PERBEG=0x3042,PACL=0x3004,PAGT=0x3005,PTAR=0x3006,PERAR=0x3026,PERCR=0x302a,PERERP=0x302b,PERD=0x302c,PTCE=0x3007,PTCE_V2=0x3017,PTCE_V3=0x3027,PTCEAD=0x3028,PEFA=0x300f,PEFAAD=0x3029,PRCR=0x300d,PPRR=0x3008,PFCA=0x300a,PFCNT=0x300b,PPBS=0x300c,PUET=0x300e,PPBMI=0x3012,PECB=0x3010,PERPT=0x3021,PEABFE=0x3022,PEAPBL=0x3024,PEAPBM=0x3025,PEAPS=0x302d,PECNRE=0x3030,PECNRR=0x3031,PECNEE=0x3032,PECNER=0x3033,PECKC=0x3034,XGCR=0x7801,XLTQ=0x7802,XMDR=0x7803,XLKBU=0x7804,XRMT=0x7810,XRALTA=0x7811,XRALST=0x7812,XRALTB=0x7813" offset="0x0.0" size="0x4.0" />
</node>

<node name="access_reg_summary_ext" descr="" attr_is_union="1" size="0x440" >
	<field name="hgcr" descr="" subnode="hgcr_ext" capability="0" offset="0x0.0" selected_by="HGCR" size="0x8" />
	<field name="hcap" descr="" subnode="hcap_ext" capability="0" offset="0x0.0" selected_by="HCAP" size="0x14" />
	<field name="hpkt" descr="" subnode="hpkt_ext" capability="0" offset="0x0.0" selected_by="HPKT" size="0x10" />
	<field name="htgt" descr="" subnode="htgt_ext" capability="0" offset="0x0.0" selected_by="HTGT" size="0x44" />
	<field name="hopf" descr="" subnode="hopf_ext" capability="0" offset="0x0.0" selected_by="HOPF" size="0x14" />
	<field name="hmcb" descr="" subnode="hmcb_ext" capability="0" offset="0x0.0" selected_by="HMCB" size="0x10" />
	<field name="hmon" descr="" subnode="hmon_ext" capability="0" offset="0x0.0" selected_by="HMON" size="0x220" />
	<field name="hrwc" descr="" subnode="hrwc_ext" capability="0" offset="0x0.0" selected_by="HRWC" size="0x220" />
	<field name="hctr" descr="" subnode="hctr_ext" capability="0" offset="0x0.0" selected_by="HCTR" size="0x10" />
	<field name="htac" descr="" subnode="htac_ext" capability="0" offset="0x0.0" selected_by="HTAC" size="0x30" />
	<field name="hcot" descr="" subnode="hcot_ext" capability="0" offset="0x0.0" selected_by="HCOT" size="0x30" />
	<field name="mpat_reg" descr="" subnode="mpat_reg_ext" capability="0" offset="0x0.0" selected_by="MPAT" size="0x70" />
	<field name="mpar" descr="" subnode="mpar_ext" capability="0" offset="0x0.0" selected_by="MPAR" size="0xc" />
	<field name="mpagr" descr="" subnode="mpagr_ext" capability="0" offset="0x0.0" selected_by="MPAGR" size="0xc" />
	<field name="momte" descr="" subnode="momte_ext" capability="0" offset="0x0.0" selected_by="MOMTE" size="0x10" />
	<field name="mpsc" descr="" subnode="mpsc_ext" capability="0" offset="0x0.0" selected_by="MPSC" size="0x14" />
	<field name="mgpc" descr="" subnode="mgpc_ext" capability="0" offset="0x0.0" selected_by="MGPC" size="0x18" />
	<field name="mprs" descr="" subnode="mprs_ext" capability="0" offset="0x0.0" selected_by="MPRS" size="0x14" />
	<field name="mdri" descr="" subnode="mdri_ext" capability="0" offset="0x0.0" selected_by="MDRI" size="0x120" />
	<field name="mogcr" descr="" subnode="mogcr_ext" capability="0" offset="0x0.0" selected_by="MOGCR" size="0x20" />
	<field name="mrrr" descr="" subnode="mrrr_ext" capability="0" offset="0x0.0" selected_by="MRRR" size="0x8" />
	<field name="mafcr" descr="" subnode="mafcr_ext" capability="0" offset="0x0.0" selected_by="MAFCR" size="0x8" />
	<field name="mafti" descr="" subnode="mafti_ext" capability="0" offset="0x0.0" selected_by="MAFTI" size="0x410" />
	<field name="mafri" descr="" subnode="mafri_ext" capability="0" offset="0x0.0" selected_by="MAFRI" size="0x410" />
	<field name="mtpppc" descr="" subnode="mtpppc_ext" capability="0" offset="0x0.0" selected_by="MTPPPC" size="0x10" />
	<field name="mtpptr" descr="" subnode="mtpptr_ext" capability="0" offset="0x0.0" selected_by="MTPPTR" size="0x50" />
	<field name="mtptpt" descr="" subnode="mtptpt_ext" capability="0" offset="0x0.0" selected_by="MTPTPT" size="0x8" />
	<field name="mtpcpc" descr="" subnode="mtpcpc_ext" capability="0" offset="0x0.0" selected_by="MTPCPC" size="0x28" />
	<field name="mtpspu" descr="" subnode="mtpspu_ext" capability="0" offset="0x0.0" selected_by="MTPSPU" size="0x8" />
	<field name="moni" descr="" subnode="moni_ext" capability="0" offset="0x0.0" selected_by="MONI" size="0x8" />
	<field name="sgcr" descr="" subnode="sgcr_ext" capability="0" offset="0x0.0" selected_by="SGCR" size="0x50" />
	<field name="spad" descr="" subnode="spad_ext" capability="0" offset="0x0.0" selected_by="SPAD" size="0x10" />
	<field name="sfdat" descr="" subnode="sfdat_ext" capability="0" offset="0x0.0" selected_by="SFDAT" size="0x8" />
	<field name="sfd" descr="" subnode="sfd_ext" capability="0" offset="0x0.0" selected_by="SFD" size="0x410" />
	<field name="sfn" descr="" subnode="sfn_ext" capability="0" offset="0x0.0" selected_by="SFN" size="0x410" />
	<field name="sfdd" descr="" subnode="sfdd_ext" capability="0" offset="0x0.0" selected_by="SFDD" size="0x420" />
	<field name="sfdb" descr="" subnode="sfdb_ext" capability="0" offset="0x0.0" selected_by="SFDB" size="0x48" />
	<field name="spgt" descr="" subnode="spgt_ext" capability="0" offset="0x0.0" selected_by="SPGT" size="0x240" />
	<field name="smid" descr="" subnode="smid_ext" capability="0" offset="0x0.0" selected_by="SMID" size="0x240" />
	<field name="smpu" descr="" subnode="smpu_ext" capability="0" offset="0x0.0" selected_by="SMPU" size="0x410" />
	<field name="sspr" descr="" subnode="sspr_ext" capability="0" offset="0x0.0" selected_by="SSPR" size="0x8" />
	<field name="spms" descr="" subnode="spms_ext" capability="0" offset="0x0.0" selected_by="SPMS" size="0x404" />
	<field name="spvid" descr="" subnode="spvid_ext" capability="0" offset="0x0.0" selected_by="SPVID" size="0x8" />
	<field name="spvtr" descr="" subnode="spvtr_ext" capability="0" offset="0x0.0" selected_by="SPVTR" size="0x10" />
	<field name="spvm" descr="" subnode="spvm_ext" capability="0" offset="0x0.0" selected_by="SPVM" size="0x400" />
	<field name="spaft" descr="" subnode="spaft_ext" capability="0" offset="0x0.0" selected_by="SPAFT" size="0x8" />
	<field name="sfgc" descr="" subnode="sfgc_ext" capability="0" offset="0x0.0" selected_by="SFGC" size="0x14" />
	<field name="sftr" descr="" subnode="sftr_ext" capability="0" offset="0x0.0" selected_by="SFTR" size="0x240" />
	<field name="svfa" descr="" subnode="svfa_ext" capability="0" offset="0x0.0" selected_by="SVFA" size="0x18" />
	<field name="sfdf" descr="" subnode="sfdf_ext" capability="0" offset="0x0.0" selected_by="SFDF" size="0x14" />
	<field name="slcr_switch_lag" descr="" subnode="slcr_switch_lag_ext" capability="0" offset="0x0.0" selected_by="SLCR" size="0x10" />
	<field name="SLCRV2" descr="" subnode="SLCRV2_ext" capability="0" offset="0x0.0" selected_by="SLCR_V2" size="0x38" />
	<field name="sfdt" descr="" subnode="sfdt_ext" capability="0" offset="0x0.0" selected_by="SFDT" size="0x2e0" />
	<field name="slcor" descr="" subnode="slcor_ext" capability="0" offset="0x0.0" selected_by="SLCOR" size="0x10" />
	<field name="slecr" descr="" subnode="slecr_ext" capability="0" offset="0x0.0" selected_by="SLECR" size="0x10" />
	<field name="spmlr" descr="" subnode="spmlr_ext" capability="0" offset="0x0.0" selected_by="SPMLR" size="0x8" />
	<field name="svmlr" descr="" subnode="svmlr_ext" capability="0" offset="0x0.0" selected_by="SVMLR" size="0x8" />
	<field name="spvmlr" descr="" subnode="spvmlr_ext" capability="0" offset="0x0.0" selected_by="SPVMLR" size="0x400" />
	<field name="svpe" descr="" subnode="svpe_ext" capability="0" offset="0x0.0" selected_by="SVPE" size="0x4" />
	<field name="sfmr" descr="" subnode="sfmr_ext" capability="0" offset="0x0.0" selected_by="SFMR" size="0x2c" />
	<field name="sver" descr="" subnode="sver_ext" capability="0" offset="0x0.0" selected_by="SVER" size="0x10" />
	<field name="spvc" descr="" subnode="spvc_ext" capability="0" offset="0x0.0" selected_by="SPVC" size="0xc" />
	<field name="spfsr" descr="" subnode="spfsr_ext" capability="0" offset="0x0.0" selected_by="SPFSR" size="0x8" />
	<field name="sffp" descr="" subnode="sffp_ext" capability="0" offset="0x0.0" selected_by="SFFP" size="0x8" />
	<field name="smpe" descr="" subnode="smpe_ext" capability="0" offset="0x0.0" selected_by="SMPE" size="0xc" />
	<field name="smpeb" descr="" subnode="smpeb_ext" capability="0" offset="0x0.0" selected_by="SMPEB" size="0x420" />
	<field name="pmlp_reg" descr="" subnode="pmlp_reg_ext" capability="0" offset="0x0.0" selected_by="PMLP" size="0x40" />
	<field name="pmtu_reg" descr="" subnode="pmtu_reg_ext" capability="0" offset="0x0.0" selected_by="PMTU" size="0x10" />
	<field name="ptys_reg" descr="" subnode="ptys_reg_ext" capability="0" offset="0x0.0" selected_by="PTYS" size="0x40" />
	<field name="ppad_reg" descr="" subnode="ppad_reg_ext" capability="0" offset="0x0.0" selected_by="PPAD" size="0x10" />
	<field name="paos_reg" descr="" subnode="paos_reg_ext" capability="0" offset="0x0.0" selected_by="PAOS" size="0x10" />
	<field name="ppaos_reg" descr="" subnode="ppaos_reg_ext" capability="0" offset="0x0.0" selected_by="PPAOS" size="0x10" />
	<field name="pmaos_reg" descr="" subnode="pmaos_reg_ext" capability="0" offset="0x0.0" selected_by="PMAOS" size="0x10" />
	<field name="pfcc_reg" descr="" subnode="pfcc_reg_ext" capability="0" offset="0x0.0" selected_by="PFCC" size="0x20" />
	<field name="ppcnt_reg" descr="" subnode="ppcnt_reg_ext" capability="0" offset="0x0.0" selected_by="PPCNT" size="0x100" />
	<field name="pude_reg" descr="" subnode="pude_reg_ext" capability="0" offset="0x0.0" selected_by="PUDE" size="0x10" />
	<field name="pmpe_reg" descr="" subnode="pmpe_reg_ext" capability="0" offset="0x0.0" selected_by="PMPE" size="0x10" />
	<field name="pmpc_reg" descr="" subnode="pmpc_reg_ext" capability="0" offset="0x0.0" selected_by="PMPC" size="0x20" />
	<field name="plib_reg" descr="" subnode="plib_reg_ext" capability="0" offset="0x0.0" selected_by="PLIB" size="0x10" />
	<field name="pfsc_reg" descr="" subnode="pfsc_reg_ext" capability="0" offset="0x0.0" selected_by="PFSC" size="0x10" />
	<field name="pmmp_reg" descr="" subnode="pmmp_reg_ext" capability="0" offset="0x0.0" selected_by="PMMP" size="0x28" />
	<field name="pmcr_reg" descr="" subnode="pmcr_reg_ext" capability="0" offset="0x0.0" selected_by="PMCR" size="0x1c" />
	<field name="pgmr" descr="" subnode="pgmr_ext" capability="0" offset="0x0.0" selected_by="PGMR" size="0x18" />
	<field name="pptb_reg" descr="" subnode="pptb_reg_ext" capability="0" offset="0x0.0" selected_by="PPTB" size="0x10" />
	<field name="pbmc_reg" descr="" subnode="pbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PBMC" size="0x6c" />
	<field name="pbsr_reg" descr="" subnode="pbsr_reg_ext" capability="0" offset="0x0.0" selected_by="PBSR" size="0x64" />
	<field name="pspa_reg" descr="" subnode="pspa_reg_ext" capability="0" offset="0x0.0" selected_by="PSPA" size="0x8" />
	<field name="pvlc_reg" descr="" subnode="pvlc_reg_ext" capability="0" offset="0x0.0" selected_by="PVLC" size="0x10" />
	<field name="ppsc_reg" descr="" subnode="ppsc_reg_ext" capability="0" offset="0x0.0" selected_by="PPSC" size="0x30" />
	<field name="plbf_reg" descr="" subnode="plbf_reg_ext" capability="0" offset="0x0.0" selected_by="PLBF" size="0x8" />
	<field name="pifr_reg" descr="" subnode="pifr_reg_ext" capability="0" offset="0x0.0" selected_by="PIFR" size="0x60" />
	<field name="pipg_reg" descr="" subnode="pipg_reg_ext" capability="0" offset="0x0.0" selected_by="PIPG" size="0x8" />
	<field name="pplr_reg" descr="" subnode="pplr_reg_ext" capability="0" offset="0x0.0" selected_by="PPLR" size="0x8" />
	<field name="pmpr_reg" descr="" subnode="pmpr_reg_ext" capability="0" offset="0x0.0" selected_by="PMPR" size="0x10" />
	<field name="pplm_reg" descr="" subnode="pplm_reg_ext" capability="0" offset="0x0.0" selected_by="PPLM" size="0x40" />
	<field name="sltp_reg" descr="" subnode="sltp_reg_ext" capability="0" offset="0x0.0" selected_by="SLTP" size="0x1c" />
	<field name="slrg_reg" descr="" subnode="slrg_reg_ext" capability="0" offset="0x0.0" selected_by="SLRG" size="0x28" />
	<field name="slred_reg" descr="" subnode="slred_reg_ext" capability="0" offset="0x0.0" selected_by="SLRED" size="0xa0" />
	<field name="phbr_binding_reg" descr="" subnode="phbr_binding_reg_ext" capability="0" offset="0x0.0" selected_by="PHBR" size="0x1c" />
	<field name="phcr" descr="" subnode="phcr_ext" capability="0" offset="0x0.0" selected_by="PHCR" size="0x4c" />
	<field name="phrr_reg" descr="" subnode="phrr_reg_ext" capability="0" offset="0x0.0" selected_by="PHRR" size="0x60" />
	<field name="pptt_reg" descr="" subnode="pptt_reg_ext" capability="0" offset="0x0.0" selected_by="PPTT" size="0x1c" />
	<field name="pprt_reg" descr="" subnode="pprt_reg_ext" capability="0" offset="0x0.0" selected_by="PPRT" size="0x20" />
	<field name="pcmr_reg" descr="" subnode="pcmr_reg_ext" capability="0" offset="0x0.0" selected_by="PCMR" size="0xc" />
	<field name="pddr_reg" descr="" subnode="pddr_reg_ext" capability="0" offset="0x0.0" selected_by="PDDR" size="0x100" />
	<field name="ppbmp_reg" descr="" subnode="ppbmp_reg_ext" capability="0" offset="0x0.0" selected_by="PPBMP" size="0x30" />
	<field name="ppbmc_reg" descr="" subnode="ppbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PPBMC" size="0x10" />
	<field name="ppbme_reg" descr="" subnode="ppbme_reg_ext" capability="0" offset="0x0.0" selected_by="PPBME" size="0x10" />
	<field name="pter_reg" descr="" subnode="pter_reg_ext" capability="0" offset="0x0.0" selected_by="PTER" size="0x20" />
	<field name="pepc_reg" descr="" subnode="pepc_reg_ext" capability="0" offset="0x0.0" selected_by="PEPC" size="0x10" />
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
	<field name="mcqi_reg" descr="" subnode="mcqi_reg_ext" capability="0" offset="0x0.0" selected_by="MCQI" size="0x1c" />
	<field name="mcc_reg" descr="" subnode="mcc_reg_ext" capability="0" offset="0x0.0" selected_by="MCC" size="0x20" />
	<field name="mcda_reg" descr="" subnode="mcda_reg_ext" capability="0" offset="0x0.0" selected_by="MCDA" size="0x90" />
	<field name="mqis_reg" descr="" subnode="mqis_reg_ext" capability="0" offset="0x0.0" selected_by="MQIS" size="0x18" />
	<field name="mirc_reg" descr="" subnode="mirc_reg_ext" capability="0" offset="0x0.0" selected_by="MIRC" size="0x8" />
	<field name="mcdd_reg" descr="" subnode="mcdd_reg_ext" capability="0" offset="0x0.0" selected_by="MCDD" size="0x20" />
	<field name="mdfcr_reg" descr="" subnode="mdfcr_reg_ext" capability="0" offset="0x0.0" selected_by="MDFCR" size="0x60" />
	<field name="mdcr" descr="" subnode="mdcr_ext" capability="0" offset="0x0.0" selected_by="MDCR" size="0x60" />
	<field name="mddt_reg" descr="" subnode="mddt_reg_ext" capability="0" offset="0x0.0" selected_by="MDDT" size="0x110" />
	<field name="mdrcr" descr="" subnode="mdrcr_ext" capability="0" offset="0x0.0" selected_by="MDRCR" size="0x30" />
	<field name="mdsr_reg" descr="" subnode="mdsr_reg_ext" capability="0" offset="0x0.0" selected_by="MDSR" size="0x30" />
	<field name="mfrl_reg" descr="" subnode="mfrl_reg_ext" capability="0" offset="0x0.0" selected_by="MFRL" size="0x8" />
	<field name="igcr" descr="" subnode="igcr_ext" capability="0" offset="0x0.0" selected_by="IGCR" size="0x10" />
	<field name="iddd" descr="" subnode="iddd_ext" capability="0" offset="0x0.0" selected_by="IDDD" size="0x8" />
	<field name="iddds" descr="" subnode="iddds_ext" capability="0" offset="0x0.0" selected_by="IDDDS" size="0x440" />
	<field name="iedr" descr="" subnode="iedr_ext" capability="0" offset="0x0.0" selected_by="IEDR" size="0x210" />
	<field name="ieds" descr="" subnode="ieds_ext" capability="0" offset="0x0.0" selected_by="IEDS" size="0x8" />
	<field name="ifbo" descr="" subnode="ifbo_ext" capability="0" offset="0x0.0" selected_by="IFBO" size="0x28" />
	<field name="iicr" descr="" subnode="iicr_ext" capability="0" offset="0x0.0" selected_by="IICR" size="0x24" />
	<field name="icsr" descr="" subnode="icsr_ext" capability="0" offset="0x0.0" selected_by="ICSR" size="0x410" />
	<field name="icam_reg" descr="" subnode="icam_reg_ext" capability="0" offset="0x0.0" selected_by="ICAM" size="0x38" />
	<field name="spzr" descr="" subnode="spzr_ext" capability="0" offset="0x0.0" selected_by="SPZR" size="0x100" />
	<field name="ibfmr" descr="" subnode="ibfmr_ext" capability="0" offset="0x0.0" selected_by="IBFMR" size="0x10" />
	<field name="ibfmrc" descr="" subnode="ibfmrc_ext" capability="0" offset="0x0.0" selected_by="IBFMRC" size="0x4" />
	<field name="sbgcr" descr="" subnode="sbgcr_ext" capability="0" offset="0x0.0" selected_by="SBGCR" size="0x4" />
	<field name="sbpr" descr="" subnode="sbpr_ext" capability="0" offset="0x0.0" selected_by="SBPR" size="0x18" />
	<field name="sbcm" descr="" subnode="sbcm_ext" capability="0" offset="0x0.0" selected_by="SBCM" size="0x28" />
	<field name="sbpm" descr="" subnode="sbpm_ext" capability="0" offset="0x0.0" selected_by="SBPM" size="0x20" />
	<field name="sbmm" descr="" subnode="sbmm_ext" capability="0" offset="0x0.0" selected_by="SBMM" size="0x28" />
	<field name="sbme" descr="" subnode="sbme_ext" capability="0" offset="0x0.0" selected_by="SBME" size="0x28" />
	<field name="sbsr" descr="" subnode="sbsr_ext" capability="0" offset="0x0.0" selected_by="SBSR" size="0x41c" />
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
	<field name="mpgcr" descr="" subnode="mpgcr_ext" capability="0" offset="0x0.0" selected_by="MPGCR" size="0x24" />
	<field name="mpilm" descr="" subnode="mpilm_ext" capability="0" offset="0x0.0" selected_by="MPILM" size="0x18" />
	<field name="mpibe" descr="" subnode="mpibe_ext" capability="0" offset="0x0.0" selected_by="MPIBE" size="0x28" />
	<field name="mpnhlfe" descr="" subnode="mpnhlfe_ext" capability="0" offset="0x0.0" selected_by="MPNHLFE" size="0x4c" />
	<field name="mpnhlfeb" descr="" subnode="mpnhlfeb_ext" capability="0" offset="0x0.0" selected_by="MPNHLFEB" size="0x420" />
	<field name="mpft" descr="" subnode="mpft_ext" capability="0" offset="0x0.0" selected_by="MPFT" size="0x8" />
	<field name="mpepm" descr="" subnode="mpepm_ext" capability="0" offset="0x0.0" selected_by="MPEPM" size="0x14" />
	<field name="mpqdr" descr="" subnode="mpqdr_ext" capability="0" offset="0x0.0" selected_by="MPQDR" size="0x8" />
	<field name="mpilem" descr="" subnode="mpilem_ext" capability="0" offset="0x0.0" selected_by="MPILEM" size="0x8" />
	<field name="mpelem" descr="" subnode="mpelem_ext" capability="0" offset="0x0.0" selected_by="MPELEM" size="0xc" />
	<field name="tngcr" descr="" subnode="tngcr_ext" capability="0" offset="0x0.0" selected_by="TNGCR" size="0x44" />
	<field name="tnpc" descr="" subnode="tnpc_ext" capability="0" offset="0x0.0" selected_by="TNPC" size="0x1c" />
	<field name="tngee" descr="" subnode="tngee_ext" capability="0" offset="0x0.0" selected_by="TNGEE" size="0x60" />
	<field name="tncr" descr="" subnode="tncr_ext" capability="0" offset="0x0.0" selected_by="TNCR" size="0x30" />
	<field name="tncr_v2" descr="" subnode="tncr_v2_ext" capability="0" offset="0x0.0" selected_by="TNCR_V2" size="0x38" />
	<field name="tnumt" descr="" subnode="tnumt_ext" capability="0" offset="0x0.0" selected_by="TNUMT" size="0x20" />
	<field name="tnqcr" descr="" subnode="tnqcr_ext" capability="0" offset="0x0.0" selected_by="TNQCR" size="0xc" />
	<field name="tnqdr" descr="" subnode="tnqdr_ext" capability="0" offset="0x0.0" selected_by="TNQDR" size="0x8" />
	<field name="tneem" descr="" subnode="tneem_ext" capability="0" offset="0x0.0" selected_by="TNEEM" size="0xc" />
	<field name="tndem" descr="" subnode="tndem_ext" capability="0" offset="0x0.0" selected_by="TNDEM" size="0xc" />
	<field name="tnifr" descr="" subnode="tnifr_ext" capability="0" offset="0x0.0" selected_by="TNIFR" size="0x60" />
	<field name="tigcr" descr="" subnode="tigcr_ext" capability="0" offset="0x0.0" selected_by="TIGCR" size="0x18" />
	<field name="tiqcr" descr="" subnode="tiqcr_ext" capability="0" offset="0x0.0" selected_by="TIQCR" size="0xc" />
	<field name="tiqdr" descr="" subnode="tiqdr_ext" capability="0" offset="0x0.0" selected_by="TIQDR" size="0x8" />
	<field name="tieem" descr="" subnode="tieem_ext" capability="0" offset="0x0.0" selected_by="TIEEM" size="0xc" />
	<field name="tidem" descr="" subnode="tidem_ext" capability="0" offset="0x0.0" selected_by="TIDEM" size="0xc" />
	<field name="rcap" descr="" subnode="rcap_ext" capability="0" offset="0x0.0" selected_by="RCAP" size="0x8" />
	<field name="rgcr" descr="" subnode="rgcr_ext" capability="0" offset="0x0.0" selected_by="RGCR" size="0x34" />
	<field name="ritr" descr="" subnode="ritr_ext" capability="0" offset="0x0.0" selected_by="RITR" size="0x40" />
	<field name="rigr" descr="" subnode="rigr_ext" capability="0" offset="0x0.0" selected_by="RIGR" size="0x3fc" />
	<field name="rigr_v2" descr="" subnode="rigr_v2_ext" capability="0" offset="0x0.0" selected_by="RIGR_V2" size="0xb0" />
	<field name="rtar_tcam" descr="" subnode="rtar_tcam_ext" capability="0" offset="0x0.0" selected_by="RTAR" size="0x20" />
	<field name="recr" descr="" subnode="recr_ext" capability="0" offset="0x0.0" selected_by="RECR" size="0x10" />
	<field name="recr_v2" descr="" subnode="recr_v2_ext" capability="0" offset="0x0.0" selected_by="RECR_V2" size="0x38" />
	<field name="ruft" descr="" subnode="ruft_ext" capability="0" offset="0x0.0" selected_by="RUFT" size="0x78" />
	<field name="ruht" descr="" subnode="ruht_ext" capability="0" offset="0x0.0" selected_by="RUHT" size="0x78" />
	<field name="rmft" descr="" subnode="rmft_ext" capability="0" offset="0x0.0" selected_by="RMFT" size="0x90" />
	<field name="rmft_v2" descr="" subnode="rmft_v2_ext" capability="0" offset="0x0.0" selected_by="RMFT_V2" size="0x174" />
	<field name="rmftad" descr="" subnode="rmftad_ext" capability="0" offset="0x0.0" selected_by="RMFTAD" size="0x220" />
	<field name="rrcr" descr="" subnode="rrcr_ext" capability="0" offset="0x0.0" selected_by="RRCR" size="0x24" />
	<field name="ratr" descr="" subnode="ratr_ext" capability="0" offset="0x0.0" selected_by="RATR" size="0x2c" />
	<field name="ratrb" descr="" subnode="ratrb_ext" capability="0" offset="0x0.0" selected_by="RATRB" size="0x420" />
	<field name="ratrad" descr="" subnode="ratrad_ext" capability="0" offset="0x0.0" selected_by="RATRAD" size="0x210" />
	<field name="rtdp" descr="" subnode="rtdp_ext" capability="0" offset="0x0.0" selected_by="RTDP" size="0x44" />
	<field name="rips_ip" descr="" subnode="rips_ip_ext" capability="0" offset="0x0.0" selected_by="RIPS" size="0x14" />
	<field name="rdpm" descr="" subnode="rdpm_ext" capability="0" offset="0x0.0" selected_by="RDPM" size="0x40" />
	<field name="rica" descr="" subnode="rica_ext" capability="0" offset="0x0.0" selected_by="RICA" size="0x10" />
	<field name="ricnt_inter" descr="" subnode="ricnt_inter_ext" capability="0" offset="0x0.0" selected_by="RICNT" size="0x100" />
	<field name="ralta" descr="" subnode="ralta_ext" capability="0" offset="0x0.0" selected_by="RALTA" size="0x4" />
	<field name="ralst" descr="" subnode="ralst_ext" capability="0" offset="0x0.0" selected_by="RALST" size="0x104" />
	<field name="raltb" descr="" subnode="raltb_ext" capability="0" offset="0x0.0" selected_by="RALTB" size="0x4" />
	<field name="ralue" descr="" subnode="ralue_ext" capability="0" offset="0x0.0" selected_by="RALUE" size="0x38" />
	<field name="rauht_lpm_unicast" descr="" subnode="rauht_lpm_unicast_ext" capability="0" offset="0x0.0" selected_by="RAUHT" size="0x74" />
	<field name="rauhtd" descr="" subnode="rauhtd_ext" capability="0" offset="0x0.0" selected_by="RAUHTD" size="0x20" />
	<field name="raleu" descr="" subnode="raleu_ext" capability="0" offset="0x0.0" selected_by="RALEU" size="0x2c" />
	<field name="ralbu" descr="" subnode="ralbu_ext" capability="0" offset="0x0.0" selected_by="RALBU" size="0x20" />
	<field name="ralcm" descr="" subnode="ralcm_ext" capability="0" offset="0x0.0" selected_by="RALCM" size="0x4" />
	<field name="rmid" descr="" subnode="rmid_ext" capability="0" offset="0x0.0" selected_by="RMID" size="0x40" />
	<field name="rmpe" descr="" subnode="rmpe_ext" capability="0" offset="0x0.0" selected_by="RMPE" size="0xc" />
	<field name="rmpu" descr="" subnode="rmpu_ext" capability="0" offset="0x0.0" selected_by="RMPU" size="0x110" />
	<field name="rmeir" descr="" subnode="rmeir_ext" capability="0" offset="0x0.0" selected_by="RMEIR" size="0x210" />
	<field name="reiv" descr="" subnode="reiv_ext" capability="0" offset="0x0.0" selected_by="REIV" size="0x420" />
	<field name="rxlte" descr="" subnode="rxlte_ext" capability="0" offset="0x0.0" selected_by="RXLTE" size="0xc" />
	<field name="rxltm" descr="" subnode="rxltm_ext" capability="0" offset="0x0.0" selected_by="RXLTM" size="0x14" />
	<field name="rxltcc" descr="" subnode="rxltcc_ext" capability="0" offset="0x0.0" selected_by="RXLTCC" size="0x68" />
	<field name="rlcme" descr="" subnode="rlcme_ext" capability="0" offset="0x0.0" selected_by="RLCME" size="0x3c" />
	<field name="rlcmle" descr="" subnode="rlcmle_ext" capability="0" offset="0x0.0" selected_by="RLCMLE" size="0x58" />
	<field name="rlcmld" descr="" subnode="rlcmld_ext" capability="0" offset="0x0.0" selected_by="RLCMLD" size="0x30" />
	<field name="rarpc" descr="" subnode="rarpc_ext" capability="0" offset="0x0.0" selected_by="RARPC" size="0x30" />
	<field name="rarpr" descr="" subnode="rarpr_ext" capability="0" offset="0x0.0" selected_by="RARPR" size="0x10" />
	<field name="rarcl" descr="" subnode="rarcl_ext" capability="0" offset="0x0.0" selected_by="RARCL" size="0x2c" />
	<field name="rarctm" descr="" subnode="rarctm_ext" capability="0" offset="0x0.0" selected_by="RARCTM" size="0x8" />
	<field name="rarft" descr="" subnode="rarft_ext" capability="0" offset="0x0.0" selected_by="RARFT" size="0xc" />
	<field name="rarlpgt" descr="" subnode="rarlpgt_ext" capability="0" offset="0x0.0" selected_by="RARLPGT" size="0x20" />
	<field name="rsnh" descr="" subnode="rsnh_ext" capability="0" offset="0x0.0" selected_by="RSNH" size="0x10" />
	<field name="rtca" descr="" subnode="rtca_ext" capability="0" offset="0x0.0" selected_by="RTCA" size="0x14" />
	<field name="rtps" descr="" subnode="rtps_ext" capability="0" offset="0x0.0" selected_by="RTPS" size="0x8" />
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
	<field name="qgcr" descr="" subnode="qgcr_ext" capability="0" offset="0x0.0" selected_by="QGCR" size="0x8" />
	<field name="qcap" descr="" subnode="qcap_ext" capability="0" offset="0x0.0" selected_by="QCAP" size="0x14" />
	<field name="qpts" descr="" subnode="qpts_ext" capability="0" offset="0x0.0" selected_by="QPTS" size="0x8" />
	<field name="qdpm" descr="" subnode="qdpm_ext" capability="0" offset="0x0.0" selected_by="QDPM" size="0x40" />
	<field name="qpdpm" descr="" subnode="qpdpm_ext" capability="0" offset="0x0.0" selected_by="QPDPM" size="0x84" />
	<field name="qepm" descr="" subnode="qepm_ext" capability="0" offset="0x0.0" selected_by="QEPM" size="0x14" />
	<field name="qpcr" descr="" subnode="qpcr_ext" capability="0" offset="0x0.0" selected_by="QPCR" size="0x28" />
	<field name="qpbr" descr="" subnode="qpbr_ext" capability="0" offset="0x0.0" selected_by="QPBR" size="0x10" />
	<field name="qetcr" descr="" subnode="qetcr_ext" capability="0" offset="0x0.0" selected_by="QETCR" size="0x50" />
	<field name="qegcs" descr="" subnode="qegcs_ext" capability="0" offset="0x0.0" selected_by="QEGCS" size="0x10" />
	<field name="qeec" descr="" subnode="qeec_ext" capability="0" offset="0x0.0" selected_by="QEEC" size="0x20" />
	<field name="qpdp" descr="" subnode="qpdp_ext" capability="0" offset="0x0.0" selected_by="QPDP" size="0x8" />
	<field name="qpdpc" descr="" subnode="qpdpc_ext" capability="0" offset="0x0.0" selected_by="QPDPC" size="0x8" />
	<field name="qprt" descr="" subnode="qprt_ext" capability="0" offset="0x0.0" selected_by="QPRT" size="0x8" />
	<field name="qsptc" descr="" subnode="qsptc_ext" capability="0" offset="0x0.0" selected_by="QSPTC" size="0x8" />
	<field name="qtct" descr="" subnode="qtct_ext" capability="0" offset="0x0.0" selected_by="QTCT" size="0x8" />
	<field name="qtctm" descr="" subnode="qtctm_ext" capability="0" offset="0x0.0" selected_by="QTCTM" size="0x8" />
	<field name="qstct" descr="" subnode="qstct_ext" capability="0" offset="0x0.0" selected_by="QSTCT" size="0x10" />
	<field name="qspip" descr="" subnode="qspip_ext" capability="0" offset="0x0.0" selected_by="QSPIP" size="0x8" />
	<field name="qspcp" descr="" subnode="qspcp_ext" capability="0" offset="0x0.0" selected_by="QSPCP" size="0xc" />
	<field name="qrwe" descr="" subnode="qrwe_ext" capability="0" offset="0x0.0" selected_by="QRWE" size="0x8" />
	<field name="qpem" descr="" subnode="qpem_ext" capability="0" offset="0x0.0" selected_by="QPEM" size="0x104" />
	<field name="qpdsm" descr="" subnode="qpdsm_ext" capability="0" offset="0x0.0" selected_by="QPDSM" size="0x44" />
	<field name="qppm" descr="" subnode="qppm_ext" capability="0" offset="0x0.0" selected_by="QPPM" size="0x44" />
	<field name="qsll" descr="" subnode="qsll_ext" capability="0" offset="0x0.0" selected_by="QSLL" size="0x8" />
	<field name="qhll" descr="" subnode="qhll_ext" capability="0" offset="0x0.0" selected_by="QHLL" size="0xc" />
	<field name="qcam" descr="" subnode="qcam_ext" capability="0" offset="0x0.0" selected_by="QCAM" size="0x48" />
	<field name="pgcr" descr="" subnode="pgcr_ext" capability="0" offset="0x0.0" selected_by="PGCR" size="0x20" />
	<field name="ppbt" descr="" subnode="ppbt_ext" capability="0" offset="0x0.0" selected_by="PPBT" size="0x14" />
	<field name="pevpb" descr="" subnode="pevpb_ext" capability="0" offset="0x0.0" selected_by="PEVPB" size="0x8" />
	<field name="pvgt" descr="" subnode="pvgt_ext" capability="0" offset="0x0.0" selected_by="PVGT" size="0x8" />
	<field name="pvbt" descr="" subnode="pvbt_ext" capability="0" offset="0x0.0" selected_by="PVBT" size="0x14" />
	<field name="prbt" descr="" subnode="prbt_ext" capability="0" offset="0x0.0" selected_by="PRBT" size="0x14" />
	<field name="pemrbt" descr="" subnode="pemrbt_ext" capability="0" offset="0x0.0" selected_by="PEMRBT" size="0x14" />
	<field name="perb" descr="" subnode="perb_ext" capability="0" offset="0x0.0" selected_by="PERB" size="0xa0" />
	<field name="perbrg" descr="" subnode="perbrg_ext" capability="0" offset="0x0.0" selected_by="PERBRG" size="0x10" />
	<field name="perbeg" descr="" subnode="perbeg_ext" capability="0" offset="0x0.0" selected_by="PERBEG" size="0x10" />
	<field name="pacl" descr="" subnode="pacl_ext" capability="0" offset="0x0.0" selected_by="PACL" size="0x70" />
	<field name="pagt" descr="" subnode="pagt_ext" capability="0" offset="0x0.0" selected_by="PAGT" size="0x70" />
	<field name="ptar" descr="" subnode="ptar_ext" capability="0" offset="0x0.0" selected_by="PTAR" size="0x30" />
	<field name="perar" descr="" subnode="perar_ext" capability="0" offset="0x0.0" selected_by="PERAR" size="0x8" />
	<field name="percr" descr="" subnode="percr_ext" capability="0" offset="0x0.0" selected_by="PERCR" size="0x80" />
	<field name="pererp" descr="" subnode="pererp_ext" capability="0" offset="0x0.0" selected_by="PERERP" size="0x1c" />
	<field name="perd" descr="" subnode="perd_ext" capability="0" offset="0x0.0" selected_by="PERD" size="0x50" />
	<field name="ptce" descr="" subnode="ptce_ext" capability="0" offset="0x0.0" selected_by="PTCE" size="0xf0" />
	<field name="ptce_v2" descr="" subnode="ptce_v2_ext" capability="0" offset="0x0.0" selected_by="PTCE_V2" size="0x188" />
	<field name="ptce_v3" descr="" subnode="ptce_v3_ext" capability="0" offset="0x0.0" selected_by="PTCE_V3" size="0xa4" />
	<field name="ptcead" descr="" subnode="ptcead_ext" capability="0" offset="0x0.0" selected_by="PTCEAD" size="0x220" />
	<field name="pefa" descr="" subnode="pefa_ext" capability="0" offset="0x0.0" selected_by="PEFA" size="0xb0" />
	<field name="pefaad" descr="" subnode="pefaad_ext" capability="0" offset="0x0.0" selected_by="PEFAAD" size="0x420" />
	<field name="prcr" descr="" subnode="prcr_ext" capability="0" offset="0x0.0" selected_by="PRCR" size="0x40" />
	<field name="pprr" descr="" subnode="pprr_ext" capability="0" offset="0x0.0" selected_by="PPRR" size="0x14" />
	<field name="pfca" descr="" subnode="pfca_ext" capability="0" offset="0x0.0" selected_by="PFCA" size="0xc" />
	<field name="pfcnt" descr="" subnode="pfcnt_ext" capability="0" offset="0x0.0" selected_by="PFCNT" size="0x20" />
	<field name="ppbs" descr="" subnode="ppbs_ext" capability="0" offset="0x0.0" selected_by="PPBS" size="0x1c" />
	<field name="puet" descr="" subnode="puet_ext" capability="0" offset="0x0.0" selected_by="PUET" size="0x10" />
	<field name="ppbmi" descr="" subnode="ppbmi_ext" capability="0" offset="0x0.0" selected_by="PPBMI" size="0x14" />
	<field name="pecb" descr="" subnode="pecb_ext" capability="0" offset="0x0.0" selected_by="PECB" size="0x210" />
	<field name="perpt" descr="" subnode="perpt_ext" capability="0" offset="0x0.0" selected_by="PERPT" size="0x80" />
	<field name="peabfe" descr="" subnode="peabfe_ext" capability="0" offset="0x0.0" selected_by="PEABFE" size="0x410" />
	<field name="peapbl" descr="" subnode="peapbl_ext" capability="0" offset="0x0.0" selected_by="PEAPBL" size="0x20" />
	<field name="peapbm" descr="" subnode="peapbm_ext" capability="0" offset="0x0.0" selected_by="PEAPBM" size="0xf8" />
	<field name="peaps" descr="" subnode="peaps_ext" capability="0" offset="0x0.0" selected_by="PEAPS" size="0x34" />
	<field name="pecnre" descr="" subnode="pecnre_ext" capability="0" offset="0x0.0" selected_by="PECNRE" size="0x10" />
	<field name="pecnrr" descr="" subnode="pecnrr_ext" capability="0" offset="0x0.0" selected_by="PECNRR" size="0x20" />
	<field name="pecnee" descr="" subnode="pecnee_ext" capability="0" offset="0x0.0" selected_by="PECNEE" size="0x18" />
	<field name="pecner" descr="" subnode="pecner_ext" capability="0" offset="0x0.0" selected_by="PECNER" size="0x38" />
	<field name="peckc" descr="" subnode="peckc_ext" capability="0" offset="0x0.0" selected_by="PECKC" size="0x30" />
	<field name="xgcr" descr="" subnode="xgcr_ext" capability="0" offset="0x0.0" selected_by="XGCR" size="0x8" />
	<field name="xltq" descr="" subnode="xltq_ext" capability="0" offset="0x0.0" selected_by="XLTQ" size="0x2c" />
	<field name="xmdr" descr="" subnode="xmdr_ext" capability="0" offset="0x0.0" selected_by="XMDR" size="0xa0" />
	<field name="xlkbu" descr="" subnode="xlkbu_ext" capability="0" offset="0x0.0" selected_by="XLKBU" size="0x140" />
	<field name="xrmt" descr="" subnode="xrmt_ext" capability="0" offset="0x0.0" selected_by="XRMT" size="0x14" />
	<field name="xralta" descr="" subnode="xralta_ext" capability="0" offset="0x0.0" selected_by="XRALTA" size="0x8" />
	<field name="xralst" descr="" subnode="xralst_ext" capability="0" offset="0x0.0" selected_by="XRALST" size="0x108" />
	<field name="xraltb" descr="" subnode="xraltb_ext" capability="0" offset="0x0.0" selected_by="XRALTB" size="0x8" />
</node>

<node name="access_reg_summary_selector_ext" descr="" attr_is_union="1" size="0x440" >
	<field name="access_reg_summary" descr="" subnode="access_reg_summary_ext" offset="0x0.0" size="0x440" union_selector="$(parent).ctrl.id" />
	<field name="ctrl" descr="" subnode="access_reg_summary_ctrl_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="array128_auto" descr="" size="0x10.0" >
	<field name="array128_auto" descr="Auto generated" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="array256_auto" descr="" size="0x20.0" >
	<field name="array256_auto" descr="Auto generated" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="beabfe_bloom_filter" descr="" size="0x4.0" >
	<field name="bf_index" descr="Bloom filter entry\;Range is 0.. 2^cap_max_bf_log -1" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="bf_bank" descr="Bloom filter bank and erp table bank\;Range 0 .. cap_max_erp_table_banks-1" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="state" descr="Bloom filter state\;0: clear (default)\;1: set" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="bufferx_reg" descr="" size="0x8.0" >
	<field name="size" descr="The part of the packet buffer array is allocated for the specific buffer.\;Units are represented in cells.\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="epsb" descr="Eligible for Port Shared buffer.\;If epsb is set, packets assigned to bufferX are allowed to insert the port \;shared buffer.\;For port_shared_buffer, this field is reserved.\;When lossy==1 this field is reserved.\;The field is reserved for Switch-X/-2." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="lossy" descr="The field indicates if the buffer is lossy.\;0: Lossless\;1: Lossy\;\;The field is reserved for Switch-X/-2.\;For port_shared_buffer, this field is reserved.\;NOTE: This field does NOT affect the pause control. Pause control is con\;figured using PFCC register." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="xon_threshold" descr="When the amount of data in the buffer goes below this value, device stops \;sending pause frames for the Prios associated with the buffer. Units are \;represented in cells.\;In Spectrum xon_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_threshold" descr="Once the amount of data in the buffer goes above this value, device starts \;sending Pause frames for all Prios associated with the buffer. Units are \;represented in cells.\;In Spectrum xoff_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved." access="RW" offset="0x4.16" size="0x0.16" />
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
	<field name="high_latency_thr" descr="High latency threshold\;Units of 1uSec\;\;Note: HW has latency measurement error of   250nSec\;Note: packets with a latency larger than 4Sec latency may not be \;latency-mirrored. Thus it is recommended to set SLL to 4Sec\;\;" access="RW" offset="0x8.0" size="0x0.20" />
</node>

<node name="cnct_ext" descr="" size="0x8.0" >
	<field name="prio" descr="Priority" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="local_port" descr="Local port number. If the Index value is 0xFF the operation is \;applied for all the ports of the device." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="re" descr="Enable write operation into the r bit" access="WO" offset="0x4.14" size="0x0.1" />
	<field name="ee" descr="Enable write operation into the e bit" access="WO" offset="0x4.15" size="0x0.1" />
	<field name="r" descr="CNTag Remove (Default = 0)\;0: keep CNTags on frames egressing to this port\;1: remove CNTags from frames egressing to this port\;written only if re is set\;(Default = 0)" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="e" descr="CNP Enable (Default = 0)\;0: disable congestion notification for this egress port\;1: enable congestion notification for this egress port\;written only if ee is set" access="RW" offset="0x4.31" size="0x0.1" />
</node>

<node name="cnmc_ext" descr="" size="0x4.0" >
	<field name="prio" descr="Priority" access="RW" offset="0x0.8" size="0x0.3" />
</node>

<node name="config_item" descr="" size="0xc.0" >
	<field name="length" descr="Length of configuration item data in bytes (not including \;header). Must be between 0 and 256." access="RW" offset="0x0.0" size="0x0.9" />
	<field name="writer_host_id" descr="This field identify the host that configured this TLV. The \;field is not relevant for the following writer_ids: unspeci\;fied, chassis BMC and MAD." access="RO" offset="0x0.9" size="0x0.3" />
	<field name="version" descr="Configuration item version - defines the data structure fol\;lowing the header (together with the type field)." access="RW" offset="0x0.12" size="0x0.4" />
	<field name="writer_id" descr="The entity which configured this parameter\;0x0: UNSPECIFIED\;0x1: CHASSIS_BMC \;0x2: MAD \;0x3: BMC\;0x4: COMMAND_INTERFACE\;0x5: ICMD - with unspecified source\;0x6: ICMD_UEFI_HII - configured by the NIC&quot;s UEFI \;expansion ROM&quot;s HII menu.\;0x7: ICMD_UEFI_CLP - configured by the NIC&quot;s expan\;sion ROM&quot;s CLP.\;0x8: ICMD_Flexboot - configured by the NIC&quot;s legacy \;expansion ROM.\;0x9: ICMD_mlxconfig - configured by Mellanox mlxconfig \;tool\;0xA: ICMD_USER1 - value available for customer created \;tools that uses the ICMD interface for writing TLVs.\;0xB: ICMD_USER2 - value available for customer created \;tools that uses the ICMD interface for writing TLVs.\;0xC: ICMD_MLXCONFIG_SET_RAW - configures by\;mlxconfig set raw operation.\;0xD: ICMD_FLEXBOOT_CLP - configured by Legacy \;Expansion ROM CLP\;0x10: BMC_APP1 - Configuration was done over the BMC \;by application #1 (application name is OEM specific)\;0x11: BMC_APP2 - Configuration was done over the BMC \;by application #2 (application name is OEM specific)\;0x12: BMP_APP3 - Configuration was done over the BMC \;by application #3 (application name is OEM specific)\;0x1F: OTHER - the parameter was written by the NIC due \;to other reasons. \;Note - This field is writeable only when using the ICMD \;interface. The only value that are valid for writes are 0x6-\;0xB. Other values will be replaced by 0x5ICMD." access="RO" enum="UNSPECIFIED=0x0,CHASSIS_BMC=0x1,MAD=0x2,BMC=0x3,COMMAND_INTERFACE=0x4,ICMD=0x5,ICMD_UEFI_HII=0x6,ICMD_UEFI_CLP=0x7,ICMD_Flexboot=0x8,ICMD_mlxconfig=0x9,ICMD_USER1=0xa,ICMD_USER2=0xb,ICMD_MLXCONFIG_SET_RAW=0xc,ICMD_FLEXBOOT_CLP=0xd,BMC_APP1=0x10,BMC_APP2=0x11,BMP_APP3=0x12,OTHER=0x1f" offset="0x0.16" size="0x0.5" />
	<field name="access_mode" descr="Defines which value of the Configuration Item will be \;accessed.\;0x0: NEXT - Next value to be applied \;0x1: CURRENT - Currently set values (only valid for Query \;operation) Supported only if NVGC.nvda_read_current_set\;tings==1.\;0x2: FACTORY - Default factory values (only valid for \;Query operation). Supported only if NVGC.nvda_read_fac\;tory_settings==1.\;\;" access="INDEX" enum="NEXT=0x0,CURRENT=0x1,FACTORY=0x2" offset="0x0.22" size="0x0.2" />
	<field name="header_type" descr="[internal] Encodes the storage element Header Format\;0x0: header_only - Only Header is protected by CRC\;0x1: header_and_date - Header &amp; Data are protected by \;CRC\;other values are reserved" access="RW" enum="header_only=0x0,header_and_date=0x1" offset="0x0.26" size="0x0.2" />
	<field name="valid" descr="[Internal] Encodes the data element validity\;0x0: invalid_data- should be skipped\;0x1: illegal- treated as Invalidated data element\;0x2: valid_data\;0x3: free- (no data exists)" access="RW" enum="invalid_data=0x0,illegal=0x1,valid_data=0x2,free=0x3" offset="0x0.30" size="0x0.2" />
	<field name="type_index" descr="Configuration item index according to its type_class. \;Table 1455, &quot;Configuration Item Type Class Global Lay\;out,&quot; on page 1599\;Table 1457, &quot;Configuration Item Type Class Physical Port \;Layout,&quot; on page 1600\;Table 1459, &quot;Configuration Item Type Class Per Host-PF \;Layout,&quot; on page 1600\;Table 1461, &quot;Configuration Item Type Class Log Layout,&quot; \;on page 1600\;Table 1463, &quot;Configuration Item Type Class File Layout,&quot; \;on page 1601\;Table 1465, &quot;Configuration Item Type Class Host Layout,&quot; \;on page 1601\;Table 1478, &quot;Configuration Item Type Layout, Class Switch \;Global,&quot; on page 1611" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="type_class" descr="Type Class.\;0x0: Global\;0x1: Port\;0x3: Host_PF\;0x5: Log\;0x6: File\;0x7: Host\;0x8 Switch Global" access="INDEX" enum="Global=0x0,Port=0x1,Host_PF=0x3,Log=0x5,File=0x6,Host=0x7" offset="0x4.24" size="0x0.8" />
	<field name="crc16" descr="[Internal] Encodes the data integrity check of the data ele\;ment. \;Note: In some elements, only encodes the header into the \;CRC16, as defined in the header type field." access="RW" offset="0x8.0" size="0x0.16" />
</node>

<node name="cpcs_ext" descr="" size="0x18.0" >
	<field name="tclass" descr="Traffic Class" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="cpmhoe" descr="Enable write operation into cp_min_header_octets." access="WO" offset="0x4.28" size="0x0.1" />
	<field name="cpsbe" descr="Enable write operation into cp_sample_base." access="WO" offset="0x4.29" size="0x0.1" />
	<field name="log2_cpwe" descr="Enable write operation into cpw." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="cpqspe" descr="Enable write operation into cpqsp." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="cpqsp" descr="The set point for the queue, this is the target number of octets in the \;CP&apos;s queue. Default value is 26048.\;Values configured to this register must be 64B aligned. Maximum \;value for this register is 4194240.\;Written only if cpqspe is set." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="log2_cpw" descr="The weight (cpW) of the congestion point is equal to two to the \;power of this object.\;Thus, if this object contains a -1, cpW = 1/2.\;Written only if log2_cpwe is set." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="cp_sample_base" descr="The minimum number of octets to enqueue in the CP&apos;s queue \;between CNM PDU transmissions. Default value 150016\;Values configured to this register must be 64B aligned. Maximum \;value for the register is 2147483584.\;Written only if cpsbe is set" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="cp_min_header_octets" descr="The minimum number of octets that the CP is to return in the Encap\;sulated MSDU field (IEEE 802.1Qau 33.4.10) of each CNM it gener\;ates (IEEE 802.1Qau 32.9.4). Default value 0.\;Written only if cpmhoe is set." access="RW" offset="0x14.0" size="0x4.0" />
</node>

<node name="cpid_ext" descr="" size="0xc.0" >
	<field name="prio" descr="Priority" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="local_port" descr="Local port number. if the Index value is 0xFF the operation \;will be applied for all the ports of the device." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cpid_high" descr="IEEE 802.1Qau Congestion Point Identifier." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="cpid_low" descr="IEEE 802.1Qau Congestion Point Identifier." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="cpqe_ext" descr="" size="0xc.0" >
	<field name="local_port" descr="Egress Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="marking_percent" descr="ECN Marking percentage when the local_port rate is above the \;phantom queue rate as configured by phantom_queue_rate in \;QEEC, see Section 11.13.11, &quot;QEEC - QoS ETS Element Con\;figuration,&quot; on page 1801\;Range is 0..100, units of integer percentage" access="RW" offset="0x8.16" size="0x0.7" />
</node>

<node name="cwgcr_ext" descr="" size="0x14.0" >
	<field name="aqs_time" descr="Average queue size time\;Time from current_queue_size to previous_aqs\;The time is 2^aqs_time * 64nSec\;Valid range is 0..24" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="aqs_weight" descr="Average queue size weight.\;The average queue size (aqs) is calculated by:\;aqs = ((current_queue_size)*2^-w) + ((previous_aqs)*(1-2^-w)) \;where w is aqs_weight\;The time between current_queue_size and previous_aqs is configured \;by aqs_time\;Note: when mode=percentage then there is no moving average (the \;aqs_weight is effectively 0). See Section 12.6.2, &quot;CWTP - Congestion \;WRED ECN TClass Profile Register,&quot; on page 1836" access="RW" offset="0x0.8" size="0x0.4" />
	<field name="scd" descr="Enable ECN Source Congestion Detection only. Don&apos;t mark victim \;packets.\;" access="RW" offset="0x0.16" size="0x0.1" />
	<field name="en" descr="enable bits:\;bit2: WRED drop enable\;For Spectrum, ingress mirror of WRED can utilize this configuration, \;see Section 4.12.2, &quot;MPAR - Monitoring Port Analyzer Register,&quot; on \;page 700" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="cece" descr="Count ECN for Congestion Experienced\;0: do not count &quot;ECN mark&quot; for a packet which has Congestion Experi\;enced (ECN=11 at ingress) \;1: do count ECN mark for a packet which has Congestion Experienced \;(ECN=11 at ingress) and experiences congestion in the switch (default)\;In any case, a packet coming with ECN=00 is not counted as ECN." access="RW" offset="0x4.0" size="0x0.1" />
	<field name="mece" descr="Mirror ECN for Congestion Experienced\;0: do not ecn-mirror a packet which has Congestion Experienced \;(ECN=11 at ingress)\;1: do ecn-mirror for a packet which has Congestion Experienced \;(ECN=11 at ingress) and experiences congestion in the switch (default)\;In any case, a packet coming with ECN=00 is not ecn-mirrored\;Reserved when Spectrum-1\;Reserved when Quantum which always does ecn-mirror regardless of \;fecn in the packet" access="RW" offset="0x4.1" size="0x0.1" />
</node>

<node name="cwpp_ext" descr="" size="0x20.0" >
	<field name="pool" descr="Egress pool in the switch shared buffer\;Range is 0..cap_num_pool_supported-1" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="profile1_min" descr="Minimum Average Queue Size of the profile number &lt;i&gt;, in cells. \;Valid inputs are 0..cap_total_buffer_size/cap_cell_size\;For Spectrum: must be a multiple of 64" access="RW" offset="0x8.0" size="0x0.20" />
	<field name="profile1_max" descr="Maximum Average Queue Size of the profile number &lt;i&gt;, in \;cells. Valid inputs are 0..cap_total_buffer_size/cap_cell_size\;For Spectrum: must be a multiple of 64" access="RW" offset="0xC.0" size="0x0.20" />
	<field name="profile1_percent" descr="Percentage of WRED and ECN marking for Maximum Average \;Queue Size of the profile number &lt;i&gt;\;Range is 0..100, units of integer percentage\;Default is 0" access="RW" offset="0xC.24" size="0x0.7" />
	<field name="profile2_min" descr="Same as above." access="RW" offset="0x10.0" size="0x0.20" />
	<field name="profile2_max" descr="Same as above." access="RW" offset="0x14.0" size="0x0.20" />
	<field name="profile2_percent" descr="Same as above." access="RW" offset="0x14.24" size="0x0.7" />
	<field name="profile3_min" descr="Same as above." access="RW" offset="0x18.0" size="0x0.20" />
	<field name="profile3_max" descr="Same as above." access="RW" offset="0x1C.0" size="0x0.20" />
	<field name="profile3_percent" descr="Same as above." access="RW" offset="0x1C.24" size="0x0.7" />
</node>

<node name="cwtp_ext" descr="" size="0x40.0" >
	<field name="pnat" descr="Port number access type. Determines the way local_port is \;interpreted:\;0: Local_port_number\;" access="INDEX" enum="Local_port_number=0x0" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_data-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="mode" descr="Mode of thresholds for WRED and ECN:\;0: Fixed\;1: Percentage" access="RW" enum="Fixed=0x0,Percentage=0x1" offset="0x24.24" size="0x0.1" />
	<field name="profile1_min" descr="Minimum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_cell_size.\;For Spectrum: must be a multiple of 64\;Note: for Spectrum, must be larger than 2^aqs_weight cells, \;see Section 12.6.1, &quot;CWGCR - Congestion WRED ECN Gen\;eral Configuration Register,&quot; on page 1834\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. Range is \;0..100, units of integer percentage. When ECN Source Conges\;tion Detection is enabled then congestion occurs when there \;are at least 256 cells in the buffer\;" access="RW" offset="0x28.0" size="0x0.20" />
	<field name="profile1_max" descr="Maximum Average Queue Size of the profile number &lt;i&gt;\;When mode is Fixed:\;Cells. Valid inputs are 1..cap_total_buffer_size/cap_cell_size\;For Spectrum: must be a multiple of 64\;When mode is Percentage:\;Percentage of the quota of local_port,traffic_class. Range is \;0..100, units of integer percentage.\;profile&lt;i&gt;_max must always be equal or greater than pro\;file&lt;i&gt;_min" access="RW" offset="0x2C.0" size="0x0.20" />
	<field name="profile1_percent" descr="Percentage of WRED and ECN marking for Maximum Aver\;age Queue Size of the profile number &lt;i&gt;\;Range is 0..100, units of integer percentage\;Default is 0" access="RW" offset="0x2C.24" size="0x0.7" />
	<field name="profile2_min" descr="Same as above." access="RW" offset="0x30.0" size="0x0.20" />
	<field name="profile2_max" descr="Same as above." access="RW" offset="0x34.0" size="0x0.20" />
	<field name="profile2_percent" descr="Same as above." access="RW" offset="0x34.24" size="0x0.7" />
	<field name="profile3_min" descr="Same as above." access="RW" offset="0x38.0" size="0x0.20" />
	<field name="profile3_max" descr="Same as above." access="RW" offset="0x3C.0" size="0x0.20" />
	<field name="profile3_percent" descr="Same as above." access="RW" offset="0x3C.24" size="0x0.7" />
</node>

<node name="cwtpm_ext" descr="" size="0x44.0" >
	<field name="pnat" descr="Port number access type. Determines the way local_port is \;interpreted:\;0: Local_port_number\;" access="INDEX" enum="Local_port_number=0x0" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="traffic_class" descr="Traffic Class\;Range is 0..cap_max_tclass_data-1" access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="ee" descr="Enable ECN on traffic class\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.0" size="0x0.1" />
	<field name="ew" descr="Enable WRED on traffic class:\;0: Disable\;1: Enable\;Default is 0\;Reserved when Quantum" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x24.1" size="0x0.1" />
	<field name="tcp_g" descr="TCP Green Profile Number\;0 for disabling both WRED and ECN for this type of traffic.\;Default is 0\;Reserved when Quantum and NIC" access="RW" offset="0x34.0" size="0x0.2" />
	<field name="tcp_r" descr="TCP Red Profile Number\;0 for disabling both WRED and ECN for this type of traffic.\;Default is 0\;Reserved when Quantum and NIC" access="RW" offset="0x38.0" size="0x0.2" />
	<field name="tcp_y" descr="TCP Yellow Profile Number\;0 for disabling both WRED and ECN for this type of traffic.\;Default is 0\;Reserved when Quantum and NIC" access="RW" offset="0x38.16" size="0x0.2" />
	<field name="ntcp_g" descr="Non-TCP Green Profile Number\;0 for disabling both WRED and ECN for this type of traffic.\;Default is 0\;Reserved when Quantum and NIC" access="RW" offset="0x3C.0" size="0x0.2" />
	<field name="ntcp_r" descr="Non-TCP Red Profile Number\;0 for disabling both WRED and ECN for this type of traffic.\;Default is 0\;Reserved when Quantum and NIC" access="RW" offset="0x40.0" size="0x0.2" />
	<field name="ntcp_y" descr="Non-TCP Yellow Profile Number\;0 for disabling both WRED and ECN for this type of traffic.\;Default is 0\;Reserved when Quantum and NIC" access="RW" offset="0x40.16" size="0x0.2" />
</node>

<node name="ecn" descr="" size="0x4.0" >
	<field name="color2" descr="The EXP mapping for color k, where k=0..2, see Table 1851, \;&quot;color&lt;k&gt;Layout,&quot; on page 1816" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="color1" descr="The EXP mapping for color k, where k=0..2, see Table 1851, \;&quot;color&lt;k&gt;Layout,&quot; on page 1816" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="color0" descr="The EXP mapping for color k, where k=0..2, see Table 1851, \;&quot;color&lt;k&gt;Layout,&quot; on page 1816" access="RW" offset="0x0.24" size="0x0.8" />
</node>

<node name="elport_record" descr="" size="0x4.0" >
	<field name="evid" descr="egress vid, range 0..4095" access="RW" offset="0x0.0" size="0x0.12" />
	<field name="update" descr="Update enable (when write):\;0: do not update the entry\;1: update the entry" access="OP" offset="0x0.31" size="0x0.1" />
</node>

<node name="enum_entry" descr="" size="0x4.0" >
</node>

<node name="eth_2819_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="ether_stats_drop_events_high" descr="The total number of events in which packets were \;dropped by the probe due to lack of resources.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ether_stats_drop_events_low" descr="The total number of events in which packets were \;dropped by the probe due to lack of resources.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ether_stats_octets_high" descr="The total number of octets of data (including those in \;bad packets) received (excluding framing bits but \;including FCS octets).\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ether_stats_octets_low" descr="The total number of octets of data (including those in \;bad packets) received (excluding framing bits but \;including FCS octets).\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ether_stats_pkts_high" descr="The total number of packets (including bad packets, \;broadcast packets, and multicast packets) received.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ether_stats_pkts_low" descr="The total number of packets (including bad packets, \;broadcast packets, and multicast packets) received.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_high" descr="The total number of good packets received that were \;directed to the broadcast address. \;Note: This does not include multicast packets.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_low" descr="The total number of good packets received that were \;directed to the broadcast address. \;Note: This does not include multicast packets.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_high" descr="The total number of good packets received that were \;directed to a multicast MAC address. \;Note: This number does not include packets directed \;to the broadcast address.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_low" descr="The total number of good packets received that were \;directed to a multicast MAC address. \;Note: This number does not include packets directed \;to the broadcast address.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_high" descr="The total number of packets received that had a length \;(excluding framing bits, but including FCS octets) of \;between 64 and MTU octets, inclusive, but had either \;a bad frame check sequence (FCS) with an integral \;number of octets (FCS error) or a bad FCS with a \;non-integral number of octets (alignment error).\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_low" descr="The total number of packets received that had a length \;(excluding framing bits, but including FCS octets) of \;between 64 and MTU octets, inclusive, but had either \;a bad frame check sequence (FCS) with an integral \;number of octets (FCS error) or a bad FCS with a \;non-integral number of octets (alignment error).\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_high" descr="The total number of packets received that were less \;than 64 octets long (excluding framing bits, but \;including FCS octets) and were otherwise well \;formed.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_low" descr="The total number of packets received that were less \;than 64 octets long (excluding framing bits, but \;including FCS octets) and were otherwise well \;formed.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_high" descr="The total number of packets received that were longer \;than MTU octets (excluding framing bits, but includ\;ing FCS octets) but were otherwise well formed.\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_low" descr="The total number of packets received that were longer \;than MTU octets (excluding framing bits, but includ\;ing FCS octets) but were otherwise well formed.\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="ether_stats_fragments_high" descr="The total number of packets received that were less \;than 64 octets in length (excluding framing bits but \;including FCS octets) and had either a bad FCS with \;an integral number of octets (FCS error) or a bad FCS \;with a non-integral number of octets (alignment \;error).\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="ether_stats_fragments_low" descr="The total number of packets received that were less \;than 64 octets in length (excluding framing bits but \;including FCS octets) and had either a bad FCS with \;an integral number of octets (FCS error) or a bad FCS \;with a non-integral number of octets (alignment \;error).\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="ether_stats_jabbers_high" descr="The total number of packets received that were longer \;than MTU octets (excluding framing bits, but includ\;ing FCS octets), and had either a bad FCS with an \;integral number of octets (FCS error) or a bad FCS \;with a non-integral number of octets (alignment \;error).\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="ether_stats_jabbers_low" descr="The total number of packets received that were longer \;than MTU octets (excluding framing bits, but includ\;ing FCS octets), and had either a bad FCS with an \;integral number of octets (FCS error) or a bad FCS \;with a non-integral number of octets (alignment \;error).\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="ether_stats_collisions_high" descr="The best estimate of the total number of collisions on \;this Ethernet segment.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ether_stats_collisions_low" descr="The best estimate of the total number of collisions on \;this Ethernet segment.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_high" descr="The total number of packets (including bad packets) \;received that were 64 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_low" descr="The total number of packets (including bad packets) \;received that were 64 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_high" descr="The total number of packets (including bad packets) \;received that were between 65 and 127 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_low" descr="The total number of packets (including bad packets) \;received that were between 65 and 127 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_high" descr="The total number of packets (including bad packets) \;received that were between 128 and 255 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_low" descr="The total number of packets (including bad packets) \;received that were between 128 and 255 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_high" descr="The total number of packets (including bad packets) \;received that were between 256 and 511 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_low" descr="The total number of packets (including bad packets) \;received that were between 256 and 511 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_high" descr="The total number of packets (including bad packets) \;received that were between 512 and 1023 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_low" descr="The total number of packets (including bad packets) \;received that were between 512 and 1023 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad packets) \;received that were between 1024 and 1518 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_low" descr="The total number of packets (including bad packets) \;received that were between 1024 and 1518 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad packets) \;received that were between 1519 and 2047 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_low" descr="The total number of packets (including bad packets) \;received that were between 1519 and 2047 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad packets) \;received that were between 2048 and 4095 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_low" descr="The total number of packets (including bad packets) \;received that were between 2048 and 4095 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x94.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad packets) \;received that were between 4096 and 8191 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x98.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_low" descr="The total number of packets (including bad packets) \;received that were between 4096 and 8191 octets in \;length (excluding framing bits but including FCS \;octets)." access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad packets) \;received that were between 8192 and 10239 octets in \;length (excluding framing bits but including FCS \;octets).\;" access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_low" descr="The total number of packets (including bad packets) \;received that were between 8192 and 10239 octets in \;length (excluding framing bits but including FCS \;octets).\;" access="RO" offset="0xA4.0" size="0x4.0" />
</node>

<node name="eth_2863_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="if_in_octets_high" descr="The total number of octets received, including framing charac\;ters. Including MAC control frames.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="if_in_octets_low" descr="The total number of octets received, including framing charac\;ters. Including MAC control frames.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_high" descr="The number of packets successfully received, which were not \;addressed to a multicast or broadcast MAC address.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_low" descr="The number of packets successfully received, which were not \;addressed to a multicast or broadcast MAC address.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="if_in_discards_high" descr="The number of inbound packets which were chosen to be dis\;carded even though no errors had been detected to prevent \;their being deliverable to a higher-layer protocol.\;\;\;\;\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="if_in_discards_low" descr="The number of inbound packets which were chosen to be dis\;carded even though no errors had been detected to prevent \;their being deliverable to a higher-layer protocol.\;\;\;\;\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="if_in_errors_high" descr="The number of inbound packets that contained errors prevent\;ing them from being deliverable to a higher-layer protocol. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="if_in_errors_low" descr="The number of inbound packets that contained errors prevent\;ing them from being deliverable to a higher-layer protocol. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="if_in_unknown_protos_high" descr="The number of packets received via the interface which were \;discarded because of an unknown or unsupported protocol.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="if_in_unknown_protos_low" descr="The number of packets received via the interface which were \;discarded because of an unknown or unsupported protocol.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="if_out_octets_high" descr="The total number of octets transmitted out of the interface, \;including framing characters.\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="if_out_octets_low" descr="The total number of octets transmitted out of the interface, \;including framing characters.\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_high" descr="The total number of packets that higher-level protocols \;requested be transmitted and were not addressed to a multicast \;or broadcast MAC address, including those that were discarded \;or not sent.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_low" descr="The total number of packets that higher-level protocols \;requested be transmitted and were not addressed to a multicast \;or broadcast MAC address, including those that were discarded \;or not sent.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="if_out_discards_high" descr="The number of outbound packets which were chosen to be dis\;carded, even though no errors had been detected to prevent \;their being transmitted. \;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="if_out_discards_low" descr="The number of outbound packets which were chosen to be dis\;carded, even though no errors had been detected to prevent \;their being transmitted. \;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="if_out_errors_high" descr="The number of outbound packets that could not be transmitted \;because of errors.\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="if_out_errors_low" descr="The number of outbound packets that could not be transmitted \;because of errors.\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_high" descr="The number of packets successfully received, which were \;addressed to a multicast MAC address.\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_low" descr="The number of packets successfully received, which were \;addressed to a multicast MAC address.\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_high" descr="The number of packets successfully received, which were \;addressed to a broadcast MAC address.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_low" descr="The number of packets successfully received, which were \;addressed to a broadcast MAC address.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_high" descr="The total number of packets that higher-level protocols \;requested be transmitted, and which were addressed to a multi\;cast MAC address, including those that were discarded or not \;sent.\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_low" descr="The total number of packets that higher-level protocols \;requested be transmitted, and which were addressed to a multi\;cast MAC address, including those that were discarded or not \;sent.\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_high" descr="The total number of packets that higher-level protocols \;requested be transmitted, and which were addressed to a broad\;cast MAC address, including those that were discarded or not \;sent.\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_low" descr="The total number of packets that higher-level protocols \;requested be transmitted, and which were addressed to a broad\;cast MAC address, including those that were discarded or not \;sent.\;" access="RO" offset="0x64.0" size="0x4.0" />
</node>

<node name="eth_3635_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="dot3stats_alignment_errors_high" descr="A count of frames received that are not an integral number \;of octets in length and do not pass the FCS check.\;" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="dot3stats_alignment_errors_low" descr="A count of frames received that are not an integral number \;of octets in length and do not pass the FCS check.\;" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_high" descr="A count of frames received that are an integral number of \;octets in length but do not pass the FCS check. This count \;does not include frames received with frame-too-long or \;frame-too-short errors.\;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_low" descr="A count of frames received that are an integral number of \;octets in length but do not pass the FCS check. This count \;does not include frames received with frame-too-long or \;frame-too-short errors.\;" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_high" descr="A count of frames that are involved in a single collision, \;and are subsequently transmitted successfully.\;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_low" descr="A count of frames that are involved in a single collision, \;and are subsequently transmitted successfully.\;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_high" descr="A count of frames that are involved in more than one colli\;sion and are subsequently transmitted successfully. \;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_low" descr="A count of frames that are involved in more than one colli\;sion and are subsequently transmitted successfully. \;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_high" descr="A count of times that the SQE TEST ERROR is received \;on a particular interface.\;This counter does not increment on interfaces operating at \;speeds greater than 10 Mb/s, or on interfaces operating in \;full-duplex mode. \;" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_low" descr="A count of times that the SQE TEST ERROR is received \;on a particular interface.\;This counter does not increment on interfaces operating at \;speeds greater than 10 Mb/s, or on interfaces operating in \;full-duplex mode. \;" access="RW" offset="0x24.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_high" descr="A count of frames for which the first transmission attempt \;on a particular interface is delayed because the medium is \;busy. \;This counter does not increment when the interface is \;operating in full-duplex mode. \;" access="RW" offset="0x28.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_low" descr="A count of frames for which the first transmission attempt \;on a particular interface is delayed because the medium is \;busy. \;This counter does not increment when the interface is \;operating in full-duplex mode. \;" access="RW" offset="0x2C.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_high" descr="The number of times that a collision is detected on a par\;ticular interface later than one slotTime into the transmis\;sion of a packet.\;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x30.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_low" descr="The number of times that a collision is detected on a par\;ticular interface later than one slotTime into the transmis\;sion of a packet.\;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x34.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_high" descr="A count of frames for which transmission on a particular \;interface fails due to excessive collisions.\;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x38.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_low" descr="A count of frames for which transmission on a particular \;interface fails due to excessive collisions.\;This counter does not increment when the interface is \;operating in full-duplex mode.\;" access="RW" offset="0x3C.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_high" descr="A count of frames for which transmission failed and were \;discarded even though no errors had been detected to pre\;vent their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x40.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_low" descr="A count of frames for which transmission failed and were \;discarded even though no errors had been detected to pre\;vent their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_high" descr="The number of times that the carrier sense condition was \;lost or never asserted when attempting to transmit a frame \;on a particular interface. \;This counter does not increment when the interface is \;operating in full-duplex mode. \;" access="RW" offset="0x48.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_low" descr="The number of times that the carrier sense condition was \;lost or never asserted when attempting to transmit a frame \;on a particular interface. \;This counter does not increment when the interface is \;operating in full-duplex mode. \;" access="RW" offset="0x4C.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_high" descr="A count of frames received that exceed the maximum per\;mitted frame size.\;" access="RW" offset="0x50.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_low" descr="A count of frames received that exceed the maximum per\;mitted frame size.\;" access="RW" offset="0x54.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_high" descr="A count of frames for which reception failed and were dis\;carded even though no errors had been detected to prevent \;their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x58.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_low" descr="A count of frames for which reception failed and were dis\;carded even though no errors had been detected to prevent \;their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x5C.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_high" descr="The number of times the receiving media is non-idle (a \;carrier event) for a period of time equal to or greater than \;minFrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate \;&quot;Receive Error&quot;.\;\;" access="RW" offset="0x60.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_low" descr="The number of times the receiving media is non-idle (a \;carrier event) for a period of time equal to or greater than \;minFrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate \;&quot;Receive Error&quot;.\;\;" access="RW" offset="0x64.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_high" descr="A count of MAC Control frames received that contain an \;opcode that is not supported.\;" access="RW" offset="0x68.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_low" descr="A count of MAC Control frames received that contain an \;opcode that is not supported.\;" access="RW" offset="0x6C.0" size="0x4.0" />
	<field name="dot3in_pause_frames_high" descr="A count of MAC Control frames received with an opcode \;indicating the PAUSE operation.\;\;" access="RW" offset="0x70.0" size="0x4.0" />
	<field name="dot3in_pause_frames_low" descr="A count of MAC Control frames received with an opcode \;indicating the PAUSE operation.\;\;" access="RW" offset="0x74.0" size="0x4.0" />
	<field name="dot3out_pause_frames_high" descr="A count of MAC Control frames transmitted with an \;opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x78.0" size="0x4.0" />
	<field name="dot3out_pause_frames_low" descr="A count of MAC Control frames transmitted with an \;opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x7C.0" size="0x4.0" />
</node>

<node name="eth_802_3_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="a_frames_transmitted_ok_high" descr="A count of frames that are successfully transmitted. \;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="a_frames_transmitted_ok_low" descr="A count of frames that are successfully transmitted. \;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="a_frames_received_ok_high" descr="A count of frames that are successfully received. This \;does not include frames received with frame-too-long, \;frame check sequence (FCS), length or alignment errors, \;or frames lost due to other MAC errors.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="a_frames_received_ok_low" descr="A count of frames that are successfully received. This \;does not include frames received with frame-too-long, \;frame check sequence (FCS), length or alignment errors, \;or frames lost due to other MAC errors.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="a_frame_check_sequence_errors_high" descr="A count of receive frames that are an integral number of \;octets in length and do not pass the FCS check. This \;does not include frames received with frame-too-long, or \;frame-too-short (frame fragment) errors.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="a_frame_check_sequence_errors_low" descr="A count of receive frames that are an integral number of \;octets in length and do not pass the FCS check. This \;does not include frames received with frame-too-long, or \;frame-too-short (frame fragment) errors.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="a_alignment_errors_high" descr="A count of frames that are not an integral number of \;octets in length and do not pass the FCS check.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="a_alignment_errors_low" descr="A count of frames that are not an integral number of \;octets in length and do not pass the FCS check.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="a_octets_transmitted_ok_high" descr="A count of data and padding octets of frames that are \;successfully transmitted.\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="a_octets_transmitted_ok_low" descr="A count of data and padding octets of frames that are \;successfully transmitted.\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="a_octets_received_ok_high" descr="A count of data and padding octets in frames that are \;successfully received. This does not include octets in \;frames received with frame-too-long, FCS, length or \;alignment errors, or frames lost due to other MAC \;errors.\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="a_octets_received_ok_low" descr="A count of data and padding octets in frames that are \;successfully received. This does not include octets in \;frames received with frame-too-long, FCS, length or \;alignment errors, or frames lost due to other MAC \;errors.\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="a_multicast_frames_xmitted_ok_high" descr="A count of frames that are successfully transmitted to a \;group destination address other than broadcast.\;\; \;\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="a_multicast_frames_xmitted_ok_low" descr="A count of frames that are successfully transmitted to a \;group destination address other than broadcast.\;\; \;\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="a_broadcast_frames_xmitted_ok_high" descr="A count of the frames that were successfully transmitted \;to the broadcast address. Frames transmitted to multicast \;addresses are not broadcast frames and are excluded.\;\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="a_broadcast_frames_xmitted_ok_low" descr="A count of the frames that were successfully transmitted \;to the broadcast address. Frames transmitted to multicast \;addresses are not broadcast frames and are excluded.\;\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="a_multicast_frames_received_ok_high" descr="A count of frames that are successfully received and \;directed to an active nonbroadcast group address. This \;does not include frames received with frame-too-long, \;FCS, length or alignment errors, or frames lost due to \;internal MAC sublayer error. \;  \;\;\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="a_multicast_frames_received_ok_low" descr="A count of frames that are successfully received and \;directed to an active nonbroadcast group address. This \;does not include frames received with frame-too-long, \;FCS, length or alignment errors, or frames lost due to \;internal MAC sublayer error. \;  \;\;\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="a_broadcast_frames_received_ok_high" descr="A count of the frames that were successfully transmitted \;to the broadcast address. Frames transmitted to multicast \;addresses are not broadcast frames and are excluded. \;\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="a_broadcast_frames_received_ok_low" descr="A count of the frames that were successfully transmitted \;to the broadcast address. Frames transmitted to multicast \;addresses are not broadcast frames and are excluded. \;\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="a_in_range_length_errors_high" descr="A count of frames with a length/type field value between \;the minimum unpadded MAC client data size and the \;maximum allowed MAC client data size, inclusive, that \;does not match the number of MAC client data octets \;received. The counter also increments for frames whose \;length/type field value is less than the minimum allowed \;unpadded MAC client data size and the number of MAC \;client data octets received is greater than the minimum \;unpadded MAC client data size.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="a_in_range_length_errors_low" descr="A count of frames with a length/type field value between \;the minimum unpadded MAC client data size and the \;maximum allowed MAC client data size, inclusive, that \;does not match the number of MAC client data octets \;received. The counter also increments for frames whose \;length/type field value is less than the minimum allowed \;unpadded MAC client data size and the number of MAC \;client data octets received is greater than the minimum \;unpadded MAC client data size.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="a_out_of_range_length_field_high" descr="A count of frames with a length field value greater than \;the maximum allowed LLC data size. \;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="a_out_of_range_length_field_low" descr="A count of frames with a length field value greater than \;the maximum allowed LLC data size. \;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="a_frame_too_long_errors_high" descr="A count of frames received that exceed the maximum \;permitted frame size by IEEE 802.3 (MTU size).\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="a_frame_too_long_errors_low" descr="A count of frames received that exceed the maximum \;permitted frame size by IEEE 802.3 (MTU size).\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="a_symbol_error_during_carrier_high" descr="For full duplex operation at 1000 Mb/s, it is a count of \;the number of times the receiving media is non-idle (a \;carrier event) for a period of time equal to or greater than \;minFrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate \;&quot;Data reception error&quot;.\;For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/s, it is a \;count of the number of times the receiving media is non-\;idle for a period of time equal to or greater than min\;FrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate\;Error.\;\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="a_symbol_error_during_carrier_low" descr="For full duplex operation at 1000 Mb/s, it is a count of \;the number of times the receiving media is non-idle (a \;carrier event) for a period of time equal to or greater than \;minFrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate \;&quot;Data reception error&quot;.\;For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/s, it is a \;count of the number of times the receiving media is non-\;idle for a period of time equal to or greater than min\;FrameSize, and during which there was at least one \;occurrence of an event that causes the PHY to indicate\;Error.\;\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="a_mac_control_frames_transmitted_high" descr="A count of MAC Control frames passed to the MAC \;sublayer for transmission.\;\;" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="a_mac_control_frames_transmitted_low" descr="A count of MAC Control frames passed to the MAC \;sublayer for transmission.\;\;" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="a_mac_control_frames_received_high" descr="A count of MAC Control frames passed by the MAC \;sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="a_mac_control_frames_received_low" descr="A count of MAC Control frames passed by the MAC \;sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="a_unsupported_opcodes_received_high" descr="A count of MAC Control frames received that contain an \;opcode that is not supported by the device.\;\;" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="a_unsupported_opcodes_received_low" descr="A count of MAC Control frames received that contain an \;opcode that is not supported by the device.\;\;" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_received_high" descr="A count of MAC PAUSE frames passed by the MAC \;sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_received_low" descr="A count of MAC PAUSE frames passed by the MAC \;sublayer to the MAC Control sublayer.\;\;" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_transmitted_high" descr="A count of PAUSE frames passed to the MAC sublayer \;for transmission.\;\;" access="RO" offset="0x90.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_transmitted_low" descr="A count of PAUSE frames passed to the MAC sublayer \;for transmission.\;\;" access="RO" offset="0x94.0" size="0x4.0" />
</node>

<node name="eth_adjacency_ext" descr="" size="0x18.0" >
	<field name="destination_mac_47_32" descr="MAC address of the destination next-hop." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="destination_mac_31_0" descr="MAC address of the destination next-hop." access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="eth_discard_cntrs_grp_ext" descr="" size="0xf8.0" >
	<field name="ingress_general_high" descr="Ingress general \;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ingress_general_low" descr="Ingress general \;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ingress_policy_engine_high" descr="Ingress policy engine discards" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ingress_policy_engine_low" descr="Ingress policy engine discards" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ingress_vlan_membership_high" descr="Ingress VLAN membership filter discards" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ingress_vlan_membership_low" descr="Ingress VLAN membership filter discards" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_high" descr="Ingress VLAN tag allowance (tagged, untagged and prio-tagged) \;filter discards" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_low" descr="Ingress VLAN tag allowance (tagged, untagged and prio-tagged) \;filter discards" access="RO" offset="0x1C.0" size="0x4.0" />
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
	<field name="ingress_tx_link_down_high" descr="Per ingress port count dropped packets due to egress link down" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="ingress_tx_link_down_low" descr="Per ingress port count dropped packets due to egress link down" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="egress_stp_filter_high" descr="Egress spanning tree filter" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="egress_stp_filter_low" descr="Egress spanning tree filter" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="egress_hoq_stall_high" descr="Number of sequential packets dropped, due to Head-Of-Queue \;Lifetime Limit, that causes the port to enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="egress_hoq_stall_low" descr="Number of sequential packets dropped, due to Head-Of-Queue \;Lifetime Limit, that causes the port to enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="egress_sll_high" descr="Number of packets dropped, because the Switch Lifetime Limit \;was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="egress_sll_low" descr="Number of packets dropped, because the Switch Lifetime Limit \;was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ingress_discard_all_high" descr="Number of packets dropped, because of any reason.\; Note: see description in the description area for limitations of \;this counter.\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ingress_discard_all_low" descr="Number of packets dropped, because of any reason.\; Note: see description in the description area for limitations of \;this counter.\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x7C.0" size="0x4.0" />
</node>

<node name="eth_extended_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="port_transmit_wait_high" descr="The time (in 4ns resolution) during which the port selected had \;data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="port_transmit_wait_low" descr="The time (in 4ns resolution) during which the port selected had \;data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_high" descr="A count of packets marked as ECN or potentially marked as \;ECN.\;ECN Counting enable/disable is configurable. \;Valid only for Spectrum family.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_low" descr="A count of packets marked as ECN or potentially marked as \;ECN.\;ECN Counting enable/disable is configurable. \;Valid only for Spectrum family.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_high" descr="The number of multicast packets dropped due to lack of egress \;buffer resources.\;Valid only for Spectrum.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_low" descr="The number of multicast packets dropped due to lack of egress \;buffer resources.\;Valid only for Spectrum.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="rx_ebp_high" descr="The number of received EBP packets.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="rx_ebp_low" descr="The number of received EBP packets.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="tx_ebp_high" descr="The number of transmitted EBP packets.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="tx_ebp_low" descr="The number of transmitted EBP packets.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_high" descr="The number of events where the port rx buffer has passed a full\;ness threshold \;\;Reserved for Switches." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_low" descr="The number of events where the port rx buffer has passed a full\;ness threshold \;\;Reserved for Switches." access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="rx_buffer_full_high" descr="The number of events where the port rx buffer has reached 100% \;fullness \;\;Reserved for Switches." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="rx_buffer_full_low" descr="The number of events where the port rx buffer has reached 100% \;fullness \;\;Reserved for Switches." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_high" descr="The number of roce packets with ICRC error\;\;Reserved for Switches." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_low" descr="The number of roce packets with ICRC error\;\;Reserved for Switches." access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_high" descr="The total number of packets (including bad packets) transmitted \;that were 64 octets in length (excluding framing bits but includ\;ing FCS octets)." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_low" descr="The total number of packets (including bad packets) transmitted \;that were 64 octets in length (excluding framing bits but includ\;ing FCS octets)." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 65 and 127 octets in length (excluding fram\;ing bits but including FCS octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 65 and 127 octets in length (excluding fram\;ing bits but including FCS octets)." access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 128 and 255 octets in length (excluding fram\;ing bits but including FCS octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 128 and 255 octets in length (excluding fram\;ing bits but including FCS octets)." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 256 and 511 octets in length (excluding fram\;ing bits but including FCS octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 256 and 511 octets in length (excluding fram\;ing bits but including FCS octets)." access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 512 and 1023 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 512 and 1023 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 1024 and 1518 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 1024 and 1518 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 1519 and 2047 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 1519 and 2047 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 2048 and 4095 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 2048 and 4095 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 4096 and 8191 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 4096 and 8191 octets in length (excluding \;framing bits but including FCS octets)." access="RO" offset="0x94.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad packets) transmitted \;that were between 8192 and 10239 octets in length (excluding \;framing bits but including FCS octets).transmitted\;" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_low" descr="The total number of packets (including bad packets) transmitted \;that were between 8192 and 10239 octets in length (excluding \;framing bits but including FCS octets).transmitted\;" access="RO" offset="0x9C.0" size="0x4.0" />
</node>

<node name="eth_only_router_ext" descr="" size="0x3f8.0" >
	<field name="router_interface_list" descr="Router Interface List.\;Encoding of this field depends on the type field.\;For Ethernet Only, \;If (type==Ethernet Only), each bit in the bit vector indi\;cates if the router interface indexed by the bit location is a \;member of the group\;If (type==Ethernet and IPoIB), each DWORD might \;include a single router interface number with a pointer to \;the Adjacency table used for Multicast Adjacency for \;IPoIB Multicast" access="RW" high_bound="127" low_bound="0" offset="0x0.0" size="0x200.0" />
</node>

<node name="eth_oob_port_cntrs_ext" descr="" size="0xf8.0" >
	<field name="if_in_ucast_pkts_high" descr="The number of packets successfully received, which were not addressed \;to a multicast or broadcast MAC address.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_low" descr="The number of packets successfully received, which were not addressed \;to a multicast or broadcast MAC address.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="if_in_octets_high" descr="The total number of octets received, including framing characters. Includ\;ing MAC control frames.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="if_in_octets_low" descr="The total number of octets received, including framing characters. Includ\;ing MAC control frames.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="if_in_discards_high" descr="The number of inbound packets which were chosen to be discarded even \;though no errors had been detected to prevent their being deliverable to a \;higher-layer protocol.\;\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="if_in_discards_low" descr="The number of inbound packets which were chosen to be discarded even \;though no errors had been detected to prevent their being deliverable to a \;higher-layer protocol.\;\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="if_in_errors_high" descr="The number of inbound packets that contained errors preventing them \;from being deliverable to a higher-layer protocol. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="if_in_errors_low" descr="The number of inbound packets that contained errors preventing them \;from being deliverable to a higher-layer protocol. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_high" descr="e total number of packets received that had a length (excluding framing \;bits, but including FCS octets) of between 64 and MTU octets, inclusive, \;but had either a bad frame check sequence (FCS) with an integral number \;of octets (FCS error) or a bad FCS with a non-integral number of octets \;(alignment error).\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_low" descr="e total number of packets received that had a length (excluding framing \;bits, but including FCS octets) of between 64 and MTU octets, inclusive, \;but had either a bad frame check sequence (FCS) with an integral number \;of octets (FCS error) or a bad FCS with a non-integral number of octets \;(alignment error).\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_high" descr="The total number of packets received that were less than 64 octets long \;(excluding framing bits, but including FCS octets) and were otherwise \;well formed.\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_low" descr="The total number of packets received that were less than 64 octets long \;(excluding framing bits, but including FCS octets) and were otherwise \;well formed.\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_high" descr="The total number of packets received that were longer than MTU octets \;(excluding framing bits, but including FCS octets) but were otherwise \;well formed.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_low" descr="The total number of packets received that were longer than MTU octets \;(excluding framing bits, but including FCS octets) but were otherwise \;well formed.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_high" descr="he number of times the receiving media is non-idle (a carrier event) for a \;period of time equal to or greater than minFrameSize, and during which \;there was at least one occurrence of an event that causes the PHY to indi\;cate &quot;Receive Error&quot;.\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_low" descr="he number of times the receiving media is non-idle (a carrier event) for a \;period of time equal to or greater than minFrameSize, and during which \;there was at least one occurrence of an event that causes the PHY to indi\;cate &quot;Receive Error&quot;.\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="dot3in_pause_frames_high" descr="A count of MAC Control frames received with an opcode indicating the \;PAUSE operation.\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="dot3in_pause_frames_low" descr="A count of MAC Control frames received with an opcode indicating the \;PAUSE operation.\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_high" descr="A count of MAC Control frames received that contain an opcode that is \;not supported.\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_low" descr="A count of MAC Control frames received that contain an opcode that is \;not supported.\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_high" descr="The total number of packets that higher-level protocols requested be \;transmitted and were not addressed to a multicast or broadcast MAC \;address, including those that were discarded or not sent.\;\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_low" descr="The total number of packets that higher-level protocols requested be \;transmitted and were not addressed to a multicast or broadcast MAC \;address, including those that were discarded or not sent.\;\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="if_out_octets_high" descr="The total number of octets transmitted out of the interface, including \;framing characters.\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="if_out_octets_low" descr="The total number of octets transmitted out of the interface, including \;framing characters.\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="dot3out_pause_frames_high" descr="A count of MAC Control frames transmitted with an opcode indicating \;the PAUSE operation.\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="dot3out_pause_frames_low" descr="A count of MAC Control frames transmitted with an opcode indicating \;the PAUSE operation.\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="if_out_errors_high" descr="The number of outbound packets that could not be transmitted because of \;errors.\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="if_out_errors_low" descr="The number of outbound packets that could not be transmitted because of \;errors.\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="phy_time_since_last_clear_high" descr="The time passed since the last phy counters clear event in msec." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="phy_time_since_last_clear_low" descr="The time passed since the last phy counters clear event in msec." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="phy_received_bits_high" descr="This counter provides information on the total amount of traffic (bits) \;received." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="phy_received_bits_low" descr="This counter provides information on the total amount of traffic (bits) \;received." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="phy_symbol_errors_high" descr="This counter provides information on error bits." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="phy_symbol_errors_low" descr="This counter provides information on error bits." access="RO" offset="0x84.0" size="0x4.0" />
</node>

<node name="eth_per_prio_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="rx_octets_high" descr="The total number of octets received, including framing characters.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="rx_octets_low" descr="The total number of octets received, including framing characters.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="rx_frames_high" descr="The total number of packets received for this priority (including control \;frames).\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="rx_frames_low" descr="The total number of packets received for this priority (including control \;frames).\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_octets_high" descr="The total number of octets transmitted, including framing characters.\;\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="tx_octets_low" descr="The total number of octets transmitted, including framing characters.\;\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="tx_frames_high" descr="The total number of packets transmitted.\;\;\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="tx_frames_low" descr="The total number of packets transmitted.\;\;\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="rx_pause_high" descr="The total number of PAUSE frames received from the far-end port.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="rx_pause_low" descr="The total number of PAUSE frames received from the far-end port.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="rx_pause_duration_high" descr="The total time in microseconds that transmission of packets to the far-end \;port have been paused.\;\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="rx_pause_duration_low" descr="The total time in microseconds that transmission of packets to the far-end \;port have been paused.\;\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="tx_pause_high" descr="The total number of PAUSE or PFC frames sent to the far-end port.\;\;\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_pause_low" descr="The total number of PAUSE or PFC frames sent to the far-end port.\;\;\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_pause_duration_high" descr="The total time in microseconds that the far-end port have been requested \;to pause.\;\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_pause_duration_low" descr="The total time in microseconds that the far-end port have been requested \;to pause.\;\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="rx_pause_transition_high" descr="Counts the number of transitions from Xoff to Xon.\;\;" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="rx_pause_transition_low" descr="Counts the number of transitions from Xoff to Xon.\;\;" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rx_discards_high" descr="The number of inbound packets which were chosen to be discarded even \;though no errors had been detected to prevent their being deliverable to a \;higher-layer protocol.\;\;\;\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rx_discards_low" descr="The number of inbound packets which were chosen to be discarded even \;though no errors had been detected to prevent their being deliverable to a \;higher-layer protocol.\;\;\;\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period longer \;than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all events on all pri\;orities (including global pause)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_low" descr="The number of times the device detected a stalled state for a period longer \;than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all events on all pri\;orities (including global pause)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period longer \;than device_stall_critical_watermark\;The counter is presented in priority 0, but is a sum of all events on all pri\;orities (including global pause).\;" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_low" descr="The number of times the device detected a stalled state for a period longer \;than device_stall_critical_watermark\;The counter is presented in priority 0, but is a sum of all events on all pri\;orities (including global pause).\;" access="RO" offset="0x8C.0" size="0x4.0" />
</node>

<node name="eth_per_receive_buffer_grp_ext" descr="" size="0xf8.0" >
	<field name="rx_no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of ingress shared \;buffer resources. \;Not supported by Spectrum.\;Supported by Spectrum-2." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="rx_no_buffer_discard_uc_low" descr="The number of unicast packets dropped due to lack of ingress shared \;buffer resources. \;Not supported by Spectrum.\;Supported by Spectrum-2." access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_cong_layout_ext" descr="" size="0xf8.0" >
	<field name="wred_discard_high" descr="The number of packet that are dropped by the Weighted Random \;Early Detection (WRED) function.\;For switches - valid only for Spectrum and on\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="wred_discard_low" descr="The number of packet that are dropped by the Weighted Random \;Early Detection (WRED) function.\;For switches - valid only for Spectrum and on\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_tc_high" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;For switches - valid only for Spectrum-3 and on\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_tc_low" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;For switches - valid only for Spectrum-3 and on\;\;" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_layout_ext" descr="" size="0xf8.0" >
	<field name="transmit_queue_high" descr="Contains the transmit queue depth in bytes on traffic class selected \;by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="transmit_queue_low" descr="Contains the transmit queue depth in bytes on traffic class selected \;by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of shared buffer \;resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_low" descr="The number of unicast packets dropped due to lack of shared buffer \;resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="ets" descr="" size="0x8.0" >
	<field name="bw_allocation" descr="For SwitchX/-2:\;The percentage of bandwidth guaranteed to TClass within its \;TClass Group.\;The sum of bw_allocation value across all TClasses within one \;group must equal 100.\;" access="RW" offset="0x0.0" size="0x0.7" />
	<field name="group" descr="TClass Group assigned to a TClass.\;Range 0..7\;0x8 value indicates no TClass Group is assigned to the TClass." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="r" descr="Rate limit update. Enables update of the rate limiter (with the max\;_bw_units, max_bw_value). If this bit is cleared, the rate limiter \;value will not change." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="b" descr="Bandwidth allocation update. Enables update of the ETS band\;width allocation (with the bw_allocation). If this bit is cleared, the \;bandwidth allocation value will not change." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="g" descr="Group update. Enables update of the group assigned to the TClass. \;If this bit is cleared, the group value will not change." access="WO" offset="0x0.31" size="0x0.1" />
	<field name="max_bw_value" descr="The maximal bandwidth allowed for the use TClass\;Units according to max_bw_units\;Reserved when max_bw_units = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_bw_units" descr="Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response returns value in units that allow the most \;accurate number, not in the units configured using Set()." access="RW" enum="DISABLED=0x0,HUNDREDS_MBPS=0x3,GBPS=0x4" offset="0x4.16" size="0x0.4" />
</node>

<node name="ets_global" descr="" size="0x8.0" >
	<field name="r" descr="Rate limit update. Enables update of the rate limiter (with the max\;_bw_units, max_bw_value). If this bit is cleared, the rate limiter \;value will not change." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="max_bw_value" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow the most \;accurate number, not in the units configured using Set()." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_bw_units" descr="The maximal bandwidth allowed for the use for the port\;Encoding of max_bw_units:\;0x0: DISABLED - rate limiter disabled\;0x3: HUNDREDS_MBPS - max_bw_value is in 100 Mbps units\;0x4: GBPS - max_bw_value is in 1 Gbps units\;Note - Query response will return value in units that allow the most \;accurate number, not in the units configured using Set()." access="RW" enum="DISABLED=0x0,HUNDREDS_MBPS=0x3,GBPS=0x4" offset="0x4.16" size="0x0.4" />
</node>

<node name="fid_router_ext" descr="" size="0x18.0" >
	<field name="fid" descr="FID\;Used to connect a bridge to the router. \;When ubridge = 0 only FIDs from the vFID range are \;supported\;Note: when ubridge = 1 this is the egress-fid for router to \;bridge\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="swid" descr="Switch Partition ID" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="router_interface_mac_47_32" descr="Router interface MAC address.\;Note: in SwitchX silicon family, all router interfaces on \;the same switch partition MUST have the same MAC \;address. \;In Spectrum-1 device, all MAC addresses must have the \;same 38 MSBits\;In Spectrum-2 device, all MAC addresses must have the \;same 36 MSBits" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="mac_profile_id" descr="MAC msb profile ID\;range 0 .. cap_max_rif_mac_profile-1\;Reserved when Spectrum-1" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="router_interface_mac_31_0" descr="Router interface MAC address.\;Note: in SwitchX silicon family, all router interfaces on \;the same switch partition MUST have the same MAC \;address. \;In Spectrum-1 device, all MAC addresses must have the \;same 38 MSBits\;In Spectrum-2 device, all MAC addresses must have the \;same 36 MSBits" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="vrrp_id_ipv4" descr="VRRP ID for IPv4\;Reserved when SwitchX/-2. The MAD address should \;be entered to the FDB" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="vrrp_id_ipv6" descr="VRRP ID for IPv6\;Reserved when SwitchX/-2. The MAD address should \;be entered to the FDB" access="RW" offset="0x14.8" size="0x0.8" />
</node>

<node name="flush_per_fid_ext" descr="" size="0x8.0" >
	<field name="fid" descr="When ubridge = 0, for router sub-port interface, FID is cap_fid + \;rif \;Otherwise, valid range is 1..cap_fid-1" access="INDEX" offset="0x4.0" size="0x0.16" />
</node>

<node name="flush_per_lag_and_fid_ext" descr="" size="0x8.0" >
	<field name="lag_id" descr="" access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="fid" descr="" access="INDEX" offset="0x4.0" size="0x0.16" />
</node>

<node name="flush_per_lag_ext" descr="" size="0x8.0" >
	<field name="lag_id" descr="" access="INDEX" offset="0x4.0" size="0x0.10" />
</node>

<node name="flush_per_port_and_fid_ext" descr="" size="0x8.0" >
	<field name="system_port" descr="" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="fid" descr="" access="INDEX" offset="0x4.0" size="0x0.16" />
</node>

<node name="flush_per_port_ext" descr="" size="0x8.0" >
	<field name="system_port" descr="" access="INDEX" offset="0x4.0" size="0x0.16" />
</node>

<node name="fore_ext" descr="" size="0xc.0" >
	<field name="fan_under_limit" descr="Fan speed is below the low limit defined in MFSL register. Each \;bit relates to a single tachometer and indicates the specific tachom\;eter reading is below the threshold." access="RO" offset="0x0.16" size="0x0.10" />
	<field name="fan_over_limit" descr="Fan speed is above the high limit defined in MFSL register. Each \;bit relates to a single tachometer and indicates the specific tachom\;eter reading is above the threshold." access="RO" offset="0x4.16" size="0x0.10" />
</node>

<node name="hcap_ext" descr="" size="0x14.0" >
	<field name="max_cpu_ingress_tclass" descr="Maximum number of CPU ingress traffic classes supported" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="max_num_trap_groups" descr="Maximum number of trap groups supported" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="max_num_dr_paths" descr="Maximum number of direct route (DR) paths in the DR Path \;table." access="RO" offset="0x10.0" size="0x0.4" />
</node>

<node name="hcot_ext" descr="" size="0x30.0" >
	<field name="trap_id" descr="Trap_id\;Allowed trap_id&apos;s:\;240h..243h: CONFT_SWITCH_0..3\;250h..253h: CONFT_ROUTER_0..3\;260h..263h: CONFT_SWITCH_ENC_0..3\;270h..273h: CONFT_SWITCH_DEC_0..3 // overlay switch" access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="key_type" descr="Key types:\;0: ethertype\;1: next_proto\;2: layer4_port\;3: icmp_igmp_type" access="RW" enum="ethertype=0x0,next_proto=0x1,layer4_port=0x2,icmp_igmp_type=0x3" offset="0x4.0" size="0x0.8" />
	<field name="key" descr="Used bits according to key_type.\;E.g. when key_type=0 then only 16 lsb are used\;if key_type=0 then the key is explained in Table 226, &quot;HCOT \;Key_type Ethertype Layout,&quot; on page 397\;if key_type=1 then the key is explained in Table 228, &quot;HCOT \;Key_type Next_proto Layout,&quot; on page 398\;if key_type=2 then the key is explained in Table 230, &quot;HCOT \;Key_type layer4_port Layout,&quot; on page 399\;if key_type=3 then the key is explained in Table 232, &quot;HCOT \;Key_type Icmp_Igmp_Type Layout,&quot; on page 400\;" subnode="hcot_key_auto_ext" access="RW" offset="0x10.0" size="0x10.0" union_selector="$(parent).key_type" />
	<field name="mask" descr="Note: all fields must have a mask with the same value for the \;whole field. Example etherype field which is 16bits must have all \;16bits with same mask value\;if key_type=0 then the mask is explained in Table 226, &quot;HCOT \;Key_type Ethertype Layout,&quot; on page 397\;if key_type=1 then the mask is explained in Table 228, &quot;HCOT \;Key_type Next_proto Layout,&quot; on page 398\;if key_type=2 then the mask is explained in Table 230, &quot;HCOT \;Key_type layer4_port Layout,&quot; on page 399\;if key_type=3 then the mask is explained in Table 232, &quot;HCOT \;Key_type Icmp_Igmp_Type Layout,&quot; on page 400" subnode="hcot_mask_auto_ext" access="RW" offset="0x20.0" size="0x10.0" union_selector="$(parent).key_type" />
</node>

<node name="hcot_key_auto_ext" descr="" attr_is_union="1" size="0x10.0" >
	<field name="hcot_key_ethernet_ext" descr="" subnode="hcot_key_ethernet_ext" offset="0x0.0" selected_by="ethertype" size="0x10.0" />
	<field name="hcot_key_next_proto_ext" descr="" subnode="hcot_key_next_proto_ext" offset="0x0.0" selected_by="next_proto" size="0x10.0" />
	<field name="hcot_key_layer4_port_ext" descr="" subnode="hcot_key_layer4_port_ext" offset="0x0.0" selected_by="layer4_port" size="0x10.0" />
	<field name="hcot_key_icmp_igmp_type_ext" descr="" subnode="hcot_key_icmp_igmp_type_ext" offset="0x0.0" selected_by="icmp_igmp_type" size="0x10.0" />
</node>

<node name="hcot_key_ethernet_ext" descr="" size="0x10.0" >
	<field name="ethertype" descr="The first Ethertype that doesn&quot;t point to either:\;VLAN, CNTAG or configurable Ethertype" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="tunnel_port" descr="Tunnel port:\;1: NVE\;2: VPLS\;4: Flex_tunnel0\;8: Flex_tunnel1\;\;This field cannot be masked\;Reserved when trap_id is not CONFT_SWITCH_ENC_0..3" access="RW" enum="NVE=0x1,VPLS=0x2,Flex_tunnel0=0x4,Flex_tunnel1=0x8" offset="0x4.0" size="0x0.4" />
</node>

<node name="hcot_key_icmp_igmp_type_ext" descr="" size="0x10.0" >
	<field name="min" descr="Minimum range for packet type field\;Must not be masked" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="max" descr="Maximum range for packet type field\;Must not be masked" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="is_ipv4" descr="0: Packet is IPv6\;1: Packet is IPv4" access="RW" offset="0x0.16" size="0x0.1" />
	<field name="is_igmp" descr="0: Packet is ICMP\;1: Packet is IGMP. Reserved when is_ipv4=0" access="RW" offset="0x0.17" size="0x0.1" />
	<field name="tunnel_port" descr="Tunnel port:\;1: NVE\;2: VPLS\;4: Flex_tunnel0\;8: Flex_tunnel1\;\;\;This field cannot be masked\;Reserved when trap_id is not CONFT_SWITCH_ENC_0..3" access="RW" enum="NVE=0x1,VPLS=0x2,Flex_tunnel0=0x4,Flex_tunnel1=0x8" offset="0x4.0" size="0x0.4" />
</node>

<node name="hcot_key_layer4_port_ext" descr="" size="0x10.0" >
	<field name="l4_port" descr="When UDP: destination port \;When TCP: match on destination port or on source port" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="is_ipv4" descr="0: Packet is IPv6\;1: Packet is IPv4" access="RW" offset="0x0.16" size="0x0.1" />
	<field name="is_udp" descr="0: Packet is TCP\;1: Packet is UDP" access="RW" offset="0x0.17" size="0x0.1" />
	<field name="tunnel_port" descr="Tunnel port:\;1: NVE\;2: VPLS\;4: Flex_tunnel0\;8: Flex_tunnel1\;\;\;This field cannot be masked\;Reserved when trap_id is not CONFT_SWITCH_ENC_0..3" access="RW" enum="NVE=0x1,VPLS=0x2,Flex_tunnel0=0x4,Flex_tunnel1=0x8" offset="0x4.0" size="0x0.4" />
</node>

<node name="hcot_key_next_proto_ext" descr="" size="0x10.0" >
	<field name="ip_proto" descr="For IPv4: next_ protocol\;For IPv6: next header" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="is_ipv4" descr="0: Packet is IPv6\;1: Packet is IPv4" access="RW" offset="0x0.16" size="0x0.1" />
	<field name="tunnel_port" descr="Tunnel port:\;1: NVE\;2: VPLS\;4: Flex_tunnel0\;8: Flex_tunnel1\;\;\;This field cannot be masked\;Reserved when trap_id is not CONFT_SWITCH_ENC_0..3" access="RW" enum="NVE=0x1,VPLS=0x2,Flex_tunnel0=0x4,Flex_tunnel1=0x8" offset="0x4.0" size="0x0.4" />
</node>

<node name="hcot_mask_auto_ext" descr="" attr_is_union="1" size="0x10.0" >
	<field name="hcot_key_ethernet_ext" descr="" subnode="hcot_key_ethernet_ext" offset="0x0.0" selected_by="ethertype" size="0x10.0" />
	<field name="hcot_key_next_proto_ext" descr="" subnode="hcot_key_next_proto_ext" offset="0x0.0" selected_by="next_proto" size="0x10.0" />
	<field name="hcot_key_layer4_port_ext" descr="" subnode="hcot_key_layer4_port_ext" offset="0x0.0" selected_by="layer4_port" size="0x10.0" />
	<field name="hcot_key_icmp_igmp_type_ext" descr="" subnode="hcot_key_icmp_igmp_type_ext" offset="0x0.0" selected_by="icmp_igmp_type" size="0x10.0" />
</node>

<node name="hctr_ext" descr="" size="0x10.0" >
	<field name="custom_trap_index" descr="Custom Trap:\;0: IP2ME_CUSTOM0\;1: IP2ME_CUSTOM1\;2: IP2ME_CUSTOM2, reserved when Spectrum-1\;3: IP2ME_CUSTOM3, reserved when Spectrum-1" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="udp_dport" descr="Extraction point is udp dport" access="RW" offset="0x4.1" size="0x0.1" />
	<field name="tcp_sport" descr="Extraction point is tcp sport" access="RW" offset="0x4.2" size="0x0.1" />
	<field name="tcp_dport" descr="Extraction point is tcp dport" access="RW" offset="0x4.3" size="0x0.1" />
	<field name="range_min" descr="Minimum range" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="range_max" descr="Maximum range" access="RW" offset="0xC.0" size="0x0.16" />
</node>

<node name="hgcr_ext" descr="" size="0x8.0" >
	<field name="truncation_size" descr="Truncation Size.\;For packets of trap_ids where HPKT.tr_en=1\;Sets the packet size after truncation (when truncation is enabled). \;Unit is 1 byte.\;Default is 16K-1 (no truncation)\;For Switch-IB2: Granularity is 32B. \;For Spectrum-2/3: Granularity is 4B.\;Reserved when Switch-IB and Spectrum-1 (no truncation).\;For Switch-IB2: minimum value is 32B\;For Quantum and Spectrum-2: minimum value is 48B\;" access="RW" offset="0x0.0" size="0x0.13" />
</node>

<node name="hmcb_ext" descr="" size="0x10.0" >
	<field name="mc_index" descr="Index to the start point in the database where there are pointers to \;multicast identifiers.\;For Spectrum: index to KVD Central Database, see Appendix \;A.3.1.2, &quot;KVD Central Database Linear Entries&quot; (page 2254)" access="RW" offset="0x4.0" size="0x0.24" />
</node>

<node name="hmon_ext" descr="" size="0x220.0" >
	<field name="crdq" descr="Clear RDQ\;Range 0.. cap_max_num_rdq - 1\;Reserved when clr = 0\;Reserved when cprdq = 0\;Reserved when Spectrum-1\;Note: all counters are read regardless of cprdq and crdq" access="INDEX" offset="0x0.0" size="0x0.6" />
	<field name="cprdq" descr="Per RDQ:\;0: CLEAR_ALL: clear all counters of all RDQs\;1: CLEAR_PER_RDQ: clear counter of RQD crdq\;Reserved when clr = 0\;Reserved when Spectrum-1" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="wqe_of_wrap" descr="WQE overflow wrap around. The wqe_overflow had a wrap \;around\;Reserved when Spectrum-2\;" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="wqe_overflow_high" descr="WQE overflow for sum of all RDQs\;Spectrum-1: 8bit rolling counter\;Reserved when Spectrum-2\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="wqe_overflow_low" descr="WQE overflow for sum of all RDQs\;Spectrum-1: 8bit rolling counter\;Reserved when Spectrum-2\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="wqe_overflow_rdq" descr="See Table 216, &quot;HMON - wqe_overflow_rdq Layout,&quot; on \;page 390\;Entries above cap_max_num_rdq are not valid\;Reserved when SwitchX/-2, Switch-IB/2, Spectrum-1" subnode="uint64" access="RW" high_bound="63" low_bound="0" offset="0x20.0" size="0x200.0" />
</node>

<node name="hopf_ext" descr="" size="0x14.0" >
	<field name="flow_number" descr="For send flows: Packet Send Flow (PSF)\;For receive flow: Packet Receive Flow (PRF)\;\;Note that the PSFs are a shared resource with SDQs\;Note that the PRFs are a shared resource with RDQs\;For send flows: range from 0..cap_max_num_sdq-1\;For send flows: range from 0..cap_max_num_rdq-1" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="cqe_ver" descr="CQE Version\;0: CQE Version 1\;1: CQE Version 2\;Reserved when sr = 1 (SEND)\;Informative: for OOB there is no CQE on SEND flow. On \;RECEIVE flow the CQE is appended to the begging of the pack\;etReserved when profile cqe_version is 0\;Reserved when SwitchX/-2, Switch-IB/2" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="sr" descr="Send/receive\;0: RECEIVE Packet Flow\;1: SEND Packet Flow" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="i_f" descr="Interface:\;0: OOB Ethernet link 0\;1: OOB Ethernet link 1\;Note: does not affect when ETHEMAD trap_id (interface accord\;ing to EMAD send interface)\;" access="RW" offset="0x4.0" size="0x0.3" />
	<field name="vport" descr="Send Virtual port\;0: port0\;1: VHCA portReserved when sr = 0 (RECEIVE)\;Reserved when SwitchX/-2" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="cpu_tclass" descr="Send Flow: CPU Egress TClass\;Reserved when sr = 0 (RECEIVE)\;Range is 0.. cap_max_cpu_egress_tclass-1\;Reserved when Switch-IB/2 and Quantum" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="rcv_cpu_tclass" descr="Reserved when sr = 1 (SEND)\;Receive Flow: per Interface (per OOB0,1) CPU Ingress Traffic \;Class\;Range is 0.. cap_max_oob_cpu_ingress_tclass-1\;Note: for different pcp values the rcv_cpu_tclass must be differ\;ent\;Reserved when SwitchX/-2" access="RW" offset="0x4.24" size="0x0.4" />
	<field name="mac_47_32" descr="Destination Mac address associated with the specific packet flow \;(used by the device to send packets to).\;Note: for Switch-IB/2 and Quantum: the 42 msb bits must be the \;same for all packet_flow . The last configured mac will modify \;the msb for all macs of all packet_flow.\;Note: does not affect when ETHEMAD trap_id (DMAC accord\;ing to EMAD send SMAC)\;Reserved when sr = 1 (SEND)" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="mac_31_0" descr="Destination Mac address associated with the specific packet flow \;(used by the device to send packets to).\;Note: for Switch-IB/2 and Quantum: the 42 msb bits must be the \;same for all packet_flow . The last configured mac will modify \;the msb for all macs of all packet_flow.\;Note: does not affect when ETHEMAD trap_id (DMAC accord\;ing to EMAD send SMAC)\;Reserved when sr = 1 (SEND)" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="vid" descr="VLAN ID\;For receive flows, adds the VID to the OOB packet\;Range 0.. cap_max_oob_vid \;Reserved when vlan_ex = 0\;Reserved when sr = 1 (SEND)\;Reserved when SwitchX/-2" access="RW" offset="0x10.0" size="0x0.12" />
	<field name="pcp" descr="For receive flows, adds the PCP to the OOB packet\;Reserved when vlan_ex = 0\;Reserved when sr = 1 (SEND)\;Reserved when SwitchX/-2\;" access="RW" offset="0x10.12" size="0x0.3" />
	<field name="dei" descr="For receive flows, adds the DEI to the OOB packet\;Reserved when vlan_ex = 0\;Reserved when sr = 1 (SEND)\;Reserved when SwitchX/-2" access="RW" offset="0x10.15" size="0x0.1" />
	<field name="vlan_ex" descr="Vlan tag exists\;0: no VLAN tag\;1: with a VLAN tag\;For receive flows, adds a vlan_tag to the OOB packet\;Reserved when sr = 1 (SEND)\;Reserved when SwitchX/-2" access="RW" offset="0x10.16" size="0x0.1" />
</node>

<node name="hpkt_ext" descr="" size="0x10.0" >
	<field name="trap_id" descr="Trap ID to configure. See Table 89, &quot;TRAP IDs,&quot; on page 263.\;Note: A trap_id can only be associated with a single trap_group. \;The SwitchX will associate the trap_id with the last trap_group \;configured.\;Note: for SwitchX/-2, Switch-IB/2 and Spectrum-1 the range is \;0..255." access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="trap_group" descr="Trap group configured for trap_id\;Range 0.. cap_max_num_trap_groups - 1\;For Switch-X/2: Range 0.. HCAP.max_num_trap_groups -1\;Reserved when ((action is NOP) and (trap_id is not Soure trap) \;and (trap_id is not Event trap))" access="RW" offset="0x0.12" size="0x0.6" />
	<field name="action" descr="Action to perform on trap_id\;0: NOP - packet will be forwarded by the switch based on normal \;switching rules. The packet may get other traps \;1: TRAP - CPU receives the sole copy\;2: MIRROR_TO_CPU - CPU receives a replica of the packet, \;Reserved when Switch-IB/2 and Quantum\;3: DISCARD_ERROR\;4: SOFT_DISCARD_ERROR - allows other traps and allows Pol\;icy Engine to set Forward rule. Not supported by SwitchX/-2\;5: TRAP_AND_SOFT_DISCARD_ERROR - allows other traps to \;overwrite this trap and allows Policy Engine to set Forward rule. \;Not supported by SwitchX/-2, Switch-IB/2 and Quantum\;6: EXCEPTION_TRAP - CPU receives the sole copy and an error \;is counted. Not supported by SwitchX/-2, Switch-IB/2 and Quan\;tum\;7: FWD_DISCARD_ERROR - same as DISCARD_ERROR but \;allows previous traps (if were). \;15: SET_FW_DEFAULT - set the FW_Default value. Must not be \;used for trap_ids which do not have a FW_Default. This value is a \;WO.\;\;This field is reserved when trap_id&apos;s are Source traps, see Source \;trap column in Table 89, &quot;TRAP IDs,&quot; on page 263\;This field is reserved when trap_id&apos;s are Event traps, see Event trap \;column in Table 89, &quot;TRAP IDs,&quot; on page 263" access="RW" enum="NOP=0x0,TRAP=0x1,MIRROR_TO_CPU=0x2,DISCARD_ERROR=0x3,SOFT_DISCARD_ERROR=0x4,TRAP_AND_SOFT_DISCARD_ERROR=0x5,EXCEPTION_TRAP=0x6,FWD_DISCARD_ERROR=0x7,SET_FW_DEFAULT=0xf" offset="0x0.20" size="0x0.4" />
	<field name="tr_en" descr="Truncation enabled\;0: no truncation\;1: truncation enabled\;Truncation size is according to HGCR.truncation_size\;Reserved when SwitchX/-2, Switch-IB/2 and Spectrum-1" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="ctrl" descr="Control Packet\;Packets configured as control traffic will use dedicated buffer \;resources. For more details see Section 9.3, &quot;Packet to Buffer Clas\;sification,&quot; on page 1277\;0: Keep factory defaults\;1: Do not use control buffer for this Trap-ID\;2: Use control buffer for the Trap-ID\;Note that not all Trap-IDs can use the control buffer. See the Con\;trol Packet column in Table 89, &quot;TRAP IDs,&quot; on page 263Reserved \;when SwitchX/-2 and Switch-IB/2" access="RW" offset="0x4.16" size="0x0.2" />
</node>

<node name="hrwc_ext" descr="" size="0x220.0" >
	<field name="crdq" descr="Clear RDQ\;Range 0.. cap_max_num_rdq - 1\;Reserved when clr = 0\;Reserved when cprdq = 0\;Note: all counters are read regardless of cprdq and crdq" access="INDEX" offset="0x0.0" size="0x0.6" />
	<field name="cprdq" descr="Per RDQ:\;0: CLEAR_ALL: clear all counters of all RDQs\;1: CLEAR_PER_RDQ: clear counter of RQD crdq\;Reserved when clr = 0" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="rdq_wqe_counter" descr="See Table 218, &quot;HRWC - Host RDQ WQE Counter Register Lay\;out,&quot; on page 391\;Entries above cap_max_num_rdq are not valid" subnode="uint64" access="RW" high_bound="63" low_bound="0" offset="0x20.0" size="0x200.0" />
</node>

<node name="htac_ext" descr="" size="0x30.0" >
	<field name="trap_id" descr="Trap_id\;Allowed trap_id&apos;s:\;ICMPV6_CONF_TYPE0, ICMPV6_CONF_TYPE1,\;NVE_DECAP_ICMPV6_CONF_TYPE,\;NVE_DECAP_ET,\;CONF_ET0, CONF_ET1\;NVE_DECAP_IGMP_CONF_TYPE\;NVE_DECAP_UDP_CONF_TYPE" access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="attributes0" descr="Attributes per trap_id:\;ICMPV6_CONF_TYPE0, ICMPV6_CONF_TYPE1, NVE_DE\;CAP_ICMPV6_CONF_TYPE: ICMP type, 8bits\;CONF_ET0, CONF_ET1: Ethertype, 16bits\;NVE_DECAP_ET: Ethertype0, 16bits\;NVE_DECAP_IGMP_CONF_TYPE: 8bits\;NVE_DECAP_UDP_CONF_TYPE: IPv4 dport: 15:0, enable \;IPv4: bit16\;Lsb&apos;s are at offset 0xC within this field" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="attributes1" descr="Attributes per trap_id:\;ICMPV6_CONF_TYPE0, ICMPV6_CONF_TYPE1, NVE_DE\;CAP_ICMPV6_CONF_TYPE: Reserved\;CONF_ET0, CONF_ET1: Reserved\;NVE_DECAP_ET: Ethertype1, 16bits\;NVE_DECAP_IGMP_CONF_TYPE: Reserved\;NVE_DECAP_UDP_CONF_TYPE: IPv6 dport: 15:0, enable \;IPv6: bit16\;Lsb&apos;s are at offset 0xC within this field" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
</node>

<node name="htgt_ext" descr="" size="0x44.0" >
	<field name="trap_group" descr="Trap group\;Range is 0 .. cap_max_num_trap_groups - 1\;For Switch-X/2: Range 0.. HCAP.max_num_trap_groups -1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="type" descr="CPU path type. See Table 207, &quot;CPU Path Types,&quot; on page 383." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="swid" descr="Switch Partition ID\;Note that event traps have swid value of &apos;254&apos; (all-swid)Reserved \;when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="pid" descr="Policer ID for trap group trap_group.\;Host Interface Policers should be allocated out of the Global Polic\;ers.\;Range is 0..(cap_max_policers_cpu-1)\;Note: the policer affects only packets which are trapped to CPU, \;mirrored packets on trap_group are not subject to policer." access="RW" offset="0x4.0" size="0x0.14" />
	<field name="pide" descr="Policer enable\;For more details about policers, refer to Section 10.7.6, &quot;Policer,&quot; \;on page 1565.\;Note: must not be set for MIRROR_SESSION trap_ids\;" access="RW" offset="0x4.15" size="0x0.1" />
	<field name="mirror_agent" descr="Mirroring port analyzer ID (pa_id), see Section 4.12.1, &quot;MPAT - \;Monitoring Port Analyzer Table,&quot; on page 681\;Reserved when mirror_action is TRAP_TO_CPU" access="RW" offset="0x8.0" size="0x0.3" />
	<field name="mirror_action" descr="Trap Mirror Action\;0: TRAP_TO_CPU (packet is forwarded to the CPU based on the \;path configured) \;1: TRAP_TO_CPU_AND_MIRROR, trap to CPU and Mirror to a \;mirroring agent\;2: TRAP_TO_MIRROR, mirror to mirroring agent and do not trap \;to the CPU.\;Reserved when SwitchX/-2, Switch-IB/2 and Quantum" access="RW" offset="0x8.8" size="0x0.2" />
	<field name="priority" descr="Trap Group Priority\;In case a packet matches multiple classification rules, the packet \;will only be trapped once, based on the Trap-ID associated with the \;group with the highest priority value. Higher values mean higher \;priority.\;Range is 0..cap_max_trap_group_priorities-1\;Reserved when SwitchX/-2, Switch-IB/2 and Quantum. For these \;devices the priority value equals the trap_group value." access="RW" offset="0xC.0" size="0x0.4" />
	<field name="path" descr="Path to designated CPU" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="mirror_probability_rate" descr="For mirroring: sampling rate = 1 out of rate packets \;Valid values are: 1 to 3.5*10^9\;Values of 0 behaves like 1\;Default 1\;Note: high values are round by HW to: 10^9 * {4.3, 2.15, 1.43, \;1.08, 0.86, 0.72, 0.61, 0.54}. \;Reserved when mirror_action is TRAP_TO_CPU\;Reserved when SwitchX/-2, Switch-IB/2, Spectrum-1, Quantum.\;" access="RW" offset="0x40.0" size="0x4.0" />
</node>

<node name="ib_swid_ext" descr="" size="0x24.0" >
	<field name="swid" descr="" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="lid" descr="Base LID of the router interface\;Note: must be aligned with RTCA.lid\;See Section 13.13.23, &quot;RALTA - Router Algorithmic LPM Tree \;Allocation Register,&quot; on page 2001" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="lmc" descr="LMC of the router interface\;Note: must be aligned with RTCA.lmc\;See Section 13.13.23, &quot;RALTA - Router Algorithmic LPM Tree \;Allocation Register,&quot; on page 2001" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="guid" descr="GUID for &quot;GID2ME&quot; on link-local\;" subnode="uint64" access="RW" offset="0xC.0" size="0x8.0" />
</node>

<node name="ibfmr_ext" descr="" size="0x10.0" >
	<field name="atm_v" descr="Attribute Modifier valid\;The attribute_modifier is valid\;" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="attribute_id" descr="Attribute ID of the received MAD\;Supported:\;0x0019: LinearForwardingTable\;0x001B: MulticastForwardingTable" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="attribute_modifier" descr="AttributeModifier of the received MAD" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="ibfmrc_ext" descr="" size="0x4.0" >
	<field name="attr_id_en" descr="Attribute ID enable:\;bit0: 0x0019: LinearForwardingTable\;bit1: 0x001B: MulticastForwardingTable\;" access="RW" offset="0x0.0" size="0x4.0" />
</node>

<node name="icam_reg_ext" descr="" size="0x38.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: REG_IDs 0x3800 to 0x387F\;1: REG_IDs 0x3880 to 0x38FF\;Values 2-255 are reserved." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index : \;0: enhanced features\;Values 1-255 are reserved" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="infr_access_reg_cap_mask" descr="Supported infrastructure&apos;s access register bitmask. Based on \;access_reg_group index. \;When bit is set to &apos;1&apos;, The register is supported in the device. \;For access_reg_group == 0:\;Bit 1: IGCR \;Bit 2: IDDD\;Bit 3: IDDDS\;Bit 4: IEDR\;Bit 5: IEDS\;Bit 16: IFBO - (0x3810)\;Bit 17: IICR\;" access="RO" enum="IGCR=0x2,IDDD=0x4,IDDDS=0x8,IEDR=0x10,IEDS=0x20,IFBO=0x10000,IICR=0x20000" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="infr_feature_cap_mask" descr="Supported infrastructure&apos;s enhanced features. Based on fea\;ture_group index.\;When bit is set to &apos;1&apos;, The feature is supported in the device: \;" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="icsr_ext" descr="" size="0x410.0" >
	<field name="base_address" descr="Base cr-space address for reading" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="num_reads" descr="Number of cr-space consecutive reads.\;EAch read is 4B (DWord)\;Range 1..256" access="OP" offset="0x8.0" size="0x0.9" />
	<field name="data" descr="The cr-space read data" access="RO" high_bound="255" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="iddd_ext" descr="" size="0x8.0" >
	<field name="entry_type" descr="Entry type\;For Spectrum-2 hash entries see Appendix A.4.1.1, &quot;KVD Central \;Database Hash-based&quot; (page 2260)\;For Spectrum-2 linear entries see Appendix A.4.1.2, &quot;KVD Cen\;tral Database Linear Entries&quot; (page 2261)" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="duplication" descr="Duplication\;Valid values:\;1, 2, 4, 8, 16\;Default is 1\;\;" access="RW" offset="0x4.0" size="0x0.5" />
</node>

<node name="iddds_ext" descr="" size="0x440.0" >
	<field name="pipe" descr="Pipe\;See Table 677, &quot;IDDDS - pipe entry Layout,&quot; on page 774" subnode="iddds_pipeline_entry" access="RW" high_bound="15" low_bound="0" offset="0x40.0" size="0x400.0" />
</node>

<node name="iddds_pipeline_entry" descr="" size="0x40.0" >
	<field name="entry_type" descr="Entry type\;Per entry type: read percentage of utilization (lookups/time) in \;database\;Range 0..100\;For Spectrum-2 hash entries see Appendix A.4.1.1, &quot;KVD Central \;Database Hash-based&quot; (page 2260)\;For Spectrum-2 linear entries see Appendix A.4.1.2, &quot;KVD Cen\;tral Database Linear Entries&quot; (page 2261)" access="RO" high_bound="63" low_bound="0" offset="0x0.24" size="0x40.0" />
</node>

<node name="iedr_ext" descr="" size="0x210.0" >
	<field name="num_rec" descr="Number of records\;Range 1..64\;When bg=1 the num_rec =1 and this field is reserved" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="bg" descr="Background delete:\;0: immediate delete operation (a.k.a. sync)\;1: background delete operation (a.k.a. async). SW must poll for \;IEDS.ed_status=0 before attempting new deletes" access="OP" offset="0x0.24" size="0x0.1" />
	<field name="record" descr="See Table 681, &quot;IEDR record Layout,&quot; on page 776" subnode="iedr_record" access="RW" high_bound="63" low_bound="0" offset="0x10.0" size="0x200.0" />
</node>

<node name="iedr_record" descr="" size="0x8.0" >
	<field name="size" descr="Size of entries do be deleted.\;The unit is 1 entry, regardless of entry type\;Range 1..4096" access="OP" offset="0x0.0" size="0x0.13" />
	<field name="type" descr="Resource type\;For Spectrum-2, see Section A.4.1.2, &quot;KVD Central Database Lin\;ear Entries,&quot; on page 2261" access="OP" offset="0x0.24" size="0x0.8" />
	<field name="index_start" descr="Resource index start" access="OP" offset="0x4.0" size="0x0.24" />
</node>

<node name="ieds_ext" descr="" size="0x8.0" >
	<field name="edpr" descr="Entry Delete Priority\;When set FW will give higher priority for the current ongoing \;entry delete process. Can be set also while entry delete process is \;ongoing. Affects only current process. By default all process \;start as low prio\;" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ed_status" descr="Entry delete status:\;0: No entry delete process is ongoing\;1: Entry delete process is ongoing" access="RO" offset="0x4.0" size="0x0.4" />
</node>

<node name="ifbo_ext" descr="" size="0x28.0" >
	<field name="type" descr="Hash type\;2: Random\;3: CRC2\;4: XOR2 - this is a always symmetric hash function, always sym\;metric also for inner fields (L2, L3,L4). \;\;" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="outer_header_enables" descr="Outer header enables. Each bit enables a specific layer field to be \;included in the hash calculation. Layers that are not listed below \;are enabled by default.\;Bit 0: Enable Layer2 fields if packet is not IPv4/6\;Bit 1: Enable Layer2 fields if packet is IPv4\;Bit 2: Enable Layer2 fields if packet is IPv6\;Bit 3: Enable IPv4 fields if packet is not TCP and not UDP\;Bit 4: Enable IPv4 fields if packet is either TCP or UDP\;Bit 5: Enable IPv6 fields if packet is not TCP and not UDP\;Bit 6: Enable IPv6 fields if packet is either TCP or UDP\;Bit 7: Enable TCP/UDP header fields if packet is IPv4\;Bit 8: Enable TCP/UDP header fields if packet is IPv6" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="outer_header_fields_enable" descr="By defaults, all fields are &apos;0&apos;\;Layer2 fields, subject to outer_header_enables:\;Bit 0: SMAC\;Bit 1: DMAC\;Bit 2: Ethertype\;Bit 3: Outer VID\;Bit 4: Outer PCP\;Bit 5: Outer DEI\;Bit 6: Inner VID\;Bit 7: Inner PCP\;Bit 8: Inner DEI\;\;IPv4 fields, subject to outer_header_enables:\;Bits 12:9: IPv4 SIP 0-3 enable per byte. For ARP all bytes are used\;Bits 16:13: IPv4 DIP 0-3 enable per byte. For ARP all bytes are \;used\;Bit 17: IPv4 Protocol\;Bit 18: IPv4 DSCP\;Bit 19: IPv4 ECN\;Bit 20: IPv4 IP L3 Length - length field bits [13:10]\;\;IPv6 fields, subject to outer_header_enables:\;Bits 21: IPv6 enable bytes of SIP 0. For ARP all bytes are used\;Bits 28:22 reserved\;Bits 36:29: IPv6 SIP 8-15 enable per byte. For ARP all bytes are \;used\;Bits 37: IPv6 enable bytes of DIP 0. For ARP all bytes are used\;Bits 44:38 reserved\;Bits 52:45: IPv6 DIP 8-15 enable per byte. For ARP all bytes are \;used\;Bit 53: IPv6 Next Header\;Bit 54: IPv6 DSCP\;Bit 55: IPv6 ECN\;Bit 56: IPv6 IP L3 Length - length field bits [13:10]\;Bit 57: IPv6 Flow label\;\;RoCE v1 fields: [TBD]\;Bit 58: [TBD] GRH SIP\;Bit 59: [TBD] GRH DIP\;Bit 60: [TBD] GRH Next Protocol\;Bit 61: [TBD] GRH DSCP\;Bit 62: [TBD] GRH ECN\;Bit 63: [TBD] GRH L3 Length\;Bit 64: [TBD] GRH Flow label" access="RW" high_bound="4" low_bound="0" offset="0x14.0" size="0x14.0" />
</node>

<node name="igcr_ext" descr="" size="0x10.0" >
	<field name="ddd_lpm_high_ipv4" descr="For DDD for IPv4 LPM\;LPM_High is for routes with prefixes from ddd_lpm_high_ipv4 .. \;32\;LPM_Low is for routes with prefixes from 1 to  ddd_lp\;m_high_ipv4-1\;Range: 1..32, default: 9\;Note: can only be changed when the router is disabled\;" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="ddd_lpm_high_ipv6" descr="For DDD for IPv6 LPM\;LPM_High is for routes with prefixes from ddd_lpm_high_ipv6 .. \;128\;LPM_Low is for routes with prefixes from 1 to ddd_lp\;m_high_ipv6-1\;Range: 1..128, default: 33\;Note: can only be changed when the router is disabled" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="ddd_pe_actions_priority" descr="For DDD on ACL actions\;ACL actions which are pointed by a rule with priority equal to or \;smaller than this value will have DDD\;For example if the value is 0 then only default actions will have \;DDD\;Default 0" access="RW" offset="0x8.0" size="0x0.24" />
	<field name="pisbo" descr="[Spectrum-2-phase2]\;Port isolation bridge only:\;0: port isolation also after router\;1: port isolation does not work if packet was routed\;Note that the NVE isolation (TNIFR) is orthogonal to this configu\;ration\;" access="RW" offset="0xC.0" size="0x0.1" />
</node>

<node name="iicr_ext" descr="" size="0x24.0" >
	<field name="kvh_mark_clear" descr="KVH mark and clear\;0: Nop \;1: Mark all KVH entries (e.g. before FW-ISSU)\;2: Clear (delete) all marked KVH entries (e.g. after FW-ISSU)\;Spectrum-1: mark/delete only KVH hash entries\;Spectrum-2: mark/delete KVH hash and KVH linear entries\;Note: dump sessions must not be ongoing between mark and \;clear. e.g. SFN, SFDD, RAUHTD, PEFAAD, MPNHLFED, \;TNIPSN" access="OP" offset="0x8.0" size="0x0.4" />
	<field name="clear_pe_regions_value" descr="clear (deallocate) policy engine TCAM regions if: \;(1) region[bit] = clear_pe_regions_value[bit] \;(2) and clear_pe_regions_mask[bit]=1\;Note: a used TCAM region must not be cleared (if traffic is pass\;ing through this region). An ACL may point to this unused \;TCAM region.\;If mask=0 then this is a Nop" access="OP" offset="0x10.0" size="0x0.16" />
	<field name="clear_pe_regions_mask" descr="clear (deallocate) policy engine TCAM regions if: \;(1) region[bit] = clear_pe_regions_value[bit] \;(2) and clear_pe_regions_mask[bit]=1\;Note: a used TCAM region must not be cleared (if traffic is pass\;ing through this region). An ACL may point to this unused \;TCAM region.\;If mask=0 then this is a Nop" access="OP" offset="0x14.0" size="0x0.16" />
	<field name="clear_rifs_value" descr="clear (deallocate) router interface (RIF) if: \;(1) rif[bit] = clear_rifs_value[bit] \;(2) and clear_rifs_mask[bit]=1\;Note: a used RIF must not be cleared (if traffic is passing \;through this RIF).\;If mask=0 then this is a Nop" access="OP" offset="0x18.0" size="0x0.16" />
	<field name="clear_rifs_mask" descr="clear (deallocate) router interface (RIF) if: \;(1) rif[bit] = clear_rifs_value[bit] \;(2) and clear_rifs_mask[bit]=1\;Note: a used RIF must not be cleared (if traffic is passing \;through this RIF).\;If mask=0 then this is a Nop" access="OP" offset="0x1C.0" size="0x0.16" />
	<field name="traps_2_default" descr="Set all trap_id&apos;s actions to default as after reset." access="OP" offset="0x20.0" size="0x0.1" />
</node>

<node name="index_dump" descr="" size="0x4.0" >
	<field name="index_dump" descr="" offset="0x0.0" size="0x0.24" />
</node>

<node name="ipinip_encap_adjacency_ext" descr="" size="0x18.0" >
	<field name="ipip_type" descr="Underlay destination ip type:\;0: IPv4, set by ipv4_udip\;1: IPv6, set by ipv6_ptr\;\;Note: the type field (IPv4 or IPv6) must match the configu\;ration of the router interface, see protocol field in \;Table 1931, &quot;Loopback IPinIP Overlay Router Interface \;Properties Layout&quot;" access="RW" offset="0x0.16" size="0x0.4" />
	<field name="ipv4_udip" descr="Underlay ipv4 dip\;Reserved when ipip_type is IPv6" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="ipv6_ptr" descr="Pointer to IPv6 underlay destination ip address\;See Section 13.13.19, &quot;RIPS - Router IP version Six Regis\;ter,&quot; on page 1987\;For Spectrum: Pointer to KVD linear space, see Appendix \;A.4.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2256)" access="RW" offset="0xC.0" size="0x0.24" />
</node>

<node name="ipoib_multicast_adjacency_ext" descr="" size="0x18.0" >
	<field name="dlid" descr="Destination local ID.\;For multicast, this is actually mlid - multicast LID." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="sl" descr="Service level" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="tclass" descr="Traffic class" access="RW" offset="0x8.0" size="0x0.8" />
</node>

<node name="ipoib_pkey_router_ext" descr="" size="0x14.0" >
	<field name="pkey" descr="InfiniBand partition key" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="swid" descr="Switch partition ID" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="scope" descr="Multicast GID scope" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="qkey" descr="Queue key\;Note: All router interfaces must share the same qkey." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="qpn" descr="Local QP used for the IPoIB router interface.\;Note: In SwitchX devices, the QPn allocation must follow the fol\;lowing rules:\;1. QPn used for router interfaces must be allocated sequentially \;where QPn for Router Interface #n must be calculated by\;2. QPn = QPn_base + Router Interface Index" access="RW" offset="0x10.0" size="0x0.24" />
</node>

<node name="ipoib_router_inter_ext" descr="" size="0x3f8.0" >
	<field name="size" descr="Size - the number of valid entries in the list following this field." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="rif_entry" descr="Rif Entry\;For more details, see Table 1947, &quot;rif_entry Layout,&quot; on \;page 1924" access="RW" high_bound="252" low_bound="0" offset="0x4.0" size="0x3f4.0" />
</node>

<node name="ipoib_unicast_with_grh_adjacency_ext" descr="" size="0x18.0" >
	<field name="dlid" descr="Destination local ID" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="sl" descr="Service level" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="my_lid" descr="LID path bits, to be masked by the interface LMC and added to \;the SLID base configured for the router port." access="RW" offset="0x0.24" size="0x0.7" />
	<field name="dqpn" descr="Destination queue pair number" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="dgid" descr="Destination global ID" access="RW" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
</node>

<node name="ipoib_unicast_without_grh_adjacency_ext" descr="" size="0x18.0" >
	<field name="dlid" descr="Destination local ID" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="sl" descr="Service level" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="dqpn" descr="Destination queue pair number" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="my_lid" descr="LID path bits, to be masked by the interface LMC and added to \;the SLID base configured for the router port." access="RW" offset="0x8.0" size="0x0.7" />
</node>

<node name="link_level_retrans_cntr_grp_data_ext" descr="" size="0xf8.0" >
	<field name="llr_rx_cells_high" descr="The total number of cells received (including bad cells)." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="llr_rx_cells_low" descr="The total number of cells received (including bad cells)." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="llr_rx_error_high" descr="The total number of bad cells received (including CRC error).\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="llr_rx_error_low" descr="The total number of bad cells received (including CRC error).\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="llr_rx_crc_error_high" descr="The total number of cells received with CRC error.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="llr_rx_crc_error_low" descr="The total number of cells received with CRC error.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="llr_tx_cells_high" descr="The total number of cells transmitted (including retransmitted cells)." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="llr_tx_cells_low" descr="The total number of cells transmitted (including retransmitted cells)." access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="llr_tx_ret_cells_high" descr="The total number of cells retransmitted." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="llr_tx_ret_cells_low" descr="The total number of cells retransmitted." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="llr_tx_ret_events_high" descr="The total number of retransmission events." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="llr_tx_ret_events_low" descr="The total number of retransmission events." access="RO" offset="0x2C.0" size="0x4.0" />
</node>

<node name="local_span_ext" descr="" size="0x10.0" >
	<field name="tclass" descr="Traffic Class on which the mirrored packet is queued\;For Spectrum: Switch Priority\;Reserved when qos is QoS maintain\;Reserved when system_port is to CPU since HTGT.cpu_tclass is \;used" access="RW" offset="0xC.0" size="0x0.4" />
</node>

<node name="loopback_generic_router_interface_ext" descr="" size="0x4.0" >
</node>

<node name="loopback_ipinip_router_interface_ext" descr="" size="0x1c.0" >
	<field name="uvr" descr="Underlay Virtual Router\;Range is 0..cap_max_virtual_routers-1\;Reserved when Spectrum-2" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="options" descr="When type is IP_IN_GRE_KEY_IN_IP:\;0: The key is defined by gre_key\;1: The 24msbs of the key are set by ipip_gre_key_for_hash, see \;TIGCR. The 8 lsbs of the key are based on a hash value configured \;by RECR or RECR_V2.\;See Section 16.5.1, &quot;TIGCR - Tunneling IPinIP General Configura\;tion Register,&quot; on page 2152, Section 13.13.7, &quot;RECR - Router \;ECMP Configuration Register,&quot; on page 1940, Section 13.13.8, \;&quot;RECR_V2 - Router ECMP Configuration Version 2 Register,&quot; on \;page 1942" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="ipip_type" descr="Encapsulation Type\;0: IP_IN_IP: Tunnel is IPinIP \;1: IP_IN_GRE_IN_IP: Tunnel is GRE, no key\;2: IP_IN_GRE_KEY_IN_IP: Tunnel is GRE, with a key" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="underlay_router_interface" descr="Underlay ingress router interfaceReserved when Spectrum-1\;\;" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="usip" descr="Encapsulation Underlay source IP\;Reserved when protocol is IPv4" access="RW" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="gre_key" descr="GRE Key\;Reserved when ipip_type is not IP_IN_GRE_KEY_IN_IP" access="RW" offset="0x18.0" size="0x4.0" />
</node>

<node name="loopback_router_interface_ext" descr="" size="0x24.0" >
	<field name="protocol" descr="Protocol\;0: IPIP_IPV4 - overlay RIF with underlay of IPinIP IPv4\;1: IPIP_IPV6 - overlay RIF with underlay of IPinIP IPv6\;2: GENERIC \;\;" access="RW" enum="IPIP_IPV4=0x0,IPIP_IPV6=0x1,GENERIC=0x2" offset="0x0.28" size="0x0.4" />
	<field name="rif_loopback_parameters" descr="For protocol = IPIP_IPV4 or protocol = IPIP_IPV6 See Table 1931, \;&quot;Loopback IPinIP Overlay Router Interface Properties Layout,&quot; on \;page 1916\;For protocol GENERIC See Table 1933, &quot;Loopback Generic \;Router Interface Properties Layout,&quot; on page 1917" subnode="loopback_router_interface_rif_loopback_parameters_auto_ext" access="RW" offset="0x8.0" size="0x1c.0" union_selector="$(parent).protocol" />
</node>

<node name="loopback_router_interface_rif_loopback_parameters_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="loopback_ipinip_router_interface_ext" descr="" subnode="loopback_ipinip_router_interface_ext" offset="0x0.0" selected_by="IPIP_IPV4" size="0x1c.0" />
	<field name="loopback_generic_router_interface_ext" descr="" subnode="loopback_generic_router_interface_ext" offset="0x0.0" selected_by="GENERIC" size="0x4.0" />
</node>

<node name="mafcr_ext" descr="" size="0x8.0" >
	<field name="clear" descr="Clear counter_accu_fifo_overflow counter" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="counter_accu_fifo_overflow" descr="Counter of accuflow fifo overflow.\;When system behaves &quot;well&quot; then this counter will always be 0.\;If ((FW polling is too slow) or (HW increment is too high)) then \;the HW accuflow fifo becomes overflowed. In this case new \;accuflow counter increments are not counted.\;This counter is stuck at 0xF...FF" access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="mafri_ext" descr="" size="0x410.0" >
	<field name="num_rec" descr="Number of records to read\;Range 1..128" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="counter_index_base" descr="Counter Index base\;Counters will be read starting at counter_index_base\;Must have a value of 32*N \;Range: cap_start_accuflow .. cap_max_accuflow - 1\;Note: counter_index_base + num_rec must be equal or lower \;than cap_max_accuflow" access="OP" offset="0x4.0" size="0x0.24" />
	<field name="record" descr="See Table 613, &quot;MAFRI - record Layout,&quot; on page 721" subnode="mafri_record" access="RW" high_bound="127" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="mafri_record" descr="" size="0x8.0" >
	<field name="bytes_inc" descr="Bytes to increment to bytes counter\;Unit of 512B\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="packets_inc" descr="Packets to increment to packets counter\;Unit is 4packets\;" access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="mafti_ext" descr="" size="0x410.0" >
	<field name="num_rec" descr="Number of records\;Range 1..64\;\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="bank_id" descr="Bank ID\;" access="RO" offset="0x0.16" size="0x0.3" />
	<field name="record" descr="See Table 609, &quot;MAFTI - record Layout,&quot; on page 718" subnode="mafti_record" access="RW" high_bound="63" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="mafti_record" descr="" size="0x10.0" >
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum-2 see Section 4.2, &quot;Flow Counters,&quot; on page 622" access="RO" offset="0x0.0" size="0x0.24" />
	<field name="bytes_inc" descr="Bytes to increment to bytes counter\;Unit of 512B\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="packets_inc" descr="Packets to increment to packets counter\;Unit is 4 packets\;" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mcc_reg_ext" descr="" size="0x20.0" >
	<field name="instruction" descr="Command to be executed by the FSM\;0x1: LOCK_UPDATE_HANDLE\;0x2: RELEASE_UPDATE_HANDLE \;0x3: UPDATE_COMPONENT\;0x4: VERIFY_COMPONENT\;0x5: ACTIVATE_COMPONENET \;0x6: ACTIVATE\;0x7: READ_COMPONENT\;0x8: CANCEL\;0x9: CHECK_UPDATE_HANDLE\;0xA: FORCE_HANDLE_RELEASE\;0xB: READ_PENDING_COMPONENT\;Other values are reserved. Applicable for write operation \;only." access="RW" enum="LOCK_UPDATE_HANDLE=0x1,RELEASE_UPDATE_HANDLE=0x2,UPDATE_COMPONENT=0x3,VERIFY_COMPONENT=0x4,ACTIVATE_COMPONENET=0x5,ACTIVATE=0x6,READ_COMPONENT=0x7,CANCEL=0x8,CHECK_UPDATE_HANDLE=0x9,FORCE_HANDLE_RELEASE=0xa,READ_PENDING_COMPONENT=0xb" offset="0x0.0" size="0x0.8" />
	<field name="time_elapsed_since_last_cmd" descr="The number of seconds elapsed since the update_handle \;owner last issued a command. The time saturates at 0xFFF." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="component_index" descr="Index of the accessed component. Valid for \;UPDATE_COMPONENT, ACTIVATE_COMPONENET, \;READ_COMPONENT and READ_PENDING_COMPO\;NENT instructions. Otherwise, this field is reserved." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="update_handle" descr="Token representing the current flow executed by the FSM.\;" access="RW" offset="0x8.0" size="0x0.24" />
	<field name="control_state" descr="Current Update FSM state\;0x0: IDLE\;0x1: LOCKED\;0x2: INITIALIZE\;0x3: DOWNLOAD\;0x4: VERIFY\;0x5: APPLY\;0x6: ACTIVATE\;0x7: UPLOAD\;0x8: UPLOAD_PENDING\;Other values are reserved" access="RO" enum="IDLE=0x0,LOCKED=0x1,INITIALIZE=0x2,DOWNLOAD=0x3,VERIFY=0x4,APPLY=0x5,ACTIVATE=0x6,UPLOAD=0x7,UPLOAD_PENDING=0x8" offset="0xC.0" size="0x0.4" />
	<field name="error_code" descr="Indicates the successful completion of the instruction, or \;the reason it failed. \;0x0: OK\;0x1: ERROR\;0x2: REJECTED_DIGEST_ERR\;0x3: REJECTED_NOT_APPLICABLE\;0x4: REJECTED_UNKNOWN_KEY\;0x5: REJECTED_AUTH_FAILED\;0x6: REJECTED_UNSIGNED\;0x7: REJECTED_KEY_NOT_APPLICABLE\;0x8: REJECTED_BAD_FORMAT\;0x9: BLOCKED_PENDING_RESET\;0xA: REJECTED_NOT_A_SECURED_FW\;0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED\;0xC: REJECTED_NO_DEBUG_TOKEN\;0xD: REJECTED_VERSION_NUM_MISMATCH\;0xE: REJECTED_USER_TIMESTAMP_MISMATCH\;0xF: REJECTED_FORBIDDEN_VERSION\;0x10: FLASH_ERASE_ERROR\;0x11: REJECTED_REBURN_RUNNING_AND_RETRY\;Other values should be treated as an unknown error." access="RO" offset="0xC.8" size="0x0.8" />
	<field name="control_progress" descr="Indicates the estimated progress status of the current opera\;tion executed by the FSM. Valid values are 0..100.\;101 indicates that progress reporting is not supported for \;this update state." access="RO" offset="0xC.16" size="0x0.7" />
	<field name="handle_owner_host_id" descr="For handle_owner_type BMC, command-interface and \;ICMD, indicates the identifier of the host of the handle \;owner.\;Otherwise reserved" access="RO" offset="0xC.24" size="0x0.4" />
	<field name="handle_owner_type" descr="Type of entity holding the update handle:\;0x0: unspecified\;0x1: Chassis BMC\;0x2: MAD\;0x3: BMC\;0x4: command interface\;0x5: ICMD \;Other values are reserved." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="component_size" descr="Component size in bytes. \;Valid for UPDATE_COMPONENT instruction. Specifying \;the size may shorten the update time.\;Value 0x0 means that size is unspecified." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch / NIC\;1: Gearbox" access="INDEX" offset="0x14.0" size="0x0.8" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x14.16" size="0x0.12" />
</node>

<node name="mcda_reg_ext" descr="" size="0x90.0" >
	<field name="update_handle" descr="Update handle registered when the FSM was activated." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="offset" descr="Offset of accessed address relative to component start. \;Accesses must be in accordance to log_mcda_word_size in \;Table 1522, &quot;MCQI CAPABILITIES Info Layout,&quot; on \;page 1646" access="RW" offset="0x4.0" size="0x4.0" />
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
	<field name="status" descr="Module Status\;0h - GOOD\;1h - NO_EEPROM_MODULE. No response from module&apos;s \;EPROM.\;2h - MODULE_NOT_SUPPORTED. Module type not supported \;by the device. \;3h - MODULE_NOT_CONNECTED. No module present indica\;tion. \;9h - I2C_ERROR. Error occurred while trying to access the mod\;ule&apos;s EPROM using I2C.\;10h - MODULE_DISABLED - module is disabled \;[Internal] 11h - Page Access Failed - page not supported or trying \;to access a protected page with bad password." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="l" descr="Lock bit. Setting this bit will lock the access to the specific cable.\;Used for updating a full page in a cable EPROM. Any access \;other then subsequence writes will fail while the port is locked." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="device_address" descr="Device address" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="page_number" descr="Page number" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="i2c_device_address" descr="I2C device address" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="size" descr="Number of bytes to read/write (up to 128 bytes)" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="bank_number" descr="Bank number" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="dword" descr="Bytes to read/write" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
</node>

<node name="mcion_ext" descr="" size="0xc.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_status_bits" descr="Module IO status, as defined by SFF:\;Bit 0 - Present\;Bit 1 - RX_LOS\;Bit 2 - TX_Fault\;\;" access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="mcpp_reg_ext" descr="" size="0x10.0" >
	<field name="enoc" descr="Enable Over Current Events\;Enable power policer according to indication of Over Current \;which is provided by device interface (e.g. OC_WARN pin in \;Spectrum)\;0 - disable \;1 - enable (default)" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="ent" descr="Enable Temperature Events\;Enable power policer according to high temperature\;0 - disable (default)\;1 - enable" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="hysteresis_temperature" descr="Below this temperature the Temperature Event is cleared. Units \;are Celsius\;Default 95\;hysteresis_temperature must be lower or equal to warning_tem\;perature\;Reserved when ent = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="warning_temperature" descr="Above this temperature the Temperature Event is set. Units are \;Celsius\;Default 105\;Reserved when ent = 0" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="wsoc" descr="Warning State due to Over Current Event:\;0 - Yellow_State\;1 - Red_State (default)" access="RW" offset="0x8.30" size="0x0.1" />
	<field name="wst" descr="Warning State due to Temperature Event:\;0 - Yellow_State (default)\;1 - Red_State" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="yellow_state_rate" descr="Port rate at Yellow_State. Units are percentage from Green_State \;port rate\;Default 50" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="red_state_rate" descr="Port rate at Red_State. Units are percentage from Green_State \;port rate\;red_state_rate must be lower or equal to yellow_state_rate\;Default 0" access="RW" offset="0xC.16" size="0x0.8" />
</node>

<node name="mcqi_reg_ext" descr="" size="0x1c.0" >
	<field name="component_index" descr="Component index gathered by &quot;MCQS - Management \;Component Query Status&quot;" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="read_pending_component" descr="When set, the register will return information about the \;pending component (if available)" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch / NIC\;1: Gearbox" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="info_type" descr="Component properties set.\;0x0: CAPABILITIES\;0x1: VERSION\;0x5: ACTIVATION_METHOD\;Other values are reserved" access="RW" enum="CAPABILITIES=0x0,VERSION=0x1,ACTIVATION_METHOD=0x5" offset="0x8.0" size="0x0.5" />
	<field name="info_size" descr="Properties set structure size, given in bytes." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="offset" descr="The requested/returned data offset from the section start, \;given in bytes.\;Must be DWORD aligned." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="data_size" descr="The requested/returned data size, given in bytes.\;If data_size is not DWORD aligned, the last bytes are zero \;padded." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="data" descr="Properties set structure according to info_type.\;CAPABILITIES - See Table 1522, &quot;MCQI CAPABILI\;TIES Info Layout,&quot; on page 1646\;VERSION - See Table 1524, &quot;MCQI VERSION Info Lay\;out,&quot; on page 1648\;ACTIVATION_METHOD - See Table 1528, &quot;MCQI \;ACTIVATION_METHOD Info Layout,&quot; on page 1650" access="RO" high_bound="VARIABLE" low_bound="0" offset="0x18.0" size="0x4.0" />
</node>

<node name="mcqs_reg_ext" descr="" size="0x10.0" >
	<field name="component_index" descr="Component Index. Values range from 1 to the last compo\;nent indicated by last_index_flag." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="last_index_flag" descr="When set, this component is the last component (highest \;component_index)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="identifier" descr="This field uniquely identifies a specific component type. \;0x1: BOOT_IMG\;0x4: OEM_NVCONFIG\;0x5: MLNX_NVCONFIG\;0x6: CS_TOKEN\;0x7: DBG_TOKEN\;0xA: Gearbox\;0xB: CC_ALGO - Congestion Control Algorithm\;\;Other values are reserved" access="RO" enum="BOOT_IMG=0x1,OEM_NVCONFIG=0x4,MLNX_NVCONFIG=0x5,CS_TOKEN=0x6,DBG_TOKEN=0x7,Gearbox=0xa,CC_ALGO=0xb" offset="0x4.0" size="0x0.16" />
	<field name="component_update_state" descr="Component statue in update flow\;0x0: IDLE\;0x1: IN_PROGRESS\;0x2: APPLIED\;0x3: ACTIVE \;0x4: ACTIVE_PENDING_RESET\;0x5: FAILED\;0x6: CANCELED\;0x7: BUSY\;\;Other values are reserved" access="RO" enum="IDLE=0x0,IN_PROGRESS=0x1,APPLIED=0x2,ACTIVE=0x3,ACTIVE_PENDING_RESET=0x4,FAILED=0x5,CANCELED=0x6,BUSY=0x7" offset="0x8.0" size="0x0.4" />
	<field name="component_status" descr="The status of the component:\;0x0: NOT_PRESENT - The component is supported by the \;device but, currently not present\;0x1: PRESENT - This component is present.\;0x2: IN_USE - The component is present and currently in \;use.\;\;Other values are reserved" access="RO" enum="NOT_PRESENT=0x0,PRESENT=0x1,IN_USE=0x2" offset="0x8.4" size="0x0.5" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" offset="0xC.0" size="0x0.8" />
	<field name="last_update_state_changer_host_id" descr="For last_update_state_changer_type BMC, command-\;interface and ICMD, indicates the identifier of the host of \;the handle owner. Otherwise reserved." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="last_update_state_changer_type" descr="Indicates which entity was the last to change the compo\;nent_update_state of this component.\;0x0: unspecified\;0x1: Chassis_BMC\;0x2: MAD\;0x3: BMC\;0x4: command_interface\;0x5: ICMD\;\;Other values are reserved" access="RO" enum="unspecified=0x0,Chassis_BMC=0x1,MAD=0x2,BMC=0x3,command_interface=0x4,ICMD=0x5" offset="0xC.28" size="0x0.4" />
</node>

<node name="mdcr_ext" descr="" size="0x60.0" >
	<field name="device_type" descr="Peripheral device type\;1: XM" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="device_status_data" descr="Device initialization Data. \;For XM status, see Table 1546, &quot;MDCR - XM Data Layout,&quot; on \;page 1662" subnode="mdcr_xm_data" access="RO" offset="0x10.0" size="0x50.0" />
</node>

<node name="mdcr_xm_data" descr="" size="0x50.0" >
	<field name="xm_status" descr="XM load status.\;0: Pending\;1: No connection (At least 1 of the two Ethernet ports is not up)\;2: Version mismatch (major and minor are different from major_\;expected and minor_expected)\;3: Loaded successfully" access="RO" offset="0x0.20" size="0x0.4" />
	<field name="xm_major" descr="XM major version" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="xm_minor" descr="XM minor version" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="xm_build_id" descr="XM build ID" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="xm_expected_major" descr="XM expected major version" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="xm_expected_minor" descr="XM expected minor version" access="RO" offset="0x14.0" size="0x0.16" />
</node>

<node name="mddt_reg_ext" descr="" size="0x110.0" >
	<field name="device_index" descr="Device index" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="type" descr="0: PRM Register\;1: Command\;2-3: Reserved" access="OP" offset="0x4.0" size="0x0.2" />
	<field name="write_size" descr="Write size in D-Words." access="OP" offset="0x4.16" size="0x0.8" />
	<field name="read_size" descr="Read size in D-Words." access="OP" offset="0x4.24" size="0x0.8" />
	<field name="payload" descr="Payload\;For PRM Register type payload- See Table 1550, &quot;PRM \;Register Payload Layout,&quot; on page 1664\;For Command type payload - See Table 1552, &quot;Command \;Payload Layout,&quot; on page 1665" subnode="prm_register_payload" access="RW" offset="0x10.0" size="0x100.0" />
</node>

<node name="mdfcr_reg_ext" descr="" size="0x60.0" >
	<field name="device_type" descr="Peripheral device type\;1: Vega_Gearbox\;2: Tile" access="INDEX" enum="Vega_Gearbox=0x1,Tile=0x2" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="all" descr="All devices are selected and device_index is ignored\;When set to &apos;1&apos;, the fw_status should represent the worst case of \;any of the devices. fw_version, build_id, major and minor should \;be of device number 0." access="INDEX" offset="0x4.31" size="0x0.1" />
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
	<field name="slot_index" descr="Slot index" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="all" descr="All devices are selected and device_index is ignored\;When set to &apos;1&apos;, the rst_status should represent the worst case of \;any of the devices." access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="rst_op" descr="Reset Operation.\;0: Query of the reset status which is displayed through rst_status.\;1: Full Reset of the selected device(s).\;2-8: Reserved." access="RW" offset="0xC.0" size="0x0.3" />
	<field name="rst_status" descr="Reset status.\;0: Reset completed successfully. 1: Reset operation has not finished \;yet." access="RO" offset="0xC.16" size="0x0.4" />
</node>

<node name="mdri_ext" descr="" size="0x120.0" >
	<field name="clear" descr="Per bit:\;Bit 0: clear global_reasons\;Bit 1: clear port_reasons\;Bit 2: clear buffer_reasons\;Bit 3: clear ethernet_reasons\;Bit 4: clear ip_reasons\;Bit 5: clear mpls_reasons\;Bit 6: clear tunnel_reasons\;Bit 7: clear host_reasons" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="read" descr="Per bit:\;Bit 0: read global_reasons\;Bit 1: read port_reasons\;Bit 2: read buffer_reasons\;Bit 3: read ethernet_reasons\;Bit 4: read ip_reasons\;Bit 5: read mpls_reasons\;Bit 6: read tunnel_reasons\;Bit 7: read host_reasons" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="global_reasons" descr="Bit0: TCAM ECC Error (had a correctable ECC error)\;Bit1: no egress port (e.g. MC group is empty, port-isolation)\;\;Bit3: MAFCR.counter_accu_fifo_overflow was incremented (this \;is not a disacrd, but it&apos;s a bad behaviour)" access="RO" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="port_reasons" descr="Bit0: receive buffer overflow\;\;Bit1: egress mtu error" access="RO" high_bound="7" low_bound="0" offset="0x40.0" size="0x20.0" />
	<field name="buffer_reasons" descr="Bit0: sll" access="RO" high_bound="7" low_bound="0" offset="0x60.0" size="0x20.0" />
	<field name="ethernet_reasons" descr="Bit0: smac is mc\;Bit1: smac equal dmac\;Bit2: invalid ethertype (0x05DC &lt; ethertype &lt; 0x600)Bit3: ingress \;spanning tree\;Bit4: fdb_miss, same as trap_id FDB_MISS\;Bit5: fdb_mismatch, same as trap_id FDB_MISMATCH\;Bit6: fid miss, same as trap_id FID_MISS" access="RO" high_bound="7" low_bound="0" offset="0x80.0" size="0x20.0" />
	<field name="ip_reasons" descr="Bit0: packet to router is not ip/mpls/arp (no ip header)\;Bit1: disabled irif \;Bit2: uc dip over mc or bc mac\;Bit3: dip is loopback address \;for ipv6: (dip==::1/128) || (dip==0:0:0:0:0:ffff:7f00:0/104)\;for ipv4: dip==127.0.0.0/8\;Bit4: sip is mc \;for ipv6: (SIP == FF00::/8)\;for ipv4: (SIP == 224.0.0.0: 239.255.255.255 aka 224.0.0.0/4)\;Bit5: sip is in class e\;(pkt is ipv4) &amp;&amp; (sip == 240.0.0.0/4) &amp;&amp; (sip != 255.255.255.255)\;Bit6: sip is loopback\;for ipv6: sip == ::1/128\;for ipv4: sip == 127.0.0.0/8\;Bit7: sip is unspecified\;for ipv6: sip == ::0\;for ipv4: sip == 0.0.0.0/32\;Bit8: ip header not okay (IPVer, checksum, IHL)Bit9: mc mac mis\;match\;\;Bit10: sip equal dip\;Bit11: ipv4 sip is limited broadcast\;Bit12: lpm no route uc ipv4\;Bit13: lpm no route uc ipv6\;Bit14: uc dip is link local, same as trap_id&apos;s DIS\;CARD_ING_ROUTER_DIP_LINK_LOCAL, IPV6_LINK_LO\;CAL_DEST\;Bit15: sip is link local, same as trap_id&apos;s DISCARD_ING_ROUT\;ER_SIP_LINK_LOCAL, IPV6_LINK_LOCAL_SRC\;Bit16: mc egress mtu aggregated\;Bit17: mc RPF \;Bit18: uc RPF Bit20: IPv4 dip is limited broadcast (dip==bc)\;Bit21: IPv4 dip is local network (dip == 0.0.0.0/8)\;Bit22: NVE packet to overlay router \;\;Bit23: mc dip over uc mac\;Bit24: mc dip is link local, same as trap_id: LOCALNETWORK, \;IPV6_MC_LINK_LOCALDEST\;Bit25: ingress MTU (this check is configured as forward)\;Bit26: mc egress mtu, (both for UC and for MC, MPLS)\;Bit29: ttl_error, same as trap_id TTLERROR\;Bit30: disabled erif \;\;Bit31: host miss ipv4, same as trap_id HOST_MISS_IPV4\;Bit32: host miss ipv6, same as trap_id HOST_MISS_IPV6\;Bit33: loopback error, same as trap_id LBERROR\;Bit34: ipv6 dip is unspecified, dip==::0/128, same as trap_id" access="RO" high_bound="7" low_bound="0" offset="0xA0.0" size="0x20.0" />
	<field name="mpls_reasons" descr="Bit0: outer label is not valid\;\;Bit1: no IP after decap (or after php)\;\;Bit3: mpls uc Ethertype (0x8847) over mc or bc mac\;Bit4: mpls mc Ethertype over not allowed mac\;Bit5: MPLS min ingress label allowed (label too low)\;Bit6: MPLS max ingress label allowed (label too high)\;Bit7: ReservedBit8: php decap and no ip header or ip header is not \;okay\;\;Bit9: ilm miss, same as trap_id MPLS_ILM_MISS\;Bit10: mpls loopback filter" access="RO" high_bound="7" low_bound="0" offset="0xC0.0" size="0x20.0" />
	<field name="tunnel_reasons" descr="Bit0: decap_encap_prevention - same as trap_id DECAP_ENCAP\;Bit1: ipip_tunnel_loop \;\;Bit2: reserved\;\;Bit3: ipip_decap_error - same as trap_id IPIP_DECAP_ERROR\;Bit4: ipip_error - same as trap_id IPIP_ERROR. For Spectrum-2 \;catches nothing \;Bit7: nve_decap_frag_error - same as trap_id NVE_DECAP_\;FRAG_ERROR\;Bit8: overlay_port_isolation - see TNIFR\;\;Bit10: overlay_smac_is_mc\;Bit11: overlay_smac_equal_dmac\;Bit12: overlay_is_too_short - (decap remains with short packet)\;Bit13: decap_underlay_is_too_long - (decap of more than 126 \;bytes)\;\;Bit14: nve_decap_error - same as trap_id NVE_DECAP \;_TAG_ERROR\;Bit15: decap_ecn - same as trap_id DECAP_ECN0, \;DECAP_ECN1\;" access="RO" high_bound="7" low_bound="0" offset="0xE0.0" size="0x20.0" />
	<field name="host_reasons" descr="Bit0: tx_base_header_is_wrong - (version or base type)\;Bit1: tx_base_header_system_port_is_out_of_range" access="RO" high_bound="7" low_bound="0" offset="0x100.0" size="0x20.0" />
</node>

<node name="mdsr_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0: The debug session ended successfully\;1: Failed to execute the operation. See additional_info for more \;details.\;2-15: Reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="additional_info" descr="0: No additional information available \;1: There is no debug session in progress\;2: FW is not secured, debug session cannot be ended\;3: Fail - Request was sent from a different host that the one that \;issued the debug session\;4: Fail - Host is not allowed to query debug session" access="RO" offset="0x0.8" size="0x0.6" />
	<field name="end" descr="Set to &apos;1&apos; to end debug session." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="merr_ext" descr="" size="0x14.0" >
	<field name="ent_type" descr="Entity type.\;0: Reserved\;1: QSFP Module (the relevant signals are: present, reset, interrupt, \;power enable, low power mode, power good, modsel, QSFP \;LEDs)" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="current_index" descr="Current entity index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Slot index." access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="target_index" descr="Entity number to be mapped to." access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="mfba_reg_ext" descr="" size="0x10c.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="The size of the data to be written or read in bytes\;Should comply with block_size and block_alignment fields in \;MFPA." access="WO" offset="0x4.0" size="0x0.9" />
	<field name="address" descr="The start address of this read or write access in bytes. Should comply \;with block_size and block_alignment fields in MFPA." access="INDEX" offset="0x8.0" size="0x4.0" />
	<field name="data" descr="The data to be written or read data." access="RW" high_bound="63" low_bound="0" offset="0xC.0" size="0x100.0" />
</node>

<node name="mfbe_reg_ext" descr="" size="0xc.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device. \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="bulk_64kb_erase" descr="Erase a 64KB flash area in one bulk operation." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="bulk_32kb_erase" descr="Erase a 32KB flash area in one bulk operation." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="address" descr="The start address (in bytes) of this erase operation. Must be aligned \;with the selected erase size (sector, 32KB or 64KB)." access="INDEX" offset="0x8.0" size="0x4.0" />
</node>

<node name="mfcr_ext" descr="" size="0x8.0" >
	<field name="pwm_frequency" descr="Controls the frequency of the PWM signal.\;Supported frequencies are:\;0x0: 11Hz \;0x1: 14.7Hz\;0x2: 22.1Hz\;0x3 - 0111111: Reserved\;0x40: 1.4KHz\;0x41: 5KHz\;0x42: 20KHz\;0x43: 22.5KHz\;0x44: 25KHz\;0x45 - 0x7F: Reserved" access="RW" offset="0x0.0" size="0x0.7" />
	<field name="pwm_active" descr="Indicates which of the PWM control is active (bit per PWM)" access="RO" offset="0x4.0" size="0x0.5" />
	<field name="tacho_active" descr="Indicates which of the tachometer is active (bit per tachometer)" access="RO" offset="0x4.16" size="0x0.10" />
</node>

<node name="mfm_ext" descr="" size="0x18.0" >
	<field name="index" descr="Index to the fabric memory table." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="memory_high" descr="Holds software-written data.\;Default value: 0x0\;Device reset will reset to the default value." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="memory_low" descr="Holds software-written data.\;Default value: 0x0\;Device reset will reset to the default value." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="memory_mask_high" descr="On write commands, indicates which of the bits from memory \;field are updated. Reserved on read operations." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="memory_mask_low" descr="On write commands, indicates which of the bits from memory \;field are updated. Reserved on read operations." access="WO" offset="0x14.0" size="0x4.0" />
</node>

<node name="mfmc_reg_ext" descr="" size="0x1c.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device. \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="wrp_block_count" descr="Power of 2 of the write protect block count\;0: 1 block\;1: 2 blocks\;2: 4 blocks\;3: 8 blocks etc.\;Range 0..5\;Note that per flash device there may be invalid configurations\;Reserved when wrp_en = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="block_size" descr="Block size\;0: write protect sub-sector blocks\;1: write protect sector blocks\;Reserved when wrp_en = 0\;Note that not all block sizes are supported on all flash device, need \;to check MFPA capabilities" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="wrp_en" descr="Write protect enable\;Set write protect of flash device" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="sub_sector_protect_size" descr="Power of 2 for sub_sector size in 4Kbytes.\;0: 4Kbyte.\;1: 8 Kbyte\;2: 16Kbyte.\;Etc." access="RO" offset="0x8.0" size="0x0.6" />
	<field name="sector_protect_size" descr="Power of 2 for sector size in 4Kbytes.\;0: 4Kbyte.\;1: 8 Kbyte\;2: 16Kbyte.\;Etc." access="RO" offset="0x8.8" size="0x0.6" />
	<field name="quad_en" descr="Quad enable IO bit in the device status register" access="RW" offset="0x10.24" size="0x0.1" />
	<field name="dummy_clock_cycles" descr="The number of dummy clock cycles subsequent to all FAST READ \;commands. \;Reserved if not supported by the device" access="RW" offset="0x18.0" size="0x0.4" />
</node>

<node name="mfnr_ext" descr="" size="0x30.0" >
	<field name="fan_index" descr="Fan tachometer index." access="INDEX" offset="0x0.0" size="0x0.5" />
	<field name="serial_number" descr="Fan serial number (ASCII string)\;Value of &apos;0&apos;: Some error (Fan not present, disconnected etc.)" access="RO" high_bound="5" low_bound="0" offset="0x4.0" size="0x18.0" />
	<field name="part_number" descr="Fan part number (ASCII string)\;Value of &apos;0&apos;: Some error (Fan not present, disconnected etc.)" access="RO" high_bound="4" low_bound="0" offset="0x1C.0" size="0x14.0" />
</node>

<node name="mfpa_reg_ext" descr="" size="0x20.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device.\;Range between 0 .. flash_num -1\;" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, boot_address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="boot_address" descr="The flash address from which the firmware will boot in the next reset \;(warm start)." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="flash_num" descr="The number of flash devices\;1: there is 1 flash device, etc." access="RO" offset="0x10.0" size="0x0.4" />
	<field name="sub_sector_wrp_en" descr="If set, MFMC register supports setting write protect with sub-sector- \;blocks\;Sub-sector block size is available in MFMC.sub_sector_protect_size" access="RO" offset="0x10.16" size="0x0.1" />
	<field name="sector_wrp_en" descr="If set, MFMC register supports setting write protect with sector \;blocks.\;Sector block size is available in MFMC.sector_protect_size" access="RO" offset="0x10.17" size="0x0.1" />
	<field name="bulk_64kb_erase_en" descr="If set, MFBE register supports 64KB bulk erase operation.\;" access="RO" offset="0x10.29" size="0x0.1" />
	<field name="bulk_32kb_erase_en" descr="If set, MFBE register supports 32KB bulk erase operation." access="RO" offset="0x10.30" size="0x0.1" />
	<field name="wip" descr="Work In Progress. Indicates that the flash is currently busy." access="RO" offset="0x10.31" size="0x0.1" />
	<field name="jedec_id" descr="Return the flash JEDEC ID value returned by the standard Read \;JEDEC ID command that is available in most flash devices." access="RO" offset="0x14.0" size="0x0.24" />
	<field name="sector_size" descr="The minimal unit that can be erased with and MFBE command (in \;bytes)." access="RO" offset="0x18.0" size="0x0.10" />
	<field name="block_alignment" descr="Log 2 of the requested write alignment in bytes. Write access to the \;flash\;must not cross this alignment.\;Read and write access must be aligned to this value." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="block_size" descr="The block size in byes of the flash device, max read size for MFBA \;(typically 128 bytes)." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="capability_mask" descr="Bitmask indicates which capabilities are supported.\;Bit 15..0: reserved \;\;Bit 16: Set write protect supported (register MFMC supports setting \;write protection)\;Bit 17: quad enable read write is supported (register MFMC supports \;setting quad enable)\;Bit 18: set dummy cycle supported (register MFMC supports setting \;dummy cycles)" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mfrl_reg_ext" descr="" size="0x8.0" >
	<field name="reset_level" descr="The firmware reset level. See &quot;MFRL - Management Firmware \;Reset Level&quot; on page 1671\;Only a single bit may be set.\;Bit 0: LEVEL0\;Bit 3: LEVEL3\;Bit 6: LEVEL6\;Other bits are reserved." access="RW" enum="LEVEL0=0x1,LEVEL3=0x8,LEVEL6=0x40" offset="0x4.0" size="0x0.8" />
	<field name="reset_type" descr="Each bit represents a chip reset type.\;If set to &apos;1&apos;, the reset is supported. \;Bit 0: Full chip reset\;Bit 1: Port alive" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="rst_type_sel" descr="The requested reset." access="RW" offset="0x4.24" size="0x0.3" />
	<field name="pci_sync_for_fw_update_resp" descr="Response of the driver for the reset request.\;1: Acknowledgment\;2: Dis-acknowledgment\;3: Reserved" access="WO" enum="Acknowledgment=0x1,Dis=0x2,Reserved=0x3" offset="0x4.27" size="0x0.2" />
	<field name="pci_sync_for_fw_update_start" descr="Setting this bit to &apos;1&apos; will request a synced driver flow and &apos;0&apos; for \;the legacy flow" access="WO" offset="0x4.29" size="0x0.1" />
</node>

<node name="mfsc_ext" descr="" size="0x8.0" >
	<field name="pwm" descr="Fan pwm to control / monitor" access="INDEX" offset="0x0.24" size="0x0.3" />
	<field name="pwm_duty_cycle" descr="Controls the duty cycle of the PWM. Value range from 0..255 to \;represent duty cycle of 0%...100%" access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="mfsl_ext" descr="" size="0xc.0" >
	<field name="ie" descr="Interrupt Enable. If the ie bit is set and the Tachometer reading is out \;of range as defined by tach_min and tach_max, the FERR# will be \;asserted." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="ee" descr="Event Enable.\;0 - Do not generate event\;1 - Generate Event \;2 - Generate single event\;For Fan Error Evet details refer to Section  28.23.5, &quot;FORE - Fan Out \;of Range Event&quot;." access="RW" offset="0x0.2" size="0x0.2" />
	<field name="tacho" descr="Fan tachometer index" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="tach_min" descr="Tachometer minimum value (minimum RPM)." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="tach_max" descr="Tachometer maximum value (maximum RPM)." access="RW" offset="0x8.0" size="0x0.16" />
</node>

<node name="mfsm_ext" descr="" size="0x8.0" >
	<field name="n" descr="" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="tacho" descr="Fan tachometer index" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rpm" descr="Fan speed (round per minute) calculated based on the time measure\;ment between n fan pulses.\;Note that in order for the RPM to be correct, the n value should cor\;respond to the number of tach pulses per rotation measured by the \;tachometer." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="mgcr_reg_ext" descr="" size="0x20.0" >
	<field name="segment" descr="The GPIO segment which the command&apos;s parameters apply" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="segments_count" descr="Ceiling function of total number of GPIOs / 32 in the system." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="GPIO_data_in" descr="Input value of accessible GPIO[i] signals.\;When GPIO_access_en[i] = 0, GPIO_data_in[i] always returns 0" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="GPIO_data_out" descr="Output value of accessible GPIO signals.\;When GPIO_access_en[i] = 0, GPIO_data_out[i] always returns \;0" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="GPIO_set" descr="These 2 fields are used together to control GPIO signals in the fol\;lowing manner:\;GPIO_set[i]=0, GPIO_clear[i]=0 : GPIO_data_out[i] = No \;Change\;GPIO_set[i]=0, GPIO_clear[i]=1 : GPIO_data_out[i] = 0\;GPIO_set[i]=1, GPIO_clear[i]=0 : GPIO_data_out[i] = 1\;GPIO_set[i]=1, GPIO_clear[i]=1 : GPIO_data_out[i] = not(GPI\;O_data_out[i])\;Ignored for non-controllable GPIO signals." access="WO" offset="0xC.0" size="0x4.0" />
	<field name="GPIO_clear" descr="These 2 fields are used together to control GPIO signals in the fol\;lowing manner:\;GPIO_set[i]=0, GPIO_clear[i]=0 : GPIO_data_out[i] = No \;Change\;GPIO_set[i]=0, GPIO_clear[i]=1 : GPIO_data_out[i] = 0\;GPIO_set[i]=1, GPIO_clear[i]=0 : GPIO_data_out[i] = 1\;GPIO_set[i]=1, GPIO_clear[i]=1 : GPIO_data_out[i] = not(GPI\;O_data_out[i])\;Ignored for non-controllable GPIO signals." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="GPIO_access_en" descr="Access allowance to the corresponding GPIO signal.\;0: GPIO[i] is not observable / controllable by the host SW.\;1: GPIO[i] is observable / controllable by the host SW." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="direction" descr="0: GPIO[i] is an input only signal\;1: GPIO[i] is an output signal. Data out can be updates by the host \;SW and data in can be queried by the host SW.\;For non-accessible GPIOs, the corresponding value is 0." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="drive_type" descr="0: GPIO[i] is an open drain output. The device can only drive the \;GPIO[i] output pin low when GPIO_data_out[i] is 0. When GPI\;O_data_out[i] is 1, GPIO[i] is in HighZ. \;1: GPIO[i] is a full-drive output pin\;When GPIO_access_en[i] =0, direction[i] and drive_type[i] are \;always read as 0." access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see Table 1415, &quot;Hardware Info Layout,&quot; \;on page 1573" subnode="mgir_hardware_info" access="RW" offset="0x0.0" size="0x20.0" />
	<field name="fw_info" descr="Firmware Information, see Table 1417, &quot;Firmware Info Layout,&quot; \;on page 1574" subnode="mgir_fw_info" access="RW" offset="0x20.0" size="0x40.0" />
	<field name="sw_info" descr="Software Information, see Table 1419, &quot;Software Info Layout,&quot; \;on page 1577\;This field indicates the oldest software version compatible \;with the current firmware" subnode="mgir_sw_info" access="RW" offset="0x60.0" size="0x20.0" />
</node>

<node name="mgir_fw_info" descr="" size="0x40.0" >
	<field name="sub_minor" descr="Sub-minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_sub_minor." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_minor." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_major." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="secured" descr="When set, the device is running firmware with secure-\;firmware updates capabilities." access="RO" offset="0x0.24" size="0x0.1" />
	<field name="signed_fw" descr="When set the device is running a signed FW binaries." access="RO" offset="0x0.25" size="0x0.1" />
	<field name="debug" descr="When set, the device is running a debug firmware. \;&apos;debug&apos; binary can only be installed on specific devices \;(identified by their &apos;Factory base MAC&apos;), which currently \;run a specific firmware version. These restrictions are \;expressed by a signed &apos;debug&apos; token that must be loaded \;to the device before installing the debug binary." access="RO" offset="0x0.26" size="0x0.1" />
	<field name="dev" descr="When set, the device is running a development firmware \;version." access="RO" offset="0x0.27" size="0x0.1" />
	<field name="string_tlv" descr="When set, string-TLV is supported." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="build_id" descr="Firmware Build ID. Optional. ." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="year" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= 0x05, \;Day= 0x03, and Year= 0x04" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="day" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= 0x05, \;Day= 0x03, and Year= 0x04" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="month" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= 0x05, \;Day= 0x03, and Year= 0x04" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="hour" descr="Firmware installation hour.\;For example 17:43 will be coded as 0x1743" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="psid" descr="To be defined later." access="RO" high_bound="15" low_bound="0" offset="0x10.24" size="0x10.0" />
	<field name="ini_file_version" descr="User-configured version number of the current INI file." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="extended_major" descr="FW version&apos;s Major field in extended (32b) format." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="extended_minor" descr="FW version&apos;s Minor field in extended (32b) format." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="extended_sub_minor" descr="FW version&apos;s SubMinor field in extended (32b) format." access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="isfu_major" descr="" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="life_cycle" descr="0: Production\;1: GA Secured\;2: GA Non-Secured\;3: RMA" access="RO" offset="0x34.0" size="0x0.2" />
	<field name="sec_boot" descr="0: Disable\;1: Enable" access="RO" offset="0x34.2" size="0x0.1" />
</node>

<node name="mgir_hardware_info" descr="" size="0x20.0" >
	<field name="device_id" descr="PCI device ID. For specific device IDs, see Table 12, \;&quot;Switch Supported PCI Device IDs,&quot; on page 187" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="device_hw_revision" descr="SwitchX Devices:\;0x00A0: Device step A0, FCC package\;0x00A1: Device step A1, FCC package\;0x00A2: Device step A2, FCC package\;Switch-IB Devices:\;0x00A0: Switch-IB device step A0, FCC package\;0x0000 is a valid value for some devices not included in \;PRM." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="pvs" descr="Process Voltage Scaling\;Maximum supported V_CODE voltage (in 50mV incre\;ments) for the device." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="num_ports" descr="Number of physical port the device supports." access="RO" offset="0x4.16" size="0x0.8" />
	<field name="hw_dev_id" descr="The PCI device-ID of the NIC/HCA in recovery (Live\;fish) mode." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="manufacturing_base_mac_47_32" descr="MSB of the &quot;base&quot; MAC address of the NIC that was allo\;cate during manufacturing. The NIC derives the MAC \;addresses for the different PCI PFs from this MAC \;address. This parameter can be used as a canonical unique \;identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not sup\;ported." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="manufacturing_base_mac_31_0" descr="LSB of the &quot;base&quot; MAC address of the NIC that was allo\;cate during manufacturing. The NIC derives the MAC \;addresses for the different PCI PFs from this MAC \;address. This parameter can be used as a canonical unique \;identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not sup\;ported." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="uptime" descr="Time (in secs.) since last reset0" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgir_sw_info" descr="" size="0x20.0" >
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
	<field name="rom0_version" descr="ROM 0 version." subnode="rom_version" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="rom1_version" descr="ROM 1 version." subnode="rom_version" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="rom2_version" descr="ROM 2version." subnode="rom_version" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="rom3_version" descr="ROM 3 version." subnode="rom_version" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="mgnle_reg_ext" descr="" size="0x20.0" >
	<field name="le_pointer" descr="Pointer to the log entry (see description above for more \;information)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="lost_events" descr="The number of events that the system failed to log since the \;previous log entry.\;15 should be interpreted as &apos;15 or more events were lost&apos;" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="synced_time" descr="0x0: Boot - time is measured since NIC bootup.\;0x1: Synced - time was synced by the host." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="time_h" descr="The 32 MSB of the 64bit timestamp.  In microseconds\;When &quot;time_synced&quot; bit is set this is the time passed since the \;1/1/1970 epoch.\;When &quot;time_synced&quot; is cleared this is the NIC uptime." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_l" descr="The 32 LSB of the 64bit timestamp.  In microseconds" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item" access="RO" offset="0x10.0" size="0xc.0" />
	<field name="log_data" descr="The logged data. Format is  different per the according to the \;log type." access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgpc_ext" descr="" size="0x18.0" >
	<field name="counter_index" descr="counter index\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Range 0 .. cap_shared_counter_pool_size - 1" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622" access="OP" offset="0x0.24" size="0x0.8" />
	<field name="opcode" descr="0: Nope\;1: Add counters - add a set of values to the counter set. Valid only \;on Write operation\;2: Flush Counters - when counter set is un-bound, flush ensures \;counters will not be updated due to packets in the pipe. Valid only \;on Write operation\;8: Clear counters. Setting the clr bit will reset the counter value \;for all counters of the specified Router Interface.\;" access="OP" offset="0x4.28" size="0x0.4" />
	<field name="byte_counter" descr="Byte counter value" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="packet_counter" descr="Packet counter value\;Spectrum HW has 58bits for packet counters" subnode="uint64" access="RW" offset="0x10.0" size="0x8.0" />
</node>

<node name="mgpir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see Table 1427, &quot;Hardware Info Layout,&quot; \;on page 1582" subnode="mgpir_hw_info" access="RW" offset="0x0.0" size="0x20.0" />
</node>

<node name="mgpir_hw_info" descr="" size="0x20.0" >
	<field name="num_of_devices" descr="Number of devices of device_type. \;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="devices_per_flash" descr="Number of devices of device_type per flash. \;" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="device_type" descr="Device type.\;0: No devices on system of that type.\;1: Vega gearbox dice\;2: Tiles\;3: AGBM\;4: XM" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="num_of_modules" descr="Number of modules. \;" access="RO" offset="0x4.0" size="0x0.8" />
</node>

<node name="mhmpr_reg_ext" descr="" size="0x14.0" >
	<field name="upm" descr="&apos;0&apos; - if the ports are managed by host.\;&apos;1&apos; - if the ports are not managed by host" access="RW" offset="0x0.0" size="0x0.1" />
</node>

<node name="mhsr_ext" descr="" size="0x8.0" >
	<field name="health" descr="Software health state:\;0 - Failure\;1 - Reserved\;2 - Normal Operation\;3 - Boot / Init (default state)\;Else - Reserved" access="WO" offset="0x0.0" size="0x0.4" />
</node>

<node name="mid" descr="" size="0x4.0" >
	<field name="mid" descr="" offset="0x0.0" size="0x0.16" />
</node>

<node name="mirc_reg_ext" descr="" size="0x8.0" >
	<field name="status_code" descr="Indicates the successful completion of the instruction, or the \;reason it failed. \;0x0: OK\;0x1: BUSY\;0x2: PROHIBITED_FW_VER_ERR\;0x3: FIRST_PAGE_COPY_FAILED\;0x4: FIRST_PAGE_ERASE_FAILED\;0x5: FIRST_PAGE_RESTORE_FAILED\;0x6: CANDIDATE_FW_DEACTIVATION_FAILED\;0x7: FW_ALREADY_ACTIVATED\;0x8: ERROR_DEVICE_RESET_REQUIRED\;0x9: ERROR_FW_PROGRAMMING_NEEDED\;Other values should be treated as an unknown error." access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="mjtag_ext" descr="" size="0x30.0" >
	<field name="size" descr="Size of operation - relevant for JTAG interface access com\;mands only, indicating the number of transaction bytes to exe\;cute. Maximum size supported is 40.\;Note: when size=0, no operation is performed (clock is not tog\;gled). The tdo is sampled and provided in the response at \;jtag_transaction_set_0." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="sequence_number" descr="Command sequence number - to prevent re-execution of the \;same command due to command retransmission, this command \;includes a sequence number.\;The enable and disable commands MUST be issues with \;sequence_number = 0 while any JTAG access command must \;increase the sequence_number by 1 (the first JTAG access com\;mand should start at sequence_number = 1)." access="WO" offset="0x0.24" size="0x0.4" />
	<field name="cmd" descr="Command\;0 - JTAG interface disable - JTAG interface is disabled\;1 - JTAG interface enable - enabling JTAG interface\;2 - JTAG interface access" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="jtag_transaction_set" descr="See Table 1405, &quot;JTAG Transaction Set Byte Layout,&quot; on \;page 1567" access="RW" high_bound="43" low_bound="0" offset="0x4.24" size="0x2c.0" />
</node>

<node name="mlcr_ext" descr="" size="0xc.0" >
	<field name="led_type" descr="Led type (only supported when cap_local_or_uid_only==1.)\;0: LOCALP_AND_UID - local port and uid\;1: UID\;2: LOCALP - local port" access="RW" enum="LOCALP_AND_UID=0x0,UID=0x1,LOCALP=0x2" offset="0x0.0" size="0x0.4" />
	<field name="cap_local_or_uid_only" descr="If set, led_type of type UID and LOCAL Port only are supported." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="operation_cap" descr="If set to &apos;1&apos;, operation field is supported." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="operation" descr="0: Controlled by HW / Beacon\;1: LED on - if bi-color, apply amber.\;2: LED off\;Others: Reserved\;" access="RW" offset="0x0.12" size="0x0.4" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port\;(only supported when cap_local_or_uid_only==1.)" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="beacon_duration" descr="Duration of the beacon to be active, units of seconds\;The value of 0x0 will turn off the beacon\;The value of 0xffff will set the beacon to infinity" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="beacon_remain" descr="Remaining duration of the beacon, units of seconds\;The value of 0xffff means infinity" access="RO" offset="0x8.0" size="0x0.16" />
</node>

<node name="mmia_ext" descr="" size="0xc.0" >
	<field name="operation" descr="0 - NOP\;1 - Erase\;2 - Read\;3 - Write" access="WO" offset="0x0.0" size="0x0.3" />
	<field name="Data" descr="" access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mnvda_reg_ext" descr="" size="0x10.0" >
	<field name="configuration_item_header" descr="" subnode="config_item" access="RW" offset="0x0.0" size="0xc.0" />
	<field name="configuration_item_data" descr="" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="mnvdi_reg_ext" descr="" size="0xc.0" >
	<field name="configuration_item_header" descr="" subnode="config_item" access="RW" offset="0x0.0" size="0xc.0" />
</node>

<node name="mnvgc_reg_ext" descr="" size="0x10.0" >
	<field name="nvda_read_factory_settings" descr="NVDA Read factory settings. Indicates if reading the fac\;tory settings by NVDA is supported.\;0:unsupported\;1: supported" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="nvda_read_current_settings" descr="NVDA Read current settings. Indicates if reading the cur\;rent settings by NVDA is supported.\;0: unsupported\;1: supported" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="priv_nv_other_host" descr="When set, TLVs of other hosts may be modified." access="RO" offset="0x0.2" size="0x0.1" />
</node>

<node name="mnvgn_reg_ext" descr="" size="0x20.0" >
	<field name="nv_pointer" descr="Pointer to the NV parameter (see description above for more \;information)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item" access="RO" offset="0x10.0" size="0xc.0" />
	<field name="configuration_item_data" descr="" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mnvia_reg_ext" descr="" size="0x8.0" >
	<field name="target" descr="Information targeted for invalidation\;0: ALL - all NVRAM parameters.\; All other values are reserved." access="WO" offset="0x0.0" size="0x0.3" />
	<field name="writer_id" descr="The entity which perform the invalidate.\;The encoding same as writer_id in Configuration Item reg\;ister (See Table 1453, &quot;Configuration Item Layout,&quot; on \;page 1596)." access="RW" offset="0x0.4" size="0x0.5" />
</node>

<node name="mnvqc_reg_ext" descr="" size="0x8.0" >
	<field name="type" descr="Configuration item type. \;Table 1455, &quot;Configuration Item Type Class Global Lay\;out,&quot; on page 1599\;Table 1457, &quot;Configuration Item Type Class Physical \;Port Layout,&quot; on page 1600\;Table 1459, &quot;Configuration Item Type Class Per Host-PF \;Layout,&quot; on page 1600" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="support_rd" descr="The configuration item is supported and can be read" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_wr" descr="The configuration item is supported and can be updated" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="version" descr="The maximal version of the configuration item supported \;by the device" access="RO" offset="0x4.4" size="0x0.4" />
</node>

<node name="mogcr_ext" descr="" size="0x20.0" >
	<field name="ptp_eftc" descr="PTP Egress FIFO Trap Clear\;The PTP_EGR_FIFO trap provides MTPPTR with clr according \;to this value. Default 0.\;Reserved when IB switches and when SwitchX/-2, Spectrum-2" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="ptp_iftc" descr="PTP Ingress FIFO Trap Clear\;The PTP_ING_FIFO trap provides MTPPTR with clr according \;to this value. Default 0.\;Reserved when IB switches and when SwitchX/-2, Spectrum-2" access="RW" offset="0x0.1" size="0x0.1" />
	<field name="tele_managed" descr="Telemetry is managed:\;0: telemetery is unmanged (default for IB switches)\;1: telemetery is manged (default for Eth switches)\;When unmanaged - the events are by VS-MADs\;When managed - the events are by EMADs\;Reserved when Ethernet switches" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="sid" descr="Sample ingress discards:\;0: ingress discards are not sampled\;1: ingress discards are sampled\;Reserved when Switch-IB/2, Quantum, \;Spectrum-2 TBD" access="RW" offset="0x8.0" size="0x0.1" />
	<field name="mirroring_pid_base" descr="Base policer id for mirroring policers.\;Must have an even value (e.g. 1000, not 1001).\;Reserved when SwitchX/-2, Switch-IB/2, Spectrum-1 and Quan\;tum" access="RW" offset="0xC.0" size="0x0.14" />
	<field name="mirror_latency_units" descr="Units of mirror header latency\;Units of nSec\;For Spectrum-2/3: values are 1,2,4..32768nSec\;Default 64nSec\;See Table 524, &quot;ETH-ERSPAN Mirror Header TLV LATENCY \;Frame Layout,&quot; on page 640\;Reserved when Spectrum-1" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="latency_histogram_units" descr="Units of latency histograms\;Units of nSec\;For Spectrum-2/3: values are 1,2,4..32768nSec\;Default 64nSec\;See Section 9.6.4.1, &quot;Latency Histograms,&quot; on page 1280\;Reserved when Spectrum-1\;" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="toc_fmt" descr="Timestamp over CRC format:\;0: Free_Running_Clock\;1: UTC" access="RW" enum="Free_Running_Clock=0x0,UTC=0x1" offset="0x1C.24" size="0x0.1" />
</node>

<node name="momte_ext" descr="" size="0x10.0" >
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR\;1: LNM - local network manager\;Reserved when Spectrum/-2" access="OP" enum="HYPERVISOR=0x0,LNM=0x1" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="If (mngr_type == &quot;Hypervisor&quot;)\;Unique port identifier for the final destination of the packet\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from \;which the command came from is InfiniBand: \;ib port number\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from \;which the command came from is Ethernet: \;Local Port\;\;For Quantum:\;- Supported to/from Aggregation Node\;- Not supported to/from IB Router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="Switch Partition ID\;Reserved when mngr_type = LNM\;Reserved when Ethernet switches" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="type" descr="Type:\;0x20: WRED, egress, no CPU port\;0x31: SHARED_BUFFER_TClass, egress\;0x32: Shared-buffer-TClass-descriptors, egress [advanced]\;\;0x33: SHARED_BUFFER_Egress_Port, egress\;0x40: ING_CONG, ingress\;0x50: EGR_CONG, egress\;0x60: ECN, egress, no CPU port\;0x70: HIGH_LATENCY, egress, no CPU port\;See Section 509, &quot;Mirror triggers,&quot; on page 629" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="tclass_en_high" descr="TClass/PG mirror enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;When type = 0x33: only bit0 is used, representing the port\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tclass_en_low" descr="TClass/PG mirror enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;When type = 0x33: only bit0 is used, representing the port\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="moni_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="en" descr="Enable monitoring on network interface:\;0: disable (default)\;1: enable" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="mpagr_ext" descr="" size="0xc.0" >
	<field name="trigger" descr="Mirror trigger \;See Table 509, &quot;Mirror triggers,&quot; on page 629\;Reserved when the mirror binding is not Global" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR - config all ports\;1: LNM - local network manager - config all ports of the SWID\;Reserved when Ethernet switches" access="OP" enum="HYPERVISOR=0x0,LNM=0x1" offset="0x0.8" size="0x0.4" />
	<field name="swid" descr="Switch Partition ID\;Reserved when mngr_type = LNM\;Reserved when Ethernet switches" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="pa_id" descr="Port analyzer ID" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="enable" descr="Enable mirroring \;By default, port mirroring is disabled for all ports.\;Reserved when Quantum and Spectrum-2." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="probability_rate" descr="Sampling rate = 1 out of rate packets \;Valid values are: 1 to 3.5*10^9\;Value of 1 means &quot;sample all&quot;\;Default 1\;Note: high values are round by HW to: 10^9 * {4.3, 2.15, 1.43, \;1.08, 0.86, 0.72, 0.61, 0.54}." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mpar_ext" descr="" size="0xc.0" >
	<field name="i_e" descr="Ingress/egress\;See Table 509, &quot;Mirror triggers,&quot; on page 629\;Reserved when the mirror binding is not per Rx or per Tx" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="local_port" descr="When Ethernet: always Local Port\;\;When IB:\;If (mngr_type == &quot;Hypervisor&quot;):\;Unique port identifier\;If (mngr_type == &quot;Local Network Manager&quot;):\;ib port number\;\;For SwitchX/-2 and Spectrum/-2:\;- Supported from CPU port\;For Switch-IB/2, Quantum:\;- Supported to/from CPU port\;- Supported to/from Aggregation Node\;- Not supported to/from IB Router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR\;1: LNM - local network manager\;Reserved when Spectrum/-2" access="OP" enum="HYPERVISOR=0x0,LNM=0x1" offset="0x0.24" size="0x0.4" />
	<field name="pa_id" descr="Port analyzer ID\;Reserved when enable=0" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="enable" descr="Enable mirroring \;By default, port mirroring is disabled for all ports." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="probability_rate" descr="Sampling rate = 1 out of rate packets \;Valid values are: 1 to 4.3*10^9\;Values of 0 behaves like 1\;Default 1\;Note: high values are round by HW to: 10^9 * {4.3, 2.15, 1.43, 1.08, \;0.86, 0.72, 0.61, 0.54}. \;Reserved when SwitchX/-2, Switch-IB/2 and Spectrum-1\;Supported for Quantum and Spectrum-2 and on" access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mpat_encap_localib_ext" descr="" size="0x10.0" >
	<field name="vl" descr="Virtual Lane on which the mirrored packet is queued.\;Mirrored packets cannot be queued on VL-15" access="RW" offset="0xC.0" size="0x0.4" />
</node>

<node name="mpat_encap_remoteib_ext" descr="" size="0x4c.0" >
	<field name="dlid" descr="Destination LID. Note that the analyzer port is configured by the sys\;tem_port field and not by forwarding the packet based on the dlid \;field." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. When set to dynamic mode, the analyzer port \;is set based on the forwarding information for the dlid onprivate-LFT \;0 instead of  the system_port field. In static mode, the packet is trans\;mitted to the configured system_port regardless of the forwarding \;database.\;0: static analyzer port\;1: dynamic analyzer port" access="RW" offset="0x0.16" size="0x0.2" />
	<field name="sl" descr="Service Level" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="we" descr="Write enable:\;0: write all fields\;1: write only psn_init_val" access="WO" offset="0x0.24" size="0x0.8" />
	<field name="slid" descr="Source LID (LID of the sending device)" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="version" descr="Remote SPAN InfiniBand encapsulation header version\;1: V1 - Mirror Header Version 1\;2: V2 - Mirror Header Version 2\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the ana\;lyzer port based on the desired forwarding table (the one that belong \;to the swid)." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="vl" descr="Virtual Lane on which the mirrored packet is queued.\;Mirrored packets cannot be queued on VL-15." access="RW" offset="0xC.0" size="0x0.4" />
	<field name="flow_label" descr="GRH FlowLabel" access="RW" offset="0x10.0" size="0x0.20" />
	<field name="tclass" descr="GRH TClass" access="RW" offset="0x10.20" size="0x0.8" />
	<field name="hop_limit" descr="GHR HopLmt" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="sgid" descr="GRH SGID[127:0]" access="RW" high_bound="3" low_bound="0" offset="0x18.0" size="0x10.0" />
	<field name="dgid" descr="GRH DGID[127:0]" access="RW" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
	<field name="pkey" descr="BTH PKey" access="RW" offset="0x38.0" size="0x0.16" />
	<field name="m" descr="BTH m" access="RW" offset="0x38.22" size="0x0.1" />
	<field name="se" descr="BTH se" access="RW" offset="0x38.23" size="0x0.1" />
	<field name="dest_qp" descr="BTH dest QP" access="RW" offset="0x3C.0" size="0x0.24" />
	<field name="psn_init_val" descr="BTH packet sequence number initial value\;Note: when reading, HW will reveal the current packet sequence \;number" access="RW" offset="0x40.0" size="0x0.24" />
	<field name="ar" descr="BTH MLNX adaptive routing enable flag" access="RW" offset="0x40.30" size="0x0.1" />
	<field name="qkey" descr="DETH QKey" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="src_qp" descr="DETH source QP" access="RW" offset="0x48.0" size="0x0.24" />
</node>

<node name="mpat_encap_rmtethl2_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="Destination MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. \;When set to dynamic mode, the analyzer port is set based on the \;forwarding information for the {mac, vid} combination and not \;based on the system_port field. In static mode, the packet is trans\;mitted to the configured system_port regardless of the forwarding \;database. Note that in Dynamic mode, if the switch FDB does not \;hold a filtering entry for the {mac, vid}, the mirroring copy is not \;flooded - it is discarded.\;0: STATIC_ANALYZER - static analyzer port\;1: DYNAMIC_ANALYZER - dynamic analyzer port\;Reserved when ubridge=1" access="RW" enum="STATIC_ANALYZER=0x0,DYNAMIC_ANALYZER=0x1" offset="0x0.16" size="0x0.2" />
	<field name="version" descr="ERSPAN mirror header version.\;0: V0 - Mirror Header Version 0\;1: V1 - Mirror Header Version 1. Reserved when SwitchX/-2\;2: V2 - Mirror Header Version 2. Reserved when SwitchX/-2 and \;for Spectrum-1\;\;15: NO_HEADER - No Mirror header" access="RW" enum="V0=0x0,V1=0x1,V2=0x2,NO_HEADER=0xf" offset="0x0.18" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the \;Analyzer port based on the desired forwarding table (the one that \;belong to the swid).\;Reserved when Spectrum/-2" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="mac_31_0" descr="Destination MAC address" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="vid" descr="When dpa = 0: Encapsulation header VLAN ID\;When dpa = 1 and fid &lt; 4K (fid_msb = 0) then: VLAN ID\;When dpa = 1 and fid &gt;=4K (fid_msb != 0) then: FID lsb" access="RW" offset="0x8.0" size="0x0.12" />
	<field name="dei" descr="Encapsulation header DEI. \;Reserved when qos is QoS maintain\;Reserved when tp = 0\;Reserved when SwitchX/-2" access="RW" offset="0x8.12" size="0x0.1" />
	<field name="pcp" descr="Encapsulation header PCP. \;Reserved when qos is QoS maintain\;Reserved when tp = 0" access="RW" offset="0x8.13" size="0x0.3" />
	<field name="tp" descr="Tag Packet. Indicates the mirroring header should be VLAN \;tagged.\;0: Mirror packet is un-tagged\;1: Mirror packet is tagged" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="tclass" descr="Traffic Class\;For Spectrum: Switch Priority\;Reserved when qos is QoS maintain" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="vlan_et_id" descr="Encapsulation header VLAN Ethertype ID\;Default is &apos;0&apos;\;Ethertype IDs are configured by SVER, see Section 6.12.33, \;&quot;SVER - Switch VLAN EtherType Register,&quot; on page 920\;Reserved when SwitchX/-2" access="RW" offset="0xC.16" size="0x0.2" />
	<field name="fid_msb" descr="FID msb\;Reserved when dpa=0" access="RW" offset="0xC.24" size="0x0.4" />
</node>

<node name="mpat_encap_rmtethl3gre_ext" descr="" size="0x50.0" >
	<field name="mac_47_32" descr="Destination MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. \;When set to dynamic mode, the analyzer port is set based on the \;forwarding information for the {mac, vid} combination and not \;based on the system_port field. In static mode, the packet is trans\;mitted to the configured system_port regardless of the forwarding \;database. Note that in Dynamic mode, if the switch FDB does not \;hold a filtering entry for the {mac, vid}, the mirroring copy is not \;flooded - it is discarded.\;0: STATIC_ANALYZER - static analyzer port\;1: DYNAMIC_ANALYZER - dynamic analyzer port\;Reserved when ubridge=1" access="RW" offset="0x0.16" size="0x0.2" />
	<field name="version" descr="ERSPAN mirror header version.\;\;1: V1 - Mirror Header Version 1. Reserved when SwitchX/-2\;2: V2 - Mirror Header Version 2. Reserved when SwitchX/-2 and \;for Spectrum-1\;\;15: NO_HEADER - No Mirror header" access="RW" offset="0x0.18" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the \;Analyzer port based on the desired forwarding table (the one that \;belong to the swid).\;Reserved when Spectrum/-2" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="mac_31_0" descr="Destination MAC address" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="vid" descr="When dpa = 0: Encapsulation header VLAN ID\;When dpa = 1 and fid &lt; 4K (fid_msb = 0) then: VLAN ID\;When dpa = 1 and fid &gt;=4K (fid_msb != 0) then: FID lsb" access="RW" offset="0x8.0" size="0x0.12" />
	<field name="dei" descr="Encapsulation header DEI. \;Reserved when qos is QoS maintain\;Reserved when tp = 0\;Reserved when SwitchX/-2" access="RW" offset="0x8.12" size="0x0.1" />
	<field name="pcp" descr="Encapsulation header PCP. \;Reserved when qos is QoS maintain\;Reserved when tp = 0" access="RW" offset="0x8.13" size="0x0.3" />
	<field name="tp" descr="Tag Packet. Indicates the mirroring header should be VLAN \;tagged.\;0: Mirror packet is un-tagged\;1: Mirror packet is tagged" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="dscp" descr="Encapsulation header DSCP\;Reserved when qos is QoS maintain" access="RW" offset="0x8.18" size="0x0.6" />
	<field name="protocol" descr="0: IPV4\;1: IPV6" access="RW" enum="IPV4=0x0,IPV6=0x1" offset="0x8.24" size="0x0.4" />
	<field name="tclass" descr="Traffic Class\;For Spectrum: Switch Priority\;Reserved when qos is QoS maintain" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="ttl" descr="Encapsulation header Time-to-Live/HopLimit" access="RW" offset="0xC.4" size="0x0.8" />
	<field name="ecn" descr="Encapsulation header ECN" access="RW" offset="0xC.12" size="0x0.2" />
	<field name="vlan_et_id" descr="Encapsulation header VLAN Ethertype ID\;Default is &apos;0&apos;\;Ethertype IDs are configured by SVER, see Section 6.12.33, \;&quot;SVER - Switch VLAN EtherType Register,&quot; on page 920\;Reserved when SwitchX/-2" access="RW" offset="0xC.16" size="0x0.2" />
	<field name="fid_msb" descr="FID msb\;Reserved when dpa=0" access="RW" offset="0xC.24" size="0x0.4" />
	<field name="smac_47_32" descr="Source MAC address" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="smac_31_0" descr="Source MAC address" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="dip" descr="Destination IP address\;The IP version is configured by protocol\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="RW" high_bound="3" low_bound="0" offset="0x30.0" size="0x10.0" />
	<field name="sip" descr="Source IP address\;The IP version is configured by protocol\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
</node>

<node name="mpat_encap_rmtethvlan_ext" descr="" size="0x10.0" >
	<field name="vid" descr="Encapsulation header VLAN ID" access="RW" offset="0x8.0" size="0x0.12" />
	<field name="dei" descr="Encapsulation header DEI\;Reserved when qos is QoS maintain\;Reserved when SwitchX/-2" access="RW" offset="0x8.12" size="0x0.1" />
	<field name="pcp" descr="Encapsulation header PCP\;Reserved when qos is QoS maintain" access="RW" offset="0x8.13" size="0x0.3" />
	<field name="tclass" descr="Traffic Class.\;For Spectrum: Switch Priority\;Reserved when qos is QoS maintain" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="vlan_et_id" descr="Encapsulation header VLAN Ethertype ID\;Default is &apos;0&apos;\;Ethertype IDs are configured by SVER, see Section 6.12.33, \;&quot;SVER - Switch VLAN EtherType Register,&quot; on page 920\;Reserved when SwitchX/-2" access="RW" offset="0xC.16" size="0x0.2" />
</node>

<node name="mpat_reg_encapsulation_auto_ext" descr="" attr_is_union="1" size="0x50.0" >
	<field name="local_span_ext" descr="" subnode="local_span_ext" offset="0x0.0" selected_by="LOCAL_ETH" size="0x10.0" />
	<field name="mpat_encap_rmtethvlan_ext" descr="" subnode="mpat_encap_rmtethvlan_ext" offset="0x0.0" selected_by="REMOTE_ETH" size="0x10.0" />
	<field name="mpat_encap_rmtethl2_ext" descr="" subnode="mpat_encap_rmtethl2_ext" offset="0x0.0" selected_by="REMOTE_ETH_L2" size="0x10.0" />
	<field name="mpat_encap_rmtethl3gre_ext" descr="" subnode="mpat_encap_rmtethl3gre_ext" offset="0x0.0" selected_by="REMOTE_ETH_L3" size="0x50.0" />
	<field name="mpat_encap_localib_ext" descr="" subnode="mpat_encap_localib_ext" offset="0x0.0" selected_by="LOCAL_IB" size="0x10.0" />
	<field name="remote_span_ib_local_ud_ext" descr="" subnode="remote_span_ib_local_ud_ext" offset="0x0.0" selected_by="REMOTE_IB_LOCAL_UD" size="0x4c.0" />
	<field name="mpat_encap_remoteib_ext" descr="" subnode="mpat_encap_remoteib_ext" offset="0x0.0" selected_by="REMOTE_IB_GLOBAL_UD" size="0x4c.0" />
</node>

<node name="mpat_reg_ext" descr="" size="0x70.0" >
	<field name="system_port" descr="If (mngr_type == &quot;Hypervisor&quot;)\;Unique port identifier for the final destination of the packet\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from which \;the command came from is InfiniBand: \;ib port number\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from which \;the command came from is Ethernet: \;Local Port\;For SwitchX/-2, Switch-IB/2 and Spectrum-1: CPU port is not sup\;ported\;For Quantum: CPU port is supported\;For Spectrum-2: CPU port is supported\;Note: when CPU port:\;1. span_type must be LOCAL_ETH or LOCAL_IB\;2. tr is reserved (no truncation)\;Reserved when dpa = 1" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR\;1: LOCAL_NETWORK_MANAGER\;For more details regarding Manager Type, refer to Section 2.13, \;&quot;Management Security Hierarchy,&quot; on page 330." access="OP" enum="HYPERVISOR=0x0,LOCAL_NETWORK_MANAGER=0x1" offset="0x0.16" size="0x0.4" />
	<field name="session_id" descr="Mirror Session ID.\;Used for MIRROR_SESSION&lt;i&gt; trap\;Reserved when SwitchX/-2, Switch-IB/2 and Spectrum-1" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="pa_id" descr="Port Analyzer ID (a.k.a mirror-agent)\;Range 0 .. cap_max_span_analyzers - 1" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="span_type" descr="See Table 572, &quot;Span Types,&quot; on page 686\;0x0: LOCAL_ETH\;0x1: REMOTE_ETH\;0x2: REMOTE_ETH_L2\;0x3: REMOTE_ETH_L3\;0x4: LOCAL_IB\;0xA: REMOTE_IB_LOCAL_UD\;0xB: REMOTE_IB_GLOBAL_UD" access="RW" enum="LOCAL_ETH=0x0,REMOTE_ETH=0x1,REMOTE_ETH_L2=0x2,REMOTE_ETH_L3=0x3,LOCAL_IB=0x4,REMOTE_IB_LOCAL_UD=0xa,REMOTE_IB_GLOBAL_UD=0xb" offset="0x4.0" size="0x0.4" />
	<field name="stclass" descr="Stacking TClass. TClass to be used if the packet is transmitted on a \;stacking port to be transmitted on a port in a different device.\;Reserved when Switch-IB/2, Quantum and Spectrum" access="RW" offset="0x4.13" size="0x0.3" />
	<field name="tr" descr="Truncate. Indicates all packets mirrored to this Analyzer port will be \;truncated.\;Truncation size is defined by truncation_size\;For Spectrum-1, packets from CPU to a truncation-enabled agent will \;not be mirrored. \;For Spectrum-2, packets from CPU to a truncation-enabled agent will \;be mirrored\;Reserved when system_port is to CPU" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="be" descr="Best Effort. Indicates mirroring traffic should not cause packet drop or \;back pressure but will discard the mirroring packets. Mirroring pack\;ets will be forwarded on a best effort manner.\;0: NOT_DISCARD - Do not discard mirrored packets\;1: DISCARD - Discard mirrored packets if causing congestion\;Relevant both for ingress mirror and egress mirror" access="RW" enum="NOT_DISCARD=0x0,DISCARD=0x1" offset="0x4.25" size="0x0.1" />
	<field name="qos" descr="Quality of Service mode\;0: CONFIGURED - QoS parameters (Switch Priority, and encapsula\;tion PCP, DEI, DSCP or VL) are configured\;1: MAINTAIN - QoS parameters (Switch Priority, Color) are the same \;as in the original packet that has triggered the mirroring. For SPAN \;also the pcp,dei are maintained. Reserved when Spectrum-1.\;For SPAN packets the PCP, DEI is as mirrored packet\;For SwitchX/-2: this field is reserved.\;" access="RW" enum="CONFIGURED=0x0,MAINTAIN=0x1" offset="0x4.26" size="0x0.1" />
	<field name="c" descr="Clear counters\;Clears the buffer_drop and be_drop counters" access="OP" offset="0x4.28" size="0x0.1" />
	<field name="e" descr="Enable. Indicating the Port Analyzer is enabled\;Note: For SwitchX/-2 and Switch-IB/2 before disabling a port ana\;lyzer, software should make sure no port / rule is associated with the \;Port Analyzer to be disabled." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="truncation_size" descr="Truncation Size.\;Sets the truncation size in case truncation is enabled. \;Unit is 1 byte.\;Granularity is 4 bytes. \;For Switch-IB/2 and Spectrum-1: minimum value is 32B\;For Quantum and Spectrum-2/3: minimum value is 48B\;For Switch-IB/2, all port analyzers must have the same truncation size.\;For SwitchX/-2, this value is set to 64 bytes and can not be changed in \;current FW version. For more details, contact Mellanox support.\;Reserved when span_type is LOCALIB" access="RW" offset="0x8.0" size="0x0.13" />
	<field name="pid" descr="Policer ID\;Range MOGCR.mirroring_pid_base .. (MOGCR.mirror\;ing_pid_base + cap_max_span_analyzers - 1)\;See pid in QPCR, Section 11.13.7, &quot;QPCR - QoS Policer Configura\;tion Register,&quot; on page 1789\;Note: the policer takes packet length prior to truncation. The policer \;must have color_aware=not, type=srDCM, violate_action=discard.\;Reserved when SwitchX/-2, Switch-IB/2, Spectrum-1 and Quantum" access="RW" offset="0xC.0" size="0x0.14" />
	<field name="pide" descr="Policer enable\;For more details about policers, refer to Section 10.7.6, &quot;Policer,&quot; on \;page 1565\;Note: for mirror to CPU: MPAT.pid is enabled then the trap-group-\;policer will not police\;Reserved when SwitchX/-2, Switch-IB/2, Spectrum-1 and Quantum" access="RW" offset="0xC.15" size="0x0.1" />
	<field name="encapsulation" descr="Remote SPAN encapsulation. The encapsulation information is based \;on the span_type field. The following tables provide a reference to the \;encapsulation fields for the different SPAN types: \;Table 573, &quot;Local SPAN Layout,&quot; on page 687.\;Table 575, &quot;Remote SPAN Ethernet VLAN Layout,&quot; on page 688.\;Table 577, &quot;Encapsulated Remote SPAN Ethernet L2 Layout,&quot; on \;page 689.\;Table 579, &quot;Encapsulated Remote SPAN Ethernet L3 Layout,&quot; on \;page 691.\;Table 581, &quot;Local SPAN InfiniBand Layout,&quot; on page 694.\;Table 583, &quot;Remote SPAN InfiniBand Local UD Layout,&quot; on \;page 695.\;Table 585, &quot;Remote SPAN InfiniBand Global UD Layout,&quot; on \;page 697." subnode="mpat_reg_encapsulation_auto_ext" access="RW" offset="0x10.0" size="0x50.0" union_selector="$(parent).span_type" />
	<field name="buffer_drop_high" descr="Number of packet drops on the analyzer agent due to buffer size\;Not supported for SwitchX/-2, Switch-IB and Quantum\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="buffer_drop_low" descr="Number of packet drops on the analyzer agent due to buffer size\;Not supported for SwitchX/-2, Switch-IB and Quantum\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="be_drop_high" descr="Number of packet drops on the analyzer agent due to Best Effort when \;be is enabled\;Not supported for SwitchX/2 and Switch-IB and Quantum\;\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="be_drop_low" descr="Number of packet drops on the analyzer agent due to Best Effort when \;be is enabled\;Not supported for SwitchX/2 and Switch-IB and Quantum\;\;" access="RO" offset="0x6C.0" size="0x4.0" />
</node>

<node name="mpcir_ext" descr="" size="0x10.0" >
	<field name="all" descr="If set to &apos;01&apos;, activates the flow of preparation for FW ISSU, on all \;services. The values in op-codes for &quot;per-service&quot; are ignored.\;If set to &apos;10&apos;, returns to operational state on all services. The val\;ues in op-codes for &quot;per-service&quot; are ignored.\;11 - Reserved" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="ports" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.0" size="0x0.2" />
	<field name="cpld" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.2" size="0x0.2" />
	<field name="module_mng" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.4" size="0x0.2" />
	<field name="thermal" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.6" size="0x0.2" />
	<field name="fans" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.8" size="0x0.2" />
	<field name="power" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.10" size="0x0.2" />
	<field name="voltage_current" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.12" size="0x0.2" />
	<field name="leds" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.14" size="0x0.2" />
	<field name="gearbox" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding \;_stat fields." access="OP" offset="0x4.16" size="0x0.2" />
	<field name="ports_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.0" size="0x0.2" />
	<field name="cpld_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.2" size="0x0.2" />
	<field name="module_mng_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.4" size="0x0.2" />
	<field name="thermal_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.6" size="0x0.2" />
	<field name="fans_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.8" size="0x0.2" />
	<field name="power_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.10" size="0x0.2" />
	<field name="voltage_current_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.12" size="0x0.2" />
	<field name="leds_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.14" size="0x0.2" />
	<field name="gearbox_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done ser\;vice handling [Internal]: busy with some other critical flow).\;For not implemented services on a particular system, the status \;should be &apos;1&apos;." access="RO" offset="0xC.16" size="0x0.2" />
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
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for all \;counters in the counter group. This bit can be set for both Set() and \;Get() operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;Table 1496, &quot;PCIe Performance Counters Data Layout,&quot; on \;page 1620\;Table 1500, &quot;PCIE lanes counters Data Layout,&quot; on page 1624 - \;[Internal] \;Table 1498, &quot;PCIE timers and states Data Layout,&quot; on page 1622 - \;[Internal]" subnode="mpcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="mpecs_reg_ext" descr="" size="0x20.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIE index number\;Reserved when access is from the host" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="capability_id" descr="capability ID as defined in PCIE spec" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="reg_num" descr="Register number\;Byte offset from the beginning of the capability ID" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="byte_enable" descr="Enable bit per byte\;bit 0 - byte 0 (bits 7:0)\;bit 1 - byte 1 (bits 15:8)\;bit 2 - byte 2 (bits 23:16)\;bit 3 - byte 3 (bits 31:24)\;Reserved for read operation." access="WO" offset="0xC.0" size="0x0.4" />
	<field name="status" descr="PCIE configuration space access status: \;0x0: SUCCESS - successful access\;0x1: FUNC_NUM_FAILURE - accessing unsupported configura\;tion space function number\;0x2: CAP_ID_FAILURE - accessing unsupported configuration \;space capability ID number\;0x3: REG_NUM_FAILURE - accessing unsupported configuration \;space register number\;0x4: WRITE_FAILURE - write access to read-only configuration \;space\;0x5: PROTECTED_FAILURE - protected configuration" access="RO" enum="SUCCESS=0x0,FUNC_NUM_FAILURE=0x1,CAP_ID_FAILURE=0x2,REG_NUM_FAILURE=0x3,WRITE_FAILURE=0x4,PROTECTED_FAILURE=0x5" offset="0xC.8" size="0x0.8" />
	<field name="func_num" descr="Function number\;physical function index - see PCIE spec" access="INDEX" offset="0xC.16" size="0x0.8" />
	<field name="ext" descr="Extended or regular configuration space, as defined in PCIE spec:\;0 - Regular\;1 - Extended" access="INDEX" offset="0x10.0" size="0x0.2" />
	<field name="data" descr="" access="RW" offset="0x14.0" size="0x4.0" />
</node>

<node name="mpein_reg_ext" descr="" size="0x30.0" >
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="PCIe index number (Internal domain index)\;Reserved when access is from the host, but can be used when oper\;ating in Socket-Direct mode." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="link_speed_enabled" descr="Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="link_width_enabled" descr="Maximum Link Width enabled:\;0: 1x\;1: 2x\;2: 4x\;3: 8x\;4: 16x" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="link_speed_active" descr="Current Link Speed:\;Bit 0: 2.5G (Gen1)\;Bit 1: 5G (Gen2)\;Bit 2: 8G (Gen3)\;Bit 4: 16G (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="link_width_active" descr="Negotiated Link Width, pcie_link_width active:\;0 - 1x\;1 - 2x\;2 - 4x\;3 - 8x\;4 - 16x" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="lane0_physical_position" descr="The physical lane position of logical lane0" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="num_of_vfs" descr="Number of Total Virtual Functions (for all PFs)" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="num_of_pfs" descr="Number of Physical Functions (PFs)" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="bdf0" descr="Bus Device Function - only for function0" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="lane_reversal" descr="Reversal mode of the link:\;0 - straight \;1 - reversal\;\;Note: together with lane0_physical_position provide the physical \;lane." access="RO" offset="0x18.0" size="0x0.1" />
	<field name="port_type" descr="Indicates the specific type of this PCI Express Function. Note that \;different Functions in a multi-Function device can generally be of \;different types.\;0 - PCI Express Endpoint port\;4 - Root Port of PCI Express Root Complex\;5 - PCI Express Upstream port\;6 - PCI Express Downstream port" access="RO" offset="0x18.12" size="0x0.4" />
	<field name="pwr_status" descr="Indicates the status of PCI power consumption limitations.\;0: PCI power report could not be read.\;1: Sufficient power reported.\;2: Insufficient power reported.\;3-7: Reserved" access="RO" offset="0x18.16" size="0x0.3" />
	<field name="max_payload_size" descr="Max payload size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.24" size="0x0.4" />
	<field name="max_read_request_size" descr="Max read request size in bytes:\;0 - 128B\;1 - 256B\;2 - 512B\;3 - 1024B\;4 - 2048B\;5 - 4096B" access="RO" offset="0x18.28" size="0x0.4" />
	<field name="pci_power" descr="Power reported by the PCI device. The units are in Watts.\;0: Power is unknown." access="RO" offset="0x1C.0" size="0x0.12" />
	<field name="link_peer_max_speed" descr="Peer Max Link Speed:\;Bit 0: 2.5G - (Gen1)\;Bit 1: 5G - (Gen2)\;Bit 2: 8G - (Gen3)\;Bit 4: 16G - (Gen4)\;Bit 5: 32G (Gen5)" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="device_status" descr="device_status bit mask:\;Bit 0: Correctable_error\;Bit 1: Non_Fatal_Error_detection\;Bit 2: Fatal_Error_detected\;Bit 3: Unsupported_request_detected\;Bit 4: AUX_power \;Bit 5: Transaction_Pending" access="RO" enum="Correctable_error=0x1,Non_Fatal_Error_detection=0x2,Fatal_Error_detected=0x4,Unsupported_request_detected=0x8,AUX_power=0x10,Transaction_Pending=0x20" offset="0x24.16" size="0x0.16" />
</node>

<node name="mpelem_ext" descr="" size="0xc.0" >
	<field name="eip_ecn" descr="Egress IP ECN\;ECN field of the IP header of the packet which goes out from \;the LER or LSR that implements PHP and decapsulates the \;MPLS header" access="RW" offset="0x4.8" size="0x0.2" />
	<field name="ip_ecn" descr="IP ECN\;ECN field of the IP header of the packet that has entered the \;Egress LER or LSR that implements PHP and decapsulates the \;MPLS header" access="INDEX" offset="0x4.16" size="0x0.2" />
	<field name="mpls_ecn" descr="MPLS ECN\;ECN field of the MPLS header of the packet that has entered the \;Egress LER or LSR that implements PHP and decapsulates the \;MPLS header" access="INDEX" offset="0x4.24" size="0x0.2" />
	<field name="trap_id" descr="Trap ID\;Trap-ID is DECAP_ECN0 or DECAP_ECN1.\;Reserved when trap_en is &apos;0&apos;" access="RW" offset="0x8.0" size="0x0.9" />
	<field name="trap_en" descr="Trap enable:\;0: no trap due to decap ecn\;1: trap enable with trap_id. HPKT can control the trap action. \;See Section 2.15.3, &quot;HPKT - Host PacKet Trap,&quot; on page 379" access="RW" offset="0x8.28" size="0x0.4" />
</node>

<node name="mpepm_ext" descr="" size="0x14.0" >
	<field name="exp" descr="EXP entry is the EXP to Switch Priority mapping.\;For more details, refer to Section 2151, &quot;exp&lt;i&gt; Layout,&quot; on \;page 2095" access="RW" high_bound="7" low_bound="0" offset="0x4.16" size="0x10.0" />
</node>

<node name="mpfm_ext" descr="" size="0x8.0" >
	<field name="mode" descr="PCIe Failure Mode.\;0 - normal. PCIe failure causes SwitchX reset.\;1 - independent. PCIe failure does not cause SwitchX reset." access="RW" offset="0x0.0" size="0x0.4" />
</node>

<node name="mpft_ext" descr="" size="0x8.0" >
	<field name="rif" descr="Router Interface to be bypassed by FRR" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="av" descr="label action valid:\;0 - set label_action to &apos;0&apos;: no php, no push\;1 - keep the label_action as is\;See Section 14.8.4.1, &quot;MPNHLFE Parameters - Forward to \;Ethernet,&quot; on page 2080" access="WO" offset="0x4.0" size="0x0.1" />
</node>

<node name="mpgcr_ext" descr="" size="0x24.0" >
	<field name="ler_exp_rw" descr="Ingress LER EXP Re-write Enable\;Initial value for exp_rewrite_en for ingress LER:\;2: Disable the exp_rewrite_en\;3: Enable the exp_rewrite_en" access="RW" offset="0x0.20" size="0x0.2" />
	<field name="mpls_pcp_rw" descr="LSR and LER PCP Re-write Enable\;Indicates how LSR handles the pcp_rewrite_en:\;0: Preserve the value of the pcp_rewrite_en\;2: Disable the pcp_rewrite_en\;3: Enable the pcp_rewrite_en\;Note: for ingress LER the RGCR may set the pcp_rw, and \;then the mpls will set it again." access="RW" offset="0x0.22" size="0x0.2" />
	<field name="mpls_et" descr="At ingress: MPLS Ethertype accepted for LSR and egress \;LER:\;1: Ethertype 0x8847\;2: Ethertype 0x8848\;3: Ethertype 0x8847 or Ethertype 0x8848\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="ingress_ler_ttl_value" descr="Ingress LER TTL Value\;The value used in MPLS encapsulation when pushing a \;new label over IP packet in ingress LER. This value will \;not be decremented.\;Reserved when ingress_ler_ttl is 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="lsr_egress_ttl" descr="Egress LSR TTL (also for LSR PHP to Labels)\;Configures how the TTL of the exposed labels are set at \;LSR egress:\;1: COPY - The TTL is taken from the first popped label \;2: MINIMUM - The TTL is the minimum value between \;all popped labels\;Note: &quot;exposed labels&quot; are the labels pushed by NHLFE\;Note: the decrement of the TTL is done after the new value \;is set" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="egress_ler_ttl" descr="Configures the TTL of IP header when IP packet is \;exposed\;\;0: PRESERVE - The TTL is taken from the IP header\;If the packet goes to IP router then the IP router will decre\;ment the TTL\;\;1: COPY - The TTL is taken from the first popped label\;If the packet goes to IP router then the IP router will decre\;ment the TTL\;If the packet is forwarded to outgoing interface then the \;TTL will be decremented\;\;2: MINIMUM - The TTL is the minimum value between \;all popped labels and the IP header\;If the packet goes to IP router then the IP router may decre\;ment the TTL\;If the packet is forwarded to outgoing interface and TTL is \;taken from IP header then the TTL is not decremented\;If the packet is forwarded to outgoing interface and TTL is \;taken from Labels then the TTL is decremented" access="RW" offset="0x4.20" size="0x0.2" />
	<field name="ingress_ler_ttl" descr="Ingress LER TTL\;This flag indicates which value of TTL is written in the \;new pushed label in ingress LER: \;0: TTL is taken from the IP header\;1: TTL is configured by ingress_ler_ttl_value\;Note that the IP TTL was already decremented by the IP \;router. At ingress LER flow the LSR does not decremented \;the MPLS TTL.\;\;" access="RW" offset="0x4.22" size="0x0.1" />
	<field name="hrlsn" descr="High Reserved Label ID Space Number\;Label IDs from 0 to hrlsn are accepted" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="label_id_min" descr="Label IDs from label_id_min to label_id_max are \;accepted" access="RW" offset="0x10.0" size="0x0.20" />
	<field name="label_id_max" descr="Label IDs from label_id_min to label_id_max are \;accepted" access="RW" offset="0x14.0" size="0x0.20" />
	<field name="default_label_space" descr="Default label_space (default is 0)\;Range 0..cap_mpls_label_space-1\;" access="RW" offset="0x1C.0" size="0x0.16" />
	<field name="activity_dis_mpnhlfe" descr="Disable activity bit in MPNHLFE:\;0 - enable - activity will be set when an entries are hit\;(default)\;1 - disable - activity will not be set when an entries are hit\;See Section 14.8.4, &quot;MPNHLFE - MPLS NHLFE Table \;Register,&quot; on page 2078" access="RW" offset="0x20.0" size="0x0.1" />
</node>

<node name="mpgo_reg_ext" descr="" size="0x14.0" >
	<field name="set_pd" descr="Set pulse duration" access="WO" offset="0x0.0" size="0x0.1" />
	<field name="next_pulse_time_stamp" descr="Next Pulse Time Stamp\;Start time of next trigger\;Units are device time units" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="pulse_duration" descr="Pulse Duration\;Units are mSec\;Default is 100\;Set only when set_pd = &apos;1&apos;" access="RW" offset="0x10.0" size="0x0.10" />
</node>

<node name="mpgr_ext" descr="" size="0x20.0" >
	<field name="fsps_admin" descr="Frequency Scaling Power Save Admin state:\;0 - Disable Frequency Scaling - Force device to highest frequency \;supported\;1 - Force Frequency Scaling - Force device to highest frequency sup\;ported\;2 - Auto - Automatic Frequency Scaling (based on port&apos;s speed)." access="RW" offset="0x0.0" size="0x0.4" />
	<field name="fsps_status" descr="Actual Frequency\;0 - High Frequency\;1 - Low Frequency" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="vsps_admin" descr="Voltage Scaling Power Save Admin state:\;0 - Disable Voltage Scaling - Force device to high voltage\;1 - Force Voltage Scaling - Force device to low voltage\;2 - Auto - Automatic Voltage Scaling (based on device active fre\;quency)." access="RW" offset="0x10.0" size="0x0.4" />
	<field name="vsps_status" descr="Actual Voltage\;0 - High Voltage\;1 - Low Voltage" access="RO" offset="0x14.0" size="0x0.4" />
</node>

<node name="mpibe_ext" descr="" size="0x28.0" >
	<field name="label_space" descr="Label Space\;Range 0 .. cap_mpls_label_space - 1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="nhlfe_ptr" descr="NHLFE entry pointer which is used for matching on the exist\;ing entries in the ILM table" access="INDEX" offset="0x10.0" size="0x0.24" />
	<field name="ecmp_size" descr="ECMP size used for matching on the existing entries in the ILM \;table\;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096." access="INDEX" offset="0x14.0" size="0x0.13" />
	<field name="new_nhlfe_ptr" descr="New NHLFE pointer and ECMP size values" access="WO" offset="0x20.0" size="0x0.24" />
	<field name="new_ecmp_size" descr="New NHLFE pointer and ECMP size values" access="WO" offset="0x24.0" size="0x0.13" />
</node>

<node name="mpilem_ext" descr="" size="0x8.0" >
	<field name="mpls_ecn" descr="ECN of the pushed MPLS label" access="RW" offset="0x0.16" size="0x0.2" />
	<field name="ip_ecn" descr="ECN of the IP header in the ingress LER" access="INDEX" offset="0x0.24" size="0x0.2" />
</node>

<node name="mpilm_ext" descr="" size="0x18.0" >
	<field name="label_space" descr="Label Space\;Range 0 .. cap_mpls_label_space - 1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="op" descr="Operation\;For Write:\;0: Write or over-write operation. \;1: Reserved \;2: Reserved \;3: Delete operation. Used to delete an existing entry. If entry \;doesn&apos;t exist, the operation fails.\;For Query:\;0: Read operation. If entry doesn&apos;t exist, the operation fails.\;" access="OP" offset="0x0.28" size="0x0.3" />
	<field name="label_id" descr="Label ID" access="INDEX" offset="0x4.0" size="0x0.20" />
	<field name="nhlfe_ptr" descr="NHLFE entry pointer\;Points to the NHLFE table. When using ECMP, points to the \;first entry in the ECMP list\;For Spectrum, the index is to the KVD linear, see Appendix \;A.3.1.2, &quot;KVD Central Database Linear Entries&quot; (page 2254)" access="RW" offset="0x8.0" size="0x0.24" />
	<field name="ecmp_size" descr="The amount of sequential entries starting from the nhlfe_ptr \;(the number of ECMPs)\;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096." access="RW" offset="0xC.0" size="0x0.13" />
	<field name="npop" descr="Number of labels to pop from the label stack.\;Range from 0 to cap_mpls_ilm_entry_pop" access="RW" offset="0xC.24" size="0x0.2" />
	<field name="trap_id" descr="Trap ID to be reported to CPU\;For Spectrum-1 Trap-ID is MPLS_ILM0 or MPLS_ILM1\;For Spectrum-2/3 Trap-ID is MPLS_ILM0 .. MPLS_ILM3\;For trap_action of NOP, MIRROR and DISCARD_ERROR, \;trap_id is reserved" access="RW" offset="0x10.0" size="0x0.9" />
	<field name="trap_action" descr="Trap Action\;0: NOP\;1: TRAP\;2: MIRROR_TO_CPU\;3: MIRROR\;4: DISCARD_ERROR" access="RW" enum="NOP=0x0,TRAP=0x1,MIRROR_TO_CPU=0x2,MIRROR=0x3,DISCARD_ERROR=0x4" offset="0x10.28" size="0x0.4" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x14.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x14.24" size="0x0.8" />
</node>

<node name="mpir_ext" descr="" size="0x10.0" >
	<field name="host_buses" descr="Number of PCIe buses available for the host to connect ot the \;device.\;&apos;0&apos; when operating in non-Socket-Direct mode." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="node" descr="the node within each depth." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="pcie_index" descr="Internal domain index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="depth" descr="depth level of the DUT of some hierarchy" access="INDEX" offset="0x0.24" size="0x0.6" />
	<field name="sdm" descr="Socket-Direct mode indication.\;0: non-Socket-Direct mode (single host or multi-host)\;1: Socket-Direct mode, for querying host" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="subordinate_bus" descr="sunbordinate bus - the highest bus number that subordinates to \;switch.\;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="secondary_bus" descr="secondary bus - the internal logic bus in the switch. \;Default value of &apos;0&apos; in case it is not a switch port." access="RO" offset="0x4.8" size="0x0.8" />
	<field name="device" descr="PCIe device number." access="RO" offset="0x8.3" size="0x0.5" />
	<field name="bus" descr="PCIe bus number." access="RO" offset="0x8.16" size="0x0.8" />
	<field name="local_port" descr="Local port number" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="slot_number" descr="Slot number" access="RO" offset="0xC.0" size="0x0.13" />
	<field name="num_con_devices" descr="number of PCIe connected deices / EP on the current port." access="RO" offset="0xC.16" size="0x0.8" />
	<field name="slot_cap" descr="If set to &apos;1&apos;, slot_number field is supported." access="RO" offset="0xC.31" size="0x0.1" />
</node>

<node name="mpls_adjacency_ext" descr="" size="0x18.0" >
	<field name="nhlfe_ptr" descr="NHLFE entry pointer\;Points to the NHLFE table. When using ECMP, points to the \;first entry in the ECMP list." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="ecmp_size" descr="ecmp_size is the amount of sequential entries from the \;nhlfe_ptr (the number of ECMPs). \;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096.\;" access="RW" offset="0x4.0" size="0x0.13" />
	<field name="underlay_router_interface" descr="Underlay router interfaceReserved when Spectrum-1" access="RW" offset="0x10.0" size="0x0.16" />
</node>

<node name="mpnhlfe_ext" descr="" size="0x4c.0" >
	<field name="a" descr="Activity. Set for new entries. Set if a packet lookup has hit on the \;specific entry. \;To clear the a bit, use &quot;clear activity&quot; ca operation.\;Enabled by activity_dis in MPGCR, see Section 14.8.1, &quot;MPGCR \;- MPLS General Configuration Register,&quot; on page 2071" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="ca" descr="Clear activity, valid only for read access:\;0: do not clear activity\;1: clear activity" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="nhlfe_ptr" descr="Index in the NHLFE table\;For Spectrum, the index is to the KVD linear, see Appendix \;A.3.1.2, &quot;KVD Central Database Linear Entries&quot; (page 2254)" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="v" descr="Valid indication\;" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="forward_action" descr="NHLFE Action\;0: Forward_to_Ethernet\;1: Forward_to_IP_Router\;2: Continue_Lookups - if there is another label then lookup ILM, \;else Forward to IP Router\;3: Next_NHLFE\;" access="RW" enum="Forward_to_Ethernet=0x0,Forward_to_IP_Router=0x1,Continue_Lookups=0x2,Next_NHLFE=0x3" offset="0x8.0" size="0x0.4" />
	<field name="trap_id" descr="Trap ID to be reported to CPU\;For Spectrum-1 Trap-ID is MPLS_NHLFE0 or MPLS_NHLFE1\;For Spectrum-2/3 Trap-ID is MPLS_NHLFE0 .. MPLS_NHLFE3\;For trap_action of NOP, MIRROR and DISCARD__ERROR \;trap_id is reserved" access="RW" offset="0xC.0" size="0x0.9" />
	<field name="trap_action" descr="Trap Action\;0: NOP\;1: TRAP\;2: MIRROR_TO_CPU\;3: MIRROR\;4: DISCARD_ERROR, see DISCARD_LSR3 trap_id" access="RW" offset="0xC.28" size="0x0.4" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x10.24" size="0x0.8" />
	<field name="nhlfe_parameters" descr="The fields in parameters are depended on forward_action as fol\;lows:\;Table 2131, &quot;Parameters - Forward to Ethernet Layout,&quot; on \;page 2080\;Table 2133, &quot;Parameters - Forward to IP Router Layout,&quot; on \;page 2083\;Table 2135, &quot;Parameters - Continue Lookups Layout,&quot; on \;page 2085\;Table 2137, &quot;Parameters - Next NHLFE Layout,&quot; on page 2087\;" subnode="mpnhlfe_nhlfe_parameters_auto_ext" access="RW" offset="0x30.0" size="0x1c.0" union_selector="$(parent).forward_action" />
</node>

<node name="mpnhlfe_nhlfe_parameters_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="mpnhlfe_param_eth_ext" descr="" subnode="mpnhlfe_param_eth_ext" offset="0x0.0" selected_by="Forward_to_Ethernet" size="0x1c.0" />
	<field name="mpnhlfe_param_iprouter_ext" descr="" subnode="mpnhlfe_param_iprouter_ext" offset="0x0.0" selected_by="Forward_to_IP_Router" size="0x1c.0" />
	<field name="mpnhlfe_param_lookups_ext" descr="" subnode="mpnhlfe_param_lookups_ext" offset="0x0.0" selected_by="Continue_Lookups" size="0x1c.0" />
	<field name="next_nhlfe_ext" descr="" subnode="next_nhlfe_ext" offset="0x0.0" selected_by="Next_NHLFE" size="0x1c.0" />
</node>

<node name="mpnhlfe_param_eth" descr="" size="0x1c.0" >
	<field name="exp" descr="EXP value for set_exp\;Ignored by the device when protection_active = 1" access="RW" offset="0x0.16" size="0x0.3" />
	<field name="set_exp" descr="Set the packet EXP with exp value\;Ignored by the device when protection_active = 1" access="RW" offset="0x0.19" size="0x0.1" />
	<field name="exp_rw" descr="EXP Re-write\;0: Preserve the value of the rewrite_enable\;1: Set the rewrite_enable\;2: Clear the rewrite_enable\;Ignored by the device when protection_active = 1" access="RW" offset="0x0.20" size="0x0.2" />
	<field name="usp_exp" descr="Update Switch Priority and Packet Color based on EXP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s EXP field as configured by MPEPM. Relevant for \;packets within the MPLS domain.\;Note: the function of set_exp is done prior to the function of usp_\;exp\;Ignored by the device when protection_active = 1\;See Section 14.8.8, &quot;MPEPM - MPLS EXP to Priority Mapping \;Register,&quot; on page 2095." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="usp_dscp" descr="Update Switch Priority and Packet Color based on DSCP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s DSCP field as configured by RDPM. \;Note that this field takes effect only if the IP header is exposed as a \;result of this NHLFE action, otherwise if usp_exp is set then usp_\;exp will effect.\;Ignored by the device when protection_active = 1\;See Section 13.10.20, &quot;RDPM - Router DSCP to Priority Mapping \;Register,&quot; on page 1956\;" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dscp_rw" descr="DSCP Re-write Enable.\;Controlling the rewrite_enable for DSCP:\;0: Preserve the value of the rewrite_enable bit\;1: Set the rewrite_enable bit\;2: Clear the rewrite_enable bit\;Note that this field takes effect only if the IP header is exposed as a \;result of this NHLFE action\;Ignored by the device when protection_active = 1\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="label_id" descr="Label id to push to the label stack\;Reserved when label_action is &apos;0&apos;, &apos;1&apos; or &apos;3&apos;" access="RW" offset="0x4.0" size="0x0.20" />
	<field name="label_action" descr="Label action:\;0: no php, no push. Reserved when protection_active = &apos;0&apos;\;1: php. Enables updating the EXP/DSCP and TTL of outermost \;label. When protection_active = &apos;1&apos; this does nothing.\;2: push label. Push a new label with label id label_id \;\;\;\;" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="dmac_47_32" descr="Destination MAC\;The MAC address of the next hop\;Ignored by the device when protection_active = 1" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="dmac_31_0" descr="Destination MAC\;The MAC address of the next hop\;Ignored by the device when protection_active = 1" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="egress_router_interface" descr="Egress RIF\;Ignored by the device when protection_active = 1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="protection_active" descr="The protection_nhlfe_ptr is active\;When set, the device will use the backup path pointed by protec\;tion_nhlfe_ptr\;Reserved when protection_en is &apos;0&apos;\;Note: currently reserved, must be &apos;0&apos;" access="RW" offset="0x14.24" size="0x0.1" />
	<field name="protection_en" descr="Protection enable, indicating that the LSP is protected and there is \;a valid protection_nhlfe_ptr (but may not be currently active)\;Allows MPFT to modify the protection_active\;Note: currently reserved, must be &apos;0&apos;" access="RW" offset="0x14.25" size="0x0.1" />
	<field name="protection_nhlfe_ptr" descr="Protection NHLFE pointer\;A pointer to the backup NHLFE entry used for FRR\;Note: currently reserved, must be &apos;0&apos;" access="RW" offset="0x18.0" size="0x0.24" />
</node>

<node name="mpnhlfe_param_eth_ext" descr="" size="0x1c.0" >
	<field name="exp" descr="EXP value for set_exp\;Ignored by the device when protection_active = 1" access="RW" offset="0x0.16" size="0x0.3" />
	<field name="set_exp" descr="Set the packet EXP with exp value\;Ignored by the device when protection_active = 1" access="RW" offset="0x0.19" size="0x0.1" />
	<field name="exp_rw" descr="EXP Re-write\;0: Preserve the value of the rewrite_enable\;1: Set the rewrite_enable\;2: Clear the rewrite_enable\;Ignored by the device when protection_active = 1" access="RW" offset="0x0.20" size="0x0.2" />
	<field name="usp_exp" descr="Update Switch Priority and Packet Color based on EXP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s EXP field as configured by MPEPM. Relevant for \;packets within the MPLS domain.\;Note: the function of set_exp is done prior to the function of usp_\;exp\;Ignored by the device when protection_active = 1\;See Section 14.8.8, &quot;MPEPM - MPLS EXP to Priority Mapping \;Register,&quot; on page 2095." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="usp_dscp" descr="Update Switch Priority and Packet Color based on DSCP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s DSCP field as configured by RDPM. \;Note that this field takes effect only if the IP header is exposed as a \;result of this NHLFE action, otherwise if usp_exp is set then usp_\;exp will effect.\;Ignored by the device when protection_active = 1\;See Section 13.10.20, &quot;RDPM - Router DSCP to Priority Mapping \;Register,&quot; on page 1956\;" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dscp_rw" descr="DSCP Re-write Enable.\;Controlling the rewrite_enable for DSCP:\;0: Preserve the value of the rewrite_enable bit\;1: Set the rewrite_enable bit\;2: Clear the rewrite_enable bit\;Note that this field takes effect only if the IP header is exposed as a \;result of this NHLFE action\;Ignored by the device when protection_active = 1\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="label_id" descr="Label id to push to the label stack\;Reserved when label_action is &apos;0&apos;, &apos;1&apos; or &apos;3&apos;" access="RW" offset="0x4.0" size="0x0.20" />
	<field name="label_action" descr="Label action:\;0: no php, no push. Reserved when protection_active = &apos;0&apos;\;1: php. Enables updating the EXP/DSCP and TTL of outermost \;label. When protection_active = &apos;1&apos; this does nothing.\;2: push label. Push a new label with label id label_id \;\;\;\;" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="dmac_47_32" descr="Destination MAC\;The MAC address of the next hop\;Ignored by the device when protection_active = 1" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="dmac_31_0" descr="Destination MAC\;The MAC address of the next hop\;Ignored by the device when protection_active = 1" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="egress_router_interface" descr="Egress RIF\;Ignored by the device when protection_active = 1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="protection_active" descr="The protection_nhlfe_ptr is active\;When set, the device will use the backup path pointed by protec\;tion_nhlfe_ptr\;Reserved when protection_en is &apos;0&apos;\;Note: currently reserved, must be &apos;0&apos;" access="RW" offset="0x14.24" size="0x0.1" />
	<field name="protection_en" descr="Protection enable, indicating that the LSP is protected and there is \;a valid protection_nhlfe_ptr (but may not be currently active)\;Allows MPFT to modify the protection_active\;Note: currently reserved, must be &apos;0&apos;" access="RW" offset="0x14.25" size="0x0.1" />
	<field name="protection_nhlfe_ptr" descr="Protection NHLFE pointer\;A pointer to the backup NHLFE entry used for FRR\;Note: currently reserved, must be &apos;0&apos;" access="RW" offset="0x18.0" size="0x0.24" />
</node>

<node name="mpnhlfe_param_iprouter" descr="" size="0x1c.0" >
	<field name="usp_dscp" descr="Update Switch Priority and Packet Color based on DSCP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s DSCP field as configured by RDPM. Note that this \;field is takes effect only if the IP header tis exposed as a result of \;this NHLFE action. See Section 13.10.20, &quot;RDPM - Router DSCP \;to Priority Mapping Register,&quot; on page 1956\;" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dscp_rw" descr="DSCP Re-write Enable\;Controlling the rewrite_enable for DSCP:\;0: Preserve the value of the rewrite_enable bit\;1: Set the rewrite_enable bit\;2: Clear the rewrite_enable bit\;Note that this field takes effect only if the IP header is exposed as a \;result of this NHLFE action.\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="irif" descr="Ingress Router Interface used for forwarding the packet to the \;router.\;Reserved when irifv = &apos;0&apos;" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="irifv" descr="irif is valid\;Indicates that the irif, dscp_rw, usp_dscp are field is valid. \;Useful for the case that Continue Lookups have a valid irif. If mul\;tiple NHLFE lookups are performed, the device will use the last \;valid irif .SW must make sure that at least 1 irif is valid otherwise \;the packet will be discarded\;" access="RW" offset="0xC.24" size="0x0.1" />
	<field name="egress_router_interface" descr="Egress RIF\;Reserved when irifv = &apos;0&apos;\;Reserved when Spectrum-1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="erifv" descr="egress_router_interface is valid\;Reserved when Spectrum-1" access="RW" offset="0x10.24" size="0x0.1" />
</node>

<node name="mpnhlfe_param_iprouter_ext" descr="" size="0x1c.0" >
	<field name="usp_dscp" descr="Update Switch Priority and Packet Color based on DSCP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s DSCP field as configured by RDPM. Note that this \;field is takes effect only if the IP header tis exposed as a result of \;this NHLFE action. See Section 13.10.20, &quot;RDPM - Router DSCP \;to Priority Mapping Register,&quot; on page 1956\;" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dscp_rw" descr="DSCP Re-write Enable\;Controlling the rewrite_enable for DSCP:\;0: Preserve the value of the rewrite_enable bit\;1: Set the rewrite_enable bit\;2: Clear the rewrite_enable bit\;Note that this field takes effect only if the IP header is exposed as a \;result of this NHLFE action.\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="irif" descr="Ingress Router Interface used for forwarding the packet to the \;router.\;Reserved when irifv = &apos;0&apos;" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="irifv" descr="irif is valid\;Indicates that the irif, dscp_rw, usp_dscp are field is valid. \;Useful for the case that Continue Lookups have a valid irif. If mul\;tiple NHLFE lookups are performed, the device will use the last \;valid irif .SW must make sure that at least 1 irif is valid otherwise \;the packet will be discarded\;" access="RW" offset="0xC.24" size="0x0.1" />
	<field name="egress_router_interface" descr="Egress RIF\;Reserved when irifv = &apos;0&apos;\;Reserved when Spectrum-1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="erifv" descr="egress_router_interface is valid\;Reserved when Spectrum-1" access="RW" offset="0x10.24" size="0x0.1" />
</node>

<node name="mpnhlfe_param_lookups" descr="" size="0x1c.0" >
	<field name="usp_dscp" descr="Update Switch Priority and Packet Color based on DSCP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s DSCP field as configured by RDPM. \;This field is ignored by the device when lookup on next label is \;done\;See Section 13.10.20, &quot;RDPM - Router DSCP to Priority Mapping \;Register,&quot; on page 1956\;" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dscp_rw" descr="DSCP Re-write Enable\;Controlling the rewrite_enable for DSCP:\;0 - Preserve the value of the rewrite_enable bit\;1 - Set the rewrite_enable bit\;2 - Clear the rewrite_enable bit\;This field is ignored by the device when lookup on next label is \;done\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="irif" descr="Ingress Router Interface used for forwarding the packet to the \;router.\;Reserved when irifv = &apos;0&apos;" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="irifv" descr="irif is valid\;Indicates that the irif, dscp_rw, usp_dscp are field is valid. \;Irif is needed for forward to IP router. If another lookup is done \;then the irif is stored for this packet for later use.\;SW must make sure that at least 1 irif is valid otherwise the packet \;will be discarded\;" access="RW" offset="0xC.24" size="0x0.1" />
	<field name="egress_router_interface" descr="Egress RIF\;Reserved when irifv = &apos;0&apos;\;Reserved when Spectrum-1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="erifv" descr="egress_router_interface is valid\;Reserved when Spectrum-1" access="RW" offset="0x10.24" size="0x0.1" />
</node>

<node name="mpnhlfe_param_lookups_ext" descr="" size="0x1c.0" >
	<field name="usp_dscp" descr="Update Switch Priority and Packet Color based on DSCP\;Forces recalculation of the Switch Priority and Packet Color based \;on the packet&apos;s DSCP field as configured by RDPM. \;This field is ignored by the device when lookup on next label is \;done\;See Section 13.10.20, &quot;RDPM - Router DSCP to Priority Mapping \;Register,&quot; on page 1956\;" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dscp_rw" descr="DSCP Re-write Enable\;Controlling the rewrite_enable for DSCP:\;0 - Preserve the value of the rewrite_enable bit\;1 - Set the rewrite_enable bit\;2 - Clear the rewrite_enable bit\;This field is ignored by the device when lookup on next label is \;done\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="irif" descr="Ingress Router Interface used for forwarding the packet to the \;router.\;Reserved when irifv = &apos;0&apos;" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="irifv" descr="irif is valid\;Indicates that the irif, dscp_rw, usp_dscp are field is valid. \;Irif is needed for forward to IP router. If another lookup is done \;then the irif is stored for this packet for later use.\;SW must make sure that at least 1 irif is valid otherwise the packet \;will be discarded\;" access="RW" offset="0xC.24" size="0x0.1" />
	<field name="egress_router_interface" descr="Egress RIF\;Reserved when irifv = &apos;0&apos;\;Reserved when Spectrum-1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="erifv" descr="egress_router_interface is valid\;Reserved when Spectrum-1" access="RW" offset="0x10.24" size="0x0.1" />
</node>

<node name="mpnhlfeb_ext" descr="" size="0x420.0" >
	<field name="v" descr="Valid\;0: remove ecmp entries\;1: Write ecmp entries" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="nhlfe_ptr" descr="Index in the NHLFE table\;For Spectrum, the index is to the KVD linear, see \;Section A.3.1.2, &quot;KVD Central Database Linear Entries,&quot; on \;page 2254" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="num_rec" descr="Number of records" access="OP" offset="0x8.0" size="0x0.8" />
	<field name="trap_id" descr="Trap ID to be reported to CPU\;Trap-ID is MPLS_NHLFE0 .. MPLS_NHLFE3\;For trap_action of NOP, MIRROR and DISCARD__ERROR \;trap_id is reserved" access="WO" offset="0xC.0" size="0x0.9" />
	<field name="trap_action" descr="Trap Action\;0: NOP\;1: TRAP\;2: MIRROR_TO_CPU\;3: MIRROR\;4: DISCARD_ERROR" access="WO" enum="NOP=0x0,TRAP=0x1,MIRROR_TO_CPU=0x2,MIRROR=0x3,DISCARD_ERROR=0x4" offset="0xC.28" size="0x0.4" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="WO" offset="0x10.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622\;Not supported by SwitchX and SwitchX-2" access="WO" offset="0x10.24" size="0x0.8" />
	<field name="record" descr="Record\;See Table 2141, &quot;MPNHLFEB - Record Layout,&quot; on page 2089" subnode="mpnhlfeb_record" access="WO" high_bound="31" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="mpnhlfeb_record" descr="" size="0x20.0" >
	<field name="size" descr="Size\;The amount of entries to be written for this record. Allows \;writing this record multiple consecutive times\;Range 1..4095" access="WO" offset="0x0.16" size="0x0.12" />
	<field name="forward_action" descr="NHLFE Action:\;0: Forward_to_Ethernet\;1: Forward_to_IP_Router\;2: Continue_Lookups - If there is another label then lookup \;ILM, else Forward to IP Router\;3: Next_NHLFE" access="WO" enum="Forward_to_Ethernet=0x0,Forward_to_IP_Router=0x1,Continue_Lookups=0x2,Next_NHLFE=0x3" offset="0x0.28" size="0x0.4" />
	<field name="nhlfe_parameters" descr="The fields in parameters are depended on forward_action as \;follows:\;Table 2131, &quot;Parameters - Forward to Ethernet Layout,&quot; on \;page 2080\;Table 2133, &quot;Parameters - Forward to IP Router Layout,&quot; on \;page 2083\;Table 2135, &quot;Parameters - Continue Lookups Layout,&quot; on \;page 2085\;Table 2137, &quot;Parameters - Next NHLFE Layout,&quot; on \;page 2087\;Note: only 224 msb of the referenced entries entry are used" subnode="mpnhlfeb_record_nhlfe_parameters_auto" access="WO" offset="0x4.0" size="0x1c.0" union_selector="$(parent).forward_action" />
</node>

<node name="mpnhlfeb_record_nhlfe_parameters_auto" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="mpnhlfe_param_eth" descr="" subnode="mpnhlfe_param_eth" offset="0x0.0" selected_by="Forward_to_Ethernet" size="0x1c.0" />
	<field name="mpnhlfe_param_iprouter" descr="" subnode="mpnhlfe_param_iprouter" offset="0x0.0" selected_by="Forward_to_IP_Router" size="0x1c.0" />
	<field name="mpnhlfe_param_lookups" descr="" subnode="mpnhlfe_param_lookups" offset="0x0.0" selected_by="Continue_Lookups" size="0x1c.0" />
	<field name="next_nhlfe" descr="" subnode="next_nhlfe" offset="0x0.0" selected_by="Next_NHLFE" size="0x1c.0" />
</node>

<node name="mpqdr_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number (receive port)\;Supported from CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="exp" descr="For ingress LER, the default EXP" access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="mprs_ext" descr="" size="0x14.0" >
	<field name="parsing_depth" descr="Minimum Parsing Depth\;Units of Bytes. \;Need to enlarge parsing depth according to L3, MPLS, tunnels, \;ACL rules, custom_bytes, traps, hash etc. \;Default is 96B\;Value must be larger than 0\;The device will parse no deeper than cap_max_parsing_depth\;Reserved when SwitchX/-2\;\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="parsing_en" descr="Parsing enable\;Bit0: enable parsing of NVE of types VXLAN, VXLAN-GPE, \;GENEVE and NVGRE, default enabled\;Note: for proper parsing the parsing_depth must also be config\;ured\;Reserved when SwitchX/-2 also reserved when Spectrum-2 since \;Spectrum-2 supports concurrent QinQ and NVE" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="ctipl_l2_length" descr="L2 header length to be added to IP length for Cut Through IP \;Length Based mode\;This length should include DMAC, SMAC, L2 tags (VLANs \;etc.), MPLS labels. e.g. configure 52 for DMAC+SMAC + 10 \;tags/labels\;Units of Bytes\;Reserved when ctipl = 0" access="RW" offset="0x8.0" size="0x0.7" />
	<field name="ctipl" descr="Cut Through IP Length Based\;0: Cut through from low to high rate is based on MTU and port \;rates (default)\;1: Cut through from low to high rate is based on IP Length and \;port rates for IP packets, else, based on MTU" access="RW" offset="0x8.8" size="0x0.1" />
	<field name="vxlan_udp_dport" descr="VXLAN UDP destination port\;Used for identifying VXLAN packets and for dport field in encap\;sulation\;Default 4789" access="RW" offset="0x10.0" size="0x0.16" />
</node>

<node name="mpsc_ext" descr="" size="0x14.0" >
	<field name="local_port" descr="Local port number (Rx ports)\;Not supported from CPU port\;Not supported from router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cong" descr="Congestion\;Sample only when egress congestion\;The congestion configuration is done by SBCTC, see\;Section 9.8.16, &quot;SBCTC - Shared Buffer Congestion Threshold \;Configuration Register,&quot; on page 1321\;For Switch-IB/2 the congestion is port congestion. Thus need to \;configure port congestion in SBGCR.tele_entitiy, see \;Section 9.8.1, &quot;SBGCR - Shared Buffer Global Configuration Reg\;ister,&quot; on page 1292\;For Switch-IB/2 this is a global configuration, affecting all \;local_ports\;Reserved when Spectrum-1/-2/-3" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="e" descr="Enable\;0: Disable sampling on port local_port (disabled)\;1: Enable sampling on port local_port" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="c" descr="Clear counter\;Clears the count_sample_drop" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="rate" descr="Sampling rate = 1 out of rate packets (with randomization around \;the point)\;Valid values are: 1 to 3.5*10^9\;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="count_sample_drops_high" descr="A count of frames that were discarded after sampling. Discard is \;due to CPU policers or lack of resources towards the CPU.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="count_sample_drops_low" descr="A count of frames that were discarded after sampling. Discard is \;due to CPU policers or lack of resources towards the CPU.\;" access="RO" offset="0x10.0" size="0x4.0" />
</node>

<node name="mqis_reg_ext" descr="" size="0x18.0" >
	<field name="info_type" descr="Type of information string to be queried:\;0x0: VPD - Read the PCI Vital Product Data capability con\;tent.\;0x1: MODEL_NAME\;0x2: MODEL_DESCRIPTION\;0x3: IMAGE_VSD\;0x4: DEVICE_VSD\;0x5: ROM_INFO\;other values are reserved." access="INDEX" enum="MODEL_NAME=0x1,MODEL_DESCRIPTION=0x2,IMAGE_VSD=0x3,DEVICE_VSD=0x4,ROM_INFO=0x5" offset="0x0.0" size="0x0.8" />
	<field name="info_length" descr="Total size of the information string, according to info_type. \;Value given in bytes." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="read_length" descr="Number of bytes requested. The device returns the number \;of bytes actually read." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="read_offset" descr="Offset in bytes of the first byte requested to read." access="INDEX" offset="0x8.16" size="0x0.16" />
	<field name="info_string" descr="Information string accessed, according to info_type. If the \;information is not available, a NULL string is returned." access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
</node>

<node name="mrrr_ext" descr="" size="0x8.0" >
	<field name="init_rr" descr="Initiate resource release:\;0: Resource release type 0 \;1: Resource release type 1\;If rr_status is &quot;1&quot; then this operation fails" access="WO" offset="0x0.0" size="0x0.4" />
	<field name="rr_status" descr="Resource release status:\;0: No resource release process is ongoing\;1: Resource release process is ongoing" access="RO" offset="0x4.0" size="0x0.4" />
</node>

<node name="mrsr_ext" descr="" size="0x8.0" >
	<field name="command" descr="Reset/shutdown command\;0 - do nothing\;1 - software reset\;3 - enclosure reset (requires system support)\;4 - shutdown (requires system support)" access="WO" offset="0x0.0" size="0x0.4" />
</node>

<node name="mrtc_reg_ext" descr="" size="0x10.0" >
	<field name="time_synced" descr="If set, the time returned in time_l/time_h is the number of microseconds \;passed since 1/1/1970. \;otherwise, the time_l/time_h measures the time since the NIC boot." access="RO" offset="0x0.31" size="0x0.1" />
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
	<field name="crc" descr="Each bit represent whether a CRC error occured on the \;management interface to the tile number." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="bypass" descr="Each bit represent whether a bypass clock is run on the \;corresponding tile." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="fatal_dft" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="freq0" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0xC.0" size="0x0.5" />
	<field name="freq1" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0xC.5" size="0x0.5" />
	<field name="freq2" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0xC.10" size="0x0.5" />
	<field name="freq3" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0xC.15" size="0x0.5" />
	<field name="freq4" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0xC.20" size="0x0.5" />
	<field name="freq5" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0xC.25" size="0x0.5" />
	<field name="freq6" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0x10.0" size="0x0.5" />
	<field name="freq7" descr="Each field represent the frequency dividing factor for the \;core clock for each of the tiles" access="RO" offset="0x10.5" size="0x0.5" />
</node>

<node name="mtbr_reg_ext" descr="" size="0x18.0" >
	<field name="base_sensor_index" descr="Base sensor index\;Sensors are read starting from base_sensor_index\;Sensor 0 is the ASIC sensor, sensors 1-63 are ambient sensors and \;sensors 64-127 are mapped to the SFP+/QSFP modules sequen\;tially (module 0 is mapped to sensor 64, module 1 to sensor 65 \;and so on). Gearbox sensors starts from 256 index." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="num_rec" descr="Number of records to read\;Range 1..255" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="temperature_record" descr="Temperature record\;See Table 1369, &quot;MTBR - Temperature Record Layout,&quot; on \;page 1544" subnode="mtbr_temp_record" access="RO" high_bound="1" low_bound="0" offset="0x10.0" size="0x8.0" />
</node>

<node name="mtbr_temp_record" descr="" size="0x4.0" >
	<field name="temperature" descr="Temperature reading from the sensor. Units of 0.125 Celsius \;degrees.\;If no ambient sensor is present then the value is &apos;0&apos;. Also for a \;passive copper case.\;0x8000:NO_CONN- No cable is connected.\;0x8001: NO_TEMP_SENS - In case a cable is connected but the \;temperature sensing is not supported.\;0x8002: INDX_NA- No such cable index. Bigger than the number \;of modules.\;0x8003: INCORRECT_SENS_INFO - Sensor information is \;incorrect." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.\;When the bit relevant MTMP.mte is cleared, the field max_tem\;perature is reserved.\;The value will be &apos;0&apos; for any of the &apos;800X&apos; temperature values and \;for &apos;0&apos; value." access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="mtcap_ext" descr="" size="0x10.0" >
	<field name="sensor_count" descr="Number of sensors supported by the device\;This includes the ASIC and the ambient sensors. QSFP module sen\;sors are not included." access="RO" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Only ASIC and \;ambient sensors are supported. Each bit represents a sensor.\;0: Not connected or not supported\;1: Supports temperature measurements" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="mtecr_ext" descr="" size="0x60.0" >
	<field name="sensor_count" descr="Number of sensors supported by the device\;This includes the ASIC, ambient sensors, Gearboxes etc. QSFP \;module sensors are not included." access="RO" offset="0x0.0" size="0x0.12" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read from.\;" access="RO" offset="0x0.16" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x4.28" size="0x0.4" />
	<field name="sensor_map_0" descr="Mapping of system sensors supported by the device. Each bit rep\;resents a sensor.\;This field is size variable based on the last_sensor field and in gran\;ularity of 32bits.\;0: Not connected or not supported\;1: Supports temperature measurements" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mtewe_ext" descr="" size="0x5c.0" >
	<field name="sensor_count" descr="Number of sensors supported by the device\;This includes the ASIC, ambient sensors, Gearboxes etc. QSFP \;module sensors are not included." access="RO" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read from." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="sensor_warning_0" descr="Bit vector indicating which of the sensor reading is above thresh\;old.\;This field is size dependent and based on last_sensor field and in \;granularity of 32bits." access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="mtmp_ext" descr="" size="0x20.0" >
	<field name="sensor_index" descr="Sensors index to access.\;\;64-127 of sensor_index are mapped to the SFP+/QSFP modules \;sequentially (module 0 is mapped to sensor_index 64, module 1 \;to sensor_index 65 and so on). Gearbox sensors are from index \;256." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="temperature" descr="Temperature reading from the sensor. Reading is in 0.125 Cel\;sius degrees units.\;For negative values 2&apos;s complement is used (for example: -3.25 \;Celsius will read as 0xFFE6)" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.\;When the bit mte is cleared, the field max_temperature is \;reserved." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="mtr" descr="Max Temperature Reset - clears the value of the max tempera\;ture register" access="OP" offset="0x8.30" size="0x0.1" />
	<field name="mte" descr="Max Temperature Enable - enables measuring the max tempera\;ture on a sensor" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="temperature_threshold_hi" descr="temperature_threshold_hi refers to the high threshold of Warn\;ing Event. If the sensor temperature measurement is above the \;threshold (and events are enabled), an event will be generated.\;threshold_hi and threshold_lo implements hysteresis mecha\;nism of the threshold preventing toggling of the indication.\;Note that temperature_threshold_hi must be equal or lower \;than the system requirement.\;System requirement for module is the module warning tempera\;ture.\;System requirement for board/silicon sensors is according to \;product information parameters\;Note that the temperature threshold can be used to generate an \;event message or an interrupt using GPIO" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="tee" descr="Temperature Event Enable\;0 - do not generate event\;1 - generate event \;2 - generate single event\;Note: events may be delayed by up to 60 Seconds from &quot;gener\;ate event&quot; or &quot;generate single event&quot;\;Supported Only for switch devices. For HCA devices, SW \;should register Temperature Warning Event to an EQ." access="RW" offset="0xC.30" size="0x0.2" />
	<field name="temperature_threshold_lo" descr="temperature_threshold_hi refers to the low threshold of Warning \;Event. The offset threshold_lo implements the lower threshold \;for the hysteresis mechanism of over temperature alert. Once \;alert is set, if the temperature goes below this threshold, the alert \;is cleared.\;Note that temperature_threshold_lo must be at least 5 degrees \;lower than temperature_threshold_hi" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="sensor_name_hi" descr="Sensor Name\;8 character long sensor name" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="sensor_name_lo" descr="Sensor Name\;8 character long sensor name" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mtpcpc_ext" descr="" size="0x28.0" >
	<field name="local_port" descr="local_port\;Supported to/from CPU port\;Reserved when pport = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pport" descr="Per port:\;0: config is global. When reading - the local_port is 1\;1: config is per port" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="ptp_trap_en" descr="Enable PTP traps\;The trap_id is configured by MTPTPT" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="ing_correction_message_type" descr="Bitwise vector of PTP message types to update correctionField\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: \;Delay_Req)\;Supported also from CPU port\;Default all 0" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="egr_correction_message_type" descr="Bitwise vector of PTP message types to update correctionField\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: \;Delay_Req)\;Supported also from CPU port\;Default all 0" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="num_domains" descr="Number of valid domains for match:\;0: ignore domain field (&quot;always match&quot;)\;1: Match only if domain[0] has a match\;2: Match only if domain[0] or [1] have a match\;etc.\;Range 0..cap_max_ptp_domains" access="RW" offset="0x20.0" size="0x0.8" />
	<field name="domain" descr="domain for matching\;" access="RW" high_bound="3" low_bound="0" offset="0x24.24" size="0x4.0" />
</node>

<node name="mtpppc_ext" descr="" size="0x10.0" >
	<field name="ing_timestamp_message_type" descr="Bitwise vector of PTP message types to timestamp at ingress\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: \;Delay_Req)\;Default all 0\;" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="egr_timestamp_message_type" descr="Bitwise vector of PTP message types to timestamp at egress.\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: \;Delay_Req)\;Default all 0\;" access="RW" offset="0xC.0" size="0x0.16" />
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
	<field name="cap_pin_7_mode" descr="Capability of PPS pin #7\;Bit0: support_pps_in\;Bit1: support_pps_out\;Bit2: support_virtual_pin - [Internal] For Switches, only pin 7 is a \;virtual pin, and it is only virtual pin" access="RO" enum="support_pps_in=0x1,support_pps_out=0x2,support_virtual_pin=0x4" offset="0xC.24" size="0x0.4" />
	<field name="field_select" descr="Field select indicates which fields to modify in write operation to \;this register. This field selector supported only when \;MCAM.mtpps_fs==1. if MCAM.mtpps_fs==0 then SW should \;ensure that all the WO/RW fields are valid. \;Bit 0: enable\;Bit 1: utc_mode\;Bit 2: pattern\;Bit 3: pin_mode\;Bit 4: time_stamp\;Bit 5: out_pulse_duration\;Bit 6: out_periodic_adjustment\;Bit 7: enhanced_out_periodic_adjustment\;Bit 8: npps" access="WO" enum="enable=0x1,utc_mode=0x2,pattern=0x4,pin_mode=0x8,time_stamp=0x10,out_pulse_duration=0x20,out_periodic_adjustment=0x40,enhanced_out_periodic_adjustment=0x80,npps=0x100" offset="0x10.0" size="0x4.0" />
	<field name="pin" descr="Pin to be configured or queried out of the supported pins." access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="pin_mode" descr="Pin mode to be used. The mode must comply with the supported \;modes of the requested pin.\;0x0: pps_in\;0x1: pps_out\;0x2: virtual_pin\;0x3: pps_out_and_virtual_pin\;[Internal]: Spectrum-1 supports only virtual_pin and only on \;pin=7\;Operation will fail if pin does not support the required mode." access="RW" enum="pps_in=0x0,pps_out=0x1,virtual_pin=0x2,pps_out_and_virtual_pin=0x3" offset="0x20.8" size="0x0.4" />
	<field name="pattern" descr="When pin_mode = pps_in:\;0x0: Rising edge \;0x1: Falling edge \;\;When pin_mode = pps_out:\;0x0: Pulse - (one shot) The device will generate a pulse at \;time_stamp time with a duration of out_pulse_duration. \;0x1: Periodic - the device will generate periodical pulses with \;pulse duration  of  out_pulse_duration every 1 second according \;to internal clock. The 1st pulse will be generated at time_stamp \;time.\;Reserved when pin_mode = 0x2 virtual_pin\;\;" access="RW" offset="0x20.16" size="0x0.4" />
	<field name="enable" descr="Enables the PPS functionality the specific pin.\;0x0: Disable \;0x1: Enable" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x20.31" size="0x0.1" />
	<field name="time_stamp" descr="When pin_mode = pps_in, the latched device time when it was \;triggered from the external GPIO pin. \;When pin_mode = pps_out or virtual_pin or \;pps_out_and_virtual_pin, the target time to generate \;next output signal. \;When utc_mode = FREE_RUNNING - Time is in units \;of device clock. \;[Internal] When utc_mode = UTC - Bits 29:0 are nSec, \;bits 47:30 are Sec \;\;For Spectrum-1 the device clock frequency is 6.4nSec" subnode="uint64" access="RW" offset="0x28.0" size="0x8.0" />
	<field name="out_periodic_adjustment" descr="Frequency adjustment: Every PPS the HW frequency will be \;adjusted by this value. Units of HW clock, where HW counts \;10^9 HW clocks for 1 HW second.\;Range is from -32768 to +32767\;The hardware does consecutive frequency adjustment \;Reserved when pin_mode != ptp_out\;Reserved when switches\;" access="RW" offset="0x30.0" size="0x0.16" />
	<field name="out_pulse_duration" descr="Output pulse duration in units of mSec. \;Range is 1 to 1000. \;Reserved when pin_mode != ptp_out" access="RW" offset="0x30.16" size="0x0.16" />
	<field name="enhanced_out_periodic_adjustment" descr="Same as out_periodic_adjustment field, but supports a wider \;range.\;supported only when \;MCAM.mtpps_enhanced_out_periodic_adjustment==1.\;mutual exclusive with out_periodic_adjustment, i.e. when \;enhanced_out_periodic_adjustment!=0, out_periodic_adjustment \;is invalid.\;Reserved when switches" access="RW" offset="0x34.0" size="0x4.0" />
</node>

<node name="mtpptr_ext" descr="" size="0x50.0" >
	<field name="dir" descr="Direction\;0: Ingress\;1: Egress" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="local_port" descr="local_port\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ovf" descr="Overflow\;The HW timestamp FIFO had an overflow\;The overflow state is cleared when clr = 1" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="read_one" descr="Read up to one record\;May response with num_rec = 0 or 1\;" access="OP" offset="0x4.30" size="0x0.1" />
	<field name="clr" descr="Clear the records" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="num_rec" descr="Number of valid records in the response\;When read_one = 1 then this equals to 1 and only 1 record \;responded, even if the HW FIFO has more than 1 record\;Range 0.. cap_ptp_timestamp_fifo" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="record" descr="Records, see Table 619, &quot;MTPPTR - Record Layout,&quot; on \;page 724" subnode="array128_auto" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mtpspu_ext" descr="" size="0x8.0" >
	<field name="message_type" descr="Set UTC on packets from CPU for PTP packets with the config\;ured message_types.\;This is a necessary but non-sufficient condition since need to \;enable also per port. See Section 4.12.14, &quot;MTPPPC - Monitor\;ing Time Precision Packet Port Configuration,&quot; on page 722\;Message types are defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: \;Delay_Req)" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="mtptp_ext" descr="" size="0x40.0" >
	<field name="portnumber" descr="Identifying a specific PTP port" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="grandmasteridentity" descr="Up to 8 octets of clock identities. Part of SourcePortIdentity" access="RW" high_bound="7" low_bound="0" offset="0x8.24" size="0x8.0" />
	<field name="time_source" descr="The time source according to timeSource enumeration as defined \;in IEEE 1588 spec:\;0x10: ATOMIC_CLOCK\;0x20: GPS\;0x30: TERRESTRIAL_RADIO\;0x40: PTP\;0x50: NTP\;0x60: HAND_SET\;0x90: OTHER\;0xA0: INTERNAL_OSCILLATOR\;FE-F0: For use by alternate PTP profiles" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="li61" descr="LI-61 (leap61). The last minute of the current UTC day contains \;61 seconds. Valid only when utcv is true." access="RW" offset="0x14.8" size="0x0.1" />
	<field name="li59" descr="LI-59 (leap59). The last minute of the current UTC day contains \;59 seconds. Valid only when utcv is true." access="RW" offset="0x14.9" size="0x0.1" />
	<field name="utcv" descr="If set to &apos;1&apos;, the current_utc_offset, li61 and li59 are valid." access="RW" offset="0x14.10" size="0x0.1" />
	<field name="ptp" descr="If set to &apos;1&apos;, the" access="RW" offset="0x14.11" size="0x0.1" />
	<field name="ttra" descr="If set to &apos;1&apos;, the timescale and the value of current_utc_offset are \;raceable to primary reference." access="RW" offset="0x14.12" size="0x0.1" />
	<field name="ftra" descr="If set to &apos;1&apos;, the frequency determining the timescale is traceable \;to primary reference." access="RW" offset="0x14.13" size="0x0.1" />
	<field name="current_utc_offset" descr="Equals to TAI-UTC. Valid only when UTCV is true in sec" access="RW" offset="0x14.16" size="0x0.16" />
</node>

<node name="mtptpt_ext" descr="" size="0x8.0" >
	<field name="trap_id" descr="Trap id:\;0: PTP0\;1: PTP1 - Reserved when Quantum\;2: PTP2ME - Reserved when Spectrum/-2" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="message_type" descr="Bitwise vector of PTP message types to trap. This is a necessary \;but non-sufficient condition since need to enable also per port. \;See Section 4.12.14, &quot;MTPPPC - Monitoring Time Precision \;Packet Port Configuration,&quot; on page 722\;Message types are defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: \;Delay_Req)" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="mtrc_cap_reg_ext" descr="" size="0x84.0" >
	<field name="num_string_db" descr="Number of different string sections building the database" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="trc_ver" descr="Indicates the version of the tracing mechanism.0x0: VER_0\;0x1: VER_1\;other values are reserved" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="trace_to_memory" descr="When set the device supports logging traces to memory" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="trace_owner" descr="Write 0x1 to register for tracer ownership, write 0x0 to de-regis\;ter.\;Read value 0x1 indicates tracer ownership is granted" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="num_string_trace" descr="The number of consecutive event_id that should be interpreted as \;a string trace" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="first_string_trace" descr="The lowest event_id that should be interpreted as a string trace" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="log_max_trace_buffer_size" descr="Log 2 of the maximal size of the trace buffer given in units of \;4KB" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="string_db_param" descr="String DB section parameters." subnode="string_db_parameters" access="RO" high_bound="7" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mtrc_conf_reg_ext" descr="" size="0x80.0" >
	<field name="trace_mode" descr="Tracing mode\;0x1: TRACE_TO_MEMORY\;Other values are reserved." access="RW" offset="0x0.0" size="0x0.4" />
	<field name="log_trace_buffer_size" descr="Log 2 of the Size of the trace buffer, given in units of 4KB.\;Value should not exceed log_max_trace_buffer_size.\;Valid only for trace_mode TRACE_TO_MEMORY.\;Modifying this parameter after the tracer was active may cause \;loss of sync regarding the location of the next trace." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="trace_mkey" descr="MKey registered for the trace buffer access.\;Valid only for trace_mode TRACE_TO_MEMORY.\;Modifying this parameter after the tracer was active may cause \;loss of sync regarding the location of the next trace." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mtrc_ctrl_reg_ext" descr="" size="0x40.0" >
	<field name="modify_field_select" descr="Field select indicated which writable fields to modify\;bit 0: trace_status\;Other bits are reserved." access="WO" offset="0x0.0" size="0x0.16" />
	<field name="arm_event" descr="When set, an event will be generated if new Tracer events were \;logged since last event." access="WO" offset="0x0.27" size="0x0.1" />
	<field name="trace_status" descr="Current status of the tracer\;0x0: DISABLED - logging traces is stopped\;0x1: ACTIVE - logging traces is active" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="current_timestamp_52_32" descr="MSB of the current timesatmp counter" access="RO" offset="0x8.0" size="0x0.21" />
	<field name="current_timestamp_31_0" descr="LSB of the current timesatmp counter" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="mtrc_stdb_reg_ext" descr="" size="0xc.0" >
	<field name="read_size" descr="The number of bytes to read from the String DB. The number of \;bytes must:\;Be a multiple of 64B\;Not exceed the String DB section (with start_offset)\;Not exceed the limitations defined by the medium carrying the Regis\;ter." access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="string_db_index" descr="The section of the String DB being accessed" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="start_offset" descr="The offset in the String DB to read from, given in Bytes. The off\;set must:\;Be a multiple of 64B\;Not exceed the String DB section (with read_size)" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="string_db_data" descr="Strings from the database. The size of this field is defined by \;read_size" access="RO" high_bound="VARIABLE" low_bound="0" offset="0x8.0" size="0x4.0" />
</node>

<node name="mtutc_reg_ext" descr="" size="0x1c.0" >
	<field name="operation" descr="Operation:\;0: SET_TIME_AT_NEXT_SEC - the utc_sec will be sampled at \;the next PPS (of either virtual_pin or hw_utc_nsec wrap around)\;1: SET_TIME_IMMEDIATE - reserved when Spectrum-1\;2: ADJUST_TIME\;3: ADJUST_FREQ_UTC \;4: ADJUST_FREQ_FRC - Free Running Clock\;5: ADJUST_FREQ_BOTH" access="OP" enum="SET_TIME_AT_NEXT_SEC=0x0,ADJUST_TIME=0x2,ADJUST_FREQ_UTC=0x3,ADJUST_FREQ_FRC=0x4,ADJUST_FREQ_BOTH=0x5" offset="0x0.0" size="0x0.4" />
	<field name="freq_adjustment" descr="Frequency adjustment: Every PPS the HW frequency will be \;adjusted by this value. Units of HW clock, where HW counts \;10^9 HW clocks for 1 HW second. The values are represented in \;two&apos;s complement.\;Updated when operation is ADJUST_FREQ\;\;\;\;For Spectrum-2 the FW sets the nominator and denominator of \;the free_running" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="utc_sec" descr="UTC seconds\;Updated when operation is SET_TIME_IMMEDIATE or at next \;PPS when operation is SET_TIME_AT_NEXT_SEC" access="WO" offset="0x10.0" size="0x4.0" />
	<field name="utc_nsec" descr="UTC nSecs\;Range 0..(10^9-1)\;Updated when operation is SET_TIME_IMMEDIATE\;Reserved when Spectrum-1" access="WO" offset="0x14.0" size="0x0.30" />
	<field name="time_adjustment" descr="Time adjustment\;Units of nSec\;Range is from -32768 to +32767\;Reserved when Spectrum-1\;[Internal] Spc-2: FW will hold the emad until the function is done \;by HW. FW may have to hold up to 330uSec" access="WO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mtwe_ext" descr="" size="0x10.0" >
	<field name="sensor_warning" descr="Bit vector indicating which of the sensor reading is above thresh\;old.\;Address 00h bit31 is sensor_warning[127]\;Address 0Ch bit0 is sensor_warning[0]" access="RO" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="multicast_tunnel_ext" descr="" size="0x10.0" >
	<field name="fid" descr="Filtering identifier (FID)\;Reserved when v_fid = 0\;Reserved when ubridge=1\;Reserved when Spectrum-2\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="underlay_mc_ptr_msb" descr="Most significant bits of Underlay Multicast Pointer. Used as a \;pointer to the first entry of the group based link lists of MC entries \;(for NVE tunnels). For Spectrum-1 the number of link lists in the \;group is configured by TNGCR.nve_group_size_mc.\;The pointer points to entries which are configured by TNUMT or \;by TNGEE\;For Spectrum/-2, this points to an entry in the KVD Linear, see \;Appendix A.5.1, &quot;KVD Central Database&quot; (page 2261)" access="RW" offset="0x0.16" size="0x0.16" />
	<field name="mid" descr="Multicast identifier - global identifier that represents the multicast \;group across all devices" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="v_fid" descr="valid FID:\;0: .1Q bridge\;1: .1D bridge\;Reserved when ubridge=1\;Reserved when Spectrum-2\;" access="RW" offset="0x4.23" size="0x0.1" />
	<field name="underlay_mc_ptr_lsb" descr="Least significant bits of pointer to link list of flooding entries (for \;NVE tunnels)\;The pointer may point to TNGEE" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="ecmp_size" descr="ecmp_size:\;ecmp_size is the amount of sequential entries starting from the\;pointer to the first TNUMT/TNGEE (the number of ECMPs).\;0: controlled by TNGCR.nve_group_size_mc\;Values: 1-128, 256, 512, 1024, 2048 and 4096\;" access="RW" offset="0xC.0" size="0x0.13" />
</node>

<node name="mvcap_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit rep\;resents a sensor.\;0: Not connected or not supported\;1: Supports voltage and current measurements" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x8.0" size="0x0.4" />
</node>

<node name="mvcr_ext" descr="" size="0x18.0" >
	<field name="sensor_index" descr="Sensors index to access\;Mapping of system sensors to index is system specific, and detail \;can be found in the system specification. 64-127 of sensor_index \;are mapped to the SFP+/QSFP modules sequentially (module 0 is \;mapped to sensor_index 64, module 1 to sensor_index 65 and so \;on)." access="INDEX" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="voltage_sensor_value" descr="Voltage reading from the sensor. \;Voltage units are 0.01V." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="current_sensor_value" descr="Current reading from the sensor." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="sensor_name" descr="Sensor Name\;8 character long sensor name" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="next_nhlfe" descr="" size="0x1c.0" >
	<field name="label_id" descr="Label id to push to the label stack\;Reserved when label_action is &apos;0&apos;, &apos;1&apos; or &apos;3&apos;" access="RW" offset="0x4.0" size="0x0.20" />
	<field name="label_action" descr="Label action:\;0: no php, no push\;1: reserved \;2: push label. Push a new label with label id label_id \;\;" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="next_nhlfe" descr="NHLFE entry pointer\;Points to the NHLFE table. When using ECMP, points to the\;first entry in the ECMP list." access="RW" offset="0x10.0" size="0x0.24" />
	<field name="ecmp_size" descr="ecmp_size is the amount of sequential entries from the next_nhlfe \;pointer (the number of ECMPs). \;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096." access="RW" offset="0x14.0" size="0x0.13" />
</node>

<node name="next_nhlfe_ext" descr="" size="0x1c.0" >
	<field name="label_id" descr="Label id to push to the label stack\;Reserved when label_action is &apos;0&apos;, &apos;1&apos; or &apos;3&apos;" access="RW" offset="0x4.0" size="0x0.20" />
	<field name="label_action" descr="Label action:\;0: no php, no push\;1: reserved \;2: push label. Push a new label with label id label_id \;\;" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="next_nhlfe" descr="NHLFE entry pointer\;Points to the NHLFE table. When using ECMP, points to the\;first entry in the ECMP list." access="RW" offset="0x10.0" size="0x0.24" />
	<field name="ecmp_size" descr="ecmp_size is the amount of sequential entries from the next_nhlfe \;pointer (the number of ECMPs). \;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096." access="RW" offset="0x14.0" size="0x0.13" />
</node>

<node name="pacl_ext" descr="" size="0x70.0" >
	<field name="acl_type" descr="Type of ACL.\;See Table 1210, &quot;ACL Types,&quot; on page 1334 for the supported ACL \;types.\;Reserved when Spectrum-1\;Supported by Spectrum-2" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="v" descr="Valid. Setting the v bit makes the ACL valid. It should not be \;cleared while the ACL is bounded to either a port, VLAN or ACL \;rule." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="e" descr="Type of ACL group. Only valid on Create ACL Group operation \;and Read.\;0: iACL\;1: eACL\;" access="INDEX" enum="iACL=0x0,eACL=0x1" offset="0x0.31" size="0x0.1" />
	<field name="acl_id" descr="An identifier representing the ACL (managed by software)\;Range 0 .. cap_max_acl_regions - 1\;" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="tcam_region_info" descr="Information that represents the TCAM region to be used for the \;ACL. The region information is obtained by PTAR. \;The number of valid regions is derived from the ACL type. The first \;region will be used for the first packet type in the ACL type list and \;so forth.\;For Spectrum-1 entry [0] is used and entries [1..3] are reserved.\;For tcam_region_info [1..3] the value &apos;0&apos; indicates NULL region \;and can be used to indicate no rules for a specific packet type.\;Note: tcam_region_info[n] is mapped from (acl_id+n).\;See tables: \;Table 1669, &quot;tcam_region_info[0] Layout,&quot; on page 1675\;Table 1671, &quot;tcam_region_info[1] Layout,&quot; on page 1676\;Table 1673, &quot;tcam_region_info[2] Layout,&quot; on page 1676\;Table 1675, &quot;tcam_region_info[3] Layout,&quot; on page 1676\;\;" subnode="array128_auto" access="RW" high_bound="3" low_bound="0" offset="0x30.0" size="0x40.0" />
</node>

<node name="pagt_ext" descr="" size="0x70.0" >
	<field name="size" descr="Number of ACLs in the group.\;0: invalidate the group\;1 or more: add ACLs to the group\;Range 0 .. cap_max_acl_group_size\;Total number of ACLs in all groups must be lower or equal to cap_\;max_acl_tot_groups\;Note: a group which is binded must not be invalidated" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="e" descr="0: iACL\;1: eACL\;Reserved in Spectrum/-2\;" access="INDEX" enum="iACL=0x0,eACL=0x1" offset="0x0.31" size="0x0.1" />
	<field name="acl_group_id" descr="ACL group identifier\;Range of 0 .. cap_max_acl_groups-1" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="acl_id_record" descr="See Table 1679, &quot;ACL ID Record Layout,&quot; on page 1679" access="RW" high_bound="15" low_bound="0" offset="0x30.0" size="0x40.0" />
</node>

<node name="paos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:\;1: up\;2: down\;4: down_by_port_failure - (transitioned by the hardware)\;" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):\;1: up\;2: down_by_configuration\;3: up_once - if the port goes up and then down, the operational \;status should go to &quot;down by port failure&quot; and can only go back \;up upon explicit command\;4: disabled_by_system - this mode cannot be set by the software, \;only by the hardware.\;\;\;\;" access="RW" enum="up=0x1,down_by_configuration=0x2,up_once=0x3,disabled_by_system=0x4" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the router port. \;In this case, the swid indicates which of the router ports to config\;ure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="e" descr="Event generation on operational state change:\;0: Do_not_generate_event\;1: Generate_Event \;2: Generate_Single_Event\;\;Not Supported for HCA." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="fd" descr="Force down.\;Supported only when indicated in PCAM\;Can be set only with admin_status = 2 (&apos;down_by_configura\;tion&apos;), will force link to be down. \;" access="RW" offset="0x4.8" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be \;updated based on the e field. Only relevant on Set operations.\;Not Supported for HCA." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin state will be \;updated based on admin_state field. Only relevant on Set() opera\;tions." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pbmc_reg_ext" descr="" size="0x6c.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="xoff_refresh" descr="The time before a new pause frame should be sent to refresh the pause \;state. Using the same units as xoff_timer_value above." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_timer_value" descr="When device generates a pause frame, it uses this value as the pause \;timer.\;The pause timer is measured in units of pause &quot;quanta&quot;, where each unit \;is equal to 512 bit times." access="RW" offset="0x4.16" size="0x0.16" />
	<field name="port_buffer_size" descr="Total packet buffer array available for the port. The sum of buffer array \;allocated to bufferX must not exceed port_buffer_size.\;In Spectrum and above- Max supported Headroom buffer for port. \;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fullness_threshold" descr="Almost full threshold configuration.\;Percentage of buffer fullness which indicates &quot;almost full&quot; occurrence\;Range: 0-100%\;Reserved for Switches." access="RW" offset="0x8.16" size="0x0.7" />
	<field name="buffer" descr="Configuring per-buffer parameters. i=0..9\;" subnode="bufferx_reg" access="RW" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="port_shared_buffer" descr="Configuring port shared buffer parameters. Using the same layout as in \;BufferX, for details see Table 1060, &quot;bufferX Register Layout,&quot; on \;page 1274.\;Not supported in SwitchX and SwitchX-2\;Valid for HCA when pbmc_port_shared_buffer is set in PCAM." subnode="uint64" access="RW" offset="0x64.0" size="0x8.0" />
</node>

<node name="pbsr_reg_ext" descr="" size="0x64.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="used_shared_headroom_buffer" descr="Number of currently used shared headroom buffer cells." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="clear_wm" descr="Clear watermarks for all PGs" access="OP" offset="0x8.31" size="0x0.1" />
	<field name="stat_buffer" descr="status per-buffer parameters. i=0..9\;" subnode="stat_bufferx_reg" access="RW" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
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
	<field name="rx_errors" descr="Number of transitions to recovery due to Framing \;errors and CRC (dlp and tlp) errors." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="tx_errors" descr="Number of transitions to recovery due to EIEOS \;and TS errors." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="crc_error_dllp" descr="Number of transitions to recovery due to identify\;ing CRC DLLP errors" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="crc_error_tlp" descr="Number of transitions to recovery due to identify\;ing CRC TLP errors" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_overflow_buffer_pkt" descr="The number of packets dropped due to lack of \;PCIe buffers or receive path from NIC port toward \;the hosts." subnode="uint64" access="RO" offset="0x28.0" size="0x8.0" />
	<field name="outbound_stalled_reads" descr="The percentage of time within the last second that \;the NIC had outbound non-posted read requests \;but could not perform the operation due to insuffi\;cient non-posted credits.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="outbound_stalled_writes" descr="The percentage of time within the last second that \;the NIC had outbound posted writes requests but \;could not perform the operation due to insufficient \;posted credits.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="outbound_stalled_reads_events" descr="The number of events where out\;bound_stalled_reads was above a threshold.\;The threshold is configured by out\;bound_stalled_reads_th in MPEGC.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="outbound_stalled_writes_events" descr="The number of events where out\;bound_stalled_writes was above a threshold.\;The threshold is configured by out\;bound_stalled_writes_th in MPEGC.\;Supported only when MCAM.pcie_out\;bound_stalled ==1." access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="tx_overflow_buffer_marked_pkt" descr="The number of packets marked due to lack of PCIe \;buffers or receive path from NIC port toward the \;hosts.\;Supported only if MCAM.mark_tx_action_cqe or \;MCAM.mark_tx_action_cnp are set to &apos;1&apos;." subnode="uint64" access="RO" offset="0x40.0" size="0x8.0" />
</node>

<node name="pcie_timers_states_ext" descr="" size="0xf8.0" >
	<field name="time_to_boot_image_start" descr="Time form start until FW boot image starts running in \;usec. \;Note: can&apos;t be cleared." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_to_link_image" descr="Time form start until FW pci_link image starts running \;in usec." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="calibration_time" descr="Time it took FW to do calibration in usec." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_to_first_perst" descr="Time form start until FW handle first prest" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="time_to_detect_state" descr="Time form start until first transition to LTSSM.Detect_Q" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="time_to_l0" descr="Time form start until first transition to LTSSM.L0" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="time_to_crs_en" descr="Time form start until crs is enabled" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="time_to_plastic_image_start" descr="Time form start until FW plastic image starts running in \;usec." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="time_to_iron_image_start" descr="Time form start until FW iron image starts running in \;usec." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="perst_handler" descr="Number of persts arrived" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="times_in_l1" descr="Number of times LTSSM entered L1 flow" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="times_in_l23" descr="Number of times LTSSM entered L23 flow" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="dl_down" descr="Number of moves for DL_active to DL_down" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="config_cycle1usec" descr="Number of configuration requests that FW handled in \;less then 1 usec" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="config_cycle2to7usec" descr="Number of configuration requests that FW handled \;within 2 to 7 usec" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="config_cycle8to15usec" descr="Number of configuration requests that FW handled \;within 8 to 15 usec" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="config_cycle16to63usec" descr="Number of configuration requests that FW handled \;within 16 to 63 usec" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="config_cycle64usec" descr="Number of configuration requests that FW handled took \;more than 64 usec" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="correctable_err_msg_sent" descr="Number of correctable error msg sent" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="non_fatal_err_msg_sent" descr="Number of Non-Fatal error msg sent" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fatal_err_msg_sent" descr="Number of Fatal error msg sent" access="RO" offset="0x58.0" size="0x4.0" />
</node>

<node name="pcmr_reg_ext" descr="" size="0xc.0" >
	<field name="local_port" descr="Local port number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fcs_cap" descr="Specifies the check enable/disable capabilities of the local port. A \;bit set to 1 for affirmation of supported enable/disable capability: \;FCS check disable/enable capability" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="rx_ts_over_crc_cap" descr="Specifies the ingress timestamps enable/disable capabilities of the local \;port. A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="rx_fcs_drop_cap" descr="Specifies the ingress drop enable/disable capabilities of the local port. A bit \;set to 1 for affirmation of supported enable/disable capability: \;" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="tx_fcs_recalc_cap" descr="Specifies the egress drop enable/disable capabilities of the local port. A bit \;set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="tx_ts_over_crc_cap" descr="Specifies the egress timestamps enable/disable capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RW" offset="0x4.16" size="0x0.1" />
	<field name="entropy_gre_calc_cap" descr="Specifies the egress GRE tunnel protocol entropy calculation enable/disable \;capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="entropy_calc_cap" descr="Specifies the egress tunnel protocol entropy calculation enable/disable \;capabilities of the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="force_entropy_cap" descr="Specifies the egress tunnel protocol entropy calculation force capabilities of \;the local port. \;A bit set to 1 for affirmation of supported enable/disable capability:" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="fcs_chk" descr="FCS check\;Values:\;0: disable check. \;1: perform check\;Note: when disabling a check, it will also affects the relevant counters." access="RW" offset="0x8.1" size="0x0.1" />
	<field name="rx_ts_over_crc" descr="RX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;" access="RW" offset="0x8.13" size="0x0.1" />
	<field name="rx_fcs_drop" descr="RX FCS drop control:\;0: ingress port will drop a packet with bad FCS (Default)\;1: ingress port will not drop a packet with bad FCS\;NOTE: All FCS counters (PPCNT) are valid for both drop modes.\;NOTE: Reserved when PCMR.fcs_cap=1 &amp; PCMR.fcs_chk=0" access="RW" offset="0x8.14" size="0x0.1" />
	<field name="tx_fcs_recalc" descr="TX FCS drop control:\;0: egress port will recalculate and overwrite FCS value (Default) \;1: egress port will not overwrite FCS value \;NOTE: when this bit is set, any modification of the packet will \;result in a bad FCS." access="RW" offset="0x8.15" size="0x0.1" />
	<field name="tx_ts_over_crc" descr="TX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Reserved when tx_fcs_recalc is set" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="entropy_gre_calc" descr="0x0: DISABLE - entropy calculation is disabled for GRE tunneling \;protocol.\;0x1: ENABLE - entropy calculation is enabled for GRE tunneling \;protocol, if entropy_calc is enabled as well. valid only if force_en\;tropy is activated." access="RW" offset="0x8.29" size="0x0.1" />
	<field name="entropy_calc" descr="0x0: DISABLE - entropy calculation is disabled for all supported \;tunneling protocols.\;0x1: ENABLE - entropy calculation is enabled for all supported tun\;neling protocols. GRE also depends on the entropy_gre_calc valid \;only if force_entropy is activated." access="RW" offset="0x8.30" size="0x0.1" />
	<field name="force_entropy" descr="0x0: DEFAULT - use device defaults for tunnel entropy calculation. \;This mode should be used if entropy calculation requirement is \;unknown.\;0x1: FORCE - force the entropy calculation according to entropy_\;calc and entropy_gre_calc." access="RW" offset="0x8.31" size="0x0.1" />
</node>

<node name="pddr_advanced_opcode_ext" descr="" size="0x4.0" >
	<field name="advanced_opcode" descr="Status opcode: \;\;PHY FW indication (0 - 1023):\;0 - No issue observed\;1 - Port is close by command (see PAOS).\;2 - AN no partner detected.\;3 - AN ack not received. \;4 - AN next-page exchange failed. \;5 - KR frame lock not acquired.\;6 - KR link inhibit timeout \;7 - KR Link partner didn&apos;t set receiver ready\;8 - KR tuning didn&apos;t completed \;9 - PCS didn&apos;t acquire block lock. \;10 - PCS didn&apos;t acquire AM lock (NO FEC) \;11 - PCS didn&apos;t get align_status.\;12 - FC FEC isn&apos;t locked\;13 - RS FEC isn&apos;t locked\;14 - Remote fault received\;15 - Bad Signal integrity \;16 - Compliance code mismatch (protocol mismatch between cable and port)\;17 - Large number of physical errors (high BER). \;18 - Port is disabled by Ekey\;19- Phase EO failure\;20- stamping of Non Mellanox Cables/Modules\;21 - Down by PortInfo MAD\;22 - Disabled by Verification\;23 - Calibration failure\;24 - EDR speed is not allowed due to cable stamping: EDR stamping\;25 - FDR10 speed is not allowed due to cable stamping: FDR10 stamping\;26 - Port is closed due to cable stamping: Ethernet_compliace_code_zero\;27 - Port is closed due to cable stamping: 56GE stamping\;28 - Port is closed due to cable stamping: non-Mellanox QSFP28\;29 - Port is closed due to cable stamping: non-Mellanox SFP28\;30 - Port is closed, no backplane enabled speed over backplane channel\;31 - Port is closed, no passive protocol enabled over passive copper channel\;32 - Port is closed, no active protocol enabled over active channel\;33 - Port width is doesn&apos;t match the port speed enabled\;34 - Local speed degradation\;35 - Remote speed degradation\;36 - No Partner detected during force mode. \;37 - Partial link indication during force mode. \;38 - AN Failure - FEC mismatch during override \;39 - AN Failure - No HCD\;40 - VPI protocol don&apos;t match\;41 - Port is closed, module can&apos;t be set to the enabled rate\;42 - Bad SI, cable is configured to non optimal rate \;43 - No Partner detected during force mode, while port is running fast link-up\;44 - Partial link indication during force mode, while port is running fast link-up\;45 - Main USR logic didn&apos;t get align_status.\;46 - Tile USR logic didn&apos;t get align_status;\;128 - Troubleshooting in process\;1023- Info not available\;\;\;MNG FW issues (1024 - 2047):\;1024 - Cable is unplugged/powered off\;1025 - Long Range for non MLNX cable/module .\;1026 - Bus stuck (I2C Data or clock shorted) \;1027 - bad/unsupported EEPROM \;1028 - part number list\;1029 - unsupported cable.\;1030 - module temperature shutdown\;1031 - Shorted cable\;1032 - Power Budget Exceeded\;1033 - Management force down the port\;1034 - Module is disabled by command\;1035 - System Power is Exceeded therefore the module is powered off. \;1036 - Module&apos;s PMD type is not enabled (see PMTPS).\;1043 - NDR speed is not allowed due to cable stamping: NDR stamping\;1044 - HDR speed is not allowed due to cable stamping: HDR stamping\;1045 - EDR speed is not allowed due to cable stamping: EDR stamping\;1046 - FDR10 speed is not allowed due to cable stamping: FDR10 stamping\;\;Core/Driver (2048 - 3072):\;" access="RW" offset="0x0.0" size="0x0.16" />
</node>

<node name="pddr_c2p_link_enabed_eth_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_c2p_link_enabed_ib_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_proto_enabled" descr="ib link enabled speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80" offset="0x0.0" size="0x0.16" />
	<field name="core_to_phy_link_width_enabled" descr="ib link enabled width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;Bit 3: 8x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_cable_cap_eth_ext" descr="" size="0x4.0" >
	<field name="cable_ext_eth_proto_cap" descr="Cable Ethernet protocols cap. \;For opcode definition see: PTYS.ext_eth_proto_cap" access="RO" offset="0x0.0" size="0x4.0" />
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
	<field name="clr_mask" descr="Valid only when PDDR.clr is set\;Bit mask for page bits 255:0, when bits 31:0 assigned to offset 00h \;bits 31:0.\;bits 63:32 assigned to offset 04h bits 31:0.\;bits 95:64 assigned to offset 08h bits 31:0.\;bits 127:69 assigned to offset 0Ch bits 31:0.\;Only when PDDR.clr is set and the appropriate bit in the mask is \;set, the event will be cleared" access="OP" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
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
</node>

<node name="pddr_link_up_info_page_ext" descr="" size="0xf8.0" >
	<field name="up_reason_mng" descr="invalid port access severity\;0 - No down command / unknown\;1 - BMC force linkup\;2 - WOL force linkup\;\;3 - ASN.1 force link up" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="up_reason_drv" descr="invalid port access severity\;0 - No down command / unknown\;1 - Up by at least one of the hosts" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="up_reason_pwr" descr="invalid port access severity\;0 - No down command / unknown\;1 - Keep link up on boot \;2 - Keep link up Eth/IB\;3 - Keep link up on standby" access="RO" offset="0x0.16" size="0x0.4" />
	<field name="time_to_link_up" descr="Time in msec." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fast_link_up_status" descr="Indicates if fast link-up was performed in the link: \;0: Unknown\;1: Fast Link-UP was performed. \;2: Regular link-up flow performed due to changes in cable\;3: Regular link-up flow performed due to changes in speed\;4: Regular link-up performed due to changes in temperature\;5: Regular link-up performed due to MLPN flow\;6: Regular link-up performed due to PCNR.tuning_override config\;uration while port was in &quot;down&quot; state.\;7: Regular link-up performed due to changes in TX rev of remote \;side\;8: Fast Link-up was performed, but the total link-up time is \;expected to be long due to changes in TX rev of local side (i.e. \;remote doesn&quot;t activate fast link-up flow)" access="RO" offset="0x8.0" size="0x0.4" />
</node>

<node name="pddr_module_info_ext" descr="" size="0xf8.0" >
	<field name="ethernet_compliance_code" descr="QSFP:\;Ethernet Compliance Codes bit mask (10/40G/100G)\;Byte131 per SFF-8636 \;Bit 7 - Extended Specification Compliance valid\;Bit 6 - 10GBASE-LRM\;Bit 5 - 10GBASE-LR\;Bit 4 - 10GBASE-SR\;Bit 3 - 40GBASE-CR4\;Bit 2 - 40GBASE-SR4\;Bit 1 - 40GBASE-LR4\;Bit 0 - 40G Active Cable (XLPPI)\;\;SFP : \;10G Ethernet Compliance Codes\;Byte3 per SFF-8472:\;Bit 7 - 10G Base-ER \;Bit 6 - 10G Base-LRM \;Bit 5 - 10G Base-LR \;Bit 4 - 10G Base-SR\;\;CMIS based (QSFP-DD/ SFP-DD / OSFP)\;Byte 87 - Module Media Interface" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes \;for SFP:\;byte 36 per SFF-8472\;\;for QSFP:\;byte192 per SFF-8636 (QSFP28) \;\;for CMIS (SFP-DD / QSFP-DD/ OSFP) :\;Byte 86 - Host Electrical Interface" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="cable_breakout" descr="Reserved for SFP. \;\;For QSFP:\;Byte113 per SFF-8636\;\;For CMIS based modules:\;1 - QSFP-DD to QSFP-DD\;2 - QSFP-DD to 2xQSFP or 2xQSFP-DD (depopulated / 4 lanes)\;3 - QSFP-DD to 4xSFP-DD or 4xQSFP (depopulated / 2 lanes)\;4 - QSFP-DD to 8xSFP\;5 - QSFP-DD (depopulated / 4 lanes) or QSFP to QSFP or QSFP-\;DD (depopulated / 4 lanes)\;6 - QSFP-DD (depopulated / 4 lanes) or QSFP to 2xQSFP(depopu\;lated / 2 lanes) or 2xSFP-DD\;7 - QSFP-DD (depopulated / 4 lanes) to 4xSFP\;8 - SFP-DD to SFP-DD\;9 - SFP-DD to 2xSFP\;\;Note: QSFP-DD can refer to OSFP form factor according to identi\;fier" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="cable_technology" descr="QSFP: \;Byte 147 per SFF-8636.\;\;SFP:\;SFP+ Cable Technology: \;byte8 per SFF-8472:\;Bit 3 - Active Cable\;Bit 2 - Passive Cable\;\;CMIS based (QSFP-DD / OSFP/ SFP-DD):\;Byte 212" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="cable_power_class" descr="Module maximum power consumption for SFP/QSFP:\;0 - Power Class 0 (1.0 W max)\;1 - Power Class 1 (1.5 W max)\;2 - Power Class 2 (2.0 W max)\;3 - Power Class 3 (2.5 W max)\;4 - Power Class 4 (3.5 W max)\;5 - Power Class 5 (4.0 W max)\;6 - Power Class 6 (4.5 W max)\;7 - Power Class 7 (5.0 W max)\;\;Module maximum power consumption for SFP-DD:\;0 - Power Class 0 (0.5 W max)\;1 - Power Class 1 (1.0 W max)\;2 - Power Class 2 (1.5 W max)\;3 - Power Class 3 (2.0 W max)\;4 - Power Class 4 (3.5 W max)\;5 - Power Class 5 (5.0 W max)\;6 - reserved\;7 - reserved\;8 - Power Class 8 (&gt; 5.0 W max)\;Module maximum power consumption for QSFP-DD/OSFP:\;1 - Power Class 1 (1.5 W max)\;2 - Power Class 2 (3.5 W max)\;3 - Power Class 3 (7.0 W max)\;4 - Power Class 4 (8.0 W max)\;5 - Power Class 5 (10 W max)\;6 - Power Class 6 (12 W max)\;7 - Power Class 7 (14 W max)\;8 - Power Class 8 (&gt; 14 W max)\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="cable_identifier" descr="0 - QSFP28\;1 - QSFP+\;2 - SFP28/SFP+\;3 - QSA (QSFP-&gt;SFP)\;4 - Backplane\;5 - SFP-DD\;6 - QSFP-DD\;7 - QSFP_CMIS\;8 - OSFP\;9 - C2C" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="cable_length" descr="Cable length in 1m units.\;\;For CMIS modules:\;bits 6:7 represent cable_length_multiplier for calculating cable \;length\;00 - 0.1 multiplier (1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (1 to 630m)\;11 - 100 multiplier (1 to 6300m)\;\;bits 0:5 represent cable_length_value for calculating cable length.\;\;length is calculated with cable_length_value * cable_length_multi\;plier" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="cable_vendor" descr="Cable vendor:\;0 - Other \;1 - Mellanox\;2 - Known OUI\;" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="cable_type" descr="Cable/module type:\;0 - Unidentified\;1 - Active cable (active copper / optics)\;2 - Optical Module (separated).\;2 - Passive copper cable\;3 - Cable unplugged\;\;In CMIS based Modules per byte 85." access="RO" offset="0x4.28" size="0x0.4" />
	<field name="cable_tx_equalization" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="cable_rx_emphasis" descr="\;\;\;for CMIS (QSFP-DD/ SFP-DD/ OSFP) field will represent Rx pre-\;emphasis.\;" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="cable_rx_amp" descr="Reserved for SFP\;" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="max_power" descr="Byte 201 for CMIS (QSFP-DD/ SFP-DD/ OSFP)\;Other Cable ignore field." access="RO" offset="0x8.24" size="0x0.8" />
	<field name="cable_attenuation_5g" descr="Reserved for SFP" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="cable_attenuation_7g" descr="Reserved for SFP" access="RO" offset="0xC.8" size="0x0.8" />
	<field name="cable_attenuation_12g" descr="Reserved for SFP" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="cable_attenuation_25g" descr="Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)\;Other Cable ignore field." access="RO" offset="0xC.24" size="0x0.8" />
	<field name="tx_cdr_state" descr="Reserved for SFP\;\;Bit 0 - TX CDR on/off on channel 0 \;Bit 1 - TX CDR on/off on channel 1 \;Bit 2 - TX CDR on/off on channel 2 \;Bit 3 - TX CDR on/off on channel 3 \;Bit 4 - TX CDR on/off on channel 4 \;Bit 5 - TX CDR on/off on channel 5 \;Bit 6 - TX CDR on/off on channel 6 \;Bit 7 - TX CDR on/off on channel 7 \;\;CDR on - when bit is set.\;CDR off - when bit is clear.\;" access="RO" offset="0x10.0" size="0x0.8" />
	<field name="rx_cdr_state" descr="Reserved for SFP\;\;Bit 0 - RX CDR on/off on channel 0 \;Bit 1 - RX CDR on/off on channel 1 \;Bit 2 - RX CDR on/off on channel 2 \;Bit 3 - RX CDR on/off on channel 3\;Bit 4 - RX CDR on/off on channel 4 \;Bit 5 - RX CDR on/off on channel 5 \;Bit 6 - RX CDR on/off on channel 6 \;Bit 7 - RX CDR on/off on channel 7 \;\;CDR on - when bit is set.\;CDR off - when bit is clear.\;" access="RO" offset="0x10.8" size="0x0.8" />
	<field name="tx_cdr_cap" descr="0 - No CDR\;1 - Build-in CDR with on/off control \;2 - Build-in CDR without on/off control" access="RO" offset="0x10.16" size="0x0.4" />
	<field name="rx_cdr_cap" descr="0 - No CDR\;1 - Build-in CDR with on/off control \;2 - Build-in CDR without on/off control" access="RO" offset="0x10.20" size="0x0.4" />
	<field name="cable_rx_post_emphasis" descr="Valid only for CMIS (QSFP-DD/ SFP-DD/ OSFP)\;Rx post-emphasis." access="RO" offset="0x10.24" size="0x0.8" />
	<field name="vendor_name" descr="" access="RO" high_bound="3" low_bound="0" offset="0x14.0" size="0x10.0" />
	<field name="vendor_pn" descr="Vendor Part Number" access="RO" high_bound="3" low_bound="0" offset="0x24.0" size="0x10.0" />
	<field name="vendor_rev" descr="" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fw_version" descr="If information is not available by the module: set to 0" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="vendor_sn" descr="Vendor Serial Number" access="RO" high_bound="3" low_bound="0" offset="0x3C.0" size="0x10.0" />
	<field name="voltage" descr="Internally measured supply voltage in 100uV" access="RO" offset="0x4C.00" size="0x0.16" />
	<field name="temperature" descr="module temperature in 1/256 C" access="RO" offset="0x4C.16" size="0x0.16" />
	<field name="rx_power_lane1" descr="RX measured power channel 1 in dBm" access="RO" offset="0x50.0" size="0x0.16" />
	<field name="rx_power_lane0" descr="RX measured power channel 0 in dBm" access="RO" offset="0x50.16" size="0x0.16" />
	<field name="rx_power_lane3" descr="RX measured power channel 3 in dBm" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="rx_power_lane2" descr="RX measured power channel 2 in dBm" access="RO" offset="0x54.16" size="0x0.16" />
	<field name="rx_power_lane5" descr="RX measured power channel 5 in dBm" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="rx_power_lane4" descr="RX measured power channel 4 in dBm" access="RO" offset="0x58.16" size="0x0.16" />
	<field name="rx_power_lane7" descr="RX measured power channel 7 in dBm" access="RO" offset="0x5C.0" size="0x0.16" />
	<field name="rx_power_lane6" descr="RX measured power channel 6 in dBm" access="RO" offset="0x5C.16" size="0x0.16" />
	<field name="tx_power_lane1" descr="TX measured power channel 1 in dBm" access="RO" offset="0x60.0" size="0x0.16" />
	<field name="tx_power_lane0" descr="TX measured power channel 0 in dBm" access="RO" offset="0x60.16" size="0x0.16" />
	<field name="tx_power_lane3" descr="TX measured power channel 3 in dBm" access="RO" offset="0x64.0" size="0x0.16" />
	<field name="tx_power_lane2" descr="TX measured power channel 2 in dBm" access="RO" offset="0x64.16" size="0x0.16" />
	<field name="tx_power_lane5" descr="TX measured power channel 5 in dBm" access="RO" offset="0x68.0" size="0x0.16" />
	<field name="tx_power_lane4" descr="TX measured power channel 4 in dBm" access="RO" offset="0x68.16" size="0x0.16" />
	<field name="tx_power_lane7" descr="TX measured power channel 7 in dBm" access="RO" offset="0x6C.0" size="0x0.16" />
	<field name="tx_power_lane6" descr="TX measured power channel 6 in dBm" access="RO" offset="0x6C.16" size="0x0.16" />
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
	<field name="module_st" descr="Valid for CMIS modules only.\;Module state:\;0 - reserved\;1 - LowPwr state\;2 - PwrUp state\;3 - Ready state\;4 - PwrDn state\;5 - Fault state" access="RO" offset="0x94.29" size="0x0.3" />
	<field name="active_set_media_compliance_code" descr="Valid for CMIS modules only.\;According to current Active set, value of Module Media Interface \;byte" access="RW" offset="0x98.16" size="0x0.8" />
	<field name="active_set_host_compliance_code" descr="Valid for CMIS modules only.\;According to current Active set, value of Host Electrical Interface \;byte" access="RW" offset="0x98.24" size="0x0.8" />
	<field name="dp_st_lane7" descr="DataPath state for lane7" access="RO" offset="0xA0.0" size="0x0.4" />
	<field name="dp_st_lane6" descr="DataPath state for lane6" access="RO" offset="0xA0.4" size="0x0.4" />
	<field name="dp_st_lane5" descr="DataPath state for lane5" access="RO" offset="0xA0.8" size="0x0.4" />
	<field name="dp_st_lane4" descr="DataPath state for lane4" access="RO" offset="0xA0.12" size="0x0.4" />
	<field name="dp_st_lane3" descr="DataPath state for lane3" access="RO" offset="0xA0.16" size="0x0.4" />
	<field name="dp_st_lane2" descr="DataPath state for lane2" access="RO" offset="0xA0.20" size="0x0.4" />
	<field name="dp_st_lane1" descr="DataPath state for lane1" access="RO" offset="0xA0.24" size="0x0.4" />
	<field name="dp_st_lane0" descr="DataPath state for lane0" access="RO" offset="0xA0.28" size="0x0.4" />
</node>

<node name="pddr_monitor_opcode_ext" descr="" size="0x4.0" >
	<field name="monitor_opcode" descr="Status opcode: \;\;PHY FW indication (0 - 1023):\;0 - No issue observed\;1 - Port is close by command (see PAOS).\;2,3,4,38,39 - AN failure \;5,6,7,8 - Link training failure. \;9,10,11,12,13 - Logical mismatch between link partners\;14 - Remote fault received\;15,42,17 - Bad signal integrity \;16,24-32 - Cable compliance code mismatch (protocol mismatch \;between cable and port) \;23,22,19,18- Internal error\;34,35 - Speed degradation\;128 - Troubleshooting in process\;1023- Info not available\;\;MNG FW issues (1024 - 2047):\;1024 - Cable is unplugged\;1025 - Long Range for non Mellanox cable/module .\;1026 - Bus stuck (I2C Data or clock shorted) \;1027 - Bad/unsupported EEPROM \;1028 - Part number list\;1029 - Unsupported cable.\;1030 - Module temperature shutdown\;1031 - Shorted cable\;1032 - Power budget exceeded\;1033 - Management forced down the port\;1034 - Module is disabled by command\;1036 - Module&apos;s PMD type is not enabled (see PMTPS).\;\;\;\;1040 - pcie system power slot Exceeded\;\;\;1043,1044,1045,1046 - Module&apos;s stamping speed degeneration\;\;\;Core/Driver (2048 - 3071):\;\;" access="RW" offset="0x0.0" size="0x0.16" />
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
	<field name="ib_phy_fsm_state" descr="FW IB state machine:\;0x0 - IB_AN_FSM_DISABLED\;0x1 - IB_AN_FSM_INITIALY\;0x2 - IB_AN_FSM_RCVR_CFG\;0x3 - IB_AN_FSM_CFG_TEST\;0x4 - IB_AN_FSM_WAIT_RMT_TEST\;0x5 - IB_AN_FSM_WAIT_CFG_ENHANCED\;0x6 - IB_AN_FSM_CFG_IDLE\;0x7 - IB_AN_FSM_LINK_UP\;\;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="eth_an_fsm_state" descr="Ethernet (CL73) Auto-negotiation FSM state:\;0x0 - ETH_AN_FSM_ENABLE\;0x1 - ETH_AN_FSM_XMIT_DISABLE\;0x2 - ETH_AN_FSM_ABILITY_DETECT\;0x3 - ETH_AN_FSM_ACK_DETECT\;0x4 - ETH_AN_FSM_COMPLETE_ACK\;0x5 - ETH_AN_FSM_AN_GOOD_CHECK\;0x6 - ETH_AN_FSM_AN_GOOD\;0x7 - ETH_AN_FSM_NEXT_PAGE_WAIT\;[Internal] 0x8 - ETH_AN_FSM_LINK_STAT_CHECK\;[Internal] 0x9 - ETH_AN_FSM_EXTRA_TUNE\;[Internal] 0xa - ETH_AN_FSM_FIX_REVERSALS\;[Internal] 0xb - ETH_AN_FSM_IB_FAIL\;\;" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="phy_mngr_fsm_state" descr="FW Phy Manager FSM state:\;0 - Disabled \;1 - Open port\;2 - Polling\;3 - Active / Linkup\;4 - Close port" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="phy_manager_link_enabled" descr="For IB: See Table  1185, &quot;PDDR - Phy manager link enabled IB layout,&quot; \;on page  1386\;For Ethernet: See Table  1187, &quot;PDDR - Phy manager link enabled Eth \;layout,&quot; on page  1386\;" subnode="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="core_to_phy_link_enabled" descr="For IB: See Table  1189, &quot;PDDR - core2phy link enabled IB layout,&quot; on \;page  1387\;For Ethernet: See Table  1191, &quot;PDDR - Core2Phy link enabled Eth lay\;out,&quot; on page  1387" subnode="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="cable_proto_cap" descr="For IB: See Table  1193, &quot;PDDR - cable cap IB layout,&quot; on page  1388\;For Ethernet: See Table  1195, &quot;PDDR - cable cap Eth layout,&quot; on \;page  1388\;" subnode="pddr_operation_info_page_cable_proto_cap_auto_ext" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="link_active" descr="For IB: See Table  1197, &quot;PDDR - Link Active IB layout,&quot; on page  1389\;For Ethernet: See Table  1199, &quot;PDDR - Link Active Eth layout,&quot; on \;page  1389" subnode="pddr_operation_info_page_link_active_auto_ext" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="loopback_mode" descr="0 - Phy remote loopback \;2 - Phy local loopback. When set the port&apos;s egress traffic is looped back to \;the receiver and the port transmitter is disabled. \;4 - External local loopback. Enables the port&apos;s transmitter to link with the \;port&apos;s receiver using an external loopback connector. Bits 3-7 are reserved." access="RO" offset="0x18.0" size="0x0.4" />
	<field name="fec_mode_request" descr="FEC mode request\;See fec_mode_active\;for supported retransmission mode see PPLM.fec_mode_capability" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="fec_mode_active" descr="FEC mode active\;0 - No FEC\;1 - Firecode FEC\;2 - Standard RS-FEC - RS(528,514)\;3 - Standard LL RS-FEC - RS(271,257)\;[Internal] 4 - Mellanox Strong RS-FEC - RS(277,257)\;[Internal] 5 - Mellanox LL RS-FEC - RS(163,155)\;[Internal] 6 - Reserved\;Bit 7 - Standard RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;\;for supported retransmission mode see PPLM.fec_mode_capability" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="eth_100g_fec_support" descr="FEC 100G (25Gb/s per lane) supported FEC include override \;masking , should reflect current phy configuration\;Bit 0 - No FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="eth_25g_50g_fec_support" descr="FEC 25G/50G (25Gb/s per lane) supported FEC include override \;masking , should reflect current phy configuration\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.4" size="0x0.4" />
</node>

<node name="pddr_operation_info_page_link_active_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_link_active_ib_ext" descr="" subnode="pddr_link_active_ib_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_link_active_eth_ext" descr="" subnode="pddr_link_active_eth_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_phy_manager_link_enabed_ib_ext" descr="" subnode="pddr_phy_manager_link_enabed_ib_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabed_eth_ext" descr="" subnode="pddr_phy_manager_link_enabed_eth_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_info_page_ext" descr="" size="0xf8.0" >
	<field name="port_notifications" descr="Port notifications bit mask\;Bit 0 - Link partner advertised capabilities \;Bit 1 - Speed degradation" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="remote_device_type" descr="Remote device type: \;0 - Unknown (3rd party , Force , legacy MLPN)  \;1 - CX4\;2 - CX4_LX\;3 - CX5\;4 - CX5_LX\;5 - CX6\;6 - CX6_LX\;7-99 Reserved\;100 - SwitchIB\;101 - Spectrum \;102 - SwitchIB-2\;103 - SwitchIB-3\;104 - Spectrum-2\;105-255 Reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="lp_ib_revision" descr="Link partner IB TS revision \;\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ib_revision" descr="IB TS revision \;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="num_of_negotiation_attempts" descr="Negotiation attempt counter" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="phy_manger_disable_mask" descr="Phy manager disable bit mask: \;Bit 0 - Module not present (module absence/cage power off)\;Bit 1 - PAOS command\;Bit 2 - MAD IB PortInfo down command\;Bit 3 - Long range cable (Non Mellanox) \;Bit 4 - Verification command\;Bit 5 - ekey command\;Bit 6 - High power - cable require higher power than allowed.\;Bit 7 - Unknown Identifier (Module)\;Bit 8 - PAOS up once \;Bit 9 - Stamping failure\;Bit 10 - Calibration not done\;[Internal] Bit 11 - Module Locking\;[Internal] Bit 13 - Power budget exceeded\;[Internal] Bit 14 - Interrupt Event / Module Temp\;[Internal] Bit 15 - TEC flow / module bring up issue" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="hw_link_phy_state" descr="IBP HW FSM Reflected State:\;0x10 - sleeping delay\;0x11 - sleeping quiet\;0x20 - polling active\;0x21 - polling quiet\;0x30 - disable\;0x40 - config debounce\;0x41 - config receiver\;0x42 - config wait remote\;0x43 - config tx reverse lanes\;0x44 - config enhanced    \;0x45 - config test\;0x46 - confg wait remote test\;0x47 - config wait cfg enhanced\;0x48 - config idle\;0x50 - linkup\;0x60 - recover retrain\;0x61 - recover wait remote\;0x62 - recover idle\;0x70 - test\;\;Force Modes:\;0x80 - Force     send ts1 (command may be given only on disable \;state)\;0x90 - Force send ts2\;0xA0 - Force Sent Idle\;0xB0 -  Force send ts Mlnx\;0xC0 - Force send ts3\;0xD0 - Force LinkUp" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="pcs_phy_state" descr="PCS HW state:\;Bits 0-3: Block lock\;Bits 4-7: Reserved \;Bits 8-11: AM lock\;Bits 12-15: Reserved\;Bits 16-19: FEC lock\;Bits 20-23: Reserved\;Bits 24: Align_status\;Bits 25: Hi_BER" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="lp_proto_enabled" descr="IB ports : \;Link partner advertised speeds (first TS3)\;See ib_link_speed_enabled encoding.\;\;Ethernet ports:\;Link partner advertised Ethernet protocols active state: see \;PTYS.lp_advertise" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="lp_fec_mode_request" descr="Reserved when negotiation wasn&apos;t performed according to \;port_notifications.Link partner advertised capabilities value.\;Advertised link partner FEC mode request" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="lp_fec_mode_support" descr="Reserved when negotiation wasn&apos;t performed according to \;port_notifications.Link partner advertised capabilities value.\;\;Advertised link partner FEC mode support\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;Bit 3 - Standard LL RS-FEC - RS(271,257)\;Bit 4 - Mellanox Strong RS-FEC - RS(277,257)\;Bit 5 - Mellanox LL RS-FEC - RS(163,155)\;Bit 6 - Reserved\;Bit 7 - Standard RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;\;for supported retransmission mode see PPLM.fec_mode_capability" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ib_last_link_down_reason" descr="Bit 0 - heartbeat_ack_received\;Bit 1 - heartbeat_send_received\;Bit 2 - heartbeat_err\;Bit 3 - tx_width_reduction_done_1x\;Bit 4 - tx_width_reduction_done_full\;Bit 5 - rx_width_reduction_done_1x\;Bit 6 - rx_width_reduction_done_full\;Bit 7 - width_reduction_timeout\;Bit 8 - ibl_link_retrain\;Bit 9 - rx_comskp_timeout\;Bit 10 - fifo_full_err\;Bit 11 - ts_at_linkup\;Bit 12 - minor_threshold_reached\;Bit 13 - link_fail\;Bit 14 - rx_eb_full_r\;Bit 15 - rx_8_10_lane_err\;Bit 16 - llr_link_retrain_set\;Bit 17 - fc_timeout\;Bit 18 - phy_error\;Bit 19 - lli_err\;Bit 20 - excessive_buffer_err\;Bit 21 - remote_init\;Bits 31-22 - Reserved" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="eth_last_link_down_lane" descr="Bit 0 - block_lock_failed\;Bit 1 - skip_detected\;Bit 2 - fec_sync_failed\;Bit 3 - fec_block_sync\;Bit 4 - fec_block_sync_lost" access="RO" high_bound="3" low_bound="0" offset="0x1C.24" size="0x4.0" />
	<field name="speed_deg_db" descr="Bit 0 - Speed degradation database Valid\;Bit 1 - Speed degradation Serdes Rx database valid\;BIts 3-2 - reserved\;Bit 4 - rx_reversal\;Bit 5 - tx_reversal\;Bit 7-6 - reserved\;Bits 11:8 - failed_qdr/fdr10 - bit per lane.\;Bits 15:12 - failed_fdr - bit per lane.\;Bits 19:16- failed_edr - bit per lane.\;Bits 24:20 - peer_failed_test\;Bits 26-25 - reserved\;Bit 27 - first_test_speed" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="degrade_grade_lane0" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x28.0" size="0x0.24" />
	<field name="degrade_grade_lane1" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x2C.0" size="0x0.24" />
	<field name="degrade_grade_lane2" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x30.0" size="0x0.24" />
	<field name="degrade_grade_lane3" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x34.0" size="0x0.24" />
	<field name="kr_startup_fsm_lane" descr="Per lane KR startup state:\;0 - KR_FSM_INITIALIZE\;1 - KR_FSM_SEND_TRAINING\;2 - KR_FSM_TRAIN_LOCAL_TX\;3 - KR_FSM_TRAIN_LOCAL_RX\;4 - KR_FSM_TRAIN_REMOTE\;5 - KR_FSM_LINK_READY\;6 - KR_FSM_SEND_DATA" access="RO" high_bound="3" low_bound="0" offset="0x48.24" size="0x4.0" />
	<field name="eth_an_debug_indication" descr="eth_an_debug bit mask:\;Bit 0 - Force link up\;Bit 1 - No HCD\;Bit 2 - Entered ACK_detect\;Bit 3 - Entered Good\;Bit 4 - Entered Good_Check\;Bit 5 - Entered Extra_tune\;Bit 6 - Entered Fix_Reversals\;Bit 7 - Entered Next_Page\;Bit 8 - Entered Sub-FSM Fail\;Bit 9 - Tuning timeout\;Bit 10 - No markers detected (during Good check)\;Bit 11 - Do KR-startup\;Bits 15:18 - KR startup failure mask" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ib_phy_fsm_state_trace" descr="FW IB state machine:\;Bit 0 - entered IB_AN_FSM_DISABLED\;Bit 1 - entered IB_AN_FSM_INITIALY\;Bit 2 - entered IB_AN_FSM_RCVR_CFG\;Bit 3 - entered IB_AN_FSM_CFG_TEST\;Bit 4 - entered IB_AN_FSM_WAIT_RMT_TEST\;Bit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCED\;Bit 6 - entered IB_AN_FSM_CFG_IDLE\;Bit 7 - entered IB_AN_FSM_LINK_UP\;Bit 8 - Failed from CFG_IDLE\;" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="kr_startup_debug_indications" descr="kr_stratup_debug_indication_&lt;i&gt; bit mask:\;Bit 0 - PRBS lock failed\;Bit 1 - Entered send training\;Bit 2 - Entered train local RX\;Bit 3 - Entered train remote \;Bit 4 - Entered link ready\;Bit 5 - Entered Send_Data\;Bit 6 - Didn&apos;t get receiver ready \;Bit 7 - tuning timeout\;Bit 8 - No frame lock\;Bit 9 - No response from peer\;Bit 10 - frames lock tuning not done" access="RO" high_bound="3" low_bound="0" offset="0x58.16" size="0x8.0" />
	<field name="irisc_status" descr="" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="stamping_reason" descr="Bit 0 - com_codes_is_zero \;Bit 1- rx_cdr_check_force_mode \;Bit 2- com_code_complaince \;Bit 3- eth_56g_stamped\;Bit 4- non_mlx_qsfp_tranciver\;Bit 5- &quot;non_mlx_sfp_tranciver&quot;\;Bit 6-ib_comp_codes\;Bit 7-edr_comp\;Bit 8-fdr_comp" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="kr_frame_lock_tuning_failure_events_count" descr="Number of times that fast tuning (50ms) for KR lock failed to \;achieve frame lock." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="kr_full_tuning_failure_count" descr="Number of times that full tuning (0.5sec/3sec) for KR full tuning \;flow failed to achieve desire SI performance" access="RO" offset="0x74.0" size="0x4.0" />
</node>

<node name="pddr_phy_manager_link_enabed_eth_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
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
	<field name="clr_mask" descr="Valid only when PDDR.clr is set\;Bit mask for page bits 255:0, when bits 31:0 assigned to offset 00h \;bits 31:0.\;bits 63:32 assigned to offset 04h bits 31:0.\;bits 95:64 assigned to offset 08h bits 31:0.\;bits 127:69 assigned to offset 0Ch bits 31:0.\;Only when PDDR.clr is set and the appropriate bit in the mask is \;set, the event will be cleared. \;For example: To clear the kr_false_ready need set PDDR.clr , \;select the &quot;port event page&quot; and set bit 48 in clr_mask." access="OP" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
</node>

<node name="pddr_reg_ext" descr="" size="0x100.0" >
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0: Local_port_number\;1: IB_or_label_port_number\;" access="INDEX" enum="Local_port_number=0x0,IB_or_label_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:\;0: Operational_info_page\;1: Troubleshooting_info_page\;2: Phy_info_page - [Internal]\;3: Module_info_page\;4: port_events_page - [internal]\;5: device_events_page - [internal]\;6: link_down_info - [EMC only]\;7: link_down_events - [internal]\;8: Link_up_info - [Internal]" access="INDEX" enum="Operational_info_page=0x0,Troubleshooting_info_page=0x1,Phy_info_page=0x2,Module_info_page=0x3,port_events_page=0x4,device_events_page=0x5,link_down_info=0x6,link_down_events=0x7,Link_up_info=0x8" offset="0x4.0" size="0x0.8" />
	<field name="module_info_ext" descr="Module info extended configurations.\;resolution for rx_power and tx_power in module info page\;0 - dbm\;1 - 0.1 dbm\;2 - mW" access="RW" offset="0x4.29" size="0x0.2" />
	<field name="page_data" descr="See Table  1183, &quot;Operation Info Page Layout,&quot; on page  1382\;See Table  1209, &quot;Troubleshooting info Page layout,&quot; on page  1409\;See Table  1201, &quot;Phy info page layout,&quot; on page  1389\;See Table  1207, &quot;Module Info Page Layout,&quot; on page  1399\;See Table  1215, &quot;Port events Page Layout,&quot; on page  1415\;See Table  1217, &quot;Device events Page Layout,&quot; on page  1418\;See Table  1203, &quot;Link down info page layout,&quot; on page  1396\;See Table  1205, &quot;Link down events page layout,&quot; on page  1398\;See Table  1219, &quot;Link Up Info Page Layout,&quot; on page  1421" subnode="pddr_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
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
</node>

<node name="pddr_troubleshooting_page_ext" descr="" size="0xf8.0" >
	<field name="group_opcode" descr="0 - Monitor opcodes\;[Internal] 1 - Advanced debug opcodes" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="status_opcode" descr="Status opcode described in:\;See Table  1211, &quot;PDDR - Monitor opcodes layout,&quot; on page  1411\;[Internal] See Table  1213, &quot;PDDR - Advanced opcodes layout,&quot; on \;page  1413\;" subnode="pddr_troubleshooting_page_status_opcode_auto_ext" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="status_message" descr="ASCII code message\;All Messages are terminated by a Null character &apos;\0&apos;\;\;" access="RO" high_bound="58" low_bound="0" offset="0xC.0" size="0xec.0" />
</node>

<node name="pddr_troubleshooting_page_status_opcode_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_monitor_opcode_ext" descr="" subnode="pddr_monitor_opcode_ext" offset="0x0.0" size="0x4.0" />
	<field name="pddr_advanced_opcode_ext" descr="" subnode="pddr_advanced_opcode_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="peabfe_ext" descr="" size="0x410.0" >
	<field name="size" descr="Number of BF entries to be updated\;Range is 1..256" access="OP" offset="0x0.0" size="0x0.9" />
	<field name="bf_entry" descr="Bloom Filter entry\;See Table 1759, &quot;PEABFE - Bloom Filter Entry Layout,&quot; on \;page 1733\;" subnode="beabfe_bloom_filter" access="RW" high_bound="255" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="peapbl_ext" descr="" size="0x20.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1\;Note: the register updates all duplicated regions" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="erp_id" descr="erp id" access="INDEX" offset="0x10.0" size="0x0.4" />
	<field name="num_rec" descr="Number of records to be updated\;Range is 1..36" access="WO" offset="0x10.16" size="0x0.8" />
	<field name="pruning_ctcam_cs" descr="Pruning C-TCAM clear or set. Clear or set defined by c_s\;0: don&apos;t modify prune_ctcam bit\;1: modify the prune_ctcam bit" access="WO" offset="0x10.28" size="0x0.1" />
	<field name="c_s" descr="Clear or set:\;0: prune clear\;1: prune set" access="WO" offset="0x10.31" size="0x0.1" />
	<field name="pruning_vector_cs" descr="Pruning vector clear or set. Modify option defined by c_s\;Per bit:\;0: don&apos;t modify pruning_vector bit\;1: modify the pruning_vector bit" access="WO" offset="0x14.0" size="0x0.16" />
</node>

<node name="peapbm_ext" descr="" size="0xf8.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1\;Note: the register updates all duplicated regions" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="erp_id" descr="erp id" access="INDEX" offset="0x10.0" size="0x0.4" />
	<field name="erp_id_mask" descr="erp id mask, per bit:\;0: for both values of erp_id bit\;1: for value according to erp_id bit\;Example: mask 1111 - update only erp_id, mask 0000 - update all \;erps" access="INDEX" offset="0x10.8" size="0x0.4" />
	<field name="pruning_ctcam_cs" descr="Pruning C-TCAM clear or set. Clear or set defined by c_s\;0: don&apos;t modify prune_ctcam bit\;1: modify the prune_ctcam bit" access="WO" offset="0x10.28" size="0x0.1" />
	<field name="c_s" descr="Clear or set:\;0: prune clear\;1: prune set" access="WO" offset="0x10.31" size="0x0.1" />
	<field name="pruning_vector_cs" descr="Pruning vector clear or set. Modify option defined by c_s\;Per bit:\;0: don&apos;t modify pruning_vector bit\;1: modify the pruning_vector bit" access="WO" offset="0x14.0" size="0x0.16" />
	<field name="priority_start" descr="Update will be from priority_start (inclusive) to priority_end \;(inclusive).\;For Spectrum-2 range is 1.. cap_kvd_size-1" access="INDEX" offset="0x18.0" size="0x0.24" />
	<field name="priority_end" descr="Update will be from priority_start (inclusive) to priority_end \;(inclusive).\;For Spectrum-2 range is 1.. cap_kvd_size-1" access="INDEX" offset="0x1C.0" size="0x0.24" />
	<field name="key" descr="ACL Key as described in Section 10.6.2, &quot;Flex2 ACL Key Blocks \;Layout,&quot; on page 1475\;Note: for regions which have 12 Key Blocks the 6 lsb Key Blocks \;are valid and the 6 msb Key Blocks are not used for this function" access="INDEX" high_bound="23" low_bound="0" offset="0x20.0" size="0x60.0" />
	<field name="key_mask" descr="Mask\;Mask entries which match the key with this mask. Per bit:\;0: ignore bit key (always match)\;1: compare bit in key\;Note: for regions which have 12 Key Blocks the 6 lsb Key Blocks \;are valid and the 6 msb Key Blocks are not used for this function" access="INDEX" high_bound="23" low_bound="0" offset="0x80.0" size="0x60.0" />
	<field name="large_entry_key_id" descr="Large entry key ID\;A key for 12 Key block rules\;Reserved when the region has 2, 4 or 6 key blocks\;Range 0 .. cap_max_pe_large_key_id- 1" access="INDEX" offset="0xE0.0" size="0x0.24" />
	<field name="large_entry_key_id_mask" descr="Large entry key ID mask\;0: ignore bit large_entry_key_id (always match)\;1: compare bit in large_entry_key_id\;Reserved when the region has 2, 4 or 6 key blocks\;Range 0 .. cap_max_pe_large_key_id- 1" access="INDEX" offset="0xE4.0" size="0x0.24" />
	<field name="delta_start" descr="Start point of delta value and mask\;Units of bits\;Reserved when delta_mask = 0" access="INDEX" offset="0xF0.0" size="0x0.10" />
	<field name="delta_value" descr="Delta value\;Relevant only for large keys when delta_start &gt;= 27*8bits\;For all other cases the delta_value is given in the key" access="INDEX" offset="0xF4.0" size="0x0.8" />
	<field name="delta_mask" descr="Delta mask\;Per bit:\;0: ignore relevant bit from offset delta_start\;1: compare relevant bit from offset delta_start" access="INDEX" offset="0xF4.16" size="0x0.8" />
</node>

<node name="peaps_ext" descr="" size="0x34.0" >
	<field name="ovf" descr="Overflow:\;0: previous session ended okay\;1: previous session had an overflow \;Overflow example: value of 90 was shifted by -100 to -10\;This field is cleared at every read or write access\;Regardless of region" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="busy" descr="Busy:\;0: READY - can accept a new priority shift command\;1: BUSY - cannot accept a new priority shift command\;Regardless of region" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="ct_offset" descr="Offset within the C-TCAM region to start the priority shift\;Reserved when ct_size = 0" access="WO" offset="0x8.0" size="0x0.16" />
	<field name="ct_size" descr="The number of rules in the C-TCAM to do the priority shift, starting \;from ct_offset" access="WO" offset="0xC.0" size="0x0.16" />
	<field name="tcam_region_info" descr="Opaque object that represents the TCAM region\;See Section 10.10.13, &quot;PTAR - Policy-Engine TCAM Allocation \;Register,&quot; on page 1680.\;This is the base region. All duplicated region_id&apos;s will be shifted as \;well. See Section 10.10.17, &quot;PERD - Policy-Engine Region Dupli\;cation Register,&quot; on page 1691See Section 1773, &quot;tcam_re\;gion_info Layout,&quot; on page 1744" subnode="tcam_region_info_peaps" access="WO" offset="0x10.0" size="0x10.0" />
	<field name="priority_start" descr="Initial start priority\;For Spectrum-2 range is 1.. cap_kvd_size-1" access="WO" offset="0x20.0" size="0x0.24" />
	<field name="priority_end" descr="Initial end priority\;Must be equal or greater than priority_start\;For Spectrum-2 range is 1.. cap_kvd_size-1" access="WO" offset="0x24.0" size="0x0.24" />
	<field name="priority_inc" descr="2&apos;s complement value for priority increase or decrease" access="WO" offset="0x30.0" size="0x0.24" />
</node>

<node name="pecb_ext" descr="" size="0x210.0" >
	<field name="tfst" descr="Take First\;0: take last (in packet offset) extraction point (default)\;1: take first (in packet offset) extraction point\;Example1: L2-&gt;L3-&gt;UDP-&gt;FPH3-&gt;FPH3-&gt;FPH3\;Take the first or last FPH3\;Example2: IPv4-&gt;UDP. Take IPv4 (first) or UDP (last)\;Reserved when Spectrum-1 (which supports only last)." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="cbset" descr="Custom Bytes Set\;Range 0 .. cap_max_custom_byte_sets-1\;See encoding in Table 1215, &quot;Spectrum-1 Custom Bytes Sets,&quot; on \;page 1361" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="ext_point" descr="Extraction point protocol encoding\;Extraction point protocol encoding is define by Table 1219, &quot;Cus\;tom Bytes Extraction Points,&quot; on page 1363\;Example: ext_point &quot;IPv6 Payload&quot; is at index 11 (0xB)\;Maximum number of concurrent enabled extraction points per cbset \;is cap_max_ext_points\;See Table 1745, &quot;Extraction_point&lt;j&gt; Layout,&quot; on page 1726" access="RW" high_bound="255" low_bound="0" offset="0x10.16" size="0x200.0" />
</node>

<node name="peckc_ext" descr="" size="0x30.0" >
	<field name="key" descr="Key:\;0: has_conf_et\;1: dscp_range\;2: or_tcp_control_or_ecn\;4: ipv6_custom_extension\;5: inner_ipv6_custom_extension\;6: ipv6_hbh_custom_option\;7: inner_ipv6_hbh_custom_option" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="index" descr="Index\;For example: dscp_range[2]: key=1, index=2\;Valid bits according to the key" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="attributes0" descr="Attributes per key:\;has_conf_et: ethertype, 16bits\;\;dscp_range: dscp_min, 6bits\;\;or_tcp_control_or_ecn: xor, 9bits\;\;ipv6_custom_extension: value, 8bits\;inner_ipv6_custom_extension: value, 8bits\;\;ipv6_hbh_custom_option: value, 8bits\;inner_ipv6_hbh_custom_option: value, 8bits" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="attributes1" descr="Attributes per key:\;has_conf_et: tag length\;\;dscp_range: dscp_max, 6bits\;\;or_tcp_control_or_ecn: mask, 9bits\;or_tcp_control_or_ecn[i] = ({tcp_control,tcp_ecn_bits} ^ xor) &amp; \;mask)\;\;ipv6_custom_extension: mask, 8bits\;inner_ipv6_custom_extension: mask, 8bits\;\;ipv6_hbh_custom_option: mask, 8bits\;inner_ipv6_hbh_custom_option: mask, 8bits" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
</node>

<node name="pecnee_ext" descr="" size="0x18.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1\;Note: the counter (PECNER) is always enabled. It is suggested \;to clear the counter (PECNER.clear) after changing the \;region_id, erp_id_bitwise or ctcam" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="region_id_mask" descr="Region_id mask\;Per bit:\;0: ignore region_id relevant bit\;1: compare region_id relevant bit\;Can be used for a binary search on regions with high count val\;ues\;Range 0 .. 2^ (round_down(log2(cap_max_regions-1)) + 1)" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="erp_id_bitwise" descr="Erp ID to count on\;Value as bitwise. Can set either one erp or all erps. (e.g. value of \;b&apos;101 is not allowed).\;When more than 1 region is counted then all erps are counted\;Reserved when region_id_mask != FF&apos;s (more than 1 region)\;\;" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="ctcam" descr="Count on C-TCAM\;When more than 1 region then all C-TCAM access are counted\;Reserved when region_id_mask != 0 (more than 1 region)" access="RW" offset="0x14.0" size="0x0.1" />
</node>

<node name="pecner_ext" descr="" size="0x38.0" >
	<field name="clear" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="erp_initial_high" descr="ERP or C-TCAM is initial active after erpt_vector (phase 1)\;Note: if n (erps + ctcam) are enabled then the counter may \;increase by 0..n for a given region lookup" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="erp_initial_low" descr="ERP or C-TCAM is initial active after erpt_vector (phase 1)\;Note: if n (erps + ctcam) are enabled then the counter may \;increase by 0..n for a given region lookup" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="erp_post_bf_high" descr="ERP active after bloom filter (phase 2)\;Doesn&apos;t increment as C-TCAM\;Note: if n erps are enabled then the counter may increase by 0..n \;for a given region lookup\;Note: when PERCR.bf_bypass=1 then this counter does not \;count." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="erp_post_bf_low" descr="ERP active after bloom filter (phase 2)\;Doesn&apos;t increment as C-TCAM\;Note: if n erps are enabled then the counter may increase by 0..n \;for a given region lookup\;Note: when PERCR.bf_bypass=1 then this counter does not \;count." access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="erp_lookup_high" descr="ERP or CTCAM had a lookup - active after bloom filter and \;pruning (phase 3)\;Note: if n erps + ctcam are enabled then the counter may \;increase by 0..n for a given region lookup" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="erp_lookup_low" descr="ERP or CTCAM had a lookup - active after bloom filter and \;pruning (phase 3)\;Note: if n erps + ctcam are enabled then the counter may \;increase by 0..n for a given region lookup" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="erp_any_match_high" descr="ERP or CTCAM had a match (not yet a final match - later prior\;ity will choose the final)\;Note: if n erps + ctcam are enabled then the counter may \;increase by 0..n for a given region lookup" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="erp_any_match_low" descr="ERP or CTCAM had a match (not yet a final match - later prior\;ity will choose the final)\;Note: if n erps + ctcam are enabled then the counter may \;increase by 0..n for a given region lookup" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="erp_final_match_high" descr="ERP or CTCAM had a final match\;Note: the counter may increase by 0..1 for a given region lookup" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="erp_final_match_low" descr="ERP or CTCAM had a final match\;Note: the counter may increase by 0..1 for a given region lookup" access="RO" offset="0x34.0" size="0x4.0" />
</node>

<node name="pecnre_ext" descr="" size="0x10.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1\;Note: the counter (PECNRR) is always enabled. It is suggested \;to clear the counter (PECNRR.clear) after changing the \;region_id" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="region_id_mask" descr="Region_id mask\;Per bit:\;0: ignore region_id relevant bit\;1: compare region_id relevant bit\;Can be used for a binary search on regions with high count val\;ues\;Note: value of all &apos;0&apos; is not supported \;Range 0 .. 2^ (round_down(log2(cap_max_regions-1)) + 1)" access="RW" offset="0xC.0" size="0x0.16" />
</node>

<node name="pecnrr_ext" descr="" size="0x20.0" >
	<field name="clear" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="tcam_trigger_high" descr="Count number of tcam triggers (bind to ACL group)\;For example: if a packet has iACL and eirfACL then inc by 2\;Note: packets from CPU ingress are not counted" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="tcam_trigger_low" descr="Count number of tcam triggers (bind to ACL group)\;For example: if a packet has iACL and eirfACL then inc by 2\;Note: packets from CPU ingress are not counted" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="tcam_full_lookup_high" descr="Count number of tcam triggers which needed a full lookup\;\;Note: packets from CPU ingress are not counted\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="tcam_full_lookup_low" descr="Count number of tcam triggers which needed a full lookup\;\;Note: packets from CPU ingress are not counted\;" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="pefa_ext" descr="" size="0xb0.0" >
	<field name="index" descr="Index in the KVD Linear Centralized Database. For more details \;see Appendix A.4.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2256)\;Range is 0.. cap_max_kvd_action_sets - 1" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="pind" descr="Partial Index\;Used for partial action set\;0: full action set\;1: double partial action sets \;2: partial action set, partial index 0\;3: partial action set, partial index 1\;Note that &quot;full action set&quot; and &quot;partial action set, partial index 0&quot; \;have the same pointer but different indexes\;Reserved when Spectrum-1" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="as_user_val" descr="Action set user value\;Can be used for activity dump, see PEFAAD\;Note: for partial action sets, both action sets in the same index \;have the same as_user_val\;Reserved when ddd_en = 1\;Reserved when Spectrum-1\;" access="RW" offset="0x4.0" size="0x0.10" />
	<field name="ddd_en" descr="The action is DDD enabled\;Note that action DDD must be enabled if (1) DDD is enabled for \;actions and (2) the action is pointed by a ddd priority.\;See IDDD and IGCR.ddd_pe_actions_priority\;Note: for partial action sets, both action sets in the same index \;have the same ddd_en\;" access="RW" offset="0x4.20" size="0x0.1" />
	<field name="ca" descr="Clear activity:\;When write: \;0: activity is set\;1: activity is cleared\;2: activity is maintained (used for updating)\;When read:\;0, 2: activity is maintained\;1: after reading the activity is cleared\;Reserved when Spectrum-1\;When pind=1 then applies to both partials" access="OP" offset="0x4.24" size="0x0.2" />
	<field name="a1" descr="Activity of partial1\;Reserved when pind = 0 or pind = 2" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="a" descr="Activity of full or partial0\;For a new entry: set if ca=0, clear if ca=1\;Set if a packet lookup has hit on the specific entry\;Reserved when Spectrum-1\;When pind=&quot;double partial&quot; then applies to partial 0\;Reserved when pind = 3\;" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="flexible_action_set" descr="Action-set to perform when rule is matched.\;See Section 10.8, &quot;Flexible ACL Action Set,&quot; on page 1592.\;Must be zero padded if action set is shorter." access="RW" high_bound="41" low_bound="0" offset="0x8.0" size="0xa8.0" />
</node>

<node name="pefaad_ext" descr="" size="0x420.0" >
	<field name="filter_fields" descr="Filter Fields:\;if a bit is &apos;0&apos; then the relevant field is ignored and dump is done \;regardless of the field value\;Bit0: filter by activity: entry_a\;Bit1: filter by action set user value: as_user_val when ddd_en=0\;All set filters are relevant (there is AND between the filters)\;Reserved when op is Clear activity" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="num_rec" descr="At request: number of records requested\;At response: number of records dumped\;Range for request is 1..256\;Range for response is 0..256" access="OP" offset="0x4.0" size="0x0.9" />
	<field name="op" descr="Operation\;0: Dump entries\;1: Dump entries and force end of session (clear activity will clear \;this session while next dump will be a new session)\;2: Clear activity for all entries which were dumped in the current \;session" access="OP" offset="0x4.24" size="0x0.2" />
	<field name="entry_a" descr="Dump only if activity has value of entry_a\;Reserved when filter_fields bit0 is &apos;0&apos;" access="INDEX" offset="0x8.16" size="0x0.1" />
	<field name="as_user_val" descr="Action set user value\;Reserved when ddd_en = 1\;Reserved when filter_fields bit1 is &apos;0&apos;" access="INDEX" offset="0x10.0" size="0x0.10" />
	<field name="index_dump" descr="Dumped index\;For Spectrum-2 pointer to policy engine actions array which is in \;the KVH Linear." subnode="index_dump" access="RO" high_bound="255" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="pemrbt_ext" descr="" size="0x14.0" >
	<field name="protocol" descr="Protocol:\;0: IPv4\;1: IPv6" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="group_id" descr="ACL group identifier (acl_group_id)\;Range of group id is 0..cap_max_acl_groups-1\;Note: the group_id must be configured prior to enabling mc router" access="RW" offset="0x10.0" size="0x0.16" />
</node>

<node name="pepc_reg_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="twisted_pair_an_mode" descr="twisted_pair operational mode in case of AN enabled: \;0x0 - auto Master/Slave mode for AN links.\;0x1 - Master mode\;0x2 - Slave mode" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="twisted_pair_force_mode" descr="twisted_pair operational mode in case of AN disabled: \;0x0 - Master mode\;0x1 - Slave mode" access="RW" offset="0x4.8" size="0x0.1" />
</node>

<node name="perar_ext" descr="" size="0x8.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="hw_region" descr="HW Region\;Range 0 .. cap_max_regions-1\;Spectrum-2 note: \;- For a 8 key block region, 2 consecutive regions are used\;- For a 12 key block region, 3 consecutive regions are used\;- For sensitivity (PACL.acl_type != 0): if any region (in the sensi\;tivity) is 2 then all regions (in the sensitivity) are 2, if any region \;(in the sensitivity) is 3 then all regions (in the sensitivity) are 3\;" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="perb_ext" descr="" size="0xa0.0" >
	<field name="rule_index" descr="Rule Index\;Range 0..3" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="pipe_stage" descr="Pipe line stage:\;0: iport\;1: irif\;2: erif\;3: eport" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="op" descr="0: Bind ACL to Routing Interface\;1: Unbind ACL from Routing Interface (default)" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="group_id" descr="ACL group identifier (acl_group_id)\;Range of group id is 0..cap_max_acl_groups-1\;Note: the group_id must be configured prior to enabling mc router" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="cmu" descr="Classifier Mask Underlay:\;0: regular classifier\;1: mask (ignore) underlay (inner_ prefix) fields if no underlay\;" access="RW" offset="0xC.0" size="0x0.1" />
	<field name="cmo" descr="Classifier Mask Overlay:\;0: regular classifier\;1: mask (ignore) overlay (no inner_ prefix) fields if underlay exists\;" access="RW" offset="0xC.1" size="0x0.1" />
	<field name="classifier_entry" descr="Classifier entry, related to pipe_stage:\;Table 1653, &quot;PERB classifier_iport Layout,&quot; on page 1665" access="RW" high_bound="31" low_bound="0" offset="0x20.0" size="0x80.0" />
</node>

<node name="perbeg_ext" descr="" size="0x10.0" >
	<field name="egress_local_port" descr="Egress local port" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="rb_eport_group" descr="Used by PERB classifier" access="RW" offset="0xC.0" size="0x0.4" />
</node>

<node name="perbrg_ext" descr="" size="0x10.0" >
	<field name="dir" descr="Direction:\;0: irif\;1: erif" access="INDEX" enum="irif=0x0,erif=0x1" offset="0x0.0" size="0x0.1" />
	<field name="rif" descr="Router Interface" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="rb_rif_group" descr="According to dir: rb_irif_group, rb_erif_group\;Used by PERB classifier" access="RW" offset="0xC.0" size="0x0.4" />
</node>

<node name="percr_ext" descr="" size="0x80.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="bf_bypass" descr="Bloom filter bypass\;0: Bloom filter is used (default)\;1: Bypass BF, erps are used regardless of bloom filter\;The bypass is an OR condition of region_id or erp. See \;PERPT.bf_bypass\;\;Reserved when SwitchX/-2 and Spectrum-1" access="RW" offset="0x4.16" size="0x0.1" />
	<field name="ctcam_ignore_prune" descr="Ignore prune_ctcam by other A-TCAM rules\;Used e.g. for a new rule" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="atcam_ignore_prune" descr="Ignore prune_vector by other A-TCAM rules\;Used e.g. for a new rule\;See PGCR.atcam_ignore_prune_vector, See Section 10.10.1, \;&quot;PGCR - Policy-Engine General Configuration Register,&quot; on \;page 1655" access="RW" offset="0x4.25" size="0x0.1" />
	<field name="master_mask" descr="Master mask, mask the ERPs, the delta_masks and the C-TCAM \;lookup.\;When there are no erp&apos;s (erpt_pointer_valid = 0) then this pro\;vides the mask\;Per bit:\;0: TCAM will ignore the bit in key\;1: TCAM will compare the bit in key\;Reserved when SwitchX/-2 and Spectrum-1\;\;" access="RW" high_bound="23" low_bound="0" offset="0x20.0" size="0x60.0" />
</node>

<node name="perd_ext" descr="" size="0x50.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="atcam_dup" descr="A-TCAM region duplication:\;0: dup 1\;1: dup 2\;2: dup 4\;3: dup 8\;4: dup 16" access="RW" offset="0x8.0" size="0x0.3" />
	<field name="region_id_dup" descr="Region ID for duplication\;Reserved when i &gt;= atcam_dup\;" subnode="region_id_dup" access="RW" high_bound="14" low_bound="0" offset="0x14.0" size="0x3c.0" />
</node>

<node name="pererp_ext" descr="" size="0x1c.0" >
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="ctcam_le" descr="C-TCAM Lookup enable\;Reserved when erpt_pointer_valid = 0\;" access="RW" offset="0x4.28" size="0x0.1" />
	<field name="erpt_pointer" descr="Pointer to erp table within the erp bank\;Can be changed for an existing region\;Range is 0.. cap_max_erp_table_size-1\;Reserved when erpt_pointer_valid = 0\;Note: the erpt_pointer can have the same value for different \;ACLs. However, the erpt_pointer must not point to a mid-entry of \;different ACL (e.g. if ACL1 uses erpt_pointer 100 with vector of \;8 lsbs then ACL2 must not point to the range 101..107)" access="RW" offset="0x10.0" size="0x0.8" />
	<field name="erpt_bank_pointer" descr="Pointer to erp table bank\;Note: May be modified any time\;Range 0 .. cap_max_erp_table_banks-1\;Reserved when erpt_pointer_valid = 0" access="RW" offset="0x10.16" size="0x0.4" />
	<field name="ctcam_only" descr="C-TCAM only\;Lookup only in C-CTAM\;Reserved when erpt_pointer_valid = 1\;\;" access="RW" offset="0x10.30" size="0x0.1" />
	<field name="erpt_pointer_valid" descr="erpt_pointer is valid:\;0: exact match, erpt_pointer is not valid\;1: use erps, erpt_pointer is valid\;The non valid erpt is used as follows:\;- if ctcam_only = 0 then lookup only 1 time in A-TCAM, without \;erp, using master_mask. a.k.a. exact-match. No C-TCAM lookup\;- if ctcam_only = 1 then lookup only in C-TCAM, without erp\;" access="RW" offset="0x10.31" size="0x0.1" />
	<field name="erpt_vector" descr="Vector of allowed erp_indexes starting from erpt_pointer withing \;the erpt_bank_pointer\;Note that the allow is on erp_index and not on erp_id\;Used for speeding the lookups \;Next entries will be in next bank\;\;Reserved when erpt_pointer_valid = 0" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="master_rp_id" descr="Master RP ID\;When there are no erp&apos;s then this provide the erp_id for the lookup\;Reserved when erpt_pointer_valid = 1\;Can be changed for an existing region\;" access="RW" offset="0x18.0" size="0x0.4" />
</node>

<node name="perpt_ext" descr="" size="0x80.0" >
	<field name="erpt_index" descr="Index to erp table within the erp bank\;Within an erp range pointed by an ACL the lower entries are \;searched before higher entries.\;Range is 0.. cap_max_erp_table_bank_size-1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="erpt_bank" descr="Erp table bank\;Range 0 .. cap_max_erp_table_banks-1" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="key_size" descr="0: 2 key blocks \;1: 4 key blocks \;2: 8 key blocks \;3: 12 key blocks" access="OP" offset="0x4.0" size="0x0.4" />
	<field name="erp_id" descr="erp ID for use by the rules\;Note that the erp_id may be modified by SW, even when the erp is \;in use\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="bf_bypass" descr="Bloom Filter bypass\;0: This erp is used only if bloom filter state is set for the given rule \;1: This erp is used regardless of bloom filter state\;The bypass is an OR condition of region_id or erp. See \;PERCR.bf_bypass\;" access="RW" offset="0x8.8" size="0x0.1" />
	<field name="erpt_base_index" descr="Base Index to erp table within the erp bank\;Must align to erp_index_in_vector\;Range is 0.. cap_max_erp_table_bank_size-1" access="OP" offset="0xC.0" size="0x0.8" />
	<field name="erpt_base_bank" descr="Base Erp table bank, points to head of erp_vector\;Must align to erp_index_in_vector\;Range 0 .. cap_max_erp_table_banks-1" access="OP" offset="0xC.16" size="0x0.4" />
	<field name="erp_index_in_vector" descr="erp index in the vector\;Must align to {erpt_base_bank, erpt_base_index}\;" access="OP" offset="0x10.0" size="0x0.4" />
	<field name="erp_vector" descr="erp vector, needed for write operations\;" access="OP" offset="0x14.0" size="0x0.16" />
	<field name="mask" descr="Mask, at the same size as key. per bit:\;0: A-TCAM will ignore the bit in key\;1: A-TCAM will compare the bit in key\;" access="RW" high_bound="23" low_bound="0" offset="0x20.0" size="0x60.0" />
</node>

<node name="pevpb_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Ingress local port \;Not including CPU port\;Note: Spectrum-2: no VLAN binding for tunnel_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ev" descr="Enable VLAN binding from ingress port\;0: disable\;1: enable (default)" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="pfca_ext" descr="" size="0xc.0" >
	<field name="index" descr="Counter set index" access="INDEX" offset="0x0.0" size="0x0.9" />
	<field name="type" descr="Counter type:\;0: Bytes_counter\;1: Packets_counter\;" access="RW" enum="Bytes_counter=0x0,Packets_counter=0x1" offset="0x0.24" size="0x0.2" />
	<field name="op" descr="Operation:\;0: NOP\;1: Allocate\;2: Test\;3: Free" access="WO" enum="NOP=0x0,Allocate=0x1,Test=0x2,Free=0x3" offset="0x0.30" size="0x0.2" />
	<field name="counter_set" descr="Opaque object that represents the flow counter. Returned when \;allocating counter. Provided by software for action-set binding or \;any other counter operation." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="pfcc_reg_ext" descr="" size="0x20.0" >
	<field name="shl_opr" descr="Send to higher layers operation:\;0 - Pause and PFC are handled by the port (default)\;1 - Pause and PFC are handled by the port and are also been send to \;higher layers.\;Only valid if shl_cap = 1." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="shl_cap" descr="Send to higher layers capabilities:\;0 - No capability of sending Pause and PFC to higher layers\;1 - Device has capability of send Pause and PFC to higher layers\;NOTE: This relates to IEEE 802.3 PAUSE and IEEE 802.3 PFC." access="RO" offset="0x0.1" size="0x0.1" />
	<field name="critical_stall_mask" descr="Valid only on HCAs.\;Mask bit indicating if device_stall_critical_watermark should be \;updated.\;If set to &quot;1&quot;, device_stall_critical_watermark will be updated" access="WO" offset="0x0.2" size="0x0.1" />
	<field name="minor_stall_mask" descr="Valid only on HCAs.\;Mask bit indicating if device_stall_minor_watermark should be \;updated.\;If set to &quot;1&quot;, device_stall_minor_watermark will be updated" access="WO" offset="0x0.3" size="0x0.1" />
	<field name="ppan_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if ppan should be updated.\;If set to &quot;0&quot;, ppan will be updated" access="WO" offset="0x0.4" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="set_buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;\;Buffer ownership configuration. when this bits are set to a value other \;than 0, device will ignore all other fields pfcc register\;0 - unknown \;1 - device owned, all buffer configuration will return to its defaults. \;2 - Reserved \;3 - Reserved" access="WO" offset="0x0.24" size="0x0.2" />
	<field name="buf_ownership" descr="Supported by HCA only, see PCAM.feature_cap_mask bit 44.\;Current status of buffer ownership\;0 - unknown\;1 - device owned  \;2 - software owned" access="RO" offset="0x0.26" size="0x0.2" />
	<field name="cap_remote_admin" descr="Indicates if operation of remote admin parameters (dcxb_operation_\;type 0x2) is supported. \;" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="Indicates if operation of local admin parameters (dcxb_operation_type \;0x1) is supported. \;" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="dcbx_operation_type" descr="The Operation type, valid only on HCAs.\;0x0: local_operative_parameters\;0x1: local_admin_parameters - supported only when cap_local_ad\;min==1.\;0x2: remote_admin_parameters - supported only when cap_re\;mote_admin==1.\;Only pfctx and pfcrx are supported on remote device" access="INDEX" enum="local_operative_parameters=0x0,local_admin_parameters=0x1,remote_admin_parameters=0x2" offset="0x0.30" size="0x0.2" />
	<field name="prio_mask_rx" descr="Bit per prio indicating if RX flow control policy should be updated \;based on bit pfcrx." access="WO" offset="0x4.0" size="0x0.8" />
	<field name="prio_mask_tx" descr="Bit per prio indicating if TX flow control policy should be updated \;based on bit pfctx." access="WO" offset="0x4.16" size="0x0.8" />
	<field name="ppan" descr="Pause policy auto negotiation\;0: disabled - generate and ignore pause frames based on pptx, pprx\;1: enabled - when auto-negotiation is performed, set the pause policy \;based on the auto-negotiation resolution.\;Note - The auto-negotiation advertisement is set according to pptx, \;pprx.\;Note - When PFC is set on the TX / RX ppan must be set to 0." access="RW" enum="disabled=0x0,enabled=0x1" offset="0x4.28" size="0x0.4" />
	<field name="fctx_disabled" descr="Valid only on HCAs.\;The bit is set if the device has passed the device_stall_critical_water\;mark ( for global flow control or any priority when using priority flow \;control) and has become stalled. \;When fctx_disabled is set, the device will not send flow control and \;priority flow control (PFC) packets.\;" access="RO" offset="0x8.8" size="0x0.1" />
	<field name="pfctx" descr="Priority based flow control policy on TX[7:0]. Per priority bit mask:\;0 - never generate pause frames on the specified priority (default)\;1 - generate pause frames according to RX buffer threshold on the \;specified priority\;pfctx, pptx must be mutually exclusive (for example, only one of them \;at most can be set)." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="pptx_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if pptx should be updated.\;If set to &quot;0&quot;, pptx will be updated" access="WO" offset="0x8.29" size="0x0.1" />
	<field name="aptx" descr="Active (operational) pause policy on TX\;0 - do not generate pause frames\;1 - generate pause frames according to RX buffer threshold" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="pptx" descr="Admin pause policy on TX (see also pfctx):\;0 - never generate pause frames (default)\;1 - generate pause frames according to RX buffer threshold" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="pfcrx" descr="Priority based flow control policy on RX[7:0]. Per priority bit mask:\;0 - ignore incoming pause frames on the specified priority (default)\;1 - respect incoming pause frames on the specified priority" access="RW" offset="0xC.16" size="0x0.8" />
	<field name="pprx_mask_n" descr="Valid only on HCAs.\;Mask bit (negative polarity) indicating if pprx should be updated.\;If set to &quot;0&quot;, pprx will be updated" access="WO" offset="0xC.29" size="0x0.1" />
	<field name="aprx" descr="Active (operational) pause policy on RX\;0 - ignore received pause frames\;1 - respect received pause frames" access="RO" offset="0xC.30" size="0x0.1" />
	<field name="pprx" descr="Admin pause policy on RX (see also pfcrx):\;0 - ignore received pause frames (default)\;1 - respect received pause frames" access="RW" offset="0xC.31" size="0x0.1" />
	<field name="device_stall_critical_watermark" descr="Valid only on HCAs (When health_mon_rx_activity is set).\;The maximum period for a single received packet processing, if the \;packet was not processed during this time, the device will be declared \;as stalled and will increase the device_stall_critical_watermark_cnt \;(PPCNT) counter. Value given in mSec, The maximum period is 8 \;sec. \;The special value of 0, indicates that the device_stall_critical_water\;mark is inactive.\;Range: 0x0050 - 0x1F40 \;see also critical_stall_mask" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="device_stall_minor_watermark" descr="Valid only on HCAs (When health_mon_rx_activity is set).\;The maximum period for a single received packet processing, if the \;packet was not processed during this time, the device will increase the \;device_stall_minor_watermark_cnt (PPCNT). Value given in mSec, \;The maximum period is 8 sec. \;The special value of 0, indicates that the device_stall_minor_water\;mark is inactive.\;Range: 0x0050 - 0x1F40 \;see also critical_stall_mask" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="pfcnt_ext" descr="" size="0x20.0" >
	<field name="counter_set" descr="Counter Set Identifier.\;For SwitchX and SwitchX-2: an opaque object provided upon \;allocation of a counter set and used to identify the flow counter to \;access." access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for \;relevant flow counter. \;Note: This bit can be set for both Write() and Read() operation to \;enable clear on read operation." access="OP" offset="0x4.31" size="0x0.1" />
	<field name="flow_counter_0" descr="Flow counter value" access="RO" high_bound="5" low_bound="0" offset="0x8.0" size="0x18.0" />
</node>

<node name="pfsc_reg_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fwd_admin" descr="Administratively configured of Forward switching for Egress:\;0 - Allow cut-through forwarding\;1 - Always Store and Forward" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="fwd_oper" descr="Operational Egress Forward switching:\;0 - Cut-Through forwarding operation is allowed\;1 - Only Store and Forward operation" access="RO" offset="0x8.0" size="0x0.4" />
</node>

<node name="pgcr_ext" descr="" size="0x20.0" >
	<field name="pbs_table_size" descr="Number of PBS entries. This is a settable capability.\;Reserved when Spectrum/-2\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="update_prune" descr="Update atcam_ignore_prune_vector only\;0: update all fields including atcam_ignore_prune_vector\;1: update only atcam_ignore_prune_vector\;Reserved when SwitchX/-2 and Spectrum-1" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="max_iacl" descr="Max Ingress ACL\;Maximum number of Ingress ACLs\;Reserved when Spectrum/-2" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="max_eacl" descr="Max Egress ACL\;Maximum number of Egress ACLs\;Reserved when Spectrum/-2" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="atcam_ignore_prune_vector" descr="When atcam_ignore_prune is set for a region, then the ignore \;is for ERP IDs according to this vector\;Each bit is per ERP ID\;0: do not ignore erp prune\;1: ignore erp prune\;\;Reserved when SwitchX/-2 and Spectrum-1\;" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="default_action_pointer_base" descr="Default action pointer base\;Each region has a default action pointer which is equal to:\;default_action_pointer_base + region_id\;For Spectrum-2 pointer to policy engine actions array which is \;in the KVH Linear.\;Notes: \;1. may be changed on the fly, need fence to release old action \;entries\;2. pointer either to full action-set or to partial pointer 0\;3. when a multi-ACL the first region_id is used for all regions \;of the multi-ACL" access="RW" offset="0x1C.0" size="0x0.24" />
</node>

<node name="pgmr_ext" descr="" size="0x18.0" >
	<field name="pg_sel" descr="Selection between an operation on a local port or a group, for &apos;set&apos; \;and &apos;get&apos; operations. \;0 - local port (group field is neglected even if set)\;1 - group (local_port field is neglected even if set)" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="group" descr="Group number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is inter\;preted:\;0 - Local port number\;1 - IB / label port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="group_of_port" descr="The corresponding group number for thelocal_port" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="ports_mapping_of_group" descr="A bit map of all available local ports in the system (each bit rep\;resents a local port). \;The corresponding bits which represent the local ports for the spe\;cific group in the group field, are set to &apos;1&apos;.\;If set to &apos;0&apos; - not in that specific group or not available." access="RW" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
</node>

<node name="phbr_binding_reg_ext" descr="" size="0x1c.0" >
	<field name="pnat" descr="Port number access type:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="opcode" descr="Opcode:\;0 - Bind a local_port, hist_id\;1 - Unbind a local_port, hist_id" access="RW" offset="0x0.28" size="0x0.4" />
	<field name="hist_id" descr="Histogram id to bind\;from 0 to cap_max_port_hist_id - 1" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="mode_cap" descr="Mode capability \;bit 0 - Exponential histogram supported" access="RO" offset="0x4.14" size="0x0.2" />
	<field name="hist_type" descr="0x0020: PortRcvData\;0x0021: PortRcvData_Prio\;0x0040: PortXmitData\;0x0041: PortXmitData_Prio\;0x0042: PortXmitWait" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="mode" descr="Mode:\;0 - Linear histogram\;1 - Exponential histogram" access="RW" offset="0x8.28" size="0x0.3" />
	<field name="hist_parameters" descr="According to hist_type\;" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="hist_min_value" descr="Min value for histogram main range\;Units according to the units of the hist_type\;must be greater than zero." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="hist_max_value" descr="Max value for histogram main range\;\;NOTE: for Spectrum device the following rules must be met:\;1. hist_max_value = hist_min_value + 2^n, n &gt;= 3\;2. hist_max_value &lt; 2^29\;Units according to the units of the hist_type" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="sample_time" descr="Sample time interval. \;Allowed range for Switch-IB and Spectrum:\;time = 2^sample_time * 128nSec\;sample_time range is 0..cap_max_sample_time-1" access="RW" offset="0x18.0" size="0x0.6" />
</node>

<node name="phcr_err_cnt_column_range" descr="" size="0x4.0" >
	<field name="low_val" descr="" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="high_val" descr="" access="RW" offset="0x0.8" size="0x0.4" />
</node>

<node name="phcr_ext" descr="" size="0x4c.0" >
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="opcode" descr="Opcode:\;0: Query the number of histogram columns.\;1: Set the range for each of the columns. \;2-7: Reserved" access="RW" offset="0x0.29" size="0x0.3" />
	<field name="num_err_cntrs" descr="Number of counters that are available for counting errors per \;each of the ports." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="err_cnt_column_range_0" descr="Configuration per each of the counters\;See Table 1165, &quot;PHCR - Port Histogram Counter Configuration \;Layout,&quot; on page 1359" subnode="phcr_err_cnt_column_range" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="phrr_reg_ext" descr="" size="0x60.0" >
	<field name="pnat" descr="Port number access type:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clr" descr="Clear:\;1 - Clear the data in the histogram agent" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="hist_id" descr="see PHBR" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="bin" descr="Value of bin \;Units according to the units of the hist_type which is used for the \;hist_id\;Max bins is according to cap_hist_num_bins" subnode="uint64" access="RO" high_bound="9" low_bound="0" offset="0x10.0" size="0x50.0" />
</node>

<node name="phys_layer_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in \;msec.\;[Internal] supported in USR" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear event in \;msec.\;[Internal] supported in USR" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="symbol_errors_high" descr="Perf.PortCounters(SymbolErrorCounter) = Perf.Port\;Counters(UnknownSymbol)\;[Internal] supported in USR" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="symbol_errors_low" descr="Perf.PortCounters(SymbolErrorCounter) = Perf.Port\;Counters(UnknownSymbol)\;[Internal] supported in USR" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="sync_headers_errors_high" descr="Perf.PortExtendedSpeedsCounters(SynchHeader\;ErrorCounter)" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="sync_headers_errors_low" descr="Perf.PortExtendedSpeedsCounters(SynchHeader\;ErrorCounter)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane0Counter) / BIP error counter, lane 0\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;[Internal] supported in USR" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane0Counter) / BIP error counter, lane 0\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;[Internal] supported in USR" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane1Counter) / BIP error counter, lane 1\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;[Internal] supported in USR" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane1Counter) / BIP error counter, lane 1\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;[Internal] supported in USR" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane2Counter) / BIP error counter, lane 2\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;[Internal] supported in USR" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane2Counter) / BIP error counter, lane 2\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;[Internal] supported in USR" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane3Counter) / BIP error counter, lane 3\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3\;[Internal] supported in USR" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPer\;Lane3Counter) / BIP error counter, lane 3\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3\;[Internal] supported in USR" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FECCorreca\;bleBlockCounter)" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_low" descr="Perf.PortExtendedSpeedsCounters(FECCorreca\;bleBlockCounter)" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FEUncorreca\;bleBlockCounter)" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_low" descr="Perf.PortExtendedSpeedsCounters(FEUncorreca\;bleBlockCounter)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_high" descr="The number of RS-FEC blocks received that had no \;errors.\;Note: Total rs_fec blocks received = rs_fec_corrected_\;blocks + rs_fec_uncorrectable_blocks + rs_fec_no_er\;rors_blocks" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_low" descr="The number of RS-FEC blocks received that had no \;errors.\;Note: Total rs_fec blocks received = rs_fec_corrected_\;blocks + rs_fec_uncorrectable_blocks + rs_fec_no_er\;rors_blocks" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_high" descr="Perf.PortExtendedSpeedCounters(PortFECCor\;rectedSymbolCounter)" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_low" descr="Perf.PortExtendedSpeedCounters(PortFECCor\;rectedSymbolCounter)" access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane0)" access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane0)" access="RO" offset="0xA4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane1)" access="RO" offset="0xA8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane1)" access="RO" offset="0xAC.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane2)" access="RO" offset="0xB0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane2)" access="RO" offset="0xB4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane3)" access="RO" offset="0xB8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSym\;bolCounterLane3)" access="RO" offset="0xBC.0" size="0x4.0" />
	<field name="link_down_events" descr="Perf.PortCounters(LinkDownedCounter)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0xC0.0" size="0x4.0" />
	<field name="successful_recovery_events" descr="Perf.PortCounters(LinkErrorRecoveryCounter)\;Note: This counter is valid only for IB." access="RO" offset="0xC4.0" size="0x4.0" />
</node>

<node name="phys_layer_stat_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in \;msec.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear event in \;msec.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="phy_received_bits_high" descr="This counter provides information on the total amount of \;traffic (bits) received.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="phy_received_bits_low" descr="This counter provides information on the total amount of \;traffic (bits) received.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="phy_symbol_errors_high" descr="This counter provides information on error bits that were \;not corrected by FEC correction algorithm or that FEC is \;not active.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="phy_symbol_errors_low" descr="This counter provides information on error bits that were \;not corrected by FEC correction algorithm or that FEC is \;not active.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="phy_corrected_bits_high" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="phy_corrected_bits_low" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_high" descr="This counter provides information on error bits that were \;identified on lane 0. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_low" descr="This counter provides information on error bits that were \;identified on lane 0. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_high" descr="This counter provides information on error bits that were \;identified on lane 1. \;When FEC is enabled this induction corresponds to cor\;rected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_low" descr="This counter provides information on error bits that were \;identified on lane 1. \;When FEC is enabled this induction corresponds to cor\;rected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_high" descr="This counter provides information on error bits that were \;identified on lane 2. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;\;\;\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_low" descr="This counter provides information on error bits that were \;identified on lane 2. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;\;\;\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_high" descr="This counter provides information on error bits that were \;identified on lane 3. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3\;\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_low" descr="This counter provides information on error bits that were \;identified on lane 3. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3\;\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_high" descr="This counter provides information on error bits that were \;identified on lane 4. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 4\;\;\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_low" descr="This counter provides information on error bits that were \;identified on lane 4. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 4\;\;\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_high" descr="This counter provides information on error bits that were \;identified on lane 5. \;When FEC is enabled this induction corresponds to cor\;rected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 5\;\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_low" descr="This counter provides information on error bits that were \;identified on lane 5. \;When FEC is enabled this induction corresponds to cor\;rected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 5\;\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_high" descr="This counter provides information on error bits that were \;identified on lane 6. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 6\;\;\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_low" descr="This counter provides information on error bits that were \;identified on lane 6. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 6\;\;\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_high" descr="This counter provides information on error bits that were \;identified on lane 7. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 7\;\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_low" descr="This counter provides information on error bits that were \;identified on lane 7. \;When FEC is enabled this induction corresponds to cor\;rected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 7\;\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="raw_ber_coef" descr="Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)\;" access="RO" offset="0x60.0" size="0x0.4" />
	<field name="raw_ber_magnitude" descr="Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)\;" access="RO" offset="0x60.8" size="0x0.8" />
	<field name="effective_ber_coef" descr="Effective_BER = \;effective_ber_coef*10^(-effective_ber_magnitude)\;" access="RO" offset="0x64.0" size="0x0.4" />
	<field name="effective_ber_magnitude" descr="Effective_BER = \;effective_ber_coef*10^(-effective_ber_magnitude)\;" access="RO" offset="0x64.8" size="0x0.8" />
</node>

<node name="pifr_reg_ext" descr="" size="0x60.0" >
	<field name="local_port" descr="Local port number.\;Note: Port isolation is not supported to \ from port 0 (i.e CPU port)." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="port_filter" descr="Port filter bitmask\;1 - Filter - Packets coming from port_filter&lt;i&gt; will not be transmitted to \;port local_port. \;0 - Do not filter (default value for all local_port).\;All LAG ports must share the same configuration.\;Refer to the relevant section for port numbering scheme." access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="port_filter_update_en" descr="port_filter_update_en bitmask, see port_filter\;When port_filter_update_en&lt;i&gt; set, the filter value for local port i is \;updated according to port_filter&lt;i&gt;.\;When port_filter_update_en&lt;i&gt; is cleared, the filter value for local port i \;maintains its current value." access="WO" high_bound="7" low_bound="0" offset="0x40.0" size="0x20.0" />
</node>

<node name="pipg_reg_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ipg" descr="Inter Packet Gap. Sets the Inter Packet Gap value for the ports, in 4 bytes \;granularity. Default value of this field is 3 (indicating 12 bytes IPG)." access="RW" offset="0x4.2" size="0x0.4" />
	<field name="dic" descr="Deficit Idle Count. When set, the dic bit is set, the Deficit Idle Count mech\;anism is enabled, else it is disabled.\;This bit is set by default." access="RW" offset="0x4.31" size="0x0.1" />
</node>

<node name="plbf_reg_ext" descr="" size="0x8.0" >
	<field name="lbf_mode" descr="Loop-back filter mode:\;0 - Do not update loop-back filter mode\;1 - Disable loop-back filtering\;2 - Enable loop-back filtering \;By default, loop-back filter is enabled for ALL ports" access="RW" offset="0x0.0" size="0x0.3" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
</node>

<node name="plib_reg_ext" descr="" size="0x10.0" >
	<field name="ib_port" descr="In IB port: InfiniBand port remapping for local_port\;In Ethernet port: Label port remapping for local_port\;Note: ib_port number can only be updated when a port admin state is DIS\;ABLED." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="split_num" descr="Valid only for Ethernet Switches. \;Label split mapping for local_port" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="slot_num" descr="Valid only for Ethernet Switches. \;Slot_number mapping for local_port" access="RW" offset="0x8.0" size="0x0.4" />
</node>

<node name="pmaos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Module state (reserved while admin_status is disabled):\;0: initializing\;1: plugged_enabled\;2: unplugged\;3: module_plugged_with_error - (details in error_type).\;4: plugged_disabled" access="RO" enum="initializing=0x0,plugged_enabled=0x1,unplugged=0x2,module_plugged_with_error=0x3,plugged_disabled=0x4" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Module administrative state (the desired state of the module):\;1: enabled\;2: disabled_by_configuration\;3: enabled_once - if the module is active and then unplugged, or \;module experienced an error event, the operational status should \;go to &quot;disabled&quot; and can only be enabled upon explicit enable \;command.\;\;Note - To disable a module, all ports associated with the port must \;be disabled first.\;" access="RW" enum="enabled=0x1,disabled_by_configuration=0x2,enabled_once=0x3" offset="0x0.8" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rst" descr="Module Reset toggle\;NOTE: setting reset while module is plugged-in will result in tran\;sition of oper_status to initialization." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="e" descr="Event Generation on operational state change:\;0: Do_not_generate_event\;1: Generate_Event \;2: Generate_Single_Event" access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="error_type" descr="Module error details:\;0x0: Power_Budget_Exceeded\;0x1: Long_Range_for_non_MLNX_cable_or_module\;0x2: Bus_stuck - (I2C Data or clock shorted)\;0x3: bad_or_unsupported_EEPROM\;0x4: Enforce_part_number_list\;0x5: unsupported_cable\;0x6: High_Temperature\;0x7: bad_cable - (Module/Cable is shorted)\;0x8: PMD_type_is_not_enabled - (see PMTPS).\;0xc: pcie_system_power_slot_Exceeded\;Valid only when oper_status = 4&apos;b0011." access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc" offset="0x4.8" size="0x0.4" />
	<field name="operational_notification" descr="This notification can occur only if module passed initialization \;process\;0x0: No notifications.\;0x1: Speed degradation - the module is not enabled in its full \;speed due to incompatible transceiver/cable \;Valid only when oper_status = 4&apos;b0001." access="RO" offset="0x4.16" size="0x0.4" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be \;updated based on the e field. Only relevant on Set operations." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin state will be \;updated based on admin_state field. Only relevant on Set() opera\;tions." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pmcr_reg_ext" descr="" size="0x1c.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cs_sel" descr="Valid only for CMIS (QSFP-DD / SFP-DD / OSFP) compliant modules.\;If Control Set 1 not implemented or non CMIS module ignore field.\;0 - Auto (default)\;1 - Use Control Set 0\;2 - Use Control Set 1" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="cdr_override_cntl" descr="Module CDR override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="cdr_override_value" descr="Valid only in case CDR is configured to override mode by cdr_over\;ride_cntl: \;0 - RX OFF, TX OFF\;1 - RX ON , TX OFF\;2 - RX OFF, TX ON\;3 - RX ON, TX ON" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="tx_disable_override_cntl" descr="In HCA, valid based on PCAM feature capabilities. \;Module TX_DISABLE override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="tx_disable_override_value" descr="Valid only in case TX_DISABLE is configured to override mode by tx_\;disable_override_cntl: \;0 - TX_DISABLE is low (i.e. TX is enabled)\;" access="RW" offset="0x4.24" size="0x0.2" />
	<field name="rx_amp_override_cntl" descr="Module RX amplitude override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="rx_amp_override_value" descr="Valid only in case RX amplitude is configured to override mode by \;rx_amp_override_cntl" access="RW" offset="0x8.8" size="0x0.4" />
	<field name="rx_los_override_cntl" descr="Valid only in case RX _LOS is configured to override mode by \;rx_los_override_admin" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="rx_los_override_admin" descr="Module RX _LOS override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x8.24" size="0x0.2" />
	<field name="rx_emp_override_cntl" descr="Module RX emphasis override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0xC.0" size="0x0.2" />
	<field name="rx_emp_override_value" descr="Valid only in case RX emphasis is configured to override mode by \;rx_emp_override_cntl" access="RW" offset="0xC.8" size="0x0.4" />
	<field name="tx_equ_override_cntl" descr="Module TX equalization override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x10.0" size="0x0.2" />
	<field name="tx_equ_override_value" descr="Valid only in case TX equalization is configured to override mode by \;tx_equ_override_cntl" access="RW" offset="0x10.8" size="0x0.4" />
	<field name="tx_adaptive_override_cntrl" descr="Module adaptive tuning flow override control:\;0 - Auto (default)\;1 - Keep the module configuration" access="RW" offset="0x10.24" size="0x0.2" />
	<field name="ap_sel_override_cntrl" descr="Module Application select override control:\;0 - Auto (default)\;1 - Use Module&apos;s Default application value\;2 - Override" access="RW" offset="0x18.0" size="0x0.2" />
	<field name="ap_sel_override_value" descr="Application Select from the applications list advertised by the module. Up \;to 15 applications available.\;\;Values range from 1 to 15.\;\;Note: application can be set with default SI values defined by the module \;or SI defined by the host" access="RW" offset="0x18.8" size="0x0.4" />
	<field name="si_override_cntrl" descr="Valid only for CMIS (QSFP-DD / SFP-DD / OSFP) compliant modules.\;If not CMIS module ignore field.\;Module Signal Integrity override control:\;0 - Auto (default)\;1 - Override with Module&apos;s Default applications SI values\;2 - Override with Hosts SI values" access="RW" offset="0x18.24" size="0x0.2" />
</node>

<node name="pmlp_reg_ext" descr="" size="0x40.0" >
	<field name="width" descr="0: unmap_local_port\;1: x1 - lane 0 is used\;2: x2 - lanes 0,1 are used\;4: x4 - lanes 0,1,2 and 3 are used\;8: x8 - lanes 0-7 are used\;\;Other - reserved" access="RW" enum="unmap_local_port=0x0,x1=0x1,x2=0x2,x4=0x4,x8=0x8" offset="0x0.0" size="0x0.8" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="m_lane_m" descr="Module lane mapping: \;0 - Local to Module mapping include module lanes mapping\;1 - Local to Module mapping only, without lane mapping\;\;When this operational is set (&apos;1&apos;), the following fields are ignored in SET \;command and should return the value &quot;0&quot; in GET commands: \;PMLP.rxtx\;PMLP.lane&lt;i&gt;_module_mapping.tx_lane\;PMLP.lane&lt;i&gt;_module_mapping.rx_lane" access="OP" offset="0x0.28" size="0x0.1" />
	<field name="rxtx" descr="Use different configuration for RX and TX.\;If this bit is cleared, the TX value is used for both RX and TX. When set, \;the RX configuration is taken from the separate field. This is to enable \;backward compatible implementation." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="lane0_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="lane1_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="lane2_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="lane3_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="lane4_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="lane5_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="lane6_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="lane7_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDeses in a module can be mapped to a local port. \;" access="RW" offset="0x20.0" size="0x4.0" />
</node>

<node name="pmmp_reg_ext" descr="" size="0x28.0" >
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="eeprom_override" descr="Override/ignore EEPROM advertisement properties bitmask: \;Bit 0 - Override cable protocols and technology for QSFP\;Bit 1 - Override cable protocols and technology for SFP\;Bit 2- Ignore Power Class (set high power)\;Bit 3- Override Cable Length \;Bit 4- Override Attenuation\;\;Bit 8 - Set Module to Low Power\;\;" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="eeprom_override_mask" descr="Write Mask bit (negative polarity):\;0 - allow write\;1 - ignore write\;On write commands, indicates which of the bits from eeprom_override \;field are updated.\;Reserved on read operations." access="WO" offset="0x4.16" size="0x0.16" />
	<field name="qsfp_cable_protocol_technology" descr="Valid only when the protocols and technology is overridden as indicated by \;eeprom_override\;See Table  1042, &quot;PMMP - QSFP Protocol Bytes Override Layout,&quot; on \;page  1254" access="RW" high_bound="2" low_bound="0" offset="0x8.0" size="0xc.0" />
	<field name="sfp_cable_protocol_technology" descr="Valid only when the protocols and technology is overridden as indicated by \;eeprom_override\;See Table  1044, &quot;PMMP - SFP Protocol Bytes Override Layout,&quot; on \;page  1256" access="RW" high_bound="2" low_bound="0" offset="0x14.0" size="0xc.0" />
	<field name="cable_length" descr="Length of cable assembly, units of 1 m.\;Valid only when the cable length is overridden as indicated by \;eeprom_override." access="RW" offset="0x20.0" size="0x0.8" />
	<field name="attenuation_5g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x24.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 7GHz in db." access="RW" offset="0x24.8" size="0x0.8" />
	<field name="attenuation_12g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 12GHz in db." access="RW" offset="0x24.16" size="0x0.8" />
	<field name="attenuation_25g" descr="Valid only when the attenuation is overridden as indicated by \;eeprom_override.\;Attenuation - total channel attenuation @ 25GHz in db." access="RW" offset="0x24.24" size="0x0.8" />
</node>

<node name="pmpc_reg_ext" descr="" size="0x20.0" >
	<field name="module_state_updated" descr="On read operation:\;A bit vector where each bit represents a module (bit 0 represents module 0 \;etc). A set bit indicates one or more changes in the module state (plugged/\;unplugged) has happened since the last time the bit was cleared. The \;default is 1 in all relevant bits.\;On write operation:\;Used to clear the module_status_updated bits. Writing a set bit clears the \;relevant bit in the module_status_updated vector. Cleared bits in this field \;preserve the value of the relevant bit in the bit vector. The software cannot \;set a bit in the module_status_updated vector.\;Note: To prevent a case where an update is missed by the software, it is \;recommended to use the flow below:\;Read the module_status_updated vector\;Find a bit(s) relevant to a module(s) the software would like to handle\;Clear the relevant bit(s)\;Handle the module (e.g. read the module parameters using MCIA reg\;ister)\;Read module_status_updated again to make sure the status did not change \;after reading the cable information." access="RW" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="pmpe_reg_ext" descr="" size="0x10.0" >
	<field name="module_status" descr="Port operational state:1- plugged, enabled\;2- unplugged\;3- module plugged, error (details in error_type) \;4- plugged, disabled" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="error_type" descr="Module error details:\;0x0: Power_Budget_Exceeded\;0x1: Long_Range_for_non_MLNX_cable_or_module\;0x2: Bus_stuck - (I2C Data or clock shorted)\;0x3: bad_or_unsupported_EEPROM\;0x4: Enforce_part_number_list\;0x5: unsupported_cable\;0x6: High_Temperature\;0x7: bad_cable - (Module/Cable is shorted)\;0x8: PMD_type_is_not_enabled - (see PMTPS).\;0xc: pcie_system_power_slot_Exceeded\;Valid only when (oper_status = 0x3)." access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc" offset="0x4.8" size="0x0.4" />
</node>

<node name="pmpr_reg_ext" descr="" size="0x10.0" >
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA \;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="attenuation_5g" descr="Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Attenuation - total channel attenuation @ 7GHz in db. \;A 0 value implies that attenuation_5g is used also for 7GHz" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="attenuation_12g" descr="Attenuation - total channel attenuation @ 12GHz in db.\;A 0 value implies that attenuation_5g is used also for 12GHz" access="RW" offset="0xC.0" size="0x0.8" />
</node>

<node name="pmtu_reg_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="max_mtu" descr="Maximum MTU supported on the port (Read Only).\;MTU depends on the port type. When port type (Eth/IB/FC) is configured, \;the relevant MTU is reported. When the port type is not configured, the \;minimum between the max_mtu for the different types (Eth/IB/FC) is \;reported." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="admin_mtu" descr="Administratively configured MTU on the port. Must be smaller or equal to \;max_mtu." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="oper_mtu" descr="Operational MTU. This is the actual MTU configured on the ports. Packets \;exceeding this size will be dropped.\;Note: In Ethernet or FC, oper_mtu is equal to admin_mtu. In InfiniBand, \;the actual operational MTU is reported which may be smaller than admin\;_mtu." access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="ppad_reg_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="If single_base_mac = 0 - base MAC address, \;For Spectrum mac[5:0] is reserved.\;For Spectrum-2 mac[6:0] is reserved.\;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Port number\;Reserved when single_base_mac = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="single_base_mac" descr="0 - base_mac, local_port should be 0 and mac[6:0]and mac \;[5:0] are reserved in Spectrum-2 and Spectrum-1 accor\;dantly.HW will set incremental \;1 - single_mac - mac of the local_port\;Reserved for SwitchX/-2." access="OP" offset="0x0.28" size="0x0.1" />
	<field name="mac_31_0" descr="If single_base_mac = 0 - base MAC address, \;For Spectrum mac[5:0] is reserved.\;For Spectrum-2 mac[6:0] is reserved.\;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="ppaos_reg_ext" descr="" size="0x10.0" >
	<field name="phy_test_mode_status" descr="Port extended down status:\;0: regular_operation - (port down/up according to PAOS) \;1: phy_test_mode\;phy test mode can be valid only when PAOS.admin_status=2 and \;PAOS.oper_status=2 (i.e port is down)." access="RO" enum="regular_operation=0x0,phy_test_mode=0x1" offset="0x0.0" size="0x0.4" />
	<field name="phy_test_mode_admin" descr="Port extended administrative down status:\;0: regular_operation (port down/up according to PAOS) \;1: phy_test_mode \;\;The phy test mode (1) can be set only when PAOS.admin_sta\;tus=2 (i.e port configuration is down)." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the router port. \;In this case, the swid indicates which of the router ports to config\;ure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="ppbmc_reg_ext" descr="" size="0x10.0" >
	<field name="monitor_type" descr="Monitor type based on monitor_cntl setting and the operational \;mode of the link:\;0 - Post FEC / No FEC BER monitoring\;1 - Pre FEC BER monitoring" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_state" descr="The monitor state of the port:\;0 - No BER Monitor support\;1 - Normal\;2 - Warning\;3 - Alarm\;\;* The init monitor state for each port upon link up is normal" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="monitor_cntl" descr="Bitmask - monitor options:\;Bit 0 - Pre FEC monitor: \;When set, a link with FEC active will monitor Pre-FEC BER.\;When cleared, link with FEC active will monitor Post-FEC (effec\;tive) BER.\;When FEC is not active, will monitor only effective BER." access="RW" offset="0x4.16" size="0x0.4" />
	<field name="event_ctrl" descr="Bitmask - event generation on operational state change:\;Bit 0 - Normal state\;Bit 1 - Warning state\;Bit 2 - Alarm state\;Bit 3 - Reserved\;\;Note: Normal state events can be generated only if either Alarm \;and/or Warning events are enabled." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="ievent" descr="Invoke event\;0: Read only\;1: Does both reading and invoke an event of type PPBME_TRAP\;\;Note: setting this field invokes an event, regardless to e and \;event_ctl fields, it has no effect on the event state." access="OP" offset="0x4.29" size="0x0.1" />
	<field name="e" descr="Event generation on operational state change:\;0 - Do not generate event\;1 - Generate Event \;2 - Generate Single Event\;Not Supported for HCA." access="RW" offset="0x4.30" size="0x0.2" />
</node>

<node name="ppbme_reg_ext" descr="" size="0x10.0" >
	<field name="monitor_type" descr="Monitor type based on monitor_options setting and the operational \;mode of the link:\;0 - Post FEC / No-FEC BER monitoring\;1 - Pre FEC BER monitoring" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0 - Lsocal port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_state" descr="The monitor state of the port:\;0 - No BER Monitor on the port\;1 - Normal\;2 - Warning\;3 - Alarm" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ievent" descr="Invoke event\;0: Read only\;1: Does both reading and invoke an event of type PPBME_TRAP\;\;Note: setting this field invokes an event, regardless to e and \;event_ctl fields, it has no effect on the event state." access="OP" offset="0x4.29" size="0x0.1" />
</node>

<node name="ppbmi_ext" descr="" size="0x14.0" >
	<field name="ilm_index" descr="ILM entry Index\;For Spectrum, the index points to the KVD Linear, see \;Section A.4.1.2, &quot;KVD Central Database Linear Entries,&quot; on \;page 2256" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="nhlfe_index" descr="NHLFE entry pointer\;Points to the NHLFE table. When using ECMP, points to the first \;entry in the ECMP list\;For Spectrum, the index is to the KVD linear, see Section A.4.1.2, \;&quot;KVD Central Database Linear Entries,&quot; on page 2256" access="RW" offset="0x8.0" size="0x0.24" />
	<field name="ecmp_size" descr="The amount of sequential entries starting from the nhlfe_ptr (the \;number of ECMPs)\;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096." access="RW" offset="0xC.0" size="0x0.13" />
	<field name="npop" descr="Number of labels to pop from the label stack.\;Range from 0 to cap_mpls_ilm_entry_pop" access="RW" offset="0xC.24" size="0x0.2" />
</node>

<node name="ppbmp_reg_ext" descr="" size="0x30.0" >
	<field name="monitor_group" descr="Monitor Parameters Group\;0x0: Pre-FEC BER monitor parameters for RS-FEC links\;0x1: Pre-FEC BER monitor parameters for FC-FEC links\;0x2: Effective BER (post FEC/NO-FEC) monitor parameters\;\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_parameters" descr="See Table 1223, &quot;PPBMP - Monitor Parameters Layout,&quot; on \;page 1424" subnode="uint64" access="RW" offset="0x4.0" size="0x8.0" />
</node>

<node name="ppbs_ext" descr="" size="0x1c.0" >
	<field name="type" descr="Entry type:\;0x0: Unicast_Record\;0x1: Unicast_LAG_Record\;0x2: Multicast_Record\;0xC: Unicast_Tunnel_Record\;0xF: Multicast_Tunnel_Record" access="RW" enum="Unicast_Record=0x0,Unicast_LAG_Record=0x1,Multicast_Record=0x2,Unicast_Tunnel_Record=0xc,Multicast_Tunnel_Record=0xf" offset="0x4.20" size="0x0.4" />
	<field name="swid" descr="Switch partition ID for queries. Reserved on Write.\;Reserved when Spectrum/-2" access="INDEX" offset="0x4.24" size="0x0.8" />
	<field name="pbs_ptr" descr="Index into the PBS table. \;In SwitchX/-2 pbs_ptr is limited to 0 .. (pbs_table_size-1)\;For Spectrum/-2, the index points to the KVD Linear, see Appendix \;A.4.1.2, &quot;KVD Central Database Linear Entries&quot; (page 2256)" access="INDEX" offset="0x8.0" size="0x0.24" />
	<field name="pbs_record" descr="PBS Record. For full description see:\;Table 1729, &quot;Unicast PBS Record Layout,&quot; on page 1717\;Table 1731, &quot;Unicast LAG PBS Record Layout,&quot; on page 1718\;Table 1733, &quot;Multicast PBS Record Layout,&quot; on page 1719\;Table 1735, &quot;Unicast Tunnel PBS Record Layout,&quot; on page 1720\;Table 1737, &quot;Multicast Tunnel PBS Record Layout,&quot; on page 1721" subnode="ppbs_pbs_record_auto_ext" access="RW" offset="0xC.0" size="0x10.0" union_selector="$(parent).type" />
</node>

<node name="ppbs_multicast_ext" descr="" size="0x8.0" >
	<field name="fid" descr="Filtering identifier (FID)\;Reserved when v_fid = 0\;Reserved when ubridge=1\;Reserved when Spectrum-2 \;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="pgi" descr="Multicast port group index - index into the Port Group Table.\;Value 0x1FFF indicates the pgi should point to the MID entry.\;For Spectrum/-2 this value must be set to 0x1FFF" access="RW" offset="0x0.16" size="0x0.13" />
	<field name="v_fid" descr="valid FID:\;0: .1Q bridge\;1: .1D bridge\;Reserved when ubridge=1\;Reserved when Spectrum-2\;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="mid" descr="Multicast port group index - index to the port group table." access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="ppbs_pbs_record_auto_ext" descr="" attr_is_union="1" size="0x10.0" >
	<field name="ppbs_unicast_ext" descr="" subnode="ppbs_unicast_ext" offset="0x0.0" selected_by="Unicast_Record" size="0x8.0" />
	<field name="unicast_lag_ext" descr="" subnode="unicast_lag_ext" offset="0x0.0" selected_by="Unicast_LAG_Record" size="0x8.0" />
	<field name="ppbs_multicast_ext" descr="" subnode="ppbs_multicast_ext" offset="0x0.0" selected_by="Multicast_Record" size="0x8.0" />
	<field name="unicast_tunnel_ext" descr="" subnode="unicast_tunnel_ext" offset="0x0.0" selected_by="Unicast_Tunnel_Record" size="0x10.0" />
	<field name="multicast_tunnel_ext" descr="" subnode="multicast_tunnel_ext" offset="0x0.0" selected_by="Multicast_Tunnel_Record" size="0x10.0" />
</node>

<node name="ppbs_unicast_ext" descr="" size="0x8.0" >
	<field name="fid" descr="Filtering identifier (FID)\;Reserved when v_fid = 0\;Reserved when ubridge=1\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="vid" descr="New VID when set_vid = 1\;Reserved when set_vid = 0\;Reserved when ubridge=0" access="RW" offset="0x0.16" size="0x0.12" />
	<field name="set_vid" descr="Set VID:\;0: do not update VID\;1: set VID\;For Spectrum-2 when set_vid=0 and smpe_valid=1 then the smpe \;will modify the vid\;Reserved when ubridge=0" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="v_fid" descr="valid FID:\;0: .1Q bridge, the VID is maintained\;1: .1D bridge, the VID is modified according to:\;{fid, system_port} -&gt; vid\;Where the mapping is according to SVFA register\;Reserved when ubridge=1" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="system_port" descr="Unique port identifier for the final destination of the packet\;Must be &apos;0&apos; when action is &apos;3&apos; - forward to IP router \;For SwitchX/-2 value of 0 is for drop\;Note: for Spectrum/-2, if action is 0 (forward) and system_port is 0 \;then the PPBS entry must not be used! (Must not be pointed by an \;ACL action)" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="action" descr="Action to apply on the packet:\;0: NOP - forward (based on the system_port destination)\;3: FORWARD_TO_IP_ROUTER\;4: FORWARD_TO_FCF - Reserved when Spectrum/-2\;5: DISCARD - Reserved when Spectrum/-2\;15: DISCARD_ERROR" access="RW" enum="NOP=0x0,FORWARD_TO_IP_ROUTER=0x3,FORWARD_TO_FCF=0x4,DISCARD=0x5,DISCARD_ERROR=0xf" offset="0x4.28" size="0x0.4" />
</node>

<node name="ppbt_ext" descr="" size="0x14.0" >
	<field name="local_port" descr="Local port \;Not including CPU port\;\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="op" descr="0: Bind ACL to Port\;1: Unbind ACL from Port (default)" access="RW" offset="0x0.28" size="0x0.3" />
	<field name="e" descr="0: iACL\;1: eACL" access="INDEX" enum="iACL=0x0,eACL=0x1" offset="0x0.31" size="0x0.1" />
	<field name="acl_id_group_id" descr="When g=0:\;ACL identifier (acl_id)\;Range of acl id is 0..cap_max_acl_regions-1\;When g=1:\;ACL group identifier (acl_group_id)\;Range of group id is 0..cap_max_acl_groups-1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="g" descr="group\;0: bind an ACL\;1: bind an ACL group\;Must be set to 1 for Spectrum/-2" access="RW" offset="0x10.31" size="0x0.1" />
</node>

<node name="ppcnt_plr_counters_ext" descr="" size="0xf8.0" >
	<field name="plr_rcv_codes_high" descr="Number of received PLR codewords\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="plr_rcv_codes_low" descr="Number of received PLR codewords\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="plr_rcv_code_err_high" descr="The total number of bad codewords received (including \;uncorrectable)." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="plr_rcv_code_err_low" descr="The total number of bad codewords received (including \;uncorrectable)." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="plr_rcv_uncorrectable_code_high" descr="The number of uncorrectable codewords received\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="plr_rcv_uncorrectable_code_low" descr="The number of uncorrectable codewords received\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="plr_xmit_codes_high" descr="Number of transmitted PLR codewords" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="plr_xmit_codes_low" descr="Number of transmitted PLR codewords" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_high" descr="The total number of codewords retransmitted." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_low" descr="The total number of codewords retransmitted." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_high" descr="The total number of retransmitted event. \;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_low" descr="The total number of retransmitted event. \;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="plr_sync_events_high" descr="The number of sync events" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="plr_sync_events_low" descr="The number of sync events" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="hi_retransmission_rate_high" descr="High retransmission rate\;The number of the retransmission rate has crossed the \;retransmission rate threshold\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="hi_retransmission_rate_low" descr="High retransmission rate\;The number of the retransmission rate has crossed the \;retransmission rate threshold\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_within_t_sec_max_high" descr="The maximum number of retransmitted events in t sec \;window\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="plr_xmit_retry_codes_within_t_sec_max_low" descr="The maximum number of retransmitted events in t sec \;window\;" access="RO" offset="0x44.0" size="0x4.0" />
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
</node>

<node name="ppcnt_reg_ext" descr="" size="0x100.0" >
	<field name="grp" descr="Performance counter group.\;Group 63 indicates all groups (include all per priority/TC/Receive Buffer \;counters). Only valid on Set() operation with clr bit set.\;0x0: IEEE_802_3_Counters\;0x1: RFC_2863_Counters\;0x2: RFC_2819_Counters\;0x3: RFC_3635_Counters\;0x5: Ethernet_Extended_Counters\;0x6: Ethernet_Discard_Counters \;0x8: Link_Level_Retransmission_Counters - [Internal]\;0x10: Per_Priority_Counters - \;0x11: Per_Traffic_Class_Counters - \;0x12: Physical_Layer_Counters\;0x13: Per_Traffic_Class_Congestion_Counters\;0x15: Per_Receive_Buffer_Counters - [Internal]\;0x16: Physical_Layer_Statistical_Counters\;0x19: Out_of_Band_Port_Counters - Note: This group is valid only for \;OOB ports - [Internal]\;0x20: InfiniBand_Port_Counters\;0x21: InfiniBand_Extended_Port_Counters\;0x22: PLR_counters_group\;0x23: RS_FEC_Histogram_group - [Internal] \;0x24: USR_XSR_Physical_layer_counters_group - [Internal]\;" access="INDEX" enum="IEEE_802_3_Counters=0x0,RFC_2863_Counters=0x1,RFC_2819_Counters=0x2,RFC_3635_Counters=0x3,Ethernet_Extended_Counters=0x5,Ethernet_Discard_Counters=0x6,Link_Level_Retransmission_Counters=0x8,Per_Priority_Counters=0x10,Per_Traffic_Class_Counters=0x11,Physical_Layer_Counters=0x12,Per_Traffic_Class_Congestion_Counters=0x13,Per_Receive_Buffer_Counters=0x15,Physical_Layer_Statistical_Counters=0x16,Out_of_Band_Port_Counters=0x19,InfiniBand_Port_Counters=0x20,InfiniBand_Extended_Port_Counters=0x21,PLR_counters_group=0x22,RS_FEC_Histogram_group=0x23,USR_XSR_Physical_layer_counters_group=0x24" offset="0x0.0" size="0x0.6" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;1: IB_port_number\;2: host_port_number\;3: OOB_port_number - Internal\;\;Note - pnat=2 is supported for &quot;Per Traffic Class Congestion Counters&quot; and \;&quot;Per Traffic Class Counters&quot; groups." access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,host_port_number=0x2,OOB_port_number=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number. \;255 indicates all ports on the device, and is only allowed for Set() operation." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must be always 0.\;Switch partition ID to associate port with.\;Switch partitions are numbered from 0 to 7 inclusively.\;Switch partition 254 indicates stacking ports.\;Switch partition 255 indicates all switch partitions.\;Only valid on Set() operation with local_port=255." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="prio_tc" descr="Priority index for per priority counter sets, valid values: 0-7\;For Spectrum-2 and on at tx side range can be 0 .. cap_max_tclass_data-1, \;see QGCR.tx_cnt_tclass\;\;Traffic class index for per traffic class counter set, valid values: \;For Switches, valid values: 0 .. cap_max_tclass_data-1 \;\;For HCA, valid values: 0.. HCA_CAP.max_tc\;\;Otherwise must be 0." access="INDEX" offset="0x4.0" size="0x0.5" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for all counters \;in the counter group. This bit can be set for both Set() and Get() operation.\;\;" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;See Table  992, &quot;Ethernet IEEE 802.3 Counters Group Data Layout,&quot; on \;page  1200\;See Table  994, &quot;Ethernet RFC 2863 Counter Group Data Layout,&quot; on \;page  1204\;See Table  996, &quot;Ethernet RFC 2819 Counter Group Data Layout,&quot; on \;page  1207\;See Table  998, &quot;Ethernet RFC 3635 Counter Group Data Layout,&quot; on \;page  1211\;See Table  1000, &quot;Ethernet Extended Counter Group Data Layout,&quot; on \;page  1214\;See Table  1003, &quot;Ethernet Discard Counter Group Fields,&quot; on page  1218\;See Table  1014, &quot;Link Level Retransmission Counter Group Data Layout,&quot; \;on page  1227\;See Table  1004, &quot;Ethernet Per Priority Group Data Layout,&quot; on page  1220\;See Table  1008, &quot;Ethernet Per Traffic Class Group data layout,&quot; on \;page  1226\;See Table  1020, &quot;Physical Layer Counters Data Layout,&quot; on page  1234\;See Table  1010, &quot;Ethernet Per Traffic Class Congestion Group data layout,&quot; \;on page  1226\;See Table  1012, &quot;Ethernet Per Receive Buffer Group data layout,&quot; on \;page  1227\;See Table  1024, &quot;Physical Layer Statistical Counters Data Layout,&quot; on \;page  1241 \;See Table  1006, &quot;Ethernet OOB Port Counters Data Layout,&quot; on page  1223 \;- [Internal]\;See Table  1016, &quot;InfiniBand PortCounters Attribute Group Data Layout,&quot; \;on page  1228\;See Table  1018, &quot;InfiniBand Extended PortCounters Attribute Group Data \;Layout,&quot; on page  1230\;See Table  1026, &quot;PLR Counters Data Layout,&quot; on page  1244 - [Internal]\;See Table  1028, &quot;RS-Histograms Data Layout,&quot; on page  1246 - [Internal] \;See Table  1022, &quot;USR_XSR Physical Layer Counters Data Layout,&quot; on \;page  1238" subnode="ppcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="ppcnt_rs_fec_histograms_counters_ext" descr="" size="0xf8.0" >
	<field name="hist" descr="Value of RS-hist" subnode="uint64" access="RO" high_bound="15" low_bound="0" offset="0x0.0" size="0x80.0" />
</node>

<node name="pplm_reg_ext" descr="" size="0x40.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fec_mode_active" descr="Active FEC (bitmask)\;0: No_FEC\;1: Firecode_FEC\;2: Standard_RS_FEC - RS(528,514)\;3: Standard_LL_RS-FEC - RS(271,257)\;4: Mellanox_Strong_RS-FEC - RS(277,257) [Internal]\;5: Mellanox_LL_RS-FEC - RS(163,155) [Internal] \;6: Reserved - [Internal]\;7: Standard_RS-FEC - (544,514)\;8: Zero_Latency_FEC - [Internal] \;9: Ethernet_Consortium_LL_50G_RS-FEC - (272,257+1)\;12: RS-FEC - (544,514)\;13: LL-FEC - (271,257)" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS=0x3,Mellanox_Strong_RS=0x4,Mellanox_LL_RS=0x5,Reserved=0x6,Standard_RS=0x7,Zero_Latency_FEC=0x8,Ethernet_Consortium_LL_50G_RS=0x9,RS=0xc,LL=0xd" offset="0xC.0" size="0x0.24" />
	<field name="fec_override_cap_10g_40g" descr="10GE/40GE Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: Reserved2\;3: Reserved3" access="RO" enum="No=0x0,Firecode_FEC=0x1,Reserved2=0x2,Reserved3=0x3" offset="0x10.0" size="0x0.4" />
	<field name="fec_override_cap_25g" descr="25GE Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: RS-FEC\;3: Reserved" access="RO" enum="No=0x0,Firecode_FEC=0x1,RS=0x2,Reserved=0x3" offset="0x10.4" size="0x0.4" />
	<field name="fec_override_cap_50g" descr="50GE (2 lanes) Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: RS-FEC\;3: Reserved" access="RO" enum="No=0x0,Firecode_FEC=0x1,RS=0x2,Reserved=0x3" offset="0x10.8" size="0x0.4" />
	<field name="fec_override_cap_100g" descr="100GE (4 lanes) Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Reserved1\;2: RS-FEC - (528,514)\;3: Reserved3" access="RO" enum="No=0x0,Reserved1=0x1,RS=0x2,Reserved3=0x3" offset="0x10.12" size="0x0.4" />
	<field name="fec_override_cap_56g" descr="56GE Ethernet FEC override capability bitmask:\;0: No-FEC\;1: Firecode_FEC\;2: Reserved2\;3: Reserved3" access="RO" enum="No=0x0,Firecode_FEC=0x1,Reserved2=0x2,Reserved3=0x3" offset="0x10.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_cap" descr="RS-FEC correction bypass override capability:\;0: NO_correction_bypass\;1: RS-FEC_correction_bypass" access="RO" enum="NO_correction_bypass=0x0,RS=0x1" offset="0x10.28" size="0x0.4" />
	<field name="fec_override_admin_10g_40g" descr="10GE/40GE Ethernet FEC override admin, see 10g_40g_fec_override_cap.\;(one-hot setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC" access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.0" size="0x0.4" />
	<field name="fec_override_admin_25g" descr="25GE Ethernet FEC override admin, see 25g_fec_override_cap. (one-hot \;setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC\;4: RS-FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_admin must be set \;with the same value." access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2,RS=0x4" offset="0x14.4" size="0x0.4" />
	<field name="fec_override_admin_50g" descr="50GE Ethernet FEC override admin, see 50g_fec_override_cap. (one-hot \;setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC\;4: RS-FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_admin must be set \;with the same value." access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2,RS=0x4" offset="0x14.8" size="0x0.4" />
	<field name="fec_override_admin_100g" descr="100GE Ethernet FEC override admin, see 100g_fec_override_cap. (one-hot \;setting): \;0: auto_mode - no override\;1: No_FEC\;4: RS-FEC" access="RW" enum="auto_mode=0x0,No_FEC=0x1,RS=0x4" offset="0x14.12" size="0x0.4" />
	<field name="fec_override_admin_56g" descr="56GE Ethernet FEC override admin, see 56g_fec_override_cap. (one-hot \;setting): \;0: auto_mode - no override\;1: No_FEC\;2: Firecode_FEC" access="RW" enum="auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_admin" descr="RS-FEC correction bypass override admin: (one-hot setting): \;0: auto_mode - no override \;1: NO_correction_bypass\;2: RS-FEC_correction_bypass" access="RW" enum="auto_mode=0x0,NO_correction_bypass=0x1,RS=0x2" offset="0x14.28" size="0x0.4" />
	<field name="fec_override_cap_200g_4x" descr="200GE FEC override capability bitmask:\;Bit 0 - Reserved \;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved \;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium LL RS-FEC (272,257+1)\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;[Internal] Bit 14 - ELL (272,257+1) + PLR\;" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="fec_override_cap_400g_8x" descr="400GE FEC override capability bitmask:\;Bit 0 - Reserved \;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved\;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium LL RS-FEC (272,257+1)\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;[Internal] Bit 14 - ELL (272,257+1) + PLR\;" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="fec_override_cap_50g_1x" descr="50GE single lane override capability bitmask:\;Bit 0 - Reserved \;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved \;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium LL RS-FEC (272,257+1)\;[Internal] Bit 12 - RS-FEC - (544,514) + PLR\;[Internal] Bit 13 - LL-FEC - (271,257) + PLR\;[Internal] Bit 14 - ELL - (272,257+1) + PLR" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="fec_override_cap_100g_2x" descr="100GE over 2 lanes, FEC override capability bitmask:\;Bit 0 - No-FEC\;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- Reserved \;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 9- 50G Ethernet Consortium Low Latency RS-FEC (272,257+1)\;[Internal] Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR\;[Internal] Bit 14 - ELL (272,257+1) + PLR\;" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="fec_override_admin_200g_4x" descr="200GE FEC override admin bitmask (one-hot setting) \;0: Auto_mode\;7: RS-FEC - (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;Bit 9 is set - RS-FEC (272,257+1)\;[Internal] Bit 12 is set - RS-FEC (544,514) + PLR\;[Internal] Bit 13 is set - LL-FEC (271,257) + PLR \;[Internal] Bit 14 is set - LL-FEC (272,257+1) + PLR" access="RW" offset="0x20.0" size="0x0.16" />
	<field name="fec_override_admin_400g_8x" descr="400GE FEC override admin bitmast (one-hot setting): \;0: Auto_mode\;7: RS-FEC_(544,514)\;8: Zero_Latency_FEC \;9: RS-FEC_(272,257+1)\;12: RS-FEC_(544,514) - + PLR [Internal]\;13: LL-FEC_(271,257) - + PLR [Internal]\;14: LL-FEC_(272,257+1) - + PLR [Internal]" access="RW" offset="0x20.16" size="0x0.16" />
	<field name="fec_override_admin_50g_1x" descr="50GE, 1lanes FEC override admin bitmask (one-hot setting)\;0 - Auto mode\;Bit 0 is set - NO-FEC \;Bit 1 is set - FC-FEC\;Bit 2 is set - RS-FEC (528,514)\;Bit 7 is set- RS-FEC (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;Bit 9 is set - RS-FEC (272,257+1)\;[Internal] Bit 12 is set - RS-FEC (544,514) + PLR\;[Internal] Bit 13 is set - LL-FEC (271,257) + PLR \;[Internal] Bit 14 is set - LL-FEC (272,257+1) + PLR" access="RW" offset="0x24.0" size="0x0.16" />
	<field name="fec_override_admin_100g_2x" descr="100GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 0 is set - Reserved\;Bit 2 is set - Reserved \;Bit 7 is set- RS-FEC (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;Bit 9 is set - RS-FEC (272,257+1)\;[Internal] Bit 12 is set - RS-FEC (544,514) + PLR\;[Internal] Bit 13 is set - LL-FEC (271,257) + PLR \;[Internal] Bit 14 is set - LL-FEC (272,257+1) + PLR" access="RW" offset="0x24.16" size="0x0.16" />
	<field name="ib_fec_override_cap_edr" descr="EDR FEC override capability bitmask:\;Bit 0 - No-FEC \;Bit 1- Reserved\;Bit 2- RS-FEC (528,514)\;Bit 3- LL-FEC (271,257)\;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;[Internal]Bit 12 - RS-FEC (544,514) + PLR\;[Internal] Bit 13 - LL-FEC (271,257) + PLR" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="ib_fec_override_cap_hdr" descr="HDR FEC override capability bitmask:\;Bit 0 - No-FEC \;Bit 1- Reserved \;Bit 2- Reserved \;Bit 3- LL-FEC (271,257)\;Bit 4- Reserved\;Bit 5- Reserved\;Bit 6- Reserved\;Bit 7 - RS-FEC (544,514)\;[Internal] Bit 8 - Zero Latency FEC\;Bit 12 - RS-FEC (544,514) + PLR\;Bit 13 - LL-FEC (271,257) + PLR" access="RO" offset="0x30.16" size="0x0.16" />
	<field name="ib_fec_override_cap_fdr10" descr="FDR FEC10 override capability bitmask:\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2-15: Reserved" access="RO" offset="0x34.0" size="0x0.16" />
	<field name="ib_fec_override_cap_fdr" descr="FDR FEC override capability bitmask:\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2-15: Reserved" access="RO" offset="0x34.16" size="0x0.16" />
	<field name="ib_fec_override_admin_edr" descr="EDR FEC override admin bitmask:\;0 - Auto mode\;Bit 0 is set - No FEC\;Bit 4 is set- LL-FEC (271,257)\;Bit 7 is set- RS-FEC (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;[Internal] Bit 12 is set - RS-FEC (544,514) + PLR\;[Internal] Bit 13 is set - LL-FEC (271,257) + PLR" access="RW" offset="0x38.0" size="0x0.16" />
	<field name="ib_fec_override_admin_hdr" descr="HDR FEC override admin bitmask:\;0 - Auto mode\;Bit 0 is set - No FEC\;Bit 4 is set- LL-FEC (271,257)\;Bit 7 is set- RS-FEC (544,514)\;[Internal] Bit 8 is set - Zero Latency FEC \;Bit 12 is set - RS-FEC (544,514) + PLR\;Bit 13 is set - LL-FEC (271,257) + PLR" access="RW" offset="0x38.16" size="0x0.16" />
	<field name="ib_fec_override_admin_fdr10" descr="FDR FEC override admin bitmask:\;0:Auto_mode\;1: No_FEC\;2: Firecode_FEC" access="RW" enum="Auto_mode=0x0,No_FEC=0x1,Firecode_FEC=0x2" offset="0x3C.0" size="0x0.16" />
	<field name="ib_fec_override_admin_fdr" descr="FDR FEC override admin bitmask:\;0: Auto_mode\;1: No_FEC\;2: Firecode_FEC" access="RW" offset="0x3C.16" size="0x0.16" />
</node>

<node name="pplr_reg_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lb_en" descr="Loopback enable - bitmask.\;See lb_cap bits description." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="lb_cap" descr="Loopback capability - bitmask\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback - When set the port&apos;s egress traffic is looped \;back to the receiver and the port transmitter is disabled.\;Bit 2: External_local_loopback - Enables the port&apos;s transmitter to link with \;the port&apos;s receiver using an external loopback connector.\;\;\;Note: Phy remote loopback can be supported only for lane rate higher than \;25Gbuad." access="RO" offset="0x4.16" size="0x0.8" />
</node>

<node name="pprr_ext" descr="" size="0x14.0" >
	<field name="register_index" descr="Index of Port Range Register being accessed\;Range is 0 .. cap_max_acl_l4_port_range-1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="ip_length" descr="Apply range comparators to:\;0: L4_PORT - the range is applied to l4 port. Default\;1: IP_LENGTH - The range is applied to IP Length. \;For Spectrum-1: when set, these fields must be set to 0: udp, tcp, \;src, dst. For Spectrum-2: these fields can be used\;2: TTL. outer TTL (IP or MPLS). port_range_min[15:8] and \;port_range_max[15:8] are reserved. Reserved when Spectrum-1. \;Reserved when outer_inner is INNER\;3: CUSTOM_BYTE_SET. Custom byte set is according to cbset. \;Reserved when Spectrum-1. Reserved when outer_inner is INNER\;4: ING_LOCAL_PORT_USER_MEM. Rsvd when Spectrum-1.\;5: UTC_29_14. UTC bits 29:14. Reserved when Spectrum-1.\;15: None - comparator resulat is &apos;0&apos;. Reserved when Spectrum-1.\;Reserved when outer_inner is INNER\;Applies to both inner and outer depending on outer_inner field\;Reserved when SwitchX/-2" access="RW" offset="0x0.16" size="0x0.4" />
	<field name="outer_inner" descr="0: OUTER - Apply port range register to outer IP header\;1: INNER - Apply port range register to inner IP header, Reserved \;when SwitchX/-2, supported by Spectrum/-2\;2: BOTH - Apply port range register to outer IP header or to inner \;IP header, Reserved when SwitchX/-2, and for Spectrum-2" access="RW" offset="0x0.22" size="0x0.2" />
	<field name="ignore_l4" descr="Ignore L4. Apply port range register regardless of L4. When set tcp \;and udp are reserved. Default 0.\;Must not be set when ip_length points to layer 4 fields.\;Reserved when SwitchX/-2 or Spectrum-1" access="RW" offset="0x0.24" size="0x0.1" />
	<field name="ignore_l3" descr="Ignore L3. Apply port range register regardless of L3. When set \;ipv4 and ipv6 are reserved. Default 0.\;Must not be set when ip_length points to layer 3 fields.\;Reserved when SwitchX/-2 or Spectrum-1" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="udp" descr="Apply port range register to UDP packets\;Default 0" access="RW" offset="0x0.26" size="0x0.1" />
	<field name="tcp" descr="Apply port range register to TCP packets\;Default 0" access="RW" offset="0x0.27" size="0x0.1" />
	<field name="dst" descr="Apply port range register to destination L4 ports\;Default 0" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="src" descr="Apply port range register to source L4 ports\;Default 0" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="ipv6" descr="Apply port range register to IPv6 packets\;Default 0" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="ipv4" descr="Apply port range register to IPv4 packets\;Default 0" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="port_range_max" descr="Maximum port range for comparison" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="port_range_min" descr="Minimum port range for comparison.\;Match is defined as: \;port_range_min &lt;= packet_port &lt;= port_range_max" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="cbset" descr="Custom Bytes Set\;Range 0 .. cap_max_custom_byte_sets-1See encoding in \;Table 1215, &quot;Spectrum-1 Custom Bytes Sets,&quot; on page 1361\;Note: at a given time no more than 2 cbsets can be used (for differ\;ent register_index values)\;Reserved when ip_length != CUSTOM_BYTE_SET\;Reserved when SwitchX/-2 and Spectrum-1\;" access="RW" offset="0x10.0" size="0x0.8" />
</node>

<node name="pprt_reg_ext" descr="" size="0x20.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPRT configu\;rations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on \;lane index" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)\;Physical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="p_c" descr="PRBS RX polarity support indication\;if this bit is cleared - bit 28 (&apos;p&apos;) is been ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS RX polarity - NOT gate in PRBS (not Physical lane Polar\;ity)\;0 - No polarity inversion.\;1 - PRBS RX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="tun_ovr" descr="[Internal]: If set to &apos;1&apos;, the value in tuning_type field will over\;ride the default adaptation flow (BER Bath for IB and XOR for \;Eth), which is set automatically when tun_ovr is &apos;0&apos;." access="OP" offset="0x0.29" size="0x0.1" />
	<field name="s" descr="start tuning:\;1 - start RX_tuning based on PRBS pattern \;Note: assuming peer transmitting PRBS. \;cannot be set when prbs_rx_tuning_status = 1 (during tuning)" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS RX is disabled.\;1 - PRBS RX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave : Non error based tune\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding \;2 - PAM4 with precoding\;3 - PAM4 without gray no precoding" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave : Non error based tune \;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - XAUI/2.5GE (3.125 Gb/s)\;Bit 3- DDR (5 Gb/s) \;Bit 4- QDR (10 Gb/s) \;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) \;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s) \;" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_oper" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s)\;1 - DDR (5 Gb/s) \;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s)\;4 - FDR (14.0625 Gb/s) \;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s\;7 - 9 - reserved\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s) \;\;Note: All lanes must be set to the same rate" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="prbs_lock_status_ext" descr="PRBS lock on PRBS pattern status for lanes 7-4: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status \;will return to 0 (Not locked)" access="RO" offset="0x14.20" size="0x0.4" />
	<field name="prbs_lock_status" descr="PRBS lock on PRBS pattern status for lanes 3-0: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status \;will return to 0 (Not locked)" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="prbs_rx_tuning_status" descr="Tuning status: \;0 - PRBS mode tuning was not performed.\;1 - Performing PRBS mode tuning.\;2 - PRBS mode tuning completed.\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status \;will return to 0." access="RO" offset="0x14.28" size="0x0.4" />
</node>

<node name="ppsc_reg_ext" descr="" size="0x30.0" >
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mod_pwr_opt" descr="See PCAM.feature_cap_mask bit 16 for support indication: \;Transceiver power optimization:\;0 - Disable\;1 - Enable" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="wrps_admin" descr="Width reduction power save admin state:\;0000: Disable Width Reduction - Force link to full width (Default)\;0001: Force Width Reduction - Force link to single lane\;0010: Auto - Automatic Width Reduction (based on traffic)." access="RW" offset="0x10.0" size="0x0.4" />
	<field name="wrps_status" descr="Link actual width:\;0000: Full width\;0001: Single lane\;1111: In transition" access="RO" offset="0x14.0" size="0x0.4" />
	<field name="down_threshold" descr="Link width down threshold, Values: 1%-100%\;The BW (In percent) before the link width is moved to single lane" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="up_threshold" descr="Link width up threshold, Values: 1-5 (default 3)\;how aggressive/smoothed in response to high BW.\;1 - means aggressive response to every BW increase\;5 - means smoothened response to every BW increase" access="RW" offset="0x18.16" size="0x0.8" />
	<field name="down_th_vld" descr="Valid bit to update the down threshold\;if &apos;1&apos; update down_threshold" access="WO" offset="0x18.30" size="0x0.1" />
	<field name="up_th_vld" descr="Valid bit to update the up threshold\;if &apos;1&apos; update up_threshold" access="WO" offset="0x18.31" size="0x0.1" />
	<field name="srps_admin" descr="Speed reduction power save admin state:\;0000: Disable Speed Reduction - force link to full speed (Default)\;0001: Force Speed Reduction - force link to low speed" access="RW" offset="0x20.0" size="0x0.4" />
</node>

<node name="pptb_reg_ext" descr="" size="0x10.0" >
	<field name="pm" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="um" descr="untagged_buff mask - enables update of the untagged_buff field.\;Reserved for Spectrum.\;Reserved for HCA devices." access="WO" offset="0x0.8" size="0x0.1" />
	<field name="cm" descr="ctrl_buff mask - enables update of the ctrl_buff field.\;NOTE: This field is ignored by the device, and control traffic is mapped \;to a pre-defined buffer (buffer - 9).\;In some old implementations (on SwitchX and SwitchX-2) software is \;required to use the value 9 in this field, later devices ignore this field.\;Reserved for HCA devices" access="WO" offset="0x0.9" size="0x0.1" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mm" descr="Mapping mode\;0 - Mapping both Unicast and Multicast packets to the same buffer\;In get operation, 0 means Unicast only.\;1 - Mapping Unicast only\;2 - Mapping Multicast only\;This field is reserved for HCA devices" access="INDEX" offset="0x0.28" size="0x0.2" />
	<field name="prio0buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="prio1buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="prio2buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="prio3buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.12" size="0x0.4" />
	<field name="prio4buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="prio5buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="prio6buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.24" size="0x0.4" />
	<field name="prio7buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.28" size="0x0.4" />
	<field name="untagged_buff" descr="Mapping of untagged frames to one of the allocated receive port buffers.\;NOTE: In SwitchX/-2, this field must be mapped to a buffer 8.\;\;Reserved for Spectrum. Spectrum maps untagged packets based on the \;Switch Priority.\;Reserved for HCA devices" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="ctrl_buff" descr="Mapping of control frames to one of the allocated receive port buffers.\;NOTE: This field is ignored by the device, and control traffic is mapped \;to a pre-defined buffer (buffer - 9).\;In some old implementations (on SwitchX and SwitchX-2), software is \;required to use the value 9 in this field, later devices ignore this field.\;Reserved for HCA devices" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="pm_msb" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i+8.\;Reserved for HCA device" access="WO" offset="0x8.24" size="0x0.8" />
	<field name="prio8buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="prio9buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.4" size="0x0.4" />
	<field name="prio10buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.8" size="0x0.4" />
	<field name="prio11buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.12" size="0x0.4" />
	<field name="prio12buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.16" size="0x0.4" />
	<field name="prio13buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.20" size="0x0.4" />
	<field name="prio14buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.24" size="0x0.4" />
	<field name="prio15buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port \;buffers.\;&lt;X&gt; = 8..15\;" access="RW" offset="0xC.28" size="0x0.4" />
</node>

<node name="pptt_reg_ext" descr="" size="0x1c.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPTT configu\;rations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on \;lane index" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support/capability: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)\;Physical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0 - Local port number\;1 - IB / label port number\;[Internal] 3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="p_c" descr="PRBS TX polarity support indication.\;if this bit is cleared - bit 28 (&apos;p&apos;) is been ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS TX polarity - NOT gate in PRBS (not Physical lane Polar\;ity)\;0 - No polarity inversion.\;1 - PRBS TX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS TX is disabled.\;1 - PRBS TX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_waveA (8 ones , 8 zeros)\;Bit 14 - Square_waveB (4 ones , 4zeros)\;Bit 15 - Square_waveC (2 ones , 2zeros)\;Bit 16 - Square_waveD (one , zero)\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding \;2 - PAM4 with precoding" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_waveA (8 ones , 8 zeros)\;0xE - Square_waveB (4 ones , 4zeros)\;0xF - Square_waveC (2 ones , 2zeros)\;0x10 - Square_waveD (one , zero)\;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - XAUI/2.5GE (3.125 Gb/s)\;Bit 3- DDR (5 Gb/s) \;Bit 4- QDR (10 Gb/s) \;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) \;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s)" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s)\;1 - DDR (5 Gb/s) \;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/40GE (10.3125 Gb/s)\;4 - FDR (14.0625 Gb/s) \;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / \;53.125Gb/s)\;7- 9 - reserved\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s)\;\;Note: All lanes must be set to the same rate" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="prbt_ext" descr="" size="0x14.0" >
	<field name="rif" descr="Router Interface Index - a pointer to the Router Interface Table.\;Range is 0.. cap_max_router_interfaces-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="op" descr="0: Bind ACL to Routing Interface\;1: Unbind ACL from Routing Interface (default)" access="RW" offset="0x0.28" size="0x0.3" />
	<field name="e" descr="0: iACL\;1: eACL" access="INDEX" enum="iACL=0x0,eACL=0x1" offset="0x0.31" size="0x0.1" />
	<field name="acl_id_group_id" descr="When g=0:\;ACL identifier (acl_id)\;Range of acl id is 0..cap_max_acl_regions-1\;When g=1:\;ACL group identifier (acl_group_id)\;Range of group id is 0..cap_max_acl_groups-1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="g" descr="group\;0: bind an ACL\;1: bind an ACL group\;Must be set to 1 for Spectrum/-2" access="RW" offset="0x10.31" size="0x0.1" />
</node>

<node name="prcr_ext" descr="" size="0x40.0" >
	<field name="offset" descr="Offset within the source region to copy/move from" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="op" descr="Operation:\;0: Move rules\;1: Copy rules \;Move/Copy the rules from tcan_region_info starting at offset off\;set to dest_tcam_region_info at offset dest_offset." access="OP" offset="0x0.28" size="0x0.4" />
	<field name="size" descr="The number of rules to copy/move" access="OP" offset="0x4.0" size="0x0.16" />
	<field name="tcam_region_info" descr="Opaque object that represents the source TCAM region.\;See Section 10.10.13, &quot;PTAR - Policy-Engine TCAM Allocation \;Register,&quot; on page 1680.\;See Table 1719, &quot;tcam_region_info Layout,&quot; on page 1710" subnode="tcam_region_info_prcr" access="INDEX" offset="0x10.0" size="0x10.0" />
	<field name="dest_offset" descr="Offset within the destination region to copy/move to" access="INDEX" offset="0x20.0" size="0x0.16" />
	<field name="dest_tcam_region_info" descr="Opaque object that represents the destination TCAM region.\;See Section 10.10.13, &quot;PTAR - Policy-Engine TCAM Allocation \;Register,&quot; on page 1680." access="INDEX" high_bound="3" low_bound="0" offset="0x30.0" size="0x10.0" />
</node>

<node name="prio_j" descr="" size="0x4.0" >
	<field name="color2" descr="The DSCP mapping for color k, where k=0..2, see Table 1857, \;&quot;color&lt;k&gt;Layout&quot;" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="color1" descr="The DSCP mapping for color k, where k=0..2, see Table 1857, \;&quot;color&lt;k&gt;Layout&quot;" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="color0" descr="The DSCP mapping for color k, where k=0..2, see Table 1857, \;&quot;color&lt;k&gt;Layout&quot;" access="RW" offset="0x0.24" size="0x0.8" />
</node>

<node name="prm_register_payload" descr="" size="0x100.0" >
	<field name="register_id" descr="Register ID" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="method" descr="0: Query\;1: Write" access="OP" offset="0x0.23" size="0x0.2" />
	<field name="register_data" descr="Register data" access="RW" high_bound="62" low_bound="0" offset="0x4.0" size="0xfc.0" />
</node>

<node name="pspa_reg_ext" descr="" size="0x8.0" >
	<field name="sub_port" descr="Reserved for Spectrum/Switch-IB/2.\;\;Virtual port within the physical port. \;0 - when virtual ports are not enabled on the port." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="Switch partition ID with which to associate {port, sub_port}.\;Switch partitions are numbered from 0 to 7 inclusively.\;Switch partition 254 indicates stacking port.\;Switch partition 255 indicates a disabled port." access="RW" offset="0x0.24" size="0x0.8" />
</node>

<node name="ptar_ext" descr="" size="0x30.0" >
	<field name="key_type" descr="TCAM key type for the region.\;See Table 1220, &quot;ACL Keys Summary,&quot; on page 1368 for list of \;supported key types.\;\;" access="WO" offset="0x0.0" size="0x0.8" />
	<field name="action_set_type" descr="Type of action set to be used on this region.\;For SwitchX/-2: See Table 1551, &quot;ACL Actions-Set Summary,&quot; \;on page 1586.\;For Spectrum/-2: always &apos;2&apos; Flexible Action Set" access="WO" offset="0x0.16" size="0x0.8" />
	<field name="e" descr="Egress\;0: egress ACL\;1: ingress ACL\;Reserved when Spectrum/-2 since direction is not relevant for \;allocation" access="WO" offset="0x0.27" size="0x0.1" />
	<field name="op" descr="For Write operation\;0: ALLOCATE a TCAM region\;1: RESIZE a TCAM region\;2: DEALLOACTE TCAM region\;3: TEST allocation\;The RESIZE and TEST have no significance for the A-TCAM \;which does not need to allocate a region size\;" access="RW" offset="0x0.28" size="0x0.4" />
	<field name="region_size" descr="TCAM region size. \;For op = ALLOCATE or op = RESIZE or op = TEST: this field is \;set by SW and the device returns the actual allocated size.\;Note that actual size may be larger than requested.\;Allowed range 1 .. cap_max_rules-1\;Reserved when op = DEALLOCATE\;For Spectrum-2: The region_size is relevant only for C-TCAM. \;Value of 0 is for no C-TCAM." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="region_id" descr="Region identifier\;Range 0 .. cap_max_regions-1" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="packet_rate" descr="TCAM region expected packet rate performance.\;Granularity is of 5%\;Reserved when Spectrum-2\;\;" access="WO" offset="0xC.0" size="0x0.5" />
	<field name="op_type" descr="Optimization Type\;0: No optimization\;1: Soft optimization\;2: Hard optimization\;Reserved when op is 1 RESIZE and previous size is not 0 or when \;op is 2 (DEALLOACTE TCAM) or when op is 3 (TEST)\;\;\;\;\;" access="WO" offset="0xC.8" size="0x0.2" />
	<field name="ctcam_dup" descr="C-TCAM duplication:\;0: dup 1\;1: dup 2\;2: dup 4\;This field controls duplication according to op_type\;Reserved when op_type = 0\;Reserved when Spectrum-1" access="WO" offset="0xC.12" size="0x0.3" />
	<field name="tcam_region_info" descr="Opaque object that represents the TCAM region.\;For op = ALLOCATE: returned by the device.\;For op = RESIZE or op = DEALLOCATE: provided as input to \;the device.\;See Table 1683, &quot;tcam_region_info Layout,&quot; on page 1684\;\;" subnode="tcam_region_info_ptar" access="RW" offset="0x10.0" size="0x10.0" />
	<field name="flexible_key_id" descr="Identifier of the Flexible Key. \;For Spectrum-1: only valid if (key_type = FLEX_KEY) \;For Spectrum-2: only valid if (key_type = FLEX_KEY2)\;See Table 1685, &quot;flexible key Layout,&quot; on page 1685\;For Spectrum-1 and for C-TCAM: The key size will be rounded \;up to one of the following values: 32B, 64B, 96B (2, 4 or 6 key \;blocks)\;For Spectrum-2 A-TCAM: The key size will be rounded up to one \;of the following values: 16B, 32B, 64B, 96B (2, 4, 8 or 12 key \;blocks)\;Reserved when op = RESIZE or op = DEALLOCATE\;\;" access="WO" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
</node>

<node name="ptce_ext" descr="" size="0xf0.0" >
	<field name="offset" descr="Offset within the region to which to write." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="op" descr="Operation:\;For Write:\;0: WRITE_operation - Used to write a new entry to the table. All \;R/W fields are relevant for new entry. Activity bit is cleared for \;new entries\;1: UPDATE_action - Only action set will be updated.\;2: CLEAR_ACTIVITY - activity bit is cleared for the entry\;For Query:\;0: READ_operation\;1: CLEAR_ON_READ - on read operation. Used to read entry \;and clear Activity bit." access="OP" enum="READ_operation=0x0,CLEAR_ON_READ=0x1" offset="0x0.20" size="0x0.3" />
	<field name="a" descr="Activity. Set if a packet lookup has hit on the specific entry.\;To clear the a bit, use &quot;clear activity&quot; op or &quot;clear on read&quot; opera\;tion." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="v" descr="Valid." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tcam_region_info" descr="Opaque object that represents the TCAM region.\;\;See Table 1699, &quot;tcam_region_info Layout,&quot; on page 1695" subnode="tcam_region_info_ptce" access="INDEX" offset="0x10.0" size="0x10.0" />
	<field name="key" descr="ACL Key as described in Section 10.4, &quot;ACL Keys,&quot; on \;page 1368" access="RW" high_bound="15" low_bound="0" offset="0x20.0" size="0x40.0" />
	<field name="mask" descr="Bitmask in the same size as key. A bit that is set directs the TCAM \;to compare the corresponding bit in key. A bit that is clear directs \;the TCAM to ignore the corresponding bit in key." access="RW" high_bound="15" low_bound="0" offset="0x60.0" size="0x40.0" />
	<field name="action_set" descr="Action-set to perform when rule is matched as described in \;Section 10.7.10, &quot;ACL Action-Set,&quot; on page 1586.\;Must be zeroes padded if action set is shorter." access="RW" high_bound="15" low_bound="0" offset="0xA0.0" size="0x40.0" />
	<field name="asbind" descr="Action-set bind. Bind an ACL or ACL group to the action-set.\;The ACL/ACL group is indicated by the g field." access="RW" offset="0xE0.30" size="0x0.1" />
	<field name="term" descr="Terminate binding process." access="RW" offset="0xE0.31" size="0x0.1" />
	<field name="acl_id_group_id" descr="When g=0:\;ACL identifier (acl_id)\;Range of acl id is 0..cap_max_acl_regions-1\;When g=1:\;ACL group identifier (acl_group_id)\;Range of group id is 0..cap_max_acl_groups-1" access="RW" offset="0xE4.0" size="0x0.16" />
	<field name="e" descr="Egress indication. If this bit is set, the acl_id/acl_group_id is an \;egress ACL. If cleared, Ingress ACL." access="INDEX" offset="0xE4.30" size="0x0.1" />
	<field name="g" descr="Group. When set, the binding is of an ACL group. When cleared, \;the binding is of an ACL." access="RW" offset="0xE4.31" size="0x0.1" />
</node>

<node name="ptce_v2_ext" descr="" size="0x188.0" >
	<field name="offset" descr="Offset within the region to which to write." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="op" descr="Operation\;For Write:\;0: WRITE operation. Used to write a new entry to the table. All\;R/W fields are relevant for new entry. Activity bit is set for new\;entries - Note write with v = 0 will delete the entry\;1: UPDATE action. Only flexible_action_set and priority will be\;updated.\;2: CLEAR activity. Activity bit is cleared for the entry3: \;WRITE_CLEAR. Does WRITE with CLEAR activity For Query:\;0: READ operation.\;1: CLEAR_ON_READ on read operation. Used to read entry and\;clear Activity bit." access="RW" offset="0x0.20" size="0x0.3" />
	<field name="a" descr="Activity. Set if a packet lookup has hit on the specific entry.\;To clear the a bit, use &quot;clear activity&quot; op or &quot;clear on read&quot; opera\;tion\;Reserved when Spectrum-2" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="v" descr="Valid." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="priority" descr="Priority of the rule, higher values win\;For Spectrum-2 range is 1.. cap_kvd_size-1\;Note: priority does not have to be unique per rule\;Within a region, higher priority should have lower offset (no lim\;itation between regions in a multi-ACL)\;Reserved when SwitchX/-2 and Spectrum-1" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="tcam_region_info" descr="Opaque object that represents the TCAM region.\;See Table 1703, &quot;tcam_region_info Layout,&quot; on page 1697" subnode="tcam_region_info_ptce_v2" access="INDEX" offset="0x10.0" size="0x10.0" />
	<field name="flex_key_blocks" descr="ACL Keys\;For Spectrum-1: Flex keys, see Section 10.5.2, &quot;Flexible ACL \;Key Blocks Layout,&quot; on page 1405\;For Spectrum-2: Flex2 keys, see Section 10.6.2, &quot;Flex2 ACL Key \;Blocks Layout,&quot; on page 1475" access="RW" high_bound="23" low_bound="0" offset="0x20.0" size="0x60.0" />
	<field name="mask" descr="Mask, at the same size as key. per bit:\;0: TCAM will ignore the bit in key\;1: TCAM will compare the bit in key" access="RW" high_bound="23" low_bound="0" offset="0x80.0" size="0x60.0" />
	<field name="flexible_action_set" descr="according to: Section 10.8, &quot;Flexible ACL Action Set,&quot; on \;page 1592\;Spectrum-2: the flexible_action_set must be all NULL with a nex\;t_action_set_ptr" access="RW" high_bound="41" low_bound="0" offset="0xE0.0" size="0xa8.0" />
</node>

<node name="ptce_v3_ext" descr="" size="0xa4.0" >
	<field name="dup" descr="Insert the rule on duplicated regions\;0: 1 duplication\;1..16: dup duplications \;(values of 0 and 1 have the same meaning)" access="WO" offset="0x0.0" size="0x0.5" />
	<field name="op" descr="Operation\;For Write:\;0: WRITE operation. Used to write a new entry to the table. All R/\;W fields are relevant for new entry. Activity bit is set for new \;entries - Note write with v = 0 will delete the entry\;Note: WRITE must not be used if an entry exists!!! 1: UPDATE \;an existing rule. \;\;\;For Query:\;0: READ operation.\;" access="OP" offset="0x0.20" size="0x0.3" />
	<field name="v" descr="Valid" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="priority" descr="Priority of the rule, higher values win\;For Spectrum-2 range is 1.. cap_kvd_size-1\;Note: priority does not have to be unique per rule" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="tcam_region_info" descr="Opaque object that represents the TCAM region.\;(See Table 1707, &quot;tcam_region_info Layout,&quot; on page 1701)" subnode="tcam_region_info_ptce_v3" access="INDEX" offset="0x10.0" size="0x10.0" />
	<field name="flex2_key_blocks" descr="ACL Key as described in Section 10.6.2, &quot;Flex2 ACL Key Blocks \;Layout,&quot; on page 1475\;The key must be masked according to the ERP (if ERPs exist for \;the region) or according to master_mask (if no ERPs for the \;region)" access="INDEX" high_bound="23" low_bound="0" offset="0x20.0" size="0x60.0" />
	<field name="erp_id" descr="Erp ID" access="INDEX" offset="0x80.0" size="0x0.4" />
	<field name="delta_start" descr="Start point of delta value and mask\;Units of bits\;The value must not exceed (num_key_blocks * 36 - 8)\;E.g. for 12 key blocks, range is 0..424 (432 = 12*36-8)\;Reserved when delta_mask = 0\;" access="INDEX" offset="0x84.0" size="0x0.10" />
	<field name="delta_value" descr="Delta value\;Bits which are masked by delta_mask are reserved (must be 0)" access="INDEX" offset="0x88.0" size="0x0.8" />
	<field name="delta_mask" descr="Delta mask\;Per bit:\;0: ignore relevant bit in delta_value\;1: compare relevant bit in delta_value\;Delta mask must not be set for reserved field in the key blocks\;Note: no delta when no ERPs, thus for regions with PER\;ERP.erpt_pointer_valid=0 the delta_mask must be 0" access="INDEX" offset="0x88.16" size="0x0.8" />
	<field name="prune_vector" descr="Pruning vector relative to the PERPT.erp_id.\;Used for reducing lookups\;0: NEED - need to do a lookup on the erpt entry\;1: PRUNE - no need to do a lookup on the erpt entry\;May be modified by PEAPBL, PEAPBM\;Note: for Spectrum-2 a region with 8 key blocks must be set either \;to all 1&apos;s or all 0&apos;s" access="RW" offset="0x90.0" size="0x0.16" />
	<field name="prune_ctcam" descr="Pruning on C-TCAM. Used for reducing lookups\;0: NEED - need to do a lookup in the C-TCAM\;1: PRUNE - no need to do a lookup in the C-TCAM\;May be modified by PEAPBL, PEAPBM" access="RW" offset="0x94.31" size="0x0.1" />
	<field name="large_entry_key_id" descr="Large entry key ID\;A key for 12 Key block rules \;Reserved when the region has less than 12 key blocks\;Within a region: must be different for keys which have different 6 \;Key blocks msb (key blocks 6..11). Must be the same for key \;blocks which have common 6 Key blocks msb.\;Range 0 .. cap_max_pe_large_key_id- 1 \;\;Must not be updated by SW when op=UPDATE\;When op=UPDATE the large_entry_key_id must be identical to \;the value that already exists" access="RW" offset="0x98.0" size="0x0.24" />
	<field name="large_exists" descr="Large entry key ID exists\;Within this region:\;0: SINGLE: The large_entry_key_id is not currently in use\;For rule insert: the msb of the key will be added\;For rule delete: the msb of the key will be removed\;1: NON_SINGLE: The large_entry_key_id is currently in use\;For rule insert: the msb of the key will not be added\;For rule delete: the msb of the key will not be removed\;\;rule insert: op=WRITE with v=1\;rule delete: op=WRITE with v=0\;Reserved when op=UPDATE" access="WO" offset="0x98.31" size="0x0.1" />
	<field name="action_pointer" descr="Pointer to action, see PEFA\;Range is 0.. cap_max_kvd_action_sets - 1" access="RW" offset="0xA0.0" size="0x0.24" />
	<field name="paptr" descr="Partial action pointer, see PEFA\;0: pointer to full action pointer or to partial pointer 0\;1: pointer to partial pointer 1\;Note that &quot;full action set&quot; and &quot;partial action set, partial index 0&quot; \;have the same pointer but different indexes" access="RW" offset="0xA0.30" size="0x0.2" />
</node>

<node name="ptcead_ext" descr="" size="0x220.0" >
	<field name="offset" descr="Offset within the multicast forwarding table\;Must be N*32" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="op" descr="0: Read activity\;1: Read and clear activity" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="num_rec" descr="Number of records to read\;Range 1..4096" access="OP" offset="0x4.0" size="0x0.13" />
	<field name="tcam_region_info" descr="Opaque object that represents the TCAM region.\;See Table 1711, &quot;tcam_region_info Layout,&quot; on page 1704" subnode="tcam_region_info_ptcead" access="INDEX" offset="0x10.0" size="0x10.0" />
	<field name="activity_vector" descr="Activity per offset\;Line 20h bit 31 is for entry offset+4095\;Line 21C bit 0 is for entry offset+0\;Bits higher than num_rec are reserved\;Bits higher than region_size are reserved\;For non-valid offsets the activity is reserved" access="RO" high_bound="127" low_bound="0" offset="0x20.0" size="0x200.0" />
</node>

<node name="pter_phy_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate\;0 - No Error\;---- Physical Errors ----\;1 - Raw BER\;2 - Effective BER\;" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities \;Bit 0 - Raw BER\;Bit 1 - Effective BER\;\;\;\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection opertional status\;0x0 - No error injection\;0x1 - Performing error injection" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="ber_exp" descr="BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ber_mantissa" descr="BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="error_injection_time" descr="Duration in 10 msec the port will generate errors.\;Reading this field will return the time left for errors to inject in msec\;\;\;0x0000 indicates no generation of errors.\;When set to 0xFFFF - No decremental operation, meaning the errors will \;be injected continuously without stop condition.\;" access="RW" offset="0x4.12" size="0x0.16" />
</node>

<node name="pter_port_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate\;0 - No Error\;---- Port Errors ----\;1 - Corrupt data packet ICRC\;2 - Corrupt data packet VCRC\;4- Corrupt credit packet LPCRC" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities \;Bit 0- Corrupt data packet ICRC\;Bit 1- Corrupt data packet VCRC\;Bit 2- Corrupt credit packet LPCRC\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="error_count" descr="Error Count\;Number of times the port will generate the configured error.\;0 indicates not to generate error.\;Reading error_count will return the number of left errors to inject. When \;0, all requested errors has been injected." access="RW" offset="0x4.12" size="0x0.5" />
</node>

<node name="pter_reg_ext" descr="" size="0x20.0" >
	<field name="status" descr="Error injection status: \;0x0 -Good status\;0x2 - No available sources for Error injection\;0x3 - Error injection configuration when port is in non operational state \;(port is neither in UP or TEST MODE)\;0x4 - out of range BER setting" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB / label port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="error_page" descr="Error_page selection: \;0: Injection_of_Phy_Errors\;1: Injection_of_Port_Errors" access="INDEX" enum="Injection_of_Phy_Errors=0x0,Injection_of_Port_Errors=0x1" offset="0x0.24" size="0x0.4" />
	<field name="page_data" descr="error injection page data: \;See Table  1090, &quot;PTER- Port Transmit Errors Register Phy Level Layout,&quot; \;on page  1294\;See Table  1092, &quot;PTER- Port Transmit Errors Register Port Level Fields,&quot; \;on page  1295" subnode="pter_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x1c.0" union_selector="$(parent).error_page" />
</node>

<node name="pter_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="pter_phy_page_reg_ext" descr="" subnode="pter_phy_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Phy_Errors" size="0x1c.0" />
	<field name="pter_port_page_reg_ext" descr="" subnode="pter_port_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Port_Errors" size="0x1c.0" />
</node>

<node name="ptys_reg_ext" descr="" size="0x40.0" >
	<field name="proto_mask" descr="Protocol Mask. Indicates which of the protocol data is valid\;Bit 0: InfiniBand\;Bit 1: Reserved\;Bit 2: Ethernet" access="INDEX" enum="InfiniBand=0x1,Reserved=0x2,Ethernet=0x4" offset="0x0.0" size="0x0.3" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="force_tx_aba_param" descr="When AN is disabled, use aba TX set. \;" access="RW" offset="0x0.24" size="0x0.1" />
	<field name="an_disable_cap" descr="Auto Negotiation disable capability:\;0 - Device does not support AN disable\;1 - Device Supports  AN disable" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="an_disable_admin" descr="Auto Negotiation disable:\;0 - Normal operation \;1 - Disable AN.\;Note: In Ethernet port, when Disabling AN, the &quot;eth_proto_admin&quot; bit \;mask must comply to single speed rate set.\;In IB port, when Disabling AN, the &quot;ib_proto_admin&quot; bit mask must \;comply to single speed rate set.\;It&apos;s recommended to validate the FEC override bits in PPLM when operat\;ing with AN. \;\;" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="reserved_high" descr="THIS BIT MUST BE TIED TO 1!\;This is old capability bit that address AN_DISABLE capability with only \;one enabled protocol." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="data_rate_oper" descr="Port data rate in resolution of 100 Mb/s (data_rate_oper * 100 Mb/s)\;Value 0x0 indicates this field is not supported." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_port_rate" descr="Port maxium data rate in resolution of 1 Gb/s (data_rate_oper * 1 Gb/s)\;Value 0x0 indicates this field is not supported.\;" access="RO" offset="0x4.16" size="0x0.12" />
	<field name="an_status" descr="Auto Negotiation status: \;0 - Status is unavailable\;1 - AN completed successfully \;2 - AN performed but failed\;3 - AN was not performed, link is up \;4 - AN was not performed, link is down" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="ext_eth_proto_capability" descr="For HCA: See also PCAM.feature_cap_mask bit 13 for Extended Ether\;net protocol support.\;Extended Ethernet port speed/protocols supported (bitmask):\;Bit 0 - SGMII_100M\;Bit 1 - 1000BASE-X / SGMII\;Bit 3 - 5GBASE-R\;Bit 4 - XFI / XAUI-1 // 10G\;Bit 5 - XLAUI-4/XLPPI-4 // 40G \;Bit 6 - 25GAUI-1/ 25GBASE-CR / KR \;Bit 7 - 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 \;Bit 8 - 50GAUI-1 / LAUI-1/ 50GBASE-CR / KR\;Bit 9 - CAUI-4 / 100GBASE-CR4 / KR4\;Bit 10 - 100GAUI-2 / 100GBASE-CR2 / KR2 \;Bit 11 - 100GAUI-1 / 100GBASE-CR / KR\;Bit 12 - 200GAUI-4 / 200GBASE-CR4/KR4\;Bit 13 - 200GAUI-2 / 200GBASE-CR2/KR2\;Bit 14 - Reserved\;Bit 15 - 400GAUI-8\;Bit 16 - 400GAUI-4\;Other - Reserved" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="eth_proto_capability" descr="Ethernet port speed/protocols supported (bitmask)\;Bit 31 - 50GBase-KR2\;Bit 30 - 50GBase-CR2\;Bit 29 - 25GBase-SR\;Bit 28 - 25GBase-KR\;Bit 27 - 25GBase-CR\;[Internal] Bit 26 - 10GBase-T \;[Internal] Bit 25 - 1000Base-T\;[Internal] Bit 24 - 100Base-TX\;[Internal] Bit 23 - 100GBase LR4/ER4\;Bit 22 - 100GBase KR4\;Bit 21 - 100GBase SR4\;Bit 20 - 100GBase CR4\;Bit 19 - 50GBase-KR4\;Bit 18 - 50GBase-SR2Bit 16 - 40GBase LR4/ER4\;Bit 15 - 40GBase SR4\;Bit 14 - 10GBase ER/LR\;Bit 13 - 10GBase SR\;Bit 12 - 10GBase CR\;Bit 9 - SGMII_100Base\;[Internal] Bit 8 - 56GBase *R4\;Bit 7 - 40GBase KR4\;Bit 6 - 40GBase CR4\;[internal] Bit 5 - 20GBase-KR2\;Bit 4 - 10GBase KR\;Bit 3 - 10GBase KX4\;Bit 2 - 10GBase-CX4\;Bit 1 - 1000Base KX\;Bit 0 - SGMII" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ib_proto_capability" descr="InfiniBand port speed supported (bitmask)\;ib_link_speed &lt;= ib_proto_capability[7:0]\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80" offset="0x10.0" size="0x0.16" />
	<field name="ib_link_width_capability" descr="ib_link_width &lt;= ib_proto_capability\;Bit 0 - 1x\;Bit 1 - 2x\;Bit 2 - 4x\;Bit 3 - 8x\;Bit 4 - 12x" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="ext_eth_proto_admin" descr="Ethernet port extended speed/protocols bitmask\;NOTE: This field and &quot;eth_proto_admin&quot; are mutual exclusive, meaning \;that only one of the field can be set on write command." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="eth_proto_admin" descr="Ethernet port speed/protocols bitmask" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="ib_proto_admin" descr="InfiniBand port speed bitmask" access="RW" offset="0x1C.0" size="0x0.16" />
	<field name="ib_link_width_admin" descr="InfiniBand port link width bitmask\;" access="RW" offset="0x1C.16" size="0x0.16" />
	<field name="ext_eth_proto_oper" descr="Ethernet port extended speed/protocols bitmask" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="eth_proto_oper" descr="Ethernet port speed/protocols bitmask" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ib_proto_oper" descr="InfiniBand port speed bitmask" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="ib_link_width_oper" descr="InfiniBand port link width bitmask\;" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="connector_type" descr="Connector type indication\;0: No_connector_or_unknown \;1: PORT_NONE - None\;2: PORT_TP - Twisted Pair\;3: PORT_AUI - AUI\;4: PORT_BNC - BNC\;5: PORT_MII - MII\;6: PORT_FIBRE - FIBRE\;7: PORT_DA - Direct Attach Copper\;8: PORT_OTHER - Other" access="RO" enum="No_connector_or_unknown=0x0,PORT_NONE=0x1,PORT_TP=0x2,PORT_AUI=0x3,PORT_BNC=0x4,PORT_MII=0x5,PORT_FIBRE=0x6,PORT_DA=0x7,PORT_OTHER=0x8" offset="0x2C.0" size="0x0.4" />
	<field name="eth_proto_lp_advertise" descr="Ethernet port&apos;s link partner advertised protocols. Returns the protocols \;that were advertised by the link partner during auto-negotiation.\;" access="RO" offset="0x30.0" size="0x4.0" />
</node>

<node name="pude_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:\;0001 - up\;0010 - down\;0100 - down by port failure (transitioned by the hardware)\;" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):\;0001 - up\;0010 - down by configuration\;0011 - up once - if the port goes up and then down, the operational sta\;tus should go to &quot;down by port failure&quot; and can only go back up upon \;explicit command\;0100 - disabled by system" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must  always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;Switch partition 254 indicates stacking ports.\;Switch partition 255 indicates all switch partitions.\;Note: While external ports uses unique local port numbers (and thus swid is \;redundant), router ports use the same local port number where swid is the \;only indication for the relevant port." access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="puet_ext" descr="" size="0x10.0" >
	<field name="index" descr="Ethertype table index\;Each index represents a bit in the key ethertype_vector\;Value for writing: 5 or 6\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="ethertype" descr="Ethertype value for the specific table entry.\;Note: Some of the table entries hold a pre-defined default value and \;cannot be modified.\;index = 0: IPv4, 0x800(not configurable)\;index = 1: IPv6, 0x86DD (not configurable)\;index = 2: ARP and RARP, 0x806, 0x8035 (not configurable)\;index = 3: FCP (not configurable)\;index = 4: GRH (not configurable)\;index = 5: Default: TRILL, configurable\;index = 6: Default: InfiniBand GRH, configurableindex = 7: \;reserved (not configurable)" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="pvbt_ext" descr="" size="0x14.0" >
	<field name="vlan_group" descr="Vlan group\;Range is 0 .. cap_max_acl_vlan_groups-1" access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="op" descr="0: Bind ACL to VLAN group\;1: Unbind ACL from VLAN group (default)" access="RW" offset="0x0.20" size="0x0.3" />
	<field name="swid" descr="Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="acl_id_group_id" descr="When g=0:\;ACL identifier (acl_id)\;Range of acl id is 0..cap_max_acl_regions-1\;When g=1:\;ACL group identifier (acl_group_id)\;Range of group id is 0..cap_max_acl_groups-1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="g" descr="group\;0: bind an ACL\;1: bind an ACL group\;Must be set to 1 for Spectrum/-2" access="RW" offset="0x10.31" size="0x0.1" />
</node>

<node name="pvgt_ext" descr="" size="0x8.0" >
	<field name="vid" descr="VLAN ID" access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="op" descr="0: Bind VID to VLAN group\;1: Unbind VID from VLAN group (default)" access="WO" offset="0x0.20" size="0x0.3" />
	<field name="swid" descr="Switch partition ID" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="vlan_group" descr="VLAN group to which the VLAN will be added\;Range 0 .. cap_max_acl_vlan_groups-1\;Reserved on write when op = 1" access="RW" offset="0x4.0" size="0x0.12" />
</node>

<node name="pvlc_reg_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="vl_hw_cap" descr="Virtual Lanes supported on this port.\;0 - Reserved\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="vl_admin" descr="Virtual Lanes enabled by the local admin on this port.\;0: No change; valid only on Set()\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="vl_operational" descr="Operational VLs as configured by the SM on this port:\;0: No change; valid only on Set()\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14\;Changing vl_operational in certain PortStates may cause in flow control \;update errors which may initiate Link/PHY retraining.\;vl_operational value is valid only when link state is UP." access="RO" offset="0xC.0" size="0x0.4" />
</node>

<node name="qcam_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First 128 REG_ID" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index\;0: Enhanced features" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="qos_access_reg_cap_mask" descr="Supported QoS access register bitmasks. Based on \;access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: QCAP (0x4001)\;Bit 2: QPTS (0x4002)\;Bit 3: QDPM (0x4003)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="qos_feature_cap_mask" descr="Supported QoS enhanced features based on feature_group index.\;When bit is set, the feature is supported in the device\;Bit 0: QPTS_TRUST_BOTH - trust_both is supported in QPTS \;register" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="qcap_ext" descr="" size="0x14.0" >
	<field name="max_policers_per_port" descr="Maximum number of policers available per port" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="max_policers_global" descr="Maximum number of global policers" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="max_policers_cpu" descr="Maximum number of cpu policers" access="RO" offset="0x10.0" size="0x0.8" />
</node>

<node name="qdpm_ext" descr="" size="0x40.0" >
	<field name="dscp" descr="DSCP entry is the DSCP to Switch Priority mapping. For more \;details refer to Table 1801." access="RW" high_bound="63" low_bound="0" offset="0x0.24" size="0x40.0" />
</node>

<node name="qeec_ext" descr="" size="0x20.0" >
	<field name="local_port" descr="Local port number\;CPU port supported." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="element_index" descr="The index of the element in the hierarchy." access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="element_hierarchy" descr="The hierarchy of the element\;0: Port\;1: Group\;2: Sub_Group\;3: Traffic_Class" access="INDEX" enum="Port=0x0,Group=0x1,Sub_Group=0x2,Traffic_Class=0x3" offset="0x4.16" size="0x0.4" />
	<field name="next_element_index" descr="The index of the element in the lower hierarchy.\;reserved when element_heirarchy  &apos;0&apos;" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="min_shaper_rate" descr="Min shaper information rate\;For all hierarchies at Non-CPU port, and for port-hierarchy on CPU \;ports:\;bps mode, Units of 1000bps\;Granularity is 200mbps\;Error is up to 3% from configuration (for example: when rate is con\;figured to 200mbps, actual rate may be 206mbps)\;Reading reveals the actual rate (e.g. 206 in the above example)\;Note: for rates lower than 10,000bps or lower than 100 packets per \;sec, error is up to 10%\;Reserved when ptps = 1" access="RW" offset="0xC.0" size="0x0.28" />
	<field name="pb" descr="Packets or Bytes mode\;0: bytes mode\;1: packets mode\;Applies to both min shaper and max shaper\;For Spectrum family packets mode is supported only for TClasses \;of CPU port.\;Reserved when ptps = 1" access="RW" offset="0xC.28" size="0x0.1" />
	<field name="ptps" descr="PTP shaper\;0: regular shaper mode\;1: PTP oriented shaper\;Allowed only for hierarchy 0\;Not supported for CPU port\;Note that ptps mode may effect the shaper rates of all hierarchies\;Reserved when Spectrum-2\;\;" access="RW" offset="0xC.29" size="0x0.1" />
	<field name="mise" descr="Min shaper configuration enable. Enables configuration of \;min_shaper_rate, min_shaper_bs on this ETS element\;0: disable\;1: enable" access="RW" enum="disable=0x0,enable=0x1" offset="0xC.31" size="0x0.1" />
	<field name="max_shaper_rate" descr="Max shaper information rate\;For all hierarchies at Non-CPU port, and for port-hierarchy on CPU \;ports:\;bps mode, Units of 1000bps\;Granularity is 200mbps\;Error is up to 3% from configuration (for example: when rate is con\;figured to 200mbps, actual rate may be 206mbps)\;Reading reveals the actual rate (e.g. 206 in the above example)\;\;For Tclass of CPU ports:\;bps mode:\;- Granularity is 1000bps\;- Error is up to 1% from configuration\;packet per sec mode:\;- Granularity is 10 packet per sec\;- Error is up to 1% from configuration\;Note: for rates lower than 10,000bps or lower than 100 packets per \;sec, error is up to 10%\;Reserved when ptps = 1\;" access="RW" offset="0x10.0" size="0x0.31" />
	<field name="mase" descr="Max shaper configuration enable. Enables configuration of max\;_shaper_rate, max_shaper_bs on this ETS element\;0: disable\;1: enable" access="RW" enum="disable=0x0,enable=0x1" offset="0x10.31" size="0x0.1" />
	<field name="phantom_queue_rate" descr="Phantom queue rate\;Units of 1000bps, bps only\;Granularity is 200mbps\;Error is up to 3% from configuration (for example: at 100Gbps, rate \;is configured to 200mbps, actual rate may be 206mbps)\;ECN marking is done when the rate is above phantom_queue_rate\;For Spectrum family: When phantom queue is enabled then max \;shaper must be disabled. Disabling is done by setting the relevant \;rate to its max value. By default the phantom queue is disabled.\;Reserved when ptps = 1\;" access="RW" offset="0x14.0" size="0x0.31" />
	<field name="pqe" descr="Phantom queue configuration enable. Enables configuration of the \;phantom queue rate\;0: disable\;1: enable\;Allowed only for hierarchy 0\;Not supported for CPU port\;Reserved when ptps = 1" access="RW" offset="0x14.31" size="0x0.1" />
	<field name="dwrr_weight" descr="dwrr weight on the link going down from the ETS element:\;The percentage of bandwidth guaranteed to a ETS within its hierar\;chy.\;The sum of dwrr_weight value across all ETS elements within one \;hierarchy should equal 100.\;This field is reserved when dwrr is strict priority." access="RW" offset="0x18.0" size="0x0.8" />
	<field name="dwrr" descr="dwrr or strict priority on the link going down from the ETS element:\;0: strict priority\;1: DWRR" access="RW" offset="0x18.15" size="0x0.1" />
	<field name="de" descr="DWRR configuration enable. Enables configuration of the dwrr and \;dwrr_weight.\;0: disable\;1: enable" access="RW" offset="0x18.31" size="0x0.1" />
	<field name="max_shaper_bs" descr="Max shaper Burst size\;Burst size is 2^max_shaper_bs * 512 [bits]\;For Spectrum-1: Range is: 5..25\;For Spectrum-2: Range is: 11..25\;Value of 0 is configured as minimum\;Reserved when ptps = 1" access="RW" offset="0x1C.0" size="0x0.6" />
	<field name="min_shaper_bs" descr="Min shaper Burst size\;Burst size is 2^min_shaper_bs * 512 [bits]\;For Spectrum-1: Range is: 5..25\;For Spectrum-2: Range is: 11..25\;\;Value of 0 is configured as minimum\;Reserved when ptps = 1" access="RW" offset="0x1C.16" size="0x0.6" />
</node>

<node name="qegcs_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="abr_glob_sp" descr="Arbitration across groups:\;0: DWRR \;1: Strict Priority (default)" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="grp15_arb_sp" descr="Arbitration inside group 15:\;0: DWRR\;1: Strict Priority (default)\;Note that if grp07_arb_sp is configured to Strict Priority then\;grp15_arb_sp must be configured as Strict Priority as well" access="RW" offset="0x4.1" size="0x0.1" />
	<field name="grp07_arb_sp" descr="Arbitration inside groups 0..7: \;0: DWRR\;1: Strict Priority (default)" access="RW" offset="0x4.2" size="0x0.1" />
</node>

<node name="qepm_ext" descr="" size="0x14.0" >
	<field name="local_port" descr="Local port.\;Supported for data packets from CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="exp" descr="EXP entry is the EXP to Switch Priority mapping. For more \;details refer to Table 1809, &quot;exp&lt;i&gt; Layout,&quot; on page 1787" access="RW" high_bound="7" low_bound="0" offset="0x4.16" size="0x10.0" />
</node>

<node name="qetcr_ext" descr="" size="0x50.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="tc_configuration" descr="Per-tclass configuration. For details, refer to Table 1817, &quot;ETS \;tcN Configuration Register Layout&quot;." subnode="ets" access="RW" high_bound="7" low_bound="0" offset="0x8.0" size="0x40.0" />
	<field name="global_configuration" descr="Global configuration. For details, refer to Table 1819, &quot;ETS \;Global Configuration Register Layout&quot;.\;" subnode="ets_global" access="RW" offset="0x48.0" size="0x8.0" />
</node>

<node name="qgcr_ext" descr="" size="0x8.0" >
	<field name="tx_cnt_tclass" descr="Tx count Tclass:\;0: Tx count is by cnt priority as configured by QSPCP.tx_count\;ing_prio (default)\;1: Tx count is by Tclass, total of cap_max_tclass counters per port" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="qhll_ext" descr="" size="0xc.0" >
	<field name="local_port" descr="Local port\;No support for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="hll_time" descr="HLL Time\;HLL Time = 4.096uSec * 2^hll_time\;Default is 17 (0.54Sec)\;Range is 0 ..19\;Values of 20-31 means infinite (no HLL)" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="stall_cnt" descr="Stall count. Number of HLL discarded packets required to \;enter the Stall-State.\;Default is 7\;Range 1..7\;Reserved when stall_en = 0" access="RW" offset="0x8.0" size="0x0.3" />
	<field name="stall_en" descr="Stall enable\;0: Stall disabled\;1: Stall enabled (default)" access="RW" offset="0x8.31" size="0x0.1" />
</node>

<node name="qpbr_ext" descr="" size="0x10.0" >
	<field name="pid" descr="Policer ID.\;Global policers are numbered from 0 to cap_max_polic\;ers_per_port-1.\;Per port policers are numbered from 0 to cap_max_policers_\;global-1. \;Storm Control policers are numbered from 0 to cap_max_polic\;ers_storm_control-1" access="RW" offset="0x0.0" size="0x0.14" />
	<field name="g" descr="0: port policer and Storm Control policer configuration\;1: global policer configuration\;Reserved when Spectrum/-2" access="RW" offset="0x0.15" size="0x0.1" />
	<field name="local_port" descr="local_port number. The policer is assigned to traffic coming from \;the port. \;SwitchX/-2: Note that one can bind a global policer to a port, and \;use the same global policer to more than a single port.\;Spectrum family: Note that one can bind a Storm Control policer to \;a port.type, and use the same Storm Control policer to more than a \;single port.\;CPU port is not supported." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="op" descr="Operation:\;0: bind policer\;1: update policer binding (status id bind)\;2: unbind policer (For SwitchX/-2 only g and pid should be valid, \;for Spectrum family the unbinding uses the same indexes as bind\;ing)\;\;" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="uc" descr="For Port or Storm Control: Meter ingress unicast packets" access="INDEX" offset="0x4.0" size="0x0.1" />
	<field name="mc" descr="For Port or Storm Control: Meter ingress multicast packets" access="INDEX" offset="0x4.1" size="0x0.1" />
	<field name="bc" descr="For Port or Storm Control: Meter ingress broadcast packets" access="INDEX" offset="0x4.2" size="0x0.1" />
	<field name="uuc" descr="For Port or Storm Control: Meter ingress unknown unicast packets" access="INDEX" offset="0x4.3" size="0x0.1" />
	<field name="umc" descr="For Port or Storm Control: Meter ingress unknown multicast pack\;ets" access="INDEX" offset="0x4.4" size="0x0.1" />
</node>

<node name="qpcr_ext" descr="" size="0x28.0" >
	<field name="pid" descr="Policer ID.\;Global policers are numbered from 0 to cap_max_policers_\;global - 1.\;Per port policers are numbered from 0 to cap_max_polic\;ers_per_port - 1. \;Storm policers are numbered from 0 to cap_max_polic\;ers_storm_control -1\;For Spectrum family, a dual rate policer consumes 2 pids. A dual \;rate policer must have an even numbered pid." access="INDEX" offset="0x0.0" size="0x0.14" />
	<field name="g" descr="0: per port policer configuration, Reserved when Spectrum/-2\;2: global policer configuration\;3: storm control policer configuration\;For IB Switches must be global" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port. Relevant only for per port policers\;No support for CPU port.\;No support for router port.\;Editing of this field is not allowed for a bounded policer.\;Reserved when Spectrum family and for IB switches" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mode" descr="Operation Mode\;0: policer\;1: packet sampling\;Reserved when Spectrum family and when IB switches\;Editing of this field is not allowed for a bounded policer" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="type" descr="policer type:\;0: srTCM, single rate three colors marking. This mode is not \;supported by Spectrum family\;1: srDCM, single rate dual colors marking. This mode is not sup\;ported by SwitchX/-2\;2: trTCM, dual rate three colors marking. This mode is not sup\;ported by SwitchX/-2\;Editing of this field is not allowed for a bounded policer\;IB switches support only srDCM" access="RW" offset="0x4.8" size="0x0.2" />
	<field name="ir_units" descr="0: cir and eir use units of 10^6 bits/sec\;1: cir and eir use units of 10^3 bits/sec\;Reserved when mode = &apos;1&apos; packet sampling\;Reserved when SwitchX/-2 and when IB switches" access="OP" offset="0x4.12" size="0x0.1" />
	<field name="bytes" descr="0: meter based on packets/sec\;1: meter based on bytes/sec\;This field is reserved when mode = 1 (packet sampling)\;Editing of this field is not allowed for a bounded policer\;Reserved when IB switches (support only packets/sec)" access="RW" offset="0x4.14" size="0x0.1" />
	<field name="color_aware" descr="0: meter is not color aware\;1: meter is color aware\;Editing of this field is not allowed for a bounded policer\;Reserved when storm control policers\;Reserved when SwitchX/-2 and when IB switches" access="RW" offset="0x4.15" size="0x0.1" />
	<field name="add_counter" descr="Add value to counters. The counter on the pid will be added with \;the value of violate_count \;Reserved when SwitchX/-2 and when IB switches" access="OP" offset="0x4.30" size="0x0.1" />
	<field name="clear_counter" descr="Clear counters. Setting the clear_counter bit will reset the vio\;late_count of the pid \;Reserved when SwitchX/-2 and when IB switches" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="ebs" descr="Excessive burst size\;When bytes = 0: burst size is 2^ebs [packets]\;When bytes = 1: burst size is 2^ebs * 512 [bits]\;\;SwitchX/-2: range is from 64Mbit to 8Gbit.\;\;Spectrum family: Burst size is from (cir (for single rate) or eir \;(for double rate)) * rate * 50uSec to 32Gbit, for bytes = 0 rate is \;10^3 and for bytes = 1 rate is 10^3 or 10^6 according to ir_units. \;Also, ebs must always be larger than 3\;Reserved when type is srDCM" access="RW" offset="0x8.16" size="0x0.6" />
	<field name="cbs" descr="Committed burst size\;When bytes = 0: burst size is 2^cbs [packets]\;When bytes = 1: burst size is 2^cbs * 512 [bits]\;\;SwitchX/-2: range is from 64Mbit to 8Gbit.\;\;Spectrum family:\;When bytes = 1: Burst size is from cir * rate * 400uSec up to \;32Gbit, for bytes = 0 rate is 10^3 and for bytes = 1 rate is 10^3 or \;10^6 according to ir_units.\;When bytes = 0: Burst size is up to 2^26 packets\;Also, cbs must always be larger than 3\;\;[Internal] min rate for Spc-1 is *50uS\;\;Switch-IB/2 and Quantum: Range is 4.. 11 (16..2K Packets/Sec)\;Spectrum-1 when bits mode: Range is 4..25\;Spectrum-1 when packet mode: Range is 4..24\;Spectrum-2 and on when bits mode: Range is 4..31\;Spectrum-2 and on when packet mode: Range is 4..26\;\;When configured for packet sampling (mode=1), this field is \;used for range indicating the range of the uniform random. \;Range is in power of 2 packets. Random sampling will be uni\;form distribution in the following range: packet_rate - range : \;packet_rate + range" access="RW" offset="0x8.24" size="0x0.6" />
	<field name="cir" descr="Committed information rate.\;For Spectrum/-2: Resolution error is up to 1%.\;For bytes the units are according to ir_units.For packets meter\;ing CIR is in Packet/sec units.\;For SwitchX/-2: When configured for packet sampling, this field \;is used for packet_rate indicating the rate for packet sampling.\;\;Switch-IB/2: range: 6250, 8000, 12000, 15000, 20000, 50000, \;100000 packets/sec. HW will round to N*64. Resolution error is \;up to 10%.\;\;\;Quantum: range: 64 ... 100,000 packets/sec. HW will round to \;N*64. Resolution error is up to 1%.\;\;\;Note: Reading will provide the exact value used by the HW\;" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="eir" descr="Excess information rate. \;Resolution error is up to 1%. Reading will provide the exact \;value used by the HW.\;For bytes the units are according to ir_units.For packets meter\;ing CIR is in Packet/sec units.\;Reserved when type is srDCM\;" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="exceed_action" descr="Action for packets classified yellow by the policer (packets that \;exceed CBS but do not exceed EBS):\;0: forward - Not supported by Spectrum family.\;1: discard - Not supported by Spectrum family.\;2: forward_and_set_color_to_yellow - Reserved when SwitchX/\;-2.\;Editing of this field is not allowed for a bounded policer.\;Reserved when type is srDCM" access="RW" enum="forward=0x0,discard=0x1,forward_and_set_color_to_yellow=0x2" offset="0x14.0" size="0x0.4" />
	<field name="violate_action" descr="Action for packets classified Red by the policer (e.g. packets that \;exceed CBS when type is srDCM or exceed EBS when type is \;trTCM):\;0: forward - Not supported by Spectrum family.\;1: discard\;2: forward_and_set_color_to_red - No support by SwitchX/-2\;\;For Spectrum/-2 storm control policers the action must be dis\;card\;" access="RW" enum="forward=0x0,discard=0x1,forward_and_set_color_to_red=0x2" offset="0x18.0" size="0x0.4" />
	<field name="violate_count_high" descr="Counts the number of times violate_actions happened on this pid\;Reserved when SwitchX/-2 and when IB switches \;\;" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="violate_count_low" descr="Counts the number of times violate_actions happened on this pid\;Reserved when SwitchX/-2 and when IB switches \;\;" access="RW" offset="0x24.0" size="0x4.0" />
</node>

<node name="qpdp_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port.\;Supported for data packets from CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="switch_prio" descr="Default port Switch Priority (default 0)\;" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="color" descr="Default port color (default=0)\;0x0: GREEN\;0x1: YELLOW\;0x2: RED\;" access="RW" enum="GREEN=0x0,YELLOW=0x1,RED=0x2" offset="0x4.8" size="0x0.2" />
</node>

<node name="qpdpc_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port.\;No support for CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pcp" descr="Default port PCP (default 0)" access="RW" offset="0x4.0" size="0x0.3" />
	<field name="dei" descr="Default port DEI (default 0)\;Reserved when SwitchX/-2" access="RW" offset="0x4.8" size="0x0.1" />
</node>

<node name="qpdpm_ext" descr="" size="0x84.0" >
	<field name="local_port" descr="Local Port.\;Supported for data packets from CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dscp" descr="DSCP entry is the DSCP to Switch Priority mapping. For more \;details refer to Table 1805" access="RW" high_bound="63" low_bound="0" offset="0x4.16" size="0x80.0" />
</node>

<node name="qpdsm_ext" descr="" size="0x44.0" >
	<field name="local_port" descr="Local port.\;No support for CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="switch_prio" descr="The DSCP mapping for Switch Priority i, See Table 1855, \;&quot;switch_prio&lt;j&gt; Layout&quot;\;Switch Prio range is from 0 to cap_max_switch_priorities-1" subnode="prio_j" access="RW" high_bound="15" low_bound="0" offset="0x4.0" size="0x40.0" />
</node>

<node name="qpem_ext" descr="" size="0x104.0" >
	<field name="local_port" descr="Local port.\;No support for CPU port.\;No support for router port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="switch_prio" descr="The EXP mapping for Switch Priority i, See Table 1847, \;&quot;switch_prio&lt;i&gt; Layout&quot;\;Switch Prio range is from 0 to cap_max_switch_priorities-\;1" subnode="switch_prio" access="RW" high_bound="15" low_bound="0" offset="0x4.0" size="0x100.0" />
</node>

<node name="qppm_ext" descr="" size="0x44.0" >
	<field name="local_port" descr="Local port.\;No support for CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="switch_prio" descr="The PCP mapping for Switch Priority i, See Table 1861, \;&quot;switch_prio&lt;j&gt; Layout&quot;\;Switch Prio range is from 0 to cap_max_switch_priorities-1" subnode="switch_prio_j" access="RW" high_bound="15" low_bound="0" offset="0x4.0" size="0x40.0" />
</node>

<node name="qprt_ext" descr="" size="0x8.0" >
	<field name="pcp" descr="Packet&apos;s PCP value" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="dei" descr="Packet&apos;s DEI value.\;Reserved when SwitchX/-2" access="INDEX" offset="0x0.11" size="0x0.1" />
	<field name="local_port" descr="Local port.\;Supported for data packets from CPU port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rprio" descr="For SwitchX/-2: Regeneration Priority.\;For Spectrum family: Switch Priority\;The default value for the table is: PCP i -&gt;Regeneration Priority i\;" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="color" descr="Packet Color.\;0: GREEN\;1: YELLOW\;2: RED\;Not supported for SwitchX/-2\;" access="RW" enum="GREEN=0x0,YELLOW=0x1,RED=0x2" offset="0x4.8" size="0x0.2" />
</node>

<node name="qpts_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local Port\;CPU port supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="trust_state" descr="0: TRUST_PORT \;1: TRUST_PCP - default\;2: TRUST_DSCP - when MPLS trust EXP\;3: TRUST_BOTH" access="RW" enum="TRUST_PORT=0x0,TRUST_PCP=0x1,TRUST_DSCP=0x2,TRUST_BOTH=0x3" offset="0x4.0" size="0x0.3" />
</node>

<node name="qrwe_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port\;Supported for CPU port\;No support for router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pcp" descr="pcp_rewrite_enable:\;0: disable PCP and DEI rewrite, this is the default \;1: enable PCP and DEI rewrite" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="dscp" descr="dscp_rewrite_enable:\;0: disable DSCP rewrite, this is the default \;1: enable DSCP rewrite" access="RW" offset="0x4.1" size="0x0.1" />
	<field name="exp" descr="exp_rewrite_enable:\;0: disable EXP rewrite, this is the default \;1: enable EXP rewrite" access="RW" offset="0x4.2" size="0x0.1" />
</node>

<node name="qsll_ext" descr="" size="0x8.0" >
	<field name="sll_time" descr="SLL Time\;SLL Time = 4.096uSec * 2^sll_time\;Default is 20 (4.3Sec)Range is 3 ..30\;Value of 31 means infinite (no SLL)" access="RW" offset="0x4.0" size="0x0.5" />
</node>

<node name="qspcp_ext" descr="" size="0xc.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to Counting Priority.\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="local_port" descr="Local port\;No support for CPU port\;No support for router port\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rx_counting_prio" descr="The Rx Counting Priority value for the relevant Switch Priority \;value.\;default: \;for i=[0..7]: switch_prio i: rx_counting_prio i\;for i=[8..15]: switch_prio i: rx_counting_prio (i-8)" access="RW" offset="0x4.0" size="0x0.3" />
	<field name="tx_counting_prio" descr="The Tx Counting Priority value for the relevant Switch Priority \;value.\;default: \;for i=[0..7]: switch_prio i: tx_counting_prio i\;for i=[8..15]: switch_prio i: tx_counting_prio (i-8)\;[Spectrum2] This field is reserved when QGCR.tx_cnt_tclass is set" access="RW" offset="0x8.0" size="0x0.3" />
</node>

<node name="qspip_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority entry form mapping to IEEE Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="ieee_prio" descr="The new IEEE Priority value for the relevant Switch Priority value.\;default: \;for i=[0..7]: switch_prio i: ieee_prio i\;for i=[8..15]: switch_prio i: ieee_prio (i-8)\;Note: Different switch_prio values assigned to a given buffer (see \;PPTB) may be assigned to different ieee_prio values." access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="qsptc_ext" descr="" size="0x8.0" >
	<field name="itclass" descr="Received TClass" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="local_eport" descr="Local egress port number (must be stacking port)" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="local_iport" descr="Local ingress port number (must be stacking port)" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="tclass" descr="Regenerated stacking TClass for received packets on stacking port \;with TClass \;The default value for the Stacking Port TClass Regeneration Table \;is tclass[itclass=i]=i." access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="qstct_ext" descr="" size="0x10.0" >
	<field name="switch_prio" descr="Ingress Switch Priority" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="swid" descr="Switch partition ID" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="utclass" descr="Stacking TClass used for unicast packets with priority switch_prio.\;Default values are: \;- utclass[switch_prio=0]=1, \;- utclass[switch_prio=1]=0, \;- utclass[switch_prio=&lt;i&gt;]=i (for i&gt;1)." access="RW" offset="0x4.0" size="0x0.3" />
	<field name="mtclass" descr="Stacking TClass used for multicast packets with priority prio.\;Default values are: \;- mtclass[switch_prio=0]=1, \;- mtclass[switch_prio=1]=0, \;- mtclass[switch_prio=&lt;i&gt;]=i (for i&gt;1)." access="RW" offset="0x8.0" size="0x0.3" />
</node>

<node name="qtct_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Switch Priority" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="local_port" descr="Local port number (transmit port)\;No support for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cap_remote_admin" descr="For NIC only, Reserved when Switches" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="cap_local_admin" descr="For NIC only, Reserved when Switches" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="operation_type" descr="For NIC only, Reserved when Switches" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="tclass" descr="Traffic Class\;Default values are: \;- switch_prio=0: tclass=1 \;- switch_prio=1: tclass=0\;- switch_prio&gt;1: tclass = switch_prio\;\;When MC aware mode is enabled, setting values greater or equal \;to (cap_max_tclass_data)/2) is not allowed" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="qtctm_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port\;No support for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mc" descr="Multicast Mode\;0: NONE_MC_AWARE - Switch Priority to Traffic Class mapping \;is not based on Multicast packet indication (default)\;1: MC_AWARE - Switch Priority to Traffic Class mapping is based \;on Multicast packet indication" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="ralbu_ext" descr="" size="0x20.0" >
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="protocol" descr="Protocol\;0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="bin" descr="The LPM entries assigned to this bin may be updated." access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="old_bmp_len" descr="The value of the bmp_len field in the rules assigned to bin that \;would be replaced by new_bmp_len." access="INDEX" offset="0x4.16" size="0x0.8" />
	<field name="prefix_len" descr="The prefix length of the LPM route that was added/removed" access="INDEX" offset="0x8.0" size="0x0.8" />
	<field name="new_bmp_len" descr="The value of the bmp_len that would be written instead of the old\;_bmp_len" access="WO" offset="0x8.16" size="0x0.8" />
	<field name="ip" descr="This field is the prefix of the LPM route that was added/removed.. \;The field must be padded with zeros after the first prefix_len bits." access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
</node>

<node name="ralcm_ext" descr="" size="0x4.0" >
	<field name="protocol" descr="Protocol:\;0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers-1" access="INDEX" offset="0x0.16" size="0x0.16" />
</node>

<node name="raleu_ext" descr="" size="0x2c.0" >
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers-1\;Reserved when mvr = 1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="protocol" descr="Protocol\;0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="adjacency_index" descr="Adjacency Index used for matching on the existing entries.\;" access="INDEX" offset="0x10.0" size="0x0.24" />
	<field name="ecmp_size" descr="ECMP Size used for matching on the existing entries.\;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096." access="INDEX" offset="0x14.0" size="0x0.13" />
	<field name="new_adjacency_index" descr="New Adjacency Index. \;" access="WO" offset="0x20.0" size="0x0.24" />
	<field name="new_ecmp_size" descr="New ECMP Size. \;The valid range is:\;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096.\;" access="WO" offset="0x24.0" size="0x0.13" />
</node>

<node name="ralst_ext" descr="" size="0x104.0" >
	<field name="tree_id" descr="Tree identifier numbered from 1..(cap_shspm_max_trees-1)." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="root_bin" descr="The bin number of the root bin. \;0&lt;root_bin=&lt;(length of IP address)\;For a default-route tree configure 0xff" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="bin" descr="Holding the childs of the bin according to the stored tree&apos;s structure. \;The most significant byte is the bin&apos;s number of the left child and the \;least significant byte holds the right child. See Table 2053, &quot;bin Lay\;out,&quot; on page 2002. \;0xFF indicates that there is no child. For trees composed of less than \;4 blocks, the bins in excess are reserved.\;Note that tree_id 0 is allocated for a default-route tree, bins are 0xff" access="RW" high_bound="128" low_bound="1" offset="0x4.16" size="0x100.0" />
</node>

<node name="ralta_ext" descr="" size="0x4.0" >
	<field name="tree_id" descr="An identifier (numbered from 1..cap_shspm_max_trees-1) repre\;senting the tree identifier (managed by software).\;Note that tree_id 0 is allocated for a default-route tree" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="protocol" descr="Protocol:\;0: Unicast IPv4\;1: Unicast IPv6\;Reserved when op = 1 (deallocate a tree)." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="op" descr="opcode (valid for Write, must be 0 on Read)\;0: allocate a tree\;1: deallocate a tree" access="OP" offset="0x0.28" size="0x0.2" />
</node>

<node name="raltb_ext" descr="" size="0x4.0" >
	<field name="tree_id" descr="Tree to be used for the {virtual_router, protocol}\;Tree identifier numbered from 1..(cap_shspm_max_trees-1).\;By default, all Unicast IPv4 and IPv6 are bound to tree_id 0" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="protocol" descr="Protocol. \;0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers-1" access="INDEX" offset="0x0.16" size="0x0.16" />
</node>

<node name="ralue_ext" descr="" size="0x38.0" >
	<field name="a" descr="Activity. Set for new entries. Set if a packet lookup has hit on the \;specific entry, only if the entry is a route. To clear the a bit, use \;&quot;clear activity&quot; op.\;Enabled by activity_dis in RGCR, see Section 13.13.2, &quot;RGCR - \;Router General Configuration Register,&quot; on page 1897" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: Write operation. Used to write a new entry to the table. All RW \;fields are written for new entry. Activity bit is set for new entries.\;1: Update operation. Used to update an existing route entry and \;only update the RW fields that are detailed in the field op_u_mask. \;If entry doesn&apos;t exist, the operation fails.\;2: Clear activity. The activity bit (the field a) is cleared for the \;entry.\;3: Delete operation. Used to delete an existing entry. If entry \;doesn&apos;t exist, the operation fails.\;For Query:\;0: Read operation. If entry doesn&apos;t exist, the operation fails\;1: Clear on read operation. Used to read entry and clear Activity bit" access="OP" offset="0x0.20" size="0x0.3" />
	<field name="protocol" descr="0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="op_u_mask" descr="opcode update mask.\;On read operation, this field is reserved.\;This field is valid for update opcode, otherwise - reserved\;This field is a bitmask of the fields that should be updated\;bit0: entry_type\;bit1: bmp_len\;bit2: action_type and action fields\;bit3: counter_set_type and counter_set_index fields" access="WO" offset="0x4.8" size="0x0.4" />
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers-1" access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="prefix_len" descr="Number of bits in the prefix of the LPM route.\;Note that for IPv6 prefixes, if prefix_len&gt;64 the entry consumes \;two entries in the physical HW table" access="INDEX" offset="0x8.0" size="0x0.8" />
	<field name="dip" descr="The prefix of the route or of the marker that the object of the LPM \;is compared with. The most significant bits of the dip are the prefix. \;The least significant bits must be &apos;0&apos; if the prefix_len is smaller \;than 128 for IPv6 or smaller than 32 for IPv4.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="INDEX" high_bound="3" low_bound="0" offset="0xC.0" size="0x10.0" />
	<field name="action_type" descr="Action Type\;Indicates how the IP address is connected\;It can be connected to a local subnet through local_erif or can be on \;a remote subnet connected through a next-hop router, or transmitted \;to the CPU.\;0: REMOTE\;1: LOCAL\;2: IP2ME\;3: AR - Adaptive Routing, reserved when Spectrum-1\;\;\;Reserved when entry_type = MARKER_ENTRY" access="RW" enum="REMOTE=0x0,LOCAL=0x1,IP2ME=0x2" offset="0x1C.0" size="0x0.4" />
	<field name="bmp_len" descr="The best match prefix length in the case that there is no match for \;longer prefixes (see &quot;Introduction&quot; on page 1863). \;If (entry_type != MARKER_ENTRY), bmp_len must be equal to \;prefix_len\;Note: for any update operation with entry_type modification this \;field must be set" access="RW" offset="0x1C.16" size="0x0.8" />
	<field name="entry_type" descr="Entry Type\;1: MARKER_ENTRY\;2: ROUTE_ENTRY\;3: MARKER_AND_ROUTE_ENTRY\;Note - for Marker entries, the action_type and action fields are \;reserved" access="RW" offset="0x1C.30" size="0x0.2" />
	<field name="action" descr="The forwarding action as function of action_type:\;Section 13.13.26.1, &quot;RALUE Remote Action,&quot; on page 2007\;Section 13.13.26.2, &quot;RALUE Local Action,&quot; on page 2008\;Section 13.13.26.3, &quot;RALUE IP2ME Action,&quot; on page 2009\;Section 13.13.26.4, &quot;RALUE AR Action,&quot; on page 2010" access="RW" high_bound="4" low_bound="0" offset="0x20.0" size="0x14.0" />
	<field name="counter_index" descr="Counter Index for flow counters\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x34.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on page 623\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x34.24" size="0x0.8" />
</node>

<node name="rarcl_ext" descr="" size="0x2c.0" >
	<field name="tc_cong_level0" descr="Traffic Class congestion level threshold0\;Units of cells" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="tc_cong_level1" descr="Traffic Class congestion level threshold1\;Units of cells" access="RW" offset="0x14.0" size="0x0.24" />
	<field name="tc_cong_level2" descr="Traffic Class congestion level threshold2\;Units of cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="eport_cong_level0" descr="Egress ports congestion level threshold0\;Units of cells" access="RW" offset="0x20.0" size="0x0.24" />
	<field name="eport_cong_level1" descr="Egress ports congestion level threshold1\;Units of cells" access="RW" offset="0x24.0" size="0x0.24" />
	<field name="eport_cong_level2" descr="Egress ports congestion level threshold2\;Units of cells" access="RW" offset="0x28.0" size="0x0.24" />
</node>

<node name="rarctm_ext" descr="" size="0x8.0" >
	<field name="tclass" descr="Traffic Class\;Range 0.. cap_max_tclass_data-1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="local_port" descr="Egress local port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mapping" descr="Mapping:\;0: TC_ORIENTED\;1: PORT_ORIENTED" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="rarft_ext" descr="" size="0xc.0" >
	<field name="arft_index" descr="AR Flow Table Index \;Note: profile1 should be at RALUE.ar_flow_table_size after pro\;file0\;Pointer to PGT table" access="INDEX" offset="0x0.0" size="0x0.20" />
	<field name="arft_entry_in_row" descr="Index to entry in the arft row\;Range 0..  cap_max_arft_entries_in_row-1" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="local_port" descr="Egress local_port\;SW may set an entry. HW may change the entry.\;Valid when valid = &quot;1&quot;\;Note: In normal flows the local_port will be changed by HW as \;part of the adaptive routing\;Note: may also be a port which is part of a LAG" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="valid" descr="Valid\;SW can set non-valid or valid. HW can only set valid.\;When HW encounters a non-valid entry then HW will choose the \;local_port and will set the valid to &quot;1&quot;\;" access="RW" offset="0x8.16" size="0x0.1" />
</node>

<node name="rarlpgt_ext" descr="" size="0x20.0" >
	<field name="arlpgt_index" descr="AR Local Port Group Table Index \;Range 0.. cap_max_arlpgt-1" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="egress_port" descr="Egress port bitmask\;Note: all ports of a given LAG-ID must have the same value\;No CPU\;" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
</node>

<node name="rarpc_ext" descr="" size="0x30.0" >
	<field name="pc_entry" descr="Packet classification index\;For Spectrum2 allow: 0..3\;Value 255 for default classifier.\;When multi-match then classifier with lower value wins.\;When no match the default classifier wins." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="ar_packet_prof_id" descr="Packet_profile_id:\;0: HBF\;1: AR profile 0\;2: AR profile 1" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="switch_prio" descr="Bitwise enable per each Switch Priority\;Reserved when pc_entry = 255" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="inner_l4_type" descr="Bit0: others\;Bit1: TCP\;Bit2: UDP\;Reserved when pc_entry = 255" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="l4_type" descr="Bit0: others\;Bit1: TCP\;Bit2: UDP\;Reserved when pc_entry = 255" access="RW" offset="0x14.8" size="0x0.8" />
	<field name="inner_l3_type" descr="Bit0: others\;Bit1: IPv4\;Bit2: IPv6\;Reserved when pc_entry = 255" access="RW" offset="0x14.16" size="0x0.8" />
	<field name="l3_type" descr="Bit0: others\;Bit1: IPv4\;Bit2: IPv6\;Reserved when pc_entry = 255" access="RW" offset="0x14.24" size="0x0.8" />
	<field name="bth_opcode_msb" descr="Bitwise enable on BTH.opcode[7:5]\;Reserved when pc_entry = 255" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="bth_ar" descr="BTH.ar (proprietry bit)\;Bit0: ar_is_0\;Bit0: ar_is_1\;Reserved when pc_entry = 255" access="RW" offset="0x18.8" size="0x0.2" />
	<field name="bth_opcode_lsb" descr="Bitwise enable on BTH.opcode[4:0]\;Reserved when pc_entry = 255" access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="ingress_port" descr="Bitwise enable ingress local_port\;Reserved when pc_entry = 255" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
</node>

<node name="rarpr_ext" descr="" size="0x10.0" >
	<field name="ar_prof_id" descr="AR Profile_id:\;0: HBF\;1: AR profile 0\;2: AR profile 1" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="prof_mode" descr="Profile mode:\;0: Adaptive Routing Free\;1: Adaptive Routing Time bound\;2: Random" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="grade_thr_busy" descr="Threshold for Busy grade" access="RW" offset="0x8.0" size="0x0.3" />
	<field name="grade_thr_free" descr="Threshold for Free grade" access="RW" offset="0x8.8" size="0x0.3" />
	<field name="elph" descr="[Internal]\;AR only for elephant flows" access="RW" offset="0x8.24" size="0x0.1" />
	<field name="srt" descr="Enable the ar_shaper_rate_to\;Note: shaper_from is done prior to shaper_to" access="RW" offset="0xC.0" size="0x0.1" />
	<field name="srf" descr="Enable the ar_shaper_rate_from" access="RW" offset="0xC.1" size="0x0.1" />
</node>

<node name="ratr_adjacency_parameters_auto_ext" descr="" attr_is_union="1" size="0x18.0" >
	<field name="eth_adjacency_ext" descr="" subnode="eth_adjacency_ext" offset="0x0.0" size="0x18.0" />
	<field name="ipoib_unicast_without_grh_adjacency_ext" descr="" subnode="ipoib_unicast_without_grh_adjacency_ext" offset="0x0.0" size="0x18.0" />
	<field name="ipoib_unicast_with_grh_adjacency_ext" descr="" subnode="ipoib_unicast_with_grh_adjacency_ext" offset="0x0.0" size="0x18.0" />
	<field name="ipoib_multicast_adjacency_ext" descr="" subnode="ipoib_multicast_adjacency_ext" offset="0x0.0" size="0x18.0" />
	<field name="mpls_adjacency_ext" descr="" subnode="mpls_adjacency_ext" offset="0x0.0" size="0x18.0" />
	<field name="ipinip_encap_adjacency_ext" descr="" subnode="ipinip_encap_adjacency_ext" offset="0x0.0" size="0x18.0" />
</node>

<node name="ratr_ext" descr="" size="0x2c.0" >
	<field name="size" descr="Size - only valid for Allocate / Resize command.\;Reserved when Spectrum/-2" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="a" descr="Activity. Set for new entries. Set if a packet lookup has hit on \;the specific entry. To clear the a bit, use &quot;clear activity&quot; opcode.\;Enabled by activity_dis in RGCR, see Section 13.13.2, &quot;RGCR \;- Router General Configuration Register,&quot; on page 1897" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="v" descr="Valid bit. Indicates if the adjacency entry is valid.\;Note: the device may need some time before reusing an invali\;dated entry. During this time the entry can not be reused. It is \;recommended to use another entry before reusing an invalidated \;entry (e.g. software can put it at the end of the list for reusing). \;Trying to access an invalidated entry not yet cleared by the \;device results with failure indicating &quot;Try Again&quot; status.\;When valid is &apos;0&apos; then egress_router_interface,trap_action, \;adjacency_parameters and counters are reserved" access="RW" offset="0x0.24" size="0x0.1" />
	<field name="opcode" descr="Operation\;For Write:\;0: Allocate/resize Adjacency Table. Reserved when Spectrum/-\;2\;1: Write Adjacency entry \;2: Deallocate Adjacency Table. Reserved when Spectrum/-2\;3: Write Adjacency entry only if the activity is cleared. The \;write may not succeed if the activity is set. There is not direct \;feedback if the write has succeeded or not, however, the get the \;response and later read accesses to this register will reveal the \;actual entry (SW can compare the get response to the set com\;mand). This opcode must not be used for new entries For \;Query:\;0: Read \;2: Read and clear activity\;For Spectrum family the allocate/resize and deallocate are \;reserved\;Note that Write operation may also be used for updating \;counter_set_type and counter_index. In this case all other \;fields must not be updated" access="OP" offset="0x0.28" size="0x0.4" />
	<field name="adjacency_index_15_0" descr="Least significant bits of index into the adjacency table.\;For SwitchX/-2, the adjacency table is linear and used for adja\;cency entries only. \;For Spectrum, the index is to the KVD linear, see Appendix \;A.4.1.2, &quot;KVD Central Database Linear Entries&quot; (page 2256)\;For Spectrum-2, the index is to the KVD linear, see \;Section A.4.1.2, &quot;KVD Central Database Linear Entries,&quot; on \;page 2256\;" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="table" descr="Adjacency table:\;0: Ethernet_unicast_adjacency_table\;1: IPoIB_unicast_and_multicast_adjacency_table\;2: IPoIB_all_routers_adjacency_table\;3: IPoIB_IP_broadcast_adjacency_table\;Reserved when Spectrum/-2" access="INDEX" enum="Ethernet_unicast_adjacency_table=0x0,IPoIB_unicast_and_multicast_adjacency_table=0x1,IPoIB_all_routers_adjacency_table=0x2,IPoIB_IP_broadcast_adjacency_table=0x3" offset="0x4.16" size="0x0.3" />
	<field name="type" descr="Adjacency entry type:\;0: Ethernet\;1: IPoIB_Unicast_without_GRH - reserved when Spectrum/-2\;2: IPoIB_Unicast_with_GRH - supported only in table 0 \;(Ethernet unicast adjacency), Reserved when Spectrum/-2\;3: IPoIB_Multicast - Reserved when Spectrum/-2\;4: MPLS - reserved when SwitchX/-2\;5: IPinIP_Encap - reserved when SwitchX/-2\;" access="RW" enum="Ethernet=0x0,IPoIB_Unicast_with_GRH=0x2,IPoIB_Multicast=0x3" offset="0x4.28" size="0x0.4" />
	<field name="egress_router_interface" descr="Egress Router Interface Index\;Range is 0 .. cap_max_router_interfaces - 1" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="trap_id" descr="Trap ID to be reported to CPU.\;For Spectrum, Trap-ID is RTR_EGRESS0 or RTR_EGRESS1.\;For Spectrum-2, Trap-ID is RTR_EGRESS0 .. RTR_EGRESS3.\;For trap_action of NOP, MIRROR and DISCARD_ERROR \;Error, trap_id is reserved." access="RW" offset="0xC.0" size="0x0.9" />
	<field name="adjacency_index_23_16" descr="Most significant bits of the adjacency_index" access="INDEX" offset="0xC.16" size="0x0.8" />
	<field name="trap_action" descr="Trap Action\;0: NOP\;1: TRAP\;2: MIRROR_TO_CPU\;3: MIRROR\;4: DISCARD_ERROR - see DISCARD_ROUTER3 trap_id\;\;When action is TRAP or DISCARD_ERROR then type must be \;&apos;0&apos;(Ethernet)" access="RW" enum="NOP=0x0,TRAP=0x1,MIRROR_TO_CPU=0x2,MIRROR=0x3,DISCARD_ERROR=0x4" offset="0xC.28" size="0x0.4" />
	<field name="adjacency_parameters" descr="Adjacency parameters. The parameters are related to the type \;field and are described in the tables below.\;Table 1990, &quot;Ethernet Adjacency Parameters Layout,&quot; on \;page 1967\;Table 1992, &quot;IPoIB Unicast without GRH Adjacency Parame\;ters Layout,&quot; on page 1968\;Table 1994, &quot;IPoIB Unicast with GRH Adjacency Parameters \;Layout,&quot; on page 1969\;Table 1996, &quot;IPoIB Multicast Adjacency Parameters Layout,&quot; \;on page 1970\;Table 1998, &quot;MPLS Adjacency Parameters Layout,&quot; on \;page 1971\;Table 2000, &quot;IPinIP Encap Adjacency Parameters Layout,&quot; on \;page 1972\;" subnode="ratr_adjacency_parameters_auto_ext" access="RW" offset="0x10.0" size="0x18.0" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum: See Section 4.2, &quot;Flow Counters,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x28.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 623\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x28.24" size="0x0.8" />
</node>

<node name="ratrad_ext" descr="" size="0x210.0" >
	<field name="ecmp_size" descr="ecmp_size is the amount of sequential entries from the adja\;cency_index (the number of ECMPs).\;The valid range is:\;Spectrum-1: 32-64, 512, 1024, 2048 and 4096.\;Spectrum-2/3: 32-128, 256, 512, 1024, 2048 and 4096." access="INDEX" offset="0x0.0" size="0x0.13" />
	<field name="op" descr="0: Read activity\;1: Read and clear activity" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="adjacency_index" descr="Index into the adjacency table.\;For Spectrum, the index is to the KVD linear, see Appendix \;A.4.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2256)" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="activity_vector" descr="Activity per ECMP entry\;Line 10h bit 31 is for entry 4095\;Line 20C bit0 is for entry 0\;Bits higher than ecmp_size are reserved" access="RO" high_bound="127" low_bound="0" offset="0x10.0" size="0x200.0" />
</node>

<node name="ratrb_eth" descr="" size="0xc.0" >
	<field name="destination_mac_47_32" descr="MAC address of the destination next-hop." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="destination_mac_31_0" descr="MAC address of the destination next-hop." access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="ratrb_ext" descr="" size="0x420.0" >
	<field name="adjacency_index" descr="Index into the adjacency table.\;For Spectrum, the index is to the KVD linear, see Appendix \;A.4.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2256)" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="v" descr="Valid\;0: remove ecmp entries\;1: Write ecmp entries" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="num_rec" descr="Number of records to write\;Range 1..64" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="trap_id" descr="Trap ID to be reported to CPU.\;Trap-ID is RTR_EGRESS0 .. RTR_EGRESS3.\;For trap_action of NOP, MIRROR and DISCARD_ERROR \;Error, trap_id is reserved." access="WO" offset="0x8.0" size="0x0.9" />
	<field name="trap_action" descr="Trap Action\;0: NOP\;1: TRAP\;2: MIRROR_TO_CPU\;3: MIRROR\;4: DISCARD_ERROR\;When action is TRAP or DISCARD_ERROR then type must \;be &apos;0&apos;(Ethernet)" access="WO" enum="NOP=0x0,TRAP=0x1,MIRROR_TO_CPU=0x2,MIRROR=0x3,DISCARD_ERROR=0x4" offset="0x8.28" size="0x0.4" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum: See Section 4.2, &quot;Flow Counters,&quot; on \;page 622\;Not supported by SwitchX and SwitchX-2" access="WO" offset="0xC.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 623\;Not supported by SwitchX and SwitchX-2" access="WO" offset="0xC.24" size="0x0.8" />
	<field name="record" descr="Record. See Section 2006, &quot;RATRB - Record Layout,&quot; on \;page 1977" subnode="ratrb_record" access="WO" high_bound="63" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="ratrb_ipinip" descr="" size="0xc.0" >
	<field name="ipip_type" descr="Underlay destination ip type:\;0: IPv4, set by ipv4_udip\;1: IPv6, set by ipv6_ptr\;\;Note: the type field (IPv4 or IPv6) must match the configu\;ration of the router interface, see protocol field in \;Table 1931, &quot;Loopback IPinIP Overlay Router Interface \;Properties Layout&quot;" access="RW" offset="0x0.28" size="0x0.4" />
	<field name="ipv4_udip" descr="Underlay ipv4 dip\;Reserved when ipip_type is IPv6" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="ipv6_ptr" descr="Pointer to IPv6 underlay destination ip address\;See Section 13.13.19, &quot;RIPS - Router IP version Six Regis\;ter,&quot; on page 1987\;For Spectrum: Pointer to KVD linear space, see \;Section A.4.1.2, &quot;KVD Central Database Linear Entries,&quot; \;on page 2256" access="RW" offset="0x8.0" size="0x0.24" />
</node>

<node name="ratrb_mpls" descr="" size="0xc.0" >
	<field name="nhlfe_ptr" descr="NHLFE entry pointer\;Points to the NHLFE table. When using ECMP, points to the \;first entry in the ECMP list." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="ecmp_size" descr="ecmp_size is the amount of sequential entries from the \;nhlfe_ptr (the number of ECMPs). \;Spectrum-1: 1-64, 512, 1024, 2048 and 4096.\;Spectrum-2: 1-128, 256, 512, 1024, 2048 and 4096.\;" access="RW" offset="0x4.0" size="0x0.13" />
</node>

<node name="ratrb_record" descr="" size="0x10.0" >
	<field name="egress_router_interface" descr="Egress Router Interface Index\;Range is 0 .. cap_max_router_interfaces - 1" access="WO" offset="0x0.0" size="0x0.16" />
	<field name="size" descr="Size\;The amount of entries to be written for this record. Allows \;writing this record multiple consecutive times\;Range 1..4095" access="WO" offset="0x0.16" size="0x0.12" />
	<field name="type" descr="Adjacency entry type:\;0: Ethernet\;4: MPLS\;5: IPinIP_Encap" access="WO" enum="Ethernet=0x0,MPLS=0x4,IPinIP_Encap=0x5" offset="0x0.28" size="0x0.4" />
	<field name="adjacency_parameters" descr="Adjacency parameters. The parameters are related to the type\;field and are described in the tables below.\;Table 2008, &quot;RATRB Ethernet Adjacency Parameters Lay\;out,&quot; on page 1978\;Table 2010, &quot;RATRB MPLS Adjacency Parameters Lay\;out,&quot; on page 1979\;Table 2012, &quot;RATRB IPinIP Encap Adjacency Parameters \;Layout,&quot; on page 1980" subnode="ratrb_record_adjacency_parameters_auto" access="WO" offset="0x4.0" size="0xc.0" union_selector="$(parent).type" />
</node>

<node name="ratrb_record_adjacency_parameters_auto" descr="" attr_is_union="1" size="0xc.0" >
	<field name="ratrb_eth" descr="" subnode="ratrb_eth" offset="0x0.0" selected_by="Ethernet" size="0xc.0" />
	<field name="ratrb_mpls" descr="" subnode="ratrb_mpls" offset="0x0.0" selected_by="MPLS" size="0xc.0" />
	<field name="ratrb_ipinip" descr="" subnode="ratrb_ipinip" offset="0x0.0" selected_by="IPinIP_Encap" size="0xc.0" />
</node>

<node name="rauht_lpm_unicast_ext" descr="" size="0x74.0" >
	<field name="rif" descr="Router Interface" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="a" descr="Activity. Set for new entries. Set if a packet lookup has hit \;on the specific entry.\;To clear the a bit, use &quot;clear activity&quot; op.\;Enabled by activity_dis in RGCR, see Section 13.13.2, \;&quot;RGCR - Router General Configuration Register,&quot; on \;page 1897" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: Add. Used to write a new entry to the table. All RW fields \;are relevant for new entry. Activity bit is set for new entries\;1: Update action. Used to update an existing route entry and \;only update the following fields:\;trap_action, trap_id, mac, counter_set_type, counter_in\;dex\;2: Clear activity. A bit is cleared for the entry.\;3: Delete entry\;4: Delete all host entries on a RIF. In this command, dip \;field is reserved\;For Query:\;0: Read operation. \;1: Clear on read operation. Used to read entry and clear \;activity bit." access="OP" offset="0x0.20" size="0x0.3" />
	<field name="type" descr="Entry Type:\;0: IPv4\;1: IPv6" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="dip" descr="Destination IP address.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are \;reserved.\;Note: This field is a RW field when accessing the entry \;using the handle." access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="trap_id" descr="Trap ID to be reported to CPU.\;For Spectrum, Trap-ID is RTR_EGRESS0 or \;RTR_EGRESS1.\;For Spectrum-2, Trap-ID is RTR_EGRESS0 .. \;RTR_EGRESS3.\;For trap_action of NOP, MIRROR and DISCARD_ER\;ROR, trap_id is reserved." access="RW" offset="0x60.0" size="0x0.9" />
	<field name="trap_action" descr="Trap Action\;0: NOP\;1: TRAP\;2: MIRROR_TO_CPU\;3: MIRROR\;4: DISCARD_ERROR, see DISCARD_ROUTER3 trap_id" access="RW" offset="0x60.28" size="0x0.4" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum: See Section 4.2, &quot;Flow Counters,&quot; on \;page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x68.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 623\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x68.24" size="0x0.8" />
	<field name="mac_47_32" descr="MAC address" access="RW" offset="0x6C.0" size="0x0.16" />
	<field name="mac_31_0" descr="MAC address" access="RW" offset="0x70.0" size="0x4.0" />
</node>

<node name="rauhtd_ext" descr="" size="0x20.0" >
	<field name="filter_fields" descr="Filter Fields:\;if a bit is &apos;0&apos; then the relevant field is ignored and dump is done \;regardless of the field value\;Bit0: filter by activity: entry_a\;Bit3: filter by entry rip: entry_rif" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="num_rec" descr="At request: number of records requested\;At response: number of records dumped\;For IPv4, each record has 4 entries at request and up to 4 entries \;at response\;Range is 0 ..32" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="op" descr="Operation\;0: Dump entries\;1: Clear activity for all entries which were dumped in the current \;session" access="OP" offset="0x4.24" size="0x0.2" />
	<field name="entry_type" descr="Dump only if entry type is:\;0: IPv4\;1: IPv6" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="entry_a" descr="Dump only if activity has value of entry_a\;Reserved if filter_fields bit0 is &apos;0&apos;" access="INDEX" offset="0x8.16" size="0x0.1" />
	<field name="entry_rif" descr="Dump only if RIF has value of entry_rif\;Reserved if filter_fields bit3 is &apos;0&apos;" access="INDEX" offset="0xC.0" size="0x0.16" />
</node>

<node name="rcap_ext" descr="" size="0x8.0" >
	<field name="router_interfaces" descr="Maximal number of virtual interfaces supported by the \;device." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="virtual_routers" descr="Maximum number of virtual routers supported by the \;device." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="rdpm_ext" descr="" size="0x40.0" >
	<field name="dscp" descr="DSCP entry is the DSCP to Prio mapping. For more details refer \;to Table 2028." access="INDEX" high_bound="63" low_bound="0" offset="0x0.24" size="0x40.0" />
</node>

<node name="recr_ext" descr="" size="0x10.0" >
	<field name="type" descr="Hash Type:\;0: CRC (default)\;1: XOR" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="sh" descr="Symmetric Hash.\;When set, the hash calculation results in the same hash value as \;when Source Address (layer 3 and layer 4) is swapped. This \;ensures that the same conversions result in the same hash value.\;For SwitchX/-2: when this bit is set, enabling addresses in \;ecmp_hash must be in couples - both source and destination. This \;includes the following sets:\;SIP, DIP\;TCP/UDP Source Port, TCP/UDP destination port" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="ecmp_hash" descr="ECMP Hashing Configuration. This is a bitmask, in which each set \;bit includes the corresponding item in the ECMP hash calculation.\;0: Source IP address (can be IPv4 or IPv6)\;1: Destination IP address (can be IPv4 or IPv6)\;2: Traffic Class (DSCP and ECN)\;3: Flow Label\;4: TCP/UDP indication (this is the next_protocol field)\;5: TCP/UDP Source Port\;6: TCP/UDP Destination Port\;\;The default ecmp_hash contains SIP, DIP, flow label, Source TCP/\;UDP Port and Destination TCP/UDP Port." access="RW" offset="0x4.0" size="0x0.20" />
	<field name="seed" descr="ECMP seed value." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="recr_v2_ext" descr="" size="0x38.0" >
	<field name="type" descr="Hash type\;0: CRC (default)\;1: XOR \;2: Random\;3: CRC2, For Spectrum-2 and on\;\; \;\;" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="sh" descr="Symmetric hash \;When set, the hash calculation will result in the same hash value as \;when the source address (layer 2 and layer 3) is swapped. This \;ensures that the same conversions will result in the same hash \;value.\;Note: When this bit is set, enabling addresses in outer_header_\;fields_enables and inner_header_fields_enables\;For SwitchX/-2: must be in couples - both source and destination. \;This includes the following sets:\;- SMAC, DMAC\;- SIP, DIP\;- TCP/UDP source port, TCP/UDP destination port\;- SID, DID, for SwitchX/-2 only\;" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="local_port" descr="Ingress Local port number\;Supported from CPU port\;Not supported from router port\;Reserved when pp = Global Configuration" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pp" descr="Per Port Configuration\;0: Global Configuration (for all ports)\;1: Per port configuration, based on local_port field.\;Note: SW must not read as global if last write was not global." access="INDEX" offset="0x0.24" size="0x0.1" />
	<field name="seed" descr="Hash seed value\;The seed is the same for all ports (latest configuration configures \;the seed for all ports)." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="general_fields" descr="This is a bit mask, in which each bit enables a specific field to be \;included in the hash calculation. \;Bit i - custom_bytes i-2\;i = 2 .. 2 + (cap_max_custom_byte_sets_for_hash * cap_cus\;tom_byte_entry_size - 1)\;See Section 10.3.14, &quot;Custom Bytes,&quot; on page 1360" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="outer_header_enables" descr="This is a bit mask, each bit enables a specific layer field to be \;included in the hash calculation. Layers that are not listed below \;are enabled by default.\;Bit 0: Enable Layer2 fields if packet is not IPv4/6\;Bit 1: Enable Layer2 fields if packet is IPv4\;Bit 2: Enable Layer2 fields if packet is IPv6\;Bit 3: Enable IPv4 fields if packet is not TCP and not UDP\;Bit 4: Enable IPv4 fields if packet is either TCP or UDP\;Bit 5: Enable IPv6 fields if packet is not TCP and not UDP\;Bit 6: Enable IPv6 fields if packet is either TCP or UDP\;Bit 7: Enable TCP/UDP header fields if packet is IPv4\;Bit 8: Enable TCP/UDP header fields if packet is IPv6" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="outer_header_fields_enable" descr="Outer header fields enable.\;The default configurations contains SMAC, DMAC, outer\;VID and Ethertype" access="RW" high_bound="4" low_bound="0" offset="0x14.0" size="0x14.0" />
	<field name="inner_header_enables" descr="Inner header enables. Each bit enables a specific layer field to be \;included in the hash calculation. Layers that are not listed below \;are enabled by default.\;Bit 0: Enable inner Layer2 fields if inner packet is not IPv4/6\;Bit 1: Enable inner Layer2 fields if inner packet is IPv4\;Bit 2: Enable inner Layer2 fields if inner packet is IPv6\;Bit 3: Enable inner IPv4 fields if inner packet is not TCP and not \;UDP\;Bit 4: Enable inner IPv4 fields if inner packet is either TCP or \;UDP\;Bit 5: Enable inner IPv6 fields if inner packet is not TCP and not \;UDP\;Bit 6: Enable inner IPv6 fields if inner packet is either TCP or \;UDP\;Bit 7: Enable inner TCP/UDP header fields if inner packet is IPv4\;Bit 8: Enable inner TCP/UDP header fields if inner packet is IPv6" access="RW" offset="0x2C.0" size="0x0.16" />
	<field name="inner_header_fields_enable" descr="Inner header fields enable.\;\;Inner Layer2 fields, subject to inner_header_enables:\;Bit 0: SMAC\;Bit 1: DMAC\;Bit 2: Ethertype\;\;Inner IPv4 fields, subject to inner_header_enables:\;Bits 6:3: IPv4 SIP 0-3 enable per byte\;Bits 10:7: IPv4 DIP 0- 3 enable per byte\;Bit 11: IPv4 Protocol\;\;Inner IPv6 fields, subject to inner_header_enables:\;Bits 12: IPv6 enable bytes of SIP 0-7\;Bits 19:13 reserved\;Bits 27:20: IPv6 SIP 8-15 enable per byte\;Bits 28: IPv6 enable bytes of DIP 0-7\;Bits 35:29 reserved\;Bits 43:36: IPv6 DIP 8-15 enable per byte\;Bit 44: IPv6 Next Header\;Bit 45: IPv6 Flow label\;\;Inner TCP /UDP header fields, subject to inner_header_enables:\;Bit 46: TCP/UDP source port\;Bit 47: TCP/UDP destination port" subnode="uint64" access="RW" offset="0x30.0" size="0x8.0" />
</node>

<node name="region_id_dup" descr="" size="0x4.0" >
	<field name="region_id_dup" descr="" offset="0x0.0" size="0x0.16" />
</node>

<node name="reiv_ext" descr="" size="0x420.0" >
	<field name="erif" descr="egress RIF\;Range is 0.. cap_max_router_interfaces-1" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="elport_record" descr="egress local port record\;record i for local_port i\;See Table 2096, &quot;REIV - elport_record Layout,&quot; on page 2036" subnode="elport_record" access="RW" high_bound="255" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="remote_span_ib_local_ud_ext" descr="" size="0x4c.0" >
	<field name="dlid" descr="Destination LID. Note that the analyzer port is configured by the sys\;tem_port field and not by forwarding the packet based on the dlid \;field." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. When set to dynamic mode, the analyzer port \;is set based on the forwarding information for the dlid onprivate-LFT \;0 instead of  the system_port field. In static mode, the packet is trans\;mitted to the configured system_port regardless of the forwarding \;database.\;0: static analyzer port\;1: dynamic analyzer port" access="RW" offset="0x0.16" size="0x0.2" />
	<field name="sl" descr="Service Level" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="we" descr="Write enable:\;0: write all fields\;1: write only psn_init_val" access="WO" offset="0x0.24" size="0x0.8" />
	<field name="slid" descr="Source LID (LID of the sending device)" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="version" descr="Remote SPAN InfiniBand encapsulation header version\;1: V1 - Mirror Header Version 1\;2: V2 - Mirror Header Version 2\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the ana\;lyzer port based on the desired forwarding table (the one that belong \;to the swid)." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="vl" descr="Virtual Lane on which the mirrored packet is queued.\;Mirrored packets cannot be queued on VL-15." access="RW" offset="0xC.0" size="0x0.4" />
	<field name="pkey" descr="BTH PKey" access="RW" offset="0x38.0" size="0x0.16" />
	<field name="m" descr="BTH m" access="RW" offset="0x38.22" size="0x0.1" />
	<field name="se" descr="BTH se" access="RW" offset="0x38.23" size="0x0.1" />
	<field name="dest_qp" descr="BTH dest QP" access="RW" offset="0x3C.0" size="0x0.24" />
	<field name="psn_init_val" descr="BTH packet sequence number initial value\;Note: when reading, HW will reveal the current packet sequence \;number" access="RW" offset="0x40.0" size="0x0.24" />
	<field name="ar" descr="BTH MLNX adaptive routing enable flag" access="RW" offset="0x40.30" size="0x0.1" />
	<field name="qkey" descr="DETH QKey" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="src_qp" descr="DETH source QP" access="RW" offset="0x48.0" size="0x0.24" />
</node>

<node name="rgcr_ext" descr="" size="0x34.0" >
	<field name="mpls_en" descr="MPLS router enable.\;Enables receive/forward of MPLS packets to/from the \;router\;Enables router traps" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="ipv6_en" descr="IPv6 router enable.\;Enables receive/forward of IPv6 packets to/from the router\;Enables router traps" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="ipv4_en" descr="IPv4 router enable.\;Enables receive/forward of IPv4 packets to/from the router\;Enables router traps" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="max_vlan_router_interfaces" descr="Max VLAN router interfaces - defines the maximum num\;ber of active VLAN router interfaces per virtual router \;(VR) to be used.\;Reserved when Spectrum/-2" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="max_port_router_interfaces" descr="Max VLAN router interfaces - defines the maximum num\;ber of active VLAN router interfaces per VR to be used.\;Reserved when Spectrum/-2" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="max_pkey_router_interfaces" descr="Max VLAN router interfaces - defines the maximum num\;ber of active VLAN router interfaces per VR to be used.\;Note: max_pkey_interface can not be increased while the \;router is enable unless ipb and allr are cleared.\;Reserved when Spectrum/-2" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="max_router_interfaces" descr="Max router interfaces - defines the maximum number of \;active router interfaces for ALL VRs." access="RW" offset="0x10.0" size="0x0.16" />
	<field name="max_virtual_routers" descr="Max number of active VRs.\;Reserved when Spectrum/-2\;" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="rpf" descr="When set, multicast RPF is not performed for all router \;packets. This bit overrides the RMFT.rpf configuration \;and only allows the following options:\;0: no RPF, ignore expected_ingress_rif\;1: RPF / directional forwarding enable (match only if \;packet is coming from)\;Note: While this configuration can be done on a per entry \;basis, using the global configuration allows more efficient \;internal resource utilization and is recommended.\;Note: This bit cannot be changed while router is enabled.\;Reserved when Spectrum/-2" access="RW" offset="0x18.0" size="0x0.1" />
	<field name="mcsi" descr="Multicast Single Interface.\;Indicates all multicast groups contain at most a single L3 \;interface. Allows some internal resource optimizations.\;Reserved when Spectrum/-2" access="RW" offset="0x18.4" size="0x0.1" />
	<field name="allr" descr="All Routers\;Allocate Multicast IPoIB Adjacency Table for all routers.\;Note: the allr bit cannot be set (updated from 0 to 1) while \;the router is enabled.\;Reserved when Spectrum/-2" access="RW" offset="0x18.8" size="0x0.1" />
	<field name="ipb" descr="IP Broadcast. Allocates Multicast IPoIB Adjacency Table \;for IP Broadcast.\;Note: ipb bit can not be set (updated from 0 to 1) while the \;router is enabled.\;Reserved when Spectrum/-2" access="RW" offset="0x18.9" size="0x0.1" />
	<field name="pcp_rw" descr="PCP Re-write Enable\;Indicates how to handle the pcp_rewrite_en:\;0: Preserve the value of the pcp_rewrite_en\;2: Disable the pcp_rewrite_en\;3: Enable the pcp_rewrite_en\;Reserved when SwitchX/-2" access="RW" offset="0x18.16" size="0x0.2" />
	<field name="usp" descr="Update Switch Priority and Packet Color\;0: Preserve the value of the Switch Priority and Packet \;Color\;1: Recalculate the value of the Switch Priority and Packet \;Color. See Section 13.13.20, &quot;RDPM - Router DSCP to \;Priority Mapping Register,&quot; on page 1988\;Reserved when SwitchX/-2" access="RW" offset="0x18.20" size="0x0.1" />
	<field name="ipv4_packet_rate" descr="IPv4 TCAM regions expected packet rate performance.\;Granularity is of 5%\;Reserved when Spectrum-2" access="RW" offset="0x1C.0" size="0x0.5" />
	<field name="ipv4_op_type" descr="IPv4 TCAM regions optimization Type\;0: No optimization\;1: Soft optimization\;2: Hard optimization\;Reserved when Spectrum-2" access="RW" offset="0x1C.8" size="0x0.2" />
	<field name="ipv6_packet_rate" descr="IPv6 TCAM regions expected packet rate performance.\;Granularity is of 5%\;Reserved when Spectrum-2" access="RW" offset="0x1C.16" size="0x0.5" />
	<field name="ipv6_op_type" descr="IPv6 TCAM regions optimization Type\;0: No optimization\;1: Soft optimization\;2: Hard optimization\;Reserved when Spectrum-2\;\;\;" access="RW" offset="0x1C.24" size="0x0.2" />
	<field name="activity_dis" descr="Activity Disable:\;0: enable - activity will be set when an entries are hit\;(default)\;1: disable - activity will not be set when an entries are hit\;Bit 0: Disable activity bit in Router Algorithmic LPM \;Unicast Entry. See Section 13.13.26, &quot;RALUE - Router \;Algorithmic LPM Unicast Entry Register,&quot; on page 2004\;Bit 1: Disable activity bit in Router Algorithmic LPM \;Unicast Host Entry. See Section 13.13.28, &quot;RAUHT - \;Router Algorithmic LPM Unicast Host Table Register,&quot; on \;page 2019\;Bit 2: Disable activity bit in RATR\;Not supported by SwitchX/-2 and Switch-IB" access="RW" offset="0x20.0" size="0x0.8" />
	<field name="grh_hop_limit" descr="HopLmt field in GRH for IPoIB adjacencies." access="RW" offset="0x20.16" size="0x0.8" />
	<field name="expected_irif_list_index_base" descr="For MC routing RPF, base address of the lists of expected \;ingress RIFs\;Default 0\;For Spectrum, this is in KVD Linear, see Section A.4.1.2, \;&quot;KVD Central Database Linear Entries,&quot; on page 2256\;The list is configured by RMEIR, see Section 13.13.36, \;&quot;RMEIR - Router Multicast Expected Ingress RIFs Regis\;ter,&quot; on page 2033\;Reserved when SwitchX, SwitchX-2 and Switch-IB" access="RW" offset="0x24.0" size="0x0.24" />
	<field name="ar_srt" descr="Adaptive Routing Shaper Rate To\;Shape the time between flows that can change their desti\;nation to a RIF\;1: 100nSec\;2: 1uSec (default)\;3: 10uSec\;4: 100uSec\;5: 1mSec\;Shaper burst size is 1. \;Shaper error is up to *8 faster (e.g. when configured \;1mSec, then there will be 1 to 8 changes in 1mSec)" access="RW" offset="0x30.0" size="0x0.3" />
	<field name="ar_srf" descr="Adaptive Routing Shaper Rate From\;Shape the time between flows that can change their desti\;nation from a RIF\;1: 100nSec\;2: 1uSec (default)\;3: 10uSec\;4: 100uSec\;5: 1mSec\;Shaper burst size is 1. \;Shaper error is up to *8 faster (e.g. when configured \;1mSec, then there will be 1 to 8 changes in 1mSec)" access="RW" offset="0x30.8" size="0x0.3" />
</node>

<node name="rica_ext" descr="" size="0x10.0" >
	<field name="index" descr="Counter set index. \;Relevant for Interface Counter Set type only." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="counter_set_type" descr="Counter set type.\;0: Interface counter set. \;1: Global IPv4 counter set\;2: Global IPv6 counter set\;\;The above types allocate two counter sets, one for ingress counter \;and one for egress counter.\;Note: For the global counter sets, the ingress and egress handles \;must be freed on the same operation." access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="op" descr="Operation:\;0: NOP\;1: allocate\;2: test\;3: free" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="ingress_counter_set" descr="Opaque object that represents the counter set. Returned when allo\;cating counter set. This is provided by the software for router \;interface creation.\;Provided by software on Free operation" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="egress_counter_set" descr="Opaque object that represents the counter set. Returned when allo\;cating counter set. This is provided by the software for router \;interface creation.\;Provided by software on Free operation" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="ricnt_inter_ext" descr="" size="0x100.0" >
	<field name="gl" descr="Global. This field indicates whether to access an interface \;counter or a global (IPv4 / IPv6) counter set. When accessing a \;global counter set, counter_handle field is ignored\;0: Interface counters\;1: Ingress IPv4 counter set\;2: Egress IPv4 counter set\;3: Ingress IPv6 counter set\;4: Egress IPv6 counter set\;Reserved when Spectrum/-2, Switch-IB/2, Quantum" access="INDEX" offset="0x0.16" size="0x0.3" />
	<field name="opcode" descr="0: NOPE, supported only for read access\;1: ADD counters - add a set of values to the counter_handle.\;2: FLUSH Counters - when counter set is un-bound, flush \;ensures counters in counter_handle will not be updated due to \;packets in the pipe.\;8: CLEAR counters - reset all counters of the counter_handle\;\;When read opcode can be NOPE or CLEAR\;For SwitchX/-2, Switch-IB/2, Quantum: When write opcode \;must be CLEAR" access="OP" offset="0x0.28" size="0x0.4" />
	<field name="counter_handle" descr="For SwitchX/-2 the counter handle is retrieved using RICA\;For Spectrum/2, Switch-IB/2, Quantum: the counter_handle is \;described in Table 2034, &quot;RICNT Counter Handle Layout,&quot; on \;page 1991. \;For Switch-IB/2, Quantum: based on Router Interface Index" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="counter_set" descr="Router Interface counter set types.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 623\;Supports counter_set_types of:\;- No Count\;- CounterSet4 (SwitchX/-2 only)\;- IB Router Interface Counter-set Basic (Switch-IB/2, Quan\;tum)\;- Router Interface Counter-set Basic (Spectrum/-2)\;- Router Interface Counter-set Enhanced (Spectrum/-2)\;- Router Interface Counter-set Mixed-1 (Spectrum/-2)\;- Router Interface Counter-set Mixed-2 (Spectrum/-2)\;For ADD operation the counter set is used as write field" access="RW" high_bound="61" low_bound="0" offset="0x8.0" size="0xf8.0" />
</node>

<node name="rigr_erif_list" descr="" size="0x90.0" >
	<field name="rmid_index" descr="RMID Index\;Range 0 .. max_mid - 1\;Reserved when vrmid = &apos;0&apos;\;For Spectrum family the index is to the Port Group Table, see \;Appendix A.4.2, &quot;Port Group Table (PGT)&quot; (page 2256)" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="vrmid" descr="RMID Index is valid" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="erif_entry" descr="See Table 1953, &quot;RIGR List Type Erif List Erif_Entry Lay\;out,&quot; on page 1927\;Number of entries can be from 1 to cap_mc_erif_list_entries\;Low-entries must be set if high-entries are set. For example: if \;erif_entry[2].v is set then erif_entry[1].v and erif_entry[0].v \;must be set." subnode="rigr_erif_list_erif_entry_auto" access="RW" high_bound="31" low_bound="0" offset="0x4.0" size="0x80.0" />
	<field name="adabe_reserved1" descr="" access="RW" offset="0x84.0" size="0x4.0" />
	<field name="adabe_reserved2" descr="" access="RW" offset="0x88.0" size="0x4.0" />
	<field name="adabe_reserved3" descr="" access="RW" offset="0x8C.0" size="0x4.0" />
</node>

<node name="rigr_erif_list_erif_entry" descr="" size="0x4.0" >
	<field name="erif" descr="Egress Router Interface\;Valid range is 0..cap_max_router_interfaces - 1\;i can be from 0 to cap_mc_erif_list_entries-1" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="v" descr="Egress Router Interface is valid\;Note that low-entries must be set if high-entries are set. For \;example: if erif_entry[2].v is set then erif_entry[1].v and \;erif_entry[0].v must be set.\;i can be from 0 to cap_mc_erif_list_entries-1" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="rigr_erif_list_erif_entry_auto" descr="" attr_is_union="1" size="0x4.0" >
	<field name="rigr_erif_list_erif_entry" descr="" subnode="rigr_erif_list_erif_entry" offset="0x0.0" size="0x4.0" />
</node>

<node name="rigr_ext" descr="" size="0x3fc.0" >
	<field name="offset" descr="Offset for the Interface Group\;SwitchX and SwitchX-2:\;Offset of the multicast forwarding entry within the Multicast \;Forwarding Table to which the interfaces would be added. Same \;index used in RMFT register to write the {S,G} / {*,G} entry." access="INDEX" offset="0x0.0" size="0x0.18" />
	<field name="list_encoding" descr="0: SwitchX_Ethernet\;1: IPoIB\;" access="RW" enum="SwitchX_Ethernet=0x0,IPoIB=0x1" offset="0x0.22" size="0x0.2" />
	<field name="op" descr="Opcode:\;1: Add router interfaces to group.\;2: Remove router interfaces from group\;3: Remove all interfaces\;4: Update adjacency_index of IPoIB router interfaces\;Note: For the Update op, all router interfaces provided in rout\;er_interface_list, must be of type IPoIB PKEY interface" access="WO" offset="0x0.24" size="0x0.3" />
	<field name="type" descr="Entry Type:\;0: IPv4\;1: IPv6" access="INDEX" enum="IPv4=0x0,IPv6=0x1" offset="0x0.28" size="0x0.2" />
	<field name="router_interface_list" descr="Router Interface List.\;Encoding of this field depends on the type field.\;Table 1939, &quot;Ethernet Only Router Interface List Layout,&quot; on \;page 1910\;Table 1941, &quot;IPoIB Router Interface List Layout,&quot; on \;page 1910\;Note: It is possible to use (type==Ethernet and IPoIB), only that \;packing might cause larger command payload in case of a large \;number of interfaces." subnode="rigr_router_interface_list_auto_ext" access="RW" offset="0x4.0" size="0x3f8.0" union_selector="$(parent).list_encoding" />
</node>

<node name="rigr_router_interface_list_auto_ext" descr="" attr_is_union="1" size="0x3f8.0" >
	<field name="eth_only_router_ext" descr="" subnode="eth_only_router_ext" offset="0x0.0" selected_by="SwitchX_Ethernet" size="0x3f8.0" />
	<field name="ipoib_router_inter_ext" descr="" subnode="ipoib_router_inter_ext" offset="0x0.0" selected_by="IPoIB" size="0x3f8.0" />
</node>

<node name="rigr_v2_ext" descr="" size="0xb0.0" >
	<field name="list_type" descr="Router Interface List type\;Format field indicates the encoding of the router_interface_list \;field.\;0: ERIF_LIST\;3: NVE_DECAP\;" access="RW" enum="ERIF_LIST=0x0,NVE_DECAP=0x3" offset="0x0.20" size="0x0.4" />
	<field name="rigr_index" descr="Index to Router Interface Group (RIGR) Table\;For Spectrum family the index is to the KVD linear, see Appen\;dix A.4.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2256)" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="next_rigr_index" descr="Next RIGR Index\;For Spectrum family the index is to the KVD linear, see Appen\;dix A.4.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2256)\;Reserved when vnext = &apos;0&apos;" access="RW" offset="0x8.0" size="0x0.24" />
	<field name="vnext" descr="Next RIGR Index is valid" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="erif_list" descr="Egress Router Interface List according to list_type\;See Table 1951, &quot;RIGR List Type Erif List Layout,&quot; on \;page 1926\;See Table 1959, &quot;RIGR List Type NVE Decap Layout,&quot; on \;page 1929\;\;\;\;\;" subnode="rigr_erif_list" access="RW" offset="0x20.0" size="0x90.0" />
</node>

<node name="rips_ip_ext" descr="" size="0x14.0" >
	<field name="index" descr="Index to IPv6 address\;For Spectrum, the index is to the KVD linear, see Section A.4.1, \;&quot;KVD Central Database,&quot; on page 2252" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="ipv6" descr="IPv6 address\;" access="RW" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
</node>

<node name="ritr_ext" descr="" size="0x40.0" >
	<field name="rif" descr="Router Interface Index - a pointer to the Router Interface Table.\;Range is 0.. cap_max_router_interfaces-1\;Note: when type = 2 (Sub-Port Interface) and ubridge = 0 then \;range is no more than 0..1K-1\;For Spectrum-1: when type is Loopback IPinIP and protocol is \;IPv6 then 2 Router Interface Table entries are consumed and the \;entry must be even. For Spectrum-2: 1 entry, can be odd." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="mpls" descr="MPLS routing enable - enables routing of packets coming from \;MPLS tunnel\;Reserved when IB switches\;Reserved when type is Loopback generic" access="RW" offset="0x0.19" size="0x0.1" />
	<field name="op" descr="Operation Code\;Opcode: \;0: Create or Edit RIF\;1: Delete RIF\;Reserved when SwitchX/-2 and Switch-IB/2 since there is no \;need to create or delete an interface." access="WO" offset="0x0.20" size="0x0.2" />
	<field name="type_ib" descr="Type Infiniband\;Controls the type field\;Reserved when SwitchX/-2 and Spectrum/-2\;For IB switches must be set to &apos;1&apos;" access="RW" offset="0x0.22" size="0x0.1" />
	<field name="type" descr="Router interface type\;If type_ib = 0:\;0: VLAN\;1: FID - not supported by SwitchX/-2\;2: Subport\;3: Loopback\;4: IPoIB_PKEY - not supported by Spectrum/-2\;0: IB_SWID" access="RW" enum="VLAN=0x0,FID=0x1,Subport=0x2,Loopback=0x3,IPoIB_PKEY=0x4,IB_SWID=0x0" offset="0x0.23" size="0x0.3" />
	<field name="ipv6_mc" descr="IPv6 multicast routing enable\;Reserved when IB switches" access="RW" offset="0x0.26" size="0x0.1" />
	<field name="ipv4_mc" descr="IPv4 multicast routing enable\;Reserved when IB switches" access="RW" offset="0x0.27" size="0x0.1" />
	<field name="ipv6" descr="IPv6 routing enable - enables routing of IPv6 traffic on the \;router interface.\;Reserved when IB switches" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="ipv4" descr="IPv4 routing enable - enables routing of IPv4 traffic on the \;router interface.\;Reserved when IB switches" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="valid" descr="Router interface valid\;Reserved when Spectrum/-2" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="enable" descr="Router interface enable - enables routing on the router interface\;When ubridge = 1 the SVFA.irif_v, SFMR.irif_v must be set \;after enable and must be cleared before disable" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="virtual_router" descr="Virtual router ID associated with the router interface\;Range is 0..cap_max_virtual_routers-1\;Reserved when IB switches" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="mpls_fe" descr="MPLS routing Forwarding enable - enables routing of MPLS \;traffic on the router interface. When disabled, forwarding is \;blocked but local traffic (traps and IP to me) will be enabled\;Reserved when type is Loopback generic\;Reserved when IB switches" access="RW" offset="0x4.19" size="0x0.1" />
	<field name="urpf_ad" descr="Unicast RPF Allow Default:\;0: match on default route (/0) is not considered as a match\;1: match on default route (/0) is considered as a match\;Note that in loose mode with allow default will always have a \;match\;Reserved when type is Loopback generic\;Reserved when IB switches" access="RW" offset="0x4.20" size="0x0.1" />
	<field name="urpf_strict" descr="Unicast RPF is strict mode:\;0: loose mode, check that SIP is in the table (as a DIP)\;1: strict mode, check that the packet arrives on the same router \;interface that the router would use to reach that SIP\;Note: strict mode always filters packets going to an adjacency \;table (a.k.a. ECMP) with more than 1 entry\;Note: when IP2ME (either trap or decap) the urpf will filter (if \;enabled)\;Reserved when type is Loopback generic\;Reserved when IB switches" access="RW" offset="0x4.21" size="0x0.1" />
	<field name="urpf_en_ipv6" descr="Unicast RPF enable for IPv6 packets\;Reserved when type is Loopback generic\;Reserved when IB switches" access="RW" offset="0x4.22" size="0x0.1" />
	<field name="urpf_en_ipv4" descr="Unicast RPF enable for IPv4 packets\;Reserved when type is Loopback generic\;Reserved when IB switches\;" access="RW" offset="0x4.23" size="0x0.1" />
	<field name="lb_en" descr="Loop-back Filter Enable for unicast packets.\;If the flag is set then loop-back filter for unicast packets is \;implemented on the RIF. Multicast packets are always subject \;to loopback filtering.\;Note that in SwitchX/-2 devices, loopback filter is always \;enabled and this bit is ignored.\;Reserved when Switch-IB/-2, since loopback filter is always \;enabled\;" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="ipv6_mc_fe" descr="IPv6 Multicast Forwarding Enable. When disabled, forwarding \;is blocked but local traffic (traps and IP to me) will be enabled.\;Reserved when SwitchX/-2 and IB switches" access="RW" offset="0x4.26" size="0x0.1" />
	<field name="ipv4_mc_fe" descr="IPv4 Multicast Forwarding Enable. When disabled, forwarding \;is blocked but local traffic (traps and IP to me) will be enabled.\;Reserved when SwitchX/-2 and IB switches" access="RW" offset="0x4.27" size="0x0.1" />
	<field name="ipv6_fe" descr="IPv6 Forwarding Enable - enables forwarding of IPv6 traffic on \;the router interface. When disabled, forwarding is blocked but \;local traffic (traps and IP to me) will be enabled.\;Reserved when SwitchX/-2 and IB switches" access="RW" offset="0x4.28" size="0x0.1" />
	<field name="ipv4_fe" descr="IPv4 routing Forwarding Enable - enables routing of IPv4 traf\;fic on the router interface. When disabled, forwarding is \;blocked but local traffic (traps and IP to me) will be enabled.\;Reserved when SwitchX/-2 and IB switches" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="router_interface_properties" descr="Router interface properties - format depends on router interface \;type. The different formats are described in:\;Table 1921, &quot;VLAN Router Interface Properties Layout,&quot; on \;page 1908\;Table 1923, &quot;FID Router Interface Properties Layout,&quot; on \;page 1910\;Table 1925, &quot;Sub-Port Router Interface Properties Layout,&quot; on \;page 1912\;Table 1929, &quot;Loopback Router Interface Properties Layout,&quot; on \;page 1915\;Table 1927, &quot;IPoIB PKEY Router Interface Properties Layout,&quot; \;on page 1914\;Table 1935, &quot;IB SWID Router Interface Properties Layout,&quot; on \;page 1917" subnode="ritr_router_interface_properties_auto_ext" access="RW" offset="0x8.0" size="0x24.0" union_selector="$(parent).type" />
	<field name="mtu" descr="Router interface MTU\;Must be greater than 63B\;Reserved IB switches" access="RW" offset="0x34.0" size="0x0.16" />
	<field name="ttl_threshold" descr="Time-to-live - minimum TTL for multicast packets\;Reserved IB switches" access="RW" offset="0x34.24" size="0x0.8" />
	<field name="ingress_counter_index" descr="Counter Index for flow counters.\;For Spectrum/-2: see Section 4.2, &quot;Flow Counters,&quot; on \;page 622\;Reserved when SwitchX/-2 and IB switches" access="RW" offset="0x38.0" size="0x0.24" />
	<field name="ingress_counter_set_type" descr="Ingress Counter Set Type for router interface counters.\;For Spectrum/-2: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 623\;Reserved when SwitchX/-2 and IB switches\;In SwitchX/-2, counter set is allocated using RICA register." access="RW" offset="0x38.24" size="0x0.8" />
	<field name="egress_counter_index" descr="Counter Index for flow counters.\;For Spectrum/-2: See Section 4.2, &quot;Flow Counters,&quot; on \;page 622\;Reserved when SwitchX/-2 and IB switches" access="RW" offset="0x3C.0" size="0x0.24" />
	<field name="egress_counter_set_type" descr="Egress Counter Set Type for router interface counters.\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 623\;For Spectrum/-2: if IPinIP Encapsulation may be done on this \;RIF then counter set must not be &apos;0&apos;\;Reserved when SwitchX/-2 and IB switches\;In SwitchX/-2, counter set is allocated using RICA register" access="RW" offset="0x3C.24" size="0x0.8" />
</node>

<node name="ritr_router_interface_properties_auto_ext" descr="" attr_is_union="1" size="0x24.0" >
	<field name="vlan_router_interface_ext" descr="" subnode="vlan_router_interface_ext" offset="0x0.0" selected_by="VLAN" size="0x18.0" />
	<field name="fid_router_ext" descr="" subnode="fid_router_ext" offset="0x0.0" selected_by="FID" size="0x18.0" />
	<field name="router_interface_sub_port_ext" descr="" subnode="router_interface_sub_port_ext" offset="0x0.0" selected_by="Subport" size="0x18.0" />
	<field name="loopback_router_interface_ext" descr="" subnode="loopback_router_interface_ext" offset="0x0.0" selected_by="Loopback" size="0x24.0" />
	<field name="ipoib_pkey_router_ext" descr="" subnode="ipoib_pkey_router_ext" offset="0x0.0" selected_by="IPoIB_PKEY" size="0x14.0" />
	<field name="ib_swid_ext" descr="" subnode="ib_swid_ext" offset="0x0.0" selected_by="IB_SWID" size="0x24.0" />
</node>

<node name="rlcme_ext" descr="" size="0x3c.0" >
	<field name="m_idx" descr="M Index" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: WRITE_STATIC\;1: WRITE_CACHEABLE (may be overwritten by HW)\;2: DELETE_STATIC\;For Query:\;0: READ_STATIC" access="OP" offset="0x0.20" size="0x0.3" />
	<field name="protocol" descr="0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers -1" access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="dip" descr="The prefix of the route or of the marker that the object of the LPM \;is compared with. The most significant bits of the dip are the pre\;fix. The least significant bits must be &apos;0&apos; if the prefix_len is \;smaller than 128 for IPv6 or smaller than 32 for IPv4.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="INDEX" high_bound="3" low_bound="0" offset="0xC.0" size="0x10.0" />
	<field name="action_type" descr="Action Type\;Indicates how the IP address is connected\;It can be connected to a local subnet through local_erif or can be \;on a remote subnet connected through a next-hop router, or trans\;mitted to the CPU.\;0: REMOTE \;1: LOCAL \;2: IP2ME\;Reserved when entry_type = MARKER_ENTRY" access="RW" offset="0x1C.0" size="0x0.2" />
	<field name="action" descr="The forwarding action as function of action_type:\;Section 13.13.26.1, &quot;RALUE Remote Action,&quot; on page 2007\;Section 13.13.26.2, &quot;RALUE Local Action,&quot; on page 2008\;Section 13.13.26.3, &quot;RALUE IP2ME Action,&quot; on page 2009\;Reserved when action_valid = 0" access="RW" high_bound="4" low_bound="0" offset="0x20.0" size="0x14.0" />
	<field name="counter_index" descr="Counter Index for flow counters\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x34.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on page 623\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x34.24" size="0x0.8" />
	<field name="l_value" descr="Value of L\;For IPv4: up to 31, for IPv6: up to 127.\;Reserved when action_valid = 1" access="RW" offset="0x38.0" size="0x0.7" />
	<field name="l_vector" descr="L Vector\;bit0: value of 2bits {m+1, m+2} is &quot;0&quot;\;bit1: value of 2bits {m+1, m+2} is &quot;1&quot;\;bit2: value of 2bits {m+1, m+2} is &quot;2&quot;\;bit3: value of 2bits {m+1, m+2} is &quot;3&quot;" access="RW" offset="0x38.8" size="0x0.4" />
	<field name="action_valid" descr="The action is valid:\;0: this entry provides the L value\;1: this entry is an action entry" access="RW" offset="0x38.25" size="0x0.1" />
</node>

<node name="rlcmld_ext" descr="" size="0x30.0" >
	<field name="filter_fields" descr="Filter Fields:\;if a bit is &apos;0&apos; then the relevant field is ignored and dump is done \;regardless of the field value\;Bit1: filter by m_idx\;Bit2: filter by protocol\;Bit3: filter by virtual_router\;Bit4: filter by dip\;All set filters are relevant (there is AND between the filters)" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="select" descr="Which entries to delete:\;0: ML entries\;1: M entries\;2: M and ML entries" access="INDEX" offset="0x0.16" size="0x0.2" />
	<field name="m_idx" descr="M Index\;0: m0\;1: m1" access="INDEX" offset="0x4.0" size="0x0.1" />
	<field name="protocol" descr="0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers -1" access="INDEX" offset="0xC.0" size="0x0.16" />
	<field name="dip" descr="The prefix and mask (dip_mask) of the route or of the marker that \;the object of the LPM is compared with. The most significant bits \;of the dip are the prefix. The least significant bits must be &apos;0&apos; if the \;prefix_len is smaller than 128 for IPv6 or smaller than 32 for IPv4.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="dip_mask" descr="dip_mask:\;per bit:\;0: no match\;1: match" access="INDEX" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
</node>

<node name="rlcmle_ext" descr="" size="0x58.0" >
	<field name="m_idx" descr="M Index" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: WRITE_STATIC\;1: WRITE_CACHEABLE (may be overwritten by HW)\;2: DELETE_STATIC\;For Query:\;0: READ_STATIC" access="OP" offset="0x0.20" size="0x0.3" />
	<field name="protocol" descr="0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="l_value" descr="Value of L\;For IPv4: up to 31, for IPv6: up to 127." access="INDEX" offset="0x4.0" size="0x0.7" />
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers -1" access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="dip" descr="The prefix and mask (dip_mask) of the route or of the marker that \;the object of the LPM is compared with. The most significant bits \;of the dip are the prefix. The least significant bits must be &apos;0&apos; if the \;prefix_len is smaller than 128 for IPv6 or smaller than 32 for IPv4.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="dip_mask" descr="dip_mask:\;per bit:\;0: no match\;1: match" access="INDEX" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="action_type" descr="Action Type\;Indicates how the IP address is connected\;It can be connected to a local subnet through local_erif or can be \;on a remote subnet connected through a next-hop router, or trans\;mitted to the CPU.\;0: REMOTE \;1: LOCAL \;2: IP2ME\;Reserved when entry_type = MARKER_ENTRY" access="RW" offset="0x30.0" size="0x0.2" />
	<field name="action" descr="The forwarding action as function of action_type:\;Section 13.13.26.1, &quot;RALUE Remote Action,&quot; on page 2007\;Section 13.13.26.2, &quot;RALUE Local Action,&quot; on page 2008\;Section 13.13.26.3, &quot;RALUE IP2ME Action,&quot; on page 2009" access="RW" high_bound="4" low_bound="0" offset="0x40.0" size="0x14.0" />
	<field name="counter_index" descr="Counter Index for flow counters\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x54.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on page 623\;Not supported by SwitchX and SwitchX-2" access="RW" offset="0x54.24" size="0x0.8" />
</node>

<node name="rmeir_ext" descr="" size="0x210.0" >
	<field name="expected_irif_list_index" descr="Expected Ingress RIF List Index\;An index to the list of expected ingress RIFs\;For Spectrum, this is in KVD Linear, see Appendix A.4.1.2, \;&quot;KVD Central Database Linear Entries&quot; (page 2256)" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="num_entries" descr="Number of entries\;Range 1..16\;Value of 0 means 1 entry\;Reserved when Spectrum-1" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="expected_irif_bit_vector" descr="Bit Vector of the expected Ingress RIFs. Configures 256 \;entries.\;For more than 256 RIFs use stacking of irif_bit_vectors\;User must use stacking for supporting cap_max_router_inter\;faces RIFs\;Rif (N*256) is at 2Ch bit0\;The 1st expected_irif_list_index (e.g. 1000) is for RIFs 0..255, \;the 2nd expected_irif_list_index (e.g. 1002) is for RIFs \;256..511 etc.\;Valid range is 0.. cap_max_router_interfaces-1\;Note: Spectrum-1 supports only 1 entry\;Note for Spectrum-1: value of 0x3ff represents the RIF after \;NVE encap." subnode="array256_auto" access="RW" high_bound="15" low_bound="0" offset="0x10.0" size="0x200.0" />
</node>

<node name="rmft_ext" descr="" size="0x90.0" >
	<field name="offset" descr="Offset within the multicast forwarding table to write to.\;Reserved when Switch-IB" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="a" descr="Activity. Set if a packet lookup has hit on the specific entry.\;To clear the a bit, use &quot;clear activity&quot; op\;Reserved when Switch-IB" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: Write operation. Used to write a new entry to the table. All \;RW fields are relevant for new entry. Activity bit is cleared for \;new entries\;1: Update action. Used to update an existing route entry and \;only update the following fields:\;trap, trap_group, trap_id, \;m, mirror_dst, prio, qos\;2: Clear activity. A bit is cleared for the entry\;For Query:\;0: Read operation. \;1: clear on Read operation. Used to read entry and clear activ\;ity bit." access="OP" offset="0x0.20" size="0x0.3" />
	<field name="type" descr="Entry Type:\;0: IPv4\;1: IPv6\;For Switch-IB, the type IPv6 represents GRH, the type IPv4 is \;not supported" access="INDEX" offset="0x0.28" size="0x0.2" />
	<field name="v" descr="Valid" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="virtual_router" descr="Range is 0..cap_max_virtual_routers-1" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="dip" descr="Destination IP address.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are \;reserved.\;For Switch-IB represents destination GID" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="dip_mask" descr="Reserved when Switch-IB" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="sip" descr="Source IP address.\;IPv4 address uses bits sip[31:0] and bits sip[127:32] are \;reserved.\;Reserved when Switch-IB" access="RW" high_bound="3" low_bound="0" offset="0x30.0" size="0x10.0" />
	<field name="sip_mask" descr="Reserved when Switch-IB" access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
	<field name="trap_id" descr="Trap ID to be reported to CPU\;Bits 8:6 must be equal to 111 (binary)\;Reserved when Switch-IB" access="RW" offset="0x60.0" size="0x0.9" />
	<field name="trap_grp" descr="Trap group to use when trapping to CPU\;Reserved when Switch-IB" access="RW" offset="0x60.16" size="0x0.4" />
	<field name="trap_action" descr="0: permit\;1: soft drop\;2: trap\;3: soft drop &amp; trap\;4: deny\;Reserved when Switch-IB" access="RW" offset="0x60.28" size="0x0.4" />
	<field name="ttl_value" descr="Value to be used for TTL set / decrement\;For Switch-IB this field must have the same value for all \;entries" access="RW" offset="0x64.0" size="0x0.8" />
	<field name="ttl_cmd" descr="Time To Live (TTL) Command:\;0: Decrement - packet&apos;s TTL field will be decremented by \;ttl_value\;1: Set - packet&apos;s TTL field will be set to ttl_value\;For Switch-IB this field must have the same value for all \;entries" access="RW" offset="0x64.8" size="0x0.2" />
	<field name="qos" descr="Quality of Service:\;0: Map Prio from DSCP, see Section \;1: Preserve packet&apos;s Prio (as arrived to the router)\;For Switch-IB must be set to &apos;1&apos;" access="RW" offset="0x64.16" size="0x0.2" />
	<field name="prio" descr="Reserved when Switch-IB" access="RW" offset="0x64.20" size="0x0.3" />
	<field name="mirror_dst" descr="Mirroring destination of m bit is set\;Reserved when Switch-IB" access="RW" offset="0x64.24" size="0x0.3" />
	<field name="m" descr="Mirror enable.\;Reserved when Switch-IB" access="RW" offset="0x64.31" size="0x0.1" />
	<field name="expected_ingress_rif" descr="Expected ingress router interface, used for RPF check\;Reserved when Switch-IB" access="RW" offset="0x68.0" size="0x0.18" />
	<field name="rpf" descr="RPF Check Mode\;0: No RPF, Ignore expected_ingress_rif\;1: RPF Check Enabled - Discard\;2: RPF Check Enabled - Trap (Configured by HPKT)\;4: Directional forwarding (match only if packet is coming \;from expected_ingress_rif)\;For Switch-IB must be set to &apos;4&apos;" access="RW" offset="0x68.28" size="0x0.3" />
	<field name="assert" descr="Assert check enable\;This field is only valid when rpf is not set to Ignore or Trap.\;Reserved when Switch-IB" access="RW" offset="0x68.31" size="0x0.1" />
	<field name="egress_rif_group" descr="Egress router interface list\;Switch-IB supports range of 7:0" access="RW" high_bound="7" low_bound="0" offset="0x70.0" size="0x20.0" />
</node>

<node name="rmft_v2_ext" descr="" size="0x174.0" >
	<field name="offset" descr="Offset within the multicast forwarding table to write to.\;Reserved when Switch-IB" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="a" descr="Activity. Set for new entries. Set if a packet lookup has hit on the \;specific entry.\;Reserved when Switch-IB" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: WRITE operation. Used to write a new entry to the table. All\;R/W fields are relevant for new entry. Activity bit is set for new\;entries - Note write with v = 0 will delete the entry\;1: UPDATE action. Only action will be updated.\;2: CLEAR activity. Activity bit is cleared for the entry\;3: WRITE_CLEAR. Does WRITE with CLEAR activity \;For Query:\;0: READ operation.\;1: CLEAR_ON_READ on read operation. Used to read entry and\;clear Activity bit." access="OP" offset="0x0.20" size="0x0.3" />
	<field name="type" descr="Entry Type:\;0: Multicast IPv4\;1: Multicast IPv6\;For Switch-IB must be &apos;1&apos; (IPv6 is like GID)" access="INDEX" offset="0x0.28" size="0x0.2" />
	<field name="v" descr="Valid\;Reserved when Switch-IB" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="virtual_router" descr="Virtual Router ID\;Range from 0..cap_max_virtual_routers-1\;Reserved when Switch-IB" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="irif" descr="Ingress RIF" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="irif_m" descr="iRIF mask\;0: ignore the irif\;1: compare the irif\;For Switch-IB must be &apos;1&apos;" access="RW" offset="0x8.24" size="0x0.1" />
	<field name="dip" descr="Destination IP address.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved.\;For Switch-IB this is 128bit GID" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="dip_mask" descr="A bit that is set directs the TCAM to compare the corresponding bit \;in key. A bit that is clear directs the TCAM to ignore the corre\;sponding bit in key" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="sip" descr="Source IP address.\;IPv4 address uses bits sip[31:0] and bits sip[127:32] are reserved.\;Reserved when Switch-IB" access="RW" high_bound="3" low_bound="0" offset="0x30.0" size="0x10.0" />
	<field name="sip_mask" descr="A bit that is set directs the TCAM to compare the corresponding bit \;in key. A bit that is clear directs the TCAM to ignore the corre\;sponding bit in key\;Reserved when Switch-IB" access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
	<field name="flexible_action_set" descr="Flexible Action-Set.\;The layout of this field is the same as described in Section 10.8, \;&quot;Flexible ACL Action Set,&quot; on page 1592    while the only supported \;action types in this field and in any action-set pointed from here are \;as follows:\;00h: NULL_ACTION\;01h: MAC_TTL_ACTION, only TTL configuration is supported.\;03h: TRAP_ACTION\;04h: TRAP_W_USERDEF_ACTION\;06h: QOS_ACTION\;08h: POLICING_MONITORING_ACTION\;09h: METADATA_ACTION\;10h: ROUTER_MC_ACTION\;If goto is set then the binding_cmd must be &apos;0&apos; (none/continue), see \;Section 10.8.2.3, &quot;Goto action set,&quot; on page 1596)\;The action types are defined in Section 10.8, &quot;Flexible ACL Action \;Set,&quot; on page 1592.\;See Section 10.8.4, &quot;Flexible Action Set Blocks,&quot; on page 1602\;See Section 10.8.4.2, &quot;MAC_TTL_ACTION,&quot; on page 1602\;See Section 10.8.4.4, &quot;TRAP_ACTION,&quot; on page 1607\;See Section 10.8.4.8, &quot;QOS_ACTION,&quot; on page 1613\;See Section 10.8.4.10, &quot;POLICING_AND_COUNTING_AC\;TION,&quot; on page 1618\;See Section 10.8.4.11, &quot;META_DATA_ACTION,&quot; on page 1619\;See Section 10.8.4.13, &quot;MC_ROUTING_ACTION,&quot; on page 1625\;If the packet is not discarded by TRAP_ACTION then ROUT\;ER_MC_ACTION must be called" access="RW" high_bound="60" low_bound="0" offset="0x80.0" size="0xf4.0" />
</node>

<node name="rmftad_ext" descr="" size="0x220.0" >
	<field name="offset" descr="Offset within the multicast forwarding table\;Must be N*32" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="type" descr="Entry Type:\;0: Multicast IPv4\;1: Multicast IPv6" access="INDEX" offset="0x0.20" size="0x0.2" />
	<field name="op" descr="0: Read activity\;1: Read and clear activity" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="num_rec" descr="Number of records to read\;Range 1..4096" access="OP" offset="0x4.0" size="0x0.13" />
	<field name="activity_vector" descr="Activity per offset\;Line 20h bit 31 is for entry offset+4095\;Line 21C bit 0 is for entry offset+0\;Bits higher than num_rec are reserved\;Bits higher than region_size are reserved\;For non-valid offsets the activity is reserved" access="RO" high_bound="127" low_bound="0" offset="0x20.0" size="0x200.0" />
</node>

<node name="rmid_ext" descr="" size="0x40.0" >
	<field name="rmid_index" descr="RMID Index\;Range 0 .. max_mid - 1\;For Spectrum family, the index is to the Port Group Table, see \;Section A.4.2, &quot;Port Group Table (PGT),&quot; on page 2256" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="rmpe_index" descr="Router multicast port to ERIF Index\;When ubridge=0: Range is 0.. cap_max_rmpe - max_fid - 1\;When ubridge=1: Range is 0.. cap_max_rmpe - 1\;Reserved when egress_port is all &apos;0&apos;" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="egress_port" descr="Egress Port bitmask, \;CPU port is not supported\;Router port is not supported\;0: Do not transmit the packet to the local port\;1: Transmit the packet to the local port\;All LAG ports must share the same configuration.\;If all bits are &apos;0&apos; then the packet is discarded without error count\;ing" access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
</node>

<node name="rmid_index" descr="" size="0x4.0" >
	<field name="rmid_index" descr="" offset="0x0.0" size="0x0.16" />
</node>

<node name="rmpe_ext" descr="" size="0xc.0" >
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rmpe_index" descr="Router multicast port to ERIF\;When ubridge=0: Range is 0.. cap_max_rmpe - max_fid - 1\;When ubridge=1: Range is 0.. cap_max_rmpe - 1\;Note: when ubridge=1 the rmpe and smpe use the same range, see \;SMPE register" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="erif" descr="Egress Router Interface\;Valid range is 0..cap_max_router_interfaces - 1" access="RW" offset="0x8.0" size="0x0.16" />
</node>

<node name="rmpu_ext" descr="" size="0x110.0" >
	<field name="local_port" descr="Local port to send the packet\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="size" descr="Number of valid RMIDs to be updated.\;Range is 1 to 64" access="INDEX" offset="0x4.16" size="0x0.8" />
	<field name="op" descr="Operation\;0: Set bit\;1: Clear bit" access="WO" offset="0x4.30" size="0x0.2" />
	<field name="rmid_index" descr="RMID index to where the relevant local_port bit indication is to \;be set/cleared.\;Range 0 .. max_mid - 1" subnode="rmid_index" access="INDEX" high_bound="63" low_bound="0" offset="0x10.0" size="0x100.0" />
</node>

<node name="rom_version" descr="" size="0x4.0" >
	<field name="build" descr="Build version" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="minor" descr="Minor version" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="major" descr="Major version" access="RO" offset="0x0.24" size="0x0.8" />
</node>

<node name="router_interface_sub_port_ext" descr="" size="0x18.0" >
	<field name="system_port" descr="Port unique identifier.\;When lag bit is set, this field holds the lag_id in bits \;[9:0]\;When ubridge=1 this is the egress port only\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="lag" descr="LAG indication. When this bit is set, the system_port \;field holds the LAG identifier" access="RW" offset="0x0.24" size="0x0.1" />
	<field name="efid" descr="Egress FID\;Used to connect the erif to a bridge if erifACL has modi\;fied the DMAC or the VID\;Reserved when ubridge = 0" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="router_interface_mac_47_32" descr="Router interface MAC address.\;Note: In the SwitchX silicon family, all router interfaces \;on the same switch partition must have the same MAC \;address" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="mac_profile_id" descr="MAC msb profile ID\;range 0 .. cap_max_rif_mac_profile-1\;Reserved when Spectrum-1" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="router_interface_mac_31_0" descr="Router interface MAC address.\;Note: In the SwitchX silicon family, all router interfaces \;on the same switch partition must have the same MAC \;address" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="vid" descr="Sub-port VLAN ID\;Reserved when ubridge = 1\;" access="RW" offset="0x10.0" size="0x0.12" />
	<field name="vrrp_id_ipv4" descr="VRRP ID for IPv4\;Reserved when SwitchX/-2. The MAD address should \;be entered to the FDB" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="vrrp_id_ipv6" descr="VRRP ID for IPv6\;Reserved when SwitchX/-2. The MAD address should \;be entered to the FDB" access="RW" offset="0x14.8" size="0x0.8" />
</node>

<node name="rrcr_ext" descr="" size="0x24.0" >
	<field name="offset" descr="Offset within the region from which to copy/move." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="op" descr="Operation:\;0: move rules.\;1: copy rules." access="WO" offset="0x0.28" size="0x0.4" />
	<field name="size" descr="The number of rules to copy/move." access="WO" offset="0x4.0" size="0x0.16" />
	<field name="table_id" descr="Identifier of the table on which to perform the operation.\;Encoding is the same as in RTAR.key_type. See Section 13.13.6, \;&quot;RTAR - Router TCAM Allocation Register,&quot; on page 1937." access="INDEX" offset="0x10.0" size="0x0.4" />
	<field name="dest_offset" descr="Offset within the region to which to copy/move." access="INDEX" offset="0x20.0" size="0x0.16" />
</node>

<node name="rsnh_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Egress Local Port" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="e2d_en" descr="ERIF to DMAC mapping enable" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="dmac_47_32" descr="DMAC" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="dmac_31_0" descr="DMAC" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="rtar_tcam_ext" descr="" size="0x20.0" >
	<field name="key_type" descr="TCAM key type for the region.\;Supported router types include:\;00h: IPv4 Unicast, not supported by Spectrum\;01h: IPv4 Multicast\;02h: IPv6 Unicast, not supported by Spectrum\;03h: IPv6 Multicast\;04h: IPv4 Host Table, not supported by Spectrum\;05h: IPv6 Host Table, not supported by Spectrum\;Note: Current SwitchX and SwitchX-2 device requires allocation \;of host table resources while it might not be needed in future \;devices." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="op" descr="For Write operation\;0: ALLOCATE a TCAM region\;1: RESIZE a TCAM region\;When providing a larger size, additional entries are added at the \;end of the table (larger indexes). When providing a smaller size, \;the last entries are removed. If RESIZE operation will cause \;removal of valid entries, the operation will fail.\;2: DEALLOACTE TCAM region\;3: TEST allocation" access="WO" offset="0x0.28" size="0x0.4" />
	<field name="region_size" descr="TCAM region size. \;For op = ALLOCATE or op = RESIZE or op = TEST: this field is \;set by SW and the device returns the actual allocated size.\;Note that actual size may be larger than requested.\;Allowed range 1 .. cap_max_rules-1\;Reserved when op = DEALLOCATE" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="rtca_ext" descr="" size="0x14.0" >
	<field name="lid" descr="Base LID for the port" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="lmc" descr="LID mask count" access="RW" offset="0x0.16" size="0x0.3" />
	<field name="swid" descr="Switch partition ID - identifies the TCA port connecting the router \;to the specific SWID. Only relevant for ports connected to an \;InfiniBand switch partition." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="gid" descr="Global ID" access="RW" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
</node>

<node name="rtdp_ext" descr="" size="0x44.0" >
	<field name="tunnel_index" descr="Index to the Decap entry\;For Spectrum, Index to KVD Linear, see Section A.4.1.2, &quot;KVD \;Central Database Linear Entries,&quot; on page 2256" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="type" descr="Type of the RTDP entry:\;0: NVE\;1: IPinIP\;" access="RW" enum="NVE=0x0,IPinIP=0x1" offset="0x0.28" size="0x0.4" />
	<field name="rtdp_entry" descr="RTDP entry according to type:\;Table 2018, &quot;RTDP Entry for NVE Decap Layout,&quot; on \;page 1984\;Table 2020, &quot;RTDP Entry for IPinIP Decap Layout,&quot; on \;page 1984\;" subnode="rtdp_rtdp_entry_auto_ext" access="RW" offset="0x4.0" size="0x18.0" union_selector="$(parent).type" />
	<field name="egress_router_interface" descr="Underlay egress router interface\;Range is 0 .. cap_max_router_interfaces - 1\;Reserved when Spectrum-1\;\;" access="RW" offset="0x40.0" size="0x0.16" />
</node>

<node name="rtdp_ipinip_ext" descr="" size="0x18.0" >
	<field name="sip_check" descr="0: No sip checks \;1: filter packet if underlay is not IPv4 or if underlay SIP does \;not equal to ipv4_usip3: filter packet if underlay is not IPv6 \;or if underlay SIP does not equal to ipv6_usip\;If decapsulation failed due to these configurations then \;trap_id is IPIP_DECAP_ERROR" access="RW" offset="0x0.0" size="0x0.3" />
	<field name="irif" descr="Ingress Router Interface for the overlay router" access="RW" offset="0x0.16" size="0x0.16" />
	<field name="gre_key_check" descr="0: do not check GRE key\;1: Check GRE key\;When check is enabled:\;A packet received as IPinIP (without GRE) will always pass.\;A packet received as IPinGREinIP without a key will not \;pass the check.\;A packet received as IPinGREinIP with a key will pass the \;check only if the key in the packet is equal to expect\;ed_gre_key.\;If decapsulation failed due to GRE key then trap_id is IPIP_\;DECAP_ERROR" access="RW" offset="0x4.23" size="0x0.1" />
	<field name="type_check" descr="Bit0:\;0: do not allow IPinIP (without GRE) decapsulation\;1: allow IPinIP (without GRE) decapsulation\;Bit1:\;0: do not allow IPinGREinIP without a key decapsulation\;1: allow IPinGREinIP without a key decapsulation\;Bit2:\;0: do not allow IPinGREinIP with a key decapsulation\;1: allow IPinGREinIP with a key decapsulation\;If decapsulation failed due to these configurations then \;trap_id is IPIP_DECAP_ERROR" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="ipv4_usip" descr="Underlay IPv4 address for ipv4 source address check\;Reserved when sip_check is not &apos;1&apos;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="ipv6_usip_ptr" descr="This field is valid when sip_check is &quot;sipv6 check explic\;itly&quot;\;This is a pointer to the IPv6 DIP which is configured by \;RIPS, see Section 13.13.19, &quot;RIPS - Router IP version Six \;Register,&quot; on page 1987\;For Spectrum, the index is to the KVD linear, see \;Section A.4.1, &quot;KVD Central Database,&quot; on page 2252\;Reserved when sip_check is not &apos;2&apos; or &apos;3&apos;" access="RW" offset="0xC.0" size="0x0.24" />
	<field name="expected_gre_key" descr="GRE key for checking\;Reserved when gre_key_check is &apos;0&apos;" access="RW" offset="0x10.0" size="0x4.0" />
</node>

<node name="rtdp_nve_decap_ext" descr="" size="0x4.0" >
	<field name="decap_disable" descr="When set, disable decap. \;This is a bitwise configuration:\;Bit 0: Disable VXLAN\;Bit 1: Disable VXLAN-GPE\;Bit 2: Disable GENEVE\;Bit 3: Disable NVGRE" access="RW" offset="0x0.0" size="0x0.4" />
</node>

<node name="rtdp_rtdp_entry_auto_ext" descr="" attr_is_union="1" size="0x18.0" >
	<field name="rtdp_nve_decap_ext" descr="" subnode="rtdp_nve_decap_ext" offset="0x0.0" selected_by="NVE" size="0x4.0" />
	<field name="rtdp_ipinip_ext" descr="" subnode="rtdp_ipinip_ext" offset="0x0.0" selected_by="IPinIP" size="0x18.0" />
</node>

<node name="rtps_ext" descr="" size="0x8.0" >
	<field name="tca_phy_pstate" descr="TCA Physical Port State.\;0: No change\;1- Down\;2: Polling\;3: Up" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="tca_log_pstate" descr="TCA Logical Port State.\;0: No change\;1: Down\;2: Init\;3: Arm\;4: Active" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="swid" descr="Switch partition ID - identifies the TCA port connecting the router \;to the specific SWID. Only relevant for ports connected to an \;InfiniBand switch partition." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="switch_phy_pstate" descr="TCA Physical Port State is used to communicate the TCA logical \;port state managed by software with the switch port connected to \;it and managed by the SwitchX device.\;0: Reserved\;1: Down\;2: Polling \;3: Up" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="switch_log_pstate" descr="TCA Logical Port State.\;0: Reserved\;1: Down\;2: Init\;3: Arm\;4: Active" access="RO" offset="0x4.4" size="0x0.4" />
</node>

<node name="ruft_ext" descr="" size="0x78.0" >
	<field name="offset" descr="Offset within the Unicast FIB LPM. \;Range 0.. cap_max_router_lpm_entries-1\;When Quantum and on: Value of 0xFFFF used for default \;route" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="a" descr="Activity. Set if a packet lookup has hit on the specific entry.\;To clear the a bit, use &quot;clear activity&quot; op.\;Reserved when IB switches" access="RO" offset="0x0.16" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: Write operation. Used to write a new entry to the table. \;All RW fields are relevant for new entry. Activity bit is \;cleared for new entries\;1: Update action. Used to update an existing route entry and \;only update the following fields:\;trap, trap_group, trap_id,\;m, mirror_dst, prio, qos,\;adjacency_index, ecmp_size\;2: Clear activity. A bit is cleared for the entry\;\;For Query:\;0: Read operation. \;1: clear on Read operation. Used to read entry and clear \;Activity bit.\;Reserved when IB switches" access="OP" offset="0x0.20" size="0x0.3" />
	<field name="type" descr="Entry Type\;0: IPv4\;1: IPv6\;2: IB GID site-local" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="v" descr="Valid\;Note that clearing the valid bit will delete the entry and the \;device might not be able to hold an invalid entry properties." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="virtual_router" descr="Virtual router ID\;Range is 0..cap_max_virtual_routers-1\;Reserved when IB switches" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="dip" descr="Destination IP address\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are \;reserved.\;For type = IB GID site-local only bits 79:64 are used, other \;bits are reserved. \;The dip is related to the linear range of the offset such that:\;(dip[79:64] - offset) = const, if const is changed then the \;dip[79:64] of all entries will be updated. const is an implicit \;field.\;Note: dip[79:64] must be larger or equal to offset\;For Switch-IB the dip range is 0..(0xFFDC+offset)" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="dip_mask" descr="When type = IB GID site-local, this field is reserved" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="ecmp_hash" descr="Equal Cost Multi-Pathing Hash value\;Reserved when IB switches" access="INDEX" offset="0x54.0" size="0x4.0" />
	<field name="ecmp_hash_mask" descr="Note: ECMP Hash value is masked before used as an Index\;Reserved when IB switches" access="INDEX" offset="0x58.0" size="0x4.0" />
	<field name="trap_id" descr="Trap ID to be reported to CPU. \;trap_id must be in the range of 1C0h - 1FFh" access="RW" offset="0x60.0" size="0x0.9" />
	<field name="trap_group" descr="Trap Group to use when trapping to CPU\;Trap groups are limited to 0 - max_num_trap_groups-1\;max_num_trap_groups is provided by Section 2.15.2, \;&quot;HCAP - Host Interface Capabilities,&quot; on page 413" access="RW" offset="0x60.16" size="0x0.4" />
	<field name="trap_action" descr="0: permit\;1: soft drop\;2: trap\;3: soft drop &amp; trap\;4: deny\;Reserved when IB switches" access="RW" offset="0x60.28" size="0x0.4" />
	<field name="qos" descr="Quality of Service:\;0: Map Prio from DSCP, see Section . Not supported when \;type = IB GID site-local\;1: Preserve packet&apos;s Prio (as arrived to the router)" access="RW" offset="0x64.16" size="0x0.2" />
	<field name="prio" descr="" access="RW" offset="0x64.20" size="0x0.3" />
	<field name="mirror_dst" descr="Mirroring destination when m bit is set.\;" access="RW" offset="0x64.24" size="0x0.3" />
	<field name="m" descr="Mirror enable \;Reserved when IB switches" access="RW" offset="0x64.31" size="0x0.1" />
	<field name="egress_router_interface" descr="Egress Router Interface Index\;Reserved when table != Algo" access="RW" offset="0x70.0" size="0x0.16" />
	<field name="adjacency_index" descr="Index in the adjacency table\;Reserved when table = Algo" access="RW" offset="0x74.0" size="0x0.16" />
	<field name="table" descr="Adjacency Table:\;When Switch-X/2:\;0: Ethernet Unicast Adjacency Table\;1: IPoIB Unicast and Multicast Adjacency Table\;2: IPoIB All Routers Adjacency Table\;3: IPoIB IP Broadcast Adjacency Table\;When IB Switches:\;4: ALGO_LID. Algorithmic Routing based on DGID[15:0]. \;5: ALGO_SITE_LOCAL, Algorithmic Routing for next \;hop, based on site-local field in DGID[79:64]. Reserved \;when Switch-IB/2." access="RW" offset="0x74.16" size="0x0.3" />
	<field name="ecmp_size" descr="ECMP Group Size.\;Used for group-based ECMP to defined the number of rele\;vant paths in the ECMP group.\;Reserved when IB switches" access="RW" offset="0x74.24" size="0x0.8" />
</node>

<node name="ruht_ext" descr="" size="0x78.0" >
	<field name="offset" descr="Offset within the Unicast FIB LPM to write to. Numbered \;from 0..max_host_table-1 as defined by RATR" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="a" descr="Activity. Set if a packet lookup has hit on the specific entry.\;To clear the a bit, use &quot;clear activity&quot; op." access="RO" offset="0x0.16" size="0x0.1" />
	<field name="op" descr="Operation\;For Write:\;0: Write operation. Used to write a new entry to the table. \;All RW fields are relevant for new entry. Activity bit is \;cleared for new entries\;1: Update action. Used to update an existing route entry and \;only update the following fields:\;trap, trap_group, trap_id,\;m, mirror_dst, prio, qos\;2: Clear activity. A bit is cleared for the entry.\;\;For Query:\;0: Read operation. \;1: clear on Read operation. Used to read entry and clear \;activity bit." access="OP" offset="0x0.20" size="0x0.3" />
	<field name="type" descr="Entry Type:\;0: IPv4\;1: IPv6" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="oe" descr="Offset Enable.\;When set, the access is using the offset field.\;When cleared, the access is using the IP address.\;Note: accessing an entry using offset result in better perfor\;mance." access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="v" descr="Valid bit" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="virtual_router" descr="Range is 0..cap_max_virtual_routers-1" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="dip" descr="Destination IP address.\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are \;reserved.\;Note: This field is a RW field when accessing the entry \;using the handle." access="INDEX" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="ecmp_hash" descr="Equal Cost Multi-Pathing Hash value" access="INDEX" offset="0x54.0" size="0x4.0" />
	<field name="ecmp_hash_mask" descr="Note: ECMP Hash value is masked before used as an Index" access="INDEX" offset="0x58.0" size="0x4.0" />
	<field name="trap_id" descr="Trap ID to be reported to CPU. \;trap_id must be in the range of 1C0h - 1FFh" access="RW" offset="0x60.0" size="0x0.9" />
	<field name="trap_group" descr="Trap group to use when trapping to CPU.\;Trap groups are limited to 0 - (max_num_trap_groups-1)\;max_num_trap_groups is provided by Section 2.15.2, \;&quot;HCAP - Host Interface Capabilities,&quot; on page 413" access="RW" offset="0x60.16" size="0x0.4" />
	<field name="trap_action" descr="0: permit\;1: soft drop\;2: trap\;3: soft drop &amp; trap\;4: deny" access="RW" offset="0x60.28" size="0x0.4" />
	<field name="qos" descr="Quality of Service\;0: Map Prio from DSCP, see Section \;1: Preserve packet&apos;s Prio (as arrived to the router)" access="RW" offset="0x64.16" size="0x0.2" />
	<field name="prio" descr="" access="RW" offset="0x64.20" size="0x0.3" />
	<field name="mirror_dst" descr="Mirroring destination of m bit is set\;" access="RW" offset="0x64.24" size="0x0.3" />
	<field name="m" descr="Mirror Enable\;" access="RW" offset="0x64.31" size="0x0.1" />
	<field name="adjacency_index" descr="Index to the adjacency table." access="RW" offset="0x74.0" size="0x0.16" />
	<field name="table" descr="Adjacency Table\;0: Ethernet Unicast Adjacency Table\;1: IPoIB Unicast and Multicast Adjacency Table\;2: IPoIB All Routers Adjacency Table\;3: IPoIB IP Broadcast Adjacency Table" access="RW" offset="0x74.16" size="0x0.3" />
	<field name="ecmp_size" descr="ECMP Group Size\;Used for Group-based ECMP to defined the number of rele\;vant paths in the ECMP group" access="RW" offset="0x74.24" size="0x0.8" />
</node>

<node name="rxltcc_ext" descr="" size="0x68.0" >
	<field name="clear" descr="clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="hit_ipv4_m_high" descr="Counts hit on IPv4 M lookups\;Count only when no need to continue ML lookup\;Thus a hit on M may be counted as hit on ML" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="hit_ipv4_m_low" descr="Counts hit on IPv4 M lookups\;Count only when no need to continue ML lookup\;Thus a hit on M may be counted as hit on ML" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="hit_ipv4_ml_high" descr="Counts hit on IPv4 ML lookups\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="hit_ipv4_ml_low" descr="Counts hit on IPv4 ML lookups\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="miss_ipv4_m_high" descr="Counts misses on IPv4 M lookups\;If there was an IPv4 ML lookup then this is not counted" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="miss_ipv4_m_low" descr="Counts misses on IPv4 M lookups\;If there was an IPv4 ML lookup then this is not counted" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="miss_ipv4_ml_high" descr="Counts misses on IPv4 ML lookups\;Note: a miss on ML is counted only if there was a hit on the M" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="miss_ipv4_ml_low" descr="Counts misses on IPv4 ML lookups\;Note: a miss on ML is counted only if there was a hit on the M" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="learned_ipv4_high" descr="Counts learned IPv4 lookups\;Typically the learned is equal or smaller than the miss" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="learned_ipv4_low" descr="Counts learned IPv4 lookups\;Typically the learned is equal or smaller than the miss" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="hit_ipv6_m_high" descr="Counts hit on IPv6 M lookups\;(See notes above)" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="hit_ipv6_m_low" descr="Counts hit on IPv6 M lookups\;(See notes above)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="hit_ipv6_ml_high" descr="Counts hit on IPv6 ML lookups\;(See notes above)" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="hit_ipv6_ml_low" descr="Counts hit on IPv6 ML lookups\;(See notes above)" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="miss_ipv6_m_high" descr="Counts misses on IPv6 M lookups\;(See notes above)\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="miss_ipv6_m_low" descr="Counts misses on IPv6 M lookups\;(See notes above)\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="miss_ipv6_ml_high" descr="Counts misses on IPv6 ML lookups\;(See notes above)" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="miss_ipv6_ml_low" descr="Counts misses on IPv6 ML lookups\;(See notes above)" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="learned_ipv6_high" descr="Counts learned IPv6 lookups\;(See notes above)" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="learned_ipv6_low" descr="Counts learned IPv6 lookups\;(See notes above)" access="RO" offset="0x64.0" size="0x4.0" />
</node>

<node name="rxlte_ext" descr="" size="0xc.0" >
	<field name="virtual_router" descr="Virtual router ID associated with the router interface\;Range is 0..cap_max_virtual_routers-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="protocol" descr="Protocol:\;0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="lpm_xlt_en" descr="LPM XLT Enable:\;0: disable (default)\;1: enable" access="RW" offset="0x8.0" size="0x0.4" />
</node>

<node name="rxltm_ext" descr="" size="0x14.0" >
	<field name="m_sel" descr="M select: \;0: m0\;1: m1\;Note: update time is a few mSec. \;When m_sel is updated then SW must set go_m_sel .\;" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="go_m_sel" descr="Go m select:\;Set to 1 by SW when m_select value is changed by SW.\;Set to 0 by FW when m_select change was implemented.\;If go_m_sel=1 then NACK\;Note: during change of m_sel SW must not delete XLT entries with \;old m value." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="m_sel_update" descr="0: Update all fields\;1: Update only go_m_sel, m_sel" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="m0_val_v4" descr="Global M0 value For IPv4\;Range 0..32" access="RW" offset="0x10.0" size="0x0.6" />
	<field name="m1_val_v4" descr="Global M1 value For IPv4\;Range 0..32" access="RW" offset="0x10.8" size="0x0.6" />
	<field name="m0_val_v6" descr="Global M0 value For IPv6\;Range 0..128" access="RW" offset="0x10.16" size="0x0.8" />
	<field name="m1_val_v6" descr="Global M1 value For IPv6\;Range 0..128" access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="sbcam_ext" descr="" size="0x4c.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First 128 REG_ID" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index\;0: Enhanced features" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sb_access_reg_cap_mask" descr="Supported Shared Buffer access register bitmasks. Based on \;access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: SBPR_(0xB001)\;Bit 2: SBCM_(0xB002)\;Bit 3: SBPM_(0xB003)\;Bit 5: SBSR_(0xB005)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="sb_feature_cap_mask" descr="Supported Shared Buffer enhanced features based on feature_group \;index.\;When bit is set, the feature is supported in the device\;Bit 0: descriptors_cap - (desc) is supported \;Bit 1: ext_buff_occupancy_cap - is supported \;Bit 2: exclude_cap - bit is supported\;Bit 3: sb_own_res - user can configure ePort per tc shared buffer \;configuration    \;Bit 4: sb_global_res - user can configure ePort, iPort and iPort per \;pg shared buffer configuration  " access="RO" enum="descriptors_cap=0x1,ext_buff_occupancy_cap=0x2,exclude_cap=0x4,sb_own_res=0x8,sb_global_res=0x10" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
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
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class: range is 0..cap_max_tclass - 1\;For traffic class to CPU port: range is 0..cap_max_cpu_in\;gress_tclass- 1\;\;For Spectrum-1 MC packets: no admission on Tx.Tclass, so \;when traffic class is in MC aware mode then the traffic classes \;which are MC aware must not be configured, but can be read. \;Spectrum-2 has admission on Tx.Tclass so all traffic classes can \;be configured also for MC aware mode. \;see Section 11.5, &quot;Ethernet Switch Packet Priority and TClass \;Mapping,&quot; on page 1764\;\;" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="local_port" descr="Local port number\;For Ingress: excludes CPU port\;For Egress: includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;Reserved when Spectrum-1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="exc" descr="Exclude - no accounting in the pool\;0: the tclass is accounted in the pool (default)\;1: the tclass is not accounted in the pool \;Reserved when Spectrum-1, supported by Spectrum-2. \;Note: currenty not supported by Switch FW\;\;" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy\;This includes cells at the pool and at the min_buff" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. \;This includes cells at the pool and at the min_buff\;Cleared by writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared \;(and a new max value is tracked from the time the clear was per\;formed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size for the limiter\;The minimum buffer is not part of the pool area.\;Units of cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="The maximum buffer threshold in the pool area.\;When the pool that is associated to the port-pg/tclass is config\;ured to static, then max_buff is configured in cells\;When the pool that is associated to the port-pg/tclass is config\;ured to dynamic, then max_buff holds the &quot;alpha&quot; parameter, \;supporting the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1\;[Advanced] When: (1) dir=Ingress and (2) desc=1 and (3) the \;PG is lossless then the max_buff must not be &apos;0&apos;, both for static \;and dynamic modes\;" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool\;Range 0 .. cap_num_pool_supported - 1\;[Advanced] exposed supported: pools 0..8\;[Advanced] actual supported: pools 0..15, pool 13 is used for \;FW pool swap, pool 14 is used for desc, pool 15 is used for MC" access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbctc_ext" descr="" size="0x14.0" >
	<field name="mode" descr="Mode of threshold:\;0: Fixed\;1: Percentage\;Reserved when Spectrum-1 and Quantum\;" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="res" descr="When SBGCR.tele_entity = BOTH then resolution index:\;0: TCLASS\;1: PORT\;Reserved (has no meaning) when SBGCR.tele_entity != 2 \;(BOTH)\;" access="INDEX" offset="0x0.4" size="0x0.1" />
	<field name="local_port" descr="Local port number for egress sport\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dir_ing" descr="Direction\;0: Egress Tclass\;1: Ingress PG\;Reserved when Spectrum-1" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="event" descr="Event generation on crossing thr max for this port:\;0: NO_EVENT - Do not generate event\;1: EVENTS - Generate events for crossing up and down\;Not configured when en_config = 0" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="en_config" descr="Enable configuration of all fields except event field" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="tclass_en_high" descr="TClass/PG Trap enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits when SBGCR.tele_entity = PORT: bit0 (all tclasses), \;else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tclass_en_low" descr="TClass/PG Trap enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits when SBGCR.tele_entity = PORT: bit0 (all tclasses), \;else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="thr_max" descr="Threshold max\;When an egress port TClass crosses the threshold (cross up or \;down) then the HW will emit an event of SB_CONG_TX_PORT \;and the status can be read by SBCTR\;For Quantum and Spectrum-2: When an egress port TClass/PG \;crosses the threshold then congestion mirror is enabled\;\;When congestion mode is Fixed:\;- Cells. Valid inputs are 1..cap_total_buffer_size/cap_cell_size\;When congestion mode is Percentage:\;- Percentage of the quota of local_port,traffic_class. Range is \;0,..100, units of integer percentage.\;\;Written only if en_config = 1\;\;" access="RW" offset="0x10.0" size="0x0.24" />
</node>

<node name="sbctr_ext" descr="" size="0x10.0" >
	<field name="entity" descr="Entity type:\;0: TCLASS\;1: PORT\;This field represents the value configured by SBGCR.tele_entity" access="RO" offset="0x0.0" size="0x0.2" />
	<field name="fp" descr="False Positive\;When a trap: this is a false positive trap\;Reserved when Switch-IB/2, Quantum and Spectrum-2/-3" access="RO" offset="0x0.4" size="0x0.1" />
	<field name="dir_ing" descr="Direction\;0: Egress Tclass\;1: Ingress PG\;Reserved when Spectrum-1" access="INDEX" offset="0x0.8" size="0x0.2" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ievent" descr="Invoke event \;0: Read only\;1: Does both reading and invoke an event of type SB_CON\;G_TX_PORT" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="tclass_vector_high" descr="Tclass vector\;Each bit represents corresponding tclass\;0: Tclass is below the congestion threshold\;1: Tclass is above the congestion threshold\;Note that a TClass which is disabled from threshold will always \;be below the congested threshold. See SBCTC\;Valid bits when entity = PORT: bit0 (all tclasses), else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="tclass_vector_low" descr="Tclass vector\;Each bit represents corresponding tclass\;0: Tclass is below the congestion threshold\;1: Tclass is above the congestion threshold\;Note that a TClass which is disabled from threshold will always \;be below the congested threshold. See SBCTC\;Valid bits when entity = PORT: bit0 (all tclasses), else:\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="sbcts_ext" descr="" size="0x14.0" >
	<field name="clear" descr="Clear counter\;0: Do not clear\;1: Clear the counter" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="trap_overflow_counter" descr="Trap Overflow Counter\;Counts how many congestion traps (SB_CONG_TX_PORT) \;were not invoked by the device due to trap overflow\;Counter is sticky when reaching 2^24-1" access="RO" offset="0x10.0" size="0x0.24" />
</node>

<node name="sbdcc_ext" descr="" size="0x210.0" >
	<field name="clr" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="no_buffer_discard_cpu_tclass" descr="Count the number of unicast packets to CPU dropped due to \;lack of shared buffer resources\;For tclass i\;Range is 0.. cap_max_cpu_ingress_tclass-1\;See Table 1173, &quot;SBDCC - counter Layout,&quot; on page 1307" subnode="uint64" access="RO" high_bound="63" low_bound="0" offset="0x10.0" size="0x200.0" />
</node>

<node name="sbdcm_ext" descr="" size="0x14.0" >
	<field name="counter_index" descr="Counter Index for flow counters, counting no buffer discard per \;switch priority.\;For Spectrum-2: reserves counter range at size of cap_max\;_switch_priorities+1 \;Each entry is per switch priority from 0 to cap_max\;_switch_priorities-1\;For Spectrum: See Section 4.1, &quot;Performance and Monitoring \;Counters,&quot; on page 621\;Not supported by SwitchX/-2 and Spectrum-1" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;default: type=0 (disabled)\;Not supported by SwitchX/-2 and Spectrum-1" access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="sbdcr_ext" descr="" size="0x14.0" >
	<field name="counter_index" descr="Counter Index for flow counters, counting no buffer discard per \;switch priority.\;Reserves a counter range of num_ports*num_PGs:\;PG 0..7 - PGs\;PG 8 - Control PG\;PG 9 - Mirror PG\;PG 10 - egress-traps, reserved when Spectrum-2 \;\;For Spectrum: See Section 4.1, &quot;Performance and Monitoring \;Counters,&quot; on page 621\;Not supported by SwitchX/-2 and Spectrum-1" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum-2: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622\;default: type=0 (disabled)\;Not supported by SwitchX/-2 and Spectrum-1" access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="sbgcr_ext" descr="" size="0x4.0" >
	<field name="tele_entity" descr="Telemetry entity type:\;0: TCLASS\;1: PORT\;2: BOTH - support both TCLASS and PORT. Indexed by \;SBCTC.res \;Note: change of this field is allowed only when congestion \;threshold is disabled on all ports and tclasses, see SBCTC\;Reserved when Spectrum/-2" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="cong_fp" descr="Congestion false positive\;For Tclass Congestion:\;0: False Negative - allow trap and rules only for congested \;Tclass. Response may be delayed by a few uSec\;1: False Positive - allow fp-trap and rules for all Tclasses, con\;verging over time to only congested Tclasses. Provided immedi\;ate response \;Reserved when SwitchX/-2, Switch-IB/2, Quantum and Spec\;trum-2/-3" access="RW" offset="0x0.4" size="0x0.1" />
</node>

<node name="sbhbr_ext" descr="" size="0x1c.0" >
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="opcode" descr="Opcode:\;0: Bind a hist_id\;1: Unbind a hist_id (default)" access="RW" offset="0x0.28" size="0x0.4" />
	<field name="hist_id" descr="Histogram id to bind\;from 0 to cap_max_queue_hist_id - 1" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="hist_type" descr="0x1000: Queue_Depth_Traffic_Class\;See Table 1181, &quot;SBHBR - Histograms Hist-type for queue histo\;grams,&quot; on page 1312" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="hist_parameters" descr="According to hist_type\;See Table 1181, &quot;SBHBR - Histograms Hist-type for queue histo\;grams,&quot; on page 1312" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="hist_min_value" descr="Min value for histogram main range\;Units according to the units of the hist_type" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="hist_max_value" descr="Max value for histogram main range\;Note: for Spectrum device, hist_group=1 this rule must be meet:\;hist_max_value = hist_min_value + 2^n, n &gt;= 3\;Units according to the units of the hist_type" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="sample_time" descr="Sample time interval. \;Allowed range:\;time = 2^sample_time * 128nSec\;sample_time range is 0..cap_max_sample_time-1\;Note: for Spectrum the sample_time is global for all ports and all \;tclass \;For Spectrum-2 the sample_time is per port.tclass." access="RW" offset="0x18.0" size="0x0.6" />
</node>

<node name="sbhbr_v2_ext" descr="" size="0x1c.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota\;Reserved when hist_type = Queue_Latency and this field is \;treated as &apos;1&apos; Egress port quota\;" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class, hist_type of Queue_Depth_Traffic_Class: range \;is 0..cap_max_tclass - 1\;For traffic class, hist_type of Queue_Latency: range is 0..cap_\;max_tclass_data - 1\;For traffic class to CPU port: range is 0..cap_max_cpu_in\;gress_tclass- 1\;For Spectrum: no admission on Tx.Tclass, so when traffic class is \;in MC aware mode then the traffic classes which are MC aware \;must not be configured, but can be read. Spectrum-2 has admis\;sion on Tx.Tclass so all traffic classes can be configured also for \;MC aware mode. \;see Section 11.5, &quot;Ethernet Switch Packet Priority and TClass \;Mapping,&quot; on page 1764\;" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="local_port" descr="Local port number.\;For Ingress: excludes CPU port and Router port\;For Egress: excludes IP Router\;For Egress hist_type of Queue_Latency: exludes also CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="en" descr="When hist_type = Queue_Depth_Traffic_Class:\;Enable the histogram\;When hist_type = Queue_Latency:\;This is a WO for clearing the histograms and the counters" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="hist_type" descr="0x1000: Queue_Depth_Traffic_Class\;0x1002: Queue_Latency\;See Table 1181, &quot;SBHBR - Histograms Hist-type for queue histo\;grams,&quot; on page 1312" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="mode" descr="mode\;0: Linear histogram\;1: Exponential histogram" access="RW" offset="0x8.28" size="0x0.3" />
	<field name="hist_min_value" descr="Min value for histogram main range\;Units according to the units of the hist_type" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="hist_max_value" descr="Max value for histogram main range\;When mode=0 (linear), then this rule must be meet:\;hist_max_value = hist_min_value + 2^n, n &gt;= 3\;When mode=1 (exponential), then this rule must be meet:\;hist_max_value = hist_min_value + 255*2^n, n &gt;= 0\;Units according to the units of the hist_type" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="sample_time" descr="Sample time interval. \;Allowed range:\;time = 2^sample_time * 128nSec\;sample_time range is 0..cap_max_sample_time-1\;For Spectrum-1 the sample_time is global for all ports and all \;tclass \;For Spectrum-2 the sample_time is per port.tclass. \;Reserved when hist_type = Queue_Latency" access="RW" offset="0x18.0" size="0x0.6" />
</node>

<node name="sbhpc_ext" descr="" size="0x24.0" >
	<field name="max_buff" descr="Maximum SHP (Shared Headroom Pool) size. \;Default:0\;When max_buff&gt;0 then ports which have PBMC.shp_max\;_loan&gt;0 may use the SHP" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="buff_occupancy" descr="Current SHP occupancy\;" access="RO" offset="0x20.0" size="0x0.24" />
</node>

<node name="sbhrr_ext" descr="" size="0x60.0" >
	<field name="clr" descr="Clear:\;0: Read the data in the histogram agent\;1: Read and clear the data in the histogram agent" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="hist_id" descr="see SBHBR" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="bin" descr="Value of bin \;Units according to the units of the hist_type which is used for the \;hist_id\;Max bins is according to cap_hist_num_bins\;Bin is saturated at (2^cap_hist_bin_size_type1-1). When any bin \;is saturated all bins stop incrementing.\;See Table 1186, &quot;SBHRR - Bin Layout,&quot; on page 1313" subnode="uint64" access="RO" high_bound="9" low_bound="0" offset="0x10.0" size="0x50.0" />
</node>

<node name="sbhrr_v2_ext" descr="" size="0x90.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota\;Reserved when hist_type = Queue_Latency and this field is \;treated as &apos;1&apos; Egress port quota" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pg_buff" descr="PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)\;For PG buffer: range is 0..cap_max_pg_buffers - 1\;For traffic class: range is 0..cap_max_tclass - 1\;For traffic class to CPU port: range is 0..cap_max_cpu_ingress_t\;class- 1\;See Section 11.5, &quot;Ethernet Switch Packet Priority and TClass \;Mapping,&quot; on page 1764" access="INDEX" offset="0x0.8" size="0x0.6" />
	<field name="local_port" descr="Local port number.\;For Ingress: excludes CPU port\;For Egress: includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clr" descr="Clear:\;0: Read the data in the histogram agent\;1: Read and clear the data in the histogram agent" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="hist_type" descr="0x1000: Queue_Depth_Traffic_Class\;0x1002: Queue_Latency\;See Table 1181, &quot;SBHBR - Histograms Hist-type for queue histo\;grams,&quot; on page 1312" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="min_sampled_high" descr="min_sampled\;Cleared when clr = 1, cleared to 0xffff_ffff_ffff_ffff\;Units according to the units of the hist_type which is used for the \;hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="min_sampled_low" descr="min_sampled\;Cleared when clr = 1, cleared to 0xffff_ffff_ffff_ffff\;Units according to the units of the hist_type which is used for the \;hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="max_sampled_high" descr="max_sampled\;Cleared when clr = 1, cleared to 0\;Units according to the units of the hist_type which is used for the \;hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="max_sampled_low" descr="max_sampled\;Cleared when clr = 1, cleared to 0\;Units according to the units of the hist_type which is used for the \;hist_id\;Reserved when hist_type = Queue_Depth_Traffic_Class" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="bin" descr="Value of bin \;Units according to the units of the hist_type which is used for the \;hist_id\;Max bins is according to cap_hist_num_bins.\;Bin is saturated at (2^cap_hist_bin_size_type1-1). When any bin \;is saturated all bins stop incrementing.\;See Table 1192, &quot;SBHRR_V2 - Bin Layout,&quot; on page 1319" subnode="uint64" access="RO" high_bound="9" low_bound="0" offset="0x40.0" size="0x50.0" />
</node>

<node name="sbib_ext" descr="" size="0x10.0" >
	<field name="int_buffer_index" descr="Internal Buffer Index \;Spectrum supports only 1 index per port with value of 0" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port\;Not supported for Router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="status" descr="Status:\;0: the internal buffer status is not yet at the size of buff_size\;1: the internal buffer status is equal to buff_size" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="buff_size" descr="Buffer size\;Units represented in cells\;Allowed range is 0 to (cap_max_headroom_size - 1)\;Default is 0" access="RW" offset="0x8.0" size="0x0.24" />
</node>

<node name="sbme_ext" descr="" size="0x28.0" >
	<field name="local_port" descr="Local port number for egress ports\;Includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool\;[Advanced] exposed supported: pools 0..8\;[Advanced] actual supported: pools 0..15, pool 13 is used for \;FW pool swap, pool 14 is used for desc, pool 15 is used for MC\;[Advanced] default for desc is pool 14\;[Advanced] default for non-desc is pool 15" access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbmm_ext" descr="" size="0x28.0" >
	<field name="prio" descr="Switch Priority" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;Reserved when Spectrum-1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared by \;writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared \;(and a new max value is tracked from the time the clear was per\;formed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size for the limiter, in cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="When the pool associated to the port-pg/tclass is configured to \;static, Maximum buffer size for the limiter configured in cells.\;When the pool associated to the port-pg/tclass is configured to \;dynamic, the max_buff holds the &quot;alpha&quot; parameter, supporting \;the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
	<field name="pool" descr="Association of the port-priority to a pool" access="RW" offset="0x24.0" size="0x0.4" />
</node>

<node name="sbpm_ext" descr="" size="0x20.0" >
	<field name="dir" descr="Direction\;0: Ingress port quota\;1: Egress port quota" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="pool" descr="The pool associated to quota counting on the local_port\;Range 0 .. cap_num_pool_supported - 1\;[Advanced] exposed supported: pools 0..8\;[Advanced] actual supported: pools 0..15, pool 13 is used for \;FW pool swap, pool 14 is used for desc, pool 15 is used for MC" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="Local port number\;For Ingress: excludes CPU port\;For Egress: includes CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;Reserved when Spectrum-1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="buff_occupancy" descr="Current buffer occupancy of the port.pool \;This includes cells at the pool and at the min_buff" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. \;This includes cells at the pool and at the min_buff\;Cleared by writing to the clr field" access="RO" offset="0x14.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, max_buff_occupancy field is cleared (and \;a new max value is tracked from the time the clear was per\;formed)" access="OP" offset="0x14.31" size="0x0.1" />
	<field name="min_buff" descr="Minimum buffer size\;The minimum buffer is not part of the pool area.\;Units of cells" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="max_buff" descr="The maximum buffer threshold in the pool area.\;When the pool is configured to static, then max_buf is config\;ured in cells.\;When the pool is configured to dynamic, then max_buff holds \;the &quot;alpha&quot; parameter, supporting the following values:\;0 : 0\;i : (1/128)*2^(i-1), for i=1..14\;0xFF: Infinity\;Reserved when infi_max = 1\;[Advanced] When: (1) dir=Ingress and (2) desc=1 and (3) the \;pool is associated from a lossless PG then the max_buff must \;not be &apos;0&apos;, both for static and dynamic modes\;" access="RW" offset="0x1C.0" size="0x0.24" />
	<field name="infi_max" descr="Max buffer is infinite\;When set, the max_buff field is reserved" access="RW" offset="0x1C.31" size="0x0.1" />
</node>

<node name="sbpr_ext" descr="" size="0x18.0" >
	<field name="pool" descr="Pool index\;Range 0 .. cap_num_pool_supported - 1\;[Advanced] exposed supported: pools 0..8\;[Advanced] actual supported: pools 0..15, pool 13 is used for \;FW pool swap, pool 14 is used for desc, pool 15 is used for MC" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="dir" descr="Direction\;0: Ingress pools\;1: Egress pools" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="snap" descr="Read the snapshot guage\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;Reserved when Spectrum-1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;For Spectrum-1: Total 84960 descriptors\;" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="Pool size in buffer cells\;Reserved when infi_size = 1\;[Advanced] When: (1) dir=Ingress and (2) desc=1 and (3) a \;lossless PG is associating to this pool then the size must not be \;&apos;0&apos;" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="infi_size" descr="size is infinite\;When set, the size field is reserved" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="mode" descr="Pool quota calculation mode:\;0: Static\;1: Dynamic" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0xC.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared by \;writing to the clr field" access="RO" offset="0x10.0" size="0x0.24" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared \;(and a new max value is tracked from the time the clear was per\;formed)" access="OP" offset="0x10.31" size="0x0.1" />
	<field name="ext_buff_occupancy" descr="Extended current buffer occupancy\;Includes also all of the min_buff of the relevant PG buffer or \;traffic class associated to this pool\;Reserved when Spectrum-1, supported by Spectrum-2 and \;Quantum. Note: currenty not supported by Switch FW\;ext_buff_occupancy" access="RO" offset="0x14.0" size="0x0.24" />
</node>

<node name="sbsns_ext" descr="" size="0x18.0" >
	<field name="status" descr="Snapshot status:\;0: RELEASED - snapshot is non-active\;1: LOCKED - snapshot is active\;" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="trigger_id" descr="Tells which trigger id has trigger the snapshot.\;See encoding of type in Table 1151, &quot;Shared Buffer Snapshot \;triggers,&quot; on page 1283" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="trigger_parameters" descr="Trigger parameters.\;See encoding according to Table 1151, &quot;Shared Buffer Snapshot \;triggers,&quot; on page 1283" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="time_high" descr="Snapshot time:\;The time when the last snapshot was taken as free_running_\;clock\;" access="RO" offset="0x10.0" size="0x0.6" />
	<field name="time_low" descr="Snapshot time:\;The time when the last snapshot was taken as free_running_\;clock\;" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="sbsnt_ext" descr="" size="0x4.0" >
	<field name="take" descr="Take snapshot:\;0: RELEASE - release snapshot\;1: TAKE_AND_TRAP - take snapshot of the guages and invoke \;trap SB_SNAPSHOT \;2: TAKE_NO_TRAP - take snapshot of the guages without \;invoking a trap\;When snapshot status is LOCKED then the TAKE will be \;ignored\;When snapshot status is RELEASED then the RELEASE will \;be ignored\;See SBSNS.status" access="OP" offset="0x0.0" size="0x0.2" />
</node>

<node name="sbsnte_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="type" descr="Type:\;0x20: WRED, egress, no CPU port\;0x31: Shared-buffer-per-Tclass, egress\;0x32: Shared-buffer-per-Tclass-descriptors, egress [advanced]\;0x40: ING-CONG, ingress\;0x50: EGR-CONG, egress\;See Table 1151, &quot;Shared Buffer Snapshot triggers,&quot; on page 1283" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="tclass_en_high" descr="TClass/PG snapshot trigger enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tclass_en_low" descr="TClass/PG snapshot trigger enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="sbsr_ext" descr="" size="0x41c.0" >
	<field name="ports" descr="Ports:\;0: read per pg_buff and/or tclass\;1: ports, read per port\;" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="snap" descr="Read the snapshot gauge\;0: FREE - read free running buff_occupancy\;1: SNAP - read snapshot of the buff_occupancy\;When SBSNR.status is RELEASED then the device will \;NACK the command\;Reserved when Spectrum-1" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Clear Max Buffer Occupancy\;When this bit is set, the max_buff_occupancy field is cleared \;(and a new max value is tracked from the time the clear was per\;formed)" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Descriptor buffer\;" access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="ingress_port_mask" descr="Bit vector for all ingress network port.\;Indicates which of the ports (for which the relevant bit is set) are \;affected by the set operation. Configuration of any other port \;does not change." access="INDEX" high_bound="7" low_bound="0" offset="0x10.0" size="0x20.0" />
	<field name="pg_buff_mask" descr="Bit vector for all priority groups.\;Indicates which of the priorities (for which the relevant bit is \;set) are affected by the set operation. Configuration of any other \;priority does not change.\;Range is 0..cap_max_pg_buffers - 1\;Reserved when ports = 1" access="INDEX" offset="0x30.0" size="0x0.10" />
	<field name="egress_port_mask" descr="Bit vector for all egress network port.\;Indicates which of the ports (for which the relevant bit is set) are \;affected by the set operation. Configuration of any other port \;does not change." access="INDEX" high_bound="7" low_bound="0" offset="0x34.0" size="0x20.0" />
	<field name="tclass_mask" descr="Bit vector for all traffic classes.\;Indicates which of the traffic classes (for which the relevant bit \;is set) are affected by the set operation. Configuration of any \;other priority does not change.\;Range is 0..cap_max_tclass - 1\;For traffic class to CPU port: range is 0..cap_max_cpu_in\;gress_tclass- 1\;Reserved when ports = 1" subnode="uint64" access="INDEX" offset="0x54.0" size="0x8.0" />
	<field name="shared_buffer_status" descr="Shared Buffer Properties, see Table 1168, &quot;Shared Buffer Status \;Fields,&quot; on page 1305\;This field is a collection of all the statuses of the requested quo\;tas, while i=0..min{requested quotas, cap_sbsr_stat_size-1}\;The ith status refers a quota as follows;\;The occurrences of the masked ingress quotas are written before \;the masked egress quotas.\;All the occurrences associated to port are written together from \;the smallest masked port index. In each port, the occurrences of \;the masked priority groups/ traffic classes are written from the \;lowest to the highest." subnode="shared_buffer_status" access="RO" high_bound="119" low_bound="0" offset="0x5C.0" size="0x3c0.0" />
</node>

<node name="sfd_ext" descr="" size="0x410.0" >
	<field name="rec_type" descr="Record type:\;0: records are 16B\;1: records are 32B\;Reserved when SwitchX/-2" access="OP" offset="0x0.20" size="0x0.1" />
	<field name="swid" descr="Switch partition ID for queries\;Reserved on Write\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="record_locator" descr="Used for querying the FDB. Use record_locator=0 to initiate the \;query. When a record is returned, a new record_locator is returned \;to be used in the subsequent query.\;Reserved when database update." access="INDEX" offset="0x4.0" size="0x0.30" />
	<field name="op" descr="Operation.\;For Query:\;0: SFD_DUMP - dump entire FDB (process according to \;record_locator)\;1: SFD_QUERY - query records by {MAC, VID/FID} value\;2: SFD_QUERY_AND_CLEAR_ACTIVITY - query and clear \;activity. Query records by {MAC, VID/FID} value. Not supported \;by SwitchX and SwitchX2.\;For Write:\;0: SFD_TEST - Response indicates if each of the records could be \;added to the FDB. Test operation is not supported by Spectrum\;1: SFD_EDIT - add/modify. Aged-out records cannot be added. \;This command removes the learning notification of the {MAC, \;VID/FID}. Response includes the entries that were added to the \;FDB.\;2: SFD_REMOVE - remove record by {MAC, VID/FID}. This \;command also removes the learning notification and aged-out noti\;fications of the {MAC, VID/FID}. The response provides current \;(pre-removal) entries as non-aged-out." access="OP" enum="SFD_TEST=0x0,SFD_EDIT=0x1,SFD_REMOVE=0x2" offset="0x4.30" size="0x0.2" />
	<field name="num_rec" descr="Request: Number of records to read/add/modify/remove\;Response: Number of records read/added/replaced/removed\;See above description for more details.\;For rec_type = 0: Range 0..64\;For rec_type = 1: Range 0..32" access="OP" offset="0x8.0" size="0x0.8" />
	<field name="records" descr="For rec_type = 0, see Section 737, &quot;SFD - Records type0 Layout,&quot; \;on page 862\;For rec_type = 1, see Section 739, &quot;SFD - Records type1 Layout,&quot; \;on page 864" access="RW" high_bound="255" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="sfdat_ext" descr="" size="0x8.0" >
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="age_time" descr="Aging time in seconds\;Range: 10.. 1,000,000 seconds\;Default is 300 seconds\;" access="RW" offset="0x4.0" size="0x0.20" />
</node>

<node name="sfdb_ext" descr="" size="0x48.0" >
	<field name="update_type" descr="Update type:\;0: Update Multicast_Tunnel_FDB_record.underlay_mc_ptr and \;ecmp_size\;1: Update Multicast_FDB_record.mid and Update Multicast\;_Tunnel_FDB_record.mid\;2: Update Unicast_Tunnel_FDB_record.uip_lsb (the pointer to \;the generic L2 encapsulation entry) and ecmp_size\;3: Update counter_set_type, counter_index for all FDB Record \;Types\;4: Update Multicast_Tunnel_FDB_UC_DMAC.underlay_mc_ptr \;and ecmp_size. For Multicast_Tunnel_FDB_record entries where \;the DMAC is a UC DMAC (bit40=&apos;0&apos;)\;5: Update Multicast_Tunnel_FDB_MC_DMAC.under\;lay_mc_ptr and ecmp_size\;\;Explanation:\;- Multicast_Tunnel_FDB_UC_DMAC is Multicast_Tunnel_FD\;B_record entries where the DMAC is a UC DMAC (bit40=&apos;0&apos;)\;- Multicast_Tunnel_FDB_MC_DMAC is Multicast_Tunnel_FD\;B_record entries where the DMAC is a non-UC DMAC \;(bit40!=&apos;0&apos;)\;\;See Section 6.2.17, &quot;FDB Records,&quot; on page 810" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="entry_fid" descr="Update only if FID has value of entry_fid\;Range 1..cap_fid-1\;" access="INDEX" offset="0xC.0" size="0x0.16" />
	<field name="gfid" descr="Global fid.\;Update for all fids, ignore the entry_fid field," access="INDEX" offset="0xC.31" size="0x0.1" />
	<field name="parameter" descr="For update_type = 0:\;- Multicast_Tunnel_FDB_record.underlay_mc_ptr (24bits)\;For update_type = 1:\;- Multicast_FDB_record.mid (16bits)\;- Multicast_Tunnel_FDB_record.mid (16bits)\;For update_type = 2:\;Update Unicast_Tunnel_FDB_record.uip_lsb (24bits)\;For update_type = 3, 6, 7, 8:\;- bits 31:24: counter_set_type (8bit)\;- bits 23:0: counter_index (24bit)" access="INDEX" offset="0x20.0" size="0x4.0" />
	<field name="parameter1" descr="For update_type = 0:\;- Multicast_Tunnel_FDB_record.ecmp_size (13bits)\;For update_type = 2:\;- Unicast_Tunnel_FDB_record.ecmp_size (13bits)" access="INDEX" offset="0x24.0" size="0x4.0" />
	<field name="new_parameter" descr="New parameter\;For update_type = 0:\;- Multicast_Tunnel_FDB_record.underlay_mc_ptr (13bits)\;For update_type = 1:\;- Multicast_FDB_record.mid (16bits)\;- Multicast_Tunnel_FDB_record.mid (16bit)s\;For update_type = 2:\;Update Unicast_Tunnel_FDB_record.uip_lsb (24bits)\;For update_type = 3\;- bits 31:24: counter_set_type (8bit)\;- bits 23:0: counter_index (24bit)" access="WO" offset="0x40.0" size="0x4.0" />
	<field name="new_parameter1" descr="For update_type = 0:\;- Multicast_Tunnel_FDB_record.ecmp_size (13bits)\;For update_type = 2:\;- Unicast_Tunnel_FDB_record.ecmp_size (13bits)" access="WO" offset="0x44.0" size="0x4.0" />
</node>

<node name="sfdd_ext" descr="" size="0x420.0" >
	<field name="filter_fields" descr="Filter Fields:\;if a bit is &apos;0&apos; then the relevant field is ignored and dump is done \;regardless of the field value\;Bit0: filter by activity: entry_a\;Bit1: filter by policy: entry_policy\;Bit2: filter by entry type: entry_type\;Bit3: filter by entry parameters: entry_parameters\;All set filters are relevant (there is AND between the filters)\;Reserved when op is Clear activity" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="rec_type" descr="Record type:\;0: records are 16B\;1: records are 32B\;Reserved when SwitchX/-2" access="OP" offset="0x0.20" size="0x0.1" />
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="num_rec" descr="At request: number of records requested\;At response: number of records dumped\;Range is 0 ..32" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="end" descr="End session\;Forces an end to the current session" access="OP" offset="0x4.20" size="0x0.1" />
	<field name="op" descr="Operation\;0: Dump entries\;1: Clear activity for all entries which were dumped in the current \;session" access="OP" offset="0x4.24" size="0x0.2" />
	<field name="entry_type" descr="Dump only if entry type has encoding of entry_type\;See Section 6.2.17, &quot;FDB Records,&quot; on page 810\;Reserved if filter_fields bit2 is &apos;0&apos;" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="entry_policy" descr="Dump only if policy has encoding of policy\;Reserved if filter_fields bit1 is &apos;0&apos;" access="INDEX" offset="0x8.8" size="0x0.2" />
	<field name="entry_a" descr="Dump only if activity has value of entry_a\;Reserved if filter_fields bit0 is &apos;0&apos;" access="INDEX" offset="0x8.16" size="0x0.1" />
	<field name="entry_fid" descr="Dump only if FID has value of entry_fid\;When ubridge = 0, for router sub-port interface, FID is cap_fid + \;rif\;Otherwise, valid range is 1..cap_fid-1\;Reserved if filter_fields bit3 is &apos;0&apos;" access="INDEX" offset="0xC.0" size="0x0.16" />
	<field name="entry_parameters" descr="For entry of type Unicast FDB record: System Port parameters, \;see Section 6.12.7.1, &quot;SFDD System Port Parameters,&quot; on \;page 869\;For entry of type Unicast LAG record: Lag ID parameters, see \;Section 6.12.7.2, &quot;SFDD Lag ID Parameters,&quot; on page 870\;For entry of type Multicast record: MID parameters, see \;Section 6.12.7.3, &quot;SFDD MID Parameters,&quot; on page 870\;For entry of type Unicast Tunnel FDB record Underlay parame\;ters, see Section 6.12.7.4, &quot;SFDD Underlay Parameters,&quot; on \;page 871\;Multicast Tunnel FDB record: underlay_mc_ptr (24bit)" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x10.0" />
	<field name="notification_records" descr="For rec_type = 0, see Section 737, &quot;SFD - Records type0 Layout,&quot; \;on page 862\;For rec_type = 1, see Section 739, &quot;SFD - Records type1 Layout,&quot; \;on page 864" access="RW" high_bound="255" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="sfdf_ext" descr="" size="0x14.0" >
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="st" descr="Static:\;0: delete only dynamic entries \;1: delete both dynamic and static entries" access="INDEX" offset="0x4.24" size="0x0.1" />
	<field name="iut" descr="Ignore Unicast Tunnel entries:\;0: flush_types 0..5 also flush &quot;Unicast Tunnel&quot; entries\;1: flush_types 0..5 do not flush &quot;Unicast Tunnel&quot; entries" access="INDEX" offset="0x4.25" size="0x0.1" />
	<field name="flush_type" descr="Flush type\;0: FLUSH_PER_SWID - All SWID entries are flushed. Parameter \;is reserved.\;1: FLUSH_PER_FID - All FID entries are flushed, including NVE \;(tunnels). Parameter is FID.\;2: FLUSH_PER_PORT - All entries pointing to port are flushed. \;Parameter is system_port.\;3: FLUSH_PER_PORT_AND_FID - All FID entries pointing to \;the port are flushed. \;4: FLUSH_PER_LAG - All entries pointing to LAG are flushed. \;Parameter is lag_id.\;5: FLUSH_PER_LAG_AND_FID - All FID entries pointing to \;the LAG are flushed. \;6: FLUSH_PER_NVE - All entries of type &quot;Unicast Tunnel&quot; are \;flushed. No parameters\;7: FLUSH_PER_NVE_AND_FID - same as FLUSH_PER_NVE, \;but only for FID entries. Parameter is FID.\;10: FLUSH_MC_DMAC_UC - all MC entries where the DMAC \;is a UC DMAC (bit40=&apos;0&apos;). No parameters\;11: FLUSH_MC_DMAC_UC_AND_FID - all MC entries where \;the DMAC is a UC DMAC (bit40=&apos;0&apos;). Parameter is FID." access="INDEX" enum="FLUSH_PER_SWID=0x0,FLUSH_PER_FID=0x1,FLUSH_PER_PORT=0x2,FLUSH_PER_PORT_AND_FID=0x3,FLUSH_PER_LAG=0x4,FLUSH_PER_LAG_AND_FID=0x5,FLUSH_PER_NVE=0x6,FLUSH_PER_NVE_AND_FID=0x7,FLUSH_MC_DMAC_UC=0xa,FLUSH_MC_DMAC_UC_AND_FID=0xb" offset="0x4.28" size="0x0.4" />
	<field name="parameter" descr="Parameter used for the different flush_type:\;FLUSH_PER_SWID, FLUSH_PER_NVE: reserved\;FLUSH_PER_FID, FLUSH_PER_NVE_AND_FID: Table 787, \;&quot;Parameter Layout - Flush per FID,&quot; on page 899\;FLUSH_PER_PORT: Table 789, &quot;Parameter Layout - Flush per \;Port,&quot; on page 899\;FLUSH_PER_PORT_AND_FID: Table 791, &quot;Parameter Layout - \;Flush per Port and FID,&quot; on page 899\;FLUSH_PER_LAG: Table 793, &quot;Parameter Layout - Flush per \;LAG,&quot; on page 900\;FLUSH_PER_LAG_AND_FID: Table 795, &quot;Parameter Layout - \;Flush per LAG and FID,&quot; on page 901" subnode="sfdf_parameter_auto_ext" access="RW" offset="0x8.0" size="0x8.0" />
</node>

<node name="sfdf_parameter_auto_ext" descr="" attr_is_union="1" size="0x8.0" >
	<field name="flush_per_fid_ext" descr="" subnode="flush_per_fid_ext" offset="0x0.0" size="0x8.0" />
	<field name="flush_per_port_ext" descr="" subnode="flush_per_port_ext" offset="0x0.0" size="0x8.0" />
	<field name="flush_per_port_and_fid_ext" descr="" subnode="flush_per_port_and_fid_ext" offset="0x0.0" size="0x8.0" />
	<field name="flush_per_lag_ext" descr="" subnode="flush_per_lag_ext" offset="0x0.0" size="0x8.0" />
	<field name="flush_per_lag_and_fid_ext" descr="" subnode="flush_per_lag_and_fid_ext" offset="0x0.0" size="0x8.0" />
</node>

<node name="sfdt_ext" descr="" size="0x2e0.0" >
	<field name="fgl_ptr" descr="Port Group Index\;Range 0 .. max_mid - 1\;For Spectrum/-2, pointer to PGT table, see Appendix A.3.2, \;&quot;Port Group Table (PGT)&quot; (page 2254)" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="size" descr="Number of port_member_lists to be added/edited in the FGL \;membership.\;Valid range is 1..90" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="port_members_list" descr="port_member list, see Table 813, &quot;port_members_list&lt;i&gt; Lay\;out,&quot; on page 915" subnode="uint64" access="RW" high_bound="89" low_bound="0" offset="0x10.0" size="0x2d0.0" />
</node>

<node name="sffp_ext" descr="" size="0x8.0" >
	<field name="type" descr="0: BROADCAST\;1: UNKNOWN_UNICAST\;2: UNREGISTERED_MULTICAST_IPV4\;3: UNREGISTERED_MULTICAST_IPV6\;4: RESERVED\;5: UNREGISTERED_MULTICAST_NON_IP\;6: IPV4_LINK_LOCAL - (Addresses 224.0.0.X)\;7: IPV6_ALL_HOSTS - (Address FF02::1)" access="INDEX" enum="BROADCAST=0x0,UNKNOWN_UNICAST=0x1,UNREGISTERED_MULTICAST_IPV4=0x2,UNREGISTERED_MULTICAST_IPV6=0x3,RESERVED=0x4,UNREGISTERED_MULTICAST_NON_IP=0x5,IPV4_LINK_LOCAL=0x6,IPV6_ALL_HOSTS=0x7" offset="0x0.0" size="0x0.4" />
	<field name="profile_id" descr="Profile ID" access="INDEX" offset="0x0.16" size="0x0.2" />
	<field name="flood_offset" descr="Flood offset\;Default 0\;" access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="sfgc_ext" descr="" size="0x14.0" >
	<field name="type" descr="0: BROADCAST\;1: UNKNOWN_UNICAST\;2: UNREGISTERED_MULTICAST_IPV4\;3: UNREGISTERED_MULTICAST_IPV6\;4: RESERVED\;5: UNREGISTERED_MULTICAST_NON_IP\;6: IPV4_LINK_LOCAL - (Addresses 224.0.0.X), not supported by \;SwitchX/-2\;7: IPV6_ALL_HOSTS - (Address FF02::1), not supported by \;SwitchX/-2\;Other - reserved" access="INDEX" enum="BROADCAST=0x0,UNKNOWN_UNICAST=0x1,UNREGISTERED_MULTICAST_IPV4=0x2,UNREGISTERED_MULTICAST_IPV6=0x3,RESERVED=0x4,UNREGISTERED_MULTICAST_NON_IP=0x5,IPV4_LINK_LOCAL=0x6,IPV6_ALL_HOSTS=0x7" offset="0x0.0" size="0x0.4" />
	<field name="flood_table" descr="Flooding table index to associate with the specific type on the spe\;cific switch partition.\;If table_type == single entry:\;Indexed from 0 to max_flood_tables-1\;If table_type == VID:\;Indexed from 0 to max_vid_flood_tables-1\;If table_type == FID_Offset (when ubridge=0 supports VIDs):\;Indexed from 0 to max_fid_offset_flood_tables-1\;If table_type == FID (when ubridge=0 supports and used only \;vFIDs):\;Indexed from 0 to max_fid_flood_tables-1\;Reserved when ubridge=1" access="RW" offset="0x4.0" size="0x0.6" />
	<field name="table_type" descr="Table type to use:\;0: any_type - should only be used if only one type of table is con\;figured in the profile. Reserved when Spectrum/-2\;1: per_VID_tables - reserved when ubridge=1\;2: single_entry_tables - reserved when ubridge=1\;3: FID_Offset - reserved when SwitchX/-2\;4: FID - (when ubridge=0 used for vFIDs only, not for the first 4K \;FIDs). Reserved when SwitchX/-2" access="RW" enum="any_type=0x0,FID=0x4" offset="0x4.16" size="0x0.3" />
	<field name="bridge_type" descr="Bridge Type (see Section 6.4.2.1, &quot;FID Classification,&quot; on \;page 840):\;0: type0 - when ubridge=0: 802.1Q. FID\;1: type1 - when ubridge=0: vFID. Reserved when SwitchX/-2" access="INDEX" enum="type0=0x0,type1=0x1" offset="0x4.24" size="0x0.3" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum/-2: See Section 4.1, &quot;Performance and Monitoring \;Counters,&quot; on page 621\;Not supported by SwitchX/-2" access="RW" offset="0xC.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum/-2: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622\;Not supported by SwitchX/-2" access="RW" offset="0xC.24" size="0x0.8" />
	<field name="mid_base" descr="MID Base\;Reserved when ubridge=0" access="RW" offset="0x10.0" size="0x0.16" />
</node>

<node name="sfmr_ext" descr="" size="0x2c.0" >
	<field name="fid" descr="Filtering Identifier\;Also supported for values of 0..4K-1" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="op" descr="Operation\;0: FID is valid\;1: FID is not valid" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="update" descr="update existing entry" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="disable_tport_encap" descr="Disable tunnel_port encap for this fid. Bitwise:\;Bit0: disable NVE encap for this fid\;When set then the tunnel-encap will match the trap DIS\;CARD_LOOKUP_SWITCH_UC or DISCARD_LOOK\;UP_SWITCH_MC_NULL and will count on \;PPCNT.ingress_tx_link_down" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="update_mask" descr="Reserved when update = 0 \;When update = 1:\;Bit0: update disable_tport_encap\;Bit1: update flood_rsp, flood_bridge_type\;Bit2: update fid_offset\;Bit3: update vtfp, nve_tunnel_flood_ptr\;Bit4: update vv, vni\;Bit5: update irif_v, irif\;Bit6: update decap_counter_set_type, decap_counter_index\;Bit7: update cff_counter_set_type, cff_counter_base_index\;Bit8: update cff_mid_base\;Bit9: update nve_flood_prf_id\;Bit10: update smpe_valid, smpe" access="OP" offset="0x4.8" size="0x0.16" />
	<field name="fid_offset" descr="FID Offset\;Used to point into the flooding table selected by SFGC regis\;ter if the table is of type FID-Offset. \;For other flooding table types, this field is reserved.\;Reserved when op = 1\;Reserved when flood_rsp = 1" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="flood_bridge_type" descr="Flood bridge type (see SFGC.bridge_type):\;0: type_0\;1: type_1\;Reserved when ubridge = 0\;Reserved when flood_rsp = 1" access="RW" enum="type_0=0x0,type_1=0x1" offset="0x8.28" size="0x0.1" />
	<field name="flood_rsp" descr="Router sub-port flooding tables:\;0: regular flooding tables\;1: router sub-port flooding table, for this fid the flooding is \;per router-sub-port local_port. Must not be set for a fid which \;is not a router-sub-port. \;Note: must be set prior to enabling the relevant RIF!\;Reserved when ubridge = 0" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="nve_tunnel_flood_ptr" descr="Underlay Flooding and BC Pointer. Used as a pointer to the \;first entry of the group based link lists of flooding or BC \;entries (for NVE tunnels). \;For Spectrum-1 the number of link lists in the group is con\;figured by TNGCR.nve_group_size_flood.\;For Spectrum-2 and on points to first entry (which may point \;to a group).\;The pointer points to entries which are configured by \;TNUMT or by TNGEE, see Section 15.11.6, &quot;TNUMT - \;Tunneling NVE Underlay Multicast Table Register,&quot; on \;page 2130, Section 15.11.3, &quot;TNGEE - TuNnel Generic \;Encapsulation Entry Register,&quot; on page 2124\;For Spectrum/-2, this points to an entry in the KVD Linear, \;see Appendix A.3.1.2, &quot;KVD Central Database Linear \;Entries&quot; (page 2254)\;Reserved when op = 1" access="RW" offset="0xC.0" size="0x0.24" />
	<field name="vtfp" descr="Tunnel Flood Pointer Valid\;If it is not set, nve_tunnel_flood_ptr is reserved and is con\;sidered as NULL pointer.\;For Spectrum when ubridge=0 and 802.1Q FIDs - reserved \;Reserved when op = 1" access="RW" offset="0xC.31" size="0x0.1" />
	<field name="vni" descr="Virtual Network Identifier\;SW must not assign a given VNI to more than one FID\;Reserved when op = 1\;Reserved when vv = 0\;Range 0.. (2^24-2)" access="RW" offset="0x10.0" size="0x0.24" />
	<field name="vv" descr="VNI Valid.\;If it is not set, vni is reserved\;Reserved when op = 1" access="RW" offset="0x10.31" size="0x0.1" />
	<field name="irif" descr="Ingress RIF (Router Interface)\;Range is 0.. cap_max_router_interfaces-1\;Reserved when ubridge = 0\;Reserved when irif_v = 0\;" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="irif_v" descr="Ingress RIF valid:\;0: irif is not valid, no irif assigned\;1: irif valid\;Must not be set for a non valid RIF\;Reserved when ubridge = 0" access="RW" offset="0x14.24" size="0x0.1" />
	<field name="decap_counter_index" descr="Counter Index for flow counters.\;Counts NVE Decap from vni to fid\;For Spectrum/-2: See Section 4.1, &quot;Performance and Moni\;toring Counters,&quot; on page 621\;Not supported by SwitchX/-2\;Reserved when ubridge=1" access="RW" offset="0x18.0" size="0x0.24" />
	<field name="decap_counter_set_type" descr="Counter Set Type for flow counters.\;Counts NVE Decap from vni to fid\;For Spectrum/-2: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622\;Not supported by SwitchX/-2\;Reserved when ubridge=1" access="RW" offset="0x18.24" size="0x0.8" />
	<field name="nve_flood_prf_id" descr="Fid Flooding profile_id for NVE Encap\;Reserved when SwitchX/-2 and Spectrum-1\;[Spectrum-2-phase2]" access="RW" offset="0x24.8" size="0x0.2" />
	<field name="smpe" descr="Switch multicast port to egress VID\;Range is 0.. cap_max_rmpe - 1\;Reserved when ubridge = 0\;Reserved when flood_rsp = 1\;Reserved when SwitxcX/-2 or when Spectrum-1" access="RW" offset="0x28.0" size="0x0.16" />
	<field name="smpe_valid" descr="SMPE is valid\;Reserved when ubridge = 0\;Reserved when flood_rsp = 1\;Reserved when SwitchX/-2 or when Spectrum-1" access="RW" offset="0x28.20" size="0x0.1" />
</node>

<node name="sfn_ext" descr="" size="0x410.0" >
	<field name="rec_type" descr="Record type:\;0: records are 16B\;1: records are 32B\;Reserved when SwitchX/-2" access="OP" offset="0x0.20" size="0x0.1" />
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="num_rec" descr="Request: Number of learned notifications and aged-out notifica\;tion records requested\;Response: Number of notification records returned (must be \;smaller than or equal to the value requested)\;For rec_type = 0: Range 0..64\;For rec_type = 1: Range 0..32" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="end" descr="End session\;Forces an end to the current session" access="OP" offset="0x4.20" size="0x0.1" />
	<field name="notification_records" descr="For rec_type = 0, see Section 737, &quot;SFD - Records type0 Layout,&quot; \;on page 862\;For rec_type = 1, see Section 739, &quot;SFD - Records type1 Layout,&quot; \;on page 864" access="RW" high_bound="255" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="sftr_ext" descr="" size="0x240.0" >
	<field name="index" descr="Index. Used as an index into the Flooding Table\;Reserved when table_type == single entry" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="flood_table" descr="Flooding table index to associate with the specific type on the spe\;cific switch partition.\;If table_type == single entry:\;Indexed from 0 to max_flood_tables-1\;If table_type == VID:\;Indexed from 0 to max_vid_flood_tables-1\;If table_type == FID-Offset (supports VIDs):\;Indexed from 0 to max_fid_offset_flood_tables-1\;If table_type == FID (supports only vFIDs):\;Indexed from 0 to max_fid_flood_tables-1" access="INDEX" offset="0x0.16" size="0x0.6" />
	<field name="swid" descr="Switch Partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="range" descr="Range of entries to update\;Allows executing the same operation on multiple entries from \;index to (index+range-1)\;Reserved when Read operations." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="table_type" descr="Table type to use:\;0: any-type. Should only be used if only one type of table is con\;figured in the profile. Reserved when Spectrum/-2\;1: VID tables.\;2: Single entry tables.\;3: FID Offset. Reserved when SwitchX/-2.\;4: FID (used for vFIDs only). Reserved when SwitchX/-2." access="INDEX" offset="0x4.16" size="0x0.3" />
	<field name="port" descr="Local port membership \;0: Non-member \;1: Member - packets that point to the MID are transmitted into the \;port\;All LAG ports must share the same configuration.Refer to \;Section 8.3, &quot;Port Numbering,&quot; on page 973 for port numbering \;scheme.\;CPU port is supported, trap_id is FDB\;Router port is supported" access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="mask" descr="Local port mask; reserved when Read operations.\;0: Do not update port state.\;1: Update port membership based on the op and the port value" access="WO" high_bound="7" low_bound="0" offset="0x220.0" size="0x20.0" />
</node>

<node name="sgcr_ext" descr="" size="0x50.0" >
	<field name="llb" descr="Link Local Broadcast (Default=0)\;When set, all Link Local packets (224.0.0.X) will be \;treated as broadcast packets and ignore the IGMP snoop\;ing entries.\;Note: this capability is not supported on SwitchX device. \;It is supported on SwitchX-2 device\;Reserved when Spectrum/-2" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="activity_dis" descr="Activity Disable:\;0: enable - activity will be set when an entries are hit\;(default)\;1: disable - activity will not be set when an entries are hit\;\;Bit 0: Disable activity bit in FDB. See Section 6.12.5, \;&quot;SFD - Switch Filtering Database,&quot; on page 860\;\;Bits 7:1: reserved\;Not supported by SwitchX, SwitchX-2" access="RW" offset="0x8.0" size="0x0.8" />
</node>

<node name="shared_buffer_status" descr="" size="0x8.0" >
	<field name="buff_occupancy" descr="Current buffer occupancy" access="RO" offset="0x0.0" size="0x0.24" />
	<field name="max_buff_occupancy" descr="Maximum value of buffer occupancy monitored. Cleared by \;writing to the clr field" access="RO" offset="0x4.0" size="0x0.24" />
</node>

<node name="slcor_ext" descr="" size="0x10.0" >
	<field name="lag_id" descr="LAG Identifier. Index into the LAG descriptor table." access="RW" offset="0x0.0" size="0x0.10" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="col" descr="Collector configuration\;0x0: LAG_ADD_PORT - (port is added with collector disabled)\;0x1: LAG_COLLECTOR_ENABLED\;0x2: LAG_COLLECTOR_DISABLED\;0x3: LAG_REMOVE_PORT" access="RW" enum="LAG_ADD_PORT=0x0,LAG_COLLECTOR_ENABLED=0x1,LAG_COLLECTOR_DISABLED=0x2,LAG_REMOVE_PORT=0x3" offset="0x0.30" size="0x0.2" />
	<field name="port_index" descr="Port index in the LAG list. Only valid on Add Port to LAG col. \;valid range is from 0 to cap_max_lag_members-1\;" access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="slcr_switch_lag_ext" descr="" size="0x10.0" >
	<field name="type" descr="Hash type\;0: CRC (default)\;1: XOR \;2: Random (egress port is chosen randomly out of the LAG mem\;bers). \;Reserved when SwitchX/-2" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="sh" descr="Symmetric hash \;When set, the hash calculation will result in the same hash value as \;when the source address (layer 2 and layer 3) is swapped. This \;ensures that the same conversions will result in the same hash \;value.\;Note: for SwitchX/-2 when this bit is set, enabling addresses in \;lag_hash must be in couples - both source and destination. This \;includes the following sets:\;SMAC, DMAC\;SIP, DIP\;TCP/UDP Source Port, TCP/UDP destination port\;SID, DID - for SwitchX/-2 only" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="local_port" descr="Local port number\;Reserved when SwitchX/-2" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pp" descr="Per Port Configuration\;0: Global Configuration (for all ports)\;1: Per port configuration, based on local_port field.\;Note: SW must not read as global if last write was not global.\;Reserved when SwitchX/-2" access="INDEX" offset="0x0.24" size="0x0.1" />
	<field name="lag_hash" descr="LAG hashing configuration. This is a bitmask, in which each set \;bit includes the corresponding item in the LAG hash calculation.\;0: Ingress_port\;1: SMAC - for IPv4 and IPv6 packets\;2: SMAC - for non-IP packets\;3: DMAC - for IPv4 and IPv6 packets\;4: DMAC - for non-IP packets\;5: Ethertype - for IPv4 and IPv6 packets\;6: Ethertype - for non-IP packets\;7: VLAN_ID - for IPv4 and IPv6 packets\;8: VLAN_ID - for non-IP packets\;\;9: Source_IP_address - (can be IPv4 or IPv6, also for ARP pay\;load)\;10: Destination_IP_address - (can be IPv4 or IPv6, also for ARP \;payload)\;11: TCP/UDP - source port\;12: TCP/UDP - destination port\;13: IPv4 Protocol/IPv6 Next Header\;14: IPv6 Flow label\;15: SID - FCoE source ID\;16: DID - FCoE destination ID\;17: OXID - FCoE originator exchange ID\;19: Destination_QP_number - for RoCE packets\;\;The default lag_hash contains SMAC, DMAC, VLANID and Eth\;ertype (for all packet types)\;Note: An engine action can be added to the LAG hash calculation. \;For more details, contact Mellanox support." access="RW" offset="0x4.0" size="0x0.20" />
	<field name="seed" descr="LAG seed value. The seed is the same for all ports (latest configu\;ration configures the seed for all ports)." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="slecr_ext" descr="" size="0x10.0" >
	<field name="re" descr="Roaming enable. In case of a new MAC address that has a port \;mismatch with existing dynamic FDB entry:\;0: do not learn\;1: learn (default)\;(Learn means generating a learning notification to the software)\;Note: learning is enabled only if all enables are set (spanning tree, \;port-vid, global)\;" access="RW" offset="0x0.2" size="0x0.1" />
	<field name="il" descr="Independent Learning\;0: Shared VLAN learning, Reserved when Spectrum/-2\;1: Independent VLAN learning (default)\;" access="RW" offset="0x0.3" size="0x0.1" />
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="slred_reg_ext" descr="" size="0xa0.0" >
	<field name="page_data_sel" descr="select page data number to display.\;0 - info page data\;1 - page data 1 (indexes 0 to 319)\;2 - page data 2 (indexes 320 to 639)\;3 - page data 3 (indexes 640 to 959)\;4 - page data 4 (indexes 960 to 1279)\;5 - page data 5 (indexes 1280 to 1599)\;6 - page data 6 (indexes 1600 to 1919)\;7 - page data 7 (indexes 1920 to 2239)" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lane" descr="physical lane number." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0 - Local port number\;1 - IB / label port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="1 - 28nm products\;3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="lane_speed" descr="The lane speed on which the eye scan was measured\;0-1 - reserved\;2 - QDR (10 Gb/s) / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE) (10.3125 Gb/s) \;4 - FDR (56GE) (14.0625 Gb/s) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) (25.78125 Gb/s) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE) (26.5625Gbd / 53.125Gb/s) \;7 - 15 - reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="status" descr="eye scan status:\;0 - eye scan was not performed.\;1 - unsupported scan for current speed.\;2 - system busy.\;3 - Performing eye scan.\;4 - eye scan completed. \;5 - error, eye scan not completed." access="RO" offset="0x4.4" size="0x0.3" />
	<field name="eye_sel" descr="eye selection for PAM4 signals.\;0 - up\;1 - mid\;2 - down\;Note: for NRZ field is ignored" access="RW" offset="0x4.18" size="0x0.2" />
	<field name="measure_time" descr="max measure time in seconds for single eye diagram.\;0 - 10 sec\;1 - 30 sec\;2 - 60 sec\;3 - 90 sec\;4 - 120 sec\;5 - 240 sec\;6 - 480 sec\;7 - 600 sec\;8 - 900 sec\;9-15 reserved\;each tic measure time will be measure_time / (hight_dim x width_dim)" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="eye_diag_dim" descr="dimensions of eye scan matrix in the format of hight_dim x width_dim\;0 - 16x16 (256 err val)\;1 - 32x32 (1024 err val)\;2 - 32x64 (1024 err val)\;3 - 64x32 (2048 err val)" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="err_res_base" descr="mantissa resolution for err_val. err value will represent errors betweener\;r_res_base ^(err_val - 1) +1 to err_res_base^err_val\;0 - err_res_base is 10\;1-3 - reserved\;\;For example if err_res_base is 10:\;0 err_value represents 0 errors\;1 err_value represents 1-10 errors\;2 err_value represents 11-100 errors\;3 err_value represents 101-1000 errors\;...\;7 err_value represents 10^6+1 - 10^7 errors" access="RW" offset="0x4.27" size="0x0.2" />
	<field name="destructive_ctrl" descr="0 - non destructive scan\;1 - destructive scan\;Note: if non destructive scan is not supported this field is ignored and a \;destructive scan will be operated" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="last_scan" descr="set to &apos;1&apos; when performing last eye scan for lane.\;For example: when scanning 3 eyes in the order of up, mid, down. \;field should be set when scanning down eye.\;If scanning only 1 eye, field should be set." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="en" descr="start eye scan" access="WO" offset="0x4.31" size="0x0.1" />
	<field name="page_data" descr="page data for index page_data_sel\;page 0 will contain info page data.\;See Table  1138, &quot;SLRED - Serdes Lane Receive Eye Diagram Register \;Layout for info page,&quot; on page  1343\;the page data 1-7 will contain the err_val for each index in ascend\;ing order.\;See Table  1140, &quot;SLRED - Serdes Lane Receive Eye Diagram Register \;Layout for page_data,&quot; on page  1344\;Each err_val[i] represents the bit errors of row floor(i / width_dim)\;and column i mod width_dim\;each err_val indicates the number of bit errors for one tick" access="RO" high_bound="37" low_bound="0" offset="0x8.0" size="0x98.0" />
</node>

<node name="slrg_16nm_ext" descr="" size="0x1c.0" >
	<field name="grade_lane_speed" descr="The lane speed on which the grade was measured:\;0 - SDR / PCIe Gen 1\;1 - DDR / PCIe Gen 2\;2 - QDR / PCIe Gen 3\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / PCIe Gen 4\;5 - EDR (25GE / 50GE / 100GE) / PCIe Gen 5\;6 - HDR (50GE / 200GE / 400GE)\;7- 9 - reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13 - 15 - reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="grade" descr="The grade that the lane received based on a specific configuration.\;" access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg_up" descr="Voltage offset from eye center to the negative side of the upper eye. \;Only applicable for PAM4 signal." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="height_eo_pos_up" descr="Voltage offset from eye center to the positive side of the upper eye.\;Only applicable for PAM4 signal." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="height_eo_pos_mid" descr="Voltage offset from eye center to the positive side of the middle \;eye." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="phase_eo_neg_up" descr="The offset from the eye center to the negative (left) side of the \;upper eye. Only applicable for PAM4 signal." access="RO" offset="0xC.16" size="0x0.8" />
	<field name="phase_eo_pos_up" descr="The offset from the eye center to the positive (right) side of the \;upper eye. Only applicable for PAM4 signal." access="RO" offset="0xC.24" size="0x0.8" />
	<field name="phase_eo_neg_mid" descr="The offset from the eye center to the negative (left) side of the mid\;dle eye." access="RO" offset="0x10.0" size="0x0.8" />
	<field name="phase_eo_pos_mid" descr="The offset from the eye center to the positive (right) side of the \;middle eye." access="RO" offset="0x10.8" size="0x0.8" />
	<field name="height_eo_neg_mid" descr="Voltage offset from eye center to the negative side of the middle \;eye." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="height_eo_neg_low" descr="Voltage offset from eye center to the negative side of the lower eye. \;Only applicable for PAM4 signal." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos_low" descr="Voltage offset from eye center to the positive side of the lower eye. \;Only applicable for PAM4 signal." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg_low" descr="The offset from the eye center to the negative (left) side of the \;lower eye. Only applicable for PAM4 signal." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="phase_eo_pos_low" descr="The offset from the eye center to the positive (right) side of the \;lower eye. Only applicable for PAM4 signal." access="RO" offset="0x18.24" size="0x0.8" />
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

<node name="slrg_reg_ext" descr="" size="0x28.0" >
	<field name="lane" descr="Physical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. 0 - Local port number\;1 - IB / label port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 40nm products\;1 - 28nm products\;3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="See Table  1126, &quot;SLRG - Serdes Lane Receive Grade Register Layout for \;40nm and 28nm,&quot; on page  1330\;See Table  1128, &quot;SLRG - Serdes Lane Receive Grade Register Layout for \;16nm,&quot; on page  1332" subnode="slrg_reg_page_data_auto_ext" access="RO" offset="0x4.0" size="0x24.0" />
</node>

<node name="slrg_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x24.0" >
	<field name="slrg_40nm_28nm_ext" descr="" subnode="slrg_40nm_28nm_ext" offset="0x0.0" size="0x24.0" />
	<field name="slrg_16nm_ext" descr="" subnode="slrg_16nm_ext" offset="0x0.0" size="0x1c.0" />
</node>

<node name="sltp_16nm_ext" descr="" size="0x18.0" >
	<field name="post_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or \;smaller.\;" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="main_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or \;smaller.\;" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="pre_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or \;smaller.\;" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="pre_2_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or \;smaller.\;" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="ob_alev_out" descr="Output common mode. Values can be set in the range of (0-30)" access="RW" offset="0x8.0" size="0x0.5" />
	<field name="ob_amp" descr="Output amplitude. Values can be set in the range of (10-100)." access="RW" offset="0x8.8" size="0x0.7" />
	<field name="ob_m2lp" descr="MSB to LSB proportion. \;Values can be set between -10 to 50. \;\;MSB emphasis achieved when value is between -10 to -1 \;LSB emphasis achieved when value is between 1 to 50. \;When set to 0 - equal proportion." access="RW" offset="0x8.25" size="0x0.7" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;0: configuration_warning - taps values can&apos;t be set to serdes due to \;internal limitations. Actual TX configuration is modify internally \;with the same sum of taps weight.\;11: Illegal_ob_combination - ob_m2lp, ob_amp and ob_alev is in \;legal range each, but the total combination can&apos;t be set to serdes \;due to internal limitations, the Set command is ignored.\;12: Illegal_ob_m2lp\;13: Illegal_ob_amp\;14: Illegal_ob_alev_out\;15: Illegal_taps\;\;Bit 12-0 - Reserved /Unknown" access="RO" enum="configuration_warning=0x0,Illegal_ob_combination=0xb,Illegal_ob_m2lp=0xc,Illegal_ob_amp=0xd,Illegal_ob_alev_out=0xe,Illegal_taps=0xf" offset="0xC.16" size="0x0.16" />
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

<node name="sltp_gearbox_ext" descr="" size="0x18.0" >
	<field name="pre_tap" descr="" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="main_tap" descr="" access="RW" offset="0x0.16" size="0x0.16" />
	<field name="post_tap" descr="" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="inner_eye_1" descr="" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="inner_eye_2" descr="" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="tx_swing" descr="" access="RW" offset="0xC.0" size="0x0.4" />
</node>

<node name="sltp_reg_ext" descr="" size="0x1c.0" >
	<field name="c_db" descr="copy transmitter parameters to Data Base. \;" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe)\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7-9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13-15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Physical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="pnat" descr="Port number access type. determines the way local_port is inter\;preted:\;0 - Local port number\;1 - IB / label port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 40nm products\;1 - 28nm products\;3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="See Table  1116, &quot;SLTP - Serdes Lane Transmit Parameters Register Layout \;for 28nm and 40nm,&quot; on page  1325\;See Table  1118, &quot;SLTP - Serdes Lane Transmit Parameters Register Layout \;for 16nm,&quot; on page  1326\;See Table  1120, &quot;[Internal] Serdes Lane Transmit Parameters Register \;Layout For Gearbox,&quot; on page  1327" subnode="sltp_reg_page_data_auto_ext" access="RO" offset="0x4.0" size="0x18.0" />
</node>

<node name="sltp_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x18.0" >
	<field name="sltp_28nm_40nm_ext" descr="" subnode="sltp_28nm_40nm_ext" offset="0x0.0" size="0x10.0" />
	<field name="sltp_16nm_ext" descr="" subnode="sltp_16nm_ext" offset="0x0.0" size="0x18.0" />
	<field name="sltp_gearbox_ext" descr="" subnode="sltp_gearbox_ext" offset="0x0.0" size="0x18.0" />
</node>

<node name="smid_ext" descr="" size="0x240.0" >
	<field name="mid" descr="Multicast identifier - global identifier that represents the multi\;cast group\;Range 0 .. max_mid - 1\;For Spectrum/-2, pointer to PGT table, see Appendix A.3.2, \;&quot;Port Group Table (PGT)&quot; (page 2254)" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="op" descr="opcode:\;0: UPDATE - (updates only according to the mask)\;1: WRITE - (all ports will become non-member followed by a \;write)" access="OP" enum="UPDATE=0x0,WRITE=0x1" offset="0x4.0" size="0x0.4" />
	<field name="smpe" descr="Switch multicast port to egress VID\;Reserved when ubridge=0\;Reserved when Spectrum-2" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="smpe_valid" descr="SMPE is valid\;When not valid, the egress VID will not be modified by the \;SMPE table\;Reserved when ubridge=0\;Reserved when Spectrum-2" access="RW" offset="0x8.20" size="0x0.1" />
	<field name="port" descr="Local port membership \;0: Non-member \;1: Member - packets that point to the MID are transmitted into \;the port\;All LAG ports must share the same configuration.Refer to \;Section 8.3, &quot;Port Numbering,&quot; on page 973 for port numbering \;scheme.\;CPU port is supported, trap_id is FDB\;Router port is supported" access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="mask" descr="Local port mask. Reserved on Get() operations.\;0: Do not update port state\;1: Update port membership based on the port value" access="WO" high_bound="7" low_bound="0" offset="0x220.0" size="0x20.0" />
</node>

<node name="smpe_ext" descr="" size="0xc.0" >
	<field name="local_port" descr="Local port number\;CPU port is not supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="smpe_index" descr="Switch multicast port to egress VID\;Range is 0.. cap_max_rmpe - 1\;Note: when ubridge=1 the rmpe and smpe use the same range, see \;RMPE register" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="evid" descr="Egress VID" access="RW" offset="0x8.0" size="0x0.12" />
</node>

<node name="smpeb_elport_record" descr="" size="0x4.0" >
	<field name="value" descr="Value:\;egress vid, range 0..4095" access="RW" offset="0x0.0" size="0x0.20" />
	<field name="update" descr="Update enable (when write):\;0: do not update the entry\;1: update the entry" access="OP" offset="0x0.31" size="0x0.1" />
</node>

<node name="smpeb_ext" descr="" size="0x420.0" >
	<field name="smpe_index" descr="Switch multicast port to egress VID\;When ubridge=0: Range is 0.. cap_max_rmpe - max_fid - 1\;When ubridge=1: Range is 0.. cap_max_rmpe - 1\;Note: when ubridge=1 the rmpe and smpe use the same range, see \;RMPE register" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="elport_record" descr="egress local port record\;record i for local_port i\;See Table 847, &quot;SMPEB - elport_record Layout,&quot; on page 939" subnode="smpeb_elport_record" access="RW" high_bound="255" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="smpu_ext" descr="" size="0x410.0" >
	<field name="local_port" descr="Local port to send the packet\;CPU port is supported, trap_id is FDB\;Router port is supported" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="size" descr="Number of valid MIDs to be updated.\;Range is 1 to 256" access="INDEX" offset="0x4.16" size="0x0.9" />
	<field name="op" descr="Operation\;0: Set bit\;1: Clear bit" access="WO" offset="0x4.30" size="0x0.2" />
	<field name="mid" descr="MID list to where the relevant local_port bit indication is to be \;set/cleared.\;Range 0 .. max_mid - 1\;For Spectrum, pointer to PGT table, see Appendix A.3.2, &quot;Port \;Group Table (PGT)&quot; (page 2254)" subnode="mid" access="INDEX" high_bound="255" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="spad_ext" descr="" size="0x10.0" >
	<field name="base_mac_47_32" descr="Base MAC address for the switch partitions.\;Per switch partition MAC address is equal to:\;base_mac + swid\;For Spectrum: base_mac" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="base_mac_31_0" descr="" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="spaft_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number\;Not supported for CPU port (for CPU port all tag types are \;allowed)" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="allow_tagged" descr="When set, tagged frames on the ingress are admitted (default 1)" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="allow_priotagged" descr="When set, priority tagged frames on the ingress are admitted \;(default 1)" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="allow_untagged" descr="When set, untagged frames on the ingress are admitted (default 1)" access="RW" offset="0x4.31" size="0x0.1" />
</node>

<node name="spfsr_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="security" descr="Security Checks\;0: security checks disabled, default\;1: security checks enabled\;" access="RW" offset="0x4.31" size="0x0.1" />
</node>

<node name="spgt_ext" descr="" size="0x240.0" >
	<field name="pgi" descr="Multicast port group index - index into the Port group table (PGT)" access="INDEX" offset="0x0.0" size="0x0.13" />
	<field name="range" descr="Range of entries on which the op is executed. Allows executing \;the same operation on multiple entries. op will be executed on the \;entries in the range of pgi to (pgi + range - 1).\;Reserved when Read operations." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="port" descr="Local port membership. A bit vector where each port represents a \;local port. \;0: Non-member\;1: Member - multicast packets that point to the record are trans\;mitted into the port\;All LAG ports must share the same configuration.Refer to \;Section 8.3, &quot;Port Numbering,&quot; on page 973 for port numbering \;scheme." access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="mask" descr="Local port mask. A bit vector where each port represents a local \;port.\;0: Do not update port state.\;1: Update port membership based on the op and the port value" access="WO" high_bound="7" low_bound="0" offset="0x220.0" size="0x20.0" />
</node>

<node name="spmlr_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="learn_mode" descr="Enable learning on this port.\;0: Learn Disable\;2: Learn Enable\;3: Security Mode\;(Learn means generating a learning notification to the software)\;Note: learning is enabled only if all enables are set (spanning tree, \;port-vid, global)" access="RW" offset="0x4.30" size="0x0.2" />
</node>

<node name="spms_ext" descr="" size="0x404.0" >
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="state" descr="MSTP/RSTP State on VID &lt;i&gt;\;0: STP_DO_NOT_UPDATE - Do not change spanning tree state \;(used when writing only)\;1: STP_DISCARDING - Disable learning. No forwarding to/from \;this port (default)\;2: STP_LEARNING - Enable learning. No frame forwarding to/\;from this port\;3: STP_FORWARDING - port is learning and forwarding\;\;" access="RW" enum="STP_DO_NOT_UPDATE=0x0,STP_DISCARDING=0x1,STP_LEARNING=0x2,STP_FORWARDING=0x3" high_bound="4095" low_bound="0" offset="0x4.30" size="0x400.0" />
</node>

<node name="spvc_ext" descr="" size="0xc.0" >
	<field name="local_port" descr="local port\;Supported from CPU port\;Note: applies both to Rx port and Tx port, so if a packet traverses \;through Rx port i and a Tx port j then port i and port j must have the \;same configuration" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="et0" descr="Vlan Tag0 EtherType0 enable\;Packet is initially classified as VLAN Tag if its&apos; tag0 EtherType is \;equal to ether_type0\;0: disable\;1: enable (default)" access="RW" offset="0x8.0" size="0x0.1" />
	<field name="inner_et0" descr="Vlan Tag1 EtherType0 enable\;Packet is initially classified as double VLAN Tag if in addition to \;being classified with a tag0 VLAN Tag it&apos;s tag1 EtherType value is \;equal to ether_type0\;0: disable\;1: enable (default)" access="RW" offset="0x8.1" size="0x0.1" />
	<field name="et1" descr="Vlan Tag0 EtherType1 enable\;Packet is initially classified as VLAN Tag if its&apos; tag0 EtherType is \;equal to ether_type1\;0: disable\;1: enable (default)" access="RW" offset="0x8.8" size="0x0.1" />
	<field name="inner_et1" descr="Vlan Tag1 EtherType1 enable\;Packet is initially classified as double VLAN Tag if in addition to \;being classified with a tag0 VLAN Tag it&apos;s tag1 EtherType value is \;equal to ether_type1\;0: disable\;1: enable (default)" access="RW" offset="0x8.9" size="0x0.1" />
	<field name="et2" descr="Vlan Tag0 EtherType2 enable\;Packet is initially classified as VLAN Tag if its&apos; tag0 EtherType is \;equal to ether_type2\;0: disable (default)\;1: enable" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="inner_et2" descr="Vlan Tag1 EtherType2 enable\;Packet is initially classified as double VLAN Tag if in addition to \;being classified with a tag0 VLAN Tag it&apos;s tag1 EtherType value is \;equal to ether_type2\;0: disable (default)\;1: enable" access="RW" offset="0x8.17" size="0x0.1" />
</node>

<node name="spvid_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="When tport = 0:\;Ingress Local port number\;Not supported for CPU port (it is expected that CPU data packets \;are tagged)\;When tport = 1: Tunnel port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="tport" descr="Port is tunnel port\;Reserved when SwitchX/-2 or Spectrum-1" access="INDEX" offset="0x0.24" size="0x0.1" />
	<field name="pvid" descr="Port default VID (default PVID is 001h)" access="RW" offset="0x4.0" size="0x0.12" />
	<field name="et_vlan" descr="EtherType used for when VLAN is pushed at ingress (for untagged \;packets or for QinQ push mode)\;0: ether_type0 - (default)\;1: ether_type1\;\;Ethertype IDs are configured by SVER, see Section 6.12.34, \;&quot;SVER - Switch VLAN EtherType Register,&quot; on page 928\;Reserved when egr_et_set = 1\;Reserved when SwitchX/-2" access="RW" enum="ether_type0=0x0,ether_type1=0x1" offset="0x4.16" size="0x0.2" />
	<field name="egr_et_set" descr="When VLAN is pushed at ingress (for untagged packets or for \;QinQ push mode) then the Ethertype is decided at egress port.\;Note: also for L2 tunnel encap the overlay VLAN Ethertype will \;be decided at egress port.\;See SPEVET\;Reserved when Spectrum-1" access="RW" offset="0x4.24" size="0x0.1" />
</node>

<node name="spvm_ext" descr="" size="0x400.0" >
	<field name="num_rec" descr="Number of records to update. Each record contains: i, e, u, vid.\;Range 1..255" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pte" descr="Priority Tagged Update Enable\;On Write operations, if this bit is cleared, the pt bit will NOT be \;updated. To update the pt bit, pte must be set." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="pt" descr="Priority tagged.\;If this bit is set, packets forwarded to the port with untagged \;VLAN membership (u bit is set) will be tagged with priority tag \;(VID=0).\;For Spectrum-1 this field must not be modified for an active port \;(a port which has traffic egressing through it). \;For Spectrum, setting SPVTR.epvid_mode will modify this field" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="vid_record" descr="See Table 775, &quot;VID Record Layout&quot;" access="RW" high_bound="254" low_bound="0" offset="0x4.0" size="0x3fc.0" />
</node>

<node name="spvmlr_ext" descr="" size="0x400.0" >
	<field name="num_rec" descr="Number of records to update. Each record contains: learn_enable\;Note: setting num_rec to &apos;0&apos; indicates one record (same as setting \;num_rec to one).\;" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="local_port" descr="Local port (receive)\;Not supported from CPU port\;Not supported from Router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="vid_learn_enable" descr="List of VLAN IDs and the learn enable state for each of the IDs.\;For layout, see Section 825, &quot;VID Learn Enable Layout,&quot; on \;page 921" access="RW" high_bound="254" low_bound="0" offset="0x4.0" size="0x3fc.0" />
</node>

<node name="spvtr_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="When tport = 0:\;Local port number\;Not supported from/to CPU\;When tport = 1: Tunnel port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="tport" descr="Port is tunnel port\;Reserved when SwitchX/-2 or Spectrum-1" access="INDEX" offset="0x0.24" size="0x0.1" />
	<field name="epvid_mode" descr="Egress Port VLAN-ID Mode\;0: IEEE Compliant VLAN membership\;1: pop VLAN (for VLAN stacking)\;For Spectrum family, this affects the values of SPVM.e,u,pt. And \;this fields is a WO" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="ipvid_mode" descr="Ingress Port VLAN-ID Mode\;0: IEEE Compliant PVID (default)\;1: push VLAN (for VLAN stacking, except prio tagged packets)\;2: always push VLAN (also for prio tagged packets) - reserved \;when SwitchX/-2\;For Spectrum/-2, this affects the values of SPVM.i" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="ipprio_mode" descr="Ingress Port Priority Mode\;This controls the PCP and DEI of the new outer VLAN\;Note: for SwitchX/-2 the DEI is not affected.\;0: use port default PCP and DEI (configured by QPDPC)\;1: use C-VLAN PCP and DEI\;See Section 11.13.13, &quot;QPDPC - QoS Port Default PCP,&quot; on \;page 1806\;Has no effect when ipvid_mode = 0\;Reserved when tport = 1. See TNQCR." access="RW" offset="0x4.20" size="0x0.4" />
	<field name="epve" descr="Egress Port VID Mode Update Enable\;When set, the Egress Port VID Mode is updated with the provided \;epvid_mode field" access="OP" offset="0x4.29" size="0x0.1" />
	<field name="ipve" descr="Ingress Port VID Mode Update Enable\;When set, the Ingress Port VID Mode is updated with the provided \;ipvid_mode field\;Reserved on Get operations" access="OP" offset="0x4.30" size="0x0.1" />
	<field name="ippe" descr="Ingress Port Prio Mode Update Enable\;When set, the Port Prio Mode is updated with the provided ippri\;o_mode field\;Reserved on Get operations" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="ethertype" descr="Ethertype to be used at egress when pushing new VLAN tag for \;VLAN stacking (default=0x8100)\;Reserved when Spectrum/-2" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="ete" descr="Ethertype Update Enable\;When set, the Ethertype is updated with the provided ethertype \;field\;Reserved when Spectrum/-2" access="OP" offset="0xC.31" size="0x0.1" />
</node>

<node name="spzr_ext" descr="" size="0x100.0" >
	<field name="enh_sw_p0" descr="When set, it enables enhanced switch port 0. Reported in \;NodeInfo.\;Otherwise, enhanced switch port 0 is disabled." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="ng" descr="Set node GUID to node_guid specified.\;node_guid and ng must be the same for all ports." access="WO" offset="0x0.9" size="0x0.1" />
	<field name="sig" descr="Set system image GUID to system_image_guid specified. \;system_image_guid and sig must be the same for all ports." access="WO" offset="0x0.10" size="0x0.1" />
	<field name="mp" descr="Change PKey table size to max_pkey.\;" access="WO" offset="0x0.11" size="0x0.1" />
	<field name="vk" descr="Set the internal GSA V_Key. Incoming VendorSpecific MADs \;must have matching V_Key to the one set by this command." access="WO" offset="0x0.12" size="0x0.1" />
	<field name="cm" descr="Set PortInfo:CapabilityMask to PortInfo:CapabilityMask speci\;fied." access="WO" offset="0x0.13" size="0x0.1" />
	<field name="enh_sw_p0_mask" descr="Enhanced switch port 0 mask. When 1, the EnhSwP0 field is valid \;(see below). When 0, the EnhSwP0 field is ignored." access="WO" offset="0x0.14" size="0x0.1" />
	<field name="ndm" descr="Node description mask. Set to 1 to write the NodeDescription \;field (see below).\;" access="WO" offset="0x0.15" size="0x0.1" />
	<field name="cm2" descr="Set PortInfo:CapabilityMask2 to PortInfo:CapabilityMask2 speci\;fied." access="WO" offset="0x0.16" size="0x0.1" />
	<field name="swid" descr="Switch partition to which the command applies" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="capability_mask" descr="Sets the PortInfoCapabilityMask:\;Specifies the supported capabilities of this node. A bit set to 1 for \;affirmation of supported capability.\;0: Reserved\;1: IsSM\;2: IsNoticeSupported\;3: IsTrapSupported\;4: Reserved\;5: IsAutomaticMigrationSupported\;6: IsSLMappingSupported\;7: IsMKeyNVRAM (supports M_Key in NVRAM)\;8: IsPKeyNVRAM (supports P_Key in NVRAM)\;9: IsLEDInfoSupported\;10: IsSMdisabled\;11: IsSystemImageGUIDSupported\;12: IsPKeySwitchExternalPortTrapSupported\;13-15: Reserved\;16: IsCommunicationManagementSupported\;17: IsSNMPTunnelingSupported\;18: IsReinitSupported\;19: IsDeviceManagementSupported\;20: IsVendorClassSupported\;21: IsDRNoticeSupported\;22: IsCapabilityMaskNoticeSupported\;23: IsBootManagementSupported\;24: IsLinkRoundTripLatencySupported\;25: IsClientReregistrationSupported\;26: IsOtherLocalChangesNoticeSupported\;27: IsLinkSpeedWidthPairsTableSupported\;28-31: Reserved" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="system_image_guid_h" descr="System Image GUID, takes effect only if the sig bit is set. Must be \;the same for both ports." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="system_image_guid_l" descr="System Image GUID, takes effect only if the sig bit is set. Must be \;the same for both ports." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="node_guid_h" descr="Node GUID, takes effect only if the ng bit is set\;Must be the same for both ports." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="node_guid_l" descr="Node GUID, takes effect only if the ng bit is set\;Must be the same for both ports." access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="v_key_h" descr="The internal GSA V_Key. Incoming VendorSpecific MADs must \;have a V_Key matching the one set by this command. If not speci\;fied, then must be set to 0.\;Takes effect only if the VK bit is set." access="RW" offset="0x20.0" size="0x4.0" />
	<field name="v_key_l" descr="The internal GSA V_Key. Incoming VendorSpecific MADs must \;have a V_Key matching the one set by this command. If not speci\;fied, then must be set to 0.\;Takes effect only if the VK bit is set." access="RW" offset="0x24.0" size="0x4.0" />
	<field name="capability_mask2" descr="" access="RW" offset="0x28.0" size="0x4.0" />
	<field name="max_pkey" descr="Maximum pkeys for the port.\;Must be the same for both ports.\;Takes effect if the mp bit is set" access="RO" offset="0x2C.16" size="0x0.16" />
	<field name="node_description" descr="Text string that describes the node" access="RW" high_bound="15" low_bound="0" offset="0x30.0" size="0x40.0" />
</node>

<node name="sspr_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port to send the packet" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="m" descr="Master - if set then this record describes the master system port. \;Only one master system port is allowed per local port.\;Must be set for Spectrum" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="system_port" descr="Unique port identifier for the final destination of the packet\;Range is 1 to cap_max_system_port\;For Spectrum see the cap_max_system_port at Appendix A.8, \;&quot;Ethernet Switching Resources&quot; (page 2272)" access="INDEX" offset="0x4.0" size="0x0.16" />
</node>

<node name="stat_bufferx_reg" descr="" size="0x8.0" >
	<field name="watermark" descr="Watermark in cells (max buffer usage since last clear)" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="used_buffer" descr="Number of used buffer cells." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="string_db_parameters" descr="" size="0x8.0" >
	<field name="string_db_base_address" descr="Offset of the first string of the section, relative to the entire string \;data base, given in bytes." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="string_db_size" descr="Size of string database section, given in bytes" access="RO" offset="0x4.0" size="0x0.24" />
</node>

<node name="sver_ext" descr="" size="0x10.0" >
	<field name="ether_type0" descr="VLAN EtherType0\;Used for VLAN parsing, pushing, Mirroring and ACL actions\;Default: 0x8100" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="ether_type1" descr="VLAN EtherType1\;Used for VLAN parsing, pushing, Mirroring and ACL actions\;Default: 0x88A8" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="ether_type2" descr="VLAN Ether type2\;Used for VLAN parsing, pushing, Mirroring and ACL actions" access="RW" offset="0xC.16" size="0x0.16" />
</node>

<node name="svfa_ext" descr="" size="0x18.0" >
	<field name="v" descr="Valid\;Indicates the VID to FID mapping entry is valid. \;Reserved when SwitchX/-2, where entries are always valid and \;can not be invalidated regardless of the v bit value." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="mapping_table" descr="Mapping table:\;0: VLAN_mapping_table - VID to FID mapping\;1: Port_VLAN_mapping_table - {Port,VID} to FID mapping\;2: VNI_mapping_table - VNI to FID mapping. Reserved when \;ubridge = 0" access="INDEX" enum="VLAN_mapping_table=0x0,Port_VLAN_mapping_table=0x1,VNI_mapping_table=0x2" offset="0x0.8" size="0x0.3" />
	<field name="local_port" descr="Local port number\;Reserved when mapping_table = &apos;0&apos; (VLAN mapping)\;Reserved when mapping_table = &apos;2&apos; (VNI mapping)" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="vid" descr="VLAN ID\;Reserved when mapping_table = &apos;2&apos; (VNI mapping)" access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="fid" descr="Filtering ID\;Cannot be modified for a valid (v=1) mapping\;Reserved when trap_action is TRAP or DISCARD_ERROR\;" access="RW" offset="0x4.16" size="0x0.16" />
	<field name="counter_index" descr="Counter Index for flow counters.\;For Spectrum/-2: see Section 4.2, &quot;Flow Counters,&quot; on page 622\;Reserved when SwitchX/-2" access="RW" offset="0x8.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters.\;For Spectrum/-2: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622\;Spectrum-2: Note that for router-sub-port at the FID after routing \;there is no counting. If need counter then use fid-rif. \;Also when iACL set fis then no fid counting. \;Reserved when SwitchX/-2" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="trap_action" descr="Trap Action\;0x0: NOP\;0x1: TRAP\;0x2: MIRROR_TO_CPU\;0x3: MIRROR\;0x4: DISCARD_ERROR\;For TRAP and MIRROR_TO_CPU the trap-ID is FID_TRAP\;Reserved when SwitchX/-2\;Spectrum-2 - note that for router-sub-port, at the FID after routing \;there is no trap (behavior is NOP). If need trap then use fid-rif\;" access="RW" enum="NOP=0x0,TRAP=0x1,MIRROR_TO_CPU=0x2,MIRROR=0x3,DISCARD_ERROR=0x4" offset="0xC.28" size="0x0.4" />
	<field name="vni" descr="vni\;Reserved when mapping_table != &apos;2&apos; (VNI mapping table)" access="INDEX" offset="0x10.0" size="0x0.24" />
	<field name="irif" descr="Ingress RIF (Router Interface)\;Range is 0.. cap_max_router_interfaces-1\;Reserved when ubridge = 0\;Reserved when irif_v = 0\;\;" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="irif_v" descr="Ingress RIF valid:\;0: irif is not valid, no irif assigned\;1: irif valid\;Must not be set for a non enabled RIF\;Reserved when ubridge = 0" access="RW" offset="0x14.24" size="0x0.1" />
</node>

<node name="svmlr_ext" descr="" size="0x8.0" >
	<field name="swid" descr="Switch partition ID\;Reserved when Spectrum/-2" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="vid" descr="VLAN ID" access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="learn_enable" descr="Enable learning on this VLAN.\;(Learn means generating a learning notification to the software)\;Note: learning is enabled only if all enables are set (spanning tree, \;port-vid, global)" access="RW" offset="0x4.31" size="0x0.1" />
</node>

<node name="svpe_ext" descr="" size="0x4.0" >
	<field name="vp_en" descr="Virtual Port Enable:\;0: VLAN mode, ingress VID to FID mapping\;1: Virtual Port mode, ingress {Port,VID} to FID mapping" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="local_port" descr="Ingress local port number\;Not supported for CPU port (CPU port uses VLAN mode)\;" access="INDEX" offset="0x0.16" size="0x0.8" />
</node>

<node name="switch_prio" descr="" size="0x10.0" >
	<field name="ecn" descr="The EXP mapping for ECN j, see Table 1849, &quot;ecn&lt;j&gt; Layout&quot;" subnode="ecn" access="RW" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="switch_prio_j" descr="" size="0x4.0" >
	<field name="color2" descr="The PCP and DEI mapping for color k, where k=0..2, see \;Table 1863, &quot;color&lt;k&gt;Layout&quot;" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="color1" descr="The PCP and DEI mapping for color k, where k=0..2, see \;Table 1863, &quot;color&lt;k&gt;Layout&quot;" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="color0" descr="The PCP and DEI mapping for color k, where k=0..2, see \;Table 1863, &quot;color&lt;k&gt;Layout&quot;" access="RW" offset="0x0.24" size="0x0.8" />
</node>

<node name="tcam_region_info_peaps" descr="" size="0x10.0" >
	<field name="byte" descr="adabe only\;bytes of tcam_region_info" access="WO" high_bound="15" low_bound="0" offset="0x0.24" size="0x10.0" />
</node>

<node name="tcam_region_info_prcr" descr="" size="0x10.0" >
	<field name="byte" descr="adabe only\;bytes of tcam_region_info" access="WO" high_bound="15" low_bound="0" offset="0x0.24" size="0x10.0" />
</node>

<node name="tcam_region_info_ptar" descr="" size="0x10.0" >
	<field name="byte" descr="adabe only\;bytes of tcam_region_info" access="WO" high_bound="15" low_bound="0" offset="0x0.24" size="0x10.0" />
</node>

<node name="tcam_region_info_ptce" descr="" size="0x10.0" >
	<field name="byte" descr="adabe only\;bytes of tcam_region_info" access="WO" high_bound="15" low_bound="0" offset="0x0.24" size="0x10.0" />
</node>

<node name="tcam_region_info_ptce_v2" descr="" size="0x10.0" >
	<field name="byte" descr="adabe only\;bytes of tcam_region_info" access="WO" high_bound="15" low_bound="0" offset="0x0.24" size="0x10.0" />
</node>

<node name="tcam_region_info_ptce_v3" descr="" size="0x10.0" >
	<field name="byte" descr="adabe only\;bytes of tcam_region_info" access="WO" high_bound="15" low_bound="0" offset="0x0.24" size="0x10.0" />
</node>

<node name="tcam_region_info_ptcead" descr="" size="0x10.0" >
	<field name="byte" descr="adabe only\;bytes of tcam_region_info" access="WO" high_bound="15" low_bound="0" offset="0x0.24" size="0x10.0" />
</node>

<node name="tidem_ext" descr="" size="0xc.0" >
	<field name="eip_ecn" descr="Egress IP ECN\;ECN field of the IP header of the packet which goes out from \;the decapsulation" access="RW" offset="0x4.8" size="0x0.2" />
	<field name="overlay_ecn" descr="ECN field of the IP header in the overlay network" access="INDEX" offset="0x4.16" size="0x0.2" />
	<field name="underlay_ecn" descr="ECN field of the IP header in the underlay network" access="INDEX" offset="0x4.24" size="0x0.2" />
	<field name="trap_id" descr="Trap ID\;Trap-ID is DECAP_ECN0 or DECAP_ECN1\;Reserved when trap_en is &apos;0&apos;" access="RW" offset="0x8.0" size="0x0.9" />
	<field name="trap_en" descr="Trap enable:\;0: no trap due to decap ecn\;1: trap enable with trap_id. HPKT can control the trap action. \;See Section 2.15.3, &quot;HPKT - Host PacKet Trap,&quot; on page 379" access="RW" offset="0x8.28" size="0x0.4" />
</node>

<node name="tieem_ext" descr="" size="0xc.0" >
	<field name="underlay_ecn" descr="ECN of the IP header in the underlay network." access="RW" offset="0x4.16" size="0x0.2" />
	<field name="overlay_ecn" descr="ECN of the IP header in the overlay network.\;If the packet has no IP header, the encapsulation uses the \;mapped value for overlay_ecn of 0." access="INDEX" offset="0x4.24" size="0x0.2" />
</node>

<node name="tigcr_ext" descr="" size="0x18.0" >
	<field name="ipip_ttl_uc" descr="The TTL for IPinIP Tunnel encapsulation of underlay unicast pack\;ets." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ipip_ttlc" descr="For IPinIP Tunnel encapsulation: TTL Copy from inner:\;0: use ipip_ttl_uc\;1: copy the ttl from the packet header." access="RW" offset="0x4.8" size="0x0.1" />
	<field name="ipip_fl_suffix" descr="IPIP Flow Label Suffix\;For IPinIP Tunnel encapsulation: Constant 12 most significant bits \;of the flow label. \;Reserved when ipip_flh = 1\;Reserved when Spectrum-1\;*** Note: this field is not supported by current FW, the value is \;always &apos;0&apos; *** \;" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="ipip_fl_prefix" descr="For IPinIP Tunnel encapsulation:\;Constant 12 most significant bits of the flow label. \;Spectrum-1: reserved when ipip_flh = 0\;Spectrum-2: not reserved" access="RW" offset="0xC.8" size="0x0.12" />
	<field name="ipip_flh" descr="For IPinIP Tunnel encapsulation:\;0: Flow Label is static\;- Spectrum-1: &apos;0&apos;\;- Spectrum-2: by {ipip_fl_prefix, ipip_fl_suffix}\;1: Flow Label 8 least significant bits are calculated from ECMP \;hash, and 12msb are configured by ipip_fl_prefix\;See Section 13.10.7, &quot;RECR - Router ECMP Configuration Regis\;ter,&quot; on page 1916, Section 13.10.8, &quot;RECR_V2 - Router ECMP \;Configuration Version 2 Register,&quot; on page 1917" access="RW" offset="0xC.24" size="0x0.1" />
	<field name="ipip_flc" descr="For IPinIP Tunnel encapsulation: Flow Label Copy from inner \;0: Calculate flow label using ipip_flh.\;1: If packet is IPv6 and encapsulation is IPv6, copy the whole flow \;label from the packet header. Otherwise, calculate flow label using \;ipip_flh." access="RW" offset="0xC.25" size="0x0.1" />
	<field name="ipip_gre_key_for_hash" descr="For IPinIP Tunnel encapsulation: \;The 24 most significant bits of the GRE key when type is IP with \;GRE with a key and the key is set by ECMP hash\;See Section 13.10.7, &quot;RECR - Router ECMP Configuration Regis\;ter,&quot; on page 1916, Section 13.10.8, &quot;RECR_V2 - Router ECMP \;Configuration Version 2 Register,&quot; on page 1917" access="RW" offset="0x14.8" size="0x0.24" />
</node>

<node name="tiqcr_ext" descr="" size="0xc.0" >
	<field name="enc_pcp_rw" descr="For encapsulation: how to handle the pcp_rewrite_en:\;0: Preserve the value of the pcp_rewrite_en\;2: Clear the pcp_rewrite_en\;3: Set the pcp_rewrite_en" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="enc_dscp_rw" descr="For encapsulation: how to handle the dscp_rewrite_en:\;0: Preserve the value of the dscp_rewrite_en\;2: Clear the dscp_rewrite_en\;3: Set the dscp_rewrite_en" access="RW" offset="0x4.2" size="0x0.2" />
	<field name="enc_set_sp" descr="For encapsulation: how to set Switch Priority and packet Color:\;0: Preserve Switch Priority and packet Color\;1: Set new Switch Priority and packet Color as configured by \;TIQDR.\;See Section 16.5.3, &quot;TIQDR - Tunneling IPinIP QoS Default Regis\;ter,&quot; on page 2156" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="enc_set_dscp" descr="For encapsulation: how to set DSCP field:\;0: Copy the DSCP from the overlay (inner) IP header to the underlay \;(outer) IP header. If there is no IP header, use TIQDR.dscp\;1: Set the DSCP field as the TIQDR.dscp\;The dscp field is configured by TIQDR. See Table 2206, &quot;TIQDR - \;Tunneling IPinIP QoS Default Register Layout,&quot; on page 2156" access="RW" offset="0x4.28" size="0x0.1" />
	<field name="dec_pcp_rw" descr="For decapsulation: how to handle the pcp_rewrite_en:\;0: Preserve the value of the pcp_rewrite_en\;2: Clear the pcp_rewrite_en\;3: Set the pcp_rewrite_en" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="dec_dscp_rw" descr="For decapsulation: how to handle the dscp_rewrite_en:\;0: Preserve the value of the dscp_rewrite_en\;2: Clear the dscp_rewrite_en\;3: Set the dscp_rewrite_en" access="RW" offset="0x8.2" size="0x0.2" />
	<field name="dec_set_sp" descr="For decapsulation: how to set Switch Priority and packet Color:\;0: Preserve Switch Priority\;1: Set a new Switch Priority from overlay DSCP as configured by \;RDPM (of the overlay packet, later the overlay router may re-mod\;ify).\;See Section 13.10.20, &quot;RDPM - Router DSCP to Priority Mapping \;Register,&quot; on page 1956" access="RW" offset="0x8.24" size="0x0.1" />
	<field name="dec_set_dscp" descr="For decapsulation: how to set the overlay DSCP field, if exists, \;while stripping off the underlay headers:\;0: Preserve inner DSCP\;1: Copy the DSCP from the underlay IP header" access="RW" offset="0x8.28" size="0x0.1" />
</node>

<node name="tiqdr_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number (receive port)\;Supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dscp" descr="For encapsulation, the default DSCP" access="RW" offset="0x4.0" size="0x0.6" />
	<field name="switch_prio" descr="For encapsulation, the default values of Switch Priority" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="color" descr="For encapsulation, the default values of packet Color" access="RW" offset="0x4.24" size="0x0.2" />
</node>

<node name="tncr_ext" descr="" size="0x30.0" >
	<field name="clear_counters" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="count_encap_high" descr="Count number of packets which did encapsulation to NVE tun\;neling\;Note that MC packets which are encapsulated multiple times are \;counted multiple times" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="count_encap_low" descr="Count number of packets which did encapsulation to NVE tun\;neling\;Note that MC packets which are encapsulated multiple times are \;counted multiple times" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="count_decap_high" descr="Count number of packets which did decapsulation from NVE \;tunneling" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="count_decap_low" descr="Count number of packets which did decapsulation from NVE \;tunneling" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="count_decap_errors_high" descr="Count number of packets had decapsulation errors of NVE tun\;neling" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="count_decap_errors_low" descr="Count number of packets had decapsulation errors of NVE tun\;neling" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="count_decap_discards_high" descr="Count number of packets had decapsulation discards of NVE \;tunneling" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="count_decap_discards_low" descr="Count number of packets had decapsulation discards of NVE \;tunneling" access="RO" offset="0x2C.0" size="0x4.0" />
</node>

<node name="tncr_v2_ext" descr="" size="0x38.0" >
	<field name="tunnel_port" descr="Tunnel port:\;0: NVE\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="clear_counters" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="count_decap_discards_high" descr="Count number of packets had decapsulation discards of NVE \;tunneling" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="count_decap_discards_low" descr="Count number of packets had decapsulation discards of NVE \;tunneling" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="count_encap_discards_high" descr="Count number of packets had encapsulation discards of NVE \;tunneling" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="count_encap_discards_low" descr="Count number of packets had encapsulation discards of NVE \;tunneling" access="RO" offset="0x34.0" size="0x4.0" />
</node>

<node name="tndem_ext" descr="" size="0xc.0" >
	<field name="eip_ecn" descr="Egress IP ECN\;ECN field of the IP header of the packet which goes out from the \;decapsulation" access="RW" offset="0x4.8" size="0x0.2" />
	<field name="overlay_ecn" descr="ECN field of the IP header in the overlay network\;If the packet has no overlay IP header, the decapsulation uses the \;mapped value &apos;0&apos;" access="INDEX" offset="0x4.16" size="0x0.2" />
	<field name="underlay_ecn" descr="ECN field of the IP header in the underlay network" access="INDEX" offset="0x4.24" size="0x0.2" />
	<field name="trap_id" descr="Trap ID\;Trap-ID is DECAP_ECN0 or DECAP_ECN1\;Reserved when trap_en is &apos;0&apos;" access="RW" offset="0x8.0" size="0x0.9" />
	<field name="trap_en" descr="Trap enable:\;0: no trap due to decap ecn\;1: trap enable with trap_id. HPKT can control the trap action. \;See Section 2.15.3, &quot;HPKT - Host PacKet Trap,&quot; on page 379" access="RW" offset="0x8.28" size="0x0.4" />
</node>

<node name="tneem_ext" descr="" size="0xc.0" >
	<field name="underlay_ecn" descr="ECN of the IP header in the underlay network" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="overlay_ecn" descr="ECN of the IP header in the overlay network\;Note: if overlay packet did not have ECN then the overlay ECN \;of the packet is considered as 0x0\;For Spectrum familiy only, MPLS packets use overlay_ecn of 00\;\;For Spectrum-2, MPLS packets use the packet overlay_ecn" access="INDEX" offset="0x4.24" size="0x0.2" />
</node>

<node name="tngcr_ext" descr="" size="0x44.0" >
	<field name="type" descr="Tunnel type for Encapsulation:\;0: Tunnel is VXLAN\;1: Tunnel is VXLAN-GPE\;2: Tunnel is GENEVE\;3: Tunnel is NVGRE\;Note: for Spectrum-1 the NVE parsing must be enabled, see \;Section 4.12.7, &quot;MPRS - Monitoring Parsing State Register,&quot; on \;page 708, see parsing_en field\;The types are mutually exclusive\;For Spectrum family: type must not be modified under traffic of \;NVE tunneling encapsulation or decapsulation." access="RW" offset="0x0.0" size="0x0.4" />
	<field name="nve_ttl_uc" descr="The TTL for NVE Tunnel encapsulation underlay unicast pack\;ets." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="nve_ttlc" descr="For NVE Tunnel encapsulation: TTL Copy from inner:\;0: use nve_ttl_uc (for UC) or nve_ttl_mc (for MC).\;1: copy the ttl from the packet header.\;Reserved when Spectrum-1" access="RW" offset="0x4.8" size="0x0.1" />
	<field name="nve_decap_ttl" descr="Configures the overlay TTL at decap\;0: PRESERVE - The overlay TTL is as is from the overlay. \;Spectrum-1 supports this mode only.\;\;1: COPY - The overlay TTL is taken from the underlay. \;\;2: MINIMUM - The overlay TTL is the minimum value between \;underlay and overlay TTL.\;For all cases, the later overlay router will decrement the TTL. \;Note: same config for UC and for MC\;Reserved when Spectrum-1" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="nve_ttl_mc" descr="The TTL for NVE Tunnel encapsulation of underlay multicast \;packets." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="nve_fl_suffix" descr="NVE Flow Label Suffix\;For NVE Tunnel encapsulation: Constant 8 least significant bits \;of the flow label. \;Reserved when nve_flh = 1\;*** Note: this field is not supported by current FW, the value is \;always &apos;0&apos; *** \;Reserved when Spectrum-1\;" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="nve_fl_prefix" descr="NVE Flow Label Prefix\;For NVE Tunnel encapsulation: Constant 12 most significant \;bits of the flow label. \;Spectrum-1: reserved when nve_flh = 0\;Spectrum-2: not reserved" access="RW" offset="0xC.8" size="0x0.12" />
	<field name="nve_flh" descr="NVE Flow Label Hash\;For NVE Tunnel encapsulation:\;0: Flow Label is static\;- Spectrum-1: &apos;0&apos;\;- Spectrum-2: by {nve_fl_prefix, nve_fl_suffix}\;1: Flow Label 8 least significant bits are calculated from ECMP \;hash, and 12msb are configured by nve_fl_prefix\;See Section 13.10.7, &quot;RECR - Router ECMP Configuration \;Register,&quot; on page 1917, Section 13.10.8, &quot;RECR_V2 - Router \;ECMP Configuration Version 2 Register,&quot; on page 1918" access="RW" offset="0xC.24" size="0x0.1" />
	<field name="nve_flc" descr="For NVE Tunnel encapsulation: Flow Label Copy from inner \;0: Calculate flow label using nve_flh.\;1: If packet is IPv6 and encapsulation is IPv6, copy the whole \;flow label from the packet header. Otherwise, calculate flow \;label using nve_flh." access="RW" offset="0xC.25" size="0x0.1" />
	<field name="nve_udp_sport_prefix" descr="NVE UDP Source Port Prefix\;Constant 8 most significant bits of the NVE UDP source port.\;For Spectrum: the 8 least significant bits are set by LAG hash\;See Section 6.12.24, &quot;SLCR_V2 - Switch LAG Configuration 2 \;Register,&quot; on page 902, Section 6.12.24, &quot;SLCR_V2 - Switch \;LAG Configuration 2 Register,&quot; on page 902.\;For Spectrum-2: the 8 least significant bits are set by ECMP \;hash, see Section 13.10.7, &quot;RECR - Router ECMP Configura\;tion Register,&quot; on page 1917, Section 13.10.8, &quot;RECR_V2 - \;Router ECMP Configuration Version 2 Register,&quot; on page 1918\;Reserved when NVE Tunnel encapsulation is NVGRE" access="RW" offset="0x10.8" size="0x0.8" />
	<field name="et_vlan" descr="EtherType used for when VLAN is pushed at decap \;0: ether_type0 (default)\;1: ether_type1\;2: ether_type2 \;Ethertype IDs are configured by SVER, see Section 6.12.33, \;&quot;SVER - Switch VLAN EtherType Register,&quot; on page 920\;Reserved when Spectrum-2, see SPVID" access="RW" offset="0x10.20" size="0x0.2" />
	<field name="nve_udp_sport_type" descr="NVE UDP source port type\;For NVE Tunnel encapsulation (VXLAN, VXLAN-GPE or \;GENEVE):\;0: Source UDP is fixed (default &apos;0&apos;)\;1: Source UDP 8 least significant bits are calculated from hash, \;and 8msb are configured by nve_src_udp_port_prefix\;For NVE Tunnel encapsulation (NVGRE):\;0: NVGRE.flow_id is &apos;0&apos;\;1: NVGRE.flow_id (8 bits) is set by hash\;For Spectrum-1: use LAG hash, see Section 6.12.23, &quot;SLCR - \;Switch LAG Configuration Register,&quot; on page 900, \;Section 6.12.24, &quot;SLCR_V2 - Switch LAG Configuration 2 \;Register,&quot; on page 902.\;For Spectrum-2: use ECMP hash, see Section 13.10.7, &quot;RECR - \;Router ECMP Configuration Register,&quot; on page 1917, \;Section 13.10.8, &quot;RECR_V2 - Router ECMP Configuration Ver\;sion 2 Register,&quot; on page 1918\;" access="RW" offset="0x10.24" size="0x0.1" />
	<field name="nve_enc_orig_we" descr="Write enable to nve_enc_orig\;Reserved when Spectrum-2" access="WO" offset="0x10.30" size="0x0.1" />
	<field name="nve_enc_orig" descr="VLAN handling of overlay packet at encap:\;0: STRIP_TAG - 1 VLAN tag is stripped (if existed at ingress) \;(default)\;1: KEEP_ORIG - all VLAN tags of original packet are kept \;When overlay router and KEEP_ORIG the inner vid is 0\;Reserved when Spectrum-2, see SPVTR.epvid_mode" access="RW" offset="0x10.31" size="0x0.1" />
	<field name="nve_group_size_mc" descr="For NVE Tunnel multicast:\;The amount of sequential link lists of MC entries. The first link \;list is configured by SFD.underlay_mc_ptr\;Valid ranges:\;1, 2, 4, 8 16, 32, 64\;The link lists are configured by TNUMT\;The hash is set by LAG hash\;See Section 15.11.6, &quot;TNUMT - Tunneling NVE Underlay Mul\;ticast Table Register,&quot; on page 2130\;See Section 6.12.24, &quot;SLCR_V2 - Switch LAG Configuration 2 \;Register,&quot; on page 902, Section 6.12.24, &quot;SLCR_V2 - Switch \;LAG Configuration 2 Register,&quot; on page 902.\;Reserved when Spectrum-2 and on" access="RW" offset="0x18.0" size="0x0.8" />
	<field name="nve_group_size_flood" descr="For NVE Tunnel flooding or BC:\;The amount of sequential link lists of flooding or BC entries. \;The first link list is configured by SFMR.nve_tunnel_flood_ptr\;Valid ranges:\;1, 2, 4, 8 16, 32, 64\;\;The link lists are configured by TNUMT\;The hash is set by LAG hash\;See Section 15.11.6, &quot;TNUMT - Tunneling NVE Underlay Mul\;ticast Table Register,&quot; on page 2130\;See Section 6.12.24, &quot;SLCR_V2 - Switch LAG Configuration 2 \;Register,&quot; on page 902, Section 6.12.24, &quot;SLCR_V2 - Switch \;LAG Configuration 2 Register,&quot; on page 902.\;Reserved when Spectrum-2 and on" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="underlay_virtual_router" descr="Underlay virtual router\;Reserved when Spectrum-2" access="RW" offset="0x20.0" size="0x0.16" />
	<field name="learn_enable" descr="When decap:\;Enable learning from NVE port\;Reserved when Spectrum-2, see TNPC" access="RW" offset="0x20.31" size="0x0.1" />
	<field name="underlay_rif" descr="Underlay ingress router interface\;Reserved when Spectrum-1" access="RW" offset="0x24.0" size="0x0.16" />
	<field name="usipv4" descr="Underlay Source IPv4 address of the NVE\;For Spectrum family: usipv4 must not be modified under traffic \;of NVE tunneling encapsulation." access="RW" offset="0x28.0" size="0x4.0" />
	<field name="usipv6" descr="Underlay Source IPv6 address of the NVE\;For Spectrum family: usipv6 must not be modified under traffic \;of NVE tunneling encapsulation.\;" access="RW" high_bound="3" low_bound="0" offset="0x30.0" size="0x10.0" />
	<field name="header0_bit_set" descr="For VXLAN/VXLAN-GPE/GENEVE header:\;Set bits to &apos;1&apos;\;The device will do an OR function with the default header0\;Header0 is the first 4B in the header\;Reserved when type = 3 (NVGRE)" access="RW" offset="0x40.0" size="0x4.0" />
</node>

<node name="tngee_ext" descr="" size="0x60.0" >
	<field name="l2_enc_index" descr="Index to L2 encap entry\;For Spectrum familiy the index is to the KVD linear, see Appen\;dix A.3.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2254)" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="tunnel_type" descr="Tunnel type:\;0: NVE (L2 enc NVE)\;" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="next_l2_enc_ptr" descr="Index to next L2 encap entry\;Note: may be point either to a TNGEE entry or to a TNUMT \;entry. \;For Spectrum-2 ... KVH ...\;Reserved when vnext = 0\;" access="RW" offset="0x8.0" size="0x0.24" />
	<field name="vnext" descr="Next valid\;The next_l2_enc_index is valid\;" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="ecmp_size" descr="ecmp_size is the amount of sequential entries starting from nex\;t_l2_enc_ptr (the number of ECMPs).\;Values: 1-128, 256, 512, 1024, 2048 and 4096\;Reserved when vnext = 0" access="RW" offset="0xC.0" size="0x0.13" />
	<field name="uirif" descr="Underlay Ingress Router Interface\;Valid range is 0..cap_max_router_interfaces - 1" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="protocol" descr="Protocol:\;0: IPv4\;1: IPv6" access="RW" enum="IPv4=0x0,IPv6=0x1" offset="0x10.28" size="0x0.1" />
	<field name="udip" descr="If protocol is IPv4:\;The underlay destination IPv4 of the remote VTEP (the least sig\;nificant bits)\;Else if protocol is IPv6:\;A pointer to the IPv6 address of the remote VTEP destination in \;the overlay network. See Section 13.10.19, &quot;RIPS - Router IP \;version Six Register,&quot; on page 1956.\;When protocol is IPv4 and udip=0 then no replication, the uirif, \;entry have no significance." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="counter_index" descr="Counter Index for flow counters\;For Spectrum: see Section 4.2, &quot;Flow Counters,&quot; on page 622" access="RW" offset="0x3C.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type for flow counters\;For Spectrum: See Section 4.2.2, &quot;Counter Set Type,&quot; on \;page 622" access="RW" offset="0x3C.24" size="0x0.8" />
	<field name="entry" descr="Entry\;See Table 2169, &quot;TNGEE - NVE Layout,&quot; on page 2126" access="RW" high_bound="7" low_bound="0" offset="0x40.0" size="0x20.0" />
</node>

<node name="tnifr_ext" descr="" size="0x60.0" >
	<field name="tunnel_port" descr="Tunnel port:\;0: NVE\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="port_filter" descr="Port filter bitmask\;0: Do not filter (default value for all local_port)\;1: Filter - Packets coming from port_filter&lt;i&gt; will not be trans\;mitted to port NVE\;All LAG ports must share the same configuration.\;" access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="port_filter_update_en" descr="Port filter update enable bitmask\;0: Mask disable - do not modify relevant port_filter bit\;1: Mask enable - modify relevant port_filter bit" access="OP" high_bound="7" low_bound="0" offset="0x40.0" size="0x20.0" />
</node>

<node name="tnpc_ext" descr="" size="0x1c.0" >
	<field name="learn_enable_v4" descr="When decap:\;Enable learning from tunnel port for IPv4 packets" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="lb_tx_uc_tunnel_port" descr="For unicast packets:\;Bit0: Allow loopback from NVE to NVE\;Values:\;0: loopback_filter - (default)\;1: loopback_allowed\;" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="lb_tx_mc_tunnel_port" descr="For multicast packets:\;Bit0: Allow loopback filter from NVE to NVE\;Values:\;0: loopback filter (default)\;1: loopback allowed\;" access="RW" offset="0x18.0" size="0x4.0" />
</node>

<node name="tnqcr_ext" descr="" size="0xc.0" >
	<field name="enc_pcp_rw" descr="For encapsulation: how to handle the pcp_rewrite_en:\;0: Preserve the value of the pcp_rewrite_en\;2: Clear the pcp_rewrite_en\;3: Set the pcp_rewrite_en" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="enc_dscp_rw" descr="For encapsulation: how to handle the dscp_rewrite_en:\;0: Preserve the value of the dscp_rewrite_en\;2: Clear the dscp_rewrite_en\;3: Set the dscp_rewrite_en" access="RW" offset="0x4.2" size="0x0.2" />
	<field name="enc_set_sp" descr="For encapsulation: how to set Switch Priority and packet Color:\;0: Preserve Switch Priority and packet Color\;1: Set new Switch Priority and packet Color as configured by \;TNQDR.\;See Section 15.11.8, &quot;TNQDR - Tunneling NVE QoS Default \;Register,&quot; on page 2135" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="enc_set_dscp" descr="For encapsulation: how to set DSCP field:\;0: Copy the DSCP from the overlay (inner) IP header to the \;underlay (outer) IP header. If there is no IP header, use \;TNQDR.dscp\;1: Set the DSCP field as the TNQDR.dscp\;The dscp field is configured in TNQDR register. See \;Section 15.11.8, &quot;TNQDR - Tunneling NVE QoS Default Regis\;ter,&quot; on page 2135" access="RW" offset="0x4.28" size="0x0.1" />
	<field name="dec_pcp_rw" descr="For decapsulation: how to handle the pcp_rewrite_en:\;0: Preserve the value of the pcp_rewrite_en\;2: Clear the pcp_rewrite_en\;3: Set the pcp_rewrite_en" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="dec_dscp_rw" descr="For decapsulation: how to handle the dscp_rewrite_en:\;0: Preserve the value of the dscp_rewrite_en\;2: Clear the dscp_rewrite_en\;3: Set the dscp_rewrite_en" access="RW" offset="0x8.2" size="0x0.2" />
	<field name="dec_set_pcp" descr="For decapsulation: how to set the overlay PCP,DEI fields:\;0: Preserve/Set inner PCP,DEI when push. When untagged push \;value of 0 for PCP,DEI \;1: Copy the PCP,DEI from the underlay L2 header (default)\;Note: Spc-1 supports only &apos;1&apos; Copy\;Reserved when Spectrum-1" access="RW" offset="0x8.20" size="0x0.1" />
	<field name="dec_set_sp" descr="For decapsulation: how to set Switch Priority and packet Color:\;0: Preserve Switch Priority\;1: Set a new Switch Priority from overlay DSCP as configured \;by RDPM (of the overlay packet, even if not routed).\;See Section 13.10.20, &quot;RDPM - Router DSCP to Priority Map\;ping Register,&quot; on page 1957." access="RW" offset="0x8.24" size="0x0.1" />
	<field name="dec_set_dscp" descr="For decapsulation: how to set the overlay DSCP field, if exists, \;while stripping off the underlay headers:\;0: Preserve inner DSCP\;1: Copy the DSCP from the underlay IP header" access="RW" offset="0x8.28" size="0x0.1" />
</node>

<node name="tnqdr_ext" descr="" size="0x8.0" >
	<field name="local_port" descr="Local port number (receive port)\;Supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dscp" descr="For encapsulation, the default DSCP" access="RW" offset="0x4.0" size="0x0.6" />
	<field name="switch_prio" descr="For encapsulation, the default values of Switch Priority" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="color" descr="For encapsulation, the default values of packet Color" access="RW" offset="0x4.24" size="0x0.2" />
</node>

<node name="tnumt_ext" descr="" size="0x20.0" >
	<field name="underlay_mc_ptr" descr="Index to the Underlay Multicast Table\;For Spectrum familiy the index is to the KVD linear, see Appen\;dix A.3.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2254)\;May point also to TNGEE\;" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="record_type" descr="0: IPv4\;1: IPv6" access="RW" enum="IPv4=0x0,IPv6=0x1" offset="0x0.28" size="0x0.4" />
	<field name="next_underlay_mc_ptr" descr="The next index to the Underlay Multicast Table\;For Spectrum familiy the index is to the KVD linear, see Appen\;dix A.3.1.2, &quot;KVD Central Database Linear Entries&quot; \;(page 2254)" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="vnext" descr="Next valid\;The next_underlay_mc_ptr is valid" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="record" descr="If type is IPV4, the record is detailed on Table 2177, &quot;Record - \;Tunnel MC IPV4 Layout,&quot; on page 2131\;If type is IPV6, the record is detailed on Table 2179, &quot;Record - \;Tunnel MC IPV6 Layout,&quot; on page 2132" subnode="tnumt_record_auto_ext" access="RW" offset="0x8.0" size="0x18.0" union_selector="$(parent).record_type" />
</node>

<node name="tnumt_record_auto_ext" descr="" attr_is_union="1" size="0x18.0" >
	<field name="tunnel_mc_ipv4_ext" descr="" subnode="tunnel_mc_ipv4_ext" offset="0x0.0" selected_by="IPv4" size="0x18.0" />
	<field name="tunnel_mc_ipv6_ext" descr="" subnode="tunnel_mc_ipv6_ext" offset="0x0.0" selected_by="IPv6" size="0x18.0" />
</node>

<node name="tunnel_mc_ipv4_ext" descr="" size="0x18.0" >
	<field name="size" descr="Number of IP addresses in the record\;Range is 1..cap_max_nve_mc_entries_ipv4" access="RW" offset="0x0.0" size="0x0.3" />
	<field name="udip" descr="The underlay IPv4 addresses, while i=0 .. (size-1).\;udip&lt;i&gt; is reserved if i &gt;= size\;When udip=0 then no replication" access="RW" high_bound="2" low_bound="0" offset="0x4.0" size="0xc.0" />
</node>

<node name="tunnel_mc_ipv6_ext" descr="" size="0x18.0" >
	<field name="size" descr="Number of IP addresses in the record\;Range is 1..cap_max_nve_mc_entries_ipv6\;" access="RW" offset="0x0.0" size="0x0.3" />
	<field name="udip_ptr" descr="The pointers to the underlay IPv6 addresses, while i=0..(size-1).\;udip_ptr&lt;i&gt; is reserved if i&gt;=size. \;The IPv6 addresses are configured by RIPS, see \;Section 13.10.19, &quot;RIPS - Router IP version Six Register,&quot; on \;page 1956\;For Spectrum, the index is to the KVD linear, see Section A.3.1, \;&quot;KVD Central Database,&quot; on page 2251" subnode="udip_ptr" access="RW" high_bound="4" low_bound="0" offset="0x4.0" size="0x14.0" />
</node>

<node name="udip_ptr" descr="" size="0x4.0" >
	<field name="udip_ptr" descr="" offset="0x0.0" size="0x0.24" />
</node>

<node name="uint64" descr="" size="0x8.0" >
	<field name="hi" descr="" offset="0x0.0" size="0x4.0" />
	<field name="lo" descr="" offset="0x4.0" size="0x4.0" />
</node>

<node name="unicast_lag_ext" descr="" size="0x8.0" >
	<field name="vid" descr="VLAN ID to be used when uvid is set. \;Reserved when uvid = 0\;Note: supported regardless of ubridge value" access="RW" offset="0x0.0" size="0x0.12" />
	<field name="uvid" descr="Update VID. \;If set, the packet&apos;s VLAN ID is updated to vid. This can be used for \;.1D entries.\;Reserved when SwitchX/-2\;For Spectrum-2 when set_vid=0 and smpe_valid=1 then the smpe will \;modify the vid\;Note: supported regardless of ubridge value" access="RW" offset="0x0.15" size="0x0.1" />
	<field name="lag_id" descr="LAG Identifier - pointer into the LAG descriptor table, see also \;Section 6.2.11, &quot;LAG Descriptor Table,&quot; on page 807." access="RW" offset="0x4.0" size="0x0.10" />
</node>

<node name="unicast_tunnel_ext" descr="" size="0x10.0" >
	<field name="udip" descr="If gen_enc = 1:\;A pointer to the generic L2 encapsulation entry, see TNGEE\;Else If protocol is IPv4:\;The underlay destination IPv4 of the remote VTEP\;If protocol is IPv6:\;A pointer to the IPv6 address of the remote VTEP destination in \;the overlay network. See Section 13.10.19, &quot;RIPS - Router IP ver\;sion Six Register,&quot; on page 1956" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="gen_enc" descr="Generic L2 encapsulation\;Reserved when Spectrum-1" access="RW" offset="0x4.26" size="0x0.1" />
	<field name="protocol" descr="Protocol:\;0: IPv4\;1: IPv6" access="RW" enum="IPv4=0x0,IPv6=0x1" offset="0x4.27" size="0x0.1" />
	<field name="ecmp_size" descr="ecmp_size is the amount of sequential entries starting from the\;pointer to the first TNGEE (the number of ECMPs).\;Values: 1-128, 256, 512, 1024, 2048 and 4096\;Reserved when gen_enc = 0" access="RW" offset="0xC.0" size="0x0.13" />
</node>

<node name="usr_xsr_physical_layer_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in \;msec.\;[Internal] supported in USR" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear event in \;msec.\;[Internal] supported in USR" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane4_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane4_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane5_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane5_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane6_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane6_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane7_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane7_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane0)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane1)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane2)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane3)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane4_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane4_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane4)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane5_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane5_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane5)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane6_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane6_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane6)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane7_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane7_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrect\;ableBlockCounterLane7)\;[Internal] supported in USR - ZL FEC" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="link_down_events" descr="Perf.PortCounters(LinkDownedCounter)\;[Internal] supported in USR" access="RO" offset="0x88.0" size="0x4.0" />
</node>

<node name="vlan_router_interface_ext" descr="" size="0x18.0" >
	<field name="vlan_id" descr="VLAN ID\;Note: when ubridge = 1 this is the egress-router-vid. \;" access="RW" offset="0x0.0" size="0x0.12" />
	<field name="swid" descr="Switch Partition ID" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="efid" descr="Egress FID\;Used to connect the rif to a bridge \;Reserved when ubridge = 0\;Reserved when Spectrum-1\;" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="router_interface_mac_47_32" descr="Router interface MAC address.\;Note: for SwitchX/-2 all router interfaces on the same \;switch partition MUST have the same MAC address. \;In Spectrum-1 device, all MAC addresses must have the \;same 38 MSBits\;In Spectrum-2 device, all MAC addresses per mac_pro\;file_id must have the same 36 MSBits" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="mac_profile_id" descr="MAC msb profile ID\;range 0 .. cap_max_rif_mac_profile-1\;Reserved when Spectrum-1" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="router_interface_mac_31_0" descr="Router interface MAC address.\;Note: for SwitchX/-2 all router interfaces on the same \;switch partition MUST have the same MAC address. \;In Spectrum-1 device, all MAC addresses must have the \;same 38 MSBits\;In Spectrum-2 device, all MAC addresses per mac_pro\;file_id must have the same 36 MSBits" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="vrrp_id_ipv4" descr="VRRP ID for IPv4\;Reserved when SwitchX/-2. The MAC address should \;be entered to the FDB" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="vrrp_id_ipv6" descr="VRRP ID for IPv6\;Reserved when SwitchX/-2. The MAC address should \;be entered to the FDB" access="RW" offset="0x14.8" size="0x0.8" />
</node>

<node name="xgcr_ext" descr="" size="0x8.0" >
	<field name="mtm" descr="M-Table mode:\;0: Linear mapping of dip to M-Table Index (default)\;1: Hash#1 mapping of dip to M-Table Index" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="xlkbu_ext" descr="" size="0x140.0" >
	<field name="data_type" descr="Data type:\;0: KVH Single\;1: KVH Double" access="OP" offset="0x4.0" size="0x0.4" />
	<field name="value" descr="Seek for entry that matches value where mask bits are &apos;1&apos;" access="OP" high_bound="15" low_bound="0" offset="0x40.0" size="0x40.0" />
	<field name="mask" descr="Seek for entry that matches value where mask bits are &apos;1&apos;" access="OP" high_bound="15" low_bound="0" offset="0x80.0" size="0x40.0" />
	<field name="new_value" descr="For matched entries, update entry to new_value where new_val\;ue_mask bits are &apos;1&apos;" access="OP" high_bound="15" low_bound="0" offset="0xC0.0" size="0x40.0" />
	<field name="new_value_mask" descr="For matched entries, update entry to new_value where new_val\;ue_mask bits are &apos;1&apos;" access="OP" high_bound="15" low_bound="0" offset="0x100.0" size="0x40.0" />
</node>

<node name="xltq_ext" descr="" size="0x2c.0" >
	<field name="xm_device_id" descr="XM device ID\;Value of &apos;0&apos; when no known XLT device\;ID 0xCF71 for XLT\;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="xlt_cap_mask0" descr="Capability mask:\;bit0: IPv4 LPM (a.k.a. XRT)\;bit1: IPv6 LPM (a.k.a. XRT)\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="cap_xlt_entries" descr="Number of XLT entries\;Note: SW must not fill more than 80% in order to avoid overflow\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="cap_xlt_mtable" descr="XLT M-Table max size\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="cap_xlt_shspm_max_trees" descr="Number of LPM trees in the XLT\;" access="RO" offset="0x28.0" size="0x4.0" />
</node>

<node name="xmdr_ext" descr="" size="0xa0.0" >
	<field name="num_rec" descr="Number of records for Direct access to XM\;Supported: 0...4 commands (except NOP which is a filler)\;0 commands is reserved when bulk_entry = 1. \;0 commands is allowed when bulk_entry = 0 for immediate XRT-\;cache fluch." access="OP" offset="0x4.0" size="0x0.4" />
	<field name="bulk_entry" descr="Bulk_entry\;0: Last entry - immediate flush of XRT-cache\;1: Bulk entry - do not flush the XRT-cache\;" access="OP" offset="0x4.8" size="0x0.1" />
	<field name="reply_vect" descr="Reply Vector\;Bit i for command index i+1\;values per bit:\;0: failed\;1: succeeded\;e.g. if commands 1,2,4 succeeded and command 3 failed then \;binary value will be 0b1011" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="transaction" descr="Transaction.\;See Appendix B, &quot;eXtended Mezanine (XM)&quot; (page 2288)" access="WO" high_bound="31" low_bound="0" offset="0x20.0" size="0x80.0" />
</node>

<node name="xralst_ext" descr="" size="0x108.0" >
	<field name="tree_id" descr="Tree identifier numbered from 1..(cap_xlt_shspm_max_trees-1)." access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="root_bin" descr="The bin number of the root bin. \;0&lt;root_bin=&lt;(length of IP address)\;For a default-route tree configure 0xff" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="bin" descr="Holding the childs of the bin according to the stored tree&apos;s structure. \;The most significant byte is the bin&apos;s number of the left child and the \;least significant byte holds the right child. See Table 2269, &quot;bin Lay\;out,&quot; on page 2221. \;0xFF indicates that there is no child. For trees composed of less than \;4 blocks, the bins in excess are reserved.\;Note that tree_id 0 is allocated for a default-route tree, bins are 0xff" access="RW" high_bound="128" low_bound="1" offset="0x8.16" size="0x100.0" />
</node>

<node name="xralta_ext" descr="" size="0x8.0" >
	<field name="tree_id" descr="An identifier (numbered from 1..cap_xlt_shspm_max_trees-1) \;representing the tree identifier (managed by software).\;Note that tree_id 0 is allocated for a default-route tree" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="protocol" descr="Protocol:\;0: Unicast IPv4\;1: Unicast IPv6\;Reserved when op = 1 (deallocate a tree)." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="op" descr="opcode (valid for Write, must be 0 on Read)\;0: allocate a tree\;1: deallocate a tree" access="OP" offset="0x4.28" size="0x0.2" />
</node>

<node name="xraltb_ext" descr="" size="0x8.0" >
	<field name="tree_id" descr="Tree to be used for the {virtual_router, protocol}\;Tree identifier numbered from 1..(cap_xlt_shspm_max_trees-1).\;By default, all Unicast IPv4 and IPv6 are bound to tree_id 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="protocol" descr="Protocol. \;0: Unicast IPv4\;1: Unicast IPv6" access="INDEX" offset="0x4.12" size="0x0.4" />
	<field name="virtual_router" descr="Virtual Router ID\;Range is 0..cap_max_virtual_routers-1" access="INDEX" offset="0x4.16" size="0x0.16" />
</node>

<node name="xrmt_ext" descr="" size="0x14.0" >
	<field name="index" descr="Index in M-Table\;Range 0..cap_xlt_mtable-1" access="INDEX" offset="0x4.0" size="0x0.20" />
	<field name="l1_vec" descr="" access="RW" offset="0x10.0" size="0x0.8" />
	<field name="l1_val" descr="" access="RW" offset="0x10.8" size="0x0.8" />
	<field name="l0_vec" descr="" access="RW" offset="0x10.16" size="0x0.8" />
	<field name="l0_val" descr="" access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="root" size="0x440.0" descr="" >
	<field name="register_access_table_switch_ext_Nodes" offset="0x0.0" size="0x440.0" subnode="register_access_table_switch_ext_Nodes" descr="" />
</node>

<node name="register_access_table_switch_ext_Nodes" size="0x440.0" attr_is_union="1" descr="" >
	<field name="access_reg_summary_selector_ext" offset="0x0.0" size="0x440.0" subnode="access_reg_summary_selector_ext" descr="" />
</node>
</NodesDefinition>
