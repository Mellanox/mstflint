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
<info source_doc_name="Mellanox &lt;Doc Name&gt;" source_doc_version="Rev 0.64" />
<node name="adv_rdma_capabilities" descr="" size="0x800.0" >
	<field name="rdma_ctrl_icrc_rx" descr="If set, RDMA_CTRL supports icrc_rx_mode ICRC_RDMA_SERVICE" offset="0x0.13" size="0x0.1" />
	<field name="rdma_ctrl_icrc_tx" descr="If set, RDMA_CTRL supports icrc_tx_mode ICRC_RDMA_SERVICE" offset="0x0.14" size="0x0.1" />
	<field name="rcx_config_solicited_sack_en" descr="If set, solicited-SACK generation and retransmission is supported.\;" offset="0x0.15" size="0x0.1" />
	<field name="upb_retx_psn_range" descr="If set, PSN range retransmission is supported." offset="0x0.16" size="0x0.1" />
	<field name="aux_task_service_recovery_mode" descr="If set, recovery_mode is supported in AUX_TASK_SERVICE object" offset="0x0.17" size="0x0.1" />
	<field name="rcx_config_qnack" descr="If set, qnack_en and qnack_format fields are supported in RCX_CONFIG." offset="0x0.18" size="0x0.1" />
	<field name="rcx_config_qsack" descr="If set, qsack_en and qsack_format fields are supported in RCX_CONFIG." offset="0x0.19" size="0x0.1" />
	<field name="prt_config_qsack_sample_num" descr="If set, qsack_sample_num field in PRT_CONFIG object is supported" offset="0x0.20" size="0x0.1" />
	<field name="rdma_ctrl_state" descr="If set, ctrl_state field in RDMA_CTRL Object is supported" offset="0x0.21" size="0x0.1" />
	<field name="rcx_config_cc_window_based" descr="If set, setting RCX_CONFIG.cc_window_based is supported" offset="0x0.23" size="0x0.1" />
	<field name="rcx_config_sack_freq_min" descr="If set, setting RCX_CONFIG.sack_freq_min_en is supported" offset="0x0.24" size="0x0.1" />
	<field name="transport_apps_config_handover_en" descr="If set, TRANSPORT_APPS_CONFIG object supports handover flow." offset="0x0.25" size="0x0.1" />
	<field name="qp_cc_flowtag" descr="When set, the cc_flowtag is reported in the output of INIT2RTR_QP, RTR2RTS_QP, RTS2RTS_QP commands" offset="0x0.26" size="0x0.1" />
	<field name="rdma_ctrl_rc_rcx_force" descr="If set, RDMA_CTRL objects supports forcing RCX for RC QPs." offset="0x0.27" size="0x0.1" />
	<field name="ext_field_mutex_reg_c" descr="If set, field mp_path_select, mp_ctrl_response, ooo_eligible, retx_indication are MutEx with a register C pair, and may overwrite if modified." offset="0x0.28" size="0x0.1" />
	<field name="ext_field_mutex_reg_c_ext" descr="If set, field mp_path_select, mp_ctrl_response, ooo_eligible, retx_indication are MutEx with a register C pair, and may overwrite if modified." offset="0x0.29" size="0x0.1" />
	<field name="rdma_transport_manager_other_eswitch" descr="RDMA_TRANSPORT domains manager on other eswitches. When set can create and manage RDMA_TRANSPORT_RX and RDMA_TRANSPORT_TX domain tables for other vports on other eswitches." offset="0x0.30" size="0x0.1" />
	<field name="rdma_transport_manager" descr="RDMA_TRANSPORT domains manager. When set can create and manage NIC_RX_CLASS, RDMA_TRANSPORT_RX and RDMA_TRANSPORT_TX domain tables for other vports on the eswitch." offset="0x0.31" size="0x0.1" />
	<field name="prt_config_sq_retx_wqe_total_max" descr="Total number of WQEs supported for all SQ_RETX_REQUEST queues of a PRT object" offset="0x4.0" size="0x0.16" />
	<field name="transport_apps_backup_process_max" descr="Maximal number of TRANSPORT_APPS_CONFIG backup processes supported (not including 1 active process)." offset="0x4.16" size="0x0.4" />
	<field name="ext_field_mutex_reg_c_id" descr="Pair of register C MutEx with mp_path_select, mp_ctrl_response, ooo_eligible, retx_indication. Valid if ext_field_mutex_reg_c is set.\;0x0: REG_C_0_1\;0x1: REG_C_2_3\;0x2: REG_C_4_5\;0x3: REG_C_6_7\;0x4: REG_C_8_9\;0x5: REG_C_10_11\;Other values are reserved." enum="REG_C_0_1=0x0,REG_C_2_3=0x1,REG_C_4_5=0x2,REG_C_6_7=0x3,REG_C_8_9=0x4,REG_C_10_11=0x5" offset="0x4.20" size="0x0.4" />
	<field name="rcx_config_sack_entropy_source" descr="Bitmask indicating the supported values for sack_entropy_source in RCX_CONFIG. Set bit indicates the respective value is supported. See value definition in sack_entropy_source in Table  715, &quot;RCX_CONFIG Object Fields,&quot; on page  1146" offset="0x4.24" size="0x0.4" />
	<field name="rcx_config_max_num" descr="Maximal number of supported RCX_CONFIG objects" offset="0x4.28" size="0x0.3" />
	<field name="rx_ooo_psn_win_size" descr="Bitmap indicating supported values for QPC.rx_ooo_psn_win. Set bits indicate size is supported.\;bit 0: PSN_WIN_512\;bit 1: PSN_WIN_1K\;bit 2: PSN_WIN_2K\;bit 3: PSN_WIN_4K\;bit 4: PSN_WIN_8K\;bit 5: PSN_WIN_16K\;bit 6: PSN_WIN_32K\;bit 7: PSN_WIN_64K\;If no bit is set, QPC.rx_ooo_psn_win must be set to device default." enum="PSN_WIN_512=0x1,PSN_WIN_1K=0x2,PSN_WIN_2K=0x4,PSN_WIN_4K=0x8,PSN_WIN_8K=0x10,PSN_WIN_16K=0x20,PSN_WIN_32K=0x40,PSN_WIN_64K=0x80" offset="0x8.0" size="0x0.8" />
	<field name="message_based_qp_and_striding_wq" descr="Bitmap indicating striding message based QP is supported, per transport service. Set bit indicates support.\;Bit 0: TS_RC\;Bit 1: TS_UC\;Bit 2: TS_DC\;Bit 3: TS_UD\;Bit 5: TS_XRC\;Other bits are reserved" enum="TS_RC=0x1,TS_UC=0x2,TS_DC=0x4,TS_UD=0x8,TS_XRC=0x20" offset="0x8.8" size="0x0.8" />
	<field name="ps_user_context_max_log_size" descr="Maximal value supported for ps_user_context_log_size in MULTIPATH_CONFIG object" offset="0x8.16" size="0x0.8" />
	<field name="mp_max_num_queues" descr="Maximal value supported for num_queues in MULTIPATH_CONFIG object" offset="0x8.24" size="0x0.8" />
	<field name="rdma_ctrl_max_num" descr="Maximum supported RDMA_CTRL objects." offset="0xC.0" size="0x0.16" />
	<field name="max_receive_send_message_size_stride" descr="Indicates the maximal value supported for QP_CONTEXT.max_receive_send_message_size, given in strides" offset="0xC.16" size="0x0.16" />
	<field name="max_receive_send_message_size_byte" descr="Indicates the maximal value supported for QP_CONTEXT.max_receive_send_message_size, given in Bytes" offset="0x10.0" size="0x4.0" />
	<field name="prt_config_retx_mode" descr="Bitmap indicating support for PRT_CONFIG.retx_mode. Each bit offset represents the corresponding mode. Set bit indicates the mode is supported." offset="0x14.0" size="0x0.16" />
	<field name="prt_config_queue_array_max_size" descr="Maximal number of queues supported for PRT_CONFIG queue_array" offset="0x14.16" size="0x0.8" />
	<field name="rcx_config_sack_freq_min_max" descr="The maximum value that can be chosen for RCX_CONFIG.sack_freq_min" offset="0x14.24" size="0x0.8" />
	<field name="prt_config_sq_retx_max" descr="Maximal number of SQ_RETX_REQUEST queues supported for PRT_CONFIG queue_arra" offset="0x18.0" size="0x0.8" />
	<field name="prt_config_cq_to_notify_max" descr="Maximal number of CQ_TO_NOTIFY queues supported for PRT_CONFIG queue_arra" offset="0x18.8" size="0x0.8" />
	<field name="prt_config_rq_sack_retx_max" descr="Maximal number of RQ_RETX_GENERATE queues supported for PRT_CONFIG queue_arra" offset="0x18.16" size="0x0.8" />
	<field name="prt_config_rq_sack_gen_max" descr="Maximal number of RQ_SACK_GENERATE queues supported for PRT_CONFIG queue_array" offset="0x18.24" size="0x0.8" />
	<field name="cc_hint_num_max" descr="Maximal number of supported CC_HINT objects. Value 0x0 indicates 256" offset="0x1C.0" size="0x0.16" />
	<field name="cc_hint_status_size_max" descr="Maximal size supported for cc_hint_status in CC_HINT object , given in bytes. Value 0x0 indicates status is not supported." offset="0x1C.16" size="0x0.8" />
	<field name="cc_hint_size_max" descr="Maximal size supported for cc_hint_data in CC_HINT object , given in bytes. Value 0x0 indicates 256B" offset="0x1C.24" size="0x0.8" />
	<field name="rcx_config_connection_profile" descr="Bitmap indicating support for RCX_CONFIG.connection_profile. Each bit index represents the corresponding profile. Set bit indicates the profile is supported." offset="0x20.0" size="0x4.0" />
	<field name="prt_config_vhca_queue_array_size_max" descr="Maximal number of queues supported for PRT_CONFIG_VHCA queue_array" offset="0x24.0" size="0x0.12" />
	<field name="rcx_config_cc_window_based_unit" descr="Bitmap indicating supported values for RCX_CONFIG.cc_window_unit. Set bit indicates the corresponding mode is supported." offset="0x24.16" size="0x0.8" />
	<field name="upb_size_log_max" descr="Log (base 2) maximal size of the UPB in units of Bytes." offset="0x24.24" size="0x0.6" />
	<field name="ext_field_mutex_reg_c_id_ext" descr="Pair of register C MutEx with mp_path_select, mp_ctrl_response, ooo_eligible, retx_indication. \;Valid if ext_field_mutex_reg_c_ext is set.\;0x0: REG_C_0_1\;0x1: REG_C_2_3\;0x2: REG_C_4_5\;0x3: REG_C_6_7\;0x4: REG_C_8_9\;0x5: REG_C_10_11\;0x6: REG_C_12_13\;0x7: REG_C_14_15\;0x8: REG_C_16_17\;0x9: REG_C_18_19\;0xA: REG_C_20_21\;0xB: REG_C_22_23\;0xC: REG_C_24_25\;0xD: REG_C_26_27\;0xE: REG_C_28_29\;0xF: REG_C_30_31\;0x10: REG_C_32_33\;0x11: REG_C_34_35\;0x12: REG_C_36_37\;0x13: REG_C_38_39\;0x14: REG_C_40_41\;0x15: REG_C_42_43\;0x16: REG_C_44_45\;0x17: REG_C_46_47\;other values are reserved." enum="REG_C_0_1=0x0,REG_C_2_3=0x1,REG_C_4_5=0x2,REG_C_6_7=0x3,REG_C_8_9=0x4,REG_C_10_11=0x5,REG_C_12_13=0x6,REG_C_14_15=0x7,REG_C_16_17=0x8,REG_C_18_19=0x9,REG_C_20_21=0xa,REG_C_22_23=0xb,REG_C_24_25=0xc,REG_C_26_27=0xd,REG_C_28_29=0xe,REG_C_30_31=0xf,REG_C_32_33=0x10,REG_C_34_35=0x11,REG_C_36_37=0x12,REG_C_38_39=0x13,REG_C_40_41=0x14,REG_C_42_43=0x15,REG_C_44_45=0x16,REG_C_46_47=0x17" offset="0x28.24" size="0x0.8" />
	<field name="rdma_transport_rx_flow_table_properties" descr="Capabilities and properties of RDMA_TRANSPORT_RX Flow Tables" subnode="flow_table_prop_layout" offset="0x40.0" size="0x40.0" />
	<field name="rdma_transport_tx_flow_table_properties" descr="Capabilities and properties of RDMA_TRANSPORT_TX Flow Tables" subnode="flow_table_prop_layout" offset="0x80.0" size="0x40.0" />
	<field name="rdma_transport_rx_ft_field_support_2" descr="Additional match field support of RDMA_TRANSPORT_RX Flow Tables" subnode="flow_table_fields_supported_2" offset="0xC0.0" size="0x10.0" />
	<field name="rdma_transport_tx_ft_field_support_2" descr="Additional match field support of RDMA_TRANSPORT_TX Flow Tables" subnode="flow_table_fields_supported_2" offset="0xD0.0" size="0x10.0" />
	<field name="rdma_transport_rx_ft_field_bitmask_support_2" descr="Additional partial field match support of RDMA_TRANSPORT_RX Flow Tables" subnode="flow_table_fields_supported_2" offset="0xE0.0" size="0x10.0" />
	<field name="rdma_transport_tx_ft_field_bitmask_support_2" descr="Additional partial field match support of RDMA_TRANSPORT_TX Flow Tables" subnode="flow_table_fields_supported_2" offset="0xF0.0" size="0x10.0" />
	<field name="rdma_transport_rx_header_modify" descr="Header modify capabilities of RDMA_TRANSPORT_RX Flow Tables" subnode="header_modify_cap_properties" offset="0x100.0" size="0x80.0" />
	<field name="rdma_transport_tx_header_modify" descr="Header modify capabilities of RDMA_TRANSPORT_TX Flow Tables" subnode="header_modify_cap_properties" offset="0x180.0" size="0x80.0" />
	<field name="nic_rx_class_flow_table_properties" descr="Capabilities and properties of NIC_RX_CLASS Flow Tables" subnode="flow_table_prop_layout" offset="0x200.0" size="0x40.0" />
	<field name="nic_rx_class_ft_field_support_2" descr="Additional partial field match support of NIC_RX_CLASS Flow Tables" subnode="flow_table_fields_supported_2" offset="0x240.0" size="0x10.0" />
	<field name="nic_rx_class_ft_field_bitmask_support_2" descr="Additional partial field match support of NIC_RX_CLASS Flow Tables" subnode="flow_table_fields_supported_2" offset="0x250.0" size="0x10.0" />
	<field name="nic_rx_class_header_modify" descr="Header modify capabilities of NIC_RX_CLASS Flow Tables" subnode="header_modify_cap_properties" offset="0x260.0" size="0x80.0" />
</node>

<node name="adv_virtualization_capabilities" descr="" size="0x100.0" >
	<field name="pg_track_log_max_addr_space" descr="log (base 2) of the maximal Address Space size for a PAGE_TRACK object, given in bytes" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="pg_track_log_min_addr_space" descr="log (base 2) of the minimal Address Space size for a PAGE_TRACK object, given in bytes" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="pg_track_max_num_range" descr="Maximum number of tracked address ranges for a single PAGE_TRACK object" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="pg_track_log_max_num" descr="log (base 2) of the maximum number of supported PAGE_TRACK objects" access="RW" offset="0x0.24" size="0x0.5" />
	<field name="pg_track_log_max_page_size" descr="log (base 2) of the maximal page size for a PAGE_TRACK object, given in bytes" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="pg_track_log_min_page_size" descr="log (base 2) of the minimal page size for a PAGE_TRACK object, given in bytes" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="pg_track_log_max_msg_size" descr="log (base 2) of the maximal message size for a PAGE_TRACK object, given in bytes" access="RW" offset="0x4.16" size="0x0.5" />
	<field name="pg_track_log_min_msg_size" descr="log (base 2) of the minimal message size for a PAGE_TRACK object, given in bytes" access="RW" offset="0x4.24" size="0x0.5" />
</node>

<node name="atomic_caps" descr="" size="0x100.0" >
	<field name="supported_atomic_req_8B_endianness_mode_1" descr="Atomic requester 8B atomics mode 0x1 support." access="RW" offset="0x8.25" size="0x0.1" />
	<field name="atomic_req_8b_endianness_mode" descr="Active 8 Byte Atomic operations (standard and extended) endianness format in requester scatter.\;Note: 1-4 and 16-256 Byte Atomic operations are always in BE.\;\;0x0: big - requester endianness format is always Big endian for standard 8B and extended 8B atomics.\;0x1: according_to_host_endianness - requester endianness format is according to HOST_ENDIANNESS register for standard 8B and extended 8B atomics. Supported only when atomic_req_8B_endianess_mode_1 ==1.\;Note that in responder, the scatter endianness is always according to HOST_ENDIANNESS register." access="RW" enum="big=0x0,according_to_host_endianness=0x1" offset="0x8.30" size="0x0.2" />
	<field name="atomic_operations" descr="Bit mask for atomic operations supported, bit equal to 1 means operations is supported.\;bit 0: Atomic_Compare_and_Swap_supported\;bit 1: Atomic_Fetch_and_Add_supported\;bit 2: Atomic_Masked_Compare_and_Swap_supported - extended atomic operation\;bit 3: Atomic_Masked_Fetch_and_Add_supported - extended atomic operation\;bit 4: remote_micro_applications_supported" access="RW" enum="Atomic_Compare_and_Swap_supported=0x1,Atomic_Fetch_and_Add_supported=0x2,Atomic_Masked_Compare_and_Swap_supported=0x4,Atomic_Masked_Fetch_and_Add_supported=0x8,remote_micro_applications_supported=0x10" offset="0x10.0" size="0x0.16" />
	<field name="atomic_size_qp" descr="Atomic sizes supported for all qps transport services except of DC.\;bit 0: byte_1\;bit 1: bytes_2\;bit 2: bytes_4\;bit 3: bytes_8\;bit 4: bytes_16\;bit 5: bytes_32\;bit 6: bytes_64\;bit 7: bytes_128\;bit 8: bytes_256" access="RW" enum="byte_1=0x1,bytes_2=0x2,bytes_4=0x4,bytes_8=0x8,bytes_16=0x10,bytes_32=0x20,bytes_64=0x40,bytes_128=0x80,bytes_256=0x100" offset="0x14.0" size="0x0.16" />
	<field name="atomic_size_dc" descr="Atomic sizes supported for DC qps.\;bit 0: byte_1\;bit 1: bytes_2\;bit 2: bytes_4\;bit 3: bytes_8\;bit 4: bytes_16\;bit 5: bytes_32\;bit 6: bytes_64\;bit 7: bytes_128\;bit 8: bytes_256" access="RW" enum="byte_1=0x1,bytes_2=0x2,bytes_4=0x4,bytes_8=0x8,bytes_16=0x10,bytes_32=0x20,bytes_64=0x40,bytes_128=0x80,bytes_256=0x100" offset="0x18.0" size="0x0.16" />
	<field name="load_remote_micro_app_4byte" descr="Bitmask indicates which load remote micro operationsof 4 byte operands size are supported.\;Bits x for operation code ==x. \;Section  , &quot;,&quot; on page  1876" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="load_remote_micro_app_8byte" descr="Bitmask indicates which load remote micro operations of 8 byte operands size are supported.\;Bits x for operation code ==x. \;Section  , &quot;,&quot; on page  1876" access="RW" offset="0x24.0" size="0x4.0" />
	<field name="store_remote_micro_app_4byte" descr="Bitmask indicates which store remote micro operations of 4 byte operands size are supported. \;Bits x for operation code ==x. \;Section  , &quot;,&quot; on page  1876" access="RW" offset="0x28.0" size="0x4.0" />
	<field name="store_remote_micro_app_8byte" descr="Bitmask indicates which store remote micro operations of 8 byte operands size are supported.\;Bits x for operation code ==x. \;Section  , &quot;,&quot; on page  1876" access="RW" offset="0x2C.0" size="0x4.0" />
	<field name="swap_pci_atomic" descr="Bitmask indicates for which sizes of SWAP PCI Atomic are supported.\;Bit 0: Bytes_4\;Bit 1: Bytes_8\;Bit 2: Bytes_16" access="RW" enum="Bytes_4=0x1,Bytes_8=0x2,Bytes_16=0x4" offset="0x50.0" size="0x0.16" />
	<field name="fetch_add_pci_atomic" descr="Bitmask indicates for which sizes of FETCH_ADD PCI Atomic are supported.\;Bit 0: Bytes_4\;Bit 1: Bytes_8\;Bit 2: Bytes_16" access="RW" enum="Bytes_4=0x1,Bytes_8=0x2,Bytes_16=0x4" offset="0x50.16" size="0x0.16" />
	<field name="compare_swap_pci_atomic" descr="Bitmask indicates for which sizes of COMPARE_SWAP PCI Atomic are supported.\;Bit 0: Bytes_4\;Bit 1: Bytes_8\;Bit 2: Bytes_16" access="RW" enum="Bytes_4=0x1,Bytes_8=0x2,Bytes_16=0x4" offset="0x54.16" size="0x0.16" />
</node>

<node name="cc_prov_capabilities" descr="" size="0x100.0" >
	<field name="cc_service_cap" descr="Capabilities reported by the CC provider to RDMA CC-aware application. The contents of this field is outside the scope of this document" high_bound="63" low_bound="0" offset="0x0.0" size="0x100.0" />
</node>

<node name="cmd_hca_cap" descr="" size="0x100.0" >
	<field name="vhca_resource_manager" descr="vHCA resource manager.\;If set, vhca resource manager is capable to control capabilities of other vHCAs under its responsibility." offset="0x0.0" size="0x0.1" />
	<field name="log_sha_mmo_max_size" descr="Log(Base 2) of the maximum SHA MMO operation size in Bytes.\;Valid only when HCA_CAP.sha_mmo==1\;0 means no limit on size." offset="0x0.8" size="0x0.5" />
	<field name="lag_queue_affinity_active_port" descr="If set, Lag with Queue Affinity port selection mode may use active_port for port remapping instead of tx_remap_affinity" offset="0x0.13" size="0x0.1" />
	<field name="emulated_dev_mkey_crossing_access_disabled" descr="If unset, creating crossing vCHA mkey to emulated device&apos;s crossed vHCA mkeys is supported. See &quot;Data Path Flow&quot; on page 1890" offset="0x0.14" size="0x0.1" />
	<field name="shared_object_to_user_object_allowed" descr="If set, Shared object that is created with UID==0xfff can point to any UID" offset="0x0.15" size="0x0.1" />
	<field name="flow_counter_access_aso_opc_mod" descr="Value of OPC_MOD field in WQE Ctrl Segment for ACESS_ASO WQE that accesses Flow Counter" offset="0x0.16" size="0x0.8" />
	<field name="abs_native_port_num" descr="when set the native_port_num may exceed the number of ports reported by HCA_CAP.num_lag_ports." offset="0x0.24" size="0x0.1" />
	<field name="page_request_disable" descr="If set, Page Request events are not issued by the device" offset="0x0.25" size="0x0.1" />
	<field name="eq_dbr" descr="If set, device supports EQ DoorBell Record ()" offset="0x0.26" size="0x0.1" />
	<field name="lightweight_eq" descr="If set, device supports lightweight EQs (Section  8.21.9, &quot;Lightweight EQ,&quot; on page  867)" offset="0x0.27" size="0x0.1" />
	<field name="query_match_sample_info" descr="When set, QUERY_MATCH_SAMPLE_INFO command is supported." offset="0x0.28" size="0x0.1" />
	<field name="flow_counter_access_aso" descr="When set, ACESS_ASO WQE can also access Flow Counter" offset="0x0.29" size="0x0.1" />
	<field name="alloc_flow_counter_pd" descr="When set, PD may be associated withy Flow Counter (bulk) in ALLOC_FLOW_COUNTER." offset="0x0.30" size="0x0.1" />
	<field name="access_other_hca_roce" descr="If set, vhca group manager is capable to control &quot;roce&quot; field in HCA_CAP for another vHCA under its responsibility.\;See Table  32.3.6, &quot;QUERY_OTHER_HCA_CAP - Query Other HCA Capabilities,&quot; on page  4178." offset="0x0.31" size="0x0.1" />
	<field name="vhca_id" descr="Virtual HCA identifier." offset="0x4.0" size="0x0.16" />
	<field name="transpose_max_element_size" descr="The maximum size of element in a matrix for transpose operation in granularity of Bytes." offset="0x4.16" size="0x0.8" />
	<field name="event_on_vhca_state_invalid" descr="Used by vport group manager to indicate if to report event when vhca_state==invalid in VHCA_STATE Context for all vHCAs.\;Table  4580, &quot;VHCA_STATE_CONTEXT Structure Layout,&quot; on page  4636" offset="0x4.24" size="0x0.1" />
	<field name="event_on_vhca_state_allocated" descr="Used by vport group manager to indicate if to report event when vhca_state==allocated in VHCA_STATE Context for all vHCAs.\;Table  4580, &quot;VHCA_STATE_CONTEXT Structure Layout,&quot; on page  4636" offset="0x4.25" size="0x0.1" />
	<field name="event_on_vhca_state_active" descr="Used by vport group manager to indicate if to report event when vhca_state==active in VHCA_STATE Context for all vHCAs.\;Table  4580, &quot;VHCA_STATE_CONTEXT Structure Layout,&quot; on page  4636" offset="0x4.26" size="0x0.1" />
	<field name="event_on_vhca_state_in_use" descr="Used by vport group manager to indicate if to report event when vhca_state==in_use in VHCA_STATE Context for all vHCAs.\;Table  4580, &quot;VHCA_STATE_CONTEXT Structure Layout,&quot; on page  4636" offset="0x4.27" size="0x0.1" />
	<field name="event_on_vhca_state_teardown_request" descr="Used by vport group manager to indicate if to report event when vhca_state==teardown_request in VHCA_STATE Context for all vHCAs.\;Table  4580, &quot;VHCA_STATE_CONTEXT Structure Layout,&quot; on page  4636" offset="0x4.28" size="0x0.1" />
	<field name="dtor" descr="If set, DTOR Register is supported.\;See Table  1922, &quot;Default Timeout Layout,&quot; on page  2289" offset="0x4.29" size="0x0.1" />
	<field name="create_lag_when_not_master_up" descr="If set, then it&apos;s not necessary for LAG Master to do CREATE_LAG only of other function are down.\;" offset="0x4.30" size="0x0.1" />
	<field name="hca_cap_2" descr="If set, HCA_CAP 2 is supported." offset="0x4.31" size="0x0.1" />
	<field name="transpose_max_size" descr="The maximum aligned size of a matrix for transpose operations given in Bytes. Matrix aligned size is calculated by rounding up the number of rows and columns to the nearest power of 2 and assuming 256B elements." offset="0x8.0" size="0x0.16" />
	<field name="transpose_max_rows" descr="The maximum number of rows of a matrix for transpose operation." offset="0x8.16" size="0x0.8" />
	<field name="transpose_max_cols" descr="The maximum number of columns of a matrix for transpose operation." offset="0x8.24" size="0x0.8" />
	<field name="log_decompress_mmo_max_size" descr="Log(Base 2) of the maximum DECOMPRESS MMO operation size in Bytes.\;0 means no limit on size." offset="0xC.0" size="0x0.5" />
	<field name="decompress_lz4_checksum_v2" descr="If set, decompression MMO supports the lz4 algorithm with checksum sub type" offset="0xC.5" size="0x0.1" />
	<field name="decompress_lz4_no_checksum_v2" descr="If set, decompression MMO supports the lz4 algorithm without checksum sub type" offset="0xC.6" size="0x0.1" />
	<field name="decompress_lz4_data_only_v2" descr="If set, decompression MMO supports the lz4 algorithm with data_only sub type" offset="0xC.7" size="0x0.1" />
	<field name="log_compress_mmo_max_size" descr="Log(Base 2) of the maximum CPOMPRESS MMO operation size in Bytes.\;Valid only when HCA_CAP.compress==1\;0 means no limit on size." offset="0xC.8" size="0x0.5" />
	<field name="decompress_snappy_v2" descr="If set, decompression MMO supports the snappy algorithm" offset="0xC.13" size="0x0.1" />
	<field name="ibl2_tx_vl15" descr="If set, sending packets on VL15 is supported for IBL2 QPs." offset="0xC.14" size="0x0.1" />
	<field name="relaxed_ordering_write_pci_enabled" descr="\;\;If set, MKeys support setting order_write_after_write to RELAXED_ORDER\;Valid if mkc_order_write_after_write_ro is 0x0" offset="0xC.15" size="0x0.1" />
	<field name="log_dma_mmo_max_size" descr="Log(Base 2) of the maximum DMA MMO operation size in Bytes.\;Valid only when HCA_CAP.dma_mmo==1\;0 means no limit on size." offset="0xC.16" size="0x0.5" />
	<field name="init2init_qp_drain_sigerr" descr="If set, drain_sigerr in QP context can be modified in INIT2INIT command." offset="0xC.21" size="0x0.1" />
	<field name="ibl2_qp" descr="If set QPs with IBL2 Service Type are supported." offset="0xC.22" size="0x0.1" />
	<field name="ibl2_delay_drop" descr="If set, disabling packet drop due to lack of receive WQEs is supported for IBL2 QPs." offset="0xC.23" size="0x0.1" />
	<field name="log_regexp_mmo_max_size" descr="Log(Base 2) of the maximum scatter/gather size of Regexp operation in Bytes.\;0 means Regexp MMO is not supported." offset="0xC.24" size="0x0.5" />
	<field name="qp_data_in_order" descr="If set, data_in_order field in QP Context is supported." offset="0xC.29" size="0x0.1" />
	<field name="sw_steering_icm_large_scale_steering" descr="If set SW steering should create a Flow Table for its matcher anchors, triggering large scale steering policy in FW for this table." offset="0xC.30" size="0x0.1" />
	<field name="resources_on_virtio_fs_emulation_manager" descr="If set, allocating recources on Virtio FS emulation manager (instead of emulated device by a tunnel) is supported.\;This is done by setting VIRTIO_FS_DEVICE_MULATION_OBJECT.resources_on_emulation_manager=1." offset="0xC.31" size="0x0.1" />
	<field name="log_max_qp" descr="Log (base 2) of the maximum number of QPs supported" offset="0x10.0" size="0x0.5" />
	<field name="dynamic_qp_allocation" descr="If set, indicates that the device supports dynamic allocation of resources for QPs.\;" offset="0x10.5" size="0x0.1" />
	<field name="wqe_index_ignore_cap" descr="When set, wqe_index in the WQE Control element is ignored by the HCA. \;Notes:\;This field is NOT ignored in BlueFlame.\;It is recommended to set the right wqe_index in case wq_signature is enabled." offset="0x10.6" size="0x0.1" />
	<field name="prio_tag_required" descr="If set, the system requires to always have prio tag on the network. SW should set the required flow table rules to ensure that. Enabled by NV_SW_OFFLOAD_CONFIG.prio_tag_required_en.\;" offset="0x10.7" size="0x0.1" />
	<field name="pcie_hanged" descr="If set, pci_hanged report is supported.\;See Section  30.7.1, &quot;PCIe Hanged Event,&quot; on page  2149" offset="0x10.8" size="0x0.1" />
	<field name="nvmeotcp" descr="If set, NVMEoTCP offload is supported.\;For detailed capabilities see Table  1380, &quot;NVMEoTCP Capabilities Layout,&quot; on page  1794" offset="0x10.9" size="0x0.1" />
	<field name="comm_channel_cross_esw" descr="If set, CHANNEL_SERVICE.allowed_vhca_id is permitted to refer to VHCA from a different eswitch on the same host. Otherwise, the CHANNEL_SERVICE allowed_vhca_id must be from it&quot;s own eswtch only.\;" offset="0x10.10" size="0x0.1" />
	<field name="comm_channel_dc" descr="If set, Channel_Service and Channel_Connection objects support transport_type ==DC." offset="0x10.11" size="0x0.1" />
	<field name="isolate_vl_tc_new" descr="When set, the device supports isolating force loopback QPs (QP.fl bit set) on a different VL/TC.\;" offset="0x10.12" size="0x0.1" />
	<field name="rc_qp_create_on_init" descr="If set, CREATE_QP for RC QP allows the state transition directly to INIT.\;The required parameters for this transition are taken from the relevant tables of CREATE_QP and RST2INIT_QP.\;This will be executed by CREATE_QP command op_mode==CREATE_ON_INIT." offset="0x10.13" size="0x0.1" />
	<field name="rc_qp_init2rts" descr="If set, INIT2RTR_QP for RC QP allows the state transition directly to RTS without the need to move to RTR.\;The required and optional parameters for this transition are taken from the relevant tables of INIT2RTR_QP and RTR2RTS_QP.\;This will be executed by INIT2RTR command op_mode==INIT2RTS." offset="0x10.14" size="0x0.1" />
	<field name="event_cap" descr="If set, Event Capabilities structure is supported.\;See Table  3551, &quot;Event Capabilities Layout,&quot; on page  4133" offset="0x10.15" size="0x0.1" />
	<field name="log_max_qp_sz" descr="Log (base 2) of the maximum number of WQEs allowed on the RQ or the SQ of a QP." offset="0x10.16" size="0x0.8" />
	<field name="log_max_srq_sz" descr="Log (base 2) of the maximum number of WQEs allowed on the SRQ/XRC_SRQ." offset="0x10.24" size="0x0.8" />
	<field name="scatter_fcs_w_decap_disable" descr="When set, driver should avoid sending decapsulated packets to RQs with scatter_fcs field set." offset="0x14.4" size="0x0.1" />
	<field name="shampo_old" descr="\;If set, SHAMPO operations are supported.\;To get detailed SHAMPO capabilities, software should query SHAMPO cap Section  32.3.4.22, &quot;SHAMPO Capabilities,&quot; on page  4153." offset="0x14.5" size="0x0.1" />
	<field name="go_back_n" descr="If set, retry_mode==go_back_n in QP and DCT is supported" offset="0x14.6" size="0x0.1" />
	<field name="selective_repeat" descr="If set, retry_mode==selective_repeat in QP and DCT is supported" offset="0x14.7" size="0x0.1" />
	<field name="ts_cqe_to_dest_cqn" descr="If set, ts_cqe_to_dest_cqn in SQ Context is supported." offset="0x14.13" size="0x0.1" />
	<field name="uplink_follow" descr="If set, admin_state in MODIFY_VPORT_STATE can be set to FOLLOW for uplink vport.\;" offset="0x14.14" size="0x0.1" />
	<field name="psp_old" descr="If set, PSP is supported." offset="0x14.15" size="0x0.1" />
	<field name="log_max_srq" descr="Log (base 2) of the maximum number of SRQs/XRC_SRQs supported" offset="0x14.16" size="0x0.5" />
	<field name="isolate_vl_tc" descr="When set, the device supports isolating force loopback QPs (QP.fl bit set) on a different VL/TC.\;[Internal] This field is deprecated and replaced with isolate_vl_tc_new." offset="0x14.21" size="0x0.1" />
	<field name="reg_c_preserve" descr="When set, registers of type C will preserve their value even through the operations detailed in Section 8.18.2.9, &quot;MetaData Registers&quot;, on page 724" offset="0x14.22" size="0x0.1" />
	<field name="allow_pause_tx" descr="If set, then sending pause frames is allowed (EtherType 0x8808 according to 802.3x).\;" offset="0x14.23" size="0x0.1" />
	<field name="regexp_num_of_engines" descr="Number of REGEXP engines supported by the device.\;Valid only when regexp==1." offset="0x14.24" size="0x0.4" />
	<field name="ece" descr="If set, ECE Enhanced Connection Establishment (ECE) in QP commands is supported." offset="0x14.28" size="0x0.1" />
	<field name="regexp_alloc_onbehalf_umem" descr="If set, ECPF should allocate regexp umem used by external host and only when external host has capability of regexp_params.\;" offset="0x14.29" size="0x0.1" />
	<field name="log_max_cq" descr="Log (base 2) of the maximum number of CQs supported" offset="0x18.0" size="0x0.5" />
	<field name="virtio_blk_device_emulation_manager" descr="If set, this vHCA is allowed to manage VIRTIO BLK device emulation.\;detailed capabilities reported in VIRTIO Device emulation Capabilities (Table  1632, &quot;VIRTIO_Emulation Capabilities Layout,&quot; on page  2066)" offset="0x18.5" size="0x0.1" />
	<field name="virtio_net_device_emulation_manager" descr="If set, this vHCA is allowed to manage VIRTIO NET device emulation.\;Detailed capabilities reported in VIRTIO Device emulation Capabilities (Table  1632, &quot;VIRTIO_Emulation Capabilities Layout,&quot; on page  2066)" offset="0x18.6" size="0x0.1" />
	<field name="upt_device_emulation_manager" descr="If set, this vHCA is allowed to manage UPT device emulation.\;Detailed capabilities reported in UPT Device emulation Capabilities (Table  1630, &quot;UPT Device Emulation Capabilities Layout,&quot; on page  2063)" offset="0x18.7" size="0x0.1" />
	<field name="max_num_of_fixed_buffers_per_mkey" descr="Maximum number of fixed buffers per mkey is defined by\;16K*2^max_num_of_fixed_buffers_per_mkey" offset="0x18.8" size="0x0.5" />
	<field name="access_register_user" descr="If set, ACCESS_REGISTER_USER command is supported." offset="0x18.13" size="0x0.1" />
	<field name="log_max_cq_sz" descr="Log (base 2) of the maximum CQEs allowed in a CQ" offset="0x18.16" size="0x0.8" />
	<field name="max_sgl_for_optimized_performance" descr="Maximum scatter gather list for optimized perfromance.\;0 means invalid (no recommended value)" offset="0x18.24" size="0x0.8" />
	<field name="log_max_eq" descr="Log (base 2) of the maximum number of EQs.\;Should be used only in case HCA_CAP.max_num_eqs==0." offset="0x1C.0" size="0x0.4" />
	<field name="fast_teardown" descr="If set, fast teardown is supported.\;Section  6.3.1, &quot;Fast Teardown,&quot; on page  523" offset="0x1C.4" size="0x0.1" />
	<field name="resources_on_nvme_emulation_manager" descr="If set, allocating recources on NVMe emulation manager (instead of emulated device by a tunnel) is supported.\;This is done by setting NVME_DEVICE_MULATION_OBJECT.resources_on_emulation_manager=1." offset="0x1C.5" size="0x0.1" />
	<field name="dpp" descr="If set, Direct Packet Placement is supported.\;To get detailed DPP capabilities, software should query DPP cap Section  32.3.4.17, &quot;DPP Capabilities,&quot; on page  4131." offset="0x1C.6" size="0x0.1" />
	<field name="dump_fill_mkey" descr="If set, dump_fill_mkey is reported in QUERY_SPECIAL_CONTEXT command. See Section  32.7.5, &quot;QUERY_SPECIAL_CONTEXTS - Query Special Context Numbers,&quot; on page  4263." offset="0x1C.7" size="0x0.1" />
	<field name="repeated_mkey" descr="If set, repeated_mkey is reported in QUERY_SPECIAL_CONTEXT command. See Section  32.7.5, &quot;QUERY_SPECIAL_CONTEXTS - Query Special Context Numbers,&quot; on page  4263." offset="0x1C.8" size="0x0.1" />
	<field name="terminate_scatter_list_mkey" descr="If set, terminate_scatter_list_mkey is reported in QUERY_SPECIAL_CONTEXT command. See Section  32.7.5, &quot;QUERY_SPECIAL_CONTEXTS - Query Special Context Numbers,&quot; on page  4263." offset="0x1C.9" size="0x0.1" />
	<field name="nvme_device_emulation_manager" descr="If set, this vHCA is allowed to manage NVME device emulation.\;detailed capabilities reported in NVME Device emulation Capabilities (Table  1628, &quot;NVME Device Emulation Capabilities Layout,&quot; on page  2058)" offset="0x1C.10" size="0x0.1" />
	<field name="hotplug_manager" descr="If set, this vHCA is allowed to manage (hot plug/unplug) emulated devices. Detailed capabilities are reported in Hotplug Capabilities (Table  1638, &quot;Hotplug Capabilities Layout,&quot; on page  2084)." offset="0x1C.11" size="0x0.1" />
	<field name="m_vhca_mk" descr="If set, Multi vHCA Mkey is supported.\;See Section 14.9, &quot;Multi vHCA Mkey&quot;, on page 1634" offset="0x1C.12" size="0x0.1" />
	<field name="m_pci_port" descr="If set, Multi PCI Port is supported.\;See Section 14.10, &quot;Multi PCI Port&quot;, on page 1635" offset="0x1C.13" size="0x0.1" />
	<field name="as_notify" descr="If set, AS_NOTIFY is supported.\;" offset="0x1C.14" size="0x0.1" />
	<field name="tunneled_atomic" descr="If set, tunneled_atomic in Mkey Context is supported.\;See Table  796, &quot;MKey Context Fields,&quot; on page  1225" offset="0x1C.15" size="0x0.1" />
	<field name="log_max_mkey" descr="Log (base 2) of the maximum number of data MKey entries (the number of Regions/Windows)" offset="0x1C.16" size="0x0.6" />
	<field name="relaxed_ordering_read_pci_enabled" descr="If set, MKeys support setting pci_relaxed_ordered_read.\;Valid if pci_relaxed_ordered_read is 0x0" offset="0x1C.22" size="0x0.1" />
	<field name="mkc_order_write_after_write_ro" descr="If set, MKeys support setting order_write_after_write to RELAXED_ORDER" offset="0x1C.23" size="0x0.1" />
	<field name="log_max_eq_sz" descr="Log (base 2) of the maximum EQEs allowed in an EQ" offset="0x1C.24" size="0x0.8" />
	<field name="log_max_klm_list_size" descr="Log (base 2) of the maximum indirect KLM entries list (in MKey)" offset="0x20.0" size="0x0.6" />
	<field name="null_mkey" descr="If set, NULL_MKEY is reported in QUERY_SPECIAL_CONTEXT command, see Section  32.7.5, &quot;QUERY_SPECIAL_CONTEXTS - Query Special Context Numbers,&quot; on page  4263." offset="0x20.6" size="0x0.1" />
	<field name="umr_extended_translation_offset" descr="If set, UMR Control segment translation_offset_42:16 is supported. See Table  117, &quot;UMR_CTRL Segment Layout,&quot; on page  612." offset="0x20.7" size="0x0.1" />
	<field name="log_max_bsf_list_size" descr="Log (base 2) of the maximum bsf entries list (in MKey)" offset="0x20.8" size="0x0.6" />
	<field name="hard_coded_1" descr="\;Replaced by fast_teardown due to FW bug.\;FW must report 1 in this internal field\;" offset="0x20.14" size="0x0.1" />
	<field name="force_teardown" descr="If set, force teardown of HCA is supported using TEARDOWN_HCA command. See  Section  32.3.14, &quot;TEARDOWN_HCA - Tear-down HCA,&quot; on page  4193." offset="0x20.15" size="0x0.1" />
	<field name="log_max_mrw_sz" descr="Log (base 2) of the maximum size of a Memory Region/Window" offset="0x20.16" size="0x0.7" />
	<field name="fixed_buffer_size" descr="If set, Mkey access_mode of type fixed buffer size is supported.Table  796, &quot;MKey Context Fields,&quot; on page  1225" offset="0x20.23" size="0x0.1" />
	<field name="max_indirection" descr="Maximum level of Mkey indirection supported" offset="0x20.24" size="0x0.8" />
	<field name="log_max_ra_res_dc" descr="Log (base 2) of the maximum number of outstanding RDMA read/Atomic per DC QP as a responder" offset="0x24.0" size="0x0.6" />
	<field name="vnic_env_cq_overrun" descr="If set, cq_overrun counter is supported in QUERY_VNIC_ENV. See Section 32.35.2,  on page 4659\;" offset="0x24.6" size="0x0.1" />
	<field name="ooo_sl_mask" descr="If set, ooo_sl_mask in hca vport context is supported.\;See Table  102, &quot;HCA_Vport Context Layout,&quot; on page  582" offset="0x24.7" size="0x0.1" />
	<field name="log_max_static_sq_wq" descr="Log(base 2) of the maximum supported SQs with static WQ." offset="0x24.8" size="0x0.5" />
	<field name="vnic_env_eth_wqe_too_small" descr="When set, the device supports the vNIC counter eth_wqe_too_small in QUERY_VNIC_ENV. See Section 32.35.2,  on page 4659" offset="0x24.13" size="0x0.1" />
	<field name="eth_wqe_too_small_mode" descr="When set, the device supports modifying the handling of WQE too small through eth_wqe_too_small_mode field in Nic_vport Context.\;" offset="0x24.14" size="0x0.1" />
	<field name="vhca_trust_level_reg" descr="If set, VHCA_TRUST_LEVEL register is supported.\;See Section 31.2.26, &quot;VHCA_TRUST_LEVEL Register&quot;, on page 2281." offset="0x24.15" size="0x0.1" />
	<field name="log_max_ra_req_dc" descr="Log (base 2) of the maximum number of outstanding RDMA read/Atomic per DC QP as a requester" offset="0x24.16" size="0x0.6" />
	<field name="resources_on_virtio_blk_emulation_manager" descr="If set, allocating recources on VIRTIO_BLK emulation manager (instead of emulated device by a tunnel) is supported.\;This is done by setting VIRTIO_BLK_DEVICE_MULATION_OBJECT.resources_on_emulation_manager=1." offset="0x24.22" size="0x0.1" />
	<field name="resources_on_virtio_net_emulation_manager" descr="If set, allocating recources on VIRTIO_NET emulation manager (instead of emulated device by a tunnel) is supported.\;This is done by setting VIRTIO_NET_DEVICE_MULATION_OBJECT.resources_on_emulation_manager=1." offset="0x24.23" size="0x0.1" />
	<field name="log_max_static_sq_wq_size" descr="Log(base 2) of maximum static wq supported in granularity of 64B" offset="0x24.24" size="0x0.5" />
	<field name="qpc_extension" descr="If set, QP Context extension is supported in QP commands.\;" offset="0x24.29" size="0x0.1" />
	<field name="ats_ro_dependence" descr="If set, ATS and RO must be set identically for an MKey. when cleared, ATS and RO may be set independently. note that for peer-to-peer communications ATS and RO should be configured identically to avoid PCI requests and completions going through different paths." offset="0x24.30" size="0x0.1" />
	<field name="non_wire_sq" descr="If set, SQ context of type non wire is supported" offset="0x24.31" size="0x0.1" />
	<field name="log_max_ra_res_qp" descr="Log (base 2) of the maximum number of outstanding RDMA read/Atomic per QP as a responder" offset="0x28.0" size="0x0.6" />
	<field name="decompress_mmo_sq_v1" descr="If set, DEcompress MMO in SQ is supported. \;Maximum size of decompress is reported in HCA_CAP.log_decompress_mmo_max_size.\;" offset="0x28.6" size="0x0.1" />
	<field name="compress_mmo_sq" descr="If set, Compress MMO in SQ is supported.\;Maximum size of compress is reported in HCA_CAP.log_compress_mmo_max_size.\;" offset="0x28.7" size="0x0.1" />
	<field name="compress_min_block_size" descr="Minimum value of block size in COMPRESS MMO control. See Section  23.10.2, &quot;COMPRESS MMO,&quot; on page  1803" offset="0x28.8" size="0x0.4" />
	<field name="dma_mmo_sq" descr="If set, DMA MMO wqe in SQ is supported. \;Maximum size of DMA_MMO is reported in HCA_CAP.log_dma_mmo_max_size.\;" offset="0x28.12" size="0x0.1" />
	<field name="rts2rts_lag_tx_port_affinity" descr="If set, modify lag_tx_port_affinity in QP context in RTS2RTS is supported" offset="0x28.13" size="0x0.1" />
	<field name="rts2rts_udp_sport" descr="If set, modify udp_sport in QP context in RTS2RTS is supported.\;Note that this cap depends also on HCA_CAP.sw_r_roce_src_udp_port." offset="0x28.14" size="0x0.1" />
	<field name="rtr2rts_qp_counters_set_id" descr="If set, modify counters_set_id in QP context in RTR2RTS is supported." offset="0x28.15" size="0x0.1" />
	<field name="log_max_ra_req_qp" descr="Log (base 2) of the maximum number of outstanding RDMA read/Atomic per QP as a requester" offset="0x28.16" size="0x0.6" />
	<field name="roce_accl" descr="If set, ROCE_ACCL register will be supported. See Section  31.2.10, &quot;ROCE_ACCL - ROCE Accelerator,&quot; on page  2231." offset="0x28.22" size="0x0.1" />
	<field name="sig_crc32c" descr="If set, CRC32c signature type is supported." offset="0x28.23" size="0x0.1" />
	<field name="sig_crc64_xp10" descr="If set, CRC64_xp10 signature type is supported." offset="0x28.24" size="0x0.1" />
	<field name="release_all_pages" descr="If set, the device releases all pages immediately for another function.\;SW can release all pages directly when getting release_all_pages ==1 in Table  380, &quot;Pages Request Event Layout,&quot; on page  861.\;Device reports 1 in max capability and 0 in current.\;SW that supports the flow should set 1 in the current capability." offset="0x28.26" size="0x0.1" />
	<field name="cc_roce_ecn_rp_burst_decouple" descr="When set RoCE ECN RP CC supports decoupling the transmission bursts of multiple CC QPs transmitting to the same destination IP. Valid only for Mellanox 3rd generation NICs compatibility mode." offset="0x28.27" size="0x0.1" />
	<field name="cc_roce_ecn_rp_dynamic_g" descr="When set RoCE ECN RP CC supports dynamic updates of dce_tcp_g according to the average number of CNPs received per QP per second. Valid only for Mellanox 3rd generation" offset="0x28.28" size="0x0.1" />
	<field name="cc_roce_ecn_rp_dynamic_ai" descr="When set RoCE ECN RP CC supports dynamic updates of rpg_ai_rate according to time elapsed since last CNP was received. Valid only for Mellanox 3rd generation NICs" offset="0x28.29" size="0x0.1" />
	<field name="cc_roce_ecn_rp_dynamic_rtt" descr="When set RoCE ECN RP CC supports dynamic updates of dce_tcp_rtt according to the number of CC flows. Valid only for Mellanox 3rd generation NICs compatibility mode." offset="0x28.30" size="0x0.1" />
	<field name="cc_roce_ecn_rp_classify_mode" descr="When set RoCE ECN RP CC supports classifying flows for Congestion Control by either QP number or by destination IP." offset="0x28.31" size="0x0.1" />
	<field name="gid_table_size" descr="GID table size. If gid_table_size_ro==1, the write is ignored.\;0x0: gid_entries_8\;0x1: gid_entries_16\;0x2: gid_entries_32\;0x3: gid_entries_64\;0x4: gid_entries_128" enum="gid_entries_8=0x0,gid_entries_16=0x1,gid_entries_32=0x2,gid_entries_64=0x3,gid_entries_128=0x4" offset="0x2C.0" size="0x0.16" />
	<field name="qcam_reg" descr="If set, QCAM register is supported. See Table  1320, &quot;QCAM - QoS Capabilities Mask Register Layout,&quot; on page  1719." offset="0x2C.16" size="0x0.1" />
	<field name="cwcam_reg" descr="If set, CWCAM register is supported. See Section  31.8.13, &quot;CWCAM - Congestion WRED Capabilities Mask Register,&quot; on page  3500" offset="0x2C.17" size="0x0.1" />
	<field name="sbcam_reg" descr="If set, SBCAM register is supported. See Section  31.9.5, &quot;SBCAM - Shared Buffer Capabilities Mask Register,&quot; on page  3521" offset="0x2C.18" size="0x0.1" />
	<field name="vnic_env_int_rq_oob" descr="If set, internal_rq_out_of_buffer counter is supported in QUERY_VNIC_ENV. See Section 32.35.2,  on page 4659\;" offset="0x2C.19" size="0x0.1" />
	<field name="gen3_cc_negotiation" descr="If set, gen3_cc_ negotiation_en in QUERY_CONG_STATUS and MODIFY_CONG_STATUS commands is supported." offset="0x2C.20" size="0x0.1" />
	<field name="rts2rts_qp_dscp" descr="If set, modify dscp and f_dscp in QP context in RTS2RTS is supported." offset="0x2C.21" size="0x0.1" />
	<field name="rts2rts_qp_counters_set_id" descr="If set, modify counters_set_id in QP context in RTS2RTS is supported." offset="0x2C.22" size="0x0.1" />
	<field name="rnr_nak_q_counters" descr="If set, resp_rnr_nak and req_rnr_retries_exceeded Q counters are supported. See Section  32.36.3, &quot;QUERY_Q_COUNTER - Query Q Counter,&quot; on page  4677." offset="0x2C.23" size="0x0.1" />
	<field name="rts2rts_qp_rmp" descr="If set, modify xrq/rmp in QP context in RTS2RTS is supported.\;The modify of this field is best effort, and command will fail (BAD_RESOURCE_STATE) and no modifications done in the following cases:\;QP is in the middle of receiving a message or the original RMP is XRQ. During this command execution, incoming packets to this QP may be dropped, and no RNR_NACK will be sent for them." offset="0x2C.24" size="0x0.1" />
	<field name="pkey_table_size_ro" descr="If set, device will ignore the written value to pkey_table_size." offset="0x2C.25" size="0x0.1" />
	<field name="gid_table_size_ro" descr="If set, device will ignore the written value to gid_table_size." offset="0x2C.26" size="0x0.1" />
	<field name="cache_line_128byte" descr="If set, 128 byte cache line size is supported.\;0 means only 64 byte cache line is supported." offset="0x2C.27" size="0x0.1" />
	<field name="start_pad" descr="Start Padding in RX messages is supported.\;Section  3.3.14, &quot;Start of Packet Padding (RX),&quot; on page  383." offset="0x2C.28" size="0x0.1" />
	<field name="cc_modify_allowed" descr="Modify Congestion Control parameters and statistics allowed.\;Section  32.42, &quot;Congestion Control Commands,&quot; on page  4723" offset="0x2C.29" size="0x0.1" />
	<field name="cc_query_allowed" descr="Query Congestion Control parameters and statistics allowed.\;Section  32.42, &quot;Congestion Control Commands,&quot; on page  4723" offset="0x2C.30" size="0x0.1" />
	<field name="end_pad" descr="End Padding in RX messages is supported.\;Section  3.3.15, &quot;End of Packet Padding (RX),&quot; on page  384." offset="0x2C.31" size="0x0.1" />
	<field name="pkey_table_size" descr="PKey table size. If pkey_table_size_ro==1, the write is ignored.\;0x0: entries_128\;0x1: entries_256\;0x2: entries_512\;0x3: entries_1k\;0x4: entries_2k\;0x5: entries_4k" enum="entries_128=0x0,entries_256=0x1,entries_512=0x2,entries_1k=0x3,entries_2k=0x4,entries_4k=0x5" offset="0x30.0" size="0x0.16" />
	<field name="max_qp_cnt" descr="Maximum number of QP counters sets." offset="0x30.16" size="0x0.10" />
	<field name="rq_delay_drop" descr="If set, disabling packet drop due to lack of receive WQEs is supported." offset="0x30.26" size="0x0.1" />
	<field name="modify_rq_counters_set_id" descr="If set, modify counters_set_id in RQ context is supported.Table  235, &quot;CREATE_RQ and MODIFY_RQ Bitmask,&quot; on page  696" offset="0x30.27" size="0x0.1" />
	<field name="debug" descr="If set, debug capabilities are supported.\;Software should query debug capabilities for detailed capabilities. Section  32.3.4.11, &quot;Debug Capabilities,&quot; on page  4119." offset="0x30.28" size="0x0.1" />
	<field name="retransmission_q_counters" descr="If set, retransmission Q counters is supported. Section  32.36, &quot;Q Counters Commands,&quot; on page  4674." offset="0x30.29" size="0x0.1" />
	<field name="vport_counters" descr="If set, Vport counters are supported.Section  32.35, &quot;Vport Monitoring Commands,&quot; on page  4653." offset="0x30.30" size="0x0.1" />
	<field name="out_of_seq_cnt" descr="If set, out of sequence counter in Q counters is supported.Section  32.36, &quot;Q Counters Commands,&quot; on page  4674." offset="0x30.31" size="0x0.1" />
	<field name="num_ports" descr="Number of network ports." offset="0x34.0" size="0x0.8" />
	<field name="port_type" descr="Indicates port type\;0x0: IB\;0x1: Ethernet" enum="IB=0x0,Ethernet=0x1" offset="0x34.8" size="0x0.2" />
	<field name="beacon_led" descr="If set, Beacon LED is supported. See Section  31.14.3, &quot;MLCR - Management LED Control Register,&quot; on page  3574." offset="0x34.10" size="0x0.1" />
	<field name="disable_link_up_by_init_hca" descr="If set, device will not bring link up on INIT_HCA command.\;" offset="0x34.11" size="0x0.1" />
	<field name="pulse_gen_control" descr="When set, the device supports driver control over pulse generation through a GPIO pin." offset="0x34.12" size="0x0.1" />
	<field name="port_checks" descr="If set, disabling port checks using PCMR register is supported." offset="0x34.13" size="0x0.1" />
	<field name="enhanced_retransmission_q_counters" descr="If set, enhanced retransmission Q counters is supported. Section  32.36, &quot;Q Counters Commands,&quot; on page  4674." offset="0x34.14" size="0x0.1" />
	<field name="port_module_event" descr="If set, Port Module Event is supported." offset="0x34.15" size="0x0.1" />
	<field name="local_ca_ack_delay" descr="The Local CA ACK Delay. This is the value recommended to be returned in Query HCA verb.\;The delay value in microseconds is computed using 4.096us * 2^(local_ca_ack_delay)." offset="0x34.16" size="0x0.5" />
	<field name="pcam_reg" descr="If set, PCAM register is supported. Table  1959, &quot;PCAM - Ports Capabilities Mask Register Layout,&quot; on page  2326" offset="0x34.21" size="0x0.1" />
	<field name="mcam_reg" descr="If set, MCAM register is supported. See Table  3294, &quot;MCAM - Management Capabilities Mask Register Layout,&quot; on page  3792." offset="0x34.22" size="0x0.1" />
	<field name="device_memory" descr="If set, device internal memory capabilities is supported.\;See Table  3539, &quot;Device Memory Capabilities Layout,&quot; on page  4121." offset="0x34.23" size="0x0.1" />
	<field name="eswitch_manager" descr="If set, e-switch flow table mechanism is supported.\;To get detailed flow table capabilities, software should query Flow Table NIC Cap.Table  3517, &quot;Flow Table NIC Capabilities Layout,&quot; on page  4076." offset="0x34.24" size="0x0.1" />
	<field name="nic_flow_table" descr="If set, NIC flow table mechanism is supported.\;To get detailed flow table capabilities, software should query NIC flow table cap.Table  3517, &quot;Flow Table NIC Capabilities Layout,&quot; on page  4076." offset="0x34.25" size="0x0.1" />
	<field name="ets" descr="When set, ETS is supported. See Section  22, &quot;Quality of Service,&quot; on page  1690." offset="0x34.26" size="0x0.1" />
	<field name="vnic_env_queue_counters" descr="When set QUERY_VNIC_ENV supports current_error_queues, total_error_queues and send_queue_priori-ty_update_flow counters. See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\;report" offset="0x34.27" size="0x0.1" />
	<field name="eth_virt" descr="If set, Ethernet virtualization interface is supported.See Section  14.1, &quot;Ethernet Virtualization,&quot; on page  1605" offset="0x34.28" size="0x0.1" />
	<field name="ib_virt" descr="If set, InfiniBand virtualization interface is supported.\;See Section  8.8, &quot;HCA_Vport Context - HCA Virtual Port Context,&quot; on page  581" offset="0x34.29" size="0x0.1" />
	<field name="vhca_group_manager" descr="Virtual HCA group manager. Responsible for enabling other vHCAs in its group." offset="0x34.30" size="0x0.1" />
	<field name="vport_group_manager" descr="Virtual port group manager. Responsible for enabling other Vports." offset="0x34.31" size="0x0.1" />
	<field name="wol_p" descr="If set, wake on phy activity is supported." offset="0x38.0" size="0x0.1" />
	<field name="wol_u" descr="If set, wake on unicast packet is supported." offset="0x38.1" size="0x0.1" />
	<field name="wol_m" descr="If set, wake on multicast packet is supported." offset="0x38.2" size="0x0.1" />
	<field name="wol_b" descr="If set, wake on broadcast packet is supported." offset="0x38.3" size="0x0.1" />
	<field name="wol_a" descr="If set, wake on ARP is supported." offset="0x38.4" size="0x0.1" />
	<field name="wol_g" descr="If set, wake on magic packet is supported." offset="0x38.5" size="0x0.1" />
	<field name="wol_s" descr="If set, wake on secured magic packet is supported." offset="0x38.6" size="0x0.1" />
	<field name="ib_port_sniffer" descr="If set, IB port sniffer is supported.\;See Section 32.39, &quot;IB Port sniffer&quot;, on page 4710" offset="0x38.7" size="0x0.1" />
	<field name="rol_g" descr="If set, reset on magic packet is supported." offset="0x38.8" size="0x0.1" />
	<field name="rol_s" descr="If set, reset on secured magic packet is supported." offset="0x38.9" size="0x0.1" />
	<field name="fpga" descr="If set, FPGA is supported by the device. See TBD" offset="0x38.10" size="0x0.1" />
	<field name="afu_owner" descr="If set, AFU commands are supported.\;See Section 32.22, &quot;AFU Command - Acceleration Functions Units commands&quot;, on page 4519" offset="0x38.11" size="0x0.1" />
	<field name="multi_prio_sq" descr="If set, the device supports an indication from the SW that SQ is used for transmission of packets with multiple priorities. See Table 95, &quot;NIC_Vport Context Layout,&quot; on page 572." offset="0x38.12" size="0x0.1" />
	<field name="general_notification_event" descr="If set, General Notification event is supported.\;See Section  8.21.8.8.8, &quot;General Notification Event,&quot; on page  852" offset="0x38.13" size="0x0.1" />
	<field name="dcbx" descr="If set, DCBX is supported.\;SW should query DCBX_PARAM register for more details.\;See Section 31.2.7, &quot;DCBX_PARAM Register&quot;, on page 2226." offset="0x38.14" size="0x0.1" />
	<field name="temp_warn_event" descr="If set, Temperature Warning Event is supported.\;Section  8.21.8.8.7, &quot;Temp Warning Event,&quot; on page  851." offset="0x38.15" size="0x0.1" />
	<field name="max_tc" descr="Number of Link Layer Traffic Classes supported.\;The device supports TCs in range 0..max_tc-1.\;Value 0 indicates that 8 TCs are supported." offset="0x38.16" size="0x0.4" />
	<field name="traffic_fast_control" descr="If set, INIT_SEGMENT.traffic_state is supported." offset="0x38.20" size="0x0.1" />
	<field name="dp_ordering_ooo_rw_rc" descr="When set, the QP ordering semantic OOO_RW is supported for RC service type. See Table  13.2.5, &quot;QP Ordering Semantics,&quot; on page  1594" offset="0x38.21" size="0x0.1" />
	<field name="dp_ordering_ooo_rw_dc" descr="When set, the QP ordering semantic OOO_RW is supported for DC service type. See Table  13.2.5, &quot;QP Ordering Semantics,&quot; on page  1594" offset="0x38.22" size="0x0.1" />
	<field name="dp_ordering_ooo_rw_xrc" descr="When set, the QP ordering semantic OOO_RW is supported for XRC service type. See Table  13.2.5, &quot;QP Ordering Semantics,&quot; on page  1594" offset="0x38.23" size="0x0.1" />
	<field name="log_max_msg" descr="Log (base 2) of the maximum message size in bytes supported by the device" offset="0x38.24" size="0x0.5" />
	<field name="pps_modify" descr="If set, modifying PPS parameters using MTPPS register is supported. See Section  13.3.1.1, &quot;Auxiliary Pulse-Per-Second (PPS) Signals,&quot; on page  1600." offset="0x38.29" size="0x0.1" />
	<field name="pps" descr="If set, query PPS parameters, using MTPPS register and PPS event mechanism is supported. See Section  13.3.1.1, &quot;Auxiliary Pulse-Per-Second (PPS) Signals,&quot; on page  1600." offset="0x38.30" size="0x0.1" />
	<field name="cqe_version" descr="CQE version.\;CQE format includes different format and fields depending on CQE version.Table  275, &quot;64B CQE With Data Layout,&quot; on page  788." offset="0x3C.0" size="0x0.4" />
	<field name="wqe_based_flow_table_update_cap" descr="When set, the additional capabilities are supported, See Table  3553, &quot;WQE_BASED_FLOW_TABLE Capabilities Layout,&quot; on page  4135" offset="0x3C.4" size="0x0.1" />
	<field name="stat_rate_200" descr="When this bit is set, rates of Gbps_56, Gbps_25, Gbps_100, Gbps_200, and Gbps_50 are supported in Address Path Structure Fields.stat_rate,  UD address vector field.static_rate" offset="0x3C.5" size="0x0.1" />
	<field name="flow_group_type_hash_split" descr="When set, the device supports Flow Groups of type HASH_SPLIT, splitting traffic into buckets according to packet header hash calculation\;" offset="0x3C.6" size="0x0.1" />
	<field name="init2_lag_tx_port_affinity" descr="If set, lag_tx_port_affinity in QP context can be modified in INIT2INIT and INIT2RTR commands." offset="0x3C.7" size="0x0.1" />
	<field name="log_max_extended_rnr_retry" descr="Log(base 2) of the maximum value supported in QP.extended_rnr_retry.\;If set to 0, extended_rnr_retry_valid,extended_rnr_retry and extended_cur_rnr_retry are not supported.\;See Table  83, &quot;QP Context Structure Layout,&quot; on page  540" offset="0x3C.8" size="0x0.5" />
	<field name="init2rtr_drain_sigerr" descr="If set, drain_sigerr in QP context can be modified in INIT2RTR command." offset="0x3C.13" size="0x0.1" />
	<field name="pci_sync_for_fw_update_event" descr="If set, General notification event supports pci_sync_for_fw_update sub-event. See &quot;Driver Flow During Reset&quot; on page 356\;" offset="0x3C.14" size="0x0.1" />
	<field name="sig_block_4048" descr="If set, Block size of 4048 Bytes is supported for signature." offset="0x3C.15" size="0x0.1" />
	<field name="stat_rate_support" descr="Each bit corresponds to a value of Static Rate parameter in Address Vectors. For example, if bit 0 is set, then value of 0 (Full BW) is supported as Static Rate value." offset="0x3C.16" size="0x0.16" />
	<field name="extended_retry_count" descr="If set, extended_retry_count_valid, extended_retry_count and extended_cur_retry_count in QP context are supported.\;See Table 83, &quot;QP Context Structure Layout,&quot; on page 540" offset="0x40.0" size="0x0.1" />
	<field name="atomic" descr="If set, atomic operations are supported.\;To get detailed atomic capabilities, software should query atomic cap Section  32.3.4.4, &quot;Atomic Capabilities,&quot; on page  4064." offset="0x40.1" size="0x0.1" />
	<field name="roce" descr="If set, RoCE operations are supported.\;To get detailed RoCE capabilities, software should query RoCE cap. Section  32.3.4.5, &quot;RoCE Capabilities,&quot; on page  4067." offset="0x40.2" size="0x0.1" />
	<field name="eth_net_offloads" descr="If set, Ethernet networking offloads are supported.\;To get detailed Ethernet capabilities, software should query Ethernet cap. Section  32.3.4.6, &quot;Networking Offload Capabilities,&quot; on page  4069." offset="0x40.3" size="0x0.1" />
	<field name="qos" descr="If set, quality of service capabilities are supported.\;To get detailed quality of service capabilities, software should query quality of service cap. Section  32.3.4.10, &quot;Quality of Service Capabilities,&quot; on page  4114." offset="0x40.4" size="0x0.1" />
	<field name="dct" descr="Dynamically Connected transport mode is supported." offset="0x40.5" size="0x0.1" />
	<field name="rf" descr="If set, the HCA support remote fence for RDMA read." offset="0x40.6" size="0x0.1" />
	<field name="sho" descr="Signature handover is supported." offset="0x40.8" size="0x0.1" />
	<field name="bsf_in_create_mkey" descr="If set, SW can set a list of BSFs in CREATE_MKEY command." offset="0x40.9" size="0x0.1" />
	<field name="sctr_data_cqe" descr="Scatter Data to CQE is supported." offset="0x40.10" size="0x0.1" />
	<field name="wq_signature" descr="WQE signature check on WQ - (for SQ, RQ and QP)." offset="0x40.11" size="0x0.1" />
	<field name="e_psv" descr="Extended psv support. When enabled, the device will collect signature errors extended data and will report them in QUERY_PSV." offset="0x40.12" size="0x0.1" />
	<field name="sigerr_cqe" descr="Signature error CQE supported." offset="0x40.13" size="0x0.1" />
	<field name="cmdif_checksum" descr="0x0: disabled - command interface signature is neither checked for input nor for output\;0x1: initial_state - command interface signature is not checked on input, but is generated by device for output\;0x3: enabled - command interface signature is both checked for input and generated for output. [EMC] when &quot;e&quot; bit is set, setting state to 0x1 will behave the same as 0x3 (enabled)" enum="disabled=0x0,initial_state=0x1,enabled=0x3" offset="0x40.14" size="0x0.2" />
	<field name="drain_sigerr" descr="If set, QP moves to SQ draining upon signature hand-over error.Section  23.11.14.2, &quot;Signature Handover Completion Report,&quot; on page  1833." offset="0x40.16" size="0x0.1" />
	<field name="dc_cnak_trace" descr="If set, dc cnak trace is supported.\;Section  16.2.4, &quot;DC CNAK Trace,&quot; on page  1656" offset="0x40.17" size="0x0.1" />
	<field name="dc_connect_qp" descr="If set, DC connect QP is supported." offset="0x40.18" size="0x0.1" />
	<field name="dc_req_sctr_data_cqe" descr="If set, scatter data to CQE for requester in DC is supported." offset="0x40.19" size="0x0.1" />
	<field name="umr_fence" descr="The required fence type for UMR WQEs.\;0x0: STRONG - a strong fence is required. \;0x1: SMALL - a small fence is required. \;0x2: NONE - No fence is required." enum="STRONG=0x0,SMALL=0x1,NONE=0x2" offset="0x40.20" size="0x0.2" />
	<field name="umr_indirect_mkey_disabled" descr="When set, Indirect MKeys cannot be set to be UMR-able" offset="0x40.22" size="0x0.1" />
	<field name="umr_modify_atomic_disabled" descr="When set, UMR may not modify atomic privileges (a) of an MKey" offset="0x40.23" size="0x0.1" />
	<field name="umr_modify_entity_size_disabled" descr="When set, UMR may not modify page/buffer size (log_entity_size) of an MKey" offset="0x40.24" size="0x0.1" />
	<field name="repeated_block_disabled" descr="When set, repeated/strided block MKey is not supported." offset="0x40.25" size="0x0.1" />
	<field name="ib_link_list_striding_wq" descr="If set, IB striding WQ for link list WQ is supported." offset="0x40.26" size="0x0.1" />
	<field name="ipoib_basic_offloads" descr="If set, IPoIB basic offloads are supported.\;To get detailed IPoIB basic capabilities, SW should query IPoIB basic capabilities using QUERY_HCA_CAP.op_mod = IPoIB basic offload capabilities." offset="0x40.27" size="0x0.1" />
	<field name="ipoib_enhanced_offloads" descr="If set, IPoIB enhanced offloads is supported.\;To get detailed IPoIB Enhanced capabilities, SW should query IPoIB Enhanced capabilities using QUERY_HCA_CAP.op_mod = IPoIB enhanced offload capabilities." offset="0x40.28" size="0x0.1" />
	<field name="eth_striding_wq" descr="If set, Ethernet striding wq is supported." offset="0x40.30" size="0x0.1" />
	<field name="compact_address_vector" descr="WQE with compact Address Vector supported.Table  216, &quot;UD Address Vector Layout,&quot; on page  664." offset="0x40.31" size="0x0.1" />
	<field name="rc" descr="If set, RC Transport is supported" offset="0x44.0" size="0x0.1" />
	<field name="uc" descr="If set, UC Transport is supported" offset="0x44.1" size="0x0.1" />
	<field name="ud" descr="If set, UD Transport is supported" offset="0x44.2" size="0x0.1" />
	<field name="xrc" descr="If set, XRC transport is supported" offset="0x44.3" size="0x0.1" />
	<field name="dc_v2" descr="If set, DC transport service version 2 is supported." offset="0x44.4" size="0x0.1" />
	<field name="initiator_src_dct" descr="If set, initiator_src_dct in QP Context is supported.\;Table  83, &quot;QP Context Structure Layout,&quot; on page  540" offset="0x44.5" size="0x0.1" />
	<field name="rts2rts_primary_sl" descr="If set, RTS2RTS command supports setting sl in primary path.\;Table  3906, &quot;RTS2RTS_QP Optional Parameters Mask,&quot; on page  4321." offset="0x44.6" size="0x0.1" />
	<field name="set_deth_sqpn" descr="If set, SW can control the DETH source QP number on UD QPs with the QP.deth_sqpn. Table  83, &quot;QP Context Structure Layout,&quot; on page  540." offset="0x44.7" size="0x0.1" />
	<field name="pkv" descr="If set, PKey Violation Counter is supported" offset="0x44.8" size="0x0.1" />
	<field name="qkv" descr="If set, QKey Violation Counter is supported" offset="0x44.9" size="0x0.1" />
	<field name="initiator_src_dct_in_cqe" descr="If set, CQ supports initiator_src_dct.\;" offset="0x44.10" size="0x0.1" />
	<field name="ipoib_enhanced_pkey_change" descr="When set, PKey change does not require recreating the underlay IPoIB QPs." offset="0x44.11" size="0x0.1" />
	<field name="ib_cyclic_striding_wq" descr="If set, striding CYCLIC WQ is supported for IB traffic where QPs are attached to an XRQ with a WQ with wq_type ==0x2 or 0x3." offset="0x44.12" size="0x0.1" />
	<field name="qp_e2e_packet_based" descr="if set, packet based e2e credit mode is supported in req_e2e_credit_mode in QP." offset="0x44.13" size="0x0.1" />
	<field name="imaicl" descr="Internal mkey access is considered local.\;If set, internal mkey access (access to an mkey via a pointer of an indirect mkey) will always be considered a local access, thus remote access flags will not be checked on the internally accessed mkey. \;Note: A given mkey may be accessed internally by one packet and externally by another packet. Section  21.2.1, &quot;User-Mode Memory Registration (UMR),&quot; on page  1679." offset="0x44.14" size="0x0.1" />
	<field name="umr_ptr_rlkey" descr="If set, the reserved lkey is allowed to be used in a UMR WQE data segment of type UMR pointer as described in Table  121, &quot;UMR_PTR Segment Layout,&quot; on page  615." offset="0x44.15" size="0x0.1" />
	<field name="vector_calc" descr="If set, vector calc operations is supported.\;To get detailed vector calc capabilities, software should query vector calc cap. Section  32.3.4.9, &quot;Vector Calc Capabilities,&quot; on page  4112." offset="0x44.16" size="0x0.1" />
	<field name="apm" descr="If set, Automatic Path Migration is supported" offset="0x44.17" size="0x0.1" />
	<field name="atm" descr="This field replaced with a new field called &apos;atomic&apos;" offset="0x44.18" size="0x0.1" />
	<field name="cd" descr="If set, core direct is supported" offset="0x44.19" size="0x0.1" />
	<field name="cq_period_start_from_cqe" descr="If set, cq_period_mode =1 is supported.(i.e. cq_period timer restarts upon completion generation).\;Table  306, &quot;Completion Queue Context Layout,&quot; on page  817." offset="0x44.20" size="0x0.1" />
	<field name="scqe_break_moderation" descr="Completion Event Moderation breakage by solicited CQE feature is supported." offset="0x44.21" size="0x0.1" />
	<field name="exponential_backoff" descr="When set, exponentially increasing timeout value is supported. Section  13.2.4, &quot;Exponential Backoff Timer,&quot; on page  1594." offset="0x44.22" size="0x0.1" />
	<field name="block_lb_mc" descr="Block loopback multicast supported. Can be enabled per QP using QP.block_lb_mc_en." offset="0x44.23" size="0x0.1" />
	<field name="pg" descr="If set, on-demand paging is supported. For more details, Section  9.3, &quot;On-demand Paging,&quot; on page  1215." offset="0x44.24" size="0x0.1" />
	<field name="cq_eq_remap" descr="If set, cq.eqn can be modified by MODIFY_CQ. i.e. CQ to EQ remapping is supported.\;Section  32.10.4, &quot;MODIFY_CQ - Modify CQ Parameters,&quot; on page  4290." offset="0x44.25" size="0x0.1" />
	<field name="ib_striding_wq_cq_first_indication" descr="If set, CQ.byte_cnt[29:29] is used to indicate to start of message (Only for IB).\;[Internal] FW should report this only for IB." offset="0x44.26" size="0x0.1" />
	<field name="cq_invalidate" descr="If set, setting CQ in invalid state using MODIFY_CQ command is supported. Section  32.10.4, &quot;MODIFY_CQ - Modify CQ Parameters,&quot; on page  4290" offset="0x44.27" size="0x0.1" />
	<field name="cq_period_mode_modify" descr="If set, CQ.cq_period_mode can be modified by MODIFY_CQ.Section  32.10.4, &quot;MODIFY_CQ - Modify CQ Parameters,&quot; on page  4290" offset="0x44.28" size="0x0.1" />
	<field name="cq_moderation" descr="If set, CQ moderation is enabled by MODIFY_CQ Command. Table  3856, &quot;MODIFY_CQ Input Structure Layout,&quot; on page  4290" offset="0x44.29" size="0x0.1" />
	<field name="cq_resize" descr="If set, resizing CQ is enabled. Section  8.20.8, &quot;Resizing a CQ,&quot; on page  794" offset="0x44.30" size="0x0.1" />
	<field name="cq_oi" descr="If set, cq.oi can be modified by MODIFY_CQ command. Section  32.10.4, &quot;MODIFY_CQ - Modify CQ Parameters,&quot; on page  4290." offset="0x44.31" size="0x0.1" />
	<field name="log_pg_sz" descr="Log (base 2) of the minimum system page size supported.\;For proper operation it must be less than or equal to the minimum page size of the hosting platform (CPU)." offset="0x48.0" size="0x0.8" />
	<field name="log_max_dc_cnak_qps" descr="Log (base 2) of the maximum number of supported DC_CNAK QPs.\;The device distributes the connects randomly between the opened QPs." offset="0x48.8" size="0x0.5" />
	<field name="umem_uid_0" descr="If set, UMEM can be used instead of PASs also when UID=0.\;" offset="0x48.13" size="0x0.1" />
	<field name="nic_cap_reg" descr="If set, NIC_CAP_REG register is supported." offset="0x48.14" size="0x0.1" />
	<field name="port_selection_cap" descr="If set, Port Selection Capabilities report is supported" offset="0x48.15" size="0x0.1" />
	<field name="uar_sz" descr="UAR Area Size = 1MB * 2^uar_sz" offset="0x48.16" size="0x0.6" />
	<field name="regexp_params" descr="If set, QUERY_REGEXP_PARAMS and SET_REGEXP_PARAMS are supported." offset="0x48.22" size="0x0.1" />
	<field name="fl_rc_qp_when_roce_disabled" descr="If set, RC RoCE QP creation with force loopback==1 is allowed when RoCE is disabled in nic vport context (roce_en=0) or RoCE is disabled/not supported by HCA_CAP (roce=0). In such case, source and destination network addresses should be reserved." offset="0x48.23" size="0x0.1" />
	<field name="log_max_local_dma_size" descr="The maximum Local DMA size is:\;(2^log_max_local_dma_size) -1 Byte." offset="0x48.24" size="0x0.5" />
	<field name="local_dma" descr="If set, Local DMA WQE is supported.\;The maximum Local DMA size is reported in log_max_local_dma_size." offset="0x48.29" size="0x0.1" />
	<field name="dci_no_rdma_wr_optimized_performance" descr="If set, it is recommended to use DC transport QP&quot;s without RDMA Write operations for best performance, by setting QPC.rdma_wr_disabled. Supported only when HCA_CAP.dc_v2==1" offset="0x48.30" size="0x0.1" />
	<field name="uar_4k" descr="If set, UARs are of size 4KB.\;In this mode, ALLOC_UAR allocates a group of UARs of size HCA_CAP.num_of_uars_per_page.\;" offset="0x48.31" size="0x0.1" />
	<field name="num_lag_ports" descr="The number of lag ports supported. \;If greater than 1, LAG features are supported and indicates the number of lag ports supported. May likely be greater than HCA_CAP.num_ports. See Section  14, &quot;Virtualization,&quot; on page  1605." offset="0x4C.0" size="0x0.4" />
	<field name="lag_master" descr="If set, SW is allowed to create and manage LAG. Valid only when HCA_CAP.num_lag_ports&gt;1. See Section  14, &quot;Virtualization,&quot; on page  1605." offset="0x4C.4" size="0x0.1" />
	<field name="lag_native_fdb_selection" descr="If set, NATIVE_FDB mode (mode 1) will be supported in CREATE_LAG command." offset="0x4C.6" size="0x0.1" />
	<field name="lag_tx_port_affinity" descr="If set, lag_tx_port_affinity in QP and TIS is supported. even if LAG isn&apos;t created by CREATE_LAG.\;Note that this can be used only if num_lag_ports&gt;1." offset="0x4C.7" size="0x0.1" />
	<field name="lag_dct" descr="If set, DCTs are supported while LAG is active (CREATE_LAG)" offset="0x4C.8" size="0x0.1" />
	<field name="atomic_rate_pa" descr="If this bit is set, the internal lock mechanism is based on physical address bits. When the bit is cleared, the lock is based on virtual address bits" offset="0x4C.10" size="0x0.1" />
	<field name="qp_handling_when_roce_disabled" descr="When set, QP&quot;s and DCT handling, such as creation, modifications and destorying, is allowed, even if RoCE is disabled. \;When RoCE is disabled, device blocks RoCE traffic on egress path (RDMA_TX) and on ingress path (RDMA_RX), preventing regular RoCE data traffic.\;On such case source_addr_index, rgid_or_rip, rmac, flow_label, and hop_limit are reserved." offset="0x4C.11" size="0x0.1" />
	<field name="qp_error_syndrome" descr="If set, QP context reports error_syndrome in QUERY_QP." offset="0x4C.12" size="0x0.1" />
	<field name="qp_8k_mtu" descr="If set, using of 8K MTU QP is supported" offset="0x4C.13" size="0x0.1" />
	<field name="ec_offload_engine_disabled" descr="If set, then embedding cpu engine is disabled.\;Valid only for devices that supports embedded CPU (SOC)\;" offset="0x4C.14" size="0x0.1" />
	<field name="disciplined_fr_counter" descr="When set, the free-running counter is affected by adjustments made to the real-time clock." offset="0x4C.15" size="0x0.1" />
	<field name="log_bf_reg_size" descr="Log (base 2) of BlueFlame max register size in bytes." offset="0x4C.16" size="0x0.5" />
	<field name="suspend_qp_rc" descr="If set, Suspend/Resume is supported for RC QPs. See TBD" offset="0x4C.21" size="0x0.1" />
	<field name="suspend_qp_ud" descr="If set, Suspend/Resume is supported for UD QPs. See TBD" offset="0x4C.22" size="0x0.1" />
	<field name="suspend_qp_uc" descr="If set, Suspend/Resume is supported for UC QPs. See TBD" offset="0x4C.23" size="0x0.1" />
	<field name="virtio_fs_device_emulation_manager" descr="If set, this vHCA is allowed to manage VIRTIO FS device emulation.\;detailed capabilities reported in VIRTIO Device emulation Capabilities (Table  1632, &quot;VIRTIO_Emulation Capabilities Layout,&quot; on page  2066)" offset="0x4C.24" size="0x0.1" />
	<field name="mkey_by_name" descr="If set, SW can choose Mkey number in CREATE_MKEY command.\;." offset="0x4C.25" size="0x0.1" />
	<field name="qp_by_name" descr="If set, SW can choose QP number in CREATE_QP command." offset="0x4C.26" size="0x0.1" />
	<field name="max_qp_retry_freq" descr="If set, QP maximum retry frequency limit is supported.\;See configuration of max_qp_retry_limit and max_qp_retry_period in Nic Vport Context." offset="0x4C.27" size="0x0.1" />
	<field name="query_driver_version" descr="If set, the device supports querying the driver version that was set by SET_DRIVER_VERSION, using QUERY_DRIVER_VERSION.\;See Section 32.3.20, &quot;QUERY_DRIVER_VERSION&quot;, on page 4202" offset="0x4C.28" size="0x0.1" />
	<field name="pad_tx_eth_packet" descr="If set, device automatically pads Ethernet packets shorter than 64 bytes to 64 bytes." offset="0x4C.29" size="0x0.1" />
	<field name="driver_version" descr="If set, SET_DRIVER_VERSION command is supported and should be used by the driver which performs start-up. Section  32.3.19, &quot;SET_DRIVER_VERSION,&quot; on page  4200." offset="0x4C.30" size="0x0.1" />
	<field name="bf" descr="If set to &apos;1&apos; then BlueFlame may be used" offset="0x4C.31" size="0x0.1" />
	<field name="max_wqe_sz_sq" descr="Max descriptor size in bytes for the SQ. SQ WQEs must not be bigger than indicated here. RDMA-read total scatter gather list size cannot exceed 512 bytes" offset="0x50.0" size="0x0.16" />
	<field name="num_of_diagnostic_counters" descr="Indicates number of diagnostic counters supported by device.\;Software should query debug capabilities for detailed capabilities. Section  32.3.4.11, &quot;Debug Capabilities,&quot; on page  4119" offset="0x50.16" size="0x0.16" />
	<field name="max_wqe_sz_rq" descr="Max descriptor size in bytes for the RQ and SRQ. RQ and SRQ WQEs must not be bigger than indicated here." offset="0x54.0" size="0x0.16" />
	<field name="regexp_version" descr="Indicates the regexp version.\;Valid only when regexp_params==1.\;0x0: version_0 \;0x1: version_1" offset="0x54.16" size="0x0.3" />
	<field name="regexp_mmo_sq" descr="If set, REGEX MMO in SQ is supported. SW can use MMO WQE of type REGEXP.\;" offset="0x54.19" size="0x0.1" />
	<field name="shampo" descr="If set, SHAMPO operations are supported.\;To get detailed SHAMPO capabilities, software should query SHAMPO cap Section  32.3.4.22, &quot;SHAMPO Capabilities,&quot; on page  4153" offset="0x54.20" size="0x0.1" />
	<field name="psp" descr="If set, PSP is supported. See Section  32.3.4.16, &quot;PSP Capabilities,&quot; on page  4129" offset="0x54.21" size="0x0.1" />
	<field name="tis_tir_td_order" descr="if clr, TIR of a transport domain should either be created after all TISs and SQs of the same domain, TIR.self_lb_en should be reapplied using MODIFY_TIR, for self loopback filtering to function correctly.\;if set, no creation/update ordering is required for self loopback filtering" offset="0x54.22" size="0x0.1" />
	<field name="mkey_error_isolate" descr="If set, the device supports isolating MKey Access Error from QP Error. See Section  9.5.1, &quot;Isolate Memory Access Error and QP Error,&quot; on page  1221." offset="0x54.23" size="0x0.1" />
	<field name="mkey_pcie_tph" descr="If set, MKey TPH is supported" offset="0x54.24" size="0x0.1" />
	<field name="pcc_np_multiplane_probe" descr="If set, PCC NP supports responding to probe packets on the same plane it was received" offset="0x54.25" size="0x0.1" />
	<field name="pcc_np_gns_select_full_bit_mask" descr="If set, PCC_NP_CONFIG supports gns_selec FULL_BIT_MASK mode" offset="0x54.26" size="0x0.1" />
	<field name="pcc_np_resp_ts_insert" descr="If set, PCC NP supports inserting probe response timestamp (T3) into the probe response packet." offset="0x54.27" size="0x0.1" />
	<field name="embedded_program" descr="If set Embedded Program Capabilities are available. See Section  32.3.4.23, &quot;Embedded Program Capabilities,&quot; on page  4154\;If clr, HCA_CAP.dpa should be checked." offset="0x54.28" size="0x0.1" />
	<field name="driver_ver_change_event_id_mode" descr="Defines how DRIVER_VERSION_CHANGE Event identifies a function:\;0x0: FUNCTION_INDEX\;0x1: FUNCTION_VHCA_ID" enum="FUNCTION_INDEX=0x0,FUNCTION_VHCA_ID=0x1" offset="0x54.29" size="0x0.1" />
	<field name="vhca_state_change_event_id_mode" descr="Defines how VHCA State Change Event identifies a function:\;0x0: FUNCTION_INDEX\;0x1: FUNCTION_VHCA_ID" enum="FUNCTION_INDEX=0x0,FUNCTION_VHCA_ID=0x1" offset="0x54.30" size="0x0.1" />
	<field name="icm_mng_function_id_mode" descr="Defines how MANAGE_PAGES, QUERY_PAGES and page request identify a function:\;0x0: FUNCTION_INDEX\;0x1: FUNCTION_VHCA_ID" enum="FUNCTION_INDEX=0x0,FUNCTION_VHCA_ID=0x1" offset="0x54.31" size="0x0.1" />
	<field name="max_wqe_sz_sq_dc" descr="Max descriptor size in bytes for the SQ of DC type. SQ WQEs must not be bigger than indicated here." offset="0x58.0" size="0x0.16" />
	<field name="max_flow_counter_31_16" descr="MSB of the maximum number of flow counters." offset="0x58.16" size="0x0.16" />
	<field name="max_qp_mcg" descr="Maximum number of QPs per multicast group." offset="0x5C.0" size="0x0.25" />
	<field name="query_host_net_function_num_max" descr="Maximum number of entries that can be returned by QUERY_HOST_NET_FUNCTIONS command. Value 0x0 indicates only a single entry is returned." offset="0x5C.27" size="0x0.5" />
	<field name="log_max_mcg" descr="Log (base 2) of the maximum number of multicast groups." offset="0x60.0" size="0x0.8" />
	<field name="flow_counter_bulk_alloc" descr="\;Bitmask field indicates the supported bulk sizes in ALLOC_FLOW_COUNTER command Table  4205, &quot;ALLOC_FLOW_COUNTER Input Structure Layout,&quot; on page  4466.\;\;Bit 0: BULK_128 - allocate 128 counters.\;Bit 1: BULK_256 - allocate 256 counters.\;Bit 2: BULK_512 - allocate 512 counters.\;Bit 3: BULK_1K - allocate 1K counters.\;Bit 4: BULK_2K - allocate 2K counters.\;Bit 5: BULK_4K - allocate 4K counters.\;Bit 6: BULK_8K - allocate 8K counters.\;Bit 7: BULK_16K - allocate 16K counters." enum="BULK_128=0x1,BULK_256=0x2,BULK_512=0x4,BULK_1K=0x8,BULK_2K=0x10,BULK_4K=0x20,BULK_8K=0x40,BULK_16K=0x80" offset="0x60.8" size="0x0.8" />
	<field name="mlnx_tag_ethertype" descr="Ethernet type value which indicates Mellanox tagging.\;0 means not supported.\;See Section  3.7, &quot;MLNX ETHERTYPE TAGGING,&quot; on page  393." offset="0x60.16" size="0x0.16" />
	<field name="log_max_xrcd" descr="Log (base 2) of the maximum number of XRCDs." offset="0x64.0" size="0x0.5" />
	<field name="q_counter_other_vport" descr="When set, QUERY_Q_COUNTER supports query of other vhca counter sets" offset="0x64.5" size="0x0.1" />
	<field name="q_counter_aggregation" descr="When set, QUERY_Q_COUNTER supports reporting the aggrgation of all Q counters sets." offset="0x64.6" size="0x0.1" />
	<field name="vport_counter_local_loopback" descr="When set, local_loopback counter is supported in Section 32.35.1, &quot;QUERY_VPORT_COUNTER - Query Vport Counter&quot;, on page 4653" offset="0x64.7" size="0x0.1" />
	<field name="vnic_env_cnt_steering_fail" descr="When set, generated_pkt_steering_fail and handled_pkt_steering_fail are supported in QUERY_VNIC_ENV command" offset="0x64.8" size="0x0.1" />
	<field name="pci_sync_for_fw_update_with_driver_unload" descr="If set, device reset synchronization is supported using pci_sync_for_fw_update sub-event, including DRIVER_UNLOAD stage. See &quot;Driver Flow During Reset&quot; on page 356" offset="0x64.9" size="0x0.1" />
	<field name="pcie_reset_using_hotreset" descr="If set, device reset using SBR is supported using pci_reset_method. Driver should set if SBR is supported.\;Hot reset is triggered by writing to SBR bit in Bridge Control Register defined by PCIe Base spec" offset="0x64.10" size="0x0.1" />
	<field name="dp_ordering_ooo_all_rc" descr="When set, the QP ordering semantic OOO_ALL is supported for RC service type. See Table 13.2.5, &quot;QP Ordering Semantics,&quot; on page 1594" offset="0x64.11" size="0x0.1" />
	<field name="dp_ordering_ooo_all_dc" descr="When set, the QP ordering semantic OOO_ALL is supported for DC service type. See Table 13.2.5, &quot;QP Ordering Semantics,&quot; on page 1594" offset="0x64.12" size="0x0.1" />
	<field name="dp_ordering_ooo_all_xrc" descr="When set, the QP ordering semantic OOO_ALL is supported for XRC service type. See Table 13.2.5, &quot;QP Ordering Semantics,&quot; on page 1594" offset="0x64.13" size="0x0.1" />
	<field name="dp_ordering_ooo_all_uc" descr="When set, the QP ordering semantic OOO_ALL is supported for UC service type. See Table 13.2.5, &quot;QP Ordering Semantics,&quot; on page 1594" offset="0x64.14" size="0x0.1" />
	<field name="dp_ordering_ooo_all_ud" descr="When set, the QP ordering semantic OOO_ALL is supported for UD service type. See Table 13.2.5, &quot;QP Ordering Semantics,&quot; on page 1594" offset="0x64.15" size="0x0.1" />
	<field name="log_max_pd" descr="Log (base 2) of the maximum number of PDs." offset="0x64.16" size="0x0.5" />
	<field name="pci_relaxed_ordered_read" descr="If set, MKeys support setting pci_relaxed_ordered_read." offset="0x64.21" size="0x0.1" />
	<field name="flow_table_freeze" descr="When set, freezing a Flow Table using freeze field is supported" offset="0x64.22" size="0x0.1" />
	<field name="tir_esw_lb_filter_disable" descr="When set, TIRs will not consider packets hairpinned by the eswitch for filtering by transport domain." offset="0x64.23" size="0x0.1" />
	<field name="log_max_transport_domain" descr="Log (base 2) of the maximum number of Transport Domains." offset="0x64.24" size="0x0.5" />
	<field name="always_fire_port_state_change_event" descr="When set - the vport will receive port_state_change Event when physical port state is changed regardless of its esw_vport state, nic_vport state or uplink policy (up/down/follow).\;" offset="0x64.29" size="0x0.1" />
	<field name="uncorrectable_notification_dpu_reset_en" descr="When set - on DPU panic\reset, the device will signal an uncorrectable error through AER PCIe cap (Uncorrectable Internal Error Status) to all hosts it is connected to.\;" offset="0x64.30" size="0x0.1" />
	<field name="emulated_vf_exist" descr="If set, the vf_exist to EMULATED_FUNCTION_INFO is valid." offset="0x64.31" size="0x0.1" />
	<field name="max_flow_counter_15_0" descr="LSB of the maximum number of flow counters.\;" offset="0x68.0" size="0x0.16" />
	<field name="log_max_flow_counter_bulk" descr="Log (base 2) of the maximal number of flow counters that can be queried by a single QUERY_FLOW_COUNTER command.Table  4213, &quot;QUERY_FLOW_COUNTER Input Structure Layout,&quot; on page  4469." offset="0x68.16" size="0x0.8" />
	<field name="quota_exceeded_count" descr="When set, the device supports Quota Exceeded counter for a vNIC in QUERY_VNIC_ENV. See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\\;" offset="0x68.25" size="0x0.1" />
	<field name="invalid_command_count" descr="When set, the device supports Invalid Command counter for a vNIC in QUERY_VNIC_ENV. See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\;" offset="0x68.26" size="0x0.1" />
	<field name="nic_receive_steering_depth" descr="when set, the device support reporting of a the steering depth of the NIC Receive Flow Table in QUERY_VNIC_ENV.\;See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\;" offset="0x68.27" size="0x0.1" />
	<field name="eq_overrun_count" descr="When set, the device supports Completion event and Async event EQ overrun counter for a vNIC in QUERY_VNIC_ENV. See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\;report" offset="0x68.28" size="0x0.1" />
	<field name="transmit_discard_vport_down" descr="When set QUERY_VNIC_ENV supports transmit_discard_vport_down counter. See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\;" offset="0x68.29" size="0x0.1" />
	<field name="receive_discard_vport_down" descr="When set QUERY_VNIC_ENV supports receive_discard_vport_down counter. See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\;" offset="0x68.30" size="0x0.1" />
	<field name="nic_receive_steering_discard" descr="When set QUERY_VNIC_ENV supports nic_receive_steering_discard counter. See Section 32.35.2, &quot;QUERY_VNIC_ENV - Query vNIC Environment&quot;, on page 4659\;" offset="0x68.31" size="0x0.1" />
	<field name="log_max_tis" descr="Log (base2) of the number of TIS supported. \;0 - feature not supported." offset="0x6C.0" size="0x0.5" />
	<field name="log_max_tir" descr="Log (base2) of the number of TIR supported. \;0 - feature not supported." offset="0x6C.8" size="0x0.5" />
	<field name="mp_load_balance_mode" descr="Defines support for device based load balancing for RDMA packets in multiplane\;0x1: NO_BALANCING - LB by device is not supported\;0x2: TRANSPORT - LB is performed by the device at the transport layer\;0x3: PACKET_STEERING - LB can be done by Flow Table actions\;Other values should be considered as NO_BALANCING" offset="0x6C.13" size="0x0.3" />
	<field name="log_max_sq" descr="Log (base2) of the number of SQ supported. \;0 - feature not supported." offset="0x6C.16" size="0x0.5" />
	<field name="cq_null_eq" descr="If set, CQ can be created with NULL_EQ element type." offset="0x6C.22" size="0x0.1" />
	<field name="ft_alias_sw_vhca_id" descr="If set, ALIAS_CONTEXT.vhca_id_type SW_VHCA_ID is supported for FLOW_TABLE_ALIAS Object type." offset="0x6C.23" size="0x0.1" />
	<field name="log_max_rq" descr="Log (base2) of the number of RQ supported. \;0 - feature not supported." offset="0x6C.24" size="0x0.5" />
	<field name="pad_tls_encrypt_sig" descr="When set, Packet Padding is support for packets performing TLS/Disk Encryption/Signature operations" offset="0x6C.29" size="0x0.1" />
	<field name="flow_counters_dump" descr="If set, device supports dump of flow counters to memory by QUERY_FLOW_COUNTER command instead of returning counters in the command&apos;s outbox." offset="0x6C.30" size="0x0.1" />
	<field name="modify_tis" descr="If set, MODIFY_TIS command is supported. Section  32.14.2, &quot;MODIFY_TIS - Modify TIS,&quot; on page  4358." offset="0x6C.31" size="0x0.1" />
	<field name="log_max_tis_per_sq" descr="Log (base2) of the number of TIS supported per SQ." offset="0x70.0" size="0x0.5" />
	<field name="vnic_env_cnt_odp_page_fault" descr="If set, QUERY_VNIC_ENV supports odp_local_triggered_page_fault and odp_remote_triggered_page_fault counters" offset="0x70.5" size="0x0.1" />
	<field name="vnic_env_cnt_bar_uar_access" descr="If set, QUERY_VNIC_ENV supports bar_uar_access counter" offset="0x70.6" size="0x0.1" />
	<field name="tlp_device_emulation_manager" descr="If set, this vHCA is allowed to manage TLP based device emulation. For detailed capabilities see Table  1636, &quot;TLP_DEVICE_EMULATION Capabilities Layout,&quot; on page  2078." offset="0x70.7" size="0x0.1" />
	<field name="log_max_rqt_size" descr="Log (base2) of max RQT size." offset="0x70.8" size="0x0.5" />
	<field name="qp_e2e_credit_disable" descr="if set, QP.req_e2e_credit_mode supports E2E_CREDIT_DISABLE mode." offset="0x70.13" size="0x0.1" />
	<field name="query_delegated_vhca" descr="If set, QUERY_DELEGATED_VHCA command is supported." offset="0x70.14" size="0x0.1" />
	<field name="delegate_vhca_management" descr="If set, DELEGATE_VHCA_MANAGEMENT command is supported." offset="0x70.15" size="0x0.1" />
	<field name="log_max_rqt" descr="Log (base2) of the number of RQTs supported.\;0 - feature not supported." offset="0x70.16" size="0x0.5" />
	<field name="vport_metadata_clr" descr="If set, VNIC and Eswitch manager can clr packet metadata when crossing Vport boundary using vport_to_fdb_metadata and fdb_to_vport_metadata in NIC Vport Conetxt and ESW Vport Conetxt respectively." offset="0x70.21" size="0x0.1" />
	<field name="pci_sync_for_fw_update_tool_reset" descr="if set, device reset by tool is supported. See &quot;Driver Flow During Reset&quot; on page 356" offset="0x70.22" size="0x0.1" />
	<field name="sd_group_size" descr="If set, NIC vport context sd_group_size is supported." offset="0x70.23" size="0x0.1" />
	<field name="log_max_rmp" descr="Log (base2) of the number of RMPs supported.\;0 - feature not supported." offset="0x70.24" size="0x0.5" />
	<field name="mem_rq_rmp" descr="If set, mem_rq_type of type MEMORY_RQ_RMP in RQ context is supported. See Table 232, &quot;RQ Context Fields,&quot; on page 686" offset="0x70.29" size="0x0.1" />
	<field name="eth_wqe_too_small_discard_no_cqe" descr="When set, NIC_VPORT_CONTEXT.eth_wqe_too_small_mode can be set to DISCARD_WQE_NO_CQE" offset="0x70.30" size="0x0.1" />
	<field name="basic_cyclic_rcv_wqe" descr="0: cyclic receive WQE always includes the 16 byte of ctrl (signature field).\;1: cyclic receive WQE includes the 16 bytes of ctrl only when RMP.basic_cyclic_rcv_wqe/XRC_SRQ.basic_cyclic_rcv_wqe is enabled.\;" offset="0x70.31" size="0x0.1" />
	<field name="log_min_stride_sz_sq" descr="Log (base2) of the minimum size (in bytes) of SQ stride." offset="0x74.0" size="0x0.5" />
	<field name="aes_xts_transaction_sig" descr="If set, aes-xts and transaction signature are supported in the same BSF (BSF_128B)" offset="0x74.7" size="0x0.1" />
	<field name="log_max_stride_sz_sq" descr="Log (base2) of the maximum size (in bytes) of SQ stride." offset="0x74.8" size="0x0.5" />
	<field name="qp_latency_sensitive_disable" descr="If clr, QP latency_sensitive is supported." offset="0x74.13" size="0x0.1" />
	<field name="queue_mng_aso_credit_ctrl" descr="If set, QUEUE_MNG_ASO supports non-zero credit_ctrl" offset="0x74.14" size="0x0.1" />
	<field name="queue_mng_aso_queue_op_consumer" descr="If set, QUEUE_MNG_ASO supports queue_op CONSUMER_INC" offset="0x74.15" size="0x0.1" />
	<field name="log_min_stride_sz_rq" descr="Log (base2) of the minimum size (in bytes) of RQ stride." offset="0x74.16" size="0x0.5" />
	<field name="sq_ft_wqe_post" descr="If set, SQ ft_wqe_post can be set" offset="0x74.21" size="0x0.1" />
	<field name="mkc_order_write_after_write_ro_only" descr="if set, MKey field order_write_after_write must be set to RELAXED_ORDER." offset="0x74.22" size="0x0.1" />
	<field name="mkc_order_read_after_write" descr="If set, MKeys support setting order_read_after_write to RELAXED_ORDER" offset="0x74.23" size="0x0.1" />
	<field name="log_max_stride_sz_rq" descr="Log (base2) of the maximum size (in bytes) of RQ stride." offset="0x74.24" size="0x0.5" />
	<field name="log_max_current_uc_list_wr_supported" descr="If set, log_max_current_uc_list cap is modifiable by a vHCA to itself.\;limiting log_max_current_uc_list to the required size may improve memory consumption." offset="0x74.29" size="0x0.1" />
	<field name="roce_rw_supported" descr="If set, roce cap is modifiable by a vHCA to itself.\;Disabling roce when not needed may improve memory consumption." offset="0x74.30" size="0x0.1" />
	<field name="ext_stride_num_range" descr="When set, the device supports the following values for the number of strides per WQE of a Striding WQ:\;8, 16, 32..., 256" offset="0x74.31" size="0x0.1" />
	<field name="log_max_wq_sz" descr="Log (base 2) of the maximum number of WQEs allowed on the WQ." offset="0x78.0" size="0x0.5" />
	<field name="log_max_hairpin_num_packets" descr="Log (base 2) of the maximum number of packets allowed on hairpin WQ." offset="0x78.8" size="0x0.5" />
	<field name="log_max_hairpin_wq_data_sz" descr="Log (base 2) of the maximum size of data buffer on hairpin WQ in granularity of bytes.\;" offset="0x78.16" size="0x0.5" />
	<field name="hairpin_ipoib2eth" descr="If set, hairpin for IPoIB traffic to ETH traffic is supported.\;See Section 3.8, &quot;Hairpin&quot;, on page 394" offset="0x78.21" size="0x0.1" />
	<field name="hairpin_eth2ipoib" descr="If set, hairpin for ETH traffic to IPoIB traffic is supported.\;See Section 3.8, &quot;Hairpin&quot;, on page 394" offset="0x78.22" size="0x0.1" />
	<field name="hairpin_ib_raw" descr="If set, hairpin for IB native traffic is supported.\;See Section 3.8, &quot;Hairpin&quot;, on page 394" offset="0x78.23" size="0x0.1" />
	<field name="log_max_hairpin_queues" descr="Log (base 2) of the maximum hairpin SQs and RQs supported." offset="0x78.24" size="0x0.5" />
	<field name="hairpin_trim" descr="If set, Hairpin Trim is supported. RQ hairpin_trim_size may be set with non-zero value." offset="0x78.30" size="0x0.1" />
	<field name="hairpin" descr="If set, hairpin is supported.\;See Section 3.8, &quot;Hairpin&quot;, on page 394" offset="0x78.31" size="0x0.1" />
	<field name="log_max_current_uc_list" descr="Log (base2) of the maximum size of current_uc_mac_address list used in nic_vport_context. Table  95, &quot;NIC_Vport Context Layout,&quot; on page  572.\;This field is RW only if HCA_CAP.log_max_current_uc_list_wr_supported==1, otherwise this field is RO" offset="0x7C.0" size="0x0.5" />
	<field name="query_host_net_function_v1" descr="If set, QUERY_HOST_NET_FUNCTIONS supports output layout verion 0x1" offset="0x7C.5" size="0x0.1" />
	<field name="silent_mode_query" descr="When set, silent_mode querying is supported" offset="0x7C.6" size="0x0.1" />
	<field name="aes_xts_tweak_inc_shift" descr="When set, the device supports incrementing the aes-xts tweak by any power-of-two number every block." offset="0x7C.7" size="0x0.1" />
	<field name="log_max_current_mc_list" descr="Log (base2) of the maximum size of current_mc_mac_address list used in nic_vport_context. Table  95, &quot;NIC_Vport Context Layout,&quot; on page  572." offset="0x7C.8" size="0x0.5" />
	<field name="aes_xts_multi_block_be_tweak" descr="If set, aes-xts is supported for multiple block per mkey. Tweak is supplied in big endian." offset="0x7C.13" size="0x0.1" />
	<field name="aes_xts_single_block_le_tweak" descr="If set, aes-xts is supported for a single block per mkey. Tweak is supplied in little endian." offset="0x7C.14" size="0x0.1" />
	<field name="aes_xts_tweak_inc_64" descr="If set, AES-XTS supports incrementing tweak by 2^64 for every block" offset="0x7C.15" size="0x0.1" />
	<field name="log_max_vlan_list" descr="Log (base2) of the maximum size of VLAN list used in nic_vport_context. Table  95, &quot;NIC_Vport Context Layout,&quot; on page  572" offset="0x7C.16" size="0x0.5" />
	<field name="vhca_state" descr="If set, QUERY_VHCA_STATE and MODIFY_VHCA_STATE commands are supported" offset="0x7C.21" size="0x0.1" />
	<field name="silent_mode_set" descr="When set, silent_mode setting is supported" offset="0x7C.22" size="0x0.1" />
	<field name="system_image_guid_modifiable" descr="If set, modifying system_image_guid is supported in NIC vport context.\;See Table  95, &quot;NIC_Vport Context Layout,&quot; on page  572." offset="0x7C.23" size="0x0.1" />
	<field name="log_min_hairpin_wq_data_sz" descr="Log (base 2) of the minimum size of data buffer on hairpin WQ in granularity of bytes." offset="0x7C.24" size="0x0.5" />
	<field name="disable_local_lb_mc" descr="If set, disabling local loopback for multicast is supported in nic vport context using disable_mc_local_lb.\;See Table  95, &quot;NIC_Vport Context Layout,&quot; on page  572." offset="0x7C.29" size="0x0.1" />
	<field name="disable_local_lb_uc" descr="If set, disabling local loopback for unicast is supported in nic vport context using disable_uc_local_lb.\;See Table  95, &quot;NIC_Vport Context Layout,&quot; on page  572." offset="0x7C.30" size="0x0.1" />
	<field name="nic_vport_change_event" descr="If set, Nic vport change event mechanism supported. \;Section  14.1.6, &quot;NIC Vport Change Notification,&quot; on page  1612." offset="0x7C.31" size="0x0.1" />
	<field name="general_obj_types_63_0" descr="Bit mask indicates which general objects are supported.\;This field reports capability of first 64 Objects. Next 64 are reported in HCA_CAP. general_obj_types_127_64.\;Mapping of bits to object types is defined in Table  4341, &quot;GENERAL OBJECT TYPES,&quot; on page  4530" subnode="uint64" offset="0x80.0" size="0x8.0" />
	<field name="create_qp_start_hint" descr="Indicates a hint to the device which QP number is recommended to start creating QPs.\;Supported only if !=0 and 0 means use device creation hint. Note that the reported and requested value is a best effort hint for creating a QP.\;[Internal] FW need to report value !=0 (1 is good) in max cap and current hint default in current cap." offset="0x88.0" size="0x0.24" />
	<field name="steering_format_version" descr="Indicates the device steering logic format. If the device driver does not recognize the current version, SW owned tables should not be used. Valid only for Tables with Sw_owner_v2 set.[Internal]\;0x0: CONNECTX_5\;0x1: CONNECTX_6DX\;0x2: CONNECTX_7\;0x3: CONNECTX_8\;other values are reserved for future formats" enum="CONNECTX_5=0x0,CONNECTX_6DX=0x1,CONNECTX_7=0x2,CONNECTX_8=0x3" offset="0x88.24" size="0x0.4" />
	<field name="rq_ts_format" descr="Indicates the supported ts_format in RQ Context.\;0x0: FREE_RUNNING_TS\;0x1: REAL_TIME_TS\;0x2: FREE_RUNNING_AND_REAL_TIME_TS - both free running real time timestamps are supported." enum="FREE_RUNNING_TS=0x0,REAL_TIME_TS=0x1,FREE_RUNNING_AND_REAL_TIME_TS=0x2" offset="0x88.28" size="0x0.2" />
	<field name="sq_ts_format" descr="Indicates the supported ts_format in SQ Context.\;0x0: FREE_RUNNING_TS\;0x1: REAL_TIME_TS\;0x2: FREE_RUNNING_AND_REAL_TIME_TS - both free running real time timestamps are supported." enum="FREE_RUNNING_TS=0x0,REAL_TIME_TS=0x1,FREE_RUNNING_AND_REAL_TIME_TS=0x2" offset="0x88.30" size="0x0.2" />
	<field name="max_num_eqs" descr="Maximum number of EQs supported by the device.\;Value 0x0 indicates the number should be derived from HCA_CAP.log_max_eq." offset="0x8C.0" size="0x0.16" />
	<field name="log_max_umem" descr="Log(base 2) of maximum supported UMEM objects.\;0 means not supported." offset="0x8C.16" size="0x0.5" />
	<field name="ipsec_offload" descr="When set IPsec Offload capabilities are supported.\;Detailed capabilities are reported in Table  3543, &quot;IPSEC Capabilities Layout,&quot; on page  4126" offset="0x8C.21" size="0x0.1" />
	<field name="crypto" descr="" offset="0x8C.22" size="0x0.1" />
	<field name="aes_xts_multi_block_le_tweak" descr="aes-xts is supported for multiple blocks per mkey , tweak supplied in little endian" offset="0x8C.23" size="0x0.1" />
	<field name="log_max_uctx" descr="Log(base 2) of maximum supported UCTX objects.\;0 means not supported." offset="0x8C.24" size="0x0.5" />
	<field name="cross_vhca_rqt" descr="When set, RQT can hold RQs of different vHCAs." offset="0x8C.29" size="0x0.1" />
	<field name="ats" descr="If set, the device supports ATS and it has been enabled in the PCIe extended capability. \;Only when it is set, SW may set Mkey.ma_translation_mode==ATS and UMEM.ats==1." offset="0x8C.30" size="0x0.1" />
	<field name="log_uar_page_sz" descr="Log (base 2) of UAR page in 4Kbyte chunks." offset="0x90.0" size="0x0.16" />
	<field name="log_max_l2_table" descr="Log (base2) of the maximum size of L2 Table.\;Section  32.20, &quot;L2 Table Commands,&quot; on page  4506." offset="0x90.24" size="0x0.5" />
	<field name="tls_rx" descr="If set, TLS offload For received traffic is supported.\;Detailed capabilities are reported in Table  3541, &quot;TLS Capabilities Layout,&quot; on page  4125" offset="0x90.29" size="0x0.1" />
	<field name="tls_tx" descr="If set, TLS offload For transmit traffic is supported.\;Detailed capabilities are reported in Table  3541, &quot;TLS Capabilities Layout,&quot; on page  4125" offset="0x90.30" size="0x0.1" />
	<field name="sigerr_domain_and_sig_type" descr="If set, SIGERR CQE supports reporting domain and sig_type fields." offset="0x90.31" size="0x0.1" />
	<field name="hairpin_trim_size_max" descr="Maximum supported value for RQ hairpin_trim_size given in bytes.. Valid if hairpin_trim is set" offset="0x94.0" size="0x0.16" />
	<field name="e" descr="[EMC] EMC mode. EMC-only features and APIs are enabled" offset="0x94.31" size="0x0.1" />
	<field name="device_frequency_mhz" descr="Internal device frequency given in MHz. Valid only if non-zero. This field is deprecated and replaced by device_frequency_khz." offset="0x98.0" size="0x4.0" />
	<field name="device_frequency_khz" descr="Internal device frequency given in KHz. Valid only if non-zero. \;When supported, this field reports more accurate value of the device frequency comparing to device_frequency_mhz.\;Section  8.20.14, &quot;CQE Timestamping,&quot; on page  823" offset="0x9C.0" size="0x4.0" />
	<field name="log_max_pasid" descr="Log (base 2) of the maximum PASIDs supported. Section  25, &quot;CAPI- Coherent Accelerator Programming Interface,&quot; on page  1871." offset="0xA0.0" size="0x0.5" />
	<field name="capi_invalidate" descr="If set, CAPI invalidation by INIT_SEGMENT.capi_invalidate is supported." offset="0xA0.28" size="0x0.1" />
	<field name="nvmf_target_offload" descr="If set, NVMe-oF target offload is supported.\;See Section  8.22.2, &quot;NVM Express over Fabric (NVMe-oF) Target Offload Context,&quot; on page  879." offset="0xA0.29" size="0x0.1" />
	<field name="create_pec" descr="If set, CREATE_CAPI_PEC is supported.\;See Section  25, &quot;CAPI- Coherent Accelerator Programming Interface,&quot; on page  1871" offset="0xA0.30" size="0x0.1" />
	<field name="capi" descr="If set, CAPI is supported.\;See Section  25, &quot;CAPI- Coherent Accelerator Programming Interface,&quot; on page  1871" offset="0xA0.31" size="0x0.1" />
	<field name="num_of_uars_per_page" descr="Number of 4KB UARs per system page. Valid only when uar_4k==1." offset="0xA4.0" size="0x4.0" />
	<field name="flex_parser_protocols" descr="Bit mask indicates which Flex parser protocols are already enabled. The enable is done by NV_FLEX_PARSER_CONF Tlv. \;Bit 0: flex_ipv4_over_vxlan_enabled\;Bit 1: flex_ipv4_over_ip_enabled\;Bit 2: flex_ipv6_over_ip_enabled\;Bit 3: flex_geneve_enabled\;Bit 7: flex_vxlan_gpe_enabled\;Bit 8: flex_icmp_enabled\;Bit 9: flex_icmpv6_enabled\;Bit 10: flex_geneve_tlv_option_0_enabled\;Bit 11: flex_gtp_u_enabled\;Bit 12: flex_ipoib_ud_qp_enabled\;Bit 13: flex_vxlan_pad_enabled\;Bit 14: flex_cw_mpls_over_gre_enabled\;Bit 15: flex_cw_mpls_over_udp_enabled\;Bit 16: flex_gtpu_dw_2_enabled\;Bit 17: flex_gtpu_first_ext_dw_0_enabled\;Bit 18: flex_gtpu_dw_0_enabled\;Bit 19: flex_gtpu_teid_enabled\;Bit 20: flex_vxlan_gpe_nsh_enabled" enum="flex_ipv4_over_vxlan_enabled=0x1,flex_ipv4_over_ip_enabled=0x2,flex_ipv6_over_ip_enabled=0x4,flex_geneve_enabled=0x8,flex_vxlan_gpe_enabled=0x80,flex_icmp_enabled=0x100,flex_icmpv6_enabled=0x200,flex_geneve_tlv_option_0_enabled=0x400,flex_gtp_u_enabled=0x800,flex_ipoib_ud_qp_enabled=0x1000,flex_vxlan_pad_enabled=0x2000,flex_cw_mpls_over_gre_enabled=0x4000,flex_cw_mpls_over_udp_enabled=0x8000,flex_gtpu_dw_2_enabled=0x10000,flex_gtpu_first_ext_dw_0_enabled=0x20000,flex_gtpu_dw_0_enabled=0x40000,flex_gtpu_teid_enabled=0x80000,flex_vxlan_gpe_nsh_enabled=0x100000" offset="0xA8.0" size="0x4.0" />
	<field name="log_max_dct_connections" descr="Log (base2) of maximum number of outstanding connections that can be assigned per DCT." offset="0xAC.0" size="0x0.5" />
	<field name="driver_metadata_ptr" descr="If set then driver_metadata_ptr in SET_DRIVER_VERSION is supported." offset="0xAC.5" size="0x0.1" />
	<field name="adv_virtualization" descr="When set, Advanced Virtualization Capabilities are supported\;See Table  3565, &quot;ADV_VIRTUALIZAION Capabilities Layout,&quot; on page  4163" offset="0xAC.6" size="0x0.1" />
	<field name="driver_version_before_init_hca" descr="If set SW can execute driver version command before INIT_HCA." offset="0xAC.7" size="0x0.1" />
	<field name="log_max_guaranteed_connections" descr="Log (base2) of the maximum number of the total guaranteed outstanding connections." offset="0xAC.8" size="0x0.5" />
	<field name="ts_prov_cap" descr="If set TRANSPORT_SERVICE_PROV Capabilities are supported. See Table  3569, &quot;TRANSPORT_SERVICE_PROVIDER Capabilities Layout,&quot; on page  4174" offset="0xAC.13" size="0x0.1" />
	<field name="adv_rdma_cap" descr="If set, Advanced RDMA Capabilities are supported.\;See Table  3567, &quot;ADV_RDMA Capabilities Layout,&quot; on page  4164" offset="0xAC.14" size="0x0.1" />
	<field name="flex_parser_header_modify" descr="If set, Header modify for fields flex parser headers is supported." offset="0xAC.15" size="0x0.1" />
	<field name="max_geneve_tlv_option_data_len" descr="The maximum value that can be set in data_length field in GENEVE_TLV_OPTION general object.\;See" offset="0xAC.16" size="0x0.5" />
	<field name="geneve_tlv_option_offset" descr="When set, Geneve TLV Option sampling supports setting the offset of the sample from the start of the Option." offset="0xAC.22" size="0x0.1" />
	<field name="geneve_tlv_sample" descr="When set, Geneve TLV Option sampling supports sample handles for steering usage" offset="0xAC.23" size="0x0.1" />
	<field name="max_geneve_tlv_options" descr="Maximum number of supported geneve TLV options that can be matched" offset="0xAC.24" size="0x0.8" />
	<field name="log_max_atomic_size_dc" descr="Log (base 2) of the maximum atomic operand size in bytes for DC qps\;Removed" offset="0xB0.0" size="0x0.8" />
	<field name="log_max_dci_errored_streams" descr="Log (base 2) of the maximum DCI error stream channels supported per DCI before a DCI move to error state." offset="0xB0.8" size="0x0.5" />
	<field name="log_max_dci_stream_channels" descr="Log (base 2) of the maximum DCI stream channels supported per DCI." offset="0xB0.16" size="0x0.5" />
	<field name="log_max_atomic_size_qp" descr="Log (base 2) of the maximum atomic operand size in bytes for all qps.\;Removed." offset="0xB0.24" size="0x0.8" />
	<field name="cqe_compression" descr="CQE Compression is supported,\;See Section  8.20.11, &quot;CQE Compression,&quot; on page  802" offset="0xB4.0" size="0x0.1" />
	<field name="cqe_compression_128b" descr="If set, CQE compression for 128 Byte CQE is supported.\;See Section  8.20.11, &quot;CQE Compression,&quot; on page  802" offset="0xB4.1" size="0x0.1" />
	<field name="cqe_128_always" descr="If set, CQE of size byte always is supported.\;See cqe_sz field in CQ Context.\;See Table  306, &quot;Completion Queue Context Layout,&quot; on page  817" offset="0xB4.2" size="0x0.1" />
	<field name="mini_cqe_resp_stride_index" descr="If set, Resp_ByteCnt_Checksum_Stride_Index format in mini_cqe_res_format is supported.\;See Table  307, &quot;Completion Queue Context Field Descriptions,&quot; on page  818" offset="0xB4.3" size="0x0.1" />
	<field name="mini_cqe_resp_flow_tag" descr="If set, Resp_Flow_Tag format in mini_cqe_res_format is supported.\;See Table  307, &quot;Completion Queue Context Field Descriptions,&quot; on page  818" offset="0xB4.5" size="0x0.1" />
	<field name="mini_cqe_resp_l3_l4_tag" descr="If set, Resp_l3_l4_info format in mini_cqe_res_format is supported.\;See Table  307, &quot;Completion Queue Context Field Descriptions,&quot; on page  818" offset="0xB4.6" size="0x0.1" />
	<field name="log_max_dek" descr="Log(base 2) of maximum DEK Objects that are supported.\;0 means not supported." offset="0xB4.8" size="0x0.5" />
	<field name="crossing_vhca_mkey" descr="If set, creating mkey with access_mode==CROSSING_VHCA_MKEY is supported.\;See Section  9.2.2.2, &quot;Translation Indirection to another vHCA,&quot; on page  1213\;" offset="0xB4.13" size="0x0.1" />
	<field name="generic_device_emulation_manager" descr="If set, this Generic PCI device emulation is supported" offset="0xB4.14" size="0x0.1" />
	<field name="enhanced_cqe_compression" descr="If set, then ENHANCED_CQE_COMPRESSION in CQ.cqe_compression_layout is supported" offset="0xB4.15" size="0x0.1" />
	<field name="max_multi_user_group_size" descr="Maximum size of slave QPs that can be attached to a multi user master QP.\;0 means feature not supported\;See Section  8.3.4.4, &quot;Multi User QP,&quot; on page  539" offset="0xB4.16" size="0x0.16" />
	<field name="cqe_compression_max_num" descr="Max number of compressed and aggregated CQEs in a single session.\;Valid only if cqe_compression =1.\;See Section  8.20.11, &quot;CQE Compression,&quot; on page  802" offset="0xB8.0" size="0x0.16" />
	<field name="cqe_compression_timeout" descr="CQE Compression session expiration timeout in usecs.\;Valid only if cqe_compression =1.\;Note that When ZTT is enabled, this field may be changed during runtime in order to optimize the device performance. SW who wish to know the most accurate value on such case should periodically query this field.\;See Section  8.20.11, &quot;CQE Compression,&quot; on page  802" offset="0xB8.16" size="0x0.16" />
	<field name="log_max_xrq" descr="Log (Base 2) of the maximum number of XRQs supported." offset="0xBC.0" size="0x0.5" />
	<field name="sync_steering_cache_inv" descr="When set, dynamic cache invalidation for SW steering can be managed SYNC_STEERING command" offset="0xBC.6" size="0x0.1" />
	<field name="modify_xrq" descr="If set, MODIFY_XRQ command will be supported. See Section  32.29.4, &quot;MODIFY_XRQ - Modify XRQ,&quot; on page  4595" offset="0xBC.7" size="0x0.1" />
	<field name="log_tag_matching_list_sz" descr="Log (Base 2) of the maximum number of tags SW is allowed to append for tag matching topology." offset="0xBC.8" size="0x0.5" />
	<field name="rndv_offload_dc" descr="When set, rendezvous offload for DC transport service is supported. See Section  23.3, &quot;Tag Matching and Rendezvous Offload,&quot; on page  1731" offset="0xBC.13" size="0x0.1" />
	<field name="rndv_offload_rc" descr="When set, rendezvous offload for RC transport service is supported. See Section  23.3, &quot;Tag Matching and Rendezvous Offload,&quot; on page  1731" offset="0xBC.14" size="0x0.1" />
	<field name="tag_matching" descr="When set, Tag Matching is supported. See Section  23.3, &quot;Tag Matching and Rendezvous Offload,&quot; on page  1731" offset="0xBC.15" size="0x0.1" />
	<field name="log_max_tm_offloaded_op_size" descr="Log (base 2) of the maximal IB payload size of offloaded tagmatching message in granularity of bytes (includes tag matching header)." offset="0xBC.16" size="0x0.4" />
	<field name="flex_parser_id_gtpu_dw_0" descr="Indicate the Flex Parser ID used to parse gtpu_dw_0 field. Valid only when flex_gtpu_dw_0_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xBC.20" size="0x0.4" />
	<field name="must_not_use" descr="" offset="0xBC.24" size="0x0.8" />
	<field name="sw_owner_id" descr="If set, the device will accept sw_owner_id by INIT_HCA Command.\;See Section  14.4, &quot;Multi-port vHCA,&quot; on page  1616" offset="0xC0.1" size="0x0.1" />
	<field name="trusted_vnic_vhca" descr="When set, the vNIC/vHCA is as trusted as vhca_group_manager." offset="0xC0.2" size="0x0.1" />
	<field name="flex_parser_id_gtpu_teid" descr="Indicates the Flex Parser ID used to parse gtpu_teid field. Valid only when flex_gtpu_teid_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xC0.4" size="0x0.4" />
	<field name="num_vhca_ports" descr="The number of supported VHCA ports.\;0 means the VHCA supports a single port (0 and 1 are equivalent).\;Applicable only when HCA_CAP.num_ports=1 (reserved otherwise).\;See Section  14.4, &quot;Multi-port vHCA,&quot; on page  1616" offset="0xC0.8" size="0x0.8" />
	<field name="native_port_num" descr="The device physical port number that the VHCA is natively associated with. 0 means field is invalid.\;See Table  14.4, &quot;Multi-port vHCA,&quot; on page  1616" offset="0xC0.16" size="0x0.8" />
	<field name="affiliate_nic_vport_criteria" descr="A bitmask that indicated which vport affiliation criteria are supported in NIC_VPORT_CONTEXT. See Section  8.7, &quot;NIC_Vport Context - NIC Virtual Port Context,&quot; on page  572\;Bit 0: RDMA_AFFILIATION - if set, RDMA affiliation is supported." enum="RDMA_AFFILIATION=0x1" offset="0xC0.24" size="0x0.8" />
	<field name="num_ppcnt_monitor_counters" descr="The number of ppcnt group counters that are supported in PPCNT group by SET_MONITOR_COUNTERS command." offset="0xC4.0" size="0x0.16" />
	<field name="max_num_of_monitor_counters" descr="The maximum number of counters that can be monitored by SET_MONITOR_COUNTERS command." offset="0xC4.16" size="0x0.16" />
	<field name="num_q_monitor_counters" descr="The number of Q group counters that are supported in Q Counters by SET_MONITOR_COUNTERS command." offset="0xC8.0" size="0x0.16" />
	<field name="max_num_sf" descr="The maximum number of Sub-functions that can be supported.\;0 means field is invalid and capability is reported in log_max_sf." offset="0xC8.16" size="0x0.16" />
	<field name="max_num_sf_partitions" descr="Maxim number of sub-function partitions that can be created by SET_SF_PARTITIONS command.\;Valid only when sf_set_partition==1." offset="0xD0.0" size="0x0.8" />
	<field name="log_min_sf_size" descr="Log(base 2) of the minimum bar size of sub-function on in granularity of 4KB.\;Valid only when sf==1." offset="0xD0.8" size="0x0.8" />
	<field name="cq_time_stamp_real_time_mode" descr="Bitmask indicates which Real Time mode of PTP in CQ.\;Bit 0x0: REAL_TIME_ONLY\;Bit 0x1: REAL_TIME_AND_INTERNAL_TIMER\;" enum="REAL_TIME_ONLY=0x1,REAL_TIME_AND_INTERNAL_TIMER=0x2" offset="0xD0.16" size="0x0.2" />
	<field name="migration" descr="If set, Migration commands are supported.\;See Section  14.8, &quot;Virtual Function Migration,&quot; on page  1630 and Section  32.4, &quot;Migration Commands,&quot; on page  4227" offset="0xD0.18" size="0x0.1" />
	<field name="wait_on_time" descr="If set, wait on time wqe is supported.\;" offset="0xD0.19" size="0x0.1" />
	<field name="wait_on_data_big_endian" descr="Deprecated in favor of wait_on_data. \;If set, Wait-on-Data WQE is supported. Polled memory is assumed to be in Big-endian notation.\;Note: This field can be queried only after the host&apos;s endianness was set (e.g., using HOST_ENDIANNESS access register)." offset="0xD0.20" size="0x0.1" />
	<field name="wait_on_data" descr="If set, wait on data WQE is supported. Polled memory is assumed to be in host&apos;s endian notation." offset="0xD0.21" size="0x0.1" />
	<field name="uc_qp_mc" descr="If set, the device supports MC over UC transport See Section  13.2.8, &quot;MC Supported UC Transport,&quot; on page  1599" offset="0xD0.22" size="0x0.1" />
	<field name="dpa" descr="If set, DPA is supported.\;Detailed capabilities are reported in Table  3561, &quot;Embedded Program Capabilities Layout,&quot; on page  4154" offset="0xD0.23" size="0x0.1" />
	<field name="log_max_sf" descr="Log(base 2) of the maximum supported Sub-Functions.\;SW should read this field only if max_num_sf==0.\;Valid only when sf==1." offset="0xD0.24" size="0x0.5" />
	<field name="sf_set_partition" descr="If set, modify of sub-function partitions configuration is supported by SET_SF_PARTITIONS command.\;otherwise, SW can only read the configuration by QUERY_SF_PARTITIONS command.\;Valid only when sf==1." offset="0xD0.30" size="0x0.1" />
	<field name="sf" descr="If set, Sub-Functions is supported (See Section 14.2, &quot;Sub-Function&quot;, on page 1613).\;\;[Internal] FW must report it for ECPF and PF\;Editor Note- it&apos;s RW only to not break BWC.\;If max is 1, SW should set current to 1." offset="0xD0.31" size="0x0.1" />
	<field name="uctx_permission" descr="Bit mask field indicates which capabilities are supported in cap in UCT Context." offset="0xD4.0" size="0x4.0" />
	<field name="flex_parser_id_outer_first_mpls_over_udp_label" descr="Indicates the Flex Parser ID used to parse MPLS over UDP header. Valid only when flex_cw_mpls_over_udp_enabled in HCA_CAP.flex_parser_protocols is set.\;" offset="0xD8.0" size="0x0.4" />
	<field name="flex_parser_id_outer_first_mpls_over_gre" descr="Indicates the Flex Parser ID used to parse MPLS over GRE header. Valid only when flex_cw_mpls_over_gre_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xD8.4" size="0x0.4" />
	<field name="flex_parser_id_icmpv6_dw0" descr="Indicates the Flex Parser ID used to parse DW 0 of ICMPv6 header. Valid only when lex_icmpv6_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xD8.8" size="0x0.4" />
	<field name="flex_parser_id_icmpv6_dw1" descr="Indicates the Flex Parser ID used to parse DW 1 of ICMPv6 header. Valid only when lex_icmpv6_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xD8.12" size="0x0.4" />
	<field name="flex_parser_id_icmp_dw0" descr="Indicates the Flex Parser ID used to parse DW 0 of ICMP header. Valid only when flex_icmp_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xD8.16" size="0x0.4" />
	<field name="flex_parser_id_icmp_dw1" descr="Indicates the Flex Parser ID used to parse DW 1 of ICMP header. Valid only when flex_icmp_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xD8.20" size="0x0.4" />
	<field name="flex_parser_id_geneve_tlv_option_0" descr="Indicate the Flex Parser ID used to parse geneve_tlv_option_0 header. Valid only when geneve_tlv_option_0_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xD8.24" size="0x0.4" />
	<field name="flex_parser_id_mpls_over_x_cw" descr="Indicates the Flex Parser ID used to parse CW following MPLS over GRE/UDP header. Value 0x0 indicates this field is invalid." offset="0xD8.28" size="0x0.4" />
	<field name="sf_base_id" descr="Base sub-function identifier. This is also the base vport number of the Sub-Function on eSwitch.\;Valid only when HCA_CAP.sf==1." offset="0xDC.0" size="0x0.16" />
	<field name="max_num_match_definer" descr="Maximum number of Match Definer objects that can be supported. See Section  8.26.16, &quot;Match Definer Object,&quot; on page  934" offset="0xDC.16" size="0x0.16" />
	<field name="num_total_dynamic_vf_msix" descr="Number of MSI-X vectors that can be distributed to VFs dynamically by the VF resource manager. Value 0x0 indicates that MSI-X vector assignment is done by the device.\;0 means invalid.\;" offset="0xE0.0" size="0x0.24" />
	<field name="flex_parser_id_gtpu_first_ext_dw_0" descr="Indicates the Flex Parser ID used to parse gtpu_first_ext_dw_0 field. Valid only when flex_gtpu_first_ext_dw_0_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xE0.24" size="0x0.4" />
	<field name="flex_parser_id_gtpu_dw_2" descr="Indicates the Flex Parser ID used to parse gtpu_dw_2 field. Valid only when flex_gtpu_dw_2_enabled in HCA_CAP.flex_parser_protocols is set." offset="0xE0.28" size="0x0.4" />
	<field name="dynamic_msix_table_size" descr="Number of MSI-X vectors allocated. Value must be in range defined by min_dynamic_vf_msix_table_size and max_dynamic_vf_msix_table_size. \;Valid only for SET and QUERY from another HCA, which is the vport group manager. Driver should query its own MSI-X table through PCI configuration header." offset="0xE4.0" size="0x0.12" />
	<field name="log_flow_hit_aso_max_alloc" descr="Log (base 2) of the maximum allocation granular-\;ity of FLOW_HIT_ASO Object" offset="0xE4.16" size="0x0.5" />
	<field name="log_flow_hit_aso_granularity" descr="Log (base 2) of the minimum allocation granularity \;of FLOW_HIT_ASO Object." offset="0xE4.24" size="0x0.5" />
	<field name="max_dynamic_vf_msix_table_size" descr="Maximal number of Dynamic MSI-X vectors that can be set in dynamic_msix_table_size for other HCA capabilities" offset="0xE8.0" size="0x0.12" />
	<field name="data_direct" descr="If set, the Data Direct function is supported. See &quot;Data Direct Interface&quot; on page 1689" offset="0xE8.13" size="0x0.1" />
	<field name="host_net_functions_changed" descr="If set, software can query the host&quot;s network PCI functions information and get informed on changes by the HOST_NET_FUNCTIONS_CHANGED event" offset="0xE8.14" size="0x0.1" />
	<field name="decompress_deflate_v2" descr="If set, Decompress Deflate MMO in QP is supported (only RC and DC QPs).\;Maximum size of decompress is reported in HCA_CAP.log_decompress_mmo_max_size." offset="0xE8.15" size="0x0.1" />
	<field name="min_dynamic_vf_msix_table_size" descr="Minimal number of Dynamic MSI-X vectors that can be set in dynamic_msix_table_size for other HCA capabilities" offset="0xE8.16" size="0x0.4" />
	<field name="decompress_deflate_v1" descr="If set, Decompress Deflate MMO in QP is supported (only RC and DC QPs).\;Maximum size of decompress is reported in HCA_CAP.log_decompress_mmo_max_size." offset="0xE8.20" size="0x0.1" />
	<field name="compress_mmo_qp" descr="If set, Compress MMO in QP is supported (only RC and DC QPs).\;Maximum size of compress is reported in HCA_CAP.log_compress_mmo_max_size." offset="0xE8.21" size="0x0.1" />
	<field name="regexp_mmo_qp" descr="If set, REGEX MMO WQEs in QP is supported (only RC and DC QPs)." offset="0xE8.22" size="0x0.1" />
	<field name="dma_mmo_qp" descr="If set, DMA MMO wqe in QP is supported (only RC and DC QPs). \;Maximum size of DMA_MMO is reported in HCA_CAP.log_dma_mmo_max_size." offset="0xE8.23" size="0x0.1" />
	<field name="log_max_num_flow_hit_aso" descr="log (base 2) of the maximum number of supported \;FLOW_HIT_ASO objects" offset="0xE8.24" size="0x0.5" />
	<field name="dpu_cache_invalidate_mmo_qp" descr="If set, Cache-Invalidate MMO WQE in QP is supported. Maximum size of cache-invalidate operation is reported in HCA_CAP.dpu_cache_invalidate_mmo_log_max_size." offset="0xE8.29" size="0x0.1" />
	<field name="qp_mmo_type" descr="If set, QP.mmo_type should indicate the MMO type used by a QP.\;" offset="0xE8.30" size="0x0.1" />
	<field name="sha_mmo_qp" descr="If set, SHA MMO wqe in QP is supported (only RC and DC QPs)." offset="0xE8.31" size="0x0.1" />
	<field name="max_flow_execute_aso" descr="Maximum number of Execute ASO actions supported for a single Flow Table Entry" offset="0xEC.0" size="0x0.5" />
	<field name="log_header_modify_argument_max_alloc" descr="Log (base 2) of the maximum allocation granularity of Header Modify Argument Object, given in 64B units." offset="0xEC.8" size="0x0.5" />
	<field name="log_header_modify_argument_granularity" descr="Defines the Log (base 2) of the minimum allocation granularity of Header Modify Argument Object:\;minimal granularity = log_header_modify_argument_granularity - log_header_modify_argument_granularity_offset\;(4 bit substraction with wraparound)" offset="0xEC.16" size="0x0.4" />
	<field name="log_header_modify_argument_granularity_offset" descr="Defines the Log (base 2) of the minimum allocation granularity of Header Modify Argument Object:\;minimal granularity = log_header_modify_argument_granularity - log_header_modify_argument_granularity_offset\;(4 bit substraction with wraparound)" offset="0xEC.20" size="0x0.4" />
	<field name="log_max_num_header_modify_argument" descr="log (base 2) of the maximum number of supported HEADER_MODIFY_ARGUMENT objects" offset="0xEC.24" size="0x0.5" />
	<field name="vhca_tunnel_commands" descr="Bits mask indicates when the commands are supported to be performed as tunneled commands.\;Bit 0: INIT_HCA\;Bit 1: TEARDOWN_HCA\;Bit 2: ENABLE_HCA\;Bit 3: DISABLE_HCA\;Bit 4: QUERY_SPECIAL_CONTEXT\;Bit 5: FLOW_TABLE_COMMANDS\;Bit 6: QP_COMMANDS\;Bit 9: SET_ROCE_ADDRESS\;Bit 10: QUERY_ROCE_ADDRESS\;Bit 11: GEN_OBJ_CMD_NVME_SQ - General object command of NVME_SQ\;Bit 12: GEN_OBJ_CMD_NVME_CQ - General object command of NVME_CQ\;Bit 13: GEN_OBJ_CMD_NVME_DEVICE_EUMULATION: General object command of DEVICE_EUMULATION\;Bit 14: NVME_NAMESPACE\;Bit 15: PD" subnode="uint64" enum="INIT_HCA=0x1,TEARDOWN_HCA=0x2,ENABLE_HCA=0x4,DISABLE_HCA=0x8,QUERY_SPECIAL_CONTEXT=0x10,FLOW_TABLE_COMMANDS=0x20,QP_COMMANDS=0x40,SET_ROCE_ADDRESS=0x200,QUERY_ROCE_ADDRESS=0x400,GEN_OBJ_CMD_NVME_SQ=0x800,GEN_OBJ_CMD_NVME_CQ=0x1000,GEN_OBJ_CMD_NVME_DEVICE_EUMULATION=0x2000,NVME_NAMESPACE=0x4000,PD=0x8000" offset="0xF0.0" size="0x8.0" />
	<field name="match_definer_format_supported" descr="Bitmask indicates the supported Match Definer Formats. See Section  8.26.16, &quot;Match Definer Object,&quot; on page  934" subnode="uint64" offset="0xF8.0" size="0x8.0" />
</node>

<node name="crypto_caps" descr="" size="0x100.0" >
	<field name="wrapped_import_method" descr="Bitmap indicating for each engine/offload if it is in Plaintext or Wrapped mode. If set, the mode is Wrapped.\;Bit 0: TLS - If set, TLS is in wrapped mode\;Bit 1: IPSEC - If set, IPSEC is in wrapped mode\;Bit 2: AES-XTS - If set, AES-XTS is in wrapped mode\;Bit 3: MACSEC\;other bits are reserved" access="RW" enum="TLS=0x1,IPSEC=0x2,AES=0x4,MACSEC=0x8" offset="0x0.0" size="0x0.8" />
	<field name="int_kek_auto_size" descr="Bitmask indicating the support for different Key sizes for device generated keys in INT_KEK objects. If set, INT_KEK can be created where key is generated by the device (auto_gen = 0x1) and the specific key_size:\;bit 0: SIZE_128\;bit 1: SIZE_256\;other bits are reserved" access="RW" offset="0x0.8" size="0x0.4" />
	<field name="sw_wrapped_dek_key_purpose" descr="When set, SW wrapped DEK should include the key_purpose inside the encrypted DEK" access="RW" offset="0x0.12" size="0x0.1" />
	<field name="large_mtu_tweak_64" descr="If set, large MTU tweak 64 is supported" access="RW" offset="0x0.15" size="0x0.1" />
	<field name="int_kek_manual_size" descr="Bitmask indicating the support for different Key sizes for SW provided keys in INT_KEK objects. If set, INT_KEK can be created where key is provided by SW (auto_gen = 0x0) and the specific key_size:\;bit 0: SIZE_128\;bit 1: SIZE_256\;other bits are reserved" access="RW" offset="0x0.16" size="0x0.4" />
	<field name="query_crypto_state" descr="If set, QUERY_CRYPTO_STATE command is supported" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="int_kek_auto" descr="If set, INT_KEK can be created where key is generated by the device (auto_gen = 0x1)" access="RW" offset="0x0.26" size="0x0.1" />
	<field name="int_kek_manual" descr="If set, INT_KEK can be created where key is provided by SW (auto_gen = 0x0)" access="RW" offset="0x0.27" size="0x0.1" />
	<field name="synchronize_dek" descr="If set, SYNC_CRYPTO command is required before modifying and reusing a previously used DEK." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="wrapped_crypto_going_to_commissioning" descr="When set to 1, the device receives an authenticated command to go back to crypto commissioning mode. This will happen after the next FW reset. \;Valid only when wrapped_crypto_operational=1. After FW reset, wrapped_crypto_operational will be unset to 0, and this bit will be unset to 0 as well." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="wrapped_crypto_operational" descr="If set to 1, it indicates that the crypto engines in wrapped import\;method are operational.\;If set to 0, SW should change it to operational mode. \;See Table  1904, &quot;CRYPTO_OPERATIONAL Register Layout,&quot; on page  2276." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="log_max_num_creds" descr="Log (base 2) of maximal number of Credentials supported\;" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="log_max_num_import_keks" descr="Log (base 2) of maximal number of Imported KEKs supported\;" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="log_max_num_deks" descr="Log (base 2) of maximal number of DEKs supported\;" access="RW" offset="0x4.16" size="0x0.5" />
	<field name="log_dek_max_alloc" descr="Log (base 2) of the maximum allocation of a single STC\;Object range" access="RW" offset="0x4.24" size="0x0.5" />
	<field name="num_nv_credentials" descr="Number of non-volatile credential slots out of the total credentials" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="num_nv_import_keks" descr="Number of non-volatile import_KEK slots out of the total import KEKs" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="failed_selftests" descr="Bitmap for selftests. If set, the respective test has failed.\;Depending on which tests have failed, the respective crypto capability may be turned off as a result\;0x1: test_aes_gcm- AES GCM test\;0x2: test_aes_ecb- AES ECB test\;0x4: test_aes_xts- AES XTS test\;0x8: test_hmac_sha- HMAC SHA test\;0x10: test_sha- SHA test" access="RW" enum="test_aes_gcm=0x1,test_aes_ecb=0x2,test_aes_xts=0x4,test_hmac_sha=0x8,test_sha=0x10" offset="0x8.16" size="0x0.16" />
	<field name="sw_wrapped_dek" descr="Bitmask indicating for which DEK purpose, DEKs wrapped by SW are supported.\;bit 1: TLS\;bit 2: IPSEC\;bit 3: AES_XTS\;bit 4: MACSEC - (internal)\;bit 5: GCM_mem2mem - (internal)\;bit 6: PSP\;other bits are reserved" access="RW" enum="TLS=0x2,IPSEC=0x4,AES_XTS=0x8,MACSEC=0x10,GCM_mem2mem=0x20,PSP=0x40" offset="0xC.0" size="0x0.16" />
	<field name="log_max_num_int_kek" descr="Log (base 2) of maximal number of Internal KEK objects supported" access="RW" offset="0xC.16" size="0x0.5" />
	<field name="log_dek_granularity" descr="Log (base 2) of the minimum allocation granularity of DEK\;Object range" access="RW" offset="0xC.24" size="0x0.5" />
	<field name="fips_module_name_selector" descr="0x0: NO_FIPS - not a FIPS module\;0x1: Nvidia_BlueField3_Datapath_Acceleration_Crypto" access="RW" enum="NO_FIPS=0x0,Nvidia_BlueField3_Datapath_Acceleration_Crypto=0x1" offset="0x10.0" size="0x4.0" />
	<field name="fips_module_version_major" descr="" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="fips_module_version_minor" descr="" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="log_crypto_mmo_max_size" descr="Log(Base 2) of the maximum crypto MMO operation size in Bytes. Value 0x0 indicates no limit on size." access="RW" offset="0x20.16" size="0x0.6" />
	<field name="crypto_mmo_gcm_auth_tag_96" descr="if set, Crypto MMO AES-GCM 96 bit authentication tag is supported." access="RW" offset="0x20.25" size="0x0.1" />
	<field name="crypto_mmo_gcm_auth_tag_128" descr="if set, Crypto MMO AES-GCM 128 bit authentication tag is supported." access="RW" offset="0x20.26" size="0x0.1" />
	<field name="crypto_mmo_aes_gcm_128_decrypt" descr="if set, Crypto MMO AES-GCM-128 decryption is supported." access="RW" offset="0x20.27" size="0x0.1" />
	<field name="crypto_mmo_aes_gcm_256_decrypt" descr="if set, Crypto MMO AES-GCM-256 decryption is supported." access="RW" offset="0x20.28" size="0x0.1" />
	<field name="crypto_mmo_aes_gcm_128_encrypt" descr="if set, Crypto MMO AES-GCM-128 encryption is supported." access="RW" offset="0x20.29" size="0x0.1" />
	<field name="crypto_mmo_aes_gcm_256_encrypt" descr="if set, Crypto MMO AES-GCM-256 encryption is supported." access="RW" offset="0x20.30" size="0x0.1" />
	<field name="crypto_mmo_qp" descr="if set, Crypto MMO WQE is supported for RC \;and DC QPs." access="RW" offset="0x20.31" size="0x0.1" />
</node>

<node name="debug_cap" descr="" size="0x44.0" >
	<field name="log_max_samples" descr="The maximum number of samples that can be stored on the device&apos;s sampling buffer is 2^ log_max_samples in counters unit (i.e. 100 will represent the ability to store 100 samples of single counter, 50 samples of 2 counters, etc)." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="log_min_resource_dump_eq" descr="Log(base 2) of the the recommended minimal size of eq to handle the resource_dump_event" access="RW" offset="0x0.16" size="0x0.5" />
	<field name="resource_dump" descr="If set, Resource_dump register is supported.\;See Table  1898, &quot;RESOURCE_DUMP Register Layout,&quot; on page  2271" access="RW" offset="0x0.22" size="0x0.1" />
	<field name="log_cr_dump_to_mem_size" descr="Log(base 2) of the size in granularity of 4KB to be allocated by host in order to accommodate cr_dump.\;0 means feature is not supported.\;See Table  1896, &quot;CORE_DUMP Register Layout,&quot; on page  2269" access="RW" offset="0x0.23" size="0x0.5" />
	<field name="core_dump_qp" descr="If set, Core dump of type of specific QP is supported.\;" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="core_dump_general" descr="If set, Core dump of type &quot;General&quot; is supported." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="log_min_sample_period" descr="The minimal sample period is 2^ log_min_smaple_period in device clocks. Clock rate of the device is reported by HCA_CAP.device_frequency_khz." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="diag_counter_tracer_dump" descr="If set, the device supports dumping the diagnostic counters reports into the tracer buffer." access="RW" offset="0x4.28" size="0x0.1" />
	<field name="health_mon_rx_activity" descr="If set, health monitoring for rx path activity is supported.\;See Table  30.5.1, &quot;RX Path Activity,&quot; on page  2147" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="repetitive" descr="Repetitive sampling mode is supported" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="single" descr="Single sampling mode is supported" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="diagnostic_counter" descr="List of counters supported. Number of counters reported by num_of_counters." subnode="diagnostic_cntr_layout" access="RW" high_bound="VARIABLE" low_bound="0" offset="0x40.0" size="0x4.0" />
</node>

<node name="device_emulation_cap" descr="" size="0x100.0" >
	<field name="max_emulated_devices" descr="Total number of emulated devices managed by the device emulation manager (physical functions devices).\;Information about these Devices can be reported by QUERY_EMULATED_FUNCTIONS_INFO. See Table 1577, &quot;QUERY_EMULATED_FUNCTIONS_INFO Input Structure Layout,&quot; on page 2036." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="db_table_handle" descr="When set, the db_table_handle field in the EMULATED_DEV_DB_CQ_MAPPING object is valid." access="RW" offset="0x0.17" size="0x0.1" />
	<field name="dynamic_vf_db_control" descr="When set, configuring dynamic_vf_db_control field in the NVME_DEVICE_EMULATION object (PF only) is supported." access="RW" offset="0x0.18" size="0x0.1" />
	<field name="nvme_emulated_dev_eq" descr="If set, explicit creation of Emulated Device EQs to be used for MSI-X resources is supported. (These resources are to be created on the emulation manager device). Otherwise, MSI-X resources are internally allocated during the creation of queue object" access="RW" offset="0x0.19" size="0x0.1" />
	<field name="nvme_db_cq_map_set_db_val" descr="If set, explicit mapping of Emulated Device doorbell to CQ supports setting the Doorbell value, as if a Doorbell was posted by the host function." access="RW" offset="0x0.20" size="0x0.1" />
	<field name="nvme_emulated_dev_db_cq_map" descr="If set, explicit mapping of Emulated Device doorbell to CQ is supported (for the emulation manager\;device) using EMULATED_DEV_DB_CQ_MAPPING Object. Otherwise, doorbell resources are internally allocated and mapped by the device." access="RW" offset="0x0.21" size="0x0.1" />
	<field name="nvme_emulation_object_event" descr="if set, NVME device emulation object supports triggering Object Change Event" access="RW" offset="0x0.22" size="0x0.1" />
	<field name="nvme_cq_interrupt_disabled" descr="If set, nvme_cq supports interrupt_disabled==1." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="log_max_nvme_offload_namespaces" descr="\;Log(base 2) of the maximum number of namesapces supported per emulation manager. This means the total number of namespaces that can be created across all NVMe emulated functions that belong to the same emulation manager. Relevant only for Command Capsule offload type.\;" access="RW" offset="0x0.24" size="0x0.5" />
	<field name="nvme_offload_type_command_capsule" descr="If set, offload type of Command Capsule is supported in Device Emulation QP to NVMe MAP Object, See Section 27.18.2, &quot;NVME SQ - NVME Emulation SQ Object&quot;, on page 1913." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="nvme_offload_type_SQE" descr="If set, offload type of SQE is supported in Device Emulation QP to NVMe MAP Object, See Section 27.18.2, &quot;NVME SQ - NVME Emulation SQ Object&quot;, on page 1913." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="registers_size" descr="Size of device emulation registers" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="log_max_nvme_offload_nsid" descr="Log(base 2) of the maximal nsid that can be assigned to a namespace src id.\;Relevant only for Command Capsult offload type. \;0 means limited only by log_max_nvme_offload_namespaces." access="RW" offset="0x4.16" size="0x0.5" />
	<field name="log_max_emulated_cq" descr="Log(base 2) of the maximum supported emulated CQs, assuming doorbell stride is 4B. For other values of doorbell stride the maximal CQ number should be re-calculated. If HCA_CAP.nvme_max_device_doorbell_range is not 0x0, this field should be ignored." access="RW" offset="0x8.0" size="0x0.5" />
	<field name="log_max_emulated_sq" descr="Log(base 2) of the maximum supported emulated SQs, assuming doorbell stride is 4B. For other values of doorbell stride the maximal SQ number should be re-calculated. If HCA_CAP.nvme_max_device_doorbell_range is not 0x0, this field should be ignored." access="RW" offset="0x8.8" size="0x0.5" />
	<field name="log_max_queue_depth" descr="Log (base 2) of maximum allowed nvme queue depth.\;0 means 1K." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="nvme_max_device_doorbell_range" descr="Maximal value supported for doorbell_range per NVME device, set in NVMe Device Emulation Object. Value given in bytes\;When 0x0, the value can be calculated by using log_max_emulated_sq and log_max_emulated_cq fields according to: \;8x(1&lt;&lt;max{log_max_emulated_sq, log_max_emulated_cq})" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="min_num_vf_dynamic_msix" descr="The minimum number of dynamic MSIXs that can be set for an NVMe emulated VF" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="max_num_vf_dynamic_msix" descr="The maximum number of dynamic MSIXs that can be set for an NVMe emulated VF" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="max_num_pf_msix" descr="The maximum number of MSIXs that can be set for an emulated PF." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="nvme_max_doorbell_range" descr="Maximal total doorbell range supported for all NVME emulated devices. Value given in bytes." access="RW" offset="0x18.0" size="0x4.0" />
	<field name="log_max_exp_bar_size" descr="Log (base 2) of the maximum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="log_min_exp_bar_size" descr="Log (base 2) of the minimum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="max_managed_emulated_hosts" descr="The maximal number of managed emulated hosts (PCI links) that can be managed by the device. This is a one based value and valid if HCA_CAP.host_number_ready is set." access="RW" offset="0x1C.16" size="0x0.4" />
	<field name="host_number_ready" descr="If set, host_number_valid and host_number fields are valid for both the QUERY_EMULATED_FUNCTIONS_INFO and HOTPLUG_DEVICE commands. Additionally, setting the corresponding device type in the op_mod field of the QUERY_MANAGED_EMULATED_HOSTS_INFO command is supported." access="RW" offset="0x1C.20" size="0x0.1" />
	<field name="always_armed_device_db" descr="When set, configuring always_armed_device_db field in the NVME_DEVICE_EMULATION object is supported." access="RW" offset="0x1C.27" size="0x0.1" />
	<field name="max_emulated_objects_per_vhca_id" descr="The maximum number of device emulated objects that can be created per single vhca_id. This is a zero based value." access="RW" offset="0x1C.28" size="0x0.4" />
</node>

<node name="device_mem_cap" descr="" size="0x100.0" >
	<field name="memic" descr="If set, MEMIC is supported. See Section 21.3, &quot;Memory Mapped to InterConnect (MEMIC)&quot;, on page 1688." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="log_max_memic_addr_alignment" descr="The maximum alignment of MEMIC address that can be required in MEMIC allocation is 64*2^log_max_memic_addr_alignment" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="memic_atomic_test_and_set" descr="Bitmask indicating which sizes for MEMIC atomic test-and-set are supported. Value of 0x0 atomic test-and-set is not supported.\;The field is available when the corresponding capability in DEVICE_MEMORY.memic_operations is set.\;\;Bit 0x0: size_1Byte\;Bit 0x1: size_2Byte\;Bit 0x2: size_4Byte\;Bit 0x3: size_8Byte\;Bit 0x4: size_16Byte" access="RW" enum="size_1Byte=0x1,size_2Byte=0x2,size_4Byte=0x4,size_8Byte=0x8,size_16Byte=0x10" offset="0x4.8" size="0x0.8" />
	<field name="log_min_memic_alloc_size" descr="Log (base 2) of the minimum allocation size of MEMIC in granularity of bytes." access="RW" offset="0x4.16" size="0x0.5" />
	<field name="memic_atomic_increment" descr="Bitmask indicating which sizes for MEMIC atomic increment are supported. Value of 0x0 means atomic increment is not supported.\;The field is available when the corresponding capability in DEVICE_MEMORY.memic_operations is set.\;\;Bit 0x0: size_1Byte\;Bit 0x1: size_2Byte\;Bit 0x2: size_4Byte\;Bit 0x3: size_8Byte\;Bit 0x4: size_16Byte" access="RW" enum="size_1Byte=0x1,size_2Byte=0x2,size_4Byte=0x4,size_8Byte=0x8,size_16Byte=0x10" offset="0x4.24" size="0x0.8" />
	<field name="memic_bar_start_addr" descr="Start address of MEMIC area on the BAR." subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="memic_bar_size" descr="Size of MEMIC area on the BAR starting from memic_bar_start_addr in a granularity of bytes." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="max_memic_size" descr="Maximum memic size supported in bytes." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="steering_sw_icm_start_address" descr="ICM base address reserved for SW managed steering, given in Bytes" subnode="uint64" access="RW" offset="0x18.0" size="0x8.0" />
	<field name="log_steering_sw_icm_size" descr="Log (base 2) of the ICM range reserved for SW managed steering, given in bytes." access="RW" offset="0x20.0" size="0x0.8" />
	<field name="log_sw_icm_alloc_granularity" descr="Log (base 2) of the minimum allocation granularity of SW ICM in granularity of bytes." access="RW" offset="0x20.8" size="0x0.6" />
	<field name="log_header_modify_sw_icm_size" descr="Log (base 2) of the ICM range reserved for SW managed Header Modify contexts, given in bytes." access="RW" offset="0x20.16" size="0x0.8" />
	<field name="must_not_use" descr="" access="RW" offset="0x20.24" size="0x0.8" />
	<field name="log_header_modify_pattern_sw_icm_size" descr="Log (base 2) of the ICM range reserved for SW managed Header Modify Pattern contexts, given in bytes." access="RW" offset="0x24.0" size="0x0.8" />
	<field name="log_indirect_encap_sw_icm_size" descr="Log (base 2) of the ICM range reserved for SW managed encap contexts, given in bytes. Value 0x0 indicates this feature is not supported." access="RW" offset="0x24.24" size="0x0.8" />
	<field name="header_modify_sw_icm_start_address" descr="ICM base address reserved for SW managed Header Modify contexts, given in Bytes" subnode="uint64" access="RW" offset="0x28.0" size="0x8.0" />
	<field name="header_modify_pattern_sw_icm_start_address" descr="ICM base address reserved for SW managed Header Modify Pattern contexts, given in Bytes" subnode="uint64" access="RW" offset="0x38.0" size="0x8.0" />
	<field name="memic_operations" descr="Bitmask indicating which MEMIC operations are supported by Read and Write operations on MEMIC. The operations are handled assuming the data in MEMIC is stored in Big endian notation and the operations are done in endianess of the host.\;\;Note: This field can be queried only after the host&apos;s endianness was set (e.g., using HOST_ENDIANNESS access register).\;\;0x0: MEMIC_ATOMIC_INCREMENT - supported by write operation.\;0x1: MEMIC_ATOMIC_TEST_AND_SET - supported by READ operation." access="RW" enum="MEMIC_ATOMIC_INCREMENT=0x0,MEMIC_ATOMIC_TEST_AND_SET=0x1" offset="0x40.0" size="0x4.0" />
	<field name="indirect_encap_sw_icm_start_address" descr="ICM base address reserved for SW managed encap contexts, given in Bytes" subnode="uint64" access="RW" offset="0x48.0" size="0x8.0" />
	<field name="indirect_encap_icm_base" descr="ICM base address for indirect encap data, given in Bytes.\;SW managed encap context pointers should be adjusted to be relative to this address, instead of indirect_encap_sw_icm_start_address" subnode="uint64" access="RW" offset="0x50.0" size="0x8.0" />
</node>

<node name="diagnostic_cntr_layout" descr="" size="0x4.0" >
	<field name="counter_id" descr="Diagnostic counter identifier." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="sync" descr="The counter might be used as Synced Start Diagnostics Counters" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="dpp_cap" descr="" size="0x100.0" >
	<field name="dpp_wire_protocol" descr="Bit mask indicates which DPP wire protocols are supported." subnode="uint64" access="RW" offset="0x0.0" size="0x8.0" />
	<field name="log_max_dpp_segment_size" descr="Log(base 2) of the maximum supported size of scattered data per packet in granularity of Bytes." access="RW" offset="0x8.0" size="0x0.5" />
	<field name="log_min_dpp_segment_size" descr="Log(base 2) of the minimum supported size of scattered data per packet in granularity of Bytes." access="RW" offset="0x8.8" size="0x0.5" />
	<field name="max_scatter_size" descr="Maximum scatter size." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="max_psn_size_supported" descr="The maximum number of bits in packet to represent PSN." access="RW" offset="0xC.0" size="0x0.8" />
	<field name="log_max_dpp_buffer_size" descr="Log(base 2) of the maximum supported buffer size of in granularity of Bytes." access="RW" offset="0xC.8" size="0x0.5" />
	<field name="dpp_max_scatter_offset" descr="The maximum value of dpp_scatter_offset in RQ context." access="RW" offset="0xC.16" size="0x0.8" />
</node>

<node name="e_switch_cap" descr="" size="0x100.0" >
	<field name="nic_vport_port_guid_modify" descr="If set, port_guid modify is supported by vport_group_manager to other vports in nic vport_context.\;Table  4572, &quot;MODIFY_NIC_VPORT_CONTEXT Input Structure Layout,&quot; on page  4633." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="nic_vport_node_guid_modify" descr="If set, node_guid modify is supported by vport_group_manager to other vports in nic vport_context.\;Table  4572, &quot;MODIFY_NIC_VPORT_CONTEXT Input Structure Layout,&quot; on page  4633." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="merged_eswitch" descr="If set, merged E-switch model is supported. Where a manager of an e-switch can set flow table rules on vports that belong to another e-switch that have same sw_owner_id. i.e. source_eswitch_owner_vhca_id and destination_eswitch_owner_vhca_id are valid." access="RO" offset="0x0.2" size="0x0.1" />
	<field name="counter_eswitch_affinity" descr="Defines which eSwitch should allocate the Flow Counter attached to a Flow the FDB table, when the Flow matches the source_vport and the eswitch_id (using the merge_eswitch feature).\;0x0: SOURCE_ESWITCH - The eSwitch matched in the eswitch_id.\;0x1: FLOW_ESWITCH - The eSwitch to which the Flow is added" access="RW" enum="SOURCE_ESWITCH=0x0,FLOW_ESWITCH=0x1" offset="0x0.3" size="0x0.1" />
	<field name="ecpf_vport_exists" descr="If set, the E-switch includes one more vport for Embedded CPU function (vport number 0xfffe)." access="RW" offset="0x0.4" size="0x0.1" />
	<field name="fdb_single_tir_destination" descr="If set, a single TIR can be used as a destination in FDB Flows." access="RW" offset="0x0.5" size="0x0.1" />
	<field name="esw_functions_changed" descr="If set, QUERY_HOST_NET_FUNCTIONS command and HOST_NET_FUNCTIONS_CHANGED event is supported." access="RW" offset="0x0.6" size="0x0.1" />
	<field name="match_uplink_other_esw" descr="If set, then match on uplink of other e-switch is supported." access="RW" offset="0x0.7" size="0x0.1" />
	<field name="esw_vport_state_max_tx_speed" descr="When set, indicates an eSwitch-Manager can set a vport&quot;s max_tx_speed via MODIFY_VPORT_STATE." access="RO" offset="0x0.20" size="0x0.1" />
	<field name="sw_network_metadata" descr="If set, then sw_network_metadata in NIC vport context is supported." access="RW" offset="0x0.21" size="0x0.1" />
	<field name="root_ft_on_other_esw" descr="If set, the device supports using a root flow table of another e-Switch by setting table_eswitch_owner_vhca_id_valid and table_eswitch_owner_vhca_id in SET_FLOW_TABLE_ROOT command. (Supported for FDb and Ingress Flow table only)" access="RW" offset="0x0.22" size="0x0.1" />
	<field name="esw_uplink_ingress_acl" descr="If set, the device supports INGRESS ACL for the uplink vport." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="esw_shared_ingress_acl" descr="If set, the device supports sharing an INGRESS ACL root flow table among multiple e-switch vports on same e-switch, by setting the table_of_other_vport and table_vport_num in SET_FLOW_TABLE_ROOT command." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="vport_cvlan_insert_always" descr="If set, cvlan insert_always mode in vport_cvlan_insert is supported in e-switch. See Section  8.6, &quot;Esw_Vport Context - E-switch Virtual Port Context,&quot; on page  569." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="vport_cvlan_insert_overwrite" descr="If set, cvlan insertion for transmitted packets or overwrite when it does not exist is supported in e-switch. See Section  8.6, &quot;Esw_Vport Context - E-switch Virtual Port Context,&quot; on page  569." access="RW" offset="0x0.27" size="0x0.1" />
	<field name="vport_cvlan_insert_if_not_exist" descr="If set, cvlan insertion for transmitted packets if it does not exist is supported in e-switch. See Section  8.6, &quot;Esw_Vport Context - E-switch Virtual Port Context,&quot; on page  569." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="vport_svlan_insert" descr="If set, svlan insertion for transmitted packets is supported in e-switch. See Section  8.6, &quot;Esw_Vport Context - E-switch Virtual Port Context,&quot; on page  569." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="vport_cvlan_strip" descr="If set, cvlan strip for received packets is supported in e-switch. See Section  8.6, &quot;Esw_Vport Context - E-switch Virtual Port Context,&quot; on page  569." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="vport_svlan_strip" descr="If set, svlan strip for received packets is supported in e-switch. See Section  8.6, &quot;Esw_Vport Context - E-switch Virtual Port Context,&quot; on page  569." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="max_encap_header_size" descr="The maximum size of the encapsulation header supported by ALLOC_PACKET_REFORMAT_CONTEXT for NIC related flow tables" access="RW" offset="0x4.0" size="0x0.10" />
	<field name="log_max_packet_reformat_context" descr="Log (base 2) of the maximum packet reformat contexts that can be created by ALLOC_PACKET_REFORMAT_CONTEXT." access="RW" offset="0x4.16" size="0x0.5" />
	<field name="log_max_fdb_encap_uplink" descr="Log (base 2) of the number of supported packet reformat Contexts for FDB Flow Table Type which can be created to be attached to an Uplink destination. Value 0x0 indicates this feature is not supported. See Section  8.18.4.6, &quot;Allocating a Packet Reformat Context,&quot; on page  733" access="RW" offset="0x4.24" size="0x0.5" />
	<field name="encap_general_header" descr="If set, encapsulation of General header is supported.\;Supporting general header encapsulation does not necessarily mean that offload and parsing is also supported. So SW need to make sure the encapsulated protocol can be parsed add offloaded is needed." access="RW" offset="0x4.29" size="0x0.1" />
	<field name="nvgre_encap_decap" descr="If set, encapsulation and decapsulation of NVGRE header is supported." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="vxlan_encap_decap" descr="If set, encapsulation and decapsulation of VXLAN header is supported." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="esw_sf_base_id" descr="Base sub-function identifier on eswitch that also define the vport number on eswitch.\;" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="log_max_esw_sf" descr="Log(base 2) of maximum number of Sub-functions supported on eswitch (SFs on both PF and ECPF).." access="RW" offset="0x8.16" size="0x0.5" />
	<field name="esw_manager_vport_number" descr="Indicates the vport number of the Eswitch manager.\;Valid only when esw_manager_vport_number_valid==1.\;" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="esw_manager_vport_number_valid" descr="If set, esw_manager_vport_number capability is valid." access="RW" offset="0xC.31" size="0x0.1" />
</node>

<node name="embedded_program_capabilities" descr="" size="0x800.0" >
	<field name="e_prog_program_type" descr="Bitmask of embedded program types supported by the device for the EMBEDDED_PROGRAM object. Each bit represents the corresponding program_type value. Set bit indicates the type is supported." offset="0x0.0" size="0x0.8" />
	<field name="log_max_dpa_threads_per_process" descr="Log(base 2) of the maximum number of DPA_THREADS per DPA_PROCESS." offset="0x0.8" size="0x0.5" />
	<field name="dpa_thread_interrupt_id_32b" descr="If set, interrupt_id_32b is supported and should be used in DPA_THREAD, instead of interrupt_id field" offset="0x0.13" size="0x0.1" />
	<field name="dpa_process_attr" descr="If set, DPA_PROCESS attributes are supported" offset="0x0.14" size="0x0.1" />
	<field name="dpa_auth_supported" descr="When set, device supports authentication of the DPA binary." offset="0x0.15" size="0x0.1" />
	<field name="log_max_dpa_mem" descr="Log(base 2) of the maximum number of DPA_MEM objects." offset="0x0.16" size="0x0.5" />
	<field name="e_prog_error_message" descr="If set embeddded program loading failure supports extended debug information in err_buffer_mkey" offset="0x0.21" size="0x0.1" />
	<field name="process_win_secondary" descr="When set DPA process may be assigned with a secondary DPA window" offset="0x0.22" size="0x0.1" />
	<field name="process_win_primary" descr="When set DPA process may be assigned with a primary DPA window" offset="0x0.23" size="0x0.1" />
	<field name="log_max_num_dpa_mem_blocks" descr="Log(base 2) of the maximum number of DPA MEM block supported per process for dpa_mem_type DPA_HEAP." offset="0x0.24" size="0x0.5" />
	<field name="thread_affinity_eug" descr="When set, DPA thread supports EU Affinity EUG" offset="0x0.30" size="0x0.1" />
	<field name="thread_affinity_single_eu" descr="When set, DPA thread supports EU Affinity SINGLE_EU" offset="0x0.31" size="0x0.1" />
	<field name="dpa_mem_block_size" descr="Indicates the size of DPA_MEM block in bytes for dpa_mem_type DPA_HEAP" offset="0x4.0" size="0x4.0" />
	<field name="max_num_dpa_thread_per_group" descr="Maximal number of DPA threads affined to the same DPA EUG" offset="0x8.0" size="0x0.16" />
	<field name="log_max_dpa_outbox" descr="Log(base 2) of the maximum number of DPA_OUTBOX objects." offset="0x8.16" size="0x0.5" />
	<field name="log_max_dpa_threads" descr="Log(base 2) of the maximum number of DPA_THREAD Objects." offset="0x8.24" size="0x0.5" />
	<field name="log_max_dpa_window" descr="Log(base 2) of the maximum number of DPA_WINDOW Objects." offset="0xC.24" size="0x0.5" />
	<field name="stateful_thread_context_buffer_size" descr="The size of the buffer user should allocate in DPA memory to store stateful thread context. given in bytes" offset="0x10.0" size="0x0.16" />
	<field name="dpa_process_log_max_dpa_uar" descr="Maximum amount of DPA UARs process can create\;" offset="0x10.16" size="0x0.3" />
	<field name="dpa_os_api_version_supported" descr="If set, DPA_PROCESS dpa_os_api_version field and \;HCA_CAP.dpa_os_api_version and HCA_CAP.dpa_os_api_version_min are valid" offset="0x10.22" size="0x0.1" />
	<field name="user_debugger_supported" descr="When set, user debugging is supported" offset="0x10.23" size="0x0.1" />
	<field name="dpa_coredump_type" descr="Bitmask indicating supported DPA coredump types. See coredump_type field in Table  4419, &quot;DPA_PROCESS_COREDUMP Input Structure Field Descriptions,&quot; on page  4565" offset="0x10.24" size="0x0.8" />
	<field name="max_dpa_processes" descr="Maximal number of DPA_PROCESS objects." offset="0x14.0" size="0x0.12" />
	<field name="dpa_mem_crash_dump" descr="When set, DPA memory dump in case of process crash is supported." offset="0x14.12" size="0x0.1" />
	<field name="dpa_platform_version" descr="DPA platform version.\;0x0000: DPA_RESRVED\;0x0100: DPA_PLATFORM_V10\;0x0101: DPA_PLATFORM_V11\;0x0200: DPA_PLATFORM_V20\;0x0300: DPA_PLATFORM_V30\;0x0301: DPA_PLATFORM_V31\;0x0400: DPA_PLATFORM_V40\;0xFFFF: DPA_UNSUPPORTED" enum="DPA_RESRVED=0x0,DPA_PLATFORM_V10=0x100,DPA_PLATFORM_V11=0x101,DPA_PLATFORM_V20=0x200,DPA_PLATFORM_V30=0x300,DPA_PLATFORM_V31=0x301,DPA_PLATFORM_V40=0x400,DPA_UNSUPPORTED=0xffff" offset="0x14.16" size="0x0.16" />
	<field name="dpa_os_api_version" descr="DPA API version currently running, and the maximum version of DPA that is supported.\;Valid if dpa_os_api_version_supported is set" offset="0x18.0" size="0x4.0" />
	<field name="dpa_os_api_version_min" descr="The minimum version of DPA that is supported.\;Valid if dpa_os_api_version_supported is set" offset="0x1C.0" size="0x4.0" />
	<field name="e_prog_error_message_size_min" descr="Minimum size of memory buffer allocated for embedded program loading failure debug information in err_buffer_mkey, given in bytes" offset="0x20.0" size="0x4.0" />
	<field name="dpa_thread_cont_run_time_max" descr="Maximum continuous execution time allowed for a DPA thread on a DPA EU before it must give-up the EU, given in seconds." offset="0x24.0" size="0x0.16" />
	<field name="dpa_thread_eq_type" descr="Bitmap indicating supported values in DPA_THREAD.eq_type. Set bit indicates the corresponding EQ Type is supported. See EQ Type enumeration in DPA Thread Object." offset="0x24.28" size="0x0.4" />
	<field name="dpa_eq_num_max" descr="Maximal number of DPA_EQ objects" offset="0x28.0" size="0x4.0" />
	<field name="dpa_mem_vhca_block_size" descr="Indicates the size of DPA_MEM block in bytes for dpa_mem_type DPA_MEM_VHCA" offset="0x2C.0" size="0x4.0" />
	<field name="dpa_mem_vhca_num_max" descr="Maximal number of DPA_MEM_VHCA objects supported" offset="0x30.0" size="0x0.16" />
	<field name="dpa_mem_vhca_block_num_max" descr="Maximal number of DPA MEM block supported per process for dpa_mem_type DPA_MEM_VHCA" offset="0x30.16" size="0x0.16" />
	<field name="e_prog_binary_size_max" descr="Maximum size of pre-compiled binary which can be uploaded to EMBEDDED_PROGRAM given in bytes" subnode="uint64" offset="0x38.0" size="0x8.0" />
	<field name="event_bitmask_63_0" descr="Bits[63:0] of a bitmap indicating which event types can be mapped to DPA_EQ. Set bit indicates the respective event type can be mapped. Event types are defined in Table  317, &quot;Event Type and Coding,&quot; on page  830" subnode="uint64" offset="0x40.0" size="0x8.0" />
	<field name="event_bitmask_127_64" descr="Bits[127:64] of a bitmap indicating which event types can be mapped to DPA_EQ. Set bit indicates the respective event type can be mapped. Event types are defined in Table  317, &quot;Event Type and Coding,&quot; on page  830" subnode="uint64" offset="0x48.0" size="0x8.0" />
	<field name="event_bitmask_191_128" descr="Bits[191:128] of a bitmap indicating which event types can be mapped to DPA_EQ. Set bit indicates the respective event type can be mapped. Event types are defined in Table  317, &quot;Event Type and Coding,&quot; on page  830" subnode="uint64" offset="0x50.0" size="0x8.0" />
	<field name="event_bitmask_255_192" descr="Bits[255:192] of a bitmap indicating which event types can be mapped to DPA_EQ. Set bit indicates the respective event type can be mapped. Event types are defined in Table  317, &quot;Event Type and Coding,&quot; on page  830" subnode="uint64" offset="0x58.0" size="0x8.0" />
	<field name="paso_handler_error_message" descr="If set, PASO_HANDLER creation supports extended error message" offset="0x100.29" size="0x0.1" />
	<field name="paso_handler_auth" descr="If set, authentication of a PASO binary is supported." offset="0x100.30" size="0x0.1" />
	<field name="paso" descr="If set, PASO ASO is supported" offset="0x100.31" size="0x0.1" />
	<field name="paso_platform_version" descr="PASO Platform version.\;0x0000: PASO_RESERVED\;0x0400: PASO_PLATFORM_V10\;0xFFFF: PASO_UNSUPPORTED" enum="PASO_RESERVED=0x0,PASO_PLATFORM_V10=0x400,PASO_UNSUPPORTED=0xffff" offset="0x104.16" size="0x0.16" />
	<field name="paso_input_registers" descr="Bitmap indicating metadata C register pairs supported as input for PASO_HANDLER. Set bit indicates the pair is supported. \;Bit definition correlates to aso_return_reg_pair in Table  446, &quot;IPSEC_OFFLOAD Object Fields,&quot; on page  926" offset="0x108.0" size="0x4.0" />
	<field name="paso_output_registers" descr="Bitmap indicating metadata C register pairs supported as output for PASO_HANDLER. Set bit indicates the pair is supported. \;Bit definition correlates to aso_return_reg_pair in Table  446, &quot;IPSEC_OFFLOAD Object Fields,&quot; on page  926" offset="0x10C.0" size="0x4.0" />
	<field name="paso_handler_num_max" descr="Maximum PASO_HANDLER objects supported." offset="0x140.16" size="0x0.16" />
	<field name="paso_handler_error_message_size_min" descr="Minimum buffer size required for the PASO_HANDLER error messages buffer, given in bytes." offset="0x144.0" size="0x4.0" />
	<field name="paso_state_num_log_max" descr="Log (base 2) of maximum PASO_STATE objects supported." offset="0x148.0" size="0x0.6" />
	<field name="paso_state_alloc_log_max" descr="Log (base 2) of maximum allocation range for the PASO_STATE object." offset="0x148.8" size="0x0.6" />
	<field name="paso_state_log_granularity" descr="Log (base 2) of minimum allocation granularity for the PASO_STATE object." offset="0x148.16" size="0x0.6" />
	<field name="paso_handler_binary_size_log_max" descr="Log (base 2) of the maximum PASO_HANDLER binary size, given in KB." offset="0x148.24" size="0x0.6" />
</node>

<node name="event_capabilities" descr="" size="0x100.0" >
	<field name="user_affiliated_events_63_0" descr="Event Bitmask indicates the supported affiliated events. set bit indicates the corresponding affiliated event_type is supported.\;Bit 0x1:Path_Migrated_Succeeded\;Bit 0x02:Communication_Established\;Bit 0x03:Send_Queue_Drained\;Bit 0x04:CQ_Error\;Bit 0x05:Local_WQ_Catastrophic_Error\;Bit 0x07:Path_Migration_Failed\;Bit 0x10:Invalid_Request_Local_WQ_Error\;Bit 0x11:Local_Access_Violation_WQ_Error\;Bit 0x12:Local_SRQ_Catastrophic_Error\;Bit 0x13:Last_WQE_Reached\;Bit 0x14:SRQ_Limit\;Bit 0x18:XRQ_ERROR\;Bit 0x1C:DCT_All_Connections_Closed\;Bit 0x1D: DCT_Access_Key_Violation\;Bit 0x27: OBJECT_CHANGE_EVENT" subnode="uint64" access="RW" enum="Path_Migrated_Succeeded=0x2,Communication_Established=0x4,Send_Queue_Drained=0x8,CQ_Error=0x10,Local_WQ_Catastrophic_Error=0x20,Path_Migration_Failed=0x80,Invalid_Request_Local_WQ_Error=0x10000,Local_Access_Violation_WQ_Error=0x20000,Local_SRQ_Catastrophic_Error=0x40000,Last_WQE_Reached=0x80000,SRQ_Limit=0x100000,XRQ_ERROR=0x1000000,DCT_All_Connections_Closed=0x10000000,DCT_Access_Key_Violation=0x20000000,OBJECT_CHANGE_EVENT=0x80" offset="0x0.0" size="0x8.0" />
	<field name="user_affiliated_events_127_64" descr="" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="user_affiliated_events_191_128" descr="" subnode="uint64" access="RW" offset="0x10.0" size="0x8.0" />
	<field name="user_affiliated_events_255_192" descr="" subnode="uint64" access="RW" offset="0x18.0" size="0x8.0" />
	<field name="user_unaffiliated_events_63_0" descr="Event Bitmask indicates the supported user unaffiliated events. i.e. bit x indicates event_type=x is supported and unaffiliated.\;\;Bit 0x09: Port_State_Change\;Bit 0x0D: Nic_Vport_Change\;Bit 0x0E: HOST_NET_FUNCTIONS_CHANGED\;Bit 0x16: Port_Module_Event\;Bit 0x17: Temp_Warning_Event\;Bit 0x25: PPS_Event\;Bit 0x22: General_Notification_Event" subnode="uint64" access="RW" enum="Port_State_Change=0x200,Nic_Vport_Change=0x2000,HOST_NET_FUNCTIONS_CHANGED=0x4000,Port_Module_Event=0x400000,Temp_Warning_Event=0x800000,PPS_Event=0x20,General_Notification_Event=0x4" offset="0x20.0" size="0x8.0" />
	<field name="user_unaffiliated_events_127_64" descr="" subnode="uint64" access="RW" offset="0x28.0" size="0x8.0" />
	<field name="user_unaffiliated_events_191_128" descr="" subnode="uint64" access="RW" offset="0x30.0" size="0x8.0" />
	<field name="user_unaffiliated_events_255_192" descr="" subnode="uint64" access="RW" offset="0x38.0" size="0x8.0" />
	<field name="lightweight_eq_event_63_0" descr="Bits[63:0] of a bitmask, each bit indicates whether corresponding event type is supported by Lightweight EQ. See encoding in Table  317, &quot;Event Type and Coding,&quot; on page  830" subnode="uint64" access="RW" offset="0x40.0" size="0x8.0" />
	<field name="lightweight_eq_event_127_64" descr="Bits[127:64] of a bitmask, each bit indicates whether corresponding event type is supported by Lightweight EQ" subnode="uint64" access="RW" offset="0x48.0" size="0x8.0" />
	<field name="lightweight_eq_event_191_128" descr="Bits[191:128] of a bitmask, each bit indicates whether corresponding event type is supported by Lightweight EQ" subnode="uint64" access="RW" offset="0x50.0" size="0x8.0" />
	<field name="lightweight_eq_event_255_192" descr="Bits[255:192] of a bitmask, each bit indicates whether corresponding event type is supported by Lightweight EQ" subnode="uint64" access="RW" offset="0x58.0" size="0x8.0" />
</node>

<node name="flow_table_eswitch_cap" descr="" size="0x1000.0" >
	<field name="fdb_flow_counter_en" descr="Describes the limitations under which Flow Counters are supported in the FDB Flow Table beside extended_fdb_flow_counter_en. See Section  8.18.5.5, &quot;E-Switch Forwarding Data Base (FDB),&quot; on page  744." access="RW" offset="0x0.0" size="0x0.2" />
	<field name="ingress_acl_forward_to_vport" descr="If set, the Ingress ACL table supports the Forward action to another VPort" access="RW" offset="0x0.2" size="0x0.1" />
	<field name="fdb_multi_path_to_table" descr="If set, the FDB table supports the Forward action with a destination list that includes a Flow Table" access="RW" offset="0x0.3" size="0x0.1" />
	<field name="egress_acl_forward_to_vport" descr="When set, the Egress ACL table supports the Forward action to another VPort." access="RW" offset="0x0.4" size="0x0.1" />
	<field name="multi_fdb_encap" descr="If set, a Flow Table with enabled Reformat/decapsulate actions may be created when not all VFs are down, if another table with these actions enabled already exists." access="RW" offset="0x0.5" size="0x0.1" />
	<field name="extended_fdb_flow_counter_en" descr="Describes the limitations under which Flow Counters are supported in the FDB Flow Table besides extended_fdb_flow_counter_en. See Section  8.18.5.5, &quot;E-Switch Forwarding Data Base (FDB),&quot; on page  744." access="RW" offset="0x0.6" size="0x0.1" />
	<field name="ingress_acl_forward_to_vport_ingress" descr="when set, Ingress ACL FLow Table Entry may use VPORT_INGRESS as a destination to forward the packet to the Ingress ACL Flow Table of a different Vport.\;The ingress ACL of the eswitch manager cannot be a destination." access="RW" offset="0x0.7" size="0x0.1" />
	<field name="flow_source" descr="When set, the flow_source field of in the Flow Context can be used to indicate the known origin of packets matching this Flow." access="RW" offset="0x0.8" size="0x0.1" />
	<field name="esw_fdb_ipv4_ttl_modify" descr="When set, the device supports modifying the TTL even for Flows forwarding packets from uplink to non-uplink vports." access="RW" offset="0x0.9" size="0x0.1" />
	<field name="esw_fdb_modify_header_fwd_to_table" descr="When set, FDB table supports Modify Header action and Forward to Flow Table action in the same Flow." access="RW" offset="0x0.10" size="0x0.1" />
	<field name="ingress_acl_flow_counter_for_drop_actions" descr="If set, Ingress ACL Flow Table type may include a Flow Counter for flow with Drop actions." access="RW" offset="0x0.11" size="0x0.1" />
	<field name="ingress_acl_forward_to_uplink" descr="When set, the Ingress ACL table supports the Forward action to the Uplink Vport" access="RW" offset="0x0.12" size="0x0.1" />
	<field name="fdb_multi_path_any_table" descr="If set, the FDB table supports the Forward action with a destination list that includes any number of Flow Tables" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="vport_direction" descr="When set, Vports direction may be modified using MODIFY_VPORT_STATE." access="RW" offset="0x0.14" size="0x0.1" />
	<field name="fdb_dynamic_tunnel" descr="When set, it is no longer required that reformat_en or decap_en for FDB Flow Tables will be set only while all VFs are down." access="RW" offset="0x0.15" size="0x0.1" />
	<field name="fdb_multi_path_any_vport" descr="When set, Multiple processing paths are supported for any combination of multiple VPorts" access="RW" offset="0x0.16" size="0x0.1" />
	<field name="fdb_multi_path_any_table_limit_regc" descr="When set, the FDB table supports the Forward action with a destination list that includes any number of Flow Tables.\;The metadata registers maintained after matching such Flow are limited to Register C0 only.\;If fdb_multi_path_any_table is set, the metadata limitation is removed." access="RW" offset="0x0.17" size="0x0.1" />
	<field name="fdb_uplink_hairpin" descr="When set, the FDB table supports forwarding a packet back to the uplink it arrived from (hairpin)" access="RO" offset="0x0.18" size="0x0.1" />
	<field name="fdb_to_vport_reg_c_id" descr="Bit map per register_c ID indicating whether this register can be used to pass metadata to Vport Rx Flow Table. The ESW VPORT Context indicates whether this feature is supported and which Registers to pass. Set bit means this register is supported. \;Bit 0: REG_C_0 \;Bit 1: REG_C_1\;Bit 2: REG_C_2 \;Bit 3: REG_C_3 \;Bit 4: REG_C_4 \;Bit 5: REG_C_5 \;Bit 6: REG_C_6 \;Bit 7: REG_C_7" access="RW" enum="REG_C_0=0x1,REG_C_1=0x2,REG_C_2=0x4,REG_C_3=0x8,REG_C_4=0x10,REG_C_5=0x20,REG_C_6=0x40,REG_C_7=0x80" offset="0x0.24" size="0x0.8" />
	<field name="flow_table_properties_nic_esw_fdb" descr="Capabilities and properties of E-Switch FDB Flow Tables" subnode="flow_table_prop_layout" access="RW" offset="0x40.0" size="0x40.0" />
	<field name="flow_table_properties_esw_acl_ingress" descr="Capabilities and properties of E-Switch Ingress ACL Flow Tables" subnode="flow_table_prop_layout" access="RW" offset="0x80.0" size="0x40.0" />
	<field name="flow_table_properties_esw_acl_egress" descr="Capabilities and properties of E-Switch Egress ACL Flow Tables" subnode="flow_table_prop_layout" access="RW" offset="0xC0.0" size="0x40.0" />
	<field name="header_modify_esw_fdb" descr="Header modify capabilities of E-Switch FDB Flow Tables" subnode="header_modify_cap_properties" access="RW" offset="0x100.0" size="0x80.0" />
	<field name="header_modify_esw_acl_ingress" descr="Header modify capabilities of E-Switch Ingress ACL Flow" subnode="header_modify_cap_properties" access="RW" offset="0x180.0" size="0x80.0" />
	<field name="header_modify_esw_acl_egress" descr="Header modify capabilities of E-Switch Egress ACL Flow" subnode="header_modify_cap_properties" access="RW" offset="0x200.0" size="0x80.0" />
	<field name="ft_field_support_2_esw_fdb" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x280.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_esw_fdb" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x290.0" size="0x10.0" />
	<field name="ft_field_support_2_esw_acl_ingress" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x2A0.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_esw_acl_ingress" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x2B0.0" size="0x10.0" />
	<field name="ft_field_support_2_esw_acl_egress" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x2C0.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_esw_acl_egress" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x2D0.0" size="0x10.0" />
	<field name="sw_steering_fdb_action_drop_icm_address_rx" descr="ICM address in FDB Rx steering domain performing a Drop action. valid only if FDB table supports SW owner, and the value is non-zero" subnode="uint64" access="RW" offset="0x300.0" size="0x8.0" />
	<field name="sw_steering_fdb_action_drop_icm_address_tx" descr="ICM address in FDB Tx steering domain performing a Drop action. valid only if FDB table supports SW owner, and the value is non-zero" subnode="uint64" access="RW" offset="0x308.0" size="0x8.0" />
	<field name="sw_steering_uplink_icm_address_rx" descr="ICM address in FDB Rx steering domain sending the packet to the Uplink. valid only if FDB table supports SW owner, and the value is non-zero" subnode="uint64" access="RW" offset="0x310.0" size="0x8.0" />
	<field name="sw_steering_uplink_icm_address_tx" descr="ICM address in FDB Tx steering domain sending the packet to the Uplink. valid only if FDB table supports SW owner, and the value is non-zero" subnode="uint64" access="RW" offset="0x318.0" size="0x8.0" />
</node>

<node name="flow_table_fields_supported" descr="" size="0x10.0" >
	<field name="source_eswitch_port" descr="" offset="0x0.0" size="0x0.1" />
	<field name="source_vhca_port" descr="" offset="0x0.1" size="0x0.1" />
	<field name="outer_geneve_opt_len" descr="" offset="0x0.2" size="0x0.1" />
	<field name="outer_geneve_protocol_type" descr="" offset="0x0.3" size="0x0.1" />
	<field name="outer_geneve_oam" descr="" offset="0x0.4" size="0x0.1" />
	<field name="outer_geneve_vni" descr="" offset="0x0.5" size="0x0.1" />
	<field name="outer_vxlan_vni" descr="" offset="0x0.6" size="0x0.1" />
	<field name="outer_gre_key" descr="" offset="0x0.7" size="0x0.1" />
	<field name="outer_gre_protocol" descr="" offset="0x0.8" size="0x0.1" />
	<field name="outer_tcp_flags" descr="" offset="0x0.9" size="0x0.1" />
	<field name="outer_tcp_dport" descr="" offset="0x0.10" size="0x0.1" />
	<field name="outer_tcp_sport" descr="" offset="0x0.11" size="0x0.1" />
	<field name="outer_udp_dport" descr="" offset="0x0.12" size="0x0.1" />
	<field name="outer_udp_sport" descr="" offset="0x0.13" size="0x0.1" />
	<field name="outer_ip_dscp" descr="" offset="0x0.14" size="0x0.1" />
	<field name="outer_ip_ecn" descr="" offset="0x0.15" size="0x0.1" />
	<field name="outer_ip_protocol" descr="" offset="0x0.16" size="0x0.1" />
	<field name="outer_frag" descr="" offset="0x0.17" size="0x0.1" />
	<field name="outer_dip" descr="" offset="0x0.18" size="0x0.1" />
	<field name="outer_sip" descr="" offset="0x0.19" size="0x0.1" />
	<field name="outer_ipv6_flow_label" descr="" offset="0x0.20" size="0x0.1" />
	<field name="outer_second_vid" descr="" offset="0x0.21" size="0x0.1" />
	<field name="outer_second_cfi" descr="Second outer VLAN.cfi/dei" offset="0x0.22" size="0x0.1" />
	<field name="outer_second_prio" descr="Second outer VLAN.pcp" offset="0x0.23" size="0x0.1" />
	<field name="outer_ipv4_ttl" descr="" offset="0x0.24" size="0x0.1" />
	<field name="outer_first_vid" descr="" offset="0x0.25" size="0x0.1" />
	<field name="outer_first_cfi" descr="First outer VLAN.cfi/dei" offset="0x0.26" size="0x0.1" />
	<field name="outer_first_prio" descr="First outer VLAN.pcp" offset="0x0.27" size="0x0.1" />
	<field name="outer_ip_version" descr="" offset="0x0.28" size="0x0.1" />
	<field name="outer_ether_type" descr="" offset="0x0.29" size="0x0.1" />
	<field name="outer_smac" descr="" offset="0x0.30" size="0x0.1" />
	<field name="outer_dmac" descr="" offset="0x0.31" size="0x0.1" />
	<field name="metadata_reg_a" descr="If set, metadata_reg_a match is supported in flow table.\;Number of bits supported in this field is reported in Flow Table Properties, See Table  3521, &quot;Flow Table Properties Layout,&quot; on page  4090." offset="0x4.0" size="0x0.1" />
	<field name="metadata_reg_b" descr="If set, metadata_reg_b match is supported in flow table.\;Number of bits supported in this field is reported in Flow Table Properties, See Table  3521, &quot;Flow Table Properties Layout,&quot; on page  4090." offset="0x4.1" size="0x0.1" />
	<field name="outer_first_mpls_over_gre_cw" descr="" offset="0x4.2" size="0x0.1" />
	<field name="inner_tcp_ack_num" descr="" offset="0x4.3" size="0x0.1" />
	<field name="outer_tcp_ack_num" descr="" offset="0x4.4" size="0x0.1" />
	<field name="outer_first_mpls_over_udp_cw" descr="" offset="0x4.5" size="0x0.1" />
	<field name="prog_sample_field" descr="" offset="0x4.6" size="0x0.1" />
	<field name="inner_tcp_seq_num" descr="" offset="0x4.7" size="0x0.1" />
	<field name="outer_tcp_seq_num" descr="" offset="0x4.8" size="0x0.1" />
	<field name="inner_tcp_flags" descr="" offset="0x4.9" size="0x0.1" />
	<field name="inner_tcp_dport" descr="" offset="0x4.10" size="0x0.1" />
	<field name="inner_tcp_sport" descr="" offset="0x4.11" size="0x0.1" />
	<field name="inner_udp_dport" descr="" offset="0x4.12" size="0x0.1" />
	<field name="inner_udp_sport" descr="" offset="0x4.13" size="0x0.1" />
	<field name="inner_ip_dscp" descr="" offset="0x4.14" size="0x0.1" />
	<field name="inner_ip_ecn" descr="" offset="0x4.15" size="0x0.1" />
	<field name="inner_ip_protocol" descr="" offset="0x4.16" size="0x0.1" />
	<field name="inner_frag" descr="" offset="0x4.17" size="0x0.1" />
	<field name="inner_dip" descr="" offset="0x4.18" size="0x0.1" />
	<field name="inner_sip" descr="" offset="0x4.19" size="0x0.1" />
	<field name="inner_ipv6_flow_label" descr="" offset="0x4.20" size="0x0.1" />
	<field name="inner_second_vid" descr="" offset="0x4.21" size="0x0.1" />
	<field name="inner_second_cfi" descr="Second inner VLAN.cfi/dei" offset="0x4.22" size="0x0.1" />
	<field name="inner_second_prio" descr="Second inner VLAN.pcp" offset="0x4.23" size="0x0.1" />
	<field name="inner_ipv4_ttl" descr="" offset="0x4.24" size="0x0.1" />
	<field name="inner_first_vid" descr="" offset="0x4.25" size="0x0.1" />
	<field name="inner_first_cfi" descr="First inner VLAN.cfi/dei" offset="0x4.26" size="0x0.1" />
	<field name="inner_first_prio" descr="First inner VLAN.pcp" offset="0x4.27" size="0x0.1" />
	<field name="inner_ip_version" descr="" offset="0x4.28" size="0x0.1" />
	<field name="inner_ether_type" descr="" offset="0x4.29" size="0x0.1" />
	<field name="inner_smac" descr="" offset="0x4.30" size="0x0.1" />
	<field name="inner_dmac" descr="" offset="0x4.31" size="0x0.1" />
	<field name="source_sqn" descr="" offset="0x8.0" size="0x0.1" />
	<field name="outer_second_svlan" descr="Outer second VLAN supports s-vlan in addition to c-vlan" offset="0x8.1" size="0x0.1" />
	<field name="outer_first_svlan" descr="Outer first VLAN supports s-vlan in addition to c-vlan" offset="0x8.2" size="0x0.1" />
	<field name="inner_second_svlan" descr="Inner second VLAN supports s-vlan in addition to c-vlan" offset="0x8.3" size="0x0.1" />
	<field name="inner_first_svlan" descr="Inner first VLAN supports s-vlan in addition to c-vlan" offset="0x8.4" size="0x0.1" />
	<field name="bth_dst_qp" descr="If set, Destination QP in BTH header is supported." offset="0x8.5" size="0x0.1" />
	<field name="outer_ipv6_hop_limit" descr="" offset="0x8.6" size="0x0.1" />
	<field name="inner_ipv6_hop_limit" descr="" offset="0x8.7" size="0x0.1" />
	<field name="outer_esp_spi" descr="" offset="0x8.8" size="0x0.1" />
	<field name="inner_esp_spi" descr="" offset="0x8.9" size="0x0.1" />
	<field name="outer_emd_tag" descr="If set, Embedded Meta Data L2 tag is supported in outer header (outer_emd_tag and outer_emd_tag_data[])" offset="0x8.10" size="0x0.1" />
	<field name="outer_first_mpls_label" descr="" offset="0x8.11" size="0x0.1" />
	<field name="outer_first_mpls_exp" descr="" offset="0x8.12" size="0x0.1" />
	<field name="outer_first_mpls_s_bos" descr="" offset="0x8.13" size="0x0.1" />
	<field name="outer_first_mpls_ttl" descr="" offset="0x8.14" size="0x0.1" />
	<field name="inner_first_mpls_label" descr="" offset="0x8.15" size="0x0.1" />
	<field name="inner_first_mpls_exp" descr="" offset="0x8.16" size="0x0.1" />
	<field name="inner_first_mpls_s_bos" descr="" offset="0x8.17" size="0x0.1" />
	<field name="inner_first_mpls_ttl" descr="" offset="0x8.18" size="0x0.1" />
	<field name="outer_first_mpls_over_gre_label" descr="" offset="0x8.19" size="0x0.1" />
	<field name="outer_first_mpls_over_gre_exp" descr="" offset="0x8.20" size="0x0.1" />
	<field name="outer_first_mpls_over_gre_s_bos" descr="" offset="0x8.21" size="0x0.1" />
	<field name="outer_first_mpls_over_gre_ttl" descr="" offset="0x8.22" size="0x0.1" />
	<field name="outer_first_mpls_over_udp_label" descr="" offset="0x8.23" size="0x0.1" />
	<field name="outer_first_mpls_over_udp_exp" descr="" offset="0x8.24" size="0x0.1" />
	<field name="outer_first_mpls_over_udp_s_bos" descr="" offset="0x8.25" size="0x0.1" />
	<field name="outer_first_mpls_over_udp_ttl" descr="" offset="0x8.26" size="0x0.1" />
	<field name="outer_vxlan_gpe_next_protocol" descr="" offset="0x8.27" size="0x0.1" />
	<field name="outer_vxlan_gpe_flags" descr="" offset="0x8.28" size="0x0.1" />
	<field name="outer_vxlan_gpe_vni" descr="" offset="0x8.29" size="0x0.1" />
	<field name="geneve_tlv_option_0_exist" descr="" offset="0x8.30" size="0x0.1" />
	<field name="geneve_tlv_option_0_data" descr="" offset="0x8.31" size="0x0.1" />
	<field name="metadata_reg_c_0" descr="" offset="0xC.0" size="0x0.1" />
	<field name="metadata_reg_c_1" descr="" offset="0xC.1" size="0x0.1" />
	<field name="metadata_reg_c_2" descr="" offset="0xC.2" size="0x0.1" />
	<field name="metadata_reg_c_3" descr="" offset="0xC.3" size="0x0.1" />
	<field name="metadata_reg_c_4" descr="" offset="0xC.4" size="0x0.1" />
	<field name="metadata_reg_c_5" descr="" offset="0xC.5" size="0x0.1" />
	<field name="metadata_reg_c_6" descr="" offset="0xC.6" size="0x0.1" />
	<field name="metadata_reg_c_7" descr="" offset="0xC.7" size="0x0.1" />
	<field name="icmp_header_data" descr="" offset="0xC.8" size="0x0.1" />
	<field name="icmpv6_header_data" descr="" offset="0xC.9" size="0x0.1" />
	<field name="icmp_type" descr="" offset="0xC.10" size="0x0.1" />
	<field name="icmpv6_type" descr="" offset="0xC.11" size="0x0.1" />
	<field name="icmp_code" descr="" offset="0xC.12" size="0x0.1" />
	<field name="icmpv6_code" descr="" offset="0xC.13" size="0x0.1" />
	<field name="outer_geneve_c" descr="" offset="0xC.14" size="0x0.1" />
	<field name="outer_geneve_ver" descr="" offset="0xC.15" size="0x0.1" />
	<field name="gtpu_dw_2" descr="Third DW of GTP-U header, exists in the packet only if indicated so by the flags in the GTP-U header" offset="0xC.16" size="0x0.1" />
	<field name="outer_bth_pkey" descr="" offset="0xC.17" size="0x0.1" />
	<field name="outer_grh_gid" descr="Both DGID and SGID" offset="0xC.18" size="0x0.1" />
	<field name="outer_grh_tclass" descr="" offset="0xC.19" size="0x0.1" />
	<field name="outer_grh_flow_label" descr="" offset="0xC.20" size="0x0.1" />
	<field name="outer_lrh_lid" descr="Both DLID and SLID" offset="0xC.21" size="0x0.1" />
	<field name="gtpu_msg_flags" descr="" offset="0xC.22" size="0x0.1" />
	<field name="gtpu_msg_type" descr="" offset="0xC.23" size="0x0.1" />
	<field name="gtpu_teid" descr="" offset="0xC.24" size="0x0.1" />
	<field name="gtpu_dw_0" descr="" offset="0xC.25" size="0x0.1" />
	<field name="gtpu_first_ext_dw_0" descr="" offset="0xC.26" size="0x0.1" />
	<field name="ipsec_next_header" descr="" offset="0xC.27" size="0x0.1" />
	<field name="ipsec_syndrome" descr="" offset="0xC.28" size="0x0.1" />
	<field name="outer_gre_s_present" descr="" offset="0xC.29" size="0x0.1" />
	<field name="outer_gre_k_present" descr="" offset="0xC.30" size="0x0.1" />
	<field name="outer_gre_c_present" descr="" offset="0xC.31" size="0x0.1" />
</node>

<node name="flow_table_fields_supported_2" descr="" size="0x10.0" >
	<field name="outer_l4_checksum_ok" descr="" offset="0x0.0" size="0x0.1" />
	<field name="outer_ipv4_checksum_ok" descr="" offset="0x0.1" size="0x0.1" />
	<field name="inner_l4_checksum_ok" descr="" offset="0x0.2" size="0x0.1" />
	<field name="inner_ipv4_checksum_ok" descr="" offset="0x0.3" size="0x0.1" />
	<field name="psp_header" descr="DW 0-5 of PSP header" offset="0x0.4" size="0x0.1" />
	<field name="outer_l4_ok" descr="" offset="0x0.5" size="0x0.1" />
	<field name="outer_l3_ok" descr="" offset="0x0.6" size="0x0.1" />
	<field name="inner_l4_ok" descr="" offset="0x0.7" size="0x0.1" />
	<field name="inner_l3_ok" descr="" offset="0x0.8" size="0x0.1" />
	<field name="psp_syndrome" descr="Metadata of the packet created after passing through PSP decryption. Note: this field cannot be modified, but can be copied to another field" offset="0x0.9" size="0x0.1" />
	<field name="outer_ipv4_ihl" descr="" offset="0x0.10" size="0x0.1" />
	<field name="inner_ipv4_ihl" descr="" offset="0x0.11" size="0x0.1" />
	<field name="outer_lrh_sl" descr="" offset="0x0.12" size="0x0.1" />
	<field name="macsec_tag" descr="" offset="0x0.13" size="0x0.1" />
	<field name="macsec_syndrome" descr="" offset="0x0.14" size="0x0.1" />
	<field name="tunnel_header_0_1" descr="indicates support for tunnel_header[0] and tunnel_header[1]" offset="0x0.15" size="0x0.1" />
	<field name="tunnel_header_2_3" descr="indicates support for tunnel_header[2] and tunnel_header[3]" offset="0x0.16" size="0x0.1" />
	<field name="bth_opcode" descr="" offset="0x0.17" size="0x0.1" />
	<field name="hash_result" descr="" offset="0x0.18" size="0x0.1" />
	<field name="outer_esp_seq_num" descr="" offset="0x0.19" size="0x0.1" />
	<field name="inner_esp_seq_num" descr="" offset="0x0.20" size="0x0.1" />
	<field name="lag_rx_port_affinity" descr="" offset="0x0.21" size="0x0.1" />
	<field name="outer_mpls" descr="Outer MPLS labels" offset="0x0.22" size="0x0.1" />
	<field name="inner_mpls" descr="Inner MPLS labels" offset="0x0.23" size="0x0.1" />
	<field name="bth_a" descr="" offset="0x0.24" size="0x0.1" />
	<field name="random_number" descr="" offset="0x0.25" size="0x0.1" />
	<field name="frc_timestamp" descr="" offset="0x0.26" size="0x0.1" />
	<field name="utc_timestamp" descr="" offset="0x0.27" size="0x0.1" />
	<field name="outer_l4_type" descr="Outer packet L4 classification" offset="0x0.28" size="0x0.1" />
	<field name="inner_l4_type" descr="Inner packet L4 classification" offset="0x0.29" size="0x0.1" />
	<field name="outer_l4_type_ext" descr="Outer packet L4 classification. Encoding defined in outer_l4_type_ext field Table  530, &quot;Match Select Fields,&quot; on page  1006" offset="0x0.30" size="0x0.1" />
	<field name="inner_l4_type_ext" descr="Inner packet L4 classification. Encoding defined in outer_l4_type_ext field in Table  530, &quot;Match Select Fields,&quot; on page  1006" offset="0x0.31" size="0x0.1" />
	<field name="metadata_reg_c_8" descr="" offset="0x4.0" size="0x0.1" />
	<field name="metadata_reg_c_9" descr="" offset="0x4.1" size="0x0.1" />
	<field name="metadata_reg_c_10" descr="" offset="0x4.2" size="0x0.1" />
	<field name="metadata_reg_c_11" descr="" offset="0x4.3" size="0x0.1" />
	<field name="metadata_reg_c_12" descr="" offset="0x4.4" size="0x0.1" />
	<field name="metadata_reg_c_13" descr="" offset="0x4.5" size="0x0.1" />
	<field name="metadata_reg_c_14" descr="" offset="0x4.6" size="0x0.1" />
	<field name="metadata_reg_c_15" descr="" offset="0x4.7" size="0x0.1" />
	<field name="out_ipv6_traffic_class" descr="" offset="0x4.8" size="0x0.1" />
	<field name="out_ipv6_payload_length" descr="" offset="0x4.9" size="0x0.1" />
	<field name="inner_ipv6_traffic_class" descr="" offset="0x4.10" size="0x0.1" />
	<field name="inner_ipv6_payload_length" descr="" offset="0x4.11" size="0x0.1" />
	<field name="out_ipv4_total_length" descr="" offset="0x4.12" size="0x0.1" />
	<field name="inner_ipv4_total_length" descr="" offset="0x4.13" size="0x0.1" />
	<field name="out_tcp_data_offset" descr="" offset="0x4.14" size="0x0.1" />
	<field name="inner_tcp_data_offset" descr="" offset="0x4.15" size="0x0.1" />
	<field name="ipsec_next_header" descr="" offset="0x4.16" size="0x0.1" />
	<field name="bth_psn" descr="" offset="0x4.17" size="0x0.1" />
	<field name="bth_rsvd7" descr="" offset="0x4.18" size="0x0.1" />
	<field name="bth_payload" descr="bth_payload_0 to bth_payload_15" offset="0x4.19" size="0x0.1" />
	<field name="bth_payload_partial" descr="bth_payload_0, bth_payload_2, bth_payload_5, bth_payload_6, bth_payload_7, bth_payload_11" offset="0x4.20" size="0x0.1" />
	<field name="retx_indication" descr="indicates that the packet being sent is a retransmission" offset="0x4.21" size="0x0.1" />
	<field name="ooo_eligible" descr="indicates that the packet being sent is eligible to be reordered in the network" offset="0x4.22" size="0x0.1" />
	<field name="mp_ctrl_response" descr="indicates that the packet being sent is a multipath control response packe" offset="0x4.23" size="0x0.1" />
	<field name="mp_path_select" descr="Multipathing path select (PS) assigned to the packet" offset="0x4.24" size="0x0.1" />
	<field name="plb_port_id" descr="Load Balancer chosen port identifier. The value N corresponds to physical port number N+1 (as represented in HCA_CAP.native_port_num)." offset="0x4.25" size="0x0.1" />
	<field name="plb_port_strict" descr="If set, Load Balancer chosen port must be used or the packet should be dropped." offset="0x4.26" size="0x0.1" />
	<field name="plb_port_preferred" descr="If set, using Load Balancer chosen port is recommended, however a different port may be used." offset="0x4.27" size="0x0.1" />
	<field name="icrc_status" descr="" offset="0x4.28" size="0x0.1" />
	<field name="flow_tag" descr="" offset="0x4.29" size="0x0.1" />
	<field name="packet_window_anchor" descr="packet_window_anchor and packet_window_offset" offset="0x4.30" size="0x0.1" />
	<field name="packet_window" descr="DW 0-15 of packet_window" offset="0x4.31" size="0x0.1" />
	<field name="metadata_reg_c_47_16" descr="Each bit represents support for a single reg C indexing 47:16. See bit assignment in HCA_CAP.return_reg_id_47_16" offset="0x8.0" size="0x4.0" />
	<field name="bth_tver" descr="" offset="0xC.31" size="0x0.1" />
</node>

<node name="flow_table_nic_cap" descr="" size="0x1000.0" >
	<field name="nic_receive_max_steering_depth" descr="Indicates a limit to the longest path of packet traversing through the NIC receive steering table. The field is given in device specific units. \;Value 0x0 indicates unlimited depth." offset="0x0.0" size="0x0.8" />
	<field name="add_action_partial_field_supported" descr="When set, add_action supports offset and length fields for partial field access." offset="0x0.23" size="0x0.1" />
	<field name="sw_owner_reformat_supported" descr="If set, SW owner flow table can support reformat action." offset="0x0.24" size="0x0.1" />
	<field name="nic_rx_rdma_fwd_tir" descr="When set, TIR can be used as a destination in NIC Receive RDMA table" offset="0x0.25" size="0x0.1" />
	<field name="ttl_checksum_correction" descr="If set, CQE checksum field may be used even if TTL field was modified by Flow steering tables." offset="0x0.26" size="0x0.1" />
	<field name="nic_rx_flow_tag_multipath_en" descr="When set, NIC RX table supports setting flow_tag for Flows beyond Multi-Processing split.\;See Section  8.18.3.2, &quot;Flow Tagging,&quot; on page  726" offset="0x0.27" size="0x0.1" />
	<field name="allow_sniffer_and_nic_rx_shared_tir" descr="If set, the same TIR can be used by multiple Flow Tables of the following different types: nic receive, receive sniffer, transmit sniffer." offset="0x0.29" size="0x0.1" />
	<field name="nic_rx_multi_path_tirs_fts" descr="If set, this NIC Receive Flow Table supports multiple processing paths for TIRs and Flow tables.See Section  8.18.2.4, &quot;Multi-Processing Paths,&quot; on page  721\;Note: Regardless of whether the destination list includes TIRs or not, the last Flow Table in the destination list is not required to have a level equal or greater than 64 like other Flow Tables in the list." offset="0x0.30" size="0x0.1" />
	<field name="nic_rx_multi_path_tirs" descr="If set, this NIC Receive Flow Table supports multiple processing paths for TIRs. Section  8.18.2.4, &quot;Multi-Processing Paths,&quot; on page  721" offset="0x0.31" size="0x0.1" />
	<field name="max_encap_header_size" descr="The maximum size of the encapsulation header supported by ALLOC_PACKET_REFORMAT_CONTEXT" offset="0x4.0" size="0x0.10" />
	<field name="log_max_packet_reformat_context" descr="Log (base 2) of the maximum packet reformat contexts that can be created by ALLOC_PACKET_REFORMAT_CONTEXT.." offset="0x4.16" size="0x0.5" />
	<field name="encap_general_header" descr="If set, encapsulation of Generalheader is supported.\;Supporting general header encapsulation isn&apos;t necessary mean offload and parsing is also supported. So SW need to make sure the encapsulated protocol can be parsed add offloaded is needed." offset="0x4.31" size="0x0.1" />
	<field name="flow_table_properties_nic_receive" descr="Capabilities and properties of NIC Receive Flow Tables" subnode="flow_table_prop_layout" offset="0x40.0" size="0x40.0" />
	<field name="flow_table_properties_nic_receive_rdma" descr="Capabilities and properties of NIC Receive RDMA Flow Tables" subnode="flow_table_prop_layout" offset="0x80.0" size="0x40.0" />
	<field name="flow_table_properties_nic_receive_sniffer" descr="Capabilities and properties of NIC Receive Sniffer Flow Tables" subnode="flow_table_prop_layout" offset="0xC0.0" size="0x40.0" />
	<field name="flow_table_properties_nic_transmit" descr="Capabilities and properties of NIC Transmit Flow Tables" subnode="flow_table_prop_layout" offset="0x100.0" size="0x40.0" />
	<field name="flow_table_properties_nic_transmit_rdma" descr="Capabilities and properties of NIC Transmit RDMA Flow Tables" subnode="flow_table_prop_layout" offset="0x140.0" size="0x40.0" />
	<field name="flow_table_properties_nic_transmit_sniffer" descr="Capabilities and properties of NIC Transmit Sniffer Flow Tables" subnode="flow_table_prop_layout" offset="0x180.0" size="0x40.0" />
	<field name="header_modify_nic_receive" descr="Header modify capabilities of NIC Receive Flow Tables" subnode="header_modify_cap_properties" offset="0x200.0" size="0x80.0" />
	<field name="ft_field_support_2_nic_receive" descr="" subnode="flow_table_fields_supported_2" offset="0x280.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_nic_receive" descr="" subnode="flow_table_fields_supported_2" offset="0x290.0" size="0x10.0" />
	<field name="ft_field_support_2_nic_receive_rdma" descr="" subnode="flow_table_fields_supported_2" offset="0x2A0.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_nic_receive_rdma" descr="" subnode="flow_table_fields_supported_2" offset="0x2B0.0" size="0x10.0" />
	<field name="ft_field_support_2_nic_receive_sniffer" descr="" subnode="flow_table_fields_supported_2" offset="0x2C0.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_nic_receive_sniffer" descr="" subnode="flow_table_fields_supported_2" offset="0x2D0.0" size="0x10.0" />
	<field name="ft_field_support_2_nic_transmit" descr="" subnode="flow_table_fields_supported_2" offset="0x2E0.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_nic_transmit" descr="" subnode="flow_table_fields_supported_2" offset="0x2F0.0" size="0x10.0" />
	<field name="ft_field_support_2_nic_transmit_rdma" descr="" subnode="flow_table_fields_supported_2" offset="0x300.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_nic_transmit_rdma" descr="" subnode="flow_table_fields_supported_2" offset="0x310.0" size="0x10.0" />
	<field name="ft_field_support_2_nic_transmit_sniffer" descr="" subnode="flow_table_fields_supported_2" offset="0x320.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_nic_transmit_sniffer" descr="" subnode="flow_table_fields_supported_2" offset="0x330.0" size="0x10.0" />
	<field name="header_modify_nic_transmit" descr="Header modify capabilities of NIC Transmit Flow Tables\;" subnode="header_modify_cap_properties" offset="0x380.0" size="0x80.0" />
	<field name="sw_steering_nic_rx_action_drop_icm_address" descr="ICM address representing a drop action. Should be used by SW managed steering for efficient packet drops in NIC Rx Flow Table Type." subnode="uint64" offset="0x400.0" size="0x8.0" />
	<field name="sw_steering_nic_tx_action_drop_icm_address" descr="ICM address representing a drop action. Should be used by SW managed steering for efficient packet drops in NIC Tx Flow Table Type." subnode="uint64" offset="0x408.0" size="0x8.0" />
	<field name="sw_steering_nic_tx_action_allow_icm_address" descr="ICM address representing a Allow action. Should be used by SW managed steering  NIC Tx Flow Table Type." subnode="uint64" offset="0x410.0" size="0x8.0" />
</node>

<node name="flow_table_prop_layout" descr="" size="0x40.0" >
	<field name="wqe_based_flow_update" descr="When set, this table type supports updating Flows in Flow Tables using a WQE. See Section  8.19, &quot;High Update Rate Flow Table,&quot; on page  748" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="sw_owner_v2" descr="When set, this flow table type supports using SW managed Flow Tables. The Flow Table format version is indicated by QUERY_HCA_CAP.steering_format_version. In addition if this field is set sw_owner field should be ignored" access="RW" offset="0x0.1" size="0x0.1" />
	<field name="ipsec_decrypt" descr="When set, this table type supports IPSEC Decryption operation by IPSEC_OFFLOAD action" access="RW" offset="0x0.2" size="0x0.1" />
	<field name="ipsec_encrypt" descr="When set, this table type supports IPSEC Encryption operation by IPSEC_OFFLOAD action" access="RW" offset="0x0.3" size="0x0.1" />
	<field name="forward_vhca_tx" descr="If set, the flow table supports VHCA_TX destination type. i.e. forwarding to other vhca transmit root." access="RW" offset="0x0.4" size="0x0.1" />
	<field name="forward_vhca_rx" descr="If set, the flow table supports VHCA_RX destination type. i.e. forwarding to other vhca receive root." access="RW" offset="0x0.5" size="0x0.1" />
	<field name="reformat_and_fwd_to_table" descr="When set, the flow table supports Reformat or Decapsulate actions in conjunction with Forward to Flow Table action for the same rule. Valid only if the table also supports Reformat or Decapsulate operations. In any case, programmer should not attempt to Reformat/Decapsulate the same packet more than once." access="RW" offset="0x0.6" size="0x0.1" />
	<field name="termination_table" descr="When set, this table type supports creating Flow Tables marked as Termination." access="RW" offset="0x0.7" size="0x0.1" />
	<field name="table_miss_action_domain" descr="When set, the Flow Table type supports defining a miss behavior that will direct the packets to a different Table Type domain" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="ip_type" descr="If set, ip_type in CRAETE_FLOW_GROUP is supported." access="RW" offset="0x0.9" size="0x0.1" />
	<field name="ignore_flow_level" descr="If set, A Flow Table Entry may point to a Flow Table with equal or lower Flow Level." access="RW" offset="0x0.10" size="0x0.1" />
	<field name="reformat_and_modify_action" descr="When set, this Flow Table type supports setting Modify Headers and Reformat related actions for the same FTE (if both actions are supported)." access="RW" offset="0x0.11" size="0x0.1" />
	<field name="reformat_l2_to_l3_tunnel" descr="If set, reformatting the packet from L2 packet to a tunneled L3 packet is supported (remove the L2 header and add tunnel header)" access="RW" offset="0x0.12" size="0x0.1" />
	<field name="reformat_l3_tunnel_to_l2" descr="If set, reformatting the packet from tunneled L3 packet to an L2 packet is supported (remove the tunnel and add L2 header)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="sw_owner" descr="When set, this flow table type supports using SW managed Flow Tables.\;Note that if sw_owner_v2 is set, this field should be ignored" access="RW" offset="0x0.14" size="0x0.1" />
	<field name="modify_and_vlan_action" descr="When set, this Flow Table type supports setting Modify Headers and VLAN related actions for the same FTE (if both actions are supported)." access="RW" offset="0x0.15" size="0x0.1" />
	<field name="reformat_and_vlan_action" descr="When set, this Flow Table type supports setting Reformat related and VLAN related actions for the same FTE (if both actions are supported)." access="RW" offset="0x0.16" size="0x0.1" />
	<field name="push_vlan_2" descr="When set, this Flow Table supports Push_VLAN_2 action (PUSH_VLAN_2)\;push _vlan_2 always happens after push_vlan, so push_vlan_2_tag will be the outermost.\;push_vlan_2 is illegal if not setting also push_vlan" access="RW" offset="0x0.17" size="0x0.1" />
	<field name="pop_vlan_2" descr="When set, this Flow Table supports Pop_VLAN_2 action (POP_VLAN_2)\;pop_vlan_2 is illegal if pop_vlan is not set." access="RW" offset="0x0.18" size="0x0.1" />
	<field name="fpga_vendor_acceleration" descr="If set, FPGA vendor acceleration action is supported." access="RW" offset="0x0.19" size="0x0.1" />
	<field name="push_vlan" descr="When set, this Flow Table supports Push VLAN action (PUSH_VLAN)" access="RW" offset="0x0.20" size="0x0.1" />
	<field name="pop_vlan" descr="When set, this Flow Table supports Pop VLAN action (POP_VLAN)" access="RW" offset="0x0.21" size="0x0.1" />
	<field name="reset_root_to_default" descr="If set, indicates if reset root table to default behavior is supported. See Table 4108, &quot;SET_FLOW_TABLE_ROOT - Input Structure Field Descriptions,&quot; on page 4405" access="RW" offset="0x0.22" size="0x0.1" />
	<field name="decap" descr="If set, decapsulation action is supported." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="reformat" descr="If set, Reformat action is supported." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="flow_table_modify" descr="If set, MODIFY_FLOW_TABLE is supported. See Section 32.19.2 MODIFY_FLOW_TABLE - Modify a Flow Table on page 4400." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="identified_miss_table" descr="If set, forward to identified miss table when creating new flow table is supported. See Section 32.19.1 CREATE_FLOW_TABLE - Allocate a New Flow Table on page 4394." access="RW" offset="0x0.26" size="0x0.1" />
	<field name="modify_root" descr="When set, this Flow Table type supports dynamic modification of the root Flow Table." access="RW" offset="0x0.27" size="0x0.1" />
	<field name="flow_modify_en" descr="When set, this Flow Table type supports modifying flow entries. Section  8.18.4.10, &quot;Redefining a Flow,&quot; on page  739." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="flow_counter" descr="When set, this Flow Table type supports associating flow counters to its flows." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="flow_tag" descr="If set, indicates that flow_tag which is reported in CQE is supported for this type flow table." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="ft_support" descr="When set, this Flow Table type is supported." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="max_ft_level" descr="Maximal value for the Flow Table level." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="max_modify_header_actions" descr="The maximal number of actions that can be allocated by ALLOC_MODIFY_HEADER_CONTEXT. \;0 means modify header not supported." access="RW" offset="0x4.8" size="0x0.8" />
	<field name="log_max_modify_header_context" descr="Log (base 2) of the number of Modify Header Contexts sup ported for this type" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="log_max_ft_size" descr="Log (base2) of the Flow Table size" access="RW" offset="0x4.24" size="0x0.6" />
	<field name="vlan_and_fwd_to_table" descr="When set, the flow table supports Pop VLAN or Push VLAN actions in conjunction with Forward action to a Flow Table in the same Entry. In any case, programmer should not attempt to push or pop more than one VLAN header for the same packet.\;Valid only if the table also supports Push VLAN or Pop VLAN actions." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="termination_table_raw_traffic" descr="When set, this table type supports creating Flow Tables marked as Termination also for raw traffic. i.e. for traffic that will not have modify headers" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="metadata_reg_a_width" descr="Number of supported bits in metadata_reg_a, starting at bit 0. \;If metadata_reg_a is not supported, this field is reserved (as indicated in Flow Tale Field Supported)." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="metadata_reg_b_width" descr="Number of supported bits in metadata_reg_b, starting at bit 0. \;If metadata_reg_b is not supported, this field is reserved (as indicated in Flow Tale Field Supported)." access="RW" offset="0x8.8" size="0x0.8" />
	<field name="log_max_flow_sampler_num" descr="Log (base 2) of the number of Flow Sampler Objects sup ported for this type" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="forward_flow_meter" descr="When set, the Flow Table type supports FWD action with a Flow Meter object as a destination." access="RW" offset="0x8.24" size="0x0.1" />
	<field name="execute_aso" descr="When set, this flow table type supports the action Execute ASO" access="RW" offset="0x8.25" size="0x0.1" />
	<field name="reformat_del_esp_transport_over_udp" descr="when set, the relevant packet reformat operation is supported" access="RW" offset="0x8.26" size="0x0.1" />
	<field name="reformat_l3_esp_tunnel_to_l2" descr="when set, the relevant packet reformat operation is supported" access="RW" offset="0x8.27" size="0x0.1" />
	<field name="reformat_del_esp_transport" descr="when set, the relevant packet reformat operation is supported" access="RW" offset="0x8.28" size="0x0.1" />
	<field name="reformat_add_esp_transport_over_udp" descr="when set, the relevant packet reformat operation is supported" access="RW" offset="0x8.29" size="0x0.1" />
	<field name="reformat_l2_to_l3_esp_tunnel" descr="when set, the relevant packet reformat operation is supported" access="RW" offset="0x8.30" size="0x0.1" />
	<field name="reformat_add_esp_transport" descr="when set, the relevant packet reformat operation is supported" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="log_max_ft_num" descr="Log (base 2) of the number of Flow Tables sup ported for this type" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="reformat_del_psp_transport" descr="If set, reformat header DEL_PSP_TRANSPORT is supported" access="RW" offset="0xC.8" size="0x0.1" />
	<field name="reformat_add_psp_transport" descr="If set, reformat header ADD_PSP_TRANSPORT is supported" access="RW" offset="0xC.9" size="0x0.1" />
	<field name="field_math_ffs" descr="If set, FFS_FIELD action is supported for this table type" access="RW" offset="0xC.10" size="0x0.1" />
	<field name="field_math_xor" descr="If set, XOR_FIELD action is supported for this table type" access="RW" offset="0xC.11" size="0x0.1" />
	<field name="field_math_sub" descr="If set, SUB_FIELD action is supported for this table type" access="RW" offset="0xC.12" size="0x0.1" />
	<field name="field_math_and" descr="If set, AND_FIELD action is supported for this table type" access="RW" offset="0xC.13" size="0x0.1" />
	<field name="gen_cqe" descr="If set, GEN_CQE action is supported for this table type." access="RW" offset="0xC.14" size="0x0.1" />
	<field name="sq_connect" descr="If set, an SQ can be defined to transmit packets directly to the Flow Table domain." access="RW" offset="0xC.15" size="0x0.1" />
	<field name="ignore_flow_level_rtc_valid" descr="When set, a flow table created with rtc_valid=1 will be able to point to a flow table with equal or lower level." access="RW" offset="0xC.16" size="0x0.1" />
	<field name="reformat_l3_audp_tunnel_to_l2" descr="When set, reformat header REMOVE_AUDP_TUNNEL is supported" access="RW" offset="0xC.17" size="0x0.1" />
	<field name="reformat_l2_to_l3_audp_tunnel" descr="When set, reformat header ADD_AUDP_TUNNEL is supported" access="RW" offset="0xC.18" size="0x0.1" />
	<field name="cross_vhca_object" descr="When set, this table supports using cross_vhca objects. They type of the local object must be supported for the table type, and must be supported by the device according to HCA_CAP.cross_vhca_object_to_object_supported." access="RW" offset="0xC.19" size="0x0.1" />
	<field name="stc_insert_encap" descr="If set, this table type supports STC of type HEADER_INSERT with encap property, even if the reformat field is 0x0." access="RW" offset="0xC.20" size="0x0.1" />
	<field name="reparse" descr="When set, this Flow Table type supports Flow Table Entries with reparse indication or RTC with reparse_mode REPARSE_ALWAYS" access="RW" offset="0xC.21" size="0x0.1" />
	<field name="reformat_remove_macsec" descr="When set, reformat header REMOVE_MACSEC is supported" access="RW" offset="0xC.22" size="0x0.1" />
	<field name="reformat_add_macsec" descr="When set, reformat header ADD_MACSEC is supported" access="RW" offset="0xC.23" size="0x0.1" />
	<field name="psp_decrypt" descr="When set, this table type supports PSP Decryption operation." access="RW" offset="0xC.24" size="0x0.1" />
	<field name="psp_encrypt" descr="When set, this table type supports PSP Encryption operation." access="RW" offset="0xC.25" size="0x0.1" />
	<field name="macsec_decrypt" descr="When set, this table type supports MACSEC Decryption operation." access="RW" offset="0xC.26" size="0x0.1" />
	<field name="macsec_encrypt" descr="When set, this table type supports MACSEC Encryption operation." access="RW" offset="0xC.27" size="0x0.1" />
	<field name="reformat_remove" descr="When set, reformat header remove is supported " access="RW" offset="0xC.28" size="0x0.1" />
	<field name="reformat_insert" descr="When set, reformat header insert is supported " access="RW" offset="0xC.29" size="0x0.1" />
	<field name="reformat_l3_psp_tunnel_to_l2" descr="when set, the relevant packet reformat operation is supported." access="RW" offset="0xC.30" size="0x0.1" />
	<field name="reformat_l2_to_l3_psp_tunnel" descr="when set, the relevant packet reformat operation is supported." access="RW" offset="0xC.31" size="0x0.1" />
	<field name="log_max_destination" descr="Log (base 2) of the maximal number of destinations in a single Flow with Forward action" access="RW" offset="0x10.0" size="0x0.8" />
	<field name="log_max_flow_counter" descr="Log (base 2) of the maximal number of flow counters in a single flow with Count action." access="RW" offset="0x10.8" size="0x0.8" />
	<field name="flow_timestamp" descr="If set, flow_timestamp action is supported" access="RW" offset="0x10.27" size="0x0.1" />
	<field name="forward_nic_rx_rdma" descr="If set, the flow table supports NIC_RX_RDMA destination type." access="RW" offset="0x10.28" size="0x0.1" />
	<field name="icrc_calc" descr="If set, ICRC calculation action is support for this table type" access="RW" offset="0x10.29" size="0x0.1" />
	<field name="flow_semaphore" descr="If set, FLOW_SEMAPHORE action is supported for this table type" access="RW" offset="0x10.30" size="0x0.1" />
	<field name="field_math_add" descr="If set, ADD_FIELD action is supported for this table type" access="RW" offset="0x10.31" size="0x0.1" />
	<field name="log_max_flow" descr="Log (base 2) of the total number of flows sup ported for this type. The number of flows is the total over all Flow Tables of this type." access="RW" offset="0x14.0" size="0x0.8" />
	<field name="ft_field_support" descr="Bit per flow table header field support." subnode="flow_table_fields_supported" access="RW" offset="0x20.0" size="0x10.0" />
	<field name="ft_field_bitmask_support" descr="Bit per flow table header field bitmask support." subnode="flow_table_fields_supported" access="RW" offset="0x30.0" size="0x10.0" />
</node>

<node name="generic_dev_emu_capabilities" descr="" size="0x100.0" >
	<field name="db_table_handle" descr="When set, the db_table_handle field in the EMULATED_DEV_DB_CQ_MAPPING object is valid." access="RW" offset="0x0.17" size="0x0.1" />
	<field name="max_bar_per_device_type" descr="Maximal number of BARs to be configured for a single GENERIC_EMULATION_DEVICE_TYPE." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="bar_1MB" descr="When set, memory space below 1 MB BARs are supported" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="bar_32b" descr="When set, 32bit BARs are supported" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="bar_io" descr="When set, IO BAR type is supported" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="bar_64b" descr="When set, 64bit BARs are supported" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="nvme_bar_layout" descr="If set, configuring the NVMe bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.20" size="0x0.1" />
	<field name="virtio_blk_bar_layout" descr="If set, configuring the VIRTIO_BLK bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.21" size="0x0.1" />
	<field name="virtio_net_bar_layout" descr="If set, configuring the VIRTIO_NET bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.22" size="0x0.1" />
	<field name="virtio_fs_bar_layout" descr="If set, configuring the VIRTIO_FS bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.23" size="0x0.1" />
	<field name="max_generic_device_types" descr="Maximal number of persistent generic device types supported" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="max_bar_regions_per_bar" descr="Maximal number of BAR regions to be configured in a single emulated BAR." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="max_bar_regions_per_device_type" descr="Maximal number of BAR regions to be configured for a single GENERIC_EMULATION_DEVICE_TYPE." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="vendor_specific_cap_type_support" descr="Bitmask indicating which vendor-specific PCI CAPs are suported. Set bit indicates this CAP is supported\;Bit 0: VSC - Vendor Specific Capability\;Bit 1: VSEC - Vendor Specific Extended Capability \;other bits are reserved." access="RW" enum="VSC=0x1,VSEC=0x2" offset="0xC.0" size="0x0.8" />
	<field name="max_vsc_total_size" descr="Total maximal length of VSC supported, given in bytes." access="RW" offset="0xC.8" size="0x0.8" />
	<field name="max_vsec_total_size" descr="Total maximal length of VSEC supported, given in bytes" access="RW" offset="0xC.16" size="0x0.16" />
	<field name="max_num_msix_per_device" descr="The maximum number of MSIXs that can be set for a generic emulation device." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="log_max_bar_size" descr="Log (base 2) of the maximal size for emulated BAR, given in bytes." access="RW" offset="0x14.16" size="0x0.8" />
	<field name="log_min_bar_size" descr="Log (base 2) of the minimal size for emulated BAR, given in bytes." access="RW" offset="0x14.24" size="0x0.8" />
	<field name="max_controller_message_size" descr="Maximal message size supported in TBD command, given in bytes" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="max_num_db_per_device" descr="The maximum number of doorbells that can be set for a generic emulation device." access="RW" offset="0x18.16" size="0x0.16" />
	<field name="log_max_exp_bar_size" descr="Log (base 2) of the maximum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="log_min_exp_bar_size" descr="Log (base 2) of the minimum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="max_managed_emulated_hosts" descr="The maximal number of managed emulated hosts (PCI links) that can be managed by the device. This is a one based value and valid if HCA_CAP.host_number_ready is set." access="RW" offset="0x1C.16" size="0x0.4" />
	<field name="host_number_ready" descr="If set, host_number_valid and host_number fields are valid for both the QUERY_EMULATED_FUNCTIONS_INFO and HOTPLUG_DEVICE commands. Additionally, setting the corresponding device type in the op_mod field of the QUERY_MANAGED_EMULATED_HOSTS_INFO command is supported." access="RW" offset="0x1C.20" size="0x0.1" />
	<field name="always_armed_device_db" descr="When set, configuring always_armed_device_db field in the GENERIC_PCI_DEVICE_EMULATION object is supported." access="RW" offset="0x1C.27" size="0x0.1" />
	<field name="max_emulated_objects_per_vhca_id" descr="The maximum number of device emulated objects that can be created per single vhca_id. This is a zero based value." access="RW" offset="0x1C.28" size="0x0.4" />
	<field name="bar_region_types_support_region_update_notifier" descr="Bitmap indicates the supported BAR Region types for the region update notifier mechanism. Each set Bit representing BAR region identifier support according to Table 1545, &quot;BAR Region Types,&quot; on page 2011" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="controller_send_message_opmodes_supported" descr="Bitmask indicates the supported opmodes for GENERIC_PCI_CONTROLLER_SEND_MESSAGE command:\;Bit0 - op_mod 0x0 (bar stateful region device query) supported\;Bit1 - op_mod 0x1 (bar stateful region device modify) supported\;Bit2 - op_mod 0x2 (bar stateful region device set default values) supported\;Bit3 - op_mod 0x3 (bar stateful region device_type set default values) supported\;Bit4 - op_mod 0x4 (bar sw_pci_cb region message) supported" access="RW" offset="0x2C.0" size="0x4.0" />
	<field name="sw_pci_cb_api_version" descr="The version of supported SW_PCI_CB handler apis" access="RW" offset="0x30.0" size="0x4.0" />
	<field name="max_sw_pci_cb_context_mem_size" descr="Maximal size of persistent memory buffer that can be allocated for SW_PCI_CB handler, given in bytes" access="RW" offset="0x34.0" size="0x4.0" />
	<field name="max_sw_pci_cb_xro_mem_size" descr="Maximal size of memory buffer allocated to callback handler for code and read-only data, given in bytes" access="RW" offset="0x38.0" size="0x4.0" />
	<field name="max_sw_pci_cb_static_mem_size" descr="Maximal size of memory buffer allocated to callback handler for static data, given in bytes. The buffer is initialized in the process start." access="RW" offset="0x3C.0" size="0x4.0" />
	<field name="bar_stateful_region_block_size" descr="Minimal allocation data unit for a BAR stateful region, in bytes." access="RW" offset="0x40.0" size="0x0.16" />
	<field name="max_bar_stateful_regions_per_bar" descr="Maximal amount of BAR stateful regions that can be configured per BAR." access="RW" offset="0x40.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_stateful_region" descr="Maximal amount of BAR stateful region blocks for a single stateful BAR region." access="RW" offset="0x44.0" size="0x0.16" />
	<field name="max_bar_stateful_regions_per_device_type" descr="Maximal amount of BAR stateful regions that can be configured per device type." access="RW" offset="0x44.16" size="0x0.16" />
	<field name="stateful_region_base_addr_align_log" descr="Log (base 2) of BAR stateful region base address alignment. Upon BAR stateful region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x48.0" size="0x0.6" />
	<field name="bar_db_region_block_size" descr="Minimal allocation data unit for a BAR doorbell region, in bytes." access="RW" offset="0x4C.0" size="0x0.16" />
	<field name="max_bar_db_regions_per_bar" descr="Maximal amount of BAR doorbell regions that can be configured per BAR." access="RW" offset="0x4C.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_db_region" descr="Maximal amount of BAR doorbell region blocks for a single doorbell BAR region." access="RW" offset="0x50.0" size="0x0.16" />
	<field name="max_bar_db_regions_per_device_type" descr="Maximal amount of BAR doorbell regions that can be configured per device type." access="RW" offset="0x50.16" size="0x0.16" />
	<field name="db_region_base_addr_align_log" descr="Log (base 2) of BAR doorbell region base address alignment. Upon BAR doorbell region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x54.0" size="0x0.6" />
	<field name="bar_msix_pba_region_block_size" descr="Minimal allocation data unit for a BAR MSI-X PENDING region, in bytes." access="RW" offset="0x58.0" size="0x0.16" />
	<field name="max_bar_msix_pba_regions_per_bar" descr="Maximal amount of BAR MSI-X PENDING regions that can be configured per BAR." access="RW" offset="0x58.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_msix_pba_region" descr="Maximal amount of BAR MSI-X PENDING region blocks for a single MSI-X PENDING BAR region." access="RW" offset="0x5C.0" size="0x0.16" />
	<field name="max_bar_msix_pba_regions_per_device_type" descr="Maximal amount of BAR MSI-X PENDING regions that can be configured per device type." access="RW" offset="0x5C.16" size="0x0.16" />
	<field name="msix_pba_region_base_addr_align_log" descr="Log (base 2) of BAR MSI-X PENDING region base address alignment. Upon BAR MSI-X PENDING region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x60.0" size="0x0.6" />
	<field name="bar_msix_table_region_block_size" descr="Minimal allocation data unit for a BAR MSI-X VECTOR table region, in bytes." access="RW" offset="0x64.0" size="0x0.16" />
	<field name="max_bar_msix_table_regions_per_bar" descr="Maximal amount of BAR MSI-X VECTOR table regions that can be configured per BAR." access="RW" offset="0x64.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_msix_table_region" descr="Maximal amount of BAR MSI-X VECTOR table region blocks for a single MSI-X VECTOR table BAR region." access="RW" offset="0x68.0" size="0x0.16" />
	<field name="max_bar_msix_table_regions_per_device_type" descr="Maximal amount of BAR MSI-X VECTOR table regions that can be configured per device type." access="RW" offset="0x68.16" size="0x0.16" />
	<field name="msix_table_region_base_addr_align_log" descr="Log (base 2) of BAR MSI-X VECTOR table region base address alignment. Upon BAR MSI-X VECTOR table region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x6C.0" size="0x0.6" />
	<field name="bar_sw_pci_cb_region_block_size" descr="Minimal allocation data unit for a BAR SW_PCI_CB region, in bytes." access="RW" offset="0x70.0" size="0x0.16" />
	<field name="max_bar_sw_pci_cb_regions_per_bar" descr="Maximal amount of BAR SW_PCI_CB regions that can be configured per BAR." access="RW" offset="0x70.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_sw_pci_cb_region" descr="Maximal amount of BAR SW_PCI_CB region blocks for a single SW_PCI_CB BAR region." access="RW" offset="0x74.0" size="0x0.16" />
	<field name="max_bar_sw_pci_cb_regions_per_device_type" descr="Maximal amount of BAR SW_PCI_CB regions that can be configured per device type." access="RW" offset="0x74.16" size="0x0.16" />
	<field name="sw_pci_cb_region_base_addr_align_log" descr="Log (base 2) of BAR SW_PCI_CB region base address alignment. Upon BAR SW_PCI_CB region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x78.0" size="0x0.6" />
</node>

<node name="hca_caps_2" descr="" size="0x100.0" >
	<field name="packet_window_offset_max" descr="Maximal (signed 2c) value supported for packet_window_offset" offset="0xC.0" size="0x0.9" />
	<field name="packet_window_offset_min" descr="Minimal (signed 2c) value supported for packet_window_offset" offset="0xC.16" size="0x0.9" />
	<field name="log_reserved_qpn_max_alloc" descr="Log (base 2) of the maximum bulk of allocated RESERVED_QPN objects\;See Table  572, &quot;RESERVED_QPN Object Format,&quot; on page  1063" offset="0x10.0" size="0x0.5" />
	<field name="local_mng_port" descr="When set, the network port connects to a local BMC device through NC-SI.\;Valid if local_mng_port_valid is set." offset="0x10.5" size="0x0.1" />
	<field name="local_eswitch" descr="When set, indicates that an degenerated eswitch will be available to the network function, consisting of a single vport and a single uplink.\;For vhca_resource_manager this cap indicates this feature may be set for the VFs/SFs.\;" offset="0x10.6" size="0x0.1" />
	<field name="umr_log_entity_size_5" descr="When set, UMR WQE supports modifying log_entity_size[5] for Mkeys that support UMR." offset="0x10.7" size="0x0.1" />
	<field name="log_reserved_qpn_granularity" descr="Log (base 2) of the minimum bulk granularity of allocated RESERVED_QPN objects\;See Table  572, &quot;RESERVED_QPN Object Format,&quot; on page  1063" offset="0x10.8" size="0x0.5" />
	<field name="query_vuid" descr="If set, QUERY_VUID commands is supported." offset="0x10.13" size="0x0.1" />
	<field name="introspection_mkey_access_allowed" descr="If set, then vHCA can read introspection_mkey of other vHCAs on same eswitch and access it by crossed vCHA mkey.\;To do that, SW should create local mkey with:\;\;- access_mode = CROSSING_VHCA_MKEY\;- crossing_target_vhca_id = vhca_id of the vHCA to be accessed.\;- translations_octword_size_crossing_target_mkey = introspection_mkey of the vHCA to be accessed.\;" offset="0x10.14" size="0x0.1" />
	<field name="log_max_num_reserved_qpn" descr="Log (base 2) of the maximum number of RESERVED_QPN objects\;See Table 572, &quot;RESERVED_QPN Object Format,&quot; on page 1063" offset="0x10.16" size="0x0.5" />
	<field name="enh_eth_striding_wq" descr="When set, Enhanced Ethernet/IPoIB STRWQ are supported. See &quot;STRWQ Enhancements&quot; on page 274" offset="0x10.21" size="0x0.1" />
	<field name="fw_cpu_monitoring" descr="If set, device support fw_cpu monitoring,\;To enabled it, SW should set NIC_CAP_REG.fw_cpu_monitoring_enabled==1." offset="0x10.22" size="0x0.1" />
	<field name="dp_ordering_force" descr="If set, dp_ordering_force in QP Context and DCT Context are supported." offset="0x10.23" size="0x0.1" />
	<field name="max_num_prog_sample_field" descr="Maximal number of prog_sample_field supported in a single match criteria/value. Value 0x0 indicates 0x4. \;Valid only if this field is supported for the specific table type" offset="0x10.24" size="0x0.5" />
	<field name="cq_with_emulated_dev_eq" descr="If set, CQ can be created with EMULATED_DEV_EQ element type." offset="0x10.29" size="0x0.1" />
	<field name="force_multi_prio_sq" descr="When set, indicates that the device is optimized to support SQs used \;for transmission of packets with multiple priorities, even w/o explicit request by NIC_VPORT_CONTEXT.multi_prio_sq. For vhca_resource_manager, indicates the device supports setting this field for the managed VHCAs/Vports." offset="0x10.30" size="0x0.1" />
	<field name="migratable" descr="When set, the respective VF may be migrated" offset="0x10.31" size="0x0.1" />
	<field name="max_reformat_remove_offset" descr="Maximal offset of removed header using Packet Reformat context, given in Bytes" offset="0x14.0" size="0x0.8" />
	<field name="max_reformat_remove_size" descr="Maximal size of removed header using Packet Reformat context, given in Bytes" offset="0x14.8" size="0x0.8" />
	<field name="max_reformat_insert_offset" descr="Maximal offset of inserted header using Packet Reformat context, given in Bytes" offset="0x14.16" size="0x0.8" />
	<field name="max_reformat_insert_size" descr="Maximal size of inserted header using Packet Reformat context, given in Bytes" offset="0x14.24" size="0x0.8" />
	<field name="log_max_conn_track_offload" descr="Log (base 2) of the maximum CONN_TRACK objects supported.\;Valid only when HCA_CAP.general_obj_types[CONN_TRACK_OFFLOAD]==1." offset="0x18.0" size="0x0.5" />
	<field name="migration_state" descr="if set, migration_state field in QUERY_VHCA_MIGRATION_STATE output is valid." offset="0x18.6" size="0x0.1" />
	<field name="multiplane" descr="When set, the device supports multiplane port(s)." offset="0x18.7" size="0x0.1" />
	<field name="log_conn_track_max_alloc" descr="Log (base 2) of the maximum allocation granularity of the CONN_TRACK object.\;Valid only when HCA_CAP.general_obj_types[CONN_TRACK_OFFLOAD]==1." offset="0x18.8" size="0x0.5" />
	<field name="sf_eq_usage" descr="Indicates how SF should use EQs:\;0x0: MINIMAL_USE - SF should use as EQs as little as possible\;0x1: UNLIMITED - SF may use as many EQ as available\;In any case EQs are limited by max_num_eqs_24bit.\;For vhca_resource_manager, non-zero value indicates the support for setting this field for the managed SFs." enum="MINIMAL_USE=0x0,UNLIMITED=0x1" offset="0x18.13" size="0x0.1" />
	<field name="multiplane_sq" descr="If set, SQ can be associated with port-plane by setting the plane index in SQ Context" offset="0x18.14" size="0x0.1" />
	<field name="migration_in_chunks" descr="If set, migration in chunks is supported" offset="0x18.15" size="0x0.1" />
	<field name="log_conn_track_granularity" descr="Log (base 2) of the minimum allocation granularity of CONN_TRACK object.\;Valid only when HCA_CAP.general_obj_types[CONN_TRACK_OFFLOAD]==1." offset="0x18.16" size="0x0.5" />
	<field name="multiplane_qp_ud" descr="If set, UD QP can be associated with port-plane by setting the plane index in QPC address path" offset="0x18.21" size="0x0.1" />
	<field name="migration_tracking_state" descr="If set, the device supports saving VF state while the VF is not suspended, and in incremental steps. See &quot;Incremental Migration&quot; on page 1631." offset="0x18.22" size="0x0.1" />
	<field name="migration_multi_load" descr="if set, LOAD_VHCA_STATE can be called multiple times before calling RESUME_VHCA." offset="0x18.23" size="0x0.1" />
	<field name="log_min_stride_wqe_sz" descr="Log (base 2) of the minimum required size of rcv wqe in a strided RQ in granularity of Bytes.\;Note that 0 means 16KB.\;" offset="0x18.24" size="0x0.5" />
	<field name="bsf_v2" descr="If set, BSF version 2 is supported. See Table  1432, &quot;Byte Stream Format V2 (BSF_V2) Layout,&quot; on page  1850" offset="0x18.29" size="0x0.1" />
	<field name="non_tunnel_reformat" descr="When set, Packet Reformat types INSERT_HEADER or REMOVE_HEADER do not require setting reformat_en in the Flow Table Contetx, and are allowed to be used in conjunction with Forward to Table action." offset="0x18.30" size="0x0.1" />
	<field name="multi_sl_qp" descr="If set, the device supports an indication from the SW that QPs are used for transmission of packets with multiple SLs" offset="0x18.31" size="0x0.1" />
	<field name="cross_vhca_object_to_object_supported" descr="A bitmask that indicates which objects can be accessed/used by which objects allocated in another vHCA.\;Bit 0: local_cq_to_remote_dpa_umem - Local CQ can access remote umem that is used by DPA in another vHCA.\;Bit 1: local_sq_to_remote_dpa_umem - Local SQ can access remote umem that is used by DPA in another vHCA.\;Bit 2: local_rq_to_remote_dpa_umem - Local RQ can access remote umem that is used by DPA in another vHCA.\;Bit 3: local_qp_to_remote_dpa_umem - Local QPcan access remote umem that is used by DPA in another vHCA.\;Bit 4: local_cq_to_remote_dpa_thread - Local CQ can access remote DPA_THREAD in another vHCA.\;Bit 5: local_nvme_sq_be_remote_nvme_sq - Local NVME_SQ_BE can access remote NVME_SQ in another vHCA.\;Bit 6: local_dpa_window_to_remote_pd - Local DPA_WINDOW can access remote PD in another vHCA.\;Bit 7: local_dpa_outbox_to_remote_uar - Local DPA_OUTBOX can access remote UAR in another vHCA.\;Bit 8: local_mkey_to_remote_mkey - Local Mkey can access remote Mkey in another vHCA .\;Bit 9: local_cq_to_remote_emulated_dev_eq - Local CQ can access remote  EMULATED_DEV_EQ in another vHCA\;Bit 10: Local_stc_to_remote_tir - Local STC can allow STE to forward a packet to a remote TIR\;Bit 11: Local_stc_to_remote_flow_table - local STC can allow STE to forward a packet to a remote Flow Table\;Bit 12:Local_rtc_to_remote_flow_table - Local RTC can have a remote Flow Table as a default miss action\;Bit 13: Local_flow_table_to_remote_rtc - local Flow Table can have a remote RTC defining its behavior\;Bit 14: local_flow_table_rtc_vld_to_remote_flow_table_miss - local Flow Table with rtc_vld=1 can have a remote Flow Table as a default miss action\;Bit 15: local_cq_to_remote_dpa_uar - Local CQ can access remote DPA UAR.\;Bit 16: local_sq_to_remote_dpa_uar - Local SQ can access remote DPA UAR.\;Bit 17: local_rq_to_remote_dpa_uar - Local RQ can access remote DPA UAR.\;Bit 18: local_qp_to_remote_dpa_uar - Local QP can access remote DPA UAR.\;Bit 19: local_flow_table_to_remote_flow_table_miss - local Flow table can have a remote Flow Table as a default miss action (extends bit 14)\;Bit 20: local_flow_table_root_to_remote_flow_table - Remote Flow Table can be set as Root of Local Flow Tables\;Bit 21: local_decrypt_action_to_remote_prog_master_key - Remote PROG_MASTER_KEY can be used in Local PSP Decrypt action" enum="local_cq_to_remote_dpa_umem=0x1,local_sq_to_remote_dpa_umem=0x2,local_rq_to_remote_dpa_umem=0x4,local_qp_to_remote_dpa_umem=0x8,local_cq_to_remote_dpa_thread=0x10,local_nvme_sq_be_remote_nvme_sq=0x20,local_dpa_window_to_remote_pd=0x40,local_dpa_outbox_to_remote_uar=0x80,local_mkey_to_remote_mkey=0x100,local_cq_to_remote_emulated_dev_eq=0x200,Local_stc_to_remote_tir=0x400,Local_stc_to_remote_flow_table=0x800,Local_rtc_to_remote_flow_table=0x1000,Local_flow_table_to_remote_rtc=0x2000,local_flow_table_rtc_vld_to_remote_flow_table_miss=0x4000,local_cq_to_remote_dpa_uar=0x8000,local_sq_to_remote_dpa_uar=0x10000,local_rq_to_remote_dpa_uar=0x20000,local_qp_to_remote_dpa_uar=0x40000,local_flow_table_to_remote_flow_table_miss=0x80000,local_flow_table_root_to_remote_flow_table=0x100000,local_decrypt_action_to_remote_prog_master_key=0x200000" offset="0x1C.0" size="0x4.0" />
	<field name="allowed_object_for_other_vhca_access" descr="Indicates which objects can be accessed/used by other objects allocated in another vHCA.\;Bit 0x0: PD\;Bit 0x1: UAR\;Bit 0x2: MKEY\;Bit 0x3: UMEM\;Bit 0x4: EQ\;Bit 0x7: NVME_SQ\;Bit 0x8: TIR\;Bit 0x9: FLOW_TABLE\;Bit 0xA: RTC\;Bit 0xB: EMULATED_DEV_EQ\;Bit 0xC: PROG_MASTER_KEY\;Bit 0x2B: DPA_THREAD\;Bit 0x2C: DPA_UAR" subnode="uint64" enum="PD=0x1,UAR=0x2,MKEY=0x4,UMEM=0x8,EQ=0x10,NVME_SQ=0x80,TIR=0x100,FLOW_TABLE=0x200,RTC=0x400,EMULATED_DEV_EQ=0x800,PROG_MASTER_KEY=0x1000,DPA_THREAD=0x800,DPA_UAR=0x1000" offset="0x20.0" size="0x8.0" />
	<field name="introspection_mkey" descr="A memory key for introspection access of this vHCA that spans the entire host memory physical addresses.\;This mkey is configured to allow creating crossing vhca mkey.\;Only vHCA with introspection_mkey_access_allowed==1 can query and use this mkey on vHCA on same eswitch.\;\;0 means field is invalid and no access to this mkey." offset="0x28.0" size="0x4.0" />
	<field name="log_ec_mmo_max_dst" descr="Log(Base 2) of the maximum number of Erasure Coding MMO destinations. Valid only when HCA_CAP.ec_mmo_qp==1" offset="0x2C.0" size="0x0.5" />
	<field name="log_ec_mmo_max_src" descr="Log(Base 2) of the maximum number of Erasure Coding MMO sources. Valid only when HCA_CAP.ec_mmo_qp==1" offset="0x2C.8" size="0x0.5" />
	<field name="pcc_ccmad_probe_prio_set" descr="When set, setting CMAD probe priority can be enabled in PCC_CONFIG object using probe_prio_set_en" offset="0x2C.15" size="0x0.1" />
	<field name="log_ec_mmo_max_size" descr="Log(Base 2) of the maximum Erasure Coding MMO block size in bytes. Valid only when HCA_CAP.ec_mmo_qp==1" offset="0x2C.16" size="0x0.5" />
	<field name="local_mng_port_valid" descr="When set, local_mng_port field indicates the connection to a local BMC" offset="0x2C.21" size="0x0.1" />
	<field name="hairpin_data_buffer_locked" descr="If set, hairpin data buffer can be allocated in locked internal buffer. i.e. hairpin_data_buffer_type==locked_internal_buffer." offset="0x2C.22" size="0x0.1" />
	<field name="hairpin_sq_wq_in_host_mem" descr="If set, hairpin SQ can be opened with hairpin_wq_buffer_type==host_memory." offset="0x2C.23" size="0x0.1" />
	<field name="hairpin_sq_wqe_bb_size" descr="Indicates required size of SQ WQE BB in granularity of 64 Bytes that needed for hairpin SQ buffer." offset="0x2C.24" size="0x0.5" />
	<field name="driver_version_change_event" descr="If set, DRIVER_VERSION_CHANGE Event is supported.\;See Table 382, &quot;DRIVER_VERSION_CHANGE Event Layout,&quot; on page 862" offset="0x2C.29" size="0x0.1" />
	<field name="sync_driver_version" descr="If set, SYNC_DRIVER_VERSION command is supported.\;See Section 32.3.21, &quot;SYNC_DRIVER_VERSION&quot;, on page 4204" offset="0x2C.30" size="0x0.1" />
	<field name="ec_mmo_qp" descr="if set, Erasue Coding MMO WQE is supported for RC and DC QPs. Maximum size of erasure_coding_mmo is reported in HCA_CAP.log_ec_mmo_max_size. Maximum number of sources and destinations are reported in HCA_CAP.log_ec_mmo_max_src, HCA.log_ec_mmo_max_dst." offset="0x2C.31" size="0x0.1" />
	<field name="sync_driver_actions" descr="Bitmask indicates which actions is supported by SYNC_DRIVER_VERSION command.\;Bit 0x0: IGNORE_LRO" offset="0x30.0" size="0x4.0" />
	<field name="execute_aso_type" descr="Bitmask indicating which ASO type may be used using the execute_aso action.\;Bit 0: IPSEC\;Bit 1: CONN_TRACK\;Bit 2: FLOW_METER\;Bit 4: FLOW_HIT\;Bit 7: FLOW_ENTROPY\;Bit 8: QUEUE_MNG\;Bit 9: URISC_MEM\;Bit 12: PASO_STATE\;Bit 13: FIFO_ASO\;Other bits are reserved" enum="IPSEC=0x1,CONN_TRACK=0x2,FLOW_METER=0x4,FLOW_HIT=0x10,FLOW_ENTROPY=0x80,QUEUE_MNG=0x100,URISC_MEM=0x200,PASO_STATE=0x1000,FIFO_ASO=0x2000" offset="0x34.0" size="0x0.16" />
	<field name="min_mkey_log_entity_size" descr="Log (base 2) of minimal required value of log_entity_size in Mkey Context.\;Note that 0 equals to value 12." offset="0x34.16" size="0x0.5" />
	<field name="format_select_dw_8_6_ext" descr="When set, format_select_dw[8:6] support offsets greater than 0x3F" offset="0x34.21" size="0x0.1" />
	<field name="provider_id_ex_valid" descr="if set, the provider_id_ex field in CHANNEL_SERVICE and CHANNEL_CONNECTION is supported." offset="0x34.22" size="0x0.1" />
	<field name="memory_slow_release" descr="If set, MEMORY_SLOW_RELEASE command is supported" offset="0x34.23" size="0x0.1" />
	<field name="flow_table_type_2_type" descr="bitmask indicating which transitions between flow table types are supported\;Bit 0: NIC_RX_2_NIC_RX_RDMA\;Bit 1: NIC_TX_RDNA_2_NIC_TX\;Bit 2: NIC_TX_2_FDB\;Other bits are reserved" enum="NIC_RX_2_NIC_RX_RDMA=0x1,NIC_TX_RDNA_2_NIC_TX=0x2,NIC_TX_2_FDB=0x4" offset="0x34.24" size="0x0.8" />
	<field name="general_obj_types_127_64" descr="Bitmask that indicates if General objects 127-64 are supported.\;Mapping of bits to object types is defined in Table 4341, &quot;GENERAL OBJECT TYPES,&quot; on page 4530" subnode="uint64" offset="0x38.0" size="0x8.0" />
	<field name="repeated_mkey_v2" descr="Mkey number used to identify a repeated block V2 format.\;0 means Repeated Mkey v2 not supported.\;See Table 1280, &quot;Repeated Block Format,&quot; on page 1680" offset="0x40.0" size="0x4.0" />
	<field name="reserved_gid_index" descr="Reserved index in GID table.\;Valid only when reserved_gid_index_valid==1." offset="0x44.0" size="0x0.16" />
	<field name="sw_vhca_id" descr="Software vhca identifier.\;Valid only when sw_vhca_id_valid ==1 and only after INIT_HCA command." offset="0x44.16" size="0x0.14" />
	<field name="sw_vhca_id_valid" descr="If set, SW must provide sw_vhca_id in INIT_HCA command, beside that sw_vhca_id is valid.\;SW that read 1 in max value, should set 1 to current value.\;" offset="0x44.30" size="0x0.1" />
	<field name="reserved_gid_index_valid" descr="If set, reserved_gid_index is valid" offset="0x44.31" size="0x0.1" />
	<field name="flow_counter_bulk_log_granularity" descr="Log (base 2) of the allocation granularity of a Flow Counter Bulk" offset="0x48.0" size="0x0.5" />
	<field name="flow_counter_bulk_log_max_alloc" descr="Log (base 2) of the maximum allocation size of a Flow Counter Bulk" offset="0x48.8" size="0x0.5" />
	<field name="ts_cqe_metadata_size2wqe_counter" descr="Number of bits (starting at LSB) passed from WQE.flow_table_metadata to CQE.wqe_counter (LSB)" offset="0x48.16" size="0x0.5" />
	<field name="log_max_channel_service_connection" descr="Log (base 2) of the maximum number of supported connected clients to a single Channel Service.\;Value 0x0 indicates that the number is not limited, and reporting the connected client list and number of connections is not supported." offset="0x48.24" size="0x0.5" />
	<field name="format_select_dw_outer_first_mpls_over_udp" descr="Value required in format_select_dw* to match: MPLSoUDP first MPLS label" offset="0x4C.0" size="0x0.8" />
	<field name="format_select_dw_outer_first_mpls_over_gre" descr="Value required in format_select_dw* to match: MPLSoGRE first MPLS label" offset="0x4C.8" size="0x0.8" />
	<field name="format_select_dw_geneve_tlv_option_0" descr="Value required in format_select_dw* to match: Geneve TLV Option 0" offset="0x4C.16" size="0x0.8" />
	<field name="format_select_dw_mpls_over_x_cw" descr="Value required in format_select_dw* to match: MPLSoGRE/MPLSoUDP Control Word" offset="0x4C.24" size="0x0.8" />
	<field name="format_select_dw_gtpu_first_ext_dw_0" descr="Value required in format_select_dw* to match: GTP-U first DW of first extension" offset="0x50.0" size="0x0.8" />
	<field name="format_select_dw_gtpu_dw_2" descr="Value required in format_select_dw* to match: GTP-U 3ed DW" offset="0x50.8" size="0x0.8" />
	<field name="format_select_dw_gtpu_dw_1" descr="Value required in format_select_dw* to match: GTP-U 2nd DW/TEID" offset="0x50.16" size="0x0.8" />
	<field name="format_select_dw_gtpu_dw_0" descr="Value required in format_select_dw* to match: GTP-U 1st DW" offset="0x50.24" size="0x0.8" />
	<field name="generate_wqe_type" descr="Bitmask indicating which WQE types are supported by the GENERATE_WQE command\;Bit 1: FLOW_UPDATE\;Other bits are reserved." enum="FLOW_UPDATE=0x2" offset="0x54.0" size="0x4.0" />
	<field name="log_max_rq_hairpin_data_buffer_locked_size" descr="Log(base 2) of the maximum locked data buffer that can be allocated per hairpin RQ in granularity of Bytes." offset="0x58.0" size="0x0.5" />
	<field name="log_max_total_hairpin_data_buffer_locked_size" descr="Log(base 2) of the maximum total locked data buffer that can be allocated for hairpin RQ in granularity of Bytes.\;Note that this capability is shared between all vHCAs." offset="0x58.8" size="0x0.5" />
	<field name="max_enh_strwq_supported_profile" descr="Maximal number of supported Enhanced STRWQ profiles." offset="0x58.16" size="0x0.16" />
	<field name="enh_strwq_max_tailroom" descr="Maximal Tailroom size for Enhanced STRWQ profile, given in Strides" offset="0x5C.0" size="0x0.8" />
	<field name="enh_strwq_max_headroom" descr="Maximal Headroom size for Enhanced STRWQ profile, given in Strides" offset="0x5C.8" size="0x0.8" />
	<field name="enh_strwq_max_log_page_size" descr="log (base 2) of the maximal page size supported for Enhanced STRWQ profile. Value is given in 4KB" offset="0x5C.16" size="0x0.5" />
	<field name="pcc_np_config_handover_en" descr="If set, PCC_NP_CONFIG object supports handover flow." offset="0x5C.21" size="0x0.1" />
	<field name="match_select_ib_l4_ver" descr="Defines ib_l4 field format in Table  529, &quot;Match Select Layout,&quot; on page  994\;0x0: IB_L4_V1\;0x1: IB_L4_V2\;0x3: IB_L4_V3" enum="IB_L4_V1=0x0,IB_L4_V2=0x1,IB_L4_V3=0x3" offset="0x5C.22" size="0x0.2" />
	<field name="log_max_send_dbr_less_qp_sq" descr="Log (base 2) of the maximal number of supported QPs and SQs not using DBR for send operations" offset="0x5C.24" size="0x0.5" />
	<field name="send_dbr_mode_no_dbr_ext" descr="When set, QP/SQ using SW DB support avoiding DBR update for send operations by setting send_dbr_mode to NO_DBR_EXT" offset="0x5C.30" size="0x0.1" />
	<field name="send_dbr_mode_no_dbr_int" descr="When set, QP/SQ using device DB support avoiding DBR update for send operations by setting send_dbr_mode to NO_DBR_INT" offset="0x5C.31" size="0x0.1" />
	<field name="migration_tag_version_0_eq" descr="Migration tag of tag_version 0.\;Valid only for vport_group_manager ==1 for it&apos;s VFs that are enabled for migration (HCA_CAP.migratable==1), and when !=0." high_bound="3" low_bound="0" offset="0x60.0" size="0x10.0" />
	<field name="ec_vf_base_vport_number" descr="Indicates the base vport of embedded cpu virtual functions (VFs) that are connected to e-switch.\;Valid only if non-zero." offset="0x70.0" size="0x0.16" />
	<field name="min_mkey_log_entity_size_fixed_buffer" descr="Log (base 2) of minimal supported value of log_entity_size in Mkey Context with access_mode=Fixed_Buffer_Size.\;Valid only if HCA_CAP.min_mkey_log_entity_size_fixed_buffer_valid is set, otherwise min_mkey_log_entity_size should apply for this access_mode as well." offset="0x70.16" size="0x0.5" />
	<field name="log_max_hairpin_wqe_num" descr="Maximal value for log_hairpin_wqe_num in hairpin RQ/SQ" offset="0x70.24" size="0x0.5" />
	<field name="max_rqt_vhca_id" descr="Maximal number of different vhca_id supported for RQs across all RQTs (including the vhca_id of RQs on the same function as the RQT itself)." offset="0x74.0" size="0x0.16" />
	<field name="max_mkey_log_entity_size_mtt" descr="Maximum value which may be assigned to the log_entity_size for mkey with access_mode=MTT.\;Value 0 - indicates 31" offset="0x74.16" size="0x0.6" />
	<field name="max_mkey_log_entity_size_fixed_buffer" descr="Maximum value which may be assigned to the log_entity_size for mkey with access_mode=Fixed_Buffer_Size.\;Value 0 - indicates 31" offset="0x74.24" size="0x0.6" />
	<field name="mkey_by_name_reserve_base" descr="Indicates the base index of the Mkey range dedicated for Mkeys created by name. Valid only when mkey_by_name_reserve == 1." offset="0x78.0" size="0x0.24" />
	<field name="mkey_by_name_reserve_log_size" descr="Indicates the log (base 2) size of the Mkey range dedicated for Mkeys created by name. Valid only when mkey_by_name_reserve == 1." offset="0x78.24" size="0x0.6" />
	<field name="mkey_by_name_reserve" descr="if set, Mkeys created by name are allocated from a reserved range. The range is defined by mkey_by_name_reserve_base and mkey_by_name_reserve_log_size. Regular Mkeys are guaranteed to be outside this range." offset="0x78.31" size="0x0.1" />
	<field name="max_pcc_cq_table_size" descr="Maximal number of CQs in PCC_CONFIG object cqn[] table." offset="0x7C.0" size="0x0.8" />
	<field name="num_pcc_backup_process" descr="Number of PCC backup processes supported (not including 1 active process).\;Applicable to both PCC_CONFIG and PCC_NP_CONFIG separately." offset="0x7C.8" size="0x0.4" />
	<field name="pcc_np_multi_probe_type" descr="If set, PCC_NP_CONFIG supports different probe types in different slots, and probe type is indicated in the probe packet CQE." offset="0x7C.12" size="0x0.1" />
	<field name="pcc_ccmad_custom" descr="When set, Probe packet custome header is supported for PCC_CONFIG object" offset="0x7C.13" size="0x0.1" />
	<field name="pcc_probe_packet" descr="When set, Probe packet parameters are supported for PCC_CONFIG and PCC_NP_CONFIG" offset="0x7C.14" size="0x0.1" />
	<field name="pcc_ifa2" descr="When set, IFA2 probe type is supported" offset="0x7C.15" size="0x0.1" />
	<field name="log_max_emu_db_size" descr="Log (base 2) max size of single DB in DB region for emulated devices, given in bytes" offset="0x7C.16" size="0x0.3" />
	<field name="log_min_emu_db_size" descr="Log (base 2) min size of single DB in DB region for emulated devices, given in bytes" offset="0x7C.20" size="0x0.3" />
	<field name="log_max_emu_stride_size" descr="Log (base 2) max stride of single DB in DB region for emulated devices, given in bytes" offset="0x7C.24" size="0x0.4" />
	<field name="log_min_emu_stride_size" descr="Log (base 2) min stride of single DB in DB region for emulated devices, given in bytes" offset="0x7C.28" size="0x0.4" />
	<field name="return_reg_id" descr="Bit map per register_c ID indicating whether this register can be used as a return value for relevant operations such as ASO and Flow Meter. set bit means this register is supported. If the entire field is 0x0, HCA_CAP.flow_meter_reg_id should be used for 8 LSB instead. This field is extended by return_reg_id_47_16\;Bit 0: REG_C_0\;Bit 1: REG_C_1\;Bit 2: REG_C_2\;Bit 3: REG_C_3\;Bit 4: REG_C_4\;Bit 5: REG_C_5\;Bit 6: REG_C_6\;Bit 7: REG_C_7\;Bit 8: REG_C_8\;Bit 9: REG_C_9\;Bit 10: REG_C_10\;Bit 11: REG_C_11\;Bit 12: REG_C_12\;Bit 13: REG_C_13\;Bit 14: REG_C_14\;Bit 15: REG_C_15" enum="REG_C_0=0x1,REG_C_1=0x2,REG_C_2=0x4,REG_C_3=0x8,REG_C_4=0x10,REG_C_5=0x20,REG_C_6=0x40,REG_C_7=0x80,REG_C_8=0x100,REG_C_9=0x200,REG_C_10=0x400,REG_C_11=0x800,REG_C_12=0x1000,REG_C_13=0x2000,REG_C_14=0x4000,REG_C_15=0x8000" offset="0x80.0" size="0x0.16" />
	<field name="max_pcc_np_queues" descr="Maximal number of queues (rq and sq) allowed in PCC_NP_CONFIG obj." offset="0x80.16" size="0x0.8" />
	<field name="pcc_num_probe_slot" descr="The number of PCC probe types that are supported in parallel." offset="0x80.24" size="0x0.3" />
	<field name="rdma_telemetry" descr="if set, RDMA-Telemetry notifications to the SW is supported. See &quot;RDMA Telemetry Notifications&quot; on page 2151" offset="0x80.27" size="0x0.1" />
	<field name="aux_task_service_handover_en" descr="If set, AUX_TASK_SERVICE object supports handover flow." offset="0x80.28" size="0x0.1" />
	<field name="postpone_connected_qp_timeout" descr="If set, POSTPONE_CONNECTED_QP_TIMEOUT command is supported." offset="0x80.29" size="0x0.1" />
	<field name="min_mkey_log_entity_size_fixed_buffer_valid" descr="If set, min_mkey_log_entity_size_fixed_buffer is valid.\;if clr, min_mkey_log_entity_size_mtt should be used instead" offset="0x80.30" size="0x0.1" />
	<field name="cqc_create_armed" descr="When set, CQC.st field can be set to NOTIFICATION_REQUEST_ARMED upon CREATE_CQ" offset="0x80.31" size="0x0.1" />
	<field name="flow_table_hash_type" descr="default hash function type used for hardware flow table.\;0x0 - CRC32 \;Other values reserved" offset="0x84.0" size="0x0.4" />
	<field name="encap_entropy_hash_type" descr="Entropy calculation type for encapsulation functionality (see Section 8.18.4.7, &quot;Encapsulation Entropy&quot;, on page 735).\;0x0: INNER_CRC\;Other values reserved." enum="INNER_CRC=0x0" offset="0x84.4" size="0x0.4" />
	<field name="postpone_connected_qp_timeout_max_num_address" descr="Maximum value supported for num_address in POSTPONE_CONNECTED_QP_TIMEOUT command. Valid only if HCA_CAP. postpone_connected_qp_timeout is set." offset="0x84.8" size="0x0.8" />
	<field name="gen_cqe_reg_count" descr="Higest Index of metadata C register supported for copy into CQE for GEN_CQE action is defined by:\;gen_cqe_start_reg + gen_cqe_reg_count - 1" offset="0x84.16" size="0x0.6" />
	<field name="gen_cqe_start_reg" descr="Lowest Index of metadata C register supported for copy into CQE for GEN_CQE action" offset="0x84.24" size="0x0.6" />
	<field name="max_num_eqs_24b" descr="Maximum number of EQs supported by the device.\;When 0x0, max_num_eqs should be used instead." offset="0x88.0" size="0x0.24" />
	<field name="dpu_cache_invalidate_mmo_log_max_size" descr="Log (Base 2) of maximum size of DPU cache-invalidate operation, given in Bytes. Valid only if HCA_CAP.dpu_cache_invalidate_mmo_qp is set. 0 means no size limit." offset="0x88.24" size="0x0.5" />
	<field name="destination_nop" descr="if set then NOP is supported as a destination for a Flow Table Entry." offset="0x8C.0" size="0x0.1" />
	<field name="pcc_ccmad_custom_max_size" descr="Maximal value supported for CCMAD custom header, given in DWORDs." offset="0x8C.16" size="0x0.8" />
	<field name="rdma_telemetry_max_num_vport_range" descr="Maximal number supported for num_vport_range in Table  1699, &quot;RDMA Telemetry Object Format,&quot; on page  2152" offset="0x8C.24" size="0x0.4" />
	<field name="pcc_steering_log_update_wq_size" descr="log2 (base 2) of the size of the allocated WQ for steering based CC features Flow Update, given in WQEBB\;" offset="0x8C.28" size="0x0.3" />
	<field name="pcc_steering_ext" descr="When set, steering based CC features are enabled" offset="0x8C.31" size="0x0.1" />
	<field name="migration_tag_version_0_geq" descr="Migration tag lower limit. See &quot;Virtual Function Migration&quot; on page 1630\;Valid when migration_tag_version_0_eq is valid." high_bound="3" low_bound="0" offset="0x90.0" size="0x10.0" />
	<field name="rdma_telemetry_notification_type" descr="Bitmask of supported RDMA-Telemetry notification types. Set bit indicates the event is supported. See bit definition in telemetry_notification_type field in Table  1700, &quot;RDMA Telemetry Object Fields,&quot; on page  2153" subnode="uint64" offset="0xA0.0" size="0x8.0" />
	<field name="tool_partial_cap" descr="Bitmask indicating partial capabilities for dedicated tools. Set bit indicates the partial feature is supported\;See Table  3503, &quot;Tool Partial Capability Layout,&quot; on page  4058" offset="0xA8.0" size="0x4.0" />
	<field name="aso32_take_from_reg" descr="Bitmask indicating which ASO type supports the take_from_reg option. Set bit indicates the ASO type supports this option.\;See bit definition in HCA_CAP.execute_aso_type" offset="0xAC.0" size="0x0.16" />
	<field name="aux_task_service_max_num" descr="Maximal number of supported AUX_TASK_SERVICE objects" offset="0xAC.16" size="0x0.16" />
	<field name="aux_task_service_min_resp_wq" descr="Minimal number of concurrent messages Request QP must support for AUX_TASK_SERVICE object" offset="0xB0.0" size="0x0.8" />
	<field name="aux_task_service_log_max_rbs" descr="log (base 2) of the maximal RBS supported for AUX_TASK_SERVICE object, given in bytes." offset="0xB0.8" size="0x0.8" />
	<field name="aux_task_service_profile" descr="Bitmap indicating supported AUX_TASK_SERVICE task profiles. Set bit indicates the corresponding profile is supported. See profile enumeration in task_profile field in Table  707, &quot;AUX_TASK_SERVICE Object Fields,&quot; on page  1139" offset="0xB0.16" size="0x0.16" />
	<field name="flow_entropy_aso_granularity" descr="Log (base 2) of the minimum allocation granularity of FLOW_ENTROPY_ASO Object." offset="0xB4.0" size="0x0.5" />
	<field name="proxy_cmd_tunnel_profile" descr="Bitmap indicating support for PROXY_CMD_TUNNEL profiles. Set bit indicates the respective profile is supported.\;Profile are defined by Table  4828, &quot;Proxy Command Profiles,&quot; on page  4760\;Bit 0: RETX_1" enum="RETX_1=0x1" offset="0xB4.8" size="0x0.8" />
	<field name="conn_track_aso_32_num_log_max" descr="Log (base 2) of the maximum number of CONN_TRACK Objects supported, when using aso_32" offset="0xB4.16" size="0x0.6" />
	<field name="load_balance_id" descr="Identifier of the device Load Balancer instance with which the function is associated.\;It is recommended for link aggregation to be aligned wih instances of the Load Balancer.\;Value 0x0 indicates the function is not associated with a Load Balancer instance.\;" offset="0xB4.24" size="0x0.4" />
	<field name="delegate_vhca_management_profiles" descr="Bitmap of supported profiles in DELEGATE_VHCA_MANAGEMENT and QUERY_DELEGATED_VHCA commands. \;Each set bit indicates supported profile." offset="0xB8.0" size="0x0.16" />
	<field name="flow_semaphore_take_from_reg" descr="If set, FLOW_SEMAPHORE action supports taking parameters from a metadata register C using take_from_reg option" offset="0xB8.25" size="0x0.1" />
	<field name="timer_take_from_reg" descr="If set, TIMER action supports taking parameters from a metadata register C using take_from_reg option" offset="0xB8.26" size="0x0.1" />
	<field name="lag_per_mp_group" descr="If set, device supports LAG creation per multiplane group, see Section  15.4, &quot;LAG for Multiplane,&quot; on page  1642. LAG driver should set current value only if it supports this feature." offset="0xB8.27" size="0x0.1" />
	<field name="aso32_take_from_reg_pair_id_valid" descr="If set, using C register pair as parameter for ASO operations supports a single pair indicated by aso32_take_from_reg_pair_id\;Otherwise, supported pairs are indicated by HCA_CAP.return_reg_id (Odd ID N indicates support for the pair N, N-1)" offset="0xB8.28" size="0x0.1" />
	<field name="function_id_type_vhca_id" descr="When set, function_id_type can be set to VHCA_ID in the following commands:\;QUERY_HCA_CAP\;SET_HCA_CAP\;DISABLE_HCA\;ENABLE_HCA\;QUERY_DRIVER_VERSION\;SYNC_DRIVER_VERSION\;MODIFY_VHCA_STATE\;QUERY_VHCA_STATE" offset="0xB8.29" size="0x0.1" />
	<field name="ingress_egress_esw_vport_connect" descr="When this bit is set, QUERY_VPORT_STATE and MODIFY_VPORT_STATE commands support ingress_connect and egress_connect fields for the driver created vports." offset="0xB8.30" size="0x0.1" />
	<field name="query_adjacent_functions_id" descr="When this bit is set, the device indicates that driver can discover adjacent functions using the command QUERY_ADJACENT_FUNCTIONS_ID." offset="0xB8.31" size="0x0.1" />
	<field name="delegate_vhca_max" descr="This field specifies how many VHCAs a driver can delegate to another VHCA. The limit applies per VHCA. For example, if delegate_vhca_max is 10, the driver can delegate up to 10 VHCAs to each destination VHCA." offset="0xBC.0" size="0x0.16" />
	<field name="delegated_vhca_max" descr="This field specifies maximum number of delegated VHCAs." offset="0xBC.16" size="0x0.16" />
	<field name="delegate_function_type" descr="Bitmap indicated supported function types for management delegation. Set bit indicates this type is supported. Bit definition is aligned with function_type in Table  4634, &quot;FUNCTION_VHCA_RID_INFO Field Descriptions,&quot; on page  4667" offset="0xC0.0" size="0x0.8" />
	<field name="flow_entropy_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of FLOW_ENTROPY_ASO Object, when using aso_32" offset="0xC0.8" size="0x0.6" />
	<field name="conn_track_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of CONN_TRACK_OFFLOAD Object, when using aso_32" offset="0xC0.16" size="0x0.6" />
	<field name="flow_hit_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of FLOW_HIT_ASO Object, when using aso_32" offset="0xC0.24" size="0x0.6" />
	<field name="execute_aso_32_type" descr="Bitmask indicating which ASO type may be used using the execute_aso_32 action.\;See bit definition in execute_aso_type" offset="0xC4.0" size="0x0.16" />
	<field name="flow_entropy_aso_32_num_log_max" descr="Log (base 2) of the maximum number of FLOW_ENTROPY_ASO Objects supported, when using aso_32" offset="0xC4.16" size="0x0.6" />
	<field name="flow_hit_aso_32_num_log_max" descr="Log (base 2) of the maximum number of FLOW_HIT_ASO Objects supported, when using aso_32" offset="0xC4.24" size="0x0.6" />
	<field name="fifo_access_aso_opc_mod" descr="Value of OPC_MOD field in WQE Ctrl Segment for ACESS_ASO WQE that accesses FIFO_ASO" offset="0xC8.0" size="0x0.8" />
	<field name="urisc_mem_aso_granularity" descr="Log (base 2) of the minimum allocation granularity of URISC_MEM_ASO Object." offset="0xC8.8" size="0x0.5" />
	<field name="urisc_mem_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of URISC_MEM_ASO Object, when using aso_32" offset="0xC8.16" size="0x0.6" />
	<field name="urisc_mem_aso_32_num_log_max" descr="Log (base 2) of the maximum number of URISC_MEM_ASO Objects supported, when using aso_32" offset="0xC8.24" size="0x0.6" />
	<field name="urisc_mem_aso_instruction" descr="Bitmask indicating support for URISC instructions for URISC_MEM_ASO objects. Set bit indicates the instruction is supported. Each bit corresponds to the appropriate instruction in Table  253, &quot;URISC Instruction Set,&quot; on page  727" offset="0xCC.0" size="0x4.0" />
	<field name="aso32_take_from_reg_pair_id" descr="Indicates the supported register C pair as parameter for ASO operations. Valid if aso32_take_from_reg_pair_id_valid is set.\;" offset="0xD0.0" size="0x0.5" />
	<field name="fifo_aso_granularity" descr="Log (base 2) of the minimum allocation granularity of FIFO_ASO object" offset="0xD0.8" size="0x0.5" />
	<field name="fifo_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of FIFO_ASO object, when using aso_32" offset="0xD0.16" size="0x0.6" />
	<field name="fifo_aso_32_num_log_max" descr="Log (base 2) of the maximum number of FIFO_ASO objects supported, when using aso_32" offset="0xD0.24" size="0x0.6" />
	<field name="fifo_aso_ctrl_tail_size" descr="Size of FIFO_ASO tail pointer in fifo_ctrl, given in bits" offset="0xD4.0" size="0x0.5" />
	<field name="fifo_aso_ctrl_tail_offset" descr="Offset of FIFO_ASO tail pointer in fifo_ctrl, given in bits from lsb" offset="0xD4.8" size="0x0.5" />
	<field name="fifo_aso_ctrl_head_size" descr="Size of FIFO_ASO head pointer in fifo_ctrl, given in bits" offset="0xD4.16" size="0x0.5" />
	<field name="fifo_aso_ctrl_head_offset" descr="Offset of FIFO_ASO head pointer in fifo_ctrl, given in bits from lsb" offset="0xD4.24" size="0x0.5" />
	<field name="return_reg_id_47_16" descr="Bit map per register_c ID indicating whether this register can be used as a return value for relevant operations such as ASO and Flow Meter. set bit means this register is supported.\;Bit 0: REG_C_16\;Bit 1: REG_C_17\;Bit 2: REG_C_18\;Bit 3: REG_C_19\;Bit 4: REG_C_20\;Bit 5: REG_C_21\;Bit 6: REG_C_22\;Bit 7: REG_C_23\;Bit 8: REG_C_24\;Bit 9: REG_C_25\;Bit 10: REG_C_26\;Bit 11: REG_C_27\;Bit 12: REG_C_28\;Bit 13: REG_C_29\;Bit 14: REG_C_30\;Bit 15: REG_C_31\;Bit 16: REG_C_32\;Bit 17: REG_C_33\;Bit 18: REG_C_34\;Bit 19: REG_C_35\;Bit 20: REG_C_36\;Bit 21: REG_C_37\;Bit 22: REG_C_38\;Bit 23: REG_C_39\;Bit 24: REG_C_40\;Bit 25: REG_C_41\;Bit 26: REG_C_42\;Bit 27: REG_C_43\;Bit 28: REG_C_44\;Bit 29: REG_C_45\;Bit 30: REG_C_46\;Bit 31: REG_C_47" enum="REG_C_16=0x1,REG_C_17=0x2,REG_C_18=0x4,REG_C_19=0x8,REG_C_20=0x10,REG_C_21=0x20,REG_C_22=0x40,REG_C_23=0x80,REG_C_24=0x100,REG_C_25=0x200,REG_C_26=0x400,REG_C_27=0x800,REG_C_28=0x1000,REG_C_29=0x2000,REG_C_30=0x4000,REG_C_31=0x8000,REG_C_32=0x10000,REG_C_33=0x20000,REG_C_34=0x40000,REG_C_35=0x80000,REG_C_36=0x100000,REG_C_37=0x200000,REG_C_38=0x400000,REG_C_39=0x800000,REG_C_40=0x1000000,REG_C_41=0x2000000,REG_C_42=0x4000000,REG_C_43=0x8000000,REG_C_44=0x10000000,REG_C_45=0x20000000,REG_C_46=0x40000000,REG_C_47=0x80000000" offset="0xD8.0" size="0x4.0" />
	<field name="queue_mng_aso_granularity" descr="Log (base 2) of the minimum allocation granularity of QUEUE_MNG_ASO object" offset="0xDC.0" size="0x0.5" />
	<field name="queue_mng_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of QUEUE_MNG_ASO object, when using aso_32" offset="0xDC.8" size="0x0.6" />
	<field name="queue_mng_aso_32_num_log_max" descr="Log (base 2) of the maximum number of QUEUE_MNG_ASO objects supported, when using aso_32" offset="0xDC.16" size="0x0.6" />
	<field name="rtt_timestamp_format" descr="Bitmask per RTT probe, indicating the format of the timestamp. Set bit indicates REAL_TIME, clr bit indicates FREE_RUNNING\;bit 0: RP_RTT_REQUEST_TX\;bit 1: NP_RTT_REQUEST_RX\;bit 2: NP_RTT_RESPONSE_TX\;bit 3: RP_RTT_RESPONSE_RX" enum="RP_RTT_REQUEST_TX=0x1,NP_RTT_REQUEST_RX=0x2,NP_RTT_RESPONSE_TX=0x4,RP_RTT_RESPONSE_RX=0x8" offset="0xDC.28" size="0x0.4" />
	<field name="timer_granularity" descr="Log (base 2) of the minimum allocation granularity of TIMER object" offset="0xE0.0" size="0x0.5" />
	<field name="timer_alloc_log_max" descr="Log (base 2) of the maximum allocation range of TIMER object" offset="0xE0.8" size="0x0.6" />
	<field name="timer_num_log_max" descr="Log (base 2) of the maximum number of TIMER objects supported" offset="0xE0.16" size="0x0.6" />
	<field name="ria_tag_size_max" descr="The maximal tag_size supported for RIA object, given in bytes" offset="0xE0.24" size="0x0.8" />
	<field name="pcc_probe_metadata" descr="Bitmap of supported values for PCC_CONFIG probe_metadata. Set bit indicates the corresponding value is supported." offset="0xE4.0" size="0x0.16" />
	<field name="flow_wqe_post_reg_pair_num_max" descr="Maximum number of register C pairs that can be used as input for FLOW_WQE_POST operation." offset="0xE4.16" size="0x0.8" />
	<field name="ria_num_log_max" descr="The maximal number of RIA objects supported" offset="0xE4.24" size="0x0.6" />
	<field name="ria_reg_id_pair" descr="Bit map per metadata register C ID pair indicating whether this register pair can be used as input\output for RIA object. Set bit indicates the corresponding register pair can be used.\;Bit definition correlates to aso_return_reg_pair in Table  446, &quot;IPSEC_OFFLOAD Object Fields,&quot; on page  926" offset="0xE8.0" size="0x4.0" />
	<field name="flow_semaphore_granularity" descr="Log (base 2) of the minimum allocation granularity of FLOW_SEMAPHORE object" offset="0xEC.0" size="0x0.5" />
	<field name="flow_semaphore_alloc_log_max" descr="Log (base 2) of the maximum allocation range of FLOW_SEMAPHORE object" offset="0xEC.8" size="0x0.6" />
	<field name="flow_semaphore_num_log_max" descr="Log (base 2) of the maximum number of FLOW_SEMAPHORE objects supported" offset="0xEC.16" size="0x0.6" />
	<field name="ria_resource_id_range_max" descr="The maximal resource_id_range supported for resource_index_allocator objec" offset="0xF0.0" size="0x4.0" />
	<field name="flow_wqe_post_reg_id_pair" descr="Bit map per metadata register C ID pair indicating whether this register pair can be used as input for FLOW_WQE_POST operation. Set bit indicates the corresponding register pair can be used.\;Bit definition correlates to aso_return_reg_pair in Table  446, &quot;IPSEC_OFFLOAD Object Fields,&quot; on page  926" offset="0xF4.0" size="0x4.0" />
	<field name="packet_window_anchor" descr="Bitmask indicating which anchors are supported for packet window. each bit represents the corresponding anchor in Table  4246, &quot;Header Anchor List,&quot; on page  4492.\;Set bit indicates the anchor is supported" subnode="uint64" offset="0xF8.0" size="0x8.0" />
</node>

<node name="header_modify_cap_properties" descr="" size="0x80.0" >
	<field name="set_action_field_support" descr="Indicates which packet fields can be modified by SET action." subnode="flow_table_fields_supported" access="RW" offset="0x0.0" size="0x10.0" />
	<field name="set_action_field_support_2" descr="Indicates which packet fields can be modified by SET action." subnode="flow_table_fields_supported_2" access="RW" offset="0x10.0" size="0x10.0" />
	<field name="add_action_field_support" descr="Indicates which packet fields can be modified by ADD action.\;" subnode="flow_table_fields_supported" access="RW" offset="0x20.0" size="0x10.0" />
	<field name="add_action_field_support_2" descr="Indicates which packet fields can be modified by ADD action." subnode="flow_table_fields_supported_2" access="RW" offset="0x30.0" size="0x10.0" />
	<field name="action_src_field_support" descr="Indicates which packet fields are supported as source for COPY/ADD_FIELD/AND_FIELD/XOR_FIELD/SUB_FIELD/FFS operations.\;Fields are supported as destination of the operation if SET operation is supported ( set_action_field_support)." subnode="flow_table_fields_supported" access="RW" offset="0x40.0" size="0x10.0" />
	<field name="action_src_field_support_2" descr="Indicates which packet fields are supported as source for COPY/ADD_FIELD/AND_FIELD/XOR_FIELD/SUB_FIELD/FFS operations.\;Fields are supported as destination of the operation if SET operation is supported ( set_action_field_support_2)." subnode="flow_table_fields_supported_2" access="RW" offset="0x50.0" size="0x10.0" />
</node>

<node name="hotplug_capabilities" descr="" size="0x100.0" >
	<field name="max_hotplug_devices" descr="Maximum number of devices that can be hotpluged." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="log_max_bar_size" descr="Log (base 2) of the maximum bar size for a hotplug device.\;For GENERIC_PCI_DEVICE and TLP device types this field is reserved." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="hotplug_device_types_supported" descr="Bit mask indicates the supported device types that can issue HOTPLUG_DEVICE/HOTUNPLUG_DEVICE commands\;Bit 0: NVME\;Bit 1: VIRTIO_NET\;Bit 2: VIRTIO_BLK\;Bit 4: VIRTIO_FS\;Bit 5: UPT\;Bit 6: GENERIC_PCI_DEVICE\;Bit 7: TLP\;For Virtio Transitional devices, virtio_transitional_device_hotplug field should be check additionally." access="RW" enum="NVME=0x1,VIRTIO_NET=0x2,VIRTIO_BLK=0x4,VIRTIO_FS=0x10,UPT=0x20,GENERIC_PCI_DEVICE=0x40,TLP=0x80" offset="0x0.16" size="0x0.16" />
	<field name="max_total_vfs" descr="The total maximum number of VFs that can be assigned to a single PF created using the HOTPLUG_DEVICE command." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="pci_hotplug_state_info" descr="If set, pci_hotplug_state field in EMULATED_FUNCTIONS_INFO and  GENERIC_EMULATED_FUNCTION_INFO structures is valid for hotplug devices." access="RW" offset="0x4.29" size="0x0.1" />
	<field name="virtio_transitional_device_hotplug" descr="When set, virtio transitional device hotplug (and unplug) functionality is supported. \;Virtio Transitional device supports hotplug if both the device type is supported by hotplug_device_types_supported and virtio_transitional_device_hotplug is set." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="pci_hotplug_state_change" descr="If set, pci_hotplug_state in Emulation Device Objects is supported (Virito Net/Blk,FS and Nvme)." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="max_num_hotplug_pt_function" descr="Maximal number of consecutive functions of a device that can be passed through a single Hotplug Passthrough operation" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="max_num_hotplug_pt_special_region" descr="Maximal number of Special Regions supported for a single Hotplug Passthrough device operation" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="hot_plug_unplug_host_awareness_device_types_supported" descr="Bit mask indicates the device types that support hot plug/unplug with host-awareness. For each supported device type, the emulation management software can explicitly select the HOST_AWARE (mode 0x1) and HOST_UNAWARE (mode 0x2) for hot plug/unplug operations.\;The bitmap layout is identical to that described in the hotplug_device_types_supported field. See Table  1639, &quot;Hotplug Capabilities Field Descriptions,&quot; on page  2085.\;For each device type, the corresponding bit is valid only if the matching bit in hotplug_device_types_supported is set." access="RW" offset="0xC.0" size="0x0.16" />
	<field name="hotplug_power_off_device_types_supported" descr="Bit mask indicates the supported device types that may be created at POWER_OFF state.\;The bitmap layout is identical to that described in the hotplug_device_types_supported field. See Table  1454, &quot;Hotplug Capabilities Field Descriptions,&quot; on page  1813.\;For more information see Figure 124,&quot;HotPlug State Diagram&quot; on page 1889." access="RW" offset="0xC.16" size="0x0.16" />
	<field name="hot_plug_unplug_host_aware_ab_device_types_supported" descr="Bit mask indicates the device types that support hot plug/unplug with host aware attention button. For each supported device type, the emulation management software can select the HOST_AWARE_AB (mode 0x3) for hot plug/unplug operations.\;The bitmap layout is identical to that described in the hotplug_device_types_supported field. See Table  1639, &quot;Hotplug Capabilities Field Descriptions,&quot; on page  2085.\;For each device type, the corresponding bit is valid only if the matching bit in hotplug_device_types_supported is set." access="RW" offset="0x10.0" size="0x0.16" />
	<field name="hotplug_sriov_device_types_supported" descr="Bit mask indicates the device types that can issue HOTPLUG_DEVICE/HOTUNPLUG_DEVICE commands for SR-IOV capable PFs. The bitmap layout is identical to that described in the hotplug_device_types_supported field. See Table  1639, &quot;Hotplug Capabilities Field Descriptions,&quot; on page  2085.For each device type, the corresponding bit is valid only if the matching bit in hotplug_device_types_supported is set." access="RW" offset="0x10.16" size="0x0.16" />
	<field name="emu_max_dynamic_vfs" descr="The maximum number of dynamic VFs that can be assigned across all PFs created using the HOTPLUG_DEVICE command." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="emu_max_first_vf_offset" descr="The maximum First VF offset value that can be configured to a PF created using the HOTPLUG_DEVICE command." access="RW" offset="0x18.0" size="0x0.16" />
	<field name="emu_max_vf_stride" descr="The maximum VF stride value that can be configured to a PF created using the HOTPLUG_DEVICE command." access="RW" offset="0x18.16" size="0x0.8" />
</node>

<node name="ipsec_cap" descr="" size="0x100.0" >
	<field name="log_max_ipsec_offload" descr="Log (base 2) of the maximum IPsec Offload contexts supported" access="RW" offset="0x0.16" size="0x0.5" />
	<field name="ipsec_crypto_esp_aes_gcm_128_decrypt" descr="IPsec decryption using ESP-AES-GCM-128 is supported " access="RW" offset="0x0.25" size="0x0.1" />
	<field name="ipsec_crypto_esp_aes_gcm_256_decrypt" descr="IPsec decryption using ESP-AES-GCM-256 is supported " access="RW" offset="0x0.26" size="0x0.1" />
	<field name="ipsec_crypto_esp_aes_gcm_128_encrypt" descr="IPsec encryption using ESP-AES-GCM-128 is supported " access="RW" offset="0x0.27" size="0x0.1" />
	<field name="ipsec_crypto_esp_aes_gcm_256_encrypt" descr="IPsec encryption using ESP-AES-GCM-256 is supported " access="RW" offset="0x0.28" size="0x0.1" />
	<field name="ipsec_esn" descr="ESN is supported " access="RW" offset="0x0.29" size="0x0.1" />
	<field name="ipsec_crypto_offload" descr="IPsec crypto offload is supported " access="RW" offset="0x0.30" size="0x0.1" />
	<field name="ipsec_full_offload" descr="IPsec full offload is supported " access="RW" offset="0x0.31" size="0x0.1" />
	<field name="log_ipsec_granularity" descr="Log (base 2) of the minimum allocation granularity of IPSEC_OFFLOAD Object range" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="log_ipsec_max_alloc" descr="Log (base 2) of the maximum allocation of a single IPSEC_OFFLOAD Object range" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="max_log_ipsec_full_replay_window" descr="Log (base 2) of the maximum number of bits in the replay window " access="RW" offset="0x4.16" size="0x0.8" />
	<field name="min_log_ipsec_full_replay_window" descr="Log (base 2) of the minimum number of bits in the replay window " access="RW" offset="0x4.24" size="0x0.8" />
	<field name="ipsec_aso_32_num_log_max" descr="Log (base 2) of the maximum IPsec Offload contexts supported, when using aso_32" access="RO" offset="0x8.16" size="0x0.6" />
	<field name="ipsec_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of IPSEC_OFFLOAD Object, when using aso_32" access="RO" offset="0x8.24" size="0x0.6" />
</node>

<node name="macsec_cap" descr="" size="0x100.0" >
	<field name="log_max_macsec_offload" descr="Log (base 2) of the maximum MACSEC Offload contexts supported" access="RW" offset="0x0.16" size="0x0.5" />
	<field name="macsec_crypto_esp_aes_gcm_128_decrypt" descr="MACSEC decryption using ESP-AES-GCM-128 is supported " access="RW" offset="0x0.25" size="0x0.1" />
	<field name="macsec_crypto_esp_aes_gcm_256_decrypt" descr="MACSEC decryption using ESP-AES-GCM-256 is supported " access="RW" offset="0x0.26" size="0x0.1" />
	<field name="macsec_crypto_esp_aes_gcm_128_encrypt" descr="MACSEC encryption using ESP-AES-GCM-128 is supported " access="RW" offset="0x0.27" size="0x0.1" />
	<field name="macsec_crypto_esp_aes_gcm_256_encrypt" descr="MACSEC encryption using ESP-AES-GCM-256 is supported " access="RW" offset="0x0.28" size="0x0.1" />
	<field name="macsec_epn" descr="EPN is supported \;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="max_log_macsec_full_replay_window" descr="Log (base 2) of the maximum number of bits in the replay window " access="RW" offset="0x4.16" size="0x0.8" />
	<field name="min_log_macsec_full_replay_window" descr="Log (base 2) of the minimum number of bits in the replay window " access="RW" offset="0x4.24" size="0x0.8" />
</node>

<node name="nvmeotcp_cap" descr="" size="0x100.0" >
	<field name="version" descr="Bitmask indicates the supported NVMEoTCP versions as reported in ICresp.\;Bit0: version_0" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="crc_tx" descr="If set, CRC32 for transmitted data is supported." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="crc_rx" descr="If set, CRC32 for received data is supported." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="zerocopy" descr="If set, zero copy is supported." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="log_max_nvmeotcp_tag_buffer_size" descr="Log(base 2) of the maximum support tag buffer table size in granularity of 16B" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="log_max_nvmeotcp_tag_buffer_table" descr="Log(base 2) of the maximum support tag buffer tables" access="RW" offset="0x4.8" size="0x0.5" />
</node>

<node name="nvmf_cap" descr="" size="0x100.0" >
	<field name="log_max_namespace_per_xrq" descr="Log (base2) of the maximum number of namespaces supported by XRQ.\;Must be less than HCA_CAP.log_max_namespace_per_xrq" access="RW" offset="0x0.0" size="0x0.5" />
	<field name="passthrough_sqe_rw_service" descr="if set, NVMe-oF offload target supports vendor specific: PASSTHROUGH_SQE_WRITE_PRP (0x80), PASSTHROUGH_SQE_WRITE_PRP_LIST (0x81), PASSTHROUGH_SQE_READ_PRP (0x84) and PASSTHROUGH_SQE_READ_PRP_LIST (0x85) commands." access="RW" offset="0x0.7" size="0x0.1" />
	<field name="log_max_cmd_timeout" descr="Log(base2) of the maximum supported command timeout(in Useconds) in NVMF_BACKEND_CONTROLLER_CONTEXT.\;0 means the device sets a default value.\;Table  1346, &quot;NVMF_BACKEND_CONTROLLER_CONTEXT Input Structure Layout,&quot; on page  1770" access="RW" offset="0x0.8" size="0x0.5" />
	<field name="partial_write_cache" descr="If set, partial_write_cache in NVMe-of Target Offload Context is supported.\;See Table 406, &quot;NVMe-oF Target Offload Context Header Layout,&quot; on page 880." access="RW" offset="0x0.13" size="0x0.1" />
	<field name="report_error_origin" descr="If set, origin error reporting (whether it&quot;s a backend controller error or a frontend controller error) is supported by the NVMf target offload engine. i.e. report_error_origin can be set in XRQ NVMe-oF target offload context." access="RW" offset="0x0.15" size="0x0.1" />
	<field name="log_min_cmd_timeout" descr="Log(base2) of the minimum supported command timeout (in Useconds) in NVMF_BACKEND_CONTROLLER_CONTEXT.\;Table  1346, &quot;NVMF_BACKEND_CONTROLLER_CONTEXT Input Structure Layout,&quot; on page  1770" access="RW" offset="0x0.16" size="0x0.5" />
	<field name="last_req_latency" descr="If set, last_read_req_latency and last_write_req_latency are supported in NVMF_NAMESPACE_COUNTER_SET Object" access="RW" offset="0x0.22" size="0x0.1" />
	<field name="current_q_depth" descr="If set, current_q_depth is supported in NVMF_NAMESPACE_COUNTER_SET Object" access="RW" offset="0x0.23" size="0x0.1" />
	<field name="log_max_frontend_nsid" descr="Log (base 2) of maximum frontend NSID that can be used when attaching namespaces.\;0 means unlimited." access="RW" offset="0x0.24" size="0x0.5" />
	<field name="qp_last_nvme_cqe_reached" descr="if set, XRQ ERROR event support reporting QP_Last_NVMe_CQE_reached type.\;See Section  8.21.8.4, &quot;XRQ Error Event,&quot; on page  837" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="nvmf_stats_report_back" descr="If set, then report back XRQ statistics is supported.\;i.e. nvmf_stats_report_back_en in XRQ context can be set." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="release_xrq_error" descr="If set, RELEASE_XRQ_ERROR command is supported.\;See Section  32.29.8, &quot;RELEASE_XRQ_ERROR - Release XRQ Error,&quot; on page  4603" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="write_offload_rc" descr="If set, NVMe-oF offload of type write for RC transport service is supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.1" size="0x0.1" />
	<field name="read_offload_rc" descr="If set, NVMe-oF offload of type read for RC transport service is supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.2" size="0x0.1" />
	<field name="read_write_offload_rc" descr="If set, NVMe-oF offload of types read and write for RC transport service are supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.3" size="0x0.1" />
	<field name="read_write_flush_offload_rc" descr="If set, NVMe-oF offload of types read, write and flush for RC transport service are supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.4" size="0x0.1" />
	<field name="frontend_namespace_context" descr="If set, QUERY_NVMF_NAMESPACE_CONTEXT command is supported." access="RW" offset="0x4.5" size="0x0.1" />
	<field name="cmd_unknown_namespace_cnt" descr="If set, cmd_unknown_namespace_cnt in NVMe-oF Target Offload Context is supported. Table  406, &quot;NVMe-oF Target Offload Context Header Layout,&quot; on page  880" access="RW" offset="0x4.6" size="0x0.1" />
	<field name="log_min_staging_buffer_size" descr="The minimum size of NVMe-oF staging buffer in bytes is 2^(log_max_staging_buffer_size+nvme_memory_log_page_size)." access="RW" offset="0x4.8" size="0x0.5" />
	<field name="log_max_staging_buffer_size" descr="The maximum size of NVMe-oF staging buffer in bytes is 2^(log_max_staging_buffer_size+nvme_memory_log_page_size)." access="RW" offset="0x4.16" size="0x0.5" />
	<field name="write_offload_dc" descr="If set, NVMe-oF offload of type write for DC transport service is supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.22" size="0x0.1" />
	<field name="read_offload_dc" descr="If set, NVMe-oF offload of type read for DC transport service is supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.23" size="0x0.1" />
	<field name="read_write_offload_dc" descr="If set, NVMe-oF offload of types read and write for DC transport service are supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="read_write_flush_offload_dc" descr="If set, NVMe-oF offload of types read, write and flush for DC transport service are supported.\;See Table 407, &quot;NVMe-oF Target Offload Context Field Descriptions,&quot; on page 882" access="RW" offset="0x4.25" size="0x0.1" />
	<field name="max_icdoff" descr="The maximum supported icdoff in NVMe-oF target offload context header.Table  406, &quot;NVMe-oF Target Offload Context Header Layout,&quot; on page  880." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="log_max_backend_controller_per_xrq" descr="Log (base 2) of the maximum supported backend controllers per XRQ." access="RW" offset="0x8.8" size="0x0.5" />
	<field name="log_max_backend_controller" descr="Log (base 2) of the maximum supported backend controllers." access="RW" offset="0x8.16" size="0x0.5" />
	<field name="log_max_io_size" descr="Log (base 2) of the maximum supported nvmf io size in granularity of bytes." access="RW" offset="0x8.24" size="0x0.5" />
	<field name="log_min_queue_size" descr="Log (base 2) of the minimum supported nvme queue size in granularity of bytes.\;" access="RW" offset="0xC.0" size="0x0.5" />
	<field name="log_max_queue_size" descr="Log (base 2) of the maximum supported nvme queue size in granularity of bytes.\;" access="RW" offset="0xC.8" size="0x0.5" />
	<field name="max_lba_metadata_size" descr="The maximum supported LBA metadata size that can be set in ATTACH_NVMF_NAMESPACE. See Table 1356, &quot;ATTACH_NVMF_NAMESPACE Input Structure Layout,&quot; on page 1774" access="RW" offset="0xC.16" size="0x0.16" />
	<field name="min_ioccsz" descr="The minimum supported iocc size in granularity of 16bytes" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="max_ioccsz" descr="The maximum supported iocc size in granularity of 16bytes" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="nvmf_error_message_size" descr="Size of NVMf Error Message in units of 64B, See Table  408, &quot;NVMF Error Message Layout,&quot; on page  885" access="RW" offset="0x18.0" size="0x0.4" />
	<field name="nvmf_error_reporting" descr="If set, NVMf target offload error reporting is supported. i.e. error_report_qpn can be set in XRQ Context." access="RW" offset="0x18.4" size="0x0.1" />
	<field name="lossless_error_report" descr="If set, lossless error reporting is supported by the NVMf target offload engine. i.e. lossless_error_report can be set in XRQ Context." access="RW" offset="0x18.5" size="0x0.1" />
	<field name="nvmf_error_filters" descr="Bitmask indicates the supported filters for NVMF error reporting by XRQ. To enable specific filters, SW should set nvmf_error_filters in XRQ Context.\;Bit 0: report_CC_check_originated_errors\;Bit 1: report_disk_originated_errors_with_more_bit\;Bit 2: report_disk_originated_errors_without_more_bit\;Bit 3: report_good_disk_completions - (for debug)" access="RW" enum="report_CC_check_originated_errors=0x1,report_disk_originated_errors_with_more_bit=0x2,report_disk_originated_errors_without_more_bit=0x4,report_good_disk_completions=0x8" offset="0x18.16" size="0x0.16" />
	<field name="log_max_metadata_size" descr="Log(base 2) of the maximum supported metadata size per nvmf io transaction." access="RW" offset="0x1C.0" size="0x0.5" />
	<field name="log_max_num_pacers_per_port" descr="Log (base 2) of the maximum number of pacers per port supported by . See Table 1918, &quot;NVMF_TARGET_PACER_DEFAULTS Register Layout,&quot; on page 2285.\;0 means register not supported." access="RW" offset="0x1C.8" size="0x0.4" />
	<field name="min_iorcsz" descr="Minimal allowed value for iorcsz in 16B granularity. \;0 same as 1 (i.e.16B)." access="RW" offset="0x20.0" size="0x4.0" />
	<field name="max_iorcsz" descr="Maximal allowed value for iorcsz in 16B granularity. \;0 same as 1 (i.e.16B)." access="RW" offset="0x24.0" size="0x4.0" />
</node>

<node name="odp_cap" descr="" size="0x100.0" >
	<field name="transport_page_fault_scheme_cap" descr="Transport Page Fault scheme capabilities" subnode="odp_scheme_cap" access="RW" offset="0x0.0" size="0x40.0" />
	<field name="memory_page_fault_scheme_cap" descr="Memory Page Fault scheme capabilities" subnode="odp_scheme_cap" access="RW" offset="0x40.0" size="0x40.0" />
	<field name="mem_page_fault" descr="When set, Memory Page Fault scheme is supported. Set to 1 by SET_HCA_CAP to select this scheme, otherwise Transport Page Fault scheme is used." access="RW" offset="0xC0.31" size="0x0.1" />
</node>

<node name="odp_per_transport_service_cap" descr="" size="0x4.0" >
	<field name="tag_matching" descr="Tag matching operations are supported" access="RO" offset="0x0.25" size="0x0.1" />
	<field name="rmp" descr="Receive on RMP is supported.\;" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="atomic" descr="Atomic operations are supported.\;SW must set same configuration for write and read fields.\;" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="read" descr="RDMA read operations are supported.\;SW must set same configuration for write and read fields.\;" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="write" descr="RDMA write operations are supported.\;SW must set same configuration for write and read fields.\;" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="receive" descr="Receive operations are supported.\;" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="send" descr="Send operations are supported.\;For Transport page fault scheme this field is RW, and its value is applied to all other Transport services.\;" access="RO" offset="0x0.31" size="0x0.1" />
</node>

<node name="odp_scheme_cap" descr="" size="0x40.0" >
	<field name="rget_psv_wqe" descr="When set, RGET_PSV WQEs may point to ODP supported keys" access="RO" offset="0x8.19" size="0x0.1" />
	<field name="get_psv_wqe" descr="When set, GET PSV WQEs may point to ODP supported keys" access="RO" offset="0x8.20" size="0x0.1" />
	<field name="umr_wqe" descr="When set, UMR WQEs with pointer (data segment ) may point to ODP supported keys" access="RO" offset="0x8.21" size="0x0.1" />
	<field name="aso_wqe" descr="When set, ASO WQEs may point to ODP supported keys" access="RO" offset="0x8.22" size="0x0.1" />
	<field name="local_mmo_wqe" descr="When set, LOCAL_MMO WQEs may point to ODP supported keys" access="RO" offset="0x8.23" size="0x0.1" />
	<field name="mmo_wqe" descr="When set, MMO WQEs may point to ODP supported keys" access="RO" offset="0x8.24" size="0x0.1" />
	<field name="page_prefetch" descr="if set, scheme supports page prefetch\;Reserved for Transport Scheme." access="RO" offset="0x8.26" size="0x0.1" />
	<field name="dpa_process_win" descr="When set, DPA process window may be used to access ODP supported keys" access="RO" offset="0x8.28" size="0x0.1" />
	<field name="klm_null_mkey" descr="When set, a KLM indicating the null mkey, will trigger a fault" access="RO" offset="0x8.29" size="0x0.1" />
	<field name="cross_vhca_mkey" descr="When set, crossing_vhca_mkey may lead to a series of keys culminating in an ODP supported key" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="sig" descr="ODP supported with signature hand-over operations. Section  23.11.16, &quot;Signature Handover Programming,&quot; on page  1836." access="RO" offset="0x8.31" size="0x0.1" />
	<field name="rc_odp_caps" descr="RC transport ODP capabilities." subnode="odp_per_transport_service_cap" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="uc_odp_caps" descr="UC transport ODP capabilities." subnode="odp_per_transport_service_cap" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="ud_odp_caps" descr="UD transport ODP capabilities." subnode="odp_per_transport_service_cap" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="xrc_odp_caps" descr="XRC transport ODP capabilities." subnode="odp_per_transport_service_cap" access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="dc_odp_caps" descr="DC transport ODP capabilities." subnode="odp_per_transport_service_cap" access="RW" offset="0x20.0" size="0x4.0" />
</node>

<node name="parse_graph_node_cap" descr="" size="0x100.0" >
	<field name="parse_graph_node_in" descr="Bitmask for the supported protocol headers that programmable parse graph may use as existing nodes in the parse graph and define an input arcs.\;Bit 1: HEAD\;Bit 2: MAC\;Bit 3: IP\;Bit 4: GRE\;Bit 5: UDP\;Bit 6: MPLS\;Bit 7: TCP\;Bit 8: VXLAN_GPE\;Bit 9: GENEVE\;Bit 10: IPSEC_ESP- [Internal]\;Bit 11: IPV4\;Bit 12: IPV6\;Bit 13: PSP\;" access="RW" enum="HEAD=0x2,MAC=0x4,IP=0x8,GRE=0x10,UDP=0x20,MPLS=0x40,TCP=0x80,VXLAN_GPE=0x100,GENEVE=0x200,IPSEC_ESP=0x400,IPV4=0x800,IPV6=0x1000,PSP=0x2000" offset="0x0.0" size="0x4.0" />
	<field name="parse_graph_node_out" descr="Bitmask for the supported protocol headers that programmable parse graph may use as existing nodes in the parse graph and define an output arcs.\;Bit 1: HEAD\;Bit 2: MAC\;Bit 3: IP\;Bit 4: GRE\;Bit 5: UDP\;Bit 6: MPLS\;Bit 7: TCP\;Bit 8: VXLAN_GPE\;Bit 9: GENEVE\;Bit 10: IPSEC_ESP\;Bit 11: IPV4\;Bit 12: IPV6\;Bit 13: PSP\;" access="RW" enum="HEAD=0x2,MAC=0x4,IP=0x8,GRE=0x10,UDP=0x20,MPLS=0x40,TCP=0x80,VXLAN_GPE=0x100,GENEVE=0x200,IPSEC_ESP=0x400,IPV4=0x800,IPV6=0x1000,PSP=0x2000" offset="0x4.0" size="0x4.0" />
	<field name="parse_graph_flow_match_sample_offset_mode" descr="Bitmask indicating which modes are supported for flow_match_sample_offset_mode in PARSE_GRAPH_NODE object. Set bit indicates it is supported.\;Bit 0: FIXED_SIZE\;Bit 1: EXPLICIT_FIELD\;Bit 3: FIELD_LUT" access="RW" enum="FIXED_SIZE=0x1,EXPLICIT_FIELD=0x2,FIELD_LUT=0x8" offset="0x8.0" size="0x0.16" />
	<field name="parse_graph_header_length_mode" descr="Bitmask indicating which modes are supported for header_length_mode in PARSE_GRAPH_NODE object. Set bit indicates it is supported.\;Bit 0: FIXED_SIZE\;Bit 1: EXPLICIT_FIELD\;Bit 3: FIELD_LUT" access="RW" enum="FIXED_SIZE=0x1,EXPLICIT_FIELD=0x2,FIELD_LUT=0x8" offset="0x8.16" size="0x0.16" />
	<field name="parse_graph_flow_match_sample_id_in_out" descr="If set, the device supports setting the value of the flow_match_sample_field_id. If set the device will do best effort t use the same field id" access="RW" offset="0xC.0" size="0x0.1" />
	<field name="zero_size_flex_parser_supported" descr="when set, creation of a parse_graph_node objects with header length mode FIXED_SIZE and header_length_base_value 0 is supported." access="RW" offset="0xC.1" size="0x0.1" />
	<field name="parse_graph_tlv_option_enable" descr="When set, the PARSE_GRAPH_NODE objects TLV Option fields are supported." access="RW" offset="0xC.3" size="0x0.1" />
	<field name="parse_graph_anchor" descr="When set, header_anchor_id can be used to indicate a header insert/remove anchor." access="RW" offset="0xC.4" size="0x0.1" />
	<field name="parse_graph_override_native_arc" descr="If set, Parse Graph arc contradicting the native parser are allowed, and will override them. Overriding a native arc will disable the ability to parse respective header, and performing relevant offloads and accelerations.\;" access="RW" offset="0xC.5" size="0x0.1" />
	<field name="header_length_field_offset_mode" descr="Defines how header_length_field_offset should be used. See definition in similar field in Table  540, &quot;PARSE_GRAPH_NODE Fields,&quot; on page  1034" access="RW" offset="0xC.6" size="0x0.1" />
	<field name="max_num_parse_graph_flow_match_sample" descr="Maximal number of flow match samples supported for a single PARSE_GRAPH_NODE" access="RW" offset="0xC.8" size="0x0.8" />
	<field name="max_num_parse_graph_arc_out" descr="Maximal number of output arcs supported for a single PARSE_GRAPH_NODE" access="RW" offset="0xC.16" size="0x0.8" />
	<field name="max_num_parse_graph_arc_in" descr="Maximal number of input arcs supported for a single PARSE_GRAPH_NODE" access="RW" offset="0xC.24" size="0x0.8" />
	<field name="max_parse_graph_flow_match_sample_field_base_offset_value" descr="Maximal value for match sample field base offset." access="RW" offset="0x10.0" size="0x0.8" />
	<field name="parse_graph_max_next_header_field_size" descr="Maximal value supported for next_header_field_size in \;PARSE_GRAPH_NODE Object." access="RW" offset="0x10.8" size="0x0.5" />
	<field name="parse_graph_lut_log_granularity" descr="Log (base 2) of the minimum allocation granularity of PARSE_GRAPH_LUT Object." access="RW" offset="0x10.13" size="0x0.3" />
	<field name="max_parse_graph_header_length_base_value" descr="Maximal value for header_length_base_value." access="RW" offset="0x10.16" size="0x0.16" />
	<field name="parse_graph_header_length_field_mask_width" descr="Number of valid bits in header_length_field_mask in PARSE_GRAPH_NODE Object, For example, value 5 indicates bits[4:0] are valid." access="RW" offset="0x14.0" size="0x0.8" />
	<field name="max_num_sample_group" descr="Maximal number of sample groups supported for sample_group_id in PARSE_GRAPH_NODE.flow_match_sample.\;Value 0x0 indicates grouping of sample field is not supported" access="RW" offset="0x14.8" size="0x0.5" />
	<field name="parse_graph_max_next_header_field_offset" descr="Maximal value supported for next_header_field_offset in PARSE_GRAPH_NODE Object." access="RW" offset="0x14.16" size="0x0.16" />
	<field name="parse_graph_tlv_option_length_mode" descr="Bitmask indicating which modes are supported for tlv_option_length_mode in PARSE_GRAPH_NODE object. Set bit indicates it is supported. \;Bit 0: FIXED_SIZE \;Bit 1: EXPLICIT_FIELD\;Bit 3: FIELD_LUT\;Other bits are reserved" access="RW" enum="FIXED_SIZE=0x1,EXPLICIT_FIELD=0x2,FIELD_LUT=0x8" offset="0x18.16" size="0x0.16" />
	<field name="parse_graph_tlv_option_max_type_field_size" descr="Maximal value supported for tlv_option_type_field_size in PARSE_GRAPH_NODE Object" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="parse_graph_tlv_option_length_field_mask_width" descr="Number of valid bits in tlv_option_length_field_mask in PARSE_GRAPH_NODE Object, For example, value 5 indicates bits[4:0] are valid." access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="parse_graph_lut_entry_size" descr="Lookup table entry size, given in bits." access="RW" offset="0x1C.16" size="0x0.5" />
	<field name="parse_graph_lut_log_max" descr="Log (base 2) of the maximum total allocation for all PARSE_GRAPH_LUT Objects." access="RW" offset="0x1C.24" size="0x0.4" />
	<field name="parse_graph_lut_size_log_max" descr="Log (base 2) of the maximum allocation of a single PARSE_GRAPH_LUT Object." access="RW" offset="0x1C.28" size="0x0.4" />
	<field name="max_parse_graph_tlv_option_length_base_value" descr="Maximal value supported for tlv_option_length_base_value in PARSE_GRAPH_NODE Object" access="RW" offset="0x20.0" size="0x0.16" />
	<field name="max_parse_graph_tlv_option_type_field_offset" descr="Maximal value supported for tlv_option_offset in PARSE_GRAPH_NODE Object" access="RW" offset="0x20.16" size="0x0.16" />
	<field name="max_parse_tlv_option_length_field_offset" descr="Maximal value supported for tlv_option_length_field_offset in PARSE_GRAPH_NODE Object" access="RW" offset="0x24.0" size="0x0.16" />
	<field name="max_parse_graph_tlv_option_offset" descr="Maximal value supported for tlv_option_offset in PARSE_GRAPH_NODE Object" access="RW" offset="0x24.16" size="0x0.16" />
	<field name="parse_graph_max_header_length_field_offset" descr="Maximal value supported for header_length_field_offset in PARSE_GRAPH_NODE Object.\;If 0x0, the field is not valid." access="RW" offset="0x28.0" size="0x0.16" />
</node>

<node name="per_protocol_networking_offload_caps" descr="" size="0x100.0" >
	<field name="tunnel_stateless_vxlan" descr="If set, Stateless Offloads for VXLAN tunneled (inner) packets are supported.\;The following stateless offloads are supported for the VXLAN tunneled (inner) packets when this flag is on:\;RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering, VLAN insertion." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="tunnel_stateless_gre" descr="If set, Stateless Offloads for GRE L2 or L3 tunneled packets are supported.\;The following stateless offloads are supported for the GRE tunneled (inner) packets when this flag is on:\;RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering, VLAN insertion." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="tunnel_lro_vxlan_old" descr="If set, LRO for VXLAN L2 or L3 tunneled packets is  supported." access="RW" offset="0x0.2" size="0x0.1" />
	<field name="tunnel_lro_gre_old" descr="If set, LRO for GRE tunneled packets is supported." access="RW" offset="0x0.3" size="0x0.1" />
	<field name="tunnel_lso_const_out_ip_id" descr="If set IP Identification field of the outer IP header of segmented by LSO tunneling packet is not incremented." access="RW" offset="0x0.4" size="0x0.1" />
	<field name="enhanced_multi_pkt_send_wqe" descr="If set, Enhanced multi packet send WQE is supported. See Section  3.3.5, &quot;Enhanced Multi-Packet Send WQE Offload,&quot; on page  366" access="RW" offset="0x0.5" size="0x0.1" />
	<field name="scatter_fcs" descr="If set, setting RQ.scatter_fcs is supported. Valid only for Ethernet.\;See Table 231, &quot;RQ Context Format,&quot; on page 685." access="RW" offset="0x0.6" size="0x0.1" />
	<field name="reg_umr_sq" descr="If set, Reg UMR SQ is supported.Table  245, &quot;SQ Context Format,&quot; on page  706" access="RW" offset="0x0.7" size="0x0.1" />
	<field name="rss_ind_tbl_cap" descr="Log (base2) of the maximum RSS indirection table size is supported.\;0 - RSS is not supported." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="wqe_inline_mode" descr="Wqe inline mode\;0: L2 - min inline mode is L2\;1: vport_context - min inline mode is according to nic_vport_context for ETH port and hca_vport_context for IB port.\;2: not_required - inline not required" access="RW" enum="L2=0x0,vport_context=0x1,not_required=0x2" offset="0x0.12" size="0x0.2" />
	<field name="multi_pkt_send_wqe" descr="Multi Packet Send Wqe\;0x0: not_supported\;0x1: Privileged - Supported for privileged SQs only.\;Section  3.3.4, &quot;Multi-Packet Send WQE Offload,&quot; on page  365." access="RW" enum="not_supported=0x0,Privileged=0x1" offset="0x0.14" size="0x0.2" />
	<field name="max_lso_cap" descr="Log (base2) of the maximum LSO message (TCPpayload) supported.\;0 - LSO is not supported." access="RW" offset="0x0.16" size="0x0.5" />
	<field name="self_lb_uc" descr="If set, self-loopback for unicast is supported. \;When self-unicast loopback is supported, it can be enabled per TIR via TIR.self_lb_en field. For more details,Table  223, &quot;TIR Context Format,&quot; on page  674." access="RW" offset="0x0.21" size="0x0.1" />
	<field name="self_lb_mc" descr="If set, self-loopback for multicast is supported. \;When self-multicast loopback is supported it can be enabled per TIR via TIR.self_lb_en field. For more details, see Table  223, &quot;TIR Context Format,&quot; on page  674." access="RW" offset="0x0.22" size="0x0.1" />
	<field name="self_lb_en_modifiable" descr="If set, self_lb_en in TIR Context is modifiable. Table  227, &quot;MODIFY_TIR Bitmask,&quot; on page  680." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="wqe_vlan_insert" descr="If set, WQE Vlan insertion is supported. See Table 3.3.11, &quot;VLAN Insertion/Stripping,&quot; on page 378." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="lro_max_msg_sz_mode" descr="lro_max_message_size_mode reports which LRO max message size mode the device supports.\;0x0: start_from_TCP_header - TIR. lro_max_message_size field sets max LRO IP payload size (TCP header + TCP payload).\;0x1: start_from_L2_header - TIR.lro_max_message_size field sets max LRO message size starting from L2 headers (L2 + L3 + TCP headers + TCP payload).\;Reserved when lro_cap = 0 \;The device allows to limit per TIR the maximum message size LRO is allowed to aggregate. This limit can be set per TIR via lro_max_message_size field. Table 223, &quot;TIR Context Format,&quot; on page 674." access="RW" enum="start_from_TCP_header=0x0,start_from_L2_header=0x1" offset="0x0.25" size="0x0.2" />
	<field name="lro_time_stamp" descr="When set, the adapter supports LRO for segments with a TCP timestamp option.\;Reserved when lro_cap = 0." access="RW" offset="0x0.27" size="0x0.1" />
	<field name="lro_psh_flag" descr="When set, the adapter supports LRO for segments with a TCP PSH bit enabled.\;Reserved when lro_cap = 0 ." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="lro_cap" descr="LRO hardware offload is supported" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="vlan_strip" descr="VLAN stripping offload capability is supported" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="csum_cap" descr="Checksum Offload capability is supported" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tunnel_stateless_geneve_rx" descr="If set, the following receive Stateless Offloads for Geneve tunneled (inner) packets are supported: RSS, Checksum Offloads, Flow Steering. \;On transmit side, Checksum and LSO for Geneve tunneled (inner) packets may be achieved using the Software Parsing mechanism. See Section  3.3.12, &quot;Hypervisor Offloading for Tunneling,&quot; on page  379" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="max_geneve_opt_len" descr="Maximum geneve_opt_len supported. Valid only when tunnel_stateless_geneve_rx==1.\;0x0: 14DW\;0x1: 63DW\;SW must filter GENEVE packets with geneve_opt_len greater that the supported values using Flow Table mechanism.\;\;" access="RW" offset="0x4.1" size="0x0.1" />
	<field name="tunnel_lro_vxlan" descr="If set, LRO for VXLAN L2 or L3 tunneled packets is  supported." access="RW" offset="0x4.2" size="0x0.1" />
	<field name="tunnel_lro_gre" descr="If set, LRO for GRE tunneled packets is supported." access="RW" offset="0x4.3" size="0x0.1" />
	<field name="swp_csum_l4_partial" descr="If set, SWP L4 checksum offload requires SW to place the checksum of the pseudo-header in the L4.checksum field, and the device will add the rest of the checksum.\;" access="RW" offset="0x4.7" size="0x0.1" />
	<field name="max_vxlan_udp_ports" descr="Maximum number of supported vxlan udp ports that can be added by ADD_VXLAN_UDP_DPORT command.\;Note that 0 indicates 4 ports." access="RW" offset="0x4.8" size="0x0.8" />
	<field name="tunnel_stateless_vxlan_gpe_nsh" descr="If set, Stateless Offloads for VXLAN-GPE tunneled packets with NSH header(s) are supported. The following offloads are supported for the inner packets: RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering. In addition, if packet Decapsulation is supported, it is also supported for this kind of encapsulation." access="RW" offset="0x4.17" size="0x0.1" />
	<field name="tunnel_stateless_ip_over_ip_tx" descr="If set, Transmit Stateless Offloads for IPoIP tunneled (inner) packets are supported: TX Checksum Offloads, LSO, Flow Steering. If cleared, checksum and LSO offloads can be achieved using the Software Parsing mechanism." access="RW" offset="0x4.18" size="0x0.1" />
	<field name="tunnel_stateless_ip_over_ip_rx" descr="If set, the following receive Stateless Offloads for IPoIP tunneled (inner) packets are supported: RSS, Checksum Offloads, Flow Steering. In addition, if packet Decapsulation is supported, it is also supported for this kind of encapsulation." access="RW" offset="0x4.19" size="0x0.1" />
	<field name="tunnel_stateless_gtp" descr="Of set, Stateless Offloads for GTP tunneled packets are supported." access="RW" offset="0x4.20" size="0x0.1" />
	<field name="insert_trailer" descr="When set Inserting a packet trailer through WQE is supported (in ETH Segment). See Table  113, &quot;Eth Segment Format,&quot; on page  608" access="RW" offset="0x4.21" size="0x0.1" />
	<field name="tunnel_stateless_ip_over_ip" descr="If set, Stateless Offloads for IP over IP tunneled packets are supported. The following offloads are supported for the inner packets: RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering. In addition, if packet Decapsulation is supported, it is also supported for this kind of encapsulation.\;[Internal] This field is deprecated and replaced with tunnel_stateless_ip_over_ip_rx and tunnel_stateless_ip_over_ip_tx" access="RW" offset="0x4.22" size="0x0.1" />
	<field name="tunnel_stateless_ipv4_over_vxlan" descr="If set, Stateless Offloads for IPv4 over VXLAN tunneled packets are supported. The following offloads are supported for the inner packets: RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering. In addition, if packet Decapsulation is supported, it is also supported for this kind of encapsulation." access="RW" offset="0x4.23" size="0x0.1" />
	<field name="tunnel_stateless_vxlan_gpe" descr="If set, Stateless Offloads for VXLAN-GPE tunneled packets are supported. The following offloads are supported for the inner packets: RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering. In addition, if packet Decapsulation is supported, it is also supported for this kind of encapsulation." access="RW" offset="0x4.24" size="0x0.1" />
	<field name="tunnel_stateless_mpls_over_gre" descr="If set, Stateless Offloads for MPLS (w/ CW) over GRE tunneled packets are supported. The following offloads are supported for the inner packets: RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering. In addition, if packet Decapsulation is supported, it is also supported for this kind of encapsulation." access="RW" offset="0x4.25" size="0x0.1" />
	<field name="tunnel_stateless_mpls_over_udp" descr="If set, Stateless Offloads for MPLS (w/ CW) over UDP tunneled packets are supported. The following offloads are supported for the inner packets: RSS, RX &amp; TX Checksum Offloads, LSO, Flow Steering. In addition, if packet Decapsulation is supported, it is also supported for this kind of encapsulation." access="RW" offset="0x4.26" size="0x0.1" />
	<field name="tunnel_stateless_geneve_tx" descr="If set, Transmit Stateless Offloads for Genenve tunneled packets are supported. The following stateless are supported for the inner packets: TX Checksum Offloads, LSO, Flow Steering." access="RW" offset="0x4.27" size="0x0.1" />
	<field name="cqe_checksum_full" descr="When set, the device checksum calculation reported in the CQE is modified to include all packet fields above layer 2. See Section  3.3.1, &quot;Checksum Offload,&quot; on page  363" access="RW" offset="0x4.28" size="0x0.1" />
	<field name="swp_lso" descr="If set, LSO offload with Software Parsing is supported.\;See Section  3.3.3, &quot;Software Parsing (SWP),&quot; on page  364." access="RW" offset="0x4.29" size="0x0.1" />
	<field name="swp_csum" descr="If set, Checksum offload with Software Parsing is supported.\;See Section  3.3.3, &quot;Software Parsing (SWP),&quot; on page  364." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="swp" descr="If set, Software Parsing is supported.\;See Section  3.3.3, &quot;Software Parsing (SWP),&quot; on page  364 .\;Modifying this field by vhca_resource_manager will affect swp_csum and swp_lso (if supported).\;" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="lro_min_mss_size" descr="Minimal TCP payload size required for LRO. Must be &gt;= 1.\;Reserved when lro_cap = 0." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="packet_merge_timer_supported_periods" descr="Array of supported LRO/SHAMPO timer periods in microseconds. The supported timers are organized in ascending order. \;When requested timer&quot;s period is N timer&quot;s expiration period can fluctuate between N and 2N.\;Reserved when lro_cap = 0 and shampo_cap==0." access="RW" high_bound="3" low_bound="0" offset="0x30.0" size="0x10.0" />
</node>

<node name="port_selection_capabilities" descr="" size="0x1000.0" >
	<field name="port_select_queue_affinity_disabled" descr="When set, LAG master may not choose to use port selection by Queue Affinity, see Section  15.3.3, &quot;Queue Affinity,&quot; on page  1642" access="RW" offset="0x0.12" size="0x0.1" />
	<field name="port_select_flow_table_bypass" descr="When set, device supports bypassing port select table using TIS/QP lag_tx_port_affinity. Device driver setting this field must support setting active_port in CREATE/MODIFY_LAG " access="RW" offset="0x0.13" size="0x0.1" />
	<field name="port_select_eswitch" descr="When set, LAG master may choose to use port selection by the eSwitch Flow Tables, see Section  15.3.2, &quot;Multi Port Eswitch,&quot; on page  1642" access="RW" offset="0x0.14" size="0x0.1" />
	<field name="port_select_flow_table" descr="When set, LAG master may choose to use port selection by Port Selection Flow Tables, see Section  15.3.1, &quot;Port Selection Table,&quot; on page  1641" access="RW" offset="0x0.15" size="0x0.1" />
	<field name="flow_table_properties_port_selection" descr="Capabilities and properties of PORT SELECTION Flow Tables" subnode="flow_table_prop_layout" access="RW" offset="0x40.0" size="0x40.0" />
	<field name="ft_field_support_2_port_selection" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x80.0" size="0x10.0" />
	<field name="ft_field_bitmask_support_2_port_selection" descr="" subnode="flow_table_fields_supported_2" access="RW" offset="0x90.0" size="0x10.0" />
	<field name="header_modify_port_selection" descr="Header modify capabilities of PORT SELECTION Flow Tables" subnode="header_modify_cap_properties" access="RW" offset="0x100.0" size="0x80.0" />
</node>

<node name="psp_cap" descr="" size="0x100.0" >
	<field name="log_max_num_of_psp_spi" descr="Log (Base 2) of the maximum number of SPIs that can be returned at once from the PSP_GET_SPI command." access="RW" offset="0x0.16" size="0x0.5" />
	<field name="psp_crypto_esp_aes_gcm_128_decrypt" descr="PSP decryption using ESP-AES-GCM-128 is supported " access="RW" offset="0x0.25" size="0x0.1" />
	<field name="psp_crypto_esp_aes_gcm_256_decrypt" descr="PSP decryption using ESP-AES-GCM-256 is supported " access="RW" offset="0x0.26" size="0x0.1" />
	<field name="psp_crypto_esp_aes_gcm_128_encrypt" descr="PSP encryption using ESP-AES-GCM-128 is supported " access="RW" offset="0x0.27" size="0x0.1" />
	<field name="psp_crypto_esp_aes_gcm_256_encrypt" descr="PSP encryption using ESP-AES-GCM-256 is supported " access="RW" offset="0x0.28" size="0x0.1" />
	<field name="psp_crypto_offload" descr="PSP crypto offload is supported " access="RW" offset="0x0.30" size="0x0.1" />
	<field name="psp_prog_master_key_num_max" descr="Maximum number of Programmable Master Keys." access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="qos_caps" descr="" size="0x100.0" >
	<field name="flow_meter_reg_id" descr="Bit map per register_c ID indicating whether this register can be used for Flow Meter result. set bit means this register is supported. \;Bit 0: REG_C_0\;Bit 1: REG_C_1\;Bit 2: REG_C_2 \;Bit 3: REG_C_3 \;Bit 4: REG_C_4 \;Bit 5: REG_C_5 \;Bit 6: REG_C_6\;Bit 7: REG_C_7" access="RW" enum="REG_C_0=0x1,REG_C_1=0x2,REG_C_2=0x4,REG_C_3=0x8,REG_C_4=0x10,REG_C_5=0x20,REG_C_6=0x40,REG_C_7=0x80" offset="0x0.0" size="0x0.8" />
	<field name="log_max_flow_meter" descr="Log (base 2) of the maximal number of supported Flow Meter Objects (actual number may be lower)" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="log_esw_max_sched_depth" descr="Log (base 2) of the longest path supported from the root TSAR to the scheduler leaves. For example, value 0x0 indicates the leaves must be attached to the root TSAR." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="packet_pacing_uid" descr="If set, Packet pacing can be set with UID!=0." access="RW" offset="0x0.20" size="0x0.1" />
	<field name="nic_rate_limit" descr="When set, NIC Transmit scheduler supports setting rate limit for scheduling elements. Valid only if nic_sq_scheduling is set." access="RW" offset="0x0.21" size="0x0.1" />
	<field name="nic_bw_share" descr="When set, NIC Transmit scheduler supports non-default BW allocation for scheduling elements. Valid only if nic_sq_scheduling is set." access="RW" offset="0x0.22" size="0x0.1" />
	<field name="nic_sq_scheduling" descr="When set, NIC Transmit scheduler can be built to define QoS between Send Queues (SQs)." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="flow_meter_old" descr="If set, the device supports Flow Meters.\;[Internal] Deprecated by flow_meter due to FW bug in reg C MSB usage. FW should still report it." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="packet_pacing_typical_size" descr="When set, each rate can be associated with a typical packet size." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="packet_pacing_burst_bound" descr="When set, setting an upper bound for packet bursts of a packet pacing rate limit is supported." access="RW" offset="0x0.26" size="0x0.1" />
	<field name="hll" descr="When set, the device supports Head of queue Lifetime Limit for Ethernet ports.\;See" access="RW" offset="0x0.27" size="0x0.1" />
	<field name="esw_rate_limit" descr="When set, eSwitch scheduler supports setting rate limit for scheduling elements." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="esw_bw_share" descr="When set, eSwitch scheduler supports non-default BW allocation for scheduling elements." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="esw_scheduling" descr="If set, E-Switch scheduler can be built to define QoS, see Section  22.1, &quot;Transmit Scheduling,&quot; on page  1690" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="packet_pacing" descr="If set, packet pacing is supported.\;Section  32.37, &quot;QoS Commands - Quality of Service Commands,&quot; on page  4689." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="max_flow_meter_bs_exponent" descr="Maximal value supported for Bucket Size mantissa (CBS or EBS)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="log_max_qos_nic_queue_group" descr="Log (base 2) of the Maximal number of supported Scheduling elements of type QUEUE_GROUP for NIC Transmit Scheduling. Valid only if nic_sq_scheduling is set." access="RW" offset="0x4.16" size="0x0.5" />
	<field name="qos_remap_pp" descr="When set, QoS Remap WQE can be used to move SQ from one PP rate to another" access="RW" offset="0x4.21" size="0x0.1" />
	<field name="esw_cross_esw_sched" descr="If set, E-switch scheduler supports connecting Vports of other E-switch managers" access="RW" offset="0x4.22" size="0x0.1" />
	<field name="flow_meter" descr="If set, the device supports Flow Meters." access="RW" offset="0x4.23" size="0x0.1" />
	<field name="log_nic_max_sched_depth" descr="Log (base 2) of the longest path supported from the root TSAR to the NIC scheduler leaves (QUEUE_GROUPS). For example, value 0x0 indicates the leaves must be attached to the root TSAR. Valid only if nic_sq_scheduling is set." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="packet_pacing_req_uc" descr="If set, packet pacing is supported for requestor side of UC QPs" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="packet_pacing_req_ud" descr="If set, packet pacing is supported for requestor side of UD QPs" access="RO" offset="0x4.29" size="0x0.1" />
	<field name="nic_qp_scheduling" descr="When set, NIC Transmit scheduler can be built to define \;QoS between Queue Pairs (QPs)." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="wqe_rate_pp" descr="If set, PP Context supports wqe_rate_pp taype." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="packet_pacing_max_rate" descr="The maximal rate limit supported by Packet Pacing. Value is given in Kb/s." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="packet_pacing_min_rate" descr="The minimal rate limit supported by Packet Pacing. Value is given in Kb/s." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="packet_pacing_rate_table_size" descr="The size of packet pacing table." access="RW" offset="0x10.0" size="0x0.16" />
	<field name="log_esw_max_rate_limit" descr="Log (base 2) of the maximal number of supported Scheduling Elements with type RATE_LIMIT for the E-Switch Scheduler." access="RW" offset="0x10.16" size="0x0.5" />
	<field name="esw_tsar_type" descr="Bit mask indicates the supported TSAR types in E-Switch Scheduler. Set bit indicates the corresponding type is supported. \;See bit definition in tsar_type field in Table 4690, &quot;TSAR Element Attributes Field Descriptions,&quot; on page 4696" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="esw_element_type" descr="Bit mask indicates the supported Scheduling element types in E-Switch Scheduler. Set bit indicates the corresponding type is supported. \;See bit definition in element_type field in Table 4688, &quot;Scheduling Context Field Descriptions,&quot; on page 4695" access="RW" offset="0x14.16" size="0x0.16" />
	<field name="max_qos_para_vport_old" descr="Maximal number of Para-VPorts supported. \;Value 0x0 indicates Para-VPorts are not supported.\;" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="max_qos_para_vport" descr="Maximal number of Para-VPorts supported. \;Value 0x0 indicates Para-VPorts are not supported.\;" access="RW" offset="0x18.16" size="0x0.16" />
	<field name="max_tsar_bw_share" descr="Maximal value allowed for a TSAR agent BW share (bw_share)" access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="nic_tsar_type" descr="Bit mask indicates the supported TSAR types in NIC Scheduler. Set bit indicates the corresponding type is supported. \;Bit 0: DWRR\;Bit 1: Round Robin\;Bit 2: ETS" access="RW" offset="0x20.0" size="0x0.16" />
	<field name="nic_element_type" descr="Bit mask indicates the supported Scheduling element types in NIC Scheduler. Set bit indicates the corresponding type is supported. \;Bit 0: TSAR\;Bit 2: VPORT_TC\;Bit 3: PARA_VPORT_TCBit 4: QUEUE_GROUP" access="RW" offset="0x20.16" size="0x0.16" />
	<field name="flow_meter_aso_32_num_log_max" descr="log (base 2) of the maximum number of supported \;FLOW_METER_ASO objects when using aso_32" access="RW" offset="0x24.0" size="0x0.6" />
	<field name="log_max_num_meter_aso" descr="log (base 2) of the maximum number of supported \;FLOW_METER_ASO objects" access="RW" offset="0x24.8" size="0x0.5" />
	<field name="log_meter_aso_max_alloc" descr="Log (base 2) of the maximum allocation granular-\;ity of FLOW_METER_ASO Object" access="RW" offset="0x24.16" size="0x0.5" />
	<field name="log_meter_aso_granularity" descr="Log (base 2) of the minimum allocation granularity \;of FLOW_METER_ASO Object." access="RW" offset="0x24.24" size="0x0.5" />
	<field name="flow_meter_aso_32_alloc_log_max" descr="Log (base 2) of the maximum allocation range of FLOW_METER_ASO Object, when using aso_32" access="RW" offset="0x28.8" size="0x0.6" />
	<field name="log_max_qos_esw_scheduling_element" descr="Log (base 2) of the maximal number of supported Scheduling elements of any type for e-switch Scheduler. Valid only if esw_scheduling is set, and value is non-zero." access="RW" offset="0x28.16" size="0x0.5" />
	<field name="log_max_qos_nic_scheduling_element" descr="Log (base 2) of the maximal number of supported Scheduling elements of any type for NIC Scheduler. Valid only if nic_sq_scheduling is set, and value is non-zero." access="RW" offset="0x28.24" size="0x0.5" />
</node>

<node name="query_hca_cap_out" descr="" size="0x1010.0" >
	<field name="status" descr="" offset="0x0.24" size="0x0.8" />
	<field name="syndrome" descr="" offset="0x4.0" size="0x4.0" />
	<field name="capability" descr="Capability structure according to the op_mod. See op_mod field description\;General_Device_Capabilities - Table 3499 on page 3975.\;Ethernet_Offload_Capabilities,\;IPoIB_Basic_Offload_Capabilities,\;IPoIB_Enhanced_Offload_Capabilities - Table 3515 on page 4070 \;ODP_Capabilities - Table 3505 on page 4059.\;Atomic_Capabilities - Table 3511 on page 4064.\;RoCE_Capabilities - Table 3513 on page 4067.\;NIC_Flow_Table_Capabilities - Table 3517 on page 4076\;E-switch_Flow_Table_Capabilities - Table 3519 on page 4084\;E-switch_Capabilities - Table 3529 on page 4109\;Vector_Calc_Capabilities - Table 3531 on page 4113\;0xC: Quality_of_Service_Capabilities - Table 3533 on page 4114\;Debug_Capabilities - Table 3535 on page 4119\;NVMe-oF_Capabilities - Table 1370 on page 1781\;Device_Memory_Capabilities - Table 3539 on page 4121\;NVME_Device_Emulation_Capabilities - Table 1628 on page 2058\;TLS_Capabilities - Table 3541 on page 4125\;DPP_Capabilities - Table 3549 on page 4131\;EVENT_Capabilities - See Table 3551 on page 4133\;IPSEC_Capabilities - Table 3543 on page 4126\;VDPA_EMULATION_Capabilities,\;VIRTIO_NET_EMULATION_Capabilities,\;VIRTIO_BLK_EMULATION_Capabilities,\;VIRTIO_FS_EMULATION_Capabilities -Table 1632 on page 2066\;HOTPLUG_Capabilities - Table 1638 on page 2084\;NVMEOTCP_Capabilities -Table 1380 on page 1794\;CRYPTO_Capabilities - Table 3555 on page 4144\;WQE_BASED_FLOW_TABLE_Capabilities - Table 3553 on page 4135\;PARSE_GRAPH_NODE_Capabilities - Table 3557 on page 4148\;SHAMPO_Capabilities - Table 3559 on page 4153\;PSP_Capabilities - Table 3547 on page 4130\;MACSEC_Capabilities - Table 3545 on page 4128\;General_Device_Capabilities _2- Table 3501 on page 4034\;UPT_Device_Emulation_Capabilities - Table 1630 on page 2063\;EMBEDDED_PROGRAM Capabilities - Table 3561 on page 4154\;PORT_SELECTION_Capabilities - Table 3563 on page 4161\;ADV_VIRTUALIZATION_Capabilities - Table 3565 on page 4163\;GENERIC_DEVICE_EMULATION_Capabilities - Table 1634 on page 2072\;TLP_DEVICE_EMULATION_Capabilities - Table 1636 on page 2078\;ADV_RDMA_Capabilities - Table 3567 on page 4164\;TRANSPORT_SERVICE_PROV_Capabilities - Table 3569 on page 4174\;CC_SERVICE_PROV_Capabilities - Table 3571 on page 4175" subnode="query_hca_cap_out_capability_auto" offset="0x10.0" size="0x1000.0" />
</node>

<node name="query_hca_cap_out_capability_auto" descr="" attr_is_union="1" size="0x1000.0" >
	<field name="adv_rdma_capabilities" descr="" subnode="adv_rdma_capabilities" offset="0x0.0" size="0x800.0" />
	<field name="adv_virtualization_capabilities" descr="" subnode="adv_virtualization_capabilities" offset="0x0.0" size="0x100.0" />
	<field name="atomic_caps" descr="" subnode="atomic_caps" offset="0x0.0" size="0x100.0" />
	<field name="cc_prov_capabilities" descr="" subnode="cc_prov_capabilities" offset="0x0.0" size="0x100.0" />
	<field name="cmd_hca_cap" descr="" subnode="cmd_hca_cap" offset="0x0.0" size="0x100.0" />
	<field name="crypto_caps" descr="" subnode="crypto_caps" offset="0x0.0" size="0x100.0" />
	<field name="debug_cap" descr="" subnode="debug_cap" offset="0x0.0" size="0x44.0" />
	<field name="device_emulation_cap" descr="" subnode="device_emulation_cap" offset="0x0.0" size="0x100.0" />
	<field name="device_mem_cap" descr="" subnode="device_mem_cap" offset="0x0.0" size="0x100.0" />
	<field name="dpp_cap" descr="" subnode="dpp_cap" offset="0x0.0" size="0x100.0" />
	<field name="e_switch_cap" descr="" subnode="e_switch_cap" offset="0x0.0" size="0x100.0" />
	<field name="embedded_program_capabilities" descr="" subnode="embedded_program_capabilities" offset="0x0.0" size="0x800.0" />
	<field name="event_capabilities" descr="" subnode="event_capabilities" offset="0x0.0" size="0x100.0" />
	<field name="flow_table_eswitch_cap" descr="" subnode="flow_table_eswitch_cap" offset="0x0.0" size="0x1000.0" />
	<field name="flow_table_nic_cap" descr="" subnode="flow_table_nic_cap" offset="0x0.0" size="0x1000.0" />
	<field name="generic_dev_emu_capabilities" descr="" subnode="generic_dev_emu_capabilities" offset="0x0.0" size="0x100.0" />
	<field name="hca_caps_2" descr="" subnode="hca_caps_2" offset="0x0.0" size="0x100.0" />
	<field name="hotplug_capabilities" descr="" subnode="hotplug_capabilities" offset="0x0.0" size="0x100.0" />
	<field name="ipsec_cap" descr="" subnode="ipsec_cap" offset="0x0.0" size="0x100.0" />
	<field name="macsec_cap" descr="" subnode="macsec_cap" offset="0x0.0" size="0x100.0" />
	<field name="nvmeotcp_cap" descr="" subnode="nvmeotcp_cap" offset="0x0.0" size="0x100.0" />
	<field name="nvmf_cap" descr="" subnode="nvmf_cap" offset="0x0.0" size="0x100.0" />
	<field name="odp_cap" descr="" subnode="odp_cap" offset="0x0.0" size="0x100.0" />
	<field name="parse_graph_node_cap" descr="" subnode="parse_graph_node_cap" offset="0x0.0" size="0x100.0" />
	<field name="per_protocol_networking_offload_caps" descr="" subnode="per_protocol_networking_offload_caps" offset="0x0.0" size="0x100.0" />
	<field name="port_selection_capabilities" descr="" subnode="port_selection_capabilities" offset="0x0.0" size="0x1000.0" />
	<field name="psp_cap" descr="" subnode="psp_cap" offset="0x0.0" size="0x100.0" />
	<field name="qos_caps" descr="" subnode="qos_caps" offset="0x0.0" size="0x100.0" />
	<field name="roce_cap" descr="" subnode="roce_cap" offset="0x0.0" size="0x100.0" />
	<field name="shampo_cap" descr="" subnode="shampo_cap" offset="0x0.0" size="0x100.0" />
	<field name="tlp_dev_emu_capabilities" descr="" subnode="tlp_dev_emu_capabilities" offset="0x0.0" size="0x100.0" />
	<field name="tls_cap" descr="" subnode="tls_cap" offset="0x0.0" size="0x100.0" />
	<field name="ts_prov_capabilities" descr="" subnode="ts_prov_capabilities" offset="0x0.0" size="0x80.0" />
	<field name="upt_device_emulation_caps" descr="" subnode="upt_device_emulation_caps" offset="0x0.0" size="0x100.0" />
	<field name="vector_calc_caps" descr="" subnode="vector_calc_caps" offset="0x0.0" size="0x100.0" />
	<field name="virtio_emulation_cap" descr="" subnode="virtio_emulation_cap" offset="0x0.0" size="0x100.0" />
	<field name="wqe_based_flow_table_capabilities" descr="" subnode="wqe_based_flow_table_capabilities" offset="0x0.0" size="0x100.0" />
</node>

<node name="roce_cap" descr="" size="0x100.0" >
	<field name="qp_ts_format" descr="Indicates the supported ts_format in QP Context.\;0x0: FREE_RUNNING_TS\;0x1: REAL_TIME_TS\;0x2: FREE_RUNNING_AND_REAL_TIME_TS - both free running real time timestamps are supported." access="RW" enum="FREE_RUNNING_TS=0x0,REAL_TIME_TS=0x1,FREE_RUNNING_AND_REAL_TIME_TS=0x2" offset="0x0.0" size="0x0.2" />
	<field name="query_roce_address_table" descr="If set, QUERY_ROCE_ADDRESS command supports query_table field." access="RW" offset="0x0.21" size="0x0.1" />
	<field name="query_roce_address_other_vport" descr="If set, QUERY_ROCE_ADDRESS command supports other_vport and vport_number fields." access="RW" offset="0x0.22" size="0x0.1" />
	<field name="qp_ooo_rw_default" descr="If set, all QPs will be created by default with ordering semantic OOO_RW. Ordering semantic can be changed per QP by setting QPC.retry_mode to GO_BACK_N and dp_ordering to IB, or by ECE negotiation.\;Set this field to enable this behavior." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="roce_cc_general" descr="When set, cong_protocol R-ROCE GENERAL is supported" access="RW" offset="0x0.24" size="0x0.1" />
	<field name="fl_rc_qp_when_roce_enabled" descr="If set, RC RoCE QP creation with force loopback==1 is\;allowed when RoCE is enabled in nic vport context. On such\;case source and destination network addresses should be\;reserved" access="RW" offset="0x0.25" size="0x0.1" />
	<field name="fl_rc_qp_when_roce_disabled" descr="If set, RC RoCE QP creation with force loopback==1 is allowed when RoCE is disabled in nic vport context. On such case source and destination network addresses should be reserved." access="RW" offset="0x0.26" size="0x0.1" />
	<field name="sw_r_roce_src_udp_port" descr="When 0, the device sets the UDP source port for all egress RoCE v2 packets. The device keeps the source port in the range of r_roce_min_src_udp_port and r_roce_max_src_udp_port.\;When 1, the device supports SW defined UDP source port for RoCE v2 packet. Enable it is by setting this field to 1.\;\;" access="RW" offset="0x0.27" size="0x0.1" />
	<field name="rts2rts_src_addr_index_for_vlan_valid_vlan_id" descr="If set, RTS2RTS command supports setting src_addr_index in primary path. Table  3906, &quot;RTS2RTS_QP Optional Parameters Mask,&quot; on page  4321.\;\;Note: Updating src_addr_index is allowed only if new source address index contains updates in vlan_id, vlan_valid of RoCE Address Layout. Table  4606, &quot;RoCE Address Layout,&quot; on page  4650." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="roce_rx_allow_untagged" descr="If set, received untagged packets are allowed depending on Roce address configurations.\;Table  4607, &quot;RoCE Address Field Descriptions,&quot; on page  4650." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="rts2rts_primary_eth_prio" descr="If set, RTS2RTS command supports setting eth_prio in primary path.\;Table  3906, &quot;RTS2RTS_QP Optional Parameters Mask,&quot; on page  4321." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="roce_apm" descr="If set, Automatic Path Migration is supported." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="roce_version" descr="Bitmask field indicates the supported RoCE Protocol Versions.\;RoCE Versions Bitmask Fields\;Bit 0: version_1_0 - RoCE (v1)\;Bit 1: version_1_5 - R-RoCE IP Based (v1.5)\;Bit 2: version_2_0 - R-RoCE UDP Based (v2)\;When bitmask is zero RoCE is not supported.\;RoCE Address table is allowed to contain only supported RoCE versions and only those packets which belong to supported RoCE protocols can be delivered to RoCE QPs." access="RW" enum="version_1_0=0x1,version_1_5=0x2,version_2_0=0x4" offset="0x10.0" size="0x0.8" />
	<field name="l3_type" descr="Bitmask field indicates the supported L3 types in RoCE\;Bit 0: Grh\;Bit 1: Ipv4\;Bit 2: Ipv6" access="RW" enum="Grh=0x1,Ipv4=0x2,Ipv6=0x4" offset="0x10.16" size="0x0.4" />
	<field name="r_roce_dest_udp_port" descr="For R-RoCE over UDP, UDP.dport." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="r_roce_min_src_udp_port" descr="UDP source port provided by SW must be in the range [r_roce_min_src_udp_port- r_roce_max_src_udp_port]," access="RW" offset="0x18.0" size="0x0.16" />
	<field name="r_roce_max_src_udp_port" descr="Port UDP source port provided by SW must be in the range [r_roce_min_src_udp_port- r_roce_max_src_udp_port]" access="RW" offset="0x18.16" size="0x0.16" />
	<field name="roce_address_table_size" descr="Size of RoCE address table.\;Software allowed to access entries [0..roce_address_table_size-1]" access="RW" offset="0x1C.0" size="0x0.16" />
</node>

<node name="shampo_cap" descr="" size="0x100.0" >
	<field name="shampo_min_mss_size" descr="Minimal packet payload size required for SHAMPO." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="shampo_log_min_reservation_size" descr="Log(base 2) of the minimum value of the field WQ.shampo_log_reservation_size" access="RW" offset="0x0.16" size="0x0.5" />
	<field name="shampo_log_max_reservation_size" descr="Log(base 2) of the maximum value of the field WQ.shampo_log_reservation_size" access="RW" offset="0x0.24" size="0x0.5" />
	<field name="shampo_log_max_headers_entry_size" descr="Log(base 2) of the the maximum value of the WQ.shampo_log_headers_entry_size that is supported." access="RW" offset="0x4.24" size="0x0.5" />
	<field name="shampo_header_split_data_merge" descr="When set, shampo_mode HEADER_SPLIT_DATA_MERGE is supported." access="RW" offset="0x4.30" size="0x0.1" />
	<field name="shampo_header_split" descr="When set, shampo_mode HEADER_SPLIT is supported." access="RW" offset="0x4.31" size="0x0.1" />
</node>

<node name="tlp_dev_emu_capabilities" descr="" size="0x100.0" >
	<field name="max_emulated_devices" descr="Total number of emulated TLP physical functions devices managed by the device emulation manager.\;Information about these devices can be reported by QUERY_EMULATED_FUNCTIONS_INFO. See Table  1577, &quot;QUERY_EMULATED_FUNCTIONS_INFO Input Structure Layout,&quot; on page  2036." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="db_table_handle" descr="When set, the db_table_handle field in the EMULATED_DEV_DB_CQ_MAPPING object is valid." access="RW" offset="0x0.17" size="0x0.1" />
	<field name="tlp_channel_req_dsp_bdf" descr="When set, the dsp_bdf field is present in the TLP Emulation Channel Request Queue Entry and carries a valid host-visible downstream port BDF for requests where dsp_id field identifies a specific downstream port (i.e., dsp_id is not a special value)." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="max_bar_per_device_type" descr="Maximal number of BARs to be configured for a single GENERIC_EMULATION_DEVICE_TYPE." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="bar_1MB" descr="When set, memory space below 1 MB BARs are supported." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="bar_32b" descr="When set, 32bit BARs are supported." access="RW" offset="0x0.29" size="0x0.1" />
	<field name="bar_io" descr="When set, IO BAR type is supported." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="bar_64b" descr="When set, 64bit BARs are supported." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="log_tlp_rsp_gw_stride" descr="Log(base 2) of stride between response gateways within TLP response gateway page, in granularity of bytes." access="RW" offset="0x4.0" size="0x0.5" />
	<field name="log_tlp_rsp_gw_page_stride" descr="Log(base 2) of stride between TLP response gateway pages, in granularity of 4KB." access="RW" offset="0x4.8" size="0x0.5" />
	<field name="nvme_bar_layout" descr="If set, configuring the NVMe bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.20" size="0x0.1" />
	<field name="virtio_blk_bar_layout" descr="If set, configuring the VIRTIO_BLK bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.21" size="0x0.1" />
	<field name="virtio_net_bar_layout" descr="If set, configuring the VIRTIO_NET bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.22" size="0x0.1" />
	<field name="virtio_fs_bar_layout" descr="If set, configuring the VIRTIO_FS bar layout in GENERIC_EMULATION_DEVICE_TYPE is supported." access="RW" offset="0x4.23" size="0x0.1" />
	<field name="max_tlp_generic_device_types" descr="Maximal number of TLP generic device types supported." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="max_bar_regions_per_bar" descr="Maximal number of BAR regions to be configured in a single BAR associated with TLP GENERIC device type." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="max_bar_regions_per_device_type" descr="Maximal number of BAR regions to be configured for a single TLP GENERIC device type." access="RW" offset="0x8.16" size="0x0.16" />
	<field name="max_acg_credits_per_tlp_channel" descr="Indicates the maximum number of Asynchronous Credit Grant (ACG) requests supported per TLP_EMULATION_CHANNEL." access="RW" offset="0xC.0" size="0x0.16" />
	<field name="min_tlp_channel_request_queue_depth" descr="Indicates the minimal required depth of the request queue for a TLP_EMULATION_CHANNEL." access="RW" offset="0xC.16" size="0x0.16" />
	<field name="max_num_msix_per_device" descr="The maximum number of MSIXs that can be set for a TLP emulation device." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="log_max_bar_size" descr="Log (base 2) of the maximal size for to be configured in a single BAR associated with TLP GENERIC device type, given in bytes." access="RW" offset="0x14.16" size="0x0.8" />
	<field name="log_min_bar_size" descr="Log (base 2) of the minimal size for to be configured in a single BAR associated with TLP GENERIC device type, given in bytes." access="RW" offset="0x14.24" size="0x0.8" />
	<field name="tlp_emulation_channel_np_rsp_timeout_max" descr="The maximum value, in milliseconds, that can be configured for the np_rsp_timeout field of a TLP_EMULATION_CHANNEL object. A value of 0 indicates that the non-posted response timeout mechanism is not supported." access="RW" offset="0x18.0" size="0x0.16" />
	<field name="max_num_db_per_device" descr="The maximum number of doorbells that can be set for a TLP emulation device." access="RW" offset="0x18.16" size="0x0.16" />
	<field name="log_max_exp_bar_size" descr="Log (base 2) of the maximum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="log_min_exp_bar_size" descr="Log (base 2) of the minimum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="max_managed_emulated_hosts" descr="The maximal number of managed emulated hosts (PCI links) that can be managed by the device. This is a one based value and valid if HCA_CAP.host_number_ready is set." access="RW" offset="0x1C.16" size="0x0.4" />
	<field name="host_number_ready" descr="If set, host_number_valid and host_number fields are valid for both the QUERY_EMULATED_FUNCTIONS_INFO and HOTPLUG_DEVICE commands, as well as for the TLP_EMULATION_CHANNEL object. Additionally, setting the corresponding device type in the op_mod field of the QUERY_MANAGED_EMULATED_HOSTS_INFO command is supported." access="RW" offset="0x1C.20" size="0x0.1" />
	<field name="always_armed_device_db" descr="When set, configuring always_armed_device_db field in the TLP_DEVICE_EMULATION object is supported." access="RW" offset="0x1C.27" size="0x0.1" />
	<field name="max_emulated_objects_per_vhca_id" descr="The maximum number of device emulated objects that can be created per single vhca_id. This is a zero based value." access="RW" offset="0x1C.28" size="0x0.4" />
	<field name="max_tlp_channel_rsp_gw_element_payload_size" descr="Indicates the maximum allowed total size, in bytes, for the payload (header + data) of the element transmitted through the response gateway of a TLP_EMULATION_CHANNEL." access="RW" offset="0x20.0" size="0x0.16" />
	<field name="tlp_rsp_gw_num_pages" descr="Total number of TLP response gateway pages within the TLP response gateway pages region." access="RW" offset="0x20.16" size="0x0.4" />
	<field name="log_tlp_rsp_gw_num_per_page" descr="Log(base 2) of the total number of TLP response gateways within a single TLP response gateway page." access="RW" offset="0x20.20" size="0x0.4" />
	<field name="pci_caps_0_31_supported" descr="A 32-bit bitmask representing standard PCI capabilities with IDs in the range 0 to 31, supported by the device. Each bit position n corresponds to PCI Capability ID n. If bit n is set, the device supports exposing PCI capability n in the PCI configuration space of a TLP emulation device." access="RW" offset="0x2C.0" size="0x4.0" />
	<field name="pcie_caps_0_63_supported" descr="A 64-bit bitmask representing standard PCIe capabilities with IDs in the range 0 to 63, supported by the device. Each bit position n corresponds to PCIe Capability ID n. If bit n is set, the device supports exposing PCIe capability n in the PCI configuration space of a TLP emulation device." subnode="uint64" access="RW" offset="0x30.0" size="0x8.0" />
	<field name="tlp_rsp_gw_pages_bar_offset" descr="TLP response gateway pages region offset, in bytes, with respect to BAR0 of the device. This region is used to implement response gateways for TLP_EMULATION_CHANNEL objects, enabling SW to device communication." subnode="uint64" access="RW" offset="0x38.0" size="0x8.0" />
	<field name="ingress_mmio_read_hdr_fields_valid" descr="A 32-bit bitmask that indicates the valid fields in the ingress MMIO READ TLP header. If a bit is set, the corresponding field is valid in the ingress MMIO READ TLP header. Non valid fields should be ignored by the SW.\;Bit 0: MMIO_FMT\;Bit 1: MMIO_TYPE\;Bit 2: MMIO_T9\;Bit 3: MMIO_TC\;Bit 4: MMIO_T8\;Bit 5: MMIO_ATTR_2\;Bit 6: MMIO_LN\;Bit 7: MMIO_TH\;Bit 8: MMIO_TD\;Bit 9: MMIO_EP\;Bit 10: MMIO_ATTR_1_0\;Bit 11: MMIO_AT\;Bit 12: MMIO_LENGTH\;Bit 13: MMIO_REQ_ID\;Bit 14: MMIO_TAG\;Bit 15: MMIO_LAST_DW_BE\;Bit 16: MMIO_FIRST_DW_BE\;Bit 17: MMIO_ADDRESS_31_2\;Bit 18: MMIO_ADDRESS_63_32\;Bit 19: MMIO_TLP_PH" access="RW" enum="MMIO_FMT=0x1,MMIO_TYPE=0x2,MMIO_T9=0x4,MMIO_TC=0x8,MMIO_T8=0x10,MMIO_ATTR_2=0x20,MMIO_LN=0x40,MMIO_TH=0x80,MMIO_TD=0x100,MMIO_EP=0x200,MMIO_ATTR_1_0=0x400,MMIO_AT=0x800,MMIO_LENGTH=0x1000,MMIO_REQ_ID=0x2000,MMIO_TAG=0x4000,MMIO_LAST_DW_BE=0x8000,MMIO_FIRST_DW_BE=0x10000,MMIO_ADDRESS_31_2=0x20000,MMIO_ADDRESS_63_32=0x40000,MMIO_TLP_PH=0x80000" offset="0x40.0" size="0x4.0" />
	<field name="ingress_mmio_write_hdr_fields_valid" descr="A 32-bit bitmask that indicates the valid fields in the ingress MMIO WRITE TLP header. If a bit is set, the corresponding field is valid in the ingress MMIO WRITE TLP header. Non valid fields should be ignored by the SW.\;The bitmap layout is identical to that described in the ingress_mmio_read_hdr_fields_valid field." access="RW" offset="0x44.0" size="0x4.0" />
	<field name="bar_db_region_block_size" descr="Minimal allocation data unit for a BAR doorbell region, in bytes." access="RW" offset="0x4C.0" size="0x0.16" />
	<field name="max_bar_db_regions_per_bar" descr="Maximal amount of BAR doorbell regions that can be configured per BAR." access="RW" offset="0x4C.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_db_region" descr="Maximal amount of BAR doorbell region blocks for a single doorbell BAR region." access="RW" offset="0x50.0" size="0x0.16" />
	<field name="max_bar_db_regions_per_device_type" descr="Maximal amount of BAR doorbell regions that can be configured per device type." access="RW" offset="0x50.16" size="0x0.16" />
	<field name="db_region_base_addr_align_log" descr="Log (base 2) of BAR doorbell region base address alignment. Upon BAR doorbell region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x54.0" size="0x0.6" />
	<field name="bar_msix_pba_region_block_size" descr="Minimal allocation data unit for a BAR MSI-X PENDING region, in bytes." access="RW" offset="0x58.0" size="0x0.16" />
	<field name="max_bar_msix_pba_regions_per_bar" descr="Maximal amount of BAR MSI-X PENDING regions that can be configured per BAR." access="RW" offset="0x58.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_msix_pba_region" descr="Maximal amount of BAR MSI-X PENDING region blocks for a single MSI-X PENDING BAR region." access="RW" offset="0x5C.0" size="0x0.16" />
	<field name="max_bar_msix_pba_regions_per_device_type" descr="Maximal amount of BAR MSI-X PENDING regions that can be configured per device type." access="RW" offset="0x5C.16" size="0x0.16" />
	<field name="msix_pba_region_base_addr_align_log" descr="Log (base 2) of BAR MSI-X PENDING region base address alignment. Upon BAR MSI-X PENDING region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x60.0" size="0x0.6" />
	<field name="bar_msix_table_region_block_size" descr="Minimal allocation data unit for a BAR MSI-X VECTOR table region, in bytes." access="RW" offset="0x64.0" size="0x0.16" />
	<field name="max_bar_msix_table_regions_per_bar" descr="Maximal amount of BAR MSI-X VECTOR table regions that can be configured per BAR." access="RW" offset="0x64.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_msix_table_region" descr="Maximal amount of BAR MSI-X VECTOR table region blocks for a single MSI-X VECTOR table BAR region." access="RW" offset="0x68.0" size="0x0.16" />
	<field name="max_bar_msix_table_regions_per_device_type" descr="Maximal amount of BAR MSI-X VECTOR table regions that can be configured per device type." access="RW" offset="0x68.16" size="0x0.16" />
	<field name="msix_table_region_base_addr_align_log" descr="Log (base 2) of BAR MSI-X VECTOR table region base address alignment. Upon BAR MSI-X VECTOR table region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x6C.0" size="0x0.6" />
	<field name="bar_sw_pci_cb_region_block_size" descr="Minimal allocation data unit for a BAR SW_PCI_CB region, in bytes." access="RW" offset="0x70.0" size="0x0.16" />
	<field name="max_bar_sw_pci_cb_regions_per_bar" descr="Maximal amount of BAR SW_PCI_CB regions that can be configured per BAR." access="RW" offset="0x70.16" size="0x0.16" />
	<field name="max_num_blocks_per_bar_sw_pci_cb_region" descr="Maximal amount of BAR SW_PCI_CB region blocks for a single SW_PCI_CB BAR region." access="RW" offset="0x74.0" size="0x0.16" />
	<field name="max_bar_sw_pci_cb_regions_per_device_type" descr="Maximal amount of BAR SW_PCI_CB regions that can be configured per device type." access="RW" offset="0x74.16" size="0x0.16" />
	<field name="sw_pci_cb_region_base_addr_align_log" descr="Log (base 2) of BAR SW_PCI_CB region base address alignment. Upon BAR SW_PCI_CB region configuration, during the creation of the device type, the region base address must be aligned to this value." access="RW" offset="0x78.0" size="0x0.6" />
</node>

<node name="tls_cap" descr="" size="0x100.0" >
	<field name="tls_1_3_aes_gcm_256" descr="If set, indicates support of the aes_gcm cipher with TLS1.3 and 256 bit key" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="tls_1_2_aes_gcm_256" descr="If set, indicates support of the aes_gcm cipher with TLS1.2 and 256 bit key" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="tls_1_3_aes_gcm_128" descr="If set, indicates support of the aes_gcm cipher with TLS1.3 and 128 bit key" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="tls_1_2_aes_gcm_128" descr="If set, indicates support of the aes_gcm cipher with TLS1.2 and 128 bit key" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="ts_prov_capabilities" descr="" size="0x80.0" >
	<field name="ps_format_support" descr="Bitmask indicating supported formats of PATH_SELECT object.\;Bit 0: PS_ARRAY\;Other bits are reserved" offset="0x0.0" size="0x0.4" />
	<field name="ps_array_format" descr="Bitmap indicating supported PS array formats.\;Each bit offset represents the format with the ID defined in PATH_SELECT object ps_array_format" offset="0x0.24" size="0x0.4" />
	<field name="ps_auto_select" descr="If set, PS-based multipathing supports auto selection of PS" offset="0x0.30" size="0x0.1" />
	<field name="ps_cap" descr="If set, PS-based multipathing is supported" offset="0x0.31" size="0x0.1" />
	<field name="ps_array_32_max_size" descr="Maximum number of PS entries supported in a PATH_SELECT object, for format PS_ARRAY_32" offset="0x4.0" size="0x0.16" />
	<field name="rcx_type" descr="Bitmap indicating support for RCX transport types. Set bit indicates the type is supported." offset="0x4.24" size="0x0.8" />
	<field name="ps_entry_32_max_value" descr="Maximum value supported as ps_value in PATH_SELECT object, for format PS_ARRAY_32" offset="0x8.0" size="0x4.0" />
	<field name="ps_array_30_max_size" descr="Maximum number of PS entries supported in a PATH_SELECT object, for format PS_ARRAY_30" offset="0xC.0" size="0x0.16" />
	<field name="ps_entry_30_max_value" descr="Maximum value supported as ps_value in PATH_SELECT object, for format PS_ARRAY_30" offset="0x10.0" size="0x4.0" />
</node>

<node name="uint64" descr="" size="0x8.0" >
	<field name="hi" descr="" offset="0x0.0" size="0x4.0" />
	<field name="lo" descr="" offset="0x4.0" size="0x4.0" />
</node>

<node name="upt_device_emulation_caps" descr="" size="0x100.0" >
	<field name="passthru_reg_size" descr="Size of UPT passthru register in granularity of 4KB" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="db_table_handle" descr="When set, the db_table_handle field in the EMULATED_DEV_DB_CQ_MAPPING object is valid." access="RW" offset="0x0.17" size="0x0.1" />
	<field name="always_armed_device_db" descr="When set, configuring always_armed_device_db field in the UPT_DEVICE_EMULATION object is supported." access="RW" offset="0x0.22" size="0x0.1" />
	<field name="flow_table_metadata_mark_tso" descr="When set, flow_table_metadata_mode supports MARK_TSO mode." access="RW" offset="0x0.23" size="0x0.1" />
	<field name="passthru_reg_bar_id" descr="Identifier of the BAR (0-5) that contains the passthru register." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="upt_emu_dev_eq_extended" descr="When set, EMULATED_DEV_EQ for UPT emulation device supports Extended eq_type" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="inner_rss_report" descr="When set the UPT device emulation supports reporting whether the RSS hash was performed on the inner headers (see &quot;UPT RSS Reporting&quot; on page 1902)" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="queue_period_upon_event" descr="If set, queue_period_mode==upon_event is supported in UPT_SQ." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="queue_period_upon_cqe" descr="If set, queue_period_mode==upon_cqe is supported in UPT_SQ." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="max_emulated_devices" descr="Maximum number of UPT emulated devices" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="supported_features" descr="Supported UPT netVF features:\;These features may be enabled per UPT Device emulation object\;Bit 0: VMK_NETVF_F_RXCSUM - Enable checksum verification when receiving packets.\;Bit 1: VMK_NETVF_F_RSS - Enable RSS\;Bit 2: VMK_NETVF_F_RXVLAN - Enable VLAN tag stripping\;Bit 3: VMK_NETVF_F_LRO - Enable LRO\;Bit 4: VMK_NETVF_F_INNEROFLD - Enable Inner rx checksum verification for encapsulated packets." access="RW" enum="VMK_NETVF_F_RXCSUM=0x1,VMK_NETVF_F_RSS=0x2,VMK_NETVF_F_RXVLAN=0x4,VMK_NETVF_F_LRO=0x8,VMK_NETVF_F_INNEROFLD=0x10" offset="0x4.16" size="0x0.16" />
	<field name="passthru_reg_bar_offset" descr="Offset in bytes of the passthru register with respect to BAR0 of the UPT VF." subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="supported_capabilities" descr="Supported UPT netVF capabilities.\;Capabilities are read-only and provide what the UPT emulation data-path supports. Steering and RSS related should be inferred by software.\;Bit 2: GENEVE_CHECKSUM_OFFLOAD\;Bit 3: GENEVE_TSO\;Bit 4: VXLAN_CHECKSUM_OFFLOAD\;Bit 5: VXLAN_TSO\;Bit 6: GENEVE_OUTER_CHECKSUM_OFFLOAD\;Bit 7: VXLAN_OUTER_CHECKSUM_OFFLOAD" access="RW" enum="GENEVE_CHECKSUM_OFFLOAD=0x4,GENEVE_TSO=0x8,VXLAN_CHECKSUM_OFFLOAD=0x10,VXLAN_TSO=0x20,GENEVE_OUTER_CHECKSUM_OFFLOAD=0x40,VXLAN_OUTER_CHECKSUM_OFFLOAD=0x80" offset="0x10.0" size="0x4.0" />
	<field name="max_num_interrupts" descr="Maximum number of interrupts per UPT emulation device" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="max_managed_emulated_hosts" descr="The maximal number of managed emulated hosts (PCI links) that can be managed by the device. This is a one based value and valid if HCA_CAP.host_number_ready is set." access="RW" offset="0x14.16" size="0x0.4" />
	<field name="host_number_ready" descr="If set, host_number_valid and host_number fields are valid for both the QUERY_EMULATED_FUNCTIONS_INFO and HOTPLUG_DEVICE commands. Additionally, setting the corresponding device type in the op_mod field of the QUERY_MANAGED_EMULATED_HOSTS_INFO command is supported." access="RW" offset="0x14.20" size="0x0.1" />
	<field name="max_num_upt_rqs" descr="Maximum number of UPT RQs that may be created by the emulation manager\;" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="max_num_upt_sqs" descr="Maximum number of UPT SQs that may be created by the emulation manager" access="RW" offset="0x18.16" size="0x0.16" />
	<field name="max_rq_size" descr="Maximum number of descriptors in UPT RQ" access="RW" offset="0x1C.0" size="0x0.16" />
	<field name="max_sq_size" descr="Maximum number of descriptors in UPT SQ" access="RW" offset="0x1C.16" size="0x0.16" />
</node>

<node name="vector_calc_caps" descr="" size="0x100.0" >
	<field name="calc_matrix_type_8bits" descr="If set, then Galois multipliers type of 8bits is supported.\;See Table  137, &quot;V_CALC Segment Format,&quot; on page  623." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="calc_matrix" descr="If set, Calc matrix is supported." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="max_chunk_size" descr="Maximum chunk size supported." access="RW" offset="0x4.0" size="0x0.3" />
	<field name="max_vector_count" descr="Maximum number of vectors supported." access="RW" offset="0x4.16" size="0x0.8" />
	<field name="calc_operation_0" descr="Bit mask indicates which vector calc operations are supported by calc_operation_0 in vector calc segment.\;Bit 1: add operation supported\;Bit 2: max operation supported\;Bit 3: and operation supported\;Bit 4: or operation supported\;Bit 5: xor operation supported\;Bit 6: min operation supported\;Bit 7: swap_endianness operation supported" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="calc_operation_1" descr="Bit mask indicates which vector calc operations are supported by calc_operation_1 in vector calc segment.\;Bit 5: XOR" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="calc_operation_2" descr="Bit mask indicates which vector calc operations are supported by calc_operation_2 in vector calc segment.\;Bit 5: XOR" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="calc_operation_3" descr="Bit mask indicates which vector calc operations are supported by calc_operation_3 in vector calc segment.\;Bit 5: XOR" access="RW" offset="0x14.0" size="0x0.16" />
</node>

<node name="virtio_emulation_cap" descr="" size="0x100.0" >
	<field name="virtio_queue_type" descr="Bitmask indicates the supported Virtio queue types supported.\;Bit 0: SPLIT\;Bit 1: PACKED" access="RW" enum="SPLIT=0x1,PACKED=0x2" offset="0x0.0" size="0x0.8" />
	<field name="event_mode" descr="Bit mask indicates which event modes are supported in VIRTIO Q.\;Bit 0x0: NO_MSIX_MODE\;Bit 0x1: QP_MODE\;Bit 0x2: MSIX_MODE" access="RW" enum="NO_MSIX_MODE=0x1,QP_MODE=0x2,MSIX_MODE=0x4" offset="0x0.8" size="0x0.8" />
	<field name="device_features_bits_mask" descr="For virtio-net and vDPA:\;\;Bit 2: VIRTIO_NET_F_MRG_RXBUF\;Bit 3: VIRTIO_NET_F_HOST_UFO\;Bit 4: VIRTIO_NET_F_HOST_ECN\;Bit 5: VIRTIO_NET_F_GUEST_UFO\;Bit 6: VIRTIO_NET_F_GUEST_ECN\;Bit 7 :VIRTIO_NET_F_GUEST_TSO6\;Bit 8 :VIRTIO_NET_F_GUEST_TSO4\;Bit 9:VIRTIO_NET_F_GUEST_CSUM\;Bit 10:VIRTIO_NET_F_CSUM\;Bit 11: VIRTIO_NET_F_HOST_TSO6\;Bit 12: VIRTIO_NET_F_HOST_TSO4\;\;For virtio-blk:\;Bit 0: VIRTIO_BLK_F_MQ\;Bit 3:VIRTIO_BLK_F_WRITE_ZEROES\;Bit 4:VIRTIO_BLK_F_DISCARD\;Bit 5:VIRTIO_BLK_F_CONFIG_WCE\;Bit 6:VIRTIO_BLK_F_TOPOLOGY\;Bit 8:VIRTIO_BLK_F_BLK_SIZE\;Bit 10:VIRTIO_BLK_F_GEOMETRY\;Bit 11: VIRTIO_BLK_F_SEG_MAX\;Bit 12:VIRTIO_BLK_F_SIZE_MAX\;\;For virtio-fs:\;Bit 0: VIRTIO_FS_F_NOTIFICATION\;" access="RW" offset="0x0.16" size="0x0.13" />
	<field name="virtio_version_1_0" descr="If set device is virtio 1.0 compliant" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="eth_frame_offload_type" descr="When set descriptor converting virtio-net desc to ethernet frames is supported.\;See Virtio emulation offload section." access="RW" offset="0x0.30" size="0x0.1" />
	<field name="desc_tunnel_offload_type" descr="When set descriptor tunneling is supported.\;See Virtio emulation offload section." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="log_doorbell_bar_size" descr="Log(base 2) of doorbell Bar size in granularity of 4KB.\;Valid when doorbell_bar_info is set or for VDPA_Emulation_capabilities." access="RW" offset="0x4.0" size="0x0.5" />
	<field name="virtio_q_index_modify" descr="When set, device supports hw_available_index and hw_used_index update during modify_general_object" access="RW" offset="0x4.5" size="0x0.1" />
	<field name="virtio_net_q_addr_modify" descr="When set, device supports desc_addr, used_addr and available_addr update during modify_general_object." access="RW" offset="0x4.6" size="0x0.1" />
	<field name="vnet_modify_ext" descr="This bit indicates that following fields of the VIRTIO_NET_Q object and VIRTIO_Q objects can be modifiable during MODIFY_GENERAL_OBJECT command: \;virtio_q_type, virtio_version_1_0, virtio_q_mkey,  queue_feature_bit_mask_12_3, query_feature_bit_mask 12_0 and event_mode" access="RW" offset="0x4.7" size="0x0.1" />
	<field name="log_doorbell_stride" descr="Log(base 2) of stride between doorbells in granularity of Bytes.\;Reserved when QUERY_HCA_CAP.opmode is &quot;Virtio_net_emulation_capabilities&quot; or &quot;Virtio_blk_emulation_capabilites&quot;" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="queue_period_upon_event" descr="If set, queue_period_mode==upon_upon_event in VIRTIO_Q is supported." access="RW" offset="0x4.13" size="0x0.1" />
	<field name="queue_period_upon_cqe" descr="If set, queue_period_mode==upon_cqet in VIRTIO_Q is supported." access="RW" offset="0x4.14" size="0x0.1" />
	<field name="dirty_byte_map" descr="If set, dirty_byte_map in virio_net_q is supported." access="RW" offset="0x4.15" size="0x0.1" />
	<field name="max_tunnel_desc" descr="The maximum number of descriptors the device can tunnel on a single SEND operation. \;Valid only when hca_cap.desc_tunnel_offload_type is set." access="RW" offset="0x4.16" size="0x0.16" />
	<field name="doorbell_bar_offset" descr="Start doorbell offset.\;Valid when doorbell_bar_info is set or for VDPA_Emulation_capabilities." subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="max_device_num_virtio_queues" descr="maximum supported virtio queues per virtio device." access="RW" offset="0x10.0" size="0x0.24" />
	<field name="max_virtq_size" descr="Maximum number of descriptors allowed in a device virtqueue" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="max_emulated_devices" descr="Max number of emulated devices that can be managed by the device emulation manager (physical functions devices).\;Information about these devices can be reported by QUERY_\;EMULATED_FUNCTIONS_INFO.0 means capability not valid and SW can assume 256." access="RW" offset="0x14.16" size="0x0.16" />
	<field name="virtio_q_cfg_v2" descr="If set, it indicates that virtio device emulation object supports virtio_q_configuration_v2 layout for object create, query and modification." access="RW" offset="0x18.0" size="0x0.1" />
	<field name="emulated_dev_eq" descr="If set, explicit creation of Emulated Device EQs to be used for MSI-X resources is supported. (These resources are to be created on the emulation manager device). Otherwise, MSI-X resources are internally allocated during the creation of the emulation object." access="RW" offset="0x18.1" size="0x0.1" />
	<field name="emulated_dev_db_cq_map" descr="If set, explicit mapping of Emulated Device doorbell to CQ is supported (for the emulation manager\;device) using EMULATED_DEV_DB_CQ_MAPPING Object. Otherwise, doorbell resources are internally allocated and mapped by the device." access="RW" offset="0x18.2" size="0x0.1" />
	<field name="doorbell_bar_info" descr="When set, log_doorbell_bar_size, doorbell_bar_offset, doorbell_bar_num are valid for Virtio_net/Virtio_blk/Virtio_fs_emulation_capabilites&quot;.\;\;For VDPA, log_doorbell_bar_size and log_doorbell_bar_offset are always valid, and this field only indicates doorbell_bar_num is valid." access="RW" offset="0x18.3" size="0x0.1" />
	<field name="max_num_pf_admin_vq" descr="Maximum number of supported Admin queues per PF device. Value 0x0 indicates Admin queues are not supported. If supported, configuring the VIRTIO_F_ADMIN_VQ feature bit, admin_queue_num and admin_queue_index registers in the VIRTIO_NET/BLK/FS_DEVICE_EMULATION object (PF only) is allowed." access="RW" offset="0x18.4" size="0x0.4" />
	<field name="doorbell_bar_num" descr="indicates which PCI BAR contains the doorbell notification registers.\;Valid when doorbell_bar_info is set." access="RW" offset="0x18.8" size="0x0.3" />
	<field name="freeze_to_rdy_supported" descr="When set, the state transition from FREEZE to RDY for VIRTIO_&lt;NET/BLK/FS&gt;_Q object is supported." access="RW" offset="0x18.11" size="0x0.1" />
	<field name="desc_group_mkey_supported" descr="When set, configuring desc_group_mkey field in the VIRTIO_Q object is supported." access="RW" offset="0x18.12" size="0x0.1" />
	<field name="db_cq_map_set_db_val" descr="If set, explicit mapping of Emulated Device doorbell to CQ supports setting the Doorbell value, as if a Doorbell was posted by the host function." access="RW" offset="0x18.13" size="0x0.1" />
	<field name="dynamic_vf_db_control" descr="When set, configuring dynamic_vf_db_control field in the VIRTIO_NET/BLK/FS_DEVICE_EMULATION object (PF only) is supported." access="RW" offset="0x18.14" size="0x0.1" />
	<field name="db_table_handle" descr="When set, the db_table_handle field in the EMULATED_DEV_DB_CQ_MAPPING object is valid." access="RW" offset="0x18.15" size="0x0.1" />
	<field name="device_features_bits_mask_2" descr="For virtio-net and vDPA:\;\;Bit 0: VIRTIO_NET_F_RSS\;Bit 1: VIRTIO_NET_F_SPEED_DUPLEX\;Bit 2: VIRTIO_NET_F_HASH_REPORT\;" access="RW" enum="VIRTIO_NET_F_RSS=0x1,VIRTIO_NET_F_SPEED_DUPLEX=0x2,VIRTIO_NET_F_HASH_REPORT=0x4" offset="0x18.16" size="0x0.16" />
	<field name="log_max_exp_bar_size" descr="Log (base 2) of the maximum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="log_min_exp_bar_size" descr="Log (base 2) of the minimum size, in bytes, that can be configured for an Exprom BAR of an emulated PF device. A value of 0 indicates that SW controlled Exprom BAR size configuration is not supported and that the device&quot;s default settings are used.\;" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="max_managed_emulated_hosts" descr="The maximal number of managed emulated hosts (PCI links) that can be managed by the device. This is a one based value and valid if HCA_CAP.host_number_ready is set." access="RW" offset="0x1C.16" size="0x0.4" />
	<field name="host_number_ready" descr="If set, host_number_valid and host_number fields are valid for both the QUERY_EMULATED_FUNCTIONS_INFO and HOTPLUG_DEVICE commands. Additionally, setting the corresponding device type in the op_mod field of the QUERY_MANAGED_EMULATED_HOSTS_INFO command is supported." access="RW" offset="0x1C.20" size="0x0.1" />
	<field name="always_armed_device_db" descr="When set, configuring always_armed_device_db field in the VIRTIO_&lt;NET/BLK/FS&gt;_DEVICE_EMULATION object is supported." access="RW" offset="0x1C.27" size="0x0.1" />
	<field name="max_emulated_objects_per_vhca_id" descr="The maximum number of device emulated objects that can be created per single vhca_id. This is a zero based value." access="RW" offset="0x1C.28" size="0x0.4" />
	<field name="umem_1_buffer_param_a" descr="The size of UMEM 1 that need to provide to device when creating VIRTIO_Q is:\;buffer size = umem_1_buffer_param_a * virtio_q size + umem_1_buffer_param_b" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="umem_1_buffer_param_b" descr="" access="RW" offset="0x24.0" size="0x4.0" />
	<field name="umem_2_buffer_param_a" descr="The size of UMEM 2 that need to provide to device when creating VIRTIO_Q is:\;buffer size = umem_2_buffer_param_a * virtio_q size + umem_2_buffer_param_b" access="RW" offset="0x28.0" size="0x4.0" />
	<field name="umem_2_buffer_param_b" descr="" access="RW" offset="0x2C.0" size="0x4.0" />
	<field name="umem_3_buffer_param_a" descr="The size of UMEM 1 that need to provide to device when creating VIRTIO_Q is:\;buffer size = umem_3_buffer_param_a * virtio_q size + umem_3_buffer_param_b" access="RW" offset="0x30.0" size="0x4.0" />
	<field name="umem_3_buffer_param_b" descr="" access="RW" offset="0x34.0" size="0x4.0" />
	<field name="min_num_vf_dynamic_msix" descr="The minimum number of dynamic MSIXs that can be set for an emulated VF" access="RW" offset="0x38.0" size="0x0.16" />
	<field name="max_num_vf_dynamic_msix" descr="The maximum number of dynamic MSIXs that can be set for an emulated VF" access="RW" offset="0x38.16" size="0x0.16" />
	<field name="max_num_pf_msix" descr="The maximum number of MSIXs that can be set for an emulated PF." access="RW" offset="0x3C.0" size="0x0.16" />
</node>

<node name="wqe_based_flow_table_capabilities" descr="" size="0x100.0" >
	<field name="log_max_num_header_modify_pattern" descr="Log (base 2) of the maximum Header Modify Pattern objects supported" access="RW" offset="0x0.0" size="0x0.5" />
	<field name="log_max_num_rtc" descr="Log (base 2) of the maximum RTCs objects supported" access="RW" offset="0x0.8" size="0x0.5" />
	<field name="log_max_num_stc" descr="Log (base 2) of the maximum STCs objects supported" access="RW" offset="0x0.16" size="0x0.5" />
	<field name="log_max_num_ste" descr="Log (base 2) of the maximum STEs objects supported" access="RW" offset="0x0.24" size="0x0.5" />
	<field name="ste_alloc_log_max" descr="Log (base 2) of the maximum allocation of a single STE Object" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="ste_alloc_log_granularity" descr="Log (base 2) of the minimum allocation granularity of STE Object." access="RW" offset="0x4.8" size="0x0.5" />
	<field name="stc_alloc_log_max" descr="Log (base 2) of the maximum allocation of a single STC Object" access="RW" offset="0x4.16" size="0x0.5" />
	<field name="stc_alloc_log_granularity" descr="Log (base 2) of the minimum allocation granularity of STC Object." access="RW" offset="0x4.24" size="0x0.5" />
	<field name="rtc_linear_lookup_table" descr="When set, RTC can be configured as a Section  8.19.4.3, &quot;Linear Lookup Table,&quot; on page  752" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="rtc_hash_split_table" descr="When set, RTC can be configured as a Section  8.19.2, &quot;Hash Table Structure,&quot; on page  749" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="rtc_log_depth_max" descr="Maximal value supported for RTC log_depth" access="RW" offset="0x8.0" size="0x0.5" />
	<field name="rtc_index_mode" descr="Bitmask indicating which RTC update_index_mode are supported\;bit 0: BY_HASH\;bit 1: BY_OFFSET\;" access="RW" enum="BY_HASH=0x1,BY_OFFSET=0x2" offset="0x8.8" size="0x0.5" />
	<field name="rtc_reparse_mode" descr="Bitmask indicating which RTC reparse_mode are supported\;bit 0: REPARSE_NEVER\;bit 1: REPARSE_ALWAYS\;bit 2: REPARSE_BY_STC - When enabled, RTC reparse value is used by default when there is no reparse value through STC\;" access="RW" enum="REPARSE_NEVER=0x1,REPARSE_ALWAYS=0x2,REPARSE_BY_STC=0x4" offset="0x8.16" size="0x0.5" />
	<field name="jump_to_ste_log_max_hash_size" descr="Log (base 2) of the maximum hash table size supported by the JUMP_TO_STE_TABLE STC" access="RW" offset="0x8.24" size="0x0.5" />
	<field name="ste_format" descr="Bitmask indicating which STE formats are supported for WQE based update. Set bit indicates format is supported. Each bit corresponds to the respective value in ste_format_0 field description in Table  658, &quot;RTC Object Fields,&quot; on page  1106" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="max_header_modify_pattern_length" descr="The maximal value for pattern_length in Header Modify Pattern object." access="RW" offset="0xC.16" size="0x0.8" />
	<field name="rtc_index_mode_gen_wqe" descr="Bitmask indicating which RTC update_index_mode are supported when using GENERATE_WQE. See description in rtc_index_mode" access="RW" offset="0xC.24" size="0x0.5" />
	<field name="stc_action_type_63_0" descr="Bitmask indicating which STC action_type are supported (LSB):\;bit 00: NOP\;bit 05: FIELD_COPY\;bit 06: FIELD_SET\;bit 07: FIELD_ADD\;bit 08: REMOVE_WORDS \;bit 09: HEADER_REMOVE\;bit 11: HEADER_INSERT\;bit 12: FLOW_TAG\;bit 14: HEADER_MODIFY_LIST\;bit 16: IPSEC_ENCRYPT\;bit 17: IPSEC_DECRYPT\;bit 18: EXECUTE_ASO\;bit 19: TRAILER\;bit 20: COUNT\;bit 26: EXE_CTRL\;bit 27: FIELD_ADD_FIELD\;bit 31: PSP_ENCRYPT\;bit 32: PSP_DECRYPT\;bit 35: EXECUTE_ASO_32\;bit 39: PACKET_OP\;bit 40: GEN_CQE\;bit 42: FIELD_XOR_FIELD\;bit 43: FIELD_SUB_FIELD\;bit 44: FIELD_AND_FIELD\;bit 45: FIELD_FFS\;bit 47: FLOW_SEMAPHORE\;bit 48: TIMER\;bit 49: RIA\;bit 64: JUMP_TO_STE_TABLE\;bit 65: JUMP_TO_TIR\;bit 66: JUMP_TO_FLOW_TABLE\;bit 67: JUMP_TO_DROP\;bit 68: JUMP_TO_ALLOW\;bit 69: JUMP_TO_VPORT\;bit 70: JUMP_TO_UPLINK\;bit 71: JUMP_TO_FLOW_TABLE_FDB_RX\;bit 72: JUMP_TO_QP\;bit 96: IPSEC_ENCRYPT_FIELD_SET\;bit 97: PSP_DECRYPT_W_KEY\;bit 98: PREP_PASO\;bit 99: FLOW_WQE_POST\;" subnode="uint64" access="RW" enum="NOP=0x1,FIELD_COPY=0x20,FIELD_SET=0x40,FIELD_ADD=0x80,REMOVE_WORDS=0x100,HEADER_REMOVE=0x200,HEADER_INSERT=0x800,FLOW_TAG=0x1000,HEADER_MODIFY_LIST=0x4000,IPSEC_ENCRYPT=0x10000,IPSEC_DECRYPT=0x20000,EXECUTE_ASO=0x40000,TRAILER=0x80000,COUNT=0x100000,EXE_CTRL=0x4000000,FIELD_ADD_FIELD=0x8000000,PSP_ENCRYPT=0x80000000,PSP_DECRYPT=0x1,EXECUTE_ASO_32=0x8,PACKET_OP=0x80,GEN_CQE=0x100,FIELD_XOR_FIELD=0x400,FIELD_SUB_FIELD=0x800,FIELD_AND_FIELD=0x1000,FIELD_FFS=0x2000,FLOW_SEMAPHORE=0x8000,TIMER=0x10000,RIA=0x20000,JUMP_TO_STE_TABLE=0x1,JUMP_TO_TIR=0x2,JUMP_TO_FLOW_TABLE=0x4,JUMP_TO_DROP=0x8,JUMP_TO_ALLOW=0x10,JUMP_TO_VPORT=0x20,JUMP_TO_UPLINK=0x40,JUMP_TO_FLOW_TABLE_FDB_RX=0x80,JUMP_TO_QP=0x100,IPSEC_ENCRYPT_FIELD_SET=0x1,PSP_DECRYPT_W_KEY=0x2,PREP_PASO=0x4,FLOW_WQE_POST=0x8" offset="0x10.0" size="0x8.0" />
	<field name="stc_action_type_127_64" descr="Bitmask indicating which STC action_type are supported (MSB). See description in stc_action_type_63_0" subnode="uint64" access="RW" offset="0x18.0" size="0x8.0" />
	<field name="header_remove_type" descr="Bitmask indicating which header_remove combinations are supported\;bit 0: L2_TUNNEL_DECAP - remove all outer headers up to inner MAC\;bit 1: L3_TUNNEL_DECAP - remove all outer headers up to inner IP\;bit 2: L3_ENCAP - remove all outer headers up to outer IP, preparing for L3 tunnel encapsulation\;bit 3: REMOVE_L2 - remove words at the start of the packet\;bit 4: POP_VLAN - remove words at the start of outermost (1st) VLAN\;bit 7: REMOVE_AFTER_SAMPLE - remove a header following a sampled field\;Other bits are reserved\;bit 8: OUT_REMOVE_IP - remove ip header, supported only when l4 type is TCP or UDP.\;bit 9: REMOVE_OUT_UDP_TCP_START - remove words at the start of the outer UDP or TCP header.\;bit 10: REMOVE_ESP - remove esp header.\;bit 11: REMOVE_FINALIZE - finalizes all removal operations.\;bit 12: DECAP_PSP - remove all outer headers up to and including PSP Header\;bit 13: REMOVE_PSP_TRANSPORT - remove UDP and PSP headers\;bit 14: REMOVE_IB_BTH_OFFSET - remove words after IB_BTH + a non-zero offset.\;bit 15: REMOVE_OUT_L4_PAYLOAD_OFFSET - remove words at the start of the L4 payload with a non-zero offset. Note that L4 checksum may not be correctly calculated following this action\;Other bits are reserved." access="RW" enum="L2_TUNNEL_DECAP=0x1,L3_TUNNEL_DECAP=0x2,L3_ENCAP=0x4,REMOVE_L2=0x8,POP_VLAN=0x10,REMOVE_AFTER_SAMPLE=0x80,OUT_REMOVE_IP=0x100,REMOVE_OUT_UDP_TCP_START=0x200,REMOVE_ESP=0x400,REMOVE_FINALIZE=0x800,DECAP_PSP=0x1000,REMOVE_PSP_TRANSPORT=0x2000,REMOVE_IB_BTH_OFFSET=0x4000,REMOVE_OUT_L4_PAYLOAD_OFFSET=0x8000" offset="0x20.0" size="0x0.16" />
	<field name="header_insert_type" descr="Bitmask indicating which header_insert combinations are supported\;bit 0: ENCAPSULATE - add tunnel headers at the start of the packet\;bit 1: INSERT_L2 - insert words at the start of the packet\;bit 2: INSERT_L2_TAG - insert words after the MAC address\;bit 3: INSERT_IPV6_EXT - insert IPv6 extension header\;bit 4: INSERT_OUT_IP_START - insert words at the start of the outer IP header.\;bit 5: INSERT_OUT_IPV4_END - insert words at the end of the outer IPv4 header.\;bit 6: INSERT_OUT_IPV6_END - insert words at the end of the outer IPv6 header.\;bit 7: INSERT_ESP - insert words at the start of the esp header.\;bit 8: INSERT_IB_TH - insert words after IB BTH. Note that ICRC may not be correctly calculated following this action\;bit 9: INSERT_OUT_L4_PAYLOAD_START - insert words at the start of the L4 payload. Note that L4 checksum may not be correctly calculated following this action\;bit 10: INSERT_IB_BTH_OFFSET - insert words after IB_BTH + a non-zero offset.\;bit 11: INSERT_OUT_L4_PAYLOAD_OFFSET - insert words at the start of the L4 payload with a non-zero offset. Note that L4 checksum may not be correctly calculated following this action\;Other bits are reserved." access="RW" enum="ENCAPSULATE=0x1,INSERT_L2=0x2,INSERT_L2_TAG=0x4,INSERT_IPV6_EXT=0x8,INSERT_OUT_IP_START=0x10,INSERT_OUT_IPV4_END=0x20,INSERT_OUT_IPV6_END=0x40,INSERT_ESP=0x80,INSERT_IB_TH=0x100,INSERT_OUT_L4_PAYLOAD_START=0x200,INSERT_IB_BTH_OFFSET=0x400,INSERT_OUT_L4_PAYLOAD_OFFSET=0x800" offset="0x20.16" size="0x0.16" />
	<field name="trivial_match_definer" descr="Indicates the handle for a Match Definer with no match criteria (always match). Value 0x0 indicates this handle is not supported" access="RW" offset="0x24.0" size="0x4.0" />
	<field name="rtc_max_num_hash_definer_gen_wqe" descr="Applies only for updates through GENERATE_WQE.\;See description in rtc_max_num_hash_definer" access="RW" offset="0x28.0" size="0x0.5" />
	<field name="rtc_max_num_hash_definer" descr="Applies only for updates through GENERATE_WQE.\;See description in rtc_max_num_hash_definer" access="RW" offset="0x28.8" size="0x0.5" />
	<field name="rtc_max_num_match_ste_gen_wqe" descr="Applies only for updates through GENERATE_WQE.\;See description in rtc_max_num_match_ste" access="RW" offset="0x28.16" size="0x0.5" />
	<field name="rtc_max_num_match_ste" descr="Maximal number of STEs representing the match key of an RTC. Value 0x0 indicates a single STE" access="RW" offset="0x28.24" size="0x0.5" />
	<field name="access_index_mode" descr="Bitmask indicating which RTC access_index_mode are supported\;bit 0: BY_HASH\;bit 1: LINEAR\;" access="RW" enum="BY_HASH=0x1,LINEAR=0x2" offset="0x2C.0" size="0x0.8" />
	<field name="stc_max_trailer" descr="Maximal value supported for Trailer STC action. Value given in DW" access="RW" offset="0x2C.8" size="0x0.6" />
	<field name="flow_table_type_2_type" descr="bitmask indicating which transitions between flow table types are supported.\;See bitmask definition flow_table_type_2_type field in Table 3502, &quot;HCA Capabilities 2 Field Descriptions,&quot; on page 4040" access="RW" offset="0x2C.16" size="0x0.8" />
	<field name="stc_flex_param_num_max" descr="The maximal value supported for STC.stc_flex_param_num" access="RW" offset="0x2C.24" size="0x0.4" />
	<field name="flow_timestamp_width_max" descr="The maximal timestamp_width supported in FLOW_TIMESTAMP STC action" access="RW" offset="0x2C.28" size="0x0.4" />
	<field name="ste_format_gen_wqe" descr="Bitmask indicating which STE formats are supported for WQE based update when using GENERATE_WQE. See description in ste_format field" access="RW" offset="0x30.0" size="0x0.16" />
	<field name="stc_execute_aso_type" descr="Bitmask indicating which ASO type may be used using the EXEUTE_ASO STC\;See bit assignment in the description of HCA_CAP.execute_aso_type" access="RW" offset="0x30.16" size="0x0.16" />
	<field name="linear_match_definer_reg_c3" descr="Definer ID required for &quot;Linear Lookup Table&quot; on page 429" access="RW" offset="0x34.0" size="0x4.0" />
	<field name="rtc_array_list_match_definer" descr="When set, using nontrivial match definer in array_list RTC is enabled" access="RW" offset="0x38.0" size="0x0.1" />
	<field name="flow_timestamp_ts_format" descr="Indicates the supported ts_format in flow_timestamp STC action.\;See value definition in sq_ts_format." access="RW" offset="0x38.20" size="0x0.2" />
	<field name="stc_reparse" descr="if set, STC PACKET_OP supports reparse" access="RW" offset="0x38.23" size="0x0.1" />
	<field name="jump_to_ste_table_hash_calc" descr="If set, hash_calc field is supported for JUMP_TO_STE_TABLE STC type" access="RW" offset="0x38.24" size="0x0.1" />
	<field name="stc_flex" descr="If set, Flex STC is supported" access="RW" offset="0x38.25" size="0x0.1" />
	<field name="qp_action_probe_response" descr="if set, STC JUMP_TO_QP supports qp_action PROBE_RESPONSE" access="RW" offset="0x38.26" size="0x0.1" />
	<field name="qp_action_trim_nack" descr="if set, STC JUMP_TO_QP supports qp_action TRIM_NACK" access="RW" offset="0x38.27" size="0x0.1" />
	<field name="stc_insert_action_push_esp" descr="If set, push_esp attribute is supported in insert_action." access="RW" offset="0x38.28" size="0x0.1" />
	<field name="fdb_unified_en" descr="If set, FDB_UNIFIED domain is supported." access="RW" offset="0x38.29" size="0x0.1" />
	<field name="fdb_rx_set_flow_tag_stc" descr="If set, FLOW_TAG stc is allowed in FDB_RX. FLOW_TAG is cleared for non e-switch VPORTs" access="RW" offset="0x38.30" size="0x0.1" />
	<field name="fdb_jump_to_tir_stc" descr="If set, JUMP_TO_TIR stc is allowed in FDB" access="RW" offset="0x38.31" size="0x0.1" />
	<field name="stc_execute_aso_32_type" descr="Bitmask indicating which ASO type may be used using the EXEUTE_ASO_32 STC\;See bit assignment in the description of HCA_CAP.execute_aso_type" access="RW" offset="0x3C.16" size="0x0.16" />
	<field name="stc_flex_action_type_63_0" descr="Bitmask indicating which STC &quot;action_type&quot;s are supported for Flex STC (LSB):\;See bit definition in stc_action_type_63_0" subnode="uint64" access="RW" offset="0x40.0" size="0x8.0" />
	<field name="stc_flex_action_type_127_64" descr="Bitmask indicating which STC &quot;action_type&quot;s are supported for Flex STC (MSB).\;See bit definition in stc_action_type_63_0" subnode="uint64" access="RW" offset="0x48.0" size="0x8.0" />
	<field name="flow_timestamp_offset_post_l4_max" descr="Maximal supported offset for flow_timestamp FLOW_TS_POST_L4" access="RW" offset="0x50.0" size="0x0.9" />
	<field name="flow_timestamp_offset" descr="Bitmask indicating which anchors and offsets are supported for flow_timestamp \;Bit 0: FLOW_TS_POST_L4 - timestamp inserted after TCP/UDPP header, using TCP_UDP_START anchor and offset. offset must also comply with in flow_timestamp_offset_post_l4_max\;Other values are reserved" access="RW" offset="0x50.16" size="0x0.8" />
</node>

<node name="root" size="0x1010.0" descr="" >
	<field name="hca_cap_table_hca_ext_Nodes" offset="0x0.0" size="0x1010.0" subnode="hca_cap_table_hca_ext_Nodes" descr="" />
</node>

<node name="hca_cap_table_hca_ext_Nodes" size="0x1010.0" attr_is_union="1" descr="" >
	<field name="query_hca_cap_out" offset="0x0.0" size="0x1010.0" subnode="query_hca_cap_out" descr="" />
</node>
</NodesDefinition>
