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
<info source_doc_name="" source_doc_version="Rev 0.10.029" />
<node name="High_bit_error_rate_configuration_page_ext" descr="" size="0x4.0" >
	<field name="en" descr="enable hi_ber monitoring" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="High_symbol_error_rate_configuration_page_ext" descr="" size="0x8.0" >
	<field name="en" descr="enable hi_ser monitoring and action" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="symbol_err_thr" descr="Number of errored symbols in 8192 codewords window to declare hi_ser" access="RW" offset="0x4.0" size="0x0.24" />
	<field name="hi_ser_action" descr="Select hi_ser consequent action:\;0x00: no action\;0x01: alignment loss\;0x02: hi_ber action" access="RW" offset="0x4.29" size="0x0.2" />
</node>

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
	<field name="port_xmit_discards_high" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="port_xmit_discards_low" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x34.0" size="0x4.0" />
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
	<field name="qp1_dropped_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="qp1_dropped_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x90.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x94.0" size="0x4.0" />
	<field name="port_multicast_xmit_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="port_multicast_xmit_pkts_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xA4.0" size="0x4.0" />
	<field name="port_multicast_rcv_pkts_high" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xA8.0" size="0x4.0" />
	<field name="port_multicast_rcv_pkts_low" descr="For counter description please refer to the InfiniBand specification" access="RO" offset="0xAC.0" size="0x4.0" />
</node>

<node name="IB_portcntrs_attribute_grp_data_ext" descr="" size="0xf8.0" >
	<field name="link_downed_counter" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="link_error_recovery_counter" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="symbol_error_counter" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="port_rcv_remote_physical_errors" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="port_rcv_errors" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="port_xmit_discards" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="port_rcv_switch_relay_errors" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="excessive_buffer_overrun_errors" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0xC.0" size="0x0.4" />
	<field name="local_link_integrity_errors" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0xC.4" size="0x0.4" />
	<field name="port_rcv_constraint_errors" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="port_xmit_constraint_errors" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="vl_15_dropped" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="qp1_dropped" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="port_xmit_data" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="port_rcv_data" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="port_xmit_pkts" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="port_rcv_pkts" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_xmit_wait" descr="For counter description please refer to the InfiniBand specification\;" access="RO" offset="0x24.0" size="0x4.0" />
</node>

<node name="MCFS_ext" descr="" size="0x20.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="freq" descr="Module Frequency\;0: 400_KHz(default)\;1: 1_MHz\;2: 100_KHz\;3: Reserved" access="RW" offset="0x4.0" size="0x0.2" />
</node>

<node name="MFMI_ext" descr="" size="0x18.0" >
	<field name="fm_state" descr="Specifies the current FM state.\;FM states as follows:\;0: Reserved\;1: Offline\;2: Standby\;3: Configured\;4: Reserved (Timeoout)\;5: Error" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="time_point_last_restart" descr="Epoch timestamp of FM restart, in seconds.\;This value is stable as long FM didn&apos;t restart." subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
	<field name="duration_since_last_restart" descr="Time passed since last restart, in seconds.\;Should be incremented in each report." subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="MICM_ext" descr="" size="0x28.0" >
	<field name="interrupts_mask" descr="Interrupts Mask\;Enabling or disabling bits in the MICM register will determine whether the interrupt GPIO is triggered when an interrupt occurs. The status of any interrupt bit can always be read (or cleared) via the MICV register. By default all interrupts are enabled." access="RW" high_bound="7" low_bound="0" offset="0x4.0" size="0x20.0" />
</node>

<node name="MICV_ext" descr="" size="0x24.0" >
	<field name="op" descr="Operation\;0: Read\;1: Read and clear" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="int_vec" descr="Interrupts Vector\;bit0: Thermal. For more info read also Table 179, &quot;MTEWE - Management Temperature Extended Warning Event Register Layout,&quot; on page 199\;bit1: Ready for PVS setting\;bit2: Reserved\;bit3: Graceful reset Ack\;\;bit5: FW Assert [DWIP]\;bit6-31: Reserved\;Other bits are reserved" access="RO" high_bound="7" low_bound="0" offset="0x4.0" size="0x20.0" />
</node>

<node name="MLPC_ext" descr="" size="0x40.0" >
	<field name="lp_msb" descr="port MSB\;Used to identify the L1 controller associated to the desired HW counters." access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="port\;Used to identify the L1 controller associated to the desired HW counters." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cnt_64bit" descr="Bit mask to configure extended 64 bits long counters.\;Bit per even HW counter. When bit [i] is set, counter[2i] and counter[2i+1] will be used to form a 64-bit counter.\;The odd counter cnt_sel[2i+1], will serve as the selector to configure the 64 bit counter.\;The odd counter cnt_val[2i+1], will serve as the LSB of the counter.\;The even counter cnt_val[2i], will serve as the MSB of the counter." access="RW" offset="0x4.0" size="0x0.4" />
	<field name="stop_at_ff" descr="When set, when one of the perf counters reaches FFs, all the counters will stop counting." access="RW" offset="0x4.29" size="0x0.1" />
	<field name="counter_rst" descr="Force reset for all the counters. \;Must be 0 for Get operation." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="counter_en" descr="Enable for the HW counters" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="force_count_mask" descr="Force count bit mask, when bit[i] is set, pref_counter&lt;i&gt; will count with no consideration of any enable/reset/stop signals." access="RW" offset="0xC.0" size="0x0.8" />
	<field name="cnt_type" descr="HW counter type.\;[DWIP] See Table 209, &quot;L1 Performance Counter Type,&quot; on page 224" access="RW" high_bound="7" low_bound="0" offset="0x10.28" size="0x4.0" />
	<field name="cnt_val" descr="HW counter value.\;The counter value can be configured to an initial value before enabling the feature." access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
</node>

<node name="MMAG_ext" descr="" size="0x10.0" >
	<field name="local_module" descr="Local module index\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ga" descr="Geographical Address of the ASIC which controls the module\;\;Reserved when module type is chip2chip or backplane." access="RO" offset="0x4.0" size="0x0.4" />
	<field name="global_module" descr="Global module number\;" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="module_type" descr="module_type:\;0: Backplane_with_4_lanes\;1: QSFP\;2: SFP\;3: No_Cage\;4: Backplane_with_single_lane\;8: Backplane_with_two_lanes\;10: Chip2Chip4x\;11: Chip2Chip2x\;12: Chip2Chip1x\;14: QSFP_DD\;15: OSFP\;16: SFP_DD\;17: DSFP\;18: Chip2Chip8x\;19: Twisted_Pair\;20: Backplane_with_8_lanes\;21: Loopback \;22: OE_16x\;23: OSFP_ELS\;24: QSFP_2x\;25: CPO_32x" access="RO" offset="0xC.0" size="0x0.8" />
</node>

<node name="MMAM_ext" descr="" size="0x10.0" >
	<field name="module" descr="(Global) Module number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ga" descr="Geographical Address of the ASIC which controls the module\;\;Reserved when module type is chip2chip or backplane." access="RO" offset="0x4.0" size="0x0.4" />
	<field name="local_module" descr="Local module number" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="module_type" descr="module_type:\;0: Backplane_with_4_lanes\;1: QSFP\;2: SFP\;3: No_Cage\;4: Backplane_with_single_lane\;8: Backplane_with_two_lanes\;10: Chip2Chip4x\;11: Chip2Chip2x\;12: Chip2Chip1x\;14: QSFP_DD\;15: OSFP\;16: SFP_DD\;17: DSFP\;18: Chip2Chip8x\;19: Twisted_Pair\;20: Backplane_with_8_lanes\;21: Loopback \;22: OE_16x\;23: OSFP_ELS\;24: QSFP_2x\;25: CPO_32x" access="RO" offset="0xC.0" size="0x0.8" />
</node>

<node name="MMCR_ext" descr="" size="0x50.0" >
	<field name="next_module_control" descr="Next Module Control\;bit 0: indication for module 0. \;bit 1: indication for module 1.\;..\;bit 127: indication of module 127.\;\;For each module, \;0: FW controls module\;1: SW controls module\;\;Valid bits: 0 .. (MGPIR.max_modules_per_slot -1)\;Rest of the bits are ignored.\;\;This field is not used as RW but as an index." access="RW" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
	<field name="module_control_mask" descr="Module Control Mask\;bit 0: indication for module 0. \;bit 1: indication for module 1.\;..\;bit 127: indication of module 127.\;\;On read:\;FW will return mask = 0xffff from module 0 until (MGPIR.max_modules_per_slot -1)\;\;On write:\;0: ignore module_control\;1: Set according to module_control\;Valid bits: 0 .. (MGPIR.max_modules_per_slot -1)\;Rest of the bits are ignored." access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="curr_module_control" descr="Current Module Control\;bit 0: indication for module 0. \;bit 1: indication for module 1.\;..\;bit 127: indication of module 127.\;\;For each module, \;0: FW controls module\;1: SW controls module\;\;Valid bits: 0 .. (MGPIR.max_modules_per_slot -1)\;Rest of the bits are ignored.\;" access="RO" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
</node>

<node name="MOCBR_ext" descr="" size="0xc.0" >
	<field name="e" descr="0: Meter by reference feature is disabled\;1: Meter by reference feature is enabled" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="l" descr="Long index\;0: Use short indexing (only 16bit is taken from cb set LSB)\;1: Use long indexing (16 bit is taken from cb set LSB and additional 3 bits are taken from cb set +1). \;Cbset is defined in COUNTER_BY_REF_PARAM.cbset.\;See Table 2871, &quot;COUNTER_BY_REF_PARAM Block Layout,&quot; on page 3169" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="base_counter_index" descr="Range for flow counters: \;0 .. cap_shared_counter_pool_size - 1\;Range for accuFlow counters: \;cap_start_accuflow .. cap_start_accuflow + cap_max_accuflow - 1\;Used to calculate the desired counter index.\;Counter Index = MOCBR.base_counter_index + (cbset value)" access="RW" offset="0x8.0" size="0x0.24" />
</node>

<node name="MOCBS_ext" descr="" size="0xc.0" >
	<field name="op" descr="Operation.\;0: Read_only \;1: Read_and_Clear_cause" access="OP" enum="Read_only=0x0,Read_and_Clear_cause=0x1" offset="0x0.0" size="0x0.2" />
	<field name="cnt_err" descr="0: No indication of counter Id calculation mismatch\;1: Global Counter Id calculation mismatch indication" access="RO" offset="0x4.0" size="0x0.1" />
</node>

<node name="MOFTC_bitmap512_ext" descr="" size="0x88.0" >
	<field name="port_bitmask" descr="Port bitmask request.\;Port 0 (bit 0, cpu port) and ports beyond cap_max_switch_ports are reserved.\;Service ports are allowed.\;8x ports are not allowed." access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
	<field name="port_bitmask_actual" descr="Prio bitmask actual.\;FW may choose to provide more ports than requested.\;FW will not choose to provide more TC/PG/Prio than requested." access="RO" high_bound="15" low_bound="0" offset="0x40.0" size="0x40.0" />
</node>

<node name="MOFTC_ext" descr="" size="0x108.0" >
	<field name="clear_mbo" descr="Clear Max Buff Occupancy\;Will clear the max_buff_occupancy gauge once after the first sample. This clear field does not clear other counters.\;\;Applicable for the Traffic Classes enabled by tc_bitmask and Port Groups enabled by pg_bitmask.\;\;Values:\;0: not_clear\;1: clear" access="RW" enum="not_clear=0x0,clear=0x1" offset="0x0.31" size="0x0.1" />
	<field name="prio_bitmask" descr="Priority bitmask" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="tc_bitmask" descr="Traffic Class bitmask" access="RW" offset="0x8.0" size="0x0.17" />
	<field name="pg_bitmask" descr="PG bitmask" access="RW" offset="0xC.0" size="0x0.9" />
	<field name="metadata_bitmask" descr="For each bit, see definition in the sample, see Table , &quot;,&quot; on page 1265" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="global_counters_bitmask" descr="For each bit, see definition in the sample see Table , &quot;,&quot; on page 1265" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="port_counters_bitmask" descr="For each bit, see definition in the sample see Table , &quot;,&quot; on page 1265" subnode="uint64" access="RW" offset="0x20.0" size="0x8.0" />
	<field name="flow_counter_base_0" descr="Base of the flow counters to read. Set 0\;Range 0.. cap_shared_counter_pool_size-2" access="RW" offset="0x30.0" size="0x0.24" />
	<field name="flow_counter_num_0" descr="Number of consecutive counters to read. Set 0" access="RW" offset="0x34.0" size="0x0.16" />
	<field name="flow_counter_base_1" descr="Base of the flow counters to read. Set 1\;Range 0.. cap_shared_counter_pool_size-2" access="RW" offset="0x38.0" size="0x0.24" />
	<field name="flow_counter_num_1" descr="Number of consecutive counters to read. Set 1" access="RW" offset="0x3C.0" size="0x0.16" />
	<field name="bitmap_size" descr="0: BITMAP_512 - supported by Spectrum-4." access="OP" enum="BITMAP_512=0x0" offset="0x7C.0" size="0x0.4" />
	<field name="port_bitmask" descr="See Table 1272, &quot;MOFTC - 512 Port Bitmap Layout,&quot; on page 1388" subnode="MOFTC_port_bitmask_auto_ext" access="RW" offset="0x80.0" size="0x88.0" union_selector="$(parent).bitmap_size" />
</node>

<node name="MOFTC_port_bitmask_auto_ext" descr="" attr_is_union="1" size="0x88.0" >
	<field name="MOFTC_bitmap512_ext" descr="" subnode="MOFTC_bitmap512_ext" offset="0x0.0" selected_by="BITMAP_512" size="0x88.0" />
</node>

<node name="MOFTD_ext" descr="" size="0x24.0" >
	<field name="num_rec" descr="number of records (entries) in this register. \;Entry is 32bit.\;" access="RO" offset="0x0.0" size="0x0.12" />
	<field name="itr_index" descr="Iteration counter value" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="num_entries_in_itr" descr="num_of_entries in an iteration" access="RO" offset="0x8.0" size="0x0.20" />
	<field name="entry_index" descr="Index of the first entry in this chunk (MOFTD)\;Example:\;num_entries_in_itr=20,000:\;1st chunk (MOFTD) had 9000 entries, entry_index=0\;2nd chunk (MOFTD) has 9000 entries, entry_index=9000\;3rd chunk (MOFTD) has 2000 entries, entry_index=18,000" access="RO" offset="0xC.0" size="0x0.20" />
	<field name="num_entries_per_port" descr="Number of entries per port (entry is 32bit)\;If there are no ports then value is 0" access="RO" offset="0x10.0" size="0x0.12" />
	<field name="first_port_in_chunk" descr="First port in this chunk (in this MOFTD)\;Reserved when num_entries_per_port = 0" access="RO" offset="0x10.16" size="0x0.10" />
	<field name="user_cookie" descr="Cookie from MOCS" subnode="uint64" access="RO" offset="0x18.0" size="0x8.0" />
	<field name="entry" descr="Entries from the sample.\;See Table 971, &quot;HFT Sample,&quot; on page 1265" access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x20.0" size="0x4.0" size_condition="$(parent).num_rec" />
</node>

<node name="MRFV_CVB_ext" descr="" size="0x8.0" >
	<field name="cvb_data_index" descr="CVB Voltage = -4 + 0.5 * cvb_data_index\;cvb_data_index valid values 0 .. 15\;Process Sigma &lt;-&gt; DVDD (mV)\;-4.0: 856.00\;-3.5: 847.75\;-3.0: 839.50\;-2.5: 831.25\;-2.0: 823.00\;-1.5: 814.75\;-1.0: 806.50\;-0.5: 798.25\;0 (nominal): 790.00\;0.5: 781.75\;1.0: 773.50\;1.5: 765.25\;2.0: 757.00\;2.5: 748.75\;3.0: 740.50\;3.5: 732.25\;4.0: 724.00\;Reserved when selector = 1" access="RO" offset="0x0.0" size="0x0.5" />
	<field name="selector" descr="0: cvb_data_index is valid\;1: cvb_voltage is valid\;\;" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="cvb_voltage" descr="CVB Voltage\;Returns required CVB voltage in mV.\;\;Reserved when selector = 0" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="tav_cvb_voltage" descr="TAV CVB Voltage\;Returns required TAV CVB voltage in mV.\;Used in Retimer only.\;Value of 0 means not valid voltage, host should ignore this value.\;" access="RO" offset="0x4.20" size="0x0.12" />
</node>

<node name="MRFV_PVS_MAIN_ext" descr="" size="0x4.0" >
	<field name="pvs_main_data" descr="PVS Data\;Range 0.675 - 0.75\;Vdd = 750mV - (fuse value - 1)*5mV" access="RO" offset="0x0.0" size="0x0.7" />
</node>

<node name="MRFV_PVS_TILE_ext" descr="" size="0x4.0" >
	<field name="pvs_tile_data" descr="PVS tile Data\;Range 0.675 - 0.72\;Vdd = 750mV - (fuse value - 1)*5mV" access="RO" offset="0x0.0" size="0x0.7" />
</node>

<node name="MRFV_ULT_ext" descr="" size="0xc.0" >
	<field name="ult_lot_digit_1" descr="" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="ult_lot_digit_2" descr="" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="ult_lot_digit_3" descr="" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="ult_lot_digit_4" descr="" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="ult_lot_digit_5" descr="" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ult_lot_digit_6" descr="" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="ult_lot_digit_7" descr="" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="ult_lot_digit_8" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="ult_y" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="ult_x" descr="" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="ult_wafer_number" descr="" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="ult_err_detection" descr="" access="RO" offset="0x8.29" size="0x0.3" />
</node>

<node name="MRFV_data_auto_ext" descr="" attr_is_union="1" size="0xc.0" >
	<field name="MRFV_CVB_ext" descr="" subnode="MRFV_CVB_ext" offset="0x0.0" selected_by="cvb" size="0x8.0" />
	<field name="MRFV_PVS_MAIN_ext" descr="" subnode="MRFV_PVS_MAIN_ext" offset="0x0.0" selected_by="pvs_main_die" size="0x4.0" />
	<field name="MRFV_PVS_TILE_ext" descr="" subnode="MRFV_PVS_TILE_ext" offset="0x0.0" selected_by="pvs_tile_0" size="0x4.0" />
	<field name="MRFV_ULT_ext" descr="" subnode="MRFV_ULT_ext" offset="0x0.0" selected_by="ULT" size="0xc.0" />
</node>

<node name="MRFV_ext" descr="" size="0x40.0" >
	<field name="fuse_id" descr="Fuse Index\;0: cvb - CVB Main Die, used for Retimer\;1: ULT - used for Retimer\;2: pvs_main_die - (used for SPC-4)\;3: pvs_tile_0 - (used for SPC-4)\;4: pvs_tile_1 - (used for SPC-4)\;5: pvs_tile_2 - (used for SPC-4)\;6: pvs_tile_3 - (used for SPC-4)\;7: pvs_tile_4 - (used for SPC-4)\;8: pvs_tile_5 - (used for SPC-4)\;9: pvs_tile_6 - (used for SPC-4)\;10: pvs_tile_7 - (used for SPC-4)\;Other values reserved\;Reserved when fm = 1" access="INDEX" enum="cvb=0x0,ULT=0x1,pvs_main_die=0x2,pvs_tile_0=0x3,pvs_tile_1=0x4,pvs_tile_2=0x5,pvs_tile_3=0x6,pvs_tile_4=0x7,pvs_tile_5=0x8,pvs_tile_6=0x9,pvs_tile_7=0xa" offset="0x0.0" size="0x0.8" />
	<field name="fm" descr="Fuse Mismatch\;0: No fuse mismatch\;1: Fuse mismatch found\;2-3: Reserved" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="v" descr="Valid bit\;0: Fuse reading is not supported for this system\;1: Response is valid\;2-3: Reserved\;Reserved when fm = 1" access="RO" offset="0x0.30" size="0x0.2" />
	<field name="data" descr="Data\;See Table 305, &quot;MRFV entry - CVB Layout,&quot; on page 299\;See Table 307, &quot;MRFV entry - ULT Layout,&quot; on page 301\;See Table 309, &quot;MRFV entry - PVS_MAIN Layout,&quot; on page 302\;See Table 311, &quot;MRFV entry - PVS_Tile Layout,&quot; on page 303\;Reserved when fm = 1" subnode="MRFV_data_auto_ext" access="RO" offset="0x10.0" size="0xc.0" union_selector="$(parent).fuse_id" />
</node>

<node name="MRSV_CX_7_Value_ext" descr="" size="0x20.0" >
	<field name="disable_inband_recovery" descr="disable_inband_recovery strap" access="RO" offset="0x0.21" size="0x0.1" />
	<field name="primary_is_pcore1" descr="primary_is_pcore1 strap" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="two_p_core_active" descr="2p_core_active strap" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="socket_direct" descr="socket_direct strap" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="pci_reversal" descr="pci_reversal strap" access="RO" offset="0x0.25" size="0x0.1" />
	<field name="pci_partition_1" descr="pci_partition_1 strap" access="RO" offset="0x0.26" size="0x0.1" />
	<field name="pci_partition_0" descr="pci_partition_0 strap" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="osc_freq_1" descr="osc_freq_[1] strap" access="RO" offset="0x0.28" size="0x0.1" />
	<field name="osc_freq_0" descr="osc_freq_[0] strap" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="core_bypass_n" descr="core bypass n strap" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="fnp" descr="fnp strap" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="straps_mask" descr="strapping pins mask\;0: ignore strap value\;1: strap value is valid" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="MRSV_data_auto_ext" descr="" attr_is_union="1" size="0x20.0" >
	<field name="MRSV_CX_7_Value_ext" descr="" subnode="MRSV_CX_7_Value_ext" offset="0x0.0" selected_by="bf3" size="0x20.0" />
</node>

<node name="MRSV_ext" descr="" size="0x40.0" >
	<field name="ssid" descr="Straps Structure Id\;0: bf3" access="RO" enum="bf3=0x0" offset="0x0.0" size="0x0.8" />
	<field name="v" descr="Valid bit\;0: Strapping pins value reading is not supported for this system\;1: Response is valid" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="data" descr="Data\;See Table 107, &quot;MRSV entry - BF-3 Straps Layout,&quot; on page 140" subnode="MRSV_data_auto_ext" access="RO" offset="0x10.0" size="0x20.0" union_selector="$(parent).ssid" />
</node>

<node name="MSECQ_reg_ext" descr="" size="0x40.0" >
	<field name="local_enhanced_ssm_code" descr="The enhanced SSM code to be delivered when on holdover." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="local_ssm_code" descr="The SSM code to be delivered when on holdover." access="RO" offset="0x4.8" size="0x0.4" />
	<field name="network_option" descr="The network option of this device (as defined in ITU-T G.781).\;1: Network option 1\;2: Network option 2" access="RO" offset="0x4.12" size="0x0.2" />
	<field name="local_clock_identity" descr="The SyncE clock identity of the device." subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="MSEES_reg_ext" descr="" size="0x40.0" >
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the local_port[9:8] bits" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type, determines the way local_port is interpreted:\;0: Local port number\;1: Label port number\;3: Out of band or PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="field_select" descr="Field select indicates which fields to modify in write operation to this register. \;Bit 0: enable field_select\;Bit 1: admin_status\;Bit 2: admin_freq_measure\;Bits 3-31: Reserved" access="WO" offset="0x4.0" size="0x4.0" />
	<field name="failure_reason" descr="0: undefined error \;1: port down\;2: too high frequency_diff\;3: network synchronizer device error\;4: lack of resources for tracking \;5-255: reserved for future use \;\;Note: Reserved when oper_status is different than 4 or 5" access="RO" offset="0x8.0" size="0x0.9" />
	<field name="oper_freq_measure" descr="0: frequency_diff field is not valid\;1: frequency_diff field is valid" access="RO" offset="0x8.9" size="0x0.1" />
	<field name="admin_freq_measure" descr="0: don&apos;t measure frequency_diff\;1: measure frequency_diff" access="RW" offset="0x8.10" size="0x0.1" />
	<field name="ho_acq" descr="Holdover acquired.\;0: The device does not have enough data to go into holdover.\;1: The device has enough data to go into holdover." access="RO" offset="0x8.23" size="0x0.1" />
	<field name="oper_status" descr="0: free running - the device is using internal oscillator as timing source \;1: self track - the device is in sync with this timing source\;2: other track - the device is in sync with other timing source\;3: holdover - the device is using the internal oscillator and past information as a timing source.\;4: Holdover due to failure (see field failure_reason)\;5: Free running due to failure (see field failure_reason)." access="RO" offset="0x8.24" size="0x0.4" />
	<field name="admin_status" descr="0: holdover/free running - the device will use internal oscillator as timing source. \;Free running is the default value.\;Device holdover / free running will take place only if admin status = 0 across all other ports.\;1: track - the device will sync to this timing source. When writing admin status = 1 to a port, all other ports will move to admin status = 0." access="RW" offset="0x8.28" size="0x0.4" />
	<field name="frequency_diff" descr="The FFO (Fractional Frequency Offset) between the rx and tx symbol rate: (rx_frequency- tx_frequency) /rx_frequency.\;Value is in ppt (2&apos;s complement).\;Any value larger than 0x7FFFFFFF represented as 0x7FFFFFFF. \;Any value smaller than 0x80000000 represented as 0x80000000.\;\;Note: Reserved when oper_freq is different than &apos;1&apos;." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="MTMG_ext" descr="" size="0x10.0" >
	<field name="e" descr="enable \;0: FW is not monitoring modules temperature\;1: FW is monitoring modules temperature\;By default, FW is not running." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="mit" descr="Monitoring Interval Time\;Defines the frequency which FW monitors the module temp.\;Valid values 6, 12, 18.. 252 (seconds). \;Can be changed only when MTMG.e = 0 (fw is not running)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="threshold_1" descr="Defines the threshold that when the change in the consecutive temperature measurements once every mit time crosses it, the respective counter is incremented by 1. Units in deg C, 2s-complement (allows negative values)" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="threshold_2" descr="Defines the threshold that when the change in the consecutive temperature measurements once every mit time crosses it, the respective counter is incremented by 1. Units in deg C, 2s-complement (allows negative values)" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="threshold_3" descr="Defines the threshold that when the change in the consecutive temperature measurements once every mit time crosses it, the respective counter is incremented by 1. Units in deg C, 2s-complement (allows negative values)" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="threshold_4" descr="Defines the threshold that when the change in the consecutive temperature measurements once every mit time crosses it, the respective counter is incremented by 1. Units in deg C, 2s-complement (allows negative values)" access="RW" offset="0xC.16" size="0x0.8" />
</node>

<node name="MTMR_ext" descr="" size="0xc.0" >
	<field name="module" descr="Module number\;\;" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="op" descr="Operation\;0: Read only\;1: Clear counters \;2: Read and Clear counters\;3: Reserved" access="OP" offset="0x4.0" size="0x0.2" />
	<field name="abs_max_temp_change" descr="Absolute value of max temperature change between consecutive measurements, in 1C resolution" access="RO" offset="0x4.16" size="0x0.5" />
	<field name="thr_1_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.0" size="0x0.4" />
	<field name="thr_2_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.8" size="0x0.4" />
	<field name="thr_3_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.16" size="0x0.4" />
	<field name="thr_4_cnt" descr="Counter for events when the change in the consecutive temperature measurements crosses threshold_x. Saturated at 0xf value." access="RO" offset="0x8.24" size="0x0.4" />
</node>

<node name="MTSR_ext" descr="" size="0x10.0" >
	<field name="mode" descr="0: Normal\;1: Warning\;2: Critical\;3-7: Reserved" access="RO" offset="0x0.0" size="0x0.3" />
	<field name="normal_events_cnt" descr="Num of normal thermal events triggered counter" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="warning_events_cnt" descr="Num of warning thermal events triggered counter" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="critical_events_cnt" descr="Num of critical thermal events triggered counter" access="RO" offset="0xC.0" size="0x0.8" />
</node>

<node name="PPCR_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port[9:8]\;Reserved for HCA" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="asymmetry_enable" descr="[DWIP]\;Indicate whether asymmetry is enabled or not.\;\;For HCA, reserved if PPCR.asymmetry_enable_supported=0" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="asymmetry_enable_supported" descr="[DWIP]\;Indicate whether asymmetry_enable supported or not.\;Reserved for switch.\;" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="aggregated_port" descr="Aggregated Port number to be reflected in MAD.\;0 means N/A\;\;Reserved for HCA" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="plane" descr="Plane number to be reflected in MAD.\;0 means N/A\;\;Reserved for HCA" access="RW" offset="0x8.16" size="0x0.3" />
	<field name="split" descr="When planarized  the FW shall respond to Hierarchy Info.Split with the following split value.\;In this use case it represents the split of the APort.\;\;When split = 0, the FW shall send Hierarchy Info without the split field. (meaning it is NA)\;\;When Non planarized (num_of_planes = 0), Hierarchy Info.Split will reflect the actual split value, when 2X- it&apos;ll hold the location within the 4x.\;\;0: NA\;1: Split 1.\;2: Split 2.\;3-7: Reserved\;Reserved for HCA" access="RW" offset="0x8.24" size="0x0.3" />
	<field name="num_of_planes" descr="The number of planes comprising this Aggregated port\;" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="p_type" descr="[DWIP]\;Planarization Type\;0: non planarized\;1: planirized_gen1\;2-7: Reserved" access="RW" offset="0xC.16" size="0x0.3" />
</node>

<node name="PPIR_ext" descr="" size="0x8.0" >
	<field name="lcnf_pln" descr="Last Core Negotiation Failed due to Planarized.\;When there is no match between local and remote fields compared to local config by PPCR\;" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="lpnf_phy" descr="Last Phy Negotiation Failed due to Phy\;No partner detected for a long period" access="RO" offset="0x0.8" size="0x0.1" />
	<field name="lpnf_no_hcd" descr="Last Phy Negotiation Failed due to Highest Common Denominator mismatch.\;" access="RO" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="peer_num_of_planes" descr="The number of planes comprising the peer Aggregated port\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="peer_p_type" descr="Peer Planarization Type\;0: non planarized\;1: planirized_gen1\;2-7: Reserved" access="RO" offset="0x4.16" size="0x0.3" />
</node>

<node name="access_reg_summary_ctrl_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="id" descr="" subnode="enum_entry" enum="MMDIO=0x9017,MLCR=0x902b,MGCR=0x903a,MJTAG=0x901f,MFM=0x901d,MHSR=0x901e,MICV=0x917a,MICM=0x917b,MRSV=0x9164,MTPPS=0x9053,MTUTC=0x9055,MRTC=0x902d,MSECQ=0x9155,MSEES=0x9156,MCIA=0x9014,MCION=0x9052,MCFS=0x9165,PMAOS=0x5012,MMTA=0x9113,PMTM=0x5067,PMPC=0x501f,PMPE=0x5024,MDDT=0x9160,MDDQ=0x9161,MDDC=0x9163,MGPIR=0x9100,MDRCR=0x9102,MDFCR=0x9101,MTCAP=0x9009,MTECR=0x9109,MTMP=0x900a,MTWE=0x900b,MTEWE=0x910b,MTBR=0x900f,MTBR_V2=0x9165,MTMG=0x910d,MTMR=0x910e,MVCAP=0x902e,MVCR=0x900c,MSPS=0x900d,MCPP=0x900e,MPSCR=0x910f,MTSR=0x9121,MLPC=0x9166,MPPCR=0x9173,MPPGCR=0x9174,MPPGS=0x9175,MPPGH=0x9176,MPGHR=0x9141,MPPDR=0x9177,MSLCG=0x902c,MPSQ=0x9044,MPSH=0x9045,MRSR=0x9023,MRSRFT=0x911e,MFRL=0x9028,MROQ=0x902f,MBTR=0x9077,MCQS=0x9060,MCQI=0x9061,MCC=0x9062,MCDA=0x9063,MCDD=0x905c,MIRC=0x9162,MQIS=0x9064,MGIR=0x9020,MSGI=0x9021,MSCI=0x902a,MDIR=0x911a,MISOC=0x9026,MSSIR=0x9105,MINI=0x905e,MCAM=0x907f,MECCC=0x905f,MMAM=0x9170,MMAG=0x9171,MFMI=0x9078,MRFV=0x906d,MBCT=0x9120,MTEIR=0x9190,MDTR=0x9073,MDPS=0x9074,MDSR=0x9110,MFSV=0x9115,MTCQ=0x9065,MQDIK=0x9116,MKDC=0x9066,MSPMER=0x9070,MFCDR=0x9178,MSGCR=0x9179,MSHR=0x917e,MNVDA=0x9024,MNVDI=0x9025,MNVQC=0x9030,MNVIA=0x9033,MNVGC=0x9034,MNVGN=0x9035,MGNLE=0x9036,MGLS=0x9068,MTRC_CAP=0x9040,MTRC_CONF=0x9041,MTRC_STDB=0x9042,MTRC_STDB_V2=0x9210,MTRC_CTRL=0x9043,MTEIM=0x9118,MTIE=0x911b,MTIM=0x911c,MTDC=0x911d,MFPA=0x9010,MFBA=0x9011,MFBE=0x9012,MFMC=0x9013,MFCR=0x9001,MFSC=0x9002,MFSM=0x9003,MFSL=0x9004,FORE=0x9007,MFNR=0x903b,MPCIR=0x905a,MERR=0x903c,MRPR=0x9117,MDCR=0x9111,MHMPR=0x905d,MFRC=0x9069,MMCR=0x906c,MFRI=0x906b,MFRP=0x906a,MISSUV=0x9191,PCAM=0x507f,PCAP=0x5001,PTYS=0x5004,PAOS=0x5006,PLTC=0x5046,PPCNT=0x5008,PUDE=0x5009,PGMR=0x5039,PTER=0x5055,PREI=0x5058,PPRM=0x5059,PMLP=0x5002,PMPR=0x5013,PMMP=0x5044,PMCR=0x5045,PMPT=0x5064,PMPD=0x5065,PLDS=0x5076,PPSC=0x5011,PRTL=0x5014,PPLR=0x5018,PPLM=0x5023,SLTP=0x5027,SLTPv2=0x502f,SLRG=0x5028,PTASv2=0x502e,PDDR=0x5031,PPTT=0x5036,PPRT=0x5037,PMDR=0x503c,PPHCR=0x503e,PPAOS=0x5040,PPBMP=0x5051,PPBMC=0x5052,PPBME=0x5053,SLLM=0x505b,PLCC=0x505e,PMTU=0x5003,PPAD=0x5005,PFCC=0x5007,PPTB=0x500b,PBMC=0x500c,PGUID=0x5066,PVLC=0x500f,PHBR=0x5034,PHRR=0x5035,PBSR=0x5038,PCMR=0x5041,PFSC=0x5043,PPCR=0x504c,PPIR=0x50eb,PTSR=0x5400,PRTSR=0x5402,PTSB=0x5401,PLIB=0x500a,PLIBDB=0x50e1,PPSLC=0x50e2,PPSLS=0x50e3,PPSLD=0x50e4,PEVNT=0x50e6,PBWC=0x50e7,PBWR=0x50e8,PPDFD=0x50e9,MOGCR=0x9086,MPRS=0x9083,MDRI=0x9084,MRRR=0x9087,MONI=0x90f4,MOLP=0x90f9,MFBD=0x90fb,MMGCR=0x90e9,MPAT=0x901a,MPAR=0x901b,MPAGR=0x9089,MOMTE=0x908d,MOCMI=0x9098,MOTRM=0x9402,MPSC=0x9080,MOTPR=0x9420,MOTSPT=0x9421,MOTTG=0x9422,MOTBT=0x9423,MOTCB=0x9424,MGPC=0x9081,MGPCB=0x9096,MOCS=0x9095,MAFCR=0x908a,MAFTI=0x908b,MAFRI=0x908c,MAFBI=0x9097,MOCA=0x90e3,MOFPH=0x90e4,MOFPC=0x90e5,MOFRB=0x90e6,MOCBR=0x90e7,MOCBS=0x90e8,MOFTC=0x9400,MOFTD=0x9401,MTPPPC=0x9090,MTPPTR=0x9091,MTPTPT=0x9092,MTPCPC=0x9093,MTPSPU=0x9094,MODCR=0x9099,MFDE=0x9200,MOFDE=0x9152,MORD=0x9153,GHPKT=0x6802,GSGUID=0x6803,GPLID=0x6805,UNWKM=0x6501,UNRSA=0x6502,UNRC=0x6503,UNDRI=0x6504,UKDRI=0x6506,UNDFD=0x6505" offset="0x0.0" size="0x4.0" />
</node>

<node name="access_reg_summary_ext" descr="" attr_is_union="1" size="0x5a0" >
	<field name="MCFS" descr="" subnode="MCFS_ext" capability="0" offset="0x0.0" selected_by="MCFS" size="0x20" />
	<field name="MFMI" descr="" subnode="MFMI_ext" capability="0" offset="0x0.0" selected_by="MFMI" size="0x18" />
	<field name="MICM" descr="" subnode="MICM_ext" capability="0" offset="0x0.0" selected_by="MICM" size="0x28" />
	<field name="MICV" descr="" subnode="MICV_ext" capability="0" offset="0x0.0" selected_by="MICV" size="0x24" />
	<field name="MLPC" descr="" subnode="MLPC_ext" capability="0" offset="0x0.0" selected_by="MLPC" size="0x40" />
	<field name="MMAG" descr="" subnode="MMAG_ext" capability="0" offset="0x0.0" selected_by="MMAG" size="0x10" />
	<field name="MMAM" descr="" subnode="MMAM_ext" capability="0" offset="0x0.0" selected_by="MMAM" size="0x10" />
	<field name="MMCR" descr="" subnode="MMCR_ext" capability="0" offset="0x0.0" selected_by="MMCR" size="0x50" />
	<field name="MOCBR" descr="" subnode="MOCBR_ext" capability="0" offset="0x0.0" selected_by="MOCBR" size="0xc" />
	<field name="MOCBS" descr="" subnode="MOCBS_ext" capability="0" offset="0x0.0" selected_by="MOCBS" size="0xc" />
	<field name="MOFTC" descr="" subnode="MOFTC_ext" capability="0" offset="0x0.0" selected_by="MOFTC" size="0x108" />
	<field name="MOFTD" descr="" subnode="MOFTD_ext" capability="0" offset="0x0.0" selected_by="MOFTD" size="0x24" />
	<field name="MRFV" descr="" subnode="MRFV_ext" capability="0" offset="0x0.0" selected_by="MRFV" size="0x40" />
	<field name="MRSV" descr="" subnode="MRSV_ext" capability="0" offset="0x0.0" selected_by="MRSV" size="0x40" />
	<field name="MSECQ_reg" descr="" subnode="MSECQ_reg_ext" capability="0" offset="0x0.0" selected_by="MSECQ" size="0x40" />
	<field name="MSEES_reg" descr="" subnode="MSEES_reg_ext" capability="0" offset="0x0.0" selected_by="MSEES" size="0x40" />
	<field name="MTMG" descr="" subnode="MTMG_ext" capability="0" offset="0x0.0" selected_by="MTMG" size="0x10" />
	<field name="MTMR" descr="" subnode="MTMR_ext" capability="0" offset="0x0.0" selected_by="MTMR" size="0xc" />
	<field name="MTSR" descr="" subnode="MTSR_ext" capability="0" offset="0x0.0" selected_by="MTSR" size="0x10" />
	<field name="PPCR" descr="" subnode="PPCR_ext" capability="0" offset="0x0.0" selected_by="PPCR" size="0x10" />
	<field name="PPIR" descr="" subnode="PPIR_ext" capability="0" offset="0x0.0" selected_by="PPIR" size="0x8" />
	<field name="fore" descr="" subnode="fore_ext" capability="0" offset="0x0.0" selected_by="FORE" size="0xc" />
	<field name="ghpkt" descr="" subnode="ghpkt_ext" capability="0" offset="0x0.0" selected_by="GHPKT" size="0x10" />
	<field name="gplid" descr="" subnode="gplid_ext" capability="0" offset="0x0.0" selected_by="GPLID" size="0x10" />
	<field name="gsguid" descr="" subnode="gsguid_ext" capability="0" offset="0x0.0" selected_by="GSGUID" size="0x10" />
	<field name="mafbi" descr="" subnode="mafbi_ext" capability="0" offset="0x0.0" selected_by="MAFBI" size="0x308" />
	<field name="mafcr" descr="" subnode="mafcr_ext" capability="0" offset="0x0.0" selected_by="MAFCR" size="0xc" />
	<field name="mafri" descr="" subnode="mafri_ext" capability="0" offset="0x0.0" selected_by="MAFRI" size="0x410" />
	<field name="mafti" descr="" subnode="mafti_ext" capability="0" offset="0x0.0" selected_by="MAFTI" size="0x308" />
	<field name="mbct" descr="" subnode="mbct_ext" capability="0" offset="0x0.0" selected_by="MBCT" size="0x420" />
	<field name="mbtr" descr="" subnode="mbtr_ext" capability="0" offset="0x0.0" selected_by="MBTR" size="0x8" />
	<field name="mcam_reg" descr="" subnode="mcam_reg_ext" capability="0" offset="0x0.0" selected_by="MCAM" size="0x48" />
	<field name="mcc_reg" descr="" subnode="mcc_reg_ext" capability="0" offset="0x0.0" selected_by="MCC" size="0x20" />
	<field name="mcda_reg" descr="" subnode="mcda_reg_ext" capability="0" offset="0x0.0" selected_by="MCDA" size="0x90" />
	<field name="mcdd_reg" descr="" subnode="mcdd_reg_ext" capability="0" offset="0x0.0" selected_by="MCDD" size="0x20" />
	<field name="mcia" descr="" subnode="mcia_ext" capability="0" offset="0x0.0" selected_by="MCIA" size="0x94" />
	<field name="mcion" descr="" subnode="mcion_ext" capability="0" offset="0x0.0" selected_by="MCION" size="0x10" />
	<field name="mcpp_reg" descr="" subnode="mcpp_reg_ext" capability="0" offset="0x0.0" selected_by="MCPP" size="0x10" />
	<field name="mcqi_reg" descr="" subnode="mcqi_reg_ext" capability="0" offset="0x0.0" selected_by="MCQI" size="0x94" />
	<field name="mcqs_reg" descr="" subnode="mcqs_reg_ext" capability="0" offset="0x0.0" selected_by="MCQS" size="0x10" />
	<field name="mdcr" descr="" subnode="mdcr_ext" capability="0" offset="0x0.0" selected_by="MDCR" size="0x60" />
	<field name="mddc" descr="" subnode="mddc_ext" capability="0" offset="0x0.0" selected_by="MDDC" size="0x30" />
	<field name="mddq" descr="" subnode="mddq_ext" capability="0" offset="0x0.0" selected_by="MDDQ" size="0x30" />
	<field name="mddt_reg" descr="" subnode="mddt_reg_ext" capability="0" offset="0x0.0" selected_by="MDDT" size="0x110" />
	<field name="mdfcr_reg" descr="" subnode="mdfcr_reg_ext" capability="0" offset="0x0.0" selected_by="MDFCR" size="0x60" />
	<field name="mdir_reg" descr="" subnode="mdir_reg_ext" capability="0" offset="0x0.0" selected_by="MDIR" size="0x40" />
	<field name="mdps_reg" descr="" subnode="mdps_reg_ext" capability="0" offset="0x0.0" selected_by="MDPS" size="0x10" />
	<field name="mdrcr" descr="" subnode="mdrcr_ext" capability="0" offset="0x0.0" selected_by="MDRCR" size="0x30" />
	<field name="mdri" descr="" subnode="mdri_ext" capability="0" offset="0x0.0" selected_by="MDRI" size="0x120" />
	<field name="mdsr_reg" descr="" subnode="mdsr_reg_ext" capability="0" offset="0x0.0" selected_by="MDSR" size="0x30" />
	<field name="mdtr_reg" descr="" subnode="mdtr_reg_ext" capability="0" offset="0x0.0" selected_by="MDTR" size="0xb0" />
	<field name="meccc" descr="" subnode="meccc_ext" capability="0" offset="0x0.0" selected_by="MECCC" size="0x14" />
	<field name="merr" descr="" subnode="merr_ext" capability="0" offset="0x0.0" selected_by="MERR" size="0x14" />
	<field name="mfba_reg" descr="" subnode="mfba_reg_ext" capability="0" offset="0x0.0" selected_by="MFBA" size="0x10c" />
	<field name="mfbd" descr="" subnode="mfbd_ext" capability="0" offset="0x0.0" selected_by="MFBD" size="0x24" />
	<field name="mfbe_reg" descr="" subnode="mfbe_reg_ext" capability="0" offset="0x0.0" selected_by="MFBE" size="0xc" />
	<field name="mfcdr_reg" descr="" subnode="mfcdr_reg_ext" capability="0" offset="0x0.0" selected_by="MFCDR" size="0x8" />
	<field name="mfcr" descr="" subnode="mfcr_ext" capability="0" offset="0x0.0" selected_by="MFCR" size="0x8" />
	<field name="mfde" descr="" subnode="mfde_ext" capability="0" offset="0x0.0" selected_by="MFDE" size="0xb0" />
	<field name="mfm" descr="" subnode="mfm_ext" capability="0" offset="0x0.0" selected_by="MFM" size="0x18" />
	<field name="mfmc_reg" descr="" subnode="mfmc_reg_ext" capability="0" offset="0x0.0" selected_by="MFMC" size="0x1c" />
	<field name="mfnr" descr="" subnode="mfnr_ext" capability="0" offset="0x0.0" selected_by="MFNR" size="0x30" />
	<field name="mfpa_reg" descr="" subnode="mfpa_reg_ext" capability="0" offset="0x0.0" selected_by="MFPA" size="0x20" />
	<field name="mfrc" descr="" subnode="mfrc_ext" capability="0" offset="0x0.0" selected_by="MFRC" size="0xc" />
	<field name="mfri" descr="" subnode="mfri_ext" capability="0" offset="0x0.0" selected_by="MFRI" size="0x30" />
	<field name="mfrl_reg" descr="" subnode="mfrl_reg_ext" capability="0" offset="0x0.0" selected_by="MFRL" size="0x8" />
	<field name="mfrp" descr="" subnode="mfrp_ext" capability="0" offset="0x0.0" selected_by="MFRP" size="0x1c" />
	<field name="mfsc" descr="" subnode="mfsc_ext" capability="0" offset="0x0.0" selected_by="MFSC" size="0x8" />
	<field name="mfsl" descr="" subnode="mfsl_ext" capability="0" offset="0x0.0" selected_by="MFSL" size="0xc" />
	<field name="mfsm" descr="" subnode="mfsm_ext" capability="0" offset="0x0.0" selected_by="MFSM" size="0x8" />
	<field name="mfsv_reg" descr="" subnode="mfsv_reg_ext" capability="0" offset="0x0.0" selected_by="MFSV" size="0x30" />
	<field name="mgcr_reg" descr="" subnode="mgcr_reg_ext" capability="0" offset="0x0.0" selected_by="MGCR" size="0x20" />
	<field name="mgir" descr="" subnode="mgir_ext" capability="0" offset="0x0.0" selected_by="MGIR" size="0xa0" />
	<field name="mgls" descr="" subnode="mgls_ext" capability="0" offset="0x0.0" selected_by="MGLS" size="0xc" />
	<field name="mgnle_reg" descr="" subnode="mgnle_reg_ext" capability="0" offset="0x0.0" selected_by="MGNLE" size="0x20" />
	<field name="mgpc" descr="" subnode="mgpc_ext" capability="0" offset="0x0.0" selected_by="MGPC" size="0x18" />
	<field name="mgpcb" descr="" subnode="mgpcb_ext" capability="0" offset="0x0.0" selected_by="MGPCB" size="0x410" />
	<field name="mgpir" descr="" subnode="mgpir_ext" capability="0" offset="0x0.0" selected_by="MGPIR" size="0xa0" />
	<field name="mhmpr_reg" descr="" subnode="mhmpr_reg_ext" capability="0" offset="0x0.0" selected_by="MHMPR" size="0x14" />
	<field name="mhsr" descr="" subnode="mhsr_ext" capability="0" offset="0x0.0" selected_by="MHSR" size="0x8" />
	<field name="mini" descr="" subnode="mini_ext" capability="0" offset="0x0.0" selected_by="MINI" size="0x50" />
	<field name="mirc_reg" descr="" subnode="mirc_reg_ext" capability="0" offset="0x0.0" selected_by="MIRC" size="0x8" />
	<field name="misoc_reg" descr="" subnode="misoc_reg_ext" capability="0" offset="0x0.0" selected_by="MISOC" size="0x120" />
	<field name="missuv" descr="" subnode="missuv_ext" capability="0" offset="0x0.0" selected_by="MISSUV" size="0x20" />
	<field name="mjtag" descr="" subnode="mjtag_ext" capability="0" offset="0x0.0" selected_by="MJTAG" size="0x30" />
	<field name="mkdc_reg" descr="" subnode="mkdc_reg_ext" capability="0" offset="0x0.0" selected_by="MKDC" size="0x2c" />
	<field name="mlcr" descr="" subnode="mlcr_ext" capability="0" offset="0x0.0" selected_by="MLCR" size="0xc" />
	<field name="mmdio" descr="" subnode="mmdio_ext" capability="0" offset="0x0.0" selected_by="MMDIO" size="0xc" />
	<field name="mmgcr" descr="" subnode="mmgcr_ext" capability="0" offset="0x0.0" selected_by="MMGCR" size="0x48" />
	<field name="mmta_reg" descr="" subnode="mmta_reg_ext" capability="0" offset="0x0.0" selected_by="MMTA" size="0x90" />
	<field name="mnvda_reg" descr="" subnode="mnvda_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDA" size="0x10c" />
	<field name="mnvdi_reg" descr="" subnode="mnvdi_reg_ext" capability="0" offset="0x0.0" selected_by="MNVDI" size="0xc" />
	<field name="mnvgc_reg" descr="" subnode="mnvgc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGC" size="0x10" />
	<field name="mnvgn_reg" descr="" subnode="mnvgn_reg_ext" capability="0" offset="0x0.0" selected_by="MNVGN" size="0x20" />
	<field name="mnvia_reg" descr="" subnode="mnvia_reg_ext" capability="0" offset="0x0.0" selected_by="MNVIA" size="0x8" />
	<field name="mnvqc_reg" descr="" subnode="mnvqc_reg_ext" capability="0" offset="0x0.0" selected_by="MNVQC" size="0x8" />
	<field name="moca" descr="" subnode="moca_ext" capability="0" offset="0x0.0" selected_by="MOCA" size="0xc" />
	<field name="mocmi" descr="" subnode="mocmi_ext" capability="0" offset="0x0.0" selected_by="MOCMI" size="0x14" />
	<field name="mocs" descr="" subnode="mocs_ext" capability="0" offset="0x0.0" selected_by="MOCS" size="0xe8" />
	<field name="modcr" descr="" subnode="modcr_ext" capability="0" offset="0x0.0" selected_by="MODCR" size="0x14" />
	<field name="mofde" descr="" subnode="mofde_ext" capability="0" offset="0x0.0" selected_by="MOFDE" size="0x4" />
	<field name="mofpc" descr="" subnode="mofpc_ext" capability="0" offset="0x0.0" selected_by="MOFPC" size="0xc" />
	<field name="mofph" descr="" subnode="mofph_ext" capability="0" offset="0x0.0" selected_by="MOFPH" size="0x20" />
	<field name="mofrb" descr="" subnode="mofrb_ext" capability="0" offset="0x0.0" selected_by="MOFRB" size="0x210" />
	<field name="mogcr" descr="" subnode="mogcr_ext" capability="0" offset="0x0.0" selected_by="MOGCR" size="0x20" />
	<field name="molp" descr="" subnode="molp_ext" capability="0" offset="0x0.0" selected_by="MOLP" size="0x8" />
	<field name="momte" descr="" subnode="momte_ext" capability="0" offset="0x0.0" selected_by="MOMTE" size="0x10" />
	<field name="moni" descr="" subnode="moni_ext" capability="0" offset="0x0.0" selected_by="MONI" size="0x8" />
	<field name="motbt" descr="" subnode="motbt_ext" capability="0" offset="0x0.0" selected_by="MOTBT" size="0x10" />
	<field name="motcb" descr="" subnode="motcb_ext" capability="0" offset="0x0.0" selected_by="MOTCB" size="0x14" />
	<field name="motpr" descr="" subnode="motpr_ext" capability="0" offset="0x0.0" selected_by="MOTPR" size="0x20" />
	<field name="motrm_reg" descr="" subnode="motrm_reg_ext" capability="0" offset="0x0.0" selected_by="MOTRM" size="0xc" />
	<field name="motspt" descr="" subnode="motspt_ext" capability="0" offset="0x0.0" selected_by="MOTSPT" size="0x8" />
	<field name="mottg" descr="" subnode="mottg_ext" capability="0" offset="0x0.0" selected_by="MOTTG" size="0x218" />
	<field name="mpagr" descr="" subnode="mpagr_ext" capability="0" offset="0x0.0" selected_by="MPAGR" size="0xc" />
	<field name="mpar" descr="" subnode="mpar_ext" capability="0" offset="0x0.0" selected_by="MPAR" size="0xc" />
	<field name="mpat_reg" descr="" subnode="mpat_reg_ext" capability="0" offset="0x0.0" selected_by="MPAT" size="0x9c" />
	<field name="mpcir" descr="" subnode="mpcir_ext" capability="0" offset="0x0.0" selected_by="MPCIR" size="0xa0" />
	<field name="mpghr" descr="" subnode="mpghr_ext" capability="0" offset="0x0.0" selected_by="MPGHR" size="0x90" />
	<field name="mppcr" descr="" subnode="mppcr_ext" capability="0" offset="0x0.0" selected_by="MPPCR" size="0x40" />
	<field name="mppdr" descr="" subnode="mppdr_ext" capability="0" offset="0x0.0" selected_by="MPPDR" size="0x80" />
	<field name="mppgcr" descr="" subnode="mppgcr_ext" capability="0" offset="0x0.0" selected_by="MPPGCR" size="0x24" />
	<field name="mppgh" descr="" subnode="mppgh_ext" capability="0" offset="0x0.0" selected_by="MPPGH" size="0x50" />
	<field name="mppgs" descr="" subnode="mppgs_ext" capability="0" offset="0x0.0" selected_by="MPPGS" size="0x10" />
	<field name="mprs" descr="" subnode="mprs_ext" capability="0" offset="0x0.0" selected_by="MPRS" size="0x14" />
	<field name="mpsc" descr="" subnode="mpsc_ext" capability="0" offset="0x0.0" selected_by="MPSC" size="0x14" />
	<field name="mpscr" descr="" subnode="mpscr_ext" capability="0" offset="0x0.0" selected_by="MPSCR" size="0x20" />
	<field name="mpsh_reg" descr="" subnode="mpsh_reg_ext" capability="0" offset="0x0.0" selected_by="MPSH" size="0x50" />
	<field name="mpsq_reg" descr="" subnode="mpsq_reg_ext" capability="0" offset="0x0.0" selected_by="MPSQ" size="0x10" />
	<field name="mqdik_reg" descr="" subnode="mqdik_reg_ext" capability="0" offset="0x0.0" selected_by="MQDIK" size="0x208" />
	<field name="mqis_reg" descr="" subnode="mqis_reg_ext" capability="0" offset="0x0.0" selected_by="MQIS" size="0x18" />
	<field name="mroq" descr="" subnode="mroq_ext" capability="0" offset="0x0.0" selected_by="MROQ" size="0x20" />
	<field name="mrpr_reg" descr="" subnode="mrpr_reg_ext" capability="0" offset="0x0.0" selected_by="MRPR" size="0x108" />
	<field name="mrrr" descr="" subnode="mrrr_ext" capability="0" offset="0x0.0" selected_by="MRRR" size="0x8" />
	<field name="mrsr" descr="" subnode="mrsr_ext" capability="0" offset="0x0.0" selected_by="MRSR" size="0x8" />
	<field name="mrsrft" descr="" subnode="mrsrft_ext" capability="0" offset="0x0.0" selected_by="MRSRFT" size="0x8" />
	<field name="mrtc_reg" descr="" subnode="mrtc_reg_ext" capability="0" offset="0x0.0" selected_by="MRTC" size="0x10" />
	<field name="msci" descr="" subnode="msci_ext" capability="0" offset="0x0.0" selected_by="MSCI" size="0xc" />
	<field name="msgcr_reg" descr="" subnode="msgcr_reg_ext" capability="0" offset="0x0.0" selected_by="MSGCR" size="0x8" />
	<field name="msgi" descr="" subnode="msgi_ext" capability="0" offset="0x0.0" selected_by="MSGI" size="0x80" />
	<field name="mshr_reg" descr="" subnode="mshr_reg_ext" capability="0" offset="0x0.0" selected_by="MSHR" size="0x10" />
	<field name="mslcg" descr="" subnode="mslcg_ext" capability="0" offset="0x0.0" selected_by="MSLCG" size="0x110" />
	<field name="mspmer" descr="" subnode="mspmer_ext" capability="0" offset="0x0.0" selected_by="MSPMER" size="0x30" />
	<field name="msps" descr="" subnode="msps_ext" capability="0" offset="0x0.0" selected_by="MSPS" size="0xa0" />
	<field name="mssir_reg" descr="" subnode="mssir_reg_ext" capability="0" offset="0x0.0" selected_by="MSSIR" size="0x88" />
	<field name="mtbr_reg" descr="" subnode="mtbr_reg_ext" capability="0" offset="0x0.0" selected_by="MTBR" size="0x410" />
	<field name="mtbr_v2" descr="" subnode="mtbr_v2_ext" capability="0" offset="0x0.0" selected_by="MTBR_V2" size="0x90" />
	<field name="mtcap" descr="" subnode="mtcap_ext" capability="0" offset="0x0.0" selected_by="MTCAP" size="0x10" />
	<field name="mtcq_reg" descr="" subnode="mtcq_reg_ext" capability="0" offset="0x0.0" selected_by="MTCQ" size="0x70" />
	<field name="mtdc" descr="" subnode="mtdc_ext" capability="0" offset="0x0.0" selected_by="MTDC" size="0x20" />
	<field name="mtecr" descr="" subnode="mtecr_ext" capability="0" offset="0x0.0" selected_by="MTECR" size="0x60" />
	<field name="mteim_reg" descr="" subnode="mteim_reg_ext" capability="0" offset="0x0.0" selected_by="MTEIM" size="0x30" />
	<field name="mteir_reg" descr="" subnode="mteir_reg_ext" capability="0" offset="0x0.0" selected_by="MTEIR" size="0xc" />
	<field name="mtewe" descr="" subnode="mtewe_ext" capability="0" offset="0x0.0" selected_by="MTEWE" size="0x5c" />
	<field name="mtie" descr="" subnode="mtie_ext" capability="0" offset="0x0.0" selected_by="MTIE" size="0x30" />
	<field name="mtim" descr="" subnode="mtim_ext" capability="0" offset="0x0.0" selected_by="MTIM" size="0x10" />
	<field name="mtmp" descr="" subnode="mtmp_ext" capability="0" offset="0x0.0" selected_by="MTMP" size="0x20" />
	<field name="mtpcpc" descr="" subnode="mtpcpc_ext" capability="0" offset="0x0.0" selected_by="MTPCPC" size="0x28" />
	<field name="mtpppc" descr="" subnode="mtpppc_ext" capability="0" offset="0x0.0" selected_by="MTPPPC" size="0x28" />
	<field name="mtpps_reg" descr="" subnode="mtpps_reg_ext" capability="0" offset="0x0.0" selected_by="MTPPS" size="0x38" />
	<field name="mtpptr" descr="" subnode="mtpptr_ext" capability="0" offset="0x0.0" selected_by="MTPPTR" size="0x50" />
	<field name="mtpspu" descr="" subnode="mtpspu_ext" capability="0" offset="0x0.0" selected_by="MTPSPU" size="0x8" />
	<field name="mtptpt" descr="" subnode="mtptpt_ext" capability="0" offset="0x0.0" selected_by="MTPTPT" size="0x8" />
	<field name="mtrc_cap_reg" descr="" subnode="mtrc_cap_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CAP" size="0x84" />
	<field name="mtrc_conf_reg" descr="" subnode="mtrc_conf_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CONF" size="0x80" />
	<field name="mtrc_ctrl_reg" descr="" subnode="mtrc_ctrl_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_CTRL" size="0x40" />
	<field name="mtrc_stdb_reg" descr="" subnode="mtrc_stdb_reg_ext" capability="0" offset="0x0.0" selected_by="MTRC_STDB" size="0xc" />
	<field name="mtrc_stdb_v2" descr="" subnode="mtrc_stdb_v2_ext" capability="0" offset="0x0.0" selected_by="MTRC_STDB_V2" size="0x5a0" />
	<field name="mtutc_reg" descr="" subnode="mtutc_reg_ext" capability="0" offset="0x0.0" selected_by="MTUTC" size="0x1c" />
	<field name="mtwe" descr="" subnode="mtwe_ext" capability="0" offset="0x0.0" selected_by="MTWE" size="0x10" />
	<field name="mvcap_reg" descr="" subnode="mvcap_reg_ext" capability="0" offset="0x0.0" selected_by="MVCAP" size="0x10" />
	<field name="mvcr" descr="" subnode="mvcr_ext" capability="0" offset="0x0.0" selected_by="MVCR" size="0x18" />
	<field name="paos_reg" descr="" subnode="paos_reg_ext" capability="0" offset="0x0.0" selected_by="PAOS" size="0x10" />
	<field name="pbmc_reg" descr="" subnode="pbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PBMC" size="0x6c" />
	<field name="pbsr_reg" descr="" subnode="pbsr_reg_ext" capability="0" offset="0x0.0" selected_by="PBSR" size="0x64" />
	<field name="pbwc" descr="" subnode="pbwc_ext" capability="0" offset="0x0.0" selected_by="PBWC" size="0x8" />
	<field name="pbwr" descr="" subnode="pbwr_ext" capability="0" offset="0x0.0" selected_by="PBWR" size="0x94" />
	<field name="pcam_reg" descr="" subnode="pcam_reg_ext" capability="0" offset="0x0.0" selected_by="PCAM" size="0x50" />
	<field name="pcap_reg" descr="" subnode="pcap_reg_ext" capability="0" offset="0x0.0" selected_by="PCAP" size="0x14" />
	<field name="pcmr_reg" descr="" subnode="pcmr_reg_ext" capability="0" offset="0x0.0" selected_by="PCMR" size="0xc" />
	<field name="pddr_reg" descr="" subnode="pddr_reg_ext" capability="0" offset="0x0.0" selected_by="PDDR" size="0x100" />
	<field name="pevnt" descr="" subnode="pevnt_ext" capability="0" offset="0x0.0" selected_by="PEVNT" size="0x8" />
	<field name="pfcc_reg" descr="" subnode="pfcc_reg_ext" capability="0" offset="0x0.0" selected_by="PFCC" size="0x20" />
	<field name="pfsc_reg" descr="" subnode="pfsc_reg_ext" capability="0" offset="0x0.0" selected_by="PFSC" size="0x10" />
	<field name="pgmr" descr="" subnode="pgmr_ext" capability="0" offset="0x0.0" selected_by="PGMR" size="0x2c" />
	<field name="pguid_reg" descr="" subnode="pguid_reg_ext" capability="0" offset="0x0.0" selected_by="PGUID" size="0x60" />
	<field name="phbr" descr="" subnode="phbr_ext" capability="0" offset="0x0.0" selected_by="PHBR" size="0x1c" />
	<field name="phrr_reg" descr="" subnode="phrr_reg_ext" capability="0" offset="0x0.0" selected_by="PHRR" size="0x68" />
	<field name="plcc_reg" descr="" subnode="plcc_reg_ext" capability="0" offset="0x0.0" selected_by="PLCC" size="0x10" />
	<field name="plds" descr="" subnode="plds_ext" capability="0" offset="0x0.0" selected_by="PLDS" size="0x18" />
	<field name="plib_reg" descr="" subnode="plib_reg_ext" capability="0" offset="0x0.0" selected_by="PLIB" size="0x10" />
	<field name="plibdb" descr="" subnode="plibdb_ext" capability="0" offset="0x0.0" selected_by="PLIBDB" size="0x10" />
	<field name="pltc_reg" descr="" subnode="pltc_reg_ext" capability="0" offset="0x0.0" selected_by="PLTC" size="0x10" />
	<field name="pmaos_reg" descr="" subnode="pmaos_reg_ext" capability="0" offset="0x0.0" selected_by="PMAOS" size="0x10" />
	<field name="pmcr_reg" descr="" subnode="pmcr_reg_ext" capability="0" offset="0x0.0" selected_by="PMCR" size="0x2c" />
	<field name="pmdr_reg" descr="" subnode="pmdr_reg_ext" capability="0" offset="0x0.0" selected_by="PMDR" size="0x48" />
	<field name="pmlp_reg" descr="" subnode="pmlp_reg_ext" capability="0" offset="0x0.0" selected_by="PMLP" size="0x40" />
	<field name="pmmp_reg" descr="" subnode="pmmp_reg_ext" capability="0" offset="0x0.0" selected_by="PMMP" size="0x40" />
	<field name="pmpc_reg" descr="" subnode="pmpc_reg_ext" capability="0" offset="0x0.0" selected_by="PMPC" size="0x20" />
	<field name="pmpd_reg" descr="" subnode="pmpd_reg_ext" capability="0" offset="0x0.0" selected_by="PMPD" size="0x30" />
	<field name="pmpe_reg" descr="" subnode="pmpe_reg_ext" capability="0" offset="0x0.0" selected_by="PMPE" size="0x10" />
	<field name="pmpr_reg" descr="" subnode="pmpr_reg_ext" capability="0" offset="0x0.0" selected_by="PMPR" size="0x10" />
	<field name="pmpt_reg" descr="" subnode="pmpt_reg_ext" capability="0" offset="0x0.0" selected_by="PMPT" size="0x1c" />
	<field name="pmtm_reg" descr="" subnode="pmtm_reg_ext" capability="0" offset="0x0.0" selected_by="PMTM" size="0x10" />
	<field name="pmtu_reg" descr="" subnode="pmtu_reg_ext" capability="0" offset="0x0.0" selected_by="PMTU" size="0x10" />
	<field name="ppad_reg" descr="" subnode="ppad_reg_ext" capability="0" offset="0x0.0" selected_by="PPAD" size="0x10" />
	<field name="ppaos_reg" descr="" subnode="ppaos_reg_ext" capability="0" offset="0x0.0" selected_by="PPAOS" size="0x10" />
	<field name="ppbmc_reg" descr="" subnode="ppbmc_reg_ext" capability="0" offset="0x0.0" selected_by="PPBMC" size="0x10" />
	<field name="ppbme_reg" descr="" subnode="ppbme_reg_ext" capability="0" offset="0x0.0" selected_by="PPBME" size="0x10" />
	<field name="ppbmp_reg" descr="" subnode="ppbmp_reg_ext" capability="0" offset="0x0.0" selected_by="PPBMP" size="0x30" />
	<field name="ppcnt_reg" descr="" subnode="ppcnt_reg_ext" capability="0" offset="0x0.0" selected_by="PPCNT" size="0x100" />
	<field name="ppdfd" descr="" subnode="ppdfd_ext" capability="0" offset="0x0.0" selected_by="PPDFD" size="0xc" />
	<field name="pphcr" descr="" subnode="pphcr_ext" capability="0" offset="0x0.0" selected_by="PPHCR" size="0x5c" />
	<field name="pplm_reg" descr="" subnode="pplm_reg_ext" capability="0" offset="0x0.0" selected_by="PPLM" size="0x74" />
	<field name="pplr_reg" descr="" subnode="pplr_reg_ext" capability="0" offset="0x0.0" selected_by="PPLR" size="0x8" />
	<field name="pprm_reg" descr="" subnode="pprm_reg_ext" capability="0" offset="0x0.0" selected_by="PPRM" size="0x50" />
	<field name="pprt_reg" descr="" subnode="pprt_reg_ext" capability="0" offset="0x0.0" selected_by="PPRT" size="0x24" />
	<field name="ppsc_reg" descr="" subnode="ppsc_reg_ext" capability="0" offset="0x0.0" selected_by="PPSC" size="0x30" />
	<field name="ppslc" descr="" subnode="ppslc_ext" capability="0" offset="0x0.0" selected_by="PPSLC" size="0x34" />
	<field name="ppsld" descr="" subnode="ppsld_ext" capability="0" offset="0x0.0" selected_by="PPSLD" size="0x14" />
	<field name="ppsls" descr="" subnode="ppsls_ext" capability="0" offset="0x0.0" selected_by="PPSLS" size="0x8" />
	<field name="pptb_reg" descr="" subnode="pptb_reg_ext" capability="0" offset="0x0.0" selected_by="PPTB" size="0xc" />
	<field name="pptt_reg" descr="" subnode="pptt_reg_ext" capability="0" offset="0x0.0" selected_by="PPTT" size="0x1c" />
	<field name="prei_reg" descr="" subnode="prei_reg_ext" capability="0" offset="0x0.0" selected_by="PREI" size="0x18" />
	<field name="prtl_reg" descr="" subnode="prtl_reg_ext" capability="0" offset="0x0.0" selected_by="PRTL" size="0x20" />
	<field name="prtsr" descr="" subnode="prtsr_ext" capability="0" offset="0x0.0" selected_by="PRTSR" size="0x10" />
	<field name="ptasv2_reg" descr="" subnode="ptasv2_reg_ext" capability="0" offset="0x0.0" selected_by="PTASv2" size="0x30" />
	<field name="pter_reg" descr="" subnode="pter_reg_ext" capability="0" offset="0x0.0" selected_by="PTER" size="0x20" />
	<field name="ptsb" descr="" subnode="ptsb_ext" capability="0" offset="0x0.0" selected_by="PTSB" size="0x20" />
	<field name="ptsr" descr="" subnode="ptsr_ext" capability="0" offset="0x0.0" selected_by="PTSR" size="0x20" />
	<field name="ptys_reg" descr="" subnode="ptys_reg_ext" capability="0" offset="0x0.0" selected_by="PTYS" size="0x44" />
	<field name="pude_reg" descr="" subnode="pude_reg_ext" capability="0" offset="0x0.0" selected_by="PUDE" size="0x10" />
	<field name="pvlc_reg" descr="" subnode="pvlc_reg_ext" capability="0" offset="0x0.0" selected_by="PVLC" size="0x10" />
	<field name="resource_dump" descr="" subnode="resource_dump_ext" capability="0" offset="0x0.0" selected_by="MORD" size="0xc8" />
	<field name="sllm_reg" descr="" subnode="sllm_reg_ext" capability="0" offset="0x0.0" selected_by="SLLM" size="0x30" />
	<field name="slrg_reg" descr="" subnode="slrg_reg_ext" capability="0" offset="0x0.0" selected_by="SLRG" size="0x28" />
	<field name="sltp_reg" descr="" subnode="sltp_reg_ext" capability="0" offset="0x0.0" selected_by="SLTP" size="0x4c" />
	<field name="sltpv2_reg" descr="" subnode="sltpv2_reg_ext" capability="0" offset="0x0.0" selected_by="SLTPv2" size="0x10c" />
	<field name="ukdri" descr="" subnode="ukdri_ext" capability="0" offset="0x0.0" selected_by="UKDRI" size="0x10" />
	<field name="undfd" descr="" subnode="undfd_ext" capability="0" offset="0x0.0" selected_by="UNDFD" size="0x8" />
	<field name="undri" descr="" subnode="undri_ext" capability="0" offset="0x0.0" selected_by="UNDRI" size="0x10" />
	<field name="unrc" descr="" subnode="unrc_ext" capability="0" offset="0x0.0" selected_by="UNRC" size="0x40" />
	<field name="unrsa" descr="" subnode="unrsa_ext" capability="0" offset="0x0.0" selected_by="UNRSA" size="0x18" />
	<field name="unwkm" descr="" subnode="unwkm_ext" capability="0" offset="0x0.0" selected_by="UNWKM" size="0x8c" />
</node>

<node name="access_reg_summary_selector_ext" descr="" attr_is_union="1" size="0x5a0" >
	<field name="access_reg_summary" descr="" subnode="access_reg_summary_ext" offset="0x0.0" size="0x5a0" union_selector="$(parent).ctrl.id" />
	<field name="ctrl" descr="" subnode="access_reg_summary_ctrl_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="size" descr="The part of the packet buffer array is allocated for the specific buffer.\;Units are represented in cells.\;\;For shared_headroom_pool, this field represents the maximum loan from the shared headroom pool and it can be set only when port_shared_buffer is enabled.\;Range is 0..cap_max_shared_headroom_pool_loan_size. \;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="epsb" descr="Eligible for Port Shared buffer.\;If epsb is set, packets assigned to bufferX are allowed to insert the port shared buffer.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved.\;When lossy==1 this field is reserved.\;The field is reserved for Switch-X/-2." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="lossy" descr="The field indicates if the buffer is lossy.\;0: Lossless\;1: Lossy\;\;The field is reserved for Switch-X/-2.\;For port_shared_buffer, this field is reserved.\;For shared_headroom_pool, this field is reserved.\;NOTE: This field does NOT affect the pause control. Pause control is configured using PFCC register." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="xon_threshold" descr="When the amount of data in the buffer goes below this value, device stops sending pause frames for the Prios associated with the buffer. Units are represented in cells.\;In Spectrum xon_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_threshold" descr="Once the amount of data in the buffer goes above this value, device starts sending Pause frames for all Prios associated with the buffer. Units are represented in cells.\;In Spectrum xoff_threshold is reserved for buffer[9].\;For Spectrum, if lossy is set on, this field is reserved.\;For shared_headroom_pool, this field is reserved." access="RW" offset="0x4.16" size="0x0.16" />
</node>

<node name="command_payload_ext" descr="" size="0x104.0" >
	<field name="data" descr="Command data. It may be a request or a response data." access="RW" high_bound="64" low_bound="0" offset="0x0.0" size="0x104.0" />
</node>

<node name="config_item_ext" descr="" size="0xc.0" >
	<field name="length" descr="Length of configuration item data in bytes (not including header). Must be between 0 and 256." access="RW" offset="0x0.0" size="0x0.9" />
	<field name="host_id_valid" descr="Host ID valid:\;1: the type_index.host_id field is valid\;Valid only when MNVGC.priv_nv_other_host=1 and the type_class is a Host or Host-PF" access="INDEX" offset="0x0.9" size="0x0.1" />
	<field name="version" descr="Configuration item version - defines the data structure following the header (together with the type field)." access="RW" offset="0x0.12" size="0x0.4" />
	<field name="writer_id" descr="The entity which configured this parameter\;0x0: UNSPECIFIED\;0x1: CHASSIS_BMC\;0x2: MAD\;0x3: BMC\;0x4: COMMAND_INTERFACE\;0x5: ICMD - with unspecified source\;0x6: ICMD_UEFI_HII - configured by the NIC&apos;s UEFI expansion ROM&quot;s HII menu.\;0x7: ICMD_UEFI_CLP - configured by the NIC&apos;s expansion ROM&quot;s CLP.\;0x8: ICMD_Flexboot - configured by the NIC&quot;s legacy expansion ROM.\;0x9: ICMD_mlxconfig - configured by Mellanox mlxconfig tool\;0xA: ICMD_USER1 - value available for customer created tools that uses the ICMD interface for writing TLVs.\;0xB: ICMD_USER2 - value available for customer created tools that uses the ICMD interface for writing TLVs.\;0xC: ICMD_MLXCONFIG_SET_RAW - configures by\;mlxconfig set raw operation.\;0xD: ICMD_FLEXBOOT_CLP - configured by Legacy Expansion ROM CLP\;0x10: BMC_APP1 - Configuration was done over the BMC by application #1 (application name is OEM specific)\;0x11: BMC_APP2 - Configuration was done over the BMC by application #2 (application name is OEM specific)\;0x12: BMP_APP3 - Configuration was done over the BMC by application #3 (application name is OEM specific)\;0x1F: OTHER - the parameter was written by the NIC due to other reasons. \;\;Note - This field is writeable only when using the ICMD interface. The only value that are valid for writes are 0x6 through 0xB. Other values will be replaced by 0x5ICMD." access="RO" enum="UNSPECIFIED=0x0,CHASSIS_BMC=0x1,MAD=0x2,BMC=0x3,COMMAND_INTERFACE=0x4,ICMD=0x5,ICMD_UEFI_HII=0x6,ICMD_UEFI_CLP=0x7,ICMD_Flexboot=0x8,ICMD_mlxconfig=0x9,ICMD_USER1=0xa,ICMD_USER2=0xb,ICMD_MLXCONFIG_SET_RAW=0xc,ICMD_FLEXBOOT_CLP=0xd,BMC_APP1=0x10,BMC_APP2=0x11,BMP_APP3=0x12,OTHER=0x1f" offset="0x0.16" size="0x0.5" />
	<field name="access_mode" descr="Defines which value of the Configuration Item will be accessed.\;0: NEXT - Next value to be applied\;1: CURRENT - Currently set values (only valid for Query operation) Supported only if NVGC.nvda_read_current_settings==1.\;2: FACTORY - Default factory values (only valid for Query operation). Supported only if NVGC.nvda_read_factory_settings==1." access="INDEX" enum="NEXT=0x0,CURRENT=0x1,FACTORY=0x2" offset="0x0.22" size="0x0.2" />
	<field name="rd_en" descr="Read Enable\;Controls the read operation during different life-cycle stages.\;0: TLV cannot be read by the subsequent life-cycle priorities.\;1: TLV can be read by the subsequent life-cycle priorities." access="RW" offset="0x0.24" size="0x0.1" />
	<field name="ovr_en" descr="Override Enable\;0: Can only be overwritten by the current life-cycle priority.\;1: Allowed to be over-written by the subsequent life-cycle priorities." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="priority" descr="The life-cycle priority of this configuration.\;0x0: USER,\;0x1: OEM,\;0x2: Reserved  \;0x3: MLNX\;\;The priority is set by either:\;1. When using MNVDA, the TLV will have user priority\;2. When using NVCONFIG, each TLV has its own priority" access="RO" offset="0x0.28" size="0x0.2" />
	<field name="type" descr="Configuration item index according to its type_class. \;Table 377, &quot;Configuration Item Data Type Class Global Layout,&quot; on page 348\;Table 379, &quot;Configuration Item Data Type Class Physical Port Layout,&quot; on page 348\;Table 381, &quot;Configuration Item Data Type Class Per Host-PF Layout,&quot; on page 349\;Table 383, &quot;Configuration Item Data Type Class Log Layout,&quot; on page 349\;Table 385, &quot;Configuration Item Data Type Class File Layout,&quot; on page 350\;\;Table 387, &quot;Configuration Item Data Type Class Module Layout,&quot; on page 350\;Table 389, &quot;Configuration Item Data Type Class Multi Instance Layout,&quot; on page 351" subnode="config_item_type_auto_ext" access="INDEX" offset="0x4.0" size="0x4.0" />
</node>

<node name="config_item_type_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="configuration_item_type_class_file_ext" descr="" subnode="configuration_item_type_class_file_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_global_ext" descr="" subnode="configuration_item_type_class_global_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_log_ext" descr="" subnode="configuration_item_type_class_log_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_module_ext" descr="" subnode="configuration_item_type_class_module_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_multi_instance_ext" descr="" subnode="configuration_item_type_class_multi_instance_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_per_host_pf_ext" descr="" subnode="configuration_item_type_class_per_host_pf_ext" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_type_class_physical_port_ext" descr="" subnode="configuration_item_type_class_physical_port_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="configuration_item_type_class_file_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="type_class" descr="type_class = 0x6" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="configuration_item_type_class_global_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="type_class" descr="type_class = 0x0" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="configuration_item_type_class_log_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="type_class" descr="type_class = 0x5" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="configuration_item_type_class_module_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.14" />
	<field name="module_index" descr="Module Index" access="INDEX" offset="0x0.14" size="0x0.10" />
	<field name="type_class" descr="type_class = 0x9" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="configuration_item_type_class_multi_instance_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="type_class" descr="type_class = 0xA" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="configuration_item_type_class_per_host_pf_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="pf_index" descr="If host_id_valid is set, indicates the PF ID, otherwise reserved. \;" access="INDEX" offset="0x0.10" size="0x0.8" />
	<field name="host_id" descr="If host_id_valid is set, indicates the host ID, otherwise reserved. \;" access="INDEX" offset="0x0.18" size="0x0.6" />
	<field name="type_class" descr="type_class = 0x3" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="configuration_item_type_class_physical_port_ext" descr="" size="0x4.0" >
	<field name="parameter_index" descr="" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="type_class" descr="type_class = 0x1" access="INDEX" offset="0x0.24" size="0x0.8" />
</node>

<node name="crspace_access_payload_ext" descr="" size="0x104.0" >
	<field name="address" descr="Starting address" access="WO" offset="0x0.0" size="0x4.0" />
	<field name="data" descr="CrSpace data" access="RW" high_bound="63" low_bound="0" offset="0x4.0" size="0x100.0" />
</node>

<node name="crspace_timeout_ext" descr="" size="0xa0.0" >
	<field name="log_address" descr="crspace address accessed, which resulted in timeout" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="log_id" descr="which irisc triggered the timeout" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the timeout.\;\;[DWIP] Superseded by top level tile_v and tile_index. Kept for backwards compatibility." access="RO" offset="0x4.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:\;0: The timeout was from main\;1: The timeout was from a tile\;\;[DWIP] Superseded by top level tile_v and tile_index. Kept for backwards compatibility." access="RO" offset="0x4.23" size="0x0.1" />
	<field name="oe" descr="Old Event:\;0: New event\;1: Old event, found during MFGD activation" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="is_yu" descr="Timeout came from YU" access="RW" offset="0x4.29" size="0x0.1" />
	<field name="is_iron" descr="Timeout came from IRON" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="is_main_farm" descr="timeout came from Main Fram" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="log_ip" descr="IP (instruction pointer) that triggered the timeout" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="cvb_config_error_ext" descr="" size="0xa0.0" >
	<field name="cvb_error_type" descr="0: VDD configuration error\;1: DVDD configuration error" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the timeout." access="RO" offset="0x4.0" size="0x0.4" />
	<field name="tile_v" descr="Tile valid:\;0: The cvb configuration is main related\;1: The cvb configuration is tile related" access="RO" offset="0x4.31" size="0x0.1" />
</node>

<node name="date_time_layout_ext" descr="" size="0x8.0" >
	<field name="hours" descr="hour (UTC) - 2 packed BCD digits" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="minutes" descr="minutes - 2 packed BCD digits" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="seconds" descr="seconds - 2 packed BCD digits" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="day" descr="day - 2 packed BCD digits" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="month" descr="month - 2 packed BCD digits" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="year" descr="year - 4 packed BCD digits" access="RW" offset="0x4.16" size="0x0.16" />
</node>

<node name="enum_entry" descr="" size="0x4.0" >
</node>

<node name="eth_2819_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="ether_stats_drop_events_high" descr="The total number of events in which packets were dropped by the probe due to lack of resources.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ether_stats_drop_events_low" descr="The total number of events in which packets were dropped by the probe due to lack of resources.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ether_stats_octets_high" descr="The total number of octets of data (including those in bad packets) received (excluding framing bits but including FCS octets).\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ether_stats_octets_low" descr="The total number of octets of data (including those in bad packets) received (excluding framing bits but including FCS octets).\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ether_stats_pkts_high" descr="The total number of packets (including bad packets, broadcast packets, and multicast packets) received.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ether_stats_pkts_low" descr="The total number of packets (including bad packets, broadcast packets, and multicast packets) received.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_high" descr="The total number of good packets received that were directed to the broadcast address. \;Note: This does not include multicast packets.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ether_stats_broadcast_pkts_low" descr="The total number of good packets received that were directed to the broadcast address. \;Note: This does not include multicast packets.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_high" descr="The total number of good packets received that were directed to a multicast MAC address. \;Note: This number does not include packets directed to the broadcast address.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="ether_stats_multicast_pkts_low" descr="The total number of good packets received that were directed to a multicast MAC address. \;Note: This number does not include packets directed to the broadcast address.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_high" descr="The total number of packets received that had a length (excluding framing bits, but including FCS octets) of between 64 and MTU octets, inclusive, but had either a bad frame check sequence (FCS) with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="ether_stats_crc_align_errors_low" descr="The total number of packets received that had a length (excluding framing bits, but including FCS octets) of between 64 and MTU octets, inclusive, but had either a bad frame check sequence (FCS) with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_high" descr="The total number of packets received that were less than 64 octets long (excluding framing bits, but including FCS octets) and were otherwise well formed.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="ether_stats_undersize_pkts_low" descr="The total number of packets received that were less than 64 octets long (excluding framing bits, but including FCS octets) and were otherwise well formed.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_high" descr="The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets) but were otherwise well formed.\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="ether_stats_oversize_pkts_low" descr="The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets) but were otherwise well formed.\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="ether_stats_fragments_high" descr="The total number of packets received that were less than 64 octets in length (excluding framing bits but including FCS octets) and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="ether_stats_fragments_low" descr="The total number of packets received that were less than 64 octets in length (excluding framing bits but including FCS octets) and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="ether_stats_jabbers_high" descr="The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets), and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="ether_stats_jabbers_low" descr="The total number of packets received that were longer than MTU octets (excluding framing bits, but including FCS octets), and had either a bad FCS with an integral number of octets (FCS error) or a bad FCS with a non-integral number of octets (alignment error).\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="ether_stats_collisions_high" descr="The best estimate of the total number of collisions on this Ethernet segment.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ether_stats_collisions_low" descr="The best estimate of the total number of collisions on this Ethernet segment.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_high" descr="The total number of packets (including bad packets) received that were 64 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="ether_stats_pkts64octets_low" descr="The total number of packets (including bad packets) received that were 64 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_high" descr="The total number of packets (including bad packets) received that were between 65 and 127 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="ether_stats_pkts65to127octets_low" descr="The total number of packets (including bad packets) received that were between 65 and 127 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_high" descr="The total number of packets (including bad packets) received that were between 128 and 255 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="ether_stats_pkts128to255octets_low" descr="The total number of packets (including bad packets) received that were between 128 and 255 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_high" descr="The total number of packets (including bad packets) received that were between 256 and 511 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="ether_stats_pkts256to511octets_low" descr="The total number of packets (including bad packets) received that were between 256 and 511 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_high" descr="The total number of packets (including bad packets) received that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ether_stats_pkts512to1023octets_low" descr="The total number of packets (including bad packets) received that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad packets) received that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="ether_stats_pkts1024to1518octets_low" descr="The total number of packets (including bad packets) received that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad packets) received that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="ether_stats_pkts1519to2047octets_low" descr="The total number of packets (including bad packets) received that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad packets) received that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="ether_stats_pkts2048to4095octets_low" descr="The total number of packets (including bad packets) received that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x94.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad packets) received that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x98.0" size="0x4.0" />
	<field name="ether_stats_pkts4096to8191octets_low" descr="The total number of packets (including bad packets) received that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad packets) received that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).\;" access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="ether_stats_pkts8192to10239octets_low" descr="The total number of packets (including bad packets) received that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).\;" access="RO" offset="0xA4.0" size="0x4.0" />
</node>

<node name="eth_2863_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="if_in_octets_high" descr="The total number of octets received, including framing characters. Including MAC control frames.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="if_in_octets_low" descr="The total number of octets received, including framing characters. Including MAC control frames.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_high" descr="The number of packets successfully received, which were not addressed to a multicast or broadcast MAC address.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="if_in_ucast_pkts_low" descr="The number of packets successfully received, which were not addressed to a multicast or broadcast MAC address.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="if_in_discards_high" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="if_in_discards_low" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="if_in_errors_high" descr="The number of inbound packets that contained errors preventing them from being deliverable to a higher-layer protocol. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="if_in_errors_low" descr="The number of inbound packets that contained errors preventing them from being deliverable to a higher-layer protocol. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="if_in_unknown_protos_high" descr="The number of packets received via the interface which were discarded because of an unknown or unsupported protocol.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="if_in_unknown_protos_low" descr="The number of packets received via the interface which were discarded because of an unknown or unsupported protocol.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="if_out_octets_high" descr="The total number of octets transmitted out of the interface, including framing characters.\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="if_out_octets_low" descr="The total number of octets transmitted out of the interface, including framing characters.\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_high" descr="The total number of packets that higher-level protocols requested be transmitted and were not addressed to a multicast or broadcast MAC address, including those that were discarded or not sent.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="if_out_ucast_pkts_low" descr="The total number of packets that higher-level protocols requested be transmitted and were not addressed to a multicast or broadcast MAC address, including those that were discarded or not sent.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="if_out_discards_high" descr="The number of outbound packets which were chosen to be discarded, even though no errors had been detected to prevent their being transmitted. \;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="if_out_discards_low" descr="The number of outbound packets which were chosen to be discarded, even though no errors had been detected to prevent their being transmitted. \;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="if_out_errors_high" descr="The number of outbound packets that could not be transmitted because of errors.\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="if_out_errors_low" descr="The number of outbound packets that could not be transmitted because of errors.\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_high" descr="The number of packets successfully received, which were addressed to a multicast MAC address.\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="if_in_multicast_pkts_low" descr="The number of packets successfully received, which were addressed to a multicast MAC address.\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_high" descr="The number of packets successfully received, which were addressed to a broadcast MAC address.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="if_in_broadcast_pkts_low" descr="The number of packets successfully received, which were addressed to a broadcast MAC address.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_high" descr="The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a multicast MAC address, including those that were discarded or not sent.\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="if_out_multicast_pkts_low" descr="The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a multicast MAC address, including those that were discarded or not sent.\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_high" descr="The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a broadcast MAC address, including those that were discarded or not sent.\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="if_out_broadcast_pkts_low" descr="The total number of packets that higher-level protocols requested be transmitted, and which were addressed to a broadcast MAC address, including those that were discarded or not sent.\;" access="RO" offset="0x64.0" size="0x4.0" />
</node>

<node name="eth_3635_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="dot3stats_alignment_errors_high" descr="A count of frames received that are not an integral number of octets in length and do not pass the FCS check.\;" access="RW" offset="0x0.0" size="0x4.0" />
	<field name="dot3stats_alignment_errors_low" descr="A count of frames received that are not an integral number of octets in length and do not pass the FCS check.\;" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_high" descr="A count of frames received that are an integral number of octets in length but do not pass the FCS check. This count does not include frames received with frame-too-long or frame-too-short errors.\;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="dot3stats_fcs_errors_low" descr="A count of frames received that are an integral number of octets in length but do not pass the FCS check. This count does not include frames received with frame-too-long or frame-too-short errors.\;" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_high" descr="A count of frames that are involved in a single collision, and are subsequently transmitted successfully.\;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="dot3stats_single_collision_frames_low" descr="A count of frames that are involved in a single collision, and are subsequently transmitted successfully.\;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_high" descr="A count of frames that are involved in more than one collision and are subsequently transmitted successfully. \;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="dot3stats_multiple_collision_frames_low" descr="A count of frames that are involved in more than one collision and are subsequently transmitted successfully. \;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x1C.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_high" descr="A count of times that the SQE TEST ERROR is received on a particular interface.\;This counter does not increment on interfaces operating at speeds greater than 10 Mb/s, or on interfaces operating in full-duplex mode. \;" access="RW" offset="0x20.0" size="0x4.0" />
	<field name="dot3stats_sqe_test_errors_low" descr="A count of times that the SQE TEST ERROR is received on a particular interface.\;This counter does not increment on interfaces operating at speeds greater than 10 Mb/s, or on interfaces operating in full-duplex mode. \;" access="RW" offset="0x24.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_high" descr="A count of frames for which the first transmission attempt on a particular interface is delayed because the medium is busy. \;This counter does not increment when the interface is operating in full-duplex mode. \;" access="RW" offset="0x28.0" size="0x4.0" />
	<field name="dot3stats_deferred_transmissions_low" descr="A count of frames for which the first transmission attempt on a particular interface is delayed because the medium is busy. \;This counter does not increment when the interface is operating in full-duplex mode. \;" access="RW" offset="0x2C.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_high" descr="The number of times that a collision is detected on a particular interface later than one slotTime into the transmission of a packet.\;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x30.0" size="0x4.0" />
	<field name="dot3stats_late_collisions_low" descr="The number of times that a collision is detected on a particular interface later than one slotTime into the transmission of a packet.\;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x34.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_high" descr="A count of frames for which transmission on a particular interface fails due to excessive collisions.\;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x38.0" size="0x4.0" />
	<field name="dot3stats_excessive_collisions_low" descr="A count of frames for which transmission on a particular interface fails due to excessive collisions.\;This counter does not increment when the interface is operating in full-duplex mode.\;" access="RW" offset="0x3C.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_high" descr="A count of frames for which transmission failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x40.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_transmit_errors_low" descr="A count of frames for which transmission failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_high" descr="The number of times that the carrier sense condition was lost or never asserted when attempting to transmit a frame on a particular interface. \;This counter does not increment when the interface is operating in full-duplex mode. \;" access="RW" offset="0x48.0" size="0x4.0" />
	<field name="dot3stats_carrier_sense_errors_low" descr="The number of times that the carrier sense condition was lost or never asserted when attempting to transmit a frame on a particular interface. \;This counter does not increment when the interface is operating in full-duplex mode. \;" access="RW" offset="0x4C.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_high" descr="A count of frames received that exceed the maximum permitted frame size.\;" access="RW" offset="0x50.0" size="0x4.0" />
	<field name="dot3stats_frame_too_longs_low" descr="A count of frames received that exceed the maximum permitted frame size.\;" access="RW" offset="0x54.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_high" descr="A count of frames for which reception failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x58.0" size="0x4.0" />
	<field name="dot3stats_internal_mac_receive_errors_low" descr="A count of frames for which reception failed and were discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RW" offset="0x5C.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_high" descr="The number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate &quot;Receive Error&quot;.\;" access="RW" offset="0x60.0" size="0x4.0" />
	<field name="dot3stats_symbol_errors_low" descr="The number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate &quot;Receive Error&quot;.\;" access="RW" offset="0x64.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_high" descr="A count of MAC Control frames received that contain an opcode that is not supported.\;" access="RW" offset="0x68.0" size="0x4.0" />
	<field name="dot3control_in_unknown_opcodes_low" descr="A count of MAC Control frames received that contain an opcode that is not supported.\;" access="RW" offset="0x6C.0" size="0x4.0" />
	<field name="dot3in_pause_frames_high" descr="A count of MAC Control frames received with an opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x70.0" size="0x4.0" />
	<field name="dot3in_pause_frames_low" descr="A count of MAC Control frames received with an opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x74.0" size="0x4.0" />
	<field name="dot3out_pause_frames_high" descr="A count of MAC Control frames transmitted with an opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x78.0" size="0x4.0" />
	<field name="dot3out_pause_frames_low" descr="A count of MAC Control frames transmitted with an opcode indicating the PAUSE operation.\;\;" access="RW" offset="0x7C.0" size="0x4.0" />
</node>

<node name="eth_802_3_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="a_frames_transmitted_ok_high" descr="A count of frames that are successfully transmitted. \;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="a_frames_transmitted_ok_low" descr="A count of frames that are successfully transmitted. \;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="a_frames_received_ok_high" descr="A count of frames that are successfully received. This does not include frames received with frame-too-long, frame check sequence (FCS), length or alignment errors, or frames lost due to other MAC errors.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="a_frames_received_ok_low" descr="A count of frames that are successfully received. This does not include frames received with frame-too-long, frame check sequence (FCS), length or alignment errors, or frames lost due to other MAC errors.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="a_frame_check_sequence_errors_high" descr="A count of receive frames that are an integral number of octets in length and do not pass the FCS check. This does not include frames received with frame-too-long, or frame-too-short (frame fragment) errors.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="a_frame_check_sequence_errors_low" descr="A count of receive frames that are an integral number of octets in length and do not pass the FCS check. This does not include frames received with frame-too-long, or frame-too-short (frame fragment) errors.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="a_alignment_errors_high" descr="A count of frames that are not an integral number of octets in length and do not pass the FCS check.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="a_alignment_errors_low" descr="A count of frames that are not an integral number of octets in length and do not pass the FCS check.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="a_octets_transmitted_ok_high" descr="A count of data and padding octets of frames that are successfully transmitted.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="a_octets_transmitted_ok_low" descr="A count of data and padding octets of frames that are successfully transmitted.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="a_octets_received_ok_high" descr="A count of data and padding octets in frames that are successfully received. This does not include octets in frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to other MAC errors.\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="a_octets_received_ok_low" descr="A count of data and padding octets in frames that are successfully received. This does not include octets in frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to other MAC errors.\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="a_multicast_frames_xmitted_ok_high" descr="A count of frames that are successfully transmitted to a group destination address other than broadcast.\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="a_multicast_frames_xmitted_ok_low" descr="A count of frames that are successfully transmitted to a group destination address other than broadcast.\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="a_broadcast_frames_xmitted_ok_high" descr="A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded.\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="a_broadcast_frames_xmitted_ok_low" descr="A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded.\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="a_multicast_frames_received_ok_high" descr="A count of frames that are successfully received and directed to an active nonbroadcast group address. This does not include frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to internal MAC sublayer error. \;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="a_multicast_frames_received_ok_low" descr="A count of frames that are successfully received and directed to an active nonbroadcast group address. This does not include frames received with frame-too-long, FCS, length or alignment errors, or frames lost due to internal MAC sublayer error. \;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="a_broadcast_frames_received_ok_high" descr="A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded. \;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="a_broadcast_frames_received_ok_low" descr="A count of the frames that were successfully transmitted to the broadcast address. Frames transmitted to multicast addresses are not broadcast frames and are excluded. \;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="a_in_range_length_errors_high" descr="A count of frames with a length/type field value between the minimum unpadded MAC client data size and the maximum allowed MAC client data size, inclusive, that does not match the number of MAC client data octets received. The counter also increments for frames whose length/type field value is less than the minimum allowed unpadded MAC client data size and the number of MAC client data octets received is greater than the minimum unpadded MAC client data size.\;" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="a_in_range_length_errors_low" descr="A count of frames with a length/type field value between the minimum unpadded MAC client data size and the maximum allowed MAC client data size, inclusive, that does not match the number of MAC client data octets received. The counter also increments for frames whose length/type field value is less than the minimum allowed unpadded MAC client data size and the number of MAC client data octets received is greater than the minimum unpadded MAC client data size.\;" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="a_out_of_range_length_field_high" descr="A count of frames with a length field value greater than the maximum allowed LLC data size. \;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="a_out_of_range_length_field_low" descr="A count of frames with a length field value greater than the maximum allowed LLC data size. \;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="a_frame_too_long_errors_high" descr="A count of frames received that exceed the maximum permitted frame size by IEEE 802.3 (MTU size).\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="a_frame_too_long_errors_low" descr="A count of frames received that exceed the maximum permitted frame size by IEEE 802.3 (MTU size).\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="a_symbol_error_during_carrier_high" descr="For full duplex operation at 1000 Mb/s, it is a count of the number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate &quot;Data reception error&quot;.\;For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/s, it is a count of the number of times the receiving media is non-idle for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate\;Error.\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="a_symbol_error_during_carrier_low" descr="For full duplex operation at 1000 Mb/s, it is a count of the number of times the receiving media is non-idle (a carrier event) for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate &quot;Data reception error&quot;.\;For operation at 10 Gb/s, 40 Gb/s, and 100 Gb/s, it is a count of the number of times the receiving media is non-idle for a period of time equal to or greater than minFrameSize, and during which there was at least one occurrence of an event that causes the PHY to indicate\;Error.\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="a_mac_control_frames_transmitted_high" descr="A count of MAC Control frames passed to the MAC sublayer for transmission.\;" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="a_mac_control_frames_transmitted_low" descr="A count of MAC Control frames passed to the MAC sublayer for transmission.\;" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="a_mac_control_frames_received_high" descr="A count of MAC Control frames passed by the MAC sublayer to the MAC Control sublayer.\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="a_mac_control_frames_received_low" descr="A count of MAC Control frames passed by the MAC sublayer to the MAC Control sublayer.\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="a_unsupported_opcodes_received_high" descr="A count of MAC Control frames received that contain an opcode that is not supported by the device.\;" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="a_unsupported_opcodes_received_low" descr="A count of MAC Control frames received that contain an opcode that is not supported by the device.\;" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_received_high" descr="A count of MAC PAUSE frames passed by the MAC sublayer to the MAC Control sublayer.\;" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_received_low" descr="A count of MAC PAUSE frames passed by the MAC sublayer to the MAC Control sublayer.\;" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_transmitted_high" descr="A count of PAUSE frames passed to the MAC sublayer for transmission.\;" access="RO" offset="0x90.0" size="0x4.0" />
	<field name="a_pause_mac_ctrl_frames_transmitted_low" descr="A count of PAUSE frames passed to the MAC sublayer for transmission.\;" access="RO" offset="0x94.0" size="0x4.0" />
</node>

<node name="eth_discard_cntrs_grp_ext" descr="" size="0xf8.0" >
	<field name="ingress_general_high" descr="Ingress general \;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="ingress_general_low" descr="Ingress general \;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ingress_policy_engine_high" descr="Ingress policy engine discards" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ingress_policy_engine_low" descr="Ingress policy engine discards" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ingress_vlan_membership_high" descr="Ingress VLAN membership filter discards" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="ingress_vlan_membership_low" descr="Ingress VLAN membership filter discards" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_high" descr="Ingress VLAN tag allowance (tagged, untagged and prio-tagged) filter discards" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ingress_tag_frame_type_low" descr="Ingress VLAN tag allowance (tagged, untagged and prio-tagged) filter discards" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="egress_vlan_membership_high" descr="Egress VLAN membership filter discards" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="egress_vlan_membership_low" descr="Egress VLAN membership filter discards" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="loopback_filter_high" descr="Loop-back filter discards" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="loopback_filter_low" descr="Loop-back filter discards" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="egress_general_high" descr="Egress general discards\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="egress_general_low" descr="Egress general discards\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="egress_hoq_high" descr="Head-of-Queue time-out discards" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="egress_hoq_low" descr="Head-of-Queue time-out discards" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="port_isolation_high" descr="Port isolation filter discards" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_isolation_low" descr="Port isolation filter discards" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="egress_policy_engine_high" descr="Egress policy engine discards" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="egress_policy_engine_low" descr="Egress policy engine discards" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="ingress_tx_link_down_high" descr="Per ingress port count dropped packets due to egress link down" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="ingress_tx_link_down_low" descr="Per ingress port count dropped packets due to egress link down" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="egress_stp_filter_high" descr="Egress spanning tree filter" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="egress_stp_filter_low" descr="Egress spanning tree filter" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="egress_hoq_stall_high" descr="Number of sequential packets dropped, due to Head-Of-Queue Lifetime Limit, that causes the port to enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="egress_hoq_stall_low" descr="Number of sequential packets dropped, due to Head-Of-Queue Lifetime Limit, that causes the port to enter the Stall state \;\;Reserved for Switches" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="egress_sll_high" descr="Number of packets dropped, because the Switch Lifetime Limit was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="egress_sll_low" descr="Number of packets dropped, because the Switch Lifetime Limit was exceeded. \;\;Applies for switches only. Reserved for HCAs" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="ingress_discard_all_high" descr="Number of packets dropped for of any reason.\; Note: see description in the description area for limitations of this counter.\;Applies for switches only. Reserved for HCAs\;\;Note: deprecated for all Ethernet devices" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="ingress_discard_all_low" descr="Number of packets dropped for of any reason.\; Note: see description in the description area for limitations of this counter.\;Applies for switches only. Reserved for HCAs\;\;Note: deprecated for all Ethernet devices" access="RO" offset="0x7C.0" size="0x4.0" />
</node>

<node name="eth_extended_cntrs_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="port_transmit_wait_high" descr="The time (in 4ns resolution) during which the port selected had data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="port_transmit_wait_low" descr="The time (in 4ns resolution) during which the port selected had data to transmit but no data was sent.\;time = port_transmit_wait*4 [ns]\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_high" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;Valid only for Spectrum family.\;\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_low" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;Valid only for Spectrum family.\;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_high" descr="The number of multicast packets dropped due to lack of egress buffer resources.\;Valid only for Spectrum.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="no_buffer_discard_mc_low" descr="The number of multicast packets dropped due to lack of egress buffer resources.\;Valid only for Spectrum.\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="rx_ebp_high" descr="The number of received EBP packets.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="rx_ebp_low" descr="The number of received EBP packets.\;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="tx_ebp_high" descr="The number of transmitted EBP packets.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="tx_ebp_low" descr="The number of transmitted EBP packets.\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_high" descr="The number of events where the port rx buffer has passed a fullness threshold \;\;Reserved for Switches." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="rx_buffer_almost_full_low" descr="The number of events where the port rx buffer has passed a fullness threshold \;\;Reserved for Switches." access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="rx_buffer_full_high" descr="The number of events where the port rx buffer has reached 100% fullness \;\;Reserved for Switches." access="RO" offset="0x30.0" size="0x4.0" />
	<field name="rx_buffer_full_low" descr="The number of events where the port rx buffer has reached 100% fullness \;\;Reserved for Switches." access="RO" offset="0x34.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_high" descr="The number of roce packets with ICRC error\;\;Reserved for Switches." access="RO" offset="0x38.0" size="0x4.0" />
	<field name="rx_icrc_encapsulated_low" descr="The number of roce packets with ICRC error\;\;Reserved for Switches." access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_high" descr="The total number of packets (including bad packets) transmitted that were 64 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="tx_stats_pkts64octets_low" descr="The total number of packets (including bad packets) transmitted that were 64 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_high" descr="The total number of packets (including bad packets) transmitted that were between 65 and 127 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x58.0" size="0x4.0" />
	<field name="tx_stats_pkts65to127octets_low" descr="The total number of packets (including bad packets) transmitted that were between 65 and 127 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_high" descr="The total number of packets (including bad packets) transmitted that were between 128 and 255 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_stats_pkts128to255octets_low" descr="The total number of packets (including bad packets) transmitted that were between 128 and 255 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_high" descr="The total number of packets (including bad packets) transmitted that were between 256 and 511 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_stats_pkts256to511octets_low" descr="The total number of packets (including bad packets) transmitted that were between 256 and 511 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_high" descr="The total number of packets (including bad packets) transmitted that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="tx_stats_pkts512to1023octets_low" descr="The total number of packets (including bad packets) transmitted that were between 512 and 1023 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_high" descr="The total number of packets (including bad packets) transmitted that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x78.0" size="0x4.0" />
	<field name="tx_stats_pkts1024to1518octets_low" descr="The total number of packets (including bad packets) transmitted that were between 1024 and 1518 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_high" descr="The total number of packets (including bad packets) transmitted that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="tx_stats_pkts1519to2047octets_low" descr="The total number of packets (including bad packets) transmitted that were between 1519 and 2047 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_high" descr="The total number of packets (including bad packets) transmitted that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="tx_stats_pkts2048to4095octets_low" descr="The total number of packets (including bad packets) transmitted that were between 2048 and 4095 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_high" descr="The total number of packets (including bad packets) transmitted that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="tx_stats_pkts4096to8191octets_low" descr="The total number of packets (including bad packets) transmitted that were between 4096 and 8191 octets in length (excluding framing bits but including FCS octets)." access="RO" offset="0x94.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_high" descr="The total number of packets (including bad packets) transmitted that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).transmitted\;" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="tx_stats_pkts8192to10239octets_low" descr="The total number of packets (including bad packets) transmitted that were between 8192 and 10239 octets in length (excluding framing bits but including FCS octets).transmitted\;" access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="ece_marked_high" descr="A count of packets marked as ECE or potentially marked as ECE." access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="ece_marked_low" descr="A count of packets marked as ECE or potentially marked as ECE." access="RO" offset="0xA4.0" size="0x4.0" />
	<field name="tx_int_cksm_err_high" descr="Counter is incremented upon packet payload internal checksum error" access="RO" offset="0xA8.0" size="0x4.0" />
	<field name="tx_int_cksm_err_low" descr="Counter is incremented upon packet payload internal checksum error" access="RO" offset="0xAC.0" size="0x4.0" />
</node>

<node name="eth_per_prio_grp_data_layout_ext" descr="" size="0xf8.0" >
	<field name="rx_octets_high" descr="The total number of octets received, including framing characters.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="rx_octets_low" descr="The total number of octets received, including framing characters.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="rx_frames_high" descr="The total number of packets received for this priority (not including pause frames).\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="rx_frames_low" descr="The total number of packets received for this priority (not including pause frames).\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="tx_octets_high" descr="The total number of octets transmitted, including framing characters.\;\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="tx_octets_low" descr="The total number of octets transmitted, including framing characters.\;\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="tx_frames_high" descr="The total number of packets transmitted.\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="tx_frames_low" descr="The total number of packets transmitted.\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="rx_pause_high" descr="The total number of PAUSE frames received from the far-end port." access="RO" offset="0x50.0" size="0x4.0" />
	<field name="rx_pause_low" descr="The total number of PAUSE frames received from the far-end port." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="rx_pause_duration_high" descr="The total time in microseconds that transmission of packets to the far-end port have been paused.\;Note that if pause is global then tclass &quot;0&quot; will increment\;" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="rx_pause_duration_low" descr="The total time in microseconds that transmission of packets to the far-end port have been paused.\;Note that if pause is global then tclass &quot;0&quot; will increment\;" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="tx_pause_high" descr="The total number of PAUSE or PFC frames sent to the far-end port.\;" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="tx_pause_low" descr="The total number of PAUSE or PFC frames sent to the far-end port.\;" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="tx_pause_duration_high" descr="The total time in microseconds that the far-end port have been requested to pause.\;\;" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="tx_pause_duration_low" descr="The total time in microseconds that the far-end port have been requested to pause.\;\;" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="rx_pause_transition_high" descr="Counts the number of transitions from Xoff to Xon.\;" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="rx_pause_transition_low" descr="Counts the number of transitions from Xoff to Xon.\;" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rx_discards_high" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rx_discards_low" descr="The number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being deliverable to a higher-layer protocol.\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period longer than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause)." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="device_stall_minor_watermark_cnt_low" descr="The number of times the device detected a stalled state for a period longer than device_stall_minor_watermark\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause)." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_high" descr="The number of times the device detected a stalled state for a period longer than device_stall_critical_watermark.\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause)." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="device_stall_critical_watermark_cnt_low" descr="The number of times the device detected a stalled state for a period longer than device_stall_critical_watermark.\;The counter is presented in priority 0, but is a sum of all events on all priorities (including global pause)." access="RO" offset="0x8C.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_cong_layout_ext" descr="" size="0xf8.0" >
	<field name="wred_discard_high" descr="The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="wred_discard_low" descr="The number of packet that are dropped by the Weighted Random Early Detection (WRED) function.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="ecn_marked_tc_high" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="ecn_marked_tc_low" descr="A count of packets marked as ECN or potentially marked as ECN.\;ECN Counting enable/disable is configurable. \;" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="eth_per_traffic_class_layout_ext" descr="" size="0xf8.0" >
	<field name="transmit_queue_high" descr="Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="transmit_queue_low" descr="Contains the transmit queue depth in bytes on traffic class selected by traffic_class of the port selected by local_port.\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_high" descr="The number of unicast packets dropped due to lack of shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="no_buffer_discard_uc_low" descr="The number of unicast packets dropped due to lack of shared buffer resources.\;Valid only for Spectrum.\;Valid for HCA when ppcnt_no_buffer_uc is set in PCAM." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="fatal_cause_ext" descr="" size="0xa0.0" >
	<field name="cause_id" descr="HW / FW cause ID\;\;FW Causes (When fw_cause = 1):\;1: Core PLL lock failure\;\;When test = 1 AND fw_cause = 0, cause ID = 0xCAFE" access="RO" offset="0x0.0" size="0x0.20" />
	<field name="fw_cause" descr="0: cause_id reflects HW cause ID\;1: cause_id reflects FW cause (event)" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="test" descr="Test:\;0: real cause ID\;1: test cause ID" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the assert.\;\;[DWIP] Superseded by top level tile_v and tile_index. Kept for backwards compatibility." access="RO" offset="0x4.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:\;0: The assert was from main\;1: The assert was from a tile\;\;[DWIP] Superseded by top level tile_v and tile_index. Kept for backwards compatibility." access="RO" offset="0x4.23" size="0x0.1" />
</node>

<node name="flow_estimator_record_ext" descr="" size="0x8.0" >
	<field name="num_rec" descr="Number of records to read\;Range 1..cap_max_flow_estimator_bins" access="RW" offset="0x0.0" size="0x0.11" />
	<field name="counter_index_base" descr="Counter Index base\;Range 0..cap_shared_counter_pool_size - 1" access="RW" offset="0x4.0" size="0x0.24" />
</node>

<node name="fore_ext" descr="" size="0xc.0" >
	<field name="fan_under_limit" descr="Fan speed is below the low limit defined in MFSL register. Each bit relates to a single tachometer and indicates the specific tachometer reading is below the threshold.\;Bitmask, per bit:\;0: not_under_thr\;1: under_thr" access="RO" offset="0x0.16" size="0x0.10" />
	<field name="fan_under_limit_msb" descr="Fan speed is below the low limit defined in MFSL register. Each bit relates to a single tachometer and indicates the specific tachometer reading is below the threshold.\;Bitmask, per bit:\;0: not_under_thr\;1: under_thr" access="RO" offset="0x0.26" size="0x0.6" />
	<field name="fan_over_limit" descr="Fan speed is above the high limit defined in MFSL register. Each bit relates to a single tachometer and indicates the specific tachometer reading is above the threshold.\;Bitmask, per bit:\;0: not_over_limit\;1: over_limit" access="RO" offset="0x4.16" size="0x0.10" />
	<field name="fan_over_limit_msb" descr="Fan speed is above the high limit defined in MFSL register. Each bit relates to a single tachometer and indicates the specific tachometer reading is above the threshold.\;Bitmask, per bit:\;0: not_over_limit\;1: over_limit" access="RO" offset="0x4.26" size="0x0.6" />
</node>

<node name="fw_assert_ext" descr="" size="0xa0.0" >
	<field name="assert_var0" descr="This is the 1st variable passed to assert" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="assert_var1" descr="This is the 2nd variable passed to assert" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="assert_var2" descr="This is the 3rd variable passed to assert" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="assert_var3" descr="This is the 4th variable passed to assert" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="assert_var4" descr="This is the 5th variable passed to assert" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="assert_exinstptr" descr="this is instruction pointer when assert was triggered" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="assert_callra" descr="This is the next return address after triggering assert" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="ext_synd" descr="Extended syndrome" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the assert.\;\;[DWIP] Superseded by top level tile_v and tile_index. Kept for backwards compatibility." access="RO" offset="0x1C.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:\;0: The assert was from main\;1: The assert was from a tile\;\;[DWIP] Superseded by top level tile_v and tile_index. Kept for backwards compatibility." access="RO" offset="0x1C.23" size="0x0.1" />
	<field name="oe" descr="Old Event:\;0: New event\;1: Old event, found during MFGD activation" access="RO" offset="0x1C.24" size="0x0.1" />
	<field name="test" descr="Test:\;0: real cause ID\;1: test cause ID (cause ID = 0xCAFE)" access="RO" offset="0x1C.31" size="0x0.1" />
	<field name="assert_string" descr="String provided by the device\;Endianity:\;Offset 04h[31:24] - byte0\;Offset 04h[23:16] - byte1\;Offset 04h[15:8] - byte2\;Offset 04h[7:0] - byte3\;Offset 08h[31:24] - byte4\;etc." access="RO" high_bound="31" low_bound="0" offset="0x20.0" size="0x80.0" />
</node>

<node name="ghpkt_ext" descr="" size="0x10.0" >
	<field name="trap_id" descr="Trap IDs\;See Section 1359, &quot;GPUNet Trap IDs&quot;, on page 1497" access="INDEX" offset="0x0.0" size="0x0.10" />
	<field name="action" descr="Action to perform on trap_id\;0: NOP \;1: TRAP" access="RW" enum="NOP=0x0,TRAP=0x1" offset="0x0.20" size="0x0.4" />
</node>

<node name="gplid_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lid" descr="The Port LID configured to the GPU Port. \;[Internal] Notice: the port LID has 20 bits for future compatibility, but only the 16 LSBs are being used." access="RO" offset="0x4.0" size="0x0.20" />
</node>

<node name="gsguid_ext" descr="" size="0x10.0" >
	<field name="system_guid_h" descr="The system GUID of the device." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="system_guid_l" descr="The system GUID of the device." access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="hst_link_eth_enabled_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="hst_link_ib_enabled_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="kvd_im_stop_ext" descr="" size="0xa0.0" >
	<field name="pipes_mask" descr="Bit per kvh pipe" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="oe" descr="Old Event:\;0: New event\;1: Old event, found during MFGD activation" access="RO" offset="0x0.24" size="0x0.1" />
</node>

<node name="lane_2_module_mapping_ext" descr="" size="0x4.0" >
	<field name="module" descr="Module field is considered as Label index when mod_lab_map = label_mapping_selected (= 1)\;Module or Label number" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA.\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="RW" offset="0x0.8" size="0x0.4" />
	<field name="sub_module" descr="Indicates start offset of rx_lane, tx_lane inside the modules lanes in 8x granularity. relevant for modules with more than 8 lanes. such as OE.\;0: lanes_0-7\;1: lanes_8_15\;2: lanes_16_23\;3: lanes_24_31" access="RW" offset="0x0.12" size="0x0.4" />
	<field name="tx_lane" descr="TX lane. \;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is cleared, this field is used for RX as well." access="RW" offset="0x0.16" size="0x0.4" />
	<field name="rx_lane" descr="RX lane.\;When m_lane_m field is set, this field is ignored (Reserved). \;When rxtx field is clreared, for set operation this field is ignored and for get operation may return invalid value, Rx mapping for get should be taken from tx_lane." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="bidi_map" descr="Supported if PCAM.feature_cap_mask bit 116 is set, otherwise field is not valid.\;Relevant for Bidi port only, Simplex port should ignore.\;indicates if module lane Tx or Rx is used.\;0: module_rx_lane_valid - Bidi lane uses module rx lane. \;tx lane value is not valid should be ignored\;1: module_tx_lane_valid - Bidi lane uses module tx lane. \;rx lane value is not valid should be ignored" access="RO" offset="0x0.30" size="0x0.1" />
</node>

<node name="local_span_ext" descr="" size="0x10.0" >
	<field name="tclass" descr="Traffic Class on which the mirrored packet is queued\;For Spectrum switches: Switch Priority\;Reserved when qos is QoS maintain\;Reserved when system_port is to CPU since HTGT.cpu_tclass is used\;Reserved when imp=1" access="RW" offset="0xC.0" size="0x0.4" />
</node>

<node name="mafbi_entry_auto_ext" descr="" attr_is_union="1" size="0x300.0" >
	<field name="mafbi_entry_type0_ext" descr="" subnode="mafbi_entry_type0_ext" offset="0x0.0" selected_by="entry_type0" size="0x300.0" />
</node>

<node name="mafbi_entry_type0_ext" descr="" size="0x300.0" >
	<field name="record" descr="See Table 1232, &quot;MAFTI - record Layout,&quot; on page 1344" subnode="mafti_record_ext" access="RW" high_bound="63" low_bound="0" offset="0x0.0" size="0x300.0" />
</node>

<node name="mafbi_ext" descr="" size="0x308.0" >
	<field name="num_rec" descr="Number of records\;Range 1..64\;\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="type" descr="Type:\;0: entry_type0 - Looks like MAFTI w/o bank_id" access="RO" enum="entry_type0=0x0" offset="0x0.24" size="0x0.2" />
	<field name="entry" descr="See Table 1236, &quot;MAFBI - entry_type0 Layout,&quot; on page 1346" subnode="mafbi_entry_auto_ext" access="RW" offset="0x8.0" size="0x300.0" union_selector="$(parent).type" />
</node>

<node name="mafcr_ext" descr="" size="0xc.0" >
	<field name="clear" descr="Clear counter_accu_overflow counter" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="counter_accu_overflow" descr="Counter of accuflow overflow.\;When system behaves &quot;well&quot; then this counter will always be 0.\;If ((FW polling is too slow) or (HW increment is too high)) then the HW accuflow becomes overflowed. In this case new accuflow counter increments are not counted.\;This counter is stuck at 0xF...FF" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="bytes_inc_units" descr="Bytes inc units\;Units of 1 byte\;Note: this value will change only after boot/ISSU \;\;\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="packets_inc_units" descr="Backets inc units\;Units of 1 packet\;Note: this value will change only after boot/ISSU \;\;" access="RO" offset="0x8.16" size="0x0.16" />
</node>

<node name="mafri_ext" descr="" size="0x410.0" >
	<field name="num_rec" descr="Number of records to read\;Range 1..128" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="event" descr="Event generation:\;0: NO_EVENT - Do not generate MAFRI event\;1: EVENTS - Generate MAFRI event\;Note: return of EMAD must be after the MAFRI event!" access="OP" offset="0x0.16" size="0x0.1" />
	<field name="fsf" descr="Flush spill fifo\;0: NO_FLUSH_SPILL\;1: FLUSH_SPILL - will trigger MAFTI events for all relevant spill -fifos\;Note: return of EMAD must be after the MAFTI event! if both fsf and event are set, MAFTI event will be sent before MAFRI event.\;" access="OP" offset="0x0.24" size="0x0.1" />
	<field name="counter_index_base" descr="Counter Index base\;Counters will be read starting at counter_index_base\;Range: cap_start_accuflow .. cap_start_accuflow+cap_max_accuflow - 1\;Note: counter_index_base + num_rec must be equal or lower than cap_max_accuflow" access="OP" offset="0x4.0" size="0x0.24" />
	<field name="user_val" descr="User val:\;Opaque field to be returned on MAFRI trap" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="record" descr="See Table 1240, &quot;MAFRI - record Layout,&quot; on page 1348\;When event = 1, the records will be zero." subnode="mafri_record_ext" access="RW" high_bound="127" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="mafri_record_ext" descr="" size="0x8.0" >
	<field name="bytes_inc" descr="Bytes to increment to bytes counter\;Unit of MAFCR.bytes_inc_units\;Note that user needs to add 64B for each packet\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="packets_inc" descr="Packets to increment to packets counter\;Unit is MAFCR.packets_inc_units\;" access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="mafti_ext" descr="" size="0x308.0" >
	<field name="num_rec" descr="Number of records\;Range 1..64\;\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="record" descr="See Table 1232, &quot;MAFTI - record Layout,&quot; on page 1344" subnode="mafti_record_ext" access="RW" high_bound="63" low_bound="0" offset="0x8.0" size="0x300.0" />
</node>

<node name="mafti_record_ext" descr="" size="0xc.0" >
	<field name="counter_index" descr="Counter Index for flow counters.\;Note: different MAFTI records may have the exact same counter_index.\;For Spectrum-2 see Section 5.2, &quot;Flow Counters&quot;, on page 1254" access="RO" offset="0x0.0" size="0x0.24" />
	<field name="bytes_inc" descr="Bytes to increment to bytes counter\;Unit of MAFCR.bytes_inc_units\;Note that user needs to add 64B for each packet\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="packets_inc" descr="Packets to increment to packets counter\;Unit is MAFCR.packets_inc_units\;" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mbct_ext" descr="" size="0x420.0" >
	<field name="slot_index" descr="Slot index. \;0: Reserved." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="data_size" descr="actual data field size in bytes for the current data transfer" access="WO" offset="0x4.0" size="0x0.11" />
	<field name="ini_status" descr="ini status\;0: Empty_not_valid\;1: Valid - (Magic Pattern applied)\;2: Ready_to_use\;3: In_use\;Other values are Reserved" access="RO" enum="Empty_not_valid=0x0,Valid=0x1,Ready_to_use=0x2,In_use=0x3" offset="0x4.29" size="0x0.3" />
	<field name="oee" descr="Opcode Event Enable. When set to &apos;1&apos;, an event will be sent once the opcode was executed and the fsm_state has changed. This bit will be cleared once the event was sent." access="WO" offset="0x8.25" size="0x0.1" />
	<field name="last" descr="Indicates that the current data field is the last chunk of the INI." access="WO" offset="0x8.26" size="0x0.1" />
	<field name="op" descr="When the register is used in a &apos;Query&apos; mode, only option 7 (Query Status) is legal.\;0: Reserved\;1: Erase_INI_image\;2: Data_transfer - (download)\;3: Activate\;4: Deactivate\;5: Abort\;6: Clear_Errors\;7: Query_Status\;Other values are Reserved" access="WO" enum="Reserved=0x0,Erase_INI_image=0x1,Data_transfer=0x2,Activate=0x3,Deactivate=0x4,Abort=0x5,Clear_Errors=0x6,Query_Status=0x7" offset="0x8.28" size="0x0.4" />
	<field name="fsm_state" descr="0: Idle\;1: Data_transfer - (download)\;2: Magic_Pattern_Valid\;3: Ready\;4: Erase\;5: INI_in_use\;6: Error\;Other values are Reserved" access="RO" enum="Idle=0x0,Data_transfer=0x1,Magic_Pattern_Valid=0x2,Ready=0x3,Erase=0x4,INI_in_use=0x5,Error=0x6" offset="0xC.16" size="0x0.4" />
	<field name="status" descr="Status\;0: NA\;1: Busy\;2: Partial - partial data transfer completed successfully and ready for next data transfer\;3: Last_data - last data transfer completed, applying magic pattern. \;4: Erase_is_complete\;5: Error_Attempted_Erase_INI_in_use - Trying to erase INI while it being used.\;6: Transfer_failure - (bad data received or write error)\;7: Erase_failure\;8: INI_error\;9: Activation_of_INI_failed\;10: Deactivation_of_INI_failed\;11: Error_Illegal_operation\;Other values are Reserved" access="RO" enum="NA=0x0,Busy=0x1,Partial=0x2,Last_data=0x3,Erase_is_complete=0x4,Error_Attempted_Erase_INI_in_use=0x5,Transfer_failure=0x6,Erase_failure=0x7,INI_error=0x8,Activation_of_INI_failed=0x9,Deactivation_of_INI_failed=0xa,Error_Illegal_operation=0xb" offset="0xC.24" size="0x0.5" />
	<field name="data" descr="Up to 1KB of data." access="WO" high_bound="255" low_bound="0" offset="0x20.0" size="0x400.0" />
</node>

<node name="mbtr_ext" descr="" size="0x8.0" >
	<field name="cmd" descr="Command\;0: Perform_graceful_reset_procedure -  Not supported for query operations. Will return BAD_PARAM.\;1: PVS_tuning_was_set" access="WO" enum="Perform_graceful_reset_procedure=0x0,PVS_tuning_was_set=0x1" offset="0x0.0" size="0x0.8" />
	<field name="status" descr="0: Success\;1: ADC_value_is_out_of_limit\;2: ADC_cant_be_compared_due_to_fuse_not_burned \;3: ADC_cant_be_compared_due_to_invalid_fuse_value\;Valid only if cmd = 1" access="RO" enum="Success=0x0,ADC_value_is_out_of_limit=0x1,ADC_cant_be_compared_due_to_fuse_not_burned=0x2,ADC_cant_be_compared_due_to_invalid_fuse_value=0x3" offset="0x4.0" size="0x0.8" />
</node>

<node name="mcam_reg_ext" descr="" size="0x48.0" >
	<field name="access_reg_group" descr="Access Register ID groups \;0: First_128_REG_ID - Register IDs 0x9001 - 0x907F)\;1: Register_IDs_0x9080 - 0x90FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9080 while bit 127 represents register ID 0x90FF).\;2: Register_IDs_0x9100 - 0x917F (bit 0 in mng_access_reg_cap_mask represent register ID 0x9100 while bit 127 represents register ID 0x917F).\;3: Register_IDs_0x9180 - 0x91FF (bit 0 in mng_access_reg_cap_mask represent register ID 0x9180 while bit 127 represents register ID 0x91FF)." access="INDEX" enum="First_128_REG_ID=0x0,Register_IDs_0x9080=0x1,Register_IDs_0x9100=0x2,Register_IDs_0x9180=0x3" offset="0x0.0" size="0x0.8" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="mng_access_reg_cap_mask" descr="Supported management&apos;s access register bitmask. Based on access_reg_group index. \;When bit is set, the register is supported in the device. \;For example:\;Bit 1: MFCR_0x9001\;Bit 2: MFSC_0x9002\;Bit 3: MFSM_0x9003\;Bit 4: MFSL_0x9004\;Bit 58: MGCR_0x903A\;Bit 73: MPPF_0x9049\;Bit 127: MCAP_0x907F" access="RO" enum="MFCR_0x9001=0x2,MFSC_0x9002=0x4,MFSM_0x9003=0x8,MFSL_0x9004=0x10,MGCR_0x903A=0x4000000,MPPF_0x9049=0x200,MCAP_0x907F=0x80000000" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="mng_feature_cap_mask" descr="Supported port&apos;s enhanced features.Based on feature_group index.\;When bit is set, The feature is supported in the device: \;Bit 0: MPCNT counter group- PCIE performance counters supported\;Bit 1: mtpps_fs - If set, field_select field in MTPPS register is supported.\;Bit 2: mtpps_enhanced_out_periodic_adjustment - If set, enhanced_out_periodic_adjustment field in MTPPS register is supported.\;Bit 3: tx_lossy_overflow_oper - If set, tx_overflow_buffer_pkt counter in MPCNT register is supported.\;Bit 4: pcie_outbound_stalled - if set, outbound_stalled_reads, outbound_stalled_writes, outbound_stalled_reads_events and outbound_stalled_writes_events counters in MPCNT are supported.\;Bit 5: Management pass through is supported\;Bit 6: sensor_map - If set, sensor_map is supported in MTCAP register.\;Bit 7: if set, module_status bit 8 (Module Low Power) in MCION register is supported. \;Bit 8: beacon_capability_disable - If set, beacon feature, as appears in MLCR register, in not supported by the device. \;Bit 9: dynamic_tx_overflow - If set, tx_overflow_sense field is supported in MPEGC register. \;Bit 10: mark_tx_action_cqe is supported if set to &apos;1&apos;.\;Bit 11: mark_tx_action_cnp is supported if set to &apos;1&apos;.\;Bit 12: dev_info is supported in  register is set to &apos;1&apos;.\;Bit 13: sensor_count field is 12bit size in MTMP and MTBR\;Bit 14: cs_tokens_supported is supported \;Bit 15: debug_fw_tokens_supported\;Bit 16: long_keys is supported \;Bit 17: pwr_status and pci_power are supported in MPEIN\;Bit 18: If set, accessing through device_type and device_index is supported in MCC, MCQI and MCQS\;Bit 19: pcie_sync_for_fw_update_supported is set to &apos;1&apos;\;Bit 20: ptpCyc2Realtime_modify - If set, the cycle to realtime translation offload is supported\;Bit 21: If set to &apos;1&apos;, reset_state in MFRL is supported\;Bit 22: If set to &apos;1&apos;, link_peer_max_speed is supported in MPEIN Register\;Bit 23: If set to &apos;1&apos;, slot_index field is supported in: MCIA, MCAS, MCION, MQSP, MTCAP, MTECR, MTMP, MTEWE, MTBR, MVCAP, MVCR, MGPIR, MDDT, MDCR.\;Bit 24: If set, transceiver burn flow is supported in MCC, MCQI and MCQS.\;Bit 26: If set, progress field is supported in MCQS\;Bit 28: If set, number_of_slots field is supported in MGPIR.\;Bit 29: If set, virtual hot plug / unplug is supported in MPEGC.\;Bit 30: If set, my_pf_number is supported in MPPF.\;Bit 31: If set, sdee is supported in MTMP\;Bit 34: If set, MCIA supports 32 D-words. Otherwise, 12 D-words.\;Bit 35: If set, MGIR.hw_info.technology is supported. \;Bit 37: If set, lp_msb is supported for MLCR, MPIR \;Bit 39: If set, MRCS and RMDT tokens are supported in MCQS\;Bit 40: If set, &apos;encryption&apos; field in MGIR is supported\;Bit 43: If set, MFCR supports tacho_active_msb field\;Bit 44: If set, FORE supports fan_under_limit_msb and fan_over_limit_msb fields\;Bit 45: If set, MFRL.pci_rescan_required is supported\;Bit 46: time_adjust_range_extended - if set, the MTUTC.time_adjustment range is extended to -\;Bit 47: If set, MTUTC.freq_adj_units=1 is supported\;Bit 48: If set, MRSRFT/MRSR.command=6 is supported\;Bit 49: If set, MCQS.identifier support CRCS and CRDT tokens\;Bit 51: If set, MTUTC.freq_adj_units=2 is supported\; [Internal]: NIC only, FW rejects reset till user committed that traffic is disabled\;Bit 59: If set, MCC.component_specific_error_code is valid for LinkX devices\;Bit 60: If set, MGNLE.clr is supported\;Bit 61: If set, MGIR supports life_cycle_msb and pds fields in FW info and development field in HW info.\; Bit 65: If set, MVCR support current_sensor_value_msb\;Bit 66: If set. MFRL supports pci_reset_req_method, pci_switch_exist fields. [DWIP]\;Bit 67: If set, MRSR.cmd = 6 works with SBR\;Bit 70: If set, supports MTCAP support 8 bit internal_sensor_count [DWIP]\;Bit 71: If set, supports MVCAP supports sensor_map_type [DWIP]\;Bit 75: If set, PLLP supports oe_identifier and resource_labe_port [switch_only][DWIP]\;bit 76: If set, MCQS supports the component_not_supported field [DWIP]\;Bit 77: If set, host_id field in MPIR is supported\;Bit 78: If set, MGIR supports 12 bit num_ports field\;\;bit 80: If set, MCQS,identifier supports the DPA_COMPONENT, DPA _COMPONENT_REMOVAL fields and MCQI supports DPA apps info\;Bit 81: If set, MFCDR supports module and query_type fields [DWIP]\;Bit 82: If set, MCIA supports async mode [DWIP][switch_only]\;Bit 85: If set, MTDT token is supported" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="mcc_reg_ext" descr="" size="0x20.0" >
	<field name="instruction" descr="Command to be executed by the FSM\;0x1: LOCK_UPDATE_HANDLE\;0x2: RELEASE_UPDATE_HANDLE \;0x3: UPDATE_COMPONENT\;0x4: VERIFY_COMPONENT\;0x6: ACTIVATE\;0x7: READ_COMPONENT\;0x8: CANCEL\;0x9: CHECK_UPDATE_HANDLE\;0xA: FORCE_HANDLE_RELEASE\;0xB: READ_PENDING_COMPONENT\;0xC: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved. Applicable for write operation only." access="RW" enum="LOCK_UPDATE_HANDLE=0x1,RELEASE_UPDATE_HANDLE=0x2,UPDATE_COMPONENT=0x3,VERIFY_COMPONENT=0x4,ACTIVATE=0x6,READ_COMPONENT=0x7,CANCEL=0x8,CHECK_UPDATE_HANDLE=0x9,FORCE_HANDLE_RELEASE=0xa,READ_PENDING_COMPONENT=0xb,DOWNSRTEAM_DEVICE_TRANSFER=0xc" offset="0x0.0" size="0x0.8" />
	<field name="activation_delay_sec" descr="This is a configuration that delays the activation of the component in seconds. Relevant only for activate command.\;This configuration is volatile." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="time_elapsed_since_last_cmd" descr="The number of seconds elapsed since the update_handle owner last issued a command. The time saturates at 0xFFF." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="component_index" descr="Index of the accessed component. \;Value from MCQS.component_index\;Valid for \;UPDATE_COMPONENT, ACTIVATE_COMPONENET, READ_COMPONENT and READ_PENDING_COMPONENT instructions. Otherwise, this field is reserved." access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="update_handle" descr="Token representing the current flow executed by the FSM." access="RW" offset="0x8.0" size="0x0.24" />
	<field name="auto_update" descr="Auto-update to all matching downstream devices is requested." access="WO" offset="0x8.31" size="0x0.1" />
	<field name="control_state" descr="Current Update FSM state\;0x0: IDLE\;0x1: LOCKED\;0x2: INITIALIZE\;0x3: DOWNLOAD\;0x4: VERIFY\;0x5: APPLY\;0x6: ACTIVATE\;0x7: UPLOAD\;0x8: UPLOAD_PENDING\;0x9: DOWNSRTEAM_DEVICE_TRANSFER\;Other values are reserved" access="RO" enum="IDLE=0x0,LOCKED=0x1,INITIALIZE=0x2,DOWNLOAD=0x3,VERIFY=0x4,APPLY=0x5,ACTIVATE=0x6,UPLOAD=0x7,UPLOAD_PENDING=0x8,DOWNSRTEAM_DEVICE_TRANSFER=0x9" offset="0xC.0" size="0x0.4" />
	<field name="error_code" descr="Indicates the successful completion of the instruction, or the reason it failed. \;0x0: OK\;0x1: ERROR\;0x2: REJECTED_DIGEST_ERR\;0x3: REJECTED_NOT_APPLICABLE\;0x4: REJECTED_UNKNOWN_KEY\;0x5: REJECTED_AUTH_FAILED\;0x6: REJECTED_UNSIGNED\;0x7: REJECTED_KEY_NOT_APPLICABLE\;0x8: REJECTED_BAD_FORMAT\;0x9: BLOCKED_PENDING_RESET\;0xA: REJECTED_NOT_A_SECURED_FW\;0xB: REJECTED_MFG_BASE_MAC_NOT_LISTED\;0xC: REJECTED_NO_DEBUG_TOKEN\;0xD: REJECTED_VERSION_NUM_MISMATCH\;0xE: REJECTED_USER_TIMESTAMP_MISMATCH\;0xF: REJECTED_FORBIDDEN_VERSION\;0x10: FLASH_ERASE_ERROR\;0x11: REJECTED_REBURN_RUNNING_AND_RETRY\;0x12: REJECTED_LINKX_TYPE_NOT_SUPPORTED\;0x13: REJECTED_HOST_STORAGE_IN_USE\;0x14: REJECTED_LINKX_TRANSFER (see module index in rejected_device_index)\;0x15: REJECTED_LINKX_ACTIVATE (see module index in rejected_device_index)\;0x16: REJECTED_INCOMPATIBLE_FLASH\;0x17: REJECTED_TOKEN_ALREADY_APPLIED\;0x18: REJECTED_FW_BURN_DRAM_NOT_AVAILABLE\;0x19: FW_BURN_REJECTED_INVALID_SECURITY_VERSION\;0x1A: FW_BURN_REJECTED_CERT_CER509 \;0x1B: FW_BURN_REJECTED_CERT_SIGNATURE\;0x1C: FW_BURN_REJECTED_CERT_METADATA\;0x1D: FW_BURN_REJECTED_INTERNAL_ERROR_0 \;0x1E: FW_BURN_REJECTED_NO_PLACE\;0x1F: FW_BURN_REJECTED_REMOVAL_NO_MATCH_CERT_UIDD\;0x20: FW_BURN_REJECTED_INTERNAL_ERROR_1 0x21: FW_BURN_REJECTED_INTERNAL_ERROR_2 0x22: FW_BURN_REJECTED_OF_NUM_OF_SWAP\;0x23: FW_BURN_REJECTED_INTERNAL_ERROR_3 \;0x24: FW_BURN_REJECTED_INTERNAL_ERROR_4 0x25: FW_BURN_REJECTED_NOT_ALLOWED_SAME_CERT_UIDD \;0x26: FW_BURN_REJECTED_INTERNAL_ERROR_5 \;0x27: FW_BURN_REJECTED_INTERNAL_ERROR_6 \;0x28: FW_BURN_REJECTED_FLASH_WRITE_PROTECTED\;0x29: FW_BURN_REJECTED_INTERNAL_ERROR_7 0x2A: FW_BURN_REJECTED_INTERNAL_ERROR_8 0x2B: FW_BURN_REJECTED_INTERNAL_ERROR_90x2C: FW_BURN_REJECTED_DPA_ELF\;0x2D: FW_BURN_REJECTED_DPA_CRYPTO_BLOB\;0x2E: FW_BURN_REJECTED_DPA_APP_METADATA\;0x2F: FW_BURN_REJECTED_DPA_REMOVAL_SIGNATURE\;0x30: FW_BURN_REJECTED_DPA_CONTAINER_VERIFY\;0x31: FW_BURN_REJECTED_INTERNAL_ERROR_10 \;Other values should be treated as an unknown error." access="RO" offset="0xC.8" size="0x0.8" />
	<field name="control_progress" descr="Indicates the estimated progress status of the current operation executed by the FSM. Valid values are 0..100.\;101 indicates that progress reporting is not supported for this update state." access="RO" offset="0xC.16" size="0x0.7" />
	<field name="handle_owner_host_id" descr="For handle_owner_type BMC, command-interface and ICMD, indicates the identifier of the host of the handle owner.\;Otherwise reserved" access="RO" offset="0xC.24" size="0x0.4" />
	<field name="handle_owner_type" descr="Type of entity holding the update handle:\;0x0: unspecified\;0x1: Chassis BMC\;0x2: MAD\;0x3: BMC\;0x4: command interface\;0x5: ICMD \;Other values are reserved." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="component_size" descr="Component size in bytes. \;Valid for UPDATE_COMPONENT instruction. Specifying the size may shorten the update time.\;Value 0x0 means that size is unspecified." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" enum="Switch_or_NIC=0x0,Gearbox=0x1" offset="0x14.0" size="0x0.8" />
	<field name="warning_code" descr="Indicates warnings reported during the completion that did not prevent successful completion of the instruction\;0x0: OK\;0x1: WARNING_DPA_API_OS_INCOMPATIBLE\;0x2: WARNING_DPA_API_FW_INCOMPATIBLE" access="RO" offset="0x14.8" size="0x0.8" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.\;For QM-3 CPO system, device index represents OE or ELS device." access="INDEX" offset="0x14.16" size="0x0.12" />
	<field name="device_index_size" descr="In multiple downstream devices action, the action will be executed starting on device_index and ending on device_index + device_index_size - 1." access="RW" offset="0x18.0" size="0x0.12" />
	<field name="rejected_device_index" descr="The device index that the action has been rejected to." access="RO" offset="0x18.16" size="0x0.12" />
	<field name="component_specific_err_code" descr="[DWIP]:\;Component Specific Error Code\;Relevant only for Linkx failed updates" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mcda_reg_ext" descr="" size="0x90.0" >
	<field name="update_handle" descr="Update handle registered when the FSM was activated." access="RW" offset="0x0.0" size="0x0.24" />
	<field name="offset" descr="Offset of accessed address relative to component start. Accesses must be in accordance to log_mcda_word_size in Table 244, &quot;MCQI CAPABILITIES Info Layout,&quot; on page 254" access="RW" offset="0x4.0" size="0x4.0" />
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

<node name="mcia_ext" descr="" size="0x94.0" >
	<field name="status" descr="Module Status\;0: SUCCESS\;1: NO_EEPROM_MODULE. No response from module&apos;s EEPROM.\;2: MODULE_NOT_SUPPORTED. Module type not supported by the device. 3: MODULE_NOT_CONNECTED. No module present indication. \;4: MODULE_TYPE_INVALID - module is not supported by INI. \;\;9: I2C_ERROR. Error occurred while trying to access the module&apos;s EEPROM using I2C.\;16: MODULE_DISABLED - module is disabled \;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number\;\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pnv" descr="[DWIP]:\;Page Number Valid\;0: write page number\;1: don&apos;t write page number\;Valid only if module is in SW control" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="l" descr="Lock Page bit. \;When bit is set, FW can access the last accessed page.\;After boot and ISSU, default value is 0.\;\;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="device_address" descr="Device address\;\;" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="page_number" descr="Page number\;Reserved when MCIA.l = 1 or when MCIA.pnv = 1\;\;" access="INDEX" offset="0x4.16" size="0x0.8" />
	<field name="i2c_device_address" descr="I2C device address\;" access="INDEX" offset="0x4.24" size="0x0.8" />
	<field name="size" descr="Number of bytes to read/write (up to 128 bytes)" access="INDEX" offset="0x8.0" size="0x0.16" />
	<field name="bank_number" descr="Bank number\;" access="INDEX" offset="0x8.16" size="0x0.8" />
	<field name="bg_mode" descr="[DWIP][switch_only]\;Background operation\;0: Foreground mode (legacy)\;1: Background mode\;\;When working on background mode, FW shall return STS_OK immediately and return the transaction data via MCIA trap." access="OP" offset="0x8.27" size="0x0.1" />
	<field name="passwd_length" descr="0: password length is 4B (password_msb is reserved)\;1: password length is 8B (password_msb is used)" access="OP" offset="0x8.28" size="0x0.1" />
	<field name="password" descr="The password that is written to the module password field.\;This field is reserved when passwd_cap is not set to 1. \;Reserved when module is in SW control." access="OP" offset="0xC.0" size="0x4.0" />
	<field name="dword" descr="Bytes to read/write\;Note: some FW versions support only 12*4B\;See MCAM bit34" access="RW" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
	<field name="password_msb" descr="password msb\;Supported only when MCAM bit34 is set\;Supported only when passwd_cap is set\;Reserved when passwd_length = 0" access="RW" offset="0x90.0" size="0x4.0" />
</node>

<node name="mcion_ext" descr="" size="0x10.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="module" descr="Module number\;\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_status_bits" descr="Module IO status, as defined by SFF and CMIS:\;Bit 0: Present\;Bit 1: RX_LOS\;Bit 2: TX_Fault\;Bit 6: LPMode\;Bit 7: Interrupt (IntL)\;Bit 8: Low Power Mode Status \;Bit 9: Power Good\;If bit 0 (Present) is clear, all other bits are reserved." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="module_inputs" descr="Module inputs: \;Bit 0: ResetL - low polarity\;Bit 1: LPMode\;Bit 2: Power Enable\;Reserved when module is controlled by FW" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="module_status_bits_valid" descr="Module Inputs Valid Bitmask\;Bitmask which mentions the validity of module_inputs fields.\;For each bit, 0 means valid, 1 means not valid.\;For example:\;Bit 0: if set, present bit value is ignored. If cleared, value is valid.\;Bit 1: if set, rx loss value is ignored. when cleared, value is valid and so on for all bits mentioned in module_inputs.\;Reserved when module is controlled by FW" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="mcpp_reg_ext" descr="" size="0x10.0" >
	<field name="enoc" descr="Enable Over Current Events\;Enable power policer according to indication of Over Current which is provided by device interface (e.g. OC_WARN pin in Spectrum)\;0 - disable \;1 - enable (default)" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="ent" descr="Enable Temperature Events\;Enable power policer according to high temperature\;0 - disable (default)\;1 - enable" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="hysteresis_temperature" descr="Below this temperature the Temperature Event is cleared. Units are Celsius\;Default 95\;hysteresis_temperature must be lower or equal to warning_temperature\;Reserved when ent = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="warning_temperature" descr="Above this temperature the Temperature Event is set. Units are Celsius\;Default 105\;Reserved when ent = 0" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="wsoc" descr="Warning State due to Over Current Event:\;0 - Yellow_State\;1 - Red_State (default)" access="RW" offset="0x8.30" size="0x0.1" />
	<field name="wst" descr="Warning State due to Temperature Event:\;0 - Yellow_State (default)\;1 - Red_State" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="yellow_state_rate" descr="Port rate at Yellow_State. Units are percentage from Green_State port rate\;Default 50" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="red_state_rate" descr="Port rate at Red_State. Units are percentage from Green_State port rate\;red_state_rate must be lower or equal to yellow_state_rate\;Default 0" access="RW" offset="0xC.16" size="0x0.8" />
</node>

<node name="mcqi_activation_method_ext" descr="" size="0x7c.0" >
	<field name="all_hosts_sync" descr="When set, the operation needed to move the component form ACTIVE_PENDING_RESET to ACTIVE should happen simultaneously on all hosts." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="auto_activate" descr="This component will be ACTIVE or ACTIVE_PENDING_RESET after the APPLY state." access="RO" offset="0x0.1" size="0x0.1" />
	<field name="pending_fw_reset" descr="This component goes to ACTIVE_PENDING_RESET after activation.\;A FW reset will move it to ACTIVE state." access="RO" offset="0x0.2" size="0x0.1" />
	<field name="pending_server_reboot" descr="This component goes to ACTIVE_PENDING_RESET state after activation.\;A server reset (PCIe PERST#), will move it ACTIVE state." access="RO" offset="0x0.3" size="0x0.1" />
	<field name="pending_server_dc_power_cycle" descr="This component goes to ACTIVE_PENDING_RESET state after activation.\;DC power cycle (power cycle of PCI power rails), will move it ACTIVE state." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="pending_server_ac_power_cycle" descr="This component goes to ACTIVE_PENDING_RESET state after activation.\;AC power cycle (power cycle for both PCI power rails and AUX power), will move it ACTIVE state." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="self_activation" descr="When set, the component supports self activation. For cables, please refer to activation_type in LINKX_PROPERTIES data for more details." access="RO" offset="0x0.6" size="0x0.1" />
</node>

<node name="mcqi_cap_ext" descr="" size="0x7c.0" >
	<field name="supported_info_bitmask" descr="Bitmask indicating which info_type(s) are supported for this component. Set bit indicates the property set is supported\;bit 1: VERSION\;bit 5: ACTIVATION_METHOD\;Other bits are reserved. CAPABILITIES set is always supported.\;bit 6: LinkX\;bit 7: Clock Synchronizer\;\;bit 9: DPA_APPS_INFO\;\;Other bits are reserved" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="component_size" descr="The size of the component given in bytes. Value 0x0 indicates that the size in unknown.\;For some components, size may only be available in the READ_COMPONENT state." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="max_component_size" descr="Maximum size for this component, given in bytes." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="mcda_max_write_size" descr="Maximal write size for MCDA" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="log_mcda_word_size" descr="Log 2 of the access word size in bytes.\;Read and write access must be aligned to the word size. Write access must be done for an integer number of words." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="match_base_guid_mac" descr="The device only accepts updates for this component that explicitly lists its base MAC and/or base GUID" access="RW" offset="0x10.26" size="0x0.1" />
	<field name="check_user_timestamp" descr="A user defined timestamp (MVTS) is active for this component." access="RW" offset="0x10.27" size="0x0.1" />
	<field name="match_psid" descr="PSID is validated for this component update." access="RW" offset="0x10.28" size="0x0.1" />
	<field name="match_chip_id" descr="Chip ID (device_hw_revision) is validated for this component update." access="RW" offset="0x10.29" size="0x0.1" />
	<field name="signed_updates_only" descr="Only signed components are accepted." access="RW" offset="0x10.30" size="0x0.1" />
	<field name="rd_en" descr="When set, this components may be read" access="RO" offset="0x10.31" size="0x0.1" />
</node>

<node name="mcqi_clock_source_properties_ext" descr="" size="0x4.0" >
	<field name="image_version_minor" descr="Image Version Minor Number" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="image_version_major" descr="Image Version Major Number" access="RO" offset="0x0.4" size="0x0.4" />
	<field name="vendor_id" descr="Clock Source Device Vendor Id\;0: Renesas\;1: SiTime 148\;2: SiTime 348\;3: TI\;4-255: Reserved" access="RO" offset="0x0.16" size="0x0.8" />
</node>

<node name="mcqi_dpa_apps_info_ext" descr="" size="0x70.0" >
	<field name="total_number_of_entries" descr="Provides the number of DPA apps in the active DPA_APPS partition.\;If there are no DPA apps, this field is equal to 0 and all the DPA_APP_METADATA fields will be 0." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="DPA_APPS_INFO version." access="RO" offset="0x0.24" size="0x0.8" />
	<field name="dpa_app_metadata" descr="DPA metadata, see Table 258, &quot;MCQI DPA_APP_METADATA Layout,&quot; on page 263" subnode="mcqi_dpa_metadata_ext" access="RO" offset="0x8.0" size="0x68.0" />
</node>

<node name="mcqi_dpa_metadata_ext" descr="" size="0x68.0" >
	<field name="subtype" descr="The subtype of the section" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="type" descr="The type of the section. Should be used to identify &quot;twin&quot; applications, e.g. - CCProg coming from a 3rd party versus &quot;native&quot; application. \;Enumeration details:\;0 - APU_APP_EXTERNAL,\;1 - 3 - Reserved,\;4 - APU_APP_PCC,\;5 - APU_APP_DLL,\;6 - APU_APP_KERNEL,\;7-255 - Reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="version" descr="Version of App Metadata structure" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="length" descr="Structure length" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="dpa_app_version" descr="DPA application version" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="dpa_os_api_version" descr="Version of the DPA API to OS" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="dpa_fw_api_version" descr="Version of the DPA API to other DPA FW modules" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="dpa_app_uuid" descr="DPA application UUID, updated with a change in application version" access="RO" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
	<field name="dpa_app_description_string" descr="Application description ASCII string" access="RO" high_bound="7" low_bound="0" offset="0x40.0" size="0x20.0" />
</node>

<node name="mcqi_linkx_properties_ext" descr="" size="0x7c.0" >
	<field name="fw_image_status_bitmap" descr="Bit 0: Image A is running\;Bit 1: Image A is committed, module boots from image A\;Bit 2: Image A is erased / empty\;Bit 3: Reserved\;Bit 4: Image B is running\;Bit 5: Image B is committed, module boots from image B\;Bit 6: Image B is erased / empty\;Bit 7: Reserved" access="RO" offset="0x0.0" size="0x0.8" />
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
	<field name="management_interface_protocol" descr="0: Does not support either one of the FW update procedures defined below\;1: SFF-8636 management interface and pseudo-CMIS FW. Update is supported\;2: CMIS 4.0 is implemented" access="RO" offset="0x1C.0" size="0x0.6" />
	<field name="activation_type" descr="0: HW reset is required. Host should be prepared to power cycle a cable after sending a RunFWImage command.\;1: Self-activation with HW reset contained in the RunFWImage command. No additional actions required from the host.\;2:Self-activation with hitless reset contained in the RunFWImage command. No additional actions required from the host.\;3-15: Reserved" access="RO" offset="0x1C.10" size="0x0.4" />
	<field name="vendor_sn" descr="Vendor Serial Number" access="RO" offset="0x20.0" size="0x0.16" />
</node>

<node name="mcqi_reg_data_auto_ext" descr="" attr_is_union="1" size="0x7c.0" >
	<field name="mcqi_activation_method_ext" descr="" subnode="mcqi_activation_method_ext" offset="0x0.0" selected_by="ACTIVATION_METHOD" size="0x7c.0" />
	<field name="mcqi_cap_ext" descr="" subnode="mcqi_cap_ext" offset="0x0.0" selected_by="CAPABILITIES" size="0x7c.0" />
	<field name="mcqi_clock_source_properties_ext" descr="" subnode="mcqi_clock_source_properties_ext" offset="0x0.0" selected_by="CLOCK_SOURCE_PROPERTIES" size="0x4.0" />
	<field name="mcqi_dpa_apps_info_ext" descr="" subnode="mcqi_dpa_apps_info_ext" offset="0x0.0" selected_by="DPA_APPS_INFO" size="0x70.0" />
	<field name="mcqi_linkx_properties_ext" descr="" subnode="mcqi_linkx_properties_ext" offset="0x0.0" selected_by="LINKX_PROPERTIES" size="0x7c.0" />
	<field name="mcqi_version_ext" descr="" subnode="mcqi_version_ext" offset="0x0.0" selected_by="VERSION" size="0x7c.0" />
</node>

<node name="mcqi_reg_ext" descr="" size="0x94.0" >
	<field name="component_index" descr="Component index gathered by &quot;MCQS - Management Component Query Status&quot;" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.\;\;For Clock Source EEPROM, the index represents the Clock Source Index, starting from 1\;\;For DPA_APPS_INFO, the index represents the index of the DPA app to query, starting from 0" access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="read_pending_component" descr="When set, the register will return information about the pending component (if available)" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch / NIC\;1: Gearbox" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="info_type" descr="Component properties set.\;0x0: CAPABILITIES\;0x1: VERSION\;0x5: ACTIVATION_METHOD\;0x6: LINKX_PROPERTIES\;0x7: CLOCK_SOURCE_PROPERTIES\;\;0x9: DPA_APPS_INFO\;Other values are reserved" access="RW" enum="CAPABILITIES=0x0,VERSION=0x1,ACTIVATION_METHOD=0x5,LINKX_PROPERTIES=0x6,CLOCK_SOURCE_PROPERTIES=0x7,DPA_APPS_INFO=0x9" offset="0x8.0" size="0x0.5" />
	<field name="info_size" descr="Properties set structure size, given in bytes." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="offset" descr="The requested/returned data offset from the section start, given in bytes.\;Must be DWORD aligned.\;If offset is invalid, FW will return an error." access="RW" offset="0x10.0" size="0x4.0" />
	<field name="data_size" descr="The requested/returned data size, given in bytes.\;If data_size is not DWORD aligned, the last bytes are zero padded.\;If size is invalid, FW will return an error." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="data" descr="Properties set structure according to info_type.\;CAPABILITIES - See Table 244, &quot;MCQI CAPABILITIES Info Layout,&quot; on page 254\;VERSION - See Table 246, &quot;MCQI VERSION Info Layout,&quot; on page 256\;ACTIVATION_METHOD - See Table 250, &quot;MCQI ACTIVATION_METHOD Info Layout,&quot; on page 258\;LINKX_PROPERTIES - See Table 252, &quot;MCQI LINKX_PROPERTIES Info Layout,&quot; on page 259\;CLOCK_SOURCE_PROPERTIES - See Table 254, &quot;MCQI CLOCK_SOURCE_PROPERTIES Layout,&quot; on page 261\;DPA_APPS_INFO - See Table 256, &quot;MCQI DPA_APPS_INFO Layout,&quot; on page 262" subnode="mcqi_reg_data_auto_ext" access="RO" offset="0x18.0" size="0x7c.0" union_selector="$(parent).info_type" />
</node>

<node name="mcqi_version_ext" descr="" size="0x7c.0" >
	<field name="version_string_length" descr="" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="user_defined_time_valid" descr="When set, the component has a valid user-defined version time-stamp in user_defined_time" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="build_time_valid" descr="When set, the component has a valid creation time-stamp in build_time" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="version" descr="Version number" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="build_time" descr="Time of component creation. Valid only if build_time_valid is set. See Table 248, &quot;Date-Time Layout,&quot; on page 257" subnode="date_time_layout_ext" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="user_defined_time" descr="User-defined time assigned to the component version. Valid only if user_defined_time_valid is set. See Table 248, &quot;Date-Time Layout,&quot; on page 257" subnode="date_time_layout_ext" access="RW" offset="0x10.0" size="0x8.0" />
	<field name="build_tool_version" descr="Build tool version number.\;Valid only when not equal to 0" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="version_string" descr="NULL terminated string representing the version." access="RW" high_bound="91" low_bound="0" offset="0x20.24" size="0x5c.0" />
</node>

<node name="mcqs_reg_ext" descr="" size="0x10.0" >
	<field name="component_index" descr="Component Index. Values range from 0 to the last component indicated by last_index_flag." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die. \;For cables, the index represents the module index starting at index 1. Index 0 indicates the host device.\;For Clock synchronizer, index is used to represent the clock sync&apos; device index. Starting from 1." access="INDEX" offset="0x0.16" size="0x0.12" />
	<field name="component_not_supported" descr="When set, this component not supported." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="last_index_flag" descr="When set, this component is the last component (highest component_index)." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="identifier" descr="This field uniquely identifies a specific component type. \;0x1: BOOT_IMG\;0x4: OEM_NVCONFIG\;0x5: MLNX_NVCONFIG\;0x6: CS_TOKEN\;0x7: DBG_TOKEN\;0xA: Gearbox\;0xB: CC_ALGO - Congestion Control Algorithm\;0xC: LINKX_IMG\;0xD: CRYPTO_TO_COMMISSIONING\;0xE: RMCS_TOKEN\;0xF: RMDT_TOKEN\;0x10: CRCS_TOKEN \;0x11: CRDT_TOKEN \;0x12: CLOCK_SYNC_EEPROM  \;0x15: DIGITAL_CACERT - Certificate to be trusted by the device0x17: DIGITAL_CACERT_REMOVAL\;\;MTDT_TOKENOther values are reserved\;[DWIP]: 0x1A: LINKX_FW_ELS\;\;0x1C: DPA_COMPONENT\;0x1D: DPA_COMPONENT_REMOVAL\;\;0x1E: MTDT_TOKEN" access="RO" enum="BOOT_IMG=0x1,OEM_NVCONFIG=0x4,MLNX_NVCONFIG=0x5,CS_TOKEN=0x6,DBG_TOKEN=0x7,Gearbox=0xa,CC_ALGO=0xb,LINKX_IMG=0xc,CRYPTO_TO_COMMISSIONING=0xd,RMCS_TOKEN=0xe,RMDT_TOKEN=0xf,CRCS_TOKEN=0x10,CRDT_TOKEN=0x11,CLOCK_SYNC_EEPROM=0x12,DIGITAL_CACERT=0x15,DPA_COMPONENT=0x1c,DPA_COMPONENT_REMOVAL=0x1d,MTDT_TOKEN=0x1e" offset="0x4.0" size="0x0.16" />
	<field name="component_update_state" descr="Component state in update flow\;0x0: IDLE\;0x1: IN_PROGRESS\;0x2: APPLIED\;0x3: ACTIVE \;0x4: ACTIVE_PENDING_RESET\;0x5: FAILED\;0x6: CANCELED\;0x7: BUSY\;\;Other values are reserved" access="RO" enum="IDLE=0x0,IN_PROGRESS=0x1,APPLIED=0x2,ACTIVE=0x3,ACTIVE_PENDING_RESET=0x4,FAILED=0x5,CANCELED=0x6,BUSY=0x7" offset="0x8.0" size="0x0.4" />
	<field name="component_status" descr="The status of the component:\;0x0: NOT_PRESENT - The component is supported by the device but, currently not present\;0x1: PRESENT - This component is present. For downstream devices link LinkX component, this is an indication that the binary image is present at the host device memory.\;0x2: IN_USE - The component is present and currently in use." access="RO" enum="NOT_PRESENT=0x0,PRESENT=0x1,IN_USE=0x2" offset="0x8.4" size="0x0.5" />
	<field name="progress" descr="Progress in percentage (from 0 to 100). This field is only relevant for cables." access="RO" offset="0x8.9" size="0x0.7" />
	<field name="device_type" descr="Peripheral device type:\;0: Switch_or_NIC\;1: Gearbox" access="INDEX" offset="0xC.0" size="0x0.8" />
	<field name="last_update_state_changer_host_id" descr="For last_update_state_changer_type BMC, command-interface and ICMD, indicates the identifier of the host of the handle owner. Otherwise reserved." access="RO" offset="0xC.24" size="0x0.4" />
	<field name="last_update_state_changer_type" descr="Indicates which entity was the last to change the component_update_state of this component.\;0x0: unspecified\;0x1: Chassis_BMC\;0x2: MAD\;0x3: BMC\;0x4: command_interface\;0x5: ICMD\;\;Other values are reserved" access="RO" enum="unspecified=0x0,Chassis_BMC=0x1,MAD=0x2,BMC=0x3,command_interface=0x4,ICMD=0x5" offset="0xC.28" size="0x0.4" />
</node>

<node name="mdcr_ext" descr="" size="0x60.0" >
	<field name="device_type" descr="Peripheral device type\;1: XM" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="device_status_data" descr="Device initialization Data. \;For XM status, see Table 459, &quot;MDCR - XM Data Layout,&quot; on page 394" subnode="mdcr_xm_data_ext" access="RO" offset="0x10.0" size="0x50.0" />
</node>

<node name="mdcr_xm_data_ext" descr="" size="0x50.0" >
	<field name="xm_status" descr="XM load status.\;0: Pending\;1: No connection (At least 1 of the two Ethernet ports is not up)\;2: Version mismatch (major and minor are different from major_expected and minor_expected)\;3: Loaded successfully" access="RO" offset="0x0.20" size="0x0.4" />
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
	<field name="device_enable" descr="When set, FW is the manager and allowed to program the Downstream Device." access="RW" offset="0x4.28" size="0x0.1" />
	<field name="rst" descr="Reset request\;0: No reset\;1: Soft Reset\;2-7: Reserved" access="OP" offset="0x4.29" size="0x0.3" />
</node>

<node name="mddq_data_auto_ext" descr="" attr_is_union="1" size="0x20.0" >
	<field name="mddq_device_info_ext" descr="" subnode="mddq_device_info_ext" offset="0x0.0" selected_by="device_info" size="0x20.0" />
	<field name="mddq_slot_info_ext" descr="" subnode="mddq_slot_info_ext" offset="0x0.0" selected_by="slot_info" size="0x20.0" />
	<field name="mddq_slot_name_ext" descr="" subnode="mddq_slot_name_ext" offset="0x0.0" selected_by="slot_name" size="0x20.0" />
</node>

<node name="mddq_device_info_ext" descr="" size="0x20.0" >
	<field name="device_index" descr="Device index\;The first device should number 0" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="flash_id" descr="The flash ID that the device is using." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="lc_pwr_on" descr="If set to &apos;1&apos;, the fields related to the device are valid since the line-card is powered on and plugged and matching the INI version. \;Note: this bit is not an indication to validity of the fields related to the specific FW capabilities and version." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="thermal_sd" descr="Thermal Shutdown. If set, the device was shut down due to thermal event." access="RO" offset="0x0.29" size="0x0.1" />
	<field name="flash_owner" descr="If set to &apos;1&apos;, the device is the flash owner. Otherwise, a shared flash is used by this device (another device is the flash owner)." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="uses_flash" descr="If set, the device uses a flash" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="device_type" descr="0: Amos Gearbox\;1: Abir Gearbox" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fw_major" descr="Major FW version number. Valid only after the FW is burnt. Otherwise, the value should be &apos;0&apos;." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="fw_sub_minor" descr="Sub-minor FW version number. Valid only after the FW is burnt. Otherwise, the value should be &apos;0&apos;." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fw_minor" descr="Minor FW version number. Valid only after the FW is burnt. Otherwise, the value should be &apos;0&apos;." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="max_cmd_write_size_supp" descr="Maximum write size (in D-Words) that the device supports for its PRM commands." access="RO" offset="0xC.0" size="0x0.8" />
	<field name="max_cmd_read_size_supp" descr="Maximum read size (in D-Words) that the device supports for its PRM commands." access="RO" offset="0xC.8" size="0x0.8" />
	<field name="device_type_name" descr="Device type ASCII name. Up to 8 chars\;" access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
</node>

<node name="mddq_ext" descr="" size="0x30.0" >
	<field name="slot_index" descr="Slot index\;0: Reserved" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="query_type" descr="0: Reserved\;1: slot_info\;2: device_info - for a device on the slot. If there are no devices on the slot, data_valid will be &apos;0&apos;.\;3: slot_name - Name of the slot (string)" access="INDEX" enum="Reserved=0x0,slot_info=0x1,device_info=0x2,slot_name=0x3" offset="0x0.16" size="0x0.8" />
	<field name="sie" descr="Slot info event enable\;When set to &apos;1&apos;, each change in the MDDQ.slot_info.provisioned / sr_valid / active / ready will generate an DSDSC event." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="request_message_sequence" descr="Request message sequential number. \;The first message number should be 0" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="response_message_sequence" descr="Response message sequential number. \;For a specific request, the response message sequential number is the following one. \;In addition, the last message should be 0." access="RO" offset="0x4.16" size="0x0.8" />
	<field name="query_index" descr="Index related to the specific query_type. \;For query_type = 1,2,3 this field is neglected." access="INDEX" offset="0x8.0" size="0x0.8" />
	<field name="data_valid" descr="If set, the data in the data field is valid and contain the information for the queried index. \;Note: This field is not reflecting any validity of the data while accessing a non-existing query entity. Querying with an out of range index will lead to BAD_PARAM status of the register." access="RO" offset="0x8.31" size="0x0.1" />
	<field name="data" descr="Properties of that field are based on query_type.\;For slot information query_type data - see Table 155, &quot;MDDQ slot_info Layout,&quot; on page 180\;For devices on slot query_type data - see Table 157, &quot;MDDQ device_info Register Layout,&quot; on page 181\;For slot name query_type data - see Table 159, &quot;MDDQ slot_name Layout,&quot; on page 183" subnode="mddq_data_auto_ext" access="RO" offset="0x10.0" size="0x20.0" union_selector="$(parent).query_type" />
</node>

<node name="mddq_slot_info_ext" descr="" size="0x20.0" >
	<field name="active" descr="If set, the FW has completed the MDDC.device_enable command" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="lc_ready" descr="If set, the LC is powered on, matching the INI version and a new FW version can be burnt (if necessary)\;0: Not ready\;1: Ready\;2: Error\;3: Reserved" access="RO" offset="0x0.28" size="0x0.2" />
	<field name="sr_valid" descr="If set, Shift Register is valid (after being provisioned) and data can be sent from the switch ASIC to the line-card CPLD over Shift-Register." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="provisioned" descr="If set, the INI file is ready and the card is provisioned" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="ini_file_version" descr="User-configured version number of the current INI file.\;Valid only when active or lc_ready are &apos;1&apos;." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="hw_revision" descr="HW revision of the line-card as it appears in the current INI file.\;Valid only when active or lc_ready are &apos;1&apos;." access="RO" offset="0x4.16" size="0x0.16" />
	<field name="card_type" descr="Card type\;0x00: Buffalo 4x400G\;0x01: Buffalo 8x200G\;0x02: Buffalo 16x100G\;" access="RO" offset="0x8.0" size="0x0.8" />
</node>

<node name="mddq_slot_name_ext" descr="" size="0x20.0" >
	<field name="slot_ascii_name" descr="Slot&apos;s ASCII name. Up to 20 chars\;" access="RO" high_bound="19" low_bound="0" offset="0x0.24" size="0x14.0" />
</node>

<node name="mddt_reg_ext" descr="" size="0x110.0" >
	<field name="device_index" descr="Device index" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="type" descr="0: PRM_Register\;1: Command\;2: CrSpace_access" access="OP" enum="PRM_Register=0x0,Command=0x1,CrSpace_access=0x2" offset="0x4.0" size="0x0.2" />
	<field name="write_size" descr="Write size in D-Words." access="OP" offset="0x4.16" size="0x0.8" />
	<field name="read_size" descr="Read size in D-Words." access="OP" offset="0x4.24" size="0x0.8" />
	<field name="payload" descr="Payload\;For PRM Register type payload - See Table 147, &quot;PRM Register Payload Layout,&quot; on page 176\;For Command type payload - See Table 149, &quot;Command Payload Layout,&quot; on page 176\;For CrSpace type payload - See Table 151, &quot;CrSpace access Payload Layout,&quot; on page 177" subnode="mddt_reg_payload_auto_ext" access="RW" offset="0xC.0" size="0x104.0" union_selector="$(parent).type" />
</node>

<node name="mddt_reg_payload_auto_ext" descr="" attr_is_union="1" size="0x104.0" >
	<field name="command_payload_ext" descr="" subnode="command_payload_ext" offset="0x0.0" selected_by="Command" size="0x104.0" />
	<field name="crspace_access_payload_ext" descr="" subnode="crspace_access_payload_ext" offset="0x0.0" selected_by="CrSpace_access" size="0x104.0" />
	<field name="prm_register_payload_ext" descr="" subnode="prm_register_payload_ext" offset="0x0.0" selected_by="PRM_Register" size="0x104.0" />
</node>

<node name="mdfcr_reg_ext" descr="" size="0x60.0" >
	<field name="device_type" descr="Peripheral device type\;1: Vega_Gearbox\;2: Tile" access="INDEX" enum="Vega_Gearbox=0x1,Tile=0x2" offset="0x0.0" size="0x0.8" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="all" descr="All devices are selected and device_index is ignored\;When set to &apos;1&apos;, the fw_status should represent the worst case of any of the devices. fw_version, build_id, major and minor should be of device number 0." access="INDEX" offset="0x4.31" size="0x0.1" />
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

<node name="mdps_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_index" descr="The sensor to stress. Each sensor description can be queried via MVCR" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="supported" descr="Returns true if the sensor supports the stressor" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="stressor_type" descr="0: Under voltage - allowed only with debug token\;1: Over voltage\;2: Voltage loss - allowed only with debug token" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="stressors_params" descr="Layout is according to stressor_type value:\;For over voltage seeTable 347, &quot;Over Voltage Stressor Parameters Layout,&quot; on page 326\;For under voltage seeTable 349, &quot;Under Voltage Stressor Parameters Layout,&quot; on page 327\;" subnode="mdps_reg_stressors_params_auto_ext" access="RW" offset="0x8.0" size="0x8.0" />
</node>

<node name="mdps_reg_stressors_params_auto_ext" descr="" attr_is_union="1" size="0x8.0" >
	<field name="over_voltage_stressor_parameters_ext" descr="" subnode="over_voltage_stressor_parameters_ext" offset="0x0.0" size="0x8.0" />
	<field name="under_voltage_stressor_parameters_ext" descr="" subnode="under_voltage_stressor_parameters_ext" offset="0x0.0" size="0x4.0" />
</node>

<node name="mdrcr_ext" descr="" size="0x30.0" >
	<field name="device_type" descr="Peripheral device type\;1: Gearbox\;" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="device_index" descr="Device number \;For gearboxes, the index represents the gearbox die." access="INDEX" offset="0x4.0" size="0x0.12" />
	<field name="all" descr="All devices are selected and device_index is ignored\;When set to &apos;1&apos;, the rst_status should represent the worst case of any of the devices." access="INDEX" offset="0x4.31" size="0x0.1" />
	<field name="rst_op" descr="Reset Operation.\;0: Query of the reset status which is displayed through rst_status.\;1: Full Reset of the selected device(s).\;2-8: Reserved." access="RW" offset="0xC.0" size="0x0.3" />
	<field name="rst_status" descr="Reset status.\;0: Reset completed successfully. 1: Reset operation has not finished yet." access="RO" offset="0xC.16" size="0x0.4" />
</node>

<node name="mdri_ext" descr="" size="0x120.0" >
	<field name="clear" descr="Per bit:\;Bit 0: clear global_reasons\;Bit 1: clear port_reasons\;Bit 2: clear buffer_reasons\;Bit 3: clear ethernet_reasons\;Bit 4: clear ip_reasons\;Bit 5: clear mpls_reasons\;Bit 6: clear tunnel_reasons\;Bit 7: clear host_reasons" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="read" descr="Per bit:\;Bit 0: read global_reasons\;Bit 1: read port_reasons\;Bit 2: read buffer_reasons\;Bit 3: read ethernet_reasons\;Bit 4: read ip_reasons\;Bit 5: read mpls_reasons\;Bit 6: read tunnel_reasons\;Bit 7: read host_reasons" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="global_reasons" descr="Bit0: TCAM ECC Error (had a correctable ECC error)\;Bit1: no egress port (e.g. MC group is empty, port-isolation)\;\;Bit3: MAFCR.counter_accu_overflow was incremented (this is not a discard, but it&apos;s a bad behavior)," access="RO" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="port_reasons" descr="Bit0: receive buffer overflow\;\;Bit1: egress mtu error" access="RO" high_bound="7" low_bound="0" offset="0x40.0" size="0x20.0" />
	<field name="buffer_reasons" descr="Bit0: sll" access="RO" high_bound="7" low_bound="0" offset="0x60.0" size="0x20.0" />
	<field name="ethernet_reasons" descr="Bit0: smac is mc\;Bit1: smac equal dmac\;Bit2: invalid ethertype (0x05DC &lt; ethertype &lt; 0x600)Bit3: ingress spanning tree\;Bit4: fdb_miss, same as trap_id FDB_MISS\;Bit5: fdb_mismatch, same as trap_id FDB_MISMATCH\;Bit6: fid miss, same as trap_id FID_MISS" access="RO" high_bound="7" low_bound="0" offset="0x80.0" size="0x20.0" />
	<field name="ip_reasons" descr="Bit0: packet to router is not ip/mpls/arp (no ip header)\;Bit1: disabled irif \;Bit2: uc dip over mc or bc mac\;Bit3: dip is loopback address \;for ipv6: (dip==::1/128) || (dip==0:0:0:0:0:ffff:7f00:0/104)\;for ipv4: dip==127.0.0.0/8\;Bit4: sip is mc \;for ipv6: (SIP == FF00::/8)\;for ipv4: (SIP == 224.0.0.0: 239.255.255.255 aka 224.0.0.0/4)\;Bit5: sip is in class e\;(pkt is ipv4) &amp;&amp; (sip == 240.0.0.0/4) &amp;&amp; (sip != 255.255.255.255)\;Bit6: sip is loopback\;for ipv6: sip == ::1/128\;for ipv4: sip == 127.0.0.0/8\;Bit7: sip is unspecified\;for ipv6: sip == ::0\;for ipv4: sip == 0.0.0.0/32\;Bit8: ip header not okay (IPVer, checksum, IHL)Bit9: mc mac mismatch\;\;Bit10: sip equal dip\;Bit11: ipv4 sip is limited broadcast\;Bit12: lpm no route uc ipv4\;Bit13: lpm no route uc ipv6\;Bit14: uc dip is link local, same as trap_id&apos;s DISCARD_ING_ROUTER_DIP_LINK_LOCAL, IPV6_LINK_LOCAL_DEST\;Bit15: sip is link local, same as trap_id&apos;s DISCARD_ING_ROUTER_SIP_LINK_LOCAL, IPV6_LINK_LOCAL_SRC\;Bit16: mc egress mtu aggregated\;Bit17: mc RPF \;Bit18: uc RPF Bit20: IPv4 dip is limited broadcast (dip==bc)\;Bit21: IPv4 dip is local network (dip == 0.0.0.0/8)\;Bit22: NVE packet to overlay router \;\;Bit23: mc dip over uc mac\;Bit24: mc dip is link local, same as trap_id: LOCALNETWORK, IPV6_MC_LINK_LOCALDEST\;Bit25: ingress MTU (this check is configured as forward)\;Bit26: mc egress mtu, (both for UC and for MC, MPLS)\;Bit29: ttl_error, same as trap_id TTLERROR\;Bit30: disabled erif \;\;Bit31: host miss ipv4, same as trap_id HOST_MISS_IPV4\;Bit32: host miss ipv6, same as trap_id HOST_MISS_IPV6\;Bit33: loopback error, same as trap_id LBERROR\;Bit34: ipv6 dip is unspecified, dip==::0/128, same as trap_id" access="RO" high_bound="7" low_bound="0" offset="0xA0.0" size="0x20.0" />
	<field name="mpls_reasons" descr="Bit0: outer label is not valid\;\;Bit1: no IP after decap (or after php)\;\;Bit3: mpls uc Ethertype (0x8847) over mc or bc mac\;Bit4: mpls mc Ethertype over not allowed mac\;Bit5: MPLS min ingress label allowed (label too low)\;Bit6: MPLS max ingress label allowed (label too high)\;Bit7: ReservedBit8: php decap and no ip header or ip header is not okay\;\;Bit9: ilm miss, same as trap_id MPLS_ILM_MISS\;Bit10: mpls loopback filter" access="RO" high_bound="7" low_bound="0" offset="0xC0.0" size="0x20.0" />
	<field name="tunnel_reasons" descr="Bit0: decap_encap_prevention - same as trap_id DECAP_ENCAP\;Bit1: ipip_tunnel_loop \;\;Bit2: reserved\;\;Bit3: ipip_decap_error - same as trap_id IPIP_DECAP_ERROR\;Bit4: ipip_error - same as trap_id IPIP_ERROR. For Spectrum-2 catches nothing \;Bit7: nve_decap_frag_error - same as trap_id NVE_DECAP_FRAG_ERROR\;Bit8: overlay_port_isolation - see TNIFR\;\;Bit10: overlay_smac_is_mc\;Bit11: overlay_smac_equal_dmac\;Bit12: overlay_is_too_short - (decap remains with short packet) - also catches VLAN removal. Only for Spectrum-1/2/3. \;Bit13: decap_underlay_is_too_long - (decap of more than 126 bytes)\;\;Bit14: nve_decap_error - same as trap_id NVE_DECAP _TAG_ERROR\;Bit15: decap_ecn - same as trap_id DECAP_ECN0, DECAP_ECN1\;" access="RO" high_bound="7" low_bound="0" offset="0xE0.0" size="0x20.0" />
	<field name="host_reasons" descr="Bit0: tx_base_header_is_wrong - (version or base type)\;Bit1: tx_base_header_system_port_is_out_of_range" access="RO" high_bound="7" low_bound="0" offset="0x100.0" size="0x20.0" />
</node>

<node name="mdsr_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0: The debug session ended successfully\;1: Failed to execute the operation. See additional_info for more details.\;2: Debug session active. See type_of_token for more details.\;3: No token applied\;4: Challenge provided, no token installed yet, see type_of_token for details.\;5: Timeout before token installed, see type_of_token for details\;6: Timeout of active token.\;7-15: Reserved\;\;Note: Status might be &apos;0&apos; even when debug query is not allowed and additional_info field will expose the reason." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="additional_info" descr="0: No additional information available \;1: There is no debug session in progress\;2: FW is not secured, debug session cannot be ended\;3: Fail - Debug end request cannot be accepted. \;4: Fail - Host is not allowed to query debug session\;5: Debug session active" access="RO" offset="0x0.8" size="0x0.6" />
	<field name="type_of_token" descr="0: CS token \;1: Debug FW token \;2: FRC token \;3: RMCS token\;4: RMDT token \;5: CRCS token \;6: CRDT token\;" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="end" descr="Set to &apos;1&apos; to end debug session.\;Setting to &apos;0&apos; will not trigger any operation." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="time_left" descr="Time left in seconds.\;In case that status is 2 (debug session active) - time left for token operation\;In case that status is 4 (challenge provided, no token installed yet) - time left for token installation\;For any other status, field should be zero" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mdtr_reg_event_params_auto_ext" descr="" attr_is_union="1" size="0xa0.0" >
	<field name="cvb_config_error_ext" descr="" subnode="cvb_config_error_ext" offset="0x0.0" selected_by="cvb_config_error" size="0xa0.0" />
</node>

<node name="mdtr_reg_ext" descr="" size="0xb0.0" >
	<field name="event_id" descr="1: cvb_config_error" access="RO" enum="cvb_config_error=0x1" offset="0x0.0" size="0x0.16" />
	<field name="severity" descr="Severity:\;2: FATL - (fatal) Unrecoverable switch behavior\;3: NRML - (normal) Unexpected state with possible systemic Failure\;5: INTR - (debug) Unexpected state without systemic Failure" access="RO" enum="FATL=0x2,NRML=0x3,INTR=0x5" offset="0x0.16" size="0x0.8" />
	<field name="irisc_id" descr="Which RISC triggered the event" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="tile_v" descr="Tile valid:\;0: The error was from main\;1: The error was from a tile" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the error." access="RO" offset="0x8.0" size="0x0.4" />
	<field name="event_params" descr="event parameters - layout is according to event_id value:\;See Table 343, &quot;Event_params cvb_config_error Layout,&quot; on page 325" subnode="mdtr_reg_event_params_auto_ext" access="RW" offset="0x10.0" size="0xa0.0" union_selector="$(parent).event_id" />
</node>

<node name="meccc_ext" descr="" size="0x14.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="device_index" descr="Device index\;For gearboxes, the index represents the gearbox die" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clr" descr="Clear counters\;" access="OP" offset="0x4.0" size="0x0.1" />
	<field name="ecc_crt_cnt" descr="ECC Correctable Counter\;Counter increments 1 time per each SRAM (including TCAM) which had 1 or more ECC correctable events. \;Cleared at: (1) reset (including soft_reset), (2) clear bit\;Counts from: (1) main, (2) all tiles" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ecc_ucrt_cnt" descr="ECC Uncorrectable Counter\;Cleared at: (1) reset (including soft_reset), (2) clear bit\;" access="RO" offset="0x10.0" size="0x0.8" />
</node>

<node name="merr_ext" descr="" size="0x14.0" >
	<field name="ent_type" descr="Entity type.\;0: Reserved\;1: QSFP Module (the relevant signals are: present, reset, interrupt, power enable, low power mode, power good, modsel, QSFP LEDs)" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="current_index" descr="Current entity index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="target_index" descr="Entity number to be mapped to." access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="mfba_reg_ext" descr="" size="0x10c.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="size" descr="The size of the data to be written or read in bytes\;Should comply with block_size and block_alignment fields in MFPA." access="OP" offset="0x4.0" size="0x0.9" />
	<field name="address" descr="The start address of this read or write access in bytes. Should comply with block_size and block_alignment fields in MFPA." access="INDEX" offset="0x8.0" size="0x4.0" />
	<field name="data" descr="The data to be written or read data." access="RW" high_bound="63" low_bound="0" offset="0xC.0" size="0x100.0" />
</node>

<node name="mfbd_ext" descr="" size="0x24.0" >
	<field name="time_res" descr="Time Resolution\;0: time units are in microseconds \;1: time units are in milliseconds" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="fw_init_total_time" descr="FW init time." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="fw_init_open_ports_time" descr="FW init time to open all ports." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="boot_time" descr="boot and bootrom time" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="init_tiles_time" descr="Tiles boot time" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="init_phy_power_time" descr="Phy power time" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="init_usr_algo_time" descr="User Algo&apos; time" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="init_gearbox_time" descr="Time of init Gearbox" access="RO" offset="0x20.0" size="0x4.0" />
</node>

<node name="mfbe_reg_ext" descr="" size="0xc.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device. \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="bulk_64kb_erase" descr="Erase a 64KB flash area in one bulk operation." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="bulk_32kb_erase" descr="Erase a 32KB flash area in one bulk operation." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="address" descr="The start address (in bytes) of this erase operation. Must be aligned with the selected erase size (sector, 32KB or 64KB)." access="INDEX" offset="0x8.0" size="0x4.0" />
</node>

<node name="mfcdr_reg_ext" descr="" size="0x8.0" >
	<field name="module" descr="Module number\;Valid when query_type = 1, else this field is ignored" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port MSB\;Valid when query_type = 0, else this field is ignored" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port\;Valid when query_type = 0, else this field is ignored" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="query_type" descr="Selector of query type\;0: local_port based query\;1: module based query" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="status" descr="0: N/A \;1: Fake cable detected\;2: NVIDIA Cable detected\;3: Reserved" access="RO" offset="0x4.0" size="0x0.2" />
</node>

<node name="mfcr_ext" descr="" size="0x8.0" >
	<field name="pwm_frequency" descr="Controls the frequency of the PWM signal.\;Supported frequencies are:\;0x0: 11Hz \;0x1: 14.7Hz\;0x2: 22.1Hz\;0x3 - 0111111: Reserved\;0x40: 1.4KHz\;0x41: 5KHz\;0x42: 20KHz\;0x43: 22.5KHz\;0x44: 25KHz\;0x45 - 0x7F: Reserved" access="RW" offset="0x0.0" size="0x0.7" />
	<field name="pwm_active" descr="Indicates which of the PWM control is active (bit per PWM)" access="RO" offset="0x4.0" size="0x0.5" />
	<field name="tacho_active" descr="Indicates which of the tachometer is active (bit per tachometer)\;Bitmask, per bit:\;0: not active\;1: active" access="RO" offset="0x4.16" size="0x0.10" />
	<field name="tacho_active_msb" descr="Indicates which of the tachometer is active (bit per tachometer)\;Bitmask, per bit:\;0: not active\;1: active" access="RO" offset="0x4.26" size="0x0.6" />
</node>

<node name="mfde_event_params_auto_ext" descr="" attr_is_union="1" size="0xa0.0" >
	<field name="crspace_timeout_ext" descr="" subnode="crspace_timeout_ext" offset="0x0.0" selected_by="crspace_timeout" size="0xa0.0" />
	<field name="fatal_cause_ext" descr="" subnode="fatal_cause_ext" offset="0x0.0" selected_by="fatal_cause" size="0xa0.0" />
	<field name="fw_assert_ext" descr="" subnode="fw_assert_ext" offset="0x0.0" selected_by="fw_assert" size="0xa0.0" />
	<field name="kvd_im_stop_ext" descr="" subnode="kvd_im_stop_ext" offset="0x0.0" selected_by="kvd_im_stop" size="0xa0.0" />
	<field name="riscv_exception_ext" descr="" subnode="riscv_exception_ext" offset="0x0.0" selected_by="riscv_exception" size="0x18.0" />
</node>

<node name="mfde_ext" descr="" size="0xb0.0" >
	<field name="event_id" descr="1: crspace_timeout\;2: kvd_im_stop - KVD insertion machine stopped\;3: test\;4: fw_assert\;5: fatal_cause\;6: long_cmd_timeout\;7: riscv_exception\;" access="RO" enum="crspace_timeout=0x1,kvd_im_stop=0x2,test=0x3,fw_assert=0x4,fatal_cause=0x5,long_cmd_timeout=0x6,riscv_exception=0x7" offset="0x0.0" size="0x0.16" />
	<field name="severity" descr="Severity:\;2: FATL - (fatal) Unrecoverable switch behavior\;3: NRML - (normal) Unexpected state with possible systemic Failure\;5: INTR - (debug) Unexpected state without systemic Failure" access="RO" enum="FATL=0x2,NRML=0x3,INTR=0x5" offset="0x0.16" size="0x0.8" />
	<field name="irisc_id" descr="Which RISC triggered the event" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="reg_attr_id" descr="For access register flows: register id\;For MAD flow: attribute id\;For command interface other flows: opcode" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="mgmt_class" descr="Reserved when packet_cmd_type !=1 (mad)\;0: access register over mad" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="packet_state" descr="Packet state\;Current packet state:\;0: idle\;1: retry\;2: long process\;Else, reserved." access="RO" offset="0x4.27" size="0x0.2" />
	<field name="method" descr="0: Query\;1: Write" access="RO" enum="Query=0x0,Write=0x1" offset="0x4.29" size="0x0.1" />
	<field name="notify_fw_dump_completion" descr="When set, SDK should notify FW once upon completion of the FW dump taken due to this event." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="packet_interface" descr="Packet interface identification used internally in the firmware, e.g., PCI, C MDIF_DRIVER, CMDIF_TOOLS, ICMD, INBAND RX0, INBAND RX1, etc...\;0: Buffer_OOB0 \;1: Buffer_OOB1 \;2: Buffer_RX0 \;3: Buffer_RX1 \;4: ICMD\;5: Buffer_PC0 \;6: CMD_IF_Driver \;7: CMD_IF_Tools \;8: Buffer_IPR0_QP0 \;9: Buffer_IPR0_QP1 \;10: Buffer_IPR0_N2N \;11: Buffer_IPR0_HW_Traps \;12: Buffer_IPR1_HW_Traps \;13: Buffer_SMA_Traps_PBG \;14: BMC \;100: Buffer_MNG_SL_Q0 \;101: Buffer_MNG_SL_Q1 \;102: Buffer_MNG_SL_Q2 \;103: Buffer_MNG_SL_Q3 \;104: MNOC0 \;105: MNOC1 \;" access="RO" enum="Buffer_OOB0=0x0,Buffer_OOB1=0x1,Buffer_RX0=0x2,Buffer_RX1=0x3,ICMD=0x4,Buffer_PC0=0x5,CMD_IF_Driver=0x6,CMD_IF_Tools=0x7,Buffer_IPR0_QP0=0x8,Buffer_IPR0_QP1=0x9,Buffer_IPR0_N2N=0xa,Buffer_IPR0_HW_Traps=0xb,Buffer_IPR1_HW_Traps=0xc,Buffer_SMA_Traps_PBG=0xd,BMC=0xe,Buffer_MNG_SL_Q0=0x64,Buffer_MNG_SL_Q1=0x65,Buffer_MNG_SL_Q2=0x66,Buffer_MNG_SL_Q3=0x67,MNOC0=0x68,MNOC1=0x69" offset="0x8.0" size="0x0.8" />
	<field name="packet_cmd_type" descr="Packet command type:\;0: access_register\;1: mad\;2: other\;Else, reserved." access="RO" offset="0x8.8" size="0x0.2" />
	<field name="tile_index" descr="When tile_v=1 the tile_index that caused the timeout.\;\;Note: Supersedes event params&apos; tile_index" access="RO" offset="0x8.16" size="0x0.6" />
	<field name="tile_v" descr="Tile valid:\;0: The timeout was from main\;1: The timeout was from a tile\;\;Note: Supersedes event params&apos; tile_v" access="RO" offset="0x8.23" size="0x0.1" />
	<field name="packet_state_sticky" descr="sticky indication of previous packet state (if at some point it was different then idle it will stick to that value):\;0: idle\;1: retry\;2: long process\;Else, reserved." access="RO" offset="0x8.27" size="0x0.2" />
	<field name="event_params" descr="event parameters - layout is according to event_id value:\;See Table 1308, &quot;Event_params crspace_timeout Layout,&quot; on page 1419\;See Table 1310, &quot;Event_params kvd_im_stop Layout,&quot; on page 1421\;See Table 1312, &quot;Event_params fw_assert Layout,&quot; on page 1422\;See Table 1314, &quot;Event_params fatal_cause Layout,&quot; on page 1424\;See Table 1316, &quot;RiscV Exception Layout,&quot; on page 1425" subnode="mfde_event_params_auto_ext" access="RW" offset="0x10.0" size="0xa0.0" union_selector="$(parent).event_id" />
</node>

<node name="mfm_ext" descr="" size="0x18.0" >
	<field name="index" descr="Index to the fabric memory table." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="memory_high" descr="Holds software-written data.\;Default value: 0x0\;Device reset will reset to the default value." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="memory_low" descr="Holds software-written data.\;Default value: 0x0\;Device reset will reset to the default value." access="RW" offset="0xC.0" size="0x4.0" />
	<field name="memory_mask_high" descr="On write commands, indicates which of the bits from memory field are updated. Reserved on read operations." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="memory_mask_low" descr="On write commands, indicates which of the bits from memory field are updated. Reserved on read operations." access="WO" offset="0x14.0" size="0x4.0" />
</node>

<node name="mfmc_reg_ext" descr="" size="0x1c.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device. \;Range between 0 .. MFPA.flash_num -1" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="wrp_block_count" descr="Power of 2 of the write protect block count\;0: 1 block\;1: 2 blocks\;2: 4 blocks\;3: 8 blocks etc.\;Range 0..5\;Note that per flash device there may be invalid configurations\;Reserved when wrp_en = 0" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="block_size" descr="Block size\;0: write protect sub-sector blocks\;1: write protect sector blocks\;Reserved when wrp_en = 0\;Note that not all block sizes are supported on all flash device, need to check MFPA capabilities" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="wrp_en" descr="Write protect enable\;Set write protect of flash device" access="RW" offset="0x4.31" size="0x0.1" />
	<field name="sub_sector_protect_size" descr="Power of 2 for sub_sector size in 4Kbytes.\;0: 4Kbyte.\;1: 8 Kbyte\;2: 16Kbyte.\;Etc." access="RO" offset="0x8.0" size="0x0.6" />
	<field name="sector_protect_size" descr="Power of 2 for sector size in 4Kbytes.\;0: 4Kbyte.\;1: 8 Kbyte\;2: 16Kbyte.\;Etc." access="RO" offset="0x8.8" size="0x0.6" />
	<field name="quad_en" descr="Quad enable IO bit in the device status register" access="RW" offset="0x10.24" size="0x0.1" />
	<field name="dummy_clock_cycles" descr="The number of dummy clock cycles subsequent to all FAST READ commands. \;Reserved if not supported by the device" access="RW" offset="0x18.0" size="0x0.4" />
</node>

<node name="mfnr_ext" descr="" size="0x30.0" >
	<field name="fan_index" descr="Fan tachometer index.\;" access="INDEX" offset="0x0.0" size="0x0.5" />
	<field name="serial_number" descr="Fan serial number (ASCII string)\;Value of &apos;0&apos;: Some error (Fan not present, disconnected etc.)" access="RO" high_bound="5" low_bound="0" offset="0x4.0" size="0x18.0" />
	<field name="part_number" descr="Fan part number (ASCII string)\;Value of &apos;0&apos;: Some error (Fan not present, disconnected etc.)" access="RO" high_bound="4" low_bound="0" offset="0x1C.0" size="0x14.0" />
</node>

<node name="mfpa_reg_ext" descr="" size="0x20.0" >
	<field name="fs" descr="Flash select - selects the flash device.\;Only zero is supported for NICs with a single flash device.\;Range between 0 .. flash_num -1\;" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="add_cap_32b" descr="Capability bit - If set to &apos;1&apos;, boot_address field is 32 bit length." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="boot_address" descr="The flash address from which the firmware will boot in the next reset (warm start)." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="flash_num" descr="The number of flash devices1: there is 1 flash device, etc." access="RO" offset="0x10.0" size="0x0.4" />
	<field name="sub_sector_wrp_en" descr="If set, MFMC register supports setting write protect with sub-sector- blocks\;Sub-sector block size is available in MFMC.sub_sector_protect_size" access="RO" offset="0x10.16" size="0x0.1" />
	<field name="sector_wrp_en" descr="If set, MFMC register supports setting write protect with sector blocks.\;Sector block size is available in MFMC.sector_protect_size" access="RO" offset="0x10.17" size="0x0.1" />
	<field name="bulk_64kb_erase_en" descr="If set, MFBE register supports 64KB bulk erase operation.\;" access="RO" offset="0x10.29" size="0x0.1" />
	<field name="bulk_32kb_erase_en" descr="If set, MFBE register supports 32KB bulk erase operation." access="RO" offset="0x10.30" size="0x0.1" />
	<field name="wip" descr="Work In Progress. Indicates that the flash is currently busy." access="RO" offset="0x10.31" size="0x0.1" />
	<field name="jedec_id" descr="Return the flash JEDEC ID value returned by the standard Read JEDEC ID command that is available in most flash devices." access="RO" offset="0x14.0" size="0x0.24" />
	<field name="sector_size" descr="The minimal unit that can be erased with and MFBE command (in bytes)." access="RO" offset="0x18.0" size="0x0.10" />
	<field name="block_alignment" descr="Log 2 of the requested write alignment in bytes. Write access to the flash\;must not cross this alignment.\;Read and write access must be aligned to this value." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="block_size" descr="The block size in byes of the flash device, max read size for MFBA (typically 128 bytes)." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="capability_mask" descr="Bitmask indicates which capabilities are supported.\;Bit 15..0: reserved \;\;Bit 16: Set write protect supported (register MFMC supports setting write protection)\;Bit 17: quad enable read write is supported (register MFMC supports setting quad enable)\;Bit 18: set dummy cycle supported (register MFMC supports setting dummy cycles)" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mfrc_ext" descr="" size="0xc.0" >
	<field name="e" descr="Enable bit\;Applies to all fast recovery features.See full behavior of disable below table. \;0: disables the feature and all it&quot;s triggers, without clearing\;the visibility counters of the feature. 1: enables the fast recovery feature. When set after the feature was disabled, all counters are cleared.\;Reserved when trigger is not 0." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="trigger" descr="Trigger of the fast recovery feature: \;0: All (used for &quot;e&quot; bit only)\;2: Credit watchdog.\;4: Raw BER.\;5: Effective BER.\;6: Symbol BER.\;7: TX PLR Trigger.\;Else, reserved." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="capability_bits" descr="capability bits of the fast recovery feature\;0: When set, Credit watchdog notification is supported\;1: When set, Raw BER notification is supported\;2: When set, Effective BER notification is supported\;3: When set, Symbol BER notification is supported\;4: When set, TX PLR Trigger notification is supported" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="en_normal_notification" descr="Enables fast recovery normal notifications (traps) to host (MFRI event). Fast recovery notification are best effort and might drop when congested. \;Reserved when trigger = 0." access="RW" offset="0x8.29" size="0x0.1" />
	<field name="en_warning_notification" descr="Enables fast recovery warning notifications (traps) to host (MFRI event). Fast recovery notification are best effort and might drop when congested. \;Reserved when trigger = 0." access="RW" offset="0x8.30" size="0x0.1" />
	<field name="en_error_notification" descr="Enables fast recovery error notifications (traps) to host (MFRI event). Fast recovery notification are best effort and might drop when congested. \;Reserved when trigger = 0." access="RW" offset="0x8.31" size="0x0.1" />
</node>

<node name="mfri_ext" descr="" size="0x30.0" >
	<field name="port" descr="Local Port Number" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="field_select" descr="Field select bitmask.\;When reading, this is will ignored.\;On the response / trap this will have the bit mask of the valid fields. \;0: num_errors\;1: num_warnings\;2: num_normals\;3: min_value\;4: max_value\;5: consecutive_normal\;6: last_value[0] \;7: last_value[1]\;8: last_value[2]\;Else, reserved." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="thr_type" descr="threshold type exceeded. \;0: Reserved\;1: Error threshold \;2: Warning threshold\;3: Normal TH\;Reserved when not a trap." access="RO" offset="0x4.16" size="0x0.2" />
	<field name="trigger" descr="Trigger of the fast recovery feature: \;2: Credit watchdog.\;4: Raw BER.\;5: Effective BER.\;6: Symbol BER.\;7: TX PLR Trigger.\;Else, reserved." access="INDEX" offset="0x4.24" size="0x0.8" />
	<field name="fields_overflow" descr="fields over flow bit-mask. \;Due to counters size differences between triggers, when a bit is set, it means that the counter got to the max value it can count:\;0: num_errors\;1: num_warnings\;2: num_normals\;3: min_value\;4: max_value\;5: consecutive_normal\;6: last_value[0] \;7: last_value[1]\;8: last_value[2]\;Else, reserved." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="num_errors" descr="Accumulated number of error events since last reset." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="num_warnings" descr="Number of warning events." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="min_value" descr="Minimum value pet time window." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="max_value" descr="Maximum value pet time window." access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="consecutive_normal" descr="The number of consecutive time windows which the port was in Normal mode.\;Reserved when last_value isn&apos;t normal." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="last_value" descr="The values of the last time windows,\;when last[0] is the latest.\;" access="RO" high_bound="2" low_bound="0" offset="0x24.0" size="0xc.0" />
</node>

<node name="mfrl_reg_ext" descr="" size="0x8.0" >
	<field name="reset_trigger" descr="The firmware reset trigger. \;Bit 0: TRIGGER0 (live-patch) - When selecting this trigger, all other fields are NA.\;Bit 1: TRIGGER1 (Immediate Reset) Note: this reset trigger must be selected explicitly by user and cannot be triggered as part of default logic. \;Bit 3: TRIGGER3 (PCIe link toggle | hot reset), For this reset trigger, need to configure pci_reset_req_method). \;Bit 6: TRIGGER6 (PERST)\;Other bits are reserved." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="reset_type" descr="Each bit represents a chip reset type.\;If set to &apos;1&apos;, the reset is supported.\;Bit 0: Full chip reset\;Bit 1: Keep network port active during reset\;Bit 3: ARM only reset\;Bit 4: ARM OS shut down\;Bit 5: Network reset - Keep PCIe active during reset." access="RO" offset="0x4.8" size="0x0.8" />
	<field name="reset_state" descr="Reset state.\;0: IDLE\;1: Negotiation in progress\;2: Reset in progress\;3: Error - Negotiation timeout\;4: Error - Negotiation dis-acknowledgment\;5: Error- driver unload timeout [DWIP]\;6: Error- ARM OS is up, please shut down\;7: ARM OS shut down in progress\;8: Waiting for reset trigger\;9-15: Reserved" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="pci_reset_req_method" descr="FW reset Method selector; Support for the different reset methods exposed through reset_info register. \;0: Link Disable \;1: Hot reset (SBR) \;2-7: reserved ." access="RW" offset="0x4.21" size="0x0.3" />
	<field name="rst_type_sel" descr="The requested reset type.\;When reset_trigger = Immediate (1), reset_type_sel valid values are: bit3 or bit4 (ARM only reset or ARM os shutdown)" access="RW" offset="0x4.24" size="0x0.3" />
	<field name="pci_sync_for_fw_update_resp" descr="Response of the driver for the reset request.\;1: Acknowledgment\;2: Dis-acknowledgment\;3: Reserved" access="WO" enum="Acknowledgment=0x1,Dis=0x2,Reserved=0x3" offset="0x4.27" size="0x0.2" />
	<field name="pci_sync_for_fw_update_start" descr="This field defines the reset flow. \;0: Legacy flow \;1: Synced driver flow  \;2: Synced tool flow \;Synced driver flow will not require to issue MFRL command \;from other hosts (x86 / ARM for SoC) \;Synced tool flow required to be executed from external host (should not be executed from internal host)." access="RW" offset="0x4.29" size="0x0.2" />
	<field name="pci_rescan_required" descr="Setting this bit to 1 indicates a need of rescan for the corresponding PCI slot" access="RO" offset="0x4.31" size="0x0.1" />
</node>

<node name="mfrp_ext" descr="" size="0x1c.0" >
	<field name="trigger" descr="Trigger of the fast recovery feature: \;2: Credit watchdog.\;4: aw BER.\;5: Effective BER.\;6: Symbol BER.\;7: TX PLR Trigger.\;Else, reserved." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="port MSB" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="en_thr" descr="Enable thresholds: \;0: No thresholds activated\;1: Only Error threshold is activated\;2: Only Warning and Normal thresholds are activated\;3: All three thresholds are activated" access="RO" offset="0x4.0" size="0x0.2" />
	<field name="error_thr_action" descr="Action required when exceeding error_thr.\;0: Do nothing\;1: Toggle the physical link (drop to polling).\;2: Change logical state to Init." access="RO" offset="0x4.4" size="0x0.2" />
	<field name="error_thr" descr="Error threshold- refers to the number of credit watchdog events that occurred in the specific time window. \;When the switch reaches this threshold it shall drop the logical link. \;Reserved when en_thr is 0 or 2." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="warning_thr" descr="Warning threshold- number of credit watchdog events that occurred in the specific time window. \;Shall be smaller than error_thr when set.\;Reserved when en_thr is 0 or 1." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="normal_thr" descr="Normal threshold- number of credit watchdog events that occurred in the specific time window. \;Shall be smaller than warning_thr.\;Reserved when en_thr is 0 or 1." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_window" descr="The time frame which the events are grouped. This is a tumbling window (not a sliding window), means that each window is uncorrelated to the adjacent windows events. \;Time frame to measure Normal_thr.\;Units of sampling_rate.\;Value of zero is non valid." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="sampling_rate" descr="Time frame to measure warning threshold and error threshold. \;Units of 10mSec, range 0..1Sec." access="RO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mfsc_ext" descr="" size="0x8.0" >
	<field name="pwm" descr="Fan pwm to control / monitor" access="INDEX" offset="0x0.24" size="0x0.3" />
	<field name="pwm_duty_cycle" descr="Controls the duty cycle of the PWM. Value range from 0..255 to represent duty cycle of 0%...100%" access="RW" offset="0x4.0" size="0x0.8" />
</node>

<node name="mfsl_ext" descr="" size="0xc.0" >
	<field name="ie" descr="Interrupt Enable. If the ie bit is set and the Tachometer reading is out of range as defined by tach_min and tach_max, the FERR# will be asserted." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="ee" descr="Event Enable.\;0 - Do not generate event\;1 - Generate Event \;2 - Generate single event\;For Fan Error Evet details refer to Section  3.5.10, &quot;MRSV - Management Read Straps Value Register&quot;." access="RW" offset="0x0.2" size="0x0.2" />
	<field name="tacho" descr="Fan tachometer index" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="tach_min" descr="Tachometer minimum value (minimum RPM)." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="tach_max" descr="Tachometer maximum value (maximum RPM)." access="RW" offset="0x8.0" size="0x0.16" />
</node>

<node name="mfsm_ext" descr="" size="0x8.0" >
	<field name="n" descr="" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="tacho" descr="Fan tachometer index" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rpm" descr="Fan speed (round per minute) calculated based on the time measurement between n fan pulses.\;Note that in order for the RPM to be correct, the n value should correspond to the number of tach pulses per rotation measured by the tachometer." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="mfsv_reg_ext" descr="" size="0x30.0" >
	<field name="efuses_prog_en" descr="When this bit is set, it indicates that it is allowed for the boot FW to program the FW security version related EFUSEs if needed. This bit is not relevant in case the FW operates in an automatically EFUSEs programming approach (set in the INI file). Once set to 1, this configuration will be relevant only for the upcoming boot, thus this configuration will be set back to 0 upon next boot.\;\;" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="fw_sec_ver_stat" descr="Firmware security version status.0: EFUSEs value is equal to the currently running FW image value. No change is needed.1: EFUSEs value is smaller than the currently running FW image value. An update to the EFUSEs is required.2: There is pending image, MFSV is rejected\;3: Reserved\;\;" access="RO" offset="0x0.1" size="0x0.2" />
	<field name="efuses_prog_method" descr="EFUSEs programming method.0: manually. Upon boot, if FW indicates that FW_sec_ver_stat is 1 and only if EFUSEs_prog_en is 1, it will program the EFUSEs as needed.1: automatically. Upon boot, if FW indicates that FW_sec_ver_stat is 1, it will program the EFUSEs as needed.\;\;" access="RO" offset="0x0.3" size="0x0.1" />
	<field name="revoke_efuse_prog" descr="0: EFUSEs value is equal to the currently running FW image value. No change is needed. \;1: EFUSEs value is smaller than the currently running FW image value. An update to the EFUSEs is required. \;" access="RW" offset="0x0.4" size="0x0.1" />
	<field name="pending_efuse_prog" descr="0: No pending EFUSE programming command \;1: There is pending MFSV command \;\;" access="RO" offset="0x0.5" size="0x0.1" />
	<field name="dummy_ratchet_prog_en" descr="[Internal]\;Relevant only from CX8/QM3/ArcusE \;When this bit is set, device should increase dummy ratchet value (fuse_psc_reserved2_field_ratchet) \;\;In case that fuse_psc_reserved2_field_ratchet = 0xFFFF, return Fuse_failure = 2." access="RO" offset="0x0.6" size="0x0.1" />
	<field name="fuse_failure" descr="" access="RO" offset="0x0.8" size="0x0.2" />
	<field name="index" descr="Index\;0: NCORE FW\;1: PSC_BL1\;2: PSC_FW\;3: BCT\;4: reserved2_field_ratchet\;5-15: Reserved" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="img_sec_ver" descr="Image security version value" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="efuses_sec_ver" descr="EFUSEs security version value" access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mgcr_reg_ext" descr="" size="0x20.0" >
	<field name="segment" descr="The GPIO segment which the command&apos;s parameters apply" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="segments_count" descr="Ceiling function of total number of GPIOs / 32 in the system." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="GPIO_data_in" descr="Input value of accessible GPIO[i] signals.\;When GPIO_access_en[i] = 0, GPIO_data_in[i] always returns 0" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="GPIO_data_out" descr="Output value of accessible GPIO signals.\;When GPIO_access_en[i] = 0, GPIO_data_out[i] always returns 0" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="GPIO_set" descr="These 2 fields are used together to control GPIO signals in the following manner:\;GPIO_set[i]=0, GPIO_clear[i]=0 : GPIO_data_out[i] = No Change\;GPIO_set[i]=0, GPIO_clear[i]=1 : GPIO_data_out[i] = 0\;GPIO_set[i]=1, GPIO_clear[i]=0 : GPIO_data_out[i] = 1\;GPIO_set[i]=1, GPIO_clear[i]=1 : GPIO_data_out[i] = not(GPIO_data_out[i])\;Ignored for non-controllable GPIO signals." access="WO" offset="0xC.0" size="0x4.0" />
	<field name="GPIO_clear" descr="These 2 fields are used together to control GPIO signals in the following manner:\;GPIO_set[i]=0, GPIO_clear[i]=0 : GPIO_data_out[i] = No Change\;GPIO_set[i]=0, GPIO_clear[i]=1 : GPIO_data_out[i] = 0\;GPIO_set[i]=1, GPIO_clear[i]=0 : GPIO_data_out[i] = 1\;GPIO_set[i]=1, GPIO_clear[i]=1 : GPIO_data_out[i] = not(GPIO_data_out[i])\;Ignored for non-controllable GPIO signals." access="WO" offset="0x10.0" size="0x4.0" />
	<field name="GPIO_access_en" descr="Access allowance to the corresponding GPIO signal.\;0: GPIO[i] is not observable / controllable by the host SW.\;1: GPIO[i] is observable / controllable by the host SW." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="direction" descr="0: GPIO[i] is an input only signal\;1: GPIO[i] is an output signal. Data out can be updates by the host SW and data in can be queried by the host SW.\;For non-accessible GPIOs, the corresponding value is 0." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="drive_type" descr="0: GPIO[i] is an open drain output. The device can only drive the GPIO[i] output pin low when GPIO_data_out[i] is 0. When GPIO_data_out[i] is 1, GPIO[i] is in HighZ. \;1: GPIO[i] is a full-drive output pin\;When GPIO_access_en[i] =0, direction[i] and drive_type[i] are always read as 0." access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgir_dev_info_ext" descr="" size="0x1c.0" >
	<field name="dev_branch_tag" descr="The format of the string represented by ASCII." access="RO" high_bound="27" low_bound="0" offset="0x0.24" size="0x1c.0" />
</node>

<node name="mgir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see Table 272, &quot;Hardware Info Layout,&quot; on page 276" subnode="mgir_hardware_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
	<field name="fw_info" descr="Firmware Information, see Table 275, &quot;Firmware Info Layout,&quot; on page 280" subnode="mgir_fw_info_ext" access="RW" offset="0x20.0" size="0x40.0" />
	<field name="sw_info" descr="Software Information, see Table 277, &quot;Software Info Layout,&quot; on page 283\;This field indicates the oldest software version compatible with the current firmware" subnode="mgir_sw_info_ext" access="RW" offset="0x60.0" size="0x20.0" />
	<field name="dev_info" descr="Development Information, see Table 281, &quot;Development Info Layout,&quot; on page 286" subnode="mgir_dev_info_ext" access="RW" offset="0x80.0" size="0x1c.0" />
</node>

<node name="mgir_fw_info_ext" descr="" size="0x40.0" >
	<field name="sub_minor" descr="Sub-minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_sub_minor." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_minor." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major firmware version number.\;Deprecated and returns &apos;0&apos;. \;Refer to extended_major." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="secured" descr="When set, the device is running firmware with secure-firmware updates capabilities." access="RO" offset="0x0.24" size="0x0.1" />
	<field name="signed_fw" descr="When set the device is running a signed FW binaries." access="RO" offset="0x0.25" size="0x0.1" />
	<field name="debug" descr="When set, the device is running a debug firmware. &apos;debug&apos; binary can only be installed on specific devices (identified by their &apos;Factory base MAC&apos;), which currently run a specific firmware version. These restrictions are expressed by a signed &apos;debug&apos; token that must be loaded to the device before installing the debug binary." access="RO" offset="0x0.26" size="0x0.1" />
	<field name="dev" descr="*NOTE* this field has diff meaning for Switch vs. NIC \;\;\;" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="string_tlv" descr="When set, string-TLV is supported.\;For Retimer - always return 0 (not supported)." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="dev_sc" descr="*NOTE* for NICs same as dev field\;Development-secure:\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="build_id" descr="Firmware Build ID. Optional. \;Note: Deprecated for switches and returns &apos;0&apos;." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="year" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="day" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="month" descr="Firmware installation date. \;\;For example: 3 May 2004 will be coded as Month= 0x05, Day= 0x03, and Year= 0x04" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="hour" descr="Firmware installation hour.\;For example 17:43 will be coded as 0x1743" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="psid" descr="FW PSID" access="RO" high_bound="15" low_bound="0" offset="0x10.24" size="0x10.0" />
	<field name="ini_file_version" descr="User-configured version number of the current INI file." access="RO" offset="0x20.0" size="0x4.0" />
	<field name="extended_major" descr="FW version&apos;s Major field in extended (32b) format." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="extended_minor" descr="FW version&apos;s Minor field in extended (32b) format." access="RO" offset="0x28.0" size="0x4.0" />
	<field name="extended_sub_minor" descr="FW version&apos;s SubMinor field in extended (32b) format." access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="isfu_major" descr="incremented by one when version is not ISSUable" access="RO" offset="0x30.0" size="0x0.16" />
	<field name="disabled_tiles_bitmap" descr="Bitmap representing the disabled tiles in the ASIC. Tile &apos;0&apos; is represented by the msb bit. \;0: tile is enabled\;1: tile is disabled\;\;The total number of tiles can be derived through MGPIR register." access="RO" offset="0x30.16" size="0x0.16" />
	<field name="life_cycle" descr="0: Production\;1: GA Secured\;2: GA Non-Secured\;3: RMA\;4: Pre Production\;Note: has also msb bits in life_cycle_msb.\;" access="RO" offset="0x34.0" size="0x0.2" />
	<field name="sec_boot" descr="0: Disable\;1: Enable" access="RO" offset="0x34.2" size="0x0.1" />
	<field name="encryption" descr="0: Disable\;1: Enable" access="RO" offset="0x34.3" size="0x0.1" />
	<field name="life_cycle_msb" descr="[DWIP]\;MSB of the life cycle.\;Supported in QM3, CX8 and on." access="RO" offset="0x34.4" size="0x0.3" />
	<field name="issu_able" descr="[DWIP]\;ISSU-able:\;0: not ISSUable\;1: ISSUable\;Supported from Quantum-3 and on\;Supported for Retimers\;Based on FW decisions: fuse, INI, NV and version on flash vs. running version" access="RO" offset="0x34.13" size="0x0.1" />
	<field name="pds" descr="[DWIP]\;0: PSC is not PDS mode\;1: PSC in PDS mode\;Supported in QM3,CX8 and on." access="RO" offset="0x34.14" size="0x0.1" />
</node>

<node name="mgir_hardware_info_ext" descr="" size="0x20.0" >
	<field name="device_id" descr="PCI device ID." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="device_hw_revision" descr="See Table 274, &quot;Device HW Revision Descriptions,&quot; on page 279" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="pvs" descr="Process Voltage Scaling\;Supported nominal V_CORE voltage (in 50mV units) for the device." access="RO" offset="0x4.0" size="0x0.5" />
	<field name="technology" descr="Process technology\;0: N/A\;1: 40nm\;2: 28nm\;3: 16nm\;4: 7nm\;5: 5nm\;6-31: Reserved" access="RO" offset="0x4.11" size="0x0.5" />
	<field name="num_ports" descr="Number of ports the device supports." access="RO" offset="0x4.16" size="0x0.12" />
	<field name="ib_mad_gen" descr="[DWIP]\;IB MAD Protocol. Based on value from ConfigProfile\;0: IBg1\;1: IBg2\;2-7: Reserved" access="RO" offset="0x4.28" size="0x0.3" />
	<field name="hw_dev_id" descr="The PCI device-ID of the NIC/HCA in recovery (Livefish) mode." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="vbios_variant" descr="[GPUNet]\;0: boards prior to C05\;1: boards 05 and later\;3-4: Reserved\;\;Supported in GB100." access="RO" offset="0xC.0" size="0x0.2" />
	<field name="module_master_fw_default" descr="Module Master FW Default\;0: FW is in control over modules management by default\;1: SW is in control over modules management by default\;2: Standalone ASIC (no I2C connectivity).\; Note: Relevant only for Spectrum-3 and above" access="RO" offset="0xC.16" size="0x0.2" />
	<field name="cpo_indication" descr="[DWIP][switch_only] \;When set, this bit indicate this is CPO system" access="RO" offset="0xC.27" size="0x0.1" />
	<field name="ga_valid" descr="GA Valid bit\;0: MGIR.HW Info.ga is reserved\;1: MGIR.HW Info.ga is valid\;\;Supported in CX7, QM3 and on." access="RO" offset="0xC.28" size="0x0.1" />
	<field name="development" descr="[DWIP]\;The device is running:\;0: a regular-secure firmware version\;1: a development-secure firmware version\;\;Supported in QM3,CX8 and on." access="RO" offset="0xC.30" size="0x0.1" />
	<field name="manufacturing_base_mac_47_32" descr="MSB of the &quot;base&quot; MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not supported." access="RO" offset="0x10.0" size="0x0.16" />
	<field name="ga" descr="[DWIP]\;Geographical Address\;0: ASIC 0\;1: ASIC 1\;2: ASIC 2\;3: ASIC 3\;Valid for multi ASIC platforms only\;\;Describes the device index for the compute node." access="RO" offset="0x10.16" size="0x0.6" />
	<field name="chip_type" descr="[DWIP]\;Chip Type\;0: Real chip\;1: Emulation\;2: ChipSim\;3: SimX \;Supported from Quantum-3 and ArcusE" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="manufacturing_base_mac_31_0" descr="LSB of the &quot;base&quot; MAC address of the NIC that was allocate during manufacturing. The NIC derives the MAC addresses for the different PCI PFs from this MAC address. This parameter can be used as a canonical unique identifier of the NIC.\;manufacturing_base_mac of value 0 means field is not supported." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="device_ticks_per_msec" descr="Device Ticks per msec\;Reserved when chip_type = Real chip (0)" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="uptime" descr="Time (in secs.) since last reset0" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mgir_sw_info_ext" descr="" size="0x20.0" >
	<field name="sub_minor" descr="Sub-minor Driver version number.\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="minor" descr="Minor Driver version number.\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="major" descr="Major Driver version number.\;" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="rom3_type" descr="ROM 3 type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP\;0x4: NVME\;0x5: FCODE\;0x6: UEFI Virtio net\;0x7: UEFI Virtio blk\;0x8: PXE Virtio net\;0x9-0xF: Reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="rom3_arch" descr="Arch type of ROM 3:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="rom2_type" descr="ROM 2type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP\;0x4: NVME\;0x5: FCODE\;0x6: UEFI Virtio net\;0x7: UEFI Virtio blk\;0x8: PXE Virtio net\;0x9-0xF: Reserved" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="rom2_arch" descr="Arch type of ROM 2:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.12" size="0x0.4" />
	<field name="rom1_type" descr="ROM 1type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP\;0x4: NVME\;0x5: FCODE\;0x6: UEFI Virtio net\;0x7: UEFI Virtio blk\;0x8: PXE Virtio net\;0x9-0xF: Reserved" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="rom1_arch" descr="Arch type of ROM 1:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.20" size="0x0.4" />
	<field name="rom0_type" descr="ROM 0 type:\;0x0: none\;0x1: Flexboot\;0x2: UEFI\;0x3: UEFI-CLP\;0x4: NVME\;0x5: FCODE\;0x6: UEFI Virtio net\;0x7: UEFI Virtio blk\;0x8: PXE Virtio net\;0x9-0xF: Reserved" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="rom0_arch" descr="Arch type of ROM 0:\;0x0: unspecified\;0x1: AMD64 - x86 64bit architecture\;0x2: AARCH64 - ARM Architecture 64 bits\;0x3: AMD64_AARCH64 - ROM code supporting both AMD64 and AARCH64 architectures\;0x4: IA32 - Intel Architecture 32 bits" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="rom0_version" descr="ROM 0 version." subnode="rom_version_ext" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="rom1_version" descr="ROM 1 version." subnode="rom_version_ext" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="rom2_version" descr="ROM 2version." subnode="rom_version_ext" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="rom3_version" descr="ROM 3 version." subnode="rom_version_ext" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="mgls_ext" descr="" size="0xc.0" >
	<field name="bank_sn" descr="Sequence number of the active nv bank." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="entries_in_last_bank" descr="Number of log entries in the active bank." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="entries_in_log" descr="Total number of entries in nv log." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mgnle_reg_ext" descr="" size="0x20.0" >
	<field name="le_pointer" descr="Pointer to the log entry (see description above for more information)\;" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="clr" descr="Clears the log entry after read.\;\;Supported only if MCAM.mng_feature_cap_mask bit 60 is set." access="OP" offset="0x4.0" size="0x0.1" />
	<field name="lost_events" descr="The number of events that the system failed to log since the previous log entry.\;15 should be interpreted as &apos;15 or more events were lost&apos;" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="synced_time" descr="0x0: Boot - time is measured since NIC bootup.\;0x1: Synced - time was synced by the host." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="time_h" descr="The 32 MSB of the 64bit timestamp.  In microseconds\;When &quot;time_synced&quot; bit is set this is the time passed since the 1/1/1970 epoch.\;When &quot;time_synced&quot; is cleared this is the NIC uptime." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_l" descr="The 32 LSB of the 64bit timestamp.  In microseconds" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RO" offset="0x10.0" size="0xc.0" />
	<field name="log_data" descr="The logged data. Format is  different per the according to the log type." access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x1C.0" size="0x4.0" size_condition="$(parent).configuration_item_header.length" />
</node>

<node name="mgpc_ext" descr="" size="0x18.0" >
	<field name="counter_index" descr="counter index\;For Spectrum: see Section 5.2, &quot;Flow Counters&quot;, on page 1254\;Range 0 .. cap_shared_counter_pool_size - 1" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="counter_set_type" descr="Counter Set Type\;For Spectrum: See Section 5.2.2, &quot;Counter Set Type&quot;, on page 1255" access="OP" offset="0x0.24" size="0x0.8" />
	<field name="opcode" descr="0: Nop\;\;2: Flush Counters - when counter set is un-bound, flush ensures counters will not be updated due to packets in the pipe. Valid only on Write operation\;8: Clear counters. Setting the clr bit will reset the counter value for all counters of the specified Router Interface.\;" access="OP" offset="0x4.28" size="0x0.4" />
	<field name="byte_counter" descr="Byte counter value" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="packet_counter" descr="Packet counter value\;Spectrum HW has 58bits for packet counters" subnode="uint64" access="RW" offset="0x10.0" size="0x8.0" />
</node>

<node name="mgpcb_ext" descr="" size="0x410.0" >
	<field name="counter_index_base" descr="Counter Index base\;Range 0..cap_shared_counter_pool_size - 1\;Supported only for counter_set_type = 0x3 Packets and Byte" access="OP" offset="0x0.0" size="0x0.24" />
	<field name="num_rec" descr="Number of valid records\;Range 1..64" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="opcode" descr="0: Nop\;8: Clear counters" access="OP" offset="0x8.0" size="0x0.4" />
	<field name="record" descr="See Table 1189, &quot;MGPCB - record Layout,&quot; on page 1316\;" subnode="mgpcb_record_ext" access="RW" high_bound="63" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="mgpcb_record_ext" descr="" size="0x10.0" >
	<field name="byte_counter" descr="Bytes counter value" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="packet_counter" descr="Packets counter value" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="mgpir_ext" descr="" size="0xa0.0" >
	<field name="hw_info" descr="Hardware Information, see Table 165, &quot;Hardware Info Layout,&quot; on page 185" subnode="mgpir_hw_info_ext" access="RW" offset="0x0.0" size="0x20.0" />
</node>

<node name="mgpir_hw_info_ext" descr="" size="0x20.0" >
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="max_modules_per_slot" descr="Maximum number of modules that can be connected per slot. Includes internal and external modules." access="RO" offset="0x4.16" size="0x0.8" />
	<field name="num_lanes_per_sub_module" descr="Maximum lane count per submodule" access="RO" offset="0x8.16" size="0x0.4" />
	<field name="max_sub_modules_index" descr="The maximum submodule index.\;0: Only one submodule 3: Four submodules\;\;Other values are reserved" access="RO" offset="0x8.24" size="0x0.4" />
</node>

<node name="mhmpr_reg_ext" descr="" size="0x14.0" >
	<field name="upm" descr="&apos;0&apos; - if the ports are managed by host.\;&apos;1&apos; - if the ports are not managed by host" access="RW" offset="0x0.0" size="0x0.1" />
</node>

<node name="mhsr_ext" descr="" size="0x8.0" >
	<field name="health" descr="Software health state:\;0 - Failure\;1 - Reserved\;2 - Normal Operation\;3 - Boot / Init (default state)" access="WO" offset="0x0.0" size="0x0.4" />
</node>

<node name="mini_data_auto_ext" descr="" attr_is_union="1" size="0x40.0" >
	<field name="mini_fused_out_ports_ext" descr="" subnode="mini_fused_out_ports_ext" offset="0x0.0" selected_by="fused_out_ports" size="0x40.0" />
	<field name="mini_module_i2c_mapping_ext" descr="" subnode="mini_module_i2c_mapping_ext" offset="0x0.0" selected_by="module_i2c_mapping" size="0x40.0" />
	<field name="mini_module_power_level_ext" descr="" subnode="mini_module_power_level_ext" offset="0x0.0" selected_by="module_power_level" size="0x4.0" />
</node>

<node name="mini_ext" descr="" size="0x50.0" >
	<field name="type" descr="Type:\;\;3: module_i2c_mapping\;4: module_power_level\;5: fused_out_ports\;" access="INDEX" enum="module_i2c_mapping=0x3,module_power_level=0x4,fused_out_ports=0x5" offset="0x0.0" size="0x0.8" />
	<field name="index" descr="index\;Index depends on MINI.type \;" access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="valid" descr="Valid:\;0: the relevant type is not supported by this Firmware version\;1: the relevant type is valid" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="data" descr="This field takes meaning per type\;For module_i2c_mapping see Table  297, &quot;MINI type module_i2c_mapping Register Layout,&quot; on page  294\;For module_power_level see Table  299, &quot;MINI type module_power_level Layout,&quot; on page  295\;For disabled_ports see Table  301, &quot;MINI type fused_out_ports Layout,&quot; on page  296\;" subnode="mini_data_auto_ext" access="RW" offset="0x10.0" size="0x40.0" union_selector="$(parent).type" />
</node>

<node name="mini_fused_out_ports_ext" descr="" size="0x40.0" >
	<field name="fused_out_ports_bitmap" descr="Bitmap for indicating which ports are being disabled\;For each bit\;0: Port is enabled\;1: Port is disabled\;" access="RO" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="mini_module_i2c_mapping_ext" descr="" size="0x40.0" >
	<field name="module_gw_num" descr="Module I2C GW Id" access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="mini_module_power_level_ext" descr="" size="0x4.0" >
	<field name="spl" descr="Supported Power Level\;Units of 0.25Watt\;0 = 0W\;1 = 0.25W\;2 = 0.5W\;3 = 0.75W\;and so on\;" access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="mirc_reg_ext" descr="" size="0x8.0" >
	<field name="status_code" descr="Indicates the successful completion of the instruction, or the reason it failed. \;0x0: OK\;0x1: BUSY\;0x2: PROHIBITED_FW_VER_ERR\;0x3: FIRST_PAGE_COPY_FAILED\;0x4: FIRST_PAGE_ERASE_FAILED\;0x5: FIRST_PAGE_RESTORE_FAILED\;0x6: CANDIDATE_FW_DEACTIVATION_FAILED\;0x7: FW_ALREADY_ACTIVATED\;0x8: ERROR_DEVICE_RESET_REQUIRED\;0x9: ERROR_FW_PROGRAMMING_NEEDED\;Other values should be treated as an unknown error." access="RO" offset="0x0.0" size="0x0.8" />
</node>

<node name="misoc_reg_ext" descr="" size="0x120.0" >
	<field name="type" descr="Type of component query:\;0x0: ARM_ATF\;0x1: ARM_UEFI\;0x2: DPU_BMC\;0x3: CEC\;All other values are reserved" access="INDEX" enum="ARM_ATF=0x0,ARM_UEFI=0x1,DPU_BMC=0x2,CEC=0x3" offset="0x0.0" size="0x0.4" />
	<field name="query_pending" descr="If set, the query will be for the pending version instead on the current version" access="INDEX" offset="0x0.30" size="0x0.1" />
	<field name="query_not_availble" descr="If set, the version information for this component type is not available\;In this case the version will be all zeros" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="version" descr="The version as a null-terminated ASCII string\;Null termination will not be present if version takes up all of the field size" access="RO" high_bound="255" low_bound="0" offset="0x10.24" size="0x100.0" />
</node>

<node name="missuv_ext" descr="" size="0x20.0" >
	<field name="valid" descr="Valid target version:\;0: not found a valid target version\;1: found a valid target version\;When &apos;0&apos; - all other fields are reserved" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="target_major" descr="Target FW version&apos;s Major field in extended (32b) format." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="target_minor" descr="Target FW version&apos;s Minor field in extended (32b) format." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="target_sub_minor" descr="Target FW version&apos;s SubMinor field in extended (32b) format." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="target_issu_minor" descr="Target ISSU Minor version" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="target_issu_major" descr="Target ISSU Major version (compare to MGIR.isfu_major)" access="RO" offset="0x1C.16" size="0x0.16" />
</node>

<node name="mjtag_ext" descr="" size="0x30.0" >
	<field name="size" descr="Size of operation - relevant for JTAG interface access commands only, indicating the number of transaction bytes to execute. Maximum size supported is 40.\;Note: when size=0, no operation is performed (clock is not toggled). The tdo is sampled and provided in the response at jtag_transaction_set_0." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="sequence_number" descr="Command sequence number - to prevent re-execution of the same command due to command retransmission, this command includes a sequence number.\;The enable and disable commands MUST be issues with sequence_number = 0 while any JTAG access command must increase the sequence_number by 1 (the first JTAG access command should start at sequence_number = 1)." access="WO" offset="0x0.24" size="0x0.4" />
	<field name="cmd" descr="Command\;0 - JTAG interface disable - JTAG interface is disabled\;1 - JTAG interface enable - enabling JTAG interface\;2 - JTAG interface access" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="jtag_transaction_set" descr="See Table 95, &quot;JTAG Transaction Set Byte Layout,&quot; on page 133" access="RW" high_bound="43" low_bound="0" offset="0x4.24" size="0x2c.0" />
</node>

<node name="mkdc_reg_ext" descr="" size="0x2c.0" >
	<field name="error_code" descr="Indicates the successful completion of the instruction or the reason it failed:\;0: OK\;1: BAD_SESSION_ID\;2: BAD_KEEP_ALIVE_COUNTER\;3: BAD_SOURCE_ADDRESS\;4: SESSION_TIMEOUT\;Other values are Reserved." access="RO" enum="OK=0x0,BAD_SESSION_ID=0x1,BAD_KEEP_ALIVE_COUNTER=0x2,BAD_SOURCE_ADDRESS=0x3,SESSION_TIMEOUT=0x4" offset="0x0.0" size="0x0.4" />
	<field name="session_id" descr="Unique debug session identifier." access="INDEX" offset="0x0.16" size="0x0.16" />
	<field name="current_keep_alive_counter" descr="Running counter that states the current sequence number of each keep-alive session." access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="next_keep_alive_counter" descr="Running counter that states the expected next sequence number of each keep-alive session." access="RO" offset="0x8.0" size="0x4.0" />
</node>

<node name="mlcr_ext" descr="" size="0xc.0" >
	<field name="led_type" descr="Led type (only supported when cap_local_or_uid_only==1.)\;0: LOCALP_AND_UID - not supported\;1: UID \;2: LOCALP - local port\;" access="INDEX" enum="LOCALP_AND_UID=0x0,UID=0x1,LOCALP=0x2" offset="0x0.0" size="0x0.4" />
	<field name="cap_local_or_uid_only" descr="If set, led_type of type UID and LOCAL Port only are supported." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="operation_cap" descr="If set to &apos;1&apos;, operation field is supported." access="RO" offset="0x0.5" size="0x0.1" />
	<field name="operation" descr="0: Controlled by HW / Beacon\;1: LED on - \;LED Scheme #1: PHY LED amber on, Logic LED off\;LED Scheme #2: PHY LED amber on, Logic LED Green On\;2: LED off - PHY and Logic LEDs are off\;Others: Reserved" access="RW" offset="0x0.12" size="0x0.4" />
	<field name="local_port" descr="Local port number\;Not supported for CPU port\;Valid only when led_type = LOCALP (2)" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="2-bit expansion of the local port. Represents the local_port[9:8] bits\;Valid only when led_type = LOCALP (2)" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="beacon_duration" descr="Duration of the beacon to be active, units of seconds\;The value of 0x0 will turn off the beacon\;The value of 0xffff will set the beacon to infinity" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="beacon_remain" descr="Remaining duration of the beacon, units of seconds\;The value of 0xffff means infinity" access="RO" offset="0x8.0" size="0x0.16" />
</node>

<node name="mmdio_ext" descr="" size="0xc.0" >
	<field name="operation" descr="0 - NOP\;1 - Address (reserved for Clause 22)\;2 - Read\;3 - Write\;4 - Post Read Increment Address (reserved for Clause 22)\;6 - Address + Read - Generates Address cycle and then Read cycle in Clause 45 (reserved for Clause 22)\;7 - Address + Write - Generates Address cycle and then Write cycle in Clause 45 (reserved for Clause 22)" access="WO" offset="0x0.0" size="0x0.3" />
	<field name="clause" descr="MDIO Definition:\;0 - Clause 22\;1 - Clause 45" access="WO" offset="0x0.8" size="0x0.2" />
	<field name="mdio_index" descr="Selection of the MDIO interface" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="reg_adr" descr="Reg Address (Clause 22) / Dev Type (Clause 45)" access="RW" offset="0x4.0" size="0x0.5" />
	<field name="phy_adr" descr="PHY Address (PHYAD)" access="RW" offset="0x4.8" size="0x0.5" />
	<field name="data" descr="Data (Clause 22) / Address/Data (Clause 45)" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="address" descr="Address (Clause 45)\;This field is only valid for Address + Read and Address + Write operations, providing the address. For other Clause 45 operations the data field provides the address when appropriate." access="RW" offset="0x8.16" size="0x0.16" />
</node>

<node name="mmgcr_ext" descr="" size="0x48.0" >
	<field name="device_uid" descr="Device UID.\;Default value is 0.\;This field will configure the mirror_device_uid TLV for the mirror header - Table 1031, &quot;ETH-ERSPAN Mirror Header TLV MIRROR_DEVICE_UID Frame Fields,&quot; on page 1311" access="RW" offset="0x0.0" size="0x0.24" />
	<field name="elig_ip_len_en" descr="[DWIP]\;Eligibility test for IP packet length.\;Non-IP packets are not eligible.\;\;Supported by Spectrum-5 onwards." access="RW" offset="0xC.0" size="0x0.1" />
	<field name="elig_cbset_10_en" descr="[DWIP][Spectrum-6]\;Eligibility test for Custom Byte Set 10 ([21:20]).\;\;Supported by Spectrum-6 onwards." access="RW" offset="0xC.1" size="0x0.1" />
	<field name="elig_cbset_11_en" descr="[DWIP]\;Eligibility test for Custom Byte Set 11 ([23:22]).\;\;Supported by Spectrum-5 onwards." access="RW" offset="0xC.2" size="0x0.1" />
	<field name="elig_bth_en" descr="[DWIP]\;Eligibility test for packets with BTH.\;When unset, BTH eligibility tests are skipped - packets with or without BTH pass.\;\;Supported by Spectrum-5 onwards." access="RW" offset="0xC.3" size="0x0.1" />
	<field name="elig_dscp_en" descr="[DWIP][Spectrum-6]\;Eligibility test for DSCP.\;Non-IP packets are not eligible.\;\;Supported by Spectrum-6 onwards." access="RW" offset="0xC.4" size="0x0.1" />
	<field name="elig_mask" descr="[DWIP]\;If set on Write, update eligibility parameters.\;\;Reserved on Query.\;Supported by Spectrum-5 onwards." access="WO" offset="0xC.31" size="0x0.1" />
	<field name="elig_ip_min_size" descr="[DWIP]\;Eligible minimum IP packet length. Packets with length greater than the minimum set are eligible. Mirroring or trimming for payloads equal or shorter to the set minimum length will be disabled.\;\;For IPv4 packets the total length is taken.\;For IPv6 packets the payload length is taken.\;\;Reserved when elig_ip_len_en=0.\;Supported by Spectrum-5 onwards." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="elig_cbset_10_mask" descr="[DWIP][Spectrum-6]\;Custom Byte Set 10 ([21:20]) mask.\;\;Reserved when elig_cbset_10_en=0.\;Supported by Spectrum-6 onwards." access="RW" offset="0x18.0" size="0x0.16" />
	<field name="elig_cbset_10" descr="[DWIP][Spectrum-6]\;Custom Byte Set 10 ([21:20]) eligible value.\;Value to compare masked Custom Byte Set 10 with.\;\;Reserved when elig_cbset_10_en=0.\;Supported by Spectrum-6 onwards." access="RW" offset="0x18.16" size="0x0.16" />
	<field name="elig_cbset_11_mask" descr="[DWIP]\;Custom Byte Set 11 ([23:22]) mask.\;\;Reserved when elig_cbset_11_en=0.\;Supported by Spectrum-5 onwards." access="RW" offset="0x1C.0" size="0x0.16" />
	<field name="elig_cbset_11" descr="[DWIP]\;Custom Byte Set 11 ([23:22]) eligible value.\;Value to compare masked Custom Byte Set 11 with.\;\;Spectrum-5: CBSET 11 is all 0 if it is not valid.\;\;Reserved when elig_cbset_11_en=0.\;Supported by Spectrum-5 onwards." access="RW" offset="0x1C.16" size="0x0.16" />
	<field name="elig_bth_opcode_bitmap" descr="[DWIP]\;Eligible BTH opcodes when the packet is BTH. Represented as bitmap. Set opcodes are eligible.\;\;Reserved when elig_bth_en=0.\;Supported by Spectrum-5 onwards." access="RW" high_bound="7" low_bound="0" offset="0x20.0" size="0x20.0" />
	<field name="elig_dscp_bitmap" descr="[DWIP][Spectrum-6]\;Eligible DSCPs in an IP packet. Represented as bitmap. Set values are eligible.\;Non-IP packets are not eligible.\;\;Reserved when elig_dscp_en=0.\;Supported by Spectrum-6 onwards." subnode="uint64" access="RW" offset="0x40.0" size="0x8.0" />
</node>

<node name="mmta_reg_ext" descr="" size="0x90.0" >
	<field name="module" descr="module number" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="supported_measurements" descr="Supported measurements bit mask\;0: Temperature\;1: TEC Power\;2: Second Temperature\;Other are reserved" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="module_name_hi" descr="8 characters long module name" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="module_name_lo" descr="8 characters long module name" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="module_temperature" descr="Temperature, see Table 135, &quot;Module Temperature Layout,&quot; on page 166" subnode="mmta_temprature_ext" access="RW" offset="0xC.0" size="0x18.0" />
	<field name="module_tec_power" descr="TEC Power, see Table 137, &quot;Module TEC Power Layout,&quot; on page 168" subnode="mmta_tec_power_ext" access="RW" offset="0x24.0" size="0x20.0" />
	<field name="module_second_temperature" descr="Second Temperature, see Table 135, &quot;Module Temperature Layout,&quot; on page 166\;" subnode="mmta_temprature_ext" access="RW" offset="0x44.0" size="0x18.0" />
</node>

<node name="mmta_tec_power_ext" descr="" size="0x20.0" >
	<field name="cooling_level" descr="The required cooling level based on TEC power and Set Point\;" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="temp_unit" descr="Temperature measurement units\;0: units of 0.125 Celsius degrees\;1: units of 1/256 Celsius degrees\;\;For negative values 2&apos;s complement is used\;" access="INDEX" offset="0x0.29" size="0x0.1" />
	<field name="mtecr" descr="Max TEC Power Reset:\;0: do not modify the value of the max temperature register\;1: clear the value of the TEC Power and Setpoint register" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="mtece" descr="Max TEC Power Enable:\;0: disable measuring the max TEC Power and set point on a module\;1: enables measuring the max TEC Power and set point on a module" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tec_power" descr="TEC power reading from the module. Units of 1mW." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_tec_power" descr="The highest measured TEC power from the module.\;Reserved when mtece = 0\;Cleared by mtecr = 1" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="tec_power_warning_low" descr="Refers to module TEC Power low warning threshold. Units of 1mW." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="tec_power_warning_high" descr="Refers to module TEC Power high warning threshold. Units of 1mW." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="tec_power_alarm_low" descr="Refers to module TEC Power low alarm threshold. Units of 1mW." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="tec_power_alarm_high" descr="Refers to module TEC Power high alarm threshold. Units of 1mW." access="RO" offset="0xC.16" size="0x0.16" />
	<field name="set_point_temperature" descr="Laser set point measured from the laser\;Units defined at temp_unit field\;" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="max_set_point_temperature" descr="The highest measured set point from the module.\;Reserved when mtece = 0\;Cleared by mtecr = 1" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="set_point_temperature_warning_low" descr="Refers to module set point low warning threshold Units defined at temp_unit field" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="set_point_temperature_warning_high" descr="Refers to module TEC Power high warning threshold Units defined at temp_unit field" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="set_point_temperature_alarm_low" descr="Refers to module set point low alarm threshold\;Units defined at temp_unit field" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="set_point_temperature_alarm_high" descr="Refers to module set point high alarm threshold\;Units defined at temp_unit field" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="min_cooling_level" descr="The minimum allowed cooling level\;" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="max_cooling_level" descr="The maximum allowed cooling level\;" access="RO" offset="0x1C.16" size="0x0.16" />
</node>

<node name="mmta_temprature_ext" descr="" size="0x18.0" >
	<field name="temp_unit" descr="Temperature measurement units\;0: units of 0.125 Celsius degrees\;1: units of 1/256 Celsius degrees\;\;For negative values 2&apos;s complement is used\;" access="INDEX" offset="0x0.26" size="0x0.1" />
	<field name="tempee" descr="Temperature Warning Event Enable (MMTA Trap)\;0: do_not_generate_event\;1: generate_event\;2: generate_single_event" access="RW" enum="do_not_generate_event=0x0,generate_event=0x1,generate_single_event=0x2" offset="0x0.27" size="0x0.2" />
	<field name="tempwe" descr="Temperature Warning Enable:\;0: all fields are set\;1: only tempee field is set, all other fields reserved" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="mtempr" descr="Max Temperature Reset:\;0: do not modify the value of the max temperature register\;1: clear the value of the max temperature register" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="mtempe" descr="Max Temperature Enable:\;0: disable measuring the max temperature on a sensor\;1: enables measuring the max temperature on a sensor" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="temperature" descr="Temperature reading from the module\;Units defined at temp_unit field" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the module.\;Reserved when mte = 0\;Cleared by mtr = 1" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="temperature_warning_low" descr="Refers to module temperature low warning threshold\;Units defined at temp_unit field" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="temperature_warning_high" descr="Refers to module temperature high warning threshold\;Units defined at temp_unit field" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="temperature_alarm_low" descr="Refers to module temperature low alarm threshold\;Units defined at temp_unit field" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="temperature_alarm_high" descr="Refers to module temperature high alarm threshold\;Units defined at temp_unit field" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="mnvda_reg_ext" descr="" size="0x10c.0" >
	<field name="configuration_item_header" descr="Configuration Item Header" subnode="config_item_ext" access="RW" offset="0x0.0" size="0xc.0" />
	<field name="configuration_item_data" descr="Configuration Item Data" access="RW" high_bound="63" low_bound="0" offset="0xC.0" size="0x100.0" />
</node>

<node name="mnvdi_reg_ext" descr="" size="0xc.0" >
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RW" offset="0x0.0" size="0xc.0" />
</node>

<node name="mnvgc_reg_ext" descr="" size="0x10.0" >
	<field name="nvda_read_factory_settings" descr="0:unsupported\;1: supported" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="nvda_read_current_settings" descr="NVDA Read current settings. Indicates if reading the current settings by NVDA is supported.\;0: unsupported\;1: supported" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="priv_nv_other_host" descr="When set, TLVs of other hosts may be modified." access="RO" offset="0x0.2" size="0x0.1" />
</node>

<node name="mnvgn_reg_ext" descr="" size="0x20.0" >
	<field name="nv_pointer" descr="Pointer to the NV parameter (see description above for more information)" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="configuration_item_header" descr="" subnode="config_item_ext" access="RW" offset="0x10.0" size="0xc.0" />
	<field name="configuration_item_data" descr="Configuration Item Data" access="RW" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x1C.0" size="0x4.0" size_condition="$(parent).configuration_item_header.length" />
</node>

<node name="mnvia_reg_ext" descr="" size="0x8.0" >
	<field name="target" descr="Information targeted for invalidation\;0: ALL - all NVRAM parameters.\; All other values are reserved." access="WO" offset="0x0.0" size="0x0.3" />
	<field name="writer_id" descr="The entity which perform the invalidate.\;The encoding same as writer_id in Configuration Item register (See Table 375, &quot;Configuration Item Header Layout,&quot; on page 344)." access="RW" offset="0x0.4" size="0x0.5" />
</node>

<node name="mnvqc_reg_ext" descr="" size="0x8.0" >
	<field name="type" descr="Configuration item type according to its class. \;Table 377, &quot;Configuration Item Data Type Class Global Layout,&quot; on page 348\;Table 379, &quot;Configuration Item Data Type Class Physical Port Layout,&quot; on page 348\;Table 381, &quot;Configuration Item Data Type Class Per Host-PF Layout,&quot; on page 349\;Table 383, &quot;Configuration Item Data Type Class Log Layout,&quot; on page 349\;Table 385, &quot;Configuration Item Data Type Class File Layout,&quot; on page 350\;\;Table 389, &quot;Configuration Item Data Type Class Multi Instance Layout,&quot; on page 351" access="INDEX" offset="0x0.0" size="0x4.0" />
	<field name="support_rd" descr="The configuration item is supported and can be read" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_wr" descr="The configuration item is supported and can be updated" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="version" descr="The maximal version of the configuration item supported by the device" access="RO" offset="0x4.4" size="0x0.4" />
</node>

<node name="moca_ext" descr="" size="0xc.0" >
	<field name="counter_index" descr="counter index\;For Spectrum: see Section 5.2, &quot;Flow Counters&quot;, on page 1254\;Range 0 .. cap_shared_counter_pool_size - 1" access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="counter_type" descr="0: flow counter\;1: flow estimator counter\;" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="size" descr="Amount of counters to allocate from counter_index.\;Counter_index + size must not exceedcap_shared_counter_pool_size - 1\;Reserved when read." access="OP" offset="0x8.0" size="0x0.24" />
</node>

<node name="mocmi_ext" descr="" size="0x14.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number (Rx ports)\;Not supported from CPU port\;Not supported from router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cond_nelp" descr="Conditional mirroring:\;Disables a dynamic mirror trigger per ingress local_port\;For non-Elephant packets only\;\;Bitwise vector, value per mirror trigger (e.g. bit 3 for trigger 0x3 Tail drop mirror)\;Value per bit:\;0: Enable mirror trigger \;1: Disable mirror trigger\;\;Notes: \;1. the enable does not trigger the mirror, it just allows the mirror\;2. applies only to dynamic mirror triggers\;Bits of static mirror triggers are reserved\;" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="cond_elp" descr="Conditional mirroring:\;Disables a dynamic mirror trigger per ingress local_port\;Same logic as for cond_nelp\;For Elephant packets only" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="elig" descr="[DWIP]\;Enable eligibilty testing.\;See MMGCR for eligibility tests configuration (Section 5.2.1, &quot;MMGCR - Monitoring Mirroring Global Configuration Register&quot;, on page 1268).\;Implemented for tail drop (INGRESS_SHARED_BUFFER), see Section 5.4.1, &quot;Mirror Triggers&quot;, on page 1269.\;Disabled by default.\;Reserved when cond_nelp or cond_elp are disabled for tail drop.\;Supported from Spectrum-5 onwards." access="RW" offset="0x10.3" size="0x0.1" />
</node>

<node name="mocs_ceer_ext" descr="" size="0x40.0" >
	<field name="port_mask" descr="Local port.\;Each bit represents a local port.Refer to Section 9.3, &quot;Port Numbering&quot;, on page 1899 for port numbering scheme.\;CPU port is not supported.\;Router port is not supported.\;\;The device will report information only about flows that were identified as elephant flows (thus the CEER.detection_entry will be chosen by the device). \;When MOCS.clear is set then for the trap the CEER.clear=1. \;Endianity example: local_port 1 is at 3Ch bit1" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
</node>

<node name="mocs_entry_auto_ext" descr="" attr_is_union="1" size="0xc8.0" >
	<field name="mocs_ceer_ext" descr="" subnode="mocs_ceer_ext" offset="0x0.0" selected_by="CEER" size="0x40.0" />
	<field name="mocs_fsed_ext" descr="" subnode="mocs_fsed_ext" offset="0x0.0" selected_by="FSED" size="0x10.0" />
	<field name="mocs_mafbi_ext" descr="" subnode="mocs_mafbi_ext" offset="0x0.0" selected_by="MAFBI" size="0x8.0" />
	<field name="mocs_mgpcb_ext" descr="" subnode="mocs_mgpcb_ext" offset="0x0.0" selected_by="MGPCB" size="0x8.0" />
	<field name="mocs_mofrb_ext" descr="" subnode="mocs_mofrb_ext" offset="0x0.0" selected_by="MOFRB" size="0x60.0" />
	<field name="mocs_moftd_ext" descr="" subnode="mocs_moftd_ext" offset="0x0.0" selected_by="MOFTD" size="0x10.0" />
	<field name="mocs_pbsr_ext" descr="" subnode="mocs_pbsr_ext" offset="0x0.0" selected_by="PBSR" size="0x40.0" />
	<field name="mocs_pbsr_v2_ext" descr="" subnode="mocs_pbsr_v2_ext" offset="0x0.0" selected_by="PBSR_V2" size="0x14.0" />
	<field name="mocs_ppcnt_ext" descr="" subnode="mocs_ppcnt_ext" offset="0x0.0" selected_by="PPCNT_SES1" size="0xa0.0" />
	<field name="mocs_ppcnt_v2_ext" descr="" subnode="mocs_ppcnt_v2_ext" offset="0x0.0" selected_by="PPCNT_V2_SES1" size="0xc8.0" />
	<field name="mocs_rarftbr_ext" descr="" subnode="mocs_rarftbr_ext" offset="0x0.0" selected_by="RARFTBR" size="0x8.0" />
	<field name="mocs_sbsrd_ext" descr="" subnode="mocs_sbsrd_ext" offset="0x0.0" selected_by="SBSRD" size="0x4.0" />
	<field name="mocs_upcnt_ext" descr="" subnode="mocs_upcnt_ext" offset="0x0.0" selected_by="UPCNT" size="0x48.0" />
	<field name="mocs_usacn_ext" descr="" subnode="mocs_usacn_ext" offset="0x0.0" selected_by="USACN" size="0x48.0" />
	<field name="mocs_utcc_ext" descr="" subnode="mocs_utcc_ext" offset="0x0.0" selected_by="UTCC" size="0x44.0" />
</node>

<node name="mocs_ext" descr="" size="0xe8.0" >
	<field name="type" descr="Session type:\;0x0: PPCNT_SES0 - (provides PPCNT traps)\;0x1: PPCNT_SES1 - (provides PPCNT traps)\;0x2: MGPCB\;0x3: PBSR\;0x4: SBSRD\;0x5: CEER\;0x6: MAFBI\;0x7: MOPCE\;0x8: FSED\;0xA: USACN\;0xB: UTCC\;0xC: UPCNT\;0xD: MOFRB\;0xE: MOFTD\;0x10: RARFTBR\;0x20: PPCNT_V2_SES0\;0x21: PPCNT_V2_SES1\;0x23: PBSR_V2\;" access="INDEX" enum="PPCNT_SES0=0x0,PPCNT_SES1=0x1,MGPCB=0x2,PBSR=0x3,SBSRD=0x4,CEER=0x5,MAFBI=0x6,MOPCE=0x7,FSED=0x8,USACN=0xa,UTCC=0xb,UPCNT=0xc,MOFRB=0xd,MOFTD=0xe,RARFTBR=0x10,PPCNT_V2_SES0=0x20,PPCNT_V2_SES1=0x21,PBSR_V2=0x23" offset="0x0.0" size="0x0.8" />
	<field name="status" descr="Status:\;0: IDLE\;1: BUSY\;2: CANCELED\;3: CONT" access="RO" enum="IDLE=0x0,BUSY=0x1,CANCELED=0x2,CONT=0x3" offset="0x4.0" size="0x0.2" />
	<field name="opcode" descr="Opcode.\;Note that a session is per type, thus multi sessions are allowed for different types.\;Opcode START cannot be set when a session is BUSY.\;\;0: START - start a session. Per session rejected when status = BUSY.\;1: CANCEL - cancel the session, see explanation above.\;2: STOP_ITERATIONS - completes current iteration, finishes MOCS afterwards." access="WO" enum="START=0x0,CANCEL=0x1,STOP_ITERATIONS=0x2" offset="0x4.8" size="0x0.4" />
	<field name="clear" descr="Clear the counters:\;0x0: READ_NO_CLEAR\;0x1: READ_AND_CLEAR\;0x2: CLEAR_ONLY - no read, for faster operation. Will provide only MOCS_DONE trap when finished.\;\;Reserved when type = MOPCE (0x7), FSED (0x8), MOFTD (0xE), RARFTBR (0x10)" access="RW" enum="READ_NO_CLEAR=0x0,READ_AND_CLEAR=0x1,CLEAR_ONLY=0x2" offset="0x4.16" size="0x0.2" />
	<field name="event_tid" descr="Transaction ID to be returned in the event EMADs\;Example: \;- MOCS had tid=3 and event_tid=17\;- MOCS returned with tid=3 and event_tid=17\;- PPCNT returned with tid=17\;- MOCS_DONE returned with tid=17 and event_tid=17" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
	<field name="num_of_iter" descr="Number of iterations.\;Value 0 - no iterative MOCS operation.\;Reserved when type is not MOFTD, RARFTBR\;Reserved when inf_iter=1." access="RW" offset="0x10.0" size="0x0.16" />
	<field name="min_iter_time" descr="Minimum time for one iteration from start to start.\;Units of 50uSec (e.g. value of 12 means 0.6mSec).\;If the iteration takes shorter than min_iter_time then FW will wait before starting the next iteration.\;The iteration may take longer than min_iter_time, in that case iteration mode behaves as fast as possible (AFAP).\;Range 2 and above\;Reserved when iter_mode = 0\;Reserved when num_of_iter = 0 and inf_iter = 0." access="RW" offset="0x10.16" size="0x0.8" />
	<field name="iter_mode" descr="Iteration mode:\;0: AFAP - as fast as possible\;1: WAIT - wait iter_time from start to start\;Reserved when num_of_iter = 0 and inf_iter = 0." access="RW" enum="AFAP=0x0,WAIT=0x1" offset="0x10.28" size="0x0.2" />
	<field name="inf_iter" descr="Infinite iterations.\;When set MOCS iterations are not limited.\;Stopping iterative operation is done with opcode = STOP_ITERATIONS." access="RW" offset="0x10.31" size="0x0.1" />
	<field name="iter_md_op" descr="Metadata operation selector for iterations.\;0: Before_every_REG_TLV\;1: Before_new_iteration_REG_TLVs_only\;Reserved when metadata=0.\;" access="OP" enum="Before_every_REG_TLV=0x0,Before_new_iteration_REG_TLVs_only=0x1" offset="0x14.23" size="0x0.1" />
	<field name="metadata" descr="Metadata selector.\;Only 1 metadata TLV per event is supported.\;0: None\;1: Iteration\;2: Iteration_plus_timestamp\;" access="OP" enum="None=0x0,Iteration=0x1,Iteration_plus_timestamp=0x2" offset="0x14.24" size="0x0.8" />
	<field name="entry" descr="See Table 1194, &quot;MOCS entry - PPCNT Layout,&quot; on page 1323\;See Table 1196, &quot;MOCS entry - PPCNT V2 Layout,&quot; on page 1324\;See Table 1198, &quot;MOCS entry - MGPCB Layout,&quot; on page 1326\;See Table 1200, &quot;MOCS entry - PBSR Layout,&quot; on page 1327\;See Table 1202, &quot;MOCS entry - PBSR V2 Layout,&quot; on page 1328\;See Table 1204, &quot;MOCS entry - SBSRD Layout,&quot; on page 1329\;See Table 1206, &quot;MOCS entry - CEER Layout,&quot; on page 1330\;See Table 1208, &quot;MOCS entry - MAFBI Layout,&quot; on page 1331\;See Table 1210, &quot;MOCS entry - FSED Layout,&quot; on page 1332\;See Table 1212, &quot;MOCS entry - USACN Layout,&quot; on page 1334\;See Table 1214, &quot;MOCS entry - UTCC Layout,&quot; on page 1335\;See Table 1216, &quot;MOCS entry - UPCNT Layout,&quot; on page 1336\;See Table 1218, &quot;MOCS entry - MOFRB Layout,&quot; on page 1337\;See Table 1222, &quot;MOCS entry - MOFTD Layout,&quot; on page 1339\;See Table 1224, &quot;MOCS entry - RARFTBR Layout,&quot; on page 1340\;" subnode="mocs_entry_auto_ext" access="RW" offset="0x20.0" size="0xc8.0" union_selector="$(parent).type" />
</node>

<node name="mocs_fsed_ext" descr="" size="0x10.0" >
	<field name="filter_fields" descr="filter fields:\;If a bit is &apos;0&apos; then the relevant field is ignored and dump is\;done regardless of the field value\;\;0: partition_id\;1: activity\;2: semaphore_state\;3: group_id\;\;All set filters are relevant (there is AND between the filters)" access="OP" enum="partition_id=0x0,activity=0x1,semaphore_state=0x2,group_id=0x3" offset="0x0.0" size="0x0.4" />
	<field name="op" descr="Operation\;0: Dump_entries \;1: Clear_activity_for_all_dumped_entries\;2: Clear_activity_only - (no dump)\;" access="OP" enum="Dump_entries=0x0,Clear_activity_for_all_dumped_entries=0x1,Clear_activity_only=0x2" offset="0x0.8" size="0x0.2" />
	<field name="entry_partition_id" descr="Dump only if entry partition has value of entry_parition\;Reserved when filter_fields bit0 is &apos;0&apos;" access="INDEX" offset="0x4.0" size="0x0.3" />
	<field name="entry_activity" descr="Dump only if activity has value of entry_activity\;Reserved when filter_fields bit1 is &apos;0&apos;" access="INDEX" offset="0x4.8" size="0x0.1" />
	<field name="entry_sem_s" descr="Dump only if semaphore state has value of entry_sem_s\;Reserved when filter_fields bit2 is &apos;0&apos;" access="INDEX" offset="0x4.9" size="0x0.1" />
	<field name="group_id" descr="Dump only if Group id equals to the value mentioned\;Reserved when filter_fields bit3 is &apos;0&apos;" access="INDEX" offset="0x4.16" size="0x0.16" />
	<field name="num_rec" descr="Number of records to read\;Range 0 .. (cap_kvd_size-1)\;\;Reserved when op = Clear only (2)" access="RW" offset="0x8.0" size="0x0.20" />
	<field name="nt" descr="New transaction\;0: continue_from_last_transaction\;1: start_new_transaction" access="OP" enum="continue_from_last_transaction=0x0,start_new_transaction=0x1" offset="0xC.0" size="0x0.1" />
</node>

<node name="mocs_mafbi_ext" descr="" size="0x8.0" >
	<field name="num_rec" descr="Number of records to read\;Must have a value of 32*N \;Range: 32.. cap_max_accuflow/2" access="RW" offset="0x0.0" size="0x0.24" />
	<field name="type" descr="type" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="flush" descr="Flush:\;0: do not flush the counters, read immediately\;1: flush the counters" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="counter_index_base" descr="Counter Index base\;Must have a value of 32*N \;Range: cap_start_accuflow .. cap_start_accuflow+cap_max_accuflow" access="RW" offset="0x4.0" size="0x0.24" />
</node>

<node name="mocs_mgpcb_ext" descr="" size="0x8.0" >
	<field name="num_rec" descr="Number of records to read\;Range 1..cap_shared_counter_pool_size" access="RW" offset="0x0.0" size="0x0.24" />
	<field name="flush" descr="Flush:\;0: do not flush the counters, read immediately\;1: flush the counters\;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="counter_index_base" descr="Counter Index base\;Range 0..cap_shared_counter_pool_size - 1\;Supported only for counter_set_type = 0x3 Packets and Byte" access="RW" offset="0x4.0" size="0x0.24" />
</node>

<node name="mocs_mofrb_ext" descr="" size="0x60.0" >
	<field name="flow_estimator_record" descr="See" subnode="flow_estimator_record_ext" access="RW" high_bound="11" low_bound="0" offset="0x0.0" size="0x60.0" />
</node>

<node name="mocs_moftd_ext" descr="" size="0x10.0" >
	<field name="user_cookie" descr="User cookie that will be sent with the data\;Opaque value" subnode="uint64" access="RW" offset="0x8.0" size="0x8.0" />
</node>

<node name="mocs_pbsr_ext" descr="" size="0x40.0" >
	<field name="port_mask" descr="Local port.\;Each bit represents a local port. Refer to Section 9.3, &quot;Port Numbering&quot;, on page 1899 for port numbering scheme.\;CPU port is supported\;Router port is not supported\;Endianity example: local_port 1 is at 3Ch bit1" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
</node>

<node name="mocs_pbsr_v2_ext" descr="" size="0x14.0" >
	<field name="bitmap_size" descr="Bitmap size in DWORDs.\;Range is 0..floor(cap_max_switch_ports/32)+1.\;E.g. bitmap_size 16 is for 512 ports, 17 for 544 ports, 32 for 1024 ports, etc.\;" access="OP" offset="0x0.0" size="0x0.8" />
	<field name="port_mask" descr="Port mask array, read as one bitmap.\;Each bit represents a local port. Refer to Section 9.3, &quot;Port Numbering&quot;, on page 1899 for port numbering scheme.\;CPU port is supported\;Router port is not supported\;Endianity example: local_port 1 is at 3Ch bit1" access="RW" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x10.0" size="0x4.0" size_condition="$(parent).bitmap_size" />
</node>

<node name="mocs_ppcnt_ext" descr="" size="0xa0.0" >
	<field name="port_mask" descr="Local port\;Each bit represents a PPCNT.local_port\;Endianity example: local_port 1 is at 3Ch bit1" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
	<field name="grp_mask" descr="PPCNT Group mask\;Each bit represents a PPCNT.grp" access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
	<field name="tc_mask" descr="PPCNT tclass mask - valid only for relevant groups\;Each bit represents a PPCNT.prio_tc" access="RW" offset="0x50.0" size="0x4.0" />
	<field name="rx_buffer_mask" descr="PPCNT rx_buffer mask - valid only for relevant groups\;Each bit represents a PPCNT.prio_tc" access="RW" offset="0x54.0" size="0x0.16" />
	<field name="prio_mask" descr="PPCNT prio mask - valid only for relevant groups\;Each bit represents a PPCNT.prio_tc" access="RW" offset="0x54.16" size="0x0.16" />
</node>

<node name="mocs_ppcnt_v2_ext" descr="" size="0xc8.0" >
	<field name="grp_mask" descr="PPCNT Group mask\;Each bit represents a PPCNT.grp" access="RW" high_bound="3" low_bound="0" offset="0x20.0" size="0x10.0" />
	<field name="tc_mask" descr="PPCNT tclass mask - valid only for relevant groups\;Each bit represents a PPCNT.prio_tc" access="RW" offset="0x30.0" size="0x4.0" />
	<field name="prio_mask" descr="PPCNT prio mask - valid only for relevant groups\;Each bit represents a PPCNT.prio_tc" access="RW" offset="0x34.0" size="0x0.17" />
	<field name="rx_buffer_mask" descr="PPCNT rx_buffer mask - valid only for relevant groups\;Each bit represents a PPCNT.prio_tc" access="RW" offset="0x38.0" size="0x0.16" />
	<field name="port_bitmap_size" descr="Bitmap size in DWORDs.\;Range is 0..floor(cap_max_switch_ports/32)+1.\;E.g. bitmap_size 16 is for 512 ports, 17 for 544 ports, 32 for 1024 ports, etc." access="OP" offset="0xC0.0" size="0x0.8" />
	<field name="port_mask" descr="Port mask array, read as one bitmap.\;Each bit represents a local port. Refer to Section 9.3, &quot;Port Numbering&quot;, on page 1899 for port numbering scheme.\;Each bit represents a PPCNT.local_port" access="RW" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0xC4.0" size="0x4.0" size_condition="$(parent).port_bitmap_size" />
</node>

<node name="mocs_rarftbr_ext" descr="" size="0x8.0" >
	<field name="num_job" descr="Number of RARFTBR calls.\;Range is 1..24." access="OP" offset="0x0.0" size="0x0.12" />
	<field name="job" descr="RARFTBR job records.\;See Table 1226, &quot;MOCS-RARFTBR Record Layout,&quot; on page 1340" subnode="mocs_rarftbr_record_ext" access="RW" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x4.0" size="0x4.0" size_condition="$(parent).num_job" />
</node>

<node name="mocs_rarftbr_record_ext" descr="" size="0x4.0" >
	<field name="arft_index" descr="The first AR Flow Table index to begin with." access="INDEX" offset="0x0.0" size="0x0.20" />
	<field name="num_rec_log" descr="Number of Flow Table entries, logarithmic scale, i.e. num_rec = 2num_rec_log.\;Requested size should fit a one or two consecutive (per AR profile) FG ECMP sized blocks, See Section 14.5.4.4, &quot;ECMP Size&quot;, on page 3490.\;Range 5..13.\;Note: A single job can result in multiple RARFTBR events." access="OP" offset="0x0.24" size="0x0.5" />
</node>

<node name="mocs_sbsrd_ext" descr="" size="0x4.0" >
	<field name="modi" descr="[Spectrum-6][DWIP]\;Read modification descriptor.\;On egress, only buff_occupancy is valid.\;Supported from Spectrum-6." access="RW" offset="0x0.27" size="0x0.1" />
	<field name="desc" descr="[Advanced]\;Read descriptors status" access="RW" offset="0x0.28" size="0x0.1" />
	<field name="cells" descr="Read cells status" access="RW" offset="0x0.29" size="0x0.1" />
	<field name="snap" descr="Read snapshot\;Note that clear will not take affect on snapshot" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="curr" descr="Read current status" access="RW" offset="0x0.31" size="0x0.1" />
</node>

<node name="mocs_upcnt_ext" descr="" size="0x48.0" >
	<field name="port_mask" descr="Local port.\;Each bit represents a local port" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
	<field name="grp_mask" descr="UPCNT Group mask\;Each bit represents a UPCNT.grp" subnode="uint64" access="RW" offset="0x40.0" size="0x8.0" />
</node>

<node name="mocs_usacn_ext" descr="" size="0x48.0" >
	<field name="port_mask" descr="Local port.\;Each bit represents a local port" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
	<field name="side" descr="Bit 0: Host\;Bit 1: Line" access="RW" offset="0x40.0" size="0x0.4" />
	<field name="num_rec" descr="Number of records to read\;Range: 1.. cap_sadb_entries - sadb_entry_index_base" access="RW" offset="0x44.0" size="0x0.16" />
	<field name="sadb_entry_index_base" descr="SADB entry index base\;Range 0.. cap_sadb_entries - 1\;Note: cap_sadb_entries is provided by UGCAP" access="RW" offset="0x44.16" size="0x0.16" />
</node>

<node name="mocs_utcc_ext" descr="" size="0x44.0" >
	<field name="port_mask" descr="Local port.\;Each bit represents a local port" access="RW" high_bound="15" low_bound="0" offset="0x0.0" size="0x40.0" />
	<field name="side" descr="Bit 0: Host\;Bit 1: Line" access="RW" offset="0x40.0" size="0x0.4" />
</node>

<node name="modcr_ext" descr="" size="0x14.0" >
	<field name="clear" descr="Clear the coutners" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="fatal_asserts" descr="Count number of fatal asserts" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="normal_asserts" descr="Count number of normal asserts" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="debug_asserts" descr="Count number of debug asserts" access="RO" offset="0x10.0" size="0x4.0" />
</node>

<node name="module_latched_flag_info_ext" descr="" size="0x50.0" >
	<field name="rx_los_cap" descr="when set, indicates modules supports rx los indication" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="dp_fw_fault" descr="Valid for CMIS based modules only\;Latched modules Datapath fw fault flag" access="RO" offset="0x0.22" size="0x0.1" />
	<field name="mod_fw_fault" descr="Valid for CMIS based modules only\;Latched module fw fault flag" access="RO" offset="0x0.23" size="0x0.1" />
	<field name="vcc_flags" descr="Latched VCC flags of module\;Bit 0: high_vcc_alarm\;Bit 1: low_vcc_alarm\;Bit 2: high_vcc_warning\;Bit 3: low_vcc_warning" access="RO" enum="high_vcc_alarm=0x1,low_vcc_alarm=0x2,high_vcc_warning=0x4,low_vcc_warning=0x8" offset="0x0.24" size="0x0.4" />
	<field name="temp_flags" descr="Latched temperature flags of module\;Bit 0: high_temp_alarm\;Bit 1: low_temp_alarm\;Bit 2: high_temp_warning\;Bit 3: low_temp_warning" access="RO" enum="high_temp_alarm=0x1,low_temp_alarm=0x2,high_temp_warning=0x4,low_temp_warning=0x8" offset="0x0.28" size="0x0.4" />
	<field name="tx_ad_eq_fault" descr="Reserved for SFP\;Bitmask for latched Tx adaptive equalization fault flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="tx_cdr_lol" descr="Bitmask for latched Tx cdr loss of lock flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="tx_los" descr="Reserved for SFP\;Bitmask for latched Tx loss of signal flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="tx_fault" descr="Bitmask for latched Tx fault flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="tx_power_lo_war" descr="Bitmask for latched Tx power low warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="tx_power_hi_war" descr="Bitmask for latched Tx power high warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="tx_power_lo_al" descr="Bitmask for latched Tx power low alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="tx_power_hi_al" descr="Bitmask for latched Tx power high alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="tx_bias_lo_war" descr="Bitmask for latched Tx bias low warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="tx_bias_hi_war" descr="Bitmask for latched Tx bias high warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0xC.8" size="0x0.8" />
	<field name="tx_bias_lo_al" descr="Bitmask for latched Tx bias low alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0xC.16" size="0x0.8" />
	<field name="tx_bias_hi_al" descr="Bitmask for latched Tx bias high alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0xC.24" size="0x0.8" />
	<field name="rx_cdr_lol" descr="Bitmask for latched Rx cir loss of lock flag per lane.\;Bit 0 - lane 0 .. Bit 7 - lane 7" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="rx_los" descr="Bitmask for latched Rx loss of signal flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x10.24" size="0x0.8" />
	<field name="rx_power_lo_war" descr="Bitmask for latched Rx power low warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="rx_power_hi_war" descr="Bitmask for latched Rx power high warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x14.8" size="0x0.8" />
	<field name="rx_power_lo_al" descr="Bitmask for latched Rx power low alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x14.16" size="0x0.8" />
	<field name="rx_power_hi_al" descr="Bitmask for latched Rx power high alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x14.24" size="0x0.8" />
	<field name="rx_output_valid_change" descr="Bitmask for latched rx output valid change per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x18.0" size="0x0.8" />
	<field name="laser_source_flag_in_use_msb" descr="Bitmask per flag type in ELS module.\;When bit is set, indicates that FW reads flag from module.\;In order to get reliable latched flag information for that flag, it&apos;s recommended to set event for module flags via trap.\;Bit 0: laser2_temp_hi_al\;Bit 1: laser2_temp_lo_al\;Bit 2: laser2_temp_hi_war\;Bit 3: laser2_temp_lo_war\;" access="RO" offset="0x18.24" size="0x0.4" />
	<field name="laser2_warning_flag" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser2 warning indication" access="RO" offset="0x18.28" size="0x0.1" />
	<field name="laser_warning_flag" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser warning indication\;" access="RO" offset="0x18.29" size="0x0.1" />
	<field name="laser2_fault_flag" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser2 fault indication" access="RO" offset="0x18.30" size="0x0.1" />
	<field name="laser_fault_flag" descr="ELS laser fault indication" access="RO" offset="0x18.31" size="0x0.1" />
	<field name="laser2_bias_lo_war" descr="ELS laser bias low warning" access="RO" offset="0x20.0" size="0x0.1" />
	<field name="laser_bias_lo_war" descr="ELS laser bias low warning" access="RO" offset="0x20.1" size="0x0.1" />
	<field name="laser2_bias_hi_war" descr="ELS laser bias high warning" access="RO" offset="0x20.2" size="0x0.1" />
	<field name="laser_bias_hi_war" descr="ELS laser bias high warning" access="RO" offset="0x20.3" size="0x0.1" />
	<field name="laser2_bias_lo_al" descr="ELS laser bias low alarm" access="RO" offset="0x20.4" size="0x0.1" />
	<field name="laser_bias_lo_al" descr="ELS laser bias low alarm" access="RO" offset="0x20.5" size="0x0.1" />
	<field name="laser2_bias_hi_al" descr="ELS laser bias high alarm" access="RO" offset="0x20.6" size="0x0.1" />
	<field name="laser_bias_hi_al" descr="ELS laser bias high alarm" access="RO" offset="0x20.7" size="0x0.1" />
	<field name="laser_source_flag_in_use" descr="Bitmask per flag type in ELS module.\;When bit is set, indicates that FW reads flag from module.\;In order to get reliable latched flag information for that flag, it&apos;s recommended to set event for module flags via trap.\;Bit 0: global_alarm_for_laser\;Bit 1: global_warning_for_laser\;Bit 2: laser_bias_hi_al_cap \;Bit 3: laser_bias_lo_al_cap\;Bit 4: laser_bias_hi_war_cap\;Bit 5: laser_bias_lo_war_cap\;Bit 6: laser_opt_pwr_hi_al_cap\;Bit 7: laser_opt_pwr_lo_al_cap\;Bit 8: laser_opt_pwr_hi_war_cap\;Bit 9: laser_opt_pwr_lo_war_cap\;Bit 10: laser_temp_hi_al\;Bit 11: laser_temp_lo_al\;Bit 12: laser_temp_hi_war\;Bit 13: laser_temp_lo_war\;Bit 14: global_alarm_for_laser2\;Bit 15: global_warning_for_laser2\;Bit 16: laser2_bias_hi_al_cap \;Bit 17: laser2_bias_lo_al_cap\;Bit 18: laser2_bias_hi_war_cap\;Bit 19: laser2_bias_lo_war_cap\;Bit 20: laser2_opt_pwr_hi_al_cap\;Bit 21: laser2_opt_pwr_lo_al_cap\;Bit 22: laser2_opt_pwr_hi_war_cap\;Bit 23: laser2_opt_pwr_lo_war_cap" access="RO" enum="global_alarm_for_laser=0x1,global_warning_for_laser=0x2,laser_bias_hi_al_cap=0x4,laser_bias_lo_al_cap=0x8,laser_bias_hi_war_cap=0x10,laser_bias_lo_war_cap=0x20,laser_opt_pwr_hi_al_cap=0x40,laser_opt_pwr_lo_al_cap=0x80,laser_opt_pwr_hi_war_cap=0x100,laser_opt_pwr_lo_war_cap=0x200,laser_temp_hi_al=0x400,laser_temp_lo_al=0x800,laser_temp_hi_war=0x1000,laser_temp_lo_war=0x2000,global_alarm_for_laser2=0x4000,global_warning_for_laser2=0x8000,laser2_bias_hi_al_cap=0x10000,laser2_bias_lo_al_cap=0x20000,laser2_bias_hi_war_cap=0x40000,laser2_bias_lo_war_cap=0x80000,laser2_opt_pwr_hi_al_cap=0x100000,laser2_opt_pwr_lo_al_cap=0x200000,laser2_opt_pwr_hi_war_cap=0x400000,laser2_opt_pwr_lo_war_cap=0x800000" offset="0x20.8" size="0x0.24" />
	<field name="optical_engine_flag_in_use" descr="Bitmask per flag type in Optical engine module.\;When bit is set, indicates that FW reads flag from module.\;In order to get reliable latched flag information for that flag, it&apos;s recommended to set event for module flags via trap.\;Bit 0: els_input_power_hi_al\;Bit 1: els_input_power_lo_al\;Bit 2: els_input_power_hi_war\;Bit 3: els_input_power_lo_war\;Bit 4: lane_temp_hi_al\;Bit 5: lane_temp_lo_al\;Bit 6: lane_temp_hi_war\;Bit 7: lane_temp_lo_war" access="RO" enum="els_input_power_hi_al=0x1,els_input_power_lo_al=0x2,els_input_power_hi_war=0x4,els_input_power_lo_war=0x8,lane_temp_hi_al=0x10,lane_temp_lo_al=0x20,lane_temp_hi_war=0x40,lane_temp_lo_war=0x80" offset="0x24.0" size="0x0.16" />
	<field name="laser2_temp_lo_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser temperature low warning" access="RO" offset="0x24.16" size="0x0.1" />
	<field name="laser_temp_lo_war" descr="ELS laser temperature low warning" access="RO" offset="0x24.17" size="0x0.1" />
	<field name="laser2_temp_hi_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser temperature high warning" access="RO" offset="0x24.18" size="0x0.1" />
	<field name="laser_temp_hi_war" descr="ELS laser temperature high warning" access="RO" offset="0x24.19" size="0x0.1" />
	<field name="laser2_temp_lo_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser temperature low alarm" access="RO" offset="0x24.20" size="0x0.1" />
	<field name="laser_temp_lo_al" descr="ELS laser temperature low alarm" access="RO" offset="0x24.21" size="0x0.1" />
	<field name="laser2_temp_hi_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser temperature high alarm" access="RO" offset="0x24.22" size="0x0.1" />
	<field name="laser_temp_hi_al" descr="ELS laser temperature high alarm" access="RO" offset="0x24.23" size="0x0.1" />
	<field name="laser2_opt_pwr_lo_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser optical power low warning" access="RO" offset="0x24.24" size="0x0.1" />
	<field name="laser_opt_pwr_lo_war" descr="ELS laser optical power low warning" access="RO" offset="0x24.25" size="0x0.1" />
	<field name="laser2_opt_pwr_hi_war" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser optical power high warning" access="RO" offset="0x24.26" size="0x0.1" />
	<field name="laser_opt_pwr_hi_war" descr="ELS laser optical power high warning" access="RO" offset="0x24.27" size="0x0.1" />
	<field name="laser2_opt_pwr_lo_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser optical power low alarm" access="RO" offset="0x24.28" size="0x0.1" />
	<field name="laser_opt_pwr_lo_al" descr="ELS laser optical power low alarm" access="RO" offset="0x24.29" size="0x0.1" />
	<field name="laser2_opt_pwr_hi_al" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. ELS laser optical power high alarm" access="RO" offset="0x24.30" size="0x0.1" />
	<field name="laser_opt_pwr_hi_al" descr="ELS laser optical power high alarm" access="RO" offset="0x24.31" size="0x0.1" />
	<field name="els_input_power_lo_war" descr="Bitmask for latched ELS input power low warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x28.0" size="0x0.8" />
	<field name="els_input_power_hi_war" descr="Bitmask for latched ELS input power high warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x28.8" size="0x0.8" />
	<field name="els_input_power_lo_al" descr="Bitmask for latched ELS input power low alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x28.16" size="0x0.8" />
	<field name="els_input_power_hi_al" descr="Bitmask for latched ELS input power high alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x28.24" size="0x0.8" />
	<field name="lane_temp_lo_war" descr="Bitmask for latched OE lane temperature low warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x2C.0" size="0x0.8" />
	<field name="lane_temp_hi_war" descr="Bitmask for latched OE lane temperature high warning flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x2C.8" size="0x0.8" />
	<field name="lane_temp_lo_al" descr="Bitmask for latched OE lane temperature low alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x2C.16" size="0x0.8" />
	<field name="lane_temp_hi_al" descr="Bitmask for latched OE lane temperature high alarm flag per lane.\;Bit 0 - lane 0... Bit 7 - lane 7" access="RO" offset="0x2C.24" size="0x0.8" />
</node>

<node name="mofde_ext" descr="" size="0x4.0" >
	<field name="status" descr="Status of Flash Erasing:\;0: No data to erase\;1: Flash Storage is erased (after this status is returned, status will be changed to 0).\;2: Erase in progress.\;7: Fail to erase - Iron cannot access flash." access="RO" offset="0x0.0" size="0x0.3" />
	<field name="erase_log" descr="Erase Logged dump from flash.\;0: do nothing - shouldn&apos;t happen, FW will return BAT_STATUS\;1: erase dump from flash" access="OP" offset="0x0.28" size="0x0.4" />
</node>

<node name="mofpc_ext" descr="" size="0xc.0" >
	<field name="profile" descr="Flow Estimator profile index\;range 0 - cap_max_flow_estimator_profile - 1" access="INDEX" offset="0x0.0" size="0x0.3" />
	<field name="log_num_of_bins" descr="Number of bins for flow estimator must be power of 2.\;Number of bins = 2^log_num_of_bins\;Range 0 - cap_max_flow_estimator_bins_log\;Default value is 0." access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="mofph_ext" descr="" size="0x20.0" >
	<field name="type" descr="Hash type\;0: CRC - (default)\;1: XOR_HASH\;2: Random" access="RW" enum="CRC=0x0,XOR_HASH=0x1,Random=0x2" offset="0x0.0" size="0x0.4" />
	<field name="profile" descr="Flow Estimator Profile Index\;Range 0 - cap_max_flow_estimator_profile - 1" access="INDEX" offset="0x0.8" size="0x0.3" />
	<field name="seed_by_sw" descr="8 bit of seed for hash function.\;Reserved when seed_en is disabled or by HW." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="seed_en" descr="0: Disabled\;1: Seed_by_HW\;2: Seed_by_SW\;" access="RW" enum="Disabled=0x0,Seed_by_HW=0x1,Seed_by_SW=0x2" offset="0x4.30" size="0x0.2" />
	<field name="outer_header_enables" descr="Outer header enables. Each bit enables a specific layer field to be included in the hash calculation. Layers that are not listed below are enabled by default.\;Bit 0: Enable IPv4 fields if packet is not TCP and not UDP\;Bit 1: Enable IPv4 fields if packet is either TCP or UDP\;Bit 2: Enable IPv6 fields if packet is not TCP and not UDP\;Bit 3: Enable IPv6 fields if packet is either TCP or UDP\;Bit 4: Enable TCP/UDP header fields if packet is IPv4\;Bit 5: Enable TCP/UDP header fields if packet is IPv6" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="outer_header_hash" descr="If a bit is set, the relevant field will be calculated in the hash.\;ipv4:\;0-3: ipv4 dip bytes 0-3\;4-7: ipv4 sip bytes 0-3\;8: IPv4 mask fragments - mask ipv4 fragmented packets (mask all fields after ipv4 header)\;9: ipv4 next protocol\;ipv6:\;10: ipv6 dip bytes 0-7 (one bit for all 8 bytes)\;11-18: ipv6 dip bytes 8-15\;19: ipv6 sip bytes 0-7 (one bit for all 8 bytes)\;20-27: ipv6 sip bytes 8-15\;29: ipv6 next protocol\;L4:\;30: L4 dest port (only for UDP and TCP)\;31: L4 source port (only for UDP and TCP)\;mpls:\;33: mpls exp\;34-39: mpls label 0-5\;40: mask label after extension - mask the label after the indication label for the extension reserved labels (label 15)\;41: mask labels and headers after entropy - mask all the labels and headers after entropy label, note that both ELI and EL are not masked, all headers after MPLS stack are masked (e.g ip header)\;42: if mpls, mask all the headers after mpls header\;43: mask reserved labels - supports up to 256 reserved labels. not mask ELs (entropy labels)\;general:\;44: arp dip\;45: arp sip\;46: bth_dest_qp\;47: mask after flex (mask all the headers after flex)\;48: grh dip\;49: grh next protocol\;50: grh sip\;51: if packet is vxlan/geneve/gpe, mask all next headers after UDP\;52: if packet is vxlan/geneve/gpe, mask all header after vxlan/geneve/gpe\;53: ingress port\;54: if packet is nvgre - mask all next headers after nvgre" subnode="uint64" access="RW" offset="0x10.0" size="0x8.0" />
	<field name="inner_header_enables" descr="Inner header enables. Each bit enables a specific layer field to be included in the hash calculation. Layers that are not listed below are enabled by default.\;Bit 0: Enable IPv4 fields if packet is not TCP and not UDP\;Bit 1: Enable IPv4 fields if packet is either TCP or UDP\;Bit 2: Enable IPv6 fields if packet is not TCP and not UDP\;Bit 3: Enable IPv6 fields if packet is either TCP or UDP\;Bit 4: Enable TCP/UDP header fields if packet is IPv4\;Bit 5: Enable TCP/UDP header fields if packet is IPv6" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="inner_header_hash" descr="If a bit is set, the relevant field will be calculated in the hash.\;\;ipv4:\;0-3: ipv4 dip bytes 0-3 (arp dip is not supported for inner)\;4-7: ipv4 sip bytes 0-3\;8: IPv4 mask fragments - mask ipv4 fragmented packets (mask all fields after ipv4 header)\;9: ipv4 next protocol\;\;ipv6:\;10: ipv6 dip bytes 0-7 (one bit for all 8 bytes)\;11-18: ipv6 dip bytes 8-15\;19: ipv6 sip bytes 0-7 (one bit for all 8 bytes)\;20-27: ipv6 sip bytes 8-15\;28: ipv6 flow label\;29: ipv6 next protocol\;\;L4:\;30: L4 dest port (only for UDP and TCP)\;31: L4 source port (only for UDP and TCP)" access="RW" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mofrb_ext" descr="" size="0x210.0" >
	<field name="num_rec" descr="On Query: Number of records to read\;0 .. cap_max_flow_estimator_bins" access="RW" offset="0x0.0" size="0x0.11" />
	<field name="clear" descr="clear:\;0: do NOT clear the bins\;1: clear the bins" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="counter_index_base" descr="counter index of the first bin\;For Spectrum: see Section 5.2, &quot;Flow Counters&quot;, on page 1254\;Range 0 .. cap_shared_counter_pool_size - 1" access="INDEX" offset="0x4.0" size="0x0.24" />
	<field name="flow_estimator_bin" descr="Flow estimator bin value" access="RO" high_bound="511" low_bound="0" offset="0x10.24" size="0x200.0" />
</node>

<node name="mogcr_ext" descr="" size="0x20.0" >
	<field name="ptp_eftc" descr="PTP Egress FIFO Trap Clear\;The PTP_EGR_FIFO trap provides MTPPTR with clr according to this value. Default 0.\;Supported for Spectrum-1, reserved otherwise." access="RW" offset="0x0.0" size="0x0.1" />
	<field name="ptp_iftc" descr="PTP Ingress FIFO Trap Clear\;The PTP_ING_FIFO trap provides MTPPTR with clr according to this value. Default 0.\;Supported for Spectrum-1, reserved otherwise." access="RW" offset="0x0.1" size="0x0.1" />
	<field name="tele_managed" descr="Telemetry is managed:\;0: telemetery is unmanged (default for IB switches)\;1: telemetery is manged (default for Eth switches)\;When unmanaged - the events are by VS-MADs\;When managed - the events are by EMADs\;Reserved when Ethernet switches" access="RW" offset="0x0.8" size="0x0.1" />
	<field name="sid" descr="Sample ingress discards:\;0: ingress discards are not sampled\;1: ingress discards are sampled\;Reserved when Quantum switches." access="RW" offset="0x8.0" size="0x0.1" />
	<field name="mirroring_pid_base" descr="Base policer id for mirroring policers.\;Must have an even value (e.g. 1000, not 1001).\;Reserved when Spectrum-1 and Quantum-1/-2." access="RW" offset="0xC.0" size="0x0.14" />
	<field name="mirror_latency_units" descr="Units of mirror header latency\;Units of nSec\;For Spectrum-2/3: values are 1,2,4..32768nSec\;Default 64nSec\;See Table 1013, &quot;ERSPAN Mirror Header TLV LATENCY Frame Layout,&quot; on page 1303\;Reserved when Spectrum-1." access="RW" offset="0x14.0" size="0x0.16" />
	<field name="latency_histogram_units" descr="Units of latency histograms\;Units of nSec\;For Spectrum-2/3: values are 1,2,4..32768nSec\;Default 64nSec\;See Section 10.6.4.1, &quot;Latency Histograms&quot;, on page 2719\;Reserved when Spectrum\;" access="RW" offset="0x18.0" size="0x0.16" />
	<field name="toc_fmt" descr="Timestamp over CRC format:\;0: Free_Running_Clock - Default\;1: UTC\;Reserved when local_toc_fmt=1.\;This configuration is used by PCMR to configure ToC per local port.\;Reserved when Spectrum-1." access="RW" enum="Free_Running_Clock=0x0,UTC=0x1" offset="0x1C.24" size="0x0.1" />
	<field name="local_toc_fmt" descr="0: GLOBAL - toc_fmt dictates timestamp over CRC globally.\;1: LOCAL - toc_fmt sets the timestamp over CRC default value. PFCR can set ToC format individually. (See Section 9.20.20, &quot;PFCR - Ports FCS Configuration Register&quot;, on page 2654)\;Reserved when Spectrum-1." access="RW" offset="0x1C.25" size="0x0.1" />
</node>

<node name="molp_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local Port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="label_port" descr="Label on the front panel.\;Used for mirror header and for EMT (Egress Modifier Template)." access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="momte_ext" descr="" size="0x10.0" >
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR\;1: LNM - local network manager\;Reserved when Spectrum/-2" access="OP" enum="HYPERVISOR=0x0,LNM=0x1" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="If (mngr_type == &quot;Hypervisor&quot;)\;Unique port identifier for the final destination of the packet\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from which the command came from is InfiniBand: \;ib port number\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from which the command came from is Ethernet: \;Local Port\;\;For Quantum:\;- Supported to/from Aggregation Node\;- Not supported to/from IB Router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="Switch Partition ID\;Reserved when mngr_type = LNM\;Reserved when Ethernet switches" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="type" descr="See Section 5.4.1, &quot;Mirror Triggers&quot;, on page 1269\;Type:\;0x20: WRED_egress - no CPU port\;0x31: SHARED_BUFFER_TClass - egress\;0x32: Shared_buffer_TClass_descriptors - egress [advanced]\;0x33: SHARED_BUFFER_Egress_Port - egress\;0x40: ING_CONG - ingress\;0x50: EGR_CONG - egress\;0x60: ECN - egress, no CPU port\;0x70: HIGH_LATENCY - egress, no CPU port" access="INDEX" enum="WRED_egress=0x20,SHARED_BUFFER_TClass=0x31,Shared_buffer_TClass_descriptors=0x32,SHARED_BUFFER_Egress_Port=0x33,ING_CONG=0x40,EGR_CONG=0x50,ECN=0x60,HIGH_LATENCY=0x70" offset="0x4.0" size="0x0.8" />
	<field name="tclass_en_high" descr="TClass/PG mirror enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;When type = 0x33: only bit0 is used, representing the port\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tclass_en_low" descr="TClass/PG mirror enable (for IB switches this is VL enable)\;Each bit represents corresponding tclass\;0: disable (default)\;1: enable\;When type = 0x33: only bit0 is used, representing the port\;Valid bits for Ethernet devices: 0.. cap_max_tclass_data - 1" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="moni_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="en" descr="Enable monitoring on network interface:\;0: disable (default)\;1: enable" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="motbt_ext" descr="" size="0x10.0" >
	<field name="tx_group" descr="Trimming Tx group\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="bts_per_tclass_mask" descr="Write enable for the BTS/T&amp;F per Traffic Class.\;Bit index corresponds to an original Traffic Class.\;Reserved on Qurey." access="WO" offset="0x8.0" size="0x0.16" />
	<field name="bts_per_tclass" descr="BTS or T&amp;F.\;Bitmap - bit index corresponds to an original Traffic Class.\;0: FWD - Trim and Forward\;1: BTS - Back to Sender" access="RW" enum="FWD=0x0,BTS=0x1" offset="0xC.0" size="0x0.16" />
</node>

<node name="motcb_ext" descr="" size="0x14.0" >
	<field name="base_counter_index" descr="Base counter index for flow counters." access="RW" offset="0x10.0" size="0x0.24" />
	<field name="counter_set_type" descr="Trimming counter set type.\;See Section 5.2.2.3, &quot;Trimming Counter Set Types&quot;, on page 1258.\;0x0: NO_COUNT - Don&apos;t count\;0xE: TX_TC_COUNT - Count per {Tx port, original Traffic Class}\;0xF: RX_COUNT - Count per Rx port\;\;Other values are reserved." access="RW" enum="NO_COUNT=0x0,TX_TC_COUNT=0xe,RX_COUNT=0xf" offset="0x10.24" size="0x0.8" />
</node>

<node name="motpr_ext" descr="" size="0x20.0" >
	<field name="profile" descr="Trimming profile index." access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="type" descr="Profile Type.\;0: FWD - Default\;1: BTS - Supported from Spectrum-6" access="RW" enum="FWD=0x0,BTS=0x1" offset="0x4.0" size="0x0.2" />
	<field name="pcp_rw" descr="Rewrite PCP and DEI according to the Switch Prio set by the agent.\;0: PRESERVE - preserves pcp_rewrite_en\;2: CLEAR - clears pcp_rewrite_en\;3: SET - sets pcp_rewrite_en\;\;Supported from Spectrum-5 onwards." access="RW" enum="PRESERVE=0x0,CLEAR=0x2,SET=0x3" offset="0x10.0" size="0x0.2" />
	<field name="dscp_rw" descr="Rewrite DSCP according to the Switch Prio set by the agent.\;0: PRESERVE - preserves dscp_rewrite_en\;2: CLEAR - clears dscp_rewrite_en\;3: SET - sets dscp_rewrite_en\;\;Supported from Spectrum-5 onwards." access="RW" enum="PRESERVE=0x0,CLEAR=0x2,SET=0x3" offset="0x10.8" size="0x0.2" />
	<field name="dscp" descr="The DSCP value to overwrite with.\;\;Supported from Spectrum-5 onwards." access="RW" offset="0x10.16" size="0x0.6" />
	<field name="overwrite_dscp" descr="Whether to overwrite DSCP with dscp provided by the trimming agent.\;Note: Can be overridden by dscp_rewrite_en if set.\;\;Supported from Spectrum-5 onwards." access="RW" offset="0x10.23" size="0x0.1" />
	<field name="bts_keep_mac" descr="Whether to keep original DMAC and SMAC in BTS. By default the DMAC and SMAC are swapped.\;\;Supported in Spectrum-6 onwards.\;Reserved when type   BTS." access="RW" offset="0x14.0" size="0x0.1" />
	<field name="bts_keep_udp" descr="Whether to keep original UDP dport and sport in BTS. By default the UDP dport and sport are swapped.\;\;Supported in Spectrum-6 onwards.\;Reserved when type   BTS." access="RW" offset="0x14.2" size="0x0.1" />
	<field name="emt_index" descr="Egress Modifier Template binding 0.\;EMT index.\;Range: 0 .. cap_max_emts - 1.\;See FMTC, FMTE.\;\;Supported from Spectrum-5 onwards.\;Reserved when emt_bind = NOP." access="RW" offset="0x18.0" size="0x0.8" />
	<field name="emt_bind" descr="Egress Modifier Template binding 0.\;Bind an EMT:\;0: NOP - no bind\;1: PUSH - bind as push\;2: EDIT - bind as edit\;4: POP - bind as pop\;\;Supported from Spectrum-5 onwards.\;Reserved when trim=0." access="RW" enum="NOP=0x0,PUSH=0x1,EDIT=0x2,POP=0x4" offset="0x18.8" size="0x0.4" />
	<field name="modifier_base" descr="Egress Modifier Template binding 0.\;Modifier Base Label.\;\;Push/Edit/Pop will be applied in the beginning of the following selected field of encapsulated header:\;Note: Pop is allowed only with SOP (0).\;\;0: SOP (start of packet)\;1: New MAC header\;2: New ETHERTYPE \;3: New IPv4/IPv6 header\;4: New MPLS \;5: New VxLAN/Geneve/VxLAN-GPE/NVGRE \;6: New GRE header\;7: New UDP header\;8: New Flex Encap \;9: New Inner MAC header \;\;11: New Inner ETHER Type \;\;Supported from Spectrum-5 onwards.\;Reserved when emt_bind = NOP." access="RW" offset="0x18.16" size="0x0.4" />
	<field name="modifier_offset" descr="Egress Modifier Template binding 0.\;\;Offset on top of modifier_base.\;0: ZERO - zero offset\;1: CBSET_0 - offset is custom_bytes[1:0]\;2: CBSET_1 - offset is custom_bytes[3:2]\;\;Supported from Spectrum-5 onwards.\;Reserved when emt_bind = NOP." access="RW" enum="ZERO=0x0,CBSET_0=0x1,CBSET_1=0x2" offset="0x18.24" size="0x0.2" />
</node>

<node name="motrm_reg_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number (Rx ports)\;Not supported from CPU port\;Not supported from router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="en_nvl" descr="For NVLink packets:\;Enable trigger mirror according to NVLink LRH.Trig field\;0: Disable mirror trigger \;1: Enable mirror trigger" access="RW" offset="0x8.0" size="0x0.1" />
	<field name="en_ing2" descr="For IBg2 packets:\;Enable trigger mirror according to IP.DSCP[0] field\;0: Disable mirror trigger \;1: Enable mirror trigger" access="RW" offset="0x8.1" size="0x0.1" />
</node>

<node name="motspt_ext" descr="" size="0x8.0" >
	<field name="switch_prio" descr="Original Switch Priority.\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="trim_switch_prio" descr="Trimming Switch Priority.\;Default value is 0." access="RW" offset="0x4.0" size="0x0.4" />
	<field name="trim_tclass" descr="Trimming Traffic Class.\;Default value is 0." access="RW" offset="0x4.16" size="0x0.5" />
</node>

<node name="mottg_ext" descr="" size="0x218.0" >
	<field name="map" descr="Mapping per local port.\;See Table 1179, &quot;MOTTG - Tx Group Map Layout,&quot; on page 1310.\;\;CPU port is not supported." access="RW" high_bound="519" low_bound="0" offset="0x10.24" size="0x208.0" />
</node>

<node name="mpagr_ext" descr="" size="0xc.0" >
	<field name="trigger" descr="Mirror trigger \;See Table 972, &quot;Mirror Triggers,&quot; on page 1269\;Reserved when the mirror binding is not Global" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR - config all ports\;1: LNM - local network manager - config all ports of the SWID\;Reserved when Ethernet switches" access="OP" enum="HYPERVISOR=0x0,LNM=0x1" offset="0x0.8" size="0x0.4" />
	<field name="swid" descr="Switch Partition ID\;Reserved when mngr_type = LNM\;Reserved when Ethernet switches" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="pa_id" descr="Port analyzer ID" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="enable" descr="Enable mirroring \;By default, port mirroring is disabled for all ports.\;Reserved when Quantum and Spectrum-2." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="probability_rate" descr="Sampling rate = 1 out of rate packets.\;Value of 1 means &quot;sample all&quot;.\;The value 0 behaves like 1.\;Default 1\;Note: high values are round up by HW to: {   (232-1)/n    | n      } ({232-1, 231-1, 1431655765, ...})." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mpar_ext" descr="" size="0xc.0" >
	<field name="i_e" descr="Ingress/egress.\;See Table 972, &quot;Mirror Triggers,&quot; on page 1269.\;Reserved when the mirror binding is not per Rx or per Tx." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="local_port" descr="When Ethernet: always Local Port\;\;When IB:\;If (mngr_type == &quot;Hypervisor&quot;):\;Unique port identifier\;If (mngr_type == &quot;Local Network Manager&quot;):\;ib port number\;\;For Spectrum family:\;- Supported from CPU port\;For Quantum/-2:\;- Supported to/from CPU port\;- Supported to/from Aggregation Node\;- Not supported to/from IB Router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR\;1: LNM - local network manager\;Reserved for Spectrum family." access="OP" enum="HYPERVISOR=0x0,LNM=0x1" offset="0x0.24" size="0x0.4" />
	<field name="pa_id" descr="Port Analyzer ID (a.k.a mirror-agent)\;Reserved when enable=0" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="enable" descr="Enable mirroring \;By default, port mirroring is disabled for all ports." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="probability_rate" descr="Sampling rate = 1 out of rate packets.\;The value 0 behaves like 1.\;Default is 1.\;Note: high values are round up by HW to: {   (232-1)/n    | n      } ({232-1, 231-1, 1431655765, ...}). \;Reserved when Spectrum-1.\;Supported for Quantum and Spectrum-2 and on." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mpat_encap_localib_ext" descr="" size="0x10.0" >
	<field name="vl" descr="Virtual Lane on which the mirrored packet is queued.\;Mirrored packets cannot be queued on VL-15" access="RW" offset="0xC.0" size="0x0.4" />
</node>

<node name="mpat_encap_remoteib_ext" descr="" size="0x4c.0" >
	<field name="dlid" descr="Destination LID. \;Note that the analyzer port is configured by the system_port field and not by forwarding the packet based on the dlid field." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. When set to dynamic mode, the analyzer port is set based on the forwarding information for the {swid, dlid} on private-LFT 0 instead of the system_port field. In static mode, the packet is transmitted to the configured system_port regardless of the forwarding database.\;0: static analyzer port\;1: dynamic analyzer port" access="RW" offset="0x0.16" size="0x0.2" />
	<field name="sl" descr="Service Level" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="we" descr="Write enable:\;0: write all fields\;1: write only psn_init_val" access="WO" offset="0x0.24" size="0x0.8" />
	<field name="slid" descr="Source LID (LID of the sending device)" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="version" descr="Remote SPAN InfiniBand encapsulation header version\;1: V1 - Mirror Header Version 1\;2: V2 - Mirror Header Version 2\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the analyzer port based on the desired forwarding table (the one that belong to the swid)." access="RW" offset="0x4.24" size="0x0.8" />
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
	<field name="psn_init_val" descr="BTH packet sequence number initial value\;Note: when reading, HW will reveal the current packet sequence number" access="RW" offset="0x40.0" size="0x0.24" />
	<field name="ar" descr="BTH MLNX adaptive routing enable flag" access="RW" offset="0x40.30" size="0x0.1" />
	<field name="qkey" descr="DETH QKey" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="src_qp" descr="DETH source QP" access="RW" offset="0x48.0" size="0x0.24" />
</node>

<node name="mpat_encap_rmtethl2_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="Destination MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. \;When set to dynamic mode, the analyzer port is set based on the forwarding information for the {mac, vid} combination and not based on the system_port field. In static mode, the packet is transmitted to the configured system_port regardless of the forwarding database. Note that in Dynamic mode, if the switch FDB does not hold a filtering entry for the {mac, vid}, the mirroring copy is not flooded - it is discarded.\;0: STATIC_ANALYZER - static analyzer port\;1: DYNAMIC_ANALYZER - dynamic analyzer port\;Reserved when ubridge=1" access="RW" enum="STATIC_ANALYZER=0x0,DYNAMIC_ANALYZER=0x1" offset="0x0.16" size="0x0.2" />
	<field name="version" descr="ERSPAN mirror header version.\;0: V0 - Mirror Header Version 0.\;1: V1 - Mirror Header Version 1.\;2: V2 - Mirror Header Version 2. Reserved when Spectrum-1.\;15: NO_HEADER - No Mirror header" access="RW" enum="V0=0x0,V1=0x1,V2=0x2,NO_HEADER=0xf" offset="0x0.18" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the Analyzer port based on the desired forwarding table (the one that belong to the swid).\;Reserved when Spectrum/-2" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="mac_31_0" descr="Destination MAC address" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="vid" descr="When dpa = 0: Encapsulation header VLAN ID\;When dpa = 1 and fid &lt; 4K (fid_msb = 0) then: VLAN ID\;When dpa = 1 and fid &gt;=4K (fid_msb != 0) then: FID lsb" access="RW" offset="0x8.0" size="0x0.12" />
	<field name="dei" descr="Encapsulation header DEI. \;Reserved when qos is QoS maintain\;Reserved when tp = 0" access="RW" offset="0x8.12" size="0x0.1" />
	<field name="pcp" descr="Encapsulation header PCP. \;Reserved when qos is QoS maintain\;Reserved when tp = 0" access="RW" offset="0x8.13" size="0x0.3" />
	<field name="tp" descr="Tag Packet. Indicates the mirroring header should be VLAN tagged.\;0: Mirror packet is un-tagged\;1: Mirror packet is tagged" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="tclass" descr="Traffic Class\;For Spectrum switches: Switch Priority\;Reserved when qos is QoS maintain\;Reserved when imp=1" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="vlan_et_id" descr="Encapsulation header VLAN Ethertype ID\;Default is &apos;0&apos;\;Ethertype IDs are configured by SVER, see Section 7.12.39, &quot;SVER - Switch VLAN EtherType Register&quot;, on page 1843" access="RW" offset="0xC.16" size="0x0.2" />
	<field name="fid_msb" descr="FID msb\;Reserved when dpa=0" access="RW" offset="0xC.24" size="0x0.4" />
</node>

<node name="mpat_encap_rmtethl3gre_ext" descr="" size="0x50.0" >
	<field name="mac_47_32" descr="Destination MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. \;When set to dynamic mode, the analyzer port is set based on the forwarding information for the {mac, vid} combination and not based on the system_port field. In static mode, the packet is transmitted to the configured system_port regardless of the forwarding database. Note that in Dynamic mode, if the switch FDB does not hold a filtering entry for the {mac, vid}, the mirroring copy is not flooded - it is discarded.\;0: STATIC_ANALYZER - static analyzer port\;1: DYNAMIC_ANALYZER - dynamic analyzer port\;Reserved when ubridge=1" access="RW" enum="STATIC_ANALYZER=0x0,DYNAMIC_ANALYZER=0x1" offset="0x0.16" size="0x0.2" />
	<field name="version" descr="ERSPAN mirror header version.\;\;1: V1 - Mirror Header Version 1.\;2: V2 - Mirror Header Version 2. Reserved when Spectrum-1.\;15: NO_HEADER - No Mirror header" access="RW" enum="V1=0x1,V2=0x2,NO_HEADER=0xf" offset="0x0.18" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the Analyzer port based on the desired forwarding table (the one that belong to the swid).\;Reserved when Spectrum/-2" access="RW" offset="0x0.24" size="0x0.8" />
	<field name="mac_31_0" descr="Destination MAC address" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="vid" descr="When dpa = 0: Encapsulation header VLAN ID\;When dpa = 1 and fid &lt; 4K (fid_msb = 0) then: VLAN ID\;When dpa = 1 and fid &gt;=4K (fid_msb != 0) then: FID lsb" access="RW" offset="0x8.0" size="0x0.12" />
	<field name="dei" descr="Encapsulation header DEI. \;Reserved when qos is QoS maintain\;Reserved when tp = 0" access="RW" offset="0x8.12" size="0x0.1" />
	<field name="pcp" descr="Encapsulation header PCP. \;Reserved when qos is QoS maintain\;Reserved when tp = 0" access="RW" offset="0x8.13" size="0x0.3" />
	<field name="tp" descr="Tag Packet. Indicates the mirroring header should be VLAN tagged.\;0: Mirror packet is un-tagged\;1: Mirror packet is tagged" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="dscp" descr="Encapsulation header DSCP\;Reserved when qos is QoS maintain" access="RW" offset="0x8.18" size="0x0.6" />
	<field name="protocol" descr="0: IPV4\;1: IPV6" access="RW" enum="IPV4=0x0,IPV6=0x1" offset="0x8.24" size="0x0.4" />
	<field name="tclass" descr="Traffic Class\;For Spectrum switches: Switch Priority\;Reserved when qos is QoS maintain\;Reserved when imp=1" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="ttl" descr="Encapsulation header Time-to-Live/HopLimit" access="RW" offset="0xC.4" size="0x0.8" />
	<field name="ecn" descr="Encapsulation header ECN" access="RW" offset="0xC.12" size="0x0.2" />
	<field name="vlan_et_id" descr="Encapsulation header VLAN Ethertype ID\;Default is &apos;0&apos;\;Ethertype IDs are configured by SVER, see Section 7.12.39, &quot;SVER - Switch VLAN EtherType Register&quot;, on page 1843" access="RW" offset="0xC.16" size="0x0.2" />
	<field name="fid_msb" descr="FID msb\;Reserved when dpa=0" access="RW" offset="0xC.24" size="0x0.4" />
	<field name="smac_47_32" descr="Source MAC address" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="smac_31_0" descr="Source MAC address" access="RW" offset="0x14.0" size="0x4.0" />
	<field name="dip" descr="Destination IP address\;The IP version is configured by protocol\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="RW" high_bound="3" low_bound="0" offset="0x30.0" size="0x10.0" />
	<field name="sip" descr="Source IP address\;The IP version is configured by protocol\;IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved." access="RW" high_bound="3" low_bound="0" offset="0x40.0" size="0x10.0" />
</node>

<node name="mpat_encap_rmtethvlan_ext" descr="" size="0x10.0" >
	<field name="vid" descr="Encapsulation header VLAN ID" access="RW" offset="0x8.0" size="0x0.12" />
	<field name="dei" descr="Encapsulation header DEI\;Reserved when qos is QoS maintain" access="RW" offset="0x8.12" size="0x0.1" />
	<field name="pcp" descr="Encapsulation header PCP\;Reserved when qos is QoS maintain" access="RW" offset="0x8.13" size="0x0.3" />
	<field name="tclass" descr="Traffic Class.\;For Spectrum switches: Switch Priority\;Reserved when qos is QoS maintain\;Reserved when imp=1" access="RW" offset="0xC.0" size="0x0.4" />
	<field name="vlan_et_id" descr="Encapsulation header VLAN Ethertype ID\;Default is &apos;0&apos;\;Ethertype IDs are configured by SVER, see Section 7.12.39, &quot;SVER - Switch VLAN EtherType Register&quot;, on page 1843" access="RW" offset="0xC.16" size="0x0.2" />
</node>

<node name="mpat_reg_encapsulation_auto_ext" descr="" attr_is_union="1" size="0x50.0" >
	<field name="local_span_ext" descr="" subnode="local_span_ext" offset="0x0.0" selected_by="LOCAL_ETH" size="0x10.0" />
	<field name="mpat_encap_localib_ext" descr="" subnode="mpat_encap_localib_ext" offset="0x0.0" selected_by="LOCAL_IB" size="0x10.0" />
	<field name="mpat_encap_remoteib_ext" descr="" subnode="mpat_encap_remoteib_ext" offset="0x0.0" selected_by="REMOTE_IB_GLOBAL_UD" size="0x4c.0" />
	<field name="mpat_encap_rmtethl2_ext" descr="" subnode="mpat_encap_rmtethl2_ext" offset="0x0.0" selected_by="REMOTE_ETH_L2" size="0x10.0" />
	<field name="mpat_encap_rmtethl3gre_ext" descr="" subnode="mpat_encap_rmtethl3gre_ext" offset="0x0.0" selected_by="REMOTE_ETH_L3" size="0x50.0" />
	<field name="mpat_encap_rmtethvlan_ext" descr="" subnode="mpat_encap_rmtethvlan_ext" offset="0x0.0" selected_by="REMOTE_ETH" size="0x10.0" />
	<field name="remote_span_ib_local_ud_ext" descr="" subnode="remote_span_ib_local_ud_ext" offset="0x0.0" selected_by="REMOTE_IB_LOCAL_UD" size="0x4c.0" />
</node>

<node name="mpat_reg_ext" descr="" size="0x9c.0" >
	<field name="system_port" descr="If (mngr_type == &quot;Hypervisor&quot;)\;Unique port identifier for the final destination of the packet\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from which the command came from is InfiniBand: \;ib port number\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from which the command came from is Ethernet: \;Local Port\;For Spectrum-1: CPU port is not supported\;For Quantum/-2: CPU port is supported\;From Spectrum-2: CPU port is supported\;Note: when CPU port:\;1. span_type must be LOCAL_ETH or LOCAL_IB\;2. tr is reserved (no truncation)\;Reserved when dpa = 1\;Reserved when imp=1" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="mngr_type" descr="Manager Type\;0: HYPERVISOR\;1: LOCAL_NETWORK_MANAGER\;For more details regarding Manager Type, refer to Section 2.14, &quot;Management Security Hierarchy&quot;, on page 610." access="OP" enum="HYPERVISOR=0x0,LOCAL_NETWORK_MANAGER=0x1" offset="0x0.16" size="0x0.4" />
	<field name="session_id" descr="Mirror Session ID.\;Used for MIRROR_SESSION&lt;i&gt; trap.\;Reserved when Spectrum-1." access="RW" offset="0x0.24" size="0x0.4" />
	<field name="pa_id" descr="Port Analyzer ID (a.k.a mirror-agent)\;Range 0 .. cap_max_span_analyzers - 1.\;[DWIP] When trim=1, only pa_id=0 is supported." access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="span_type" descr="See Table 1146, &quot;Span Types,&quot; on page 1282\;0x0: LOCAL_ETH\;0x1: REMOTE_ETH\;0x2: REMOTE_ETH_L2\;0x3: REMOTE_ETH_L3\;0x4: LOCAL_IB\;0xA: REMOTE_IB_LOCAL_UD\;0xB: REMOTE_IB_GLOBAL_UD" access="RW" enum="LOCAL_ETH=0x0,REMOTE_ETH=0x1,REMOTE_ETH_L2=0x2,REMOTE_ETH_L3=0x3,LOCAL_IB=0x4,REMOTE_IB_LOCAL_UD=0xa,REMOTE_IB_GLOBAL_UD=0xb" offset="0x4.0" size="0x0.4" />
	<field name="trim" descr="[DWIP]\;Trimming agent enable.\;When enabled, the agent is used for trimming only. Agent can&apos;t be used for mirroring at any trigger point.\;Supported only with INGRESS_SHARED_BUFFER trigger.\;\;Supported from Spectrum-5 onwards.\;Supported for pa_id=0 only." access="RW" offset="0x4.4" size="0x0.1" />
	<field name="imp" descr="Is Multi Port:\;0: Mirror only to one port - according to system_port description\;1: Mirror to one of the multi_ports, see nmp description\;\;If nmp != 0, the decision to which port to mirror will be according to multi_port[ingress_port_lag_hash[1:0]]" access="OP" offset="0x4.16" size="0x0.1" />
	<field name="nmp" descr="Number of Multi Port:\;0: mirror to single port, multi_port[0]\;1: mirror to one of 2 ports, multi_port[0] and multi_port[1]\;2: mirror to one of 4 ports, multi_port[0] - multi_port[3]\;Reserved when imp = 0." access="OP" offset="0x4.17" size="0x0.2" />
	<field name="tr" descr="Truncate. Indicates all packets mirrored to this Analyzer port will be truncated.\;Truncation size is defined by truncation_size\;For Spectrum, packets from CPU to a truncation-enabled agent will not be mirrored. \;For Spectrum-2, packets from CPU to a truncation-enabled agent will be mirrored\;Reserved when system_port is to CPU\;Reserved when MPAT.itc = 1" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="be" descr="Best Effort. Indicates mirroring traffic should not cause packet drop or back pressure but will discard the mirroring packets. Mirroring packets will be forwarded in a best effort manner.\;0: NOT_DISCARD - Do not discard mirrored packets\;1: DISCARD - Discard mirrored packets if causing congestion\;Relevant both for ingress mirror and egress mirror\;\;" access="RW" enum="NOT_DISCARD=0x0,DISCARD=0x1" offset="0x4.25" size="0x0.1" />
	<field name="qos" descr="Quality of Service mode\;0: CONFIGURED - QoS parameters (Switch Priority, and encapsulation PCP, DEI, DSCP or VL) are configured\;1: MAINTAIN - QoS parameters (Switch Priority, Color) are the same as in the original packet that has triggered the mirroring. For SPAN also the pcp,dei are maintained. Reserved when Spectrum.\;For SPAN packets the PCP, DEI is as mirrored packet" access="RW" enum="CONFIGURED=0x0,MAINTAIN=0x1" offset="0x4.26" size="0x0.1" />
	<field name="c" descr="Clear counters\;Clears the buffer_drop and be_drop counters" access="OP" offset="0x4.28" size="0x0.1" />
	<field name="e" descr="Enable. Indicating the Port Analyzer is enabled\;Note: before disabling a port analyzer, software should make sure no port / rule is associated with the Port Analyzer to be disabled." access="RW" offset="0x4.31" size="0x0.1" />
	<field name="truncation_size" descr="Truncation Size.\;Sets the truncation size in case truncation is enabled. \;Unit is 1 byte.\;Granularity is 4 bytes. \;For Spectrum-1: minimum value is 32B\;For Quantum and Spectrum-2/3: minimum value is 48B\;For Spectrum-4: minimum value is 64B. \;Reserved when span_type is LOCALIB\;Reserved when MPAT.itc = 1" access="RW" offset="0x8.0" size="0x0.13" />
	<field name="switch_prio" descr="Switch Prio for the mirrored/trimmed packet.\;In mirroring:\;Reserved when imp=0.\;Reserved when qos=1 (MAINTAIN).\;Reserved for IB-switch.\;\;[DWIP] In trimming used when trim_qos=0, reserved otherwise." access="RW" offset="0x8.16" size="0x0.4" />
	<field name="tclass" descr="Traffic class of the mirrored/trimmed packet.\;Reserved when the mirror port is CPU port (it is set by HTGT.cpu_tclass).\;In mirroring:\;Reserved when imp=0\;Reserved when qos=1 (MAINTAIN).\;Reserved for IB-switch.\;\;[DWIP] In trimming used when trim_qos=0, reserved otherwise." access="RW" offset="0x8.24" size="0x0.4" />
	<field name="itc" descr="Ignore Truncation Configuration\;0: use MPAT.tr and MPAT.truncation_size to configure truncation profile.\;1: use ITPR to configure truncation profile. See Table 1373, &quot;ITPR - Infrastructure Truncation Profile Register Fields,&quot; on page 1658.\;Valid for Spectrum-4 and on." access="RW" offset="0x8.31" size="0x0.1" />
	<field name="pid" descr="Policer ID\;Range MOGCR.mirroring_pid_base .. (MOGCR.mirroring_pid_base + cap_max_span_analyzers - 1)\;See pid in QPCR, Section 12.12.6, &quot;QPCR - QoS Policer Configuration Register&quot;, on page 3379\;Note: the policer takes packet length prior to truncation. The policer must have color_aware=not, type=srDCM, violate_action=discard.\;Reserved when Spectrum-1 and Quantum/-2." access="RW" offset="0xC.0" size="0x0.14" />
	<field name="pide" descr="Policer enable\;For more details about policers, refer to Section 11.7.6, &quot;Policer&quot;, on page 3121\;Note: for mirror to CPU: MPAT.pid is enabled then the trap-group-policer will not police\;Reserved when Spectrum-1 and Quantum/-2." access="RW" offset="0xC.15" size="0x0.1" />
	<field name="encapsulation" descr="Remote SPAN encapsulation. The encapsulation information is based on the span_type field. The following tables provide a reference to the encapsulation fields for the different SPAN types: \;Table 1147, &quot;Local SPAN Layout,&quot; on page 1283.\;Table 1149, &quot;Remote SPAN Ethernet VLAN Layout,&quot; on page 1284.\;Table 1151, &quot;Encapsulated Remote SPAN Ethernet L2 Layout,&quot; on page 1285.\;Table 1153, &quot;Encapsulated Remote SPAN Ethernet L3 Layout,&quot; on page 1287.\;Table 1155, &quot;Local SPAN InfiniBand Layout,&quot; on page 1290.\;Table 1157, &quot;Remote SPAN InfiniBand Local UD Layout,&quot; on page 1291.\;Table 1159, &quot;Remote SPAN InfiniBand Global UD Layout,&quot; on page 1293." subnode="mpat_reg_encapsulation_auto_ext" access="RW" offset="0x10.0" size="0x50.0" union_selector="$(parent).span_type" />
	<field name="buffer_drop_high" descr="Counter:\;Number of packet drops on the analyzer agent due to buffer size\;Reserved when Quantum switches." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="buffer_drop_low" descr="Counter:\;Number of packet drops on the analyzer agent due to buffer size\;Reserved when Quantum switches." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="be_drop_high" descr="Counter:\;Number of packet drops on the analyzer agent due to Best Effort when be is enabled\;Reserved when Quantum switches." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="be_drop_low" descr="Counter:\;Number of packet drops on the analyzer agent due to Best Effort when be is enabled\;Reserved when Quantum switches." access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="pc" descr="Pad Count\;0: No_padding\;1: TwoBytes_padding\;\;Supported from Spectrum-4 and above." access="RW" enum="No_padding=0x0,TwoBytes_padding=0x1" offset="0x78.0" size="0x0.2" />
	<field name="multi_port" descr="System port.\;If nmp != 0, CPU port cannot be used.\;If (mngr_type == &quot;Hypervisor&quot;)\;Unique port identifier for the final destination of the packet\;If (mngr_type == &quot;Local Network Manager&quot;) and the port from which the command came from is Ethernet: \;Local Port\;When CPU port:\;1. span_type must be LOCAL_ETH or LOCAL_IB\;2. tr is reserved (no truncation)" access="RW" high_bound="3" low_bound="0" offset="0x7C.16" size="0x8.0" />
	<field name="trim_fwd_profile" descr="[DWIP]\;Trim And Forward (T&amp;F) trimming profile selector.\;Profile has to be of type=FWD, see Section 5.3.1, &quot;MOTPR - Monitoring Trimming Profile Register&quot;, on page 1306.\;\;Supported from Spectrum-5." access="RW" offset="0x8C.0" size="0x0.8" />
	<field name="trim_bts_profile" descr="[DWIP]\;Back To Sender (BTS) trimming profile selector.\;Profile has to be of type=BTS, see Section 5.3.1, &quot;MOTPR - Monitoring Trimming Profile Register&quot;, on page 1306.\;\;Supported from Spectrum-6." access="RW" offset="0x8C.8" size="0x0.8" />
	<field name="ip_len_fix" descr="[DWIP]\;IP length fix for trimmed packets.\;When enabled, IP length field is fixed after truncation.\;0: No change (default)\;1: Update IP length field after truncation.\;Reserved when itc=1.\;[DWIP] Supported from Spectrum-5." access="RW" offset="0x8C.16" size="0x0.1" />
	<field name="trim_qos" descr="[DWIP]\;Quality of Service trimming mode.\;0: AGENT - take trimming Switch Priority and Traffic Class from the trimming agent (MPAT).\;1: MAPPED - map trimming Switch Priority and Traffic Class from original Switch Priority (MOTSPT).\;Supported from Spectrum-6." access="RW" enum="AGENT=0x0,MAPPED=0x1" offset="0x8C.20" size="0x0.1" />
	<field name="pcp_rw" descr="[DWIP]\;Rewrite PCP and DEI according to the Switch Prio set by the agent.\;0: PRESERVE - preserves pcp_rewrite_en\;2: CLEAR - clears pcp_rewrite_en\;3: SET - sets pcp_rewrite_en\;\;Supported in Spectrum-5 only.\;Reserved when trim=0." access="RW" enum="PRESERVE=0x0,CLEAR=0x2,SET=0x3" offset="0x90.0" size="0x0.2" />
	<field name="dscp_rw" descr="[DWIP]\;Rewrite DSCP according to the Switch Prio set by the agent.\;0: PRESERVE - preserves dscp_rewrite_en\;2: CLEAR - clears dscp_rewrite_en\;3: SET - sets dscp_rewrite_en\;\;Supported in Spectrum-5 only.\;Reserved when trim=0." access="RW" enum="PRESERVE=0x0,CLEAR=0x2,SET=0x3" offset="0x90.8" size="0x0.2" />
	<field name="dscp" descr="[DWIP]\;The DSCP value to overwrite with.\;\;Supported in Spectrum-5 only.\;Reserved when trim=0." access="RW" offset="0x90.16" size="0x0.6" />
	<field name="overwrite_dscp" descr="[DWIP]\;Whether to overwrite DSCP with dscp provided by the trimming agent.\;Note: Can be overridden by dscp_rewrite_en if set.\;\;Supported in Spectrum-5 only.\;Reserved when trim=0." access="RW" offset="0x90.23" size="0x0.1" />
	<field name="ignore_agent_trim_profile" descr="[DWIP]\;Ignores MPAT trimming profile fields.\;Supported on Write and on Query.\;Trimming profile can be set in MOTPR. See Section 5.3.1, &quot;MOTPR - Monitoring Trimming Profile Register&quot;, on page 1306.\;Supported in Spectrum-5 only." access="OP" offset="0x90.31" size="0x0.1" />
	<field name="emt_index" descr="[DWIP] Egress Modifier Template binding 0.\;EMT index.\;Range: 0 .. cap_max_emts - 1.\;See FMTC, FMTE.\;\;Supported in Spectrum-5 only.\;Reserved when trim=0 or when emt_bind = NOP." access="RW" offset="0x98.0" size="0x0.8" />
	<field name="emt_bind" descr="[DWIP] Egress Modifier Template binding 0.\;Bind an EMT:\;0: NOP - no bind\;1: PUSH - bind as push\;2: EDIT - bind as edit\;4: POP - bind as pop\;\;Supported in Spectrum-5 only.\;Reserved when trim=0." access="RW" enum="NOP=0x0,PUSH=0x1,EDIT=0x2,POP=0x4" offset="0x98.8" size="0x0.4" />
	<field name="modifier_base" descr="[DWIP] Egress Modifier Template binding 0.\;Modifier Base Label.\;\;Push/Edit/Pop will be applied in the beginning of the following selected field of encapsulated header:\;Note: Pop is allowed only with SOP (0).\;\;0: SOP (start of packet)\;1: New MAC header\;2: New ETHERTYPE \;3: New IPv4/IPv6 header\;4: New MPLS \;5: New VxLAN/Geneve/VxLAN-GPE/NVGRE \;6: New GRE header\;7: New UDP header\;8: New Flex Encap \;9: New Inner MAC header \;\;11: New Inner ETHER Type \;\;Supported in Spectrum-5 only.\;Reserved when trim=0 or when emt_bind = NOP." access="RW" offset="0x98.16" size="0x0.4" />
	<field name="modifier_offset" descr="[DWIP] Egress Modifier Template binding 0.\;\;Offset on top of modifier_base.\;0: ZERO - zero offset\;1: CBSET_0 - offset is custom_bytes[1:0]\;2: CBSET_1 - offset is custom_bytes[3:2]\;\;Supported in Spectrum-5 only.\;Reserved when trim=0 or when emt_bind = NOP." access="RW" enum="ZERO=0x0,CBSET_0=0x1,CBSET_1=0x2" offset="0x98.24" size="0x0.2" />
</node>

<node name="mpcir_ext" descr="" size="0xa0.0" >
	<field name="all" descr="If set to &apos;01&apos;, activates the flow of preparation for FW ISSU, on all services. The values in op-codes for &quot;per-service&quot; are ignored.\;If set to &apos;10&apos;, returns to operational state on all services. The values in op-codes for &quot;per-service&quot; are ignored.\;11 - get_status for all services" access="OP" offset="0x0.30" size="0x0.2" />
	<field name="ports" descr="For each of the services, the following operations are available:\;0: N/A (no action)\;1: start preparation flow for FW ISSU \;2: return to operational service (end of FW ISSU flow)\;3: get status\;\;When set to &apos;3&apos;, the current status will appear in corresponding _stat fields." access="OP" offset="0x4.0" size="0x0.2" />
	<field name="ports_stat" descr="Status for each of the services. \;0: not in FW ISSU flow state (FW ISSU flow is not initiated) \;1: done with preparations for FW ISSU flow\;2: Preparation for FW ISSU flow started but FW still not done service handling [Internal]: busy with some other critical flow)." access="RO" offset="0xC.0" size="0x0.2" />
</node>

<node name="mpghr_ext" descr="" size="0x90.0" >
	<field name="hist_reset_counter" descr="Counter of number of times FW reset the shaper counters." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="bin_size" descr="Bin Size, Units in Watt." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="short_bin_unit_time_measure" descr="Bin Unit Time measure for Short window\;Units of 500 micro seconds\;" access="RO" offset="0x0.16" size="0x0.16" />
	<field name="hist_min_value" descr="Histogram min value, Units in Watt\;Setting value will reset the bins" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="long_bin_unit_time_measure" descr="Bin Unit Time measure for Long window\;Units of 500 micro seconds\;" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="short_pwr_avg_bin" descr="Short Power average Bin" access="RO" high_bound="15" low_bound="0" offset="0x10.0" size="0x40.0" />
	<field name="long_pwr_avg_bin" descr="Long Power average Bin" access="RO" high_bound="15" low_bound="0" offset="0x50.0" size="0x40.0" />
</node>

<node name="mppcr_ext" descr="" size="0x40.0" >
	<field name="profile_id" descr="Profile id\;Valid values: 0-15" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="tcs" descr="[DWIP]\;Time Config Selector\;0: profile_config is set with avg_pwr_num_of_sampling, pid_update_num_of_sampling fields\;1: profile_config is set with avg_pwr_time, pid_update_time fields" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="v" descr="Valid\;0: Profile is not valid\;1: Profile is valid" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="param_b" descr="reserved for future use" access="RW" high_bound="3" low_bound="0" offset="0x4.24" size="0x4.0" />
	<field name="profile_name" descr="Profile Name. Array of 20 char, Null terminated\;Can&apos;t change profile which is currently used by FW" access="RW" high_bound="19" low_bound="0" offset="0x8.24" size="0x14.0" />
	<field name="profile_config" descr="Profile configuration" subnode="power_profile_config_ext" access="RW" high_bound="1" low_bound="0" offset="0x20.0" size="0x20.0" />
</node>

<node name="mppdr_ext" descr="" size="0x80.0" >
	<field name="vr_power" descr="Power consumption read from VR in Watts" access="RO" high_bound="63" low_bound="0" offset="0x0.16" size="0x80.0" />
</node>

<node name="mppgcr_ext" descr="" size="0x24.0" >
	<field name="e" descr="Enable power capping\;0: Power capping is disabled\;1: Power capping is enabled 2-3: Reserved\;\;Can be changed on the fly. Once disabled 100% line rate is configured" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="phe" descr="Power Histogram Enable\;0: Power Histogram is disabled\;1: Power Histogram is enabled \;2-3: Reserved" access="RW" offset="0x0.2" size="0x0.2" />
	<field name="persistent_mode" descr="[DWIP]\;0: Profiles configuration is persistent\;1: Profiles configuration is not persistent" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="curr_profile_id" descr="The actual profile id used by the FW.\;See Table 212, &quot;MPPCR - Management Power Profiling Configuration Register Layout,&quot; on page 227\;Valid values: 0-15" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="next_profile_id" descr="The next profile id to be used by the FW.\;See Table 212, &quot;MPPCR - Management Power Profiling Configuration Register Layout,&quot; on page 227\;Valid values: 0-15" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="idle_power_a_factor" descr="Idle Power A factor to be used when calculating Idle power\;" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="idle_power_b_factor" descr="Idle Power B factor to be used when calculating Idle power" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="shaper_adj_num_of_iter" descr="Num of MPPGCR.sampling_time iterations to update the shaper" access="RW" offset="0x1C.16" size="0x0.8" />
	<field name="min_shaper" descr="Min shaper value to be used by FW\;Min allowed value is 1" access="RW" offset="0x20.0" size="0x0.8" />
</node>

<node name="mppgh_ext" descr="" size="0x50.0" >
	<field name="bin_unit_time_measure" descr="Bin Unit Time Measure\;Units in micro seconds. For instance, 1000 equals to 1ms." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="hist_reset_counter" descr="Counter of number of times FW reset the shaper counters." access="RO" offset="0x8.0" size="0x0.8" />
	<field name="no_shaper_bin" descr="No Shaper Bin\;The time interval spent w/o applying any shaper due to power limits." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="shaper_bin" descr="Shaper Bin \;Each bin represents 6.25%.\;For example, \;shaper_bin[0] will be incremented every time FW configured shaper value greater than 0% and lower than 6.25%.\;shaper_bin[1] will be incremented every time FW configured shaper value 6.25%-12.5%\;..\;shaper_bin[15] will be incremented every time FW configured shaper value 93.75%-100%\;\;Note: The shaper configuration is applied to all ports which effect the traffic / port bandwidth." access="RO" high_bound="15" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mppgs_ext" descr="" size="0x10.0" >
	<field name="op" descr="Operation\;0: Read only\;1: Clear counters and Read" access="OP" offset="0x0.0" size="0x0.2" />
	<field name="critical_power_cnt" descr="Number of times identified critical power indication." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="short_win_power_avg" descr="Power average calculated on the short window\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="long_win_power_avg" descr="Power average calculated on the long window\;" access="RO" offset="0xC.0" size="0x0.16" />
</node>

<node name="mprs_ext" descr="" size="0x14.0" >
	<field name="parsing_depth" descr="Minimum Parsing Depth\;Units of Bytes. \;Need to enlarge parsing depth according to L3, MPLS, tunnels, ACL rules, custom_bytes, traps, hash etc. \;Default is 96B\;Value must be larger than 0\;The device will parse no deeper than cap_max_parsing_depth\;\;" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="ctipl_dis" descr="If set, ctipl_l2_length and ctipl fields are reserved.\;Default value is 0." access="OP" offset="0x0.29" size="0x0.1" />
	<field name="prs_depth_dis" descr="If set, parsing_depth and parsing_en fields are reserved.\;Default value is 0." access="OP" offset="0x0.30" size="0x0.1" />
	<field name="en_l4_raw_prs" descr="Enable L4 RAW parsing and L4 inner RAW parsing.\;Parser will extract 4 bytes after IP header to l4_raw and will extract 4 bytes after inner IP header for inner_l4_raw.\;See l4_extended_types in Table 2379, &quot;ACL Key Elements - L4 Group,&quot; on page 2851\;Default value is 0.\;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="parsing_en" descr="Parsing enable\;Bit0: enable parsing of NVE of types VXLAN, VXLAN-GPE, GENEVE and NVGRE, default enabled\;Note: for proper parsing the parsing_depth must also be configured\;Supported for Spectrum-1, reserved otherwise since Spectrum-2 supports concurrent QinQ and NVE." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="ctipl_l2_length" descr="L2 header length to be added to IP length for Cut Through IP Length Based mode\;This length should include DMAC, SMAC, L2 tags (VLANs etc.), MPLS labels. e.g. configure 52 for DMAC+SMAC + 10 tags/labels\;Units of Bytes\;Reserved when ctipl = 0." access="RW" offset="0x8.0" size="0x0.7" />
	<field name="ctipl" descr="Cut Through IP Length Based\;0: Cut through from low to high rate is based on MTU and port rates (default)\;1: Cut through from low to high rate is based on IP Length and port rates for IP packets, else, based on MTU" access="RW" offset="0x8.8" size="0x0.1" />
	<field name="vxlan_udp_dport" descr="VXLAN UDP destination port\;Used for identifying VXLAN packets and for dport field in encapsulation\;Default 4789" access="RW" offset="0x10.0" size="0x0.16" />
</node>

<node name="mpsc_ext" descr="" size="0x14.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number (Rx ports)\;Not supported from CPU port\;Not supported from router port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cong" descr="Congestion\;Sample only when egress congestion\;The congestion configuration is done by SBCTC, see\;Section 10.11.1, &quot;SBCTC - Shared Buffer Congestion Threshold Configuration Register&quot;, on page 2768\;For Switch-IB/2 the congestion is port congestion. Thus need to configure port congestion in SBGCR.tele_entitiy, see Section 10.8.1, &quot;SBGCR - Shared Buffer Global Configuration Register&quot;, on page 2728\;For Switch-IB/2 this is a global configuration, affecting all local_ports\;Reserved for Spectrum switches." access="RW" offset="0x4.29" size="0x0.1" />
	<field name="e" descr="Enable\;0: Disable sampling on port local_port (disabled)\;1: Enable sampling on port local_port" access="RW" offset="0x4.30" size="0x0.1" />
	<field name="c" descr="Clear counter\;Clears the count_sample_drop" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="rate" descr="Sampling rate = 1 out of rate packets (with randomization around the point)\;Valid values are: 1 to 3.5*10^9\;" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="count_sample_drops_high" descr="A count of frames that were discarded after sampling. Discard is due to CPU policers or lack of resources towards the CPU.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="count_sample_drops_low" descr="A count of frames that were discarded after sampling. Discard is due to CPU policers or lack of resources towards the CPU.\;" access="RO" offset="0x10.0" size="0x4.0" />
</node>

<node name="mpscr_ext" descr="" size="0x20.0" >
	<field name="warning_inactive_time" descr="Thermal Throttling (FW mode) warning inactive time\;Each unit is equivalent to 100uSec\;Reserved for Switch.\;" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="warning_active_time" descr="Thermal Throttling (FW mode) warning active time\;Each unit is equivalent to 100uSec\;Reserved for Switch.\;" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="critical_inactive_time" descr="Thermal Throttling (FW mode) critical inactive time\;Each unit is equivalent to 100uSec\;Reserved for Switch.\;" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="critical_active_time" descr="Thermal Throttling (FW mode) critical active time\;Each unit is equivalent to 100uSec\;Reserved for Switch.\;" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="l0_all_queues_are_import" descr="[DWIP]\;If set, L0 controller (HW) requires all queues to be empty before moving to L0 state. Global parameter in Switch project.\;Reserved for GPU.\;" access="RW" offset="0xC.0" size="0x0.1" />
	<field name="cc" descr="Clear Counters\;0: Don&apos;t clear MTSR counters\;1: Clear MTSR counters\;Reserved for Switch." access="OP" offset="0x10.0" size="0x0.1" />
	<field name="ge" descr="[DWIP]\;Global Enable L1/L0 functionality.\;When set, enable L1/L0 feature according to the port configuration\;\;Note 1: Moving from disable to enable will require reinit the ports for the change to take effect." access="OP" offset="0x18.0" size="0x0.1" />
</node>

<node name="mpsh_reg_ext" descr="" size="0x50.0" >
	<field name="time_measure_unit" descr="Unit time of time which each bin is counting. Unit is equal to \;time_measure_unit in time_unit\;\;For exmple:\;time_unit = 0\;time_measure_unit = 500\;Each bit tick is 500 useconds" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="power_entity" descr="0 - Main\;1 - Tile 0\;2- Tile 1\;3- Tile 2\;4- Tile 3\;5- Tile 4\;6- Tile 5\;7- Tile 6\;8- Tile 7" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="time_unit" descr="Unit time of\;0 - useconds\;1 - miliseconds" access="RO" offset="0x4.0" size="0x0.2" />
	<field name="power_state" descr="Each element indicates the duration that the device was in this power stateThe total time equals to the element value * unit_time_measure" access="RO" high_bound="15" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mpsq_reg_ext" descr="" size="0x10.0" >
	<field name="power_states_supported_bitmask" descr="If the bit is set, the device supports this power state.\;0 - P0. Default power state, each device will support this state.\;1 - P1 TAV\;2-15 - reserved" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="power_entity" descr="0 - Main\;1 - Tile 0\;2- Tile 1\;3- Tile 2\;4- Tile 3\;5- Tile 4\;6- Tile 5\;7- Tile 6\;8- Tile 7" access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="current_state" descr="The current device power state\;0 - P0\;1 - P1 TAV\;2-15 - reserved" access="RO" offset="0x4.0" size="0x0.4" />
</node>

<node name="mqdik_reg_ext" descr="" size="0x208.0" >
	<field name="algorithm" descr="0: ECC. Used for any of the P256, P385, P521 curves.\;1: RSA. Used for 2048 or 4096 keys." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="key_size" descr="Number of Bytes in the public_key" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="status" descr="0: Key is not ready for query\;1: Key is provided in the response" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="public_key" descr="Public-key value, per the specific algorithm." access="RO" high_bound="127" low_bound="0" offset="0x8.0" size="0x200.0" />
</node>

<node name="mqis_reg_ext" descr="" size="0x18.0" >
	<field name="info_type" descr="Type of information string to be queried:\;0x0: VPD - Read the PCI Vital Product Data capability content.\;0x1: MODEL_NAME\;0x2: MODEL_DESCRIPTION\;0x3: IMAGE_VSD\;0x4: DEVICE_VSD\;0x5: ROM_INFO\;other values are reserved." access="INDEX" enum="MODEL_NAME=0x1,MODEL_DESCRIPTION=0x2,IMAGE_VSD=0x3,DEVICE_VSD=0x4,ROM_INFO=0x5" offset="0x0.0" size="0x0.8" />
	<field name="info_length" descr="Total size of the information string, according to info_type. Value given in bytes." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="read_length" descr="Number of bytes requested. The device returns the number of bytes actually read." access="RW" offset="0x8.0" size="0x0.16" />
	<field name="read_offset" descr="Offset in bytes of the first byte requested to read." access="INDEX" offset="0x8.16" size="0x0.16" />
	<field name="info_string" descr="Information string accessed, according to info_type. If the information is not available, a NULL string is returned." access="RO" high_bound="7" low_bound="0" offset="0x10.24" size="0x8.0" />
</node>

<node name="mroq_ext" descr="" size="0x20.0" >
	<field name="reset_trigger" descr="The firmware reset trigger\;Bit 0: TRIGGER0 (live-patch)\;Bit 1: immediate action (used for embedded CPU shut down/\;Reset)\;Bit 3: TRIGGER3 (PCIe link disable | hot reset)\;Bit 6: TRIGGER6 (PERST)\;Other bits are reserved" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="reset_type" descr="Query chip reset type\;0: Full chip reset\;1: Keep network port active during reset (phy less reset)\;2: NIC only reset (for SoC devices) - Keep ARM subsystem operational while NIC subsystem (including PCI) is reset.\;3: ARM only reset\;4: ARM OS shut down\;5: Network reset - Keep PCIe active during reset. Relevant for CX8 onward \;0xff: In-Service SW update - Keep network port and PCIe port active and operation during reset." access="INDEX" offset="0x0.8" size="0x0.8" />
	<field name="query_is_valid" descr="Selected type is supported." access="RO" offset="0x0.16" size="0x0.1" />
	<field name="pci_sync_for_fw_update_start" descr="This filed defines the reset flow. \;Bit 0: Legacy flow \;Bit 1: Synced driver flow \;Bit 2: Synced tool flow, should be 0 for internal host\;Bit 3: Reserved" access="RO" offset="0x0.17" size="0x0.4" />
	<field name="pci_reset_req_method" descr="FW reset Method\;bit0: Link Disable \;bit1: Hot reset (SBR)\;bit2-7: reserved \;Note: This field provides information when reset trigger equal to TRIGGER3 (e.g., PCIe link toggle, PCIe hot reset)" access="RO" offset="0x0.24" size="0x0.8" />
</node>

<node name="mrpr_reg_ext" descr="" size="0x108.0" >
	<field name="type" descr="Runtime parameter to access or query\;" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="status" descr="0: Parameter is not supported\;1: Parameter is supported but is not ready for read\;2: Successful read\;3: Successful write\;Else - Reserved" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="length" descr="Number of Bytes in the parameter data section.\;When reading an unsupported /unavailable parameter, this field is 0 and there is no data field in the read response." access="RW" offset="0x0.24" size="0x0.8" />
	<field name="data" descr="Parameter data.\;Writing to this field for read-only parameter has no effect. \;Reading this field for a write-only parameter returns unpredicted value." access="RW" high_bound="63" low_bound="0" offset="0x8.0" size="0x100.0" />
</node>

<node name="mrrr_ext" descr="" size="0x8.0" >
	<field name="init_rr" descr="Initiate resource release:\;0: Resource release type 0 \;1: Resource release type 1 \;If rr_status is &quot;1&quot; then this operation fails" access="WO" offset="0x0.0" size="0x0.4" />
	<field name="rr_status" descr="Resource release status:\;0: No resource release process is ongoing\;1: Resource release process is ongoing" access="RO" offset="0x4.0" size="0x0.4" />
</node>

<node name="mrsr_ext" descr="" size="0x8.0" >
	<field name="command" descr="Reset/shutdown command\;0: clear state of reset_at_pci_disable\;1: software reset immediate (switch soft reset).\;6: reset_at_pci_disable - reset will be done at PCI_DISABLE. See MCAM bit48. Note: when no PCI (e.g. unmanaged switches or for Retimers) will do reset without waiting for PCI_DISABLE\;7: fw_link_reset_at_pci_disable - PCIe FW Link Reset, core is up [DWIP]" access="RW" offset="0x0.0" size="0x0.4" />
</node>

<node name="mrsrft_ext" descr="" size="0x8.0" >
	<field name="state_ld" descr="When PCI Link Disable:\;0: hot reset6: all reset\;7: PCIe FW Link Reset, core is up" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="state_sbr" descr="When PCI Secondary Bus Reset:\;0: hot reset6: all reset\;7: PCIe FW Link Reset, core is up" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="state_sld" descr="When PCI Surprise Link Down:\;0: hot reset6: all reset\;7: PCIe FW Link Reset, core is up" access="RW" offset="0x0.8" size="0x0.4" />
	<field name="state_perst" descr="When PERST:\;0: hot reset6: all reset\;7: PCIe FW Link Reset, core is up" access="RW" offset="0x0.12" size="0x0.4" />
</node>

<node name="mrtc_reg_ext" descr="" size="0x10.0" >
	<field name="time_synced" descr="If set, the time returned in time_l/time_h is the number of microseconds passed since 1/1/1970. \;otherwise, the time_l/time_h measures the time since the NIC boot." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="time_h" descr="MSB of timestemp depnding on time_synced" access="RW" offset="0x8.0" size="0x4.0" />
	<field name="time_l" descr="LSB of timestemp depnding on time_synced" access="RW" offset="0xC.0" size="0x4.0" />
</node>

<node name="msci_ext" descr="" size="0xc.0" >
	<field name="index" descr="CPLD index" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="version" descr="CPLD version" access="RO" offset="0x4.0" size="0x4.0" />
</node>

<node name="msgcr_reg_ext" descr="" size="0x8.0" >
	<field name="fake_cable_detect_en" descr="0: fake cable detection is disabled\;1: fake cable detection is enabled" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="support_perst_gpio" descr="[DWIP]:\;0: PERST GPIO assertion will NOT trigger ASIC reset\;1: PERST GPIO assertion will trigger ASIC reset\;" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="support_inter_asic_block" descr="[DWIP]:\;Support inter ASIC blocking\;0: Disable_Link GPIO assertion will NOT trigger Inter ASIC communication blocking\;1: Disable_Link GPIO assertion will trigger Inter ASIC communication blocking\;" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="support_error_injection" descr="[DWIP]:\;Support Error injection \;0: Deny any error injection operation (Thermal/Link/PCI)\;1: Allow error injection trigger\;" access="RO" offset="0x4.8" size="0x0.1" />
</node>

<node name="msgi_ext" descr="" size="0x80.0" >
	<field name="serial_number" descr="ASIC serial number (ASCII string)" access="RO" high_bound="5" low_bound="0" offset="0x0.0" size="0x18.0" />
	<field name="part_number" descr="ASIC part number (ASCII string)" access="RO" high_bound="4" low_bound="0" offset="0x20.0" size="0x14.0" />
	<field name="revision" descr="Revision (ASCII string)" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="product_name" descr="Product Name (ASCII string)" access="RO" high_bound="15" low_bound="0" offset="0x40.0" size="0x40.0" />
</node>

<node name="mshr_reg_ext" descr="" size="0x10.0" >
	<field name="state" descr="Physical Violation Prevention Mode\;0: UNLOCKED\;0x1: LOCKED\;0x2: LOCK_FW_UPDATE\;0x3: LOCK_HOST_CFG\;Supported only in Quantum-3" access="WO" enum="UNLOCKED=0x0,LOCKED=0x1,LOCK_FW_UPDATE=0x2,LOCK_HOST_CFG=0x3" offset="0x0.24" size="0x0.8" />
	<field name="key" descr="Key" access="WO" high_bound="7" low_bound="0" offset="0x8.24" size="0x8.0" />
</node>

<node name="mslcg_ext" descr="" size="0x110.0" >
	<field name="cap_num_clock_gates" descr="Number of System Level Clock Gates\;[Internal] Rubin has ~3500 SLCGs; Rubin has (TBD) BLCGs\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="global" descr="Global config:\;0: Not Global\;1: Global \;When global=1 mode, then state[0] is used" access="INDEX" offset="0x4.0" size="0x0.1" />
	<field name="clock_gate_type" descr="System Level Clock Gating type:\;0: SLCG (Secondary Level Clock Gating)\;1: BLCG (Block Level Clock Gating)" access="INDEX" offset="0x4.8" size="0x0.2" />
	<field name="slcg_base" descr="Clock gating base index\;Units of 1024\;e.g. when clock_gate_type = 0 and slgc_base=1 then state[3] applies to SLCG [1024+3]\;Reserved when global = 1" access="INDEX" offset="0x8.0" size="0x0.8" />
	<field name="slcg_base_offset_start" descr="Clock gating base index offset starting location\;0: No offset from slgc_base\;1-1023: Offset from slgc_base\;e.g. when clock_gate_type = 0 and slgc_base=1 and slgc_base_offset_start=45 then state[3] applies to SLCG [1024+45+3]\;Reserved when global = 1" access="INDEX" offset="0x8.16" size="0x0.10" />
	<field name="state" descr="State per each Clock Gate (CG)\;0: CG disabled \;1: CG enabled\;2: apply production setting (FW configuration according to production info). Note that this opcode (apply) is write only.\;Note: when reading only values 0 or 1 will be returned.\;States over cap_num_clock_gates are reserved (will return 0).\;3: Do nothing. Note that this opcode (apply) is write only.\;\;Note: when reading only values 0 or 1 will be returned.\;Reserved when global = 1\;" access="RW" high_bound="1023" low_bound="0" offset="0x10.30" size="0x100.0" />
</node>

<node name="mspmer_ext" descr="" size="0x30.0" >
	<field name="device_index" descr="Device Index\;0: Main_board_or_NIC\;" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="status" descr="Status\;0: Success\;1: Physical monitor is not supported\;2: Device index is not valid" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="clr" descr="Clear Counters\;0: don&apos;t clear counters\;1: clear counters" access="OP" offset="0x4.16" size="0x0.1" />
	<field name="prev_en" descr="Prevention Enable\;0: Notification only. Prevention is disabled \;1: Prevention is enabled\;\;In Spectrum-4 only, controlled by NV_SWITCH_PHY_SEC_CONF.pvpm. See Table 416, &quot;NV_SWITCH_PHY_SEC_CONF Layout,&quot; on page 822" access="RO" offset="0x4.24" size="0x0.1" />
	<field name="supported_physical_monitor" descr="31: FMON - Frequency MONitor\;30: VMON - Voltage MONitor\;29: SCPM - Secure Canary Path Monitor\;0: General \;\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="fmon_ctr" descr="Frequency Monitor Counter\;\;Stuck at 0xF, cleared only at hard reset (RST_) or power down or clr bit." access="RO" offset="0x14.0" size="0x0.4" />
	<field name="vmon_ctr" descr="Voltage Monitor Counter\;\;Stuck at 0xF, cleared only at hard reset (RST_) or power down or clr bit." access="RO" offset="0x14.4" size="0x0.4" />
	<field name="scpm_ctr" descr="Security Canary Path Monitor Counter\;A circuit macro used to flag timing slack violations as part of mitigations for physical security attacks.\;\;Stuck at 0xF, cleared only at hard reset (RST_) or power down or clr bit." access="RO" offset="0x14.8" size="0x0.4" />
	<field name="general_err" descr="General Error indication\;Cleared only at hard reset (RST_) or power down or clr bit." access="RO" offset="0x14.12" size="0x0.1" />
</node>

<node name="msps_ext" descr="" size="0xa0.0" >
	<field name="psu0" descr="System Power Supply 0 Status" access="RO" high_bound="19" low_bound="0" offset="0x0.0" size="0x50.0" />
	<field name="psu1" descr="System Power Supply 1 Status" access="RO" high_bound="19" low_bound="0" offset="0x50.0" size="0x50.0" />
</node>

<node name="mssir_firebird_ext" descr="" size="0x80.0" >
	<field name="crc" descr="Each bit represent whether a CRC error occured on the management interface to the tile number." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="bypass" descr="Each bit represent whether a bypass clock is run on the corresponding tile." access="RO" offset="0x4.0" size="0x0.8" />
	<field name="fatal_dft" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="freq0" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0xC.0" size="0x0.5" />
	<field name="freq1" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0xC.5" size="0x0.5" />
	<field name="freq2" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0xC.10" size="0x0.5" />
	<field name="freq3" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0xC.15" size="0x0.5" />
	<field name="freq4" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0xC.20" size="0x0.5" />
	<field name="freq5" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0xC.25" size="0x0.5" />
	<field name="freq6" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0x10.0" size="0x0.5" />
	<field name="freq7" descr="Each field represent the frequency dividing factor for the core clock for each of the tiles" access="RO" offset="0x10.5" size="0x0.5" />
</node>

<node name="mssir_reg_ext" descr="" size="0x88.0" >
	<field name="sys_indx" descr="System Identifier\;0: Firebird\;" access="INDEX" enum="Firebird=0x0" offset="0x0.0" size="0x0.4" />
	<field name="sys_info" descr="Firebird System Information, see Table 293, &quot;MSSIR - Management System Status Information Register Layout,&quot; on page 291" subnode="mssir_firebird_ext" access="RW" offset="0x8.0" size="0x80.0" />
</node>

<node name="mtbr_reg_ext" descr="" size="0x410.0" >
	<field name="base_sensor_index" descr="Base sensor index\;Sensors are read starting from base_sensor_index\;Sensor 0 is the ASIC sensor, sensors 1-63 are ambient sensors and sensors 64-127 are mapped to the SFP+/QSFP modules sequentially (module 0 is mapped to sensor 64, module 1 to sensor 65 and so on). Gearbox sensors starts from 256 index." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="num_rec" descr="Number of records to read\;Range 1..256" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="temperature_record" descr="Temperature record\;See Table 185, &quot;MTBR - Temperature Record Layout,&quot; on page 204" subnode="mtbr_temp_record_ext" access="RO" high_bound="255" low_bound="0" offset="0x10.0" size="0x400.0" />
</node>

<node name="mtbr_temp_record_ext" descr="" size="0x4.0" >
	<field name="temperature" descr="Temperature reading from the sensor. Units of 0.125 Celsius degrees.\;If no ambient sensor is present then the value is &apos;0&apos;. Also for a passive copper case.\;0x8000:NO_CONN- No cable or device&apos;s sensor is connected.\;0x8001: NO_TEMP_SENS - In case a cable or device is connected but the temperature sensing is not supported.\;0x8002: INDX_NA- No such cable or device&apos;s sensor index. Bigger than the number of modules.\;0x8003: INCORRECT_SENS_INFO - Sensor information is incorrect." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.\;When the bit relevant MTMP.mte is cleared, the field max_temperature is reserved.\;The value will be &apos;0&apos; for any of the &apos;800X&apos; temperature values and for &apos;0&apos; value." access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="mtbr_v2_ext" descr="" size="0x90.0" >
	<field name="base_sensor_index" descr="Base sensor index\;Sensors are read starting from base_sensor_index\;Sensor 0 is the ASIC sensor, sensors 1-63 are ambient sensors and sensors 64-127 are mapped to the SFP+/QSFP modules sequentially (module 0 is mapped to sensor 64, module 1 to sensor 65 and so on). Gearbox sensors starts from 256 index." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="num_rec" descr="Number of records to read\;Range 1..32" access="OP" offset="0x4.0" size="0x0.8" />
	<field name="temperature_record" descr="Temperature record\;See Table 185, &quot;MTBR - Temperature Record Layout,&quot; on page 204" subnode="mtbr_temp_record_ext" access="RO" high_bound="31" low_bound="0" offset="0x10.0" size="0x80.0" />
</node>

<node name="mtcap_ext" descr="" size="0x10.0" >
	<field name="sensor_count" descr="Number of ASIC+platform sensors supported by the device \;This includes the ASIC and the ambient sensors. Module sensors are not included.\;This actually is equal to sum of all &apos;1&apos; in sensor_map\;Range 1..64\;\;Known sensors:\;0: current asic temp, FW exposes current max(all diode temp sensors)\;1..63: ambient, supported only for unmanaged switch, defined by ini\;64..127: modules (not exposed by this field)" access="RO" offset="0x0.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="internal_sensor_count" descr="Number of sensors supported by the device that are on the ASIC.\;Exposes how many ASIC diodes exist. \;The FW exposes all of them as sensor[0]" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Only ASIC and ambient sensors are supported. Each bit represents a sensor.\;Per bit:\;0: Not_connected_or_not_supported\;1: Supports_temperature_measurements" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="mtcq_reg_ext" descr="" size="0x70.0" >
	<field name="device_index" descr="Device number.\;For gearboxes, the index represents the gearbox die.\;For cables, the index represents the module index starting at index 1 while index 0 indicates the host device." access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="status" descr="Indicates the status of the desired token we are generating the challenge for.\;0x0 - OK\;0x1 - TOKEN_ALREADY_APPLIED\;0x2 - TOKEN_NOT_SUPPORTED\;0x3 - NO_KEY_CONFIGURED (there is no public_key that can be used for this token) \;0x4 - INTERFACE_NOT_ALLOWED (asking for local token from remote interface, or remote token from local interface)" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="token_opcode" descr="The token which a challenge is generated for.\;0: RMCS\;1: RMDT\;2: CRCS - supported from Spectrum-4 and above\;3: CRDT - supported from Spectrum-4 and above\;\;5: MTDT\;Other: Reserved" access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="keypair_uuid" descr="The UUID of the key used to generate the challenge." access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="base_mac" descr="Device base MAC address / unique identifier." subnode="uint64" access="RO" offset="0x14.0" size="0x8.0" />
	<field name="psid" descr="Device PSID" access="RO" high_bound="3" low_bound="0" offset="0x1C.0" size="0x10.0" />
	<field name="fw_version_39_32" descr="Device FW version" access="RO" offset="0x2C.0" size="0x0.8" />
	<field name="fw_version_31_0" descr="Device FW version" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="source_address" descr="Source address of debug requester. DLID for Infiniband\;Valid only for RMCS/RMDT." access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
	<field name="session_id" descr="Unique debug session identifier. \;See details in REMOTE_DEBUG_KEEP_ALIVE.\;Valid only for RMCS." access="RO" offset="0x44.0" size="0x0.16" />
	<field name="challenge_version" descr="Version of the challenge format." access="RO" offset="0x44.24" size="0x0.8" />
	<field name="challenge" descr="Random generated field. Used for randomness and replay-protection." access="RO" high_bound="7" low_bound="0" offset="0x48.0" size="0x20.0" />
</node>

<node name="mtdc_ext" descr="" size="0x20.0" >
	<field name="tracer_limit_en" descr="Tracer writing to PCI is limited.When this mode is enable, the hw tracer pointer cannot override the software read index pointer.If software will not update the read index pointer, new events will fall and will not be sent.\;0: NA - ignored, does not perform any operation \;1: Enable\;2: Disable" access="RW" offset="0x0.0" size="0x0.2" />
	<field name="tlb_addr_msb" descr="The lsb of the address for the cyclic buffer in the host memory." access="RW" offset="0x8.0" size="0x4.0" />
	<field name="tlb_addr_lsb" descr="The lsb of the for the cyclic buffer address in the host memory." access="RW" offset="0xC.12" size="0x0.20" />
	<field name="hw_pointer" descr="Pointer of the current hw index the tracer is writing to.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="sw_pointer" descr="Pointer to the last tracer event index that the software consumed.\;" access="RW" offset="0x14.0" size="0x4.0" />
</node>

<node name="mtecr_ext" descr="" size="0x60.0" >
	<field name="sensor_count" descr="Number of sensors supported by the ASIC+platform\;This includes the ASIC, ambient sensors, module sensors, Gearboxes etc. \;This actually is equal to sum of all &apos;1&apos; in sensor_map\;\;Known sensors:\;0: current asic temp, FW exposes current max(all diode temp sensors)\;1..62: ambient, supported only for unmanaged switch, defined by ini\;64..255: modules\;256..288: Gearbox\;289..704: reserved for future" access="RO" offset="0x0.0" size="0x0.12" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read from.\;e.g. when 32modules: 64+32-1 = 95" access="RO" offset="0x0.16" size="0x0.12" />
	<field name="internal_sensor_count" descr="Number of sensors supported by the device that are on the ASIC. \;Exposes how many ASIC diodes exist. \;The FW exposes all of them as sensor[0]" access="RO" offset="0x4.0" size="0x0.7" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x4.28" size="0x0.4" />
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit represents a sensor.\;This field is size variable based on the last_sensor field and in granularity of 32bits.\;Per bit:\;0: Not connected or not supported\;1: Supports temperature measurements\;\;In case of last_sensor = 704 (22*32):\;sensor_warning[0] bit31 is sensor_warning[703]\;sensor_warning[0] bit0 is sensor_warning[703-31]\;sensor_warning[21] bit31 is sensor_warning[31]\;sensor_warning[21] bit0 is sensor_warning[0]\;\;In case if last_sensor = 259 (22*32):\;Note: roundup(259,32)=288\;sensor_warning[0] bit31 is sensor_warning[287]\;sensor_warning[0] bit0 is sensor_warning[287-31=256]\;sensor_warning[8] bit31 is sensor_warning[31]\;sensor_warning[8] bit0 is sensor_warning[0]\;sensor_warning[9..21] are not used\;\;64-192 of sensor_index are mapped to the modules sequentially (module 0 is mapped to sensor_index 64, module 1 to sensor_index 65 and so on)." access="RO" high_bound="21" low_bound="0" offset="0x8.0" size="0x58.0" />
</node>

<node name="mteim_reg_ext" descr="" size="0x30.0" >
	<field name="cap_core_tile" descr="Number of processors per tile ASIC.\;" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="cap_core_main" descr="Number of processors in the main ASIC." access="RO" offset="0x0.8" size="0x0.8" />
	<field name="cap_core_dpa" descr="Number of processors in the DPA unit." access="RO" offset="0x0.16" size="0x0.8" />
	<field name="cap_num_of_tile" descr="Number of tiles per device. For devices without tiles (only main ASIC), this field should be &apos;0&apos;.\;" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="type_core_tile" descr="Processor type.\;0: N/A\;1: IRISC\;2: RISC5\;Else: Reserved" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="type_core_main" descr="Processor type.\;0: N/A\;1: IRISC\;2: RISC5\;Else: Reserved" access="RO" offset="0x4.4" size="0x0.4" />
	<field name="type_core_dpa" descr="Processor type.\;0: N/A\;1: IRISC\;2: RISC5\;Else: Reserved" access="RO" offset="0x4.8" size="0x0.4" />
	<field name="is_phy_uc_supported" descr="Indicates wether Phy_UC tracers mapping are supported by the device FW. \;When set, The event_id of the Phy UC of the instance will be calculated by first_tile/main _core _event_id[i] + cap_core_tile/main.\;When clear the Phy UC will be ignored.\;" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="is_dwsn_msb_supported" descr="When set to &apos;1&apos;, the device supports dwsn_msb bit within the FW trace layout." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="first_dpa_core_event_id" descr="The mapping for the rest of the DPA ASIC processors are sequential and the mapping is defined as:\;processor[x]=first_dpacore_event_id+x" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="first_main_core_event_id" descr="The mapping for the rest of the main ASIC processors are sequential and the mapping is defined as:\;processor[x]=first_main_core_event_id+x" access="RO" offset="0x8.24" size="0x0.8" />
	<field name="first_tile_core_event_id" descr="The mapping for the rest of the tile[y] ASIC processors are sequential and the mapping is defined as:\;processor[x]=first_tile_core_event_id[y]+x\;" access="RO" high_bound="7" low_bound="0" offset="0xC.24" size="0x8.0" />
</node>

<node name="mteir_reg_ext" descr="" size="0xc.0" >
	<field name="thermal_error_mode" descr="Error type Injected\;0: No thermal error injection\;1: Warning\;2: Critical\;3: Fatal\;4: Force the device into normal temperature range\;Default is no thermal error injection \;Note: Change to critical/fatal may cause the ASIC to reset." access="RW" offset="0x0.0" size="0x0.3" />
</node>

<node name="mtewe_ext" descr="" size="0x5c.0" >
	<field name="sensor_count" descr="Number of sensors supported by the device\;This includes the ASIC, ambient sensors, Gearboxes etc.\;\;Known sensors:\;0: current asic temp, FW exposes current max(all diode temp sensors)\;1..62: ambient, supported only for unmanaged switch, defined by ini\;64..255: modules\;256..288: Gearbox\;289..704: reserved for future" access="RO" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.12" size="0x0.4" />
	<field name="last_sensor" descr="Last sensor index that is available in the system to read from." access="RO" offset="0x0.16" size="0x0.12" />
	<field name="sensor_warning" descr="Bit vector indicating which of the sensor reading is above threshold.\;This field is size dependent and based on last_sensor field and in granularity of 32bits.\;\;In case of last_sensor = 704 (22*32):\;sensor_warning[0] bit31 is sensor_warning[703]\;sensor_warning[0] bit0 is sensor_warning[703-31]\;sensor_warning[21] bit31 is sensor_warning[31]\;sensor_warning[21] bit0 is sensor_warning[0]\;\;In case if last_sensor = 259 (22*32):\;Note: roundup(259,32)=288\;sensor_warning[0] bit31 is sensor_warning[287]\;sensor_warning[0] bit0 is sensor_warning[287-31=256]\;sensor_warning[8] bit31 is sensor_warning[31]\;sensor_warning[8] bit0 is sensor_warning[0]\;sensor_warning[9..21] are not used" access="RO" high_bound="21" low_bound="0" offset="0x4.0" size="0x58.0" />
</node>

<node name="mtie_ext" descr="" size="0x30.0" >
	<field name="enable_all" descr="Enable/Disable all FW tracer initiator and ignore mask.\;Starts from bit 0.\;0: Use bit mask\;1: Enable all\;2: Disable all" access="OP" offset="0x0.0" size="0x0.2" />
	<field name="log_delay" descr="Adding delay to log events in usecs\;" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="source_id_bitmask" descr="Bit mask of all the possible tracer initiators.\;Reserved when enable_all != 0.\;The mapping of source id to HW unit is unique per device and can be fetched from FW code.\;" access="RW" high_bound="7" low_bound="0" offset="0x10.0" size="0x20.0" />
</node>

<node name="mtim_ext" descr="" size="0x10.0" >
	<field name="log_level" descr="The verbosity of the log. \;0: LOG_DEBUG\;1: LOG_INFO\;2: LOG_WARNING\;3: LOG_ERROR\;\;The lower value reflects higher verbosity than higher value.\;e.g: LOG_INFO contains LOG_WARNING and LOG_ERROR" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="log_bit_mask" descr="Bit mask of the different FW units that can be activated for the FW log.\;The mapping of source id to FW unit is unique per device and can be fetched from FW code.\;" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="mtmp_ext" descr="" size="0x20.0" >
	<field name="sensor_index" descr="Sensors index\;0: current asic temp, FW exposes current max(all diode temp sensors)\;1..62: ambient, supported only for unmanaged switch, defined by ini\;64..255: modules 256..288: Gearbox\;Others up to 704 are reserved" access="INDEX" offset="0x0.0" size="0x0.12" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="asic_index" descr="ASIC index. See ig field for more details." access="INDEX" offset="0x0.25" size="0x0.4" />
	<field name="ig" descr="Internal granularity.\;Used to query the internal diodes of the switch main ASIC and tiles. \;0: the &apos;i&apos; field may be used to query the entire ASIC internal diodes. Main + tile.\;1: The &apos;i&apos; field is ignored and only the main ASIC diodes are available to query and sensor_index is the index of the main ASIC diodes. \;2: The &apos;i&apos; field is ignored and only the tile ASIC diodes are available to query and sensor_index is the index of the tile ASIC diodes. To query a specific tile, asic_index field should be used.\;3: Reserved.\;Those sensors are not available externally and should only be used for debug." access="INDEX" offset="0x0.29" size="0x0.2" />
	<field name="i" descr="Used to query the internal diodes of the switch ASIC; for i=1, sensor_index is the index of the ASIC diode." access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="temperature" descr="Temperature reading from the sensor. \;Units of 0.125 Celsius degrees.\;For negative values 2&apos;s complement is used (for example: -3.25 Celsius will read as 0xFFE6)" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_temperature" descr="The highest measured temperature from the sensor.\;Reserved when mte = 0\;Cleared by mtr = 1\;Valid only when i = 0\;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="sdme" descr="Shut Down Events Modify Set Enable:\;0: all fields are set\;1: only sdee field is set, all other fields reserved" access="OP" offset="0x8.28" size="0x0.1" />
	<field name="weme" descr="Warning Events Modify Set Enable:\;0: all fields are set\;1: only tee field is set, all other fields reserved" access="OP" offset="0x8.29" size="0x0.1" />
	<field name="mtr" descr="Max Temperature Reset:\;0: do not modify the value of the max temperature register\;1: clear the value of the max temperature register" access="OP" offset="0x8.30" size="0x0.1" />
	<field name="mte" descr="Max Temperature Enable:\;0: disable measuring the max temperature on a sensor\;1: enables measuring the max temperature on a sensor" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="temperature_threshold_hi" descr="temperature_threshold_hi refers to the high threshold of Warning Event. Units of 0.125 Celsius degrees.\;If the sensor temperature measurement is above the threshold (and events are enabled), an event will be generated.\;threshold_hi and threshold_lo implements hysteresis mechanism of the threshold preventing toggling of the indication.\;Note that temperature_threshold_hi must be equal or lower than the system requirement.\;System requirement for module is the module warning temperature.\;System requirement for board/silicon sensors is according to product information parameters\;Note that the temperature threshold can be used to generate an event message or an interrupt using GPIO" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="sdee" descr="Temperature Shut Down Event Enable (MTSDE Register)\;0: do_not_generate_event\;1: generate_event\;2: generate_single_event\;\;Supported in downstream devices (devices on slots)." access="RW" offset="0xC.28" size="0x0.2" />
	<field name="tee" descr="Temperature Warning Event Enable (MTEWE Register)\;0: do_not_generate_event\;1: generate_event\;2: generate_single_event\;\;" access="RW" enum="do_not_generate_event=0x0,generate_event=0x1,generate_single_event=0x2" offset="0xC.30" size="0x0.2" />
	<field name="temperature_threshold_lo" descr="temperature_threshold_lo refers to the low threshold of Warning Event.Units of 0.125 Celsius degrees.\;The offset threshold_lo implements the lower threshold for the hysteresis mechanism of over temperature alert. Once alert is set, if the temperature goes below this threshold, the alert is cleared.\;Note that temperature_threshold_lo must be at least 5 degrees lower than temperature_threshold_hi" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="sensor_name_hi" descr="Sensor Name\;8 character long sensor name\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="sensor_name_lo" descr="Sensor Name\;8 character long sensor name\;" access="RO" offset="0x1C.0" size="0x4.0" />
</node>

<node name="mtpcpc_ext" descr="" size="0x28.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="local_port\;Supported to/from CPU port\;Reserved when pport = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="pport" descr="Per port:\;0: config is global. When reading - the local_port is 1\;1: config is per port" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="ptp_trap_en" descr="Enable PTP traps\;The trap_id is configured by MTPTPT" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="ing_correction_message_type" descr="Bitwise vector of PTP message types to update correctionField\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)\;Supported also from CPU port\;Default all 0\;Reserved from Quantum-3" access="RW" offset="0x10.0" size="0x0.16" />
	<field name="egr_correction_message_type" descr="Bitwise vector of PTP message types to update correctionField\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)\;Supported also from CPU port\;Default all 0" access="RW" offset="0x14.0" size="0x0.16" />
	<field name="ptp_pkey" descr="For IB Switches only:\;The PTP Pkey\;Used for identifying the PTP packets.\;Reserved when Ethernet switches" access="RW" offset="0x18.0" size="0x0.15" />
	<field name="num_domains" descr="Number of valid domains for match:\;0: ignore domain field (&quot;always match&quot;)\;1: Match only if domain[0] has a match\;2: Match only if domain[0] or [1] have a match\;etc.\;Range 0..cap_max_ptp_domains\;" access="RW" offset="0x20.0" size="0x0.8" />
	<field name="domain" descr="domain for matching\;" access="RW" high_bound="3" low_bound="0" offset="0x24.24" size="0x4.0" />
</node>

<node name="mtpppc_ext" descr="" size="0x28.0" >
	<field name="ing_timestamp_message_type" descr="Bitwise vector of PTP message types to timestamp at ingress\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)\;Default all 0\;" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="egr_timestamp_message_type" descr="Bitwise vector of PTP message types to timestamp at egress.\;MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)\;Default all 0\;" access="RW" offset="0xC.0" size="0x0.16" />
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
	<field name="field_select" descr="Field select indicates which fields to modify in write operation to this register. This field selector supported only when MCAM.mtpps_fs==1. if MCAM.mtpps_fs==0 then SW should ensure that all the WO/RW fields are valid. \;Bit 0: enable\;\;Bit 2: pattern\;Bit 3: pin_mode\;Bit 4: time_stamp\;Bit 5: out_pulse_duration\;\;" access="WO" enum="enable=0x1,pattern=0x4,pin_mode=0x8,time_stamp=0x10,out_pulse_duration=0x20" offset="0x10.0" size="0x4.0" />
	<field name="pin" descr="Pin to be configured or queried out of the supported pins." access="INDEX" offset="0x20.0" size="0x0.8" />
	<field name="pin_mode" descr="Pin mode to be used. The mode must comply with the supported modes of the requested pin.\;0x0: pps_in\;0x1: pps_out\;0x2: virtual_pin\;0x3: pps_out_and_virtual_pin\;\;Operation will fail if pin does not support the required mode." access="RW" enum="pps_in=0x0,pps_out=0x1,virtual_pin=0x2,pps_out_and_virtual_pin=0x3" offset="0x20.8" size="0x0.4" />
	<field name="pattern" descr="When pin_mode = pps_in:\;0x0: Rising edge \;0x1: Falling edge \;\;When pin_mode = pps_out:\;0x0: Pulse - (one shot) The device will generate a pulse at time_stamp time with a duration of out_pulse_duration. \;0x1: Periodic - the device will generate periodical pulses with pulse duration  of  out_pulse_duration every   according to internal clock. The 1st pulse will be generated at time_stamp time.\;\;Reserved when pin_mode = 0x2 virtual_pin\;\;" access="RW" offset="0x20.16" size="0x0.4" />
	<field name="utc_mode" descr="UTC time:\;0x0: FREE_RUNNING - time_stamp is by free running clock\;0x1: UTC - time_stamp is UTC" access="RW" enum="FREE_RUNNING=0x0,UTC=0x1" offset="0x20.30" size="0x0.1" />
	<field name="enable" descr="Enables the PPS functionality the specific pin.\;0x0: Disable \;0x1: Enable" access="RW" enum="Disable=0x0,Enable=0x1" offset="0x20.31" size="0x0.1" />
	<field name="time_stamp" descr="When pin_mode = pps_in, the latched device time when it was triggered from the external GPIO pin. \;When pin_mode = pps_out or virtual_pin or pps_out_and_virtual_pin, the target time to generate next output signal. \;\;\;" subnode="uint64" access="RW" offset="0x28.0" size="0x8.0" />
	<field name="out_pulse_duration" descr="Output pulse duration in units of mSec. \;Range is 1 to 1000. \;Reserved when pin_mode != ptp_out\;In case the set value is 0, device default will be used.\;" access="RW" offset="0x30.16" size="0x0.16" />
</node>

<node name="mtpptr_ext" descr="" size="0x50.0" >
	<field name="dir" descr="Direction\;0: Ingress\;1: Egress" access="INDEX" offset="0x0.0" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="local_port\;Not supported for CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ovf" descr="Overflow\;The HW timestamp FIFO had an overflow\;The overflow state is cleared when clr = 1" access="RO" offset="0x4.0" size="0x0.1" />
	<field name="read_one" descr="Read up to one record\;May response with num_rec = 0 or 1\;" access="OP" offset="0x4.30" size="0x0.1" />
	<field name="clr" descr="Clear the records" access="OP" offset="0x4.31" size="0x0.1" />
	<field name="num_rec" descr="Number of valid records in the response\;When read_one = 1 then this equals to 1 and only 1 record responded, even if the HW FIFO has more than 1 record\;Range 0.. cap_ptp_timestamp_fifo" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="record" descr="Records, see Table 1280, &quot;MTPPTR - Record Layout,&quot; on page 1394" subnode="mtpptr_record_ext" access="RW" high_bound="3" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mtpptr_record_ext" descr="" size="0x10.0" >
	<field name="domain_number" descr="domainNumber field as defined by IEEE 1588" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="message_type" descr="MessageType field as defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="sequence_id" descr="SequenceId field as defined by IEEE 1588" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="timestamp_high" descr="Timestamp of when the PTP packet has passed through the port\;Units of PLL clock time\;For Spectrum-1 the PLL clock is 156.25Mhz and PLL clock time is 6.4nSec" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="timestamp_low" descr="Timestamp of when the PTP packet has passed through the port\;Units of PLL clock time\;For Spectrum-1 the PLL clock is 156.25Mhz and PLL clock time is 6.4nSec" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="mtpspu_ext" descr="" size="0x8.0" >
	<field name="message_type" descr="Set UTC on packets from CPU for PTP packets with the configured message_types.\;This is a necessary but insufficient condition since need to enable also per port. See Section 5.5.4, &quot;MTPCPC - Monitoring Time Precision Correction Port Configuration&quot;, on page 1397\;Message types are defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)\;\;Valid bits are 0-3 only.\;Bits 4-15 are reserved as TS shall not be applied to general messages." access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="mtptpt_ext" descr="" size="0x8.0" >
	<field name="trap_id" descr="Trap id:\;0: PTP0\;1: PTP1\;2: PTP_IBG1\;See Table 1041, &quot;PTP Traps,&quot; on page 1331 for details on which opcode is supported per device" access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="message_type" descr="Bitwise vector of PTP message types to trap. This is a necessary but non-sufficient condition since need to enable also per port. See Section 5.5.1, &quot;MTPPPC - Monitoring Time Precision Packet Port Configuration&quot;, on page 1391\;Message types are defined by IEEE 1588\;Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)" access="RW" offset="0x4.0" size="0x0.16" />
</node>

<node name="mtrc_cap_reg_ext" descr="" size="0x84.0" >
	<field name="num_string_db" descr="Number of different string sections building the database" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="trc_ver" descr="Indicates the version of the tracing mechanism.\;0x0: VER_0\;0x1: VER_1\;Other values are reserved.\;Reserved in Switch" access="RO" offset="0x0.24" size="0x0.2" />
	<field name="trace_to_memory" descr="When set the device supports logging traces to memory\;0: FIFO Mode\;1: Host Memory Mode" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="trace_owner" descr="Write 0x1 to register for tracer ownership, write 0x0 to de-register.\;Read value 0x1 indicates tracer ownership is granted.\;" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="num_string_trace" descr="The number of consecutive event_id that should be interpreted as a string trace" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="first_string_trace" descr="The lowest event_id that should be interpreted as a string trace" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="log_max_trace_buffer_size" descr="Log 2 of the maximal size of the trace buffer given in units of 4KB" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="tracer_capabilities" descr="Tracer suppported capbailities bitmask:\;0: FIFO.\;1: MEM mode.\;else, reserved." access="RO" offset="0x8.30" size="0x0.2" />
	<field name="string_db_param" descr="String DB section parameters." subnode="string_db_parameters_ext" access="RO" high_bound="7" low_bound="0" offset="0x10.0" size="0x40.0" />
</node>

<node name="mtrc_conf_reg_ext" descr="" size="0x80.0" >
	<field name="trace_mode" descr="Tracing mode\;0x0: FIFO\;0x1: TRACE_TO_MEMORY\;Other values are reserved." access="RW" offset="0x0.0" size="0x0.4" />
	<field name="log_trace_buffer_size" descr="Log 2 of the Size of the trace buffer, given in units of 4KB.\;Value should not exceed log_max_trace_buffer_size.\;Valid only for trace_mode TRACE_TO_MEMORY.\;Modifying this parameter after the tracer was active may cause loss of sync regarding the location of the next trace." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="trace_mkey" descr="MKey registered for the trace buffer access.\;Valid only for trace_mode TRACE_TO_MEMORY.\;Modifying this parameter after the tracer was active may cause loss of sync regarding the location of the next trace.\;Reserved for Switches." access="RW" offset="0x8.0" size="0x4.0" />
</node>

<node name="mtrc_ctrl_reg_ext" descr="" size="0x40.0" >
	<field name="modify_field_select" descr="Field select indicated which writable fields to modify\;bit 0: trace_status\;Other bits are reserved." access="WO" offset="0x0.0" size="0x0.16" />
	<field name="arm_event" descr="When set, an event will be generated if new Tracer events were logged since last event.\;Reserved in Switches." access="WO" offset="0x0.27" size="0x0.1" />
	<field name="trace_status" descr="Current status of the tracer\;0x0: DISABLED - logging traces is stopped\;0x1: ACTIVE - logging traces is active" access="RW" offset="0x0.30" size="0x0.2" />
	<field name="current_timestamp_52_32" descr="MSB of the current timesatmp counter" access="RO" offset="0x8.0" size="0x0.21" />
	<field name="current_timestamp_31_0" descr="LSB of the current timesatmp counter" access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="mtrc_stdb_reg_ext" descr="" size="0xc.0" >
	<field name="read_size" descr="The number of bytes to read from the String DB. The number of bytes must:\;Be a multiple of 64B\;Not exceed the String DB section (with start_offset)\;Not exceed the limitations defined by the medium carrying the Register." access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="string_db_index" descr="The section of the String DB being accessed" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="start_offset" descr="The offset in the String DB to read from, given in Bytes. The offset must:\;Be a multiple of 64B\;Not exceed the String DB section (with read_size)" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="string_db_data" descr="Strings from the database. The size of this field is defined by read_size" access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x8.0" size="0x4.0" size_condition="$(parent).read_size" />
</node>

<node name="mtrc_stdb_v2_ext" descr="" size="0x5a0.0" >
	<field name="read_size" descr="The number of bytes to read from the String DB. The number of bytes must:\;Be a multiple of 64B\;Not exceed the String DB section (with start_offset)\;Not exceed the limitations defined by the medium carrying the Register." access="INDEX" offset="0x0.0" size="0x0.24" />
	<field name="string_db_index" descr="The section of the String DB being accessed" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="start_offset" descr="The offset in the String DB to read from, given in Bytes. The offset must:\;Be a multiple of 64B\;Not exceed the String DB section (with read_size)" access="INDEX" offset="0x4.0" size="0x4.0" />
	<field name="string_db_data" descr="Strings from the database. The size of this field is defined by read_size" access="RO" high_bound="357" low_bound="0" offset="0x8.0" size="0x598.0" />
</node>

<node name="mtutc_reg_ext" descr="" size="0x1c.0" >
	<field name="operation" descr="Operation:\;\;1: SET_TIME_IMMEDIATE\;2: ADJUST_TIME\;3: ADJUST_FREQ_UTC \;4: ADJUST_FREQ_FRC - Free Running Clock (DWIP and Switch only)\;5: ADJUST_FREQ_BOTH - (DWIP and Switch only)\;6: ADJUST_PHASE - Supported only if MCAM.mng_feature_cap_mask bit 54 is set." access="OP" enum="SET_TIME_IMMEDIATE=0x1,ADJUST_TIME=0x2,ADJUST_FREQ_UTC=0x3,ADJUST_FREQ_FRC=0x4,ADJUST_FREQ_BOTH=0x5,ADJUST_PHASE=0x6" offset="0x0.0" size="0x0.4" />
	<field name="log_max_phase_adjustment" descr="[DWIP]\;range is from -(2^ log_max_phase_adjustment) to +2^ log_max_phase_adjustment) in units of ns." access="RO" offset="0x0.5" size="0x0.6" />
	<field name="log_max_freq_adjustment" descr="If 0: Range is from -50,000,000 ppb to +50,000,000 ppb.\;Otherwise: range is from -(2^log_max_freq_adjustment) ppb to +2^log_max_freq_adjustment ppb.\;" access="RO" offset="0x0.16" size="0x0.5" />
	<field name="freq_adj_units" descr="Updated when operation is ADJUST_FREQ.\;\;0: units_are_ppb - every PPS the HW frequency will be adjusted by this value\;1: units_are_parts_per_million - but with a 16 bit binary fractional field\;2: units_are_parts_per_billion - but with a 16 bit binary fractional field" access="RW" enum="units_are_ppb=0x0,units_are_parts_per_million=0x1,units_are_parts_per_billion=0x2" offset="0x0.24" size="0x0.3" />
	<field name="freq_adjustment" descr="Units are per MTUTC.freq_adj_units value. Frequency adjustment: Every PPS the HW frequency will be adjusted by this value. \; field.\;Updated when operation is ADJUST_FREQ\;\;Range is from -50,000,000 ppb to +50,000,000 ppb" access="RW" offset="0x4.0" size="0x4.0" />
	<field name="utc_sec" descr="UTC seconds\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x10.0" size="0x4.0" />
	<field name="utc_nsec" descr="UTC nSecs\;Range 0..(10^9-1)\;Updated when operation is SET_TIME_IMMEDIATE" access="WO" offset="0x14.0" size="0x0.30" />
	<field name="time_adjustment" descr="Time or phase adjustment\;Updated when operation is ADJUST_TIME or ADJUST_PHASE.\;\;When ADJUST_TIME:\;Time adjustment, Units of nSec, Range is from -32768 to 32768.\;If MCAM.time_adjust_range_extended==1, range is from \;\;\;\;When ADJUST_PHASE:\;Phase adjustment, Units of nSec, Range is according to log_max_ phase_adjustment field.\;" access="WO" offset="0x18.0" size="0x4.0" />
</node>

<node name="mtwe_ext" descr="" size="0x10.0" >
	<field name="sensor_warning" descr="Bit vector indicating which of the sensor reading is above threshold.\;Address 00h bit31 is sensor_warning[127]\;Address 0Ch bit0 is sensor_warning[0]" access="RO" high_bound="3" low_bound="0" offset="0x0.0" size="0x10.0" />
</node>

<node name="mvcap_reg_ext" descr="" size="0x10.0" >
	<field name="sensor_map" descr="Mapping of system sensors supported by the device. Each bit represents a sensor. \;Sensor mapping is based on the sensor_map_type\;0: Not connected or not supported\;1: Supports voltage and current measurements" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="slot_index" descr="Slot index\;0: Main board" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="sensor_map_type" descr="[DWIP]\;0: Sensors 0-63.\;1: Sensors 64-127.\;2: Sensors 128-191." access="INDEX" offset="0x8.28" size="0x0.2" />
</node>

<node name="mvcr_ext" descr="" size="0x18.0" >
	<field name="sensor_index" descr="Sensors:\;- 0..max_system_sensors-1 are ambient sensors on the system (max_system_sensors from INI)\;[DWIP][Switch_internal]: 64..154 are mapped to modules by 1:1 e.g. module 1 is index 65\;\;" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="slot_index" descr="Slot index\;0: Main board\;" access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="curr_cap" descr="0: Sensor does not support current reading\;1: Sensor supports current reading" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="volt_cap" descr="0: Sensor does not support voltage reading\;1: Sensor supports voltage reading" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="voltage_sensor_value" descr="Voltage reading from the sensor. \;Voltage units are 0.01V." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="current_sensor_value" descr="Current reading from the sensor lsb.\;Current units are 0.01A." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="current_sensor_value_msb" descr="Current reading from the sensor msb.Current units are 0.01A." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="sensor_name" descr="Sensor Name\;8 character long sensor name.\;\;" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="over_voltage_stressor_parameters_ext" descr="" size="0x8.0" >
	<field name="over_votlage_percentage_change" descr="The percentage change in 1% units\;If percentage change is over 1 percentage point or change from previous request, FW will return BAD PARAM" access="RW" offset="0x0.0" size="0x0.6" />
</node>

<node name="paos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:\;1: up\;2: down\;4: down_by_port_failure - (transitioned by the hardware)\;  \;" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x0.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):\;1: up\;2: down_by_configuration\;4: disabled_by_system - this mode cannot be set by the software, only by the hardware.\;6: sleep - can be configured only if sleep_cap is set. Note that a sleep setting will cause the port to transition immediately into sleep state regardless of previous admin_status.\;" access="RW" enum="up=0x1,down_by_configuration=0x2,disabled_by_system=0x4,sleep=0x6" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="e" descr="Event generation on operational state change (oper_status):\;0: Do_not_generate_event\;1: Generate_Event \;2: Generate_Single_Event\;\;Not Supported for HCA." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="physical_state_status" descr="IB Port Physical operational (actual) link state:\;0: N/A\;1: Sleep\;2: Polling\;3: Disabled\;4: PortConfigurationTraining\;5: LinkUp\;6: LinkErrorRecovery\;All others reserved\;Note that physical state of 1,2,3,4 will all be reflected as oper_status = down.\;LinkUp for Ethernet link refers to PhyUp state where local side is ready, but not necessarily that peer side is also ready." access="RO" enum="N_A=0x0,Sleep=0x1,Polling=0x2,Disabled=0x3,PortConfigurationTraining=0x4,LinkUp=0x5,LinkErrorRecovery=0x6" offset="0x4.4" size="0x0.4" />
	<field name="fd" descr="Force down.\;Supported only when indicated in PCAM\;Can be set only with admin_status = 2 (&apos;down_by_configuration&apos;), will force link to be down. \;" access="RW" offset="0x4.8" size="0x0.1" />
	<field name="sleep_cap" descr="Sleep capability:\;0: Sleep state is not supported\;1: Sleep state supported" access="RO" offset="0x4.9" size="0x0.1" />
	<field name="ps_e" descr="Event generation for physical state.\;On set operation, will be ignored if ee_ps is not set.\;When bit is set, will generate an event for transition into state.\;Bit 0: Sleep\;Bit 2: Disabled\;Bit 3: PortConfigurationTraining\;Not Supported for HCA." access="RW" enum="Sleep=0x1,Disabled=0x4,PortConfigurationTraining=0x8" offset="0x4.12" size="0x0.4" />
	<field name="logical_state_status" descr="IB or NVLink Port Logical link state:\;0: N/A\;1: Down\;2: Init\;3: Arm\;4: Active" access="RO" enum="N_A=0x0,Down=0x1,Init=0x2,Arm=0x3,Active=0x4" offset="0x4.16" size="0x0.3" />
	<field name="ls_e" descr="event generation mask for logical state.\;On set operation, will be ignored when ee_ls is not set.\;When bit is set, will generate event for transition into state.\;Bit 0: Down\;Bit 1: Init\;Bit 2: Arm\;Bit 3: Active\;Not Supported for HCA." access="RW" enum="Down=0x1,Init=0x2,Arm=0x4,Active=0x8" offset="0x4.20" size="0x0.4" />
	<field name="ee_nmxas" descr="Event update enable for NMX AdminState. If this bit is set, event generation will be updated based on the nmxas_e field. Only relevant on Set operations.\;Not Supported for HCA.\;" access="WO" offset="0x4.27" size="0x0.1" />
	<field name="ee_ps" descr="Event update enable for physical state. If this bit is set, event generation will be updated based on the ps_e field. Only relevant on Set operations.\;Not Supported for HCA." access="WO" offset="0x4.28" size="0x0.1" />
	<field name="ee_ls" descr="Event update enable for logical state. If this bit is set, event generation will be updated based on the ls_e field. Only relevant on Set operations.\;Not Supported for HCA." access="WO" offset="0x4.29" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.\;Not Supported for HCA." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin state update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
	<field name="nmx_adminstate_status" descr="NVLink Port NMX AdminState current state:\;0: N/A\;1: Up\;2: Down\;3: Diag\;" access="RO" enum="N_A=0x0,Up=0x1,Down=0x2,Diag=0x3" offset="0x8.0" size="0x0.3" />
	<field name="nmxas_e" descr="Event generation mask for NMX AdminState status.\;On set operation, will be ignored when ee_nmxas is not set.\;When bit is set, will generate event for transition into state.\;\;Bit 0: Up\;Bit 1: Down\;Bit 2: Diag\;\;" access="RW" enum="Up=0x1,Down=0x2,Diag=0x4" offset="0x8.4" size="0x0.4" />
	<field name="ps_e_ext" descr="Extension of ps_e field. Event generation for physical state.\;On set operation, will be ignored if ee_ps is not set.\;When bit is set, will generate an event for transition into state.\;Bit 0: Polling\;Bit 1: Reserved\;" access="RW" enum="Polling=0x1,Reserved=0x2" offset="0x8.12" size="0x0.2" />
	<field name="last_oper_status" descr="Supported if PCAM.feature_cap_mask bit 118 is set\;Last reported oper state in PUDE:\;0: no_info\;1: up\;2: down\;4: down_by_port_failure - (transitioned by the hardware)" access="RO" enum="up=0x1,down=0x2,down_by_port_failure=0x4" offset="0x8.16" size="0x0.3" />
</node>

<node name="pbmc_reg_ext" descr="" size="0x6c.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="xoff_refresh" descr="The time before a new pause frame should be sent to refresh the pause state. Using the same units as xoff_timer_value above." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="xoff_timer_value" descr="When device generates a pause frame, it uses this value as the pause timer.\;The pause timer is measured in units of pause &quot;quanta&quot;, where each unit is equal to 512 bit times." access="RW" offset="0x4.16" size="0x0.16" />
	<field name="port_buffer_size" descr="Total packet buffer array available for the port. The sum of buffer array allocated to bufferX must not exceed port_buffer_size.\;In Spectrum and above- Max supported Headroom buffer for port. \;" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fullness_threshold" descr="Almost full threshold configuration.\;Percentage of buffer fullness which indicates &quot;almost full&quot; occurrence\;Range: 0-100%\;Reserved for Switches." access="RW" offset="0x8.16" size="0x0.7" />
	<field name="buffer" descr="Configuring per-buffer parameters. i=0..9.\;See Table 1068, &quot;BufferX Register Layout,&quot; on page 1149" subnode="bufferx_reg_ext" access="RW" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="shared_headroom_pool" descr="Configuring shared headroom pool parameters. Using the same layout as in BufferX.\;Not supported in SwitchX and SwitchX-2\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit).\;See Table 1068, &quot;BufferX Register Layout,&quot; on page 1149" subnode="bufferx_reg_ext" access="RW" offset="0x5C.0" size="0x8.0" />
	<field name="port_shared_buffer" descr="Configuring port shared buffer parameters. Using the same layout as in BufferX.\;Not supported in SwitchX and SwitchX-2\;Valid for HCA when pbmc_port_shared_buffer is set in PCAM.\;See Table 1068, &quot;BufferX Register Layout,&quot; on page 1149" subnode="bufferx_reg_ext" access="RW" offset="0x64.0" size="0x8.0" />
</node>

<node name="pbsr_reg_ext" descr="" size="0x64.0" >
	<field name="buffer_type" descr="Valid only for 8x port setting (see Table 588, &quot;PMLP - Ports Module to Local Port Register Fields,&quot; on page 620)\;1: Main buffer\;2: Secondary buffer" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear_wm_buff_mask" descr="Each bit represents a stat_buffer\;per bit:\;0: do not clear watermark\;1: clear watermark\;Reserved when clear_wm = 1" access="OP" offset="0x4.0" size="0x0.10" />
	<field name="used_shared_headroom_buffer" descr="Number of currently used shared headroom buffer cells." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="clear_wm" descr="Clear watermarks for all PGs" access="OP" offset="0x8.31" size="0x0.1" />
	<field name="stat_buffer" descr="status per-buffer parameters. i=0..9\;" subnode="stat_bufferx_reg_ext" access="RO" high_bound="9" low_bound="0" offset="0xC.0" size="0x50.0" />
	<field name="stat_shared_headroom_pool" descr="status of shared headroom pool parameters. Using the same layout as in stat_BufferX, for details see Table 1081, &quot;stat_bufferX Register Layout,&quot; on page 1168.\;Not supported in SwitchX and SwitchX-2\;Not supported in HCA (See PCAM shp_pbmc_pbsr_support bit). \;Not supported in GPUNet" subnode="stat_bufferx_reg_ext" access="RO" offset="0x5C.0" size="0x8.0" />
</node>

<node name="pbwc_ext" descr="" size="0x8.0" >
	<field name="log_time_interval" descr="Log time interval.\;This field determine the time between measurements T:\;T = (2^log_time_interval) * 64uSec\;Default is 7, means that T = (2^7) * 64uSec = 8mSec.\;\;For SPC4, and SPC5, the range is dependent on the port&apos;s rate:\;800Gbps: 0..10\;400Gbps: 0..10\;200Gbps: 0..11\;100Gbps: 0..12\;50Gbps: 0..13\;25Gbps: 0..14\;10Gbps: 0..15\;\;" access="RW" offset="0x0.0" size="0x0.4" />
	<field name="alpha_factor" descr="Alpha for the exponential moving average formula.\;Alpha = 1/(2^alpha_factor)\;Range 0..7\;\;Default is 2" access="RW" offset="0x4.0" size="0x0.3" />
</node>

<node name="pbwr_ext" descr="" size="0x94.0" >
	<field name="local_port_bitmap" descr="Local port\;Each bit represents a local port. Refer to Section 9.3, &quot;Port Numbering&quot;, on page 1899 for port numbering scheme.\;Ports order in the bitmask is from bottom to top. e.g for setting local port 1, bit 1 in the last DWORD (offset 0x7Ch) should be set.\;CPU port is not supported.\;Router port is not supported" access="INDEX" high_bound="31" low_bound="0" offset="0x0.0" size="0x80.0" />
	<field name="num_rec" descr="Number of records.\;Range 0..1024.\;Range 1025..2047 is reserved." access="OP" offset="0x80.0" size="0x0.11" />
	<field name="dir" descr="Direction:\;0: ingress\;1: egress" access="INDEX" enum="ingress=0x0,egress=0x1" offset="0x80.31" size="0x0.1" />
	<field name="bw_record" descr="BW of the corresponding local port. Valid only if the corresponding bit at local_port_bitmap is set (1).\;The units of the BW are determined by Table 1119, &quot;PBWC - Port BW Configuration Register Layout,&quot; on page 1202.\;" access="RO" arr_is_dynamic="1" high_bound="VARIABLE" low_bound="0" offset="0x90.0" size="0x4.0" size_condition="$(parent).num_rec" />
</node>

<node name="pcam_reg_ext" descr="" size="0x50.0" >
	<field name="access_reg_group" descr="Access Register ID groups\;0: RegID_0x5000_to_0x507F\;1: RegID_0x5080_to_50FF\;Values 2-255 are Reserved" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="pl_op" descr="Reserved for non-planarized port.\;Features and access regs will be presented according to:\;0: aggregated_port_access\;1: plane_port_access" access="OP" enum="aggregated_port_access=0x0,plane_port_access=0x1" offset="0x0.8" size="0x0.1" />
	<field name="feature_group" descr="Feature list mask index: \;0: enhanced_features \;Values 1 - 255 are Reserved" access="INDEX" enum="enhanced_features=0x0" offset="0x0.16" size="0x0.8" />
	<field name="port_access_reg_cap_mask" descr="Supported port&apos;s access register bitmaks. Based on access_reg_group index.\;When bit is set. The register is supported in the device. \;When access_reg_group == 0 :\;Bit_0: 0x5000 \;Bit_1: 0x5001 (PCAP)\;Bit_2: 0x5002 (PMLP)\;Bit_3: 0x5003 (PMTU)\;Bit_4: 0x5004 (PTYS)\;Bit_127: 0x507F (PCAM)" access="RO" high_bound="3" low_bound="0" offset="0x8.0" size="0x10.0" />
	<field name="feature_cap_mask" descr="Supported port&apos;s enhanced features. Based on feature_group index. When bit is set, The feature is supported in the device:\;Bit 0: PPCNT_counter_group_Phy_statistical_counter_group \;Bit 1 - PPCNT_counter_group_Discard_counter_group\;Bit 9: PFCC - support of stall mask and global rx,tx mask. \;Bit 10: PMCR - support of tx_disable override.\;Bit 11: PPCNT_counter_group - IB Extended port counter group\;Bit 12: PPCNT_Extended_Ethernet_group - tx packet size histograms\;Bit 13: PTYS_extended_Ethernet_support\;Bit 14: PMAOS_reset_toggle_support\;Bit 15: Set_Module_low_power_supported \;Bit 16: Module_power_optimization_is_supported_in_PPSC\;Bit 17: Support_of_IB_force_state_machine_in_PTYS - (an_disable)\;Bit 18: PPCNT_Extended_Ethernet_group_icrc_counter\;Bit 19: cm2_en_is_supported_in_PCAP\;Bit 20: time_tolink_up_is_supported_in_PDDR\;Bit 21: gearbox_die_num_field_is_supported_in_PMDR\;Bit 22: force_entropy_entropy_calc_entropy_gre_calc - and capability bits are supported in PCMR\;Bit 23: FEC_override_support_for_50G_per_lane_is_supported_in_PPLM\;Bit 25: PTYS_allow_both_extended_and_legacy_protocol_masks\;Bit 26: PPCNT_eth_per_tc_cong_group_supported\;Bit 27: pnat_sup_host - the device supports pnat = 2 (host) when set to &apos;1&apos;\;Bit 28: ppcnt_no_buffer_discard_uc - this counter is supported in PPCNT when set to &apos;1&apos;\;Bit 29: pbmc_port_shared_buffer - supported in PBMC.\;Bit 30: PLR_max_retry_window_support - PPCNT group 0x22 max retry per window\;Bit 32: PDDR_ext_eth_proto_support\;Bit 41: PMAOS - support of &quot;opertional_notifcation&quot; field\;Bit 42: PRBS_polarity_support - support of polarity bits in PPTT and PPRT\;Bit 43: PDDR_register_is_supported\;Bit 44: pfcc_buffer_onwership - PFCC buffer ownership is supported.\;Bit 45: force_down - supported in PAOS reg.\;Bit 46: pmlp_lane_mapping_off - Support of m_lane_m field in PMLP.\;Bit 51: ppcnt_symobl_ber\;Bit 52: shp_pbmc_pbsr_support\;Bit 54: ppcnt_effective_error_counter\;Bit 55: FEC_override_support_for_100G_per_lane_is_supported_in_PPLM\;Bit 57: PMECR_option_to_not_generate_events_upon_PMLP_set\;Bit 64: Local_port_MSB - bits [9:8] supported\;Bit 65: PDDR_moule_latched_info_page_supported\;Bit 66: PDDR_module_info_ext_supported\;Bit 70: SLTP_tx_policy_supported\;Bit 71: pmcr_capability_bits_supported\;Bit 72: pmtu_max_admin_mtu_supported\;Bit 73: PPCNT_grp_profile_supported\;Bit 77: PPCNT.physical_layer_counters_RS_FEC_8_lanes_supported\;Bit 85: PPCNT.counters_cap\;Bit 86: SLTP.lane_broadcast_supported\;Bit 87: PMMP.apply_im_supported\;Bit 91: SLRG.all_lanes_supported\;Bit 92: PIPG.ipg_oper_ipg_cap_idx_supported\;Bit 93: PPBMP_clr_supported\;Bit 94: PIPG.dic1_1g_supported\;Bit 98: FEC_override_support_for_200G_per_lane_is_supported_in_PPLM\;Bit 99: PUDE.local_reason_opcode_supported\;Bit 101: PPCNT.physical_layer_counters.intentional_unintentional_link_down_events_supported\;Bit 102: PAOS.nmx_adminstate_status_fields_supported\;Bit 103: PFCC.cable_length_supported\;Bit 104: PDDR.link_up_info_page_1ch_to_2ch_counters_supported\;Bit 107: PFCC.packet_ratio_supported\;Bit 109: PPCNT.Physical_Layer_Counters.data/serdes_received_bits_counters\;Bit 111: PPCNT.physical_layer_recovery_counters_supported\;Bit 112: PMLP.lane_label_mapping_supported\;Bit 113: PPCNT.physical_layer_counters.estimated_effective_ber_supported\;Bit 114 PPCNT.physical_layer_counters.ucr_ber_supported\;Bit 116: PMLP.bidi_map_bit_supported\;Bit 117: PDDR.link_down_info_page.recovery_entry_reason_supported\;Bit 118: PAOS.last_oper_state_supported\;Bit 119: PPCNT.rs_fec_uncorrectable_during_recovery_supported\;Bit 120: PDDR.operational_info_page.test_mode_fsm_state_supported\;Other bits are reserved" access="RO" enum="PPCNT_counter_group_Phy_statistical_counter_group=0x1,PFCC=0x200,PMCR=0x400,PPCNT_counter_group=0x800,PPCNT_Extended_Ethernet_group=0x1000,PTYS_extended_Ethernet_support=0x2000,PMAOS_reset_toggle_support=0x4000,Set_Module_low_power_supported=0x8000,Module_power_optimization_is_supported_in_PPSC=0x10000,Support_of_IB_force_state_machine_in_PTYS=0x20000,PPCNT_Extended_Ethernet_group_icrc_counter=0x40000,cm2_en_is_supported_in_PCAP=0x80000,time_tolink_up_is_supported_in_PDDR=0x100000,gearbox_die_num_field_is_supported_in_PMDR=0x200000,force_entropy_entropy_calc_entropy_gre_calc=0x400000,FEC_override_support_for_50G_per_lane_is_supported_in_PPLM=0x800000,PTYS_allow_both_extended_and_legacy_protocol_masks=0x2000000,PPCNT_eth_per_tc_cong_group_supported=0x4000000,pnat_sup_host=0x8000000,ppcnt_no_buffer_discard_uc=0x10000000,pbmc_port_shared_buffer=0x20000000,PLR_max_retry_window_support=0x40000000,PDDR_ext_eth_proto_support=0x1,PMAOS=0x200,PRBS_polarity_support=0x400,PDDR_register_is_supported=0x800,pfcc_buffer_onwership=0x1000,force_down=0x2000,pmlp_lane_mapping_off=0x4000,ppcnt_symobl_ber=0x80000,shp_pbmc_pbsr_support=0x100000,ppcnt_effective_error_counter=0x400000,FEC_override_support_for_100G_per_lane_is_supported_in_PPLM=0x800000,PMECR_option_to_not_generate_events_upon_PMLP_set=0x2000000,Local_port_MSB=0x1,PDDR_moule_latched_info_page_supported=0x2,PDDR_module_info_ext_supported=0x4,SLTP_tx_policy_supported=0x40,pmcr_capability_bits_supported=0x80,pmtu_max_admin_mtu_supported=0x100,PPCNT_grp_profile_supported=0x200,PPCNT_physical_layer_counters_RS_FEC_8_lanes_supported=0x2000,PPCNT_counters_cap=0x200000,SLTP_lane_broadcast_supported=0x400000,PMMP_apply_im_supported=0x800000,SLRG_all_lanes_supported=0x8000000,PIPG_ipg_oper_ipg_cap_idx_supported=0x10000000,PPBMP_clr_supported=0x20000000,PIPG_dic1_1g_supported=0x40000000,FEC_override_support_for_200G_per_lane_is_supported_in_PPLM=0x4,PUDE_local_reason_opcode_supported=0x8,PPCNT_physical_layer_counters_intentional_unintentional_link_down_events_supported=0x20,PAOS_nmx_adminstate_status_fields_supported=0x40,PFCC_cable_length_supported=0x80,PDDR_link_up_info_page_1ch_to_2ch_counters_supported=0x100,PFCC_packet_ratio_supported=0x800,PPCNT_physical_layer_recovery_counters_supported=0x8000,PMLP_lane_label_mapping_supported=0x10000,PPCNT_physical_layer_counters_estimated_effective_ber_supported=0x20000,PMLP_bidi_map_bit_supported=0x100000,PDDR_link_down_info_page_recovery_entry_reason_supported=0x200000,PAOS_last_oper_state_supported=0x400000,PPCNT_rs_fec_uncorrectable_during_recovery_supported=0x800000,PDDR_operational_info_page_test_mode_fsm_state_supported=0x1000000" high_bound="3" low_bound="0" offset="0x28.0" size="0x10.0" />
</node>

<node name="pcap_reg_ext" descr="" size="0x14.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cm2_en" descr="port_capability_mask[95:80] is supported if set to &apos;1&apos;." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="port_capability_mask" descr="Sets the PortInfoCapabilityMask:\;Specifies the supported capabilities of this node. A bit set to 1 for affirmation of supported capability.\;port_capability_mask[127:96] is mapped to CapabilityMask in PortInfo MAD.\;port_capability_mask[95:80] is mapped to CapabilityMask2 in PortInfo MAD.\;\;\;" access="RW" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
</node>

<node name="pcmr_reg_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fcs_cap" descr="Specifies the check enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability: \;FCS check disable/enable capability" access="RO" offset="0x4.1" size="0x0.1" />
	<field name="rx_ts_over_crc_cap" descr="Specifies the ingress timestamps enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.13" size="0x0.1" />
	<field name="rx_fcs_drop_cap" descr="Specifies the ingress drop enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.14" size="0x0.1" />
	<field name="tx_fcs_recalc_cap" descr="Specifies the egress drop enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.15" size="0x0.1" />
	<field name="tx_ts_over_crc_cap" descr="Specifies the egress timestamps enable/disable capabilities of the local port. A bit set to 1 for affirmation of supported enable/disable capability" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="fcs_chk" descr="FCS check\;Values:\;0: disable check. \;1: perform check\;Note: when disabling a check, it will also affects the relevant counters." access="RW" offset="0x8.1" size="0x0.1" />
	<field name="rx_ts_over_crc" descr="RX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Note: \;1. If this field is changed while traffic is passing then some packets may be dropped due to incorrect FCS.\;2. Default value is (1) - TS over FCS\;Reserved when GPUNet" access="RW" offset="0x8.13" size="0x0.1" />
	<field name="rx_fcs_drop" descr="RX FCS drop control:\;0: ingress port will drop a packet with bad FCS (Default)\;1: ingress port will not drop a packet with bad FCS\;NOTE: All FCS counters (PPCNT) are valid for both drop modes.\;NOTE: Reserved when PCMR.fcs_cap=1 &amp; PCMR.fcs_chk=0" access="RW" offset="0x8.14" size="0x0.1" />
	<field name="tx_fcs_recalc" descr="TX FCS recalculation:\;0: egress port will recalculate and overwrite FCS value (Default) \;1: egress port will not overwrite FCS value \;NOTE: when this bit is set, any modification of the packet will result in a bad FCS.\;Reserved when GPUNet" access="RW" offset="0x8.15" size="0x0.1" />
	<field name="tx_ts_over_crc" descr="TX TimeStamp over FCS\;0: no TS over FCS\;1: TS over FCS\;Reserved when tx_fcs_recalc is set\;Reserved when GPUNet" access="RW" offset="0x8.16" size="0x0.1" />
</node>

<node name="pd_link_eth_enabled_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pd_link_ib_enabled_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_c2p_link_enabled_eth_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_c2p_link_enabled_ib_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_proto_enabled" descr="bi link enabled speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="core_to_phy_link_width_enabled" descr="IB link enabled width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_c2p_link_enabled_nvlink_ext" descr="" size="0x4.0" >
	<field name="core_to_phy_link_nvlink_enabled" descr="NVLink protocols admin state\;see: Table  491, &quot;PTYS - Extended Protocol NVLink - admin layout,&quot; on page  485" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_eth_ext" descr="" size="0x4.0" >
	<field name="cable_ext_eth_proto_cap" descr="Cable Ethernet protocols cap. If PTYS.ext_eth_proto_cap filed is supported, use for opcode definition PTYS.ext_eth_proto_capIf PTYS.ext_eth_proto_capability mask is empty, use For opcode definition PTYS.eth_proto_cap." access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_cable_cap_ib_ext" descr="" size="0x4.0" >
	<field name="cable_link_speed_cap" descr="Cable support IB speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="cable_link_width_cap" descr="Cable support IB width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_cable_cap_nvlink_ext" descr="" size="0x4.0" >
	<field name="cable_nvlink_proto_cap" descr="Cable NVLink protocols cap:\;See: Table  489, &quot;PTYS - Extended Protocol NVLink - cap/oper layout,&quot; on page  484" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_active_eth_ext" descr="" size="0x4.0" >
	<field name="link_eth_active" descr="Ethernet protocols active: see PTYS.ext_eth_proto_oper" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_active_ib_ext" descr="" size="0x4.0" >
	<field name="link_speed_active" descr="IB link active speed:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x0.0" size="0x0.16" />
	<field name="link_width_active" descr="IB link active width:\;Bit 0: 1x\;Bit 1: 2x\;Bit 2: 4x\;\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_link_active_nvlink_ext" descr="" size="0x4.0" >
	<field name="link_nvlink_active" descr="NVLink protocols active\;See: Table  489, &quot;PTYS - Extended Protocol NVLink - cap/oper layout,&quot; on page  484" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_link_down_info_page_ext" descr="" size="0xf4.0" >
	<field name="down_blame" descr="Which receiver caused last link down: \;0: Unknown\;1: Local_phy\;2: Remote_phy" access="RO" enum="Unknown=0x0,Local_phy=0x1,Remote_phy=0x2" offset="0x0.0" size="0x0.4" />
	<field name="down_intent" descr="For the last link down reason, indicates if the link drop was intentional (e.g port down command, cable unplug etc...) or unintentional (e.g Bad SI).\;down_intent is updated on the link drop according to local reason information and updated again on LinkUp according to local + peer down reason (only if negotiation took place during linkup flow)" access="RO" offset="0x0.4" size="0x0.4" />
	<field name="local_reason_opcode" descr="Opcode of link down reason for local / remote side / last successful recovery entry reason: \;Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is set\;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Cable_Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Peer_side_down_to_sleep_state\;33: Peer_side_down_to_disable_state\;34: Peer_side_down_to_disable_and_port_lock\;35: Peer_side_down_due_to_thermal_event\;36: Peer_side_down_due_to_force_event\;37: Peer_side_down_due_to_reset_event\;38: Reset_no_power_cycle\;39: Fast_recovery_tx_plr_trigger\;40: Down_due_to_HW_force_event\;42: L1_exit_failure\;43: too_many_link_error_recoveries\;44: Down_due_to_contain_mode\;45: BW_loss_threshold_exceeded\;46: ELS_laser_fault\;47: Hi_SER" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="recovery_entry_reason" descr="Opcode of link down reason for local / remote side / last successful recovery entry reason: \;Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is set\;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Cable_Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Peer_side_down_to_sleep_state\;33: Peer_side_down_to_disable_state\;34: Peer_side_down_to_disable_and_port_lock\;35: Peer_side_down_due_to_thermal_event\;36: Peer_side_down_due_to_force_event\;37: Peer_side_down_due_to_reset_event\;38: Reset_no_power_cycle\;39: Fast_recovery_tx_plr_trigger\;40: Down_due_to_HW_force_event\;42: L1_exit_failure\;43: too_many_link_error_recoveries\;44: Down_due_to_contain_mode\;45: BW_loss_threshold_exceeded\;46: ELS_laser_fault\;47: Hi_SER" access="RO" enum="No_link_down_indication=0x0,Unknown_reason=0x1,Hi_BER=0x2,Block_Lock_loss=0x3,Alignment_loss=0x4,FEC_sync_loss=0x5,PLL_lock_loss=0x6,FIFO_overflow=0x7,false_SKIP_condition=0x8,Minor_Error_threshold_exceeded=0x9,Physical_layer_retransmission_timeout=0xa,Heartbeat_errors=0xb,Link_Layer_credit_monitoring_watchdog=0xc,Link_Layer_integrity_threshold_exceeded=0xd,Link_Layer_buffer_overrun=0xe,Down_by_outband_command_with_healthy_link=0xf,Down_by_outband_command_for_link_with_hi_ber=0x10,Down_by_inband_command_with_healthy_link=0x11,Down_by_inband_command_for_link_with_hi_ber=0x12,Down_by_verification_GW=0x13,Received_Remote_Fault=0x14,Received_TS1=0x15,Down_by_management_command=0x16,Cable_was_unplugged=0x17,Cable_access_issue=0x18,Cable_Thermal_shutdown=0x19,Current_issue=0x1a,Power_budget=0x1b,Fast_recovery_raw_ber=0x1c,Fast_recovery_effective_ber=0x1d,Fast_recovery_symbol_ber=0x1e,Fast_recovery_credit_watchdog=0x1f,Peer_side_down_to_sleep_state=0x20,Peer_side_down_to_disable_state=0x21,Peer_side_down_to_disable_and_port_lock=0x22,Peer_side_down_due_to_thermal_event=0x23,Peer_side_down_due_to_force_event=0x24,Peer_side_down_due_to_reset_event=0x25,Reset_no_power_cycle=0x26,Fast_recovery_tx_plr_trigger=0x27,Down_due_to_HW_force_event=0x28,L1_exit_failure=0x2a,too_many_link_error_recoveries=0x2b,Down_due_to_contain_mode=0x2c,BW_loss_threshold_exceeded=0x2d,ELS_laser_fault=0x2e,Hi_SER=0x2f" offset="0x4.16" size="0x0.8" />
	<field name="remote_reason_opcode" descr="Opcode of link down reason for local / remote side / last successful recovery entry reason: \;Recovery entry reason supported only if PCAM.feature_cap_mask bit 117 is set\;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Cable_Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Peer_side_down_to_sleep_state\;33: Peer_side_down_to_disable_state\;34: Peer_side_down_to_disable_and_port_lock\;35: Peer_side_down_due_to_thermal_event\;36: Peer_side_down_due_to_force_event\;37: Peer_side_down_due_to_reset_event\;38: Reset_no_power_cycle\;39: Fast_recovery_tx_plr_trigger\;40: Down_due_to_HW_force_event\;42: L1_exit_failure\;43: too_many_link_error_recoveries\;44: Down_due_to_contain_mode\;45: BW_loss_threshold_exceeded\;46: ELS_laser_fault\;47: Hi_SER" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="e2e_reason_opcode" descr="see local_reason_opcode for local reason opcode\;for remote reason opcode: local_reason_opcode+100" access="RO" offset="0xC.0" size="0x0.8" />
	<field name="ts1_opcode" descr="TS1 opcode describes the reason the peer requested to ramp down the link:\;0x8: TS1.Sleep\;0x9: TS1.Disable\;0xA: TS1.PortLock\;0xB: TS1.Thermal\;0xC: TS1.Clean \;0xD  : TS1.Force\;0xE: TS1.reset_req\;\;Note: This field is valid in case the local_reason_opcode = 21 or 32-38" access="RO" offset="0xC.12" size="0x0.4" />
	<field name="l1_failure_reason" descr="0: no_info_or_no_l1_failure\;1: HW_timeout\;2: FW_timeout\;3: Recovery_failure" access="RO" offset="0xC.16" size="0x0.4" />
	<field name="last_recovery_state" descr="last unsucsessful recovery event state\;0: no_info\;1: Retrain - no local receiver lock\;2: WaitRMT - local receiver locked, peer not locked\;3: IDLE - both local and remote trasmitter locked" access="RO" offset="0xC.20" size="0x0.4" />
	<field name="num_of_symbol_ber_alarms" descr="Number of Symbol BER Windows that crossed alarm threshold" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="last_raw_ber_magnitude" descr="Last raw BER window calculated.\;\;Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="last_raw_ber_coef" descr="Last raw BER window calculated.\;\;Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="cons_raw_norm_ber" descr="Number of last consecutive normal Raw BER windows" access="RO" offset="0x10.28" size="0x0.4" />
	<field name="max_raw_ber_magnitude" descr="Maximal raw BER window calculated.\;\;Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)\;" access="RO" offset="0x14.0" size="0x0.8" />
	<field name="max_raw_ber_coef" descr="Maximal raw BER window calculated.\;\;Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)\;" access="RO" offset="0x14.8" size="0x0.4" />
	<field name="min_raw_ber_magnitude" descr="Minimal raw BER window calculated.\;\;Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)\;" access="RO" offset="0x14.16" size="0x0.8" />
	<field name="min_raw_ber_coef" descr="Minimal raw BER window calculated.\;\;Raw_BER = raw_ber_coef*10^(-raw_ber_magnitude)\;" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="num_of_raw_ber_alarms" descr="Number of Raw BER Windows that crossed alarm threshold\;" access="RO" offset="0x18.0" size="0x0.16" />
	<field name="num_of_eff_ber_alarms" descr="Number of Effective BER Windows that crossed alarm threshold\;" access="RO" offset="0x18.16" size="0x0.16" />
	<field name="time_to_link_down_to_disable" descr="Time in msec to link down to disable state, once a paos down is set or a link down event occurs.\;If the phy manager state is different then disable the timer will return 0." access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="time_to_link_down_to_rx_loss" descr="Time in msec to link down to rx disable state, once a link down event occurs.\;If the phy manager state is different then rx disable the timer will return 0.\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="min_eff_ber_magnitude" descr="Minimal effective BER window calculated.\;\;Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x24.0" size="0x0.8" />
	<field name="min_eff_ber_coef" descr="Minimal effective BER window calculated.\;\;Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x24.8" size="0x0.4" />
	<field name="last_eff_ber_magnitude" descr="Last effective BER window calculated.\;\;Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x24.16" size="0x0.8" />
	<field name="last_eff_ber_coef" descr="Last effective BER window calculated.\;\;Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x24.24" size="0x0.4" />
	<field name="cons_eff_norm_ber" descr="Number of last consecutive normal Effective BER windows" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="max_eff_ber_magnitude" descr="Maximal effective BER window calculated.\;\;Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x28.0" size="0x0.8" />
	<field name="max_eff_ber_coef" descr="Maximal effective BER window calculated.\;\;Effective_BER = eff_ber_coef*10^(-eff_ber_magnitude)" access="RO" offset="0x28.8" size="0x0.4" />
	<field name="max_symbol_ber_magnitude" descr="Maximal symbol BER window calculated.\;\;Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x28.16" size="0x0.8" />
	<field name="max_symbol_ber_coef" descr="Maximal symbol BER window calculated.\;\;Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x28.24" size="0x0.4" />
	<field name="cons_symbol_norm_ber" descr="Number of last consecutive normal Symbol BER windows" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="min_symbol_ber_magnitude" descr="Minimal symbol BER window calculated.\;\;Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x2C.0" size="0x0.8" />
	<field name="min_symbol_ber_coef" descr="Minimal symbol BER window calculated.\;\;Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x2C.8" size="0x0.4" />
	<field name="last_symbol_ber_magnitude" descr="Last symbol BER window calculated.\;\;Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x2C.16" size="0x0.8" />
	<field name="last_symbol_ber_coef" descr="Last symbol BER window calculated.\;\;Effective_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x2C.24" size="0x0.4" />
	<field name="hi_ser_counter" descr="Number of hi_ser events since last clear" access="RO" offset="0x30.0" size="0x0.8" />
</node>

<node name="pddr_link_up_info_page_ext" descr="" size="0xf8.0" >
	<field name="up_reason_mng" descr="invalid port access severity\;0 - No down command / unknown\;1 - BMC force linkup\;2 - WOL force linkup\;\;3 - ASN.1 force link up" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="up_reason_drv" descr="invalid port access severity\;0 - No down command / unknown\;1 - Up by at least one of the hosts" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="up_reason_pwr" descr="invalid port access severity\;0 - No down command / unknown\;1 - Keep link up on boot \;2 - Keep link up Eth/IB\;3 - Keep link up on standby" access="RO" offset="0x0.16" size="0x0.4" />
	<field name="time_to_link_up" descr="Time in msec to link up from disable until phy up state.\;While the phy manager did not reach phy up state the timer will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while working at force mode." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="fast_link_up_status" descr="Indicates if fast link-up was performed in the link: \;0: Unknown\;1: Fast Link-UP was performed. \;2: Regular link-up flow was performed due to changes in cable\;3: Regular link-up flow was performed due to changes in protocol (speed or FEC)\;4: Regular link-up flow was performed due to a non-fastbootable FW version (PCNR is not supported)\;5: Regular link-up performed due to MLPN flow\;6: Regular link-up performed due to PCNR.tuning_override configuration while port was in &quot;down&quot; state.\;7: Invalid fastboot data struct (0xCAFECAFE magic value is not present. For example, SW reset was executed before finish saving data during PCNR flow)\;8: fast link-up timeout\;9: fast link-up flaps issue\;10: fast link-up failed during link-up" access="RO" offset="0x8.0" size="0x0.4" />
	<field name="time_to_link_up_phy_up_to_active" descr="Ethernet:\;Time in msec to link up from phy up until active state.\;While the phy manager did not reach active state the timer will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while working at force mode.\;IB:\;Time in msec from entering recovery state until back to Active state in case of successful recovery" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="time_to_link_up_sd_to_phy_up" descr="Ethernet only\;Time in msec to link up from signal detect until phy up state.\;While the phy manager did not reach phy up state the timer will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while working at force mode." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_to_link_up_disable_to_sd" descr="Ethernet:\;Time in msec to link up from disable until signal detect state.\;While the phy manager did not reach signal detect state the timer will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while working at force mode.\; IB:\;Time in msec to link up from disable until partner is detected (exit of Signal detect/receiver detect states)." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="time_to_link_up_disable_to_pd" descr="Ethernet only\;Time in msec to link up from disable until protocol detect state.\;While the phy manager did not reach protocol detect state the timer will return 0.\;The timer resets to 0 in one of the following cases:\;1. When moving to disable or rx disable state.\;2. When moving from active or phy up to polling state, while working at force mode.\;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="time_of_module_conf_done_up" descr="Time in msec of phy2mod command response of module conf done in port up case" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="time_of_module_conf_done_down" descr="Time in msec of phy2mod command response of module conf done in port down case" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="time_logical_init_to_active" descr="Time in mSec that it takes for the port logical state to transition from init to an active state.\;The timer reset to 0 ONLY when the logical port state goes down." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="total_time_pcs_local_fault" descr="Total time in sec of PCS state of Local Fault" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="total_time_pcs_remote_fault" descr="Total time in sec of PCS state of Remote Fault" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="time_on_last_hi_ser" descr="Time duration of last hi_ser event.\;value reset every new hi_ser event." access="RO" offset="0x30.0" size="0x4.0" />
</node>

<node name="pddr_module_info_ext" descr="" size="0xd0.0" >
	<field name="ethernet_compliance_code" descr="QSFP:\;Ethernet Compliance Codes bit mask (10/40G/100G)\;Byte131 per SFF-8636 \;Bit 7 - Extended Specification Compliance valid\;Bit 6 - 10GBASE-LRM\;Bit 5 - 10GBASE-LR\;Bit 4 - 10GBASE-SR\;Bit 3 - 40GBASE-CR4\;Bit 2 - 40GBASE-SR4\;Bit 1 - 40GBASE-LR4\;Bit 0 - 40G Active Cable (XLPPI)\;\;SFP: \;10G Ethernet Compliance Codes\;Byte3 per SFF-8472:\;Bit 7 - 10G Base-ER \;Bit 6 - 10G Base-LRM \;Bit 5 - 10G Base-LR \;Bit 4 - 10G Base-SR\;\;CMIS based (QSFP-DD/ SFP-DD / OSFP/OE)\;Byte 87 - Module Media Interface" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes \;for SFP:\;byte 36 per SFF-8472\;\;for QSFP:\;byte192 per SFF-8636 (QSFP28) \;\;for CMIS (SFP-DD / QSFP-DD/ OSFP/OE):\;Byte 86 - Host Electrical Interface" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="cable_breakout" descr="Reserved for SFP. \;\;For QSFP:\;Byte113 per SFF-8636\;\;For CMIS based modules:\;\;XX naming is according to cable_identifier name\;For example: if cable_identifier = ,6 XX string is QSFP-DD\;\;0 - Unspecified\;1 - XX to XX\;2 - XX to 2xQSFP or 2xXX (depopulated / 4 lanes)\;3 - XX to 4xDSFP or 4xQSFP (depopulated / 2 lanes)\;4 - XX to 8xSFP\;5 - XX (depopulated / 4 lanes) to QSFP or XX (depopulated / 4 lanes)\;6 - XX (depopulated / 4 lanes) to 2xXX(depopulated / 2 lanes) or 2xSFP-DD\;7 - XX (depopulated / 4 lanes) to 4xSFP\;8 - XX(/ 2 lane module) to XX\;9 - XX(/ 2 lane module) to 2xSFP" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="cable_technology" descr="QSFP: \;Byte 147 per SFF-8636.\;\;SFP:\;SFP+ Cable Technology: \;byte8 per SFF-8472:\;Bit 3 - Active Cable\;Bit 2 - Passive Cable\;\;CMIS based (QSFP-DD / OSFP/ SFP-DD/OE):\;Byte 212\;\;0x00: VCSEL_850nm\;0x01: VCSEL_1310nm\;0x02: VCSEL_1550nm\;0x03: FP_laser_1310nm\;0x04: DFB_laser_1310nm\;0x05: DFB_laser_1550nm\;0x06: EML_1310nm\;0x07: EML_1550nm\;0x08: others\;0x09: DFB_laser_1490nm\;0x0a: Passive_copper_cable_unequalized\;0x0b: Passive_copper_cable_equalized\;0x0c: Copper_cable_near_end_and_far_end_limiting_active_equailizer\;0x0d: Copper_cable_far_end_limiting_active_equailizer\;0x0e: Copper_cable_near_end_limiting_active_equializer\;0x0f: Copper_cable_linear_active_equalizers\;0x10: c_band_tunable_laser\;0x11: l_band_tunable_laser\;0x12: Copper_cable_near_end_and_far_end_linear_active_equalizers\;0x13: Copper_cable_far_end_linear_active_equalizers\;0x14:Copper_cable_near_end_linear_active_equalizers" access="RW" enum="VCSEL_850nm=0x0,VCSEL_1310nm=0x1,VCSEL_1550nm=0x2,FP_laser_1310nm=0x3,DFB_laser_1310nm=0x4,DFB_laser_1550nm=0x5,EML_1310nm=0x6,EML_1550nm=0x7,others=0x8,DFB_laser_1490nm=0x9,Passive_copper_cable_unequalized=0xa,Passive_copper_cable_equalized=0xb,Copper_cable_near_end_and_far_end_limiting_active_equailizer=0xc,Copper_cable_far_end_limiting_active_equailizer=0xd,Copper_cable_near_end_limiting_active_equializer=0xe,Copper_cable_linear_active_equalizers=0xf,c_band_tunable_laser=0x10,l_band_tunable_laser=0x11,Copper_cable_near_end_and_far_end_linear_active_equalizers=0x12,Copper_cable_far_end_linear_active_equalizers=0x13,Copper_cable_near_end_linear_active_equalizers=0x14" offset="0x0.24" size="0x0.8" />
	<field name="cable_power_class" descr="Module maximum power consumption for SFP/QSFP:\;0: Power_Class_0 - (1.0 W max)\;1: Power_Class_1 - (1.5 W max)\;2: Power_Class_2 - (2.0 W max)\;3: Power_Class_3 - (2.5 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (4.0 W max)\;6: Power_Class_6 - (4.5 W max)\;7: Power_Class_7 - (5.0 W max)\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for SFP-DD:\;0: Power_Class_0 - (0.5 W max)\;1: Power_Class_1 - (1.0 W max)\;2: Power_Class_2 - (1.5 W max)\;3: Power_Class_3 - (2.0 W max)\;4: Power_Class_4 - (3.5 W max)\;5: Power_Class_5 - (5.0 W max)\;6: reserved\;7: reserved\;8: Power_Class_8 - (power from max_power field)\;\;Module maximum power consumption for QSFP-DD/OSFP:\;1 - Power_Class_1 - (1.5 W max)\;2 - Power_Class_2 - (3.5 W max)\;3 - Power_Class_3 - (7.0 W max)\;4 - Power_Class_4 - (8.0 W max)\;5 - Power_Class_5 - (10 W max)\;6 - Power_Class_6 - (12 W max)\;7 - Power_Class_7 - (14 W max)\;8 - Power_Class_8 - (power from max_power field)" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="cable_identifier" descr="0: QSFP28\;1: QSFP_Plus\;2: SFP28_or_SFP_Plus\;3: QSA - (QSFP-&gt;SFP)\;4: Backplane\;5: SFP_DD\;6: QSFP_DD\;7: QSFP_CMIS\;8: OSFP\;9: C2C\;10: DSFP\;11: QSFP_Split_Cable\;12: CPO\;13: OE\;14: ELS\;\;identifiers that are CMIS compliant are: 5,6,7,8,10" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="cable_length" descr="Cable length in 1m units.\;\;For CMIS modules:\;bits 6:7 represent cable_length_multiplier for calculating cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;bits 0:5 represent cable_length_value for calculating cable length.\;length is calculated with cable_length_value * cable_length_multiplier" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="cable_vendor" descr="Cable vendor:\;0: Other\;1: Mellanox\;2: Known_OUI\;3: NVIDIA\;" access="RO" enum="Other=0x0,Mellanox=0x1,Known_OUI=0x2,NVIDIA=0x3" offset="0x4.24" size="0x0.4" />
	<field name="cable_type" descr="Cable/module type:\;0: Unidentified\;1: Active_cable - (active copper / optics)\;2: Optical_Module - (separated)\;3: Passive_copper_cable\;4: Cable_unplugged\;5: Twisted_pair\;6: CPO\;7: OE\;8: ELS\;" access="RO" enum="Unidentified=0x0,Active_cable=0x1,Optical_Module=0x2,Passive_copper_cable=0x3,Cable_unplugged=0x4,Twisted_pair=0x5,CPO=0x6,OE=0x7,ELS=0x8" offset="0x4.28" size="0x0.4" />
	<field name="cable_tx_equalization" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="cable_rx_emphasis" descr="For CMIS (QSFP-DD/ SFP-DD/ OSFP) field will represent Rx pre-emphasis." access="RO" offset="0x8.8" size="0x0.8" />
	<field name="cable_rx_amp" descr="Reserved for SFP\;" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="max_power" descr="Reserved for SFP, QSFP\;Byte 201 for CMIS (QSFP-DD/ SFP-DD/ OSFP/ELS/OE)\;Other Cable ignore field." access="RO" offset="0x8.24" size="0x0.8" />
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
	<field name="vendor_pn" descr="Vendor Part Number left-aligned and padded on the right with ASCII spaces (20h)" access="RO" high_bound="3" low_bound="0" offset="0x24.0" size="0x10.0" />
	<field name="vendor_rev" descr="ASCII Vendor revision aligned to right padded with 0h on the left" access="RO" offset="0x34.0" size="0x4.0" />
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
	<field name="tx_bias_lane1" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x70.0" size="0x0.16" />
	<field name="tx_bias_lane0" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x70.16" size="0x0.16" />
	<field name="tx_bias_lane3" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x74.0" size="0x0.16" />
	<field name="tx_bias_lane2" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x74.16" size="0x0.16" />
	<field name="tx_bias_lane5" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x78.0" size="0x0.16" />
	<field name="tx_bias_lane4" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x78.16" size="0x0.16" />
	<field name="tx_bias_lane7" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x7C.0" size="0x0.16" />
	<field name="tx_bias_lane6" descr="TX measured bias current on channel [i] in 2uA unit.\;\;The real sample value in uA units should be calculated as follows:\;tx_bias_lane[i] * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x7C.16" size="0x0.16" />
	<field name="temperature_low_th" descr="Alarm low temperature threshold in 1/256 C" access="RO" offset="0x80.0" size="0x0.16" />
	<field name="temperature_high_th" descr="Alarm high temperature threshold in 1/256 C" access="RO" offset="0x80.16" size="0x0.16" />
	<field name="voltage_low_th" descr="Alarm low Voltage threshold in 100uV" access="RO" offset="0x84.0" size="0x0.16" />
	<field name="voltage_high_th" descr="Alarm high Voltage threshold in 100uV" access="RO" offset="0x84.16" size="0x0.16" />
	<field name="rx_power_low_th" descr="Alarm low RX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x88.0" size="0x0.16" />
	<field name="rx_power_high_th" descr="Alarm high RX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x88.16" size="0x0.16" />
	<field name="tx_power_low_th" descr="Alarm low TX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x8C.0" size="0x0.16" />
	<field name="tx_power_high_th" descr="Alarm high TX Power threshold in dBm. \;Taking only from channel 0." access="RO" offset="0x8C.16" size="0x0.16" />
	<field name="tx_bias_low_th" descr="Alarm low TX Bias current threshold in 2 uA. \;\;The real threshold value in uA units should be calculated as follows:\;tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x90.0" size="0x0.16" />
	<field name="tx_bias_high_th" descr="Alarm high TX Bias current threshold in 2 uA.\;\;The real threshold value in uA units should be calculated as follows:\;tx_bias_high_th * 2 * tx_bias_scaling_factor[enum_value]" access="RO" offset="0x90.16" size="0x0.16" />
	<field name="wavelength" descr="Nominal laser wavelength in nm" access="RO" offset="0x94.0" size="0x0.16" />
	<field name="smf_length" descr="SMF link length\;SFP per byte 14,15.\;QSFP per byte 142\;for CMIS based modules, per byte 132\;\;bit 9:8 - 00 length base in 1 km units\;bit 9:8 - 01 length base in 100m units\;bits 7:0 - length base" access="RO" offset="0x94.16" size="0x0.10" />
	<field name="rx_output_valid_cap" descr="when set, indicates rx_output_valid is supported by the module" access="RW" offset="0x94.26" size="0x0.1" />
	<field name="did_cap" descr="set in case of Linear Direct Drive module" access="RO" offset="0x94.27" size="0x0.1" />
	<field name="rx_power_type" descr="rx power measurement type\;0: OMA\;1: Average_power" access="RO" enum="OMA=0x0,Average_power=0x1" offset="0x94.28" size="0x0.1" />
	<field name="module_st" descr="Valid for CMIS modules only.\;Module state:\;0: reserved\;1: LowPwr_state\;2: PwrUp_state\;3: Ready_state\;4: PwrDn_state\;5: Fault_state" access="RO" enum="reserved=0x0,LowPwr_state=0x1,PwrUp_state=0x2,Ready_state=0x3,PwrDn_state=0x4,Fault_state=0x5" offset="0x94.29" size="0x0.3" />
	<field name="ib_compliance_code" descr="Byte 164 of SFF-8636\;For CMIS modules IB Protocols:\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x98.0" size="0x0.10" />
	<field name="tx_bias_scaling_factor" descr="Valid for CMIS modules only.\;This field is relevant for the following fields: tx_bias_lane[7:0], tx_bias_high_th and tx_bias_low_th.\;The value of the above fields should be multiplied according to the tx_bias_scaling_factor value.\;0: multiply_1x\;1: multiply_2x\;2: multiply_4x\;" access="RO" enum="multiply_1x=0x0,multiply_2x=0x1,multiply_4x=0x2" offset="0x98.10" size="0x0.2" />
	<field name="active_set_media_compliance_code" descr="Valid for CMIS modules only.\;According to current Active set, value of Module Media Interface byte" access="RO" offset="0x98.16" size="0x0.8" />
	<field name="active_set_host_compliance_code" descr="Valid for CMIS modules only.\;According to current Active set, value of Host Electrical Interface byte" access="RO" offset="0x98.24" size="0x0.8" />
	<field name="ib_width" descr="Bitmask of width of IB Protocols" access="RO" offset="0x9C.0" size="0x0.6" />
	<field name="monitor_cap_mask" descr="monitoring capabilities mask\;Bit 0 - temperature monitoring implemented\;Bit 1 - voltage monitoring implemented\;Bit 2 - tx power monitoring implemented\;Bit 3 - rx power monitoring implemented\;Bit 4 - tx bias monitoring implemented" access="RO" offset="0x9C.8" size="0x0.8" />
	<field name="nbr100" descr="Nominal bit rate in units of 100Mb/s" access="RO" offset="0x9C.16" size="0x0.8" />
	<field name="nbr250" descr="Nominal bit rate in units of 250Mb/s" access="RO" offset="0x9C.24" size="0x0.8" />
	<field name="dp_st_lane" descr="DataPath state for lane&lt;i&gt;\;1: DPDeactivated\;2: DPInit\;3: DPDeinit\;4: DPActivated\;5: DPTxTurnOn\;6: DPTxTurnOff\;7: DPInitialized" access="RO" enum="DPDeactivated=0x1,DPInit=0x2,DPDeinit=0x3,DPActivated=0x4,DPTxTurnOn=0x5,DPTxTurnOff=0x6,DPInitialized=0x7" high_bound="7" low_bound="0" offset="0xA0.28" size="0x4.0" />
	<field name="length_om5" descr="OM5 fiber length supported in units of 2m" access="RO" offset="0xA4.0" size="0x0.8" />
	<field name="length_om4" descr="OM4 fiber length supported in units of 2m\;SFP in units of 10m" access="RO" offset="0xA4.8" size="0x0.8" />
	<field name="length_om3" descr="OM3 fiber length supported in units of 2m\;SFP in units of 10m" access="RO" offset="0xA4.16" size="0x0.8" />
	<field name="length_om2" descr="OM2 fiber length supported in units of 1m\;SFP in units of 10m" access="RO" offset="0xA4.24" size="0x0.8" />
	<field name="memory_map_rev" descr="memory map revision" access="RO" offset="0xA8.0" size="0x0.8" />
	<field name="wavelength_tolerance" descr="16-bit integer value for the laser wavelength tolerance in nm divided by 200 (units of 0.005nm)." access="RO" offset="0xA8.8" size="0x0.16" />
	<field name="length_om1" descr="OM1 fiber length supported in units of 10m" access="RO" offset="0xA8.24" size="0x0.8" />
	<field name="memory_map_compliance" descr="memory map compliance in ASCII.\;SFF-8472 / SFF-8636/ CMIS" access="RO" offset="0xAC.0" size="0x4.0" />
	<field name="date_code" descr="ASCII code for vendor&apos;s date code.\;63:48- 2 digit for date code year, 00 = year 2000\;47:32 - 2 digit for date code month.\;31:16 - 2 digit for day of the month code.\;15:0 - 2 digit LOT code." subnode="uint64" access="RO" offset="0xB0.0" size="0x8.0" />
	<field name="vendor_oui" descr="vendor oui" access="RO" offset="0xB8.0" size="0x0.24" />
	<field name="connector_type" descr="connector type based on SFF-8024" access="RO" offset="0xB8.24" size="0x0.8" />
	<field name="rx_output_valid" descr="Rx output status indication per lane" access="RO" offset="0xBC.0" size="0x0.8" />
	<field name="cable_attenuation_53g" descr="cable attenuation at 53GHz" access="RO" offset="0xBC.8" size="0x0.8" />
	<field name="tx_input_freq_sync" descr="Defines which Tx input lanes must be frequency synchronous.\;0: Tx_input_lanes_1_8\;1: Tx_input_lanes_1_4_and_5-8\;2: Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8\;3: Lanes_may_be_asynchronous_in_frequency" access="RO" enum="Tx_input_lanes_1_8=0x0,Tx_input_lanes_1_4_and_5=0x1,Tx_input_lanes_1_2_and_3_4_and_5_6_and_7_8=0x2,Lanes_may_be_asynchronous_in_frequency=0x3" offset="0xBC.16" size="0x0.2" />
	<field name="error_code" descr="Relevant for CMIS modules only\;Error Code response for ControlSet configuration of DataPath.\;0x0: ConfigUndefined\;0x1: ConfigSuccess\;0x2: ConfigRejected\;0x3: ConfigRejectedInvalidAppSel\;0x4: ConfigRejectedInvalidDataPath\;0x5: ConfigRejectedInvalidSI\;0x6: ConfigRejectedLanesInUse\;0x7: ConfigRejectedPartialDataPath\;0xC: ConfigInProgress" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc" offset="0xC0.0" size="0x0.4" />
	<field name="max_fiber_length" descr="Maximum length of allowed fiber in meters" access="RO" offset="0xC0.16" size="0x0.16" />
	<field name="els2_oper_state" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Indicates the ELS laser operative state:\;0: undifined_state\;1: laser_at_module_ready\;2: fiber_check\;3: laser_tuning\;4: laser_active\;5: fault_due_to_fiber_contaminated\;6: fault_due_to_APC_fault\;7: fault_due_to_laser_ramping_timeout_fault\;8: fault_due_to_max_power_exceeded\;9: fault_due_to_min_power_subceeded\;10: fault_due_to_els_unplugged" access="RO" enum="undifined_state=0x0,laser_at_module_ready=0x1,fiber_check=0x2,laser_tuning=0x3,laser_active=0x4,fault_due_to_fiber_contaminated=0x5,fault_due_to_APC_fault=0x6,fault_due_to_laser_ramping_timeout_fault=0x7,fault_due_to_max_power_exceeded=0x8,fault_due_to_min_power_subceeded=0x9,fault_due_to_els_unplugged=0xa" offset="0xC4.16" size="0x0.4" />
	<field name="els_oper_state" descr="Indicates the ELS laser operative state:\;0: undifined_state\;1: laser_at_module_ready\;2: fiber_check\;3: laser_tuning\;4: laser_active\;5: fault_due_to_fiber_contaminated\;6: fault_due_to_APC_fault\;7: fault_due_to_laser_ramping_timeout_fault\;8: fault_due_to_max_power_exceeded\;9: fault_due_to_min_power_subceeded\;10: fault_due_to_els_unplugged" access="RO" enum="undifined_state=0x0,laser_at_module_ready=0x1,fiber_check=0x2,laser_tuning=0x3,laser_active=0x4,fault_due_to_fiber_contaminated=0x5,fault_due_to_APC_fault=0x6,fault_due_to_laser_ramping_timeout_fault=0x7,fault_due_to_max_power_exceeded=0x8,fault_due_to_min_power_subceeded=0x9,fault_due_to_els_unplugged=0xa" offset="0xC4.20" size="0x0.4" />
	<field name="laser2_restriction" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Each bit represent the ELS&apos;s laser restriction. When restriction are on, the laser can operate only in restricted power mode, for the safety of the optical components. Restriction can be lifted only after fiber testing.\;0: laser2_restriction_on\;1: laser2_restriction_off" access="RO" enum="laser2_restriction_on=0x0,laser2_restriction_off=0x1" offset="0xC4.24" size="0x0.1" />
	<field name="laser_restriction" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser restriction. When restriction are on, the laser can operate only in restricted power mode, for the safety of the optical components. Restriction can be lifted only after fiber testing.\;0: laser_restriction_on\;1: laser_restriction_off" access="RO" enum="laser_restriction_on=0x0,laser_restriction_off=0x1" offset="0xC4.25" size="0x0.1" />
	<field name="laser2_status" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Each bit represent the ELS&apos;s laser status CMIS name of field.\;0: laser2_off\;1: laser2_ramping\;2: laser2_on" access="RO" enum="laser2_on=0x2" offset="0xC4.26" size="0x0.2" />
	<field name="laser_status" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser status CMIS name of field.\;0: laser_off\;1: laser_ramping\;2: laser_on" access="RO" enum="laser_on=0x2" offset="0xC4.28" size="0x0.2" />
	<field name="laser2_enabled" descr="Relevant for CPO ETH switches. when 8x port split is applied, this fields represent the ELS laser with the higher logical mapping index. Each bit represent the ELS&apos;s laser. \;0: laser2_disabled\;1: laser2_enabled" access="RO" enum="laser2_disabled=0x0,laser2_enabled=0x1" offset="0xC4.30" size="0x0.1" />
	<field name="laser_enabled" descr="Relevant for CPO product. Each bit represent the ELS&apos;s laser. \;0: laser_disabled\;1: laser_enabled" access="RO" enum="laser_disabled=0x0,laser_enabled=0x1" offset="0xC4.31" size="0x0.1" />
	<field name="module_production_test_revision_lsb" descr="Pluggable module production test version. Lower 32 bits." access="RO" offset="0xC8.0" size="0x4.0" />
	<field name="module_production_test_revision_msb" descr="Pluggable module production test version. Upper 8 bits." access="RO" offset="0xCC.24" size="0x0.8" />
</node>

<node name="pddr_monitor_opcode_ext" descr="" size="0x4.0" >
	<field name="monitor_opcode" descr="Status opcode: \;\;PHY FW indication (0 - 1023):\;0 - No issue observed\;1 - Port is close by command (see PAOS).\;2,3,4,38,39,60 - AN failure \;5,6,7,8 - Link training failure. \;9,10,11,12,13 - Logical mismatch between link partners\;14 - Remote fault received\;15,42,17,48,49,52, - Bad signal integrity \;16,24-32 - Cable compliance code mismatch (protocol mismatch between cable and port) \;23,22,19,18,50,55- Internal error\;34,35 - Speed degradation\;56 - module_lanes_frequency_not_synced\;57 - signal not detected\;60 - no partner detected for long time\;128 - Troubleshooting in process\;1023- Info not available\;\;MNG FW issues (1024 - 2047):\;1024 - Cable is unplugged\;1025 - Long Range for non Mellanox cable/module\;1026 - Bus stuck (I2C Data or clock shorted)\;1027 - Bad/unsupported EEPROM\;1028 - Part number list\;1029 - Unsupported cable\;1030 - Module temperature shutdown\;1031 - Shorted cable\;1032 - Power budget exceeded\;1033 - Management forced down the port\;1034 - Module is disabled by command\;1035 - System Power is Exceeded therefore the module is powered off.\;1036 - Module&apos;s PMD type is not enabled (see PMTPS).\;1040 - pcie system power slot Exceeded\;1042 - Module state machine fault\;1043,1044,1045,1046 - Module&apos;s stamping speed degeneration\;1047, 1048 - Modules DataPath FSM fault\;1050, 1051, 1052, 1053- Module Boot Error\;1054 - Module Forced to Low Power by command\;1055 - ELS laser fiber is contaminated\;1056 - ELS laser power control failure\;1057 - ELS unplugged\;1058 - ELS laser rampling timeout failure\;1059 - ELS undefined state\;Core/Driver (2048 - 3071):" access="RW" offset="0x0.0" size="0x0.16" />
</node>

<node name="pddr_operation_info_page_cable_proto_cap_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_cable_cap_eth_ext" descr="" subnode="pddr_cable_cap_eth_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_cable_cap_ib_ext" descr="" subnode="pddr_cable_cap_ib_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_cable_cap_nvlink_ext" descr="" subnode="pddr_cable_cap_nvlink_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_c2p_link_enabled_eth_ext" descr="" subnode="pddr_c2p_link_enabled_eth_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_c2p_link_enabled_ib_ext" descr="" subnode="pddr_c2p_link_enabled_ib_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_c2p_link_enabled_nvlink_ext" descr="" subnode="pddr_c2p_link_enabled_nvlink_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_ext" descr="" size="0xf8.0" >
	<field name="neg_mode_active" descr="0: protocol_was_not_negotiated - (force mode)\;1: MLPN_rev0_negotiated\;2: CL73_Ethernet_negotiated\;3: Protocol_according_to_Parallel_detect - (remote port in force mode)\;4: Standard_IB_negotiated" access="RO" enum="protocol_was_not_negotiated=0x0,MLPN_rev0_negotiated=0x1,CL73_Ethernet_negotiated=0x2,Protocol_according_to_Parallel_detect=0x3,Standard_IB_negotiated=0x4" offset="0x0.16" size="0x0.4" />
	<field name="proto_active" descr="Active protocol:\;Bit 0: InfiniBand\;Bit 2: Ethernet\;Bit 3: NVLink" access="RO" enum="InfiniBand=0x1,Ethernet=0x4,NVLink=0x8" offset="0x0.20" size="0x0.4" />
	<field name="ib_phy_fsm_state" descr="FW IB state machine:\;0x0: IB_AN_FSM_DISABLED\;0x1: IB_AN_FSM_INITIALY\;0x2: IB_AN_FSM_RCVR_CFG\;0x3: IB_AN_FSM_CFG_TEST\;0x4: IB_AN_FSM_WAIT_RMT_TEST\;0x5: IB_AN_FSM_WAIT_CFG_ENHANCED\;0x6: IB_AN_FSM_CFG_IDLE\;0x7: IB_AN_FSM_LINK_UP\;0x8: IB_AN_FSM_POLLING" access="RO" enum="IB_AN_FSM_DISABLED=0x0,IB_AN_FSM_INITIALY=0x1,IB_AN_FSM_RCVR_CFG=0x2,IB_AN_FSM_CFG_TEST=0x3,IB_AN_FSM_WAIT_RMT_TEST=0x4,IB_AN_FSM_WAIT_CFG_ENHANCED=0x5,IB_AN_FSM_CFG_IDLE=0x6,IB_AN_FSM_LINK_UP=0x7,IB_AN_FSM_POLLING=0x8" offset="0x4.8" size="0x0.8" />
	<field name="eth_an_fsm_state" descr="Ethernet (CL73) Auto-negotiation FSM state:\;0x0: ETH_AN_FSM_ENABLE\;0x1: ETH_AN_FSM_XMIT_DISABLE\;0x2: ETH_AN_FSM_ABILITY_DETECT\;0x3: ETH_AN_FSM_ACK_DETECT\;0x4: ETH_AN_FSM_COMPLETE_ACK\;0x5: ETH_AN_FSM_AN_GOOD_CHECK\;0x6: ETH_AN_FSM_AN_GOOD\;0x7: ETH_AN_FSM_NEXT_PAGE_WAIT" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="phy_mngr_fsm_state" descr="FW Phy Manager FSM state:\;0: Disabled \;1: Open_port\;2: Polling\;3: Active\;4: Close_port\;5: Phy_up\;6: Sleep\;7: Rx_disable\;8: Signal_detect\;9: Receiver_detect\;10: Sync_peer\;11: Negotiation\;12: Training\;13: SubFSM_active\;14: Protocol_Detect\;15: Unkown" access="RO" enum="Disabled=0x0,Open_port=0x1,Polling=0x2,Active=0x3,Close_port=0x4,Phy_up=0x5,Sleep=0x6,Rx_disable=0x7,Signal_detect=0x8,Receiver_detect=0x9,Sync_peer=0xa,Negotiation=0xb,Training=0xc,SubFSM_active=0xd,Protocol_Detect=0xe,Unkown=0xf" offset="0x4.24" size="0x0.8" />
	<field name="phy_manager_link_enabled" descr="For IB: Table  757, &quot;PDDR - Phy Manager Link Enabled IB layout,&quot; on page  809\;For Ethernet: Table  759, &quot;PDDR - Phy Manager Link Enabled Eth layout,&quot; on page  810\;For NVLink: Table  761, &quot;PDDR - Phy Manager Link Enable NVLink layout,&quot; on page  810" subnode="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" access="RO" offset="0x8.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="core_to_phy_link_enabled" descr="For IB: Table  763, &quot;PDDR - Core2phy Link Enabled IB layout,&quot; on page  811\;For Ethernet: Table  765, &quot;PDDR - Core2phy Link Enabled Eth layout,&quot; on page  812\;For NVLink: Table  767, &quot;PDDR - Core2phy Link Enabled NVLink layout,&quot; on page  812" subnode="pddr_operation_info_page_core_to_phy_link_enabled_auto_ext" access="RO" offset="0xC.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="cable_proto_cap" descr="For IB: Table  769, &quot;PDDR - Cable Cap IB layout,&quot; on page  813\;For Ethernet: Table  771, &quot;PDDR - Cable Cap Eth layout,&quot; on page  814\;For NVLink: Table  773, &quot;PDDR - Cable Cap NVLink layout,&quot; on page  814" subnode="pddr_operation_info_page_cable_proto_cap_auto_ext" access="RO" offset="0x10.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="link_active" descr="For IB: Table  775, &quot;PDDR - Link Active IB layout,&quot; on page  815\;For Ethernet: Table  777, &quot;PDDR - Link Active Eth layout,&quot; on page  815\;For NVLink: Table  779, &quot;PDDR - Link Active NVLink layout,&quot; on page  816" subnode="pddr_operation_info_page_link_active_auto_ext" access="RO" offset="0x14.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="loopback_mode" descr="0: No_loopback_active\;1: Phy_remote_loopback \;2: Phy_local_loopback -When set the port&apos;s egress traffic is looped back to the receiver and the port transmitter is disabled. \;4: External_local_loopback -Enables the port&apos;s transmitter to link with the port&apos;s receiver using an external loopback connector." access="RO" enum="No_loopback_active=0x0,Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4" offset="0x18.0" size="0x0.12" />
	<field name="fec_mode_request" descr="FEC mode request.\;See fec_mode_active." access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="fec_mode_active" descr="FEC mode active\;0: No_FEC\;1: Firecode_FEC\;2: Standard_RS_FEC - RS(528,514)\;3: Standard_LL_RS_FEC - RS(271,257)\;4: Interleaved_Quad_RS_FEC - (544,514)   Quad_KP4_FEC\;5: Interleaved_Quad_RS_FEC_PLR - 546,516) Quad_KP4_FEC\;6: Interleaved_Standard_RS-FEC - (544,514)\;7: Standard_RS-FEC - (544,514)\;8: Interleaved_Octet_RS_FEC_PLR -(546,516) Octet_KP4_FEC\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)\;11: Interleaved_Standard_RS_FEC_PLR - (544,514)- [Internal]\;12: RS-FEC - (544,514) + PLR- [Internal]\;13: LL-FEC - (271,257) + PLR- [Internal]\;14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal] \;15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Quad_RS_FEC=0x4,Interleaved_Quad_RS_FEC_PLR=0x5,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Interleaved_Octet_RS_FEC_PLR=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS=0xc,LL=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf" offset="0x1C.16" size="0x0.16" />
	<field name="eth_100g_fec_support" descr="FEC 100G (25Gb/s per lane) supported FEC include override masking, should reflect current phy configuration after link is up\;\;Bit 0 - No FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="eth_25g_50g_fec_support" descr="FEC 25G/50G (25Gb/s per lane) supported FEC include override masking, should reflect current phy configuration after link is up\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="profile_fec_in_use" descr="The profile that has been selected: \;Bit 0 - IB spec / legacy (See profiles description) \;Bit 1 - Internal ports (Backplane) \;Bit 2 - Passive copper - Short \;Bit 3 - Passive copper - Medium \;Bit 4 - Passive copper - Long \;Bit 5 - Active optics / copper short reach (&lt;20m) \;Bit 6 - Optics long reach (&gt;20m) \;Bit 7 - NO-FEC \;Bit 8 - FEC-ON" access="RO" offset="0x20.16" size="0x0.16" />
	<field name="pd_link_enabled" descr="For IB: Table  781, &quot;PDDR - Parallel Detect Link Enabled IB Layout,&quot; on page  817\;For Ethernet: Table  783, &quot;PDDR - Parallel Detect Link Enabled Eth Layout,&quot; on page  817" subnode="pddr_operation_info_page_pd_link_enabled_auto_ext" access="RO" offset="0x24.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="phy_hst_link_enabled" descr="For IB: Table  785, &quot;PDDR - HST Link Enabled IB Layout,&quot; on page  818\;For Ethernet: Table  787, &quot;PDDR - HST Link Enabled Eth Layout,&quot; on page  819" subnode="pddr_operation_info_page_phy_hst_link_enabled_auto_ext" access="RO" offset="0x28.0" size="0x4.0" union_selector="$(parent).proto_active" />
	<field name="eth_an_link_enabled" descr="Table  789, &quot;PDDR - ETH AN Link Enabled Eth Layout,&quot; on page  819" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="test_mode_fsm_state" descr="Test mode FSM state exposure is supported only if PCAM.feature_cap_mask bit 120 is set.\;bidi test mode FSM\;0: Disable - this mode is shared by bidi and simplex test mode FSM\;1: Open_lane\;2: Idle\;3: Close_lane\;- simplex test mode FSM\;4: Reciever_detect\;5. Idle_simplex\;6. Signal_detect\;7. Auto_fix_reversal_polarity\;8. Tuning" access="RO" enum="Disable=0x0,Open_lane=0x1,Idle=0x2,Close_lane=0x3,Reciever_detect=0x4" offset="0x38.24" size="0x0.8" />
</node>

<node name="pddr_operation_info_page_link_active_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_link_active_eth_ext" descr="" subnode="pddr_link_active_eth_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_link_active_ib_ext" descr="" subnode="pddr_link_active_ib_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_link_active_nvlink_ext" descr="" subnode="pddr_link_active_nvlink_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_pd_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pd_link_eth_enabled_ext" descr="" subnode="pd_link_eth_enabled_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pd_link_ib_enabled_ext" descr="" subnode="pd_link_ib_enabled_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_hst_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="hst_link_eth_enabled_ext" descr="" subnode="hst_link_eth_enabled_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="hst_link_ib_enabled_ext" descr="" subnode="hst_link_ib_enabled_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
</node>

<node name="pddr_operation_info_page_phy_manager_link_enabled_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_phy_manager_link_enabled_eth_ext" descr="" subnode="pddr_phy_manager_link_enabled_eth_ext" offset="0x0.0" selected_by="Ethernet" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabled_ib_ext" descr="" subnode="pddr_phy_manager_link_enabled_ib_ext" offset="0x0.0" selected_by="InfiniBand" size="0x4.0" />
	<field name="pddr_phy_manager_link_enabled_nvlink_ext" descr="" subnode="pddr_phy_manager_link_enabled_nvlink_ext" offset="0x0.0" selected_by="NVLink" size="0x4.0" />
</node>

<node name="pddr_phy_info_page_ext" descr="" size="0xf8.0" >
	<field name="port_notifications" descr="Port notifications bit mask\;Bit 0 - Link partner advertised capabilities \;Bit 1 - Speed degradation" access="RO" offset="0x0.0" size="0x0.8" />
	<field name="negotiation_mask" descr="Bit 0: eth_base_page\;Bit 1: ib_base_page\;Bit 2: ib_base_page_rev2 - XDR onwards\;Bit 3: Consortium\;Bit 4: MLPN_rev0\;Bit 5: MLPN_rev1\;Bit 6: NLPN_rev2" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="remote_device_type" descr="Remote device type: \;0 - Unknown (3rd party, Force, legacy MLPN)\;1 - CX4\;2 - CX4_LX\;3 - CX5\;4 - CX5_LX\;5 - CX6\;6 - CX6_LX\;7 - CX6_DX\;8 - CX7\;9 - Bluefield-2\;10 - CX8\;11 - Bluefield-3\;12- CX9\;13-99 Reserved\;\;100 - SwitchIB\;101 - Spectrum \;102 - SwitchIB-2\;103 - Quantum\;104 - Spectrum-2\;105 - Spectrum-3\;106 - Quantum-2\;107 - Spectrum-4\;108 -Quantum-3\;109 - Quantum-4\;110 - Spectrum-5\;111 - Spectrum-6\;112-199 -Reserved\;\;200 - GBxxx (GB100/102/200)\;201 - GRxxx\;202-255 - Reserved" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="lp_ib_revision" descr="Link partner IB TS revision \;\;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="ib_revision" descr="IB TS revision \;" access="RO" offset="0x4.8" size="0x0.8" />
	<field name="num_of_negotiation_attempts" descr="Negotiation attempt counter" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="phy_manager_disable_mask" descr="Phy manager disable bit mask: \;Bit 0 - Module not present (module absence/cage power off)\;Bit 1 - PAOS command\;Bit 2 - MAD IB PortInfo down command\;Bit 3 - Long range cable (Non Mellanox) \;Bit 4 - Verification command\;Bit 5 - ekey command\;Bit 6 - High power - cable require higher power than allowed.\;Bit 7 - Unknown Identifier (Module)\;Bit 8 - PAOS up once \;Bit 9 - Stamping failure\;Bit 10 - Calibration not done\;Bit 11 - Module Locking\;Bit 13 - Power budget exceeded\;Bit 14 - Interrupt Event / Module Temp\;Bit 15 - TEC flow / module bring up issue" access="RO" offset="0x8.0" size="0x0.24" />
	<field name="hw_link_phy_state" descr="IBP HW FSM Reflected State:\;0x10: sleeping_delay\;0x11: sleeping_quiet\;0x20: polling_active\;0x21: polling_quiet\;0x30: disable\;0x31: update_retimer\;0x40: config_debounce\;0x41: config_receiver\;0x42: config_wait_remote\;0x43: config_tx_reverse_lanes\;0x44: config_enhanced    \;0x45: config_test\;0x46: confg_wait_remote_test\;0x47: config_wait_cfg_enhanced\;0x48: config_idle\;0x50: linkup\;0x51: Linkup_Tx_Idle\;0x52: Linkup_Tx_Empty\;-Recovery\;0x60: recover_retrain\;0x61: recover_wait_remote\;0x62: recover_idle\;0x63: Local_down_cmd\;0x64: Remote_down_cmd\;0x65: uphy_recovery_send_ts1\;0x66: uphy_recovery_send_pam2\;0x67: uphy_recovery_send_pam4\;0x68: uphy_recovery_peq\;0x70: test\;- Force Modes\;0x80: Force_send_ts1 - command may be given only on disable state\;0x90: Force_send_ts2\;0xA0: Force_Sent_Idle\;0xB0: Force_send_ts_Mlnx\;0xC0: Force_send_ts3\;0xD0: Force_LinkUp\;- L1\;0xE0: Go_To_Quiet\;0xE1: Retimer_Align\;0xE2: Quiet_Entry\;0xE3: Quiet\;0xE4: Wake\;0xE5: Wake_Tx_Sleep0\;0xE6: Send_Announce\;0xE7: Tx_HS\;0xE8: Wait_For_Cdr_Lock" access="RO" enum="sleeping_delay=0x10,sleeping_quiet=0x11,polling_active=0x20,polling_quiet=0x21,disable=0x30,update_retimer=0x31,config_debounce=0x40,config_receiver=0x41,config_wait_remote=0x42,config_tx_reverse_lanes=0x43,config_enhanced=0x44,config_test=0x45,confg_wait_remote_test=0x46,config_wait_cfg_enhanced=0x47,config_idle=0x48,linkup=0x50,Linkup_Tx_Idle=0x51,Linkup_Tx_Empty=0x52,recover_retrain=0x60,recover_wait_remote=0x61,recover_idle=0x62,Local_down_cmd=0x63,Remote_down_cmd=0x64,uphy_recovery_send_ts1=0x65,uphy_recovery_send_pam2=0x66,uphy_recovery_send_pam4=0x67,uphy_recovery_peq=0x68,test=0x70,Force_send_ts1=0x80,Force_send_ts2=0x90,Force_Sent_Idle=0xa0,Force_send_ts_Mlnx=0xb0,Force_send_ts3=0xc0,Force_LinkUp=0xd0,Go_To_Quiet=0xe0,Retimer_Align=0xe1,Quiet_Entry=0xe2,Quiet=0xe3,Wake=0xe4,Wake_Tx_Sleep0=0xe5,Send_Announce=0xe6,Tx_HS=0xe7,Wait_For_Cdr_Lock=0xe8" offset="0x8.24" size="0x0.8" />
	<field name="pcs_phy_state" descr="PCS HW state:\;Bits 0-7: Block lock\;Bits 8-15: AM lock\;Bits 16-23: FEC lock\;Bits 24: Align_status\;Bits 25: Hi_BER\;Bits 26: Hi_SER" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="lp_proto_enabled" descr="IB ports: \;Link partner advertised speeds (first TS3)\;See ib_link_speed_enabled encoding.\;\;Ethernet ports:\;Link partner advertised Ethernet protocols active state: see PTYS.lp_advertise" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="lp_fec_mode_request" descr="Reserved when negotiation wasn&apos;t performed according to port_notifications.Link partner advertised capabilities value.\;Advertised link partner FEC mode request" access="RO" offset="0x14.0" size="0x0.16" />
	<field name="lp_fec_mode_support" descr="Reserved when negotiation wasn&apos;t performed according to port_notifications.Link partner advertised capabilities value.\;\;Advertised link partner FEC mode support\;Bit 0 - No FEC\;Bit 1 - Firecode FEC\;Bit 2 - Standard RS-FEC - RS(528,514)\;Bit 3 - Standard LL RS-FEC - RS(271,257)\;Bit 4 - Mellanox Strong RS-FEC - RS(277,257)\;Bit 5 - Mellanox LL RS-FEC - RS(163,155)\;Bit 6 - Reserved\;Bit 7 - Standard RS-FEC (544,514)\;Bit 8 - Zero Latency FEC\;Bit 12 - RS-FEC (544,514) + PLR\;Bit 13 - LL-FEC (271,257) + PLR\;\;" access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ib_last_link_down_reason" descr="Bit 0 - heartbeat_ack_received\;Bit 1 - heartbeat_send_received\;Bit 2 - heartbeat_err\;Bit 3 - tx_width_reduction_done_1x\;Bit 4 - tx_width_reduction_done_full\;Bit 5 - rx_width_reduction_done_1x\;Bit 6 - rx_width_reduction_done_full\;Bit 7 - width_reduction_timeout\;Bit 8 - ibl_link_retrain\;Bit 9 - rx_comskp_timeout\;Bit 10 - fifo_full_err\;Bit 11 - ts_at_linkup\;Bit 12 - minor_threshold_reached\;Bit 13 - link_fail\;Bit 14 - rx_eb_full_r\;Bit 15 - rx_8_10_lane_err\;Bit 16 - llr_link_retrain_set\;Bit 17 - fc_timeout\;Bit 18 - phy_error\;Bit 19 - lli_err\;Bit 20 - excessive_buffer_err\;Bit 21 - remote_init\;Bit 22 - plr_retry_expired\;Bit 23 - port_didnt_exit_plr_sync\;Bit 24 - eq_failed\;Bits 31-24 - Reserved" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="eth_last_link_down_lane" descr="Bit 0 - block_lock_failed\;Bit 1 - skip_detected\;Bit 2 - fec_sync_failed\;Bit 3 - fec_block_sync\;Bit 4 - fec_block_sync_lost" access="RO" high_bound="3" low_bound="0" offset="0x1C.24" size="0x4.0" />
	<field name="speed_deg_db" descr="Bit 0 - Speed degradation database Valid\;Bit 1 - Speed degradation SerDes Rx database valid\;BIts 3-2 - reserved\;Bit 4 - rx_reversal\;Bit 5 - tx_reversal\;Bit 7-6 - reserved\;Bits 11:8 - failed_qdr/fdr10 - bit per lane.\;Bits 15:12 - failed_fdr - bit per lane.\;Bits 19:16- failed_edr - bit per lane.\;Bits 24:20 - peer_failed_test\;Bits 26-25 - reserved\;Bit 27 - first_test_speed" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="degrade_grade_lane0" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x28.0" size="0x0.24" />
	<field name="degrade_grade_lane1" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x2C.0" size="0x0.24" />
	<field name="degrade_grade_lane2" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x30.0" size="0x0.24" />
	<field name="degrade_grade_lane3" descr="Valid only when port_notifications.Speed degradation is asserted \;" access="RO" offset="0x34.0" size="0x0.24" />
	<field name="num_of_presets_tested_lane7" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.0" size="0x0.5" />
	<field name="num_of_presets_tested_lane6" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.8" size="0x0.5" />
	<field name="num_of_presets_tested_lane5" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.16" size="0x0.5" />
	<field name="num_of_presets_tested_lane4" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x38.24" size="0x0.5" />
	<field name="kr_startup_debug_indications_5" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" offset="0x3C.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_4" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" enum="Local_frame_lock=0x1,Remote_frame_lock=0x2,Local_Frame_lock_timer_expired=0x4,Remote_Frame_lock_timer_expired=0x8,Local_receiver_ready=0x10,Remote_receiver_ready=0x20,max_wait_timer_expired=0x40,Wait_timer_done=0x80,Hold_off_timer_expired=0x100,link_fail_inhibit_timer_expired=0x200" offset="0x3C.16" size="0x0.16" />
	<field name="kr_startup_debug_indications_7" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" offset="0x40.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_6" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" offset="0x40.16" size="0x0.16" />
	<field name="num_of_presets_tested_lane3" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.0" size="0x0.5" />
	<field name="num_of_presets_tested_lane2" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.8" size="0x0.5" />
	<field name="num_of_presets_tested_lane1" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.16" size="0x0.5" />
	<field name="num_of_presets_tested_lane0" descr="presets tested in TX tuning flow counter or in KR Startup" access="RO" offset="0x44.24" size="0x0.5" />
	<field name="kr_startup_fsm_lane" descr="Per lane KR startup state:\;0: KR_FSM_INITIALIZE\;1: KR_FSM_SEND_TRAINING\;2: KR_FSM_TRAIN_LOCAL_TX\;3: KR_FSM_TRAIN_LOCAL_RX\;4: KR_FSM_TRAIN_REMOTE\;5: KR_FSM_LINK_READY\;6: KR_FSM_SEND_DATA\;7: KR_FSM_NVLT\;8: KR_ABORT\;9: KR_TIMEOUT\;10: KR_FSM_IN_IDLE" access="RO" enum="KR_FSM_INITIALIZE=0x0,KR_FSM_SEND_TRAINING=0x1,KR_FSM_TRAIN_LOCAL_TX=0x2,KR_FSM_TRAIN_LOCAL_RX=0x3,KR_FSM_TRAIN_REMOTE=0x4,KR_FSM_LINK_READY=0x5,KR_FSM_SEND_DATA=0x6,KR_FSM_NVLT=0x7,KR_ABORT=0x8,KR_TIMEOUT=0x9,KR_FSM_IN_IDLE=0xa" high_bound="7" low_bound="0" offset="0x48.24" size="0x8.0" />
	<field name="eth_an_debug_indication" descr="eth_an_debug bit mask:\;Bit 0 - Force link up\;Bit 1 - No HCD\;Bit 2 - Entered ACK_detect\;Bit 3 - Entered Good\;Bit 4 - Entered Good_Check\;Bit 5 - Entered Extra_tune\;Bit 6 - Entered Fix_Reversals\;Bit 7 - Entered Next_Page\;Bit 8 - Entered Sub-FSM Fail\;Bit 9 - Tuning timeout\;Bit 10 - No markers detected (during Good check)\;Bit 11 - Do KR-startup\;Bits 15:18 - KR startup failure mask" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="ib_phy_fsm_state_trace" descr="FW IB state machine:\;HDR Gen\;Bit 0 - entered IB_AN_FSM_DISABLED\;Bit 1 - entered IB_AN_FSM_INITIALY\;Bit 2 - entered IB_AN_FSM_RCVR_CFG\;Bit 3 - entered IB_AN_FSM_CFG_TEST\;Bit 4 - entered IB_AN_FSM_WAIT_RMT_TEST\;Bit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCED\;Bit 6 - entered IB_AN_FSM_CFG_IDLE\;Bit 7 - entered IB_AN_FSM_LINK_UP\;Bit 8 - Failed from CFG_IDLE\;\;NDR Gen:\;Bit 0 - entered IB_AN_FSM_DISABLED\;Bit 1 - entered IB_AN_FSM_POLLING\;Bit 2 - entered IB_AN_FSM_INITIALY\;Bit 3 - entered IB_AN_FSM_CFG_TEST\;Bit 4 - entered IB_AN_FSM_WAIT_RMT_TEST\;Bit 5 - entered IB_AN_FSM_WAIT_CFG_ENHANCED\;Bit 6 - entered IB_AN_FSM_CFG_IDLE\;Bit 7 - entered IB_AN_FSM_SYNC_CHECK\;Bit 8 - entered IB_AN_FSM_LINK_UP\;Bit 9 - Failed from CFG_IDLE\;Bit 10 - peer requested KR\;Bit 11 - speed degradation needed - &quot;best_grade&quot; didn&quot;t reach threshold\;\;" access="RO" offset="0x54.0" size="0x0.16" />
	<field name="rounds_waited_for_peer_to_end_test" descr="" access="RO" offset="0x54.16" size="0x0.5" />
	<field name="eth_an_watchdog_cnt" descr="counts ETH Watchdog was performed (and closed the IB fsm)." access="RO" offset="0x54.21" size="0x0.2" />
	<field name="fall_from_cfg_idle_cdr_cnt" descr="count falls from Cfg_idle (before linkup) due cdr not lock" access="RO" offset="0x54.23" size="0x0.3" />
	<field name="fall_from_cfg_idle_cnt" descr="count falls from Cfg_idle (before linkup) due amps lock on PLU" access="RO" offset="0x54.26" size="0x0.3" />
	<field name="cdr_not_locked_cnt" descr="count the cdr not locked after EQ" access="RO" offset="0x54.29" size="0x0.3" />
	<field name="kr_startup_debug_indications_1" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_0" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" enum="Local_frame_lock=0x1,Remote_frame_lock=0x2,Local_Frame_lock_timer_expired=0x4,Remote_Frame_lock_timer_expired=0x8,Local_receiver_ready=0x10,Remote_receiver_ready=0x20,max_wait_timer_expired=0x40,Wait_timer_done=0x80,Hold_off_timer_expired=0x100,link_fail_inhibit_timer_expired=0x200" offset="0x58.16" size="0x0.16" />
	<field name="kr_startup_debug_indications_3" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" offset="0x5C.0" size="0x0.16" />
	<field name="kr_startup_debug_indications_2" descr="kr_startup_debug_indication_&lt;i&gt; bit mask:\;Bit 0: Local_frame_lock\;Bit 1: Remote_frame_lock\;Bit 2: Local_Frame_lock_timer_expired\;Bit 3: Remote_Frame_lock_timer_expired \;Bit 4: Local_receiver_ready\;Bit 5: Remote_receiver_ready\;Bit 6: max_wait_timer_expired \;Bit 7: Wait_timer_done\;Bit 8: Hold_off_timer_expired\;Bit 9: link_fail_inhibit_timer_expired" access="RO" offset="0x5C.16" size="0x0.16" />
	<field name="tx_tuning_stages_lane" descr="Stages mask per lane:\;Bit 0: Single_preset_stage\;Bit 1: multiple_preset_stage\;Bit 2: LMS" access="RO" enum="Single_preset_stage=0x1,multiple_preset_stage=0x2,LMS=0x4" high_bound="7" low_bound="0" offset="0x60.28" size="0x4.0" />
	<field name="plu_tx_pwrup" descr="PLU power up status per lane" access="RO" offset="0x64.0" size="0x0.8" />
	<field name="plu_rx_pwrup" descr="PLU power up status per lane" access="RO" offset="0x64.8" size="0x0.8" />
	<field name="plu_tx_polarity" descr="Configured PLU polarity per lane" access="RO" offset="0x64.16" size="0x0.8" />
	<field name="plu_rx_polarity" descr="Configured PLU polarity per lane" access="RO" offset="0x64.24" size="0x0.8" />
	<field name="irisc_status" descr="" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="ib_cfg_delay_timeout" descr="0 - Default as defined in IB Spec.\;1 - Override default with 64msec timeout for all speeds.\;2 - Reserved\;3 - Reserved" access="RO" offset="0x68.4" size="0x0.2" />
	<field name="sd_valid" descr="when set, signal_detected has valid value." access="RO" offset="0x68.6" size="0x0.1" />
	<field name="plu_tx_speed" descr="PLU configured speed:\;" access="RO" offset="0x68.8" size="0x0.4" />
	<field name="plu_rx_speed" descr="PLU configured speed:\;" access="RO" offset="0x68.12" size="0x0.4" />
	<field name="plr_outstanding_cells" descr="" access="RO" offset="0x68.16" size="0x0.8" />
	<field name="signal_detected" descr="valid only when sd_valid is set\;Bitmask per lane.\;When set signal has been detected on the lane" access="RO" offset="0x68.24" size="0x0.8" />
	<field name="stamping_reason" descr="Bit 0: com_codes_is_zero\;Bit 1: rx_cdr_check_force_mode \;Bit 2: com_code_compliance \;Bit 3: eth_56g_stamped\;Bit 4: non_mlx_qsfp_transceiver\;Bit 5: non_mlx_sfp_transceiver\;Bit 6: ib_comp_codes\;Bit 7: edr_comp\;Bit 8: fdr_comp" access="RO" enum="com_codes_is_zero=0x1,rx_cdr_check_force_mode=0x2,com_code_compliance=0x4,eth_56g_stamped=0x8,non_mlx_qsfp_transceiver=0x10,non_mlx_sfp_transceiver=0x20,ib_comp_codes=0x40,edr_comp=0x80,fdr_comp=0x100" offset="0x6C.0" size="0x4.0" />
	<field name="kr_frame_lock_tuning_failure_events_count" descr="Number of times that fast tuning (50ms) for KR lock failed to achieve frame lock." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="kr_full_tuning_failure_count" descr="Number of times that full tuning (0.5sec/3sec) for KR full tuning flow failed to achieve desire SI performance" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="pm_debug_indication" descr="Bit 0: phy_test_mode\;Bit 1: force_mode_en" access="RO" enum="phy_test_mode=0x1,force_mode_en=0x2" offset="0x78.0" size="0x0.16" />
	<field name="ib_debug_indication" descr="Bit 0: cause_plr_tx_max_outstanding_cells" access="RO" enum="cause_plr_tx_max_outstanding_cells=0x1" offset="0x78.16" size="0x0.16" />
	<field name="pm_catastrophic_enum" descr="Phy Manager catastrophic enum" access="RO" offset="0x7C.0" size="0x0.7" />
	<field name="pm_cat_val" descr="When set, indicates the pm_catastrophic_enum is valid" access="RO" offset="0x7C.7" size="0x0.1" />
	<field name="an_catastrophic_enum" descr="Auto-neg catastrophic enum" access="RO" offset="0x7C.8" size="0x0.7" />
	<field name="an_cat_val" descr="When set, indicates the an_catastrophic_enum is valid" access="RO" offset="0x7C.15" size="0x0.1" />
	<field name="hst_catastrophic_enum" descr="HST catastrophic enum" access="RO" offset="0x7C.16" size="0x0.7" />
	<field name="hst_cat_val" descr="When set, indicates the hst_catastrophic_enum is valid" access="RO" offset="0x7C.23" size="0x0.1" />
	<field name="pd_catastrophic_enum" descr="Parallel Detect catastrophic enum" access="RO" offset="0x7C.24" size="0x0.7" />
	<field name="pd_cat_val" descr="When set, indicates the pd_catastrophic_enum is valid" access="RO" offset="0x7C.31" size="0x0.1" />
	<field name="pd_debug_indication" descr="Bit 0: speed_change_high_speed_module\;Bit 1: False_positive_signal_detect\;Bit 2: Nv2nv_force\;Bit 3: bad_kr_mask \;Bit 4: kr_mlx_peer\;Bit 5: entered_signal_detect\;Bit 6: entered_rate_config\;Bit 7: entered_activate_sunfsm\;Bit 8: entered_done\;Bit 9: entered_subfsm_fail" access="RO" enum="speed_change_high_speed_module=0x1,False_positive_signal_detect=0x2,Nv2nv_force=0x4,bad_kr_mask=0x8,kr_mlx_peer=0x10,entered_signal_detect=0x20,entered_rate_config=0x40,entered_activate_sunfsm=0x80,entered_done=0x100,entered_subfsm_fail=0x200" offset="0x80.0" size="0x4.0" />
	<field name="pd_count" descr="Parallel detect cycles counter" access="RO" offset="0x84.0" size="0x0.6" />
	<field name="fp_signal_detect_count" descr="False Positive signal detect count" access="RO" offset="0x84.8" size="0x0.6" />
	<field name="hst_mismatch_reason" descr="0: speed\;1: FEC\;2: precoding\;3: Gray coding" access="RO" offset="0x84.16" size="0x0.2" />
	<field name="psi_collision2" descr="FSM 2 to call sub fsm of PSI that caused collision\;see fsm_mask in debug page for FSM numbering" access="RO" offset="0x84.22" size="0x0.5" />
	<field name="psi_collision1" descr="FSM 1 to call sub fsm of PSI that caused collision\;see fsm_mask in debug page for FSM numbering" access="RO" offset="0x84.27" size="0x0.5" />
	<field name="nlpn_debug_ind_mask" descr="Bit 0: nonce_match_fail\;Bit 1: timeout - rst cause idle in npln\;Bit 2: hs_neg\;Bit 3: dme_neg" access="RO" enum="nonce_match_fail=0x1,timeout=0x2,hs_neg=0x4,dme_neg=0x8" offset="0x88.0" size="0x0.8" />
	<field name="phy2mod_speed_req" descr="phy 2 module requested speed, aka speed_apsel_value\;bitmask according to PTYS.ext_ethernet_protocol for ETH speeds\;or ib_ext_protocols for IB speeds" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="phy2mod_deactivate_lanes" descr="Bitmask per lane for phy2mod deactivate request status.\;0 - allow DP activation\;1 - Deactivate module DP" access="RO" offset="0x90.0" size="0x0.8" />
	<field name="phy2mod_ack_lanes" descr="Bitmask per lane for phy2mod request status.\;0 - ack\;1 - nack" access="RO" offset="0x90.8" size="0x0.8" />
	<field name="one_pll_mod" descr="indicates module has one pll for all lanes of the module." access="RO" offset="0x90.29" size="0x0.1" />
	<field name="no_dme_mod" descr="no_dme_module indicates module doesn&apos;t support low speed signaling such as 312.5 MB/s for DME ETH AN signaling or SDR (2.5 GB/s) for IB low speed AN." access="RO" offset="0x90.30" size="0x0.1" />
	<field name="eeprom_prsnt" descr="eeprom present indication" access="RO" offset="0x90.31" size="0x0.1" />
	<field name="rx_bypass_mux_plt0" descr="1 bit per each split; 1-enabled; 0-Bypass (No MacSec)" access="RO" offset="0x94.0" size="0x0.2" />
	<field name="rx_bypass_mux_plt1" descr="1 bit per each split; 1-enabled; 0-Bypass (No MacSec)" access="RO" offset="0x94.2" size="0x0.2" />
	<field name="tx_bypass_mux_plt0" descr="1 bit per each split; 1-enabled; 0-Bypass (No MacSec)" access="RO" offset="0x94.4" size="0x0.2" />
	<field name="tx_bypass_mux_plt1" descr="1 bit per each split; 1-enabled; 0-Bypass (No MacSec)" access="RO" offset="0x94.6" size="0x0.2" />
	<field name="reconciliation_mux_plt0" descr="1 bit per each split; 1-enabled; 0-Bypass (No MacSec)" access="RO" offset="0x94.8" size="0x0.2" />
	<field name="reconciliation_mux_plt1" descr="1 bit per each split; 1-enabled; 0-Bypass (No MacSec)" access="RO" offset="0x94.10" size="0x0.2" />
	<field name="macsec_en_plt0_s0" descr="MacSec enabled plt0 split 0" access="RO" offset="0x94.12" size="0x0.1" />
	<field name="macsec_en_plt0_s1" descr="MacSec enabled plt0 split 1" access="RO" offset="0x94.13" size="0x0.1" />
	<field name="macsec_en_plt1_s0" descr="MacSec enabled plt1 split 0" access="RO" offset="0x94.14" size="0x0.1" />
	<field name="macsec_en_plt1_s1" descr="MacSec enabled plt1 split 1" access="RO" offset="0x94.15" size="0x0.1" />
	<field name="cnt_rx_frame_received_ok_s0" descr="MacSec Engine Wrapper, debug counter" access="RO" offset="0x94.16" size="0x0.4" />
	<field name="cnt_rx_frame_received_ok_s1" descr="MacSec Engine Wrapper, debug counter" access="RO" offset="0x94.20" size="0x0.4" />
	<field name="port_xmit_pkts_inc_s0" descr="MacSec Engine Wrapper, debug counter" access="RO" offset="0x94.24" size="0x0.4" />
	<field name="port_xmit_pkts_inc_s1" descr="MacSec Engine Wrapper, debug counter" access="RO" offset="0x94.28" size="0x0.4" />
	<field name="plr_rtt_ndr_4x_kp4_threshold" descr="rtt threshold in 1 ns units for NDR_4x speeds with KP4 FEC\;" access="RO" offset="0x98.0" size="0x0.16" />
	<field name="plr_rtt_hdr_threshold" descr="rtt threshold in 1 ns units for HDR speeds" access="RO" offset="0x98.16" size="0x0.16" />
	<field name="plr_rtt_ndr_2x_kp4_threshold" descr="rtt threshold in 1 ns units for NDR_2x speeds with KP4 FEC\;" access="RO" offset="0x9C.0" size="0x0.16" />
	<field name="plr_rtt_xdr_1x_kp4_threshold" descr="rtt threshold in 1 ns units for XDR_1x speeds with KP4 FEC\;" access="RO" offset="0x9C.16" size="0x0.16" />
	<field name="plr_rtt_ndr_2x_ell_threshold" descr="rtt threshold in 1 ns units for NDR_2x speeds with ELL FEC\;" access="RO" offset="0xA0.0" size="0x0.16" />
	<field name="plr_rtt_ndr_4x_ell_threshold" descr="rtt threshold in 1 ns units for NDR_4x speeds with ELL FEC\;" access="RO" offset="0xA0.16" size="0x0.16" />
	<field name="plr_rtt_xdr_1x_ell_threshold" descr="rtt threshold in 1 ns units for XDR_1x speeds with ELL FEC\;" access="RO" offset="0xA4.0" size="0x0.16" />
	<field name="plr_rtt_xdr_2x_kp4_threshold" descr="rtt threshold in 1 ns units for XDR_2x speeds with KP4 FEC\;" access="RO" offset="0xA4.16" size="0x0.16" />
</node>

<node name="pddr_phy_manager_link_enabled_eth_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_eth_enabled" descr="Ethernet protocols admin state: see PTYS.ext_eth_proto_admin" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_phy_manager_link_enabled_ib_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_proto_enabled" descr="IB link enabled speed:\;Bit 0 - SDR\;Bit 1 - DDR\;Bit 2 - QDR\;Bit 3 - FDR10\;Bit 4 - FDR\;Bit 5 - EDR\;Bit 6 - HDR\;Bit 7 - NDR\;Bit 8 - XDR" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="phy_manager_link_width_enabled" descr="IB link enabled width:\;Bit 0 - 1x\;Bit 1 - 2x\;Bit 2 - 4x\;Other - reserved" access="RO" offset="0x0.16" size="0x0.16" />
</node>

<node name="pddr_phy_manager_link_enabled_nvlink_ext" descr="" size="0x4.0" >
	<field name="phy_manager_link_nvlink_enabled" descr="NVLink protocols admin state: \;see: Table  491, &quot;PTYS - Extended Protocol NVLink - admin layout,&quot; on page  485" access="RO" offset="0x0.0" size="0x4.0" />
</node>

<node name="pddr_reg_ext" descr="" size="0x100.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_port\;1: Near_End_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="module_ind_type" descr="Module index type selector:\;0: CPO_or_pluggable_modules\;1: OE\;2: ELS" access="INDEX" enum="CPO_or_pluggable_modules=0x0,OE=0x1,ELS=0x2" offset="0x0.24" size="0x0.2" />
	<field name="page_select" descr="page select index:\;0: Operational_info_page\;1: Troubleshooting_info_page\;2: Phy_info_page\;3: Module_info_page\;6: link_down_info\;8: Link_up_info\;9: Module_latched_flag_info_page" access="INDEX" enum="Operational_info_page=0x0,Troubleshooting_info_page=0x1,Phy_info_page=0x2,Module_info_page=0x3,link_down_info=0x6,Link_up_info=0x8,Module_latched_flag_info_page=0x9" offset="0x4.0" size="0x0.8" />
	<field name="module_info_ext" descr="Module info extended configurations.\;resolution for rx_power, rx_power_high_th, rx_power_low_th tx_power, tx_power_high_th, tx_power_low_th in module info page\;0: dbm\;1: uW" access="OP" enum="dbm=0x0,uW=0x1" offset="0x4.29" size="0x0.2" />
	<field name="page_data" descr="Table  755, &quot;Operation Info Page Layout,&quot; on page  800\;Table  799, &quot;Troubleshooting info Page layout,&quot; on page  859\;Table  791, &quot;Phy Info Page Layout,&quot; on page  820\;Table  797, &quot;Module Info Page Layout,&quot; on page  842\;Table  793, &quot;Link Down Info Page Layout,&quot; on page  836\;Table  809, &quot;Link Up Info Page Layout,&quot; on page  873\;Table  811, &quot;Module Latched Flag Info Page Layout,&quot; on page  877\;" subnode="pddr_reg_page_data_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).page_select" />
</node>

<node name="pddr_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="module_latched_flag_info_ext" descr="" subnode="module_latched_flag_info_ext" offset="0x0.0" selected_by="Module_latched_flag_info_page" size="0x50.0" />
	<field name="pddr_link_down_info_page_ext" descr="" subnode="pddr_link_down_info_page_ext" offset="0x0.0" selected_by="link_down_info" size="0xf4.0" />
	<field name="pddr_link_up_info_page_ext" descr="" subnode="pddr_link_up_info_page_ext" offset="0x0.0" selected_by="Link_up_info" size="0xf8.0" />
	<field name="pddr_module_info_ext" descr="" subnode="pddr_module_info_ext" offset="0x0.0" selected_by="Module_info_page" size="0xd0.0" />
	<field name="pddr_operation_info_page_ext" descr="" subnode="pddr_operation_info_page_ext" offset="0x0.0" selected_by="Operational_info_page" size="0xf8.0" />
	<field name="pddr_phy_info_page_ext" descr="" subnode="pddr_phy_info_page_ext" offset="0x0.0" selected_by="Phy_info_page" size="0xf8.0" />
	<field name="pddr_troubleshooting_page_ext" descr="" subnode="pddr_troubleshooting_page_ext" offset="0x0.0" selected_by="Troubleshooting_info_page" size="0xf8.0" />
</node>

<node name="pddr_troubleshooting_page_ext" descr="" size="0xf8.0" >
	<field name="group_opcode" descr="0: Monitor_opcodes" access="INDEX" enum="Monitor_opcodes=0x0" offset="0x0.0" size="0x0.16" />
	<field name="status_opcode" descr="Status opcode described in:\;Table  801, &quot;PDDR - Monitor opcodes layout,&quot; on page  860" subnode="pddr_troubleshooting_page_status_opcode_auto_ext" access="RO" offset="0x4.0" size="0x4.0" union_selector="$(parent).group_opcode" />
	<field name="status_message" descr="ASCII code message\;All Messages are terminated by a Null character &apos;\0&apos;" access="RO" high_bound="58" low_bound="0" offset="0xC.0" size="0xec.0" />
</node>

<node name="pddr_troubleshooting_page_status_opcode_auto_ext" descr="" attr_is_union="1" size="0x4.0" >
	<field name="pddr_monitor_opcode_ext" descr="" subnode="pddr_monitor_opcode_ext" offset="0x0.0" selected_by="Monitor_opcodes" size="0x4.0" />
</node>

<node name="pevnt_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rx_cont" descr="The local_port RX is contained.\;RX containd - When a packet had a corruption, and is discarded. the port which detect the error &apos;contains&apos; it by stopping the traffic." access="RO" offset="0x4.0" size="0x0.1" />
	<field name="tx_cont" descr="The local_port TX is contained.\;TX containd - When a packet had a corruption, and is discarded. the port which detect the error &apos;contains&apos; it by stopping the traffic." access="RO" offset="0x4.1" size="0x0.1" />
</node>

<node name="pfcc_reg_ext" descr="" size="0x20.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local port number\;1: IB / label port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="prio_mask_rx" descr="Bit per prio indicating if RX flow control policy should be updated based on bit pfcrx ." access="WO" offset="0x4.0" size="0x0.8" />
	<field name="prio_mask_tx" descr="Bit per prio indicating if TX flow control policy should be updated based on bit pfctx ." access="WO" offset="0x4.16" size="0x0.8" />
	<field name="ppan" descr="Pause policy auto negotiation\;0: disabled - generate and ignore pause frames based on pptx, pprx\;1: enabled - when auto-negotiation is performed, set the pause policy based on the auto-negotiation resolution.\;\;" access="RW" enum="disabled=0x0,enabled=0x1" offset="0x4.28" size="0x0.4" />
	<field name="pfctx" descr="Priority based flow control policy on TX[7:0]. Per priority bit mask:\;0: never generate pause frames on the specified priority (default)\;1: generate pause frames according to RX buffer threshold on the specified priority\;pfctx, pptx must be mutually exclusive (for example, only one of them at most can be set)." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="patx" descr="Peer advertisement pause policy on Tx\;0: Unknown\;1: Peer supports pause on Tx\;2: Peer doesn&apos;t support pause on Tx\;\;" access="RO" offset="0x8.27" size="0x0.2" />
	<field name="aptx" descr="Active (operational) pause policy on TX\;0: do not generate pause frames\;1: generate pause frames according to RX buffer threshold" access="RO" offset="0x8.30" size="0x0.1" />
	<field name="pptx" descr="Admin pause policy on TX (see also pfctx):\;0: never generate pause frames (default)\;1: generate pause frames according to RX buffer threshold" access="RW" offset="0x8.31" size="0x0.1" />
	<field name="pfcrx" descr="Priority based flow control policy on RX[7:0]. Per priority bit mask:\;0: ignore incoming pause frames on the specified priority (default)\;1: respect incoming pause frames on the specified priority" access="RW" offset="0xC.16" size="0x0.8" />
	<field name="parx" descr="Peer advertisement pause policy on Rx\;0: Unknown\;1: Peer supports pause on Rx\;2: Peer doesn&apos;t support pause on Rx\;\;" access="RO" offset="0xC.27" size="0x0.2" />
	<field name="aprx" descr="Active (operational) pause policy on RX\;0: ignore received pause frames\;1: respect received pause frames" access="RO" offset="0xC.30" size="0x0.1" />
	<field name="pprx" descr="Admin pause policy on RX (see also pfcrx):\;0: ignore received pause frames (default)\;1: respect received pause frames" access="RW" offset="0xC.31" size="0x0.1" />
</node>

<node name="pfsc_reg_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fwd_admin" descr="Administratively configured of Forward switching for Egress:\;0: Allow cut-through forwarding\;1: Always Store and Forward" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="fwd_oper" descr="Operational Egress Forward switching:\;0: Cut-Through forwarding operation is allowed\;1: Only Store and Forward operation" access="RO" offset="0x8.0" size="0x0.4" />
</node>

<node name="pgmr_ext" descr="" size="0x2c.0" >
	<field name="pg_sel" descr="Selection between an operation on a local port or a group, for &apos;set&apos; and &apos;get&apos; operations. \;0 - local port (group field is neglected even if set)\;1 - group (local_port field is neglected even if set)" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="group" descr="Group number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. Determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="group_of_port" descr="The corresponding group number for thelocal_port" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x4.8" size="0x0.4" />
	<field name="ports_mapping_of_group" descr="A bit map of all available local ports in the system (each bit represents a local port). \;The corresponding bits which represent the local ports for the specific group in the group field, are set to &apos;1&apos;.\;If set to &apos;0&apos; - not in that specific group or not available.\;Bit 0 - local_port 1\;Bit 1 - local_port 2\;..." access="RW" high_bound="8" low_bound="0" offset="0x8.0" size="0x24.0" />
</node>

<node name="pguid_reg_ext" descr="" size="0x60.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sys_guid" descr="System GUID.\;Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x4.0" size="0x10.0" />
	<field name="node_guid" descr="Node GUID.\;Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x14.0" size="0x10.0" />
	<field name="port_guid" descr="Port GUID.\;Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x24.0" size="0x10.0" />
	<field name="allocated_guid" descr="Allocated GUID.\;Only 64 LSB are used. 64 MSB are reserved." access="RO" high_bound="3" low_bound="0" offset="0x34.0" size="0x10.0" />
</node>

<node name="phbr_ext" descr="" size="0x1c.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="hist_id" descr="Histogram id to bind\;from 0 to cap_max_port_hist_id - 1" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="hist_type" descr="Histogram Type.\;See Table 1076, &quot;Histogram Types,&quot; on page 1154" access="RW" offset="0x8.0" size="0x0.16" />
	<field name="mode" descr="Mode:\;0: Linear\;1: Exponential" access="RW" enum="Linear=0x0,Exponential=0x1" offset="0x8.28" size="0x0.3" />
	<field name="first_bin_thr" descr="First Bin Threshold.\;All values that are under this threshold will be counted in the first bin.\;Units according to the units of the hist_type.\;Range 1...(2^28) - 1" access="RW" offset="0xC.0" size="0x4.0" />
	<field name="bin_size" descr="Bin Size.\;bin_0 size will be first_bin_thr.\;If mode = 0, the size of bin 1-8 will be bin_size.\;If mode = 1, the size of bin_i will be 2^(i-1) * bin_size when 1 &lt; i &lt; 8.\;Range 1...(2^25) - 1\;Units according to the units of the hist_type" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="hist_repeat_num" descr="Histogram Repeat Number.\;When this field equal to 0 the histogram will stop.\;When this field equal to 0xffffff the histogram will run infinite times.\;On other values the histogram will run hist_repeat_num times.\;Range 1...2^24 - 1" access="RW" offset="0x14.0" size="0x0.24" />
	<field name="sample_time" descr="Sample time interval. \;Allowed range for Switch-IB and Spectrum:\;time = 2^sample_time * 128nSec\;sample_time range is 0..cap_max_sample_time-1" access="RW" offset="0x18.0" size="0x0.6" />
</node>

<node name="phrr_reg_ext" descr="" size="0x68.0" >
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clr" descr="Clear:\;1: Clear the data in the histogram agent" access="RW" offset="0x0.31" size="0x0.1" />
	<field name="hist_id" descr="see Table  1074, &quot;PHBR - Port Histogram Binding Register Layout,&quot; on page  1152" access="INDEX" offset="0x4.0" size="0x0.8" />
	<field name="bin" descr="Value of bin \;Units according to the units of the hist_type which is used for the hist_id" subnode="uint64" access="RO" high_bound="9" low_bound="0" offset="0x10.0" size="0x50.0" />
	<field name="min_watermark" descr="Min value while the histogram was working." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="max_watermark" descr="Max value while the histogram was working." access="RO" offset="0x64.0" size="0x4.0" />
</node>

<node name="phys_layer_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in msec." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear event in msec." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="symbol_errors_high" descr="Perf.PortCounters(SymbolErrorCounter) = Perf.PortCounters(UnknownSymbol)" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="symbol_errors_low" descr="Perf.PortCounters(SymbolErrorCounter) = Perf.PortCounters(UnknownSymbol)" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="sync_headers_errors_high" descr="Perf.PortExtendedSpeedsCounters(SynchHeaderErrorCounter)" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="sync_headers_errors_low" descr="Perf.PortExtendedSpeedsCounters(SynchHeaderErrorCounter)" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane0Counter) / BIP error counter, lane 0\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane0_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane0Counter) / BIP error counter, lane 0\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane1Counter) / BIP error counter, lane 1\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane1_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane1Counter) / BIP error counter, lane 1\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane2Counter) / BIP error counter, lane 2\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane2_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane2Counter) / BIP error counter, lane 2\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_high" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane3Counter) / BIP error counter, lane 3\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="edpl_bip_errors_lane3_low" descr="Perf.PortExtendedSpeedsCounters(ErrorDetectionPerLane3Counter) / BIP error counter, lane 3\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0)" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0)" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1)" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1)" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2)" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2)" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3)" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="fc_fec_corrected_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3)" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0)" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane0_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane0)" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1)" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane1_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane1)" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2)" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane2_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane2)" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3)" access="RO" offset="0x70.0" size="0x4.0" />
	<field name="fc_fec_uncorrectable_blocks_lane3_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrectableBlockCounterLane3)" access="RO" offset="0x74.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FECCorrecableBlockCounter)" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="rs_fec_corrected_blocks_low" descr="Perf.PortExtendedSpeedsCounters(FECCorrecableBlockCounter)" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_high" descr="Perf.PortExtendedSpeedsCounters(FEUncorrecableBlockCounter)" access="RO" offset="0x80.0" size="0x4.0" />
	<field name="rs_fec_uncorrectable_blocks_low" descr="Perf.PortExtendedSpeedsCounters(FEUncorrecableBlockCounter)" access="RO" offset="0x84.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_high" descr="The number of RS-FEC blocks received that had no errors.\;Note: Total rs_fec blocks received = rs_fec_corrected_blocks + rs_fec_uncorrectable_blocks + rs_fec_no_errors_blocks" access="RO" offset="0x88.0" size="0x4.0" />
	<field name="rs_fec_no_errors_blocks_low" descr="The number of RS-FEC blocks received that had no errors.\;Note: Total rs_fec blocks received = rs_fec_corrected_blocks + rs_fec_uncorrectable_blocks + rs_fec_no_errors_blocks" access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_high" descr="Perf.PortExtendedSpeedCounters(PortFECCorrectedSymbolCounter)" access="RO" offset="0x98.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_total_low" descr="Perf.PortExtendedSpeedCounters(PortFECCorrectedSymbolCounter)" access="RO" offset="0x9C.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane0)" access="RO" offset="0xA0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane0_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane0)" access="RO" offset="0xA4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane1)" access="RO" offset="0xA8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane1_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane1)" access="RO" offset="0xAC.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane2)" access="RO" offset="0xB0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane2_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane2)" access="RO" offset="0xB4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane3)" access="RO" offset="0xB8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane3_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane3)" access="RO" offset="0xBC.0" size="0x4.0" />
	<field name="link_down_events" descr="Counts local unintentional drops (no remote consideration)\;\;Perf.PortCounters(LinkDownedCounter)" access="RO" offset="0xC0.0" size="0x4.0" />
	<field name="successful_recovery_events" descr="\;Counts successful recovery events per active link. clears on new link up" access="RO" offset="0xC4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane4_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane4)" access="RO" offset="0xC8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane4_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane4)" access="RO" offset="0xCC.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane5_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane5)" access="RO" offset="0xD0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane5_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane5)" access="RO" offset="0xD4.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane6_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane6)" access="RO" offset="0xD8.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane6_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane6)" access="RO" offset="0xDC.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane7_high" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane7)" access="RO" offset="0xE0.0" size="0x4.0" />
	<field name="rs_fec_corrected_symbols_lane7_low" descr="Perf.PortExtendedSpeedCounters(FECCorrectedSymbolCounterLane7)" access="RO" offset="0xE4.0" size="0x4.0" />
	<field name="unintentional_link_down_events" descr="Counts Local &amp; remote unintentional drops (remote intentional are not counted)\;Updated on link drop only" access="RO" offset="0xF0.0" size="0x4.0" />
	<field name="intentional_link_down_events" descr="Counts Local &amp; remote intentional drops (remote intentional counted)\;Updated on link drop only" access="RO" offset="0xF4.0" size="0x4.0" />
</node>

<node name="phys_layer_stat_cntrs_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in msec.\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear event in msec.\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="phy_received_bits_high" descr="This counter provides information on the total \;amount of bits received by the PHY FEC decoder.\;" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="phy_received_bits_low" descr="This counter provides information on the total \;amount of bits received by the PHY FEC decoder.\;" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="phy_symbol_errors_high" descr="This counter provides information on error bits that were not corrected by phy correction mechanisms. (FEC + PLR)\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="phy_symbol_errors_low" descr="This counter provides information on error bits that were not corrected by phy correction mechanisms. (FEC + PLR)\;" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="phy_corrected_bits_high" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="phy_corrected_bits_low" descr="Corrected bits by FEC engine. \;" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_high" descr="This counter provides information on error bits that were identified on lane 0. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="phy_raw_errors_lane0_low" descr="This counter provides information on error bits that were identified on lane 0. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 0\;\;\;" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_high" descr="This counter provides information on error bits that were identified on lane 1. \;When FEC is enabled this induction corresponds to corrected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;\;" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="phy_raw_errors_lane1_low" descr="This counter provides information on error bits that were identified on lane 1. \;When FEC is enabled this induction corresponds to corrected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 1\;\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_high" descr="This counter provides information on error bits that were identified on lane 2. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="phy_raw_errors_lane2_low" descr="This counter provides information on error bits that were identified on lane 2. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 2\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_high" descr="This counter provides information on error bits that were identified on lane 3. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="phy_raw_errors_lane3_low" descr="This counter provides information on error bits that were identified on lane 3. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 3\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_high" descr="This counter provides information on error bits that were identified on lane 4. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 4\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="phy_raw_errors_lane4_low" descr="This counter provides information on error bits that were identified on lane 4. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 4\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_high" descr="This counter provides information on error bits that were identified on lane 5. \;When FEC is enabled this induction corresponds to corrected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 5\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="phy_raw_errors_lane5_low" descr="This counter provides information on error bits that were identified on lane 5. \;When FEC is enabled this induction corresponds to corrected errors\;In PRBS test mode, indicates the number of PRBS errors\;on lane 5\;" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_high" descr="This counter provides information on error bits that were identified on lane 6. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 6" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="phy_raw_errors_lane6_low" descr="This counter provides information on error bits that were identified on lane 6. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 6" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_high" descr="This counter provides information on error bits that were identified on lane 7. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 7" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="phy_raw_errors_lane7_low" descr="This counter provides information on error bits that were identified on lane 7. \;When FEC is enabled this induction corresponds to corrected errors.\;In PRBS test mode, indicates the number of PRBS errors\;on lane 7" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="raw_ber_coef" descr="Raw_BER = raw_ber_coef  *10^(-raw_ber_magnitude)\;" access="RO" offset="0x60.0" size="0x0.4" />
	<field name="raw_ber_magnitude" descr="Raw_BER = raw_ber_coef  *10^(-raw_ber_magnitude)\;" access="RO" offset="0x60.8" size="0x0.8" />
	<field name="fc_zero_hist" descr="Valid for links with RS FEC histograms only.\;First histogram bin with value of 0 while all higher bins are only with 0 value as well.\;0 - No histogram active / N/A value" access="RO" offset="0x60.16" size="0x0.10" />
	<field name="effective_ber_coef" descr="effective_fec_BER = effective_fec_ber_coef *10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.0" size="0x0.4" />
	<field name="effective_ber_magnitude" descr="effective_fec_BER = effective_fec_ber_coef *10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.8" size="0x0.8" />
	<field name="estimated_effective_ber_coef" descr="Supported if PCAM.feature_cap_mask bit 105 set\;estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.16" size="0x0.4" />
	<field name="estimated_effective_ber_coef_float" descr="Supported if PCAM.feature_cap_mask bit 105 set\;estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.20" size="0x0.4" />
	<field name="estimated_effective_ber_magnitude" descr="Supported if PCAM.feature_cap_mask bit 105 set\;estimated_effective_fec_BER = estimated_effective_fec_ber_coef estimated_effective_ber_coef_float*10^(-effective_fec_ber_magnitude)\;" access="RO" offset="0x64.24" size="0x0.8" />
	<field name="symbol_ber_coef" descr="Symbol_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x68.0" size="0x0.4" />
	<field name="symbol_ber_magnitude" descr="Symbol_BER = symbol_ber_coef*10^(-symbol_ber_magnitude)" access="RO" offset="0x68.8" size="0x0.8" />
	<field name="ucr_ber_coef" descr="Supported if PCAM.feature_cap_mask bit 106 set\;ucr_fec_BER = ucr_fec_ber_coef ucr_ber_coef_float*10^(-ucr_ber_magnitude)\;" access="RO" offset="0x68.16" size="0x0.4" />
	<field name="ucr_ber_coef_float" descr="Supported if PCAM.feature_cap_mask bit 106 set\;ucr_fec_BER = ucr_fec_ber_coef ucr_ber_coef_float*10^(-ucr_ber_magnitude)\;" access="RO" offset="0x68.20" size="0x0.4" />
	<field name="ucr_ber_magnitude" descr="Supported if PCAM.feature_cap_mask bit 106 set\;ucr_fec_BER = ucr_fec_ber_coef ucr_ber_coef_float*10^(-ucr_ber_magnitude)\;" access="RO" offset="0x68.24" size="0x0.8" />
	<field name="raw_ber_coef_lane1" descr="Raw_BER_lan0 = raw_ber_coef_lane1*10^(-raw_ber_magnitude_lane1)" access="RO" offset="0x6C.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane1" descr="Raw_BER_lan0 = raw_ber_coef_lane1*10^(-raw_ber_magnitude_lane1)" access="RO" offset="0x6C.8" size="0x0.8" />
	<field name="raw_ber_coef_lane0" descr="Raw_BER_lan0 = raw_ber_coef_lane0*10^(-raw_ber_magnitude_lane0)" access="RO" offset="0x6C.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane0" descr="Raw_BER_lan0 = raw_ber_coef_lane0*10^(-raw_ber_magnitude_lane0)" access="RO" offset="0x6C.24" size="0x0.8" />
	<field name="raw_ber_coef_lane3" descr="Raw_BER_lan0 = raw_ber_coef_lane3*10^(-raw_ber_magnitude_lane3)" access="RO" offset="0x70.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane3" descr="Raw_BER_lan0 = raw_ber_coef_lane3*10^(-raw_ber_magnitude_lane3)" access="RO" offset="0x70.8" size="0x0.8" />
	<field name="raw_ber_coef_lane2" descr="Raw_BER_lan0 = raw_ber_coef_lane2*10^(-raw_ber_magnitude_lane2)" access="RO" offset="0x70.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane2" descr="Raw_BER_lan0 = raw_ber_coef_lane2*10^(-raw_ber_magnitude_lane2)" access="RO" offset="0x70.24" size="0x0.8" />
	<field name="raw_ber_coef_lane5" descr="Raw_BER_lan0 = raw_ber_coef_lane5*10^(-raw_ber_magnitude_lane5)" access="RO" offset="0x74.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane5" descr="Raw_BER_lan0 = raw_ber_coef_lane5*10^(-raw_ber_magnitude_lane5)" access="RO" offset="0x74.8" size="0x0.8" />
	<field name="raw_ber_coef_lane4" descr="Raw_BER_lan0 = raw_ber_coef_lane4*10^(-raw_ber_magnitude_lane4)" access="RO" offset="0x74.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane4" descr="Raw_BER_lan0 = raw_ber_coef_lane4*10^(-raw_ber_magnitude_lane4)" access="RO" offset="0x74.24" size="0x0.8" />
	<field name="raw_ber_coef_lane7" descr="Raw_BER_lan0 = raw_ber_coef_lane7*10^(-raw_ber_magnitude_lane7)" access="RO" offset="0x78.0" size="0x0.4" />
	<field name="raw_ber_magnitude_lane7" descr="Raw_BER_lan0 = raw_ber_coef_lane7*10^(-raw_ber_magnitude_lane7)" access="RO" offset="0x78.8" size="0x0.8" />
	<field name="raw_ber_coef_lane6" descr="Raw_BER_lan0 = raw_ber_coef_lane6*10^(-raw_ber_magnitude_lane6)" access="RO" offset="0x78.16" size="0x0.4" />
	<field name="raw_ber_magnitude_lane6" descr="Raw_BER_lan0 = raw_ber_coef_lane6*10^(-raw_ber_magnitude_lane6)" access="RO" offset="0x78.24" size="0x0.8" />
	<field name="phy_effective_errors_high" descr="This counter provides information on error bits that were not corrected by FEC correction algorithm or that FEC is not active.\;" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="phy_effective_errors_low" descr="This counter provides information on error bits that were not corrected by FEC correction algorithm or that FEC is not active.\;" access="RO" offset="0x80.0" size="0x4.0" />
</node>

<node name="plcc_reg_ext" descr="" size="0x10.0" >
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_port\;1: Near_End_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band_or_PCI" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band_or_PCI=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="page_select" descr="page select index:\;0: High_symbol_error_rate_configuration_page\;1: High_bit_error_rate_configuration_page" access="INDEX" enum="High_symbol_error_rate_configuration_page=0x0,High_bit_error_rate_configuration_page=0x1" offset="0x4.0" size="0x0.8" />
	<field name="page_data" descr="Table  1053, &quot;High symbol error rate configuration Page Layout,&quot; on page  1113\;Table  1055, &quot;High bit error rate configuration Page Layout,&quot; on page  1113" subnode="plcc_reg_page_data_auto_ext" access="RW" offset="0x8.0" size="0x8.0" union_selector="$(parent).page_select" />
</node>

<node name="plcc_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x8.0" >
	<field name="High_bit_error_rate_configuration_page_ext" descr="" subnode="High_bit_error_rate_configuration_page_ext" offset="0x0.0" selected_by="High_bit_error_rate_configuration_page" size="0x4.0" />
	<field name="High_symbol_error_rate_configuration_page_ext" descr="" subnode="High_symbol_error_rate_configuration_page_ext" offset="0x0.0" selected_by="High_symbol_error_rate_configuration_page" size="0x8.0" />
</node>

<node name="plds_ext" descr="" size="0x18.0" >
	<field name="fec_uncor_cap" descr="When set, rs_fec_uncor_th is valid and configurable" access="RO" offset="0x0.0" size="0x0.1" />
	<field name="plr_retry_cap" descr="When set, plr_csn_retry_th is valid and configurable" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]." access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type, determines the way local_port is interpreted:\;0 - Local port number.\;1 - IB port number." access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="neg_res" descr="The negotiation result capability bit.\;Indicates the negotiation results for supporting the transition of the down request opcodes between the link partners.\;0: The device doesn&quot;t support receiving remote down request opcodes.\;1: The device support receiving remote down request opcodes.\;\;Note: While this bit is set to &quot;0&quot;, the link-down default states configurations will not be operational.\;This bit will be set to &apos;1&apos; in case the following 2 conditions are met: \;- Both the link partners are NVIDIA devices. \;- Both the link partners are XDR devices and above." access="RO" offset="0x4.0" size="0x0.1" />
	<field name="link_dwn_default_state_cfg" descr="The user can configure or retrieve the LinkDownDefaultState:\;0: Polling\;1: Sleep\;2: Disable" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="link_down_cap" descr="The link-down states capability mask:\;Bit 0: LinkDownDefaultState\;Bit 1: Polling\;Bit 2: Sleep\;Bit 3: Disable" access="RO" enum="LinkDownDefaultState=0x1,Polling=0x2,Sleep=0x4,Disable=0x8" offset="0x4.10" size="0x0.8" />
	<field name="config_down_cap" descr="Capability mask for the supported reasons for link-down request:\;Bit 0: LinkLocalErrorDefaultState\;Bit 1: LinkRemoteErrorDefaultState\;Bit 2: RemoteDownCMD2Disable\;Bit 3: RemoteDownCMD2Sleep\;Bit 4: RemoteDownDueToReset\;Bit 5: RemoteDownDueToUpperLayerDP\;Bit 6: RemoteDownDueToPortLock\;Bit 7: RemoteDownDueToThermal" access="RO" enum="LinkLocalErrorDefaultState=0x1,LinkRemoteErrorDefaultState=0x2,RemoteDownCMD2Disable=0x4,RemoteDownCMD2Sleep=0x8,RemoteDownDueToReset=0x10,RemoteDownDueToUpperLayerDP=0x20,RemoteDownDueToPortLock=0x40,RemoteDownDueToThermal=0x80" offset="0x4.21" size="0x0.11" />
	<field name="link_dwn_rmt_thermal_cfg" descr="The user can configure or retrieve the link-down default state for the RemoteDownDueToThermal down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable\;\;Note: TS1.PortLock opcode will be mapped to RemoteDownDueToThermal." access="RW" offset="0x8.1" size="0x0.3" />
	<field name="link_dwn_rmt_port_lock_cfg" descr="The user can configure or retrieve the link-down default state for the RemoteDownDueToPortLock down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable\;\;Note: TS1.PortLock opcode will be mapped to RemoteDownDueToPortLock." access="RW" offset="0x8.5" size="0x0.3" />
	<field name="link_dwn_rmt_up_layer_cfg" descr="The user can configure or retrieve the link-down default state for the RemoteDownDueToUpperLayerDP down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable\;\;Note: TS1.Force opcode will be mapped to RemoteDownDueToUpperLayerDP." access="RW" offset="0x8.9" size="0x0.3" />
	<field name="link_dwn_rmt_reset_cfg" descr="The user can configure or retrieve the link-down default state for the RemoteDownDueToReset down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable\;\;Note: TS1.reset_req opcode will be mapped to RemoteDownDueToReset." access="RW" offset="0x8.13" size="0x0.3" />
	<field name="link_dwn_rmt_sleep_cfg" descr="The user can configure or retrieve the link-down default state for the RemoteDownCMD2Sleep down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable\;\;Note: TS1.Sleep opcode will be mapped to RemoteDownCMD2Sleep." access="RW" offset="0x8.17" size="0x0.3" />
	<field name="link_dwn_rmt_disable_cfg" descr="The user can configure or retrieve the link-down default state for the RemoteDownCMD2Disable down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable\;\;Note: TS1.Disable opcode will be mapped to RemoteDownCMD2Disable." access="RW" offset="0x8.21" size="0x0.3" />
	<field name="link_dwn_rmt_error_cfg" descr="The user can configure or retrieve the link-down default state for the LinkRemoteErrorDefaultState down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable\;\;Note: TS1.Thermal opcode will be mapped to LinkRemoteErrorDefaultState." access="RW" offset="0x8.25" size="0x0.3" />
	<field name="link_dwn_local_error_cfg" descr="The user can configure or retrieve the link-down default state for the LinkLocalErrorDefaultState down request:\;0: LinkDownDefaultState\;1: Polling\;2: Sleep\;3: Disable" access="RW" offset="0x8.29" size="0x0.3" />
	<field name="set_mask" descr="The set bit mask allows the user to configure which fields to modify and which will not be changed on a set operation. \;Bit 0: LinkLocalErrorDefaultState_en\;Bit 1: LinkRemoteErrorDefaultState_en\;Bit 2: RemoteDownCMD2Disable_en\;Bit 3: RemoteDownCMD2Sleep_en\;Bit 4: RemoteDownDueToReset_en\;Bit 5: RemoteDownDueToUpperLayerDP_en \;Bit 6: RemoteDownDueToPortLock_en\;Bit 7: RemoteDownDueToThermal_en" access="WO" enum="LinkLocalErrorDefaultState_en=0x1,LinkRemoteErrorDefaultState_en=0x2,RemoteDownCMD2Disable_en=0x4,RemoteDownCMD2Sleep_en=0x8,RemoteDownDueToReset_en=0x10,RemoteDownDueToUpperLayerDP_en=0x20,RemoteDownDueToPortLock_en=0x40,RemoteDownDueToThermal_en=0x80" offset="0xC.0" size="0x0.11" />
	<field name="linkup_retry_iterations" descr="Number of retry &apos;N&apos; iterations allowed for linkup tries before going to link down default state.\;Valid only when link link_dwn_default_state_cfg is set to Sleep or Disabled states, ignored otherwise.\;0 - FW_default\;1-255 - &apos;N&apos; retries\;\;Note:\;Counter will iterate +1 only when exiting polling state (after peer side is detected)." access="RW" offset="0xC.24" size="0x0.8" />
	<field name="rs_fec_uncor_th" descr="Link drop trigger for number of uncorrectable FEC blocks in a 128 fec block window threshold.\;If threshold is crossed, link will be dropped or trigger recovery flow.\;0: FW_default" access="RW" offset="0x10.0" size="0x0.7" />
	<field name="plr_csn_retry_th" descr="Link drop trigger for number of PLR retry on same CSN threshold.\;If threshold is crossed, link will be dropped or trigger recovery flow.\;0: FW_default" access="RW" offset="0x10.16" size="0x0.9" />
</node>

<node name="plib_reg_ext" descr="" size="0x10.0" >
	<field name="ib_port" descr="In IB port: InfiniBand port remapping for local_port\;In Ethernet port: Label port remapping for local_port\;Note: ib_port number can only be updated when a port admin state is DISABLED." access="RW" offset="0x0.0" size="0x0.10" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="split_num" descr="Valid only for Ethernet Switches. \;Label split mapping for local_port" access="RW" offset="0x4.0" size="0x0.4" />
</node>

<node name="plibdb_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ib_port_1x" descr="IB port remapping for local port when port is configured in width of 1x.\;Note: This value is theoretical and not the actual configuration\;Range: 1.. cap_max_switch_ports\;Value of 0 means port is unmapped." access="RO" offset="0x4.0" size="0x0.10" />
	<field name="ib_port_2x" descr="IB port remapping for local port when port is configured in width of 2x.\;Note: This value is theoretical and not the actual configuration\;Range: 1.. cap_max_switch_ports\;Value of 0 means port is unmapped" access="RO" offset="0x8.0" size="0x0.10" />
	<field name="ib_port_4x" descr="IB port remapping for local port when port is configured in width of 4x.\;Note: This value is theoretical and not the actual configuration\;Range: 1.. cap_max_switch_ports\;Value of 0 means port is unmapped" access="RO" offset="0xC.0" size="0x0.10" />
</node>

<node name="pltc_reg_ext" descr="" size="0x10.0" >
	<field name="lane_mask" descr="for set operation, lane bitmask\;for query operation, only one bit shall be set" access="INDEX" offset="0x0.0" size="0x0.8" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="precoding_cap_mask" descr="0x0 - no tx precoding available / no override capability\;\;Bit 0- tx precoding override possible via local_tx_precoding_admin field\;Bit 1- rx precoding override possible via local_rx_precoding_admin field" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="local_tx_precoding_admin" descr="0 - auto\;1 - force Tx precoding\;2 - force Tx without precoding" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="local_rx_precoding_admin" descr="Rx configuration override for 100g Pam4 per lane protocols.\;0 - auto\;1 - Rx precoding enabled. \;if negotiated, request Tx precoding from peer.\;2 - Rx precoding disabled. \;if negotiated, request no Tx precoding from peer" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="local_tx_precoding_oper" descr="0 - unknown / no active link\;1 - Tx precoding enabled.\;2 - Tx precoding disabled." access="RO" offset="0xC.0" size="0x0.2" />
	<field name="local_rx_precoding_oper" descr="Rx precoding operational mode\;0 - unknown / no active link\;1 - Rx precoding enabled. \;2 - Rx precoding disabled." access="RO" offset="0xC.16" size="0x0.2" />
</node>

<node name="pmaos_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Module state (reserved while admin_status is disabled):\;0: initializing\;1: plugged_enabled\;2: unplugged\;3: module_plugged_with_error - (details in error_type).\;5: unknown" access="RO" enum="initializing=0x0,plugged_enabled=0x1,unplugged=0x2,module_plugged_with_error=0x3,unknown=0x5" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Module administrative state (the desired state of the module):\;1: enabled\;2: disabled_by_configuration\;3: enabled_once - if the module is active and then unplugged, or module experienced an error event, the operational status should go to &quot;disabled&quot; and can only be enabled upon explicit enable command.\;0xe: disconnect_cable\;\;Note - To disable a module, all ports associated with the port must be disabled first. \;Note 2 - disconnect cable will shut down the optical module in ungraceful manner. \;" access="RW" enum="enabled=0x1,disabled_by_configuration=0x2,enabled_once=0x3,disconnect_cable=0xe" offset="0x0.8" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="rst" descr="Module Reset toggle\;NOTE: setting reset while module is plugged-in will result in transition of oper_status to initialization." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="e" descr="Event Generation on operational state change:\;0: Do_not_generate_event\;1: Generate_Event\;2: Generate_Single_Event\;Not supported by secondary ASICs." access="RW" enum="Do_not_generate_event=0x0,Generate_Event=0x1,Generate_Single_Event=0x2" offset="0x4.0" size="0x0.2" />
	<field name="error_type" descr="Module error details:\;0x0: Power_Budget_Exceeded\;0x1: Long_Range_for_non_MLNX_cable_or_module\;0x2: Bus_stuck - (I2C Data or clock shorted)\;0x3: bad_or_unsupported_EEPROM\;0x4: Enforce_part_number_list\;0x5: unsupported_cable\;0x6: High_Temperature\;0x7: bad_cable - (Module/Cable is shorted)\;0x8: PMD_type_is_not_enabled - (see PMTPS)\;0xc: pcie_system_power_slot_Exceeded\;\;[DWIP] 0xf: Boot_error\;[DWIP] 0x10: Recovery_error\;[DWIP] 0x11: Submodule_failure\;\;\;Valid only when oper_status = 4&apos;b0011" access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc" offset="0x4.8" size="0x0.5" />
	<field name="operational_notification" descr="This notification can occur only if module passed initialization process\;0x0: No notifications.\;0x1: Speed degradation - the module is not enabled in its full speed due to incompatible transceiver/cable \;Valid only when oper_status = 4&apos;b0001." access="RO" offset="0x4.16" size="0x0.4" />
	<field name="rev_incompatible" descr="When in multi ASIC module sharing systems,\;This flag will be asserted in case primary and secondary FW versions are not compatible." access="RO" offset="0x4.28" size="0x0.1" />
	<field name="secondary" descr="Indicates whether the ASIC serves as a the modules secondary (=1) or primary (=0) device." access="RO" offset="0x4.29" size="0x0.1" />
	<field name="ee" descr="Event update enable. If this bit is set, event generation will be updated based on the e field. Only relevant on Set operations.\;Not supported by secondary ASICs." access="WO" offset="0x4.30" size="0x0.1" />
	<field name="ase" descr="Admin status update enable. If this bit is set, admin state will be updated based on admin_state field. Only relevant on Set() operations." access="WO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pmcr_reg_ext" descr="" size="0x2c.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="error_code_response" descr="Valid for CMIS modules.\;error code response on override values.\;0x0: ConfigUndefined\;0x1: ConfigSuccess\;0x2: ConfigRejected\;0x3: ConfigRejectedInvalidAppSel\;0x4: ConfigRejectedInvalidDataPath\;0x5: ConfigRejectedInvalidSI\;0x6: ConfigRejectedLanesInUse\;0x7: ConfigRejectedPartialDataPath\;0xC: ConfigInProgress" access="RO" enum="ConfigUndefined=0x0,ConfigSuccess=0x1,ConfigRejected=0x2,ConfigRejectedInvalidAppSel=0x3,ConfigRejectedInvalidDataPath=0x4,ConfigRejectedInvalidSI=0x5,ConfigRejectedLanesInUse=0x6,ConfigRejectedPartialDataPath=0x7,ConfigInProgress=0xc" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="cdr_override_cntl" descr="Module CDR override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x4.0" size="0x0.2" />
	<field name="cdr_override_cap" descr="Module TX and RX override control capability.\;Bit 0 - RX CDR control is possible\;Bit 0 - TX CDR control is possible" access="RO" offset="0x4.2" size="0x0.2" />
	<field name="cdr_override_value" descr="Valid only in case CDR is configured to override mode by cdr_override_cntl: \;0 - RX OFF, TX OFF\;1 - RX ON, TX OFF\;2 - RX OFF, TX ON\;3 - RX ON, TX ON" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="tx_disable_override_cntl" descr="In HCA, valid based on PCAM feature capabilities. \;Module TX_DISABLE override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x4.16" size="0x0.2" />
	<field name="tx_disable_override_value" descr="Valid only in case TX_DISABLE is configured to override mode by tx_disable_override_cntl: \;0 - TX_DISABLE is low (i.e. TX is enabled)\;1 - TX_DISABLE is high (i.e. TX is disabled)" access="RW" offset="0x4.24" size="0x0.2" />
	<field name="rx_amp_override_cntl" descr="Module RX amplitude override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="rx_amp_override_cap" descr="Module rx_amp override control capability." access="RO" offset="0x8.2" size="0x0.1" />
	<field name="rx_amp_override_value" descr="Valid only in case RX amplitude is configured to override mode by rx_amp_override_cntl" access="RW" offset="0x8.8" size="0x0.4" />
	<field name="rx_amp_override_value_cap" descr="Module rx_amp bitmask of allowed values." access="RO" offset="0x8.12" size="0x0.4" />
	<field name="rx_los_override_cntl" descr="Valid only in case RX _LOS is configured to override mode by rx_los_override_admin" access="RW" offset="0x8.16" size="0x0.2" />
	<field name="rx_los_override_cap" descr="Module RX_LOS override control capability." access="RO" offset="0x8.18" size="0x0.1" />
	<field name="rx_los_override_admin" descr="Module RX _LOS override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x8.24" size="0x0.2" />
	<field name="rx_emp_override_cntl" descr="Module RX emphasis override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0xC.0" size="0x0.2" />
	<field name="rx_emp_override_cap" descr="Module rx_emp override control capability." access="RO" offset="0xC.2" size="0x0.1" />
	<field name="rx_emp_override_value" descr="For CMIS modules, pre emphasis equalization value.\;For SFF modules, emphasis equalization value.\;Valid only in case RX emphasis is configured to override mode by rx_emp_override_cntl" access="RW" offset="0xC.8" size="0x0.4" />
	<field name="rx_emp_override_value_cap" descr="Module rx_emp max allowed values." access="RO" offset="0xC.12" size="0x0.4" />
	<field name="rx_post_emp_override_cntl" descr="Module RX emphasis override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0xC.16" size="0x0.2" />
	<field name="rx_post_emp_override_cap" descr="Module rx_post_emp override control capability." access="RO" offset="0xC.18" size="0x0.1" />
	<field name="rx_post_emp_override_value" descr="Valid for CMIS modules only.\;Post emphasis equalization value.\;Valid only in case RX emphasis is configured to override mode by rx_post_emp_override_cntl" access="RW" offset="0xC.24" size="0x0.4" />
	<field name="rx_post_emp_override_value_cap" descr="Module rx_post_emp max allowed values." access="RO" offset="0xC.28" size="0x0.4" />
	<field name="tx_equ_override_cntl" descr="Module TX equalization override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x10.0" size="0x0.2" />
	<field name="tx_equ_override_cap" descr="Module TX equalization override control capability." access="RO" offset="0x10.2" size="0x0.1" />
	<field name="tx_equ_override_value" descr="Valid only in case TX equalization is configured to override mode by tx_equ_override_cntl." access="RW" offset="0x10.8" size="0x0.4" />
	<field name="tx_equ_override_value_cap" descr="Module tx_eq max allowed values." access="RO" offset="0x10.12" size="0x0.4" />
	<field name="tx_adaptive_override_value" descr="0 - disable adaptive Tx Equalization\;1 - enable adaptive Tx equalization\;Valid only in case TX equalization is configured to override mode by tx_adaptive_override_cntrl." access="RW" offset="0x10.17" size="0x0.1" />
	<field name="tx_adaptive_override_cntrl" descr="Module adaptive tuning flow override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - override" access="RW" offset="0x10.24" size="0x0.2" />
	<field name="tx_adaptive_override_cap" descr="Module TX adaptive tuning flow override control capability." access="RO" offset="0x10.26" size="0x0.1" />
	<field name="ap_sel_override_cntrl" descr="Module Application select override control:\;0 - Auto (default)\;1 - Use Module&apos;s Default application value\;2 - Override" access="RW" offset="0x18.0" size="0x0.2" />
	<field name="ap_sel_override_value" descr="Application Select from the applications list advertised by the module. Up to 15 applications available.\;\;Values range from 1 to 15.\;\;Note: application can be set with default SI values defined by the module or SI defined by the host" access="RW" offset="0x18.8" size="0x0.4" />
	<field name="media_type_override_cntl" descr="Module media type override control:\;0 - Auto (default)\;1 - Keep the module configuration\;2 - Override" access="RW" offset="0x1C.0" size="0x0.2" />
	<field name="media_type_override_cap" descr="Media type override capability is possible via media_type_override_cntrl field" access="RO" offset="0x1C.2" size="0x0.1" />
	<field name="media_type_override_value" descr="Valid only in case media_type_override_cntrl is configured to override mode.\;Configures module media type peer side for optimal performance\;0: Peer_is_retimed_module - [internal] &quot;Optical_retimed &quot; in CDB\;1: Peer_is_LPO_module - [internal] &quot;Optical_Did&quot; in CDB\;2: reserved\;3: reserved" access="RW" offset="0x1C.8" size="0x0.2" />
	<field name="prec_host_tx_override_cntl" descr="Precoding host Tx override control.\;0 - Auto (FW default)\;1 - Keep the module configuration - module read\;2 - Override - overrides according to prec_host_tx_override_val\;Note:\;According to configured value above,\;get operation prec_host_tx_override_val reads the value which is indexed to.\;" access="RW" offset="0x20.0" size="0x0.2" />
	<field name="prec_host_rx_override_cntl" descr="Precoding host Rx override control.\;0 - Auto (FW default)\;1 - Keep the module configuration - module read\;2 - Override - overrides according to prec_host_rx_override_val\;Note:\;According to configured value above,\;get operation prec_host_rx_override_val reads the value which is indexed to.\;" access="RW" offset="0x20.2" size="0x0.2" />
	<field name="prec_host_cap" descr="Precoding host override is supported" access="RW" offset="0x20.7" size="0x0.1" />
	<field name="prec_host_tx_override_val" descr="Precoding host Tx override value.\;Set is valid only in case prec_host_tx_override_cntl is configured to override mode.\;0: precoding_line_tx_disabled\;1: precoding_line_tx_enabled" access="RW" offset="0x20.8" size="0x0.1" />
	<field name="prec_host_rx_override_val" descr="Precoding host Rx override value.\;Set is valid only in case prec_host_rx_override_cntl is configured to override mode.\;0: precoding_host_rx_disabled\;1: precoding_host_rx_enabled" access="RW" offset="0x20.9" size="0x0.1" />
	<field name="prec_line_tx_override_cntl" descr="Precoding line Tx override control.\;0 - Auto (FW default)\;1 - Keep the module configuration - module read\;2 - Override - overrides according to prec_line_tx_override_val\;Note:\;According to configured value above,\;get operation prec_line_tx_override_val reads the value which is indexed to.\;" access="RW" offset="0x20.16" size="0x0.2" />
	<field name="prec_line_rx_override_cntl" descr="Precoding line Rx override control.\;0 - Auto (FW default)\;1 - Keep the module configuration - module read\;2 - Override - overrides according to prec_line_rx_override_val\;Note:\;According to configured value above,\;get operation prec_line_rx_override_val reads the value which is indexed to.\;" access="RW" offset="0x20.18" size="0x0.2" />
	<field name="prec_line_cap" descr="Precoding line override is supported" access="RW" offset="0x20.23" size="0x0.1" />
	<field name="prec_line_tx_override_val" descr="Precoding line Tx override value.\;Set is valid only in case prec_line_tx_override_cntl is configured to override mode.\;0: precoding_line_tx_disabled\;1: precoding_line_tx_enabled" access="RW" offset="0x20.24" size="0x0.1" />
	<field name="prec_line_rx_override_val" descr="Precoding line Rx override value.\;Set is valid only in case prec_line_rx_override_cntl is configured to override mode.\;0: precoding_line_rx_disabled\;1: precoding_line_rx_enabled" access="RW" offset="0x20.25" size="0x0.1" />
</node>

<node name="pmdr_reg_ext" descr="" size="0x48.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.0" size="0x0.2" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="mcm_tile_valid" descr="0 if there is no MCM tile arch" access="RO" offset="0x0.12" size="0x0.1" />
	<field name="gb_valid" descr="0 if there is no Gearbox/Retimer arch" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="[7:0] bits for Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0 - 40nm products\;1 - 28nm products\;3 - 16nm products\;4 - 7nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid\;2 - Bad Param (Values are not ready yet - during polling)\;3 - Invalid index of local_port or label_port" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="pport_msb" descr="[9:8] pport bits" access="RO" offset="0x4.6" size="0x0.2" />
	<field name="cluster" descr="Logical cluster number" access="RO" offset="0x4.8" size="0x0.7" />
	<field name="module" descr="" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="pport" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="ib_port" descr="" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="module_lane_mask" descr="lane mask of active lanes on module" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="swid" descr="" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="split" descr="Number of ports the label port is split to.\;0 - split to 1\;1 - split to 2\;2 - split to 4\;3 - split to 8" access="RO" offset="0x8.24" size="0x0.3" />
	<field name="gb_dp_num" descr="DataPath number in GB/Retimer of the port" access="RO" offset="0x8.27" size="0x0.5" />
	<field name="lp_query_msb" descr="MSB Local port bits [9:8] index for the label port chosen (in case pnat field is &apos;1&apos;)." access="RO" offset="0xC.0" size="0x0.2" />
	<field name="lbp_query_msb" descr="MSB Label port bits [9:8] index." access="RO" offset="0xC.2" size="0x0.2" />
	<field name="tile_pport_msb" descr="MSB tile_pport bits [7:6] index." access="RO" offset="0xC.4" size="0x0.2" />
	<field name="local_port_query" descr="LSB Local port bits [7:0] index for the label port chosen (in case pnat field is &apos;1&apos;)." access="RO" offset="0xC.16" size="0x0.8" />
	<field name="label_port_query" descr="Label port index for the local port chosen (in case pnat field is &apos;0&apos;)." access="RO" offset="0xC.24" size="0x0.8" />
	<field name="gearbox_die_num" descr="Number of the Gearbox/Retimer the local_port is related to.\;valid only when gb_valid is 1" access="RO" offset="0x10.0" size="0x0.7" />
	<field name="tile_pport" descr="" access="RO" offset="0x10.8" size="0x0.5" />
	<field name="pll_cnt_rx" descr="Number of common PLLs mapped to port rx lanes." access="RO" offset="0x10.13" size="0x0.3" />
	<field name="mcm_tile_num" descr="Number of the MCM Tile the local_port is related to.\;valid only when mcm_tile_valid is 1\;" access="RO" offset="0x10.16" size="0x0.8" />
	<field name="tile_cluster" descr="" access="RO" offset="0x10.24" size="0x0.4" />
	<field name="slot_index" descr="Reserved for HCA \;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="RO" offset="0x10.28" size="0x0.4" />
	<field name="lane0_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.0" size="0x0.3" />
	<field name="lane1_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.3" size="0x0.3" />
	<field name="lane2_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.6" size="0x0.3" />
	<field name="lane3_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.9" size="0x0.3" />
	<field name="lane4_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.12" size="0x0.3" />
	<field name="lane5_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.15" size="0x0.3" />
	<field name="lane6_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.18" size="0x0.3" />
	<field name="lane7_physical_rx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical rx lane mapping" access="RO" offset="0x14.21" size="0x0.3" />
	<field name="pll_cnt_tx" descr="Number of common PLLs mapped to port for tx lanes." access="RO" offset="0x14.24" size="0x0.3" />
	<field name="vl_num" descr="largest VL number of the port.\;for e.g if vl_num = 3\;VL&lt;0-3&gt;_lane_map are only valid" access="RO" offset="0x14.27" size="0x0.5" />
	<field name="lane0_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.0" size="0x0.3" />
	<field name="lane1_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.3" size="0x0.3" />
	<field name="lane2_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.6" size="0x0.3" />
	<field name="lane3_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.9" size="0x0.3" />
	<field name="lane4_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.12" size="0x0.3" />
	<field name="lane5_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.15" size="0x0.3" />
	<field name="lane6_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.18" size="0x0.3" />
	<field name="lane7_physical_tx" descr="LSB [2:0] bits for logical lane&lt;i&gt; to physical tx lane mapping" access="RO" offset="0x18.21" size="0x0.3" />
	<field name="pll_index" descr="minimal index of pll group of pll that port uses for tx lanes.\;For all common pll&apos;s that are mapped to the port: [pll_index, pll_index+ 1, ... pll_index + pll_cnt]" access="RO" offset="0x18.24" size="0x0.8" />
	<field name="VL0_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.0" size="0x0.4" />
	<field name="VL1_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.4" size="0x0.4" />
	<field name="VL2_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.8" size="0x0.4" />
	<field name="VL3_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.12" size="0x0.4" />
	<field name="VL4_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.16" size="0x0.4" />
	<field name="VL5_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.20" size="0x0.4" />
	<field name="VL6_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.24" size="0x0.4" />
	<field name="VL7_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x1C.28" size="0x0.4" />
	<field name="VL8_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="VL9_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.4" size="0x0.4" />
	<field name="VL10_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.8" size="0x0.4" />
	<field name="VL11_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.12" size="0x0.4" />
	<field name="VL12_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.16" size="0x0.4" />
	<field name="VL13_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.20" size="0x0.4" />
	<field name="VL14_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.24" size="0x0.4" />
	<field name="VL15_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x20.28" size="0x0.4" />
	<field name="VL16_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.0" size="0x0.4" />
	<field name="VL17_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.4" size="0x0.4" />
	<field name="VL18_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.8" size="0x0.4" />
	<field name="VL19_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.12" size="0x0.4" />
	<field name="VL20_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.16" size="0x0.4" />
	<field name="VL21_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.20" size="0x0.4" />
	<field name="VL22_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.24" size="0x0.4" />
	<field name="VL23_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x24.28" size="0x0.4" />
	<field name="VL24_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.0" size="0x0.4" />
	<field name="VL25_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.4" size="0x0.4" />
	<field name="VL26_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.8" size="0x0.4" />
	<field name="VL27_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.12" size="0x0.4" />
	<field name="VL28_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.16" size="0x0.4" />
	<field name="VL29_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.20" size="0x0.4" />
	<field name="VL30_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.24" size="0x0.4" />
	<field name="VL31_lane_map" descr="logical lane number that maps to VL_x lane" access="RO" offset="0x28.28" size="0x0.4" />
	<field name="module_lane_mask_msb" descr="Module extension for MSB" access="RO" offset="0x3C.8" size="0x0.24" />
	<field name="oe_lane7_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.0" size="0x0.4" />
	<field name="oe_lane6_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.4" size="0x0.4" />
	<field name="oe_lane5_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.8" size="0x0.4" />
	<field name="oe_lane4_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.12" size="0x0.4" />
	<field name="oe_lane3_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.16" size="0x0.4" />
	<field name="oe_lane2_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.20" size="0x0.4" />
	<field name="oe_lane1_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.24" size="0x0.4" />
	<field name="oe_lane0_to_els_logical_laser" descr="OE optical lane to ELS logical laser mapping" access="RO" offset="0x40.28" size="0x0.4" />
	<field name="els_module_index" descr="ELS module index" access="RO" offset="0x44.0" size="0x0.8" />
	<field name="els_index" descr="ELS label index" access="RO" offset="0x44.10" size="0x0.6" />
	<field name="oe_mcu_index" descr="Optical engine MCU index" access="RO" offset="0x44.24" size="0x0.7" />
	<field name="cpo_indication" descr="CPO indication:\;0 - not CPO\;1 - CPO\;" access="RO" offset="0x44.31" size="0x0.1" />
</node>

<node name="pmlp_reg_ext" descr="" size="0x40.0" >
	<field name="width" descr="0: unmap_local_port\;1: x1 - lane 0 is used\;2: x2 - lanes 0,1 are used\;4: x4 - lanes 0,1,2 and 3 are used\;8: x8 - lanes 0-7 are used\;\;Other - reserved" access="RW" enum="unmap_local_port=0x0,x1=0x1,x2=0x2,x4=0x4,x8=0x8" offset="0x0.0" size="0x0.8" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="m_lane_m" descr="Module lane mapping: \;0 - Local to Module mapping include module lanes mapping\;1 - Local to Module mapping only, without lane mapping\;\;When this operational is set (&apos;1&apos;), the following fields are ignored in SET command and should return the value &quot;0&quot; in GET commands: \;PMLP.rxtx\;PMLP.lane&lt;i&gt;_module_mapping.tx_lane\;PMLP.lane&lt;i&gt;_module_mapping.rx_lane" access="OP" offset="0x0.28" size="0x0.1" />
	<field name="mod_lab_map" descr="Supported only if PCAM.feature_cap_mask bit 112 is set\;On set operation, indicates ports lane mapping configuration if it should be taken from module mappings or label mappings.\;0: module_mapping_selected - port lanes are mapped according to module lanes from lane_module_mapping[0-7] fields. Module field is considered as module index.\;1: label_mapping_selected - port lanes are mapped according to label lanes from lane_module_mapping[0-7] fields. Module field is considered as Label index.\;" access="INDEX" offset="0x0.29" size="0x0.1" />
	<field name="rxtx" descr="Use different configuration for RX and TX.\;If this bit is cleared, the TX value is used for both RX and TX. When set, the RX configuration is taken from the separate field. This is to enable backward compatible implementation." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="lane_module_mapping" descr="Module SerDes for lane &lt;i&gt;\;Up to 8 SerDes in a module can be mapped to a local port." subnode="lane_2_module_mapping_ext" access="RW" high_bound="7" low_bound="0" offset="0x4.0" size="0x20.0" />
</node>

<node name="pmmp_cmis_protocol_override_layout_ext" descr="" size="0xc.0" >
	<field name="host_electrical_compliance" descr="Host Electrical compliance code per CMIS byte 86 based on SFF-8024 table 4-5\;0 - unspecified\;1- 1000BASE - CX\;2 - XAUI\;3 - XFI\;4 - SFI\;5 - 25GAUI C2M\;6 - XLAUI C2M\;7 - XLPPI\;8 - LAUI-2 C2M\;9 - 50GAUI-2 C2M\;10 - 50GAUI-1 C2M\;11 - CAUI-4 C2M\;13 - 100GAUI-2 C2M\;15 - 200GAUI-4 C2M\;17 - 400GAUI-8 C2M\;20 - 25GBASE-CR CA-L\;21 - 25GBASE-CR CA-S\;22 - 25GBASE-CR CA-N\;23 - 40GBASE-CR4\;24 - 50GBASE-CR\;26 - 100GBASE-CR4\;27 - 100GBASE-CR2\;28 - 200GBASE-CR4\;29 - 400GBASE-CR8\;\;65 - CAUI-4 C2M no FEC\;66 - CAUI-4 C2M RS FEC\;67 - 50GBASE-CR2 RS FEC\;68 - 50GBASE-CR2 FC FEC\;69 - 50GBASE-CR2 no FEC" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="cable_breakout" descr="bits 7-0 as per byte 210 in CMIS, Near-End implementation\;Bit 0 - Channel 1 implementation \;Bit 1 - Channel 2 implementation\;Bit 2 - Channel 3 implementation\;Bit 3 - Channel 4 implementation\;Bit 4- Channel 5 implementation \;Bit 5- Channel 6 implementation\;Bit 6- Channel 7 implementation\;Bit 7- Channel 8 implementation\;\;for each channel:\;0 - Channel implemented \;1 - Channel not - implemented\;\;bit 12-8 as per byte 211 4-0 in CMIS, Far-End implementation\;" access="RW" offset="0x0.8" size="0x0.13" />
	<field name="media_type_encoding" descr="Byte 85 in CMIS. Media type encoding override\;0: undefined\;1: Optical_MMF\;2: Optical_SMF\;3: Passive_copper\;4: Active_cables\;5: BASE_T" access="RW" offset="0x0.21" size="0x0.4" />
	<field name="mod_pwrup_maxduration" descr="Module transition to high power maximum duration. coded according to table 8-29 of CMIS." access="RW" offset="0x0.28" size="0x0.4" />
	<field name="media_compliance" descr="Module media interface compliance for CMIS, per byte 87.\;Values taken according to module_media_type from SFF-8024:\;\;If MMF - SFF-8024 table 4-6, MM media interface codes\;If SMF - SFF-8024 table 4-7, SM media interface code\;\;If Active cable- SFF-8024 table 4-9 Active cable assembly code:\;0 -unspecified\;1 - Active cable assembly with BER &lt; 1e-12\;2 - Active cable assembly with BER &lt; 5e-5\;3 - Active cable assembly with BER &lt; 2.6e-4\;4 - Active cable assembly with BER &lt; 1e-6" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="module_media_type" descr="Module media type encoding, per byte 85 of CMIS:\;0 - undefined\;1 - MMF\;2 - SMF\;3 - passive Copper\;4 - Active cables\;5 - Base-T" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="dp_tx_off_maxduration" descr="Data path turn off maximum duration. coded according to table 8-29 of CMIS 4.0." access="RW" offset="0x4.16" size="0x0.4" />
	<field name="dp_tx_on_maxduration" descr="Data path turn on maximum duration. coded according to table 8-29 of CMIS 4.0." access="RW" offset="0x4.20" size="0x0.4" />
	<field name="dp_init_maxduration" descr="Data path init maximum duration. coded according to table 8-29 of CMIS 4.0." access="RW" offset="0x4.28" size="0x0.4" />
	<field name="cmis_override_mask" descr="bitmask of override from CMIS protocol bytes page.\;Relevant only when Bit 9 is set in eeprom_override field.\;inverse polarity.\;0 - override\;1 - don&apos;t override\;\;Bit 0 - cable_breakout\;Bit 1 -host_electrical_compliance\;Bit 2 - module_media_type\;Bit 3 - media_compliance\;Bit 4 - mod_pwrup_maxDuration\;Bit 5 - dp_init_maxDuration\;Bit 6 - dp_tx_on_maxDuration\;Bit 7 - dp_tx_off_maxDuration\;Bit 9 - media_type_encoding" access="RW" offset="0x8.0" size="0x0.16" />
</node>

<node name="pmmp_qsfp_protocol_override_layout_ext" descr="" size="0xc.0" >
	<field name="ethernet_compliance_code" descr="Ethernet Compliance Codes bit mask (10/40G/100G)\;Override byte131 per SFF-8636:\;Bit 7 - Extended Specification Compliance valid\;Bit 6 - 10GBASE-LRM\;Bit 5 - 10GBASE-LR\;Bit 4 - 10GBASE-SR\;Bit 3 - 40GBASE-CR4\;Bit 2 - 40GBASE-SR4\;Bit 1 - 40GBASE-LR4\;Bit 0 - 40G Active Cable (XLPPI)" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="cable_breakout" descr="Override of byte113 per SFF-8636:\;Bit 6-4 (Far End):\;0 - Far end is unspecified\;1 - Cable with single far end with 4 channels implemented, or separable module with 4-channel connector\;2 - Cable with single far end with 2 channels implemented, or separable module with 2-channel connector\;3 - Cable with single far end with 1 channel implemented, or separable module with 1-channel connector\;4 - 4 far ends with 1 channel implemented in each (i.e. 4x1 break out)\;5 - 2 far ends with 2 channels implemented in each (i.e. 2x2 break out)\;6 - 2 far ends with 1 channel implemented in each (i.e. 2x1 break out)\;\;Bit 3-0 (Near End)\;Bit 0 - Channel 1 implementation \;Bit 1 - Channel 2 implementation\;Bit 2 - Channel 3 implementation\;Bit 3 - Channel 4 implementation\;\;for each channel:\;0 - Channel implemented \;1 - Channel not - implemented\;" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="giga_ethernet_compliance_code" descr="Gigabit Ethernet Compliance Codes \;Override byte134 per SFF-8636:\;Bit 3 - 1000BASE-T\;Bit 2 - 1000BASE-CX\;Bit 1 - 1000BASE-LX\;Bit 0 - 1000BASE-SX" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes \;Override byte192 per SFF-8636:\;0 - Unspecified\;1 - 100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC\;2 - 100GBASE-SR4 or 25GBASE-SR\;3 - 100GBASE-LR4 or 25GBASE-LR\;4 - 100GBASE-ER4 or 25GBASE-ER\;5 - 100GBASE-SR10\;6 - 100G CWDM4\;7 - 100G PSM4 Parallel SMF\;8 - 100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC\;11 - 100GBASE-CR4 or 25GBASE-CR CA-L\;12 - 25GBASE-CR CA-S\;13 - 25GBASE-CR CA-N\;16 - 40GBASE-ER4\;17 - 4 x 10GBASE-SR\;18 - 40G PSM4 Parallel SMF\;19 - G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)\;20 - G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)\;21 - G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)\;22 - 10GBASE-T with SFI electrical interface\;23 - 100G CLR4\;24 - 100G AOC or 25GAUI C2M AOC. No FEC\;25 - 100G ACC or 25GAUI C2M ACC. No FEC" access="RW" offset="0x4.8" size="0x0.8" />
</node>

<node name="pmmp_reg_ext" descr="" size="0x40.0" >
	<field name="sticky" descr="When set will keep eeprom_override values after plug out event" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="apply_im" descr="When set, override will be configured immediately without PMAOS toggle requirement if supported.\;for list supported overrides see eeprom_override description.\;supported if PCAM.bit 87 set" access="WO" offset="0x0.1" size="0x0.1" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="sub_module" descr="Sub module selector.\;0: sub_module1\;1: sub_module2" access="INDEX" enum="sub_module1=0x0,sub_module2=0x1" offset="0x0.28" size="0x0.1" />
	<field name="eeprom_override" descr="Override/ignore EEPROM advertisement properties bitmask: \;Bit 0: Override_cable_protocols_and_technology_for_QSFP\;Bit 1: Override_cable_protocols_and_technology_for_SFP\;Bit 2: Ignore_Power_Class - set high power\;Bit 3: Override_Cable_Length \;Bit 4: Override_Attenuation\;Bit 8: Set_Module_to_Low_Power\;Bit 9: Override_cable_protocols_and_technology_for_CMIS - based modules QSFP-DD/ OSFP/ DSFP/ SFP-DD\;Bit 11: Override_module_type\;Bit 12: Override_ELS_lane_power\;Bit 13: Override_ELS_output_fiber_checked_flag\;Bit 14: Override_ELS_lane_enable\;Supported overrides with apply_im is bits 8, 12, 13, 14.\;rest of overrides will be applied only after PMAOS toggle.\;For bits 11-14, the override is done separately - each configuration at a time" access="RW" enum="Override_cable_protocols_and_technology_for_QSFP=0x1,Override_cable_protocols_and_technology_for_SFP=0x2,Ignore_Power_Class=0x4,Override_Cable_Length=0x8,Override_Attenuation=0x10,Set_Module_to_Low_Power=0x100,Override_cable_protocols_and_technology_for_CMIS=0x200,Override_module_type=0x800,Override_ELS_lane_power=0x1000,Override_ELS_output_fiber_checked_flag=0x2000,Override_ELS_lane_enable=0x4000" offset="0x4.0" size="0x0.16" />
	<field name="eeprom_override_mask" descr="Write Mask bit (negative polarity):\;0 - allow write\;1 - ignore write\;On write commands, indicates which of the bits from eeprom_override field are updated.\;Reserved on read operations." access="WO" offset="0x4.16" size="0x0.16" />
	<field name="qsfp_cable_protocol_technology" descr="Protocol technology override for QSFP cable or CMIS based cable (QSFP-DD/OSFP)\;Valid only when the protocols and technology for QSFP is overridden as indicated by eeprom_override\;Table  605, &quot;PMMP - QSFP Protocol Bytes Override Layout,&quot; on page  635\;Table  609, &quot;PMMP - CMIS Protocol Bytes Override Layout,&quot; on page  639" subnode="pmmp_reg_qsfp_cable_protocol_technology_auto_ext" access="RW" offset="0x8.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="sfp_cable_protocol_technology" descr="Valid only when the protocols and technology is overridden as indicated by eeprom_override\;Table  607, &quot;PMMP - SFP Protocol Bytes Override Layout,&quot; on page  638" subnode="pmmp_reg_sfp_cable_protocol_technology_auto_ext" access="RW" offset="0x14.0" size="0xc.0" union_selector="$(parent).eeprom_override" />
	<field name="cable_length" descr="Length of cable assembly, units of 1 m for non CMIS cables.\;\;for CMIS cables, represents cable length field:\;bits 6:7 represent cable_length_multiplier for calculating cable length\;00 - 0.1 multiplier (0.1 to 6.3m)\;01- 1 multiplier (1 to 63m)\;10 - 10 multiplier (10 to 630m)\;11 - 100 multiplier (100 to 6300m)\;\;Valid only when the cable length is overridden as indicated by eeprom_override." access="RW" offset="0x20.0" size="0x0.8" />
	<field name="module_type" descr="0: passive_copper_cable\;1: active_copper_cable\;2: Liner_far_end_equalized_copper\;3: Linear_full_equalized_copper\;4: Linear_optical_module - Direct Drive\;5: active_optical_module\;6: on_board_retimer_over_transceiver" access="RW" offset="0x20.8" size="0x0.4" />
	<field name="attenuation_5g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x24.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 7GHz in db." access="RW" offset="0x24.8" size="0x0.8" />
	<field name="attenuation_12g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 12GHz in db." access="RW" offset="0x24.16" size="0x0.8" />
	<field name="attenuation_25g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 25GHz in db." access="RW" offset="0x24.24" size="0x0.8" />
	<field name="attenuation_53g" descr="Valid only when the attenuation is overridden as indicated by eeprom_override.\;Attenuation - total channel attenuation @ 53GHz in db." access="RW" offset="0x28.8" size="0x0.8" />
	<field name="lane_enable" descr="Laser Enable. Valid only when override_ELS_lane_enable_and_ELS_putput_fiber_checked_flag is overridden as indicated by eeprom_override. Bit mask for ELS laser, should be same bitmask as output_fiber_checked_flag:\;0 - disable laser\;1 - enable laser" access="RW" offset="0x28.16" size="0x0.8" />
	<field name="output_fiber_checked_flag" descr="Set power restriction for ELS laser. Valid only when override_ELS_lane_enable is overridden as indicated by eeprom_override. This bit mask, should be same bitmask as lane_enable:\;0 - set restriction on\;1 - set restriction off" access="RW" offset="0x28.24" size="0x0.8" />
	<field name="power_setpoint_lane" descr="Laser optical power for laser &lt;i&gt;, in unit of 10   W. Valid only when override_ELS_lanepower is overridden as indicated by eeprom_override" access="RW" high_bound="7" low_bound="0" offset="0x30.16" size="0x10.0" />
</node>

<node name="pmmp_reg_qsfp_cable_protocol_technology_auto_ext" descr="" attr_is_union="1" size="0xc.0" >
	<field name="pmmp_cmis_protocol_override_layout_ext" descr="" subnode="pmmp_cmis_protocol_override_layout_ext" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_CMIS" size="0xc.0" />
	<field name="pmmp_qsfp_protocol_override_layout_ext" descr="" subnode="pmmp_qsfp_protocol_override_layout_ext" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_QSFP" size="0xc.0" />
</node>

<node name="pmmp_reg_sfp_cable_protocol_technology_auto_ext" descr="" attr_is_union="1" size="0xc.0" >
	<field name="pmmp_sfp_protocol_bytes_override_ext" descr="" subnode="pmmp_sfp_protocol_bytes_override_ext" offset="0x0.0" selected_by="Override_cable_protocols_and_technology_for_SFP" size="0xc.0" />
</node>

<node name="pmmp_sfp_protocol_bytes_override_ext" descr="" size="0xc.0" >
	<field name="tengig_ethernet_compliance_code" descr="10G Ethernet Compliance Codes\;Override byte3 per SFF-8472:\;Bit 7 - 10G Base-ER \;Bit 6 - 10G Base-LRM \;Bit 5 - 10G Base-LR \;Bit 4 - 10G Base-SR\;" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="cable_technology" descr="SFP+ Cable Technology\;Override byte8 per SFF-8472:\;Bit 3 - Active Cable\;Bit 2 - Passive Cable" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="bit_rate" descr="Override byte12 per SFF-8472\;The nominal bit (signaling) rate (BR, nominal) is specified in units of 100 MBd, rounded off to the nearest 100 MBd.\;A value of FFh indicates the bit rate is greater than 25.0Gb/s" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="ethernet_compliance_code" descr="Ethernet Compliance Codes \;Override byte6 per SFF-8472:\;Bit 7 - BASE-PX \;Bit 6 - BASE-BX10 \;Bit 5 - 100BASE-FX \;Bit 4 - 100BASE-LX/LX10 \;Bit 3 - 1000BASE-T \;Bit 2 - 1000BASE-CX \;Bit 1 - 1000BASE-LX \;Bit 0 - 1000BASE-SX\;" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ext_ethernet_compliance_code" descr="Extended Specification Compliance Codes (25GE) \;Override byte36 per SFF-8472:\;0 - Unspecified\;1 - 100G AOC (Active Optical Cable) or 25GAUI C2M AOC with FEC\;2 - 100GBASE-SR4 or 25GBASE-SR\;3 - 100GBASE-LR4 or 25GBASE-LR\;4 - 100GBASE-ER4 or 25GBASE-ER\;5 - 100GBASE-SR10\;6 - 100G CWDM4\;7 - 100G PSM4 Parallel SMF\;8 - 100G ACC (Active Copper Cable) or 25GAUI C2M ACC. with FEC\;11 - 100GBASE-CR4 or 25GBASE-CR CA-L\;12 - 25GBASE-CR CA-S\;13 - 25GBASE-CR CA-N\;16 - 40GBASE-ER4\;17 - 4 x 10GBASE-SR\;18 - 40G PSM4 Parallel SMF\;19 - G959.1 profile P1I1-2D1 (10709 MBd, 2km, 1310nm SM)\;20 - G959.1 profile P1S1-2D2 (10709 MBd, 40km, 1550nm SM)\;21 - G959.1 profile P1L1-2D2 (10709 MBd, 80km, 1550nm SM)\;22 - 10GBASE-T with SFI electrical interface\;23 - 100G CLR4\;24 - 100G AOC or 25GAUI C2M AOC. No FEC\;25 - 100G ACC or 25GAUI C2M ACC. No FEC" access="RW" offset="0x4.8" size="0x0.8" />
</node>

<node name="pmpc_reg_ext" descr="" size="0x20.0" >
	<field name="module_state_updated" descr="On read operation:\;A bit vector where each bit represents a module (bit 0 represents module 0 etc). A set bit indicates one or more changes in the module state (plugged/unplugged/unknown) has happened since the last time the bit was cleared. The default is 1 in all relevant bits.\;On write operation:\;Used to clear the module_status_updated bits. Writing a set bit clears the relevant bit in the module_status_updated vector. Cleared bits in this field preserve the value of the relevant bit in the bit vector. The software cannot set a bit in the module_status_updated vector.\;Note: To prevent a case where an update is missed by the software, it is recommended to use the flow below:\;Read the module_status_updated vector\;Find a bit(s) relevant to a module(s) the software would like to handle\;Clear the relevant bit(s)\;Handle the module (e.g. read the module parameters using MCIA register)\;Read module_status_updated again to make sure the status did not change after reading the cable information." access="RW" high_bound="7" low_bound="0" offset="0x0.0" size="0x20.0" />
</node>

<node name="pmpd_reg_ext" descr="" size="0x30.0" >
	<field name="status" descr="0 - Diagnostic data not supported\;1 - Normal mission mode. \;2 - PRBS checker is not locked. \;3 - PRBS checker is locked." access="RO" offset="0x0.0" size="0x0.4" />
	<field name="cl" descr="clear counters" access="OP" offset="0x0.4" size="0x0.1" />
	<field name="lane" descr="Module lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="host_media" descr="Host or Media lanes\;0 - Media lanes\;1 - Host lanes" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="module" descr="module to access" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="errors_cap" descr="Bits Errors count capability" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="ber_cap" descr="BER measure capability" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="snr_cap" descr="SNR measure capability" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="prbs_bits_high" descr="This counter provides information on the total amount of prbs traffic (bits) received on module&apos;s side." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="prbs_bits_low" descr="This counter provides information on the total amount of prbs traffic (bits) received on module&apos;s side." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="prbs_errors_high" descr="This counter provides information on the total amount of prbs errors detected on module&apos;s side." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="prbs_errors_low" descr="This counter provides information on the total amount of prbs errors detected on module&apos;s side." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="measured_snr" descr="SNR in dB\;0 - not supported." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="ber_coef" descr="BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x18.0" size="0x0.4" />
	<field name="ber_magnitude" descr="BER = raw_ber_coef*10^(-raw_ber_magnitude)" access="RO" offset="0x18.8" size="0x0.8" />
</node>

<node name="pmpe_reg_ext" descr="" size="0x10.0" >
	<field name="module_status" descr="Port operational state:\;1: plugged_enabled\;2: unplugged\;3: module_plugged_error - details in error_type \;5: unknown" access="RO" enum="plugged_enabled=0x1,unplugged=0x2,module_plugged_error=0x3,unknown=0x5" offset="0x0.0" size="0x0.4" />
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="error_type" descr="Module error details:\;0x0: Power_Budget_Exceeded\;0x1: Long_Range_for_non_MLNX_cable_or_module\;0x2: Bus_stuck - (I2C Data or clock shorted)\;0x3: bad_or_unsupported_EEPROM\;0x4: Enforce_part_number_list\;0x5: unsupported_cable\;0x6: High_Temperature\;0x7: bad_cable - (Module/Cable is shorted)\;0x8: PMD_type_is_not_enabled - (see PMTPS).\;0xc: pcie_system_power_slot_Exceeded\;0xf: Boot_error - [DWIP]\;0x10: Recovery_error - [DWIP]\;0x11: Submodule_failure - [DWIP]\;\;\;\;Valid only when (oper_status = 0x3)." access="RO" enum="Power_Budget_Exceeded=0x0,Long_Range_for_non_MLNX_cable_or_module=0x1,Bus_stuck=0x2,bad_or_unsupported_EEPROM=0x3,Enforce_part_number_list=0x4,unsupported_cable=0x5,High_Temperature=0x6,bad_cable=0x7,PMD_type_is_not_enabled=0x8,pcie_system_power_slot_Exceeded=0xc,Boot_error=0xf,Recovery_error=0x10,Submodule_failure=0x11" offset="0x4.8" size="0x0.5" />
</node>

<node name="pmpr_reg_ext" descr="" size="0x10.0" >
	<field name="module" descr="Module number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA \;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="attenuation_5g" descr="Attenuation - total channel attenuation @ 5GHz in db." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="attenuation_7g" descr="Attenuation - total channel attenuation @ 7GHz in db. \;A 0 value implies that attenuation_5g is used also for 7GHz" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="attenuation_53g" descr="Attenuation - total channel attenuation @ 53GHz in db.\;A 0 value implies that attenuation_5g is used also for 25GHz" access="RW" offset="0x8.16" size="0x0.8" />
	<field name="attenuation_12g" descr="Attenuation - total channel attenuation @ 12GHz in db.\;A 0 value implies that attenuation_5g is used also for 12GHz" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="attenuation_25g" descr="Attenuation - total channel attenuation @ 25GHz in db.\;A 0 value implies that attenuation_5g is used also for 25GHz" access="RW" offset="0xC.16" size="0x0.8" />
</node>

<node name="pmpt_reg_ext" descr="" size="0x1c.0" >
	<field name="status" descr="0 - Normal mission mode. \;1 - Module is not connected OR module doesn&apos;t support PRBS and diagnostics data\;2 - unsupported configuration setting\;3 - PRBS Generator only\;4 - PRBS Checker only \;5 - PRBS traffic both Checker and Generator\;Note: For lock status on PRBS data see PMPD.status" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="lane_mask" descr="Reserved when (le=0 or ls = 0)\;Logical lane number mask.\;For Get operation only one bit shall be set" access="INDEX" offset="0x0.4" size="0x0.8" />
	<field name="host_media" descr="Host or Media lanes\;0 - Media lanes\;1 - Host lanes" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="invt_cap" descr="PRBS inversion is supported" access="RO" offset="0x0.13" size="0x0.1" />
	<field name="swap_cap" descr="PAM4 MSB&lt;-&gt; LSB swapping is supported by the module" access="RO" offset="0x0.14" size="0x0.1" />
	<field name="module" descr="module index" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PMPT configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on lane index\;Affects lane indexing for set operations only, ignored for get operations" access="OP" offset="0x0.29" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support/capability: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS is disabled.\;1 - PRBS is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="Supported module&apos;s PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23 (x^23 + x^18 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 17 - PRBS13 (x^13 + x^12 + x^2+ x + 1)\;Bit 21 - SSPR\;Bit 22 - SSPRQ" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 7):\;0 - NRZ test pattern\;1 - PAM4 encoding" access="INDEX" offset="0x8.0" size="0x0.4" />
	<field name="ch_ge" descr="0 - Access is for both Checker and Generator (Can be used for Set operations only)\;1 - Access is for Generator\;2 - Access if for Checker\;Note: Checker and Generator must be in same rate" access="INDEX" offset="0x8.4" size="0x0.2" />
	<field name="invt_admin" descr="PRBS inversion enable bit, see ivnt_cap:\;0 - NO PRBS inversion\;1 - PRBS inversion" access="RW" offset="0x8.8" size="0x0.1" />
	<field name="swap_admin" descr="PAM4 MSB&lt;-&gt; LSB swapping enable bit, see swap_cap. \;0 - NO MSB&lt;-&gt; LSB swapping \;1 - MSB &lt;-&gt; LSB swapping" access="RW" offset="0x8.9" size="0x0.1" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23 (x^23 + x^18 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0x11 - PRBS13 (x^13 + x^12 + x^2+ x + 1)\;0x15 - SSPR\;0x16 - SSPRQ" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) \;Bit 2 - Reserved\;Bit 3- 10GE/40GE (10.3125 Gb/s) \;Bit 4- FDR (14.0625 Gb/s) \;Bit 5- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 6- Reserved \;Bit 7- HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;Bit 8- NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;Bit 9 - XDR (106.25 Gbd / 212.5Gb/s)" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - Non selected. \;1 - 1GE (1.25 Gb/s)\;2 - SDR (2.5 Gb/s) \;8 - 10GE/40GE (10.3125 Gb/s) \;16 - FDR (14.0625 Gb/s) \;32 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;128 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;256 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;512 - XDR (106.25 Gbd / 212.5Gb/s)\;" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="pmtm_reg_ext" descr="" size="0x10.0" >
	<field name="module" descr="module number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="slot_index" descr="Reserved for HCA\;Slot_index \;Slot_index = 0 represent the onboard (motherboard). \;In case of non modular system only slot_index = 0 is available." access="INDEX" offset="0x0.24" size="0x0.4" />
	<field name="module_type" descr="module_type: \;0: Backplane_with_4_lanes\;1: QSFP\;2: SFP\;3: No_Cage - [Obsolete]\;4: Backplane_with_single_lane\;8: Backplane_with_two_lanes\;10: Chip2Chip4x\;11: Chip2Chip2x \;12: Chip2Chip1x\;14: QSFP_DD \;15: OSFP\;16: SFP_DD\;17: DSFP \;18: Chip2Chip8x\;19: Twisted_Pair\;20: Backplane_with_8_lanes\;21: Loopback \;22: OE_16x \;23: OSFP_ELS\;24: QSFP_2x\;25: CPO_32x" access="RW" enum="Backplane_with_4_lanes=0x0,QSFP=0x1,SFP=0x2,No_Cage=0x3,Backplane_with_single_lane=0x4,Backplane_with_two_lanes=0x8,Chip2Chip4x=0xa,Chip2Chip2x=0xb,Chip2Chip1x=0xc,QSFP_DD=0xe,OSFP=0xf,SFP_DD=0x10,DSFP=0x11,Chip2Chip8x=0x12,Twisted_Pair=0x13,Backplane_with_8_lanes=0x14,Loopback=0x15,OE_16x=0x16,OSFP_ELS=0x17,QSFP_2x=0x18,CPO_32x=0x19" offset="0x4.0" size="0x0.5" />
	<field name="module_width" descr="Number of module&apos;s electrical lanes\;\;NOTE: For SET command, this value should match the module type width in module_type field" access="RW" offset="0x4.8" size="0x0.5" />
</node>

<node name="pmtu_reg_ext" descr="" size="0x10.0" >
	<field name="itre" descr="Ingress Truncation enable, the admin_mtu is used as truncation:\;0: disable\;1: enable\;Reserved when NICs (NICs use only &apos;0&apos;)\;Reserved when SwitchX/-2 and IB Switches (use only &apos;0&apos;)\;Reserved when i_e = 0 or 2\;Reserved when GPUNet" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="i_e" descr="Ingress/Egress:\;0: applies for both ingress and for egress, read from egress\;1: applies only for ingress\;2: applies only for egress\;Reserved when NICs (NICs use only &apos;0&apos;)\;Reserved when SwitchX/-2 and IB Switches (use only &apos;0&apos;)\;Reserved when GPUNet" access="INDEX" offset="0x0.4" size="0x0.2" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number\;Not including CPU port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="protocol" descr="[DWIP]:\;The protocol which the MTU is applied to. \;0: All protocols that are supported by the device. On get, it will return the value for IBg1\;1: IB (gen 1) \;2: NVLink\;3: IBg2\;4-15: Reserved\;Reserved when Eth switches\;Reserved when NIC\;Note: for GB100 IBg2 is not PoR, Nov 2023" access="INDEX" offset="0x0.28" size="0x0.4" />
	<field name="max_mtu" descr="Maximum MTU supported on the port (Read Only).\;MTU depends on the port type. When port type (Eth/IB/FC) is configured, the relevant MTU is reported. When the port type is not configured, the minimum between the max_mtu for the different types (Eth/IB/FC) is reported.\;Informative:- For GPUNet: IB is used for MADs, thus max MTU is 768B\;- NVLink max MTU is 320B" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="admin_mtu" descr="Administratively configured MTU on the port. Must be smaller or equal to max_mtu.\;When IB: configuration is allowed only when port state is down.\;When itre=1 then must be at least 128B and granularity is 8B" access="RW" offset="0x8.16" size="0x0.16" />
	<field name="oper_mtu" descr="Operational MTU. This is the actual MTU configured on the ports. Packets exceeding this size will be dropped.\;Note: For NICs and for IB the actual operational MTU is reported which may be smaller than admin_mtu.\;For NICs: when PCAM.max_admin_mtu capability is set then oper_mtu will be the max of all admin_mtu" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="power_profile_config_ext" descr="" size="0x10.0" >
	<field name="max_integral" descr="The max value allowed for the integral calculation" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="power_allocation" descr="Power Allocation Threshold \;Units of Watt\;Can&apos;t change profile which is currently used by FW" access="RW" offset="0x0.16" size="0x0.11" />
	<field name="v" descr="Valid bit\;0: Profile configuration isn&apos;t valid\;1: Profile configuration is valid" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="Kd_factor" descr="Kd factor used for the FW PID controller" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="Ki_factor" descr="Ki factor used for the FW PID controller" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="Kp_factor" descr="Kp factor used for the FW PID controller" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="avg_pwr_num_of_sampling" descr="Num of MPPGCR.sampling_time to be used for the window average calculation\;Valid when tcs = 0" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="pid_update_num_of_sampling" descr="Number of sampling to update PID output\;Valid when tcs = 0" access="RW" offset="0xC.0" size="0x0.8" />
	<field name="pid_update_time" descr="[DWIP]\;Update time of the PID output, units of mSec. FW will round the received value by it&apos;s measurement units.\;minimum value - 5mSec\;Valid when tcs = 1" access="RW" offset="0xC.16" size="0x0.8" />
	<field name="avg_pwr_time" descr="[DWIP]\;Time to be used for the window average calculation, units of mSec. FW will round the received value by it&apos;s measurement units.\;minimum value - 5mSec\;Valid when tcs = 1" access="RW" offset="0xC.24" size="0x0.8" />
</node>

<node name="ppad_reg_ext" descr="" size="0x10.0" >
	<field name="mac_47_32" descr="If single_base_mac = 0 - base MAC address\;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Port number\;Reserved when single_base_mac = 0" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.24" size="0x0.2" />
	<field name="single_base_mac" descr="0: base_mac - Switch global MAC address. FW will set incremental MAC per port starting from the base_mac.\;1: single_mac - mac of the local_port\;Reserved for SwitchX/-2." access="OP" offset="0x0.28" size="0x0.1" />
	<field name="mac_31_0" descr="If single_base_mac = 0 - base MAC address\;If single_base_mac = 1 - the per port MAC address" access="RW" offset="0x4.0" size="0x4.0" />
</node>

<node name="ppaos_reg_ext" descr="" size="0x10.0" >
	<field name="phy_test_mode_status" descr="Port extended down status:\;0: regular_operation - (port down/up according to PAOS) \;1: phy_test_mode\;\;phy test mode can be valid only when PAOS.admin_status=2 and PAOS.oper_status=2 (i.e port is down)." access="RO" enum="regular_operation=0x0,phy_test_mode=0x1" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="phy_test_mode_admin" descr="Port extended administrative down status:\;0: regular_operation - (port down/up according to PAOS) \;1: phy_test_mode\;\;The phy test mode (1) can be set only when PAOS.admin_status=2 (i.e port configuration is down)." access="RW" enum="regular_operation=0x0,phy_test_mode=0x1" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;The swid field is only valid when the local_port is the router port. In this case, the swid indicates which of the router ports to configure/query." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="phy_status" descr="rx phy status:\;0: rx_phy_down\;1: rx_phy_up\;2: rx_phy_down_by_command\;\;Note: The phy up indication is according to protocol (up == align_status=true)\;i.g. In PRBS test mode phy up is when PRB is lock (up== prbs lock)" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x4.4" size="0x0.4" />
	<field name="phy_status_admin" descr="rx phy port admin. Controls phy entities operational port status.\;valid for port_type &lt;&gt; &apos;0&apos;.\;to operate link status for port_type &apos;0&apos; use PAOS.admin_status.\;0: rx_phy_down\;1: rx_phy_up\;" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="dc_cpl_port" descr="When set, indicates that ports trace is DC coupled.\;Enabling test mode in case of DC coupled port is allowed only when setting dc_cpl_allow and printing warning to user as specified in the description." access="RO" offset="0x4.28" size="0x0.1" />
	<field name="dc_cpl_allow" descr="Relevant only for DC couple ports, Ignored otherwise.\;Field must be set when entering test mode, otherwise command is ignored.\;When entering test mode in DC couple system the following message must be presented to user:\;&quot;Warning: DC couple system must be powered on both sides of the physical link prior to enabling test mode. System may be harmed and product lifetime may be shortened if not ensured.&quot;" access="WO" offset="0x4.29" size="0x0.1" />
</node>

<node name="ppbmc_reg_ext" descr="" size="0x10.0" >
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;4 - USR Main\;5 - USR Tile\;Other values are reserved.\;Configuration 4,5 should use the same clock" access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="monitor_type" descr="Monitor type based on monitor_cntl setting and the operational mode of the link:\;Bit 0: Post_FEC_or_No_FEC_BER_monitoring\;Bit 1: Pre_FEC_BER_monitoring\;Bit 2: Symbol_BER_monitoring\;Bit 3: Estimated_Effective_BER_monitoring" access="RO" enum="Post_FEC_or_No_FEC_BER_monitoring=0x1,Pre_FEC_BER_monitoring=0x2,Symbol_BER_monitoring=0x4,Estimated_Effective_BER_monitoring=0x8" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_state" descr="The monitor state of the port:\;0 - No BER Monitor support\;1 - Normal\;2 - Warning\;3 - Alarm\;* The init monitor state for each port upon link up is normal" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="est_ef_ber_cap" descr="Indicates Estimated Effective BER monitoring supported" access="RO" offset="0x4.8" size="0x0.1" />
	<field name="clr_stat" descr="clear statistics from PPDR. link_down_info page of selected monitor type" access="OP" offset="0x4.9" size="0x0.1" />
	<field name="monitor_type_ext" descr="Extension for monitor type based on monitor_cntl setting and the operational mode of the link:\;Bit 0: UCR - Uncorrectable Codeword Ratio\;" access="RO" enum="UCR=0x1" offset="0x4.12" size="0x0.4" />
	<field name="monitor_cntl" descr="Bitmask - monitor options:\;When multiple_monitor_cap is set, multiple bits can be set. Else, only 1 bit can be set\;Bit 0: Raw_BER_monitor - When set, a link with FEC active will monitor Pre-FEC BER.\;Bit 1: Effective_FEC_monitor\;Bit 2: Symbol_FEC_monitor\;Bit 3: Estimated_Effective_BER_monitoring\;Bit 4: UCR - Uncorrectable Codeword Ratio" access="RW" enum="Raw_BER_monitor=0x1,Effective_FEC_monitor=0x2,Symbol_FEC_monitor=0x4,Estimated_Effective_BER_monitoring=0x8,UCR=0x10" offset="0x4.16" size="0x0.8" />
	<field name="event_ctrl" descr="Bitmask - event generation on operational state change:\;Bit 0 - Normal state\;Bit 1 - Warning state\;Bit 2 - Alarm state\;Bit 3 - Reserved\;\;Note: Normal state events can be generated only if either Alarm and/or Warning events are enabled." access="RW" offset="0x4.24" size="0x0.4" />
	<field name="multiple_monitor_cap" descr="When set, multiple monitoring groups are possible. Hence, monitor_cntl can be set with multiple bits.\;else, monitor_cntl can be set with only 1 bits" access="RO" offset="0x4.28" size="0x0.1" />
	<field name="ievent" descr="Invoke event\;0: Read only\;1: Does both reading and invoke an event of type PPBME_TRAP\;\;Note: setting this field invokes an event, regardless to e and event_ctl fields, it has no effect on the event state." access="OP" offset="0x4.29" size="0x0.1" />
	<field name="e" descr="Event generation on operational state change:\;0 - Do not generate event\;1 - Generate Event \;2 - Generate Single Event\;Not Supported for HCA." access="RW" offset="0x4.30" size="0x0.2" />
	<field name="monitor_type_cap" descr="Monitor type capability mask:\;Bit 3: Estimated_Effective_BER_monitoring\;Bit 4: UCR - Uncorrectable Codeword Ratio" access="RO" enum="Estimated_Effective_BER_monitoring=0x8,UCR=0x10" offset="0x8.16" size="0x0.8" />
</node>

<node name="ppbme_reg_ext" descr="" size="0x10.0" >
	<field name="monitor_type" descr="Monitor type based on monitor_options setting and the operational mode of the link:\;0 - Post FEC / No-FEC BER monitoring\;1 - Pre FEC BER monitoring\;2 - Symbol BER monitoring\;3 - Estimated Effective BER monitoring" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="monitor_state" descr="The monitor state of the port:\;0 - No BER Monitor on the port\;1 - Normal\;2 - Warning\;3 - Alarm" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="monitor_type_ext" descr="Extension for monitor type based on monitor_cntl setting and the operational mode of the link:\;Bit 0: UCR - Uncorrectable Codeword Ratio\;" access="RO" enum="UCR=0x1" offset="0x4.12" size="0x0.4" />
	<field name="ievent" descr="Invoke event\;0: Read only\;1: Does both reading and invoke an event of type PPBME_TRAP\;\;Note: setting this field invokes an event, regardless to e and event_ctl fields, it has no effect on the event state." access="OP" offset="0x4.29" size="0x0.1" />
</node>

<node name="ppbmp_monitor_parameters_ext" descr="" size="0x8.0" >
	<field name="warning_th_exp" descr="BER threshold for warning state, when the monitor state is normal and the monitored BER crosses above the warning_threshold, the monitor state will is set to warning\;warning_threshold = warning_th_mantissa * 10^(-warning_th_exp)\;The warning_threshold shall be within the supported range for the monitor type" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="warning_th_mantissa" descr="BER threshold for warning state, when the monitor state is normal and the monitored BER crosses above the warning_threshold, the monitor state will is set to warning\;warning_threshold = warning_th_mantissa * 10^(-warning_th_exp)\;The warning_threshold shall be within the supported range for the monitor type" access="RW" offset="0x0.8" size="0x0.4" />
	<field name="alarm_th_exp" descr="BER threshold for alarm state, when the monitored BER crosses above the alarm_threshold, the monitor state is set to alarm.\;alarm_threshold = alarm_th_mantissa * 10^(-alarm_th_exp)\;The alarm_threshold shall be within the supported range for the monitor type" access="RW" offset="0x0.16" size="0x0.8" />
	<field name="alarm_th_mantissa" descr="BER threshold for alarm state, when the monitored BER crosses above the alarm_threshold, the monitor state is set to alarm.\;alarm_threshold = alarm_th_mantissa * 10^(-alarm_th_exp)\;The alarm_threshold shall be within the supported range for the monitor type" access="RW" offset="0x0.24" size="0x0.4" />
	<field name="normal_th_exp" descr="BER threshold for normal state, when the monitored BER crosses below the normal_threshold, the monitor state is set to normal.\;normal_threshold = normal_th_mantissa * 10^(-normal_th_exp)\;The warning_threshold shall be within the supported range for the monitor type" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="normal_th_mantissa" descr="BER threshold for normal state, when the monitored BER crosses below the normal_threshold, the monitor state is set to normal.\;normal_threshold = normal_th_mantissa * 10^(-normal_th_exp)\;The warning_threshold shall be within the supported range for the monitor type" access="RW" offset="0x4.24" size="0x0.4" />
</node>

<node name="ppbmp_monitor_params_cap_ext" descr="" size="0x4.0" >
	<field name="th_cap_exp_min" descr="The minimum value that could be configured for the [*]_th_exp fields of the Monitor Parameters." access="RO" offset="0x0.0" size="0x0.8" />
	<field name="th_cap_exp_max" descr="The maximum value that could be configured for the [*]_th_exp fields of the Monitor Parameters." access="RO" offset="0x0.8" size="0x0.8" />
</node>

<node name="ppbmp_reg_ext" descr="" size="0x30.0" >
	<field name="monitor_group" descr="Monitor Parameters Group\;0x0: Raw_BER_RS\;0x1: Raw_BER_FC\;0x2: Effective_BER\;0x4: Pre_FEC_BER\;0x5: Symbol_BER\;0x6: Estimated_Effective_BER_monitoring\;0x7: UCR" access="INDEX" enum="Raw_BER_RS=0x0,Raw_BER_FC=0x1,Effective_BER=0x2,Pre_FEC_BER=0x4,Symbol_BER=0x5,Estimated_Effective_BER_monitoring=0x6,UCR=0x7" offset="0x0.0" size="0x0.4" />
	<field name="grp_prf_set" descr="When set, grp_prf field will set local_port&apos;s group.\;Else, grp_prf field will be ignore in set operation" access="WO" offset="0x0.11" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="grp_prf" descr="Group profile port is mapped to.\;when group_profile is set," access="RW" offset="0x0.24" size="0x0.3" />
	<field name="monitor_parameters_w_ignore" descr="&apos;monitor_parameters&apos; field ignore write. \;Relevant for set operation only, while this bit is set to &apos;1&apos;- \;ignore the &apos;monitor_parameters&apos; values." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="time_window_w_en" descr="&apos;time_window&apos; field write enable\;Relevant for set operation only, while this bit is set to &apos;0&apos;- \;ignore the &apos;time_window&apos; value." access="WO" offset="0x0.30" size="0x0.1" />
	<field name="clr" descr="Supported if PCAM.feature_cap_mask bit 93 is set.\;0: override_thresholds - thresholds set according to monitor_parameters values.\;1: set_fw_default_thresholds - thresholds set in monitor_parameters are ignored" access="RW" enum="override_thresholds=0x0,set_fw_default_thresholds=0x1" offset="0x0.31" size="0x0.1" />
	<field name="monitor_parameters" descr="Table 869, &quot;PPBMP - BER Monitor Parameters Layout,&quot; on page 968" subnode="ppbmp_reg_monitor_parameters_auto_ext" access="RW" condition="$(parent).monitor_group" offset="0x4.0" size="0x8.0" />
	<field name="time_window" descr="The time frame which the events are grouped. \;This is a tumbling window (not a sliding window), means that each window is uncorrelated to the adjacent windows events. \;For BER features the time window derived from \;the lowest threshold.\;Units of sampling_rate.\;Value of zero is means the BER monitor is not active or time window is unknown\;\;time window is adjustable only for Estimated Effective BER, UCR monitors type and Tx_BW_loss, otherwise ignored.\;\;Note: changing the &apos;time_window&apos; field value for one port will affect all the device ports window." access="RW" offset="0xC.0" size="0x0.24" />
	<field name="sampling_rate" descr="Time frame to measure warning threshold and error threshold. \;Units of 10mSec, range 0..1Sec. \;Value of zero is means the BER monitor is not active or sampling rate is unknown" access="RO" offset="0x10.0" size="0x0.8" />
	<field name="monitor_parameters_cap" descr="The configured Monitor Parameters shall be within the ranges defined by this field.\;The returned value is according to the monitor_group index and the device capabilities.\;See Table 873, &quot;PPBMP - Monitor Parameters Capabilities Layout,&quot; on page 970" subnode="ppbmp_monitor_params_cap_ext" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="ppbmp_reg_monitor_parameters_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x8.0" >
	<field name="ppbmp_monitor_parameters_ext" descr="" subnode="ppbmp_monitor_parameters_ext" condition="($(parent).monitor_group == Raw_BER_RS) | ($(parent).monitor_group == Raw_BER_FC) | ($(parent).monitor_group == Effective_BER) | ($(parent).monitor_group == Pre_FEC_BER) | ($(parent).monitor_group == Symbol_BER) | ($(parent).monitor_group == Estimated_Effective_BER_monitoring) | ($(parent).monitor_group == UCR)" offset="0x0.0" size="0x8.0" />
</node>

<node name="ppcnt_infiniband_general_counter_ext" descr="" size="0xf8.0" >
	<field name="rq_general_error_high" descr="The total number of packets that were dropped since it contained errors. Reasons for this include:\;1. dropped due to MPR mismatch.\;Supported only when indicated by PCAM.\;" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="rq_general_error_low" descr="The total number of packets that were dropped since it contained errors. Reasons for this include:\;1. dropped due to MPR mismatch.\;Supported only when indicated by PCAM.\;" access="RO" offset="0x14.0" size="0x4.0" />
</node>

<node name="ppcnt_infiniband_packets_counter_ext" descr="" size="0xf8.0" >
	<field name="time_since_last_clear_high" descr="The time passed since the last counters clear event in msec." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="time_since_last_clear_low" descr="The time passed since the last counters clear event in msec." access="RO" offset="0x4.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="port_unicast_xmit_pkts_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="port_unicast_rcv_pkts_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="sync_header_error_counter_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="sync_header_error_counter_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="port_local_physical_errors_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="port_local_physical_errors_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="port_malformed_packet_errors_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="port_malformed_packet_errors_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="port_buffer_overrun_errors_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="port_buffer_overrun_errors_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="port_dlid_mapping_errors_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="port_dlid_mapping_errors_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="port_vl_mapping_errors_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="port_vl_mapping_errors_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="port_looping_errors_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="port_looping_errors_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="port_inactive_discards_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="port_inactive_discards_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="port_neighbor_mtu_discards_high" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="port_neighbor_mtu_discards_low" descr="For counter description please refer to the InfiniBand  Specification" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="port_llu_rx_icrc_error_high" descr="Total number of packets received on the port with ICRC error." access="RO" offset="0x60.0" size="0x4.0" />
	<field name="port_llu_rx_icrc_error_low" descr="Total number of packets received on the port with ICRC error." access="RO" offset="0x64.0" size="0x4.0" />
	<field name="port_tx_parity_error_high" descr="Total number of packets with parity error detected on the switch." access="RO" offset="0x68.0" size="0x4.0" />
	<field name="port_tx_parity_error_low" descr="Total number of packets with parity error detected on the switch." access="RO" offset="0x6C.0" size="0x4.0" />
</node>

<node name="ppcnt_nvlink_reduction_mlid_counters_ext" descr="" size="0xa0.0" >
	<field name="mlid" descr="The MLID the counters applies to.\;Value of 0xFFFF means the counters aggregates all MLIDs." access="RO" offset="0x4.0" size="0x0.16" />
	<field name="incoming_good_mc_read_req_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read requests - packets" access="RO" offset="0x10.0" size="0x4.0" />
	<field name="incoming_good_mc_read_req_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read requests - packets" access="RO" offset="0x14.0" size="0x4.0" />
	<field name="incoming_good_mc_read_req_data_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read requests - data" access="RO" offset="0x18.0" size="0x4.0" />
	<field name="incoming_good_mc_read_req_data_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read requests - data" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="incoming_good_mc_write_req_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write requests - packets" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="incoming_good_mc_write_req_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write requests - packets" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="incoming_good_mc_write_req_data_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write requests - data" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="incoming_good_mc_write_req_data_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write requests - data" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="incoming_good_mc_read_resp_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read responses -\;packets" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="incoming_good_mc_read_resp_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read responses -\;packets" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="incoming_good_mc_read_resp_data_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read responses - data" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="incoming_good_mc_read_resp_data_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC read responses - data" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="incoming_good_mc_write_resp_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write responses -\;packets" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="incoming_good_mc_write_resp_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write responses -\;packets" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="incoming_good_mc_write_resp_data_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write responses - data" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="incoming_good_mc_write_resp_data_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count incoming good MC write responses - data" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC read responses - packets" access="RO" offset="0x50.0" size="0x4.0" />
	<field name="generated_mc_read_resp_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC read responses - packets" access="RO" offset="0x54.0" size="0x4.0" />
	<field name="generated_mc_read_resp_data_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC read responses - data" access="RO" offset="0x58.0" size="0x4.0" />
	<field name="generated_mc_read_resp_data_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC read responses - data" access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="generated_mc_write_resp_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC write responses - packets" access="RO" offset="0x60.0" size="0x4.0" />
	<field name="generated_mc_write_resp_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC write responses - packets" access="RO" offset="0x64.0" size="0x4.0" />
	<field name="generated_mc_write_resp_data_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC write responses - data" access="RO" offset="0x68.0" size="0x4.0" />
	<field name="generated_mc_write_resp_data_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count generated MC write responses - data" access="RO" offset="0x6C.0" size="0x4.0" />
	<field name="dropped_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count dropped packets. Should count only on\;configuration errors and not C&amp;D errors / LLU_RX\;errors.\;Includes penalty box errors." access="RO" offset="0x70.0" size="0x4.0" />
	<field name="dropped_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count dropped packets. Should count only on\;configuration errors and not C&amp;D errors / LLU_RX\;errors.\;Includes penalty box errors." access="RO" offset="0x74.0" size="0x4.0" />
	<field name="trapped_pkt_high" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count trapped packets" access="RO" offset="0x78.0" size="0x4.0" />
	<field name="trapped_pkt_low" descr="Per lean pipe, per MLID (and one for all MLIDs\;combined):\;count trapped packets" access="RO" offset="0x7C.0" size="0x4.0" />
	<field name="nvl_reduction_errors_high" descr="Per lean pipe, count reduction configuration error.\;This counter ignores the specified MLID value." access="RO" offset="0x80.0" size="0x4.0" />
	<field name="nvl_reduction_errors_low" descr="Per lean pipe, count reduction configuration error.\;This counter ignores the specified MLID value." access="RO" offset="0x84.0" size="0x4.0" />
	<field name="nvl_reduction_penalty_box_errors_high" descr="Per lean pipe, count reduction MLID in penalty\;box errors for both requests and responses.\;This counter ignores the specified MLID value." access="RO" offset="0x88.0" size="0x4.0" />
	<field name="nvl_reduction_penalty_box_errors_low" descr="Per lean pipe, count reduction MLID in penalty\;box errors for both requests and responses.\;This counter ignores the specified MLID value." access="RO" offset="0x8C.0" size="0x4.0" />
	<field name="port_nvr_local_alm_id_allocations_high" descr="Count number of allocated local ALM_ID.\;When RIB Mode is off, the counted values should\;match the number of reductions on the port.\;This counter ignores the specified MLID and\;LeanPipe values." access="RO" offset="0x90.0" size="0x4.0" />
	<field name="port_nvr_local_alm_id_allocations_low" descr="Count number of allocated local ALM_ID.\;When RIB Mode is off, the counted values should\;match the number of reductions on the port.\;This counter ignores the specified MLID and\;LeanPipe values." access="RO" offset="0x94.0" size="0x4.0" />
	<field name="port_nvr_global_alm_id_allocations_high" descr="Count number of allocated global ALM_ID\;from RIB. When RIB is off, count should be 0.\;This counter ignores the specified MLID and\;LeanPipe values." access="RO" offset="0x98.0" size="0x4.0" />
	<field name="port_nvr_global_alm_id_allocations_low" descr="Count number of allocated global ALM_ID\;from RIB. When RIB is off, count should be 0.\;This counter ignores the specified MLID and\;LeanPipe values." access="RO" offset="0x9C.0" size="0x4.0" />
</node>

<node name="ppcnt_plr_counters_ext" descr="" size="0xf8.0" >
	<field name="plr_rcv_codes_high" descr="Number of received PLR codewords\;\;" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="plr_rcv_codes_low" descr="Number of received PLR codewords\;\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="plr_rcv_code_err_high" descr="The total number of rejected codewords received" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="plr_rcv_code_err_low" descr="The total number of rejected codewords received" access="RO" offset="0xC.0" size="0x4.0" />
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
	<field name="plr_codes_loss_high" descr="Received bandwidth loss due to codes retransmission. calculated in resolution of \;(plr_rcv_code_err / plr_rcv_codes) * 10^10\;\;BW Loss % = (plr_codes_loss / 10^10 ) *100" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="plr_codes_loss_low" descr="Received bandwidth loss due to codes retransmission. calculated in resolution of \;(plr_rcv_code_err / plr_rcv_codes) * 10^10\;\;BW Loss % = (plr_codes_loss / 10^10 ) *100" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_within_t_sec_max_high" descr="The maximum number of retransmitted events in t sec window\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="plr_xmit_retry_events_within_t_sec_max_low" descr="The maximum number of retransmitted events in t sec window\;" access="RO" offset="0x44.0" size="0x4.0" />
</node>

<node name="ppcnt_recovery_counters_ext" descr="" size="0xf4.0" >
	<field name="total_successful_recovery_events" descr="Number of total successful recovery events of any of the recovery types during ports reset cycle (does not clear on link down)" access="RO" offset="0x0.0" size="0x4.0" />
	<field name="unintentional_link_down_events" descr="Counts Local &amp; remote unintentional drops (remote intentional are not counted)\;Updated on link drop only" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="intentional_link_down_events" descr="Counts Local &amp; remote intentional drops (remote intentional counted)\;Updated on link drop only" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="time_in_last_host_logical_recovery" descr="Time in ms of each of the recovery types from last recovery flow event." access="RO" offset="0xC.0" size="0x4.0" />
	<field name="time_in_last_host_serdes_feq_recovery" descr="Time in ms of each of the recovery types from last recovery flow event." access="RO" offset="0x10.0" size="0x4.0" />
	<field name="time_in_last_module_tx_disable_recovery" descr="Time in ms of each of the recovery types from last recovery flow event." access="RO" offset="0x14.0" size="0x4.0" />
	<field name="time_in_last_module_datapath_full_toggle_recovery" descr="Time in ms of each of the recovery types from last recovery flow event." access="RO" offset="0x18.0" size="0x4.0" />
	<field name="total_time_in_host_logical_recovery" descr="Total time in ms of each of the recovery types from all of the recovery flows that happened. Accumulative between link flaps" access="RO" offset="0x1C.0" size="0x4.0" />
	<field name="total_time_in_host_serdes_feq_recovery" descr="Total time in ms of each of the recovery types from all of the recovery flows that happened. Accumulative between link flaps" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="total_time_in_module_tx_disable_recovery" descr="Total time in ms of each of the recovery types from all of the recovery flows that happened. Accumulative between link flaps" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="total_time_in_module_datapath_full_toggle_recovery" descr="Total time in ms of each of the recovery types from all of the recovery flows that happened. Accumulative between link flaps" access="RO" offset="0x28.0" size="0x4.0" />
	<field name="total_host_logical_recovery_count" descr="Counter of the total times each recovery type flow happened. Accumulative between link flaps\;" access="RO" offset="0x2C.0" size="0x4.0" />
	<field name="total_host_serdes_feq_recovery_count" descr="Counter of the total times each recovery type flow happened. Accumulative between link flaps\;" access="RO" offset="0x30.0" size="0x4.0" />
	<field name="total_module_tx_disable_recovery_count" descr="Counter of the total times each recovery type flow happened. Accumulative between link flaps\;" access="RO" offset="0x34.0" size="0x4.0" />
	<field name="total_module_datapath_full_toggle_recovery_count" descr="Counter of the total times each recovery type flow happened. Accumulative between link flaps\;" access="RO" offset="0x38.0" size="0x4.0" />
	<field name="total_host_logical_succesful_recovery_count" descr="Counter of the total times each recovery type flow happened and succeeded to recover. Accumulative between link flaps\;" access="RO" offset="0x3C.0" size="0x4.0" />
	<field name="total_host_serdes_feq_succesful_recovery_count" descr="Counter of the total times each recovery type flow happened and succeeded to recover. Accumulative between link flaps\;" access="RO" offset="0x40.0" size="0x4.0" />
	<field name="total_module_tx_disable_succesful_recovery_count" descr="Counter of the total times each recovery type flow happened and succeeded to recover. Accumulative between link flaps\;" access="RO" offset="0x44.0" size="0x4.0" />
	<field name="total_module_datapath_full_toggle_succesful_recovery_count" descr="Counter of the total times each recovery type flow happened and succeeded to recover. Accumulative between link flaps\;" access="RO" offset="0x48.0" size="0x4.0" />
	<field name="time_since_last_recovery" descr="Time since last successful recovery\;1 sec granularity.\;valid only if total_successful_recoveries OR successful_recovery_event &gt;= 1" access="RO" offset="0x4C.0" size="0x4.0" />
	<field name="last_host_logical_recovery_attempts_count" descr="number of lock attempts counts. lock attempt is defined as 500uS cycle lock attempt to linkup   " access="RO" offset="0x50.0" size="0x4.0" />
	<field name="last_host_serdes_feq_attempts_count" descr="number PHY algorithm cycles counts." access="RO" offset="0x54.0" size="0x4.0" />
	<field name="time_between_last_2_recoveries" descr="time in msec between 2 last consecutive recoveries (success or fail) from exit of first to entry of second. When value ss in 0xFFFF, time is more than 1min    \;\;valid only if (total_successful_recoveries OR successful_recovery_event) + link_down_counter &gt;= 2" access="RO" offset="0x58.0" size="0x0.16" />
	<field name="last_rs_fec_uncorrectable_during_recovery_high" descr="Number of uncorrectable RS-FEC blocks received on port, during the last recovery flow event." access="RO" offset="0x5C.0" size="0x4.0" />
	<field name="last_rs_fec_uncorrectable_during_recovery_low" descr="Number of uncorrectable RS-FEC blocks received on port, during the last recovery flow event." access="RO" offset="0x60.0" size="0x4.0" />
</node>

<node name="ppcnt_reg_counter_set_auto_ext" descr="" attr_is_union="1" size="0xf8.0" >
	<field name="IB_long_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_long_portcntrs_attribute_grp_data_ext" offset="0x0.0" selected_by="InfiniBand_Extended_Port_Counters" size="0xf8.0" />
	<field name="IB_portcntrs_attribute_grp_data_ext" descr="" subnode="IB_portcntrs_attribute_grp_data_ext" offset="0x0.0" selected_by="InfiniBand_Port_Counters" size="0xf8.0" />
	<field name="eth_2819_cntrs_grp_data_layout_ext" descr="" subnode="eth_2819_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_2819_Counters" size="0xf8.0" />
	<field name="eth_2863_cntrs_grp_data_layout_ext" descr="" subnode="eth_2863_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_2863_Counters" size="0xf8.0" />
	<field name="eth_3635_cntrs_grp_data_layout_ext" descr="" subnode="eth_3635_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="RFC_3635_Counters" size="0xf8.0" />
	<field name="eth_802_3_cntrs_grp_data_layout_ext" descr="" subnode="eth_802_3_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="IEEE_802_3_Counters" size="0xf8.0" />
	<field name="eth_discard_cntrs_grp_ext" descr="" subnode="eth_discard_cntrs_grp_ext" offset="0x0.0" selected_by="Ethernet_Discard_Counters" size="0xf8.0" />
	<field name="eth_extended_cntrs_grp_data_layout_ext" descr="" subnode="eth_extended_cntrs_grp_data_layout_ext" offset="0x0.0" selected_by="Ethernet_Extended_Counters" size="0xf8.0" />
	<field name="eth_per_prio_grp_data_layout_ext" descr="" subnode="eth_per_prio_grp_data_layout_ext" offset="0x0.0" selected_by="Per_Priority_Counters" size="0xf8.0" />
	<field name="eth_per_traffic_class_cong_layout_ext" descr="" subnode="eth_per_traffic_class_cong_layout_ext" offset="0x0.0" selected_by="Per_Traffic_Class_Congestion_Counters" size="0xf8.0" />
	<field name="eth_per_traffic_class_layout_ext" descr="" subnode="eth_per_traffic_class_layout_ext" offset="0x0.0" selected_by="Per_Traffic_Class_Counters" size="0xf8.0" />
	<field name="phys_layer_cntrs_ext" descr="" subnode="phys_layer_cntrs_ext" offset="0x0.0" selected_by="Physical_Layer_Counters" size="0xf8.0" />
	<field name="phys_layer_stat_cntrs_ext" descr="" subnode="phys_layer_stat_cntrs_ext" offset="0x0.0" selected_by="Physical_Layer_Statistical_Counters" size="0xf8.0" />
	<field name="ppcnt_infiniband_general_counter_ext" descr="" subnode="ppcnt_infiniband_general_counter_ext" offset="0x0.0" selected_by="InfiniBand_General_Counters" size="0xf8.0" />
	<field name="ppcnt_infiniband_packets_counter_ext" descr="" subnode="ppcnt_infiniband_packets_counter_ext" offset="0x0.0" selected_by="InfiniBand_pkts_counters" size="0xf8.0" />
	<field name="ppcnt_nvlink_reduction_mlid_counters_ext" descr="" subnode="ppcnt_nvlink_reduction_mlid_counters_ext" offset="0x0.0" selected_by="NVLink_Reduction_Counters" size="0xa0.0" />
	<field name="ppcnt_plr_counters_ext" descr="" subnode="ppcnt_plr_counters_ext" offset="0x0.0" selected_by="PLR_counters_group" size="0xf8.0" />
	<field name="ppcnt_recovery_counters_ext" descr="" subnode="ppcnt_recovery_counters_ext" offset="0x0.0" selected_by="physical_layer_recovery_counters" size="0xf4.0" />
	<field name="ppcnt_rs_fec_histograms_counters_ext" descr="" subnode="ppcnt_rs_fec_histograms_counters_ext" offset="0x0.0" selected_by="RS_FEC_Histogram_group" size="0xf8.0" />
</node>

<node name="ppcnt_reg_ext" descr="" size="0x100.0" >
	<field name="grp" descr="Performance counter group.\;Group 63 indicates all groups (include all per priority/TC/Receive Buffer counters). Only valid on Set() operation with clr bit set.\;0x0: IEEE_802_3_Counters\;0x1: RFC_2863_Counters\;0x2: RFC_2819_Counters\;0x3: RFC_3635_Counters\;0x5: Ethernet_Extended_Counters\;0x6: Ethernet_Discard_Counters \;0x10: Per_Priority_Counters - \;0x11: Per_Traffic_Class_Counters - \;0x12: Physical_Layer_Counters\;0x13: Per_Traffic_Class_Congestion_Counters\;0x16: Physical_Layer_Statistical_Counters\;0x1A: physical_layer_recovery_counters\;0x20: InfiniBand_Port_Counters\;0x21: InfiniBand_Extended_Port_Counters\;0x22: PLR_counters_group\;0x23: RS_FEC_Histogram_group\;0x25: InfiniBand_pkts_counters\;0x26: InfiniBand_General_Counters\;0x27: L1_General_Counters\;0x2C: NVLink_Reduction_Counters" access="INDEX" enum="IEEE_802_3_Counters=0x0,RFC_2863_Counters=0x1,RFC_2819_Counters=0x2,RFC_3635_Counters=0x3,Ethernet_Extended_Counters=0x5,Ethernet_Discard_Counters=0x6,Per_Priority_Counters=0x10,Per_Traffic_Class_Counters=0x11,Physical_Layer_Counters=0x12,Per_Traffic_Class_Congestion_Counters=0x13,Physical_Layer_Statistical_Counters=0x16,physical_layer_recovery_counters=0x1a,InfiniBand_Port_Counters=0x20,InfiniBand_Extended_Port_Counters=0x21,PLR_counters_group=0x22,RS_FEC_Histogram_group=0x23,InfiniBand_pkts_counters=0x25,InfiniBand_General_Counters=0x26,NVLink_Reduction_Counters=0x2c" offset="0x0.0" size="0x0.6" />
	<field name="port_type" descr="Supported only when indicated by PCAM on FPGA based NICs:\;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;1: IB_port_number\;2: host_port_number\;Note - pnat=2 is supported for &quot;Per Traffic Class Congestion Counters&quot; and &quot;Per Traffic Class Counters&quot; groups." access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,host_port_number=0x2" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number. \;Note:\;when lp_gl = 0, 255 indicates all ports on the device, and is only allowed for Set() operation.\;when lp_gl = 1, the index is a local port number\;Note: for HCA this bit is not supported, ignored by device" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must be always 0.\;Switch partition ID to associate port with.\;Switch partitions are numbered from 0 to 7 inclusively.\;Switch partition 254 indicates stacking ports.\;Switch partition 255 indicates all switch partitions.\;Only valid on Set() operation with local_port=255." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="prio_tc" descr="Priority index for per priority counter sets, valid values: 0-7\;For Spectrum-2 and on at tx side range can be 0..cap_max_tclass_data-1, cap_control_tclass, see QGCR.tx_cnt_tclass.\; \;Traffic class index for per traffic class counter set, valid values:\;For Switches, valid values: 0 .. cap_max_tclass_data-1\; \;For HCA, valid values: 0.. HCA_CAP.max_tc\;\;Otherwise must be 0.\;\;For &quot;NVLink Reduction Counters&quot; group index of MLID and lean pipe." access="INDEX" offset="0x4.0" size="0x0.5" />
	<field name="grp_profile" descr="Supported only when indicated by PCAM: PPCNT_grp_profile_supported (bit 73).\;The group profile index. Relevant only if the clr bit is set.\;0: Will reset the counter value for all counters in the counter group.\;Else: Will point to the corresponding bit-map profile in the PPCGP register. The bit map will return the specific counters that will be reset in the group.\;\;NOTE: The grp_profile index is not supported for the following counters groups:\;1. 0x12: Physical_Layer_Counters\;2. 0x16: Physical_Layer_Statistical_Counters\;3. 0x22: PLR_counters_group\;" access="INDEX" offset="0x4.5" size="0x0.3" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x4.8" size="0x0.4" />
	<field name="counters_cap" descr="counters_cap is supported if PCAM.feature_cap_mask bit 85 is set.\;When set, each counter in the group will show in bit 0 if the counter is supported.\;&apos;0&apos; - not supported\;&apos;1&apos; - supported\;Note: To know which PPCNT groups are supported per device, listed in table TBD or PCAM fields with PPCNT can be queried." access="OP" offset="0x4.29" size="0x0.1" />
	<field name="lp_gl" descr="Local Port global variable\;0: local_port port 255 = all ports of the device.\;1: local_port index indicates Local port number.\;for HCA this bit is not supported, ignored by device" access="INDEX" offset="0x4.30" size="0x0.1" />
	<field name="clr" descr="Clear counters. Setting the clr bit will reset the counter value for all counters in the counter group. This bit can be set for both Set() and Get() operation.\;\;NOTE: Clearing a certain group&apos;s counters can influence another group&apos;s counters value." access="OP" offset="0x4.31" size="0x0.1" />
	<field name="counter_set" descr="Counter set as described in\;Table  499, &quot;Ethernet IEEE 802.3 Counters Group Data Layout,&quot; on page  498\;Table  501, &quot;Ethernet RFC 2863 Counter Group Data Layout,&quot; on page  502\;Table  503, &quot;Ethernet RFC 2819 Counter Group Data Layout,&quot; on page  505\;Table  505, &quot;Ethernet RFC 3635 Counter Group Data Layout,&quot; on page  510\;Table  507, &quot;Ethernet Extended Counter Group Data Layout,&quot; on page  514\;Table  510, &quot;Ethernet Discard Counter Group Fields,&quot; on page  519\;Table  511, &quot;Ethernet Per Priority Group Data Layout,&quot; on page  521\;Table  515, &quot;Ethernet Per Traffic Class Group data layout,&quot; on page  529\;Table  527, &quot;Physical Layer Counters Data Layout,&quot; on page  540\;Table  517, &quot;Ethernet Per Traffic Class Congestion Group data layout,&quot; on page  530\;Table  531, &quot;Physical Layer Statistical Counters Data Layout,&quot; on page  549\;Table  523, &quot;InfiniBand PortCounters Attribute Group Data Layout,&quot; on page  534\;Table  525, &quot;InfiniBand Extended PortCounters Attribute Group Data Layout,&quot; on page  536\;Table  533, &quot;PLR Counters Data Layout,&quot; on page  555 \;Table  535, &quot;RS-Histograms Data Layout,&quot; on page  557\;Table  539, &quot;InfiniBand Packets Counters Data Layout,&quot; on page  559\;Table  541, &quot;InfiniBand General Counters Data Layout,&quot; on page  562\;Table  559, &quot;Physical Layer Recovery Counters Group Data Layout,&quot; on page  594\;Table  561, &quot;NVLink Reduction Counters Group Layout,&quot; on page  597" subnode="ppcnt_reg_counter_set_auto_ext" access="RO" offset="0x8.0" size="0xf8.0" union_selector="$(parent).grp" />
</node>

<node name="ppcnt_rs_fec_histograms_counters_ext" descr="" size="0xf8.0" >
	<field name="hist" descr="Value of RS-hist\;In order to know bin errors distribution use PPHCR reg." subnode="uint64" access="RO" high_bound="20" low_bound="0" offset="0x0.0" size="0xa8.0" />
</node>

<node name="ppdfd_ext" descr="" size="0xc.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ntimes" descr="Number of times to transmit the error\;Note that by HW the event is triggered 1 time. So FW will trigger the event again and again as fast as possible (roughly every 1uSec).\;On a read access, the FW should return ntimes originally configured." access="RW" offset="0x4.0" size="0x0.16" />
	<field name="poison_en" descr="Poison will set a Phy EBP signal (different type than stomp). \;Reserved when stomp_en = 1.\;On a read access, FW should return poison_en originally configured." access="RW" offset="0x8.0" size="0x0.1" />
	<field name="stomp_en" descr="Stomp will set a Phy EBP signal.\;On a read access, FW should return stomp_en originally configured." access="RW" offset="0x8.1" size="0x0.1" />
</node>

<node name="pphcr_bin_range_ext" descr="" size="0x4.0" >
	<field name="low_val" descr="Low range of bin&apos;s measurement" access="RW" offset="0x0.0" size="0x0.6" />
	<field name="high_val" descr="High range of bin&apos;s measurement" access="RW" offset="0x0.16" size="0x0.6" />
</node>

<node name="pphcr_ext" descr="" size="0x5c.0" >
	<field name="we" descr="Support of histogram bins configuration. \;In case this bit is cleared, the port doesn&apos;t support configuration of the histogram bins, for the specific hist_type." access="RO" offset="0x0.0" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="port_type" descr="0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type:\;0: Local_port_number\;1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port or DataPath number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="active_hist_type" descr="0 - Invalid (Link down / unsupported) \;1 - KP4 RS-FEC (544,514) errors \;2 - LL RS-FEC (271,257) / (272,257+1) errors\;3 - KR4 RS-FEC (528,514) errors\;4 - PRBS errors" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="hist_type" descr="0: According to active link" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="num_of_bins" descr="Available number of bins \;" access="RO" offset="0x4.16" size="0x0.8" />
	<field name="hist_min_measurement" descr="Lowest measurement/low limit of the histogram \;Example:\;In case of hist_type = 1, represent KP4 RS FEC symbol errors(= 0)\;In case of hist_type = 2, represent LL RS FEC symbol errors ( = 0)\;" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="hist_max_measurement" descr="Highest measurement/high limit of the histogram:\;Example:\;In case of hist_type = 1, represent KP4 RS FEC symbol errors ( = 15)\;In case of hist_type = 2, represent LL RS FEC symbol errors ( = 7)" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="bin_range_write_mask" descr="Valid only if we (write enable) = 1 \;Ignored on GET \;Write mask for the bin_range array. \;If bit X is set, bin_range [X] write should be execute\;Else if bit X is clear, ignored value in written to bin_range [X]" access="WO" offset="0xC.0" size="0x0.16" />
	<field name="bin_range" descr="Write to bin_range[x] is applicable only if we = 1 &amp; the corresponding bits in bin_range_write_mask is set.\;Mapping of measurement units to a bin.\;See Table  847, &quot;PPHCR - Port Phy Bin Range Histogram Configuration Layout,&quot; on page  943" subnode="pphcr_bin_range_ext" access="RW" high_bound="18" low_bound="0" offset="0x10.0" size="0x4c.0" />
</node>

<node name="pplm_reg_ext" descr="" size="0x74.0" >
	<field name="test_mode" descr="0: Mission_mode_configuration_and_capabilities\;1: Test_mode_configuration_and_capabilities" access="INDEX" enum="Mission_mode_configuration_and_capabilities=0x0,Test_mode_configuration_and_capabilities=0x1" offset="0x0.1" size="0x0.1" />
	<field name="plr_vld" descr="When set, PLR set configurations are valid, otherwise ignored.\;relevant fields for PLR configurations are: plr_margin_th, tx_crc_plr, plr_reject_mode\;Feature is supported when PCAM bit 95 is set" access="WO" offset="0x0.2" size="0x0.1" />
	<field name="tx_crc_plr_vld" descr="Valid only when plr_vld is set. When set, PLR configuration for tx_crc_plr is used , otherwise ignored." access="WO" offset="0x0.3" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_Port\;1: Near_End_Port - For Gearbox - Host side\;2: Internal_IC_Port \;3: Far_End_Port - For Gearbox - Line side\;\;Other values are reserved.\;\;Using port_type &apos;0&apos; will override all different parts of the link structure.\;Using port_type &apos;1&apos; will configure also port_type &apos;2&apos; accordingly and vise versa." access="INDEX" enum="Network_Port=0x0,Near_End_Port=0x1,Internal_IC_Port=0x2,Far_End_Port=0x3" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0: Local_port_number\;1: IB_port_number" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="plr_reject_mode_vld" descr="Valid only when plr_vld is set. When set, PLR configuration for plr_reject_mode is used, otherwise ignored." access="WO" offset="0x0.24" size="0x0.1" />
	<field name="plr_margin_th_override_to_default" descr="Valid only if plr_vld is not set. When set, force default value into the plr_margin_th" access="WO" offset="0x0.25" size="0x0.1" />
	<field name="tx_crc_plr_override_to_default" descr="Valid only if plr_vld is not set. When set, force default value into the tx_crc_plr" access="WO" offset="0x0.26" size="0x0.1" />
	<field name="plr_reject_mode_override_to_default" descr="Valid only if plr_vld is not set. When set, force default value into the plr_reject_mode" access="WO" offset="0x0.27" size="0x0.1" />
	<field name="plt_margin_th_support" descr="Supported PLR margin thresholds capability bitmask:\;Bit 0: PLR margin threshold 0 supported\;Bit 1: PLR margin threshold 1 supported\;Bit 2: PLR margin threshold 2 supported\;Bit 3: PLR margin threshold 3 supported\;Bit 4: PLR margin threshold 4 supported\;Bit 5: PLR margin threshold 5 supported\;Bit 6: PLR margin threshold 6 supported\;Bit 7: PLR margin threshold 7 supported\;" access="RO" offset="0x4.9" size="0x0.8" />
	<field name="tx_crc_plr_support" descr="Supported tx CRC over PLR capability\;0: not supported\;1: supported" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="plr_reject_mode_support" descr="Supported PLR reject modes capability bitmask:\;Bit 0: rejection_based_on_plr_margin\;Bit 1: rejection_based_on_crc_and_cs\;Bit 2: rejection_based_on_CS\;Bit 3: reserved" access="RO" offset="0x4.19" size="0x0.4" />
	<field name="plr_reject_mode_oper" descr="This is the operational value:\;0: rejection_based_on_plr_margin\;1: rejection_based_on_crc_and_cs\;2: rejection_based_on_CS\;3: reserved" access="RO" offset="0x4.25" size="0x0.2" />
	<field name="tx_crc_plr_oper" descr="This is the operational value. When set tx CRC over PLR is enabled" access="RO" offset="0x4.27" size="0x0.1" />
	<field name="plr_margin_th_oper" descr="This is the operational value.\;PLR margin threshold in which a codeword is retransmitted" access="RO" offset="0x4.28" size="0x0.4" />
	<field name="fec_mode_active" descr="Active FEC (bitmask)\;For each enum, a short prefix for tools is presented in the row below.\;0: No_FEC \;1: Firecode_FEC\;FC_FEC\;2: Standard_RS_FEC - RS(528,514)\;KR4_FEC\;3: Standard_LL_RS_FEC - RS(271,257)\;LL_FEC\;4: Interleaved_Quad_RS_FEC - (544,514)  \;Quad_KP4_FEC\;5: Interleaved_Quad_RS_FEC_PLR - (546,516) \;Quad_KP4_FEC\;6: Interleaved_Standard_RS-FEC - (544,514)\;Int_KP4_FEC\;7: Standard_RS-FEC - (544,514)\;KP4_FEC\;8: Interleaved_Octet_RS_FEC_PLR - (546,516) \;Octet_KP4_FEC\;9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;ELL_FEC\;10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC - (272,257+1)\;Int_ELL_FEC\;11: Interleaved_Standard_RS_FEC_PLR - (544,514) \;Int_KP4_FEC_PLR\;12: RS-FEC - (544,514) + PLR\;Int_KP4_FEC_PLR\;13: LL-FEC - (271,257) + PLR\;Int_KP4_FEC_PLR\;14: Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal] \;ELL_FEC_PLR\;15: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR - (272,257+1) [Internal]\;Int_ELL_FEC_PLR" access="RO" enum="No_FEC=0x0,Firecode_FEC=0x1,Standard_RS_FEC=0x2,Standard_LL_RS_FEC=0x3,Interleaved_Quad_RS_FEC=0x4,Interleaved_Quad_RS_FEC_PLR=0x5,Interleaved_Standard_RS=0x6,Standard_RS=0x7,Interleaved_Octet_RS_FEC_PLR=0x8,Ethernet_Consortium_LL_50G_RS_FEC=0x9,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC=0xa,Interleaved_Standard_RS_FEC_PLR=0xb,RS=0xc,LL=0xd,Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xe,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_PLR=0xf" offset="0xC.0" size="0x0.24" />
	<field name="plr_reject_mode" descr="This is the admin value:\;0: rejection_based_on_plr_margin\;1: rejection_based_on_crc_and_cs\;2: rejection_based_on_CS\;3: reserved\;set value is used only if both plr_vld and plr_reject_mode_vld are set, else configure to default value" access="RW" offset="0xC.24" size="0x0.2" />
	<field name="tx_crc_plr" descr="This is the admin value. When set tx CRC over PLR is enabled\;set value is used only if both plr_vld and tx_crc_plr_vld are set, else configure to default value" access="RW" offset="0xC.27" size="0x0.1" />
	<field name="plr_margin_th" descr="This is the admin value.\;PLR margin threshold in which a codeword is retransmitted\;set value is used only if plr_vld is set to high, else configure to default value\;" access="RW" offset="0xC.28" size="0x0.4" />
	<field name="fec_override_cap_10g_40g" descr="10GE/40GE Ethernet FEC override capability bitmask:\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: Reserved2\;Bit 3: Reserved3\;\;" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,Reserved2=0x4,Reserved3=0x8" offset="0x10.0" size="0x0.4" />
	<field name="fec_override_cap_25g" descr="25GE Ethernet FEC override capability bitmask:\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: RS_FEC\;Bit 3: Reserved" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4,Reserved=0x8" offset="0x10.4" size="0x0.4" />
	<field name="fec_override_cap_50g" descr="50GE (2 lanes) Ethernet FEC override capability bitmask:\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: RS_FEC\;Bit 3: Reserved" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4,Reserved=0x8" offset="0x10.8" size="0x0.4" />
	<field name="fec_override_cap_100g" descr="100GE (4 lanes) Ethernet FEC override capability bitmask:\;Bit 0: No_FEC\;Bit 1: Reserved1\;Bit 2: RS_FEC - (528,514)\;Bit 3: Reserved3" access="RO" enum="No_FEC=0x1,Reserved1=0x2,RS_FEC=0x4,Reserved3=0x8" offset="0x10.12" size="0x0.4" />
	<field name="fec_override_cap_56g" descr="56GE Ethernet FEC override capability bitmask:\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: Reserved2\;Bit 3: Reserved3" access="RO" enum="No_FEC=0x1,Firecode_FEC=0x2,Reserved2=0x4,Reserved3=0x8" offset="0x10.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_cap" descr="RS-FEC correction bypass override capability:\;0: NO_correction_bypass\;1: RS_FEC_correction_bypass" access="RO" enum="NO_correction_bypass=0x0,RS_FEC_correction_bypass=0x1" offset="0x10.28" size="0x0.4" />
	<field name="fec_override_admin_10g_40g" descr="10GE/40GE Ethernet FEC override admin, see 10g_40g_fec_override_cap.\;(one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;\;" access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.0" size="0x0.4" />
	<field name="fec_override_admin_25g" descr="25GE Ethernet FEC override admin, see 25g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: RS_FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_admin must be set with the same value." access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4" offset="0x14.4" size="0x0.4" />
	<field name="fec_override_admin_50g" descr="50GE Ethernet FEC override admin, see 50g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC\;Bit 2: RS_FEC\;\;Note - 25g_fec_override_admin and 50g_fec_override_admin must be set with the same value." access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2,RS_FEC=0x4" offset="0x14.8" size="0x0.4" />
	<field name="fec_override_admin_100g" descr="100GE Ethernet FEC override admin, see 100g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 2: RS_FEC" access="RW" enum="No_FEC=0x1,RS_FEC=0x4" offset="0x14.12" size="0x0.4" />
	<field name="fec_override_admin_56g" descr="56GE Ethernet FEC override admin, see 56g_fec_override_cap. (one-hot setting): \;0: auto_mode - no override\;Bit 0: No_FEC\;Bit 1: Firecode_FEC" access="RW" enum="No_FEC=0x1,Firecode_FEC=0x2" offset="0x14.16" size="0x0.4" />
	<field name="rs_fec_correction_bypass_admin" descr="RS-FEC correction bypass override admin: (one-hot setting): \;0: auto_mode - no override \;1: NO_correction_bypass\;2: RS_FEC_correction_bypass" access="RW" enum="auto_mode=0x0,NO_correction_bypass=0x1,RS_FEC_correction_bypass=0x2" offset="0x14.28" size="0x0.4" />
	<field name="fec_override_cap_200g_4x" descr="200GE FEC override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;Others bits reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x18.0" size="0x0.16" />
	<field name="fec_override_cap_400g_8x" descr="400GE FEC override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x18.16" size="0x0.16" />
	<field name="fec_override_cap_50g_1x" descr="50GE single lane override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x1C.0" size="0x0.16" />
	<field name="fec_override_cap_100g_2x" descr="100GE over 2 lanes, FEC override capability bitmask:\;Bit 8: Zero_Latency_FEC\;Bit 9: Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1\;All others are reserved" access="RO" enum="Fifty50G_Ethernet_Consortium_LL_RS_FEC_272_257plus1=0x200" offset="0x1C.16" size="0x0.16" />
	<field name="fec_override_admin_200g_4x" descr="200GE FEC override admin bitmask (one-hot setting) \;0: Auto_mode\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x20.0" size="0x0.16" />
	<field name="fec_override_admin_400g_8x" descr="400GE FEC override admin bitmask (one-hot setting): \;0: Auto_mode\;Bit7: RS_FEC_544_514\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x20.16" size="0x0.16" />
	<field name="fec_override_admin_50g_1x" descr="50GE, 1lanes FEC override admin bitmask (one-hot setting)\;0: Auto_mode\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x24.0" size="0x0.16" />
	<field name="fec_override_admin_100g_2x" descr="100GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: RS_FEC_272_257_plus_1 - (272,257+1)" access="RW" enum="RS_FEC_544_514=0x80,RS_FEC_272_257_plus_1=0x200" offset="0x24.16" size="0x0.16" />
	<field name="fec_override_cap_400g_4x" descr="400GE, 4 lanes FEC override capability bitmask:\;Bit 7: RS_FEC_544_514 - (544,514)\;Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1 - (272,257+1)\;Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x200" offset="0x28.0" size="0x0.16" />
	<field name="fec_override_cap_800g_8x" descr="800GE, 8 lanes FEC override capability bitmask:\;Bit 7: RS_FEC_544_514 - RS-FEC (544,514)\;Bit 8: Reserved\;Bit 9: Ethernet_Consortium_LL_50G_RS_FEC- (272,257+1)\;Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Reserved=0x100,Ethernet_Consortium_LL_50G_RS_FEC=0x200" offset="0x28.16" size="0x0.16" />
	<field name="fec_override_cap_100g_1x" descr="100GE, 1 lane FEC override capability bitmask:\;Bit 6: Interleaved_RS_FEC_544_514\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1\;Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1\;Other bits reserved" access="RO" enum="Interleaved_RS_FEC_544_514=0x40,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1=0x200,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x400" offset="0x2C.0" size="0x0.16" />
	<field name="fec_override_cap_200g_2x" descr="200GE, 2 lanes FEC override capability bitmask:\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1\;Other bits Reserved" access="RO" enum="RS_FEC_544_514=0x80,Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x200" offset="0x2C.16" size="0x0.16" />
	<field name="fec_override_admin_400g_4x" descr="400GE, 4 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1=0x200" offset="0x44.0" size="0x0.16" />
	<field name="fec_override_admin_800g_8x" descr="800GE, 8 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257plus_1=0x200" offset="0x44.16" size="0x0.16" />
	<field name="fec_override_admin_100g_1x" descr="100GE, 1 lane FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 6: Interleaved_RS_FEC_544_514\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1\;Bit 10: Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,Interleaved_RS_FEC_544_514=0x40,RS_FEC_544_514=0x80,Ethernet_Consortium_50G_Low_Latency_RS_FEC_272_257_plus_1=0x200,Interleaved_Ethernet_Consortium_LL_50G_RS_FEC_272_257_plus_1=0x400" offset="0x48.0" size="0x0.16" />
	<field name="fec_override_admin_200g_2x" descr="200GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 7: RS_FEC_544_514\;Bit 9: Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514=0x80,Ethernet_Consortium_Low_Latency_RS_FEC_272_257_plus_1=0x200" offset="0x48.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_307p5g_2x_bidi" descr="307p5G 2x bidi - NVL6 override admin bitmask (one-hot setting):\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x50.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_307p5g_2x_bidi" descr="307p5G 2x bidi - NVL6 override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x50.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_337p5g_2x_bidi" descr="337.5G 2x bidi - NVL6 override admin bitmask (one-hot setting):\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x54.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_337p5g_2x_bidi" descr="337.5G 2x bidi - NVL6 override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x54.16" size="0x0.16" />
	<field name="fec_override_cap_800g_4x" descr="800GE, 4 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x58.0" size="0x0.16" />
	<field name="fec_override_cap_1600g_8x" descr="1600GE, 8 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x58.16" size="0x0.16" />
	<field name="fec_override_cap_200g_1x" descr="200GE, 1 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x5C.0" size="0x0.16" />
	<field name="fec_override_cap_400g_2x" descr="400GE, 2 lane FEC override capability bitmask:\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine" access="RO" enum="RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x5C.16" size="0x0.16" />
	<field name="fec_override_admin_800g_4x" descr="800GE, 4 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x60.0" size="0x0.16" />
	<field name="fec_override_admin_1600g_8x" descr="1600GE, 8 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x60.16" size="0x0.16" />
	<field name="fec_override_admin_200g_1x" descr="200GE, 1 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x64.0" size="0x0.16" />
	<field name="fec_override_admin_400g_2x" descr="400GE, 2 lanes FEC override admin bitmask (one-hot setting):\;0: Auto_mode\;Bit 4: RS_FEC_544_514_Quad_FEC_Engine\;Other bits Reserved" access="RW" enum="Auto_mode=0x0,RS_FEC_544_514_Quad_FEC_Engine=0x10" offset="0x64.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_375g_2x_bidi" descr="375G 2x bidi - NVL6 override admin bitmask (one-hot setting):\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x68.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_375g_2x_bidi" descr="375G 2x bidi - NVL6 override capability bitmask:\;Bit 5: RS_FEC_546_516_plus_PLR_Quad_FEC_Engine\;Bit 8: RS_FEC_546_516_plus_PLR_Octet_FEC_Engine\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Quad_FEC_Engine=0x20,RS_FEC_546_516_plus_PLR_Octet_FEC_Engine=0x100,RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x68.16" size="0x0.16" />
	<field name="nvlink_fec_override_admin_1x_xdr_simplex" descr="XDR 1x simplex - NVL6 override admin bitmask (one-hot setting):\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RW" enum="RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x6C.0" size="0x0.16" />
	<field name="nvlink_fec_override_cap_1x_xdr_simplex" descr="XDR 1x simplex - NVL6 override capability bitmask:\;Bit 11: RS_FEC_546_516_plus_PLR_Double_FEC_Engine\;All others Reserved" access="RO" enum="RS_FEC_546_516_plus_PLR_Double_FEC_Engine=0x800" offset="0x6C.16" size="0x0.16" />
</node>

<node name="pplr_reg_ext" descr="" size="0x8.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.0" size="0x0.4" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: Near_End_Port- (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: Far_End_Port - (For Retimer/Gearbox - Line side)\;Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near_End_Port=0x1,Internal_IC_LR_Port=0x2,Far_End_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="op_mod" descr="operational mode for link configurations for phy_ local_loopback mode.\;0 - link will operate in optimal latency performance mode\;1 - link will operate in same configurations as operational port.\;\;Note: for FEC override via PPLM register, chosen FEC will be according to the PPLM configuration that was set and this bit will be ignored for FEC purposes" access="OP" offset="0x0.8" size="0x0.1" />
	<field name="apply_im" descr="Apply immediate: When set, the enabled/disabled loopback will be set immediately even if link is active.\;Note: Currently supported only for Bit 7: LL_local_loopback. in other loopbacks will be ignored" access="OP" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lb_en" descr="Loopback enable - only one bit shall be set.\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback\;Bit 2: External_local_loopback\;Bit 7: LL_local_loopback\;\;" access="RW" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.0" size="0x0.12" />
	<field name="lb_cap" descr="Loopback capability - bitmask\;Bit 0: Phy_remote_loopback\;Bit 1: Phy_local_loopback - When set the port&apos;s egress traffic is looped back to the receiver and the port transmitter is disabled.\;Bit 2: External_local_loopback - Enables the port&apos;s transmitter to link with the port&apos;s receiver using an external loopback connector.\;Bit 4: Near_end_digital_loopback - [Internal]\;Bit 7: LL_local_loopback - When set the port&apos;s egress Link layer traffic is looped back to the receiver. Physical port in this loopback mode is down.\;\;Notes \;1. Phy remote loopback can be supported only for lane rate higher than 25Gbuad in the 16nm devices.\;\;" access="RO" enum="Phy_remote_loopback=0x1,Phy_local_loopback=0x2,External_local_loopback=0x4,LL_local_loopback=0x80" offset="0x4.16" size="0x0.12" />
	<field name="lb_cap_mode_idx" descr="Supported only when indicated by PCAM Bit 97:PPLR.lb_cap_mode_idx. The returned value of the &apos;lp_cap&apos; capability field will be according to the selected mode index:\;0: Operational_mode\;1: Test_mode" access="INDEX" enum="Operational_mode=0x0,Test_mode=0x1" offset="0x4.30" size="0x0.1" />
	<field name="lb_link_mode_idx" descr="Index for link mode type configuration\;0: simplex_rate\;1: Bidi_rate" access="INDEX" offset="0x4.31" size="0x0.1" />
</node>

<node name="pprm_reg_ext" descr="" size="0x50.0" >
	<field name="ovrd_no_neg_bhvr" descr="Defines the behavior of no_neg_bhvr field.\;0: ingore_no_neg_bhvr_field - stay with current configured behaivour\;1: no_neg_behavior_according_to_fw_defult - ignore no_neg_bhvr set, and set FW default for the behavior\;2: no_neg_behavior_according_to_no_neg_bhvr_field - set behavior according to configured no_neg_bhvr field" access="RW" offset="0x0.2" size="0x0.2" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="recovery_types_cap" descr="Recovery types that are supported by device.\;Bit 0: host_logic_re_lock\;Bit 1: host_serdes_feq\;Bit 2: module_tx_disable\;Bit 3: module_datapath_full_toggle" access="RO" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,module_tx_disable=0x4,module_datapath_full_toggle=0x8" offset="0x4.0" size="0x0.8" />
	<field name="no_neg_bhvr" descr="Relevant only if ovrd_no_neg_bhvr is set to &apos;2&apos;, ignored otherwise\;In case of no negotiation happened during link up flow, defines the behavior of enabled recovery types:\;Bit 0: host_logic_re_lock\;Bit 1: host_serdes_feq\;Bit 2-3: reserved\;\;0: Disaled\;1: Enabled" access="RW" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,Disaled=0x0,Enabled=0x1" offset="0x4.24" size="0x0.4" />
	<field name="wd_logic_re_lock_res" descr="time resolution for wd_time_host_logic_re_lock field.\;0: 1ms\;1: 10ms\;2: 100ms\;3: 1 sec" access="RW" offset="0x4.28" size="0x0.2" />
	<field name="oper_logic_re_lock_res" descr="time resolution for oper_time_host_logic_re_lock field.\;0: 1ms\;1: 10ms\;2: 100ms\;3: 1 sec" access="RO" offset="0x4.30" size="0x0.2" />
	<field name="module_datapath_full_toggle" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="module_tx_disable" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="host_serdes_feq" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" offset="0x8.8" size="0x0.4" />
	<field name="host_logic_re_lock" descr="Admin Configurations per recovery type.\;Recovery types:\;1. Host Logic re_lock - Physical layer alignment re-lock\;2. Host SerDes Full EQ \;3. Module Tx Disable - Toggle module optical laser to off--&gt;on. supported only on optical modules that support TxDisable command\;4. Full module Toggle - Re-initialization of CMIS module DPSM.\;\;0: FW_default\;1: Enable\;2: Disable\;3: Disable_Support_in_Negotiation\;\;" access="RW" enum="FW_default=0x0,Enable=0x1,Disable=0x2,Disable_Support_in_Negotiation=0x3" offset="0x8.12" size="0x0.4" />
	<field name="link_down_timeout" descr="Desired time in 0 mSec granularity from start of the recovery process until port announces port down.\;value of 0, means that port will announce port down immediately, and will try &quot;recovery&quot; types when port is down.\;Value of 0xFFFFFF means all recovery types allowed will be tried (if agreed) before port announces down" access="RW" offset="0xC.0" size="0x0.16" />
	<field name="link_down_timeout_oper" descr="operational time in 10 mSec granularity from start of the recovery process until port announces port down after negotiation agreed on both sides" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="draining_timeout" descr="Time in mSec from start of the recovery process until port draining starts (and if port is still in &quot;LinkUp&quot;). \;Value of 0 means draining is disabled.\;Default value of 100mSec" access="RW" offset="0x14.0" size="0x0.8" />
	<field name="oper_recovery" descr="Bitmask of agreed and operational recovery modes.\;Prior to negotiation and linkup value will be 0.\;Bit 0: host_logic_re_lock\;Bit 1: host_serdes_feq\;Bit 2: module_tx_disable\;Bit 3: module_datapath_full_toggle" access="RO" enum="host_logic_re_lock=0x1,host_serdes_feq=0x2,module_tx_disable=0x4,module_datapath_full_toggle=0x8" offset="0x18.0" size="0x0.8" />
	<field name="wd_module_full_toggle" descr="500ms granularity for watchdog timer in Module full toggle recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.0" size="0x0.8" />
	<field name="wd_module_tx_disable" descr="100ms granularity for watchdog timer in Module Tx Disable recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.8" size="0x0.8" />
	<field name="wd_host_serdes_feq" descr="10ms granularity for watchdog timer in host FEQ recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.16" size="0x0.8" />
	<field name="wd_host_logic_re_lock" descr="granularity of wd_logic_re_lock_res for watchdog timer in host re_lock recovery\;0: FW default - valid for set only\;on GET operation, returns watchdog value requested" access="RW" offset="0x1C.24" size="0x0.8" />
	<field name="oper_time_module_full_toggle" descr="500ms granularity for operational timer in Module full toggle recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.0" size="0x0.8" />
	<field name="oper_time_module_tx_disable" descr="100ms granularity for operational timer in Module Tx Disable recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.8" size="0x0.8" />
	<field name="oper_time_host_serdes_feq" descr="10ms granularity for operational timer in host FEQ recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.16" size="0x0.8" />
	<field name="oper_time_host_logic_re_lock" descr="granularity of oper_logic_re_lock_res for operational timer in host Re-lock recovery\;on GET operation, returns watchdog value requested" access="RO" offset="0x20.24" size="0x0.8" />
</node>

<node name="pprt_reg_ext" descr="" size="0x24.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPRT configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on lane index\;Affects lane indexing for set operations only, ignored for get operations." access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="Supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved.\;" access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)\;Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols support\;if this bit is cleared - bit 25 (&apos;s&apos;) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols\;0 - No Swap.\;1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dm_ig" descr="disable mask ignore\;If set to 1, the port&quot;s and the cable&quot;s capabilities won&quot;t affect tuning" access="OP" offset="0x0.26" size="0x0.1" />
	<field name="p_c" descr="PRBS RX polarity support indication\;if this bit is cleared - bit 28 (&apos;p&apos;) is ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS RX polarity - NOT gate in PRBS (not Physical lane Polarity)\;\;0 - No polarity inversion.\;1 - PRBS RX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="s" descr="start tuning:\;1 - start RX_tuning based on PRBS pattern \;Notes:\;1) assuming peer transmitting PRBS. \;2) cannot be set when prbs_rx_tuning_status = 1 (during tuning).\;3) In BiDi rates, it is not required to set this bit in the first initialization of test mode after PAOS was set to down. For any re-tuning after initialization it is required to set this bit." access="OP" offset="0x0.30" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS RX is disabled.\;1 - PRBS RX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave : Non error based tune\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)\;Bit 29 - PRBS58 (x^58+ x^39 + 1)" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding [internal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="otf_ch_cap" descr="When set, On the fly configuration change is supported.\;otherwise, change of any configuration requires PAOS toggle.\;Configurations that are supported when bit is set:\;S\;P ( PRBS polarity)\;SW (MSB &lt;-&gt; LSB swap)\;Prbs_mode_admin (pattern)\;msb_lsb_cnt\;Ph_p (physical polarity)\;Modulation (precoding, gray and modulation)\;prbs_hist_fec_int\;Prbs_hist_en" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave : Non error based tune \;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)\;0x1D - PRBS58 (x^58+ x^39 + 1)\;\;\;" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)\;Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)\;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;Bit 11 - XDR / NVL6 / simplex_200G_1x (106.25 Gbd / 212.5 Gb/s)\;Bit 12 - NVL6 / NVL7 / 337p5G_2x_bidi / 168p75G_1x_bidi (90 Gbd / 180 Gb/s)\;Bit 13 - NVL6 / NVL7 / 375G_2x_bidi / 187p5_1x_bidi (100 Gbd / 200 Gb/s)\;Bit 14 - NVL6 / NVL7 / 307p5G_2x_bidi / 153p75G_1x_bidi (82 Gbd / 164 Gb/s)\;Note: PCIe speeds are relevant when pnat = 3 only" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="lane_rate_oper" descr="Lane rate to be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)\;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s) \;8 - XDR / NVL6 / simplex_200G_1x (106.25 Gbd / 212.5 Gb/s)\;9 - NVL6 / NVL7 / 337p5G_2x_bidi / 168p75G_1x_bidi (90 Gbd / 180 Gb/s)\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s)\;13 - NVL6 / NVL7 / 375G_2x_bidi / 187p5_1x_bidi (100 Gbd / 200 Gb/s)\;14 - NVL6 / NVL7 / 307p5G_2x_bidi / 153p75G_1x_bidi (82 Gbd / 164 Gb/s)\;\;Note: All lanes must be set to the same rate.\;Note: PCIe speeds are relevant when pnat = 3 only" access="RW" offset="0x10.16" size="0x0.16" />
	<field name="prbs_lock_status_ext" descr="PRBS lock on PRBS pattern status for lanes 7-4: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked)" access="RO" offset="0x14.20" size="0x0.4" />
	<field name="prbs_lock_status" descr="PRBS lock on PRBS pattern status for lanes 3-0: \;0 - Not locked\;1 - Locked\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0 (Not locked)" access="RO" offset="0x14.24" size="0x0.4" />
	<field name="prbs_rx_tuning_status" descr="Tuning status: \;0 - PRBS mode tuning was not performed.\;1 - Performing PRBS mode tuning.\;2 - PRBS mode tuning completed.\;3 - Signal Detect in progress\;4 - Secondary not detected - this could occur in bidir test mode if the primary device is configured prior to the secondary\;\;Note: Once exiting prbs test mode the prbs_rx_tuning_status will return to 0." access="RO" offset="0x14.28" size="0x0.4" />
</node>

<node name="ppsc_reg_ext" descr="" size="0x30.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
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

<node name="ppslc_ext" descr="" size="0x34.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="l1_req_en" descr="Enable L1 Request\;0: L1 Request is disabled on this port\;1: L1 Request is enabled on this port\;" access="RW" offset="0x4.0" size="0x0.1" />
	<field name="l1_fw_req_en" descr="Enable L1 FW Request\;0: Only L1 HW mode is supported (thermal throttling is disabled) \;1: support thermal throttling on this port \;Reserved for Switch." access="RW" offset="0x8.0" size="0x0.1" />
	<field name="l1_cap_adv" descr="L1 Capability Advertisement\;0: Port doesn&apos;t support L1\;1: Port supports L1 advertisement" access="RW" offset="0x8.4" size="0x0.1" />
	<field name="l1_fw_cap_adv" descr="L1 FW Capability Advertisement\;0: Port doesn&apos;t support L1 FW\;1: Port supports L1 FW advertisement\;Reserved for Switch." access="RW" offset="0x8.8" size="0x0.1" />
	<field name="l0_rx_cap_adv" descr="[DWIP]:\;L0 FW Capability Advertisement\;0: Port doesn&apos;t support L0 FW\;1: Port supports L0 FW advertisement" access="RW" offset="0x8.16" size="0x0.1" />
	<field name="l0_rx_req_en" descr="[DWIP]:\;Enable L0 Request\;0: Port doesn&apos;t support L0 FW\;1: Port supports L0 FW advertisement\;Reserved for Switch." access="RW" offset="0x8.17" size="0x0.1" />
	<field name="l0_tx_cap_adv" descr="[DWIP]:\;L0 FW Capability Advertisement\;0: Port doesn&apos;t support L0 FW\;1: Port supports L0 FW advertisement" access="RW" offset="0x8.18" size="0x0.1" />
	<field name="l0_tx_req_en" descr="[DWIP]:\;Enable L0 Request\;0: Port doesn&apos;t support L0 FW\;1: Port supports L0 FW advertisement\;Reserved for Switch." access="RW" offset="0x8.19" size="0x0.1" />
	<field name="l0_all_queues_are_import" descr="[DWIP]\;If set, L0 controller (HW) requires all queues to be empty before moving to L0 state. Per port parameter in GPU project.\;Reserved for Switch.\;" access="RW" offset="0x8.20" size="0x0.1" />
	<field name="ignore_pred_pm" descr="[DWIP] [SwitchOnly]:\;Ignore Predictor Post Mistake\;If the predictor decision is to move to L1 idle, but no traffic arrives, we will ignore the predictor until traffic arrives again\;0: don&apos;t ignore predictor\;1: ignore predictor" access="RW" offset="0xC.30" size="0x0.1" />
	<field name="pred_algo_en" descr="[DWIP] [SwitchOnly]:\;Predictive Algo Enable\;0: Predictive Algo&apos; is disabled\;1: Predictive Algo&apos; is enabled\;\;Relevant for Switch Only" access="RW" offset="0xC.31" size="0x0.1" />
	<field name="hp_queues_bitmap" descr="High Priority Queues Bitmap\;for each queue, \;0: Normal queue\;1: High priority queue\;\;Note: High priority queues can move to L1 active only when queue is fully empty. Normal queues can move to L1 active as long as the number of bytes within the queue is lower than MPSCR.queue_depth_th\;\;bits 17-31 are reserved" access="RW" offset="0x10.0" size="0x4.0" />
	<field name="l1_hw_active_time" descr="units of 50 usec minimum value of 50 usec\;" access="RW" offset="0x18.0" size="0x0.10" />
	<field name="l1_hw_inactive_time" descr="units of 50 usec. minimum value of 50 usec\;" access="RW" offset="0x1C.0" size="0x0.10" />
	<field name="l0_hw_inactive_time" descr="[DWIP]\;units of 50 nsec. minimum value of 50 nsec\;Valid only for GR100, QM-4 and above\;In QM4, changing this value will require link toggle\;" access="RW" offset="0x1C.16" size="0x0.10" />
	<field name="qem" descr="Queue Desire (state) Exit Mode upon traffic arrival\;0: Move to L1 Idle immediately \;1: Wait for desire window completion before moving to L1 idle\;2: Ignore traffic arrival \;\;Note: \;For GB100, only index 0-7 are valid. \;For QM-3 only index 0-16 are valid. \;Must be 0 for queues defined in hp_queues_bitmap as high priority." access="RW" high_bound="19" low_bound="0" offset="0x20.24" size="0x14.0" />
</node>

<node name="ppsld_ext" descr="" size="0x14.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="fw_mode" descr="FW Mode\;0: Trigger Once - \;1: Infinite L1 Idle \;2: Infinite L1 Desire \;3: Toggle Always \;4: Disabled \;5: Infinite L0 Force \;6: Infinite L1 Force \;\;Note: can be changed only when device in not under thermal event. During thermal event, FW will override the use debug configuration." access="RW" offset="0x4.0" size="0x0.3" />
	<field name="trigger" descr="Trigger port to move to force mode one time\;0: No trigger\;1: Trigger port to move to force mode\;Valid only when fw_mode = Trigger Once" access="OP" offset="0x8.0" size="0x0.1" />
	<field name="ehld" descr="Exposed HW L1 desire\;The state of the controller2plu_l1_desire bit that controller publishes \;" access="RO" offset="0xC.0" size="0x0.2" />
	<field name="fw_idle_window_time" descr="FW Idle Window time\;units of 100uSec\;Relevant only for fw_mode = Toggle always (3)." access="RW" offset="0x10.0" size="0x0.8" />
	<field name="fw_desire_window_time" descr="FW Desire Window time\;units of 100uSec\;Relevant only for fw_mode = Trigger once (0) or Toggle always (3)." access="RW" offset="0x10.16" size="0x0.8" />
</node>

<node name="ppsls_ext" descr="" size="0x8.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="l1_fw_mode_cap" descr="0: Port doesn&apos;t support L1 fw mode\;1: Port supports L1 fw mode" access="RO" offset="0x4.16" size="0x0.1" />
	<field name="l1_cap" descr="0: Port doesn&apos;t support L1\;1: Port supports L1" access="RO" offset="0x4.18" size="0x0.1" />
	<field name="l0_neg_rx_status" descr="[DWIP]\;L0 RX negotiation status\;0: L0 RX negotiation failed (L1 is not supported by both sides)\;1: L0 RX negotiation succeeded (supported on both sides)\;Reserved when link is down" access="RO" offset="0x4.19" size="0x0.1" />
	<field name="l0_neg_tx_status" descr="[DWIP]\;L0 TX negotiation status\;0: L0 TX negotiation failed (L1 is not supported by both sides)\;1: L0 TX negotiation succeeded (supported on both sides)\;Reserved when link is down" access="RO" offset="0x4.20" size="0x0.1" />
	<field name="fw_mode_remote" descr="FW mode remote indication\;0: N/A\;1: L1 fw mode remote capability is set \;2: L1 fw mode remote request is set \;3: L1 fw mode remote request and capability are set \;Valid only is l1_neg_status = 1 \;Reserved when link is down" access="RO" offset="0x4.27" size="0x0.2" />
	<field name="fw_mode_act" descr="Actual Mode \;0: HW mode\;1: FW mode\;Valid only is l1_neg_status = 1 \;Reserved when link is down\;Reserved for Switch." access="RO" offset="0x4.29" size="0x0.1" />
	<field name="fw_mode_neg_status" descr="FW mode negotiation status\;0: L1 fw mode negotiation failed\;1: L1 fw mode negotiation succeeded \;Valid only if l1_neg_status = 1 \;Reserved when link is down" access="RO" offset="0x4.30" size="0x0.1" />
	<field name="l1_neg_status" descr="L1 negotiation status\;0: L1 negotiation failed (L1 is not supported by both sides)\;1: L1 negotiation succeeded (supported on both sides)\;Reserved when link is down" access="RO" offset="0x4.31" size="0x0.1" />
</node>

<node name="pptb_reg_ext" descr="" size="0xc.0" >
	<field name="pm" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i." access="WO" offset="0x0.0" size="0x0.8" />
	<field name="um" descr="untagged_buff mask - enables update of the untagged_buff field.\;Reserved for Spectrum family.\;Reserved for HCA devices." access="WO" offset="0x0.8" size="0x0.1" />
	<field name="cm" descr="ctrl_buff mask - enables update of the ctrl_buff field.\;NOTE: This field is ignored by the device, and control traffic is mapped to a pre-defined buffer (buffer - 9).\;In some old implementations (on SwitchX and SwitchX-2) software is required to use the value 9 in this field, later devices ignore this field.\;Reserved for HCA devices" access="WO" offset="0x0.9" size="0x0.1" />
	<field name="lp_msb" descr="Local port[9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="mm" descr="Mapping mode\;0: Mapping both Unicast and Multicast packets to the same buffer\;In get operation, 0 means Unicast only.\;1: Mapping Unicast only\;2: Mapping Multicast only\;This field is reserved for HCA devices\;SwitchX/-2 support &apos;0&apos; only" access="INDEX" offset="0x0.28" size="0x0.2" />
	<field name="prio0buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.0" size="0x0.4" />
	<field name="prio1buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.4" size="0x0.4" />
	<field name="prio2buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="prio3buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.12" size="0x0.4" />
	<field name="prio4buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.16" size="0x0.4" />
	<field name="prio5buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="prio6buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.24" size="0x0.4" />
	<field name="prio7buff" descr="Mapping of Switch Priority of &lt;X&gt; to one of the allocated receive port buffers.\;&lt;X&gt; = 0..7\;" access="RW" offset="0x4.28" size="0x0.4" />
	<field name="untagged_buff" descr="Mapping of untagged frames to one of the allocated receive port buffers.\;NOTE: In SwitchX/-2, this field must be mapped to a buffer 8.\;\;Reserved for Spectrum. Spectrum maps untagged packets based on the Switch Priority.\;Reserved for HCA devices" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="ctrl_buff" descr="Mapping of control frames to one of the allocated receive port buffers.\;NOTE: This field is ignored by the device, and control traffic is mapped to a pre-defined buffer (buffer - 9).\;In some old implementations (on SwitchX and SwitchX-2), software is required to use the value 9 in this field, later devices ignore this field.\;Reserved for HCA devices" access="RW" offset="0x8.4" size="0x0.4" />
	<field name="pm_msb" descr="prioX_buff mask - enables update of the prioX_buff field.\;Bit i is a flag for updating the mapping for switch priority i+8.\;Reserved for HCA device" access="WO" offset="0x8.24" size="0x0.8" />
</node>

<node name="pptt_reg_ext" descr="" size="0x1c.0" >
	<field name="le" descr="Per Lane configuration enable (can be set only if ls = 1):\;0 - No per lane configuration\;1 - Per lane configurations\;When le is cleared, lane index is reserved and all PPTT configurations are taking place on all lanes.\;When le is set, configurations are taking place per lane based on lane index\;Affects lane indexing for set operations only, ignored for get operations" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="ls" descr="Per Lane configuration support/capability: \;0 - No support of per lane configuration\;1 - Support of per lane configuration" access="RO" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0 - Network Port\;1 - Near-End Port (For Retimer/Gearbox - Host side)\;2 - Internal IC LR Port \;3 - Far-End Port (For Retimer/Gearbox - Line side)\;Other values are reserved.\;Note: PRBS can be enabled only for two entities that directly connected to each other.\;For non MCM and no Retimer/Gearbox only 0 allowed.\;For non MCM and with Retimer/Gearbox 2-1 or 3 or 0.\;For MCM without Retimer/Gearbox 4-5 or 2 or 0.\;For MCM with Retimer/Gearbox 4-5 or 2-1 or 3 or 0.\;all the port will be in test mode when PRBS is enabled." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Reserved when (le=0 or ls = 0)\;Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="local_port" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sw_c" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols support\;if this bit is cleared - bit 25 (&apos;s&apos;) is ignored" access="RO" offset="0x0.24" size="0x0.1" />
	<field name="sw" descr="PRBS MSB &lt;-&gt;LSB Swap for PAM4 symbols\;0 - No Swap.\;1 - Swap MSB &lt;-&gt; LSB." access="RW" offset="0x0.25" size="0x0.1" />
	<field name="dm_ig" descr="disable mask ignore\;If set to 1, the port&quot;s and the cable&quot;s capabilities won&quot;t affect tuning" access="OP" offset="0x0.26" size="0x0.1" />
	<field name="p_c" descr="PRBS TX polarity support indication.\;if this bit is cleared - bit 28 (&apos;p&apos;) is been ignored" access="RO" offset="0x0.27" size="0x0.1" />
	<field name="p" descr="PRBS TX polarity - NOT gate in PRBS (not Physical lane Polarity)\;0 - No polarity inversion.\;1 - PRBS TX polarity inversion." access="RW" offset="0x0.28" size="0x0.1" />
	<field name="e" descr="Enable PRBS test mode bit:\;0 - PRBS TX is disabled.\;1 - PRBS TX is enabled." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="prbs_modes_cap" descr="PRBS capability (bitmask)\;Bit 0 - PRBS31 (x^31 + x^28 + 1)\;Bit 1 - PRBS23A (x^23 + x^18 + 1)\;Bit 2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;Bit 3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;Bit 4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;Bit 5 - PRBS7 (x^7 + x^6 + 1)\;Bit 6 - PRBS11 (x^11 + x^9 + 1)\;Bit 7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;Bit 8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;Bit 9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;Bit 10 - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;Bit 11 - PRBS9 (x^9 + x^5 + 1)\;Bit 12 - IDLE using scramble58 (x^58+ x^39 + 1)\;Bit 13 - Square_wave8 (8 ones, 8 zeros)\;Bit 14 - Square_wave4 (4 ones, 4zeros)\;Bit 15 - Square_wave2 (2 ones, 2zeros)\;Bit 16 - Square_wave1 (one, zero)\;Bit 17 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;Bit 18 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;Bit 19 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;Bit 20 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;Bit 21- SSPR\;Bit 22- SSPRQ\;Bit 23- LT frames (KR-startup frames)\;Bit 24 - PRBS15 - x^15 + x^14 + 1\;Bit 25 - PRBS28 - x^28 + x^25 + 1\;Bit 26 - Square wave3 (3ones, 3zeros)\;Bit 27 - Square wave13 (13ones, 13zeros)\;Bit 28 - Square wave30 (30ones, 30zeros)\;Bit 29 - PRBS58 (x^58+ x^39 + 1)\;" access="RO" offset="0x4.0" size="0x4.0" />
	<field name="modulation" descr="Reserved for speeds below 53.125Gb/s (lane_rate_admin &lt; 13):\;0 - NRZ test pattern\;1 - PAM4 encoding [internal] with gray no precoding\;2 - PAM4 with precoding [internal] with gray\;3 - PAM4 without gray no precoding\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="otf_ch_cap" descr="When set, On the fly configuration change is supported.\;otherwise, change of any configuration requires PAOS toggle.\;Configurations that are supported when bit is set:\;P ( PRBS polarity)\;SW (MSB &lt;-&gt; LSB swap)\;Prbs_mode_admin (PRBS pattern)\;msb_lsb_cnt\;Ph_p (physical polarity)\;Modulation (precoding, gray and modulation)" access="RO" offset="0x8.15" size="0x0.1" />
	<field name="prbs_mode_admin" descr="See prbs_mode_cap: \;0x0 - PRBS31 (x^31 + x^28 + 1)\;0x1 - PRBS23A (x^23 + x^18 + 1)\;0x2 - PRBS23B (x^23 + x^18 + x^12+ x^6 + 1)\;0x3 - PRBS23C (x^23 + x^22 + x^19+ x^18 + 1)\;0x4 - PRBS23D (x^23 + x^19 + x^18+ x^11 + 1)\;0x5 - PRBS7 (x^7 + x^6 + 1)\;0x6 - PRBS11 (x^11 + x^9 + 1)\;0x7 - PRBS11A (x^11 + x^10 + x^6+ x^5 + 1)\;0x8 - PRBS11B (x^11 + x^9 + x^6+ x^5 + 1)\;0x9 - PRBS11C (x^11 + x^8 + x^6+ x^4 + 1)\;0xA - PRBS11D (x^11 + x^7 + x^6+ x^4 + 1)\;0xB - PRBS9 (x^9 + x^5 + 1)\;0xC - IDLEs using scramble58 (x^58+ x^39 + 1)\;0xD - Square_wave8 (8 ones, 8 zeros)\;0xE - Square_wave4 (4 ones, 4zeros)\;0xF - Square_wave2 (2 ones, 2zeros)\;0x10 - Square_wave1 (one, zero)\;0x11 - PRBS13A (x^13 + x^12 + x^2+ x + 1)\;0x12 - PRBS13B (x^13 + x^7 + x^3+ x^2 + 1)\;0x13 - PRBS13C (x^13 + x^8 + x^4+ x^2 + 1)\;0x14 - PRBS13D (x^13 + x^9 + x^5+ x^2 + 1)\;0x15 - SSPR\;0x16 - SSPRQ\;0x17 - LT frames (KR-startup frames)\;0x18 - PRBS15 - x^15 + x^14 + 1\;0x19 - PRBS28 - x^28 + x^25 + 1\;0x1A - Square wave3 (3ones, 3zeros)\;0x1B - Square wave13 (13ones, 13zeros)\;0x1C - Square wave30 (30ones, 30zeros)\;0x1D - PRBS58 (x^58+ x^39 + 1)\;0x1E - Default Pattern - Recommended for Bidir links for simplicity\;" access="RW" offset="0x8.24" size="0x0.8" />
	<field name="prbs_fec_cap" descr="When set, PRBS over FEC is supported.\;Note: Feature is enabled on all lanes of port" access="RO" offset="0xC.0" size="0x0.1" />
	<field name="lane_rate_cap" descr="Per lane rate capability (bitmask)\;Bit 0 - 1GE (1.25 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;Bit 1 - SDR (2.5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;Bit 2 - XAUI/2.5GE (3.125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;Bit 3- DDR (5 Gb/s) / Gen 4 PCIe (16 Gb/s)\;Bit 4- QDR (10 Gb/s) / Gen 5 PCIe (32 Gb/s)\;Bit 5- FDR10 / 10GE/40GE (10.3125 Gb/s) / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;Bit 6- FDR (14.0625 Gb/s) \;Bit 7- EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) \;Bit 8 - 50GE-KR4 (12.89 Gb/s) \;Bit 9 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s) \;Bit 10 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;Bit 11 - XDR / NVL6 / 200G_simplex_1x (106.25Gbd / 212.5Gb/s)\;Bit 12 - NVL6 / NVL7 / 337p5G_2x_bidi / 168p75G_1x_bidi (90 Gbd / 180Gb/s)\;Bit 13 - NVL6 / NVL7 / 375G_2x_bidi / 175p5_1x_bidi (100 Gbd / 200Gb/s)\;Bit 14 - NVL6 / NVL7 / 330G_2x_bidi / 153p75G_1x_bidi (82 Gbd / 164 Gb/s)\;\;Note: PCIe speeds are relevant when pnat = 3 only\;Note: for Bidir rates the following field" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="prbs_fec_admin" descr="When set, PRBS over FEC is enabled for port.\;For FEC configuration, set PPLM.test_mode" access="RW" offset="0x10.0" size="0x0.1" />
	<field name="lane_rate_admin" descr="Lane rate be used in PRBS, see lane_rate_cap:\;0 - SDR (2.5 Gb/s) / Gen 1 PCIe (2.5 Gb/s)\;1 - DDR (5 Gb/s) / Gen 2 PCIe (5 Gb/s)\;2 - QDR (10 Gb/s)\;3 - FDR10 / 10GE/4 0GE (10.3125 Gb/s) / Gen 3 PCIe (8 Gb/s)\;4 - FDR (14.0625 Gb/s) / Gen 4 PCIe (16 Gb/s)\;5 - EDR / 25GE / 50GE / 100GE (25.78125 Gb/s) / Gen 5 PCIe (32 Gb/s)\;6 - HDR /50GE / 100GE / 200GE / 400GE (26.5625Gbd / 53.125Gb/s / Gen 5 PCIe (64 Gb/s PAM4, 32Gbd)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR / NVL6 / 200G_simplex_1x (106.25 Gbd / 212.5 Gb/s)\;9 - NVL6 / NVL7 / 337p5G_2x_bidi / 168p75G_1x_bidi (90 Gbd / 180 Gb/s)\;10 - 1GE (1.25 Gb/s)\;11 - XAUI/2.5GE (3.125 Gb/s)\;12 - 50GE-KR4 (12.89 Gb/s)\;13 - NVL6 / NVL7 / 375G_2x_bidi / 187p5_1x_bidi (100 Gbd / 200 Gb/s)\;14 - NVL6 / NVL7 / 307p5G_2x_bidi / 153p75G_1x_bidi (82 Gbd / 164 Gb/s)\;\;Note: All lanes must be set to the same rate\;Note: PCIe speeds are relevant when pnat = 3 only" access="RW" offset="0x10.16" size="0x0.16" />
</node>

<node name="prei_reg_28nm_ext" descr="" size="0x8.0" >
	<field name="mixer_offset1" descr="eye centering control.\;may cause link degradation when set." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="mixer_offset0" descr="eye centering control.\;may cause link degradation when set." access="RW" offset="0x0.16" size="0x0.16" />
</node>

<node name="prei_reg_ext" descr="" size="0x18.0" >
	<field name="status" descr="Error injection status:\;     0x0 -Good status \;     0x2 - No available sources for Error injection \;     0x3 - Error injection configuration when port is in non operational state (port is neither in UP or TEST MODE)" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="time_res" descr="0: 10ms" access="OP" offset="0x0.4" size="0x0.2" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="1 - 28nm products\;3 - 16nm products" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="mps" descr="[DWIP]\;Multiple Port Set.\;Supported only if indicated in PMSCR.prm_support of PREI support, otherwise ignored.\;When set, local_port index is ignored and set command is given to all ports in mask given from PMSCR.local_port_mask field" access="INDEX" offset="0x0.31" size="0x0.1" />
	<field name="error_type_admin" descr="Error Type to generate:\;0: No_Error ---- Physical Errors ---- \;Bit 0: mixer_offset_ctrl_set" access="RW" enum="mixer_offset_ctrl_set=0x1" offset="0x4.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities:\;Bit 0: mixer_offset_ctrl" access="RO" enum="mixer_offset_ctrl=0x1" offset="0x4.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection operational status:\; 0x0 - No error injection \; 0x1 - Performing error injection" access="RO" offset="0x4.24" size="0x0.4" />
	<field name="error_injection_time" descr="Duration in time_res the port will generate errors. Reading this field will return the time left for errors to inject in msec.\;0x0000 indicates no generation of errors. \;0xFFFF - No decremental operation, meaning the errors will be injected continuously without stop condition. \;" access="RW" offset="0x8.12" size="0x0.16" />
	<field name="page_data" descr="Table  579, &quot;PREI - Port Receive Error Injection Register Layout for 28nm,&quot; on page  613" subnode="prei_reg_28nm_ext" access="RW" offset="0x10.0" size="0x8.0" />
</node>

<node name="prm_register_payload_ext" descr="" size="0x104.0" >
	<field name="register_id" descr="Register ID" access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="method" descr="0: Query\;1: Write" access="OP" offset="0x0.22" size="0x0.2" />
	<field name="status" descr="Return code of the Downstream Device to the register that was sent.\;0x0: OK - Operation was successfully executed\;0x1: BUSY \;0x4: NOT_SUPP_REG - The Switch register requested is not supported on that device\;0x7: BAD_PARAM - Incomplete or erroneous parameter set\;0x70: INTERNAL_ERR - Internal error" access="RO" offset="0x0.24" size="0x0.8" />
	<field name="register_data" descr="Register data" access="RW" high_bound="63" low_bound="0" offset="0x4.0" size="0x100.0" />
</node>

<node name="prtl_reg_ext" descr="" size="0x20.0" >
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0: Local_port_number\;1: IB_port_number\;3: Out_of_band" access="INDEX" enum="Local_port_number=0x0,IB_port_number=0x1,Out_of_band=0x3" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="rtt_support" descr="Support of RTT measurement" access="RO" offset="0x0.31" size="0x0.1" />
	<field name="latency_accuracy" descr="Latency measurement accuracy (i,e. max error size). \;accuracy is relative to specific device implementation. \;This field returns the accuracy in nsec resolution. \;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="latency_res" descr="Latency resolution in nsec of round_trip_latency \;\;" access="RO" offset="0x4.16" size="0x0.4" />
	<field name="local_phy_latency" descr="Shall be 0 if not implemented (rtt_support = 0). \;This value represents the intra-ASIC pipeline latency of the physical layer. It is an unsigned 16-bit integer in nsec." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="local_mod_dp_latency" descr="Shall be 0 if not implemented (rtt_support = 0), if the module is not plugged in or if the information is not available on the plugged module. \;This value represents the module&apos;s Datapath pipeline latency.It It is an unsigned 16-bit integer in nsec." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="round_trip_latency" descr="Shall be 0 if not implemented (rtt_support = 0). \;This value represents a measurement of the round-trip latency of the link attached to this port. \;It is an unsigned 24-bit integer counting latency_res nsec. \;intervals. \;This value might not be accurate to better than +/- latency_accuracy nsec. \;A value of 0 is valid when implemented, and indicates a latency of up to latency_accuracy nsec. \;round_trip_latency is reset to 0xFFFFFF whenever this port transitions to PAOS.Oper_status = Down." access="RO" offset="0x10.0" size="0x0.24" />
</node>

<node name="prtsr_ext" descr="" size="0x10.0" >
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="gl" descr="Global:\;0: per port\;1: global, all ports\;When reading and gl=1, read from local_port &apos;1&apos;" access="INDEX" offset="0x0.28" size="0x0.1" />
	<field name="prio_bitmask" descr="Prio bitmask\;When IB: VLs\;When read: only 1 bit must be set\;When IB: valid bits: 0..7" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="ts" descr="Transmit Suspend:\;0: Off (transmit enabled)\;1: On (transmit suspended)\;2: Cycle_Based Internal] FW sets iteration to 0xFF, thus 10^76Sec which is 10^60 years" access="RW" offset="0x8.0" size="0x0.2" />
	<field name="cycle_time" descr="Cycle time \;Cycle time will be 2^cycle_time*clk_time\;clk_time (nSec) = 1000/QUERY_FW.core_clk (Mhz)" access="RW" offset="0xC.0" size="0x0.6" />
</node>

<node name="ptasv2_7nm_ext" descr="" size="0x28.0" >
	<field name="lt_ext_neg_type" descr="affects negotiation type for lt_ext fields: iter_time_admin, num_of_iter_admin, prbs_type_admin, lt_ext_timeout_admin, ber_target_admin\;0: neg_agreed_function - oper fields will be applied by agreed function of negotiation\;1: force_params_to_peer - negotiation will force peer side to choose the local parameters. if both sides try to force parameters, agreed function will be applied\;2: ignore_neg - set support in negotiation to 0 and set local config to HW. this bit may result in an asymmetrical training between sides. Applicable only for hybrid lt ext only" access="RW" offset="0x10.16" size="0x0.2" />
	<field name="kr_extra_tune_fine_srch_cap" descr="When set, kr_extra_tune_fine_srch_en is supported" access="RO" offset="0x10.26" size="0x0.1" />
	<field name="ber_cnt_mlsd_dis_cap" descr="When set, ber_cnt_mlsd_dis is supported." access="RO" offset="0x10.27" size="0x0.1" />
	<field name="ber_target_cap" descr="When set, ber_target_coef_admin/oper and ber_target_magnitude_admin/oper are supported" access="RO" offset="0x10.28" size="0x0.1" />
	<field name="lt_ext_timeout_cap" descr="When set, lt_ext_timeout_admin/oper is supported" access="RO" offset="0x10.29" size="0x0.1" />
	<field name="prbs_type_cap" descr="When set, prbs_type_admin/oper is supported" access="RO" offset="0x10.30" size="0x0.1" />
	<field name="iterations_cap" descr="When set, iter_time_admin/oper and num_of_iter_admin/oper are supported" access="RO" offset="0x10.31" size="0x0.1" />
	<field name="lt_ext_timeout_admin" descr="requested value of The maximum time that the transmitter can transmit the requested PRBS type.\;\;Minimum required 60 secs. Granularity 1 sec\;\;Note that: transmitted iterations x transmitted iteration time + 10 msec, shall be less or equal to Maximum extended link training time." access="RW" offset="0x14.0" size="0x0.8" />
	<field name="prbs_type_admin" descr="0: PRBS_13\;1: PRBS_31" access="RW" offset="0x14.8" size="0x0.2" />
	<field name="ber_cnt_mlsd_dis" descr="When set, Disables mlsd during ber count" access="RW" offset="0x14.10" size="0x0.1" />
	<field name="kr_extra_tune_fine_srch_en" descr="When set, Enables fine search algorithm" access="RW" offset="0x14.11" size="0x0.1" />
	<field name="num_of_iter_admin" descr="requested value of The number of required iterations. This parameter is required only for Async mode.\;\;The range is 1 to 16." access="RW" offset="0x14.16" size="0x0.4" />
	<field name="iter_time_admin" descr="requested value of the time that each iteration will use. An iteration is defined as a the time of the BER measurement that comes after the equalization.\;\;10 msec granularity." access="RW" offset="0x14.22" size="0x0.10" />
	<field name="ber_target_coef_admin" descr="requested value of BER target value.\;exit condition if BER target is met prior to end of all iterations, finish the algorithm\;BER_target = ber_target_coef *10^(-ber_target_magnitude)" access="RW" offset="0x18.0" size="0x0.4" />
	<field name="ber_target_magnitude_admin" descr="requested value of BER target value.\;exit condition if BER target is met prior to end of all iterations, finish the algorithm\;BER_target = ber_target_coef *10^(-ber_target_magnitude)" access="RW" offset="0x18.8" size="0x0.8" />
	<field name="lt_ext_timeout_oper" descr="operational value of The maximum time that the transmitter can transmit the requested PRBS type.\;\;Minimum required 60 secs. Granularity 1 sec\;\;Note that: transmitted iterations x transmitted iteration time + 10 msec, shall be less or equal to Maximum extended link training time." access="RO" offset="0x1C.0" size="0x0.8" />
	<field name="prbs_type_oper" descr="operational value of prbs type\;0: PRBS_13\;1: PRBS_31" access="RO" offset="0x1C.8" size="0x0.2" />
	<field name="num_of_iter_oper" descr="operational value of The number of required iterations. This parameter is required only for Async mode.\;\;The range is 1 to 16." access="RO" offset="0x1C.16" size="0x0.4" />
	<field name="iter_time_oper" descr="operational value of the time that each iteration will use. An iteration is defined as a the time of the BER measurement that comes after the equalization.\;10 msec granularity." access="RO" offset="0x1C.22" size="0x0.10" />
	<field name="ber_target_coef_oper" descr="operational value of BER target value.\;exit condition if BER target is met prior to end of all iterations, finish the algorithm\;BER_target = ber_target_coef *10^(-ber_target_magnitude)" access="RO" offset="0x20.0" size="0x0.4" />
	<field name="ber_target_magnitude_oper" descr="operational value of BER target value.\;exit condition if BER target is met prior to end of all iterations, finish the algorithm\;BER_target = ber_target_coef *10^(-ber_target_magnitude)" access="RO" offset="0x20.8" size="0x0.8" />
</node>

<node name="ptasv2_reg_ext" descr="" size="0x30.0" >
	<field name="xdr_lt_cap" descr="XDR LT capability.\;When set, xdr_lt_c2m_en and xdr_lt_c2c_en control is possible." access="RO" offset="0x0.4" size="0x0.1" />
	<field name="ib_cfg_delaytimeout_cap" descr="Configuration of DelayTimeOut capability.\;When set ib_cfg_delaytimeout control is possible.\;\;[Note: This feature is currently available only for HDR switch]" access="RO" offset="0x0.10" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type.\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: products_40nm\;1: products_28nm\;4: products_7nm\;5: products_5nm" access="RO" enum="products_7nm=0x4,products_5nm=0x5" offset="0x0.24" size="0x0.4" />
	<field name="xdr_lt_c2c_en" descr="LT for C2C channel Vs peer XDR speeds (200G per lane)\;0 - Auto (FW default)\;1 - skip LT flow\;2 - do LT flow\;This bit will affect requested lt_xdr negotiation vs peer." access="RW" offset="0x4.0" size="0x0.2" />
	<field name="xdr_lt_c2m_en" descr="LT for C2M channel Vs Module XDR speeds (200G per lane)\;0 - Auto (FW default)\;1 - skip LT flow\;2 - do segmented LT flow" access="RW" offset="0x4.2" size="0x0.2" />
	<field name="kr_ext_oper" descr="Updated only after LT phase was performed.\;0: lt_is_disabled\;1: lt_enabled_regular_kr\;2: lt_enabled_ext_kr_async_mode" access="RO" offset="0x4.24" size="0x0.2" />
	<field name="kr_ext_req" descr="Extended KR request:\;\;0: Auto - (FW default)\;1: Disable_kr_ext\;2: Enable_kr_ext_in_async_mode\;\;While the KR extended is enabled- nonstandard KR training will occur. This will include pause periods between sending the KR frames and sending the PRBS pattern instead (to support BER grade calculations)" access="RW" enum="Disable_kr_ext=0x1,Enable_kr_ext_in_async_mode=0x2" offset="0x4.29" size="0x0.2" />
	<field name="kr_ext_cap" descr="Extended KR capability. Will return support for a nonstandard KR training flow (as explained in the fields below)." access="RO" offset="0x4.31" size="0x0.1" />
	<field name="page_data" descr="Table 713, &quot;PTASv2 - Phy Tuning Algorithm Settings Register Layout for 7nm and 5nm,&quot; on page 767" subnode="ptasv2_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x8.0" size="0x28.0" />
</node>

<node name="ptasv2_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x28.0" >
	<field name="ptasv2_7nm_ext" descr="" subnode="ptasv2_7nm_ext" condition="($(parent).version == products_7nm) | ($(parent).version == products_5nm)" offset="0x0.0" size="0x28.0" />
</node>

<node name="pter_phy_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate\;0: No_Error\;1: Raw_BER\;2: Effective_BER\;4: Symbol_errors - all transmitted 66/64 bit symbols will be erroneous for the configured time period in error_injection_time" access="RW" enum="No_Error=0x0,Raw_BER=0x1,Effective_BER=0x2,Symbol_errors=0x4" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities \;Bit 0: Raw_BER\;Bit 1: Effective_BER\;Bit 2 : Symbol_errors" access="RO" enum="Raw_BER=0x1,Effective_BER=0x2,Symbol_errors=0x4" offset="0x0.8" size="0x0.8" />
	<field name="error_type_oper" descr="Error injection operational status\;0x0 - No error injection\;0x1 - Performing error injection" access="RO" offset="0x0.24" size="0x0.4" />
	<field name="ber_exp" descr="BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ber_mantissa" descr="BER for injection.\;BER = ber_mantissa * 10^(-ber_exp)" access="RW" offset="0x4.8" size="0x0.4" />
	<field name="error_injection_time" descr="Duration in 10 msec the port will generate errors.\;Reading this field will return the time left for errors to inject in msec\;\;\;0x0000 indicates no generation of errors.\;When set to 0xFFFF - No decremental operation, meaning the errors will be injected continuously without stop condition." access="RW" offset="0x4.12" size="0x0.16" />
</node>

<node name="pter_port_page_reg_ext" descr="" size="0x1c.0" >
	<field name="error_type_admin" descr="Error Type to generate\;0 - No Error\;---- Port Errors ----\;1 - Corrupt data packet ICRC\;2 - Corrupt data packet VCRC\;4- Corrupt credit packet LPCRC" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="error_type_cap" descr="Error injection capabilities \;Bit 0- Corrupt data packet ICRC\;Bit 1- Corrupt data packet VCRC\;Bit 2- Corrupt credit packet LPCRC\;" access="RO" offset="0x0.8" size="0x0.8" />
	<field name="error_count" descr="Error Count\;Number of times the port will generate the configured error.\;0 indicates not to generate error.\;Reading error_count will return the number of left errors to inject. When 0, all requested errors has been injected." access="RW" offset="0x4.12" size="0x0.5" />
</node>

<node name="pter_reg_ext" descr="" size="0x20.0" >
	<field name="status" descr="Error injection status: \;0x0 -Good status\;0x2 - No available sources for Error injection\;0x3 - Error injection configuration when port is in non operational state (port is neither in UP or TEST MODE)\;0x4 - out of range BER setting" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="error_page" descr="Error_page selection: \;0: Injection_of_Phy_Errors\;1: Injection_of_Port_Errors" access="INDEX" enum="Injection_of_Phy_Errors=0x0,Injection_of_Port_Errors=0x1" offset="0x0.24" size="0x0.4" />
	<field name="page_data" descr="error injection page data: \;Table  573, &quot;PTER- Port Transmit Errors Register Phy Level Layout,&quot; on page  610\;Table  575, &quot;PTER- Port Transmit Errors Register Port Level Fields,&quot; on page  611" subnode="pter_reg_page_data_auto_ext" access="RW" offset="0x4.0" size="0x1c.0" union_selector="$(parent).error_page" />
</node>

<node name="pter_reg_page_data_auto_ext" descr="" attr_is_union="1" size="0x1c.0" >
	<field name="pter_phy_page_reg_ext" descr="" subnode="pter_phy_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Phy_Errors" size="0x1c.0" />
	<field name="pter_port_page_reg_ext" descr="" subnode="pter_port_page_reg_ext" offset="0x0.0" selected_by="Injection_of_Port_Errors" size="0x1c.0" />
</node>

<node name="ptsb_ext" descr="" size="0x20.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="sl" descr="SL\;For GB100: allowed 0..3\;Reserved when type = 0" access="INDEX" offset="0x4.0" size="0x0.4" />
	<field name="vc" descr="VC (Virtual Channel)\;For GB100: allowed 0,1\;Reserved when type = 1" access="INDEX" offset="0x4.4" size="0x0.4" />
	<field name="pipe" descr="Pipe\;For GB100: allowed 0,1\;Reserved when type = 1" access="INDEX" offset="0x4.8" size="0x0.4" />
	<field name="type" descr="Type:\;0: NVLink\;1: IB" access="INDEX" offset="0x4.12" size="0x0.4" />
	<field name="burst_send" descr="Burst send:\;Send up to burst_send consecutive packets.\;Value of 0 is not supported.\;FW will send 1 packet after each other, typically time of 100&apos;s of nSec between every 2 packets.\;Note that this &quot;allows sending&quot;. If there are no packets or no credits then the packets will not be transmitted but the counter will be incremented" access="OP" offset="0x8.0" size="0x0.10" />
</node>

<node name="ptsr_ext" descr="" size="0x20.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="ts" descr="Tx suspend:\;0: Tx enabled (default)\;1: Tx disabled" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="ptys_reg_ext" descr="" size="0x44.0" >
	<field name="proto_mask" descr="Protocol Mask. Indicates which of the protocol data is valid\;Bit 0: InfiniBand\;Bit 1: NVLink\;Bit 2: Ethernet\;\;" access="INDEX" enum="InfiniBand=0x1,NVLink=0x2,Ethernet=0x4" offset="0x0.0" size="0x0.3" />
	<field name="transmit_allowed" descr="Valid only when port is mapped to SW controlled module, otherwise ignored. module control can be queried via MMCR register.\;\;0: transmit_not_allowed - Transmitter is not allowed to transmit signal on output\;1: transmit_allowed - Transmitter is allowed to transmit signal on output. for enabling transmitter, PAOS.admin_status must be up as well." access="RW" enum="transmit_not_allowed=0x0,transmit_allowed=0x1" offset="0x0.3" size="0x0.1" />
	<field name="plane_ind" descr="Reserved for non-planarized port.\;Plane port index of the aggregated port. A value of 0 refers to the aggregated port only." access="INDEX" offset="0x0.4" size="0x0.4" />
	<field name="port_type" descr="Supported only when indicated by PCAM \;0: Network_Port\;1: Near-End_Port - (For Gearbox - Host side)\;2: Internal_IC_Port \;3: Far-End_Port - (For Gearbox - Line side)\;\;Other values are reserved." access="INDEX" enum="Network_Port=0x0,Near=0x1,Internal_IC_Port=0x2,Far=0x3" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="tx_ready_e" descr="Valid only when ee_tx_ready is set, otherwise field is ignored.\;0: do_not_generate_event\;Bit 0: generate_tx_ready_event - When set, PTSE register will generate event when Transmitter is generating valid signal on the line\;Bit 1: generate_tx_not_ready_event - when set, PTSE will generate event when the transmitter stopped transmitting after Tx_ready was set.\;Note: if both tx_not_ready and tx_ready are set, one toggle event may be received instead of 2 consecutive events of not ready --&gt; ready." access="RW" offset="0x0.26" size="0x0.2" />
	<field name="ee_tx_ready" descr="Event Enable for tx_ready_e.\;when bit is not set, tx_teady_e write value will be ignored" access="WO" offset="0x0.28" size="0x0.1" />
	<field name="an_disable_cap" descr="Auto Negotiation disable capability:\;0 - Device does not support AN disable\;1 - Device Supports  AN disable" access="RO" offset="0x0.29" size="0x0.1" />
	<field name="an_disable_admin" descr="Auto Negotiation disable:\;0 - Normal operation \;1 - Disable AN.\;Note: In Ethernet port, when Disabling AN, the &quot;eth_proto_admin&quot; bit mask must comply to single speed rate set.\;In IB port, when Disabling AN, the &quot;ib_proto_admin&quot; bit mask must comply to single speed rate set.\;It&apos;s recommended to validate the FEC override bits in PPLM when operating with AN. \;\;" access="RW" offset="0x0.30" size="0x0.1" />
	<field name="data_rate_oper" descr="Port data rate in resolution of 100 Mb/s (data_rate_oper * 100 Mb/s)\;Value 0x0 indicates this field is not supported.\;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="max_port_rate" descr="Port maxium data rate in resolution of 1 Gb/s (data_rate_oper * 1 Gb/s)\;Value 0x0 indicates this field is not supported.\;\;" access="RO" offset="0x4.16" size="0x0.12" />
	<field name="an_status" descr="Auto Negotiation status: \;0: Status_is_unavailable\;1: AN_completed_successfully \;2: AN_performed_but_failed\;3: AN_was_not_performed_link_is_up \;4: AN_was_not_performed_link_is_down" access="RO" enum="Status_is_unavailable=0x0,AN_completed_successfully=0x1,AN_performed_but_failed=0x2,AN_was_not_performed_link_is_up=0x3,AN_was_not_performed_link_is_down=0x4" offset="0x4.28" size="0x0.4" />
	<field name="ext_eth_proto_capability" descr="For HCA: See also PCAM.feature_cap_mask bit 13 for Extended Ethernet protocol support.\;Extended Ethernet port speed/protocols supported (bitmask):\;Bit 0: SGMII_100M\;Bit 1: 1000BASE-X / SGMII\;Bit 3: 5GBASE-R\;Bit 4: XFI / XAUI-1 // 10G\;Bit 5: XLAUI-4/XLPPI-4 // 40G \;Bit 6: 25GAUI-1/ 25GBASE-CR / KR \;Bit 7: 50GAUI-2 / LAUI-2/ 50GBASE-CR2/KR2 \;Bit 8: 50GAUI-1 /50GBASE-CR / KR\;Bit 9: CAUI-4 / 100GBASE-CR4 / KR4\;Bit 10: 100GAUI-2 / 100GBASE-CR2 / KR2 \;Bit 11: 100GAUI-1 / 100GBASE-CR / KR\;Bit 12: 200GAUI-4 / 200GBASE-CR4/KR4\;Bit 13: 200GAUI-2 / 200GBASE-CR2/KR2\;Bit 14: 200GAUI-1 / 200GBASE-CR1/KR1\;Bit 15: 400GAUI-8/ 400GBASE-CR8\;Bit 16: 400GAUI-4/ 400GBASE-CR4\;Bit 17: 400GAUI-2 / 400GBASE-CR2/KR2\;Bit 18: Reserved [internal] Placeholder for 400GAUI-1\;Bit 19: 800GAUI-8 / 800GBASE-CR8 / KR8\;Bit 20: 800GAUI-4 / 800GBASE-CR4/KR4\;Bit 23: 1.6TAUI-8 /1.6TBASE-CR8/KR8\;Bit 31: SGMII_10M\;Other - Reserved" access="RO" offset="0x8.0" size="0x4.0" />
	<field name="eth_proto_capability" descr="Ethernet port speed/protocols supported (bitmask)\;Bit 31 - 50GBase-KR2\;Bit 30 - 50GBase-CR2\;Bit 29 - 25GBase-SR\;Bit 28 - 25GBase-KR\;Bit 27 - 25GBase-CR\;Bit 26 - 10GBase-T \;Bit 25 - 1000Base-T\;Bit 24 - 100Base-TX\;Bit 23 - 100GBase LR4/ER4\;Bit 22 - 100GBase KR4\;Bit 21 - 100GBase SR4\;Bit 20 - 100GBase CR4\;Bit 18 - 50GBase-SR2\;Bit 16 - 40GBase LR4/ER4\;Bit 15 - 40GBase SR4\;Bit 14 - 10GBase ER/LR\;Bit 13 - 10GBase SR\;Bit 12 - 10GBase CR\;Bit 10 - 10Base-T\;Bit 9 - SGMII_100Base\;Bit 7 - 40GBase KR4\;Bit 6 - 40GBase CR4\;Bit 4 - 10GBase KR\;Bit 3 - 10GBase KX4\;Bit 2 - 10GBase-CX4\;Bit 1 - 1000Base KX\;Bit 0 - SGMII" access="RO" offset="0xC.0" size="0x4.0" />
	<field name="ib_proto_capability" descr="InfiniBand port speed supported (bitmask)\;Bit 0: SDR\;Bit 1: DDR\;Bit 2: QDR\;Bit 3: FDR10\;Bit 4: FDR\;Bit 5: EDR\;Bit 6: HDR\;Bit 7: NDR\;Bit 8: XDR" access="RO" enum="SDR=0x1,DDR=0x2,QDR=0x4,FDR10=0x8,FDR=0x10,EDR=0x20,HDR=0x40,NDR=0x80,XDR=0x100" offset="0x10.0" size="0x0.16" />
	<field name="ib_link_width_capability" descr="ib_link_width &lt;= ib_proto_capability\;Bit 0 - 1x\;Bit 1 - 2x\;Bit 2 - 4x\;" access="RO" offset="0x10.16" size="0x0.16" />
	<field name="ext_eth_proto_admin" descr="Ethernet port extended speed/protocols bitmask\;NOTE: This field and &quot;eth_proto_admin&quot; are mutual exclusive, meaning that only one of the field can be set on write command." access="RW" offset="0x14.0" size="0x4.0" />
	<field name="eth_proto_admin" descr="Ethernet port speed/protocols bitmask" access="RW" offset="0x18.0" size="0x4.0" />
	<field name="ib_proto_admin" descr="InfiniBand port speed bitmask" access="RW" offset="0x1C.0" size="0x0.16" />
	<field name="ib_link_width_admin" descr="InfiniBand port link width bitmask\;" access="RW" offset="0x1C.16" size="0x0.16" />
	<field name="ext_eth_proto_oper" descr="Ethernet port extended speed/protocols bitmask" access="RO" offset="0x20.0" size="0x4.0" />
	<field name="eth_proto_oper" descr="Ethernet port speed/protocols bitmask" access="RO" offset="0x24.0" size="0x4.0" />
	<field name="ib_proto_oper" descr="InfiniBand port speed bitmask" access="RO" offset="0x28.0" size="0x0.16" />
	<field name="ib_link_width_oper" descr="InfiniBand port link width bitmask\;" access="RO" offset="0x28.16" size="0x0.16" />
	<field name="connector_type" descr="Connector type indication\;0: No_connector_or_unknown \;1: PORT_NONE - None\;2: PORT_TP - Twisted Pair\;3: PORT_AUI - AUI\;4: PORT_BNC - BNC\;5: PORT_MII - MII\;6: PORT_FIBRE - FIBRE\;7: PORT_DA - Direct Attach Copper\;8: PORT_OTHER - Other" access="RO" enum="No_connector_or_unknown=0x0,PORT_NONE=0x1,PORT_TP=0x2,PORT_AUI=0x3,PORT_BNC=0x4,PORT_MII=0x5,PORT_FIBRE=0x6,PORT_DA=0x7,PORT_OTHER=0x8" offset="0x2C.0" size="0x0.4" />
	<field name="lane_rate_oper" descr="For active link, Indicates the lane data rate passed per physical lane including the overhead due to FEC.\;resolution of 10 Mb/s (lane_rate_oper * 10Mb/s)." access="RO" offset="0x2C.4" size="0x0.20" />
	<field name="xdr_2x_slow_active" descr="When set and link active, indicates link speed is xdr_2x slow." access="RO" offset="0x2C.24" size="0x0.1" />
	<field name="xdr_2x_slow_admin" descr="When set, along with ib protocol xdr_2x, XDR_2x slow will be allowed instead of xdr_2x.\;Note: in GB100, set by default only with ini and cannot be changed." access="RW" offset="0x2C.25" size="0x0.1" />
	<field name="force_lt_frames_admin" descr="Ethernet Force mode options when AN disable is set.\;0 - auto, keep normal operation\;1 - Do Force LT (KR Startup) flow\;2 - Do not do LT (KR Startup) flow\;\;Note: Ignored when an_disable_admin is not set\;In Ethernet port, when setting force LT flow, the &quot;eth_proto_ext_admin&quot; bit mask must comply to single speed rate set." access="RW" offset="0x2C.28" size="0x0.2" />
	<field name="force_lt_frames_cap" descr="0 - device does not support Force LT (KR Startup) flow\;1 - device supports Force LT (KR Startup) flow\;\;Note: Ignored when an_disable_admin is not set" access="RO" offset="0x2C.30" size="0x0.1" />
	<field name="xdr_2x_slow_cap" descr="capability for XDR_2x slow is support (200G)" access="RO" offset="0x2C.31" size="0x0.1" />
</node>

<node name="pude_reg_ext" descr="" size="0x10.0" >
	<field name="oper_status" descr="Port operational state:\;0001 - up\;0010 - down\;0100 - down by port failure (transitioned by the hardware)\;" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="admin_status" descr="Port administrative state (the desired state of the interface):\;0001 - up\;0010 - down by configuration\;0011 - up once - if the port goes up and then down, the operational status should go to &quot;down by port failure&quot; and can only go back up upon explicit command\;0100 - disabled by system \;0110 - sleep" access="RO" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="swid" descr="For HCA: must always be 0.\;Switch partition ID with which to associate the port.\;Switch partitions are numbered from 0 to 7 inclusively.\;Switch partition 254 indicates stacking ports.\;Switch partition 255 indicates all switch partitions.\;Note: While external ports uses unique local port numbers (and thus swid is redundant), router ports use the same local port number where swid is the only indication for the relevant port." access="INDEX" offset="0x0.24" size="0x0.8" />
	<field name="nmx_adminstate_status" descr="NVLink Port NMX AdminState current state:\;0: NA\;1: Up\;2: Down\;3: Diag\;" access="RO" enum="NA=0x0,Up=0x1,Down=0x2,Diag=0x3" offset="0x4.0" size="0x0.3" />
	<field name="physical_state_status" descr="IB Port Physical link state:\;0: N/A\;1: Sleep\;2: Polling\;3: Disabled\;4: PortConfigurationTraining\;5: LinkUp\;6: LinkErrorRecovery\;All others reserved\;LinkUp for Ethernet link refers to PhyUp state where local side is ready, but not necessarily that peer side is also ready.\;" access="RO" enum="N_A=0x0,Sleep=0x1,Polling=0x2,Disabled=0x3,PortConfigurationTraining=0x4,LinkUp=0x5,LinkErrorRecovery=0x6" offset="0x4.4" size="0x0.4" />
	<field name="logical_state_status" descr="IB or NVLink Port Logical link state:\;0: N/A\;1: Down\;2: Init\;3: Arm\;4: Active" access="RO" offset="0x4.16" size="0x0.3" />
	<field name="local_reason_opcode" descr="Opcode of link down reason for local\;0: No_link_down_indication\;1: Unknown_reason\;2: Hi_BER\;3: Block_Lock_loss\;4: Alignment_loss\;5: FEC_sync_loss\;6: PLL_lock_loss\;7: FIFO_overflow\;8: false_SKIP_condition\;9: Minor_Error_threshold_exceeded\;10: Physical_layer_retransmission_timeout\;11: Heartbeat_errors\;12: Link_Layer_credit_monitoring_watchdog\;13: Link_Layer_integrity_threshold_exceeded\;14: Link_Layer_buffer_overrun\;15: Down_by_outband_command_with_healthy_link\;16: Down_by_outband_command_for_link_with_hi_ber\;17: Down_by_inband_command_with_healthy_link\;18: Down_by_inband_command_for_link_with_hi_ber\;19: Down_by_verification_GW\;20: Received_Remote_Fault \;21: Received_TS1\;22: Down_by_management_command\;23: Cable_was_unplugged\;24: Cable_access_issue \;25: Cable_Thermal_shutdown \;26: Current_issue \;27: Power_budget\;28: Fast_recovery_raw_ber\;29: Fast_recovery_effective_ber\;30: Fast_recovery_symbol_ber\;31: Fast_recovery_credit_watchdog\;32: Peer_side_down_to_sleep_state\;33: Peer_side_down_to_disable_state\;34: Peer_side_down_to_disable_and_port_lock\;35: Peer_side_down_due_to_thermal_event\;36: Peer_side_down_due_to_force_event\;37: Peer_side_down_due_to_reset_event\;38: Reset_no_power_cycle\;39: Fast_recovery_tx_plr_trigger\;40: Down_due_to_HW_force_event\;41: Down_due_to_thermal_event\;42: L1_exit_failure\;43: too_many_link_error_recoveries\;44: Down_due_to_contain_mode\;45: BW_loss_threshold_exceeded\;46: ELS_laser_fault\;47: Hi_SER" access="RO" enum="No_link_down_indication=0x0,Unknown_reason=0x1,Hi_BER=0x2,Block_Lock_loss=0x3,Alignment_loss=0x4,FEC_sync_loss=0x5,PLL_lock_loss=0x6,FIFO_overflow=0x7,false_SKIP_condition=0x8,Minor_Error_threshold_exceeded=0x9,Physical_layer_retransmission_timeout=0xa,Heartbeat_errors=0xb,Link_Layer_credit_monitoring_watchdog=0xc,Link_Layer_integrity_threshold_exceeded=0xd,Link_Layer_buffer_overrun=0xe,Down_by_outband_command_with_healthy_link=0xf,Down_by_outband_command_for_link_with_hi_ber=0x10,Down_by_inband_command_with_healthy_link=0x11,Down_by_inband_command_for_link_with_hi_ber=0x12,Down_by_verification_GW=0x13,Received_Remote_Fault=0x14,Received_TS1=0x15,Down_by_management_command=0x16,Cable_was_unplugged=0x17,Cable_access_issue=0x18,Cable_Thermal_shutdown=0x19,Current_issue=0x1a,Power_budget=0x1b,Fast_recovery_raw_ber=0x1c,Fast_recovery_effective_ber=0x1d,Fast_recovery_symbol_ber=0x1e,Fast_recovery_credit_watchdog=0x1f,Peer_side_down_to_sleep_state=0x20,Peer_side_down_to_disable_state=0x21,Peer_side_down_to_disable_and_port_lock=0x22,Peer_side_down_due_to_thermal_event=0x23,Peer_side_down_due_to_force_event=0x24,Peer_side_down_due_to_reset_event=0x25,Reset_no_power_cycle=0x26,Fast_recovery_tx_plr_trigger=0x27,Down_due_to_HW_force_event=0x28,Down_due_to_thermal_event=0x29,L1_exit_failure=0x2a,too_many_link_error_recoveries=0x2b,Down_due_to_contain_mode=0x2c,BW_loss_threshold_exceeded=0x2d,ELS_laser_fault=0x2e,Hi_SER=0x2f" offset="0x4.24" size="0x0.8" />
</node>

<node name="pvlc_reg_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port number" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="vl_hw_cap" descr="Virtual Lanes supported on this port.\;0 - Reserved\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14" access="RO" offset="0x4.0" size="0x0.4" />
	<field name="vl_admin" descr="Virtual Lanes enabled by the local admin on this port.\;0: No change; valid only on Set()\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14\;" access="RW" offset="0x8.0" size="0x0.4" />
	<field name="vl_operational" descr="Operational VLs as configured by the SM on this port:\;0: No change; valid only on Set()\;1: VL0\;2: VL0, VL1\;4: VL0 - VL3\;\;8: VL0 - VL7\;15: VL0 - VL14\;Changing vl_operational in certain PortStates may cause in flow control update errors which may initiate Link/PHY retraining.\;vl_operational value is valid only when link state is UP." access="RO" offset="0xC.0" size="0x0.4" />
</node>

<node name="remote_span_ib_local_ud_ext" descr="" size="0x4c.0" >
	<field name="dlid" descr="Destination LID. \;Note that when dpa=0 the analyzer port is configured by the system_port field and not by forwarding the packet based on the dlid field." access="RW" offset="0x0.0" size="0x0.16" />
	<field name="dpa" descr="Dynamic port analyzer. When set to dynamic mode, the analyzer port is set based on the forwarding information for the {swid, dlid} on private-LFT 0 instead of the system_port field. In static mode, the packet is transmitted to the configured system_port regardless of the forwarding database.\;0: static analyzer port\;1: dynamic analyzer port" access="RW" offset="0x0.16" size="0x0.2" />
	<field name="sl" descr="Service Level" access="RW" offset="0x0.20" size="0x0.4" />
	<field name="we" descr="Write enable:\;0: write all fields\;1: write only psn_init_val" access="WO" offset="0x0.24" size="0x0.8" />
	<field name="slid" descr="Source LID (LID of the sending device)" access="RW" offset="0x4.0" size="0x0.16" />
	<field name="version" descr="Remote SPAN InfiniBand encapsulation header version\;1: V1 - Mirror Header Version 1\;2: V2 - Mirror Header Version 2\;" access="RW" offset="0x4.20" size="0x0.4" />
	<field name="swid" descr="Switch partition ID\;Reserved when dpa = static analyzer port\;Reserved when mngr_type = local port manager\;Switch partition ID is used for dynamic analyzer port, to set the analyzer port based on the desired forwarding table (the one that belong to the swid)." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="vl" descr="Virtual Lane on which the mirrored packet is queued.\;Mirrored packets cannot be queued on VL-15." access="RW" offset="0xC.0" size="0x0.4" />
	<field name="pkey" descr="BTH PKey" access="RW" offset="0x38.0" size="0x0.16" />
	<field name="m" descr="BTH m" access="RW" offset="0x38.22" size="0x0.1" />
	<field name="se" descr="BTH se" access="RW" offset="0x38.23" size="0x0.1" />
	<field name="dest_qp" descr="BTH dest QP" access="RW" offset="0x3C.0" size="0x0.24" />
	<field name="psn_init_val" descr="BTH packet sequence number initial value\;Note: when reading, HW will reveal the current packet sequence number" access="RW" offset="0x40.0" size="0x0.24" />
	<field name="ar" descr="BTH MLNX adaptive routing enable flag" access="RW" offset="0x40.30" size="0x0.1" />
	<field name="qkey" descr="DETH QKey" access="RW" offset="0x44.0" size="0x4.0" />
	<field name="src_qp" descr="DETH source QP" access="RW" offset="0x48.0" size="0x0.24" />
</node>

<node name="resource_dump_ext" descr="" size="0xc8.0" >
	<field name="segment_type" descr="See Resource Dump section in the Adapters PRM." access="INDEX" offset="0x0.0" size="0x0.16" />
	<field name="seq_num" descr="Sequence number. 0 on first call of dump and incremented on each more dump." access="INDEX" offset="0x0.16" size="0x0.4" />
	<field name="vhca_id_valid" descr="If set, then vhca_id field is valid. Otherwise dump resources on my vhca_id.\;Not supported in Switch." access="WO" offset="0x0.29" size="0x0.1" />
	<field name="inline_dump" descr="If set, data is dumped in the register in inline_data field. otherwise dump to mkey.\;Supports only inline dump = 1" access="OP" offset="0x0.30" size="0x0.1" />
	<field name="more_dump" descr="If set, the device has additional information that has not been dumped yet." access="RO" offset="0x0.31" size="0x0.1" />
	<field name="vhca_id" descr="vhca_id where the resource is allocated.\;Not supported in Switch." access="WO" offset="0x4.0" size="0x0.16" />
	<field name="index1" descr="First object index to be dumped when supported by the object.\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1." access="INDEX" offset="0x8.0" size="0x4.0" />
	<field name="index2" descr="Second object index to be dumped when supported by the object.\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1." access="INDEX" offset="0xC.0" size="0x4.0" />
	<field name="num_of_obj2" descr="The amount of objects to dump starting for index 2.\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. \;Range is 0..0xfff0. When the segment&apos;s num_of_obj2_supports_all is set, the special value of 0xffff represents &quot;all&quot;. When the segment&apos;s num_of_objx_supports_active is set, the special value of 0xfffe represents &quot;active&quot;. The  value of 0x0 and 0x1 are allowed even if the supported_num_of_obj2 is &quot;0&quot;." access="INDEX" offset="0x10.0" size="0x0.16" />
	<field name="num_of_obj1" descr="The amount of objects to dump starting for index 1\;SW shall read this field upon command done and shall provide it on the next call in case dump_more==1. \;Range is 0..0xfff0. When the segment&apos;s num_of_obj1_supports_all is set, the special value of 0xffff represents &quot;all&quot;. When the segment&apos;s num_of_objx_supports_active is set, the special value of 0xfffe represents &quot;active&quot;. The value of 0x0 and 0x1 are allowed even if the supported_num_of_obj1 is &quot;0&quot;." access="INDEX" offset="0x10.16" size="0x0.16" />
	<field name="device_opaque" descr="An opaque provided by the device. SW shall read the device_opaque upon command done and shall provide it on the next call in case dump_more==1. On first call, device_opaque shall be 0.\;" subnode="uint64" access="INDEX" offset="0x18.0" size="0x8.0" />
	<field name="mkey" descr="Memory key to dump to. \;Valid when inline_dump==0.\;Not supported in Switch." access="WO" offset="0x20.0" size="0x4.0" />
	<field name="size" descr="In write, the size of maximum allocated buffer that the device can use.\;In read, the actual written size.\;In granularity of Bytes.\;Not supported in Switch." access="RO" offset="0x24.0" size="0x4.0" />
	<field name="address" descr="VA address (absolute address) of memory where to start dumping. \;Valid when inline_dump==0.\;Not supported in Switch." subnode="uint64" access="WO" offset="0x28.0" size="0x8.0" />
	<field name="inline_data" descr="Data that is dumped in case of inline mode.\;Valid when inline_dump==1." access="RO" high_bound="37" low_bound="0" offset="0x30.0" size="0x98.0" />
</node>

<node name="riscv_exception_ext" descr="" size="0x18.0" >
	<field name="mepc" descr="Machine Exception Program Counter (mepc).\;" subnode="uint64" access="RO" offset="0x0.0" size="0x8.0" />
	<field name="mcause" descr="Machine Cause Register (mcause).RiscV exception code." subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
	<field name="mtval" descr="Machine Trap Value (mtval) Register.Holds exception-specific information to assist software in handling the trap." subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="rom_version_ext" descr="" size="0x4.0" >
	<field name="build" descr="Build version" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="minor" descr="Minor version" access="RO" offset="0x0.16" size="0x0.8" />
	<field name="major" descr="Major version" access="RO" offset="0x0.24" size="0x0.8" />
</node>

<node name="sllm_5nm_ext" descr="" size="0x2c.0" >
	<field name="peq_cap" descr="When set, peq_interval_period, peq_interval_period_oper field has valid value and is configurable" access="RW" offset="0x0.0" size="0x0.1" />
	<field name="peq_interval_period" descr="Admin Interval period between periodic EQs is 10uS granularity.\;for get, returns value of PEQ interval.\;All ports of the same physical cluster must be down in order to set the command\;0: FW default" access="RW" offset="0x4.0" size="0x0.12" />
	<field name="peq_interval_period_oper" descr="operational Interval period between periodic EQs after negotiation agreement.\;10uS granularity." access="RO" offset="0x8.0" size="0x0.12" />
</node>

<node name="sllm_reg_ext" descr="" size="0x30.0" >
	<field name="c_db" descr="copy to FW Data-Base." access="OP" offset="0x0.0" size="0x0.1" />
	<field name="br_lanes" descr="When set, configuration will be applied to all port lanes" access="WO" offset="0x0.1" size="0x0.1" />
	<field name="br_lanes_cap" descr="When set, br_lanes config is valid. otherwise, field ignores config" access="RO" offset="0x0.2" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)\;4: USR_Main\;5: USR_Tile\;\;" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3,USR_Main=0x4,USR_Tile=0x5" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="3: prod_16nm\;4: prod_7nm\;5: prod_5nm\;6: prod_3nm" access="RO" enum="prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,prod_3nm=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - invalid\;1 - valid" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="Table  909, &quot;SLLM - SerDes Lane Link Maintenance Register Layout for 5nm and 3nm,&quot; on page  1000" subnode="sllm_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x4.0" size="0x2c.0" />
</node>

<node name="sllm_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x2c.0" >
	<field name="sllm_5nm_ext" descr="" subnode="sllm_5nm_ext" condition="($(parent).port_type == Network_Port) AND (($(parent).version == prod_5nm) OR $(parent).version == prod_3nm)" offset="0x0.0" size="0x2c.0" />
</node>

<node name="slrg_16nm_ext" descr="" size="0x24.0" >
	<field name="grade_lane_speed" descr="The lane speed on which the grade was measured:\;0 - SDR / PCIe Gen 1\;1 - DDR / PCIe Gen 2\;2 - QDR / PCIe Gen 3\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / PCIe Gen 4\;5 - EDR (25GE / 50GE / 100GE) / PCIe Gen 5\;6 - HDR (50GE / 200GE / 400GE)\;7- 9 - reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13 - 15 - reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="grade" descr="The grade that the lane received based on a specific configuration.\;" access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg_up" descr="Voltage offset from eye center to the negative side of the upper eye. Only applicable for PAM4 signal." access="RO" offset="0x8.0" size="0x0.16" />
	<field name="height_eo_pos_up" descr="Voltage offset from eye center to the positive side of the upper eye.\;Only applicable for PAM4 signal." access="RO" offset="0x8.16" size="0x0.16" />
	<field name="height_eo_pos_mid" descr="Voltage offset from eye center to the positive side of the middle eye." access="RO" offset="0xC.0" size="0x0.16" />
	<field name="phase_eo_neg_up" descr="The offset from the eye center to the negative (left) side of the upper eye. Only applicable for PAM4 signal." access="RO" offset="0xC.16" size="0x0.8" />
	<field name="phase_eo_pos_up" descr="The offset from the eye center to the positive (right) side of the upper eye. Only applicable for PAM4 signal." access="RO" offset="0xC.24" size="0x0.8" />
	<field name="phase_eo_neg_mid" descr="The offset from the eye center to the negative (left) side of the middle eye." access="RO" offset="0x10.0" size="0x0.8" />
	<field name="phase_eo_pos_mid" descr="The offset from the eye center to the positive (right) side of the middle eye." access="RO" offset="0x10.8" size="0x0.8" />
	<field name="height_eo_neg_mid" descr="Voltage offset from eye center to the negative side of the middle eye." access="RO" offset="0x10.16" size="0x0.16" />
	<field name="height_eo_neg_low" descr="Voltage offset from eye center to the negative side of the lower eye. Only applicable for PAM4 signal." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos_low" descr="Voltage offset from eye center to the positive side of the lower eye. Only applicable for PAM4 signal." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg_low" descr="The offset from the eye center to the negative (left) side of the lower eye. Only applicable for PAM4 signal." access="RO" offset="0x18.16" size="0x0.8" />
	<field name="phase_eo_pos_low" descr="The offset from the eye center to the positive (right) side of the lower eye. Only applicable for PAM4 signal." access="RO" offset="0x18.24" size="0x0.8" />
	<field name="up_eye_grade" descr="upper eye grade" access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="mid_eye_grade" descr="middle eye grade" access="RO" offset="0x1C.16" size="0x0.16" />
	<field name="dn_eye_grade" descr="lower eye grade" access="RO" offset="0x20.0" size="0x0.16" />
</node>

<node name="slrg_3nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurement" descr="Bitmask for measurement activation\;Bit 0 - Upper eye\;Bit 1 - Middle eye\;Bit 2 - Lower eye\;Bit 3- Composite eye\;Note: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.\;valid only when SLRG.status is &apos;1&apos;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_mode" descr="fom mode:\;FOM eye mode to search\;0x0: FOM_MODE_EYE_OPEN\;0x1: FOM_MODE_EYEO_SNR\;0x2: FOM_MODE_NORM_SNR\;0x3: FOM_MODE_EYE_LVLN\;0x4: FOM_MODE_EYE_LVLP\;0x5: FOM_MODE_THRES_NERR\;0x6: FOM_MODE_CDR_NERR\;0x7: FOM_MODE_CSDET_NERR\;0x8: FOM_MODE_MLSE_NERR\;0x9: FOM_MODE_SFEC_NERR\;\;\;" access="RW" enum="FOM_MODE_EYE_OPEN=0x0,FOM_MODE_EYEO_SNR=0x1,FOM_MODE_NORM_SNR=0x2,FOM_MODE_EYE_LVLN=0x3,FOM_MODE_EYE_LVLP=0x4,FOM_MODE_THRES_NERR=0x5,FOM_MODE_CDR_NERR=0x6,FOM_MODE_CSDET_NERR=0x7,FOM_MODE_MLSE_NERR=0x8,FOM_MODE_SFEC_NERR=0x9" offset="0x4.16" size="0x0.4" />
	<field name="fom_meas_type_read" descr="Indicate if the fom_measurement is of PAM4 or NRZ data\;\;0 - PAM4 (Upper, mid, low eye)\;1 - NRZ (Composite eye)" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.\;valid only if fom_measurement bit &apos;0&apos; is set" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.\;valid only if fom_measurement bit &apos;3&apos; is set" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.\;valid only if fom_measurement bit &apos;2&apos; is set" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.\;valid only if fom_measurement bit &apos;1&apos; is set" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="slrg_40nm_28nm_ext" descr="" size="0x24.0" >
	<field name="grade_lane_speed" descr="The lane speed on which the grade was measured:\;0 - SDR\;1 - DDR\;2 - QDR\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE)\;5 - EDR (25GE / 50GE / 100GE)\;6 - 9 - reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13 - 15 - reserved" access="RO" offset="0x0.0" size="0x0.4" />
	<field name="time_to_link_up" descr="The time that took took to bring up the link in msec." access="RO" offset="0x0.16" size="0x0.16" />
	<field name="grade" descr="" access="RO" offset="0x4.0" size="0x0.24" />
	<field name="grade_version" descr="" access="RO" offset="0x4.24" size="0x0.8" />
	<field name="height_eo_neg" descr="Voltage offset from eye center to the negative side." access="RO" offset="0x14.0" size="0x0.16" />
	<field name="height_eo_pos" descr="Voltage offset from eye center to the positive side." access="RO" offset="0x14.16" size="0x0.16" />
	<field name="phase_eo_neg" descr="The offset from the eye center to the negative side." access="RO" offset="0x1C.0" size="0x0.16" />
	<field name="phase_eo_pos" descr="The offset from the eye center to the positive side." access="RO" offset="0x1C.16" size="0x0.16" />
</node>

<node name="slrg_5nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurement" descr="Bitmask for measurement activation\;Bit 0 - Upper eye\;Bit 1 - Middle eye\;Bit 2 - Lower eye\;Bit 3- Composite eye\;Note: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.\;valid only when SLRG.status is &apos;1&apos;" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_mode" descr="fom mode:\;FOM eye mode to search\;0x0: FOM_MODE_EYE_OPEN\;0x1: FOM_MODE_EYEO_SNR\;0x2: FOM_MODE_NORM_SNR\;0x3: FOM_MODE_EYE_LVLN\;0x4: FOM_MODE_EYE_LVLP\;0x5: FOM_MODE_THRES_NERR\;0x6: FOM_MODE_CDR_NERR\;0x7: FOM_MODE_CSDET_NERR\;0x8: FOM_MODE_MLSE_NERR\;0x9: FOM_MODE_SFEC_NERR\;\;\;" access="RW" enum="FOM_MODE_EYE_OPEN=0x0,FOM_MODE_EYEO_SNR=0x1,FOM_MODE_NORM_SNR=0x2,FOM_MODE_EYE_LVLN=0x3,FOM_MODE_EYE_LVLP=0x4,FOM_MODE_THRES_NERR=0x5,FOM_MODE_CDR_NERR=0x6,FOM_MODE_CSDET_NERR=0x7,FOM_MODE_MLSE_NERR=0x8,FOM_MODE_SFEC_NERR=0x9" offset="0x4.16" size="0x0.4" />
	<field name="fom_meas_type_read" descr="Indicate if the fom_measurement is of PAM4 or NRZ data\;\;0 - PAM4 (Upper, mid, low eye)\;1 - NRZ (Composite eye)" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.\;valid only if fom_measurement bit &apos;0&apos; is set" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.\;valid only if fom_measurement bit &apos;3&apos; is set" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.\;valid only if fom_measurement bit &apos;2&apos; is set" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.\;valid only if fom_measurement bit &apos;1&apos; is set" access="RO" offset="0xC.16" size="0x0.16" />
</node>

<node name="slrg_7nm_ext" descr="" size="0x18.0" >
	<field name="fom_measurement" descr="Bitmask for measurement activation\;Bit 0 - Upper eye\;Bit 1 - Middle eye\;Bit 2 - Lower eye\;Bit 3- Composite eye\;Note: NRZ only Bit 3 is valid" access="OP" offset="0x0.0" size="0x0.4" />
	<field name="initial_fom" descr="measured EOM status after FEQ.\;valid only when SLRG.status is &apos;1&apos;" access="RO" offset="0x4.0" size="0x0.8" />
	<field name="fom_mode" descr="fom mode:\;FOM eye mode to search\;0x0: FOM_MODE_EYEC\;0x1: FOM_MODE_EYEO\;0x2: FOM_MODE_EYEM\;0x3: FOM_MODE_BER\;0x4: FOM_MODE_EYEC_VN\;0x5: FOM_MODE_EYEC_VP\;0x6: FOM_MODE_EYEM_VN\;0x7: FOM_MODE_EYEM_VP\;\;" access="RW" enum="FOM_MODE_EYEC=0x0,FOM_MODE_EYEO=0x1,FOM_MODE_EYEM=0x2,FOM_MODE_BER=0x3,FOM_MODE_EYEC_VN=0x4,FOM_MODE_EYEC_VP=0x5,FOM_MODE_EYEM_VN=0x6,FOM_MODE_EYEM_VP=0x7" offset="0x4.16" size="0x0.3" />
	<field name="fom_meas_type_read" descr="Indicate if the fom_measurement is of PAM4 or NRZ data\;\;0 - PAM4 (Upper, mid, low eye)\;1 - NRZ (Composite eye)" access="RO" offset="0x4.31" size="0x0.1" />
	<field name="lower_eye" descr="last measured EOM-FOM status of lower eye.\;valid only if fom_measurement bit &apos;2&apos; is set" access="RO" offset="0x8.0" size="0x0.8" />
	<field name="mid_eye" descr="last measured EOM-FOM status of middle eye.\;valid only if fom_measurement bit &apos;1&apos; is set" access="RO" offset="0x8.8" size="0x0.8" />
	<field name="upper_eye" descr="last measured EOM-FOM status of upper eye.\;valid only if fom_measurement bit &apos;0&apos; is set" access="RO" offset="0x8.16" size="0x0.8" />
	<field name="last_fom" descr="last measured EOM-FOM status of composite eye.\;valid only if fom_measurement bit &apos;3&apos; is set" access="RO" offset="0x8.24" size="0x0.8" />
</node>

<node name="slrg_all_lanes_5nm_ext" descr="" size="0x14.0" >
	<field name="fom_mode" descr="FOM type measurement.\;0: SNR - bit scale of 1/256 dB.\;The SNR value represents the electrical signal-to-noise ratio on an optical lane, and is defined as the minimum of the three individual eye SNR values." access="OP" offset="0x0.0" size="0x0.4" />
	<field name="fom_lane1" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x4.0" size="0x0.16" />
	<field name="fom_lane0" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x4.16" size="0x0.16" />
	<field name="fom_lane3" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x8.0" size="0x0.16" />
	<field name="fom_lane2" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x8.16" size="0x0.16" />
	<field name="fom_lane5" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0xC.0" size="0x0.16" />
	<field name="fom_lane4" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0xC.16" size="0x0.16" />
	<field name="fom_lane7" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x10.0" size="0x0.16" />
	<field name="fom_lane6" descr="FOM value on the media lane &lt;i&gt; According to fom_mode value" access="RO" offset="0x10.16" size="0x0.16" />
</node>

<node name="slrg_reg_ext" descr="" size="0x28.0" >
	<field name="all_lanes" descr="Set 1 for all lanes measurement page. When set, ignore the value under the local_port field. The measurement should be conducted on all active lanes. For Retimer/Gearbox measured lanes side is chosen based on port_type.\;Supported if PCAM.feature_cap_mask bit 91 is set. \;Relevant only for 5nm\;0: per_lane_measurement\;1: all_lane_measurement" access="INDEX" enum="per_lane_measurement=0x0,all_lane_measurement=0x1" offset="0x0.1" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)\;\;" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.12" size="0x0.2" />
	<field name="pnat" descr="Port number access type. \;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number.\;" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm\;1: prod_28nm\;3: prod_16nm\;4: prod_7nm\;5: prod_5nm\;6: prod_3nm" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5,prod_3nm=0x6" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="0 - Invalid\;1 - Valid\;" access="RO" offset="0x0.28" size="0x0.4" />
	<field name="page_data" descr="Table 693, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 40nm and 28nm,&quot; on page 751\;Table 695, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 16nm,&quot; on page 753\;Table 697, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 7nm,&quot; on page 755\;Table 699, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 5nm,&quot; on page 757\;Table 707, &quot;SLRG all lanes FOM for 5nm- Layout,&quot; on page 761\;Table 709, &quot;SLRG - SerDes Lane Receive Grade Register Layout for 3nm,&quot; on page 762" subnode="slrg_reg_page_data_auto_ext" access="RO" condition="$(parent).all_lanes" offset="0x4.0" size="0x24.0" />
</node>

<node name="slrg_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x24.0" >
	<field name="slrg_16nm_ext" descr="" subnode="slrg_16nm_ext" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_16nm))" offset="0x0.0" size="0x24.0" />
	<field name="slrg_3nm_ext" descr="" subnode="slrg_3nm_ext" condition="(($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_40nm_28nm_ext" descr="" subnode="slrg_40nm_28nm_ext" condition="($(parent).port_type == Network_Port AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm))" offset="0x0.0" size="0x24.0" />
	<field name="slrg_5nm_ext" descr="" subnode="slrg_5nm_ext" condition="(($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_7nm_ext" descr="" subnode="slrg_7nm_ext" condition="(($(parent).port_type == Network_Port | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_7nm))" offset="0x0.0" size="0x18.0" />
	<field name="slrg_all_lanes_5nm_ext" descr="" subnode="slrg_all_lanes_5nm_ext" condition="(($(parent).port_type == Network_Port || $(parent).port_type == NearEnd_Port  || $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm AND $(parent).all_lanes == all_lane_measurement))" offset="0x0.0" size="0x14.0" />
</node>

<node name="sltp_16nm_ext" descr="" size="0x48.0" >
	<field name="post_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="main_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="pre_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="pre_2_tap" descr="Value of each tap is between -96 to 96\;\;NOTE: The total sum of all absolute taps values should be 96 or smaller.\;" access="RW" offset="0x4.24" size="0x0.8" />
	<field name="ob_alev_out" descr="Output common mode. Values can be set in the range of (0-30)" access="RW" offset="0x8.0" size="0x0.5" />
	<field name="ob_amp" descr="Output amplitude. Values can be set in the range of (10-100)." access="RW" offset="0x8.8" size="0x0.7" />
	<field name="ob_m2lp" descr="MSB to LSB proportion. \;Values can be set between -10 to 50. \;\;MSB emphasis achieved when value is between -10 to -1 \;LSB emphasis achieved when value is between 1 to 50. \;When set to 0 - equal proportion." access="RW" offset="0x8.25" size="0x0.7" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;0: configuration_warning - taps values can&apos;t be set to SerDes due to internal limitations. Actual TX configuration is modify internally with the same sum of taps weight.\;11: Illegal_ob_combination - ob_m2lp, ob_amp and ob_alev is in legal range each, but the total combination can&apos;t be set to SerDes due to internal limitations, the Set command is ignored.\;12: Illegal_ob_m2lp\;13: Illegal_ob_amp\;14: Illegal_ob_alev_out\;15: Illegal_taps\;\;Bit 12-0 - Reserved /Unknown" access="RO" enum="configuration_warning=0x0,Illegal_ob_combination=0xb,Illegal_ob_m2lp=0xc,Illegal_ob_amp=0xd,Illegal_ob_alev_out=0xe,Illegal_taps=0xf" offset="0xC.16" size="0x0.16" />
	<field name="regp_bfm1n" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.0" size="0x0.8" />
	<field name="regn_bfm1p" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.8" size="0x0.8" />
	<field name="obnlev" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.16" size="0x0.8" />
	<field name="obplev" descr="Values can be set in the range of (0-200)." access="RW" offset="0x10.24" size="0x0.8" />
</node>

<node name="sltp_28nm_40nm_ext" descr="" size="0x48.0" >
	<field name="ob_tap2" descr="\;" access="RW" offset="0x4.0" size="0x0.8" />
	<field name="ob_tap1" descr="\;" access="RW" offset="0x4.8" size="0x0.8" />
	<field name="ob_tap0" descr="\;" access="RW" offset="0x4.16" size="0x0.8" />
	<field name="polarity" descr="Tx lane polarity" access="RW" offset="0x4.24" size="0x0.1" />
	<field name="ob_bias" descr="" access="RW" offset="0x8.0" size="0x0.8" />
	<field name="ob_reg" descr="(ref_txcml100_reg)" access="RW" offset="0x8.8" size="0x0.8" />
	<field name="ob_preemp_mode" descr="Concatenation of taps polarity + preemp_sel" access="RW" offset="0x8.16" size="0x0.4" />
	<field name="ob_leva" descr="" access="RW" offset="0x8.20" size="0x0.4" />
	<field name="ob_bad_stat" descr="Bitmask for bad SET status:\;Bit 0 - Illegal ob_bais value\;Bit 1 - Illegal ob taps polarity (distance between taps)" access="RO" offset="0xC.29" size="0x0.2" />
	<field name="ob_norm" descr="OB Normalization status:\;0 - No Normalization was done\;1 - Normalization performed" access="RO" offset="0xC.31" size="0x0.1" />
</node>

<node name="sltp_5nm_ext" descr="" size="0x48.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0: tap0_is_out_of_range\;Bit 1: tap1_is_out_of_range\;Bit 2: tap2_is_out_of_range\;Bit 3: tap3_is_out_of_range\;Bit 4: tap4_is_out_of_range\;Bit 5: tap5_is_out_of_range\;Bit 6: tap6_is_out_of_range\;Bit 7: tap7_is_out_of_range\;Bit 8: tap8_is_out_of_range\;Bit 9: tap9_is_out_of_range\;Bit 10: tap10_is_out_of_range\;Bit 11: tap11_is_out_of_range\;Bit 9: sum_of_taps_is_out_of_range" access="RO" enum="tap0_is_out_of_range=0x1,tap1_is_out_of_range=0x2,tap2_is_out_of_range=0x4,tap3_is_out_of_range=0x8,tap4_is_out_of_range=0x10,tap5_is_out_of_range=0x20,tap6_is_out_of_range=0x40,tap7_is_out_of_range=0x80,tap8_is_out_of_range=0x100,tap9_is_out_of_range=0x200,tap10_is_out_of_range=0x400,tap11_is_out_of_range=0x800,sum_of_taps_is_out_of_range=0x200" offset="0x0.0" size="0x0.16" />
	<field name="lt_preset_sel" descr="Valid only when lt_preset_sel_cap is set, otherwise ignored\;0: no_preset_selected - changes Tx DB according to cable\;1-7: LT_index_preset_select - Tx will get / set LT preset" access="RW" offset="0x0.24" size="0x0.3" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.\;for when direct drive module connected:\;0 - db to override is for Did vs Did\;1 - db to override if for Did vs retimed module\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="lt_preset_sel_cap" descr="When set, lt_preset_sel field is valid." access="RO" offset="0x0.30" size="0x0.1" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.\;When set, Tx DB will not be written into HW on linkup phase.\;When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="tap0" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.0" size="0x0.8" />
	<field name="tap1" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.8" size="0x0.8" />
	<field name="tap2" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.16" size="0x0.8" />
	<field name="tap3" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.24" size="0x0.8" />
	<field name="tap4" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.0" size="0x0.8" />
	<field name="tap5" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.8" size="0x0.8" />
	<field name="tap6" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.16" size="0x0.8" />
	<field name="tap7" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x8.24" size="0x0.8" />
	<field name="tap8" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.0" size="0x0.8" />
	<field name="tap9" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.8" size="0x0.8" />
	<field name="tap10" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.16" size="0x0.8" />
	<field name="tap11" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Taps value must be under the following rules:\;\;taps [0-1, 6-11] valid ranges are [-8,8]\;And Also:\;|tap0| + | tap1| &lt;8\;|tap6| + | tap7| + | tap8|&lt;8\;|tap9| + | tap10| + | tap11| &lt;8\;taps [2-5] valid ranges are [-63, 63]\;\;For PAM4 links need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63. \;For NRZ links must guarantee sum|c(i)| = 63\;\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0xC.24" size="0x0.8" />
	<field name="drv_amp" descr="High speed output driver amplitude settings, default = 6&quot;d63.\;Amplitude scaling = (drv_amp+1)/64\;\;It should be noted there are two limitations for changing drv_amp in 5nm:\;1) The value can be configured if only taps 2-5 are being used. If any other taps are being used (0-1,6-11), meaning they have a non-zero value, drv_amp will be ignored, and set to default value.\;2) Setting to any value other then the default one will reduce the valid ranges of taps 2-5. The maximum valid range is [-63,63] when drv_amp = 6&quot;d63. If drv_amp=X, then the valid range will be [-X,X]." access="RW" offset="0x10.26" size="0x0.6" />
</node>

<node name="sltp_7nm_ext" descr="" size="0x48.0" >
	<field name="fir_pre2" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3),\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x0.0" size="0x0.8" />
	<field name="fir_pre3" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3),\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x0.8" size="0x0.8" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0: pre3_is_out_of_range\;Bit 1: pre2_is_out_of_range\;Bit 2: pre1_is_out_of_range\;Bit 3: main_tap_is_out_of_range\;Bit 4: post1_is_out_of_range\;Bit 5: sum_of_taps_is_out_of_range\;Bit 6: taps_not_alinged_with_speed" access="RO" enum="pre3_is_out_of_range=0x1,pre2_is_out_of_range=0x2,pre1_is_out_of_range=0x4,main_tap_is_out_of_range=0x8,post1_is_out_of_range=0x10,sum_of_taps_is_out_of_range=0x20,taps_not_alinged_with_speed=0x40" offset="0x0.16" size="0x0.8" />
	<field name="drv_amp" descr="High speed output driver amplitude settings, default = 6&quot;d63.\; amplitude scaling = (AMP+1) / 64" access="RW" offset="0x0.24" size="0x0.6" />
	<field name="fir_post1" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3),\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.8" size="0x0.8" />
	<field name="fir_main" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3),\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.16" size="0x0.8" />
	<field name="fir_pre1" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;for 100G per lane 5 taps, \;for 50G per lane 4 taps are used (no pre3),\;or 25G per lane 3 taps are used (no pre3,pre2)\;Valid values for taps:\;fir_main [34,63]\;fir_pre1 [-23,0]\;fir_pre2 [0,8]\;fir_pre3 [-5,0]\;fir_post1 [-21,0]\;\;Need to guarantee that the sum of the coefficient magnitude equals sum |c(i)| &lt;= 63.\;NRZ speeds must guarantee sum|c(i)| = 63\;Note: Configured taps may get effective value of +/-1 from the value that has been set." access="RW" offset="0x4.24" size="0x0.8" />
</node>

<node name="sltp_lut_7nm_ext" descr="" size="0x48.0" >
	<field name="fir_pre2" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Valid values for taps:\;fir_pre2 [0,8]\;fir_pre3 [-5,0]" access="RW" offset="0x0.0" size="0x0.8" />
	<field name="fir_pre3" descr="Signed value for TX FIR taps.\;tap scaling = fir_tap/63.\;Valid values for taps:\;fir_pre2 [0,8]\;fir_pre3 [-5,0]" access="RW" offset="0x0.8" size="0x0.8" />
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0: pre3_is_out_of_range\;Bit 1: pre2_is_out_of_range\;Bit 7: LUT_value_is_out_of_range" access="RO" enum="pre3_is_out_of_range=0x1,pre2_is_out_of_range=0x2,LUT_value_is_out_of_range=0x80" offset="0x0.16" size="0x0.8" />
	<field name="drv_amp" descr="High speed output driver amplitude settings, default = 6&quot;d63.\; amplitude scaling = (AMP+1) / 64" access="RW" offset="0x0.24" size="0x0.6" />
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
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)\;" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.1" size="0x0.3" />
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe) / 5GBASE-R\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR (106.25 Gbd / 212.5Gb/s)\;9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13-15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="conf_mod" descr="Set configuration mode for 7nm/5nm product.\;0: tx_linear - when set, tx taps are configured from\;for 7nm\;Table  681, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 7nm,&quot; on page  738\;For 5nm\;Table  685, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 5nm,&quot; on page  743\;LUT table fields are ignored\;1: tx_lut - when set, tx taps are configured from\;Table  683, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for LUT 7nm,&quot; on page  739\;7nm_fir_taps page fields are ignored." access="OP" enum="tx_linear=0x0,tx_lut=0x1" offset="0x0.12" size="0x0.1" />
	<field name="tx_policy" descr="Configures Tx parameter set policy\;0 - Tx parameters will be set according to best possible configuration chosen by the system\;1 - Tx parameters will be set according to Data Base only and will not be overridden by link training (e.g KR-Startup)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number\;3 - Out of band / PCI" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="0: prod_40nm\;1: prod_28nm\;3: prod_16nm\;4: prod_7nm\;5: prod_5nm" access="RO" enum="prod_40nm=0x0,prod_28nm=0x1,prod_16nm=0x3,prod_7nm=0x4,prod_5nm=0x5" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular, for links that do AN/LT, valid will be set when link operational status is UP (PAOS.oper_status=0x1).\;For links without AN/LT, valid will be set when Tx is enabled.\;\;0 - Invalid\;1 - Valid\;\;Note: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="Table  675, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 28nm and 40nm,&quot; on page  735\;Table  677, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 16nm,&quot; on page  736\;Table  681, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 7nm,&quot; on page  738\;Table  683, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for LUT 7nm,&quot; on page  739\;Table  685, &quot;SLTP - SerDes Lane Transmit Parameters Register Layout for 5nm,&quot; on page  743" subnode="sltp_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x4.0" size="0x48.0" />
</node>

<node name="sltp_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x48.0" >
	<field name="sltp_16nm_ext" descr="" subnode="sltp_16nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_16nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_28nm_40nm_ext" descr="" subnode="sltp_28nm_40nm_ext" condition="($(parent).port_type == Network_Port) AND ($(parent).version == prod_40nm | $(parent).version == prod_28nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_5nm_ext" descr="" subnode="sltp_5nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_7nm_ext" descr="" subnode="sltp_7nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_7nm)" offset="0x0.0" size="0x48.0" />
	<field name="sltp_lut_7nm_ext" descr="" subnode="sltp_lut_7nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port) AND ($(parent).version == prod_7nm)" offset="0x0.0" size="0x48.0" />
</node>

<node name="sltpv2_lut_5nm_ext" descr="" size="0x108.0" >
	<field name="ob_bad_stat" descr="Bitmask for bad &apos;set&apos; status:\;Bit 0:LUT_value_is_out_of_range\;Bit 1: delay_0_invalid\;Bit 2: delay_1_invalid\;Bit 3: delay_2_invalid" access="RO" enum="delay_2_invalid=0x8" offset="0x0.0" size="0x0.16" />
	<field name="lut_sel" descr="0: LUT_1 - taps 0-1 (16 entries), valid ranges per entry: [-16, 15]\;1: LUT_2 - taps 2-5 (256 entries), valid ranges per entry: [-64, 63]\;2: LUT_3 - taps 6-8 (64 entries), valid ranges per entry: [-16, 15]\;3: LUT_4 - taps 9-11 (64 entries), valid ranges per entry: [-16, 15]\;\;Note that only LUT_2 group has FW DB, hence c_db shall work only for LUT_2." access="INDEX" enum="LUT_1=0x0,LUT_2=0x1,LUT_3=0x2,LUT_4=0x3" offset="0x0.20" size="0x0.4" />
	<field name="vs_peer_db" descr="relevant for when c_db is set, else field is ignored.\;for when direct drive module connected:\;0 - db to override is for Did vs Did\;1 - db to override if for Did vs retimed module\;" access="RW" offset="0x0.28" size="0x0.2" />
	<field name="no_db_set" descr="supported only if PCAM bit 96 in feature_cap_mask is set.\;When set, Tx DB will not be written into HW on linkup phase.\;When cleared, Tx DB is written into HW on linkup phase." access="RW" offset="0x0.31" size="0x0.1" />
	<field name="delay0" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.0" size="0x0.6" />
	<field name="delay1" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.6" size="0x0.6" />
	<field name="delay2" descr="relevant for LUT3 (taps6-8), LUT4 (taps9-11). ignore otherwise.\;even taps (6, 8. 10) can get even values\;odd taps (7, 9, 11) cam get odd values." access="RW" offset="0x4.12" size="0x0.6" />
	<field name="lut" descr="Lookup Table values per entry" access="RW" high_bound="255" low_bound="0" offset="0x8.24" size="0x100.0" />
</node>

<node name="sltpv2_reg_ext" descr="" size="0x10c.0" >
	<field name="c_db" descr="Copy transmitter parameters to Data Base. \;When set, for get operation shall return Data Base values\;otherwise will be written to HW directly.\;" access="OP" offset="0x0.0" size="0x0.1" />
	<field name="port_type" descr="For HCA supported only when indicated by PCAM \;0: Network_Port\;1: NearEnd_Port - (For Retimer/Gearbox - Host side)\;2: Internal_IC_LR_Port \;3: FarEnd_Port - (For Retimer/Gearbox - Line side)\;\;" access="INDEX" enum="Network_Port=0x0,NearEnd_Port=0x1,Internal_IC_LR_Port=0x2,FarEnd_Port=0x3" offset="0x0.1" size="0x0.3" />
	<field name="lane_speed" descr="Reserved for PCIe.\;The lane speed for TX settings:\;0 - SDR / Gen1 (PCIe)\;1 - DDR / Gen2 (PCIe) / 5GBASE-R\;2 - QDR / Gen3 (PCIe)\;3 - FDR10 (10GE / 40GE)\;4 - FDR (56GE) / Gen4 (PCIe)\;5 - EDR (25GE / 50GE / 100GE) / Gen5 (PCIe)\;6 - HDR (50GE / 200GE / 400GE)\;7 - NDR /100GE / 200GE / 400GE / 800GE (53.125 Gbd / 106.25Gb/s)\;8 - XDR (106.25 Gbd / 212.5Gb/s)\;9 - Reserved\;10 - 1GE\;11 - 2.5GE (XAUI)\;12 - 50GE-KR4\;13-15 - Reserved" access="RW" offset="0x0.4" size="0x0.4" />
	<field name="lane" descr="Logical lane number" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="tx_policy" descr="Configures Tx parameter set policy\;0 - Tx parameters will be set according to best possible configuration chosen by the system\;1 - Tx parameters will be set according to Data Base only and will not be overridden by link training (e.g KR-Startup)" access="RW" offset="0x0.13" size="0x0.1" />
	<field name="pnat" descr="Port number access type. determines the way local_port is interpreted:\;0 - Local port number\;1 - IB port number" access="INDEX" offset="0x0.14" size="0x0.2" />
	<field name="local_port" descr="Local port number [7:0]" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="version" descr="5: prod_5nm" access="RO" enum="prod_5nm=0x5" offset="0x0.24" size="0x0.4" />
	<field name="status" descr="Indicates that Tx setting readout is valid and active. In particular, for links that do AN/LT, valid will be set when link operational status is UP (PAOS.oper_status=0x1).\;For links without AN/LT, valid will be set when Tx is enabled.\;\;0 - Invalid\;1 - Valid\;\;Note: Get and Set operations can be set when status = invalid." access="RO" offset="0x0.28" size="0x0.1" />
	<field name="lp_msb" descr="Local port number [9:8]" access="INDEX" offset="0x0.30" size="0x0.2" />
	<field name="page_data" descr="Table  689, &quot;SLTPv2 - SerDes Lane Transmit Parameters v2 Register Layout for LUT 5nm,&quot; on page  748" subnode="sltpv2_reg_page_data_auto_ext" access="RW" condition="$(parent).version" offset="0x4.0" size="0x108.0" />
</node>

<node name="sltpv2_reg_page_data_auto_ext" descr="" attr_is_union="1" is_conditional="1" size="0x108.0" >
	<field name="sltpv2_lut_5nm_ext" descr="" subnode="sltpv2_lut_5nm_ext" condition="($(parent).port_type == Network_Port | $(parent).port_type == Internal_IC_LR_Port  | $(parent).port_type == NearEnd_Port  | $(parent).port_type == FarEnd_Port) AND ($(parent).version == prod_5nm)" offset="0x0.0" size="0x108.0" />
</node>

<node name="stat_bufferx_reg_ext" descr="" size="0x8.0" >
	<field name="watermark" descr="Watermark in cells (max buffer usage since last clear)\;For stat_shared_headroom_pool, this field is reserved." access="RO" offset="0x0.0" size="0x0.16" />
	<field name="used_buffer" descr="Number of used buffer cells.\;For stat_port_shared_headroom_pool this field is reserved." access="RO" offset="0x4.0" size="0x0.16" />
</node>

<node name="string_db_parameters_ext" descr="" size="0x8.0" >
	<field name="string_db_base_address" descr="Offset of the first string of the section, relative to the entire string data base, given in bytes." access="RO" offset="0x0.0" size="0x4.0" />
	<field name="string_db_size" descr="Size of string database section, given in bytes" access="RO" offset="0x4.0" size="0x0.24" />
</node>

<node name="uint64" descr="" size="0x8.0" >
	<field name="hi" descr="" offset="0x0.0" size="0x4.0" />
	<field name="lo" descr="" offset="0x4.0" size="0x4.0" />
</node>

<node name="ukdri_ext" descr="" size="0x10.0" >
	<field name="local_port" descr="Local port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear" descr="Clear Indications" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="ktu_disccard_vec" descr="Per bit:\;Bit0: VersionFail - Version is not zero\;Bit1: ProtocolTypeFail - Protocol is not correct\;Bit2: MsgVSActualSizeFail - Msg size does not match actual size\;Bit3: SkMtdNotExist - No MTD in SK message\;Bit4: SkMtdAlignment - MTD in SK is not DW align\;Bit5: SkSecAlignment - SEC in SK in not DW align\;Bit6: MsgSizeVsDsHeaderFail - Msg size vs header mismatch\;Bit7: MsgSizeTooSmall - Actual header size is smaller then minimum size." access="RO" offset="0x8.0" size="0x4.0" />
	<field name="nvle_msg_disccard_vec" descr="Per bit:\;Bit0: MsgSizeNotMatchOpcode - MSG size does not match the opcode\;Bit1: VersionFail - NVLE wrong version\;Bit2: CmdOpcodeFail - Wrong NVLE cmd_opcode\;Bit3: PortNumFail - Wrong port number in NVLE header\;Bit4: PipeNumFail - Invalid pipe number \;Bit5: DataSizeFail - wrong data size \;Bit6: SlotIndexFail - Invalid slot index\;Bit7: NVLEMsgSizeTooSmall - NVLE msg size is smaller then 3." access="RO" offset="0xC.0" size="0x4.0" />
</node>

<node name="under_voltage_stressor_parameters_ext" descr="" size="0x4.0" >
	<field name="under_voltage_percentage_change" descr="The percentage change in 1% units\;If percentage change is over 1 percentage point or change from previous request, FW will return BAD PARAM" access="RW" offset="0x0.0" size="0x0.6" />
</node>

<node name="undfd_ext" descr="" size="0x8.0" >
	<field name="pipe_index" descr="Pipe\;For GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="dfd_en" descr="DFD en, when enabled the encryption will set an authentication error tag:\;0: DFD disabled (default)\;1: DFD enabled" access="RW" offset="0x4.0" size="0x0.1" />
</node>

<node name="undri_ext" descr="" size="0x10.0" >
	<field name="pipe_index" descr="Pipe\;For GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="dir" descr="Direction:\;0: Decr\;1: Encr" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="local_port" descr="Local port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear" descr="Clear Indications" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="discard_vec" descr="Per bit:\;Bit0: BadPktType\;Bit1: NoNVSecTag\;Bit2: NvsetagBadVersion\;Bit3: BadPktLen\;Bit4: PktLenMinSize\;Bit5: AR_MissMatch\;Bit6: FlowMapEntryNotValid\;Bit7: StateEntryNotValid\;Bit8: KeyEntryNotValid\;Bit9: FeedbackOverrun\;Bit10: NVSecTagError\;Bit11: NVLECreditIssue\;Decryption only:\;Bit12: AuthenticationFail\;Bit13: ReplayFail" subnode="uint64" access="RO" offset="0x8.0" size="0x8.0" />
</node>

<node name="unrc_ext" descr="" size="0x40.0" >
	<field name="pipe_index" descr="Pipe\;For GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="local_port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="clear" descr="Clear counters" access="OP" offset="0x0.31" size="0x0.1" />
	<field name="ing_error_packets" descr="count number of error packets ingressing to the NVLE.\;Note: this counter count all the error packet in NVLE - it includes the ing_auth_error counter.\;For counter layout see Table 1384, &quot;Counter Layout,&quot; on page 1517" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
	<field name="ing_good_packets" descr="count number of good packets ingressing the NVLEFor counter layout see Table 1384, &quot;Counter Layout,&quot; on page 1517" subnode="uint64" access="RO" offset="0x18.0" size="0x8.0" />
	<field name="egr_good_packets" descr="count number of good packets egressing the NVLEFor counter layout see Table 1384, &quot;Counter Layout,&quot; on page 1517" subnode="uint64" access="RO" offset="0x20.0" size="0x8.0" />
	<field name="egr_error_packets" descr="count number of error packets egressing the NVLE\;Note: egr_good_packets + egr_error_packets = sum of all packets egressing the NVLE\;For counter layout see Table 1384, &quot;Counter Layout,&quot; on page 1517" subnode="uint64" access="RO" offset="0x28.0" size="0x8.0" />
	<field name="ktu_msg_cnt" descr="Number of messages that was sent from the KTU to the NVLEs.\;Note - this counter is not per pipe.\;For counter layout see Table 1384, &quot;Counter Layout,&quot; on page 1517" subnode="uint64" access="RO" offset="0x30.0" size="0x8.0" />
	<field name="ing_auth_error" descr="Number of authentication errors.\;For counter layout see Table 1384, &quot;Counter Layout,&quot; on page 1517" subnode="uint64" access="RO" offset="0x38.0" size="0x8.0" />
</node>

<node name="unrsa_ext" descr="" size="0x18.0" >
	<field name="pipe_index" descr="Pipe\;For GB100 can be either 0 or 1" access="INDEX" offset="0x0.8" size="0x0.4" />
	<field name="dir" descr="Direction:\;0: Decr\;1: Encr" access="INDEX" offset="0x0.12" size="0x0.1" />
	<field name="local_port" descr="" access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="entry_index" descr="Entry Index.\;Decr range 0..max_cap_sec_key_entry * 2 + 1\;Encr range 0..max_cap_sec_key_entry\;\;" access="INDEX" offset="0x4.0" size="0x0.16" />
	<field name="ev" descr="Entry Valid:\;0: Entry is not valid\;1: Entry is valid\;All RO fields have no meaning when ev=0" access="RO" offset="0x8.24" size="0x0.1" />
	<field name="packet_number" descr="Packet number\;Note: GB100 HW has only 56 bits\;FW note: for Decr read from expected packet number, for Encr read from SADB" subnode="uint64" access="RO" offset="0x10.0" size="0x8.0" />
</node>

<node name="unwkm_ext" descr="" size="0x8c.0" >
	<field name="status" descr="Return status:\;0: OK\;\;FW will parse these fields and set the relevant bit if the value is not valid (1-4 are only for SK):\;Bit1: ktu_msg.SK.common_header_version!=0\;Bit2: ktu_msg.SK.Protocol != NVLE\;Bit3: ktu_msg.SK.nvle_version !=0\;Bit4: ktu_msg.SK.hw_port == not_valid\;Bit5: ktu_msg.op != 1, 2, 3\;Bit6: ktu_msg.size &gt; 22\;\;Bit15: at least one of the bits in errors is set" access="RO" offset="0x0.0" size="0x0.16" />
	<field name="local_port" descr="Local port." access="INDEX" offset="0x0.16" size="0x0.8" />
	<field name="lpv" descr="Local port valid:\;0: local_port field is reserved. FW will look at ktu_msg\;1: local_port is valid. FW will ignore hw_port in ktu_msg if exist." access="OP" offset="0x0.31" size="0x0.1" />
	<field name="errors" descr="KTU error vector, each error set the corresponding bit in the error vector:\;Bit3: CMD_VER_ERR - the command is specified with unsupported KTU_CMD.VER.\;Bit4: CMD_OP_ERR - the command is specified with unsupported KTU_CMD.OP.\;Bit5: CMD_AA_ERR - The command is specified with unsupported KTU_CMD.AA for the given\;KTU_CMD.OP.\;Bit6: CMD_ARG_ERR - The command is specified with unsupported KTU_CMD.ARGs for the given\;KTU_CMD.OP.\;Bit8: INS_IWK_DIS_ERR - INS_IWK command is started but INS_IWK was disabled.\;Bit9: INS_WK_DIS_ERR - INS_WK command is started but INS_WK was disabled.\;Bit10: INS_SK_DIS_ERR - INS_SK command is started\;but INS_SK was disabled.\;Bit11: INS_WK_NWK_ERR - INS_WK command is started but no previous valid WK is available.\;Bit12: INS_SK_NWK_ERR - INS_SK command is started but no valid WK is available.\;Bit14: CMD_AUTH_ERR - The authentication check of the triggered command fails.\;Bit16: ANTI_REPLAY_CNT_CHK_ERR - Anti-replay Counter check fails.\;Bit17: OUTPUT_ERR - Output to the downstream unit is returned with error responses.\;Bit31: MAX_CMD_FAILURE_ERR - 10 commands failure. the count resets after IWK or WK succeeds." access="RW" offset="0x4.0" size="0x4.0" />
	<field name="ktu_msg" descr="Table 1372, &quot;KTU Message Layout,&quot; on page 1511\;FW will extract these fields of the CM:\;1. protocol type - make sure KUW TBD &apos;0&apos;\;2. version - make sure FW can parse this version TBD 0\;3. hw_port - note: hw port = local_port-1\;Note: this is a WO field, cannot be read" access="WO" high_bound="31" low_bound="0" offset="0xC.0" size="0x80.0" />
</node>

<node name="root" size="0x5a0.0" descr="" >
	<field name="register_access_table_gpu_Nodes" offset="0x0.0" size="0x5a0.0" subnode="register_access_table_gpu_Nodes" descr="" />
</node>

<node name="register_access_table_gpu_Nodes" size="0x5a0.0" attr_is_union="1" descr="" >
	<field name="access_reg_summary_selector_ext" offset="0x0.0" size="0x5a0.0" subnode="access_reg_summary_selector_ext" descr="" />
</node>
</NodesDefinition>
